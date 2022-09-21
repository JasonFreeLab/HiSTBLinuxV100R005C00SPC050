// Copyright 2015 Google Inc. All Rights Reserved.

#include <assert.h>
#include <getopt.h>
#include <gtest/gtest.h>
#include <time.h>

#if defined(__linux__)
#include <sys/utsname.h>
#endif

#include "cdm.h"
#include "device_cert.h"
#include "override.h"
#include "test_host.h"

#if defined(OEMCRYPTO_TESTS)
# include "oec_device_features.h"
#endif

using namespace widevine;

TestHost* g_host = NULL;

int main(int argc, char** argv) {
  // Init gtest and let it consume arguments.
  ::testing::InitGoogleTest(&argc, argv);

  // Parse arguments.
  int show_usage = 0;
  int opt;
  int verbosity = 0;
  while ((opt = getopt_long(argc, argv, "v", NULL, NULL)) != -1) {
    switch (opt) {
      case 'v':
        ++verbosity;
        break;
      case '?':
        show_usage = 1;
        break;
    }
  }
  if (show_usage) {
    fprintf(stderr, "Usage: %s [-v|-vv|-vvv]\n\n", argv[0]);
    return 0;
  }

  // Set up a Host so that tests and initialize the library.  This makes these
  // services available to the tests.  We would do this in the test suite
  // itself, but the core & OEMCrypto tests don't know they depend on this
  // for storage.
  g_host = new TestHost();
  Cdm::ClientInfo client_info;
  // Set client info that denotes this as the test suite:
  client_info.product_name = "CE cdm tests";
  client_info.company_name = "www";
  client_info.model_name = "www";
#if defined(__linux__)
  client_info.device_name = "Linux";
  {
    struct utsname name;
    if (uname(&name) == 0) {
      client_info.arch_name = name.machine;
    }
  }
#else
  client_info.device_name = "unknown";
#endif
  client_info.build_info = __DATE__;

  Cdm::Status status = Cdm::initialize(
      Cdm::kNoSecureOutput, client_info, g_host, g_host, g_host,
      static_cast<Cdm::LogLevel>(verbosity));
  (void)status;  // status is now used when assertions are turned off.
  assert(status == Cdm::kSuccess);

#if defined(OEMCRYPTO_TESTS)
  // Set up the OEMCrypto test harness.
  wvoec::global_features.Initialize(false /* is_cast_receiver */,
                                    false /* force_load_test_keybox */);
  ::testing::GTEST_FLAG(filter)
      = wvoec::global_features.RestrictFilter(::testing::GTEST_FLAG(filter));
#endif

  return RUN_ALL_TESTS();
}
