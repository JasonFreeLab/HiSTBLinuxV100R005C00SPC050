// Copyright 2014 Google Inc. All Rights Reserved.

#include "OEMCryptoCENC.h"

#include <string>
#include <gtest/gtest.h>
#include "log.h"
#include "oemcrypto_logging.h"
#include "oemcrypto_mock.cpp"

class OEMCryptoLoggingTest : public ::testing::Test {
 protected:
  OEMCryptoLoggingTest() {}

  void SetUp() {
    ::testing::Test::SetUp();
    ASSERT_EQ(OEMCrypto_SUCCESS, OEMCrypto_Initialize());
  }

  void TearDown() {
    OEMCrypto_Terminate();
    ::testing::Test::TearDown();
  }
};

TEST_F(OEMCryptoLoggingTest, TestDumpHexFunctions) {
  uint8_t vector[] = {0xFA, 0x11, 0x28, 0x33};
  std::string buffer;
  wvoec_mock::dump_hex_helper(buffer, "name", vector, 4u);
  ASSERT_EQ("name = \n     wvcdm::a2b_hex(\"FA112833\");\n", buffer);

  uint8_t vector2[] = {
      0xFA, 0x11, 0x28, 0x33, 0xFA, 0x11, 0x28, 0x33, 0xFA, 0x11,
      0x28, 0x33, 0xFA, 0x11, 0x28, 0x33, 0xFA, 0x11, 0x28, 0x33,
      0xFA, 0x11, 0x28, 0x33, 0x01, 0x14, 0x28, 0xAB, 0xFA, 0xCD,
      0xEF, 0x67, 0x01, 0x14, 0x28, 0xAB, 0xFA, 0xCD, 0xEF, 0x67,
  };

  buffer.clear();  // dump_hex_helper appends to buffer
  wvoec_mock::dump_hex_helper(buffer, "name", vector2, 40u);
  ASSERT_EQ(
      "name = \n     "
      "wvcdm::a2b_hex("
      "\"FA112833FA112833FA112833FA112833FA112833FA112833011428ABFACDEF67\"\n  "
      "                  \"011428ABFACDEF67\");\n",
      buffer);

  buffer.clear();  // dump_hex_helper appends to buffer
  wvoec_mock::dump_array_part_helper(buffer, "array", 5u, "name", vector2, 40u);
  ASSERT_EQ(
      "std::string s5_name = \n     "
      "wvcdm::a2b_hex("
      "\"FA112833FA112833FA112833FA112833FA112833FA112833011428ABFACDEF67\"\n  "
      "                  \"011428ABFACDEF67\");\narray[5].name = message_ptr + "
      "message.find(s5_name.data());\n",
      buffer);

  buffer.clear();  // dump_hex_helper appends to buffer
  wvoec_mock::dump_array_part_helper(buffer, "array", 5u, "name", NULL, 40u);
  ASSERT_EQ("array[5].name = NULL;\n", buffer);
}

TEST_F(OEMCryptoLoggingTest, TestChangeLoggingLevel) {
  wvoec_mock::SetLoggingLevel(wvcdm::LOG_WARN);
  ASSERT_EQ(wvcdm::LOG_WARN, wvcdm::g_cutoff);

  wvoec_mock::SetLoggingLevel(wvcdm::LOG_INFO);
  ASSERT_EQ(wvcdm::LOG_INFO, wvcdm::g_cutoff);

  wvoec_mock::SetLoggingSettings(wvcdm::LOG_WARN,
                                 wvoec_mock::kLoggingDumpTraceAll);
  ASSERT_EQ(wvcdm::LOG_WARN, wvcdm::g_cutoff);
  ASSERT_TRUE(wvoec_mock::LogCategoryEnabled(wvoec_mock::kLoggingDumpTraceAll));
  wvoec_mock::TurnOffLoggingForAllCategories();

  wvoec_mock::SetLoggingLevel(wvcdm::LOG_VERBOSE);
  ASSERT_EQ(wvcdm::LOG_VERBOSE, wvcdm::g_cutoff);

  wvoec_mock::SetLoggingLevel(wvcdm::LOG_WARN);
}

TEST_F(OEMCryptoLoggingTest, TestChangeLoggingCategories) {
  using namespace wvoec_mock;
  TurnOffLoggingForAllCategories();
  ASSERT_FALSE(LogCategoryEnabled(kLoggingTraceDecryption |
                                  kLoggingTraceOEMCryptoCalls));

  AddLoggingForCategories(kLoggingDumpKeyControlBlocks |
                          kLoggingDumpDerivedKeys);
  ASSERT_TRUE(LogCategoryEnabled(kLoggingDumpKeyControlBlocks));
  ASSERT_FALSE(LogCategoryEnabled(kLoggingTraceUsageTable));
  ASSERT_TRUE(LogCategoryEnabled(kLoggingDumpTraceAll));

  RemoveLoggingForCategories(kLoggingDumpKeyControlBlocks |
                             kLoggingTraceUsageTable);
  ASSERT_FALSE(LogCategoryEnabled(kLoggingDumpKeyControlBlocks));

  ASSERT_TRUE(LogCategoryEnabled(kLoggingDumpDerivedKeys));
  ASSERT_FALSE(LogCategoryEnabled(kLoggingTraceUsageTable));

  TurnOffLoggingForAllCategories();
  ASSERT_FALSE(LogCategoryEnabled(kLoggingTraceUsageTable));

  AddLoggingForCategories(kLoggingDumpTraceAll);
  ASSERT_TRUE(LogCategoryEnabled(kLoggingDumpKeyControlBlocks));

  ASSERT_TRUE(LogCategoryEnabled(kLoggingTraceOEMCryptoCalls));
  ASSERT_TRUE(LogCategoryEnabled(kLoggingDumpContentKeys));
  ASSERT_TRUE(LogCategoryEnabled(kLoggingDumpKeyControlBlocks));
  ASSERT_TRUE(LogCategoryEnabled(kLoggingDumpDerivedKeys));
  ASSERT_TRUE(LogCategoryEnabled(kLoggingTraceNonce));
  ASSERT_TRUE(LogCategoryEnabled(kLoggingTraceDecryption));
  ASSERT_TRUE(LogCategoryEnabled(kLoggingTraceUsageTable));
  ASSERT_TRUE(LogCategoryEnabled(kLoggingDumpTraceAll));

  RemoveLoggingForCategories(kLoggingDumpKeyControlBlocks);
  ASSERT_FALSE(LogCategoryEnabled(kLoggingDumpKeyControlBlocks));
}
