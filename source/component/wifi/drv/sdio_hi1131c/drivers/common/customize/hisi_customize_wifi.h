/*
 *
 * Copyright (C), 2001-2012, Hisilicon Tech. Co., Ltd.
 *
 *
 * File Name     : hisi_customize_wifi.h
 * Version       : Initial Draft
 * Author        : 
 * Created       : 2015/10/08
 * Last Modified :
 * Description   :
 * Function List :
 * History       :
 * 1.Date        : 2015/10/08
 *   Author      : 
 *   Modification: Created file
 *
 */

#ifndef __HISI_CUSTOMIZE_WIFI_H__
#define __HISI_CUSTOMIZE_WIFI_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE

#define NVRAM_PARAMS_ARRAY      "nvram_params"

#define MAC_LEN                 6
#define NV_WLAN_NUM             193
#define NV_WLAN_VALID_SIZE      12
#define MAC2STR(a)              (a)[0], "**", "**", "**", (a)[4], (a)[5]
#define MACFMT                  "%02x:%s:%s:%s:%02x:%02x"
#define MAC2STR_ALL(a)          (a)[0], (a)[1], (a)[2], (a)[3], (a)[4], (a)[5]
#define MACFMT_ALL              "%02x:%02x:%02x:%02x:%02x:%02x"
#define CUS_TAG_INI                     0x01
#define CUS_TAG_DTS                     0x02
#define CUS_TAG_NV                      0x03
#define CALI_TXPWR_PA_DC_REF_MIN        (1000)
#define CALI_TXPWR_PA_DC_REF_MAX        (10000)
#define CALI_TXPWR_PA_DC_FRE_MIN        (0)
#define CALI_TXPWR_PA_DC_FRE_MAX        (78)
#define CALI_BT_TXPWR_PA_DC_REF_MAX     (15000)
#define CHN_EST_CTRL_EVB                (0x3C192240)
#define CHN_EST_CTRL_MATE7              (0x3C193240)
#define CHN_EST_CTRL_FPGA               (0x3C19A243)
#define PHY_POWER_REF_2G_3798           (0xDCE0F4)
#define PHY_POWER_REF_2G_EVB0           (0xDCE0F4)
#define RTC_CLK_FREQ_MIN                (32000)
#define RTC_CLK_FREQ_MAX                (33000)
#define RF_LINE_TXRX_GAIN_DB_2G_MIN     (-32)
#define RF_LINE_TXRX_GAIN_DB_5G_MIN     (-12)
#define PSD_THRESHOLD_MIN               (-15)
#define PSD_THRESHOLD_MAX               (-10)
#define LNA_GAIN_DB_MIN                 (-10)
#define LNA_GAIN_DB_MAX                 (20)
#define NUM_OF_NV_MAX_TXPOWER           (45)                                /* NVRAM中存储的各协议速率最大发射功率参数的个数 From:24G_11b_1M To:5G_VHT80_MCS7 */
#define NUM_OF_NV_PARAMS                (2 * NUM_OF_NV_MAX_TXPOWER + 1)     /* NVRAM中存储的参数值的总个数:每项power值对应一项scale，加上dpd开关 */
#define MAX_TXPOWER_MIN                 (130)                               /* 最大发送功率的最小有效值:130 13.0dbm */
#define MAX_TXPOWER_MAX                 (238)                               /* 最大发送功率的最大有效值:238 23.8dbm */
#define NUM_OF_BAND_EDGE_LIMIT          (6)                                 /* FCC边带认证参数个数 */
#define MAX_DBB_SCALE                   (0xEE)                              /* DBB SCALE最大有效值 */
#define TX_RATIO_MAX                    (2000)                              /* tx占空比的最大有效值 */
#define TX_PWR_COMP_VAL_MAX             (50)                                /* 发射功率补偿值的最大有效值 */
#define MORE_PWR_MAX                    (50)                                /* 根据温度额外补偿的发射功率的最大有效值 */
#define COUNTRY_CODE_LEN                (3)                                 /* 国家码位数 */

/* DEFINED FOR WIFI READ DTS FILE */
//#define CUST_MODU_DTS           (0x50)

/* 定制化 DTS CONFIG ID */
typedef enum
{
    /* 5g开关 */
    WLAN_CFG_DTS_BAND_5G_ENABLE = 0,
    /* 校准 */
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN1,
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_START = WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN1,     /* 校准 2g TXPWR_REF起始配置ID */
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN2,
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN3,
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN4,
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN5,
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN6,
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN7,
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN8,
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN9,
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN10,
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN11,
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN12,
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN13,
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_5G_VAL_BAND1,
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_5G_START = WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_5G_VAL_BAND1,    /* 校准 5g TXPWR_REF起始配置ID */
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_5G_VAL_BAND2,
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_5G_VAL_BAND3,
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_5G_VAL_BAND4,
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_5G_VAL_BAND5,
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_5G_VAL_BAND6,
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_5G_VAL_BAND7,
    WLAN_CFG_DTS_CALI_TONE_AMP_GRADE,
    /* FCC认证 */
    WLAN_CFG_DTS_BAND_EDGE_LIMIT_2G_11G_TXPWR,                                                      /* FCC CH1,CH11 band edge limit */      //21
    WLAN_CFG_DTS_BAND_EDGE_LIMIT_TXPWR_START = WLAN_CFG_DTS_BAND_EDGE_LIMIT_2G_11G_TXPWR,           /* FCC认证:TXPWR 起始配置ID */
    WLAN_CFG_DTS_BAND_EDGE_LIMIT_2G_11N_HT20_TXPWR,                                                 /* FCC CH1,CH11 band edge limit */
    WLAN_CFG_DTS_BAND_EDGE_LIMIT_2G_11N_HT40_TXPWR,                                                 /* FCC CH3,CH9 band edge limit */
    WLAN_CFG_DTS_BAND_EDGE_LIMIT_5G_11A_HT20_VHT20_TXPWR,                                           /* FCC CH36、64、100、149、165, band edge limit */
    WLAN_CFG_DTS_BAND_EDGE_LIMIT_5G_HT40_VHT40_TXPWR,                                               /* FCC CH38,CH62 、102、151，band edge limit */
    WLAN_CFG_DTS_BAND_EDGE_LIMIT_5G_VHT80_TXPWR,                                                    /* FCC CH42、58、106、155，band edge limit */
    WLAN_CFG_DTS_BAND_EDGE_LIMIT_2G_11G_DBB_SCALING,                                                /* FCC CH1,CH11 dbb scaling */
    WLAN_CFG_DTS_BAND_EDGE_LIMIT_SCALE_START = WLAN_CFG_DTS_BAND_EDGE_LIMIT_2G_11G_DBB_SCALING,     /* FCC认证:SCALE 起始配置ID */
    WLAN_CFG_DTS_BAND_EDGE_LIMIT_2G_11N_HT20_DBB_SCALING,                                           /* FCC CH1,CH11 dbb scaling */
    WLAN_CFG_DTS_BAND_EDGE_LIMIT_2G_11N_HT40_DBB_SCALING,                                           /* FCC CH3,CH9 dbb scaling */
    WLAN_CFG_DTS_BAND_EDGE_LIMIT_5G_11A_HT20_VHT20_DBB_SCALING,                                     /* FCC CH36、64、100、149、165, dbb scaling */
    WLAN_CFG_DTS_BAND_EDGE_LIMIT_5G_HT40_VHT40_DBB_SCALING,                                         /* FCC CH38,CH62 、102、151，dbb scaling */
    WLAN_CFG_DTS_BAND_EDGE_LIMIT_5G_VHT80_DBB_SCALING,                                              /* FCC CH42、58、106、155，dbb scaling */
    /* rf register */
    WLAN_CFG_DTS_RF_REG117,                     //33
    WLAN_CFG_DTS_RF_FIRST = WLAN_CFG_DTS_RF_REG117,
    WLAN_CFG_DTS_RF_REG123,
    WLAN_CFG_DTS_RF_REG124,
    WLAN_CFG_DTS_RF_REG125,
    WLAN_CFG_DTS_RF_REG126,
    WLAN_CFG_DTS_RF_LAST = WLAN_CFG_DTS_RF_REG126,
    /* bt tmp */
    WLAN_CFG_DTS_BT_CALI_TXPWR_PA_REF_BAND1,    //37
    WLAN_CFG_DTS_BT_CALI_TXPWR_PA_REF_BAND2,
    WLAN_CFG_DTS_BT_CALI_TXPWR_PA_REF_BAND3,
    WLAN_CFG_DTS_BT_CALI_TXPWR_PA_REF_BAND4,
    WLAN_CFG_DTS_BT_CALI_TXPWR_PA_REF_BAND5,
    WLAN_CFG_DTS_BT_CALI_TXPWR_PA_REF_BAND6,
    WLAN_CFG_DTS_BT_CALI_TXPWR_PA_REF_BAND7,
    WLAN_CFG_DTS_BT_CALI_TXPWR_PA_REF_BAND8,
    WLAN_CFG_DTS_BT_CALI_TXPWR_PA_NUM,          //45
    WLAN_CFG_DTS_BT_CALI_TXPWR_PA_FRE1,
    WLAN_CFG_DTS_BT_CALI_TXPWR_PA_FRE2,
    WLAN_CFG_DTS_BT_CALI_TXPWR_PA_FRE3,
    WLAN_CFG_DTS_BT_CALI_TXPWR_PA_FRE4,
    WLAN_CFG_DTS_BT_CALI_TXPWR_PA_FRE5,
    WLAN_CFG_DTS_BT_CALI_TXPWR_PA_FRE6,
    WLAN_CFG_DTS_BT_CALI_TXPWR_PA_FRE7,
    WLAN_CFG_DTS_BT_CALI_TXPWR_PA_FRE8,         //53
    WLAN_CFG_DTS_BT_CALI_TONE_AMP_GRADE,

    WLAN_CFG_DTS_BUTT,
}WLAN_CFG_DTS;

/* 定制化 INI CONFIG ID */
typedef enum
{
    /* COUNTRY CODE */
    WLAN_CFG_INIT_COUNTRY_CODE = 0,
    /* ROAM */
    WLAN_CFG_INIT_ROAM_SWITCH,
    WLAN_CFG_INIT_SCAN_ORTHOGONAL,
    WLAN_CFG_INIT_TRIGGER_B,
    WLAN_CFG_INIT_TRIGGER_A,
    WLAN_CFG_INIT_DELTA_B,
    WLAN_CFG_INIT_DELTA_A,

    /* 性能 */
    WLAN_CFG_INIT_AMPDU_TX_MAX_NUM,
    WLAN_CFG_INIT_USED_MEM_FOR_START,
    WLAN_CFG_INIT_USED_MEM_FOR_STOP,
    WLAN_CFG_INIT_RX_ACK_LIMIT,                     //10
    WLAN_CFG_INIT_SDIO_D2H_ASSEMBLE_COUNT,
    WLAN_CFG_INIT_SDIO_H2D_ASSEMBLE_COUNT,
    /* LINKLOSS */
    WLAN_CFG_INIT_LINK_LOSS_THRESHOLD_WLAN_NEAR,    //这里不能直接赋值
    WLAN_CFG_INIT_LINK_LOSS_THRESHOLD_WLAN_FAR,
    WLAN_CFG_INIT_LINK_LOSS_THRESHOLD_P2P,
    /* 自动调频 */
    WLAN_CFG_INIT_AUTO_FREQ_ENABLE,                 //16
    WLAN_CFG_INIT_PSS_THRESHOLD_LEVEL_0,
    WLAN_CFG_INIT_CPU_FREQ_LIMIT_LEVEL_0,
    WLAN_CFG_INIT_DDR_FREQ_LIMIT_LEVEL_0,
    WLAN_CFG_INIT_PSS_THRESHOLD_LEVEL_1,
    WLAN_CFG_INIT_CPU_FREQ_LIMIT_LEVEL_1,
    WLAN_CFG_INIT_DDR_FREQ_LIMIT_LEVEL_1,
    WLAN_CFG_INIT_PSS_THRESHOLD_LEVEL_2,
    WLAN_CFG_INIT_CPU_FREQ_LIMIT_LEVEL_2,
    WLAN_CFG_INIT_DDR_FREQ_LIMIT_LEVEL_2,
    WLAN_CFG_INIT_PSS_THRESHOLD_LEVEL_3,
    WLAN_CFG_INIT_CPU_FREQ_LIMIT_LEVEL_3,
    WLAN_CFG_INIT_DDR_FREQ_LIMIT_LEVEL_3,
    WLAN_CFG_INIT_DEVICE_TYPE_LEVEL_0,
    WLAN_CFG_INIT_DEVICE_TYPE_LEVEL_1,
    WLAN_CFG_INIT_DEVICE_TYPE_LEVEL_2,
    WLAN_CFG_INIT_DEVICE_TYPE_LEVEL_3,
    /* 低功耗 */
    WLAN_CFG_INIT_POWERMGMT_SWITCH,                 //33
    /* 可维可测 */
    WLAN_CFG_INIT_LOGLEVEL,
    /* PHY算法 */
    WLAN_CFG_INIT_CHN_EST_CTRL,
    WLAN_CFG_INIT_POWER_REF_2G,
    /* 时钟信息 */
    WLAN_CFG_INIT_RTS_CLK_FREQ,
    WLAN_CFG_INIT_CLK_TYPE,
    /* 2G RF前端 */
    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_2G_BAND1_MULT4,    //39
    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_2G_BAND_START = WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_2G_BAND1_MULT4,
    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_2G_BAND1_MULT10,
    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_2G_BAND2_MULT4,
    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_2G_BAND2_MULT10,
    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_2G_BAND3_MULT4,
    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_2G_BAND3_MULT10,
    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_2G_BAND_END = WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_2G_BAND3_MULT10,
    /* 5G RF前端 */
    WLAN_CFG_INIT_RF_LINE_RX_GAIN_DB_5G,
    WLAN_CFG_INIT_LNA_GAIN_DB_5G,
    WLAN_CFG_INIT_RF_LINE_TX_GAIN_DB_5G,
    WLAN_CFG_INIT_EXT_SWITCH_ISEXIST_5G,
    WLAN_CFG_INIT_EXT_PA_ISEXIST_5G,
    WLAN_CFG_INIT_EXT_LNA_ISEXIST_5G,
    WLAN_CFG_INIT_LNA_ON2OFF_TIME_NS_5G,
    WLAN_CFG_INIT_LNA_OFF2ON_TIME_NS_5G,
    /* 温度上升导致发射功率下降过多的功率补偿 */
    WLAN_CFG_INIT_TX_RATIO_LEVEL_0,                 /* tx占空比 */                      //55
    WLAN_CFG_INIT_TX_PWR_COMP_VAL_LEVEL_0,          /* 发射功率补偿值 */
    WLAN_CFG_INIT_TX_RATIO_LEVEL_1,
    WLAN_CFG_INIT_TX_PWR_COMP_VAL_LEVEL_1,
    WLAN_CFG_INIT_TX_RATIO_LEVEL_2,
    WLAN_CFG_INIT_TX_PWR_COMP_VAL_LEVEL_2,
    WLAN_CFG_INIT_MORE_PWR,                         /* 根据温度额外补偿的发射功率 */
    /* SCAN */
    WLAN_CFG_INIT_RANDOM_MAC_ADDR_SCAN,
    /* 11AC2G */
    WLAN_CFG_INIT_11AC2G_ENABLE,                    /* 11ac2g开关 */                    //63
    WLAN_CFG_INIT_DISABLE_CAPAB_2GHT40,             /* 2ght40禁止开关 */

    WLAN_CFG_INIT_BUTT,
}WLAN_CFG_INIT;

/* 定制化 NVRAM PARAMS INDEX */
typedef enum
{
    NVRAM_PARAMS_INDEX_0   = 0,
    NVRAM_PARAMS_INDEX_1   = 1,
    NVRAM_PARAMS_INDEX_2   = 2,
    NVRAM_PARAMS_INDEX_3   = 3,
    NVRAM_PARAMS_INDEX_4   = 4,
    NVRAM_PARAMS_INDEX_5   = 5,
    NVRAM_PARAMS_INDEX_6   = 6,
    NVRAM_PARAMS_INDEX_7   = 7,
    NVRAM_PARAMS_INDEX_8   = 8,
    NVRAM_PARAMS_INDEX_9   = 9,
    NVRAM_PARAMS_INDEX_10  = 10,
    NVRAM_PARAMS_INDEX_11  = 11,
    NVRAM_PARAMS_INDEX_12  = 12,
    NVRAM_PARAMS_INDEX_13  = 13,
    NVRAM_PARAMS_INDEX_14  = 14,
    NVRAM_PARAMS_INDEX_15  = 15,
    NVRAM_PARAMS_INDEX_16  = 16,
    NVRAM_PARAMS_INDEX_17  = 17,
    NVRAM_PARAMS_INDEX_18  = 18,
    NVRAM_PARAMS_INDEX_19  = 19,
    NVRAM_PARAMS_INDEX_20  = 20,
    NVRAM_PARAMS_INDEX_21  = 21,
    NVRAM_PARAMS_INDEX_22  = 22,
    NVRAM_PARAMS_INDEX_23  = 23,
    NVRAM_PARAMS_INDEX_24  = 24,
    NVRAM_PARAMS_INDEX_25  = 25,

    NVRAM_PARAMS_INDEX_BUTT,
}NVRAM_PARAMS_INDEX;

typedef struct
{
    char*   name;
    int     case_entry;
} wlan_cfg_cmd;

/* 定制化HOST全局变量结构体 */
typedef struct
{
    /* ba tx 聚合数 */
    unsigned int    ul_ampdu_tx_max_num;
    /* 漫游 */
    unsigned char   uc_roam_switch;
    unsigned char   uc_roam_scan_band;
    unsigned char   uc_roam_scan_orthogonal;
    signed char     c_roam_trigger_b;
    signed char     c_roam_trigger_a;
    signed char     c_roam_delta_b;
    signed char     c_roam_delta_a;
    /* scan */
    unsigned char   uc_random_mac_addr_scan;
    /* capab */
    unsigned char   uc_disable_capab_2ght40;
} wlan_customize_stru;

extern wlan_customize_stru g_st_wlan_customize;
extern int hwifi_config_init(int);
extern int hwifi_get_init_value(int, int);
extern char* hwifi_get_country_code(void);
extern int hwifi_get_mac_addr(unsigned char *);
extern unsigned char* hwifi_get_nvram_params(void);

#endif /* #ifdef _PRE_PLAT_FEATURE_CUSTOMIZE */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif //hisi_customize_wifi.h

