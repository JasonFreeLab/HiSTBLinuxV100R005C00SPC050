//==============================================================================
//           Copyright (C), 2008-2014, Hisilicon Tech. Co., Ltd.
//==============================================================================
//  文件名称: imeida_peq_api.h
//  文件描述: 该文件包含PEQ算法库的各结构体定义信息和功能函数的声明信息
//            在使用算法库时需要包含此文件
//
//  结构体列表:
//      iMedia_PEQ_STRU_MEM_CONFIG  -- PEQ算法内存配置结构体
//      iMedia_PEQ_STRU_MEM_SIZE    -- PEQ算法内存大小结构体
//      iMedia_PEQ_STRU_VERSION     -- PEQ算法版本信息结构体
//      iMedia_PEQ_STRU_PARAMS      -- PEQ算法参数配置结构体
//
//  函数列表:
//      iMedia_PEQ_GetSize()        -- 获取内存大小
//      iMedia_PEQ_Init()           -- 初始化算法实例(通道变量)
//      iMedia_PEQ_Apply()          -- 算法处理应用
//      iMedia_PEQ_SetParams()      -- 设置算法参数配置
//      iMedia_PEQ_GetParams()      -- 获取算法参数配置
//      iMedia_PEQ_GetVersion()     -- 获取算法库版本信息，包括所用编译器版本、
//                                     发布时间和版本号
//
//  修改记录: 见文件尾
//==============================================================================
#ifndef _IMEDIA_PEQ_API_H_
#define _IMEDIA_PEQ_API_H_

#include "imedia_typedef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif // __cplusplus

//==============================================================================
//     基本常量宏定义
//==============================================================================
#define    IMEDIA_PEQ_FRAME_LENGTH_S             (256)   // 单声道帧长
#define    IMEDIA_PEQ_SAMPLE_48K                 (48000) // 采样率
#define    IMEDIA_PEQ_BAND_NUM_MAX               (10)    // 最大频段数

//==============================================================================
//     返回码定义信息
//==============================================================================
// BEGIN: modified by y00278990 20141120 问题单: DTS2014112004982
#define    IMEDIA_PEQ_EOK                        (0)     // 操作成功返回码
#define    IMEDIA_PEQ_INV_INIT_PPHANDLE          (-1)    // Init接口中无效句柄
#define    IMEDIA_PEQ_INV_INIT_BASE              (-2)    // Init接口中无效的存储缓冲区
#define    IMEDIA_PEQ_INV_INIT_MEM_SIZE          (-3)    // Init接口中存储缓冲区长度小于要求的长度
#define    IMEDIA_PEQ_INV_INIT_PST_PARAMS        (-4)    // Init接口中配置参数结构体指针为空
#define    IMEDIA_PEQ_INV_CHECK_BAND_NUM         (-5)    // 配置的段数超出范围
#define    IMEDIA_PEQ_INV_CHECK_FILTERTYPE       (-6)    // 配置的滤波器类型超出范围
#define    IMEDIA_PEQ_INV_CHECK_CUTOFF           (-7)    // 配置的中心频率设置错误
#define    IMEDIA_PEQ_INV_CHECK_Q                (-8)    // 配置的品质因子超出范围
#define    IMEDIA_PEQ_INV_CHECK_GAIN             (-9)    // 配置的增益值超出范围
#define    IMEDIA_PEQ_INV_APPLY_HANDLE           (-10)   // Apply接口中通道变量指针为空
#define    IMEDIA_PEQ_INV_APPLY_INBUF            (-11)   // Apply接口中输入数据地址为空
#define    IMEDIA_PEQ_INV_APPLY_OUTBUF           (-12)   // Apply接口中输出数据地址为空
#define    IMEDIA_PEQ_INV_APPLY_UNINITIED        (-13)   // Apply接口中通道未初始化
#define    IMEDIA_PEQ_INV_SETPARAMS_HANDLE       (-14)   // 参数设置接口中句柄为空
#define    IMEDIA_PEQ_INV_SETPARAMS_PST_PARAMS   (-15)   // 参数设置接口中参数结构体指针为空
#define    IMEDIA_PEQ_INV_SETPARAMS_UNINITIED    (-16)   // 调用SetParams接口前没有Init
#define    IMEDIA_PEQ_INV_GETPARAMS_HANDLE       (-17)   // 参数获取接口中句柄为空
#define    IMEDIA_PEQ_INV_GETPARAMS_PST_PARAMS   (-18)   // 参数获取接口中接收参数结构体指针为空
#define    IMEDIA_PEQ_INV_GETPARAMS_UNINITIED    (-19)   // 调用GetParams接口前没有Init
#define    IMEDIA_PEQ_INV_GETVERSION_PPVERSION   (-20)   // 版本信息接口中输入指针为空
#define    IMEDIA_PEQ_INV_GETSIZE_MEMSIZE_PST    (-21)   // 无效的内存大小结构体指针
#define    IMEDIA_PEQ_INV_GETSIZE_MEMCFG_PST     (-22)   // 无效的内存配置结构体指针
#define    IMEDIA_PEQ_INV_GETSIZE_SAMPLE_RATE    (-23)   // 无效的采样率
// END: modified by y00278990 20141120 问题单: DTS2014112004982
//==============================================================================
//     版本信息结构体
//==============================================================================
// DSP代码版本信息结构体
typedef struct  tagPEQ_STRU_VERSION
{
    IMEDIA_INT8    ucCgtVersion[100];     // Code Generation Tools版本号
    IMEDIA_INT8    ucReleaseVer[100];     // 算法库版本号
    IMEDIA_INT8    ucReleaseTime[100];    // 编译日期
} iMedia_PEQ_STRU_VERSION, *iMedia_PEQ_PST_VERSION;

//==============================================================================
//     滤波器枚举类型
//==============================================================================
typedef enum
{
    PEQ_HP_FILTER = 0,  // 高通滤波器 HP
    PEQ_LS_FILTER = 1,  // 低频搁架滤波器 LS
    PEQ_PK_FILTER = 2,  // 峰值滤波器 PK
    PEQ_HS_FILTER = 3,  // 高频搁架滤波器 HS
    PEQ_LP_FILTER = 4   // 低通滤波器 LP
} iMedia_PEQ_Filter_Type;

//==============================================================================
//     PEQ的内存配置结构体
//==============================================================================
typedef struct tagPEQ_STRU_MEM_CONFIG
{
    IMEDIA_INT32  iSampleRate;                                    // 数据采样率
    IMEDIA_INT8   cReserve[4];                                    // 保留区
} iMedia_PEQ_STRU_MEM_CONFIG, *iMedia_PEQ_PST_MEM_CONFIG;

//==============================================================================
//     PEQ的内存大小结构体
//==============================================================================
typedef struct tagPEQ_STRU_MEM_SIZE
{
    IMEDIA_UINT32   uiStrSize;                                    // 通道变量大小, 单位为字节
    IMEDIA_INT32    iInSize;                                      // 无效参数
    IMEDIA_INT32    iOutSize;                                     // 无效参数
} iMedia_PEQ_STRU_MEM_SIZE, *iMedia_PEQ_PST_MEM_SIZE;

//==============================================================================
//     PEQ的配置参数，参数均可动态配置
//==============================================================================
typedef struct tagPEQ_STRU_PARAMS
{
    IMEDIA_UINT8  filtertype[IMEDIA_PEQ_BAND_NUM_MAX]; // 滤波器类型
                                                       // 范围: [0: HP, 1: LS, 2: PK, 3: HS 4: LP]
    IMEDIA_UINT16 cutoff[IMEDIA_PEQ_BAND_NUM_MAX];     // 中心频率，单位Hz
                                                       // 范围: HP and LS[20, 4000], PK[20, 22000], HS and LP[4000, 22000]
    IMEDIA_UINT16 q[IMEDIA_PEQ_BAND_NUM_MAX];          // Q值，*10定点，范围: HS and LS[7, 10], PK[5, 100], 高低通为7
                                                       // modified by y00278990 20141120 问题单: DTS2014112005541
    IMEDIA_INT16  gain[IMEDIA_PEQ_BAND_NUM_MAX];       // 频段增益, *1000定标，高低通滤波器增益为0dB，其他类型的滤波器增益范围[-15000, 15000]dB
                                                       // modified by y00278990 20141120 问题单: DTS2014112005541
    IMEDIA_UINT32 uiBandNum;                           // 频段数，范围(0, 10]
} iMedia_PEQ_STRU_PARAMS, *iMedia_PEQ_PST_PARAMS;

//==============================================================================
// 函数名称: iMedia_PEQ_GetSize
// 功能描述: 获取通道大小
// 输入参数:
//     pstConf     -- 内存配置结构体
// 输出参数:
//     pstMemSize  -- 通道大小结构体
// 返回参数:
//     ret         -- 操作返回码IMEDIA_PEQ_EOK表示成功，其他返回码表示失败
//==============================================================================
IMEDIA_INT32 iMedia_PEQ_GetSize(iMedia_PEQ_PST_MEM_SIZE pstMemSize, iMedia_PEQ_PST_MEM_CONFIG pstConf);

//==============================================================================
// // 函数名称: iMedia_PEQ_Init
// 功能描述: 初始化算法实例(通道变量)，并返回其句柄
// 输入参数:
//     ppHandle    -- 对象句柄
//     pMemBase    -- 通道变量起始地址
//     uiMemSize   -- 通道变量空间大小
//     pstParams   -- PEQ参数配置结构体指针
// 输出参数:
//     ppHandle    -- 对象句柄
// 返回参数:
//     ret         -- 操作返回码 IMEDIA_PEQ_EOK表示成功，其他返回码表示失败
//==============================================================================
IMEDIA_INT32 iMedia_PEQ_Init(IMEDIA_VOID** ppHandle,
                             const IMEDIA_VOID* pMemBase,
                             IMEDIA_UINT32 uiMemSize,
                             const iMedia_PEQ_PST_PARAMS pstParams);

//==============================================================================
// 函数名称: iMedia_PEQ_Apply
// 功能描述: 算法处理应用(处理一帧512点，约5.33ms)
// 输入参数:
//     pHandle    -- 对象句柄
//     psIn       -- 输入数据缓冲区指针
// 输出参数:
//     psOut      -- 输出数据缓冲区指针
// 返回参数:
//     ret        -- 操作返回码 IMEDIA_PEQ_EOK表示成功，其他返回码表示失败
//==============================================================================
IMEDIA_INT32 iMedia_PEQ_Apply(IMEDIA_VOID* pHandle, const IMEDIA_INT16* psIn, IMEDIA_INT16* psOut);

//==============================================================================
// 函数名称: iMedia_PEQ_SetParams
// 功能描述: 动态参数配置接口，切换参数配置时使用。
//           注意: 该接口仅是调试接口，只能在调试阶段使用，不建议现网使用。
// 输入参数:
//     pHandle    -- 对象句柄
//     pstParams  -- 算法参数配置结构体指针
// 输出参数:
//     pHandle    -- 对象句柄
// 返回参数:
//     ret        -- 操作返回码 IMEDIA_PEQ_EOK表示成功，其他返回码表示失败
//==============================================================================
IMEDIA_INT32 iMedia_PEQ_SetParams(IMEDIA_VOID* pHandle, const iMedia_PEQ_PST_PARAMS pstParams);

//==============================================================================
// 函数名称: iMedia_PEQ_GetParams
// 功能描述: 动态参数配置接口，切换参数配置时使用。
//           注意: 该接口仅是调试接口，只能在调试阶段使用，不建议现网使用。
// 输入参数:
//     pHandle   -- 对象句柄
//     pstParams -- 算法参数配置结构体指针
// 输出参数:
//     pHandle   -- 对象句柄
// 返回参数:
//     ret       -- 操作返回码 IMEDIA_PEQ_EOK表示成功，其他返回码表示失败
//==============================================================================
IMEDIA_INT32 iMedia_PEQ_GetParams(const IMEDIA_VOID* pHandle, iMedia_PEQ_PST_PARAMS pstParams);

//==============================================================================
// 函数名称: iMedia_PEQ_GetVersion
// 功能描述: 获取算法库版本信息，包括所用编译器版本、发布时间和版本号
// 输入参数:
//     ppVersion  -- 版本信息结构体句柄
// 输出参数:
//     ppVersion  -- 版本信息结构体句柄
// 返回参数:
//     ret        -- 操作返回码 IMEDIA_PEQ_EOK表示成功，其他返回码表示失败
//==============================================================================
IMEDIA_INT32 iMedia_PEQ_GetVersion(iMedia_PEQ_PST_VERSION* ppVersion);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif // __cplusplus

#endif // __IMEDIA_PEQ_API_H__

//==============================================================================
// 修改记录:
//  2013-10-24 14:02:23    建立文件
//                         创建人：黄涛/h00207014
//  2014-08-21 15:33:25    修改PEQ接口
//                         修改人：熊佳/x00227689
//  2014-09-04 10:12:51    完成PEQ基本功能和参数范围确认
//                         修改人：熊佳/x00227689
//  2014-10-28 14:00:00    完成接口的修改
//                         修改人：闫丽霞/y00278990
//  2014-11-20 16:05:12    修改问题单：DTS2014112004982和DTS2014112005541
//                         修改人：闫丽霞/y00278990
//==============================================================================

