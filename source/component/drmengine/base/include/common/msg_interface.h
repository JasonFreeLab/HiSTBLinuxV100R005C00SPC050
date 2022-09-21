#ifndef __VTOP_MSG_INTERFACE_DEFS_H__
#define __VTOP_MSG_INTERFACE_DEFS_H__

#ifdef    __cplusplus
extern "C"{
#endif

#include "hi_type.h"
#include <sys/types.h>

/* 每条消息体的最大尺寸 */
#define VTOP_MSG_MAX_MSG_SIZE    4096

#define VTOP_MSG_MAX_NAME_LEN    16
#define VTOP_MSG_MAX_TASK_NAME_LEN    VTOP_MSG_MAX_NAME_LEN

typedef char VTOP_MSG_TASKNAME[VTOP_MSG_MAX_TASK_NAME_LEN];

/* ID & 句柄定义: 从0开始，-1无效 */
typedef int VTOP_TASK_ID;
#define VTOP_INVALID_TASK_ID        (-1)

/* msg id: 从0开始，假设计数不会满，0xffffffffffffffff为无效 */
typedef unsigned int  VTOP_MSG_ID;

/* 用户自定义消息类型: 0x00000000 ~ 0x7FFFFFFF    */
/* 系统保留消息类型:   0x80000000 ~ 0xFFFFFFFE    */
typedef unsigned int VTOP_MSG_TYPE;
#define VTOP_INVALID_MSG_TYPE    (0xFFFFFFFF)
#define VTOP_MSG_TYPE_SYS(msgType)    (msgType | 0x80000000)
#define VTOP_MSG_TYPE_USER(msgType)    (msgType & 0x7fffffff)

/* ============== 消息优先级 ============== */
typedef enum
{
    VTOP_MSG_PRIO_LOW     = 0,
    VTOP_MSG_PRIO_MID   = 1,
    VTOP_MSG_PRIO_HIGH     = 2,

    VTOP_MSG_PRIO_BUTT
}VTOP_MSG_E_Prio;

#define VTOP_MSG_PRIO_DEFAULT VTOP_MSG_PRIO_MID

/* ============== 消息缓冲块别级 ============== */
typedef enum
{
    VTOP_MSG_BL_0     = 0,        /*256  Bytes*/
    VTOP_MSG_BL_1   = 1,        /*512  Bytes*/
    VTOP_MSG_BL_2     = 2,        /*1024 Bytes*/
    VTOP_MSG_BL_3   = 3,        /*4096 Bytes*/
    VTOP_MSG_BL_BUTT
}VTOP_MSG_E_BufferLevel;

typedef size_t VTOP_MSG_BLOCKNUM[VTOP_MSG_BL_BUTT];

/* ============== 消息 FLAG ============== */
#define VTOP_MSG_FLG_SYNC          0x00000001  /* 同步标志位 */
#define VTOP_MSG_FLG_ASYNC         0x00000002  /* 异步标志位 */
#define VTOP_MSG_FLG_ACK        0x00000008  /* 应答标志位 */
#define VTOP_MSG_FLG_RESP       0x00000010  /* 同步消息响应标志 */

#define VTOP_MSG_FLG_P2P          0x00000100  /* 点对点消息 */
#define VTOP_MSG_FLG_SP         0x00000200  /* 订阅消息 */
/* 0x00001000 ~ 0x00008000 reserved for system */

#define VTOP_MSG_isSyncMsg(flag)    ((flag) & VTOP_MSG_FLG_SYNC)
#define VTOP_MSG_isASyncMsg(flag)   ((flag) & VTOP_MSG_FLG_ASYNC)
#define VTOP_MSG_isRespMsg(flag)    ((flag) & VTOP_MSG_FLG_RESP)

#define VTOP_MSG_isP2PMsg(flag)     ((flag) & VTOP_MSG_FLG_P2P)
#define VTOP_MSG_isSPMsg(flag)      ((flag) & VTOP_MSG_FLG_SP)

/* ============== 错误码定义 ============== */

/******************************************************************************
|----------------------------------------------------------------|
| 1 |   APP_ID   |   MOD_ID    | ERR_LEVEL |   ERR_ID            |
|----------------------------------------------------------------|
|<--><--7bits----><----8bits---><--3bits---><------13bits------->|
******************************************************************************/

//#define SCP_APPID  (0x80L | 0x22L)    /* 34=0x22, including errid flag "1"=0x80UL */
//#define SCP_MSG_MODID    0x01L
#define SCP_APP_MOD_ID    (0xA2010000)    /* =(SCP_APPID | SCP_MSG_MODID) */

/* 定义8个等级*/
typedef enum
{
    VTOP_LOG_LEVEL_DEBUG = 0,  /* debug-level                                  */
    VTOP_LOG_LEVEL_INFO,       /* informational                                */
    VTOP_LOG_LEVEL_NOTICE,     /* normal but significant condition             */
    VTOP_LOG_LEVEL_WARNING,    /* warning conditions                           */
    VTOP_LOG_LEVEL_ERROR,      /* error conditions                             */
    VTOP_LOG_LEVEL_CRIT,       /* critical conditions                          */
    VTOP_LOG_LEVEL_ALERT,      /* action must be taken immediately             */
    VTOP_LOG_LEVEL_FATAL,      /* just for compatibility with previous version */

    VTOP_LOG_LEVEL_BUTT
} VTOP_LOG_ERRLEVEL_E;

#if 0
#define SCP_DEF_ERR(level, errid) \
    ( SCP_APP_MOD_ID | ((level)<<13) | (errid) )
#endif

#define SCP_DEF_ERR(level, errid) \
    ((int)SCP_APP_MOD_ID|((((int)(level))&0x00000007)<<13)|(((int)(errid))&0x00001FFF))

typedef enum
{
    VTOP_MSG_ERRID_GENERAL=0x000,        /* 通用错误                     */
    VTOP_MSG_ERRID_UNKNOWN,                /* 未知错误                     */
    VTOP_MSG_ERRID_NOMEM,                /* 申请内存失败                 */
    VTOP_MSG_ERRID_NULLPTR,                /* 空指针                         */
    VTOP_MSG_ERRID_INVALIDPARA,            /* 无效参数(空指针除外)         */
    VTOP_MSG_ERRID_VERSION,             /* 版本与服务进程不匹配         */

    VTOP_MSG_ERRID_NOSHMMEM=0x100,        /* 申请共享内存失败             */
    VTOP_MSG_ERRID_SHMEXIST,            /* 申请共享内存已经存在         */
    VTOP_MSG_ERRID_SHMNOTEXIST,            /* 申请共享内存不存在             */
    VTOP_MSG_ERRID_SHMATTACH,            /* 挂接共享内存不存在             */
    VTOP_MSG_ERRID_SEMINIT,                /* 初始化信号量失败                */
    VTOP_MSG_ERRID_SEMGET,                /* 获取信号量失败                */
    VTOP_MSG_ERRID_SEMDESTROY,            /* 销毁信号量失败                */
    VTOP_MSG_ERRID_SEMLOCK,                /* 加锁信号量失败                */
    VTOP_MSG_ERRID_SEMUNLOCK,            /* 解锁信号量失败                */

    VTOP_MSG_ERRID_DSEXIST=0x200,        /* 线程数据已经存在             */
    VTOP_MSG_ERRID_DSNOTEXIST,            /* 线程数据不存在                 */
    VTOP_MSG_ERRID_DSSMALLMEM,            /* 用户给定的内存大小             */

    VTOP_MSG_ERRID_PROCEXIST=0x300,        /* 消息服务程序已经运行         */
    VTOP_MSG_ERRID_PROCNOTEXIST,        /* 消息服务程序不存在             */
    VTOP_MSG_ERRID_PROCMSGBUFFULL,        /* 消息服务程序消息接收缓冲已满    */
    VTOP_MSG_ERRID_PROCSTART,           /* 消息服务程序启动失败    */

    VTOP_MSG_ERRID_TASKEXIST=0x400,        /* 消息任务已经存在             */
    VTOP_MSG_ERRID_TASKNOTEXIST,        /* 消息任务不存在                 */
    VTOP_MSG_ERRID_TASKFULL,            /* 达到消息任务数最大值         */

    VTOP_MSG_ERRID_SUBEXIST=0x600,        /* 订阅表已经存在                 */
    VTOP_MSG_ERRID_SUBNOTEXIST,            /* 订阅表不存在                 */
    VTOP_MSG_ERRID_SUBFULL,                /* 达到订阅表数最大值             */
    VTOP_MSG_ERRID_SUBMEMBERFULL,        /* 订阅表中成员已满                */
    VTOP_MSG_ERRID_NOTSUBMEMBER,        /* 非订阅者                      */

    VTOP_MSG_ERRID_MSGBUFFULL=0x700,    /* 对方消息接收缓冲已满         */
    VTOP_MSG_ERRID_TIMEOUT,                /* 发送超时                     */
    VTOP_MSG_ERRID_RESPTIMEOUT,         /* 接收响应消息超时             */
    VTOP_MSG_ERRID_MSGRCV,                /* 消息接收失败                    */
    VTOP_MSG_ERRID_MSGSND,                /* 消息发送失败                    */
    VTOP_MSG_ERRID_MSGSIZE,             /* 消息大小非法，可能超过最大限制*/
    VTOP_MSG_ERRID_CLOSECONN,           /* 关闭连接，正常错误*/

    VTOP_MSG_ERRID_BUTT
}VTOP_MSG_E_ERRID;

// 0xA8018000
#define VTOP_MSG_ERR_GENERAL         SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_GENERAL)
#define VTOP_MSG_ERR_UNKNOWN         SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_UNKNOWN)
#define VTOP_MSG_ERR_NOMEM            SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_NOMEM)
#define VTOP_MSG_ERR_NULLPTR        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_NULLPTR)
#define VTOP_MSG_ERR_INVALIDPARA    SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_INVALIDPARA)
#define VTOP_MSG_ERR_VERSION        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_VERSION)

// 0xA8018100
#define VTOP_MSG_ERR_NOSHMMEM        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_NOSHMMEM)
#define VTOP_MSG_ERR_SHMEXIST        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_SHMEXIST)
#define VTOP_MSG_ERR_SHMNOTEXIST    SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_SHMNOTEXIST)
#define VTOP_MSG_ERR_SHMATTCH        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_SHMATTACH)
#define VTOP_MSG_ERR_SEMINIT        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_SEMINIT)
#define VTOP_MSG_ERR_SEMGET            SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_SEMGET)
#define VTOP_MSG_ERR_SEMDESTROY        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_SEMDESTROY)
#define VTOP_MSG_ERR_SEMLOCK        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_SEMLOCK)
#define VTOP_MSG_ERR_SEMUNLOCK        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_SEMUNLOCK)

// 0xA8018200
#define VTOP_MSG_ERR_DSEXIST        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_DSEXIST)
#define VTOP_MSG_ERR_DSNOTEXIST        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_DSNOTEXIST)
#define VTOP_MSG_ERR_DSSMALLMEM        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_DSSMALLMEM)

// 0xA8018300
#define VTOP_MSG_ERR_PROCEXIST        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_PROCEXIST)
#define VTOP_MSG_ERR_PROCNOTEXIST    SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_PROCNOTEXIST)
#define VTOP_MSG_ERR_PROCMSGBUFFULL    SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_PROCMSGBUFFULL)
#define VTOP_MSG_ERR_PROCSTART      SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_PROCSTART)

// 0xA8018400
#define VTOP_MSG_ERR_TASKEXIST        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_TASKEXIST)
#define VTOP_MSG_ERR_TASKNOTEXIST    SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_TASKNOTEXIST)
#define VTOP_MSG_ERR_TASKFULL        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_TASKFULL)

// 0xA8018600
#define VTOP_MSG_ERR_SUBEXIST        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_SUBEXIST)
#define VTOP_MSG_ERR_SUBNOTEXIST    SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_SUBNOTEXIST)
#define VTOP_MSG_ERR_SUBFULL        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_SUBFULL)
#define VTOP_MSG_ERR_SUBMEMBERFULL    SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_SUBMEMBERFULL)
#define VTOP_MSG_ERR_NOTSUBMEMBER    SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_NOTSUBMEMBER)

// 0xA8018700
#define VTOP_MSG_ERR_MSGBUFFULL        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_MSGBUFFULL)
#define VTOP_MSG_ERR_TIMEOUT        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_TIMEOUT)
#define VTOP_MSG_ERR_RESPTIMEOUT    SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_RESPTIMEOUT)
#define VTOP_MSG_ERR_MSGRCV            SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_MSGRCV)
#define VTOP_MSG_ERR_MSGSND            SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_MSGSND)
#define VTOP_MSG_ERR_MSGSIZE        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_MSGSIZE)
#define VTOP_MSG_ERR_CLOSECONN        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_CLOSECONN)

/* ============== 消息结构 ============== */
typedef struct
{
    VTOP_TASK_ID    sndTaskId;    // 消息发送者ID
    VTOP_TASK_ID    rcvTaskId;    // 消息发送者ID
    VTOP_MSG_TYPE   msgType;    // 消息发送者设置
    VTOP_MSG_ID        msgID;        // 系统设置，用户只读

    unsigned int     ulPrio;        // VTOP_MSG_E_Prio类型, 消息优先级，消息发送者设置。P2P同步消息发送无效.
    unsigned int     ulFlag;        // 由系统设置，用户只读。详见"msg flags"
    unsigned int     ulMsgLen;    // 消息内容长度
    unsigned char   *pMsgBody;    // 消息内容
}VTOP_MSG_S_Block;

/* ============== 消息服务程序属性配置 ============== */
typedef struct
{
    unsigned int  ulMaxTask;         /* 消息进程或者线程最大值：0为默认值      */
    unsigned int  ulMaxSub;          /* 消息订阅表的最大个数：0为默认值      */
    unsigned int  ulMaxMem;             /* 消息系统可用的最大内存：0为默认值      */
    VTOP_MSG_BLOCKNUM blockNum;     /* 消息系统缓冲块个数配置: 全0为默认值   */
}VTOP_MSG_S_Config;

/* ============== 消息服务程序方法配置 ============== */
typedef void (*PFUNC_VTOP_MSG_Log)(
        const char *file,             /* 出错的文件名（短文件名、不含路径）    */
        const char *function,        /* 出错的函数                            */
        int line,                /* 出错的位置，即错误处在文件中的行数    */
        int err,                /* 错误码                                */
        VTOP_LOG_ERRLEVEL_E err_level,    /* 错误的级别                            */
        const char *perr);            /* 错误信息：本错误的字符串解释。        */

typedef struct
{
    /* msg module log function, implement by user */
    PFUNC_VTOP_MSG_Log pMsgLog;/*del '*' by qushen*/

    // 其他的适配接口可再添加
}VTOP_MSG_S_ops;

/* ============== 消息任务消息处理函数 ============== */
typedef void (*PFUNC_VTOP_MSG_Handler)(VTOP_MSG_S_Block *pMsg);

/* ============== 消息任务列表 ============== */
typedef struct tag_VTOP_MSG_S_TaskListNode
{
    VTOP_TASK_ID taskId;
    struct tag_VTOP_MSG_S_TaskListNode * pNext;
}VTOP_MSG_S_TaskListNode;

/* ============== 订阅列表 ============== */
typedef struct tag_VTOP_MSG_S_SubListNode
{
    VTOP_MSG_TYPE msgType;
    struct tag_VTOP_MSG_S_SubListNode * pNext;
}VTOP_MSG_S_SubListNode;

/* 使用消息系统之前，必须启动消息服务进程 */
int VTOP_MSG_Main(VTOP_MSG_S_Config * pMsgConfig, VTOP_MSG_S_ops * pMsg_ops);

/* 消息服务进程异常退出后，清理消息系统所用的系统资源，如共享内存，系统消息队列等 */
int VTOP_MSG_Destroy(HI_BOOL bExitByForce);

/* 初始化消息模块 */
int  VTOP_MSG_Register(
        const VTOP_MSG_TASKNAME taskName,
        PFUNC_VTOP_MSG_Handler pMsgHandler,
        PFUNC_VTOP_MSG_Log  pTaskLog,
        VTOP_TASK_ID * pTaskId);

/* 消息合并接口，指定消息类型后收取消息队列中所有类型的消息, qushen, 2009-04-24 */
int VTOP_MSG_SetMerge(VTOP_TASK_ID taskId, VTOP_MSG_TYPE msgtype);

/*  去初始化消息模块  */
int VTOP_MSG_UnRegister(VTOP_TASK_ID taskId);

VTOP_TASK_ID VTOP_MSG_GetTaskId(const VTOP_MSG_TASKNAME taskName);
int VTOP_MSG_GetTaskName(VTOP_TASK_ID taskId, VTOP_MSG_TASKNAME taskName);

/*同消息发送超时参数一致，timeout为零表示非阻塞，非零表示阻塞(>0,阻塞超时时间ms，-1为一直阻塞)*/
int VTOP_MSG_GetAndDispatch(
        VTOP_TASK_ID taskId,
        int timeout);

/*---------------------- 消息模式1: P2P: Point to Point ----------------------------*/
/* 同步消息发送 */
int VTOP_MSG_SynSend(
        VTOP_MSG_S_Block *pMsg,
        VTOP_MSG_S_Block** ppMsgResp,
        int timeout);

/* 同步消息接收者在收到消息并进行相应处理之后，应该调用本接口向发送者发送一个回应消息*/
int VTOP_MSG_SendResp(
                VTOP_MSG_S_Block* pMsg,
                VTOP_MSG_S_Block *pMsgResp );

/* 同步消息发送者在收到回应消息之后，应该调用本接口释放回应消息的内容 */
int VTOP_MSG_SynRespFree(VTOP_MSG_S_Block * pMsgResp);

/* 异步消息发送 */
int VTOP_MSG_AsynSend(VTOP_MSG_S_Block *pMsg);

/* 用户主动收取消息接口 */
int VTOP_MSG_Recv(VTOP_TASK_ID taskId, VTOP_MSG_S_Block **ppMsg, int timeout);

/* 收取消息完毕释放接口 */
int VTOP_MSG_RecvFree(VTOP_MSG_S_Block *pMsg);

/*---------------------- 消息模式2: Pub/Sub: Publish/Subscribe ----------------------------*/
// 订阅某个类型的消息
int VTOP_MSG_Subscribe(VTOP_TASK_ID taskId, VTOP_MSG_TYPE msgType);

// 取消某个类型的消息订阅
int VTOP_MSG_UnSubscribe(VTOP_TASK_ID taskId, VTOP_MSG_TYPE msgType);

// 发布某个类型的消息,消息类型在pMsg->ulMsgType中给出
int VTOP_MSG_Publish(VTOP_MSG_S_Block *pMsg);

// 所有的subscriber(订阅者)通过 VTOP_MSG_Get 接收publisher发布的消息.

char* VTOP_MSG_GetVersion(void);

/* 测试接口 */
void VTOP_MSG_Show(VTOP_MSG_S_Block * pMsg, const char * file, const char * func, int line);

#define THIS_FILE ((strrchr(__FILE__, '/') ?: __FILE__ - 1) + 1)
#define VTOP_MSG_SHOW(pMsg)    VTOP_MSG_Show(pMsg, THIS_FILE, __FUNCTION__, __LINE__)

#ifdef    __cplusplus
}
#endif

#endif /*  __VTOP_MSG_INTERFACE_DEFS_H__  */
