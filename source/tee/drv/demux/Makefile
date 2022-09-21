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
LOCAL_OUT := $(OUT)/drv/demux
else
LOCAL_OUT := $(shell pwd)
endif

LIBS    :=  libsec_$(notdir $(LOCAL_OUT)).a
OBJS    :=  tee_drv_demux.o \
            tee_drv_demux_func.o  \
            tee_drv_demux_index.o \
            tee_hal_demux.o

CFLAGS += -I$(HI_TEE_API_DIR)/demux
CFLAGS += -I$(TRUSTEDCORE_DIR)/platform/devchip/$(PLATFORM_DIR_NAME)/include

ALL_OUT_OBJ = $(foreach VAR,$(OBJS),$(addprefix $(LOCAL_OUT)/,$(VAR)))
ALL_OUT_LIBS = $(foreach VAR,$(LIBS),$(addprefix $(LOCAL_OUT)/,$(VAR)))

#===============================================================================
# rules
#===============================================================================
include $(HI_TEE_DRV_DIR)/stb_drv.mak
