// Copyright 2013 Google Inc. All Rights Reserved.
// These tests are for the cdm engine, and code below it in the stack.  In
// particular, we assume that the OEMCrypo layer works, and has a valid keybox.
// This is because we need a valid RSA certificate, and will attempt to connect
// to the provisioning server to request one if we don't.

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>

#include "cdm_engine.h"
#include "config_test_env.h"
#include "initialization_data.h"
#include "license_request.h"
#include "log.h"
#include "OEMCryptoCENC.h"
#include "properties.h"
#include "scoped_ptr.h"
#include "string_conversions.h"
#include "test_printers.h"
#include "url_request.h"
#include "wv_cdm_constants.h"
#include "wv_cdm_types.h"

namespace wvcdm {

namespace {
// Http OK response code.
const int kHttpOk = 200;

// Default license server, can be configured using --server command line option
// Default key id (pssh), can be configured using --keyid command line option
std::string g_client_auth;
KeyId g_key_id_pssh;
KeyId g_key_id_unwrapped;
CdmKeySystem g_key_system;
std::string g_license_server;
KeyId g_wrong_key_id;

const std::string kCencMimeType = "video/mp4";
const std::string kWebmMimeType = "video/webm";
}  // namespace

class WvCdmEngineTest : public testing::Test {
 public:
  WvCdmEngineTest() : cdm_engine_(&file_system_) {}

  static void SetUpTestCase() {
    ConfigTestEnv config(kContentProtectionUatServer);
    g_client_auth.assign(config.client_auth());
    g_key_system.assign(config.key_system());
    g_wrong_key_id.assign(config.wrong_key_id());
    g_license_server.assign(config.license_server());
    g_key_id_pssh.assign(a2bs_hex(config.key_id()));

    // Extract the key ID from the PSSH box.
    InitializationData extractor(CENC_INIT_DATA_FORMAT, g_key_id_pssh);
    g_key_id_unwrapped = extractor.data();
  }

  virtual void SetUp() {
    CdmResponseType status =
        cdm_engine_.OpenSession(g_key_system, NULL, NULL, &session_id_);
    if (status == NEED_PROVISIONING) {
      Provision();
      status = cdm_engine_.OpenSession(g_key_system, NULL, NULL, &session_id_);
    }
    ASSERT_EQ(NO_ERROR, status);
    ASSERT_NE("", session_id_) << "Could not open CDM session.";
    ASSERT_TRUE(cdm_engine_.IsOpenSession(session_id_));
  }

  virtual void TearDown() { cdm_engine_.CloseSession(session_id_); }

 protected:
  void Provision() {
    CdmProvisioningRequest prov_request;
    std::string provisioning_server_url;
    CdmCertificateType cert_type = kCertificateWidevine;
    std::string cert_authority;
    std::string cert, wrapped_key;
    ASSERT_EQ(NO_ERROR, cdm_engine_.GetProvisioningRequest(
                            cert_type, cert_authority, &prov_request,
                            &provisioning_server_url));
    UrlRequest url_request(provisioning_server_url);
    EXPECT_TRUE(url_request.is_connected());
    url_request.PostCertRequestInQueryString(prov_request);
    std::string message;
    bool ok = url_request.GetResponse(&message);
    EXPECT_TRUE(ok);
    ASSERT_EQ(NO_ERROR, cdm_engine_.HandleProvisioningResponse(message, &cert,
                                                               &wrapped_key));
  }

  void GenerateKeyRequest(const std::string& key_id,
                          const std::string& init_data_type_string) {
    CdmAppParameterMap app_parameters;
    CdmKeySetId key_set_id;

    InitializationData init_data(init_data_type_string, key_id);

    CdmKeyRequest key_request;

    EXPECT_EQ(KEY_MESSAGE, cdm_engine_.GenerateKeyRequest(
                               session_id_, key_set_id, init_data,
                               kLicenseTypeStreaming, app_parameters,
                               &key_request));

    key_msg_ = key_request.message;
    EXPECT_EQ(kKeyRequestTypeInitial, key_request.type);
  }

  void GenerateRenewalRequest() {
    CdmKeyRequest request;
    EXPECT_EQ(KEY_MESSAGE,
              cdm_engine_.GenerateRenewalRequest(session_id_, &request));

    key_msg_ = request.message;
    server_url_ = request.url;
  }

  std::string GetKeyRequestResponse(const std::string& server_url,
                                    const std::string& client_auth) {
    return GetKeyRequestResponse(server_url, client_auth, true);
  }

  std::string FailToGetKeyRequestResponse(const std::string& server_url,
                                          const std::string& client_auth) {
    return GetKeyRequestResponse(server_url, client_auth, false);
  }

  // posts a request and extracts the drm message from the response
  std::string GetKeyRequestResponse(const std::string& server_url,
                                    const std::string& client_auth,
                                    bool expect_success) {
    // Use secure connection and chunk transfer coding.
    UrlRequest url_request(server_url + client_auth);
    if (!url_request.is_connected()) {
      return "";
    }

    url_request.PostRequest(key_msg_);
    std::string response;
    bool ok = url_request.GetResponse(&response);
    LOGD("response: %s\n", response.c_str());
    EXPECT_TRUE(ok);

    int status_code = url_request.GetStatusCode(response);
    if (expect_success) EXPECT_EQ(kHttpOk, status_code);

    if (status_code != kHttpOk) {
      return "";
    } else {
      std::string drm_msg;
      LicenseRequest lic_request;
      lic_request.GetDrmMessage(response, drm_msg);
      LOGV("drm msg: %u bytes\r\n%s", drm_msg.size(),
           HexEncode(reinterpret_cast<const uint8_t*>(drm_msg.data()),
                     drm_msg.size()).c_str());
      return drm_msg;
    }
  }

  void VerifyNewKeyResponse(const std::string& server_url,
                            const std::string& client_auth) {
    std::string resp = GetKeyRequestResponse(server_url, client_auth);
    CdmKeySetId key_set_id;
    EXPECT_EQ(KEY_ADDED,
              cdm_engine_.AddKey(session_id_, resp, &key_set_id));
  }

  void VerifyRenewalKeyResponse(const std::string& server_url,
                                const std::string& client_auth) {
    std::string resp = GetKeyRequestResponse(server_url, client_auth);
    EXPECT_EQ(KEY_ADDED, cdm_engine_.RenewKey(session_id_, resp));
  }

  FileSystem file_system_;
  CdmEngine cdm_engine_;
  std::string key_msg_;
  std::string session_id_;
  std::string server_url_;
};

// Test that provisioning works, even if device is already provisioned.
TEST_F(WvCdmEngineTest, ProvisioningTest) {
  uint32_t nonce = 0;
  uint8_t buffer[1];
  size_t size = 0;
  int result = OEMCrypto_RewrapDeviceRSAKey(
      0, buffer, 0, buffer, 0, &nonce, buffer, 0, buffer, buffer, &size);
  if (result == OEMCrypto_ERROR_NOT_IMPLEMENTED) {
    LOGW("WARNING: Skipping ProvisioningTest because the device does not "
         "support provisioning. If you are using a baked-in certificate, this "
         "is expected. Otherwise, something is wrong.");
    return;
  }

  Provision();
}

TEST_F(WvCdmEngineTest, BaseIsoBmffMessageTest) {
  GenerateKeyRequest(g_key_id_pssh, kCencMimeType);
  GetKeyRequestResponse(g_license_server, g_client_auth);
}

// TODO(juce): Set up with correct test data.
TEST_F(WvCdmEngineTest, BaseWebmMessageTest) {
  GenerateKeyRequest(g_key_id_unwrapped, kWebmMimeType);
  GetKeyRequestResponse(g_license_server, g_client_auth);
}

TEST_F(WvCdmEngineTest, WrongMessageTest) {
  std::string wrong_message = a2bs_hex(g_wrong_key_id);
  GenerateKeyRequest(wrong_message, kCencMimeType);

  // We should receive a response with no license, i.e. the extracted license
  // response message should be empty.
  ASSERT_EQ("", FailToGetKeyRequestResponse(g_license_server, g_client_auth));
}

TEST_F(WvCdmEngineTest, NormalDecryptionIsoBmff) {
  GenerateKeyRequest(g_key_id_pssh, kCencMimeType);
  VerifyNewKeyResponse(g_license_server, g_client_auth);
}

// TODO(juce): Set up with correct test data.
TEST_F(WvCdmEngineTest, NormalDecryptionWebm) {
  GenerateKeyRequest(g_key_id_unwrapped, kWebmMimeType);
  VerifyNewKeyResponse(g_license_server, g_client_auth);
}

TEST_F(WvCdmEngineTest, LicenseRenewal) {
  GenerateKeyRequest(g_key_id_pssh, kCencMimeType);
  VerifyNewKeyResponse(g_license_server, g_client_auth);

  GenerateRenewalRequest();
  VerifyRenewalKeyResponse(server_url_.empty() ? g_license_server : server_url_,
                           g_client_auth);
}

}  // namespace wvcdm
