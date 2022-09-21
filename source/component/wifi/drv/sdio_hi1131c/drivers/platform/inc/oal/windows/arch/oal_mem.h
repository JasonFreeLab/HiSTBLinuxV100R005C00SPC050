/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : oal_mem.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年9月19日
  最近修改   :
  功能描述   : oal_mem.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年9月19日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __OAL_WINDOWS_MEM_H__
#define __OAL_WINDOWS_MEM_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/


/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define OAL_HCC_HDR_LEN 8
#define OAL_MAX_CB_LEN  19
#define OAL_TX_CB_LEN   19

#define MAX_MAC_HEAD_LEN            WLAN_MAX_MAC_HDR_LEN              //不包含4地址的最大MAC头长度30 4字节对齐到32
#define MAC_HEAD_OFFSET   (OAL_NETBUF_MACHDR_BYTE_LEN - MAX_MAC_HEAD_LEN)
#define CB_OFFSET         (OAL_NETBUF_MACHDR_BYTE_LEN - MAX_MAC_HEAD_LEN - OAL_MAX_CB_LEN)

/* 对于enhanced类型的申请接口与释放接口，每一个内存块都包含一个4字节的头部， */
/* 用来指向内存块管理结构体oal_mem_struc，整个内存块的结构如下所示。           */
/*                                                                           */
/* +-------------------+------------------------------------------+---------+ */
/* | oal_mem_stru addr |                    payload               | dog tag | */
/* +-------------------+------------------------------------------+---------+ */
/* |      4 byte       |                                          | 4 byte  | */
/* +-------------------+------------------------------------------+---------+ */
#define OAL_MEM_INFO_SIZE            4
/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

/*****************************************************************************
  枚举名  : oal_mem_netbuf_pool_id_enum_uint8
  协议表格:
  枚举说明: netbuf内存池ID
*****************************************************************************/
typedef enum
{
    OAL_MEM_NETBUF_POOL_ID_SHORT_PKT = 0,                /* 短帧内存池 */
    OAL_MEM_NETBUF_POOL_ID_MGMT_PKT,                     /* 管理帧 */
    OAL_MEM_NETBUF_POOL_ID_LARGE_PKT,                    /* 长帧内存池 */
    OAL_MEM_NETBUF_POOL_ID_OAM_PKT,                      /* SDT内存池 */

    OAL_MEM_NETBUF_POOL_ID_BUTT
}oal_mem_netbuf_pool_id_enum;
typedef oal_uint8 oal_mem_netbuf_pool_id_enum_uint8;

/*****************************************************************************
  结构名  : oal_netbuf_subpool_stru
  结构说明: 裸系统下netbuf子内存池结构体
*****************************************************************************/
typedef struct
{
    oal_uint16            us_free_cnt;         /* 本子内存池可用内存块数 */
    oal_uint16            us_total_cnt;        /* 本子内存池内存块总数 */
    oal_uint16            us_start_index;      /* 本子内存池paylaod的起始index */
    oal_uint16            us_len;              /* 本子内存池的内存块长度 */

    /* 记录oal_netbuf_stru可用内存索引表的栈顶元素，其内容为oal_netbuf_stru指针 */
    oal_netbuf_stru       *pst_free_stack;
} oal_netbuf_subpool_stru;

/*****************************************************************************
  结构名  : oal_netbuf_pool_stru
  结构说明: 裸系统下netbuf内存池配置结构体
*****************************************************************************/
typedef struct oal_netbuf_pool
{
    oal_uint16              us_max_byte_len;        /* 本内存池可分配内存块最大长度 */
    oal_uint16              us_mem_total_cnt;       /* 本内存池一共有多少内存块 */
    oal_uint16              us_mem_used_cnt;        /* 本内存池已用内存块 */
    oal_uint8               uc_subpool_cnt;         /* 本内存池一共有多少子内存池 */
    oal_uint8               uc_reserved;
    /* 子内存池索引表数组 */
    oal_netbuf_subpool_stru    ast_subpool_table[OAL_MEM_NETBUF_POOL_ID_BUTT];

}oal_netbuf_pool_stru;
 //typedef oal_netbuf_pool oal_netbuf_pool_stru;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/
/* device 侧裸系统和 host侧的函数输出 */
extern oal_uint8 *oal_netbuf_cb(oal_netbuf_stru *pst_netbuf);
extern oal_uint8 *oal_netbuf_data(oal_netbuf_stru *pst_netbuf);
extern oal_uint8* oal_netbuf_header(oal_netbuf_stru *pst_netbuf);
extern oal_uint8* oal_netbuf_payload(oal_netbuf_stru *pst_netbuf);

extern oal_uint32  oal_netbuf_get_len(oal_netbuf_stru *pst_netbuf);
extern oal_netbuf_stru  *oal_netbuf_alloc(oal_uint32 ul_size, oal_int32 l_reserve, oal_int32 l_align);
extern oal_uint32  oal_mem_netbuf_free(oal_uint32  ul_file_id,
                                                oal_uint32      ul_line_num,
                                                oal_netbuf_stru   *pst_netbuf,
                                                oal_uint8          uc_lock);
extern oal_uint32  oal_netbuf_free(oal_netbuf_stru *pst_netbuf);
extern oal_uint8   *oal_netbuf_get_mac_hdr_addr(oal_netbuf_stru *pst_netbuf);
extern oal_void  oal_netbuf_queue_purge(oal_netbuf_head_stru  *pst_netbuf_head);
extern oal_void  oal_netbuf_set_len(oal_netbuf_stru *pst_netbuf, oal_uint32 ul_len);
extern oal_uint8   *oal_netbuf_get_hcc_hdr_addr(oal_netbuf_stru *pst_netbuf);
extern oal_uint8   *oal_netbuf_get_payload_addr(oal_netbuf_stru * pst_netbuf);
extern oal_netbuf_stru* oal_mem_multi_netbuf_alloc(oal_uint32 ul_file_id, oal_uint32 ul_line_num, oal_uint32 ul_len);
extern oal_netbuf_stru *oal_netbuf_get_ctrl_blk(oal_uint16  us_index);
extern oal_uint32 oal_mem_multi_netbuf_free(oal_uint32  ul_line_num, oal_netbuf_stru   *pst_netbuf);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_mm.h */

