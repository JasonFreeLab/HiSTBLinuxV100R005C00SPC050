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
LOCAL_OUT := $(OUT)/drv/mmc
else
LOCAL_OUT := $(shell pwd)
endif

LIBS    := libsec_$(notdir $(LOCAL_OUT)).a

CFLAGS += \
         -I$(COMMON_DRV_INCLUDE)
         
OBJS    := \
				drv_rpmb.o mmc_drv.o  mmc_if.o mmc_rpmb.o sha256.o

ifeq ($(strip $(CFG_HI3798CV200)), y)
CFLAGS += -DCONFIG_ARCH_HI3798CV2X 
OBJS += mmc_ids_hi3798cvx.o
CFLAGS += -DCONFIG_HIMCI_V200 
OBJS += himciv200.o
endif

ifeq ($(strip $(CFG_HI3798MV200)), y)
CFLAGS += -DCONFIG_ARCH_HI3798MV2X 
OBJS += mmc_ids_hi3798mv2x.o
CFLAGS += -DCONFIG_HIMCI_V300 
OBJS += himciv300.o
endif	

ifeq ($(strip $(CFG_HI3796MV200)), y)
CFLAGS += -DCONFIG_ARCH_HI3796MV2X 
OBJS += mmc_ids_hi3796mv2x.o
CFLAGS += -DCONFIG_HIMCI_V300 
OBJS += himciv300.o
endif

ALL_OUT_OBJ = $(foreach VAR,$(OBJS),$(addprefix $(LOCAL_OUT)/,$(VAR)))
ALL_OUT_LIBS = $(foreach VAR,$(LIBS),$(addprefix $(LOCAL_OUT)/,$(VAR)))

#===============================================================================
# rules
#===============================================================================
include $(HI_TEE_DRV_DIR)/stb_drv.mak
