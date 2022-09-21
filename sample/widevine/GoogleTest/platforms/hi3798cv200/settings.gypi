# Copyright 2015 Google Inc. All rights reserved.
{
  # Here you can override global gyp variables with platform-specific values.
  # See cdm.gyp for a complete list of settings you can override.
  'variables': {
    #'oemcrypto_version': 9,
  }, # end variables

  # Here you can set platform-specific compiler settings.
  'target_defaults': {
    # These are flags passed to the compiler for all C & C++ files.
    'cflags': [
      '-fPIC',
      '-fno-exceptions',
    ],

    # These are flags passed to the compiler for plain C only.
    'cflags_c': [
    ],

    # These are flags passed to the compiler for C++ only.
    'cflags_cc': [
      '-std=c++11',
    ],

    # These are flags passed to the linker.
    'ldflags': [
    ],

    # These are macros set by the compiler.
    'defines': [
      #'EXAMPLE_MACRO_WITH_NO_VALUE',
      #'EXAMPLE_KEY=EXAMPLE_VALUE',
    ],

    # These are additional include paths to search for headers.
    'include_dirs': [
      #'/usr/local/include',
    ],

    'target_conditions': [
      ['_toolset == "host"', {
        # These are settings specifically for the host toolchain.
        # The extra equals sign in the key name instructs gyp to replace
        # the generic settings above rather than append to them.
        'cflags=': [
        ],

        'cflags_c=': [
        ],

        'cflags_cc=': [
        ],

        'ldflags=': [
        ],

        'defines=': [
        ],

        'include_dirs=': [
        ],
      }], # end _toolset == "host" condition
    ], # end target_conditions

    'configurations': {
      # These are additional settings per build configuration.
      # You may specify any of the keys above in this section
      # (cflags, cflags_c, cflags_cc, ldflags, defines, include_dirs).
      'Debug': {
        'cflags': [
          '-O0',
          '-g',
        ],
        'defines': [
          '_DEBUG',
        ],
        'ldflags': [
          '-g',
        ],
      },
      'Release': {
        'cflags': [
          '-O2',
        ],
        'defines': [
          'NDEBUG',
        ],
      },
    }, # end configurations
  }, # end target_defaults
}
