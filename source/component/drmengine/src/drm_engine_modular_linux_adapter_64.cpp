#include "drm_engine_modular_linux_adapter.h"
//#include "drm_widevine_http.h"

using namespace android;

namespace drmengine {

HI_VOID translateToPluginMode(HI_CRYPTO_MODE mode, CryptoPlugin::Mode* pluginMode)
{
    if (NULL == pluginMode)
    {
        LOGE_DRM("pluginMode is NULL\n");
        return;
    }
    switch(mode)
    {
        case HI_CRYPTO_MODE_UNENCRYPTED:
            *pluginMode = CryptoPlugin::kMode_Unencrypted;
            break;
        case HI_CRYPTO_MODE_AES_CTR:
            *pluginMode = CryptoPlugin::kMode_AES_CTR;
            break;
        case HI_CRYPTO_MODE_AES_WV:
            *pluginMode = CryptoPlugin::kMode_AES_WV;
            break;
        case HI_CRYPTO_MODE_AES_CBC:
            *pluginMode = CryptoPlugin::kMode_AES_CBC;
            break;
        default:
            break;
    }
}
#if 0
HI_VOID translateToPluginSubsample(const HI_DRM_SUBSAMPLES *subSamples, CryptoPlugin::SubSample *pluginSubSamples)
{
    if (NULL != subSamples && NULL != pluginSubSamples)
    {
        pluginSubSamples->mNumBytesOfClearData = subSamples->u32numBytesOfClearData;
        pluginSubSamples->mNumBytesOfEncryptedData = subSamples->u32numBytesOfEncryptedData;
    }
}
#endif
HI_VOID translateToPluginPattern(const HI_DRM_PATTERN *pattern, CryptoPlugin::Pattern *pluginPattern)
{
    if (NULL == pattern || NULL == pluginPattern)
    {
        LOGE_DRM("pattern or pluginPattern is NULL\n");
        return;
    }
    if (NULL != pattern && NULL != pluginPattern)
    {
        pluginPattern->mEncryptBlocks = pattern->u32EncryptBlocks;
        pluginPattern->mSkipBlocks = pattern->u32SkipBlocks;
    }
}

DrmEngineModularLinuxAdapter::DrmEngineModularLinuxAdapter(const HI_U8 uuid[16])
    : m_pListener(NULL), m_pDrmFactory(NULL), m_pDrmPlugin(NULL),
      m_pCryptoFactory(NULL), m_pCryptoPlugin(NULL),
      m_pSharedLibrary(NULL), 
      m_strKeySetId("")
{
    LOGI_DRM("Constructor DrmEngineModularLinuxAdapter enter");
    memcpy(m_Uuid, uuid, UUID_SIZE);

    HI_S32 status = createDrmPlugin(uuid);
    if (HI_SUCCESS != status)
    {
        LOGE_DRM("createDrmPlugin fail");
        destroyDrmPlugin();
        return;
    }
}

DrmEngineModularLinuxAdapter::~DrmEngineModularLinuxAdapter(void)
{
    destroyDrmPlugin();
    closeFactory();
}

HI_BOOL DrmEngineModularLinuxAdapter::drmAdpIsCryptoSchemeSupported(const HI_U8 uuid[16], const HI_CHAR* mimetype)
{
    LOGI_DRM("Enter drmAdpIsCryptoSchemeSupported()");
    if(NULL == uuid || NULL == mimetype || NULL == m_pDrmFactory)
    {
        return HI_FALSE;
    }

    String8 strMimeType((HI_CHAR*)mimetype);

    if("" != strMimeType)
    {
        if (m_pDrmFactory->isCryptoSchemeSupported(uuid) &&
            m_pDrmFactory->isContentTypeSupported(strMimeType))
        {
            return HI_TRUE;
        }
    }
    return HI_FALSE;
}

HI_S32 DrmEngineModularLinuxAdapter::drmAdpOpenSession(void)
{
    LOGI_DRM("Enter drmAdpOpenSession()");
    HI_S32 result = HI_FAILURE;
    if(NULL != m_pDrmPlugin)
    {
        result = m_pDrmPlugin->openSession(m_strSessionId);
    }
    LOGI_DRM("result = %d", result);
    if(HI_SUCCESS != result)
    {
        LOGE_DRM("open session failed!");
        return HI_FAILURE;
    }

    result = createCryptoPlugin(m_Uuid);
    if(HI_SUCCESS != result)
    {
        LOGE_DRM("createCryptoPlugin fail");
        destroyCryptoPlugin();
        return HI_FAILURE;
    }
    LOGI_DRM("open session success!");

    return HI_SUCCESS;
}

HI_S32 DrmEngineModularLinuxAdapter::drmAdpCloseSession(void)
{
    LOGI_DRM("Enter drmAdpCloseSession()");
    HI_S32 result = HI_FAILURE;
    destroyCryptoPlugin();

    if(NULL != m_pDrmPlugin)
    {
        result = m_pDrmPlugin->closeSession(m_strSessionId);
        if(HI_SUCCESS != result)
        {
            LOGI_DRM("closeSession fail");
            return HI_FAILURE;
        }
        LOGI_DRM("close session success!");
    }

    return HI_SUCCESS;
}

HI_S32 DrmEngineModularLinuxAdapter::drmAdpGetKeyRequest(const std::string& initData, 
                                            const HI_U8* mimeType, 
                                            HI_DRM_KEY_TYPE keyType, 
                                            std::map < std::string, std::string > &optionalParameters, 
                                            HI_DRM_KEY_REQUEST* pKeyRequest)
{
    LOGI_DRM("Enter drmAdpGetKeyRequest(), mimeType = %s", mimeType);

    if(HI_NULL == mimeType)
    {
        LOGE_DRM("Check param mimeType is null");
    }

    HI_S32 result = HI_FAILURE;
    String8 strMimeType((HI_CHAR*)mimeType);
    Vector<HI_U8> strInitData;
    strInitData.appendArray(reinterpret_cast<const HI_U8*>(initData.c_str()),
                         initData.length());
    Vector<HI_U8> strRequest;
    String8 strRequestUrl("");
    DrmPlugin::KeyType eKeyType;
    DrmPlugin::KeyRequestType eKeyRequestType = DrmPlugin::kKeyRequestType_Unknown;
    KeyedVector<String8, String8> const KVOptionalParameters;

    switch(keyType)
    {
        case HI_DRM_KEY_TYPE_OFFLINE:
            eKeyType = DrmPlugin::kKeyType_Offline;
            break;
        case HI_DRM_KEY_TYPE_STREAMING:
            eKeyType = DrmPlugin::kKeyType_Streaming;
            break;
        case HI_DRM_KEY_TYPE_RELEASE:
            eKeyType = DrmPlugin::kKeyType_Release;
            break;
        default:
            break;
    }

    if(NULL != m_pDrmPlugin)
    {
        LOGI_DRM("begin get to getKeyRequest, strMimeType = %s", mimeType);

        result = m_pDrmPlugin->getKeyRequest(m_strSessionId, strInitData, 
                                                              strMimeType, eKeyType,
                                                              KVOptionalParameters, strRequest,
                                                              strRequestUrl, &eKeyRequestType);
        if(HI_SUCCESS != result)
        {
            LOGE_DRM("getKeyRequest fail result = %d", result);
            return HI_FAILURE;
        }
    }

    switch(eKeyRequestType)
    {
        case DrmPlugin::kKeyRequestType_Initial:
            pKeyRequest->eKeyRequestType = HI_DRM_KEYRST_TYPE_INITIAL;
            break;
        case DrmPlugin::kKeyRequestType_Renewal:
            pKeyRequest->eKeyRequestType = HI_DRM_KEYRST_TYPE_RENEWAL;
            break;
        case DrmPlugin::kKeyRequestType_Release:
            pKeyRequest->eKeyRequestType = HI_DRM_KEYRST_TYPE_RELEASE;
            break;
        default:
            break;
    }

    pKeyRequest->requestData = strRequest;
    pKeyRequest->defaultUrl = strRequestUrl;

#if 0
    LOGI_DRM("begin get to fetch key request");

    if(HI_DRM_EVENT_PROVISION_REQUIRED == m_stMsgData.eDrmEventType)
    {
        LOGI_DRM("begin get to fetch key request HI_DRM_EVENT_PROVISION_REQUIRED");
        result = fetchProvisionAndProKeyRes(m_strSessionId, m_stMsgData.stEventData.data);
        if(HI_FAILURE == result)
        {
            return result;
        }
    }

    //for widevine cdm
    if(HI_DRM_EVENT_LICENSE_REQUEST == m_stMsgData.eDrmEventType)
    {
        result = fetchLicAndProKeyRes(m_strSessionId, m_stMsgData.stEventData.data);
    }
    //for playready(playready have no message)
    else if(pKeyRequest->requestData.length() > 0)
    {
        result = fetchLicAndProKeyRes(m_strSessionId, pKeyRequest->requestData);
    }
    else
    {
        //error happend
        result = HI_FAILURE;
    }
#endif
    LOGI_DRM("Leave drmAdpGetKeyRequest()");
    return result;
}

HI_S32 DrmEngineModularLinuxAdapter::drmAdpProvideKeyResponse(const std::string & response, std::string& keySetId)
{
    LOGI_DRM("Enter drmAdpProvideKeyResponse()");
    HI_S32 status = HI_FAILURE;
    Vector<HI_U8> vecKeySetId;
    Vector<HI_U8> vecResponse;
    vecResponse.appendArray(reinterpret_cast<const HI_U8*>(response.c_str()),
                         response.length());
    if(NULL != m_pDrmPlugin)
    {
        status = m_pDrmPlugin->provideKeyResponse(m_strSessionId, vecResponse, vecKeySetId);
        if(HI_SUCCESS != status)
        {
            LOGE_DRM("provideKeyResponse() fail, status = %d", status);
            return HI_FAILURE;
        }
        keySetId.append((const HI_CHAR*)vecKeySetId.array(), vecKeySetId.size());
        return HI_SUCCESS;
    }
    LOGE_DRM("drmAdpProvideKeyResponse() return HI_FAILURE");
    return HI_FAILURE;
}

HI_S32 DrmEngineModularLinuxAdapter::drmAdpDecrypt(HI_BOOL secure, const uint8_t key[16], const uint8_t iv[16],
                                  const HI_DRM_PATTERN &pattern, HI_CRYPTO_MODE mode, HI_U8* pSrc,
                                  const HI_DRM_SUBSAMPLES *subSamples, HI_S32 numSubSamples,
                                  HI_VOID* pDst)
{
    HI_S32 ret = HI_FAILURE;
    HI_CHAR errorInfo[256] = {0};
    CryptoPlugin::Pattern pluginPattern;
    CryptoPlugin::Mode pluginMode;

    if(NULL != m_pCryptoPlugin)
    {
        translateToPluginMode(mode,  &pluginMode);
        translateToPluginPattern(&pattern,  &pluginPattern);
        ret = m_pCryptoPlugin->decrypt(secure, key, iv, pluginMode,
                                                       pSrc, (CryptoPlugin::SubSample*)subSamples,
                                                       numSubSamples, pDst, errorInfo);
        if(ret < 0)
        {
            LOGE_DRM("decrypt fail, ret = %d", ret);
            return HI_FAILURE;
        }
    }

    return HI_SUCCESS;
}

HI_S32 DrmEngineModularLinuxAdapter::drmAdpGetPropertyString(const std::string &name, const std::string &value)
{
    return HI_SUCCESS;
}

HI_S32 DrmEngineModularLinuxAdapter::drmAdpSetPropertyString(const std::string &name, const std::string &value)
{
    return HI_SUCCESS;
}

HI_S32 DrmEngineModularLinuxAdapter::drmAdpSetListener(DrmListener* listener)
{
    if(NULL != listener)
    {
        m_pListener = listener;
        return HI_SUCCESS;
    }
    return HI_FAILURE;
}

void DrmEngineModularLinuxAdapter::sendEvent(DrmPlugin::EventType eventType, int extra,
                           Vector<HI_U8> const& sessionId,
                           Vector<HI_U8> const& data)
{
    LOGI_DRM("Enter sendEvent event type = %d, sessionId = %s", eventType, sessionId.array());
    HI_DRM_EVENT_TYPE event = HI_DRM_EVENT_KEY_BUTT;
    //HI_DRM_MSG_DATA stMsgData;
    //memset((HI_VOID*)&m_stMsgData, 0, sizeof(HI_DRM_MSG_DATA));

    m_stMsgData.sessionId = sessionId;

    switch(eventType)
    {
        LOGI_DRM("kDrmPluginEventProvisionRequired switch");
        case DrmPlugin::kDrmPluginEventProvisionRequired:
            event = HI_DRM_EVENT_PROVISION_REQUIRED;
            m_stMsgData.stEventData.s32extra = extra;
            m_stMsgData.stEventData.data = data;
            m_stMsgData.eDrmEventType = event;
            //fetchProvisionAndProKeyRes(stMsgData.sessionId, stMsgData.stEventData.data);
            LOGI_DRM("kDrmPluginEventProvisionRequired return");
            return;
            break;
        case DrmPlugin::kDrmPluginEventKeyNeeded:
            event = HI_DRM_EVENT_KEY_NEEDED;
            m_stMsgData.stEventData.s32extra = extra;
            m_stMsgData.stEventData.data = data;
            m_stMsgData.eDrmEventType = event;
            break;
        case DrmPlugin::kDrmPluginEventKeyExpired:
            event = HI_DRM_EVENT_KEY_EXPIRED;
            m_stMsgData.stEventData.s32extra = extra;
            m_stMsgData.stEventData.data = data;
            m_stMsgData.eDrmEventType = event;
            break;
        case DrmPlugin::kDrmPluginEventVendorDefined:
            event = HI_DRM_EVENT_VENDOR_DEFINED;
            m_stMsgData.stEventData.s32extra = extra;
            m_stMsgData.stEventData.data = data;
            m_stMsgData.eDrmEventType = event;
            break;
        case DrmPlugin::kDrmPluginEventSessionReclaimed:
            event = HI_DRM_EVENT_SESSION_RECLAIMED;
            m_stMsgData.stEventData.s32extra = extra;
            m_stMsgData.stEventData.data = data;
            m_stMsgData.eDrmEventType = event;
            break;
        case DrmPlugin::kDrmPluginEventRemoveComplete:
            event = HI_DRM_EVENT_REMOVE_COMPLETE;
            m_stMsgData.stEventData.s32extra = extra;
            m_stMsgData.stEventData.data = data;
            m_stMsgData.eDrmEventType = event;
            break;
        case DrmPlugin::kDrmPluginEventLicenseRequest:
            event = HI_DRM_EVENT_LICENSE_REQUEST;
            m_stMsgData.stEventData.s32extra = extra;
            m_stMsgData.stEventData.data = data;
            m_stMsgData.eDrmEventType = event;
            //fetchLicAndProKeyRes(m_stMsgData.sessionId, m_stMsgData.data);
            return;
            break;
        case DrmPlugin::kDrmPluginEventLicenseRenewal:
            event = HI_DRM_EVENT_LICENSE_RENEWAL;
            m_stMsgData.stEventData.s32extra = extra;
            m_stMsgData.stEventData.data = data;
            m_stMsgData.eDrmEventType = event;
            break;
        case DrmPlugin::kDrmPluginEventLicenseRelease:
            event = HI_DRM_EVENT_LICENSE_RENEWAL;
            m_stMsgData.stEventData.s32extra = extra;
            m_stMsgData.stEventData.data = data;
            m_stMsgData.eDrmEventType = event;
            break;
        default:
            break;
    }

    LOGI_DRM("begin notify m_pListener");
    m_pListener->notify(event, &m_stMsgData);
}

void DrmEngineModularLinuxAdapter::sendExpirationUpdate(Vector<HI_U8> const& sessionId,
                                      int64_t expiryTimeInMS)
{
    LOGI_DRM("enter sendExpirationUpdate");
    HI_DRM_EVENT_TYPE event = HI_DRM_EVENT_EXPIRATION_UPDATE;
    HI_DRM_MSG_DATA stMsgData;

    stMsgData.sessionId = sessionId;
    stMsgData.s64expiryTimeInMS = expiryTimeInMS;

    m_pListener->notify(event, &stMsgData);
}

void DrmEngineModularLinuxAdapter::sendKeysChange(Vector<HI_U8> const& sessionId,
                                std::list<DrmPlugin::KeyStatus> keyStatusList,
                                bool hasNewUsableKey)
{
    LOGI_DRM("enter sendKeysChange");
    HI_DRM_EVENT_TYPE event = HI_DRM_EVENT_KEY_CHANGE;
    HI_DRM_MSG_DATA stMsgData;
    HI_KEY_STATUS stKeyStatus;

    stMsgData.sessionId = sessionId;
    stMsgData.stkeyChange.bhasNewUsableKey = (true == hasNewUsableKey) ? HI_TRUE : HI_FALSE;

    std::list<DrmPlugin::KeyStatus>::iterator iter;
    for(iter =  keyStatusList.begin(); iter != keyStatusList.end(); iter++)
    {
        stKeyStatus.mKeyId = (iter->mKeyId);
        stKeyStatus.mType = transKeyStatus(iter->mType);
        stMsgData.stkeyChange.stkeyStatusList.push_back(stKeyStatus);
    }

    m_pListener->notify(event, &stMsgData);

}

void DrmEngineModularLinuxAdapter::sendDeferredComplete(Vector<HI_U8> const& sessionId, status_t sessionStatus)
{
    LOGI_DRM("enter sendDeferredComplete");
    HI_DRM_EVENT_TYPE event = HI_DRM_EVENT_DEFERRED_COMPLETE;
    HI_DRM_MSG_DATA stMsgData;

    stMsgData.sessionId = sessionId;
    stMsgData.stEventData.s32extra = sessionStatus;

    m_pListener->notify(event, &stMsgData);

}

HI_S32 DrmEngineModularLinuxAdapter::createDrmPlugin(const HI_U8 uuid[16])
{
    HI_S32 status = HI_FAILURE;
    LOGI_DRM("Enter createDrmPlugin()");
    if(!findFactoryForScheme(uuid))
    {
        LOGE_DRM("failed find scheme %s", uuid);
        return HI_FAILURE;
    }

    if(NULL != m_pDrmFactory)
    {
        status = m_pDrmFactory->createPlugin(uuid, &m_pDrmPlugin);
        if (HI_SUCCESS != status)
        {
            LOGE_DRM("createDrmPlugin fail");
            destroyDrmPlugin();
            return HI_FAILURE;
        }
    }

    LOGI_DRM("createDrmPlugin success!");

    return HI_SUCCESS;
}

HI_S32 DrmEngineModularLinuxAdapter::createCryptoPlugin(const HI_U8 uuid[16])
{
    HI_S32 status = HI_FAILURE;
    LOGI_DRM("Enter createCryptoPlugin()");
    if(!findFactoryForScheme(uuid))
    {
        LOGE_DRM("failed find scheme %s", uuid);
        return HI_FAILURE;
    }

    if(NULL != m_pCryptoFactory)
    {
        status = m_pCryptoFactory->createPlugin(uuid, m_strSessionId.editArray(), m_strSessionId.size(), &m_pCryptoPlugin);
        if (HI_SUCCESS != status)
        {
            LOGE_DRM("createCryptoPlugin fail");
            destroyCryptoPlugin();
            return HI_FAILURE;
        }
        LOGI_DRM("createCryptoPlugin success!");
    }

    return HI_SUCCESS;
}

HI_S32 DrmEngineModularLinuxAdapter::destroyDrmPlugin()
{
    if(NULL != m_pDrmPlugin)
    {
        delete m_pDrmPlugin;
        m_pDrmPlugin = NULL;
    }
    LOGI_DRM("destroyDrmPlugin success");
    return HI_SUCCESS;
}

HI_S32 DrmEngineModularLinuxAdapter::destroyCryptoPlugin()
{
    if(NULL != m_pCryptoPlugin)
    {
        delete m_pCryptoPlugin;
        m_pCryptoPlugin = NULL;
    }
    LOGI_DRM("destroyCryptoPlugin success");
    return HI_SUCCESS;
}

HI_BOOL DrmEngineModularLinuxAdapter::findFactoryForScheme(const HI_U8 uuid[16])
{
    LOGI_DRM("Enter findFactoryForScheme()");
    std::string strPath("/vendor/lib/mediadrm");

    DIR* pDir = opendir(strPath.c_str());

    if(NULL != pDir)
    {
        struct dirent* pEntry;

        while(pEntry = readdir(pDir))
        {
            std::string strPluginPath;
            strPluginPath = strPath;
            strPluginPath += "/";
            strPluginPath += pEntry->d_name;
            HI_S32 nPos = strPluginPath.find(".so");

            if(nPos == strPluginPath.length() -3)
            {
                if(loadLibraryForScheme(strPluginPath, uuid))
                {
                    closedir(pDir);
                    LOGI_DRM("findFactoryForScheme() success");
                    return HI_TRUE;
                }
            }
        }

        closedir(pDir);
    }
    return HI_FALSE;
}

HI_BOOL DrmEngineModularLinuxAdapter::loadLibraryForScheme(const std::string strPath, const HI_U8 uuid[16])
{
    LOGI_DRM("strPath = %s", strPath.c_str());

    m_pSharedLibrary = new SharedLibrary(strPath);
    if(!*m_pSharedLibrary)
    {
        LOGE_DRM("loadLibraryForScheme fail1");
        return HI_FALSE;
    }

    typedef DrmFactory* (*CreateDrmFactoryFunc)();
    typedef CryptoFactory* (*CreateCryptoFactoryFunc)();

    CreateDrmFactoryFunc createDrmFactory = (CreateDrmFactoryFunc)(m_pSharedLibrary->lookup("createDrmFactory"));
    CreateCryptoFactoryFunc createCryptoFactory = (CreateCryptoFactoryFunc)(m_pSharedLibrary->lookup("createCryptoFactory"));

    if(NULL == createDrmFactory ||
        NULL == createCryptoFactory ||
        (m_pDrmFactory = createDrmFactory()) == NULL ||
       (m_pCryptoFactory = createCryptoFactory()) == NULL ||
       !m_pDrmFactory->isCryptoSchemeSupported(uuid) ||
       !m_pCryptoFactory->isCryptoSchemeSupported(uuid))
    {
        LOGE_DRM("loadLibraryForScheme fail2");
        closeFactory();
        return HI_FALSE;
    }
    LOGI_DRM("loadLibraryForScheme success");
    return HI_TRUE;
}

HI_VOID DrmEngineModularLinuxAdapter::closeFactory()
{
    if(NULL != m_pDrmFactory)
    {
        delete m_pDrmFactory;
        m_pDrmFactory = NULL;
    }

    if(NULL != m_pCryptoFactory)
    {
        delete m_pCryptoFactory;
        m_pCryptoFactory= NULL;
    }

    if(NULL != m_pSharedLibrary)
    {
        delete m_pSharedLibrary;
        m_pSharedLibrary = NULL;
    }
}

HI_DRM_KEYSTATUS_TYPE DrmEngineModularLinuxAdapter::transKeyStatus(DrmPlugin::KeyStatusType keyStatus)
{
    switch(keyStatus)
    {
        case DrmPlugin::kKeyStatusType_Usable:
            return HI_DRM_KEYSTATUS_TYPE_USABLE;
            break;
        case DrmPlugin::kKeyStatusType_Expired:
            return HI_DRM_KEYSTATUS_TYPE_EXPIRED;
            break;
        case DrmPlugin::kKeyStatusType_OutputNotAllowed:
            return HI_DRM_KEYSTATUS_TYPE_OUTPUT_NOT_ALLOWED;
            break;
        case DrmPlugin::kKeyStatusType_StatusPending:
            return HI_DRM_KEYSTATUS_TYPE_STATUS_PENDING;
            break;
        case DrmPlugin::kKeyStatusType_InternalError:
            return HI_DRM_KEYSTATUS_TYPE_INTERNAL_ERROR;
            break;
        case DrmPlugin::kKeyStatusType_Released:
            return HI_DRM_KEYSTATUS_TYPE_Released;
            break;
        default:
            return HI_DRM_KEYSTATUS_TYPE_BUTT;
            break;
    }
}

HI_S32 DrmEngineModularLinuxAdapter::fetchLicAndProKeyRes(const std::string sessionId, const std::string request)
{
    std::string response;
    HI_S32 status = HI_FAILURE;
#if 0
    if(sessionId != m_strSessionId)
    {
        return HI_FAILURE;
    }

    status = fetchLicense(kLicenseServerAppspot, request, &response);
    if(HI_SUCCESS != status)
    {
        return HI_FAILURE;
    }

    status = drmAdpProvideKeyResponse(response, m_strKeySetId);
#endif
    return status;
}

HI_S32 DrmEngineModularLinuxAdapter::fetchProvisionAndProKeyRes(const std::string sessionId, const std::string request)
{
    LOGI_DRM("Enter fetchProvisionAndProKeyRes(), sessionId = %s", sessionId.c_str());
    std::string response;
    HI_S32 status = HI_FAILURE;
    std::string url = kProvisioningServerUrl;
#if 0
    if(sessionId != m_strSessionId)
    {
        return HI_FAILURE;
    }

    url += "&signedRequest=" + request;

    status = fetchLicense(url, "", &response);
    if(HI_SUCCESS != status)
    {
        return HI_FAILURE;
    }

    status = drmAdpProvideKeyResponse(response, m_strKeySetId);
#endif
    return status;
}

HI_S32 DrmEngineModularLinuxAdapter::fetchLicense(const std::string url, const std::string request, std::string* response)
{
    LOGI_DRM("Enter fetchLicense()");
    HI_S32 status = HI_SUCCESS;
#if 0
    DrmWidevineHttp *drmWvHttp = new DrmWidevineHttp(url);
    if(HI_NULL == drmWvHttp)
    {
        return HI_FAILURE;
    }

    status = drmWvHttp->drmHttpFetchLicense(request, response);

    delete drmWvHttp;
    drmWvHttp = HI_NULL;
#endif
    return status;
}

}
