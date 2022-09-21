/******************************************************************************

  Copyright (C), 2014-2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_hdmi_srm.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2017/02/08
  Description   :
  History       :
  Date          : 2017/02/08
  Author        : sdk
  Modification  :
*******************************************************************************/
#ifndef __DRV_HDMI_SRM_H__
#define __DRV_HDMI_SRM_H__

#ifdef __cplusplus
extern "C" {
#endif

#define SRM_ID_SIGNIFIES			0x9
#define SRM_HDCP2X_INDICATOR		0x1
#define SRM_SIZE_DEV_ID				5
/*  System Renewability Message Format  */
#define SRM_SIZE_HEADER             12      //sizeof(SRM_HEADER_1_UN)+sizeof(SRM_HEADER_2_UN)+sizeof(SRM_REVOC_INFO_UN)
#define SRM_SIZE_LENGTH_G1			3    	//24 bits
#define SRM_SIZE_MAX_HEAD_DEV_ID    4720    //33760 bits
#define SRM_SIZE_LLC_SIGNATURE      384     //3072  bits
#define SRM_SIZE_MAX_HEAD_FORMAT    5116    //(SRM_SIZE_HEADER + SRM_SIZE_MAX_HEAD_DEV_ID + SRM_SIZE_LLC_SIGNATURE)
/* Next-generation extension format  */
#define SRM_SIZE_LENGTH_GNEXT		2    	//16 bits
#define SRM_SIZE_MAX_EXT_DEV_ID     (1024*5)
#define SRM_SIZE_MAX_EXT_FORMAT     5498    //(sizeof(SRM_EXTENSION_1_UN)+SRM_SIZE_MAX_EXT_DEV_ID+SRM_SIZE_LLC_SIGNATURE)
/* self-define max extension format count */
#define SRM_MAX_EXT_FORMAT_NUM      10


typedef HI_U8 SRM_DEV_ID_S[SRM_SIZE_DEV_ID];

typedef union
{
    struct{
        HI_U32          b04_SrmId               :   4;
        HI_U32          b04_Hdcp2Indicator      :   4;
        HI_U32          b08_Reserved            :   8;
        HI_U32          b16_SrmVersion          :  16;
    }bits;

    HI_U32  u32Data;

}SRM_HEADER_1_UN;


typedef union
{
    struct{
        HI_U32          b08_SrmGenerationNum    :   8;
        HI_U32          b24_Length              :  24;
    }bits;

    HI_U32  u32Data;

}SRM_HEADER_2_UN;



typedef union
{
    struct{
        HI_U32          b10_NumOfDevices        :  10;
        HI_U32          b22_Reserved            :  22;
    }bits;

    HI_U32  u32Data;

}SRM_REVOC_INFO_UN;


typedef union
{
    struct{
        HI_U32          b16_Length              :  16;
        HI_U32          b06_Reserved            :   6;
        HI_U32          b10_NumOfDevices        :  10;
    }bits;

    HI_U32  u32Data;

}SRM_EXTENSION_1_UN;


typedef struct{

    SRM_EXTENSION_1_UN  unExt1;

    HI_U8               *pu8ExtDeviceIds;
    HI_U8               *pu8ExtLlcSignature;

}SRM_EXT_FORMAT_S;

typedef struct
{
    /*  System Renewability Message Format  */
    SRM_HEADER_1_UN     unHead1;
    SRM_HEADER_2_UN     unHead2;
    SRM_REVOC_INFO_UN   unRevocInfo;
    HI_U8               *pu8HeadDeviceIds;
    HI_U8               *pu8HeadLlcSignature;

    /* Next-generation extension format  */
    SRM_EXT_FORMAT_S    stExtFmt[SRM_MAX_EXT_FORMAT_NUM+1];

    /* sel-define */
	HI_BOOL 			bInit;
	HI_BOOL             bValid;
    HI_U8               *pu8RawData;

}SRM_INFO_S;



HI_S32	DRV_HDMI_SrmInit(HI_VOID);

HI_S32	DRV_HDMI_SrmDeinit(HI_VOID);

HI_S32	DRV_HDMI_SrmSet(HI_U8 *pu8Data,HI_U32 u32Len,HI_BOOL bFromUser);

HI_S32	DRV_HDMI_SrmCheck(HI_U8 *pu8DevIdList,HI_U32 u32DevIdNum);

HI_S32	DRV_HDMI_SrmGet(SRM_INFO_S **ppstSrmInfo);



#ifdef __cplusplus
}
#endif

#endif	/* __DRV_HDMI_SRM_H__ */




