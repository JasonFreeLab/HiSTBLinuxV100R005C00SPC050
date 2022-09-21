// Copyright 2012 Google Inc. All Rights Reserved.

#ifndef WVCDM_CORE_WV_CDM_CONSTANTS_H_
#define WVCDM_CORE_WV_CDM_CONSTANTS_H_

#include <string>

namespace wvcdm {
static const size_t KEY_CONTROL_SIZE = 16;
static const size_t KEY_ID_SIZE = 16;
static const size_t KEY_IV_SIZE = 16;
static const size_t KEY_PAD_SIZE = 16;
static const size_t KEY_SIZE = 16;
static const size_t MAC_KEY_SIZE = 32;
static const size_t KEYBOX_KEY_DATA_SIZE = 72;

// Use 0 to represent never expired license as specified in EME spec
// (NaN in JS translates to 0 in unix timestamp).
static const int64_t NEVER_EXPIRES = 0;

static const char SESSION_ID_PREFIX[] = "sid";
static const char KEY_SET_ID_PREFIX[] = "ksid";
static const char KEY_SYSTEM[] = "com.widevine";

// define query keys, values here
static const std::string QUERY_KEY_LICENSE_TYPE = "LicenseType";
                                                    // "Streaming", "Offline"
static const std::string QUERY_KEY_PLAY_ALLOWED = "PlayAllowed";
                                                    // "True", "False"
static const std::string QUERY_KEY_PERSIST_ALLOWED = "PersistAllowed";
                                                    // "True", "False"
static const std::string QUERY_KEY_RENEW_ALLOWED = "RenewAllowed";
                                                    // "True", "False"
static const std::string QUERY_KEY_LICENSE_DURATION_REMAINING =
    "LicenseDurationRemaining";                     // non-negative integer
static const std::string QUERY_KEY_PLAYBACK_DURATION_REMAINING =
    "PlaybackDurationRemaining";                    // non-negative integer
static const std::string QUERY_KEY_RENEWAL_SERVER_URL = "RenewalServerUrl";
                                                    // url
static const std::string QUERY_KEY_OEMCRYPTO_SESSION_ID = "OemCryptoSessionId";
                                                    // session id
static const std::string QUERY_KEY_SECURITY_LEVEL = "SecurityLevel";
                                                    // "L1", "L3"
static const std::string QUERY_KEY_DEVICE_ID = "DeviceID";
                                               // device unique id
static const std::string QUERY_KEY_SYSTEM_ID = "SystemID";
                                               // system id
static const std::string QUERY_KEY_PROVISIONING_ID = "ProvisioningID";
                                               // provisioning unique id
static const std::string QUERY_KEY_CURRENT_HDCP_LEVEL = "HdcpLevel";
                                                        // current HDCP level
static const std::string QUERY_KEY_MAX_HDCP_LEVEL = "MaxHdcpLevel";
                                                // maximum supported HDCP level
static const std::string QUERY_KEY_USAGE_SUPPORT = "UsageSupport";
                                        // whether usage reporting is supported
static const std::string QUERY_KEY_NUMBER_OF_OPEN_SESSIONS =
    "NumberOfOpenSessions";
static const std::string QUERY_KEY_MAX_NUMBER_OF_SESSIONS =
    "MaxNumberOfSessions";
static const std::string QUERY_KEY_OEMCRYPTO_API_VERSION =
    "OemCryptoApiVersion";

static const std::string QUERY_VALUE_TRUE = "True";
static const std::string QUERY_VALUE_FALSE = "False";
static const std::string QUERY_VALUE_STREAMING = "Streaming";
static const std::string QUERY_VALUE_OFFLINE = "Offline";
static const std::string QUERY_VALUE_SECURITY_LEVEL_L1 = "L1";
static const std::string QUERY_VALUE_SECURITY_LEVEL_L2 = "L2";
static const std::string QUERY_VALUE_SECURITY_LEVEL_L3 = "L3";
static const std::string QUERY_VALUE_SECURITY_LEVEL_UNKNOWN = "Unknown";
static const std::string QUERY_VALUE_DISCONNECTED = "Disconnected";
static const std::string QUERY_VALUE_UNPROTECTED = "Unprotected";
static const std::string QUERY_VALUE_HDCP_V1 = "HDCP-1.x";
static const std::string QUERY_VALUE_HDCP_V2_0 = "HDCP-2.0";
static const std::string QUERY_VALUE_HDCP_V2_1 = "HDCP-2.1";
static const std::string QUERY_VALUE_HDCP_V2_2 = "HDCP-2.2";

static const std::string ISO_BMFF_VIDEO_MIME_TYPE = "video/mp4";
static const std::string ISO_BMFF_AUDIO_MIME_TYPE = "audio/mp4";
static const std::string WEBM_VIDEO_MIME_TYPE = "video/webm";
static const std::string WEBM_AUDIO_MIME_TYPE = "audio/webm";
static const std::string CENC_INIT_DATA_FORMAT = "cenc";
static const std::string HLS_INIT_DATA_FORMAT = "hls";
static const std::string WEBM_INIT_DATA_FORMAT = "webm";

static const std::string HLS_KEYFORMAT_ATTRIBUTE = "KEYFORMAT";
static const std::string HLS_KEYFORMAT_VERSIONS_ATTRIBUTE = "KEYFORMATVERSIONS";
static const std::string HLS_KEYFORMAT_VERSION_VALUE_1 = "1";
static const std::string HLS_METHOD_ATTRIBUTE = "METHOD";
static const std::string HLS_METHOD_AES_128 = "AES-128";
static const std::string HLS_METHOD_NONE = "NONE";
static const std::string HLS_METHOD_SAMPLE_AES = "SAMPLE-AES";
static const std::string HLS_IV_ATTRIBUTE = "IV";
static const std::string HLS_URI_ATTRIBUTE = "URI";

static const char EMPTY_ORIGIN[] = "";
}  // namespace wvcdm

#endif  // WVCDM_CORE_WV_CDM_CONSTANTS_H_
