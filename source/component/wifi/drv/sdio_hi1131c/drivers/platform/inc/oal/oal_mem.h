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

#ifndef __OAL_MEM_H__
#define __OAL_MEM_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "platform_spec.h"
#include "oal_cache.h"
#include "oal_list.h"
#include "oal_schedule.h"
#include "oal_net.h"
#include "oal_util.h"
#include "arch/oal_mem.h"

#if ((_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE) && (_PRE_OS_VERSION == _PRE_OS_VERSION_LINUX))
#include <linux/kallsyms.h>
#endif
/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define OAL_MEM_NETBUF_ALLOC(_uc_out_subpool_id,_us_len,_uc_netbuf_priority) \
    oal_netbuf_alloc(_us_len,0, WLAN_MEM_NETBUF_ALIGN)
#ifdef _PRE_DEBUG_MODE
#define OAL_MEM_NETBUF_TRACE(_pst_netbuf, _uc_lock)
#else
#define OAL_MEM_NETBUF_TRACE(_pst_netbuf, _uc_lock)
#endif
/*Local Mem 所有接口的 _uc_lock 参数不再生效 2016/8/29*/
/* 除netbuf内存池外的其他内存池的对外提供接口 host和device共用接口 */
#define OAL_MEM_ALLOC(_en_pool_id, _us_len, _uc_lock) \
    oal_mem_alloc(THIS_FILE_ID, __LINE__, _en_pool_id, _us_len, _uc_lock)
#define OAL_MEM_FREE(_p_data, _uc_lock) \
    oal_mem_free(THIS_FILE_ID, __LINE__, _p_data, _uc_lock)

#define OAL_MEM_FREE_ARRAY(_p_data, _num) \
    oal_mem_free_array(THIS_FILE_ID, __LINE__, _p_data, _num)

#define OAL_MEM_INCR_USER(_pst_mem, _uc_lock) \
    oal_mem_incr_user(THIS_FILE_ID, __LINE__, _pst_mem, _uc_lock)

#define OAL_MEM_ALLOC_ENHANCED(_en_pool_id, _us_len, _uc_lock) \
    oal_mem_alloc_enhanced(THIS_FILE_ID, __LINE__, _en_pool_id, _us_len, _uc_lock)

#define OAL_MEM_FREE_ENHANCED(_pst_mem, _uc_lock) \
    oal_mem_free_enhanced(THIS_FILE_ID, __LINE__, _pst_mem, _uc_lock)

/* host输出内存信息接口 */
#define OAL_MEM_INFO_PRINT(_pool_id)

#ifdef _PRE_DEBUG_MODE
#define OAL_MEM_TRACE(_p_data, _uc_lock) \
    oal_mem_trace(THIS_FILE_ID, __LINE__, _p_data, _uc_lock)

#define OAL_MEM_TRACE_ENHANCED(_pst_mem, _uc_lock) \
    oal_mem_trace_enhanced(THIS_FILE_ID, __LINE__, _pst_mem, _uc_lock)
#else
#define OAL_MEM_TRACE(_p_data, _uc_lock)
#define OAL_MEM_TRACE_ENHANCED(_pst_mem, _uc_lock)
#endif

/* 对于enhanced类型的申请接口与释放接口，每一个内存块都包含一个4字节的头部， */
/* 用来指向内存块管理结构体oal_mem_struc，整个内存块的结构如下所示。           */
/*                                                                           */
/* +-------------------+------------------------------------------+---------+ */
/* | oal_mem_stru addr |                    payload               | dog tag | */
/* +-------------------+------------------------------------------+---------+ */
/* |      4/8 byte       |                                          | 4 byte  | */
/* +-------------------+------------------------------------------+---------+ */
#define OAL_DOG_TAG    0x5b3a293e    /* 狗牌，用于检测内存越界 */

#ifdef _PRE_DEBUG_MODE
#ifdef CONFIG_ARM64
#define OAL_DOG_TAG_SIZE             8   /* 狗牌大小(8字节) */
#else
#define OAL_DOG_TAG_SIZE             4   /* 狗牌大小(4字节) */
#endif
#define OAL_NETBUF_MAINTAINS_SIZE    24  /* alloc_file_id(4B) + alloc_line_num(4B) + alloc_timestamp(4B) + */
                                         /* trace_file_id(4B) + trace_line_num(4B) + trace_timestamp(4B)   */
#else
#define OAL_DOG_TAG_SIZE             0
#define OAL_NETBUF_MAINTAINS_SIZE    0
#endif

#define OAL_NETBUF_DEFAULT_HEADROOM  256 /*申请netbuf时候默认的headroom*/
#define OAL_MAX_TX_DSCR_CNT_IN_LIST  100
#define OAL_TX_DSCR_ITEM_NUM         200
#define OAL_TX_DSCR_RCD_TAIL_CNT     20

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
#if(_PRE_OS_VERSION == _PRE_OS_VERSION_LINUX)
#define OAL_MEM_SPRINT_SYMBOL_SIZE    KSYM_SYMBOL_LEN
#else
#define OAL_MEM_SPRINT_SYMBOL_SIZE    1
#endif
#endif
/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
  枚举名  : oal_mem_pool_id_enum_uint8
  协议表格:
  枚举说明: HOST侧内存池ID
*****************************************************************************/
typedef enum
{
    OAL_MEM_POOL_ID_EVENT = 0,              /* 事件内存池 */
    OAL_MEM_POOL_ID_SHARED_DATA_PKT,        /* 共享数据帧内存池 */
    OAL_MEM_POOL_ID_SHARED_MGMT_PKT,        /* 共享管理帧内存池 */
    OAL_MEM_POOL_ID_LOCAL,                  /* 本地变量内存池  */
    OAL_MEM_POOL_ID_MIB,                    /* MIB内存池 */
    OAL_MEM_POOL_ID_SHARED_DSCR,            /* 共享描述符内存池 */

    //OAL_MEM_POOL_ID_NETBUF,                 /* netbuf内存池 */
    OAL_MEM_POOL_ID_SDT_NETBUF,             /* SDT netbuf内存池 */

    OAL_MEM_POOL_ID_BUTT
}oal_mem_pool_id_enum;
typedef oal_uint8 oal_mem_pool_id_enum_uint8;
/*****************************************************************************
  枚举名  : oal_netbuf_priority_enum_uint8
  协议表格:
  枚举说明: netbuf优先级
*****************************************************************************/
typedef enum
{
    OAL_NETBUF_PRIORITY_LOW     = 0,  //最低优先级,不能跨池申请
    OAL_NETBUF_PRIORITY_MID     = 1,  //中间优先级，可以跨池申请，但不能申请大包的最后N片
    OAL_NETBUF_PRIORITY_HIGH    = 2,  //最高优先级，可以跨池申请，且可以申请大包的最后N片

    OAL_NETBUF_PRIORITY_BUTT
}oal_netbuf_priority_enum;
typedef oal_uint8 oal_netbuf_priority_enum_uint8;

/*****************************************************************************
  枚举名  : oal_netbuf_id_enum_uint8
  协议表格:
  枚举说明: 对外提供netbuf内存池ID
*****************************************************************************/
typedef enum
{
    OAL_NORMAL_NETBUF = 0,                /* 包括短帧、长帧内存池 */
    OAL_MGMT_NETBUF   = 1,                /* 管理帧内存池 */
    OAL_OAM_NETBUF    = 2,                /* SDT内存池 */

    OAL_NETBUF_POOL_ID_BUTT
}oal_netbuf_id_enum;
typedef oal_uint8 oal_netbuf_id_enum_uint8;

#define OAL_MEM_POOL_ID_ALG_LOCAL  OAL_MEM_POOL_ID_LOCAL
#define OAL_MEM_POOL_ID_HI_LOCAL   OAL_MEM_POOL_ID_LOCAL

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
typedef struct
{
    oal_uint32  (* p_mempool_info_func)(oal_uint8 en_pool_id,
                                        oal_uint16 us_mem_total_cnt,
                                        oal_uint16 us_mem_used_cnt,
                                        oal_uint8  uc_subpool_id,
                                        oal_uint16 us_total_cnt,
                                        oal_uint16 us_free_cnt);
    oal_uint32  (* p_memblock_info_func)(oal_uint8 *puc_origin_data,
                                         oal_uint8                   uc_user_cnt,
                                         oal_mem_pool_id_enum_uint8  en_pool_id,
                                         oal_uint8                   uc_subpool_id,
                                         oal_uint16                  us_len,
                                         oal_uint32                  ul_alloc_file_id,
                                         oal_uint32                  ul_alloc_line_num);

}oal_mempool_info_to_sdt_stru;

/*****************************************************************************
  结构名  : oal_mem_netbuf_info_stru
  结构说明: netbuf内存块维测结构体
*****************************************************************************/
typedef struct
{
    oal_uint32   ul_dog_tag;            /* 狗牌，用于内存写越界检查 */
    oal_uint32   ul_alloc_file_id;      /* 申请netbuf内存时的文件ID */
    oal_uint32   ul_alloc_line_num;     /* 申请netbuf内存时的行号 */
    oal_uint32   ul_alloc_time_stamp;   /* 申请netbuf内存时的时间戳 */
    oal_uint32   ul_trace_file_id;      /* netbuf内存在关键路径上的文件ID */
    oal_uint32   ul_trace_line_num;     /* netbuf内存在关键路径上的行号 */
    oal_uint32   ul_trace_time_stamp;   /* netbuf内存在关键路径上的时间戳 */
}oal_mem_netbuf_info_stru;

/*****************************************************************************
  结构名  : oal_mem_stru
  结构说明: 内存块结构体
*****************************************************************************/
struct oal_mem_stru_tag
{
    oal_uint8                  *puc_data;                                   /* 存放数据的指针 */
    oal_uint8                  *puc_origin_data;                            /* 记录数据的原始指针 */
#if 0
    oal_uint8                   uc_user_cnt;                                /* 申请本内存块的用户计数 */
    oal_mem_state_enum_uint8    en_mem_state_flag;                          /* 内存块状态 */
    oal_mem_pool_id_enum_uint8  en_pool_id;                                 /* 本内存属于哪一个内存池 */
    oal_uint8                   uc_subpool_id;                              /* 本内存是属于哪一级子内存池 */
    oal_uint16                  us_len;                                     /* 内存块的长度 */
    oal_uint8                   auc_resv[2];
    oal_dlist_head_stru         st_list;
#endif
    oal_uint16                  us_len;                                     /* 内存块的长度 */
    oal_uint8                   uc_user_cnt       :4;                       /* 申请本内存块的用户计数 */
    oal_mem_state_enum_uint8    en_mem_state_flag :4;                       /* 内存块状态 */
    oal_mem_pool_id_enum_uint8  en_pool_id        :4;                       /* 本内存属于哪一个内存池 */
    oal_uint8                   uc_subpool_id     :4;                       /* 本内存是属于哪一级子内存池 */

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_ulong                  ul_return_addr;                              /* alloc内存的函数地址 新增 */
#endif


    /* 内存调试信息 */
#ifdef _PRE_DEBUG_MODE
    oal_uint32                  ul_alloc_core_id[WLAN_MEM_MAX_USERS_NUM];    /* 申请内存时的内核ID */
    oal_uint32                  ul_alloc_file_id[WLAN_MEM_MAX_USERS_NUM];    /* 申请内存时的文件ID */
    oal_uint32                  ul_alloc_line_num[WLAN_MEM_MAX_USERS_NUM];   /* 申请内存时的行号 */
    oal_uint32                  ul_alloc_time_stamp[WLAN_MEM_MAX_USERS_NUM]; /* 申请内存时的时间戳 */
    oal_uint32                  ul_trace_file_id;                            /* 内存在关键路径上的文件ID */
    oal_uint32                  ul_trace_line_num;                           /* 内存在关键路径上的行号 */
    oal_uint32                  ul_trace_time_stamp;                         /* 内存在关键路径上的时间戳 */
#endif
}oal_cacheline_aligned;
typedef struct oal_mem_stru_tag  oal_mem_stru;


/*****************************************************************************
  结构名  : oal_mem_subpool_stru
  结构说明: 子内存池结构体
*****************************************************************************/
typedef struct
{
    oal_spin_lock_stru    st_spinlock;
    oal_uint16            us_len;             /* 本子内存池的内存块长度 */
    oal_uint16            us_free_cnt;        /* 本子内存池可用内存块数 */

    /* 记录oal_mem_stru可用内存索引表的栈顶元素，其内容为oal_mem_stru指针 */
    void                **ppst_free_stack;

    oal_uint16            us_total_cnt;       /* 本子内存池内存块总数 */
    oal_uint8             auc_resv[2];
} oal_mem_subpool_stru;

/*****************************************************************************
  结构名  : oal_mem_pool_stru
  结构说明: 内存池结构体
*****************************************************************************/
typedef struct
{
    oal_uint16              us_max_byte_len;        /* 本内存池可分配内存块最大长度 */
    oal_uint8               uc_subpool_cnt;         /* 本内存池一共有多少子内存池 */
    oal_uint8               uc_resv;
    /* 子内存池索引表数组 */
    oal_mem_subpool_stru    ast_subpool_table[WLAN_MEM_MAX_SUBPOOL_NUM];

    oal_uint16              us_mem_used_cnt;        /* 本内存池已用内存块 */
    oal_uint16              us_mem_total_cnt;       /* 本内存池一共有多少内存块 */
    oal_mem_stru           *pst_mem_start_addr;
}oal_mem_pool_stru;

/*****************************************************************************
  结构名  : oal_mem_subpool_cfg_stru
  结构说明: 子内存池配置结构体
*****************************************************************************/
typedef struct
{
    oal_uint16  us_size;    /* 本子内存池内存块大小 */
    oal_uint16  us_cnt;     /* 本子内存池内存块个数 */
}oal_mem_subpool_cfg_stru;

/*****************************************************************************
  结构名  : oal_mem_pool_cfg_stru
  结构说明: 内存池配置结构体
*****************************************************************************/
typedef struct
{
    oal_mem_pool_id_enum_uint8          en_pool_id;      /* 内存池ID */
    oal_uint8                           uc_subpool_cnt;  /* 本内存池子内存池个数 */

    oal_uint8                           auc_resv[2];

    /* 指向每一子内存池具体配置信息 */
    oal_mem_subpool_cfg_stru  *pst_subpool_cfg_info;
}oal_mem_pool_cfg_stru;

#ifdef _PRE_DEBUG_MODE
typedef struct
{
    oal_uint    ul_released_addr;
    oal_uint32  ul_release_file_id;
    oal_uint32  ul_release_line_num;
    oal_uint32  ul_release_ts;
    oal_uint32  ul_tx_dscr_in_up_intr;          /*上半部处理的描述符地址*/
    oal_uint32  ul_up_intr_ts;                  /*上半部处理的时间*/
    oal_uint32  ul_tx_dscr_in_dn_intr;          /*下半部处理的描述符地址*/
    oal_uint32  ul_dn_intr_ts;                  /*下半部处理的时间*/
    oal_uint32  ul_tx_dscr_in_q[OAL_MAX_TX_DSCR_CNT_IN_LIST];//存放dev发送队列中的描述地址
    oal_uint8   uc_mpdu_num;                    /*mpdu数目*/
    oal_uint8   uc_q_num;                       /*队列*/
    oal_uint16  bit_dscr_is_overflow  : 1;      /*ul_tx_dscr_in_q数组记录不够，溢出标志*/
    oal_uint16  bit_resv              : 15;
}oal_mempool_tx_dscr_info;

typedef struct
{
    oal_uint     ul_tx_dscr_addr[WLAN_MEM_SHARED_TX_DSCR_CNT1 + WLAN_MEM_SHARED_TX_DSCR_CNT2];
    oal_mempool_tx_dscr_info ast_tx_dscr_info[OAL_TX_DSCR_ITEM_NUM];
    oal_uint16   us_tx_dscr_cnt;
    oal_uint16   us_released_tx_dscr_cnt;   /*指示发送描述符释放统计的位置*/
    oal_uint16   us_tx_dscr_cnt_up;         /*指示上半部描述符统计的位置*/
    oal_uint16   us_tx_dscr_cnt_dn;         /*指示上半部描述符统计的位置*/
    oal_uint16   us_rcd_rls_stop_flag;
    oal_uint16   us_rsv;
}oal_mempool_tx_dscr_addr;
#endif


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_void* oal_mem_alloc(
                       oal_uint32                    ul_file_id,
                       oal_uint32                    ul_line_num,
                       oal_mem_pool_id_enum_uint8    en_pool_id,
                       oal_uint16                    us_len,
                       oal_uint8                     uc_lock);
extern oal_uint32  oal_mem_free(oal_uint32 ul_file_id, oal_uint32 ul_line_num, oal_void *pst_mem, oal_uint8 uc_lock);

extern oal_uint32  oal_mem_free_array(
                oal_uint32    ul_file_id,
                oal_uint32    ul_line_num,
                oal_void     *p_data,
                oal_uint8     uc_mem_num);

extern oal_mem_stru* oal_mem_alloc_enhanced(
                oal_uint32                    ul_file_id,
                oal_uint32                    ul_line_num,
                oal_mem_pool_id_enum_uint8    en_pool_id,
                oal_uint16                    us_len,
                oal_uint8                     uc_lock);
extern oal_uint32  oal_mem_free_enhanced(oal_uint32 ul_file_id, oal_uint32 ul_line_num, oal_mem_stru *p_data, oal_uint8 uc_lock);
extern oal_uint32  oal_mem_init_pool(oal_void);
extern oal_uint32  oal_mem_exit(oal_void);
extern oal_uint32  oal_mem_incr_user(
                       oal_uint32      ul_file_id,
                       oal_uint32      ul_line_num,
                       oal_mem_stru   *pst_mem,
                       oal_uint8       uc_lock);
extern oal_void  oal_mem_info(oal_mem_pool_id_enum_uint8 en_pool_id);
extern oal_void  oal_mem_leak(oal_mem_pool_id_enum_uint8 en_pool_id);

extern oal_void  oal_mem_start_stat(oal_void);
extern oal_uint32  oal_mem_end_stat(oal_void);

extern oal_uint32  oal_mem_trace_enhanced(oal_uint32      ul_file_id,
                                          oal_uint32      ul_line_num,
                                          oal_mem_stru   *pst_mem,
                                          oal_uint8       uc_lock);
extern oal_uint32  oal_mem_trace(oal_uint32    ul_file_id,
                                 oal_uint32    ul_line_num,
                                 oal_void     *p_data,
                                 oal_uint8     uc_lock);

#ifdef _PRE_DEBUG_MODE
extern oal_mempool_tx_dscr_addr* oal_mem_get_tx_dscr_addr(oal_void);
extern oal_void oal_mem_stop_rcd_rls(oal_void);
extern oal_uint16 oal_mem_get_stop_flag(oal_void);
#endif
/* device 侧裸系统和 host侧的函数输出 */
extern oal_mem_pool_stru* oal_mem_get_pool(oal_mem_pool_id_enum_uint8 en_pool_id);

extern oal_mem_pool_cfg_stru* oal_mem_get_pool_cfg_table(oal_mem_pool_id_enum_uint8 en_pool_id);
extern oal_netbuf_stru* oal_mem_sdt_netbuf_alloc(oal_uint16 us_len, oal_uint8 uc_lock);
extern oal_uint32  oal_mem_sdt_netbuf_free(oal_netbuf_stru *pst_netbuf, oal_uint8 uc_lock);
extern oal_netbuf_stru* oal_netbuf_duplicate(oal_netbuf_stru* pst_src_netbuf,
											oal_uint8 uc_out_subpool_id,
											oal_uint32 ul_add_head_room,
											oal_uint32 ul_add_tail_room);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
extern oal_void oal_mem_print_normal_pool_info(oal_mem_pool_id_enum_uint8 en_pool_id);
extern oal_void oal_mem_print_pool_info(oal_void);
extern oal_ulong oal_get_func_return_address(oal_void);
extern oal_void oal_mem_print_funcname(oal_ulong func_addr);
#endif

#define oal_netbuf_duplicate_normal(pst_src_netbuf,ul_add_head_room,ul_add_tail_room) \
                    oal_netbuf_duplicate(pst_src_netbuf,OAL_NORMAL_NETBUF,ul_add_head_room,ul_add_tail_room)

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_mm.h */

