#ifndef CDM_OEC_SESSION_UTIL_H_
#define CDM_OEC_SESSION_UTIL_H_

// Copyright 2016 Google Inc. All Rights Reserved.
//
// OEMCrypto unit tests
//
#include <openssl/rsa.h>
#include <string>
#include <vector>

#include "oec_device_features.h"
#include "wv_cdm_constants.h"

using namespace std;

// GTest requires PrintTo to be in the same namespace as the thing it prints,
// which is std::vector in this case.
namespace std {

struct PatternTestVariant {
  PatternTestVariant(size_t encrypt, size_t skip, OEMCryptoCipherMode mode) {
    this->pattern.encrypt = encrypt;
    this->pattern.skip = skip;
    this->pattern.offset = 0;
    this->mode = mode;
  }
  OEMCrypto_CENCEncryptPatternDesc pattern;
  OEMCryptoCipherMode mode;
};

void PrintTo(const vector<uint8_t>& value, ostream* os);
void PrintTo(const PatternTestVariant& param, ostream* os);

}  // namespace std

namespace wvoec {

const size_t kNumKeys = 4;

namespace {
#if defined(TEST_SPEED_MULTIPLIER)  // Can slow test time limits when
                                    // debugging is slowing everything.
const int kSpeedMultiplier = TEST_SPEED_MULTIPLIER;
#else
const int kSpeedMultiplier = 1;
#endif
const int kShortSleep = 1 * kSpeedMultiplier;
const int kLongSleep = 2 * kSpeedMultiplier;
const uint32_t kDuration = 2 * kSpeedMultiplier;
const uint32_t kLongDuration = 5 * kSpeedMultiplier;
const int32_t kTimeTolerance = 10 * kSpeedMultiplier;
}  // namespace

typedef struct {
  uint8_t verification[4];
  uint32_t duration;
  uint32_t nonce;
  uint32_t control_bits;
} KeyControlBlock;

// Note: The API does not specify a maximum key id length.  We specify a
// maximum just for these tests, so that we have a fixed message size.
const size_t kTestKeyIdMaxLength = 16;

// Most content will use a key id that is 16 bytes long.
const int kDefaultKeyIdLength = 16;

const size_t kMaxTestRSAKeyLength = 2000;  // Rough estimate.

typedef struct {
  uint8_t key_id[kTestKeyIdMaxLength];
  size_t key_id_length;
  uint8_t key_data[wvcdm::MAC_KEY_SIZE];
  size_t key_data_length;
  uint8_t key_iv[wvcdm::KEY_IV_SIZE];
  uint8_t control_iv[wvcdm::KEY_IV_SIZE];
  KeyControlBlock control;
  // Note: cipher_mode may not be part of a real signed message. For these
  // tests, it is convenient to keep it in this structure anyway.
  OEMCryptoCipherMode cipher_mode;
} MessageKeyData;

// This structure will be signed to simulate a message from the server.
struct MessageData {
  MessageKeyData keys[kNumKeys];
  uint8_t mac_key_iv[wvcdm::KEY_IV_SIZE];
  uint8_t mac_keys[2 * wvcdm::MAC_KEY_SIZE];
  uint8_t pst[kTestKeyIdMaxLength];
};

struct RSAPrivateKeyMessage {
  uint8_t rsa_key[kMaxTestRSAKeyLength];
  uint8_t rsa_key_iv[wvcdm::KEY_IV_SIZE];
  size_t rsa_key_length;
  uint32_t nonce;
};

// Increment counter for AES-CTR.  The CENC spec specifies we increment only
// the low 64 bits of the IV counter, and leave the high 64 bits alone.  This
// is different from the OpenSSL implementation, so we implement the CTR loop
// ourselves.
void ctr128_inc64(int64_t increaseBy, uint8_t* iv);

// Some compilers don't like the macro htonl within an ASSERT_EQ.
uint32_t htonl_fnc(uint32_t x);

// Prints error string from openSSL
void dump_openssl_error();

class Session {
 public:
  Session();
  ~Session();

  uint32_t get_nonce() { return nonce_; }

  uint32_t session_id() { return (uint32_t)session_id_; }

  void open();
  void close();
  void SetSessionId(uint32_t session_id);

  uint32_t GetOecSessionId() { return session_id_; }
  void GenerateNonce(uint32_t* nonce, int* error_counter = NULL);
  void FillDefaultContext(vector<uint8_t>* mac_context,
                          vector<uint8_t>* enc_context);
  void GenerateDerivedKeysFromKeybox();
  void GenerateDerivedKeysFromSessionKey();
  void GenerateTestSessionKeys();
  void LoadTestKeys(const std::string& pst = "", bool new_mac_keys = true);
  void VerifyTestKeys();
  void RefreshTestKeys(const size_t key_count, uint32_t control_bits,
                       uint32_t nonce, OEMCryptoResult expected_result);
  void SetKeyId(int index, const string& key_id);
  void FillSimpleMessage(uint32_t duration, uint32_t control, uint32_t nonce,
                         const std::string& pst = "");

  void FillRefreshMessage(size_t key_count, uint32_t control_bits,
                          uint32_t nonce);
  void EncryptAndSign();
  void EncryptMessage(RSAPrivateKeyMessage* data,
                      RSAPrivateKeyMessage* encrypted);

  template <typename T>
      void ServerSignMessage(const T& data, std::vector<uint8_t>* signature);

  void ClientSignMessage(const vector<uint8_t>& data,
                         std::vector<uint8_t>* signature);
  void FillKeyArray(const MessageData& data, OEMCrypto_KeyObject* key_array);
  void FillRefreshArray(OEMCrypto_KeyRefreshObject* key_array,
                        size_t key_count);
  void EncryptCTR(
      const vector<uint8_t>& in_buffer, const uint8_t *key,
      const uint8_t* starting_iv, vector<uint8_t>* out_buffer);
  void TestDecryptCTR(bool select_key_first = true,
                      OEMCryptoResult expected_result = OEMCrypto_SUCCESS);
  void MakeRSACertificate(
      struct RSAPrivateKeyMessage* encrypted, std::vector<uint8_t>* signature,
      uint32_t allowed_schemes, const vector<uint8_t>& rsa_key);
  void RewrapRSAKey(const struct RSAPrivateKeyMessage& encrypted,
                    const std::vector<uint8_t>& signature,
                    vector<uint8_t>* wrapped_key, bool force);
  void PreparePublicKey(const uint8_t* rsa_key = NULL,
                        size_t rsa_key_length = 0);
  static bool VerifyPSSSignature(
      EVP_PKEY* pkey, const uint8_t* message, size_t message_length,
      const uint8_t* signature, size_t signature_length);
  void VerifyRSASignature(
      const vector<uint8_t>& message, const uint8_t* signature,
      size_t signature_length, RSA_Padding_Scheme padding_scheme);
  bool GenerateRSASessionKey(vector<uint8_t>* enc_session_key);
  void InstallRSASessionTestKey(const vector<uint8_t>& wrapped_rsa_key);
  void DisallowDeriveKeys();
  void GenerateReport(const std::string& pst, bool expect_success = true,
                      Session* other = 0);
  OEMCrypto_PST_Report* pst_report();
  void DeleteEntry(const std::string& pst);
  void ForceDeleteEntry(const std::string& pst);

  MessageData& license() { return license_; }
  MessageData& encrypted_license() { return encrypted_license_; }

  const uint8_t* message_ptr();

  OEMCrypto_KeyObject* key_array() { return key_array_; }
  std::vector<uint8_t>& signature() { return signature_; }

 private:
  bool open_;
  bool forced_session_id_;
  OEMCrypto_SESSION session_id_;
  vector<uint8_t> mac_key_server_;
  vector<uint8_t> mac_key_client_;
  vector<uint8_t> enc_key_;
  uint32_t nonce_;
  RSA* public_rsa_;
  vector<uint8_t> pst_report_buffer_;
  MessageData license_;
  MessageData encrypted_license_;
  OEMCrypto_KeyObject key_array_[kNumKeys];
  std::vector<uint8_t> signature_;
};

}  // namespace wvoec

#endif  // CDM_OEC_SESSION_UTIL_H_
