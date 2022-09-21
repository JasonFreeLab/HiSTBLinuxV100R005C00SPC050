#ifndef __DRV_VDP_NXG__
#define __DRV_VDP_NXG__

#include "vdp_hal_ip_nxg.h"


typedef struct hiDRV_NEXGUARD_PARAM_S
{
    HI_BOOL  bEnable;                /**<Enable watermark or not */
    HI_U32 u32Key;                  /**<If use reg key, config here; if use OTP key, don't care. */
    HI_U32 u32SubscriberID;         /**<If use reg SubscriberID, config here; if use OTP SubscriberID, don't care. */
    HI_U8 u8OperatorID;             /**<If use reg peratorID, config here; if use OTP peratorID, don't care. */
}DRV_NEXGUARD_PARAM_S;
typedef enum hiDRV_NEXGUARD_SETTING_TYPE_E
{
    DRV_NEXGUARD_SETTING_8bit = 0,        /**<8bit setting*/
    DRV_NEXGUARD_SETTING_10bit,          /**<10bit setting*/
    DRV_NEXGUARD_SETTING_HDR,            /**<HDR setting*/
    DRV_NEXGUARD_SETTING_CERTIFICATE,    /**<Certificate setting*/
    DRV_NEXGUARD_SETTING_BUTT
}DRV_NEXGUARD_SETTING_TYPE_E;

typedef struct hiDRV_VDP_NEXGUARD_ATTR_S
{
    HI_U32 u32ServiceId;            /**<Service ID */
    HI_U8 u8Setting[DRV_NEXGUARD_SETTING_BUTT][21];            /**<Hardware setting data, only for nexguard. */
}DRV_VDP_NEXGUARD_ATTR_S;



typedef struct hiDRV_NEXGUARD_CFG_S
{
    HI_BOOL bNxgValid;
    HI_BOOL bEnable;
    HI_U8  u8SetArray[DRV_NEXGUARD_SETTING_BUTT][21];
}DRV_NEXGUARD_CFG_S;


HI_VOID NG_Reset(HI_VOID);                                   /* to perform a software reset of the WM IP core */
HI_VOID NG_EnableIn(HI_BOOL enableIn);                    /*   1-bit, globally enables/disables watermarking */
HI_VOID NG_DebugEnableIn(HI_BOOL debugEnableIn);          /*   1-bit, visible test pattern enable/disable */
HI_VOID NG_SetKeyInSeed(HI_U32 keyInSeed);       /*  32-bit 每 KeyIn */



HI_VOID NG_SetOperatorId(HI_U8 operatorId);    /*   8-bit 每 Payload[55:48] */
HI_VOID NG_SetSubscriberId(HI_U32 subScriberId); /*  32-bit 每 Payload[47:16] */
HI_VOID NG_SetTimeCode(HI_U16 timeCode);   /*  16-bit 每 Payload[15:0]  */


HI_VOID NXG_HW_SetParameters(HI_BOOL bEnable);
#endif

