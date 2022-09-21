// Copyright 2013 Google Inc. All Rights Reserved.

#ifndef CDM_TEST_HTTP_SOCKET_H_
#define CDM_TEST_HTTP_SOCKET_H_

#include <stdlib.h>

#include <string>

#include <gtest/gtest_prod.h>
#include <openssl/ssl.h>

#include "wv_cdm_types.h"  // CORE_DISALLOW_COPY_AND_ASSIGN

namespace wvcdm {

// Provides basic Linux based TCP socket interface.
class HttpSocket {
 public:
  // A scheme (http:// or https://) is required for the URL.
  explicit HttpSocket(const std::string& url);
  ~HttpSocket();

  bool Connect(int timeout_in_ms);
  void CloseSocket();

  const std::string& scheme() const { return scheme_; }
  bool secure_connect() const { return secure_connect_; }
  const std::string& domain_name() const { return domain_name_; }
  int port() const { return atoi(port_.c_str()); }
  const std::string& resource_path() const { return resource_path_; }

  int Read(char* data, int len, int timeout_in_ms);
  int Write(const char* data, int len, int timeout_in_ms);

 private:
  static bool ParseUrl(const std::string& url, std::string* scheme,
                       bool* secure_connect, std::string* domain_name,
                       std::string* port, std::string* path);
  FRIEND_TEST(HttpSocketTest, ParseUrlTest);

  std::string scheme_;
  bool secure_connect_;
  std::string domain_name_;
  std::string port_;
  std::string resource_path_;
  bool valid_url_;

  int socket_fd_;
  SSL* ssl_;
  SSL_CTX* ssl_ctx_;

  CORE_DISALLOW_COPY_AND_ASSIGN(HttpSocket);
};

}  // namespace wvcdm

#endif  // CDM_TEST_HTTP_SOCKET_H_
