// Copyright 2015 Google Inc. All Rights Reserved.

#include <arpa/inet.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "initialization_data.h"
#include "license_protocol.pb.h"
#include "string_conversions.h"
#include "wv_cdm_constants.h"

// References:
//  [1] http://dashif.org/identifiers/content-protection/
//  [2] http://www.w3.org/TR/encrypted-media/cenc-format.html#common-system
//  [3] https://tools.ietf.org/html/draft-pantos-http-live-streaming-18

namespace wvcdm {

// Protobuf generated classes.
using video_widevine_server::sdk::WidevineCencHeader;

namespace {

// Constants for JSON formatting
const std::string kLeftBrace = "{";
const std::string kRightBrace = "}";
const std::string kLeftBracket = "[";
const std::string kRightBracket = "]";
const std::string kComma = ",";
const std::string kColon = ":";
const std::string kDoubleQuote = "\"";
const std::string kNewline = "\n";
const std::string kFourSpaceIndent = "    ";

const std::string kJsonProvider = "provider";
const std::string kJsonContentId = "content_id";
const std::string kJsonKeyIds = "key_ids";

const uint32_t kFourCcCbc1 = 0x63626331;
const uint32_t kFourCcCbcs = 0x63626373;

const std::string kWidevinePssh = a2bs_hex(
    // Widevine PSSH box
    "00000042"                          // atom size
    "70737368"                          // atom type="pssh"
    "00000000"                          // v0, flags=0
    "edef8ba979d64acea3c827dcd51d21ed"  // system id (Widevine)
    "00000022"                          // data size
    // data:
    "08011a0d7769646576696e655f74657374220f73747265616d696e675f636c697031");

const std::string kWidevinePsshFirst = a2bs_hex(
    // first PSSH box, Widevine
    "00000042"                          // atom size
    "70737368"                          // atom type "pssh"
    "00000000"                          // v0, flags=0
    "edef8ba979d64acea3c827dcd51d21ed"  // system id (Widevine)
    "00000022"                          // data size
    // data:
    "08011a0d7769646576696e655f74657374220f73747265616d696e675f636c697031"

    // second PSSH box, Playready [1]
    "00000028"                          // atom size
    "70737368"                          // atom type "pssh"
    "00000000"                          // v0, flags=0
    "9a04f07998404286ab92e65be0885f95"  // system id (PlayReady)
    "00000008"                          // data size
    // arbitrary data:
    "0102030405060708");

const std::string kWidevinePsshAfterV0Pssh = a2bs_hex(
    // first PSSH box, Playready [1]
    "00000028"                          // atom size
    "70737368"                          // atom type "pssh"
    "00000000"                          // v0, flags=0
    "9a04f07998404286ab92e65be0885f95"  // system id (PlayReady)
    "00000008"                          // data size
    // arbitrary data:
    "0102030405060708"

    // second PSSH box, Widevine
    "00000042"                          // atom size
    "70737368"                          // atom type "pssh"
    "00000000"                          // v0, flags=0
    "edef8ba979d64acea3c827dcd51d21ed"  // system id (Widevine)
    "00000022"                          // data size
    // data:
    "08011a0d7769646576696e655f74657374220f73747265616d696e675f636c697031");

const std::string kWidevinePsshAfterNonZeroFlags = a2bs_hex(
    // first PSSH box, Playready [1]
    "00000028"                          // atom size
    "70737368"                          // atom type "pssh"
    "00abcdef"                          // v0, flags=abcdef
    "9a04f07998404286ab92e65be0885f95"  // system id (PlayReady)
    "00000008"                          // data size
    // arbitrary data:
    "0102030405060708"

    // second PSSH box, Widevine
    "00000042"                          // atom size
    "70737368"                          // atom type "pssh"
    "00000000"                          // v0, flags=0
    "edef8ba979d64acea3c827dcd51d21ed"  // system id (Widevine)
    "00000022"                          // data size
    // data:
    "08011a0d7769646576696e655f74657374220f73747265616d696e675f636c697031");

const std::string kWidevinePsshAfterV1Pssh = a2bs_hex(
    // first PSSH box, generic CENC [2]
    "00000044"                          // atom size
    "70737368"                          // atom type "pssh"
    "01000000"                          // v1, flags=0
    "1077efecc0b24d02ace33c1e52e2fb4b"  // system id (generic CENC)
    "00000002"                          // key ID count
    "30313233343536373839303132333435"  // key ID="0123456789012345"
    "38393031323334354142434445464748"  // key ID="ABCDEFGHIJKLMNOP"
    "00000000"                          // data size=0

    // second PSSH box, Widevine
    "00000042"                          // atom size
    "70737368"                          // atom type "pssh"
    "00000000"                          // v0, flags=0
    "edef8ba979d64acea3c827dcd51d21ed"  // system id (Widevine)
    "00000022"                          // data size
    // data:
    "08011a0d7769646576696e655f74657374220f73747265616d696e675f636c697031");

const std::string kWidevineV1Pssh = a2bs_hex(
    // Widevine PSSH box, v1 format
    "00000044"                          // atom size
    "70737368"                          // atom type "pssh"
    "01000000"                          // v1, flags=0
    "edef8ba979d64acea3c827dcd51d21ed"  // system id (Widevine)
    "00000002"                          // key ID count
    "30313233343536373839303132333435"  // key ID="0123456789012345"
    "38393031323334354142434445464748"  // key ID="ABCDEFGHIJKLMNOP"
    "00000022"                          // data size
    // data:
    "08011a0d7769646576696e655f74657374220f73747265616d696e675f636c697031");

const std::string kOtherBoxFirst = a2bs_hex(
    // first box, not a PSSH box
    "00000018"                          // atom size
    "77686174"                          // atom type "what"
    "deadbeefdeadbeefdeadbeefdeadbeef"  // garbage box data

    // second box, a Widevine PSSH box
    "00000042"                          // atom size
    "70737368"                          // atom type "pssh"
    "00000000"                          // v0, flags=0
    "edef8ba979d64acea3c827dcd51d21ed"  // system id (Widevine)
    "00000022"                          // data size
    // data:
    "08011a0d7769646576696e655f74657374220f73747265616d696e675f636c697031");

const std::string kZeroSizedPsshBox = a2bs_hex(
    // Widevine PSSH box
    "00000000"                          // atom size (whole buffer)
    "70737368"                          // atom type="pssh"
    "00000000"                          // v0, flags=0
    "edef8ba979d64acea3c827dcd51d21ed"  // system id (Widevine)
    "00000022"                          // data size
    // data:
    "08011a0d7769646576696e655f74657374220f73747265616d696e675f636c697031");

// HLS test attribute key and values
const std::string kHlsIvHexValue = "6DF49213A781E338628D0E9C812D328E";
const std::string kHlsIvValue = "0x" + kHlsIvHexValue;
const std::string kHlsKeyFormatValue = "com.widevine.alpha";
const std::string kHlsKeyFormatValueOther = "com.example";
const std::string kHlsTestKey1 = "TESTKEY1";
const std::string kHlsTestValue1 = "testvalue1";
const std::string kHlsTestKey2 = "TESTKEY2";
const std::string kHlsTestValue2 = "testvalue2";
const std::string kHlsTestInvalidLowercaseKey = "testkey3";
const std::string kHlsTestKeyWithDash = "TEST-KEY4";
const std::string kHlsTestInvalidNonAlphanumKey = "TEST;KEY4";
const std::string kHlsTestValueWithEmbeddedQuote = "test\"value1";
const std::string kHlsTestEmptyHexValue = "";
const std::string kHlsTestNoHexValue = "0x";
const std::string kHlsTestHexValueWithOddBytes = kHlsIvHexValue + "7";
const std::string kHlsTestInvalidHexValue = kHlsIvHexValue + "g7";
char kHlsTestKeyFormatVersionsSeparator = '/';
const std::string kHlsTestUriDataFormat = "data:text/plain;base64,";
const std::string kHlsTestProvider = "youtube";
const std::string kHlsTestContentId = "MjAxNV9UZWFycw==";
const std::string kHlsTestKeyId1 = "371E135E1A985D75D198A7F41020DC23";
const std::string kHlsTestKeyId2 = "E670D9B60AE61583E01BC9253FA19261";
const std::string kHlsTestKeyId3 = "78094E72165DF39721B8A354D6A71390";
const std::string kHlsTestInvalidKeyId = "B8A354D6A71390";
const std::string kHlsTestKeyFormatVersion1 = "1";
const std::string kHlsTestKeyFormatVersion3 = "3";
const std::string kHlsTestKeyFormatVersion5 = "5";
const std::string kHlsTestKeyFormatVersion13 = "13";
const std::string kHlsTestKeyFormatVersion21 = "21";
const std::string kHlsTestKeyFormatVersion37 = "37";

// HLS attribute helper functions
std::string QuoteString(const std::string& value) {
  return "\"" + value + "\"";
}

std::string GenerateJsonInitData(const std::string& provider,
                                 const std::string& content_id,
                                 const std::vector<std::string>& key_ids) {
  std::string json = kLeftBrace + kNewline;
  if (provider.size() > 0) {
    json += kFourSpaceIndent + kDoubleQuote + kJsonProvider + kDoubleQuote +
            kColon + kDoubleQuote + provider + kDoubleQuote + kComma + kNewline;
  }
  if (content_id.size() > 0) {
    json += kFourSpaceIndent + kDoubleQuote + kJsonContentId + kDoubleQuote +
            kColon + kDoubleQuote + content_id + kDoubleQuote + kComma +
            kNewline;
  }
  if (key_ids.size() > 0) {
    json += kFourSpaceIndent + kDoubleQuote + kJsonKeyIds + kDoubleQuote +
            kColon + kNewline;
    json += kFourSpaceIndent + kLeftBracket + kNewline;
    for (size_t i = 0; i < key_ids.size(); ++i) {
      json += kFourSpaceIndent + kFourSpaceIndent + kDoubleQuote + key_ids[i] +
              kDoubleQuote;
      if (i != key_ids.size() - 1) {
        json += kComma;
      }
      json += kNewline;
    }
    json += kFourSpaceIndent + kRightBracket + kNewline;
  }
  json += kRightBrace + kNewline;
  return json;
}

class VectorOfStrings {
 public:
  VectorOfStrings(const std::string& str) { vec_.push_back(str); }
  VectorOfStrings& Add(const std::string& str) {
    vec_.push_back(str);
    return *this;
  }
  const std::vector<std::string> Generate() { return vec_; }

 private:
  std::vector<std::string> vec_;
};

std::string GenerateHlsUriData(const std::string& provider,
                               const std::string& content_id,
                               const std::vector<std::string>& key_ids) {
  std::string json = GenerateJsonInitData(provider, content_id, key_ids);
  std::vector<uint8_t> json_init_data(
      reinterpret_cast<const uint8_t*>(json.data()),
      reinterpret_cast<const uint8_t*>(json.data() + json.size()));
  return kHlsTestUriDataFormat + Base64Encode(json_init_data);
}

std::string CreateHlsAttributeList(const std::string& method,
                                   const std::string& provider,
                                   const std::string& content_id,
                                   const std::vector<std::string>& key_ids,
                                   const std::string& iv,
                                   const std::string& key_format,
                                   const std::string& key_format_version) {
  return "EXT-X-KEY: " + HLS_METHOD_ATTRIBUTE + "=" + method + "," +
         HLS_URI_ATTRIBUTE + "=" +
         QuoteString(GenerateHlsUriData(provider, content_id, key_ids)) + "," +
         HLS_IV_ATTRIBUTE + "=" + iv + "," + HLS_KEYFORMAT_ATTRIBUTE + "=" +
         QuoteString(key_format) + "," + HLS_KEYFORMAT_VERSIONS_ATTRIBUTE +
         "=" + QuoteString(key_format_version);
}

// HLS attribute list for testing
const std::string kHlsAttributeList = CreateHlsAttributeList(
    HLS_METHOD_SAMPLE_AES, kHlsTestProvider, kHlsTestContentId,
    VectorOfStrings(kHlsTestKeyId1).Generate(), kHlsIvValue, kHlsKeyFormatValue,
    HLS_KEYFORMAT_VERSION_VALUE_1);

const std::string kHlsAttributeListKeyFormatUnknown = CreateHlsAttributeList(
    HLS_METHOD_SAMPLE_AES, kHlsTestProvider, kHlsTestContentId,
    VectorOfStrings(kHlsTestKeyId1).Generate(), kHlsIvValue,
    kHlsKeyFormatValueOther, HLS_KEYFORMAT_VERSION_VALUE_1);

const std::string kHlsAttributeListKeyFormatVersionUnsupported =
    CreateHlsAttributeList(HLS_METHOD_SAMPLE_AES, kHlsTestProvider,
                           kHlsTestContentId,
                           VectorOfStrings(kHlsTestKeyId1).Generate(),
                           kHlsIvValue, kHlsKeyFormatValue, "2");

const std::string kHlsAttributeListKeyFormatVersionMultiple =
    CreateHlsAttributeList(HLS_METHOD_SAMPLE_AES, kHlsTestProvider,
                           kHlsTestContentId,
                           VectorOfStrings(kHlsTestKeyId1).Generate(),
                           kHlsIvValue, kHlsKeyFormatValue, "1/2/5");

const std::string kHlsAttributeListMethodAes128 = CreateHlsAttributeList(
    HLS_METHOD_AES_128, kHlsTestProvider, kHlsTestContentId,
    VectorOfStrings(kHlsTestKeyId1).Generate(), kHlsIvValue, kHlsKeyFormatValue,
    HLS_KEYFORMAT_VERSION_VALUE_1);

const std::string kHlsAttributeListMethodNone = CreateHlsAttributeList(
    HLS_METHOD_NONE, kHlsTestProvider, kHlsTestContentId,
    VectorOfStrings(kHlsTestKeyId1).Generate(), kHlsIvValue, kHlsKeyFormatValue,
    HLS_KEYFORMAT_VERSION_VALUE_1);

const std::string kHlsAttributeListMethodInvalid = CreateHlsAttributeList(
    kHlsTestValue1, kHlsTestProvider, kHlsTestContentId,
    VectorOfStrings(kHlsTestKeyId1).Generate(), kHlsIvValue, kHlsKeyFormatValue,
    HLS_KEYFORMAT_VERSION_VALUE_1);

const std::string kHlsAttributeListInvalidUriNoProvider =
    CreateHlsAttributeList(HLS_METHOD_SAMPLE_AES, "", kHlsTestContentId,
                           VectorOfStrings(kHlsTestKeyId1).Generate(),
                           kHlsIvValue, kHlsKeyFormatValue,
                           HLS_KEYFORMAT_VERSION_VALUE_1);

const std::string kHlsAttributeListInvalidUriNoContentId =
    CreateHlsAttributeList(HLS_METHOD_SAMPLE_AES, kHlsTestProvider, "",
                           VectorOfStrings(kHlsTestKeyId1).Generate(),
                           kHlsIvValue, kHlsKeyFormatValue,
                           HLS_KEYFORMAT_VERSION_VALUE_1);

const std::string kHlsAttributeListInvalidUriNoKeyId = CreateHlsAttributeList(
    HLS_METHOD_SAMPLE_AES, kHlsTestProvider, kHlsTestContentId,
    VectorOfStrings("").Generate(), kHlsIvValue, kHlsKeyFormatValue,
    HLS_KEYFORMAT_VERSION_VALUE_1);

const std::string kHlsAttributeListValidUriThreeKeyIds = CreateHlsAttributeList(
    HLS_METHOD_SAMPLE_AES, kHlsTestProvider, kHlsTestContentId,
    VectorOfStrings(kHlsTestKeyId1)
        .Add(kHlsTestKeyId2)
        .Add(kHlsTestKeyId3)
        .Generate(),
    kHlsIvValue, kHlsKeyFormatValue, HLS_KEYFORMAT_VERSION_VALUE_1);

const std::string kHlsAttributeListNoIv = CreateHlsAttributeList(
    HLS_METHOD_SAMPLE_AES, kHlsTestProvider, kHlsTestContentId,
    VectorOfStrings(kHlsTestKeyId1).Generate(), kHlsTestNoHexValue,
    kHlsKeyFormatValue, HLS_KEYFORMAT_VERSION_VALUE_1);

const std::string kHlsAttributeListInvalidIv = CreateHlsAttributeList(
    HLS_METHOD_SAMPLE_AES, kHlsTestProvider, kHlsTestContentId,
    VectorOfStrings(kHlsTestKeyId1).Generate(), kHlsTestHexValueWithOddBytes,
    kHlsKeyFormatValue, HLS_KEYFORMAT_VERSION_VALUE_1);

std::string InsertHlsAttributeInList(const std::string key,
                                     const std::string& value) {
  return kHlsAttributeList + "," + key + "=" + value + "," + kHlsTestKey2 +
         "=" + kHlsTestValue2;
}

struct HlsInitDataVariant {
  HlsInitDataVariant(CdmHlsMethod method, const std::string& provider,
                     const std::string& content_id, const std::string& key_id,
                     bool success)
      : method_(method), provider_(provider), content_id_(content_id),
        success_(success) {
    if (key_id.size() > 0) key_ids_.push_back(key_id);
  }
  HlsInitDataVariant& AddKeyId(const std::string& key_id) {
    key_ids_.push_back(key_id);
    return *this;
  }
  const CdmHlsMethod method_;
  const std::string provider_;
  const std::string content_id_;
  std::vector<std::string> key_ids_;
  const bool success_;
};

struct HlsAttributeVariant {
  HlsAttributeVariant(const std::string& attribute_list, const std::string& key,
                      const std::string& value, bool success)
      : attribute_list_(attribute_list),
        key_(key),
        value_(value),
        success_(success) {}
  const std::string attribute_list_;
  const std::string key_;
  const std::string value_;
  const bool success_;
};

class InitializationDataTest : public ::testing::TestWithParam<std::string> {};

class HlsAttributeExtractionTest
    : public ::testing::TestWithParam<HlsAttributeVariant> {};

class HlsHexAttributeExtractionTest
    : public ::testing::TestWithParam<HlsAttributeVariant> {};

class HlsQuotedAttributeExtractionTest
    : public ::testing::TestWithParam<HlsAttributeVariant> {};

class HlsKeyFormatVersionsExtractionTest
    : public ::testing::TestWithParam<std::vector<std::string> > {};

class HlsConstructionTest
    : public ::testing::TestWithParam<HlsInitDataVariant> {};

class HlsInitDataConstructionTest : public ::testing::Test {};

class HlsParseTest : public ::testing::TestWithParam<HlsAttributeVariant> {};

class HlsTest : public ::testing::Test {};
}  // namespace

TEST_P(InitializationDataTest, Parse) {
  InitializationData init_data(ISO_BMFF_VIDEO_MIME_TYPE, GetParam());
  EXPECT_FALSE(init_data.IsEmpty());
}

INSTANTIATE_TEST_CASE_P(ParsePssh, InitializationDataTest,
                        ::testing::Values(kWidevinePssh, kWidevinePsshFirst,
                                          kWidevinePsshAfterV0Pssh,
                                          kWidevinePsshAfterNonZeroFlags,
                                          kWidevinePsshAfterV1Pssh,
                                          kWidevineV1Pssh, kOtherBoxFirst,
                                          kZeroSizedPsshBox));

TEST_P(HlsKeyFormatVersionsExtractionTest, ExtractKeyFormatVersions) {
  std::vector<std::string> versions = GetParam();
  std::string key_format_versions;
  for (size_t i = 0; i < versions.size(); ++i) {
    key_format_versions += versions[i] + kHlsTestKeyFormatVersionsSeparator;
  }
  key_format_versions.resize(key_format_versions.size() -
                             sizeof(kHlsTestKeyFormatVersionsSeparator));
  std::vector<std::string> extracted_versions =
      InitializationData::ExtractKeyFormatVersions(key_format_versions);
  EXPECT_EQ(versions.size(), extracted_versions.size());
  for (size_t i = 0; i < versions.size(); ++i) {
    bool found = false;
    for (size_t j = 0; j < extracted_versions.size(); ++j) {
      if (versions[i] == extracted_versions[j]) {
        found = true;
        break;
      }
    }
    EXPECT_TRUE(found);
  }
}

INSTANTIATE_TEST_CASE_P(
    HlsTest, HlsKeyFormatVersionsExtractionTest,
    ::testing::Values(VectorOfStrings(kHlsTestKeyFormatVersion1).Generate(),
                      VectorOfStrings(kHlsTestKeyFormatVersion21).Generate(),
                      VectorOfStrings(kHlsTestKeyFormatVersion1)
                          .Add(kHlsTestKeyFormatVersion3)
                          .Generate(),
                      VectorOfStrings(kHlsTestKeyFormatVersion1)
                          .Add(kHlsTestKeyFormatVersion3)
                          .Add(kHlsTestKeyFormatVersion13)
                          .Generate(),
                      VectorOfStrings(kHlsTestKeyFormatVersion13)
                          .Add(kHlsTestKeyFormatVersion5)
                          .Add(kHlsTestKeyFormatVersion21)
                          .Add(kHlsTestKeyFormatVersion37)
                          .Generate()));

TEST_P(HlsAttributeExtractionTest, ExtractAttribute) {
  HlsAttributeVariant param = GetParam();
  std::string value;
  if (param.success_) {
    EXPECT_TRUE(InitializationData::ExtractAttribute(param.attribute_list_,
                                                     param.key_, &value));
    EXPECT_EQ(param.value_, value);
  } else {
    EXPECT_FALSE(InitializationData::ExtractAttribute(param.attribute_list_,
                                                      param.key_, &value));
  }
}

INSTANTIATE_TEST_CASE_P(
    HlsTest, HlsAttributeExtractionTest,
    ::testing::Values(
        HlsAttributeVariant(kHlsAttributeList, HLS_METHOD_ATTRIBUTE,
                            HLS_METHOD_SAMPLE_AES, true),
        HlsAttributeVariant(kHlsAttributeList, HLS_URI_ATTRIBUTE,
                            QuoteString(GenerateHlsUriData(
                                kHlsTestProvider, kHlsTestContentId,
                                VectorOfStrings(kHlsTestKeyId1).Generate())),
                            true),
        HlsAttributeVariant(kHlsAttributeList, HLS_IV_ATTRIBUTE, kHlsIvValue,
                            true),
        HlsAttributeVariant(kHlsAttributeList, HLS_KEYFORMAT_ATTRIBUTE,
                            QuoteString(kHlsKeyFormatValue), true),
        HlsAttributeVariant(kHlsAttributeList, HLS_KEYFORMAT_VERSIONS_ATTRIBUTE,
                            QuoteString(HLS_KEYFORMAT_VERSION_VALUE_1), true),
        HlsAttributeVariant(InsertHlsAttributeInList(kHlsTestKey1,
                                                     kHlsTestValue1),
                            kHlsTestKey1, kHlsTestValue1, true),
        HlsAttributeVariant(InsertHlsAttributeInList(kHlsTestKey1,
                                                     kHlsTestValue1),
                            kHlsTestKey2, kHlsTestValue2, true),
        HlsAttributeVariant(InsertHlsAttributeInList(kHlsTestKey1 + "\t",
                                                     kHlsTestValue1),
                            kHlsTestKey1, kHlsTestValue1, false),
        HlsAttributeVariant(InsertHlsAttributeInList(kHlsTestKey1,
                                                     " " + kHlsTestValue1),
                            kHlsTestKey1, kHlsTestValue1, false),
        HlsAttributeVariant(InsertHlsAttributeInList(kHlsTestKey1,
                                                     kHlsTestValue1 + " "),
                            kHlsTestKey1, kHlsTestValue1, false),
        HlsAttributeVariant(InsertHlsAttributeInList(kHlsTestKey1 + "3",
                                                     kHlsTestValue1),
                            kHlsTestKey1, kHlsTestValue1, false),
        HlsAttributeVariant(InsertHlsAttributeInList(kHlsTestKey1, ""),
                            kHlsTestKey1, "", true),
        HlsAttributeVariant(InsertHlsAttributeInList(
                                kHlsTestInvalidLowercaseKey, kHlsTestValue1),
                            kHlsTestInvalidLowercaseKey, kHlsTestValue1, false),
        HlsAttributeVariant(InsertHlsAttributeInList(kHlsTestKeyWithDash,
                                                     kHlsTestValue1),
                            kHlsTestKeyWithDash, kHlsTestValue1, true),
        HlsAttributeVariant(InsertHlsAttributeInList(
                                kHlsTestInvalidNonAlphanumKey, kHlsTestValue1),
                            kHlsTestInvalidNonAlphanumKey, kHlsTestValue1,
                            false),
        HlsAttributeVariant(
            InsertHlsAttributeInList(kHlsTestKey1, QuoteString(kHlsTestValue1)),
            kHlsTestKey1, QuoteString(kHlsTestValue1), true),
        HlsAttributeVariant(
            InsertHlsAttributeInList(
                kHlsTestKey1, QuoteString(kHlsTestValueWithEmbeddedQuote)),
            kHlsTestKey1, QuoteString(kHlsTestValueWithEmbeddedQuote), true)));

TEST_P(HlsHexAttributeExtractionTest, ExtractHexAttribute) {
  HlsAttributeVariant param = GetParam();
  std::vector<uint8_t> value;
  if (param.success_) {
    EXPECT_TRUE(InitializationData::ExtractHexAttribute(param.attribute_list_,
                                                        param.key_, &value));
    EXPECT_EQ(param.value_, b2a_hex(value));
  } else {
    EXPECT_FALSE(InitializationData::ExtractHexAttribute(param.attribute_list_,
                                                         param.key_, &value));
  }
}

INSTANTIATE_TEST_CASE_P(
    HlsTest, HlsHexAttributeExtractionTest,
    ::testing::Values(
        HlsAttributeVariant(kHlsAttributeList, HLS_IV_ATTRIBUTE, kHlsIvHexValue,
                            true),
        HlsAttributeVariant(InsertHlsAttributeInList(kHlsTestKey1,
                                                     kHlsTestEmptyHexValue),
                            kHlsTestKey1, kHlsTestEmptyHexValue, false),
        HlsAttributeVariant(InsertHlsAttributeInList(kHlsTestKey1,
                                                     kHlsTestNoHexValue),
                            kHlsTestKey1, kHlsTestNoHexValue, false),
        HlsAttributeVariant(InsertHlsAttributeInList(
                                kHlsTestKey1, kHlsTestHexValueWithOddBytes),
                            kHlsTestKey1, kHlsTestHexValueWithOddBytes, false),
        HlsAttributeVariant(InsertHlsAttributeInList(kHlsTestKey1,
                                                     kHlsTestInvalidHexValue),
                            kHlsTestKey1, kHlsTestInvalidHexValue, false)));

TEST_P(HlsQuotedAttributeExtractionTest, ExtractQuotedAttribute) {
  HlsAttributeVariant param = GetParam();
  std::string value;
  if (param.success_) {
    EXPECT_TRUE(InitializationData::ExtractQuotedAttribute(
        param.attribute_list_, param.key_, &value));
    EXPECT_EQ(param.value_, value);
  } else {
    EXPECT_FALSE(InitializationData::ExtractQuotedAttribute(
        param.attribute_list_, param.key_, &value));
  }
}

INSTANTIATE_TEST_CASE_P(
    HlsTest, HlsQuotedAttributeExtractionTest,
    ::testing::Values(
        HlsAttributeVariant(
            kHlsAttributeList, HLS_URI_ATTRIBUTE,
            GenerateHlsUriData(kHlsTestProvider, kHlsTestContentId,
                               VectorOfStrings(kHlsTestKeyId1).Generate()),
            true),
        HlsAttributeVariant(kHlsAttributeList, HLS_KEYFORMAT_ATTRIBUTE,
                            kHlsKeyFormatValue, true),
        HlsAttributeVariant(kHlsAttributeList, HLS_KEYFORMAT_VERSIONS_ATTRIBUTE,
                            HLS_KEYFORMAT_VERSION_VALUE_1, true),
        HlsAttributeVariant(
            InsertHlsAttributeInList(kHlsTestKey1, QuoteString(kHlsTestValue1)),
            kHlsTestKey1, kHlsTestValue1, true),
        HlsAttributeVariant(
            InsertHlsAttributeInList(
                kHlsTestKey1, QuoteString(kHlsTestValueWithEmbeddedQuote)),
            kHlsTestKey1, kHlsTestValueWithEmbeddedQuote, false)));

TEST_P(HlsConstructionTest, InitData) {
  HlsInitDataVariant param = GetParam();

  std::string uri =
      GenerateHlsUriData(param.provider_, param.content_id_, param.key_ids_);
  std::string value;
  EXPECT_EQ(param.success_, InitializationData::ConstructWidevineInitData(
                                param.method_, uri, &value));
  if (param.success_) {
    WidevineCencHeader cenc_header;
    EXPECT_TRUE(cenc_header.ParseFromString(value));
    EXPECT_EQ(video_widevine_server::sdk::WidevineCencHeader_Algorithm_AESCTR,
              cenc_header.algorithm());
    for (size_t i = 0; i < param.key_ids_.size(); ++i) {
      bool key_id_found = false;
      if (param.key_ids_[i].size() != 32) continue;
      for (int j = 0; j < cenc_header.key_id_size(); ++j) {
        if (param.key_ids_[i] == b2a_hex(cenc_header.key_id(j))) {
          key_id_found = true;
          break;
        }
      }
      EXPECT_TRUE(key_id_found);
    }
    EXPECT_EQ(param.provider_, cenc_header.provider());
    std::vector<uint8_t> param_content_id_vec(Base64Decode(param.content_id_));
    EXPECT_EQ(
        std::string(param_content_id_vec.begin(), param_content_id_vec.end()),
        cenc_header.content_id());
    uint32_t protection_scheme = 0;
    switch (param.method_) {
      case kHlsMethodAes128: protection_scheme = kFourCcCbc1; break;
      case kHlsMethodSampleAes: protection_scheme = kFourCcCbcs; break;
      default: break;
    }
    EXPECT_EQ(protection_scheme, ntohl(cenc_header.protection_scheme()));
  }
}

INSTANTIATE_TEST_CASE_P(
    HlsTest, HlsConstructionTest,
    ::testing::Values(
        HlsInitDataVariant(kHlsMethodAes128, "", kHlsTestContentId,
                           kHlsTestKeyId1, false),
        HlsInitDataVariant(kHlsMethodAes128, kHlsTestProvider,
                           "", kHlsTestKeyId1, false),
        HlsInitDataVariant(kHlsMethodAes128, kHlsTestProvider,
                           kHlsTestContentId, "", false),
        HlsInitDataVariant(kHlsMethodAes128, kHlsTestProvider,
                           kHlsTestContentId, kHlsTestInvalidKeyId, false),
        HlsInitDataVariant(kHlsMethodNone, kHlsTestProvider, kHlsTestContentId,
                           kHlsTestKeyId1, false),
        HlsInitDataVariant(kHlsMethodAes128, kHlsTestProvider,
                           kHlsTestContentId, kHlsTestKeyId1, true),
        HlsInitDataVariant(kHlsMethodSampleAes, kHlsTestProvider,
                           kHlsTestContentId, kHlsTestKeyId1, true),
        HlsInitDataVariant(kHlsMethodAes128, kHlsTestProvider,
                           kHlsTestContentId, kHlsTestKeyId1, true)
            .AddKeyId(kHlsTestKeyId2)
            .AddKeyId(kHlsTestKeyId3),
        HlsInitDataVariant(kHlsMethodSampleAes, kHlsTestProvider,
                           kHlsTestContentId, kHlsTestKeyId1, true)
            .AddKeyId(kHlsTestKeyId2)
            .AddKeyId(kHlsTestKeyId3),
        HlsInitDataVariant(kHlsMethodAes128, kHlsTestProvider,
                           kHlsTestContentId, kHlsTestInvalidKeyId, true)
            .AddKeyId(kHlsTestKeyId1),
        HlsInitDataVariant(kHlsMethodSampleAes, kHlsTestProvider,
                           kHlsTestContentId, kHlsTestInvalidKeyId, true)
            .AddKeyId(kHlsTestKeyId1)));

TEST_F(HlsInitDataConstructionTest, InvalidUriDataFormat) {
  std::string json =
      GenerateJsonInitData(kHlsTestProvider, kHlsTestContentId,
                           VectorOfStrings(kHlsTestKeyId1).Generate());
  std::vector<uint8_t> json_init_data(
      reinterpret_cast<const uint8_t*>(json.data()),
      reinterpret_cast<const uint8_t*>(json.data() + json.size()));
  std::string value;
  EXPECT_FALSE(InitializationData::ConstructWidevineInitData(
      kHlsMethodAes128, Base64Encode(json_init_data), &value));
}

TEST_F(HlsInitDataConstructionTest, InvalidUriBase64Encode) {
  std::string json =
      GenerateJsonInitData(kHlsTestProvider, kHlsTestContentId,
                           VectorOfStrings(kHlsTestKeyId1).Generate());
  std::string value;
  EXPECT_FALSE(InitializationData::ConstructWidevineInitData(
      kHlsMethodSampleAes, kHlsTestUriDataFormat + json, &value));
}

TEST_P(HlsParseTest, Parse) {
  HlsAttributeVariant param = GetParam();
  InitializationData init_data(HLS_INIT_DATA_FORMAT, param.attribute_list_);
  if (param.success_) {
    EXPECT_TRUE(init_data.is_hls());
    EXPECT_FALSE(init_data.IsEmpty());
    if (param.key_.compare(HLS_METHOD_ATTRIBUTE) == 0) {
      if (param.value_.compare(HLS_METHOD_SAMPLE_AES) == 0) {
        EXPECT_EQ(kHlsMethodSampleAes, init_data.hls_method());
      } else if (param.value_.compare(HLS_METHOD_AES_128) == 0) {
        EXPECT_EQ(kHlsMethodAes128, init_data.hls_method());
      } else if (param.value_.compare(HLS_METHOD_NONE) == 0) {
        EXPECT_EQ(kHlsMethodNone, init_data.hls_method());
      }
    } else {
      EXPECT_EQ(kHlsMethodSampleAes, init_data.hls_method());
    }

    WidevineCencHeader cenc_header;
    EXPECT_TRUE(cenc_header.ParseFromString(init_data.data()));
    EXPECT_EQ(video_widevine_server::sdk::WidevineCencHeader_Algorithm_AESCTR,
              cenc_header.algorithm());
    if (param.key_.compare(kJsonProvider) == 0) {
      EXPECT_EQ(param.value_, cenc_header.provider());
    } else if (param.key_.compare(kJsonContentId) == 0) {
      EXPECT_EQ(param.value_, cenc_header.content_id());
    } else if (param.key_.compare(kJsonKeyIds) == 0) {
      EXPECT_EQ(param.value_, b2a_hex(cenc_header.key_id(0)));
    }

    EXPECT_EQ(kHlsIvHexValue, b2a_hex(init_data.hls_iv()));
  } else {
    EXPECT_TRUE(init_data.is_hls());
    EXPECT_TRUE(init_data.IsEmpty());
  }
}

INSTANTIATE_TEST_CASE_P(
    HlsTest, HlsParseTest,
    ::testing::Values(
        HlsAttributeVariant(kHlsAttributeList, "", "", true),
        HlsAttributeVariant(kHlsAttributeListKeyFormatUnknown,
                            HLS_KEYFORMAT_ATTRIBUTE, kHlsKeyFormatValueOther,
                            false),
        HlsAttributeVariant(kHlsAttributeListKeyFormatVersionUnsupported,
                            HLS_KEYFORMAT_VERSIONS_ATTRIBUTE, "2", false),
        HlsAttributeVariant(kHlsAttributeListMethodAes128, HLS_METHOD_ATTRIBUTE,
                            HLS_METHOD_AES_128, true),
        HlsAttributeVariant(kHlsAttributeListMethodNone, HLS_METHOD_ATTRIBUTE,
                            HLS_METHOD_NONE, false),
        HlsAttributeVariant(kHlsAttributeListKeyFormatVersionMultiple,
                            HLS_KEYFORMAT_VERSIONS_ATTRIBUTE,
                            HLS_KEYFORMAT_VERSION_VALUE_1, true),
        HlsAttributeVariant(kHlsAttributeListMethodInvalid,
                            HLS_METHOD_ATTRIBUTE, kHlsTestValue1, false),
        HlsAttributeVariant(kHlsAttributeListInvalidUriNoProvider,
                            kJsonProvider, kHlsTestProvider, false),
        HlsAttributeVariant(kHlsAttributeListInvalidUriNoContentId,
                            kJsonContentId, kHlsTestContentId, false),
        HlsAttributeVariant(kHlsAttributeListInvalidUriNoKeyId, kJsonKeyIds,
                            kHlsTestKeyId1, false),
        HlsAttributeVariant(kHlsAttributeListValidUriThreeKeyIds, kJsonKeyIds,
                            kHlsTestKeyId1, true),
        HlsAttributeVariant(kHlsAttributeListNoIv, HLS_IV_ATTRIBUTE,
                            kHlsTestNoHexValue, false),
        HlsAttributeVariant(kHlsAttributeListInvalidIv, HLS_IV_ATTRIBUTE,
                            kHlsTestHexValueWithOddBytes, false)));

}  // namespace wvcdm
