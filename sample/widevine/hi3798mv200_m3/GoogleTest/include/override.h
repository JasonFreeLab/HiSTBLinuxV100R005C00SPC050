// Copyright 2015 Google Inc. All Rights Reserved.
// TODO: Import to core/, use everywhere.
#ifndef WVCDM_CDM_OVERRIDE_H_
#define WVCDM_CDM_OVERRIDE_H_

#define GCC_HAS_OVERRIDE ( \
  (__GNUC__ > 4) || \
  (__GNUC__ == 4 && __GNUC_MINOR__ >= 7) \
)

#if defined(COMPILER_MSVC) || defined(__clang__) || GCC_HAS_OVERRIDE
#define OVERRIDE override
#else
#define OVERRIDE
#endif

#endif  // WVCDM_CDM_OVERRIDE_H_
