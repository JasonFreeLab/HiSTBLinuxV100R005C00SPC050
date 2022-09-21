#ifndef HI_DRM_DEFINES_H__
#define HI_DRM_DEFINES_H__

#include <string>
#include <list>
#include <map>

#include "hi_type.h"


#define HI_DRM_UUID_LEN (16)
#define HI_DRM_KEY_LEN (16)
#define HI_DRM_IV_LEN (16)

typedef enum hiDRM_EVENT_TYPE
{
    HI_DRM_EVENT_PROVISION_REQUIRED = 1,   /**<This event type indicates that the app needs to request a certificate from provisioning server */
    HI_DRM_EVENT_KEY_NEEDED,                /**<This event type indicates that the app needs to request keys from a license server */
    HI_DRM_EVENT_KEY_EXPIRED,               /**<This event type indicates that the licensed usage duration for keys in a session has expired */
    HI_DRM_EVENT_VENDOR_DEFINED,            /**<This event may indicate some specific vendor-defined condition,see your DRM provider documentation for details */
    HI_DRM_EVENT_SESSION_RECLAIMED,        /**<This event indicates that a session opened by the app has been reclaimed by the resource manager */
    HI_DRM_EVENT_EXPIRATION_UPDATE,        /**<expiration update */
    HI_DRM_EVENT_KEY_CHANGE,                /**<key changed event */
    HI_DRM_EVENT_DEFERRED_COMPLETE,
    HI_DRM_EVENT_REMOVE_COMPLETE,
    HI_DRM_EVENT_LICENSE_REQUEST,
    HI_DRM_EVENT_LICENSE_RENEWAL,
    HI_DRM_EVENT_LICENSE_RELEASE,
    HI_DRM_EVENT_KEY_BUTT
} HI_DRM_EVENT_TYPE;

typedef enum hiDRM_KEY_TYPE
{
    HI_DRM_KEY_TYPE_OFFLINE,        /**<keys will be for offline use,they will be saved to the device for use when the device is not connected to a network */
    HI_DRM_KEY_TYPE_STREAMING,      /**<This key request type species that the keys will be for online use, they will not be saved to the device for subsequent use when the device is not connected to a network.*/
    HI_DRM_KEY_TYPE_RELEASE,        /**<This key request type specifies that previously saved offline keys should be released. */
    HI_DRM_KEY_TYPE_BUTT
} HI_DRM_KEY_TYPE;

typedef enum hiDRM_KEYREQUEST_TYPE
{
    HI_DRM_KEYRST_TYPE_UNKNOWN,    /**<UNKNOWN type */
    HI_DRM_KEYRST_TYPE_INITIAL,    /**<Key request type is initial license request */
    HI_DRM_KEYRST_TYPE_RENEWAL,    /**<Key request type is license renewal */
    HI_DRM_KEYRST_TYPE_RELEASE,    /**<Key request type is license release */
    HI_DRM_KEYRST_TYPE_BUTT
} HI_DRM_KEYREQUEST_TYPE;

typedef enum hiDRM_KEYSTATUS_TYPE
{
    HI_DRM_KEYSTATUS_TYPE_USABLE,                /**<The key is currently usable to decrypt media data */
    HI_DRM_KEYSTATUS_TYPE_EXPIRED,               /**<The key is no longer usable to decrypt media data as expired */
    HI_DRM_KEYSTATUS_TYPE_OUTPUT_NOT_ALLOWED,   /**<The key is not currently usable to decrypt media data because its output requirements cannot currently be met*/
    HI_DRM_KEYSTATUS_TYPE_STATUS_PENDING,       /**<The status of the key is not yet known and is being determined */
    HI_DRM_KEYSTATUS_TYPE_INTERNAL_ERROR,       /**<The key is not currently usable to decrypt media data as internal error */
    HI_DRM_KEYSTATUS_TYPE_Released,
    HI_DRM_KEYSTATUS_TYPE_BUTT
} HI_DRM_KEYSTATUS_TYPE;

typedef struct hiDRM_KEYREQUEST
{
    std::string requestData;                /**< key request data delivered to license server*/
    HI_DRM_KEYREQUEST_TYPE eKeyRequestType;   /**< key request type,refer to ::HI_DRM_KEYREQUEST_TYPE */
    std::string defaultUrl;                        /**< default url of license server */
} HI_DRM_KEY_REQUEST;

typedef struct hiDRM_PROVITION_REQUEST
{
    std::string requestData;           /**<data delivered to provision server */
    std::string defaultUrl;                   /**< default url of provision server */
} HI_DRM_PROVITION_REQUEST;

typedef enum hiCRYPTO_MODE
{
    HI_CRYPTO_MODE_UNENCRYPTED = 0,     /**< no encrypted,not support*/
    HI_CRYPTO_MODE_AES_CTR     = 1,      /**< AES CRT mode */
    HI_CRYPTO_MODE_AES_WV      = 2,      /**< AES WV */
    HI_CRYPTO_MODE_AES_CBC      = 3,
} HI_CRYPTO_MODE;

typedef enum hiPLUGIN_MODE
{
    HI_PLUGIN_MODULAR = 0,
    HI_PLUGIN_CLASSIC = 1,
}HI_PLUGIN_MODE;

typedef struct hiDRM_SUBSAMPLES
{
public:
    hiDRM_SUBSAMPLES(HI_U32 numBytesOfClearData, HI_U32 numBytesOfEncryptedData)
        :u32numBytesOfClearData(numBytesOfClearData),
         u32numBytesOfEncryptedData(numBytesOfEncryptedData) {}

    HI_U32 u32numBytesOfClearData;      /**< number of clear data per sample,the unit is byte*/
    HI_U32 u32numBytesOfEncryptedData;  /**< number of encrypted data per sample,the unit is byte*/
} HI_DRM_SUBSAMPLES;

typedef struct hiDRM_PATTERN
{
public:
    hiDRM_PATTERN()
        :u32EncryptBlocks(0),
         u32SkipBlocks(0) {}

    hiDRM_PATTERN(HI_U32 encryptBlocks, HI_U32 skipBlocks)
        :u32EncryptBlocks(encryptBlocks),
         u32SkipBlocks(skipBlocks) {}

    HI_U32 u32EncryptBlocks;
    HI_U32 u32SkipBlocks;
}HI_DRM_PATTERN;

typedef struct hiKEY_STATUS
{
    std::string mKeyId;                 /**< key id */
    HI_DRM_KEYSTATUS_TYPE mType;          /**< key type,refer to ::HI_DRM_KEYSTATUS_TYPE */
} HI_KEY_STATUS;

typedef struct hiDRM_KEY_CHANGE
{
    std::list<HI_KEY_STATUS> stkeyStatusList;   /**< key status list */
    HI_BOOL bhasNewUsableKey;                /**< has new usable key */
} HI_DRM_KEY_CHANGE;

typedef struct hiDRM_EVENT_DATA
{
    HI_S32 s32extra;                       /**< drm event extra data */
    std::string data;                     /**< drm event data */
} HI_DRM_EVENT_DATA;

typedef struct hiDRM_MSG_DATA
{
    std::string sessionId;               /**< drm event data,sessionid */
    HI_DRM_EVENT_DATA stEventData;         /**< drm event data,not valid for HI_DRM_EVENT_KEY_EXPIRED,HI_DRM_EVENT_KEY_CHANGE*/
    HI_S64 s64expiryTimeInMS;             /**< drm event data,only for HI_DRM_EVENT_KEY_EXPIRED */
    HI_DRM_KEY_CHANGE stkeyChange;         /**< drm event data,only for HI_DRM_EVENT_KEY_CHANGE */
    HI_DRM_EVENT_TYPE eDrmEventType;
} HI_DRM_MSG_DATA;

/** Ref-counted object for callbacks */
class DrmListener
{
public:
    virtual HI_VOID notify(HI_DRM_EVENT_TYPE msg, HI_DRM_MSG_DATA* value) = 0;
};

#endif //HI_DRM_DEFINES_H__
