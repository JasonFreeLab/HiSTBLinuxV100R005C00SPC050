// Copyright 2013 Google Inc. All Rights Reserved.
//
// Lock - Platform independent interface for a Mutex class
//
#ifndef WVCDM_CORE_LOCK_H_
#define WVCDM_CORE_LOCK_H_

#include "wv_cdm_types.h"

namespace wvcdm {

// Simple lock class. The implementation is platform dependent.
//
// The lock must be unlocked by the thread that locked it.
// The lock is also not recursive (ie. cannot be taken multiple times).
class Lock {
 public:
  Lock();
  ~Lock();

  void Acquire();
  void Release();

  friend class AutoLock;

 private:
  class Impl;
  Impl* impl_;

  CORE_DISALLOW_COPY_AND_ASSIGN(Lock);
};

// Manages the lock automatically. It will be locked when AutoLock
// is constructed and release when AutoLock goes out of scope.
class AutoLock {
 public:
  explicit AutoLock(Lock& lock) : lock_(&lock) { lock_->Acquire(); }

  explicit AutoLock(Lock* lock) : lock_(lock) { lock_->Acquire(); }

  ~AutoLock() { lock_->Release(); }

 private:
  Lock* lock_;

  CORE_DISALLOW_COPY_AND_ASSIGN(AutoLock);
};

}  // namespace wvcdm

#endif  // WVCDM_CORE_LOCK_H_
