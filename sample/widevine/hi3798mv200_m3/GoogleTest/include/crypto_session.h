// Copyright 2012 Google Inc. All Rights Reserved.

#ifndef WVCDM_CORE_CRYPTO_SESSSION_H_
#define WVCDM_CORE_CRYPTO_SESSSION_H_

#include <map>
#include <string>

#include "lock.h"
#include "oemcrypto_adapter.h"
#include "OEMCryptoCENC.h"
#include "wv_cdm_types.h"

namespace wvcdm {

class CryptoKey;
typedef std::map<CryptoKeyId, CryptoKey*> CryptoKeyMap;

class CryptoSession {
 public:
  typedef OEMCrypto_HDCP_Capability HdcpCapability;
  typedef enum {
    kUsageDurationsInvalid = 0,
    kUsageDurationPlaybackNotBegun = 1,
    kUsageDurationsValid = 2,
  } UsageDurationStatus;

  CryptoSession();
  virtual ~CryptoSession();

  virtual bool ValidateKeybox();
  virtual bool GetToken(std::string* token);
  virtual CdmSecurityLevel GetSecurityLevel();
  virtual bool GetDeviceUniqueId(std::string* device_id);
  virtual bool GetApiVersion(uint32_t* version);
  virtual bool GetSystemId(uint32_t* system_id);
  virtual bool GetProvisioningId(std::string* provisioning_id);
  virtual uint8_t GetSecurityPatchLevel();

  virtual CdmResponseType Open() { return Open(kLevelDefault); }
  virtual CdmResponseType Open(SecurityLevel requested_security_level);
  virtual void Close();

  virtual bool IsOpen() { return open_; }
  virtual CryptoSessionId oec_session_id() { return oec_session_id_; }

  // Key request/response
  virtual bool GenerateRequestId(std::string* req_id_str);
  virtual bool PrepareRequest(const std::string& key_deriv_message,
                              bool is_provisioning, std::string* signature);
  virtual bool PrepareRenewalRequest(const std::string& message,
                                     std::string* signature);
  virtual CdmResponseType LoadKeys(const std::string& message,
                                   const std::string& signature,
                                   const std::string& mac_key_iv,
                                   const std::string& mac_key,
                                   const std::vector<CryptoKey>& key_array,
                                   const std::string& provider_session_token);
  virtual bool LoadCertificatePrivateKey(std::string& wrapped_key);
  virtual bool RefreshKeys(const std::string& message,
                           const std::string& signature, int num_keys,
                           const CryptoKey* key_array);
  virtual bool GenerateNonce(uint32_t* nonce);
  virtual bool GenerateDerivedKeys(const std::string& message);
  virtual bool GenerateDerivedKeys(const std::string& message,
                                   const std::string& session_key);
  virtual bool RewrapDeviceRSAKey(const std::string& message,
                                  const std::string& signature,
                                  const std::string& nonce,
                                  const std::string& enc_rsa_key,
                                  const std::string& rsa_key_iv,
                                  std::string* wrapped_rsa_key);

  // Media data path
  virtual CdmResponseType Decrypt(const CdmDecryptionParameters& parameters);

  // Usage related methods
  virtual bool UsageInformationSupport(bool* has_support);
  virtual CdmResponseType UpdateUsageInformation();
  virtual CdmResponseType DeactivateUsageInformation(
      const std::string& provider_session_token);
  virtual CdmResponseType GenerateUsageReport(
      const std::string& provider_session_token, std::string* usage_report,
      UsageDurationStatus* usage_duration_status,
      int64_t* seconds_since_started, int64_t* seconds_since_last_played);
  virtual CdmResponseType ReleaseUsageInformation(
      const std::string& message, const std::string& signature,
      const std::string& provider_session_token);
  // Delete a usage information for a single token.  This does not require
  // a signed message from the server.
  virtual CdmResponseType DeleteUsageInformation(
      const std::string& provider_session_token);
  // Delete usage information for a list of tokens.  This does not require
  // a signed message from the server.
  virtual  CdmResponseType DeleteMultipleUsageInformation(
      const std::vector<std::string>& provider_session_tokens);
  virtual CdmResponseType DeleteAllUsageReports();
  virtual bool IsAntiRollbackHwPresent();

  virtual bool GetHdcpCapabilities(HdcpCapability* current,
                                   HdcpCapability* max);
  virtual bool GetRandom(size_t data_length, uint8_t* random_data);
  virtual bool GetNumberOfOpenSessions(size_t* count);
  virtual bool GetMaxNumberOfSessions(size_t* max);

  virtual CdmResponseType GenericEncrypt(const std::string& in_buffer,
                                         const std::string& key_id,
                                         const std::string& iv,
                                         CdmEncryptionAlgorithm algorithm,
                                         std::string* out_buffer);
  virtual CdmResponseType GenericDecrypt(const std::string& in_buffer,
                                         const std::string& key_id,
                                         const std::string& iv,
                                         CdmEncryptionAlgorithm algorithm,
                                         std::string* out_buffer);
  virtual CdmResponseType GenericSign(const std::string& message,
                                      const std::string& key_id,
                                      CdmSigningAlgorithm algorithm,
                                      std::string* signature);
  virtual CdmResponseType GenericVerify(const std::string& message,
                                        const std::string& key_id,
                                        CdmSigningAlgorithm algorithm,
                                        const std::string& signature);

 private:
  void Init();
  void Terminate();
  void GenerateMacContext(const std::string& input_context,
                          std::string* deriv_context);
  void GenerateEncryptContext(const std::string& input_context,
                              std::string* deriv_context);
  bool GenerateSignature(const std::string& message, std::string* signature);
  bool GenerateRsaSignature(const std::string& message, std::string* signature);
  size_t GetOffset(std::string message, std::string field);
  bool SetDestinationBufferType();
  bool SelectKey(const std::string& key_id);

  static const OEMCrypto_Algorithm kInvalidAlgorithm =
      static_cast<OEMCrypto_Algorithm>(-1);

  OEMCrypto_Algorithm GenericSigningAlgorithm(CdmSigningAlgorithm algorithm);
  OEMCrypto_Algorithm GenericEncryptionAlgorithm(
      CdmEncryptionAlgorithm algorithm);
  size_t GenericEncryptionBlockSize(CdmEncryptionAlgorithm algorithm);

  static const size_t kAes128BlockSize = 16;  // Block size for AES_CBC_128
  static const size_t kSignatureSize = 32;  // size for HMAC-SHA256 signature
  static Lock crypto_lock_;
  static bool initialized_;
  static int session_count_;

  bool open_;
  bool update_usage_table_after_close_session_;
  CryptoSessionId oec_session_id_;

  OEMCryptoBufferType destination_buffer_type_;
  bool is_destination_buffer_type_valid_;
  SecurityLevel requested_security_level_;

  KeyId cached_key_id_;

  uint64_t request_id_base_;
  static uint64_t request_id_index_;

  CdmCipherMode cipher_mode_;

  CORE_DISALLOW_COPY_AND_ASSIGN(CryptoSession);
};

}  // namespace wvcdm

#endif  // WVCDM_CORE_CRYPTO_SESSSION_H_
