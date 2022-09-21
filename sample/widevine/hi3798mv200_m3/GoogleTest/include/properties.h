// Copyright 2013 Google Inc. All Rights Reserved.

#ifndef WVCDM_CORE_PROPERTIES_H_
#define WVCDM_CORE_PROPERTIES_H_

#include <map>
#include <string>

#include "cdm_client_property_set.h"
#include "lock.h"
#include "scoped_ptr.h"
#include "wv_cdm_types.h"

#if defined(UNIT_TEST)
# include <gtest/gtest_prod.h>
#endif

namespace wvcdm {

typedef std::map<CdmSessionId, CdmClientPropertySet*>
    CdmClientPropertySetMap;

// This class saves information about features and properties enabled
// for a given platform. At initialization it initializes properties from
// property_configuration.h. That file specifies features selected for each
// platform. Core CDM can then query enabled features though specific getter
// methods.
// Setter methods are provided but their only planned use is for testing.
class Properties {
 public:
  static void Init();

  static inline bool oem_crypto_use_secure_buffers() {
    return oem_crypto_use_secure_buffers_;
  }
  static inline bool oem_crypto_use_fifo() { return oem_crypto_use_fifo_; }
  static inline bool oem_crypto_use_userspace_buffers() {
    return oem_crypto_use_userspace_buffers_;
  }
  static inline bool use_certificates_as_identification() {
    return use_certificates_as_identification_;
  }
  static inline bool security_level_path_backward_compatibility_support() {
    return security_level_path_backward_compatibility_support_;
  }
  static bool GetCompanyName(std::string* company_name);
  static bool GetModelName(std::string* model_name);
  static bool GetArchitectureName(std::string* arch_name);
  static bool GetDeviceName(std::string* device_name);
  static bool GetProductName(std::string* product_name);
  static bool GetBuildInfo(std::string* build_info);
  static bool GetWVCdmVersion(std::string* version);
  static bool GetDeviceFilesBasePath(CdmSecurityLevel security_level,
                                     std::string* base_path);
  static bool GetFactoryKeyboxPath(std::string* keybox);
  static bool GetOEMCryptoPath(std::string* library_name);
  static bool AlwaysUseKeySetIds();

  static bool GetSecurityLevelDirectories(std::vector<std::string>* dirs);
  static bool GetApplicationId(const CdmSessionId& session_id,
                               std::string* app_id);
  static bool GetServiceCertificate(const CdmSessionId& session_id,
                                    std::string* service_certificate);
  static bool SetServiceCertificate(const CdmSessionId& session_id,
                                    const std::string& service_certificate);
  static bool UsePrivacyMode(const CdmSessionId& session_id);
  static uint32_t GetSessionSharingId(const CdmSessionId& session_id);

  static bool AddSessionPropertySet(const CdmSessionId& session_id,
                                    CdmClientPropertySet* property_set);
  static bool RemoveSessionPropertySet(const CdmSessionId& session_id);

 private:
  static CdmClientPropertySet* GetCdmClientPropertySet(
      const CdmSessionId& session_id);
  static void set_oem_crypto_use_secure_buffers(bool flag) {
    oem_crypto_use_secure_buffers_ = flag;
  }
  static void set_oem_crypto_use_fifo(bool flag) {
    oem_crypto_use_fifo_ = flag;
  }
  static void set_oem_crypto_use_userspace_buffers(bool flag) {
    oem_crypto_use_userspace_buffers_ = flag;
  }
  static void set_use_certificates_as_identification(bool flag) {
    use_certificates_as_identification_ = flag;
  }
  static void set_security_level_path_backward_compatibility_support(
      bool flag) {
    security_level_path_backward_compatibility_support_ = flag;
  }

#if defined(UNIT_TEST)
  FRIEND_TEST(CdmSessionTest, InitWithCertificate);
  FRIEND_TEST(CdmSessionTest, InitWithKeybox);
  FRIEND_TEST(CdmSessionTest, ReInitFail);
  FRIEND_TEST(CdmSessionTest, InitFailCryptoError);
  FRIEND_TEST(CdmSessionTest, InitNeedsProvisioning);
  FRIEND_TEST(CdmLicenseTest, PrepareKeyRequestValidation);
#endif

 private:
  static bool oem_crypto_use_secure_buffers_;
  static bool oem_crypto_use_fifo_;
  static bool oem_crypto_use_userspace_buffers_;
  static bool use_certificates_as_identification_;
  static bool security_level_path_backward_compatibility_support_;
  static scoped_ptr<CdmClientPropertySetMap> session_property_set_;

  CORE_DISALLOW_COPY_AND_ASSIGN(Properties);
};

}  // namespace wvcdm

#endif  // WVCDM_CORE_PROPERTIES_H_
