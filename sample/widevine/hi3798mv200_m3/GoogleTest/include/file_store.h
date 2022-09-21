// Copyright 2013 Google Inc. All Rights Reserved.
//
// File - Platform independent interface for a File class
//
#ifndef WVCDM_CORE_FILE_STORE_H_
#define WVCDM_CORE_FILE_STORE_H_

#include <unistd.h>
#include <string>
#include <vector>

#include "wv_cdm_types.h"

namespace wvcdm {

// File class. The implementation is platform dependent.
class File {
 public:
  virtual ssize_t Read(char* buffer, size_t bytes);
  virtual ssize_t Write(const char* buffer, size_t bytes);
  virtual void Close();

 protected:
  class Impl;

  File(Impl*);
  virtual ~File();

 private:
  Impl* impl_;

  friend class FileSystem;
  CORE_DISALLOW_COPY_AND_ASSIGN(File);
};

class FileSystem {
 public:
  class Impl;

  // defines as bit flag
  enum OpenFlags {
    kNoFlags = 0,
    kCreate = 1,
    kReadOnly = 2,  // defaults to read and write access
    kTruncate = 4
  };

  FileSystem();
  FileSystem(const std::string& origin, void* extra_data);
  virtual ~FileSystem();

  virtual File* Open(const std::string& file_path, int flags);

  virtual bool Exists(const std::string& file_path);
  virtual bool Remove(const std::string& file_path);
  virtual ssize_t FileSize(const std::string& file_path);

  const std::string& origin() const { return origin_; }
  void SetOrigin(const std::string& origin);

 private:
  Impl* impl_;
  std::string origin_;

  CORE_DISALLOW_COPY_AND_ASSIGN(FileSystem);
};

}  // namespace wvcdm

#endif  // WVCDM_CORE_FILE_STORE_H_
