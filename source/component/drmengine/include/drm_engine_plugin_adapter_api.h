#ifndef DRM_ENGINE_PLUGIN_ADAPTER_API_H_
#define DRM_ENGINE_PLUGIN_ADAPTER_API_H_

#include <stdint.h>
#include <dirent.h>
#include <string.h>

#include "DrmDefines.h"

namespace drmengine {

const std::string kBaidu = "https://www.baidu.com";
const std::string kProvisioningServerUrl =
    "https://www.googleapis.com/"
    "certificateprovisioning/v1/devicecertificates/create"
    "?key=AIzaSyB-5OLKTx2iU5mko18DfdwK5611JIjbUhE";

const std::string kLicenseServerAppspot =
    "http://widevine-proxy.appspot.com/proxy";
const std::string kLicenseServerUat = "https://proxy.uat.widevine.com/proxy";

class DrmEnginePluginAdapterApi{

public:
    DrmEnginePluginAdapterApi(){}

    virtual ~DrmEnginePluginAdapterApi(){}

    virtual HI_BOOL drmAdpIsCryptoSchemeSupported(const HI_U8 uuid[16], const HI_CHAR* mimetype) = 0;

    virtual HI_S32 drmAdpOpenSession(void) = 0;

    virtual HI_S32 drmAdpCloseSession(void) = 0;

    virtual HI_S32 drmAdpGetKeyRequest(const std::string& initData, 
                                                const HI_U8* mimeType, 
                                                HI_DRM_KEY_TYPE keyType, 
                                                std::map < std::string, std::string > &optionalParameters, 
                                                HI_DRM_KEY_REQUEST *pKeyRequest) = 0;

    virtual HI_S32 drmAdpProvideKeyResponse(const std::string & response, std::string& keySetId) = 0;

    virtual HI_S32 drmAdpDecrypt(HI_BOOL secure, const uint8_t key[16], const uint8_t iv[16],
                                      const HI_DRM_PATTERN &pattern, HI_CRYPTO_MODE mode, HI_U8* pSrc,
                                      const HI_DRM_SUBSAMPLES *subSamples, HI_S32 numSubSamples,
                                      HI_VOID* pDst) = 0;

    virtual HI_S32 drmAdpGetPropertyString(const std::string &name, const std::string &value) = 0;

    virtual HI_S32 drmAdpSetPropertyString(const std::string &name, const std::string &value) = 0;

    virtual HI_S32 drmAdpSetListener(DrmListener* listener) = 0;

};

}

#endif
