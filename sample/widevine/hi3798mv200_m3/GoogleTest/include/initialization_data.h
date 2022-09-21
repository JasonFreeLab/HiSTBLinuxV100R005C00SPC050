// Copyright 2014 Google Inc. All Rights Reserved.

#ifndef CORE_INCLUDE_INITIALIZATION_DATA_H_
#define CORE_INCLUDE_INITIALIZATION_DATA_H_

#include <string>

#include "wv_cdm_types.h"

namespace wvcdm {

class WvCdmEngineTest;

class InitializationData {
 public:
  InitializationData(const std::string& type = std::string(),
                     const CdmInitData& data = CdmInitData());

  bool is_supported() const { return is_cenc_ || is_webm_ || is_hls_; }
  bool is_cenc() const { return is_cenc_; }
  bool is_hls() const { return is_hls_; }
  bool is_webm() const { return is_webm_; }

  bool IsEmpty() const { return data_.empty(); }

  const std::string& type() const { return type_; }
  const CdmInitData& data() const { return data_; }
  std::vector<uint8_t> hls_iv() const { return hls_iv_; }
  CdmHlsMethod hls_method() const { return hls_method_; }

 private:
  // Parse a blob of multiple concatenated PSSH atoms to extract the first
  // Widevine PSSH.
  bool ExtractWidevinePssh(const CdmInitData& init_data, CdmInitData* output);

  bool ExtractHlsAttributes(const std::string& attribute_list,
                            CdmHlsMethod* method, std::vector<uint8_t>* iv,
                            std::string* uri);
  static bool ConstructWidevineInitData(CdmHlsMethod method,
                                        const std::string& uri,
                                        CdmInitData* output);
  static bool ExtractQuotedAttribute(const std::string& attribute_list,
                                     const std::string& key,
                                     std::string* value);
  static bool ExtractHexAttribute(const std::string& attribute_list,
                                  const std::string& key,
                                  std::vector<uint8_t>* value);
  static bool ExtractAttribute(const std::string& attribute_list,
                               const std::string& key, std::string* value);

  static std::vector<std::string> ExtractKeyFormatVersions(
      const std::string& key_format_versions);

// For testing only:
#if defined(UNIT_TEST)
  FRIEND_TEST(HlsAttributeExtractionTest, ExtractAttribute);
  FRIEND_TEST(HlsConstructionTest, InitData);
  FRIEND_TEST(HlsInitDataConstructionTest, InvalidUriDataFormat);
  FRIEND_TEST(HlsInitDataConstructionTest, InvalidUriBase64Encode);
  FRIEND_TEST(HlsHexAttributeExtractionTest, ExtractHexAttribute);
  FRIEND_TEST(HlsKeyFormatVersionsExtractionTest, ExtractKeyFormatVersions);
  FRIEND_TEST(HlsParseTest, Parse);
  FRIEND_TEST(HlsQuotedAttributeExtractionTest, ExtractQuotedAttribute);
  FRIEND_TEST(HlsTest, ExtractHlsAttributes);
#endif

  std::string type_;
  CdmInitData data_;
  bool is_cenc_;
  bool is_hls_;
  bool is_webm_;

  std::vector<uint8_t> hls_iv_;
  CdmHlsMethod hls_method_;
};

}  // namespace wvcdm

#endif  // CORE_INCLUDE_INITIALIZATION_DATA_H_
