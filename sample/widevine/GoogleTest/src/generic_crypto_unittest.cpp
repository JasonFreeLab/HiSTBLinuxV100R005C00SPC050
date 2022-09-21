// Copyright 2016 Google Inc. All Rights Reserved.
// These tests are for the generic crypto operations.  They call on the
// CdmEngine class and exercise the classes below it as well.  In
// particular, we assume that the OEMCrypo layer works, and has a valid keybox.
// This is because we need a valid RSA certificate, and will attempt to connect
// to the provisioning server to request one if we don't.

#include <arpa/inet.h>
#include <gtest/gtest.h>
#include <string>

#include "cdm_engine.h"

#include "license_request.h"
#include "log.h"
#include "oec_session_util.h"
#include "oemcrypto_key_mock.h"
#include "string_conversions.h"
#include "url_request.h"
#include "wv_cdm_constants.h"
#include "wv_cdm_types.h"

namespace {

const std::string kKeySystem = "com.widevine.alpha";

}  // namespace

namespace wvcdm {

class WvGenericOperationsTest : public testing::Test {
 public:
  virtual void SetUp() {
    ::testing::Test::SetUp();

    // Load test keybox. This keybox will be used by any CryptoSession
    // created by the CDM under test.
    ASSERT_EQ(OEMCrypto_SUCCESS, OEMCrypto_LoadTestKeybox());

    // Perform CdmEngine setup
    cdm_engine_ = new CdmEngine(&file_system_);

    CdmResponseType status =
        cdm_engine_->OpenSession(kKeySystem, NULL, NULL, &session_id_);
    if (status == NEED_PROVISIONING) {
      Provision();
      status = cdm_engine_->OpenSession(kKeySystem, NULL, NULL, &session_id_);
    }
    ASSERT_EQ(NO_ERROR, status);
    ASSERT_NE("", session_id_) << "Could not open CDM session.";
    ASSERT_TRUE(cdm_engine_->IsOpenSession(session_id_));

    // Get OEMCrypto session ID from the CDM
    CdmQueryMap query;
    cdm_engine_->QueryOemCryptoSessionId(session_id_, &query);
    std::istringstream parse_int;
    parse_int.str(query[QUERY_KEY_OEMCRYPTO_SESSION_ID]);
    parse_int >> oec_session_id_;

    // Construct and install keys into the CDM's OEMCrypto session.
    OecSessionSetup(oec_session_id_);
    EncryptAndLoadKeys();
  }

  virtual void TearDown() {
    oec_util_session_.close();
    cdm_engine_->CloseSession(session_id_);
    // OEMCrypto_Terminate() will be performed during the test class's
    // destruction (specifically by the CryptoSession destructor)
  }

  void OecSessionSetup(uint32_t oec_session_id) {
    buffer_size_ = 160;
    oec_util_session_.SetSessionId(oec_session_id);
    oec_util_session_.GenerateTestSessionKeys();
    MakeFourKeys();
  }

  enum GenericKeyType {
    kGenericEncrypt = 0,
    kGenericDecrypt = 1,
    kGenericSign = 2,
    kGenericVerify = 3
  };

  virtual void MakeFourKeys(
      uint32_t duration = wvoec::kDuration, uint32_t control = 0,
      uint32_t nonce = 0, const std::string& pst = "") {
    ASSERT_NO_FATAL_FAILURE(
        oec_util_session_.FillSimpleMessage(duration, control, nonce, pst));
    oec_util_session_.license().keys[kGenericEncrypt].control.control_bits |=
        htonl(wvoec_mock::kControlAllowEncrypt);
    oec_util_session_.license().keys[kGenericDecrypt].control.control_bits |=
        htonl(wvoec_mock::kControlAllowDecrypt);
    oec_util_session_.license().keys[kGenericSign].control.control_bits |=
        htonl(wvoec_mock::kControlAllowSign);
    oec_util_session_.license().keys[kGenericVerify].control.control_bits |=
        htonl(wvoec_mock::kControlAllowVerify);

    oec_util_session_.license().keys[kGenericSign].key_data_length =
        wvcdm::MAC_KEY_SIZE;
    oec_util_session_.license().keys[kGenericVerify].key_data_length =
        wvcdm::MAC_KEY_SIZE;

    clear_buffer_.assign(buffer_size_, 0);
    for (size_t i = 0; i < clear_buffer_.size(); i++) {
      clear_buffer_[i] = 1 + i % 250;
    }
    for (size_t i = 0; i < wvcdm::KEY_IV_SIZE; i++) {
      iv_[i] = i;
    }
  }

  std::string GetKeyId(GenericKeyType type) {
    std::string key_id;
    size_t key_id_length = oec_util_session_.license().keys[0].key_id_length;
    key_id.assign(
        &(oec_util_session_.license().keys[type].key_id[0]),
        &(oec_util_session_.license().keys[type].key_id[key_id_length]));
    return key_id;
  }

  std::string GetClearBuffer() {
    std::string buffer;
    size_t buffer_length = clear_buffer_.size();
    buffer.assign(&clear_buffer_[0], &clear_buffer_[buffer_length]);
    return buffer;
  }

  std::string GetEncryptedBuffer() {
    std::string buffer;
    size_t buffer_length = encrypted_buffer_.size();
    buffer.assign(&encrypted_buffer_[0], &encrypted_buffer_[buffer_length]);
    return buffer;
  }

  std::string GetIvBlock() {
    std::string buffer;
    size_t buffer_length = wvcdm::KEY_IV_SIZE;
    buffer.assign(&iv_[0], &iv_[buffer_length]);
    return buffer;
  }

  std::string GetSignatureBuffer() {
    std::string buffer;
    buffer.resize(SHA256_DIGEST_LENGTH);
    return buffer;
  }

  void EncryptAndLoadKeys() {
    ASSERT_NO_FATAL_FAILURE(oec_util_session_.EncryptAndSign());
    oec_util_session_.LoadTestKeys();
  }

 protected:
  void Provision() {
    CdmProvisioningRequest prov_request;
    std::string provisioning_server_url;
    CdmCertificateType cert_type = kCertificateWidevine;
    std::string cert_authority;
    std::string cert, wrapped_key;
    ASSERT_EQ(NO_ERROR,
              cdm_engine_->GetProvisioningRequest(
                  cert_type, cert_authority, &prov_request,
                  &provisioning_server_url));
    UrlRequest url_request(provisioning_server_url);
    EXPECT_TRUE(url_request.is_connected());
    url_request.PostCertRequestInQueryString(prov_request);
    std::string message;
    bool ok = url_request.GetResponse(&message);
    EXPECT_TRUE(ok);
    ASSERT_EQ(NO_ERROR,
              cdm_engine_->HandleProvisioningResponse(message, &cert,
                                                      &wrapped_key));
  }

  // This CryptoSession object handles Initialization and Termination
  // calls on OEMCrypto for the duration of the test. CryptoSessions
  // created by the CDM will share the OEMCrypto state of this CryptoSession,
  // including, for example, a test keybox.
  CryptoSession crypto_session_;

  FileSystem file_system_;
  CdmEngine* cdm_engine_;
  std::string key_msg_;
  std::string session_id_;
  std::string server_url_;
  uint32_t oec_session_id_;
  wvoec::Session oec_util_session_;
  size_t buffer_size_;
  vector<uint8_t> clear_buffer_;
  vector<uint8_t> encrypted_buffer_;
  uint8_t iv_[wvcdm::KEY_IV_SIZE];
};

TEST_F(WvGenericOperationsTest, NormalSessionOpenClose) {
  wvoec::Session s;
  ASSERT_NO_FATAL_FAILURE(s.open());
  ASSERT_NO_FATAL_FAILURE(s.close());
}

TEST_F(WvGenericOperationsTest, GenerateSessionKeys) {
  wvoec::Session s;
  ASSERT_NO_FATAL_FAILURE(s.open());
  ASSERT_NO_FATAL_FAILURE(s.GenerateTestSessionKeys());
  ASSERT_NO_FATAL_FAILURE(s.close());
}

TEST_F(WvGenericOperationsTest, GenericEncryptNoKey) {
  CdmResponseType cdm_sts;
  std::string in_buffer = GetClearBuffer();
  std::string out_buffer = GetEncryptedBuffer();
  std::string iv = GetIvBlock();

  // No key
  KeyId key_id("xyz");
  cdm_sts = cdm_engine_->GenericEncrypt(session_id_, in_buffer, key_id, iv,
                                        wvcdm::kEncryptionAlgorithmAesCbc128,
                                        &out_buffer);
  EXPECT_EQ(KEY_ERROR_1, cdm_sts);
}

TEST_F(WvGenericOperationsTest, GenericEncryptKeyNotAllowed) {
  CdmResponseType cdm_sts;
  std::string in_buffer = GetClearBuffer();
  std::string out_buffer = GetEncryptedBuffer();
  std::string iv = GetIvBlock();

  // Wrong key
  std::string key_id = GetKeyId(kGenericDecrypt);

  cdm_sts = cdm_engine_->GenericEncrypt(session_id_, in_buffer, key_id, iv,
                                        wvcdm::kEncryptionAlgorithmAesCbc128,
                                        &out_buffer);
  EXPECT_EQ(UNKNOWN_ERROR, cdm_sts);
}

TEST_F(WvGenericOperationsTest, GenericEncryptGood) {
  CdmResponseType cdm_sts;
  std::string in_buffer = GetClearBuffer();
  std::string out_buffer = GetEncryptedBuffer();
  std::string iv = GetIvBlock();

  // Good key
  std::string key_id = GetKeyId(kGenericEncrypt);

  cdm_sts = cdm_engine_->GenericEncrypt(session_id_, in_buffer, key_id, iv,
                                        wvcdm::kEncryptionAlgorithmAesCbc128,
                                        &out_buffer);
  EXPECT_EQ(NO_ERROR, cdm_sts);
}

TEST_F(WvGenericOperationsTest, GenericDecryptKeyNotAllowed) {
  CdmResponseType cdm_sts;
  std::string in_buffer = GetClearBuffer();
  std::string out_buffer = GetEncryptedBuffer();
  std::string iv = GetIvBlock();

  // Wrong key
  std::string key_id = GetKeyId(kGenericEncrypt);

  cdm_sts = cdm_engine_->GenericDecrypt(session_id_, in_buffer, key_id, iv,
                                        wvcdm::kEncryptionAlgorithmAesCbc128,
                                        &out_buffer);
  EXPECT_EQ(UNKNOWN_ERROR, cdm_sts);
}

TEST_F(WvGenericOperationsTest, GenericDecryptGood) {
  CdmResponseType cdm_sts;
  std::string in_buffer = GetClearBuffer();
  std::string out_buffer = GetEncryptedBuffer();
  std::string iv = GetIvBlock();

  // Good key
  std::string key_id = GetKeyId(kGenericDecrypt);

  cdm_sts = cdm_engine_->GenericDecrypt(session_id_, in_buffer, key_id, iv,
                                        wvcdm::kEncryptionAlgorithmAesCbc128,
                                        &out_buffer);
  EXPECT_EQ(NO_ERROR, cdm_sts);
}

TEST_F(WvGenericOperationsTest, GenericSignKeyNotAllowed) {
  CdmResponseType cdm_sts;
  std::string in_buffer = GetClearBuffer();
  std::string signature_buffer;

  // Wrong key
  std::string key_id = GetKeyId(kGenericVerify);

  cdm_sts = cdm_engine_->GenericSign(session_id_, in_buffer, key_id,
                                     wvcdm::kSigningAlgorithmHmacSha256,
                                     &signature_buffer);
  EXPECT_EQ(UNKNOWN_ERROR, cdm_sts);
}

TEST_F(WvGenericOperationsTest, GenericSignGood) {
  CdmResponseType cdm_sts;
  std::string in_buffer = GetClearBuffer();
  std::string signature_buffer;

  // Good key
  std::string key_id = GetKeyId(kGenericSign);

  cdm_sts = cdm_engine_->GenericSign(session_id_, in_buffer, key_id,
                                     wvcdm::kSigningAlgorithmHmacSha256,
                                     &signature_buffer);
  EXPECT_EQ(NO_ERROR, cdm_sts);
}

TEST_F(WvGenericOperationsTest, GenericVerifyKeyNotAllowed) {
  CdmResponseType cdm_sts;
  std::string in_buffer = GetClearBuffer();
  std::string signature_buffer = GetSignatureBuffer();

  // Wrong key
  std::string key_id = GetKeyId(kGenericSign);

  cdm_sts = cdm_engine_->GenericVerify(session_id_, in_buffer, key_id,
                                       wvcdm::kSigningAlgorithmHmacSha256,
                                       signature_buffer);
  EXPECT_EQ(UNKNOWN_ERROR, cdm_sts);
}

TEST_F(WvGenericOperationsTest, GenericVerifyGood) {
  CdmResponseType cdm_sts;
  std::string in_buffer = GetClearBuffer();
  std::string signature_buffer = GetSignatureBuffer();

  // Good key - signature not set.
  std::string key_id = GetKeyId(kGenericVerify);

  cdm_sts = cdm_engine_->GenericVerify(session_id_, in_buffer, key_id,
                                       wvcdm::kSigningAlgorithmHmacSha256,
                                       signature_buffer);
  // OEMCrypto error is OEMCrypto_ERROR_SIGNATURE_FAILURE
  EXPECT_EQ(UNKNOWN_ERROR, cdm_sts);
}

class WvGenericOperationsDataTest : public WvGenericOperationsTest {
 public:
  // Construct keys for encrypt/decrypt and for sign/verify
  virtual void MakeFourKeys(
      uint32_t duration = wvoec::kDuration, uint32_t control = 0,
      uint32_t nonce = 0, const std::string& pst = "") {
    ASSERT_NO_FATAL_FAILURE(
        oec_util_session_.FillSimpleMessage(duration, control, nonce, pst));
    oec_util_session_.license().keys[kGenericEncrypt].control.control_bits |=
        htonl(wvoec_mock::kControlAllowEncrypt |
              wvoec_mock::kControlAllowDecrypt);
    oec_util_session_.license().keys[kGenericSign].control.control_bits |=
        htonl(wvoec_mock::kControlAllowSign | wvoec_mock::kControlAllowVerify);

    oec_util_session_.license().keys[kGenericSign].key_data_length =
        wvcdm::MAC_KEY_SIZE;

    clear_buffer_.assign(buffer_size_, 0);
    for (size_t i = 0; i < clear_buffer_.size(); i++) {
      clear_buffer_[i] = 1 + i % 250;
    }
    for (size_t i = 0; i < wvcdm::KEY_IV_SIZE; i++) {
      iv_[i] = i;
    }
  }
};

TEST_F(WvGenericOperationsDataTest, GenericEncryptDecrypt) {
  CdmResponseType cdm_sts;
  std::string in_buffer = GetClearBuffer();
  std::string encrypted_buffer = GetEncryptedBuffer();
  std::string iv = GetIvBlock();

  // Encrypt
  std::string key_id = GetKeyId(kGenericEncrypt);

  cdm_sts = cdm_engine_->GenericEncrypt(
      session_id_, in_buffer, key_id, iv, wvcdm::kEncryptionAlgorithmAesCbc128,
      &encrypted_buffer);

  EXPECT_EQ(NO_ERROR, cdm_sts);

  // Decrypt, use same key as encrypt.
  key_id = GetKeyId(kGenericEncrypt);

  std::string final_buffer;
  final_buffer.resize(in_buffer.size());

  cdm_sts = cdm_engine_->GenericDecrypt(
      session_id_, encrypted_buffer, key_id, iv,
      wvcdm::kEncryptionAlgorithmAesCbc128, &final_buffer);

  EXPECT_EQ(NO_ERROR, cdm_sts);
  EXPECT_EQ(0, in_buffer.compare(final_buffer));
}

TEST_F(WvGenericOperationsDataTest, GenericSignVerify) {
  CdmResponseType cdm_sts;
  std::string in_buffer = GetClearBuffer();
  std::string signature_buffer = GetSignatureBuffer();

  // Signing key
  std::string key_id = GetKeyId(kGenericSign);
  cdm_sts = cdm_engine_->GenericSign(session_id_, in_buffer, key_id,
                                     wvcdm::kSigningAlgorithmHmacSha256,
                                     &signature_buffer);
  EXPECT_EQ(NO_ERROR, cdm_sts);

  // Verify signature, use same key as sign.
  key_id = GetKeyId(kGenericSign);
  cdm_sts = cdm_engine_->GenericVerify(session_id_, in_buffer, key_id,
                                       wvcdm::kSigningAlgorithmHmacSha256,
                                       signature_buffer);
  EXPECT_EQ(NO_ERROR, cdm_sts);
}

}  // namespace wvcdm
