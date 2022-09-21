// Copyright 2013 Google Inc. All Rights Reserved.

#ifndef CDM_TEST_URL_REQUEST_H_
#define CDM_TEST_URL_REQUEST_H_

#include <string>
#include "http_socket.h"
#include "wv_cdm_types.h"

namespace wvcdm {

// Provides simple HTTP request and response service.
// Only POST request method is implemented.
class UrlRequest {
 public:
  explicit UrlRequest(const std::string& url);
  ~UrlRequest();

  bool is_connected() const { return is_connected_; }
  void Reconnect();

  bool PostRequest(const std::string& data);
  bool PostCertRequestInQueryString(const std::string& data);

  bool GetResponse(std::string* message);
  static int GetStatusCode(const std::string& response);

 private:
  bool PostRequestWithPath(const std::string& path, const std::string& data);

  bool is_connected_;
  HttpSocket socket_;

  CORE_DISALLOW_COPY_AND_ASSIGN(UrlRequest);
};

}  // namespace wvcdm

#endif  // CDM_TEST_URL_REQUEST_H_
