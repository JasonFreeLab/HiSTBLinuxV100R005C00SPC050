# Copyright 2015 Google Inc. All Rights Reserved.
#
# Include this in any custom unit test targets.
# Does not include the device certificate or the test runner main.
{
  'sources': [
    './src/http_socket.cpp',
    './src/license_request.cpp',
    './src/url_request.cpp',

    './src/cdm_test.cpp',
    './src/cdm_test_printers.cpp',
    './include/cdm_test_printers.h',
    './src/test_host.cpp',
    './include/test_host.h',
  ],
  'include_dirs': [
    './include',
  ],
  'defines': [
    'UNIT_TEST',
    'CDM_TESTS',
  ],
  'conditions': [
    # OpenSSL needed for http_socket
    ['openssl_config == "target"', {
      'dependencies': [
        '<(openssl_target)',
      ],
    }, {
      # openssl_config == "system"
      'link_settings': {
        'libraries': [
          '-lssl',
        ],
      },
    }],
  ],
}
