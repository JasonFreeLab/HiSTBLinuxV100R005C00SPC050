// Copyright 2015 Google Inc. All Rights Reserved.
// Based on the EME draft spec from 2016 June 10.
// http://www.w3.org/TR/2016/WD-encrypted-media-20160610/"
#ifndef WVCDM_CDM_CDM_H_
#define WVCDM_CDM_CDM_H_

#if defined(_MSC_VER)
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef int int32_t;
typedef __int64 int64_t;
#else
# include <stdint.h>
#endif

#include <map>
#include <string>

// Define CDM_EXPORT to export functionality across shared library boundaries.
#if defined(WIN32)
# if defined(CDM_IMPLEMENTATION)
#  define CDM_EXPORT __declspec(dllexport)
# else
#  define CDM_EXPORT __declspec(dllimport)
# endif  // defined(CDM_IMPLEMENTATION)
#else  // defined(WIN32)
# if defined(CDM_IMPLEMENTATION)
#  define CDM_EXPORT __attribute__((visibility("default")))
# else
#  define CDM_EXPORT
# endif
#endif  // defined(WIN32)

namespace widevine {

class CDM_EXPORT ITimerClient {
 public:
  // Called by ITimer when a timer expires.
  virtual void onTimerExpired(void* context) = 0;

 protected:
  ITimerClient() {}
  virtual ~ITimerClient() {}
};

class CDM_EXPORT Cdm : public ITimerClient {
 public:
  // Session types defined by EME.
  typedef enum {
    kTemporary = 0,
    kPersistentLicense = 1,
    kPersistent = kPersistentLicense,  // deprecated name from June 1 draft
    kPersistentUsageRecord = 2,
  } SessionType;

  // Message types defined by EME.
  typedef enum {
    kLicenseRequest = 0,
    kLicenseRenewal = 1,
    kLicenseRelease = 2,
    kIndividualizationRequest = 3,  // Not used. Direct Individualization
                                    // is used instead of App-Assisted
  } MessageType;

  typedef enum {
    // These are defined by Widevine:
    kSuccess = 0,
    kNeedsDeviceCertificate = 1,
    kSessionNotFound = 2,
    kDecryptError = 3,
    kNoKey = 4,

    // These are analogous to the errors used by EME:
    kTypeError = 5,
    kInvalidAccess = kTypeError,  // deprecated name from June 1 draft
    kNotSupported = 6,
    kInvalidState = 7,
    kQuotaExceeded = 8,
    kRangeError = 9,

    // The action could not be completed yet but has been scheduled to be done
    // later.  A call to |event_listener.onDeferredComplete| will be made once
    // the action is complete.
    kDeferred = 99998,
    // This covers errors that we do not expect (see logs for details):
    kUnexpectedError = 99999,
  } Status;

  // These are the init data types defined by EME.
  typedef enum {
    kCenc = 0,
    kKeyIds = 1,  // NOTE: not supported by Widevine at this time
    kWebM = 2,

    // This type is not defined by EME but is supported by Widevine
    kHls = 10000,
  } InitDataType;

  // These are the crypto schemes supported by CENC 3.0.
  typedef enum {
    kClear = 0,
    kAesCtr = 1,  // AES-CTR, for use with cenc and cens modes
    kAesCbc = 2,  // AES-CBC, for use with cbc1 and cbcs modes
  } EncryptionScheme;

  // These are key statuses defined by EME.
  typedef enum {
    kUsable = 0,
    kExpired = 1,
    kOutputRestricted = 2,
    kOutputNotAllowed = kOutputRestricted,  // deprecated name from June 1 draft
    kStatusPending = 3,
    kInternalError = 4,
    kReleased = 5,
  } KeyStatus;

  // Permissible usages for a key. Returned as a set of flags; multiple
  // flags may be set. The specific settings are defined in the license
  // and the OEMCrypto Key Control Block. The CDM uses settings in the
  // license to derive these flags.
  typedef uint32_t KeyAllowedUsageFlags;
  static const KeyAllowedUsageFlags kAllowNone = 0;
  static const KeyAllowedUsageFlags kAllowDecryptToClearBuffer = 1;
  static const KeyAllowedUsageFlags kAllowDecryptToSecureBuffer = 2;
  static const KeyAllowedUsageFlags kAllowGenericEncrypt = 4;
  static const KeyAllowedUsageFlags kAllowGenericDecrypt = 8;
  static const KeyAllowedUsageFlags kAllowGenericSign = 16;
  static const KeyAllowedUsageFlags kAllowGenericSignatureVerify = 32;

  // These are defined by Widevine.  The CDM can be configured to decrypt in
  // three modes (dependent on OEMCrypto support).
  typedef enum {
    // Data is decrypted to an opaque handle.
    // Translates to OEMCrypto's OEMCrypto_BufferType_Secure.
    kOpaqueHandle = 0,

    // Decrypted data never returned to the caller, but is decoded and rendered
    // by OEMCrypto.
    // Translates to OEMCrypto's OEMCrypto_BufferType_Direct.
    kDirectRender = 1,

    // There is no secure output available, so all data is decrypted into a
    // clear buffer in main memory.
    // Translates to OEMCrypto's OEMCrypto_BufferType_Clear.
    kNoSecureOutput = 2,
  } SecureOutputType;

  // Logging levels defined by Widevine.
  // See Cdm::initialize().
  typedef enum {
    kSilent = -1,
    kErrors = 0,
    kWarnings = 1,
    kInfo = 2,
    kDebug = 3,
    kVerbose = 4,
  } LogLevel;

  // A map of key statuses.
  // See Cdm::getKeyStatuses().
  typedef std::map<std::string, KeyStatus> KeyStatusMap;

  // An event listener interface provided by the application and attached to
  // each CDM session.
  // See Cdm::createSession().
  class IEventListener {
   public:
    // A message (license request, renewal, etc.) to be dispatched to the
    // application's license server.
    // The response, if successful, should be provided back to the CDM via a
    // call to Cdm::update().
    virtual void onMessage(const std::string& session_id,
                           MessageType message_type,
                           const std::string& message) = 0;

    // There has been a change in the keys in the session or their status.
    virtual void onKeyStatusesChange(const std::string& session_id) = 0;

    // A remove() operation has been completed.
    virtual void onRemoveComplete(const std::string& session_id) = 0;

    // Called when a deferred action has completed.
    virtual void onDeferredComplete(const std::string& session_id,
                                    Status result) = 0;

    // Called when the CDM requires a new device certificate
    virtual void onDirectIndividualizationRequest(
        const std::string& session_id, const std::string& request) = 0;

   protected:
    IEventListener() {}
    virtual ~IEventListener() {}
  };

  // A storage interface provided by the application. This defines the "origin"
  // that the CDM will operate in by the files it can access.  Passing different
  // IStorage instances to Cdm::create will cause those CDM instances to be in
  // different "origins" as defined by the IStorage instance.  For example,
  // different IStorage instances could be tied to different folders for
  // different origins.
  //
  // It is important for multi-origin hosts to verify the application's origin.
  // This ensures that the application does not access files from another
  // origin.
  //
  // NOTE: It is important for users of your application to be able to clear
  // stored data.  Also, browsers or other multi-application systems should
  // store data separately per-app or per-origin.
  // See http://www.w3.org/TR/encrypted-media/#privacy-storedinfo.
  class IStorage {
   public:
    virtual bool read(const std::string& name,
                      std::string* data) = 0;
    virtual bool write(const std::string& name,
                       const std::string& data) = 0;
    virtual bool exists(const std::string& name) = 0;
    virtual bool remove(const std::string& name) = 0;
    virtual int32_t size(const std::string& name) = 0;

   protected:
    IStorage() {}
    virtual ~IStorage() {}
  };

  // A clock interface provided by the application, independent of CDM
  // instances.
  // See Cdm::initialize().
  class IClock {
   public:
    // Returns the current time in milliseconds since 1970 UTC.
    virtual int64_t now() = 0;

   protected:
    IClock() {}
    virtual ~IClock() {}
  };

  // A timer interface provided by the application, independent of CDM
  // instances.
  // See Cdm::initialize().
  class ITimer {
   public:
    // This typedef is for backward compatibility with v3.0.0.
    typedef ITimerClient IClient;

    // Call |client->onTimerExpired(context)| after a delay of |delay_ms| ms.
    virtual void setTimeout(int64_t delay_ms,
                            IClient* client,
                            void* context) = 0;

    // Cancel all timers associated with |client|.
    virtual void cancel(IClient *client) = 0;

   protected:
    ITimer() {}
    virtual ~ITimer() {}
  };

  // Client information, provided by the application, independent of CDM
  // instances.
  // See Cdm::initialize().
  // These parameters end up as client indentification in license requests.
  // All fields may be used by a license server proxy to drive business logic.
  // Some fields are required (indicated below), but please fill out as many
  // as make sense for your application.
  // No user-identifying information may be put in these fields!
  struct ClientInfo {
    // The name of the product or application, e.g. "TurtleTube"
    // Required.
    std::string product_name;

    // The name of the company who makes the device, e.g. "Kubrick, Inc."
    // Required.
    std::string company_name;

    // The name of the device, e.g. "HAL"
    std::string device_name;

    // The device model, e.g. "HAL 9000"
    // Required.
    std::string model_name;

    // The architecture of the device, e.g. "x86-64"
    std::string arch_name;

    // Information about the build of the browser, application, or platform into
    // which the CDM is integrated, e.g. "v2.71828, 2038-01-19-03:14:07"
    std::string build_info;
  };

  // Initialize the CDM library and provide access to platform services.
  // All platform interfaces are required.
  // Logging is controlled by |verbosity|.
  // Must be called and must return kSuccess before create() is called.
  static Status initialize(
      SecureOutputType secure_output_type,
      const ClientInfo& client_info,
      IStorage* storage,
      IClock* clock,
      ITimer* timer,
      LogLevel verbosity);

  // Query the CDM library version.
  static const char* version();

  // Constructs a new CDM instance.
  // initialize() must be called first and must return kSuccess before a CDM
  // instance may be constructed.
  // The CDM may notify of events at any time via the provided |listener|,
  // which may not be NULL.
  // |storage| defines the storage to use for this instance.  This can be used
  // to provide per-origin storage.  Passing NULL will use the storage passed
  // to initialize().
  // If |privacy_mode| is true, server certificates are required and will be
  // used to encrypt messages to the license server.
  // By using server certificates to encrypt communication with the license
  // server, device-identifying information cannot be extracted from the
  // license exchange process by an intermediate layer between the CDM and
  // the server.
  // This is particularly useful for browser environments, but is recommended
  // for use whenever possible.
  static Cdm* create(IEventListener* listener,
                     IStorage* storage,
                     bool privacy_mode);

  virtual ~Cdm() {}

  // Provides a server certificate to be used to encrypt messages to the
  // license server.
  // If |privacy_mode| was true in create() and setServerCertificate() is not
  // called, the CDM will attempt to provision a server certificate through
  // IEventListener::onMessage() with messageType == kLicenseRequest.
  // May not be called if |privacy_mode| was false.
  virtual Status setServerCertificate(const std::string& certificate) = 0;

  // Creates a new session.
  // Do not use this to load an existing persistent session.
  // If successful, the session_id is returned via |sessionId|.
  virtual Status createSession(SessionType session_type,
                               std::string* session_id) = 0;

  // Generates a request based on the initData.
  // The request will be provided via a synchronous call to
  // IEventListener::onMessage().
  // This is done so that license requests and renewals follow the same flow.
  virtual Status generateRequest(const std::string& session_id,
                                 InitDataType init_data_type,
                                 const std::string& init_data) = 0;

  // Loads an existing persisted session from storage.
  virtual Status load(const std::string& session_id) = 0;

  // Provides messages, including licenses, to the CDM.
  // If the message is a successful response to a release message, stored
  // session data will be removed for the session.
  virtual Status update(const std::string& session_id,
                        const std::string& response) = 0;

  // The time, in milliseconds since 1970 UTC, after which the key(s) in the
  // session will no longer be usable to decrypt media data, or -1 if no such
  // time exists.
  virtual Status getExpiration(const std::string& session_id,
                               int64_t* expiration) = 0;

  // A map of known key IDs to the current status of the associated key.
  virtual Status getKeyStatuses(const std::string& session_id,
                                KeyStatusMap* key_statuses) = 0;

  // Gets the permitted usage for a specific key by ID.
  virtual Status getKeyAllowedUsages(const std::string& session_id,
                                     const std::string& key_id,
                                     KeyAllowedUsageFlags* usage_flags) = 0;

  // Gets the permitted usage for a specific key by ID.
  // Search for key across all known sessions.  If there are keys in separate
  // sessions that match the given key_id, return kTypeError unless all such
  // keys have identical Allowed Usage settings.
  virtual Status getKeyAllowedUsages(const std::string& key_id,
                                     KeyAllowedUsageFlags* usage_flags) = 0;

  // Indicates that the application no longer needs the session and the CDM
  // should release any resources associated with it and close it.
  // Does not generate release messages for persistent sessions.
  // Does not remove stored session data for persistent sessions.
  virtual Status close(const std::string& session_id) = 0;

  // Removes stored session data associated with the session.
  // The session must be loaded before it can be removed.
  // Generates release messages, which must be delivered to the license server.
  // A reply from the license server must be provided via update() before the
  // session is fully removed.
  virtual Status remove(const std::string& session_id) = 0;

  // Describes a repeating pattern as defined by the CENC 3.0 standard. A
  // CENC 3.0 pattern consists of a number of encrypted blocks followed by a
  // number of clear blocks, after which it repeats.
  struct Pattern {
   public:
    Pattern()
      : encrypted_blocks(0),
        clear_blocks(0) {}

    Pattern(uint32_t encrypt, uint32_t clear)
      : encrypted_blocks(encrypt),
        clear_blocks(clear) {}

    // The number of crypto blocks that are encrypted and therefore need to be
    // decrypted.
    uint32_t encrypted_blocks;

    // The number of crypto blocks that are not encrypted and therefore should
    // be skipped when doing decryption.
    uint32_t clear_blocks;
  };

  struct InputBuffer {
   public:
    InputBuffer()
      : key_id(NULL),
        key_id_length(0),
        iv(NULL),
        iv_length(0),
        pattern(),
        data(NULL),
        data_length(0),
        block_offset(0),
        encryption_scheme(kAesCtr),
        is_video(true),
        first_subsample(true),
        last_subsample(true) {}

    const uint8_t* key_id;
    uint32_t key_id_length;

    // The IV is expected to be 16 bytes.
    const uint8_t* iv;
    uint32_t iv_length;

    // Describes the repeating pattern with which the content was encrypted.  If
    // left at its default value of (0,0), patterns will be disabled.  Should
    // only be changed for content that uses patterns, such as for CENC 3.0
    // "cens" and "cbcs" content or for HLS content.
    Pattern pattern;

    // This pointer and length describe the data to be decrypted.  This data
    // should be ready to be decrypted with no further processing.  If the data
    // is coming from a format that requires processing before decryption, that
    // processing needs to happen before the data is passed in here.  For
    // example, content coming from HLS will need to have its extra start code
    // emulation prevention removed before it is passed to Widevine.
    const uint8_t* data;
    uint32_t data_length;

    // |data|'s offset within its 16-byte AES block.  Only used for encrypted
    // subsamples from content using CENC standards before 3.0 or the
    // equivalent mode in CENC 3.0, "cenc" mode.  Should always be 0 in CENC 3.0
    // modes "cens," "cbc1," and "cbcs," as well as for HLS content.  When used,
    // it should start at 0 for each sample, then go up by |data_length| (mod
    // 16) after the |is_encrypted| part of each subsample.
    uint32_t block_offset;

    // Specifies the encryption scheme, if any, to be used to decrypt the data.
    // When set to kClear, decryption will copy the input data directly to the
    // output buffer.  This is necessary for secure output types, where the
    // output buffer cannot be directly accessed above the CDM.
    EncryptionScheme encryption_scheme;

    // Used by secure output type kDirectRender, where the secure hardware must
    // decode and render the decrypted content:
    bool is_video;
    bool first_subsample;
    bool last_subsample;
  };

  struct OutputBuffer {
    OutputBuffer()
      : data(NULL),
        data_length(0),
        data_offset(0),
        is_secure(false) {}

    // If |is_secure| is false or the secure output type is kNoSecureOutput,
    // this is a memory address in main memory.
    // If |is_secure| is true and the secure output type is kOpaqueHandle,
    // this is an opaque handle.
    // If |is_secure| is true and the secure output type is kDirectRender,
    // this is ignored.
    // See also SecureOutputType argument to initialize().
    uint8_t* data;

    // The maximum amount of data that can be decrypted to the buffer in this
    // call, starting from |data|.
    // Must be at least as large as the input buffer's |data_length|.
    // This size accounts for the bytes that will be skipped by |data_offset|.
    uint32_t data_length;

    // An offset applied to the output address.
    // Useful when |data| is an opaque handle rather than an address.
    uint32_t data_offset;

    // False for clear buffers, true otherwise.
    // Must be false if the secure output type is kNoSecureOutput.
    // See also SecureOutputType argument to initialize().
    bool is_secure;
  };

  // Decrypt the input as described by |input| and pass the output as described
  // in |output|.
  virtual Status decrypt(const InputBuffer& input,
                         const OutputBuffer& output) = 0;

  // Sets a value in the custom app settings.  These are settings
  // that are sent with any message to the license server.  These methods
  // should only be used by advanced users maintaining existing systems.
  // The |key| cannot be empty.
  virtual Status setAppParameter(const std::string& key,
                                 const std::string& value) = 0;

  // Gets the current value in the custom app settings.  If the key is
  // not present, then kTypeError is returned.  The |key| cannot be
  // empty.  |result| cannot be null.  See setAppParameter().
  virtual Status getAppParameter(const std::string& key,
                                 std::string* result) = 0;

  // Removes the value in the custom app settings.  If the key is not
  // present, then kTypeError is returned.  The |key| cannot be empty.
  // See setAppParameter().
  virtual Status removeAppParameter(const std::string& key) = 0;

  // Clears all the values in the custom app settings.  See setAppParameter().
  virtual Status clearAppParameters() = 0;

  // Generic crypto - functions for applying crypto operations to
  // app-level data (outside the content stream).

  typedef enum {
    kEncryptionAlgorithmUnknown,
    kEncryptionAlgorithmAesCbc128,
  } GenericEncryptionAlgorithmType;

  typedef enum {
    kSigningAlgorithmUnknown,
    kSigningAlgorithmHmacSha256
  } GenericSigningAlgorithmType;

  // Encrypts a buffer of app-level data.
  virtual Status genericEncrypt(
      const std::string& session_id, const std::string& in_buffer,
      const std::string& key_id, const std::string& iv,
      GenericEncryptionAlgorithmType algorithm, std::string* out_buffer) = 0;

  // Decrypts a buffer of app-level data.
  virtual Status genericDecrypt(
      const std::string& session_id, const std::string& in_buffer,
      const std::string& key_id, const std::string& iv,
      GenericEncryptionAlgorithmType algorithm, std::string* out_buffer) = 0;

  // Signs a buffer of app-level data.
  virtual Status genericSign(
      const std::string& session_id, const std::string& message,
      const std::string& key_id, GenericSigningAlgorithmType algorithm,
      std::string* signature) = 0;

  // Verifies the signature on a buffer of app-level data.
  // Returns kSuccess if signature is verified, otherwise returns kDecryptError.
  virtual Status genericVerify(
      const std::string& session_id, const std::string& message,
      const std::string& key_id, GenericSigningAlgorithmType algorithm,
      const std::string& signature) = 0;

 protected:
  Cdm() {}
};

}  // namespace widevine

#endif  // WVCDM_CDM_CDM_H_
