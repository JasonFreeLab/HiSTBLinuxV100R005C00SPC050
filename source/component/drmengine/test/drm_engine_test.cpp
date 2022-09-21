#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "drm_engine_api.h"
#include "DrmDefines.h"
#include "WVLog.h"
#include "drm_common_test.h"

using namespace testing;

namespace drmengine {

class DrmEngineTest;

typedef DrmEngineApi* (*DRM_CREATE)(const HI_U8 uuid[16], 
                                                          const HI_CHAR* mimeType, 
                                                          const HI_PLUGIN_MODE pluginMode,
                                                          HI_U32 mimeTypeLength, 
                                                          const HI_U8* initData,
                                                          DrmListener* listener,
                                                          HI_DRM_KEY_TYPE keyType,
                                                          std::map < std::string, std::string > &optionalParameters);

typedef HI_S32 (*DRM_DESTROY)(DrmEngineApi* &drmClient);

typedef HI_S32 (*DRM_DECRYPTO)(DrmEngineApi* drmClient,
                                                     HI_BOOL secure, HI_U8* key, HI_S32 keyLen,
                                                     HI_U8* iv, HI_S32 ivLen, HI_CRYPTO_MODE mode,
                                                     HI_CHAR* pSrc,HI_S32 s32srcSize,
                                                     HI_DRM_PATTERN pattern,
                                                     const HI_DRM_SUBSAMPLES* subSamples, HI_S32 numSubSamples,
                                                     HI_VOID *pDst);

DRM_CREATE DRM_Create_Func;
DRM_DESTROY DRM_Destroy_Func;
DRM_DECRYPTO DRM_Decrypto_Func;

DrmEngineTest* g_pDrmEngineTest = HI_NULL;
DrmEngineApi* g_pDrmEngineApi = HI_NULL;

class DrmEngineTest : public Test, public DrmListener{
public:
    DrmEngineTest() {}
    ~DrmEngineTest() {}

    MOCK_METHOD2(notify, HI_VOID(HI_DRM_EVENT_TYPE msg, HI_DRM_MSG_DATA* value));
private:
    virtual void SetUp(){
        LOGI_DRM("Enter SetUp!");
        g_pDrmEngineTest = this;
        /*
        const std::string libPath = kDrmEngineLibraryPath + kDrmEngineLibraryName;
        g_pDrmEngineLibHandle = new SharedLibrary(libPath);
        DRM_Create_Func = (DRM_CREATE)g_pDrmEngineLibHandle->lookup("DRM_Create");
        DRM_Destroy_Func = (DRM_DESTROY)g_pDrmEngineLibHandle->lookup("DRM_Destroy");
        DRM_Decrypto_Func = (DRM_DECRYPTO)g_pDrmEngineLibHandle->lookup("DRM_Decrypto");
        */
    }

    virtual void TearDown(){
        /*
        if(HI_NULL != g_pDrmEngineLibHandle)
        {
            delete g_pDrmEngineLibHandle;
            g_pDrmEngineLibHandle = HI_NULL;
        }
        */
        DrmEngineApi::DRM_Destroy(g_pDrmEngineApi);
        usleep(500*1000);
    }
};

TEST_F(DrmEngineTest, TestDrmCreate) {
    LOGI_DRM("Begin TestDrmCreate\n");
    LOGI_DRM("uuid = %s", kWidevineUUID);
    std::map < std::string, std::string > optionalParameter;
    const HI_U8* initData = (HI_U8*)kCencInitData.c_str();
    g_pDrmEngineApi = DrmEngineApi::DRM_Create(kWidevineUUID, "cenc", HI_PLUGIN_MODULAR, 0, initData,
                              this, HI_DRM_KEY_TYPE_STREAMING, optionalParameter);
}

TEST_F(DrmEngineTest, TestDrmDecrypter) {
    LOGI_DRM("Begin TestDrmDecrypter\n");
    LOGI_DRM("uuid = %s", kWidevineUUID);
    std::map < std::string, std::string > optionalParameter;
    const HI_U8* initData = (HI_U8*)kCencInitData.c_str();
    g_pDrmEngineApi = DrmEngineApi::DRM_Create(kWidevineUUID, "cenc", HI_PLUGIN_MODULAR, 0, initData,
                              this, HI_DRM_KEY_TYPE_STREAMING, optionalParameter);

    const HI_DRM_SUBSAMPLES kInputCensSubSamples(0, kInputCens.size());
    //kInputCensSubSamples.u32numBytesOfClearData = 0;
    //kInputCensSubSamples.u32numBytesOfEncryptedData = kInputCens.size();

    std::vector<uint8_t> output_buffer(kInputCens.size());
    //const HI_DRM_SUBSAMPLES* subSamples;

    DrmEngineApi::DRM_Decrypto(g_pDrmEngineApi, HI_FALSE, 
                                             const_cast<HI_U8*>(kKeyIdCtr.data()), 16, const_cast<HI_U8*>(kIvCens.data()), 
                                             16, HI_CRYPTO_MODE_AES_CTR, 
                                             const_cast<HI_U8*>(kInputCens.data()), kInputCens.size(), 
                                             kPatternRecommended, &kInputCensSubSamples, 
                                             1, &(output_buffer[0]));
}

}