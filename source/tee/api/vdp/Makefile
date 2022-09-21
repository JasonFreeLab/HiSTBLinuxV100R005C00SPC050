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
LOCAL_OUT := $(OUT)/api/vdp
else
LOCAL_OUT := $(shell pwd)
endif

LIBS    := libsec_api_$(notdir $(LOCAL_OUT)).a
OBJS    := 

ifeq ($(strip $(CFG_HI_TEE_VDP_VERIMATRIX_SUPPORT)), y)
OBJS    += hi_tee_vdp_vmx_adpter.o hi_tee_vdp_watermark.o tee_vdp_common.o vdp_watermark_verimatrix.o
CFLAGS += -DHI_TEE_VDP_VWM_VERIMATRIX
endif

ifeq ($(strip $(CFG_HI_TEE_VDP_NEXTGUARD_SUPPORT)), y)
OBJS    += hi_tee_vdp_watermark.o tee_vdp_common.o vdp_watermark_nextguard.o
CFLAGS += -DHI_TEE_VDP_VWM_NEXTGUARD
endif

OBJS    += tee_vdp_common.o 

ALL_OUT_OBJ = $(foreach VAR,$(OBJS),$(addprefix $(LOCAL_OUT)/,$(VAR)))
ALL_OUT_LIBS = $(foreach VAR,$(LIBS),$(addprefix $(LOCAL_OUT)/,$(VAR)))

#===============================================================================
# rules
#===============================================================================
include $(HI_TEE_API_DIR)/stb_api.mak
