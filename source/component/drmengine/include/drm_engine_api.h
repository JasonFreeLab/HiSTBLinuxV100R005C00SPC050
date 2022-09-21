#ifndef DRM_ENGINE_API_H_
#define DRM_ENGINE_API_H_

#include <stdint.h>

#include "hi_type.h"    //from common/include
#include "DrmDefines.h"

namespace drmengine {

class DrmEngineApi {

public:
    DrmEngineApi(){}

    virtual ~DrmEngineApi(){}

    static DrmEngineApi* DRM_Create(const HI_U8 uuid[16], 
                                                          const HI_CHAR* mimeType, 
                                                          const HI_PLUGIN_MODE pluginMode,
                                                          HI_U32 mimeTypeLength, 
                                                          const std::string& initData,
                                                          DrmListener* listener,
                                                          HI_DRM_KEY_TYPE keyType,
                                                          std::map < std::string, std::string > &optionalParameters);

    static HI_S32 DRM_Destroy(DrmEngineApi* &drmClient);

    static HI_S32 DRM_Decrypto(DrmEngineApi* drmClient,
                                                     HI_BOOL secure, HI_U8* key, HI_S32 keyLen,
                                                     HI_U8* iv, HI_S32 ivLen, HI_CRYPTO_MODE mode,
                                                     HI_U8* pSrc,HI_S32 s32srcSize,
                                                     HI_DRM_PATTERN pattern,
                                                     const HI_DRM_SUBSAMPLES* subSamples, HI_S32 numSubSamples,
                                                     HI_VOID *pDst);

    virtual HI_BOOL drmIsCryptoSchemeSupported(const HI_U8 uuid[16], const HI_CHAR* mimetype) = 0;

    virtual HI_S32 drmOpenSession(void) = 0;

    virtual HI_S32 drmCloseSession(void) = 0;

    virtual HI_S32 drmGetKeyRequest(const std::string& initData, 
                                                const HI_U8* mimeType, 
                                                HI_DRM_KEY_TYPE keyType, 
                                                std::map < std::string, std::string > &optionalParameters, 
                                                HI_DRM_KEY_REQUEST *pKeyRequest) = 0;

    virtual HI_S32 drmProvideKeyResponse(const std::string & response, std::string &keySetId) = 0;

    virtual HI_S32 drmDecrypt(HI_BOOL secure, const uint8_t key[16], const uint8_t iv[16],
                                      const HI_DRM_PATTERN &pattern, HI_CRYPTO_MODE mode, HI_U8* pSrc,
                                      const HI_DRM_SUBSAMPLES *subSamples, HI_S32 numSubSamples,
                                      HI_VOID* pDst) = 0;

    virtual HI_S32 drmGetPropertyString(const std::string &name, const std::string &value) = 0;

    virtual HI_S32 drmSetPropertyString(const std::string &name, const std::string &value) = 0;

    virtual HI_S32 drmSetListener(DrmListener* listener) = 0;

};

}
#endif
