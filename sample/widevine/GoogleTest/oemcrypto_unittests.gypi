# Copyright 2015 Google Inc. All Rights Reserved.
#
# Include this in any custom unit test targets.
# Does not include the test runner main.
{
  'sources': [
    './src/oec_device_features.cpp',
    './src/oec_session_util.cpp',
    './src/oemcrypto_test.cpp',
  ],
  'include_dirs': [
    './include', 
  ],
  'defines': [
    'OEMCRYPTO_TESTS',
  ],
}
