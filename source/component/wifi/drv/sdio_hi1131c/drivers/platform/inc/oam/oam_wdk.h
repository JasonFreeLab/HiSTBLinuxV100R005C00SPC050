/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : oam_wdk.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2014年5月26日,星期一
  最近修改   :
  功能描述   : 打点工具头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年5月26日,星期一
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/
#ifndef __OAM_WDK_H__
#define __OAM_WDK_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if ((_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION) || (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION))
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define OAM_SOFTWARE_VERSION            "Hi1151 V100R001C01B200_0515"

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
typedef enum
{
    /* ALG */
    OAM_FILE_ID_ALG_EXT_IF_H            = 1100,
    OAM_FILE_ID_ALG_TRANSPLANT_H        = 1101,
    OAM_FILE_ID_ALG_MAIN_C              = 1102,
    OAM_FILE_ID_ALG_MAIN_H              = 1103,
    OAM_FILE_ID_ALG_SCHEDULE_C          = 1104,
    OAM_FILE_ID_ALG_SCHEDULE_H          = 1105,
    OAM_FILE_ID_ALG_SCHEDULE_LOG_C      = 1106,
    OAM_FILE_ID_ALG_AUTORATE_C          = 1107,
    OAM_FILE_ID_ALG_AUTORATE_H          = 1108,
    OAM_FILE_ID_ALG_AUTORATE_LOG_C      = 1109,
    OAM_FILE_ID_ALG_AUTORATE_LOG_H      = 1110,
    OAM_FILE_ID_ALG_SMARTANT_C          = 1111,
    OAM_FILE_ID_ALG_SMARTANT_H          = 1112,
    OAM_FILE_ID_ALG_DBAC_C              = 1113,
    OAM_FILE_ID_ALG_DBAC_H              = 1114,
    OAM_FILE_ID_ALG_TXBF_H              = 1115,
    OAM_FILE_ID_ALG_TXBF_C              = 1116,
    OAM_FILE_ID_ALG_SIMPLE_SCHEDULE_C   = 1117,
    OAM_FILE_ID_ALG_SIMPLE_SCHEDULE_H   = 1118,
    OAM_FILE_ID_ALG_SCHEDULE_TRAFFIC_CTL_C  = 1119,
    OAM_FILE_ID_ALG_SCHEDULE_TRAFFIC_CTL_H  = 1120,
    OAM_FILE_ID_ALG_SCHEDULE_LOG_H          = 1121,
    OAM_FILE_ID_ALG_ANTI_INTERFERENCE_C     = 1122,
    OAM_FILE_ID_ALG_ANTI_INTERFERENCE_H     = 1123,
    OAM_FILE_ID_ALG_TPC_C                   = 1124,
    OAM_FILE_ID_ALG_TPC_H                   = 1125,
	OAM_FILE_ID_ALG_TPC_LOG_C               = 1126,
    OAM_FILE_ID_ALG_TPC_LOG_H               = 1127,
    OAM_FILE_ID_ALG_TXBF_TEST_C             = 1128,
    OAM_FILE_ID_ALG_EDCA_OPT_C              = 1129,
    OAM_FILE_ID_ALG_EDCA_OPT_H              = 1130,
    OAM_FILE_ID_ALG_MWO_DETECTION_C         = 1131,
    OAM_FILE_ID_ALG_MWO_DETECTION_H         = 1132,
    OAM_FILE_ID_ALG_CCA_OPTIMIZE_C          = 1133,
    OAM_FILE_ID_ALG_CCA_OPTIMIZE_H          = 1134,
    OAM_FILE_ID_ALG_CCA_OPTIMIZE_LOG_C      = 1135,
    OAM_FILE_ID_ALG_CCA_OPTIMIZE_LOG_H      = 1136,

    /* WAL */
    OAM_FILE_ID_WAL_EXT_IF_H            = 1200,
    OAM_FILE_ID_WAL_MAIN_C              = 1201,
    OAM_FILE_ID_WAL_MAIN_H              = 1202,
    OAM_FILE_ID_WAL_LINUX_BRIDGE_C      = 1203,
    OAM_FILE_ID_WAL_LINUX_BRIDGE_H      = 1204,
    OAM_FILE_ID_WAL_LINUX_CFG80211_C    = 1205,
    OAM_FILE_ID_WAL_LINUX_CFG80211_H    = 1206,
    OAM_FILE_ID_WAL_LINUX_IOCTL_C       = 1207,
    OAM_FILE_ID_WAL_LINUX_IOCTL_H       = 1208,
    OAM_FILE_ID_WAL_DATA_C              = 1209,
    OAM_FILE_ID_WAL_DATA_H              = 1210,
    OAM_FILE_ID_WAL_CONFIG_C            = 1211,
    OAM_FILE_ID_WAL_CONFIG_H            = 1212,
    OAM_FILE_ID_WAL_LINUX_SCAN_C        = 1213,
    OAM_FILE_ID_WAL_LINUX_SCAN_H        = 1214,
    OAM_FILE_ID_WAL_LINUX_EVENT_C       = 1215,
    OAM_FILE_ID_WAL_LINUX_EVENT_H       = 1216,
    OAM_FILE_ID_WAL_LINUX_RX_RSP_C      = 1217,
    OAM_FILE_ID_WAL_LINUX_RX_RSP_H      = 1218,
    OAM_FILE_ID_WAL_LINUX_NETLINK_C     = 1219,
    OAM_FILE_ID_WAL_LINUX_NETLINK_H     = 1220,
    OAM_FILE_ID_WAL_CONFIG_ACS_C        = 1221,
    OAM_FILE_ID_WAL_CONFIG_ACS_H        = 1222,
    OAM_FILE_ID_WAL_LINUX_FLOWCTL_C     = 1223,
    OAM_FILE_ID_WAL_LINUX_FLOWCTL_H     = 1224,
    OAM_FILE_ID_WAL_REGDB_H             = 1225,
    OAM_FILE_ID_WAL_PROXYSTA_C          = 1226,
    OAM_FILE_ID_WAL_PROXYSTA_H          = 1227,
    OAM_FILE_ID_WAL_REGDB_C             = 1228,
    OAM_FILE_ID_WAL_LINUX_ATCMDSRV_C    = 1229,
    OAM_FILE_ID_WAL_LINUX_ATCMDSRV_H    = 1230,
    OAM_FILE_ID_WAL_DFX_H               = 1231,
    OAM_FILE_ID_WAL_DFX_C               = 1232,
    
    /* HMAC */
    OAM_FILE_ID_HMAC_BACKUP_C           = 1288,
    OAM_FILE_ID_HMAC_BACKUP_H           = 1289,
/* #ifdef _PRE_WLAN_FEATURE_WOW */
    OAM_FILE_ID_HMAC_WOW_C              = 1290,
    OAM_FILE_ID_HMAC_WOW_H              = 1291,
/* #endif  //_PRE_WLAN_FEATURE_WOW */
    OAM_FILE_ID_HMAC_EXT_IF_H           = 1300,
    OAM_FILE_ID_HMAC_MAIN_C             = 1301,
    OAM_FILE_ID_HMAC_MAIN_H             = 1302,
    OAM_FILE_ID_HMAC_VAP_C              = 1303,
    OAM_FILE_ID_HMAC_VAP_H              = 1304,
    OAM_FILE_ID_HMAC_USER_C             = 1305,
    OAM_FILE_ID_HMAC_USER_H             = 1306,
    OAM_FILE_ID_HMAC_TX_DATA_C          = 1307,
    OAM_FILE_ID_HMAC_TX_DATA_H          = 1308,
    OAM_FILE_ID_HMAC_TX_BSS_COMMON_C    = 1309,
    OAM_FILE_ID_HMAC_TX_BSS_COMMON_H    = 1310,
    OAM_FILE_ID_HMAC_TX_AMSDU_C         = 1311,
    OAM_FILE_ID_HMAC_TX_AMSDU_H         = 1312,
    OAM_FILE_ID_HMAC_RX_DATA_C          = 1313,
    OAM_FILE_ID_HMAC_RX_DATA_H          = 1314,
    OAM_FILE_ID_HMAC_MGMT_CLASSIFIER_C  = 1315,
    OAM_FILE_ID_HMAC_MGMT_CLASSIFIER_H  = 1316,
    OAM_FILE_ID_HMAC_MGMT_BSS_COMM_C    = 1317,
    OAM_FILE_ID_HMAC_MGMT_BSS_COMM_H    = 1318,
    OAM_FILE_ID_HMAC_MGMT_STA_C         = 1319,
    OAM_FILE_ID_HMAC_MGMT_STA_H         = 1320,
    OAM_FILE_ID_HMAC_MGMT_AP_C          = 1321,
    OAM_FILE_ID_HMAC_MGMT_AP_H          = 1322,
    OAM_FILE_ID_HMAC_FSM_C              = 1323,
    OAM_FILE_ID_HMAC_FSM_H              = 1324,
    OAM_FILE_ID_HMAC_11i_C              = 1325,
    OAM_FILE_ID_HMAC_11i_H              = 1326,
    OAM_FILE_ID_HMAC_UAPSD_C            = 1327,
    OAM_FILE_ID_HMAC_UAPSD_H            = 1328,
    OAM_FILE_ID_HMAC_CONFIG_C           = 1329,
    OAM_FILE_ID_HMAC_CONFIG_H           = 1330,
    OAM_FILE_ID_HMAC_FRAG_C             = 1331,
    OAM_FILE_ID_HMAC_FRAG_H             = 1332,
    OAM_FILE_ID_HMAC_PROTECTION_C       = 1333,
    OAM_FILE_ID_HMAC_PROTECTION_H       = 1334,
    OAM_FILE_ID_HMAC_CHAN_MGMT_C        = 1335,
    OAM_FILE_ID_HMAC_CHAN_MGMT_H        = 1336,
    OAM_FILE_ID_HMAC_SMPS_H             = 1337,
    OAM_FILE_ID_HMAC_SMPS_C             = 1338,
    OAM_FILE_ID_HMAC_DATA_ACQ_H         = 1339,
    OAM_FILE_ID_HMAC_DATA_ACQ_C         = 1340,
    OAM_FILE_ID_HMAC_RX_FILTER_H        = 1341,
    OAM_FILE_ID_HMAC_RX_FILTER_C        = 1342,
    OAM_FILE_ID_HMAC_ENCAP_FRAME_STA_C  = 1343,
    OAM_FILE_ID_HMAC_ENCAP_FRAME_AP_C   = 1344,
    OAM_FILE_ID_HMAC_CUSTOM_SECURITY_C  = 1345,
	OAM_FILE_ID_HMAC_M2U_C              = 1346,
    OAM_FILE_ID_HMAC_M2U_H              = 1347,
    OAM_FILE_ID_HMAC_PROXYARP_C         = 1348,
    OAM_FILE_ID_HMAC_HCC_ADAPT_H        = 1349,
    OAM_FILE_ID_HMAC_HCC_ADAPT_C        = 1350,
    OAM_FILE_ID_HMAC_SME_STA_C          = 1351,
    OAM_FILE_ID_HMAC_SME_STA_H          = 1352,
    OAM_FILE_ID_HMAC_DFS_C              = 1353,
    OAM_FILE_ID_HMAC_DFS_H              = 1354,
    OAM_FILE_ID_HMAC_RESET_H            = 1355,
    OAM_FILE_ID_HMAC_RESET_C            = 1356,
    OAM_FILE_ID_HMAC_SCAN_H             = 1357,
    OAM_FILE_ID_HMAC_SCAN_C             = 1358,
    OAM_FILE_ID_HMAC_P2P_C              = 1359,
    OAM_FILE_ID_HMAC_P2P_H              = 1360,
    OAM_FILE_ID_HMAC_EDCA_OPT_H         = 1361,
    OAM_FILE_ID_HMAC_EDCA_OPT_C         = 1362,
    OAM_FILE_ID_HMAC_BLOCKACK_H         = 1363,
    OAM_FILE_ID_HMAC_BLOCKACK_C         = 1364,
    OAM_FILE_ID_HMAC_PSM_AP_H           = 1365,
    OAM_FILE_ID_HMAC_PSM_AP_C           = 1366,
	OAM_FILE_ID_HMAC_RESOURCE_C         = 1367,
    OAM_FILE_ID_HMAC_RESOURCE_H         = 1368,
    OAM_FILE_ID_HMAC_DEVICE_C           = 1369,
    OAM_FILE_ID_HMAC_DEVICE_H           = 1370,
    OAM_FILE_ID_HMAC_WAPI_SMS4_C        = 1371,
    OAM_FILE_ID_HMAC_WAPI_SMS4_H        = 1372,
    OAM_FILE_ID_HMAC_WAPI_WPI_C         = 1373,
    OAM_FILE_ID_HMAC_WAPI_WPI_H         = 1374,
    OAM_FILE_ID_HMAC_ARP_OFFLOAD_C      = 1375,
    OAM_FILE_ID_HMAC_ARP_OFFLOAD_H      = 1376,
    OAM_FILE_ID_HMAC_ACS_C              = 1377,
    OAM_FILE_ID_HMAC_ACS_H              = 1378,
    OAM_FILE_ID_HMAC_TCP_OPT_C          = 1379,
    OAM_FILE_ID_HMAC_TCP_OPT_H          = 1380,
    OAM_FILE_ID_HMAC_TCP_OPT_STRUC_H    = 1381,
/* #ifdef _PRE_WLAN_FEATURE_ROAM */
    OAM_FILE_ID_HMAC_ROAM_ALG_C         = 1382,
    OAM_FILE_ID_HMAC_ROAM_ALG_H         = 1383,
    OAM_FILE_ID_HMAC_ROAM_MAIN_C        = 1384,
    OAM_FILE_ID_HMAC_ROAM_MAIN_H        = 1385,
    OAM_FILE_ID_HMAC_ROAM_CONNECT_C     = 1386,
    OAM_FILE_ID_HMAC_ROAM_CONNECT_H     = 1387,
/* #endif  //_PRE_WLAN_FEATURE_ROAM */
    OAM_FILE_ID_HMAC_ENCAP_FRAME_C      = 1388,

    OAM_FILE_ID_HMAC_WAPI_C             = 1389,
    OAM_FILE_ID_HMAC_WAPI_H             = 1390,
    OAM_FILE_ID_HMAC_CALI_MGMT_C        = 1391,
    OAM_FILE_ID_HMAC_CALI_MGMT_H        = 1392,
    OAM_FILE_ID_HMAC_CUSTOMIZE          = 1393,

    OAM_FILE_ID_HMAC_DFX_C              = 1394,
    OAM_FILE_ID_HMAC_DFX_H              = 1395,

    OAM_FILE_ID_HMAC_TRAFFIC_CLASSIFY_C = 1396,
    OAM_FILE_ID_HMAC_TRAFFIC_CLASSIFY_H = 1397,
#ifdef _PRE_WLAN_FEATURE_TCP_UDP_KEEPALIVE     
    OAM_FILE_ID_HMAC_TCP_UDP_KEEPALIVE_C = 1398,
    OAM_FILE_ID_HMAC_TCP_UDP_KEEPALIVE_H = 1399,
#endif

    /* DMAC */
    OAM_FILE_ID_DMAC_EXT_IF_H           = 1400,
    OAM_FILE_ID_DMAC_ALG_IF_H           = 1401,
    OAM_FILE_ID_DMAC_MAIN_C             = 1402,
    OAM_FILE_ID_DMAC_MAIN_H             = 1403,
    OAM_FILE_ID_DMAC_VAP_C              = 1404,
    OAM_FILE_ID_DMAC_VAP_H              = 1405,
    OAM_FILE_ID_MAC_RESOURCE_C          = 1406,
    OAM_FILE_ID_MAC_RESOURCE_H          = 1407,
    OAM_FILE_ID_MAC_DEVICE_C            = 1408,
    OAM_FILE_ID_MAC_DEVICE_H            = 1409,
    OAM_FILE_ID_MAC_VAP_C               = 1410,
    OAM_FILE_ID_MAC_VAP_H               = 1411,
    OAM_FILE_ID_MAC_USER_C              = 1412,
    OAM_FILE_ID_MAC_USER_H              = 1413,
    OAM_FILE_ID_MAC_IE_C                = 1414,
    OAM_FILE_ID_MAC_IE_H                = 1415,
    OAM_FILE_ID_MAC_FRAME_C             = 1416,
    OAM_FILE_ID_MAC_REGDOMAIN_C         = 1417,
    OAM_FILE_ID_DMAC_USER_C             = 1418,
    OAM_FILE_ID_DMAC_USER_H             = 1419,
    OAM_FILE_ID_DMAC_RX_DATA_C          = 1420,
    OAM_FILE_ID_DMAC_RX_DATA_H          = 1421,
    OAM_FILE_ID_DMAC_TID_C              = 1422,
    OAM_FILE_ID_DMAC_TID_H              = 1423,
    OAM_FILE_ID_DMAC_TX_DSCR_QUEUE_C    = 1424,
    OAM_FILE_ID_DMAC_TX_DSCR_QUEUE_H    = 1425,
    OAM_FILE_ID_DMAC_TX_BSS_COMM_C      = 1426,
    OAM_FILE_ID_DMAC_TX_BSS_COMM_H      = 1427,
    OAM_FILE_ID_DMAC_PSM_AP_C           = 1428,
    OAM_FILE_ID_DMAC_PSM_AP_H           = 1429,
    OAM_FILE_ID_DMAC_TX_COMPLETE_H      = 1430,
    OAM_FILE_ID_DMAC_TX_COMPLETE_C      = 1431,
    OAM_FILE_ID_DMAC_MGMT_CLASSIFIER_C  = 1432,
    OAM_FILE_ID_DMAC_MGMT_CLASSIFIER_H  = 1433,
    OAM_FILE_ID_DMAC_MGMT_BSS_COMM_C    = 1434,
    OAM_FILE_ID_DMAC_MGMT_BSS_COMM_H    = 1435,
    OAM_FILE_ID_DMAC_MGMT_AP_C          = 1436,
    OAM_FILE_ID_DMAC_MGMT_AP_H          = 1437,
    OAM_FILE_ID_DMAC_MGMT_STA_C         = 1438,
    OAM_FILE_ID_DMAC_MGMT_STA_H         = 1439,
    OAM_FILE_ID_DMAC_UAPSD_C            = 1440,
    OAM_FILE_ID_DMAC_UAPSD_H            = 1441,
    OAM_FILE_ID_DMAC_ALG_C              = 1442,
    OAM_FILE_ID_DMAC_ALG_H              = 1443,
    OAM_FILE_ID_DMAC_BLOCKACK_C         = 1444,
    OAM_FILE_ID_DMAC_BLOCKACK_H         = 1445,
    OAM_FILE_ID_DMAC_BEACON_C           = 1446,
    OAM_FILE_ID_DMAC_BEACON_H           = 1447,
    OAM_FILE_ID_DMAC_WEP_C              = 1448,
    OAM_FILE_ID_DMAC_WEP_H              = 1449,
    OAM_FILE_ID_DMAC_11I_C              = 1450,
    OAM_FILE_ID_DMAC_11I_H              = 1451,
    OAM_FILE_ID_DMAC_SCAN_C             = 1452,
    OAM_FILE_ID_DMAC_SCAN_H             = 1453,
    OAM_FILE_ID_DMAC_ACS_C              = 1454,
    OAM_FILE_ID_DMAC_ACS_H              = 1455,
    OAM_FILE_ID_DMAC_DFS_C              = 1456,
    OAM_FILE_ID_DMAC_DFS_H              = 1457,
    OAM_FILE_ID_DMAC_RESET_C            = 1458,
    OAM_FILE_ID_DMAC_RESET_H            = 1459,
    OAM_FILE_ID_MAC_FCS_C               = 1460,
    OAM_FILE_ID_MAC_FCS_H               = 1461,
    OAM_FILE_ID_DMAC_CONFIG_C           = 1462,
    OAM_FILE_ID_DMAC_CONFIG_H           = 1463,
    OAM_FILE_ID_DMAC_STAT_C             = 1464,
    OAM_FILE_ID_DMAC_STAT_H             = 1465,
    OAM_FILE_ID_ALG_SCH_TEST_H          = 1466,
    OAM_FILE_ID_ALG_SCH_TEST_C          = 1467,
    OAM_FILE_ID_DMAC_CHAN_MGMT_C        = 1468,
    OAM_FILE_ID_DMAC_CHAN_MGMT_H        = 1469,
    OAM_FILE_ID_DMAC_DATA_ACQ_H         = 1470,
    OAM_FILE_ID_DMAC_DATA_ACQ_C         = 1471,
    OAM_FILE_ID_DMAC_USER_TRACK_H       = 1472,
    OAM_FILE_ID_DMAC_USER_TRACK_C       = 1473,
    OAM_FILE_ID_DMAC_RX_FILTER_H        = 1474,
    OAM_FILE_ID_DMAC_RX_FILTER_C        = 1475,
    OAM_FILE_ID_MAC_REGDOMAIN_H         = 1476,
    OAM_FILE_ID_MAC_FRAME_H             = 1477,
    OAM_FILE_ID_DMAC_11W_C              = 1478,
    OAM_FILE_ID_DMAC_TXOPPS_C           = 1479,
    OAM_FILE_ID_DMAC_TXOPPS_H           = 1480,
    OAM_FILE_ID_DMAC_DFT_H              = 1481,
    OAM_FILE_ID_DMAC_DFT_C              = 1482,
	OAM_FILE_ID_DMAC_AP_PM_C            = 1483,
    OAM_FILE_ID_DMAC_AP_PM_H            = 1484,
    OAM_FILE_ID_MAC_PM_C                = 1485,
    OAM_FILE_ID_MAC_PM_H                = 1486,
    OAM_FILE_ID_DMAC_SIMPLE_SCHEDULE_C  = 1487,
    OAM_FILE_ID_DMAC_SIMPLE_SCHEDULE_H  = 1488,
    OAM_FILE_ID_DMAC_HCC_ADAPT_C        = 1489,
    OAM_FILE_ID_DMAC_HCC_ADAPT_H        = 1490,
    OAM_FILE_ID_MAC_BOARD_C             = 1491,
    OAM_FILE_ID_MAC_BOARD_H             = 1492,
    OAM_FILE_ID_DMAC_P2P_C              = 1493,
    OAM_FILE_ID_DMAC_P2P_H              = 1494,
    OAM_FILE_ID_DMAC_BTCOEX_C           = 1495,
	OAM_FILE_ID_DMAC_BTCOEX_H           = 1496,


    OAM_FILE_ID_DMAC_STA_PM_C           = 1497,
    OAM_FILE_ID_DMAC_STA_PM_H           = 1498,
    OAM_FILE_ID_DMAC_UAPSD_STA_C        = 1499,
    OAM_FILE_ID_DMAC_UAPSD_STA_H        = 1500,
	OAM_FILE_ID_DMAC_PSM_STA_C          = 1501,
    OAM_FILE_ID_DMAC_PSM_STA_H          = 1502,
    OAM_FILE_ID_DMAC_PM_STA_C           = 1503,
    OAM_FILE_ID_DMAC_PM_STA_H           = 1504,

    OAM_FILE_ID_MAC_DATA_C              = 1505,
	OAM_FILE_ID_DMAC_LTECOEX_C          = 1506,
	OAM_FILE_ID_DMAC_LTECOEX_H          = 1507,

    OAM_FILE_ID_MAC_11I_C               = 1508,
    OAM_FILE_ID_MAC_11I_H               = 1509,
    OAM_FILE_ID_DMAC_PROFILING_H        = 1510,
    OAM_FILE_ID_DMAC_DFX_C              = 1511,
    OAM_FILE_ID_DMAC_DFX_H              = 1512,
    OAM_FILE_ID_DMAC_DEVICE_C           = 1513,
    OAM_FILE_ID_DMAC_DEVICE_H           = 1514,
    OAM_FILE_ID_DMAC_ARP_OFFLOAD_C      = 1515,
    OAM_FILE_ID_DMAC_ARP_OFFLOAD_H      = 1516,

    OAM_FILE_ID_DMAC_RESOURCE_C         = 1517,
    OAM_FILE_ID_DMAC_RESOURCE_H         = 1518,
    OAM_FILE_ID_DMAC_AUTO_ADJUST_FREQ_C = 1519,
    OAM_FILE_ID_DMAC_AUTO_ADJUST_FREQ_H = 1520,
#ifdef _PRE_WLAN_FEATURE_TCP_UDP_KEEPALIVE 
    OAM_FILE_ID_DMAC_TCP_UDP_KEEPALIVE_H = 1521,
    OAM_FILE_ID_DMAC_TCP_UDP_KEEPALIVE_C = 1522,
#endif

    /* HAL */
    OAM_FILE_ID_UT_HAL_TX_PROC_PROFILING_C  = 1600,
    OAM_FILE_ID_HAL_EXT_IF_H                = 1601,
    OAM_FILE_ID_HAL_PA_C                    = 1602,
    OAM_FILE_ID_HAL_PA_H                    = 1603,
    OAM_FILE_ID_HAL_BASE_C                  = 1604,
    OAM_FILE_ID_HAL_BASE_H                  = 1605,
    OAM_FILE_ID_HAL_MAIN_C                  = 1606,
    OAM_FILE_ID_HAL_MAIN_H                  = 1607,
    OAM_FILE_ID_HAL_IRQ_C                   = 1608,
    OAM_FILE_ID_HAL_IRQ_H                   = 1609,
    OAM_FILE_ID_HAL_TO_DMAC_IF_C            = 1610,
    OAM_FILE_ID_HAL_CHIP_C                  = 1611,
    OAM_FILE_ID_HAL_DEVICE_C                = 1612,
    OAM_FILE_ID_HAL_DEVICE_H                = 1613,
    OAM_FILE_ID_HAL_SIM_C                   = 1614,
    OAM_FILE_ID_HAL_WITP_MAC_C              = 1615,
    OAM_FILE_ID_HAL_WITP_RF_C               = 1616,
    OAM_FILE_ID_HAL_WITP_RF_H               = 1617,
    OAM_FILE_ID_HAL_WITP_CALI_C             = 1618,
    OAM_FILE_ID_HAL_WITP_CALI_H             = 1619,
    OAM_FILE_ID_HAL_WITP_MAC_H              = 1620,
    OAM_FILE_ID_HAL_RESET_C                 = 1621,
    OAM_FILE_ID_HAL_RESET_H                 = 1622,
    OAM_FILE_ID_HAL_WITP_PHY_REG_H          = 1623,
    OAM_FILE_ID_HAL_WITP_DMT_IF_C           = 1624,
    OAM_FILE_ID_HAL_WITP_DMT_IF_H           = 1625,
    OAM_FILE_ID_WITP_DEBUG_C                = 1626,
    OAM_FILE_ID_HAL_WITP_SOC_H              = 1627,
    OAM_FILE_ID_HAL_WITP_PHY_H              = 1628,
    OAM_FILE_ID_HAL_WITP_PHY_C              = 1629,
    OAM_FILE_ID_HAL_HW_MAC_H                = 1630,

    OAM_FILE_ID_HAL_HI1102_PHY_REG_H          = 1631,
    OAM_FILE_ID_HAL_HI1102_MAC_REG_H          = 1632,
    OAM_FILE_ID_HAL_HI1102_SOC_H              = 1633,
    OAM_FILE_ID_HAL_HI1102_PHY_H              = 1634,
    OAM_FILE_ID_HAL_HI1102_PHY_C              = 1635,
    OAM_FILE_ID_HAL_HI1102_MAC_H              = 1636,
    OAM_FILE_ID_HAL_HI1102_MAC_C              = 1637,
    OAM_FILE_ID_HAL_DBB_REG_RW_H              = 1638,
    OAM_FILE_ID_HAL_HI1102_DSCR_H             = 1639,
    OAM_FILE_ID_HAL_HI1102_DSCR_C             = 1640,
    OAM_FILE_ID_HAL_HI1102_RF_H               = 1641,
    OAM_FILE_ID_HAL_HI1102_RF_C               = 1642,
    OAM_FILE_ID_HAL_HI1102_RESET_H            = 1643,
    OAM_FILE_ID_HAL_HI1102_RESET_C            = 1644,
    OAM_FILE_ID_HAL_HI1102_IRQ_H              = 1645,
    OAM_FILE_ID_HAL_HI1102_IRQ_C              = 1646,
    OAM_FILE_ID_HAL_HI1102_SOC_REG_H          = 1647,
    OAM_FILE_ID_HAL_HI1102_COEX_REG_H         = 1648,
    OAM_FILE_ID_HAL_HI1102_COEX_REG_C         = 1649,
    OAM_FILE_ID_HI1102_RF_CORIDC_C            = 1650,
    OAM_FILE_ID_HI1102_RF_CORIDC_H            = 1651,
    OAM_FILE_ID_HAL_HI1102_PM_C               = 1652,
    OAM_FILE_ID_HAL_HI1102_PM_H               = 1653,
    OAM_FILE_ID_HAL_HI1102_CALI_DPD_C         = 1654,
    OAM_FILE_ID_HAL_HI1102_CALI_DPD_H         = 1655,
 #ifdef _PRE_WLAN_RF_110X_CALI_DPD
    OAM_FILE_ID_HMAC_CALI_DPD_C               = 1656,
    OAM_FILE_ID_HMAC_CALI_DPD_H               = 1657,
#endif
    OAM_FILE_ID_HAL_HI1102_RF_RAM_C           = 1658,
    OAM_FILE_ID_HAL_HI1102_CALI_DPD_RAM_C     = 1659,

    /* OAM */
    OAM_FILE_ID_OAM_LINUX_NETLINK_C         = 1700,
    OAM_FILE_ID_OAM_LINUX_NETLINK_H         = 1701,
    OAM_FILE_ID_OAM_LOG_C                   = 1702,
    OAM_FILE_ID_OAM_LOG_H                   = 1703,
    OAM_FILE_ID_OAM_TRACE_C                 = 1704,
    OAM_FILE_ID_OAM_TRACE_H                 = 1705,
    OAM_FILE_ID_OAM_STATISTICS_C            = 1706,
    OAM_FILE_ID_OAM_STATISTICS_H            = 1707,
    OAM_FILE_ID_OAM_EXT_IF_H                = 1708,
    OAM_FILE_ID_OAM_MAIN_C                  = 1709,
    OAM_FILE_ID_OAM_MAIN_H                  = 1710,
    OAM_FILE_ID_REGISTER_C                  = 1711,
    OAM_FILE_ID_REGISTER_H                  = 1712,
    OAM_FILE_ID_OAM_EVENT_C                 = 1713,
    OAM_FILE_ID_OAM_EVENT_H                 = 1714,

    /* OAL */
    OAM_FILE_ID_OAL_EXT_IF_H                = 1800,
    OAM_FILE_ID_OAL_MAIN_C                  = 1801,
    OAM_FILE_ID_OAL_MAIN_H                  = 1802,
    OAM_FILE_ID_OAL_TYPES_H                 = 1803,
    OAM_FILE_ID_OAL_MEM_C                   = 1804,
    OAM_FILE_ID_OAL_MEM_H                   = 1805,
    OAM_FILE_ID_OAL_QUEUE_H                 = 1806,
    OAM_FILE_ID_OAL_GPIO_H                  = 1807,
    OAM_FILE_ID_OAL_NET_C                   = 1808,
    OAM_FILE_ID_OAL_PCI_C                   = 1809,
    OAM_FILE_ID_OAL_KERNEL_FILE_C           = 1810,
    OAM_FILE_ID_OAL_HARDWARE_C              = 1811,
    OAM_FILE_ID_OAL_PCI_IF_H                = 1812,
    OAM_FILE_ID_OAL_WORKQUEUE_H             = 1813,
#ifdef _PRE_WLAN_FEATURE_SMP_SUPPORT
    OAM_FILE_ID_OAL_THREAD_H                = 1814,
#endif
    OAM_FILE_ID_OAL_PROFILING_C             = 1815,
    OAM_FILE_ID_OAL_CFG80211_C              = 1816,

    /* FRW */
    OAM_FILE_ID_FRW_EXT_IF_H                = 1900,
    OAM_FILE_ID_FRW_MAIN_C                  = 1901,
    OAM_FILE_ID_FRW_MAIN_H                  = 1902,
    OAM_FILE_ID_FRW_IPC_MSGQUEUE_H          = 1903,
    OAM_FILE_ID_FRW_IPC_MSGQUEUE_C          = 1904,
    OAM_FILE_ID_FRW_EVENT_QUEUE_H           = 1905,
    OAM_FILE_ID_FRW_EVENT_QUEUE_C           = 1906,
    OAM_FILE_ID_FRW_EVENT_SCHED_H           = 1907,
    OAM_FILE_ID_FRW_EVENT_SCHED_C           = 1908,
    OAM_FILE_ID_FRW_EVENT_MAIN_H            = 1909,
    OAM_FILE_ID_FRW_EVENT_MAIN_C            = 1910,
    OAM_FILE_ID_FRW_EVENT_DEPLOY_H          = 1911,
    OAM_FILE_ID_FRW_EVENT_DEPLOY_C          = 1912,
    OAM_FILE_ID_FRW_TASK_H                  = 1913,
    OAM_FILE_ID_FRW_TASK_C                  = 1914,
    OAM_FILE_ID_FRW_TIMER_C                 = 1915,
    OAM_FILE_ID_FRW_TIMER_H                 = 1916,

    /* BUILDER */
    OAM_FILE_ID_BLD_RAW_C                   = 1916,
    OAM_FILE_ID_BLD_RAW_H                   = 1917,
    OAM_FILE_ID_FRW_SDIO_TEST_C             = 1918,
    OAM_FILE_ID_FRW_SDIO_TEST_H             = 1919,

    OAM_FILE_ID_OAL_HCC_HOST_C              = 1920,
    OAM_FILE_ID_OAL_SDIO_HOST_C              = 1921,

    /*chip test*/
    OAM_FILE_ID_DMAC_TEST_MAIN_C            = 2000,
    OAM_FILE_ID_DMAC_TEST_MAIN_H            = 2001,
    OAM_FILE_ID_HMAC_TEST_MAIN_C            = 2002,
    OAM_FILE_ID_HMAC_TEST_MAIN_H            = 2003,
    OAM_FILE_ID_DMAC_LPM_TEST_C             = 2004,
    OAM_FILE_ID_DMAC_LPM_TEST_H             = 2005,
    OAM_FILE_ID_DMAC_FRAME_FILTER_TEST_C    = 2006,
    OAM_FILE_ID_DMAC_FRAME_FILTER_TEST_H    = 2007,
    OAM_FILE_ID_ALG_DBAC_TEST_C             = 2008,
    OAM_FILE_ID_ALG_DBAC_TEST_H             = 2009,
    OAM_FILE_ID_DMAC_TEST_SCH_C             = 2010,
    OAM_FILE_ID_DMAC_TEST_SCH_H             = 2011,
    OAM_FILE_ID_DMAC_WMM_TEST_C             = 2012,
    OAM_FILE_ID_DMAC_WMM_TEST_H             = 2013,
    OAM_FILE_ID_ALG_TEST_MAIN_C             = 2014,
    OAM_FILE_ID_ALG_TEST_MAIN_H             = 2015,
    OAM_FILE_ID_ALG_RSSI_TEST_C             = 2016,
    OAM_FILE_ID_ALG_RSSI_TEST_H             = 2017,
    OAM_FILE_ID_ALG_TPC_TEST_C              = 2018,
    OAM_FILE_ID_ALG_TPC_TEST_H              = 2019,

    OAM_FILE_ID_HAL_TEST_MAIN_C             = 2020,
    OAM_FILE_ID_HAL_TEST_MAIN_H             = 2021,
    OAM_FILE_ID_HAL_LPM_TEST_C              = 2022,
    OAM_FILE_ID_HAL_LPM_TEST_H              = 2023,

    OAM_FILE_ID_DMAC_DFS_TEST_C             = 2024,
    OAM_FILE_ID_DMAC_DFS_TEST_H             = 2025,
    OAM_FILE_ID_DMAC_ACS_TEST_C             = 2026,
    OAM_FILE_ID_DMAC_ACS_TEST_H             = 2027,
    OAM_FILE_ID_DMAC_SCAN_TEST_C            = 2028,
    OAM_FILE_ID_DMAC_SCAN_TEST_H            = 2029,

    OAM_FILE_ID_ALG_SMARTANT_TEST_C         = 2030,
    OAM_FILE_ID_ALG_SMARTANT_TEST_H         = 2031,
    OAM_FILE_ID_ALG_AUTORATE_TEST_C         = 2032,
    OAM_FILE_ID_ALG_AUTORATE_TEST_H         = 2033,

    OAM_FILE_ID_TEST_MAIN_C                 = 2034,
    OAM_FILE_ID_TEST_MAIN_H                 = 2035,

    /*sdt*/
    OAM_FILE_ID_SDT_DRV_C                   = 2100,
    OAM_FILE_ID_SDT_DRV_H                   = 2101,

    /* HUT */
    OAM_FILE_ID_HUT_MAIN_C                  = 2102,
    OAM_FILE_ID_HUT_MAIN_H                  = 2103,

    /* HSIMU */
	OAM_FILE_ID_HSIMU_REG_C                 = 2104,
    OAM_FILE_ID_HSIMU_REG_H                 = 2105,

    /* builder */
    OAM_FILE_ID_MAIN_C                      = 2106,
    OAM_FILE_ID_MAIN_H                      = 2107,

    /* plat main */
    OAM_FILE_ID_PLAT_MAIN_C                 = 2108,
    OAM_FILE_ID_PLAT_MAIN_H                 = 2109,

    OAM_FILE_ID_HAL_HI1102_CALI_C           = 2110,
    OAM_FILE_ID_HAL_HI1102_CALI_H           = 2111,

    OAM_FILE_ID_HI1102_RF_BT_CALI_C         = 2112,
    OAM_FILE_ID_HI1102_RF_BT_CALI_H         = 2113,

    OAM_FILE_ID_DMAC_DEVICE_C_ADD           = 2114,
    OAM_FILE_ID_HAL_HI1102_CALI_RAM_C       = 2115,
    OAM_FILE_ID_HAL_HI1102_CALI_RAM_H       = 2116,

    /* plat */
    OAM_FILE_ID_PLAT_PM_WLAN_C              = 2500,

    OAM_FILE_ID_MAC_AUTO_ADJUST_FREQ_C      = 2501,
    OAM_FILE_ID_HEARTBEAT_HOST_C            = 2502,
    OAM_FILE_ID_EXCEPTION_RST_C             = 2503,

    /* hwal */
    OAM_FILE_ID_HWAL_IOCTL_C                = 2600,
    OAM_FILE_ID_HWAL_IOCTL_H                = 2601,

    OAM_FILE_ID_HWAL_EVENT_C                = 2602,
    OAM_FILE_ID_HWAL_EVENT_H                = 2603,

    OAM_FILE_ID_HWAL_NET_C                  = 2604,
    OAM_FILE_ID_HWAL_NET_H                  = 2605,


    OAM_FILE_ID_BUTT
}oam_file_id_enum;
typedef oal_uint32 oam_file_id_enum_uint32;


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

#elif (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define OAM_SOFTWARE_VERSION            "Hi1151 V100R001C01B200_0515"

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
typedef enum
{
    /* ALG */
    OAM_FILE_ID_ALG_EXT_IF_H            = 1100,
    OAM_FILE_ID_ALG_TRANSPLANT_H        = 1101,
    OAM_FILE_ID_ALG_MAIN_C              = 1102,
    OAM_FILE_ID_ALG_MAIN_H              = 1103,
    OAM_FILE_ID_ALG_SCHEDULE_C          = 1104,
    OAM_FILE_ID_ALG_SCHEDULE_H          = 1105,
    OAM_FILE_ID_ALG_SCHEDULE_LOG_C      = 1106,
    OAM_FILE_ID_ALG_AUTORATE_C          = 1107,
    OAM_FILE_ID_ALG_AUTORATE_H          = 1108,
    OAM_FILE_ID_ALG_AUTORATE_LOG_C      = 1109,
    OAM_FILE_ID_ALG_AUTORATE_LOG_H      = 1110,
    OAM_FILE_ID_ALG_SMARTANT_C          = 1111,
    OAM_FILE_ID_ALG_SMARTANT_H          = 1112,
    OAM_FILE_ID_ALG_DBAC_C              = 1113,
    OAM_FILE_ID_ALG_DBAC_H              = 1114,
    OAM_FILE_ID_ALG_TXBF_H              = 1115,
    OAM_FILE_ID_ALG_TXBF_C              = 1116,
    OAM_FILE_ID_ALG_SIMPLE_SCHEDULE_C   = 1117,
    OAM_FILE_ID_ALG_SIMPLE_SCHEDULE_H   = 1118,
    OAM_FILE_ID_ALG_SCHEDULE_TRAFFIC_CTL_C  = 1119,
    OAM_FILE_ID_ALG_SCHEDULE_TRAFFIC_CTL_H  = 1120,
    OAM_FILE_ID_ALG_SCHEDULE_LOG_H          = 1121,
    OAM_FILE_ID_ALG_ANTI_INTERFERENCE_C     = 1122,
    OAM_FILE_ID_ALG_ANTI_INTERFERENCE_H     = 1123,
    OAM_FILE_ID_ALG_TPC_C                   = 1124,
    OAM_FILE_ID_ALG_TPC_H                   = 1125,
	OAM_FILE_ID_ALG_TPC_LOG_C               = 1126,
    OAM_FILE_ID_ALG_TPC_LOG_H               = 1127,
    OAM_FILE_ID_ALG_TXBF_TEST_C             = 1128,
    OAM_FILE_ID_ALG_EDCA_OPT_C              = 1129,
    OAM_FILE_ID_ALG_EDCA_OPT_H              = 1130,
    OAM_FILE_ID_ALG_MWO_DETECTION_C         = 1131,
    OAM_FILE_ID_ALG_MWO_DETECTION_H         = 1132,
    OAM_FILE_ID_ALG_CCA_OPTIMIZE_C          = 1133,
    OAM_FILE_ID_ALG_CCA_OPTIMIZE_H          = 1134,
    OAM_FILE_ID_ALG_CCA_OPTIMIZE_LOG_C      = 1135,
    OAM_FILE_ID_ALG_CCA_OPTIMIZE_LOG_H      = 1136,

    /* WAL */
    OAM_FILE_ID_WAL_EXT_IF_H            = 1200,
    OAM_FILE_ID_WAL_MAIN_C              = 1201,
    OAM_FILE_ID_WAL_MAIN_H              = 1202,
    OAM_FILE_ID_WAL_LINUX_BRIDGE_C      = 1203,
    OAM_FILE_ID_WAL_LINUX_BRIDGE_H      = 1204,
    OAM_FILE_ID_WAL_LINUX_CFG80211_C    = 1205,
    OAM_FILE_ID_WAL_LINUX_CFG80211_H    = 1206,
    OAM_FILE_ID_WAL_LINUX_IOCTL_C       = 1207,
    OAM_FILE_ID_WAL_LINUX_IOCTL_H       = 1208,
    OAM_FILE_ID_WAL_DATA_C              = 1209,
    OAM_FILE_ID_WAL_DATA_H              = 1210,
    OAM_FILE_ID_WAL_CONFIG_C            = 1211,
    OAM_FILE_ID_WAL_CONFIG_H            = 1212,
    OAM_FILE_ID_WAL_LINUX_SCAN_C        = 1213,
    OAM_FILE_ID_WAL_LINUX_SCAN_H        = 1214,
    OAM_FILE_ID_WAL_LINUX_EVENT_C       = 1215,
    OAM_FILE_ID_WAL_LINUX_EVENT_H       = 1216,
    OAM_FILE_ID_WAL_LINUX_RX_RSP_C      = 1217,
    OAM_FILE_ID_WAL_LINUX_RX_RSP_H      = 1218,
    OAM_FILE_ID_WAL_LINUX_NETLINK_C     = 1219,
    OAM_FILE_ID_WAL_LINUX_NETLINK_H     = 1220,
    OAM_FILE_ID_WAL_CONFIG_ACS_C        = 1221,
    OAM_FILE_ID_WAL_CONFIG_ACS_H        = 1222,
    OAM_FILE_ID_WAL_LINUX_FLOWCTL_C     = 1223,
    OAM_FILE_ID_WAL_LINUX_FLOWCTL_H     = 1224,
    OAM_FILE_ID_WAL_REGDB_H             = 1225,
    OAM_FILE_ID_WAL_PROXYSTA_C          = 1226,
    OAM_FILE_ID_WAL_PROXYSTA_H          = 1227,
    OAM_FILE_ID_WAL_REGDB_C             = 1228,
    OAM_FILE_ID_WAL_LINUX_ATCMDSRV_C    = 1229,
    OAM_FILE_ID_WAL_LINUX_ATCMDSRV_H    = 1230,
    OAM_FILE_ID_WAL_DFX_H               = 1231,
    OAM_FILE_ID_WAL_DFX_C               = 1232,
    
    /* HMAC */
    OAM_FILE_ID_HMAC_BACKUP_C           = 1288,
    OAM_FILE_ID_HMAC_BACKUP_H           = 1289,
/* #ifdef _PRE_WLAN_FEATURE_WOW */
    OAM_FILE_ID_HMAC_WOW_C              = 1290,
    OAM_FILE_ID_HMAC_WOW_H              = 1291,
/* #endif  //_PRE_WLAN_FEATURE_WOW */
    OAM_FILE_ID_HMAC_EXT_IF_H           = 1300,
    OAM_FILE_ID_HMAC_MAIN_C             = 1301,
    OAM_FILE_ID_HMAC_MAIN_H             = 1302,
    OAM_FILE_ID_HMAC_VAP_C              = 1303,
    OAM_FILE_ID_HMAC_VAP_H              = 1304,
    OAM_FILE_ID_HMAC_USER_C             = 1305,
    OAM_FILE_ID_HMAC_USER_H             = 1306,
    OAM_FILE_ID_HMAC_TX_DATA_C          = 1307,
    OAM_FILE_ID_HMAC_TX_DATA_H          = 1308,
    OAM_FILE_ID_HMAC_TX_BSS_COMMON_C    = 1309,
    OAM_FILE_ID_HMAC_TX_BSS_COMMON_H    = 1310,
    OAM_FILE_ID_HMAC_TX_AMSDU_C         = 1311,
    OAM_FILE_ID_HMAC_TX_AMSDU_H         = 1312,
    OAM_FILE_ID_HMAC_RX_DATA_C          = 1313,
    OAM_FILE_ID_HMAC_RX_DATA_H          = 1314,
    OAM_FILE_ID_HMAC_MGMT_CLASSIFIER_C  = 1315,
    OAM_FILE_ID_HMAC_MGMT_CLASSIFIER_H  = 1316,
    OAM_FILE_ID_HMAC_MGMT_BSS_COMM_C    = 1317,
    OAM_FILE_ID_HMAC_MGMT_BSS_COMM_H    = 1318,
    OAM_FILE_ID_HMAC_MGMT_STA_C         = 1319,
    OAM_FILE_ID_HMAC_MGMT_STA_H         = 1320,
    OAM_FILE_ID_HMAC_MGMT_AP_C          = 1321,
    OAM_FILE_ID_HMAC_MGMT_AP_H          = 1322,
    OAM_FILE_ID_HMAC_FSM_C              = 1323,
    OAM_FILE_ID_HMAC_FSM_H              = 1324,
    OAM_FILE_ID_HMAC_11i_C              = 1325,
    OAM_FILE_ID_HMAC_11i_H              = 1326,
    OAM_FILE_ID_HMAC_UAPSD_C            = 1327,
    OAM_FILE_ID_HMAC_UAPSD_H            = 1328,
    OAM_FILE_ID_HMAC_CONFIG_C           = 1329,
    OAM_FILE_ID_HMAC_CONFIG_H           = 1330,
    OAM_FILE_ID_HMAC_FRAG_C             = 1331,
    OAM_FILE_ID_HMAC_FRAG_H             = 1332,
    OAM_FILE_ID_HMAC_PROTECTION_C       = 1333,
    OAM_FILE_ID_HMAC_PROTECTION_H       = 1334,
    OAM_FILE_ID_HMAC_CHAN_MGMT_C        = 1335,
    OAM_FILE_ID_HMAC_CHAN_MGMT_H        = 1336,
    OAM_FILE_ID_HMAC_SMPS_H             = 1337,
    OAM_FILE_ID_HMAC_SMPS_C             = 1338,
    OAM_FILE_ID_HMAC_DATA_ACQ_H         = 1339,
    OAM_FILE_ID_HMAC_DATA_ACQ_C         = 1340,
    OAM_FILE_ID_HMAC_RX_FILTER_H        = 1341,
    OAM_FILE_ID_HMAC_RX_FILTER_C        = 1342,
    OAM_FILE_ID_HMAC_ENCAP_FRAME_STA_C  = 1343,
    OAM_FILE_ID_HMAC_ENCAP_FRAME_AP_C   = 1344,
    OAM_FILE_ID_HMAC_CUSTOM_SECURITY_C  = 1345,
	OAM_FILE_ID_HMAC_M2U_C              = 1346,
    OAM_FILE_ID_HMAC_M2U_H              = 1347,
    OAM_FILE_ID_HMAC_PROXYARP_C         = 1348,
    OAM_FILE_ID_HMAC_HCC_ADAPT_H        = 1349,
    OAM_FILE_ID_HMAC_HCC_ADAPT_C        = 1350,
    OAM_FILE_ID_HMAC_SME_STA_C          = 1351,
    OAM_FILE_ID_HMAC_SME_STA_H          = 1352,
    OAM_FILE_ID_HMAC_DFS_C              = 1353,
    OAM_FILE_ID_HMAC_DFS_H              = 1354,
    OAM_FILE_ID_HMAC_RESET_H            = 1355,
    OAM_FILE_ID_HMAC_RESET_C            = 1356,
    OAM_FILE_ID_HMAC_SCAN_H             = 1357,
    OAM_FILE_ID_HMAC_SCAN_C             = 1358,
    OAM_FILE_ID_HMAC_P2P_C              = 1359,
    OAM_FILE_ID_HMAC_P2P_H              = 1360,
    OAM_FILE_ID_HMAC_EDCA_OPT_H         = 1361,
    OAM_FILE_ID_HMAC_EDCA_OPT_C         = 1362,
    OAM_FILE_ID_HMAC_BLOCKACK_H         = 1363,
    OAM_FILE_ID_HMAC_BLOCKACK_C         = 1364,
    OAM_FILE_ID_HMAC_PSM_AP_H           = 1365,
    OAM_FILE_ID_HMAC_PSM_AP_C           = 1366,
	OAM_FILE_ID_HMAC_RESOURCE_C         = 1367,
    OAM_FILE_ID_HMAC_RESOURCE_H         = 1368,
    OAM_FILE_ID_HMAC_DEVICE_C           = 1369,
    OAM_FILE_ID_HMAC_DEVICE_H           = 1370,
    OAM_FILE_ID_HMAC_WAPI_SMS4_C        = 1371,
    OAM_FILE_ID_HMAC_WAPI_SMS4_H        = 1372,
    OAM_FILE_ID_HMAC_WAPI_WPI_C         = 1373,
    OAM_FILE_ID_HMAC_WAPI_WPI_H         = 1374,
    OAM_FILE_ID_HMAC_ARP_OFFLOAD_C      = 1375,
    OAM_FILE_ID_HMAC_ARP_OFFLOAD_H      = 1376,
    OAM_FILE_ID_HMAC_ACS_C              = 1377,
    OAM_FILE_ID_HMAC_ACS_H              = 1378,
    OAM_FILE_ID_HMAC_TCP_OPT_C          = 1379,
    OAM_FILE_ID_HMAC_TCP_OPT_H          = 1380,
    OAM_FILE_ID_HMAC_TCP_OPT_STRUC_H    = 1381,
/* #ifdef _PRE_WLAN_FEATURE_ROAM */
    OAM_FILE_ID_HMAC_ROAM_ALG_C         = 1382,
    OAM_FILE_ID_HMAC_ROAM_ALG_H         = 1383,
    OAM_FILE_ID_HMAC_ROAM_MAIN_C        = 1384,
    OAM_FILE_ID_HMAC_ROAM_MAIN_H        = 1385,
    OAM_FILE_ID_HMAC_ROAM_CONNECT_C     = 1386,
    OAM_FILE_ID_HMAC_ROAM_CONNECT_H     = 1387,
/* #endif  //_PRE_WLAN_FEATURE_ROAM */
    OAM_FILE_ID_HMAC_ENCAP_FRAME_C      = 1388,

    OAM_FILE_ID_HMAC_WAPI_C             = 1389,
    OAM_FILE_ID_HMAC_WAPI_H             = 1390,
    OAM_FILE_ID_HMAC_CALI_MGMT_C        = 1391,
    OAM_FILE_ID_HMAC_CALI_MGMT_H        = 1392,
    OAM_FILE_ID_HMAC_CUSTOMIZE          = 1393,

    OAM_FILE_ID_HMAC_DFX_C              = 1394,
    OAM_FILE_ID_HMAC_DFX_H              = 1395,

    OAM_FILE_ID_HMAC_TRAFFIC_CLASSIFY_C = 1396,
    OAM_FILE_ID_HMAC_TRAFFIC_CLASSIFY_H = 1397,
#ifdef _PRE_WLAN_FEATURE_TCP_UDP_KEEPALIVE     
    OAM_FILE_ID_HMAC_TCP_UDP_KEEPALIVE_C = 1398,
    OAM_FILE_ID_HMAC_TCP_UDP_KEEPALIVE_H = 1399,
#endif

    /* DMAC */
    OAM_FILE_ID_DMAC_EXT_IF_H           = 1400,
    OAM_FILE_ID_DMAC_ALG_IF_H           = 1401,
    OAM_FILE_ID_DMAC_MAIN_C             = 1402,
    OAM_FILE_ID_DMAC_MAIN_H             = 1403,
    OAM_FILE_ID_DMAC_VAP_C              = 1404,
    OAM_FILE_ID_DMAC_VAP_H              = 1405,
    OAM_FILE_ID_MAC_RESOURCE_C          = 1406,
    OAM_FILE_ID_MAC_RESOURCE_H          = 1407,
    OAM_FILE_ID_MAC_DEVICE_C            = 1408,
    OAM_FILE_ID_MAC_DEVICE_H            = 1409,
    OAM_FILE_ID_MAC_VAP_C               = 1410,
    OAM_FILE_ID_MAC_VAP_H               = 1411,
    OAM_FILE_ID_MAC_USER_C              = 1412,
    OAM_FILE_ID_MAC_USER_H              = 1413,
    OAM_FILE_ID_MAC_IE_C                = 1414,
    OAM_FILE_ID_MAC_IE_H                = 1415,
    OAM_FILE_ID_MAC_FRAME_C             = 1416,
    OAM_FILE_ID_MAC_REGDOMAIN_C         = 1417,
    OAM_FILE_ID_DMAC_USER_C             = 1418,
    OAM_FILE_ID_DMAC_USER_H             = 1419,
    OAM_FILE_ID_DMAC_RX_DATA_C          = 1420,
    OAM_FILE_ID_DMAC_RX_DATA_H          = 1421,
    OAM_FILE_ID_DMAC_TID_C              = 1422,
    OAM_FILE_ID_DMAC_TID_H              = 1423,
    OAM_FILE_ID_DMAC_TX_DSCR_QUEUE_C    = 1424,
    OAM_FILE_ID_DMAC_TX_DSCR_QUEUE_H    = 1425,
    OAM_FILE_ID_DMAC_TX_BSS_COMM_C      = 1426,
    OAM_FILE_ID_DMAC_TX_BSS_COMM_H      = 1427,
    OAM_FILE_ID_DMAC_PSM_AP_C           = 1428,
    OAM_FILE_ID_DMAC_PSM_AP_H           = 1429,
    OAM_FILE_ID_DMAC_TX_COMPLETE_H      = 1430,
    OAM_FILE_ID_DMAC_TX_COMPLETE_C      = 1431,
    OAM_FILE_ID_DMAC_MGMT_CLASSIFIER_C  = 1432,
    OAM_FILE_ID_DMAC_MGMT_CLASSIFIER_H  = 1433,
    OAM_FILE_ID_DMAC_MGMT_BSS_COMM_C    = 1434,
    OAM_FILE_ID_DMAC_MGMT_BSS_COMM_H    = 1435,
    OAM_FILE_ID_DMAC_MGMT_AP_C          = 1436,
    OAM_FILE_ID_DMAC_MGMT_AP_H          = 1437,
    OAM_FILE_ID_DMAC_MGMT_STA_C         = 1438,
    OAM_FILE_ID_DMAC_MGMT_STA_H         = 1439,
    OAM_FILE_ID_DMAC_UAPSD_C            = 1440,
    OAM_FILE_ID_DMAC_UAPSD_H            = 1441,
    OAM_FILE_ID_DMAC_ALG_C              = 1442,
    OAM_FILE_ID_DMAC_ALG_H              = 1443,
    OAM_FILE_ID_DMAC_BLOCKACK_C         = 1444,
    OAM_FILE_ID_DMAC_BLOCKACK_H         = 1445,
    OAM_FILE_ID_DMAC_BEACON_C           = 1446,
    OAM_FILE_ID_DMAC_BEACON_H           = 1447,
    OAM_FILE_ID_DMAC_WEP_C              = 1448,
    OAM_FILE_ID_DMAC_WEP_H              = 1449,
    OAM_FILE_ID_DMAC_11I_C              = 1450,
    OAM_FILE_ID_DMAC_11I_H              = 1451,
    OAM_FILE_ID_DMAC_SCAN_C             = 1452,
    OAM_FILE_ID_DMAC_SCAN_H             = 1453,
    OAM_FILE_ID_DMAC_ACS_C              = 1454,
    OAM_FILE_ID_DMAC_ACS_H              = 1455,
    OAM_FILE_ID_DMAC_DFS_C              = 1456,
    OAM_FILE_ID_DMAC_DFS_H              = 1457,
    OAM_FILE_ID_DMAC_RESET_C            = 1458,
    OAM_FILE_ID_DMAC_RESET_H            = 1459,
    OAM_FILE_ID_MAC_FCS_C               = 1460,
    OAM_FILE_ID_MAC_FCS_H               = 1461,
    OAM_FILE_ID_DMAC_CONFIG_C           = 1462,
    OAM_FILE_ID_DMAC_CONFIG_H           = 1463,
    OAM_FILE_ID_DMAC_STAT_C             = 1464,
    OAM_FILE_ID_DMAC_STAT_H             = 1465,
    OAM_FILE_ID_ALG_SCH_TEST_H          = 1466,
    OAM_FILE_ID_ALG_SCH_TEST_C          = 1467,
    OAM_FILE_ID_DMAC_CHAN_MGMT_C        = 1468,
    OAM_FILE_ID_DMAC_CHAN_MGMT_H        = 1469,
    OAM_FILE_ID_DMAC_DATA_ACQ_H         = 1470,
    OAM_FILE_ID_DMAC_DATA_ACQ_C         = 1471,
    OAM_FILE_ID_DMAC_USER_TRACK_H       = 1472,
    OAM_FILE_ID_DMAC_USER_TRACK_C       = 1473,
    OAM_FILE_ID_DMAC_RX_FILTER_H        = 1474,
    OAM_FILE_ID_DMAC_RX_FILTER_C        = 1475,
    OAM_FILE_ID_MAC_REGDOMAIN_H         = 1476,
    OAM_FILE_ID_MAC_FRAME_H             = 1477,
    OAM_FILE_ID_DMAC_11W_C              = 1478,
    OAM_FILE_ID_DMAC_TXOPPS_C           = 1479,
    OAM_FILE_ID_DMAC_TXOPPS_H           = 1480,
    OAM_FILE_ID_DMAC_DFT_H              = 1481,
    OAM_FILE_ID_DMAC_DFT_C              = 1482,
	OAM_FILE_ID_DMAC_AP_PM_C            = 1483,
    OAM_FILE_ID_DMAC_AP_PM_H            = 1484,
    OAM_FILE_ID_MAC_PM_C                = 1485,
    OAM_FILE_ID_MAC_PM_H                = 1486,
    OAM_FILE_ID_DMAC_SIMPLE_SCHEDULE_C  = 1487,
    OAM_FILE_ID_DMAC_SIMPLE_SCHEDULE_H  = 1488,
    OAM_FILE_ID_DMAC_HCC_ADAPT_C        = 1489,
    OAM_FILE_ID_DMAC_HCC_ADAPT_H        = 1490,
    OAM_FILE_ID_MAC_BOARD_C             = 1491,
    OAM_FILE_ID_MAC_BOARD_H             = 1492,
    OAM_FILE_ID_DMAC_P2P_C              = 1493,
    OAM_FILE_ID_DMAC_P2P_H              = 1494,
    OAM_FILE_ID_DMAC_BTCOEX_C           = 1495,
	OAM_FILE_ID_DMAC_BTCOEX_H           = 1496,


    OAM_FILE_ID_DMAC_STA_PM_C           = 1497,
    OAM_FILE_ID_DMAC_STA_PM_H           = 1498,
    OAM_FILE_ID_DMAC_UAPSD_STA_C        = 1499,
    OAM_FILE_ID_DMAC_UAPSD_STA_H        = 1500,
	OAM_FILE_ID_DMAC_PSM_STA_C          = 1501,
    OAM_FILE_ID_DMAC_PSM_STA_H          = 1502,
    OAM_FILE_ID_DMAC_PM_STA_C           = 1503,
    OAM_FILE_ID_DMAC_PM_STA_H           = 1504,

    OAM_FILE_ID_MAC_DATA_C              = 1505,
	OAM_FILE_ID_DMAC_LTECOEX_C          = 1506,
	OAM_FILE_ID_DMAC_LTECOEX_H          = 1507,

    OAM_FILE_ID_MAC_11I_C               = 1508,
    OAM_FILE_ID_MAC_11I_H               = 1509,
    OAM_FILE_ID_DMAC_PROFILING_H        = 1510,
    OAM_FILE_ID_DMAC_DFX_C              = 1511,
    OAM_FILE_ID_DMAC_DFX_H              = 1512,
    OAM_FILE_ID_DMAC_DEVICE_C           = 1513,
    OAM_FILE_ID_DMAC_DEVICE_H           = 1514,
    OAM_FILE_ID_DMAC_ARP_OFFLOAD_C      = 1515,
    OAM_FILE_ID_DMAC_ARP_OFFLOAD_H      = 1516,

    OAM_FILE_ID_DMAC_RESOURCE_C         = 1517,
    OAM_FILE_ID_DMAC_RESOURCE_H         = 1518,
    OAM_FILE_ID_DMAC_AUTO_ADJUST_FREQ_C = 1519,
    OAM_FILE_ID_DMAC_AUTO_ADJUST_FREQ_H = 1520,
#ifdef _PRE_WLAN_FEATURE_TCP_UDP_KEEPALIVE 
    OAM_FILE_ID_DMAC_TCP_UDP_KEEPALIVE_H = 1521,
    OAM_FILE_ID_DMAC_TCP_UDP_KEEPALIVE_C = 1522,
#endif

    /* HAL */
    OAM_FILE_ID_UT_HAL_TX_PROC_PROFILING_C  = 1600,
    OAM_FILE_ID_HAL_EXT_IF_H                = 1601,
    OAM_FILE_ID_HAL_PA_C                    = 1602,
    OAM_FILE_ID_HAL_PA_H                    = 1603,
    OAM_FILE_ID_HAL_BASE_C                  = 1604,
    OAM_FILE_ID_HAL_BASE_H                  = 1605,
    OAM_FILE_ID_HAL_MAIN_C                  = 1606,
    OAM_FILE_ID_HAL_MAIN_H                  = 1607,
    OAM_FILE_ID_HAL_IRQ_C                   = 1608,
    OAM_FILE_ID_HAL_IRQ_H                   = 1609,
    OAM_FILE_ID_HAL_TO_DMAC_IF_C            = 1610,
    OAM_FILE_ID_HAL_CHIP_C                  = 1611,
    OAM_FILE_ID_HAL_DEVICE_C                = 1612,
    OAM_FILE_ID_HAL_DEVICE_H                = 1613,
    OAM_FILE_ID_HAL_SIM_C                   = 1614,
    OAM_FILE_ID_HAL_WITP_MAC_C              = 1615,
    OAM_FILE_ID_HAL_WITP_RF_C               = 1616,
    OAM_FILE_ID_HAL_WITP_RF_H               = 1617,
    OAM_FILE_ID_HAL_WITP_CALI_C             = 1618,
    OAM_FILE_ID_HAL_WITP_CALI_H             = 1619,
    OAM_FILE_ID_HAL_WITP_MAC_H              = 1620,
    OAM_FILE_ID_HAL_RESET_C                 = 1621,
    OAM_FILE_ID_HAL_RESET_H                 = 1622,
    OAM_FILE_ID_HAL_WITP_PHY_REG_H          = 1623,
    OAM_FILE_ID_HAL_WITP_DMT_IF_C           = 1624,
    OAM_FILE_ID_HAL_WITP_DMT_IF_H           = 1625,
    OAM_FILE_ID_WITP_DEBUG_C                = 1626,
    OAM_FILE_ID_HAL_WITP_SOC_H              = 1627,
    OAM_FILE_ID_HAL_WITP_PHY_H              = 1628,
    OAM_FILE_ID_HAL_WITP_PHY_C              = 1629,
    OAM_FILE_ID_HAL_HW_MAC_H                = 1630,

    OAM_FILE_ID_HAL_HI1102_PHY_REG_H          = 1631,
    OAM_FILE_ID_HAL_HI1102_MAC_REG_H          = 1632,
    OAM_FILE_ID_HAL_HI1102_SOC_H              = 1633,
    OAM_FILE_ID_HAL_HI1102_PHY_H              = 1634,
    OAM_FILE_ID_HAL_HI1102_PHY_C              = 1635,
    OAM_FILE_ID_HAL_HI1102_MAC_H              = 1636,
    OAM_FILE_ID_HAL_HI1102_MAC_C              = 1637,
    OAM_FILE_ID_HAL_DBB_REG_RW_H              = 1638,
    OAM_FILE_ID_HAL_HI1102_DSCR_H             = 1639,
    OAM_FILE_ID_HAL_HI1102_DSCR_C             = 1640,
    OAM_FILE_ID_HAL_HI1102_RF_H               = 1641,
    OAM_FILE_ID_HAL_HI1102_RF_C               = 1642,
    OAM_FILE_ID_HAL_HI1102_RESET_H            = 1643,
    OAM_FILE_ID_HAL_HI1102_RESET_C            = 1644,
    OAM_FILE_ID_HAL_HI1102_IRQ_H              = 1645,
    OAM_FILE_ID_HAL_HI1102_IRQ_C              = 1646,
    OAM_FILE_ID_HAL_HI1102_SOC_REG_H          = 1647,
    OAM_FILE_ID_HAL_HI1102_COEX_REG_H         = 1648,
    OAM_FILE_ID_HAL_HI1102_COEX_REG_C         = 1649,
    OAM_FILE_ID_HI1102_RF_CORIDC_C            = 1650,
    OAM_FILE_ID_HI1102_RF_CORIDC_H            = 1651,
    OAM_FILE_ID_HAL_HI1102_PM_C               = 1652,
    OAM_FILE_ID_HAL_HI1102_PM_H               = 1653,
    OAM_FILE_ID_HAL_HI1102_CALI_DPD_C         = 1654,
    OAM_FILE_ID_HAL_HI1102_CALI_DPD_H         = 1655,
 #ifdef _PRE_WLAN_RF_110X_CALI_DPD
    OAM_FILE_ID_HMAC_CALI_DPD_C               = 1656,
    OAM_FILE_ID_HMAC_CALI_DPD_H               = 1657,
#endif
    OAM_FILE_ID_HAL_HI1102_RF_RAM_C           = 1658,
    OAM_FILE_ID_HAL_HI1102_CALI_DPD_RAM_C     = 1659,

    /* OAM */
    OAM_FILE_ID_OAM_LINUX_NETLINK_C         = 1700,
    OAM_FILE_ID_OAM_LINUX_NETLINK_H         = 1701,
    OAM_FILE_ID_OAM_LOG_C                   = 1702,
    OAM_FILE_ID_OAM_LOG_H                   = 1703,
    OAM_FILE_ID_OAM_TRACE_C                 = 1704,
    OAM_FILE_ID_OAM_TRACE_H                 = 1705,
    OAM_FILE_ID_OAM_STATISTICS_C            = 1706,
    OAM_FILE_ID_OAM_STATISTICS_H            = 1707,
    OAM_FILE_ID_OAM_EXT_IF_H                = 1708,
    OAM_FILE_ID_OAM_MAIN_C                  = 1709,
    OAM_FILE_ID_OAM_MAIN_H                  = 1710,
    OAM_FILE_ID_REGISTER_C                  = 1711,
    OAM_FILE_ID_REGISTER_H                  = 1712,
    OAM_FILE_ID_OAM_EVENT_C                 = 1713,
    OAM_FILE_ID_OAM_EVENT_H                 = 1714,

    /* OAL */
    OAM_FILE_ID_OAL_EXT_IF_H                = 1800,
    OAM_FILE_ID_OAL_MAIN_C                  = 1801,
    OAM_FILE_ID_OAL_MAIN_H                  = 1802,
    OAM_FILE_ID_OAL_TYPES_H                 = 1803,
    OAM_FILE_ID_OAL_MEM_C                   = 1804,
    OAM_FILE_ID_OAL_MEM_H                   = 1805,
    OAM_FILE_ID_OAL_QUEUE_H                 = 1806,
    OAM_FILE_ID_OAL_GPIO_H                  = 1807,
    OAM_FILE_ID_OAL_NET_C                   = 1808,
    OAM_FILE_ID_OAL_PCI_C                   = 1809,
    OAM_FILE_ID_OAL_KERNEL_FILE_C           = 1810,
    OAM_FILE_ID_OAL_HARDWARE_C              = 1811,
    OAM_FILE_ID_OAL_PCI_IF_H                = 1812,
    OAM_FILE_ID_OAL_WORKQUEUE_H             = 1813,
#ifdef _PRE_WLAN_FEATURE_SMP_SUPPORT
    OAM_FILE_ID_OAL_THREAD_H                = 1814,
#endif
    OAM_FILE_ID_OAL_PROFILING_C             = 1815,
    OAM_FILE_ID_OAL_CFG80211_C              = 1816,

    /* FRW */
    OAM_FILE_ID_FRW_EXT_IF_H                = 1900,
    OAM_FILE_ID_FRW_MAIN_C                  = 1901,
    OAM_FILE_ID_FRW_MAIN_H                  = 1902,
    OAM_FILE_ID_FRW_IPC_MSGQUEUE_H          = 1903,
    OAM_FILE_ID_FRW_IPC_MSGQUEUE_C          = 1904,
    OAM_FILE_ID_FRW_EVENT_QUEUE_H           = 1905,
    OAM_FILE_ID_FRW_EVENT_QUEUE_C           = 1906,
    OAM_FILE_ID_FRW_EVENT_SCHED_H           = 1907,
    OAM_FILE_ID_FRW_EVENT_SCHED_C           = 1908,
    OAM_FILE_ID_FRW_EVENT_MAIN_H            = 1909,
    OAM_FILE_ID_FRW_EVENT_MAIN_C            = 1910,
    OAM_FILE_ID_FRW_EVENT_DEPLOY_H          = 1911,
    OAM_FILE_ID_FRW_EVENT_DEPLOY_C          = 1912,
    OAM_FILE_ID_FRW_TASK_H                  = 1913,
    OAM_FILE_ID_FRW_TASK_C                  = 1914,
    OAM_FILE_ID_FRW_TIMER_C                 = 1915,
    OAM_FILE_ID_FRW_TIMER_H                 = 1916,

    /* BUILDER */
    OAM_FILE_ID_BLD_RAW_C                   = 1916,
    OAM_FILE_ID_BLD_RAW_H                   = 1917,
    OAM_FILE_ID_FRW_SDIO_TEST_C             = 1918,
    OAM_FILE_ID_FRW_SDIO_TEST_H             = 1919,

    OAM_FILE_ID_OAL_HCC_HOST_C              = 1920,
    OAM_FILE_ID_OAL_SDIO_HOST_C              = 1921,

    /*chip test*/
    OAM_FILE_ID_DMAC_TEST_MAIN_C            = 2000,
    OAM_FILE_ID_DMAC_TEST_MAIN_H            = 2001,
    OAM_FILE_ID_HMAC_TEST_MAIN_C            = 2002,
    OAM_FILE_ID_HMAC_TEST_MAIN_H            = 2003,
    OAM_FILE_ID_DMAC_LPM_TEST_C             = 2004,
    OAM_FILE_ID_DMAC_LPM_TEST_H             = 2005,
    OAM_FILE_ID_DMAC_FRAME_FILTER_TEST_C    = 2006,
    OAM_FILE_ID_DMAC_FRAME_FILTER_TEST_H    = 2007,
    OAM_FILE_ID_ALG_DBAC_TEST_C             = 2008,
    OAM_FILE_ID_ALG_DBAC_TEST_H             = 2009,
    OAM_FILE_ID_DMAC_TEST_SCH_C             = 2010,
    OAM_FILE_ID_DMAC_TEST_SCH_H             = 2011,
    OAM_FILE_ID_DMAC_WMM_TEST_C             = 2012,
    OAM_FILE_ID_DMAC_WMM_TEST_H             = 2013,
    OAM_FILE_ID_ALG_TEST_MAIN_C             = 2014,
    OAM_FILE_ID_ALG_TEST_MAIN_H             = 2015,
    OAM_FILE_ID_ALG_RSSI_TEST_C             = 2016,
    OAM_FILE_ID_ALG_RSSI_TEST_H             = 2017,
    OAM_FILE_ID_ALG_TPC_TEST_C              = 2018,
    OAM_FILE_ID_ALG_TPC_TEST_H              = 2019,

    OAM_FILE_ID_HAL_TEST_MAIN_C             = 2020,
    OAM_FILE_ID_HAL_TEST_MAIN_H             = 2021,
    OAM_FILE_ID_HAL_LPM_TEST_C              = 2022,
    OAM_FILE_ID_HAL_LPM_TEST_H              = 2023,

    OAM_FILE_ID_DMAC_DFS_TEST_C             = 2024,
    OAM_FILE_ID_DMAC_DFS_TEST_H             = 2025,
    OAM_FILE_ID_DMAC_ACS_TEST_C             = 2026,
    OAM_FILE_ID_DMAC_ACS_TEST_H             = 2027,
    OAM_FILE_ID_DMAC_SCAN_TEST_C            = 2028,
    OAM_FILE_ID_DMAC_SCAN_TEST_H            = 2029,

    OAM_FILE_ID_ALG_SMARTANT_TEST_C         = 2030,
    OAM_FILE_ID_ALG_SMARTANT_TEST_H         = 2031,
    OAM_FILE_ID_ALG_AUTORATE_TEST_C         = 2032,
    OAM_FILE_ID_ALG_AUTORATE_TEST_H         = 2033,

    OAM_FILE_ID_TEST_MAIN_C                 = 2034,
    OAM_FILE_ID_TEST_MAIN_H                 = 2035,
	
    /*rom callback文件*/
    OAM_FILE_ID_HAL_ROMCB_C                 = 2036,
    OAM_FILE_ID_HAL_ROMCB_H                 = 2037,

    OAM_FILE_ID_DMAC_ROMCB_C                = 2038,
    OAM_FILE_ID_DMAC_ROMCB_H                = 2039,

    /*sdt*/
    OAM_FILE_ID_SDT_DRV_C                   = 2100,
    OAM_FILE_ID_SDT_DRV_H                   = 2101,

    /* HUT */
    OAM_FILE_ID_HUT_MAIN_C                  = 2102,
    OAM_FILE_ID_HUT_MAIN_H                  = 2103,

    /* HSIMU */
	OAM_FILE_ID_HSIMU_REG_C                 = 2104,
    OAM_FILE_ID_HSIMU_REG_H                 = 2105,

    /* builder */
    OAM_FILE_ID_MAIN_C                      = 2106,
    OAM_FILE_ID_MAIN_H                      = 2107,

    /* plat main */
    OAM_FILE_ID_PLAT_MAIN_C                 = 2108,
    OAM_FILE_ID_PLAT_MAIN_H                 = 2109,

    OAM_FILE_ID_HAL_HI1102_CALI_C           = 2110,
    OAM_FILE_ID_HAL_HI1102_CALI_H           = 2111,

    OAM_FILE_ID_HI1102_RF_BT_CALI_C         = 2112,
    OAM_FILE_ID_HI1102_RF_BT_CALI_H         = 2113,

    OAM_FILE_ID_DMAC_DEVICE_C_ADD           = 2114,
    OAM_FILE_ID_HAL_HI1102_CALI_RAM_C       = 2115,
    OAM_FILE_ID_HAL_HI1102_CALI_RAM_H       = 2116,

    /* plat */
    OAM_FILE_ID_PLAT_PM_WLAN_C              = 2500,

    OAM_FILE_ID_MAC_AUTO_ADJUST_FREQ_C      = 2501,
    OAM_FILE_ID_HEARTBEAT_HOST_C            = 2502,
    OAM_FILE_ID_EXCEPTION_RST_C             = 2503,

    /* hwal */
    OAM_FILE_ID_HWAL_IOCTL_C                = 2600,
    OAM_FILE_ID_HWAL_IOCTL_H                = 2601,
    
    OAM_FILE_ID_HWAL_EVENT_C                = 2602,
    OAM_FILE_ID_HWAL_EVENT_H                = 2603,

    OAM_FILE_ID_HWAL_NET_C                  = 2604,
    OAM_FILE_ID_HWAL_NET_H                  = 2605,
    OAM_FILE_ID_WIFI_SHELL_CMD_REGISTER_C  = 2606,
    OAM_FILE_ID_OS_ADAPT_C = 2607,
    OAM_FILE_ID_BUTT
}oam_file_id_enum;
typedef oal_uint32 oam_file_id_enum_uint32;


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oam_wdk.h */

