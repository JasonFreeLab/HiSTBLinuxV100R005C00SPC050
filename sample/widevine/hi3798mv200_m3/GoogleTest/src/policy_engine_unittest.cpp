// Copyright 2012 Google Inc. All Rights Reserved.

#include <limits.h>

#include <algorithm>
#include <sstream>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "license.h"
#include "mock_clock.h"
#include "policy_engine.h"
#include "scoped_ptr.h"
#include "test_printers.h"
#include "wv_cdm_event_listener.h"
#include "wv_cdm_constants.h"

namespace wvcdm {

namespace {
const int64_t kDurationUnlimited = 0;
const int64_t kLicenseStartTime = 1413517500;   // ~ 01/01/2013
const int64_t kPlaybackStartTime = kLicenseStartTime + 5;
const int64_t kRentalDuration = 604800;         // 7 days
const int64_t kPlaybackDuration = 172800;       // 48 hours
const int64_t kStreamingLicenseDuration = 300;  // 5 minutes
const int64_t kOfflineLicenseDuration = kRentalDuration;
const int64_t kLicenseRenewalPeriod = 120;           // 2 minutes
const int64_t kLicenseRenewalRetryInterval = 30;     // 30 seconds
const int64_t kLicenseRenewalRecoveryDuration = 30;  // 30 seconds
const int64_t kLowDuration =
    std::min(std::min(std::min(kRentalDuration, kPlaybackDuration),
                      kStreamingLicenseDuration),
             kOfflineLicenseDuration);
const int64_t kHighDuration =
    std::max(std::max(std::max(kRentalDuration, kPlaybackDuration),
                      kStreamingLicenseDuration),
             kOfflineLicenseDuration);
const char* kRenewalServerUrl =
    "https://test.google.com/license/GetCencLicense";
const KeyId kKeyId = "357adc89f1673433c36c621f1b5c41ee";
const KeyId kAnotherKeyId = "another_key_id";
const KeyId kSomeRandomKeyId = "some_random_key_id";
const KeyId kUnknownKeyId = "some_random_unknown_key_id";
const CdmSessionId kSessionId = "mock_session_id";

int64_t GetLicenseRenewalDelay(int64_t license_duration) {
  return license_duration > kLicenseRenewalPeriod
             ? license_duration - kLicenseRenewalPeriod
             : 0;
}

class MockCdmEventListener : public WvCdmEventListener {
 public:
  MOCK_METHOD1(OnSessionRenewalNeeded, void(const CdmSessionId& session_id));
  MOCK_METHOD3(OnSessionKeysChange, void(const CdmSessionId& session_id,
                                         const CdmKeyStatusMap& keys_status,
                                         bool has_new_usable_key));
  MOCK_METHOD2(OnExpirationUpdate, void(const CdmSessionId& session_id,
                                        int64_t new_expiry_time_seconds));
};

}  // namespace

// protobuf generated classes.
using video_widevine_server::sdk::License;
using video_widevine_server::sdk::License_Policy;
using video_widevine_server::sdk::LicenseIdentification;
using video_widevine_server::sdk::STREAMING;
using video_widevine_server::sdk::OFFLINE;

// gmock methods
using ::testing::_;
using ::testing::AtLeast;
using ::testing::InSequence;
using ::testing::MockFunction;
using ::testing::Pair;
using ::testing::Return;
using ::testing::StrictMock;
using ::testing::UnorderedElementsAre;

class PolicyEngineTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    policy_engine_.reset(
        new PolicyEngine(kSessionId, &mock_event_listener_, NULL));
    InjectMockClock();

    license_.set_license_start_time(kLicenseStartTime);

    LicenseIdentification* id = license_.mutable_id();
    id->set_version(1);
    id->set_type(STREAMING);

    License::KeyContainer* key = license_.add_key();
    key->set_type(License::KeyContainer::CONTENT);
    key->set_id(kKeyId);

    License_Policy* policy = license_.mutable_policy();
    policy = license_.mutable_policy();
    policy->set_can_play(true);
    policy->set_can_persist(false);
    policy->set_can_renew(true);
    policy->set_rental_duration_seconds(kRentalDuration);
    policy->set_playback_duration_seconds(kPlaybackDuration);
    policy->set_license_duration_seconds(kStreamingLicenseDuration);
    policy->set_renewal_recovery_duration_seconds(
        kLicenseRenewalRecoveryDuration);

    policy->set_renewal_server_url(kRenewalServerUrl);
    policy->set_renewal_delay_seconds(
        GetLicenseRenewalDelay(kStreamingLicenseDuration));
    policy->set_renewal_retry_interval_seconds(kLicenseRenewalRetryInterval);
    policy->set_renew_with_usage(false);
  }

  int64_t GetMinOfRentalPlaybackLicenseDurations() {
    const License_Policy& policy = license_.policy();
    int64_t rental_duration = policy.rental_duration_seconds();
    int64_t playback_duration = policy.playback_duration_seconds();
    int64_t license_duration = policy.license_duration_seconds();
    if (rental_duration == kDurationUnlimited) rental_duration = LLONG_MAX;
    if (playback_duration == kDurationUnlimited) playback_duration = LLONG_MAX;
    if (license_duration == kDurationUnlimited) license_duration = LLONG_MAX;
    return std::min(std::min(rental_duration, playback_duration),
                    license_duration);
  }

  void InjectMockClock() {
    mock_clock_ = new MockClock();
    policy_engine_->set_clock(mock_clock_);
  }

  void ExpectSessionKeysChange(CdmKeyStatus expected_key_status,
                               bool expected_has_new_usable_key) {
    EXPECT_CALL(mock_event_listener_,
                OnSessionKeysChange(
                    kSessionId, UnorderedElementsAre(
                                    Pair(kKeyId, expected_key_status)),
                    expected_has_new_usable_key));
  }

  void ExpectSessionKeysChange(CdmKeyStatus expected_key1_status,
                               CdmKeyStatus expected_key2_status,
                               bool expected_has_new_usable_key) {
    EXPECT_CALL(mock_event_listener_,
                OnSessionKeysChange(
                    kSessionId, UnorderedElementsAre(
                                    Pair(kKeyId, expected_key1_status),
                                    Pair(kAnotherKeyId, expected_key2_status)),
                    expected_has_new_usable_key));
  }

  StrictMock<MockCdmEventListener> mock_event_listener_;
  MockClock* mock_clock_;
  scoped_ptr<PolicyEngine> policy_engine_;
  License license_;
  MockFunction<void(int i)> check_;
};

TEST_F(PolicyEngineTest, NoLicense) {
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId));
}

TEST_F(PolicyEngineTest, PlaybackSuccess) {
  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + 1))
      .WillOnce(Return(kPlaybackStartTime))
      .WillOnce(Return(kLicenseStartTime + 10));

  ExpectSessionKeysChange(kKeyStatusUsable, true);
  EXPECT_CALL(mock_event_listener_,
              OnExpirationUpdate(_, kLicenseStartTime + kLowDuration));
  EXPECT_CALL(mock_event_listener_,
              OnExpirationUpdate(_, kPlaybackStartTime + kPlaybackDuration));

  policy_engine_->SetLicense(license_);
  policy_engine_->BeginDecryption();
  policy_engine_->OnTimerEvent();

  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));
  EXPECT_FALSE(policy_engine_->CanDecrypt(kSomeRandomKeyId));
}

TEST_F(PolicyEngineTest, PlaybackFailed_CanPlayFalse) {
  License_Policy* policy = license_.mutable_policy();
  policy->set_can_play(false);

  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + 1))
      .WillOnce(Return(kLicenseStartTime + 5));

  ExpectSessionKeysChange(kKeyStatusExpired, false);

  policy_engine_->SetLicense(license_);
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId));

  policy_engine_->OnTimerEvent();

  policy_engine_->BeginDecryption();
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId));
}

TEST_F(PolicyEngineTest, LicenseExpired_RentalDurationExpiredWithoutPlayback) {
  License_Policy* policy = license_.mutable_policy();
  policy->set_rental_duration_seconds(kLowDuration);
  policy->set_license_duration_seconds(kHighDuration);
  policy->set_renewal_delay_seconds(GetLicenseRenewalDelay(kHighDuration));
  int64_t min_duration = GetMinOfRentalPlaybackLicenseDurations();

  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + 1))
      .WillOnce(Return(kPlaybackStartTime))
      .WillOnce(Return(kLicenseStartTime + min_duration - 1))
      .WillOnce(Return(kLicenseStartTime + min_duration));

  InSequence s;
  ExpectSessionKeysChange(kKeyStatusUsable, true);
  EXPECT_CALL(mock_event_listener_,
              OnExpirationUpdate(_, kLicenseStartTime + kLowDuration));
  EXPECT_CALL(check_, Call(1));
  EXPECT_CALL(check_, Call(2));
  ExpectSessionKeysChange(kKeyStatusExpired, false);
  EXPECT_CALL(check_, Call(3));

  policy_engine_->SetLicense(license_);

  for (int i = 1; i <= 3; ++i) {
    EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));
    policy_engine_->OnTimerEvent();
    check_.Call(i);
  }

  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId));
}

TEST_F(PolicyEngineTest, PlaybackOk_RentalDurationNotExpiredWithPlayback) {
  License_Policy* policy = license_.mutable_policy();
  policy->set_rental_duration_seconds(kLowDuration);
  policy->set_license_duration_seconds(kHighDuration);
  policy->set_renewal_delay_seconds(GetLicenseRenewalDelay(kHighDuration));
  int64_t min_duration = GetMinOfRentalPlaybackLicenseDurations();

  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + 1))
      .WillOnce(Return(kPlaybackStartTime))
      .WillOnce(Return(kLicenseStartTime + min_duration - 1))
      .WillOnce(Return(kLicenseStartTime + min_duration));

  InSequence s;
  ExpectSessionKeysChange(kKeyStatusUsable, true);
  EXPECT_CALL(mock_event_listener_,
              OnExpirationUpdate(_, kLicenseStartTime + kLowDuration));
  EXPECT_CALL(mock_event_listener_,
              OnExpirationUpdate(_, kPlaybackStartTime + kPlaybackDuration));
  EXPECT_CALL(check_, Call(1));
  EXPECT_CALL(check_, Call(2));

  policy_engine_->SetLicense(license_);
  policy_engine_->BeginDecryption();

  for (int i = 1; i <= 2; ++i) {
    EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));
    policy_engine_->OnTimerEvent();
    check_.Call(i);
  }

  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));
}

TEST_F(PolicyEngineTest, PlaybackFails_PlaybackDurationExpired) {
  License_Policy* policy = license_.mutable_policy();
  policy->set_license_duration_seconds(kHighDuration);
  policy->set_renewal_delay_seconds(GetLicenseRenewalDelay(kHighDuration));
  int64_t playback_start_time = kLicenseStartTime + 10000;

  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + 1))
      .WillOnce(Return(playback_start_time))
      .WillOnce(Return(playback_start_time + kPlaybackDuration - 2))
      .WillOnce(Return(playback_start_time + kPlaybackDuration + 2));

  InSequence s;
  ExpectSessionKeysChange(kKeyStatusUsable, true);
  EXPECT_CALL(mock_event_listener_,
              OnExpirationUpdate(_, kLicenseStartTime + kHighDuration));
  EXPECT_CALL(mock_event_listener_,
              OnExpirationUpdate(_, playback_start_time + kPlaybackDuration));
  EXPECT_CALL(check_, Call(1));
  ExpectSessionKeysChange(kKeyStatusExpired, false);
  EXPECT_CALL(check_, Call(2));

  policy_engine_->SetLicense(license_);
  policy_engine_->BeginDecryption();

  for (int i = 1; i <= 2; ++i) {
    EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));
    policy_engine_->OnTimerEvent();
    check_.Call(i);
  }

  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId));
}

TEST_F(PolicyEngineTest, LicenseExpired_LicenseDurationExpiredWithoutPlayback) {
  License_Policy* policy = license_.mutable_policy();
  policy->set_can_renew(false);
  int64_t min_duration = GetMinOfRentalPlaybackLicenseDurations();

  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + 1))
      .WillOnce(Return(kPlaybackStartTime))
      .WillOnce(Return(kLicenseStartTime + min_duration - 1))
      .WillOnce(Return(kLicenseStartTime + min_duration));

  InSequence s;
  ExpectSessionKeysChange(kKeyStatusUsable, true);
  EXPECT_CALL(mock_event_listener_,
              OnExpirationUpdate(_, kLicenseStartTime + kLowDuration));
  EXPECT_CALL(check_, Call(1));
  EXPECT_CALL(check_, Call(2));
  ExpectSessionKeysChange(kKeyStatusExpired, false);
  EXPECT_CALL(check_, Call(3));

  policy_engine_->SetLicense(license_);

  for (int i = 1; i <= 3; ++i) {
    EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));
    policy_engine_->OnTimerEvent();
    check_.Call(i);
  }

  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId));
}

TEST_F(PolicyEngineTest, PlaybackOk_LicenseDurationNotExpiredWithPlayback) {
  License_Policy* policy = license_.mutable_policy();
  policy->set_can_renew(false);
  int64_t min_duration = GetMinOfRentalPlaybackLicenseDurations();

  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + 1))
      .WillOnce(Return(kPlaybackStartTime))
      .WillOnce(Return(kLicenseStartTime + min_duration - 1))
      .WillOnce(Return(kLicenseStartTime + min_duration));

  InSequence s;
  ExpectSessionKeysChange(kKeyStatusUsable, true);
  EXPECT_CALL(mock_event_listener_,
              OnExpirationUpdate(_, kLicenseStartTime + kLowDuration));
  EXPECT_CALL(mock_event_listener_,
              OnExpirationUpdate(_, kPlaybackStartTime + kPlaybackDuration));
  EXPECT_CALL(check_, Call(1));
  EXPECT_CALL(check_, Call(2));

  policy_engine_->SetLicense(license_);
  policy_engine_->BeginDecryption();

  for (int i = 1; i <= 2; ++i) {
    EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));
    policy_engine_->OnTimerEvent();
    check_.Call(i);
  }

  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));
}

TEST_F(PolicyEngineTest, PlaybackFails_ExpiryBeforeRenewalDelay) {
  License_Policy* policy = license_.mutable_policy();
  policy->set_renewal_delay_seconds(kStreamingLicenseDuration + 10);
  int64_t min_duration = GetMinOfRentalPlaybackLicenseDurations();

  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + 1))
      .WillOnce(Return(kPlaybackStartTime))
      .WillOnce(Return(kLicenseStartTime + min_duration - 1))
      .WillOnce(Return(kPlaybackStartTime + kPlaybackDuration));

  InSequence s;
  ExpectSessionKeysChange(kKeyStatusUsable, true);
  EXPECT_CALL(mock_event_listener_,
              OnExpirationUpdate(_, kLicenseStartTime + kLowDuration));
  EXPECT_CALL(mock_event_listener_,
              OnExpirationUpdate(_, kPlaybackStartTime + kPlaybackDuration));
  EXPECT_CALL(check_, Call(1));
  ExpectSessionKeysChange(kKeyStatusExpired, false);
  EXPECT_CALL(check_, Call(2));

  policy_engine_->SetLicense(license_);
  policy_engine_->BeginDecryption();

  for (int i = 1; i <= 2; ++i) {
    EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));
    policy_engine_->OnTimerEvent();
    check_.Call(i);
  }

  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId));
}

TEST_F(PolicyEngineTest, PlaybackOk_RentalDuration0) {
  License_Policy* policy = license_.mutable_policy();
  policy->set_rental_duration_seconds(kDurationUnlimited);
  int64_t license_renewal_delay =
      GetLicenseRenewalDelay(kStreamingLicenseDuration);

  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + 1))
      .WillOnce(Return(kPlaybackStartTime))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay - 1))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay))
      .WillOnce(Return(kLicenseStartTime + kStreamingLicenseDuration - 1))
      .WillOnce(Return(kPlaybackStartTime + kPlaybackDuration));

  InSequence s;
  ExpectSessionKeysChange(kKeyStatusUsable, true);
  EXPECT_CALL(mock_event_listener_,
              OnExpirationUpdate(_, kLicenseStartTime + kLowDuration));
  EXPECT_CALL(mock_event_listener_,
              OnExpirationUpdate(_, kPlaybackStartTime + kPlaybackDuration));
  EXPECT_CALL(check_, Call(1));
  EXPECT_CALL(mock_event_listener_, OnSessionRenewalNeeded(_));
  EXPECT_CALL(check_, Call(2));
  EXPECT_CALL(mock_event_listener_, OnSessionRenewalNeeded(_));
  EXPECT_CALL(check_, Call(3));
  ExpectSessionKeysChange(kKeyStatusExpired, false);
  EXPECT_CALL(check_, Call(4));

  policy_engine_->SetLicense(license_);
  policy_engine_->BeginDecryption();

  for (int i = 1; i <= 4; ++i) {
    EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));
    policy_engine_->OnTimerEvent();
    check_.Call(i);
  }

  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId));
}

TEST_F(PolicyEngineTest, PlaybackOk_PlaybackDuration0) {
  License_Policy* policy = license_.mutable_policy();
  policy->set_playback_duration_seconds(kDurationUnlimited);
  policy->set_license_duration_seconds(kHighDuration);
  int64_t license_renewal_delay = GetLicenseRenewalDelay(kHighDuration);
  policy->set_renewal_delay_seconds(license_renewal_delay);

  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime))
      .WillOnce(Return(kPlaybackStartTime))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay - 2))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay + 2))
      .WillOnce(Return(kLicenseStartTime + kHighDuration - 2))
      .WillOnce(Return(kLicenseStartTime + kHighDuration + 2));

  InSequence s;
  ExpectSessionKeysChange(kKeyStatusUsable, true);
  EXPECT_CALL(mock_event_listener_,
              OnExpirationUpdate(_, kLicenseStartTime + kHighDuration));
  EXPECT_CALL(mock_event_listener_,
              OnExpirationUpdate(_, NEVER_EXPIRES));
  EXPECT_CALL(check_, Call(1));
  EXPECT_CALL(mock_event_listener_, OnSessionRenewalNeeded(_));
  EXPECT_CALL(check_, Call(2));
  EXPECT_CALL(mock_event_listener_, OnSessionRenewalNeeded(_));
  EXPECT_CALL(check_, Call(3));
  EXPECT_CALL(check_, Call(4));

  policy_engine_->SetLicense(license_);
  policy_engine_->BeginDecryption();

  for (int i = 1; i <= 4; ++i) {
    EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));
    policy_engine_->OnTimerEvent();
    check_.Call(i);
  }

  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));
}

TEST_F(PolicyEngineTest, PlaybackOk_LicenseDuration0) {
  License_Policy* policy = license_.mutable_policy();
  policy->set_license_duration_seconds(kDurationUnlimited);
  policy->set_rental_duration_seconds(kLowDuration);
  int64_t license_renewal_delay = GetLicenseRenewalDelay(kLowDuration);
  policy->set_renewal_delay_seconds(license_renewal_delay);
  int64_t min_duration = GetMinOfRentalPlaybackLicenseDurations();

  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + 1))
      .WillOnce(Return(kPlaybackStartTime))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay - 1))
      .WillOnce(Return(kLicenseStartTime + min_duration - 1))
      .WillOnce(Return(kLicenseStartTime + kPlaybackStartTime +
                       kPlaybackDuration));

  InSequence s;
  ExpectSessionKeysChange(kKeyStatusUsable, true);
  EXPECT_CALL(mock_event_listener_,
              OnExpirationUpdate(_, kLicenseStartTime + kLowDuration));
  EXPECT_CALL(mock_event_listener_,
              OnExpirationUpdate(_, kPlaybackStartTime + kPlaybackDuration));
  EXPECT_CALL(check_, Call(1));
  EXPECT_CALL(mock_event_listener_, OnSessionRenewalNeeded(_));
  EXPECT_CALL(check_, Call(2));
  ExpectSessionKeysChange(kKeyStatusExpired, false);
  EXPECT_CALL(check_, Call(3));

  policy_engine_->SetLicense(license_);
  policy_engine_->BeginDecryption();

  for (int i = 1; i <= 3; ++i) {
    EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));
    policy_engine_->OnTimerEvent();
    check_.Call(i);
  }

  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId));
}

TEST_F(PolicyEngineTest, PlaybackOk_Durations0) {
  License_Policy* policy = license_.mutable_policy();
  policy->set_rental_duration_seconds(kDurationUnlimited);
  policy->set_playback_duration_seconds(kDurationUnlimited);
  policy->set_license_duration_seconds(kDurationUnlimited);
  policy->set_renewal_delay_seconds(kHighDuration + 10);

  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + 1))
      .WillOnce(Return(kPlaybackStartTime))
      .WillOnce(Return(kLicenseStartTime + kHighDuration - 1))
      .WillOnce(Return(kLicenseStartTime + kHighDuration));

  ExpectSessionKeysChange(kKeyStatusUsable, true);
  EXPECT_CALL(mock_event_listener_, OnExpirationUpdate(_, NEVER_EXPIRES));

  policy_engine_->SetLicense(license_);

  policy_engine_->BeginDecryption();
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));

  policy_engine_->OnTimerEvent();
  policy_engine_->OnTimerEvent();

  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));
}

TEST_F(PolicyEngineTest, PlaybackOk_LicenseWithFutureStartTime) {
  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime - 100))
      .WillOnce(Return(kLicenseStartTime - 50))
      .WillOnce(Return(kLicenseStartTime))
      .WillOnce(Return(kPlaybackStartTime));

  InSequence s;
  ExpectSessionKeysChange(kKeyStatusPending, false);
  EXPECT_CALL(mock_event_listener_,
              OnExpirationUpdate(_, kLicenseStartTime + kLowDuration));
  ExpectSessionKeysChange(kKeyStatusUsable, true);
  EXPECT_CALL(mock_event_listener_,
              OnExpirationUpdate(_, kPlaybackStartTime + kPlaybackDuration));

  policy_engine_->SetLicense(license_);

  policy_engine_->OnTimerEvent();
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId));

  policy_engine_->OnTimerEvent();
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));

  policy_engine_->BeginDecryption();
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));
}

TEST_F(PolicyEngineTest, PlaybackFailed_CanRenewFalse) {
  License_Policy* policy = license_.mutable_policy();
  policy->set_can_renew(false);
  int64_t license_renewal_delay =
      GetLicenseRenewalDelay(kStreamingLicenseDuration);

  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + 1))
      .WillOnce(Return(kPlaybackStartTime))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay - 10))
      .WillOnce(Return(kLicenseStartTime + kStreamingLicenseDuration + 10))
      .WillOnce(Return(kLicenseStartTime + kPlaybackStartTime +
                       kPlaybackDuration));

  InSequence s;
  ExpectSessionKeysChange(kKeyStatusUsable, true);
  EXPECT_CALL(mock_event_listener_,
              OnExpirationUpdate(_, kLicenseStartTime + kLowDuration));
  EXPECT_CALL(mock_event_listener_,
              OnExpirationUpdate(_, kPlaybackStartTime + kPlaybackDuration));
  EXPECT_CALL(check_, Call(1));
  EXPECT_CALL(check_, Call(2));
  ExpectSessionKeysChange(kKeyStatusExpired, false);
  EXPECT_CALL(check_, Call(3));

  policy_engine_->SetLicense(license_);
  policy_engine_->BeginDecryption();

  for (int i = 1; i <= 3; ++i) {
    EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));
    policy_engine_->OnTimerEvent();
    check_.Call(i);
  }

  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId));
}

TEST_F(PolicyEngineTest, PlaybackOk_RenewSuccess) {
  int64_t license_renewal_delay =
      GetLicenseRenewalDelay(kStreamingLicenseDuration);
  int64_t new_license_start_time =
      kLicenseStartTime + license_renewal_delay + 15;

  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + 1))
      .WillOnce(Return(kPlaybackStartTime))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay - 15))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay + 10))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay + 20))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay +
                       kLicenseRenewalRetryInterval + 10));

  InSequence s;
  ExpectSessionKeysChange(kKeyStatusUsable, true);
  EXPECT_CALL(mock_event_listener_,
              OnExpirationUpdate(_, kLicenseStartTime + kLowDuration));
  EXPECT_CALL(mock_event_listener_,
              OnExpirationUpdate(_, kPlaybackStartTime + kPlaybackDuration));
  EXPECT_CALL(check_, Call(1));
  EXPECT_CALL(mock_event_listener_, OnSessionRenewalNeeded(_));
  EXPECT_CALL(check_, Call(2));
  EXPECT_CALL(check_, Call(3));

  policy_engine_->SetLicense(license_);
  policy_engine_->BeginDecryption();

  for (int i = 1; i <= 2; ++i) {
    EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));
    policy_engine_->OnTimerEvent();
    check_.Call(i);
  }

  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));

  license_.set_license_start_time(new_license_start_time);
  LicenseIdentification* id = license_.mutable_id();
  id->set_version(2);
  policy_engine_->UpdateLicense(license_);

  policy_engine_->OnTimerEvent();
  check_.Call(3);

  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));
}

TEST_F(PolicyEngineTest, PlaybackOk_RenewSuccess_WithFutureStartTime) {
  int64_t license_renewal_delay =
      GetLicenseRenewalDelay(kStreamingLicenseDuration);
  int64_t new_license_start_time =
      kLicenseStartTime + license_renewal_delay + 50;

  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + 1))
      .WillOnce(Return(kPlaybackStartTime))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay - 15))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay + 10))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay + 20))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay + 30))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay + 60));

  InSequence s;
  ExpectSessionKeysChange(kKeyStatusUsable, true);
  EXPECT_CALL(mock_event_listener_,
              OnExpirationUpdate(_, kLicenseStartTime + kLowDuration));
  EXPECT_CALL(mock_event_listener_,
              OnExpirationUpdate(_, kPlaybackStartTime + kPlaybackDuration));
  EXPECT_CALL(check_, Call(1));
  EXPECT_CALL(mock_event_listener_, OnSessionRenewalNeeded(_));
  EXPECT_CALL(check_, Call(2));
  ExpectSessionKeysChange(kKeyStatusPending, false);
  EXPECT_CALL(check_, Call(3));
  ExpectSessionKeysChange(kKeyStatusUsable, true);
  EXPECT_CALL(check_, Call(4));

  policy_engine_->SetLicense(license_);
  policy_engine_->BeginDecryption();

  for (int i = 1; i <= 2; ++i) {
    EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));
    policy_engine_->OnTimerEvent();
    check_.Call(i);
  }
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));

  license_.set_license_start_time(new_license_start_time);
  LicenseIdentification* id = license_.mutable_id();
  id->set_version(2);
  policy_engine_->UpdateLicense(license_);

  policy_engine_->OnTimerEvent();
  check_.Call(3);
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId));

  policy_engine_->OnTimerEvent();
  check_.Call(4);
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));
}

TEST_F(PolicyEngineTest, LicenseExpired_RenewFailedVersionNotUpdated) {
  int64_t license_renewal_delay =
      GetLicenseRenewalDelay(kStreamingLicenseDuration);

  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + 1))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay - 10))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay + 10))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay + 40))
      .WillOnce(Return(kLicenseStartTime + kStreamingLicenseDuration + 10));

  InSequence s;
  ExpectSessionKeysChange(kKeyStatusUsable, true);
  EXPECT_CALL(mock_event_listener_,
              OnExpirationUpdate(_, kLicenseStartTime + kLowDuration));
  EXPECT_CALL(check_, Call(1));
  EXPECT_CALL(mock_event_listener_, OnSessionRenewalNeeded(_));
  EXPECT_CALL(check_, Call(2));
  EXPECT_CALL(mock_event_listener_, OnSessionRenewalNeeded(_));
  EXPECT_CALL(check_, Call(3));
  ExpectSessionKeysChange(kKeyStatusExpired, false);
  EXPECT_CALL(check_, Call(4));

  policy_engine_->SetLicense(license_);

  for (int i = 1; i <= 2; ++i) {
    EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));
    policy_engine_->OnTimerEvent();
    check_.Call(i);
  }

  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));

  license_.set_license_start_time(kLicenseStartTime + license_renewal_delay +
                                  30);
  policy_engine_->UpdateLicense(license_);

  policy_engine_->OnTimerEvent();
  check_.Call(3);

  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));

  policy_engine_->OnTimerEvent();
  check_.Call(4);

  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId));
}

TEST_F(PolicyEngineTest, PlaybackFailed_RepeatedRenewFailures) {
  int64_t license_renewal_delay =
      GetLicenseRenewalDelay(kStreamingLicenseDuration);

  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + 1))
      .WillOnce(Return(kPlaybackStartTime))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay - 10))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay + 10))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay + 20))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay + 40))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay + 50))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay + 70))
      .WillOnce(Return(kLicenseStartTime + kStreamingLicenseDuration + 15))
      .WillOnce(Return(kPlaybackStartTime + kPlaybackDuration));

  InSequence s;
  ExpectSessionKeysChange(kKeyStatusUsable, true);
  EXPECT_CALL(mock_event_listener_,
              OnExpirationUpdate(_, kLicenseStartTime + kLowDuration));
  EXPECT_CALL(mock_event_listener_,
              OnExpirationUpdate(_, kPlaybackStartTime + kPlaybackDuration));
  EXPECT_CALL(check_, Call(1));
  EXPECT_CALL(mock_event_listener_, OnSessionRenewalNeeded(_));
  EXPECT_CALL(check_, Call(2));
  EXPECT_CALL(check_, Call(3));
  EXPECT_CALL(mock_event_listener_, OnSessionRenewalNeeded(_));
  EXPECT_CALL(check_, Call(4));
  EXPECT_CALL(check_, Call(5));
  EXPECT_CALL(mock_event_listener_, OnSessionRenewalNeeded(_));
  EXPECT_CALL(check_, Call(6));
  EXPECT_CALL(mock_event_listener_, OnSessionRenewalNeeded(_));
  EXPECT_CALL(check_, Call(7));
  ExpectSessionKeysChange(kKeyStatusExpired, false);
  EXPECT_CALL(check_, Call(8));

  policy_engine_->SetLicense(license_);
  policy_engine_->BeginDecryption();

  for (int i = 1; i <= 8; ++i) {
    EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));
    policy_engine_->OnTimerEvent();
    check_.Call(i);
  }
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId));
}

TEST_F(PolicyEngineTest, PlaybackOk_RenewSuccessAfterExpiry) {
  int64_t license_renewal_delay =
      GetLicenseRenewalDelay(kStreamingLicenseDuration);
  int64_t new_license_start_time = kPlaybackStartTime + kPlaybackDuration + 10;
  int64_t new_playback_duration = kPlaybackDuration + 100;
  int64_t new_license_duration = kStreamingLicenseDuration + 100;

  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + 1))
      .WillOnce(Return(kPlaybackStartTime))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay - 10))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay + 10))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay + 20))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay + 40))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay + 50))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay + 70))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay + 80))
      .WillOnce(Return(kLicenseStartTime + kStreamingLicenseDuration + 10))
      .WillOnce(Return(kPlaybackStartTime + kPlaybackDuration))
      .WillOnce(Return(new_license_start_time))
      .WillOnce(Return(kPlaybackStartTime + kPlaybackDuration + 20));

  InSequence s;
  ExpectSessionKeysChange(kKeyStatusUsable, true);
  EXPECT_CALL(mock_event_listener_,
              OnExpirationUpdate(_, kLicenseStartTime + kLowDuration));
  EXPECT_CALL(mock_event_listener_,
              OnExpirationUpdate(_, kPlaybackStartTime + kPlaybackDuration));
  EXPECT_CALL(check_, Call(1));
  EXPECT_CALL(mock_event_listener_, OnSessionRenewalNeeded(_));
  EXPECT_CALL(check_, Call(2));
  EXPECT_CALL(check_, Call(3));
  EXPECT_CALL(mock_event_listener_, OnSessionRenewalNeeded(_));
  EXPECT_CALL(check_, Call(4));
  EXPECT_CALL(check_, Call(5));
  EXPECT_CALL(mock_event_listener_, OnSessionRenewalNeeded(_));
  EXPECT_CALL(check_, Call(6));
  EXPECT_CALL(check_, Call(7));
  EXPECT_CALL(mock_event_listener_, OnSessionRenewalNeeded(_));
  EXPECT_CALL(check_, Call(8));
  ExpectSessionKeysChange(kKeyStatusExpired, false);
  EXPECT_CALL(check_, Call(9));
  ExpectSessionKeysChange(kKeyStatusUsable, true);
  EXPECT_CALL(
      mock_event_listener_,
      OnExpirationUpdate(_, kPlaybackStartTime + new_playback_duration));
  EXPECT_CALL(check_, Call(10));

  policy_engine_->SetLicense(license_);
  policy_engine_->BeginDecryption();

  for (int i = 1; i <= 9; ++i) {
    EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));
    policy_engine_->OnTimerEvent();
    check_.Call(i);
  }
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId));

  license_.set_license_start_time(new_license_start_time);
  LicenseIdentification* id = license_.mutable_id();
  id->set_version(2);
  License_Policy* policy = license_.mutable_policy();
  policy->set_playback_duration_seconds(new_playback_duration);
  policy->set_license_duration_seconds(new_license_duration);

  policy_engine_->UpdateLicense(license_);

  policy_engine_->OnTimerEvent();
  check_.Call(10);

  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));
}

TEST_F(PolicyEngineTest, PlaybackOk_RenewSuccessAfterFailures) {
  int64_t license_renewal_delay =
      GetLicenseRenewalDelay(kStreamingLicenseDuration);
  int64_t new_license_start_time =
      kLicenseStartTime + license_renewal_delay + 55;
  int64_t new_playback_duration = kPlaybackDuration + 100;

  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + 1))
      .WillOnce(Return(kLicenseStartTime + 5))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay - 10))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay + 10))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay + 20))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay + 40))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay + 50))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay + 55))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay + 67))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay + 200));

  InSequence s;
  ExpectSessionKeysChange(kKeyStatusUsable, true);
  EXPECT_CALL(mock_event_listener_,
              OnExpirationUpdate(_, kLicenseStartTime + kLowDuration));
  EXPECT_CALL(mock_event_listener_,
              OnExpirationUpdate(_, kPlaybackStartTime + kPlaybackDuration));
  EXPECT_CALL(check_, Call(1));
  EXPECT_CALL(mock_event_listener_, OnSessionRenewalNeeded(_));
  EXPECT_CALL(check_, Call(2));
  EXPECT_CALL(check_, Call(3));
  EXPECT_CALL(mock_event_listener_, OnSessionRenewalNeeded(_));
  EXPECT_CALL(check_, Call(4));
  EXPECT_CALL(check_, Call(5));
  EXPECT_CALL(
      mock_event_listener_,
      OnExpirationUpdate(_, kPlaybackStartTime + new_playback_duration));
  EXPECT_CALL(check_, Call(6));
  EXPECT_CALL(check_, Call(7));

  policy_engine_->SetLicense(license_);
  policy_engine_->BeginDecryption();

  for (int i = 1; i <= 5; ++i) {
    EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));
    policy_engine_->OnTimerEvent();
    check_.Call(i);
  }

  license_.set_license_start_time(new_license_start_time);
  LicenseIdentification* id = license_.mutable_id();
  id->set_version(2);
  license_.mutable_policy()->set_playback_duration_seconds(
      new_playback_duration);
  policy_engine_->UpdateLicense(license_);

  for (int i = 6; i <= 7; ++i) {
    EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));
    policy_engine_->OnTimerEvent();
    check_.Call(i);
  }
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));
}

TEST_F(PolicyEngineTest, PlaybackOk_RenewedWithUsage) {
  int64_t new_license_start_time = kLicenseStartTime + 10;
  int64_t new_playback_duration = kPlaybackDuration + 100;

  License_Policy* policy = license_.mutable_policy();
  policy->set_renew_with_usage(true);

  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + 1))
      .WillOnce(Return(kLicenseStartTime + 3))
      .WillOnce(Return(kPlaybackStartTime))
      .WillOnce(Return(kLicenseStartTime + 10))
      .WillOnce(Return(kLicenseStartTime + 20))
      .WillOnce(Return(kLicenseStartTime + 40));

  InSequence s;
  ExpectSessionKeysChange(kKeyStatusUsable, true);
  EXPECT_CALL(mock_event_listener_,
              OnExpirationUpdate(_, kLicenseStartTime + kLowDuration));
  EXPECT_CALL(check_, Call(1));
  EXPECT_CALL(mock_event_listener_,
              OnExpirationUpdate(_, kPlaybackStartTime + kPlaybackDuration));
  EXPECT_CALL(mock_event_listener_, OnSessionRenewalNeeded(_));
  EXPECT_CALL(check_, Call(2));
  EXPECT_CALL(
      mock_event_listener_,
      OnExpirationUpdate(_, kPlaybackStartTime + new_playback_duration));
  EXPECT_CALL(check_, Call(3));

  policy_engine_->SetLicense(license_);

  policy_engine_->OnTimerEvent();
  check_.Call(1);

  policy_engine_->BeginDecryption();
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));

  policy_engine_->OnTimerEvent();
  check_.Call(2);

  license_.set_license_start_time(new_license_start_time);
  license_.mutable_policy()->set_playback_duration_seconds(
      new_playback_duration);
  policy->set_renew_with_usage(false);
  LicenseIdentification* id = license_.mutable_id();
  id->set_version(2);
  policy_engine_->UpdateLicense(license_);

  policy_engine_->OnTimerEvent();
  check_.Call(3);

  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));
}

TEST_F(PolicyEngineTest, MultipleKeysInLicense) {
  const char kSigningKeyId[] = "signing_key";

  license_.clear_key();
  License::KeyContainer* content_key = license_.add_key();
  content_key->set_type(License::KeyContainer::CONTENT);
  content_key->set_id(kKeyId);
  License::KeyContainer* non_content_key = license_.add_key();
  non_content_key->set_type(License::KeyContainer::SIGNING);
  non_content_key->set_id(kSigningKeyId);
  License::KeyContainer* content_key_without_id = license_.add_key();
  content_key_without_id->set_type(License::KeyContainer::CONTENT);
  License::KeyContainer* another_content_key = license_.add_key();
  another_content_key->set_type(License::KeyContainer::CONTENT);
  another_content_key->set_id(kAnotherKeyId);

  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + 1));

  ExpectSessionKeysChange(kKeyStatusUsable, kKeyStatusUsable, true);
  EXPECT_CALL(mock_event_listener_, OnExpirationUpdate(_, _));

  policy_engine_->SetLicense(license_);
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));
  EXPECT_TRUE(policy_engine_->CanDecrypt(kAnotherKeyId));
  EXPECT_FALSE(policy_engine_->CanDecrypt(kSigningKeyId));
  EXPECT_FALSE(policy_engine_->CanDecrypt(kSomeRandomKeyId));
}

class PolicyEngineKeyAllowedUsageTest : public PolicyEngineTest {
 protected:
  enum KeyFlag {
    kKeyFlagNull,
    kKeyFlagFalse,
    kKeyFlagTrue
  };

  static const KeyFlag kEncryptNull = kKeyFlagNull;
  static const KeyFlag kEncryptFalse = kKeyFlagFalse;
  static const KeyFlag kEncryptTrue = kKeyFlagTrue;
  static const KeyFlag kDecryptNull = kKeyFlagNull;
  static const KeyFlag kDecryptFalse = kKeyFlagFalse;
  static const KeyFlag kDecryptTrue = kKeyFlagTrue;
  static const KeyFlag kSignNull = kKeyFlagNull;
  static const KeyFlag kSignFalse = kKeyFlagFalse;
  static const KeyFlag kSignTrue = kKeyFlagTrue;
  static const KeyFlag kVerifyNull = kKeyFlagNull;
  static const KeyFlag kVerifyFalse = kKeyFlagFalse;
  static const KeyFlag kVerifyTrue = kKeyFlagTrue;

  static const KeyFlag kContentSecureFalse = kKeyFlagFalse;
  static const KeyFlag kContentSecureTrue = kKeyFlagTrue;
  static const KeyFlag kContentClearFalse = kKeyFlagFalse;
  static const KeyFlag kContentClearTrue = kKeyFlagTrue;


  void ExpectAllowedContentKeySettings(const CdmKeyAllowedUsage& key_usage,
                                       KeyFlag secure, KeyFlag clear) {
    EXPECT_EQ(key_usage.decrypt_to_secure_buffer, secure == kKeyFlagTrue);
    EXPECT_EQ(key_usage.decrypt_to_clear_buffer, clear == kKeyFlagTrue);
    EXPECT_FALSE(key_usage.generic_encrypt);
    EXPECT_FALSE(key_usage.generic_decrypt);
    EXPECT_FALSE(key_usage.generic_sign);
    EXPECT_FALSE(key_usage.generic_verify);
  }

  void ExpectAllowedOperatorKeySettings(const CdmKeyAllowedUsage& key_usage,
                                        KeyFlag encrypt, KeyFlag decrypt,
                                        KeyFlag sign, KeyFlag verify) {
    EXPECT_FALSE(key_usage.decrypt_to_secure_buffer);
    EXPECT_FALSE(key_usage.decrypt_to_clear_buffer);
    EXPECT_EQ(key_usage.generic_encrypt, encrypt == kKeyFlagTrue);
    EXPECT_EQ(key_usage.generic_decrypt, decrypt == kKeyFlagTrue);
    EXPECT_EQ(key_usage.generic_sign, sign == kKeyFlagTrue);
    EXPECT_EQ(key_usage.generic_verify, verify == kKeyFlagTrue);
  }

  void ExpectSecureContentKey(const KeyId& key_id) {
    CdmKeyAllowedUsage key_usage;
    EXPECT_EQ(NO_ERROR,
              policy_engine_->QueryKeyAllowedUsage(key_id, &key_usage));

    ExpectAllowedContentKeySettings(key_usage, kContentSecureTrue,
                                    kContentSecureFalse);
  }

  void ExpectLessSecureContentKey(const KeyId& key_id) {
    CdmKeyAllowedUsage key_usage;
    EXPECT_EQ(NO_ERROR,
              policy_engine_->QueryKeyAllowedUsage(key_id, &key_usage));

    ExpectAllowedContentKeySettings(key_usage, kContentSecureTrue,
                                    kContentSecureTrue);
  }

  void ExpectOperatorSessionKey(const KeyId& key_id, KeyFlag encrypt,
                                KeyFlag decrypt, KeyFlag sign, KeyFlag verify) {
    CdmKeyAllowedUsage key_usage;
    EXPECT_EQ(NO_ERROR,
              policy_engine_->QueryKeyAllowedUsage(key_id, &key_usage));

    ExpectAllowedOperatorKeySettings(key_usage, encrypt, decrypt, sign, verify);
  }

  void AddOperatorSessionKey(const KeyId& key_id, KeyFlag encrypt,
                             KeyFlag decrypt, KeyFlag sign, KeyFlag verify) {
    License::KeyContainer* non_content_key = license_.add_key();
    non_content_key->set_type(License::KeyContainer::OPERATOR_SESSION);
    non_content_key->set_id(key_id);
    License::KeyContainer::OperatorSessionKeyPermissions* permissions =
        non_content_key->mutable_operator_session_key_permissions();
    if (encrypt != kKeyFlagNull) {
      permissions->set_allow_encrypt(encrypt == kKeyFlagTrue);
    }
    if (decrypt != kKeyFlagNull) {
      permissions->set_allow_decrypt(decrypt == kKeyFlagTrue);
    }
    if (sign != kKeyFlagNull) {
      permissions->set_allow_sign(sign == kKeyFlagTrue);
    }
    if (verify != kKeyFlagNull) {
      permissions->set_allow_signature_verify(verify == kKeyFlagTrue);
    }
  }
};

TEST_F(PolicyEngineKeyAllowedUsageTest, AllowedUsageBasic) {

  const KeyId kGenericKeyId = "oper_session_key";

  license_.clear_key();

  // most secure
  License::KeyContainer* content_key = license_.add_key();
  content_key->set_type(License::KeyContainer::CONTENT);
  content_key->set_id(kKeyId);
  content_key->set_level(License::KeyContainer::HW_SECURE_ALL);

  // generic operator session key (sign)
  AddOperatorSessionKey(kGenericKeyId, kEncryptNull, kDecryptNull, kSignTrue,
                        kVerifyNull);

  License::KeyContainer* content_key_without_id = license_.add_key();
  content_key_without_id->set_type(License::KeyContainer::CONTENT);

  // default level - less secure
  License::KeyContainer* another_content_key = license_.add_key();
  another_content_key->set_type(License::KeyContainer::CONTENT);
  another_content_key->set_id(kAnotherKeyId);

  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + 1));

  ExpectSessionKeysChange(kKeyStatusUsable, kKeyStatusUsable, true);
  EXPECT_CALL(mock_event_listener_, OnExpirationUpdate(_, _));

  policy_engine_->SetLicense(license_);

  ExpectSecureContentKey(kKeyId);
  ExpectLessSecureContentKey(kAnotherKeyId);
  ExpectOperatorSessionKey(kGenericKeyId, kEncryptNull, kDecryptNull,
                           kSignTrue, kVerifyNull);

  CdmKeyAllowedUsage key_usage;
  EXPECT_EQ(KEY_NOT_FOUND_1,
            policy_engine_->QueryKeyAllowedUsage(kUnknownKeyId, &key_usage));
}

TEST_F(PolicyEngineKeyAllowedUsageTest, AllowedUsageGeneric) {

  const KeyId kGenericEncryptKeyId = "oper_session_key_1";
  const KeyId kGenericDecryptKeyId = "oper_session_key_2";
  const KeyId kGenericSignKeyId = "oper_session_key_3";
  const KeyId kGenericVerifyKeyId = "oper_session_key_4";
  const KeyId kGenericFullKeyId = "oper_session_key_5";
  const KeyId kGenericExplicitKeyId = "oper_session_key_6";

  license_.clear_key();

  // more secure
  License::KeyContainer* content_key = license_.add_key();
  content_key->set_type(License::KeyContainer::CONTENT);
  content_key->set_id(kKeyId);
  content_key->set_level(License::KeyContainer::HW_SECURE_DECODE);

  // less secure
  License::KeyContainer* another_content_key = license_.add_key();
  another_content_key->set_type(License::KeyContainer::CONTENT);
  another_content_key->set_id(kAnotherKeyId);
  another_content_key->set_level(License::KeyContainer::HW_SECURE_CRYPTO);

  // generic operator session keys
  AddOperatorSessionKey(kGenericSignKeyId, kEncryptNull, kDecryptNull,
                        kSignTrue, kVerifyNull);
  AddOperatorSessionKey(kGenericEncryptKeyId, kEncryptTrue, kDecryptNull,
                        kSignNull, kVerifyNull);
  AddOperatorSessionKey(kGenericDecryptKeyId, kEncryptNull, kDecryptTrue,
                        kSignNull, kVerifyNull);
  AddOperatorSessionKey(kGenericVerifyKeyId, kEncryptNull, kDecryptNull,
                        kSignNull, kVerifyTrue);
  AddOperatorSessionKey(kGenericFullKeyId, kEncryptTrue, kDecryptTrue,
                        kSignTrue, kVerifyTrue);
  AddOperatorSessionKey(kGenericExplicitKeyId, kEncryptFalse, kDecryptTrue,
                        kSignFalse, kVerifyTrue);

  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + 1));

  ExpectSessionKeysChange(kKeyStatusUsable, kKeyStatusUsable, true);
  EXPECT_CALL(mock_event_listener_, OnExpirationUpdate(_, _));

  policy_engine_->SetLicense(license_);

  ExpectSecureContentKey(kKeyId);
  ExpectLessSecureContentKey(kAnotherKeyId);
  ExpectOperatorSessionKey(kGenericEncryptKeyId, kEncryptTrue, kDecryptFalse,
                           kSignFalse, kVerifyFalse);
  ExpectOperatorSessionKey(kGenericDecryptKeyId, kEncryptFalse, kDecryptTrue,
                           kSignFalse, kVerifyFalse);
  ExpectOperatorSessionKey(kGenericSignKeyId, kEncryptFalse, kDecryptFalse,
                           kSignTrue, kVerifyFalse);
  ExpectOperatorSessionKey(kGenericVerifyKeyId, kEncryptFalse, kDecryptFalse,
                           kSignFalse, kVerifyTrue);
  ExpectOperatorSessionKey(kGenericFullKeyId, kEncryptTrue, kDecryptTrue,
                           kSignTrue, kVerifyTrue);
  ExpectOperatorSessionKey(kGenericExplicitKeyId, kEncryptFalse, kDecryptTrue,
                           kSignFalse, kVerifyTrue);
}

class PolicyEngineQueryTest : public PolicyEngineTest {
 protected:
  virtual void SetUp() {
    PolicyEngineTest::SetUp();
    policy_engine_.reset(new PolicyEngine(kSessionId, NULL, NULL));
    InjectMockClock();
  }
};

TEST_F(PolicyEngineQueryTest, QuerySuccess_LicenseNotReceived) {
  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime));

  CdmQueryMap query_info;
  EXPECT_EQ(NO_ERROR, policy_engine_->Query(&query_info));
  EXPECT_EQ(0u, query_info.size());
}

TEST_F(PolicyEngineQueryTest, QuerySuccess_LicenseStartTimeNotSet) {
  license_.clear_license_start_time();

  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + 1));

  policy_engine_->SetLicense(license_);

  CdmQueryMap query_info;
  EXPECT_EQ(NO_ERROR, policy_engine_->Query(&query_info));
  EXPECT_EQ(0u, query_info.size());
}

TEST_F(PolicyEngineQueryTest, QuerySuccess) {
  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + 1))
      .WillOnce(Return(kLicenseStartTime + 100));

  policy_engine_->SetLicense(license_);

  CdmQueryMap query_info;
  EXPECT_EQ(NO_ERROR, policy_engine_->Query(&query_info));
  EXPECT_EQ(QUERY_VALUE_STREAMING, query_info[QUERY_KEY_LICENSE_TYPE]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_PLAY_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_FALSE, query_info[QUERY_KEY_PERSIST_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_RENEW_ALLOWED]);

  int64_t remaining_time;
  std::istringstream ss;
  ss.str(query_info[QUERY_KEY_LICENSE_DURATION_REMAINING]);
  ss >> remaining_time;
  ss.clear();
  EXPECT_EQ(kStreamingLicenseDuration - 100, remaining_time);
  ss.str(query_info[QUERY_KEY_PLAYBACK_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(kPlaybackDuration, remaining_time);
  EXPECT_EQ(kRenewalServerUrl, query_info[QUERY_KEY_RENEWAL_SERVER_URL]);
}

TEST_F(PolicyEngineQueryTest, QuerySuccess_PlaybackNotBegun) {
  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + 1))
      .WillOnce(Return(kLicenseStartTime + 100))
      .WillOnce(Return(kLicenseStartTime + 200));

  policy_engine_->SetLicense(license_);

  CdmQueryMap query_info;
  EXPECT_EQ(NO_ERROR, policy_engine_->Query(&query_info));
  EXPECT_EQ(QUERY_VALUE_STREAMING, query_info[QUERY_KEY_LICENSE_TYPE]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_PLAY_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_FALSE, query_info[QUERY_KEY_PERSIST_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_RENEW_ALLOWED]);

  int64_t remaining_time;
  std::istringstream ss;
  ss.str(query_info[QUERY_KEY_LICENSE_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(kStreamingLicenseDuration - 100, remaining_time);
  ss.clear();
  ss.str(query_info[QUERY_KEY_PLAYBACK_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(kPlaybackDuration, remaining_time);
  EXPECT_EQ(kRenewalServerUrl, query_info[QUERY_KEY_RENEWAL_SERVER_URL]);

  EXPECT_EQ(NO_ERROR, policy_engine_->Query(&query_info));
  EXPECT_EQ(QUERY_VALUE_STREAMING, query_info[QUERY_KEY_LICENSE_TYPE]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_PLAY_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_FALSE, query_info[QUERY_KEY_PERSIST_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_RENEW_ALLOWED]);

  ss.clear();
  ss.str(query_info[QUERY_KEY_LICENSE_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(kStreamingLicenseDuration - 200, remaining_time);
  ss.clear();
  ss.str(query_info[QUERY_KEY_PLAYBACK_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(kPlaybackDuration, remaining_time);
  EXPECT_EQ(kRenewalServerUrl, query_info[QUERY_KEY_RENEWAL_SERVER_URL]);
}

TEST_F(PolicyEngineQueryTest, QuerySuccess_PlaybackBegun) {
  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + 1))
      .WillOnce(Return(kLicenseStartTime + 50))
      .WillOnce(Return(kLicenseStartTime + 100))
      .WillOnce(Return(kLicenseStartTime + 150))
      .WillOnce(Return(kLicenseStartTime + 200));

  policy_engine_->SetLicense(license_);

  CdmQueryMap query_info;
  EXPECT_EQ(NO_ERROR, policy_engine_->Query(&query_info));
  EXPECT_EQ(QUERY_VALUE_STREAMING, query_info[QUERY_KEY_LICENSE_TYPE]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_PLAY_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_FALSE, query_info[QUERY_KEY_PERSIST_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_RENEW_ALLOWED]);

  int64_t remaining_time;
  std::istringstream ss;
  ss.str(query_info[QUERY_KEY_LICENSE_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(kStreamingLicenseDuration - 50, remaining_time);
  ss.clear();
  ss.str(query_info[QUERY_KEY_PLAYBACK_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(kPlaybackDuration, remaining_time);
  EXPECT_EQ(kRenewalServerUrl, query_info[QUERY_KEY_RENEWAL_SERVER_URL]);

  policy_engine_->BeginDecryption();
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));

  policy_engine_->OnTimerEvent();

  EXPECT_EQ(NO_ERROR, policy_engine_->Query(&query_info));
  EXPECT_EQ(QUERY_VALUE_STREAMING, query_info[QUERY_KEY_LICENSE_TYPE]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_PLAY_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_FALSE, query_info[QUERY_KEY_PERSIST_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_RENEW_ALLOWED]);

  ss.clear();
  ss.str(query_info[QUERY_KEY_LICENSE_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(kStreamingLicenseDuration - 200, remaining_time);
  ss.clear();
  ss.str(query_info[QUERY_KEY_PLAYBACK_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(kPlaybackDuration - 100, remaining_time);
  EXPECT_EQ(kRenewalServerUrl, query_info[QUERY_KEY_RENEWAL_SERVER_URL]);
}

TEST_F(PolicyEngineQueryTest, QuerySuccess_Offline) {
  LicenseIdentification* id = license_.mutable_id();
  id->set_type(OFFLINE);

  License_Policy* policy = license_.mutable_policy();
  policy->set_can_persist(true);
  policy->set_can_renew(false);
  policy->set_license_duration_seconds(kOfflineLicenseDuration);
  policy->set_renewal_delay_seconds(
      GetLicenseRenewalDelay(kOfflineLicenseDuration));

  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + 1))
      .WillOnce(Return(kLicenseStartTime + 100))
      .WillOnce(Return(kLicenseStartTime + 200))
      .WillOnce(Return(kLicenseStartTime + 300));

  policy_engine_->SetLicense(license_);

  policy_engine_->OnTimerEvent();

  policy_engine_->BeginDecryption();
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));

  CdmQueryMap query_info;
  EXPECT_EQ(NO_ERROR, policy_engine_->Query(&query_info));
  EXPECT_EQ(QUERY_VALUE_OFFLINE, query_info[QUERY_KEY_LICENSE_TYPE]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_PLAY_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_PERSIST_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_FALSE, query_info[QUERY_KEY_RENEW_ALLOWED]);

  int64_t remaining_time;
  std::istringstream ss;
  ss.str(query_info[QUERY_KEY_LICENSE_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(kOfflineLicenseDuration - 300, remaining_time);
  ss.clear();
  ss.str(query_info[QUERY_KEY_PLAYBACK_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(kPlaybackDuration - 100, remaining_time);
  EXPECT_EQ(kRenewalServerUrl, query_info[QUERY_KEY_RENEWAL_SERVER_URL]);
}

TEST_F(PolicyEngineQueryTest, QuerySuccess_InitialRentalDurationExpired) {
  License_Policy* policy = license_.mutable_policy();
  policy->set_rental_duration_seconds(kLowDuration);
  policy->set_license_duration_seconds(kHighDuration);

  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + kLowDuration + 1))
      .WillOnce(Return(kLicenseStartTime + kLowDuration + 5));

  policy_engine_->SetLicense(license_);

  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId));

  CdmQueryMap query_info;
  EXPECT_EQ(NO_ERROR, policy_engine_->Query(&query_info));
  EXPECT_EQ(QUERY_VALUE_STREAMING, query_info[QUERY_KEY_LICENSE_TYPE]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_PLAY_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_FALSE, query_info[QUERY_KEY_PERSIST_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_RENEW_ALLOWED]);

  int64_t remaining_time;
  std::istringstream ss;
  ss.str(query_info[QUERY_KEY_LICENSE_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(0, remaining_time);
  ss.clear();
  ss.str(query_info[QUERY_KEY_PLAYBACK_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(kPlaybackDuration, remaining_time);
  EXPECT_EQ(kRenewalServerUrl, query_info[QUERY_KEY_RENEWAL_SERVER_URL]);
}

TEST_F(PolicyEngineQueryTest, QuerySuccess_InitialLicenseDurationExpired) {
  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + kStreamingLicenseDuration + 1))
      .WillOnce(Return(kLicenseStartTime + kStreamingLicenseDuration + 5));

  policy_engine_->SetLicense(license_);

  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId));

  CdmQueryMap query_info;
  EXPECT_EQ(NO_ERROR, policy_engine_->Query(&query_info));
  EXPECT_EQ(QUERY_VALUE_STREAMING, query_info[QUERY_KEY_LICENSE_TYPE]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_PLAY_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_FALSE, query_info[QUERY_KEY_PERSIST_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_RENEW_ALLOWED]);

  int64_t remaining_time;
  std::istringstream ss;
  ss.str(query_info[QUERY_KEY_LICENSE_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(0, remaining_time);
  ss.clear();
  ss.str(query_info[QUERY_KEY_PLAYBACK_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(kPlaybackDuration, remaining_time);
  EXPECT_EQ(kRenewalServerUrl, query_info[QUERY_KEY_RENEWAL_SERVER_URL]);
}

TEST_F(PolicyEngineQueryTest, QuerySuccess_CanPlayFalse) {
  LicenseIdentification* id = license_.mutable_id();
  id->set_type(OFFLINE);

  License_Policy* policy = license_.mutable_policy();
  policy->set_can_play(false);
  policy->set_can_persist(true);
  policy->set_license_duration_seconds(kOfflineLicenseDuration);
  policy->set_renewal_delay_seconds(
      GetLicenseRenewalDelay(kOfflineLicenseDuration));

  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + 1))
      .WillOnce(Return(kLicenseStartTime + 5))
      .WillOnce(Return(kLicenseStartTime + 100));

  policy_engine_->SetLicense(license_);
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId));

  policy_engine_->OnTimerEvent();

  policy_engine_->BeginDecryption();
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId));

  CdmQueryMap query_info;
  EXPECT_EQ(NO_ERROR, policy_engine_->Query(&query_info));
  EXPECT_EQ(QUERY_VALUE_OFFLINE, query_info[QUERY_KEY_LICENSE_TYPE]);
  EXPECT_EQ(QUERY_VALUE_FALSE, query_info[QUERY_KEY_PLAY_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_PERSIST_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_RENEW_ALLOWED]);

  int64_t remaining_time;
  std::istringstream ss;
  ss.str(query_info[QUERY_KEY_LICENSE_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(kOfflineLicenseDuration - 100, remaining_time);
  ss.clear();
  ss.str(query_info[QUERY_KEY_PLAYBACK_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(kPlaybackDuration, remaining_time);
  EXPECT_EQ(kRenewalServerUrl, query_info[QUERY_KEY_RENEWAL_SERVER_URL]);
}

TEST_F(PolicyEngineQueryTest, QuerySuccess_RentalDurationExpired) {
  License_Policy* policy = license_.mutable_policy();
  policy->set_rental_duration_seconds(kLowDuration);
  policy->set_license_duration_seconds(kHighDuration);
  policy->set_renewal_delay_seconds(GetLicenseRenewalDelay(kHighDuration));

  int64_t min_duration = GetMinOfRentalPlaybackLicenseDurations();
  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + 1))
      .WillOnce(Return(kPlaybackStartTime))
      .WillOnce(Return(kLicenseStartTime + min_duration - 1))
      .WillOnce(Return(kLicenseStartTime + min_duration))
      .WillOnce(Return(kLicenseStartTime + min_duration + 5));

  policy_engine_->SetLicense(license_);

  policy_engine_->BeginDecryption();
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));

  for (int i = 1; i <= 2; ++i) {
    policy_engine_->OnTimerEvent();
  }

  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));

  CdmQueryMap query_info;
  EXPECT_EQ(NO_ERROR, policy_engine_->Query(&query_info));
  EXPECT_EQ(QUERY_VALUE_STREAMING, query_info[QUERY_KEY_LICENSE_TYPE]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_PLAY_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_FALSE, query_info[QUERY_KEY_PERSIST_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_RENEW_ALLOWED]);

  int64_t remaining_time;
  std::istringstream ss;
  ss.str(query_info[QUERY_KEY_LICENSE_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(0, remaining_time);
  ss.clear();
  ss.str(query_info[QUERY_KEY_PLAYBACK_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(kPlaybackDuration - min_duration, remaining_time);
  EXPECT_EQ(kRenewalServerUrl, query_info[QUERY_KEY_RENEWAL_SERVER_URL]);
}

TEST_F(PolicyEngineQueryTest, QuerySuccess_PlaybackDurationExpired) {
  License_Policy* policy = license_.mutable_policy();
  policy->set_playback_duration_seconds(kLowDuration);
  policy->set_license_duration_seconds(kHighDuration);
  policy->set_renewal_delay_seconds(GetLicenseRenewalDelay(kHighDuration));

  int64_t min_duration = GetMinOfRentalPlaybackLicenseDurations();
  int64_t playback_start_time = kLicenseStartTime + 10000;
  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + 1))
      .WillOnce(Return(playback_start_time))
      .WillOnce(Return(playback_start_time - 2 + min_duration))
      .WillOnce(Return(playback_start_time + 2 + min_duration))
      .WillOnce(Return(playback_start_time + 5 + min_duration));

  policy_engine_->SetLicense(license_);

  policy_engine_->BeginDecryption();
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));

  for (int i = 1; i <= 2; ++i) {
    policy_engine_->OnTimerEvent();
  }

  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId));

  CdmQueryMap query_info;
  EXPECT_EQ(NO_ERROR, policy_engine_->Query(&query_info));
  EXPECT_EQ(QUERY_VALUE_STREAMING, query_info[QUERY_KEY_LICENSE_TYPE]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_PLAY_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_FALSE, query_info[QUERY_KEY_PERSIST_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_RENEW_ALLOWED]);

  int64_t remaining_time;
  std::istringstream ss;
  ss.str(query_info[QUERY_KEY_LICENSE_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(kHighDuration - 10005 - min_duration, remaining_time);
  ss.clear();
  ss.str(query_info[QUERY_KEY_PLAYBACK_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(0, remaining_time);
  EXPECT_EQ(kRenewalServerUrl, query_info[QUERY_KEY_RENEWAL_SERVER_URL]);
}

TEST_F(PolicyEngineQueryTest, QuerySuccess_LicenseDurationExpired) {
  License_Policy* policy = license_.mutable_policy();
  policy->set_can_renew(false);
  int64_t min_duration = GetMinOfRentalPlaybackLicenseDurations();

  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + 1))
      .WillOnce(Return(kLicenseStartTime + 5))
      .WillOnce(Return(kLicenseStartTime + min_duration - 1))
      .WillOnce(Return(kLicenseStartTime + min_duration))
      .WillOnce(Return(kLicenseStartTime + min_duration + 5));

  policy_engine_->SetLicense(license_);

  policy_engine_->BeginDecryption();
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));

  for (int i = 1; i <= 2; ++i) {
    policy_engine_->OnTimerEvent();
  }

  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));

  CdmQueryMap query_info;
  EXPECT_EQ(NO_ERROR, policy_engine_->Query(&query_info));
  EXPECT_EQ(QUERY_VALUE_STREAMING, query_info[QUERY_KEY_LICENSE_TYPE]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_PLAY_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_FALSE, query_info[QUERY_KEY_PERSIST_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_FALSE, query_info[QUERY_KEY_RENEW_ALLOWED]);

  int64_t remaining_time;
  std::istringstream ss;
  ss.str(query_info[QUERY_KEY_LICENSE_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(0, remaining_time);
  ss.clear();
  ss.str(query_info[QUERY_KEY_PLAYBACK_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(kPlaybackDuration - min_duration, remaining_time);
  EXPECT_EQ(kRenewalServerUrl, query_info[QUERY_KEY_RENEWAL_SERVER_URL]);
}

TEST_F(PolicyEngineQueryTest, QuerySuccess_RentalDuration0) {
  License_Policy* policy = license_.mutable_policy();
  policy->set_rental_duration_seconds(kDurationUnlimited);
  int64_t license_renewal_delay =
      GetLicenseRenewalDelay(kStreamingLicenseDuration);

  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + 1))
      .WillOnce(Return(kLicenseStartTime + 5))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay - 1))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay))
      .WillOnce(Return(kLicenseStartTime + kStreamingLicenseDuration - 1))
      .WillOnce(Return(kLicenseStartTime + kStreamingLicenseDuration))
      .WillOnce(Return(kLicenseStartTime + kStreamingLicenseDuration + 5));

  policy_engine_->SetLicense(license_);

  policy_engine_->BeginDecryption();
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));

  for (int i = 1; i <= 4; ++i) {
    policy_engine_->OnTimerEvent();
  }

  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));

  CdmQueryMap query_info;
  EXPECT_EQ(NO_ERROR, policy_engine_->Query(&query_info));
  EXPECT_EQ(QUERY_VALUE_STREAMING, query_info[QUERY_KEY_LICENSE_TYPE]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_PLAY_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_FALSE, query_info[QUERY_KEY_PERSIST_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_RENEW_ALLOWED]);

  int64_t remaining_time;
  std::istringstream ss;
  ss.str(query_info[QUERY_KEY_LICENSE_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(0, remaining_time);
  ss.clear();
  ss.str(query_info[QUERY_KEY_PLAYBACK_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(kPlaybackDuration - kStreamingLicenseDuration, remaining_time);
  EXPECT_EQ(kRenewalServerUrl, query_info[QUERY_KEY_RENEWAL_SERVER_URL]);
}

TEST_F(PolicyEngineQueryTest, QuerySuccess_PlaybackDuration0) {
  License_Policy* policy = license_.mutable_policy();
  policy->set_playback_duration_seconds(kDurationUnlimited);
  policy->set_license_duration_seconds(kHighDuration);
  int64_t license_renewal_delay = GetLicenseRenewalDelay(kHighDuration);
  policy->set_renewal_delay_seconds(license_renewal_delay);

  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime))
      .WillOnce(Return(kLicenseStartTime + 5))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay - 2))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay + 2))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay + 5))
      .WillOnce(Return(kLicenseStartTime + kHighDuration - 2))
      .WillOnce(Return(kLicenseStartTime + kHighDuration + 2))
      .WillOnce(Return(kLicenseStartTime + kHighDuration + 5));

  policy_engine_->SetLicense(license_);

  policy_engine_->BeginDecryption();
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));

  for (int i = 1; i <= 2; ++i) {
    policy_engine_->OnTimerEvent();
  }

  CdmQueryMap query_info;
  EXPECT_EQ(NO_ERROR, policy_engine_->Query(&query_info));
  EXPECT_EQ(QUERY_VALUE_STREAMING, query_info[QUERY_KEY_LICENSE_TYPE]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_PLAY_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_FALSE, query_info[QUERY_KEY_PERSIST_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_RENEW_ALLOWED]);

  int64_t remaining_time;
  std::istringstream ss;
  ss.str(query_info[QUERY_KEY_LICENSE_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(kHighDuration - license_renewal_delay - 5, remaining_time);
  ss.clear();
  ss.str(query_info[QUERY_KEY_PLAYBACK_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(LLONG_MAX, remaining_time);
  EXPECT_EQ(kRenewalServerUrl, query_info[QUERY_KEY_RENEWAL_SERVER_URL]);

  for (int i = 3; i <= 4; ++i) {
    policy_engine_->OnTimerEvent();
  }

  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));

  EXPECT_EQ(NO_ERROR, policy_engine_->Query(&query_info));
  EXPECT_EQ(QUERY_VALUE_STREAMING, query_info[QUERY_KEY_LICENSE_TYPE]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_PLAY_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_FALSE, query_info[QUERY_KEY_PERSIST_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_RENEW_ALLOWED]);

  ss.clear();
  ss.str(query_info[QUERY_KEY_LICENSE_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(0, remaining_time);
  ss.clear();
  ss.str(query_info[QUERY_KEY_PLAYBACK_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(LLONG_MAX, remaining_time);
  EXPECT_EQ(kRenewalServerUrl, query_info[QUERY_KEY_RENEWAL_SERVER_URL]);
}

TEST_F(PolicyEngineQueryTest, QuerySuccess_LicenseDuration0) {
  License_Policy* policy = license_.mutable_policy();
  policy->set_license_duration_seconds(kDurationUnlimited);
  policy->set_rental_duration_seconds(kStreamingLicenseDuration);
  policy->set_renewal_delay_seconds(GetLicenseRenewalDelay(kHighDuration));
  int64_t min_duration = GetMinOfRentalPlaybackLicenseDurations();

  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + 1))
      .WillOnce(Return(kLicenseStartTime + 5))
      .WillOnce(Return(kLicenseStartTime + min_duration - 1))
      .WillOnce(Return(kLicenseStartTime + min_duration))
      .WillOnce(Return(kLicenseStartTime + min_duration + 5));

  policy_engine_->SetLicense(license_);

  policy_engine_->BeginDecryption();
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));

  for (int i = 1; i <= 2; ++i) {
    policy_engine_->OnTimerEvent();
  }

  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));

  CdmQueryMap query_info;
  EXPECT_EQ(NO_ERROR, policy_engine_->Query(&query_info));
  EXPECT_EQ(QUERY_VALUE_STREAMING, query_info[QUERY_KEY_LICENSE_TYPE]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_PLAY_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_FALSE, query_info[QUERY_KEY_PERSIST_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_RENEW_ALLOWED]);

  int64_t remaining_time;
  std::istringstream ss;
  ss.str(query_info[QUERY_KEY_LICENSE_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(0, remaining_time);
  ss.clear();
  ss.str(query_info[QUERY_KEY_PLAYBACK_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(kPlaybackDuration - min_duration, remaining_time);
  EXPECT_EQ(kRenewalServerUrl, query_info[QUERY_KEY_RENEWAL_SERVER_URL]);
}

TEST_F(PolicyEngineQueryTest, QuerySuccess_Durations0) {
  License_Policy* policy = license_.mutable_policy();
  policy->set_rental_duration_seconds(kDurationUnlimited);
  policy->set_playback_duration_seconds(kDurationUnlimited);
  policy->set_license_duration_seconds(kDurationUnlimited);
  policy->set_renewal_delay_seconds(kHighDuration + 10);

  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + 1))
      .WillOnce(Return(kLicenseStartTime + 5))
      .WillOnce(Return(kLicenseStartTime + kHighDuration))
      .WillOnce(Return(kLicenseStartTime + kHighDuration + 9))
      .WillOnce(Return(kLicenseStartTime + kHighDuration + 15));

  policy_engine_->SetLicense(license_);

  policy_engine_->BeginDecryption();
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));

  policy_engine_->OnTimerEvent();
  policy_engine_->OnTimerEvent();

  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));

  CdmQueryMap query_info;
  EXPECT_EQ(NO_ERROR, policy_engine_->Query(&query_info));
  EXPECT_EQ(QUERY_VALUE_STREAMING, query_info[QUERY_KEY_LICENSE_TYPE]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_PLAY_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_FALSE, query_info[QUERY_KEY_PERSIST_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_RENEW_ALLOWED]);

  int64_t remaining_time;
  std::istringstream ss;
  ss.str(query_info[QUERY_KEY_LICENSE_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(LLONG_MAX, remaining_time);
  ss.clear();
  ss.str(query_info[QUERY_KEY_PLAYBACK_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(LLONG_MAX, remaining_time);
  EXPECT_EQ(kRenewalServerUrl, query_info[QUERY_KEY_RENEWAL_SERVER_URL]);
}

TEST_F(PolicyEngineQueryTest, QuerySuccess_LicenseWithFutureStartTime) {
  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime - 100))
      .WillOnce(Return(kLicenseStartTime - 50))
      .WillOnce(Return(kLicenseStartTime - 10))
      .WillOnce(Return(kLicenseStartTime))
      .WillOnce(Return(kLicenseStartTime + 10))
      .WillOnce(Return(kLicenseStartTime + 25));

  policy_engine_->SetLicense(license_);

  policy_engine_->OnTimerEvent();
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId));

  CdmQueryMap query_info;
  EXPECT_EQ(NO_ERROR, policy_engine_->Query(&query_info));
  EXPECT_EQ(QUERY_VALUE_STREAMING, query_info[QUERY_KEY_LICENSE_TYPE]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_PLAY_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_FALSE, query_info[QUERY_KEY_PERSIST_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_RENEW_ALLOWED]);

  int64_t remaining_time;
  std::istringstream ss;
  ss.str(query_info[QUERY_KEY_LICENSE_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(kStreamingLicenseDuration, remaining_time);
  ss.clear();
  ss.str(query_info[QUERY_KEY_PLAYBACK_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(kPlaybackDuration, remaining_time);
  EXPECT_EQ(kRenewalServerUrl, query_info[QUERY_KEY_RENEWAL_SERVER_URL]);

  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId));

  policy_engine_->OnTimerEvent();
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));
  policy_engine_->BeginDecryption();

  EXPECT_EQ(NO_ERROR, policy_engine_->Query(&query_info));
  EXPECT_EQ(QUERY_VALUE_STREAMING, query_info[QUERY_KEY_LICENSE_TYPE]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_PLAY_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_FALSE, query_info[QUERY_KEY_PERSIST_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_RENEW_ALLOWED]);

  ss.clear();
  ss.str(query_info[QUERY_KEY_LICENSE_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(kStreamingLicenseDuration - 25, remaining_time);
  ss.clear();
  ss.str(query_info[QUERY_KEY_PLAYBACK_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(kPlaybackDuration - 15, remaining_time);
  EXPECT_EQ(kRenewalServerUrl, query_info[QUERY_KEY_RENEWAL_SERVER_URL]);
}

TEST_F(PolicyEngineQueryTest, QuerySuccess_Renew) {
  int64_t license_renewal_delay =
      GetLicenseRenewalDelay(kStreamingLicenseDuration);

  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + 1))
      .WillOnce(Return(kLicenseStartTime + 5))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay - 25))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay + 10))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay + 20))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay +
                       kLicenseRenewalRetryInterval + 10))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay +
                       kLicenseRenewalRetryInterval + 15));

  policy_engine_->SetLicense(license_);

  policy_engine_->BeginDecryption();
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));

  for (int i = 1; i <= 2; ++i) {
    policy_engine_->OnTimerEvent();
  }

  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));

  license_.set_license_start_time(kLicenseStartTime + license_renewal_delay +
                                  15);
  LicenseIdentification* id = license_.mutable_id();
  id->set_version(2);
  policy_engine_->UpdateLicense(license_);

  policy_engine_->OnTimerEvent();
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));

  CdmQueryMap query_info;
  EXPECT_EQ(NO_ERROR, policy_engine_->Query(&query_info));
  EXPECT_EQ(QUERY_VALUE_STREAMING, query_info[QUERY_KEY_LICENSE_TYPE]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_PLAY_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_FALSE, query_info[QUERY_KEY_PERSIST_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_RENEW_ALLOWED]);

  int64_t remaining_time;
  std::istringstream ss;
  ss.str(query_info[QUERY_KEY_LICENSE_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(kStreamingLicenseDuration - kLicenseRenewalRetryInterval,
            remaining_time);
  ss.clear();
  ss.str(query_info[QUERY_KEY_PLAYBACK_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(kPlaybackDuration + 5 - license_renewal_delay -
                kLicenseRenewalRetryInterval - 15,
            remaining_time);
  EXPECT_EQ(kRenewalServerUrl, query_info[QUERY_KEY_RENEWAL_SERVER_URL]);
}

TEST_F(PolicyEngineQueryTest, QuerySuccess_RenewWithFutureStartTime) {
  int64_t license_renewal_delay =
      GetLicenseRenewalDelay(kStreamingLicenseDuration);

  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + 1))
      .WillOnce(Return(kLicenseStartTime + 5))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay - 25))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay + 10))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay + 20))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay +
                       kLicenseRenewalRetryInterval + 10))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay +
                       kLicenseRenewalRetryInterval + 20))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay +
                       kLicenseRenewalRetryInterval + 30))
      .WillOnce(Return(kLicenseStartTime + license_renewal_delay +
                       kLicenseRenewalRetryInterval + 40));

  policy_engine_->SetLicense(license_);

  policy_engine_->BeginDecryption();
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));

  for (int i = 1; i <= 2; ++i) {
    policy_engine_->OnTimerEvent();
  }

  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));

  license_.set_license_start_time(kLicenseStartTime + license_renewal_delay +
                                  kLicenseRenewalRetryInterval + 20);
  LicenseIdentification* id = license_.mutable_id();
  id->set_version(2);
  policy_engine_->UpdateLicense(license_);

  policy_engine_->OnTimerEvent();
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId));

  CdmQueryMap query_info;
  EXPECT_EQ(NO_ERROR, policy_engine_->Query(&query_info));
  EXPECT_EQ(QUERY_VALUE_STREAMING, query_info[QUERY_KEY_LICENSE_TYPE]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_PLAY_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_FALSE, query_info[QUERY_KEY_PERSIST_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_RENEW_ALLOWED]);

  int64_t remaining_time;
  std::istringstream ss;
  ss.str(query_info[QUERY_KEY_LICENSE_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(kStreamingLicenseDuration, remaining_time);
  ss.clear();
  ss.str(query_info[QUERY_KEY_PLAYBACK_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(kPlaybackDuration + 5 - license_renewal_delay -
                kLicenseRenewalRetryInterval - 20,
            remaining_time);
  EXPECT_EQ(kRenewalServerUrl, query_info[QUERY_KEY_RENEWAL_SERVER_URL]);

  policy_engine_->OnTimerEvent();
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));

  EXPECT_EQ(NO_ERROR, policy_engine_->Query(&query_info));
  EXPECT_EQ(QUERY_VALUE_STREAMING, query_info[QUERY_KEY_LICENSE_TYPE]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_PLAY_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_FALSE, query_info[QUERY_KEY_PERSIST_ALLOWED]);
  EXPECT_EQ(QUERY_VALUE_TRUE, query_info[QUERY_KEY_RENEW_ALLOWED]);

  ss.clear();
  ss.str(query_info[QUERY_KEY_LICENSE_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(kStreamingLicenseDuration - 20, remaining_time);
  ss.clear();
  ss.str(query_info[QUERY_KEY_PLAYBACK_DURATION_REMAINING]);
  ss >> remaining_time;
  EXPECT_EQ(kPlaybackDuration + 5 - license_renewal_delay -
                kLicenseRenewalRetryInterval - 40,
            remaining_time);
  EXPECT_EQ(kRenewalServerUrl, query_info[QUERY_KEY_RENEWAL_SERVER_URL]);
}

TEST_F(PolicyEngineTest, SetLicenseForRelease) {
  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + 1));

  // No key change event will fire.
  EXPECT_CALL(mock_event_listener_,
              OnExpirationUpdate(_, kLicenseStartTime + kLowDuration));
  policy_engine_->SetLicenseForRelease(license_);
  // No keys were loaded.
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId));
}

TEST_F(PolicyEngineTest, SetLicenseForReleaseAfterSetLicense) {
  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(kLicenseStartTime + 1))
      .WillOnce(Return(kPlaybackStartTime))
      .WillOnce(Return(kLicenseStartTime + 10));

  ExpectSessionKeysChange(kKeyStatusUsable, true);
  EXPECT_CALL(mock_event_listener_,
              OnExpirationUpdate(_, kLicenseStartTime + kLowDuration));
  EXPECT_CALL(mock_event_listener_,
              OnExpirationUpdate(_, kPlaybackStartTime + kPlaybackDuration));

  policy_engine_->SetLicense(license_);
  policy_engine_->BeginDecryption();
  policy_engine_->OnTimerEvent();
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId));
  ::testing::Mock::VerifyAndClear(&mock_event_listener_);

  // Set the license again with use_keys set to false.
  // This would happen when asking the session to generate a release message
  // on an existing session.
  ExpectSessionKeysChange(kKeyStatusExpired, false);
  policy_engine_->SetLicenseForRelease(license_);
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId));
}

}  // namespace wvcdm
