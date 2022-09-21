

#ifndef __MALI4XX_CFG__
#define __MALI4XX_CFG__

#ifdef __cplusplus
extern "C" {
#endif

#define GPU_DVFS_ENABLE
#define GPU_MAXFREQ_CONFIG_SUPPORT

#if defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3796mv200)
#define GPU_SUPPORT_SVB
#endif

#if defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3796mv200)
#define GPU_SECURE_SUPPORT
#endif

#define HISI_ERROR_INFO() \
    printk("func = %s, line = %d\n", __FUNCTION__, __LINE__);

#define HISI_DEBUG 0

#ifdef __cplusplus
}
#endif
#endif


