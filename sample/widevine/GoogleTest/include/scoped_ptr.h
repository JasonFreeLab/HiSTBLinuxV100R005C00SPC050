// Copyright 2013 Google Inc. All Rights Reserved.
//
// A simple and partial implementation of scoped_ptr class.
// The implementation is copied from gtest/include/gtest/internal/gtest-port.h.
//
#ifndef WVCDM_CORE_SCOPED_PTR_H_
#define WVCDM_CORE_SCOPED_PTR_H_

#include "wv_cdm_types.h"

namespace wvcdm {

// A scoped_ptr<T> is like a T*, except that the destructor of scoped_ptr<T>
// automatically deletes the pointer it holds (if any).
// That is, scoped_ptr<T> owns the T object that it points to.
// Like a T*, a scoped_ptr<T> may hold either NULL or a pointer to a T object.
// Also like T*, scoped_ptr<T> is thread-compatible, and once you
// dereference it, you get the thread safety guarantees of T.
//
// The size of scoped_ptr is small. On most compilers, sizeof(scoped_ptr<T>)
// == sizeof(T*).
//
// Current implementation targets having a strict subset of  C++11's
// unique_ptr<> features. Known deficiencies include not supporting move-only
// deleteres, function pointers as deleters, and deleters with reference
// types.

// This implementation of scoped_ptr is PARTIAL, e.g. it does not support move,
// custom deleter etc.
template <typename T>
class scoped_ptr {
 public:
  typedef T element_type;

  explicit scoped_ptr(T* p = NULL) : ptr_(p) {}
  ~scoped_ptr() { reset(); }

  T& operator*() const { return *ptr_; }
  T* operator->() const { return ptr_; }
  T* get() const { return ptr_; }

  T* release() {
    T* const ptr = ptr_;
    ptr_ = NULL;
    return ptr;
  }

  void reset(T* p = NULL) {
    if (p != ptr_) {
      if (sizeof(T) > 0) {  // Makes sure T is a complete type.
        delete ptr_;
      }
      ptr_ = p;
    }
  }

 private:
  T* ptr_;

  CORE_DISALLOW_COPY_AND_ASSIGN(scoped_ptr);
};

}  // namespace wvcdm

#endif  // WVCDM_CORE_SCOPED_PTR_H_
