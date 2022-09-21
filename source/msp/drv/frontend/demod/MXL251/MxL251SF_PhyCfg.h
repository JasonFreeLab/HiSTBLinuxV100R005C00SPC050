/*****************************************************************************************
 *
 * FILE NAME          : MxL251SF_PhyCfg.h
 * 
 * AUTHOR             : Brenndon Lee
 *                      Sunghoon Park
 *                      Dong Liu
 *                      Jun Huang
 *
 * DATE CREATED       : 05/18/2009
 *                      07/06/2010
 *                      08/19/2010 
 *                      06/18/2011
 *
 * DESCRIPTION        : This file contains MxL251SF common control register 
 *                      definitions
 *
 *****************************************************************************************
 *                Copyright (c) 2006, MaxLinear, Inc.
*****************************************************************************************/

#ifndef __MXL251SF_PHY_CFG_H__
#define __MXL251SF_PHY_CFG_H__

/*****************************************************************************************
    Include Header Files
    (No absolute paths - paths handled by make file)
*****************************************************************************************/
#include "MaxLinearDataTypes.h"
#include "MxL251SF_PhyCtrlApi.h"
#include "MxL251SF_OEM_Drv.h"
#include "MxL251SF_NVRAMFile.h"
#include "MxL_Debug.h"

/*****************************************************************************************
    Macros
*****************************************************************************************/
/*Beware of overflow while using below!!!
  Depending upon the x & fraction, the result may overflow UINT32 data type.
  Take care while using the resulting scaled number in multiplication it might lead to overflow.  */

#define MXL_MUL(x,y,fraction)		      (((x)*(y) + (1 << (fraction - 1))) >> (fraction))
#define MXL_MUL64(x,y,fraction)		      (((UINT64)(x)*(y) + (1 << (fraction - 1))) >> (fraction))
#define MXL_MUL_S(x,y,fraction)			  (((x)*(y)) + ((((x)*(y))<0)?1:-1)*(1 << ((fraction) - 1))) >> (fraction)
#define MXL_MUL64_S(x,y,fraction)		  (((SINT64)(x)*(y)) + ((((SINT64)(x)*(y))<0)?1:-1)*(1 << ((fraction) - 1))) >> (fraction)
#define MXL_REAL32_TO_HEX32(x,fraction)   ((UINT32)((x)  * (1 <<	fraction) + 0.5))
#define MXL_HEX_TO_REAL32(x,fraction)	  ((REAL32)((x) / (REAL32)(1 << (fraction))))
#define MXL_REAL32_TO_HEX64(x,fraction)   ((UINT64)(((REAL64)(x))  * (1 << fraction) + 0.5))
#define MXL_REAL64_TO_HEX64(x,fraction)   ((UINT64)(((REAL64)(x))  * (1 << fraction) + 0.5))
#define MXL_HEX64_TO_REAL64(x,fraction)	  ((REAL64)((UINT64)(x) / (REAL32)(1 << (fraction))))

/* Use below if the result of division is NOT desired in the scaled format */
#define MXL_DIV(x, y)				      (((y)!=0)?(((x) + ((y)/2)) / (y)):0)
#define MXL_DIV_S(x, y)				      (((y)!=0)?(((x) + ((((x)>=0)?1:-1)*(y)/2)) / (y)):0) // MXL_DIV_ROUND_S round div operation - use only for signed types
#define MXL_DIV64(x, y)   (  \
        {  \
        UINT64 out = 0; \
        UINT64 x_1 = (UINT64) x; \
        UINT32 y_1 = (UINT32) y; \
        if (y) \
        { \
        out = do_div(x_1,y_1); \
        } \
        x_1; \
        } \
        )

#define MXL_DIV64_S(x, y)  (                                               \
        {                                                                  \
        UINT64 out = 0;                                                    \
        UINT64 x_1;                                                        \
        UINT32 y_1;                                                        \
        SINT64 q_1;                                                        \
        if ((x) < 0) x_1 = (UINT64)(-(SINT64)(x)); else x_1 = (UINT64) x; \
        if ((y) < 0) y_1 = (UINT32)(-(SINT32)(y)); else y_1 = (UINT32) y; \
        if (y_1)                                                           \
        {                                                                  \
        out = do_div(x_1,y_1);                                             \
        }                                                                  \
        q_1 = (SINT64)x_1;                                                 \
        if ((x) < 0) q_1 = -q_1;                                           \
        if ((y) < 0) q_1 = -q_1;                                           \
        q_1;                                                               \
        }                                                                  \
        )

/* Use scaled division if the scaled up result is desired */
#define MXL_DIV_SCALE(x, y,fraction)	  (((y)!=0)?((((x) << (fraction)) + ((y)/2)) / (y)):0)
#define MXL_DIV_SCALE_S(x, y,fraction)	  (((y)!=0)?((((x) << (fraction)) + ((((x)>=0)?1:-1)*(y)/2)) / (y)):0) // use only for signed types
#define MXL_DIV_SCALE64(x, y,fraction)	( \
        {  \
        UINT64 out = 0; \
        UINT64 x_1 = (UINT64) x << (fraction); \
        UINT32 y_1 = (UINT32) y; \
        if (y) \
        { \
        out = do_div(x_1,y_1); \
        } \
        x_1; \
        } \
        )
#define MXL_DIV_SCALE64_S(x, y,fraction) (                                 \
        {                                                                  \
        UINT64 out = 0;                                                    \
        UINT64 x_1;                                                        \
        UINT32 y_1;                                                        \
        SINT64 q_1;                                                        \
        if ((x) < 0) x_1 = (UINT64)(-(SINT64)(x)); else x_1 = (UINT64) x;  \
        if ((y) < 0) y_1 = (UINT32)(-(SINT32)(y)); else y_1 = (UINT32) y;  \
        x_1 = x_1 << fraction;                                             \
        if (y_1)                                                           \
        {                                                                  \
        out = do_div(x_1,y_1);                                             \
        }                                                                  \
        q_1 = (SINT64)x_1;                                                 \
        if ((x) < 0) q_1 = -q_1;                                           \
        if ((y) < 0) q_1 = -q_1;                                           \
        q_1;                                                               \
        }                                                                  \
        )

#ifdef  _MXL251_FIXEDPOINT_
#define MXL_VAL(x)						  MXL_HEX_TO_REAL32(x, MXL251_PRECISION)
#define MXL_VAL64(x)					  ((x>0) ? ((REAL32)((UINT64)(x) / (REAL32)(1 << (MXL251_PRECISION)))): ((REAL32)((SINT64)(x) / (REAL32)(1 << (MXL251_PRECISION)))))
#define MXL_SCALEUP(x, shift)			  ((x) * (1 << shift))
#define MXL_SCALEUP64(x, shift)			  (((UINT64)x)* (1 << shift))
#define MXL_SCALEUP64_S(x, shift)		  (((SINT64)x)* (1 << shift)) //use when the result can go beyond 32 bits
#define MXL_SCALEDOWN(x, shift)		      ((x) >> (shift))
#define MXL_SCALEDOWN64(x, shift)		  ((UINT64)(x) >> (shift)) //use when the integer argument is > 32 bits
#else
#define MXL_VAL(x)            (x)
#endif

#define CW_COUNT                            0
#define CW_CORR_COUNT                       1
#define CW_ERR_COUNT                        2
#define CORR_BITS                           3

#define VERSION_REG                         0x0017

#define SLEEP_MODE_CTRL_REG                 0x0002
#define ENABLE_SLEEP                        0x0001
#define DISABLE_SLEEP                       0x0000

#define XTAL_CLK_OUT_CTRL_REG               0x0000
#define ENABLE_CLK_OUT                      0x10

#define DIG_XTAL_FREQ_CTRL_REG              0x0003
#define ENABLE_XTAL                         0x10

#define DIG_XTAL_CAP_CTRL_REG               0x0004
#define DIG_XTAL_BIAS_CTRL_REG              0x00BC

#define LOOP_THROUGH_CTRL_REG               0x0006
#define ENABLE_LOOP_THRU                    0x0020

#define WB_96MHZ_BYTE                       0x03 
#define WB_48MHZ_BYTE                       0x02 
#define WB_16MHZ_BYTE                       0x01 

#define DFE_WB_DIG_GAIN_REG                 0x4274
#define WB_TUNER0_DIG_GAIN_WORD             0x0001 
#define WB_TUNER1_DIG_GAIN_WORD             0x0002 

#define DIG_ANA_ADC0_BW_REG                 0x2004 
#define DIG_ANA_ADC1_BW_REG                 0x3004 
#define DIG_ANA_ADC_BW_MASK                 0xC000 // Bit<15:14> 

#define DIG_ANA_TUNER0_BW_REG               0x20C4 
#define DIG_ANA_TUNER1_BW_REG               0x3064
#define DIG_ANA_TUNER_BW_MASK               0x0030 // Bit<5:4>  

#define DIG_ANA_DNX0_LNA_BIAS_REG           0x2020
#define DIG_ANA_DNX1_LNA_BIAS_REG           0x3018
#define DIG_ANA_DNXx_LNA_BIAS_LOWPOWER_MASK 0x0004

#define DIG_ANA_DNX0_TZ_BW_BIAS_REG         0x202C
#define DIG_ANA_DNX1_TZ_BW_BIAS_REG         0x3024
#define DIG_ANA_DNXx_TZ_BW_BIAS_MASK        0x0300
#define DIG_ANA_DNXx_TZ_BW_BIAS_LSB         0x0008

#define DIG_ANA_DNX0_SPARE_REG              0x202C
#define DIG_ANA_DNX0_SPARE_RFRSSI_STROBE_MASK (1<<7)

#define DIG_ANA_CLKOUT_ENA_REG              0x2014
#define DIG_ANA_CLKOUT_ENA_MASK             (1<<8)

#define SYMBOL_RATE_RESAMP_BANK_REG         0x6100 
#define SYMBOL_RATE_RESAMP_RATE_LO_REG      0x610C 
#define SYMBOL_RATE_RESAMP_RATE_HI_REG      0x6108 
#define SYM_NUM_B_BANK                      2
#define BYPASS_INTERPOLATOR                 0x0010

#define DIG_HALT_GAIN_CTRL_REG              0x6015
#define FREEZE_AGC_GAIN_WORD                0x6008

#define DIG_AGC_SETPT_CTRL_LO_REG           0x602D
#define DIG_AGC_SETPT_CTRL_HI_REG           0x602E

#define MPEG_SYNC_CONTROL_REG               0x6288
#define MPEG_SYNC_CONTROL_ANNEXA            0xFF95
#define MPEG_SYNC_CONTROL_ANNEXB            0x5F92

#define STAMP_REG                           0x6290
#define MCNSSD_SEL_REG                      0x62B4 
#define MCNSSD_REG                          0x62B8 

#define NCBL_REG                            0x62A8
#define NCBH_REG                            0x62A4

#define FRCNT_REG                           0x629C
#define MEF_REG                             0x62A0

#define ANNEX_A_TYPE                        0x0400
#define QAM_TYPE                            0x0007
#define ENABLE_AUTO_DETECT_QAM_TYPE         0x8000
#define ENABLE_AUTO_DETECT_MODE             0x4000

#define QAM_LOCK_STATUS_REG                 0x6038  
#define FEC_MPEG_LOCK_REG                   0x628C

#define DIG_ADCIQ_FLIP_REG                  0x003C
#define DEMOD0_IQ_FLIP                      0x0800

#define QAM_ANNEX_TYPE_REG                  0x6004
#define QAM_TYPE_AUTO_DETECT_REG            0x6014 

#define SNR_MSE_AVG_COEF_REG                0x60D8
#define SNR_EXT_SPACE_ADDR_REG              0x60F8
#define SNR_EXT_SPACE_DATA_REG              0x60FC
#define MSE_AVG_COEF                        0xD800

#define MPEGOUT_CLK_CTRL_REG                0x0028
#define MPEGOUT_EXT_MPEGCLK_INV_REG         0x000E

#define MPEGOUT_SER_CTRL_REG                0x63C8

#define MPEGOUT_ERROR_IND_REG               0x6280
#define ENABLE_MPEG_ERROR_IND               0x0200

#define EQ_SPUR_BYPASS_REG                  0x60BC
#define CARRIER_OFFSET_REG                  0x60F8

#define EQUALIZER_FILTER_REG                0x60F8
#define EQUALIZER_EXT_SPACE_DATA_REG        0x60FC

#define RF_CHAN_BW_REG                      0x6040
#define RF_LOW_REG                          0x0011
#define RF_HIGH_REG                         0x0012
#define RF_SEQUENCER_REG                    0x0013
#define STOP_TUNE                           0x0000
#define START_TUNE                          0x0001

#define RF_WB_TUNER0_STATUS_REG             0x20F4
#define RF_WB_TUNER1_STATUS_REG             0x3078
#define RF_WB_SYN_LOCK                      0x1000

#define RF_WB_TUNER_AGC_LOCK_STATUS_REG     0x4274
#define RF_WB_TUNER0_AGC_LOCK               0x0001
#define RF_WB_TUNER1_AGC_LOCK               0x0002

#define RF_PIN_RB_EN_REG                    0x0014
#define ENABLE_RFPIN_RB                     0x0001

#define DIG_RF_PIN_RB_LO_REG                0x0018
#define DIG_RF_PIN_RB_HI_REG                0x0019
 
#define INTERLEAVER_DEPTH_REG               0x628C

#define EQU_FREQ_SWEEP_LIMIT_REG            0x6084

#define CARRIER_OFFSET_RB_REG               0x60FC
#define FREEZE_AGC_CFG_REG                  0x0015

#define DEMOD0_INTR_MASK_REG                0x63CC
#define DEMOD1_INTR_MASK_REG                0x73CC
#define DEMOD2_INTR_MASK_REG                0x83CC
#define DEMOD3_INTR_MASK_REG                0x93CC

#define INTR_MASK_REG                       0x63CC
#define INTR_STATUS_REG                     0x63D0
#define INTR_CLEAR_REG                      0x63D0
#define ENABLE_DEMOD_INT                    0x6000
#define DEMOD_RESTART_REG                   0x63FC

#define RESAMP_BANK_REG                     0x6100

#define RATE_RESAMP_RATE_MID_LO_REG         0x610C
#define RATE_RESAMP_RATE_MID_HI_REG         0x6108

#define GODARD_ACC_REG                      0x612C

#define DIG_AGC_SELECT                      0x002B
#define DIG_TESTIF_OBV_MODE                 0x00BE

#define ENABLE_TEMP_SENSOR_REG              0x0014
#define TEMP_SENSOR_RB_REG                  0x0019

#define DEMOD_AGC_SET_POINT_REG             0x6134

#define PHY_EQUALIZER_FFE_FILTER_REGISTER   0x8026
#define PHY_EQUALIZER_DFE_FILTER_REGISTER   0x8027

#define PHY_EQUALIZER_LLP_CONTROL_1_DEBUG_MSE_REGISTER 0x60D8

#define SYMBOL_RATE_RATE_LO_REG_RB          0x6024
#define SYMBOL_RATE_RATE_HI_REG_RB          0x6030

#define AGC_CTRL_SPEED_REG                  0x0031
#define FAST_AGC_CTRL_LOCK                  0x0010
#define NORMAL_AGC_CTRL_LOCK                0x0002

#define XTAL_EN_VCO_BIASBST                 0x00BD
#define DIG_TEMP_RB                         0x0019
#define TEMP_THRESHOLD                      0x8

#define DN_LNA_BIAS_CTRL_REG                0x0099 

#define COMMAND_HEADER_LENGTH               4

#define HOST_COMMAND_SYNC_IND               0xE0

#define MBIN_FORMAT_VERSION                 '1'
#define MBIN_FILE_HEADER_ID                 'M'
#define MBIN_SEGMENT_HEADER_ID              'S'
#define MBIN_MAX_FILE_LENGTH                (1<<23)

#define INVALID_CHAN_ID                     0xFF
#define INVALID_ANNEX_QAM                   0xFF

// Following macro is used to populate Host command header that goes to MxL251SF along with payload */
#define FORM_CMD_HEADER(Header, id, seqNum, len)  Header.syncChar = HOST_COMMAND_SYNC_IND + (seqNum % 0x0F); \
                                                  Header.commandId = id;  \
                                                  Header.payloadLen = (UINT8)len

#define DFE_XBAR_CHAN_CFG_REG         0x4080
#define DFE_CHN_XBAR_SEL_BIT(chanId)  (1<<((chanId)+8))
#define DFE_CHN_ENA_BIT(chanId)       (1<<(chanId))
#define DFE_CHN_ENA_ALL_MASK          0xFF

#define DFE_FREQ_OFFSET_CFG_REG       0x4084 // bit15-0
#define DFE_BANDWIDTH_CFG_REG         0x40A4 // bit15-8

#define DFE_DAGCx_SETPT_REG(chanId)   (0x51B8 + (chanId)*4) // bit9-0

// #define DFE4_IF_OUT_FREQ_CFG_REG      0x5010 // bit7-0
// #define DFE5_IF_OUT_FREQ_CFG_REG      0x5010 // bit15-8
// #define DFE6_IF_OUT_FREQ_CFG_REG      0x5014 // bit7-0
// #define DFE7_IF_OUT_FREQ_CFG_REG      0x5014 // bit15-8
#define DFE_UPXx_DDFSWORD_REG(ifChanId) (((ifChanId)<=5)?0x5010:0x5014) // ifChanId from 4 to 7
#define DFE_UPXx_DDFSWORD_LSB(ifChanId) (((ifChanId)&1)?8:0)


#define DFE_UPXx_NEGATEQ_REG          0x500c
#define DFE_UPXx_NEGATEQ_BIT(ifChanId) (1<<((ifChanId)+2)) // ifChanId from 4 to 7

#define DFE_DAGC0_RSSI_RB_REG     0x5298  // bit 11:0
#define DFE_DAGC1_RSSI_RB_REG     0x529C  // bit 11:0
#define DFE_DAGC2_RSSI_RB_REG     0x52A0  // bit 11:0
#define DFE_DAGC3_RSSI_RB_REG     0x52A4  // bit 11:0
#define DFE_DAGC4_RSSI_RB_REG     0x52A8  // bit 11:0
#define DFE_DAGC5_RSSI_RB_REG     0x52AC  // bit 11:0
#define DFE_DAGC6_RSSI_RB_REG     0x52B0  // bit 11:0
#define DFE_DAGC7_RSSI_RB_REG     0x52B4  // bit 11:0

#define DFE_WBVGAx_GAIN_REG       0x5274  // bit 7-0: tuner0, bit 15-8: tuner 1

#define DEMOD0_CUSTOM_COEF_ENA_CFG_REG      0x6100 // bit 14
#define DEMOD0_CUSTOM_COEF_DATA_CFG_REG     0x611C // bit 12 - 0
#define DEMOD0_CUSTOM_COEF_ADDR_CFG_REG     0x6118 // bit 5-0
#define DEMOD0_CUSTOM_COEF_AUTO_INC_CFG_REG 0x6118 // bit 15

#define DFE_ADC_BW_REG                      0x4280
#define DFE_UPX_CH_ENAx_REG                 0x5020 
#define DFE_UPX_CH_ENAx_BIT(ifChanId)       (1<<((ifChanId)+7)) // ifChanId from 4 to 7
#define DFE_UPX_CLK_ENAx_REG                0x5024 
#define DFE_UPX_CLK_ENAx_BIT(ifChanId)      (1<<((ifChanId)-2)) // ifChanId from 4 to 7
#define DFE_UPX_CIC_SHIFT_REG               0x530C

#define MAX_NUM_IF_OUT              2
#define DFE_IF_BASE                 4

#define DFE_RESET_REG               0x0024
#define DFE_RESETN_MASK             0x0001

#define DEMOD0_RESET_REG            0x008C
#define DMD0_RESET_MASK             0x8000
#define DEMOD1_RESET_REG            0x0090
#define DMD1_RESET_MASK             0x0080
#define DEMOD2_RESET_REG            0x0090
#define DMD2_RESET_MASK             0x8000
#define DEMOD3_RESET_REG            0x0094
#define DMD3_RESET_MASK             0x0080

#define DEMOD0_CLK_EN_REG           0x0090
#define DMD0_MCLK_EN_MASK           0x0010
#define DMD0_CLK_X4_EN              0x0008
#define DMD0_CLK_X2_EN              0x0004
#define DMD0_INV_SYNC_CLK_X1        0x0002
#define DMD0_CLK_X1_EN              0x0001

#define DEMOD1_CLK_EN_REG           0x0090
#define DMD1_MCLK_EN_MASK           0x1000
#define DMD1_CLK_X4_EN              0x0800
#define DMD1_CLK_X2_EN              0x0400
#define DMD1_INV_SYNC_CLK_X1        0x0200
#define DMD1_CLK_X1_EN              0x0100

#define DEMOD2_CLK_EN_REG           0x0094
#define DMD2_MCLK_EN_MASK           0x0010
#define DMD2_CLK_X4_EN              0x0008
#define DMD2_CLK_X2_EN              0x0004
#define DMD2_INV_SYNC_CLK_X1        0x0002
#define DMD2_CLK_X1_EN              0x0001

#define DEMOD3_CLK_EN_REG           0x0094
#define DMD3_MCLK_EN_MASK           0x1000
#define DMD3_CLK_X4_EN              0x0800
#define DMD3_CLK_X2_EN              0x0400
#define DMD3_INV_SYNC_CLK_X1        0x0200
#define DMD3_CLK_X1_EN              0x0100

#define DEMOD0_MDVAL_GATE_EN_REG    0x0090
#define DEMOD0_MDVAL_GATE_EN_MASK   0x0020
#define DEMOD1_MDVAL_GATE_EN_REG    0x0090
#define DEMOD1_MDVAL_GATE_EN_MASK   0x2000
#define DEMOD2_MDVAL_GATE_EN_REG    0x0094
#define DEMOD2_MDVAL_GATE_EN_MASK   0x0020
#define DEMOD3_MDVAL_GATE_EN_REG    0x0094
#define DEMOD3_MDVAL_GATE_EN_MASK   0x2000

#define PAD_MPSYN_0_DRV_REG         0x002C
#define PAD_MPSYN_0_DRV_MASK        0x7000

#define PAD_MCLK_DRV_REG            0x002C
#define PAD_MCLK_DRV_MASK           0x0700
#define PAD_MCLK_DRV_SHIFT_BITS     8

#define PAD_MPVAL_1_DRV_REG         0x0030
#define PAD_MPVAL_1_DRV_MASK        0x7000

#define PAD_MPSYN_1_DRV_REG         0x0030
#define PAD_MPSYN_1_DRV_MASK        0x0700

#define PAD_MDAT_0_DRV_REG          0x0030
#define PAD_MDAT_0_DRV_MASK         0x0070

#define PAD_MPVAL_0_DRV_REG         0x0030
#define PAD_MPVAL_0_DRV_MASK        0x0007

#define PAD_MDAT_2_DRV_REG          0x0034
#define PAD_MDAT_2_DRV_MASK         0x7000

#define PAD_MPVAL_2_DRV_REG         0x0034
#define PAD_MPVAL_2_DRV_MASK        0x0700

#define PAD_MPSYN_2_DRV_REG         0x0034
#define PAD_MPSYN_2_DRV_MASK        0x0070

#define PAD_MDAT_1_DRV_REG          0x0034
#define PAD_MDAT_1_DRV_MASK         0x0007

#define PAD_MDAT_3_DRV_REG          0x0038
#define PAD_MDAT_3_DRV_MASK         0x0700

#define PAD_MPVAL_3_DRV_REG         0x0038
#define PAD_MPVAL_3_DRV_MASK        0x0070

#define PAD_MPSYN_3_DRV_REG         0x0038
#define PAD_MPSYN_3_DRV_MASK        0x0007

#define MPEGx_OPEN_REG              0x003C
#define MPEGx_OPEN_MASK(chanId)     (0x0080<<chanId)

#define OOBx_OEN_REG                0x00A4
#define OOBx_OEN_MASK(chanId)       (2<<chanId)

#define DFE_CDC0_OFFSET_TZ_BYP_REG  0x4030
#define DFE_CDC0_OFFSET_TZ_BYP_MASK 0xFF00

#define DFE_CDC0_OFFSET_TZ0_BYP_VAL_REG  0x4020
#define DFE_CDC0_OFFSET_TZ0_BYP_VAL_MASK 0x3F00

#define DFE_CDC0_OFFSET_TZ1_BYP_VAL_REG  0x4024
#define DFE_CDC0_OFFSET_TZ1_BYP_VAL_MASK 0x003F

#define DFE_CDC0_OFFSET_TZ2_BYP_VAL_REG  0x4024
#define DFE_CDC0_OFFSET_TZ2_BYP_VAL_MASK 0x3F00

#define DFE_CDC0_OFFSET_TZ3_BYP_VAL_REG  0x4028
#define DFE_CDC0_OFFSET_TZ3_BYP_VAL_MASK 0x003F

#define DFE_CDC0_OFFSET_TZ4_BYP_VAL_REG  0x4028
#define DFE_CDC0_OFFSET_TZ4_BYP_VAL_MASK 0x3F00

#define DFE_CDC0_OFFSET_TZ5_BYP_VAL_REG  0x402C
#define DFE_CDC0_OFFSET_TZ5_BYP_VAL_MASK 0x003F

#define DFE_CDC0_OFFSET_TZ6_BYP_VAL_REG  0x402C
#define DFE_CDC0_OFFSET_TZ6_BYP_VAL_MASK 0x3F00

#define DFE_CDC0_OFFSET_TZ7_BYP_VAL_REG  0x4030
#define DFE_CDC0_OFFSET_TZ7_BYP_VAL_MASK 0x003F


#define DFE_CDC1_OFFSET_TZ_BYP_REG  0x4060
#define DFE_CDC1_OFFSET_TZ_BYP_MASK 0xFF00

#define DFE_CDC1_OFFSET_TZ0_BYP_VAL_REG  0x4050
#define DFE_CDC1_OFFSET_TZ0_BYP_VAL_MASK 0x3F00

#define DFE_CDC1_OFFSET_TZ1_BYP_VAL_REG  0x4054
#define DFE_CDC1_OFFSET_TZ1_BYP_VAL_MASK 0x003F

#define DFE_CDC1_OFFSET_TZ2_BYP_VAL_REG  0x4054
#define DFE_CDC1_OFFSET_TZ2_BYP_VAL_MASK 0x3F00

#define DFE_CDC1_OFFSET_TZ3_BYP_VAL_REG  0x4058
#define DFE_CDC1_OFFSET_TZ3_BYP_VAL_MASK 0x003F

#define DFE_CDC1_OFFSET_TZ4_BYP_VAL_REG  0x4058
#define DFE_CDC1_OFFSET_TZ4_BYP_VAL_MASK 0x3F00

#define DFE_CDC1_OFFSET_TZ5_BYP_VAL_REG  0x405C
#define DFE_CDC1_OFFSET_TZ5_BYP_VAL_MASK 0x003F

#define DFE_CDC1_OFFSET_TZ6_BYP_VAL_REG  0x405C
#define DFE_CDC1_OFFSET_TZ6_BYP_VAL_MASK 0x3F00

#define DFE_CDC1_OFFSET_TZ7_BYP_VAL_REG  0x4060
#define DFE_CDC1_OFFSET_TZ7_BYP_VAL_MASK 0x003F

#define DIG_ANA_REFSX_AMP_REGDIG_REG     0x2044
#define DIG_ANA_REFSX_AMP_REGDIG_MASK    0x0070
#define DIG_ANA_REFSX_AMP_REGDIG_SHIFT_BITS 4

#define DIG_ANA_MISC_SPARE_REG           0x2040
#define DIG_ANA_MISC_SPARE_MASK          0xFF00
#define DIG_ANA_MISC_SPARE_SHIFT_BITS    8

#define DIG_ANA_DNX0_LNA_ENA_REG         0x2020
#define DIG_ANA_DNX0_LNA_ENA_MASK        0x0008
#define DIG_ANA_DNX0_LNA_ENA_SHIFT_BITS  3

#define DIG_ANA_DNX1_LNA_ENA_REG         0x3018
#define DIG_ANA_DNX1_LNA_ENA_MASK        0x0008
#define DIG_ANA_DNX1_LNA_ENA_SHIFT_BITS  3

#define DIG_ANA_DNX0_LNA_SPARE_REG         0x2020
#define DIG_ANA_DNX0_LNA_SPARE_STROBE_MASK (1<<9)

#define DIG_ANA_DNX1_LNA_SPARE_REG         0x3018
#define DIG_ANA_DNX1_LNA_SPARE_STROBE_MASK (1<<9)

#define DIG_ANA_ADC0_RESETB_REG          0x200C
#define DIG_ANA_ADC0_RESETB_MASK         0x0800
#define DIG_ANA_ADC0_RESETB_SHIFT_BITS   11

#define DIG_ANA_ADC1_RESETB_REG          0x300C
#define DIG_ANA_ADC1_RESETB_MASK         0x0800
#define DIG_ANA_ADC1_RESETB_SHIFT_BITS   11

#define DIG_ANA_DAC_RESETB_REG           0x2018
#define DIG_ANA_DAC_RESETB_MASK          0x0200
#define DIG_ANA_DAC_RESETB_SHIFT_BITS    9

#define DIG_ANA_ADC0_BIAS_REG            0x2004
#define DIG_ANA_ADC0_BIAS_MASK           0x3000
#define DIG_ANA_ADC0_BIAS_SHIFT_BITS     12

#define DIG_ANA_ADC0_VCMI_REG            0x2010
#define DIG_ANA_ADC0_VCMI_MASK           0x000C
#define DIG_ANA_ADC0_VCMI_SHIFT_BITS     2


#define DIG_ANA_ADC0_VREF_REG            0x2010
#define DIG_ANA_ADC0_VREF_MASK           0x0030
#define DIG_ANA_ADC0_VREF_SHIFT_BITS     4

#define DIG_ANA_ADC0_SPARE_REG           0x200C
#define DIG_ANA_ADC0_SPARE_MASK          0xF000
#define DIG_ANA_ADC0_SPARE_SHIFT_BITS    12

#define DIG_ANA_ADC1_BIAS_REG            0x3004
#define DIG_ANA_ADC1_BIAS_MASK           0x3000
#define DIG_ANA_ADC1_BIAS_SHIFT_BITS     12

#define DIG_ANA_ADC1_VCMI_REG            0x3010
#define DIG_ANA_ADC1_VCMI_MASK           0x000C
#define DIG_ANA_ADC1_VCMI_SHIFT_BITS     2

#define DIG_ANA_ADC1_VREF_REG            0x3010
#define DIG_ANA_ADC1_VREF_MASK           0x0030
#define DIG_ANA_ADC1_VREF_SHIFT_BITS     4

#define DIG_ANA_ADC1_SPARE_REG           0x300C
#define DIG_ANA_ADC1_SPARE_MASK          0xF000
#define DIG_ANA_ADC1_SPARE_SHIFT_BITS    12

#define DFE_CDC0_OFFSET_TZ_FLIP_REG        0x4034
#define DFE_CDC0_OFFSET_TZ_FLIP_MASK       0x00FF
#define DFE_CDC0_OFFSET_TZ_FLIP_SHIFT_BITS 0


#define DFE_CDC1_OFFSET_TZ_FLIP_REG      0x4064
#define DFE_CDC1_OFFSET_TZ_FLIP_MASK     0x00FF
#define DFE_CDC1_OFFSET_TZ_FLIP_SHIFT_BITS 0

#define DIG_ANA_DNX0_RCTUNE_REG          0x2028
#define DIG_ANA_DNX0_RCTUNE_MASK         0x000F
#define DIG_ANA_DNX0_RCTUNE_SHIFT_BITS   0

#define DIG_ANA_DNX1_RCTUNE_REG          0x3020
#define DIG_ANA_DNX1_RCTUNE_MASK         0x000F
#define DIG_ANA_DNX1_RCTUNE_SHIFT_BITS   0

#define DIG_ANA_REFSX_SPARE_REG          0x2074
#define DIG_ANA_REFSX_SPARE_MASK         0xFF00
#define DIG_ANA_REFSX_SPARE_SHIFT_BITS   8


#define DIG_ANA_RFSX0_FDCP_EXT_BIN_REG        0x2090
#define DIG_ANA_RFSX0_FDCP_EXT_BIN_MASK       0x003F
#define DIG_ANA_RFSX0_FDCP_EXT_BIN_SHIFT_BITS 0

#define DIG_ANA_RFSX1_FDCP_EXT_BIN_REG        0x303C
#define DIG_ANA_RFSX1_FDCP_EXT_BIN_MASK       0x003F
#define DIG_ANA_RFSX1_FDCP_EXT_BIN_SHIFT_BITS 0

#define DIG_ANA_RFSX0_FDCP_TIMINGMODE_REG        0x2094
#define DIG_ANA_RFSX0_FDCP_TIMINGMODE_MASK       0xFF00
#define DIG_ANA_RFSX0_FDCP_TIMINGMODE_SHIFT_BITS 8

#define DIG_ANA_RFSX1_FDCP_TIMINGMODE_REG        0x3040
#define DIG_ANA_RFSX1_FDCP_TIMINGMODE_MASK       0xFF00
#define DIG_ANA_RFSX1_FDCP_TIMINGMODE_SHIFT_BITS 8

#define DIG_ANA_RFSX0_SPARE_REG0_REG             0x20B0
#define DIG_ANA_RFSX0_SPARE_REG0_MASK            0x00FF
#define DIG_ANA_RFSX0_SPARE_REG0_SHIFT_BITS      0


#define DIG_ANA_RFSX1_SPARE_REG0_REG             0x305C
#define DIG_ANA_RFSX1_SPARE_REG0_MASK            0x00FF
#define DIG_ANA_RFSX1_SPARE_REG0_SHIFT_BITS      0

#define DIG_ANA_RFSX0_EN_OC_ONLY_REG             0x2088
#define DIG_ANA_RFSX0_EN_OC_ONLY_MASK            0x0080
#define DIG_ANA_RFSX0_EN_OC_ONLY_SHIFT_BITS      7

#define DIG_ANA_RFSX1_EN_OC_ONLY_REG             0x3030
#define DIG_ANA_RFSX1_EN_OC_ONLY_MASK            0x8000
#define DIG_ANA_RFSX1_EN_OC_ONLY_SHIFT_BITS      15

#define DIG_ANA_RFSX0_CAL_CLKMODE_REG            0x2084
#define DIG_ANA_RFSX0_CAL_CLKMODE_MASK           0x0007
#define DIG_ANA_RFSX0_CAL_CLKMODE_SHIFT_BITS     0x0000

#define DIG_ANA_RFSX1_CAL_CLKMODE_REG            0x302C
#define DIG_ANA_RFSX1_CAL_CLKMODE_MASK           0x0700
#define DIG_ANA_RFSX1_CAL_CLKMODE_SHIFT_BITS     0x0008

#define DIG_ANA_TUNER0_ENA_REG        0x20C4
#define DIG_ANA_TUNER0_ENA_MASK       0x0040
#define DIG_ANA_TUNER0_ENA_SHIFT_BITS 6

#define DIG_ANA_TUNER1_ENA_REG        0x3064
#define DIG_ANA_TUNER1_ENA_MASK       0x0040
#define DIG_ANA_TUNER1_ENA_SHIFT_BITS 6

#define DFE_UPX_WBCLK_ENA_REG         0x5024
#define DFE_UPX_WBCLK_ENA_MASK        0x0040
#define DFE_UPX_WBCLK_ENA_SHIFT_BITS  6

#define DIG_ANA_IF_WB_ENA_REG         0x203c
#define DIG_ANA_IF_WB_ENA_MASK        0x0100
#define DIG_ANA_IF_WB_ENA_SHIFT_BITS  8

#define DIG_ANA_DAC_ENA_REG           0x2018
#define DIG_ANA_DAC_ENA_MASK          0x0100
#define DIG_ANA_DAC_ENA_SHIFT_BITS    8

#define DIG_ANA_IF_SPARE_REG         0x203C
#define DIG_ANA_IF_SPARE_MASK        0x00FF
#define DIG_ANA_IF_SPARE_SHIFT_BITS  0

#define DFE_ADC0_BW_REG              0x4280
#define DFE_ADC0_BW_MASK             0x0003
#define DFE_ADC0_BW_SHIFT_BITS       0

#define DFE_ADC1_BW_REG              0x4280
#define DFE_ADC1_BW_MASK             0x000C
#define DFE_ADC1_BW_SHIFT_BITS       2

#define DFE_DAGC0_GAINACCUM_RB_REG   0x52B8
#define DFE_DAGC0_GAINACCUM_RB_MASK  0x01FF
#define DFE_DAGC0_GAINACCUM_RB_SHIFT_BITS 0

#define DFE_CHN0_CIC1_SCALE_REG      0x5334
#define DFE_CHN0_CIC1_SCALE_MASK     0x0030
#define DFE_CHN0_CIC1_SCALE_SHIFT_BITS 8

#define DFE_CHN0_CIC2_SCALE_REG      0x5030
#define DFE_CHN0_CIC2_SCALE_MASK     0x0100
#define DFE_CHN0_CIC2_SCALE_SHIFT_BITS 8

#define DFE_CHN1_CIC2_SCALE_REG      0x504C
#define DFE_CHN1_CIC2_SCALE_MASK     0x0001
#define DFE_CHN1_CIC2_SCALE_SHIFT_BITS 0

#define DFE_CHN2_CIC2_SCALE_REG      0x5064
#define DFE_CHN2_CIC2_SCALE_MASK     0x0100
#define DFE_CHN2_CIC2_SCALE_SHIFT_BITS  8

#define DFE_CHN3_CIC2_SCALE_REG      0x5080
#define DFE_CHN3_CIC2_SCALE_MASK     0x0001
#define DFE_CHN3_CIC2_SCALE_SHIFT_BITS 0

#define DFE_CHN4_CIC2_SCALE_REG      0x5098
#define DFE_CHN4_CIC2_SCALE_MASK     0x0100
#define DFE_CHN4_CIC2_SCALE_SHIFT_BITS 8

#define DFE_CHN5_CIC2_SCALE_REG      0x50B4
#define DFE_CHN5_CIC2_SCALE_MASK     0x0001
#define DFE_CHN5_CIC2_SCALE_SHIFT_BITS  0

#define DFE_CHN6_CIC2_SCALE_REG      0x50CC 
#define DFE_CHN6_CIC2_SCALE_MASK     0x0100
#define DFE_CHN6_CIC2_SCALE_SHIFT_BITS 8

#define DFE_CHN7_CIC2_SCALE_REG      0x50E8
#define DFE_CHN7_CIC2_SCALE_MASK     0x0001
#define DFE_CHN7_CIC2_SCALE_SHIFT_BITS 0

#define DFE_CHN0_TILT_SCALE_BYP_REG   0x5338
#define DFE_CHN0_TILT_SCALE_BYP_MASK  0x0100
#define DFE_CHN0_TILT_SCALE_BYP_SHIFT_BITS 8

#define DFE_CHN0_FIR5_SCALE3X_REG   0x5334
#define DFE_CHN0_FIR5_SCALE3X_MASK  0x0001
#define DFE_CHN0_FIR5_SCALE3X_SHIFT_BITS 0

#define DFE_CHN0_FIR5_SCALE_REG      0x5220
#define DFE_CHN0_FIR5_SCALE_MASK     0x0001
#define DFE_CHN0_FIR5_SCALE_SHIFT_BITS 0


#define DFE_CHN4_CIC1_SCALE_REG      0x5338
#define DFE_CHN4_CIC1_SCALE_MASK     0x0003
#define DFE_CHN4_CIC1_SCALE_SHIFT_BITS 0

#define DFE_UPX4_DDFSWORD_REG         0x5010
#define DFE_UPX4_DDFSWORD_MASK        0x00FF
#define DFE_UPX4_DDFSWORD_SHIFT_BITS  0

#define DFE_UPX5_DDFSWORD_REG         0x5010
#define DFE_UPX5_DDFSWORD_MASK        0xFF00
#define DFE_UPX5_DDFSWORD_SHIFT_BITS  8

#define DFE_UPX6_DDFSWORD_REG         0x5014
#define DFE_UPX6_DDFSWORD_MASK        0x00FF
#define DFE_UPX6_DDFSWORD_SHIFT_BITS  0

#define DFE_UPX7_DDFSWORD_REG         0x5014
#define DFE_UPX7_DDFSWORD_MASK        0xFF00
#define DFE_UPX7_DDFSWORD_SHIFT_BITS  8

#define DIG_ANA_LT_ENA_REG            0x203C
#define DIG_ANA_LT_ENA_MASK           0x2000
#define DIG_ANA_LT_ENA_SHIFT_BITS     13

#define DIG_ANA_LT_SPARE_REG          0x2040
#define DIG_ANA_LT_SPARE_SHIFT_BITS   0
#define DIG_ANA_LT_SPARE_MASK         0x0003 
#define DIG_ANA_LT_SPARE_STROBE_MASK 0x0002

#define DFE_RFRSSI_EN_REG             0x40CC
#define DFE_RFRSSI_EN_SHIFT_BITS      5 
#define DFE_RFRSSI_EN_MASK            0x0020 

#define DFE_RFRSSI_AVG_SAMP_REG       0x40CC
#define DFE_RFRSSI_AVG_SAMP_SHIFT     8
#define DFE_RFRSSI_AVG_SAMP_MASK      0x0700

#define DFE_RFRSSI_CAL_REG            0x40CC
#define DFE_RFRSSI_CAL_MASK           0x0010
#define DFE_RFRSSI_CAL_SHIFT_BITS     4

#define DFE_TSENS_CAL_REG             0x40CC
#define DFE_TSENS_CAL_MASK            0x1000
#define DFE_TSENS_CAL_SHIFT_BITS      12

#define DFE_TSENS_EN_REG              0x40CC
#define DFE_TSENS_EN_MASK             0x2000
#define DFE_TSENS_EN_SHIFT_BITS       13

#define DIG_ANA_SPLT_ENA_REG          0x20B8
#define DIG_ANA_SPLT_ENA_MASK         0x0080
#define DIG_ANA_SPLT_ENA_SHIFT_BITS   7

#define DIG_ANA_SPLT_SPARE_REG         0x20B8
#define DIG_ANA_SPLT_SPARE_STROBE_MASK (1<<11)

#define DIG_ANA_XTAL_SPARE_REG        0x20C8
#define DIG_ANA_XTAL_SPARE_MASK       0xF000
#define DIG_ANA_XTAL_SPARE_SHIFT_BITS 12

#define DIG_ANA_XTAL_CAL_RSTB_REG        0x20C4
#define DIG_ANA_XTAL_CAL_RSTB_MASK       0x0200
#define DIG_ANA_XTAL_CAL_RSTB_SHIFT_BITS 9

#define DIG_ANA_RFSX0_FDCP_EXT_SEL_BIN_REG        0x2090
#define DIG_ANA_RFSX0_FDCP_EXT_SEL_BIN_MASK       0x3F00
#define DIG_ANA_RFSX0_FDCP_EXT_SEL_BIN_SHIFT_BITS 8

#define DIG_ANA_RFSX1_FDCP_EXT_SEL_BIN_REG        0x303C
#define DIG_ANA_RFSX1_FDCP_EXT_SEL_BIN_MASK       0x3F00
#define DIG_ANA_RFSX1_FDCP_EXT_SEL_BIN_SHIFT_BITS 8


#define AGC_RF2_0_BO_REG           0x4258
#define AGC_RF2_0_BO_MASK          0x003F

#define AGC_RF2_1_BO_REG           0x4258
#define AGC_RF2_1_BO_MASK          0x3F00

#define DFE_CDC0_LUT_ADDR_REG      0x4018
#define DFE_CDC0_LUT_ADDR_MASK     0x00FF
#define DFE_CDC0_LUT_RDATA_REG     0x428C

#define DFE_CDC1_LUT_ADDR_REG      0x4048
#define DFE_CDC1_LUT_ADDR_MASK     0xFF00
#define DFE_CDC1_LUT_RDATA_REG     0x42A8 

// Richard: Please keep the comments here before xtal settings is validated. 
//          After that, those comments should be removed
// Field name,   Default, Signed/Unsigned, BitCount, LSB_Location, BitType, Fraction Bit Info, Reg Addr   
//{"dig_ana_xtal_26mhz", 1, 0, 1, 7, 0, 0, 8388}, 
#define DIG_ANA_XTAL_26MHZ_REG        0x20C4
#define DIG_ANA_XTAL_26MHZ_MASK       0x0080
#define DIG_ANA_XTAL_26MHZ_SHIFT_BITS 7
//{"dig_ana_refsx_dsm_intmod", 92, 0, 7, 0, 0, 0, 8284}, 
#define DIG_ANA_REFSX_DSM_INTMOD_REG  0x205C
#define DIG_ANA_REFSX_DSM_INTMOD_MASK 0x007F
#define DIG_ANA_REFSX_DSM_INTMOD_SHIFT_BITS 0
//{"dig_ana_xtal_cap", 10, 0, 4, 10, 0, 0, 8388}
#define DIG_ANA_XTAL_CAP_REG          0x20C4
#define DIG_ANA_XTAL_CAP_MASK         0x3C00
#define DIG_ANA_XTAL_CAP_SHIFT_BITS   10
//"dig_ana_refsx_ena", 0, 0, 1, 12, 0, 0, 8288}
#define DIG_ANA_REFSX_ENA_REG         0x2060
#define DIG_ANA_REFSX_ENA_MASK        0x1000
#define DIG_ANA_REFSX_ENA_SHIFT_BIT   12
//{"dig_ana_refsx_dsm_fracmod", 0, 0, 25, 0, 0, 0, 8280}
#define DIG_ANA_REFSX_DSM_FRACMOD_REG  0x2058
//{"dig_ana_refsx_tune", 0, 0, 1, 0, 0, 0, 8312}, 
#define DIG_ANA_REFSX_TUNE_REG        0x2078
#define DIG_ANA_REFSX_TUNE_MASK       0x0001
#define DIG_ANA_REFSX_TUNE_SHIFT_BITS 0
//{"ana_dig_refsx_tune_done", 0, 0, 1, 4, 2, 0, 8424}
#define ANA_REFSX_TUNE_DONE_REG       0x20E8
#define ANA_REFSX_TUNE_DONE_MASK      0x0010
#define ANA_REFSX_TUNE_DONE_SHIFT_BITS 4
//{"amba_clk_ctrl", 6, 0, 3, 12, 1, 0, 40}, 
#define AMBA_CLK_CTRL_REG             0x0028
#define AMBA_CLK_CTRL_MASK            0x7000
#define AMBA_CLK_CTRL_SHIFT_BITS      12
//{"amba_clk_src", 1, 0, 1, 4, 1, 0, 40}
#define AMBA_CLK_SRC_REG              0x0028
#define AMBA_CLK_SRC_MASK             0x0010
#define AMBA_CLK_SRC_SHIFT_BITS       4
//{"dig_ana_rfrssi_cal_ena", 0, 0, 1, 14, 0, 0, 8316}
#define DIG_ANA_RFRSSI_CAL_ENA_REG    0x207C
#define DIG_ANA_RFRSSI_CAL_ENA_MASK   0x4000
#define DIG_ANA_RFRSSI_CAL_ENA_SHIFT_BITS 14
//{"dig_ana_rctune_ena", 0, 0, 1, 1, 0, 0, 8260}
#define DIG_ANA_RCTUNE_ENA_REG        0x2044
#define DIG_ANA_RCTUNE_ENA_MASK       0x0002
#define DIG_ANA_RCTUNE_ENA_SHIFT_BITS 1
//{"ana_dig_rctune", 0, 0, 4, 8, 2, 0, 8404}
#define ANA_DIG_RCTUNE_REG            0x20D4
#define ANA_DIG_RCTUNE_MASK           0x0F00
#define ANA_DIG_RCTUNE_SHIFT_BITS     8

// {"ana_dig_rfsx0_rdbk_synthcal", 0, 0, 10, 0, 2, 0, 8432},
#define ANA_DIG_RFSX0_RDBK_SYNTHCAL_REG  0x20F0
#define ANA_DIG_RFSX0_RDBK_SYNTHCAL_MASK ((1<<10)-1) // 0x03FF

#define ANA_DIG_REFSX_SETHI_RB_REG    0x20E0
#define ANA_DIG_REFSX_SETHI_RB_MASK   (1<<13)

//{"dig_ana_abb0_rctune", 6, 0, 4, 8, 0, 0, 8192}
#define DIG_ANA_ABB0_RCTUNE_REG       0x2000
#define DIG_ANA_ABB0_RCTUNE_MASK      0x0F00
#define DIG_ANA_ABB0_RCTUNE_SHIFT_BITS 8
//{"dig_ana_abb1_rctune", 6, 0, 4, 8, 0, 0, 12288}
#define DIG_ANA_ABB1_RCTUNE_REG       0x3000
#define DIG_ANA_ABB1_RCTUNE_MASK      0x0F00
#define DIG_ANA_ABB1_RCTUNE_SHIFT_BITS 8
//{"dig_ana_adc0_rctune", 6, 0, 4, 4, 0, 0, 8204}
#define DIG_ANA_ADC0_RCTUNE_REG       0x200C
#define DIG_ANA_ADC0_RCTUNE_MASK      0x00F0
#define DIG_ANA_ADC0_RCTUNE_SHIFT_BITS 4
//{"dig_ana_adc1_rctune", 6, 0, 4, 4, 0, 0, 12300}
#define DIG_ANA_ADC1_RCTUNE_REG       0x300C
#define DIG_ANA_ADC1_RCTUNE_MASK      0x00F0
#define DIG_ANA_ADC1_RCTUNE_SHIFT_BITS 4

//{"dig_ana_if_rctune", 6, 0, 4, 0, 0, 0, 8248}
#define DIG_ANA_IF_RCTUNE_REG         0x2038
#define DIG_ANA_IF_RCTUNE_MASK        0x000F
#define DIG_ANA_IF_RCTUNE_SHIFT_BITS  0

#define DEMOD0_INT_RESET_REG        0x6000
#define DMD0_INT_RESET              0xFFFF
#define DMD0_SOFTDEC_VALUE          0x6018

#define DEMOD0_MASK_TUNER_DONE_REG  0x6004
#define DEMOD1_MASK_TUNER_DONE_REG  0x7004
#define DEMOD2_MASK_TUNER_DONE_REG  0x8004
#define DEMOD3_MASK_TUNER_DONE_REG  0x9004

#define DFE_CHN0_COMP_REG           0x5030 
#define DFE_CHN1_COMP_REG           0x504C 
#define DFE_CHN2_COMP_REG           0x5064 
#define DFE_CHN3_COMP_REG           0x5080 
#define DFE_CHN4_COMP_REG           0x5098 
#define DFE_CHN5_COMP_REG           0x50B4 
#define DFE_CHN6_COMP_REG           0x50CC 
#define DFE_CHN7_COMP_REG           0x50E8 

#define DFE_PCH_ISEL_TS_REG         0x44C4
#define DFE_PCH_ISEL_TS_MASK        0x000C
#define DFE_PCH_ISEL_TS_SHIFT_BITS  0x0002

#define DFE_PCH_ISEL_IF_REG         0x44C4
#define DFE_PCH_ISEL_IF_MASK        0x0003
#define DFE_PCH_ISEL_IF_SHIFT_BITS  0x0000

// #define AGC_LNA_0_BO_REG            0x44C8
// #define AGC_LNA_1_BO_REG            0x44CC
#define DFE_AGC_LNA_x_BO_REG(tunerId)  (0x44C8+(tunerId)*4)
#define DFE_AGC_LNA_x_BO_LSB(tunerId)  (((tunerId)==0)?8:0)
#define DFE_AGC_LNA_x_BO_NBITS         5
#define DFE_AGC_LNA_x_BO_MASK(tunerId) (((tunerId)==0)?0x1F00:0x001F)

#define AGC_APPLY_GAIN_REG             0x4270
#define AGC_APPLY_GAIN_MASK            1

// #define AGC_RF1_BO         0x4254
#define DFE_AGC_RF1_BO_REG            0x4254
#define DFE_AGC_RF1_BO_LSB            8
#define DFE_AGC_RF1_BO_NBITS          5

// #define  AGC_RF2_1_BO              0x4258
// #define  AGC_RF2_0_BO              0x4258
#define DFE_AGC_RF2_x_BO_REG          0x4258
#define DFE_AGC_RF2_x_BO_LSB(tunerId) ((tunerId)*8)
#define DFE_AGC_RF2_x_BO_NBITS        5

// #define DFE_CHN0_3_CIC1_SCALE_REG   0x5334 // LSB=(8+chanId*2)
// #define DFE_CHN4_7_CIC1_SCALE_REG   0x5338 // LSB=(chanId-4)*2
#define DFE_CIC1_SCALE_REG(chanId)    (((chanId)<4)?0x5334:0x5338)
#define DFE_CIC1_SCALE_LSB(chanId)    (((chanId)<4)?(8+(chanId)*2):(((chanId)-4)*2))
#define DFE_CIC1_BYP_LSB(chanId)      (((chanId)&1)?1:9)
#define DFE_CIC2_SCALE_LSB(chanId)    (((chanId)&1)?0:8)
#define DFE_CIC2_BYP_LSB(chanId)      (((chanId)&1)?2:10)

#define DFE_CIC1_BYP_CIC2_SCALE_CIC2_BYP_REG(chanId)  (0x5030 + 0x1A*(chanId) + ((chanId)&1)*2)

#define DFE_CHNx_TILT_SCALE_BYP_REG 0x5338 // bit 15:8
#define DFE_TILT_SCALE_BIT(chanId)  (1<<(8+(chanId)))

#define DFE_CHNx_FIR5_SCALE3X_REG   0x5334 // bit 7:0
#define DFE_FIR5_SCALE3X_BIT(chanId) (1<<(chanId))

#define DFE_CHNx_FIR5_SCALE_REG     0x5220 // bit 7:0
#define DFE_FIR5_SCALE_BIT(chanId)  (1<<(chanId))

// #define DFE_DAGC0_GAINACCUM_RB_REG  0x52B8 // bit 12:0
// #define DFE_DAGC1_GAINACCUM_RB_REG  0x52BC // bit 12:0
// #define DFE_DAGC2_GAINACCUM_RB_REG  0x52C0 // bit 12:0
// #define DFE_DAGC3_GAINACCUM_RB_REG  0x52C4 // bit 12:0
// #define DFE_DAGC4_GAINACCUM_RB_REG  0x52C8 // bit 12:0
// #define DFE_DAGC5_GAINACCUM_RB_REG  0x52CC // bit 12:0
// #define DFE_DAGC6_GAINACCUM_RB_REG  0x52D0 // bit 12:0
// #define DFE_DAGC7_GAINACCUM_RB_REG  0x52D4 // bit 12:0

#define DFE_DAGCx_GAINACCUM_RB_REG(chanId)  (0x52B8+(chanId)*4)
#define DFE_DAGCx_GAINACCUM_RB_NBITS        13

#define DFE_TSENS_RB_REG            0x42E4 // bit 8:0
#define DFE_TSENS_RB_LSB            0
#define DFE_TSENS_RB_NBITS          9

#define DEMOD0_BURST_FREEZE_CTRL_REG      0x6008
#define DMD0_BURST_FREEZE_MODE            0x4000
#define DMD0_BURST_FREEZE_MODE_ENABLE     0x2000
#define DEMOD0_EQU_FREQ_FAGC_CTR_REG      0x6084
#define DEMOD0_EQU_CARR_DD_CTRL_REG       0x60A0
#define DEMOD0_EQU_LLP_CTRL_REG           0x60D4
#define DMD_EQU_CARR_DD_KF_MASK           0xE000

#define DEMOD_MAGC_GAIN__REG              0x0148


#define OOB_RX_POWER_CAL_FACTOR           4       // 4dB

#define DIG_ANA_DNXx_LNA_TILT_REG(tunerId) ((tunerId)==0?0x2020:0x3018) // 15-14
// TODO: should this be on/off by default?

#define DEM_MP_CLK_INV_REG                0x005C  
#define DFE_GAINCALx_INC1_REG(chanId)     (0x5254 + (chanId)*4)

#define TP_CLK_INV_REG                    0x0068
#define TP_CLK_INV_MASK                   (1<<15)

#define DMDx_MDVAL_GATE_EN_INV_REG        0x0098
#define DMDx_MDVAL_GATE_EN_INV_MASK       0x003C // bit 5:2

#define ECO8_REG                          (0x001C)
#define ECO8_DISABLE_AGC_BIT              (1<<0)
#define ECO8_DISABLE_DFE_AGC_BIT          (1<<1)

#define ADCx_RSSI_RB_REG(tunerId)         ((tunerId)==0?0x4490:0x4494)
#define ECO6_REG                          (0x0014)
#define ECO5_REG                          (0x0010)

#define ANA_DIG_SOC_ID_REG                0x03E0
#define ANA_DIG_SOC_MM_REG                0x03E4
#define ES1_MM0_VERSION                   0x0100
#define ES2_MM0_VERSION                   0x0200
#define ES2_LINK_RTL_VERSION              0x2000
#define SEQ_VHF11HI                       68750000ULL

#define ECO_4_SOC_ID_REG                  0x000C
#define LINK_RTL_VERSION_REG              0x07FC
#define IS_ES2_OR_NEWER(devContextPtr)    ((devContextPtr->ChipId) >= ES2_MM0_VERSION)
#define IS_ASIC_TARGET(devContextPtr)     ((devContextPtr->AsicId) != 0)

/* The following register definitions are copied from registers.h */
#define DIG_ANA_IF_SPARE              8252, 0, 8
#define DIG_ANA_ADC0_CHOP_ENA         8200, 0, 1 
#define DIG_ANA_ADC1_CHOP_ENA         12296, 0, 1 
#define DIG_ANA_ADC0_TI_CAL           8208, 0, 2 
#define DIG_ANA_ADC1_TI_CAL           12304, 0, 2
#define DIG_ANA_ABB0_SPARE            8196, 0, 4 
#define DIG_ANA_ABB1_SPARE            12292, 0, 4 
#define DFE_CDC0_OFFSET_TZ_FLIP       16436, 0, 8
#define DFE_CDC1_OFFSET_TZ_FLIP       16484, 0, 8 
#define DIG_ANA_LT_GAIN               8252, 14, 2 
#define DIG_ANA_SPLT_GAIN             8376, 8, 2 
#define DIG_ANA_XTAL_TH               8396, 0, 2 

// Mailbox registers
#define MAILBOX_REG_BASE_ADDR             0xA800
#define MAILBOX_REG_NUM_PENDING_HOST_CMDS 0xA800
#define MAILBOX_REG_FIRMWARE_RC_VER       0xA802
#define MAILBOX_REG_CUR_CHAN_RSSI_DU      0xA804
#define MAILBOX_REG_AFEAGC_WBVGA0_LOCK    0xA838
#define MAILBOX_REG_CHAN0_DFEAGC_STATE    0xA8F0
#define MAILBOX_REG_CHAN1_DFEAGC_STATE    0xA8F2
#define MAILBOX_REG_CHAN2_DFEAGC_STATE    0xA8F4
#define MAILBOX_REG_CHAN3_DFEAGC_STATE    0xA8F6
#define MAILBOX_REG_CHAN4_DFEAGC_STATE    0xA8F8
#define MAILBOX_REG_CHAN5_DFEAGC_STATE    0xA8FA
#define MAILBOX_REG_CHAN6_DFEAGC_STATE    0xA8FC
#define MAILBOX_REG_CHAN7_DFEAGC_STATE    0xA8FE

#define DFE_CHAN0_DFEAGC_STATE_REG (MAILBOX_REG_CHAN0_DFEAGC_STATE)
#define DFE_CHAN1_DFEAGC_STATE_REG (MAILBOX_REG_CHAN1_DFEAGC_STATE)
#define DFE_CHAN2_DFEAGC_STATE_REG (MAILBOX_REG_CHAN2_DFEAGC_STATE)
#define DFE_CHAN3_DFEAGC_STATE_REG (MAILBOX_REG_CHAN3_DFEAGC_STATE)
#define DFE_CHAN4_DFEAGC_STATE_REG (MAILBOX_REG_CHAN4_DFEAGC_STATE)
#define DFE_CHAN5_DFEAGC_STATE_REG (MAILBOX_REG_CHAN5_DFEAGC_STATE)
#define DFE_CHAN6_DFEAGC_STATE_REG (MAILBOX_REG_CHAN6_DFEAGC_STATE)
#define DFE_CHAN7_DFEAGC_STATE_REG (MAILBOX_REG_CHAN7_DFEAGC_STATE)
#define DFE_AGC_LOCK                      4

#define MAILBOX_REG_PWR_REPORT_CHN0_CNT            0xA904
#define MAILBOX_REG_PWR_REPORT_CHN0_RF1_GAIN       0xA906
#define MAILBOX_REG_PWR_REPORT_CHN0_LNA_GAIN       0xA908
#define MAILBOX_REG_PWR_REPORT_CHN0_RF2_GAIN       0xA90A
#define MAILBOX_REG_PWR_REPORT_CHN0_WBVGA_GAIN     0xA90C // S16:5 
#define MAILBOX_REG_PWR_REPORT_CHN0_G_CIC1         0xA90E
#define MAILBOX_REG_PWR_REPORT_CHN0_G_CIC2         0xA910
#define MAILBOX_REG_PWR_REPORT_CHN0_G_TCF          0xA912
#define MAILBOX_REG_PWR_REPORT_CHN0_G_FIR5         0xA914
#define MAILBOX_REG_PWR_REPORT_CHN0_G_NBDAGC       0xA916 // S16:6

#define MAILBOX_REG_PWR_REPORT_CHN1_CNT            0xA918
#define PWR_REPORT_NB_GAIN_SCALE                   16
#define PWR_REPORT_MAILBOX_REG_BLOCK_SIZE          (MAILBOX_REG_PWR_REPORT_CHN1_CNT-MAILBOX_REG_PWR_REPORT_CHN0_CNT)

#define MAILBOX_REG_PWR_CAL_FREQ_STEP_MHZ          0xA9A4
#define MAILBOX_REG_PWR_CAL_TUNER_MAP              0xA9A6
#define MAILBOX_REG_PWR_CAL_F_WB_MHZ               0xA9A8
#define MAILBOX_REG_PWR_CAL_BW_MODE                0xA9AA
#define MAILBOX_REG_PWR_CAL_NB_OFFSET              0xA9AC
#define MAILBOX_REG_PWR_CAL_DEBUG_FLAG             0xA9AE
#define PWR_CAL_DEBUG_BIT_ENABLE_COMPENSATION      (1<<0)
#define PWR_CAL_DEBUG_BIT_VERBOSE                  (1<<1)

#define MAILBOX_REG_PWR_REPORT_CHN0_RXPWR          0xA9B0 // S16:6
#define MAILBOX_REG_PWR_REPORT_CHN1_RXPWR          0xA9B2 // S16:6
#define MAILBOX_REG_PWR_REPORT_CHN2_RXPWR          0xA9B4 // S16:6
#define MAILBOX_REG_PWR_REPORT_CHN3_RXPWR          0xA9B6 // S16:6
#define MAILBOX_REG_PWR_REPORT_CHN4_RXPWR          0xA9B8 // S16:6
#define MAILBOX_REG_PWR_REPORT_CHN5_RXPWR          0xA9BA // S16:6
#define MAILBOX_REG_PWR_REPORT_CHN6_RXPWR          0xA9BC // S16:6
#define MAILBOX_REG_PWR_REPORT_CHN7_RXPWR          0xA9BE // S16:6
#define MAILBOX_REG_PWR_REPORT_CHN0_DVGA_RSSI      0xA9C0 // U16:5
#define MAILBOX_REG_PWR_REPORT_CHN1_DVGA_RSSI      0xA9C2 // U16:5
#define MAILBOX_REG_PWR_REPORT_CHN2_DVGA_RSSI      0xA9C4 // U16:5
#define MAILBOX_REG_PWR_REPORT_CHN3_DVGA_RSSI      0xA9C6 // U16:5
#define MAILBOX_REG_PWR_REPORT_CHN4_DVGA_RSSI      0xA9C8 // U16:5
#define MAILBOX_REG_PWR_REPORT_CHN5_DVGA_RSSI      0xA9CA // U16:5
#define MAILBOX_REG_PWR_REPORT_CHN6_DVGA_RSSI      0xA9CC // U16:5
#define MAILBOX_REG_PWR_REPORT_CHN7_DVGA_RSSI      0xA9CE // U16:5

#define MAILBOX_REG_CHN0_RXPWR_MONITOR             0xAA6E // S16:6
#define MAILBOX_REG_CHN1_RXPWR_MONITOR             0xAA70 // S16:6
#define MAILBOX_REG_CHN2_RXPWR_MONITOR             0xAA72 // S16:6
#define MAILBOX_REG_CHN3_RXPWR_MONITOR             0xAA74 // S16:6
#define MAILBOX_REG_CHN4_RXPWR_MONITOR             0xAA76 // S16:6
#define MAILBOX_REG_CHN5_RXPWR_MONITOR             0xAA78 // S16:6
#define MAILBOX_REG_CHN6_RXPWR_MONITOR             0xAA7A // S16:6
#define MAILBOX_REG_CHN7_RXPWR_MONITOR             0xAA7C // S16:6

#define MAILBOX_REG_IF0_AGC_SETPT                  0xA9D0
#define MAILBOX_REG_IF1_AGC_SETPT                  0xA9D2
#define MAILBOX_REG_IF2_AGC_SETPT                  0xA9D4
#define MAILBOX_REG_IF3_AGC_SETPT                  0xA9D6
#define MAILBOX_REG_IF_RAMP_STEP_DURATION          0xA9D8
#define MAILBOX_REG_IF_RAMP_STEP_SIZE              0xA9DA
#define MAILBOX_REG_IF_RAMP_BOTTOM                 0xA9DC
#define MAILBOX_REG_DFE_HOSTCMD_PARAM1             0xAA24
#define MAILBOX_REG_DFE_ACTIVE_CHAN_MAP            0xAA2A
#define MAILBOX_REG_DFE_FASTSCAN_FLAG              0xAA32
#define MAILBOX_REG_FAST_WB0_AGC_FIRST             0xAA34
#define MAILBOX_REG_FAST_WB1_AGC_FIRST             0xAA36
#define MAILBOX_REG_VCO_TRHSH_IN_MHZ               0xAA3C
#define MAILBOX_REG_TILT_FLAG                      0xAA44 // MAILBOX_REG_DFE_DEBUG0
#define DEBUG0_AFEAGC_V2_TILT_ON_PLANT_MASK        (1<<0)

// Macro to return a mask of 'nbits' ones from bit 'lsbloc'.
// (please use constants for lsbloc and nbits if possible, so that compiler/preprocessor 
// can expand most of calculations)
#define MXL_MASK(lsbloc, nbits)           ((0xFFFFFFFFU>>(32-(nbits))) << (lsbloc))

#define MXL_ABS_INT32(x)                  (UINT32)(((SINT32)(x))>=0?(x):(-((SINT32)(x))))
#define MXL_ABS_REAL32(x)                 (((x)>=0)?(x):(-(x)))

#ifdef _MXL251_FIXEDPOINT_
#define MXL_IS_ZERO(x, PRECISION)         (((x) * (1 << PRECISION )) < 1) //for Fixed point numbers with 'MXL251_PRECESION' fractional bits.
#else
#define MXL_IS_REAL32_ZERO(x)             (MXL_ABS_REAL32(x)<0.000000001)
#endif

#define MXL_SIGN_EXT16(x, n)              ((SINT16)(((UINT16)(x))<<(16-(n)))>>(16-(n)))
#define MXL_SIGN_EXT32(x, n)              ((SINT32)(((UINT32)(x))<<(32-(n)))>>(32-(n)))

#ifdef _BOOT_SCAN_ENABLED_
#define BOOT_SCAN_FREQ_START      96
#define BOOT_SCAN_FREQ_STOP       864
#define BOOT_SCAN_MAX_NUM_BINS    64 // (1000MHz/16MHz)
#define BOOT_SCAN_MIN_VALID_RSSI  400
#endif // _BOOT_SCAN_ENABLED_

#define ENHANCED_CHAN_TUNE_TIMEOUT_QAM_LOCK      150000ULL   /* QAM timeout=150ms    */
#define ENHANCED_CHAN_TUNE_TIMEOUT_FEC_LOCK      50000ULL    /* FEC timeout=50ms     */
#define ENHANCED_CHAN_TUNE_TIMEOUT_MPEG_LOCK     50000ULL    /* MPEG timeou=50ms     */
#define ENHANCED_CHAN_TUNE_TIMEOUT_ALL_LOCK      2000000ULL  /* Global timeout=2s    */

#define MHZ_1                           1000000UL
#define MAX_LO_DIV_RATIO                64
#define MAX_VCO_FREQ_IN_MHZ             5000
#define MAX_VCO_FREQ_AVOID1_IN_MHZ      3450
#define MAX_VCO_FREQ_AVOID2_IN_MHZ      4600
#define FRACN_AVOIDANCE_FREQ_LIMIT_MHZ  4
#define SCALE_OVERFLOW_PROTECT          10

/*****************************************************************************************
    User-Defined Types (Typedefs)
*****************************************************************************************/

typedef enum
{
  WB_16_MHz = 16,
  WB_48_MHz = 48,
  WB_96_MHz = 96
} WB_BANDWIDTH_E;

typedef enum
{
  NB_6_MHz = 6,
  NB_8_MHz = 8,
} NB_BANDWIDTH_E;

#define NUM_ECOS_OFFSET_SEARCH 2
typedef struct
{
  UINT32                  WbCapBandWidthInMhz;
  UINT32                  WbCapFreqInHz;
  MXL_TUNER_POWER_MODE_E  TunerPowerMode;
  UINT32                  NbChanFreqInHz;
  SINT32                  FreqOffsetInHz;
  MXL_BOOL                FastScanEnable;
  UINT8                   BandWidthInMHz;

  struct
  {
    UINT8  CurQamType;
    UINT8  CurAnnexType;
#ifdef _MXL251_FIXEDPOINT_
    UINT32 CurSymbolRate;
#else
    REAL32 CurSymbolRate;	
#endif
    SINT32 LockRangeInHz; // Default to 100KHz
#ifdef _DBG_USE_LAST_LOCKED_CARRIER_OFFSET_
    SINT32 NbTunerOffsetInHz;
    SINT32 LastLockedCarrierOffset;
#endif // _DBG_USE_LAST_LOCKED_CARRIER_OFFSET_
  } Demod;

  struct
  {
    MXL_BOOL  IFEnable;
    MXL_BOOL  Polarity;
    UINT32    FreqInHz;
    UINT16    AgcSetPoint;
  } IF;

} TUNER_CONFIG_T;

/* I2C COMMAND Communication: Command Code ID */
typedef enum
{
  HOST_CMD_SET_ADDR_CFG = 1,
  HOST_CMD_DOWNLOAD_SEGMENT_CFG,
  HOST_CMD_DOWNLOAD_DONE_CFG,

  HOST_CMD_DEV_DEVICE_RESET_CFG = 10,
  HOST_CMD_DEV_XTAL_SETTINGS_CFG,
  HOST_CMD_DEV_POWER_MODE_CFG,
  HOST_CMD_DEV_OVERWRITE_DEFAULT_CFG,

  HOST_CMD_DEV_VERSION_INFO_REQ,

  HOST_CMD_DEMOD_SYMBOL_RATE_CFG = 20,
  HOST_CMD_DEMOD_MPEG_OUT_CFG,
  HOST_CMD_DEMOD_ANNEX_QAM_TYPE_CFG,
  HOST_CMD_DEMOD_INTR_MASK_CFG,
  HOST_CMD_DEMOD_INTR_CLEAR_CFG,
  HOST_CMD_DEMOD_RESET_STAT_COUNTER_CFG, 
  HOST_CMD_DEMOD_ADC_IQ_FLIP_CFG,

  HOST_CMD_DEMOD_INTR_STATUS_REQ = 30,
  HOST_CMD_DEMOD_LOCK_REQ,  // Include FEC,MPEG and QAM Lock status req
  HOST_CMD_DEMOD_SNR_REQ,
  HOST_CMD_DEMOD_BER_UNCODED_BER_CER_REQ,

  HOST_CMD_DEMOD_ANNEX_QAM_TYPE_REQ,
  HOST_CMD_DEMOD_CARRIER_OFFSET_REQ,
  HOST_CMD_DEMOD_INTERLEAVER_DEPTH_REQ,
  HOST_CMD_DEMOD_EQUALIZER_FILTER_REQ,
  HOST_CMD_DEMOD_TIMING_OFFSET_REQ,

  HOST_CMD_TUNER_WB_CAPTURE_TUNE_CFG = 50,
  HOST_CMD_TUNER_NB_CHAN_TUNE_CFG = 51,
  HOST_CMD_TUNER_NB_CHAN_DISABLE_CFG = 52,
  HOST_CMD_TUNER_AGC_LOCK_SPEED_CFG = 53,

  HOST_CMD_TUNER_DBG_IQOUT_CFG = 54,        // Internal
  HOST_CMD_TUNER_DBG_AGC_SETPOINT_CFG = 55, // Internal
  HOST_CMD_TUNER_DBG_AFE_AGC_CFG = 56,
  HOST_CMD_TUNER_POWER_REPORT_CFG = 57,
  HOST_CMD_TUNER_WB_DISABLE_CFG = 58,  

  HOST_CMD_TUNER_LOCK_STATUS_REQ = 60, 
  HOST_CMD_TUNER_RF_RX_PWR_REQ,
  HOST_CMD_TUNER_CURR_SETTING_REQ,
  HOST_CMD_TUNER_DBG_SENSOR_TEMP_REQ,  // Internal

  // MAX_NUM_HOST_COMMAND
} MXL_CMD_ID_E;

/* I2C COMMAND Communication: Response Code ID */
typedef enum
{
  RESPONSE_ID_SUCCESS = 0,
  RESPONSE_ID_NOT_READY,
  RESPONSE_ID_NOT_INTEGRATE,
  MAX_NUM_RESPONSE_ID
} MXL_RSP_ID_E;

/* Host command data structure */
typedef struct
{
  UINT8 syncChar;                    /* 0x00: Bit[7-4]:Packet sync character (0x0E),  bit[3-0]: serial */
  MXL_CMD_ID_E commandId;            /* 0x01: command opcode = 0x02 for firmware download */
  UINT8 payloadCheckSum;             /* 0x02: Checksum of packet payload */
  UINT8 payloadLen;                  /* 0x03: Length of packet payload: 1 - 252 */
  UINT8 data[MAX_COMMAND_DATA_SIZE]; /* 0x04-0x0xFF: command field data */
} HOST_COMMAND_T, *PHOST_COMMAND_T;

/* Firmware response data structure */
typedef struct
{
  UINT8 syncChar;                    /* 0x00: Bit[7-4]:Packet sync character (0x0E),  bit[3-0]: serial */
  MXL_RSP_ID_E errorCode;            /* 0x01: Error code, 0x00 means ok. */
  UINT8 payloadCheckSum;             /* 0x02: Checksum of packet payload */
  UINT8 payloadLen;                  /* 0x03: Length of packet payload: 1 - 252 */
  UINT8 data[MAX_COMMAND_DATA_SIZE]; /* 0x04-0xFF: response field data */
} FW_RESPONSE_T, *PFW_RESPONSE_T;

typedef struct
{
  UINT8 id;                 /* 0x00-0x00: file identifier ('M') */
  UINT8 fmtVersion;         /* 0x01-0x01: file format version in ascii (default to '1') */
  UINT8 headerLen;          /* 0x02-0x02: header length (<256) in bytes, should be sizeof(MBIN_FILE_HEADER_T) */
  UINT8 numSegments;        /* 0x03-0x03: number of segments in the image (<256) */
  UINT8 entryAddress[4];    /* 0x04-0x07: entry address of execution, in big endian */
  UINT8 imageSize24[3];     /* 0x08-0x0A: 24-bit image size in bytes, not including header, in big endian */
  UINT8 imageChecksum;      /* 0x0B-0x0B: 8-bit checksum of file data, not including header */
  UINT8 reserved[4];        /* 0x0C-0x0F: reserved for future use */
} MBIN_FILE_HEADER_T;

typedef struct
{
  MBIN_FILE_HEADER_T  header;    /* 0x00: file header */
  UINT8 data[1];                 /* 0x10: place holder for accessing starting of filedata */
} MBIN_FILE_T;

typedef struct
{
  UINT8 id;                      /* 0x00-0x00: segment identifier (always 'S' for now) */
  UINT8 len24[3];                /* 0x01-0x03: data length in 24-bit big endian, not including header */
                                 /* PLEASE note: */
                                 /*    len24 is the real length of following data segement, and the next memory */
                                 /*    segment (if any) will start from next 32-bit aligned address, which is   */
                                 /*    &data[(len24+3)&(~3)]                                                    */
  UINT8 address[4];              /* 0x04-0x07: loading address of this segment, in big endian                   */
} MBIN_SEGMENT_HEADER_T;


typedef struct
{
  MBIN_SEGMENT_HEADER_T header;  /* 0x00: segment header */
  UINT8 data[1];                 /* 0x08: place holder for accessing starting of data */
} MBIN_SEGMENT_T;

// MXL defined buffer structure
typedef struct
{
  UINT32 capacity;  /* capacity of buffer */
  UINT8* dataPtr;   /* buffer pointer */
  UINT32 dataLen;   /* size of content */
} MXL_BUFFER_T;

typedef struct
{
  UINT16 addr;
  UINT16 mask;
} REG_MASK_INFO_T;

typedef struct
{
  UINT16 regAddr;
  UINT16 mask;
  UINT16 data;
} REG_CTRL_INFO_T, *PREG_CTRL_INFO_T;

typedef struct
{
  UINT8 interDepthI;
  UINT8 interDepthJ;
} INTERLEAVER_LOOKUP_INFO_T, *PINTERLEAVER_LOOKUP_INFO_T;

typedef struct
{
  UINT16 lutY;
} LUTY_LOOKUP_INFO_T, *PLUTY_LOOKUP_INFO_T;

typedef enum
{
  FIRMWARE_STATUS_UNKNOWN = 0,
  FIRMWARE_STATUS_BOOTLOADER,
  FIRMWARE_STATUS_LOADED,
} FIRMWARE_STATUS_E;

typedef enum
{
  SPIN_UNTIL_EQ  = 0,
  SPIN_UNTIL_NEQ = 1,
} SPIN_CONDITION_E;

typedef enum
{
  AGC_INIT,
  AGC_CHAN_CHANGE,
  AGC_WAIT_AFE_SETTLE,
  AGC_WAIT_DVGA_SETTLE,
  AGC_NORMAL,
  AGC_WAIT_DVGA_SETTLE_AFTER_DFE_GAIN_CHANGE,
  AGC_CABLE_CUT
} AGC_STATE_E;

#ifdef _BOOT_SCAN_ENABLED_
typedef struct
{
  UINT16 adcRssi[BOOT_SCAN_MAX_NUM_BINS];
  UINT16 wbFreq[BOOT_SCAN_MAX_NUM_BINS];
#ifdef _MXL251_FIXEDPOINT_
  UINT64 estimatedTilt;
#else
  REAL32 estimatedTilt;
#endif
} BOOT_SCAN_VARS_T;
#endif // _BOOT_SCAN_ENABLED_

typedef struct
{
  UINT64 AccCwCorrCount[MAX_251SF_DEMODS];
  UINT64 AccCwErrCount[MAX_251SF_DEMODS];
  UINT64 AccCwUnerrCount[MAX_251SF_DEMODS];
  UINT64 AccCwReceived[MAX_251SF_DEMODS];
  UINT64 AccCorrBits[MAX_251SF_DEMODS];
  UINT64 AccErrMpeg[MAX_251SF_DEMODS];
  UINT64 AccReceivedMpeg[MAX_251SF_DEMODS];
} ACC_STAT_COUNTER_T, *PACC_STAT_COUNTER_T;

typedef enum
{
  POWER_CAL_DISABLE_COMP,
  POWER_CAL_ENABLE_COMP,
} POWER_CAL_COMP_E;

typedef struct
{
  UINT8                 i2cSlaveAddr; 
  UINT8                 ActiveIFMap;
#ifdef MXL_WARE_MERGE
  UINT8                 FirstTuned;
#endif // MXL_WARE_MERGE
  UINT16                ChipId;
  UINT16                AsicId;        // 0 for FPGA platform
  UINT16                vcoThresholdInMHz;
  UINT16                DAGCBottomSetPt; // = 10*16;
  MXL_XTAL_FREQ_E       XtalFreq;
#ifdef _MXL251_FIXEDPOINT_
  UINT32				RefPllFreqInMHz;
#else
  REAL32                RefPllFreqInMHz;
#endif
  UINT32                RefVCOFreqInMHz;
  FIRMWARE_STATUS_E     FirmwareStatus;
  UINT64                FirmwareVersion;
#ifdef _BOOT_SCAN_ENABLED_
  BOOT_SCAN_VARS_T      BootScan;
#endif // _BOOT_SCAN_ENABLED_
  POWER_CAL_COMP_E      PwrCalCompAtScan; // = POWER_CAL_DISABLE_COMP; 
  const MXL_PWR_CAL_FREQ_RANGE_T* PwrCalFreqRangeTable; // = CHECKME PwrCalFreqRangeTable_ES1_100_5Band
  ACC_STAT_COUNTER_T    AccStatCounter;
  MXL_NVRAM_FILE_T      MxLNVRAMFile;
  TUNER_CONFIG_T        Tuners[MAX_NUM_TUNER];
} MXL251SF_DEV_CONTEXT_T, *PMXL251SF_DEV_CONTEXT_T;

typedef enum
{
  ENHANCED_CHAN_TUNE_STATE_WAIT_FOR_QAM_LOCK = 0,
  ENHANCED_CHAN_TUNE_STATE_WAIT_FOR_FEC_LOCK,
  ENHANCED_CHAN_TUNE_STATE_WAIT_FOR_MPEG_LOCK
} ENHANCED_CHAN_TUNE_STATE_E;

/******************************************************************************
    Global Variable Declarations
******************************************************************************/

extern UINT16 MxL251_MatchedFilterCoef_AnnexB256[];
extern UINT16 MxL251_MatchedFilterCoef_AnnexB64[];
extern UINT16 MxL251_MatchedFilterCoef_AnnexA[];

#ifdef _OOB_SUPPORT_ENABLED_
extern REG_CTRL_INFO_T MxL_OobAciMfCoef[];     
extern REG_CTRL_INFO_T MxL_OobAciMfCoef_0_772MHz[];     
extern REG_CTRL_INFO_T MxL_OobAciMfCoef_1_024MHz[];     
extern REG_CTRL_INFO_T MxL_OobAciMfCoef_1_544MHz[];
#endif // _OOB_SUPPORT_ENABLED_

extern INTERLEAVER_LOOKUP_INFO_T MxL251_InterDepthLookUpTable[];
extern LUTY_LOOKUP_INFO_T MxL251_LutYLookUpTable[];
extern MXL251SF_DEV_CONTEXT_T MxL251Dev[MAX_251SF_DEVICES];

/******************************************************************************
    Prototypes
******************************************************************************/

MXL_STATUS MxL251_Ctrl_ProgramRegisters(UINT8 i2cSlaveAddr, MXL_DEMOD_ID_E demodId , PREG_CTRL_INFO_T ctrlRegInfoPtr);
MXL_STATUS MxL251_WaitForHostCommandToComplete(UINT8 i2cAddr);
MXL_STATUS MxL251_Ctrl_DownloadFirmwareInMbin(UINT8 i2cSlaveAddr,MBIN_FILE_T* mbinPtr,UINT8 enableRun);
MXL_STATUS MxL251_Ctrl_DownloadFirmwareSegment(UINT8 i2cSlaveAddr, UINT32 address, const UINT8* dataPtr, UINT32 dataLen);
MXL_STATUS MxL251_Ctrl_SendDownloadCommand(UINT8 i2cSlaveAddr, MXL_CMD_ID_E commandId, void* dataPtr, UINT32 dataLen, UINT16 downloadBlockCnt);
MXL_STATUS MxL251_Ctrl_SendHostCommand(UINT8 i2cSlaveAddr, PHOST_COMMAND_T commandPtr);
MXL_STATUS MxL251_Ctrl_GetDeviceResp(UINT8 i2cSlaveAddr, UINT16 regAddr, PFW_RESPONSE_T responsePtr);
MXL_STATUS MxL251_Ctrl_HostComm(UINT8 i2cSlaveAddr, PHOST_COMMAND_T commandPtr, PFW_RESPONSE_T responsePtr);
MXL_STATUS MxL251_Ctrl_CheckIntegration(UINT8 readCheckSum, UINT8 readDataLen, UINT8 *readDataPtr);
MXL_STATUS MxL251_Ctrl_CalCheckSum(UINT8 inDataLen, UINT8 *inDataPtr, UINT8 *checkSum);
void       MxL251_Ctrl_SetBigEndian24(UINT8 buf[], UINT32 val);
void       MxL251_Ctrl_SetBigEndian32(UINT8 buf[], UINT32 val);
UINT32     MxL251_Ctrl_GetBigEndian24(const UINT8 buf[]);
UINT32     MxL251_Ctrl_GetBigEndian32(const UINT8 buf[]);
MXL_STATUS MxL251_Ctrl_SetWbCaptureBw(UINT8 i2cAddr, MXL_TUNER_ID_E tunerId, UINT8 wbBwVal);
MXL_STATUS MxL251_Ctrl_NbTuneCfgDfeXbar(UINT8 i2cAddr, MXL_TUNER_ID_E tunerId, UINT32 chanId);
MXL_STATUS MxL251_Ctrl_SetFir3Cic2Cic1(UINT8 i2cAddr, UINT8 chanId, UINT32 wbBW);
UINT16     MxL251_Ctrl_ConvertDemodIdToAddr(MXL_DEMOD_ID_E DemodId, UINT16 Addr);
UINT32     MxL251_Ctrl_GetField(UINT32 input, UINT32 lsbloc, UINT32 nbits);
UINT32     MxL251_Ctrl_SetField(UINT32 input, UINT32 lsbloc, UINT32 nbits, UINT32 value);
MXL_STATUS MxL251_Ctrl_WriteRegisterMask(UINT8 i2cAddr, UINT16 regAddr, UINT16 mask, UINT16 val);
MXL_STATUS MxL251_Ctrl_WriteRegisterField(UINT8 i2cAddr, UINT16 regAddr, UINT8 bitLocation, UINT8 bitWidth, UINT16 value);
MXL_STATUS MxL251_Ctrl_ReadRegisterMask(UINT8 i2cAddr, UINT16 regAddr, UINT16 mask, UINT16* valPtr);
MXL_STATUS MxL251_Ctrl_SetMpegPadDrv(UINT8 i2cAddr, MXL_DEMOD_ID_E demodId, PMPEG_PAD_DRV_T padDrvPtr);
MXL_STATUS MxL251_Ctrl_SetMpegOutEnable(UINT8 i2cAddr, MXL_DEMOD_ID_E demodId, MXL_BOOL mpegOutEnable);
MXL_STATUS MxL251_Ctrl_GetMpegPadDrv(UINT8 i2cAddr, MXL_DEMOD_ID_E demodId, PMPEG_PAD_DRV_T padDrvPtr);
UINT32     MxL251_Ctrl_SpinOnRegField(UINT8 i2cAddr, UINT16 addr, UINT16 mask, UINT16 value, SPIN_CONDITION_E cond, UINT32 timeoutUs);
UINT16     MxL251_Ctrl_GetRefVCOFreqInMHz(UINT8 i2cAddr);
MXL_STATUS MxL251_Ctrl_SetNewIFLevel(UINT8 i2cAddr, UINT8 ifIndex, UINT16 desiredIFLevel);
MXL_STATUS MxL251_Ctrl_WaitUntilIFLevelRampDone(UINT8 i2cAddr, UINT8 ifIndex);
MXL_STATUS MxL251_Ctrl_NbChanDisable(UINT8 i2cAddr, UINT8 chanId, MXL_BOOL ifRampNeeded);
MXL_STATUS MxL251_Ctrl_WbTunerDisable(UINT8 i2cAddr, UINT8 tunerId, MXL_BOOL disableAna);
MXL_STATUS MxL251_Ctrl_WbTunerEnable(UINT8 i2cAddr, UINT8 tunerId, MXL_TUNER_POWER_MODE_E powerMode, UINT32 WbCapFreqInHz, UINT8 WbCapBwInMHz, MXL_BOOL fastScan);
MXL_STATUS MxL251_Ctrl_MoveWbCenterIfNeeded(PMXL251SF_DEV_CONTEXT_T devContextPtr, UINT8 tunerId, UINT32* wbCapFreqInHzPtr, UINT8* wbCapBwInMHzPtr);
MXL_STATUS MxL251_Ctrl_GetChanXbarEnaRegister(UINT8 i2cAddr, UINT16* regDataPtr);
MXL_STATUS MxL251_Ctrl_ConfigDemodClockEnable(UINT8 i2cAddr, MXL_DEMOD_ID_E demodId, MXL_BOOL enable);
MXL_STATUS MxL251_Ctrl_GetDemodClockEnable(UINT8 i2cAddr, MXL_DEMOD_ID_E demodId, MXL_BOOL* enablePtr);
MXL_STATUS MxL251_Ctrl_ConfigIF(UINT8 i2cAddr, UINT8 chanId, MXL_BOOL IF_Polarity, UINT16 IF_AgcSetPoint, UINT32 IF_FreqInHz);
MXL_STATUS MxL251_Ctrl_ConfigDemodEqualizer(PMXL_SYMBOL_RATE_T symbolRatePtr);
MXL_STATUS MxL251_Ctrl_DeviceStandby(UINT8 i2cAddr);
MXL_STATUS MxL251_Ctrl_TunerStandby(UINT8 i2cAddr);

#ifdef _ENABLE_UART_DEBUG_
MXL_STATUS MxL251_Ctrl_EnableUart(UINT8 i2cAddr);
#endif // _ENABLE_UART_DEBUG_

#ifdef _BOOT_SCAN_ENABLED_
MXL_STATUS MxL251_Ctrl_BootScan(UINT8 i2cAddr, MXL_TUNER_ID_E tunerId, UINT8 WbCapBwInMHz);
#endif // _BOOT_SCAN_ENABLED_

#ifdef _DYNAMIC_VCO_THRESHOLD_ENABLED_
MXL_STATUS MxL251_Ctrl_SetVcoThreshold(UINT8 i2cAddr);
#endif // _DYNAMIC_VCO_THRESHOLD_ENABLED_

#ifdef _MXL_API_DEBUG_ENABLED_
MXL_STATUS MxL251_Ctrl_PrintWithTime(SINT8 *pFormat, ...);
#endif // _MXL_API_DEBUG_ENABLED_

MXL_STATUS MxL251_Ctrl_NbChannelEnable(UINT8 i2cAddr, UINT8 tunerId, UINT8 chanId, UINT8 bandWidthInMHz, UINT32 centerFrequencyInHz, MXL_BOOL IF_Polarity, UINT16 IF_AgcSetPoint, UINT32 IF_FreqInHz);
MXL_STATUS MxL251_Ctrl_ConfigTunerOverwriteDefault(UINT8 i2cAddr);
MXL_STATUS MxL251_Ctrl_UploadCustomCoefs(UINT8 i2cAddr, MXL_DEMOD_ID_E demodId, MXL_ANNEX_TYPE_E annexType, MXL_QAM_TYPE_E qamType);
MXL_STATUS MxL251_Ctrl_GetMCNSSD(UINT8 I2cSlaveAddr, MXL_DEMOD_ID_E demodId, UINT8 regCode, UINT32 *dataPtr);

MXL_STATUS MxL251_GetDemodAllLockStatus(PMXL_DEMOD_ALL_LOCK_STATUS_T cmdPtr);
MXL_STATUS MxL251_Ctrl_DemodInvertSpecrum(UINT8 i2cAddr, MXL_DEMOD_ID_E demodId);
MXL_STATUS MxL251_Ctrl_DemodRestart(UINT8 i2cAddr, MXL_DEMOD_ID_E demodId);

#ifdef _MXL251_FIXEDPOINT_
MXL_STATUS MxL251_Ctrl_10Log(UINT32 in, UINT32* out);   
#else  
MXL_STATUS MxL251_Ctrl_10Log(REAL32 in, REAL32* out); 
#endif 

MXL_STATUS Ctrl_MulDiv32Bit(UINT32 MulData1, UINT32 MulData2, UINT32 DivData, UINT32* RtnVal);
MXL_STATUS Ctrl_Decomp32Bit(UINT32 In, UINT16* b, SINT16* p);
MXL_STATUS Ctrl_SubMulDiv(UINT16 b1,UINT16 b2,UINT16 b3,SINT16 p1,SINT16 p2,SINT16 p3,UINT32 *RetVal);
UINT8 Ctrl_HighBit(UINT32 In);

#ifdef _TUNER_TEST_API_ENABLED_
SINT32 MxL251_Ctrl_ProcessCLICommand(const SINT8* cmdbuf);
#endif // _TUNER_TEST_API_ENABLED_

#ifdef _MXL251_BUILD_
UINT8      MxL251_Ctrl_GetDemodChanId(MXL_TUNER_ID_E tunreId);
UINT8      MxL251_Ctrl_GetIFChanId(MXL_TUNER_ID_E tunreId);
UINT8      MxL251_Ctrl_GetTunerId(UINT8 chanId);
UINT8      MxL251_Ctrl_ConvertDemodIdToChanId(MXL_DEMOD_ID_E demodId);
MXL_DEMOD_ID_E MxL251_Ctrl_GetDemodId(MXL_TUNER_ID_E tunreId);

PMXL251SF_DEV_CONTEXT_T MxL251_Ctrl_GetDeviceContext(UINT8 i2cAddr);
#endif // _MXL251_BUILD_

#endif /* __MXL251SF_PHY_CFG_H__*/

