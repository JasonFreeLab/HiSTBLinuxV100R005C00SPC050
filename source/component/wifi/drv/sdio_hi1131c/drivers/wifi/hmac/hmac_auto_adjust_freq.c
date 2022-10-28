/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��˼�뵼�����޹�˾

 ******************************************************************************
  �� �� ��   : hmac_auto_adjust_freq.c
  �� �� ��   : ����
  ��    ��   : wangtd
  ��������   : 2015��3��4��
  ����޸�   :
  ��������   : ����ά��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��4��
    ��    ��   : Wlan_mib_temp
    �޸�����   : �����ļ�
  2.��    ��   : 2015��8��15��
    ��    ��   : 
    �޸�����   : ����thruput bypass TX����ά���
******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "oal_net.h"
#include "oal_types.h"
#include "oam_ext_if.h"
#include  "mac_vap.h"
#include  "mac_resource.h"
#include  "hmac_vap.h"
#include  "hmac_auto_adjust_freq.h"
#include  "hmac_ext_if.h"
#include  "hmac_blockack.h"

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)&&(_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
#include "plat_pm_wlan.h"
#endif

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
#include <linux/pm_qos.h>
#endif


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_MAC_AUTO_ADJUST_FREQ_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
#ifndef WIN32
OAL_STATIC oal_uint32 pre_jiffies            = 0;
OAL_STATIC oal_uint32 g_adjust_count            = 0;

/*�ɶ��ƻ����г�ʼ��*/
host_speed_freq_level_stru g_host_speed_freq_level[] = {
    /*pps����                   CPU��Ƶ����                     DDR��Ƶ����*/
    {PPS_VALUE_0,          CPU_MIN_FREQ_VALUE_0,            DDR_MIN_FREQ_VALUE_0},
    {PPS_VALUE_1,          CPU_MIN_FREQ_VALUE_1,            DDR_MIN_FREQ_VALUE_1},
    {PPS_VALUE_2,          CPU_MIN_FREQ_VALUE_2,            DDR_MIN_FREQ_VALUE_2},
    {PPS_VALUE_3,          CPU_MIN_FREQ_VALUE_3,            DDR_MIN_FREQ_VALUE_3},
};
host_speed_freq_level_stru g_host_no_ba_freq_level[] = {
    /*pps����                        CPU��Ƶ����                      DDR��Ƶ����*/
    {NO_BA_PPS_VALUE_0,          CPU_MIN_FREQ_VALUE_0,            DDR_MIN_FREQ_VALUE_0},
    {NO_BA_PPS_VALUE_1,          CPU_MIN_FREQ_VALUE_1,            DDR_MIN_FREQ_VALUE_1},
    {NO_BA_PPS_VALUE_2,          CPU_MIN_FREQ_VALUE_2,            DDR_MIN_FREQ_VALUE_2},
    {NO_BA_PPS_VALUE_3,          CPU_MIN_FREQ_VALUE_2,            DDR_MIN_FREQ_VALUE_2},
};
device_speed_freq_level_stru g_device_speed_freq_level[] = {
    /*device��Ƶ����*/
    {FREQ_IDLE},
    {FREQ_MIDIUM},
    {FREQ_HIGHER},
    {FREQ_HIGHEST},
};

struct pm_qos_request *g_pst_wifi_auto_ddr = NULL;


OAL_STATIC freq_lock_control_stru g_freq_lock_control = {0};
OAL_STATIC oal_uint32 g_ul_wifi_rxtx_total          = 0;

OAL_STATIC oal_uint32 g_ul_orig_cpu_min_freq       = 0;
OAL_STATIC oal_uint32 g_ul_orig_cpu_max_freq       = 0;
OAL_STATIC oal_uint32 g_ul_orig_ddr_min_freq       = 0;
OAL_STATIC oal_uint32 g_ul_orig_ddr_max_freq       = 0;
#else
oal_uint32 pre_jiffies;

host_speed_freq_level_stru g_host_speed_freq_level[] = {
    /*pps����                   CPU��Ƶ����                     DDR��Ƶ����*/
    {PPS_VALUE_0,          CPU_MIN_FREQ_VALUE_0,            DDR_MIN_FREQ_VALUE_0},
    {PPS_VALUE_1,          CPU_MIN_FREQ_VALUE_1,            DDR_MIN_FREQ_VALUE_1},
    {PPS_VALUE_2,          CPU_MIN_FREQ_VALUE_2,            DDR_MIN_FREQ_VALUE_2},
    {PPS_VALUE_3,          CPU_MIN_FREQ_VALUE_3,            DDR_MIN_FREQ_VALUE_3},
};
device_speed_freq_level_stru g_device_speed_freq_level[] = {
    /*device��Ƶ����*/
    {FREQ_IDLE},
    {FREQ_MIDIUM},
    {FREQ_HIGHEST},
    {FREQ_HIGHEST},
};

freq_lock_control_stru g_freq_lock_control;
oal_uint32 g_ul_wifi_rxtx_total;

oal_uint32 g_ul_orig_cpu_min_freq;
oal_uint32 g_ul_orig_cpu_max_freq;
oal_uint32 g_ul_orig_ddr_min_freq;
oal_uint32 g_ul_orig_ddr_max_freq;
#endif
#ifdef WIN32
#define mutex_init(mux)
#define mutex_lock(mux)
#define mutex_unlock(mux)
#define spin_lock_init(mux)
#define mutex_destroy(mux)
#define spin_unlock_bh(mux)
#endif

/*****************************************************************************
 �� �� ��  : hmac_set_auto_freq_mod
 ��������  : ����auto freqʹ��
 �������  : oal_uint8 uc_freq_type
             oal_uint32 * pst_freq_value
 �������  : ��
 �� �� ֵ  : OAL_STATIC OAL_INLINE oal_bool_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��14��
    ��    ��   :  
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint8 hmac_set_auto_freq_mod(oal_uint8 uc_freq_enable)
{
    if(g_freq_lock_control.uc_lock_mod == uc_freq_enable)
    {
        OAM_WARNING_LOG1(0, OAM_SF_CFG, "{hmac_set_auto_freq_mod, set the same value[%d]}", uc_freq_enable);
        return OAL_SUCC;
    }

    g_freq_lock_control.uc_lock_mod = uc_freq_enable;
    if(FREQ_LOCK_ENABLE == uc_freq_enable)
    {
        OAM_WARNING_LOG2(0,OAM_SF_CFG,"{hmac_set_auto_freq_mod  set host enable[%d], set device enable level[%d]}",g_freq_lock_control.uc_lock_mod, g_freq_lock_control.uc_curr_lock_level);

        hmac_set_device_freq(g_freq_lock_control.uc_curr_lock_level);
    }
    else
    {
        OAM_WARNING_LOG2(0,OAM_SF_CFG,"{hmac_set_auto_freq_mod  set host enable[%d], set device diable level[%d]}",g_freq_lock_control.uc_lock_mod, FREQ_HIGHEST);

        hmac_set_device_freq(FREQ_HIGHEST);
    }
    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : hmac_set_auto_freq_debug_print
 ��������  : ����auto freqʹ��
 �������  : oal_uint8 uc_freq_type
             oal_uint32 * pst_freq_value
 �������  : ��
 �� �� ֵ  : OAL_STATIC OAL_INLINE oal_bool_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��14��
    ��    ��   :  
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum_uint8 hmac_set_auto_freq_debug_print(oal_bool_enum_uint8 en_debug_print)
{
    OAM_WARNING_LOG1(0,OAM_SF_ANY,"{hmac_set_auto_freq_debug_print en_debug_print = %d!}",g_freq_lock_control.en_debug_print);
    g_freq_lock_control.en_debug_print = en_debug_print;
    return 0;
}
/*****************************************************************************
 �� �� ��  : hmac_set_auto_freq_bypass_device_auto_freq
 ��������  : ����auto freqʹ��
 �������  : oal_uint8 uc_freq_type
             oal_uint32 * pst_freq_value
 �������  : ��
 �� �� ֵ  : OAL_STATIC OAL_INLINE oal_bool_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��14��
    ��    ��   :  
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum_uint8 hmac_set_auto_freq_bypass_device_auto_freq(oal_bool_enum_uint8 en_bypass_device)
{
    OAM_WARNING_LOG1(0,OAM_SF_ANY,"{hmac_set_auto_freq_debug_print en_bypass_device_freq = %d!}",g_freq_lock_control.en_bypass_device_freq);
    g_freq_lock_control.en_bypass_device_freq = en_bypass_device;
    return 0;
}
/*****************************************************************************
 �� �� ��  : hmac_set_auto_freq_process_func
 ��������  : ����hcc���Զ���Ƶ�Ļص�����
 �������  : hmac_auto_freq_process_func p_func
 �������  : ��
 �� �� ֵ  : oal_int32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��18��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_int32 hmac_set_auto_freq_process_func(oal_void)
{
    struct alg_process_func_handler* pst_alg_process_func_handler;

    g_freq_lock_control.uc_lock_mod = FREQ_LOCK_DISABLE;
    g_freq_lock_control.en_debug_print = OAL_FALSE;
    g_freq_lock_control.en_bypass_device_freq = OAL_FALSE;
    g_freq_lock_control.uc_curr_lock_level = 0;
    pst_alg_process_func_handler = oal_get_alg_process_func();
    if(OAL_PTR_NULL == pst_alg_process_func_handler)
    {
        OAM_ERROR_LOG0(0,OAM_SF_ANY,"{hmac_set_auto_freq_process_func get handler failed!}");
    }
    else
    {
        pst_alg_process_func_handler->p_auto_freq_count_func = hmac_hcc_auto_freq_count;
        pst_alg_process_func_handler->p_auto_freq_process_func = hmac_hcc_auto_freq_process;
        pst_alg_process_func_handler->p_auto_freq_set_lock_mod_func = hmac_set_auto_freq_mod;
        pst_alg_process_func_handler->p_auto_freq_adjust_to_level_func = hmac_adjust_freq_to_level;
    }

    return OAL_SUCC;
}

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
/*****************************************************************************
 �� �� ��  : hmac_get_cpu_freq_raw
 ��������  : ��ȡCPU��Ƶֵ
 �������  : oal_uint8 uc_freq_type
             oal_uint32 * pst_freq_value
 �������  : ��
 �� �� ֵ  : OAL_STATIC OAL_INLINE oal_bool_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��14��
    ��    ��   :  
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8 hmac_get_cpu_freq_raw(oal_uint8 uc_freq_type, oal_uint32 * pst_ul_freq_value)
{
    struct file* filp = NULL;
    mm_segment_t old_fs;
    oal_int8 buf[12] = {0};

    if (uc_freq_type == SCALING_MAX_FREQ)
        filp = filp_open(CPU_MAX_FREQ, O_RDONLY, 0);
    else if (uc_freq_type == SCALING_MIN_FREQ)
        filp = filp_open(CPU_MIN_FREQ, O_RDONLY, 0);
    else
        return -1;

    if (IS_ERR_OR_NULL(filp))
    {
        OAM_ERROR_LOG1(0,OAM_SF_ANY,"{hmac_get_cpu_freq_raw:��freq��= %d error !}",uc_freq_type);
        return -1;
    }
    old_fs = get_fs();
    set_fs(KERNEL_DS);
    filp->f_pos = 0;
    filp->f_op->read(filp, buf, 12, &filp->f_pos);
    filp_close(filp, NULL);
    set_fs(old_fs);

    if (kstrtouint(buf, 10, pst_ul_freq_value) != 0)
    {
        OAM_ERROR_LOG0(0,OAM_SF_ANY,"{error to get cpu freq !}");
        return -1;
    }

    return 0;
}

/*****************************************************************************
 �� �� ��  : hmac_get_cpu_freq_raw
 ��������  : ����CPU��Ƶֵ
 �������  : oal_uint8 uc_freq_type
             oal_uint32 * pst_freq_value
 �������  : ��
 �� �� ֵ  : OAL_STATIC OAL_INLINE oal_bool_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��14��
    ��    ��   :  
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum_uint8 hmac_set_cpu_freq_raw(oal_uint8 uc_freq_type, oal_uint32 ul_freq_value)
{
    struct file* filp = NULL;
    mm_segment_t old_fs;
    oal_int8 buf[12] = {0};

    snprintf(buf, 12, "%d", ul_freq_value);

    if (uc_freq_type == SCALING_MIN_FREQ)
        filp = filp_open(CPU_MIN_FREQ, O_RDWR, 0);
    else if (uc_freq_type == SCALING_MAX_FREQ)
        filp = filp_open(CPU_MAX_FREQ, O_RDWR, 0);
    else
        return -1;

    if (IS_ERR_OR_NULL(filp))
    {
        OAM_ERROR_LOG1(0,OAM_SF_ANY,"{hmac_set_cpu_freq_raw:��freq��= %d error !}",ul_freq_value);
        return -1;
    }
    old_fs = get_fs();
    set_fs(KERNEL_DS);
    filp->f_pos = 0;
    filp->f_op->write(filp, buf, 12, &filp->f_pos);
    filp_close(filp, NULL);
    set_fs(old_fs);

    return 0;
}


/*****************************************************************************
 �� �� ��  : hmac_get_ddr_freq_raw
 ��������  : ��ȡDDR��Ƶֵ
 �������  : oal_uint8 uc_freq_type
             oal_uint32* ul_freq_value
 �������  : ��
 �� �� ֵ  : OAL_STATIC OAL_INLINE oal_bool_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��14��
    ��    ��   :  
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8 hmac_get_ddr_freq_raw(oal_uint8 uc_freq_type, oal_uint32 * pst_ul_freq_value)
{
    struct file* filp = NULL;
    mm_segment_t old_fs;
    oal_int8 buf[12] = {0};

    if (uc_freq_type == SCALING_MAX_FREQ)
        filp = filp_open(DDR_MAX_FREQ, O_RDONLY, 0);
    else if (uc_freq_type == SCALING_MIN_FREQ)
        filp = filp_open(DDR_MIN_FREQ, O_RDONLY, 0);
    else
        return -1;

    if (IS_ERR_OR_NULL(filp))
    {
        OAM_ERROR_LOG1(0,OAM_SF_ANY,"{hmac_get_ddr_freq_raw:��freq��= %d error !}",uc_freq_type);
        return -1;
    }
    old_fs = get_fs();
    set_fs(KERNEL_DS);
    filp->f_pos = 0;
    filp->f_op->read(filp, buf, 12, &filp->f_pos);
    filp_close(filp, NULL);
    set_fs(old_fs);

    if (kstrtouint(buf, 10, pst_ul_freq_value) != 0)
    {
        printk("error to get cpu freq\n");
        return -1;
    }

    return 0;
}


/*****************************************************************************
 �� �� ��  : hmac_set_ddr_freq_raw
 ��������  : ����DDR��Ƶֵ
 �������  : oal_uint8 uc_freq_type
             oal_uint32 ul_freq_value
 �������  : ��
 �� �� ֵ  : OAL_STATIC OAL_INLINE oal_bool_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��14��
    ��    ��   :  
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum_uint8 hmac_set_ddr_freq_raw(oal_uint8 uc_freq_type, oal_uint32 ul_freq_value)
{
#if 0
    struct file* filp = NULL;
    mm_segment_t old_fs;
    char buf[12] = {0};

    snprintf(buf, 12, "%d", ul_freq_value);

    if (uc_freq_type == SCALING_MIN_FREQ)
        filp = filp_open(DDR_MIN_FREQ, O_RDWR, 0);
    else if (uc_freq_type == SCALING_MAX_FREQ)
        filp = filp_open(DDR_MAX_FREQ, O_RDWR, 0);
    else
        return -1;

    if (IS_ERR_OR_NULL(filp))
    {
        OAM_ERROR_LOG1(0,OAM_SF_ANY,"{hmac_set_ddr_freq_raw:��freq��= %d error !}",ul_freq_value);
        return -1;
    }
    old_fs = get_fs();
    set_fs(KERNEL_DS);
    filp->f_pos = 0;
    filp->f_op->write(filp, buf, 12, &filp->f_pos);
    filp_close(filp, NULL);
    set_fs(old_fs);
#else
/* HI1131C modify begin */
#if defined(CONFIG_ARCH_HI3798MV2X) || defined(CONFIG_ARCH_HI3798MV310)
    /*HI3798MV2X don't support android lower power*/
#else
    pm_qos_update_request(g_pst_wifi_auto_ddr, ul_freq_value);
#endif
#endif
    return 0;
}
#endif
oal_void hmac_adjust_freq_to_level(oal_void)
{
    oal_uint8 uc_req_lock_level = g_freq_lock_control.uc_req_lock_level;

    OAM_WARNING_LOG1(0,OAM_SF_PWR,"{hmac_adjust_freq_to_level[%d]}",uc_req_lock_level);

    if(hmac_is_device_ba_setup())
    {
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
        hmac_set_cpu_freq_raw(SCALING_MIN_FREQ,g_host_speed_freq_level[uc_req_lock_level].ul_min_cpu_freq);
        hmac_set_ddr_freq_raw(SCALING_MIN_FREQ,g_host_speed_freq_level[uc_req_lock_level].ul_min_ddr_freq);
#endif
    }
    else
    {
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
        hmac_set_cpu_freq_raw(SCALING_MIN_FREQ,g_host_no_ba_freq_level[uc_req_lock_level].ul_min_cpu_freq);
        hmac_set_ddr_freq_raw(SCALING_MIN_FREQ,g_host_no_ba_freq_level[uc_req_lock_level].ul_min_ddr_freq);
#endif

    }
    if (OAL_FALSE == g_freq_lock_control.en_bypass_device_freq)
    {
        hmac_set_device_freq(g_device_speed_freq_level[uc_req_lock_level].uc_device_type);
    }

    g_freq_lock_control.uc_curr_lock_level = uc_req_lock_level;
}

/*****************************************************************************
 �� �� ��  : hwifi_perform_calc_rwtotal_throughput
 ��������  : ͳ��SDIO����������(�����շ�)��������
             ����SDIO����շ�����
 �޸���ʷ      :
  1.��    ��   : 2013��8��14��
    ��    ��   : �Ż� 
    �޸�����   : �����ɺ���

*****************************************************************************/
void hmac_perform_calc_rwtotal_throughput(oal_uint32 ul_rxtx_total,oal_uint32 ul_sdio_dur_us)
{
    if(0 != ul_sdio_dur_us)
    {
        g_freq_lock_control.ul_total_sdio_rate = (ul_rxtx_total*1000)/ul_sdio_dur_us;

        if(OAL_TRUE == g_freq_lock_control.en_debug_print)
        {
            OAM_WARNING_LOG4(0,OAM_SF_ANY,"{SDIO perform tx statistic: packet_rate = %lu pps, sumlen = %lu B, [use time] = %lu ms,g_adjust_count = %d!}",
                g_freq_lock_control.ul_total_sdio_rate , ul_rxtx_total, ul_sdio_dur_us,g_adjust_count);
        }
    }
}
oal_uint8 hmac_get_freq_level(oal_uint32 ul_speed)
{
    oal_uint8 level_idx;

    if(hmac_is_device_ba_setup())
    {
        if (ul_speed <= g_host_speed_freq_level[1].ul_speed_level)
        {
            level_idx = 0;
        }
        else if ((ul_speed > g_host_speed_freq_level[1].ul_speed_level)
            && (ul_speed <= g_host_speed_freq_level[2].ul_speed_level))
        {
            level_idx = 1;
        }
        else if ((ul_speed > g_host_speed_freq_level[2].ul_speed_level)
            && (ul_speed <= g_host_speed_freq_level[3].ul_speed_level))
        {
            level_idx = 2;
        }
        else
        {
            level_idx = 3;
        }
    }
    else
    {
        if (ul_speed <= g_host_no_ba_freq_level[1].ul_speed_level)
        {
            level_idx = 0;
        }
        else if ((ul_speed > g_host_no_ba_freq_level[1].ul_speed_level)
            && (ul_speed <= g_host_no_ba_freq_level[2].ul_speed_level))
        {
            level_idx = 1;
        }
        else if ((ul_speed > g_host_no_ba_freq_level[2].ul_speed_level)
            && (ul_speed <= g_host_no_ba_freq_level[3].ul_speed_level))
        {
            level_idx = 2;
        }
        else
        {
            level_idx = 3;
        }
    }
    return level_idx;
}

oal_void hmac_adjust_freq(oal_void)
{
    oal_uint8 uc_req_lock_level = 0;
    oal_uint32         ul_cur_jiffies;
    oal_uint32         ul_sdio_dur_us;

    ul_cur_jiffies = jiffies;
    ul_sdio_dur_us = OAL_JIFFIES_TO_MSECS(ul_cur_jiffies - pre_jiffies);
    pre_jiffies = ul_cur_jiffies;

    /*�����Ƶ����*/
    hmac_perform_calc_rwtotal_throughput(g_ul_wifi_rxtx_total,ul_sdio_dur_us);
    g_freq_lock_control.uc_req_lock_level = hmac_get_freq_level(g_freq_lock_control.ul_total_sdio_rate);

    uc_req_lock_level = g_freq_lock_control.uc_req_lock_level;
    if (uc_req_lock_level != g_freq_lock_control.uc_curr_lock_level)
    {
        mutex_lock(&g_freq_lock_control.st_lock_freq_mtx);

        if (uc_req_lock_level != g_freq_lock_control.uc_curr_lock_level)
        {
            if(uc_req_lock_level < g_freq_lock_control.uc_curr_lock_level)
            {
                /*����MAX_DEGRADE_FREQ_TIME_THRESHOLD��Ž�Ƶ����֤����*/
                g_adjust_count++;
                if(0 != g_ul_wifi_rxtx_total)
                {
                    if(g_adjust_count >= MAX_DEGRADE_FREQ_COUNT_THRESHOLD_SUCCESSIVE_10)
                    {
                        g_adjust_count = 0;
                        wlan_pm_adjust_feq();
                    }
                }
                else
                {
                    if(g_adjust_count >= MAX_DEGRADE_FREQ_COUNT_THRESHOLD_SUCCESSIVE_2)
                    {
                        g_adjust_count = 0;
                        wlan_pm_adjust_feq();
                    }
                }
            }
            else
            {
                /*��Ƶ���ȴ�������ִ�б�֤����*/
                g_adjust_count = 0;
                wlan_pm_adjust_feq();
            }
        }
        else
        {
            g_adjust_count = 0;
        }

        mutex_unlock(&g_freq_lock_control.st_lock_freq_mtx);
    }
    else
    {
        g_adjust_count = 0;
    }
}
/*****************************************************************************
 �� �� ��  : hmac_wifi_init_freq_threshold
 ��������  : ��ʼ������ֵ,�Ͷ��ƻ��ӿ�
 �������  : void
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��17��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void hmac_wifi_init_freq_threshold(void)
{
}

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
oal_void hmac_wifi_auto_ddr_init(oal_void)
{
    g_pst_wifi_auto_ddr = kmalloc(sizeof(struct pm_qos_request), GFP_KERNEL);
    if (g_pst_wifi_auto_ddr == NULL)
    {
        OAL_IO_PRINT("[AUTODDR]pm_qos_request alloc memory failed.\n");
        return;
    }
    g_pst_wifi_auto_ddr->pm_qos_class = 0;
/* HI1131C modify begin */
#if defined(CONFIG_ARCH_HI3798MV2X) || defined(CONFIG_ARCH_HI3798MV310)
    /*HI3798MV2X don't support android lower power*/
#else
    pm_qos_add_request(g_pst_wifi_auto_ddr, PM_QOS_MEMORY_THROUGHPUT,
                       PM_QOS_MEMORY_THROUGHPUT_DEFAULT_VALUE);
#endif
/* HI1131C modify end */
    return;
}
oal_void hmac_wifi_auto_ddr_exit(oal_void)
{
    /* HI1131C modify begin */
#if defined(CONFIG_ARCH_HI3798MV2X) || defined(CONFIG_ARCH_HI3798MV310)
        /*HI3798MV2X don't support android lower power*/
#else
    pm_qos_remove_request(g_pst_wifi_auto_ddr);
#endif
   /* HI1131C modify end */

    kfree(g_pst_wifi_auto_ddr);
    g_pst_wifi_auto_ddr = NULL;
}
#endif
/*****************************************************************************
 �� �� ��  : hmac_wifi_auto_freq_ctrl_init
 ��������  : ��Ƶģ���ʼ��
 �������  : void
 �������  : ��
 �� �� ֵ  : oal_bool_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��14��
    ��    ��   :  
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void hmac_wifi_auto_freq_ctrl_init(void)
{
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    if(OAL_TRUE != g_freq_lock_control.en_is_inited)
    {
        OAM_WARNING_LOG0(0,OAM_SF_ANY,"{hmac_wifi_auto_freq_ctrl_init enter!}");

        mutex_init(&g_freq_lock_control.st_lock_freq_mtx);

        mutex_lock(&g_freq_lock_control.st_lock_freq_mtx);

        pre_jiffies = jiffies;
        g_freq_lock_control.uc_lock_mod = FREQ_LOCK_DISABLE;
        g_freq_lock_control.uc_curr_lock_level = FREQ_IDLE;
        hmac_get_cpu_freq_raw(SCALING_MIN_FREQ, &g_ul_orig_cpu_min_freq);
        hmac_get_cpu_freq_raw(SCALING_MAX_FREQ, &g_ul_orig_cpu_max_freq);
#if 0
        hmac_get_ddr_freq_raw(SCALING_MIN_FREQ, &g_ul_orig_ddr_min_freq);
        hmac_get_ddr_freq_raw(SCALING_MAX_FREQ, &g_ul_orig_ddr_max_freq);
#else
        hmac_wifi_auto_ddr_init();
#endif
        hmac_wifi_init_freq_threshold();
        OAM_WARNING_LOG4(0,OAM_SF_ANY,"{hmac_wifi_auto_freq_ctrl_init g_ul_orig_cpu_min_freq = %d,g_ul_orig_cpu_max_freq = %d,g_ul_orig_ddr_max_freq = %d,g_ul_orig_ddr_max_freq = %d}",
            g_ul_orig_cpu_min_freq,g_ul_orig_cpu_max_freq,g_ul_orig_ddr_min_freq,g_ul_orig_ddr_max_freq);
        g_freq_lock_control.en_is_inited = OAL_TRUE;
        mutex_unlock(&g_freq_lock_control.st_lock_freq_mtx);
    }
#endif
}
/*****************************************************************************
 �� �� ��  : hmac_wifi_auto_freq_ctrl_deinit
 ��������  : ��Ƶģ��ȥ��ʼ��
 �������  : void
 �������  : ��
 �� �� ֵ  : oal_bool_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��14��
    ��    ��   :  
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void hmac_wifi_auto_freq_ctrl_deinit(void)
{
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    OAM_WARNING_LOG0(0,OAM_SF_ANY,"{hmac_wifi_auto_freq_ctrl_deinit enter!}");
    mutex_lock(&g_freq_lock_control.st_lock_freq_mtx);
    if (FREQ_LOCK_ENABLE == g_freq_lock_control.uc_lock_mod)
    {
        hmac_set_cpu_freq_raw(SCALING_MIN_FREQ, g_ul_orig_cpu_min_freq);
        hmac_set_cpu_freq_raw(SCALING_MAX_FREQ, g_ul_orig_cpu_max_freq);
#if 0
        hmac_set_ddr_freq_raw(SCALING_MIN_FREQ, g_ul_orig_ddr_min_freq);
        hmac_set_ddr_freq_raw(SCALING_MAX_FREQ, g_ul_orig_ddr_max_freq);
#else
#endif
        hmac_set_device_freq(FREQ_IDLE);
        OAM_WARNING_LOG0(0,OAM_SF_ANY,"{hw_wifi_freq_ctrl_destroy freq lock release here!}");
    }
    else
    {
        OAM_WARNING_LOG0(0,OAM_SF_ANY,"{hw_wifi_freq_ctrl_destroy freq lock has already been released!}");
    }
    g_freq_lock_control.uc_lock_mod = FREQ_LOCK_DISABLE;
    g_freq_lock_control.uc_curr_lock_level = 0;
#if 1
    hmac_wifi_auto_ddr_exit();
#endif

    mutex_unlock(&g_freq_lock_control.st_lock_freq_mtx);
    mutex_destroy(&g_freq_lock_control.st_lock_freq_mtx);
#endif
}
oal_uint32 hmac_wifi_tx_rx_counter(oal_uint32 ul_pkt_count)
{
    g_ul_wifi_rxtx_total = g_ul_wifi_rxtx_total + ul_pkt_count;
#if 0
    OAM_WARNING_LOG2(0,OAM_SF_ANY,"{hmac_wifi_tx_rx_counter, ul_pkt_count = %d, g_ul_wifi_rxtx_total = %d!}",ul_pkt_count,g_ul_wifi_rxtx_total);
#endif

    return 0;
}
oal_void hmac_hcc_auto_freq_count(oal_uint32 ul_pkt_count)
{
    g_ul_wifi_rxtx_total = g_ul_wifi_rxtx_total + ul_pkt_count;
#if 0
    OAM_WARNING_LOG2(0,OAM_SF_ANY,"{hmac_hcc_auto_freq_count, ul_pkt_count = %d, g_ul_wifi_rxtx_total = %d!}",ul_pkt_count,g_ul_wifi_rxtx_total);
#endif

}
oal_uint32 hmac_hcc_auto_freq_process(oal_void)
{
    oal_uint32 ul_return_total_count = 0;

    /*����֮ǰ��ֵ�����ظ�ƽ̨*/
    ul_return_total_count = g_ul_wifi_rxtx_total;
    if(FREQ_LOCK_ENABLE == g_freq_lock_control.uc_lock_mod)
    {
        hmac_adjust_freq();
    }
    g_ul_wifi_rxtx_total = 0;
    return ul_return_total_count;
}


#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

