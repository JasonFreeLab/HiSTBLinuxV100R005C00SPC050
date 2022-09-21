#include "oec_device_features.h"

#include <stdio.h>

#include <cstring>

#include "oec_test_data.h"

namespace wvoec {

DeviceFeatures global_features;

void DeviceFeatures::Initialize(bool is_cast_receiver,
                                bool force_load_test_keybox) {
  cast_receiver = is_cast_receiver;
  uses_keybox = false;
  uses_certificate = false;
  loads_certificate = false;
  generic_crypto = false;
  usage_table = false;
  api_version = 0;
  derive_key_method = NO_METHOD;
  if (OEMCrypto_SUCCESS != OEMCrypto_Initialize()) {
    printf("OEMCrypto_Initialze failed. All tests will fail.\n");
    return;
  }
  uint32_t nonce = 0;
  uint8_t buffer[1];
  size_t size = 0;
  uses_keybox =
      (OEMCrypto_ERROR_NOT_IMPLEMENTED != OEMCrypto_GetKeyData(buffer, &size));
  printf("uses_keybox = %s.\n", uses_keybox ? "true" : "false");
  loads_certificate = uses_keybox && (OEMCrypto_ERROR_NOT_IMPLEMENTED !=
                                      OEMCrypto_RewrapDeviceRSAKey(
                                          0, buffer, 0, buffer, 0, &nonce,
                                          buffer, 0, buffer, buffer, &size));
  printf("loads_certificate = %s.\n", loads_certificate ? "true" : "false");
  uses_certificate = (OEMCrypto_ERROR_NOT_IMPLEMENTED !=
                      OEMCrypto_GenerateRSASignature(0, buffer, 0, buffer,
                                                     &size, kSign_RSASSA_PSS));
  printf("uses_certificate = %s.\n", uses_certificate ? "true" : "false");
  generic_crypto =
      (OEMCrypto_ERROR_NOT_IMPLEMENTED !=
       OEMCrypto_Generic_Encrypt(0, buffer, 0, buffer,
                                 OEMCrypto_AES_CBC_128_NO_PADDING, buffer));
  printf("generic_crypto = %s.\n", generic_crypto ? "true" : "false");
  api_version = OEMCrypto_APIVersion();
  printf("api_version = %d.\n", api_version);
  usage_table = OEMCrypto_SupportsUsageTable();
  printf("usage_table = %s.\n", usage_table ? "true" : "false");
  if (force_load_test_keybox) {
    derive_key_method = FORCE_TEST_KEYBOX;
  } else {
    PickDerivedKey();
  }
  printf("cast_receiver = %s.\n", cast_receiver ? "true" : "false");
  switch (derive_key_method) {
    case NO_METHOD:
      printf("NO_METHOD: Cannot derive known session keys.\n");
      // Note: cast_receiver left unchanged because set by user on command line.
      uses_keybox = false;
      uses_certificate = false;
      loads_certificate = false;
      generic_crypto = false;
      usage_table = false;
      break;
    case LOAD_TEST_KEYBOX:
      printf("LOAD_TEST_KEYBOX: Call LoadTestKeybox before deriving keys.\n");
      break;
    case LOAD_TEST_RSA_KEY:
      printf("LOAD_TEST_RSA_KEY: Call LoadTestRSAKey before deriving keys.\n");
      break;
    case EXISTING_TEST_KEYBOX:
      printf("EXISTING_TEST_KEYBOX: Keybox is already the test keybox.\n");
      break;
    case FORCE_TEST_KEYBOX:
      printf("FORCE_TEST_KEYBOX: User requested calling InstallKeybox.\n");
      break;
  }
  OEMCrypto_Terminate();
}

std::string DeviceFeatures::RestrictFilter(const std::string& initial_filter) {
  std::string filter = initial_filter;
  if (!uses_keybox)                   FilterOut(&filter, "*KeyboxTest*");
  if (derive_key_method
      != FORCE_TEST_KEYBOX)           FilterOut(&filter, "*ForceKeybox*");
  if (!uses_certificate)              FilterOut(&filter, "OEMCrypto*Cert*");
  if (!loads_certificate)             FilterOut(&filter, "OEMCryptoLoadsCert*");
  if (!generic_crypto)                FilterOut(&filter, "*GenericCrypto*");
  if (!cast_receiver)                 FilterOut(&filter, "*CastReceiver*");
  if (!usage_table)                   FilterOut(&filter, "*UsageTable*");
  if (derive_key_method == NO_METHOD) FilterOut(&filter, "*SessionTest*");
  if (api_version < 10)               FilterOut(&filter, "*API10*");
  if (api_version < 11)               FilterOut(&filter, "*API11*");
  // Performance tests take a long time.  Filter them out if they are not
  // specifically requested.
  if (filter.find("Performance") == std::string::npos) {
    FilterOut(&filter, "*Performance*");
  }
  return filter;
}

void DeviceFeatures::PickDerivedKey() {
  if (uses_keybox) {
    // If device uses a keybox, try to load the test keybox.
    if (OEMCrypto_ERROR_NOT_IMPLEMENTED != OEMCrypto_LoadTestKeybox()) {
      derive_key_method = LOAD_TEST_KEYBOX;
    } else if (IsTestKeyboxInstalled()) {
      derive_key_method = EXISTING_TEST_KEYBOX;
    }
  } else if (OEMCrypto_ERROR_NOT_IMPLEMENTED != OEMCrypto_LoadTestRSAKey()) {
    derive_key_method = LOAD_TEST_RSA_KEY;
  }
}

bool DeviceFeatures::IsTestKeyboxInstalled() {
  uint8_t key_data[256];
  size_t key_data_len = sizeof(key_data);
  if (OEMCrypto_GetKeyData(key_data, &key_data_len) != OEMCrypto_SUCCESS)
    return false;
  if (key_data_len != sizeof(kTestKeybox.data_)) return false;
  if (memcmp(key_data, kTestKeybox.data_, key_data_len)) return false;
  uint8_t dev_id[128] = {0};
  size_t dev_id_len = 128;
  if (OEMCrypto_GetDeviceID(dev_id, &dev_id_len) != OEMCrypto_SUCCESS)
    return false;
  // We use strncmp instead of memcmp because we don't really care about the
  // multiple '\0' characters at the end of the device id.
  return 0 == strncmp(reinterpret_cast<const char*>(dev_id),
                      reinterpret_cast<const char*>(kTestKeybox.device_id_),
                      sizeof(kTestKeybox.device_id_));
}

void DeviceFeatures::FilterOut(std::string* current_filter,
                               const std::string& new_filter) {
  if (current_filter->find('-') == std::string::npos) {
    *current_filter += "-" + new_filter;
  } else {
    *current_filter += ":" + new_filter;
  }
}

}  // namespace wvoec
