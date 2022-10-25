#include "vfmw.h"
#include "product.h"
#include "ctrl_case.h"
#include "mem_manage.h"
#include "public.h"
#include "vfmw_ctrl.h"
#include "syntax.h"
#include "vfmw_osal_ext.h"

#ifdef ENV_SOS_KERNEL
#include "vfmw_sos_kernel_osal.h"
#else
#include "vfmw_linux_kernel_osal.h"
#endif


/*======================================================================*/
/*   全局数据                                                           */
/*======================================================================*/
UINT32  g_TimeRecTable[MAX_RECORD_POS][MAX_RECORD_NUM];
UINT8   g_TimeRecId[MAX_RECORD_POS];
UINT32  g_DataTable[MAX_RECORD_DATA][MAX_RECORD_NUM];
UINT8   g_DataRecId[MAX_RECORD_DATA];

SINT32 g_VfmwInitCount  = 0;
VDMHAL_FUN_PTR_S g_vdm_hal_fun_ptr;
Vfmw_Osal_Func_Ptr vfmw_Osal_Func_Ptr_S;


/*======================================================================*/
/*   外部数据                                                           */
/*======================================================================*/
#ifdef ENV_SOS_KERNEL
extern MEMORY_NEEDED_SECVFMW_S *g_pVfmSharewMem;
extern RAW_ARRAY_NS *g_pStreamList;
extern CALLBACK_ARRAY_NS       *g_pCallBackList;
extern VDEC_CHAN_OPTION_S      *g_pChanOption;
extern VDEC_CHAN_STATE_S       *g_pChanState;
extern IMAGE_QUEUE_NS          *g_pImageList;
extern UINT8                   *g_pProcBuf;
#endif


/*======================================================================*/
/*   内部接口                                                           */
/*======================================================================*/

/************************************************************************
    VDEC 对VFMW所有的静态资源进行初始化
 ************************************************************************/
VOID VDEC_InitStaticResource(VOID)
{
    SINT32 ChanID = 0;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_SpinLockInit(G_TASKLOCK);
    vfmw_Osal_Func_Ptr_S.pfun_Osal_SpinLockInit(G_RECORDLOCK);
    vfmw_Osal_Func_Ptr_S.pfun_Osal_SpinLockInit(G_SPINLOCK);
    vfmw_Osal_Func_Ptr_S.pfun_Osal_SpinLockInit(G_SPINLOCK_FSP);
    vfmw_Osal_Func_Ptr_S.pfun_Osal_SpinLockInit(G_FRAMEBUF);
    vfmw_Osal_Func_Ptr_S.pfun_Osal_SpinLockInit(G_SPINLOCKIRQ_DESTROY);
    vfmw_Osal_Func_Ptr_S.pfun_Osal_SpinLockInit(G_ACTIVATELOCK);

    for (ChanID = 0; ChanID < MAX_CHAN_NUM; ChanID++)
    {
        vfmw_Osal_Func_Ptr_S.pfun_Osal_SemaInit(G_RLSSTREAM_SEM, ChanID);
    }

    vfmw_Osal_Func_Ptr_S.pfun_Osal_InitEvent(G_INTWAITQUEUE, 1);

    return;
}

#ifdef ENV_SOS_KERNEL
SINT32 VDEC_InitSecureShareData(VDH_SHARE_DATA_S *ShareData)
{
    SINT32 ret = VDEC_ERR;

#ifdef VDH_DISTRIBUTOR_ENABLE
    VCTRL_WriteProc(1, ShareData->hal_disable);
#endif

    VCTRL_WriteProc(0, ShareData->sec_print_word);

    dprint(PRN_ERROR, "SOS:share_mem_addr=0x%x\n", ShareData->share_mem_addr);

    g_pVfmSharewMem = (MEMORY_NEEDED_SECVFMW_S *)vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelNsMmap(ShareData->share_mem_addr, sizeof(MEMORY_NEEDED_SECVFMW_S));
    if (g_pVfmSharewMem == NULL)
    {
        dprint(PRN_ERROR, "Map g_pVfmSharewMem Failed!\n");

        return VDEC_ERR;
    }

    g_pCallBackList = &g_pVfmSharewMem->CallBackBuf;
    g_pChanOption   = &g_pVfmSharewMem->ChanOption;
    g_pStreamList   = g_pVfmSharewMem->StreamBuf;
    g_pChanState    = g_pVfmSharewMem->ChanState;
    g_pImageList    = g_pVfmSharewMem->ImageQue;
    g_pProcBuf      = g_pVfmSharewMem->ProcBuf;

    return VDEC_OK;
}

VOID VDEC_ExitSecureShareData(VOID)
{
    if (g_pVfmSharewMem != NULL)
    {
        vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelNsMunMap(g_pVfmSharewMem);
        g_pVfmSharewMem = NULL;
    }

    g_pChanOption   = NULL;
    g_pStreamList   = NULL;
    g_pCallBackList = NULL;
    g_pChanState    = NULL;
    g_pImageList    = NULL;
    g_pProcBuf      = NULL;

    return;
}
#endif

#ifdef VDH_DISTRIBUTOR_ENABLE
/************************************************************************
    硬件抽象层初始化接口: 区分安全和非安的初始化
 ************************************************************************/
SINT32 VDEC_InitDistributor(VDEC_OPERATION_S *pArgs)
{
    SINT32 ret = VDEC_ERR;

#if defined(ENV_ARMLINUX_KERNEL)
    ret = VDH_Normal_Init();
    if (ret != VDH_OK)
    {
        dprint(PRN_ERROR, "VDH_Init failed, return %d\n", ret);
        return VDEC_ERR;
    }
#elif defined(ENV_SOS_KERNEL)
    ret = VDH_Secure_Init(&pArgs->ShareData);
    if (ret != VDH_OK)
    {
        dprint(PRN_ERROR, "VDH_Secure_Init failed, return %d\n", ret);
        return VDEC_ERR;
    }
#endif

    return VDEC_OK;
}

/************************************************************************
    硬件抽象层去初始化接口: 区分安全和非安的去初始化
 ************************************************************************/
VOID VDEC_ExitDistributor(VOID)
{
    SINT32 ret = VDH_ERR;

#if defined(ENV_ARMLINUX_KERNEL)
    ret = VDH_Exit();
    if (ret != VDH_OK)
    {
        dprint(PRN_ERROR, "VDH_Exit failed, return %d\n", ret);
    }
#elif defined(ENV_SOS_KERNEL)
    ret = VDH_UnMap_ShareData();
    if (ret != VDH_OK)
    {
        dprint(PRN_ERROR, "VDH_UnMap_ShareData failed, return %d\n", ret);
    }
#endif

    return;
}
#endif

SINT32 VDEC_InitHardware(VDEC_OPERATION_S *pArgs)
{
    SINT32 ret = VDEC_ERR;

    MMUDRV_OpenHardware(0);

#ifdef VDH_DISTRIBUTOR_ENABLE
    if (g_HalDisable != 1)
    {
        ret = VDEC_InitDistributor(pArgs);
    }
    else
#endif
    {
        VDMDRV_OpenHardware(0);
        VDMHAL_GlbReset();

    #ifdef HI_SMMU_SUPPORT
        VDMHAL_SetSmmuPageTableAddr(0);
        VDMHAL_EnableSmmu();
    #endif
        VDMDRV_CloseHardware(0);

        ret = VDEC_OK;
    }

    return ret;
}

VOID VDEC_ExitHardware(VOID)
{
#ifdef VDH_DISTRIBUTOR_ENABLE
    if (g_HalDisable != 1)
    {
        VDEC_ExitDistributor();
    }
#endif

    MMUDRV_CloseHardware(0);

    return;
}

VOID VDEC_InitGlobalResource(VOID)
{
    SINT32  ChanID;

    OSAL_FP_memset(g_TimeRecId,    0, sizeof(UINT8) *MAX_RECORD_POS);
    OSAL_FP_memset(g_TimeRecTable, 0, sizeof(UINT32)*MAX_RECORD_POS*MAX_RECORD_NUM);
    OSAL_FP_memset(g_DataRecId,    0, sizeof(UINT8) *MAX_RECORD_DATA);
    OSAL_FP_memset(g_DataTable,    0, sizeof(UINT32)*MAX_RECORD_DATA*MAX_RECORD_NUM);

    OSAL_FP_sema_init(G_INIT_DEINIT_SEM, 0xFFFFFFFF);
    for (ChanID = 0; ChanID < MAX_CHAN_NUM; ChanID++)
    {
        OSAL_FP_sema_init(G_SAVEYUV_SEM,ChanID);
    }

    return;
}

/*======================================================================*/
/*   对外接口                                                           */
/*======================================================================*/

/************************************************************************
    打开/退出VDEC组件: 在insmod/rmmod时调用如下函数，
    主要职责是创建/销毁proc文件系统
 ************************************************************************/
VOID VDEC_OpenModule(VOID)
{
    OSAL_InitVfmwInterface();

    VDEC_InitGlobalResource();

    PDT_Init(&g_vdm_hal_fun_ptr);

    return;
}

VOID VDEC_ExitModule(VOID)
{
    return;
}

/************************************************************************
    VDEC全局初始化，带扩展配置信息
 ************************************************************************/
SINT32 VDEC_Init(VDEC_OPERATION_S *pArgs)
{
    SINT32 ret = VDEC_ERR;

    if (pArgs == NULL)
    {
        dprint(PRN_ERROR, "VDEC_InitWithOperation has NULL parameter, error!\n");
        return VDEC_ERR;
    }

    vfmw_Osal_Func_Ptr_S.pfun_Osal_SemaDown(G_INIT_DEINIT_SEM, 0xFFFFFFFF);

    if (g_VfmwInitCount >= 1)
    {
        goto OK_EXIT;
    }

    AcceleratorCharacter = NULL;

    VDEC_InitStaticResource();

    MEM_ManagerWithOperation(pArgs);

#ifdef ENV_SOS_KERNEL
    ret = VDEC_InitSecureShareData(&pArgs->ShareData);
    if (ret != VDEC_OK)
    {
        dprint(PRN_ERROR, "VDEC_InitSecureVFMW Failed!\n");
        goto ERR_EXIT;
    }
#endif

    ret = VCTRL_OpenVfmw(pArgs);
    if (ret != VCTRL_OK)
    {
        dprint(PRN_ERROR, "VCTRL_OpenVfmw Failed!\n");
        goto ERR_EXIT;
    }

    ret = VDEC_InitHardware(pArgs);
    if (ret != VDEC_OK)
    {
        dprint(PRN_ERROR, "VDEC_InitHardware Failed!\n");
        VCTRL_CloseVfmw();
        goto ERR_EXIT;
    }

OK_EXIT:
    if (g_VfmwInitCount < 0x7FFFFFFF)
    {
        g_VfmwInitCount++;
        VCTRL_SetCallBack(pArgs->eAdapterType, pArgs->VdecCallback);

        vfmw_Osal_Func_Ptr_S.pfun_Osal_SemaUp(G_INIT_DEINIT_SEM, 0xFFFFFFFF);

        return VDEC_OK;
    }
    else
    {
        dprint(PRN_ERROR, "init count:%d is overflow\n", g_VfmwInitCount);
    }
ERR_EXIT:

    vfmw_Osal_Func_Ptr_S.pfun_Osal_SemaUp(G_INIT_DEINIT_SEM, 0xFFFFFFFF);

    return VDEC_ERR;
}


/************************************************************************
    VDEC全局去初始化
 ************************************************************************/
SINT32 VDEC_Exit(VOID)
{
    SINT8  IsErrorFlag = 0;
    SINT32 ret = VDEC_ERR;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_SemaDown(G_INIT_DEINIT_SEM, 0xFFFFFFFF);

    g_VfmwInitCount = (g_VfmwInitCount > 0) ? g_VfmwInitCount-1 : 0;

    if (g_VfmwInitCount > 0)
    {
        vfmw_Osal_Func_Ptr_S.pfun_Osal_SemaUp(G_INIT_DEINIT_SEM, 0xFFFFFFFF);
        return VDEC_OK;
    }

    ret = VCTRL_CloseVfmw();
    if (ret != VCTRL_OK)
    {
        dprint(PRN_FATAL, "%s call close vfmw failed!\n", __func__);
        IsErrorFlag = 1;
    }

#ifdef ENV_SOS_KERNEL
    VDEC_ExitSecureShareData();
#endif

    VDEC_ExitHardware();

    MEM_ManagerClearOperation();

    g_VfmwInitCount = 0;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_SemaUp(G_INIT_DEINIT_SEM,0xFFFFFFFF);

    return  (IsErrorFlag == 0) ? VDEC_OK : VDEC_ERR;
}

/************************************************************************
    VDEC控制引擎
    ChanID:  需要操作的通道号(对于通道无关操作，此参数可为任意值)
    eCmdID:  命令编码，指定需要VDEC执行何种动作
    pArgs:   命令参数，其格式与eCmdID相关
 ************************************************************************/
SINT32 VDEC_Control(SINT32 ChanID, VDEC_CID_E eCmdID, VOID *pArgs)
{
    if (g_VfmwInitCount <= 0)
    {
        dprint(PRN_FATAL, "%s: VFMW has been destroyed, so any operation is unuseful!\n", __func__);
        return VDEC_ERR;
    }

    return CASE_HandleEntry(ChanID, eCmdID, pArgs);
}

/************************************************************************
    解码器待机接口
 ************************************************************************/
SINT32 VDEC_Suspend(VOID)
{
    VCTRL_Suspend();
    dprint(PRN_FATAL, "VDEC_Suspend ok !\n");

    return VDEC_OK;
}

SINT32 VDEC_Resume(VOID)
{
    VCTRL_Resume();
    dprint(PRN_FATAL, "VDEC_Resume ok !\n");

    return VDEC_OK;
}

/************************************************************************
    解码器获取/释放图像接口
 ************************************************************************/
SINT32 VDEC_GetImage(SINT32 ChanID, IMAGE *pImage)
{
    return VCTRL_GetChanImage(ChanID, pImage);
}

SINT32 VDEC_ReleaseImage(SINT32 ChanID, IMAGE *pImage)
{
    return VCTRL_ReleaseChanImage(ChanID, pImage);
}

