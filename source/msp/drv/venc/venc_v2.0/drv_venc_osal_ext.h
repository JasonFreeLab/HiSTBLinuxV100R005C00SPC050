#ifndef  __DRV_VENC_OSAL_EXT_H__
#define  __DRV_VENC_OSAL_EXT_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if defined(VENC_EXTRA_TYPE_DEFINE)
    #define UINT64 HI_U64
    #define SINT64 HI_S64
    #define UINT32 HI_U32
    #define SINT32 HI_S32
    #define UINT16 HI_U16
    #define SINT16 HI_S16
    #define UINT8  HI_U8
    #define SINT8  HI_S8
    #define VOID   HI_VOID
    #define UADDR  HI_U32
    #define ULONG  HI_SIZE_T
    #define HANDLE HI_HANDLE
    #define VIRT_ADDR   HI_VOID*
    typedef const void CONSTVOID;
#else
    typedef  unsigned long long UINT64;
    typedef  long long          SINT64;
    typedef  unsigned int       UINT32;
    typedef  int                SINT32;
    typedef  unsigned short     UINT16;
    typedef  short              SINT16;
    typedef  char               SINT8;
    typedef  unsigned char      UINT8;
    typedef  unsigned int       UADDR;
    typedef  const void         CONSTVOID;
    typedef  unsigned long      ULONG;
    typedef  unsigned int       HANDLE;
#ifndef  VOID
    typedef  void               VOID;
#endif

#endif

typedef struct
{
    HI_U8* pu8StartVirAddr;    /*VirAddr*/
    HI_U32 u32StartPhyAddr;    /*PhyAddr or SmmuAddr*/
    HI_U32 u32Size;
} VENC_BUFFER_S;

typedef unsigned long   VEDU_LOCK_FLAG;

typedef HI_VOID*  (*FN_OSAL_MemSet)(HI_VOID* s, HI_S32 c, unsigned long n);
typedef HI_VOID* (*FN_OSAL_MemCpy)(HI_VOID* d, HI_VOID* s, unsigned long n);
typedef SINT32   (*FN_OSAL_printk)(const char* fmt, ...);
typedef HI_VOID* (*FN_OSAL_KernelRegisterMap)(unsigned long phyAddr, unsigned long size);
typedef HI_VOID  (*FN_OSAL_KernelRegisterUnMap)(HI_VOID* vir_addr);

typedef VOID     *(*FN_OSAL_AllocVirMem)(SINT32 size);
typedef VOID     (*FN_OSAL_FreeVirMem)(VOID *virMem);

typedef struct Venc_Osal_Func_Ptr_S
{
    FN_OSAL_MemSet   pfun_Osal_MemSet;
    FN_OSAL_MemCpy   pfun_Osal_MemCpy;
    FN_OSAL_printk   pfun_Osal_printk;
    FN_OSAL_KernelRegisterMap   pfun_Osal_ioremap;
    FN_OSAL_KernelRegisterUnMap pfun_Osal_iounmap;

    FN_OSAL_AllocVirMem pfun_Osal_AllocVirMem;
    FN_OSAL_FreeVirMem  pfun_Osal_FreeVirMem;
} Venc_Osal_Func_Ptr;

////////////////////////////////////////////////////////////////////////////// must be delete or modified later!!! by liminqi
HI_VOID       VENC_DRV_OsalIrqFree(HI_U32 Irq);
HI_S32        VENC_DRV_OsalIrqInit(HI_U32 Irq, HI_VOID (*ptrCallBack)(HI_VOID));
HI_S32        VENC_DRV_OsalLockCreate (HI_VOID** phLock);
HI_VOID       VENC_DRV_OsalLockDestroy(HI_VOID* hLock);
HI_VOID       VENC_DRV_OsalLock(HI_VOID* hLock, VEDU_LOCK_FLAG* pFlag);
HI_VOID       VENC_DRV_OsalUnlock(HI_VOID* hLock, VEDU_LOCK_FLAG* pFlag);
HI_S32        VENC_DRV_OsalCreateTask(HI_VOID** phTask, HI_U8 TaskName[], HI_VOID* pTaskFunction);
HI_S32        VENC_DRV_OsalDeleteTask(HI_VOID* hTask);

struct file* VENC_DRV_OsalFopen(const char* filename, int flags, int mode);
void VENC_DRV_OsalFclose(struct file* filp);
int VENC_DRV_OsalFwrite(char* buf, int len, struct file* filp);

#ifdef HI_SMMU_SUPPORT
HI_VOID HI_DRV_VENC_GetSmmuAddr(HI_U32 *pSmmuPageBaseAddr, HI_U32 *pSmmuErrReadAddr, HI_U32 *pSmmuErrWriteAddr);
#endif

HI_S32 HI_DRV_VENC_AllocAndMap(const char *bufname, char *zone_name, HI_U32 size, int align, VENC_BUFFER_S *psMBuf);
HI_VOID HI_DRV_VENC_UnmapAndRelease(VENC_BUFFER_S *psMBuf);

HI_S32 HI_DRV_VENC_MMZ_AllocAndMap(const char *bufname, char *zone_name, HI_U32 size, int align, VENC_BUFFER_S *psMBuf);
HI_VOID HI_DRV_VENC_MMZ_UnmapAndRelease(VENC_BUFFER_S *psMBuf);

HI_S32 HI_DRV_VENC_Map(VENC_BUFFER_S *psMBuf);
HI_VOID HI_DRV_VENC_Unmap(VENC_BUFFER_S *psMBuf);
//////////////////////////////////////////////////////////////////////////////// end

HI_VOID InitVencInterface(HI_VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif //__DRV_VENC_OSAL_EXT_H__

