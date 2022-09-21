// Copyright 2015 Google Inc. All Rights Reserved.

#include <string>
#include <errno.h>
#include <getopt.h>
#include <gtest/gtest.h>

#include "buffer_reader.h"

namespace wvcdm {

class BufferReaderTest : public testing::Test {
 public:
  template <typename T>
  void WriteToBuffer(uint8_t* buffer, T v) {
    for (size_t i = 0; i < sizeof(T); ++i) {
      size_t insertAt = (sizeof(T) - i) - 1;  // reverse the order of i
      size_t shiftAmount = 8 * i;

      buffer[insertAt] = (uint8_t)((v >> shiftAmount) & 0xff);
    }
  }

  // populate and validate data by cycling through the alphabet
  // (lower case) so that it will work for strings and raw bytes

  void PopulateData(uint8_t* dest, size_t byte_count) {
    for (size_t i = 0; i < byte_count; i++) {
      dest[i] = (uint8_t)(i % 26 + 'a');
    }
  }

  bool ValidateData(const uint8_t* data, size_t byte_count) {
    for (size_t i = 0; i < byte_count; i++) {
      if (data[i] != (uint8_t)(i % 26 + 'a')) {
        return false;
      }
    }

    return true;
  }

  bool ValidateReader(const BufferReader& reader,
                      const uint8_t* expectedAddress, size_t expectedSize,
                      size_t expectedPosition) {
    return reader.data() == expectedAddress && reader.size() == expectedSize &&
           reader.pos() == expectedPosition;
  }

  bool CheckRead1(uint8_t input) {
    uint8_t raw_data[sizeof(input)];
    WriteToBuffer(raw_data, input);

    BufferReader reader(raw_data, sizeof(raw_data));

    uint8_t read;

    return reader.Read1(&read) && input == read &&
           ValidateReader(reader, raw_data, sizeof(raw_data), sizeof(input));
  }

  bool CheckRead2(uint16_t input) {
    uint8_t raw_data[sizeof(input)];
    WriteToBuffer(raw_data, input);

    BufferReader reader(raw_data, sizeof(raw_data));

    uint16_t read;

    return reader.Read2(&read) && input == read &&
           ValidateReader(reader, raw_data, sizeof(raw_data), sizeof(input));
  }

  bool CheckRead2s(int16_t input) {
    uint8_t raw_data[sizeof(input)];
    WriteToBuffer(raw_data, input);

    BufferReader reader(raw_data, sizeof(raw_data));

    int16_t read;

    return reader.Read2s(&read) && input == read &&
           ValidateReader(reader, raw_data, sizeof(raw_data), sizeof(input));
  }

  bool CheckRead4(uint32_t input) {
    uint8_t raw_data[sizeof(input)];
    WriteToBuffer(raw_data, input);

    BufferReader reader(raw_data, sizeof(raw_data));

    uint32_t read;

    return reader.Read4(&read) && input == read &&
           ValidateReader(reader, raw_data, sizeof(raw_data), sizeof(input));
  }

  bool CheckRead4s(int32_t input) {
    uint8_t raw_data[sizeof(input)];
    WriteToBuffer(raw_data, input);

    BufferReader reader(raw_data, sizeof(raw_data));

    int32_t read;

    return reader.Read4s(&read) && input == read &&
           ValidateReader(reader, raw_data, sizeof(raw_data), sizeof(input));
  }

  bool CheckRead8(uint64_t input) {
    uint8_t raw_data[sizeof(input)];
    WriteToBuffer(raw_data, input);

    BufferReader reader(raw_data, sizeof(raw_data));

    uint64_t read;

    return reader.Read8(&read) && input == read &&
           ValidateReader(reader, raw_data, sizeof(raw_data), sizeof(input));
  }

  bool CheckRead8s(int64_t input) {
    uint8_t raw_data[sizeof(input)];
    WriteToBuffer(raw_data, input);

    BufferReader reader(raw_data, sizeof(raw_data));

    int64_t read;

    return reader.Read8s(&read) && input == read &&
           ValidateReader(reader, raw_data, sizeof(raw_data), sizeof(input));
  }

  bool CheckRead4Into8(uint32_t input) {
    uint8_t raw_data[sizeof(input)];
    WriteToBuffer(raw_data, input);

    BufferReader reader(raw_data, sizeof(raw_data));

    uint64_t read;
    return reader.Read4Into8(&read) && read == input &&
           ValidateReader(reader, raw_data, sizeof(raw_data), sizeof(input));
  }

  bool CheckRead4sInto8s(int32_t input) {
    uint8_t raw_data[sizeof(input)];
    WriteToBuffer(raw_data, input);

    BufferReader reader(raw_data, sizeof(raw_data));

    int64_t read;
    return reader.Read4sInto8s(&read) && read == input &&
           ValidateReader(reader, raw_data, sizeof(raw_data), sizeof(input));
  }
};

TEST_F(BufferReaderTest, InitializeGoodDataAndGoodSize) {
  uint8_t raw_data[16];
  PopulateData(raw_data, sizeof(raw_data));

  BufferReader reader(raw_data, sizeof(raw_data));

  ASSERT_TRUE(ValidateData(raw_data, sizeof(raw_data)));
  ASSERT_TRUE(ValidateReader(reader, raw_data, sizeof(raw_data), 0));
}

TEST_F(BufferReaderTest, InitializeGoodDataAndNoSize) {
  uint8_t raw_data[16];
  PopulateData(raw_data, sizeof(raw_data));

  BufferReader reader(raw_data, 0);

  ASSERT_TRUE(ValidateData(raw_data, sizeof(raw_data)));
  ASSERT_TRUE(ValidateReader(reader, raw_data, 0, 0));
}

TEST_F(BufferReaderTest, InitializeNoDataNoSize) {
  BufferReader reader(NULL, 0);
  ASSERT_TRUE(ValidateReader(reader, NULL, 0, 0));
}

TEST_F(BufferReaderTest, InitializeNoDataBadSize) {
  BufferReader reader(NULL, 16);

  // Buffer reader should default to a size of 0 when given
  // NULL data to ensure no reading of bad data
  ASSERT_TRUE(ValidateReader(reader, NULL, 0, 0));
}

TEST_F(BufferReaderTest, HasBytesWithBytes) {
  uint8_t raw_data[16];
  PopulateData(raw_data, sizeof(raw_data));

  BufferReader reader(raw_data, sizeof(raw_data));

  // the reader should have enough bytes from 0 to the size of the buffer
  for (size_t i = 0; i <= sizeof(raw_data); i++) {
    ASSERT_TRUE(reader.HasBytes(i));
  }

  ASSERT_FALSE(reader.HasBytes(sizeof(raw_data) + 1));

  ASSERT_TRUE(ValidateData(raw_data, sizeof(raw_data)));
  ASSERT_TRUE(ValidateReader(reader, raw_data, sizeof(raw_data), 0));
}

TEST_F(BufferReaderTest, HasBytesWithEmptyBuffer) {
  uint8_t raw_data[16];
  PopulateData(raw_data, sizeof(raw_data));

  BufferReader reader(raw_data, 0);

  ASSERT_FALSE(reader.HasBytes(1));
  ASSERT_TRUE(reader.HasBytes(0));

  ASSERT_TRUE(ValidateData(raw_data, sizeof(raw_data)));
  ASSERT_TRUE(ValidateReader(reader, raw_data, 0, 0));
}

TEST_F(BufferReaderTest, HasBytesWithNullBuffer) {
  BufferReader reader(NULL, 8);

  ASSERT_FALSE(reader.HasBytes(1));
  ASSERT_TRUE(reader.HasBytes(0));

  ASSERT_TRUE(ValidateReader(reader, NULL, 0, 0));
}

TEST_F(BufferReaderTest, HasBytesAfterAllRead) {
  uint8_t raw_data[16];
  PopulateData(raw_data, sizeof(raw_data));

  BufferReader reader(raw_data, sizeof(raw_data));

  for (size_t i = 0; i < sizeof(raw_data); i++) {
    uint8_t read;
    ASSERT_TRUE(reader.Read1(&read));
  }

  ASSERT_FALSE(reader.HasBytes(1));
  ASSERT_TRUE(reader.HasBytes(0));

  ASSERT_TRUE(ValidateData(raw_data, sizeof(raw_data)));
  ASSERT_TRUE(
      ValidateReader(reader, raw_data, sizeof(raw_data), sizeof(raw_data)));
}

TEST_F(BufferReaderTest, Read1LargeNumber) { ASSERT_TRUE(CheckRead1(0xFF)); }

TEST_F(BufferReaderTest, Read1SmallNumber) { ASSERT_TRUE(CheckRead1(0x0F)); }

TEST_F(BufferReaderTest, Read1Zero) { ASSERT_TRUE(CheckRead1(0)); }

TEST_F(BufferReaderTest, Read1WithNoData) {
  uint8_t raw_data[16];
  PopulateData(raw_data, sizeof(raw_data));

  BufferReader reader(raw_data, 0);

  uint8_t read;
  ASSERT_FALSE(reader.Read1(&read));

  ASSERT_TRUE(ValidateData(raw_data, sizeof(raw_data)));
  ASSERT_TRUE(ValidateReader(reader, raw_data, 0, 0));
}

TEST_F(BufferReaderTest, Read1WithNullBuffer) {
  BufferReader reader(NULL, 16);

  uint8_t read;
  ASSERT_FALSE(reader.Read1(&read));

  ASSERT_TRUE(ValidateReader(reader, NULL, 0, 0));
}

TEST_F(BufferReaderTest, Read1WithNullReturn) {
  uint8_t raw_data[16];
  PopulateData(raw_data, sizeof(raw_data));

  BufferReader reader(raw_data, sizeof(raw_data));

  ASSERT_FALSE(reader.Read1(NULL));

  ASSERT_TRUE(ValidateData(raw_data, sizeof(raw_data)));
  ASSERT_TRUE(ValidateReader(reader, raw_data, sizeof(raw_data), 0));
}

TEST_F(BufferReaderTest, Read2LargeNumber) { ASSERT_TRUE(CheckRead2(30000)); }

TEST_F(BufferReaderTest, Read2SmallNumber) { ASSERT_TRUE(CheckRead2(10)); }

TEST_F(BufferReaderTest, Read2Zero) { ASSERT_TRUE(CheckRead2(0)); }

TEST_F(BufferReaderTest, Read2WithNoData) {
  uint8_t raw_data[16];
  PopulateData(raw_data, sizeof(raw_data));

  BufferReader reader(raw_data, 0);

  uint16_t read;
  ASSERT_FALSE(reader.Read2(&read));

  ASSERT_TRUE(ValidateData(raw_data, sizeof(raw_data)));
  ASSERT_TRUE(ValidateReader(reader, raw_data, 0, 0));
}

TEST_F(BufferReaderTest, Read2WithNullBuffer) {
  BufferReader reader(NULL, 16);

  uint16_t read;
  ASSERT_FALSE(reader.Read2(&read));

  ASSERT_TRUE(ValidateReader(reader, NULL, 0, 0));
}

TEST_F(BufferReaderTest, Read2WithNullReturn) {
  uint8_t raw_data[16];
  PopulateData(raw_data, sizeof(raw_data));

  BufferReader reader(raw_data, sizeof(raw_data));

  ASSERT_FALSE(reader.Read2(NULL));

  ASSERT_TRUE(ValidateData(raw_data, sizeof(raw_data)));
  ASSERT_TRUE(ValidateReader(reader, raw_data, sizeof(raw_data), 0));
}

TEST_F(BufferReaderTest, Read2sLargePositive) {
  ASSERT_TRUE(CheckRead2s(30000));
}

TEST_F(BufferReaderTest, Read2sSmallPositive) { ASSERT_TRUE(CheckRead2s(10)); }

TEST_F(BufferReaderTest, Read2sZero) { ASSERT_TRUE(CheckRead2s(0)); }

TEST_F(BufferReaderTest, Read2sSmallNegative) { ASSERT_TRUE(CheckRead2s(-10)); }

TEST_F(BufferReaderTest, Read2sLargeNegative) {
  ASSERT_TRUE(CheckRead2s(-30000));
}

TEST_F(BufferReaderTest, Read2sWithNoData) {
  uint8_t raw_data[16];
  PopulateData(raw_data, sizeof(raw_data));

  BufferReader reader(raw_data, 0);

  int16_t read;
  ASSERT_FALSE(reader.Read2s(&read));

  ASSERT_TRUE(ValidateData(raw_data, sizeof(raw_data)));
  ASSERT_TRUE(ValidateReader(reader, raw_data, 0, 0));
}

TEST_F(BufferReaderTest, Read2sWithNullBuffer) {
  BufferReader reader(NULL, 16);

  int16_t read;
  ASSERT_FALSE(reader.Read2s(&read));

  ASSERT_TRUE(ValidateReader(reader, NULL, 0, 0));
}

TEST_F(BufferReaderTest, Read2sWithNullReturn) {
  uint8_t raw_data[16];
  PopulateData(raw_data, sizeof(raw_data));

  BufferReader reader(raw_data, sizeof(raw_data));

  ASSERT_FALSE(reader.Read2s(NULL));

  ASSERT_TRUE(ValidateData(raw_data, sizeof(raw_data)));
  ASSERT_TRUE(ValidateReader(reader, raw_data, sizeof(raw_data), 0));
}

TEST_F(BufferReaderTest, Read4LargeNumber) {
  // a number near uint32's max value
  ASSERT_TRUE(CheckRead4(2000000000));
}

TEST_F(BufferReaderTest, Read4SmallNumber) { ASSERT_TRUE(CheckRead4(10)); }

TEST_F(BufferReaderTest, Read4Zero) { ASSERT_TRUE(CheckRead4(0)); }

TEST_F(BufferReaderTest, Read4WithNoData) {
  uint8_t raw_data[16];
  PopulateData(raw_data, sizeof(raw_data));

  BufferReader reader(raw_data, 0);

  uint32_t read;
  ASSERT_FALSE(reader.Read4(&read));

  ASSERT_TRUE(ValidateData(raw_data, sizeof(raw_data)));
  ASSERT_TRUE(ValidateReader(reader, raw_data, 0, 0));
}

TEST_F(BufferReaderTest, Read4WithNullBuffer) {
  BufferReader reader(NULL, 16);

  uint32_t read;
  ASSERT_FALSE(reader.Read4(&read));

  ASSERT_TRUE(ValidateReader(reader, NULL, 0, 0));
}

TEST_F(BufferReaderTest, Read4WithNullReturn) {
  uint8_t raw_data[16];
  PopulateData(raw_data, sizeof(raw_data));

  BufferReader reader(raw_data, sizeof(raw_data));

  ASSERT_FALSE(reader.Read4(NULL));

  ASSERT_TRUE(ValidateData(raw_data, sizeof(raw_data)));
  ASSERT_TRUE(ValidateReader(reader, raw_data, sizeof(raw_data), 0));
}

TEST_F(BufferReaderTest, Read4sLargePositive) {
  // a number near int32's max value
  ASSERT_TRUE(CheckRead4s(2000000000));
}

TEST_F(BufferReaderTest, Read4sSmallPositive) { ASSERT_TRUE(CheckRead4s(10)); }

TEST_F(BufferReaderTest, Read4sZero) { ASSERT_TRUE(CheckRead4s(0)); }

TEST_F(BufferReaderTest, Read4sSmallNegative) { ASSERT_TRUE(CheckRead4s(-10)); }

TEST_F(BufferReaderTest, Read4sLargeNegative) {
  // a number near int32's max negative value
  ASSERT_TRUE(CheckRead4s(-2000000000));
}

TEST_F(BufferReaderTest, Read4sWithNoData) {
  uint8_t raw_data[16];
  PopulateData(raw_data, sizeof(raw_data));

  BufferReader reader(raw_data, 0);

  int32_t read;
  ASSERT_FALSE(reader.Read4s(&read));

  ASSERT_TRUE(ValidateData(raw_data, sizeof(raw_data)));
  ASSERT_TRUE(ValidateReader(reader, raw_data, 0, 0));
}

TEST_F(BufferReaderTest, Read4sWithNullBuffer) {
  BufferReader reader(NULL, 16);

  int32_t read;
  ASSERT_FALSE(reader.Read4s(&read));

  ASSERT_TRUE(ValidateReader(reader, NULL, 0, 0));
}

TEST_F(BufferReaderTest, Read4sWithNullReturn) {
  uint8_t raw_data[16];
  PopulateData(raw_data, sizeof(raw_data));

  BufferReader reader(raw_data, sizeof(raw_data));

  ASSERT_FALSE(reader.Read4s(NULL));

  ASSERT_TRUE(ValidateData(raw_data, sizeof(raw_data)));
  ASSERT_TRUE(ValidateReader(reader, raw_data, sizeof(raw_data), 0));
}

TEST_F(BufferReaderTest, Read8LargeNumber) {
  // a number near uint64's max value
  ASSERT_TRUE(CheckRead8(9000000000000000000));
}

TEST_F(BufferReaderTest, Read8SmallNumber) { ASSERT_TRUE(CheckRead8(10)); }

TEST_F(BufferReaderTest, Read8Zero) { ASSERT_TRUE(CheckRead8(0)); }

TEST_F(BufferReaderTest, Read8WithNoData) {
  uint8_t raw_data[16];
  PopulateData(raw_data, sizeof(raw_data));

  BufferReader reader(raw_data, 0);

  uint64_t read;
  ASSERT_FALSE(reader.Read8(&read));

  ASSERT_TRUE(ValidateData(raw_data, sizeof(raw_data)));
  ASSERT_TRUE(ValidateReader(reader, raw_data, 0, 0));
}

TEST_F(BufferReaderTest, Read8WithNullBuffer) {
  BufferReader reader(NULL, 16);

  uint64_t read;
  ASSERT_FALSE(reader.Read8(&read));

  ASSERT_TRUE(ValidateReader(reader, NULL, 0, 0));
}

TEST_F(BufferReaderTest, Read8WithNullReturn) {
  uint8_t raw_data[16];
  PopulateData(raw_data, sizeof(raw_data));

  BufferReader reader(raw_data, sizeof(raw_data));

  ASSERT_FALSE(reader.Read8(NULL));

  ASSERT_TRUE(ValidateData(raw_data, sizeof(raw_data)));
  ASSERT_TRUE(ValidateReader(reader, raw_data, sizeof(raw_data), 0));
}

TEST_F(BufferReaderTest, Read8sLargePositive) {
  // a number near int64's max value
  ASSERT_TRUE(CheckRead8s(9000000000000000000));
}

TEST_F(BufferReaderTest, Read8sSmallPositive) { ASSERT_TRUE(CheckRead8s(10)); }

TEST_F(BufferReaderTest, Read8sZero) { ASSERT_TRUE(CheckRead8s(0)); }

TEST_F(BufferReaderTest, Read8sSmallNegative) { ASSERT_TRUE(CheckRead8s(-10)); }

TEST_F(BufferReaderTest, Read8sLargeNegative) {
  // a number near int64's max negative value
  ASSERT_TRUE(CheckRead8s(-9000000000000000000));
}

TEST_F(BufferReaderTest, Read8sWithNoData) {
  uint8_t raw_data[16];
  PopulateData(raw_data, sizeof(raw_data));

  BufferReader reader(raw_data, 0);

  int64_t read;
  ASSERT_FALSE(reader.Read8s(&read));

  ASSERT_TRUE(ValidateData(raw_data, sizeof(raw_data)));
  ASSERT_TRUE(ValidateReader(reader, raw_data, 0, 0));
}

TEST_F(BufferReaderTest, Read8sWithNullBuffer) {
  BufferReader reader(NULL, 16);

  int64_t read;
  ASSERT_FALSE(reader.Read8s(&read));

  ASSERT_TRUE(ValidateReader(reader, NULL, 0, 0));
}

TEST_F(BufferReaderTest, Read8sWithNullReturn) {
  uint8_t raw_data[16];
  PopulateData(raw_data, sizeof(raw_data));

  BufferReader reader(raw_data, sizeof(raw_data));

  ASSERT_FALSE(reader.Read8s(NULL));

  ASSERT_TRUE(ValidateData(raw_data, sizeof(raw_data)));
  ASSERT_TRUE(ValidateReader(reader, raw_data, sizeof(raw_data), 0));
}

TEST_F(BufferReaderTest, ReadString) {
  uint8_t raw_data[5];
  PopulateData(raw_data, sizeof(raw_data));

  BufferReader reader(raw_data, sizeof(raw_data));

  std::string read;
  ASSERT_TRUE(reader.ReadString(&read, sizeof(raw_data)));

  ASSERT_TRUE(ValidateData(raw_data, sizeof(raw_data)));
  ASSERT_TRUE(read.length() == sizeof(raw_data));
  ASSERT_TRUE(ValidateData((const uint8_t*)read.c_str(), read.length()));

  ASSERT_TRUE(
      ValidateReader(reader, raw_data, sizeof(raw_data), sizeof(raw_data)));
}

TEST_F(BufferReaderTest, ReadStringNullSource) {
  BufferReader reader(NULL, 5);

  std::string read;
  ASSERT_FALSE(reader.ReadString(&read, 5));

  ASSERT_TRUE(ValidateReader(reader, NULL, 0, 0));
}

TEST_F(BufferReaderTest, ReadStringNullReturn) {
  uint8_t raw_data[16];
  PopulateData(raw_data, sizeof(raw_data));

  BufferReader reader(raw_data, sizeof(raw_data));

  ASSERT_FALSE(reader.ReadString(NULL, 5));

  ASSERT_TRUE(ValidateData(raw_data, sizeof(raw_data)));
  ASSERT_TRUE(ValidateReader(reader, raw_data, sizeof(raw_data), 0));
}

TEST_F(BufferReaderTest, ReadStringZeroCount) {
  uint8_t raw_data[16];
  PopulateData(raw_data, sizeof(raw_data));

  BufferReader reader(raw_data, sizeof(raw_data));

  std::string read;
  ASSERT_TRUE(reader.ReadString(&read, 0));

  ASSERT_TRUE(0 == read.length());
  ASSERT_TRUE(ValidateData(raw_data, sizeof(raw_data)));
  ASSERT_TRUE(ValidateReader(reader, raw_data, sizeof(raw_data), 0));
}

TEST_F(BufferReaderTest, ReadStringTooLarge) {
  uint8_t raw_data[16];
  PopulateData(raw_data, sizeof(raw_data));

  BufferReader reader(raw_data, sizeof(raw_data));

  std::string read;
  ASSERT_FALSE(reader.ReadString(&read, sizeof(raw_data) * 2));

  ASSERT_TRUE(0 == read.length());
  ASSERT_TRUE(ValidateData(raw_data, sizeof(raw_data)));
  ASSERT_TRUE(ValidateReader(reader, raw_data, sizeof(raw_data), 0));
}

TEST_F(BufferReaderTest, ReadVector) {
  uint8_t raw_data[16];
  PopulateData(raw_data, sizeof(raw_data));

  BufferReader reader(raw_data, sizeof(raw_data));

  std::vector<uint8_t> read;

  ASSERT_TRUE(reader.ReadVec(&read, 4));

  ASSERT_TRUE(read.size() == 4);

  for (size_t i = 0; i < 4; i++) {
    ASSERT_TRUE(raw_data[i] == read[i]);
  }

  ASSERT_TRUE(ValidateData(raw_data, sizeof(raw_data)));
  ASSERT_TRUE(ValidateReader(reader, raw_data, sizeof(raw_data), 4));
}

TEST_F(BufferReaderTest, ReadVectorTooLarge) {
  uint8_t raw_data[16];
  PopulateData(raw_data, sizeof(raw_data));

  BufferReader reader(raw_data, sizeof(raw_data));

  std::vector<uint8_t> read;

  ASSERT_FALSE(reader.ReadVec(&read, sizeof(raw_data) * 2));

  ASSERT_TRUE(0 == read.size());
  ASSERT_TRUE(ValidateData(raw_data, sizeof(raw_data)));
  ASSERT_TRUE(ValidateReader(reader, raw_data, sizeof(raw_data), 0));
}

TEST_F(BufferReaderTest, ReadVectorNullSource) {
  BufferReader reader(NULL, 16);

  std::vector<uint8_t> read;
  ASSERT_FALSE(reader.ReadVec(&read, 4));

  ASSERT_TRUE(0 == read.size());
  ASSERT_TRUE(ValidateReader(reader, NULL, 0, 0));
}

TEST_F(BufferReaderTest, ReadVectorNullReturn) {
  uint8_t raw_data[16];
  PopulateData(raw_data, sizeof(raw_data));

  BufferReader reader(raw_data, sizeof(raw_data));

  ASSERT_FALSE(reader.ReadVec(NULL, 4));

  ASSERT_TRUE(ValidateData(raw_data, sizeof(raw_data)));
  ASSERT_TRUE(ValidateReader(reader, raw_data, sizeof(raw_data), 0));
}

TEST_F(BufferReaderTest, ReadVectorNone) {
  uint8_t raw_data[16];
  PopulateData(raw_data, sizeof(raw_data));

  BufferReader reader(raw_data, sizeof(raw_data));

  std::vector<uint8_t> read;
  ASSERT_TRUE(reader.ReadVec(&read, 0));

  ASSERT_TRUE(0 == read.size());
  ASSERT_TRUE(ValidateData(raw_data, sizeof(raw_data)));
  ASSERT_TRUE(ValidateReader(reader, raw_data, sizeof(raw_data), 0));
}

TEST_F(BufferReaderTest, Read4Into84Bytes) {
  ASSERT_TRUE(CheckRead4Into8(0xFFFFFF));
}

TEST_F(BufferReaderTest, Read4Into83Bytes) {
  ASSERT_TRUE(CheckRead4Into8(0xFFFF));
}

TEST_F(BufferReaderTest, Read4Into82Bytes) {
  ASSERT_TRUE(CheckRead4Into8(0xFF));
}

TEST_F(BufferReaderTest, Read4Into8Zero) { ASSERT_TRUE(CheckRead4Into8(0)); }

TEST_F(BufferReaderTest, Read4Into8NullSource) {
  BufferReader reader(NULL, 4);

  uint64_t read;
  ASSERT_FALSE(reader.Read4Into8(&read));

  ASSERT_TRUE(ValidateReader(reader, NULL, 0, 0));
}

TEST_F(BufferReaderTest, Read4Into8TooLittleData) {
  uint8_t raw_data[2];
  PopulateData(raw_data, sizeof(raw_data));

  BufferReader reader(raw_data, sizeof(raw_data));

  uint64_t read;
  ASSERT_FALSE(reader.Read4Into8(&read));

  ASSERT_TRUE(ValidateData(raw_data, sizeof(raw_data)));
  ASSERT_TRUE(ValidateReader(reader, raw_data, sizeof(raw_data), 0));
}

TEST_F(BufferReaderTest, Read4Into8NoReturn) {
  uint8_t raw_data[16];
  PopulateData(raw_data, sizeof(raw_data));

  BufferReader reader(raw_data, sizeof(raw_data));

  ASSERT_FALSE(reader.Read4Into8(NULL));

  ASSERT_TRUE(ValidateData(raw_data, sizeof(raw_data)));
  ASSERT_TRUE(ValidateReader(reader, raw_data, sizeof(raw_data), 0));
}

TEST_F(BufferReaderTest, Read4sInto8s4Bytes) {
  ASSERT_TRUE(CheckRead4sInto8s(0x0FFFFFFF));
}

TEST_F(BufferReaderTest, Read4sInto8s3Bytes) {
  ASSERT_TRUE(CheckRead4sInto8s(0xFFFFFF));
}

TEST_F(BufferReaderTest, Read4sInto8s2Bytes) {
  ASSERT_TRUE(CheckRead4sInto8s(0xFFFF));
}

TEST_F(BufferReaderTest, Read4sInto8s1Bytes) {
  ASSERT_TRUE(CheckRead4sInto8s(0xFF));
}

TEST_F(BufferReaderTest, Read4sInto8sZero) {
  ASSERT_TRUE(CheckRead4sInto8s(0));
}

TEST_F(BufferReaderTest, Read4sInto8sNegative) {
  ASSERT_TRUE(CheckRead4sInto8s(-100));
}

TEST_F(BufferReaderTest, Read4sInto8sNullSource) {
  BufferReader reader(NULL, 4);

  int64_t read;
  ASSERT_FALSE(reader.Read4sInto8s(&read));

  ASSERT_TRUE(ValidateReader(reader, NULL, 0, 0));
}

TEST_F(BufferReaderTest, Read4sInto8sTooLittleData) {
  uint8_t raw_data[2];
  PopulateData(raw_data, sizeof(raw_data));

  BufferReader reader(raw_data, sizeof(raw_data));

  int64_t read;
  ASSERT_FALSE(reader.Read4sInto8s(&read));

  ASSERT_TRUE(ValidateData(raw_data, sizeof(raw_data)));
  ASSERT_TRUE(ValidateReader(reader, raw_data, sizeof(raw_data), 0));
}

TEST_F(BufferReaderTest, Read4sInto8sNoReturn) {
  uint8_t raw_data[16];
  PopulateData(raw_data, sizeof(raw_data));

  BufferReader reader(raw_data, sizeof(raw_data));

  ASSERT_FALSE(reader.Read4sInto8s(NULL));

  ASSERT_TRUE(ValidateData(raw_data, sizeof(raw_data)));
  ASSERT_TRUE(ValidateReader(reader, raw_data, sizeof(raw_data), 0));
}

TEST_F(BufferReaderTest, SkipBytesNone) {
  uint8_t raw_data[16];
  PopulateData(raw_data, sizeof(raw_data));

  BufferReader reader(raw_data, sizeof(raw_data));

  ASSERT_TRUE(reader.SkipBytes(0));
  ASSERT_TRUE(ValidateData(raw_data, sizeof(raw_data)));
  ASSERT_TRUE(ValidateReader(reader, raw_data, sizeof(raw_data), 0));
}

TEST_F(BufferReaderTest, SkipBytes) {
  uint8_t raw_data[16];
  PopulateData(raw_data, sizeof(raw_data));

  BufferReader reader(raw_data, sizeof(raw_data));

  ASSERT_TRUE(reader.SkipBytes(4));
  ASSERT_TRUE(ValidateData(raw_data, sizeof(raw_data)));
  ASSERT_TRUE(ValidateReader(reader, raw_data, sizeof(raw_data), 4));
}

TEST_F(BufferReaderTest, SkipBytesTooLarge) {
  uint8_t raw_data[16];
  PopulateData(raw_data, sizeof(raw_data));

  BufferReader reader(raw_data, sizeof(raw_data));

  ASSERT_FALSE(reader.SkipBytes(sizeof(raw_data) * 2));

  ASSERT_TRUE(ValidateData(raw_data, sizeof(raw_data)));
  ASSERT_TRUE(ValidateReader(reader, raw_data, sizeof(raw_data), 0));
}
}  // namespace
