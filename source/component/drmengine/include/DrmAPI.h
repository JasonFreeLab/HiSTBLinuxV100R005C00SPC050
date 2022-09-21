/*
 * Copyright (C) 2013 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef DRM_API_H_
#define DRM_API_H_

#include <common/hi_type.h>
#include <utils/List.h>
#include <utils/String8.h>
#include <utils/Vector.h>
#include <utils/KeyedVector.h>
#include <utils/RefBase.h>
#include <utils/threads.h>

//  Loadable DrmEngine shared libraries should define the entry points
//  createDrmFactory and createCryptoFactory as shown below:
//
//  extern "C" {
//      extern android::DrmFactory *createDrmFactory();
//      extern android::CryptoFactory *createCryptoFactory();
//  }

typedef int status_t;

#define ERROR (-1)
#define OK (0)
#define DISALLOW_COPY_AND_ASSIGN(ClassName) \
    ClassName(const ClassName&); \
    void operator=(const ClassName&)

    class DrmPlugin;
    class DrmPluginListener;

    // DRMs are implemented in DrmEngine plugins, which are dynamically
    // loadable shared libraries that implement the entry points
    // createDrmFactory and createCryptoFactory.  createDrmFactory
    // constructs and returns an instance of a DrmFactory object.  Similarly,
    // createCryptoFactory creates an instance of a CryptoFactory object.
    // When a MediaCrypto or MediaDrm object needs to be constructed, all
    // available DrmEngines present in the plugins directory on the device
    // are scanned for a matching DrmEngine that can support the crypto
    // scheme.  When a match is found, the DrmEngine's createCryptoPlugin and
    // createDrmPlugin methods are used to create CryptoPlugin or
    // DrmPlugin instances to support that DRM scheme.

    class DrmFactory {
    public:
        DrmFactory() {}
        virtual ~DrmFactory() {}

        // DrmFactory::isCryptoSchemeSupported can be called to determine
        // if the plugin factory is able to construct plugins that support a
        // given crypto scheme, which is specified by a UUID.
        virtual bool isCryptoSchemeSupported(const uint8_t uuid[16]) = 0;

        // DrmFactory::isContentTypeSupported can be called to determine
        // if the plugin factory is able to construct plugins that support a
        // given media container format specified by mimeType
        virtual bool isContentTypeSupported(const String8& mimeType) = 0;

        // Construct a DrmPlugin for the crypto scheme specified by UUID.
        virtual status_t createPlugin(
                const uint8_t uuid[16], DrmPlugin **plugin) = 0;

    private:
        DrmFactory(const DrmFactory &);
        DrmFactory &operator=(const DrmFactory &);
    };

    class DrmPlugin {
    public:
        enum EventType {
            kDrmPluginEventProvisionRequired = 1,
            kDrmPluginEventKeyNeeded,
            kDrmPluginEventKeyExpired,
            kDrmPluginEventVendorDefined,
            kDrmPluginEventSessionReclaimed,
            kDrmPluginEventExpirationUpdate,
            kDrmPluginEventKeysChange,
            kDrmPluginEventDeferredComplete,
            kDrmPluginEventRemoveComplete,
            kDrmPluginEventLicenseRequest,
            kDrmPluginEventLicenseRenewal,
            kDrmPluginEventLicenseRelease,
        };

        // Drm keys can be for offline content or for online streaming.
        // Offline keys are persisted on the device and may be used when the device
        // is disconnected from the network.  The Release type is used to request
        // that offline keys be no longer restricted to offline use.
        enum KeyType {
            kKeyType_Offline,
            kKeyType_Streaming,
            kKeyType_Release
        };

        // Enumerate KeyRequestTypes to allow an app to determine the
        // type of a key request returned from getKeyRequest.
        enum KeyRequestType {
            kKeyRequestType_Unknown,
            kKeyRequestType_Initial,
            kKeyRequestType_Renewal,
            kKeyRequestType_Release
        };

        // Enumerate KeyStatusTypes which indicate the state of a key
        enum KeyStatusType
        {
            kKeyStatusType_Usable,
            kKeyStatusType_Expired,
            kKeyStatusType_OutputNotAllowed,
            kKeyStatusType_StatusPending,
            kKeyStatusType_InternalError,
            kKeyStatusType_Released
        };

        // Used by sendKeysChange to report the usability status of each
        // key to the app.
        struct KeyStatus
        {
            Vector<HI_U8> mKeyId;
            KeyStatusType mType;
        };

        DrmPlugin() {}
        virtual ~DrmPlugin() {}

        // Open a new session with the DrmPlugin object.  A session ID is returned
        // in the sessionId parameter.
        virtual status_t openSession(Vector<HI_U8>& sessionId) = 0;

        // Close a session on the DrmPlugin object.
        virtual status_t closeSession(Vector<HI_U8> const& sessionId) = 0;

        // A key request/response exchange occurs between the app and a License
        // Server to obtain the keys required to decrypt the content.  getKeyRequest()
        // is used to obtain an opaque key request blob that is delivered to the
        // license server.
        //
        // The scope parameter may be a sessionId or a keySetId, depending on the
        // specified keyType.  When the keyType is kKeyType_Offline or
        // kKeyType_Streaming, scope should be set to the sessionId the keys will be
        // provided to.  When the keyType is kKeyType_Release, scope should be set to
        // the keySetId of the keys being released.  Releasing keys from a device
        // invalidates them for all sessions.
        //
        // The init data passed to getKeyRequest is container-specific and its
        // meaning is interpreted based on the mime type provided in the mimeType
        // parameter to getKeyRequest.  It could contain, for example, the content
        // ID, key ID or other data obtained from the content metadata that is required
        // in generating the key request.  Init may be null when keyType is
        // kKeyType_Release.
        //
        // mimeType identifies the mime type of the content
        //
        // keyType specifies if the keys are to be used for streaming or offline content
        //
        // optionalParameters are included in the key request message to allow a
        // client application to provide additional message parameters to the server.
        //
        // If successful, the opaque key request blob is returned to the caller.
        virtual status_t
        getKeyRequest(Vector<HI_U8> const& scope,
                      Vector<HI_U8> const& initData,
                      String8 const& mimeType, KeyType keyType,
                      KeyedVector<String8, String8> const& optionalParameters,
                      Vector<HI_U8>& request, String8& defaultUrl,
                      KeyRequestType* keyRequestType) = 0;

        //
        // After a key response is received by the app, it is provided to the
        // Drm plugin using provideKeyResponse.
        //
        // scope may be a sessionId or a keySetId depending on the type of the
        // response.  Scope should be set to the sessionId when the response is
        // for either streaming or offline key requests.  Scope should be set to the
        // keySetId when the response is for a release request.
        //
        // When the response is for an offline key request, a keySetId is returned
        // in the keySetId vector parameter that can be used to later restore the
        // keys to a new session with the method restoreKeys. When the response is
        // for a streaming or release request, no keySetId is returned.
        //
        virtual status_t provideKeyResponse(Vector<HI_U8> const& scope,
                                        Vector<HI_U8> const& response,
                                        Vector<HI_U8>& keySetId) = 0;


        virtual status_t getPropertyString(String8 const& name, String8& value) = 0;

        virtual status_t setPropertyString(String8 const& name, String8& value) = 0;

        status_t setListener(const DrmPluginListener* listener) {
            mListener = const_cast<DrmPluginListener*>(listener);
            return OK;
        }

    protected:
        // Plugins call these methods to deliver events to the java app
        void sendEvent(EventType eventType, int extra,
                       Vector<HI_U8> const& sessionId,
                       Vector<HI_U8> const& data);

        void sendExpirationUpdate(Vector<HI_U8> const& sessionId,
                                  int64_t expiryTimeInMS);

        void sendKeysChange(Vector<HI_U8> const& sessionId,
                            std::list<DrmPlugin::KeyStatus> keyStatusList,
                            bool hasNewUsableKey);

        void sendDeferredComplete(Vector<HI_U8> const& sessionId, status_t sessionStatus);

    private:
        DrmPluginListener* mListener;

        DISALLOW_COPY_AND_ASSIGN(DrmPlugin);
    };

    class DrmPluginListener
    {
    public:
        virtual void sendEvent(DrmPlugin::EventType eventType, int extra,
                               Vector<HI_U8> const& sessionId,
                               Vector<HI_U8> const& data) = 0;

        virtual void sendExpirationUpdate(Vector<HI_U8> const& sessionId,
                                          int64_t expiryTimeInMS) = 0;

        virtual void sendKeysChange(Vector<HI_U8> const& sessionId,
                                    std::list<DrmPlugin::KeyStatus> keyStatusList,
                                    bool hasNewUsableKey) = 0;

        virtual void sendDeferredComplete(Vector<HI_U8> const& sessionId, status_t sessionStatus) = 0;
    };

    inline void DrmPlugin::sendEvent(EventType eventType, int extra,
                                     Vector<HI_U8> const& sessionId,
                                     Vector<HI_U8> const& data) {
        DrmPluginListener* listener = mListener;

        if (listener != NULL) {
            listener->sendEvent(eventType, extra, sessionId, data);
        }
    }

    inline void DrmPlugin::sendExpirationUpdate(Vector<HI_U8> const& sessionId,
                                                int64_t expiryTimeInMS) {
        DrmPluginListener* listener = mListener;

        if (listener != NULL) {
            listener->sendExpirationUpdate(sessionId, expiryTimeInMS);
        }
    }

    inline void DrmPlugin::sendKeysChange(Vector<HI_U8> const& sessionId,
                                          std::list<DrmPlugin::KeyStatus> keyStatusList,
                                          bool hasNewUsableKey) {
        DrmPluginListener* listener = mListener;

        if (listener != NULL) {
            listener->sendKeysChange(sessionId, keyStatusList, hasNewUsableKey);
        }
    }

    inline void DrmPlugin::sendDeferredComplete(Vector<HI_U8> const& sessionId, status_t sessionStatus)
    {
        DrmPluginListener* listener = mListener;
        if (listener != NULL) {
            listener->sendDeferredComplete(sessionId, sessionStatus);
        }
    }

#endif // DRM_API_H_

