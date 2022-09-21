#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

#===============================================================================
# local variables
#===============================================================================
ifneq ($(OUT),)
LOCAL_OUT := $(OUT)/drv/tzasc
else
LOCAL_OUT := $(shell pwd)
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3796mv100 hi3798mv100 hi3716dv100),)
TZASC_VERSION := v100
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798cv200 hi3798mv200 hi3798mv300),)
TZASC_VERSION := v200
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3796mv200),)
TZASC_VERSION := v300
endif

LIBS    := libsec_$(notdir $(LOCAL_OUT)).a

OBJS    := tee_drv_tzasc.o tee_drv_tzasc_common.o
OBJS    += hal/$(TZASC_VERSION)/tee_drv_tzasc_$(TZASC_VERSION).o

CFLAGS += \
	-I$(HI_TEE_DRV_DIR)/tzasc/include \
	-I$(HI_TEE_DRV_DIR)/tzasc/hal/include \
	-I$(HI_TEE_DRV_DIR)/include \
	-I$(TRUSTEDCORE_DIR)/platform/init

ifeq ($(strip $(CFG_HI_TEE_DEBUG_SUPPORT)), y)
CFLAGS += -DTEE_DRV_TZASC_DEBUG
endif

CFLAGS += -Werror -Wall

ALL_OUT_OBJ = $(foreach VAR,$(OBJS),$(addprefix $(LOCAL_OUT)/,$(VAR)))
ALL_OUT_LIBS = $(foreach VAR,$(LIBS),$(addprefix $(LOCAL_OUT)/,$(VAR)))

#===============================================================================
# rules
#===============================================================================
include $(HI_TEE_DRV_DIR)/stb_drv.mak
