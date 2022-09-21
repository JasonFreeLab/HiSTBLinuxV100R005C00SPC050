// Copyright 2016 Google Inc. All Rights Reserved.
//
// OEMCrypto unit tests
//

#include "oec_session_util.h"

#include <arpa/inet.h>  // needed for ntoh()
#include <openssl/aes.h>
#include <openssl/err.h>
#include <openssl/hmac.h>
#include <openssl/x509.h>
#include <stdint.h>

#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>

#include "log.h"
#include "oec_device_features.h"
#include "oec_test_data.h"
#include "oemcrypto_key_mock.h"
#include "OEMCryptoCENC.h"
#include "string_conversions.h"
#include "wv_cdm_constants.h"
#include "wv_keybox.h"

using namespace std;

// GTest requires PrintTo to be in the same namespace as the thing it prints,
// which is std::vector in this case.
namespace std {

void PrintTo(const vector<uint8_t>& value, ostream* os) {
  *os << wvcdm::b2a_hex(value);
}

void PrintTo(const PatternTestVariant& param, ostream* os) {
  *os << ((param.mode == OEMCrypto_CipherMode_CTR) ? "CTR mode" : "CBC mode")
      << ", encrypt=" << param.pattern.encrypt
      << ", skip=" << param.pattern.skip;
}

}  // namespace std

namespace wvoec {

// Increment counter for AES-CTR.  The CENC spec specifies we increment only
// the low 64 bits of the IV counter, and leave the high 64 bits alone.  This
// is different from the OpenSSL implementation, so we implement the CTR loop
// ourselves.
void ctr128_inc64(int64_t increaseBy, uint8_t* iv) {
  ASSERT_NE(static_cast<void*>(NULL), iv);
  uint64_t* counterBuffer = reinterpret_cast<uint64_t*>(&iv[8]);
  (*counterBuffer) =
      wvcdm::htonll64(wvcdm::ntohll64(*counterBuffer) + increaseBy);
}

// Some compilers don't like the macro htonl within an ASSERT_EQ.
uint32_t htonl_fnc(uint32_t x) { return htonl(x); }

void dump_openssl_error() {
  while (unsigned long err = ERR_get_error()) {
    char buffer[120];
    ERR_error_string_n(err, buffer, sizeof(buffer));
    cout << "openssl error -- " << buffer << "\n";
  }
}

Session::Session()
    : open_(false),
      forced_session_id_(false),
      session_id_(0),
      mac_key_server_(wvcdm::MAC_KEY_SIZE),
      mac_key_client_(wvcdm::MAC_KEY_SIZE),
      enc_key_(wvcdm::KEY_SIZE),
      public_rsa_(0) {}

Session::~Session() {
  if (!forced_session_id_ && open_) close();
  if (public_rsa_) RSA_free(public_rsa_);
}

void Session::open() {
  EXPECT_FALSE(forced_session_id_);
  EXPECT_FALSE(open_);
  ASSERT_EQ(OEMCrypto_SUCCESS, OEMCrypto_OpenSession(&session_id_));
  open_ = true;
}

void Session::SetSessionId(uint32_t session_id) {
  EXPECT_FALSE(open_);
  session_id_ = session_id;
  forced_session_id_ = true;
}

void Session::close() {
  EXPECT_TRUE(open_ || forced_session_id_);
  if (open_) {
    ASSERT_EQ(OEMCrypto_SUCCESS, OEMCrypto_CloseSession(session_id_));
  }
  forced_session_id_ = false;
  open_ = false;
}

void Session::GenerateNonce(uint32_t* nonce, int* error_counter) {
  if (OEMCrypto_SUCCESS == OEMCrypto_GenerateNonce(session_id(), nonce)) {
    return;
  }
  if (error_counter) {
    (*error_counter)++;
  } else {
    sleep(1);  // wait a second, then try again.
    ASSERT_EQ(OEMCrypto_SUCCESS,
              OEMCrypto_GenerateNonce(session_id(), nonce));
  }
}

void Session::FillDefaultContext(vector<uint8_t>* mac_context,
                                 vector<uint8_t>* enc_context) {
  /* Context strings
   * These context strings are normally created by the CDM layer
   * from a license request message.
   * They are used to test MAC and ENC key generation.
   */
  *mac_context = wvcdm::a2b_hex(
      "41555448454e5449434154494f4e000a4c08001248000000020000101907d9ff"
      "de13aa95c122678053362136bdf8408f8276e4c2d87ec52b61aa1b9f646e5873"
      "4930acebe899b3e464189a14a87202fb02574e70640bd22ef44b2d7e3912250a"
      "230a14080112100915007caa9b5931b76a3a85f046523e10011a093938373635"
      "34333231180120002a0c31383836373837343035000000000200");
  *enc_context = wvcdm::a2b_hex(
      "454e4352595054494f4e000a4c08001248000000020000101907d9ffde13aa95"
      "c122678053362136bdf8408f8276e4c2d87ec52b61aa1b9f646e58734930aceb"
      "e899b3e464189a14a87202fb02574e70640bd22ef44b2d7e3912250a230a1408"
      "0112100915007caa9b5931b76a3a85f046523e10011a09393837363534333231"
      "180120002a0c31383836373837343035000000000080");
}

void Session::GenerateDerivedKeysFromKeybox() {
  GenerateNonce(&nonce_);
  vector<uint8_t> mac_context;
  vector<uint8_t> enc_context;
  FillDefaultContext(&mac_context, &enc_context);
  ASSERT_EQ(OEMCrypto_SUCCESS,
            OEMCrypto_GenerateDerivedKeys(session_id(), &mac_context[0],
                                          mac_context.size(), &enc_context[0],
                                          enc_context.size()));

  // Expected MAC and ENC keys generated from context strings
  // with test keybox "installed".
  mac_key_server_ = wvcdm::a2b_hex(
      "3CFD60254786AF350B353B4FBB700AB382558400356866BA16C256BCD8C502BF");
  mac_key_client_ = wvcdm::a2b_hex(
      "A9DE7B3E4E199ED8D1FBC29CD6B4C772CC4538C8B0D3E208B3E76F2EC0FD6F47");
  enc_key_ = wvcdm::a2b_hex("D0BFC35DA9E33436E81C4229E78CB9F4");
}

void Session::GenerateDerivedKeysFromSessionKey() {
  // Uses test certificate.
  GenerateNonce(&nonce_);
  vector<uint8_t> enc_session_key;
  PreparePublicKey();
  ASSERT_TRUE(GenerateRSASessionKey(&enc_session_key));
  vector<uint8_t> mac_context;
  vector<uint8_t> enc_context;
  FillDefaultContext(&mac_context, &enc_context);
  ASSERT_EQ(OEMCrypto_SUCCESS,
            OEMCrypto_DeriveKeysFromSessionKey(
                session_id(), &enc_session_key[0], enc_session_key.size(),
                &mac_context[0], mac_context.size(), &enc_context[0],
                enc_context.size()));

  // Expected MAC and ENC keys generated from context strings
  // with RSA certificate "installed".
  mac_key_server_ = wvcdm::a2b_hex(
      "1E451E59CB663DA1646194DD28880788ED8ED2EFF913CBD6A0D535D1D5A90381");
  mac_key_client_ = wvcdm::a2b_hex(
      "F9AAE74690909F2207B53B13307FCA096CA8C49CC6DFE3659873CB952889A74B");
  enc_key_ = wvcdm::a2b_hex("CB477D09014D72C9B8DCE76C33EA43B3");
}

void Session::GenerateTestSessionKeys() {
  if (global_features.derive_key_method == DeviceFeatures::LOAD_TEST_RSA_KEY) {
    GenerateDerivedKeysFromSessionKey();
  } else {
    GenerateDerivedKeysFromKeybox();
  }
}

void Session::LoadTestKeys(const std::string& pst, bool new_mac_keys) {
  uint8_t* pst_ptr = NULL;
  if (pst.length() > 0) {
    pst_ptr = encrypted_license_.pst;
  }
  if (new_mac_keys) {
    ASSERT_EQ(OEMCrypto_SUCCESS,
              OEMCrypto_LoadKeys(
                  session_id(), message_ptr(), sizeof(MessageData),
                  &signature_[0], signature_.size(),
                  encrypted_license_.mac_key_iv, encrypted_license_.mac_keys,
                  kNumKeys, key_array_, pst_ptr, pst.length()));
    // Update new generated keys.
    memcpy(&mac_key_server_[0], license_.mac_keys, wvcdm::MAC_KEY_SIZE);
    memcpy(&mac_key_client_[0], license_.mac_keys + wvcdm::MAC_KEY_SIZE,
           wvcdm::MAC_KEY_SIZE);
  } else {
    ASSERT_EQ(
        OEMCrypto_SUCCESS,
        OEMCrypto_LoadKeys(session_id(), message_ptr(), sizeof(MessageData),
                           &signature_[0], signature_.size(), NULL, NULL,
                           kNumKeys, key_array_, pst_ptr, pst.length()));
  }
  VerifyTestKeys();
}

void Session::VerifyTestKeys() {
  for (unsigned int i = 0; i < kNumKeys; i++) {
    KeyControlBlock block;
    size_t size = sizeof(block);
    OEMCryptoResult sts = OEMCrypto_QueryKeyControl(
      session_id(), license_.keys[i].key_id, license_.keys[i].key_id_length,
      reinterpret_cast<uint8_t*>(&block), &size);
    if (sts != OEMCrypto_ERROR_NOT_IMPLEMENTED) {
      ASSERT_EQ(OEMCrypto_SUCCESS, sts);
      ASSERT_EQ(sizeof(block), size);
      // control duration and bits stored in network byte order. For printing
      // we change to host byte order.
      ASSERT_EQ((htonl_fnc(license_.keys[i].control.duration)),
                (htonl_fnc(block.duration))) << "For key " << i;
      ASSERT_EQ(htonl_fnc(license_.keys[i].control.control_bits),
                htonl_fnc(block.control_bits)) << "For key " << i;
    }
  }
}

void Session::RefreshTestKeys(const size_t key_count,
                              uint32_t control_bits, uint32_t nonce,
                              OEMCryptoResult expected_result) {
  // Note: we store the message in encrypted_license_, but the refresh key
  // message is not actually encrypted.  It is, however, signed.
  FillRefreshMessage(key_count, control_bits, nonce);
  ServerSignMessage(encrypted_license_, &signature_);
  OEMCrypto_KeyRefreshObject key_array[key_count];
  FillRefreshArray(key_array, key_count);
  OEMCryptoResult sts = OEMCrypto_RefreshKeys(
      session_id(), message_ptr(), sizeof(MessageData), &signature_[0],
      signature_.size(), key_count, key_array);
  ASSERT_EQ(expected_result, sts);

  ASSERT_NO_FATAL_FAILURE(TestDecryptCTR());
  sleep(kShortSleep);  //  Should still be valid key.
  ASSERT_NO_FATAL_FAILURE(TestDecryptCTR(false));
  sleep(kShortSleep + kLongSleep);  // Should be after first expiration.
  if (expected_result == OEMCrypto_SUCCESS) {
    ASSERT_NO_FATAL_FAILURE(TestDecryptCTR(false, OEMCrypto_SUCCESS));
  } else {
    ASSERT_NO_FATAL_FAILURE(
        TestDecryptCTR(false, OEMCrypto_ERROR_UNKNOWN_FAILURE));
  }
}

void Session::SetKeyId(int index, const string& key_id) {
  MessageKeyData& key = license_.keys[index];
  key.key_id_length = key_id.length();
  ASSERT_LE(key.key_id_length, kTestKeyIdMaxLength);
  memcpy(key.key_id, key_id.data(), key.key_id_length);
}

void Session::FillSimpleMessage(
    uint32_t duration, uint32_t control, uint32_t nonce,
    const std::string& pst) {
  EXPECT_EQ(OEMCrypto_SUCCESS,
            OEMCrypto_GetRandom(license_.mac_key_iv,
                                sizeof(license_.mac_key_iv)));
  EXPECT_EQ(OEMCrypto_SUCCESS,
            OEMCrypto_GetRandom(license_.mac_keys, sizeof(license_.mac_keys)));
  for (unsigned int i = 0; i < kNumKeys; i++) {
    memset(license_.keys[i].key_id, 0, kTestKeyIdMaxLength);
    license_.keys[i].key_id_length = kDefaultKeyIdLength;
    memset(license_.keys[i].key_id, i, license_.keys[i].key_id_length);
    EXPECT_EQ(OEMCrypto_SUCCESS,
              OEMCrypto_GetRandom(license_.keys[i].key_data,
                                  sizeof(license_.keys[i].key_data)));
    license_.keys[i].key_data_length = wvcdm::KEY_SIZE;
    EXPECT_EQ(OEMCrypto_SUCCESS,
              OEMCrypto_GetRandom(license_.keys[i].key_iv,
                                  sizeof(license_.keys[i].key_iv)));
    EXPECT_EQ(OEMCrypto_SUCCESS,
              OEMCrypto_GetRandom(license_.keys[i].control_iv,
                                  sizeof(license_.keys[i].control_iv)));
    if (control & wvoec_mock::kControlSecurityPatchLevelMask) {
      memcpy(license_.keys[i].control.verification, "kc11", 4);
    } else if (control & wvoec_mock::kControlRequireAntiRollbackHardware) {
      memcpy(license_.keys[i].control.verification, "kc10", 4);
    } else if (control & (wvoec_mock::kControlHDCPVersionMask |
                          wvoec_mock::kControlReplayMask)) {
      memcpy(license_.keys[i].control.verification, "kc09", 4);
    } else {
      memcpy(license_.keys[i].control.verification, "kctl", 4);
    }
    license_.keys[i].control.duration = htonl(duration);
    license_.keys[i].control.nonce = htonl(nonce);
    license_.keys[i].control.control_bits = htonl(control);
    license_.keys[i].cipher_mode = OEMCrypto_CipherMode_CTR;
  }
  memcpy(license_.pst, pst.c_str(), min(sizeof(license_.pst), pst.length()));
}

void Session::FillRefreshMessage(size_t key_count, uint32_t control_bits,
                                 uint32_t nonce) {
  for (unsigned int i = 0; i < key_count; i++) {
    encrypted_license_.keys[i].key_id_length = license_.keys[i].key_id_length;
    memcpy(encrypted_license_.keys[i].key_id, license_.keys[i].key_id,
           encrypted_license_.keys[i].key_id_length);
    memcpy(encrypted_license_.keys[i].control.verification, "kctl", 4);
    encrypted_license_.keys[i].control.duration = htonl(kLongDuration);
    encrypted_license_.keys[i].control.nonce = htonl(nonce);
    encrypted_license_.keys[i].control.control_bits = htonl(control_bits);
  }
}

void Session::EncryptAndSign() {
  encrypted_license_ = license_;

  uint8_t iv_buffer[16];
  memcpy(iv_buffer, &license_.mac_key_iv[0], wvcdm::KEY_IV_SIZE);
  AES_KEY aes_key;
  AES_set_encrypt_key(&enc_key_[0], 128, &aes_key);
  AES_cbc_encrypt(&license_.mac_keys[0], &encrypted_license_.mac_keys[0],
                  2 * wvcdm::MAC_KEY_SIZE, &aes_key, iv_buffer, AES_ENCRYPT);

  for (unsigned int i = 0; i < kNumKeys; i++) {
    memcpy(iv_buffer, &license_.keys[i].control_iv[0], wvcdm::KEY_IV_SIZE);
    AES_set_encrypt_key(&license_.keys[i].key_data[0], 128, &aes_key);
    AES_cbc_encrypt(
        reinterpret_cast<const uint8_t*>(&license_.keys[i].control),
        reinterpret_cast<uint8_t*>(&encrypted_license_.keys[i].control),
        wvcdm::KEY_SIZE, &aes_key, iv_buffer, AES_ENCRYPT);

    memcpy(iv_buffer, &license_.keys[i].key_iv[0], wvcdm::KEY_IV_SIZE);
    AES_set_encrypt_key(&enc_key_[0], 128, &aes_key);
    AES_cbc_encrypt(&license_.keys[i].key_data[0],
                    &encrypted_license_.keys[i].key_data[0],
                    license_.keys[i].key_data_length, &aes_key, iv_buffer,
                    AES_ENCRYPT);
  }
  memcpy(encrypted_license_.pst, license_.pst, sizeof(license_.pst));
  ServerSignMessage(encrypted_license_, &signature_);
  FillKeyArray(encrypted_license_, key_array_);
}

void Session::EncryptMessage(RSAPrivateKeyMessage* data,
                             RSAPrivateKeyMessage* encrypted) {
  *encrypted = *data;
  size_t padding = wvcdm::KEY_SIZE - (data->rsa_key_length % wvcdm::KEY_SIZE);
  memset(data->rsa_key + data->rsa_key_length, static_cast<uint8_t>(padding),
         padding);
  encrypted->rsa_key_length = data->rsa_key_length + padding;
  uint8_t iv_buffer[16];
  memcpy(iv_buffer, &data->rsa_key_iv[0], wvcdm::KEY_IV_SIZE);
  AES_KEY aes_key;
  AES_set_encrypt_key(&enc_key_[0], 128, &aes_key);
  AES_cbc_encrypt(&data->rsa_key[0], &encrypted->rsa_key[0],
                  encrypted->rsa_key_length, &aes_key, iv_buffer,
                  AES_ENCRYPT);
}

template <typename T>
void Session::ServerSignMessage(const T& data,
                                std::vector<uint8_t>* signature) {
  signature->assign(SHA256_DIGEST_LENGTH, 0);
  unsigned int md_len = SHA256_DIGEST_LENGTH;
  HMAC(EVP_sha256(), &mac_key_server_[0], mac_key_server_.size(),
       reinterpret_cast<const uint8_t*>(&data), sizeof(data),
       &(signature->front()), &md_len);
}

void Session::ClientSignMessage(const vector<uint8_t>& data,
                                std::vector<uint8_t>* signature) {
  signature->assign(SHA256_DIGEST_LENGTH, 0);
  unsigned int md_len = SHA256_DIGEST_LENGTH;
  HMAC(EVP_sha256(), &mac_key_client_[0], mac_key_client_.size(),
       &(data.front()), data.size(), &(signature->front()), &md_len);
}

void Session::FillKeyArray(const MessageData& data,
                           OEMCrypto_KeyObject* key_array) {
  for (unsigned int i = 0; i < kNumKeys; i++) {
    key_array[i].key_id = data.keys[i].key_id;
    key_array[i].key_id_length = data.keys[i].key_id_length;
    key_array[i].key_data_iv = data.keys[i].key_iv;
    key_array[i].key_data = data.keys[i].key_data;
    key_array[i].key_data_length = data.keys[i].key_data_length;
    key_array[i].key_control_iv = data.keys[i].control_iv;
    key_array[i].key_control =
        reinterpret_cast<const uint8_t*>(&data.keys[i].control);
    key_array[i].cipher_mode = data.keys[i].cipher_mode;
  }
}

void Session::FillRefreshArray(OEMCrypto_KeyRefreshObject* key_array,
                               size_t key_count) {
  for (size_t i = 0; i < key_count; i++) {
    if (key_count > 1) {
      key_array[i].key_id = encrypted_license_.keys[i].key_id;
      key_array[i].key_id_length = encrypted_license_.keys[i].key_id_length;
    } else {
      key_array[i].key_id = NULL;
      key_array[i].key_id_length = 0;
    }
    key_array[i].key_control_iv = NULL;
    key_array[i].key_control =
        reinterpret_cast<const uint8_t*>(&encrypted_license_.keys[i].control);
  }
}

void Session::EncryptCTR(
    const vector<uint8_t>& in_buffer, const uint8_t *key,
    const uint8_t* starting_iv, vector<uint8_t>* out_buffer) {
  ASSERT_NE(static_cast<void*>(NULL), key);
  ASSERT_NE(static_cast<void*>(NULL), starting_iv);
  ASSERT_NE(static_cast<void*>(NULL), out_buffer);
  AES_KEY aes_key;
  AES_set_encrypt_key(key, AES_BLOCK_SIZE * 8, &aes_key);
  out_buffer->resize(in_buffer.size());

  uint8_t iv[AES_BLOCK_SIZE];  // Current iv.

  memcpy(iv, &starting_iv[0], AES_BLOCK_SIZE);
  size_t l = 0;  // byte index into encrypted subsample.
  while (l < in_buffer.size()) {
    uint8_t aes_output[AES_BLOCK_SIZE];
    AES_encrypt(iv, aes_output, &aes_key);
    for (size_t n = 0; n < AES_BLOCK_SIZE && l < in_buffer.size(); n++, l++) {
      (*out_buffer)[l] = aes_output[n] ^ in_buffer[l];
    }
    ctr128_inc64(1, iv);
  }
}

void Session::TestDecryptCTR(bool select_key_first,
                             OEMCryptoResult expected_result) {
  OEMCryptoResult sts;
  if (select_key_first) {
    // Select the key (from FillSimpleMessage)
    sts = OEMCrypto_SelectKey(session_id(), license_.keys[0].key_id,
                              license_.keys[0].key_id_length);
    ASSERT_EQ(OEMCrypto_SUCCESS, sts);
  }

  vector<uint8_t> unencryptedData(256);
  for(size_t i=0; i < unencryptedData.size(); i++) unencryptedData[i] = i % 256;
  EXPECT_EQ(OEMCrypto_SUCCESS,
            OEMCrypto_GetRandom(&unencryptedData[0], unencryptedData.size()));
  vector<uint8_t> encryptionIv(wvcdm::KEY_IV_SIZE);
  EXPECT_EQ(OEMCrypto_SUCCESS,
            OEMCrypto_GetRandom(&encryptionIv[0], wvcdm::KEY_IV_SIZE));
  vector<uint8_t> encryptedData(unencryptedData.size());
  EncryptCTR(unencryptedData, license_.keys[0].key_data, &encryptionIv[0],
             &encryptedData);

  // Describe the output
  vector<uint8_t> outputBuffer(256);
  OEMCrypto_DestBufferDesc destBuffer;
  destBuffer.type = OEMCrypto_BufferType_Clear;
  destBuffer.buffer.clear.address = outputBuffer.data();
  destBuffer.buffer.clear.max_length = outputBuffer.size();
  OEMCrypto_CENCEncryptPatternDesc pattern;
  pattern.encrypt = 0;
  pattern.skip = 0;
  pattern.offset = 0;
  // Decrypt the data
  sts = OEMCrypto_DecryptCENC(
      session_id(), &encryptedData[0], encryptedData.size(), true,
      &encryptionIv[0], 0, &destBuffer, &pattern,
      OEMCrypto_FirstSubsample | OEMCrypto_LastSubsample);
  // We only have a few errors that we test are reported.
  if (expected_result == OEMCrypto_SUCCESS) {  // No error.
    ASSERT_EQ(OEMCrypto_SUCCESS, sts);
    ASSERT_EQ(unencryptedData, outputBuffer);
  } else if (expected_result == OEMCrypto_ERROR_KEY_EXPIRED) {
    // Report stale keys.
    ASSERT_EQ(OEMCrypto_ERROR_KEY_EXPIRED, sts);
    ASSERT_NE(unencryptedData, outputBuffer);
  } else if (expected_result == OEMCrypto_ERROR_INSUFFICIENT_HDCP) {
    // Report HDCP errors.
    ASSERT_EQ(OEMCrypto_ERROR_INSUFFICIENT_HDCP, sts);
    ASSERT_NE(unencryptedData, outputBuffer);
  } else {
    // OEM's can fine tune other error codes for debugging.
    ASSERT_NE(OEMCrypto_SUCCESS, sts);
    ASSERT_NE(unencryptedData, outputBuffer);
  }
}

void Session::MakeRSACertificate(
    struct RSAPrivateKeyMessage* encrypted, std::vector<uint8_t>* signature,
    uint32_t allowed_schemes, const vector<uint8_t>& rsa_key) {
  // Dummy context for testing signature generation.
  vector<uint8_t> context = wvcdm::a2b_hex(
      "0a4c08001248000000020000101907d9ffde13aa95c122678053362136bdf840"
      "8f8276e4c2d87ec52b61aa1b9f646e58734930acebe899b3e464189a14a87202"
      "fb02574e70640bd22ef44b2d7e3912250a230a14080112100915007caa9b5931"
      "b76a3a85f046523e10011a09393837363534333231180120002a0c3138383637"
      "38373430350000");

  OEMCryptoResult sts;

  // Generate signature
  size_t gen_signature_length = 0;
  sts = OEMCrypto_GenerateSignature(session_id(), &context[0], context.size(),
                                    NULL, &gen_signature_length);
  ASSERT_EQ(OEMCrypto_ERROR_SHORT_BUFFER, sts);
  ASSERT_EQ(static_cast<size_t>(32), gen_signature_length);
  vector<uint8_t> gen_signature(gen_signature_length);
  sts = OEMCrypto_GenerateSignature(session_id(), &context[0], context.size(),
                                    &gen_signature[0], &gen_signature_length);
  ASSERT_EQ(OEMCrypto_SUCCESS, sts);
  std::vector<uint8_t> expected_signature;
  ClientSignMessage(context, &expected_signature);
  ASSERT_EQ(expected_signature, gen_signature);

  // Rewrap Canned Response

  // In the real world, the signature above would just have been used to
  // contact the certificate provisioning server to get this response.

  struct RSAPrivateKeyMessage message;
  if (allowed_schemes != kSign_RSASSA_PSS) {
    uint32_t algorithm_n = htonl(allowed_schemes);
    memcpy(message.rsa_key, "SIGN", 4);
    memcpy(message.rsa_key + 4, &algorithm_n, 4);
    memcpy(message.rsa_key + 8, rsa_key.data(), rsa_key.size());
    message.rsa_key_length = 8 + rsa_key.size();
  } else {
    memcpy(message.rsa_key, rsa_key.data(), rsa_key.size());
    message.rsa_key_length = rsa_key.size();
  }
  EXPECT_EQ(OEMCrypto_SUCCESS,
            OEMCrypto_GetRandom(message.rsa_key_iv, wvcdm::KEY_IV_SIZE));
  message.nonce = nonce_;

  EncryptMessage(&message, encrypted);
  ServerSignMessage(*encrypted, signature);
}

void Session::RewrapRSAKey(const struct RSAPrivateKeyMessage& encrypted,
                           const std::vector<uint8_t>& signature,
                           vector<uint8_t>* wrapped_key, bool force) {
  size_t wrapped_key_length = 0;
  const uint8_t* message_ptr = reinterpret_cast<const uint8_t*>(&encrypted);

  ASSERT_EQ(OEMCrypto_ERROR_SHORT_BUFFER,
            OEMCrypto_RewrapDeviceRSAKey(
                session_id(), message_ptr, sizeof(encrypted), &signature[0],
                signature.size(), &encrypted.nonce, encrypted.rsa_key,
                encrypted.rsa_key_length, encrypted.rsa_key_iv, NULL,
                &wrapped_key_length));
  wrapped_key->clear();
  wrapped_key->assign(wrapped_key_length, 0);
  OEMCryptoResult sts = OEMCrypto_RewrapDeviceRSAKey(
      session_id(), message_ptr, sizeof(encrypted), &signature[0],
      signature.size(), &encrypted.nonce, encrypted.rsa_key,
      encrypted.rsa_key_length, encrypted.rsa_key_iv, &(wrapped_key->front()),
      &wrapped_key_length);
  if (force) {
    ASSERT_EQ(OEMCrypto_SUCCESS, sts);
  }
  if (OEMCrypto_SUCCESS != sts) {
    wrapped_key->clear();
  }
}

void Session::PreparePublicKey(const uint8_t* rsa_key,
                               size_t rsa_key_length) {
  if (rsa_key == NULL) {
    rsa_key = kTestRSAPKCS8PrivateKeyInfo2_2048;
    rsa_key_length = sizeof(kTestRSAPKCS8PrivateKeyInfo2_2048);
  }
  uint8_t* p = const_cast<uint8_t*>(rsa_key);
  BIO* bio = BIO_new_mem_buf(p, rsa_key_length);
  ASSERT_TRUE(NULL != bio);
  PKCS8_PRIV_KEY_INFO* pkcs8_pki = d2i_PKCS8_PRIV_KEY_INFO_bio(bio, NULL);
  ASSERT_TRUE(NULL != pkcs8_pki);
  EVP_PKEY* evp = NULL;
  evp = EVP_PKCS82PKEY(pkcs8_pki);
  ASSERT_TRUE(NULL != evp);
  if (public_rsa_) RSA_free(public_rsa_);
  public_rsa_ = EVP_PKEY_get1_RSA(evp);
  EVP_PKEY_free(evp);
  PKCS8_PRIV_KEY_INFO_free(pkcs8_pki);
  BIO_free(bio);
  if (!public_rsa_) {
    cout << "d2i_RSAPrivateKey failed. ";
    dump_openssl_error();
    ASSERT_TRUE(false);
  }
  switch (RSA_check_key(public_rsa_)) {
  case 1:  // valid.
    ASSERT_TRUE(true);
    return;
  case 0:  // not valid.
    cout << "[rsa key not valid] ";
    dump_openssl_error();
    ASSERT_TRUE(false);
  default:  // -1 == check failed.
    cout << "[error checking rsa key] ";
    dump_openssl_error();
    ASSERT_TRUE(false);
  }
}

bool Session::VerifyPSSSignature(
    EVP_PKEY* pkey, const uint8_t* message, size_t message_length,
    const uint8_t* signature, size_t signature_length) {
  EVP_MD_CTX ctx;
  EVP_MD_CTX_init(&ctx);
  EVP_PKEY_CTX* pctx = NULL;

  if (EVP_DigestVerifyInit(&ctx, &pctx, EVP_sha1(), NULL /* no ENGINE */,
                           pkey) != 1) {
    LOGE("EVP_DigestVerifyInit failed in VerifyPSSSignature");
    goto err;
  }

  if (EVP_PKEY_CTX_set_signature_md(pctx, EVP_sha1()) != 1) {
    LOGE("EVP_PKEY_CTX_set_signature_md failed in VerifyPSSSignature");
    goto err;
  }

  if (EVP_PKEY_CTX_set_rsa_padding(pctx, RSA_PKCS1_PSS_PADDING) != 1) {
    LOGE("EVP_PKEY_CTX_set_rsa_padding failed in VerifyPSSSignature");
    goto err;
  }

  if (EVP_PKEY_CTX_set_rsa_pss_saltlen(pctx, SHA_DIGEST_LENGTH) != 1) {
    LOGE("EVP_PKEY_CTX_set_rsa_pss_saltlen failed in VerifyPSSSignature");
    goto err;
  }

  if (EVP_DigestVerifyUpdate(&ctx, message, message_length) != 1) {
    LOGE("EVP_DigestVerifyUpdate failed in VerifyPSSSignature");
    goto err;
  }

  if (EVP_DigestVerifyFinal(&ctx, const_cast<uint8_t*>(signature),
                            signature_length) != 1) {
    LOGE(
        "EVP_DigestVerifyFinal failed in VerifyPSSSignature. (Probably a bad "
        "signature.)");
    goto err;
  }

  EVP_MD_CTX_cleanup(&ctx);
  return true;

 err:
  dump_openssl_error();
  EVP_MD_CTX_cleanup(&ctx);
  return false;
}

void Session::VerifyRSASignature(
    const vector<uint8_t>& message, const uint8_t* signature,
    size_t signature_length, RSA_Padding_Scheme padding_scheme) {
  EXPECT_TRUE(NULL != public_rsa_)
      << "No public RSA key loaded in test code.\n";
  EXPECT_EQ(static_cast<size_t>(RSA_size(public_rsa_)), signature_length)
      << "Signature size is wrong. " << signature_length << ", should be "
      << RSA_size(public_rsa_) << "\n";

  if (padding_scheme == kSign_RSASSA_PSS) {
    EVP_PKEY* pkey = EVP_PKEY_new();
    ASSERT_TRUE(EVP_PKEY_set1_RSA(pkey, public_rsa_) == 1);

    const bool ok = VerifyPSSSignature(pkey, &message[0], message.size(),
                                       signature, signature_length);
    EVP_PKEY_free(pkey);
    EXPECT_TRUE(ok) << "PSS signature check failed.";
  } else if (padding_scheme == kSign_PKCS1_Block1) {
    vector<uint8_t> padded_digest(signature_length);
    int size;
    // RSA_public_decrypt decrypts the signature, and then verifies that
    // it was padded with RSA PKCS1 padding.
    size = RSA_public_decrypt(signature_length, signature, &padded_digest[0],
                              public_rsa_, RSA_PKCS1_PADDING);
    EXPECT_GT(size, 0);
    padded_digest.resize(size);
    EXPECT_EQ(message, padded_digest);
  } else {
    EXPECT_TRUE(false) << "Padding scheme not supported.";
  }
}

bool Session::GenerateRSASessionKey(vector<uint8_t>* enc_session_key) {
  if (!public_rsa_) {
    cout << "No public RSA key loaded in test code.\n";
    return false;
  }
  vector<uint8_t> session_key =
      wvcdm::a2b_hex("6fa479c731d2770b6a61a5d1420bb9d1");
  enc_session_key->assign(RSA_size(public_rsa_), 0);
  int status = RSA_public_encrypt(session_key.size(), &session_key[0],
                                  &(enc_session_key->front()), public_rsa_,
                                  RSA_PKCS1_OAEP_PADDING);
  int size = static_cast<int>(RSA_size(public_rsa_));
  if (status != size) {
    cout << "GenerateRSASessionKey error encrypting session key. ";
    dump_openssl_error();
    return false;
  }
  return true;
}

void Session::InstallRSASessionTestKey(
    const vector<uint8_t>& wrapped_rsa_key) {
  ASSERT_EQ(OEMCrypto_SUCCESS,
            OEMCrypto_LoadDeviceRSAKey(session_id(), &wrapped_rsa_key[0],
                                       wrapped_rsa_key.size()));
  GenerateDerivedKeysFromSessionKey();
}

void Session::DisallowDeriveKeys() {
  GenerateNonce(&nonce_);
  vector<uint8_t> enc_session_key;
  PreparePublicKey();
  ASSERT_TRUE(GenerateRSASessionKey(&enc_session_key));
  vector<uint8_t> mac_context;
  vector<uint8_t> enc_context;
  FillDefaultContext(&mac_context, &enc_context);
  ASSERT_NE(OEMCrypto_SUCCESS,
            OEMCrypto_DeriveKeysFromSessionKey(
                session_id(), &enc_session_key[0], enc_session_key.size(),
                &mac_context[0], mac_context.size(), &enc_context[0],
                enc_context.size()));
}

void Session::GenerateReport(
    const std::string& pst, bool expect_success, Session* other) {
  if (other) {  // If other is specified, copy mac keys.
    mac_key_server_ = other->mac_key_server_;
    mac_key_client_ = other->mac_key_client_;
  }
  size_t length = 0;
  OEMCryptoResult sts = OEMCrypto_ReportUsage(
      session_id(), reinterpret_cast<const uint8_t*>(pst.c_str()), pst.length(),
      pst_report(), &length);
  if (expect_success) {
    ASSERT_EQ(OEMCrypto_ERROR_SHORT_BUFFER, sts);
  }
  if (sts == OEMCrypto_ERROR_SHORT_BUFFER) {
    ASSERT_LE(sizeof(OEMCrypto_PST_Report), length);
    pst_report_buffer_.resize(length);
  }
  sts = OEMCrypto_ReportUsage(session_id(),
                              reinterpret_cast<const uint8_t*>(pst.c_str()),
                              pst.length(), pst_report(), &length);
  if (!expect_success) {
    ASSERT_NE(OEMCrypto_SUCCESS, sts);
    return;
  }
  ASSERT_EQ(OEMCrypto_SUCCESS, sts);
  vector<uint8_t> computed_signature(SHA_DIGEST_LENGTH);
  unsigned int sig_len = SHA_DIGEST_LENGTH;
  HMAC(EVP_sha1(), &mac_key_client_[0], mac_key_client_.size(),
       reinterpret_cast<uint8_t*>(pst_report()) + SHA_DIGEST_LENGTH,
       length - SHA_DIGEST_LENGTH, &computed_signature[0], &sig_len);
  EXPECT_EQ(0, memcmp(&computed_signature[0], pst_report()->signature,
                      SHA_DIGEST_LENGTH));
  EXPECT_GE(kInactive, pst_report()->status);
  EXPECT_GE(kHardwareSecureClock, pst_report()->clock_security_level);
  EXPECT_EQ(pst.length(), pst_report()->pst_length);
  EXPECT_EQ(0, memcmp(pst.c_str(), pst_report()->pst, pst.length()));
}

OEMCrypto_PST_Report* Session::pst_report() {
  return reinterpret_cast<OEMCrypto_PST_Report*>(&pst_report_buffer_[0]);
}

void Session::DeleteEntry(const std::string& pst) {
  uint8_t* pst_ptr = encrypted_license_.pst;
  memcpy(pst_ptr, pst.c_str(), min(sizeof(license_.pst), pst.length()));
  ServerSignMessage(encrypted_license_, &signature_);
  ASSERT_EQ(OEMCrypto_SUCCESS,
            OEMCrypto_DeleteUsageEntry(session_id(), pst_ptr, pst.length(),
                                       message_ptr(), sizeof(MessageData),
                                       &signature_[0], signature_.size()));
}

void Session::ForceDeleteEntry(const std::string& pst) {
  ASSERT_EQ(OEMCrypto_SUCCESS,
            OEMCrypto_ForceDeleteUsageEntry(
                reinterpret_cast<const uint8_t*>(pst.c_str()), pst.length()));
}

const uint8_t* Session::message_ptr() {
  return reinterpret_cast<const uint8_t*>(&encrypted_license_);
}

}  // namespace wvoec
