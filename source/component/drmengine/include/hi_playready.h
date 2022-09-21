/******************************************************************************

  Copyright (C), 2011-2021, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_playready.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2011.12.17
  Description   :
  History       :

*******************************************************************************/

#ifndef __HI_PLAYREADY_H__
#define __HI_PLAYREADY_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "hi_type.h"
#include "hi_common.h"

#ifdef PLAYREADY_PRIVATE_LIB
#include <drmcommon.h>
#include <drmcrt.h>
#include <drmutilities.h>
#include <drmcrt.h>
#include <drmcontextsizes.h>
#include <drmmanager.h>
#endif


/**********************************************************************
    ** Memory allocation functions
***********************************************************************/

#define OEM_malloc  malloc
#define OEM_free    free

#define PLAYREADY_ENV_LOCALSTORE    "/usr/data/playready/prdata.localstore\0"
#define PLAYREADY_ENV_CERT_PATH     "/usr/data/playready/prpd/"
#define PLAYREADY_ENV_KEYFILE_PATH  "/usr/data/playready/"
#define PLAYREADY_ENV_CFGFILE_PATH  "/usr/data/playready/playreadyconfig.txt"

#define CERT_NAME_PRIV              "priv.dat"
#define CERT_NAME_ZGPRIV            "zgpriv.dat"
#define CERT_NAME_BGROUPCERT        "bgroupcert.dat"
#define CERT_NAME_DEVCERTTEMPLATE   "devcerttemplate.dat"

#define PLAYREADY_MAX_PATH_LEN         (256)
#define PLAYREADY_MAX_CONTENT_FILE_LEN (1024)
#define PLAYREADY_MAX_CERT_FILE_NUM    (10)
#define PLAYREADY_16_BYTES             (16)

//#define __in
#define __in_bcount(size)
//#define __out
#define __out_bcount(size)
#define __inout


typedef enum{
    DECRYPT = 0,
    ENCRYPT,
}HI_PLAYREADY_CRYPTO_TYPE_E;

typedef enum{
    CERT_ROOT_KEY_TYPE_STB = 0,      /*certifications are encrypted by stb_root_key */
    CERT_ROOT_KEY_TYPE_R2R,          /*certifications are encrypted by r2r_root_key, reserved for future use*/
    CERT_ROOT_KEY_TYPE_BUTT,
}HI_PLAYREADY_CERT_ROOT_KEY_TYPE_E;

typedef enum{
    HI_PLAYREADY_LOG_LEVEL_NO = 0,       /*no log output*/
    HI_PLAYREADY_LOG_LEVEL_ERR,          /*enable error log output*/
    HI_PLAYREADY_LOG_LEVEL_WARN,
    HI_PLAYREADY_LOG_LEVEL_INFO,         /*enable info log output*/
    HI_PLAYREADY_LOG_LEVLE_BUTT
}HI_PLAYREADY_LOG_LEVEL_E;

typedef struct
{
    HI_CHAR szCertPath[PLAYREADY_MAX_PATH_LEN];
    HI_CHAR szKeyFilePath[PLAYREADY_MAX_PATH_LEN];
    HI_CHAR szLocalStorePath[PLAYREADY_MAX_PATH_LEN];
    HI_BOOL bCertProtection;
    HI_PLAYREADY_CERT_ROOT_KEY_TYPE_E  enCertRootKeyType;
    HI_BOOL bSecureClock;
    HI_BOOL bHardwareDecrypt;
    HI_U32  u32LogLevel;
}HI_PLAYREADY_CONFIG_S;

typedef struct
{
    HI_U32  length;
    HI_U8  *pszString;
}HI_PLAYREADY_ASCII_STRING;

typedef struct
{
    HI_U32  Valid;
    HI_PLAYREADY_ASCII_STRING SecretData;
    HI_PLAYREADY_ASCII_STRING Protection_Type;
    HI_PLAYREADY_ASCII_STRING Key_ID;
    HI_PLAYREADY_ASCII_STRING License_URL;
}HI_PR_Content_Encryption_Ver1_S;

typedef struct
{
    HI_U32  Valid;
    HI_PLAYREADY_ASCII_STRING Data;
}HI_PR_Content_Encryption_Ver2_S;

typedef struct
{
    HI_U8   m_oAccountID[PLAYREADY_16_BYTES];
    HI_U8   m_oServiceID[PLAYREADY_16_BYTES];
    HI_U32                    m_dwRevision;
}HI_PLAYREADY_DOMAINID_S;

typedef struct
{
    HI_PLAYREADY_DOMAINID_S     *domainID;
    HI_PLAYREADY_ASCII_STRING *customData;
    HI_PLAYREADY_ASCII_STRING *friendlyName;
    HI_PLAYREADY_ASCII_STRING *dstrDomainServer;

    HI_PLAYREADY_ASCII_STRING *reserved;
}HI_DOMAINID_PARAM_S;

typedef struct
{
    HI_PR_Content_Encryption_Ver1_S *pCE_Ver1;
    HI_PR_Content_Encryption_Ver2_S *pCE_Ver2;
    HI_PLAYREADY_ASCII_STRING           *pLocalStore;   //not used
    HI_BOOL       IsHardWareDecrypt;                    //not used
    HI_PLAYREADY_ASCII_STRING *playReadyCertPath;       //not used
    HI_U8   strContentfile[PLAYREADY_MAX_CONTENT_FILE_LEN];
    HI_BOOL initiatorFlag;
}HI_PLAYREADY_OPENPARAM_S;


/* Playready device certification buffer is enabled */
typedef   struct
{
    int isvalid;
    FILE *pfHandle;
    int s32FilePointer;
}PLAYREADY_File_S;


typedef struct
{
    char szstring[PLAYREADY_MAX_PATH_LEN];
    unsigned char  *pu8Addr;
    int  s32length;
    FILE *pfHandle;     /*Is different with PR_CERT_FILE_S*/
    PLAYREADY_File_S file[PLAYREADY_MAX_CERT_FILE_NUM];
}PLAYREADY_CERT_FILE_S;

typedef struct
{
    PLAYREADY_CERT_FILE_S pri;
    PLAYREADY_CERT_FILE_S zgpriv;
    PLAYREADY_CERT_FILE_S bgroupcert;
    PLAYREADY_CERT_FILE_S devcerttemplate;
}HI_PLAYREADY_DevCert_BUF_S;

typedef struct
{
    HI_PR_Content_Encryption_Ver1_S *pCE_Ver1;
    HI_PR_Content_Encryption_Ver2_S *pCE_Ver2;
    HI_PLAYREADY_ASCII_STRING           *pLocalStore; //not used
    HI_PLAYREADY_ASCII_STRING           *pKeyFile;    //not used
    HI_BOOL       IsHardWareDecrypt;                  //not used
    HI_PLAYREADY_DevCert_BUF_S     stDevCertBuffer;   //not used
    HI_U8 strContentfile[PLAYREADY_MAX_CONTENT_FILE_LEN];
    HI_BOOL initiatorFlag;
}HI_PLAYREADY_OPENPARAMEx_S;


typedef struct
{
    HI_PLAYREADY_ASCII_STRING ChallengeContent;
    HI_PLAYREADY_ASCII_STRING URL;
}HI_PLAYREADY_CHALLENGE_S;

typedef struct
{
    HI_U8   *u8Data;
    HI_U32  u32Length;
    HI_U8   *u8ReplicatedData;
    HI_U32  u32ReplicatedLength;
}HI_PLAYREADY_DECRYPTPARM_S;



typedef enum{
    IS_NONE_ENCRYPT  = 0x100,
    IS_WMDRM_ENCRYPT,

    IS_PLAYREADY_ENCRYPT,

    IS_DOMAIN_JOIN,
    IS_DOMAIN_LEAVE,

    IS_SECURE_CLOCK,
    IS_GET_METER_CERT,
    IS_PROCESS_METERING,
    IS_ACK_LIC,

    IS_INVALID
}HI_IS_WHAT_ENCRYPT;

typedef enum{
    /* Data type code for custom data. */
    SOAP_GARD_CUSTOM_DATA  = 1,

    /* Data type code for redirected URL. */
    SOAP_GARD_REDIRECT_URL = 2,

    /* Data type code for service ID. */
    SOAP_GARD_SERVICE_ID   = 3,

    /* Data type code for account ID. */
    SOAP_GARD_ACCOUNT_ID   = 4
}HI_RESPONSE_DATATYPE_E;


typedef enum hiHI_PLAYREADY_LICENSE_STATUS_CATEGORY_E{
    HI_PLAYREADY_LICENSE_STATE_NORIGHT = 0,     // Playback not permitted
    HI_PLAYREADY_LICENSE_STATE_UNLIM,           // Playback unlimited
    HI_PLAYREADY_LICENSE_STATE_COUNT,           // Playback valid 5 times
    HI_PLAYREADY_LICENSE_STATE_FROM,            // Playback valid from 5/12/2004
    HI_PLAYREADY_LICENSE_STATE_UNTIL,           // Playback valid until 7/12/2008
    HI_PLAYREADY_LICENSE_STATE_FROM_UNTIL,      // Playback valid from 5/12/2004 to 9/12/2008
    HI_PLAYREADY_LICENSE_STATE_COUNT_FROM,      // Playback valid 5 times from 5/12/2004 to 9/12/2008
    HI_PLAYREADY_LICENSE_STATE_COUNT_UNTIL,     // Playback valid 5 times until 7/12/2008
    HI_PLAYREADY_LICENSE_STATE_COUNT_FROM_UNTIL,    // Playback valid 5 times from 5/12/2004 to 9/12/2008
    HI_PLAYREADY_LICENSE_STATE_EXPIRATION_AFTER_FIRSTUSE,   // Playback valid for 24 hours from first use
    HI_PLAYREADY_LICENSE_STATE_FORCE_SYNC,      // No string is associated with this value. It is only used internally for license sync functionality
    HI_PLAYREADY_LICENSE_STATE_NOT_FOUND,       // No string is associated with this value. It is only used internally for license sync functionality.
    HI_PLAYREADY_LICENSE_STATE_ENTRY_MARKED_FOR_DELETION    // No string is associated with this value. It is only used internally for license sync functionality.
}HI_PLAYREADY_LICENSE_STATUS_CATEGORY_E;

typedef enum hiHI_PLAYREADY_SECURECLOCK_STATUS_E
{
    HI_PLAYREADY_SECURECLOCK_NOT_SET = 0,
    HI_PLAYREADY_SECURECLOCK_SET = 1,
    HI_PLAYREADY_SECURECLOCK_NEED_REFRESH = 2,
    HI_PLAYREADY_SECURECLOCK_UNKNOWN,
} HI_PLAYREADY_SECURECLOCK_STATUS_E;

typedef struct hiHI_PLAYREADY_DATE_TIME_S
{
    HI_U16 u16Year;
    HI_U16 u16Month;
    HI_U16 u16DayOfWeek;
    HI_U16 u16Day;
    HI_U16 u16Hour;
    HI_U16 u16Minute;
    HI_U16 u16Second;
    HI_U16 u16Milliseconds;
} HI_PLAYREADY_DATE_TIME_S;

typedef struct hiHI_PLAYREADY_LICENSE_STATUS_DATE_S
{
    HI_U32   u32NumDates;                       /* Number of items supplied in dwDate. */
    HI_PLAYREADY_DATE_TIME_S stdatetime [4];    /* Up to 4 dates. */
}HI_PLAYREADY_LICENSE_STATUS_DATE_S;

typedef struct hiHI_PLAYREADY_LICENSE_STATUS_COUNT_S
{
    HI_U32   u32NumCounts;                      /* Number of items supplied in dwCount. */
    HI_U32   u32Count  [4];                     /* Up to 4 counts. */
}HI_PLAYREADY_LICENSE_STATUS_COUNT_S;


typedef struct hiHI_PLAYREADY_LICENSE_STATUS_S
{
    HI_U32 u32StreamId;
    HI_PLAYREADY_LICENSE_STATUS_DATE_S stDates;
    HI_PLAYREADY_LICENSE_STATUS_COUNT_S stCounts;
    HI_PLAYREADY_LICENSE_STATUS_CATEGORY_E enCategory;
    HI_U32 u32Vague;                            /* 0 -> certain, 1 -> atleast.  (There could be more */
                                                /* licenses. Aggregation not possible.) */
}HI_PLAYREADY_LICENSE_STATUS_S;


typedef struct
{
    HI_U32 Num;
    HI_PLAYREADY_LICENSE_STATUS_S  unit[10];
}HI_PLAYREADY_LICENSE_STATICS_STATUS_S;

typedef enum
{
    WEB_INIT_UNKNOWN            = 0,
    WEB_INIT_JOINDOMAIN         = 1,
    WEB_INIT_LEAVEDOMAIN        = 2,
    WEB_INIT_LICENSEACQUISITION = 3,
    WEB_INIT_METERING           = 4,

    /*
        Below HbbTV extened initiators is defined in "PlayReady Documentation v2.9"
        Specifications > HbbTV Content Protection Using Microsoft PlayReady-> 3 Specification-> 3.1. The CSP-OITF Function Interface -> 3.1.2. PlayReady Messages
      */
    WEB_INIT_LICENSEQUERY             = 5,
    WEB_INIT_LICENSESERVERURIOVERRIDE = 6,
    WEB_INIT_SETCUSTOMDATA            = 7,
    WEB_INIT_SETSOAPHEADER            = 8,
    WEB_INIT_SETHTTPHEADER            = 9

}HI_WEB_INITIATOR_TYPE;

/*
** Join/Leave domain
*/
typedef struct
{
    HI_PLAYREADY_ASCII_STRING dstrDomainServer;

    HI_U8         oAccountID[PLAYREADY_16_BYTES];

    HI_U8         oServiceID[PLAYREADY_16_BYTES];

} HI_PLAYREADY_INIT_DOMAIN_DATA;

/*
** License and content acquisition
*/
typedef struct
{
    HI_PLAYREADY_ASCII_STRING dstrContentHeader;

    HI_PLAYREADY_ASCII_STRING dstrContentURL;

    /* Point to the <LA_URL> node in the content header. */
    HI_PLAYREADY_ASCII_STRING dstrLAURL;

    /* Point to the <LUI_URL> node (if exists) in the content header. */
    HI_PLAYREADY_ASCII_STRING dstrLUIURL;

    /* Point to the <DS_ID> node (if exists) in the content header. */
    HI_PLAYREADY_ASCII_STRING dstrDSID;

    /* Point to the content of <WMConvert> node. */
    HI_PLAYREADY_ASCII_STRING dstrWMConvert;

    /* Flag inidicating whether the <WMConvert> node is available. */
    HI_S32  fWMConvert;

}HI_PLAYREADY_INIT_LICACQ_DATA;

/*
** Metering data
*/
typedef struct
{
    HI_PLAYREADY_ASCII_STRING dstrMeteringCertServer;

    HI_U8          oMID[PLAYREADY_16_BYTES];

    HI_U32         lMaxPackets;

}HI_PLAYREADY_INIT_METERING_DATA;

/*
** LicenseQuery data, content header
*/
typedef struct
{
    HI_PLAYREADY_ASCII_STRING strContentHeader;

} HI_PLAYREADY_INIT_LICQUERY_DATA;

/*
** LicenseServerUriOverride data, LA_URL
*/
typedef struct
{
    /* Point to the <LA_URL> node. */
    HI_PLAYREADY_ASCII_STRING strLAURL;

} HI_PLAYREADY_INIT_LICSERVERURIOVERRIDE_DATA;

/*
** SetCustomData
*/
typedef struct
{
    /* Point to the <CustomData> node. */
    HI_PLAYREADY_ASCII_STRING strCustomData;

} HI_PLAYREADY_INIT_SETCUSTOMDATA_DATA;

/*
** SetSoapHeader
*/
typedef struct
{
    /* Point to the <SoapHeader> node. */
    HI_PLAYREADY_ASCII_STRING strSoapHeader;

} HI_PLAYREADY_INIT_SETSOAPHEADER_DATA;

/*
** SetHttpHeader
*/
typedef struct
{
    /* Point to the <HttpHeader> node. */
    HI_PLAYREADY_ASCII_STRING strHttpHeader;

} HI_PLAYREADY_INIT_SETHTTPHEADER_DATA;


typedef struct
{
    HI_WEB_INITIATOR_TYPE eType;                /* message type */

    HI_PLAYREADY_ASCII_STRING   dstrCustomData;       /* custom data */

    union
    {
        HI_PLAYREADY_INIT_DOMAIN_DATA   oDomainData;   /* Join/Leave domain */
        HI_PLAYREADY_INIT_LICACQ_DATA   oLicAcqData;   /* License and content acquisition */
        HI_PLAYREADY_INIT_METERING_DATA oMeteringData; /* Metering data reporting */
        HI_PLAYREADY_INIT_LICQUERY_DATA oLicQueryData; /*LicenseQuery, content header*/
        HI_PLAYREADY_INIT_SETCUSTOMDATA_DATA oCustomData;    /*custom data*/
        HI_PLAYREADY_INIT_SETSOAPHEADER_DATA oSoapHeaderData;  /*SetSoapHeader*/
        HI_PLAYREADY_INIT_SETHTTPHEADER_DATA oHttpHeaderData;  /*SetHttpHeader*/
        HI_PLAYREADY_INIT_LICSERVERURIOVERRIDE_DATA oLicServerUriOverrideData;   /*LicenseServerUriOverride data, LA_URL*/
    } Data;

}HI_PLAYREADY_INITIATOR_DATA;

#define HI_MAX_TRANSACTION_ID  100

#define HI_MAX_LICENSE_ACK     20

typedef struct
{
    HI_U8 m_oKID[PLAYREADY_16_BYTES];
    HI_U8 m_oLID[PLAYREADY_16_BYTES];
    HI_U32 m_dwResult;
    HI_U32 m_dwFlags;

} HI_PLAYREADY_LICENSE_ACK;

typedef enum
{
    HI_eUnknownProtocol = 0,
    HI_eV2Protocol,
    HI_eV3Protocol
} HI_PLAYREADY_LICENSE_PROTOCOL_TYPE;

typedef enum
{
    HI_HEADER_NOT_SET          = 0,
    HI_V1_HEADER               = 1,
    HI_V2_HEADER               = 2,
    HI_KID                     = 3,
    HI_V2_4_HEADER             = 5,
    HI_V4_HEADER               = 6,
    HI_AUTODETECT_HEADER       = 7,
    HI_PLAYREADY_OBJ           = 8,
    HI_V4_1_HEADER             = 9,
    HI_PLAYREADY_OBJ_WITH_KID  = 10,
    HI_HEADER_COMPONENTS       = 11,
    HI_RIGHTS_MANAGEMENT_HEADER     = 12,   /*Rights Management header in PRO, U8 type*/

} HI_PLAYREADY_CONTENT_SET_PROPERTY_E;

typedef enum
{
    HI_PLAYREADY_STORE_CLEANUP_ALL = 0xFFFFFFFF,
    HI_PLAYREADY_STORE_CLEANUP_DELETE_EXPIRED_LICENSES = 0x1,
    HI_PLAYREADY_STORE_CLEANUP_DELETE_REMOVAL_DATE_LICENSES = 0x2,
}HI_PLAYREADY_STORE_CLEANUP_E;

typedef struct
{
    HI_PLAYREADY_LICENSE_PROTOCOL_TYPE m_eType;
    HI_U8 m_rgbTransactionID[ HI_MAX_TRANSACTION_ID ];
    HI_U32  m_cbTransactionID;
    HI_PLAYREADY_LICENSE_ACK m_rgoAcks[ HI_MAX_LICENSE_ACK ];
    HI_PLAYREADY_LICENSE_ACK *m_pAcks;
    HI_U32  m_cMaxAcks;
    HI_U32  m_cAcks;
    HI_U32 m_dwResult;

} HI_PLAYREADY_LICENSE_RESPONSE;


typedef struct HI_PLAYREADY_MINIMUM_OUTPUT_PROTECTION_LEVELS
{
    HI_U32  isValid;
    HI_U32  wCompressedDigitalVideo;
    HI_U32  wUncompressedDigitalVideo;
    HI_U32  wCompressedDigitalAudio;
    HI_U32  wUncompressedDigitalAudio;
    HI_U32  wAnalogVideo;
} HI_PLAYREADY_MINIMUM_OUTPUT_PROTECTION_LEVELS;

typedef struct HI_PLAYREADY_PLAY_OPL_S
{
    HI_PLAYREADY_MINIMUM_OUTPUT_PROTECTION_LEVELS minOPL;

} HI_PLAYREADY_PLAY_OPL_S;

typedef struct HI_PLAYREADY_COPY_OPL
{
    HI_U32  isValid;
    HI_U32  wMinimumCopyLevel;

} HI_PLAYREADY_COPY_OPL_S;

typedef enum
{
    HI_PLAY_OPL         = 0,
    HI_COPY_OPL         = 1,

}HI_POLICY_TYPE;

typedef struct
{
    HI_PLAYREADY_COPY_OPL_S oplCopy;
    HI_PLAYREADY_PLAY_OPL_S oplPlay;

}HI_PLAYREADY_OPLs_S;

typedef HI_U32 HI_PLAYREADY_Handle;
#define HI_PLAYREADY_INVALID_HANDLE_VALUE (0xFFFFFFFF)

/*
only for debug
*/
HI_VOID HI_PLAYREADY_DebugPrintData( HI_CHAR * title,  HI_U8 * buffer,  HI_U32 length);
HI_S32 HI_PLAYREADY_DebugStoreToFile( HI_CHAR * filename,  HI_U8 *pu8Data,  HI_U32 length);

/**
\brief Get playready config attributes, initialize device certification buffers, initialize drm library.
*/
HI_S32 HI_PLAYREADY_Init(HI_VOID);
HI_S32 HI_PLAYREADY_DeInit(HI_VOID);

/**
\brief Get the pointor of global playready config attributes structure.
*/
HI_PLAYREADY_CONFIG_S * HI_PLAYREADY_GetConfigAttr(HI_VOID);

/**
\brief Get playready log level.
*/
HI_PLAYREADY_LOG_LEVEL_E HI_PLAYREADY_GetLogLevel(HI_VOID);

/**
\brief Creat the playready handle, declare the playready resources.
\attention \n
\param[in]  pOpenParam:  the param of handle£¬see details in::HI_PLAYREADY_OPENPARAM_S
\param[out] handle  PlayReady handle

\retval ::HI_SUCCESS  create PlayReady handle successful.
\retval ::HI_FAILURE  create PlayReady handle failed.
\see \n
*/
HI_U32 HI_PLAYREADY_Open(HI_PLAYREADY_OPENPARAM_S *pOpenParam,
                          HI_PLAYREADY_Handle *handle);

/**
\brief only if 1 == isplayreadyCertBufferEnable. Creat the playready handle, declare the playready resources.
\attention \n
\param[in]  pOpenParam:  the param of handle£¬see details in::HI_PLAYREADY_OPENPARAM_S
\param[out] handle  PlayReady handle

\retval ::HI_SUCCESS  create PlayReady handle successful.
\retval ::HI_FAILURE  create PlayReady handle failed.
\see \n
*/
HI_U32 HI_PLAYREADY_OpenEx(HI_PLAYREADY_OPENPARAMEx_S *pOpenParam,
                            HI_PLAYREADY_Handle *handle);

/**
\brief close PlayReady handle£¬release the resources.
\attention \n
\param[in,out] handle   the PlayReady handle will be released

\retval ::HI_SUCCESS  release PlayReady handle successful
\retval ::HI_FAILURE  release PlayReady handle failed!
\see \n
*/
HI_U32 HI_PLAYREADY_Close(HI_PLAYREADY_Handle handle);


/**
\brief  set or cancel custom data
\attention this function should combine with HI_PLAYREADY_LicAcquisition_Generate_Challenge() to make custom data effective\n
\param[in,out]  handle  PlayReady handle
\param[in]     stCustomerData  custom data

\retval ::HI_SUCCESS  set custom data success
\retval ::HI_FAILURE  set custom data failed
\see \n
none
*/
HI_S32 HI_PLAYREADY_SetCustomData(HI_PLAYREADY_Handle handle,
                                      HI_PLAYREADY_ASCII_STRING stCustomData);


/**
\brief generate PlayReady license acquisition
\attention \n
\param[in]  handle  PlayReady handle
\param[out] pChallenge  the license Acquisition£¬see datails in::HI_PLAYREADY_CHALLENGE_S

\retval ::HI_SUCCESS  generate PlayReady license acquisition success
\retval ::HI_FAILURE  generate PlayReady license acquisition failed
\see \n
none
*/
HI_U32 HI_PLAYREADY_LicAcquisition_Generate_Challenge(HI_PLAYREADY_Handle handle,
                                                       HI_PLAYREADY_CHALLENGE_S *pChallenge);

/**
\brief generate PlayReady license acquisition,add customer data input
\attention \n
\param[in]  handle  PlayReady handle
\param[in]  stCustomerData  customer data
\param[out] pChallenge  the license Acquisition£¬see datails in::HI_PLAYREADY_CHALLENGE_S

\retval ::HI_SUCCESS  generate PlayReady license acquisition success
\retval ::HI_FAILURE  generate PlayReady license acquisition failed
\see \n
none
*/
HI_U32 HI_PLAYREADY_LicAcquisition_Generate_ChallengeEx(HI_PLAYREADY_Handle handle,
                                                          HI_PLAYREADY_ASCII_STRING stCustomerData,
                                                          HI_PLAYREADY_CHALLENGE_S *pChallenge);

/**
\brief process the response returned by the server and store this license
\attention \n
\param[in]  handle  PlayReady handle
\param[in]  pResponse  data returned by the server £¬see details in::HI_PLAYREADY_ASCII_STRING
\param[out] pAckResponse  ack response to server

\retval ::HI_SUCCESS  operation is successful
\retval ::HI_FAILURE  operation is failed
\see \n
none
*/
HI_U32 HI_PLAYREADY_LicAcquisition_ProcessResponse(HI_PLAYREADY_Handle handle,
                                                     HI_PLAYREADY_ASCII_STRING *pResponse,
                                                     HI_PLAYREADY_LICENSE_RESPONSE *pAckResponse);

/**
\brief inquire the license status on local place¡£
\attention \n
\param[in,out]  handle  PlayReady handle

\retval ::HI_SUCCESS  inquire the license status successful
\retval ::HI_FAILURE  inquire the license status failed
\see \n
none
*/
HI_U32 HI_PLAYREADY_GetLicenseStatus(HI_PLAYREADY_Handle handle);

/**
\brief inquire the license status on local place, Get license status also¡£
\attention \n
\param[in]  handle  PlayReady handle
\param[out] stLicenseStatus license status structure

\retval ::HI_SUCCESS  inquire the license status successful
\retval ::HI_FAILURE  inquire the license status failed
\see \n
none
*/

HI_S32 HI_PLAYREADY_GetLicenseStatusEx(HI_PLAYREADY_Handle handle,
                                        HI_PLAYREADY_LICENSE_STATICS_STATUS_S *stStaticStatus);

/**
\brief inquire the license OPL status on local place¡£
\attention \n
\param[in]  handle  PlayReady handle
\param[out] oplPolicy  OPL statue

\retval ::HI_SUCCESS  inquire the license status successful
\retval ::HI_FAILURE  inquire the license status failed
\see \n
none
*/
HI_U32 HI_PLAYREADY_GetOPLStatus(HI_PLAYREADY_Handle handle,
                                  HI_PLAYREADY_OPLs_S *oplPolicy);
/**
\brief load the valid license on local place, and bind this license to the playready handle.
\attention \n
\param[in, out]  handle  PlayReady handle

\retval ::HI_SUCCESS  load license successful
\retval ::HI_FAILURE  load license failed
\see \n
none
*/
HI_U32 HI_PLAYREADY_LoadLicense(HI_PLAYREADY_Handle handle);

/**
\brief decrypt the data protected by playready in place¡£
\attention \n
\param[in]  handle  PlayReady handle
\param[in£¬out]  pDecryptParam  the decrypted data structure, see details in ::HI_PLAYREADY_DECRYPTPARM_S

\retval ::HI_SUCCESS  decrypt operation successful
\retval ::HI_FAILURE  decrypt operation failed
\see \n
none
*/
HI_U32 HI_PLAYREADY_Decrypt(HI_PLAYREADY_Handle handle,
                            HI_PLAYREADY_DECRYPTPARM_S *pDecryptParam);

/**
\brief generates a domain join challenge to be sent to the domain registration server to register a device to a domain
\attention \n
*/
HI_U32 HI_PLAYREADY_JoinDomain_Generate_Challenge(HI_PLAYREADY_Handle      handle,
                                                    HI_DOMAINID_PARAM_S      *pDomainParam,
                                                    HI_PLAYREADY_CHALLENGE_S *pChallenge);

/**
\brief processes a domain join response received from the domain registration server
\attention \n
*/
HI_U32 HI_PLAYREADY_JoinDomain_ProcessResponse(HI_PLAYREADY_Handle handle,
                                                HI_PLAYREADY_ASCII_STRING *pResponse);

/**
\brief generates a domain leave challenge to be sent to the domain registration server to unregister a device from a domain.
\attention \n
*/

HI_U32 HI_PLAYREADY_LeaveDomain_Generate_Challenge(HI_PLAYREADY_Handle      handle,
                                                     HI_DOMAINID_PARAM_S      *pDomainParam,
                                                     HI_PLAYREADY_CHALLENGE_S *pChallenge);
/**
\brief processes a domain leave response received from the domain registration server.
*/

HI_U32 HI_PLAYREADY_LeaveDomain_ProcessResponse(HI_PLAYREADY_Handle handle,
                                                 HI_PLAYREADY_ASCII_STRING *pResponse);
/**
\brief Decode a DomainID from Base64
*/
HI_U32 HI_PLAYREADY_B64_To_DomainID(HI_U8                   *pServiceID,
                                      HI_U8                   *pAccountID,
                                      HI_U32                   u32Revision,
                                      HI_PLAYREADY_DOMAINID_S *DomainID);
/**
\brief Decode a DomainID from Base64
*/
HI_U32 HI_PLAYREADY_GetResponseData(HI_PLAYREADY_Handle handle,
                                      HI_PLAYREADY_ASCII_STRING *pResponse,
                                      HI_RESPONSE_DATATYPE_E DataType,
                                      HI_PLAYREADY_ASCII_STRING *pDataString);
/**
\brief Parse the web initiators to get the data
*/

HI_U32 HI_PLAYREADY_Generate_InitiatorData(HI_PLAYREADY_ASCII_STRING   webInitiators,
                                           HI_PLAYREADY_INITIATOR_DATA **pInitiatorData,
                                           HI_U32                      *number);
/**
\brief Parse the web initiators to get the data
*/
HI_U32 HI_PLAYREADY_Release_InitiatorData(HI_PLAYREADY_INITIATOR_DATA **pInitiatorData,
                                              HI_U32 number);
/**
\brief  it generates a metering certificate XML challenge to be sent to a server for acquiring a metering certificate.
    This function is used only for the V4 protocols, not the V2 protocols.
*/

HI_U32 HI_PLAYREADY_MeterCert_Generate_Challenge(HI_PLAYREADY_Handle handle,
                                                   HI_PLAYREADY_INITIATOR_DATA initData,
                                                   HI_PLAYREADY_CHALLENGE_S *pChallenge);
/**
\brief it handles the metering certificate acquisition response message by extracting the embedded meter certificate and storing it in the metering certificate store.
*/

HI_U32 HI_PLAYREADY_MeterCert_ProcessResponse(HI_PLAYREADY_Handle handle,
                                               HI_PLAYREADY_ASCII_STRING *pResponse);
/**
\brief find the MeterCert by MID
*/
HI_U32 HI_PLAYREADY_FindMeterCertByMID(HI_PLAYREADY_Handle handle,
                                         HI_U8 MID[],
                                         HI_PLAYREADY_ASCII_STRING *pMeterCert);
/**
\brief Release the MeterCert Resources after called HI_PLAYREADY_FindMeterCertByMID!
*/
HI_VOID HI_PLAYREADY_Release_MeterCert(HI_PLAYREADY_ASCII_STRING *pMeterCert);
/**
\brief it collects device metering data for a specific metering ID
*/

HI_U32 HI_PLAYREADY_Metering_Generate_Challenge(HI_PLAYREADY_Handle       handle,
                                                  HI_PLAYREADY_CHALLENGE_S  *pChallenge,
                                                  HI_PLAYREADY_ASCII_STRING *pMeterCert);
/**
\brief it clears device metering data and resets the metering data store for the metering key IDs specified in the metering response
*/

HI_U32 HI_PLAYREADY_Metering_ProcessResponse(HI_PLAYREADY_Handle handle,
                                              HI_PLAYREADY_ASCII_STRING *pResponse);


HI_U32 HI_PLAYREADY_GetSecureClock(  HI_PLAYREADY_Handle handle,
                                    HI_PLAYREADY_SECURECLOCK_STATUS_E   *penStatus,
                                    HI_PLAYREADY_DATE_TIME_S *pstTime);

/**
\brief it creates a secure clock challenge, which is sent over the Internet directly from a device or by a proxy application on a computer.
*/

HI_U32 HI_PLAYREADY_SecureClock_Generate_Challenge(HI_PLAYREADY_Handle handle,
                                                    HI_PLAYREADY_CHALLENGE_S *pChallenge);
/**
\brief it processes the response received from the clock service, verifies and stores the clock packet, and sets the clock time
*/

HI_U32 HI_PLAYREADY_SecureClock_ProcessResponse(HI_PLAYREADY_Handle handle,
                                                 HI_PLAYREADY_ASCII_STRING *pResponse);
/**
\brief This function will invalidate the metering certificate for the specified MID by deleting the certificate from the store,
but retaining the MID and URL. This may be necessary if the metering certificate is known to be obsolete.
*/
HI_U32 HI_PLAYREADY_MeterCert_Invalidate(HI_PLAYREADY_Handle handle,
                                          HI_U8 MID[]);

/**
\brief After receiving a metering certificate response from the server, the application should call this function.
The certificate will be validated and then added to the metering certificate store.
*/
HI_U32 HI_PLAYREADY_MeterCert_Update(  HI_PLAYREADY_Handle handle,
                                       HI_PLAYREADY_ASCII_STRING *pMeterCert,
                                       HI_U8 MID[]);

/**
\brief This function will delete the metering certificate store entry for the specified MID.
The repercussions of this deletion are that metering data will no longer be transmitted, unless a new license is later acquire that is associated with this MID.
This function should not be called unless these repercussions are fully understood.
*/
HI_U32 HI_PLAYREADY_MeterCert_Delete(HI_PLAYREADY_Handle handle,
                                      HI_PLAYREADY_ASCII_STRING *pMeterCert,
                                      HI_U8 MID[]);
/**
\brief it generates a license acquisition acknowledge challenge
*/
HI_U32 HI_PLAYREADY_LicenseAcq_Generate_Ack(HI_PLAYREADY_Handle handle,
                                              HI_PLAYREADY_LICENSE_RESPONSE *pLicResponse,
                                             HI_PLAYREADY_CHALLENGE_S *pChallenge,
                                              HI_U8 *URL);
/**
\brief it generates a license acquisition acknowledge challenge
*/

HI_U32 HI_PLAYREADY_LicenseAcq_ProcessAckResponse(  HI_PLAYREADY_Handle handle,
                                                   HI_PLAYREADY_ASCII_STRING *pResponse);
/**
\brief it sets content properties used for DRM tasks
*/
HI_U32 HI_PLAYREADY_Content_SetProperty(HI_PLAYREADY_Handle handle,
                                            HI_PLAYREADY_CONTENT_SET_PROPERTY_E ePropertyType,
                                            HI_PLAYREADY_ASCII_STRING pPropertyData);
/**
\brief Release the Challenge Resource after Called HI_PLAYREADY_XXXX_Generate_Challenge.

\attention MUST be called after HI_PLAYREADY_XXXX_Generate_Challenge when don't need the Challenge.\n
*/
HI_VOID HI_PLAYREADY_Release_Challenge(HI_PLAYREADY_CHALLENGE_S *pChallenge);

/**
\brief delete all unusable licenses from the license store
*/
HI_U32 HI_PLAYREADY_StoreMgmt_CleanupStore(HI_PLAYREADY_Handle handle,
                                            HI_PLAYREADY_STORE_CLEANUP_E en );

/**
\brief Deletes licenses for one stream which DRM header has been setted.
*/
HI_U32 HI_PLAYREADY_StoreMgmt_DeleteLicenses(HI_PLAYREADY_Handle handle,
                                             HI_U32 *pu32LicDeleted );

/**
\brief create an envelop handle and initialize the PlayReady context
*/
HI_U32 HI_PLAYREADY_Envelop_Open(HI_PLAYREADY_OPENPARAM_S *pOpenParam,
                        HI_PLAYREADY_Handle *handle);
/**
\brief Decrypt the envelop file and store it locally
*/
HI_U32 HI_PLAYREADY_Envelop_Read(HI_PLAYREADY_Handle handle,
                        HI_U8* outputFileName);
/**
\brief destroy the envelop handle and deinitialize the PlayReady context
*/
HI_U32 HI_PLAYREADY_Envelop_Close(HI_PLAYREADY_Handle handle);

/**
 * burn root key into otp for encrypting/decrypting certifications
 *
 * @param[out] bWrited,  If CertRootKey is writed, it returns HI_TRUE, other it returns HI_FALSE.
 * @return
 *     HI_SUCCESS for get CertRootKey status successfully, others for failed.
 */

HI_S32 HI_PLAYREADY_Provision_IsCertRootKeyWrited(HI_BOOL *bWrited);


/**
 * burn root key into otp for encrypting/decrypting certifications
 *
 * @param[in] pu8CertRootKey,  16bytes root key, which is used to encrypt/decrypt certifications and it's stored into otp, if it is NULL, the root key will be random key.
 * @return
 *     HI_SUCCESS for burn successfully, others for failed.
 */

HI_S32 HI_PLAYREADY_Provision_SetCertRootKey(HI_U8 *pu8CertRootKey);

/**
 * Decrypt playready certifications with  CEK, than encrypt them with CertRootKey.
 *
 * @param[in] pu8CEK,  the certifications are encrypted with CEK, if it's NULL, the certifications are clear data.
 * @return
 *     HI_SUCCESS for burn successfully, others for failed.
 */

HI_S32 HI_PLAYREADY_Provision_CertInit(HI_U8 *pu8CEK);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __HI_PLAYREADY_H__ */


