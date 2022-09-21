/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : wal_regdb.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2013年10月15日
  最近修改   :
  功能描述   : 管制域数据库
  函数列表   :
  修改历史   :
  1.日    期   : 2013年10月15日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "wal_regdb.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_WAL_REGDB_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION) || (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
/*
    以下管制域数据库由工具生成:
    Step 1: 从http://wireless.kernel.org/download/wireless-regdb/regulatory.bins/
            下载最新的管制域二进制文件regulatory.bin
    Step 2: regdbdump regulatory.bin >> db.txt
    Step 3: kernel/net/wireless/genregdb.awk db.txt >> wal_regdb.c
 */
/* 根据WIFI-2.4G-5G-国家码信道对应表更新管制域信息*/
#ifdef _PRE_WLAN_FEATURE_11D

static const struct ieee80211_regdomain regdom_AE = {
    .alpha2 = "AE",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 20, 0, 23, 0),
        REG_RULE(5250, 5330, 20, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 20, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 20, 0, 23,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_AF = {
    .alpha2 = "AF",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_AG = {
    .alpha2 = "AG",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_AI = {
    .alpha2 = "AI",
    .reg_rules = {
        REG_RULE(2402, 2472, 40, 0, 20, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_AL = {
    .alpha2 = "AL",
    .reg_rules = {
        REG_RULE(2402, 2482, 20, 0, 20, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_AM = {
    .alpha2 = "AM",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 20, 0, 18, 0),
        REG_RULE(5250, 5330, 20, 0, 18,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 3
};

static const struct ieee80211_regdomain regdom_AN = {
    .alpha2 = "AN",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 20, 0),
        REG_RULE(5250, 5330, 40, 0, 20,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 27,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_AO = {
    .alpha2 = "AO",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_AR = {
    .alpha2 = "AR",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 20, 3, 24, 0),
        REG_RULE(5250, 5330, 20, 3, 24,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5590, 20, 3, 24,
            NL80211_RRF_DFS | 0),
        REG_RULE(5650, 5710, 20, 3, 24,
            NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 20, 3, 30, 0),
    },
    .n_reg_rules = 6
};

static const struct ieee80211_regdomain regdom_AS = {
    .alpha2 = "AS",
    .reg_rules = {
        REG_RULE(2402, 2472, 40, 0, 30, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_AT = {
    .alpha2 = "AT",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 23, 0),
        REG_RULE(5250, 5330, 40, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 23,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_AU = {
    .alpha2 = "AU",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 3, 17, 0),
        REG_RULE(5250, 5330, 40, 3, 24,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5590, 40, 3, 24,
            NL80211_RRF_DFS | 0),
        REG_RULE(5650, 5710, 40, 3, 24,
            NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 40, 3, 30, 0),
    },
    .n_reg_rules = 6
};

static const struct ieee80211_regdomain regdom_AW = {
    .alpha2 = "AW",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_AZ = {
    .alpha2 = "AZ",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 18, 0),
        REG_RULE(5250, 5330, 40, 0, 18,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 18,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_BA = {
    .alpha2 = "BA",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 20, 0),
        REG_RULE(5250, 5330, 40, 0, 20,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 27,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_BD = {
    .alpha2 = "BD",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_BE = {
    .alpha2 = "BE",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 23, 0),
        REG_RULE(5250, 5330, 40, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 23,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_BG = {
    .alpha2 = "BG",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 23, 0),
        REG_RULE(5250, 5330, 40, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 23,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_BH = {
    .alpha2 = "BH",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 20, 0, 23, 0),
        REG_RULE(5250, 5330, 20, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 20, 0, 20, 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_BL = {
    .alpha2 = "BL",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 18, 0),
        REG_RULE(5250, 5330, 40, 0, 18,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 3
};

static const struct ieee80211_regdomain regdom_BM = {
    .alpha2 = "BM",
    .reg_rules = {
        REG_RULE(2402, 2472, 40, 0, 30, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_BN = {
    .alpha2 = "BN",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 20, 0),
        REG_RULE(5250, 5330, 40, 0, 20,
            NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 40, 0, 20, 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_BO = {
    .alpha2 = "BO",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 30, 0),
        REG_RULE(5170, 5250, 40, 0, 30, 0),
        REG_RULE(5250, 5330, 40, 0, 30,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 30,
            NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 40, 0, 30, 0),
    },
    .n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_BR = {
    .alpha2 = "BR",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 3, 17, 0),
        REG_RULE(5250, 5330, 40, 3, 24,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 3, 24,
            NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 40, 3, 30, 0),
    },
    .n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_BS = {
    .alpha2 = "BS",
    .reg_rules = {
        REG_RULE(2402, 2472, 40, 0, 20, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_BY = {
    .alpha2 = "BY",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 23, 0),
        REG_RULE(5250, 5330, 40, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 23,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_BZ = {
    .alpha2 = "BZ",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 30, 0),
        REG_RULE(5170, 5250, 40, 0, 30, 0),
        REG_RULE(5250, 5330, 40, 0, 30,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 30,
            NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 40, 0, 30, 0),
    },
    .n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_CA = {
    .alpha2 = "CA",
    .reg_rules = {
        REG_RULE(2402, 2472, 40, 3, 30, 0),
        REG_RULE(5170, 5250, 40, 3, 17, 0),
        REG_RULE(5250, 5330, 40, 3, 24,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 3, 24,
            NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 40, 3, 30, 0),
    },
    .n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_CH = {
    .alpha2 = "CH",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 23, 0),
        REG_RULE(5250, 5330, 40, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 23,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_CL = {
    .alpha2 = "CL",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 23, 0),
        REG_RULE(5250, 5330, 40, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 40, 0, 20, 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_CN = {
    .alpha2 = "CN",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 27, 0),
        REG_RULE(5170, 5250, 40, 0, 23, 0),
        REG_RULE(5250, 5330, 40, 0, 23,
        	NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 40, 0, 27, 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_CO = {
    .alpha2 = "CO",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 3, 30, 0),
        REG_RULE(5170, 5250, 40, 3, 17, 0),
    },
    .n_reg_rules = 2
};

static const struct ieee80211_regdomain regdom_CR = {
    .alpha2 = "CR",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 20, 0),
        REG_RULE(5250, 5330, 40, 0, 20,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 20,
            NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 40, 0, 20, 0),
    },
    .n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_CS = {
    .alpha2 = "CS",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 20, 0),
        REG_RULE(5250, 5330, 40, 0, 20,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 27,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_CU = {
    .alpha2 = "CU",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_CY = {
    .alpha2 = "CY",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 23, 0),
        REG_RULE(5250, 5330, 40, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 23,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_CZ = {
    .alpha2 = "CZ",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 23,
            NL80211_RRF_NO_OUTDOOR | 0),
        REG_RULE(5250, 5330, 40, 0, 23,
            NL80211_RRF_NO_OUTDOOR |
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 23,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_DE = {
    .alpha2 = "DE",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 23,
            NL80211_RRF_NO_OUTDOOR | 0),
        REG_RULE(5250, 5330, 40, 0, 23,
            NL80211_RRF_NO_OUTDOOR |
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 23,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_DK = {
    .alpha2 = "DK",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 23, 0),
        REG_RULE(5250, 5330, 40, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 23,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_DO = {
    .alpha2 = "DO",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 3, 30, 0),
        REG_RULE(5170, 5250, 40, 3, 17, 0),
        REG_RULE(5250, 5330, 40, 3, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 3, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 40, 3, 30, 0),
    },
    .n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_DZ = {
    .alpha2 = "DZ",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_EC = {
    .alpha2 = "EC",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 20, 3, 17, 0),
        REG_RULE(5250, 5330, 20, 3, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 20, 3, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 20, 3, 30, 0),
    },
    .n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_EE = {
    .alpha2 = "EE",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 23, 0),
        REG_RULE(5250, 5330, 40, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 23,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_EG = {
    .alpha2 = "EG",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 20, 0, 23, 0),
        REG_RULE(5250, 5330, 20, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 20, 0, 23, 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_ES = {
    .alpha2 = "ES",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 23,
            NL80211_RRF_NO_OUTDOOR | 0),
        REG_RULE(5250, 5330, 40, 0, 23,
            NL80211_RRF_NO_OUTDOOR |
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 23,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_ET = {
    .alpha2 = "ET",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_FI = {
    .alpha2 = "FI",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 23, 0),
        REG_RULE(5250, 5330, 40, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 23,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_FR = {
    .alpha2 = "FR",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 23, 0),
        REG_RULE(5250, 5330, 40, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 23,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_GB = {
    .alpha2 = "GB",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 23, 0),
        REG_RULE(5250, 5330, 40, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 23,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_GD = {
    .alpha2 = "GD",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 30, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_GE = {
    .alpha2 = "GE",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 18, 0),
        REG_RULE(5250, 5330, 40, 0, 18,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 18,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_GF = {
    .alpha2 = "GF",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_GL = {
    .alpha2 = "GL",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_GR = {
    .alpha2 = "GR",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 23, 0),
        REG_RULE(5250, 5330, 40, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 23,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_GT = {
    .alpha2 = "GT",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 3, 30, 0),
        REG_RULE(5170, 5250, 40, 3, 17, 0),
        REG_RULE(5250, 5330, 40, 3, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 3, 30,
            NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 40, 3, 30, 0),
    },
    .n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_GU = {
    .alpha2 = "GU",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 30, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_HK = {
    .alpha2 = "HK",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 3, 17, 0),
        REG_RULE(5250, 5330, 40, 3, 24,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 3, 24,
            NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 40, 3, 30, 0),
    },
    .n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_HN = {
    .alpha2 = "HN",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5735, 5835, 40, 3, 30, 0),
    },
    .n_reg_rules = 2
};

static const struct ieee80211_regdomain regdom_HR = {
    .alpha2 = "HR",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 20, 0, 23, 0),
        REG_RULE(5250, 5330, 20, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 20, 0, 23,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_HU = {
    .alpha2 = "HU",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 23, 0),
        REG_RULE(5250, 5330, 40, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 23,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_ID = {
    .alpha2 = "ID",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5735, 5815, 40, 0, 20, 0),
    },
    .n_reg_rules = 2
};

static const struct ieee80211_regdomain regdom_IE = {
    .alpha2 = "IE",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 23, 0),
        REG_RULE(5250, 5330, 40, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 23,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_IL = {
    .alpha2 = "IL",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 23,
            NL80211_RRF_NO_OUTDOOR | 0),
        REG_RULE(5250, 5330, 40, 0, 23,
            NL80211_RRF_NO_OUTDOOR |
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 3
};

static const struct ieee80211_regdomain regdom_IN = {
    .alpha2 = "IN",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 23, 0),
        REG_RULE(5250, 5330, 40, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 40, 0, 20, 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_IQ = {
    .alpha2 = "IQ",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 23, 0),
        REG_RULE(5250, 5330, 40, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 30,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_IR = {
    .alpha2 = "IR",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 30, 0),
        REG_RULE(5250, 5330, 40, 0, 30,
        	NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 40, 0, 30, 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_IS = {
    .alpha2 = "IS",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 23, 0),
        REG_RULE(5250, 5330, 40, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 23,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_IT = {
    .alpha2 = "IT",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 23, 0),
        REG_RULE(5250, 5330, 40, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 23,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_JM = {
    .alpha2 = "JM",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 3, 17, 0),
        REG_RULE(5250, 5330, 40, 3, 20,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 3, 20,
            NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 40, 3, 30, 0),
    },
    .n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_JO = {
    .alpha2 = "JO",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 18, 0),
        REG_RULE(5735, 5835, 40, 0, 18, 0),
    },
    .n_reg_rules = 3
};

static const struct ieee80211_regdomain regdom_JP = {
    .alpha2 = "JP",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 23, 0),
        REG_RULE(5250, 5330, 40, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 23,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_KE = {
    .alpha2 = "KE",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_KH = {
    .alpha2 = "KH",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_KP = {
    .alpha2 = "KP",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 3, 30, 0),
        REG_RULE(5250, 5330, 40, 3, 30,
        	NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 40, 3, 30, 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_KR = {
    .alpha2 = "KR",
    .reg_rules = {
        REG_RULE(2402, 2482, 20, 0, 20, 0),
        REG_RULE(5170, 5250, 20, 3, 30, 0),
        REG_RULE(5250, 5330, 20, 3, 30,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5630, 20, 3, 30,
            NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5815, 20, 3, 30, 0),
    },
    .n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_KW = {
    .alpha2 = "KW",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 20, 0),
        REG_RULE(5250, 5330, 40, 0, 20,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 3
};

static const struct ieee80211_regdomain regdom_KY = {
    .alpha2 = "KY",
    .reg_rules = {
        REG_RULE(2402, 2472, 40, 0, 20, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_KZ = {
    .alpha2 = "KZ",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 20, 0),
        REG_RULE(5250, 5330, 40, 0, 20,
            NL80211_RRF_DFS | 0),
        REG_RULE(5650, 5710, 40, 0, 20, 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_LA = {
    .alpha2 = "LA",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_LB = {
    .alpha2 = "LB",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5735, 5835, 20, 0, 30, 0),
    },
    .n_reg_rules = 2
};

static const struct ieee80211_regdomain regdom_LI = {
    .alpha2 = "LI",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 23, 0),
        REG_RULE(5250, 5330, 40, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 23,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_LK = {
    .alpha2 = "LK",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 20, 3, 17, 0),
        REG_RULE(5250, 5330, 20, 3, 24,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 20, 3, 24,
            NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 20, 3, 30, 0),
    },
    .n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_LS = {
    .alpha2 = "LS",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_LT = {
    .alpha2 = "LT",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 23, 0),
        REG_RULE(5250, 5330, 40, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 23,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_LU = {
    .alpha2 = "LU",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 23, 0),
        REG_RULE(5250, 5330, 40, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 23,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_LV = {
    .alpha2 = "LV",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 23, 0),
        REG_RULE(5250, 5330, 40, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 23,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_MA = {
    .alpha2 = "MA",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 20, 0),
        REG_RULE(5250, 5330, 40, 0, 20,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 3
};

static const struct ieee80211_regdomain regdom_MC = {
    .alpha2 = "MC",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 18, 0),
        REG_RULE(5250, 5330, 40, 0, 18,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 18, 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_MD = {
    .alpha2 = "MD",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_ME = {
    .alpha2 = "ME",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_MH = {
    .alpha2 = "MH",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 30, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_MK = {
    .alpha2 = "MK",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 20, 0, 23, 0),
        REG_RULE(5250, 5330, 20, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 20, 0, 23,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_MN = {
    .alpha2 = "MN",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_MO = {
    .alpha2 = "MO",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5735, 5835, 40, 3, 30, 0),
    },
    .n_reg_rules = 2
};

static const struct ieee80211_regdomain regdom_MR = {
    .alpha2 = "MR",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_MT = {
    .alpha2 = "MT",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 23, 0),
        REG_RULE(5250, 5330, 40, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 23,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_MU = {
    .alpha2 = "MU",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_MV = {
    .alpha2 = "MV",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_MW = {
    .alpha2 = "MW",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
    },
    .n_reg_rules = 1
};


static const struct ieee80211_regdomain regdom_MX = {
    .alpha2 = "MX",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 3, 30, 0),
        REG_RULE(5170, 5250, 40, 3, 17, 0),
        REG_RULE(5250, 5330, 40, 3, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5590, 40, 3, 30,
            NL80211_RRF_DFS | 0),
        REG_RULE(5650, 5710, 40, 3, 30,
            NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 40, 3, 30, 0),
    },
    .n_reg_rules = 6
};


static const struct ieee80211_regdomain regdom_MY = {
    .alpha2 = "MY",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 3, 23, 0),
        REG_RULE(5250, 5330, 40, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 40, 0, 30, 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_NI = {
    .alpha2 = "NI",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 30, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_NG = {
    .alpha2 = "NG",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5250, 5330, 40, 0, 20,
            NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 40, 0, 20, 0),
    },
    .n_reg_rules = 3
};

static const struct ieee80211_regdomain regdom_NL = {
    .alpha2 = "NL",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 23,
            NL80211_RRF_NO_OUTDOOR | 0),
        REG_RULE(5250, 5330, 40, 0, 23,
            NL80211_RRF_NO_OUTDOOR |
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 23,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_NO = {
    .alpha2 = "NO",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 23, 0),
        REG_RULE(5250, 5330, 40, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 23,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_NP = {
    .alpha2 = "NP",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5735, 5835, 40, 0, 30, 0),
    },
    .n_reg_rules = 2
};

static const struct ieee80211_regdomain regdom_NZ = {
    .alpha2 = "NZ",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 30, 0),
        REG_RULE(5170, 5250, 20, 3, 17, 0),
        REG_RULE(5250, 5330, 20, 3, 24,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 20, 3, 30,
            NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 20, 3, 30, 0),
    },
    .n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_OM = {
    .alpha2 = "OM",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 20, 3, 17, 0),
        REG_RULE(5250, 5330, 20, 3, 24,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 20, 3, 30,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_PA = {
    .alpha2 = "PA",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 3, 30, 0),
        REG_RULE(5170, 5250, 40, 3, 17, 0),
        REG_RULE(5250, 5330, 40, 3, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 40, 3, 30, 0),
    },
    .n_reg_rules = 4
};


static const struct ieee80211_regdomain regdom_PE = {
    .alpha2 = "PE",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 20, 0, 23, 0),
        REG_RULE(5250, 5330, 20, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 20, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 20, 0, 30, 0),
    },
    .n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_PG = {
    .alpha2 = "PG",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 3, 17, 0),
        REG_RULE(5250, 5330, 40, 3, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 40, 3, 30, 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_PH = {
    .alpha2 = "PH",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 17, 0),
        REG_RULE(5250, 5330, 40, 0, 24,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 24,
            NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 40, 0, 30, 0),
    },
    .n_reg_rules = 5
};


static const struct ieee80211_regdomain regdom_PK = {
    .alpha2 = "PK",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 30, 0),
        REG_RULE(5250, 5330, 40, 0, 30,
        	NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 40, 0, 30, 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_PL = {
    .alpha2 = "PL",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 23, 0),
        REG_RULE(5250, 5330, 40, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 23,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};


static const struct ieee80211_regdomain regdom_PR = {
    .alpha2 = "PR",
    .reg_rules = {
        REG_RULE(2402, 2472, 40, 3, 30, 0),
        REG_RULE(5170, 5250, 40, 3, 17, 0),
        REG_RULE(5250, 5330, 40, 3, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 3, 30,
            NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 40, 3, 30, 0),
    },
    .n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_PT = {
    .alpha2 = "PT",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 23, 0),
        REG_RULE(5250, 5330, 40, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 23,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_PY = {
    .alpha2 = "PY",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_QA = {
    .alpha2 = "QA",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5735, 5835, 40, 0, 20, 0),
    },
    .n_reg_rules = 2
};

static const struct ieee80211_regdomain regdom_RE = {
    .alpha2 = "RE",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_RO = {
    .alpha2 = "RO",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 20, 0, 23, 0),
        REG_RULE(5250, 5330, 20, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 20, 0, 23,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_RS = {
    .alpha2 = "RS",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_RU = {
    .alpha2 = "RU",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 20, 0, 23, 0),
        REG_RULE(5250, 5330, 20, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5650, 5710, 20, 0, 20,
            NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 20, 0, 20, 0),
    },
    .n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_SA = {
    .alpha2 = "SA",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 20, 3, 23, 0),
        REG_RULE(5250, 5330, 20, 3, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 20, 3, 20,
            NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5815, 20, 3, 20, 0),
    },
    .n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_SD = {
    .alpha2 = "SD",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_SE = {
    .alpha2 = "SE",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 23, 0),
        REG_RULE(5250, 5330, 40, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 23,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_SG = {
    .alpha2 = "SG",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 23, 0),
        REG_RULE(5250, 5330, 40, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5730, 40, 0, 23, 0),
        REG_RULE(5735, 5835, 40, 0, 23, 0),
    },
    .n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_SI = {
    .alpha2 = "SI",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 23, 0),
        REG_RULE(5250, 5330, 40, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 23,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_SK = {
    .alpha2 = "SK",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 23, 0),
        REG_RULE(5250, 5330, 40, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 23,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_SN = {
    .alpha2 = "SN",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_SV = {
    .alpha2 = "SV",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 20, 0),
        REG_RULE(5250, 5330, 40, 0, 20,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 20,
            NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 40, 0, 20, 0),
    },
    .n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_SY = {
    .alpha2 = "SY",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5330, 40, 0, 20, 0),
        REG_RULE(5490, 5835, 40, 0, 20, 0),
    },
    .n_reg_rules = 3
};

static const struct ieee80211_regdomain regdom_TH = {
    .alpha2 = "TH",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 3, 17, 0),
        REG_RULE(5250, 5330, 40, 3, 24,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 3, 24,
            NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 40, 3, 30, 0),
    },
    .n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_TN = {
    .alpha2 = "TN",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 20, 0, 23, 0),
        REG_RULE(5250, 5330, 20, 0, 23,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 3
};

static const struct ieee80211_regdomain regdom_TR = {
    .alpha2 = "TR",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 20, 0, 23, 0),
        REG_RULE(5250, 5330, 20, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 20, 0, 23,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_TT = {
    .alpha2 = "TT",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 3, 17, 0),
        REG_RULE(5250, 5330, 40, 3, 24,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 3, 24,
            NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 40, 3, 30, 0),
    },
    .n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_TW = {
    .alpha2 = "TW",
    .reg_rules = {
        REG_RULE(2402, 2472, 40, 3, 30, 0),
        REG_RULE(5270, 5330, 40, 3, 17,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 3, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 40, 3, 30, 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_UA = {
    .alpha2 = "UA",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20,
            NL80211_RRF_NO_OUTDOOR | 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_UG = {
    .alpha2 = "UG",
    .reg_rules = {
        REG_RULE(2402, 2472, 40, 0, 20, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_US = {
    .alpha2 = "US",
    .reg_rules = {
        REG_RULE(2402, 2472, 40, 3, 30, 0),
        REG_RULE(5170, 5250, 40, 3, 17, 0),
        REG_RULE(5250, 5330, 40, 3, 24,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5590, 40, 3, 24,
            NL80211_RRF_DFS | 0),
        REG_RULE(5650, 5710, 40, 3, 30,
            NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 40, 3, 30, 0),
    },
    .n_reg_rules = 6
};

static const struct ieee80211_regdomain regdom_UY = {
    .alpha2 = "UY",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 3, 17, 0),
        REG_RULE(5250, 5330, 40, 3, 24,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 3, 24, 0),
        REG_RULE(5735, 5835, 40, 3, 30, 0),
    },
    .n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_UZ = {
    .alpha2 = "UZ",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 3, 30, 0),
        REG_RULE(5170, 5250, 40, 3, 17, 0),
        REG_RULE(5250, 5330, 40, 3, 24,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 3
};

static const struct ieee80211_regdomain regdom_VA = {
    .alpha2 = "VA",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_VE = {
    .alpha2 = "VE",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 30, 0),
        REG_RULE(5250, 5330, 40, 0, 30,
        	NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 40, 0, 30, 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_VI = {
    .alpha2 = "VI",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 30, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_VN = {
    .alpha2 = "VN",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 20, 0, 23, 0),
        REG_RULE(5250, 5330, 20, 0, 23,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 3
};

static const struct ieee80211_regdomain regdom_YE = {
    .alpha2 = "YE",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 20, 0),
        REG_RULE(5250, 5330, 40, 0, 20,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 20,
            NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 40, 0, 20, 0),
    },
    .n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_YT = {
    .alpha2 = "YT",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_ZA = {
    .alpha2 = "ZA",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 3, 17, 0),
        REG_RULE(5250, 5330, 40, 3, 24,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 3, 24,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_ZM = {
    .alpha2 = "ZM",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
    },
    .n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_ZW = {
    .alpha2 = "ZW",
    .reg_rules = {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 20, 0),
        REG_RULE(5250, 5330, 40, 0, 20,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5590, 40, 0, 20,
            NL80211_RRF_DFS | 0),
        REG_RULE(5590, 5650, 40, 0, 20, 0),
        REG_RULE(5650, 5710, 40, 0, 20,
            NL80211_RRF_DFS | 0),
    },
    .n_reg_rules = 6
};

/* country alpha2 code can search from http://en.wikipedia.org/wiki/ISO_3166-1_alpha-2 */
const struct ieee80211_regdomain *reg_regdb[] = {
    &regdom_AE,
    &regdom_AF,
    &regdom_AG,
    &regdom_AI,
    &regdom_AL,
    &regdom_AM,
    &regdom_AN,
    &regdom_AO,
    &regdom_AR,
    &regdom_AS,
    &regdom_AT,
    &regdom_AU,
    &regdom_AW,
    &regdom_AZ,
    &regdom_BA,
    &regdom_BD,
    &regdom_BE,
    &regdom_BG,
    &regdom_BH,
    &regdom_BL,
    &regdom_BM,
    &regdom_BN,
    &regdom_BO,
    &regdom_BR,
    &regdom_BS,
    &regdom_BY,
    &regdom_BZ,
    &regdom_CA,
    &regdom_CH,
    &regdom_CL,
    &regdom_CN,
    &regdom_CO,
    &regdom_CR,
    &regdom_CS,
    &regdom_CU,
    &regdom_CY,
    &regdom_CZ,
    &regdom_DE,
    &regdom_DK,
    &regdom_DO,
    &regdom_DZ,
    &regdom_EC,
    &regdom_EE,
    &regdom_EG,
    &regdom_ES,
    &regdom_ET,
    &regdom_FI,
    &regdom_FR,
    &regdom_GB,
    &regdom_GD,
    &regdom_GE,
    &regdom_GF,
    &regdom_GL,
    &regdom_GR,
    &regdom_GT,
    &regdom_GU,
    &regdom_HK,
    &regdom_HN,
    &regdom_HR,
    &regdom_HU,
    &regdom_ID,
    &regdom_IE,
    &regdom_IL,
    &regdom_IN,
    &regdom_IQ,
    &regdom_IR,
    &regdom_IS,
    &regdom_IT,
    &regdom_JM,
    &regdom_JO,
    &regdom_JP,
    &regdom_KE,
    &regdom_KH,
    &regdom_KP,
    &regdom_KR,
    &regdom_KW,
    &regdom_KY,
    &regdom_KZ,
    &regdom_LA,
    &regdom_LB,
    &regdom_LI,
    &regdom_LK,
    &regdom_LS,
    &regdom_LT,
    &regdom_LU,
    &regdom_LV,
    &regdom_MA,
    &regdom_MC,
    &regdom_MD,
    &regdom_ME,
    &regdom_MH,
    &regdom_MK,
    &regdom_MN,
    &regdom_MO,
    &regdom_MR,
    &regdom_MT,
    &regdom_MU,
    &regdom_MV,
    &regdom_MW,
    &regdom_MX,
    &regdom_MY,
    &regdom_NG,
    &regdom_NI,
    &regdom_NL,
    &regdom_NO,
    &regdom_NP,
    &regdom_NZ,
    &regdom_OM,
    &regdom_PA,
    &regdom_PE,
    &regdom_PG,
    &regdom_PH,
    &regdom_PK,
    &regdom_PL,
    &regdom_PR,
    &regdom_PT,
    &regdom_PY,
    &regdom_QA,
    &regdom_RE,
    &regdom_RO,
    &regdom_RS,
    &regdom_RU,
    &regdom_SA,
    &regdom_SD,
    &regdom_SE,
    &regdom_SG,
    &regdom_SI,
    &regdom_SK,
    &regdom_SN,
    &regdom_SV,
    &regdom_SY,
    &regdom_TH,
    &regdom_TN,
    &regdom_TR,
    &regdom_TT,
    &regdom_TW,
    &regdom_UA,
    &regdom_UG,
    &regdom_US,
    &regdom_UY,
    &regdom_UZ,
    &regdom_VA,
    &regdom_VE,
    &regdom_VI,
    &regdom_VN,
    &regdom_YE,
    &regdom_YT,
    &regdom_ZA,
    &regdom_ZM,
    &regdom_ZW,
};

int reg_regdb_size = ARRAY_SIZE(reg_regdb);
#endif


/* 默认管制域信息 */
OAL_CONST oal_ieee80211_regdomain_stru g_st_default_regdom = {
    .n_reg_rules = 4,
    .alpha2 =  "99",
    .reg_rules = {
        /* IEEE 802.11b/g, 信道 1..13 */
        REG_RULE(2412-10, 2472+10, 40, 6, 20, 0),

        /* 信道 36 - 64 */
        REG_RULE(5150-10, 5350+10, 80, 6, 20, 0),

        /* 信道 100 - 165 */
        REG_RULE(5470-10, 5850+10, 80, 6, 20, 0),

        /* IEEE 802.11 信道 184,188,192,196 ，对于日本4.9G */
        REG_RULE(4920-10, 4980+10, 80, 6, 23, 0),
    }
};


#elif (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)
/* Win32下代码只封装几个国家的管制域信息， 为了UT， */
OAL_STATIC OAL_CONST oal_ieee80211_regdomain_stru regdom_AU = {
    5,
    {'A', 'U'},
    {0, 0},
    {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 3, 17, 0),
        REG_RULE(5250, 5330, 40, 3, 24,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 3, 24, 0),
        REG_RULE(5735, 5835, 40, 3, 30, 0),
    }
};

OAL_STATIC OAL_CONST oal_ieee80211_regdomain_stru regdom_AT= {
    4,
    {'A', 'T'},
    {0, 0},
    {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 23, 0),
        REG_RULE(5250, 5330, 40, 0, 23,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 23,
            NL80211_RRF_DFS | 0),
    }
};

OAL_STATIC OAL_CONST oal_ieee80211_regdomain_stru regdom_CN = {
    2,
    {'C', 'N'},
    {0, 0},
    {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5735, 5835, 40, 0, 30, 0),
    }
};

OAL_STATIC OAL_CONST oal_ieee80211_regdomain_stru regdom_JP = {
    7,
    {'J', 'P'},
    {0, 0},
    {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(2474, 2494, 20, 0, 20,
            NL80211_RRF_NO_OFDM | 0),
        REG_RULE(4910, 4990, 40, 0, 23, 0),
        REG_RULE(5030, 5090, 40, 0, 23, 0),
        REG_RULE(5170, 5250, 40, 0, 20, 0),
        REG_RULE(5250, 5330, 40, 0, 20,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 23,
            NL80211_RRF_DFS | 0),
    }
};

OAL_STATIC OAL_CONST oal_ieee80211_regdomain_stru regdom_GB = {
    4,
    {'G', 'B'},
    {0, 0},
    {
        REG_RULE(2402, 2482, 40, 0, 20, 0),
        REG_RULE(5170, 5250, 40, 0, 20, 0),
        REG_RULE(5250, 5330, 40, 0, 20,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5710, 40, 0, 27,
            NL80211_RRF_DFS | 0),
    }
};

OAL_STATIC OAL_CONST oal_ieee80211_regdomain_stru regdom_US = {
    6,
    {'U', 'S'},
    {0, 0},
    {
        REG_RULE(2402, 2472, 40, 3, 27, 0),
        REG_RULE(5170, 5250, 40, 3, 17, 0),
        REG_RULE(5250, 5330, 40, 3, 20,
            NL80211_RRF_DFS | 0),
        REG_RULE(5490, 5600, 40, 3, 20,
            NL80211_RRF_DFS | 0),
        REG_RULE(5650, 5710, 40, 3, 20,
            NL80211_RRF_DFS | 0),
        REG_RULE(5735, 5835, 40, 3, 30, 0),
    },
};

OAL_CONST oal_ieee80211_regdomain_stru *reg_regdb[] = {
    &regdom_AU,
    &regdom_AT,
    &regdom_CN,
    &regdom_JP,
    &regdom_GB,
    &regdom_US,
};

int reg_regdb_size = OAL_ARRAY_SIZE(reg_regdb);

/* 默认管制域信息 */
OAL_CONST oal_ieee80211_regdomain_stru g_st_default_regdom = {
    4,              /* n_reg_rules */
    {'9', '9'},     /* alpha2 */
    {0, 0},
    {   /* reg_rules */
        /* IEEE 802.11b/g, 信道 1..13 */
        REG_RULE(2402, 2482, 40, 6, 20, 0),

        /* 信道 36 - 64 */
        REG_RULE(5150-10, 5350+10, 40, 6, 20, (0)),

        /* 信道 100 - 165 */
        REG_RULE(5470-10, 5850+10, 40, 6, 20, (0)),

        /* IEEE 802.11 信道 184,188,192,196 在日本使用 4.9G */
        REG_RULE(4920-10, 4980+10, 40, 6, 23, (0)),
    },
};

#endif



/*****************************************************************************
  3 函数实现
*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_11D
/*****************************************************************************
 函 数 名  : wal_regdb_find_db
 功能描述  : 根据国家字符串查找管制域数据库
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_CONST oal_ieee80211_regdomain_stru* wal_regdb_find_db(oal_int8 *pc_str)
{
    oal_int32 l_db_idx;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pc_str))
    {
        return OAL_PTR_NULL;
    }

    /* 默认管制域 */
    if (('9' == pc_str[0]) && ('9' == pc_str[1]))
    {
        return &g_st_default_regdom;
    }

    for (l_db_idx = 0; l_db_idx < reg_regdb_size; l_db_idx++)
    {
        if ((pc_str[0] == reg_regdb[l_db_idx]->alpha2[0]) &&
            (pc_str[1] == reg_regdb[l_db_idx]->alpha2[1]))
        {
            return reg_regdb[l_db_idx];
        }

    }

    return OAL_PTR_NULL;
}
#endif






#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif






