/******************************************************************************

  Copyright (C), 2014-2024, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hdmi_mcu_task.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2015/08/13
  Description   :
  History       :
  Date          : 2015/08/13
  Author        : sdk
  Modification  :
*******************************************************************************/

#include "reg51.h"
#include "hdmi_mcu_reg_aon.h"

#include "hdmi_mcu_cec.h"
#include "hdmi_mcu_ddc_edid.h"
#include "hdmi_mcu_task.h"

/************************* define *********************************************/

#define HDMI_CPU_MCU_SWITCH_INFO_ADDR   0xf8000218
#define HDMI_MCU_CPU_CEC_INFO_0_ADDR    0xf8000210
#define HDMI_MCU_CPU_CEC_INFO_1_ADDR    0xf8000214  // cpu write cecLogicAddr

#define HDMI_INIT_CHK(pstHdmiInfo)  do{ \
	if(pstHdmiInfo->bInit != HI_TRUE) \
	{HDMI_MCU_ComPuts("hdmi no init!\n\r"); \
	return ;} \
}while(0)

/*************************  enum   ********************************************/

/*************************  struct ********************************************/
typedef struct
{
    HI_BOOL          bInit;
    HI_BOOL          bHdmiMcuEnable;
    HI_BOOL          bHpd;
    HI_BOOL          bReReadEdid;
    HI_BOOL          bCecEnable;
    CEC_LOGICALADD_E enCecLogicAddr;
    HI_BOOL          bLogicValid;
    HI_BOOL          bPhyAddrSet;
    HI_U8            au8PhyAddr[CEC_PHY_ADDR_SIZE];
}HDMI_INFO_S;

/************************* private data ***************************************/
static HDMI_INFO_S s_stHdmiInfo;

/************************* public  data ***************************************/

/************************* private interface **********************************/
static HI_VOID TaskIrqClear(HI_VOID)
{
    //un32RegAonIntrState.u32 = 0;
    HDMI_MCU_ComRegWrite( REG_AON_TX_AON_INTR_STATE, 0xfffffff2);

    return;
}

static HI_BOOL TaskIsCpuOffRun(HI_VOID)
{
    MCU_COM_U32_U unCpuSwitchInfo;

    unCpuSwitchInfo.u32 = HDMI_MCU_ComRegRead( HDMI_CPU_MCU_SWITCH_INFO_ADDR);

    if (unCpuSwitchInfo.u8[3] > 0)
    {
        return HI_TRUE;
    }

    return HI_FALSE;
}

static HI_BOOL TaskIsCpuCecEnable(HI_VOID)
{
    MCU_COM_U32_U unCpuSwitchInfo;

    unCpuSwitchInfo.u32 = HDMI_MCU_ComRegRead( HDMI_CPU_MCU_SWITCH_INFO_ADDR);
    if ( 1 == unCpuSwitchInfo.u8[2] )
    {
        return HI_TRUE;
    }

    return HI_FALSE;
}

static HI_S16 TaskCpuPhyAddrGet(HI_U8 *pu8CecPhyAddr, HI_U8 u8Len)
{
    MCU_COM_U32_U unPhyAddr;

    MCU_NULL_CHK_RET(pu8CecPhyAddr); // check 1/2/3 null pointer

    if (u8Len != CEC_PHY_ADDR_SIZE)
    {
        return HI_FAILURE;
    }

    unPhyAddr.u32    = HDMI_MCU_ComRegRead(HDMI_MCU_CPU_CEC_INFO_0_ADDR);
    pu8CecPhyAddr[0] = unPhyAddr.u8[0];
    pu8CecPhyAddr[1] = unPhyAddr.u8[1];
    pu8CecPhyAddr[2] = unPhyAddr.u8[2];
    pu8CecPhyAddr[3] = unPhyAddr.u8[3];
#if 0 // HDMI_MCU_DEBUG
    HDMI_MCU_ComPuts("InitPhy");
    HDMI_MCU_ComPutU8Hex(pu8CecPhyAddr[0]);
#endif
    if ( 0 == pu8CecPhyAddr[0])
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S16 TaskCpuLogicAddrGet(CEC_LOGICALADD_E *penLogicAddr)
{
    MCU_COM_U32_U unLogicAddr;

    unLogicAddr.u32 = HDMI_MCU_ComRegRead(HDMI_MCU_CPU_CEC_INFO_1_ADDR);
#if 0 // HDMI_MCU_DEBUG
    HDMI_MCU_ComPuts("InitLogic");
    HDMI_MCU_ComPutU8Hex(unLogicAddr.u8[3]);
#endif
    if (unLogicAddr.u8[3] < CEC_LOGICALADD_BUTT)
    {
        *penLogicAddr   = unLogicAddr.u8[3];

        return HI_SUCCESS;
    }

    return HI_FAILURE;
}

static HI_BOOL TaskIsCecIrq(HI_VOID)
{
    REG_TX_AON_INTR_STATE un32RegAonIntrState;

    if (INT_STATUS_IP3 & IRQ_HDMITX_CEC_MASK)
    {
        un32RegAonIntrState.u32 = HDMI_MCU_ComRegRead(REG_AON_TX_AON_INTR_STATE);
        return un32RegAonIntrState.bits.bit01_aon_intr_stat12 ? HI_TRUE : HI_FALSE; // cec_rx_fifo_nempty, received a message
    }

    return HI_FALSE;
}

static HI_S16 TaskHpdGet(HI_BOOL *pbHpd)
{
    REG_TX_AON_STATE      un32RegAonTxState;
    REG_HOTPLUG_ST_CFG    un32RegAonHotplugCfg;
    REG_TX_AON_INTR_STATE un32RegAonIntrState;

    /* read Hpd intr */
    un32RegAonIntrState.u32  = HDMI_MCU_ComRegRead(REG_AON_TX_AON_INTR_STATE);
    if (un32RegAonIntrState.bits.bit01_aon_intr_stat0)
    {
        un32RegAonHotplugCfg.u32 = HDMI_MCU_ComRegRead(REG_AON_HOTPLUG_ST_CFG);
        un32RegAonTxState.u32    = HDMI_MCU_ComRegRead(REG_AON_TX_AON_STATE);

        if (un32RegAonHotplugCfg.bits.bit01_hpd_polarity_ctl)
        {
            *pbHpd = un32RegAonTxState.bits.bit01_hotplug_state ? HI_FALSE: HI_TRUE;
        }
        else
        {
            *pbHpd = un32RegAonTxState.bits.bit01_hotplug_state ? HI_TRUE : HI_FALSE;
        }

        /* clear Hpd intr */
        un32RegAonIntrState.u32 = 0;
        un32RegAonIntrState.bits.bit01_aon_intr_stat0 = 1;
        HDMI_MCU_ComRegWrite(REG_AON_TX_AON_INTR_STATE, un32RegAonIntrState.u32);
        return HI_SUCCESS;
    }

    return HI_FAILURE;
}

static HI_VOID TaskCecHandle(HI_VOID)
{
    HI_U8           u8TxCnt       = 0;
    HI_BOOL         bNeedResponse = HI_FALSE;
    HDMI_INFO_S     *pstHdmiInfo  = &s_stHdmiInfo;
    CEC_MSG_FRAME_S stFrame;

    while (HI_SUCCESS == CecRxPoolRead(&stFrame) && (u8TxCnt < 3))
    {
        bNeedResponse = HI_FALSE;

        stFrame.enDestAddr = stFrame.enSrcAddr;
        stFrame.enSrcAddr  = pstHdmiInfo->enCecLogicAddr;
#if HDMI_MCU_DEBUG
        HDMI_MCU_ComPuts("handle");
        HDMI_MCU_ComPutU8Hex(stFrame.u8Opcode);
#endif
        switch (stFrame.u8Opcode)
        {
            /* opcode wakeup */
            case CEC_OPCODE_IMAGE_VIEW_ON:
            case CEC_OPCODE_ROUTING_CHANGE:
            case CEC_OPCODE_ACTIVE_SOURCE:
            case CEC_OPCODE_REQUEST_ACTIVE_SOURCE:
                HDMI_MCU_ComPuts("wakeup\n\r");
                pmocflag = HI_TRUE;
                pmocType = HI_UNF_PMOC_WKUP_CEC;
                break;
            /* other opcode handle */
            case CEC_OPCODE_GIVE_OSD_NAME:
                stFrame.u8Opcode   = CEC_OPCODE_SET_OSD_NAME;
                stFrame.stOperand.u8Data[0] = 'h';
                stFrame.stOperand.u8Data[0] = 'i';
                stFrame.stOperand.u8Data[0] = 's';
                stFrame.stOperand.u8Length  = 3;
                bNeedResponse = HI_TRUE;
                break;
            case CEC_OPCODE_GIVE_PHYSICAL_ADDRESS: /* wakeup */
                stFrame.u8Opcode   = CEC_OPCODE_REPORT_PHYADDR;
                stFrame.stOperand.u8Data[0] = ((pstHdmiInfo->au8PhyAddr[0] << 4) & 0xf0) | (pstHdmiInfo->au8PhyAddr[1] & 0x0f); // [Physical Address(A.B.C.D):A B]
                stFrame.stOperand.u8Data[0] = ((pstHdmiInfo->au8PhyAddr[2] << 4) & 0xf0) | (pstHdmiInfo->au8PhyAddr[3] & 0x0f) ; // [Physical Address(A.B.C.D):C D]
                stFrame.stOperand.u8Data[0] = pstHdmiInfo->enCecLogicAddr;
                stFrame.stOperand.u8Length  = 3;
                HDMI_MCU_ComPuts("wakeup\n\r");
                pmocflag = HI_TRUE;
                pmocType = HI_UNF_PMOC_WKUP_CEC;
                bNeedResponse = HI_TRUE;
                break;
            case CEC_OPCODE_GIVE_DEVICE_VENDOR_ID:
                stFrame.enDestAddr = CEC_LOGICALADD_BROADCAST;
                stFrame.u8Opcode   = CEC_OPCODE_DEVICE_VENDOR_ID;
                stFrame.stOperand.u8Data[0] = 'h';
                stFrame.stOperand.u8Data[0] = 'i';
                stFrame.stOperand.u8Data[0] = 's';
                stFrame.stOperand.u8Length  = 3;
                bNeedResponse = HI_TRUE;
                break;
            case CEC_OPCODE_MENU_REQUEST:
                stFrame.u8Opcode   = CEC_OPCODE_MENU_STATUS;
                // 0x00:active 0x01:deactive 0x02:query
                // stFrame.stOperand.u8Data[0] not change
                stFrame.stOperand.u8Length  = 1;
                bNeedResponse = HI_TRUE;
                break;
            case CEC_OPCODE_GIVE_DEVICE_POWER_STATUS:
                stFrame.u8Opcode   = CEC_OPCODE_REPORT_POWER_STATUS;
                // 0:on 1:standby 2:standby2on 3:on2standby
                stFrame.stOperand.u8Data[0] = 0x02;
                stFrame.stOperand.u8Length  = 1;
                bNeedResponse = HI_TRUE;
                break;
            case CEC_OPCODE_GET_MENU_LANGUAGE:
                stFrame.u8Opcode   = CEC_OPCODE_SET_MENU_LANGUAGE;
                stFrame.stOperand.u8Data[0] = 'c';
                stFrame.stOperand.u8Data[0] = 'h';
                stFrame.stOperand.u8Data[0] = 'i';
                stFrame.stOperand.u8Length  = 3;
                bNeedResponse = HI_TRUE;
                break;
            case CEC_OPCODE_GET_CEC_VERSION:
                stFrame.u8Opcode   = CEC_OPCODE_CEC_VERSION;
                stFrame.stOperand.u8Data[0] = 0x04;
                stFrame.stOperand.u8Length  = 1;
                bNeedResponse = HI_TRUE;
                break;
            default:
                break;
        }

        if (bNeedResponse)
        {
            if (HI_FAILURE == MCU_HDMI_CecFrameTx(&stFrame))
            {
#if HDMI_MCU_DEBUG
                HDMI_MCU_ComPutU8Hex(stFrame.u8Opcode);
                HDMI_MCU_ComPuts(" tx timeout\n\r");
#endif
            }
            u8TxCnt++;
        }
    }

    return;
}

/************************* public  interface **********************************/

/**
\brief	mcu hdmi task init
\param      none
\retval     none
*/
HI_VOID MCU_HDMI_TaskInit(HI_VOID)
{
    HDMI_INFO_S * pstHdmiInfo = &s_stHdmiInfo;

    MCU_HDMI_DdcInit();
    MCU_HDMI_CecInit();

    pstHdmiInfo->bReReadEdid    = HI_FALSE;
    pstHdmiInfo->bInit          = HI_TRUE;
    pstHdmiInfo->bHdmiMcuEnable = HI_TRUE;
    pstHdmiInfo->bHpd           = HI_FALSE;
    pstHdmiInfo->bCecEnable     = HI_FALSE;
    pstHdmiInfo->bLogicValid    = HI_FALSE;
    pstHdmiInfo->enCecLogicAddr = CEC_LOGICALADD_BUTT;
    pstHdmiInfo->bPhyAddrSet    = HI_FALSE;

    /* get phyaddr inherit from cpu */
    if (HI_SUCCESS == TaskCpuPhyAddrGet(pstHdmiInfo->au8PhyAddr, CEC_PHY_ADDR_SIZE))
    {
        pstHdmiInfo->bPhyAddrSet = HI_TRUE;

        /* get logicaddr inherit from cpu */
        if (HI_SUCCESS == TaskCpuLogicAddrGet(&pstHdmiInfo->enCecLogicAddr))
        {
            pstHdmiInfo->bPhyAddrSet = HI_FALSE;
            pstHdmiInfo->bLogicValid = HI_TRUE;
        }
    }

    return;
}

/**
\brief	mcu hdmi task handle ,such as ddc read,cec Tx & Rx,etc.
\param      none
\retval     none
*/
HI_VOID MCU_HDMI_TaskHandle(HI_VOID)
{
    HDMI_INFO_S * pstHdmiInfo = &s_stHdmiInfo;

    HDMI_INIT_CHK(pstHdmiInfo);

    /* cpu switch info */
    if (!TaskIsCpuOffRun())
    {
        HDMI_MCU_ComPuts("CpuRun");
        return;
    }

    /* hdmi software enable && cpu cec enable */
    if (!pstHdmiInfo->bHdmiMcuEnable || !TaskIsCpuCecEnable())
    {
        HDMI_MCU_ComPuts("CecUnEn");
        return;
    }

    /* polling hotplug */
    if (HI_SUCCESS == TaskHpdGet(&pstHdmiInfo->bHpd))
    {
        if (pstHdmiInfo->bHpd)
        {
#if HDMI_MCU_DEBUG
            HDMI_MCU_ComPuts("Hpd\n\r");
#endif
            pstHdmiInfo->bReReadEdid = HI_TRUE;
            pstHdmiInfo->bLogicValid = HI_FALSE;
        }
        else
        {
#if HDMI_MCU_DEBUG
            HDMI_MCU_ComPuts("UnHpd\n\r");
#endif
        }
    }

    /* reRead edid */
    if (pstHdmiInfo->bReReadEdid)
    {
        if (HI_SUCCESS == MCU_HDMI_DdcEdidCecAddrGet(pstHdmiInfo->au8PhyAddr, CEC_PHY_ADDR_SIZE))
        {
            pstHdmiInfo->bReReadEdid = HI_FALSE;
            pstHdmiInfo->bPhyAddrSet = HI_TRUE;
#if HDMI_MCU_DEBUG
            HDMI_MCU_ComPuts("phy");
            HDMI_MCU_ComPutU8Hex(pstHdmiInfo->au8PhyAddr[0]);
            HDMI_MCU_ComPuts("\n\r");
#endif
        }
    }

    /* cec enable */
    if (!pstHdmiInfo->bCecEnable)
    {
        if ( HI_SUCCESS == MCU_HDMI_CecEnable(HI_TRUE) )
        {
            pstHdmiInfo->bCecEnable = HI_TRUE;
        }
        else
        {
            pstHdmiInfo->bCecEnable = HI_FALSE;
        }
    }

    /* setPhyAddr AutoPing */
    if (pstHdmiInfo->bPhyAddrSet && pstHdmiInfo->bCecEnable)
    {
        if (HI_SUCCESS == MCU_HDMI_CecPhyAddrSet(pstHdmiInfo->au8PhyAddr, &pstHdmiInfo->enCecLogicAddr))
        {
            pstHdmiInfo->bPhyAddrSet = HI_FALSE;
            pstHdmiInfo->bLogicValid = HI_TRUE;
        }
    }

    /* cec handle */
    if (pstHdmiInfo->bLogicValid)
    {
        TaskCecHandle();
    }

    return;
}

/**
\brief	mcu hdmi task deinit
\param      none
\retval     none
*/
HI_VOID MCU_HDMI_TaskDeInit(HI_VOID)
{
    HDMI_INFO_S * pstHdmiInfo = &s_stHdmiInfo;

    HDMI_INIT_CHK(pstHdmiInfo);

    MCU_HDMI_CecEnable(HI_FALSE);

    MCU_HDMI_DdcDeInit();
    MCU_HDMI_CecDeInit();

    pstHdmiInfo->bReReadEdid    = HI_FALSE;
    pstHdmiInfo->bInit          = HI_FALSE;
    pstHdmiInfo->bHdmiMcuEnable = HI_FALSE;
    pstHdmiInfo->bHpd           = HI_FALSE;
    pstHdmiInfo->bCecEnable     = HI_FALSE;
    pstHdmiInfo->bLogicValid    = HI_FALSE;
    pstHdmiInfo->bPhyAddrSet    = HI_FALSE;

    return;
}

/**
\brief	mcu hdmi task interrupt sever function
\param      none
\retval     none
*/
HI_VOID MCU_HDMI_TaskIrqHandle(HI_VOID)
{
    REG_TX_AON_INTR_STATE un32RegAonIntrState;
    CEC_MSG_FRAME_S stFrame;
    HDMI_INFO_S     *pstHdmiInfo = &s_stHdmiInfo;

    if ( pstHdmiInfo->bHdmiMcuEnable && TaskIsCecIrq() )
    {
        /* clear rx fifo nempty intr */
        un32RegAonIntrState.u32 = 0;
        un32RegAonIntrState.bits.bit01_aon_intr_stat12 = HI_TRUE;
        HDMI_MCU_ComRegWrite( REG_AON_TX_AON_INTR_STATE, un32RegAonIntrState.u32);

        if (HI_SUCCESS == MCU_HDMI_CecFrameRx(&stFrame))
        {
            if (HI_SUCCESS != CecRxPoolWrite(&stFrame))
            {
#if HDMI_MCU_DEBUG
                HDMI_MCU_ComPuts("rxpool err\n\r");
#endif
            }
        }
    }

    return;
}

/************************* end of file ****************************************/

