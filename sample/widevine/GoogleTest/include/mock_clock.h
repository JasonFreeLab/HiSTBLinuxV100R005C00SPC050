// Copyright 2014 Google Inc. All Rights Reserved.

#ifndef CDM_TEST_MOCK_CLOCK_H_
#define CDM_TEST_MOCK_CLOCK_H_

#include "clock.h"
#include <gmock/gmock.h>

namespace wvcdm {

class MockClock : public Clock {
 public:
  MOCK_METHOD0(GetCurrentTime, int64_t());
};

}  // wvcdm

#endif  // CDM_TEST_MOCK_CLOCK_H_
