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
LOCAL_OUT := $(OUT)/api/otp
else
LOCAL_OUT := $(shell pwd)
endif

LIBS    := libsec_api_$(notdir $(LOCAL_OUT)).a
OBJS    := hi_tee_otp.o

ifeq ($(CFG_HI_ADVCA_TYPE), NAGRA)
OBJS    += hi_tee_otp_nagra.o
endif

ALL_OUT_OBJ = $(foreach VAR,$(OBJS),$(addprefix $(LOCAL_OUT)/,$(VAR)))
ALL_OUT_LIBS = $(foreach VAR,$(LIBS),$(addprefix $(LOCAL_OUT)/,$(VAR)))

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716dv100 hi3716mv410 hi3716mv420 hi3796mv100 hi3798cv200 hi3798mv100 hi3798mv200 hi3798mv300),)
    ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716mv410 hi3716mv420),)
		ifeq ($(CFG_HI_ADVCA_TYPE),NAGRA)
			CFLAGS += -DOTP_VERSION_V200
		else
			CFLAGS += -DOTP_VERSION_V100
		endif
	else
		CFLAGS += -DOTP_VERSION_V100
	endif
else
	CFLAGS += -DOTP_VERSION_V200
endif

ifeq ($(CFG_HI_CHIP_TYPE), hi3798cv200)
CFLAGS += -DHI_TEE_OTP_HI3798CV200
endif

ifeq ($(CFG_HI_ADVCA_TYPE), VERIMATRIX_ULTRA)
CFLAGS += -DHI_OTP_VERIMATRIX_ULTRA
endif
#===============================================================================
# rules
#===============================================================================
include $(HI_TEE_API_DIR)/stb_api.mak
