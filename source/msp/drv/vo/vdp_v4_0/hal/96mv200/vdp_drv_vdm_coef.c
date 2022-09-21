// *****************************************************************************
//
// Copyright(c) 2015,Hisilicon Technologies Co., Ltd.
// All Rights Reserved
//
// Project name : VDP
// File Name    : coef.cpp
// Author       : sdk
// Email        : zhanglun1@hisilicon.com
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
#include "vdp_coef_func.h"

/************* DeGamma Luts **************/

HI_U32 u32TMLutHisi2SDR[32] = {                //U8.8 [0,65535]
    6399,
    6246,
    6097,
    5953,
    5814,
    5679,
    5548,
    5421,
    5298,
    4843,
    4441,
    4085,
    3769,
    3488,
    3237,
    3013,
    2812,
    2631,
    2469,
    2322,
    2189,
    2068,
    1958,
    1353,
    1022,
    819 ,
    683 ,
    512 ,
    410 ,
    341 ,
    293 ,
    256
};

HI_U32 u32DeGmmLutXVYCC[64] = {                          //U21.0 [0,2097151]
    62825  ,
    62825  ,
    62825  ,
    62825  ,
    96197  ,
    130554 ,
    162602 ,
    192373 ,
    219898 ,
    245208 ,
    268340 ,
    289330 ,
    308217 ,
    325043 ,
    339852 ,
    352694 ,
    363623 ,
    372697 ,
    379983 ,
    385559 ,
    389572 ,
    393216 ,
    396860 ,
    400873 ,
    406449 ,
    413735 ,
    422809 ,
    433738 ,
    446580 ,
    461389 ,
    478215 ,
    497102 ,
    518092 ,
    541224 ,
    566534 ,
    594059 ,
    623830 ,
    655878 ,
    690235 ,
    726927 ,
    765983 ,
    807428 ,
    851289 ,
    897590 ,
    946353 ,
    997603 ,
    1051361,
    1107648,
    1166486,
    1227895,
    1291894,
    1358503,
    1427741,
    1463351,
    1499625,
    1536565,
    1574173,
    1612452,
    1651404,
    1655707,
    1655707,
    1655707,
    1655707,
    1655707
};


/************* DeGamma Luts **************/
HI_U32 u32DePQLut[64] = {                            //U21.0 [0,2097151]
    0      ,
    21     ,
    125    ,
    416    ,
    1085   ,
    2472   ,
    5173   ,
    7317   ,
    10229  ,
    14160  ,
    19440  ,
    26507  ,
    35936  ,
    48488  ,
    65172  ,
    87326  ,
    116731 ,
    134868 ,
    155767 ,
    179854 ,
    207621 ,
    239641 ,
    276578 ,
    319206 ,
    342929 ,
    368425 ,
    395828 ,
    425285 ,
    456956 ,
    491012 ,
    527639 ,
    567038 ,
    609427 ,
    655041 ,
    704134 ,
    756984 ,
    813890 ,
    875176 ,
    941195 ,
    1012329,
    1049942,
    1088992,
    1129537,
    1171636,
    1215351,
    1260749,
    1307896,
    1356864,
    1407726,
    1460559,
    1515444,
    1572464,
    1631707,
    1693264,
    1757230,
    1823705,
    1892792,
    1964599,
    2001558,
    2039240,
    2058357,
    2077660,
    2097151,
    2097151
};

// DeSLF Curve: AVS HDR
HI_U32 u32DeSLFLut[64] = {                           //U21.0 [0,2097151]
    0      ,
    3      ,
    21     ,
    102    ,
    370    ,
    1106   ,
    2860   ,
    4405   ,
    6622   ,
    9747   ,
    14076  ,
    19990  ,
    27971  ,
    38630  ,
    52747  ,
    71324  ,
    95665  ,
    110515 ,
    127495 ,
    146915 ,
    169142 ,
    194609 ,
    223836 ,
    257447 ,
    276129 ,
    296205 ,
    317799 ,
    341047 ,
    366105 ,
    393144 ,
    422360 ,
    453975 ,
    488239 ,
    525439 ,
    565906 ,
    610020 ,
    658223 ,
    711028 ,
    769041 ,
    832978 ,
    867427 ,
    903689 ,
    941896 ,
    982197 ,
    1024753,
    1069743,
    1117366,
    1167842,
    1221419,
    1278371,
    1339008,
    1403678,
    1472774,
    1546742,
    1626091,
    1711403,
    1803347,
    1902694,
    1955419,
    2010342,
    2038671,
    2067601,
    2097151,
    2097151
};
// DeHLG Curve: BBC HDR
HI_U32 u32DeHLGLut[64] = {                           //U21.0 [0,2097151]
    0      ,
    2736   ,
    10944  ,
    24624  ,
    43776  ,
    68400  ,
    98496  ,
    115596 ,
    134064 ,
    153900 ,
    175105 ,
    199066 ,
    227607 ,
    261603 ,
    302098 ,
    350333 ,
    407789 ,
    440512 ,
    476226 ,
    515204 ,
    557745 ,
    604173 ,
    654846 ,
    710149 ,
    739668 ,
    770507 ,
    802724 ,
    836381 ,
    871543 ,
    908276 ,
    946651 ,
    986742 ,
    1028624,
    1072379,
    1118089,
    1165843,
    1215731,
    1267850,
    1322297,
    1379179,
    1408566,
    1438603,
    1469304,
    1500683,
    1532756,
    1565539,
    1599045,
    1633293,
    1668297,
    1704076,
    1740645,
    1778022,
    1816226,
    1855274,
    1895186,
    1935979,
    1977675,
    2020292,
    2041952,
    2063851,
    2074890,
    2085990,
    2097151,
    2097151
};

// DeGamma Curve: SDR
HI_U32 u32DeGmmLut[64] = {                           //U21.0 [0,2097151]
    0      ,
    29156  ,
    61257  ,
    105865 ,
    164156 ,
    236747 ,
    324173 ,
    373600 ,
    426910 ,
    484155 ,
    545386 ,
    610649 ,
    679991 ,
    753455 ,
    831085 ,
    912922 ,
    999004 ,
    1043650,
    1089371,
    1136173,
    1184060,
    1233037,
    1283107,
    1334276,
    1360273,
    1386547,
    1413098,
    1439925,
    1467031,
    1494415,
    1522077,
    1550019,
    1578241,
    1606743,
    1635525,
    1664590,
    1693935,
    1723564,
    1753475,
    1783669,
    1798873,
    1814147,
    1829493,
    1844910,
    1860398,
    1875957,
    1891587,
    1907289,
    1923062,
    1938907,
    1954823,
    1970811,
    1986871,
    2003002,
    2019205,
    2035480,
    2051826,
    2068245,
    2076481,
    2084736,
    2088870,
    2093008,
    2097151,
    2097151
};

// DeHisi Curve: Hisi HDR
HI_U32 u32DeHisiLut[64] = {                          //U20.0 [0,1048575]
    0        ,
    0        ,
    0        ,
    1        ,
    1        ,
    2        ,
    4        ,
    7        ,
    10       ,
    16       ,
    24       ,
    35       ,
    51       ,
    71       ,
    99       ,
    136      ,
    184      ,
    246      ,
    325      ,
    425      ,
    550      ,
    706      ,
    899      ,
    1135     ,
    1422     ,
    1771     ,
    2191     ,
    2694     ,
    3293     ,
    4005     ,
    4846     ,
    5837     ,
    6999     ,
    8356     ,
    9938     ,
    11776    ,
    13905    ,
    16365    ,
    19202    ,
    22466    ,
    26216    ,
    30518    ,
    35445    ,
    41085    ,
    47535    ,
    54910    ,
    63341    ,
    72982    ,
    84015    ,
    96655    ,
    111156   ,
    127829   ,
    147049   ,
    169280   ,
    195096   ,
    225228   ,
    260609   ,
    302458   ,
    352398   ,
    412641   ,
    486278   ,
    577771   ,
    693812   ,
    1048575
};



/************* ToneMapping Luts **************/
// ToneMapping Lut: Default
HI_U32 u32TMLut[64] = {//U8.8 [0,65535]
    11127,
    11127,
    11123,
    11119,
    11116,
    11101,
    11086,
    11072,
    11057,
    11042,
    11028,
    11013,
    10955,
    10897,
    10783,
    10671,
    10560,
    10451,
    10237,
    10028,
    9826 ,
    9629 ,
    9437 ,
    8721 ,
    8078 ,
    7500 ,
    6980 ,
    6511 ,
    6087 ,
    5703 ,
    5354 ,
    5038 ,
    4750 ,
    4487 ,
    4247 ,
    4027 ,
    3825 ,
    3167 ,
    2684 ,
    2320 ,
    2039 ,
    1816 ,
    1637 ,
    1489 ,
    1365 ,
    1260 ,
    1170 ,
    1092 ,
    1024 ,
    964  ,
    910  ,
    862  ,
    819  ,
    683  ,
    585  ,
    512  ,
    455  ,
    410  ,
    372  ,
    341  ,
    315  ,
    293  ,
    273  ,
    256
/*
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
819 ,
683 ,
512 ,
410 ,
341 ,
293 ,
256
*/
};
/************* Smap Luts **************/
HI_U32 u32SMLutHDR102SDR[64] = {                   //U2.8 [0,1023]
    218,
    218,
    218,
    218,
    218,
    218,
    218,
    218,
    218,
    218,
    218,
    218,
    218,
    218,
    218,
    218,
    218,
    218,
    218,
    218,
    218,
    218,
    218,
    218,
    218,
    218,
    218,
    218,
    218,
    218,
    218,
    218,
    218,
    218,
    208,
    205,
    201,
    199,
    185,
    165,
    125,
    95 ,
    60 ,
    40 ,
    40 ,
    40 ,
    40 ,
    40 ,
    40 ,
    40 ,
    40 ,
    30 ,
    30 ,
    30 ,
    30 ,
    30 ,
    20 ,
    20 ,
    20 ,
    20 ,
    20 ,
    20 ,
    10 ,
    10
};

HI_U32 u32SMLutLinear[64] = {                  //U2.8 [0,1023]
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
    256,
    256
};

HI_U32 u32SMLutAVS2SDR[64] = {                 //U2.8 [0,1023]
    248,
    248,
    248,
    248,
    248,
    248,
    248,
    248,
    248,
    248,
    248,
    248,
    248,
    248,
    248,
    248,
    248,
    248,
    248,
    248,
    248,
    248,
    248,
    248,
    248,
    248,
    248,
    248,
    248,
    248,
    248,
    240,
    234,
    230,
    226,
    222,
    218,
    214,
    205,
    199,
    194,
    191,
    188,
    185,
    183,
    181,
    179,
    177,
    175,
    173,
    172,
    170,
    165,
    159,
    155,
    151,
    147,
    143,
    140,
    137,
    134,
    131,
    128,
    126,
};

// ToneMapping Lut: HDR10  to SDR
HI_U32 u32TMLutHDR102SDR[64] = {                   //U9.7 [0,65535]
    23914,
    23914,
    22658,
    21587,
    20660,
    17904,
    16054,
    14705,
    13667,
    12838,
    12157,
    11585,
    9977 ,
    8965 ,
    7732 ,
    6987 ,
    6476 ,
    6099 ,
    5567 ,
    5199 ,
    4922 ,
    4701 ,
    4518 ,
    3990 ,
    3628 ,
    3345 ,
    3110 ,
    2908 ,
    2731 ,
    2573 ,
    2430 ,
    2301 ,
    2184 ,
    2076 ,
    1977 ,
    1885 ,
    1801 ,
    1520 ,
    1307 ,
    1142 ,
    1010 ,
    903  ,
    815  ,
    743  ,
    681  ,
    630  ,
    585  ,
    546  ,
    512  ,
    482  ,
    455  ,
    431  ,
    410  ,
    341  ,
    293  ,
    256  ,
    228  ,
    205  ,
    186  ,
    171  ,
    158  ,
    146  ,
    137  ,
    128


};

// ToneMapping Lut: AVS to SDR
HI_U32 u32TMLutAVS2SDR[64] = {                 //U9.7 [0,65535]
    30773,
    30773,
    28984,
    27460,
    26140,
    22218,
    19586,
    17667,
    16192,
    15015,
    14049,
    13239,
    10963,
    9539 ,
    7813 ,
    6784 ,
    6089 ,
    5583 ,
    4886 ,
    4422 ,
    4086 ,
    3828 ,
    3623 ,
    3083 ,
    2758 ,
    2530 ,
    2354 ,
    2211 ,
    2091 ,
    1986 ,
    1893 ,
    1810 ,
    1734 ,
    1665 ,
    1601 ,
    1542 ,
    1487 ,
    1299 ,
    1150 ,
    1029 ,
    928  ,
    844  ,
    772  ,
    710  ,
    657  ,
    611  ,
    571  ,
    535  ,
    503  ,
    475  ,
    450  ,
    427  ,
    407  ,
    341  ,
    293  ,
    256  ,
    228  ,
    205  ,
    186  ,
    171  ,
    158  ,
    146  ,
    137  ,
    128
};

// ToneMapping Lut: AVS to HDR10
HI_U32 u32TMLutAVS2HDR10[64] = {               // U8.8 [0,65535]
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
    256,
    256
};

// ToneMapping Lut: HDR10 to BBC
HI_U32 u32TMLutHDR102BBC[64] = {                   //U6.10 [0,65535]
    46552,
    46552,
    40832,
    37818,
    35815,
    31414,
    29095,
    27554,
    26416,
    25520,
    24787,
    24169,
    22385,
    21199,
    19634,
    18594,
    17826,
    17222,
    16310,
    15636,
    15106,
    14672,
    14306,
    13250,
    12548,
    12029,
    11622,
    11288,
    11006,
    10764,
    10551,
    10363,
    10194,
    10041,
    9901 ,
    9772 ,
    9654 ,
    9255 ,
    8941 ,
    8684 ,
    8192 ,
    7282 ,
    6554 ,
    5958 ,
    5461 ,
    5041 ,
    4681 ,
    4369 ,
    4096 ,
    3855 ,
    3641 ,
    3449 ,
    3277 ,
    2731 ,
    2341 ,
    2048 ,
    1820 ,
    1638 ,
    1489 ,
    1365 ,
    1260 ,
    1170 ,
    1092 ,
    1024
};

// ToneMapping Lut: BBC to HDR10
HI_U32 u32TMLutBBC2HDR10[64] = {                   //U1.15 [0,65535]
    357 ,
    357 ,
    410 ,
    444 ,
    471 ,
    540 ,
    586 ,
    621 ,
    649 ,
    673 ,
    694 ,
    713 ,
    773 ,
    819 ,
    888 ,
    941 ,
    984 ,
    1021,
    1081,
    1130,
    1172,
    1209,
    1242,
    1347,
    1426,
    1491,
    1547,
    1595,
    1638,
    1677,
    1713,
    1746,
    1777,
    1805,
    1832,
    1858,
    1882,
    1968,
    2041,
    2105,
    2162,
    2213,
    2261,
    2304,
    2345,
    2382,
    2418,
    2452,
    2483,
    2514,
    2543,
    2570,
    2597,
    2693,
    2777,
    2853,
    2921,
    2983,
    3040,
    3094,
    3144,
    3190,
    3235,
    3277
};

// ToneMapping Lut: BBC to SDR
HI_U32 u32TMLutBBC2SDR[64] = {                 //U1.15 [0,65535]
    // 300nits
    40715,
    40715,
    40165,
    39847,
    39623,
    39088,
    38778,
    38560,
    38392,
    38255,
    38139,
    38040,
    37738,
    37526,
    37229,
    37020,
    36858,
    36726,
    36520,
    36360,
    36231,
    36121,
    36027,
    35741,
    35540,
    35385,
    35259,
    35153,
    35061,
    34980,
    34908,
    34842,
    34783,
    34728,
    34678,
    34631,
    34587,
    34436,
    34313,
    34210,
    34120,
    34042,
    33971,
    33908,
    33850,
    33797,
    33748,
    33702,
    33660,
    33620,
    33582,
    33547,
    33513,
    33393,
    33292,
    33205,
    33129,
    33060,
    32999,
    32942,
    32891,
    32843,
    32799,
    32757
};

// ToneMapping Lut: Hisi to HDR10
HI_U32 u32TMLutHisi2HDR10[32] = {                  //U8.8 [0,65535]
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



/************* Gamma Luts **************/
HI_U32 u32GmmLut0[64] = {//U12.0 [0,4095]
0   ,
72  ,
144 ,
216 ,
288 ,
360 ,
426 ,
486 ,
541 ,
592 ,
641 ,
686 ,
730 ,
772 ,
812 ,
850 ,
887 ,
923 ,
957 ,
991 ,
1024,
1055,
1086,
1116,
1146,
1174,
1203,
1230,
1257,
1284,
1310,
1335,
1360,
1409,
1456,
1502,
1547,
1590,
1632,
1673,
1713,
1753,
1791,
1829,
1866,
1902,
1937,
1972,
2006,
2138,
2261,
2378,
2489,
2595,
2697,
2889,
3068,
3237,
3397,
3549,
3694,
3833,
3966,
4095
};

/******************* Gmm-8 Lut Params *************************/
HI_U32 u32PQLut[64] = {            //U12.0 [0,4095]
    0   ,
    304 ,
    400 ,
    466 ,
    517 ,
    657 ,
    749 ,
    820 ,
    878 ,
    927 ,
    970 ,
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

// PQ Curve
HI_U32 u32PQLut2500[64] = {            //U12.0 [0,4095]
    0   ,
    167 ,
    227 ,
    270 ,
    304 ,
    400 ,
    466 ,
    517 ,
    559 ,
    596 ,
    628 ,
    657 ,
    749 ,
    820 ,
    927 ,
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

//HLG Curve
HI_U32 u32HLGLut[64] = {            //U12.0 [0,4095]
    0   ,
    28  ,
    39  ,
    48  ,
    55  ,
    78  ,
    96  ,
    111 ,
    124 ,
    136 ,
    147 ,
    157 ,
    192 ,
    222 ,
    271 ,
    313 ,
    350 ,
    384 ,
    443 ,
    496 ,
    543 ,
    586 ,
    627 ,
    768 ,
    887 ,
    991 ,
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

// Gamma Curve
HI_U32 u32GmmLut[64] = {            //U12.0 [0,4095]
    0   ,
    0   ,
    1   ,
    1   ,
    1   ,
    2   ,
    3   ,
    4   ,
    6   ,
    7   ,
    8   ,
    9   ,
    13  ,
    18  ,
    27  ,
    36  ,
    45  ,
    54  ,
    72  ,
    90  ,
    108 ,
    126 ,
    144 ,
    216 ,
    288 ,
    360 ,
    426 ,
    486 ,
    541 ,
    592 ,
    641 ,
    686 ,
    730 ,
    772 ,
    812 ,
    850 ,
    887 ,
    1024,
    1146,
    1257,
    1360,
    1456,
    1547,
    1632,
    1713,
    1791,
    1866,
    1937,
    2006,
    2073,
    2138,
    2200,
    2261,
    2489,
    2697,
    2889,
    3068,
    3237,
    3397,
    3549,
    3694,
    3833,
    3966,
    4095
};



extern VDP_COEF_ADDR_S gstVdpCoefBufAddr;

HI_VOID Vdp_Drv_SetHdrVdmCoef_gmm(HIHDR_SCENE_MODE_E enHiHdrMode, HI_PQ_HDR_CFG *pstHiHdrCfg)
{
#if UT_TEST
    HI_U32 addr = 0;
#else
    HI_U8  *addr    = gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_VDM_GAMMA] ;//add by hyx

#endif

    VDP_DRV_COEF_SEND_CFG   stCoefSend;


    HI_S32 tcLut_s32[64];


    void*  p_coef_array[]    = {tcLut_s32};
    HI_U32 lut_length[]      = {64};
    HI_U32 coef_bit_length[] = {12};
    FILE*   fp_hihdr_vdm_degmm_coef=NULL;


    VDP_HIHDR_SetVdmParaGmmAddr(gstVdpCoefBufAddr.u32CoefPhyAddr[VDP_COEF_BUF_VDM_GAMMA]);

#if !CBB_CFG_FROM_PQ
    if(enHiHdrMode == HIHDR_HDR10_IN_SDR_OUT)
    {
        VDP_PRINT("gamma Coef : VdmSceneMode == VDM_HDR10_IN_SDR_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32GmmLut     ;
    }
    else if(enHiHdrMode == HIHDR_HLG_IN_HDR10_OUT)
    {
        VDP_PRINT("gamma Coef : VdmSceneMode == VDM_BBC_IN_HDR10_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32PQLut     ;
    }
    else if(enHiHdrMode == HIHDR_BT2020_IN_709_OUT)
    {
        VDP_PRINT("gamma Coef : VdmSceneMode == VDM_BT2020_IN_709_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32GmmLut     ;
    }
    else if(enHiHdrMode == HIHDR_HLG_IN_SDR_OUT)
    {
        VDP_PRINT("gamma Coef : VdmSceneMode == VDM_BBC_IN_SDR_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32GmmLut     ;
    }
    else if(enHiHdrMode == HIHDR_SLF_IN_SDR_OUT)
    {
        VDP_PRINT("gamma Coef : VdmSceneMode == VDM_AVS_IN_SDR_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32GmmLut     ;
    }
    else if(enHiHdrMode == HIHDR_SLF_IN_HDR10_OUT)
    {
        VDP_PRINT("gamma Coef : VdmSceneMode == VDM_AVS_IN_HDR10_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32PQLut     ;
    }
    else if(enHiHdrMode == HIHDR_HDR10_IN_HLG_OUT)
    {
        VDP_PRINT("gamma Coef : VdmSceneMode == VDM_HDR10_IN_BBC_OUT\n");

        p_coef_array[0]    = (HI_S32*)u32PQLut     ;
    }
    else if(enHiHdrMode == HIHDR_XVYCC)
    {
        VDP_PRINT("gamma Coef : VdmSceneMode == HIHDR_XVYCC\n");

        p_coef_array[0]    = (HI_S32*)u32GmmLut     ;
    }
    else if(enHiHdrMode == HIHDR_SDR_BT2020CL_IN_BT709_OUT)
    {
        VDP_PRINT("gamma Coef : VdmSceneMode == VDM_SDR_BT2020CL_IN_BT709_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32GmmLut     ;
    }
    else
    {
        VDP_PRINT("gamma Coef : VdmSceneMode == Default !\n");
        p_coef_array[0]    = (HI_S32*)u32DePQLut     ;
    }
#else
    if (HI_NULL == (HI_S32*)pstHiHdrCfg->stGmm.pu32LUT)
    {
        VDP_PRINT("pstHiHdrCfg is NULL!\n");

        return;
    }
    p_coef_array[0]    = (HI_S32*)pstHiHdrCfg->stGmm.pu32LUT;
#endif

    stCoefSend.coef_addr         = addr                     ;
    stCoefSend.sti_type          = STI_FILE_COEF_DM         ;
    stCoefSend.fp_coef           = fp_hihdr_vdm_degmm_coef  ;
    stCoefSend.lut_num           = 1                        ;
    stCoefSend.burst_num         = 1                        ;
    stCoefSend.cycle_num         = 10                       ;
    stCoefSend.p_coef_array      = p_coef_array             ;
    stCoefSend.lut_length        = lut_length               ;
    stCoefSend.coef_bit_length   = coef_bit_length          ;
    stCoefSend.data_type         = COEF_DATA_TYPE_S32       ;

    VDP_DRV_SendCoef(&stCoefSend);
    VDP_HIHDR_SetVdmParaGmmUpd(1);

    return;
}



HI_VOID Vdp_Drv_SetHdrVdmCoef_Degmm(HIHDR_SCENE_MODE_E enHiHdrMode, HI_PQ_HDR_CFG *pstHiHdrCfg)
{
#if UT_TEST
    HI_U32 addr = 0;
#else
    HI_U8  *addr    = gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_VDM_DEGAMMA] ;//add by hyx

#endif

    VDP_DRV_COEF_SEND_CFG   stCoefSend;


    HI_S32 tcLut_s32[64];


    void*  p_coef_array[]    = {tcLut_s32};
    HI_U32 lut_length[]      = {64};
    HI_U32 coef_bit_length[] = {21};
    FILE*   fp_hihdr_vdm_degmm_coef=NULL;


    VDP_HIHDR_SetVdmParaDegmmAddr(gstVdpCoefBufAddr.u32CoefPhyAddr[VDP_COEF_BUF_VDM_DEGAMMA]);


#if !CBB_CFG_FROM_PQ
    if(enHiHdrMode == HIHDR_HDR10_IN_SDR_OUT)
    {
        VDP_PRINT("DeGamma Coef : VdmSceneMode == VDM_HDR10_IN_SDR_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32DePQLut     ;
    }
    else if(enHiHdrMode == HIHDR_HLG_IN_HDR10_OUT)
    {
        VDP_PRINT("DeGamma Coef : VdmSceneMode == VDM_BBC_IN_HDR10_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32DeHLGLut     ;
    }
    else if(enHiHdrMode == HIHDR_BT2020_IN_709_OUT)
    {
        VDP_PRINT("DeGamma Coef : VdmSceneMode == VDM_BT2020_IN_709_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32DeGmmLut     ;
    }
    else if(enHiHdrMode == HIHDR_HLG_IN_SDR_OUT)
    {
        VDP_PRINT("DeGamma Coef : VdmSceneMode == VDM_BBC_IN_SDR_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32DeHLGLut     ;
    }
    else if(enHiHdrMode == HIHDR_SLF_IN_SDR_OUT)
    {
        VDP_PRINT("DeGamma Coef : VdmSceneMode == VDM_AVS_IN_SDR_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32DeSLFLut     ;
    }
    else if(enHiHdrMode == HIHDR_SLF_IN_HDR10_OUT)
    {
        VDP_PRINT("DeGamma Coef : VdmSceneMode == VDM_AVS_IN_HDR10_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32DeSLFLut     ;
    }
    else if(enHiHdrMode == HIHDR_HDR10_IN_HLG_OUT)
    {
        VDP_PRINT("DeGamma Coef : VdmSceneMode == VDM_HDR10_IN_BBC_OUT\n");

        p_coef_array[0]    = (HI_S32*)u32DePQLut     ;
    }

    else if(enHiHdrMode == HIHDR_XVYCC)
    {
        VDP_PRINT("DeGamma Coef : VdmSceneMode == HIHDR_XVYCC\n");

        p_coef_array[0]    = (HI_S32*)u32DeGmmLutXVYCC     ;
    }
    else if(enHiHdrMode == HIHDR_SDR_BT2020CL_IN_BT709_OUT)
    {
        VDP_PRINT("degamma Coef : VdmSceneMode == VDM_SDR_BT2020CL_IN_BT709_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32DeGmmLut     ;
    }

    else
    {
        VDP_PRINT("DeGamma Coef : VdmSceneMode == Default !\n");
        p_coef_array[0]    = (HI_S32*)u32DePQLut     ;
    }
#else
    if (HI_NULL == (HI_S32*)pstHiHdrCfg->stDeGmm.pu32LUT)
    {
        VDP_PRINT("pstHiHdrCfg is NULL!\n");
        return;
    }

    p_coef_array[0]    = (HI_S32*)pstHiHdrCfg->stDeGmm.pu32LUT;
#endif

    stCoefSend.coef_addr         = addr                     ;
    stCoefSend.sti_type          = STI_FILE_COEF_DM        ;
    stCoefSend.fp_coef           = fp_hihdr_vdm_degmm_coef              ;
    stCoefSend.lut_num           = 1              ;
    stCoefSend.burst_num         = 1            ;
    stCoefSend.cycle_num         = 6            ;
    stCoefSend.p_coef_array      = p_coef_array             ;
    stCoefSend.lut_length        = lut_length               ;
    stCoefSend.coef_bit_length   = coef_bit_length          ;
    stCoefSend.data_type         = COEF_DATA_TYPE_S32       ;

    VDP_DRV_SendCoef(&stCoefSend);
    VDP_HIHDR_SetVdmParaDegmmUpd(1);

    return;
}


HI_VOID Vdp_Drv_SetSdrVdmCoef_gmm(HIHDR_SCENE_MODE_E enHiHdrMode)
{
#if UT_TEST
    HI_U32 addr = 0;
#else
    HI_U8  *addr    = gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_VDM_GAMMA] ;//add by hyx
#endif

    VDP_DRV_COEF_SEND_CFG   stCoefSend;
    HI_S32 tcLut_s32[64];
    void*  p_coef_array[]    = {tcLut_s32};
    HI_U32 lut_length[]      = {64};
    HI_U32 coef_bit_length[] = {12};
    FILE*   fp_hihdr_vdm_degmm_coef=NULL;


    VDP_HIHDR_SetVdmParaGmmAddr(gstVdpCoefBufAddr.u32CoefPhyAddr[VDP_COEF_BUF_VDM_GAMMA]);

    if(enHiHdrMode == HIHDR_HDR10_IN_SDR_OUT)
    {
        VDP_PRINT("gamma Coef : VdmSceneMode == VDM_HDR10_IN_SDR_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32GmmLut     ;
    }
    else if(enHiHdrMode == HIHDR_HLG_IN_HDR10_OUT)
    {
        VDP_PRINT("gamma Coef : VdmSceneMode == VDM_BBC_IN_HDR10_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32PQLut     ;
    }
    else if(enHiHdrMode == HIHDR_BT2020_IN_709_OUT)
    {
        VDP_PRINT("gamma Coef : VdmSceneMode == VDM_BT2020_IN_709_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32GmmLut     ;
    }
    else if(enHiHdrMode == HIHDR_HLG_IN_SDR_OUT)
    {
        VDP_PRINT("gamma Coef : VdmSceneMode == VDM_BBC_IN_SDR_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32GmmLut     ;
    }
    else if(enHiHdrMode == HIHDR_SLF_IN_SDR_OUT)
    {
        VDP_PRINT("gamma Coef : VdmSceneMode == VDM_AVS_IN_SDR_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32GmmLut     ;
    }
    else if(enHiHdrMode == HIHDR_SLF_IN_HDR10_OUT)
    {
        VDP_PRINT("gamma Coef : VdmSceneMode == VDM_AVS_IN_HDR10_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32PQLut     ;
    }
    else if(enHiHdrMode == HIHDR_HDR10_IN_HLG_OUT)
    {
        VDP_PRINT("gamma Coef : VdmSceneMode == VDM_HDR10_IN_BBC_OUT\n");

        p_coef_array[0]    = (HI_S32*)u32PQLut     ;
    }
    else if(enHiHdrMode == HIHDR_XVYCC)
    {
        VDP_PRINT("gamma Coef : VdmSceneMode == HIHDR_XVYCC\n");

        p_coef_array[0]    = (HI_S32*)u32GmmLut     ;
    }
    else if(enHiHdrMode == HIHDR_SDR_BT2020CL_IN_BT709_OUT)
    {
        VDP_PRINT("gamma Coef : VdmSceneMode == VDM_SDR_BT2020CL_IN_BT709_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32GmmLut     ;
    }
    else
    {
        VDP_PRINT("gamma Coef : VdmSceneMode == Default !\n");
        p_coef_array[0]    = (HI_S32*)u32DePQLut     ;
    }


    stCoefSend.coef_addr         = addr                     ;
    stCoefSend.sti_type          = STI_FILE_COEF_DM         ;
    stCoefSend.fp_coef           = fp_hihdr_vdm_degmm_coef  ;
    stCoefSend.lut_num           = 1                        ;
    stCoefSend.burst_num         = 1                        ;
    stCoefSend.cycle_num         = 10                       ;
    stCoefSend.p_coef_array      = p_coef_array             ;
    stCoefSend.lut_length        = lut_length               ;
    stCoefSend.coef_bit_length   = coef_bit_length          ;
    stCoefSend.data_type         = COEF_DATA_TYPE_S32       ;

    VDP_DRV_SendCoef(&stCoefSend);
    VDP_HIHDR_SetVdmParaGmmUpd(1);

    return;
}



HI_VOID Vdp_Drv_SetSdrVdmCoef_Degmm(HIHDR_SCENE_MODE_E enHiHdrMode)
{
#if UT_TEST
    HI_U32 addr = 0;
#else
    HI_U8  *addr    = gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_VDM_DEGAMMA] ;//add by hyx
#endif

    VDP_DRV_COEF_SEND_CFG   stCoefSend;
    HI_S32 tcLut_s32[64];
    void*  p_coef_array[]    = {tcLut_s32};
    HI_U32 lut_length[]      = {64};
    HI_U32 coef_bit_length[] = {21};
    FILE*   fp_hihdr_vdm_degmm_coef=NULL;


    VDP_HIHDR_SetVdmParaDegmmAddr(gstVdpCoefBufAddr.u32CoefPhyAddr[VDP_COEF_BUF_VDM_DEGAMMA]);

    if(enHiHdrMode == HIHDR_HDR10_IN_SDR_OUT)
    {
        VDP_PRINT("DeGamma Coef : VdmSceneMode == VDM_HDR10_IN_SDR_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32DePQLut     ;
    }
    else if(enHiHdrMode == HIHDR_HLG_IN_HDR10_OUT)
    {
        VDP_PRINT("DeGamma Coef : VdmSceneMode == VDM_BBC_IN_HDR10_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32DeHLGLut     ;
    }
    else if(enHiHdrMode == HIHDR_BT2020_IN_709_OUT)
    {
        VDP_PRINT("DeGamma Coef : VdmSceneMode == VDM_BT2020_IN_709_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32DeGmmLut     ;
    }
    else if(enHiHdrMode == HIHDR_HLG_IN_SDR_OUT)
    {
        VDP_PRINT("DeGamma Coef : VdmSceneMode == VDM_BBC_IN_SDR_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32DeHLGLut     ;
    }
    else if(enHiHdrMode == HIHDR_SLF_IN_SDR_OUT)
    {
        VDP_PRINT("DeGamma Coef : VdmSceneMode == VDM_AVS_IN_SDR_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32DeSLFLut     ;
    }
    else if(enHiHdrMode == HIHDR_SLF_IN_HDR10_OUT)
    {
        VDP_PRINT("DeGamma Coef : VdmSceneMode == VDM_AVS_IN_HDR10_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32DeSLFLut     ;
    }
    else if(enHiHdrMode == HIHDR_HDR10_IN_HLG_OUT)
    {
        VDP_PRINT("DeGamma Coef : VdmSceneMode == VDM_HDR10_IN_BBC_OUT\n");

        p_coef_array[0]    = (HI_S32*)u32DePQLut     ;
    }

    else if(enHiHdrMode == HIHDR_XVYCC)
    {
        VDP_PRINT("DeGamma Coef : VdmSceneMode == HIHDR_XVYCC\n");

        p_coef_array[0]    = (HI_S32*)u32DeGmmLutXVYCC     ;
    }
    else if(enHiHdrMode == HIHDR_SDR_BT2020CL_IN_BT709_OUT)
    {
        VDP_PRINT("degamma Coef : VdmSceneMode == VDM_SDR_BT2020CL_IN_BT709_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32DeGmmLut     ;
    }

    else
    {
        VDP_PRINT("DeGamma Coef : VdmSceneMode == Default !\n");
        p_coef_array[0]    = (HI_S32*)u32DePQLut     ;
    }

    stCoefSend.coef_addr         = addr                     ;
    stCoefSend.sti_type          = STI_FILE_COEF_DM        ;
    stCoefSend.fp_coef           = fp_hihdr_vdm_degmm_coef              ;
    stCoefSend.lut_num           = 1              ;
    stCoefSend.burst_num         = 1            ;
    stCoefSend.cycle_num         = 6            ;
    stCoefSend.p_coef_array      = p_coef_array             ;
    stCoefSend.lut_length        = lut_length               ;
    stCoefSend.coef_bit_length   = coef_bit_length          ;
    stCoefSend.data_type         = COEF_DATA_TYPE_S32       ;

    VDP_DRV_SendCoef(&stCoefSend);
    VDP_HIHDR_SetVdmParaDegmmUpd(1);

    return;
}


HI_VOID Vdp_Drv_SetHdrVdmCoef_Smapping(HIHDR_SCENE_MODE_E enHiHdrMode, HI_PQ_HDR_CFG *pstHiHdrCfg)
{
#if UT_TEST
    HI_U32 addr = 0;
#else
    HI_U8  *addr    = gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_VDM_SMAP] ;

#endif

    VDP_DRV_COEF_SEND_CFG   stCoefSend;


    HI_S32 tcLut_s32[64];


    void*  p_coef_array[]    = {tcLut_s32};
    HI_U32 lut_length[]      = {64};
    HI_U32 coef_bit_length[] = {10};
    FILE*   fp_hihdr_vdm_degmm_coef=NULL;


    //VDP_VID_SetVdmVdmParaTmapAddr   (VDP_LAYER_VP0,        gstVdpCoefBufAddr.u32CoefPhyAddr[VDP_COEF_BUF_VDM_TONEMAP]);
    VDP_HIHDR_SetVdmParaSmAddr(gstVdpCoefBufAddr.u32CoefPhyAddr[VDP_COEF_BUF_VDM_SMAP]);



#if !CBB_CFG_FROM_PQ
    if(enHiHdrMode == HIHDR_HDR10_IN_SDR_OUT)
    {
        VDP_PRINT("smapping Coef : VdmSceneMode == VDM_HDR10_IN_SDR_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32SMLutHDR102SDR     ;
    }
    else if(enHiHdrMode == HIHDR_HLG_IN_HDR10_OUT)
    {
        VDP_PRINT("smapping Coef : VdmSceneMode == VDM_BBC_IN_HDR10_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32SMLutLinear     ;
    }
    else if(enHiHdrMode == HIHDR_HLG_IN_SDR_OUT)
    {
        VDP_PRINT("smapping Coef : VdmSceneMode == VDM_BBC_IN_SDR_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32SMLutLinear     ;
    }
    else if(enHiHdrMode == HIHDR_SLF_IN_SDR_OUT)
    {
        VDP_PRINT("smapping Coef : VdmSceneMode == VDM_AVS_IN_SDR_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32SMLutAVS2SDR     ;
    }
    else if(enHiHdrMode == HIHDR_SLF_IN_HDR10_OUT)
    {
        VDP_PRINT("smapping Coef : VdmSceneMode == VDM_AVS_IN_HDR10_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32SMLutLinear     ;
    }
    else if(enHiHdrMode == HIHDR_HDR10_IN_HLG_OUT)
    {
        VDP_PRINT("smapping Coef : VdmSceneMode == VDM_HDR10_IN_BBC_OUT\n");

        p_coef_array[0]    = (HI_S32*)u32SMLutLinear     ;
    }
    else if(enHiHdrMode == HIHDR_SDR_BT2020CL_IN_BT709_OUT)
    {
        VDP_PRINT("smapping Coef : VdmSceneMode == VDM_SDR_BT2020CL_IN_BT709_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32SMLutLinear     ;
    }
    else
    {
        VDP_PRINT("smapping Coef : VdmSceneMode == Default !\n");
        p_coef_array[0]    = (HI_S32*)u32SMLutHDR102SDR     ;
    }
#else
    if (HI_NULL == (HI_S32*)pstHiHdrCfg->stSMAP.pu32LUTTM)
    {
        VDP_PRINT("pstHiHdrCfg is NULL!\n");
        return;
    }

            p_coef_array[0]    = (HI_S32*)pstHiHdrCfg->stSMAP.pu32LUTTM;
#endif


    stCoefSend.coef_addr         = addr                     ;
    stCoefSend.sti_type          = STI_FILE_COEF_DM         ;
    stCoefSend.fp_coef           = fp_hihdr_vdm_degmm_coef  ;
    stCoefSend.lut_num           = 1                        ;
    stCoefSend.burst_num         = 1                        ;
    stCoefSend.cycle_num         = 8                        ;
    stCoefSend.p_coef_array      = p_coef_array             ;
    stCoefSend.lut_length        = lut_length               ;
    stCoefSend.coef_bit_length   = coef_bit_length          ;
    stCoefSend.data_type         = COEF_DATA_TYPE_S32       ;

    VDP_DRV_SendCoef(&stCoefSend);
    VDP_HIHDR_SetVdmParaSmUpd(1);

    return;
}


HI_VOID Vdp_Drv_SetHdrVdmCoef_Tmapping(HIHDR_SCENE_MODE_E enHiHdrMode, HI_PQ_HDR_CFG *pstHiHdrCfg)
{
#if UT_TEST
    HI_U32 addr = 0;
#else
    HI_U8  *addr    = gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_VDM_TONEMAP] ;//add by hyx

#endif

    VDP_DRV_COEF_SEND_CFG   stCoefSend;


    HI_S32 tcLut_s32[64];


    void*  p_coef_array[]    = {tcLut_s32};
    HI_U32 lut_length[]      = {64};
    HI_U32 coef_bit_length[] = {16};
    FILE*   fp_hihdr_vdm_degmm_coef=NULL;


    VDP_HIHDR_SetVdmParaTmapAddr(gstVdpCoefBufAddr.u32CoefPhyAddr[VDP_COEF_BUF_VDM_TONEMAP]);


#if !CBB_CFG_FROM_PQ
    if(enHiHdrMode == HIHDR_HDR10_IN_SDR_OUT)
    {
        VDP_PRINT("DeGamma Coef : VdmSceneMode == VDM_HDR10_IN_SDR_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32TMLutHDR102SDR     ;
    }
    else if(enHiHdrMode == HIHDR_HLG_IN_HDR10_OUT)
    {
        VDP_PRINT("DeGamma Coef : VdmSceneMode == VDM_BBC_IN_HDR10_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32TMLutBBC2HDR10     ;
    }
    else if(enHiHdrMode == HIHDR_HLG_IN_SDR_OUT)
    {
        VDP_PRINT("DeGamma Coef : VdmSceneMode == VDM_BBC_IN_SDR_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32TMLutBBC2SDR     ;
    }
    else if(enHiHdrMode == HIHDR_SLF_IN_SDR_OUT)
    {
        VDP_PRINT("DeGamma Coef : VdmSceneMode == VDM_AVS_IN_SDR_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32TMLutAVS2SDR     ;
    }
    else if(enHiHdrMode == HIHDR_SLF_IN_HDR10_OUT)
    {
        VDP_PRINT("DeGamma Coef : VdmSceneMode == VDM_AVS_IN_HDR10_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32TMLutAVS2HDR10     ;
    }
    else if(enHiHdrMode == HIHDR_HDR10_IN_HLG_OUT)
    {
        VDP_PRINT("DeGamma Coef : VdmSceneMode == VDM_HDR10_IN_BBC_OUT\n");

        p_coef_array[0]    = (HI_S32*)u32TMLutHDR102BBC     ;
    }
    else if(enHiHdrMode == HIHDR_XVYCC)
    {
        VDP_PRINT("ToneMapping Coef : VdmSceneMode == HIHDR_XVYCC\n");

        p_coef_array[0]    = (HI_S32*)u32TMLutAVS2SDR     ;
    }
    else if(enHiHdrMode == HIHDR_SDR_BT2020CL_IN_BT709_OUT)
    {
        VDP_PRINT("ToneMapping Coef : VdmSceneMode == VDM_SDR_BT2020CL_IN_BT709_OUT\n");
        p_coef_array[0]    = (HI_S32*)u32TMLutAVS2HDR10     ;
    }
    else
    {
        VDP_PRINT("DeGamma Coef : VdmSceneMode == Default !\n");
        p_coef_array[0]    = (HI_S32*)u32TMLut     ;
    }
#else
    if (HI_NULL == (HI_S32*)pstHiHdrCfg->stTMAP.pu32LUTTM)
    {
        VDP_PRINT("pstHiHdrCfg is NULL!\n");
        return;
    }

            p_coef_array[0]    = (HI_S32*)pstHiHdrCfg->stTMAP.pu32LUTTM;
#endif


    stCoefSend.coef_addr         = addr                     ;
    stCoefSend.sti_type          = STI_FILE_COEF_DM         ;
    stCoefSend.fp_coef           = fp_hihdr_vdm_degmm_coef  ;
    stCoefSend.lut_num           = 1                        ;
    stCoefSend.burst_num         = 1                        ;
    stCoefSend.cycle_num         = 8                        ;
    stCoefSend.p_coef_array      = p_coef_array             ;
    stCoefSend.lut_length        = lut_length               ;
    stCoefSend.coef_bit_length   = coef_bit_length          ;
    stCoefSend.data_type         = COEF_DATA_TYPE_S32       ;

    VDP_DRV_SendCoef(&stCoefSend);
    VDP_HIHDR_SetVdmParaTmapUpd(1);

    return;
}
