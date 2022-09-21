// Copyright 2012 Google Inc. All Rights Reserved.

#ifndef WVCDM_CORE_CDM_SESSION_H_
#define WVCDM_CORE_CDM_SESSION_H_

#include <set>
#include <string>

#include "crypto_session.h"
#include "device_files.h"
#include "file_store.h"
#include "initialization_data.h"
#include "license.h"
#include "oemcrypto_adapter.h"
#include "policy_engine.h"
#include "scoped_ptr.h"
#include "wv_cdm_types.h"

namespace wvcdm {

class CdmClientPropertySet;
class WvCdmEventListener;

class CdmSession {
 public:
  CdmSession(FileSystem* file_system);
  virtual ~CdmSession();

  virtual CdmResponseType Init(CdmClientPropertySet* cdm_client_property_set);
  virtual CdmResponseType Init(CdmClientPropertySet* cdm_client_property_set,
                               const CdmSessionId* forced_session_id,
                               WvCdmEventListener* event_listener);

  virtual CdmResponseType RestoreOfflineSession(
      const CdmKeySetId& key_set_id, const CdmLicenseType license_type);
  virtual CdmResponseType RestoreUsageSession(
      const CdmKeyMessage& key_request, const CdmKeyResponse& key_response);

  virtual const CdmSessionId& session_id() { return session_id_; }
  virtual const CdmKeySetId& key_set_id() { return key_set_id_; }

  virtual CdmResponseType GenerateKeyRequest(
      const InitializationData& init_data, CdmLicenseType license_type,
      const CdmAppParameterMap& app_parameters, CdmKeyRequest* key_request);

  // AddKey() - Accept license response and extract key info.
  virtual CdmResponseType AddKey(const CdmKeyResponse& key_response);

  // Query session status
  virtual CdmResponseType QueryStatus(CdmQueryMap* query_response);

  // Query license information
  virtual CdmResponseType QueryKeyStatus(CdmQueryMap* query_response);

  // Query allowed usages for key
  virtual CdmResponseType QueryKeyAllowedUsage(const std::string& key_id,
                                               CdmKeyAllowedUsage* key_usage);

  // Query OEMCrypto session ID
  virtual CdmResponseType QueryOemCryptoSessionId(CdmQueryMap* query_response);

  // Decrypt() - Accept encrypted buffer and return decrypted data.
  virtual CdmResponseType Decrypt(const CdmDecryptionParameters& parameters);

  // License renewal
  // GenerateRenewalRequest() - Construct valid renewal request for the current
  // session keys.
  virtual CdmResponseType GenerateRenewalRequest(CdmKeyRequest* key_request);

  // RenewKey() - Accept renewal response and update key info.
  virtual CdmResponseType RenewKey(const CdmKeyResponse& key_response);

  // License release
  // GenerateReleaseRequest() - Construct valid release request for the current
  // session keys.
  virtual CdmResponseType GenerateReleaseRequest(CdmKeyRequest* key_request);

  // ReleaseKey() - Accept response and release key.
  virtual CdmResponseType ReleaseKey(const CdmKeyResponse& key_response);

  virtual bool IsKeyLoaded(const KeyId& key_id);
  virtual int64_t GetDurationRemaining();

  // Used for notifying the Policy Engine of resolution changes
  virtual void NotifyResolution(uint32_t width, uint32_t height);

  virtual void OnTimerEvent(bool update_usage);
  virtual void OnKeyReleaseEvent(const CdmKeySetId& key_set_id);

  virtual void GetApplicationId(std::string* app_id);
  virtual SecurityLevel GetRequestedSecurityLevel() {
    return requested_security_level_;
  }
  virtual CdmSecurityLevel GetSecurityLevel() { return security_level_; }

  // Delete usage information for the list of tokens, |provider_session_tokens|.
  virtual CdmResponseType DeleteMultipleUsageInformation(
      const std::vector<std::string>& provider_session_tokens);
  virtual CdmResponseType UpdateUsageInformation();

  virtual bool is_initial_usage_update() { return is_initial_usage_update_; }
  virtual bool is_usage_update_needed() { return is_usage_update_needed_; }
  virtual void reset_usage_flags() {
    is_initial_usage_update_ = false;
    is_usage_update_needed_ = false;
  }

  virtual bool is_release() { return is_release_; }
  virtual bool is_offline() { return is_offline_; }
  virtual bool is_temporary() { return is_temporary_; }
  virtual bool license_received() { return license_received_; }

  // ReleaseCrypto() - Closes the underlying crypto session but leaves this
  // object alive. It is invalid to call any method that requires a crypto
  // session after calling this. Since calling this renders this object mostly
  // useless, it is preferable to simply delete this object (which will also
  // release the underlying crypto session) rather than call this method.
  virtual CdmResponseType ReleaseCrypto();

  bool DeleteLicense();

  // Generate unique ID for each new session.
  CdmSessionId GenerateSessionId();

  // Generic crypto operations - provides basic crypto operations that an
  // application can use outside of content stream processing

  // Encrypts a buffer of app-level data.
  virtual CdmResponseType GenericEncrypt(const std::string& in_buffer,
                                         const std::string& key_id,
                                         const std::string& iv,
                                         CdmEncryptionAlgorithm algorithm,
                                         std::string* out_buffer);

  // Decrypts a buffer of app-level data.
  virtual CdmResponseType GenericDecrypt(const std::string& in_buffer,
                                         const std::string& key_id,
                                         const std::string& iv,
                                         CdmEncryptionAlgorithm algorithm,
                                         std::string* out_buffer);

  // Computes the signature for a message.
  virtual CdmResponseType GenericSign(const std::string& message,
                                      const std::string& key_id,
                                      CdmSigningAlgorithm algorithm,
                                      std::string* signature);

  // Verifies the signature on a buffer of app-level data.
  virtual CdmResponseType GenericVerify(const std::string& message,
                                        const std::string& key_id,
                                        CdmSigningAlgorithm algorithm,
                                        const std::string& signature);

 private:
  friend class CdmSessionTest;

  bool GenerateKeySetId(CdmKeySetId* key_set_id);

  CdmResponseType StoreLicense();
  bool StoreLicense(DeviceFiles::LicenseState state);

  // These setters are for testing only. Takes ownership of the pointers.
  void set_license_parser(CdmLicense* license_parser);
  void set_crypto_session(CryptoSession* crypto_session);
  void set_policy_engine(PolicyEngine* policy_engine);
  void set_file_handle(DeviceFiles* file_handle);

  // instance variables
  bool initialized_;
  CdmSessionId session_id_;
  scoped_ptr<CdmLicense> license_parser_;
  scoped_ptr<CryptoSession> crypto_session_;
  scoped_ptr<PolicyEngine> policy_engine_;
  scoped_ptr<DeviceFiles> file_handle_;
  bool license_received_;
  bool is_offline_;
  bool is_release_;
  bool is_temporary_;
  CdmSecurityLevel security_level_;
  SecurityLevel requested_security_level_;
  CdmAppParameterMap app_parameters_;

  // decryption and usage flags
  bool is_initial_decryption_;
  bool has_decrypted_since_last_report_;  // ... last report to policy engine.
  bool is_initial_usage_update_;
  bool is_usage_update_needed_;

  // information useful for offline and usage scenarios
  CdmKeyMessage key_request_;
  CdmKeyResponse key_response_;

  // license type offline related information
  CdmInitData offline_init_data_;
  CdmKeyMessage offline_key_renewal_request_;
  CdmKeyResponse offline_key_renewal_response_;
  std::string offline_release_server_url_;

  // license type release and offline related information
  CdmKeySetId key_set_id_;

  bool mock_license_parser_in_use_;
  bool mock_policy_engine_in_use_;

  CORE_DISALLOW_COPY_AND_ASSIGN(CdmSession);
};

}  // namespace wvcdm

#endif  // WVCDM_CORE_CDM_SESSION_H_
