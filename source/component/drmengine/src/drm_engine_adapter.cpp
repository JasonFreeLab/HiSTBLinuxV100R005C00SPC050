#include "drm_engine_adapter.h"
#include "drm_engine_modular_linux_adapter.h"
#include "drm_engine_modular_android_adapter.h"
#include "drm_engine_classic_adapter.h"

namespace drmengine {

    DrmEngineAdapter::DrmEngineAdapter(const HI_U8 uuid[16])
        : m_pDrmEnginePluginAdapterApi(NULL)
    {
        LOGI_DRM("Constructor DrmEngineAdapter enter");
        //LOGI_DRM("uuid = %s", uuid);
        // for linux
        #ifdef DRM_LINUX
        m_pDrmEnginePluginAdapterApi = new DrmEngineModularLinuxAdapter(uuid);
        #endif

        // for android
        #ifdef DRM_ANDROID
        m_pDrmEnginePluginAdapterApi = new DrmEngineModularAndroidAdapter(uuid);
        #endif
    }

    DrmEngineAdapter::DrmEngineAdapter(const HI_CHAR* mimetype)
        : m_pDrmEnginePluginAdapterApi(NULL)
    {
        m_pDrmEnginePluginAdapterApi = new DrmEngineClassicAdapter(mimetype);
    }

    DrmEngineAdapter::~DrmEngineAdapter()
    {
        if(NULL != m_pDrmEnginePluginAdapterApi)
        {
            delete m_pDrmEnginePluginAdapterApi;
            m_pDrmEnginePluginAdapterApi = NULL;
        }
    }

    HI_BOOL DrmEngineAdapter::drmIsCryptoSchemeSupported(const HI_U8 uuid[16], const HI_CHAR* mimetype)
    {
        if(NULL == uuid || NULL == mimetype || NULL == m_pDrmEnginePluginAdapterApi)
        {
            return HI_FALSE;
        }
        return m_pDrmEnginePluginAdapterApi->drmAdpIsCryptoSchemeSupported(uuid, mimetype);
    }

    HI_S32 DrmEngineAdapter::drmOpenSession(void)
    {
        if(NULL != m_pDrmEnginePluginAdapterApi)
        {
            return m_pDrmEnginePluginAdapterApi->drmAdpOpenSession();
        }
        return HI_FAILURE;
    }

    HI_S32 DrmEngineAdapter::drmCloseSession(void)
    {
        if(NULL != m_pDrmEnginePluginAdapterApi)
        {
            return m_pDrmEnginePluginAdapterApi->drmAdpCloseSession();
        }
        return HI_FAILURE;
    }

    HI_S32 DrmEngineAdapter::drmGetKeyRequest(const std::string& initData, 
                                                const HI_U8* mimeType, 
                                                HI_DRM_KEY_TYPE keyType, 
                                                std::map < std::string, std::string > &optionalParameters, 
                                                HI_DRM_KEY_REQUEST* pKeyRequest)
    {
        if(NULL != m_pDrmEnginePluginAdapterApi)
        {
            return m_pDrmEnginePluginAdapterApi->drmAdpGetKeyRequest(initData, mimeType, keyType,  optionalParameters, pKeyRequest);
        }
        return HI_FAILURE;
    }

    HI_S32 DrmEngineAdapter::drmProvideKeyResponse(const std::string & response, std::string& keySetId)
    {
        if(NULL != m_pDrmEnginePluginAdapterApi)
        {
            return m_pDrmEnginePluginAdapterApi->drmAdpProvideKeyResponse(response, keySetId);
        }
        return HI_FAILURE;
    }

    HI_S32 DrmEngineAdapter::drmDecrypt(HI_BOOL secure, const uint8_t key[16], const uint8_t iv[16],
                                      const HI_DRM_PATTERN &pattern, HI_CRYPTO_MODE mode, HI_U8* pSrc,
                                      const HI_DRM_SUBSAMPLES *subSamples, HI_S32 numSubSamples,
                                      HI_VOID* pDst)
    {
        if(HI_NULL != m_pDrmEnginePluginAdapterApi)
        {
            return m_pDrmEnginePluginAdapterApi->drmAdpDecrypt(secure, key, iv,
                                                                              pattern, mode, pSrc,
                                                                              subSamples, numSubSamples, pDst);
        }
        return HI_FAILURE;
    }

    HI_S32 DrmEngineAdapter::drmGetPropertyString(const std::string &name, const std::string &value)
    {
        return HI_SUCCESS;
    }

    HI_S32 DrmEngineAdapter::drmSetPropertyString(const std::string &name, const std::string &value)
    {
        return HI_SUCCESS;
    }

    HI_S32 DrmEngineAdapter::drmSetListener(DrmListener* listener)
    {
        if(NULL != listener)
        {
            return m_pDrmEnginePluginAdapterApi->drmAdpSetListener(listener);
        }
        return HI_FAILURE;
    }

}
