// Copyright 2013 Google Inc. All Rights Reserved.
// This file adds some print methods so that when unit tests fail, the
// will print the name of an enumeration instead of the numeric value.

#ifndef CDM_TEST_PRINTERS_H_
#define CDM_TEST_PRINTERS_H_

#include <iostream>
#include "wv_cdm_types.h"

namespace wvcdm {
void PrintTo(const enum CdmResponseType& value, ::std::ostream* os);
void PrintTo(const enum CdmLicenseType& value, ::std::ostream* os);
void PrintTo(const enum CdmSecurityLevel& value, ::std::ostream* os);
void PrintTo(const enum CdmCertificateType& value, ::std::ostream* os);
}  // namespace wvcdm

#endif  // CDM_TEST_PRINTERS_H_
