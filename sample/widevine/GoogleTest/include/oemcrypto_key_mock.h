// Copyright 2013 Google Inc. All Rights Reserved.
//
//  Mock implementation of OEMCrypto APIs
//
#ifndef OEMCRYPTO_KEY_MOCK_H_
#define OEMCRYPTO_KEY_MOCK_H_

#include <stdint.h>
#include <string>
#include <vector>

namespace wvoec_mock {

const uint32_t kControlObserveDataPath = (1<<31);
const uint32_t kControlObserveHDCP     = (1<<30);
const uint32_t kControlObserveCGMS     = (1<<29);
const uint32_t kControlRequireAntiRollbackHardware = (1<<28);
const uint32_t kControlSecurityPatchLevelShift = 15;
const uint32_t kControlSecurityPatchLevelMask =
    (0x3F<<kControlSecurityPatchLevelShift);
const uint32_t kControlReplayMask      = (0x03<<13);
const uint32_t kControlNonceRequired   = (0x01<<13);
const uint32_t kControlNonceOrEntry    = (0x02<<13);
const uint32_t kControlHDCPVersionShift = 9;
const uint32_t kControlHDCPVersionMask = (0x0F<<kControlHDCPVersionShift);
const uint32_t kControlAllowEncrypt    = (1<<8);
const uint32_t kControlAllowDecrypt    = (1<<7);
const uint32_t kControlAllowSign       = (1<<6);
const uint32_t kControlAllowVerify     = (1<<5);
const uint32_t kControlDataPathSecure  = (1<<4);
const uint32_t kControlNonceEnabled    = (1<<3);
const uint32_t kControlHDCPRequired    = (1<<2);
const uint32_t kControlCGMSMask        = (0x03);
const uint32_t kControlCGMSCopyFreely  = (0x00);
const uint32_t kControlCGMSCopyOnce    = (0x02);
const uint32_t kControlCGMSCopyNever   = (0x03);

class KeyControlBlock {
 public:
  KeyControlBlock(const std::vector<uint8_t>& key_control_string);
  ~KeyControlBlock() {}

  bool Validate();
  void Invalidate() { valid_ = false; }

  bool valid() const { return valid_; }
  uint32_t duration() const { return duration_; }
  void set_duration(uint32_t duration) { duration_ = duration; }
  uint32_t nonce() const { return nonce_; }
  const char* verification() const { return verification_; }
  uint32_t control_bits() const { return control_bits_; }

 private:
  uint32_t ExtractField(const std::vector<uint8_t>& str, int idx);

  bool valid_;
  char verification_[4];
  uint32_t duration_;
  uint32_t nonce_;
  uint32_t control_bits_;
};

// AES-128 crypto key, or HMAC signing key.
class Key {
 public:
  Key(const Key& key) : value_(key.value_), control_(key.control_),
                        ctr_mode_(key.ctr_mode_) {}
  Key(const std::vector<uint8_t>& key_string, const KeyControlBlock& control,
      bool ctr_mode) : value_(key_string), control_(control),
                       ctr_mode_(ctr_mode) {};

  virtual ~Key() {};
  void UpdateDuration(const KeyControlBlock& control);
  const std::vector<uint8_t>& value() const { return value_; }
  const KeyControlBlock& control() const { return control_; }
  bool ctr_mode() const { return ctr_mode_; }

 private:
  std::vector<uint8_t> value_;
  KeyControlBlock control_;
  bool ctr_mode_;
};

}  // namespace wvoec_mock

#endif  // OEMCRYPTO_KEY_MOCK_H_
