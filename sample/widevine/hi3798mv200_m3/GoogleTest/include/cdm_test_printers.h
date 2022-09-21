// Copyright 2015 Google Inc. All Rights Reserved.
// This file adds some print methods so that when unit tests fail, the
// will print the name of an enumeration instead of the numeric value.

#ifndef WVCDM_CDM_TEST_CDM_TEST_PRINTERS_H_
#define WVCDM_CDM_TEST_CDM_TEST_PRINTERS_H_

#include <iostream>
#include "cdm.h"

namespace widevine {

void PrintTo(const Cdm::MessageType& value, ::std::ostream* os);
void PrintTo(const Cdm::Status& value, ::std::ostream* os);
void PrintTo(const Cdm::KeyStatus& value, ::std::ostream* os);

}  // namespace widevine

#endif  // WVCDM_CDM_TEST_CDM_TEST_PRINTERS_H_
