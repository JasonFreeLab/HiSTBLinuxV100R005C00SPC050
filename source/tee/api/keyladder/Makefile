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
LOCAL_OUT := $(OUT)/api/keyladder
else
LOCAL_OUT := $(shell pwd)
endif

LIBS    := libsec_api_$(notdir $(LOCAL_OUT)).a
OBJS    := tee_keyladder.o

ifeq ($(CFG_HI_ADVCA_TYPE), VERIMATRIX_ULTRA)
OBJS    += tee_keyladder_verimatrix.o
else ifeq ($(CFG_HI_ADVCA_TYPE), DCAS)
OBJS    += tee_keyladder_dcas.o
else ifeq ($(CFG_HI_ADVCA_TYPE), NAGRA)
OBJS    += tee_cert.o
OBJS    += tee_keyladder_nagra.o
endif 

ifeq ($(CFG_HI_ADVCA_TYPE), IRDETO)
OBJS    += tee_keyladder_irdeto.o
endif

ifeq ($(CFG_HI_ADVCA_TYPE), SUMA)
OBJS    += tee_keyladder_suma.o
endif

ALL_OUT_OBJ = $(foreach VAR,$(OBJS),$(addprefix $(LOCAL_OUT)/,$(VAR)))
ALL_OUT_LIBS = $(foreach VAR,$(LIBS),$(addprefix $(LOCAL_OUT)/,$(VAR)))

#===============================================================================
# rules
#===============================================================================
include $(HI_TEE_API_DIR)/stb_api.mak
