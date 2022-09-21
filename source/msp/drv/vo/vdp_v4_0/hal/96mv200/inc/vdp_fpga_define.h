#ifndef _VDP_FPGA_DEFINE_H_
#define _VDP_FPGA_DEFINE_H_

#include "hi_type.h"
#include "vdp_define.h"
#define DISP_BASE_ADDRESS 0xf8cc0000UL
#define DISP_INT_NUMBER   122

#if  1
typedef enum tagDISP_VENC_E
{
    DISP_VENC_HDATE0 = 0,
    DISP_VENC_SDATE0,
    DISP_VENC_VGA0,
    DISP_VENC_MAX
}DISP_VENC_E;
#endif

#define CBB_CFG_FROM_PQ 1


//-----------------------------------
//debug define
//-----------------------------------
#define FPGA_DEBUG_TEST             0  //接口debug宽度输出
#define FPGA_PRINT_DEBUG_TEST   0

#define TWOCHN_TEST                 0
#define debug_width                     1008     //1008 // 992   // 1008 //1280//1920 //
#define THRD_LBL                            0
#define FPGA_DEBUG_STEP             0  //step by step
#define FPGA_DOLBY_DEBUG_STEP   0  //step by step for dolby

#define MMU_TEST                        0  //when mmu test ,false 1

#define VDP_TRIGGER_SYNC_TEST     0  //当测试trigger和sync时打开

//反压测试宏
#define VDP_PRESS_TEST          0
//中断机制: 打开宏则是中断触发
#define VDP_INT_TRIGGER         0
//自动比对时打开下面两个宏, 自动比对时不用中断触发方式
#define FPGA_AUTORUN                0
#define FPGA_AUTORUN_CFG        0

#define FPGA_ADDR_AGION         0 //码流发送首地址对齐

#define REG_LOG                 0
#define REG_LOG_ZJY             0

//----------scene & safe test define----------------
#define VDP_SAFE_TEST               0  //safe test on
#define FPGA_SCENE_TEST                   0 // && safe test on
#define FPGA_SCENE_TEST_DATA_SEND_FIRST   0  //reset need to open first time  && safe test on

#define TC_V0_TEST          1
#define TC_V1_TEST          1
#define TC_V3_TEST          1
#define TC_WBC_VP0_TEST     1
#define TC_G0_TEST          1 // 0 // 1
#define TC_G1_TEST          1 // 0 // 1
#define TC_G3_TEST          1 // 0 // 1  //nv200 donot support
#define TC_G4_TEST          1 // 0 // 1
#define TC_WBC_GP0_TEST     1 // 0 // 1
#define TC_WBC_DHD0_TEST    0  //do not open : if wbc_dhd need open , tc has done

//-------------hdr---------------------
#define VDP_HDR_EN                  1

#define HDR_FRAME_NUM               1
#define HDR_ONE_FRAME_STEP_MODE     0//common tc wei 1

#define HDR_FRAME_NUM_120           120
#define HDR_FRAME_NUM_100           100
#define HDR_FRAME_NUM_92            92
#define HDR_FRAME_NUM_25            25
#define HDR_FRAME_NUM_15            15
#define HDR_FRAME_NUM_10            10
//--------------------------------------------------

//物理起始地址
#define VDP_STREAM_PHY_BASE_ADDR ((HI_U32)0x20000000uL)//FPGA  512MB  //mmu use
//#define VDP_STREAM_PHY_BASE_ADDR ((HI_U32)0x08000000uL)//FPGA  128MB    //scene test use and safe test use
//#define VDP_STREAM_PHY_BASE_ADDR ((HI_U32)0x19000000uL)//FPGA  400MB

//安全起始地址    ////region 1 sec,安全内存范围：0x08000000--0x0fffffff
#define VDP_STREAM_PHY_SAFE_BASE_ADDR ((HI_U32)0x08000000uL)//FPGA
//非安全起始地址 ////region 2 nsec,非安全内存范围：0x10000000--0x17ffffff
#define VDP_STREAM_PHY_NOSAFE_BASE_ADDR ((HI_U32)0x10000000uL)//FPGA

#define W_4096      4096
#define W_2160P     3840
#define W_3616      3616
#define H_2112      2112
#define H_2160P     2160
#define W_1600P     2560
#define H_1600P     1600
#define W_1080P     1920
#define H_1080P     1080
#define W_720P      1280
#define H_720P      720
#define W_D1        720
#define H_D1        480
#define W_576P      720
#define H_576P      576
#define W_576I      720
#define H_576I      576
#define W_480P      720
#define H_480P      480
#define W_HVGA      480
#define H_HVGA      320
#define W_CIF       352
#define H_CIF       288
#define W_QCIF      176
#define H_QCIF      144
#define H_SUBT      120
#define W_HC        128
#define H_HC        128

#define W_VGA       640
#define H_VGA       480

#define W_VDP_COMB_MAX      1280
#define H_VDP_COMB_MAX      720
#define W_VDP_COMB_MIN      240
#define H_VDP_COMB_MIN      160

#define    VDP_DISP_DIGFMT_TMP          VDP_DISP_DIGFMT_1080P_24
#define    VDP_DISP_DIGFMT_TMP_I        VDP_DISP_DIGFMT_PAL
#define    VDP_DISP_DIGFMT_TMP_DHD0_I   VDP_DISP_DIGFMT_1080I50

//#define VDP_HI3798CV200     1
#define VDP_BUF_ADDR        VDP_STREAM_PHY_BASE_ADDR
#define VDP_BUF_SIZE        0x5000000
#define VDP_BUF_STRIDE      0x08000000
//add for scene test vid buf stride : 4k 422 : 18M
#define VDP_VID_BUF_STRIDE  0x01400000//20M
#define VDP_GFX_BUF_SIZE    0x01000000L  // 16M

//-----------------------------------------------------------------------
//add safe test
#define VDP_VID_SAFE_BUF_ADDR       VDP_STREAM_PHY_SAFE_BASE_ADDR
#define VDP_VID_BUF_SAFE_STRIDE     0x500000//5M
#define VDP_GFX_SAFE_BUF_ADDR       VDP_VID_SAFE_BUF_ADDR + 4 * VDP_VID_BUF_SAFE_STRIDE
#define VDP_GFX_BUF_SAFE_STRIDE     0x500000//5M
#define VDP_WBCDHD_SAFE_BUF_ADDR    VDP_GFX_SAFE_BUF_ADDR + 4 * VDP_GFX_BUF_SAFE_STRIDE
#define VDP_WBCVP_SAFE_BUF_ADDR     VDP_WBCDHD_SAFE_BUF_ADDR + 5 * VDP_GFX_BUF_SAFE_STRIDE
#define VDP_WBCGP_SAFE_BUF_ADDR     VDP_WBCVP_SAFE_BUF_ADDR + 5 * VDP_GFX_BUF_SAFE_STRIDE

#define VDP_VID_NOSAFE_BUF_ADDR     VDP_STREAM_PHY_NOSAFE_BASE_ADDR
#define VDP_VID_NOBUF_SAFE_STRIDE   0x500000//5M
#define VDP_GFX_NOSAFE_BUF_ADDR     VDP_VID_NOSAFE_BUF_ADDR + 4 * VDP_VID_NOBUF_SAFE_STRIDE
#define VDP_GFX_NOBUF_SAFE_STRIDE   0x500000//5M
#define VDP_WBCDHD_NOSAFE_BUF_ADDR  VDP_GFX_NOSAFE_BUF_ADDR + 4 * VDP_GFX_NOBUF_SAFE_STRIDE
#define VDP_WBCVP_NOSAFE_BUF_ADDR   VDP_WBCDHD_NOSAFE_BUF_ADDR + 5 * VDP_GFX_NOBUF_SAFE_STRIDE
#define VDP_WBCGP_NOSAFE_BUF_ADDR   VDP_WBCVP_NOSAFE_BUF_ADDR + 5 * VDP_GFX_NOBUF_SAFE_STRIDE
//-----------------------------------------------------------------------------

//gfx
#if FPGA_SCENE_TEST
   #define VDP_GFX_BUF_ADDR     (VDP_BUF_ADDR + 16 * VDP_VID_BUF_STRIDE)   //0x32C00000
#else
   #define VDP_GFX_BUF_ADDR     (VDP_BUF_ADDR + 10 * VDP_VID_BUF_STRIDE)   //0x32C00000
#endif

//#define VDP_WBC_BUF_ADDR  (VDP_GFX_BUF_ADDR + 1*VDP_BUF_STRIDE)
#define VDP_WBC_BUF_ADDR            (VDP_GFX_BUF_ADDR + 10 * VDP_GFX_BUF_SIZE)   //0x41C00000
#define VDP_WBC_BUF_STRIDE          0x01000000L
#define VDP_WBC_DHD0_BUF_ADDR       (VDP_GFX_BUF_ADDR + 10 * VDP_GFX_BUF_SIZE)    //0x41C00000
#define VDP_WBC_VP0_BUF_ADDR        (VDP_WBC_DHD0_BUF_ADDR + 4 * VDP_WBC_BUF_STRIDE)   //0x41C00000
#define VDP_WBC_GP0_BUF_ADDR        (VDP_WBC_VP0_BUF_ADDR + 4 * VDP_WBC_BUF_STRIDE)   //0x41C00000

#define VDP_GFX_ACLUT_BUF_ADDR      (VDP_BUF_ADDR + 3*VDP_BUF_SIZE)

#define VDP_TILE_BUF_ADDR           (VDP_WBC_BUF_ADDR + 3*VDP_BUF_STRIDE)
#define VDP_FLIP_BUF_ADDR           (VDP_WBC_BUF_ADDR + 5*VDP_BUF_STRIDE)
#define VDP_TNR_BUF_ADDR            (VDP_FLIP_BUF_ADDR + 0*VDP_BUF_STRIDE)
#define VDP_TNR_DCMP_BUF_ADDR       (VDP_FLIP_BUF_ADDR + 2*VDP_BUF_STRIDE)
#define VDP_DBDETECT_BUF_ADDR       (VDP_FLIP_BUF_ADDR + 1*VDP_BUF_STRIDE)
#define VDP_WBC_STT_BUF_ADDR        (VDP_DBDETECT_BUF_ADDR + 1*VDP_BUF_STRIDE)

#define DBM_CFG_ADDR                (VDP_WBC_BUF_ADDR + 4*VDP_BUF_STRIDE)

#define VGA_MUX  0
//#define OPTM_STREAM_MAX_SIZE 0x6000000L

//VOU系统时钟控制寄存器
//System control 寄存器
#define OPTM_REGS_VDP_SYS_SET   0xf8a220d8

//VOU PLL 寄存器
#define OPTM_REGS_HPLL01_SET    0xF8A22028
#define OPTM_REGS_HPLL02_SET    0xF8A2202C

#define HI_OPTM_PRINT(fmt...) printk(fmt)

//vdp check sum
#define VDP_CHK_ADDR_DHD0       VDP_BASE_ADDR+ 0xc368
#define VDP_CHK_ADDR_DHD0_1     VDP_BASE_ADDR+ 0xc374
#define VDP_CHK_ADDR_DHD1       VDP_BASE_ADDR+ 0xc768
#define VDP_CHK_ADDR_DSD0       VDP_BASE_ADDR+ 0xd3f0
#define VDP_CHK_ADDR_WBCDHD0    VDP_BASE_ADDR + 0x90f0
#define VDP_CHK_ADDR_WBCVP0     VDP_BASE_ADDR + 0x9cf0
#define VDP_CHK_ADDR_WBCGP0     VDP_BASE_ADDR + 0x94f0

#define MAX_SUM ((3+2*3)*CHN_MAX)
#define OPTM_AA_ACC_COEF_NUM 256
#define OPTM_AA_ACC_TABLE_SIZE 45
#define OPTM_AA_GMM_COEF_NUM 257*3

#define   HI_SUCCESS          0
#define   HI_FAILURE          (-1)

//VOU寄存器列表物理基地址
#define OPTM_REGS_BASE_ADDR   0xf8cc0000

//VOU系统时钟控制寄存器

//VOU hpll cfg  寄存器
#define VDP_PLL_REG_BASE_ADDR0  0xF8A22028
#define VDP_PLL_REG_BASE_ADDR1  0xF8A2202c
#define VDP_PLL_REG_BASE_ADDR2  0xF8A220d8

//VOU VO_HD 寄存器
#define OPTM_REGS_VO_HD_SET 0xF8A22028
//VOU IO_CONFIG 寄存器
#define OPTM_REGS_IO_CONFIG_SET 0xF8A22028
//VOU perl ctrl 寄存器
#define OPTM_REGS_PERL_SET  0xF8A22028

//VOU perl ctrl  0D 寄存器
#define OPTM_REGS_PERL_0D_SET  0xF8A22028

#define LoopNumBreak  1


typedef enum tagVDP_RM_LAYER_E
{
    VDP_RM_LAYER_VID0 = 0,
    VDP_RM_LAYER_VID1,
    VDP_RM_LAYER_VID2,
    VDP_RM_LAYER_VID3,
    VDP_RM_LAYER_VID4,
    VDP_RM_LAYER_GFX0,
    VDP_RM_LAYER_GFX1,
    VDP_RM_LAYER_GFX2,
    VDP_RM_LAYER_GFX3,
    VDP_RM_LAYER_GFX4,
    VDP_RM_LAYER_WBC_HD0,
    VDP_RM_LAYER_WBC_GP0,
    VDP_RM_LAYER_GP0,
    VDP_RM_LAYER_GP1,
    VDP_RM_LAYER_VP0,
    VDP_RM_LAYER_TT,

} VDP_RM_LAYER_E;
#endif
