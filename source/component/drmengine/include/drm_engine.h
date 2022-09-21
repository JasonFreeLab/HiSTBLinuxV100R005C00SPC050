#ifndef DRM_ENGINE_H_
#define DRM_ENGINE_H_

#include "drm_engine_api.h"
#include "drm_engine_adapter.h"

namespace drmengine {

class DrmEngine :public DrmEngineApi{
public:
    DrmEngine(const HI_U8 uuid[16], const HI_CHAR* mimetype, HI_PLUGIN_MODE pluginmode);

    ~DrmEngine();

    virtual HI_BOOL drmIsCryptoSchemeSupported(const HI_U8 uuid[16], const HI_CHAR* mimetype);

    virtual HI_S32 drmOpenSession(void);

    virtual HI_S32 drmCloseSession(void);

    virtual HI_S32 drmGetKeyRequest(const std::string& initData, 
                                                const HI_U8* mimeType, 
                                                HI_DRM_KEY_TYPE keyType, 
                                                std::map < std::string, std::string > &optionalParameters, 
                                                HI_DRM_KEY_REQUEST *pKeyRequest);

    virtual HI_S32 drmProvideKeyResponse(const std::string & response, std::string & keySetId);

    virtual HI_S32 drmDecrypt(HI_BOOL secure, const uint8_t key[16], const uint8_t iv[16],
                                      const HI_DRM_PATTERN &pattern, HI_CRYPTO_MODE mode, HI_U8* pSrc,
                                      const HI_DRM_SUBSAMPLES *subSamples, HI_S32 numSubSamples,
                                      HI_VOID* pDst);

    virtual HI_S32 drmGetPropertyString(const std::string &name, const std::string &value);

    virtual HI_S32 drmSetPropertyString(const std::string &name, const std::string &value);

    virtual HI_S32 drmSetListener(DrmListener* listener);
private:
    DrmEngineAdapter* m_pDrmEngineAdapter;

    DrmEngine(const DrmEngine& drmEngine);
    DrmEngine operator=(const DrmEngine& DrmEngine);
};

}

#endif