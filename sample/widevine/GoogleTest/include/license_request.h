// Copyright 2013 Google Inc. All Rights Reserved.

#ifndef CDM_TEST_LICENSE_REQUEST_H_
#define CDM_TEST_LICENSE_REQUEST_H_

#include <string>
#include "wv_cdm_types.h"

namespace wvcdm {

// Parses response from a license request.
// This class assumes a particular response format defined by
// Google license servers.
class LicenseRequest {
 public:
  LicenseRequest() {};
  ~LicenseRequest() {};

  void GetDrmMessage(const std::string& response, std::string& drm_msg);

 private:
  size_t FindHeaderEndPosition(const std::string& response) const;

  CORE_DISALLOW_COPY_AND_ASSIGN(LicenseRequest);
};

}  // namespace wvcdm

#endif  // CDM_TEST_LICENSE_REQUEST_H_
