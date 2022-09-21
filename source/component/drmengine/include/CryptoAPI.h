#ifndef CRYPTO_API_H_
#define CRYPTO_API_H_
#include <common/hi_type.h>
#include <utils/Errors.h>
#include <utils/Vector.h>
//#include <AString.h>
#include "DrmDefines.h"

using namespace android;

class CryptoPlugin;

class CryptoFactory
{
public:
    CryptoFactory() {}
    virtual ~CryptoFactory() {}

    virtual HI_BOOL isCryptoSchemeSupported(const HI_U8 uuid[HI_DRM_UUID_LEN]) const = 0;

    virtual status_t createPlugin(
        const HI_U8 uuid[HI_DRM_UUID_LEN], const HI_VOID* data, size_t size,
        CryptoPlugin** plugin) = 0;

private:
    CryptoFactory(const CryptoFactory&);
    CryptoFactory& operator=(const CryptoFactory&);
};

class CryptoPlugin
{

public:
    enum Mode
    {
        kMode_Unencrypted = 0,
        kMode_AES_CTR     = 1,

        // Neither key nor iv are being used in this mode.
        // Each subsample is encrypted w/ an iv of all zeroes.
        kMode_AES_WV      = 2,  // FIX constant
        kMode_AES_CBC     = 3,
    };

    struct SubSample
    {
        HI_U32 mNumBytesOfClearData;
        HI_U32 mNumBytesOfEncryptedData;
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
    virtual HI_BOOL requiresSecureDecoderComponent(const HI_CHAR* mime) const = 0;

    // To implement resolution constraints, the crypto plugin needs to know
    // the resolution of the video being decrypted.  The media player should
    // call this method when the resolution is determined and any time it
    // is subsequently changed.

    virtual HI_VOID notifyResolution(HI_U32 /* width */, HI_U32 /* height */) {}

    // A MediaDrm session may be associated with a MediaCrypto session.  The
    // associated MediaDrm session is used to load decryption keys
    // into the crypto/drm plugin.  The keys are then referenced by key-id
    // in the 'key' parameter to the decrypt() method.
    // Should return NO_ERROR on success, ERROR_DRM_SESSION_NOT_OPENED if
    // the session is not opened and a code from MediaErrors.h otherwise.
    virtual status_t setMediaDrmSession(const Vector<HI_U8>& /*sessionId */)
    {
        return -1;//ERROR_UNSUPPORTED;
    }

    // If the error returned falls into the range
    // ERROR_DRM_VENDOR_MIN..ERROR_DRM_VENDOR_MAX, errorDetailMsg should be
    // filled in with an appropriate string.
    // At the java level these special errors will then trigger a
    // MediaCodec.CryptoException that gives clients access to both
    // the error code and the errorDetailMsg.
    // Returns a non-negative result to indicate the number of bytes written
    // to the dstPtr, or a negative result to indicate an error.
    virtual ssize_t decrypt(
        HI_BOOL secure,
        const HI_U8 key[HI_DRM_KEY_LEN],
        const HI_U8 iv[HI_DRM_IV_LEN],
        Mode mode,
        const HI_VOID* srcPtr,
        const SubSample* subSamples, size_t numSubSamples,
        HI_VOID* dstPtr,
        HI_CHAR* errorDetailMsg) = 0;

private:
    CryptoPlugin(const CryptoPlugin&);
    CryptoPlugin& operator=(const CryptoPlugin&);
};

extern "C" {
    extern CryptoFactory* createCryptoFactory();
}

#endif  // CRYPTO_API_H_
