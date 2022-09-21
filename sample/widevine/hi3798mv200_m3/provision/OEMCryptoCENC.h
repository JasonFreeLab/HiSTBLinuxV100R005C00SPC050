// Copyright 2013 Google Inc. All Rights Reserved.

/*********************************************************************
 * OEMCryptoCENC.h
 *
 * Reference APIs needed to support Widevine's crypto algorithms.
 *********************************************************************/

#ifndef OEMCRYPTO_CENC_H_
#define OEMCRYPTO_CENC_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t OEMCrypto_SESSION;

typedef enum OEMCryptoResult {
    OEMCrypto_SUCCESS                            = 0,
    OEMCrypto_ERROR_INIT_FAILED                  = 1,
    OEMCrypto_ERROR_TERMINATE_FAILED             = 2,
    OEMCrypto_ERROR_OPEN_FAILURE                 = 3,
    OEMCrypto_ERROR_CLOSE_FAILURE                = 4,
    OEMCrypto_ERROR_ENTER_SECURE_PLAYBACK_FAILED = 5,
    OEMCrypto_ERROR_EXIT_SECURE_PLAYBACK_FAILED  = 6,
    OEMCrypto_ERROR_SHORT_BUFFER                 = 7,
    OEMCrypto_ERROR_NO_DEVICE_KEY                = 8,
    OEMCrypto_ERROR_NO_ASSET_KEY                 = 9,
    OEMCrypto_ERROR_KEYBOX_INVALID               = 10,
    OEMCrypto_ERROR_NO_KEYDATA                   = 11,
    OEMCrypto_ERROR_NO_CW                        = 12,
    OEMCrypto_ERROR_DECRYPT_FAILED               = 13,
    OEMCrypto_ERROR_WRITE_KEYBOX                 = 14,
    OEMCrypto_ERROR_WRAP_KEYBOX                  = 15,
    OEMCrypto_ERROR_BAD_MAGIC                    = 16,
    OEMCrypto_ERROR_BAD_CRC                      = 17,
    OEMCrypto_ERROR_NO_DEVICEID                  = 18,
    OEMCrypto_ERROR_RNG_FAILED                   = 19,
    OEMCrypto_ERROR_RNG_NOT_SUPPORTED            = 20,
    OEMCrypto_ERROR_SETUP                        = 21,
    OEMCrypto_ERROR_OPEN_SESSION_FAILED          = 22,
    OEMCrypto_ERROR_CLOSE_SESSION_FAILED         = 23,
    OEMCrypto_ERROR_INVALID_SESSION              = 24,
    OEMCrypto_ERROR_NOT_IMPLEMENTED              = 25,
    OEMCrypto_ERROR_NO_CONTENT_KEY               = 26,
    OEMCrypto_ERROR_CONTROL_INVALID              = 27,
    OEMCrypto_ERROR_UNKNOWN_FAILURE              = 28,
    OEMCrypto_ERROR_INVALID_CONTEXT              = 29,
    OEMCrypto_ERROR_SIGNATURE_FAILURE            = 30,
    OEMCrypto_ERROR_TOO_MANY_SESSIONS            = 31,
    OEMCrypto_ERROR_INVALID_NONCE                = 32,
    OEMCrypto_ERROR_TOO_MANY_KEYS                = 33,
    OEMCrypto_ERROR_DEVICE_NOT_RSA_PROVISIONED   = 34,
    OEMCrypto_ERROR_INVALID_RSA_KEY              = 35,
    OEMCrypto_ERROR_KEY_EXPIRED                  = 36,
    OEMCrypto_ERROR_INSUFFICIENT_RESOURCES       = 37,
    OEMCrypto_ERROR_INSUFFICIENT_HDCP            = 38,
} OEMCryptoResult;

/*
 * OEMCrypto_DestBufferDesc
 *  Describes the type and access information for the memory to receive
 *  decrypted data.
 *
 *  The OEMCrypto API supports a range of client device architectures.
 *  Different architectures have different methods for acquiring and securing
 *  buffers that will hold portions of the audio or video stream after
 *  decryption.  Three basic strategies are recognized for handling decrypted
 *  stream data:
 *  1. Return the decrypted data in the clear into normal user memory
 *     (ClearBuffer). The caller uses normal memory allocation methods to
 *     acquire a buffer, and supplies the memory address of the buffer in the
 *     descriptor.
 *  2. Place the decrypted data into protected memory (SecureBuffer).  The
 *     caller uses a platform-specific method to acquire the protected buffer
 *     and a user-memory handle that references it.  The handle is supplied
 *     to the decrypt call in the descriptor.
 *  3. Place the decrypted data directly into the audio or video decoder fifo
 *     (Direct). The caller will use platform-specific methods to initialize
 *     the fifo and the decoders.  The decrypted stream data is not accessible
 *     to the caller.
 *
 *  Specific fields are as follows:
 *
 *  (type == OEMCrypto_BufferType_Clear)
 *      address - Address of start of user memory buffer.
 *      max_length - Size of user memory buffer.
 *  (type == OEMCrypto_BufferType_Secure)
 *      buffer - handle to a platform-specific secure buffer.
 *      max_length - Size of platform-specific secure buffer.
 *  (type == OEMCrypto_BufferType_Direct)
 *      is_video - If true, decrypted bytes are routed to the video
 *                 decoder.  If false, decrypted bytes are routed to the
 *                 audio decoder.
 */
typedef enum OEMCryptoBufferType {
    OEMCrypto_BufferType_Clear,
    OEMCrypto_BufferType_Secure,
    OEMCrypto_BufferType_Direct
} OEMCryptoBufferType;

typedef struct {
    OEMCryptoBufferType type;
    union {
        struct {                   // type == OEMCrypto_BufferType_Clear
            uint8_t* address;
            size_t max_length;
        } clear;
        struct {                   // type == OEMCrypto_BufferType_Secure
            void* handle;
            size_t max_length;
            size_t offset;
        } secure;
        struct {                   // type == OEMCrypto_BufferType_Direct
            bool is_video;
        } direct;
    } buffer;
} OEMCrypto_DestBufferDesc;

/** OEMCryptoCipherMode is used in LoadKeys to prepare a key for either CTR
 * decryption or CBC decryption.
 */
typedef enum OEMCryptoCipherMode {
    OEMCrypto_CipherMode_CTR,
    OEMCrypto_CipherMode_CBC,
} OEMCryptoCipherMode;

/*
 * OEMCrypto_KeyObject
 *  Points to the relevant fields for a content key.  The fields are extracted
 *  from the License Response message offered to OEMCrypto_LoadKeys().  Each
 *  field points to one of the components of the key.  Key data, key control,
 *  and both IV fields are 128 bits (16 bytes):
 *    key_id - the unique id of this key.
 *    key_id_length - the size of key_id.
 *    key_data_iv - the IV for performing AES-128-CBC decryption of the
 *        key_data field.
 *    key_data - the key data.  It is encrypted (AES-128-CBC) with the
 *        session's derived encrypt key and the key_data_iv.
 *    key_control_iv - the IV for performing AES-128-CBC decryption of the
 *        key_control field.
 *    key_control - the key control block.  It is encrypted (AES-128-CBC) with
 *        the content key from the key_data field.
 *    cipher_mode - whether the key should be prepared for CTR mode or CBC mode
 *        when used in later calls to DecryptCENC.
 *
 *  The memory for the OEMCrypto_KeyObject fields is allocated and freed
 *  by the caller of OEMCrypto_LoadKeys().
 */
typedef struct {
    const uint8_t* key_id;
    size_t         key_id_length;
    const uint8_t* key_data_iv;
    const uint8_t* key_data;
    size_t         key_data_length;
    const uint8_t* key_control_iv;
    const uint8_t* key_control;
    OEMCryptoCipherMode cipher_mode;
} OEMCrypto_KeyObject;

/*
 * OEMCrypto_KeyRefreshObject
 *  Points to the relevant fields for renewing a content key.  The fields are
 *  extracted from the License Renewal Response message offered to
 *  OEMCrypto_RefreshKeys().  Each field points to one of the components of
 *  the key.
 *    key_id - the unique id of this key.
 *    key_control_iv - the IV for performing AES-128-CBC decryption of the
 *        key_control field. 16 bytes.
 *    key_control - the key control block.  It is encrypted (AES-128-CBC) with
 *        the content key from the key_data field. 16 bytes.
 *
 *  The key_data is unchanged from the original OEMCrypto_LoadKeys() call. Some
 *  Key Control Block fields, especially those related to key lifetime, may
 *  change.
 *
 *  The memory for the OEMCrypto_KeyRefreshObject fields is allocated and freed
 *  by the caller of OEMCrypto_RefreshKeys().
 */
typedef struct {
    const uint8_t* key_id;
    size_t key_id_length;
    const uint8_t* key_control_iv;
    const uint8_t* key_control;
} OEMCrypto_KeyRefreshObject;

/*
 * OEMCrypto_Algorithm
 * This is a list of valid algorithms for OEMCrypto_Generic_* functions.
 * Some are valid for encryption/decryption, and some for signing/verifying.
 */
typedef enum OEMCrypto_Algorithm {
    OEMCrypto_AES_CBC_128_NO_PADDING = 0,
    OEMCrypto_HMAC_SHA256            = 1,
} OEMCrypto_Algorithm;

/*
 * Flags indicating data endpoints in OEMCrypto_DecryptCENC.
 */
#define OEMCrypto_FirstSubsample 1
#define OEMCrypto_LastSubsample  2

/* OEMCrypto_CENCEncryptPatternDesc
 *  This is used in OEMCrypto_DecryptCENC to indicate the encrypt/skip pattern
 *  used, as specified in the CENC standard.
 */
typedef struct {
  size_t encrypt;  // number of 16 byte blocks to decrypt.
  size_t skip;     // number of 16 byte blocks to leave in clear.
  size_t offset;   // offset into the pattern in blocks for this call.
} OEMCrypto_CENCEncryptPatternDesc;

/*
 *  OEMCrypto_Usage_Entry_Status.
 *  Valid values for status in the usage table.
 */
typedef enum OEMCrypto_Usage_Entry_Status {
  kUnused = 0,
  kActive = 1,
  kInactive = 2
} OEMCrypto_Usage_Entry_Status;

/*
 * OEMCrypto_PST_Report is used to report an entry from the Usage Table.
 */
typedef struct {
  uint8_t signature[20]; //  -- HMAC SHA1 of the rest of the report.
  uint8_t status;  // current status of entry. (OEMCrypto_Usage_Entry_Status)
  uint8_t clock_security_level;
  uint8_t pst_length;
  uint8_t padding;                         // make int64's word aligned.
  int64_t seconds_since_license_received;  // now - time_of_license_received
  int64_t seconds_since_first_decrypt;     // now - time_of_first_decrypt
  int64_t seconds_since_last_decrypt;      // now - time_of_last_decrypt
  uint8_t pst[];
} __attribute__((packed)) OEMCrypto_PST_Report;

/*
 *  OEMCrypto_Clock_Security_Level.
 *  Valid values for clock_security_level in OEMCrypto_PST_Report.
 */
typedef enum OEMCrypto_Clock_Security_Level {
  kInsecureClock = 0,
  kSecureTimer = 1,
  kSecureClock = 2,
  kHardwareSecureClock = 3
} OEMCrypto_Clock_Security_Level;

typedef enum RSA_Padding_Scheme {
  kSign_RSASSA_PSS     = 0x1, // RSASSA-PSS with SHA1.
  kSign_PKCS1_Block1   = 0x2, // PKCS1 with block type 1 padding (only).
} RSA_Padding_Scheme;

/*
 * OEMCrypto_HDCP_Capability is used in the key control block to enforce HDCP
 * level, and in GetHDCPCapability for reporting.
 */
typedef enum OEMCrypto_HDCP_Capability {
  HDCP_NONE  = 0,  // No HDCP supported, no secure data path.
  HDCP_V1    = 1,  // HDCP version 1.0
  HDCP_V2    = 2,  // HDCP version 2.0
  HDCP_V2_1  = 3,  // HDCP version 2.1
  HDCP_V2_2  = 4,  // HDCP version 2.2 Type 1.
  HDCP_NO_DIGITAL_OUTPUT = 0xff  // No digital output.
} OEMCrypto_HDCP_Capability;

/*
 * Obfuscation Renames.
 */
#define OEMCrypto_Initialize               _oecc01
#define OEMCrypto_Terminate                _oecc02
#define OEMCrypto_InstallKeybox            _oecc03
#define OEMCrypto_GetKeyData               _oecc04
#define OEMCrypto_IsKeyboxValid            _oecc05
#define OEMCrypto_GetRandom                _oecc06
#define OEMCrypto_GetDeviceID              _oecc07
#define OEMCrypto_WrapKeybox               _oecc08
#define OEMCrypto_OpenSession              _oecc09
#define OEMCrypto_CloseSession             _oecc10
#define OEMCrypto_DecryptCTR_V10           _oecc11
#define OEMCrypto_GenerateDerivedKeys      _oecc12
#define OEMCrypto_GenerateSignature        _oecc13
#define OEMCrypto_GenerateNonce            _oecc14
#define OEMCrypto_LoadKeys_V8              _oecc15
#define OEMCrypto_RefreshKeys              _oecc16
#define OEMCrypto_SelectKey                _oecc17
#define OEMCrypto_RewrapDeviceRSAKey       _oecc18
#define OEMCrypto_LoadDeviceRSAKey         _oecc19
#define OEMCrypto_GenerateRSASignature_V8  _oecc20
#define OEMCrypto_DeriveKeysFromSessionKey _oecc21
#define OEMCrypto_APIVersion               _oecc22
#define OEMCrypto_SecurityLevel            _oecc23
#define OEMCrypto_Generic_Encrypt          _oecc24
#define OEMCrypto_Generic_Decrypt          _oecc25
#define OEMCrypto_Generic_Sign             _oecc26
#define OEMCrypto_Generic_Verify           _oecc27
#define OEMCrypto_GetHDCPCapability_V9     _oecc28
#define OEMCrypto_SupportsUsageTable       _oecc29
#define OEMCrypto_UpdateUsageTable         _oecc30
#define OEMCrypto_DeactivateUsageEntry     _oecc31
#define OEMCrypto_ReportUsage              _oecc32
#define OEMCrypto_DeleteUsageEntry         _oecc33
#define OEMCrypto_DeleteUsageTable         _oecc34
#define OEMCrypto_LoadKeys_V9_or_V10       _oecc35
#define OEMCrypto_GenerateRSASignature     _oecc36
#define OEMCrypto_GetMaxNumberOfSessions   _oecc37
#define OEMCrypto_GetNumberOfOpenSessions  _oecc38
#define OEMCrypto_IsAntiRollbackHwPresent  _oecc39
#define OEMCrypto_CopyBuffer               _oecc40
#define OEMCrypto_QueryKeyControl          _oecc41
#define OEMCrypto_LoadTestKeybox           _oecc42
#define OEMCrypto_ForceDeleteUsageEntry    _oecc43
#define OEMCrypto_GetHDCPCapability        _oecc44
#define OEMCrypto_LoadTestRSAKey           _oecc45
#define OEMCrypto_Security_Patch_Level     _oecc46
#define OEMCrypto_LoadKeys                 _oecc47
#define OEMCrypto_DecryptCENC              _oecc48


/*
 * OEMCrypto_Initialize
 *
 * Description:
 *   Initialize the crypto firmware/hardware.
 *
 * Parameters:
 *   N/A
 *
 * Threading:
 *   No other function calls will be made while this function is running. This
 *   function will not be called again before OEMCrypto_Terminate.
 *
 * Returns:
 *   OEMCrypto_SUCCESS success
 *   OEMCrypto_ERROR_INIT_FAILED failed to initialize crypto hardware
 *
 * Version:
 *   This method is supported by all API versions.
 */
OEMCryptoResult OEMCrypto_Initialize(void);

/*
 * OEMCrypto_Terminate
 *
 * Description:
 *   Closes the crypto operation and releases all related resources.
 *
 * Parameters:
 *   N/A
 *
 * Threading:
 *   No other OEMCrypto calls are made while this function is running.  After
 *   this function is called, no other OEMCrypto calls will be made until another
 *   call to OEMCrypto_Initialize is made.
 *
 * Returns:
 *   OEMCrypto_SUCCESS success
 *   OEMCrypto_ERROR_TERMINATE_FAILED failed to de-initialize crypto hardware
 *
 * Version:
 *   This method is supported by all API versions.
 */
OEMCryptoResult OEMCrypto_Terminate(void);

/*
 * OEMCrypto_OpenSession
 *
 * Description:
 *   Open a new crypto security engine context.  The security engine hardware and
 *   firmware shall acquire resources that are needed to support the session, and
 *   return a session handle that identifies that session in future calls.
 *
 * Parameters:
 *   session (out) - an opaque handle that the crypto firmware uses to identify the
 *   session.
 *
 * Threading:
 *   No other Open/Close session calls will be made while this function is
 *   running. Functions on existing sessions may be called while this function
 *   is active.
 *
 * Returns:
 *   OEMCrypto_SUCCESS success
 *   OEMCrypto_ERROR_TOO_MANY_SESSIONS failed because too many sessions are open
 *   OEMCrypto_ERROR_OPEN_SESSION_FAILED failed to initialize the crypto session
 *
 * Version:
 *   This method changed in API version 5.
 */
OEMCryptoResult OEMCrypto_OpenSession(OEMCrypto_SESSION *session);

/*
 * OEMCrypto_CloseSession
 *
 * Description:
 *   Closes the crypto security engine session and frees any associated
 *   resources.
 *
 * Parameters:
 *   session (in) - handle for the session to be closed.
 *
 * Threading:
 *   No other Open/Close session calls will be made while this function is
 *   running. Functions on existing sessions may be called while this function
 *   is active.
 *
 * Returns:
 *   OEMCrypto_SUCCESS success
 *   OEMCrypto_ERROR_INVALID_SESSION no open session with that id.
 *   OEMCrypto_ERROR_CLOSE_SESSION_FAILED failed to terminate the crypto session
 *
 * Version:
 *   This method changed in API version 5.
 */
OEMCryptoResult OEMCrypto_CloseSession(OEMCrypto_SESSION session);

/*
 * OEMCrypto_GenerateDerivedKeys
 *
 * Description:
 *   Generates three secondary keys -- mac_key_server, mac_key_client, and
 *   encrypt_key -- for handling signing and content key decryption under the
 *   license server protocol for AES CTR mode.
 *
 *   Refer to document "Widevine Modular DRM Security Integration Guide for
 *   CENC" for details.  This function computes the AES-128-CMAC of the
 *   enc_key_context and stores it in secure memory as the encrypt_key.  It
 *   then computes four cycles of AES-128-CMAC of the mac_key_context and
 *   stores it in the mac_keys.  The first two cycles are used for
 *   mac_key_server and the second two cycles are used for mac_key_client.
 *   These three keys will be stored until the next call to LoadKeys.
 *
 * Parameters:
 *   session (in) - handle for the session to be used.
 *   mac_key_context (in) - pointer to memory containing context data for
 *                          computing the HMAC generation key.
 *   mac_key_context_length (in) - length of the HMAC key context data, in bytes.
 *   enc_key_context (in) - pointer to memory containing context data for
 *                          computing the encryption key.
 *   enc_key_context_length (in) - length of the encryption key context data, in
 *                                 bytes.
 *
 *
 * Results:
 *  mac_key_server: the 256 bit mac key is generated and stored in secure memory.
 *  mac_key_client: the 256 bit mac key is generated and stored in secure memory.
 *  enc_key: the 128 bit encryption key is generated and stored in secure memory.
 *
 * Threading:
 *   This function may be called simultaneously with functions on other sessions,
 *   but not with other functions on this session.
 *
 * Returns:
 *   OEMCrypto_SUCCESS success
 *   OEMCrypto_ERROR_NO_DEVICE_KEY
 *   OEMCrypto_ERROR_INVALID_SESSION
 *   OEMCrypto_ERROR_INVALID_CONTEXT
 *   OEMCrypto_ERROR_INSUFFICIENT_RESOURCES
 *   OEMCrypto_ERROR_UNKNOWN_FAILURE
 *
 * Version:
 *   This method changed in API version 8.
 */
OEMCryptoResult OEMCrypto_GenerateDerivedKeys(
                            OEMCrypto_SESSION session,
                            const uint8_t *mac_key_context,
                            uint32_t mac_key_context_length,
                            const uint8_t *enc_key_context,
                            uint32_t enc_key_context_length);

/*
 * OEMCrypto_GenerateNonce
 *
 * Description:
 *   Generates a 32-bit nonce to detect possible replay attack on the key
 *   control block.  The nonce is stored in secure memory and will be used
 *   for the next call to LoadKeys.
 *
 *   Because the nonce will be used to prevent replay attacks, it is desirable
 *   that a rogue application cannot rapidly call this function until a
 *   repeated nonce is created randomly.  With this in mind, if more than 20
 *   nonces are requested within one second, OEMCrypto will return an error
 *   after the 20th and not generate any more nonces for the rest of the
 *   second.  After an error, if the application waits at least one second
 *   before requesting more nonces, then OEMCrypto will reset the error
 *   condition and generate valid nonces again.
 *
 * Parameters:
 *   session (in) - crypto session identifier.
 *   nonce (out) - pointer to memory to received the computed nonce.
 *
 * Results:
 *   nonce: the nonce is also stored in secure memory.  At least 4 nonces should be
 *   stored for each session.
 *
 * Threading:
 *   This function may be called simultaneously with functions on other sessions,
 *   but not with other functions on this session.
 *
 * Returns:
 *   OEMCrypto_SUCCESS success
 *   OEMCrypto_ERROR_INVALID_SESSION
 *   OEMCrypto_ERROR_INSUFFICIENT_RESOURCES
 *   OEMCrypto_ERROR_UNKNOWN_FAILURE
 *
 * Version:
 *   This method changed in API version 5.
 */
OEMCryptoResult OEMCrypto_GenerateNonce(
                            OEMCrypto_SESSION session,
                            uint32_t* nonce);

/*
 * OEMCrypto_GenerateSignature
 *
 * Description:
 *   Generates a HMAC-SHA256 signature for license request signing under the
 *   license server protocol for AES CTR mode. This uses the key mac_key_client.
 *
 *   NOTE: OEMCrypto_GenerateDerivedKeys() must be called first to establish the
 *       mac_key_client.
 *
 *   Refer to document "Widevine Modular DRM Security Integration Guide for
 *   CENC" for details.
 *
 * Parameters:
 *   session (in) - crypto session identifier.
 *   message (in) - pointer to memory containing message to be signed.
 *   message_length (in) - length of the message, in bytes.
 *   signature (out) - pointer to memory to received the computed signature.  May be
 *                     null on the first call in order to find required buffer size.
 *   signature_length (in/out) - (in) length of the signature buffer, in bytes.
 *   (out) actual length of the signature, in bytes.
 *
 * Threading:
 *   This function may be called simultaneously with functions on other sessions,
 *   but not with other functions on this session.
 *
 * Returns:
 *   OEMCrypto_SUCCESS success
 *   OEMCrypto_ERROR_INVALID_SESSION
 *   OEMCrypto_ERROR_SHORT_BUFFER if signature buffer is not large enough to hold
 *                                buffer.
 *   OEMCrypto_ERROR_INSUFFICIENT_RESOURCES
 *   OEMCrypto_ERROR_UNKNOWN_FAILURE
 *
 * Version:
 *   This method changed in API version 5.
 */
OEMCryptoResult OEMCrypto_GenerateSignature(
                            OEMCrypto_SESSION session,
                            const uint8_t* message,
                            size_t message_length,
                            uint8_t* signature,
                            size_t* signature_length);

/*
 * OEMCrypto_LoadKeys
 *
 * Description:
 *   Installs a set of keys for performing decryption in the current session.
 *
 *   The relevant fields have been extracted from the License Response protocol
 *   message, but the entire message and associated signature are provided so
 *   the message can be verified (using HMAC-SHA256 with the derived
 *   mac_key_server). If the signature verification fails, ignore all other
 *   arguments and return OEMCrypto_ERROR_SIGNATURE_FAILURE.  Otherwise, add the
 *   keys to the session context.
 *
 *   The keys will be decrypted using the current encrypt_key (AES-128-CBC) and
 *   the IV given in the KeyObject.  Each key control block will be decrypted
 *   using the first 128 bits of the corresponding content key (AES-128-CBC) and
 *   the IV given in the KeyObject.
 *
 *   If it is not null, enc_mac_keys will be used to create new mac_keys.  After
 *   all keys have been decrypted and validated, the new mac_keys are decrypted
 *   with the current encrypt_key and the offered IV.  The new mac_keys replaces
 *   the current mac_keys for future calls to OEMCrypto_RefreshKeys().  The first
 *   256 bits of the mac_keys become the mac_key[server] and the following 256
 *   bits of the mac_keys become the mac_key[client].  If enc_mac_keys is null,
 *   then there will not be a call to OEMCrypto_RefreshKeys for this session and
 *   the current mac_keys should remain unchanged.
 *
 *   The mac_key and encrypt_key were generated and stored by the previous call
 *   to OEMCrypto_GenerateDerivedKeys().  The nonce was generated and stored by
 *   the previous call to OEMCrypto_GenerateNonce().
 *
 *   This session’s elapsed time clock is started at 0.  The clock will be used
 *   in OEMCrypto_DecryptCENC().
 *
 *   NOTE: The calling software must have previously established the mac_keys
 *   and encrypt_key with a call to OEMCrypto_GenerateDerivedKeys(),
 *   OEMCrypto_DeriveKeysFromSessionKey(), or a previous call to
 *   OEMCrypto_LoadKeys().
 *
 *   Refer to document "Widevine Modular DRM Security Integration Guide for
 *   CENC" for details.
 *
 * Verification:
 *   The following checks should be performed.  If any check fails, an error is
 *   returned, and none of the keys are loaded.
 *
 *   1. The signature of the message shall be computed, and the API shall verify
 *   the computed signature matches the signature passed in.  If not, return
 *   OEMCrypto_ERROR_SIGNATURE_FAILURE.  The signature verification shall use a
 *   constant-time algorithm (a signature mismatch will always take the same time
 *   as a successful comparison).
 *
 *   2. The enc_mac_keys pointer must be either null, or point inside the
 *   message. If the pointer enc_mac_keys is not null, the API shall verify
 *   that the two pointers enc_mac_keys_iv and enc_mac_keys point to locations in
 *   the message.  I.e.  (message <= p && p < message+message_length)for p in
 *   each of enc_mac_keys_iv, enc_mac_keys. If not, return
 *   OEMCrypto_ERROR_INVALID_CONTEXT.
 *
 *   3. The API shall verify that each pointer in each KeyObject points to a
 *   location in the message.  I.e.  (message <= p && p < message+message_length)
 *   for p in each of key_id, key_data_iv, key_data, key_control_iv,
 *   key_control. If not, return OEMCrypto_ERROR_INVALID_CONTEXT.
 *
 *   4. Each key’s control block, after decryption, shall have a valid
 *   verification field. If not, return OEMCrypto_ERROR_INVALID_CONTEXT.
 *
 *   5. If any key control block has the Nonce_Enabled bit set, that key’s Nonce
 *   field shall match the nonce generated by the current nonce.  If not, return
 *   OEMCrypto_ERROR_INVALID_NONCE.  If there is a match, remove that nonce from
 *   the cache.  Note that all the key control blocks in a particular call shall
 *   have the same nonce value.
 *
 *   6. If any key control block has the Require_AntiRollback_Hardware bit set,
 *   and the device does not protect the usage table from rollback, then do not
 *   load the keys and return OEMCrypto_ERROR_UNKNOWN_FAILURE.
 *
 *   7. If the key control block has a nonzero Replay_Control, then the
 *   verification described below is also performed.
 *
 *   8. If num_keys == 0, then return OEMCrypto_ERROR_INVALID_CONTEXT.
 *
 *   Usage Table and Provider Session Token (pst):
 *
 *   If a key control block has a nonzero value for Replay_Control, then all keys
 *   in this license will have the same value.  In this case, the following
 *   additional checks are performed.
 *
 *   The pointer pst must not be null, and must point to a location in the
 *   message.  If not, return OEMCrypto_ERROR_INVALID_CONTEXT.
 *
 *   - If Replay_Control is 1 = Nonce_Required, then OEMCrypto will perform a
 *     nonce check as described above.   OEMCrypto will verify that the table does
 *     not already have an entry for the value of pst passed in as a parameter ---
 *     if an entry already exists, an error OEMCrypto_ERROR_INVALID_CONTEXT is
 *     returned and no keys are loaded.  OEMCrypto will then create a new entry in
 *     the table, and mark this session as using this new entry.  This prevents the
 *     license from being loaded more than once, and will be used for online
 *     streaming.
 *
 *   - If Replay_Control is 2 = "Require existing Session Usage table entry or
 *     Nonce", then OEMCrypto will check the Session Usage table for an existing
 *     entry with the same pst.
 *
 *   --- If the pst is not in the table yet, a new entry will be created in the
 *       table and this session shall use the new entry. In that case, the nonce
 *       will be verified for each key.
 *
 *   --- If an existing usage table entry is found, then this session will use
 *       that entry.  In that case, the nonce will not be verified for each key.
 *       Also, the entry’s mac keys will be verified against the current
 *       session’s mac keys.  This allows an offline license to be reloaded but
 *       maintain continuity of the playback times from one session to the next.
 *
 *   - If the nonce is not valid and an existing entry is not found, the return
 *     error is OEMCrypto_ERROR_INVALID_NONCE.
 *
 *   Note: If LoadKeys updates the mac keys, then the new updated mac keys will
 *   be used in the Usage Table.  If LoadKeys does not update the mac keys, the
 *   existing session mac keys are stored in the usage table.
 *
 *   Sessions that are associated with an entry will need to be able to update
 *   and verify the status of the entry, and the time stamps in the entry.
 *
 *   Devices that do not support the Usage Table will return
 *   OEMCrypto_ERROR_INVALID_CONTEXT if the Replay_Control is nonzero.
 *
 *   Note: If LoadKeys creates a new entry in the usage table, OEMCrypto will
 *   increment the Usage Table’s generation number, and then sign, encrypt, and
 *   save the Usage Table.
 *
 * Parameters:
 *   session (in) - crypto session identifier.
 *   message (in) - pointer to memory containing message to be verified.
 *   message_length (in) - length of the message, in bytes.
 *   signature (in) - pointer to memory containing the signature.
 *   signature_length (in) - length of the signature, in bytes.
 *   enc_mac_keys_iv (in) - IV for decrypting new mac_key.  Size is 128 bits.
 *   enc_mac_keys (in) - encrypted mac_keys for generating new mac_keys. Size is
 *                       512 bits.
 *   num_keys (in) - number of keys present.
 *   key_array (in) - set of keys to be installed.
 *   pst (in) - the Provider Session Token.
 *   pst_length (in) - the length of pst.
 *
 * Threading:
 *   This function may be called simultaneously with functions on other sessions,
 *   but not with other functions on this session.
 *
 * Returns:
 *   OEMCrypto_SUCCESS success
 *   OEMCrypto_ERROR_NO_DEVICE_KEY
 *   OEMCrypto_ERROR_INVALID_SESSION
 *   OEMCrypto_ERROR_INVALID_CONTEXT
 *   OEMCrypto_ERROR_SIGNATURE_FAILURE
 *   OEMCrypto_ERROR_INVALID_NONCE
 *   OEMCrypto_ERROR_TOO_MANY_KEYS
 *   OEMCrypto_ERROR_UNKNOWN_FAILURE
 *
 * Version:
 *   This method changed in API version 11.
 */
OEMCryptoResult OEMCrypto_LoadKeys(OEMCrypto_SESSION session,
                                   const uint8_t* message,
                                   size_t message_length,
                                   const uint8_t* signature,
                                   size_t signature_length,
                                   const uint8_t* enc_mac_keys_iv,
                                   const uint8_t* enc_mac_keys,
                                   size_t num_keys,
                                   const OEMCrypto_KeyObject* key_array,
                                   const uint8_t* pst,
                                   size_t pst_length);

/*
 * OEMCrypto_RefreshKeys
 *
 * Description:
 *   Updates an existing set of keys for continuing decryption in the
 *   current session.
 *
 *   The relevant fields have been extracted from the Renewal Response protocol
 *   message, but the entire message and associated signature are provided so the
 *   message can be verified (using HMAC-SHA256 with the current
 *   mac_key[server]). If any verification step fails, an error is returned.
 *   Otherwise, the key table in trusted memory is updated using the key_control
 *   block. When updating an entry in the table, only the duration, nonce, and
 *   nonce_enabled fields are used.  All other key control bits are not modified.
 *
 *   NOTE: OEMCrypto_GenerateDerivedKeys() or OEMCrypto_LoadKeys() must be called
 *   first to establish the mac_key[server].
 *
 *   This session’s elapsed time clock is reset to 0 when this function is called.
 *   The elapsed time clock is used in OEMCrypto_DecryptCENC().
 *
 *   This function does not add keys to the key table.  It is only used to update a
 *   key control block license duration. Refer to the License Signing and
 *   Verification section above for more details.  This function is used to update
 *   the duration of a key, only.  It is not used to update key control bits.
 *
 *   If the KeyRefreshObject’s key_control_iv is null, then the key_control is not
 *   encrypted.  If the key_control_iv is specified, then key_control is encrypted
 *   with the first 128 bits of the corresponding content key.
 *
 *   If the KeyRefreshObject’s key_id is null, then this refresh object should be
 *   used to update the duration of all keys for the current session.  In this
 *   case, key_control_iv will also be null and the control block will not be
 *   encrypted.
 *
 *
 * Verification:
 *   The following checks should be performed.  If any check fails, an error is
 *   returned, and none of the keys are loaded.
 *
 *   1. The signature of the message shall be computed, and the API shall verify
 *   the computed signature matches the signature passed in.  If not, return
 *   OEMCrypto_ERROR_SIGNATURE_FAILURE. The signature verification shall use a
 *   constant-time algorithm (a signature mismatch will always take the same time
 *   as a successful comparison).
 *
 *   2. The API shall verify that each pointer in each KeyObject points to a
 *   location in the message, or is null.  I.e.  (message <= p && p <
 *   message+message_length) for p in each of key_id,key_control_iv,
 *   key_control. If not, return OEMCrypto_ERROR_INVALID_CONTEXT.
 *
 *   3. Each key’s control block shall have a valid verification field. If not,
 *   return OEMCrypto_ERROR_INVALID_CONTEXT.
 *
 *   4. If the key control block has the Nonce_Enabled bit set, the Nonce field
 *   shall match one of the nonces in the cache.  If not, return
 *   OEMCrypto_ERROR_INVALID_NONCE. If there is a match, remove that nonce from the
 *   cache.   Note that all the key control blocks in a particular call shall have
 *   the same nonce value.
 *
 * Parameters:
 *   session (in) - crypto session identifier.
 *   message (in) - pointer to memory containing message to be verified.
 *   message_length (in) - length of the message, in bytes.
 *   signature (in) - pointer to memory containing the signature.
 *   signature_length (in) - length of the signature, in bytes.
 *   num_keys (in) - number of keys present.
 *   key_array (in) - set of key updates.
 *
 * Threading:
 *   This function may be called simultaneously with functions on other sessions,
 *   but not with other functions on this session.
 *
 * Returns:
 *   OEMCrypto_SUCCESS success
 *   OEMCrypto_ERROR_NO_DEVICE_KEY
 *   OEMCrypto_ERROR_INVALID_SESSION
 *   OEMCrypto_ERROR_INVALID_CONTEXT
 *   OEMCrypto_ERROR_INVALID_NONCE
 *   OEMCrypto_ERROR_SIGNATURE_FAILURE
 *   OEMCrypto_ERROR_INSUFFICIENT_RESOURCES
 *   OEMCrypto_ERROR_UNKNOWN_FAILURE
 *
 * Version:
 *   This method changed in API version 8.
 */
OEMCryptoResult
OEMCrypto_RefreshKeys(OEMCrypto_SESSION session,
                      const uint8_t* message,
                      size_t message_length,
                      const uint8_t* signature,
                      size_t signature_length,
                      size_t num_keys,
                      const OEMCrypto_KeyRefreshObject* key_array);

/*
 * OEMCrypto_QueryKeyControl
 *
 * Description:
 *   Returns the decrypted key control block for the given key_id.  This function
 *   is for application developers to debug license server and key timelines.
 *   It only returns a key control block if LoadKeys was successful, otherwise
 *   it returns OEMCrypto_ERROR_NO_CONTENT_KEY. The developer of the OEMCrypto
 *   library must be careful that the keys themselves are not accidentally
 *   revealed.
 *
 * Note:
 *   Returns control block in original, network byte order. If OEMCrypto
 *   converts fields to host byte order internally for storage, it should
 *   convert them back. Since OEMCrypto might not store the nonce or validation
 *   fields, values of 0 may be used instead.
 *
 * Verification
 *   The following checks should be performed.
 *   1) If key_id is null, return OEMCrypto_ERROR_INVALID_CONTEXT.
 *   2) If key_control_block_length is null, return OEMCrypto_ERROR_INVALID_CONTEXT.
 *   3) If *key_control_block_length is less than the length of a key control block,
 *      set it to the correct value, and return OEMCrypto_ERROR_SHORT_BUFFER.
 *   4) If key_control_block is null, return OEMCrypto_ERROR_INVALID_CONTEXT.
 *   5) If the specified key has not been loaded, return
 *      OEMCrypto_ERROR_NO_CONTENT_KEY.
 *
 * Parameters
 *   key_id (in) - The unique id of the key of interest.
 *   key_id_length (in) - The length of key_id, in bytes.
 *   key_control_block(out) - A caller-owned buffer.
 *   key_control_block_length (in/out) - The length of key_control_block buffer.
 *
 * Returns
 *   OEMCrypto_SUCCESS
 *   OEMCrypto_ERROR_INVALID_CONTEXT
 *   OEMCrypto_ERROR_SHORT_BUFFER
 *   OEMCrypto_ERROR_NO_CONTENT_KEY
 *   OEMCrypto_ERROR_UNKNOWN_FAILURE
 *
 * Threading
 *   This function may be called simultaneously with functions on other sessions,
 *   but not with other functions on this session.
 *
 * Version
 *   This method is added in API version 10.
 */
OEMCryptoResult
OEMCrypto_QueryKeyControl(OEMCrypto_SESSION session,
                          const uint8_t* key_id,
                          size_t key_id_length,
                          uint8_t* key_control_block,
                          size_t* key_control_block_length);

/*
 * OEMCrypto_SelectKey
 *
 * Description:
 *   Select a content key and install it in the hardware key ladder for
 *   subsequent decryption operations (OEMCrypto_DecryptCENC()) for this session.
 *   The specified key must have been previously "installed" via
 *   OEMCrypto_LoadKeys() or OEMCrypto_RefreshKeys().
 *
 *   A key control block is associated with the key and the session, and is used
 *   to configure the session context.  The Key Control data is documented in
 *   "Key Control Block Definition".
 *
 *   Step 1: Lookup the content key data via the offered key_id.  The key data
 *   includes the key value, and the key control block.
 *
 *   Step 2: Latch the content key into the hardware key ladder.  Set
 *           permission flags and timers based on the key's control block.
 *
 *   Step 3: use the latched content key to decrypt (AES-128-CTR) buffers passed in
 *           via OEMCrypto_DecryptCENC().  If the key is 256 bits it will be used for
 *           OEMCrypto_Generic_Sign or OEMCrypto_Generic_Verify as specified in the key
 *           control block.  Continue to use this key until OEMCrypto_SelectKey() is called
 *           again, or until OEMCrypto_CloseSession() is called.
 *
 *
 * Parameters:
 *    session (in) - crypto session identifier
 *    key_id (in) - pointer to the Key ID
 *    key_id_length (in) - length of the Key ID in bytes
 *
 * Threading:
 *   This function may be called simultaneously with functions on other sessions,
 *   but not with other functions on this session.
 *
 * Returns:
 *   OEMCrypto_SUCCESS success
 *   OEMCrypto_ERROR_INVALID_SESSION crypto session ID invalid or not open
 *   OEMCrypto_ERROR_NO_DEVICE_KEY failed to decrypt device key
 *   OEMCrypto_ERROR_NO_CONTENT_KEY failed to decrypt content key
 *   OEMCrypto_ERROR_CONTROL_INVALID invalid or unsupported control input
 *   OEMCrypto_ERROR_KEYBOX_INVALID cannot decrypt and read from Keybox
 *   OEMCrypto_ERROR_KEY_EXPIRED
 *   OEMCrypto_ERROR_INSUFFICIENT_RESOURCES
 *   OEMCrypto_ERROR_UNKNOWN_FAILURE
 *
 * Version:
 *   This method changed in API version 8.
 */
OEMCryptoResult OEMCrypto_SelectKey(OEMCrypto_SESSION session,
                                    const uint8_t* key_id,
                                    size_t key_id_length);

/*
 * OEMCrypto_DecryptCENC
 *
 * Description:
 *   Decrypts or copies the payload in the buffer referenced by the *data_addr
 *   parameter into the buffer referenced by the out_buffer parameter, using
 *   the session context indicated by the session parameter.  Decryption mode
 *   is AES-128-CTR or AES-128-CBC depending on the value of cipher_mode set in
 *   the OEMCrypto_KeyObject passed in to OEMCrypto_LoadKeys.  If is_encrypted
 *   is true, the content key associated with the session is latched in the
 *   active hardware key ladder and is used for the decryption operation.  If
 *   is_encrypted is false, the data is simply copied.
 *
 *   After decryption, the data_length bytes are copied to the location described
 *   by out_buffer.  This could be one of
 *
 *   1. The structure out_buffer contains a pointer to a clear text buffer.  The
 *   OEMCrypto library shall verify that key control allows data to be returned in
 *   clear text.  If it is not authorized, this method should return an error.
 *
 *   2. The structure out_buffer contains a handle to a secure buffer.
 *
 *   3. The structure out_buffer indicates that the data should be sent directly to
 *   the decoder and rendered.
 *
 * NOTES:
 *   For CTR mode, IV points to the counter value to be used for the initial
 *   encrypted block of the input buffer. The IV length is the AES block
 *   size. For subsequent encrypted AES blocks the IV is calculated by
 *   incrementing the lower 64 bits (byte 8-15) of the IV value used for the
 *   previous block. The counter rolls over to zero when it reaches its maximum
 *   value (0xFFFFFFFFFFFFFFFF). The upper 64 bits (byte 0-7) of the IV do not
 *   change.
 *
 *   This method may be called several times before the decrypted data is used.
 *   For this reason, the parameter subsample_flags may be used to optimize
 *   decryption.  The first buffer in a chunk of data will have the
 *   OEMCrypto_FirstSubsample bit set in subsample_flags.  The last buffer in a
 *   chunk of data will have the OEMCrypto_LastSubsample bit set in
 *   subsample_flags.  The decrypted data will not be used until after
 *   OEMCrypto_LastSubsample has been set.  If an implementation decrypts data
 *   immediately, it may ignore subsample_flags.
 *
 *   If the destination buffer is secure, an offset may be specified.  DecryptCENC
 *   begins storing data out_buffer->secure.offset bytes after the beginning of the
 *   secure buffer.
 *
 *   If the session has an entry in the Usage Table, then OEMCrypto will update the
 *   time_of_last_decrypt.  If the status of the entry is "unused", then change the
 *   status to "active" and set the time_of_first_decrypt.
 *
 *   The decryption mode, either OEMCrypto_CipherMode_CTR or
 *   OEMCrypto_CipherMode_CBC, was specified in the call to OEMCrypto_LoadKeys.
 *   The encryption pattern is specified in by the parameter pattern.  A
 *   description of partial encryption patterns can be found in the document
 *   Draft International Standard ISO/IEC DIS 23001-7.  Search for the codes
 *   "cenc", "cbc1", "cens" or "cbcs".
 *
 *
 * Verification:
 *   The following checks should be performed if is_encrypted is true.  If any
 *   check fails, an error is returned, and no decryption is performed.
 *
 *   1. If the current key’s control block has a nonzero Duration field, then the
 *   API shall verify that the duration is greater than the session’s elapsed time
 *   clock. If not, return OEMCrypto_ERROR_KEY_EXPIRED.
 *
 *   2. If the current key’s control block has the Data_Path_Type bit set, then the
 *   API shall verify that the output buffer is secure or direct.  If not, return
 *   OEMCrypto_ERROR_DECRYPT_FAILED.
 *
 *   3. If the current key’s control block has the HDCP bit set, then the API shall
 *   verify that the buffer will be output using HDCP only.  If not, return
 *   OEMCrypto_ERROR_DECRYPT_FAILED.
 *
 *   4. If the current key’s control block has a nonzero value for HDCP_Version,
 *   then the current version of HDCP for the device and the display combined will
 *   be compared against the version specified in the control block.  If the
 *   current version is not at least as high as that in the control block, then
 *   return OEMCrypto_ERROR_INSUFFICIENT_HDCP.
 *
 *   5. If the current session has an entry in the Usage Table, and the status of
 *   that entry is "inactive", then return OEMCrypto_ERROR_INVALID_SESSION.
 *
 *   If the flag is_encrypted is false, then no verification is performed.  This
 *   call shall copy clear data even when there are no keys loaded, or there is no
 *   selected key.
 *
 * Parameters:
 *   session (in) - crypto session identifier.
 *   data_addr (in) - An unaligned pointer to this segment of the stream.
 *   data_length (in) - The length of this segment of the stream, in bytes.
 *   is_encrypted (in) - True if the buffer described by data_addr, data_length is
 *                       encrypted.  If is_encrypted is false, only the data_addr
 *                       and data_length parameters are used. The iv and offset
 *                       arguments are ignored.
 *   iv (in) - The initial value block to be used for content decryption.
 *   block_offset (in) - If non-zero, the decryption block boundary is different
 *                       from the start of the data. block_offset should be
 *                       subtracted from data_addr to compute the starting address
 *                       of the first decrypted block. The bytes between the
 *                       decryption block start address and data_addr are discarded
 *                       after decryption. It does not adjust the beginning of the
 *                       source or destination data.  This parameter satisfies
 *                       0 <= block_offset < 16.  This paramater is only used
 *                       for CTR mode.
 *   out_buffer (in) - A caller-owned descriptor that specifies the handling of the
 *                     decrypted byte stream. See OEMCrypto_DestbufferDesc for details.
 *   pattern (in) - A caller-owned structure indicating the encrypt/skip
 *                  pattern as specified in the CENC standard.
 *   subsample_flags (in) - bitwise flags indicating if this is the first, middle,
 *                          or last subsample in a chunk of data.
 *      0 = neither first nor last subsample,
 *      1 = first subsample,
 *      2 = last subsample,
 *      3 = both first and last subsample.
 *
 * Threading:
 *   This function may be called simultaneously with functions on other sessions,
 *   but not with other functions on this session.
 *
 * Returns:
 *   OEMCrypto_SUCCESS
 *   OEMCrypto_ERROR_NO_DEVICE_KEY
 *   OEMCrypto_ERROR_INVALID_SESSION
 *   OEMCrypto_ERROR_INVALID_CONTEXT
 *   OEMCrypto_ERROR_DECRYPT_FAILED
 *   OEMCrypto_ERROR_KEY_EXPIRED
 *   OEMCrypto_ERROR_INSUFFICIENT_HDCP
 *   OEMCrypto_ERROR_INSUFFICIENT_RESOURCES
 *   OEMCrypto_ERROR_UNKNOWN_FAILURE
 *
 * Version:
 *   This method changed in API version 11.
 *   This method changed its name in API version 11.
 */
OEMCryptoResult OEMCrypto_DecryptCENC(OEMCrypto_SESSION session,
                                      const uint8_t *data_addr,
                                      size_t data_length,
                                      bool is_encrypted,
                                      const uint8_t *iv,
                                      size_t block_offset,
                                      OEMCrypto_DestBufferDesc* out_buffer,
                                      const OEMCrypto_CENCEncryptPatternDesc* pattern,
                                      uint8_t subsample_flags);


/*
 * OEMCrypto_CopyBuffer
 *
 * Description:
 *   Copies the payload in the buffer referenced by the *data_addr parameter into
 *   the buffer referenced by the out_buffer parameter.  The data is simply
 *   copied. The definition of OEMCrypto_DestBufferDesc and subsample_flags are
 *   the same as in OEMCrypto_DecryptCENC, above.
 *
 *   The main difference between this and DecryptCENC is that this function does
 *   not need an open session, and it may be called concurrently with other
 *   session functions on a multithreaded system.  In particular, an application
 *   will use this to copy the clear leader of a video to a secure buffer while
 *   the license request is being generated, sent to the server, and the response
 *   is being processed.  This functionality is needed because an application may
 *   not have read or write access to a secure destination buffer.
 *
 * NOTES:
 *
 *   This method may be called several times before the data is used.  The
 *   first buffer in a chunk of data will have the OEMCrypto_FirstSubsample bit
 *   set in subsample_flags.  The last buffer in a chunk of data will have the
 *   OEMCrypto_LastSubsample bit set in subsample_flags.  The data will not be
 *   used until after OEMCrypto_LastSubsample has been set.  If an
 *   implementation copies data immediately, it may ignore subsample_flags.
 *
 *   If the destination buffer is secure, an offset may be specified.
 *   CopyBuffer begins storing data out_buffer->secure.offset bytes after the
 *   beginning of the secure buffer.
 *
 * Verification
 *   The following checks should be performed.
 *   1. If either data_addr or out_buffer is null, return
 *      OEMCrypto_ERROR_INVALID_CONTEXT.
 *
 * Parameters
 *   data_addr (in) - An unaligned pointer to the buffer to be copied.
 *   data_length (in) - The length of the buffer, in bytes.
 *   out_buffer (out) - A caller-owned descriptor that specifies the handling of
 *                      the byte stream. See OEMCrypto_DestbufferDesc for details.
 *   subsample_flags (in) - bitwise flags indicating if this is the first, middle,
 *                          or last subsample in a chunk of data.
 *      0 = neither first nor last subsample,
 *      1 = first subsample,
 *      2 = last subsample,
 *      3 = both first and last subsample.
 *
 * Returns
 *   OEMCrypto_SUCCESS
 *   OEMCrypto_ERROR_INVALID_CONTEXT
 *   OEMCrypto_ERROR_UNKNOWN_FAILURE
 *
 * Threading
 *   This function may be called simultaneously with any other functions.
 * Version
 *   This method is added in API version 10.
 */
OEMCryptoResult OEMCrypto_CopyBuffer(const uint8_t *data_addr,
                                     size_t data_length,
                                     OEMCrypto_DestBufferDesc* out_buffer,
                                     uint8_t subsample_flags);

/*
 * OEMCrypto_WrapKeybox
 *
 * Description:
 *   During manufacturing, the keybox should be encrypted with the OEM root key and
 *   stored on the file system in a region that will not be erased during factory
 *   reset.   As described in section 5.5.4, the keybox may be directly encrypted
 *   and stored on the device in a single step, or it may use the two-step
 *   WrapKeybox/InstallKeybox approach.  When the Widevine DRM plugin initializes,
 *   it will look for a wrapped keybox in the file /factory/wv.keys and install it
 *   into the security processor by calling OEMCrypto_InstallKeybox().
 *
 *   OEMCrypto_WrapKeybox() is used to generate an OEM-encrypted keybox that may be
 *   passed to OEMCrypto_InstallKeybox() for provisioning.  The keybox may be
 *   either passed in the clear or previously encrypted with a transport key.  If a
 *   transport key is supplied, the keybox is first decrypted with the transport
 *   key before being wrapped with the OEM root key.  This function is only needed
 *   if the provisioning method involves saving the keybox to the file system.
 *
 * Parameters:
 *   keybox   (in) - pointer to Keybox data to encrypt.  May be NULL on the first
 *                  call to test size of wrapped keybox. The keybox may either be clear or
 *                  previously encrypted.
 *   keyboxLength  (in) - length the keybox data in bytes
 *   wrappedKeybox   (out) – Pointer to wrapped keybox
 *   wrappedKeyboxLength  (out) – Pointer to the length of the wrapped keybox in bytes
 *   transportKey  (in) – Optional. AES transport key.  If provided, the keybox
 *                        parameter was previously encrypted with this key.  The keybox will be
 *                        decrypted with the transport key using AES-CBC and a null IV.
 *   transportKeyLength (in) – Optional. Number of bytes in the transportKey, if used.
 *
 * Threading:
 *   This function is not called simultaneously with any other functions
 *
 * Returns:
 *   OEMCrypto_SUCCESS success
 *   OEMCrypto_ERROR_WRAP_KEYBOX failed to wrap Keybox
 *   OEMCrypto_ERROR_SHORT_BUFFER if keybox is provided as NULL, to determine the
 *                                size of the wrapped keybox
 *   OEMCrypto_ERROR_INSUFFICIENT_RESOURCES
 *   OEMCrypto_ERROR_NOT_IMPLEMENTED
 *
 * Version:
 *   This method is supported by all API versions.
 */
OEMCryptoResult OEMCrypto_WrapKeybox(const uint8_t *keybox,
                                     size_t keyBoxLength,
                                     uint8_t *wrappedKeybox,
                                     size_t *wrappedKeyBoxLength,
                                     const uint8_t *transportKey,
                                     size_t transportKeyLength);


/*
 * OEMCrypto_InstallKeybox
 *
 * Description:
 *   Decrypts a wrapped keybox and installs it in the security processor.  The
 *   keybox is unwrapped then encrypted with the OEM root key.  This function is
 *   called from the Widevine DRM plugin at initialization time if there is no
 *   valid keybox installed.  It looks for a wrapped keybox in the file
 *   /factory/wv.keys and if it is present, will read the file and call
 *   OEMCrypto_InstallKeybox() with the contents of the file.
 *
 * Parameters:
 *   keybox  (in) - pointer to encrypted Keybox data as input
 *   keyboxLength  (in) - length of the keybox data in bytes
 *
 * Threading:
 *   This function is not called simultaneously with any other functions.
 *
 * Returns:
 *   OEMCrypto_SUCCESS success
 *   OEMCrypto_ERROR_BAD_MAGIC
 *   OEMCrypto_ERROR_BAD_CRC
 *   OEMCrypto_ERROR_INSUFFICIENT_RESOURCES
 *   OEMCrypto_ERROR_WRITE_KEYBOX failed to handle and store Keybox
 *
 * Version:
 *   This method is supported in all API versions.
 */
OEMCryptoResult OEMCrypto_InstallKeybox(const uint8_t *keybox,
                                        size_t keyBoxLength);

/*
 * OEMCrypto_LoadTestKeybox
 *
 * Description:
 *   Temporarily use the standard test keybox in place of the factory provisioned
 *   keybox for all functions that use keybox keys or data.  This allows a
 *   standard suite of unit tests to be run on a production device without
 *   permanently changing the keybox.  This keybox will persist until the next
 *   call to OEMCrypto_Terminate or OEMCrypto_Initialize.  Upon initialization,
 *   revert to using the factory provisioned keybox.
 *
 *   The test keybox can be found in the reference implementation.
 *
 * Parameters
 *   none
 *
 * Returns
 *   OEMCrypto_SUCCESS success
 *   OEMCrypto_ERROR_UNKNOWN_FAILURE
 *
 * Threading
 *   This function is not called simultaneously with any other functions.
 *   It will be called just after OEMCrypto_Initialize().
 *
 * Version
 *   This method is added in API version 10.
 */
OEMCryptoResult OEMCrypto_LoadTestKeybox();

/*
 * OEMCrypto_IsKeyboxValid
 *
 * Description:
 *   Validate the Widevine Keybox stored on the device.
 *
 * The API performs two verification steps on the Keybox. It first verifies
 * the MAGIC field contains a valid signature (must be 'kbox'). The API then
 * computes the CRC using CRC-32 (Posix 1003.2 standard) and compares the
 * checksum to the CRC stored in the Keybox. The CRC is computed over the
 * entire Keybox excluding the 4 CRC bytes (i.e. Keybox[0..123]).
 *
 * Parameters:
 *   none
 *
 * Threading:
 *   This function may be called simultaneously with any session functions.
 *
 * Returns:
 *   OEMCrypto_SUCCESS
 *   OEMCrypto_ERROR_BAD_MAGIC
 *   OEMCrypto_ERROR_BAD_CRC
 *
 * Version:
 *   This method is supported by all API versions.
 */
OEMCryptoResult OEMCrypto_IsKeyboxValid(void);

/*
 * OEMCrypto_GetDeviceID
 *
 * Description:
 *   Retrieve the device's unique identifier from the Keybox.
 *
 * Parameters:
 *   deviceId (out) - pointer to the buffer that receives the Device ID
 *   idLength (in/out) - on input, size of the caller's device ID buffer.
 *        On output, the number of bytes written into the buffer.
 *
 * Threading:
 *   This function may be called simultaneously with any session functions.
 *
 * Returns:
 *   OEMCrypto_SUCCESS success
 *   OEMCrypto_ERROR_SHORT_BUFFER buffer is too small to return the device ID
 *   OEMCrypto_ERROR_NO_DEVICEID failed to return Device Id
 *
 * Version:
 *   This method is supported by all API versions.
 */
OEMCryptoResult OEMCrypto_GetDeviceID(uint8_t* deviceID,
                                      size_t *idLength);

/*
 * OEMCrypto_GetKeyData
 *
 * Description:
 *   Returns the Key Data field from the Keybox. The Key Data field does not
 *   need to be encrypted by an OEM root key, but may be if desired.
 *
 *   If the Key Data field was encrypted with an OEM root key when the Keybox
 *   was stored on the device, then this function should decrypt it and return
 *   the clear Key Data. If the Key Data was not encrypted, then this function
 *   should just access and return the clear Key data.
 *
 * Parameters:
 *   keyData (out) - pointer to a caller-managed buffer to hold the Key Data
 *                   field from the Keybox
 *   dataLength (in/out) - on input, the allocated buffer size.  On output,
 *                   the number of bytes in KeyData.
 *
 * Threading:
 *   This function may be called simultaneously with any session functions.
 *
 * Returns:
 *   OEMCrypto_SUCCESS success
 *   OEMCrypto_ERROR_SHORT_BUFFER the buffer is too small to return the KeyData
 *   OEMCrypto_ERROR_NO_KEYDATA failed to return KeyData
 *
 * Version:
 *   This method is supported by all API versions.
 */
OEMCryptoResult OEMCrypto_GetKeyData(uint8_t* keyData,
                                     size_t *keyDataLength);

/*
 * OEMCrypto_GetRandom
 *
 * Description:
 *   Return a buffer filled with hardware-generated random bytes. If the
 *   hardware feature does not exist, return OEMCrypto_ERROR_RNG_NOT_SUPPORTED.
 *
 * Parameters:
 *   randomData (out) - Pointer to caller-manager buffer that will receive the
 *                      random data.
 *   dataLength (in)  - Length of the random data buffer in bytes.
 *
 * Threading:
 *   This function may be called simultaneously with any session functions.
 *
 * Returns:
 *   OEMCrypto_SUCCESS success
 *   OEMCrypto_ERROR_RNG_FAILED failed to generate random number
 *   OEMCrypto_ERROR_RNG_NOT_SUPPORTED function not supported
 *
 * Version:
 *   This method is supported by all API versions.
 */
OEMCryptoResult OEMCrypto_GetRandom(uint8_t* randomData,
                                    size_t dataLength);

/*
 * OEMCrypto_RewrapDeviceRSAKey
 *
 * Description:
 *   Verifies an RSA provisioning response is valid and corresponds to the previous
 *   provisioning request by checking the nonce.  The RSA private key is decrypted
 *   and stored in secure memory.  The RSA key is then re-encrypted and signed for
 *   storage on the filesystem.  We recommend that the OEM use an encryption key
 *   and signing key generated using an algorithm at least as strong as that in
 *   GenerateDerivedKeys.
 *
 *   After decrypting enc_rsa_key, If the first four bytes of the buffer are the
 *   string "SIGN", then the actual RSA key begins on the 9th byte of the buffer.
 *   The second four bytes of the buffer is the 32 bit field "allowed_schemes",
 *   of type RSA_Padding_Scheme, which is used in OEMCrypto_GenerateRSASignature.    The
 *   value of allowed_schemes must also be wrapped with RSA key. We recommend
 *   storing the magic string "SIGN" with the key to distinguish keys that have a
 *   value for allowed_schemes from those that should use the default
 *   allowed_schemes. Devices that do not support the alternative signing
 *   algorithms may refuse to load these keys and return an error of
 *   OEMCrypto_ERROR_NOT_IMPLEMENTED.  The main use case for these alternative
 *   signing algorithms is to support devices that use x509 certificates for
 *   authentication when acting as a ChromeCast receiver.  This is not needed for
 *   devices that wish to send data to a ChromeCast.
 *
 *   If the first four bytes of the buffer enc_rsa_key are not the string "SIGN",
 *   then the default value of allowed_schemes = 1 will be used.
 *
 * Verification:
 *   The following checks should be performed.  If any check fails, an error is
 *   returned, and the key is not loaded.
 *   1. Check that all the pointer values passed into it are within the buffer
 *   specified by message and message_length.
 *   2. Verify that in_wrapped_rsa_key_length is large enough to hold the rewrapped
 *   key, returning OEMCrypto_ERROR_SHORT_BUFFER otherwise.
 *   3. Verify that the nonce matches one generated by a previous call to
 *   OEMCrypto_GenerateNonce().  The matching nonce shall be removed from the nonce
 *   table.  If there is no matching nonce, return OEMCRYPTO_ERROR_INVALID_NONCE.
 *   4. Verify the message signature, using the derived signing key
 *   (mac_key[server]).
 *   5. Decrypt enc_rsa_key using the derived encryption key (enc_key), and
 *   enc_rsa_key_iv.
 *   6. Validate the decrypted RSA device key by verifying that it can be loaded by
 *   the RSA implementation.
 *   7. Generate a random initialization vector and store it in
 *   wrapped_rsa_key_iv.
 *   8. Re-encrypt the device RSA key with an internal key (such as the OEM key or
 *   Widevine Keybox key) and the generated IV using AES-128-CBC with PKCS#5
 *   padding.
 *   9. Copy the rewrapped key to the buffer specified by wrapped_rsa_key and the
 *   size of the wrapped key to wrapped_rsa_key_length.
 *
 * Parameters:
 *   session (in)            - crypto session identifier.
 *   message (in)            - pointer to memory containing message to be
 *                           - verified.
 *   message_length (in)     - length of the message, in bytes.
 *   signature (in)          - pointer to memory containing the HMAC-SHA256
 *                           - signature for message, received from the
 *                           - provisioning server.
 *   signature_length (in)   - length of the signature, in bytes.
 *   nonce (in)              - The nonce provided in the provisioning response.
 *   enc_rsa_key (in)        - Encrypted device private RSA key received from
 *                           - the provisioning server. Format is PKCS#8
 *                           - binary DER encoded, encrypted with the derived
 *                           - encryption key, using AES-128-CBC with PKCS#5
 *                           - padding.
 *   enc_rsa_key_length (in) - length of the encrypted RSA key, in bytes.
 *   enc_rsa_key_iv (in)     - IV for decrypting RSA key.  Size is 128 bits.
 *   wrapped_rsa_key (out)   - pointer to buffer in which encrypted RSA key
 *                           - should be stored.  May be null on the first call
 *                           - in order to find required buffer size.
 *   wrapped_rsa_key_length (in/out) - length of the encrypted RSA key, in bytes.
 *
 * Threading:
 *   This function may be called simultaneously with functions on other sessions,
 *   but not with other functions on this session.
 *
 * Returns:
 *   OEMCrypto_SUCCESS success
 *   OEMCrypto_ERROR_NO_DEVICE_KEY
 *   OEMCrypto_ERROR_INVALID_SESSION
 *   OEMCrypto_ERROR_INVALID_RSA_KEY
 *   OEMCrypto_ERROR_SIGNATURE_FAILURE
 *   OEMCrypto_ERROR_INVALID_NONCE
 *   OEMCrypto_ERROR_SHORT_BUFFER
 *   OEMCrypto_ERROR_INSUFFICIENT_RESOURCES
 *   OEMCrypto_ERROR_UNKNOWN_FAILURE
 *
 * Version:
 *   This method changed in API version 9.
 */

OEMCryptoResult OEMCrypto_RewrapDeviceRSAKey(OEMCrypto_SESSION session,
                                             const uint8_t* message,
                                             size_t message_length,
                                             const uint8_t* signature,
                                             size_t signature_length,
                                             const uint32_t *nonce,
                                             const uint8_t* enc_rsa_key,
                                             size_t enc_rsa_key_length,
                                             const uint8_t* enc_rsa_key_iv,
                                             uint8_t* wrapped_rsa_key,
                                             size_t *wrapped_rsa_key_length);

/*
 * OEMCrypto_LoadDeviceRSAKey
 *
 * Description:
 *   Loads a wrapped RSA private key to secure memory for use by this session in
 *   future calls to OEMCrypto_GenerateRSASignature.  The wrapped RSA key will be
 *   the one verified and wrapped by OEMCrypto_RewrapDeviceRSAKey.  The RSA private
 *   key should be stored in secure memory.
 *
 *   If the bit field "allowed_schemes" was wrapped with this RSA key, its value
 *   will be loaded and stored with the RSA key.  If there was not bit field
 *   wrapped with the RSA key, the key will use a default value of 1 = RSASSA-PSS
 *   with SHA1.
 *
 * Verification:
 *   The following checks should be performed.  If any check fails, an error is
 *   returned, and the RSA key is not loaded.
 *   1. The wrapped key has a valid signature, as described in RewrapDeviceRSAKey.
 *   2. The decrypted key is a valid private RSA key.
 *   3. If a value for allowed_schemes is included with the key, it is a valid
 *   value.
 *
 * Parameters:
 *   session (in)                - crypto session identifier.
 *   wrapped_rsa_key (in)        - wrapped device RSA key stored on the device.
 *                               - Format is PKCS#8, binary DER encoded, and
 *                               - encrypted with a key internal to the OEMCrypto
 *                               - instance, using AES-128-CBC with PKCS#5
 *                               - padding.  This is the wrapped key generated
 *                               - by OEMCrypto_RewrapDeviceRSAKey.
 *   wrapped_rsa_key_length (in) - length of the wrapped key buffer, in bytes.
 *
 * Threading:
 *   This function may be called simultaneously with functions on other sessions,
 *   but not with other functions on this session.
 *
 * Returns:
 *   OEMCrypto_SUCCESS success
 *   OEMCrypto_ERROR_NO_DEVICE_KEY
 *   OEMCrypto_ERROR_INVALID_SESSION
 *   OEMCrypto_ERROR_INVALID_RSA_KEY
 *   OEMCrypto_ERROR_INSUFFICIENT_RESOURCES
 *   OEMCrypto_ERROR_UNKNOWN_FAILURE
 *
 * Version:
 *   This method changed in API version 9.
 */
OEMCryptoResult OEMCrypto_LoadDeviceRSAKey(OEMCrypto_SESSION session,
                                           const uint8_t* wrapped_rsa_key,
                                           size_t wrapped_rsa_key_length);

/*
 * OEMCrypto_LoadTestRSAKey
 *
 * Description:

 *   Temporarily use the standard test RSA key.  This function is only required
 *   for platforms that do not use a keybox, but have an RSA certificate baked
 *   in.  This allows a standard suite of unit tests to be run on a production
 *   device without permanently changing the certificate.  This RSA key will
 *   persist until the next call to OEMCrypto_Terminate or
 *   OEMCrypto_Initialize.
 *
 *   The test RSA key can be found in the reference implementation.
 *
 * Parameters
 *   none
 *
 * Returns
 *   OEMCrypto_SUCCESS success
 *   OEMCrypto_ERROR_UNKNOWN_FAILURE
 *
 * Threading
 *   This function is not called simultaneously with any other functions.
 *   It will be called just after OEMCrypto_Initialize().
 *
 * Version
 *   This method is added in API version 10.
 */
OEMCryptoResult OEMCrypto_LoadTestRSAKey();

/*
 * OEMCrypto_GenerateRSASignature
 *
 * Description:
 *   The OEMCrypto_GenerateRSASignature method is used to sign messages using the
 *   device private RSA key, specifically, it is used to sign the initial license
 *   request. Refer to the License Request Signed by RSA Certificate section above
 *   for more details.
 *
 *   For devices that wish to be CAST receivers, there is a new RSA padding scheme.
 *   The padding_scheme parameter indicates which hashing and padding is to be
 *   applied to the message so as to generate the encoded message (the
 *   modulus-sized block to which the integer conversion and RSA decryption is
 *   applied). The following values are defined:
 *   0x1 - RSASSA-PSS with SHA1.
 *   0x2 - PKCS1 with block type 1 padding (only).
 *
 *   In the first case, a hash algorithm (SHA1) is first applied to the message,
 *   whose length is not otherwise restricted. In the second case, the "message" is
 *   already a digest, so no further hashing is applied, and the message_length can
 *   be no longer than 83 bytes.  If the message_length is greater than 83 bytes
 *   OEMCrypto_ERROR_SIGNATURE_FAILURE shall be returned.
 *
 *   The second padding scheme is for devices that use x509 certificates for
 *   authentication. The main example is devices that work as a Cast receiver, like
 *   a ChromeCast, not for devices that wish to send to the Cast device, such as
 *   almost all Android devices.  OEMs that do not support x509 certificate
 *   authentication need not implement the second scheme and can return
 *   OEMCrypto_ERROR_NOT_IMPLEMENTED.
 *
 * Verification:
 *   The bitwise AND of the parameter padding_scheme and the RSA key’s
 *   allowed_schemes is computed.  If this value is 0, then the signature is not
 *   computed and the error OEMCrypto_ERROR_INVALID_RSA_KEY is returned.
 *
 * Parameters:
 *   session (in)              - crypto session identifier.
 *   message (in)              - pointer to memory containing message to be
 *                             - signed.
 *   message_length (in)       - length of the message, in bytes.
 *   signature (out)           - buffer to hold the message signature. On
 *                             - return, it will contain the message signature
 *                             - generated with the device private RSA key using
 *                             - RSASSA-PSS.
 *   signature_length (in/out) - (in) length of the signature buffer, in bytes.
 *                             - (out) actual length of the signature
 *   padding_scheme (in) - specify which scheme to use for the signature.
 *
 * Threading:
 *   This function may be called simultaneously with functions on other sessions,
 *   but not with other functions on this session.
 *
 * Returns:
 *   OEMCrypto_SUCCESS success
 *   OEMCrypto_ERROR_INVALID_SESSION
 *   OEMCrypto_ERROR_INVALID_CONTEXT
 *   OEMCrypto_ERROR_SHORT_BUFFER if the signature buffer is too small.
 *   OEMCrypto_ERROR_INVALID_RSA_KEY
 *   OEMCrypto_ERROR_INSUFFICIENT_RESOURCES
 *   OEMCrypto_ERROR_UNKNOWN_FAILURE
 *   OEMCrypto_ERROR_NOT_IMPLEMENTED - if algorithm > 0, and the device does not
 *   support that algorithm.
 *
 * Version:
 *   This method changed in API version 9.
 */
OEMCryptoResult OEMCrypto_GenerateRSASignature(OEMCrypto_SESSION session,
                                               const uint8_t* message,
                                               size_t message_length,
                                               uint8_t* signature,
                                               size_t *signature_length,
                                               RSA_Padding_Scheme padding_scheme);

/*
 * OEMCrypto_DeriveKeysFromSessionKey
 *
 * Description:
 *   Generates three secondary keys -- mac_key_server, mac_key_client, and
 *   encrypt_key -- for handling signing and content key decryption under the
 *   license server protocol for AES CTR mode.
 *
 *   This function is similar to OEMCrypto_GenerateDerivedKeys, except that it
 *   uses a session key to generate the secondary keys instead of the Widevine
 *   Keybox device key.  These two keys will be stored in secure memory until
 *   the next call to LoadKeys.  The session key is passed in encrypted by the
 *   device RSA public key, and must be decrypted with the RSA private key
 *   before use.  Once the enc_key and mac_keys have been generated, all calls
 *   to LoadKeys and RefreshKeys proceed in the same manner for license
 *   requests using RSA or using a Widevine keybox token.
 *
 * Verification:
 *   If the RSA key’s allowed_schemes is not kSign_RSASSA_PSS, then no keys are
 *   derived and the error OEMCrypto_ERROR_INVALID_RSA_KEY is returned.  An RSA key
 *   cannot be used for both deriving session keys and also for PKCS1 signatures.
 *
 * Parameters:
 *   session (in)                - crypto session identifier.
 *   enc_session_key (in)        - session key, encrypted with the device RSA key
 *                               - (from the device certifcate) using RSA-OAEP.
 *   enc_session_key_length (in) - length of session_key, in bytes.
 *   mac_key_context (in)        - pointer to memory containing context data for
 *                               - computing the HMAC generation key.
 *   mac_key_context_length (in) - length of the HMAC key context data, in bytes.
 *   enc_key_context (in)        - pointer to memory containing context data for
 *                               - computing the encryption key.
 *   enc_key_context_length (in) - length of the encryption key context data, in
 *                               - bytes.
 *
 * Threading:
 *   This function may be called simultaneously with functions on other sessions,
 *   but not with other functions on this session.
 *
 * Returns:
 *   OEMCrypto_SUCCESS success
 *   OEMCrypto_ERROR_DEVICE_NOT_RSA_PROVISIONED
 *   OEMCrypto_ERROR_INVALID_SESSION
 *   OEMCrypto_ERROR_INVALID_CONTEXT
 *   OEMCrypto_ERROR_INSUFFICIENT_RESOURCES
 *   OEMCrypto_ERROR_UNKNOWN_FAILURE
 *
 * Version:
 *   This method changed in API version 9.
 */
OEMCryptoResult OEMCrypto_DeriveKeysFromSessionKey(OEMCrypto_SESSION session,
                                                   const uint8_t* enc_session_key,
                                                   size_t enc_session_key_length,
                                                   const uint8_t *mac_key_context,
                                                   size_t mac_key_context_length,
                                                   const uint8_t *enc_key_context,
                                                   size_t enc_key_context_length);


/*
 * OEMCrypto_APIVersion()
 *
 * Description:
 *   This function returns the current API version number.  Because this
 *   API is part of a shared library, the version number allows the calling
 *   application to avoid version mis-match errors.
 *
 *   There is a possibility that some API methods will be backwards compatible,
 *   or backwards compatible at a reduced security level.
 *
 *   There is no plan to introduce forward-compatibility.  Applications will reject
 *   a library with a newer version of the API.
 *
 * Parameters:
 *   none
 *
 * Threading:
 *   This function may be called simultaneously with any other functions.
 *
 * Returns:
 *   The supported API, as specified in the header file OEMCryptoCENC.h.
 *
 * Version:
 *   This method should change in all API versions.
 */
uint32_t OEMCrypto_APIVersion();

/**
 *  OEMCrypto_Security_Patch_Level()
 *
 * Description:
 *   This function returns the current patch level of the software running in
 *   the trusted environment. The patch level is defined by the OEM, and is
 *   only incremented when a security update has been added.
 *
 * Parameters:
 *   none
 *
 * Returns:
 *   The OEM defined version number.
 *
 * Threading:
 *   This function may be called simultaneously with any other functions.
 *
 * Version:
 *   This method was introduced in API version 11.
 */
uint8_t OEMCrypto_Security_Patch_Level();

/*
 * OEMCrypto_SecurityLevel()
 *
 * Description:
 *   This function returns the security level of the OEMCrypto library.
 *
 *   Since this function is spoofable, it is not relied on for security
 *   purposes.  It is for information only.
 *
 * Returns:
 *   A null terminated string.  Useful values are "L1", "L2" or "L3".
 *
 * Threading:
 *   This function may be called simultaneously with any other functions.
 *
 * Version:
 *   This method changed in API version 6.
 */
const char* OEMCrypto_SecurityLevel();

/*
 * OEMCrypto_GetHDCPCapability()
 *
 * Description:
 *   Returns the maximum HDCP version supported by the device, and the HDCP version
 *   supported by the device and any connected display.
 *
 * Parameters:
 *   current  (out) - this is the current HDCP version, based on the device itself,
 *   and the display to which it is connected.
 *   maximum  (out) - this is the maximum supported HDCP version for the device,
 *   ignoring any attached device.
 *
 * Threading:
 *   This function may be called simultaneously with any other functions.
 *
 * Returns:
 *   OEMCrypto_SUCCESS
 *   OEMCrypto_ERROR_UNKNOWN_FAILURE
 *
 * Version:
 *   This method changed in API version 10.
 */
OEMCryptoResult OEMCrypto_GetHDCPCapability(OEMCrypto_HDCP_Capability *current,
                                            OEMCrypto_HDCP_Capability *maximum);

/*
 * OEMCrypto_SupportsUsageTable()
 *
 * Description:
 *   This is used to determine if the device can support a usage table.  Since this
 *   function is spoofable, it is not relied on for security purposes.  It is for
 *   information only.  The usage table is described in the section above.
 *
 * Parameters:
 *   none
 *
 * Threading:
 *   This function may be called simultaneously with any other functions.
 *
 * Returns:
 *   Returns true if the device can maintain a usage table. Returns false otherwise.
 *
 * Version:
 *   This method changed in API version 9.
 */
bool OEMCrypto_SupportsUsageTable();

/*
 * OEMCrypto_IsAntiRollbackHwPresent()
 *
 * Description:

 *   Indicate whether there is hardware protection to prevent the rollback of
 *   the usage table.  For example, this is true if the usage table is stored
 *   entirely on a secure file system that the user cannot read or write to.
 *   Another example is if the usage table has a generation number and the
 *   generation number is stored in secure memory that is not user accessible.
 *
 * Parameters:
 *   none.
 *
 * Threading:
 *   This function may be called simultaneously with any other functions.
 *
 * Returns:
 *   Returns true if oemcrypto uses anti-rollback hardware. Returns false
 *   otherwise.
 *
 * Version:
 *   This method is added in API version 10.
 */
bool OEMCrypto_IsAntiRollbackHwPresent();

/*
 * OEMCRYPTO_GetNumberOfOpenSessions()
 *
 * Description:
 *   Returns the current number of open OEMCrypto sessions. The CDM and
 *   OEMCrypto consumers can query this value so they can use resources more
 *   effectively.
 *
 * Parameters:
 *   count (out) - the current number of OEMCrypto sessions.
 *
 * Threading:
 *   This function may be called simultaneously with any other functions.
 *
 * Returns:
 *   OEMCrypto_SUCCESS
 *   OEMCrypto_ERROR_UNKNOWN_FAILURE
 *
 * Version:
 *   This method is added in API version 10.
 */
OEMCryptoResult OEMCrypto_GetNumberOfOpenSessions(size_t *count);

/*
 * OEMCRYPTO_GetMaxNumberOfSessions()
 *
 * Description:
 *   Returns the maximum number of concurrent OEMCrypto sessions supported by
 *   the device. The CDM and OEMCrypto consumers can query this value so they
 *   can use resources more effectively. If the maximum number of sessions
 *   depends on a dynamically allocated shared resource, the returned value
 *   should be a best estimate of the maximum number of sessions.
 *
 * Parameters:
 *   maximum (out) - the maximum number of OEMCrypto sessions supported by the
 *   device.
 *
 * Threading:
 *   This function may be called simultaneously with any other functions.
 *
 * Returns:
 *   OEMCrypto_SUCCESS
 *   OEMCrypto_ERROR_UNKNOWN_FAILURE
 *
 * Version:
 *   This method is added in API version 10.
 */
OEMCryptoResult OEMCrypto_GetMaxNumberOfSessions(size_t *max);

/*
 * OEMCrypto_Generic_Encrypt
 *
 * Description:
 *   This function encrypts a generic buffer of data using the current key.
 *
 *   If the session has an entry in the Usage Table, then OEMCrypto will update the
 *   time_of_last_decrypt.  If the status of the entry is "unused", then change the
 *   status to "active" and set the time_of_first_decrypt.
 *
 * Verification:
 *   The following checks should be performed.  If any check fails, an error is
 *   returned, and the data is not encrypted.
 *   1. The control bit for the current key shall have the Allow_Encrypt set. If
 *   not, return OEMCrypto_ERROR_UNKNOWN_FAILURE.
 *   2. If the current key’s control block has a nonzero Duration field, then the
 *   API shall verify that the duration is greater than the session’s elapsed time
 *   clock. If not, return OEMCrypto_ERROR_KEY_EXPIRED.
 *   3. If the current session has an entry in the Usage Table, and the status of
 *   that entry is "inactive", then return OEMCrypto_ERROR_INVALID_SESSION.
 *
 * Parameters:
 * session (in) - crypto session identifier.
 * in_buffer (in) - pointer to memory containing data to be encrypted.
 * buffer_length (in) - length of the buffer, in bytes.
 * iv (in) - IV for encrypting data.  Size is specified by the algorithm.
 * algorithm (in) - Specifies which encryption algorithm to use. See
 *                  OEMCrypto_Algorithm for valid values.
 * out_buffer (out) - pointer to buffer in which encrypted data should be stored.
 *
 * Returns:
 * OEMCrypto_SUCCESS success
 * OEMCrypto_ERROR_KEY_EXPIRED
 * OEMCrypto_ERROR_NO_DEVICE_KEY
 * OEMCrypto_ERROR_INVALID_SESSION
 * OEMCrypto_ERROR_INSUFFICIENT_RESOURCES
 * OEMCrypto_ERROR_UNKNOWN_FAILURE
 *
 * Threading:
 * This function may be called simultaneously with functions on other sessions,
 * but not with other functions on this session.
 *
 * Version:
 *   This method changed in API version 9.
 */
OEMCryptoResult OEMCrypto_Generic_Encrypt(OEMCrypto_SESSION session,
                                          const uint8_t* in_buffer,
                                          size_t buffer_length,
                                          const uint8_t* iv,
                                          OEMCrypto_Algorithm algorithm,
                                          uint8_t* out_buffer);

/*
 * OEMCrypto_Generic_Decrypt
 *
 * Description:
 *   This function decrypts a generic buffer of data using the current key.
 *
 *   If the session has an entry in the Usage Table, then OEMCrypto will update the
 *   time_of_last_decrypt.  If the status of the entry is "unused", then change the
 *   status to "active" and set the time_of_first_decrypt.
 *
 * Verification:
 *   The following checks should be performed.  If any check fails, an error is
 *   returned, and the data is not decrypted.
 *   1. The control bit for the current key shall have the Allow_Decrypt set.  If
 *   not, return OEMCrypto_ERROR_DECRYPT_FAILED.
 *   2. If the current key’s control block has the Data_Path_Type bit set, then
 *   return OEMCrypto_ERROR_DECRYPT_FAILED.
 *   3. If the current key’s control block has a nonzero Duration field, then the
 *   API shall verify that the duration is greater than the session’s elapsed time
 *   clock. If not, return OEMCrypto_ERROR_KEY_EXPIRED.
 *   4. If the current session has an entry in the Usage Table, and the status of
 *   that entry is "inactive", then return OEMCrypto_ERROR_INVALID_SESSION.
 *
 * Parameters:
 *   session (in) - crypto session identifier.
 *   in_buffer (in) - pointer to memory containing data to be encrypted.
 *   buffer_length (in) - length of the buffer, in bytes.  The algorithm may
 *   restrict buffer_length to be a multiple of block size.
 *   iv (in) - IV for encrypting data.  Size is 128 bits.
 *   algorithm (in) - Specifies which encryption algorithm to use.
 *   out_buffer (out) - pointer to buffer in which decrypted data should be stored.
 *
 * Threading:
 *   This function may be called simultaneously with functions on other sessions,
 *   but not with other functions on this session.
 *
 * Returns:
 *   OEMCrypto_SUCCESS success
 *   OEMCrypto_ERROR_KEY_EXPIRED
 *   OEMCrypto_ERROR_DECRYPT_FAILED
 *   OEMCrypto_ERROR_NO_DEVICE_KEY
 *   OEMCrypto_ERROR_INVALID_SESSION
 *   OEMCrypto_ERROR_INSUFFICIENT_RESOURCES
 *   OEMCrypto_ERROR_UNKNOWN_FAILURE
 *
 * Version:
 *   This method changed in API version 9.
 */
OEMCryptoResult OEMCrypto_Generic_Decrypt(OEMCrypto_SESSION session,
                                          const uint8_t* in_buffer,
                                          size_t buffer_length,
                                          const uint8_t* iv,
                                          OEMCrypto_Algorithm algorithm,
                                          uint8_t* out_buffer);

/*
 * OEMCrypto_Generic_Sign
 *
 * Description:
 *   This function signs a generic buffer of data using the current key.
 *
 *   If the session has an entry in the Usage Table, then OEMCrypto will update the
 *   time_of_last_decrypt.  If the status of the entry is "unused", then change the
 *   status to "active" and set the time_of_first_decrypt.
 *
 * Verification:
 *   The following checks should be performed.  If any check fails, an error is
 *   returned, and the data is not signed.
 *   1. The control bit for the current key shall have the Allow_Sign set.
 *   2. If the current key’s control block has a nonzero Duration field, then the
 *   API shall verify that the duration is greater than the session’s elapsed time
 *   clock. If not, return OEMCrypto_ERROR_KEY_EXPIRED.
 *   3. If the current session has an entry in the Usage Table, and the status of
 *   that entry is "inactive", then return OEMCrypto_ERROR_INVALID_SESSION.
 *
 * Parameters:
 *   session (in) - crypto session identifier.
 *   in_buffer (in) - pointer to memory containing data to be encrypted.
 *   buffer_length (in) - length of the buffer, in bytes.
 *   algorithm (in) - Specifies which algorithm to use.
 *   signature (out) - pointer to buffer in which signature should be stored.   May
 *   be null on the first call in order to find required buffer size.
 *   signature_length (in/out) - (in) length of the signature buffer, in bytes.
 *   (out) actual length of the signature
 *
 *
 *
 * Threading:
 *   This function may be called simultaneously with functions on other sessions,
 *   but not with other functions on this session.
 *
 * Returns:
 *   OEMCrypto_SUCCESS success
 *   OEMCrypto_ERROR_KEY_EXPIRED
 *   OEMCrypto_ERROR_SHORT_BUFFER if signature buffer is not large enough to hold
 *   the output signature.
 *   OEMCrypto_ERROR_NO_DEVICE_KEY
 *   OEMCrypto_ERROR_INVALID_SESSION
 *   OEMCrypto_ERROR_INSUFFICIENT_RESOURCES
 *   OEMCrypto_ERROR_UNKNOWN_FAILURE
 *
 * Version:
 *   This method changed in API version 9.
 */
OEMCryptoResult OEMCrypto_Generic_Sign(OEMCrypto_SESSION session,
                                       const uint8_t* in_buffer,
                                       size_t buffer_length,
                                       OEMCrypto_Algorithm algorithm,
                                       uint8_t* signature,
                                       size_t* signature_length);

/*
 * OEMCrypto_Generic_Verify
 *
 * Description:
 *   This function verifies the signature of a generic buffer of data using the
 *   current key.
 *
 *   If the session has an entry in the Usage Table, then OEMCrypto will update the
 *   time_of_last_decrypt.  If the status of the entry is "unused", then change the
 *   status to "active" and set the time_of_first_decrypt.
 *
 * Verification:
 *   The following checks should be performed.  If any check fails, an error is
 *   returned.
 *   1. The control bit for the current key shall have the Allow_Verify set.
 *   2. The signature of the message shall be computed, and the API shall verify
 *   the computed signature matches the signature passed in.  If not, return
 *   OEMCrypto_ERROR_SIGNATURE_FAILURE.
 *   3. The signature verification shall use a constant-time algorithm (a signature
 *   mismatch will always take the same time as a successful comparison).
 *   4. If the current key’s control block has a nonzero Duration field, then the
 *   API shall verify that the duration is greater than the session’s elapsed time
 *   clock. If not, return OEMCrypto_ERROR_KEY_EXPIRED.
 *   5. If the current session has an entry in the Usage Table, and the status of
 *   that entry is "inactive", then return OEMCrypto_ERROR_INVALID_SESSION.
 *
 * Parameters:
 *   session (in) - crypto session identifier.
 *   in_buffer (in) - pointer to memory containing data to be encrypted.
 *   buffer_length (in) - length of the buffer, in bytes.
 *   algorithm (in) - Specifies which algorithm to use.
 *   signature (in) - pointer to buffer in which signature resides.
 *   signature_length (in) - length of the signature buffer, in bytes.
 *
 * Threading:
 *   This function may be called simultaneously with functions on other sessions,
 *   but not with other functions on this session.
 *
 * Returns:
 *   OEMCrypto_SUCCESS success
 *   OEMCrypto_ERROR_KEY_EXPIRED
 *   OEMCrypto_ERROR_SIGNATURE_FAILURE
 *   OEMCrypto_ERROR_NO_DEVICE_KEY
 *   OEMCrypto_ERROR_INVALID_SESSION
 *   OEMCrypto_ERROR_INSUFFICIENT_RESOURCES
 *   OEMCrypto_ERROR_UNKNOWN_FAILURE
 *
 * Version:
 *   This method changed in API version 9.
 */
OEMCryptoResult OEMCrypto_Generic_Verify(OEMCrypto_SESSION session,
                                         const uint8_t* in_buffer,
                                         size_t buffer_length,
                                         OEMCrypto_Algorithm algorithm,
                                         const uint8_t* signature,
                                         size_t signature_length);


/*
 * OEMCrypto_UpdateUsageTable
 *
 * Description:
 *   OEMCrypto should propagate values from all open sessions to the Session Usage
 *   Table.  If any values have changed, increment the generation number, sign, and
 *   save the table.  During playback, this function will be called approximately
 *   once per minute.
 *
 *   Devices that do not implement a Session Usage Table may return
 *   OEMCrypto_ERROR_NOT_IMPLEMENTED.
 *
 * Parameters:
 *   none
 *
 * Threading:
 *   This function will not be called simultaneously with any session functions.
 *
 * Returns:
 *   OEMCrypto_SUCCESS success
 *   OEMCrypto_ERROR_NOT_IMPLEMENTED
 *   OEMCrypto_ERROR_UNKNOWN_FAILURE
 *
 * Version:
 *   This method changed in API version 9.
 */
OEMCryptoResult OEMCrypto_UpdateUsageTable();

/*
 * OEMCrypto_DeactivateUsageEntry
 *
 * Description:
 *   Find the entry in the Usage Table with a matching PST.  Mark the status of
 *   that entry as "inactive".  If it corresponds to an open session, the status of
 *   that session will also be marked as "inactive".  Then OEMCrypto will increment
 *   Usage Table’s generation number, sign, encrypt, and save the Usage Table.
 *
 *   If no entry in the Usage Table has a matching PST, return the error
 *   OEMCrypto_ERROR_INVALID_CONTEXT.
 *
 *   Devices that do not implement a Session Usage Table may return
 *   OEMCrypto_ERROR_NOT_IMPLEMENTED.
 *
 * Parameters:
 *   pst (in) - pointer to memory containing Provider Session Token.
 *   pst_length (in) - length of the pst, in bytes.
 *
 * Threading:
 *   This function will not be called simultaneously with any session functions.
 *
 * Returns:
 *   OEMCrypto_SUCCESS success
 *   OEMCrypto_ERROR_INVALID_CONTEXT - no entry has matching PST.
 *   OEMCrypto_ERROR_NOT_IMPLEMENTED
 *   OEMCrypto_ERROR_UNKNOWN_FAILURE
 *
 * Version:
 *   This method changed in API version 9.
 */
OEMCryptoResult OEMCrypto_DeactivateUsageEntry(const uint8_t *pst,
                                               size_t pst_length);

/*
 * OEMCrypto_ReportUsage
 *
 * Description:
 *   If the buffer_length is not sufficient to hold a report structure, set
 *   buffer_length and return OEMCrypto_ERROR_SHORT_BUFFER.
 *
 *   If no entry in the Usage Table has a matching PST, return the error
 *   OEMCrypto_ERROR_INVALID_CONTEXT.
 *
 *   OEMCrypto will increment Usage Table’s generation number, sign, encrypt, and
 *   save the Usage Table.  This is done, even though the table has not changed, so
 *   that a single rollback cannot undo a call to DeactivateUsageEntry and still
 *   report that license as inactive.
 *
 *   The pst_report is filled out by subtracting the times un the Usage Table from
 *   the current time on the secure clock.  This is done in case the secure clock
 *   is not using UTC time, but is instead using something like seconds since clock
 *   installed.
 *
 *   Valid values for status are:
 *     0 = kUnused -- the keys have not been used to decrypt.
 *     1 = kActive -- the keys have been used, and have not been deactivated.
 *     2 = kInactive -- the keys have been marked inactive.
 *
 *   The clock_security_level is reported as follows:
 *     0 = Insecure Clock - clock just uses system time.
 *     1 = Secure Timer - clock uses secure timer, which cannot be modified by user
 *     software, when OEMCrypto is active and the system time when OEMCrypto is
 *     inactive.
 *     2 = Software Secure Clock - clock cannot be modified by user software when
 *     OEMCrypto is active or inactive.
 *     3 = Hardware Secure Clock - clock cannot be modified by user software and
 *     there are security features that prevent the user from modifying the clock
 *     in hardware, such as a tamper proof battery.
 *
 *   After pst_report has been filled in, the HMAC SHA1 signature is computed for
 *   the buffer from bytes 20 to the end of the pst field.  The signature is
 *   computed using the client_mac_key which is stored in the usage table.  The
 *   HMAC SHA1 signature is used to prevent a rogue application from using
 *   OMECrypto_GenerateSignature to forge a Usage Report.
 *
 *   This function also copies the client_mac_key and server_mac_key from the Usage
 *   Table entry to the session.  They will be used to verify a signature in
 *   OEMCrypto_DeleteUsageEntry below.  This session will be associated with the
 *   entry in the Usage Table.
 *
 *   Devices that do not implement a Session Usage Table may return
 *   OEMCrypto_ERROR_NOT_IMPLEMENTED.
 *
 * Parameters:
 *   session (in) - handle for the session to be used.
 *   pst (in) - pointer to memory containing Provider Session Token.
 *   pst_length (in) - length of the pst, in bytes.
 *   buffer (out) - pointer to buffer in which usage report should be stored.   May
 *   be null on the first call in order to find required buffer size.
 *   buffer_length (in/out) - (in) length of the report buffer, in bytes.
 *                           (out) actual length of the report
 *
 * Threading:
 *   This function will not be called simultaneously with any session functions.
 *
 * Returns:
 *   OEMCrypto_SUCCESS success
 *   OEMCrypto_ERROR_SHORT_BUFFER if report buffer is not large enough to hold the
 *   output signature.
 *   OEMCrypto_ERROR_INVALID_SESSION no open session with that id.
 *   OEMCrypto_ERROR_INVALID_CONTEXT - no entry has matching PST.
 *   OEMCrypto_ERROR_NOT_IMPLEMENTED
 *   OEMCrypto_ERROR_UNKNOWN_FAILURE
 *
 * Version:
 *   This method changed in API version 9.
 */
OEMCryptoResult OEMCrypto_ReportUsage(OEMCrypto_SESSION session,
                                      const uint8_t *pst,
                                      size_t pst_length,
                                      OEMCrypto_PST_Report *buffer,
                                      size_t *buffer_length);

/*
 * OEMCrypto_DeleteUsageEntry
 *
 * Description:
 *   This function verifies the signature of the given message using the sessions
 *   mac_key[server] and the algorithm HMAC-SHA256, and then deletes an entry from
 *   the session table.   The session should already be associated with the given
 *   entry, from a previous call to OEMCrypto_ReportUsage.
 *
 *   After performing all verification listed below, and deleting the entry from
 *   the Usage Table, OEMCrypto will increment Usage Table’s generation number, and
 *   then sign, encrypt, and save the Usage Table.
 *
 *   The signature verification shall use a constant-time algorithm (a signature
 *   mismatch will always take the same time as a successful comparison).
 *
 *   Devices that do not implement a Session Usage Table may return
 *   OEMCrypto_ERROR_NOT_IMPLEMENTED.
 *
 *   Verification:
 *   The following checks should be performed.  If any check fails, an error is
 *   returned.
 *   1. The pointer pst is not null, and points inside the message.  If not, return
 *   OEMCrypto_ERROR_UNKNOWN_FAILURE.
 *   2. The signature of the message shall be computed, and the API shall verify
 *   the computed signature matches the signature passed in.  The signature will be
 *   computed using HMAC-SHA256 and the mac_key_server.  If they do not match,
 *   return OEMCrypto_ERROR_SIGNATURE_FAILURE.
 *   3. If the session is not associated with an entry in the Usage Table, return
 *   OEMCrypto_ERROR_UNKNOWN_FAILURE.
 *   4. If the pst passed in as a parameter does not match that in the Usage Table,
 *   return OEMCrypto_ERROR_UNKNOWN_FAILURE.
 *
 * Parameters:
 *   session (in) - handle for the session to be used.
 *   pst (in) - pointer to memory containing Provider Session Token.
 *   pst_length (in) - length of the pst, in bytes.
 *   message (in) - pointer to memory containing message to be verified.
 *   message_length (in) - length of the message, in bytes.
 *   signature (in) - pointer to memory containing the signature.
 *   signature_length (in) - length of the signature, in bytes.
 *
 * Threading:
 *   This function will not be called simultaneously with any session functions.
 *
 * Returns:
 *   OEMCrypto_SUCCESS success
 *   OEMCrypto_ERROR_INVALID_SESSION no open session with that id.
 *   OEMCrypto_ERROR_SIGNATURE_FAILURE
 *   OEMCrypto_ERROR_NOT_IMPLEMENTED
 *   OEMCrypto_ERROR_UNKNOWN_FAILURE
 *
 * Version:
 *   This method changed in API version 9.
 */
OEMCryptoResult OEMCrypto_DeleteUsageEntry(OEMCrypto_SESSION session,
                                           const uint8_t* pst,
                                           size_t pst_length,
                                           const uint8_t *message,
                                           size_t message_length,
                                           const uint8_t *signature,
                                           size_t signature_length);


/*
 * OEMCrypto_ForceDeleteUsageEntry
 *
 * Description:
 * This function deletes an entry from the session usage table. This will be
 * used for stale entries without a signed request from the server.
 *
 * After performing all verification listed below, and deleting the entry from
 * the Usage Table, OEMCrypto will increment the Usage Table’s generation number,
 * and then sign, encrypt, and save the Usage Table.
 *
 * Devices that do not implement a Session Usage Table may return
 * OEMCrypto_ERROR_NOT_IMPLEMENTED.
 *
 * Verification
 *   The following checks should be performed.  If any check fails, an error is
 *   returned.
 *   1) The pointer pst is not null.  If not, return OEMCrypto_ERROR_UNKNOWN_FAILURE.
 *
 * Parameters
 *   pst (in) - pointer to memory containing Provider Session Token.
 *   pst_length (in) - length of the pst, in bytes.
 *
 * Returns
 *   OEMCrypto_SUCCESS success
 *   OEMCrypto_ERROR_NOT_IMPLEMENTED
 *   OEMCrypto_ERROR_UNKNOWN_FAILURE
 *
 * Threading
 *   This function will not be called simultaneously with any session functions.
 *
 * Version
 *   This method changed in API version 10.
 */
OEMCryptoResult OEMCrypto_ForceDeleteUsageEntry(const uint8_t* pst,
                                                size_t pst_length);

/*
 * OEMCrypto_DeleteUsageTable
 *
 * Description:
 *   This is called when the CDM system believes there are major problems or
 *   resource issues.  The entire table should be cleaned and a new table should be
 *   created.
 *
 * Parameters:
 *   none
 *
 * Threading:
 *   This function will not be called simultaneously with any session functions.
 *
 * Returns:
 *   OEMCrypto_SUCCESS success
 *   OEMCrypto_ERROR_NOT_IMPLEMENTED
 *   OEMCrypto_ERROR_UNKNOWN_FAILURE
 *
 * Version:
 *   This method changed in API version 9.
 */
OEMCryptoResult OEMCrypto_DeleteUsageTable();

#ifdef __cplusplus
}
#endif

#endif  // OEMCRYPTO_CENC_H_
