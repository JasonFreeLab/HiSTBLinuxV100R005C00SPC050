// Copyright 2013 Google Inc. All Rights Reserved.

#ifndef WVCDM_CORE_CERTIFICATE_PROVISIONING_H_
#define WVCDM_CORE_CERTIFICATE_PROVISIONING_H_

#include <string>

#include "crypto_session.h"
#include "oemcrypto_adapter.h"
#include "wv_cdm_types.h"

namespace wvcdm {

class CdmSession;
class FileSystem;

class CertificateProvisioning {
 public:
  CertificateProvisioning() : cert_type_(kCertificateWidevine) {};
  ~CertificateProvisioning() {};

  // Provisioning related methods
  CdmResponseType GetProvisioningRequest(SecurityLevel requested_security_level,
                                         CdmCertificateType cert_type,
                                         const std::string& cert_authority,
                                         const std::string& origin,
                                         CdmProvisioningRequest* request,
                                         std::string* default_url);
  CdmResponseType HandleProvisioningResponse(
      FileSystem* file_system,
      const CdmProvisioningResponse& response,
      std::string* cert,
      std::string* wrapped_key);

 private:
  void ComposeJsonRequestAsQueryString(const std::string& message,
                                       CdmProvisioningRequest* request);
  bool ParseJsonResponse(const CdmProvisioningResponse& json_str,
                         const std::string& start_substr,
                         const std::string& end_substr, std::string* result);
  CryptoSession crypto_session_;
  CdmCertificateType cert_type_;

  CORE_DISALLOW_COPY_AND_ASSIGN(CertificateProvisioning);
};
}  // namespace wvcdm

#endif  // WVCDM_CORE_CERTIFICATE_PROVISIONING_H_
