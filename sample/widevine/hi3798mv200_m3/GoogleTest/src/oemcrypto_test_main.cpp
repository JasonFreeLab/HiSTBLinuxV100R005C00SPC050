#include <gtest/gtest.h>
#include <iostream>

#include "log.h"
#include "oec_device_features.h"
#include "OEMCryptoCENC.h"
#include "properties.h"

static void acknowledge_cast() {
  std::cout
      << "==================================================================\n"
      << "= This device is expected to load x509 certs as a cast receiver. =\n"
      << "==================================================================\n";
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  wvcdm::Properties::Init();
  wvcdm::g_cutoff = wvcdm::LOG_INFO;
  bool is_cast_receiver = false;
  bool force_load_test_keybox = false;
  bool filter_tests = true;
  for(int i=0; i < argc; i++) {
    if (!strcmp(argv[i], "--cast")) {
      acknowledge_cast();
      is_cast_receiver = true;
    }
    if (!strcmp(argv[i], "--force_load_test_keybox")) {
      force_load_test_keybox = true;
    }
    if (!strcmp(argv[i], "--no_filter")) {
      filter_tests  = false;
    }
  }
  wvoec::global_features.Initialize(is_cast_receiver, force_load_test_keybox);
  // If the user requests --no_filter, we don't change the filter, otherwise, we
  // filter out features that are not supported.
  if (filter_tests) {
    ::testing::GTEST_FLAG(filter)
        = wvoec::global_features.RestrictFilter(::testing::GTEST_FLAG(filter));
  }
  return RUN_ALL_TESTS();
}
