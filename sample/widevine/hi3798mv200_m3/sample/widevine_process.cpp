
#include <arpa/inet.h>

#include "widevine_process.h"


using namespace wvcdm;
using namespace widevine;

#define PATH_STR_LENGTH 256

typedef struct
{
    HI_CHAR szstring[PATH_STR_LENGTH];
    HI_U8  *pu8Addr;
    HI_S32  s32length;
}KEYBOX_FILE_S;

// for test
string key_id_test = "30303030303030303030303030303035";
//string url_test = "http://widevine-proxy.appspot.com/proxy";
string url_test = "https://proxy.uat.widevine.com/proxy?video_id=&provider=widevine_test";
string url_provision = "https://www.googleapis.com/certificateprovisioning/v1/devicecertificates/create?key=AIzaSyB-5OLKTx2iU5mko18DfdwK5611JIjbUhE";
string content_key_test = "9ac3036e04ac9d2be946ed62405149bc";

const std::string kCencInitData_test = a2bs_hex(
    "00000047"                          // blob size
    "70737368"                          // "pssh"
    "00000000"                          // flags
    "edef8ba979d64acea3c827dcd51d21ed"  // Widevine system id, assume is the key id.
    "00000027"                          // pssh data size
    // pssh data:
    "08011201301A0D7769646576696E655F"
    "74657374220A323031355F7465617273"
    "2A05415544494F");

//default server certificate.
const std::string kDefaultServerCertificate = a2bs_hex(
    "0ABF020803121028703454C008F63618ADE7443DB6C4C8188BE7F99005228E023082010A02"
    "82010100B52112B8D05D023FCC5D95E2C251C1C649B4177CD8D2BEEF355BB06743DE661E3D"
    "2ABC3182B79946D55FDC08DFE95407815E9A6274B322A2C7F5E067BB5F0AC07A89D45AEA94"
    "B2516F075B66EF811D0D26E1B9A6B894F2B9857962AA171C4F66630D3E4C602718897F5E1E"
    "F9B6AAF5AD4DBA2A7E14176DF134A1D3185B5A218AC05A4C41F081EFFF80A3A040C50B09BB"
    "C740EEDCD8F14D675A91980F92CA7DDC646A06ADAD5101F74A0E498CC01F00532BAC217850"
    "BD905E90923656B7DFEFEF42486767F33EF6283D4F4254AB72589390BEE55808F1D668080D"
    "45D893C2BCA2F74D60A0C0D0A0993CEF01604703334C3638139486BC9DAF24FD67A07F9AD9"
    "4302030100013A1273746167696E672E676F6F676C652E636F6D128003983E30352675F40B"
    "A715FC249BDAE5D4AC7249A2666521E43655739529721FF880E0AAEFC5E27BC980DAEADABF"
    "3FC386D084A02C82537848CC753FF497B011A7DA97788A00E2AA6B84CD7D71C07A48EBF616"
    "02CCA5A3F32030A7295C30DA915B91DC18B9BC9593B8DE8BB50F0DEDC12938B8E9E039CDDE"
    "18FA82E81BB032630FE955D85A566CE154300BF6D4C1BD126966356B287D657B18CE63D0EF"
    "D45FC5269E97EAB11CB563E55643B26FF49F109C2101AFCAF35B832F288F0D9D45960E259E"
    "85FB5D24DBD2CF82764C5DD9BF727EFBE9C861F869321F6ADE18905F4D92F9A6DA6536DB84"
    "75871D168E870BB2303CF70C6E9784C93D2DE845AD8262BE7E0D4E2E4A0759CEF82D109D25"
    "92C72429F8C01742BAE2B3DECADBC33C3E5F4BAF5E16ECB74EADBAFCB7C6705F7A9E3B6F39"
    "40383F9C5116D202A20C9229EE969C2519718303B50D0130C3352E06B014D838540F8A0C22"
    "7C0011E0F5B38E4E298ED2CB301EB4564965F55C5D79757A250A4EB9C84AB3E6539F6B6FDF"
    "56899EA29914");

const std::string kProvisioningServerUrl =
    "https://www.googleapis.com/"
    "certificateprovisioning/v1/devicecertificates/create"
    "?key=AIzaSyB-5OLKTx2iU5mko18DfdwK5611JIjbUhE";

static inline HI_U64 htonq (HI_U64 v)
{
    return htonl ((HI_U32) (v >> 32))
           | (HI_U64) htonl ((HI_U32) v) << 32;
}

static inline HI_U64 ntohq (HI_U64 v)
{
    return ntohl ((HI_U32) (v >> 32))
           | (HI_U64) ntohl ((HI_U32) v) << 32;
}
#ifdef SET_ENCPRYT_KEYBOX
static HI_S32 Widevine_ReadDevCert(KEYBOX_FILE_S *pDevcert)
{
    HI_S32 s32Ret = HI_SUCCESS;
    FILE *fp_DevCert = NULL;
    HI_U32 u32Len;
    HI_U8 *pu8Tmp = NULL;

    if ( NULL == pDevcert )
    {
        WVLOGE("Invalid param, null pointer!\n");
        return HI_FAILURE;
    }

    fp_DevCert = fopen(pDevcert->szstring,"rb");
    if(NULL == fp_DevCert)
    {
        WVLOGE("open file '%s' error!\n", (char *)pDevcert->szstring);
        return HI_FAILURE;
    }

    fseek(fp_DevCert,0,SEEK_END);
    pDevcert->s32length = (HI_S32)ftell(fp_DevCert);
    rewind(fp_DevCert);
    //printf("file length:%d!\n", pDevcert->s32length);

    if(pDevcert->s32length <= 0)
    {
        WVLOGE("ftell file '%s' error!\n", (char *)pDevcert->szstring);
        s32Ret = HI_FAILURE;
        goto __Quit;
    }
    pu8Tmp = (HI_U8 *)malloc((unsigned long)pDevcert->s32length);
    if(NULL == pu8Tmp)
    {
        WVLOGE("malloc size 0x%x error!\n", pDevcert->s32length);
        s32Ret = HI_FAILURE;
        goto __Quit;
    }
    u32Len = fread(pu8Tmp, 1, (unsigned long)pDevcert->s32length, fp_DevCert);
    if(u32Len != (HI_U32)pDevcert->s32length)
    {
        WVLOGE("Read '%s' failed. real size(0x%x), should be size(0x%08x).\n", (char *)pDevcert->szstring, u32Len, pDevcert->s32length);
        s32Ret = HI_FAILURE;
        goto __Quit;
    }

    pDevcert->pu8Addr = pu8Tmp;

__Quit:
    if ( NULL != fp_DevCert)
    {
        fclose(fp_DevCert);
        fp_DevCert = NULL;
    }

    if ( HI_FAILURE == s32Ret)
    {
        if ( NULL != pu8Tmp)
        {
            free(pu8Tmp);
            pu8Tmp = NULL;
        }
    }

    return s32Ret;
}
#endif

class WidevineProcessImpl : public IWidevineProcess
{
public:
    WidevineProcessImpl() : m_strMsg("") {}
    virtual ~WidevineProcessImpl() {}

    virtual HI_VOID onMessage(const std::string& session_id, Cdm::MessageType message_type, const std::string& message);
    virtual HI_VOID onKeyStatusesChange(const std::string& session_id);
    virtual HI_VOID onRemoveComplete(const std::string& session_id);
    virtual HI_VOID onDeferredComplete(const std::string& session_id, Cdm::Status result);
    virtual HI_VOID onDirectIndividualizationRequest(const std::string& session_id, const std::string& request);

    virtual HI_S32 StartWidevineProcess(IN string key_id, IN string url, OUT HI_U8* content_key, OUT HI_U32& content_key_length);
    virtual HI_S32 DecryptData(IN STRU_FRAME_PARAM* param, IN const std::string& keyid, OUT void* outputBuffer);

    HI_VOID CreateAdditionalCdm(bool privacy_mode, scoped_ptr<Cdm>* cdm);
    HI_VOID RecreateCdm(bool privacy_mode);
    HI_S32 Fetch(const std::string& url, const std::string& message, std::string* response, int* status_code);
    HI_U32 FetchLicense(const std::string& license_server, const std::string& message, std::string* response);
    HI_S32 FetchCertificate(const std::string& url, std::string* response);
    std::string GetRequestResponse(const std::string& message);
    std::string GetProvisionResponse(const std::string& message);
    void incrementIV(HI_U64 increaseBy, HI_U8* ivPtr);
    Cdm::Status countEncryptedBlocksInPatternedRange(HI_U32 range, HI_U32 startingOffset, const Cdm::Pattern& pattern,
            HI_U32 startingPatternOffset, HI_U64* result);

private:
    scoped_ptr<Cdm> cdm_;
    TestHost* widevine_host = NULL;
    const int kHttpOk = 200;
    std::string m_strMsg;
};

HI_VOID WidevineProcessImpl::onMessage(const std::string& session_id, Cdm::MessageType message_type, const std::string& message)
{
    WVLOGD("Enter function %s\n", __FUNCTION__);
    m_strMsg = message;
    //WVLOGD("request body_sunlei: %s", b2a_hex(m_strMsg).c_str());
}

HI_VOID WidevineProcessImpl::onKeyStatusesChange(const std::string& session_id)
{
    WVLOGD("Enter function %s\n", __FUNCTION__);
}

HI_VOID WidevineProcessImpl::onRemoveComplete(const std::string& session_id)
{
    WVLOGD("Enter function %s\n", __FUNCTION__);
}

HI_VOID WidevineProcessImpl::onDeferredComplete(const std::string& session_id, Cdm::Status result)
{
    WVLOGD("Enter function %s\n", __FUNCTION__);
}

HI_VOID WidevineProcessImpl::onDirectIndividualizationRequest(const std::string& session_id, const std::string& request)
{
    WVLOGD("Enter function %s\n", __FUNCTION__);
    m_strMsg = request;
}

void WidevineProcessImpl::CreateAdditionalCdm(bool privacy_mode, scoped_ptr<Cdm>* cdm)
{
    cdm->reset(Cdm::create(this, NULL, privacy_mode));
    ASSERT_NE((Cdm*)0, cdm->get());
}

void WidevineProcessImpl::RecreateCdm(bool privacy_mode)
{
    CreateAdditionalCdm(privacy_mode, &cdm_);
}

HI_S32 WidevineProcessImpl::Fetch(const std::string& url,
                                  const std::string& message,
                                  std::string* response,
                                  int* status_code)
{
    UrlRequest url_request(url);
    EXPECT_TRUE(url_request.is_connected());

    if (!url_request.is_connected())
    {
        WVLOGE("http connect fail!\n");
        return HI_FAILURE;
    }

    url_request.PostRequest(message);
    std::string http_response;
    url_request.GetResponse(&http_response);

    // Some license servers return 400 for invalid message, some
    // return 500; treat anything other than 200 as an invalid message.
    int http_status_code = url_request.GetStatusCode(http_response);

    if (status_code)
    {
        *status_code = http_status_code;
    }

    if (response)
    {
        if (http_status_code == kHttpOk)
        {
            // Parse out HTTP and server headers and return the body only.
            std::string reply_body;
            LicenseRequest lic_request;
            lic_request.GetDrmMessage(http_response, reply_body);
            *response = reply_body;
            WVLOGD("http returned ok!\n");
        }
        else
        {
            *response = http_response;
            WVLOGE("http returned fail, return code = %d!\n", *status_code);
            return HI_FAILURE;
        }

        //WVLOGD("Reply body: %s", b2a_hex(*response).c_str());
    }

    return HI_SUCCESS;
}

HI_S32 WidevineProcessImpl::FetchCertificate(const std::string& url, std::string* response)
{
    int status_code;
    HI_U32 ret = Fetch(url, "", response, &status_code);
    EXPECT_EQ(ret, HI_SUCCESS);
    EXPECT_EQ(kHttpOk, status_code);
}

HI_U32 WidevineProcessImpl::FetchLicense(const std::string& license_server,
        const std::string& message,
        std::string* response)
{
    int status_code;
#ifdef NO_NETWORK
    *response = kResponse_test;
#else
    HI_S32 ret = Fetch(license_server, message, response, &status_code);
    EXPECT_EQ(ret, HI_SUCCESS);
    EXPECT_EQ(kHttpOk, status_code);
#endif
    return HI_TRUE;
}

std::string WidevineProcessImpl::GetRequestResponse(const std::string& message)
{
    std::string reply;
    const std::string uri = url_test;

    HI_U32 ret = FetchLicense(uri, message, &reply);

    if (HI_FALSE == ret)
    {
        return "";
    }
    else
    {
        return reply;
    }
}

std::string WidevineProcessImpl::GetProvisionResponse(const std::string& message)
{
    std::string reply;
    std::string uri = url_provision;
    uri += "&signedRequest=" + message;

    HI_U32 ret = FetchCertificate(uri, &reply);

    if (HI_FALSE == ret)
    {
        return "";
    }
    else
    {
        return reply;
    }
}

HI_S32 WidevineProcessImpl::StartWidevineProcess(IN string key_id, IN string url, OUT HI_U8* content_key, OUT HI_U32& content_key_length)
{
#ifdef SET_ENCPRYT_KEYBOX
    // If keybox after provision isn't stored in secure storage, We need push encrypted
    // keybox to widevine TA.

    // TODO: Customer need to realize get cert and privkey by themselves.
    KEYBOX_FILE_S keybox_file;

    snprintf(keybox_file.szstring, 256, "%s/%s", "/data/widevine", "keybox_enc.bin_stb_root_key_enc");

    WV_PROMPT("Read %s\n", keybox_file.szstring);
    HI_S32 ret = Widevine_ReadDevCert(&keybox_file);
    if (ret < 0)
    {
       return HI_FAILURE;
    }

    WVLOGD("HI_Widevine_SetEncKeybox, keybox length:%d\n", keybox_file.s32length);
    ret = Hi_Widevine_SetEncKeybox((HI_CHAR*)keybox_file.pu8Addr, keybox_file.s32length);

    free(keybox_file.pu8Addr);
#endif

    // Start Widevine mutual authentication
    widevine_host = new TestHost();
    Cdm::ClientInfo client_info;
    // Set client info that denotes this as the test suite:
    client_info.product_name = "widevine tvp sample";
    client_info.company_name = "www";
    client_info.model_name = "www";
    client_info.device_name = "hisilicon";
    client_info.build_info = __DATE__;

    Cdm::Status status = Cdm::initialize(
                             Cdm::kOpaqueHandle, client_info, widevine_host, widevine_host, widevine_host, static_cast<Cdm::LogLevel>(3));
    EXPECT_EQ(Cdm::kSuccess, status);
    widevine_host->remove("cert.bin");

    RecreateCdm(true /* privacy_mode */);

    // Set the default server certificate.
    status = cdm_->setServerCertificate(kDefaultServerCertificate);
    EXPECT_EQ(Cdm::kSuccess, status);

    // Creating a session should succeed.
    std::string session_id;
    status = cdm_->createSession(Cdm::kTemporary, &session_id);
    EXPECT_EQ(Cdm::kSuccess, status);

    // Should get an individualization request when we generate request.
    status = cdm_->generateRequest(session_id, Cdm::kCenc, kCencInitData_test);
    EXPECT_EQ(Cdm::kSuccess, status);

    //Complete the provision request
    std::string replyCert = GetProvisionResponse(m_strMsg);
    status = cdm_->update(session_id, replyCert);
    EXPECT_EQ(Cdm::kSuccess, status);

    // Complete the licese request.
    std::string reply = GetRequestResponse(m_strMsg);
    ASSERT_TRUE(reply.empty());
    status = cdm_->update(session_id, reply);
    EXPECT_EQ(Cdm::kSuccess, status);

    return HI_SUCCESS;
}

HI_S32 WidevineProcessImpl::DecryptData(IN STRU_FRAME_PARAM* param, IN const std::string& keyid, OUT void* outputBuffer)
{
    CHK_ARG(param != NULL);
    CHK_ARG(param->frame_buffer != NULL);
    CHK_ARG(outputBuffer != NULL);
    CHK_ARG(keyid.length() != 0);

    Cdm::EncryptionScheme mode = Cdm::kAesCtr;
    Cdm::Pattern pattern;
    // Convert parameters to the form the CDM wishes to consume them in.
    const HI_U8* keyId = (HI_U8*)keyid.data();
    HI_U8 iv[KEY_IV_SIZE] = {0};
    memcpy(iv, param->iv, KEY_IV_SIZE);
    const HI_U8* const source = param->frame_buffer;
    HI_U8* const dest = (HI_U8*)(outputBuffer);

    // Calculate the output buffer size and determine if any subsamples are
    // encrypted.
    HI_U32 destSize = 0;
    bool haveEncryptedSubsamples = false;

    for (HI_U32 i = 0; i < param->numSubsamples; i++)
    {
        SubSample subSample;
        subSample.mNumBytesOfClearData = param->subsampleMaps[i * 2];
        subSample.mNumBytesOfEncryptedData = param->subsampleMaps[i * 2 + 1];
        destSize += subSample.mNumBytesOfClearData;
        destSize += subSample.mNumBytesOfEncryptedData;

        if (subSample.mNumBytesOfEncryptedData > 0)
        {
            haveEncryptedSubsamples = true;
        }
    }

    // Iterate through subsamples, sending them to the CDM serially.
    HI_U32 offset = 0;
    HI_U32 blockOffset = 0;
    const HI_U32 patternLengthInBytes =
        (/*pattern.mEncryptBlocks*/0 + 0/*pattern.mSkipBlocks*/) * kAESBlockSize;
    HI_U32 patternOffsetInBytes = 0;
    Cdm::InputBuffer input;
    Cdm::OutputBuffer output;
    input.encryption_scheme = Cdm::kClear;
    input.iv = const_cast<const HI_U8*>(iv);
    input.iv_length = KEY_IV_SIZE;
    input.key_id = keyId;
    input.key_id_length = KEY_ID_SIZE;
    input.pattern.encrypted_blocks = 0;
    input.pattern.clear_blocks = 0;
    input.is_video = param->is_secure;
    output.is_secure = param->is_secure;
    output.data = dest;
    output.data_length = destSize;

    for (HI_U32 i = 0; i < param->numSubsamples; ++i)
    {
        SubSample subSample;
        subSample.mNumBytesOfClearData = param->subsampleMaps[i * 2];
        subSample.mNumBytesOfEncryptedData = param->subsampleMaps[i * 2 + 1];

        // Calculate any flags that apply to this subsample's parts.
        HI_U32 clearFlags = 0;
        HI_U32 encryptedFlags = 0;

        // If this is the first subsample¡­
        if (i == 0)
        {
            // ¡­add OEMCrypto_FirstSubsample to the first part that is present.
            if (subSample.mNumBytesOfClearData != 0)
            {
                clearFlags = clearFlags | OEMCrypto_FirstSubsample;
            }
            else
            {
                encryptedFlags = encryptedFlags | OEMCrypto_FirstSubsample;
            }
        }

        // If this is the last subsample¡­
        if (i == param->numSubsamples - 1)
        {
            // ¡­add OEMCrypto_LastSubsample to the last part that is present
            if (subSample.mNumBytesOfEncryptedData != 0)
            {
                encryptedFlags = encryptedFlags | OEMCrypto_LastSubsample;
            }
            else
            {
                clearFlags = clearFlags | OEMCrypto_LastSubsample;
            }
        }

        // "Decrypt" any unencrypted data.  Per the ISO-CENC standard, clear data
        // comes before encrypted data.
        if (subSample.mNumBytesOfClearData != 0)
        {
            input.encryption_scheme = Cdm::kClear;
            input.data = source + offset;
            input.data_length = subSample.mNumBytesOfClearData;
            input.block_offset = 0;

            if (0 == i)
            {
                input.first_subsample = true;
            }
            else if (i == param->numSubsamples - 1)
            {
                input.last_subsample = true;
            }

            output.data_offset = offset;

            Cdm::Status res = cdm_->decrypt(input, output);

            if (Cdm::kSuccess != res)
            {
                WVLOGE("Decrypt error result in session during unencrypted block: %d",
                       res);
                return res;
            }

            offset += subSample.mNumBytesOfClearData;
        }

        // Decrypt any encrypted data.  Per the ISO-CENC standard, encrypted data
        // comes after clear data.
        if (subSample.mNumBytesOfEncryptedData != 0)
        {
            HI_U32 patternOffsetInBlocks = patternOffsetInBytes / kAESBlockSize;

            input.encryption_scheme = Cdm::kAesCtr;
            input.data = source + offset;
            input.data_length = subSample.mNumBytesOfEncryptedData;
            input.block_offset = blockOffset;

            if (0 == i)
            {
                input.first_subsample = true;
            }
            else if (i == param->numSubsamples - 1)
            {
                input.last_subsample = true;
            }

            output.data_offset = offset;

            Cdm::Status res = cdm_->decrypt(input, output);

            if (Cdm::kSuccess != res)
            {
                WVLOGE("Decrypt error result in session during unencrypted block: %d",
                       res);
                return res;
            }

            offset += subSample.mNumBytesOfEncryptedData;

            // Update the block offset, pattern offset, and IV as needed by the
            // various crypto modes. Possible combinations are cenc (AES-CTR), cens
            // (AES-CTR w/ Patterns), cbc1 (AES-CBC), and cbcs (AES-CBC w/ Patterns).
            if (mode == Cdm::kAesCtr)
            {
                // Update the IV depending on how many encrypted blocks we passed.
                uint64_t increment = 0;

                if (patternLengthInBytes == 0)
                {
                    // If there's no pattern, all the blocks are encrypted. We have to add
                    // in blockOffset to account for any incomplete crypto blocks from the
                    // preceding subsample.
                    increment = (blockOffset + subSample.mNumBytesOfEncryptedData) /
                                kAESBlockSize;
                }
                else
                {
                    res = countEncryptedBlocksInPatternedRange(
                              subSample.mNumBytesOfEncryptedData, blockOffset, pattern,
                              patternOffsetInBlocks, &increment);

                    if (Cdm::kSuccess != res)
                    {
                        // Swallow the specifics of the error to obscure decrypt internals.
                        WVLOGE("obscure decrypt internals error!\n");
                        return Cdm::kDecryptError;
                    }
                }

                incrementIV(increment, iv);

                // Update the block offset
                blockOffset = (blockOffset + subSample.mNumBytesOfEncryptedData) %
                              kAESBlockSize;

                if (patternLengthInBytes > 0)
                {
                    patternOffsetInBytes =
                        (patternOffsetInBytes + subSample.mNumBytesOfEncryptedData) %
                        patternLengthInBytes;
                }
            }
            else if (mode == Cdm::kAesCbc && patternLengthInBytes == 0)
            {
                // If there is no pattern, assume cbc1 mode and update the IV.

                // Stash the last crypto block in the IV.
                const HI_U8* bufferEnd = source + offset +
                                         subSample.mNumBytesOfEncryptedData;
                memcpy(iv, bufferEnd - kAESBlockSize, kAESBlockSize);
                //iv.assign(bufferEnd - kAESBlockSize, bufferEnd);
            }

            // There is no branch for cbcs mode because the IV and pattern offest
            // reset at the start of each subsample, so they do not need to be
            // updated.
        }
    }
    WVLOGD("Decrypt return offset:%d\n", offset);
    return offset;
}

Cdm::Status WidevineProcessImpl::countEncryptedBlocksInPatternedRange(
    HI_U32 range, HI_U32 startingOffset, const Cdm::Pattern& pattern,
    HI_U32 startingPatternOffset, HI_U64* result)
{
    uint64_t blocksPassed = 0;
    HI_U32 bytesRemaining = range;
    HI_U32 patternOffset = startingPatternOffset;
    HI_U32 patternLength = pattern.encrypted_blocks + pattern.clear_blocks;

    if (result == NULL || startingOffset >= kAESBlockSize ||
        startingPatternOffset >= patternLength)
    {
        return Cdm::kUnexpectedError;
    }

    // We may already be partway into a block, so reduce the number of bytes
    // that must be passed to complete a block if so.
    HI_U32 bytesNeededToCompleteABlock = kAESBlockSize - startingOffset;

    while (bytesRemaining >= bytesNeededToCompleteABlock)
    {
        bytesRemaining -= bytesNeededToCompleteABlock;

        if (patternOffset < pattern.encrypted_blocks)
        {
            ++blocksPassed;
        }

        patternOffset = (patternOffset + 1) % patternLength;

        // After the first block, we only concern ourselves with complete blocks.
        bytesNeededToCompleteABlock = kAESBlockSize;
    }

    *result = blocksPassed;
    return Cdm::kSuccess;
}

void WidevineProcessImpl::incrementIV(HI_U64 increaseBy, HI_U8* ivPtr)
{
    //std::vector<uint8_t>& iv = *ivPtr;
    HI_U64* counterBuffer = reinterpret_cast<HI_U64*>(&ivPtr[8]);
    (*counterBuffer) = htonq(ntohq(*counterBuffer) + increaseBy);
}

TvpSampleWidevineProcess::TvpSampleWidevineProcess()
{
    mProxy = new WidevineProcessImpl;

    if (!mProxy)
    {
        WVLOGE("New WidevineProcessImpl error!\n");
    }
}

TvpSampleWidevineProcess::~TvpSampleWidevineProcess()
{
    if (mProxy)
    {
        delete mProxy;
        mProxy = NULL;
    }
}

HI_S32 TvpSampleWidevineProcess::StartWidevineProcess(IN string key_id, IN string url, OUT HI_U8* content_key, OUT HI_U32& content_key_length)
{
    if (!mProxy)
    {
        WVLOGE("WidevineProcess proxy empty!\n");
        return -1;
    }

    return mProxy->StartWidevineProcess(key_id, url, content_key, content_key_length);
}

HI_S32 TvpSampleWidevineProcess::DecryptData(STRU_FRAME_PARAM* param, const std::string& keyid, void* outputBuffer)
{
    if (!mProxy)
    {
        WVLOGE("WidevineProcess proxy empty!\n");
        return -1;
    }

    return mProxy->DecryptData(param, keyid, outputBuffer);
}
