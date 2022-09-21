/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : oam_linux_netlink.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2014年5月15日
  最近修改   :
  功能描述   : netlink处理文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年5月15日
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
#include "oam_ext_if.h"
#include "oam_linux_netlink.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_OAM_LINUX_NETLINK_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
oam_netlink_stru        g_st_netlink;

oam_netlink_proto_ops   g_st_netlink_ops;

/* 数采上报app的结构体 */
typedef struct
{
    oal_uint32      ul_daq_addr;         /* 数采数据首地址 */
    oal_uint32      ul_data_len;         /* 数采数据总的长度 */
    oal_uint32      ul_unit_len;         /* 单元数据的最大长度:不包含(daq_unit_head)头长度 */
}oam_data_acq_info_stru;

/* 数采单元头结构体 */
typedef struct
{
    oal_uint8                           en_send_type;        /* 数采单元数据序列号 */
    oal_uint8                           uc_resv[3];
    oal_uint32                          ul_msg_sn;           /* 数采单元数据序列号 */
    oal_uint32                          ul_data_len;         /* 当前单元长度 */
}oam_data_acq_data_head_stru;

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : oam_netlink_ops_register
 功能描述  : WAL模块向其它模块提供的注册netlink消息处理函数(接收方向)
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  oam_netlink_ops_register(oam_nl_cmd_enum_uint8 en_type, oal_uint32 (*p_func)(oal_uint8 *puc_data, oal_uint32 ul_len))
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == p_func))
    {
        OAL_IO_PRINT("oam_netlink_ops_register, p_func is null ptr.");
        return;
    }

    switch (en_type)
    {
        case OAM_NL_CMD_SDT:
            g_st_netlink_ops.p_oam_sdt_func = p_func;
            break;

        case OAM_NL_CMD_HUT:
            g_st_netlink_ops.p_oam_hut_func = p_func;
            break;

        case OAM_NL_CMD_ALG:
            g_st_netlink_ops.p_oam_alg_func = p_func;
            break;

        case OAM_NL_CMD_DAQ:
            g_st_netlink_ops.p_oam_daq_func = p_func;
            break;

        case OAM_NL_CMD_REG:
            g_st_netlink_ops.p_oam_reg_func = p_func;
            break;

        case OAM_NL_CMD_ACS:
            g_st_netlink_ops.p_oam_acs_func = p_func;
            break;

        default:
            OAL_IO_PRINT("oam_netlink_ops_register, err type = %d.", en_type);
            break;
    }
}

/*****************************************************************************
 函 数 名  : oam_netlink_ops_unregister
 功能描述  : OAM模块向其它模块提供的卸载netlink消息处理函数(接收方向)
 输入参数  : en_type: 模块类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  oam_netlink_ops_unregister(oam_nl_cmd_enum_uint8 en_type)
{
    switch (en_type)
    {
        case OAM_NL_CMD_SDT:
            g_st_netlink_ops.p_oam_sdt_func = OAL_PTR_NULL;
            break;

        case OAM_NL_CMD_HUT:
            g_st_netlink_ops.p_oam_hut_func = OAL_PTR_NULL;
            break;

        case OAM_NL_CMD_ALG:
            g_st_netlink_ops.p_oam_alg_func = OAL_PTR_NULL;
            break;

        case OAM_NL_CMD_DAQ:
            g_st_netlink_ops.p_oam_daq_func = OAL_PTR_NULL;
            break;

        case OAM_NL_CMD_REG:
            g_st_netlink_ops.p_oam_reg_func = OAL_PTR_NULL;
            break;

        case OAM_NL_CMD_ACS:
            g_st_netlink_ops.p_oam_acs_func = OAL_PTR_NULL;
            break;

        default:
            OAL_IO_PRINT("oam_netlink_ops_unregister::err type = %d.", en_type);
            break;
    }
}

/*****************************************************************************
 函 数 名  : oam_netlink_kernel_recv
 功能描述  : netlink消息接收函数(方向: host app -> 内核)
 输入参数  : pst_buf: 输入数据
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  oam_netlink_kernel_recv(oal_netbuf_stru *pst_buf)
{
    oal_netbuf_stru     *pst_netbuf;
    oal_nlmsghdr_stru   *pst_nlmsghdr;

    if (OAL_PTR_NULL == pst_buf)
    {
        OAL_IO_PRINT("oam_netlink_kernel_recv, pst_buf is null.");
        return;
    }

    pst_netbuf = oal_netbuf_get(pst_buf);

    while (OAL_NETBUF_LEN(pst_netbuf) >= OAL_NLMSG_SPACE(0))
    {
        pst_nlmsghdr = oal_nlmsg_hdr(pst_netbuf);

        g_st_netlink.ul_pid = pst_nlmsghdr->nlmsg_pid;

        switch (pst_nlmsghdr->nlmsg_type)
        {
            case OAM_NL_CMD_SDT:
                if (OAL_PTR_NULL != g_st_netlink_ops.p_oam_sdt_func)
                {
                    g_st_netlink_ops.p_oam_sdt_func(OAL_NLMSG_DATA(pst_nlmsghdr), OAL_NLMSG_PAYLOAD(pst_nlmsghdr, 0));
                }
                break;

            case OAM_NL_CMD_HUT:
                if (OAL_PTR_NULL != g_st_netlink_ops.p_oam_hut_func)
                {
                    g_st_netlink_ops.p_oam_hut_func(OAL_NLMSG_DATA(pst_nlmsghdr), OAL_NLMSG_PAYLOAD(pst_nlmsghdr, 0));
                }
                break;

            case OAM_NL_CMD_ALG:
                if (OAL_PTR_NULL != g_st_netlink_ops.p_oam_alg_func)
                {
                    g_st_netlink_ops.p_oam_alg_func(OAL_NLMSG_DATA(pst_nlmsghdr), OAL_NLMSG_PAYLOAD(pst_nlmsghdr, 0));
                }
                break;
            case OAM_NL_CMD_DAQ:
                if (OAL_PTR_NULL != g_st_netlink_ops.p_oam_daq_func)
                {
                    g_st_netlink_ops.p_oam_daq_func(OAL_NLMSG_DATA(pst_nlmsghdr), OAL_NLMSG_PAYLOAD(pst_nlmsghdr, 0));
                }
                break;
            case OAM_NL_CMD_REG:
                if (OAL_PTR_NULL != g_st_netlink_ops.p_oam_reg_func)
                {
                    g_st_netlink_ops.p_oam_reg_func(OAL_NLMSG_DATA(pst_nlmsghdr), OAL_NLMSG_PAYLOAD(pst_nlmsghdr, 0));
                }
                break;
            case OAM_NL_CMD_ACS:
                if (OAL_PTR_NULL != g_st_netlink_ops.p_oam_acs_func)
                {
                    g_st_netlink_ops.p_oam_acs_func(OAL_NLMSG_DATA(pst_nlmsghdr), OAL_NLMSG_PAYLOAD(pst_nlmsghdr, 0));
                }
                break;
            default:
                // OAL_IO_PRINT("oam_netlink_kernel_recv, error nlmsg_type = %d.\n", pst_nlmsghdr->nlmsg_type);
                break;
        }

        oal_netbuf_pull(pst_netbuf, OAL_NLMSG_ALIGN(pst_nlmsghdr->nlmsg_len));
    }

    oal_netbuf_free(pst_netbuf);
}

/*****************************************************************************
 函 数 名  : oam_netlink_kernel_send
 功能描述  : netlink消息发送函数(方向: 内核 -> host app)
 输入参数  : puc_data   : 输入数据
             ul_data_len: 数据长度
             en_type    : netlink msg类型
 输出参数  : 无
 返 回 值  : 成功: 发送的字节数(netlink头 + payload + padding)
             失败: 其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32  oam_netlink_kernel_send(oal_uint8 *puc_data, oal_uint32 ul_data_len, oam_nl_cmd_enum_uint8 en_type)
{
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
          
	    return 0;
#else
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,44))
        /*TBD*/
        return 0;
#else

    oal_netbuf_stru     *pst_netbuf;
    oal_nlmsghdr_stru   *pst_nlmsghdr;
    oal_uint32           ul_size;
    oal_int32            l_ret;

    ul_size = OAL_NLMSG_SPACE(ul_data_len);
    pst_netbuf = oal_netbuf_alloc(ul_size, 0, WLAN_MEM_NETBUF_ALIGN);
    if (OAL_PTR_NULL == pst_netbuf)
    {
        return -1;
    }

    /* 初始化netlink消息首部 */
    pst_nlmsghdr = oal_nlmsg_put(pst_netbuf, 0, 0, (oal_int32)en_type, (oal_int32)ul_data_len, 0);

    /* 设置控制字段 */
    OAL_NETLINK_CB(pst_netbuf).pid = 0;
    OAL_NETLINK_CB(pst_netbuf).dst_group = 0;

    /* 填充数据区 */
    oal_memcopy(OAL_NLMSG_DATA(pst_nlmsghdr), puc_data, ul_data_len);

    /* 发送数据 */
    l_ret = oal_netlink_unicast(g_st_netlink.pst_nlsk, pst_netbuf, g_st_netlink.ul_pid, OAL_MSG_DONTWAIT);

    return l_ret;
#endif
#endif
}

/*****************************************************************************
 函 数 名  : oam_netlink_kernel_send_ex
 功能描述  : netlink消息发送函数(方向: 内核 -> host app)
 输入参数  : puc_data_1st: 输入数据1
             puc_data_2nd: 输入数据2
             ul_len_1st  : 数据长度1
             ul_len_2nd  : 数据长度2
             en_type     : netlink msg类型
 输出参数  : 无
 返 回 值  : 成功: 发送的字节数(netlink头 + payload + padding)
             失败: 其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32  oam_netlink_kernel_send_ex(oal_uint8 *puc_data_1st, oal_uint8 *puc_data_2nd,
                                      oal_uint32 ul_len_1st, oal_uint32 ul_len_2nd,
                                      oam_nl_cmd_enum_uint8 en_type)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,44))
        /*TBD*/
        return 0;
#else

    oal_netbuf_stru     *pst_netbuf;
    oal_nlmsghdr_stru   *pst_nlmsghdr;
    oal_uint32           ul_size;
    oal_int32            l_ret;

    ul_size = OAL_NLMSG_SPACE(ul_len_1st + ul_len_2nd);
    pst_netbuf = oal_netbuf_alloc(ul_size, 0, WLAN_MEM_NETBUF_ALIGN);
    if (OAL_PTR_NULL == pst_netbuf)
    {
        return -1;
    }

    /* 初始化netlink消息首部 */
    pst_nlmsghdr = oal_nlmsg_put(pst_netbuf, 0, 0, (oal_int32)en_type, (oal_int32)(ul_len_1st + ul_len_2nd), 0);

    /* 设置控制字段 */
    OAL_NETLINK_CB(pst_netbuf).pid = 0;
    OAL_NETLINK_CB(pst_netbuf).dst_group = 0;

    /* 填充数据区 */
    oal_memcopy(OAL_NLMSG_DATA(pst_nlmsghdr), puc_data_1st, ul_len_1st);
    oal_memcopy((oal_uint8 *)OAL_NLMSG_DATA(pst_nlmsghdr) + ul_len_1st, puc_data_2nd, ul_len_2nd);

    /* 发送数据 */
    l_ret = oal_netlink_unicast(g_st_netlink.pst_nlsk, pst_netbuf, g_st_netlink.ul_pid, OAL_MSG_DONTWAIT);

    return l_ret;
#endif
}

/*****************************************************************************
 函 数 名  : oam_kernel_netlink_create
 功能描述  : 内核netlink创建函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功: OAL_SUCC
             失败: 其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_netlink_kernel_create(oal_void)
{
    g_st_netlink.pst_nlsk = oal_netlink_kernel_create(&OAL_INIT_NET, OAM_NETLINK_ID, 0, oam_netlink_kernel_recv, OAL_PTR_NULL, OAL_THIS_MODULE);
    if (OAL_PTR_NULL == g_st_netlink.pst_nlsk)
    {
        OAL_IO_PRINT("oam_netlink_kernel_create, can not create netlink.");

        return OAL_ERR_CODE_PTR_NULL;
    }

    OAL_IO_PRINT("netlink create succ.");

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_netlink_kernel_destroy
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  oam_netlink_kernel_release(oal_void)
{
    oal_netlink_kernel_release(g_st_netlink.pst_nlsk);

    g_st_netlink.ul_pid = 0;

    OAL_IO_PRINT("netlink release succ.");
}


/*lint -e578*//*lint -e19*/
oal_module_symbol(g_st_netlink_ops);
oal_module_symbol(oam_netlink_ops_register);
oal_module_symbol(oam_netlink_ops_unregister);
oal_module_symbol(oam_netlink_kernel_send);
oal_module_symbol(oam_netlink_kernel_send_ex);

#elif (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)

#endif












#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

