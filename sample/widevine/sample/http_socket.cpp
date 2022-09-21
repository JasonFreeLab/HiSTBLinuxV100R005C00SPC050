// Copyright 2013 Google Inc. All Rights Reserved.

#include "http_socket.h"

#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/x509.h>

#include "log.h"

namespace wvcdm {

namespace {

// Helper function to tokenize a string.  This makes it easier to avoid silly
// parsing bugs that creep in easily when each part of the string is parsed
// with its own piece of code.
bool Tokenize(const std::string& source, const std::string& delim,
              const size_t offset, std::string* substring_output,
              size_t* next_offset) {
  size_t start_of_delim = source.find(delim, offset);
  if (start_of_delim == std::string::npos) {
    return false;
  }
  substring_output->assign(source, offset, start_of_delim - offset);
  *next_offset = start_of_delim + delim.size();
  return true;
}

SSL_CTX* InitSslContext() {
  const SSL_METHOD* method;
  SSL_CTX* ctx;

  OpenSSL_add_all_algorithms();
  SSL_load_error_strings();
  method = TLSv1_2_client_method();
  ctx = SSL_CTX_new(method);
  if (!ctx) LOGE("failed to create SSL context");
  int ret = SSL_CTX_set_cipher_list(
      ctx, "ALL:!RC4-MD5:!RC4-SHA:!ECDHE-ECDSA-RC4-SHA:!ECDHE-RSA-RC4-SHA");
  if (0 != ret) LOGE("error disabling vulnerable ciphers");
  return ctx;
}

#if 0
// unused, may be useful for debugging SSL-related issues.
void ShowServerCertificate(const SSL* ssl) {
  // gets the server certificate
  X509* cert = SSL_get_peer_certificate(ssl);
  if (cert) {
    char* line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
    LOGV("server certificate:");
    LOGV("subject: %s", line);
    free(line);
    line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
    LOGV("issuer: %s", line);
    free(line);
    X509_free(cert);
  } else {
    LOGE("Failed to get server certificate");
  }
}
#endif

// Wait for a socket to be ready for reading or writing.
// Establishing a connection counts as "ready for write".
// Returns false on select error or timeout.
// Returns true when the socket is ready.
bool SocketWait(int fd, bool for_read, int timeout_in_ms) {
  fd_set fds;
  FD_ZERO(&fds);
  FD_SET(fd, &fds);

  struct timeval tv;
  tv.tv_sec = timeout_in_ms / 1000;
  tv.tv_usec = (timeout_in_ms % 1000) * 1000;

  fd_set* read_fds = NULL;
  fd_set* write_fds = NULL;
  if (for_read) {
    read_fds = &fds;
  } else {
    write_fds = &fds;
  }

  int ret = select(fd + 1, read_fds, write_fds, NULL, &tv);
  if (ret == 0) {
    LOGE("socket timed out");
    return false;
  } else if (ret == -1) {
    LOGE("select failed, errno = %d", errno);
    return false;
  }

  // socket ready.
  return true;
}

}  // namespace

// Parses the URL and extracts all relevant information.
// static
bool HttpSocket::ParseUrl(const std::string& url, std::string* scheme,
                          bool* secure_connect, std::string* domain_name,
                          std::string* port, std::string* path) {
  size_t offset = 0;

  if (!Tokenize(url, "://", offset, scheme, &offset)) {
    LOGE("Invalid URL, scheme not found: %s", url.c_str());
    return false;
  }

  // If the scheme is http or https, set secure_connect and port accordingly.
  // Otherwise, consider the scheme unsupported and fail.
  if (*scheme == "http") {
    *secure_connect = false;
    port->assign("80");
  } else if (*scheme == "https") {
    *secure_connect = true;
    port->assign("443");
  } else {
    LOGE("Invalid URL, scheme not supported: %s", url.c_str());
    return false;
  }

  if (!Tokenize(url, "/", offset, domain_name, &offset)) {
    // The rest of the URL belongs to the domain name.
    domain_name->assign(url, offset, std::string::npos);
    // No explicit path after the domain name.
    path->assign("/");
  } else {
    // The rest of the URL, including the preceding slash, belongs to the path.
    path->assign(url, offset - 1, std::string::npos);
  }

  // The domain name may optionally contain a port which overrides the default.
  std::string domain_name_without_port;
  size_t port_offset;
  if (Tokenize(*domain_name, ":", 0, &domain_name_without_port, &port_offset)) {
    port->assign(domain_name->c_str() + port_offset);
    int port_num = atoi(port->c_str());
    if (port_num <= 0 || port_num >= 65536) {
      LOGE("Invalid URL, port not valid: %s", url.c_str());
      return false;
    }
    domain_name->assign(domain_name_without_port);
  }

  return true;
}

HttpSocket::HttpSocket(const std::string& url)
    : socket_fd_(-1), ssl_(NULL), ssl_ctx_(NULL) {
  valid_url_ = ParseUrl(url, &scheme_, &secure_connect_, &domain_name_, &port_,
                        &resource_path_);
  SSL_library_init();
}

HttpSocket::~HttpSocket() { CloseSocket(); }

void HttpSocket::CloseSocket() {
  if (socket_fd_ != -1) {
    close(socket_fd_);
    socket_fd_ = -1;
  }
  if (ssl_) {
    SSL_free(ssl_);
    ssl_ = NULL;
  }
  if (ssl_ctx_) {
    SSL_CTX_free(ssl_ctx_);
    ssl_ctx_ = NULL;
  }
}

bool HttpSocket::Connect(int timeout_in_ms) {
  if (!valid_url_) {
    return false;
  }

  // lookup the server IP
  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_NUMERICSERV | AI_ADDRCONFIG;

  struct addrinfo* addr_info = NULL;
  int ret = getaddrinfo(domain_name_.c_str(), port_.c_str(), &hints,
                        &addr_info);
  if (ret != 0) {
    LOGE("getaddrinfo failed, errno = %d", ret);
    return false;
  }

  // get a socket
  socket_fd_ = socket(addr_info->ai_family, addr_info->ai_socktype,
                      addr_info->ai_protocol);
  if (socket_fd_ < 0) {
    LOGE("cannot open socket, errno = %d", errno);
    return false;
  }

  // set the socket in non-blocking mode
  int original_flags = fcntl(socket_fd_, F_GETFL, 0);
  if (original_flags == -1) {
    LOGE("fcntl error, errno = %d", errno);
    CloseSocket();
    return false;
  }
  if (fcntl(socket_fd_, F_SETFL, original_flags | O_NONBLOCK) == -1) {
    LOGE("fcntl error, errno = %d", errno);
    CloseSocket();
    return false;
  }

  // connect to the server
  ret = connect(socket_fd_, addr_info->ai_addr, addr_info->ai_addrlen);
  freeaddrinfo(addr_info);

  if (ret == 0) {
    // connected right away.
  } else {
    if (errno != EINPROGRESS) {
      // failed right away.
      LOGE("cannot connect to %s, errno = %d", domain_name_.c_str(), errno);
      CloseSocket();
      return false;
    } else {
      // in progress.  block until timeout expired or connection established.
      if (!SocketWait(socket_fd_, /* for_read */ false, timeout_in_ms)) {
        LOGE("cannot connect to %s", domain_name_.c_str());
        CloseSocket();
        return false;
      }
    }
  }

  // set up SSL if needed
  if (secure_connect_) {
    ssl_ctx_ = InitSslContext();
    if (!ssl_ctx_) {
      CloseSocket();
      return false;
    }

    ssl_ = SSL_new(ssl_ctx_);
    if (!ssl_) {
      LOGE("failed SSL_new");
      CloseSocket();
      return false;
    }

    BIO* a_bio = BIO_new_socket(socket_fd_, BIO_NOCLOSE);
    if (!a_bio) {
      LOGE("BIO_new_socket error");
      CloseSocket();
      return false;
    }

    SSL_set_bio(ssl_, a_bio, a_bio);
    do {
      ret = SSL_connect(ssl_);
      if (ret != 1) {
        int ssl_err = SSL_get_error(ssl_, ret);
        if (ssl_err != SSL_ERROR_WANT_READ && ssl_err != SSL_ERROR_WANT_WRITE) {
          char buf[256];
          LOGE("SSL_connect error: %s", ERR_error_string(ERR_get_error(), buf));
          CloseSocket();
          return false;
        }
        bool for_read = ssl_err == SSL_ERROR_WANT_READ;
        if (!SocketWait(socket_fd_, for_read, timeout_in_ms)) {
          LOGE("cannot connect to %s", domain_name_.c_str());
          CloseSocket();
          return false;
        }
      }
    } while (ret != 1);
  }

  return true;
}

// Returns -1 for error, number of bytes read for success.
// The timeout here only applies to the span between packets of data, for the
// sake of simplicity.
int HttpSocket::Read(char* data, int len, int timeout_in_ms) {
  int total_read = 0;
  int to_read = len;

  if (socket_fd_ == -1) {
    LOGE("Socket to %s not open.  Cannot read.", domain_name_.c_str());
    return -1;
  }
  while (to_read > 0) {
    if (!SocketWait(socket_fd_, /* for_read */ true, timeout_in_ms)) {
      LOGE("unable to read from %s", domain_name_.c_str());
      return -1;
    }

    int read;
    if (secure_connect_)
      read = SSL_read(ssl_, data, to_read);
    else
      read = recv(socket_fd_, data, to_read, 0);

    if (read > 0) {
      to_read -= read;
      data += read;
      total_read += read;
    } else if (read == 0) {
      // The connection has been closed.  No more data.
      break;
    } else {
      LOGE("recv returned %d, errno = %d", read, errno);
      return -1;
    }
  }

  return total_read;
}

// Returns -1 for error, number of bytes written for success.
// The timeout here only applies to the span between packets of data, for the
// sake of simplicity.
int HttpSocket::Write(const char* data, int len, int timeout_in_ms) {
  int total_sent = 0;
  int to_send = len;

  if (socket_fd_ == -1) {
    LOGE("Socket to %s not open. Cannot write.", domain_name_.c_str());
    return -1;
  }
  while (to_send > 0) {
    int sent;
    if (secure_connect_)
      sent = SSL_write(ssl_, data, to_send);
    else
      sent = send(socket_fd_, data, to_send, 0);

    if (sent > 0) {
      to_send -= sent;
      data += sent;
      total_sent += sent;
    } else if (sent == 0) {
      // We filled up the pipe.  Wait for room to write.
      if (!SocketWait(socket_fd_, /* for_read */ false, timeout_in_ms)) {
        LOGE("unable to write to %s", domain_name_.c_str());
        return -1;
      }
    } else {
      LOGE("send returned %d, errno = %d", sent, errno);
      return -1;
    }
  }

  return total_sent;
}

}  // namespace wvcdm
