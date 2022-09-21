#include "drm_engine_modular_android_adapter.h"

namespace drmengine {

DrmEngineModularAndroidAdapter::DrmEngineModularAndroidAdapter(const HI_U8 uuid[16])
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

DrmEngineModularAndroidAdapter::~DrmEngineModularAndroidAdapter(void)
{
    destroyDrmPlugin();
    closeFactory();
}

HI_BOOL DrmEngineModularAndroidAdapter::drmAdpIsCryptoSchemeSupported(const HI_U8 uuid[16], const HI_CHAR* mimetype)
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

HI_S32 DrmEngineModularAndroidAdapter::drmAdpOpenSession(void)
{
    LOGI_DRM("Enter drmAdpOpenSession()");
    HI_S32 result = HI_FAILURE;
    if(NULL != m_pDrmPlugin)
    {
        result = m_pDrmPlugin->openSession(m_strSessionId);
    }
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

HI_S32 DrmEngineModularAndroidAdapter::drmAdpCloseSession(void)
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
    }

    return HI_SUCCESS;
}

HI_S32 DrmEngineModularAndroidAdapter::drmAdpGetKeyRequest(const std::string& initData, 
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

    return HI_SUCCESS;
}

HI_S32 DrmEngineModularAndroidAdapter::drmAdpProvideKeyResponse(const std::string & response, std::string & keySetId)
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
            return HI_FAILURE;
        }
        keySetId.append((const HI_CHAR*)vecKeySetId.array(), vecKeySetId.size());
        return HI_SUCCESS;
    }
    return HI_FAILURE;
}

HI_S32 DrmEngineModularAndroidAdapter::drmAdpDecrypt(HI_BOOL secure, const uint8_t key[16], const uint8_t iv[16],
                                  const HI_DRM_PATTERN &pattern, HI_CRYPTO_MODE mode, HI_U8* pSrc,
                                  const HI_DRM_SUBSAMPLES *subSamples, HI_S32 numSubSamples,
                                  HI_VOID* pDst)
{
    return HI_SUCCESS;
}

HI_S32 DrmEngineModularAndroidAdapter::drmAdpGetPropertyString(const std::string &name, const std::string &value)
{
    return HI_SUCCESS;
}

HI_S32 DrmEngineModularAndroidAdapter::drmAdpSetPropertyString(const std::string &name, const std::string &value)
{
    return HI_SUCCESS;
}

HI_S32 DrmEngineModularAndroidAdapter::drmAdpSetListener(DrmListener* listener)
{
    if(NULL != listener)
    {
        m_pListener = listener;
        return HI_SUCCESS;
    }
    return HI_FAILURE;
}

void DrmEngineModularAndroidAdapter::sendEvent(DrmPlugin::EventType eventType, int extra,
                           Vector<HI_U8> const& sessionId,
                           Vector<HI_U8> const& data)
{
    HI_DRM_EVENT_TYPE event = HI_DRM_EVENT_KEY_BUTT;
    HI_DRM_MSG_DATA stMsgData;

    stMsgData.sessionId = sessionId;

    switch(eventType)
    {
        case DrmPlugin::kDrmPluginEventProvisionRequired:
            event = HI_DRM_EVENT_PROVISION_REQUIRED;
            stMsgData.stEventData.s32extra = extra;
            stMsgData.stEventData.data = data;
            break;
        case DrmPlugin::kDrmPluginEventKeyNeeded:
            event = HI_DRM_EVENT_KEY_NEEDED;
            stMsgData.stEventData.s32extra = extra;
            stMsgData.stEventData.data = data;
            break;
        case DrmPlugin::kDrmPluginEventKeyExpired:
            event = HI_DRM_EVENT_KEY_EXPIRED;
            stMsgData.stEventData.s32extra = extra;
            stMsgData.stEventData.data = data;
            break;
        case DrmPlugin::kDrmPluginEventVendorDefined:
            event = HI_DRM_EVENT_VENDOR_DEFINED;
            stMsgData.stEventData.s32extra = extra;
            stMsgData.stEventData.data = data;
            break;
        case DrmPlugin::kDrmPluginEventSessionReclaimed:
            event = HI_DRM_EVENT_SESSION_RECLAIMED;
            stMsgData.stEventData.s32extra = extra;
            stMsgData.stEventData.data = data;
            break;
        case DrmPlugin::kDrmPluginEventRemoveComplete:
            event = HI_DRM_EVENT_REMOVE_COMPLETE;
            stMsgData.stEventData.s32extra = extra;
            stMsgData.stEventData.data = data;
            break;
        case DrmPlugin::kDrmPluginEventLicenseRequest:
            event = HI_DRM_EVENT_LICENSE_REQUEST;
            stMsgData.stEventData.s32extra = extra;
            stMsgData.stEventData.data = data;
            break;
        case DrmPlugin::kDrmPluginEventLicenseRenewal:
            event = HI_DRM_EVENT_LICENSE_RENEWAL;
            stMsgData.stEventData.s32extra = extra;
            stMsgData.stEventData.data = data;
            break;
        case DrmPlugin::kDrmPluginEventLicenseRelease:
            event = HI_DRM_EVENT_LICENSE_RENEWAL;
            stMsgData.stEventData.s32extra = extra;
            stMsgData.stEventData.data = data;
            break;
        default:
            break;
    }

    m_pListener->notify(event, &stMsgData);
}

void DrmEngineModularAndroidAdapter::sendExpirationUpdate(Vector<HI_U8> const& sessionId,
                                      int64_t expiryTimeInMS)
{
    HI_DRM_EVENT_TYPE event = HI_DRM_EVENT_EXPIRATION_UPDATE;
    HI_DRM_MSG_DATA stMsgData;

    stMsgData.sessionId = sessionId;
    stMsgData.s64expiryTimeInMS = expiryTimeInMS;

    m_pListener->notify(event, &stMsgData);
}

void DrmEngineModularAndroidAdapter::sendKeysChange(Vector<HI_U8> const& sessionId,
                                std::list<DrmPlugin::KeyStatus> keyStatusList,
                                bool hasNewUsableKey)
{
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

void DrmEngineModularAndroidAdapter::sendDeferredComplete(Vector<HI_U8> const& sessionId, status_t sessionStatus)
{
    HI_DRM_EVENT_TYPE event = HI_DRM_EVENT_DEFERRED_COMPLETE;
    HI_DRM_MSG_DATA stMsgData;

    stMsgData.sessionId = sessionId;
    stMsgData.stEventData.s32extra = sessionStatus;

    m_pListener->notify(event, &stMsgData);

}

HI_S32 DrmEngineModularAndroidAdapter::createDrmPlugin(const HI_U8 uuid[16])
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
    //m_pDrmPlugin->setListener(this);
    LOGI_DRM("createDrmPlugin success!");

    return HI_SUCCESS;
}

HI_S32 DrmEngineModularAndroidAdapter::createCryptoPlugin(const HI_U8 uuid[16])
{
    HI_S32 status = HI_FAILURE;
    LOGI_DRM("Enter createCryptoPlugin()");
    if(!findFactoryForScheme(uuid))
    {
        LOGE_DRM("failed find scheme %s", uuid);
        return HI_FAILURE;
    }

    // For adaptive interface with android
    //const HI_CHAR* data = "testdata";
    //HI_U32 size = 8;
    if(NULL != m_pCryptoFactory)
    {
        status = m_pCryptoFactory->createPlugin(uuid, m_strSessionId.array(), m_strSessionId.size(), &m_pCryptoPlugin);
        if (HI_SUCCESS != status)
        {
            LOGE_DRM("createCryptoPlugin fail");
            destroyCryptoPlugin();
            return HI_FAILURE;
        }
    }
    LOGI_DRM("createCryptoPlugin success!");

    return HI_SUCCESS;
}

HI_S32 DrmEngineModularAndroidAdapter::destroyDrmPlugin()
{
    if(NULL != m_pDrmPlugin)
    {
        delete m_pDrmPlugin;
        m_pDrmPlugin = NULL;
    }

    return HI_SUCCESS;
}

HI_S32 DrmEngineModularAndroidAdapter::destroyCryptoPlugin()
{
    if(NULL != m_pCryptoPlugin)
    {
        delete m_pCryptoPlugin;
        m_pCryptoPlugin = NULL;
    }
    return HI_SUCCESS;
}

HI_BOOL DrmEngineModularAndroidAdapter::findFactoryForScheme(const HI_U8 uuid[16])
{
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
                    return HI_TRUE;
                }
            }
        }

        closedir(pDir);
    }
    return HI_FALSE;
}

HI_BOOL DrmEngineModularAndroidAdapter::loadLibraryForScheme(const std::string strPath, const HI_U8 uuid[16])
{
    m_pSharedLibrary = new SharedLibrary(strPath);
    if(!*m_pSharedLibrary)
    {
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
        closeFactory();
        return HI_FALSE;
    }

    return HI_TRUE;
}

HI_VOID DrmEngineModularAndroidAdapter::closeFactory()
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

HI_DRM_KEYSTATUS_TYPE DrmEngineModularAndroidAdapter::transKeyStatus(DrmPlugin::KeyStatusType keyStatus)
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

}
