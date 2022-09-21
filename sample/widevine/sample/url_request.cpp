// Copyright 2013 Google Inc. All Rights Reserved.

#include "url_request.h"

#include <errno.h>
#include <sstream>

#include "http_socket.h"
#include "log.h"
#include "string_conversions.h"

namespace wvcdm {

namespace {

const int kReadBufferSize = 1024;
const int kConnectTimeoutMs = 15000;
const int kWriteTimeoutMs = 12000;
const int kReadTimeoutMs = 12000;

// Concatenate all chunks into one blob and returns the response with
// header information.
void ConcatenateChunkedResponse(const std::string http_response,
                                std::string* modified_response) {
  if (http_response.empty()) return;

  modified_response->clear();
  const std::string kChunkedTag = "Transfer-Encoding: chunked\r\n\r\n";
  size_t chunked_tag_pos = http_response.find(kChunkedTag);
  if (std::string::npos != chunked_tag_pos) {
    // processes chunked encoding
    size_t chunk_size = 0;
    size_t chunk_size_pos = chunked_tag_pos + kChunkedTag.size();
    sscanf(&http_response[chunk_size_pos], "%zx", &chunk_size);
    if (chunk_size > http_response.size()) {
      // precaution, in case we misread chunk size
      LOGE("invalid chunk size %u", chunk_size);
      return;
    }

    // Search for chunks in the following format:
    // header
    // chunk size\r\n  <-- chunk_size_pos @ beginning of chunk size
    // chunk data\r\n  <-- chunk_pos @ beginning of chunk data
    // chunk size\r\n
    // chunk data\r\n
    // 0\r\n
    const std::string kCrLf = "\r\n";
    size_t chunk_pos = http_response.find(kCrLf, chunk_size_pos);
    modified_response->assign(http_response, 0, chunk_size_pos);

    while ((chunk_size > 0) && (std::string::npos != chunk_pos)) {
      chunk_pos += kCrLf.size();
      modified_response->append(http_response, chunk_pos, chunk_size);

      // Search for next chunk
      chunk_size_pos = chunk_pos + chunk_size + kCrLf.size();
      sscanf(&http_response[chunk_size_pos], "%zx", &chunk_size);
      if (chunk_size > http_response.size()) {
        // precaution, in case we misread chunk size
        LOGE("invalid chunk size %u", chunk_size);
        break;
      }
      chunk_pos = http_response.find(kCrLf, chunk_size_pos);
    }
  } else {
    // Response is not chunked encoded
    modified_response->assign(http_response);
  }
}

}  // namespace

UrlRequest::UrlRequest(const std::string& url)
    : is_connected_(false), socket_(url) {
  Reconnect();
}

UrlRequest::~UrlRequest() {}

void UrlRequest::Reconnect() {
  socket_.CloseSocket();
  if (socket_.Connect(kConnectTimeoutMs)) {
    is_connected_ = true;
  } else {
    LOGE("failed to connect to %s, port=%d", socket_.domain_name().c_str(),
         socket_.port());
  }
}

bool UrlRequest::GetResponse(std::string* message) {
  std::string response;

  // Keep reading until end of stream (0 bytes read) or timeout.  Partial
  // buffers worth of data can and do happen, especially with OpenSSL in
  // non-blocking mode.
  while (true) {
    char read_buffer[kReadBufferSize];
    int bytes = socket_.Read(read_buffer, sizeof(read_buffer), kReadTimeoutMs);
    if (bytes > 0) {
      response.append(read_buffer, bytes);
    } else if (bytes < 0) {
      LOGE("read error, errno = %d", errno);
      return false;
    } else {
      // end of stream.
      break;
    }
  }

  ConcatenateChunkedResponse(response, message);
  LOGV("HTTP response: (%d): %s", message->size(), b2a_hex(*message).c_str());
  return true;
}

// static
int UrlRequest::GetStatusCode(const std::string& response) {
  const std::string kHttpVersion("HTTP/1.1 ");

  int status_code = -1;
  size_t pos = response.find(kHttpVersion);
  if (pos != std::string::npos) {
    pos += kHttpVersion.size();
    sscanf(response.substr(pos).c_str(), "%d", &status_code);
  }
  return status_code;
}

bool UrlRequest::PostRequestWithPath(const std::string& path,
                                     const std::string& data) {
  std::string request;

  request.append("POST ");
  request.append(path);
  request.append(" HTTP/1.1\r\n");

  request.append("Host: ");
  request.append(socket_.domain_name());
  request.append("\r\n");

  request.append("Connection: close\r\n");
  request.append("User-Agent: Widevine CDM v1.0\r\n");

  // buffer to store length of data as a string
  char data_size_buffer[32] = {0};
  snprintf(data_size_buffer, sizeof(data_size_buffer), "%zd", data.size());

  request.append("Content-Length: ");
  request.append(data_size_buffer);  // appends size of data
  request.append("\r\n");

  request.append("\r\n");  // empty line to terminate headers

  request.append(data);

  int ret = socket_.Write(request.c_str(), request.size(), kWriteTimeoutMs);
  LOGV("HTTP request: (%d): %s", request.size(), b2a_hex(request).c_str());
  return ret != -1;
}

bool UrlRequest::PostRequest(const std::string& data) {
  return PostRequestWithPath(socket_.resource_path(), data);
}

bool UrlRequest::PostCertRequestInQueryString(const std::string& data) {
  std::string path = socket_.resource_path();
  path.append("&signedRequest=");
  path.append(data);

  return PostRequestWithPath(path, "");
}

}  // namespace wvcdm
