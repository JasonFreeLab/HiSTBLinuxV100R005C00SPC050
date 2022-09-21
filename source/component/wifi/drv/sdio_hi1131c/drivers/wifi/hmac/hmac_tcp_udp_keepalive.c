/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_tcp_udp_keepalive.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2016年4月18日
  最近修改   :
  功能描述   : hmac侧TCP&UDP功能实现函数
  函数列表   :
  修改历史   :
  1.日    期   : 2016年4月18日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
#ifdef _PRE_WLAN_FEATURE_TCP_UDP_KEEPALIVE
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "oal_types.h"
#include "oal_net.h"
#include "hmac_tcp_udp_keepalive.h"
#include "dmac_ext_if.h"
#include "oam_wdk.h"
#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_TCP_UDP_KEEPALIVE_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
hmac_tcp_udp_conn_stru g_st_tcp_udp_conn;
/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : hmac_get_tcp_params
 功能描述  : 获取发送的TCP包的参数,
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年5月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_get_tcp_params(oal_netbuf_stru *pst_netbuf)
{
    mac_ether_header_stru   *pst_ether_hdr    = OAL_PTR_NULL; /* 以太网头 */
    oal_uint8                uc_ip_heard_len  = 0;
    oal_uint8               *puc_data         = OAL_PTR_NULL;
    oal_uint8                uc_index         = 0;
    hmac_tcp_params_stru    *pst_tcp_params   = OAL_PTR_NULL;
    mac_ip_header_stru      *pst_ip_head      = OAL_PTR_NULL;
    mac_tcp_header_stru     *pst_tcp_head     = OAL_PTR_NULL;

    if (OAL_PTR_NULL == pst_netbuf)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "hmac_get_tcp_params::pst_netbuf is null");
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_ether_hdr   = (mac_ether_header_stru *)oal_netbuf_data(pst_netbuf);
    puc_data        =  (oal_uint8 *)pst_ether_hdr;

/*lint -e778*/
    if (OAL_HOST2NET_SHORT(ETHER_TYPE_IP) == pst_ether_hdr->us_ether_type)
    {
/*lint +e778*/
        uc_ip_heard_len = (puc_data[ETHER_HDR_LEN] & 0x0f) * 4;//IP头的长度
        /* IP头首部指针 */
        pst_ip_head     =(mac_ip_header_stru *)(puc_data + OAL_SIZEOF(mac_ether_header_stru));
        /* 判断是否为tcp报文 */
        if (MAC_PROTOCOL_TYPE_TCP == pst_ip_head->uc_protocol)
        {
            /* TCP头首部指针 */
            pst_tcp_head = (mac_tcp_header_stru *)(puc_data + OAL_SIZEOF(mac_ether_header_stru) + uc_ip_heard_len);
            for (uc_index = 0;uc_index < HMAC_TCP_CONNECT_NUM; uc_index++)
            {
                pst_tcp_params = &g_st_tcp_udp_conn.st_tcp_connects[uc_index];
                /* 通过端口号判断是否为指定TCP连接的包 */
                /*lint -e778*/
                if ((OAL_HOST2NET_SHORT(pst_tcp_head->us_sport) == pst_tcp_params->us_src_port)
                    && (OAL_HOST2NET_SHORT(pst_tcp_head->us_dport) == pst_tcp_params->us_dst_port))
                /*lint +e778*/
                {
                    pst_tcp_params->ul_seq_num = OAL_HOST2NET_LONG(pst_tcp_head->ul_seqnum);
                    pst_tcp_params->ul_ack_num = OAL_HOST2NET_LONG(pst_tcp_head->ul_acknum);
                    pst_tcp_params->us_window  = OAL_HOST2NET_SHORT(pst_tcp_head->us_window);
                    oal_set_mac_addr(pst_tcp_params->uc_dst_mac, pst_ether_hdr->auc_ether_dhost);
                }
            }
        }
    }
    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : hmac_get_ip_header_checksum
 功能描述  : 计算IP头的校验和
 输入参数  :
             puc_data: 需要计算校验和部分的数据
             us_len  : 该部分的数据长度
 输出参数  :
 返 回 值  : 校验和
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年5月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint16 hmac_get_ip_header_checksum(oal_uint8 *puc_data, oal_uint16 us_len)
{
    oal_uint32    ul_sum   = 0;
    oal_uint16    us_index = 0;
    oal_uint16    us_checksum;
    if (OAL_PTR_NULL == puc_data)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "hmac_get_ip_header_checksum::puc_data is null");
        return OAL_ERR_CODE_PTR_NULL;
    }
    for (us_index = 0;us_index < us_len;)
    {
        ul_sum += (puc_data[us_index++] << 8);
        ul_sum += puc_data[us_index++];
    }
    while (ul_sum > 0xffff)
    {
        ul_sum = ((ul_sum & 0xffff0000) >> 16) + (ul_sum & 0x0000ffff);
    }
    us_checksum = (oal_uint16)ul_sum;
    us_checksum = ~us_checksum;

    return us_checksum;
}
/*****************************************************************************
 函 数 名  : hmac_set_ip_header_checksum
 功能描述  : 设置IP头的校验和
 输入参数  :
             puc_payload: payload首部地址
             us_checksum: 需要设置的校验和
             *pus_offset: 当前偏移量
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年5月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_set_ip_header_checksum(oal_uint8 *puc_payload, oal_uint16 us_checksum, oal_uint16 *pus_offset)
{
    oal_uint16             us_index;
    mac_ip_header_stru    *pst_ip_head = OAL_PTR_NULL;

    if ((OAL_PTR_NULL == puc_payload) || (OAL_PTR_NULL == pus_offset))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "hmac_set_ip_header_checksum::puc_payload = %x,pus_offset=%x",puc_payload,pus_offset);
        return OAL_ERR_CODE_PTR_NULL;
    }
    us_index = *pus_offset;

    pst_ip_head           = (mac_ip_header_stru *)(puc_payload + us_index);
    pst_ip_head->us_check = OAL_HTON_16(us_checksum);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_encap_llc_hearder
 功能描述  : 组LLC头
 输入参数  : puc_payload: payload的首部地址
             *pus_offset: 偏移长度
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/

oal_uint32  hmac_encap_llc_hearder(oal_uint8 *puc_payload, oal_uint16 *pus_offset)
{
    oal_uint16         us_index;
    mac_llc_snap_stru *pst_llc_head = OAL_PTR_NULL;

    if ((OAL_PTR_NULL == puc_payload) || (OAL_PTR_NULL == pus_offset))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "hmac_encap_llc_hearder::puc_payload=%x,pus_offset=%x",puc_payload,pus_offset);
        return OAL_ERR_CODE_PTR_NULL;
    }

    us_index = *pus_offset;
    pst_llc_head = (mac_llc_snap_stru *)(puc_payload + us_index);

    pst_llc_head->uc_llc_dsap   = 0xaa;
    pst_llc_head->uc_llc_ssap   = 0xaa;
    pst_llc_head->uc_control    = 0x03;
    /*lint -e778*/
    pst_llc_head->us_ether_type = OAL_HTON_16(ETHER_TYPE_IP);
    /*lint +e778*/
    us_index += OAL_SIZEOF(mac_llc_snap_stru);

    *pus_offset = us_index;
    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : hmac_encap_ip_hearder
 功能描述  : 组IP头
 输入参数  : puc_payload: payload的首部地址
             puc_params : TCP或UDP节点指针
             *pus_offset: 偏移长度
             uc_flag    : 标识传入的是TCP参数还是UDP参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_encap_ip_hearder(oal_uint8 *puc_payload, oal_uint8 *puc_params, oal_uint16 *pus_offset, hmac_netbuf_type_enum_uint8 uc_flag)
{
    oal_uint16             us_index;
    hmac_tcp_params_stru  *pst_tcp_params  = OAL_PTR_NULL;
    hmac_udp_params_stru  *pst_udp_params  = OAL_PTR_NULL;
    oal_uint16             us_checksum     = 0;
    mac_ip_header_stru    *pst_ip_head     = OAL_PTR_NULL;

    if ((OAL_PTR_NULL == puc_payload) || (OAL_PTR_NULL == puc_params) || (OAL_PTR_NULL == pus_offset))
    {
        OAM_ERROR_LOG3(0, OAM_SF_ANY, "hmac_encap_ip_hearder::puc_payload=%x,puc_params = %x,pus_offset = %x",puc_payload,puc_params,pus_offset);
        return OAL_ERR_CODE_PTR_NULL;
    }
    if (HMAC_NETBUF_TYPE_TCP == uc_flag)
    {
        pst_tcp_params = (hmac_tcp_params_stru *)puc_params;
    }
    else if(HMAC_NETBUF_TYPE_UDP == uc_flag)
    {
        pst_udp_params = (hmac_udp_params_stru *)puc_params;
    }
    else
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "hmac_encap_ip_hearder::uc_flag is invalid");
        return OAL_FAIL;
    }
    us_index = *pus_offset;

    pst_ip_head = (mac_ip_header_stru *)(puc_payload + us_index);

    pst_ip_head->uc_version_ihl = 0x45;
    pst_ip_head->uc_tos         = 0x00;

    /* IP头和tcp头固定为20个字节 */
    if (HMAC_NETBUF_TYPE_TCP == uc_flag)
    {
        if (OAL_PTR_NULL == pst_tcp_params)
        {
            return OAL_ERR_CODE_PTR_NULL;
        }
        pst_ip_head->us_tot_len = OAL_HTON_16(MAC_IP_HEADER_LEN + MAC_TCP_HEADER_LEN + pst_tcp_params->ul_payload_len);
    }
    else
    {
        if (OAL_PTR_NULL == pst_udp_params)
        {
            return OAL_ERR_CODE_PTR_NULL;
        }
        /*lint -e572*/
        pst_ip_head->us_tot_len = OAL_HTON_16(MAC_IP_HEADER_LEN + MAC_UDP_HEADER_LEN + pst_udp_params->ul_payload_len);
        /*lint +e572*/
    }
    /*lint -e778*/
    pst_ip_head->us_id       = OAL_HTON_16(0x11aa);
    pst_ip_head->us_frag_off = OAL_HTON_16(0x4000);
    /*lint +e778*/
    pst_ip_head->uc_ttl      = 0x80;

    /* 标记是TCP包还是UDP包 */
    if (HMAC_NETBUF_TYPE_TCP == uc_flag)
    {
        pst_ip_head->uc_protocol = 0x06;
    }
    if(HMAC_NETBUF_TYPE_UDP == uc_flag)
    {
        pst_ip_head->uc_protocol = 0x11;
    }
    pst_ip_head->us_check = 0;
    if (HMAC_NETBUF_TYPE_TCP == uc_flag)
    {
        if (OAL_PTR_NULL == pst_tcp_params)
        {
            return OAL_ERR_CODE_PTR_NULL;
        }
        oal_set_ip_addr((oal_uint8 *)&(pst_ip_head->ul_saddr), pst_tcp_params->uc_src_ip);
        oal_set_ip_addr((oal_uint8 *)&(pst_ip_head->ul_daddr), pst_tcp_params->uc_dst_ip);
    }
    else
    {
        if (OAL_PTR_NULL == pst_udp_params)
        {
            return OAL_ERR_CODE_PTR_NULL;
        }
        oal_set_ip_addr((oal_uint8 *)&(pst_ip_head->ul_saddr), pst_udp_params->uc_src_ip);
        oal_set_ip_addr((oal_uint8 *)&(pst_ip_head->ul_daddr), pst_udp_params->uc_dst_ip);
    }

    us_index += OAL_SIZEOF(mac_ip_header_stru);

    us_checksum = hmac_get_ip_header_checksum(&puc_payload[*pus_offset], us_index - (*pus_offset));
    hmac_set_ip_header_checksum(puc_payload, us_checksum, pus_offset);
    *pus_offset = us_index;
    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : hmac_encap_tcp_hearder
 功能描述  : 组TCP头
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_encap_tcp_hearder(
                         oal_uint8 *puc_payload,
                         hmac_tcp_params_stru *pst_tcp_params,
                         oal_uint16 *pus_offset)
{
    oal_uint16             us_index;
    mac_tcp_header_stru   *pst_tcp_head = OAL_PTR_NULL;

    if ((OAL_PTR_NULL == puc_payload) || (OAL_PTR_NULL == pst_tcp_params) || (OAL_PTR_NULL == pus_offset))
    {
        OAM_ERROR_LOG3(0, OAM_SF_ANY, "hmac_encap_tcp_hearder::puc_payload = 0x%x, pst_tcp_params = 0x%x,pus_offset = 0x%x",puc_payload,pst_tcp_params,pus_offset);
        return OAL_ERR_CODE_PTR_NULL;
    }
    us_index = *pus_offset;
    pst_tcp_head = (mac_tcp_header_stru *)(puc_payload + us_index);
    pst_tcp_head->us_sport  = OAL_HTON_16(pst_tcp_params->us_src_port);
    pst_tcp_head->us_dport  = OAL_HTON_16(pst_tcp_params->us_dst_port);
    /* seq num和ack num均在dmac层设置，这里写0 */
    pst_tcp_head->ul_seqnum = 0;
    pst_tcp_head->ul_acknum = 0;
    /* 高4bit的4倍为TCP头的长度，这里设定为固定值20字节 */
    pst_tcp_head->uc_offset = 0x50;
    /* bit4为ack标记位，这里设置为1 */
    pst_tcp_head->uc_flags  = 0x18;
    pst_tcp_head->us_window = OAL_HTON_16(pst_tcp_params->us_window);
    /* check的值在dmac层设置这里写0 */
    pst_tcp_head->us_check  = 0;
    pst_tcp_head->us_urgent = 0;
    us_index += OAL_SIZEOF(mac_tcp_header_stru);

    *pus_offset = us_index;
    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : hmac_encap_udp_hearder
 功能描述  : 组UDP头
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年6月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_encap_udp_hearder(
                        oal_uint8 *puc_payload,
                        hmac_udp_params_stru *pst_udp_params,
                        oal_uint16 *pus_offset)
{
    oal_uint16    us_index     = 0;
    udp_hdr_stru *pst_udp_head = OAL_PTR_NULL;


    if ((OAL_PTR_NULL == puc_payload) || (OAL_PTR_NULL == pst_udp_params))
    {
        OAM_ERROR_LOG3(0, OAM_SF_ANY, "hmac_encap_tcp_hearder::puc_payload = 0x%x, pst_udp_params = 0x%x,pus_offset = 0x%x",puc_payload,pst_udp_params,pus_offset);
        return OAL_ERR_CODE_PTR_NULL;
    }
    us_index = *pus_offset;
    pst_udp_head = (udp_hdr_stru *)(puc_payload + us_index);
    pst_udp_head->us_src_port  = OAL_HTON_16(pst_udp_params->us_src_port);
    pst_udp_head->us_des_port  = OAL_HTON_16(pst_udp_params->us_dst_port);
    /* 包含8字节的UDP头 */
    /*lint -e572*/
    pst_udp_head->us_udp_len   = OAL_HTON_16(MAC_UDP_HEADER_LEN + pst_udp_params->ul_payload_len);
    /*lint +e572*/
    /* 该值在dmac层设置 */
    pst_udp_head->us_check_sum = 0;
    us_index += OAL_SIZEOF(udp_hdr_stru);

    *pus_offset = us_index;

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : hmac_encap_tcp
 功能描述  : 组装TCP帧
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint16 hmac_encap_tcp(
                mac_vap_stru *pst_mac_vap,
                oal_uint8 *puc_data,
                hmac_tcp_params_stru *pst_tcp_params)
{
    oal_uint16 us_frame_len = 0;
    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_data) || (OAL_PTR_NULL == pst_tcp_params))
    {
        OAM_ERROR_LOG3(0, OAM_SF_ANY, "hmac_encap_tcp::null point %x %x %x", pst_mac_vap, puc_data, pst_tcp_params);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 填充LLC头 */
    hmac_encap_llc_hearder(puc_data,&us_frame_len);
    /* 填充IP头 */
    hmac_encap_ip_hearder(puc_data, (oal_uint8 *)pst_tcp_params, &us_frame_len, HMAC_NETBUF_TYPE_TCP);
    /* 填充TCP头 */
    hmac_encap_tcp_hearder(puc_data, pst_tcp_params, &us_frame_len);
    /* 填充数据 */
    oal_memcopy(&puc_data[us_frame_len], pst_tcp_params->puc_tcp_payload, pst_tcp_params->ul_payload_len);
    us_frame_len += (oal_uint16)pst_tcp_params->ul_payload_len;
    return us_frame_len;
}
/*****************************************************************************
 函 数 名  : hmac_encap_udp
 功能描述  : 组装UDP帧
 输入参数  : pst_mac_vap: 当前对应的vap指针
             puc_data   : 申请到的内存首地址
             pst_udp_params: UDP参数节点指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint16 hmac_encap_udp(
                mac_vap_stru *pst_mac_vap,
                oal_uint8 *puc_data,
                hmac_udp_params_stru *pst_udp_params)
{
    oal_uint16 us_frame_len = 0;
    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_data) || (OAL_PTR_NULL == pst_udp_params))
    {
        OAM_ERROR_LOG3(0, OAM_SF_ANY, "hmac_encap_udp::null point %x %x %x", pst_mac_vap, puc_data, pst_udp_params);
        return OAL_ERR_CODE_PTR_NULL;
    }
    /* 填充LLC头 */
    hmac_encap_llc_hearder(puc_data,&us_frame_len);
    /* 填充IP头 */
    hmac_encap_ip_hearder(puc_data, (oal_uint8 *)pst_udp_params, &us_frame_len, HMAC_NETBUF_TYPE_UDP);
    /* 填充UDP头 */
    hmac_encap_udp_hearder(puc_data, pst_udp_params, &us_frame_len);
    /* 填充数据 */
    oal_memcopy(&puc_data[us_frame_len], pst_udp_params->puc_udp_payload, pst_udp_params->ul_payload_len);
    us_frame_len += (oal_uint16)(pst_udp_params->ul_payload_len);
    return us_frame_len;
}

/*****************************************************************************
 函 数 名  : hmac_tcp_udp_process
 功能描述  : 处理应用侧下发的TCP和UDP参数，并将组好的包和参数下发到device侧
 输入参数  : pst_mac_vap: 当前对应的vap指针
             us_len     : 传入参数的长度
             puc_param  : 传入的参数指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/

oal_uint32 hmac_tcp_udp_process(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    hmac_tcp_params_stru    *pst_host_tcp_params   = OAL_PTR_NULL;
    mac_tcp_params_stru      st_device_tcp_params;
    hmac_udp_params_stru    *pst_host_udp_params   = OAL_PTR_NULL;
    mac_udp_params_stru      st_device_udp_params;
    oal_uint16               us_frame_len;
    mac_tx_ctl_stru         *pst_tx_ctl            = OAL_PTR_NULL;
    oal_netbuf_stru         *pst_frame             = OAL_PTR_NULL;
    frw_event_mem_stru      *pst_event_mem;
    frw_event_stru          *pst_hmac_to_dmac_ctx_event;
    dmac_tx_event_stru      *pst_tx_event;
    oal_uint32               ul_ret;

    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_param))
    {
        OAM_ERROR_LOG2(0, OAM_SF_CFG, "hmac_config_set_tcp_udp_params::pst_mac_vap=%x,puc_param=%x",pst_mac_vap,puc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }
    /* 申请帧内存 */
    pst_frame = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_MEM_NETBUF_SIZE2, OAL_NETBUF_PRIORITY_MID);
    if (OAL_PTR_NULL == pst_frame)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_tcp_udp_process::NULL.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAL_MEM_NETBUF_TRACE(pst_frame, OAL_TRUE);
    OAL_MEMZERO(oal_netbuf_cb(pst_frame), OAL_NETBUF_CB_SIZE());

    OAL_NETBUF_PREV(pst_frame) = OAL_PTR_NULL;
    OAL_NETBUF_NEXT(pst_frame) = OAL_PTR_NULL;
    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_frame);
    MAC_GET_CB_TX_USER_IDX(pst_tx_ctl)   = pst_mac_vap->uc_assoc_vap_id;
    mac_set_cb_tid(pst_tx_ctl, 0);
    mac_set_cb_is_amsdu(pst_tx_ctl, OAL_FALSE);

    /*通过参数长度来判断是TCP连接参数还是UDP连接参数*/
    if (OAL_SIZEOF(hmac_tcp_params_stru) == us_len)
    {
        OAM_WARNING_LOG0(0, OAM_SF_CFG, "hmac_tcp_udp_process::TCP params");
        pst_host_tcp_params   = (hmac_tcp_params_stru*)puc_param;
        /*参数转换，dmac层不需要playload，所以只需要复制部分内容，注意必须保证两个结构体内的参数顺序相同*/
        oal_memcopy(&st_device_tcp_params, pst_host_tcp_params, OAL_SIZEOF(mac_tcp_params_stru));
        us_frame_len = hmac_encap_tcp(pst_mac_vap, oal_netbuf_data(pst_frame), pst_host_tcp_params);
        oal_memcopy((oal_uint8 *)(oal_netbuf_data(pst_frame) + us_frame_len), (oal_uint8 *)&st_device_tcp_params, OAL_SIZEOF(mac_tcp_params_stru));
        oal_netbuf_put(pst_frame, (us_frame_len + OAL_SIZEOF(mac_tcp_params_stru)));
        pst_tx_ctl->us_mpdu_len = us_frame_len + OAL_SIZEOF(mac_tcp_params_stru);
        pst_event_mem           = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_tx_event_stru));
        if (OAL_PTR_NULL == pst_event_mem)
        {
            OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_BA, "{hmac_tcp_udp_process::null, pst_event_mem mem alloc failed.}");
            oal_netbuf_free(pst_frame);

            return OAL_ERR_CODE_PTR_NULL;
        }
        pst_hmac_to_dmac_ctx_event = (frw_event_stru *)pst_event_mem->puc_data;
        FRW_EVENT_HDR_INIT(&(pst_hmac_to_dmac_ctx_event->st_event_hdr),
                       FRW_EVENT_TYPE_WLAN_CTX,
                       DMAC_TX_HOST_TCP_CRX,
                       OAL_SIZEOF(dmac_tx_event_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_mac_vap->uc_chip_id,
                       pst_mac_vap->uc_device_id,
                       pst_mac_vap->uc_vap_id);

        /* 填写事件payload */
        pst_tx_event = (dmac_tx_event_stru *)(pst_hmac_to_dmac_ctx_event->auc_event_data);

        pst_tx_event->pst_netbuf    = pst_frame;
        pst_tx_event->us_frame_len  = us_frame_len + OAL_SIZEOF(mac_tcp_params_stru);

        ul_ret = frw_event_dispatch_event(pst_event_mem);
        if (ul_ret != OAL_SUCC)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_BA, "{hmac_mgmt_tx_addba_rsp::send addba rsp failed, frw_event_dispatch_event failed[%d].}", ul_ret);
            oal_netbuf_free(pst_frame);
        }
        FRW_EVENT_FREE(pst_event_mem);

    }
    else if (OAL_SIZEOF(hmac_udp_params_stru) == us_len)
    {
        OAM_WARNING_LOG0(0, OAM_SF_CFG, "hmac_tcp_udp_process::UDP params");

        pst_host_udp_params   = (hmac_udp_params_stru *)puc_param;
        if (OAL_PTR_NULL == pst_host_udp_params)
        {
            OAM_ERROR_LOG0(0, OAM_SF_ANY, "hmac_tcp_udp_process::pst_host_udp_params is null");
        }
        /*参数转换，dmac层不需要playload，所以只需要复制部分内容，注意必须保证两个结构体内的参数顺序相同*/
        oal_memcopy(&st_device_udp_params, pst_host_udp_params, OAL_SIZEOF(mac_udp_params_stru));
        us_frame_len = hmac_encap_udp(pst_mac_vap, oal_netbuf_data(pst_frame), pst_host_udp_params);
        oal_memcopy((oal_uint8 *)(oal_netbuf_data(pst_frame) + us_frame_len), (oal_uint8 *)&st_device_udp_params, OAL_SIZEOF(mac_udp_params_stru));
        oal_netbuf_put(pst_frame, (us_frame_len + OAL_SIZEOF(mac_udp_params_stru)));
        pst_tx_ctl->us_mpdu_len = us_frame_len + OAL_SIZEOF(mac_udp_params_stru);
        pst_event_mem           = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_tx_event_stru));
        if (OAL_PTR_NULL == pst_event_mem)
        {
            OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_tcp_udp_process::null, pst_event_mem mem alloc failed.}");
            oal_netbuf_free(pst_frame);

            return OAL_ERR_CODE_PTR_NULL;
        }
        pst_hmac_to_dmac_ctx_event = (frw_event_stru *)pst_event_mem->puc_data;
        FRW_EVENT_HDR_INIT(&(pst_hmac_to_dmac_ctx_event->st_event_hdr),
                       FRW_EVENT_TYPE_WLAN_CTX,
                       DMAC_TX_HOST_UDP_CRX,
                       OAL_SIZEOF(dmac_tx_event_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_mac_vap->uc_chip_id,
                       pst_mac_vap->uc_device_id,
                       pst_mac_vap->uc_vap_id);

        /* 填写事件payload */
        pst_tx_event = (dmac_tx_event_stru *)(pst_hmac_to_dmac_ctx_event->auc_event_data);
        pst_tx_event->pst_netbuf    = pst_frame;
        pst_tx_event->us_frame_len  = us_frame_len + OAL_SIZEOF(mac_tcp_params_stru);

        ul_ret = frw_event_dispatch_event(pst_event_mem);
        if (ul_ret != OAL_SUCC)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_BA, "{hmac_mgmt_tx_addba_rsp::send addba rsp failed, frw_event_dispatch_event failed[%d].}", ul_ret);
            oal_netbuf_free(pst_frame);
        }

        FRW_EVENT_FREE(pst_event_mem);
    }
    else
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "hmac_tcp_udp_process:: params is wrong");
    }
    return OAL_SUCC;
}
#endif
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif




