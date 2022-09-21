// Copyright 2013 Google Inc. All Rights Reserved.
//
// OEMCrypto unit tests - extra tests required for Android platform.
//
// The Widevine CDM system can be built on many platforms, with different
// capabilities. For example, some platforms do not require usage tables,
// and some can have a pre-installed certificate and do not need a keybox.
// On Android, these features are not optional.  This set of unit tests
// verify that these features are implemented.
//
// In the file oemcrypto_test.cpp, the unit tests only verify correct
// functionality for functions that are implemented.  Android devices must pass
// unit tests in both files.

#include <gtest/gtest.h>

#include "OEMCryptoCENC.h"

namespace wvoec {

// These tests are required for LollyPop Android devices.
class OEMCryptoAndroidLMPTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    ASSERT_EQ(OEMCrypto_SUCCESS, OEMCrypto_Initialize());
  }

  virtual void TearDown() {
    OEMCrypto_Terminate();
  }
};

// Android devices must have a keybox.
TEST_F(OEMCryptoAndroidLMPTest, GetKeyDataImplemented) {
  uint8_t key_data[256];
  size_t key_data_len = sizeof(key_data);
  ASSERT_NE(OEMCrypto_ERROR_NOT_IMPLEMENTED,
            OEMCrypto_GetKeyData(key_data, &key_data_len));
}

TEST_F(OEMCryptoAndroidLMPTest, MinVersionNumber9) {
  uint32_t version = OEMCrypto_APIVersion();
  ASSERT_LE(9u, version);
}

TEST_F(OEMCryptoAndroidLMPTest, ValidKeyboxTest) {
  ASSERT_EQ(OEMCrypto_SUCCESS, OEMCrypto_IsKeyboxValid());
}

TEST_F(OEMCryptoAndroidLMPTest, RewrapDeviceRSAKeyImplemented) {
  ASSERT_NE(OEMCrypto_ERROR_NOT_IMPLEMENTED,
            OEMCrypto_RewrapDeviceRSAKey(0, NULL, 0, NULL, 0, NULL,
                                         NULL, 0, NULL, NULL, NULL));
}

TEST_F(OEMCryptoAndroidLMPTest, RSASignatureImplemented) {
  ASSERT_NE(OEMCrypto_ERROR_NOT_IMPLEMENTED,
            OEMCrypto_GenerateRSASignature(0, NULL, 0, NULL, NULL,
                                           kSign_RSASSA_PSS));
}

TEST_F(OEMCryptoAndroidLMPTest, GenericCryptoImplemented) {
  ASSERT_NE(OEMCrypto_ERROR_NOT_IMPLEMENTED,
            OEMCrypto_Generic_Encrypt(0, NULL, 0, NULL,
                                      OEMCrypto_AES_CBC_128_NO_PADDING, NULL));
  ASSERT_NE(OEMCrypto_ERROR_NOT_IMPLEMENTED,
            OEMCrypto_Generic_Decrypt(0, NULL, 0, NULL,
                                      OEMCrypto_AES_CBC_128_NO_PADDING, NULL));
  ASSERT_NE(OEMCrypto_ERROR_NOT_IMPLEMENTED,
            OEMCrypto_Generic_Sign(0, NULL, 0,
                                   OEMCrypto_HMAC_SHA256, NULL, NULL));
  ASSERT_NE(OEMCrypto_ERROR_NOT_IMPLEMENTED,
            OEMCrypto_Generic_Verify(0, NULL, 0,
                                     OEMCrypto_HMAC_SHA256, NULL, 0));
}

TEST_F(OEMCryptoAndroidLMPTest, SupportsUsageTable) {
  ASSERT_TRUE(OEMCrypto_SupportsUsageTable());
}

TEST_F(OEMCryptoAndroidLMPTest, Level1Required) {
  const char* char_level = OEMCrypto_SecurityLevel();
  std::string security_level(char_level ? char_level : "");
  EXPECT_EQ("L1", security_level)
      << "The security level is " << security_level << ". but we expect L1.\n"
      << "If you are testing a device that should be L3 or L2, please\n"
      << "repeat the tests with the flag --gtest_filter=\"*-*Level1Required\"";
}

// These tests are required for M Android devices.
class OEMCryptoAndroidMNCTest : public OEMCryptoAndroidLMPTest {};

TEST_F(OEMCryptoAndroidMNCTest, MinVersionNumber10) {
  uint32_t version = OEMCrypto_APIVersion();
  ASSERT_GE(version, 10u);
}

TEST_F(OEMCryptoAndroidMNCTest, LoadsTestKeyboxImplemented) {
  ASSERT_EQ(OEMCrypto_SUCCESS, OEMCrypto_LoadTestKeybox());
}

TEST_F(OEMCryptoAndroidMNCTest, NumberOfSessionsImplemented) {
  ASSERT_NE(OEMCrypto_ERROR_NOT_IMPLEMENTED,
            OEMCrypto_GetNumberOfOpenSessions(NULL));
  ASSERT_NE(OEMCrypto_ERROR_NOT_IMPLEMENTED,
            OEMCrypto_GetMaxNumberOfSessions(NULL));
}

TEST_F(OEMCryptoAndroidMNCTest, QueryKeyControlImplemented) {
  ASSERT_NE(OEMCrypto_ERROR_NOT_IMPLEMENTED,
            OEMCrypto_QueryKeyControl(0, NULL, 0, NULL, NULL));
}

// These tests are required for N Android devices.
class OEMCryptoAndroidNYCTest : public OEMCryptoAndroidMNCTest {};

TEST_F(OEMCryptoAndroidNYCTest, MinVersionNumber11) {
  uint32_t version = OEMCrypto_APIVersion();
  ASSERT_GE(version, 11u);
}

}  // namespace wvoec
