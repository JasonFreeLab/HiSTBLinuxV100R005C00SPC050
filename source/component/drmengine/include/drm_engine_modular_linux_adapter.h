#ifndef DRM_ENGINE_MODULAR_LINUX_ADAPTER_H_
#define DRM_ENGINE_MODULAR_LINUX_ADAPTER_H_

#include "drm_engine_plugin_adapter_api.h"
#include "DrmDefines.h"
#include "DrmAPI.h"
#include "CryptoAPI.h"
#include "SharedLibrary.h"

#define UUID_SIZE (16)

namespace drmengine {

class DrmEngineModularLinuxAdapter : public DrmEnginePluginAdapterApi, public DrmPluginListener{
public:
    DrmEngineModularLinuxAdapter(const HI_U8 uuid[16]);

    ~DrmEngineModularLinuxAdapter(void);

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

    virtual void sendEvent(DrmPlugin::EventType eventType, int extra,
                               Vector<HI_U8> const& sessionId,
                               Vector<HI_U8> const& data);

    virtual void sendExpirationUpdate(Vector<HI_U8> const& sessionId,
                                          int64_t expiryTimeInMS);

    virtual void sendKeysChange(Vector<HI_U8> const& sessionId,
                                    std::list<DrmPlugin::KeyStatus> keyStatusList,
                                    bool hasNewUsableKey);

    virtual void sendDeferredComplete(Vector<HI_U8> const& sessionId, status_t sessionStatus);

    HI_S32 createDrmPlugin(const HI_U8 uuid[16]);

    HI_S32 createCryptoPlugin(const HI_U8 uuid[16]);

    HI_S32 destroyDrmPlugin();

    HI_S32 destroyCryptoPlugin();

    HI_BOOL findFactoryForScheme(const HI_U8 uuid[16]);

    HI_BOOL loadLibraryForScheme(const std::string strPath, const HI_U8 uuid[16]);

    HI_VOID closeFactory();

    HI_DRM_KEYSTATUS_TYPE transKeyStatus(DrmPlugin::KeyStatusType keyStatus);

    HI_S32 fetchLicAndProKeyRes(const std::string sessionId, const std::string request);

    HI_S32 fetchProvisionAndProKeyRes(const std::string sessionId, const std::string request);

    HI_S32 fetchLicense(const std::string url, const std::string request, std::string* response);

private:
    DrmListener* m_pListener;
    DrmFactory* m_pDrmFactory;
    DrmPlugin* m_pDrmPlugin;
    CryptoFactory* m_pCryptoFactory;
    CryptoPlugin* m_pCryptoPlugin;
    Vector<HI_U8> m_strSessionId;
    SharedLibrary* m_pSharedLibrary;
    std::string m_strKeySetId;
    HI_DRM_MSG_DATA m_stMsgData;
    HI_U8 m_Uuid[UUID_SIZE];

    DrmEngineModularLinuxAdapter(const DrmEngineModularLinuxAdapter& drmEngineModularLinuxAdapter);
    DrmEngineModularLinuxAdapter operator=(const DrmEngineModularLinuxAdapter& drmEngineModularLinuxAdapter);

};

}

#endif
