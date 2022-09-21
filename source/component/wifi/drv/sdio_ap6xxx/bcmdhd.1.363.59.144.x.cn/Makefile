# bcmdhd
# 1. WL_IFACE_COMB_NUM_CHANNELS must be added if Android version is 4.4 with Kernel version 3.0~3.4,
#    otherwise please remove it.
CONFIG_PLATFORM_HISILICON = y

CONFIG_BCMDHD := m
CONFIG_BCMDHD_SDIO := y
#CONFIG_BCMDHD_PCIE := y
CONFIG_BCMDHD_OOB := y
CONFIG_BCMDHD_PROPTXSTATUS := y
CONFIG_BCMDHD_DISABLE_WOWLAN := y

ifeq ($(CFG_HI_EXPORT_FLAG),)
    ifneq ($(srctree),)
    KERNEL_DIR := $(srctree)

    SDK_DIR := $(shell cd $(KERNEL_DIR)/../../.. && /bin/pwd)
    else
    SDK_DIR := $(shell cd $(CURDIR)/../../../../../.. && /bin/pwd)
    endif
  
    include $(SDK_DIR)/base.mak
endif

MODULE_SRC := bcmdhd.1.363.59.144.x.cn

MODULE := bcmdhd.ko
MODULE_PATH := $(BUILD_DIR)/$(MODULE_SRC)/bcmdhd.ko

INSTALL_DIR := $(ANDROID_PRODUCT_OUT)/system/lib/modules

MODULE_FW := $(shell pwd)/../AP6356S_4.2/Wi-Fi/fw_bcm4356a2_ag.bin \
             $(shell pwd)/../AP6356S_4.2/Wi-Fi/fw_bcm4356a2_ag_apsta.bin \
             $(shell pwd)/../AP6356S_4.2/Wi-Fi/fw_bcm4356a2_ag_p2p.bin \
             $(shell pwd)/../AP6356S_4.2/Wi-Fi/nvram_ap6356s.txt \
             $(shell pwd)/../AP6356S_4.2/BT/BCM4356A2.hcd

FW_INSTALL_DIR := $(ANDROID_PRODUCT_OUT)/system/etc/firmware/AP6356S

BUILD_MODULES = $(patsubst %,%_build,${MODULE_SRC})
UNINSTALL_MODULES = $(patsubst %,%_uninstall,${MODULE})

#HI_GPIO_CFLAG := -I$(COMMON_DIR)/include \
                 -I$(MSP_DIR)/include \
                 -I$(MSP_DRV_INCLUDE) \
                 -I$(MSP_API_INCLUDE) \
                 -I$(SDK_DIR)/source/kernel/linux-3.18.y/arch/arm/mach-s40/include

#export HI_GPIO_CFLAG += $(CFG_HI_KMOD_CFLAGS)

#export DHD_INC_CFLAG := -I$(BUILD_DIR)/$(MODULE_SRC) -I$(BUILD_DIR)/$(MODULE_SRC)/include -I$(BUILD_DIR)/$(MODULE_SRC)/common/include

DHDCFLAGS = -Wall -Wstrict-prototypes -Dlinux -DBCMDRIVER -DSDTEST       \
	-DBCMDONGLEHOST -DUNRELEASEDCHIP -DBCMDMA32 -DBCMFILEIMAGE            \
	-DDHDTHREAD -DDHD_DEBUG -DSHOW_EVENTS -DBCMDBG -DGET_OTP_MAC_ENABLE   \
	-DWIFI_ACT_FRAME -DARP_OFFLOAD_SUPPORT -DSUPPORT_PM2_ONLY             \
	-DKEEP_ALIVE -DPKT_FILTER_SUPPORT -DPNO_SUPPORT -DDHDTCPACK_SUPPRESS  \
	-DDHD_DONOT_FORWARD_BCMEVENT_AS_NETWORK_PKT -DRXFRAME_THREAD          \
	-DTSQ_MULTIPLIER                                                      \
	-DBCMSDIOH_TXGLOM_EXT -DWL_EXT_IAPSTA                                 \
	-DENABLE_INSMOD_NO_FW_LOAD                                            \
	-I$(src) -I$(src)/include \
	-I$(COMMON_DIR)/include \
	-I$(MSP_DIR)/include \
	-I$(MSP_DRV_INCLUDE) \
	-I$(MSP_API_INCLUDE) \
	-I$(SDK_DIR)/source/kernel/linux-3.18.y/arch/arm/mach-s40/include
#	-Idrivers/net/wireless/bcmdhd -Idrivers/net/wireless/bcmdhd/include

DHDOFILES = aiutils.o siutils.o sbutils.o bcmutils.o bcmwifi_channels.o \
	dhd_linux.o dhd_linux_platdev.o dhd_linux_sched.o dhd_pno.o \
	dhd_common.o dhd_ip.o dhd_linux_wq.o dhd_custom_gpio.o \
	bcmevent.o hndpmu.o linux_osl.o wldev_common.o wl_android.o \
	hnd_pktq.o hnd_pktpool.o dhd_config.o wl_android_ext.o

ifneq ($(CONFIG_BCMDHD_SDIO),)
DHDCFLAGS += \
	-DBCMSDIO -DMMC_SDIO_ABORT -DBCMLXSDMMC -DUSE_SDIOFIFO_IOVAR          \
	-DBDC -DDHD_USE_IDLECOUNT -DBCMSDIOH_TXGLOM -DPKT_STATICS      \
	-DCUSTOM_SDIO_F2_BLKSIZE=256

DHDOFILES += bcmsdh.o bcmsdh_linux.o bcmsdh_sdmmc.o bcmsdh_sdmmc_linux.o \
	dhd_sdio.o dhd_cdc.o dhd_wlfc.o

ifeq ($(CONFIG_PLATFORM_HISILICON),y)
DHDCFLAGS += -DCONFIG_PLATFORM_HISILICON
DHDCFLAGS += -DCHIP_TYPE_$(CFG_HI_CHIP_TYPE)
endif


ifeq ($(CONFIG_BCMDHD_OOB),y)
DHDCFLAGS += -DOOB_INTR_ONLY -DCUSTOMER_OOB
ifeq ($(CONFIG_BCMDHD_DISABLE_WOWLAN),y)
DHDCFLAGS += -DDISABLE_WOWLAN
endif
else
DHDCFLAGS += -DSDIO_ISR_THREAD
endif
endif

ifeq ($(CONFIG_BCMDHD_PROPTXSTATUS),y)
ifneq ($(CONFIG_BCMDHD_SDIO),)
DHDCFLAGS += -DPROP_TXSTATUS
endif
ifneq ($(CONFIG_CFG80211),)
DHDCFLAGS += -DPROP_TXSTATUS_VSDB
endif
endif

ifneq ($(CONFIG_BCMDHD_PCIE),)
DHDCFLAGS += \
	-DPCIE_FULL_DONGLE -DBCMPCIE -DCUSTOM_DPC_PRIO_SETTING=-1

DHDOFILES += dhd_pcie.o dhd_pcie_linux.o pcie_core.o dhd_flowring.o \
	dhd_msgbuf.o
endif

obj-$(CONFIG_BCMDHD) += bcmdhd.o
bcmdhd-objs += $(DHDOFILES)

#ifeq ($(CONFIG_MACH_PLATFORM),y)
DHDOFILES += dhd_gpio.o
DHDCFLAGS += -DCUSTOMER_HW -DDHD_OF_SUPPORT
#DHDCFLAGS += -DBCMWAPI_WPI -DBCMWAPI_WAI
#endif

ifeq ($(CONFIG_BCMDHD_AG),y)
DHDCFLAGS += -DBAND_AG
endif

ifeq ($(CONFIG_DHD_USE_STATIC_BUF),y)
obj-m += dhd_static_buf.o
DHDCFLAGS += -DSTATIC_WL_PRIV_STRUCT -DENHANCED_STATIC_BUF
endif

ifneq ($(CONFIG_WIRELESS_EXT),)
DHDOFILES += wl_iw.o wl_escan.o
DHDCFLAGS += -DSOFTAP -DWL_WIRELESS_EXT -DUSE_IW -DWL_ESCAN
endif
ifneq ($(CONFIG_CFG80211),)
DHDOFILES += wl_cfg80211.o wl_cfgp2p.o wl_linux_mon.o wl_cfg_btcoex.o wl_cfgvendor.o
DHDOFILES += dhd_cfg80211.o dhd_cfg_vendor.o
DHDCFLAGS += -DWL_CFG80211 -DWLP2P -DWL_CFG80211_STA_EVENT -DWL_ENABLE_P2P_IF
DHDCFLAGS += -DWL_IFACE_COMB_NUM_CHANNELS
DHDCFLAGS += -DCUSTOM_ROAM_TRIGGER_SETTING=-65
DHDCFLAGS += -DCUSTOM_ROAM_DELTA_SETTING=15
DHDCFLAGS += -DCUSTOM_KEEP_ALIVE_SETTING=28000
DHDCFLAGS += -DCUSTOM_PNO_EVENT_LOCK_xTIME=7
DHDCFLAGS += -DWL_SUPPORT_AUTO_CHANNEL
DHDCFLAGS += -DWL_SUPPORT_BACKPORTED_KPATCHES
DHDCFLAGS += -DESCAN_RESULT_PATCH
DHDCFLAGS += -DVSDB -DWL_CFG80211_VSDB_PRIORITIZE_SCAN_REQUEST
DHDCFLAGS += -DWLTDLS -DMIRACAST_AMPDU_SIZE=8
endif
EXTRA_CFLAGS = $(DHDCFLAGS)
ifeq ($(CONFIG_BCMDHD),m)
DHDCFLAGS += -DMULTIPLE_SUPPLICANT
EXTRA_LDFLAGS += --strip-debug
else
DHDCFLAGS += -DBUILD_IN_KERNEL
endif

.PHONY: all clean install uninstall
all: $(BUILD_MODULES)

install: all
	@test -d $(INSTALL_DIR) || mkdir -p $(INSTALL_DIR)
	@cp -v $(MODULE_PATH) $(INSTALL_DIR)/
	@test -d $(FW_INSTALL_DIR) || mkdir -p $(FW_INSTALL_DIR)
	@cp -v $(MODULE_FW) $(FW_INSTALL_DIR)/

uninstall: $(UNINSTALL_MODULES)

