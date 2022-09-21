/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hwal_app_ioctl.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2016年6月27日
  最近修改   :
  功能描述   : Hwal适配层，连接应用侧APP与driver的通道
  函数列表   :
  修改历史   :
  1.日    期   : 2016年6月27日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#include "wal_config.h"
#include "hwal_app_ioctl.h"
#ifdef _PRE_WLAN_FEATURE_TCP_UDP_KEEPALIVE
#include "hmac_tcp_udp_keepalive.h"
#endif
extern oal_int32 wal_cfg80211_set_channel_info(oal_wiphy_stru *pst_wiphy, oal_net_device_stru *pst_netdev);
#ifdef _PRE_WLAN_FEATURE_TCP_UDP_KEEPALIVE
extern hmac_tcp_udp_conn_stru g_st_tcp_udp_conn;
#endif
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
hwal_app_ioctl_handler g_ast_hwal_app_ioctl_handlers[] =
{
    (hwal_app_ioctl_handler) hwal_ioctl_set_freq,
#ifdef _PRE_WLAN_FEATURE_HILINK
    (hwal_app_ioctl_handler) hwal_ioctl_set_monitor,
#endif
    (hwal_app_ioctl_handler) hwal_ioctl_set_freq_40m,
#ifdef _PRE_WLAN_FEATURE_TCP_UDP_KEEPALIVE
    (hwal_app_ioctl_handler) hwal_ioctl_get_tcp_params,
    (hwal_app_ioctl_handler) hwal_ioctl_set_tcp_params
#endif
};

/*****************************************************************************
 函 数 名  : hwal_ioctl_set_freq
 功能描述  : 设置信道
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年7月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hwal_ioctl_set_freq(oal_int8 *puc_ifname, oal_void *p_buf)
{
    oal_net_device_stru     *pst_netdev = OAL_PTR_NULL;
    wal_msg_write_stru       st_write_msg;
    oal_int32                l_ret;
    oal_uint32               ul_freq;

    if ((OAL_PTR_NULL == puc_ifname) || (OAL_PTR_NULL == p_buf))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "hwal_ioctl_set_freq::puc_ifname = %x,p_buf = %x",puc_ifname,p_buf);
        return OAL_ERR_CODE_PTR_NULL;
    }
    oal_memset(&st_write_msg, 0, sizeof(wal_msg_write_stru));
    pst_netdev = oal_dev_get_by_name(puc_ifname);
    if (OAL_PTR_NULL == pst_netdev)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "hwal_ioctl_set_freq::pst_netdev is null");
        return OAL_ERR_CODE_PTR_NULL;
    }
    ul_freq    = *(oal_uint32 *)p_buf;

    l_ret = mac_is_channel_num_valid(WLAN_BAND_2G, (oal_uint8)ul_freq);
    if (OAL_SUCC != l_ret)
    {
        OAM_WARNING_LOG1(0, 0, "channel %d is invable",ul_freq);
        return -OAL_EFAIL;
    }

    /***************************************************************************
        抛事件到wal层处理
    ***************************************************************************/
    /* 填写消息 */
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_CURRENT_CHANEL, OAL_SIZEOF(oal_uint32));
    *((oal_uint32 *)(st_write_msg.auc_value)) = ul_freq;

    /* 发送消息 */
    l_ret = wal_send_cfg_event(pst_netdev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hwal_ioctl_set_freq::return err code %d!}\r\n", l_ret);
        return l_ret;
    }

    return OAL_SUCC;
}
#ifdef _PRE_WLAN_FEATURE_HILINK
/*****************************************************************************
 函 数 名  : hwal_ioctl_set_monitor
 功能描述  : 设置monitor开关
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年6月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hwal_ioctl_set_monitor(oal_int8 *puc_ifname, oal_void *p_buf)
{
    oal_net_device_stru     *pst_netdev = OAL_PTR_NULL;
    oal_uint8                uc_monitor_mode;
    wal_msg_write_stru       st_write_msg;
    oal_int32                l_ret;

    if ((OAL_PTR_NULL == puc_ifname) || (OAL_PTR_NULL == p_buf))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "hwal_ioctl_set_monitor::puc_ifname = %x,p_buf = %x",puc_ifname,p_buf);
        return OAL_ERR_CODE_PTR_NULL;
    }
    oal_memset(&st_write_msg, 0, sizeof(wal_msg_write_stru));
    pst_netdev      = oal_dev_get_by_name(puc_ifname);
    if (OAL_PTR_NULL == pst_netdev)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "hwal_ioctl_set_monitor::pst_netdev is null");
        return OAL_ERR_CODE_PTR_NULL;
    }
    uc_monitor_mode = *(oal_uint8 *)p_buf;
    /***************************************************************************
                                抛事件到wal层处理
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_MONITOR_EN, OAL_SIZEOF(oal_uint8));
    *((oal_uint8 *)(st_write_msg.auc_value)) = uc_monitor_mode;   /* 设置配置命令参数 */

    l_ret = wal_send_cfg_event(pst_netdev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_uint8),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hwal_ioctl_set_monitor::return err code %d!}\r\n", l_ret);
        return l_ret;
    }

    return OAL_SUCC;
}
#endif
/*****************************************************************************
 函 数 名  : hwal_ioctl_set_freq_40m
 功能描述  : 设置信道
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年9月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hwal_ioctl_set_freq_40m(oal_int8 *puc_ifname, oal_void *p_buf)
{
    oal_net_device_stru            *pst_netdev;
    mac_cfg_channel_param_stru      st_channel_param;
    oal_uint8                       uc_channel;
    oal_uint8                       uc_channel_width;
    oal_int32                       l_ret;
    wlan_channel_bandwidth_enum_uint8 en_bandwidth;
    hilink_channel_stru            *pst_channel;
    mac_vap_stru                   *pst_mac_vap;
    oal_uint32                      ul_ret;

    if ((OAL_PTR_NULL == puc_ifname) || (OAL_PTR_NULL == p_buf))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "hwal_ioctl_set_freq::puc_ifname = %x,p_buf = %x",puc_ifname,p_buf);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_netdev = oal_dev_get_by_name(puc_ifname);
    if (OAL_PTR_NULL == pst_netdev)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "hwal_ioctl_set_freq::pst_netdev = %x",pst_netdev);
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_channel         = (hilink_channel_stru *)p_buf;
    uc_channel          = pst_channel->uc_channel_num;
    uc_channel_width    = pst_channel->uc_channel_bandwidth;
    pst_mac_vap = OAL_NET_DEV_PRIV(pst_netdev);
    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, 0, "hwal_ioctl_set_freq_40m::pst_mac_vap is null");
        return OAL_ERR_CODE_PTR_NULL;
    }

    l_ret = mac_is_channel_num_valid(WLAN_BAND_2G, uc_channel);
    if (OAL_SUCC != l_ret)
    {
        OAM_WARNING_LOG1(0, 0, "channel %d is invable",uc_channel);
        return -OAL_EFAIL;
    }
    if (((HISI_BAND_WIDTH_40PLUS == uc_channel_width) && (uc_channel > 9))
    || (HISI_BAND_WIDTH_40MINUS == uc_channel_width)&&(uc_channel < 5))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "hwal_ioctl_set_freq::uc_channel = %d,uc_channel_width = %d",uc_channel,uc_channel_width);
        return -OAL_EFAIL;
    }

    if (HISI_BAND_WIDTH_40PLUS == uc_channel_width)
    {
        en_bandwidth = WLAN_BAND_WIDTH_40PLUS;
    }
    else
    {
        en_bandwidth = WLAN_BAND_WIDTH_40MINUS;
    }
    st_channel_param.uc_channel     = uc_channel;
    st_channel_param.en_band        = 0;
    st_channel_param.en_bandwidth   = en_bandwidth;
    st_channel_param.uc_hilink_flag = OAL_SWITCH_ON;
    ul_ret = wal_config_set_channel(pst_mac_vap, OAL_SIZEOF(mac_cfg_channel_param_stru), &st_channel_param);
    if (OAL_SUCC != ul_ret)
    {
         OAM_ERROR_LOG1(0, 0, "hwal_ioctl_set_freq_40m::ul_ret = %d",ul_ret);
         return -OAL_EFAIL;
    }
    return OAL_SUCC;
}
#ifdef _PRE_WLAN_FEATURE_TCP_UDP_KEEPALIVE
/*****************************************************************************
 函 数 名  : hwal_ioctl_get_tcp_params
 功能描述  : 应用侧将TCP参数下发到hmac以便获取tcp详细的参数信息
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年10月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hwal_ioctl_get_tcp_params(oal_int8 *puc_ifname, oal_void *p_buf)
{
    hisi_tcp_params_stru           *pst_tcp_params;
    oal_uint8                       uc_index;

    if (OAL_PTR_NULL == p_buf)
    {
        OAM_ERROR_LOG0(0, 0, "hwal_ioctl_get_tcp_params::p_buf is null");
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_tcp_params = (hisi_tcp_params_stru *)p_buf;
    for (uc_index = 0; uc_index < HMAC_TCP_CONNECT_NUM; uc_index++)
    {
        OAM_WARNING_LOG2(0, OAM_SF_ANY, "hwal_ioctl_get_tcp_params::%d,%d",g_st_tcp_udp_conn.st_tcp_connects[uc_index].ul_sess_id,pst_tcp_params->ul_sess_id);
        if (g_st_tcp_udp_conn.st_tcp_connects[uc_index].ul_sess_id == pst_tcp_params->ul_sess_id)
        {
            return OAL_SUCC;
        }
        else if (0 == g_st_tcp_udp_conn.st_tcp_connects[uc_index].ul_sess_id)
        {
            g_st_tcp_udp_conn.st_tcp_connects[uc_index].ul_sess_id  = pst_tcp_params->ul_sess_id;
            g_st_tcp_udp_conn.st_tcp_connects[uc_index].us_src_port = pst_tcp_params->us_src_port;
            g_st_tcp_udp_conn.st_tcp_connects[uc_index].us_dst_port = pst_tcp_params->us_dst_port;
            OAM_WARNING_LOG3(0, OAM_SF_ANY, "sess_id = %d,src_port = %d,dst_port = %d",pst_tcp_params->ul_sess_id
                             ,pst_tcp_params->us_src_port,pst_tcp_params->us_dst_port);
            return OAL_SUCC;
        }
    }
    return -OAL_EFAIL;;
}
/*****************************************************************************
 函 数 名  : hwal_ioctl_set_tcp_params
 功能描述  : 应用侧下发TCP参数，以开启TCP keepalive特性
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年10月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hwal_ioctl_set_tcp_params(oal_int8 *puc_ifname, oal_void *p_buf)
{
    hisi_tcp_params_stru           *pst_tcp_params;
    oal_net_device_stru            *pst_netdev;
    wal_msg_write_stru              st_write_msg;
    oal_uint8                       uc_index;
    oal_int32                       l_ret;
    if ((OAL_PTR_NULL == puc_ifname) || (OAL_PTR_NULL == p_buf))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "hwal_ioctl_set_tcp_params::puc_ifname = %x,p_buf = %x",puc_ifname,p_buf);
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_netdev = oal_dev_get_by_name(puc_ifname);
    if (OAL_PTR_NULL == pst_netdev)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "hwal_ioctl_set_tcp_params::pst_netdev = %x",pst_netdev);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_tcp_params = (hisi_tcp_params_stru *)p_buf;

    for (uc_index = 0; uc_index < HMAC_TCP_CONNECT_NUM; uc_index++)
    {
        if (g_st_tcp_udp_conn.st_tcp_connects[uc_index].ul_sess_id == pst_tcp_params->ul_sess_id)
        {
            pst_tcp_params->ul_seq_num      = g_st_tcp_udp_conn.st_tcp_connects[uc_index].ul_seq_num;
            pst_tcp_params->ul_ack_num      = g_st_tcp_udp_conn.st_tcp_connects[uc_index].ul_ack_num;
            oal_set_mac_addr(pst_tcp_params->uc_dst_mac, g_st_tcp_udp_conn.st_tcp_connects[uc_index].uc_dst_mac);
            OAM_WARNING_LOG0(0, OAM_SF_ANY, "hwal_ioctl_set_tcp_params::create a tcp keepalive");
            OAL_MEMZERO(&(g_st_tcp_udp_conn.st_tcp_connects[uc_index]), OAL_SIZEOF(hmac_tcp_params_stru));
            /* 抛事件到wal层 */
            WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_TCP_UDP_PARAMS, OAL_SIZEOF(hmac_tcp_params_stru));
            oal_memcopy(st_write_msg.auc_value, pst_tcp_params, OAL_SIZEOF(hmac_tcp_params_stru));
            st_write_msg.us_len = OAL_SIZEOF(hmac_tcp_params_stru);
            l_ret = wal_send_cfg_event(pst_netdev,
                       WAL_MSG_TYPE_WRITE,
                       WAL_MSG_WRITE_MSG_HDR_LENGTH + st_write_msg.us_len,
                       (oal_uint8 *)&st_write_msg,
                       OAL_FALSE,
                       OAL_PTR_NULL);

            if (OAL_UNLIKELY(OAL_SUCC != l_ret))
            {
                OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hwal_ioctl_set_tcp_params::return err code %d!}\r\n", l_ret);
                return l_ret;
            }
            return OAL_SUCC;
        }
    }
    return -OAL_EFAIL;;
}
#endif
/*****************************************************************************
 函 数 名  : hwal_app_ioctl
 功能描述  : 驱动提供给app侧调用的ioctl总入口
 输入参数  : *puc_ifname netDev的名字,  *pst_cmd 下发的命令信息
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年7月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hwal_app_ioctl(oal_int8 *puc_ifname, hisi_ioctl_command_stru *pst_cmd)
{
    if ((OAL_PTR_NULL == puc_ifname) || (OAL_PTR_NULL == pst_cmd))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "hwal_app_ioctl::puc_ifname = %x,p_buf = %x",puc_ifname,pst_cmd);
        return OAL_ERR_CODE_PTR_NULL;
    }

    if ((pst_cmd->ul_cmd < HISI_IOCTL_BUTT) && (OAL_PTR_NULL != g_ast_hwal_app_ioctl_handlers[pst_cmd->ul_cmd]))
    {
        return g_ast_hwal_app_ioctl_handlers[pst_cmd->ul_cmd](puc_ifname, pst_cmd->p_buf);
    }
    OAM_ERROR_LOG1(0, 0, "hwal_app_ioctl ::The CMD[%d] handlers is NULL.\r\n",pst_cmd->ul_cmd);
    return -OAL_EFAIL;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif




