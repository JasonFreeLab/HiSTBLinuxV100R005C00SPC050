#ifndef HI_DRM_DEFINES_H__
#define HI_DRM_DEFINES_H__

#include <string>
#include <list>
#include <map>

#include "hi_type.h"
#include <utils/String8.h>
#include <utils/Vector.h>
#include "drm_engine_interface.h"

using namespace android;

namespace drmengine {

#define HI_DRM_UUID_LEN (16)
#define HI_DRM_KEY_LEN (16)
#define HI_DRM_IV_LEN (16)

typedef struct hiDRM_KEYREQUEST
{
    Vector<HI_U8> requestData;                /**< key request data delivered to license server*/
    HI_DRM_KEYREQUEST_TYPE eKeyRequestType;   /**< key request type,refer to ::HI_DRM_KEYREQUEST_TYPE */
    String8 defaultUrl;                        /**< default url of license server */
} HI_DRM_KEY_REQUEST;

typedef struct hiDRM_PROVITION_REQUEST
{
    Vector<HI_U8> requestData;           /**<data delivered to provision server */
    String8 defaultUrl;                   /**< default url of provision server */
} HI_DRM_PROVITION_REQUEST;

typedef struct hiKEY_STATUS
{
    Vector<HI_U8> mKeyId;                 /**< key id */
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
    Vector<HI_U8> data;                     /**< drm event data */
} HI_DRM_EVENT_DATA;

typedef struct hiDRM_MSG_DATA
{
    Vector<HI_U8> sessionId;               /**< drm event data,sessionid */
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

}

#endif //HI_DRM_DEFINES_H__
