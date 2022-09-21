// Copyright 2013 Google Inc. All Rights Reserved.

#include "string_conversions.h"
#include "WVLog.h"

#include <arpa/inet.h>
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>

namespace drmengine{

static bool CharToDigit(char ch, unsigned char* digit) {
  if (ch >= '0' && ch <= '9') {
    *digit = ch - '0';
  } else {
    ch = tolower(ch);
    if ((ch >= 'a') && (ch <= 'f')) {
      *digit = ch - 'a' + 10;
    } else {
      return false;
    }
  }
  return true;
}

// converts an ascii hex string(2 bytes per digit) into a decimal byte string
std::vector<uint8_t> a2b_hex(const std::string& byte) {
  std::vector<uint8_t> array;
  unsigned int count = byte.size();
  if (count == 0 || (count % 2) != 0) {
    LOGE_DRM("Invalid input size %u for string %s", count, byte.c_str());
    return array;
  }

  for (unsigned int i = 0; i < count / 2; ++i) {
    unsigned char msb = 0;  // most significant 4 bits
    unsigned char lsb = 0;  // least significant 4 bits
    if (!CharToDigit(byte[i * 2], &msb) ||
        !CharToDigit(byte[i * 2 + 1], &lsb)) {
      LOGE_DRM("Invalid hex value %c%c at index %d", byte[i * 2], byte[i * 2 + 1],
           i);
      return array;
    }
    array.push_back((msb << 4) | lsb);
  }
  return array;
}

// converts an ascii hex string(2 bytes per digit) into a decimal byte string
// dump the string with the label.
std::vector<uint8_t> a2b_hex(const std::string& label,
                             const std::string& byte) {
  std::cout << std::endl
            << "[[DUMP: " << label << " ]= \"" << byte << "\"]" << std::endl
            << std::endl;

  return a2b_hex(byte);
}

std::string a2bs_hex(const std::string& byte) {
  std::vector<uint8_t> array = a2b_hex(byte);
  return std::string(array.begin(), array.end());
}

std::string b2a_hex(const std::vector<uint8_t>& byte) {
  return HexEncode(&byte[0], byte.size());
}

std::string b2a_hex(const std::string& byte) {
  return HexEncode(reinterpret_cast<const uint8_t*>(byte.data()),
                   byte.length());
}

std::string HexEncode(const uint8_t* in_buffer, unsigned int size) {
  static const char kHexChars[] = "0123456789ABCDEF";

  // Each input byte creates two output hex characters.
  std::string out_buffer(size * 2, '\0');

  for (unsigned int i = 0; i < size; ++i) {
    char byte = in_buffer[i];
    out_buffer[(i << 1)] = kHexChars[(byte >> 4) & 0xf];
    out_buffer[(i << 1) + 1] = kHexChars[byte & 0xf];
  }
  return out_buffer;
}

std::string IntToString(int value) {
  // log10(2) ~= 0.3 bytes needed per bit or per byte log10(2**8) ~= 2.4.
  // So round up to allocate 3 output characters per byte, plus 1 for '-'.
  const int kOutputBufSize = 3 * sizeof(int) + 1;
  char buffer[kOutputBufSize];
  memset(buffer, 0, kOutputBufSize);
  snprintf(buffer, kOutputBufSize, "%d", value);

  std::string out_string(buffer);
  return out_string;
}

int64_t htonll64(int64_t x) {  // Convert to big endian (network-byte-order)
  union {
    uint32_t array[2];
    int64_t number;
  } mixed;
  mixed.number = 1;
  if (mixed.array[0] == 1) {  // Little Endian.
    mixed.number = x;
    uint32_t temp = mixed.array[0];
    mixed.array[0] = htonl(mixed.array[1]);
    mixed.array[1] = htonl(temp);
    return mixed.number;
  } else {  // Big Endian.
    return x;
  }
}

}  // namespace wvcdm

