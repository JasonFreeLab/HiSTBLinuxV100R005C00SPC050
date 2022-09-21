#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
    ifneq ($(srctree),)
    KERNEL_DIR := $(srctree)

    SDK_DIR := $(shell cd $(KERNEL_DIR)/../../.. && /bin/pwd)
    else
    SDK_DIR := $(shell cd $(CURDIR)/../../../.. && /bin/pwd)
    endif

    include $(SDK_DIR)/base.mak
endif

#===============================================================================
# local variables
#===============================================================================
VPSS_DIR := $(MSP_DIR)/drv/vpss

EXTRA_CFLAGS += $(CFG_HI_KMOD_CFLAGS)

EXTRA_CFLAGS += -I$(COMMON_UNF_INCLUDE)                 \
                -I$(COMMON_API_INCLUDE)                 \
                -I$(COMMON_DRV_INCLUDE)                 \
                -I$(MSP_UNF_INCLUDE)                    \
                -I$(MSP_API_INCLUDE)                    \
                -I$(MSP_DRV_INCLUDE)

ifeq ($(CFG_HI_TEE_SUPPORT),y)
EXTRA_CFLAGS += -I$(KERNEL_DIR)/$(CFG_HI_KERNEL_VERSION)/drivers/hisilicon/sec_mmz
endif


ifdef CFG_HI_VPSS_MAX_BUFFER_NUMB
EXTRA_CFLAGS += -DHI_VPSS_MAX_BUFFER_NUMB=$(CFG_HI_VPSS_MAX_BUFFER_NUMB)
else
EXTRA_CFLAGS += -DHI_VPSS_MAX_BUFFER_NUMB=10
endif

ifdef CFG_HI_SMMU_SUPPORT
EXTRA_CFLAGS += -DHI_VPSS_SMMU_SUPPORT
endif
MOD_NAME := hi_vpss

obj-$(HI_DRV_BUILDTYPE) += $(MOD_NAME).o

ifeq ($(CFG_HI_NVR_SUPPORT),y)
ifeq ($(CFG_HI_CHIP_TYPE),hi3796mv200)
VPSS_DIR_VER := vpss_v4_0_nvr
else
VPSS_DIR_VER := vpss_v4_0
endif
else
VPSS_DIR_VER := vpss_v4_0
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798cv200 hi3798mv200 hi3798mv300 hi3798mv200_a),)
    EXTRA_CFLAGS += -I$(VPSS_DIR)/$(VPSS_DIR_VER)/                    \
                    -I$(VPSS_DIR)/$(VPSS_DIR_VER)/hal                 \
                    -I$(VPSS_DIR)/$(VPSS_DIR_VER)/vpss_in             \
                    -I$(VPSS_DIR)/$(VPSS_DIR_VER)/alg \
                    -I$(VPSS_DIR)/$(VPSS_DIR_VER)/vpss_in/hi3798cv200 \
                    -I$(VPSS_DIR)/$(VPSS_DIR_VER)/hal/hi3798cv200     \
                    -I$(VPSS_DIR)/$(VPSS_DIR_VER)/hal/hi3798mv200     \
                    -I$(VPSS_DIR)/$(VPSS_DIR_VER)/vpss_in/hi3798mv200 \
                    -I$(VPSS_DIR)/$(VPSS_DIR_VER)/hal/hi3798mv200/hal \
                    -I$(VPSS_DIR)/$(VPSS_DIR_VER)/hal/hi3798mv200/common_inc \
                    -I$(VPSS_DIR)/$(VPSS_DIR_VER)/hal/hi3798mv200/intf \
                    -I$(VPSS_DIR)/$(VPSS_DIR_VER)/hal/hi3798mv200/base \
                    -I$(VPSS_DIR)/$(VPSS_DIR_VER)/hal/hi3798mv200/alg \
                    -I$(VPSS_DIR)/$(VPSS_DIR_VER)/hal/hi3798mv200/func \
                    -I$(VPSS_DIR)/$(VPSS_DIR_VER)/hal/hi3798mv200/reg \
                    -I$(VPSS_DIR)/$(VPSS_DIR_VER)/hal/hi3798mv200/debug \
                    -I$(VPSS_DIR)/$(VPSS_DIR_VER)/hal/hi3798mv200/info \
                    -I$(VPSS_DIR)/$(VPSS_DIR_VER)/hal/hi3798mv200/frame
    DRIVER_PATH := $(CURDIR)/$(VPSS_DIR_VER)
else ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3796mv200),)
    EXTRA_CFLAGS += -I$(VPSS_DIR)/$(VPSS_DIR_VER)                    \
                    -I$(VPSS_DIR)/$(VPSS_DIR_VER)/hal                 \
                    -I$(VPSS_DIR)/$(VPSS_DIR_VER)/vpss_in             \
                    -I$(VPSS_DIR)/$(VPSS_DIR_VER)/alg \
                    -I$(VPSS_DIR)/$(VPSS_DIR_VER)/hal/hi3796mv200     \
                    -I$(VPSS_DIR)/$(VPSS_DIR_VER)/vpss_in/hi3796mv200 \
                    -I$(VPSS_DIR)/$(VPSS_DIR_VER)/hal/hi3796mv200/hal \
					-I$(VPSS_DIR)/$(VPSS_DIR_VER)/hal/hi3796mv200/common_inc \
                    -I$(VPSS_DIR)/$(VPSS_DIR_VER)/hal/hi3796mv200/intf \
                    -I$(VPSS_DIR)/$(VPSS_DIR_VER)/hal/hi3796mv200/base \
                    -I$(VPSS_DIR)/$(VPSS_DIR_VER)/hal/hi3796mv200/alg \
                    -I$(VPSS_DIR)/$(VPSS_DIR_VER)/hal/hi3796mv200/func \
                    -I$(VPSS_DIR)/$(VPSS_DIR_VER)/hal/hi3796mv200/debug \
                    -I$(VPSS_DIR)/$(VPSS_DIR_VER)/hal/hi3796mv200/info \
                    -I$(VPSS_DIR)/$(VPSS_DIR_VER)/hal/hi3796mv200/frame \
					-I$(VPSS_DIR)/$(VPSS_DIR_VER)/hal/hi3796mv200/util \
					-I$(VPSS_DIR)/$(VPSS_DIR_VER)/hal/hi3796mv200/pq \
					-I$(VPSS_DIR)/$(VPSS_DIR_VER)/hal/hi3796mv200/reg \
					-I$(VPSS_DIR)/$(VPSS_DIR_VER)/hal/hi3796mv200/drv \
					-I$(VPSS_DIR)/$(VPSS_DIR_VER)/hal/hi3796mv200/drv/crop \
					-I$(VPSS_DIR)/$(VPSS_DIR_VER)/hal/hi3796mv200/drv/tnr \
					-I$(VPSS_DIR)/$(VPSS_DIR_VER)/hal/hi3796mv200/drv/lba \
					-I$(VPSS_DIR)/$(VPSS_DIR_VER)/hal/hi3796mv200/drv/mmu \
					-I$(VPSS_DIR)/$(VPSS_DIR_VER)/hal/hi3796mv200/drv/snr \
					-I$(VPSS_DIR)/$(VPSS_DIR_VER)/hal/hi3796mv200/drv/sys \
					-I$(VPSS_DIR)/$(VPSS_DIR_VER)/hal/hi3796mv200/drv/vc1 \
					-I$(VPSS_DIR)/$(VPSS_DIR_VER)/hal/hi3796mv200/drv/dei \
					-I$(VPSS_DIR)/$(VPSS_DIR_VER)/hal/hi3796mv200/drv/fmtc \
					-I$(VPSS_DIR)/$(VPSS_DIR_VER)/hal/hi3796mv200/drv/mac \
					-I$(VPSS_DIR)/$(VPSS_DIR_VER)/hal/hi3796mv200/drv/zme
    DRIVER_PATH := $(CURDIR)/$(VPSS_DIR_VER)
else
    EXTRA_CFLAGS += -I$(VPSS_DIR)/vpss_v3_0/                    \
                    -I$(VPSS_DIR)/vpss_v3_0/hal                 \
                    -I$(VPSS_DIR)/vpss_v3_0/hal/hi3798mv100     \
                    -I$(VPSS_DIR)/vpss_v3_0/hal/hifoneb02       \
                    -I$(VPSS_DIR)/vpss_v3_0/hal/hi3716mv410     \
                    -I$(VPSS_DIR)/vpss_v3_0/vpss_in             \
                    -I$(VPSS_DIR)/vpss_v3_0/vpss_in/hi3798mv100 \
                    -I$(VPSS_DIR)/vpss_v3_0/vpss_in/hifoneb02   \
                    -I$(VPSS_DIR)/vpss_v3_0/vpss_in/hi3716mv410 \
                    -I$(VPSS_DIR)/vpss_v3_0/alg
    DRIVER_PATH := $(CURDIR)/vpss_v3_0
endif


ifeq ($(DRIVER_PATH), $(CURDIR)/$(VPSS_DIR_VER))
$(MOD_NAME)-y   :=  $(VPSS_DIR_VER)/vpss_osal.o \
                    $(VPSS_DIR_VER)/vpss_info.o\
                    $(VPSS_DIR_VER)/vpss_fb.o \
                    $(VPSS_DIR_VER)/vpss_mcdei.o \
                    $(VPSS_DIR_VER)/vpss_stt_mcdei.o \
                    $(VPSS_DIR_VER)/vpss_wbc_mcdei.o \
                    $(VPSS_DIR_VER)/vpss_wbc.o \
                    $(VPSS_DIR_VER)/vpss_in/vpss_src.o \
                    $(VPSS_DIR_VER)/vpss_his.o \
                    $(VPSS_DIR_VER)/vpss_sttinf.o \
                    $(VPSS_DIR_VER)/vpss_in/vpss_img.o \
                    $(VPSS_DIR_VER)/alg/vpss_alg_ratio.o \
                    $(VPSS_DIR_VER)/alg/vpss_alg_rwzb.o \
                    $(VPSS_DIR_VER)/alg/vpss_alg_scd.o\
                    $(VPSS_DIR_VER)/vpss_rwzb.o \
                    $(VPSS_DIR_VER)/vpss_instance.o\
                    $(VPSS_DIR_VER)/vpss_ctrl.o \
                    $(VPSS_DIR_VER)/drv_vpss_intf_k.o \
                    $(VPSS_DIR_VER)/vpss_trans_fb.o
endif
#
ifeq ($(DRIVER_PATH), $(CURDIR)/vpss_v3_0)
$(MOD_NAME)-y   :=  vpss_v3_0/vpss_osal.o \
                    vpss_v3_0/vpss_info.o\
                    vpss_v3_0/vpss_fb.o \
                    vpss_v3_0/vpss_wbc.o \
                    vpss_v3_0/vpss_in/vpss_src.o \
                    vpss_v3_0/vpss_his.o \
                    vpss_v3_0/vpss_sttinf.o \
                    vpss_v3_0/vpss_in/vpss_img.o \
                    vpss_v3_0/alg/vpss_alg_ratio.o \
                    vpss_v3_0/alg/vpss_alg_rwzb.o \
                    vpss_v3_0/alg/vpss_alg_scd.o\
                    vpss_v3_0/vpss_rwzb.o \
                    vpss_v3_0/vpss_instance.o\
                    vpss_v3_0/vpss_ctrl.o \
                    vpss_v3_0/drv_vpss_intf_k.o \
                    vpss_v3_0/vpss_trans_fb.o
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798cv200),)
$(MOD_NAME)-y   +=  \
            $(VPSS_DIR_VER)/vpss_in/hi3798cv200/vpss_in_3798cv200.o \
            $(VPSS_DIR_VER)/hal/hi3798cv200/vpss_reg_3798cv200.o \
            $(VPSS_DIR_VER)/hal/hi3798cv200/vpss_hal_3798cv200.o
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv200 hi3798mv300 hi3798mv200_a),)
$(MOD_NAME)-y   +=  \
                    $(VPSS_DIR_VER)/hal/hi3798mv200/alg/vpss_cbb_alg.o \
                    $(VPSS_DIR_VER)/hal/hi3798mv200/base/vpss_cbb_base.o \
                    $(VPSS_DIR_VER)/hal/hi3798mv200/debug/vpss_cbb_debug.o \
                    $(VPSS_DIR_VER)/hal/hi3798mv200/debug/vpss_cbb_assert.o \
                    $(VPSS_DIR_VER)/hal/hi3798mv200/frame/vpss_cbb_frame.o \
                    $(VPSS_DIR_VER)/hal/hi3798mv200/func/vpss_cbb_func.o \
                    $(VPSS_DIR_VER)/hal/hi3798mv200/info/vpss_cbb_info.o \
                    $(VPSS_DIR_VER)/hal/hi3798mv200/intf/vpss_cbb_intf.o \
                    $(VPSS_DIR_VER)/hal/hi3798mv200/util/vpss_cbb_util.o \
                    $(VPSS_DIR_VER)/hal/hi3798mv200/hal/vpss_cbb_hal.o \
                    $(VPSS_DIR_VER)/hal/hi3798mv200/reg/vpss_cbb_reg.o \
                    $(VPSS_DIR_VER)/vpss_in/hi3798mv200/vpss_in_3798mv200.o
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3796mv200),)
$(MOD_NAME)-y   +=  \
                    $(VPSS_DIR_VER)/hal/hi3796mv200/alg/vpss_cbb_alg.o \
                    $(VPSS_DIR_VER)/hal/hi3796mv200/base/vpss_cbb_base.o \
                    $(VPSS_DIR_VER)/hal/hi3796mv200/debug/vpss_cbb_debug.o \
                    $(VPSS_DIR_VER)/hal/hi3796mv200/debug/vpss_cbb_assert.o \
                    $(VPSS_DIR_VER)/hal/hi3796mv200/frame/vpss_cbb_frame.o \
                    $(VPSS_DIR_VER)/hal/hi3796mv200/func/vpss_cbb_func.o \
                    $(VPSS_DIR_VER)/hal/hi3796mv200/info/vpss_cbb_info.o \
                    $(VPSS_DIR_VER)/hal/hi3796mv200/intf/vpss_cbb_intf.o \
                    $(VPSS_DIR_VER)/hal/hi3796mv200/util/vpss_cbb_util.o \
					$(VPSS_DIR_VER)/hal/hi3796mv200/hal/vpss_cbb_hal.o \
					$(VPSS_DIR_VER)/hal/hi3796mv200/reg/vpss_cbb_reg.o \
                    $(VPSS_DIR_VER)/hal/hi3796mv200/drv/crop/vpss_cbb_hal_crop.o\
				    $(VPSS_DIR_VER)/hal/hi3796mv200/drv/dei/vpss_cbb_hal_die.o\
					$(VPSS_DIR_VER)/hal/hi3796mv200/drv/fmtc/vpss_cbb_hal_fmtc.o\
					$(VPSS_DIR_VER)/hal/hi3796mv200/drv/lba/vpss_cbb_hal_lba.o\
					$(VPSS_DIR_VER)/hal/hi3796mv200/drv/mac/vpss_cbb_hal_mac.o\
					$(VPSS_DIR_VER)/hal/hi3796mv200/drv/mmu/vpss_cbb_hal_mmu.o\
					$(VPSS_DIR_VER)/hal/hi3796mv200/drv/snr/vpss_cbb_hal_snr.o\
					$(VPSS_DIR_VER)/hal/hi3796mv200/drv/sys/vpss_cbb_hal_sys.o\
					$(VPSS_DIR_VER)/hal/hi3796mv200/drv/tnr/vpss_cbb_hal_tnr.o\
					$(VPSS_DIR_VER)/hal/hi3796mv200/drv/vc1/vpss_cbb_hal_vc1.o\
					$(VPSS_DIR_VER)/hal/hi3796mv200/drv/zme/vpss_cbb_hal_zme.o\
                    $(VPSS_DIR_VER)/vpss_in/hi3796mv200/vpss_in_3796mv200.o
endif
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv100 hi3796mv100 hi3716dv100),)
$(MOD_NAME)-y   +=  \
            vpss_v3_0/hal/hi3798mv100/vpss_reg_3798m.o \
            vpss_v3_0/hal/hi3798mv100/vpss_hal_3798m.o \
            vpss_v3_0/vpss_in/hi3798mv100/vpss_in_3798mv100.o
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716mv410 hi3716mv420),)
$(MOD_NAME)-y   +=  \
            vpss_v3_0/hal/hi3716mv410/vpss_reg_3716mv410.o \
            vpss_v3_0/hal/hi3716mv410/vpss_hal_3716mv410.o \
            vpss_v3_0/vpss_in/hi3716mv410/vpss_in_3716mv410.o
endif

BUILD_DIR := $(HI_OUT_DIR)/$(OBJ_NAME)/$(subst $(SDK_DIR)/,,$(CURDIR))

BUILD_DIR_MAKEFILE := $(BUILD_DIR)/Makefile

#===============================================================================
#   rules
#===============================================================================
.PHONY: all clean

all: $(BUILD_DIR_MAKEFILE)
	$(AT)make -C $(LINUX_DIR) ARCH=$(CFG_HI_CPU_ARCH) CROSS_COMPILE=$(HI_KERNEL_TOOLCHAINS_NAME)- M=$(BUILD_DIR) src=$(CURDIR) modules
	$(AT)test -d $(HI_MODULE_DIR) || mkdir -p $(HI_MODULE_DIR)
	$(AT)cp -f $(BUILD_DIR)/$(MOD_NAME).ko $(HI_MODULE_DIR)/

clean:
	$(AT)make -C $(LINUX_DIR) ARCH=$(CFG_HI_CPU_ARCH) CROSS_COMPILE=$(HI_KERNEL_TOOLCHAINS_NAME)- M=$(BUILD_DIR) src=$(CURDIR) clean
	$(AT)rm -rf $(HI_MODULE_DIR)/$(MOD_NAME).ko

$(BUILD_DIR_MAKEFILE): $(BUILD_DIR)
	$(AT)touch $@

$(BUILD_DIR):
	$(AT)mkdir -p $@

