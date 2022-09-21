/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hal_hi1102_cali_dpd.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2015年05月22日
  最近修改   :
  功能描述   : hi1102 校准模块功能接口定义
  函数列表   :
  修改历史   :
  1.日    期   : 2015年05月22日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_RF_110X_CALI_DPD
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "hmac_cali_dpd.h"
#include "oam_ext_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_CALI_DPD_C

/*****************************************************************************
  2 函数声明
*****************************************************************************/
#define GET2COMP(a) (a >= 1024) ? (a-2048) : (a)
#define SET2COMP(a) (a >= 0) ? (a) : (2048 + a)
#define absd(a)     (a >= 0) ? (a) : (-a)


oal_int64 g_ll_mk1_32[3][128] = {
	{
		297,	869,	1414,	1931,	2423,	2888,	3328,	3742,	4132,	4498,	4840,	5158,	5454,	5727,	5979,	6209,	6418,\
		6607,	6775,	6924,	7054,	7165,	7258,	7333,	7391,	7432,	7457,	7466,	7459,	7437,	7401,	7351,	7287,	7210, \
		7121,	7019,	6906,	6781,	6645,	6499,	6343,	6178,	6004,	5821,	5630,	5431,	5226,	5014,	4795,	4571,	4341,\
		4107,	3868,	3626,	3380,	3131,	2879,	2626,	2370,	2114,	1857,	1600,	1343,	1087,	832,	578,	327,	78,	-167,\
		-410,	-648,	-882,	-1111,	-1334,	-1552,	-1764,	-1969,	-2166,	-2357,	-2539,	-2712,	-2876,	-3031,	-3176,	-3311,	-3434, \
		-3547,	-3647,	-3736,	-3811,	-3874,	-3922,	-3957,	-3977,	-3982,	-3972,	-3946,	-3903,	-3843,	-3766,	-3671,	-3558,	-3427,\
		-3276,	-3105,	-2915,	-2703,	-2471,	-2217,	-1942,	-1644,	-1323,	-978,	-610,	-218,	199,	641,	1109,	1603,	2124,\
		2671,	3246,	3849,	4481,	5141,	5830,	6550,	7300,
	},
	{
		-889,	-2600,	-4224,	-5761,	-7214,	-8584,	-9872,	-11080,	-12209,	-13262,	-14239,	-15142,	-15973,	-16733,	-17424,	-18047,	-18605,\
		-19097,	-19526,	-19894,	-20202,	-20451,	-20643,	-20780,	-20863,	-20894,	-20873,	-20804,	-20687,	-20524,	-20316,	-20065,	-19772,	-19440,\
		-19068,	-18660,	-18217,	-17740,	-17230,	-16690,	-16120,	-15523,	-14899,	-14251,	-13579,	-12887,	-12174,	-11442,	-10694,	-9930,	-9153,\
		-8363,	-7562,	-6752,	-5935,	-5111,	-4282,	-3451,	-2618,	-1785,	-953,	-124,	699,	1517,	2327,	3128,	3918,	4696,\
		5460,	6209,	6941,	7654,	8347,	9019,	9668,	10292,	10890,	11461,	12002,	12512,	12990,	13434,	13843,	14215,	14549,\
		14842,	15094,	15303,	15468,	15586,	15656,	15678,	15648,	15566,	15431,	15240,	14992,	14686,	14319,	13891,	13400,	12845,\
		12223,	11534,	10775,	9946,	9045,	8069,	7018,	5891,	4684,	3398,	2030,	580,	-956,	-2577,	-4286,	-6085,	-7974,\
		-9956,	-12031,	-14202,	-16469,	-18835,	-21301,	-23869,	-26540,	-29315,
	},
	{
		622,	1817,	2949,	4017,	5025,	5971,	6859,	7688,	8460,	9176,	9838,	10446,	11002,	11506,	11961,	12366,	12724,\
		13035,	13301,	13522,	13701,	13837,	13932,	13988,	14005,	13985,	13929,	13837,	13712,	13554,	13364,	13144,	12895,	12617,\
		12312,	11982,	11627,	11248,	10847,	10425,	9983,	9522,	9043,	8547,	8036,	7511,	6973,	6422,	5861,	5290,	4710,\
		4124,	3531,	2933,	2331,	1726,	1119,	513,	-94,	-698,	-1299,	-1896,	-2488,	-3073,	-3651,	-4219,	-4778,	-5326,\
		-5862,	-6384,	-6891,	-7383,	-7858,	-8315,	-8753,	-9171,	-9567,	-9940,	-10290,	-10614,	-10913,	-11184,	-11427,	-11640,	-11823,\
		-11974,	-12092,	-12175,	-12223,	-12235,	-12209,	-12145,	-12040,	-11894,	-11706,	-11475,	-11199,	-10877,	-10509,	-10092,	-9627,	-9111,\
		-8543,	-7923,	-7249,	-6520,	-5735,	-4893,	-3992,	-3032,	-2011,	-928,	218,	1428,	2703,	4045,	5454,	6933,	8481,\
		10100,	11792,	13557,	15396,	17312,	19304,	21374,	23523,	25753,
	},
};

hi1102_complex_stru g_ll_pa_val[128] = {
    {1, 0},
    {5, -1},
    {8, -3},
    {12, -4},
    {15, -5},
    {18, -6},
    {22, -7},
    {26, -8},
    {29, -9},
    {33, -11},
    {36, -12},
    {40, -13},
    {43, -14},
    {46, -15},
    {50, -16},
    {53, -18},
    {57, -19},
    {60, -20},
    {64, -21},
    {67, -22},
    {71, -24},
    {74, -25},
    {77, -26},
    {81, -27},
    {84, -28},
    {88, -29},
    {91, -31},
    {94, -32},
    {98, -33},
    {101, -34},
    {105, -35},
    {108, -37},
    {111, -38},
    {115, -39},
    {118, -40},
    {121, -42},
    {124, -43},
    {128, -44},
    {131, -45},
    {135, -46},
    {138, -47},
    {141, -49},
    {144, -50},
    {147, -51},
    {151, -52},
    {154, -53},
    {157, -55},
    {160, -56},
    {164, -57},
    {167, -58},
    {170, -59},
    {173, -60},
    {176, -61},
    {180, -63},
    {183, -64},
    {187, -65},
    {190, -66},
    {193, -67},
    {196, -68},
    {200, -69},
    {203, -70},
    {206, -71},
    {210, -72},
    {213, -73},
    {216, -75},
    {220, -75},
    {223, -76},
    {227, -78},
    {230, -79},
    {234, -80},
    {238, -81},
    {241, -82},
    {245, -83},
    {248, -84},
    {251, -85},
    {255, -86},
    {259, -87},
    {262, -89},
    {266, -90},
    {270, -91},
    {273, -92},
    {277, -93},
    {281, -94},
    {284, -96},
    {288, -97},
    {292, -98},
    {296, -100},
    {300, -101},
    {304, -102},
    {307, -103},
    {311, -104},
    {316, -105},
    {319, -107},
    {323, -108},
    {327, -109},
    {331, -111},
    {335, -112},
    {339, -114},
    {343, -115},
    {347, -116},
    {351, -118},
    {355, -119},
    {359, -121},
    {363, -122},
    {367, -123},
    {371, -125},
    {375, -126},
    {380, -128},
    {384, -129},
    {388, -131},
    {392, -132},
    {396, -134},
    {400, -135},
    {404, -137},
    {409, -138},
    {413, -140},
    {417, -142},
    {421, -143},
    {425, -144},
    {429, -146},
    {433, -148},
    {437, -149},
    {441, -151},
    {445, -153},
    {449, -154},
    {453, -156},
    {457, -157},
    {460, -159},
};

oal_uint16 g_us_max_pos = 128;
oal_uint32 g_ul_dpd_data[128]; /*dpd calibration data*/

/*****************************************************************************
 函 数 名  : hi1102_cali_get_phase
 功能描述  : 两整数相除结果四舍五入
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
// do_div(temp, 1024)
oal_int64 hmac_cali_div_round_closest(oal_int64 ll_a, oal_int64 ll_b)
{
    oal_int64 ll_result = 0;
    if ((0 == ll_b) || (0 == (ll_b << 1)))
    {
        ll_result = (oal_int64)ll_a;
    }
    else
    {
        if (((ll_a >= 0) && (ll_b > 0)) || ((ll_a <=0) && (ll_b < 0)))
        {
            ll_result = (oal_int64)(((ll_a << 1) + ll_b) / (ll_b << 1));
        }
        else
        {
            ll_result = (oal_int64)(((ll_a << 1) - ll_b) / (ll_b << 1));
        }
    }

    return ll_result;
}

/*****************************************************************************
 函 数 名  : hi1102_cali_get_phase
 功能描述  : 复数除以整数结果四舍五入
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
hi1102_complex_stru hmac_cali_complex_div_round_closest(hi1102_complex_stru st_a, oal_int64 ll_b)
{
	hi1102_complex_stru st_result;

	st_result.ll_real = hmac_cali_div_round_closest(st_a.ll_real, ll_b);
	st_result.ll_imag = hmac_cali_div_round_closest(st_a.ll_imag, ll_b);

    return st_result;
}

/*****************************************************************************
 函 数 名  : dpd_cordic
 功能描述  : DPD Calibration Data Cordic
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
void hmac_dpd_cordic(oal_int64 ll_real, oal_int64 ll_image, oal_int64* pll_amp, oal_int64* pll_theta1, oal_int64* pll_theta2)
{
   unsigned char  us_idx = 0;
   oal_int64   ll_x[13] = {0}, ll_y[13] = {0};
   oal_int64   ll_flag =0;

   oal_int64   ll_real_table[13] = {1447, 1891, 2008, 2037, 2045, 2046, 2047, 2047, 2047, 2047, 2047, 2047, 2047},
               ll_imag_table[13] = {1447, 783, 399, 201, 100, 50, 25, 13, 6, 3, 2, 1, 0};

   oal_int64   ll_theta1 = 2047, ll_theta2 = 0;
   oal_int64   ll_temp1 = 0, ll_temp2 = 0; /* real and image*/
   oal_int64   ll_thetatmp1 = 0, ll_thetatmp2 = 0;/* real and image*/
   oal_int64   ll_divider = 2048;


   ll_x[0] = absd(ll_real);
   ll_y[0] = absd(ll_image);
   ll_flag = absd(ll_image);

   for (us_idx = 0; us_idx < 10; us_idx++)
   {
     if (ll_flag > 0)
     {
        ll_temp1 = ll_real_table[us_idx] ;
        ll_temp2 = - ll_imag_table[us_idx];
     }
     else if (ll_flag < 0)
     {
        ll_temp1 = ll_real_table[us_idx];
        ll_temp2 = ll_imag_table[us_idx];
     }
     else/*y=0*/
     {
        break;
     }

     ll_x[us_idx + 1] = hmac_cali_div_round_closest((ll_x[us_idx] * ll_temp1 - ll_y[us_idx] * ll_temp2), ll_divider);
     ll_y[us_idx + 1] = hmac_cali_div_round_closest((ll_y[us_idx] * ll_temp1 + ll_x[us_idx] * ll_temp2), ll_divider);

     ll_thetatmp1 = hmac_cali_div_round_closest((ll_theta1 * ll_temp1 - ll_theta2 * ll_temp2), ll_divider);;
     ll_thetatmp2 = hmac_cali_div_round_closest((ll_theta2 * ll_temp1 + ll_theta1 * ll_temp2), ll_divider);
     ll_theta1 = ll_thetatmp1;
     ll_theta2 = ll_thetatmp2;

     ll_flag =  ll_y[us_idx + 1];
   }

   if (ll_real  < 0)  { ll_theta1 = - ll_theta1; }
   if (ll_image < 0)  { ll_theta2 = - ll_theta2; }

   *pll_amp = (unsigned int)ll_x[us_idx];
   *pll_theta1 = (int)ll_theta1;
   *pll_theta2 = (int)ll_theta2;
}

/*****************************************************************************
 函 数 名  : hi1102_cali_conj
 功能描述  : 对复数求共轭
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
hi1102_complex_stru  hmac_dpd_cali_conj(hi1102_complex_stru st_a)
{
    st_a.ll_imag = -st_a.ll_imag;

    return st_a;
}

/*****************************************************************************
 函 数 名  : hmac_dpd_complex_add
 功能描述  : 复数相乘
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
hi1102_complex_stru  hmac_dpd_complex_add(hi1102_complex_stru st_a, hi1102_complex_stru st_b)
{
    hi1102_complex_stru st_return;

    st_return.ll_real = (oal_int64)(st_a.ll_real + st_b.ll_real);
    st_return.ll_imag = (oal_int64)(st_a.ll_imag + st_b.ll_imag);

    return st_return;
}

/*****************************************************************************
 函 数 名  : hmac_dpd_complex_multiply_const
 功能描述  : 复数相乘
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
hi1102_complex_stru  hmac_dpd_complex_multiply_const(hi1102_complex_stru st_a, oal_int64 ll_b)
{
    hi1102_complex_stru st_return;

    st_return.ll_real = (oal_int64)(st_a.ll_real * ll_b);
    st_return.ll_imag = (oal_int64)(st_a.ll_imag * ll_b);

    return st_return;
}

/*****************************************************************************
 函 数 名  : hi1102_cali_complex_multiply
 功能描述  : 复数相乘
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
hi1102_complex_stru  hmac_dpd_complex_multiply(hi1102_complex_stru st_a, hi1102_complex_stru st_b)
{
    hi1102_complex_stru st_return;

    st_return.ll_real = (oal_int64)(st_a.ll_real * st_b.ll_real - st_a.ll_imag * st_b.ll_imag);
    st_return.ll_imag = (oal_int64)(st_a.ll_real * st_b.ll_imag + st_a.ll_imag * st_b.ll_real);

    return st_return;
}

/*****************************************************************************
 函 数 名  : hi1102_cali_complex_div
 功能描述  : 复数除法
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年3月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
hi1102_complex_stru  hmac_dpd_complex_div(hi1102_complex_stru st_complex_num, hi1102_complex_stru st_complex_denom)
{
    hi1102_complex_stru st_mul_res;
    hi1102_complex_stru st_conj_res;
    oal_int64 ll_power;
    oal_int64 ll_real;
    oal_int64 ll_imag;
    oal_int64 ll_temp;

    /* 除数取共轭 */
    st_conj_res = hmac_dpd_cali_conj(st_complex_denom);

    /* 复数乘法 被除数*conj(除数) */
    st_mul_res = hmac_dpd_complex_multiply(st_complex_num, st_conj_res);

    /* 计算Power */
    ll_real = st_complex_denom.ll_real;
    ll_imag = st_complex_denom.ll_imag;
    ll_power = ll_real * ll_real + ll_imag * ll_imag;

    /* 如果分母为0，则上报错误 */
    if (0 == ll_power)
    {
        OAM_WARNING_LOG0(0, OAM_SF_CALIBRATE, "hi1102_cali_complex_div: l_power is zero!\n");
        return st_mul_res;
    }
    else
    {
        /*实部 四舍五入 */
        ll_temp = (((st_mul_res.ll_real) % ll_power) << 1);
        st_mul_res.ll_real = ((st_mul_res.ll_real) / ll_power);
        if (GET_ABS(ll_temp) > ll_power)
        {
            if (ll_temp > 0)
                st_mul_res.ll_real = st_mul_res.ll_real + 1;
            else
                st_mul_res.ll_real = st_mul_res.ll_real - 1;

        }
        /* 虚部 四舍五入 */
        ll_temp = (((st_mul_res.ll_imag) % ll_power) << 1);
        st_mul_res.ll_imag = ((st_mul_res.ll_imag) / ll_power);
        if (GET_ABS(ll_temp) > ll_power)
        {
            if (ll_temp > 0)
                st_mul_res.ll_imag = st_mul_res.ll_imag + 1;
            else
                st_mul_res.ll_imag = st_mul_res.ll_imag - 1;

        }
    }

    /* 返回结果 */
    return st_mul_res;
}

/*****************************************************************************
 函 数 名  : hmac_dpd_complex_div_const
 功能描述  : 复数除以整数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
hi1102_complex_stru  hmac_dpd_complex_div_const(hi1102_complex_stru st_a, oal_int64 ll_b)
{
    hi1102_complex_stru st_return;

    st_return.ll_real = (oal_int64)(st_a.ll_real >> ll_b);
    st_return.ll_imag = (oal_int64)(st_a.ll_imag >> ll_b);

    return st_return;
}

/*****************************************************************************
 函 数 名  : hmac_dpd_complex_div_const
 功能描述  : 复数相乘
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_int64  hmac_dpd_complex_pow(hi1102_complex_stru st_a)
{
	return (oal_int64)(st_a.ll_real * st_a.ll_real + st_a.ll_imag * st_a.ll_imag);
}

oal_uint32 hmac_rf_cali_dpd_corr_calc(oal_uint32* hi1102_dpd_cali_data_read,
                                            oal_uint32* hi1102_dpd_cali_data_calc)
{
    oal_uint16  us_idx = 0, us_j =0;
    oal_int32   l_real = 0, l_imag =0;
    oal_int64   ll_amp = 0;

    hi1102_complex_stru st_vv1_32;
    hi1102_complex_stru st_vv0_32;
    hi1102_complex_stru st_xll_32;
    hi1102_complex_stru st_yll_32;
    hi1102_complex_stru st_ak_16[3];
    hi1102_complex_stru st_dpd_lut_fixed;
	hi1102_complex_stru st_tmp1 = {0, 0};
	hi1102_complex_stru st_tmp2 = {0, 0};
    unsigned int        ul_vo_fixed;
    oal_int64           ll_theta0, ll_theta1;
    hi1102_complex_stru st_y_opt_32;

    hi1102_complex_stru st_sum = {0,0};

    oal_int64           ll_dpd_base = 0;

    for(us_idx = 0; us_idx < DPD_CALI_LUT_LENGTH; us_idx++)
    {
      l_real =  GET2COMP((((oal_uint32)(*(hi1102_dpd_cali_data_read + us_idx))) & 0x7ff));
      l_imag =  GET2COMP(((((oal_uint32)(*(hi1102_dpd_cali_data_read + us_idx))) >> 11) & 0x7ff));

      OAM_WARNING_LOG2(0, OAM_SF_CALIBRATE, "{hi1102_dpd_cali_data_read:: l_real = %d, l_imag = %d}\r\n", l_real, l_imag);

      g_ll_pa_val[us_idx].ll_real = (oal_int64)l_real;
      g_ll_pa_val[us_idx].ll_imag = (oal_int64)l_imag;
    }

    /* g_ll_pa_val上报值, g_ll_mk1_32给定矩阵值 */
    for (us_j = 0; us_j < 3; us_j++)
    {
        st_sum.ll_real = 0;
        st_sum.ll_imag = 0;
        for (us_idx = 0; us_idx < DPD_CALI_LUT_LENGTH ; us_idx++)
        {
            st_sum = hmac_dpd_complex_add(st_sum, hmac_dpd_complex_multiply_const(g_ll_pa_val[us_idx], g_ll_mk1_32[us_j][us_idx]));

        }
        st_ak_16[us_j] = hmac_cali_complex_div_round_closest(st_sum, 1 << 11);  //round(oal_sum/BIT28);

        OAM_WARNING_LOG3(0, OAM_SF_CALIBRATE, "st_ak_16[%d] = %d + j%d\n", us_j, (int)st_ak_16[us_j].ll_real, (int)st_ak_16[us_j].ll_imag);
    }

    for (us_idx = 0; us_idx < DPD_CALI_LUT_LENGTH ; us_idx++)
    {
        st_vv1_32.ll_real = 512 * (1 << 5);
        st_vv1_32.ll_imag = 0;

        ul_vo_fixed = 4 + 8 * us_idx;

        for (us_j = 0; us_j < 10; us_j++)
        {
			st_xll_32 = hmac_cali_complex_div_round_closest(hmac_dpd_complex_multiply_const(st_vv1_32, ul_vo_fixed), 1 << 7);

			hmac_dpd_cordic(st_xll_32.ll_real, st_xll_32.ll_imag, &ll_amp, &ll_theta0, &ll_theta1);

            st_tmp1 = hmac_cali_complex_div_round_closest(hmac_dpd_complex_multiply_const(st_ak_16[1], ll_amp), 1 << 17);
            st_tmp1 = hmac_dpd_complex_add(st_ak_16[0], st_tmp1);

			st_tmp2 = hmac_dpd_complex_multiply_const(st_ak_16[2], hmac_dpd_complex_pow(st_xll_32));
			st_tmp2 = hmac_cali_complex_div_round_closest(st_tmp2, ((oal_int64)1 << 34));

            st_vv0_32  = hmac_dpd_complex_add(st_tmp1, st_tmp2);

            st_yll_32  = hmac_cali_complex_div_round_closest(hmac_dpd_complex_multiply(st_xll_32, st_vv0_32), 1 << 9);

        #if 0
            st_y_opt_32 = hmac_dpd_complex_multiply_const(st_ak_16[0], (ul_vo_fixed >> 2));
        #else
            st_y_opt_32 = hmac_dpd_complex_multiply_const(g_ll_pa_val[127], (ul_vo_fixed << 2));
        #endif
			st_vv1_32   = hmac_dpd_complex_div(hmac_dpd_complex_multiply(st_y_opt_32, st_vv1_32), st_yll_32);

            st_vv1_32.ll_real = OAL_MAX(-((1 << 15) - 1), OAL_MIN((1 << 15) - 1, st_vv1_32.ll_real));
            st_vv1_32.ll_imag = OAL_MAX(-((1 << 15) - 1), OAL_MIN((1 << 15) - 1, st_vv1_32.ll_imag));
        }

        st_dpd_lut_fixed = hmac_cali_complex_div_round_closest(st_vv1_32, 1 << 5);  //round(vv1_32/BIT5);

#if 1
        if (0 == us_idx)
        {
            ll_dpd_base = st_dpd_lut_fixed.ll_real;
            if (0 == ll_dpd_base)
            {
                OAM_ERROR_LOG0(0, OAM_SF_CALIBRATE, " dpd: the first dpd lut elements if zero!!!\r\n");
            }
        }
        st_dpd_lut_fixed = hmac_cali_complex_div_round_closest(hmac_dpd_complex_multiply_const(st_dpd_lut_fixed, 512), ll_dpd_base);
#endif
        *(hi1102_dpd_cali_data_calc + us_idx) = (SET2COMP((oal_int32)st_dpd_lut_fixed.ll_real)) | ((SET2COMP((oal_int32)st_dpd_lut_fixed.ll_imag)) << 11);
        OAM_WARNING_LOG2(0, OAM_SF_CALIBRATE, "hi1102_dpd_cali_data_calc::real = %d, imag = %d\r\n", (oal_int32)st_dpd_lut_fixed.ll_real, (oal_int32)st_dpd_lut_fixed.ll_imag);
    }

#if 0
    for (us_idx = 0; us_idx < DPD_CALI_LUT_LENGTH ; us_idx++)
    {
        l_real = us_idx;
        l_imag = 0;
        *(hi1102_dpd_cali_data_calc + us_idx) = (SET2COMP((oal_int32)l_real)) | ((SET2COMP((oal_int32)l_imag)) << 11);
        OAM_WARNING_LOG2(0, OAM_SF_CALIBRATE, "g_al_dpd_lut::real:[%d],imag:[%d]\r\n", (oal_int32)l_real, (oal_int32)l_imag);
    }
#endif

    return OAL_SUCC;
}

#endif /* _PRE_WLAN_RF_1102CALI_DPD */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

