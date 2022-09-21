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
LOCAL_OUT := $(OUT)/drv/common
else
LOCAL_OUT := $(shell pwd)
endif

LIBS    := libsec_$(notdir $(LOCAL_OUT)).a
OBJS    := tee_drv_common.o

ASM_MEM_SRC = \
	asm_mem/memmove.o \
	asm_mem/memcpy.o

OBJS += $(ASM_MEM_SRC)

ifeq ($(strip $(CFG_HI_TEE_RPMB_KEY_SUPPORT)), y)
OBJS += tee_drv_rpmb.o
endif

ALL_OUT_OBJ = $(foreach VAR,$(OBJS),$(addprefix $(LOCAL_OUT)/,$(VAR)))
ALL_OUT_LIBS = $(foreach VAR,$(LIBS),$(addprefix $(LOCAL_OUT)/,$(VAR)))
CFLAGS += -I$(TRUSTEDCORE_DIR)/platform/devchip/${PLATFORM_DIR_NAME}/include
#===============================================================================
# rules
#===============================================================================
include $(HI_TEE_DRV_DIR)/stb_drv.mak
