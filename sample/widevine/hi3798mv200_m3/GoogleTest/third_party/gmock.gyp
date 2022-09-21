# Copyright 2013 Google Inc. All Rights Reserved.
{
  'target_defaults': {
    'type': 'static_library',
    'include_dirs': [
      'gmock',
      'gmock/include',
      'gmock/gtest',
      'gmock/gtest/include',
    ],
    'direct_dependent_settings': {
      'include_dirs': [
        'gmock/include',
        'gmock/gtest/include',
      ],
    },
  },
  'targets': [
    {
      'target_name': 'gmock',
      'sources': [
        'gmock/src/gmock-all.cc',
      ],
    },
    {
      'target_name': 'gmock_main',
      'sources': [
        'gmock/src/gmock_main.cc',
      ],
    },
    {
      'target_name': 'gtest',
      'sources': [
        'gmock/gtest/src/gtest-all.cc',
      ],
    },
  ],
}
