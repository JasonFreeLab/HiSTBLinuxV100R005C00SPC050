#ifndef STRING_CONVERSIONS_H_
#define STRING_CONVERSIONS_H_

#include <stddef.h>
#include <stdint.h>
#include <string>
#include <vector>

namespace drmengine{

std::vector<uint8_t> a2b_hex(const std::string& b);
std::vector<uint8_t> a2b_hex(const std::string& label, const std::string& b);
std::string a2bs_hex(const std::string& b);
std::string b2a_hex(const std::vector<uint8_t>& b);
std::string b2a_hex(const std::string& b);
std::string HexEncode(const uint8_t* bytes, unsigned size);
std::string IntToString(int value);
int64_t htonll64(int64_t x);
inline int64_t ntohll64(int64_t x) { return htonll64(x); }

}  // namespace wvcdm

#endif