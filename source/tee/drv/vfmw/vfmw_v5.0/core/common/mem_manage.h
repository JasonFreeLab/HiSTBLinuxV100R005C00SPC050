#ifndef _VFMW_MEM_MANAGE_HEAD_
#define _VFMW_MEM_MANAGE_HEAD_

#ifdef __cplusplus
extern "C" {
#endif

#include "vfmw.h"

#define MEM_MAN_ERR  -1
#define MEM_MAN_OK    0

typedef struct
{
    UINT8      IsCached;
    UINT8      *VirAddr;
    UADDR      PhyAddr;
    UADDR      MmuAddr;
    UINT32     Length;
    MEM_MODE_E eMode;
} MEM_RECORD_S;

typedef struct
{
    UADDR MemBaseAddr;
    SINT32 MemSize;
} MEM_INIT_S;


VOID   MEM_InitMemManager(MEM_INIT_S *pMemInit);
VOID   MEM_ManagerWithOperation(VDEC_OPERATION_S *pArgs);
VOID   MEM_ManagerClearOperation(VOID);
SINT32 MEM_AddMemRecord(UADDR PhyAddr, VOID* VirAddr, UINT32 Length);
SINT32 MEM_DelMemRecord(UADDR PhyAddr, VOID* VirAddr, UINT32 Length);
VOID  *MEM_Phy2Vir(UADDR PhyAddr);
UADDR  MEM_Vir2Phy(UINT8 *VirAddr);
VOID   MEM_WritePhyWord(UADDR PhyAddr, UINT32 Data32);
UINT32 MEM_ReadPhyWord(UADDR PhyAddr);
SINT32 MEM_AllocMemBlock(SINT8 *MemName, UADDR ExpectedPhyAddr, UINT32 ExpectedLen, MEM_RECORD_S *pMemRecord, SINT32 IsCached);
SINT32 MEM_MapRegisterAddr(UADDR RegStartPhyAddr, UINT32 RegByteLen, MEM_RECORD_S *pMemRecord);
VOID   MEM_UnmapRegisterAddr(UADDR PhyAddr, UINT8 *VirAddr);
VOID   MEM_ReleaseMemBlock(UADDR PhyAddr, UINT8 *VirAddr);
#ifdef ENV_SOS_KERNEL
VOID   MEM_NsMapToSec(UADDR PhyAddr, UINT8 **VirAddr,UINT32 Length);
VOID   MEM_NsInSecUnMap(UINT8* VirAddr);
#endif

#ifdef __cplusplus
}
#endif

#endif /* end of '#ifndef _VFMW_MEM_MANAGE_HEAD_' */

