#include "WVLog.h"
#include "hi_type.h"
#include <utils/String8.h>
#include <utils/Vector.h>
#include "drm_engine.h"
#include "DrmDefines.h"
#include "hi_playready.h"
#include "hi_playreadyhttp.h"
#include <stdlib.h>
#include <netdb.h>

using namespace android;
using namespace drmengine;

enum PLAYREADY_PROTOCAL_HEAD
{
    PROTOCAL_HTTP_HEAD = 0,
    PROTOCAL_HTTPS_HEAD,
    PROTOCAL_OTHER_HEAD
};

#define HTTP_HEAD  "http://"
#define HTTPS_HEAD "https://"
#define PLAYREADY_DEFAULT_LICENSE_URL "http://playready.directtaps.net/pr/svc/rightsmanager.asmx?"

#define CHECK_DRMENGINE(drmengine) { \
    if (NULL == drmengine) \
    { \
        LOGE_DRM("Check drmengine error\n"); \
        return HI_FAILURE; \
    } \
}

DrmEngine* g_pDrmEngine = NULL;

HI_S32 HI_DrmEngine_Create(HI_VOID **ppHandle, const HI_U8* uuid, const HI_CHAR* mimetype, HI_PLUGIN_MODE pluginmode)
{
    LOGI_DRM("Enter HI_DrmEngine_Create\n");
    if (NULL == ppHandle || NULL == uuid || NULL == mimetype)
    {
        LOGE_DRM("%s check params error\n", __FUNCTION__);
        return HI_FAILURE;
    }
    g_pDrmEngine = new DrmEngine(uuid, mimetype, pluginmode);
    CHECK_DRMENGINE(g_pDrmEngine);

    return HI_SUCCESS;
}

HI_VOID HI_DrmEngine_Destroy(HI_VOID *pHandle)
{
    LOGI_DRM("Enter HI_DrmEngine_Destroy\n");

    if(NULL != g_pDrmEngine)
    {
        delete g_pDrmEngine;
        g_pDrmEngine = NULL;
    }

    return;
}

HI_BOOL HI_DrmEngine_IsCryptoSchemeSupported(HI_VOID *pHandle, const HI_U8* uuid, const HI_CHAR* mimetype)
{
    if (NULL == uuid || NULL == mimetype || NULL == g_pDrmEngine)
    {
        LOGE_DRM("%s check params error\n", __FUNCTION__);
        return HI_FALSE;
    }
    return g_pDrmEngine->drmIsCryptoSchemeSupported(uuid, mimetype);
}

HI_S32 HI_DrmEngine_OpenSession(HI_VOID *pHandle)
{
    CHECK_DRMENGINE(g_pDrmEngine);
    return g_pDrmEngine->drmOpenSession();
}

HI_S32 HI_DrmEngine_CloseSession(HI_VOID *pHandle)
{
    CHECK_DRMENGINE(g_pDrmEngine);
    return g_pDrmEngine->drmCloseSession();
}

HI_S32 HI_DrmEngine_GetKeyRequest(HI_VOID *pHandle,
                                                                                  const HI_U8* initData,
                                                                                  HI_U32 initDataLen,
                                                                                  const HI_U8* mimeType,
                                                                                  HI_DRM_KEY_TYPE keyType,
                                                                                  HI_DRM_CTYPE_KEY_REQUEST* pCTypeKeyRequest)
{
    std::string strInitData;
    std::map < std::string, std::string > optionalParameters;
    HI_DRM_KEY_REQUEST keyRequest;
    HI_S32 ret = HI_FAILURE;

    if (NULL == initData || NULL == pCTypeKeyRequest)
    {
        LOGE_DRM("%s check params error\n", __FUNCTION__);
        return HI_FAILURE;
    }

    strInitData.assign((const HI_CHAR*)initData, initDataLen);
    CHECK_DRMENGINE(g_pDrmEngine);
    ret = g_pDrmEngine->drmGetKeyRequest(strInitData, mimeType, keyType,  optionalParameters, &keyRequest);
    if (HI_SUCCESS != ret)
    {
        LOGE_DRM("drmGetKeyRequest fail\n");
        return HI_FAILURE;
    }

    LOGI_DRM("keyRequest.defaultUrl is %s\n", keyRequest.defaultUrl.string());
    LOGI_DRM("keyRequest.defaultUrl length is %d\n", keyRequest.defaultUrl.length());
    if (keyRequest.defaultUrl.length() >= MAX_DEFAULT_URL_SIZE)
    {
        LOGE_DRM("keyRequest.defaultUrl length is %d\n", keyRequest.defaultUrl.length());
        return HI_FAILURE;
    }

    memset(pCTypeKeyRequest->defaultUrl, 0, sizeof(pCTypeKeyRequest->defaultUrl));
    if (0 == memcmp(keyRequest.defaultUrl.string(), PLAYREADY_DEFAULT_LICENSE_URL, strlen(PLAYREADY_DEFAULT_LICENSE_URL)))
    {
        LOGI_DRM("playready license url = %s\n", PLAYREADY_DEFAULT_LICENSE_URL);
        memcpy(pCTypeKeyRequest->defaultUrl, PLAYREADY_DEFAULT_LICENSE_URL, strlen(PLAYREADY_DEFAULT_LICENSE_URL));
    }
    else
    {
        memcpy(pCTypeKeyRequest->defaultUrl, keyRequest.defaultUrl.string(), keyRequest.defaultUrl.length());
    }

    LOGI_DRM("pCTypeKeyRequest->defaultUrl = %s\n", pCTypeKeyRequest->defaultUrl);
    pCTypeKeyRequest->eKeyRequestType = keyRequest.eKeyRequestType;

    if (keyRequest.requestData.size() >= MAX_REQUEST_DATA_SIZE)
    {
        LOGE_DRM("keyRequest.requestData length is %d\n", keyRequest.requestData.size());
        return HI_FAILURE;
    }
    memcpy(pCTypeKeyRequest->requestData, keyRequest.requestData.array(), keyRequest.requestData.size());
    pCTypeKeyRequest->requestDataLen = keyRequest.requestData.size();
    LOGI_DRM("keyRequest.requestData.size() = %d\n",  pCTypeKeyRequest->requestDataLen);
    LOGI_DRM("keyRequest.requestData.requestData = %s\n",  pCTypeKeyRequest->requestData);

    return HI_SUCCESS;
}

HI_S32 HI_DrmEngine_ProvideKeyResponse(HI_VOID *pHandle, HI_U8* response, HI_U32 responseLen, HI_U8* keySetId)
{
    std::string strResponse;
    std::string strKeySetId;
    HI_S32 ret = HI_FAILURE;

    if (NULL == response || NULL == keySetId)
    {
        LOGE_DRM("%s check params error\n", __FUNCTION__);
        return HI_FAILURE;
    }

    strResponse.assign((const HI_CHAR*)response, responseLen);
    CHECK_DRMENGINE(g_pDrmEngine);
    ret = g_pDrmEngine->drmProvideKeyResponse(strResponse, strKeySetId);
    if (HI_SUCCESS != ret)
    {
        LOGE_DRM("drmProvideKeyResponse fail\n");
        return HI_FAILURE;
    }
    memcpy(keySetId, strKeySetId.c_str(), KEY_ID_LENGTH);

    return HI_SUCCESS;
}

static void ParseUrl(HI_PLAYREADY_URL *drm_url, HI_U8 *url)
{
    HI_U8 *pcolon   = HI_NULL;
    HI_U8 *findhost = HI_NULL;
    HI_U8 *s = HI_NULL;
    HI_U8 *find = HI_NULL;

    if (NULL == drm_url || NULL == url)
    {
        LOGE_DRM("%s check params error\n", __FUNCTION__);
        return;
    }
    memset(drm_url, 0, sizeof(HI_PLAYREADY_URL));
    drm_url->url = url;
    s = drm_url->url;
    if (drm_url->url == HI_NULL)
    {
        LOGE_DRM("Url is NULL.\n");
        return;
    }

    //url should be "HTTP://WWW.xxx.com:80/asdd.jsp"
    if ((findhost = (HI_U8*)strstr((HI_CHAR *)s, (HI_CHAR *)"//")) != HI_NULL)
    {
        if ((findhost > s) && (*(findhost - 1) == ':'))
        {
            strncpy((HI_CHAR *)drm_url->protocol, (HI_CHAR *)s, (HI_U32)(findhost - s - 1)); //should be "HTTP"
        }

        findhost += 2; //jump "//"
        if ((find = (HI_U8*)strchr((HI_CHAR *)findhost, (HI_S32)'/')) != HI_NULL)
        {
            strncpy((HI_CHAR *)drm_url->host, (HI_CHAR *)findhost, (HI_U32)(find - findhost));
            strncpy((HI_CHAR *)drm_url->query, (HI_CHAR *)find, strlen((HI_CHAR *)find) + 1);
        }
        else
        {
            strncpy((HI_CHAR *)drm_url->host, (HI_CHAR *)findhost, strlen((HI_CHAR *)findhost) + 1);
            memset(drm_url->query,0,sizeof(drm_url->query));
        }

        pcolon = (HI_U8 *)strchr((HI_CHAR *)drm_url->host, (HI_S32)':');
        if (pcolon != HI_NULL)
        {
            drm_url->port = (HI_U32)atoi((HI_CHAR *)(pcolon + 1));
            pcolon = '\0';
        }
        else
        {
            struct servent * svt = HI_NULL;

            svt = getservbyname((HI_CHAR *)drm_url->protocol, "tcp");
            if (svt != (struct servent*)HI_NULL)
            {
                drm_url->port = (HI_U32)ntohs((HI_U16)svt->s_port);
            }
            else
            {
                drm_url->port = 0;
            }
        }
    }
    else
    {
        drm_url->port  = 80;
        strncpy((HI_CHAR *)drm_url->query, (HI_CHAR *)s, strlen((HI_CHAR *)s) + 1);
    }

    if (drm_url->port == 0)
    {
        drm_url->port = 80;
    }

    LOGI_DRM("protocol:%s, host:%s, port:%d, query:%s\n", drm_url->protocol, drm_url->host, drm_url->port, drm_url->query);
    return;
}

static HI_S32 GetProtocalHead(HI_U8* url)
{
    HI_U8* urlHead = NULL;
    if (NULL == url)
    {
        LOGE_DRM("%s check params error\n", __FUNCTION__);
        return PROTOCAL_OTHER_HEAD;
    }

    urlHead = (HI_U8 *)strstr((HI_CHAR *)url, (HI_CHAR *)HTTP_HEAD);

    if (NULL != urlHead)
    {
        return PROTOCAL_HTTP_HEAD;
    }

    urlHead = (HI_U8 *)strstr((HI_CHAR *)url, (HI_CHAR *)HTTPS_HEAD);
    if (NULL != urlHead)
    {
        return PROTOCAL_HTTPS_HEAD;
    }

    return PROTOCAL_OTHER_HEAD;
}

static HI_S32 HttpClientPlayInit(CURL **curl, HI_PLAYREADY_CHALLENGE_S *pChallenge, HI_PLAYREADY_URL *pstUrl)
{
    // use curl to process http&https request
    CURLcode return_code;
    HI_U8 u8Url[255];
    HI_U8 protocalHead;

    if ( (HI_NULL == curl)  || (HI_NULL == pChallenge) || (HI_NULL == pstUrl))
    {
        LOGE_DRM("invalid param, null pointer in httpclient init funcTion!\n");
        return HI_FAILURE;
    }

    // init libcurl
    return_code = curl_global_init(CURL_GLOBAL_ALL);
    if (CURLE_OK != return_code)
    {
        LOGE_DRM("init libcurl failed!\n");
        return HI_FAILURE;
    }

    // get easy handle
    *curl = curl_easy_init();
    LOGI_DRM("After curl init,curl addr:0x%x\n", *curl);
    if (HI_NULL == *curl)
    {
        LOGE_DRM("get a easy handle failed!\n");
        return HI_FAILURE;
    }

    memset(pstUrl, 0x00, sizeof(HI_PLAYREADY_URL));
    memcpy(u8Url, pChallenge->URL.pszString, pChallenge->URL.length);
    u8Url[pChallenge->URL.length] = '\0';
    LOGI_DRM("pChallenge->URL.length = %d\n", pChallenge->URL.length);
    LOGI_DRM("HTTP Post to : %s\n", u8Url);

    //check url is http or https
    protocalHead = GetProtocalHead(u8Url);

    // https ssl process
    if (PROTOCAL_HTTPS_HEAD == protocalHead)
    {
        LOGI_DRM("is https url\n");
        return_code = curl_easy_setopt(*curl, CURLOPT_SSL_VERIFYPEER, 0);
        return_code = curl_easy_setopt(*curl, CURLOPT_SSL_VERIFYHOST, 0);
    }
    // set url
    return_code = curl_easy_setopt(*curl, CURLOPT_URL, u8Url);

    ParseUrl(pstUrl, u8Url); //Get host, port of URL, query

    LOGI_DRM(" Mode 0 http client ps8ServerIp %s\n", pstUrl->host);
    LOGI_DRM("Mode 0 http server port : %d\n",pstUrl->port);

    // set CURLOPT_POST 1 indicates this time is POST operation
    return_code = curl_easy_setopt(*curl, CURLOPT_POST, 1);

    return HI_SUCCESS;

}

static HI_S32 HttpClientDeInit(CURL *curl)
{
    if (NULL == curl )
    {
        LOGE_DRM("invalid curl in http client deinit!\n");
        return HI_FAILURE;
    }

    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return HI_SUCCESS;
}

HI_S32 GetResponseFromServerPR(HI_U8* request, HI_U32 requestLen, HI_CHAR* url, HI_U8* outResponse, HI_U32* responseLen)
{
    CURL *curl;
    HI_PLAYREADY_URL stUrl;
    HI_PLAYREADY_CHALLENGE_S Challenge;
    HI_S32 ret;
    HI_PLAYREADY_ASCII_STRING Response;
    if (NULL == request || NULL == url || NULL == outResponse || 0 == requestLen)
    {
        LOGE_DRM("%s check params error\n", __FUNCTION__);
        return HI_FAILURE;
    }
    memset(&Challenge,0,sizeof(HI_PLAYREADY_CHALLENGE_S));
    Challenge.ChallengeContent.length = requestLen;
    Challenge.ChallengeContent.pszString = (HI_U8*)malloc(Challenge.ChallengeContent.length);
    memcpy(Challenge.ChallengeContent.pszString, request, Challenge.ChallengeContent.length);

    Challenge.URL.length = strlen(url);
    Challenge.URL.pszString = (HI_U8*)malloc(Challenge.URL.length);
    memcpy(Challenge.URL.pszString, url, Challenge.URL.length);

    ret = HttpClientPlayInit(&curl, &Challenge, &stUrl);
    if ( HI_SUCCESS != ret)
    {
        LOGE_DRM("HTTP Client init 1 failed.\n");
        return HI_FAILURE;
    }

    ret = HI_PLAYREADY_HTTP_FetchLicenseEx(curl, &stUrl, &Challenge, &Response, IS_PLAYREADY_ENCRYPT);
    if (ret != HI_SUCCESS)
    {
        LOGE_DRM("HI_PLAYREADY_HTTP_FetchLicenseEx Return:0x%x\n",
                ret);
        LOGE_DRM("~~~~~~~~~~~~HTTP and DRM Server Return Err : %s~~~~~~~~~~~~\n",
            HI_PLAYREADY_HTTP_GetReturnCodeString((HI_PLAYREADY_HTTP_STATE_E)ret));
        return ret;
    }

    LOGI_DRM("responseLen = %d\n", Response.length);
    if (MAX_RESPONSE_DATA_SIZE <= Response.length)
    {
        LOGE_DRM("responseLen %d is out of range", Response.length);
        return HI_FAILURE;
    }

    memcpy(outResponse, Response.pszString, Response.length);
    *responseLen = Response.length;
    ret = HttpClientDeInit(curl);
    if ( HI_SUCCESS != ret)
    {
        LOGE_DRM("@@@@@@@@@@@@http client deinit  1 failed!@@@@@@@@@@@@@@\n");
    }
    free(Challenge.ChallengeContent.pszString);
    free(Challenge.URL.pszString);
    HI_PLAYREADY_HTTP_Release_Response(&Response);

    return ret;
}

HI_VOID PRINT_Array(HI_U8 *data, HI_S32 len, const HI_CHAR *printinfo)
{
    HI_S32 i = 0;
    if (NULL == data || NULL == printinfo || 0 == len)
    {
        LOGE_DRM("%s check params error\n", __FUNCTION__);
        return;
    }
 
    printf("********** the %s is: \n",printinfo);
    for(i = 0; i < len; i++)
    {
        printf("0x%x ,", data[i]);
        if (i % 8 == 7)
        {
            printf("\n");
        }
    }
    printf("\n");
}

HI_S32 HI_DrmEngine_PRFetchLicense(HI_VOID *pHandle, HI_DRM_CTYPE_KEY_REQUEST stKeyRequest, HI_U8* keyID)
{
    HI_S32 status = HI_FAILURE;
    HI_U8 response[MAX_RESPONSE_DATA_SIZE] = {0};
    HI_U32 responseLen = 0;

    if (NULL == keyID)
    {
        LOGE_DRM("%s check params error\n", __FUNCTION__);
        return HI_FAILURE;
    }
    status = GetResponseFromServerPR(stKeyRequest.requestData, stKeyRequest.requestDataLen, stKeyRequest.defaultUrl, response, &responseLen);
    printf("responseLen: %d\n", responseLen);
    printf("remote response: %s\n", response);
    if (HI_SUCCESS != status)
    {
        printf("GetResponseFromServerPR fail!\n");
        return HI_FAILURE;
    }

    status = HI_DrmEngine_ProvideKeyResponse(pHandle, response, responseLen, keyID);
    if (HI_SUCCESS != status)
    {
        printf("[error]%s,%d:HI_DrmEngine_ProvideKeyResponse fail \n",__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }
    PRINT_Array(keyID, KEY_ID_LENGTH, "key id");

    return HI_SUCCESS;
}

HI_S32 HI_DrmEngine_Decrypt(HI_VOID *pHandle, HI_BOOL secure, const HI_U8* key, const HI_U8* iv,
                                  const HI_DRM_PATTERN pattern, HI_CRYPTO_MODE mode, HI_U8* pSrc,
                                  const HI_DRM_SUBSAMPLES* subSamples, HI_S32 numSubSamples,
                                  HI_VOID* pDst)
{
    if (NULL == key ||NULL == iv || NULL == pSrc || NULL == pDst)
    {
        LOGE_DRM("%s check params error\n", __FUNCTION__);
        return HI_FAILURE;
    }
    CHECK_DRMENGINE(g_pDrmEngine);
    return  g_pDrmEngine->drmDecrypt(secure, key, iv, pattern,
                                                          mode, pSrc, subSamples,
                                                          numSubSamples, pDst);
}

HI_S32 HI_DrmEngine_GetPropertyString(HI_VOID *pHandle, const HI_U8* name, const HI_U8* value)
{
    std::string strName;
    std::string strValue;
    HI_S32 ret = HI_FAILURE;
    if (NULL == name || NULL == value)
    {
        LOGE_DRM("%s check params error\n", __FUNCTION__);
        return HI_FAILURE;
    }
    CHECK_DRMENGINE(g_pDrmEngine);
    strName.assign((const HI_CHAR*)name, strlen((const HI_CHAR*)name));
    ret = g_pDrmEngine->drmGetPropertyString(strName, strValue);
    if (HI_SUCCESS != ret)
    {
        LOGE_DRM("drmGetPropertyString fail\n");
        return HI_FAILURE;
    }
    memcpy((HI_VOID*)value, strValue.c_str(), strValue.length());

    return HI_SUCCESS;
}

HI_S32 HI_DrmEngine_SetPropertyString(HI_VOID *pHandle, const HI_U8* name, const HI_U8* value)
{
    std::string strName;
    std::string strValue;
    if (NULL == name || NULL == value)
    {
        LOGE_DRM("%s check params error\n", __FUNCTION__);
        return HI_FAILURE;
    }
    strName.assign((const HI_CHAR*)name, strlen((const HI_CHAR*)name));
    strName.assign((const HI_CHAR*)value, strlen((const HI_CHAR*)value));

    CHECK_DRMENGINE(g_pDrmEngine);
    return g_pDrmEngine->drmSetPropertyString(strName, strValue);
}

