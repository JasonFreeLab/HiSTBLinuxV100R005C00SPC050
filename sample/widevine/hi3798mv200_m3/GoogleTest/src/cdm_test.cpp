// Copyright 2015 Google Inc. All Rights Reserved.
//
// This source file provides a basic set of unit tests for the Content
// Decryption Module (CDM).

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "cdm.h"
#include "cdm_test_printers.h"
#include "license_request.h"
#include "log.h"
#include "OEMCryptoCENC.h"
#include "override.h"
#include "properties_ce.h"
#include "scoped_ptr.h"
#include "string_conversions.h"
#include "test_host.h"
#include "url_request.h"

using namespace testing;
using namespace wvcdm;

namespace widevine {

namespace {

const int kHttpOk = 200;

const int kRenewalTestDelayMs = 3 * 60 * 1000;
const int kExpirationTestDelayMs = 5 * 60 * 1000;

const Cdm::SessionType kBogusSessionType = static_cast<Cdm::SessionType>(-1);
const Cdm::InitDataType kBogusInitDataType = static_cast<Cdm::InitDataType>(-1);
const std::string kBogusSessionId = "asdf";

const std::string kDefaultServerCertificate = a2bs_hex(
    "0ABF020803121028703454C008F63618ADE7443DB6C4C8188BE7F99005228E023082010A02"
    "82010100B52112B8D05D023FCC5D95E2C251C1C649B4177CD8D2BEEF355BB06743DE661E3D"
    "2ABC3182B79946D55FDC08DFE95407815E9A6274B322A2C7F5E067BB5F0AC07A89D45AEA94"
    "B2516F075B66EF811D0D26E1B9A6B894F2B9857962AA171C4F66630D3E4C602718897F5E1E"
    "F9B6AAF5AD4DBA2A7E14176DF134A1D3185B5A218AC05A4C41F081EFFF80A3A040C50B09BB"
    "C740EEDCD8F14D675A91980F92CA7DDC646A06ADAD5101F74A0E498CC01F00532BAC217850"
    "BD905E90923656B7DFEFEF42486767F33EF6283D4F4254AB72589390BEE55808F1D668080D"
    "45D893C2BCA2F74D60A0C0D0A0993CEF01604703334C3638139486BC9DAF24FD67A07F9AD9"
    "4302030100013A1273746167696E672E676F6F676C652E636F6D128003983E30352675F40B"
    "A715FC249BDAE5D4AC7249A2666521E43655739529721FF880E0AAEFC5E27BC980DAEADABF"
    "3FC386D084A02C82537848CC753FF497B011A7DA97788A00E2AA6B84CD7D71C07A48EBF616"
    "02CCA5A3F32030A7295C30DA915B91DC18B9BC9593B8DE8BB50F0DEDC12938B8E9E039CDDE"
    "18FA82E81BB032630FE955D85A566CE154300BF6D4C1BD126966356B287D657B18CE63D0EF"
    "D45FC5269E97EAB11CB563E55643B26FF49F109C2101AFCAF35B832F288F0D9D45960E259E"
    "85FB5D24DBD2CF82764C5DD9BF727EFBE9C861F869321F6ADE18905F4D92F9A6DA6536DB84"
    "75871D168E870BB2303CF70C6E9784C93D2DE845AD8262BE7E0D4E2E4A0759CEF82D109D25"
    "92C72429F8C01742BAE2B3DECADBC33C3E5F4BAF5E16ECB74EADBAFCB7C6705F7A9E3B6F39"
    "40383F9C5116D202A20C9229EE969C2519718303B50D0130C3352E06B014D838540F8A0C22"
    "7C0011E0F5B38E4E298ED2CB301EB4564965F55C5D79757A250A4EB9C84AB3E6539F6B6FDF"
    "56899EA29914");

const std::string kProvisioningServerUrl =
    "https://www.googleapis.com/"
    "certificateprovisioning/v1/devicecertificates/create"
    "?key=AIzaSyB-5OLKTx2iU5mko18DfdwK5611JIjbUhE";

const std::string kLicenseServerAppspot =
    "http://widevine-proxy.appspot.com/proxy";
const std::string kLicenseServerUat = "https://proxy.uat.widevine.com/proxy";

const std::string kCencInitData = a2bs_hex(
    "00000042"                          // blob size
    "70737368"                          // "pssh"
    "00000000"                          // flags
    "edef8ba979d64acea3c827dcd51d21ed"  // Widevine system id
    "00000022"                          // pssh data size
    // pssh data:
    "08011a0d7769646576696e655f746573"
    "74220f73747265616d696e675f636c69"
    "7031");
const std::string kCencPersistentInitData = a2bs_hex(
    "00000040"                          // blob size
    "70737368"                          // "pssh"
    "00000000"                          // flags
    "edef8ba979d64acea3c827dcd51d21ed"  // Widevine system id
    "00000020"                          // pssh data size
    // pssh data:
    "08011a0d7769646576696e655f746573"
    "74220d6f66666c696e655f636c697032");
const std::string kInvalidCencInitData = a2bs_hex(
    "0000000c"                          // blob size
    "61736466"                          // "asdf" (wrong box type)
    "01020304");                        // nonsense
const std::string kNonWidevineCencInitData = a2bs_hex(
    "00000020"                          // blob size
    "70737368"                          // "pssh"
    "00000000"                          // flags
    "000102030405060708090a0b0c0d0e0f"  // unknown system id
    "00000000");                        // pssh data size
const std::string kWebMInitData = a2bs_hex("deadbeefdeadbeefdeadbeefdeadbeef");
const std::string kKeyIdsInitData =
    "{\"kids\":[\"67ef0gd8pvfd0\",\"77ef0gd8pvfd0\"]}";
const std::string kHlsInitData =
    "#EXT-X-KEY:METHOD=SAMPLE-AES,KEYFORMAT=\"com.widevine\",KEYFORMATVERSIONS="
    "\"1\",URI=\"data:text/plain;base64,ew0KICAgInByb3ZpZGVyIjogIndpZGV2aW5lX3R"
    "lc3QiLA0KICAgImNvbnRlbnRfaWQiOiAiWW1sblluVmphMkoxYm01NSIsDQogICAia2V5X2lkc"
    "yI6IFsNCiAgICAgICI5Yjc1OTA0MDMyMWE0MDhhNWM3NzY4YjQ1MTEyODdhNiINCiAgIF0NCn0"
    "=\",IV=0x75537a79fa41abc7b598ea72aba0c26f";

// This Key ID must match the key retrieved from kLicenseServerAppspot by
// kCencInitData.
const std::vector<uint8_t> kKeyIdCtr = a2b_hex(
    "371ea35e1a985d75d198a7f41020dc23");
// This Key ID must match the key retrieved from kLicenseServerUat by
// kHlsInitData.
const std::vector<uint8_t> kKeyIdCbc = a2b_hex(
    "9b759040321a408a5c7768b4511287a6");

// A default pattern object disables patterns during decryption.
const Cdm::Pattern kPatternNone;
// The recommended pattern from CENC 3.0, which is also the pattern used by
// HLS. Encrypts 1 in every 10 crypto blocks.
const Cdm::Pattern kPatternRecommended(1, 9);
// The recommended pattern for HLS Audio, which should be decrypted in CENC 3.0
// cbcs mode despite not using patterns.  This pattern disables patterned
// decryption by having one encrypted block and no clear blocks.
const Cdm::Pattern kPatternHlsAudio(1, 0);

// Dummy encrypted data using the CENC 3.0 "cenc" mode.  Encrypted using the
// key matching kKeyIdCtr.
const std::vector<uint8_t> kInputCenc = a2b_hex(
    "64ab17b3e3dfab47245c7cce4543d4fc7a26dcf248f19f9b59f3c92601440b36"
    "17c8ed0c96c656549e461f38708cd47a434066f8df28ccc28b79252eee3f9c2d"
    "7f6c68ebe40141fe818fe082ca523c03d69ddaf183a93c022327fedc5582c5ab"
    "ca9d342b71263a67f9cb2336f12108aaaef464f17177e44e9b0c4e56e61da53c"
    "2150b4405cc82d994dfd9bf4087c761956d6688a9705db4cf350381085f383c4"
    "9666d4aed135c519c1f0b5cba06e287feea96ea367bf54e7368dcf998276c6e4"
    "6497e0c50e20fef74e42cb518fe7f22ef27202428688f86404e8278587017012"
    "c1d65537c6cbd7dde04aae338d68115a9f430afc100ab83cdadf45dca39db685");
const std::vector<uint8_t> kIvCenc = a2b_hex(
    "f6f4b1e600a5b67813ed2bded913ba9f");
const std::vector<uint8_t> kOutputCenc = a2b_hex(
    "217ce9bde99bd91e9733a1a00b9b557ac3a433dc92633546156817fae26b6e1c"
    "942ac20a89ff79f4c2f25fba99d6a44618a8c0420b27d54e3da17b77c9d43cca"
    "595d259a1e4a8b6d7744cd98c5d3f921adc252eb7d8af6b916044b676a574747"
    "8df21fdc42f166880d97a2225cd5c9ea5e7b752f4cf81bbdbe98e542ee10e1c6"
    "ad868a6ac55c10d564fc23b8acff407daaf4ed2743520e02cda9680d9ea88e91"
    "029359c4cf5906b6ab5bf60fbb3f1a1c7c59acfc7e4fb4ad8e623c04d503a3dd"
    "4884604c8da8a53ce33db9ff8f1c5bb6bb97f37b39906bf41596555c1bcce9ed"
    "08a899cd760ff0899a1170c2f224b9c52997a0785b7fe170805fd3e8b1127659");

// Dummy encrypted data using the CENC 3.0 "cens" mode.  Encrypted using the
// key matching kKeyIdCtr.
const std::vector<uint8_t> kInputCens = a2b_hex(
    "1660a777a301908b5e8c15b465ed7fa434793f65a8be816278f9479d741a78e0"
    "b245e17629d63bbc2b15a5fa98b21daf62bdaf054113604ef19311adc5c3b74c"
    "6167dc3160f27c4920d2f9ae4a7f8dfd029dde48bce29b2751f27f12503d369d"
    "0ceb8b347e2884f51715f612badf15934aaa39db886e749afb8d8bdd29a18dd6"
    "2b0c4355935c4dcc5ec0153307154ace5bfedcdaa2b670052660889f3d64c4b3"
    "e363b16dc312d7e20373e873c760fae8b8bb39eccb6fe16e0198f6818ba24c30"
    "39dec55ef91ddc47c320ec284e24d1c8cdd62515e8ce5c0cb01bea2fbf36ce99"
    "246f5f8a2aca37719524dadffd4926a75a06402779a945d0b2c14a9c3f060a34");
const std::vector<uint8_t> kIvCens = a2b_hex(
    "a891b8000af53049d7b24bdc19074839");
const std::vector<uint8_t> kOutputCens = a2b_hex(
    "4bc4abcd79205e54188f04f99ea7e02534793f65a8be816278f9479d741a78e0"
    "b245e17629d63bbc2b15a5fa98b21daf62bdaf054113604ef19311adc5c3b74c"
    "6167dc3160f27c4920d2f9ae4a7f8dfd029dde48bce29b2751f27f12503d369d"
    "0ceb8b347e2884f51715f612badf15934aaa39db886e749afb8d8bdd29a18dd6"
    "2b0c4355935c4dcc5ec0153307154ace5bfedcdaa2b670052660889f3d64c4b3"
    "f6104e15275ecb58324fb8f25ccde60db8bb39eccb6fe16e0198f6818ba24c30"
    "39dec55ef91ddc47c320ec284e24d1c8cdd62515e8ce5c0cb01bea2fbf36ce99"
    "246f5f8a2aca37719524dadffd4926a75a06402779a945d0b2c14a9c3f060a34");

// Dummy encrypted data using the CENC 3.0 "cbc1" mode.  Encrypted using the
// key matching kKeyIdCbc.
const std::vector<uint8_t> kInputCbc1 = a2b_hex(
    "a69c76294ccd7e709fc3d11b1e0ccd4a74c9ffa8ce31ab92437c4da03b85822d"
    "6f0da6d7935121cd585950ecc61efc83d2d86be9c32b3091cf546de987d9b480"
    "fae8b8c35222f6fb7e2939b1af4c1445b6bd3ac22aeafc06ec016b011d465bf0"
    "9d9a3a18865518bca314b1208830f0a18e6922b1d0a451df8f2c09efb416ca1d"
    "0bdf93a7610f40da65fd23fc65531bb01373a85658043ed238e79d2b3f3c49e7"
    "842ea0488a862932850153849f5ac20ce8181594240d16bb309d7523ffb9a7f0"
    "edd976a6dcb0c90bf6895dad90b8f373b22162c397b0d0e3e49041dce4f7a34f"
    "1dbe1e2c0f3f6be9d5bbc3e783743a70df89bf488de8dd97106c7fb9fdbbf662");
const std::vector<uint8_t> kIvCbc1 = a2b_hex(
    "0111321322793b04f871aab28f6b066e");
const std::vector<uint8_t> kOutputCbc1 = a2b_hex(
    "d5c7a71abfbfa2b490916d0e316c7b7e928b2cdaf9768b682b98f4087d664faa"
    "c8f05bd97fede1c678dc4320df4ac65674ad63370616df3ee85acc145b4bc7a8"
    "9169214197489350faa658ddff36959cf8dc2328bca5b1ccf26da4e1ce717595"
    "a11ddf354a9811890afbb2207e90367bf007df42d99c682e6024cf7671273523"
    "06d3e68a0fa2914640842759911bfdf90be7fc84742031989bb0b676d93a1904"
    "4ba6811a032ddafd9e2d2caa44ec17363794b661d2460aa4517b1e349f0eeb23"
    "9c2e83d31584f56a31b1688f89a4c64917e0037ae6aa7e483cd641dec38c3aba"
    "195ca7942df98c124d4be96524edbda671aab2a52a2305637101f274e031bbc7");

// Dummy encrypted data using the CENC 3.0 "cbcs" mode.  Encrypted using the
// key matching kKeyIdCbc.
const std::vector<uint8_t> kInputCbcs = a2b_hex(
    "7d8665445b3ac25fda29054e81626ed89f528f87315bdb07ba7fdad32835808f"
    "6458893d28a247c37ec56c48f89ba6f941757edf22fea1b69980833746526dba"
    "a8e9193125a4ac73893df76784aeb954124c59aa9771e5e5f91478ed720d2cfe"
    "7421c5f7acbdfb762e75da0b48ba3f7bbf1dda3e8ff8ad1b625622438c100bd7"
    "a063a0518b21bcbc6ebc2809478ebfd612e3400b515018b64fc1ba23c5b38b6d"
    "45aaa4c0c394c3b75066390b646bf273fc4913f7e20b8c856d20561337fd4383"
    "86938f189e0354ee9425974fc7153e61e006c3b472f21e2f3e33a1c94435d747"
    "da153cd7f0cb8a7e4d1ee43acbf51027604cfe93808b42a2b6f30b4667d056e4");
const std::vector<uint8_t> kIvCbcs = a2b_hex(
    "8e261c9660f5930ebe1734510cb9bc23");
const std::vector<uint8_t> kOutputCbcs = a2b_hex(
    "bf7d1e9edc64a1782e884870edde98399f528f87315bdb07ba7fdad32835808f"
    "6458893d28a247c37ec56c48f89ba6f941757edf22fea1b69980833746526dba"
    "a8e9193125a4ac73893df76784aeb954124c59aa9771e5e5f91478ed720d2cfe"
    "7421c5f7acbdfb762e75da0b48ba3f7bbf1dda3e8ff8ad1b625622438c100bd7"
    "a063a0518b21bcbc6ebc2809478ebfd612e3400b515018b64fc1ba23c5b38b6d"
    "d48cfbfc9e08ff501c62d5e85200dab0fc4913f7e20b8c856d20561337fd4383"
    "86938f189e0354ee9425974fc7153e61e006c3b472f21e2f3e33a1c94435d747"
    "da153cd7f0cb8a7e4d1ee43acbf51027604cfe93808b42a2b6f30b4667d056e4");

const std::string kValue = "A Value";
const std::string kNewValue = "A New Value";

const std::string kParamName = "PARAM";
const std::string kParamName2 = "PARAM2";


class CdmTest : public Test, public Cdm::IEventListener {
 public:
  CdmTest() {}
  virtual ~CdmTest() {}

  // IEventListener mocks:
  MOCK_METHOD3(onMessage,
      void(const std::string& session_id,
           Cdm::MessageType message_type,
           const std::string& message));
  MOCK_METHOD1(onKeyStatusesChange,
      void(const std::string& session_id));
  MOCK_METHOD1(onRemoveComplete,
      void(const std::string& session_id));
  MOCK_METHOD2(onDeferredComplete,
      void(const std::string& session_id, Cdm::Status error_code));
  MOCK_METHOD2(onDirectIndividualizationRequest,
      void(const std::string& session_id,
           const std::string& message));

 protected:
  virtual void SetUp() OVERRIDE {
    // Clear anything stored, load default device cert.
    g_host->Reset();

    // Clear anything stored by OEMCrypto.
    ASSERT_EQ(OEMCrypto_SUCCESS, OEMCrypto_Initialize());
    int result = OEMCrypto_DeleteUsageTable();
    // Don't fault OEMCrypto implementations without usage tables:
    if (result != OEMCrypto_ERROR_NOT_IMPLEMENTED) {
      EXPECT_EQ(OEMCrypto_SUCCESS, result);
    }
#if 1
    int result_my = OEMCrypto_UpdateUsageTable();
    EXPECT_EQ(OEMCrypto_SUCCESS, result);
#endif
    ASSERT_EQ(OEMCrypto_SUCCESS, OEMCrypto_Terminate());

    // Reinit the library.
    Cdm::Status status = Cdm::initialize(
        Cdm::kNoSecureOutput, PropertiesCE::GetClientInfo(),
        g_host, g_host, g_host, static_cast<Cdm::LogLevel>(g_cutoff));
    ASSERT_EQ(Cdm::kSuccess, status);

    // Make a fresh CDM.
    RecreateCdm(true /* privacy_mode */);
    SetDefaultServerCertificate();
  }

  virtual void TearDown() OVERRIDE {
    // So the OEMCrypto nonce flood check does not trigger.
    // A 500ms delay allows up to 10 nonces to be generated per test without
    // triggering an OEMCrypto error.
    usleep(500 * 1000);
  }

  void RecreateCdm(bool privacy_mode) {
    CreateAdditionalCdm(privacy_mode, &cdm_);
  }

  void CreateAdditionalCdm(bool privacy_mode, scoped_ptr<Cdm>* cdm) {
    cdm->reset(Cdm::create(this, NULL, privacy_mode));
    ASSERT_NE((Cdm*)0, cdm->get());
  }

  void SetDefaultServerCertificate() {
    // Set the default server certificate.
    Cdm::Status status = cdm_->setServerCertificate(kDefaultServerCertificate);
    ASSERT_EQ(Cdm::kSuccess, status);
  }

  bool Fetch(const std::string& url,
             const std::string& message,
             std::string* response,
             int* status_code) {
    UrlRequest url_request(url);
    EXPECT_TRUE(url_request.is_connected());
    if (!url_request.is_connected()) {
      return false;
    }

    url_request.PostRequest(message);
    std::string http_response;
    url_request.GetResponse(&http_response);

    // Some license servers return 400 for invalid message, some
    // return 500; treat anything other than 200 as an invalid message.
    int http_status_code = url_request.GetStatusCode(http_response);
    if (status_code) {
      *status_code = http_status_code;
    }

    if (response) {
      if (http_status_code == kHttpOk) {
        // Parse out HTTP and server headers and return the body only.
        std::string reply_body;
        LicenseRequest lic_request;
        lic_request.GetDrmMessage(http_response, reply_body);
        *response = reply_body;
      } else {
        *response = http_response;
      }
      LOGV("Reply body: %s", b2a_hex(*response).c_str());
    }
    return true;
  }

  void FetchCertificate(const std::string& url,
                        std::string* response) {
    int status_code;
    bool ok = Fetch(url, "", response, &status_code);
    ASSERT_TRUE(ok);
    if (ok) ASSERT_EQ(kHttpOk, status_code);
  }

  void FetchLicense(const std::string& license_server,
                    const std::string& message,
                    std::string* response) {
    int status_code;
    bool ok = Fetch(license_server, message, response, &status_code);
    ASSERT_TRUE(ok);
    if (ok) ASSERT_EQ(kHttpOk, status_code);
  }

  void FetchLicenseFailure(const std::string& message,
                           int expected_status_code) {
    int status_code;
    bool ok = Fetch(kLicenseServerAppspot, message, NULL, &status_code);
    ASSERT_TRUE(ok);
    if (ok) ASSERT_EQ(expected_status_code, status_code);
  }

  void CreateSessionAndGenerateRequest(Cdm::SessionType session_type,
                                       Cdm::InitDataType init_data_type,
                                       std::string* session_id,
                                       std::string* message) {
    Cdm::Status status = cdm_->createSession(session_type, session_id);
    ASSERT_EQ(Cdm::kSuccess, status);

    std::string init_data;
    if (session_type == Cdm::kTemporary) {
      if (init_data_type == Cdm::kCenc) {
        init_data = kCencInitData;
      } else if (init_data_type == Cdm::kHls) {
        init_data = kHlsInitData;
      }
    } else if (session_type == Cdm::kPersistentLicense ||
        session_type == Cdm::kPersistentUsageRecord) {
      if (init_data_type == Cdm::kCenc) {
        init_data = kCencPersistentInitData;
      }
    }
    ASSERT_FALSE(init_data.empty());

    EXPECT_CALL(*this, onMessage(*session_id, Cdm::kLicenseRequest, _)).
        WillOnce(SaveArg<2>(message));
    status = cdm_->generateRequest(*session_id, init_data_type, init_data);
    ASSERT_EQ(Cdm::kSuccess, status);
    Mock::VerifyAndClear(this);
  }

  void CreateSessionAndFetchLicense(Cdm::SessionType session_type,
                                    Cdm::InitDataType init_data_type,
                                    std::string* session_id,
                                    std::string* response) {
    std::string message;
    ASSERT_NO_FATAL_FAILURE(CreateSessionAndGenerateRequest(
        session_type, init_data_type, session_id, &message));

    std::string license_server;
    if (init_data_type == Cdm::kCenc) {
      license_server = kLicenseServerAppspot;
    } else if (init_data_type == Cdm::kHls) {
      license_server = kLicenseServerUat;
    }
    ASSERT_FALSE(license_server.empty());
    FetchLicense(license_server, message, response);
  }

  void CreateSessionAndUpdate(Cdm::SessionType session_type,
                              Cdm::InitDataType init_data_type,
                              std::string* session_id) {
    std::string response;
    ASSERT_NO_FATAL_FAILURE(CreateSessionAndFetchLicense(
        session_type, init_data_type, session_id, &response));
    EXPECT_CALL(*this, onKeyStatusesChange(*session_id));
    Cdm::Status status = cdm_->update(*session_id, response);
    ASSERT_EQ(Cdm::kSuccess, status);
    Mock::VerifyAndClear(this);
  }

  void FetchLicenseAndUpdate(const std::string& session_id,
                             const std::string& message) {
    // Acquire a license.
    std::string response;
    ASSERT_NO_FATAL_FAILURE(FetchLicense(
        kLicenseServerAppspot, message, &response));

    // This license should be accepted, but the keys are not expected to change.
    EXPECT_CALL(*this, onKeyStatusesChange(session_id)).Times(0);
    Cdm::Status status = cdm_->update(session_id, response);
    ASSERT_EQ(Cdm::kSuccess, status);
    Mock::VerifyAndClear(this);
  }

  scoped_ptr<Cdm> cdm_;
};


struct DecryptParam {
 public:
  DecryptParam(
      const std::string& short_name_param,
      Cdm::InitDataType init_data_type_param,
      const std::vector<uint8_t>& key_id_param,
      const std::vector<uint8_t>& iv_param,
      Cdm::EncryptionScheme scheme_param,
      const Cdm::Pattern& pattern_param,
      const std::vector<uint8_t>& input_param,
      const std::vector<uint8_t>& output_param)
      : short_name(short_name_param),
        init_data_type(init_data_type_param),
        key_id(&key_id_param),
        iv(&iv_param),
        scheme(scheme_param),
        pattern(&pattern_param),
        input(&input_param),
        output(&output_param) {}

  const std::string short_name;
  const Cdm::InitDataType init_data_type;
  const std::vector<uint8_t>* const key_id;
  const std::vector<uint8_t>* const iv;
  const Cdm::EncryptionScheme scheme;
  const Cdm::Pattern* const pattern;
  const std::vector<uint8_t>* const input;
  const std::vector<uint8_t>* const output;
};

void PrintTo(const DecryptParam& value, ::std::ostream* os) {
  *os << value.short_name << " DecryptParam";
}

class CdmTestWithDecryptParam : public CdmTest,
    public WithParamInterface<DecryptParam> {};


class MockTimerClient : public Cdm::ITimer::IClient {
 public:
  MockTimerClient() {}
  virtual ~MockTimerClient() {}

  MOCK_METHOD1(onTimerExpired, void(void*));
};

}  // namespace


TEST_F(CdmTest, TestHostTimer) {
  // Validate that the TestHost timers are processed in the correct order.
  const int64_t kTimerDelayMs = 1000;
  void* kCtx1 = reinterpret_cast<void*>(0x1);
  void* kCtx2 = reinterpret_cast<void*>(0x2);

  MockTimerClient client;

  g_host->setTimeout(kTimerDelayMs * 1, &client, kCtx1);
  g_host->setTimeout(kTimerDelayMs * 2, &client, kCtx2);

  EXPECT_CALL(client, onTimerExpired(kCtx1));
  g_host->ElapseTime(kTimerDelayMs);
  Mock::VerifyAndClear(&client);

  EXPECT_CALL(client, onTimerExpired(kCtx2));
  g_host->ElapseTime(kTimerDelayMs);
  Mock::VerifyAndClear(&client);

  EXPECT_CALL(client, onTimerExpired(_)).Times(0);
  g_host->ElapseTime(kTimerDelayMs);
  Mock::VerifyAndClear(&client);
}

TEST_F(CdmTest, Initialize) {
  Cdm::Status status;

  // Try with an invalid output type.
  status = Cdm::initialize(
      static_cast<Cdm::SecureOutputType>(-1), PropertiesCE::GetClientInfo(),
      g_host, g_host, g_host, static_cast<Cdm::LogLevel>(g_cutoff));
  EXPECT_EQ(Cdm::kTypeError, status);

  // Try with various client info properties missing.
  Cdm::ClientInfo working_client_info = PropertiesCE::GetClientInfo();
  Cdm::ClientInfo broken_client_info;

  broken_client_info = working_client_info;
  broken_client_info.product_name.clear();
  status = Cdm::initialize(
      Cdm::kNoSecureOutput, broken_client_info,
      g_host, g_host, g_host, static_cast<Cdm::LogLevel>(g_cutoff));
  EXPECT_EQ(Cdm::kTypeError, status);

  broken_client_info = working_client_info;
  broken_client_info.company_name.clear();
  status = Cdm::initialize(
      Cdm::kNoSecureOutput, broken_client_info,
      g_host, g_host, g_host, static_cast<Cdm::LogLevel>(g_cutoff));
  EXPECT_EQ(Cdm::kTypeError, status);

  broken_client_info = working_client_info;
  broken_client_info.device_name.clear();  // Not required
  status = Cdm::initialize(
      Cdm::kNoSecureOutput, broken_client_info,
      g_host, g_host, g_host, static_cast<Cdm::LogLevel>(g_cutoff));
  EXPECT_EQ(Cdm::kSuccess, status);

  broken_client_info = working_client_info;
  broken_client_info.model_name.clear();
  status = Cdm::initialize(
      Cdm::kNoSecureOutput, broken_client_info,
      g_host, g_host, g_host, static_cast<Cdm::LogLevel>(g_cutoff));
  EXPECT_EQ(Cdm::kTypeError, status);

  broken_client_info = working_client_info;
  broken_client_info.arch_name.clear();  // Not required
  status = Cdm::initialize(
      Cdm::kNoSecureOutput, broken_client_info,
      g_host, g_host, g_host, static_cast<Cdm::LogLevel>(g_cutoff));
  EXPECT_EQ(Cdm::kSuccess, status);

  broken_client_info = working_client_info;
  broken_client_info.build_info.clear();  // Not required
  status = Cdm::initialize(
      Cdm::kNoSecureOutput, broken_client_info,
      g_host, g_host, g_host, static_cast<Cdm::LogLevel>(g_cutoff));
  EXPECT_EQ(Cdm::kSuccess, status);

  // Try with various host interfaces missing.
  status = Cdm::initialize(
      Cdm::kNoSecureOutput, working_client_info,
      NULL, g_host, g_host, static_cast<Cdm::LogLevel>(g_cutoff));
  EXPECT_EQ(Cdm::kTypeError, status);

  status = Cdm::initialize(
      Cdm::kNoSecureOutput, working_client_info,
      g_host, NULL, g_host, static_cast<Cdm::LogLevel>(g_cutoff));
  EXPECT_EQ(Cdm::kTypeError, status);

  status = Cdm::initialize(
      Cdm::kNoSecureOutput, working_client_info,
      g_host, g_host, NULL, static_cast<Cdm::LogLevel>(g_cutoff));
  EXPECT_EQ(Cdm::kTypeError, status);

  // One last init with everything correct and working.
  status = Cdm::initialize(
      Cdm::kNoSecureOutput, working_client_info,
      g_host, g_host, g_host, static_cast<Cdm::LogLevel>(g_cutoff));
  EXPECT_EQ(Cdm::kSuccess, status);
}

TEST_F(CdmTest, SetServerCertificate) {
  // Can't set a server certificate if privacy mode is disabled.
  ASSERT_NO_FATAL_FAILURE(RecreateCdm(false /* privacy_mode */));
  Cdm::Status status = cdm_->setServerCertificate(kDefaultServerCertificate);
  EXPECT_EQ(Cdm::kNotSupported, status);

  // Can set a server certificate if privacy mode is enabled.
  ASSERT_NO_FATAL_FAILURE(RecreateCdm(true /* privacy_mode */));
  status = cdm_->setServerCertificate(kDefaultServerCertificate);
  EXPECT_EQ(Cdm::kSuccess, status);

  // It is invalid to set an empty cert.
  status = cdm_->setServerCertificate("");
  EXPECT_EQ(Cdm::kTypeError, status);

  // It is invalid to set a malformed cert.
  status = cdm_->setServerCertificate("asdf");
  EXPECT_EQ(Cdm::kTypeError, status);
}

TEST_F(CdmTest, CreateSession) {
  // Create a temporary session.
  std::string session_id;
  Cdm::Status status = cdm_->createSession(Cdm::kTemporary, &session_id);
  EXPECT_EQ(Cdm::kSuccess, status);
  EXPECT_FALSE(session_id.empty());

  // Create another using the same pointer to an already-filled-out string,
  // and expect the session ID to change.
  std::string original_session_id = session_id;
  status = cdm_->createSession(Cdm::kTemporary, &session_id);
  EXPECT_EQ(Cdm::kSuccess, status);
  EXPECT_NE(original_session_id, session_id);

  // Create a persistent session.
  status = cdm_->createSession(Cdm::kPersistentLicense, &session_id);
  EXPECT_EQ(Cdm::kSuccess, status);

  // Try a NULL pointer for session ID.
  status = cdm_->createSession(Cdm::kTemporary, NULL);
  EXPECT_EQ(Cdm::kTypeError, status);

  // Try a bogus session type.
  status = cdm_->createSession(kBogusSessionType, &session_id);
  EXPECT_EQ(Cdm::kNotSupported, status);
}

TEST_F(CdmTest, GenerateRequest) {
  std::string session_id;
  Cdm::Status status = cdm_->createSession(Cdm::kTemporary, &session_id);
  ASSERT_EQ(Cdm::kSuccess, status);

  // Generate a license request for CENC.
  EXPECT_CALL(*this, onMessage(session_id, Cdm::kLicenseRequest, _));
  status = cdm_->generateRequest(session_id, Cdm::kCenc, kCencInitData);
  EXPECT_EQ(Cdm::kSuccess, status);
  Mock::VerifyAndClear(this);

  // Can't call generateRequest more than once on a session.
  EXPECT_CALL(*this, onMessage(session_id, Cdm::kLicenseRequest, _)).Times(0);
  status = cdm_->generateRequest(session_id, Cdm::kCenc, kCencInitData);
  EXPECT_EQ(Cdm::kInvalidState, status);
  Mock::VerifyAndClear(this);

  // Create a new session and generate a license request for WebM.
  status = cdm_->createSession(Cdm::kTemporary, &session_id);
  ASSERT_EQ(Cdm::kSuccess, status);
  EXPECT_CALL(*this, onMessage(session_id, Cdm::kLicenseRequest, _));
  status = cdm_->generateRequest(session_id, Cdm::kWebM, kWebMInitData);
  EXPECT_EQ(Cdm::kSuccess, status);
  Mock::VerifyAndClear(this);

  // Create a new session and try the as-yet-unsupported key-ids format.
  status = cdm_->createSession(Cdm::kTemporary, &session_id);
  ASSERT_EQ(Cdm::kSuccess, status);
  EXPECT_CALL(*this, onMessage(session_id, Cdm::kLicenseRequest, _)).Times(0);
  status = cdm_->generateRequest(session_id, Cdm::kKeyIds, kKeyIdsInitData);
  EXPECT_EQ(Cdm::kNotSupported, status);
  Mock::VerifyAndClear(this);

  // Create a new session and generate a license request for HLS.
  status = cdm_->createSession(Cdm::kTemporary, &session_id);
  ASSERT_EQ(Cdm::kSuccess, status);
  EXPECT_CALL(*this, onMessage(session_id, Cdm::kLicenseRequest, _));
  status = cdm_->generateRequest(session_id, Cdm::kHls, kHlsInitData);
  EXPECT_EQ(Cdm::kSuccess, status);
  Mock::VerifyAndClear(this);

  // Create a new session and try a bogus init data type.
  status = cdm_->createSession(Cdm::kTemporary, &session_id);
  ASSERT_EQ(Cdm::kSuccess, status);
  EXPECT_CALL(*this, onMessage(session_id, Cdm::kLicenseRequest, _)).Times(0);
  status = cdm_->generateRequest(session_id, kBogusInitDataType, "asdf");
  EXPECT_EQ(Cdm::kTypeError, status);
  Mock::VerifyAndClear(this);

  // This same session should still be usable with a supported init data type
  // after failing with an unsupported or bogus type.
  EXPECT_CALL(*this, onMessage(session_id, Cdm::kLicenseRequest, _));
  status = cdm_->generateRequest(session_id, Cdm::kCenc, kCencInitData);
  EXPECT_EQ(Cdm::kSuccess, status);
  Mock::VerifyAndClear(this);

  // Create a new session and try to pass empty init data.
  status = cdm_->createSession(Cdm::kTemporary, &session_id);
  ASSERT_EQ(Cdm::kSuccess, status);
  EXPECT_CALL(*this, onMessage(session_id, Cdm::kLicenseRequest, _)).Times(0);
  status = cdm_->generateRequest(session_id, Cdm::kCenc, "");
  EXPECT_EQ(Cdm::kTypeError, status);
  Mock::VerifyAndClear(this);

  // Try to pass invalid CENC init data.
  status = cdm_->createSession(Cdm::kTemporary, &session_id);
  ASSERT_EQ(Cdm::kSuccess, status);
  EXPECT_CALL(*this, onMessage(session_id, Cdm::kLicenseRequest, _)).Times(0);
  status = cdm_->generateRequest(session_id, Cdm::kCenc, kInvalidCencInitData);
  EXPECT_EQ(Cdm::kNotSupported, status);
  Mock::VerifyAndClear(this);

  // Try to pass non-Widevine CENC init data.
  status = cdm_->createSession(Cdm::kTemporary, &session_id);
  ASSERT_EQ(Cdm::kSuccess, status);
  EXPECT_CALL(*this, onMessage(session_id, Cdm::kLicenseRequest, _)).Times(0);
  status = cdm_->generateRequest(session_id, Cdm::kCenc,
                                 kNonWidevineCencInitData);
  EXPECT_EQ(Cdm::kNotSupported, status);
  Mock::VerifyAndClear(this);

  // Try a bogus session ID.
  EXPECT_CALL(*this, onMessage(_, _, _)).Times(0);
  status = cdm_->generateRequest(kBogusSessionId, Cdm::kCenc, kCencInitData);
  EXPECT_EQ(Cdm::kSessionNotFound, status);
  Mock::VerifyAndClear(this);
}

TEST_F(CdmTest, Update) {
  std::string session_id;
  std::string message;
  ASSERT_NO_FATAL_FAILURE(CreateSessionAndGenerateRequest(
      Cdm::kTemporary, Cdm::kCenc, &session_id, &message));

  // Acquire a license.
  std::string response;
  ASSERT_NO_FATAL_FAILURE(FetchLicense(
      kLicenseServerAppspot, message, &response));

  // Update the session.
  EXPECT_CALL(*this, onKeyStatusesChange(session_id));
  Cdm::Status status = cdm_->update(session_id, response);
  EXPECT_EQ(Cdm::kSuccess, status);
  Mock::VerifyAndClear(this);

  // Try updating a bogus session ID.
  status = cdm_->update(kBogusSessionId, response);
  EXPECT_EQ(Cdm::kSessionNotFound, status);

  // Try updating with an empty response.
  status = cdm_->update(session_id, "");
  EXPECT_EQ(Cdm::kTypeError, status);

  // Create a new session and try updating before generating a request.
  status = cdm_->createSession(Cdm::kTemporary, &session_id);
  ASSERT_EQ(Cdm::kSuccess, status);
  status = cdm_->update(session_id, response);
  ASSERT_EQ(Cdm::kInvalidState, status);
}

TEST_F(CdmTest, Close) {
  // Create a temporary session.
  std::string session_id;
  Cdm::Status status = cdm_->createSession(Cdm::kTemporary, &session_id);
  ASSERT_EQ(Cdm::kSuccess, status);

  // Close it.
  status = cdm_->close(session_id);
  ASSERT_EQ(Cdm::kSuccess, status);

  // Can't generate a license request after close.
  EXPECT_CALL(*this, onMessage(session_id, Cdm::kLicenseRequest, _)).Times(0);
  status = cdm_->generateRequest(session_id, Cdm::kCenc, kCencInitData);
  EXPECT_EQ(Cdm::kSessionNotFound, status);
  Mock::VerifyAndClear(this);

  // Try to close the same session again.
  status = cdm_->close(session_id);
  EXPECT_EQ(Cdm::kSessionNotFound, status);

  // Try to close a bogus session.
  status = cdm_->close(kBogusSessionId);
  EXPECT_EQ(Cdm::kSessionNotFound, status);
}

TEST_F(CdmTest, LoadTemporary) {
  std::string session_id;
  std::string response;
  ASSERT_NO_FATAL_FAILURE(CreateSessionAndFetchLicense(
      Cdm::kTemporary, Cdm::kCenc, &session_id, &response));

  // Update the temporary session.
  EXPECT_CALL(*this, onKeyStatusesChange(session_id));
  Cdm::Status status = cdm_->update(session_id, response);
  ASSERT_EQ(Cdm::kSuccess, status);
  Mock::VerifyAndClear(this);

  // Close the session.
  status = cdm_->close(session_id);
  ASSERT_EQ(Cdm::kSuccess, status);

  // Can't load a temporary session.
  status = cdm_->load(session_id);
  EXPECT_EQ(Cdm::kSessionNotFound, status);
}

TEST_F(CdmTest, LoadPersistent) {
  std::string session_id;
  std::string response;
  ASSERT_NO_FATAL_FAILURE(CreateSessionAndFetchLicense(
      Cdm::kPersistentLicense, Cdm::kCenc, &session_id, &response));

  // Update the persistent session.
  EXPECT_CALL(*this, onKeyStatusesChange(session_id));
  Cdm::Status status = cdm_->update(session_id, response);
  ASSERT_EQ(Cdm::kSuccess, status);
  Mock::VerifyAndClear(this);

  // Should be able to load the session again after closing it.
  status = cdm_->close(session_id);
  ASSERT_EQ(Cdm::kSuccess, status);
  EXPECT_CALL(*this, onKeyStatusesChange(session_id));
  status = cdm_->load(session_id);
  EXPECT_EQ(Cdm::kSuccess, status);
  Mock::VerifyAndClear(this);

  // Should be able to load the session again after recreating the CDM.
  ASSERT_NO_FATAL_FAILURE(RecreateCdm(true /* privacy_mode */));
  ASSERT_NO_FATAL_FAILURE(SetDefaultServerCertificate());
  EXPECT_CALL(*this, onKeyStatusesChange(session_id));
  status = cdm_->load(session_id);
  EXPECT_EQ(Cdm::kSuccess, status);
  Mock::VerifyAndClear(this);

  // Should not be able to load the session again clearing storage.
  status = cdm_->close(session_id);
  ASSERT_EQ(Cdm::kSuccess, status);
  g_host->Reset();
  EXPECT_CALL(*this, onKeyStatusesChange(session_id)).Times(0);
  status = cdm_->load(session_id);
  EXPECT_EQ(Cdm::kSessionNotFound, status);
  Mock::VerifyAndClear(this);
}

TEST_F(CdmTest, PerOriginLoadPersistent) {
  std::string session_id;
  std::string response;
  ASSERT_NO_FATAL_FAILURE(CreateSessionAndFetchLicense(
      Cdm::kPersistentLicense, Cdm::kCenc, &session_id, &response));

  // Update and close the persistent session.
  Cdm::Status status = cdm_->update(session_id, response);
  ASSERT_EQ(Cdm::kSuccess, status);
  status = cdm_->close(session_id);
  ASSERT_EQ(Cdm::kSuccess, status);

  // Should be able to load the session again after recreating the CDM.
  ASSERT_NO_FATAL_FAILURE(RecreateCdm(true /* privacy_mode */));
  ASSERT_NO_FATAL_FAILURE(SetDefaultServerCertificate());
  status = cdm_->load(session_id);
  EXPECT_EQ(Cdm::kSuccess, status);

  // Create another host to use its storage.  This will simulate another origin.
  TestHost other_host;
  scoped_ptr<Cdm> other_cdm(
      Cdm::create(this, &other_host, /* privacy_mode */ true));
  ASSERT_TRUE(other_cdm.get());
  status = other_cdm->setServerCertificate(kDefaultServerCertificate);
  ASSERT_EQ(Cdm::kSuccess, status);

  // Should not be able to load from another origin.
  EXPECT_CALL(*this, onKeyStatusesChange(session_id)).Times(0);
  status = other_cdm->load(session_id);
  EXPECT_EQ(Cdm::kSessionNotFound, status);
  Mock::VerifyAndClear(this);
}

TEST_F(CdmTest, LoadUsageRecord) {
  std::string session_id;
  std::string response;
  ASSERT_NO_FATAL_FAILURE(CreateSessionAndFetchLicense(
      Cdm::kPersistentUsageRecord, Cdm::kCenc, &session_id, &response));

  // Update the session.
  EXPECT_CALL(*this, onKeyStatusesChange(session_id));
  Cdm::Status status = cdm_->update(session_id, response);
  ASSERT_EQ(Cdm::kSuccess, status);
  Mock::VerifyAndClear(this);

  // Should be able to load the session again after closing it.
  status = cdm_->close(session_id);
  ASSERT_EQ(Cdm::kSuccess, status);

  // There should be no usable keys after loading this session.
  EXPECT_CALL(*this, onKeyStatusesChange(session_id)).Times(0);
  EXPECT_CALL(*this, onMessage(session_id, Cdm::kLicenseRelease, _)).Times(0);
  status = cdm_->load(session_id);
  EXPECT_EQ(Cdm::kSuccess, status);
  Mock::VerifyAndClear(this);

  // Should be able to load the session again after recreating the CDM.
  ASSERT_NO_FATAL_FAILURE(RecreateCdm(true /* privacy_mode */));
  ASSERT_NO_FATAL_FAILURE(SetDefaultServerCertificate());
  EXPECT_CALL(*this, onKeyStatusesChange(session_id)).Times(0);
  EXPECT_CALL(*this, onMessage(session_id, Cdm::kLicenseRelease, _)).Times(0);
  status = cdm_->load(session_id);
  EXPECT_EQ(Cdm::kSuccess, status);
  Mock::VerifyAndClear(this);

  // Should not be able to load the session again clearing storage.
  status = cdm_->close(session_id);
  ASSERT_EQ(Cdm::kSuccess, status);
  g_host->Reset();
  EXPECT_CALL(*this, onKeyStatusesChange(session_id)).Times(0);
  EXPECT_CALL(*this, onMessage(session_id, Cdm::kLicenseRelease, _)).Times(0);
  status = cdm_->load(session_id);
  EXPECT_EQ(Cdm::kSessionNotFound, status);
  Mock::VerifyAndClear(this);
}

TEST_F(CdmTest, LoadBogus) {
  EXPECT_CALL(*this, onKeyStatusesChange(_)).Times(0);
  Cdm::Status status = cdm_->load(kBogusSessionId);
  EXPECT_EQ(Cdm::kSessionNotFound, status);
}

TEST_F(CdmTest, GetKeyStatuses) {
  std::string session_id;
  ASSERT_NO_FATAL_FAILURE(CreateSessionAndUpdate(
      Cdm::kTemporary, Cdm::kCenc, &session_id));

  // We should be able to query status and see a usable key.
  Cdm::KeyStatusMap map;
  Cdm::Status status = cdm_->getKeyStatuses(session_id, &map);
  ASSERT_EQ(Cdm::kSuccess, status);
  EXPECT_EQ(Cdm::kUsable, map.begin()->second);

  // The key ID should be the one we are expecting.
  const std::string expected_key_id(
      reinterpret_cast<const char*>(kKeyIdCtr.data()), kKeyIdCtr.size());
  EXPECT_EQ(expected_key_id, map.begin()->first);

  // Let the key expire.
  EXPECT_CALL(*this, onKeyStatusesChange(session_id));
  EXPECT_CALL(*this, onMessage(session_id, Cdm::kLicenseRenewal, _)).Times(
      AtLeast(1));
  g_host->ElapseTime(kExpirationTestDelayMs);
  Mock::VerifyAndClear(this);

  // We should see expiration reflected in the map.
  status = cdm_->getKeyStatuses(session_id, &map);
  ASSERT_EQ(Cdm::kSuccess, status);
  EXPECT_EQ(Cdm::kExpired, map.begin()->second);

  // We can't get status after closing a session.
  status = cdm_->close(session_id);
  ASSERT_EQ(Cdm::kSuccess, status);
  status = cdm_->getKeyStatuses(session_id, &map);
  ASSERT_EQ(Cdm::kSessionNotFound, status);
}

TEST_F(CdmTest, GetExpiration) {
  std::string session_id;
  ASSERT_NO_FATAL_FAILURE(CreateSessionAndUpdate(
      Cdm::kTemporary, Cdm::kCenc, &session_id));

  // We should be able to query expiration and get a value in the future.
  int64_t expiration;
  Cdm::Status status = cdm_->getExpiration(session_id, &expiration);
  ASSERT_EQ(Cdm::kSuccess, status);
  EXPECT_GT(expiration, g_host->now());
  int64_t original_expiration = expiration;

  // Let the key expire.
  EXPECT_CALL(*this, onKeyStatusesChange(session_id));
  EXPECT_CALL(*this, onMessage(session_id, Cdm::kLicenseRenewal, _)).Times(
      AtLeast(1));
  g_host->ElapseTime(kExpirationTestDelayMs);
  Mock::VerifyAndClear(this);

  // We should see expiration in the past now.
  status = cdm_->getExpiration(session_id, &expiration);
  ASSERT_EQ(Cdm::kSuccess, status);
  EXPECT_LE(expiration, g_host->now());
  // Expiration should not have changed.
  EXPECT_EQ(original_expiration, expiration);

  // We can't get expiration after closing a session.
  status = cdm_->close(session_id);
  ASSERT_EQ(Cdm::kSuccess, status);
  status = cdm_->getExpiration(session_id, &expiration);
  ASSERT_EQ(Cdm::kSessionNotFound, status);
}

TEST_F(CdmTest, Remove) {
  std::string session_id;
  ASSERT_NO_FATAL_FAILURE(CreateSessionAndUpdate(
      Cdm::kPersistentLicense, Cdm::kCenc, &session_id));

  // Remove the session.  This causes a release message to be generated.
  std::string message;
  EXPECT_CALL(*this, onKeyStatusesChange(session_id));
  EXPECT_CALL(*this, onMessage(session_id, Cdm::kLicenseRelease, _)).WillOnce(
      SaveArg<2>(&message));
  Cdm::Status status = cdm_->remove(session_id);
  ASSERT_EQ(Cdm::kSuccess, status);
  Mock::VerifyAndClear(this);

  // The keys should already be unusable.
  Cdm::KeyStatusMap map;
  status = cdm_->getKeyStatuses(session_id, &map);
  ASSERT_EQ(Cdm::kSuccess, status);
  EXPECT_EQ(Cdm::kReleased, map.begin()->second);

  // Post the release message to the license server.
  std::string response;
  ASSERT_NO_FATAL_FAILURE(FetchLicense(
      kLicenseServerAppspot, message, &response));

  // Update the session.
  EXPECT_CALL(*this, onRemoveComplete(session_id));
  status = cdm_->update(session_id, response);
  ASSERT_EQ(Cdm::kSuccess, status);
  Mock::VerifyAndClear(this);

  // The session is now completely gone.
  status = cdm_->close(session_id);
  ASSERT_EQ(Cdm::kSessionNotFound, status);
  status = cdm_->load(session_id);
  ASSERT_EQ(Cdm::kSessionNotFound, status);

  // Try a bogus session ID.
  status = cdm_->remove(kBogusSessionId);
  EXPECT_EQ(Cdm::kSessionNotFound, status);

  // Try a new session.
  status = cdm_->createSession(Cdm::kPersistentLicense, &session_id);
  ASSERT_EQ(Cdm::kSuccess, status);
  status = cdm_->remove(session_id);
  EXPECT_EQ(Cdm::kInvalidState, status);

  // Try a temporary session.
  ASSERT_NO_FATAL_FAILURE(CreateSessionAndUpdate(
      Cdm::kTemporary, Cdm::kCenc, &session_id));
  status = cdm_->remove(session_id);
  EXPECT_EQ(Cdm::kRangeError, status);
}

TEST_F(CdmTest, RemoveUsageRecord) {
  std::string session_id;
  ASSERT_NO_FATAL_FAILURE(CreateSessionAndUpdate(
      Cdm::kPersistentUsageRecord, Cdm::kCenc, &session_id));

  // Remove the session.  This causes a release message to be generated.
  std::string message;
  EXPECT_CALL(*this, onKeyStatusesChange(session_id));
  EXPECT_CALL(*this, onMessage(session_id, Cdm::kLicenseRelease, _)).WillOnce(
      SaveArg<2>(&message));
  Cdm::Status status = cdm_->remove(session_id);
  ASSERT_EQ(Cdm::kSuccess, status);
  Mock::VerifyAndClear(this);

  // The keys should already be unusable.
  Cdm::KeyStatusMap map;
  status = cdm_->getKeyStatuses(session_id, &map);
  ASSERT_EQ(Cdm::kSuccess, status);
  EXPECT_EQ(Cdm::kReleased, map.begin()->second);

  // Post the release message to the license server.
  std::string response;
  ASSERT_NO_FATAL_FAILURE(FetchLicense(
      kLicenseServerAppspot, message, &response));

  // Update the session.
  EXPECT_CALL(*this, onRemoveComplete(session_id));
  status = cdm_->update(session_id, response);
  ASSERT_EQ(Cdm::kSuccess, status);
  Mock::VerifyAndClear(this);

  // The session is now completely gone.
  status = cdm_->close(session_id);
  ASSERT_EQ(Cdm::kSessionNotFound, status);
}

TEST_F(CdmTest, RemoveIncomplete) {
  std::string session_id;
  ASSERT_NO_FATAL_FAILURE(CreateSessionAndUpdate(
      Cdm::kPersistentLicense, Cdm::kCenc, &session_id));

  // Remove the session.  This causes a release message to be generated.
  std::string message;
  EXPECT_CALL(*this, onKeyStatusesChange(session_id));
  EXPECT_CALL(*this, onMessage(session_id, Cdm::kLicenseRelease, _)).WillOnce(
      SaveArg<2>(&message));
  Cdm::Status status = cdm_->remove(session_id);
  ASSERT_EQ(Cdm::kSuccess, status);
  Mock::VerifyAndClear(this);

  // The keys should already be unusable, but they should still exist.
  Cdm::KeyStatusMap map;
  status = cdm_->getKeyStatuses(session_id, &map);
  ASSERT_EQ(Cdm::kSuccess, status);
  ASSERT_FALSE(map.empty());
  EXPECT_EQ(Cdm::kReleased, map.begin()->second);

  // Recreate the CDM.
  ASSERT_NO_FATAL_FAILURE(RecreateCdm(true /* privacy_mode */));
  ASSERT_NO_FATAL_FAILURE(SetDefaultServerCertificate());

  // Load the partially removed session.
  EXPECT_CALL(*this, onKeyStatusesChange(session_id)).Times(0);
  EXPECT_CALL(*this, onMessage(session_id, Cdm::kLicenseRelease, _)).Times(0);
  status = cdm_->load(session_id);
  ASSERT_EQ(Cdm::kSuccess, status);
  Mock::VerifyAndClear(this);

  // This session has no keys.
  status = cdm_->getKeyStatuses(session_id, &map);
  ASSERT_EQ(Cdm::kSuccess, status);
  EXPECT_TRUE(map.empty());

  // Remove the session again to fire the release message.
  message.clear();
  EXPECT_CALL(*this, onKeyStatusesChange(session_id)).Times(0);
  EXPECT_CALL(*this, onMessage(session_id, Cdm::kLicenseRelease, _)).WillOnce(
      SaveArg<2>(&message));
  status = cdm_->remove(session_id);
  ASSERT_EQ(Cdm::kSuccess, status);
  ASSERT_FALSE(message.empty());
  Mock::VerifyAndClear(this);

  // Post the release message to the license server.
  std::string response;
  ASSERT_NO_FATAL_FAILURE(FetchLicense(
      kLicenseServerAppspot, message, &response));

  // Update the session.
  EXPECT_CALL(*this, onKeyStatusesChange(session_id)).Times(0);
  EXPECT_CALL(*this, onRemoveComplete(session_id));
  status = cdm_->update(session_id, response);
  ASSERT_EQ(Cdm::kSuccess, status);
  Mock::VerifyAndClear(this);

  // The session is now completely gone.
  status = cdm_->load(session_id);
  ASSERT_EQ(Cdm::kSessionNotFound, status);
}

TEST_F(CdmTest, RemoveUsageRecordIncomplete) {
  std::string session_id;
  ASSERT_NO_FATAL_FAILURE(CreateSessionAndUpdate(
      Cdm::kPersistentUsageRecord, Cdm::kCenc, &session_id));

  // Remove the session.  This causes a release message to be generated.
  std::string message;
  EXPECT_CALL(*this, onKeyStatusesChange(session_id));
  EXPECT_CALL(*this, onMessage(session_id, Cdm::kLicenseRelease, _)).WillOnce(
      SaveArg<2>(&message));
  Cdm::Status status = cdm_->remove(session_id);
  ASSERT_EQ(Cdm::kSuccess, status);
  Mock::VerifyAndClear(this);

  // The keys should already be unusable, but they should still exist.
  Cdm::KeyStatusMap map;
  status = cdm_->getKeyStatuses(session_id, &map);
  ASSERT_EQ(Cdm::kSuccess, status);
  ASSERT_FALSE(map.empty());
  EXPECT_EQ(Cdm::kReleased, map.begin()->second);

  // Recreate the CDM.
  ASSERT_NO_FATAL_FAILURE(RecreateCdm(true /* privacy_mode */));
  ASSERT_NO_FATAL_FAILURE(SetDefaultServerCertificate());

  // Load the partially removed session.
  EXPECT_CALL(*this, onKeyStatusesChange(session_id)).Times(0);
  EXPECT_CALL(*this, onMessage(session_id, Cdm::kLicenseRelease, _)).Times(0);
  status = cdm_->load(session_id);
  ASSERT_EQ(Cdm::kSuccess, status);
  Mock::VerifyAndClear(this);

  // Remove the session again to fire a release message.
  message.clear();
  EXPECT_CALL(*this, onKeyStatusesChange(session_id)).Times(0);
  EXPECT_CALL(*this, onMessage(session_id, Cdm::kLicenseRelease, _)).WillOnce(
      SaveArg<2>(&message));
  status = cdm_->remove(session_id);
  ASSERT_EQ(Cdm::kSuccess, status);
  ASSERT_FALSE(message.empty());
  Mock::VerifyAndClear(this);

  // This session has no keys.
  status = cdm_->getKeyStatuses(session_id, &map);
  ASSERT_EQ(Cdm::kSuccess, status);
  EXPECT_TRUE(map.empty());

  // Post the release message to the license server.
  std::string response;
  ASSERT_NO_FATAL_FAILURE(FetchLicense(
      kLicenseServerAppspot, message, &response));

  // Update the session.
  EXPECT_CALL(*this, onKeyStatusesChange(session_id)).Times(0);
  EXPECT_CALL(*this, onRemoveComplete(session_id));
  status = cdm_->update(session_id, response);
  ASSERT_EQ(Cdm::kSuccess, status);
  Mock::VerifyAndClear(this);

  // The session is now completely gone.
  status = cdm_->load(session_id);
  ASSERT_EQ(Cdm::kSessionNotFound, status);
}

TEST_F(CdmTest, RemoveNotLoaded) {
  // Create a persistent session and then close it.
  std::string session_id;
  ASSERT_NO_FATAL_FAILURE(CreateSessionAndUpdate(
      Cdm::kPersistentLicense, Cdm::kCenc, &session_id));
  Cdm::Status status = cdm_->close(session_id);
  ASSERT_EQ(Cdm::kSuccess, status);

  // A session must be loaded before removing it.  Remove only works on active
  // sessions.
  status = cdm_->remove(session_id);
  EXPECT_EQ(Cdm::kSessionNotFound, status);
}

TEST_F(CdmTest, RequestPersistentLicenseWithWrongInitData) {
  // Generate a request for a persistent license without using the correct
  // persistent content init data.
  std::string session_id;
  Cdm::Status status = cdm_->createSession(Cdm::kPersistentLicense,
                                           &session_id);
  ASSERT_EQ(Cdm::kSuccess, status);

  std::string message;
  EXPECT_CALL(*this, onMessage(session_id, Cdm::kLicenseRequest, _)).WillOnce(
      SaveArg<2>(&message));
  status = cdm_->generateRequest(session_id, Cdm::kCenc, kCencInitData);
  ASSERT_EQ(Cdm::kSuccess, status);
  Mock::VerifyAndClear(this);

  // The license server will reject this.
  FetchLicenseFailure(message, 500);
}

TEST_F(CdmTest, RequestTemporaryLicenseWithWrongInitData) {
  // Generate a request for a temporary license using persistent init data.
  std::string session_id;
  Cdm::Status status = cdm_->createSession(Cdm::kTemporary, &session_id);
  ASSERT_EQ(Cdm::kSuccess, status);

  std::string message;
  EXPECT_CALL(*this, onMessage(session_id, Cdm::kLicenseRequest, _)).WillOnce(
      SaveArg<2>(&message));
  status = cdm_->generateRequest(session_id, Cdm::kCenc,
                                 kCencPersistentInitData);
  ASSERT_EQ(Cdm::kSuccess, status);
  Mock::VerifyAndClear(this);

  // Acquire a license.
  std::string response;
  ASSERT_NO_FATAL_FAILURE(FetchLicense(
      kLicenseServerAppspot, message, &response));

  // This license should not be accepted.
  EXPECT_CALL(*this, onKeyStatusesChange(session_id));
  status = cdm_->update(session_id, response);
  EXPECT_EQ(Cdm::kRangeError, status);
  Mock::VerifyAndClear(this);
}

TEST_F(CdmTest, Renewal) {
  std::string session_id;
  ASSERT_NO_FATAL_FAILURE(CreateSessionAndUpdate(
      Cdm::kTemporary, Cdm::kCenc, &session_id));

  // We should have a timer.
  EXPECT_NE(0, g_host->NumTimers());

  // When we elapse time, we should get a renewal message.
  std::string message;
  EXPECT_CALL(*this, onMessage(session_id, Cdm::kLicenseRenewal, _)).WillOnce(
      SaveArg<2>(&message));
  g_host->ElapseTime(kRenewalTestDelayMs);
  Mock::VerifyAndClear(this);
  ASSERT_FALSE(message.empty());  // Stop the test if no message came through.

  // When should still have a timer.
  EXPECT_NE(0, g_host->NumTimers());

  // We should be able to update the session.
  ASSERT_NO_FATAL_FAILURE(FetchLicenseAndUpdate(session_id, message));

  // After closing the session, there should be no more renewals.
  Cdm::Status status = cdm_->close(session_id);
  ASSERT_EQ(Cdm::kSuccess, status);

  EXPECT_CALL(*this, onMessage(session_id, Cdm::kLicenseRenewal, _)).Times(0);
  g_host->ElapseTime(kRenewalTestDelayMs * 10);
  Mock::VerifyAndClear(this);
}

TEST_F(CdmTest, ServerCertificateProvisioning) {
  // Do not set a server cert.  Provisioning will be required.
  ASSERT_NO_FATAL_FAILURE(RecreateCdm(true /* privacy_mode */));

  // Create a session.
  std::string session_id;
  Cdm::Status status = cdm_->createSession(Cdm::kTemporary, &session_id);
  ASSERT_EQ(Cdm::kSuccess, status);

  // Expect a license request type message, but this is actually a server cert
  // provisioning request.
  std::string message;
  EXPECT_CALL(*this, onMessage(session_id, Cdm::kLicenseRequest, _))
      .WillOnce(SaveArg<2>(&message));
  status = cdm_->generateRequest(session_id, Cdm::kCenc, kCencInitData);
  ASSERT_EQ(Cdm::kSuccess, status);
  Mock::VerifyAndClear(this);

  // Relay it to the server.
  std::string response;
  ASSERT_NO_FATAL_FAILURE(FetchLicense(
      kLicenseServerAppspot, message, &response));

  // No keys will change, since this wasn't a license.
  EXPECT_CALL(*this, onKeyStatusesChange(session_id)).Times(0);
  // We should get another license request generated during update.
  message.clear();
  EXPECT_CALL(*this, onMessage(session_id, Cdm::kLicenseRequest, _)).WillOnce(
      SaveArg<2>(&message));
  status = cdm_->update(session_id, response);
  ASSERT_EQ(Cdm::kSuccess, status);
  Mock::VerifyAndClear(this);

  // There are no keys yet.
  Cdm::KeyStatusMap map;
  status = cdm_->getKeyStatuses(session_id, &map);
  ASSERT_EQ(Cdm::kSuccess, status);
  ASSERT_TRUE(map.empty());

  // Relay the license request to the server.
  ASSERT_NO_FATAL_FAILURE(FetchLicense(
      kLicenseServerAppspot, message, &response));

  // Update the session.  The keys will change now.
  EXPECT_CALL(*this, onKeyStatusesChange(session_id)).Times(1);
  status = cdm_->update(session_id, response);
  ASSERT_EQ(Cdm::kSuccess, status);
  Mock::VerifyAndClear(this);

  // The keys should be usable.
  status = cdm_->getKeyStatuses(session_id, &map);
  ASSERT_EQ(Cdm::kSuccess, status);
  ASSERT_FALSE(map.empty());
  EXPECT_EQ(Cdm::kUsable, map.begin()->second);


  // Create another session.  This one should not require server certificate
  // provisioning.
  status = cdm_->createSession(Cdm::kTemporary, &session_id);
  ASSERT_EQ(Cdm::kSuccess, status);

  // Expect a license request.
  message.clear();
  EXPECT_CALL(*this, onMessage(session_id, Cdm::kLicenseRequest, _)).WillOnce(
      SaveArg<2>(&message));
  status = cdm_->generateRequest(session_id, Cdm::kCenc, kCencInitData);
  ASSERT_EQ(Cdm::kSuccess, status);
  Mock::VerifyAndClear(this);

  // Relay it to the server.
  ASSERT_NO_FATAL_FAILURE(FetchLicense(
      kLicenseServerAppspot, message, &response));

  // Keys will change, since this was an actual license.
  EXPECT_CALL(*this, onKeyStatusesChange(session_id)).Times(1);
  status = cdm_->update(session_id, response);
  ASSERT_EQ(Cdm::kSuccess, status);
  Mock::VerifyAndClear(this);


  // Create a second CDM instance.
  scoped_ptr<Cdm> cdm2;
  CreateAdditionalCdm(true /* privacy_mode */, &cdm2);

  // Create a session on the second CDM instance.  This one should require
  // provisioning, since provisioned certs should not be shared across CDM
  // instances.
  status = cdm2->createSession(Cdm::kTemporary, &session_id);
  ASSERT_EQ(Cdm::kSuccess, status);
  message.clear();
  EXPECT_CALL(*this, onMessage(session_id, Cdm::kLicenseRequest, _))
      .WillOnce(SaveArg<2>(&message));
  status = cdm2->generateRequest(session_id, Cdm::kCenc, kCencInitData);
  ASSERT_EQ(Cdm::kSuccess, status);
  Mock::VerifyAndClear(this);

  // Relay it to the server.
  ASSERT_NO_FATAL_FAILURE(FetchLicense(
      kLicenseServerAppspot, message, &response));

  // No keys will change, since this wasn't a license.
  EXPECT_CALL(*this, onKeyStatusesChange(session_id)).Times(0);
  // We should get another license request generated during update.
  EXPECT_CALL(*this, onMessage(session_id, Cdm::kLicenseRequest, _));
  status = cdm2->update(session_id, response);
  ASSERT_EQ(Cdm::kSuccess, status);
  Mock::VerifyAndClear(this);


  // Create another session on the first CDM.  This one should not require
  // server certificate provisioning.  This proves that the creation of the
  // second CDM instance did not affect the state of the first.
  status = cdm_->createSession(Cdm::kTemporary, &session_id);
  ASSERT_EQ(Cdm::kSuccess, status);
  message.clear();
  EXPECT_CALL(*this, onMessage(session_id, Cdm::kLicenseRequest, _)).WillOnce(
      SaveArg<2>(&message));
  status = cdm_->generateRequest(session_id, Cdm::kCenc, kCencInitData);
  ASSERT_EQ(Cdm::kSuccess, status);
  Mock::VerifyAndClear(this);

  // Relay it to the server.
  ASSERT_NO_FATAL_FAILURE(FetchLicense(
      kLicenseServerAppspot, message, &response));

  // Keys will change, since this was an actual license.
  EXPECT_CALL(*this, onKeyStatusesChange(session_id)).Times(1);
  status = cdm_->update(session_id, response);
  ASSERT_EQ(Cdm::kSuccess, status);
  Mock::VerifyAndClear(this);
}

TEST_F(CdmTest, SetAppParameters) {
  // Must use privacy_mode = false to ensure that the message is in plain-text.
  std::string session_id;
  ASSERT_NO_FATAL_FAILURE(RecreateCdm(false /* privacy_mode */));
  Cdm::Status status = cdm_->createSession(Cdm::kTemporary, &session_id);
  ASSERT_EQ(Cdm::kSuccess, status);

  // Set a new app parameter, and check by getting.
  std::string result;
  status = cdm_->setAppParameter(kParamName, kValue);
  ASSERT_EQ(Cdm::kSuccess, status);
  status = cdm_->getAppParameter(kParamName, &result);
  ASSERT_EQ(Cdm::kSuccess, status);
  ASSERT_EQ(kValue, result);

  // Try to get using a null result.
  status = cdm_->getAppParameter(kParamName, NULL);
  ASSERT_EQ(Cdm::kTypeError, status);

  // Try to get using an empty key.
  status = cdm_->getAppParameter("", &result);
  ASSERT_EQ(Cdm::kTypeError, status);

  // Try to set using an empty key.
  status = cdm_->setAppParameter("", kValue);
  ASSERT_EQ(Cdm::kTypeError, status);

  // Try to remove using an empty key.
  status = cdm_->removeAppParameter("");
  ASSERT_EQ(Cdm::kTypeError, status);

  // Change an existing app parameter.
  status = cdm_->setAppParameter(kParamName, kNewValue);
  ASSERT_EQ(Cdm::kSuccess, status);
  status = cdm_->getAppParameter(kParamName, &result);
  ASSERT_EQ(Cdm::kSuccess, status);
  ASSERT_EQ(kNewValue, result);

  // Remove an existing app parameter, check for invalid access when it's gone.
  status = cdm_->removeAppParameter(kParamName);
  ASSERT_EQ(Cdm::kSuccess, status);
  status = cdm_->getAppParameter(kParamName, &result);
  ASSERT_EQ(Cdm::kTypeError, status);

  // Try to remove an absent value.
  status = cdm_->removeAppParameter(kParamName2);
  ASSERT_EQ(Cdm::kTypeError, status);

  // Set some values to check for.
  status = cdm_->setAppParameter(kParamName, kValue);
  ASSERT_EQ(Cdm::kSuccess, status);
  status = cdm_->setAppParameter(kParamName2, kNewValue);
  ASSERT_EQ(Cdm::kSuccess, status);

  // Send a generate request to ensure the parameter is in the message.
  std::string message;
  EXPECT_CALL(*this, onMessage(session_id, Cdm::kLicenseRequest, _)).WillOnce(
      SaveArg<2>(&message));
  status = cdm_->generateRequest(session_id, Cdm::kCenc, kCencInitData);
  EXPECT_EQ(Cdm::kSuccess, status);
  EXPECT_TRUE(!message.empty() && message.find(kValue) != std::string::npos);
  Mock::VerifyAndClear(this);

  // Ensure that the value is still present and correct.
  status = cdm_->getAppParameter(kParamName, &result);
  ASSERT_EQ(Cdm::kSuccess, status);
  ASSERT_EQ(kValue, result);
  status = cdm_->getAppParameter(kParamName2, &result);
  ASSERT_EQ(Cdm::kSuccess, status);
  ASSERT_EQ(kNewValue, result);

  // Clear all the parameters.
  status = cdm_->clearAppParameters();
  ASSERT_EQ(Cdm::kSuccess, status);
  status = cdm_->getAppParameter(kParamName, &result);
  ASSERT_EQ(Cdm::kTypeError, status);
  status = cdm_->getAppParameter(kParamName2, &result);
  ASSERT_EQ(Cdm::kTypeError, status);
}

TEST_P(CdmTestWithDecryptParam, DecryptToClearBuffer) {
  DecryptParam param = GetParam();

  Cdm::InputBuffer input;
  Cdm::OutputBuffer output;

  input.key_id = param.key_id->data();
  input.key_id_length = param.key_id->size();
  input.iv = param.iv->data();
  input.iv_length = param.iv->size();
  input.data = param.input->data();
  input.data_length = param.input->size();
  input.encryption_scheme = param.scheme;
  input.pattern = *param.pattern;

  std::vector<uint8_t> output_buffer(input.data_length);
  output.data = &(output_buffer[0]);
  output.data_length = output_buffer.size();

  // Decrypt without keys loaded should fail.
  Cdm::Status status = cdm_->decrypt(input, output);
  ASSERT_EQ(Cdm::kNoKey, status);

  // Create a session with the right keys.
  std::string session_id;
  ASSERT_NO_FATAL_FAILURE(CreateSessionAndUpdate(
      Cdm::kTemporary, param.init_data_type, &session_id));

  // Decrypt should now succeed.
  status = cdm_->decrypt(input, output);
  ASSERT_EQ(Cdm::kSuccess, status);
  EXPECT_EQ(*param.output, output_buffer);
}

INSTANTIATE_TEST_CASE_P(CdmDecryptTest, CdmTestWithDecryptParam, Values(
  DecryptParam("CENC 3.0 cenc Mode",
               Cdm::kCenc, kKeyIdCtr, kIvCenc, Cdm::kAesCtr,
               kPatternNone, kInputCenc, kOutputCenc),
  DecryptParam("CENC 3.0 cens Mode",
               Cdm::kCenc, kKeyIdCtr, kIvCens, Cdm::kAesCtr,
               kPatternRecommended, kInputCens, kOutputCens),
  DecryptParam("CENC 3.0 cbc1 Mode",
               Cdm::kHls, kKeyIdCbc, kIvCbc1, Cdm::kAesCbc,
               kPatternNone, kInputCbc1, kOutputCbc1),
  DecryptParam("CENC 3.0 cbcs Mode",
               Cdm::kHls, kKeyIdCbc, kIvCbcs, Cdm::kAesCbc,
               kPatternRecommended, kInputCbcs, kOutputCbcs),
  DecryptParam("HLS Audio (CENC 3.0 cbcs Mode Without a Pattern)",
               Cdm::kHls, kKeyIdCbc, kIvCbc1, Cdm::kAesCbc,
               kPatternHlsAudio, kInputCbc1, kOutputCbc1)
  ));

// TODO: add infrastructure to test secure buffer decrypt for some platforms

class CdmIndividualizationTest : public CdmTest {
 protected:
  bool CheckProvisioningSupport() {
    uint32_t nonce = 0;
    uint8_t buffer[1];
    size_t size = 0;
    EXPECT_EQ(OEMCrypto_SUCCESS, OEMCrypto_Initialize());
    int result = OEMCrypto_RewrapDeviceRSAKey(0, buffer, 0, buffer, 0, &nonce,
                                              buffer, 0, buffer, buffer, &size);
    EXPECT_EQ(OEMCrypto_SUCCESS, OEMCrypto_Terminate());
    if (result == OEMCrypto_ERROR_NOT_IMPLEMENTED) {
      LOGW(
          "WARNING: Skipping PerOriginDeviceProvisioning because the device "
          "does not support provisioning. If you are using a baked-in "
          "certificate, this is expected. Otherwise, something is wrong.");
      return false;
    }
    return true;
  }

  std::string GetProvisioningResponse(const std::string& message) {
    std::string reply;
    std::string uri = kProvisioningServerUrl;
    uri += "&signedRequest=" + message;
    FetchCertificate(uri, &reply);
    if (HasFatalFailure())
      return "";
    return reply;
  }
};

TEST_F(CdmIndividualizationTest, BasicFlow) {
  if (!CheckProvisioningSupport()) return;

  // Clear any existing certificates.
  g_host->remove("cert.bin");

  // Creating a session should succeed.
  std::string session_id;
  Cdm::Status status = cdm_->createSession(Cdm::kTemporary, &session_id);
  EXPECT_EQ(Cdm::kSuccess, status);

  // Should get an individualization request when we generate request.
  std::string message;
  EXPECT_CALL(*this, onDirectIndividualizationRequest(session_id, _))
      .WillOnce(SaveArg<1>(&message));
  status = cdm_->generateRequest(session_id, Cdm::kCenc, kCencInitData);
  EXPECT_EQ(Cdm::kSuccess, status);
  Mock::VerifyAndClear(this);

  // Complete the provisioning request.
  std::string reply = GetProvisioningResponse(message);
  ASSERT_FALSE(reply.empty());
  EXPECT_CALL(*this, onMessage(session_id, Cdm::kLicenseRequest, _)).Times(1);
  EXPECT_CALL(*this, onDeferredComplete(_, _)).Times(0);
  status = cdm_->update(session_id, reply);
  ASSERT_EQ(Cdm::kSuccess, status);
  Mock::VerifyAndClear(this);
}

TEST_F(CdmIndividualizationTest, WillNotSendRequestTwice) {
  if (!CheckProvisioningSupport()) return;

  // Clear any existing certificates.
  g_host->remove("cert.bin");

  // Creating a session should succeed.
  std::string session_id;
  ASSERT_EQ(Cdm::kSuccess, cdm_->createSession(Cdm::kTemporary, &session_id));

  // Should get an individualization request when we generate request.
  std::string message;
  EXPECT_CALL(*this, onDirectIndividualizationRequest(session_id, _))
      .WillOnce(SaveArg<1>(&message));
  ASSERT_EQ(Cdm::kSuccess,
            cdm_->generateRequest(session_id, Cdm::kCenc, kCencInitData));
  Mock::VerifyAndClear(this);

  // Create a second session.
  std::string session_id2;
  ASSERT_EQ(Cdm::kSuccess, cdm_->createSession(Cdm::kTemporary, &session_id2));

  // Should not get another individualization request.
  EXPECT_CALL(*this, onMessage(_, _, _)).Times(0);
  ASSERT_EQ(Cdm::kDeferred,
            cdm_->generateRequest(session_id2, Cdm::kCenc, kCencInitData));
  Mock::VerifyAndClear(this);

  // Complete the provisioning request,  should generate requests for both
  // sessions.
  std::string reply = GetProvisioningResponse(message);
  ASSERT_FALSE(reply.empty());
  EXPECT_CALL(*this, onMessage(session_id, Cdm::kLicenseRequest, _)).Times(1);
  EXPECT_CALL(*this, onMessage(session_id2, Cdm::kLicenseRequest, _)).Times(1);
  EXPECT_CALL(*this, onDeferredComplete(session_id2, Cdm::kSuccess)).Times(1);
  EXPECT_EQ(Cdm::kSuccess, cdm_->update(session_id, reply));
  Mock::VerifyAndClear(this);
}

TEST_F(CdmIndividualizationTest,
       WillNotSendMessageWhenGenerateRequestNotCalled) {
  if (!CheckProvisioningSupport()) return;

  // Clear any existing certificates.
  g_host->remove("cert.bin");

  // Creating a session should succeed.
  std::string session_id;
  ASSERT_EQ(Cdm::kSuccess, cdm_->createSession(Cdm::kTemporary, &session_id));

  // Should get an individualization request when we generate request.
  std::string message;
  EXPECT_CALL(*this, onDirectIndividualizationRequest(session_id, _))
      .WillOnce(SaveArg<1>(&message));
  ASSERT_EQ(Cdm::kSuccess,
            cdm_->generateRequest(session_id, Cdm::kCenc, kCencInitData));
  Mock::VerifyAndClear(this);

  // Create a second session, don't call generateRequest for it.
  std::string session_id2;
  ASSERT_EQ(Cdm::kSuccess, cdm_->createSession(Cdm::kTemporary, &session_id2));

  // Complete the provisioning request, should not get calls for the second
  // session.
  std::string reply = GetProvisioningResponse(message);
  ASSERT_FALSE(reply.empty());
  EXPECT_CALL(*this, onMessage(session_id, Cdm::kLicenseRequest, _)).Times(1);
  EXPECT_CALL(*this, onMessage(session_id2, Cdm::kLicenseRequest, _)).Times(0);
  EXPECT_CALL(*this, onDeferredComplete(_, _)).Times(0);
  EXPECT_EQ(Cdm::kSuccess, cdm_->update(session_id, reply));
  Mock::VerifyAndClear(this);

  // We should get a license message for the second session.
  EXPECT_CALL(*this, onMessage(session_id2, Cdm::kLicenseRequest, _)).Times(1);
  ASSERT_EQ(Cdm::kSuccess,
            cdm_->generateRequest(session_id2, Cdm::kCenc, kCencInitData));
  Mock::VerifyAndClear(this);
}

TEST_F(CdmIndividualizationTest, PropagatesErrorsInUpdate) {
  if (!CheckProvisioningSupport()) return;

  // Clear any existing certificates.
  g_host->remove("cert.bin");

  // Creating a session should succeed.
  std::string session_id;
  ASSERT_EQ(Cdm::kSuccess, cdm_->createSession(Cdm::kTemporary, &session_id));

  // Should get an individualization request when we generate request.
  std::string message;
  EXPECT_CALL(*this, onDirectIndividualizationRequest(session_id, _))
      .WillOnce(SaveArg<1>(&message));
  ASSERT_EQ(Cdm::kSuccess, cdm_->generateRequest(session_id, Cdm::kCenc,
                                                 kInvalidCencInitData));
  Mock::VerifyAndClear(this);

  // Complete the provisioning request, should get an error call.
  std::string reply = GetProvisioningResponse(message);
  ASSERT_FALSE(reply.empty());
  EXPECT_CALL(*this, onMessage(_, _, _)).Times(0);
  EXPECT_CALL(*this, onDeferredComplete(_, _)).Times(0);
  EXPECT_EQ(Cdm::kNotSupported, cdm_->update(session_id, reply));
  Mock::VerifyAndClear(this);
}

TEST_F(CdmIndividualizationTest, OnlyPropagatesErrorsForThisSession) {
  if (!CheckProvisioningSupport()) return;

  // Clear any existing certificates.
  g_host->remove("cert.bin");

  // Creating a session should succeed.
  std::string session_id;
  ASSERT_EQ(Cdm::kSuccess, cdm_->createSession(Cdm::kTemporary, &session_id));

  // Should get an individualization request when we generate request.
  std::string message;
  EXPECT_CALL(*this, onDirectIndividualizationRequest(session_id, _))
      .WillOnce(SaveArg<1>(&message));
  ASSERT_EQ(Cdm::kSuccess,
            cdm_->generateRequest(session_id, Cdm::kCenc, kCencInitData));
  Mock::VerifyAndClear(this);

  // Create another session that will cause an error.
  std::string session_id_2;
  ASSERT_EQ(Cdm::kSuccess,
            cdm_->createSession(Cdm::kTemporary, &session_id_2));
  ASSERT_EQ(Cdm::kDeferred, cdm_->generateRequest(session_id_2, Cdm::kCenc,
                                                  kInvalidCencInitData));

  // Complete the provisioning request, should succeed, but get an error
  // callback.
  std::string reply = GetProvisioningResponse(message);
  ASSERT_FALSE(reply.empty());
  EXPECT_CALL(*this, onMessage(session_id, Cdm::kLicenseRequest, _)).Times(1);
  EXPECT_CALL(*this, onMessage(session_id_2, _, _)).Times(0);
  EXPECT_CALL(*this, onDeferredComplete(session_id_2, Cdm::kNotSupported))
      .Times(1);
  EXPECT_EQ(Cdm::kSuccess, cdm_->update(session_id, reply));
  Mock::VerifyAndClear(this);
}

TEST_F(CdmIndividualizationTest, WorksWithLoad) {
  if (!CheckProvisioningSupport()) return;

  // Create an offline session to load.
  std::string session_id;
  ASSERT_NO_FATAL_FAILURE(
      CreateSessionAndUpdate(Cdm::kPersistentLicense, Cdm::kCenc, &session_id));
  EXPECT_EQ(Cdm::kSuccess, cdm_->close(session_id));

  // Clear any existing certificates.
  g_host->remove("cert.bin");

  // Loading a session should succeed, we should get an individualization
  // request right away.
  std::string message;
  EXPECT_CALL(*this, onDirectIndividualizationRequest(session_id, _))
      .WillOnce(SaveArg<1>(&message));
  ASSERT_EQ(Cdm::kSuccess, cdm_->load(session_id));
  Mock::VerifyAndClear(this);

  // Complete the provisioning request.
  std::string reply = GetProvisioningResponse(message);
  ASSERT_FALSE(reply.empty());
  // Because we are now provisioned with a new key, we can't load the session,
  // but we will still be provisioned.
  EXPECT_CALL(*this, onDeferredComplete(_, _)).Times(0);
  EXPECT_EQ(Cdm::kUnexpectedError, cdm_->update(session_id, reply));
  Mock::VerifyAndClear(this);

  // Create a second session, we should be previsioned at this point.
  std::string session_id2;
  ASSERT_EQ(Cdm::kSuccess, cdm_->createSession(Cdm::kTemporary, &session_id2));
  EXPECT_CALL(*this, onMessage(session_id2, Cdm::kLicenseRequest, _)).Times(1);
  ASSERT_EQ(Cdm::kSuccess,
            cdm_->generateRequest(session_id2, Cdm::kCenc, kCencInitData));
  Mock::VerifyAndClear(this);
}

TEST_F(CdmIndividualizationTest, WillResendOnProvisioningError) {
  if (!CheckProvisioningSupport()) return;

  // Clear any existing certificates.
  g_host->remove("cert.bin");

  // Creating a session should succeed.
  std::string session_id;
  ASSERT_EQ(Cdm::kSuccess, cdm_->createSession(Cdm::kTemporary, &session_id));

  // Should get an individualization request when we generate request.
  std::string message;
  EXPECT_CALL(*this, onDirectIndividualizationRequest(session_id, _))
      .WillOnce(SaveArg<1>(&message));
  ASSERT_EQ(Cdm::kSuccess,
            cdm_->generateRequest(session_id, Cdm::kCenc, kCencInitData));
  Mock::VerifyAndClear(this);

  // Fail to provision the device.
  EXPECT_CALL(*this, onMessage(_, _, _)).Times(0);
  EXPECT_CALL(*this, onDeferredComplete(_, _)).Times(0);
  EXPECT_EQ(Cdm::kUnexpectedError, cdm_->update(session_id, ""));
  Mock::VerifyAndClear(this);

  // Should get another individualization request.
  std::string session_id_2;
  ASSERT_EQ(Cdm::kSuccess,
            cdm_->createSession(Cdm::kTemporary, &session_id_2));
  EXPECT_CALL(*this, onDirectIndividualizationRequest(session_id_2, _))
      .WillOnce(SaveArg<1>(&message));
  ASSERT_EQ(Cdm::kSuccess,
            cdm_->generateRequest(session_id_2, Cdm::kCenc, kCencInitData));
  Mock::VerifyAndClear(this);
}

}  // namespace widevine
