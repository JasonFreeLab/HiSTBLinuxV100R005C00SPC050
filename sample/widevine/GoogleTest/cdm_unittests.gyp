# Copyright 2015 Google Inc. All Rights Reserved.
#
# Builds under the CDM ./build.py (target platform) build system
# Refer to the distribution package's README for details.
{
  'variables': {
    'oemcrypto_lib%': '',
    'openssl_config%': 'system',
    'openssl_target%': '',
  },
  'targets': [
    {
      'target_name': 'widevine_ce_cdm_unittest',
      'type': 'executable',
      'sources': [
        # The test runner and the testing device certificate.
        'src/cdm_test_main.cpp',
        'src/device_cert.cpp',
        'include/device_cert.h',
        # The test host, which is required for all test suites on CE.
        'src/test_host.cpp',
        'include/test_host.h',
      ],
      'variables': {
        'cdm_dir': '..',
      },
      'includes': [
        'oemcrypto_unittests.gypi',
        'core_unittests.gypi',
        'cdm_unittests.gypi',
      ],
      'include_dirs': [
        './include',
      ],
      'libraries': [
        '-lrt', # for l1
        '-ljpeg', # for l1
        '-lpthread',
        '-lhi_widevineCdm',
        '-lssl',  # oec_mock
        '-lcrypto',  # oec_mock
        #'-loemcryptoL3', # for L3
        '-lhi_widevine_tee_googletest', # for L1
        '-lhi_msp', # for L1
        '-lhi_common', # for L1
        '-lteec', # for L1
        '-lprotobuf',
        #'-lpthread',  # gtest
        '-ldl',
      ],
      'dependencies': [
        #'cdm.gyp:widevine_ce_cdm_shared',
        './third_party/gmock.gyp:gmock',
        './third_party/gmock.gyp:gtest',
      ],
    },
  ],
}
