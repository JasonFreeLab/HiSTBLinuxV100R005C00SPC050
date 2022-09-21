// Copyright 2013 Google Inc. All Rights Reserved.

#include <utility>

#include <gtest/gtest.h>

#include "log.h"
#include "string_conversions.h"

namespace wvcdm {

namespace {

// Test vectors as suggested by http://tools.ietf.org/html/rfc4648#section-10
const std::string kNullString("");
const std::string kf("f");
const std::string kfo("fo");
const std::string kfoo("foo");
const std::string kfoob("foob");
const std::string kfooba("fooba");
const std::string kfoobar("foobar");
const std::string kfB64("Zg==");
const std::string kfoB64("Zm8=");
const std::string kfooB64("Zm9v");
const std::string kfoobB64("Zm9vYg==");
const std::string kfoobaB64("Zm9vYmE=");
const std::string kfoobarB64("Zm9vYmFy");

// Arbitrary clear test vectors
const std::string kMultipleOf24BitsData("Good day!");
const std::string kOneByteOverData("Hello Friend!");
const std::string kTwoBytesOverData("Hello Friend!!");
const std::string kTestData =
    "\030\361\\\366\267> \331\210\360\\-\311:\324\256\376"
    "\261\234\241\326d\326\177\346\346\223\333Y\305\214\330";

// Arbitrary encoded test vectors
const std::string kMultipleOf24BitsB64Data("R29vZCBkYXkh");
const std::string kOneByteOverB64Data("SGVsbG8gRnJpZW5kIQ==");
const std::string kTwoBytesOverB64Data("SGVsbG8gRnJpZW5kISE=");
const std::string kB64TestData = "GPFc9rc+INmI8FwtyTrUrv6xnKHWZNZ/5uaT21nFjNg=";

const std::pair<const std::string *, const std::string *> kBase64TestVectors[] =
    {make_pair(&kNullString, &kNullString),
     make_pair(&kf, &kfB64),
     make_pair(&kfo, &kfoB64),
     make_pair(&kfoo, &kfooB64),
     make_pair(&kfoob, &kfoobB64),
     make_pair(&kfooba, &kfoobaB64),
     make_pair(&kfoobar, &kfoobarB64),
     make_pair(&kMultipleOf24BitsData, &kMultipleOf24BitsB64Data),
     make_pair(&kOneByteOverData, &kOneByteOverB64Data),
     make_pair(&kTwoBytesOverData, &kTwoBytesOverB64Data),
     make_pair(&kTestData, &kB64TestData)};

std::string ConvertToBase64WebSafe(const std::string &std_base64_string) {
  std::string str(std_base64_string);
  for (size_t i = 0; i < str.size(); ++i) {
    if (str[i] == '+')
      str[i] = '-';
    else if (str[i] == '/')
      str[i] = '_';
  }
  return str;
}

}  // namespace

class Base64EncodeDecodeTest
    : public ::testing::TestWithParam<
          std::pair<const std::string *, const std::string *> > {};

TEST_P(Base64EncodeDecodeTest, EncodeDecodeTest) {
  std::pair<const std::string *, const std::string *> values = GetParam();
  std::vector<uint8_t> decoded_vector = Base64Decode(values.second->data());
  std::string decoded_string(decoded_vector.begin(), decoded_vector.end());
  EXPECT_STREQ(values.first->data(), decoded_string.data());
  std::string b64_string = Base64Encode(decoded_vector);
  EXPECT_STREQ(values.second->data(), b64_string.data());
}

TEST_P(Base64EncodeDecodeTest, WebSafeEncodeDecodeTest) {
  std::pair<const std::string *, const std::string *> values = GetParam();
  std::string encoded_string = ConvertToBase64WebSafe(*(values.second));
  std::vector<uint8_t> decoded_vector = Base64SafeDecode(encoded_string);
  std::string decoded_string(decoded_vector.begin(), decoded_vector.end());
  EXPECT_STREQ(values.first->data(), decoded_string.data());
  std::string b64_string = Base64SafeEncode(decoded_vector);
  EXPECT_STREQ(encoded_string.data(), b64_string.data());
}

INSTANTIATE_TEST_CASE_P(ExecutesBase64Test, Base64EncodeDecodeTest,
                        ::testing::ValuesIn(kBase64TestVectors));

class HtoNLL64Test : public ::testing::Test {};

TEST_F(HtoNLL64Test, PositiveNumber) {
  uint8_t data[8] = {1, 2, 3, 4, 5, 6, 7, 8};
  int64_t *network_byte_order = reinterpret_cast<int64_t *>(data);
  int64_t host_byte_order = htonll64(*network_byte_order);
  EXPECT_EQ(0x0102030405060708, host_byte_order);
}
TEST_F(HtoNLL64Test, NegativeNumber) {
  uint8_t data[8] = {0xfe, 2, 3, 4, 5, 6, 7, 8};
  int64_t *network_byte_order = reinterpret_cast<int64_t *>(data);
  int64_t host_byte_order = htonll64(*network_byte_order);
  EXPECT_EQ(-0x01FdFcFbFaF9F8F8, host_byte_order);
}
}  // namespace wvcdm
