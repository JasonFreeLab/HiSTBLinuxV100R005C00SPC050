#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
    ifneq ($(srctree),)
    KERNEL_DIR := $(srctree)

    SDK_DIR := $(shell cd $(KERNEL_DIR)/../../.. && /bin/pwd)
    else
    SDK_DIR := $(shell cd $(CURDIR)/../../../../.. && /bin/pwd)
    endif

    include $(SDK_DIR)/base.mak
endif

#===============================================================================
# local variables
#===============================================================================
ADSP_DRV_INCLUDE := $(MSP_DIR)/drv/adsp/adsp_v1_1/include

EXTRA_CFLAGS += $(CFG_HI_KMOD_CFLAGS)

EXTRA_CFLAGS += \
		-I$(COMMON_UNF_INCLUDE)                 \
		-I$(COMMON_API_INCLUDE)                 \
		-I$(COMMON_DRV_INCLUDE)                 \
		-I$(MSP_UNF_INCLUDE)                    \
		-I$(MSP_API_INCLUDE)                    \
		-I$(MSP_DRV_INCLUDE)                    \
		-I$(MSP_DIR)/api/higo/include           \
		-I$(ADSP_DRV_INCLUDE)                   \
		-I$(CURDIR)

#COMMON include
EXTRA_CFLAGS += -I$(MSP_DIR)/drv/aiao/aiao_v1_1/common/include
#AO include
EXTRA_CFLAGS += -I$(MSP_DIR)/drv/aiao/aiao_v1_1/ao

EXTRA_CFLAGS += -DHI_SND_ADAC_USE_EXT_AMP
ifeq ($(CFG_HI_SND_MUTECTL_SUPPORT),y)
EXTRA_CFLAGS += -DHI_SND_MUTECTL_SUPPORT
EXTRA_CFLAGS += -DHI_SND_MUTECTL_GPIO=$(CFG_HI_SND_MUTECTL_GPIO)
EXTRA_CFLAGS += -DHI_SND_MUTECTL_LEVEL=$(CFG_HI_SND_MUTECTL_LEVEL)
endif

#===============================================================================
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3796mv200),)
# DSP AOE
EXTRA_CFLAGS += -DHI_SND_DSP_SUPPORT
endif
#===============================================================================
ifeq ($(CFG_HI_SND_PORT_DELAY_SUPPORT),y)
EXTRA_CFLAGS += -DHI_SOUND_PORT_DELAY_SUPPORT
endif
#===============================================================================
# HI_SND_DRV_SUSPEND_SUPPORT : suspend & resume driver
#===============================================================================
EXTRA_CFLAGS += -DHI_SND_DRV_SUSPEND_SUPPORT

ifeq ($(CFG_HI_SND_HBRA_PASSTHROUGH_SUPPORT),y)
EXTRA_CFLAGS += -DHI_SND_HBRA_PASSTHROUGH_SUPPORT
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv200 hi3798mv300 hi3798mv200_a hi3796mv200),)
EXTRA_CFLAGS += -DHI_SND_HDMI_I2S_SPDIF_MUX
endif
#===============================================================================
MOD_NAME := hi_aiao

obj-$(HI_DRV_BUILDTYPE) += $(MOD_NAME).o

$(MOD_NAME)-y := drv_aiao_module.o

# COMMON SUPPORT
$(MOD_NAME)-y += \
		common/src/audio_util.o \
		common/src/hal_aiao.o \
		common/src/hal_aiao_func.o \
		common/src/hal_aiao_priv.o \
		common/src/hal_tianlai_adac.o

# AO SUPPORT (default)
$(MOD_NAME)-y += \
		ao/drv_ao.o \
		ao/drv_ao_op.o \
		ao/drv_ao_track.o \
		ao/hal_aoe_func.o \
		ao/hal_aoe.o \
		ao/drv_ao_intf.o \
		ao/drv_ao_cast.o \
		ao/hal_cast.o
#===============================================================================
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv100 hi3796mv100 hi3716dv100 hi3716mv410 hi3716mv420),)
$(MOD_NAME)-y += common/src/hal_tianlai_adac_v500.o
EXTRA_CFLAGS += -DHI_TIANLAI_V500
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798cv200 hi3796mv200),)
$(MOD_NAME)-y += common/src/hal_tianlai_adac_v600.o
EXTRA_CFLAGS += -DHI_TIANLAI_V600
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv200 hi3798mv300),)
$(MOD_NAME)-y += common/src/hal_tianlai_adac_v600.o
EXTRA_CFLAGS += -DHI_TIANLAI_V600
$(MOD_NAME)-y += common/src/hal_tianlai_adac_v700.o
EXTRA_CFLAGS += -DHI_TIANLAI_V700
endif
#===============================================================================
ifeq ($(CFG_HI_AIAO_VERIFICATION_SUPPORT),y)
EXTRA_CFLAGS += -DHI_AIAO_VERIFICATION_SUPPORT
$(MOD_NAME)-y += common/src/drv_aiao_veri.o
endif
#===============================================================================

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv100 hi3796mv100 hi3716dv100 hi3798cv200 hi3716mv410 hi3716mv420 hi3798mv200 hi3798mv300 hi3798mv200_a hi3796mv200),)
EXTRA_CFLAGS += -DHI_AIAO_TIMER_SUPPORT
EXTRA_CFLAGS += -I$(MSP_DIR)/drv/aiao/aiao_v1_1/timer
$(MOD_NAME)-y += timer/drv_timer.o
endif
#===============================================================================
# AI SUPPORT(optional)
ifeq ($(CFG_HI_AI_SUPPORT),y)
EXTRA_CFLAGS += -DHI_AUDIO_AI_SUPPORT
EXTRA_CFLAGS += -I$(MSP_DIR)/drv/aiao/aiao_v1_1/ai
$(MOD_NAME)-y += \
		ai/drv_ai_intf.o \
		ai/drv_ai.o
endif
#===============================================================================
# ALSA SUPPORT(optional)
ifeq ($(CFG_HI_SND_ALSA_AO_SUPPORT),y)
EXTRA_CFLAGS += -DHI_ALSA_AO_SUPPORT
EXTRA_CFLAGS += -DHI_ALSA_HRTIMER_SUPPORT
ALSA_DIR = alsa/dsp_mix_v2
EXTRA_CFLAGS += -I$(MSP_DIR)/drv/aiao/aiao_v1_1/$(ALSA_DIR)
$(MOD_NAME)-y += \
		$(ALSA_DIR)/hiaiao_card.o \
		$(ALSA_DIR)/hiaiao_dma.o \
		$(ALSA_DIR)/hiaiao_codec.o \
		$(ALSA_DIR)/hiaiao_i2s.o \
		$(ALSA_DIR)/alsa_aiao_proc_func.o \
		$(ALSA_DIR)/drv_ao_func.o \
		$(ALSA_DIR)/alsa_aiao_volume_func.o

ifeq ($(CFG_HI_ALSA_TVL320_KERNEL_SUPPORT),y)
EXTRA_CFLAGS += -DHI_ALSA_TLV320_SUPPORT
$(MOD_NAME)-y += \
		$(ALSA_DIR)/alsa_i2c.o \
		$(ALSA_DIR)/aic31.o
endif

endif
#===============================================================================
ifeq ($(CFG_HI_SND_ALSA_AI_SUPPORT),y)
EXTRA_CFLAGS += -DHI_ALSA_AI_SUPPORT
$(MOD_NAME)-y += $(ALSA_DIR)/drv_ai_func.o
endif
#===============================================================================
#I2S SUPPORT
EXTRA_CFLAGS += -DHI_I2S0_SUPPORT
# EXTRA_CFLAGS += -DHI_I2S1_SUPPORT
#===============================================================================
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
#===============================================================================
