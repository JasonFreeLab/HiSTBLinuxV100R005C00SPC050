/******************************************************************************

  Copyright (C), 2014-2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_hdmi_srm.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2017/02/08
  Description   :
  History       :
  Date          : 2017/02/08
  Author        : sdk
  Modification  :
*******************************************************************************/

#include "hi_type.h"
#include "hdmi_platform.h"
#include "drv_hdmi_platform.h"
#include "hdmi_product_define.h"
#include "drv_hdmi_srm.h"



#define SRM_NULL_CHK(p) do{\
	if(HI_NULL == p)\
	{HDMI_WARN("null pointer!\n");\
	return HI_FAILURE;}\
}while(0)

#define SRM_INIT_CHK(pstSrmInfo) do{\
	SRM_NULL_CHK(pstSrmInfo);\
	if(pstSrmInfo->bInit != HI_TRUE)\
	{HDMI_WARN("srm didn't init!\n");\
	return HI_FAILURE;}\
}while(0)


SRM_INFO_S	s_stSrmInfo;


static HI_VOID SrmToLittleEndian(HI_U8 *pu8Data,HI_U32 u32Len)
{
	HI_U8	u8Tmp = 0;
	HI_U32	i = 0;
	HI_U32	u32TestEndian = 0;

	u32TestEndian = 0x12345678;
	u8Tmp = *((HI_U8 *)&u32TestEndian);

	if (0x78 == u8Tmp)
	{
		if(0 != (u32Len % 4))
		{
			HDMI_WARN("u32Len =%u\n",u32Len);
		}

		for (i=0; (i<u32Len) && (pu8Data+i); i+=4)
		{
			u8Tmp = pu8Data[i+0];
			pu8Data[i+0] = pu8Data[i+3];
			pu8Data[i+3] = u8Tmp;

			u8Tmp = pu8Data[i+1];
			pu8Data[i+1] = pu8Data[i+2];
			pu8Data[i+2] = u8Tmp;
		}
	}

	return ;
}



HI_S32	DRV_HDMI_SrmInit(HI_VOID)
{
	SRM_INFO_S *pstSrmInfo = &s_stSrmInfo;

	if(!pstSrmInfo->bInit)
	{
		HDMI_MEMSET(pstSrmInfo, 0 ,sizeof(SRM_INFO_S));
		pstSrmInfo->bInit 	= HI_TRUE;
		pstSrmInfo->bValid	= HI_FALSE;
	}

	return HI_SUCCESS;
}

HI_S32	DRV_HDMI_SrmDeinit(HI_VOID)
{
	SRM_INFO_S *pstSrmInfo = &s_stSrmInfo;

	SRM_INIT_CHK(pstSrmInfo);

	if(pstSrmInfo->pu8RawData)
	{
		HDMI_VFREE(pstSrmInfo->pu8RawData);
	}

	HDMI_MEMSET(pstSrmInfo, 0 ,sizeof(SRM_INFO_S));
	pstSrmInfo->bInit 	= HI_FALSE;
	pstSrmInfo->bValid	= HI_FALSE;

	return HI_SUCCESS;
}

HI_S32	DRV_HDMI_SrmSet(HI_U8 *pu8Data,HI_U32 u32Len,HI_BOOL bFromUser)
{
	HI_S32			s32Ret = HI_SUCCESS;
	HI_U32			i = 0;
	HI_U32			u32Tmp = 0;
	HI_U32			u32Length = 0;
	HI_U32			u32DevNum = 0;
	HI_U32			u32Offset = 0;
	HI_U8			au8HeadBuf[SRM_SIZE_HEADER] = {0};
	SRM_INFO_S		stSrmTmp;
	SRM_INFO_S 		*pstSrmTmp	= &stSrmTmp;
	SRM_INFO_S 		*pstSrmInfo = &s_stSrmInfo;

	SRM_INIT_CHK(pstSrmInfo);
	SRM_NULL_CHK(pu8Data);

	/* check raw data */
	if((0==u32Len) || (u32Len < SRM_SIZE_HEADER + SRM_SIZE_LLC_SIGNATURE) || (u32Len > SRM_SIZE_MAX_EXT_FORMAT))
	{
		HDMI_ERR("error u32Len=%u\n",u32Len);
		goto error_fail;
	}

	if (bFromUser)
	{
		s32Ret = copy_from_user(au8HeadBuf,pu8Data,sizeof(au8HeadBuf));
	}
	else
	{
		HDMI_MEMCPY(au8HeadBuf,pu8Data,sizeof(au8HeadBuf));
	}
	SrmToLittleEndian(au8HeadBuf, SRM_SIZE_HEADER);

	u32Tmp = *(HI_U32 *)(au8HeadBuf+0);
	pstSrmTmp->unHead1.bits.b04_SrmId			= u32Tmp >> 28;
	pstSrmTmp->unHead1.bits.b04_Hdcp2Indicator	= u32Tmp >> 24;
	pstSrmTmp->unHead1.bits.b08_Reserved		= u32Tmp >> 16;
	pstSrmTmp->unHead1.bits.b16_SrmVersion		= u32Tmp >> 0;

	u32Tmp = *(HI_U32 *)(au8HeadBuf+4);
	pstSrmTmp->unHead2.bits.b08_SrmGenerationNum= u32Tmp >> 24;
	pstSrmTmp->unHead2.bits.b24_Length			= u32Tmp >> 0;


	u32Tmp = *(HI_U32 *)(au8HeadBuf+8);
	pstSrmTmp->unRevocInfo.bits.b10_NumOfDevices= u32Tmp >> 22;
	pstSrmTmp->unRevocInfo.bits.b22_Reserved	= u32Tmp >> 0;

	/* check srm id */
	if(SRM_ID_SIGNIFIES != pstSrmTmp->unHead1.bits.b04_SrmId)
	{
		HDMI_ERR("error b04_SrmId=%u\n",pstSrmTmp->unHead1.bits.b04_SrmId);
		goto error_fail;
	}

	/* check data length valid */
	u32Length = pstSrmTmp->unHead2.bits.b24_Length;
	if( u32Length < (SRM_SIZE_LENGTH_G1 + sizeof(SRM_REVOC_INFO_UN) + SRM_SIZE_LLC_SIGNATURE)
		|| (u32Length - SRM_SIZE_LENGTH_G1 - sizeof(SRM_REVOC_INFO_UN) - SRM_SIZE_LLC_SIGNATURE) % SRM_SIZE_DEV_ID != 0 )
	{
		HDMI_ERR("error u32Length=%u\n",u32Length);
		goto error_fail;
	}

	/* check data device number valid */
	u32DevNum = pstSrmTmp->unRevocInfo.bits.b10_NumOfDevices;
	if( u32Length != (SRM_SIZE_LENGTH_G1 + sizeof(SRM_REVOC_INFO_UN) + u32DevNum * SRM_SIZE_DEV_ID + SRM_SIZE_LLC_SIGNATURE) )
	{
		HDMI_ERR("error u32DevNum=%u\n",u32DevNum);
		goto error_fail;
	}

	/* local memory data & reset 0 */
	if(pstSrmInfo->pu8RawData)
	{
		HDMI_VFREE(pstSrmInfo->pu8RawData);
	}
	HDMI_MEMSET(pstSrmInfo, 0 ,sizeof(SRM_INFO_S));
	pstSrmInfo->bInit 		= HI_TRUE;
	pstSrmInfo->pu8RawData 	= (HI_U8 *)HDMI_VMALLOC(u32Len);
	SRM_NULL_CHK(pstSrmInfo->pu8RawData);
	if (bFromUser)
	{
		s32Ret = copy_from_user(pstSrmInfo->pu8RawData,pu8Data,u32Len);
	}
	else
	{
		HDMI_MEMCPY(pstSrmInfo->pu8RawData,pu8Data,u32Len);
	}
	/* data parse, 1st-generation format  */
	u32Offset = 0;
	pstSrmInfo->unHead1.u32Data = pstSrmTmp->unHead1.u32Data;
	u32Offset += sizeof(SRM_HEADER_1_UN);
	pstSrmInfo->unHead2.u32Data = pstSrmTmp->unHead2.u32Data;
	u32Offset += sizeof(SRM_HEADER_2_UN);
	pstSrmInfo->unRevocInfo.u32Data = pstSrmTmp->unRevocInfo.u32Data;
	u32Offset += sizeof(SRM_REVOC_INFO_UN );

	pstSrmInfo->pu8HeadDeviceIds = (HI_U8 *)(pstSrmInfo->pu8RawData + u32Offset);
	u32Offset += u32DevNum*SRM_SIZE_DEV_ID;
	pstSrmInfo->pu8HeadLlcSignature = (HI_U8 *)(pstSrmInfo->pu8RawData + u32Offset);
	u32Offset += SRM_SIZE_LLC_SIGNATURE;

	/* Next-generation extension format  */
	for(i=0;
		(i<pstSrmInfo->unHead2.bits.b08_SrmGenerationNum)
		&& (i<SRM_MAX_EXT_FORMAT_NUM)
		&& (u32Len > u32Offset);
		i++)
	{
		u32Tmp = *(HI_U32 *)(pstSrmInfo->pu8RawData + u32Offset);
		u32Offset += sizeof(SRM_EXTENSION_1_UN);
		SrmToLittleEndian((HI_U8 *)&u32Tmp,sizeof(SRM_EXTENSION_1_UN));
		pstSrmInfo->stExtFmt[i].unExt1.bits.b16_Length 		 	= u32Tmp >> 16;
		pstSrmInfo->stExtFmt[i].unExt1.bits.b06_Reserved 		= u32Tmp >> 6;
		pstSrmInfo->stExtFmt[i].unExt1.bits.b10_NumOfDevices 	= u32Tmp >> 0;

		/* check data length & device number valid */
		u32Length = pstSrmInfo->stExtFmt[i].unExt1.bits.b16_Length;
		u32DevNum = pstSrmInfo->stExtFmt[i].unExt1.bits.b10_NumOfDevices;
		if( u32Length != (SRM_SIZE_LENGTH_GNEXT + u32DevNum * SRM_SIZE_DEV_ID + SRM_SIZE_LLC_SIGNATURE)
			|| ((u32Length - SRM_SIZE_LENGTH_GNEXT - SRM_SIZE_LLC_SIGNATURE) % SRM_SIZE_DEV_ID) != 0)
		{
			HDMI_ERR("error u32Length=%u,u32DevNum=%u\n",u32Length,u32DevNum);
			goto error_fail;
		}

		pstSrmInfo->stExtFmt[i].pu8ExtDeviceIds = (HI_U8 *)(pstSrmInfo->pu8RawData + u32Offset);
		pstSrmInfo->stExtFmt[i].pu8ExtDeviceIds = (HI_U8 *)(pstSrmInfo->pu8RawData + u32Offset);
		u32Offset += u32DevNum*SRM_SIZE_DEV_ID;
		pstSrmInfo->stExtFmt[i].pu8ExtLlcSignature = (HI_U8 *)(pstSrmInfo->pu8RawData + u32Offset);
		u32Offset += SRM_SIZE_LLC_SIGNATURE;
	}

	pstSrmInfo->bValid = HI_TRUE;

	HDMI_INFO("set srm succuss.\n");

	return HI_SUCCESS;

error_fail:
	if(pstSrmInfo->pu8RawData)
	{
		HDMI_VFREE(pstSrmInfo->pu8RawData);
	}
	HDMI_MEMSET(pstSrmInfo, 0 ,sizeof(SRM_INFO_S));
	pstSrmInfo->bInit 	= HI_TRUE;
	pstSrmInfo->bValid	= HI_FALSE;
	HDMI_INFO("set srm fail.\n");

	return HI_FAILURE;

}

HI_S32	DRV_HDMI_SrmCheck(HI_U8 *pu8ChkList,HI_U32 u32DevIdNum)
{
	HI_U32			i = 0,j = 0;
	HI_U32			u32SrmRevocIdNum = 0;
	SRM_DEV_ID_S	*pstSrmRevocId = HI_NULL;
	SRM_DEV_ID_S	*pstChkList = (SRM_DEV_ID_S *)pu8ChkList;
	SRM_INFO_S 		*pstSrmInfo = &s_stSrmInfo;

	SRM_INIT_CHK(pstSrmInfo);
	if(!pu8ChkList)
	{
        HDMI_WARN("null pointer!\n");
        return HI_SUCCESS;
    }

	if(!pstSrmInfo->bValid)
	{
		return HI_SUCCESS;
	}

	for(;u32DevIdNum && pstChkList ; u32DevIdNum--,pstChkList++)
	{
		/*  System Renewability Message (1st-generation) Format  */
		for(i = 0 ,u32SrmRevocIdNum = pstSrmInfo->unRevocInfo.bits.b10_NumOfDevices,
			pstSrmRevocId = (SRM_DEV_ID_S *)pstSrmInfo->pu8HeadDeviceIds;
			pstSrmRevocId && (i < u32SrmRevocIdNum );
			i++,pstSrmRevocId++)
		{
			if(!HDMI_MEMCMP(pstSrmRevocId,pstChkList,sizeof(SRM_DEV_ID_S)))
			{
				HDMI_ERR("revocation ID!\n");
				return HI_FAILURE;
			}
		}

		/* Next-generation extension format  */
		for(j = 0,u32SrmRevocIdNum = pstSrmInfo->stExtFmt[0].unExt1.bits.b10_NumOfDevices;
			u32SrmRevocIdNum && (j < SRM_MAX_EXT_FORMAT_NUM);
			j++,u32SrmRevocIdNum = pstSrmInfo->stExtFmt[j].unExt1.bits.b10_NumOfDevices)
		{
			for(i = 0 ,pstSrmRevocId = (SRM_DEV_ID_S *)pstSrmInfo->stExtFmt[j].pu8ExtDeviceIds;
				pstSrmRevocId && (i < u32SrmRevocIdNum );
				i++,pstSrmRevocId++)
			{
				if(!HDMI_MEMCMP(pstSrmRevocId,pstChkList,sizeof(SRM_DEV_ID_S)))
				{
					HDMI_ERR("revocation ID!\n");
					return HI_FAILURE;
				}
			}
		}
	}

	return HI_SUCCESS;

}

HI_S32	DRV_HDMI_SrmGet(SRM_INFO_S **ppstSrmInfo)
{

	SRM_NULL_CHK(ppstSrmInfo);

	*ppstSrmInfo = &s_stSrmInfo;

	return HI_SUCCESS;
}



