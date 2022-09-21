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
LOCAL_OUT := $(OUT)/drv/security_check
else
LOCAL_OUT := $(shell pwd)
endif

LIBS    := libsec_$(notdir $(LOCAL_OUT)).a

ifeq ($(CFG_HI_ADVCA_TYPE),NAGRA)
OBJS    := nagra_security_check.o
endif

ifeq ($(CFG_HI_ADVCA_TYPE),VERIMATRIX)
CFLAGS += -DHI_OTP_VERIMATRIX_ADVANCE
OBJS    := security_check.o
endif

ifeq ($(CFG_HI_ADVCA_TYPE),VERIMATRIX_ULTRA)
CFLAGS += -DHI_OTP_VERIMATRIX_ULTRA
OBJS    := security_check.o
endif

CFLAGS += -I$(TRUSTEDCORE_DIR)/platform/devchip/$(PLATFORM_DIR_NAME)/pm

ALL_OUT_OBJ = $(foreach VAR,$(OBJS),$(addprefix $(LOCAL_OUT)/,$(VAR)))
ALL_OUT_LIBS = $(foreach VAR,$(LIBS),$(addprefix $(LOCAL_OUT)/,$(VAR)))

#===============================================================================
# rules
#===============================================================================
include $(HI_TEE_DRV_DIR)/stb_drv.mak
