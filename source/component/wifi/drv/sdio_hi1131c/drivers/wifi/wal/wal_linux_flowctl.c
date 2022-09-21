/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : wal_linux_flowctl.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2014年3月3日
  最近修改   :
  功能描述   : WAL flow ctrl文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年3月3日
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
#include "oal_util.h"
#include "frw_ext_if.h"

#include "wlan_spec.h"


#include "mac_vap.h"
#include "mac_device.h"
#include "mac_resource.h"

#include "hmac_ext_if.h"

#include "wal_main.h"
#include "wal_linux_flowctl.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_WAL_LINUX_FLOWCTL_C

#ifdef _PRE_WLAN_FEATURE_FLOWCTL

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
wal_macaddr_subq_stru g_ast_macaddr_map_subq[WLAN_VAP_MAX_NUM_PER_DEVICE_LIMIT][WAL_NETDEV_SUBQUEUE_MAX_NUM];

/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : wal_netdev_select_queue
 功能描述  : kernel给skb选择合适的tx subqueue;
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月4日
    作    者   : xiechunhui
    修改内容   : 新生成函数

*****************************************************************************/
#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 18, 0))
oal_uint16  wal_netdev_select_queue(oal_net_device_stru *pst_dev, oal_netbuf_stru *pst_buf)
#else
oal_uint16  wal_netdev_select_queue(oal_net_device_stru *pst_dev, oal_netbuf_stru *pst_buf, void *accel_priv, select_queue_fallback_t fallback)
#endif /* (LINUX_VERSION_CODE < KERNEL_VERSION(3, 18, 0)) */
{
    oal_ether_header_stru   *pst_ether_header   = OAL_PTR_NULL;
    mac_vap_stru            *pst_vap            = OAL_PTR_NULL;
    oal_uint16               us_assoc_id        = 0;
    oal_uint8                uc_tos             = 0;
    oal_uint8                uc_ac              = 0;
    oal_uint16               us_subq            = 0;
    oal_uint32               ul_ret             = OAL_SUCC;

    /* 获取以太网头 */
    pst_ether_header = (oal_ether_header_stru *)oal_netbuf_data(pst_buf);

    pst_vap = (mac_vap_stru *) OAL_NET_DEV_PRIV(pst_dev);

    /* 没有用户限速，则全部入index = 0 的subq, 并直接返回 */
    if (OAL_FALSE == pst_vap->bit_has_user_bw_limit)
    {
        return 0;
    }

    ul_ret = mac_vap_find_user_by_macaddr(pst_vap, pst_ether_header->auc_ether_dhost, &us_assoc_id);
    if (OAL_SUCC != ul_ret)
    {
        /* 没有找到用户的报文，均统一放入subq = 0的队列中 */
        OAM_INFO_LOG0(pst_vap->uc_vap_id, OAM_SF_ANY, "{mac_vap_find_user_by_macaddr::failed!}\r\n");
        return 0;
    }

    /* 获取skb的tos字段 */
    oal_netbuf_get_txtid(pst_buf, &uc_tos);

    /* 根据tos字段选择合适的队列 */
    uc_ac = MAC_TOS_TO_SUBQ(uc_tos);

    us_subq = (oal_uint16)((us_assoc_id * WAL_NETDEV_SUBQUEUE_PER_USE) + uc_ac);
    if (us_subq >= WAL_NETDEV_SUBQUEUE_MAX_NUM)
    {
        return 0;
    }
    return us_subq;
}

/*****************************************************************************
 函 数 名  : wal_flowctl_backp_event_handler
 功能描述  : stop或者wake某个用户的某个subqueue
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月4日
    作    者   : xiechunhui
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 wal_flowctl_backp_event_handler(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru              *pst_hmac_to_wal_event;  /* 指向申请事件的payload指针 */
    mac_ioctl_queue_backp_stru  *pst_flowctl_backp_event;
    oal_net_device_stru         *pst_net_device;
    oal_uint8                    uc_vap_id;
    oal_uint16                   us_assoc_id;
    oal_uint8                    uc_ac;
    oal_uint16                   us_subq_idx;
    /*lint -e830*//*lint -e550*/

    /* 获得事件指针 */
    pst_hmac_to_wal_event = (frw_event_stru *)pst_event_mem->puc_data;

    pst_flowctl_backp_event = (mac_ioctl_queue_backp_stru *)(pst_hmac_to_wal_event->auc_event_data);

    uc_vap_id = pst_flowctl_backp_event->uc_vap_id;
    us_assoc_id = pst_flowctl_backp_event->us_assoc_id;

    /* 获取net_device*/
    pst_net_device = hmac_vap_get_net_device(uc_vap_id);
    if (OAL_PTR_NULL == pst_net_device)
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{wal_flowctl_backp_event_handler::failed!}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 如果对整个VAP stop或者wake */
    if (0xFFFF == pst_flowctl_backp_event->us_assoc_id)
    {
        if (1 == pst_flowctl_backp_event->uc_is_stop)
        {
            oal_net_tx_stop_all_queues(pst_net_device);
            OAM_INFO_LOG3(uc_vap_id, OAM_SF_ANY, "{wal_flowctl_backp_event_handler::oal_net_tx_stop_all_queues, vap_id = %d, assoc_id = %d, tid= %d, mpdu_num = %d!}\r\n",
                    pst_flowctl_backp_event->uc_vap_id,
                    pst_flowctl_backp_event->us_assoc_id,
                    pst_flowctl_backp_event->uc_tidno);
        }
        else
        {
            oal_net_tx_wake_all_queues(pst_net_device);
            OAM_INFO_LOG3(uc_vap_id, OAM_SF_ANY, "{wal_flowctl_backp_event_handler::oal_net_tx_wake_all_queues, vap_id = %d, assoc_id = %d, tid= %d, mpdu_num = %d!}\r\n",
                    pst_flowctl_backp_event->uc_vap_id,
                    pst_flowctl_backp_event->us_assoc_id,
                    pst_flowctl_backp_event->uc_tidno);

        }

        return OAL_SUCC;
    }

    /* 如果对某个user stop或者wake */
    if (WLAN_TID_MAX_NUM == pst_flowctl_backp_event->uc_tidno)
    {
        for (uc_ac = 0; uc_ac <= MAC_LINUX_SUBQ_VO; uc_ac++)
        {
            us_subq_idx = (oal_uint16)((us_assoc_id * WAL_NETDEV_SUBQUEUE_PER_USE) + uc_ac);
            if (1 == pst_flowctl_backp_event->uc_is_stop)
            {
                oal_net_stop_subqueue(pst_net_device, us_subq_idx);
                OAM_INFO_LOG3(uc_vap_id, OAM_SF_ANY, "{wal_flowctl_backp_event_handler::oal_net_stop_subqueue, vap_id = %d, assoc_id = %d, tid= %d, mpdu_num = %d!}\r\n",
                        pst_flowctl_backp_event->uc_vap_id,
                        pst_flowctl_backp_event->us_assoc_id,
                        pst_flowctl_backp_event->uc_tidno);

            }
            else
            {
                oal_net_wake_subqueue(pst_net_device, us_subq_idx);
                OAM_INFO_LOG3(uc_vap_id, OAM_SF_ANY, "{wal_flowctl_backp_event_handler::oal_net_wake_subqueue, vap_id = %d, assoc_id = %d, tid= %d, mpdu_num = %d!}\r\n",
                        pst_flowctl_backp_event->uc_vap_id,
                        pst_flowctl_backp_event->us_assoc_id,
                        pst_flowctl_backp_event->uc_tidno);

            }
        }
        return OAL_SUCC;
    }

    /* 根据uc_tidno字段选择合适的队列 */
    uc_ac = MAC_TOS_TO_SUBQ(pst_flowctl_backp_event->uc_tidno);

    us_subq_idx = (oal_uint16)((us_assoc_id * WAL_NETDEV_SUBQUEUE_PER_USE) + uc_ac);

    if (1 == pst_flowctl_backp_event->uc_is_stop)
    {
        oal_net_stop_subqueue(pst_net_device, us_subq_idx);
        OAM_INFO_LOG3(uc_vap_id, OAM_SF_ANY, "{wal_flowctl_backp_event_handler::oal_net_stop_subqueue, vap_id = %d, assoc_id = %d, tid= %d, mpdu_num = %d!}\r\n",
                pst_flowctl_backp_event->uc_vap_id,
                pst_flowctl_backp_event->us_assoc_id,
                pst_flowctl_backp_event->uc_tidno);
    }
    else
    {
        oal_net_wake_subqueue(pst_net_device, us_subq_idx);
        OAM_INFO_LOG3(uc_vap_id, OAM_SF_ANY, "{wal_flowctl_backp_event_handler::oal_net_wake_subqueue, vap_id = %d, assoc_id = %d, tid= %d, mpdu_num = %d!}\r\n",
                pst_flowctl_backp_event->uc_vap_id,
                pst_flowctl_backp_event->us_assoc_id,
                pst_flowctl_backp_event->uc_tidno);
    }

    return OAL_SUCC;
}

#endif /* endif of _PRE_WLAN_FEATURE_FLOWCTL */
/*lint +e830*//*lint +e550*/

#ifdef _PRE_WLAN_FEATURE_OFFLOAD_FLOWCTL
/*****************************************************************************
 函 数 名  : wal_netdev_select_queue
 功能描述  : kernel给skb选择合适的tx subqueue;
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月17日
    作    者   : xiechunhui
    修改内容   : 新生成函数

*****************************************************************************/
#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 18, 0))
oal_uint16  wal_netdev_select_queue(oal_net_device_stru *pst_dev, oal_netbuf_stru *pst_buf)
#else
oal_uint16  wal_netdev_select_queue(oal_net_device_stru *pst_dev, oal_netbuf_stru *pst_buf, void *accel_priv, select_queue_fallback_t fallback)
#endif /* (LINUX_VERSION_CODE < KERNEL_VERSION(3, 18, 0)) */
{
    return oal_netbuf_select_queue(pst_buf);
}

#endif /* endif of _PRE_WLAN_FEATURE_OFFLOAD_FLOWCTL */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

