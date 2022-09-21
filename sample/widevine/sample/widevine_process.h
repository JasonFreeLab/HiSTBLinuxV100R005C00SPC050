#ifndef __WIDEVINE_PROCESS_H__
#define __WIDEVINE_PROCESS_H__

#include "general_define.h"
#include "cdm.h"
#include "cdm_test_printers.h"
#include "modular_widevine.h"
#include "license_request.h"
#include "log.h"
#include "OEMCryptoCENC.h"
#include "override.h"
#include "properties_ce.h"
#include "scoped_ptr.h"
#include "string_conversions.h"
#include "test_host.h"
#include "url_request.h"
#include "file_parser.h"

using namespace std;
using namespace wvcdm;
using namespace widevine;

#define ASSERT_TRUE(A) \
    if (HI_TRUE == (A)) \
    {\
        WVLOGE("failed!\n"); \
    }

#define ASSERT_FALSE(A) \
    if (HI_FALSE == (A)) \
    {\
        WVLOGE("failed!\n"); \
    }

#define ASSERT_EQ(A, B) \
    if ((A) != (B)) \
    {\
        WVLOGE("failed!\n"); \
    }

#define ASSERT_NE(A, B) \
    if ((A) == (B)) \
    {\
        WVLOGE("failed!\n"); \
    }

#define EXPECT_EQ(A, B) \
    if ((A) != (B)) \
    {\
        WVLOGE("failed!\n"); \
        return HI_FAILURE; \
    }

#define EXPECT_TRUE(A) \
    if (HI_FALSE == (A)) \
    {\
        WVLOGE("failed!\n"); \
        return HI_FAILURE; \
    }

struct SubSample
{
    HI_U32 mNumBytesOfClearData;
    HI_U32 mNumBytesOfEncryptedData;
};

class IWidevineProcess : public Cdm::IEventListener
{
public:
    virtual ~IWidevineProcess() {};
    virtual HI_S32 StartWidevineProcess(IN string key_id, IN string url, OUT HI_U8* content_key, OUT HI_U32& content_key_length) = 0;
    virtual HI_S32 DecryptData(IN STRU_FRAME_PARAM* param, IN const std::string& keyid, OUT void* outputBuffer) = 0;

    virtual HI_VOID onMessage(const std::string& session_id, Cdm::MessageType message_type, const std::string& message) = 0;
    virtual HI_VOID onKeyStatusesChange(const std::string& session_id) = 0;
    virtual HI_VOID onRemoveComplete(const std::string& session_id) = 0;
    virtual HI_VOID onDeferredComplete(const std::string& session_id, Cdm::Status result) = 0;
    virtual HI_VOID onDirectIndividualizationRequest(const std::string& session_id, const std::string& request) = 0;
};

class TvpSampleWidevineProcess
{
public:
    TvpSampleWidevineProcess();
    virtual ~TvpSampleWidevineProcess();
    HI_S32 StartWidevineProcess(IN string key_id, IN string url, OUT HI_U8* content_key, OUT HI_U32& content_key_length);
    HI_S32 DecryptData(STRU_FRAME_PARAM* param, const std::string& keyid, void* outputBuffer);
private:
    IWidevineProcess* mProxy;
};

#endif //__WIDEVINE_PROCESS_H__
