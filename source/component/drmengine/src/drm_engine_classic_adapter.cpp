#include "drm_engine_classic_adapter.h"

namespace drmengine {

    DrmEngineClassicAdapter::DrmEngineClassicAdapter(const HI_CHAR* mimetype)
    {

    }

    DrmEngineClassicAdapter::~DrmEngineClassicAdapter(void)
    {

    }

    HI_BOOL DrmEngineClassicAdapter::drmAdpIsCryptoSchemeSupported(const HI_U8 uuid[16], const HI_CHAR* mimetype)
    {
        return HI_TRUE;
    }

    HI_S32 DrmEngineClassicAdapter::drmAdpOpenSession(void)
    {
        return HI_SUCCESS;
    }

    HI_S32 DrmEngineClassicAdapter::drmAdpCloseSession(void)
    {
        return HI_SUCCESS;
    }

    HI_S32 DrmEngineClassicAdapter::drmAdpGetKeyRequest(const std::string& initData, 
                                                const HI_U8* mimeType, 
                                                HI_DRM_KEY_TYPE keyType, 
                                                std::map < std::string, std::string > &optionalParameters, 
                                                HI_DRM_KEY_REQUEST *pKeyRequest)
    {
        return HI_SUCCESS;
    }

    HI_S32 DrmEngineClassicAdapter::drmAdpProvideKeyResponse(const std::string & response, std::string& keySetId)
    {
        return HI_SUCCESS;
    }

    HI_S32 DrmEngineClassicAdapter::drmAdpDecrypt(HI_BOOL secure, const uint8_t key[16], const uint8_t iv[16],
                                      const HI_DRM_PATTERN &pattern, HI_CRYPTO_MODE mode, HI_U8* pSrc,
                                      const HI_DRM_SUBSAMPLES *subSamples, HI_S32 numSubSamples,
                                      HI_VOID* pDst)
    {
        return HI_SUCCESS;
    }

    HI_S32 DrmEngineClassicAdapter::drmAdpGetPropertyString(const std::string &name, const std::string &value)
    {
        return HI_SUCCESS;
    }

    HI_S32 DrmEngineClassicAdapter::drmAdpSetPropertyString(const std::string &name, const std::string &value)
    {
        return HI_SUCCESS;
    }

    HI_S32 DrmEngineClassicAdapter::drmAdpSetListener(DrmListener* listener)
    {
        return HI_SUCCESS;
    }

}
