#ifndef __VFMW_OSAL_EXT_HEADER__
#define __VFMW_OSAL_EXT_HEADER__


#include "mem_manage.h"

typedef SINT32 (*vfmw_irq_handler_t)(SINT32, VOID *);

typedef enum FileOpenMode
{
    VFMW_O_RDONLY = 00000000,
    VFMW_O_WRONLY = 00000001,
    VFMW_O_RDWR   = 00000002,
    VFMW_O_CREATE = 00000100,
    VFMW_O_TRUNC  = 00001000,
    VFMW_O_APPEND = 00002000
} FileOpenMode;

typedef enum SpinLockType
{
    G_TASKLOCK            = 0,
    G_RECORDLOCK          = 1,
    G_SPINLOCK            = 2,
    G_SPINLOCK_FSP        = 3,
    G_SPINLOCKIRQ_DESTROY = 4,
    G_ACTIVATELOCK        = 5,
    G_SPINLOCKISR_MSGQUE  = 6,
    G_SPINLOCKISR_IMAGE2D = 7,
    G_FRAMEBUF            = 8,
} SpinLockType;

typedef enum SemType
{
    G_INIT_DEINIT_SEM     = 0,
    G_RLSSTREAM_SEM       = 1,
    G_SAVEYUV_SEM         = 2,
} SemType;


typedef enum FileType
{
    G_VFMW_SAVE_STR_FILE = 0,
    G_VFMW_SAEV_SEG_FILE = 1,
    G_VFMW_SAVE_YUV_FILE = 2
} FileType;

typedef enum MutexType
{
    G_INTEVENT = 0,
    G_INTWAITQUEUE = 1
} MutexType;

typedef enum RWLockType
{
    G_STATE_RWLOCK = 0
} RWLockType;


typedef  VOID  OSAL_FILE;

typedef UINT32 (*FN_OSAL_GetTimeInMs)(VOID);
typedef UINT32 (*FN_OSAL_GetTimeInUs)(VOID);

typedef VOID   (*FN_OSAL_SpinLockInit)(SpinLockType);
typedef SINT32 (*FN_OSAL_SpinLock)(SpinLockType);
typedef SINT32 (*FN_OSAL_SpinUnlock)(SpinLockType);

typedef VOID   (*FN_OSAL_SemaInit)(SemType semType,int chanID);
typedef SINT32 (*FN_OSAL_SemaDown)(SemType semType,int chanID);
typedef VOID   (*FN_OSAL_SemaUp)(SemType,int chanID);

typedef VOID  *(*FN_OSAL_FileOpen)(const char *fileName, int flags, int mod);
typedef VOID   (*FN_OSAL_FileClose)(OSAL_FILE *);
typedef SINT32 (*FN_OSAL_FileRead)(char *buffer, UINT32 length, OSAL_FILE *pFile);
typedef SINT32 (*FN_OSAL_FileWrite)(char *buffer, UINT32 length, OSAL_FILE *pFile);

typedef VOID  *(*FN_OSAL_MemSet)(VOID *s, SINT32 c, unsigned long n);
typedef VOID  *(*FN_OSAL_MemCpy)(VOID *dest, const VOID *src, unsigned long n);
typedef VOID  *(*FN_OSAL_MemMov)(VOID *dest, const VOID *src, unsigned long n);
typedef SINT32 (*FN_OSAL_MemCmp)(VOID *dest, const VOID *src, unsigned long n);

typedef SINT32 (*FN_OSAL_printk)(const char *fmt, ...);
typedef SINT32 (*FN_OSAL_snprintf)(char *str, unsigned long size, const char *format, ...);
typedef SINT32 (*FN_OSAL_sscanf)(const char *str, const char *format, ...);
typedef SINT32 (*FN_OSAL_strncmp)(const char *s1, const char *s2, UINT32 n);

typedef UINT32 (*FN_OSAL_strlcpy)(char *dest, const char *src, UINT32 size);
typedef UINT32 (*FN_OSAL_strlcpy_command_line)(char *dest, UINT32 size);
typedef SINT8 *(*FN_OSAL_strsep)(char **stringp, const char *delim);
typedef long   (*FN_OSAL_simple_strtol)(const char *cp, char **endp, UINT32 base);
typedef SINT8 *(*FN_OSAL_strstr)(const char *haystack, const char *needle);
typedef UINT32 (*FN_OSAL_strlen)(const char *string);

typedef VOID  *(*FN_OSAL_ioremap)(UADDR  phys_addr, unsigned long size);
typedef VOID   (*FN_OSAL_iounmap)(void *addr);

typedef VOID    (*FN_OSAL_mb)(VOID);

typedef VOID   (*FN_OSAL_udelay)(unsigned long usecs);
typedef VOID   (*FN_OSAL_msleep)(unsigned int msecs);

typedef SINT32 (*FN_OSAL_InitEvent)(MutexType mutexType, SINT32 initVal);
typedef SINT32 (*FN_OSAL_GiveEvent)(MutexType mutexType);
typedef SINT32 (*FN_OSAL_WaitEvent)(MutexType mutexType, SINT32 condition, SINT32 waitTimeInMs);

#if 0
typedef VOID   (*FN_OSAL_RWLockInit)(RWLockType rwLockType);
typedef VOID   (*FN_OSAL_ReadLock)(RWLockType rwLockType);
typedef VOID   (*FN_OSAL_ReadUnLock)(RWLockType rwLockType);
typedef VOID   (*FN_OSAL_WriteLock)(RWLockType rwLockType);
typedef VOID   (*FN_OSAL_WriteUnLock)(RWLockType rwLockType);
#endif

#if 0
typedef SINT32 (*FN_OSAL_MsgQue_InitMsgQue)(VOID);
typedef SINT32 (*FN_OSAL_MsgQue_GetMsg)(MSG_QUEUE_DATA *pMsgData, VOID **pMsgNode);
typedef SINT32 (*FN_OSAL_MsgQue_UpdateReadPtr)(SINT32 retVal, VOID *pMsgNode);
typedef SINT32 (*FN_OSAL_MsgQue_GetNodeNum)(VOID);
typedef SINT32 (*FN_OSAL_MsgQue_Control)(SINT32 chanID, VDEC_CID_E eCmdID, VOID *pArgs);
typedef SINT32 (*FN_OSAL_MsgQue_DeinitMsgQue)(VOID);
#endif

typedef VOID   (*FN_OSAL_FlushCache)(VOID *ptr, UADDR  phy_addr, UINT32 length);
typedef VOID   (*FN_OSAL_KernelFlushCache)(VOID *ptr, UADDR  phy_addr, UINT32 length);

typedef SINT32 (*FN_OSAL_KernelMemAlloc)(UINT8 *memName, UINT32 length, UINT32 align, UINT32 isCached, MEM_DESC_S *pMemDesc);
typedef SINT32 (*FN_OSAL_KernelMemFree)(MEM_DESC_S *pMemDesc);
typedef SINT8 *(*FN_OSAL_KernelRegisterMap)(UADDR  phyAddr);
typedef VOID   (*FN_OSAL_KernelRegisterUnMap)(UINT8 *virAddr);

typedef UINT8 *(*FN_OSAL_KernelMmap)(MEM_RECORD_S *pMemRec);
typedef VOID   (*FN_OSAL_KernelMunMap)(UINT8 *p);

typedef UINT8 *(*FN_OSAL_KernelMmapMMZ)(MEM_RECORD_S *pMemRec);
typedef VOID   (*FN_OSAL_KernelMunMapMMZ)(UINT8 *p);

typedef UINT8 *(*FN_OSAL_KernelMmapCache)(MEM_RECORD_S *pMemRec);

typedef SINT32 (*FN_OSAL_MapSmmuFromMMZ)(UADDR *pSmmuPhyAddr, UADDR MMZPhyAddr, SINT32 Size);
typedef SINT32 (*FN_OSAL_UnMapSmmuOfMMZ)(UADDR SmmuPhyAddr, UADDR MMZPhyAddr);

typedef UINT8 *(*FN_OSAL_KernelNsMmap)(UADDR phy_addr, UINT32 size);
typedef VOID   (*FN_OSAL_KernelNsMunMap)(UINT8 *p);

typedef VOID   (*FN_OSAL_KernelGetPageTableAddr)(UINT32 *pu32ptaddr, UINT32 *pu32err_rdaddr, UINT32 *pu32err_wraddr);

typedef SINT32 (*FN_OSAL_CreateTask)(VOID *pParam, SINT8 *taskName, VOID *pTaskFunc);

typedef SINT32 (*FN_OSAL_request_irq)(UINT32 irq, vfmw_irq_handler_t handler, unsigned long flags, const char *name, void *dev);
typedef VOID   (*FN_OSAL_free_irq)(UINT32 irq, const char *name, void *dev);

typedef VOID  *(*FN_OSAL_phys_to_virt)(UADDR address);

typedef VOID  *(*FN_OSAL_AllocVirMem)(SINT32 size);
typedef VOID   (*FN_OSAL_FreeVirMem)(VOID *virMem);

typedef SINT32 (*FN_OSAL_vfmw_proc_init)(VOID);
typedef VOID   (*FN_OSAL_vfmw_proc_exit)(VOID);

typedef SINT32 (*FN_OSAL_vfmw_proc_create)(UINT8 *proc_name, VOID *fp_read, VOID *fp_write);
typedef VOID   (*FN_OSAL_vfmw_proc_destroy)(UINT8 *proc_name);
typedef SINT32 (*FN_OSAL_Get_Vp9_Support)(UINT32 *pVp9Support);
typedef UINT64 (*FN_OSAL_Do_Div)(UINT64 Dividend, UINT32 Divison);


typedef struct Vfmw_Osal_Func_Ptr
{
    FN_OSAL_GetTimeInMs pfun_Osal_GetTimeInMs;
    FN_OSAL_GetTimeInUs pfun_Osal_GetTimeInUs;

    FN_OSAL_SpinLockInit pfun_Osal_SpinLockInit;
    FN_OSAL_SpinLock     pfun_Osal_SpinLock;
    FN_OSAL_SpinUnlock   pfun_Osal_SpinUnlock;

    FN_OSAL_SemaInit pfun_Osal_SemaInit;
    FN_OSAL_SemaDown pfun_Osal_SemaDown;
    FN_OSAL_SemaUp   pfun_Osal_SemaUp;

    FN_OSAL_FileOpen  pfun_Osal_FileOpen;
    FN_OSAL_FileClose pfun_Osal_FileClose;
    FN_OSAL_FileRead  pfun_Osal_FileRead;
    FN_OSAL_FileWrite pfun_Osal_FileWrite;

    FN_OSAL_MemSet pfun_Osal_MemSet;
    FN_OSAL_MemCpy pfun_Osal_MemCpy;
    FN_OSAL_MemMov pfun_Osal_MemMov;
    FN_OSAL_MemCmp pfun_Osal_MemCmp;

    FN_OSAL_printk pfun_Osal_printk;

    FN_OSAL_snprintf pfun_Osal_snprintf;

    FN_OSAL_sscanf pfun_Osal_sscanf;

    FN_OSAL_strncmp pfun_Osal_strncmp;

    FN_OSAL_strlcpy_command_line pfun_Osal_strlcpy_command_line;

    FN_OSAL_simple_strtol pfun_Osal_simple_strtol;

    FN_OSAL_strlcpy pfun_Osal_strlcpy;
    FN_OSAL_strsep  pfun_Osal_strsep;
    FN_OSAL_strstr  pfun_Osal_strstr;
    FN_OSAL_strlen  pfun_Osal_strlen;

    FN_OSAL_ioremap pfun_Osal_ioremap;
    FN_OSAL_iounmap pfun_Osal_iounmap;

    FN_OSAL_mb     pfun_Osal_mb;

    FN_OSAL_udelay pfun_Osal_udelay;
    FN_OSAL_msleep pfun_Osal_msleep;

    FN_OSAL_InitEvent pfun_Osal_InitEvent;
    FN_OSAL_GiveEvent pfun_Osal_GiveEvent;
    FN_OSAL_WaitEvent pfun_Osal_WaitEvent;

#if 0
    FN_OSAL_RWLockInit  pfun_Osal_RWLockInit;
    FN_OSAL_ReadLock    pfun_Osal_ReadLock;
    FN_OSAL_ReadUnLock  pfun_Osal_ReadUnLock;
    FN_OSAL_WriteLock   pfun_Osal_WriteLock;
    FN_OSAL_WriteUnLock pfun_Osal_WriteUnLock;

    FN_OSAL_MsgQue_InitMsgQue    pfun_Osal_MsgQue_InitMsgQue;
    FN_OSAL_MsgQue_GetMsg        pfun_Osal_MsgQue_GetMsg;
    FN_OSAL_MsgQue_UpdateReadPtr pfun_Osal_MsgQue_UpdateReadPtr;
    FN_OSAL_MsgQue_GetNodeNum    pfun_Osal_MsgQue_GetNodeNum;
    FN_OSAL_MsgQue_Control       Pfun_Osal_MsgQue_Control;
    FN_OSAL_MsgQue_DeinitMsgQue  pfun_Osal_MsgQue_DeinitMsgQue;
#endif

    FN_OSAL_FlushCache       pfun_Osal_FlushCache;
    FN_OSAL_KernelFlushCache pfun_Osal_KernelFlushCache;

    FN_OSAL_KernelMemAlloc pfun_Osal_KernelMemAlloc;
    FN_OSAL_KernelMemFree  pfun_Osal_KernelMemFree;

    FN_OSAL_KernelRegisterMap   pfun_Osal_KernelRegisterMap;
    FN_OSAL_KernelRegisterUnMap pfun_Osal_KernelRegisterUnMap;

    FN_OSAL_KernelMmap   pfun_Osal_KernelMmap;
    FN_OSAL_KernelMunMap pfun_Osal_KernelMunMap;

    FN_OSAL_MapSmmuFromMMZ  pfun_Osal_MapSmmuFromMMZ;
    FN_OSAL_UnMapSmmuOfMMZ  pfun_Osal_UnMapSmmuOfMMZ;

    FN_OSAL_KernelMmapMMZ   pfun_Osal_KernelMmapMMZ;
    FN_OSAL_KernelMunMapMMZ pfun_Osal_KernelMunMapMMZ;

    FN_OSAL_KernelMmapCache pfun_Osal_KernelMmapCache;

    FN_OSAL_KernelNsMmap   pfun_Osal_KernelNsMmap;
    FN_OSAL_KernelNsMunMap pfun_Osal_KernelNsMunMap;

    FN_OSAL_KernelGetPageTableAddr pfun_Osal_KernelGetPageTableAddr;

    FN_OSAL_CreateTask pfun_Osal_CreateTask;

    FN_OSAL_request_irq pfun_Osal_request_irq;
    FN_OSAL_free_irq    pfun_Osal_free_irq;

    FN_OSAL_phys_to_virt pfun_Osal_phys_to_virt;

    FN_OSAL_AllocVirMem pfun_Osal_AllocVirMem;
    FN_OSAL_FreeVirMem  pfun_Osal_FreeVirMem;

    FN_OSAL_vfmw_proc_init    pfun_Osal_vfmw_proc_init;
    FN_OSAL_vfmw_proc_exit    pfun_Osal_vfmw_proc_exit;
    FN_OSAL_vfmw_proc_create  pfun_Osal_vfmw_proc_create;
    FN_OSAL_vfmw_proc_destroy pfun_Osal_vfmw_proc_destroy;

    FN_OSAL_Get_Vp9_Support   pfun_Osal_GetVp9Support;
    FN_OSAL_Do_Div            pfun_Osal_DoDiv;
} Vfmw_Osal_Func_Ptr;


extern Vfmw_Osal_Func_Ptr vfmw_Osal_Func_Ptr_S;

#define OSAL_FP_strstr                        vfmw_Osal_Func_Ptr_S.pfun_Osal_strstr
#define OSAL_FP_ioremap                       vfmw_Osal_Func_Ptr_S.pfun_Osal_ioremap
#define OSAL_FP_iounmap                       vfmw_Osal_Func_Ptr_S.pfun_Osal_iounmap
#define OSAL_FP_mb                            vfmw_Osal_Func_Ptr_S.pfun_Osal_mb
#define OSAL_FP_udelay                        vfmw_Osal_Func_Ptr_S.pfun_Osal_udelay
#define OSAL_FP_msleep                        vfmw_Osal_Func_Ptr_S.pfun_Osal_msleep
#define OSAL_FP_init_event                    vfmw_Osal_Func_Ptr_S.pfun_Osal_InitEvent
#define OSAL_FP_give_event                    vfmw_Osal_Func_Ptr_S.pfun_Osal_GiveEvent
#define OSAL_FP_wait_event                    vfmw_Osal_Func_Ptr_S.pfun_Osal_WaitEvent
#define OSAL_FP_flush_cache                   vfmw_Osal_Func_Ptr_S.pfun_Osal_FlushCache
#define OSAL_FP_kernel_flush_cache            vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelFlushCache
#define OSAL_FP_kernel_mem_alloc              vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelMemAlloc
#define OSAL_FP_kernel_mem_free               vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelMemFree
#define OSAL_FP_kernel_register_map           vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelRegisterMap
#define OSAL_FP_map_smmu_from_mmz             vfmw_Osal_Func_Ptr_S.pfun_Osal_MapSmmuFromMMZ
#define OSAL_FP_unmap_smmu_of_mmz             vfmw_Osal_Func_Ptr_S.pfun_Osal_UnMapSmmuOfMMZ
#define OSAL_FP_kernel_mmap_mmz               vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelMmapMMZ
#define OSAL_FP_kernel_unmap_mmz              vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelMunMapMMZ
#define OSAL_FP_kernel_mmap_cache             vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelMmapCache
#define OSAL_FP_kernel_ns_map                 vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelNsMmap
#define OSAL_FP_kernel_ns_unmap               vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelNsMunMap
#define OSAL_FP_kernel_get_page_table_addr    vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelGetPageTableAddr
#define OSAL_FP_create_task                   vfmw_Osal_Func_Ptr_S.pfun_Osal_CreateTask
#define OSAL_FP_request_irq                   vfmw_Osal_Func_Ptr_S.pfun_Osal_request_irq
#define OSAL_FP_alloc_virmem                  vfmw_Osal_Func_Ptr_S.pfun_Osal_AllocVirMem
#define OSAL_FP_free_virmem                   vfmw_Osal_Func_Ptr_S.pfun_Osal_FreeVirMem
#define OSAL_FP_free_irq                      vfmw_Osal_Func_Ptr_S.pfun_Osal_free_irq
#define OSAL_FP_phys_to_virt                  vfmw_Osal_Func_Ptr_S.pfun_Osal_phys_to_virt
#define OSAL_FP_get_time_ms                   vfmw_Osal_Func_Ptr_S.pfun_Osal_GetTimeInMs
#define OSAL_FP_get_time_us                   vfmw_Osal_Func_Ptr_S.pfun_Osal_GetTimeInUs
#define OSAL_FP_spin_lock_init                vfmw_Osal_Func_Ptr_S.pfun_Osal_SpinLockInit
#define OSAL_FP_spin_lock                     vfmw_Osal_Func_Ptr_S.pfun_Osal_SpinLock
#define OSAL_FP_spin_unlock                   vfmw_Osal_Func_Ptr_S.pfun_Osal_SpinUnlock
#define OSAL_FP_sema_init                     vfmw_Osal_Func_Ptr_S.pfun_Osal_SemaInit
#define OSAL_FP_sema_down                     vfmw_Osal_Func_Ptr_S.pfun_Osal_SemaDown
#define OSAL_FP_sema_up                       vfmw_Osal_Func_Ptr_S.pfun_Osal_SemaUp
#define OSAL_FP_memmov                        vfmw_Osal_Func_Ptr_S.pfun_Osal_MemMov
#define OSAL_FP_memcmp                        vfmw_Osal_Func_Ptr_S.pfun_Osal_MemCmp
#define OSAL_FP_strlcpy_command_line          vfmw_Osal_Func_Ptr_S.pfun_Osal_strlcpy_command_line
#define OSAL_FP_simple_strtol                 vfmw_Osal_Func_Ptr_S.pfun_Osal_simple_strtol
#define OSAL_FP_strlcpy                       vfmw_Osal_Func_Ptr_S.pfun_Osal_strlcpy
#define OSAL_FP_strsep                        vfmw_Osal_Func_Ptr_S.pfun_Osal_strsep
#define OSAL_FP_print                         vfmw_Osal_Func_Ptr_S.pfun_Osal_printk
#define OSAL_FP_memcpy                        vfmw_Osal_Func_Ptr_S.pfun_Osal_MemCpy
#define OSAL_FP_memset                        vfmw_Osal_Func_Ptr_S.pfun_Osal_MemSet
#define OSAL_FP_strlen                        vfmw_Osal_Func_Ptr_S.pfun_Osal_strlen
#define OSAL_FP_strncmp                       vfmw_Osal_Func_Ptr_S.pfun_Osal_strncmp
#define OSAL_FP_snprintf                      vfmw_Osal_Func_Ptr_S.pfun_Osal_snprintf
#define OSAL_FP_fopen                         vfmw_Osal_Func_Ptr_S.pfun_Osal_FileOpen
#define OSAL_FP_fclose                        vfmw_Osal_Func_Ptr_S.pfun_Osal_FileClose
#define OSAL_FP_fread                         vfmw_Osal_Func_Ptr_S.pfun_Osal_FileRead
#define OSAL_FP_fwrite                        vfmw_Osal_Func_Ptr_S.pfun_Osal_FileWrite
#define OSAL_FP_proc_init                     vfmw_Osal_Func_Ptr_S.pfun_Osal_vfmw_proc_init
#define OSAL_FP_proc_exit                     vfmw_Osal_Func_Ptr_S.pfun_Osal_vfmw_proc_exit
#define OSAL_FP_proc_create                   vfmw_Osal_Func_Ptr_S.pfun_Osal_vfmw_proc_create
#define OSAL_FP_proc_destroy                  vfmw_Osal_Func_Ptr_S.pfun_Osal_vfmw_proc_destroy
#define OSAL_FP_ssanf                         vfmw_Osal_Func_Ptr_S.pfun_Osal_sscanf
#define OSAL_FP_mmap                          vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelMmap
#define OSAL_FP_unmap                         vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelMunMap
#define OSAL_FP_do_div                        vfmw_Osal_Func_Ptr_S.pfun_Osal_DoDiv


VOID OSAL_InitVfmwInterface(VOID);

#endif
