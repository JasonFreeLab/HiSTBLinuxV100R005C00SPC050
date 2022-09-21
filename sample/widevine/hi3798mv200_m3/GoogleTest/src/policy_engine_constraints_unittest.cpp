// Copyright 2016 Google Inc. All Rights Reserved.

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "crypto_session.h"
#include "license.h"
#include "policy_engine.h"
#include "mock_clock.h"
#include "scoped_ptr.h"
#include "wv_cdm_event_listener.h"
#include "wv_cdm_types.h"

// protobuf generated classes.
using video_widevine_server::sdk::License;
using video_widevine_server::sdk::License_Policy;
using video_widevine_server::sdk::STREAMING;

namespace wvcdm {

typedef ::video_widevine_server::sdk::License License;
typedef ::video_widevine_server::sdk::License::KeyContainer KeyContainer;
typedef ::video_widevine_server::sdk::License::KeyContainer::OutputProtection
    OutputProtection;
typedef ::video_widevine_server::sdk::License::KeyContainer::
    VideoResolutionConstraint VideoResolutionConstraint;
typedef ::google::protobuf::RepeatedPtrField<KeyContainer> KeyList;
typedef ::google::protobuf::RepeatedPtrField<VideoResolutionConstraint>
    ConstraintList;

using namespace testing;

namespace {

const CdmSessionId kSessionId = "mock_session_id";

const KeyId kKeyId1 = "1111kKeyId1";
const KeyId kKeyId2 = "2222kKeyId2";
const KeyId kKeyId3 = "3333kKeyId3";
const KeyId kKeyId4 = "4444kKeyId4";
const KeyId kKeyId5 = "5555kKeyId5";
const KeyId kKeyId6 = "6666kKeyId6";

const uint32_t kMinRes1 = 0;
const uint32_t kMaxRes1 = 2000;
const uint32_t kMinRes2 = kMaxRes1;
const uint32_t kMaxRes2 = 4000;
const uint32_t kTargetRes1 = (kMinRes1 + kMaxRes1) / 2;
const uint32_t kTargetRes2 = (kMinRes2 + kMaxRes2) / 2;
const uint32_t kTargetRes3 = kMaxRes2 + 1000;

const int64_t kRentalDuration = 604800;         // 7 days
const int64_t kPlaybackDuration = 172800;       // 48 hours
const int64_t kStreamingLicenseDuration = 300;

const OutputProtection::HDCP kHdcpV2 = OutputProtection::HDCP_V2;
const OutputProtection::HDCP kHdcpV2_1 = OutputProtection::HDCP_V2_1;

// should match kHdcpCheckInterval in policy_engine.cpp
const int64_t kHdcpInterval = 10;

class HdcpOnlyMockCryptoSession : public CryptoSession {
 public:
  MOCK_METHOD2(GetHdcpCapabilities, bool(HdcpCapability*, HdcpCapability*));
};

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

class PolicyEngineConstraintsTest : public Test {
 protected:
  virtual void SetUp() {
    mock_clock_ = new NiceMock<MockClock>();
    current_time_ = 0;

    policy_engine_.reset(new PolicyEngine(kSessionId, &mock_event_listener_,
                                          &crypto_session_));
    InjectMockClock();

    SetupLicense();
  }

  void AddConstraints(ConstraintList* constraints) {
    // Constraint 1 - Low-res and no HDCP
    {
      VideoResolutionConstraint* c_lo_res_no_hdcp = constraints->Add();
      c_lo_res_no_hdcp->set_min_resolution_pixels(kMinRes1);
      c_lo_res_no_hdcp->set_max_resolution_pixels(kMaxRes1);
    }

    // Constraint 2 - High-res and stricter HDCP
    {
      VideoResolutionConstraint* c_hi_res_hdcp_v2 = constraints->Add();
      c_hi_res_hdcp_v2->set_min_resolution_pixels(kMinRes2);
      c_hi_res_hdcp_v2->set_max_resolution_pixels(kMaxRes2);
      c_hi_res_hdcp_v2->mutable_required_protection()->set_hdcp(kHdcpV2_1);
    }
  }

  void SetupLicense() {
    license_.set_license_start_time(current_time_);

    LicenseIdentification* id = license_.mutable_id();
    id->set_version(1);
    id->set_type(STREAMING);

    License_Policy* policy = license_.mutable_policy();
    policy = license_.mutable_policy();
    policy->set_can_play(true);
    policy->set_can_persist(false);
    policy->set_rental_duration_seconds(kRentalDuration);
    policy->set_playback_duration_seconds(kPlaybackDuration);
    policy->set_license_duration_seconds(kStreamingLicenseDuration);

    KeyList* keys = license_.mutable_key();

    // Key 1 - Content key w/ ID, no HDCP, no constraints
    {
      KeyContainer* key1 = keys->Add();
      key1->set_type(KeyContainer::CONTENT);
      key1->set_id(kKeyId1);
    }

    // Key 2 - Content key w/ ID, HDCP, no constraints
    {
      KeyContainer* key2 = keys->Add();
      key2->set_type(KeyContainer::CONTENT);
      key2->set_id(kKeyId2);
      key2->mutable_required_protection()->set_hdcp(kHdcpV2);
    }

    // Key 3 - Content key w/ ID, no HDCP, constraints
    {
      KeyContainer* key3 = keys->Add();
      key3->set_type(KeyContainer::CONTENT);
      key3->set_id(kKeyId3);
      AddConstraints(key3->mutable_video_resolution_constraints());
    }

    // Key 4 - Content key w/ ID, HDCP, constraints
    {
      KeyContainer* key4 = keys->Add();
      key4->set_type(KeyContainer::CONTENT);
      key4->set_id(kKeyId4);
      key4->mutable_required_protection()->set_hdcp(kHdcpV2);
      AddConstraints(key4->mutable_video_resolution_constraints());
    }

    // Key 5 - Content key w/o ID, HDCP, constraints
    {
      KeyContainer* key5 = keys->Add();
      key5->set_type(KeyContainer::CONTENT);
      key5->mutable_required_protection()->set_hdcp(kHdcpV2);
      AddConstraints(key5->mutable_video_resolution_constraints());
    }

    // Key 6 - Non-content key
    {
      KeyContainer* key6 = keys->Add();
      key6->set_type(KeyContainer::OPERATOR_SESSION);
    }
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
                                   Pair(kKeyId1, expected_key_status),
                                   Pair(kKeyId2, expected_key_status),
                                   Pair(kKeyId3, expected_key_status),
                                   Pair(kKeyId4, expected_key_status)),
                    expected_has_new_usable_key));
  }

  void ExpectSessionKeysChanges(const KeyId& k1, CdmKeyStatus expected_1,
                                const KeyId& k2, CdmKeyStatus expected_2,
                                const KeyId& k3, CdmKeyStatus expected_3,
                                const KeyId& k4, CdmKeyStatus expected_4,
                                bool expected_has_new_usable_key) {
    EXPECT_CALL(mock_event_listener_,
                OnSessionKeysChange(
                    kSessionId, UnorderedElementsAre(
                                   Pair(k1, expected_1),
                                   Pair(k2, expected_2),
                                   Pair(k3, expected_3),
                                   Pair(k4, expected_4)),
                    expected_has_new_usable_key));
  }

  scoped_ptr<PolicyEngine> policy_engine_;
  MockClock* mock_clock_;
  int64_t current_time_;
  StrictMock<HdcpOnlyMockCryptoSession> crypto_session_;
  StrictMock<MockCdmEventListener> mock_event_listener_;
  License license_;
};

TEST_F(PolicyEngineConstraintsTest, IsPermissiveWithoutAResolution) {
  EXPECT_CALL(*mock_clock_, GetCurrentTime()).Times(2);
  EXPECT_CALL(mock_event_listener_, OnExpirationUpdate(kSessionId, _));
  ExpectSessionKeysChange(kKeyStatusUsable, true);

  policy_engine_->SetLicense(license_);
  policy_engine_->OnTimerEvent();

  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId1));
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId2));
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId3));
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId4));
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId5));
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId6));
}

TEST_F(PolicyEngineConstraintsTest, HandlesResolutionsBasedOnConstraints) {
  {
    Sequence time;
    for (int i=0; i<4; ++i) {
      EXPECT_CALL(*mock_clock_, GetCurrentTime()).InSequence(time)
          .WillOnce(Return(i * 10));
    }
  }
  {
    Sequence key_change;
    ExpectSessionKeysChange(kKeyStatusUsable, true);
    ExpectSessionKeysChanges(kKeyId1, kKeyStatusUsable,
                             kKeyId2, kKeyStatusUsable,
                             kKeyId3, kKeyStatusOutputNotAllowed,
                             kKeyId4, kKeyStatusOutputNotAllowed, false);
  }
  EXPECT_CALL(mock_event_listener_, OnExpirationUpdate(kSessionId, _));
  EXPECT_CALL(crypto_session_, GetHdcpCapabilities(_, _))
      .WillRepeatedly(
          DoAll(SetArgPointee<0>(HDCP_NO_DIGITAL_OUTPUT),
                Return(true)));


  policy_engine_->SetLicense(license_);
  policy_engine_->NotifyResolution(1, kTargetRes1);
  policy_engine_->OnTimerEvent();
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId1));
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId2));
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId3));
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId4));
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId5));
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId6));

  policy_engine_->NotifyResolution(1, kTargetRes2);
  policy_engine_->OnTimerEvent();
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId1));
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId2));
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId3));
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId4));
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId5));
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId6));

  policy_engine_->NotifyResolution(1, kTargetRes3);
  policy_engine_->OnTimerEvent();
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId1));
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId2));
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId3));
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId4));
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId5));
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId6));
}

TEST_F(PolicyEngineConstraintsTest,
       RequestsHdcpImmediatelyAndOnlyAfterInterval) {
  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(0))
      .WillOnce(Return(5));
  EXPECT_CALL(mock_event_listener_, OnExpirationUpdate(kSessionId, _));
  ExpectSessionKeysChange(kKeyStatusUsable, true);

  int64_t start_time = current_time_ + 5;
  {
    InSequence calls;
    EXPECT_CALL(crypto_session_, GetHdcpCapabilities(_, _))
        .WillOnce(
            DoAll(SetArgPointee<0>(HDCP_V2_2),
                  Return(true)));
    EXPECT_CALL(*mock_clock_, GetCurrentTime())
        .WillOnce(Return(start_time + kHdcpInterval / 2))
        .WillOnce(Return(start_time + kHdcpInterval));
    EXPECT_CALL(crypto_session_, GetHdcpCapabilities(_, _))
        .WillOnce(
            DoAll(SetArgPointee<0>(HDCP_V2_2),
                  Return(true)));
  }

  policy_engine_->NotifyResolution(1, kTargetRes1);
  policy_engine_->SetLicense(license_);
  policy_engine_->OnTimerEvent();
  policy_engine_->OnTimerEvent();
  policy_engine_->OnTimerEvent();
}

TEST_F(PolicyEngineConstraintsTest, DoesNotRequestHdcpWithoutALicense) {
  EXPECT_CALL(*mock_clock_, GetCurrentTime())
      .WillOnce(Return(0));
  EXPECT_CALL(crypto_session_, GetHdcpCapabilities(_, _)).Times(0);

  policy_engine_->OnTimerEvent();
}

TEST_F(PolicyEngineConstraintsTest, HandlesConstraintOverridingHdcp) {
  {
    Sequence time;
    for (int i=0; i<3; ++i) {
      EXPECT_CALL(*mock_clock_, GetCurrentTime()).InSequence(time)
          .WillOnce(Return(i * 10));
    }
  }
  {
    Sequence key_change;
    ExpectSessionKeysChange(kKeyStatusUsable, true);
    ExpectSessionKeysChanges(kKeyId1, kKeyStatusUsable,
                             kKeyId2, kKeyStatusUsable,
                             kKeyId3, kKeyStatusOutputNotAllowed,
                             kKeyId4, kKeyStatusOutputNotAllowed, false);
  }
  EXPECT_CALL(mock_event_listener_, OnExpirationUpdate(kSessionId, _));
  EXPECT_CALL(crypto_session_, GetHdcpCapabilities(_, _))
      .WillRepeatedly(
          DoAll(SetArgPointee<0>(HDCP_V2),
                Return(true)));

  policy_engine_->SetLicense(license_);
  policy_engine_->NotifyResolution(1, kTargetRes1);
  policy_engine_->OnTimerEvent();
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId1));
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId2));
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId3));
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId4));
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId5));
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId6));

  policy_engine_->NotifyResolution(1, kTargetRes2);
  policy_engine_->OnTimerEvent();
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId1));
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId2));
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId3));
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId4));
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId5));
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId6));
}

TEST_F(PolicyEngineConstraintsTest, HandlesNoHdcp) {
  {
    Sequence time;
    for (int i=0; i<3; ++i) {
      EXPECT_CALL(*mock_clock_, GetCurrentTime()).InSequence(time)
          .WillOnce(Return(i * 10));
    }
  }
  {
    Sequence key_change;
    ExpectSessionKeysChanges(kKeyId1, kKeyStatusUsable,
                             kKeyId2, kKeyStatusOutputNotAllowed,
                             kKeyId3, kKeyStatusUsable,
                             kKeyId4, kKeyStatusOutputNotAllowed, false);
    ExpectSessionKeysChanges(kKeyId1, kKeyStatusUsable,
                             kKeyId2, kKeyStatusOutputNotAllowed,
                             kKeyId3, kKeyStatusOutputNotAllowed,
                             kKeyId4, kKeyStatusOutputNotAllowed, false);
  }
  EXPECT_CALL(mock_event_listener_, OnExpirationUpdate(kSessionId, _));
  ExpectSessionKeysChange(kKeyStatusUsable, true);
  EXPECT_CALL(crypto_session_, GetHdcpCapabilities(_, _))
      .WillRepeatedly(
          DoAll(SetArgPointee<0>(HDCP_NONE),
                Return(true)));

  policy_engine_->SetLicense(license_);

  policy_engine_->NotifyResolution(1, kTargetRes1);
  policy_engine_->OnTimerEvent();
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId1));
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId2));
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId3));
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId4));
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId5));
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId6));

  policy_engine_->NotifyResolution(1, kTargetRes2);
  policy_engine_->OnTimerEvent();
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId1));
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId2));
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId3));
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId4));
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId5));
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId6));
}

TEST_F(PolicyEngineConstraintsTest, IgnoresHdcpWithoutAResolution) {
  {
    Sequence time;
    for (int i=0; i<2; ++i) {
      EXPECT_CALL(*mock_clock_, GetCurrentTime()).InSequence(time)
          .WillOnce(Return(i * 10));
    }
  }
  ExpectSessionKeysChange(kKeyStatusUsable, true);
  EXPECT_CALL(mock_event_listener_, OnExpirationUpdate(kSessionId, _));
  EXPECT_CALL(crypto_session_, GetHdcpCapabilities(_, _)).Times(0);

  policy_engine_->SetLicense(license_);
  policy_engine_->OnTimerEvent();
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId1));
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId2));
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId3));
  EXPECT_TRUE(policy_engine_->CanDecrypt(kKeyId4));
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId5));
  EXPECT_FALSE(policy_engine_->CanDecrypt(kKeyId6));
}

}  // namespace wvcdm
