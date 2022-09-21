/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : oam_event.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年10月9日
  最近修改   :
  功能描述   : 可维可测-事件上报功能
  函数列表   :
  修改历史   :
  1.日    期   : 2012年10月9日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if ((_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION) || (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION))
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "oam_event.h"
#include "oam_main.h"
#include "oam_ext_if.h"


#undef THIS_FILE_ID
#define THIS_FILE_ID   OAM_FILE_ID_OAM_EVENT_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : oam_report_data_get_global_switch
 功能描述  : 获取收发数据帧的总开关，如果总开关不开，则不用进入上报逻辑判断
             某一个用户的上报开关是否打开，不用消耗mips。只要有一个用户的开
             关打开了总开关就打开
 输入参数  : en_direction:方向，发送还是接收  0 发送  1接收
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_switch_enum_uint8  oam_report_data_get_global_switch(oam_ota_frame_direction_type_enum_uint8 en_direction)
{
    if (OAL_UNLIKELY(OAM_OTA_FRAME_DIRECTION_TYPE_BUTT <= en_direction))
    {
        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }

    return g_st_oam_mng_ctx.st_user_track_ctx.aen_data_global_switch[en_direction];
}

/*****************************************************************************
 函 数 名  : oam_report_data_set_global_switch
 功能描述  : 设置上报数据帧的全局开关，只要有一个用户要上报，则总开关就为开
             ，否则关闭，防止消耗mips
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  oam_report_data_set_global_switch(
                                        oam_ota_frame_direction_type_enum_uint8 en_direction)
{
    oal_uint16          us_usr_idx;
    oal_switch_enum_uint8 en_mcast_switch = OAL_SWITCH_OFF;
    oal_switch_enum_uint8 en_ucast_switch = OAL_SWITCH_OFF;

    if (OAL_UNLIKELY(OAM_OTA_FRAME_DIRECTION_TYPE_BUTT <= en_direction))
    {
        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }

    /* 先检查单播数据帧是否有用户已经打开了 */
    for (us_usr_idx = 0; us_usr_idx < (WLAN_ACTIVE_USER_MAX_NUM + WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE) * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC; us_usr_idx++)
    {
        if ((OAL_SWITCH_ON == g_st_oam_mng_ctx.st_user_track_ctx.ast_80211_ucast_data_ctx[en_direction].en_frame_cb_switch)
            || (OAL_SWITCH_ON == g_st_oam_mng_ctx.st_user_track_ctx.ast_80211_ucast_data_ctx[en_direction].en_frame_content_switch)
            || (OAL_SWITCH_ON == g_st_oam_mng_ctx.st_user_track_ctx.ast_80211_ucast_data_ctx[en_direction].en_frame_dscr_switch))
        {
            en_ucast_switch = OAL_SWITCH_ON;
            break;
        }
    }

    /* 再检查组播数据帧是否开关打开了 */
    if ((OAL_SWITCH_ON == g_st_oam_mng_ctx.st_user_track_ctx.ast_80211_mcast_data_ctx[en_direction].en_frame_cb_switch)
        || (OAL_SWITCH_ON == g_st_oam_mng_ctx.st_user_track_ctx.ast_80211_mcast_data_ctx[en_direction].en_frame_content_switch)
        || (OAL_SWITCH_ON == g_st_oam_mng_ctx.st_user_track_ctx.ast_80211_mcast_data_ctx[en_direction].en_frame_dscr_switch))
    {
        en_mcast_switch = OAL_SWITCH_ON;
    }

    g_st_oam_mng_ctx.st_user_track_ctx.aen_data_global_switch[en_direction] = (en_ucast_switch | en_mcast_switch);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_report_eth_frame_set_switch
 功能描述  : 设置上报以太网帧的开关
 输入参数  : us_user_idx:用户资源池id
             en_switch  :打开还是关闭
             en_eth_direction:发送还是接收方向
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 oam_report_eth_frame_set_switch(oal_uint16               us_user_idx,
                                                   oal_switch_enum_uint8    en_switch,
                                       oam_ota_frame_direction_type_enum_uint8 en_eth_direction)
{
    if (us_user_idx >= (WLAN_ACTIVE_USER_MAX_NUM + WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE) * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC)
    {
        OAL_IO_PRINT("oam_report_eth_frame_set_switch::user_idx exceeds!\n");
        return OAL_ERR_CODE_OAM_EVT_USER_IDX_EXCEED;
    }

    if (en_eth_direction >= OAM_OTA_FRAME_DIRECTION_TYPE_BUTT)
    {
        OAL_IO_PRINT("oam_report_eth_frame_set_switch::eth_direction exceeds!\n");
        return OAL_ERR_CODE_OAM_EVT_FRAME_DIR_INVALID;
    }

    g_st_oam_mng_ctx.st_user_track_ctx.aen_eth_data_ctx[en_eth_direction] = en_switch;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_report_eth_frame_get_switch
 功能描述  : 获取上报以太网帧的开关
 输入参数  : us_user_idx:用户资源池id
             en_eth_direction:发送还是接收
             pen_eth_switch:以太网帧打印开关
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_report_eth_frame_get_switch(
                                 oal_uint16             us_user_idx,
                                 oam_ota_frame_direction_type_enum_uint8 en_eth_direction,
                                 oal_switch_enum_uint8  *pen_eth_switch)
{
    if (us_user_idx >= WLAN_ACTIVE_USER_MAX_NUM * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC + WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC)
    {
        return OAL_ERR_CODE_OAM_EVT_USER_IDX_EXCEED;
    }

    if (en_eth_direction >= OAM_OTA_FRAME_DIRECTION_TYPE_BUTT)
    {
        return OAL_ERR_CODE_OAM_EVT_FRAME_DIR_INVALID;
    }

    if (OAL_PTR_NULL == pen_eth_switch)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    *pen_eth_switch = g_st_oam_mng_ctx.st_user_track_ctx.aen_eth_data_ctx[en_eth_direction];

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_report_80211_mcast_set_switch
 功能描述  : 设置上报80211组播\广播数据或者管理帧的开关
 输入参数  : en_mcast_direction:帧是发送还是接收
             en_frame_type     :数据帧还是管理帧(包含控制帧)
             en_frame_switch  :帧开关
             en_cb_switch     :CB开关
             en_dscr_switch   :描述符开关
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_report_80211_mcast_set_switch(
                                        oam_ota_frame_direction_type_enum_uint8 en_mcast_direction,
                                        oam_user_track_frame_type_enum_uint8    en_frame_type,
                                        oal_switch_enum_uint8                   en_frame_switch,
                                        oal_switch_enum_uint8                   en_cb_switch,
                                        oal_switch_enum_uint8                   en_dscr_switch)
{
    if (en_mcast_direction >= OAM_OTA_FRAME_DIRECTION_TYPE_BUTT)
    {
        return OAL_ERR_CODE_OAM_EVT_FRAME_DIR_INVALID;
    }

    if (en_frame_type >= OAM_USER_TRACK_FRAME_TYPE_BUTT)
    {
        return OAL_ERR_CODE_CONFIG_UNSUPPORT;
    }

    if (OAL_UNLIKELY(en_frame_switch >= OAL_SWITCH_BUTT)
        || OAL_UNLIKELY(en_cb_switch >= OAL_SWITCH_BUTT)
        || OAL_UNLIKELY(en_dscr_switch >= OAL_SWITCH_BUTT))
    {
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    /* 为组播管理帧设置开关 */
    if (OAM_USER_TRACK_FRAME_TYPE_MGMT == en_frame_type)
    {
        g_st_oam_mng_ctx.st_user_track_ctx.ast_80211_mcast_mgmt_ctx[en_mcast_direction].en_frame_content_switch = en_frame_switch;
        g_st_oam_mng_ctx.st_user_track_ctx.ast_80211_mcast_mgmt_ctx[en_mcast_direction].en_frame_cb_switch = en_cb_switch;
        g_st_oam_mng_ctx.st_user_track_ctx.ast_80211_mcast_mgmt_ctx[en_mcast_direction].en_frame_dscr_switch = en_dscr_switch;
    }
    else
    {
        g_st_oam_mng_ctx.st_user_track_ctx.ast_80211_mcast_data_ctx[en_mcast_direction].en_frame_content_switch = en_frame_switch;
        g_st_oam_mng_ctx.st_user_track_ctx.ast_80211_mcast_data_ctx[en_mcast_direction].en_frame_cb_switch = en_cb_switch;
        g_st_oam_mng_ctx.st_user_track_ctx.ast_80211_mcast_data_ctx[en_mcast_direction].en_frame_dscr_switch = en_dscr_switch;

        /* 设置总开关 */
        oam_report_data_set_global_switch(en_mcast_direction);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_report_80211_mcast_get_switch
 功能描述  : 获取上报80211组播帧的开关
 输入参数  : en_mcast_direction:帧是发送还是接收
             en_frame_type     :数据帧还是管理帧(包含控制帧)
             pen_frame_switch  :帧开关
             pen_cb_switch     :CB开关
             pen_dscr_switch   :描述符开关
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_report_80211_mcast_get_switch(
                                        oam_ota_frame_direction_type_enum_uint8 en_mcast_direction,
                                        oam_user_track_frame_type_enum_uint8    en_frame_type,
                                        oal_switch_enum_uint8                  *pen_frame_switch,
                                        oal_switch_enum_uint8                  *pen_cb_switch,
                                        oal_switch_enum_uint8                  *pen_dscr_switch)
{
    if (en_mcast_direction >= OAM_OTA_FRAME_DIRECTION_TYPE_BUTT)
    {
        return OAL_ERR_CODE_OAM_EVT_FRAME_DIR_INVALID;
    }

    if (en_frame_type >= OAM_USER_TRACK_FRAME_TYPE_BUTT)
    {
        return OAL_ERR_CODE_CONFIG_UNSUPPORT;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == pen_frame_switch)
        || OAL_UNLIKELY(OAL_PTR_NULL == pen_cb_switch)
        || OAL_UNLIKELY(OAL_PTR_NULL == pen_dscr_switch))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAM_USER_TRACK_FRAME_TYPE_MGMT == en_frame_type)
    {
        *pen_frame_switch = g_st_oam_mng_ctx.st_user_track_ctx.ast_80211_mcast_mgmt_ctx[en_mcast_direction].en_frame_content_switch;
        *pen_cb_switch    = g_st_oam_mng_ctx.st_user_track_ctx.ast_80211_mcast_mgmt_ctx[en_mcast_direction].en_frame_cb_switch;
        *pen_dscr_switch  = g_st_oam_mng_ctx.st_user_track_ctx.ast_80211_mcast_mgmt_ctx[en_mcast_direction].en_frame_dscr_switch;
    }
    else
    {
        *pen_frame_switch = g_st_oam_mng_ctx.st_user_track_ctx.ast_80211_mcast_data_ctx[en_mcast_direction].en_frame_content_switch;
        *pen_cb_switch    = g_st_oam_mng_ctx.st_user_track_ctx.ast_80211_mcast_data_ctx[en_mcast_direction].en_frame_cb_switch;
        *pen_dscr_switch  = g_st_oam_mng_ctx.st_user_track_ctx.ast_80211_mcast_data_ctx[en_mcast_direction].en_frame_dscr_switch;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_report_80211_ucast_set_switch
 功能描述  : 设置80211单播帧上报的开关
 输入参数  : en_ucast_direction:帧是发送还是接收
             en_frame_type     :数据帧还是管理帧(包含控制帧)
             en_frame_switch  :帧开关
             en_cb_switch     :CB开关
             en_dscr_switch   :描述符开关
             us_user_idx       :用户资源池id
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_report_80211_ucast_set_switch(
                                        oam_ota_frame_direction_type_enum_uint8 en_ucast_direction,
                                        oam_user_track_frame_type_enum_uint8    en_frame_type,
                                        oal_switch_enum_uint8                   en_frame_switch,
                                        oal_switch_enum_uint8                   en_cb_switch,
                                        oal_switch_enum_uint8                   en_dscr_switch,
                                        oal_uint16                              us_user_idx)
{
#if 0
    oal_uint8   uc_vapid_loop;
#endif
    if (en_ucast_direction >= OAM_OTA_FRAME_DIRECTION_TYPE_BUTT)
    {
        return OAL_ERR_CODE_OAM_EVT_FRAME_DIR_INVALID;
    }

    if (en_frame_type >= OAM_USER_TRACK_FRAME_TYPE_BUTT)
    {
        return OAL_ERR_CODE_CONFIG_UNSUPPORT;
    }

    if (us_user_idx >= (WLAN_ACTIVE_USER_MAX_NUM + WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE) * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC)
    {
        return OAL_ERR_CODE_OAM_EVT_USER_IDX_EXCEED;
    }

    if (OAL_UNLIKELY(en_frame_switch >= OAL_SWITCH_BUTT)
        || OAL_UNLIKELY(en_cb_switch >= OAL_SWITCH_BUTT)
        || OAL_UNLIKELY(en_dscr_switch  >= OAL_SWITCH_BUTT))
    {
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    if (OAM_USER_TRACK_FRAME_TYPE_MGMT == en_frame_type)
    {
        g_st_oam_mng_ctx.st_user_track_ctx.ast_80211_ucast_mgmt_ctx[en_ucast_direction].en_frame_content_switch = en_frame_switch;
        g_st_oam_mng_ctx.st_user_track_ctx.ast_80211_ucast_mgmt_ctx[en_ucast_direction].en_frame_cb_switch = en_cb_switch;
        g_st_oam_mng_ctx.st_user_track_ctx.ast_80211_ucast_mgmt_ctx[en_ucast_direction].en_frame_dscr_switch = en_dscr_switch;
    }
    else
    {
        g_st_oam_mng_ctx.st_user_track_ctx.ast_80211_ucast_data_ctx[en_ucast_direction].en_frame_content_switch = en_frame_switch;
        g_st_oam_mng_ctx.st_user_track_ctx.ast_80211_ucast_data_ctx[en_ucast_direction].en_frame_cb_switch = en_cb_switch;
        g_st_oam_mng_ctx.st_user_track_ctx.ast_80211_ucast_data_ctx[en_ucast_direction].en_frame_dscr_switch = en_dscr_switch;

        /* 设置总开关 */
        oam_report_data_set_global_switch(en_ucast_direction);
    }
#if 0
    /* 描述符开关 */
    for (uc_vapid_loop = 0; uc_vapid_loop < WLAN_VAP_SUPPORT_MAX_NUM_LIMIT; uc_vapid_loop++)
    {
        // sdt 工具侧发送命令方向为0
        oam_ota_set_switch(uc_vapid_loop, en_dscr_switch, (oam_ota_type_enum_uint8)abs(en_ucast_direction - 1));
    }
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_report_80211_ucast_get_switch
 功能描述  : 获取80211单播帧的上报开关
 输入参数  : en_ucast_direction:帧是发送还是接收
             en_frame_type     :数据帧还是管理帧(包含控制帧)
             pen_frame_switch  :帧开关
             pen_cb_switch     :CB开关
             pen_dscr_switch   :描述符开关
             us_user_idx       :用户资源池id
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_report_80211_ucast_get_switch(
                                        oam_ota_frame_direction_type_enum_uint8 en_ucast_direction,
                                        oam_user_track_frame_type_enum_uint8    en_frame_type,
                                        oal_switch_enum_uint8                  *pen_frame_switch,
                                        oal_switch_enum_uint8                  *pen_cb_switch,
                                        oal_switch_enum_uint8                  *pen_dscr_switch,
                                        oal_uint16                              us_user_idx)
{
    if (en_ucast_direction >= OAM_OTA_FRAME_DIRECTION_TYPE_BUTT)
    {
        return OAL_ERR_CODE_OAM_EVT_FRAME_DIR_INVALID;
    }

    if (en_frame_type >= OAM_USER_TRACK_FRAME_TYPE_BUTT)
    {
        return OAL_ERR_CODE_CONFIG_UNSUPPORT;
    }

    if (us_user_idx >= WLAN_ACTIVE_USER_MAX_NUM * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC+ WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC)
    {
        return OAL_ERR_CODE_OAM_EVT_USER_IDX_EXCEED;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == pen_frame_switch)
        || OAL_UNLIKELY(OAL_PTR_NULL == pen_cb_switch)
        || OAL_UNLIKELY(OAL_PTR_NULL == pen_dscr_switch))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAM_USER_TRACK_FRAME_TYPE_MGMT == en_frame_type)
    {
        *pen_frame_switch = g_st_oam_mng_ctx.st_user_track_ctx.ast_80211_ucast_mgmt_ctx[en_ucast_direction].en_frame_content_switch;
        *pen_cb_switch    = g_st_oam_mng_ctx.st_user_track_ctx.ast_80211_ucast_mgmt_ctx[en_ucast_direction].en_frame_cb_switch;
        *pen_dscr_switch  = g_st_oam_mng_ctx.st_user_track_ctx.ast_80211_ucast_mgmt_ctx[en_ucast_direction].en_frame_dscr_switch;
    }
    else
    {
        *pen_frame_switch = g_st_oam_mng_ctx.st_user_track_ctx.ast_80211_ucast_data_ctx[en_ucast_direction].en_frame_content_switch;
        *pen_cb_switch    = g_st_oam_mng_ctx.st_user_track_ctx.ast_80211_ucast_data_ctx[en_ucast_direction].en_frame_cb_switch;
        *pen_dscr_switch  = g_st_oam_mng_ctx.st_user_track_ctx.ast_80211_ucast_data_ctx[en_ucast_direction].en_frame_dscr_switch;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_report_80211_probe_set_switch
 功能描述  : 设置probe request 和 probe response的打印开关
 输入参数  : en_ucast_direction:帧是发送还是接收
             en_frame_switch  :帧开关
             en_cb_switch     :CB开关
             en_dscr_switch   :描述符开关
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月30日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_report_80211_probe_set_switch(
                                        oam_ota_frame_direction_type_enum_uint8 en_probe_direction,
                                        oal_switch_enum_uint8                   en_frame_switch,
                                        oal_switch_enum_uint8                   en_cb_switch,
                                        oal_switch_enum_uint8                   en_dscr_switch)
{
    if (en_probe_direction >= OAM_OTA_FRAME_DIRECTION_TYPE_BUTT)
    {
        return OAL_ERR_CODE_OAM_EVT_FRAME_DIR_INVALID;
    }

    if (OAL_UNLIKELY(en_frame_switch >= OAL_SWITCH_BUTT)
        || OAL_UNLIKELY(en_cb_switch >= OAL_SWITCH_BUTT)
        || OAL_UNLIKELY(en_dscr_switch >= OAL_SWITCH_BUTT))
    {
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    g_st_oam_mng_ctx.st_user_track_ctx.aen_80211_probe_switch[en_probe_direction].en_frame_content_switch = en_frame_switch;
    g_st_oam_mng_ctx.st_user_track_ctx.aen_80211_probe_switch[en_probe_direction].en_frame_cb_switch = en_cb_switch;
    g_st_oam_mng_ctx.st_user_track_ctx.aen_80211_probe_switch[en_probe_direction].en_frame_dscr_switch = en_dscr_switch;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_report_80211_probereq_get_switch
 功能描述  : 获取prebe request和probe response的打印开关
 输入参数  : en_ucast_direction:帧是发送还是接收
             pen_frame_switch  :帧开关
             pen_cb_switch     :CB开关
             pen_dscr_switch   :描述符开关
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月30日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_report_80211_probe_get_switch(
                                        oam_ota_frame_direction_type_enum_uint8 en_probe_direction,
                                        oal_switch_enum_uint8                  *pen_frame_switch,
                                        oal_switch_enum_uint8                  *pen_cb_switch,
                                        oal_switch_enum_uint8                  *pen_dscr_switch)
{
    if (en_probe_direction >= OAM_OTA_FRAME_DIRECTION_TYPE_BUTT)
    {
        return OAL_ERR_CODE_OAM_EVT_FRAME_DIR_INVALID;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == pen_frame_switch)
        || OAL_UNLIKELY(OAL_PTR_NULL == pen_cb_switch)
        || OAL_UNLIKELY(OAL_PTR_NULL == pen_dscr_switch))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    *pen_frame_switch = g_st_oam_mng_ctx.st_user_track_ctx.aen_80211_probe_switch[en_probe_direction].en_frame_content_switch;
    *pen_cb_switch    = g_st_oam_mng_ctx.st_user_track_ctx.aen_80211_probe_switch[en_probe_direction].en_frame_cb_switch;
    *pen_dscr_switch  = g_st_oam_mng_ctx.st_user_track_ctx.aen_80211_probe_switch[en_probe_direction].en_frame_dscr_switch;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_report_dhcp_arp_set_switch
 功能描述  : 设置广播的dhcp和arp的上报开关
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_report_dhcp_arp_set_switch(oal_switch_enum_uint8 en_switch)
{
    g_st_oam_mng_ctx.st_user_track_ctx.en_tx_mcast_dhcp_arp_switch = en_switch;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_report_dhcp_arp_get_switch
 功能描述  : 获取上报广播dhcp和arp的开关
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_switch_enum_uint8  oam_report_dhcp_arp_get_switch(oal_void)
{
    return g_st_oam_mng_ctx.st_user_track_ctx.en_tx_mcast_dhcp_arp_switch;
}
#if 0
/*****************************************************************************
 函 数 名  : oam_report_get_switch
 功能描述  : 获取某种要上报的内容(帧，描述符)开关是否打开
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_switch_enum_uint8 oam_report_get_switch(oam_ota_type_enum_uint8 en_type)
{
    if (en_type >= OAM_OTA_TYPE_BUTT)
    {
        return OAL_SWITCH_OFF;
    }

    return g_st_oam_mng_ctx.ast_ota_ctx[0].aen_ota_switch[en_type];
}
#endif
/*****************************************************************************
 函 数 名  : oam_event_get_switch
 功能描述  : 获取EVENT模块的总开关
 输入参数  : uc_vap_id       : 当前处理的VAP ID
 输出参数  : pen_switch_type : ALARM模块的开关状态
 返 回 值  : 1) OAL_ERR_CODE_PTR_NULL: 空指针
             2) OAL_SUCC: 成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_event_get_switch(
                oal_uint8              uc_vap_id,
                oal_switch_enum_uint8 *pen_switch_type)
{
    if (OAL_PTR_NULL == pen_switch_type)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (uc_vap_id >= WLAN_VAP_SUPPORT_MAX_NUM_LIMIT)
    {
        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }

    *pen_switch_type = g_st_oam_mng_ctx.ast_event_ctx[uc_vap_id].en_event_switch;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_event_set_switch
 功能描述  : 设置EVENT模块的总开关
 输入参数  : uc_vap_id : 设置的对应的VAP ID
             en_switch_type : EVENT开关状态
 输出参数  : 无
 返 回 值  : OAL_SUCC: 设置成功
             OAL_FAIL: 设置失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_event_set_switch(
                oal_uint8               uc_vap_id,
                oal_switch_enum_uint8   en_switch_type)
{
    if (en_switch_type >= OAL_SWITCH_BUTT)
    {
        OAL_IO_PRINT("oam_event_set_switch::event_type[%d] invalid. \n", en_switch_type);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    if (uc_vap_id >= WLAN_VAP_SUPPORT_MAX_NUM_LIMIT)
    {
        OAL_IO_PRINT("oam_event_set_switch::vap_id[%d] >= WLAN_VAP_SUPPORT_MAX_NUM_LIMIT.\n", uc_vap_id);
        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }

    g_st_oam_mng_ctx.ast_event_ctx[uc_vap_id].en_event_switch = en_switch_type;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_event_set_specific_type_switch
 功能描述  : 设置具体某一种event上报的开关
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_event_set_specific_type_switch(
                            oal_uint8                   uc_vap_id,
                            oal_switch_enum_uint8       en_switch_type,
                            oam_event_type_enum_uint16  en_event_type)
{
    if (en_switch_type >= OAL_SWITCH_BUTT)
    {
        OAL_IO_PRINT("oam_event_set_specific_type_switch::en_switch_type[%d] invalid. \n", en_switch_type);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    if (uc_vap_id >= WLAN_VAP_SUPPORT_MAX_NUM_LIMIT)
    {
        OAL_IO_PRINT("oam_event_set_specific_type_switch::vap_id[%d] >= WLAN_VAP_SUPPORT_MAX_NUM_LIMIT. \n", uc_vap_id);
        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }

    g_st_oam_mng_ctx.ast_specific_event_ctx[uc_vap_id].aen_specific_event_switch[en_event_type] = en_switch_type;

    return OAL_SUCC;
}
#if 0
/*****************************************************************************
 函 数 名  : oam_ota_set_switch
 功能描述  : 设置具体某一种ota上报的开关
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_ota_set_switch(
                            oal_uint8                   uc_vap_id,
                            oal_switch_enum_uint8       en_switch_type,
                            oam_ota_type_enum_uint8     en_ota_type)
{
    if (en_ota_type >= OAM_OTA_TYPE_BUTT)
    {
        OAL_IO_PRINT("oam_ota_set_switch::event_type[%d] exceeds! \n", en_switch_type);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    if (uc_vap_id >= WLAN_VAP_SUPPORT_MAX_NUM_LIMIT)
    {
        OAL_IO_PRINT("oam_ota_set_switch::vap_id[%d] exceeds! \n", uc_vap_id);
        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }

    g_st_oam_mng_ctx.ast_ota_ctx[uc_vap_id].aen_ota_switch[en_ota_type] = en_switch_type;

    return OAL_SUCC;
}
#endif
/*****************************************************************************
 函 数 名  : oam_ota_set_beacon_switch
 功能描述  : 设置是否打印beacon帧的开关
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月7日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_ota_set_beacon_switch(
                  oal_uint8                                   uc_vap_id,
                  oam_sdt_print_beacon_rxdscr_type_enum_uint8 en_switch_type)
{
    if (en_switch_type >= OAM_SDT_PRINT_BEACON_RXDSCR_TYPE_BUTT)
    {
        OAL_IO_PRINT("oam_ota_set_beacon_switch::event_type[%d] exceeds! \n", en_switch_type);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    if (uc_vap_id >= WLAN_VAP_SUPPORT_MAX_NUM_LIMIT)
    {
        OAL_IO_PRINT("oam_ota_set_beacon_switch::vap_id[%d] exceeds! \n", uc_vap_id);
        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }

    g_st_oam_mng_ctx.ast_ota_ctx[uc_vap_id].en_beacon_switch = en_switch_type;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_ota_get_beacon_switch
 功能描述  : 获取beacon帧打印开关
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oam_sdt_print_beacon_rxdscr_type_enum_uint8  oam_ota_get_beacon_switch(oal_void)
{
    return g_st_oam_mng_ctx.ast_ota_ctx[0].en_beacon_switch;
}

/*****************************************************************************
 函 数 名  : oam_ota_set_rx_dscr_switch
 功能描述  : 设置是否打印rx_dscr的开关
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_ota_set_rx_dscr_switch(
                                                  oal_uint8             uc_vap_id,
                                                  oal_switch_enum_uint8 en_switch_type)
{
    if (en_switch_type >= OAM_PROFILING_SWITCH_BUTT)
    {
        OAL_IO_PRINT("oam_ota_set_rx_dscr_switch::event_type[%d] exceeds! \n", en_switch_type);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    if (uc_vap_id >= WLAN_VAP_SUPPORT_MAX_NUM_LIMIT)
    {
        OAL_IO_PRINT("oam_ota_set_rx_dscr_switch::vap_id[%d] exceeds! \n", uc_vap_id);
        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }

    g_st_oam_mng_ctx.ast_ota_ctx[uc_vap_id].en_rx_dscr_switch = en_switch_type;

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : oam_ota_get_rx_dscr_switch
 功能描述  : 获取rx描述符打印开关
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_switch_enum_uint8  oam_ota_get_rx_dscr_switch(oal_void)
{
    return g_st_oam_mng_ctx.ast_ota_ctx[0].en_rx_dscr_switch;
}

/*****************************************************************************
 函 数 名  : oam_event_format_string
 功能描述  : 根据格式,将事件信息写入到指定的文件中
 输入参数  : 1) 输出内容
             2) 输出最长长度
             3) VAP编号
             4) 文件ID
             5) 行号
             6) 模块ID
             7) 事件类型
 输出参数  : 无
 返 回 值  : OAL_SUCC :成功;或其他错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  oam_event_format_string(
                oal_int8                       *pac_output_data,
                oal_uint16                      ul_data_len,
                oal_uint8                       uc_vap_id,
                oam_module_id_enum_uint16       en_mod,
                oam_event_type_enum_uint16      en_event_type)
{
    oal_uint32          ul_tick;

    if (OAL_PTR_NULL == pac_output_data)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取系统TICK值 */
    ul_tick = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    /* 格式化输出内容 */
    OAL_SPRINTF(pac_output_data,
                ul_data_len,
                "【EVENT】:Tick=%u, VAP=%d, ModId=%d, EVENT TYPE=%u\r\n",
                ul_tick,
                uc_vap_id,
                en_mod,
                en_event_type);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_event_print_to_std
 功能描述  : 将EVENT信息打印到标准输出窗口
 输入参数  : uc_vap_id       : 当前处理的VAP ID
             us_file_no      : 文件ID
             ul_file_line_no : 行号
             en_mod          : 模块
             en_event_type   : 当前VAP需要上报的事件信息
 输出参数  : 无
 返 回 值  : 函数返回成功或其他错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  oam_event_print_to_std(
                oal_uint8                   uc_vap_id,
                oam_module_id_enum_uint16   en_mod,
                oam_event_type_enum_uint16  en_event_type)
{
    oal_int8   ac_output_data[OAM_PRINT_FORMAT_LENGTH];    /* 用于保存写入到文件中的内容 */
    oal_uint32 ul_rslt;

    ul_rslt = oam_event_format_string(ac_output_data,
                                      OAM_PRINT_FORMAT_LENGTH,
                                      uc_vap_id,
                                      en_mod,
                                      en_event_type);

    if (OAL_SUCC != ul_rslt)
    {
        return ul_rslt;
    }

    ul_rslt = oam_print_to_console(ac_output_data);

    if (OAL_SUCC != ul_rslt)
    {
        return ul_rslt;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_event_print_to_file
 功能描述  : 将EVENT信息打印到文件中
 输入参数  : uc_vap_id       : 当前处理的VAP ID
             us_file_no      : 文件ID
             ul_file_line_no : 行号
             en_mod          : 模块
             en_event_type   : 当前VAP需要上报的事件信息
 输出参数  : 无
 返 回 值  : 函数返回成功或其他错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  oam_event_print_to_file(
                oal_uint8                   uc_vap_id,
                oam_module_id_enum_uint16   en_mod,
                oam_event_type_enum_uint16  en_event_type)
{
#ifdef _PRE_WIFI_DMT
    oal_int8   ac_output_data[OAM_PRINT_FORMAT_LENGTH];  /* 用于保存写入到文件中的内容 */
    oal_uint32 ul_rslt;

    ul_rslt = oam_event_format_string(ac_output_data,
                                      OAM_PRINT_FORMAT_LENGTH,
                                      uc_vap_id,
                                      en_mod,
                                      en_event_type);

    if (OAL_SUCC != ul_rslt)
    {
        return ul_rslt;
    }

    ul_rslt = oam_print_to_file(ac_output_data);

    if (OAL_SUCC != ul_rslt)
    {
        return ul_rslt;
    }
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_event_print_to_sdt
 功能描述  : 将EVENT信息打印到PC调测工具平台
 输入参数  : puc_mac_hdr_addr: 用户mac地址，用于sdt过滤
             uc_vap_id       : 当前处理的VAP ID
             us_file_no      : 文件ID
             ul_file_line_no : 行号
             en_mod          : 模块
             en_event_type   : 当前VAP需要上报的事件信息
 输出参数  : 无
 返 回 值  : 函数返回成功或其他错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  oam_event_print_to_sdt(
                                    oal_uint8                 *puc_mac_hdr_addr,
                                    oal_uint8                   uc_vap_id,
                                    oam_module_id_enum_uint16   en_mod,
                                    oam_event_type_enum_uint16  en_event_type,
                                    oal_uint8                  *puc_string)
{
    oam_event_stru      st_event;
    oal_uint32          ul_tick;
    oal_netbuf_stru    *pst_netbuf;
    oal_uint32          ul_ret          = OAL_SUCC;

    if (OAL_UNLIKELY(OAL_PTR_NULL == g_st_oam_sdt_func_hook.p_sdt_report_data_func))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAL_MEMZERO(&st_event, OAL_SIZEOF(oam_event_stru));

    /* 获取系统时间 */
    ul_tick = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    /* 填写event结构体 */
    st_event.st_event_hdr.ul_tick        = ul_tick;
    st_event.st_event_hdr.uc_vap_id      = uc_vap_id;
    st_event.st_event_hdr.en_module      = en_mod;
    st_event.st_event_hdr.en_event_type  = en_event_type;
    oal_set_mac_addr(st_event.st_event_hdr.auc_user_macaddr, puc_mac_hdr_addr);

    oal_memcopy((oal_void *)st_event.auc_event_info,
                (const oal_void *)puc_string,
                 OAM_EVENT_INFO_MAX_LEN);

    /* 将event信息复制到netbuf上报给SDT,头部预留8字节，尾部预留1字节，给sdt_drv用 */
    pst_netbuf = oam_alloc_data2sdt(OAM_EVENT_STRU_SIZE);
    if (OAL_PTR_NULL == pst_netbuf)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    oal_memcopy((oal_void *)oal_netbuf_data(pst_netbuf),
                (const oal_void *)&st_event,
                OAM_EVENT_STRU_SIZE);

    /* 判断sdt发送消息队列是否已满，若满输出至串口 */
    ul_ret = oam_report_data2sdt(pst_netbuf, OAM_DATA_TYPE_EVENT, OAM_PRIMID_TYPE_OUTPUT_CONTENT);

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : oam_event_report
 功能描述  : 上报event事件。
 输入参数  : puc_mac_hdr_addr:用户mac地址，用于sdt过滤
             uc_vap_id       : 当前处理的VAP ID
             us_file_no      : 文件ID
             ul_file_line_no : 行号
             en_mod          : 模块
             en_event_type   : 当前VAP需要上报的事件信息
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_event_report(
                        oal_uint8                  *puc_mac_hdr_addr,
                        oal_uint8                   uc_vap_id,
                        oam_module_id_enum_uint16   en_mod,
                        oam_event_type_enum_uint16  en_event_type,
                        oal_uint8                  *puc_string)
{
    oal_uint32          ul_rslt;

    if (en_event_type >= OAM_EVENT_TYPE_BUTT)
    {
        return OAL_FAIL;
    }

    if (uc_vap_id >= WLAN_VAP_SUPPORT_MAX_NUM_LIMIT)
    {
        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }

    if ((OAL_PTR_NULL == puc_string) || (OAL_PTR_NULL == puc_mac_hdr_addr))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 检查event上报总开关是否打开 */
    if (OAL_SWITCH_OFF == g_st_oam_mng_ctx.ast_event_ctx[uc_vap_id].en_event_switch)
    {
        return OAL_SUCC;
    }

    /* 检查具体某一种event上报开关是否打开 */
    if (OAL_SWITCH_OFF == g_st_oam_mng_ctx.ast_specific_event_ctx[uc_vap_id].aen_specific_event_switch[en_event_type])
    {
        return OAL_SUCC;
    }

    switch (g_st_oam_mng_ctx.en_output_type)
    {
        /* 输出至控制台 */
        case OAM_OUTPUT_TYPE_CONSOLE:
            ul_rslt = oam_event_print_to_std(uc_vap_id, en_mod, en_event_type);

            break;

        /* 输出至文件系统中 */
        case OAM_OUTPUT_TYPE_FS:
            ul_rslt = oam_event_print_to_file(uc_vap_id, en_mod, en_event_type);
            break;

        /* 输出至PC侧调测工具平台 */
        case OAM_OUTPUT_TYPE_SDT:
            ul_rslt = oam_event_print_to_sdt(puc_mac_hdr_addr,
                                             uc_vap_id, en_mod,
                                             en_event_type,
                                             puc_string);

            break;

        /* 无效配置 */
        default:
            ul_rslt = OAL_ERR_CODE_INVALID_CONFIG;

            break;
    }

    if (OAL_SUCC != ul_rslt)
    {
        return ul_rslt;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_event_init
 功能描述  : OAM模块event初始化操作。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化成功或返回其他错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_event_init(oal_void)
{
    oal_uint32 ul_rslt;
    oal_uint32 ul_vapid_loop;
    oal_uint32 ul_eventtype_loop;
#if 0
    oal_uint32 ul_otatype_loop;
#endif
    /* 初始化所有VAP默认EVENT功能为开 */
    for (ul_vapid_loop = 0; ul_vapid_loop < WLAN_VAP_SUPPORT_MAX_NUM_LIMIT; ul_vapid_loop++)
    {
        /* 设置EVENT总开关 */
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
        ul_rslt = oam_event_set_switch((oal_uint8)ul_vapid_loop, OAL_SWITCH_OFF);
#else
        ul_rslt = oam_event_set_switch((oal_uint8)ul_vapid_loop, OAL_SWITCH_ON);
#endif

        if (OAL_SUCC != ul_rslt)
        {
            return ul_rslt;
        }

        /* 设置具体某一种EVENT的开关 */
        for (ul_eventtype_loop = 0; ul_eventtype_loop < OAM_EVENT_TYPE_BUTT; ul_eventtype_loop++)
        {
            oam_event_set_specific_type_switch((oal_uint8)ul_vapid_loop, OAL_SWITCH_ON, (oal_uint16)ul_eventtype_loop);
        }

        /* 内部抛事件event需要关闭 */
        oam_event_set_specific_type_switch((oal_uint8)ul_vapid_loop, OAL_SWITCH_OFF, OAM_EVENT_INTERNAL);
        oam_event_set_specific_type_switch((oal_uint8)ul_vapid_loop, OAL_SWITCH_OFF, OAM_EVENT_USER_INFO_CHANGE);
#if 0
        /* 设置具体某一种OTA的开关,描述符和帧共5种默认为关闭 */
        for (ul_otatype_loop = 0; ul_otatype_loop < OAM_OTA_TYPE_IRQ; ul_otatype_loop++)
        {
            oam_ota_set_switch((oal_uint8)ul_vapid_loop, OAL_SWITCH_OFF, (oal_uint8)ul_otatype_loop);
        }

        /* 非实时上报的OTA类型默认为开启 */
        for (ul_otatype_loop = OAM_OTA_TYPE_IRQ; ul_otatype_loop < OAM_OTA_TYPE_BUTT; ul_otatype_loop++)
        {
            oam_ota_set_switch((oal_uint8)ul_vapid_loop, OAL_SWITCH_ON, (oal_uint8)ul_otatype_loop);
        }
#endif
        /* 设置beacon打印开关为关闭 */
        oam_ota_set_beacon_switch((oal_uint8)ul_vapid_loop, OAL_SWITCH_OFF);
        /* 设置rx描述符打印开关为关闭 */
        oam_ota_set_rx_dscr_switch((oal_uint8)ul_vapid_loop, OAL_SWITCH_OFF);
    }

    /* 设置单用户跟踪相关的所有开关 */
    oam_report_set_all_switch(OAL_SWITCH_OFF);

    oam_report_dhcp_arp_set_switch(OAL_SWITCH_OFF);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_ota_report_to_std
 功能描述  : 将OTA数据打印到标准窗口:
             (1)如果是描述符，中断信息，内存池信息，定时器信息,或者事件队列信息,
                则屏幕上每行打印4字节；
             (2)如果是帧或者内存块信息，则每行打印20字节
             (3)如果是帧的话，而且帧体太长，则帧体只打印前300个字节
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  oam_ota_report_to_std(oal_uint8     *puc_param_one_addr,
                                       oal_uint16      us_param_one_len,
                                       oal_uint8      *puc_param_two_addr,
                                       oal_uint16      us_param_two_len,
                                       oam_ota_type_enum_uint8   en_ota_type)
{
    if (0 == us_param_two_len)
    {
        OAL_IO_PRINT("\n\nOTA TYPE is--> %d and OTA DATA is:\n", en_ota_type);
        oam_dump_buff_by_hex(puc_param_one_addr, us_param_one_len, 4);
    }
    else
    {
        /* 打印第一段内容 */
        OAL_IO_PRINT("\n\nOTA TYPE is--> %d and OTA DATA the first part is:\n", en_ota_type);
        oam_dump_buff_by_hex(puc_param_one_addr, us_param_one_len, OAM_PRINT_CRLF_NUM);

        /* 打印第二段内容 */
        OAL_IO_PRINT("\nOTA DATA tht second part is:\n");

        if (OAM_OTA_TYPE_80211_FRAME == en_ota_type)
        {
            us_param_two_len = OAL_MIN(us_param_two_len, OAM_OTA_DATA_TO_STD_MAX_LEN);
        }

        oam_dump_buff_by_hex(puc_param_two_addr, us_param_two_len, OAM_PRINT_CRLF_NUM);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_ota_report_to_sdt
 功能描述  : 将空口消息上报SDT工具，包括接收描述符，发送描述符，帧
 输入参数  : puc_param_one_addr:如果是描述符，则表示描述符的地址;如果是帧，表示帧头地址
             ul_param_one_len  :如果是描述符，则表示描述符长度;如果是帧，表示帧头长度
             puc_param_two_addr:如果是描述符，则为0;如果是帧，表示帧体地址
             ul_param_two_len  :如果是描述符，则为0;如果是帧，表示帧体长度
             en_ota_type       :OTA类型
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
/*lint -e662*/
oal_uint32  oam_ota_report_to_sdt(oal_uint8    *puc_param_one_addr,
                                       oal_uint16     us_param_one_len,
                                       oal_uint8     *puc_param_two_addr,
                                       oal_uint16     us_param_two_len,
                                       oam_ota_type_enum_uint8  en_ota_type)
{
    oal_uint32           ul_ret             = OAL_SUCC;
#if ((_PRE_OS_VERSION_RAW != _PRE_OS_VERSION) && (_PRE_OS_VERSION_WIN32_RAW != _PRE_OS_VERSION))
    oal_uint32           ul_tick;
    oal_uint16           us_skb_len;
    oal_netbuf_stru     *pst_netbuf;
    oam_ota_stru        *pst_ota_data;


    if (OAL_UNLIKELY(OAL_PTR_NULL == g_st_oam_sdt_func_hook.p_sdt_report_data_func))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 为上报OTA数据申请空间，如果是描述符，us_param_two_len为0 */
    us_skb_len = us_param_one_len + us_param_two_len + OAL_SIZEOF(oam_ota_hdr_stru);
    if (us_skb_len > WLAN_SDT_NETBUF_MAX_PAYLOAD)
    {
        us_skb_len = WLAN_SDT_NETBUF_MAX_PAYLOAD;
        if ((us_param_one_len + OAL_SIZEOF(oam_ota_hdr_stru)) < us_skb_len)
        {
            us_param_two_len = us_skb_len - us_param_one_len - (oal_uint16)OAL_SIZEOF(oam_ota_hdr_stru);
        }
        else
        {
            us_param_one_len = us_skb_len - OAL_SIZEOF(oam_ota_hdr_stru);
            us_param_two_len = 0;
        }
    }

    pst_netbuf = oam_alloc_data2sdt(us_skb_len);
    if (OAL_PTR_NULL == pst_netbuf)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_ota_data = (oam_ota_stru *)oal_netbuf_data(pst_netbuf);

    /* 获取系统TICK值 */
    ul_tick = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    pst_ota_data->st_ota_hdr.ul_tick     = ul_tick;
    pst_ota_data->st_ota_hdr.en_ota_type = en_ota_type;

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
    pst_ota_data->st_ota_hdr.auc_resv[0]    = 2;
#else
    pst_ota_data->st_ota_hdr.auc_resv[0]    = 3;
#endif


    switch (en_ota_type)
    {
        /* 封装接收或者发送描述符对应OTA结构体的其它成员 */
        case OAM_OTA_TYPE_RX_DSCR:
        case OAM_OTA_TYPE_TX_DSCR:
        case OAM_OTA_TYPE_IRQ:
        case OAM_OTA_TYPE_EVENT_QUEUE:
        case OAM_OTA_TYPE_TIMER:
        case OAM_OTA_TYPE_MEMPOOL:
        case OAM_OTA_TYPE_HMAC_VAP:
        case OAM_OTA_TYPE_DMAC_VAP:
        case OAM_OTA_TYPE_HMAC_USER:
        case OAM_OTA_TYPE_DMAC_USER:
        case OAM_OTA_TYPE_HMAC_VAP_MEMBER_SIZE:
        case OAM_OTA_TYPE_DMAC_VAP_MEMBER_SIZE:
            pst_ota_data->st_ota_hdr.us_ota_data_len = us_param_one_len;
            oal_memcopy((oal_void *)pst_ota_data->auc_ota_data,
                        (const oal_void *)puc_param_one_addr,
                        (oal_uint32)us_param_one_len);

            break;

        /* 封装帧对应OTA结构体的其它成员 */
        case OAM_OTA_TYPE_80211_FRAME:
        case OAM_OTA_TYPE_MEMBLOCK:
            pst_ota_data->st_ota_hdr.uc_frame_hdr_len = (oal_uint8)us_param_one_len;
            pst_ota_data->st_ota_hdr.us_ota_data_len  = us_param_one_len + us_param_two_len;

            /* 复制帧头 */
            oal_memcopy((oal_void *)pst_ota_data->auc_ota_data,
                        (const oal_void *)puc_param_one_addr,
                        (oal_uint32)us_param_one_len);

            /* 复制帧体 */
            oal_memcopy((oal_void *)(pst_ota_data->auc_ota_data + us_param_one_len),
                        (const oal_void *)puc_param_two_addr,
                        (oal_uint32)us_param_two_len);

            break;

        /* 无效值 */
        default:
            oal_mem_sdt_netbuf_free(pst_netbuf, OAL_TRUE);
            //oal_netbuf_free(pst_netbuf);
            return OAL_ERR_CODE_INVALID_CONFIG;
    }

    /* 判断sdt发送消息队列是否已满，若满输出至串口 */
    ul_ret = oam_report_data2sdt(pst_netbuf, OAM_DATA_TYPE_OTA, OAM_PRIMID_TYPE_OUTPUT_CONTENT);
#endif
    return ul_ret;
}


/*****************************************************************************
 函 数 名  : oam_ota_report
 功能描述  : 上报OTA(over the air)事件,包括接收描述符，发送描述符，帧三种。
 输入参数  : puc_param_one_addr:如果是描述符，则表示描述符的地址;如果是帧，表示帧头地址
             ul_param_one_len  :如果是描述符，则表示描述符长度;如果是帧，表示帧头长度
             puc_param_two_addr:如果是描述符，则为0;如果是帧，表示帧体地址
             ul_param_two_len  :如果是描述符，则为0;如果是帧，表示帧体长度
             en_ota_type       :OTA类型
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_ota_report(
                           oal_uint8     *puc_param_one_addr,
                           oal_uint16     us_param_one_len,
                           oal_uint8     *puc_param_two_addr,
                           oal_uint16     us_param_two_len,
                           oam_ota_type_enum_uint8  en_ota_type)
{
    oal_uint32          ul_rslt = OAL_ERR_CODE_BUTT;
#if 0
    /* 检查要打印的ota类型开关是否打开 */
    if (OAL_SWITCH_OFF == g_st_oam_mng_ctx.ast_ota_ctx[0].aen_ota_switch[en_ota_type])
    {
        return OAL_SUCC;
    }
#endif
    if (OAL_PTR_NULL == puc_param_one_addr)
    {
        OAL_IO_PRINT("oam_ota_report::puc_param_one_addr is null!\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_PTR_NULL == puc_param_two_addr)
    {
        OAL_IO_PRINT("oam_ota_report::puc_param_two_addr is null!\n");
        return OAL_ERR_CODE_PTR_NULL;
    }
    switch (g_st_oam_mng_ctx.en_output_type)
    {
        /* 输出至控制台 */
        case OAM_OUTPUT_TYPE_CONSOLE:
        ul_rslt = oam_ota_report_to_std(puc_param_one_addr,
                                        us_param_one_len,
                                        puc_param_two_addr,
                                        us_param_two_len,
                                        en_ota_type);

        break;

        /* 输出至SDT工具 */
        case OAM_OUTPUT_TYPE_SDT:
        ul_rslt = oam_ota_report_to_sdt(puc_param_one_addr,
                                        us_param_one_len,
                                        puc_param_two_addr,
                                        us_param_two_len,
                                        en_ota_type);

        break;

        default:
        ul_rslt = OAL_ERR_CODE_INVALID_CONFIG;

        break;
    }

    if (OAL_SUCC != ul_rslt)
    {
        return ul_rslt;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_report_80211_frame_to_console
 功能描述  : 将80211帧内容打印到控制台（一般是串口）
 输入参数  : puc_mac_hdr_addr :mac帧头地址
             us_mac_hdr_len   :mac帧头长度
             puc_mac_body_addr:mac帧体地址
             us_mac_frame_len :mac帧总长度(帧头+帧体)
             en_frame_direction:mac方向(tx流程还是rx流程)
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  oam_report_80211_frame_to_console(
                        oal_uint8     *puc_mac_hdr_addr,
                        oal_uint8      uc_mac_hdr_len,
                        oal_uint8     *puc_mac_body_addr,
                        oal_uint16     us_mac_frame_len,
                        oam_ota_frame_direction_type_enum_uint8  en_frame_direction)
{
    oal_uint16      us_80211_frame_body_len;

    if (OAM_OTA_FRAME_DIRECTION_TYPE_TX == en_frame_direction)
    {
        OAL_IO_PRINT("oam_report_80211_frame_to_console::tx_80211_frame header:\n");
    }
    else
    {
        OAL_IO_PRINT("oam_report_80211_frame_to_console::rx_80211_frame header:\n");
    }

    oam_dump_buff_by_hex(puc_mac_hdr_addr, uc_mac_hdr_len, OAM_PRINT_CRLF_NUM);

    if (uc_mac_hdr_len > us_mac_frame_len)
    {
        OAL_IO_PRINT("oam_report_80211_frame_to_console::rx_80211_frame invalid frame\n");
        return OAL_FAIL;
    }

    us_80211_frame_body_len   = us_mac_frame_len - uc_mac_hdr_len;

    OAL_IO_PRINT("oam_report_80211_frame_to_console::80211_frame body:\n");
    oam_dump_buff_by_hex(puc_mac_body_addr, us_80211_frame_body_len, OAM_PRINT_CRLF_NUM);

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : oam_hide_mac_addr
 功能描述  : 处于安全保护掩盖日志中OTA的帧内的mac地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void oam_hide_mac_addr(oal_uint8 *puc_mac_hdr, oal_uint8 uc_beacon_hdr_len)
{
    if (OAL_PTR_NULL == puc_mac_hdr || WLAN_MGMT_FRAME_HEADER_LEN > uc_beacon_hdr_len)
    {
        return;
    }
    /* addr1 */
    puc_mac_hdr[5] = 0xff;
    puc_mac_hdr[6] = 0xff;
    puc_mac_hdr[7] = 0xff;

    /* addr2 */
    puc_mac_hdr[11] = 0xff;
    puc_mac_hdr[12] = 0xff;
    puc_mac_hdr[13] = 0xff;

    /* addr3 */
    puc_mac_hdr[17] = 0xff;
    puc_mac_hdr[18] = 0xff;
    puc_mac_hdr[19] = 0xff;

}

/*****************************************************************************
 函 数 名  : oam_report_80211_frame_to_sdt
 功能描述  : 将80211帧内容上报SDT
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  oam_report_80211_frame_to_sdt(
                        oal_uint8     *puc_user_macaddr,
                        oal_uint8     *puc_mac_hdr_addr,
                        oal_uint8      uc_mac_hdr_len,
                        oal_uint8     *puc_mac_body_addr,
                        oal_uint16     us_mac_frame_len,
                        oam_ota_frame_direction_type_enum_uint8  en_frame_direction)
{
    oal_uint32           ul_tick;
    oal_uint16           us_skb_len;
    oal_netbuf_stru     *pst_netbuf;
    oam_ota_stru        *pst_ota_data;
    oal_uint32           ul_ret             = OAL_SUCC;

    if (OAL_UNLIKELY(OAL_PTR_NULL == g_st_oam_sdt_func_hook.p_sdt_report_data_func))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 为上报80211帧申请空间 */
    us_skb_len = us_mac_frame_len + OAL_SIZEOF(oam_ota_hdr_stru);
    if (us_skb_len > WLAN_SDT_NETBUF_MAX_PAYLOAD)
    {
        us_skb_len = WLAN_SDT_NETBUF_MAX_PAYLOAD;
        us_mac_frame_len = WLAN_SDT_NETBUF_MAX_PAYLOAD - OAL_SIZEOF(oam_ota_hdr_stru);
    }

    pst_netbuf = oam_alloc_data2sdt(us_skb_len);
    if (OAL_PTR_NULL == pst_netbuf)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_ota_data = (oam_ota_stru *)OAL_NETBUF_HEADER(pst_netbuf);

    /* 获取系统TICK值 */
    ul_tick = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    /* 填写ota消息头结构体 */
    pst_ota_data->st_ota_hdr.ul_tick            = ul_tick;
    pst_ota_data->st_ota_hdr.en_ota_type        = OAM_OTA_TYPE_80211_FRAME;
    pst_ota_data->st_ota_hdr.uc_frame_hdr_len   = uc_mac_hdr_len;
    pst_ota_data->st_ota_hdr.us_ota_data_len    = us_mac_frame_len;
    pst_ota_data->st_ota_hdr.en_frame_direction = en_frame_direction;
    oal_set_mac_addr(pst_ota_data->st_ota_hdr.auc_user_macaddr, puc_user_macaddr);
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
    pst_ota_data->st_ota_hdr.auc_resv[0]    = 2;
#else
    pst_ota_data->st_ota_hdr.auc_resv[0]    = 3;
#endif

    /* 复制帧头 */
    oal_memcopy((oal_void *)pst_ota_data->auc_ota_data,
                (const oal_void *)puc_mac_hdr_addr,
                (oal_uint32)uc_mac_hdr_len);
    /* 复制帧体 */
    oal_memcopy((oal_void *)(pst_ota_data->auc_ota_data + uc_mac_hdr_len),
                (const oal_void *)puc_mac_body_addr,
                (oal_uint32)(us_mac_frame_len - uc_mac_hdr_len));

    oam_hide_mac_addr(pst_ota_data->auc_ota_data, uc_mac_hdr_len);

    /* 判断sdt发送消息队列是否已满，若满输出至串口 */
    ul_ret = oam_report_data2sdt(pst_netbuf, OAM_DATA_TYPE_OTA, OAM_PRIMID_TYPE_OUTPUT_CONTENT);

    return ul_ret;
}


/*****************************************************************************
 函 数 名  : oam_report_80211_frame
 功能描述  : 上报802.11帧
 输入参数  : puc_mac_hdr_addr :mac帧头地址
             us_mac_hdr_len   :mac帧头长度
             puc_mac_body_addr:mac帧体地址
             us_mac_frame_len :mac帧总长度(帧头+帧体)
             en_frame_direction:mac方向(tx流程还是rx流程)
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_report_80211_frame(
                        oal_uint8     *puc_user_macaddr,
                        oal_uint8     *puc_mac_hdr_addr,
                        oal_uint8      uc_mac_hdr_len,
                        oal_uint8     *puc_mac_body_addr,
                        oal_uint16     us_mac_frame_len,
                        oam_ota_frame_direction_type_enum_uint8  en_frame_direction)
{
    oal_uint32      ul_ret      = OAL_SUCC;
    oal_uint32      ul_oam_ret  = OAL_SUCC;
    oal_uint32      ul_return_addr = 0;

    /* Less IO_print, less oam_report_80211_frame_to_console, use oam_report_80211_frame_to_sdt for log.
       Suggested by gongxiangling &  */

#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
    ul_return_addr  = __return_address();
#endif

    if (OAL_UNLIKELY(OAL_PTR_NULL == puc_mac_hdr_addr
        || OAL_PTR_NULL == puc_mac_body_addr
        || OAL_PTR_NULL == puc_user_macaddr))
    {
        OAM_ERROR_LOG4(0, OAM_SF_ANY, "{oam_report_80211_frame:[device] puc_mac_hdr_addr = 0x%X, puc_mac_body_addr = 0x%X, puc_user_macaddr = 0x%X, __return_address = 0x%X}",
                        puc_mac_hdr_addr,puc_mac_body_addr,puc_user_macaddr, ul_return_addr);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 检查帧头长度合法性 */
    if ((WLAN_MAX_FRAME_HEADER_LEN < uc_mac_hdr_len)
        || (WLAN_MIN_FRAME_HEADER_LEN > uc_mac_hdr_len))
    {
        oam_report_dft_params(BROADCAST_MACADDR,puc_mac_hdr_addr,OAM_OTA_FRAME_TO_SDT_MAX_LEN,OAM_OTA_TYPE_80211_FRAME);
        OAM_WARNING_LOG4(0, OAM_SF_ANY, "{oam_report_80211_frame:HEAD CHECK! hearder_len = %d, frame_len = %d, en_frame_direction = %d, return_addres = 0x%X}",
                        uc_mac_hdr_len,us_mac_frame_len,en_frame_direction,ul_return_addr);
        return OAL_ERR_CODE_OAM_EVT_FR_HDR_LEN_INVALID;
    }

    /* 检查mac帧总长度合法性 */
    if (uc_mac_hdr_len > us_mac_frame_len)
    {
        oam_report_dft_params(BROADCAST_MACADDR,puc_mac_hdr_addr,OAM_OTA_FRAME_TO_SDT_MAX_LEN,OAM_OTA_TYPE_80211_FRAME);
        OAM_WARNING_LOG4(0, OAM_SF_ANY, "{oam_report_80211_frame:HEAD/FRAME CHECK! hearder_len = %d, frame_len = %d, en_frame_direction = %d, return_addres = 0x%X}",
                        uc_mac_hdr_len,us_mac_frame_len,en_frame_direction,ul_return_addr);
        return OAL_ERR_CODE_OAM_EVT_FR_LEN_INVALID;
    }

    us_mac_frame_len = (us_mac_frame_len > WLAN_MAX_FRAME_LEN) ? WLAN_MAX_FRAME_LEN : us_mac_frame_len;

    if (OAL_UNLIKELY(en_frame_direction >= OAM_OTA_FRAME_DIRECTION_TYPE_BUTT))
    {
        return OAL_ERR_CODE_OAM_EVT_FRAME_DIR_INVALID;
    }

    switch (g_st_oam_mng_ctx.en_output_type)
    {
        /* 输出至控制台 */
        case OAM_OUTPUT_TYPE_CONSOLE:
            ul_ret = oam_report_80211_frame_to_console(puc_mac_hdr_addr,
                                                       uc_mac_hdr_len,
                                                       puc_mac_body_addr,
                                                       us_mac_frame_len,
                                                       en_frame_direction);
            break;

        /* 输出至SDT工具 */
        case OAM_OUTPUT_TYPE_SDT:
            /* 流控判断 */
            if (OAM_RATELIMIT_NOT_OUTPUT == oam_log_ratelimit(OAM_RATELIMIT_TYPE_FRAME_WLAN))
            {
                ul_oam_ret = OAL_SUCC;
            }
            else
            {
                ul_oam_ret = oam_report_80211_frame_to_sdt(puc_user_macaddr,
                                                       puc_mac_hdr_addr,
                                                       uc_mac_hdr_len,
                                                       puc_mac_body_addr,
                                                       us_mac_frame_len,
                                                       en_frame_direction);
            }
            break;

        default:
            ul_oam_ret = OAL_ERR_CODE_INVALID_CONFIG;
            break;
    }

    if ((OAL_SUCC != ul_oam_ret) ||
        (OAL_SUCC != ul_ret) )
    {
        OAM_WARNING_LOG4(0, OAM_SF_ANY, "{oam_report_80211_frame:[device] en_frame_direction = %d, ul_ret = %d, ul_oam_ret = %d, return_addres = 0x%X}",
                        en_frame_direction, ul_ret, ul_oam_ret, ul_return_addr);
    }

    return ((OAL_SUCC != ul_ret)?(ul_ret):(ul_oam_ret));
}

/*****************************************************************************
 函 数 名  : oam_report_dscr_to_console
 功能描述  : 将描述符信息打印到控制台（一般就是串口）
 输入参数  : puc_dscr_addr :描述符地址
             us_dscr_len   :描述符长度
             en_ota_type   :ota类型
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  oam_report_dscr_to_console(
                                    oal_uint8  *puc_dscr_addr,
                                    oal_uint16  us_dscr_len,
                                    oam_ota_type_enum_uint8  en_ota_type)
{
    if (OAM_OTA_TYPE_RX_DSCR == en_ota_type)
    {
        OAL_IO_PRINT("oam_report_dscr_to_console::rx_dscr info:\n\n");
    }

    else
    {
        OAL_IO_PRINT("oam_report_dscr_to_console::tx_dscr info:\n\n");
    }

    oam_dump_buff_by_hex(puc_dscr_addr, us_dscr_len, 4);

    return OAL_SUCC;
}

/*****************************************************************************
函数 名  : oam_report_dscr_to_sdt
功能描述  : 将描述符信息上报SDT
输入参数  : puc_dscr_addr :描述符地址
            us_dscr_len   :描述符长度
            en_ota_type   :ota类型
输出参数  : 无
返回值  :
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2014年2月19日
  作    者   : 
  修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  oam_report_dscr_to_sdt(
                                        oal_uint8  *puc_user_macaddr,
                                        oal_uint8  *puc_dscr_addr,
                                        oal_uint16  us_dscr_len,
                                        oam_ota_type_enum_uint8  en_ota_type)
{
    oal_uint32           ul_tick;
    oal_uint16           us_skb_len;
    oal_netbuf_stru     *pst_netbuf;
    oam_ota_stru        *pst_ota_data;
    oal_uint32           ul_ret         = OAL_SUCC;

    if (OAL_UNLIKELY(OAL_PTR_NULL == g_st_oam_sdt_func_hook.p_sdt_report_data_func))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 为上报描述符申请空间 */
    us_skb_len = us_dscr_len + OAL_SIZEOF(oam_ota_hdr_stru);
    if (us_skb_len > WLAN_SDT_NETBUF_MAX_PAYLOAD)
    {
        us_skb_len = WLAN_SDT_NETBUF_MAX_PAYLOAD;
        us_dscr_len = WLAN_SDT_NETBUF_MAX_PAYLOAD - OAL_SIZEOF(oam_ota_hdr_stru);
    }

    pst_netbuf = oam_alloc_data2sdt(us_skb_len);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_netbuf))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_ota_data = (oam_ota_stru *)oal_netbuf_data(pst_netbuf);

    /* 获取系统TICK值 */
    ul_tick = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    /* 填写ota消息头结构体 */
    pst_ota_data->st_ota_hdr.ul_tick     = ul_tick;
    pst_ota_data->st_ota_hdr.en_ota_type = en_ota_type;
    pst_ota_data->st_ota_hdr.us_ota_data_len = us_dscr_len;
    pst_ota_data->st_ota_hdr.uc_frame_hdr_len = 0;
    oal_set_mac_addr(pst_ota_data->st_ota_hdr.auc_user_macaddr, puc_user_macaddr);
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
    pst_ota_data->st_ota_hdr.auc_resv[0]    = 2;
#else
    pst_ota_data->st_ota_hdr.auc_resv[0]    = 3;
#endif

    /* 复制数据,填写ota数据 */
    oal_memcopy((oal_void *)pst_ota_data->auc_ota_data,
                (const oal_void *)puc_dscr_addr,
                (oal_uint32)us_dscr_len);

    /* 判断sdt发送消息队列是否已满，若满输出至串口 */
    ul_ret = oam_report_data2sdt(pst_netbuf, OAM_DATA_TYPE_OTA, OAM_PRIMID_TYPE_OUTPUT_CONTENT);

    return ul_ret;
}


/*****************************************************************************
 函 数 名  : oam_report_dscr
 功能描述  : 将描述符上报sdt,包括上报tx描述符和rx描述符
             注意::由于rx描述符最大长度为64，tx描述符最大长度为256，所以如果参数
             us_dscr_len大于256的话表明传入参数错误，直接返回
 输入参数  : puc_dscr_addr :描述符地址
             us_dscr_len   :描述符长度
             en_ota_type   :ota类型(rx描述符或者tx描述符)，由于描述符的上报是通
             过ota通道，因此需要这个参数，SDT解析的时候可以显示上报的是rx描述符
             还是tx描述符
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 oam_report_dscr(oal_uint8  *puc_user_macaddr,
                               oal_uint8  *puc_dscr_addr,
                               oal_uint16  us_dscr_len,
                               oam_ota_type_enum_uint8  en_ota_type)
{
    oal_uint32   ul_ret;

    if (OAL_UNLIKELY((OAL_PTR_NULL == puc_user_macaddr) || (OAL_PTR_NULL == puc_dscr_addr)))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    if ((WLAN_MEM_SHARED_TX_DSCR_SIZE2 < us_dscr_len)
        || (us_dscr_len == 0))
    {
        oam_dump_buff_by_hex(puc_dscr_addr, us_dscr_len, OAM_PRINT_CRLF_NUM);
        return OAL_ERR_CODE_OAM_EVT_DSCR_LEN_INVALID;
    }

    if (OAL_UNLIKELY((OAM_OTA_TYPE_RX_DSCR != en_ota_type) && (OAM_OTA_TYPE_TX_DSCR != en_ota_type)))
    {
        return OAL_ERR_CODE_CONFIG_UNSUPPORT;
    }

    switch (g_st_oam_mng_ctx.en_output_type)
    {
        /* 输出至控制台 */
        case OAM_OUTPUT_TYPE_CONSOLE:
            ul_ret = oam_report_dscr_to_console(puc_dscr_addr, us_dscr_len, en_ota_type);

            break;

        /* 输出至SDT工具 */
        case OAM_OUTPUT_TYPE_SDT:
            /* 流控判断 */
            if (OAM_RATELIMIT_NOT_OUTPUT == oam_log_ratelimit(OAM_RATELIMIT_TYPE_DSCR))
            {
                return OAL_SUCC;
            }
            ul_ret = oam_report_dscr_to_sdt(puc_user_macaddr, puc_dscr_addr, us_dscr_len, en_ota_type);

            break;

        default:
            ul_ret = OAL_ERR_CODE_INVALID_CONFIG;

            break;
    }

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : oam_report_beacon_to_console
 功能描述  : 将beacon帧内容打印到控制台（一般是串口）
 输入参数  : puc_beacon_hdr_addr :beacon帧地址
             us_beacon_len       :beacon帧长度
             en_beacon_direction :此beacon帧是接收流程中的还是发送流程中的
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  oam_report_beacon_to_console(
                        oal_uint8               *puc_beacon_hdr_addr,
                        oal_uint16               us_beacon_len,
                        oam_ota_frame_direction_type_enum_uint8 en_beacon_direction)
{
    oal_uint8      *puc_beacon_body_addr;
    oal_uint16      us_beacon_body_len;

    if (OAM_OTA_FRAME_DIRECTION_TYPE_TX == en_beacon_direction)
    {
        OAL_IO_PRINT("oam_report_beacon_to_console::tx_beacon info:\n");
    }
    else
    {
        OAL_IO_PRINT("oam_report_beacon_to_console::rx_beacon info:\n");
    }
    OAL_IO_PRINT("oam_report_beacon_to_console::beacon_header:\n");

    oam_dump_buff_by_hex(puc_beacon_hdr_addr, OAM_BEACON_HDR_LEN, OAM_PRINT_CRLF_NUM);

    puc_beacon_body_addr = puc_beacon_hdr_addr + OAM_BEACON_HDR_LEN;
    us_beacon_body_len   = us_beacon_len - OAM_BEACON_HDR_LEN;

    OAL_IO_PRINT("oam_report_beacon_to_console::beacon_body:\n");
    oam_dump_buff_by_hex(puc_beacon_body_addr, us_beacon_body_len, OAM_PRINT_CRLF_NUM);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_report_beacon_to_sdt
 功能描述  : 将beacon帧内容上报SDT
 输入参数  : puc_beacon_hdr_addr :beacon帧地址
             us_beacon_len       :beacon帧长度
             en_beacon_direction :此beacon帧是接收流程中的还是发送流程中的
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  oam_report_beacon_to_sdt(
                                oal_uint8     *puc_beacon_hdr_addr,
                                oal_uint8      uc_beacon_hdr_len,
                                oal_uint8     *puc_beacon_body_addr,
                                oal_uint16     us_beacon_len,
                                oam_ota_frame_direction_type_enum_uint8 en_beacon_direction)
{
    oal_uint32           ul_tick;
    oal_uint16           us_skb_len;
    oal_netbuf_stru     *pst_netbuf;
    oam_ota_stru        *pst_ota_data;
    oal_uint32           ul_ret         = OAL_SUCC;

    if (OAL_UNLIKELY(OAL_PTR_NULL == g_st_oam_sdt_func_hook.p_sdt_report_data_func))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 为上报beacon帧申请空间 */
    us_skb_len = us_beacon_len + OAL_SIZEOF(oam_ota_hdr_stru);
    if (us_skb_len > WLAN_SDT_NETBUF_MAX_PAYLOAD)
    {
        us_skb_len = WLAN_SDT_NETBUF_MAX_PAYLOAD;
        us_beacon_len = WLAN_SDT_NETBUF_MAX_PAYLOAD - OAL_SIZEOF(oam_ota_hdr_stru);
    }

    pst_netbuf = oam_alloc_data2sdt(us_skb_len);
    if (OAL_PTR_NULL == pst_netbuf)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_ota_data = (oam_ota_stru *)oal_netbuf_data(pst_netbuf);

    /* 获取系统TICK值 */
    ul_tick = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    /* 填写ota消息头结构体 */
    pst_ota_data->st_ota_hdr.ul_tick            = ul_tick;
    pst_ota_data->st_ota_hdr.en_ota_type        = OAM_OTA_TYPE_BEACON;
    pst_ota_data->st_ota_hdr.uc_frame_hdr_len   = OAM_BEACON_HDR_LEN;
    pst_ota_data->st_ota_hdr.us_ota_data_len    = us_beacon_len;
    pst_ota_data->st_ota_hdr.en_frame_direction = en_beacon_direction;
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
    pst_ota_data->st_ota_hdr.auc_resv[0]    = 2;
#else
    pst_ota_data->st_ota_hdr.auc_resv[0]    = 3;
#endif

    /* 复制数据,填写ota数据 */
    oal_memcopy((oal_void *)pst_ota_data->auc_ota_data,
                (const oal_void *)puc_beacon_hdr_addr,
                (oal_uint32)uc_beacon_hdr_len);
    oal_memcopy((oal_void *)(pst_ota_data->auc_ota_data + uc_beacon_hdr_len),
                (const oal_void *)puc_beacon_body_addr,
                (oal_uint32)(us_beacon_len - uc_beacon_hdr_len));

    oam_hide_mac_addr(pst_ota_data->auc_ota_data, uc_beacon_hdr_len);

    /* 下发至sdt接收队列，若队列满则串口输出 */
    ul_ret = oam_report_data2sdt(pst_netbuf, OAM_DATA_TYPE_OTA, OAM_PRIMID_TYPE_OUTPUT_CONTENT);

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : oam_report_beacon
 功能描述  : 将beacon内容上报
 输入参数  : puc_beacon_hdr_addr :beacon帧地址
             us_beacon_len       :beacon帧长度
             en_ota_type         :ota类型(beacon)
             en_beacon_direction :此beacon帧是接收流程中的还是发送流程中的
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_report_beacon(
                                    oal_uint8     *puc_beacon_hdr_addr,
                                    oal_uint8      uc_beacon_hdr_len,
                                    oal_uint8     *puc_beacon_body_addr,
                                    oal_uint16     us_beacon_len,
                                    oam_ota_frame_direction_type_enum_uint8 en_beacon_direction)
{
    oal_uint32   ul_ret;

    if (en_beacon_direction >= OAM_OTA_FRAME_DIRECTION_TYPE_BUTT)
    {
        return OAL_ERR_CODE_OAM_EVT_FRAME_DIR_INVALID;
    }

    if ((OAM_SDT_PRINT_BEACON_RXDSCR_TYPE_BEACON != g_st_oam_mng_ctx.ast_ota_ctx[0].en_beacon_switch)
        && (OAM_SDT_PRINT_BEACON_RXDSCR_TYPE_BOTH != g_st_oam_mng_ctx.ast_ota_ctx[0].en_beacon_switch))
    {
        return OAL_SUCC;
    }

    if ((OAL_PTR_NULL == puc_beacon_hdr_addr)||(OAL_PTR_NULL == puc_beacon_body_addr))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    if ((WLAN_MAX_FRAME_LEN < us_beacon_len)
        || (us_beacon_len <= WLAN_MGMT_FRAME_HEADER_LEN))
    {
        oam_dump_buff_by_hex(puc_beacon_hdr_addr, us_beacon_len, OAM_PRINT_CRLF_NUM);
        return OAL_ERR_CODE_OAM_EVT_FR_LEN_INVALID;
    }


    switch (g_st_oam_mng_ctx.en_output_type)
    {
        /* 输出至控制台 */
        case OAM_OUTPUT_TYPE_CONSOLE:
            ul_ret = oam_report_beacon_to_console(puc_beacon_hdr_addr,
                                                  us_beacon_len,
                                                  en_beacon_direction);

            break;

        /* 输出至SDT工具 */
        case OAM_OUTPUT_TYPE_SDT:
            ul_ret = oam_report_beacon_to_sdt(puc_beacon_hdr_addr,
                                              uc_beacon_hdr_len,
                                              puc_beacon_body_addr,
                                              us_beacon_len,
                                              en_beacon_direction);

            break;

        default:
            ul_ret = OAL_ERR_CODE_INVALID_CONFIG;

            break;
    }

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : oam_report_beacon_to_console
 功能描述  : 将beacon帧内容打印到控制台（一般是串口）
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  oam_report_eth_frame_to_console(
                        oal_uint8               *puc_eth_frame_hdr_addr,
                        oal_uint16               us_eth_frame_len,
                        oam_ota_frame_direction_type_enum_uint8 en_eth_frame_direction)
{
    oal_uint8      *puc_eth_frame_body_addr;
    oal_uint16      us_eth_frame_body_len;

    if (OAM_OTA_FRAME_DIRECTION_TYPE_TX == en_eth_frame_direction)
    {
        OAL_IO_PRINT("oam_report_eth_frame_to_console::recv frame from eth:\n");
    }
    else
    {
        OAL_IO_PRINT("oam_report_eth_frame_to_console::report frame to eth:\n");
    }

    OAL_IO_PRINT("oam_report_eth_frame_to_console::eth_frame header:\n");
    oam_dump_buff_by_hex(puc_eth_frame_hdr_addr, ETHER_HDR_LEN, OAM_PRINT_CRLF_NUM);

    puc_eth_frame_body_addr = puc_eth_frame_hdr_addr + ETHER_HDR_LEN;
    us_eth_frame_body_len   = us_eth_frame_len - ETHER_HDR_LEN;

    OAL_IO_PRINT("oam_report_eth_frame_to_console::eth_frame body:\n");
    oam_dump_buff_by_hex(puc_eth_frame_body_addr, us_eth_frame_body_len, OAM_PRINT_CRLF_NUM);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_report_eth_frame_to_sdt
 功能描述  : 将以太网帧内容上报SDT
 输入参数  : puc_eth_frame_hdr_addr :以太网帧头地址
             us_eth_frame_len       :以太网帧长度(帧头+帧体)
             en_eth_frame_direction :来自以太网(tx流程)还是发往以太网(rx流程)
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  oam_report_eth_frame_to_sdt(
                        oal_uint8               *puc_user_mac_addr,
                        oal_uint8               *puc_eth_frame_hdr_addr,
                        oal_uint16               us_eth_frame_len,
                        oam_ota_frame_direction_type_enum_uint8 en_eth_frame_direction)
{
    oal_uint32           ul_tick;
    oal_uint16           us_skb_len;
    oal_netbuf_stru     *pst_netbuf;
    oam_ota_stru        *pst_ota_data;
    oal_uint32           ul_ret     = OAL_SUCC;

    if (OAL_UNLIKELY(OAL_PTR_NULL == g_st_oam_sdt_func_hook.p_sdt_report_data_func))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 为上报beacon帧申请空间 */
    us_skb_len = us_eth_frame_len + OAL_SIZEOF(oam_ota_hdr_stru);
    if (us_skb_len > WLAN_SDT_NETBUF_MAX_PAYLOAD)
    {
        us_skb_len = WLAN_SDT_NETBUF_MAX_PAYLOAD;
        us_eth_frame_len = WLAN_SDT_NETBUF_MAX_PAYLOAD - OAL_SIZEOF(oam_ota_hdr_stru);
    }

    pst_netbuf = oam_alloc_data2sdt(us_skb_len);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_netbuf))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_ota_data = (oam_ota_stru *)oal_netbuf_data(pst_netbuf);

    /* 获取系统TICK值 */
    ul_tick = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    /* 填写ota消息头结构体 */
    pst_ota_data->st_ota_hdr.ul_tick            = ul_tick;
    pst_ota_data->st_ota_hdr.en_ota_type        = OAM_OTA_TYPE_ETH_FRAME;
    pst_ota_data->st_ota_hdr.uc_frame_hdr_len   = ETHER_HDR_LEN;
    pst_ota_data->st_ota_hdr.us_ota_data_len    = us_eth_frame_len;
    pst_ota_data->st_ota_hdr.en_frame_direction = en_eth_frame_direction;
    oal_set_mac_addr(pst_ota_data->st_ota_hdr.auc_user_macaddr, puc_user_mac_addr);
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
    pst_ota_data->st_ota_hdr.auc_resv[0]    = 2;
#else
    pst_ota_data->st_ota_hdr.auc_resv[0]    = 3;
#endif

    /* 复制数据,填写ota数据 */
    oal_memcopy((oal_void *)pst_ota_data->auc_ota_data,
                (const oal_void *)puc_eth_frame_hdr_addr,
                (oal_uint32)us_eth_frame_len);

    /* 下发至sdt接收队列，若队列满则串口输出 */
    ul_ret = oam_report_data2sdt(pst_netbuf, OAM_DATA_TYPE_OTA, OAM_PRIMID_TYPE_OUTPUT_CONTENT);

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : oam_report_eth_frame
 功能描述  : 上报以太网帧，此接口只能用在两个地方:
             (1)发送流程，从以太网收到包之后，在wal_bridge_vap_xmit中
             (2)接收流程，将帧上报以太网之前，在hmac_rx_transmit_msdu_to_lan中调用
             oal_netif_rx之前
 输入参数  : us_user_idx            :用户资源池id
             puc_eth_frame_hdr_addr :以太网帧头地址
             us_eth_frame_len       :以太网帧长度(帧头+帧体)
             en_eth_frame_direction :来自以太网(tx流程)还是发往以太网(rx流程)
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_report_eth_frame(oal_uint8               *puc_user_mac_addr,
                                       oal_uint8               *puc_eth_frame_hdr_addr,
                                       oal_uint16               us_eth_frame_len,
                                       oam_ota_frame_direction_type_enum_uint8 en_eth_frame_direction)
{
    oal_uint32      ul_ret;

    if (OAL_UNLIKELY((OAL_PTR_NULL == puc_user_mac_addr) || (OAL_PTR_NULL == puc_eth_frame_hdr_addr)))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    if ((ETHER_MAX_LEN < us_eth_frame_len)
        || (us_eth_frame_len < ETHER_HDR_LEN))
    {
        oam_dump_buff_by_hex(puc_eth_frame_hdr_addr, us_eth_frame_len, OAM_PRINT_CRLF_NUM);

        return OAL_ERR_CODE_OAM_EVT_FR_LEN_INVALID;
    }

    if (OAL_UNLIKELY(en_eth_frame_direction >= OAM_OTA_FRAME_DIRECTION_TYPE_BUTT))
    {
        return OAL_ERR_CODE_OAM_EVT_FRAME_DIR_INVALID;
    }

    switch (g_st_oam_mng_ctx.en_output_type)
    {
        /* 输出至控制台 */
        case OAM_OUTPUT_TYPE_CONSOLE:
            ul_ret = oam_report_eth_frame_to_console(puc_eth_frame_hdr_addr,
                                                     us_eth_frame_len,
                                                     en_eth_frame_direction);

            break;

        /* 输出至SDT工具 */
        case OAM_OUTPUT_TYPE_SDT:
            /* 流控判断 */
            if (OAM_RATELIMIT_NOT_OUTPUT == oam_log_ratelimit(OAM_RATELIMIT_TYPE_FRAME_ETH))
            {
                return OAL_SUCC;
            }
            ul_ret = oam_report_eth_frame_to_sdt(puc_user_mac_addr,
                                                 puc_eth_frame_hdr_addr,
                                                 us_eth_frame_len,
                                                 en_eth_frame_direction);
            break;

        default:
            ul_ret = OAL_ERR_CODE_INVALID_CONFIG;

            break;
    }

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : oam_report_netbuf_cb_to_sdt
 功能描述  : 将80211帧的CB字段上报SDT
 输入参数  : puc_user_mac_addr:目的用户mac地址
             puc_netbuf_cb    :要上报的CB字段
             en_frame_direction :接收还是发送
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  oam_report_netbuf_cb_to_sdt(
                                oal_uint8  *puc_user_mac_addr,
                                oal_uint8  *puc_netbuf_cb,
                                oam_ota_type_enum_uint8 en_ota_type)
{
    oal_uint32           ul_ret     = OAL_SUCC;
#if ((_PRE_OS_VERSION_RAW != _PRE_OS_VERSION) && (_PRE_OS_VERSION_WIN32_RAW != _PRE_OS_VERSION))
    oal_uint32           ul_tick;
    oal_uint16           us_ota_data_len;
    oal_uint16           us_skb_len;
    oal_netbuf_stru     *pst_netbuf;
    oam_ota_stru        *pst_ota_data;

    if (OAL_UNLIKELY(OAL_PTR_NULL == g_st_oam_sdt_func_hook.p_sdt_report_data_func))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    us_skb_len = OAM_SKB_CB_LEN + OAL_SIZEOF(oam_ota_hdr_stru) + OAM_RESERVE_SKB_LEN;
    us_ota_data_len = OAM_SKB_CB_LEN + OAL_SIZEOF(oam_ota_hdr_stru);

    pst_netbuf = oal_mem_sdt_netbuf_alloc(us_skb_len, OAL_TRUE);
    if (OAL_PTR_NULL == pst_netbuf)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }
    oal_netbuf_reserve(pst_netbuf, OAM_RESERVE_SKB_HEADROOM_LEN);

    oal_netbuf_put(pst_netbuf, us_ota_data_len);
    pst_ota_data = (oam_ota_stru *)oal_netbuf_data(pst_netbuf);

    /* 获取系统TICK值 */
    ul_tick = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    /* 填写ota消息头结构体 */
    pst_ota_data->st_ota_hdr.ul_tick     = ul_tick;
    pst_ota_data->st_ota_hdr.en_ota_type = en_ota_type;
    pst_ota_data->st_ota_hdr.us_ota_data_len = OAM_SKB_CB_LEN;
    pst_ota_data->st_ota_hdr.uc_frame_hdr_len = 0;
    oal_set_mac_addr(pst_ota_data->st_ota_hdr.auc_user_macaddr, puc_user_mac_addr);
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
    pst_ota_data->st_ota_hdr.auc_resv[0]    = 2;
#else
    pst_ota_data->st_ota_hdr.auc_resv[0]    = 3;
#endif

    /* 复制数据,填写ota数据 */
    oal_memcopy((oal_void *)pst_ota_data->auc_ota_data,
                (const oal_void *)puc_netbuf_cb,
                OAM_SKB_CB_LEN);

    /* 上报SDT */
    ul_ret = oam_report_data2sdt(pst_netbuf, OAM_DATA_TYPE_OTA, OAM_PRIMID_TYPE_OUTPUT_CONTENT);
#endif
    return ul_ret;
}


/*****************************************************************************
 函 数 名  : oam_report_netbuf_cb
 功能描述  : 上报80211的cb字段
 输入参数  : puc_user_mac_addr:目的用户mac地址
             puc_netbuf_cb    :要上报的CB字段
             en_frame_direction :接收还是发送
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_report_netbuf_cb(oal_uint8  *puc_user_mac_addr,
                                       oal_uint8  *puc_netbuf_cb,
                                       oam_ota_type_enum_uint8 en_ota_type)
{
    oal_uint32      ul_ret;

    if (OAL_PTR_NULL == puc_user_mac_addr || OAL_PTR_NULL == puc_netbuf_cb)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (en_ota_type >= OAM_OTA_TYPE_BUTT)
    {
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    /* 流控判断 */
    if (OAM_RATELIMIT_NOT_OUTPUT == oam_log_ratelimit(OAM_RATELIMIT_TYPE_CB))
    {
        return OAL_SUCC;
    }
    ul_ret = oam_report_netbuf_cb_to_sdt(puc_user_mac_addr, puc_netbuf_cb, en_ota_type);

    return ul_ret;
}
#if 0
/*****************************************************************************
 函 数 名  : oam_report_timer_track_to_sdt
 功能描述  : 将定时器创建删除时的行号文件号上报sdt
 输入参数  : ul_file_id:文件号
             ul_line_num:行号
             en_type:表明是创建还是删除定时器
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  oam_report_timer_track_to_sdt(
                                        oal_uint32 ul_file_id,
                                        oal_uint32 ul_line_num,
                                        oam_timer_track_type_enum_uint8 en_type)
{
    oal_uint32                  ul_tick;
    oal_uint16                  us_ota_data_len;
    oal_uint16                  us_skb_len;
    oal_netbuf_stru            *pst_netbuf;
    oam_ota_stru               *pst_ota_data;
    oal_uint32                  ul_ret     = OAL_SUCC;
    oam_timer_track_info_stru   st_timer_track_info;
    oal_uint8                   auc_macaddr[WLAN_MAC_ADDR_LEN] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

    if (OAL_UNLIKELY(OAL_PTR_NULL == g_st_oam_sdt_func_hook.p_sdt_report_data_func))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    us_skb_len = OAL_SIZEOF(st_timer_track_info)
               + OAL_SIZEOF(oam_ota_hdr_stru) + OAM_RESERVE_SKB_LEN;
    us_ota_data_len = OAL_SIZEOF(st_timer_track_info) + OAL_SIZEOF(oam_ota_hdr_stru);

    pst_netbuf = oal_mem_sdt_netbuf_alloc(us_skb_len, OAL_TRUE);
    if (OAL_PTR_NULL == pst_netbuf)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }
    oal_netbuf_reserve(pst_netbuf, OAM_RESERVE_SKB_HEADROOM_LEN);

    oal_netbuf_put(pst_netbuf, us_ota_data_len);
    pst_ota_data = (oam_ota_stru *)oal_netbuf_data(pst_netbuf);

    /* 获取系统TICK值 */
    ul_tick = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    /* 填写ota消息头结构体 */
    pst_ota_data->st_ota_hdr.ul_tick     = ul_tick;
    pst_ota_data->st_ota_hdr.en_ota_type = OAM_OTA_TYPE_TIMER_TRACK;
    pst_ota_data->st_ota_hdr.us_ota_data_len = OAL_SIZEOF(st_timer_track_info);
    pst_ota_data->st_ota_hdr.uc_frame_hdr_len = 0;
    oal_set_mac_addr(pst_ota_data->st_ota_hdr.auc_user_macaddr, auc_macaddr);
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
    pst_ota_data->st_ota_hdr.auc_resv[0]    = 2;
#else
    pst_ota_data->st_ota_hdr.auc_resv[0]    = 3;
#endif

    st_timer_track_info.ul_file_id  = ul_file_id;
    st_timer_track_info.ul_line_num = ul_line_num;
    st_timer_track_info.en_type     = en_type;

    /* 复制数据,填写ota数据 */
    oal_memcopy((oal_void *)pst_ota_data->auc_ota_data,
                (const oal_void *)&st_timer_track_info,
                OAL_SIZEOF(st_timer_track_info));

    /* 上报SDT */
    ul_ret = oam_report_data2sdt(pst_netbuf, OAM_DATA_TYPE_OTA, OAM_PRIMID_TYPE_OUTPUT_CONTENT);

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : oam_report_timer_track
 功能描述  : 将定时器创建删除时的行号文件号上报sdt
 输入参数  : ul_file_id:文件号
             ul_line_num:行号
             en_type:表明是创建还是删除定时器
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_report_timer_track(oal_uint32 ul_file_id,
                                        oal_uint32 ul_line_num,
                                        oam_timer_track_type_enum_uint8 en_type)
{
    if (OAL_UNLIKELY(ul_file_id >= OAM_FILE_ID_BUTT || en_type >= OAM_TIMER_TRACK_TYPE_BUTT))
    {
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    /* 检查开关 */
    if (OAL_SWITCH_OFF == oam_report_get_switch(OAM_OTA_TYPE_TIMER_TRACK))
    {
        return OAL_SUCC;
    }

    return oam_report_timer_track_to_sdt(ul_file_id, ul_line_num, en_type);
}
#endif
/*****************************************************************************
 函 数 名  : oam_report_mpdu_num_to_sdt
 功能描述  : 上报mpdu数目到sdt
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  oam_report_mpdu_num_to_sdt(
                                        oal_uint8  *puc_user_mac_addr,
                                        oam_report_mpdu_num_stru *pst_mpdu_num)
{
    oal_uint32                  ul_tick;
    oal_uint16                  us_ota_data_len;
    oal_uint16                  us_skb_len;
    oal_netbuf_stru            *pst_netbuf;
    oam_ota_stru               *pst_ota_data;
    oal_uint32                  ul_ret     = OAL_SUCC;

    if (OAL_UNLIKELY(OAL_PTR_NULL == g_st_oam_sdt_func_hook.p_sdt_report_data_func))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    us_skb_len = OAL_SIZEOF(oam_report_mpdu_num_stru)
               + OAL_SIZEOF(oam_ota_hdr_stru) + OAM_RESERVE_SKB_LEN;
    us_ota_data_len = OAL_SIZEOF(oam_report_mpdu_num_stru) + OAL_SIZEOF(oam_ota_hdr_stru);

    pst_netbuf = oal_mem_sdt_netbuf_alloc(us_skb_len, OAL_TRUE);
    if (OAL_PTR_NULL == pst_netbuf)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }
    oal_netbuf_reserve(pst_netbuf, OAM_RESERVE_SKB_HEADROOM_LEN);

    oal_netbuf_put(pst_netbuf, us_ota_data_len);
    pst_ota_data = (oam_ota_stru *)oal_netbuf_data(pst_netbuf);

    /* 获取系统TICK值 */
    ul_tick = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    /* 填写ota消息头结构体 */
    pst_ota_data->st_ota_hdr.ul_tick     = ul_tick;
    pst_ota_data->st_ota_hdr.en_ota_type = OAM_OTA_TYPE_MPDU_NUM;
    pst_ota_data->st_ota_hdr.us_ota_data_len = OAL_SIZEOF(oam_report_mpdu_num_stru);
    pst_ota_data->st_ota_hdr.uc_frame_hdr_len = 0;
    oal_set_mac_addr(pst_ota_data->st_ota_hdr.auc_user_macaddr, puc_user_mac_addr);
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
    pst_ota_data->st_ota_hdr.auc_resv[0]    = 2;
#else
    pst_ota_data->st_ota_hdr.auc_resv[0]    = 3;
#endif

    /* 复制数据,填写ota数据 */
    oal_memcopy((oal_void *)pst_ota_data->auc_ota_data,
                (const oal_void *)pst_mpdu_num,
                OAL_SIZEOF(oam_report_mpdu_num_stru));

    /* 上报SDT */
    ul_ret = oam_report_data2sdt(pst_netbuf, OAM_DATA_TYPE_OTA, OAM_PRIMID_TYPE_OUTPUT_CONTENT);

    return ul_ret;
}


/*****************************************************************************
 函 数 名  : oam_report_mpdu_num
 功能描述  : 上报mpdu数目
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_report_mpdu_num(oal_uint8  *puc_user_mac_addr,
                                        oam_report_mpdu_num_stru *pst_mpdu_num)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == puc_user_mac_addr || OAL_PTR_NULL == pst_mpdu_num))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    return oam_report_mpdu_num_to_sdt(puc_user_mac_addr, pst_mpdu_num);
}

/*****************************************************************************
 函 数 名  : oam_report_dft_params_to_sdt
 功能描述  : 将维测信息数据上报sdt
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_report_dft_params_to_sdt(
                                        oal_uint8  *puc_user_mac_addr,
                                        oal_uint8  *puc_param,
                                        oal_uint16  us_param_len,
                                        oam_ota_type_enum_uint8 en_type)
{
    oal_uint32                  ul_tick;
    oal_uint16                  us_ota_data_len;
    oal_uint16                  us_skb_len;
    oal_netbuf_stru            *pst_netbuf;
    oam_ota_stru               *pst_ota_data;
    oal_uint32                  ul_ret     = OAL_SUCC;

    if (OAL_UNLIKELY(OAL_PTR_NULL == g_st_oam_sdt_func_hook.p_sdt_report_data_func))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    us_ota_data_len = us_param_len + OAL_SIZEOF(oam_ota_hdr_stru);
    us_skb_len = us_ota_data_len + OAM_RESERVE_SKB_LEN;

    pst_netbuf = oal_mem_sdt_netbuf_alloc(us_skb_len, OAL_TRUE);
    if (OAL_PTR_NULL == pst_netbuf)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }
    oal_netbuf_reserve(pst_netbuf, OAM_RESERVE_SKB_HEADROOM_LEN);

    oal_netbuf_put(pst_netbuf, us_ota_data_len);
    pst_ota_data = (oam_ota_stru *)oal_netbuf_data(pst_netbuf);

    /* 获取系统TICK值 */
    ul_tick = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    /* 填写ota消息头结构体 */
    pst_ota_data->st_ota_hdr.ul_tick     = ul_tick;
    pst_ota_data->st_ota_hdr.en_ota_type = en_type;
    pst_ota_data->st_ota_hdr.us_ota_data_len = us_param_len;
    pst_ota_data->st_ota_hdr.uc_frame_hdr_len = 0;
    oal_set_mac_addr(pst_ota_data->st_ota_hdr.auc_user_macaddr, puc_user_mac_addr);
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
    pst_ota_data->st_ota_hdr.auc_resv[0]    = 2;
#else
    pst_ota_data->st_ota_hdr.auc_resv[0]    = 3;
#endif

    /* 复制数据,填写ota数据 */
    oal_memcopy((oal_void *)pst_ota_data->auc_ota_data,
                (const oal_void *)puc_param,
                us_param_len);

    /* 上报SDT */
    ul_ret = oam_report_data2sdt(pst_netbuf, OAM_DATA_TYPE_OTA, OAM_PRIMID_TYPE_OUTPUT_CONTENT);

    return ul_ret;
}


/*****************************************************************************
 函 数 名  : oam_report_phy_stat
 功能描述  : 上报维测信息数据
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_report_dft_params(oal_uint8  *puc_user_mac_addr,
                                        oal_uint8  *puc_param,
                                        oal_uint16  us_param_len,
                                        oam_ota_type_enum_uint8 en_type)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == puc_user_mac_addr || OAL_PTR_NULL == puc_param))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (en_type >= OAM_OTA_TYPE_BUTT)
    {
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    if (0 != us_param_len)
    {
        return oam_report_dft_params_to_sdt(puc_user_mac_addr, puc_param, us_param_len, en_type);
    }

    return OAL_ERR_CODE_INVALID_CONFIG;
}



/*****************************************************************************
 函 数 名  : oam_report_set_all_switch
 功能描述  : 设置所有用户帧上报的所有开关，如果是1，则上报所有类型帧的帧内容，
             cb字段，描述符；如果是0，则什么都不上报
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_report_set_all_switch(oal_switch_enum_uint8 en_switch)
{
    oal_uint8   uc_vapid_loop;

    if (OAL_SWITCH_OFF == en_switch)
    {
        OAL_MEMZERO(&g_st_oam_mng_ctx.st_user_track_ctx, OAL_SIZEOF(oam_user_track_ctx_stru));

        /* 关闭接收描述符打印 */
        for (uc_vapid_loop = 0; uc_vapid_loop < WLAN_VAP_SUPPORT_MAX_NUM_LIMIT; uc_vapid_loop++)
        {
#if 0
            oam_ota_set_switch(uc_vapid_loop, OAL_SWITCH_OFF, OAM_OTA_TYPE_RX_DSCR);
#endif
            oam_ota_set_beacon_switch(uc_vapid_loop, OAL_SWITCH_OFF);
            /* 设置rx描述符打印开关为关闭 */
            oam_ota_set_rx_dscr_switch(uc_vapid_loop, OAL_SWITCH_OFF);
        }
    }
    else
    {
        oal_memset(&g_st_oam_mng_ctx.st_user_track_ctx, OAL_SWITCH_ON, OAL_SIZEOF(oam_user_track_ctx_stru));

        /* 打开接收描述符打印 */
        for (uc_vapid_loop = 0; uc_vapid_loop < WLAN_VAP_SUPPORT_MAX_NUM_LIMIT; uc_vapid_loop++)
        {
#if 0
            oam_ota_set_switch(uc_vapid_loop, OAL_SWITCH_ON, OAM_OTA_TYPE_RX_DSCR);
#endif
            oam_ota_set_beacon_switch(uc_vapid_loop, OAL_SWITCH_OFF);
            /* 设置rx描述符打印开关为关闭 */
            oam_ota_set_rx_dscr_switch(uc_vapid_loop, OAL_SWITCH_OFF);
        }

    }

    return OAL_SUCC;
}



/*lint -e19*/
oal_module_symbol(oam_event_set_switch);
oal_module_symbol(oam_event_get_switch);
oal_module_symbol(oam_event_report);
oal_module_symbol(oam_ota_report);
oal_module_symbol(oam_event_set_specific_type_switch);
#if 0
oal_module_symbol(oam_ota_set_switch);
#endif
oal_module_symbol(oam_ota_set_beacon_switch);
oal_module_symbol(oam_ota_set_rx_dscr_switch);
oal_module_symbol(oam_ota_report_to_std);
oal_module_symbol(oam_report_dscr);
oal_module_symbol(oam_report_beacon);
oal_module_symbol(oam_report_eth_frame);
oal_module_symbol(oam_report_80211_frame);
oal_module_symbol(oam_ota_get_beacon_switch);
oal_module_symbol(oam_ota_get_rx_dscr_switch);
oal_module_symbol(oam_report_eth_frame_set_switch);
oal_module_symbol(oam_report_eth_frame_get_switch);
oal_module_symbol(oam_report_80211_mcast_set_switch);
oal_module_symbol(oam_report_80211_mcast_get_switch);
oal_module_symbol(oam_report_80211_ucast_set_switch);
oal_module_symbol(oam_report_80211_ucast_get_switch);
oal_module_symbol(oam_report_80211_probe_set_switch);
oal_module_symbol(oam_report_80211_probe_get_switch);
oal_module_symbol(oam_report_netbuf_cb);
#if 0
oal_module_symbol(oam_report_get_switch);
#endif
#if 0
oal_module_symbol(oam_report_timer_track);
#endif
oal_module_symbol(oam_report_mpdu_num);
oal_module_symbol(oam_report_set_all_switch);
oal_module_symbol(oam_report_dhcp_arp_get_switch);
oal_module_symbol(oam_report_dhcp_arp_set_switch);
oal_module_symbol(oam_report_dft_params);
oal_module_symbol(oam_report_data_get_global_switch);


#elif (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)

#endif

















#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

