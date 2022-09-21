// Copyright 2013 Google Inc. All Rights Reserved.

#ifndef WVCDM_CORE_POLICY_ENGINE_H_
#define WVCDM_CORE_POLICY_ENGINE_H_

#include <map>
#include <string>

#include "license_key_status.h"
#include "license_protocol.pb.h"
#include "scoped_ptr.h"
#include "wv_cdm_types.h"

namespace wvcdm {

using video_widevine_server::sdk::LicenseIdentification;

class Clock;
class CryptoSession;
class WvCdmEventListener;

// This acts as an oracle that basically says "Yes(true) you may still decrypt
// or no(false) you may not decrypt this data anymore."
class PolicyEngine {
 public:
  PolicyEngine(CdmSessionId session_id, WvCdmEventListener* event_listener,
               CryptoSession* crypto_session);
  virtual ~PolicyEngine();

  // The value returned should be taken as a hint rather than an absolute
  // status. It is computed during the last call to either SetLicense/
  // UpdateLicense/OnTimerEvent/BeginDecryption and may be out of sync
  // depending on the amount of time elapsed. The current decryption
  // status is not calculated to avoid overhead in the decryption path.
  virtual bool CanDecrypt(const KeyId& key_id);

  // OnTimerEvent is called when a timer fires. It notifies the Policy Engine
  // that the timer has fired and dispatches the relevant events through
  // |event_listener_|.
  virtual void OnTimerEvent();

  // SetLicense is used in handling the initial license response. It stores
  // an exact copy of the policy information stored in the license.
  // The license state transitions to kLicenseStateCanPlay if the license
  // permits playback.
  virtual void SetLicense(const video_widevine_server::sdk::License& license);

  // SetLicenseForRelease is used when releasing a license. The keys in this
  // license will be ignored, and any old keys will be expired.
  virtual void SetLicenseForRelease(
      const video_widevine_server::sdk::License& license);

  // Call this on first decrypt to set the start of playback.
  virtual void BeginDecryption(void);
  virtual void DecryptionEvent(void);

  // UpdateLicense is used in handling a license response for a renewal request.
  // The response may only contain any policy fields that have changed. In this
  // case an exact copy is not what we want to happen. We also will receive an
  // updated license_start_time from the server. The license will transition to
  // kLicenseStateCanPlay if the license permits playback.
  virtual void UpdateLicense(
      const video_widevine_server::sdk::License& license);

  // Used for notifying the Policy Engine of resolution changes
  virtual void NotifyResolution(uint32_t width, uint32_t height);

  virtual void NotifySessionExpiration();

  virtual CdmResponseType Query(CdmQueryMap* query_response);

  virtual CdmResponseType QueryKeyAllowedUsage(const KeyId& key_id,
                                               CdmKeyAllowedUsage* key_usage);

  virtual const LicenseIdentification& license_id() { return license_id_; }

  bool GetSecondsSinceStarted(int64_t* seconds_since_started);
  bool GetSecondsSinceLastPlayed(int64_t* seconds_since_started);

  // for offline save and restore
  int64_t GetPlaybackStartTime() { return playback_start_time_; }
  int64_t GetLastPlaybackTime() { return last_playback_time_; }
  void RestorePlaybackTimes(int64_t playback_start_time,
                            int64_t last_playback_time);

  bool IsLicenseForFuture() { return license_state_ == kLicenseStatePending; }
  bool IsPlaybackStarted() { return playback_start_time_ > 0; }

  bool IsLicenseOrPlaybackDurationExpired(int64_t current_time);
  int64_t GetLicenseOrPlaybackDurationRemaining();

  bool CanRenew() { return policy_.can_renew(); }

 private:
  friend class PolicyEngineTest;
  friend class PolicyEngineConstraintsTest;

  void InitDevice(CryptoSession* crypto_session);
  void CheckDevice(int64_t current_time);

  void SetDeviceResolution(uint32_t width, uint32_t height) {
    current_resolution_ = width * height;
  }

  typedef enum {
    kLicenseStateInitial,
    kLicenseStatePending,  // if license is issued for sometime in the future
    kLicenseStateCanPlay,
    kLicenseStateNeedRenewal,
    kLicenseStateWaitingLicenseUpdate,
    kLicenseStateExpired
  } LicenseState;

  int64_t GetLicenseExpiryTime();
  int64_t GetPlaybackExpiryTime();

  int64_t GetLicenseDurationRemaining(int64_t current_time);
  int64_t GetPlaybackDurationRemaining(int64_t current_time);

  bool IsRenewalDelayExpired(int64_t current_time);
  bool IsRenewalRecoveryDurationExpired(int64_t current_time);
  bool IsRenewalRetryIntervalExpired(int64_t current_time);

  void UpdateRenewalRequest(int64_t current_time);

  // Notifies updates in keys information and fire OnKeysChange event if
  // key changes.
  void NotifyKeysChange(CdmKeyStatus new_status);

  // Notifies updates in expiry time and fire OnExpirationUpdate event if
  // expiry time changes.
  void NotifyExpirationUpdate();

  // set_clock() is for testing only. It alters ownership of the
  // passed-in pointer.
  void set_clock(Clock* clock);

  LicenseState license_state_;

  // This is the current policy information for this license. This gets updated
  // as license renewals occur.
  video_widevine_server::sdk::License::Policy policy_;

  // This is the license id field from server response. This data gets passed
  // back to the server in each renewal request. When we get a renewal response
  // from the license server we will get an updated id field.
  video_widevine_server::sdk::LicenseIdentification license_id_;

  // The server returns the license start time in the license/license renewal
  // response based off the request time sent by the client in the
  // license request/renewal
  int64_t license_start_time_;
  int64_t playback_start_time_;
  int64_t last_playback_time_;
  int64_t last_expiry_time_;
  bool last_expiry_time_set_;

  // This is used as a reference point for policy management. This value
  // represents an offset from license_start_time_. This is used to
  // calculate the time where renewal retries should occur.
  int64_t next_renewal_time_;
  int64_t policy_max_duration_seconds_;

  // Used to dispatch CDM events.
  CdmSessionId session_id_;
  WvCdmEventListener* event_listener_;

  // Keys associated with license - holds allowed usage, usage constraints,
  // and current status (CdmKeyStatus)
  scoped_ptr<LicenseKeys> license_keys_;

  // Device checks
  int64_t next_device_check_;
  uint32_t current_resolution_;
  CryptoSession* crypto_session_;

  scoped_ptr<Clock> clock_;

  CORE_DISALLOW_COPY_AND_ASSIGN(PolicyEngine);
};

}  // wvcdm

#endif  // WVCDM_CORE_POLICY_ENGINE_H_
