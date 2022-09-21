// Copyright 2012 Google Inc. All Rights Reserved.

#ifndef WVCDM_CORE_CRYPTO_KEY_H_
#define WVCDM_CORE_CRYPTO_KEY_H_

#include "wv_cdm_types.h"

namespace wvcdm {

class CryptoKey {
 public:
  CryptoKey() {};
  ~CryptoKey() {};

  const std::string& key_id() const { return key_id_; }
  const std::string& key_data() const { return key_data_; }
  const std::string& key_data_iv() const { return key_data_iv_; }
  const std::string& key_control() const { return key_control_; }
  const std::string& key_control_iv() const { return key_control_iv_; }
  CdmCipherMode cipher_mode() const { return cipher_mode_; }
  void set_key_id(const std::string& key_id) { key_id_ = key_id; }
  void set_key_data(const std::string& key_data) { key_data_ = key_data; }
  void set_key_data_iv(const std::string& iv) { key_data_iv_ = iv; }
  void set_key_control(const std::string& ctl) { key_control_ = ctl; }
  void set_key_control_iv(const std::string& ctl_iv) {
    key_control_iv_ = ctl_iv;
  }
  void set_cipher_mode(CdmCipherMode cipher_mode) {
    cipher_mode_ = cipher_mode;
  }

  bool HasKeyControl() const { return key_control_.size() >= 16; }

 private:
  std::string key_id_;
  std::string key_data_iv_;
  std::string key_data_;
  std::string key_control_;
  std::string key_control_iv_;
  CdmCipherMode cipher_mode_;
};

}  // namespace wvcdm

#endif  // WVCDM_CORE_CRYPTO_KEY_H_
