#ifndef CRYPTO_API_H_

#define CRYPTO_API_H_

#include <stdlib.h>
#include <map>
#include <list>
#include <memory>
#include <string>
#include <stdint.h>

namespace drmapi {

typedef int status_t;

struct CryptoPlugin;

struct CryptoFactory {
    CryptoFactory() {}
    virtual ~CryptoFactory() {}

    virtual bool isCryptoSchemeSupported(const uint8_t uuid[16]) const = 0;

    virtual status_t createPlugin(
            const uint8_t uuid[16], const void *data, size_t size,
            CryptoPlugin **plugin) = 0;

private:
    CryptoFactory(const CryptoFactory &);
    CryptoFactory &operator=(const CryptoFactory &);
};

struct CryptoPlugin {
    enum Mode {
        kMode_Unencrypted = 0,
        kMode_AES_CTR     = 1,
        kMode_AES_WV      = 2,
        kMode_AES_CBC     = 3,
    };

    struct SubSample {
        uint32_t mNumBytesOfClearData;
        uint32_t mNumBytesOfEncryptedData;
    };

    struct Pattern {
        // Number of blocks to be encrypted in the pattern. If zero, pattern
        // encryption is inoperative.
        uint32_t mEncryptBlocks;

        // Number of blocks to be skipped (left clear) in the pattern. If zero,
        // pattern encryption is inoperative.
        uint32_t mSkipBlocks;
    };

    CryptoPlugin() {}
    virtual ~CryptoPlugin() {}

    // If this method returns false, a non-secure decoder will be used to
    // decode the data after decryption. The decrypt API below will have
    // to support insecure decryption of the data (secure = false) for
    // media data of the given mime type.
    virtual bool requiresSecureDecoderComponent(const char *mime) const = 0;

    // If the error returned falls into the range
    // ERROR_DRM_VENDOR_MIN..ERROR_DRM_VENDOR_MAX, errorDetailMsg should be
    // filled in with an appropriate string.
    // At the java level these special errors will then trigger a
    // MediaCodec.CryptoException that gives clients access to both
    // the error code and the errorDetailMsg.
    // Returns a non-negative result to indicate the number of bytes written
    // to the dstPtr, or a negative result to indicate an error.
    virtual ssize_t decrypt(
            bool secure,
            const uint8_t key[16],
            const uint8_t iv[16],
            Mode mode,
            //const Pattern &pattern,
            const void *srcPtr,
            const SubSample *subSamples, size_t numSubSamples,
            void *dstPtr,
            char *errorDetailMsg) = 0;

private:
    CryptoPlugin(const CryptoPlugin &);
    CryptoPlugin &operator=(const CryptoPlugin &);
};

}  // namespace android

extern "C" {
    extern drmapi::CryptoFactory *createCryptoFactory();
}

#endif  // CRYPTO_API_H_

