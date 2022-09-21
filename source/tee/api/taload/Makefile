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
LOCAL_OUT := $(OUT)/api/taload
else
LOCAL_OUT := $(shell pwd)
endif

LIBS    := libsec_api_$(notdir $(LOCAL_OUT)).a

OBJS    += common/taload_verify.o
OBJS    += common/taload_osal.o
OBJS    += taload_auth.o
OBJS    += taload_key.o

CFLAGS += -I$(HI_TEE_API_DIR)/include
CFLAGS += -I$(HI_TEE_API_DIR)/mem/include
CFLAGS += -I$(HI_TEE_API_DIR)/taload/common
CFLAGS += -I$(HI_TEE_API_DIR)/taload
CFLAGS += -I$(TRUSTEDCORE_DIR)/include/TEE

ifeq ($(HI_ADVANCED_CHIP),y)
CFLAGS += -DHI_ADVANCED_CHIP
endif

#CFLAGS += -Werror -Wall

ALL_OUT_OBJ = $(foreach VAR,$(OBJS),$(addprefix $(LOCAL_OUT)/,$(VAR)))
ALL_OUT_LIBS = $(foreach VAR,$(LIBS),$(addprefix $(LOCAL_OUT)/,$(VAR)))

#===============================================================================
# rules
#===============================================================================
include $(HI_TEE_API_DIR)/stb_api.mak
