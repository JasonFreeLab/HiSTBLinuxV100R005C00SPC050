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
LOCAL_OUT := $(OUT)/drv/pm
else
LOCAL_OUT := $(shell pwd)
endif

LIBS := libsec_$(notdir $(LOCAL_OUT)).a

CFLAGS += -I$(COMMON_DRV_INCLUDE)

OBJS := tee_drv_pmoc.o 

CFLAGS += -I$(TRUSTEDCORE_DIR)/platform/devchip/$(PLATFORM_DIR_NAME)/pm

ifeq ($(CFG_HI_CHIP_TYPE), hi3796mv200)
CFLAGS += -I$(TRUSTEDCORE_DIR)/platform/devchip/$(PLATFORM_DIR_NAME)/chip/$(PLATFORM_CHIP_NAME)/securemem_cfg/tzasc_v2
else
CFLAGS += -I$(TRUSTEDCORE_DIR)/platform/devchip/$(PLATFORM_DIR_NAME)/chip/$(PLATFORM_CHIP_NAME)/securemem_cfg
endif

ALL_OUT_OBJ = $(foreach VAR,$(OBJS),$(addprefix $(LOCAL_OUT)/,$(VAR)))
ALL_OUT_LIBS = $(foreach VAR,$(LIBS),$(addprefix $(LOCAL_OUT)/,$(VAR)))

#===============================================================================
# rules
#===============================================================================
include $(HI_TEE_DRV_DIR)/stb_drv.mak
