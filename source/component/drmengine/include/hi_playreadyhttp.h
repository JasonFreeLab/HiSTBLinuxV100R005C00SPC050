/******************************************************************************

  Copyright (C), 2011-2021, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_playreadyhttp.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2011.12.17
  Description   :
  History       :

*******************************************************************************/

#ifndef __HI_PLAYREADYHTTP_H__
#define __HI_PLAYREADYHTTP_H__
#define URL_MAX_QUERY (255)

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include <curl.h>
#include "hi_type.h"
#include "hi_common.h"
#include "hi_playready.h"


/* http status, sent in sync with the license states
*/
typedef enum hiPLAYREADY_HTTP_STATE_E
{
    HI_PLAYREADY_HTTP_STATUS_OK            = 0,
    HI_PLAYREADY_UNSUPPORTED_PROTOCOL,          //1: unsupported protocol
    HI_PLAYREADY_FAILED_INIT,                   //2: failed init
    HI_PLAYREADY_URL_MALFORMAT,                 //3: URL using bad/illegal format or missing URL
    HI_PLAYREADY_URL_MALFORMAT_USER,            //4: unknown error
    HI_PLAYREADY_COULDNT_RESOLVE_PROXY,         //5: couldnt resolve proxy name
    HI_PLAYREADY_COULDNT_RESOLVE_HOST,          //6: couldn't resolve host name
    HI_PLAYREADY_COULDNT_CONNECT,               //7: couldn't connect to server
    HI_PLAYREADY_FTP_WEIRD_SERVER_REPLY,        //8: FTP: weird server reply
    HI_PLAYREADY_FTP_ACCESS_DENIED,             //9: FTP: access deny
    HI_PLAYREADY_FTP_USER_PASSWORD_INCORRECT,   //10: unknown error
    HI_PLAYREADY_FTP_WEIRD_PASS_REPLY,          //11: FTP: unknown PASS reply
    HI_PLAYREADY_FTP_WEIRD_USER_REPLY,          //12: FTP: unknown USER reply
    HI_PLAYREADY_FTP_WEIRD_PASV_REPLY,          //13: FTP: unknown PASV reply
    HI_PLAYREADY_FTP_WEIRD_227_FORMAT,          //14: FTP: unknown 227 response format
    HI_PLAYREADY_FTP_CANT_GET_HOST,             //15: FTP: can't figure out the host in the PASV response
    HI_PLAYREADY_FTP_CANT_RECONNECT,            //16: FTP: can't connect to server the response code is unknown
    HI_PLAYREADY_FTP_COULDNT_SET_BINARY,        //17: FTP: couldn't set binary mode
    HI_PLAYREADY_PARTIAL_FILE,                  //18: Transferred a partial file
    HI_PLAYREADY_FTP_COULDNT_RETR_FILE,         //19: FTP: couldn't retrieve (RETR failed) the specified file
    HI_PLAYREADY_FTP_WRITE_ERROR,               //20: FTP: the post-transfer acknowledge response was not OK
    HI_PLAYREADY_FTP_QUOTE_ERROR,               //21: FTP: a quote command returned error
    HI_PLAYREADY_HTTP_RETURNED_ERROR,           //22: HTTP response code said error
    HI_PLAYREADY_WRITE_ERROR,                   //23: failed writing received data to disk/application
    HI_PLAYREADY_MALFORMAT_USER,                //24: unknown error
    HI_PLAYREADY_UPLOAD_FAILED,                 //25: upload failed (at start/before it took off)
    HI_PLAYREADY_READ_ERROR,                    //26: failed to open/read local data from file/application
    HI_PLAYREADY_OUT_OF_MEMORY,                 //27: out of memory
    HI_PLAYREADY_OPERATION_TIMEOUTED,           //28: a timeout was reached
    HI_PLAYREADY_FTP_COULDNT_SET_ASCII,         //29: FTP could not set ASCII mode (TYPE A)
    HI_PLAYREADY_FTP_PORT_FAILED,               //30: FTP command PORT failed
    HI_PLAYREADY_FTP_COULDNT_USE_REST,          //31: FTP command REST failed
    HI_PLAYREADY_FTP_COULDNT_GET_SIZE,          //32: FTP command SIZE failed
    HI_PLAYREADY_HTTP_RANGE_ERROR,              //33: a range was requested but the server did not deliver it
    HI_PLAYREADY_HTTP_POST_ERROR,               //34: internal problem setting up the POST
    HI_PLAYREADY_SSL_CONNECT_ERROR,             //35: SSL connect error
    HI_PLAYREADY_BAD_DOWNLOAD_RESUME,           //36: couldn't resume download
    HI_PLAYREADY_FILE_COULDNT_READ_FILE,        //37: couldn't read a file:// file
    HI_PLAYREADY_LDAP_CANNOT_BIND,              //38: LDAP: cannot bind
    HI_PLAYREADY_LDAP_SEARCH_FAILED,            //39: LDAP: search failed
    HI_PLAYREADY_LIBRARY_NOT_FOUND,             //40: a required shared library was not found

    HI_PLAYREADY_HTTP_STATUS_FAILED_REPSONSE_CODE = 41,  // 1~40 are error numbers of curl
    HI_PLAYREADY_HTTP_STATUS_FAILED_RESPONSE_READ,
    HI_PLAYREADY_HTTP_STATUS_FAILED_CONNECT,
    HI_PLAYREADY_HTTP_STATUS_FAILED_GETPOST,
    HI_PLAYREADY_DRM_E_SERVER_DEVICE_LIMIT_REACHED,
    HI_PLAYREADY_DRM_E_DEVCERT_REVOKED,
    HI_PLAYREADY_DRM_E_SERVER_INTERNAL_ERROR,
    HI_PLAYREADY_DRM_E_SERVER_INVALID_MESSAGE,
    HI_PLAYREADY_DRM_E_SERVER_SERVICE_SPECIFIC,
    HI_PLAYREADY_HTTP_STATUS_REQUIRE_DOMAIN,
    HI_PLAYREADY_DRM_E_SERVER_RENEW_DOMAIN,
    HI_PLAYREADY_HTTP_INTERNAL_SERVER_UNKNOWN,
    HI_PLAYREADY_DRM_E_SERVER_NOT_A_MEMBER,
    HI_PLAYREADY_DRM_E_SERVER_PROTOCOL_VERSION_MISMATCH,
    HI_PLAYREADY_DRM_E_SERVER_UNKNOWN_ACCOUNTID,
    HI_PLAYREADY_DRM_E_SERVER_PROTOCOL_REDIRECT,

    HI_PLAYREADY_HTTP_STATUS_MAX
}HI_PLAYREADY_HTTP_STATE_E;

/* http header structure */
typedef struct PLAYREADY_HTTP_HEADER_s
{
    HI_PLAYREADY_ASCII_STRING name;
    HI_PLAYREADY_ASCII_STRING value;

    struct PLAYREADY_HTTP_HEADER_s *next;
}PLAYREADY_HTTP_HEADER_S;

typedef struct
{
    HI_U8   *url;                  // url ptr
    HI_U32   port;                 // port value
    HI_U8    query[URL_MAX_QUERY];                // ptr into query
    HI_U8    host[0x40];           // server host
    HI_U8    protocol[8];          // protocol
} HI_PLAYREADY_URL;

/**
\brief   Send the Challenge to the Server(URL contain in the pChallenge), And store the Response returned by the Server.
        IsWhatEncryp is the Challenge Type
\attention \n
*/
HI_U32 HI_PLAYREADY_HTTP_FetchLicense(HI_PLAYREADY_CHALLENGE_S *pChallenge, HI_PLAYREADY_ASCII_STRING *pResponse, HI_IS_WHAT_ENCRYPT IsWhatEncryp);

/**
\brief   Send the Challenge to the Server(URL contain in the pChallenge), And store the Response returned by the Server.
        IsWhatEncryp is the Challenge Type
        This function does not include socket opening and connecting. The socket's opening and connecting should be implemented outside.
\attention \n
*/
HI_U32 HI_PLAYREADY_HTTP_FetchLicenseEx(CURL *curl, HI_PLAYREADY_URL *pstUrl, HI_PLAYREADY_CHALLENGE_S *pChallenge, HI_PLAYREADY_ASCII_STRING *pResponse, HI_IS_WHAT_ENCRYPT IsWhatEncryp);
/**
\brief Release the Response Resource after Called HI_PLAYREADY_HTTP_FetchLicenseEx.

\attention MUST be called after HI_PLAYREADY_HTTP_FetchLicense(Ex) when don't need the Response.\n
*/
HI_VOID HI_PLAYREADY_HTTP_Release_Response(HI_PLAYREADY_ASCII_STRING *pResponse);

HI_CHAR* HI_PLAYREADY_HTTP_GetReturnCodeString(HI_PLAYREADY_HTTP_STATE_E state);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __HI_PLAYREADYHTTP_H__ */


