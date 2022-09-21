// Copyright 2012 Google Inc. All Rights Reserved.

#ifndef WVCDM_CORE_LICENSE_H_
#define WVCDM_CORE_LICENSE_H_

#include <set>

#include "initialization_data.h"
#include "scoped_ptr.h"
#include "wv_cdm_types.h"

namespace video_widevine_server {
namespace sdk {
class SignedMessage;
class LicenseRequest;
}
}  // namespace video_widevine_server

namespace wvcdm {

class Clock;
class CryptoSession;
class PolicyEngine;

class CdmLicense {
 public:
  CdmLicense(const CdmSessionId& session_id);
  virtual ~CdmLicense();

  virtual bool Init(const std::string& token, CryptoSession* session,
                    PolicyEngine* policy_engine);

  virtual CdmResponseType PrepareKeyRequest(
      const InitializationData& init_data, const CdmLicenseType license_type,
      const CdmAppParameterMap& app_parameters, CdmKeyMessage* signed_request,
      std::string* server_url);
  virtual CdmResponseType PrepareKeyUpdateRequest(
      bool is_renewal, const CdmAppParameterMap& app_parameters,
      CdmKeyMessage* signed_request, std::string* server_url);
  virtual CdmResponseType HandleKeyResponse(
      const CdmKeyResponse& license_response);
  virtual CdmResponseType HandleKeyUpdateResponse(
      bool is_renewal, const CdmKeyResponse& license_response);

  virtual bool RestoreOfflineLicense(
      const CdmKeyMessage& license_request,
      const CdmKeyResponse& license_response,
      const CdmKeyResponse& license_renewal_response,
      int64_t playback_start_time, int64_t last_playback_time);
  virtual bool RestoreLicenseForRelease(const CdmKeyMessage& license_request,
                                        const CdmKeyResponse& license_response);
  virtual bool HasInitData() { return stored_init_data_.get(); }
  virtual bool IsKeyLoaded(const KeyId& key_id);

  virtual std::string provider_session_token() {
    return provider_session_token_;
  }

  virtual bool is_offline() {
    return is_offline_;
  }

  static CdmResponseType VerifySignedServiceCertificate(
      const std::string& signed_service_certificate);

 private:
  bool PrepareServiceCertificateRequest(CdmKeyMessage* signed_request,
                                        std::string* server_url);

  CdmResponseType HandleKeyErrorResponse(
      const video_widevine_server::sdk::SignedMessage& signed_message);

  CdmResponseType PrepareClientId(
      bool encrypt, const std::string& certificate,
      const CdmAppParameterMap& app_parameters,
      video_widevine_server::sdk::LicenseRequest* license_request);
  template <typename T>
  bool PrepareContentId(const CdmLicenseType license_type,
                        const std::string& request_id, T* content_id);

  static CdmResponseType VerifyAndExtractSignedServiceCertificate(
      const std::string& signed_service_certificate,
      std::string* service_certificate);
  bool GetServiceCertificate(std::string* service_certificate);

  CryptoSession* session_;
  PolicyEngine* policy_engine_;
  std::string server_url_;
  std::string token_;
  const CdmSessionId session_id_;
  scoped_ptr<InitializationData> stored_init_data_;
  bool initialized_;
  std::set<KeyId> loaded_keys_;
  std::string provider_session_token_;
  bool renew_with_client_id_;
  bool is_offline_;

  // Used for certificate based licensing
  CdmKeyMessage key_request_;

  scoped_ptr<Clock> clock_;

  // For testing
  // CdmLicense takes ownership of the clock.
  CdmLicense(const CdmSessionId& session_id, Clock* clock);
#if defined(UNIT_TEST)
  friend class CdmLicenseTest;
#endif

  CORE_DISALLOW_COPY_AND_ASSIGN(CdmLicense);
};

}  // namespace wvcdm

#endif  // WVCDM_CORE_LICENSE_H_
