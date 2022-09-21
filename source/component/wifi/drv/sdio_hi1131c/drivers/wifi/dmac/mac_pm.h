/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : mac_pm.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2014年8月18日
  最近修改   :
  功能描述   : mac_pm.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年8月18日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __MAC_PM_H__
#define __MAC_PM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if defined(_PRE_WLAN_FEATURE_PM) || defined(_PRE_WLAN_FEATURE_STA_PM)
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_MAC_PM_H
/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define MAC_FSM_MAX_NAME    32  /*状态机名最大长度*/
#define MAC_FSM_MAX_STATES 100
#define MAC_FSM_MAX_EVENTS 100
#define MAC_FSM_STATE_NONE 255 /* invalid state */
#define MAC_FSM_EVENT_NONE 255 /* invalid event */

#define MAC_PM_ARBITER_MAX_REQUESTORS   16      /*最大参与仲裁者数目*/
#define MAC_PM_ARBITER_MAX_REQ_NAME     16      /*请求仲裁者名字最大长度*/
#define MAC_PWR_ARBITER_ID_INVALID      255     /* invalid arbiter id */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
typedef enum {
    MAC_PWR_ARBITER_TYPE_INVALID = 0,  /*非法类型*/
    MAC_PWR_ARBITER_TYPE_AP,           /*AP类型*/
    MAC_PWR_ARBITER_TYPE_STA,          /*STA类型*/
    MAC_PWR_ARBITER_TYPE_P2P,          /*P2P类型*/

    MAC_PWR_ARBITER_TYPE_BUTT
} mac_pm_arbiter_type_enum;

/*device的状态枚举，VAP的节能状态到device的节能状态要做映射，做到AP类型vap，sta类型VAP
P2P类型vap的状态机可自行定义，最后通过仲裁归一到device的状态*/
typedef enum {
    DEV_PWR_STATE_WORK = 0,         /*工作状态*/
    DEV_PWR_STATE_DEEP_SLEEP,      /*深睡状态*/
    DEV_PWR_STATE_WOW,             /*WOW状态*/
    DEV_PWR_STATE_IDLE,            /*idle状态，无用户关联*/
    DEV_PWR_STATE_OFF,             /*下电状态*/

    DEV_PWR_STATE_BUTT             /*最大状态*/
} device_pwr_state_enum;

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
typedef struct _mac_pwr_event_info{
    oal_uint32           ul_event_id;           /*event枚举值,每状态机自己定义*/
    const oal_int8      *auc_event_name;         /*event命名*/
}mac_pwr_event_info;

/*状态信息结构定义*/
typedef struct __mac_fsm_state_info{
    oal_uint32          state;                   /*状态ID*/
    const oal_int8      *name;                   /*状态名*/
    oal_void (*mac_fsm_entry)(oal_void *p_ctx);  /*进入本状态的处理回调函数指针*/
    oal_void (*mac_fsm_exit)(oal_void *p_ctx);   /*退出本状态的处理回调函数指针*/
                                                 /*本状态下的事件处理回调函数指针*/
    oal_uint32 (*mac_fsm_event)(oal_void *p_ctx,oal_uint16 event,oal_uint16 event_data_len,oal_void *event_data);
} mac_fsm_state_info;

/*状态机结构定义*/
typedef struct  __mac_fsm {
    oal_uint8  uc_name[MAC_FSM_MAX_NAME];              /*状态机名字 */
    oal_uint8  uc_cur_state;                           /*当前状态*/
    oal_uint8  uc_prev_state;                          /*前一状态，发出状态切换事件的状态 */
    oal_uint8  uc_num_states;                          /*状态机的状态个数*/
    oal_uint8  uc_rsv[1];
    const mac_fsm_state_info *p_state_info;
    oal_void   *p_ctx;                                 /*上下文，指向状态机实例拥有者，mac_pm_handler_stru* */
    oal_void   *p_oshandler;                           /*owner指针，指向VAP或者device,由具体的状态机决定*/
    oal_uint16  us_last_event;                          /*最后处理的事件*/
    oal_uint8  uc_rsv1[2];
} mac_fsm_stru;

struct mac_pm_arbiter_requestor_info {
    oal_uint8                   auc_id_name[MAC_PM_ARBITER_MAX_REQ_NAME]; /* names of the requestors */
    mac_pm_arbiter_type_enum    en_arbiter_type;
} ;

typedef struct _mac_pm_arbiter_state_info{
    oal_uint32               ul_state;               /*state枚举值,每状态机自己定义*/
    const oal_int8          *auc_state_name;         /*state命名*/
}mac_pm_arbiter_state_info;

typedef struct _mac_pm_arbiter_info {
    oal_uint32   ul_id_bitmap;                          /*分配的requestor id bitmaps */
    oal_uint32   ul_state_bitmap[DEV_PWR_STATE_BUTT];   /*每个状态对应一个bitmap*/
    oal_uint8    uc_cur_state;                          /*当前device的低功耗状态*/
    oal_uint8    uc_prev_state;                         /*前一device的低功耗状态*/
    oal_uint8    uc_requestor_num;                      /*当前请求仲裁者的数目*/
    oal_uint8    uc_rsv;
    mac_pm_arbiter_state_info   *pst_state_info;
    struct mac_pm_arbiter_requestor_info requestor[MAC_PM_ARBITER_MAX_REQUESTORS];  /*投票者的信息，维测用*/
}mac_pm_arbiter_stru;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern mac_fsm_stru*  mac_fsm_create(oal_void*                 p_oshandle,         /*状态机owner的指针，对低功耗状态机，指向VAP结构*/
                                const oal_uint8          *p_name,             /*状态机的名字*/
                                oal_void                 *p_ctx,              /*状态机context*/
                                oal_uint8                 uc_init_state,      /*初始状态*/
                                const mac_fsm_state_info *p_state_info,       /*状态机实例指针*/
                                oal_uint8                 uc_num_states      /*本状态机的状态个数*/
);

extern oal_void mac_fsm_destroy(mac_fsm_stru* p_fsm);
extern oal_uint32 mac_fsm_trans_to_state(mac_fsm_stru* p_fsm,oal_uint8 uc_state);

extern oal_uint32 mac_fsm_event_dispatch(mac_fsm_stru* p_fsm ,oal_uint16 us_event,
                           oal_uint16 us_event_data_len, oal_void *p_event_data);

extern oal_uint32 mac_fsm_event_dispatch(mac_fsm_stru* p_fsm ,oal_uint16 us_event,
                           oal_uint16 us_event_data_len, oal_void *p_event_data);

extern oal_uint32 mac_pm_arbiter_init(mac_device_stru* pst_device);
extern oal_uint32 mac_pm_arbiter_destroy(mac_device_stru* pst_device);
extern oal_uint32 mac_pm_arbiter_alloc_id(mac_device_stru* pst_device, oal_uint8* pst_name,mac_pm_arbiter_type_enum en_arbiter_type);
extern oal_uint32 mac_pm_arbiter_free_id(mac_device_stru* pst_device, oal_uint32 ul_arbiter_id);
extern oal_void mac_pm_arbiter_to_state(mac_device_stru *pst_device, oal_uint32 ul_arbiter_id,
                                            oal_uint8  uc_state_from, oal_uint8  uc_state_to);
extern oal_uint32 mac_pm_set_hal_state(mac_device_stru *pst_device,oal_uint8 uc_state_to);


#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hmac_fsm.h */
