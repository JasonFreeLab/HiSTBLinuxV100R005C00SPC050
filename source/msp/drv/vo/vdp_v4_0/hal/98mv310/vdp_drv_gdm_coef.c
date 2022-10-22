// *****************************************************************************
//
// Copyright(c) 2015,Hisilicon Technologies Co., Ltd.
// All Rights Reserved
//
// Project name : VDP  
// File Name    : coef.cpp
// Author       : sdk
// Date         : 2015/7/17
//
// Module Name  : COEF.CPP
// -----------------------------------------------------------------------------
// Abstract     :
//code_template.v*
// 
// *****************************************************************************
// Called By    : TOP
// Modification History
// -----------------------------------------------------------------------------
// $Log :     $
//
//
// --=========================================================================--


#include "vdp_drv_vdm_coef.h"
//#include "vdm_process.h"
#include "vdp_drv_coef.h"
#include "vdp_define.h"
#include "vdp_fpga_define.h"
#include "vdp_hal_comm.h"
#include "vdp_hal_ip_vdm.h"
#include "VdpHiHDR_cfg.h"
#include "vdp_drv_comm.h"
#include "vdp_drv_ip_gdm.h"
#define VDP_COEF_COMPILE


#ifdef VDP_COEF_COMPILE

extern HI_U32 GdmtcLut[64];
extern HI_U32 GdmtcLut_New[64];
extern HI_U32 GdmtcLut_1[32];
extern HI_U32 GdmtcLut_New_1[32];
extern HI_U32 GdmtcLut_2[64];
extern HI_U32 GdmtcLut_New_2[64];

#endif 
HI_U32 u32GdmTMLutSDR2BBC[32] = {				   //U8.8 [0,65535]
	256,
	256,
	256,
	256,
	256,
	256,
	256,
	256,
	256,
	256,
	256,
	256,
	256,
	256,
	256,
	256,
	256,
	256,
	256,
	256,
	256,
	256,
	256,
	256,
	256,
	256,
	256,
	256,
	256,
	256,
	256,
	256
};

HI_U32 u32GdmGmmLutHLG7[64] =              //U12.0 [0,4095]
{
    0,
    21,
    30,
    37,
    42,
    60,
    73,
    85,
    95,
    104,
    112,
    120,
    147,
    169,
    207,
    239,
    268,
    293,
    339,
    379,
    415,
    448,
    479,
    586,
    677,
    757,
    829,
    896,
    958,
    1016,
    1071,
    1123,
    1173,
    1221,
    1267,
    1311,
    1354,
    1514,
    1659,
    1792,
    1915,
    2031,
    2138,
    2231,
    2313,
    2387,
    2454,
    2516,
    2573,
    2625,
    2675,
    2721,
    2764,
    2916,
    3041,
    3148,
    3242,
    3324,
    3399,
    3466,
    3528,
    3585,
    3638,
    3687
};
HI_U32 u32GdmHLGLut[64] = {            //U12.0 [0,4095]
	0	,
	28	,
	39	,
	48	,
	55	,
	78	,
	96	,
	111	,
	124	,
	136	,
	147	,
	157	,
	192	,
	222	,
	271	,
	313	,
	350	,
	384	,
	443	,
	496	,
	543	,
	586	,
	627	,
	768	,
	887	,
	991	,
	1086,
	1173,
	1254,
	1330,
	1402,
	1470,
	1536,
	1598,
	1659,
	1717,
	1773,
	1982,
	2165,
	2313,
	2436,
	2541,
	2633,
	2714,
	2788,
	2854,
	2916,
	2972,
	3024,
	3073,
	3119,
	3162,
	3203,
	3346,
	3466,
	3569,
	3660,
	3740,
	3812,
	3878,
	3939,
	3995,
	4047,
	4095
};

static const HI_U32 u32TMLutSDR2HDR10[32] = {                   //U2.14 [0,65535] PQLut500
    13107,
    13107,
    13107,
    13107,
    13107,
    13107,
    13107,
    13107,
    13107,
    13107,
    13107,
    13107,
    13107,
    13107,
    13107,
    13107,
    13107,
    13107,
    13107,
    13107,
    13107,
    13107,
    13107,
    13107,
    13107,
    13107,
    13107,
    13107,
    13107,
    13107,
    13107,
    13107
};
static const HI_U32 u32TMLutSDR2HDR10_1[32] = {                   //U2.14 [0,65535] PQLut500
    3636 ,
    4175 ,
    4685 ,
    5163 ,
    5609 ,
    6025 ,
    6409 ,
    6762 ,
    7083 ,
    7374 ,
    7633 ,
    7861 ,
    8057 ,
    8223 ,
    8359 ,
    8472 ,
    8566 ,
    8712 ,
    8820 ,
    8902 ,
    8967 ,
    9021 ,
    9069 ,
    9112 ,
    9150 ,
    9278 ,
    9382 ,
    9586 ,
    9910 ,
    10502,
    11534,
    13107
};

static const HI_U32 u32TMLutSDR2HDR10_2[32] = {                   //U2.14 [0,65535] PQLut500
    3503 ,
    3937 ,
    4350 ,
    4740 ,
    5108 ,
    5453 ,
    5776 ,
    6076 ,
    6353 ,
    6608 ,
    6841 ,
    7051 ,
    7239 ,
    7404 ,
    7548 ,
    7675 ,
    7787 ,
    7976 ,
    8131 ,
    8259 ,
    8365 ,
    8454 ,
    8530 ,
    8594 ,
    8650 ,
    8824 ,
    8960 ,
    9227 ,
    9545 ,
    10083,
    11199,
    13107
};
static const HI_U32 u32TMLutSDR2HDR10_3[32] = {                   //U2.14 [0,65535] PQLut500
    3370 ,
    3700 ,
    4016 ,
    4318 ,
    4606 ,
    4881 ,
    5142 ,
    5390 ,
    5623 ,
    5843 ,
    6049 ,
    6242 ,
    6421 ,
    6586 ,
    6737 ,
    6878 ,
    7008 ,
    7240 ,
    7442 ,
    7615 ,
    7763 ,
    7887 ,
    7990 ,
    8077 ,
    8151 ,
    8369 ,
    8537 ,
    8869 ,
    9179 ,
    9664 ,
    10865,
    13107
};

static const HI_U32 u32TMLutSDR2BBC[32] = {                   //U2.14 [0,65535]
    16384,
    16384,
    16384,
    16384,
    16384,
    16384,
    16384,
    16384,
    16384,
    16384,
    16384,
    16384,
    16384,
    16384,
    16384,
    16384,
    16384,
    16384,
    16384,
    16384,
    16384,
    16384,
    16384,
    16384,
    16384,
    16384,
    16384,
    16384,
    16384,
    16384,
    16384
};

HI_U32 u32GdmTMLut[32] = {//U8.8 [0,65535]
4160,
4160,
4160,
4160,
4160,
4160,
3771,
3418,
3134,
2899,
2700,
2531,
2383,
2254,
2140,
2038,
1946,
1788,
1638,
1489,
1365,
1260,
1170,
1092,
1024,
819	,
683	,
512	,
410	,
341	,
293	,
256
};

HI_U32 u32GdmPQLut[64] = {            //U12.0 [0,4095]
	205	,
	264	,
	320	,
	370	,
	420	,
	657	,
	749	,
	820	,
	878	,
	927	,
	970	,
	1008,
	1129,
	1220,
	1354,
	1454,
	1533,
	1600,
	1708,
	1794,
	1865,
	1926,
	1980,
	2146,
	2267,
	2361,
	2440,
	2506,
	2564,
	2616,
	2662,
	2704,
	2742,
	2777,
	2810,
	2841,
	2869,
	2969,
	3050,
	3119,
	3178,
	3231,
	3278,
	3321,
	3360,
	3395,
	3428,
	3459,
	3488,
	3515,
	3540,
	3564,
	3587,
	3668,
	3736,
	3794,
	3846,
	3892,
	3933,
	3971,
	4006,
	4038,
	4067,
	4095
};

HI_U32 u32GdmPQLut2500[64] = {            //U12.0 [0,4095]
	0	,
	167	,
	227	,
	270	,
	304	,
	400	,
	466	,
	517	,
	559	,
	596	,
	628	,
	657	,
	749	,
	820	,
	927	,
	1008,
	1074,
	1129,
	1220,
	1293,
	1354,
	1407,
	1454,
	1600,
	1708,
	1794,
	1865,
	1926,
	1980,
	2028,
	2071,
	2110,
	2146,
	2179,
	2210,
	2239,
	2267,
	2361,
	2440,
	2506,
	2564,
	2616,
	2662,
	2704,
	2742,
	2777,
	2810,
	2841,
	2869,
	2896,
	2922,
	2946,
	2969,
	3050,
	3119,
	3178,
	3231,
	3278,
	3321,
	3360,
	3395,
	3428,
	3459,
	3488,
};
static const HI_U32 u32PQLut500[64] = {            //U12.0 [0,4095]
    0   ,
    77  ,
    108 ,
    132 ,
    151 ,
    206 ,
    246 ,
    278 ,
    304 ,
    327 ,
    348 ,
    367 ,
    429 ,
    477 ,
    551 ,
    609 ,
    657 ,
    697 ,
    765 ,
    820 ,
    867 ,
    908 ,
    945 ,
    1061,
    1149,
    1220,
    1279,
    1331,
    1376,
    1417,
    1454,
    1487,
    1519,
    1548,
    1575,
    1600,
    1624,
    1708,
    1778,
    1838,
    1891,
    1938,
    1980,
    2019,
    2054,
    2087,
    2118,
    2146,
    2173,
    2198,
    2222,
    2245,
    2267,
    2344,
    2410,
    2467,
    2518,
    2564,
    2606,
    2644,
    2679,
    2712,
    2742,
    2771
};

static const HI_U32 u32PQLut1000[64] = {            //U12.0 [0,4095]
    0   ,
    108 ,
    151 ,
    181 ,
    206 ,
    278 ,
    327 ,
    367 ,
    400 ,
    429 ,
    454 ,
    477 ,
    551 ,
    609 ,
    697 ,
    765 ,
    820 ,
    867 ,
    945 ,
    1008,
    1061,
    1108,
    1149,
    1279,
    1376,
    1454,
    1519,
    1575,
    1624,
    1668,
    1708,
    1744,
    1778,
    1809,
    1838,
    1865,
    1891,
    1980,
    2054,
    2118,
    2173,
    2222,
    2267,
    2307,
    2344,
    2378,
    2410,
    2440,
    2467,
    2494,
    2518,
    2542,
    2564,
    2644,
    2712,
    2771,
    2823,
    2869,
    2912,
    2950,
    2986,
    3019,
    3050,
    3079
};

extern VDP_COEF_ADDR_S gstVdpCoefBufAddr;


HI_VOID Vdp_Drv_SetGdmCoef_Tmmp(GDM_SCENE_MODE_E   enHiHdrGfxMode)
{
#ifdef VDP_COEF_COMPILE

#if UT_TEST
	HI_U32 addr = 0;

#else
	HI_U8  *addr	= gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_GDM_TONEMAP] ;//add by hyx
#endif

    VDP_COEF_SEND_CFG   stCoefSend;
    

	HI_S32 tcLut_s32_1[32];

    void*  p_coef_array[]    = {tcLut_s32_1};
    HI_U32 lut_length[]      = {32};
    HI_U32 coef_bit_length[] = {16};

    FILE*   fp_hihdr_gdm_tmmp_coef=NULL;    

    //bOpenStiFile(STI_FILE_COEF_VDM);
	VDP_GP_SetGdmGdmParaTmapAddr (VDP_LAYER_GP0,	   gstVdpCoefBufAddr.u32CoefPhyAddr[VDP_COEF_BUF_GDM_TONEMAP]);
	
	
    if(enHiHdrGfxMode == GDM_SDR_IN_HDR10_OUT)
    {
        //VDP_PRINT("ToneMapping Coef : GdmSceneMode == GDM_SDR_IN_HDR10_OUT\n");
        p_coef_array[0]         = (HI_S32 *)u32TMLutSDR2HDR10_1;
    }
    else  if (enHiHdrGfxMode == GDM_SDR_IN_HLG_OUT)
    {
        //VDP_PRINT("ToneMapping Coef : GdmSceneMode == GDM_SDR_IN_HDR10_OUT\n");
        p_coef_array[0]         = (HI_S32 *)u32TMLutSDR2HDR10_1;
    }
    else if (enHiHdrGfxMode == GDM_SDR_IN_BBC_OUT)
    {
        //VDP_PRINT("ToneMapping Coef : GdmSceneMode == GDM_SDR_IN_BBC_OUT\n");
        p_coef_array[0]         = (HI_S32 *)u32GdmTMLutSDR2BBC;
    }
    else
    {
        //VDP_PRINT("ToneMapping Coef : GdmSceneMode == Default !\n");
        p_coef_array[0]         = (HI_S32*)u32GdmTMLut;//tcLut_1;
    }

	stCoefSend.coef_addr         = addr                     ; 
    stCoefSend.sti_type          = STI_FILE_COEF_DM        ; 
    stCoefSend.fp_coef           = fp_hihdr_gdm_tmmp_coef              ; 
    stCoefSend.lut_num           = 1              ; 
    stCoefSend.burst_num         = 1            ; 
    stCoefSend.cycle_num         = 8            ; 
    stCoefSend.p_coef_array      = p_coef_array        		; 
    stCoefSend.lut_length        = lut_length               ; 
    stCoefSend.coef_bit_length   = coef_bit_length          ;
    stCoefSend.data_type         = COEF_DATA_TYPE_S32       ; 
	
    VDP_FUNC_SendCoef(&stCoefSend);
	VDP_GP_SetGdmGdmParaTmapUpd 	(VDP_LAYER_GP0, 1);

#endif

}


HI_VOID Vdp_Drv_SetGdmCoef_Gmma(GDM_SCENE_MODE_E   enHiHdrGfxMode)
{
#ifdef VDP_COEF_COMPILE

#if UT_TEST
	HI_U32 addr = 0;

#else
	HI_U8  *addr	= gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_GDM_GAMMA2] ;//add by hyx
#endif

    VDP_COEF_SEND_CFG   stCoefSend;
    

	HI_S32 tcLut_s32_1[64];
    void*  p_coef_array[]    = {tcLut_s32_1};
    HI_U32 lut_length[]      = {64};
    HI_U32 coef_bit_length[] = {12};

    FILE*   fp_hihdr_gdm_gamma_coef = NULL;    

    //bOpenStiFile(STI_FILE_COEF_VDM);
	VDP_GP_SetGdmGdmParaGmmAddr  (VDP_LAYER_GP0,		gstVdpCoefBufAddr.u32CoefPhyAddr[VDP_COEF_BUF_GDM_GAMMA2]);
	
	
    if(enHiHdrGfxMode == GDM_SDR_IN_HDR10_OUT)
    {
        VDP_PRINT("ToneMapping Coef : GdmSceneMode == GDM_SDR_IN_HDR10_OUT\n");
        p_coef_array[0]         = (HI_S32*)u32PQLut500;
    }
    else if(enHiHdrGfxMode == GDM_SDR_IN_BBC_OUT)
    {
        VDP_PRINT("ToneMapping Coef : GdmSceneMode == GDM_SDR_IN_BBC_OUT\n");
        p_coef_array[0]         = (HI_S32*)u32GdmHLGLut;
    }
    else if (enHiHdrGfxMode == GDM_SDR_IN_HLG_OUT)
    {
        VDP_PRINT("ToneMapping Coef : GdmSceneMode == GDM_SDR_IN_HLG_OUT\n");
        p_coef_array[0]         = (HI_S32 *)u32GdmGmmLutHLG7;
    }
    else
    {
        VDP_PRINT("ToneMapping Coef : GdmSceneMode == Default !\n");
        p_coef_array[0]         = (HI_S32*)u32GdmPQLut;//tcLut_1;
    }

	stCoefSend.coef_addr         = addr                     ; 
    stCoefSend.sti_type          = STI_FILE_COEF_DM        ; 
    stCoefSend.fp_coef           = fp_hihdr_gdm_gamma_coef              ; 
    stCoefSend.lut_num           = 1              ; 
    stCoefSend.burst_num         = 1            ; 
    stCoefSend.cycle_num         = 10            ; 
    stCoefSend.p_coef_array      = p_coef_array        		; 
    stCoefSend.lut_length        = lut_length               ; 
    stCoefSend.coef_bit_length   = coef_bit_length          ;
    stCoefSend.data_type         = COEF_DATA_TYPE_S32       ; 
	
    VDP_FUNC_SendCoef(&stCoefSend);
	VDP_GP_SetGdmGdmParaGmmUpd		(VDP_LAYER_GP0, 1);

#endif

}









