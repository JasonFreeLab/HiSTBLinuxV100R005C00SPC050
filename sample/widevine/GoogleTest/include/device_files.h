// Copyright 2013 Google Inc. All Rights Reserved.
//
#ifndef WVCDM_CORE_DEVICE_FILES_H_
#define WVCDM_CORE_DEVICE_FILES_H_

#include <unistd.h>

#include <set>
#include <string>

#include "device_files.pb.h"
#include "scoped_ptr.h"
#include "wv_cdm_types.h"

#if defined(UNIT_TEST)
#include <gtest/gtest_prod.h>
#endif

namespace wvcdm {

class FileSystem;

class DeviceFiles {
 public:
  typedef enum {
    kLicenseStateActive,
    kLicenseStateReleasing,
    kLicenseStateUnknown,
  } LicenseState;

  DeviceFiles(FileSystem*);
  virtual ~DeviceFiles();

  virtual bool Init(CdmSecurityLevel security_level);
  virtual bool Reset(CdmSecurityLevel security_level) {
    return Init(security_level);
  }

  virtual bool StoreCertificate(const std::string& certificate,
                                const std::string& wrapped_private_key);
  virtual bool RetrieveCertificate(std::string* certificate,
                                   std::string* wrapped_private_key);
  virtual bool HasCertificate();
  virtual bool RemoveCertificate();

  virtual bool StoreLicense(const std::string& key_set_id,
                            const LicenseState state,
                            const CdmInitData& pssh_data,
                            const CdmKeyMessage& key_request,
                            const CdmKeyResponse& key_response,
                            const CdmKeyMessage& key_renewal_request,
                            const CdmKeyResponse& key_renewal_response,
                            const std::string& release_server_url,
                            int64_t playback_start_time,
                            int64_t last_playback_time,
                            const CdmAppParameterMap& app_parameters);
  virtual bool RetrieveLicense(
      const std::string& key_set_id, LicenseState* state,
      CdmInitData* pssh_data, CdmKeyMessage* key_request,
      CdmKeyResponse* key_response, CdmKeyMessage* key_renewal_request,
      CdmKeyResponse* key_renewal_response, std::string* release_server_url,
      int64_t* playback_start_time, int64_t* last_playback_time,
      CdmAppParameterMap* app_parameters);
  virtual bool DeleteLicense(const std::string& key_set_id);
  virtual bool DeleteAllFiles();
  virtual bool DeleteAllLicenses();
  virtual bool LicenseExists(const std::string& key_set_id);
  virtual bool ReserveLicenseId(const std::string& key_set_id);
  virtual bool UnreserveLicenseId(const std::string& key_set_id);

  virtual bool StoreUsageInfo(const std::string& provider_session_token,
                              const CdmKeyMessage& key_request,
                              const CdmKeyResponse& key_response,
                              const std::string& app_id,
                              const std::string& key_set_id);
  virtual bool DeleteUsageInfo(const std::string& app_id,
                               const std::string& provider_session_token);
  // Delete usage information from the file system.  Puts a list of all the
  // psts that were deleted from the file into |provider_session_tokens|.
  virtual bool DeleteAllUsageInfoForApp(
      const std::string& app_id,
      std::vector<std::string>* provider_session_tokens);
  // Retrieve one usage info from the file.  Subsequent calls will retrieve
  // subsequent entries in the table for this app_id.
  virtual bool RetrieveUsageInfo(
      const std::string& app_id,
      std::vector<std::pair<CdmKeyMessage, CdmKeyResponse> >* usage_info);
  // Retrieve the usage info entry specified by |provider_session_token|.
  // Returns false if the entry could not be found.
  virtual bool RetrieveUsageInfo(const std::string& app_id,
                                 const std::string& provider_session_token,
                                 CdmKeyMessage* license_request,
                                 CdmKeyResponse* license_response);
  // Retrieve the usage info entry specified by |key_set_id|.
  // Returns false if the entry could not be found.
  virtual bool RetrieveUsageInfoByKeySetId(const std::string& app_id,
                                           const std::string& key_set_id,
                                           CdmKeyMessage* license_request,
                                           CdmKeyResponse* license_response);

  virtual bool StoreHlsAttributes(const std::string& key_set_id,
                                  const CdmHlsMethod method,
                                  const std::vector<uint8_t>& media_segment_iv);
  virtual bool RetrieveHlsAttributes(const std::string& key_set_id,
                                     CdmHlsMethod* method,
                                     std::vector<uint8_t>* media_segment_iv);
  virtual bool DeleteHlsAttributes(const std::string& key_set_id);
 private:
  // Helpers that wrap the File interface and automatically handle hashing, as
  // well as adding the device files base path to to the file name.
  bool StoreFileWithHash(const std::string& name,
                         const std::string& serialized_file);
  bool StoreFileRaw(const std::string& name,
                    const std::string& serialized_file);
  bool RetrieveHashedFile(const std::string& name,
                          video_widevine_client::sdk::File* file);
  bool FileExists(const std::string& name);
  bool RemoveFile(const std::string& name);
  ssize_t GetFileSize(const std::string& name);

  static std::string GetCertificateFileName();
  static std::string GetHlsAttributesFileNameExtension();
  static std::string GetLicenseFileNameExtension();
  static std::string GetUsageInfoFileName(const std::string& app_id);
  static std::string GetFileNameSafeHash(const std::string& input);

#if defined(UNIT_TEST)
  FRIEND_TEST(DeviceFilesSecurityLevelTest, SecurityLevel);
  FRIEND_TEST(DeviceCertificateStoreTest, StoreCertificate);
  FRIEND_TEST(DeviceCertificateTest, ReadCertificate);
  FRIEND_TEST(DeviceCertificateTest, HasCertificate);
  FRIEND_TEST(DeviceFilesStoreTest, StoreLicense);
  FRIEND_TEST(DeviceFilesHlsAttributesTest, Delete);
  FRIEND_TEST(DeviceFilesHlsAttributesTest, Read);
  FRIEND_TEST(DeviceFilesHlsAttributesTest, Store);
  FRIEND_TEST(DeviceFilesTest, DeleteLicense);
  FRIEND_TEST(DeviceFilesTest, ReserveLicenseIdsDoesNotUseFileSystem);
  FRIEND_TEST(DeviceFilesTest, RetrieveLicenses);
  FRIEND_TEST(DeviceFilesTest, AppParametersBackwardCompatibility);
  FRIEND_TEST(DeviceFilesTest, StoreLicenses);
  FRIEND_TEST(DeviceFilesTest, UpdateLicenseState);
  FRIEND_TEST(DeviceFilesUsageInfoTest, Delete);
  FRIEND_TEST(DeviceFilesUsageInfoTest, DeleteAll);
  FRIEND_TEST(DeviceFilesUsageInfoTest, Read);
  FRIEND_TEST(DeviceFilesUsageInfoTest, Store);
  FRIEND_TEST(WvCdmRequestLicenseTest, UnprovisionTest);
  FRIEND_TEST(WvCdmRequestLicenseTest, ForceL3Test);
  FRIEND_TEST(WvCdmRequestLicenseTest, UsageInfoRetryTest);
  FRIEND_TEST(WvCdmRequestLicenseTest, UsageReleaseAllTest);
  FRIEND_TEST(WvCdmUsageInfoTest, UsageInfo);
  FRIEND_TEST(WvCdmUsageTest, WithClientId);
  FRIEND_TEST(WvCdmExtendedDurationTest, UsageOverflowTest);
#endif

  static std::set<std::string> reserved_license_ids_;

  FileSystem* file_system_;
  CdmSecurityLevel security_level_;
  bool initialized_;

  CORE_DISALLOW_COPY_AND_ASSIGN(DeviceFiles);
};

}  // namespace wvcdm

#endif  // WVCDM_CORE_DEVICE_FILES_H_
