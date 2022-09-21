#ifndef DRM_COMMON_TEST_H_
#define DRM_COMMON_TEST_H_

#include "string_conversions.h"

using namespace drmengine;

const std::string kDrmEngineLibraryPath = "mnt/";
const std::string kDrmEngineLibraryName = "libhi_drm_engine.so";
const HI_U8 kWidevineUUID[16] = {
    0xED,0xEF,0x8B,0xA9,0x79,0xD6,0x4A,0xCE,
    0xA3,0xC8,0x27,0xDC,0xD5,0x1D,0x21,0xED
};

const HI_U8 kOldNetflixWidevineUUID[16] = {
    0x29,0x70,0x1F,0xE4,0x3C,0xC7,0x4A,0x34,
    0x8C,0x5B,0xAE,0x90,0xC7,0x43,0x9A,0x47
};

const std::string kCencInitData = a2bs_hex(
    "00000042"                          // blob size
    "70737368"                          // "pssh"
    "00000000"                          // flags
    "edef8ba979d64acea3c827dcd51d21ed"  // Widevine system id
    "00000022"                          // pssh data size
    // pssh data:
    "08011a0d7769646576696e655f746573"
    "74220f73747265616d696e675f636c69"
    "7031");

// This Key ID must match the key retrieved from kLicenseServerAppspot by
// kCencInitData.
const std::vector<uint8_t> kKeyIdCtr = a2b_hex(
    "371ea35e1a985d75d198a7f41020dc23");

// A default pattern object disables patterns during decryption.
const HI_DRM_PATTERN kPatternNone(0, 0);
// The recommended pattern from CENC 3.0, which is also the pattern used by
// HLS. Encrypts 1 in every 10 crypto blocks.
const HI_DRM_PATTERN kPatternRecommended(1, 9);
// The recommended pattern for HLS Audio, which should be decrypted in CENC 3.0
// cbcs mode despite not using patterns.  This pattern disables patterned
// decryption by having one encrypted block and no clear blocks.
const HI_DRM_PATTERN kPatternHlsAudio(1, 0);

// Dummy encrypted data using the CENC 3.0 "cenc" mode.  Encrypted using the
// key matching kKeyIdCtr.
const std::vector<uint8_t> kInputCenc = a2b_hex(
    "64ab17b3e3dfab47245c7cce4543d4fc7a26dcf248f19f9b59f3c92601440b36"
    "17c8ed0c96c656549e461f38708cd47a434066f8df28ccc28b79252eee3f9c2d"
    "7f6c68ebe40141fe818fe082ca523c03d69ddaf183a93c022327fedc5582c5ab"
    "ca9d342b71263a67f9cb2336f12108aaaef464f17177e44e9b0c4e56e61da53c"
    "2150b4405cc82d994dfd9bf4087c761956d6688a9705db4cf350381085f383c4"
    "9666d4aed135c519c1f0b5cba06e287feea96ea367bf54e7368dcf998276c6e4"
    "6497e0c50e20fef74e42cb518fe7f22ef27202428688f86404e8278587017012"
    "c1d65537c6cbd7dde04aae338d68115a9f430afc100ab83cdadf45dca39db685");
const std::vector<uint8_t> kIvCenc = a2b_hex(
    "f6f4b1e600a5b67813ed2bded913ba9f");
const std::vector<uint8_t> kOutputCenc = a2b_hex(
    "217ce9bde99bd91e9733a1a00b9b557ac3a433dc92633546156817fae26b6e1c"
    "942ac20a89ff79f4c2f25fba99d6a44618a8c0420b27d54e3da17b77c9d43cca"
    "595d259a1e4a8b6d7744cd98c5d3f921adc252eb7d8af6b916044b676a574747"
    "8df21fdc42f166880d97a2225cd5c9ea5e7b752f4cf81bbdbe98e542ee10e1c6"
    "ad868a6ac55c10d564fc23b8acff407daaf4ed2743520e02cda9680d9ea88e91"
    "029359c4cf5906b6ab5bf60fbb3f1a1c7c59acfc7e4fb4ad8e623c04d503a3dd"
    "4884604c8da8a53ce33db9ff8f1c5bb6bb97f37b39906bf41596555c1bcce9ed"
    "08a899cd760ff0899a1170c2f224b9c52997a0785b7fe170805fd3e8b1127659");

// Dummy encrypted data using the CENC 3.0 "cens" mode.  Encrypted using the
// key matching kKeyIdCtr.
const std::vector<uint8_t> kInputCens = a2b_hex(
    "1660a777a301908b5e8c15b465ed7fa434793f65a8be816278f9479d741a78e0"
    "b245e17629d63bbc2b15a5fa98b21daf62bdaf054113604ef19311adc5c3b74c"
    "6167dc3160f27c4920d2f9ae4a7f8dfd029dde48bce29b2751f27f12503d369d"
    "0ceb8b347e2884f51715f612badf15934aaa39db886e749afb8d8bdd29a18dd6"
    "2b0c4355935c4dcc5ec0153307154ace5bfedcdaa2b670052660889f3d64c4b3"
    "e363b16dc312d7e20373e873c760fae8b8bb39eccb6fe16e0198f6818ba24c30"
    "39dec55ef91ddc47c320ec284e24d1c8cdd62515e8ce5c0cb01bea2fbf36ce99"
    "246f5f8a2aca37719524dadffd4926a75a06402779a945d0b2c14a9c3f060a34");
const std::vector<uint8_t> kIvCens = a2b_hex(
    "a891b8000af53049d7b24bdc19074839");
const std::vector<uint8_t> kOutputCens = a2b_hex(
    "4bc4abcd79205e54188f04f99ea7e02534793f65a8be816278f9479d741a78e0"
    "b245e17629d63bbc2b15a5fa98b21daf62bdaf054113604ef19311adc5c3b74c"
    "6167dc3160f27c4920d2f9ae4a7f8dfd029dde48bce29b2751f27f12503d369d"
    "0ceb8b347e2884f51715f612badf15934aaa39db886e749afb8d8bdd29a18dd6"
    "2b0c4355935c4dcc5ec0153307154ace5bfedcdaa2b670052660889f3d64c4b3"
    "f6104e15275ecb58324fb8f25ccde60db8bb39eccb6fe16e0198f6818ba24c30"
    "39dec55ef91ddc47c320ec284e24d1c8cdd62515e8ce5c0cb01bea2fbf36ce99"
    "246f5f8a2aca37719524dadffd4926a75a06402779a945d0b2c14a9c3f060a34");

#endif
