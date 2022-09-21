#ifndef DRM_ENGINE_INTERFACE_H_
#define DRM_ENGINE_INTERFACE_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define MAX_REQUEST_DATA_SIZE (32768)
#define MAX_RESPONSE_DATA_SIZE (32768)
#define MAX_DEFAULT_URL_SIZE (8192)
#define KEY_ID_LENGTH (16)

typedef enum hiPLUGIN_MODE
{
    HI_PLUGIN_MODULAR = 0,
    HI_PLUGIN_CLASSIC = 1,
}HI_PLUGIN_MODE;

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

typedef struct hiDRM_CTYPE_KEYREQUEST
{
    HI_U8 requestData[MAX_REQUEST_DATA_SIZE];                /**< key request data delivered to license server*/
    HI_U32 requestDataLen;
    HI_DRM_KEYREQUEST_TYPE eKeyRequestType;   /**< key request type,refer to ::HI_DRM_KEYREQUEST_TYPE */
    HI_CHAR defaultUrl[MAX_DEFAULT_URL_SIZE];                        /**< default url of license server */
} HI_DRM_CTYPE_KEY_REQUEST;

typedef enum hiCRYPTO_MODE
{
    HI_CRYPTO_MODE_UNENCRYPTED = 0,     /**< no encrypted,not support*/
    HI_CRYPTO_MODE_AES_CTR     = 1,      /**< AES CRT mode */
    HI_CRYPTO_MODE_AES_WV      = 2,      /**< AES WV */
    HI_CRYPTO_MODE_AES_CBC      = 3,
} HI_CRYPTO_MODE;

typedef struct hiDRM_SUBSAMPLES
{
    HI_U32 u32numBytesOfClearData;      /**< number of clear data per sample,the unit is byte*/
    HI_U32 u32numBytesOfEncryptedData;  /**< number of encrypted data per sample,the unit is byte*/
} HI_DRM_SUBSAMPLES;

typedef struct hiDRM_PATTERN
{
    HI_U32 u32EncryptBlocks;
    HI_U32 u32SkipBlocks;
}HI_DRM_PATTERN;

HI_S32 HI_DrmEngine_Create(HI_VOID **ppHandle, const HI_U8* uuid, const HI_CHAR* mimetype, HI_PLUGIN_MODE pluginmode);

HI_VOID HI_DrmEngine_Destroy(HI_VOID *pHandle);

HI_BOOL HI_DrmEngine_IsCryptoSchemeSupported(HI_VOID *pHandle, const HI_U8* uuid, const HI_CHAR* mimetype);

HI_S32 HI_DrmEngine_OpenSession(HI_VOID *pHandle);

HI_S32 HI_DrmEngine_CloseSession(HI_VOID *pHandle);

HI_S32 HI_DrmEngine_GetKeyRequest(HI_VOID *pHandle,
                                  const HI_U8* initData,
                                  HI_U32 initDataLen,
                                  const HI_U8* mimeType,
                                  HI_DRM_KEY_TYPE keyType,
                                  HI_DRM_CTYPE_KEY_REQUEST* pKeyRequest);

HI_S32 HI_DrmEngine_ProvideKeyResponse(HI_VOID *pHandle, HI_U8* response, HI_U32 responseLen, HI_U8* keySetId);

HI_S32 HI_DrmEngine_PRFetchLicense(HI_VOID *pHandle, HI_DRM_CTYPE_KEY_REQUEST stKeyRequest, HI_U8* keyID);
    
HI_S32 HI_DrmEngine_Decrypt(HI_VOID *pHandle, HI_BOOL secure, const HI_U8* key, const HI_U8* iv,
                                  const HI_DRM_PATTERN pattern, HI_CRYPTO_MODE mode, HI_U8* pSrc,
                                  const HI_DRM_SUBSAMPLES *subSamples, HI_S32 numSubSamples,
                                  HI_VOID* pDst);

HI_S32 HI_DrmEngine_GetPropertyString(HI_VOID *pHandle, const HI_U8* name, const HI_U8*value);

HI_S32 HI_DrmEngine_SetPropertyString(HI_VOID *pHandle, const HI_U8*name, const HI_U8*value);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* DRM_ENGINE_INTERFACE_H_*/
