// Copyright 2016 Google Inc. All Rights Reserved.

#ifndef WVCDM_CORE_LICENSE_KEY_STATUS_H_
#define WVCDM_CORE_LICENSE_KEY_STATUS_H_

#include <map>

#include "crypto_session.h"
#include "license_protocol.pb.h"
#include "wv_cdm_types.h"

namespace wvcdm {

class LicenseKeyStatus;

// Holds all content and operator session keys for a session.
class LicenseKeys {
 public:
  LicenseKeys() {}
  virtual ~LicenseKeys() { Clear(); }

  virtual bool Empty() { return keys_.empty(); }

  // Returns true if the key is a content key (not an operator session key)
  virtual bool IsContentKey(const KeyId& key_id);

  // Returns true if the key is currently usable for content decryption.
  virtual bool CanDecryptContent(const KeyId& key_id);

  // Returns the allowed usages for a key.
  virtual bool GetAllowedUsage(const KeyId& key_id,
                               CdmKeyAllowedUsage* allowed_usage);

  // Applies a new status to each content key.
  // Returns true if any statuses changed, and sets new_usable_keys to
  // true if the status changes resulted in keys becoming usable.
  virtual bool ApplyStatusChange(CdmKeyStatus new_status,
                                 bool* new_usable_keys);

  // Populates the CdmKeyStatusMap with the current content keys.
  virtual void ExtractKeyStatuses(CdmKeyStatusMap* content_keys);

  // Determines whether the specified key can be used under the current
  // resolution and/or hdcp constraints.  If no constraints have been applied
  // to the key, returns true.
  virtual bool MeetsConstraints(const KeyId& key_id);

  // Applies a resolution and/or hdcp change to each key, updating their
  // useability under their constraints.
  virtual void ApplyConstraints(uint32_t new_resolution,
                                CryptoSession::HdcpCapability new_hdcp_level);

  // Extracts the keys from a license and makes them available for
  // querying usage and constraint settings.
  virtual void SetFromLicense(
      const video_widevine_server::sdk::License& license);

 private:
  typedef ::video_widevine_server::sdk::License::KeyContainer KeyContainer;
  typedef std::map<wvcdm::KeyId, LicenseKeyStatus*>::const_iterator
      LicenseKeyStatusIterator;

  void Clear();

  bool is_initialized_;
  std::map<KeyId, LicenseKeyStatus*> keys_;

  CORE_DISALLOW_COPY_AND_ASSIGN(LicenseKeys);
};

// Holds the current license status of a key.
class LicenseKeyStatus {
  friend class LicenseKeys;

 public:
  // Returns true if the key is a content key (not an operator session key)
  virtual bool IsContentKey() { return is_content_key_; }

  // Returns true if the key is currently usable for content decryption
  virtual bool CanDecryptContent();

  // Returns the usages allowed for this key.
  virtual bool GetAllowedUsage(CdmKeyAllowedUsage* allowed_usage);

  // Returns the current status of the key.
  virtual CdmKeyStatus GetKeyStatus() const { return key_status_; }

  // Applies a new status to this key.
  // Returns true if the status changed, and sets new_usable_keys to
  // true if the status changes resulted in the key becoming usable.
  virtual bool ApplyStatusChange(CdmKeyStatus new_status,
                                 bool* new_usable_keys);

  // Returns the current constraint status of this key.  The result
  // may change due to calls to ApplyConstraints().
  // Note: this will return true until the first call to ApplyConstraints().
  virtual bool MeetsConstraints() const { return meets_constraints_; }

  // Applies the given changes in resolution or HDCP settings.
  virtual void ApplyConstraints(
      uint32_t new_resolution, CryptoSession::HdcpCapability new_hdcp_level);

 protected:
  typedef ::video_widevine_server::sdk::License::KeyContainer KeyContainer;
  typedef KeyContainer::OperatorSessionKeyPermissions
      OperatorSessionKeyPermissions;
  typedef KeyContainer::OutputProtection OutputProtection;
  typedef KeyContainer::VideoResolutionConstraint VideoResolutionConstraint;
  typedef ::google::protobuf::RepeatedPtrField<VideoResolutionConstraint>
      ConstraintList;

  LicenseKeyStatus(const KeyContainer& key);

  virtual ~LicenseKeyStatus() {}

 private:

  void ParseContentKey(const KeyContainer& key);
  void ParseOperatorSessionKey(const KeyContainer& key);

  bool HasConstraints() {
    return is_content_key_ && constraints_.size() != 0;
  }

  void SetConstraints(const ConstraintList& constraints);

  bool is_content_key_;
  CdmKeyStatus key_status_;
  bool meets_constraints_;
  CdmKeyAllowedUsage allowed_usage_;
  CryptoSession::HdcpCapability default_hdcp_level_;
  ConstraintList constraints_;

  CORE_DISALLOW_COPY_AND_ASSIGN(LicenseKeyStatus);
};

}  // namespace wvcdm

#endif  // WVCDM_CORE_LICENSE_KEY_STATUS_H_
