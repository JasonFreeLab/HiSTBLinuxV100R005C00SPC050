/******************************************************************************

          Copyright (C), 2001-2011, Hisilicon technology limited company

 ******************************************************************************
  Filename   : board.h
  Version    : first draft
  Author     : 
  Create date: 2015/04/08
  Modify     :
  Func descr : inclue file
  Func list  :
  Modi histoy:
  1.Data     : 2015/04/08
    Author   : 
    Modify
    content  : Create File

******************************************************************************/

#ifndef __ONEIMAGE_H__
#define __ONEIMAGE_H__
/*****************************************************************************
  1 Include other Head file
*****************************************************************************/

/*****************************************************************************
  2 Define macro
*****************************************************************************/
#define DTS_COMP_HW_CONNECTIVITY_NAME           "hisilicon,hisi_wifi"
/* 2015-12-15 modify by  for nfc one image beg */
//#define DTS_COMP_HISI_NFC_NAME                  "hisilicon,hisi_bfgx"
#define DTS_COMP_HISI_NFC_NAME                  "hisilicon,hisi_nfc"
/* 2015-12-15 modify by  for nfc one image end */

#define DTS_COMP_HW_HISI_SUPP_CONFIG_NAME       "hisi,wifi_supp"
#define DTS_COMP_HW_HISI_P2P_CONFIG_NAME        "hisi,wifi_p2p"
#define DTS_COMP_HW_HISI_HOSTAPD_CONFIG_NAME    "hisi,wifi_hostapd"
#define DTS_COMP_HW_HISI_FIRMWARE_CONFIG_NAME   "hisi,wifi_firmware"

/* 2015-12-15 modify by  for nfc one image beg */
//#define DTS_COMP_HW_HISI_NFC_CONFIG_NAME        "nfc_hisi_name"
//#define DTS_COMP_HW_BRCM_NFC_CONFIG_NAME        "nfc_brcm_conf_name"
#define DTS_COMP_HW_HISI_NFC_CONFIG_NAME        "nfc_hisi_conf_name"
#define DTS_COMP_HW_BRCM_NFC_CONFIG_NAME        "nfc_default_hisi_conf_name"
/* 2015-12-15 modify by  for nfc one image end */

#define PROC_CONN_DIR    "/proc/connectivity"

#define HW_CONN_PROC_DIR "connectivity"

//#define ONEIMAGE_NAME               "oneimage"
#define HW_CONN_PROC_CHIPTYPE_FILE  "chiptype"
#define HW_CONN_PROC_SUPP_FILE      "supp_config_template"
#define HW_CONN_PROC_P2P_FILE       "p2p_config_template"
#define HW_CONN_PROC_HOSTAPD_FILE   "hostapd_bin_file"
#define HW_CONN_PROC_FRIMWARE       "firmware_type_num"

#define BUFF_LEN       (129)
#define NODE_PATH_LEN  (256)
/*****************************************************************************
  3 STRUCT DEFINE
*****************************************************************************/
typedef struct hisi_proc_info {
    int     proc_type;
    char*   proc_node_name;
    char*   proc_pro_name;
}HISI_PROC_INFO_STRU;

typedef enum proc_enum
{
    HW_PROC_CHIPTYPE = 0,
    HW_PROC_SUPP,
    HW_PROC_P2P,
    HW_PROC_HOSTAPD,
    HW_PROC_FIRMWARE,
    HW_PROC_BUTT,
}HISI_PROC_ENUM;

/*****************************************************************************
  4 EXTERN VARIABLE
*****************************************************************************/

/*****************************************************************************
  5 EXTERN FUNCTION
*****************************************************************************/
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
extern bool is_my_chip(void);
extern bool is_my_nfc_chip(void);
extern int read_nfc_conf_name_from_dts(char *buf, int buf_len, char *node_name, char *property_name);
#endif
#endif

