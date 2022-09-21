/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : Sdt_drv.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2014年1月23日
  最近修改   :
  功能描述   : SDT驱动侧代码
  函数列表   :
  修改历史   :
  1.日    期   : 2014年1月23日
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
#include "oal_mem.h"
#include "sdt_drv.h"
#include "wal_ext_if.h"
#include "oam_ext_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_SDT_DRV_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
sdt_drv_mng_stru           g_st_sdt_drv_mng_entry;
oam_sdt_func_hook_stru     g_st_sdt_drv_func_hook;
#if ((_PRE_TARGET_PRODUCT_TYPE_5610DMB == _PRE_CONFIG_TARGET_PRODUCT)\
    ||(_PRE_TARGET_PRODUCT_TYPE_VSPM310DMB == _PRE_CONFIG_TARGET_PRODUCT)\
    ||(_PRE_TARGET_PRODUCT_TYPE_WS835DMB == _PRE_CONFIG_TARGET_PRODUCT))
oal_uint8                  g_st_count = 0;
oal_uint32                 g_buf_offset = 0;

oal_netbuf_stru            *g_pst_copy_netbuf = NULL;
oal_nlmsghdr_stru          *g_pst_nlhdr = NULL;
#endif
/*****************************************************************************
  3 函数实现
*****************************************************************************/
OAL_STATIC oal_uint32  sdt_drv_netlink_send(oal_netbuf_stru *pst_netbuf, oal_uint32  ul_len);

/*****************************************************************************
 函 数 名  : sdt_drv_set_mng_entry_usepid
 功能描述  : 设置sdt drv侧对端netlink进程的pid号
 输入参数  : oal_uint32  ulpid
 输出参数  : 无
 返 回 值  : OAL_STATIC OAL_INLINE oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月19日,星期三
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void sdt_drv_set_mng_entry_usepid(oal_uint32  ulpid)
{
    oal_uint    ui_irq_save;

    oal_spin_lock_irq_save(&g_st_sdt_drv_mng_entry.st_spin_lock, &ui_irq_save);

    g_st_sdt_drv_mng_entry.ul_usepid = ulpid;

    oal_spin_unlock_irq_restore(&g_st_sdt_drv_mng_entry.st_spin_lock, &ui_irq_save);
}

/*****************************************************************************
 函 数 名  : sdt_drv_netbuf_add_to_list_tail
 功能描述  : sdt收发消息入队
 输入参数  : oal_netbuf_stru *pst_netbuf
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月19日,星期三
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  sdt_drv_netbuf_add_to_list(oal_netbuf_stru *pst_netbuf)
{
    oal_uint    ui_irq_save;

    oal_spin_lock_irq_save(&g_st_sdt_drv_mng_entry.st_spin_lock, &ui_irq_save);

    oal_netbuf_add_to_list_tail(pst_netbuf, &g_st_sdt_drv_mng_entry.rx_wifi_dbg_seq);

    oal_spin_unlock_irq_restore(&g_st_sdt_drv_mng_entry.st_spin_lock, &ui_irq_save);
}

/*****************************************************************************
 函 数 名  : sdt_drv_netbuf_delist
 功能描述  : sdt消息队列出队
 输出参数  : 无
 返 回 值  : oal_netbuf_stru*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月19日,星期三
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_netbuf_stru* sdt_drv_netbuf_delist(oal_void)
{
    oal_uint                ui_irq_save;
    oal_netbuf_stru        *pst_netbuf;

    oal_spin_lock_irq_save(&g_st_sdt_drv_mng_entry.st_spin_lock, &ui_irq_save);

    pst_netbuf = oal_netbuf_delist(&g_st_sdt_drv_mng_entry.rx_wifi_dbg_seq);

    oal_spin_unlock_irq_restore(&g_st_sdt_drv_mng_entry.st_spin_lock, &ui_irq_save);

    return pst_netbuf;
}
/*****************************************************************************
 函 数 名  : sdt_drv_check_isdevlog
 功能描述  : 检测上报日志是否为device log
 输入参数  : oal_net
 输出参数  : 无
 返 回 值  : int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32 sdt_drv_check_isdevlog(oal_netbuf_stru *pst_netbuf)
{
    oal_uint8               *puc_pkt_tail;
    sdt_drv_pkt_hdr_stru    *pst_pkt_hdr;
    pst_pkt_hdr = (sdt_drv_pkt_hdr_stru *)oal_netbuf_data(pst_netbuf);
    puc_pkt_tail = (oal_uint8 *)pst_pkt_hdr + OAL_NETBUF_LEN(pst_netbuf);
    OAL_IO_PRINT("devlog {%s}\n", oal_netbuf_data(pst_netbuf));
    if (SDT_DRV_PKT_END_FLG == *puc_pkt_tail
        || SDT_DRV_PKT_START_FLG == pst_pkt_hdr->uc_data_start_flg)
    {
        OAL_IO_PRINT("check out is device log\n");
        return OAL_SUCC;
    }

    return -OAL_EFAIL;
}


/*****************************************************************************
 函 数 名  : sdt_drv_add_pkt_head
 功能描述  : 从驱动侧接收到数据，前后加上类型等信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  sdt_drv_add_pkt_head(
                                      oal_netbuf_stru  *pst_netbuf,
                                      oam_data_type_enum_uint8  en_type,
                                      oam_primid_type_enum_uint8 en_prim_id)
{
    /*************************** buffer structure ****************************/
                    /**************************************/
                    /*   |data_hdr | data | data_tail |   */
                    /*------------------------------------*/
                    /*   |  8Byte  |      |    1Byte  |   */
                    /**************************************/

    /*************************************************************************/

    /************************ data header structure **************************/
    /* ucFrameStart | ucFuncType | ucPrimId | ucReserver | usFrameLen | usSN */
    /* --------------------------------------------------------------------- */
    /*    1Byte     |    1Byte   |  1Byte   |   1Byte    |  2Bytes    |2Bytes*/
    /*************************************************************************/

    oal_uint8               *puc_pkt_tail;
    sdt_drv_pkt_hdr_stru    *pst_pkt_hdr;
    oal_uint16               us_tmp_data;

    oal_netbuf_push(pst_netbuf, WLAN_SDT_SKB_HEADROOM_LEN);
    oal_netbuf_put(pst_netbuf, WLAN_SDT_SKB_TAILROOM_LEN);

    /* SDT收到的消息数目加1 */
    g_st_sdt_drv_mng_entry.us_sn_num++;

    /* 为数据头的每一个成员赋值 */
    pst_pkt_hdr = (sdt_drv_pkt_hdr_stru *)oal_netbuf_data(pst_netbuf);

    pst_pkt_hdr->uc_data_start_flg = SDT_DRV_PKT_START_FLG;
    pst_pkt_hdr->en_msg_type       = en_type;
    pst_pkt_hdr->uc_prim_id        = en_prim_id;
    pst_pkt_hdr->uc_resv[0]        = 0;

    us_tmp_data = (oal_uint16)OAL_NETBUF_LEN(pst_netbuf);
    pst_pkt_hdr->uc_data_len_low_byte  = SDT_DRV_GET_LOW_BYTE(us_tmp_data);
    pst_pkt_hdr->uc_data_len_high_byte = SDT_DRV_GET_HIGH_BYTE(us_tmp_data);

    us_tmp_data = g_st_sdt_drv_mng_entry.us_sn_num;
    pst_pkt_hdr->uc_sequence_num_low_byte   = SDT_DRV_GET_LOW_BYTE(us_tmp_data);
    pst_pkt_hdr->uc_sequence_num_high_byte  = SDT_DRV_GET_HIGH_BYTE(us_tmp_data);

    /* 为数据尾赋值0x7e */
    puc_pkt_tail = (oal_uint8 *)pst_pkt_hdr + OAL_NETBUF_LEN(pst_netbuf);
    puc_pkt_tail--;
   *puc_pkt_tail = SDT_DRV_PKT_END_FLG;
}


/*****************************************************************************
 函 数 名  : sdt_drv_report_data2app
 功能描述  : 上报内核侧的消息
 输入参数  : oal_netbuf_stru *pst_netbuf
             oam_data_type_enum_uint8 uc_type
             oam_primid_type_enum_uint8 uc_prim_id
 输出参数  : 无
 返 回 值  : oal_int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月11日,星期二
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32  sdt_drv_report_data2app(oal_netbuf_stru *pst_netbuf, oam_data_type_enum_uint8 en_type, oam_primid_type_enum_uint8 en_prim)
{
    /* 由上层调用接口判断指针非空 */
    oal_int32       l_ret;

    /*如果是device log 则不需要加pkt 包头*/
    if (OAM_DATA_TYPE_DEVICE_LOG != en_type)
    {
        sdt_drv_add_pkt_head(pst_netbuf, en_type, en_prim);
    }

    sdt_drv_netbuf_add_to_list(pst_netbuf);

    l_ret = oal_queue_work(g_st_sdt_drv_mng_entry.oam_rx_workqueue, &g_st_sdt_drv_mng_entry.rx_wifi_work);

    return l_ret;
}

/*****************************************************************************
 函 数 名  : sdt_drv_get_wq_len
 功能描述  : 返回sdt侧接收消息的队列长度
 输入参数  : oal_void
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月11日,星期二
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32 sdt_drv_get_wq_len(oal_void)
{
    return (oal_int32)oal_netbuf_list_len(&g_st_sdt_drv_mng_entry.rx_wifi_dbg_seq);
}

/*****************************************************************************
 函 数 名  : sdt_drv_send_data_to_wifi
 功能描述  : 从app侧接收到数据，解析该数据的头部信息，确定是数据的去向，然后
             调用相应的51驱动侧接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32  sdt_drv_send_data_to_wifi(oal_uint8  *puc_param, oal_int32  l_len)
{
    oal_netbuf_stru         *pst_netbuf;
    oal_int8                *pc_buf;
    oal_int                  i_len;   /* SDIO CRC ERROR */
    oal_int32                l_ret = OAL_EFAIL;
    oal_uint8               *puc_data;

    if (OAL_PTR_NULL == puc_param)
    {
        OAL_IO_PRINT("sdt_drv_send_data_to_wifi::puc_param is null!\n");
        return -OAL_EFAIL;
    }

    i_len = (oal_int)l_len > 300 ? (oal_int)l_len: 300;

    /* 接收消息不用填充头，直接使用 */
    pst_netbuf = oal_mem_sdt_netbuf_alloc((oal_uint16)i_len, OAL_TRUE);
    if (OAL_PTR_NULL == pst_netbuf)
    {
        return -OAL_EFAIL;
    }

    pc_buf = (oal_int8 *)oal_netbuf_put(pst_netbuf, (oal_uint32)l_len);
    oal_memcopy((oal_void *)pc_buf, (const oal_void *)puc_param, (oal_uint32)l_len);

    i_len = pc_buf[5]*MAX_NUM;
    i_len = pc_buf[4] + i_len;
    i_len = i_len - OAM_RESERVE_SKB_LEN;

    puc_data = oal_netbuf_data(pst_netbuf);

    switch(pc_buf[1])
    {
        case OAM_DATA_TYPE_MEM_RW:
            if (OAL_PTR_NULL != g_st_oam_wal_func_hook.p_wal_recv_mem_data_func)
            {
                l_ret = g_st_oam_wal_func_hook.p_wal_recv_mem_data_func(&puc_data[8], (oal_uint16)i_len);
            }
            break;

        case OAM_DATA_TYPE_REG_RW:
            if (OAL_PTR_NULL != g_st_oam_wal_func_hook.p_wal_recv_reg_data_func)
            {
                l_ret = g_st_oam_wal_func_hook.p_wal_recv_reg_data_func(&puc_data[8], (oal_uint16)i_len);
            }
            break;

        case OAM_DATA_TYPE_CFG:
            if (OAL_PTR_NULL != g_st_oam_wal_func_hook.p_wal_recv_cfg_data_func)
            {
                l_ret = g_st_oam_wal_func_hook.p_wal_recv_cfg_data_func(&puc_data[8], (oal_uint16)i_len);
            }
            break;

        case OAM_DATA_TYPE_GVAR_RW:
            if (OAL_PTR_NULL != g_st_oam_wal_func_hook.p_wal_recv_global_var_func)
            {
                l_ret = g_st_oam_wal_func_hook.p_wal_recv_global_var_func(&puc_data[8], (oal_uint16)i_len);
            }
            break;

        default:
            OAL_IO_PRINT("sdt_drv_send_data_to_wifi::cmd is invalid!!-->%d\n", pc_buf[1]);
            break;
    }
#if (_PRE_OS_VERSION_RAW != _PRE_OS_VERSION)
    oal_mem_sdt_netbuf_free(pst_netbuf, OAL_TRUE);
#endif
    //oal_netbuf_free(pst_netbuf);
    return l_ret;
}

/*****************************************************************************
 函 数 名  : sdt_drv_netlink_send
 功能描述  : SDT驱动侧通过netlink向SDT APP发送数据
             记录待发送的数据与发送失败的数据；通过序列号记录
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  sdt_drv_netlink_send(oal_netbuf_stru *pst_netbuf, oal_uint32  ul_len)
{
#if (_PRE_OS_VERSION_RAW != _PRE_OS_VERSION)
#if((_PRE_TARGET_PRODUCT_TYPE_5610DMB == _PRE_CONFIG_TARGET_PRODUCT)\
    ||(_PRE_TARGET_PRODUCT_TYPE_VSPM310DMB == _PRE_CONFIG_TARGET_PRODUCT)\
    ||(_PRE_TARGET_PRODUCT_TYPE_WS835DMB == _PRE_CONFIG_TARGET_PRODUCT))
    oal_int32                   l_ret_len = 0;
    sdt_drv_pkt_hdr_stru       *p_sdt_hdr;
#endif
    oal_netbuf_stru            *pst_copy_netbuf;
    oal_nlmsghdr_stru          *pst_nlhdr;

    oal_uint32                  ul_nlmsg_len;
    oal_int32                   l_unicast_bytes  = 0;

    /* 由上层保证参数非空 */

    /* 如果没有与app建立连接，则直接返回，每500次打印一次提示信息 */
    if (0 == g_st_sdt_drv_mng_entry.ul_usepid)
    {
        if (0 == (oal_atomic_read(&g_st_sdt_drv_mng_entry.ul_unconnect_cnt) % SDT_DRV_REPORT_NO_CONNECT_FREQUENCE))
        {
            OAL_IO_PRINT("Info:waitting app_sdt start...\r\n");
            oal_atomic_inc(&g_st_sdt_drv_mng_entry.ul_unconnect_cnt);
        }

        oal_mem_sdt_netbuf_free(pst_netbuf, OAL_TRUE);
        //oal_netbuf_free(pst_netbuf);

        return OAL_FAIL;
    }

#if ((_PRE_TARGET_PRODUCT_TYPE_5610DMB == _PRE_CONFIG_TARGET_PRODUCT)\
    ||(_PRE_TARGET_PRODUCT_TYPE_VSPM310DMB == _PRE_CONFIG_TARGET_PRODUCT)\
    ||(_PRE_TARGET_PRODUCT_TYPE_WS835DMB == _PRE_CONFIG_TARGET_PRODUCT))
    // 数据包分析
    p_sdt_hdr =  (sdt_drv_pkt_hdr_stru*)oal_netbuf_data(pst_netbuf);
    if (OAM_DATA_TYPE_LOG == p_sdt_hdr->en_msg_type || OAM_DATA_TYPE_OTA == p_sdt_hdr->en_msg_type)
    {
        if (0 == g_st_count)
        {
            ul_nlmsg_len = OAL_NLMSG_LENGTH(MAX_NLMSG_LEN);
            g_pst_copy_netbuf = oal_netbuf_alloc(ul_nlmsg_len, 0, WLAN_MEM_NETBUF_ALIGN);
            if (OAL_UNLIKELY(OAL_PTR_NULL == g_pst_copy_netbuf))
            {
                oal_mem_sdt_netbuf_free(pst_netbuf, OAL_TRUE);
                //oal_netbuf_free(pst_netbuf);

                OAL_IO_PRINT("oal_netbuf_alloc failed. \r\n");
                return OAL_FAIL;
            }

            g_pst_nlhdr = oal_nlmsg_put(g_pst_copy_netbuf, 0, 0, 0, (oal_int32)MAX_NLMSG_LEN, 0);
        }

        if (NULL != g_pst_nlhdr)
        {
            l_ret_len = MAX_NLMSG_LEN - g_buf_offset - ul_len;
            if (l_ret_len > 0)
            {
                oal_memcopy((oal_void *)OAL_NLMSG_DATA(g_pst_nlhdr) + g_buf_offset, (const oal_void *)oal_netbuf_data(pst_netbuf), ul_len);
                g_st_count++;
                g_buf_offset += ul_len;
            }
        }

        if (MAX_QUEUE_COUNT == g_st_count || g_buf_offset > MAX_CO_SIZE || l_ret_len < 0)
        {
            g_st_count = 0;
            g_buf_offset = 0;

            l_unicast_bytes = oal_netlink_unicast(g_st_sdt_drv_mng_entry.pst_nlsk, g_pst_copy_netbuf, g_st_sdt_drv_mng_entry.ul_usepid, 0);
            oal_msleep(300);

            OAM_SDT_STAT_INCR(ul_nlk_sd_cnt);
            if (l_unicast_bytes <= 0)
            {
                oal_mem_sdt_netbuf_free(pst_netbuf, OAL_TRUE);
                //oal_netbuf_free(pst_netbuf);
                oal_msleep(500);
                OAM_SDT_STAT_INCR(ul_nlk_sd_fail);
                return OAL_FAIL;
            }
        }

        oal_mem_sdt_netbuf_free(pst_netbuf, OAL_TRUE);
        return OAL_SUCC;
    }
#endif

   /* 填写netlink消息头 */
    ul_nlmsg_len = OAL_NLMSG_SPACE(ul_len);
    pst_copy_netbuf = oal_netbuf_alloc(ul_nlmsg_len, 0, WLAN_MEM_NETBUF_ALIGN);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_copy_netbuf))
    {
        oal_mem_sdt_netbuf_free(pst_netbuf, OAL_TRUE);
        //oal_netbuf_free(pst_netbuf);

        OAL_IO_PRINT("oal_netbuf_alloc failed. \r\n");
        return OAL_FAIL;
    }

    pst_nlhdr = oal_nlmsg_put(pst_copy_netbuf, 0, 0, 0, (oal_int32)ul_len, 0);
    oal_memcopy((oal_void *)OAL_NLMSG_DATA(pst_nlhdr), (const oal_void *)oal_netbuf_data(pst_netbuf), ul_len);

    l_unicast_bytes = oal_netlink_unicast(g_st_sdt_drv_mng_entry.pst_nlsk, pst_copy_netbuf, g_st_sdt_drv_mng_entry.ul_usepid, OAL_MSG_DONTWAIT);

    oal_mem_sdt_netbuf_free(pst_netbuf, OAL_TRUE);
    //oal_netbuf_free(pst_netbuf);

    OAM_SDT_STAT_INCR(ul_nlk_sd_cnt);
    if (l_unicast_bytes <= 0)
    {
        OAM_SDT_STAT_INCR(ul_nlk_sd_fail);
        return OAL_FAIL;
    }
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : sdt_drv_netlink_recv
 功能描述  : 从SDT APP侧接收到数据
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  sdt_drv_netlink_recv(oal_netbuf_stru  *pst_netbuf)
{
    oal_netbuf_stru                *pst_net_buf = OAL_PTR_NULL;
    oal_nlmsghdr_stru              *pst_nlhdr = OAL_PTR_NULL;
    sdt_drv_netlink_msg_hdr_stru    st_msg_hdr;
    oal_int32                       l_len;

    if (OAL_PTR_NULL == pst_netbuf)
    {
        OAL_IO_PRINT("sdt_drv_netlink_recv::pst_netbuf is null!\n");
        return;
    }

    OAL_MEMZERO(g_st_sdt_drv_mng_entry.puc_data, DATA_BUF_LEN);

    pst_net_buf = oal_netbuf_get(pst_netbuf);
    if (OAL_NETBUF_LEN(pst_net_buf) >= OAL_NLMSG_SPACE(0))
    {
        pst_nlhdr = oal_nlmsg_hdr((OAL_CONST oal_netbuf_stru *)pst_net_buf);
        l_len   = (oal_int32)OAL_NLMSG_PAYLOAD(pst_nlhdr, 0);

        if(l_len <= DATA_BUF_LEN)
        {
            oal_memcopy((oal_void *)g_st_sdt_drv_mng_entry.puc_data,
                        (const oal_void *)OAL_NLMSG_DATA(pst_nlhdr),
                        (oal_uint32)l_len);
        }
        else
        {
            /*overflow*/
            OAL_IO_PRINT("[ERROR]invaild netlink buff len:%u,max len:%u\n",(oal_uint32)l_len,DATA_BUF_LEN);
            oal_mem_sdt_netbuf_free(pst_net_buf, OAL_TRUE);
            return;
        }

        oal_memcopy((oal_void *)&st_msg_hdr,
                    (const oal_void *)g_st_sdt_drv_mng_entry.puc_data,
                    (oal_uint32)OAL_SIZEOF(st_msg_hdr));

        if (NETLINK_MSG_HELLO == st_msg_hdr.ul_cmd)
        {
            g_st_sdt_drv_mng_entry.ul_usepid = pst_nlhdr->nlmsg_pid;   /*pid of sending process */
            OAL_IO_PRINT("%s pid is-->%d \n", OAL_FUNC_NAME, g_st_sdt_drv_mng_entry.ul_usepid);
        }
#if defined(PLATFORM_DEBUG_ENABLE) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
        else
        {
            sdt_drv_send_data_to_wifi(&g_st_sdt_drv_mng_entry.puc_data[OAL_SIZEOF(st_msg_hdr)], l_len - (oal_int32)OAL_SIZEOF(st_msg_hdr));
        }
#else
        OAL_IO_PRINT("user mode not accept msg except hello from sdt!\n");
#endif
    }

	oal_mem_sdt_netbuf_free(pst_net_buf, OAL_TRUE);
    //oal_netbuf_free(pst_net_buf);
}

/*****************************************************************************
 函 数 名  : sdt_drv_netlink_create
 功能描述  : 创建netlink
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32  sdt_drv_netlink_create(oal_void)
{
    g_st_sdt_drv_mng_entry.pst_nlsk = oal_netlink_kernel_create(&OAL_INIT_NET, NETLINK_TEST,
                                                          0, sdt_drv_netlink_recv,
                                                          OAL_PTR_NULL, OAL_THIS_MODULE);
    if (OAL_PTR_NULL == g_st_sdt_drv_mng_entry.pst_nlsk)
    {
        OAL_IO_PRINT("sdt_drv_netlink_create return fail!\n");
        return -OAL_EFAIL;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : sdt_drv_push_wifi_log_work
 功能描述  : oam rx wifi skb log data
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  sdt_drv_push_wifi_log_work(oal_work_stru *work)
{
    oal_netbuf_stru  *pst_netbuf;

    pst_netbuf = sdt_drv_netbuf_delist();

    while (OAL_PTR_NULL != pst_netbuf)
    {
        sdt_drv_netlink_send(pst_netbuf, OAL_NETBUF_LEN(pst_netbuf));

        pst_netbuf = sdt_drv_netbuf_delist();
    }
    return;
}

/*****************************************************************************
 函 数 名  : sdt_drv_func_hook_init
 功能描述  : sdt对外模块钩子函数初始化
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月12日,星期三
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void sdt_drv_func_hook_init(oal_void)
{
    g_st_sdt_drv_func_hook.p_sdt_report_data_func = sdt_drv_report_data2app;
    g_st_sdt_drv_func_hook.p_sdt_get_wq_len_func  = sdt_drv_get_wq_len;
}

/*****************************************************************************
 函 数 名  : sdt_drv_main_init
 功能描述  : sdt_drv初始化函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功或者失败原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月23日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32  sdt_drv_main_init(oal_void)
{
    oal_int32   l_nl_return_val;

    OAL_MEMZERO((void *)&g_st_sdt_drv_mng_entry, OAL_SIZEOF(g_st_sdt_drv_mng_entry));

    g_st_sdt_drv_mng_entry.puc_data = oal_memalloc(DATA_BUF_LEN);
    if (OAL_PTR_NULL == g_st_sdt_drv_mng_entry.puc_data)
    {
        OAL_IO_PRINT("alloc g_st_sdt_drv_mng_entry.puc_data fail!\n");
        return -OAL_EFAIL;
    }

    OAL_MEMZERO(g_st_sdt_drv_mng_entry.puc_data, DATA_BUF_LEN);

    l_nl_return_val = sdt_drv_netlink_create();
    if (0 > l_nl_return_val)
    {
        OAL_IO_PRINT("sdt_drv_main_init::create netlink returns fail! l_nl_return_val--> \
                      %d\n", l_nl_return_val);
        return -l_nl_return_val;
    }

    g_st_sdt_drv_mng_entry.oam_rx_workqueue = oal_create_singlethread_workqueue("oam_rx_queue");
    OAL_INIT_WORK(&g_st_sdt_drv_mng_entry.rx_wifi_work, sdt_drv_push_wifi_log_work);
    oal_spin_lock_init(&g_st_sdt_drv_mng_entry.st_spin_lock);
    oal_netbuf_list_head_init(&g_st_sdt_drv_mng_entry.rx_wifi_dbg_seq);

    /* sdt模块钩子函数初始化 */
    sdt_drv_func_hook_init();

    /* 将sdt钩子函数注册至oam模块 */
    oam_sdt_func_fook_register(&g_st_sdt_drv_func_hook);

    /* sdt正常加载之后将输出方式置为OAM_OUTPUT_TYPE_SDT */
    if (OAL_SUCC != oam_set_output_type(OAM_OUTPUT_TYPE_SDT))
    {
        OAL_IO_PRINT("oam set output type fail!");
        return -OAL_EFAIL;
    }
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : sdt_drv_main_exit
 功能描述  : sdt_drv卸载
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功或者失败原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月23日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  sdt_drv_main_exit(oal_void)
{
   	oam_sdt_func_fook_unregister();

    if (OAL_PTR_NULL != g_st_sdt_drv_mng_entry.pst_nlsk)
    {
        oal_netlink_kernel_release(g_st_sdt_drv_mng_entry.pst_nlsk);
    }

    if (OAL_PTR_NULL != g_st_sdt_drv_mng_entry.puc_data)
    {
        oal_free(g_st_sdt_drv_mng_entry.puc_data);
    }

    oal_destroy_workqueue(g_st_sdt_drv_mng_entry.oam_rx_workqueue);
    oal_netbuf_queue_purge(&g_st_sdt_drv_mng_entry.rx_wifi_dbg_seq);

    /* 卸载成功后，输出打印 */
    OAL_IO_PRINT("sdt exit ok!\n");

    return;
}

/*lint -e578*//*lint -e19*/
#if (_PRE_PRODUCT_ID_HI1151==_PRE_PRODUCT_ID)
oal_module_init(sdt_drv_main_init);
oal_module_exit(sdt_drv_main_exit);
#endif

oal_module_symbol(sdt_drv_main_init);
oal_module_symbol(sdt_drv_main_exit);


oal_module_license("GPL");

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

