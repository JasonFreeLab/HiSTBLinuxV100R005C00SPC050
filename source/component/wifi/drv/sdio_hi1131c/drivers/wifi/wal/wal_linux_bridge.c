/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : wal_linux_bridge.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年11月19日
  最近修改   :
  功能描述   : WAL linux桥接文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年11月19日
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
#include "oal_profiling.h"
#include "oam_ext_if.h"
#include "frw_ext_if.h"
#include "wlan_spec.h"

#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX
#include "hal_ext_if.h"
#endif

#include "hmac_vap.h"
#include "mac_vap.h"
#include "mac_resource.h"
#include "mac_data.h"
#include "hmac_ext_if.h"

#ifdef _PRE_WLAN_FEATURE_SMP_SUPPORT
#include "hmac_vap.h"
#endif

#include "wal_main.h"
#include "wal_linux_bridge.h"

#ifdef _PRE_WLAN_FEATURE_BTCOEX
#include "hmac_device.h"
#include "hmac_resource.h"
#endif

#ifdef _PRE_WLAN_FEATURE_WOW
#include "hmac_wow.h"
#endif

#ifdef _PRE_WLAN_FEATURE_TCP_UDP_KEEPALIVE
#include "hmac_tcp_udp_keepalive.h"
#endif
#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_WAL_LINUX_BRIDGE_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_SMP_SUPPORT

/*****************************************************************************
 函 数 名  : wal_vap_start_xmit
 功能描述  : 挂接到VAP对应net_device结构体下的发送函数
 输入参数  : pst_buf: SKB结构体,其中data指针指向以太网头
             pst_dev: net_device结构体
 输出参数  : 无
 返 回 值  : OAL_SUCC或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_net_dev_tx_enum  wal_vap_start_xmit(oal_netbuf_stru *pst_buf, oal_net_device_stru *pst_dev)
{

    mac_vap_stru   *pst_vap;
    hmac_vap_stru  *pst_hmac_vap;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dev))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{wal_vap_start_xmit::pst_dev = OAL_PTR_NULL!}\r\n");
        oal_netbuf_free(pst_buf);
        OAM_STAT_VAP_INCR(0, tx_abnormal_msdu_dropped, 1);
        return OAL_NETDEV_TX_OK;
    }

    /* 获取VAP结构体 */
    pst_vap = (mac_vap_stru *)OAL_NET_DEV_PRIV(pst_dev);

    /* 如果VAP结构体不存在，则丢弃报文 */
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{wal_vap_start_xmit::pst_vap = OAL_PTR_NULL!}\r\n");
        oal_netbuf_free(pst_buf);
        OAM_STAT_VAP_INCR(0, tx_abnormal_msdu_dropped, 1);
        return OAL_NETDEV_TX_OK;
    }

     pst_buf = oal_netbuf_unshare(pst_buf, GFP_ATOMIC);
    if (pst_buf == OAL_PTR_NULL)
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{wal_vap_start_xmit::the unshare netbuf = OAL_PTR_NULL!}\r\n");
        return OAL_NETDEV_TX_OK;
    }

    pst_hmac_vap = mac_res_get_hmac_vap(pst_vap->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG1(0, OAM_SF_TX, "{wal_vap_start_xmit::pst_hmac_vap[%d] = OAL_PTR_NULL!}", pst_vap->uc_vap_id);
        oal_netbuf_free(pst_buf);
        OAM_STAT_VAP_INCR(0, tx_abnormal_msdu_dropped, 1);
        return OAL_NETDEV_TX_OK;
    }

    /* 防止下行来包太多，造成软件处理来不及，造成软件积累包太多，skb内存不能及时释放，入队限制修改为300，MIPS降低后，这个值可以抬高 */
    if(OAL_NETBUF_LIST_NUM(&pst_hmac_vap->st_tx_queue_head[pst_hmac_vap->uc_in_queue_id])>=300)
    {
        /* 关键帧做100个缓存，保证关键帧的正常发送 */
        if(OAL_NETBUF_LIST_NUM(&pst_hmac_vap->st_tx_queue_head[pst_hmac_vap->uc_in_queue_id]) < 400)
        {
            oal_uint8   uc_data_type;

            uc_data_type = mac_get_data_type_from_8023((oal_uint8 *)oal_netbuf_payload(pst_buf), MAC_NETBUFF_PAYLOAD_ETH);
            if((MAC_DATA_EAPOL == uc_data_type) || (MAC_DATA_DHCP == uc_data_type) || (MAC_DATA_ARP_REQ == uc_data_type)|| (MAC_DATA_ARP_RSP == uc_data_type))
            {
                oal_spin_lock_bh(&pst_hmac_vap->st_smp_lock);
                OAL_NETBUF_QUEUE_TAIL(&(pst_hmac_vap->st_tx_queue_head[pst_hmac_vap->uc_in_queue_id]),pst_buf);
                oal_spin_unlock_bh(&pst_hmac_vap->st_smp_lock);
            }
            else
            {
                oal_netbuf_free(pst_buf);
            }
        }
        else
        {
            oal_netbuf_free(pst_buf);
        }

        if(g_tx_debug)
        {
            /* 增加维测信息，把tx_event_num的值打印出来，用户关连不上，或者一直ping不通，打开g_tx_debug开关，如果此时的值不为1，就属于异常 */
            OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_TX, "{wal_vap_start_xmit::tx_event_num value is [%d].}", (oal_int32)oal_atomic_read(&(pst_hmac_vap->ul_tx_event_num)));
            OAL_IO_PRINT("wal_vap_start_xmit too fast\n");
        }
    }
    else
    {
        if(g_tx_debug)
            OAL_IO_PRINT("wal_vap_start_xmit enqueue and post event\n");

        oal_spin_lock_bh(&pst_hmac_vap->st_smp_lock);
        OAL_NETBUF_QUEUE_TAIL(&(pst_hmac_vap->st_tx_queue_head[pst_hmac_vap->uc_in_queue_id]),pst_buf);
        oal_spin_unlock_bh(&pst_hmac_vap->st_smp_lock);
    }

    hmac_tx_post_event(pst_vap);

    return OAL_NETDEV_TX_OK;
}

#endif

/*****************************************************************************
 函 数 名  : wal_bridge_vap_xmit
 功能描述  : 挂接到VAP对应net_device结构体下的发送函数
 输入参数  : pst_buf: SKB结构体,其中data指针指向以太网头
             pst_dev: net_device结构体
 输出参数  : 无
 返 回 值  : OAL_SUCC或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_net_dev_tx_enum  wal_bridge_vap_xmit(oal_netbuf_stru *pst_buf, oal_net_device_stru *pst_dev)
{
    mac_vap_stru                *pst_vap;
    hmac_vap_stru               *pst_hmac_vap;
    oal_uint32                   ul_ret;
#ifdef _PRE_WLAN_FEATURE_ROAM
    oal_uint8                    uc_data_type;
#endif

#if defined(_PRE_WLAN_FEATURE_PROXYSTA) ||  defined(_PRE_WLAN_FEATURE_ALWAYS_TX)
    mac_device_stru  *pst_mac_device;

#endif

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    hmac_device_stru *pst_hmac_device;
#endif

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_buf))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{wal_bridge_vap_xmit::pst_buf = OAL_PTR_NULL!}\r\n");
        return OAL_NETDEV_TX_OK;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dev))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{wal_bridge_vap_xmit::pst_dev = OAL_PTR_NULL!}\r\n");
        oal_netbuf_free(pst_buf);
        OAM_STAT_VAP_INCR(0, tx_abnormal_msdu_dropped, 1);
        return OAL_NETDEV_TX_OK;
    }

    /* 获取VAP结构体 */
    pst_vap = (mac_vap_stru *)OAL_NET_DEV_PRIV(pst_dev);

    /* 如果VAP结构体不存在，则丢弃报文 */
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{wal_bridge_vap_xmit::pst_vap = OAL_PTR_NULL!}\r\n");
        oal_netbuf_free(pst_buf);
        OAM_STAT_VAP_INCR(0, tx_abnormal_msdu_dropped, 1);
        return OAL_NETDEV_TX_OK;
    }

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_CFG, "{hmac_config_add_vap::pst_hmac_vap null.}");
        oal_netbuf_free(pst_buf);
        return OAL_NETDEV_TX_OK;
    }

#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX

    pst_mac_device = mac_res_get_dev(pst_vap->uc_device_id);
    if ( OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_PROXYSTA, "{wal_bridge_vap_xmit::mac_res_get_dev is null!}");
        oal_netbuf_free(pst_buf);

        return OAL_NETDEV_TX_OK;
    }

    /*代码待整改，pst_device_stru指针切换未状态, 长发长收切换未本地状态*/
    if ((OAL_SWITCH_ON == pst_vap->bit_al_tx_flag)
    || ((pst_mac_device->pst_device_stru != OAL_PTR_NULL) && (HAL_ALWAYS_TX_AMPDU_ENABLE == pst_mac_device->pst_device_stru->bit_al_tx_flag)))
    //|| (HAL_ALWAYS_RX_DISABLE != pst_mac_device->pst_device_stru->bit_al_rx_flag))
    {
        OAM_INFO_LOG0(pst_vap->uc_vap_id, OAM_SF_TX, "{wal_bridge_vap_xmit::the vap alway tx/rx!}\r\n");
        oal_netbuf_free(pst_buf);
        return OAL_NETDEV_TX_OK;
    }
#endif

    pst_buf = oal_netbuf_unshare(pst_buf, GFP_ATOMIC);
    if (OAL_UNLIKELY(pst_buf == OAL_PTR_NULL))
    {
        OAM_INFO_LOG0(pst_vap->uc_vap_id, OAM_SF_TX, "{wal_bridge_vap_xmit::the unshare netbuf = OAL_PTR_NULL!}\r\n");
        return OAL_NETDEV_TX_OK;
    }

    /* 将以太网过来的帧上报SDT */
    hmac_tx_report_eth_frame(pst_vap, pst_buf);
    /* 获取TCP链路的参数信息 */
    hmac_get_tcp_params(pst_buf);
    if(OAL_GET_THRUPUT_BYPASS_ENABLE(OAL_TX_LINUX_BYPASS))
    {
        oal_netbuf_free(pst_buf);
        return OAL_NETDEV_TX_OK;
    }

    /* 考虑VAP状态与控制面互斥，需要加锁保护 */
    oal_spin_lock_bh(&pst_hmac_vap->st_lock_state);

#ifdef _PRE_WLAN_FEATURE_WOW
    /* wow 过滤开关 */
    if(OAL_TRUE == hmac_wow_tx_check_filter_switch())
    {
        oal_netbuf_free(pst_buf);
        oal_spin_unlock_bh(&pst_hmac_vap->st_lock_state);
        return OAL_NETDEV_TX_OK;
    }
#endif //_PRE_WLAN_FEATURE_WOW

    /* 判断VAP的状态，如果ROAM，则丢弃报文 MAC_DATA_DHCP/MAC_DATA_ARP */
#ifdef _PRE_WLAN_FEATURE_ROAM
    if(MAC_VAP_STATE_ROAMING == pst_vap->en_vap_state)
    {
        uc_data_type =  mac_get_data_type_from_8023((oal_uint8 *)oal_netbuf_payload(pst_buf), MAC_NETBUFF_PAYLOAD_ETH);
        if(MAC_DATA_EAPOL != uc_data_type)
        {
            oal_netbuf_free(pst_buf);
            oal_spin_unlock_bh(&pst_hmac_vap->st_lock_state);
            return OAL_NETDEV_TX_OK;
        }
    }
    else
    {
#endif  //_PRE_WLAN_FEATURE_ROAM
    /* 判断VAP的状态，如果没有UP/PAUSE，则丢弃报文 */
    if (OAL_UNLIKELY(!((MAC_VAP_STATE_UP == pst_vap->en_vap_state) || (MAC_VAP_STATE_PAUSE == pst_vap->en_vap_state))))
    {
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
        /*filter the tx xmit pkts print*/
        if(MAC_VAP_STATE_INIT == pst_vap->en_vap_state || MAC_VAP_STATE_BUTT == pst_vap->en_vap_state)
        {
            OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_TX, "{wal_bridge_vap_xmit::vap state[%d] != MAC_VAP_STATE_{UP|PAUSE}!}\r\n", pst_vap->en_vap_state);
        }
        else
        {
            OAM_INFO_LOG1(pst_vap->uc_vap_id, OAM_SF_TX, "{wal_bridge_vap_xmit::vap state[%d] != MAC_VAP_STATE_{UP|PAUSE}!}\r\n", pst_vap->en_vap_state);
        }
#else
        OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_TX, "{wal_bridge_vap_xmit::vap state[%d] != MAC_VAP_STATE_{UP|PAUSE}!}\r\n", pst_vap->en_vap_state);
#endif
        oal_netbuf_free(pst_buf);
        OAM_STAT_VAP_INCR(pst_vap->uc_vap_id, tx_abnormal_msdu_dropped, 1);

        oal_spin_unlock_bh(&pst_hmac_vap->st_lock_state);
        return OAL_NETDEV_TX_OK;
    }
#ifdef _PRE_WLAN_FEATURE_ROAM
    }
#endif

    OAL_NETBUF_NEXT(pst_buf) = OAL_PTR_NULL;
    OAL_NETBUF_PREV(pst_buf) = OAL_PTR_NULL;

    OAL_MEMZERO(OAL_NETBUF_CB(pst_buf), OAL_NETBUF_CB_SIZE());

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    pst_mac_device = mac_res_get_dev(pst_vap->uc_device_id);
    if ( OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_PROXYSTA, "{wal_bridge_vap_xmit::mac_res_get_dev is null!}");
        oal_netbuf_free(pst_buf);
        oal_spin_unlock_bh(&pst_hmac_vap->st_lock_state);
        return OAL_NETDEV_TX_OK;
    }

    if (OAL_TRUE == pst_mac_device->st_cap_flag.bit_proxysta)
    {
        /* ARP、DHCP、ICMPv6等数据包的地址转换 (只有proxy STA的发送的包才需要地址转换)*/
        if ((OAL_TRUE == pst_vap->st_vap_proxysta.en_is_proxysta) && (OAL_FALSE == pst_vap->st_vap_proxysta.en_is_main_proxysta))
        {
            ul_ret = hmac_tx_proxysta_mat(pst_buf, pst_vap);

            if (OAL_SUCC != ul_ret)
            {
                OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_PROXYSTA, "{wal_bridge_vap_xmit::hmac_tx_proxysta_mat fail.}");
                oal_netbuf_free(pst_buf);
                oal_spin_unlock_bh(&pst_hmac_vap->st_lock_state);
                return OAL_NETDEV_TX_OK;
            }
        }
    }

#endif

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    pst_hmac_device = hmac_res_get_mac_dev(pst_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_hmac_device)
    {
        OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_PROXYSTA, "{wal_bridge_vap_xmit::mac_res_get_hmac_dev is null!}");
        oal_netbuf_free(pst_buf);
        oal_spin_unlock_bh(&pst_hmac_vap->st_lock_state);
        return OAL_NETDEV_TX_OK;
    }

    if((pst_hmac_device->st_dmac_to_hmac_btcoex_rx_delba.uc_ba_size > 0) && (pst_hmac_device->st_dmac_to_hmac_btcoex_rx_delba.uc_ba_size < WLAN_AMPDU_RX_BA_LUT_WSIZE))
    {
        /* 发送方向的arp_req 统计和删ba的处理 */
        hmac_btcoex_arp_fail_delba(pst_buf,pst_hmac_vap);
    }
#endif

    OAL_MIPS_TX_STATISTIC(HMAC_PROFILING_FUNC_BRIDGE_VAP_XMIT);
    ul_ret = hmac_tx_lan_to_wlan(pst_vap, pst_buf);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        /* 调用失败，要释放内核申请的netbuff内存池 */
        oal_netbuf_free(pst_buf);
    }

    oal_spin_unlock_bh(&pst_hmac_vap->st_lock_state);

    return OAL_NETDEV_TX_OK;
}

/*lint -e19*/
oal_module_symbol(wal_bridge_vap_xmit);
/*lint +e19*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

