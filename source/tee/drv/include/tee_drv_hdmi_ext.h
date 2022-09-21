/******************************************************************************

  Copyright (C), 2016-2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : tee_drv_hdmi_ext.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2016-11-07
  Description   :
  History       :
  1.Date        : 2016-11-07
    Author      : sdk
    Modification: Created file

*******************************************************************************/
#ifndef _TEE_DRV_HDMI_EXT_H__
#define _TEE_DRV_HDMI_EXT_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cpluscplus */

#include "hi_type.h"

/**HDMI interface ID *//**CNcomment:HDMI 接口ID*/
typedef enum hiDRV_HDMI_ID_E
{
    TEE_DRV_HDMI_ID_0,                        /**< HDMI device id 0 */
    TEE_DRV_HDMI_ID_BUTT,
}TEE_DRV_HDMI_ID_E;

/**Monitoring strategy *//**CNcomment:Monitor监控策略 */
typedef enum hiTEE_HDMI_HDCP_LEVEL_E
{
    TEE_DRV_HDMI_HDCP_LEVEL_NONE = 0,        /**< no hdcp require */
    TEE_DRV_HDMI_HDCP_LEVEL_1,               /**< hdcp level 1 (hdcp1.4 or hdcp2.2) */
    TEE_DRV_HDMI_HDCP_LEVEL_2,               /**< hdcp level 2 (only hdcp2.2) */
    TEE_DRV_HDMI_HDCP_LEVEL_BUTT
}TEE_DRV_HDMI_HDCP_LEVEL_E;

/**HDMI HDCP status *//**CNcomment:HDMI HDCP状态 */
typedef enum hiTEE_DRV_HDMI_HDCP_STATUS_E
{
    TEE_DRV_HDMI_HDCP_NONE = 0,  	 /**<no hdcp is working     */
    TEE_DRV_HDMI_HDCP_14_SUCC,        /**<hdcp1.4 auth success 	*/
	TEE_DRV_HDMI_HDCP_14_FAIL,        /**<hdcp1.4 auth fail 	 	*/
    TEE_DRV_HDMI_HDCP_22_SUCC,        /**<hdcp2.2 auth success	*/
	TEE_DRV_HDMI_HDCP_22_FAIL,        /**<hdcp2.2 auth fail		*/
    TEE_DRV_HDMI_HDCP_BUTT
} TEE_DRV_HDMI_HDCP_STATUS_E;


/**HDCP stream type *//**CNcomment:码流保护类型 */
typedef enum hiTEE_DRV_HDMI_HDCP_STREAM_TYPE_E
{
    TEE_DRV_HDMI_HDCP_STREAM_TYPE_0 = 0,        /**< Type 0 Content Stream. May be transmitted by the HDCP Repeater to all HDCP Devices. */
    TEE_DRV_HDMI_HDCP_STREAM_TYPE_1,            /**< Type 1 Content Stream(Default value). Must not be transmitte by the HDCP Repeater to HDCP 1.x-complian Devices and HDCP 2.0-compliant Repeaters */
    TEE_DRV_HDMI_HDCP_STREAM_TYPE_BUTT,
}TEE_DRV_HDMI_HDCP_STREAM_TYPE_E;

/**
\brief set hdcp stream type. CNcomment：设置HDCP码流保护类型
\param[in]  enHdmi        hdmi channel id.
\param[in]  enStreamType  see TEE_DRV_HDMI_HDCP_STREAM_TYPE_E.
\retval     HI_SUCCESS    success.
*/
HI_S32 TEE_DRV_HDMI_SetHDCPStreamType(TEE_DRV_HDMI_ID_E enHdmi, TEE_DRV_HDMI_HDCP_STREAM_TYPE_E enStreamType);
/**
\brief set hdcp stratagey. CNcomment：设置HDCP策略
\param[in]  enHdmi        hdmi channel id.
\param[in]  enHdcpLevel   hdcp level, hdcp2.2 only or hdcpx or non-hdcp.
\retval     HI_SUCCESS    success.
*/
HI_S32 TEE_DRV_HDMI_SetHDCPStrategy(TEE_DRV_HDMI_ID_E enHdmi, TEE_DRV_HDMI_HDCP_LEVEL_E enHdcpLevel);

/**
\brief get current hdcp stratagey. CNcomment：获取当前HDCP策略
\param[in]  enHdmi         hdmi channel id.
\param[in]  penHdcpLevel   current hdcp level, hdcp2.2 only or hdcpx or non-hdcp.
\retval     HI_SUCCESS     success.
*/
HI_S32 TEE_DRV_HDMI_GetHDCPStrategy(TEE_DRV_HDMI_ID_E enHdmi, TEE_DRV_HDMI_HDCP_LEVEL_E *penHdcpLevel);

/**
\brief get current hdcp status. CNcomment：获取当前HDCP认证状态
\param[in]  enHdmi         hdmi channel id.
\param[in]  penHdcpLevel   current hdcp auth status
\retval     HI_SUCCESS     success.
*/
HI_S32 TEE_DRV_HDMI_GetHDCPStatus(TEE_DRV_HDMI_ID_E enHdmi, TEE_DRV_HDMI_HDCP_STATUS_E *penHdcpStatus);

/**
\brief set downscale. CNcomment：设置监控分辨率
\param[in]  enHdmi         hdmi channel id.
\param[in]  u32DownScalWidth   downscale width
\param[in]  u32DownScalHeight  downscale height
\retval     HI_SUCCESS     success.
*/
HI_S32 TEE_DRV_HDMI_SetDownScal(TEE_DRV_HDMI_ID_E enHdmi, HI_U32 u32DownScalWidth, HI_U32 u32DownScalHeight);

#ifdef __cplusplus
}
#endif /* __cpluscplus */


#endif
