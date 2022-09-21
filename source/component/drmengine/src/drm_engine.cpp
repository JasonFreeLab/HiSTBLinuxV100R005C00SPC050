#include "drm_engine.h"
#include "WVLog.h"

#include <stdio.h>

namespace drmengine {

DrmEngineApi* DrmEngineApi::DRM_Create(const HI_U8 uuid[16], 
                                                     const HI_CHAR* mimeType, 
                                                     const HI_PLUGIN_MODE pluginMode,
                                                     HI_U32 mimeTypeLength, 
                                                     const std::string& initData,
                                                     DrmListener* listener,
                                                     HI_DRM_KEY_TYPE keyType,
                                                     std::map < std::string, std::string > &optionalParameters)
{
    LOGI_DRM("Enter DRM_Create()");
    //LOGI_DRM("uuid = %s", uuid);
    if(/*NULL == uuid || NULL == mimeType || */NULL == listener)
    {
        LOGE_DRM("listener = %x", listener);
        return NULL;
    }

    if(HI_PLUGIN_MODULAR != pluginMode && HI_PLUGIN_CLASSIC != pluginMode)
    {
        return NULL;
    }

#if 0
    if(0 >= mimeTypeLength)
    {
        return NULL;
    }
#endif

    HI_S32 status = HI_FAILURE;
    HI_DRM_KEY_REQUEST stKeyRequest;

    // load library and create plugin
    DrmEngineApi* pDrmEngineApi = new DrmEngine(uuid, mimeType, pluginMode);

    // set the listener given from media player
    pDrmEngineApi->drmSetListener(listener);

    LOGI_DRM("Begin get to open session");
    // open drm session
    status = pDrmEngineApi->drmOpenSession();
    if(HI_SUCCESS != status)
    {
        //DrmEngineApi::DRM_Destroy(pDrmEngineApi);
        LOGE_DRM("open session failed!");
        return NULL;
    }

    LOGI_DRM("Begin get to getKeyRequest, mimeType = %s", mimeType);
    // get key request
    status = pDrmEngineApi->drmGetKeyRequest(initData, 
                                            (HI_U8*)mimeType, 
                                            keyType, 
                                            optionalParameters, 
                                            &stKeyRequest);
    if(HI_SUCCESS != status)
    {
        LOGE_DRM("get key request failed!");
        return NULL;
    }

    return pDrmEngineApi;
}

HI_S32 DrmEngineApi::DRM_Destroy(DrmEngineApi* &drmClient)
{
    drmClient->drmCloseSession();

    if(NULL != drmClient)
    {
        delete drmClient;
        drmClient = NULL;
    }

    return HI_SUCCESS;
}

HI_S32 DrmEngineApi::DRM_Decrypto(DrmEngineApi* drmClient,
                                                 HI_BOOL secure, HI_U8* key, HI_S32 keyLen,
                                                 HI_U8* iv, HI_S32 ivLen, HI_CRYPTO_MODE mode,
                                                 HI_U8* pSrc,HI_S32 s32srcSize,
                                                 HI_DRM_PATTERN pattern,
                                                 const HI_DRM_SUBSAMPLES* subSamples, HI_S32 numSubSamples,
                                                 HI_VOID *pDst)
{
    if(HI_NULL != drmClient && HI_NULL != key && HI_NULL != iv
       && HI_NULL != pSrc && HI_NULL != subSamples && HI_NULL != pDst)
    {
        return drmClient->drmDecrypt(secure, key, iv,
                                                    pattern, mode,pSrc,
                                                    subSamples, numSubSamples,
                                                    pDst);
    }
}

DrmEngine::DrmEngine(const HI_U8 uuid[16], const HI_CHAR* mimetype, HI_PLUGIN_MODE pluginmode)
    : m_pDrmEngineAdapter(NULL)
{
    LOGI_DRM("Constructor DrmEngine Enter");
    if(HI_PLUGIN_MODULAR == pluginmode)
    {
        m_pDrmEngineAdapter = new DrmEngineAdapter(uuid);
    }
    else if(HI_PLUGIN_CLASSIC == pluginmode)
    {
        m_pDrmEngineAdapter = new DrmEngineAdapter(mimetype);
    }
}

DrmEngine::~DrmEngine()
{
    if(NULL != m_pDrmEngineAdapter)
    {
        LOGI_DRM("~DrmEngine");
        delete m_pDrmEngineAdapter;
        m_pDrmEngineAdapter = NULL;
    }
}

HI_BOOL DrmEngine::drmIsCryptoSchemeSupported(const HI_U8 uuid[16], const HI_CHAR* mimetype)
{
    if(NULL== uuid || NULL == mimetype || NULL == m_pDrmEngineAdapter)
    {
        return HI_FALSE;
    }
    return m_pDrmEngineAdapter->drmIsCryptoSchemeSupported(uuid, mimetype);
}

HI_S32 DrmEngine::drmOpenSession(void)
{
    return m_pDrmEngineAdapter->drmOpenSession();
}

HI_S32 DrmEngine::drmCloseSession(void)
{
    if(NULL != m_pDrmEngineAdapter)
    {
        return m_pDrmEngineAdapter->drmCloseSession();
    }
}

HI_S32 DrmEngine::drmGetKeyRequest(const std::string& initData, 
                                            const HI_U8* mimeType, 
                                            HI_DRM_KEY_TYPE keyType, 
                                            std::map < std::string, std::string > &optionalParameters, 
                                            HI_DRM_KEY_REQUEST* pKeyRequest)
{
    if(NULL != m_pDrmEngineAdapter)
    {
        return m_pDrmEngineAdapter->drmGetKeyRequest(initData, mimeType, keyType,  optionalParameters, pKeyRequest);
    }
}

HI_S32 DrmEngine::drmProvideKeyResponse(const std::string & response, std::string &keySetId)
{
    if(HI_NULL != m_pDrmEngineAdapter)
    {
        return m_pDrmEngineAdapter->drmProvideKeyResponse(response, keySetId);
    }
}

HI_S32 DrmEngine::drmDecrypt(HI_BOOL secure, const uint8_t key[16], const uint8_t iv[16],
                                  const HI_DRM_PATTERN &pattern, HI_CRYPTO_MODE mode, HI_U8* pSrc,
                                  const HI_DRM_SUBSAMPLES *subSamples, HI_S32 numSubSamples,
                                  HI_VOID* pDst)
{
    if(HI_NULL != m_pDrmEngineAdapter)
    {
        return m_pDrmEngineAdapter->drmDecrypt(secure, key, iv, pattern,
                                                          mode, pSrc, subSamples,
                                                          numSubSamples, pDst);
    }
}

HI_S32 DrmEngine::drmGetPropertyString(const std::string &name, const std::string &value)
{
    return HI_SUCCESS;
}

HI_S32 DrmEngine::drmSetPropertyString(const std::string &name, const std::string &value)
{
    return HI_SUCCESS;
}

HI_S32 DrmEngine::drmSetListener(DrmListener* listener)
{
    if(NULL != listener)
    {
        return m_pDrmEngineAdapter->drmSetListener(listener);
    }
    return HI_FAILURE;
}

}
