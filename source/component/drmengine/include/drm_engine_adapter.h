#ifndef DRM_ENGINE_ADAPTER_H_
#define DRM_ENGINE_ADAPTER_H_

#include "drm_engine_plugin_adapter_api.h"
#include "DrmDefines.h"

namespace drmengine {

class DrmEngineAdapter {
public:
    DrmEngineAdapter(const HI_U8 uuid[16]);

    DrmEngineAdapter(const HI_CHAR* mimetype);

    ~DrmEngineAdapter();

    HI_BOOL drmIsCryptoSchemeSupported(const HI_U8 uuid[16], const HI_CHAR* mimetype);

    HI_S32 drmOpenSession(void);

    HI_S32 drmCloseSession(void);

    HI_S32 drmGetKeyRequest(const std::string& initData, 
                                                const HI_U8* mimeType, 
                                                HI_DRM_KEY_TYPE keyType, 
                                                std::map < std::string, std::string > &optionalParameters, 
                                                HI_DRM_KEY_REQUEST *pKeyRequest);

    HI_S32 drmProvideKeyResponse(const std::string & response, std::string& keySetId);

    HI_S32 drmDecrypt(HI_BOOL secure, const uint8_t key[16], const uint8_t iv[16],
                                      const HI_DRM_PATTERN &pattern, HI_CRYPTO_MODE mode, HI_U8* pSrc,
                                      const HI_DRM_SUBSAMPLES *subSamples, HI_S32 numSubSamples,
                                      HI_VOID* pDst);

    HI_S32 drmGetPropertyString(const std::string &name, const std::string &value);

    HI_S32 drmSetPropertyString(const std::string &name, const std::string &value);

    HI_S32 drmSetListener(DrmListener* listener);

private:
    DrmEnginePluginAdapterApi* m_pDrmEnginePluginAdapterApi;

    DrmEngineAdapter(const DrmEngineAdapter& drmEngineAdapter);
    DrmEngineAdapter operator=(const DrmEngineAdapter& drmEngineAdapter);
};

}

#endif
