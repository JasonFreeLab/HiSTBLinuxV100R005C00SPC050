// Copyright 2013 Google Inc. All Rights Reserved.

#ifndef CDM_TEST_CONFIG_TEST_ENV_H_
#define CDM_TEST_CONFIG_TEST_ENV_H_

#include <string>
#include "wv_cdm_types.h"

namespace wvcdm {
typedef enum {
  kGooglePlayServer,
  kContentProtectionUatServer,
  kContentProtectionStagingServer,
} LicenseServerId;

// Configures default test environment.
class ConfigTestEnv {
 public:
  typedef struct {
    LicenseServerId id;
    std::string url;
    std::string client_tag;
    std::string key_id;
    std::string offline_key_id;
    std::string service_certificate;
  } LicenseServerConfiguration;

  explicit ConfigTestEnv(LicenseServerId server_id);
  ConfigTestEnv(LicenseServerId server_id, bool streaming);
  ConfigTestEnv(LicenseServerId server_id, bool streaming, bool renew,
                bool release);
  ~ConfigTestEnv() {};

  const std::string& client_auth() const { return client_auth_; }
  const KeyId& key_id() const { return key_id_; }
  const CdmKeySystem& key_system() const { return key_system_; }
  const std::string& license_server() const { return license_server_; }
  const std::string& provisioning_server_url() const {
    return provisioning_server_url_;
  }
  const std::string& service_certificate() const {
    return service_certificate_;
  }
  const KeyId& wrong_key_id() const { return wrong_key_id_; }

  void set_key_id(KeyId& key_id) { key_id_.assign(key_id); }
  void set_key_system(CdmKeySystem& key_system) {
    key_system_.assign(key_system);
  }
  void set_license_server(std::string& license_server) {
    license_server_.assign(license_server);
  }

 private:
  void Init(LicenseServerId server_id);

  std::string client_auth_;
  KeyId key_id_;
  CdmKeySystem key_system_;
  std::string license_server_;
  std::string provisioning_server_url_;
  std::string service_certificate_;
  KeyId wrong_key_id_;

  CORE_DISALLOW_COPY_AND_ASSIGN(ConfigTestEnv);
};

}  // namespace wvcdm

#endif  // CDM_TEST_CONFIG_TEST_ENV_H_
