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
LOCAL_OUT := $(OUT)/drv/otp
else
LOCAL_OUT := $(shell pwd)
endif

LIBS    := libsec_$(notdir $(LOCAL_OUT)).a
OTP_VERSION :=hal_otp_v200
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716dv100 hi3716mv410 hi3716mv420 hi3796mv100 hi3798cv200 hi3798mv100 hi3798mv200 hi3798mv300),)
    OTP_VERSION :=hal_otp_v100
endif
OBJS   := tee_drv_otp.o
OBJS   += $(OTP_VERSION)/tee_hal_otp.o

CFLAGS += -I$(OTP_VERSION)
CFLAGS += -I$(HI_TEE_DRV_DIR)/otp/include

CFLAGS += -I$(TRUSTEDCORE_DIR)/platform/devchip/$(PLATFORM_DIR_NAME)/pm
CFLAGS += -I$(TRUSTEDCORE_DIR)/platform/devchip/$(PLATFORM_DIR_NAME)/include

ALL_OUT_OBJ = $(foreach VAR,$(OBJS),$(addprefix $(LOCAL_OUT)/,$(VAR)))
ALL_OUT_LIBS = $(foreach VAR,$(LIBS),$(addprefix $(LOCAL_OUT)/,$(VAR)))

#===============================================================================
# rules
#===============================================================================
include $(HI_TEE_DRV_DIR)/stb_drv.mak
