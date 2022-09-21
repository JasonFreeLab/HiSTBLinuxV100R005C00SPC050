#include "vfmw_sos_kernel_osal.h"
#include "vfmw_ctrl.h"
#include "vfmw_tee_client.h"
#include "vfmw_osal_ext.h"
#include "ctrl_case.h"
#define PRINT_TEE_VFMW_TIME  (1)

extern Vfmw_Osal_Func_Ptr vfmw_Osal_Func_Ptr_S;
extern const VDEC_CID_NODE VDEC_CID_HandlerTable[];

/* SECURE MARK */
MEMORY_NEEDED_SECVFMW_S *g_pVfmSharewMem  = NULL;
VDEC_CHAN_OPTION_S *g_pChanOption = NULL; //store chan option
RAW_ARRAY_NS *g_pStreamList = NULL; //manage stream buffer
CALLBACK_ARRAY_NS *g_pCallBackList = NULL;//manage callback buffer
VDEC_CHAN_STATE_S  *g_pChanState = NULL; //store chan state
IMAGE_QUEUE_NS     *g_pImageList = NULL; //store image info
UINT8              *g_pProcBuf     = NULL;

/************************************************************************
    TEE 通信封装接口
*************************************************************************/
SINT32 SEC_VFMW_Init(UINT32 pArgs)
{
    SINT32 ret = VDEC_ERR;

    if (SOS_VFMW_CheckUUID() == HI_FALSE)
    {
        dprint(PRN_FATAL, "CHeck UUID failed!\n");

        return VDEC_ERR;
    }

    pArgs = SOS_Mmap(pArgs, sizeof(VDEC_OPERATION_S), 1, 1);
    if (pArgs == NULL)
    {
        dprint(PRN_FATAL, "%s %d, map_section_entry failed!\n", __func__,__LINE__);
        return VDEC_ERR;
    }

    ret = VDEC_Init((VDEC_OPERATION_S *)pArgs);

    SOS_Unmap(pArgs, sizeof(VDEC_OPERATION_S));

    return ret;
}

SINT32 SEC_VFMW_Exit(VOID)
{
    SINT32 ret = VDEC_ERR;

    if (SOS_VFMW_CheckUUID() == HI_FALSE)
    {
        dprint(PRN_FATAL, "CHeck UUID failed!\n");

        return VDEC_ERR;
    }

    ret = VDEC_Exit();

    return ret;
}

SINT32 SEC_VFMW_Resume(VOID)
{
    if (SOS_VFMW_CheckUUID() == HI_FALSE)
    {
        dprint(PRN_FATAL, "CHeck UUID failed!\n");

        return VDEC_ERR;
    }

    return VDEC_Resume();
}

SINT32 SEC_VFMW_Suspend(VOID)
{
    if (SOS_VFMW_CheckUUID() == HI_FALSE)
    {
        dprint(PRN_FATAL, "CHeck UUID failed!\n");

        return VDEC_ERR;
    }

    return VDEC_Suspend();
}

UINT32 SEC_GetMapLength(UINT32 eCmdID)
{
    UINT32 Index = 0;
    UINT32 MapLength = 0;

    while (VDEC_CID_HandlerTable[Index].eCmdID < VDEC_CID_BUTT
        && VDEC_CID_HandlerTable[Index].pHandler != HI_NULL)
    {
        if (eCmdID == VDEC_CID_HandlerTable[Index].eCmdID)
        {
            MapLength = VDEC_CID_HandlerTable[Index].Length;
            break;
        }

        Index++;
    }

    return MapLength;
}


SINT32 SEC_VFMW_Control(SINT32 ChanID, UINT32 eCmdID, UINT32 pArgs, UINT32 ParamLength)
{
    SINT32 ret = VDEC_ERR;
    UINT8  MapFlag = 0;
    UINT32 MapLength = 0;

    if (SOS_VFMW_CheckUUID() == HI_FALSE)
    {
        dprint(PRN_FATAL, "Check UUID failed!\n");

        return VDEC_ERR;
    }

    MapLength = SEC_GetMapLength(eCmdID);
    if (MapLength != ParamLength)
    {
        dprint(PRN_FATAL, "eCmdID %d check param length failed: MapLength %d != ParamLength %d.\n", eCmdID, MapLength, ParamLength);
    }

    if (pArgs != 0 && MapLength != 0)
    {
        pArgs = SOS_Mmap(pArgs, MapLength, 1, 1);//指针所指的内容长度未知，暂映射4K
        if (NULL == pArgs)
        {
            dprint(PRN_FATAL, "%s %d, map_section_entry failed ret=%d\n", __func__,__LINE__,ret);
            return VDEC_ERR;
        }
        MapFlag = 1;
    }

    ret = VDEC_Control(ChanID, eCmdID, (VOID *)pArgs);

    if (1 == MapFlag)
    {
        SOS_Unmap(pArgs, MapLength);
    }

    return ret;
}

SINT32 SEC_VFMW_Thread(VOID)
{
    SINT32 ret = 0;

#if (1 == PRINT_TEE_VFMW_TIME)
    static UINT32 BeginTime = 0;
    static UINT32 StartTime = 0;
    static UINT32 Last_StartTime = 0;

    static UINT32 EndTime = 0;
    static UINT32 TotalTime = 0;
    static UINT32 Count = 0;

    StartTime = SOS_GetTimeInUs();
    if (Count == 0)
    {
        BeginTime = StartTime;
    }
#endif

    if (SOS_VFMW_CheckUUID() == HI_FALSE)
    {
        dprint(PRN_FATAL, "CHeck UUID failed!\n");

        return VDEC_ERR;
    }

    ret = VCTRL_RunProcess();

#if (1 == PRINT_TEE_VFMW_TIME)
    EndTime = SOS_GetTimeInUs();
    TotalTime += EndTime - StartTime;
    Count++;

    if (StartTime - Last_StartTime >= 1000*15)
    {
        dprint(PRN_TEE, "twice call secure thread exceed cost:   %d  us\n", StartTime - Last_StartTime);
    }

    Last_StartTime = EndTime;

    if (EndTime - StartTime >= 1000*5)
    {
        dprint(PRN_TEE, "secure thread exceed cost:  %d  start:   %d  end:   %d   us\n",
                           EndTime - StartTime, StartTime, EndTime);
    }

    if (EndTime - BeginTime >= 1000000)
    {
        dprint(PRN_TEE, "secure thread Total: %d  Count: %d  Avg:     %d    us\n", TotalTime, Count, TotalTime / Count);
        TotalTime = BeginTime = StartTime = EndTime = 0;
        Count = 0;
    }
#endif

    return ret;
}

SINT32 SEC_VFMW_Get_Image(SINT32 ChanID, UINT32 pImage)
{
    SINT32 ret = 0;

    if (SOS_VFMW_CheckUUID() == HI_FALSE)
    {
        dprint(PRN_FATAL, "CHeck UUID failed!\n");

        return VDEC_ERR;
    }

    pImage = SOS_Mmap(pImage, sizeof(IMAGE), 1, 1);
    if (NULL == pImage)
    {
        dprint(PRN_FATAL, "%s %d, map_section_entry failed ret=%d\n", __func__,__LINE__,ret);
    }
    else
    {
        ret = VCTRL_GetChanImage(ChanID, (IMAGE *)pImage);
    }

    SOS_Unmap(pImage, sizeof(IMAGE));

    return ret;
}

SINT32 SEC_VFMW_Release_Image(SINT32 ChanID, UINT32 pImage)
{
    SINT32 ret = 0;

    if (SOS_VFMW_CheckUUID() == HI_FALSE)
    {
        dprint(PRN_FATAL, "CHeck UUID failed!\n");

        return VDEC_ERR;
    }

    pImage = SOS_Mmap(pImage, sizeof(IMAGE), 1, 1);
    if (NULL == pImage)
    {
        dprint(PRN_FATAL, "%s %d, map_section_entry failed ret=%d\n", __func__,__LINE__,ret);
    }
    else
    {
        ret = VCTRL_ReleaseChanImage(ChanID, (IMAGE *)pImage);
    }

    SOS_Unmap(pImage, sizeof(IMAGE));

    return ret;
}

SINT32 SEC_VFMW_Read_Proc(UINT32 Page, SINT32 Count)
{
    SINT32 ret = -1;

    if (SOS_VFMW_CheckUUID() == HI_FALSE)
    {
        dprint(PRN_FATAL, "CHeck UUID failed!\n");

        return VDEC_ERR;
    }

    if (g_pProcBuf != NULL)
    {
    #ifndef HI_ADVCA_FUNCTION_RELEASE
        ret = VCTRL_ReadProc((SINT8 *)g_pProcBuf, Count);
    #endif
    }

    return ret;
}

SINT32 SEC_VFMW_Write_Proc(UINT32 Option, SINT32 Value)
{
    SINT32 ret = -1;

    if (SOS_VFMW_CheckUUID() == HI_FALSE)
    {
        dprint(PRN_FATAL, "CHeck UUID failed!\n");

        return VDEC_ERR;
    }

#ifndef HI_ADVCA_FUNCTION_RELEASE
    ret = VCTRL_WriteProc(Option, Value);
#endif

    return ret;
}

SINT32 SEC_TEST_Memcpy(SINT32 Src, UINT32 Dst, UINT32 Len)
{
    SINT32 ret = -1;
    UINT32 viraddr;

    viraddr = (UINT32)tee_hal_remap(Src, Len, 0, 0);
    if (0 == viraddr)
    {
        tee_hal_printf("ca2ta map_section_entry failed ret!\n");
    }
    else
    {
        memcpy((UINT8 *)Dst, (UINT8 *)viraddr, Len);
        tee_hal_unmap((void *)viraddr, Len);
        ret = 0;
    }

    return ret;
}

/*======================================================================*/
/*     Secure firmware initialization                                   */
/*======================================================================*/
tee_hal_driver_init_late(VDEC_OpenModule);
