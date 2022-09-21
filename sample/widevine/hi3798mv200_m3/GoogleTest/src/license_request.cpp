// Copyright 2013 Google Inc. All Rights Reserved.

#include "license_request.h"
#include "log.h"

namespace wvcdm {

namespace {
const std::string kTwoBlankLines("\r\n\r\n");
}  // namespace

size_t LicenseRequest::FindHeaderEndPosition(
    const std::string& response) const {
  return response.find(kTwoBlankLines);
}

// This routine parses the license server's response message and
// extracts the drm message from the response header.
void LicenseRequest::GetDrmMessage(const std::string& response,
                                   std::string& drm_msg) {
  if (response.empty()) {
    drm_msg.clear();
    return;
  }

  // Extracts DRM message.
  // Content-Length = GLS line + Header(s) + empty line + drm message;
  // we use the empty line to locate the drm message, and compute
  // the drm message length as below instead of using Content-Length
  size_t header_end_pos = FindHeaderEndPosition(response);
  if (header_end_pos != std::string::npos) {
    header_end_pos += kTwoBlankLines.size();  // points to response body

    drm_msg.clear();
    // Messages from Google Play server add a GLS wrapper.  These start
    // with "GLS/1.0 <status>".
    if (response.find("GLS/1.", header_end_pos) == header_end_pos) {
      // For GLS messages, we should skip past the next blank line, and use
      // what's left of the message.
      size_t drm_msg_pos = response.find(kTwoBlankLines, header_end_pos);
      if (drm_msg_pos != std::string::npos) {
        drm_msg_pos += kTwoBlankLines.size();  // points to drm message
        drm_msg = response.substr(drm_msg_pos);
      } else {
        LOGE("Message had GLS marker, but did not have extra blank line.");
        drm_msg = response.substr(header_end_pos);
      }
    } else {
      // For servers that do not use the GLS wrapper, we should just strip of
      // the headers, and use the rest of the message.
      drm_msg = response.substr(header_end_pos);
    }
  } else {
    LOGE("response body not found");
  }
}

}  // namespace wvcdm
