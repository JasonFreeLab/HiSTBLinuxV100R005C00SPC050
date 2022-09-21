#ifndef DRM_WIDEVINE_HTTP_H_
#define DRM_WIDEVINE_HTTP_H_

#include <string>

#include "hi_type.h"
#include "curl.h"

namespace drmengine {

#define HTTP_HEAD "http://"
#define HTTPS_HEAD "https://"
#define HTTP_LICENSE_RES_OPEN "\r\n\r\n"
#define HTTP_LICENSE_RES_CLOSE "</soap:Envelope>"

#define HTTP_MAX_HDR_LINE (0X400)
#define HTTP_XMLRPC_BUFSIZE (1024*28)
#define HTTP_OK_RESPONSE (200)

typedef struct hi_HTTP_URL{
    HI_U8 *url;
    HI_U32 port;
    HI_U8 query[255];
    HI_U8 host[0x40];
    HI_U8 protocol[8];
} HI_HTTP_URL;

enum HI_DRM_PROTOCOL_HEAD{
    PROTOCOL_HTTP_HEAD = 0,
    PROTOCOL_HTTPS_HEAD,
    PROTOCOL_OTHER_HEAD
};

enum HI_DRM_WVRES_TYPE{
    WIDEVINE_RESPONSE_PROVISION = 0,
    WIDEVINE_RESPONSE_LICENSE
};

class DrmWidevineHttp {
public:
    DrmWidevineHttp(const std::string& url);

    ~DrmWidevineHttp();

    HI_S32 drmHttpFetchLicense(const std::string& request, std::string* response);

private:
    HI_S32 drmHttpInit(const std::string& url);
    HI_S32 drmGetProtoHead(HI_U8* url);
    HI_VOID drmParseUrl(HI_HTTP_URL* pstUrl, HI_U8* url);
    HI_U32 drmHttpInitEx(struct curl_slist **headers, const HI_CHAR* method, HI_HTTP_URL *pstUrl);
    HI_VOID drmHttpCurlAppendHead(HI_CHAR* strHeaderName, HI_CHAR* strHeaderValue,
                                                                struct curl_slist **headers);

    CURL* m_pCurl;
    HI_BOOL m_bCurlStatus;
    std::string m_strUrl;

    DrmWidevineHttp(const DrmWidevineHttp& drmWidevineHttp);
    DrmWidevineHttp operator=(const DrmWidevineHttp& drmWidevineHttp);
};

}

#endif
