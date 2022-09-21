# Copyright 2015 Google Inc. All Rights Reserved.
#
# Include this in any custom unit test targets.
# Does not include the test runner main.
{
  'sources': [
    './src/base64_test.cpp',
    './src/cdm_engine_test.cpp',
    './src/cdm_session_unittest.cpp',
    './src/config_test_env.cpp',
    './src/device_files_unittest.cpp',
    './src/generic_crypto_unittest.cpp',
    './src/http_socket.cpp',
    './src/initialization_data_unittest.cpp',
    './src/license_request.cpp',
    './src/license_unittest.cpp',
    './src/license_keys_unittest.cpp',
    './src/policy_engine_unittest.cpp',
    './src/policy_engine_constraints_unittest.cpp',
    './src/test_printers.cpp',
    './src/url_request.cpp',
  ],
  'include_dirs': [
    './include',
    '../../../rootfs/protobuf/include',
  ],
  'defines': [
    'UNIT_TEST',
    'CORE_TESTS',
  ],
  'dependencies': [
    # This gypi may be included from outside this folder, and dependencies in
    # a gypi are relative to the gyp file doing the including.
    # cdm_dir is a variable the including file must set to help us find the
    # correct path.
    #'<(cdm_dir)/cdm/cdm.gyp:license_protocol',
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
