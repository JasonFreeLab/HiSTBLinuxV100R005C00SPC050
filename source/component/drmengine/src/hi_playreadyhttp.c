/******************************************************************************

  Copyright (C), 2011-2021, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_playreadyhttp.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2011.08.25
  Description   :
  History       :

 *******************************************************************************/

#include <curl.h>
#include <netinet/in.h>
#include <arpa/inet.h>              /* inet_pton */
#include <netdb.h>                  /* gethostbyname */
#include <unistd.h>
#include <sys/socket.h>             /* socket/bind/etc. */
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>                 /* vierable params */

//#include "hi_playready.h"
#include "hi_playreadyhttp.h"

#define HI_INFO_PLAYREADY(fmt, args...) \
 do{ \
         printf("[info] %s(), %d: " fmt, __FUNCTION__,__LINE__, ## args); \
 }while(0);
 
#define HI_ERR_PLAYREADY(fmt, args...) \
 do{ \
         printf("[err] %s(), %d: " fmt, __FUNCTION__,__LINE__, ## args); \
 }while(0);
 
#define HTTP_MAX_HDR_LINE (0x400)     /* manipulation buffer defines */
#define HTTP_XMLRPC_BUFSIZE (1024 * 28)   /* xml RPC buffer size */
#define HTTP_OK_RESPONSE (200)       /* http 'OK' response code */

#define LEN_TWO 2

/* stringized/misc. defines
 */
#define HTTP_HEAD  "http://"
#define HTTPS_HEAD "https://"
#define HDR_VALUE_URLENCODED "application/x-www-form-urlencoded"         /* specifies urlencoded posting */

//#define DRM_POST_PREFIX         "nonsilent=%d&challenge="    /* drm specific post prefix, pre-challenge */
#define DRM_POST_PREFIX "challenge="    /* drm specific post prefix, pre-challenge */
#define WMDRM_LICRESPONSE_OPENED "<LICENSERESPONSE>"     /* open xml tag in license response */
#define WMDRM_LICRESPONSE_CLOSED "</LICENSERESPONSE>"    /* closed xml tag in license response */
#define PR_LICRESPONSE_OPENED "<?xml"     /* open xml tag in license response */
#define PR_LICRESPONSE_CLOSED "</soap:Envelope>"    /* closed xml tag in license response */

#define HDR_TAG_CONTENT_TYPE "Content-Type"          /* header tag for content-type */
#define HDR_TAG_CONTENT_LENGTH "Content-Length"        /* header tag for content-length */
#define HDR_TAG_HOST "Host"
#define HDR_TAG_SOAPACTION "SOAPAction"
#define HDR_VALUE_URLENCODED_PR "text/xml; charset=utf-8"         /* specifies urlencoded posting */

#define STATUSCODE_OPEN "<StatusCode>"
#define STATUSCODE_CLOSED "</StatusCode>"
#define CUSTOMERDATA_OPEN "<CustomData>"
#define CUSTOMERDATA_CLOSE "</CustomData>"

#define DEVCERT_REVOKED "0x8004c065"
#define INTERNAL_ERROR "0x8004c600"
#define INVALID_MESSAGE "0x8004c601"
#define DEVICE_LIMIT_REACHED "0x8004c602"
#define SPECIFIC_SERVICE "0x8004c604"
#define REQUIRE_DOMAIN "0x8004c605"
#define RENEW_DOMAINCERT "0x8004c606"
#define NOT_A_DOMAIN_MEMBER "0x8004c60a"
#define PROTOCOL_VERSION_MISMATCH "0x8004c60b"
#define UNKNOWN_ACCOUNTID "0x8004c60c"
#define PROTOCOL_REDIRECT "0x8004c60d"

#define REDIRECT_URL_OPEN "<RedirectUrl>"
#define REDIRECT_URL_CLOSED "</RedirectUrl>"

#define SOAPACTION "SOAPAction"
#define JOIN_DOMAIN "http://schemas.microsoft.com/DRM/2007/03/protocols/JoinDomain"
#define LEAVE_DOMAIN "http://schemas.microsoft.com/DRM/2007/03/protocols/LeaveDomain"

#define PROCESS_METER "http://schemas.microsoft.com/DRM/2007/03/protocols/ProcessMeteringData"
#define GET_METERCERT "http://schemas.microsoft.com/DRM/2007/03/protocols/GetMeteringCertificate"
#define ACK_LIC "http://schemas.microsoft.com/DRM/2007/03/protocols/AcknowledgeLicense"
#define ACQ_LIC "http://schemas.microsoft.com/DRM/2007/03/protocols/AcquireLicense"

static HI_U8  g_HttpRecvBuf[HTTP_XMLRPC_BUFSIZE];
static HI_U32 g_u32Content_length = 0;;
static HI_U8  url_host[256];
extern HI_U32 PLAYREADY_DebugOpen;
static HI_CHAR *g_ErrorCode_String[HI_PLAYREADY_HTTP_STATUS_MAX + 1] = {
"HTTP STATUS OK",
"Unsupported Protocol",
"Failed Init",
"URL using bad/illegal format or missing URL",
"Unknown error",
"Couldnt resolve proxy name",
"Couldn't resolve host name",
"Couldn't connect to server",
"FTP: weird server reply",
"FTP: access deny",
"Unknown error",
"FTP: unknown PASS reply",
"FTP: unknown USER reply",
"FTP: unknown PASV reply",
"FTP: unknown 227 response format",
"FTP: can't figure out the host in the PASV response",
"FTP: can't connect to server the response code is unknown",
"FTP: couldn't set binary mode",
"Transferred a partial file",
"FTP: couldn't retrieve (RETR failed) the specified file",
"FTP: the post-transfer acknowledge response was not OK",
"FTP: a quote command returned error",
"HTTP response code said error",
"Failed writing received data to disk/application",
"Unknown error",
"Upload failed (at start/before it took off)",
"Failed to open/read local data from file/application",
"Out of memory",
"A timeout was reached",
"FTP could not set ASCII mode (TYPE A)",
"FTP command PORT failed",
"FTP command REST failed",
"FTP command SIZE failed",
"A range was requested but the server did not deliver it",
"Internal problem setting up the POST",
"SSL connect error",
"Couldn't resume download",
"Couldn't read a file",
"LDAP: cannot bind",
"LDAP: search failed",
"A required shared library was not found",
"HTTP Resonse Failed Code",
"HTTP Read DRM Server Error",
"HTTP Server Connect Error",
"HTTP Post Method Error",
"DRM Device Limited",
"Devert Revoked",
"DRM Server Internal Error",
"DRM Invaild Message",
"DRM Service Specific",
"HTTP Require Domain",
"DRM Need Renew Domain",
"HTTP Server Internal Error",
"DRM Not A Memeber"
"HTTP Protocol Dismissed",
"DRM Unknowed Accountid",
"DRM Protocol Redirect",
"HI_PLAYREADY_HTTP_STATUS_MAX",
};

typedef struct
{
    PLAYREADY_HTTP_HEADER_S *headers;          //HTTP headers
    CURL                    *curl;             //curl handle
    HI_U32                   ResponseCode;     //HTTP header response code
    HI_U8                   *DataBuffer;
    HI_U32                   Datalength;
} PLAYREADY_HTTP_HANDLE;

enum
{
    PROTOCAL_HTTP_HEAD = 0,
    PROTOCAL_HTTPS_HEAD,
    PROTOCAL_OTHER_HEAD
} PLAYREADY_PROTOCAL_HEAD;

static HI_IS_WHAT_ENCRYPT g_HTTP_IsWhatEncryp;

static void playreadyParseUrl(HI_PLAYREADY_URL *drm_url, HI_U8 *url)
{
    HI_U8 *pcolon   = HI_NULL;
    HI_U8 *findhost = HI_NULL;
    HI_U8 *s = HI_NULL;
    HI_U8 *find = NULL;

    memset(drm_url, 0, sizeof(HI_PLAYREADY_URL));
    drm_url->url = url;
    s = drm_url->url;
    if (drm_url->url == NULL)
    {
        HI_ERR_PLAYREADY("Error: url is NULL\n");
        return;
    }

    //url should be "HTTP://WWW.xxx.com:80/asdd.jsp"
    if ((findhost = (HI_U8*)strstr((HI_CHAR *)s, (HI_CHAR *)"//")) != NULL)
    {
        if ((findhost > s) && (*(findhost - 1) == ':'))
        {
            strncpy((HI_CHAR *)drm_url->protocol, (HI_CHAR *)s, (HI_U32)(findhost - s - 1)); //should be "HTTP"
        }

        findhost += 2; //jump "//"
        if ((find = (HI_U8*)strchr((HI_CHAR *)findhost, (HI_S32)'/')) != NULL)
        {
            strncpy((HI_CHAR *)drm_url->host, (HI_CHAR *)findhost, (HI_U32)(find - findhost));
            //drm_url->query = find;
            strncpy((HI_CHAR *)drm_url->query, (HI_CHAR *)find, strlen((HI_CHAR *)find) + 1);
        }
        else
        {
            strcpy((HI_CHAR *)drm_url->host, (HI_CHAR *)findhost);
            //drm_url->query = NULL;
            memset(drm_url->query,0,sizeof(drm_url->query));
        }

        pcolon = (HI_U8 *)strchr((HI_CHAR *)drm_url->host, (HI_S32)':');
        if (pcolon != NULL)
        {
            drm_url->port = (HI_U32)atoi((HI_CHAR *)(pcolon + 1)); //transfer port to numeric
            pcolon = '\0';                  //remove :port form host
        }
        else
        {
            struct servent * svt = HI_NULL;

            //svt=getservbyname( "http ", "tcp");
            svt = getservbyname((HI_CHAR *)drm_url->protocol, "tcp");
            if (svt != (struct servent*)NULL)
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
        //drm_url->query = s;
        strncpy((HI_CHAR *)drm_url->query, (HI_CHAR *)s, strlen((HI_CHAR *)s) + 1);
    }

    if (drm_url->port == 0)
    {
        drm_url->port = 80;
    }

    strcpy((char *)url_host, (const char *)drm_url->host);

    //HI_INFO_PLAYREADY("$url_host:%s\n", url_host);
    HI_INFO_PLAYREADY("protocol:%s, host:%s, port:%d, query:%s\n", drm_url->protocol, drm_url->host, drm_url->port,
               drm_url->query);

    return;
}

static HI_S32 playreadyGetProtocalHead(HI_U8* url)
{
    HI_U8* urlHead;

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

static HI_S32 playreadyHttpClientInit(CURL **curl, HI_PLAYREADY_CHALLENGE_S *pChallenge, HI_PLAYREADY_URL *pstUrl)
{
    // use curl to process http&https request
    CURLcode return_code;
    HI_U8 u8Url[255];
    HI_U8 protocalHead;

    if ( (NULL == curl)  || (NULL == pChallenge) || (NULL == pstUrl))
    {
        HI_ERR_PLAYREADY("invalid param, null pointer in httpclient init funcTion!\n");
        return HI_FAILURE;
    }

    // init libcurl
    return_code = curl_global_init(CURL_GLOBAL_ALL);
    if (CURLE_OK != return_code)
    {
        HI_ERR_PLAYREADY("init libcurl failed!\n");
        return HI_FAILURE;
    }

    // get easy handle
    *curl = curl_easy_init();
    HI_INFO_PLAYREADY("curl addr after curl init:0x%x\n", *curl);
    if (NULL == *curl)
    {
        HI_ERR_PLAYREADY("get a easy handle failed!\n");
        return HI_FAILURE;
    }

    memset(pstUrl, 0x00, sizeof(HI_PLAYREADY_URL));
    memcpy(u8Url, pChallenge->URL.pszString, pChallenge->URL.length);
    u8Url[pChallenge->URL.length] = '\0';

    //check url is http or https
    protocalHead = playreadyGetProtocalHead(u8Url);

    // set url
    if (PROTOCAL_HTTPS_HEAD == protocalHead)
    {
        HI_INFO_PLAYREADY("is https url\n");
        return_code = curl_easy_setopt(*curl, CURLOPT_SSL_VERIFYPEER, 0);
        return_code = curl_easy_setopt(*curl, CURLOPT_SSL_VERIFYHOST, 0);
    }

    HI_INFO_PLAYREADY("curl set url:%s\n", u8Url);
    return_code = curl_easy_setopt(*curl, CURLOPT_URL, u8Url);

    playreadyParseUrl(pstUrl, u8Url); //Get host, port of URL, query

    HI_INFO_PLAYREADY("Debug Host:%s\n", (HI_CHAR *)pstUrl->host);

    // set CURLOPT_POST 1 indicates this time is POST operation
    return_code = curl_easy_setopt(*curl, CURLOPT_POST, 1);

    return HI_SUCCESS;

}

static HI_S32 playreadyHttpClientDeinit(CURL *curl)
{
    if (0 == curl)
    {
        HI_ERR_PLAYREADY("invalid curl pointer in http client deinit!\n");
        return HI_FAILURE;
    }

    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return HI_SUCCESS;
}

static HI_U32 playreadyHttpInitEx(struct curl_slist **headers,
                           HI_U8 *method,
                           HI_PLAYREADY_URL *pstUrl)
{

    HI_U8 *query = NULL;
    HI_U8 buf[HTTP_MAX_HDR_LINE];
    HI_U32 len = 0;

    if ((NULL == method) || (NULL == pstUrl))
    {
        HI_ERR_PLAYREADY("invalid param ,in http init ex function!\n");
        return HI_FAILURE;
    }

    query = pstUrl->query;
    if (!query || (! * query))
    {
        query[0] = '/';
        query[1] = '\0';
    }

    if ((g_HTTP_IsWhatEncryp == IS_PLAYREADY_ENCRYPT)
        || (g_HTTP_IsWhatEncryp == IS_DOMAIN_JOIN)
        || (g_HTTP_IsWhatEncryp == IS_DOMAIN_LEAVE)
        || (g_HTTP_IsWhatEncryp == IS_GET_METER_CERT)
        || (g_HTTP_IsWhatEncryp == IS_PROCESS_METERING)
        || (g_HTTP_IsWhatEncryp == IS_ACK_LIC))
    {
        len = snprintf((HI_CHAR *)buf, HTTP_MAX_HDR_LINE, "%s %s HTTP/1.1\r\n", method, query);
    }
    else if ((g_HTTP_IsWhatEncryp == IS_WMDRM_ENCRYPT) || (IS_SECURE_CLOCK == g_HTTP_IsWhatEncryp))
    {
        len = (HI_U32)snprintf((HI_CHAR *)buf, HTTP_MAX_HDR_LINE, "%s %s HTTP/1.0\r\n", (HI_CHAR*)method,
                               (HI_CHAR*)query);
    }
    else
    {
        return HI_FAILURE;
    }

    HI_INFO_PLAYREADY("curl add Header:%s\n", buf);
    *headers = curl_slist_append(*headers, (const HI_CHAR*)buf);
    HI_INFO_PLAYREADY("in playreadyHttpInitEx, headers address:0x%x\n", *headers);

    strcpy((char *)url_host, (const char *)pstUrl->host);
    HI_INFO_PLAYREADY("in playreadyHttpInitEx, url_host:%s\n", url_host);

    return (HI_U32)HI_PLAYREADY_HTTP_STATUS_OK;
}

static HI_VOID playreadyHttpCurlAppendHead(HI_CHAR* strHeadername,
                                  HI_CHAR* strHeadervalue,
                                  struct curl_slist **headers)
{
    HI_CHAR* strHeader;

    strHeader = (HI_CHAR*)OEM_malloc(strlen(strHeadername) + strlen(": ") + strlen(strHeadervalue) + 1);
    memset(strHeader,0,sizeof(strHeader));
    strHeader = strncat(strHeader, strHeadername, strlen(strHeadername));
    strHeader = strncat(strHeader, ": ", LEN_TWO);
    strHeader = strncat(strHeader, strHeadervalue, strlen(strHeadervalue));

    *headers = curl_slist_append(*headers, strHeader);

    OEM_free(strHeader);
}

size_t playreadyHttpWriteData(HI_VOID *buffer, size_t size, size_t nmemb, HI_VOID *userp)
{
    if (strlen((const HI_CHAR*)userp) + strlen((const HI_CHAR*)buffer) > HTTP_XMLRPC_BUFSIZE)
    {
        g_u32Content_length = 0;
        HI_ERR_PLAYREADY("Http receive buffer overflow!");
        return 0;
    }

    HI_INFO_PLAYREADY("curl write data:%s\n", (HI_U8*)buffer);
    strcat((HI_CHAR*)userp, (const HI_CHAR*)buffer);

    g_u32Content_length += size * nmemb;
    return size * nmemb;
}

/*********************************************************************
Funciton:HI_PLAYREADY_HTTP_FetchLicenseEx
Parameter:
    HI_S32 *ps32SocketFd  //[in] socket
    HI_PLAYREADY_URL *pstUrl    //[in] url
    HI_PLAYREADY_CHALLENGE_S *pChallenge, // [in] challenge content
    HI_PLAYREADY_ASCII_STRING *pResponse    // [out] drm response
*********************************************************************/
HI_U32 HI_PLAYREADY_HTTP_FetchLicenseEx(CURL *curl,
                                        HI_PLAYREADY_URL *pstUrl,
                                        HI_PLAYREADY_CHALLENGE_S *pChallenge,
                                        HI_PLAYREADY_ASCII_STRING *pResponse,
                                        HI_IS_WHAT_ENCRYPT IsWhatEncryp)
{
    HI_U8 strval[16];
    HI_U8 *licresp_opened = NULL;
    HI_U8 *licresp_closed = NULL;
    HI_U32 ret = HI_PLAYREADY_HTTP_STATUS_OK;

    HI_CHAR* strHeadername = NULL;
    HI_CHAR* strHeadervalue = NULL;
    HI_CHAR* strHeader = NULL;
    struct curl_slist *headers = NULL;
    CURLcode return_code;

    PLAYREADY_HTTP_HANDLE Httphandle;

    HI_INFO_PLAYREADY("Enter HI_PLAYREADY_HTTP_FetchLicenseEx\n");

    if ( (NULL == curl) || (NULL == pstUrl) )
    {
       HI_ERR_PLAYREADY("invalid param, null pointer in http fetch License~\n");
       return (HI_U32)HI_FAILURE;
    }

    if ( 255 < (HI_U32)strlen((HI_CHAR *)pstUrl->url) )
    {
       HI_ERR_PLAYREADY("invalid url in http fetch License~\n");
       return (HI_U32)HI_FAILURE;
    }

    g_HTTP_IsWhatEncryp = IsWhatEncryp;

    memset((void *)&Httphandle, 0, sizeof(PLAYREADY_HTTP_HANDLE));

    /* Add DRM specail data before challenge */
    Httphandle.DataBuffer = (HI_U8*)OEM_malloc(sizeof(HI_U8) * HTTP_XMLRPC_BUFSIZE);
    HI_INFO_PLAYREADY("Allocate Httphandle.DataBuffer:0x%x\n", (HI_U32)Httphandle.DataBuffer);
    memset((void *)Httphandle.DataBuffer, 0, HTTP_XMLRPC_BUFSIZE);
    Httphandle.Datalength = 0;

    if (IsWhatEncryp == IS_WMDRM_ENCRYPT)
    {
        Httphandle.Datalength += sprintf((HI_CHAR *)(Httphandle.DataBuffer), "%s", DRM_POST_PREFIX);
    }

    memcpy((Httphandle.DataBuffer + Httphandle.Datalength), pChallenge->ChallengeContent.pszString,
           pChallenge->ChallengeContent.length);
    Httphandle.Datalength += pChallenge->ChallengeContent.length;

    HI_INFO_PLAYREADY("pChallenge->URL.pszString : %s\n", (HI_CHAR *)pChallenge->URL.pszString);

    (HI_VOID)playreadyHttpInitEx(&headers, (HI_U8 *)"POST", pstUrl);

    //Add HTTP header tag
    if ((IsWhatEncryp == IS_NONE_ENCRYPT) || (IsWhatEncryp == IS_INVALID))
    {
        HI_ERR_PLAYREADY("Type is invalid!\n");
        ret = (HI_U32)HI_FAILURE;
        goto ErrorExit;
    }
    else if (IS_SECURE_CLOCK == IsWhatEncryp)
    {
        HI_INFO_PLAYREADY("IsWhatEncryp == IS_SECURE_CLOCK\n");

        playreadyHttpCurlAppendHead("Accept", "*/*", &headers);

        playreadyHttpCurlAppendHead(HDR_TAG_CONTENT_TYPE, HDR_VALUE_URLENCODED, &headers);

        memset((void *)strval, 0, 16);
        sprintf((HI_CHAR *)strval, "%d", Httphandle.Datalength);
        playreadyHttpCurlAppendHead(HDR_TAG_CONTENT_LENGTH, (HI_CHAR*)strval, &headers);

        playreadyHttpCurlAppendHead("User-Agent", "Client-User-Agent", &headers);

        playreadyHttpCurlAppendHead("Proxy-Connection", "Keep-Alive", &headers);

        playreadyHttpCurlAppendHead("Pragma", "no-cache", &headers);
    }
    else if (IsWhatEncryp == IS_WMDRM_ENCRYPT)
    {
        HI_INFO_PLAYREADY("IsWhatEncryp == IS_WMDRM_ENCRYPT\n");

        playreadyHttpCurlAppendHead(HDR_TAG_CONTENT_TYPE, HDR_VALUE_URLENCODED, &headers);

        memset((void *)strval, 0, 16);
        sprintf((HI_CHAR *)strval, "%d", Httphandle.Datalength);
        playreadyHttpCurlAppendHead(HDR_TAG_CONTENT_LENGTH, (HI_CHAR*)strval, &headers);
    }
    else if ((IsWhatEncryp == IS_PLAYREADY_ENCRYPT)
             || (IsWhatEncryp == IS_DOMAIN_JOIN)
             || (IsWhatEncryp == IS_DOMAIN_LEAVE)
             || (IsWhatEncryp == IS_GET_METER_CERT)
             || (IsWhatEncryp == IS_PROCESS_METERING)
             || (IsWhatEncryp == IS_ACK_LIC))
    {
        HI_INFO_PLAYREADY("IsWhatEncryp == ENCRYPT_OTHER\n");

        playreadyHttpCurlAppendHead(HDR_TAG_HOST, (HI_CHAR*)url_host, &headers);

        playreadyHttpCurlAppendHead(HDR_TAG_CONTENT_TYPE, HDR_VALUE_URLENCODED_PR, &headers);

        memset((void *)strval, 0, 16);
        sprintf((HI_CHAR *)strval, "%d", Httphandle.Datalength);
        playreadyHttpCurlAppendHead(HDR_TAG_CONTENT_LENGTH, (HI_CHAR*)strval, &headers);

        if (IS_DOMAIN_JOIN == IsWhatEncryp)
        {
            playreadyHttpCurlAppendHead(SOAPACTION, JOIN_DOMAIN, &headers);
        }
        else if (IS_DOMAIN_LEAVE == IsWhatEncryp)
        {
            playreadyHttpCurlAppendHead(SOAPACTION, LEAVE_DOMAIN, &headers);
        }
        else if (IS_PLAYREADY_ENCRYPT == IsWhatEncryp)
        {
            playreadyHttpCurlAppendHead(SOAPACTION, ACQ_LIC, &headers);
        }
        else if (IS_ACK_LIC == IsWhatEncryp)
        {
            playreadyHttpCurlAppendHead(SOAPACTION, ACK_LIC, &headers);
        }
        else if (IS_GET_METER_CERT == IsWhatEncryp)
        {
            playreadyHttpCurlAppendHead(SOAPACTION, GET_METERCERT, &headers);
        }
        else if (IS_PROCESS_METERING == IsWhatEncryp)
        {
            playreadyHttpCurlAppendHead(SOAPACTION, PROCESS_METER, &headers);
        }
    }
    else
    {
        HI_ERR_PLAYREADY("\nIsWhatEncryp == IS_NONE_ENCRYPT\n");
        ret = (HI_U32)HI_FAILURE;
        goto ErrorExit;
    }

    /* set head */
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    /* set challenge data */
    //HI_INFO_PLAYREADY("Set challenge data:%s\n", Httphandle.DataBuffer);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, Httphandle.DataBuffer);

    /* set data receive buffer */
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, playreadyHttpWriteData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, g_HttpRecvBuf);

    HI_INFO_PLAYREADY("Before curl perform,curl addr:0x%x\n", curl);
    return_code = curl_easy_perform(curl);
    if (CURLE_OK != return_code)
    {
        HI_ERR_PLAYREADY("Request fail, ret code:%d\n", return_code);
        ret = (HI_U32)return_code;
        goto ErrorExit;
    }
    HI_INFO_PLAYREADY("curl_easy_perform code:%d\n", return_code);
    curl_slist_free_all(headers);

    HI_INFO_PLAYREADY("\n----------Received datalength:%d\n", g_u32Content_length);
    //HI_INFO_PLAYREADY("All Received: %s\n", g_HttpRecvBuf);

    if (g_u32Content_length == 0)
    {
        HI_ERR_PLAYREADY("response data lenth is zero\n");

        ret = HI_PLAYREADY_HTTP_STATUS_FAILED_REPSONSE_CODE;

        goto ErrorExit;
    }

    if ((IS_SECURE_CLOCK == IsWhatEncryp)
        || (IS_GET_METER_CERT == IsWhatEncryp)
        || (IS_PROCESS_METERING == IsWhatEncryp)
        || (IS_ACK_LIC == IsWhatEncryp))
    {
        pResponse->length = g_u32Content_length;
        pResponse->pszString = (HI_U8*)OEM_malloc(pResponse->length + 1);
        if(NULL == pResponse->pszString)
        {
            HI_ERR_PLAYREADY("String Alloc size %d error!\n",pResponse->pszString);
            goto ErrorExit;
        }
        memset(pResponse->pszString, 0, pResponse->length + 1);
        memcpy(pResponse->pszString, g_HttpRecvBuf, pResponse->length);

        HI_INFO_PLAYREADY("IsWhatEncryp:0x%x\n", IsWhatEncryp);
        HI_INFO_PLAYREADY("\n\nResponse is: %s\n\n", pResponse->pszString);
        goto ErrorExit;
    }

    // try to get PR Lisence Response content
    if ((IS_PLAYREADY_ENCRYPT == IsWhatEncryp) || (IS_DOMAIN_JOIN == IsWhatEncryp) || (IS_DOMAIN_LEAVE == IsWhatEncryp))
    {
        licresp_opened = (HI_U8 *)strstr((HI_CHAR *)(g_HttpRecvBuf), (HI_CHAR *)PR_LICRESPONSE_OPENED); /* look for response open tag */
        licresp_closed = (HI_U8 *)strstr((HI_CHAR *)(g_HttpRecvBuf), (HI_CHAR *)PR_LICRESPONSE_CLOSED); /* look for response close tag */
    }
    else if (IS_WMDRM_ENCRYPT == IsWhatEncryp)   // try to get WMDRM Lisence Response content
    {
        licresp_opened = (HI_U8 *)strstr((HI_CHAR *)(g_HttpRecvBuf), (HI_CHAR *)WMDRM_LICRESPONSE_OPENED); /* look for response open tag */
        licresp_closed = (HI_U8 *)strstr((HI_CHAR *)(g_HttpRecvBuf), (HI_CHAR *)WMDRM_LICRESPONSE_CLOSED); /* look for response close tag */
    }

    HI_INFO_PLAYREADY("\nlicresp_opened:0x%x, licresp_closed:0x%x\n", (HI_U32)licresp_opened, (HI_U32)licresp_closed);

    if ((licresp_opened != NULL) && (licresp_closed != NULL))
    {
        /* Get Response */
        if ((IS_PLAYREADY_ENCRYPT == IsWhatEncryp) || (IS_DOMAIN_JOIN == IsWhatEncryp)
            || (IS_DOMAIN_LEAVE == IsWhatEncryp))
        {
            pResponse->length = (HI_U32)(licresp_closed - licresp_opened) + sizeof(PR_LICRESPONSE_CLOSED) - 1;
        }
        else if (IsWhatEncryp == IS_WMDRM_ENCRYPT)
        {
            pResponse->length = (HI_U32)(licresp_closed - licresp_opened) + sizeof(WMDRM_LICRESPONSE_CLOSED) - 1;
        }

        pResponse->pszString = (HI_U8*)malloc(sizeof(HI_U8) * (pResponse->length + 1));
        if (pResponse->pszString == NULL)
        {
            HI_ERR_PLAYREADY("OEM_malloc(pResponse->length + 1) failed!\n");
            ret = (HI_U32)HI_FAILURE;
            goto ErrorExit;
        }

        memcpy(pResponse->pszString, licresp_opened, pResponse->length);
        pResponse->pszString[pResponse->length] = '\0';
    }
    else
    {
        HI_ERR_PLAYREADY("Can not find license response!\n");
        ret = HI_PLAYREADY_HTTP_STATUS_FAILED_REPSONSE_CODE;
        goto ErrorExit;
    }

ErrorExit:
    //release allocate memory
    g_u32Content_length = 0;

    OEM_free((HI_VOID *)Httphandle.DataBuffer);
    memset(&Httphandle, 0, sizeof(PLAYREADY_HTTP_HANDLE));
    memset(g_HttpRecvBuf, 0, sizeof(g_HttpRecvBuf));

    HI_INFO_PLAYREADY(" Exit, ret=%d\n", ret);

    return ret;
}


/*********************************************************************
Funciton:HI_PLAYREADY_HTTP_FetchLicense
Parameter:
    HI_PLAYREADY_CHALLENGE_S *pChallenge, // [in] challenge content
    HI_PLAYREADY_ASCII_STRING *pResponse    // [out] drm response
*********************************************************************/
HI_U32 HI_PLAYREADY_HTTP_FetchLicense(HI_PLAYREADY_CHALLENGE_S *pChallenge, HI_PLAYREADY_ASCII_STRING *pResponse,
                                      HI_IS_WHAT_ENCRYPT IsWhatEncryp)
{
    HI_U32 ret = HI_SUCCESS;
    HI_PLAYREADY_URL stUrl;
    CURL *curl;

    HI_INFO_PLAYREADY(" Enter\n");
    memset(&stUrl, 0, sizeof(HI_PLAYREADY_URL));
    ret = playreadyHttpClientInit(&curl, pChallenge, &stUrl);
    if ( HI_SUCCESS != ret)
    {
        HI_ERR_PLAYREADY("HTTP Client init in FetchLicense failed.\n");
        return (HI_U32)HI_FAILURE;
    }

    ret = HI_PLAYREADY_HTTP_FetchLicenseEx(curl, &stUrl, pChallenge, pResponse, IsWhatEncryp);
    if ( HI_SUCCESS != ret)
    {
        HI_ERR_PLAYREADY("HI_PLAYREADY_HTTP_FATCHLINCENSE FAILED!\n");
        return (HI_U32)HI_FAILURE;
    }

    ret = playreadyHttpClientDeinit(curl);
    if ( HI_SUCCESS != ret)
    {
        HI_ERR_PLAYREADY("@@@@@@@@@@@@http client deinit in FetchLicense failed!@@@@@@@@@@@@@@\n");
    }

    HI_INFO_PLAYREADY(" Exit, ret=%d\n", ret);

    return (HI_U32)HI_SUCCESS;
}


HI_VOID HI_PLAYREADY_HTTP_Release_Response(HI_PLAYREADY_ASCII_STRING *pResponse)
{
    HI_INFO_PLAYREADY(" Enter\n");

    if (pResponse->pszString)
    {
        free(pResponse->pszString);
        pResponse->pszString = NULL;
    }
    else
    {
        HI_INFO_PLAYREADY("No Response Resource to Release!\n");
    }

    HI_INFO_PLAYREADY(" Exit \n");
}

HI_CHAR* HI_PLAYREADY_HTTP_GetReturnCodeString(HI_PLAYREADY_HTTP_STATE_E state)
{
    if(state  >  HI_PLAYREADY_HTTP_STATUS_OK && state < HI_PLAYREADY_HTTP_STATUS_MAX)
    {
        return g_ErrorCode_String[state];
    }
    else if(HI_PLAYREADY_HTTP_STATUS_OK == state)
    {
        return g_ErrorCode_String[state];
    }
    else
    {
        return "unKnow Return Status Code";
    }
}

/*----------------------------------------END-----------------------------------*/
