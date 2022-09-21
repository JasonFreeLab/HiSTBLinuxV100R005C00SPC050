// Copyright 2013 Google Inc. All Rights Reserved.

#include <errno.h>
#include <gtest/gtest.h>
#include "http_socket.h"
#include "log.h"
#include "scoped_ptr.h"
#include "string_conversions.h"
#include "url_request.h"

namespace wvcdm {

namespace {
// Arbitrary URL for tests.
const std::string kHttpsTestServer("https://www.google.com");
const std::string kHttpTestServer("http://www.google.com");
// This URL and data are used by RoundTripTest, and can be overridden on the
// command line.
std::string gTestServer(kHttpsTestServer);
std::string gTestData("Hello");
// Arbitrary buffer size and timeout settings.
const int kHttpBufferSize = 4096;
const int kTimeout = 3000;
}

class HttpSocketTest : public testing::Test {
 public:
  HttpSocketTest() {}
  ~HttpSocketTest() {}

 protected:
  bool Connect(const std::string& server_url) {
    socket_.reset(new HttpSocket(server_url));

    if (socket_->Connect(kTimeout)) {
      LOGD("connected to %s", socket_->domain_name().c_str());
      return true;
    } else {
      LOGE("failed to connect to %s", server_url.c_str());
      return false;
    }
  }

  bool PostRequest(const std::string& data) {
    std::string request("POST ");
    request.append(socket_->resource_path());
    request.append(" HTTP/1.1\r\n");

    request.append("Host: ");
    request.append(socket_->domain_name());
    request.append("\r\n");

    // Important!  Otherwise, the HTTP 1.1 default behavior for a server is to
    // keep the connection open for a subsequent request.
    request.append("Connection: close\r\n");

    request.append("User-Agent: httpSocketTest/1.0\r\n");

    char buffer[32] = {0};
    snprintf(buffer, sizeof(buffer), "%d", static_cast<int>(data.size()));
    request.append("Content-Length: ");
    request.append(buffer);
    request.append("\r\n");

    request.append("Content-Type: multipart/form-data\r\n");

    // an extra newline terminates HTTP headers.
    request.append("\r\n");

    // append data
    request.append(data);
    socket_->Write(request.c_str(), request.size(), kTimeout);

    LOGD("request: %s", request.c_str());
    return true;
  }

  bool GetResponse(std::string* response) {
    char buffer[kHttpBufferSize];
    int bytes = socket_->Read(buffer, sizeof(buffer), kTimeout);
    if (bytes < 0) {
      LOGE("read error, errno = %d", errno);
      return false;
    }

    LOGD("read %d bytes", bytes);
    response->assign(buffer, bytes);
    return true;
  }

  scoped_ptr<HttpSocket> socket_;
  std::string domain_name_;
  std::string resource_path_;
};

struct ParseUrlTests {
  const char* url;
  const char* scheme;
  bool secure_connect;
  const char* domain_name;
  const char* port;
  const char* path;
};

ParseUrlTests parse_url_tests[] = {
    {
     "https://code.google.com/p/googletest/wiki/Primer",  // url
     "https",                                             // scheme
     true,                                                // secure_connect
     "code.google.com",                                   // domain_name
     "443",                                               // port
     "/p/googletest/wiki/Primer",                         // path
    },
    {
     "http://code.google.com/p/googletest/wiki/Primer/",  // url
     "http",                                              // scheme
     false,                                               // secure_connect
     "code.google.com",                                   // domain_name
     "80",                                                // port
     "/p/googletest/wiki/Primer/",                        // path
    },
    {
     "http://code.google.com/",  // url
     "http",                     // scheme
     false,                      // secure_connect
     "code.google.com",          // domain_name
     "80",                       // port
     "/",                        // path
    },
    {
     "http://code.google.com",  // url
     "http",                    // scheme
     false,                     // secure_connect
     "code.google.com",         // domain_name
     "80",                      // port
     "/",                       // path
    },
    {
     "http://10.11.12.13:8888/drm",  // url
     "http",                         // scheme
     false,                          // secure_connect
     "10.11.12.13",                  // domain_name
     "8888",                         // port
     "/drm",                         // path
    },
    {
     "http://10.11.12.13:8888",  // url
     "http",                     // scheme
     false,                      // secure_connect
     "10.11.12.13",              // domain_name
     "8888",                     // port
     "/",                        // path
    },
    {
     "https://10.11.12.13:8888",  // url
     "https",                     // scheme
     true,                        // secure_connect
     "10.11.12.13",               // domain_name
     "8888",                      // port
     "/",                         // path
    },
    {NULL, NULL, false, NULL, 0, NULL}  // list terminator
};

TEST_F(HttpSocketTest, ParseUrlTest) {
  std::string scheme;
  bool secure_connect;
  std::string domain_name;
  std::string port;
  std::string path;
  ParseUrlTests* test = NULL;

  for (test = &parse_url_tests[0]; test->url != NULL; ++test) {
    bool ok = HttpSocket::ParseUrl(test->url, &scheme, &secure_connect,
                                   &domain_name, &port, &path);
    EXPECT_TRUE(ok);
    if (ok) {
      EXPECT_EQ(test->scheme, scheme);
      EXPECT_EQ(test->secure_connect, secure_connect);
      EXPECT_EQ(test->domain_name, domain_name);
      EXPECT_EQ(test->port, port);
      EXPECT_EQ(test->path, path);
    }
  }
}

TEST_F(HttpSocketTest, ConnectTest) {
  EXPECT_TRUE(Connect(kHttpsTestServer));
  EXPECT_TRUE(Connect(kHttpTestServer));
  EXPECT_FALSE(Connect("ww.g.c"));
  EXPECT_FALSE(Connect("http://ww.g.c"));
  EXPECT_FALSE(Connect("https://ww.g.c"));
}

TEST_F(HttpSocketTest, RoundTripTest) {
  ASSERT_TRUE(Connect(gTestServer));
  EXPECT_TRUE(PostRequest(gTestData));

  std::string response;
  EXPECT_TRUE(GetResponse(&response));
  LOGD("response: %s", response.c_str());
}

}  // namespace wvcdm

int main(int argc, char** argv) {
  using namespace wvcdm;

  ::testing::InitGoogleTest(&argc, argv);

  std::string temp;
  std::string test_server(kHttpsTestServer);
  std::string test_data(gTestData);
  for (int i = 1; i < argc; i++) {
    temp.assign(argv[i]);
    if (temp.find("--server=") == 0) {
      gTestServer.assign(temp.substr(strlen("--server=")));
    } else if (temp.find("--data=") == 0) {
      gTestData.assign(temp.substr(strlen("--data=")));
    } else {
      std::cout << "error: unknown option '" << argv[i] << "'" << std::endl;
      std::cout << "usage: http_socket_test [options]" << std::endl
                << std::endl;
      std::cout << std::setw(30) << std::left << "    --server=<server_url>";
      std::cout
          << "configure the test server url, please include http[s] in the url"
          << std::endl;
      std::cout << std::setw(30) << std::left << " ";
      std::cout << "default: " << test_server << std::endl;
      std::cout << std::setw(30) << std::left << "    --data=<data>";
      std::cout << "configure data to send, in ascii string format"
                << std::endl;
      std::cout << std::setw(30) << std::left << " ";
      std::cout << "default: " << test_data << std::endl << std::endl;
      return 0;
    }
  }

  std::cout << std::endl;
  std::cout << "Server: " << gTestServer << std::endl;
  std::cout << "Data: " << gTestData << std::endl;

  return RUN_ALL_TESTS();
}
