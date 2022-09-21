// Copyright 2015 Google Inc. All Rights Reserved.

#include "cdm_test_printers.h"

namespace widevine {

void PrintTo(const Cdm::MessageType& value, ::std::ostream* os) {
  switch (value) {
    case Cdm::kLicenseRequest: *os << "Cdm::kLicenseRequest";
      break;
    case Cdm::kLicenseRenewal: *os << "Cdm::kLicenseRenewal";
      break;
    case Cdm::kLicenseRelease: *os << "Cdm::kLicenseRelease";
      break;
    case Cdm::kIndividualizationRequest:
      *os << "Cdm::kIndividualizationRequest";
      break;
    default: *os << "Unknown Cdm::MessageType value " << value;
      break;
  }
}

void PrintTo(const Cdm::Status& value, ::std::ostream* os) {
  switch (value) {
    case Cdm::kSuccess: *os << "Cdm::kSuccess";
      break;
    case Cdm::kNeedsDeviceCertificate: *os << "Cdm::kNeedsDeviceCertificate";
      break;
    case Cdm::kSessionNotFound: *os << "Cdm::kSessionNotFound";
      break;
    case Cdm::kDecryptError: *os << "Cdm::kDecryptError";
      break;
    case Cdm::kNoKey: *os << "Cdm::kNoKey";
      break;
    case Cdm::kTypeError: *os << "Cdm::kTypeError";
      break;
    case Cdm::kNotSupported: *os << "Cdm::kNotSupported";
      break;
    case Cdm::kInvalidState: *os << "Cdm::kInvalidState";
      break;
    case Cdm::kQuotaExceeded: *os << "Cdm::kQuotaExceeded";
      break;
    case Cdm::kRangeError: *os << "Cdm::kRangeError";
      break;
    case Cdm::kUnexpectedError: *os << "Cdm::kUnexpectedError";
      break;
    default: *os << "Unknown Cdm::Status value " << value;
      break;
  }
}

void PrintTo(const Cdm::KeyStatus& value, ::std::ostream* os) {
  switch (value) {
    case Cdm::kUsable: *os << "Cdm::kUsable";
      break;
    case Cdm::kExpired: *os << "Cdm::kExpired";
      break;
    case Cdm::kOutputRestricted: *os << "Cdm::kOutputRestricted";
      break;
    case Cdm::kStatusPending: *os << "Cdm::kStatusPending";
      break;
    case Cdm::kInternalError: *os << "Cdm::kInternalError";
      break;
    default: *os << "Unknown Cdm::KeyStatus value " << value;
      break;
  }
}

}  // namespace widevine
