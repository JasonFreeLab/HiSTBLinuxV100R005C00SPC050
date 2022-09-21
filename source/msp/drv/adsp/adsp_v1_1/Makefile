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

EXTRA_CFLAGS += $(CFG_HI_KMOD_CFLAGS) -Wno-error=format-security

EXTRA_CFLAGS += \
	-I$(COMMON_UNF_INCLUDE) \
	-I$(COMMON_API_INCLUDE) \
	-I$(COMMON_DRV_INCLUDE) \
	-I$(MSP_UNF_INCLUDE)    \
	-I$(MSP_API_INCLUDE)    \
	-I$(MSP_DRV_INCLUDE)

asflags-y := -I$(COMMON_DRV_INCLUDE)

ifeq ($(CFG_HI_CPU_ARCH),arm)
HIFIDIR := ./hifi_32bit
else
HIFIDIR := ./hifi_64bit
endif

ADSP_DIR := $(MSP_DIR)/drv/adsp/adsp_v1_1

EXTRA_CFLAGS += \
	-I$(ADSP_DIR) \
	-I$(ADSP_DIR)/include \
	-I$(ADSP_DIR)/osal

EXTRA_CFLAGS += -DHI_SOUND_SPDIF_COMPENSATION_SUPPORT

MOD_NAME := hi_adsp

obj-$(HI_DRV_BUILDTYPE) += $(MOD_NAME).o

$(MOD_NAME)-y := \
	drv_adsp_intf.o \
	drv_adsp.o \
	drv_adsp_hal.o
	
ifeq ($(CFG_HI_PROC_SUPPORT),y)
$(MOD_NAME)-y += drv_adsp_proc.o
endif
#===============================================================================
HI_SND_DSP_SUPPORT := n

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3796mv200),)
HI_SND_DSP_SUPPORT := y
endif
#===============================================================================
ifeq ($(HI_SND_DSP_SUPPORT),y)
# DSP AOE
EXTRA_CFLAGS += -DHI_SND_DSP_SUPPORT
$(MOD_NAME)-y += dsp_elf_func.o
else
#===============================================================================
# SW AOE
$(MOD_NAME)-y += \
	osal/adsp_osal.o \
	$(HIFIDIR)/common/linear/linear.o \
	$(HIFIDIR)/common/mem/dsp_mem.o \
	$(HIFIDIR)/common/resampler/resample_rom.o \
	$(HIFIDIR)/common/resampler/resample.o \
	$(HIFIDIR)/common/util/dsp_util.o \
	$(HIFIDIR)/common/ringbuf/dsp_ringbuf.o \
	$(HIFIDIR)/common/basicop/basicop.o \
	$(HIFIDIR)/common/timer/system_timer.o \
	$(HIFIDIR)/sw_main.o \
	$(HIFIDIR)/aoe/src/aop/aoe_aop.o \
	$(HIFIDIR)/aoe/src/aop/aoe_cast.o \
	$(HIFIDIR)/aoe/src/aip/aoe_aip.o \
	$(HIFIDIR)/aoe/src/engine/aoe_engine.o \
	$(HIFIDIR)/aoe/src/aoe_main.o \
	$(HIFIDIR)/aoe/src/aoe_reg.o

#===============================================================================
HI_SND_IMEDIA_SRC_SUPPORT := n
HI_SND_AVC_SUPPORT := n
HI_SND_DRC_SUPPORT := n
HI_SND_PEQ_SUPPORT := n

ifeq ($(CFG_HI_CPU_ARCH),arm)
HI_SND_IMEDIA_SRC_SUPPORT := y
HI_SND_AVC_SUPPORT := y
# HI_SND_DRC_SUPPORT := y
# HI_SND_PEQ_SUPPORT := y
endif

ASRC_DIR := $(ADSP_DIR)/external/ASRC_ARM
AVC_DIR := $(ADSP_DIR)/external/AVC_ARM
PEQ_DIR := $(ADSP_DIR)/external/PEQ_ARM

EXTRA_CFLAGS += -I$(ASRC_DIR)/inc
EXTRA_CFLAGS += -I$(AVC_DIR)/inc
EXTRA_CFLAGS += -I$(PEQ_DIR)/inc

ifeq ($(O),)
ADSP_EXT_LIB_DIR := $(HI_OUT_DIR)/$(OBJ_NAME)/$(subst $(SDK_DIR)/,,$(ASRC_DIR)/lib)
AVC_EXT_LIB_DIR := $(HI_OUT_DIR)/$(OBJ_NAME)/$(subst $(SDK_DIR)/,,$(AVC_DIR)/lib)
PEQ_EXT_LIB_DIR := $(HI_OUT_DIR)/$(OBJ_NAME)/$(subst $(SDK_DIR)/,,$(PEQ_DIR)/lib)
else
ADSP_EXT_LIB_DIR := $(O)/drivers/msp/adsp/adsp_v1_1/external/ASRC_ARM/lib
AVC_EXT_LIB_DIR := $(O)/drivers/msp/adsp/adsp_v1_1/external/AVC_ARM/lib
PEQ_EXT_LIB_DIR := $(O)/drivers/msp/adsp/adsp_v1_1/external/PEQ_ARM/lib
endif

ifeq ($(HI_SND_IMEDIA_SRC_SUPPORT),y)
EXTRA_CFLAGS += -DHI_SND_IMEDIA_SRC_SUPPORT
$(shell mkdir -p $(ADSP_EXT_LIB_DIR))
$(shell cp $(ASRC_DIR)/lib/libimedia_asrc_arma9.lib $(ADSP_EXT_LIB_DIR)/libimedia_asrc_arma9.a)
$(MOD_NAME)-y += ./external/ASRC_ARM/lib/libimedia_asrc_arma9.a
endif

ifeq ($(HI_SND_AVC_SUPPORT),y)
EXTRA_CFLAGS += -DHI_SND_AVC_SUPPORT
# EXTRA_CFLAGS += -DHI_SND_DRC_SUPPORT
$(shell mkdir -p $(AVC_EXT_LIB_DIR))
$(shell cp $(AVC_DIR)/lib/libimedia_avc_drc_armA9.lib $(AVC_EXT_LIB_DIR)/libimedia_avc_drc_armA9.a)
$(MOD_NAME)-y += ./external/AVC_ARM/lib/libimedia_avc_drc_armA9.a
endif

ifeq ($(HI_SND_PEQ_SUPPORT),y)
EXTRA_CFLAGS += -DHI_SND_PEQ_SUPPORT
$(shell mkdir -p $(PEQ_EXT_LIB_DIR))
$(shell cp $(PEQ_DIR)/lib/libimedia_peq_arm_A9.lib $(PEQ_EXT_LIB_DIR)/libimedia_peq_arm_A9.a)
$(MOD_NAME)-y += ./external/PEQ_ARM/lib/libimedia_peq_arm_A9.a
endif

endif
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
