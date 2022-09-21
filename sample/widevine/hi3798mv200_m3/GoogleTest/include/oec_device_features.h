#ifndef CDM_OEC_DEVICE_FEATURES_H_
#define CDM_OEC_DEVICE_FEATURES_H_

#include <string>

#include "OEMCryptoCENC.h"
#include "wv_keybox.h"

namespace wvoec {

class DeviceFeatures {
 public:
  enum DeriveMethod {      // Method to use derive session keys.
    NO_METHOD,             // Cannot derive known session keys.
    LOAD_TEST_KEYBOX,      // Call LoadTestKeybox before deriving keys.
    LOAD_TEST_RSA_KEY,     // Call LoadTestRSAKey before deriving keys.
    EXISTING_TEST_KEYBOX,  // Keybox is already the test keybox.
    FORCE_TEST_KEYBOX,     // User requested calling InstallKeybox.
  };

  enum DeriveMethod derive_key_method;
  bool uses_keybox;        // Device uses a keybox to derive session keys.
  bool uses_certificate;   // Device uses a certificate to derive session keys.
  bool loads_certificate;  // Device can load a certificate from the server.
  bool generic_crypto;     // Device supports generic crypto.
  bool cast_receiver;      // Device supports alternate rsa signature padding.
  bool usage_table;        // Device saves usage information.
  uint32_t api_version;

  void Initialize(bool is_cast_receiver, bool force_load_test_keybox);
  std::string RestrictFilter(const std::string& initial_filter);

 private:
  void PickDerivedKey();
  bool IsTestKeyboxInstalled();
  void FilterOut(std::string* current_filter, const std::string& new_filter);
};

extern DeviceFeatures global_features;

}  // namespace wvoec

#endif  // CDM_OEC_DEVICE_FEATURES_H_
