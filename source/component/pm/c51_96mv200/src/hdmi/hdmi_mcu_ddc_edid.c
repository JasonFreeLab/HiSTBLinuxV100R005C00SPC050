/******************************************************************************

  Copyright (C), 2014-2024, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hdmi_hal_ddc.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2015/08/13
  Description   :
  History       :
  Date          : 2015/08/13
  Author        : sdk
  Modification  :
*******************************************************************************/

#include "hdmi_mcu_reg_aon.h"
#include "hdmi_mcu_ddc_edid.h"

/************************* define *********************************************/
#define MCU_DDC_SPEED_80KHZ             0x4a
#define MCU_DDC_CMD_FIFO_CLR            0x09
#define MCU_DDC_CMD_MASTER_ABORT        0x0f

#define DDC_EDID_SALVE_ADDR             0xa0

#define DDC_EXT_BLOCK_OFFSET            0x7e
#define DDC_MAX_EDID_BUF_SIZE           128

#define EDID_UPPER_NIBBLE_MASK			0xF0
#define EDID_LOWER_NIBBLE_MASK			0x0F

/* EXTENSION BLOCK */
#define EDID_CEA_EXTVERSION3_TAG        0x02
#define EDID_CEA_EXTVERSION3_REVISION   0x03
#define EDID_DB_LEN_MASK  				0x1F
#define EDID_DB_TAG_CODE_MASK 			0xE0
/* Tag Code */
#define EDID_VENDOR_DATA_BLOCK   		0x03
/* cec phy addr offset */
#define EDID_CEA_PHYADDR_OFFSET         0x04

#define DDC_INIT_CHK_RET(pstDdcInfo) do{ \
	if(pstDdcInfo->bInit != HI_TRUE) \
	{HDMI_MCU_ComPuts("ddc no init!\n\r"); \
	return HI_FAILURE;} \
}while(0)

/*************************  enum   ********************************************/
enum EdidReadEnum
{
    EDID_RD_EXT_CNT,
    EDID_RD_EXT_EDID_0,
    EDID_RD_EXT_EDID_1_2,
    EDID_RD_NO_PHYADDR,
    EDID_RD_ERR,
    EDID_RD_BUTT
};

/*************************  struct ********************************************/

/************************* private data ***************************************/
volatile MCU_COM_U32_U s_u32DdcReg;

//static DDC_CFG_S  s_stDdcCfg = {0};
xdata  HI_U8      s_au8Edid[DDC_MAX_EDID_BUF_SIZE];
static DDC_INFO_S s_stDdcInfo;

/************************* public  data ***************************************/

/************************* private interface **********************************/
static HI_S16 EdidBlockChkSum(HI_U8 *pau8Data, HI_U8 u8Len)
{
    HI_U8 	i = 0;
    HI_U16 	u16CheckSum = 0;

    for (i = 0; i < u8Len; i++)
    {
        u16CheckSum += pau8Data[i];
#if 0//HDMI_MCU_DEBUG
        HDMI_MCU_ComPutU8Hex(pau8Data[i]);
        HDMI_MCU_ComDelayMs(10);
#endif
    }

    if ((u16CheckSum & 0xff) != 0x00)
    {
#if HDMI_MCU_DEBUG
		HDMI_MCU_ComPuts("Chk Sum Fail\n\r");
#endif
		return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S16 ExtEdidPhyAddrParse(HI_U8 *pu8CecPhyAddr, HI_U8 *pau8Data, HI_U8 u8Len)
{
	MCU_NULL_CHK_RET(pau8Data);
    MCU_NULL_CHK_RET(pu8CecPhyAddr);

	/*Byte-3~4 ,CEC Addr */
    if ( u8Len < 5 )
    {
        return HI_FAILURE;
    }

    pu8CecPhyAddr[0] = (pau8Data[EDID_CEA_PHYADDR_OFFSET] & EDID_UPPER_NIBBLE_MASK) >> 4 ;
    pu8CecPhyAddr[1] = (pau8Data[EDID_CEA_PHYADDR_OFFSET] & EDID_LOWER_NIBBLE_MASK) ;
    pu8CecPhyAddr[2] = (pau8Data[EDID_CEA_PHYADDR_OFFSET + 1] & EDID_UPPER_NIBBLE_MASK) >> 4 ;
    pu8CecPhyAddr[3] = (pau8Data[EDID_CEA_PHYADDR_OFFSET + 1] & EDID_LOWER_NIBBLE_MASK) ;

    return HI_SUCCESS;
}

static HI_S16 ExtEdidParse(HI_U8 *pu8BlkData, HI_U8 *pu8CecPhyAddr)
{
    HI_U8  	*pau8Data   = HI_NULL;
    HI_U8   u8DTDLen    = 0;
    HI_U8   u8BlkPos    = 0;
	HI_U8   u8DBOffset  = 0;
	HI_U8   u8DBTagCode = 0;
    HI_S16 	s8Ret       = HI_FAILURE;

	MCU_NULL_CHK_RET(pu8BlkData);
    MCU_NULL_CHK_RET(pu8CecPhyAddr);

    pau8Data = pu8BlkData;

    if ( HI_SUCCESS != EdidBlockChkSum(pau8Data, DDC_MAX_EDID_BUF_SIZE) )
	{
        return HI_FAILURE;
    }

	/* Byte-0 :TAG */
    if (pau8Data[0] != EDID_CEA_EXTVERSION3_TAG)
    {
#if HDMI_MCU_DEBUG
        HDMI_MCU_ComPuts("tag err!\n\r");
#endif
        return HI_FAILURE;
    }

	/* Byte-1 :REVISION */
    if (pau8Data[1] != EDID_CEA_EXTVERSION3_REVISION)
    {
#if HDMI_MCU_DEBUG
        HDMI_MCU_ComPuts("revision err!\n\r");
#endif
        return HI_FAILURE;
    }

	/* Byte-2 :DTDs Offset */
    u8DTDLen = pau8Data[2];
    if (u8DTDLen < 4)
    {
        return HI_FAILURE;
    }

	/* sevaral Data Block */
    for (u8BlkPos = 4, u8DBOffset = 0;
	     u8BlkPos < u8DTDLen;
		 u8BlkPos += u8DBOffset + 1)
    {
        u8DBOffset  =   pau8Data[u8BlkPos] & EDID_DB_LEN_MASK;
		u8DBTagCode = ( pau8Data[u8BlkPos] & EDID_DB_TAG_CODE_MASK ) >> 5;

		/* Tag Code VSDB */
        if (EDID_VENDOR_DATA_BLOCK == u8DBTagCode)
        {
			if ( u8DBOffset >= EDID_CEA_PHYADDR_OFFSET + 1 )
			{
               	s8Ret = ExtEdidPhyAddrParse(pu8CecPhyAddr, &pau8Data[u8BlkPos], u8DBOffset);
			}
            break;
        }
    }

    return s8Ret;
}

/************************* public  interface **********************************/
HI_S16 MCU_HDMI_DdcInit(HI_VOID)
{
    DDC_INFO_S *pstDdcInfo = &s_stDdcInfo;

    //if (!pstDdcInfo->bInit)
    {
        pstDdcInfo->bInit = HI_TRUE;
        pstDdcInfo->u8EdidRdStatus  = EDID_RD_EXT_CNT;
        pstDdcInfo->u8ExtEdidCnt    = 0;
    }

    return HI_SUCCESS;
}

HI_S16 MCU_HDMI_DdcDeInit(HI_VOID)
{
    DDC_INFO_S *pstDdcInfo = &s_stDdcInfo;

    DDC_INIT_CHK_RET(pstDdcInfo);

    pstDdcInfo->bInit = HI_FALSE;
    pstDdcInfo->u8EdidRdStatus  = EDID_RD_EXT_CNT;

    return HI_SUCCESS;
}

HI_S16 MCU_HDMI_DdcErrClear(HI_VOID)
{
    return HI_SUCCESS;
}

HI_S16 MCU_HDMI_DdcIssue(DDC_CFG_S *pstDdcCfg)
{
    DDC_INFO_S *pstDdcInfo    = &s_stDdcInfo;
    HI_U8       u8RdCnt       = 0;
    HI_U8       u8Time        = 0;
    HI_U8       u8FifoDataCnt = 0;
    HI_U8       *pu8RdPos     = HI_NULL;

    MCU_NULL_CHK_RET(pstDdcCfg);
    DDC_INIT_CHK_RET(pstDdcInfo);

    // TODO: cpy Cfg to DdcInfo

    // speed
    MCU_COM_CLEAR(s_u32DdcReg.u32);
    ((REG_DDC_MST_CTRL *)&s_u32DdcReg.u32)->bits.bit09_ddc_speed_cnt      = MCU_DDC_SPEED_80KHZ;
    ((REG_DDC_MST_CTRL *)&s_u32DdcReg.u32)->bits.bit01_ddc_aon_access     = HI_TRUE;
    HDMI_MCU_ComRegWrite( REG_AON_DDC_MST_CTRL, s_u32DdcReg.u32);
    // abord
    HDMI_MCU_ComDelayUs(5);
    MCU_COM_CLEAR(s_u32DdcReg.u32);
    ((REG_DDC_MST_CMD *)&s_u32DdcReg.u32)->bits.bit04_ddc_mst_cmd         = MCU_DDC_CMD_MASTER_ABORT;
    HDMI_MCU_ComRegWrite( REG_AON_DDC_MST_CMD, s_u32DdcReg.u32);
    // slave 0xa0 seg=0 offset=0
    MCU_COM_CLEAR(s_u32DdcReg.u32);
    ((REG_DDC_SLAVE_CFG *)&s_u32DdcReg.u32)->bits.bit08_ddc_slave_addr    = DDC_EDID_SALVE_ADDR;
    ((REG_DDC_SLAVE_CFG *)&s_u32DdcReg.u32)->bits.bit08_ddc_slave_offset  = pstDdcCfg->u8Offset;
    ((REG_DDC_SLAVE_CFG *)&s_u32DdcReg.u32)->bits.bit08_ddc_slave_seg     = pstDdcCfg->u8Segment;
    HDMI_MCU_ComRegWrite( REG_AON_DDC_SLAVE_CFG, s_u32DdcReg.u32);
    // cnt
    MCU_COM_CLEAR(s_u32DdcReg.u32);
    ((REG_DDC_DATA_CNT *)&s_u32DdcReg.u32)->bits.bit08_L_ddc_data_out_cnt = pstDdcCfg->u8DataSize;
    ((REG_DDC_DATA_CNT *)&s_u32DdcReg.u32)->bits.bit02_H_ddc_data_out_cnt = 0;
    HDMI_MCU_ComRegWrite( REG_AON_DDC_DATA_CNT, s_u32DdcReg.u32);
    // clr cmd
    HDMI_MCU_ComDelayUs(5);
    MCU_COM_CLEAR(s_u32DdcReg.u32);
    ((REG_DDC_MST_CMD *)&s_u32DdcReg.u32)->bits.bit04_ddc_mst_cmd         = MCU_DDC_CMD_FIFO_CLR;
    HDMI_MCU_ComRegWrite( REG_AON_DDC_MST_CMD, s_u32DdcReg.u32);
    // cmd read
    HDMI_MCU_ComDelayUs(5);
    MCU_COM_CLEAR(s_u32DdcReg.u32);
    ((REG_DDC_MST_CMD *)&s_u32DdcReg.u32)->bits.bit04_ddc_mst_cmd         = pstDdcCfg->enIssueMode;
    HDMI_MCU_ComRegWrite( REG_AON_DDC_MST_CMD, s_u32DdcReg.u32);
    // cmd data
    MCU_COM_CLEAR(s_u32DdcReg.u32);
    pu8RdPos = pstDdcCfg->pu8Data;
    for ( u8RdCnt = 0;
        u8RdCnt < pstDdcCfg->u8DataSize;
        (u8RdCnt++, MCU_COM_CLEAR(s_u32DdcReg.u32), pu8RdPos++) )
    {
        for ( u8Time = 0;
              ((u8Time < pstDdcCfg->u16IssueTimeOut) && (u8FifoDataCnt == 0));
              (u8Time++, MCU_COM_CLEAR(s_u32DdcReg.u32)) )
        {
            /* when read-fifo empty,every byte wait a max timeout */
            HDMI_MCU_ComDelayUs(100);
            s_u32DdcReg.u32 = HDMI_MCU_ComRegRead( REG_AON_DDC_DATA_CNT);
            u8FifoDataCnt = ((REG_DDC_DATA_CNT *)&s_u32DdcReg.u32)->bits.bit05_ddc_fifo_data_cnt;
        }
        if (u8Time >= pstDdcCfg->u16IssueTimeOut)
        {
#if HDMI_MCU_DEBUG
            HDMI_MCU_ComPuts("ddc time out");
#endif
            return HI_FAILURE;
        }
        else
        {
            s_u32DdcReg.u32 = HDMI_MCU_ComRegRead( REG_AON_DDC_FIFO_RDATA);
            *pu8RdPos = ((REG_DDC_FIFO_RDATA *)&s_u32DdcReg.u32)->bits.bit08_ddc_fifo_data_out;
            HDMI_MCU_ComDelayMs(1);
        }
    }

    return HI_SUCCESS;
}

HI_S16 MCU_HDMI_DdcDefaultCfgGet(DDC_CFG_S *pstCfg)
{
    MCU_NULL_CHK_RET(pstCfg);

    pstCfg->u8Segment        = 0;
    pstCfg->u8Offset         = 0;
    pstCfg->enIssueMode      = DDC_MODE_READ_MUTIL_NO_ACK;

    pstCfg->u16InProgTimeOut = DDC_DEFAULT_TIMEOUT_IN_PROG;
    pstCfg->u16SclTimeOut    = DDC_DEFAULT_TIMEOUT_SCL;
    pstCfg->u16SdaTimeOut    = DDC_DEFAULT_TIMEOUT_SDA;
    pstCfg->u16IssueTimeOut  = DDC_DEFAULT_TIMEOUT_ISSUE;

    pstCfg->u8DataSize       = 0;
    pstCfg->pu8Data          = HI_NULL;

    return HI_SUCCESS;
}

HI_S16 MCU_HDMI_DdcEdidCecAddrGet(HI_U8 *pu8CecPhyAddr, HI_U8 u8Size)
{
    HI_U8           u8ExtBlockNum = 0, i=0;
    HI_S16          s16Ret = HI_FAILURE;
    DDC_CFG_S       stCfg  = {0};
    DDC_INFO_S      *pstDdcInfo = &s_stDdcInfo;

    DDC_INIT_CHK_RET(pstDdcInfo);
    MCU_NULL_CHK_RET(pu8CecPhyAddr);

    if (u8Size != EDID_CEA_PHYADDR_OFFSET)
    {
#if HDMI_MCU_DEBUG
        HDMI_MCU_ComPuts("phyAddr len err!\n\r");
#endif
        return HI_FAILURE;
    }

    MCU_HDMI_DdcDefaultCfgGet(&stCfg);

    switch (pstDdcInfo->u8EdidRdStatus)
    {
        case EDID_RD_EXT_CNT:
            stCfg.u8Offset    = DDC_EXT_BLOCK_OFFSET;
            stCfg.enIssueMode = DDC_MODE_READ_MUTIL_NO_ACK;
            stCfg.u8DataSize  = 1;
            stCfg.pu8Data     = &pstDdcInfo->u8ExtEdidCnt;
            if (HI_SUCCESS == MCU_HDMI_DdcIssue(&stCfg))
            {
                if (pstDdcInfo->u8ExtEdidCnt)
                {
                    pstDdcInfo->u8EdidRdStatus = EDID_RD_EXT_EDID_0;
                }
                else
                {
                    pstDdcInfo->u8EdidRdStatus = EDID_RD_NO_PHYADDR;
                }
            }
            else
            {
                pstDdcInfo->u8EdidRdStatus = EDID_RD_ERR;
            }
            break;
        case EDID_RD_EXT_EDID_0:
            stCfg.u8Offset    = DDC_MAX_EDID_BUF_SIZE;
            stCfg.enIssueMode = DDC_MODE_READ_MUTIL_NO_ACK;
            stCfg.u8DataSize  = DDC_MAX_EDID_BUF_SIZE;
            stCfg.pu8Data     = &s_au8Edid[0];
            if (HI_SUCCESS == MCU_HDMI_DdcIssue(&stCfg))
            {
                if (HI_SUCCESS == ExtEdidParse(stCfg.pu8Data, pu8CecPhyAddr))
                {
                    pstDdcInfo->u8EdidRdStatus = EDID_RD_EXT_CNT;
                    s16Ret = HI_SUCCESS;
                }
                else
                {
                    pstDdcInfo->u8ExtEdidCnt--;
                    pstDdcInfo->u8EdidRdStatus = EDID_RD_EXT_EDID_1_2;
                }
            }
            else
            {
                pstDdcInfo->u8EdidRdStatus = EDID_RD_ERR;
            }
            break;
        case EDID_RD_EXT_EDID_1_2:
            stCfg.u8Segment   = 1;
            stCfg.enIssueMode = DDC_MODE_READ_SEGMENT_NO_ACK;
            stCfg.u8DataSize  = DDC_MAX_EDID_BUF_SIZE;
            stCfg.pu8Data     = &s_au8Edid[0];
            for ( i = 0; (i<2) && pstDdcInfo->u8ExtEdidCnt; i++ )
            {
                stCfg.u8Offset = i * DDC_MAX_EDID_BUF_SIZE;
                if (HI_SUCCESS == MCU_HDMI_DdcIssue(&stCfg))
                {
                    if (HI_SUCCESS == ExtEdidParse(stCfg.pu8Data, pu8CecPhyAddr))
                    {
                        pstDdcInfo->u8EdidRdStatus = EDID_RD_EXT_CNT;
                        s16Ret = HI_SUCCESS;
                        break;
                    }
                    else
                    {
                        pstDdcInfo->u8ExtEdidCnt--;
                    }
                }
                else
                {
                    pstDdcInfo->u8EdidRdStatus = EDID_RD_ERR;
                    break;
                }
            }
            pstDdcInfo->u8EdidRdStatus  = EDID_RD_NO_PHYADDR;
            break;
        case EDID_RD_ERR:
#if HDMI_MCU_DEBUG
            HDMI_MCU_ComPuts("ddc rd err!\n\r");
#endif
            // no break;
        case EDID_RD_NO_PHYADDR:
            /* set default phyaddr */
            pu8CecPhyAddr[0] = 0x1;
            pu8CecPhyAddr[1] = 0x0;
            pu8CecPhyAddr[2] = 0x0;
            pu8CecPhyAddr[3] = 0x0;
            pstDdcInfo->u8EdidRdStatus = EDID_RD_EXT_CNT;
            s16Ret = HI_SUCCESS;
#if HDMI_MCU_DEBUG
            HDMI_MCU_ComPuts("phy default!\n\r");
#endif
            break;
        default:
            break;
    }

    return s16Ret;
}

/************************* end of file ****************************************/

