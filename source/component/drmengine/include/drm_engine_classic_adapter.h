#ifndef DRM_ENGINE_CLASSIC_ADAPTER_H_
#define DRM_ENGINE_CLASSIC_ADAPTER_H_

#include "drm_engine_plugin_adapter_api.h"

namespace drmengine {

class DrmEngineClassicAdapter : public DrmEnginePluginAdapterApi {
public:
    DrmEngineClassicAdapter(const HI_CHAR* mimetype);

    ~DrmEngineClassicAdapter(void);

    virtual HI_BOOL drmAdpIsCryptoSchemeSupported(const HI_U8 uuid[16], const HI_CHAR* mimetype);

    virtual HI_S32 drmAdpOpenSession(void);

    virtual HI_S32 drmAdpCloseSession(void);

    virtual HI_S32 drmAdpGetKeyRequest(const std::string& initData, 
                                                const HI_U8* mimeType, 
                                                HI_DRM_KEY_TYPE keyType, 
                                                std::map < std::string, std::string > &optionalParameters, 
                                                HI_DRM_KEY_REQUEST *pKeyRequest);

    virtual HI_S32 drmAdpProvideKeyResponse(const std::string & response, std::string& keySetId);

    virtual HI_S32 drmAdpDecrypt(HI_BOOL secure, const uint8_t key[16], const uint8_t iv[16],
                                      const HI_DRM_PATTERN &pattern, HI_CRYPTO_MODE mode, HI_U8* pSrc,
                                      const HI_DRM_SUBSAMPLES *subSamples, HI_S32 numSubSamples,
                                      HI_VOID* pDst);

    virtual HI_S32 drmAdpGetPropertyString(const std::string &name, const std::string &value);

    virtual HI_S32 drmAdpSetPropertyString(const std::string &name, const std::string &value);

    virtual HI_S32 drmAdpSetListener(DrmListener* listener);

private:

    DrmEngineClassicAdapter(const DrmEngineClassicAdapter& drmEngineClassicAdapter);
    DrmEngineClassicAdapter operator=(const DrmEngineClassicAdapter& drmEngineClassicAdapter);

};

}

#endif
