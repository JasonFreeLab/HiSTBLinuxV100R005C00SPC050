/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : wal_linux_event.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2013年8月26日
  最近修改   :
  功能描述   : linux与驱动的接口函数，封装消息，抛事件给驱动；接收从驱动抛上来的事件，解析消息
  函数列表   :
  修改历史   :
  1.日    期   : 2013年8月26日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "frw_ext_if.h"
#include "wal_linux_ioctl.h"
#include "wal_main.h"
#include "wal_config.h"




#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_WAL_LINUX_EVENT_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : wal_cfg80211_start_req
 功能描述  : 向wal抛事件
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月4日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 wal_cfg80211_start_req(oal_net_device_stru    *pst_net_dev,
                                void                        *ps_param,
                                oal_uint16                   us_len,
                                wlan_cfgid_enum_uint16       en_wid,
                                oal_bool_enum_uint8          en_need_rsp)
{
    wal_msg_write_stru              st_write_msg;
    wal_msg_stru                   *pst_rsp_msg = OAL_PTR_NULL;
    oal_uint32                      ul_err_code;
    oal_int32                       l_ret;

    if (OAL_PTR_NULL == ps_param )
    {
         OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{wal_cfg80211_start_req::param is null!}\r\n");
         return OAL_ERR_CODE_PTR_NULL;
    }

    /* 填写 msg 消息头*/
    st_write_msg.en_wid = en_wid;
    st_write_msg.us_len = us_len;

    /* 填写 msg 消息体 */
    if(WAL_MSG_WRITE_MAX_LEN < us_len)
    {
        OAM_ERROR_LOG2(0, OAM_SF_SCAN, "{wal_cfg80211_start_req::us_len %d > WAL_MSG_WRITE_MAX_LEN %d err!}\r\n", us_len, WAL_MSG_WRITE_MAX_LEN);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }
    oal_memcopy(st_write_msg.auc_value, ps_param, us_len);

    /***************************************************************************
           抛事件到wal层处理
    ***************************************************************************/
    l_ret = wal_send_cfg_event(pst_net_dev,
                           WAL_MSG_TYPE_WRITE,
                           WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                           (oal_uint8 *)&st_write_msg,
                           en_need_rsp,
                           en_need_rsp ? &pst_rsp_msg : OAL_PTR_NULL);
    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_SCAN, "{wal_cfg80211_start_req::wal_send_cfg_event return err code %d!}\r\n", l_ret);
        return l_ret;
    }

    if(en_need_rsp && (OAL_PTR_NULL != pst_rsp_msg))
    {
        /* 读取返回的错误码 */
        ul_err_code = wal_check_and_release_msg_resp(pst_rsp_msg);
        if(OAL_SUCC != ul_err_code)
        {
            OAM_WARNING_LOG1(0, OAM_SF_SCAN, "{wal_cfg80211_start_req::wal_send_cfg_event return err code:[%u]}",
                           ul_err_code);
            return -OAL_EFAIL;
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : wal_cfg80211_start_scan
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月30日
    作    者   : 
    修改内容   : 新生成函数

  2.日    期   : 2014年1月4日
    作    者   : 
    修改内容   : 重构

*****************************************************************************/
oal_uint32  wal_cfg80211_start_scan(oal_net_device_stru *pst_net_dev, mac_cfg80211_scan_param_stru *pst_scan_param)
{
    mac_cfg80211_scan_param_stru    *pst_mac_cfg80211_scan_param;
    oal_uint32                       ul_ret = 0;

    if (OAL_PTR_NULL == pst_scan_param)
    {
         OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{wal_cfg80211_start_scan::scan failed, null ptr, pst_scan_param = null.}\r\n");
         return OAL_ERR_CODE_PTR_NULL;
    }

    /* 此处申请hmac层释放 */
    pst_mac_cfg80211_scan_param = (mac_cfg80211_scan_param_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(mac_cfg80211_scan_param_stru), OAL_FALSE);
    if (NULL == pst_mac_cfg80211_scan_param)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{wal_cfg80211_start_scan::scan failed, alloc scan param memory failed!}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    oal_memcopy(pst_mac_cfg80211_scan_param, pst_scan_param, OAL_SIZEOF(mac_cfg80211_scan_param_stru));

    /* TBD gong: 1.传的是指针的指针, 2.sizeof指针  */
    ul_ret = (oal_uint32)wal_cfg80211_start_req(pst_net_dev, &pst_mac_cfg80211_scan_param,
                                    OAL_SIZEOF(pst_mac_cfg80211_scan_param), WLAN_CFGID_CFG80211_START_SCAN, OAL_FALSE);
    if(OAL_SUCC != ul_ret)
    {
        /* 下发扫描失败，释放 */
        OAL_MEM_FREE(pst_mac_cfg80211_scan_param, OAL_FALSE);
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : wal_cfg80211_start_sched_scan
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  wal_cfg80211_start_sched_scan(oal_net_device_stru *pst_net_dev, mac_pno_scan_stru *pst_pno_scan_info)
{
    mac_pno_scan_stru      *pst_pno_scan_params;
    oal_uint32              ul_ret = 0;
    /* 申请pno调度扫描参数，此处申请hmac层释放 */
    pst_pno_scan_params = (mac_pno_scan_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(mac_pno_scan_stru), OAL_FALSE);
    if (OAL_PTR_NULL == pst_pno_scan_params)
    {
        OAM_WARNING_LOG0(0, OAM_SF_SCAN, "{wal_cfg80211_start_sched_scan::alloc pno scan param memory failed!}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    oal_memcopy(pst_pno_scan_params, pst_pno_scan_info, OAL_SIZEOF(mac_pno_scan_stru));

    ul_ret = (oal_uint32)wal_cfg80211_start_req(pst_net_dev, &pst_pno_scan_params,
                                    OAL_SIZEOF(pst_pno_scan_params), WLAN_CFGID_CFG80211_START_SCHED_SCAN, OAL_TRUE);

    if(OAL_SUCC != ul_ret)
    {
        OAL_MEM_FREE(pst_pno_scan_params, OAL_FALSE);
        return ul_ret;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : wal_cfg80211_start_connect
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月30日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32  wal_cfg80211_start_connect(oal_net_device_stru *pst_net_dev, mac_cfg80211_connect_param_stru *pst_mac_cfg80211_connect_param)
{
    return wal_cfg80211_start_req(pst_net_dev,
                pst_mac_cfg80211_connect_param,
                OAL_SIZEOF(mac_cfg80211_connect_param_stru),
                WLAN_CFGID_CFG80211_START_CONNECT,
                OAL_TRUE);
}

/*****************************************************************************
 函 数 名  : wal_cfg80211_start_disconnect
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月30日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32  wal_cfg80211_start_disconnect(oal_net_device_stru *pst_net_dev, mac_cfg_kick_user_param_stru *pst_disconnect_param)
{
    /* 注意 由于消息未真正处理就直接返回，导致WPA_SUPPLICANT继续下发消息，在驱动侧等到处理时被异常唤醒，导致后续下发的消息误以为操作失败，
       目前将去关联事件修改为等待消息处理结束后再上报，最后一个入参由OAL_FALSE改为OAL_TRUE */
    return wal_cfg80211_start_req(pst_net_dev, pst_disconnect_param, OAL_SIZEOF(mac_cfg_kick_user_param_stru), WLAN_CFGID_KICK_USER, OAL_TRUE);
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

