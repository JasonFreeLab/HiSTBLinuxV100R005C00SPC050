/******************************************************************************

  Copyright (C), 2014-2024, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hdmi_mcu_cec.c
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

#include "hdmi_mcu_reg_cec.h"
#include "hdmi_mcu_reg_aon.h"
#include "hdmi_mcu_cec.h"

/************************* define *********************************************/
#define MCU_CEC_CAPTURE_ID_MASK         0xffff
#define MCU_CEC_PING_TIME_OUT           600          // unit 10ms

#define IRQ_ARM_HDMITX_CEC_MASK         0x1000

#define CEC_INIT_CHK_RET(pstCecInfo)    do{ \
	if(pstCecInfo->unStat.u8.bit1Init != HI_TRUE) \
	{HDMI_MCU_ComPuts("cec no init!\n\r"); \
	return HI_FAILURE;} \
}while(0)

#define CEC_EN_CHK_RET(pstCecInfo)     do{ \
    if(pstCecInfo->unStat.u8.bit1Enable != HI_TRUE) \
    {HDMI_MCU_ComPuts("cec no enable!\n\r"); \
    return HI_FAILURE;} \
}while(0)

/*************************  enum   ********************************************/


/*************************  struct ********************************************/
typedef union
{
    struct{
        HI_U16  bit01_tv            : 1  ; /* 00 */
        HI_U16  bit01_record_dev1   : 1  ; /* 01 */
        HI_U16  bit01_record_dev2   : 1  ; /* 02 */
        HI_U16  bit01_tuner1        : 1  ; /* 03 */
        HI_U16  bit01_playback_dev1 : 1  ; /* 04 */
        HI_U16  bit01_audio_sys     : 1  ; /* 05 */
        HI_U16  bit01_tuner2        : 1  ; /* 06 */
        HI_U16  bit01_tuner3        : 1  ; /* 07 */
        HI_U16  bit01_playback_dev2 : 1  ; /* 08 */
        HI_U16  bit01_record_dev3   : 1  ; /* 09 */
        HI_U16  bit01_tuner4        : 1  ; /* 10 */
        HI_U16  bit01_playback_dev3 : 1  ; /* 11 */
        HI_U16  bit01_reserved1     : 1  ; /* 12 */
        HI_U16  bit01_reserved2     : 1  ; /* 13 */
        HI_U16  bit01_specific_use  : 1  ; /* 14 */
        HI_U16  bit01_broadcast     : 1  ; /* 15 */
    }bits;

    HI_U8 u8[2];
    HI_U16 u16;
}CEC_LOGIC_ADDR_U;

/************************* private data ***************************************/
static volatile MCU_COM_U32_U s_un32CecReg;

xdata CEC_INFO_S s_stCecInfo;

static HI_U8     s_u8CecPingTime;

/************************* public  data ***************************************/

/************************* private interface **********************************/
static HI_VOID CecHwEnable(HI_BOOL bEnable)
{
    HI_U8 u8Tmp = 0;
    REG_CEC_CAPTUTR_ID_U *pRegCecCapTureId;
    REG_CEC_TX_CTRL_U    *pRegCecTxCtrl;

    pRegCecCapTureId = (REG_CEC_CAPTUTR_ID_U *)(&s_un32CecReg);
    pRegCecTxCtrl    = (REG_CEC_TX_CTRL_U *)(&s_un32CecReg);

    if (bEnable)
    {
        /* Capture ID have set in cpu when inherit */
        //pRegCecCapTureId->u32 = 0;
        //pRegCecCapTureId->bits.bit16_cec_capture_id        = MCU_CEC_CAPTURE_ID_MASK;
        //HDMI_MCU_ComRegWrite(REG_CEC_CAPTUTR_ID, pRegCecCapTureId->u32);

        /* clear fifo */
        pRegCecTxCtrl->u32 = 0;
        pRegCecTxCtrl->bits.bit01_cec_reg_rx_clr_cur_set   = HI_TRUE;
        pRegCecTxCtrl->bits.bit01_cec_reg_rx_clr_all       = HI_TRUE;
        /* enable */
        pRegCecTxCtrl->bits.bit01_cec_reg_i2c_cec_passthru = HI_FALSE;
        /* ack */
        pRegCecTxCtrl->bits.bit01_cec_reg_nack_hdr         = HI_FALSE;
        HDMI_MCU_ComRegWrite(REG_CEC_TX_CTRL, pRegCecTxCtrl->u32);

        /* irq enable */
        HDMI_MCU_ComRegWrite( REG_AON_TX_AON_INTR_STATE, 0xfffffff2);
        HDMI_MCU_ComRegWrite(REG_AON_TX_AON_INTR_MASK, IRQ_ARM_HDMITX_CEC_MASK);
        u8Tmp  = INT_MASK_3;
        u8Tmp |= IRQ_HDMITX_CEC_MASK;
        INT_MASK_3 = u8Tmp;
        // TODO: print intr
    }
    else
    {
        /* irq disable */
        u8Tmp  = INT_MASK_3;
        u8Tmp &= ~IRQ_HDMITX_CEC_MASK;
        INT_MASK_3 = u8Tmp;
        HDMI_MCU_ComRegWrite( REG_AON_TX_AON_INTR_STATE, 0xfffffff2);
        HDMI_MCU_ComRegWrite(REG_AON_TX_AON_INTR_MASK, 0);

        /* capture ID */
        pRegCecCapTureId->u32 = 0;
        pRegCecCapTureId->bits.bit16_cec_capture_id        = ~MCU_CEC_CAPTURE_ID_MASK;
        HDMI_MCU_ComRegWrite(REG_CEC_CAPTUTR_ID, pRegCecCapTureId->u32);

        /* clear fifo */
        pRegCecTxCtrl->u32 = 0;
        pRegCecTxCtrl->bits.bit01_cec_reg_rx_clr_cur_set    = HI_TRUE;
        pRegCecTxCtrl->bits.bit01_cec_reg_rx_clr_all        = HI_TRUE;
        /* disable */
        pRegCecTxCtrl->bits.bit01_cec_reg_i2c_cec_passthru  = HI_TRUE;
        /* no ack */
        pRegCecTxCtrl->bits.bit01_cec_reg_nack_hdr          = HI_TRUE;
        HDMI_MCU_ComRegWrite(REG_CEC_TX_CTRL, pRegCecTxCtrl->u32);
    }

    return;
}

static HI_S16 CecOperationCodeSet(HI_U8 *pu8Data, HI_U8 u8Len)
{
	HI_U8 u8Tmp;
    REG_TX_CEC_CMD0_U * pRegTxCecCMD0;
    REG_TX_CEC_CMD1_U * pRegTxCecCMD1;
    REG_TX_CEC_CMD2_U * pRegTxCecCMD2;
    REG_TX_CEC_CMD3_U * pRegTxCecCMD3;

    pRegTxCecCMD0 = (REG_TX_CEC_CMD0_U *)(&s_un32CecReg);
    pRegTxCecCMD1 = (REG_TX_CEC_CMD1_U *)(&s_un32CecReg);
    pRegTxCecCMD2 = (REG_TX_CEC_CMD2_U *)(&s_un32CecReg);
    pRegTxCecCMD3 = (REG_TX_CEC_CMD3_U *)(&s_un32CecReg);

    if (u8Len > CEC_MAX_RAW_SIZE)
    {
        return HI_FAILURE;
    }

    s_un32CecReg.u32 = 0;
	for(u8Tmp = 0; u8Tmp < u8Len ; u8Tmp++)
	{
        switch (u8Tmp)
        {
            case 0:
                s_un32CecReg.u32 = HDMI_MCU_ComRegRead(REG_TX_CEC_CMD0);
                pRegTxCecCMD0->bits.bit08_tx_cec_operand0 = *(pu8Data + u8Tmp);
                HDMI_MCU_ComRegWrite( REG_TX_CEC_CMD0, pRegTxCecCMD0->u32);
                break;
            case 1:
                pRegTxCecCMD0->bits.bit08_tx_cec_operand1 = *(pu8Data + u8Tmp);
                HDMI_MCU_ComRegWrite( REG_TX_CEC_CMD0, pRegTxCecCMD0->u32);
                break;
            case 2:
                pRegTxCecCMD0->bits.bit08_tx_cec_operand2 = *(pu8Data + u8Tmp);
                HDMI_MCU_ComRegWrite( REG_TX_CEC_CMD0, pRegTxCecCMD0->u32);
                break;
            case 3:
                s_un32CecReg.u32 = HDMI_MCU_ComRegRead(REG_TX_CEC_CMD1);
                pRegTxCecCMD1->bits.bit08_tx_cec_operand3 = *(pu8Data + u8Tmp);
                HDMI_MCU_ComRegWrite( REG_TX_CEC_CMD1, pRegTxCecCMD1->u32);
                break;
            case 4:
                pRegTxCecCMD1->bits.bit08_tx_cec_operand4 = *(pu8Data + u8Tmp);
                HDMI_MCU_ComRegWrite( REG_TX_CEC_CMD1, pRegTxCecCMD1->u32);
                break;
            case 5:
                pRegTxCecCMD1->bits.bit08_tx_cec_operand5 = *(pu8Data + u8Tmp);
                HDMI_MCU_ComRegWrite( REG_TX_CEC_CMD1, pRegTxCecCMD1->u32);
                break;
            case 6:
                pRegTxCecCMD1->bits.bit08_tx_cec_operand6 = *(pu8Data + u8Tmp);
                HDMI_MCU_ComRegWrite( REG_TX_CEC_CMD1, pRegTxCecCMD1->u32);
                break;
            case 7:
                s_un32CecReg.u32 = HDMI_MCU_ComRegRead(REG_TX_CEC_CMD2);
                pRegTxCecCMD2->bits.bit08_tx_cec_operand7 = *(pu8Data + u8Tmp);
                HDMI_MCU_ComRegWrite( REG_TX_CEC_CMD2, pRegTxCecCMD2->u32);
                break;
            case 8:
                pRegTxCecCMD2->bits.bit08_tx_cec_operand8 = *(pu8Data + u8Tmp);
                HDMI_MCU_ComRegWrite( REG_TX_CEC_CMD2, pRegTxCecCMD2->u32);
                break;
            case 9:
                pRegTxCecCMD2->bits.bit08_tx_cec_operand9 = *(pu8Data + u8Tmp);
                HDMI_MCU_ComRegWrite( REG_TX_CEC_CMD2, pRegTxCecCMD2->u32);
                break;
            case 10:
                pRegTxCecCMD2->bits.bit08_tx_cec_operand10= *(pu8Data + u8Tmp);
                HDMI_MCU_ComRegWrite( REG_TX_CEC_CMD2, pRegTxCecCMD2->u32);
                break;
            case 11:
                s_un32CecReg.u32 = HDMI_MCU_ComRegRead(REG_TX_CEC_CMD3);
                pRegTxCecCMD3->bits.bit08_tx_cec_operand11= *(pu8Data + u8Tmp);
                HDMI_MCU_ComRegWrite( REG_TX_CEC_CMD3, pRegTxCecCMD3->u32);
                break;
            case 12:
                pRegTxCecCMD3->bits.bit08_tx_cec_operand12= *(pu8Data + u8Tmp);
                HDMI_MCU_ComRegWrite( REG_TX_CEC_CMD3, pRegTxCecCMD3->u32);
                break;
            case 13:
                pRegTxCecCMD3->bits.bit08_tx_cec_operand13= *(pu8Data + u8Tmp);
                HDMI_MCU_ComRegWrite( REG_TX_CEC_CMD3, pRegTxCecCMD3->u32);
                break;
            case 14:
                pRegTxCecCMD3->bits.bit08_tx_cec_operand14= *(pu8Data + u8Tmp);
                HDMI_MCU_ComRegWrite( REG_TX_CEC_CMD3, pRegTxCecCMD3->u32);
                break;
            default:
                break;
        }
	}

    return HI_SUCCESS;
}

static HI_VOID CecPhyAddrReport(HI_VOID)
{
    CEC_MSG_FRAME_S stFrame;
    CEC_INFO_S *pstCecInfo = &s_stCecInfo;

    /* set & report my phy addr */
    stFrame.enSrcAddr           = pstCecInfo->enMyLogicAddr;
    stFrame.enDestAddr          = CEC_LOGICALADD_BROADCAST;
    stFrame.u8Opcode            = CEC_OPCODE_REPORT_PHYADDR;
    stFrame.stOperand.u8Data[0] = ((pstCecInfo->au8MyPhyAddr[0] << 4) & 0xf0) | (pstCecInfo->au8MyPhyAddr[1] & 0x0f);
    stFrame.stOperand.u8Data[1] = ((pstCecInfo->au8MyPhyAddr[2] << 4) & 0xf0) | (pstCecInfo->au8MyPhyAddr[3] & 0x0f);
    stFrame.stOperand.u8Data[2] = pstCecInfo->enMyLogicAddr;
    stFrame.stOperand.u8Length  = 3;

    MCU_HDMI_CecFrameTx(&stFrame);

    return;
}

static HI_VOID CecLogicAddrSet(CEC_LOGICALADD_E *penCecLogicAddr)
{
    CEC_LOGIC_ADDR_U CecLogicAddr;
    REG_CEC_AUTODISC_MAP_U *pRegCecAutoDiscMap;

    pRegCecAutoDiscMap = (REG_CEC_AUTODISC_MAP_U *)(&s_un32CecReg);

    pRegCecAutoDiscMap->u32 = HDMI_MCU_ComRegRead(REG_CEC_AUTODISC_MAP);

    CecLogicAddr.u16 = pRegCecAutoDiscMap->bits.bit16_cec_auto_ping_map;

    if( !CecLogicAddr.bits.bit01_tuner1 )
        *penCecLogicAddr = CEC_LOGICALADD_TUNER_1;
    else if( !CecLogicAddr.bits.bit01_tuner2 )
        *penCecLogicAddr = CEC_LOGICALADD_TUNER_2;
    else if( !CecLogicAddr.bits.bit01_tuner3 )
        *penCecLogicAddr = CEC_LOGICALADD_TUNER_3;
    else if( !CecLogicAddr.bits.bit01_tuner4 )
        *penCecLogicAddr = CEC_LOGICALADD_TUNER_4;
    else if( !CecLogicAddr.bits.bit01_playback_dev1 )
        *penCecLogicAddr = CEC_LOGICALADD_PLAYDEV_1;
    else if( !CecLogicAddr.bits.bit01_playback_dev1 )
        *penCecLogicAddr = CEC_LOGICALADD_PLAYDEV_2;
    else if( !CecLogicAddr.bits.bit01_playback_dev1 )
        *penCecLogicAddr = CEC_LOGICALADD_PLAYDEV_3;
    else
        *penCecLogicAddr = CEC_LOGICALADD_BROADCAST;

    return;
}

static HI_VOID CecCaptureIDSet(CEC_LOGICALADD_E enCecLogicAddr)
{
    REG_CEC_CAPTUTR_ID_U *pRegCecCaptureID;

    pRegCecCaptureID = (REG_CEC_CAPTUTR_ID_U *)(&s_un32CecReg);

    pRegCecCaptureID->u32 = 0;
    pRegCecCaptureID->bits.bit16_cec_capture_id = 1<<enCecLogicAddr;
    HDMI_MCU_ComRegWrite(REG_CEC_CAPTUTR_ID, pRegCecCaptureID->u32);

    return;
}

static HI_S16 CecAutoPing(HI_VOID)
{
    HI_S16                  s16Ret = HI_FAILURE;
    CEC_INFO_S              *pstCecInfo = &s_stCecInfo;
    REG_CEC_AUTO_DISC_U     *pRegCecAutoDisc;

    pRegCecAutoDisc = (REG_CEC_AUTO_DISC_U *)(&s_un32CecReg);

    switch (pstCecInfo->enPingStatus)
    {
        case CEC_PING_START:
            /* cec ping clear */
            pRegCecAutoDisc->u32 = 0;
            pRegCecAutoDisc->bits.bit16_cec_auto_ping_clear = HI_TRUE;
            HDMI_MCU_ComRegWrite( REG_CEC_AUTO_DISC, pRegCecAutoDisc->u32 );
            /* cec ping start */
            pRegCecAutoDisc->u32 = 0;
            pRegCecAutoDisc->bits.bit16_cec_auto_ping_start = HI_TRUE;
            HDMI_MCU_ComRegWrite( REG_CEC_AUTO_DISC, pRegCecAutoDisc->u32);

            pstCecInfo->u16PingTimeout   = 0;
            pstCecInfo->enPingStatus     = CEC_PING_WAIT;
            s16Ret  =   HI_FAILURE;
#if HDMI_MCU_DEBUG
            HDMI_MCU_ComPuts("ping start\n\r");
#endif
            break;
        case CEC_PING_WAIT:
            /* cec ping chk done */
            pRegCecAutoDisc->u32 = HDMI_MCU_ComRegRead(REG_CEC_AUTO_DISC);
            if ( pRegCecAutoDisc->bits.bit16_cec_auto_ping_done )
            {
                CecLogicAddrSet(&pstCecInfo->enMyLogicAddr);
                CecCaptureIDSet(pstCecInfo->enMyLogicAddr);

                pstCecInfo->unStat.u8.bit1PingTimeout   = HI_FALSE;
                pstCecInfo->enPingStatus                = CEC_PING_START;
                s16Ret  =   HI_SUCCESS;
#if HDMI_MCU_DEBUG
                HDMI_MCU_ComPuts("ping Ok\n\r");
#endif
            }
            else
            {
                pstCecInfo->u16PingTimeout++;
                HDMI_MCU_ComDelayMs(10);
                s16Ret  =   HI_FAILURE;
                if (pstCecInfo->u16PingTimeout > MCU_CEC_PING_TIME_OUT)
                {
                    pstCecInfo->enPingStatus = CEC_PING_TIMEOUT;
                }
            }
            break;
        case CEC_PING_TIMEOUT:
            /* reset */
            // TODO:
#if HDMI_MCU_DEBUG
            HDMI_MCU_ComPuts("timeout,default\n\r");
#endif
            /* set default logicaddr */
            pstCecInfo->enMyLogicAddr               = CEC_LOGICALADD_TUNER_1;
            pstCecInfo->unStat.u8.bit1PingTimeout   = HI_TRUE;
            pstCecInfo->enPingStatus                = CEC_PING_START;
            CecCaptureIDSet(pstCecInfo->enMyLogicAddr);
            s16Ret                                  = HI_SUCCESS;
            break;

        default:
            break;
    }

    return s16Ret;
}

/************************* public  interface **********************************/
HI_S16 CecRxPoolWrite(CEC_MSG_FRAME_S *pstFrame)
{
    HI_U8 i = 0;
    CEC_INFO_S *pstCecInfo = &s_stCecInfo;

    CEC_EN_CHK_RET(pstCecInfo);

    pstCecInfo->stRx.stPool[pstCecInfo->stRx.u16WtPtr].u8Opcode   = pstFrame->u8Opcode;
    pstCecInfo->stRx.stPool[pstCecInfo->stRx.u16WtPtr].enDestAddr = pstFrame->enDestAddr;
    pstCecInfo->stRx.stPool[pstCecInfo->stRx.u16WtPtr].enSrcAddr  = pstFrame->enSrcAddr;
    pstCecInfo->stRx.stPool[pstCecInfo->stRx.u16WtPtr].stOperand.u8Length = pstFrame->stOperand.u8Length;

    for (i = 0; (i < pstCecInfo->stRx.stPool[pstCecInfo->stRx.u16WtPtr].stOperand.u8Length); i++)
    {
        pstCecInfo->stRx.stPool[pstCecInfo->stRx.u16WtPtr].stOperand.u8Data[i] = pstFrame->stOperand.u8Data[i];
    }

    pstCecInfo->stRx.u16WtPtr++;
    pstCecInfo->stRx.u16WtPtr %= CEC_MAX_MSG_NUM;

    pstCecInfo->stRx.u16InCnt++;
    pstCecInfo->stRx.u16RdAbleCnt++;

    /* if rx buff overflow, cover the first */
    if (pstCecInfo->stRx.u16RdAbleCnt > CEC_MAX_MSG_NUM)
    {
        pstCecInfo->stRx.u16RdPtr++;
        pstCecInfo->stRx.u16RdPtr %= CEC_MAX_MSG_NUM;
        pstCecInfo->stRx.u16RdAbleCnt--;
    }

    return HI_SUCCESS;
}

HI_S16 CecRxPoolRead(CEC_MSG_FRAME_S *pstFrame)
{
    HI_U8 i = 0;
    CEC_INFO_S *pstCecInfo = &s_stCecInfo;

    CEC_EN_CHK_RET(pstCecInfo);

    if (0 == pstCecInfo->stRx.u16RdAbleCnt)
    {
        return HI_FAILURE;
    }

    pstFrame->u8Opcode   = pstCecInfo->stRx.stPool[pstCecInfo->stRx.u16RdPtr].u8Opcode;
    pstFrame->enDestAddr = pstCecInfo->stRx.stPool[pstCecInfo->stRx.u16RdPtr].enDestAddr;
    pstFrame->enSrcAddr  = pstCecInfo->stRx.stPool[pstCecInfo->stRx.u16RdPtr].enSrcAddr;
    pstFrame->stOperand.u8Length = pstCecInfo->stRx.stPool[pstCecInfo->stRx.u16RdPtr].stOperand.u8Length;

    for (i = 0; (i < pstCecInfo->stRx.stPool[pstCecInfo->stRx.u16RdPtr].stOperand.u8Length); i++)
    {
        pstFrame->stOperand.u8Data[i] = pstCecInfo->stRx.stPool[pstCecInfo->stRx.u16RdPtr].stOperand.u8Data[i];
    }

    pstCecInfo->stRx.u16RdPtr++;
    pstCecInfo->stRx.u16RdPtr %= CEC_MAX_MSG_NUM;

    pstCecInfo->stRx.u16OutCnt++;
    pstCecInfo->stRx.u16RdAbleCnt--;

    return HI_SUCCESS;
}

HI_S16 MCU_HDMI_CecInit(HI_VOID)
{
    HI_U8 i;
    CEC_INFO_S *pstCecInfo = &s_stCecInfo;

    pstCecInfo->unStat.u8Byte     = 0;
    pstCecInfo->stRx.u16RdPtr     = 0;
    pstCecInfo->stRx.u16WtPtr     = 0;
    pstCecInfo->stRx.u16RdAbleCnt = 0;
    pstCecInfo->stRx.u16InCnt     = 0;
    pstCecInfo->stRx.u16OutCnt    = 0;
    for (i = 0; i<CEC_MAX_MSG_NUM; i++)
    {
        pstCecInfo->stRx.stPool[i].u8Opcode = 0;
    }
    pstCecInfo->stTx.u8Opcode = 0;

    pstCecInfo->unStat.u8.bit1Init        = HI_TRUE;
    pstCecInfo->unStat.u8.bit1PingTimeout = HI_FALSE;
    pstCecInfo->enPingStatus              = CEC_PING_START;

    return HI_SUCCESS;
}

HI_S16 MCU_HDMI_CecDeInit(HI_VOID)
{
    HI_U8 i;
    CEC_INFO_S *pstCecInfo = &s_stCecInfo;

    CEC_INIT_CHK_RET(pstCecInfo);

    pstCecInfo->unStat.u8Byte     = 0;
    pstCecInfo->stRx.u16RdPtr     = 0;
    pstCecInfo->stRx.u16WtPtr     = 0;
    pstCecInfo->stRx.u16RdAbleCnt = 0;
    pstCecInfo->stRx.u16InCnt     = 0;
    pstCecInfo->stRx.u16OutCnt    = 0;
    for (i = 0; i<CEC_MAX_MSG_NUM; i++)
    {
        pstCecInfo->stRx.stPool[i].u8Opcode = 0;
    }
    pstCecInfo->stTx.u8Opcode = 0;

    pstCecInfo->unStat.u8.bit1Init        = HI_FALSE;
    pstCecInfo->unStat.u8.bit1Enable      = HI_FALSE;
    pstCecInfo->unStat.u8.bit1PingTimeout = HI_FALSE;
    pstCecInfo->enPingStatus              = CEC_PING_START;

    return HI_SUCCESS;
}

HI_S16 MCU_HDMI_CecEnable(HI_BOOL bEnable)
{
    CEC_INFO_S *pstCecInfo = &s_stCecInfo;

    CEC_INIT_CHK_RET(pstCecInfo);

    if (bEnable)
    {
        CecHwEnable(HI_TRUE);
        pstCecInfo->unStat.u8.bit1Enable = HI_TRUE;
    }
    else
    {
        CecHwEnable(HI_FALSE);
        pstCecInfo->unStat.u8.bit1Enable = HI_FALSE;
    }

    return HI_SUCCESS;
}

HI_S16 MCU_HDMI_CecFrameTx(CEC_MSG_FRAME_S *pstFrame)
{
    HI_U8       u8Timeout   = 0;
    HI_BOOL     bSendFinish = HI_FALSE;
    CEC_INFO_S  *pstCecInfo = &s_stCecInfo;

    CEC_EN_CHK_RET(pstCecInfo);

    /* check tx lenth */
    if (pstFrame->stOperand.u8Length > CEC_MAX_RAW_SIZE)
    {
        pstFrame->stOperand.u8Length = CEC_MAX_RAW_SIZE;
    }

    /* stop */
    s_un32CecReg.u32 = HDMI_MCU_ComRegRead(REG_CEC_TX_CTRL);
    ((REG_CEC_TX_CTRL_U *)&s_un32CecReg)->bits.bit01_manual_cmd_set = HI_FALSE;
    HDMI_MCU_ComRegWrite( REG_CEC_TX_CTRL, s_un32CecReg.u32);
    /* src addr */
    s_un32CecReg.u32 = 0;
    ((REG_CEC_TX_INIT_U *)&s_un32CecReg)->bits.bit04_cec_tx_init_id = pstFrame->enSrcAddr;
    HDMI_MCU_ComRegWrite( REG_CEC_TX_INIT, s_un32CecReg.u32);
    /* dest addr */
    s_un32CecReg.u32 = 0;
    ((REG_CEC_TX_DEST_U *)&s_un32CecReg)->bits.bit04_cec_tx_dest_id = pstFrame->enDestAddr;
    HDMI_MCU_ComRegWrite( REG_CEC_TX_DEST, s_un32CecReg.u32);
    /* opcode */
    s_un32CecReg.u32 = 0;
    ((REG_TX_CEC_CMD0_U *)&s_un32CecReg)->bits.bit08_tx_cec_command = pstFrame->u8Opcode;
    HDMI_MCU_ComRegWrite( REG_TX_CEC_CMD0, s_un32CecReg.u32);
    /* lenth */
    s_un32CecReg.u32 = HDMI_MCU_ComRegRead(REG_CEC_TX_CTRL);
    ((REG_CEC_TX_CTRL_U *)&s_un32CecReg)->bits.bit04_cec_reg_tx_cmd_cnt = pstFrame->stOperand.u8Length;
    HDMI_MCU_ComRegWrite( REG_CEC_TX_CTRL, s_un32CecReg.u32);
    /* data */
    CecOperationCodeSet(&pstFrame->stOperand.u8Data, pstFrame->stOperand.u8Length);
    /* start */
    s_un32CecReg.u32 = HDMI_MCU_ComRegRead(REG_CEC_TX_CTRL);
    ((REG_CEC_TX_CTRL_U *)&s_un32CecReg)->bits.bit01_manual_cmd_set = HI_TRUE;
    HDMI_MCU_ComRegWrite( REG_CEC_TX_CTRL, s_un32CecReg.u32);

    /* wait tx finish */
    for (u8Timeout = 0, bSendFinish = HI_FALSE; ((!bSendFinish) && (u8Timeout<5)); u8Timeout++)
    {
        HDMI_MCU_ComDelayMs(10);
        s_un32CecReg.u32 = HDMI_MCU_ComRegRead(REG_AON_TX_AON_INTR_STATE);
        bSendFinish = ((REG_TX_AON_INTR_STATE *)&s_un32CecReg)->bits.bit01_aon_intr_stat11;
    }
    s_un32CecReg.u32 = 0;
    ((REG_TX_AON_INTR_STATE *)&s_un32CecReg)->bits.bit01_aon_intr_stat11 = HI_TRUE;
    HDMI_MCU_ComRegWrite( REG_AON_TX_AON_INTR_STATE, s_un32CecReg.u32);

#if 0
    /* cpy to CecInfo */
    pstCecInfo->stTx.enDestAddr = pstFrame->enDestAddr;
    pstCecInfo->stTx.enSrcAddr  = pstFrame->enSrcAddr;
    pstCecInfo->stTx.u8Opcode   = pstFrame->u8Opcode;
    for (i = 0; i < pstFrame->stOperand.u8Length; i++)
    {
        pstCecInfo->stTx.stOperand.u8Data[i] = pstFrame->stOperand.u8Data[i];
    }
#endif

    return bSendFinish ? HI_SUCCESS : HI_FAILURE;
}

HI_S16 MCU_HDMI_CecFrameRx(CEC_MSG_FRAME_S *pstFrame)
{
    CEC_INFO_S *pstCecInfo = &s_stCecInfo;

    CEC_EN_CHK_RET(pstCecInfo);

    s_un32CecReg.u32 = HDMI_MCU_ComRegRead(REG_CEC_RX_STATE);
    pstFrame->enDestAddr = ((REG_CEC_RX_STATE_U *)&s_un32CecReg)->bits.bit04_cec_rx_dest_cmd_header;
    pstFrame->enSrcAddr  = ((REG_CEC_RX_STATE_U *)&s_un32CecReg)->bits.bit04_cec_rx_init_cmd_header;
    pstFrame->stOperand.u8Length = ((REG_CEC_RX_STATE_U *)&s_un32CecReg)->bits.bit04_cec_reg_rx_cmd_byte_cnt;

    s_un32CecReg.u32 = HDMI_MCU_ComRegRead(REG_RX_CEC_CMD0);
    pstFrame->u8Opcode   = ((REG_RX_CEC_CMD0_U *)&s_un32CecReg)->bits.bit08_rx_cec_command;

    if (pstFrame->stOperand.u8Length)
    {
        pstFrame->stOperand.u8Data[0] = ((REG_RX_CEC_CMD0_U *)&s_un32CecReg)->bits.bit08_rx_cec_operand0;
        pstFrame->stOperand.u8Data[1] = ((REG_RX_CEC_CMD0_U *)&s_un32CecReg)->bits.bit08_rx_cec_operand1;
        pstFrame->stOperand.u8Data[2] = ((REG_RX_CEC_CMD0_U *)&s_un32CecReg)->bits.bit08_rx_cec_operand2;

        s_un32CecReg.u32 = HDMI_MCU_ComRegRead(REG_RX_CEC_CMD1);
        pstFrame->stOperand.u8Data[3] = ((REG_RX_CEC_CMD1_U *)&s_un32CecReg)->bits.bit08_rx_cec_operand3;
        pstFrame->stOperand.u8Data[4] = ((REG_RX_CEC_CMD1_U *)&s_un32CecReg)->bits.bit08_rx_cec_operand4;
        pstFrame->stOperand.u8Data[5] = ((REG_RX_CEC_CMD1_U *)&s_un32CecReg)->bits.bit08_rx_cec_operand5;
        pstFrame->stOperand.u8Data[6] = ((REG_RX_CEC_CMD1_U *)&s_un32CecReg)->bits.bit08_rx_cec_operand6;

        s_un32CecReg.u32 = HDMI_MCU_ComRegRead(REG_RX_CEC_CMD2);
        pstFrame->stOperand.u8Data[7] = ((REG_RX_CEC_CMD2_U *)&s_un32CecReg)->bits.bit08_rx_cec_operand7;
        pstFrame->stOperand.u8Data[8] = ((REG_RX_CEC_CMD2_U *)&s_un32CecReg)->bits.bit08_rx_cec_operand8;
        pstFrame->stOperand.u8Data[9] = ((REG_RX_CEC_CMD2_U *)&s_un32CecReg)->bits.bit08_rx_cec_operand9;
        pstFrame->stOperand.u8Data[10] = ((REG_RX_CEC_CMD2_U *)&s_un32CecReg)->bits.bit08_rx_cec_operand10;

        s_un32CecReg.u32 = HDMI_MCU_ComRegRead(REG_RX_CEC_CMD3);
        pstFrame->stOperand.u8Data[11] = ((REG_RX_CEC_CMD3_U *)&s_un32CecReg)->bits.bit08_rx_cec_operand11;
        pstFrame->stOperand.u8Data[12] = ((REG_RX_CEC_CMD3_U *)&s_un32CecReg)->bits.bit08_rx_cec_operand12;
        pstFrame->stOperand.u8Data[13] = ((REG_RX_CEC_CMD3_U *)&s_un32CecReg)->bits.bit08_rx_cec_operand13;
        pstFrame->stOperand.u8Data[14] = ((REG_RX_CEC_CMD3_U *)&s_un32CecReg)->bits.bit08_rx_cec_operand14;

    }

    /* clear current rxfifo */
    s_un32CecReg.u32 = HDMI_MCU_ComRegRead(REG_CEC_TX_CTRL);
    ((REG_CEC_TX_CTRL_U *)&s_un32CecReg)->bits.bit01_cec_reg_rx_clr_cur_set = HI_TRUE;
    HDMI_MCU_ComRegWrite( REG_CEC_TX_CTRL, s_un32CecReg.u32);

#if HDMI_MCU_DEBUG
    HDMI_MCU_ComPuts("cecrx");
    HDMI_MCU_ComPutU8Hex(pstFrame->u8Opcode);
    HDMI_MCU_ComPuts("\n\r");
#endif

    return HI_SUCCESS;
}

HI_S16 MCU_HDMI_CecPhyAddrSet(HI_U8 *pu8PhyAddr, CEC_LOGICALADD_E *penLogicAddr)
{
    HI_U8 i = 0;
    CEC_INFO_S *pstCecInfo = &s_stCecInfo;

    MCU_NULL_CHK_RET(penLogicAddr);
    CEC_EN_CHK_RET(pstCecInfo);

    if (HI_SUCCESS == CecAutoPing())
    {
        //for (i = 0; (i < CEC_PHY_ADDR_SIZE) && (!(pu8PhyAddr + i) ); i++)   // check null pointer
        for (i = 0; i < CEC_PHY_ADDR_SIZE; i++)
        {
            pstCecInfo->au8MyPhyAddr[i] = pu8PhyAddr[i];
        }

        *penLogicAddr = pstCecInfo->enMyLogicAddr;

        CecPhyAddrReport();

        return HI_SUCCESS;
    }

    return HI_FAILURE;
}

/************************* end of file ****************************************/

