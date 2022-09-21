// Copyright 2013 Google Inc. All Rights Reserved.
// This file adds some print methods so that when unit tests fail, the
// will print the name of an enumeration instead of the numeric value.

#include "test_printers.h"

namespace wvcdm {

void PrintTo(const enum CdmResponseType& value, ::std::ostream* os) {
  switch (value) {
    case NO_ERROR: *os                             << "NO_ERROR";
      break;
    case UNKNOWN_ERROR: *os                        << "UNKNOWN_ERROR";
      break;
    case KEY_ADDED: *os                            << "KEY_ADDED";
      break;
    case KEY_ERROR: *os                            << "KEY_ERROR";
      break;
    case KEY_MESSAGE: *os                          << "KEY_MESSAGE";
      break;
    case NEED_KEY: *os                             << "NEED_KEY";
      break;
    case KEY_CANCELED: *os                         << "KEY_CANCELED";
      break;
    case NEED_PROVISIONING: *os                    << "NEED_PROVISIONING";
      break;
    case DEVICE_REVOKED: *os                       << "DEVICE_REVOKED";
      break;
    case INSUFFICIENT_CRYPTO_RESOURCES: *os  << "INSUFFICIENT_CRYPTO_RESOURCES";
      break;
    case ADD_KEY_ERROR: *os                        << "ADD_KEY_ERROR";
      break;
    case CERT_PROVISIONING_GET_KEYBOX_ERROR_1:
      *os << "CERT_PROVISIONING_GET_KEYBOX_ERROR_1";
      break;
    case CERT_PROVISIONING_GET_KEYBOX_ERROR_2:
      *os << "CERT_PROVISIONING_GET_KEYBOX_ERROR_2";
      break;
    case CERT_PROVISIONING_INVALID_CERT_TYPE:
      *os  << "CERT_PROVISIONING_INVALID_CERT_TYPE";
      break;
    case CERT_PROVISIONING_REQUEST_ERROR_1:
      *os << "CERT_PROVISIONING_REQUEST_ERROR_1";
      break;
    case CERT_PROVISIONING_REQUEST_ERROR_2:
      *os << "CERT_PROVISIONING_REQUEST_ERROR_2";
      break;
    case CERT_PROVISIONING_REQUEST_ERROR_3:
      *os << "CERT_PROVISIONING_REQUEST_ERROR_3";
      break;
    case CERT_PROVISIONING_REQUEST_ERROR_4:
      *os << "CERT_PROVISIONING_REQUEST_ERROR_4";
      break;
    case CERT_PROVISIONING_RESPONSE_ERROR_1:
      *os << "CERT_PROVISIONING_RESPONSE_ERROR_1";
      break;
    case CERT_PROVISIONING_RESPONSE_ERROR_2:
      *os << "CERT_PROVISIONING_RESPONSE_ERROR_2";
      break;
    case CERT_PROVISIONING_RESPONSE_ERROR_3:
      *os << "CERT_PROVISIONING_RESPONSE_ERROR_3";
      break;
    case CERT_PROVISIONING_RESPONSE_ERROR_4:
      *os << "CERT_PROVISIONING_RESPONSE_ERROR_4";
      break;
    case CERT_PROVISIONING_RESPONSE_ERROR_5:
      *os << "CERT_PROVISIONING_RESPONSE_ERROR_5";
      break;
    case CERT_PROVISIONING_RESPONSE_ERROR_6:
      *os << "CERT_PROVISIONING_RESPONSE_ERROR_6";
      break;
    case CERT_PROVISIONING_RESPONSE_ERROR_7:
      *os << "CERT_PROVISIONING_RESPONSE_ERROR_7";
      break;
    case CERT_PROVISIONING_RESPONSE_ERROR_8:
      *os << "CERT_PROVISIONING_RESPONSE_ERROR_8";
      break;
    case CRYPTO_SESSION_OPEN_ERROR_1: *os      << "CRYPTO_SESSION_OPEN_ERROR_1";
      break;
    case CRYPTO_SESSION_OPEN_ERROR_2: *os      << "CRYPTO_SESSION_OPEN_ERROR_2";
      break;
    case CRYPTO_SESSION_OPEN_ERROR_3: *os      << "CRYPTO_SESSION_OPEN_ERROR_3";
      break;
    case CRYPTO_SESSION_OPEN_ERROR_4: *os      << "CRYPTO_SESSION_OPEN_ERROR_4";
      break;
    case CRYPTO_SESSION_OPEN_ERROR_5: *os      << "CRYPTO_SESSION_OPEN_ERROR_5";
      break;
    case DECRYPT_NOT_READY: *os                    << "DECRYPT_NOT_READY";
      break;
    case DEVICE_CERTIFICATE_ERROR_1: *os        << "DEVICE_CERTIFICATE_ERROR_1";
      break;
    case DEVICE_CERTIFICATE_ERROR_2: *os        << "DEVICE_CERTIFICATE_ERROR_2";
      break;
    case DEVICE_CERTIFICATE_ERROR_3: *os        << "DEVICE_CERTIFICATE_ERROR_3";
      break;
    case DEVICE_CERTIFICATE_ERROR_4: *os        << "DEVICE_CERTIFICATE_ERROR_4";
      break;
    case EMPTY_KEY_DATA_1: *os                     << "EMPTY_KEY_DATA_1";
      break;
    case EMPTY_KEY_DATA_2: *os                     << "EMPTY_KEY_DATA_2";
      break;
    case EMPTY_KEYSET_ID: *os                      << "EMPTY_KEYSET_ID";
      break;
    case EMPTY_KEYSET_ID_ENG_1: *os                << "EMPTY_KEYSET_ID_ENG_1";
      break;
    case EMPTY_KEYSET_ID_ENG_2: *os                << "EMPTY_KEYSET_ID_ENG_2";
      break;
    case EMPTY_KEYSET_ID_ENG_3: *os                << "EMPTY_KEYSET_ID_ENG_3";
      break;
    case EMPTY_KEYSET_ID_ENG_4: *os                << "EMPTY_KEYSET_ID_ENG_4";
      break;
    case EMPTY_LICENSE_RENEWAL: *os                << "EMPTY_LICENSE_RENEWAL";
      break;
    case EMPTY_LICENSE_RESPONSE_1: *os            << "EMPTY_LICENSE_RESPONSE_1";
      break;
    case EMPTY_LICENSE_RESPONSE_2: *os            << "EMPTY_LICENSE_RESPONSE_2";
      break;
    case EMPTY_PROVISIONING_CERTIFICATE_1:
      *os << "EMPTY_PROVISIONING_CERTIFICATE_1";
      break;
    case EMPTY_PROVISIONING_RESPONSE: *os      << "EMPTY_PROVISIONING_RESPONSE";
      break;
    case EMPTY_SESSION_ID: *os                     << "EMPTY_SESSION_ID";
      break;
    case GENERATE_DERIVED_KEYS_ERROR: *os      << "GENERATE_DERIVED_KEYS_ERROR";
      break;
    case LICENSE_RENEWAL_NONCE_GENERATION_ERROR:
      *os << "LICENSE_RENEWAL_NONCE_GENERATION_ERROR";
      break;
    case GENERATE_USAGE_REPORT_ERROR: *os      << "GENERATE_USAGE_REPORT_ERROR";
      break;
    case GET_LICENSE_ERROR: *os                    << "GET_LICENSE_ERROR";
      break;
    case GET_RELEASED_LICENSE_ERROR: *os        << "GET_RELEASED_LICENSE_ERROR";
      break;
    case GET_USAGE_INFO_ERROR_1: *os               << "GET_USAGE_INFO_ERROR_1";
      break;
    case GET_USAGE_INFO_ERROR_2: *os               << "GET_USAGE_INFO_ERROR_2";
      break;
    case GET_USAGE_INFO_ERROR_3: *os               << "GET_USAGE_INFO_ERROR_3";
      break;
    case GET_USAGE_INFO_ERROR_4: *os               << "GET_USAGE_INFO_ERROR_4";
      break;
    case INIT_DATA_NOT_FOUND: *os                  << "INIT_DATA_NOT_FOUND";
      break;
    case INVALID_CRYPTO_SESSION_1: *os            << "INVALID_CRYPTO_SESSION_1";
      break;
    case INVALID_CRYPTO_SESSION_2: *os            << "INVALID_CRYPTO_SESSION_2";
      break;
    case INVALID_CRYPTO_SESSION_3: *os            << "INVALID_CRYPTO_SESSION_3";
      break;
    case INVALID_CRYPTO_SESSION_4: *os            << "INVALID_CRYPTO_SESSION_4";
      break;
    case INVALID_CRYPTO_SESSION_5: *os            << "INVALID_CRYPTO_SESSION_5";
      break;
    case INVALID_DECRYPT_PARAMETERS_ENG_1:
      *os << "INVALID_DECRYPT_PARAMETERS_ENG_1";
      break;
    case INVALID_DECRYPT_PARAMETERS_ENG_2:
      *os << "INVALID_DECRYPT_PARAMETERS_ENG_2";
      break;
    case INVALID_DECRYPT_PARAMETERS_ENG_3:
      *os << "INVALID_DECRYPT_PARAMETERS_ENG_3";
      break;
    case INVALID_DECRYPT_PARAMETERS_ENG_4:
      *os << "INVALID_DECRYPT_PARAMETERS_ENG_4";
      break;
    case INVALID_DEVICE_CERTIFICATE_TYPE:
      *os << "INVALID_DEVICE_CERTIFICATE_TYPE";
      break;
    case INVALID_KEY_SYSTEM: *os                   << "INVALID_KEY_SYSTEM";
      break;
    case INVALID_LICENSE_RESPONSE: *os            << "INVALID_LICENSE_RESPONSE";
      break;
    case INVALID_LICENSE_TYPE: *os                 << "INVALID_LICENSE_TYPE";
      break;
    case INVALID_PARAMETERS_ENG_1: *os            << "INVALID_PARAMETERS_ENG_1";
      break;
    case INVALID_PARAMETERS_ENG_2: *os            << "INVALID_PARAMETERS_ENG_2";
      break;
    case INVALID_PARAMETERS_ENG_3: *os            << "INVALID_PARAMETERS_ENG_3";
      break;
    case INVALID_PARAMETERS_ENG_4: *os            << "INVALID_PARAMETERS_ENG_4";
      break;
    case INVALID_PARAMETERS_LIC_1: *os            << "INVALID_PARAMETERS_LIC_1";
      break;
    case INVALID_PARAMETERS_LIC_2: *os            << "INVALID_PARAMETERS_LIC_2";
      break;
    case INVALID_PROVISIONING_PARAMETERS_1:
      *os << "INVALID_PROVISIONING_PARAMETERS_1";
      break;
    case INVALID_PROVISIONING_PARAMETERS_2:
      *os << "INVALID_PROVISIONING_PARAMETERS_2";
      break;
    case INVALID_PROVISIONING_REQUEST_PARAM_1:
      *os << "INVALID_PROVISIONING_REQUEST_PARAM_1";
      break;
    case INVALID_PROVISIONING_REQUEST_PARAM_2:
      *os << "INVALID_PROVISIONING_REQUEST_PARAM_2";
      break;
    case INVALID_QUERY_KEY: *os                    << "INVALID_QUERY_KEY";
      break;
    case INVALID_SESSION_ID: *os                   << "INVALID_SESSION_ID";
      break;
    case KEY_REQUEST_ERROR_1: *os                  << "KEY_REQUEST_ERROR_1";
      break;
    case KEY_SIZE_ERROR: *os                       << "KEY_SIZE_ERROR";
      break;
    case KEYSET_ID_NOT_FOUND_1: *os                << "KEYSET_ID_NOT_FOUND_1";
      break;
    case KEYSET_ID_NOT_FOUND_2: *os                << "KEYSET_ID_NOT_FOUND_2";
      break;
    case KEYSET_ID_NOT_FOUND_3: *os                << "KEYSET_ID_NOT_FOUND_3";
      break;
    case LICENSE_ID_NOT_FOUND: *os                 << "LICENSE_ID_NOT_FOUND";
      break;
    case LICENSE_PARSER_INIT_ERROR: *os          << "LICENSE_PARSER_INIT_ERROR";
      break;
    case LICENSE_PARSER_NOT_INITIALIZED_1:
      *os << "LICENSE_PARSER_NOT_INITIALIZED_1";
      break;
    case LICENSE_PARSER_NOT_INITIALIZED_2:
      *os << "LICENSE_PARSER_NOT_INITIALIZED_2";
      break;
    case LICENSE_PARSER_NOT_INITIALIZED_3:
      *os << "LICENSE_PARSER_NOT_INITIALIZED_3";
      break;
    case LICENSE_RESPONSE_NOT_SIGNED: *os      << "LICENSE_RESPONSE_NOT_SIGNED";
      break;
      break;
    case LICENSE_RESPONSE_PARSE_ERROR_1:
      *os << "LICENSE_RESPONSE_PARSE_ERROR_1";
      break;
    case LICENSE_RESPONSE_PARSE_ERROR_2:
      *os << "LICENSE_RESPONSE_PARSE_ERROR_2";
      break;
    case LICENSE_RESPONSE_PARSE_ERROR_3:
      *os << "LICENSE_RESPONSE_PARSE_ERROR_3";
      break;
    case LOAD_KEY_ERROR: *os                       << "LOAD_KEY_ERROR";
      break;
    case NO_CONTENT_KEY: *os                       << "NO_CONTENT_KEY";
      break;
    case REFRESH_KEYS_ERROR: *os                   << "REFRESH_KEYS_ERROR";
      break;
    case RELEASE_ALL_USAGE_INFO_ERROR_1:
      *os << "RELEASE_ALL_USAGE_INFO_ERROR_1";
      break;
    case RELEASE_ALL_USAGE_INFO_ERROR_2:
      *os << "RELEASE_ALL_USAGE_INFO_ERROR_2";
      break;
    case RELEASE_KEY_ERROR: *os                    << "RELEASE_KEY_ERROR";
      break;
    case RELEASE_KEY_REQUEST_ERROR: *os          << "RELEASE_KEY_REQUEST_ERROR";
      break;
    case RELEASE_LICENSE_ERROR_1: *os              << "RELEASE_LICENSE_ERROR_1";
      break;
    case RELEASE_LICENSE_ERROR_2: *os              << "RELEASE_LICENSE_ERROR_2";
      break;
    case RELEASE_USAGE_INFO_ERROR: *os            << "RELEASE_USAGE_INFO_ERROR";
      break;
    case RENEW_KEY_ERROR_1: *os                    << "RENEW_KEY_ERROR_1";
      break;
    case RENEW_KEY_ERROR_2: *os                    << "RENEW_KEY_ERROR_2";
      break;
    case LICENSE_RENEWAL_SIGNING_ERROR: *os  << "LICENSE_RENEWAL_SIGNING_ERROR";
      break;
    case RESTORE_OFFLINE_LICENSE_ERROR_2:
      *os << "RESTORE_OFFLINE_LICENSE_ERROR_2";
      break;
    case SESSION_INIT_ERROR_2: *os                 << "SESSION_INIT_ERROR_2";
      break;
    case SESSION_INIT_GET_KEYBOX_ERROR: *os  << "SESSION_INIT_GET_KEYBOX_ERROR";
      break;
    case SESSION_NOT_FOUND_1: *os                  << "SESSION_NOT_FOUND_1";
      break;
    case SESSION_NOT_FOUND_2: *os                  << "SESSION_NOT_FOUND_2";
      break;
    case SESSION_NOT_FOUND_3: *os                  << "SESSION_NOT_FOUND_3";
      break;
    case SESSION_NOT_FOUND_4: *os                  << "SESSION_NOT_FOUND_4";
      break;
    case SESSION_NOT_FOUND_5: *os                  << "SESSION_NOT_FOUND_5";
      break;
    case SESSION_NOT_FOUND_6: *os                  << "SESSION_NOT_FOUND_6";
      break;
    case SESSION_NOT_FOUND_7: *os                  << "SESSION_NOT_FOUND_7";
      break;
    case SESSION_NOT_FOUND_8: *os                  << "SESSION_NOT_FOUND_8";
      break;
    case SESSION_NOT_FOUND_9: *os                  << "SESSION_NOT_FOUND_9";
      break;
    case SESSION_NOT_FOUND_10: *os                 << "SESSION_NOT_FOUND_10";
      break;
    case SESSION_NOT_FOUND_FOR_DECRYPT: *os  << "SESSION_NOT_FOUND_FOR_DECRYPT";
      break;
    case SESSION_KEYS_NOT_FOUND: *os               << "SESSION_KEYS_NOT_FOUND";
      break;
    case SIGNATURE_NOT_FOUND: *os                  << "SIGNATURE_NOT_FOUND";
      break;
    case STORE_LICENSE_ERROR_1: *os                << "STORE_LICENSE_ERROR_1";
      break;
    case STORE_LICENSE_ERROR_2: *os                << "STORE_LICENSE_ERROR_2";
      break;
    case STORE_USAGE_INFO_ERROR: *os               << "STORE_USAGE_INFO_ERROR";
      break;
    case UNPROVISION_ERROR_1: *os                  << "UNPROVISION_ERROR_1";
      break;
    case UNPROVISION_ERROR_2: *os                  << "UNPROVISION_ERROR_2";
      break;
    case UNPROVISION_ERROR_3: *os                  << "UNPROVISION_ERROR_3";
      break;
    case UNPROVISION_ERROR_4: *os                  << "UNPROVISION_ERROR_4";
      break;
    case UNSUPPORTED_INIT_DATA: *os                << "UNSUPPORTED_INIT_DATA";
      break;
    case USAGE_INFO_NOT_FOUND: *os                 << "USAGE_INFO_NOT_FOUND";
      break;
    case LICENSE_RENEWAL_SERVICE_CERTIFICATE_GENERATION_ERROR:
      *os << "LICENSE_RENEWAL_SERVICE_CERTIFICATE_GENERATION_ERROR";
      break;
    case EMPTY_PROVISIONING_CERTIFICATE_2:
      *os << "EMPTY_PROVISIONING_CERTIFICATE_2";
      break;
    case PARSE_SERVICE_CERTIFICATE_ERROR:
      *os << "PARSE_SERVICE_CERTIFICATE_ERROR";
      break;
    case SERVICE_CERTIFICATE_TYPE_ERROR:
      *os << "SERVICE_CERTIFICATE_TYPE_ERROR";
      break;
    case CLIENT_ID_GENERATE_RANDOM_ERROR:
      *os << "CLIENT_ID_GENERATE_RANDOM_ERROR";
      break;
    case CLIENT_ID_AES_INIT_ERROR: *os            << "CLIENT_ID_AES_INIT_ERROR";
      break;
    case CLIENT_ID_AES_ENCRYPT_ERROR: *os      << "CLIENT_ID_AES_ENCRYPT_ERROR";
      break;
    case CLIENT_ID_RSA_INIT_ERROR: *os            << "CLIENT_ID_RSA_INIT_ERROR";
      break;
    case CLIENT_ID_RSA_ENCRYPT_ERROR: *os      << "CLIENT_ID_RSA_ENCRYPT_ERROR";
      break;
    case INVALID_QUERY_STATUS: *os                 << "INVALID_QUERY_STATUS";
      break;
    case LICENSE_PARSER_NOT_INITIALIZED_4:
      *os << "LICENSE_PARSER_NOT_INITIALIZED_4";
      break;
    case INVALID_PARAMETERS_LIC_3: *os            << "INVALID_PARAMETERS_LIC_3";
      break;
    case INVALID_PARAMETERS_LIC_4: *os            << "INVALID_PARAMETERS_LIC_4";
      break;
    case INVALID_PARAMETERS_LIC_6: *os            << "INVALID_PARAMETERS_LIC_6";
      break;
    case INVALID_PARAMETERS_LIC_7: *os            << "INVALID_PARAMETERS_LIC_7";
      break;
    case LICENSE_REQUEST_SERVICE_CERTIFICATE_GENERATION_ERROR:
      *os << "LICENSE_REQUEST_SERVICE_CERTIFICATE_GENERATION_ERROR";
      break;
    case CENC_INIT_DATA_UNAVAILABLE: *os        << "CENC_INIT_DATA_UNAVAILABLE";
      break;
    case PREPARE_CENC_CONTENT_ID_FAILED:
      *os << "PREPARE_CENC_CONTENT_ID_FAILED";
      break;
    case WEBM_INIT_DATA_UNAVAILABLE: *os        << "WEBM_INIT_DATA_UNAVAILABLE";
      break;
    case PREPARE_WEBM_CONTENT_ID_FAILED:
      *os << "PREPARE_WEBM_CONTENT_ID_FAILED";
      break;
    case UNSUPPORTED_INIT_DATA_FORMAT: *os    << "UNSUPPORTED_INIT_DATA_FORMAT";
      break;
    case LICENSE_REQUEST_NONCE_GENERATION_ERROR:
        *os << "LICENSE_REQUEST_NONCE_GENERATION_ERROR";
      break;
    case LICENSE_REQUEST_SIGNING_ERROR: *os  << "LICENSE_REQUEST_SIGNING_ERROR";
      break;
    case EMPTY_LICENSE_REQUEST: *os                << "EMPTY_LICENSE_REQUEST";
      break;
    case DUPLICATE_SESSION_ID_SPECIFIED:
      *os << "DUPLICATE_SESSION_ID_SPECIFIED";
      break;
    case LICENSE_RENEWAL_PROHIBITED: *os        << "LICENSE_RENEWAL_PROHIBITED";
      break;
    case SESSION_FILE_HANDLE_INIT_ERROR:
      *os << "SESSION_FILE_HANDLE_INIT_ERROR";
      break;
    case INCORRECT_CRYPTO_MODE: *os                << "INCORRECT_CRYPTO_MODE";
      break;
    case INVALID_PARAMETERS_ENG_5: *os            << "INVALID_PARAMETERS_ENG_5";
      break;
    case DECRYPT_ERROR: *os                        << "DECRYPT_ERROR";
      break;
    case INSUFFICIENT_OUTPUT_PROTECTION:
      *os << "INSUFFICIENT_OUTPUT_PROTECTION";
      break;
    case SESSION_NOT_FOUND_12: *os                 << "SESSION_NOT_FOUND_12";
      break;
    case KEY_NOT_FOUND_1: *os                        << "KEY_NOT_FOUND_1";
      break;
    case KEY_NOT_FOUND_2: *os                        << "KEY_NOT_FOUND_2";
      break;
    case KEY_CONFLICT_1: *os                         << "KEY_CONFLICT_1";
      break;
    case INVALID_PARAMETERS_ENG_6: *os            << "INVALID_PARAMETERS_ENG_6";
      break;
    case INVALID_PARAMETERS_ENG_7: *os            << "INVALID_PARAMETERS_ENG_7";
      break;
    case INVALID_PARAMETERS_ENG_8: *os            << "INVALID_PARAMETERS_ENG_8";
      break;
    case INVALID_PARAMETERS_ENG_9: *os            << "INVALID_PARAMETERS_ENG_9";
      break;
    case INVALID_PARAMETERS_ENG_10: *os          << "INVALID_PARAMETERS_ENG_10";
      break;
    case INVALID_PARAMETERS_ENG_11: *os          << "INVALID_PARAMETERS_ENG_11";
      break;
    case INVALID_PARAMETERS_ENG_12: *os          << "INVALID_PARAMETERS_ENG_12";
      break;
    case SESSION_NOT_FOUND_13: *os                 << "SESSION_NOT_FOUND_13";
      break;
    case SESSION_NOT_FOUND_14: *os                 << "SESSION_NOT_FOUND_14";
      break;
    case SESSION_NOT_FOUND_15: *os                 << "SESSION_NOT_FOUND_15";
      break;
    case SESSION_NOT_FOUND_16: *os                 << "SESSION_NOT_FOUND_16";
      break;
    case KEY_NOT_FOUND_3: *os                      << "KEY_NOT_FOUND_3";
      break;
    case KEY_NOT_FOUND_4: *os                      << "KEY_NOT_FOUND_4";
      break;
    case KEY_NOT_FOUND_5: *os                      << "KEY_NOT_FOUND_5";
      break;
    case KEY_NOT_FOUND_6: *os                      << "KEY_NOT_FOUND_6";
      break;
    case KEY_ERROR_1: *os                          << "KEY_ERROR_1";
      break;
    case KEY_ERROR_2: *os                          << "KEY_ERROR_2";
      break;
    case KEY_ERROR_3: *os                          << "KEY_ERROR_3";
      break;
    case KEY_ERROR_4: *os                          << "KEY_ERROR_4";
      break;
    case INVALID_PARAMETERS_ENG_13: *os          << "INVALID_PARAMETERS_ENG_13";
      break;
    case INVALID_PARAMETERS_ENG_14: *os          << "INVALID_PARAMETERS_ENG_14";
      break;
    case INVALID_PARAMETERS_ENG_15: *os          << "INVALID_PARAMETERS_ENG_15";
      break;
    case INVALID_PARAMETERS_ENG_16: *os          << "INVALID_PARAMETERS_ENG_16";
      break;
    default:
      *os                                        << "Unknown CdmResponseType";
      break;
  }
}

void PrintTo(const enum CdmLicenseType& value, ::std::ostream* os) {
  switch (value) {
    case kLicenseTypeOffline: *os                  << "kLicenseTypeOffline";
      break;
    case kLicenseTypeStreaming: *os                << "kLicenseTypeStreaming";
      break;
    case kLicenseTypeRelease: *os                  << "kLicenseTypeRelease";
      break;
    case kLicenseTypeDeferred: *os                 << "kLicenseTypeDeferred";
      break;
    default:
      *os                                          << "Unknown  CdmLicenseType";
      break;
  }
};

void PrintTo(const enum CdmSecurityLevel& value, ::std::ostream* os) {
  switch (value) {
    case kSecurityLevelUninitialized: *os       << "kSecurityLevelUninitialized";
      break;
    case kSecurityLevelL1: *os                     << "kSecurityLevelL1";
      break;
    case kSecurityLevelL2: *os                     << "kSecurityLevelL2";
      break;
    case kSecurityLevelL3: *os                     << "kSecurityLevelL3";
      break;
    case kSecurityLevelUnknown: *os                << "kSecurityLevelUnknown";
      break;
    default:
      *os                                          << "Unknown CdmSecurityLevel";
      break;
  }
};

void PrintTo(const enum CdmCertificateType& value, ::std::ostream* os) {
  switch (value) {
    case kCertificateWidevine: *os                 << "kCertificateWidevine";
      break;
    case kCertificateX509: *os                     << "kCertificateX509";
      break;
    default:
      *os                                        << "Unknown CdmCertificateType";
      break;
  }
};

}  // namespace wvcdm
