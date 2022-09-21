#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "drm_widevine_http.h"
#include "WVLog.h"

namespace drmengine {

HI_U8 g_httpRcvBuff[HTTP_XMLRPC_BUFSIZE];
HI_U32 g_u32ContentLength;

size_t drmHttpWriteData(HI_VOID* buffer, size_t size, size_t nmemb, HI_VOID* userp)
{
    if (strlen((HI_CHAR *)userp) + strlen((HI_CHAR *)buffer) > HTTP_XMLRPC_BUFSIZE)
    {
        g_u32ContentLength = 0;
        return 0;
    }

    strcat((HI_CHAR*)userp, (HI_CHAR*)buffer);

    g_u32ContentLength += size * nmemb;
    return size * nmemb;
}

DrmWidevineHttp::DrmWidevineHttp(const std::string &url)
{
    m_strUrl = url;
    drmHttpInit(url);
}

DrmWidevineHttp::~DrmWidevineHttp()
{
    if(0 != m_pCurl)
    {
        curl_easy_cleanup(m_pCurl);
        curl_global_cleanup();
    }
}

HI_S32 DrmWidevineHttp::drmHttpFetchLicense(const std::string& request, std::string* response)
{
    LOGI_DRM("Enter drmHttpFetchLicense()");
    struct curl_slist *headers = HI_NULL;
    HI_CHAR strval[16];
    HI_U32 ret = HI_SUCCESS;
    HI_U8* strResOpen = HI_NULL;
    HI_U8* strResEnd = HI_NULL;
    HI_U32 resBodyLength = 0;
    HI_HTTP_URL stUrl;

    memset(&stUrl, 0, sizeof(HI_HTTP_URL));

    drmHttpInitEx(&headers, "POST", &stUrl);
    drmHttpCurlAppendHead("Host", (HI_CHAR*)stUrl.host, &headers);
    drmHttpCurlAppendHead("Connection", "close", &headers);
    drmHttpCurlAppendHead("User-Agent", "Widevine CDM v1.0", &headers);

    memset(strval, 0X00, 16);
    sprintf(strval, "%d", request.length());
    drmHttpCurlAppendHead("Content-Length", (HI_CHAR*)strval, &headers);

    curl_easy_setopt(m_pCurl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(m_pCurl, CURLOPT_POSTFIELDS, (HI_CHAR*)request.c_str());

    curl_easy_setopt(m_pCurl, CURLOPT_WRITEFUNCTION, drmHttpWriteData);
    curl_easy_setopt(m_pCurl, CURLOPT_WRITEDATA, g_httpRcvBuff);

    LOGI_DRM("Begin get to curl_easy_perform");
    CURLcode returnCode = curl_easy_perform(m_pCurl);
    if(CURLE_OK != returnCode)
    {
        LOGI_DRM("CURLE_OK != returnCode = %d", returnCode);
        ret = returnCode;
        goto ErrorExit;
    }

    curl_slist_free_all(headers);

    if(0 == g_u32ContentLength)
    {
        LOGI_DRM("Get 0 byte character from server");
        ret = HI_FAILURE;
        goto ErrorExit;
    }

    strResOpen = (HI_U8*)strstr((HI_CHAR*)g_httpRcvBuff, (HI_CHAR*)HTTP_LICENSE_RES_OPEN);
    //strResEnd = (HI_U8*)strstr((HI_CHAR*)g_httpRcvBuff, (HI_CHAR*)HTTP_LICENSE_RES_CLOSE);

    if(HI_NULL != strResOpen)
    {
        resBodyLength = g_u32ContentLength - (HI_U32)(strResOpen - g_httpRcvBuff) - sizeof(HTTP_LICENSE_RES_OPEN);
        response->assign(reinterpret_cast<char*>(strResOpen + sizeof(HTTP_LICENSE_RES_OPEN)), resBodyLength);
    }
    else
    {
        ret = HI_FAILURE;
        goto ErrorExit;
    }

ErrorExit:
    g_u32ContentLength = 0;
    memset(g_httpRcvBuff, 0, sizeof(g_httpRcvBuff));

    return ret;
}

HI_S32 DrmWidevineHttp::drmHttpInit(const std::string& url)
{
    LOGI_DRM("Enter drmHttpInit(), url = %s", url.c_str());
    CURLcode returnCode;
    HI_U8 protocolHead;

    returnCode = curl_global_init(CURL_GLOBAL_ALL);
    if(CURLE_OK != returnCode)
    {
        m_bCurlStatus = HI_FALSE;
        return HI_FAILURE;
    }

    m_pCurl = curl_easy_init();
    if(HI_NULL == m_pCurl)
    {
        m_bCurlStatus = HI_FALSE;
        return HI_FAILURE;
    }

    //memset(m_pstUrl, 0X00, sizeof(HI_HTTP_URL));
    //memcpy(m_pstUrl.url, url.c_str(), url.length());
    //m_pstUrl.url[url.length()] = '\0';

    protocolHead = drmGetProtoHead((HI_U8*)url.c_str());
    LOGI_DRM("drmHttpInit(1)");
    if(PROTOCOL_HTTPS_HEAD == protocolHead)
    {
        LOGI_DRM("drmHttpInit(2)");
        returnCode = curl_easy_setopt(m_pCurl, CURLOPT_SSL_VERIFYPEER, 0);
        returnCode = curl_easy_setopt(m_pCurl, CURLOPT_SSL_VERIFYHOST, 0);
    }
    returnCode = curl_easy_setopt(m_pCurl, CURLOPT_URL, m_strUrl.c_str());

    m_bCurlStatus = HI_TRUE;
    LOGI_DRM("Leave drmHttpInit()");
    return HI_SUCCESS;
}

HI_S32 DrmWidevineHttp::drmGetProtoHead(HI_U8* url)
{
    LOGI_DRM("Enter drmGetProtoHead(), url = %s", url);
    HI_U8* urlHead;
    urlHead = (HI_U8*)strstr((HI_CHAR*)url, (HI_CHAR*)HTTP_HEAD);
    if(NULL != urlHead)
    {
        return PROTOCOL_HTTP_HEAD;
    }

    urlHead = (HI_U8*)strstr((HI_CHAR*)url, (HI_CHAR*)HTTPS_HEAD);
    if(NULL != urlHead)
    {
        return PROTOCOL_HTTPS_HEAD;
    }

    return PROTOCOL_OTHER_HEAD;
}

HI_VOID DrmWidevineHttp::drmParseUrl(HI_HTTP_URL* pstUrl, HI_U8* url)
{
    LOGI_DRM("Enter drmParseUrl(), url = %s", url);
    HI_U8* pcolon = HI_NULL;
    HI_U8* findhost = HI_NULL;
    HI_U8* s = HI_NULL;
    HI_U8* find = HI_NULL;

    if(HI_NULL == pstUrl || HI_NULL == url)
    {
        return;
    }

    s = url;
    if((findhost = (HI_U8*)strstr((HI_CHAR*)s, (HI_CHAR*)"//")) != HI_NULL)
    {
        if((findhost > s) && (*(findhost - 1) == ':'))
        {
            strncpy((HI_CHAR*)pstUrl->protocol, (HI_CHAR*)s, (HI_U32)(findhost - s - 1));
        }

        findhost += 2;
        if((find = (HI_U8*)strchr((HI_CHAR*)findhost, (HI_S32)'/')) != HI_NULL)
        {
            strncpy((HI_CHAR *)pstUrl->host, (HI_CHAR *)findhost, (HI_U32)(find - findhost));
            strncpy((HI_CHAR *)pstUrl->query, (HI_CHAR *)find, strlen((HI_CHAR *)find) + 1);
        }
        else
        {
            strncpy((HI_CHAR *)pstUrl->host, (HI_CHAR *)findhost, strlen((HI_CHAR *)findhost) + 1);
            memset(pstUrl->query,0,sizeof(pstUrl->query));
        }

        pcolon = (HI_U8 *)strchr((HI_CHAR *)pstUrl->host, (HI_S32)':');
        if (pcolon != HI_NULL)
        {
            pstUrl->port = (HI_U32)atoi((HI_CHAR *)(pcolon + 1)); //transfer port to numeric
            pcolon = '\0';                  //remove :port form host
        }
        else
        {
            LOGI_DRM("drmParseUrl(6), pstUrl->protocol = %s", pstUrl->protocol);
            struct servent * svt = HI_NULL;

            //svt=getservbyname( "http ", "tcp");
            svt = getservbyname((HI_CHAR *)pstUrl->protocol, "tcp");
            if (svt != (struct servent*)HI_NULL)
            {
                pstUrl->port = (HI_U32)ntohs((HI_U16)svt->s_port);
            }
            else
            {
                pstUrl->port = 0;
            }
        }
    }
    else
    {
        pstUrl->port  = 80;
//        drm_url->query = s;
        strncpy((HI_CHAR *)pstUrl->query, (HI_CHAR *)s, strlen((HI_CHAR *)s) + 1);
    }

    if(PROTOCOL_HTTP_HEAD == drmGetProtoHead(url))
    {
        pstUrl->port = 80;
    }
    else if(PROTOCOL_HTTPS_HEAD == drmGetProtoHead(url))
    {
        pstUrl->port = 443;
    }
    LOGI_DRM("Leave drmParseUrl()");
}

HI_U32 DrmWidevineHttp::drmHttpInitEx(struct curl_slist **headers, const HI_CHAR* method, HI_HTTP_URL *pstUrl)
{
    LOGI_DRM("Enter drmHttpInitEx()");
    HI_U8 *query = NULL;
    HI_U8 buf[HTTP_MAX_HDR_LINE];
    HI_U32 len = 0;

    if ((NULL == method) || (NULL == pstUrl))
    {
        return HI_FAILURE;
    }

    drmParseUrl(pstUrl, (HI_U8*)m_strUrl.c_str());
    curl_easy_setopt(m_pCurl, CURLOPT_POST, 1);

    query = pstUrl->query;
    if (!query || (! * query))
    {
        query[0] = '/';
        query[1] = '\0';
    }

    len = snprintf((HI_CHAR *)buf, HTTP_MAX_HDR_LINE, "%s %s HTTP/1.1\r\n", method, query);

    *headers = curl_slist_append(*headers, reinterpret_cast<HI_CHAR*>(buf));
    LOGI_DRM("Leave drmHttpInitEx()");

    return HI_SUCCESS;
}

HI_VOID DrmWidevineHttp::drmHttpCurlAppendHead(HI_CHAR* strHeaderName,
                                             HI_CHAR* strHeaderValue,
                                             struct curl_slist **headers)
{
    HI_CHAR* strheader;
    strheader = (HI_CHAR*)malloc(strlen(strHeaderName) + strlen(": ") + strlen(strHeaderValue) + 1);
    if(HI_NULL == strheader)
    {
        return;
    }

    memset(strheader, 0X00, (strlen(strHeaderName) + strlen(": ") + strlen(strHeaderValue) + 1));
    strheader = strncat(strheader, strHeaderName, strlen(strHeaderName));
    strheader = strncat(strheader, ": ", 2);
    strheader = strncat(strheader, strHeaderValue, strlen(strHeaderValue));
    *headers = curl_slist_append(*headers, strheader);

    if(HI_NULL != strheader)
    {
        free(strheader);
        strheader = HI_NULL;
    }
}

}