/*
 *
 * Copyright (C), 2001-2021, Hisilicon Tech. Co., Ltd.
 *
 * File Name     : hisi_ini.h
 * Version	     : Initial Draft
 * Created	     : 2012/8/26
 * Last Modified :
 * Description   : hisi_ini.c header file
 * Function List :
 * History 	     :
 * 1.Date		 : 2013/10/21
 *   Modification: Created file
 *
 */

#ifndef __HISI_INI_H__
#define __HISI_INI_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*
 * 1 Other Header File Including
 */
#include "plat_debug.h"

/*
 * 2 Macro Definition
 */

#define INI_KO_MODULE
//#define INI_TEST

//#define INI_FILE_PATH			("./hisi_cfg.ini")

#ifdef INI_KO_MODULE
#if (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
#include "oam_ext_if.h"
#endif

#define INI_TIME_TEST

#define INI_MIN(_A, _B) (((_A) < (_B))? (_A) : (_B))
#define INI_DEBUG(fmt, arg...) do { \
    if (PLAT_LOG_DEBUG <= g_plat_loglevel) \
    {\
        printk(KERN_DEBUG "INI_DRV:D]%s:%d]"fmt"\n",__FUNCTION__,__LINE__, ##arg); \
    }\
} while(0)

#define INI_INFO(fmt, arg...) do { \
    if (PLAT_LOG_INFO <= g_plat_loglevel) \
    {\
        printk(KERN_DEBUG "INI_DRV:D]%s:%d]"fmt"\n",__FUNCTION__,__LINE__,##arg); \
    }\
} while(0)

#define INI_WARNING(fmt, arg...) do { \
    if (PLAT_LOG_WARNING <= g_plat_loglevel) \
    {\
        printk(KERN_WARNING "INI_DRV:W]%s:%d]"fmt"\n",__FUNCTION__,__LINE__,##arg); \
    }\
} while(0)

#define INI_ERROR(fmt, arg...) do { \
    if (PLAT_LOG_ERR <= g_plat_loglevel) \
    {\
        printk(KERN_ERR "INI_DRV:E]%s:%d]"fmt"\n\n\n",__FUNCTION__,__LINE__,##arg); \
    }\
} while(0)
#else

#include <cutils/log.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "INI_SO"

#ifdef INI_LOG_DEBUG_ENABLE
#define INI_DEBUG(fmt, arg...) do {\
    ALOGD("[%s:%d]"fmt"\n",__FUNCTION__,__LINE__, ##arg); \
} while(0)
#else
#define INI_DEBUG(fmt, arg...)
#endif

#define INI_INFO(fmt, arg...) do {\
    ALOGI(":I]%s:%d]"fmt"\n",__FUNCTION__,__LINE__,##arg); \
} while(0)

#define INI_WARNING(fmt, arg...) do {\
    ALOGW(":W]%s:%d]"fmt"\n",__FUNCTION__,__LINE__,##arg); \
} while(0)

#define INI_ERROR(fmt, arg...) do {\
    ALOGE(":E]%s:%d]"fmt"\n",__FUNCTION__,__LINE__,##arg); \
} while(0)

#define INI_FILE        FILE
typedef unsigned char                   uint8;
typedef char                            int8;
typedef unsigned short                  uint16;
typedef signed short                    int16;
typedef unsigned int                    uint32;
typedef signed int                      int32;
#endif

#define NVRAM_CUST_FILE    "/data/hisi_nv_conf"

#define HISI_CUST_NVRAM_READ     (1)
#define HISI_CUST_NVRAM_WRITE    (0)
#define HISI_CUST_NVRAM_NUM      (340)
#define HISI_CUST_NVRAM_LEN      (104)
#define HISI_CUST_NVRAM_NAME     "WINVRAM"

#define INI_MODU_WIFI           (0x1)
#define INI_MODU_GNSS           (0x2)
#define INI_MODU_BT             (0x4)
#define INI_MODU_FM             (0x8)
#define INI_MODU_WIFI_PLAT      (0x10)
#define INI_MODU_BFG_PLAT       (0x20)
#define INI_MODU_PLAT           (0x40)
#define INI_MODU_HOST_VERSION   (0x80)
#define INI_MODU_WIFI_MAC       (0x81)
#define INI_MODU_COEXIST        (0x82)

#define CUST_MODU_WIFI          (0x1)
#define CUST_MODU_GNSS          (0x2)
#define CUST_MODU_BT            (0x4)
#define CUST_MODU_FM            (0x8)
#define CUST_MODU_WIFI_PLAT     (0x10)
#define CUST_MODU_BFG_PLAT      (0x20)
#define CUST_MODU_PLAT          (0x40)
#ifdef INI_KO_MODULE
#define CUST_MODU_DTS           (0x50)
#endif
#define CUST_MODU_HOST_VERSION  (0x80)
#define CUST_MODU_WIFI_MAC      (0x81)
#define CUST_MODU_COEXIST       (0x82)
#define CUST_MODU_NVRAM         (0x83)

#define INI_MODE_VAR_WIFI           ("wifi_ini_mode")
#define INI_MODE_VAR_GNSS           ("gnss_ini_mode")
#define INI_MODE_VAR_BT             ("bt_ini_mode")
#define INI_MODE_VAR_FM             ("fm_ini_mode")
#define INI_MODE_VAR_WIFI_PLAT      ("wifi_plat_ini_mode")
#define INI_MODE_VAR_BFG_PLAT       ("bfg_plat_ini_mode")

#define INI_VAR_PLAT_BOARD          ("g_board_version.board_version")
#define INI_VAR_PLAT_PARAM          ("g_param_version.param_version")

#define INI_STR_WIFI_NORMAL0        ("[HOST_WIFI_NORMAL]")
#define INI_STR_DEVICE_WIFI         ("[DEVICE_WIFI]")

#ifdef INI_KO_MODULE

#define INI_STR_BOARD_CFG               ("[HOST_BOARD_CFG]")
#define INI_STR_WIFI_NORMAL             ("[HOST_WIFI_NORMAL]")
#define INI_STR_WIFI_PERFORMANCE        ("[HOST_WIFI_PERFORMANCE]")
#define INI_STR_WIFI_CERTIFY            ("[HOST_WIFI_CERTIFY]")
#define INI_STR_WIFI_CERTIFY_CE         ("[HOST_WIFI_CERTIFY_CE_ENHANCE]")
#define INI_STR_GNSS_GPSGLONASS         ("[HOST_GNSS_GPSGLONASS]")
#define INI_STR_GNSS_BDGPS              ("[HOST_GNSS_BDGPS]")
#define INI_STR_BT_NORMAL               ("[HOST_BT_NORMAL]")
#define INI_STR_FM_NORMAL               ("[HOST_FM_NORMAL]")
#define INI_STR_WIFI_PLAT_NORMAL        ("[HOST_WIFI_PLAT_NORMAL]")
#define INI_STR_BFG_PLAT_NORMAL         ("[HOST_BFG_PLAT_NORMAL]")
#define INI_STR_PLAT                    ("[HOST_PLAT]")
#define INI_STR_WIFI_MAC                ("[HOST_WIFI_MAC]")
#define INT_STR_HOST_VERSION            ("[HOST_VERSION]")
#define INI_STR_COEXIST                 ("[HOST_COEXIST]")
#define INI_STR_DEVICE_BFG_PLAT         ("[DEVICE_BFG_PLAT]")
#define INI_INIT_MUTEX(mutex)           mutex_init(mutex)
#define INI_MUTEX_LOCK(mutex)           mutex_lock(mutex)
#define INI_MUTEX_UNLOCK(mutex)         mutex_unlock(mutex)

#else

#define INI_SDIOBIN_DEFAULT             ("/system/vendor/firmware/SDIO_RW.bin")
#define INI_SDIOBIN_NORMAL              ("/system/vendor/firmware/SDIO_RW_Normal.bin")
#define INI_SDIOBIN_PERFORMANCE         ("/system/vendor/firmware/SDIO_RW_Performance.bin")
#define INI_SDIOBIN_CERTIFY             ("/system/vendor/firmware/SDIO_RW_Certification.bin")

#define INI_STR_WIFI_NORMAL             ("[HOST_WIFI_NORMAL]")
#define INI_STR_WIFI_PERFORMANCE        ("[HOST_WIFI_PERFORMANCE]")
#define INI_STR_WIFI_CERTIFY            ("[HOST_WIFI_CERTIFY]")
#define INI_STR_WIFI_CERTIFY_CE         ("[HOST_WIFI_CERTIFY_CE_ENHANCE]")
#define INI_STR_GNSS_GPSGLONASS         ("[HOST_GNSS_GPSGLONASS]")
#define INI_STR_GNSS_BDGPS              ("[HOST_GNSS_BDGPS]")
#define INI_STR_BT_NORMAL               ("[HOST_BT_NORMAL]")
#define INI_STR_FM_NORMAL               ("[HOST_FM_NORMAL]")
#define INI_STR_WIFI_PLAT_NORMAL        ("[HOST_WIFI_PLAT_NORMAL]")
#define INI_STR_BFG_PLAT_NORMAL         ("[HOST_BFG_PLAT_NORMAL]")
#define INI_STR_PLAT                    ("[HOST_PLAT]")
#define INI_STR_WIFI_MAC                ("[HOST_WIFI_MAC]")
#define INT_STR_HOST_VERSION            ("[HOST_VERSION]")
#define INI_STR_COEXIST                 ("[HOST_COEXIST]")
#define INI_STR_DEVICE_BFG_PLAT         ("[DEVICE_BFG_PLAT]")
#define INI_INIT_MUTEX(mutex, para)     pthread_mutex_init(mutex, para)
#define INI_MUTEX_LOCK(mutex)           pthread_mutex_lock(mutex)
#define INI_MUTEX_UNLOCK(mutex)         pthread_mutex_unlock(mutex)

#endif

#define INI_STR_MODU_LEN        (40)

#define INI_MODE_GPSGLONASS     (0)
#define INI_MODE_BDGPS          (1)
#define INI_MODE_NORMAL         (0)
#define INI_MODE_PERFORMANCE    (1)
#define INI_MODE_CERTIFY        (2)
#define INI_MODE_CERTIFY_CE     (3)

#define MAX_READ_LINE_NUM       (192)
#define INI_FILE_PATH_LEN       (128)
#define INI_READ_VALUE_LEN      (64)
#define INI_VERSION_STR_LEN     (32)

#define INI_SUCC_MODE_VAR       (1)
#define INI_SUCC                (0)
#define INI_FAILED              (-1)
/*Hi1101 and Hi1151 version micro definition*/

/*
 * 4 Message Header Definition
 */


/*
 * 5 Message Definition
 */


/*
 * 6 STRUCT Type Definition
 */

#ifdef INI_KO_MODULE
typedef struct ini_board_vervion
{
	unsigned char board_version[INI_VERSION_STR_LEN];
}INI_BOARD_VERSION_STRU;

typedef struct ini_param_vervion
{
	unsigned char param_version[INI_VERSION_STR_LEN];
}INI_PARAM_VERSION_STRU;
typedef struct file INI_FILE;

/*
 * 7 Global Variable Declaring
 */
extern char g_ini_file_name[INI_FILE_PATH_LEN];
extern INI_BOARD_VERSION_STRU g_board_version;
extern INI_PARAM_VERSION_STRU g_param_version;
#endif
/*
 * 8 UNION Type Definition
 */


/*
 * 9 OTHERS Definition
 */


/*
 * 10 Function Declare
 */

#ifdef INI_KO_MODULE
extern int32 ini_find_var_value(int32 modu, int8 * puc_var, int8 *puc_value, uint32 size);
extern int32 get_cust_conf_int32(int32 modu, int8 * puc_var, int32 *pul_value);
extern int32 get_cust_conf_string(int32 modu, int8* puc_var, int8 *puc_value, uint32 size);
extern int32 set_cust_conf_string(int32 modu, int8 * puc_var, int8 *pc_value);
extern int32 board_ini_find_modu(INI_FILE *fp);
extern int32 board_ini_find_var(INI_FILE *fp, int8 * puc_var, uint32 *pul_value);
extern int32 ini_cfg_init(void);
extern void ini_cfg_exit(void);
#else
extern int32 ini_find_var_value(int32 modu, int8 *puc_var, int8 *puc_value);
extern int32 get_cust_conf_int32(int32 modu, int8 *puc_var, int32 *pul_value);
extern int32 set_cust_conf_string(int32 modu, int8 * puc_var, int8 *pc_value);
extern int32 get_cust_conf_string(int32 modu, int8 *puc_var, int8 *puc_value);
extern int32 get_run_mode(void);
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif
