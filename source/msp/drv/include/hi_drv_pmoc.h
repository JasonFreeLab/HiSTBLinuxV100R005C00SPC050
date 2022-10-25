#ifndef  __HI_DRV_PMOC_H__
#define  __HI_DRV_PMOC_H__

#include "hi_unf_pmoc.h"
#include "hi_debug.h"

/* add register macro */
#define C51_BASE             0xf8400000

#if defined(CHIP_TYPE_hi3796mv200)
#define C51_SIZE             0xf000 //60K
#define C51_DATA             0x7000 //28K
#define MCU_CODE_MAXSIZE     0x7000 //32K
#else 
#define C51_SIZE             0x8000 //32K
#define C51_DATA             0x7000 //28K
#define MCU_CODE_MAXSIZE     0x6000 //24K
#endif

#define DEFAULT_INIT_FREQ 1200000

#if    defined(CHIP_TYPE_hi3716mv410)   \
    || defined(CHIP_TYPE_hi3716mv420)
#define HI_VDD_MPU_OPP1_UV 950
#define HI_VDD_MPU_OPP2_UV 1000
#define HI_VDD_MPU_OPP3_UV 1100
#define HI_VDD_MPU_OPP4_UV 1160
#define HI_VDD_MPU_OPP5_UV 1280
#define HI_VDD_MPU_OPP11_UV 950
#define HI_VDD_MPU_OPP12_UV 950
#define HI_VDD_MPU_OPP1_VMIN 950
#define HI_VDD_MPU_OPP2_VMIN 950
#define HI_VDD_MPU_OPP3_VMIN 970
#define HI_VDD_MPU_OPP4_VMIN 1050
#define HI_VDD_MPU_OPP5_VMIN 1120
#define HI_VDD_MPU_OPP11_VMIN 950
#define HI_VDD_MPU_OPP12_VMIN 950
#define HI_VDD_MPU_OPP1_HPM 0xb2
#define HI_VDD_MPU_OPP2_HPM 0xb2
#define HI_VDD_MPU_OPP3_HPM 0xcc
#define HI_VDD_MPU_OPP4_HPM 0xe8
#define HI_VDD_MPU_OPP5_HPM 0x113
#define HI_VDD_MPU_OPP11_HPM 0xb2
#define HI_VDD_MPU_OPP12_HPM 0xb2
#elif defined(CHIP_TYPE_hi3798cv200)
#define HI_VDD_MPU_OPP1_UV 840
#define HI_VDD_MPU_OPP2_UV 840
#define HI_VDD_MPU_OPP3_UV 870
#define HI_VDD_MPU_OPP4_UV 950
#define HI_VDD_MPU_OPP5_UV 990
#define HI_VDD_MPU_OPP6_UV 1100
#define HI_VDD_MPU_OPP7_UV 1150
#define HI_VDD_MPU_OPP1_VMIN 840
#define HI_VDD_MPU_OPP2_VMIN 840
#define HI_VDD_MPU_OPP3_VMIN 840
#define HI_VDD_MPU_OPP4_VMIN 880
#define HI_VDD_MPU_OPP5_VMIN 880
#define HI_VDD_MPU_OPP6_VMIN 970
#define HI_VDD_MPU_OPP7_VMIN 1020
#define HI_VDD_MPU_OPP1_HPM 0xc9
#define HI_VDD_MPU_OPP1_HPM_FF 0xc9
#define HI_VDD_MPU_OPP1_HPM_TT 0xc9
#define HI_VDD_MPU_OPP1_HPM_SS 0xc9
#define HI_VDD_MPU_OPP2_HPM 0xc9
#define HI_VDD_MPU_OPP2_HPM_FF 0xc9
#define HI_VDD_MPU_OPP2_HPM_TT 0xc9
#define HI_VDD_MPU_OPP2_HPM_SS 0xc9
#define HI_VDD_MPU_OPP3_HPM 0x100
#define HI_VDD_MPU_OPP3_HPM_FF 0x100
#define HI_VDD_MPU_OPP3_HPM_TT 0xe5
#define HI_VDD_MPU_OPP3_HPM_SS 0xe8
#define HI_VDD_MPU_OPP4_HPM 0x110
#define HI_VDD_MPU_OPP4_HPM_FF 0x110
#define HI_VDD_MPU_OPP4_HPM_TT 0x110
#define HI_VDD_MPU_OPP4_HPM_SS 0x110
#define HI_VDD_MPU_OPP5_HPM 0x12a
#define HI_VDD_MPU_OPP5_HPM_FF 0x12a
#define HI_VDD_MPU_OPP5_HPM_TT 0x122
#define HI_VDD_MPU_OPP5_HPM_SS 0x11c
#define HI_VDD_MPU_OPP6_HPM 0x14b
#define HI_VDD_MPU_OPP6_HPM_FF 0x14b
#define HI_VDD_MPU_OPP6_HPM_TT 0x14b
#define HI_VDD_MPU_OPP6_HPM_SS 0x14b
#define HI_VDD_MPU_OPP7_HPM 0x16a
#define HI_VDD_MPU_OPP7_HPM_FF 0x16a
#define HI_VDD_MPU_OPP7_HPM_TT 0x165
#define HI_VDD_MPU_OPP7_HPM_SS 0x15a
#elif  defined(CHIP_TYPE_hi3798mv100)   \
    || defined(CHIP_TYPE_hi3796mv100)   \
    || defined(CHIP_TYPE_hi3716dv100)
#define HI_VDD_MPU_OPP1_UV 980
#define HI_VDD_MPU_OPP2_UV 1150
#define HI_VDD_MPU_OPP3_UV 1300
#define HI_VDD_MPU_OPP4_UV 1300
#define HI_VDD_MPU_OPP5_UV 1420
#define HI_VDD_MPU_OPP6_UV 1495
#define HI_VDD_MPU_OPP1_VMIN 980
#define HI_VDD_MPU_OPP2_VMIN 1000
#define HI_VDD_MPU_OPP3_VMIN 1060
#define HI_VDD_MPU_OPP4_VMIN 1050
#define HI_VDD_MPU_OPP5_VMIN 1180
#define HI_VDD_MPU_OPP6_VMIN 1495
#define HI_VDD_MPU_OPP1_HPM 0x100
#define HI_VDD_MPU_OPP2_HPM 0xd0
#define HI_VDD_MPU_OPP3_HPM 0x10b
#define HI_VDD_MPU_OPP4_HPM 0x100
#define HI_VDD_MPU_OPP5_HPM 0x135
#define HI_VDD_MPU_OPP6_HPM 0x200
#elif defined(CHIP_TYPE_hi3798mv200_a)
#define HI_VDD_MPU_OPP1_UV 830
#define HI_VDD_MPU_OPP2_UV 830
#define HI_VDD_MPU_OPP3_UV 870
#define HI_VDD_MPU_OPP4_UV 990
#define HI_VDD_MPU_OPP5_UV 1020
#define HI_VDD_MPU_OPP6_UV 1150
#define HI_VDD_MPU_OPP7_UV 1250
#define HI_VDD_MPU_OPP1_VMIN 830
#define HI_VDD_MPU_OPP2_VMIN 830
#define HI_VDD_MPU_OPP3_VMIN 870
#define HI_VDD_MPU_OPP4_VMIN 990
#define HI_VDD_MPU_OPP5_VMIN 1020
#define HI_VDD_MPU_OPP6_VMIN 1150
#define HI_VDD_MPU_OPP7_VMIN 1250
#define HI_VDD_MPU_OPP1_HPM 0xf4
#define HI_VDD_MPU_OPP2_HPM 0xf4
#define HI_VDD_MPU_OPP3_HPM 0x106
#define HI_VDD_MPU_OPP4_HPM 0x134
#define HI_VDD_MPU_OPP5_HPM 0x14f
#define HI_VDD_MPU_OPP6_HPM 0x150
#define HI_VDD_MPU_OPP7_HPM 0x188
#elif defined(CHIP_TYPE_hi3796mv200)
#define HI_VDD_MPU_OPP1_UV 900
#define HI_VDD_MPU_OPP2_UV 900
#define HI_VDD_MPU_OPP3_UV 910
#define HI_VDD_MPU_OPP4_UV 990
#define HI_VDD_MPU_OPP5_UV 1050
#define HI_VDD_MPU_OPP6_UV 1200
#define HI_VDD_MPU_OPP7_UV 1250
#define HI_VDD_MPU_OPP1_VMIN 900
#define HI_VDD_MPU_OPP2_VMIN 900
#define HI_VDD_MPU_OPP3_VMIN 870
#define HI_VDD_MPU_OPP4_VMIN 990
#define HI_VDD_MPU_OPP5_VMIN 1050
#define HI_VDD_MPU_OPP6_VMIN 1150
#define HI_VDD_MPU_OPP7_VMIN 1250
#define HI_VDD_MPU_OPP1_HPM 0xe6
#define HI_VDD_MPU_OPP2_HPM 0xe6
#define HI_VDD_MPU_OPP3_HPM 0xe6
#define HI_VDD_MPU_OPP4_HPM 0x11c
#define HI_VDD_MPU_OPP5_HPM 0x11c
#define HI_VDD_MPU_OPP6_HPM 0x14a
#define HI_VDD_MPU_OPP7_HPM 0x150
#elif defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv310)
#define HI_VDD_MPU_OPP1_UV 930
#define HI_VDD_MPU_OPP2_UV 930
#define HI_VDD_MPU_OPP3_UV 930
#define HI_VDD_MPU_OPP4_UV 990
#define HI_VDD_MPU_OPP5_UV 990
#define HI_VDD_MPU_OPP6_UV 1150
#define HI_VDD_MPU_OPP7_UV 1150
#define HI_VDD_MPU_OPP1_VMIN 930
#define HI_VDD_MPU_OPP2_VMIN 930
#define HI_VDD_MPU_OPP3_VMIN 930
#define HI_VDD_MPU_OPP4_VMIN 990
#define HI_VDD_MPU_OPP5_VMIN 990
#define HI_VDD_MPU_OPP6_VMIN 1150
#define HI_VDD_MPU_OPP7_VMIN 1150
#define HI_VDD_MPU_OPP1_HPM 0x150
#define HI_VDD_MPU_OPP2_HPM 0x150
#define HI_VDD_MPU_OPP3_HPM 0xf0
#define HI_VDD_MPU_OPP4_HPM 0x11c
#define HI_VDD_MPU_OPP5_HPM 0x11c
#define HI_VDD_MPU_OPP6_HPM 0x153
#define HI_VDD_MPU_OPP7_HPM 0x153
#define HI_VDD_MPU_OPP1_UV_300 800
#define HI_VDD_MPU_OPP2_UV_300 850
#define HI_VDD_MPU_OPP3_UV_300 930
#define HI_VDD_MPU_OPP4_UV_300 1100
#define HI_VDD_MPU_OPP5_UV_300 1100
#define HI_VDD_MPU_OPP6_UV_300 1150
#define HI_VDD_MPU_OPP7_UV_300 1250
#define HI_VDD_MPU_OPP1_VMIN_300 800
#define HI_VDD_MPU_OPP2_VMIN_300 850
#define HI_VDD_MPU_OPP3_VMIN_300 850
#define HI_VDD_MPU_OPP4_VMIN_300 950
#define HI_VDD_MPU_OPP5_VMIN_300 950
#define HI_VDD_MPU_OPP6_VMIN_300 1150
#define HI_VDD_MPU_OPP7_VMIN_300 1250
#define HI_VDD_MPU_OPP1_HPM_300 0x150
#define HI_VDD_MPU_OPP2_HPM_300 0x150
#define HI_VDD_MPU_OPP3_HPM_300 0xfa
#define HI_VDD_MPU_OPP4_HPM_300 0x140
#define HI_VDD_MPU_OPP5_HPM_300 0x140
#define HI_VDD_MPU_OPP6_HPM_300 0x153
#define HI_VDD_MPU_OPP7_HPM_300 0x153
#else
#error YOU MUST DEFINE  CHIP_TYPE!
#endif

#if    defined(CHIP_TYPE_hi3798mv100)   \
    || defined(CHIP_TYPE_hi3796mv100)   \
    || defined(CHIP_TYPE_hi3716dv100)
#define CPU_VMAX    1495    /*mv*/
#define CPU_VMIN    920     /*mv*/
#define CORE_VMAX   1315    /*mv*/
#define CORE_VMIN   900     /*mv*/
#elif  defined(CHIP_TYPE_hi3716mv410)   \
    || defined(CHIP_TYPE_hi3716mv420)
#define CPU_VMAX    1400    /*mv*/ //0.9-1.38
#define CPU_VMIN    900     /*mv*/
#define CORE_VMAX   1320    /*mv*/ //0.9 1.25
#define CORE_VMIN   900     /*mv*/
#elif  defined(CHIP_TYPE_hi3798cv200)
#define CPU_VMAX    1150    /*mv*/
#define CPU_VMIN    650     /*mv*/
#define CORE_VMAX   1150    /*mv*/
#define CORE_VMIN   650     /*mv*/
#elif  defined(CHIP_TYPE_hi3798mv200)   \
	|| defined(CHIP_TYPE_hi3798mv300)	\
    || defined(CHIP_TYPE_hi3798mv310)	\
    || defined(CHIP_TYPE_hi3798mv200_a) \
    || defined(CHIP_TYPE_hi3796mv200)
#define CPU_VMAX    1250    /*mv*/
#define CPU_VMIN    700     /*mv*/
#define CORE_VMAX   1250    /*mv*/
#define CORE_VMIN   700     /*mv*/
#else
#define CPU_VMAX    1315    /*mv*/
#define CPU_VMIN    900     /*mv*/
#define CORE_VMAX   1205    /*mv*/
#define CORE_VMIN   900     /*mv*/
#endif
#define PWM_STEP    5       /*mv*/
#define PWM_CLASS   2
#define CPU_DEVICE  0
#define CORE_DEVICE 1

typedef struct hiCPU_VF_S
{
    unsigned int freq;          /* unit: kHz */
    unsigned int hpmrecord;     /* hpm record */
    unsigned int vmin;          /* the minimum voltage of AVS */
    unsigned int vsetting;      /* the setting voltage of DVFS */
} CPU_VF_S;

typedef struct hiCPU_HPM_S
{
    unsigned int freq;          /* unit: kHz */
    unsigned int hpmrecord[4];   /* chip hpm record */
} CPU_HPM_S;


#define MAX_FREQ_NUM 7
extern CPU_VF_S cpu_freq_hpm_table[MAX_FREQ_NUM];

#define HI_FATAL_PM(fmt...) HI_FATAL_PRINT(HI_ID_PM, fmt)

#define HI_ERR_PM(fmt...)   HI_ERR_PRINT(HI_ID_PM, fmt)

#define HI_WARN_PM(fmt...)  HI_WARN_PRINT(HI_ID_PM, fmt)

#define HI_INFO_PM(fmt...)  HI_INFO_PRINT(HI_ID_PM, fmt)

HI_S32 HI_DRV_PMOC_Init(HI_VOID);
HI_S32 HI_DRV_PMOC_DeInit(HI_VOID);
HI_S32 HI_DRV_PMOC_SwitchSystemMode(HI_UNF_PMOC_MODE_E enSystemMode, HI_UNF_PMOC_ACTUAL_WKUP_E * penWakeUpStatus);
HI_S32 HI_DRV_PMOC_SetWakeUpAttr(HI_UNF_PMOC_WKUP_S_PTR pstAttr);
HI_S32 HI_DRV_PMOC_SetStandbyDispMode(HI_UNF_PMOC_STANDBY_MODE_S_PTR pstStandbyMode);
HI_S32 HI_DRV_PMOC_SetScene(HI_UNF_PMOC_SCENE_E eScene);
HI_S32 HI_DRV_PMOC_SetDevType(HI_UNF_PMOC_DEV_TYPE_S_PTR pdevType);

#endif  /*  __HI_DRV_PMOC_H__ */

