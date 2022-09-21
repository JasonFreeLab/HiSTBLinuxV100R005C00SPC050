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
LOCAL_OUT := $(OUT)/api/cipher
else
LOCAL_OUT := $(shell pwd)
endif

LIBS    := libsec_api_$(notdir $(LOCAL_OUT)).a

ifeq ($(CFG_HI_CHIP_TYPE), hi3796mv200)
CFG_HI_CIPHER_OPTIMIZ ?= y
endif

ifeq ($(CFG_HI_CIPHER_OPTIMIZ),y)
include v3/build.mak
OBJS   += $(CIPHER_OBJ)
CFLAGS += $(CIPHER_INS)
else
ifeq ($(CFG_HI_CHIP_TYPE), hi3796mv200)
OBJS := v2/hi_tee_cipher.o
OBJS += v2/tee_mpi_cipher.o
OBJS += v2/tee_mpi_hash.o
OBJS += v2/tee_mpi_rsa.o
OBJS += v2/tee_mpi_rng.o
OBJS += v2/tee_mpi_sm2.o
OBJS += v2/cipher_osal.o
else
OBJS := hi_tee_cipher.o
endif
endif

CFLAGS += -Werror -Wall

ALL_OUT_OBJ = $(foreach VAR,$(OBJS),$(addprefix $(LOCAL_OUT)/,$(VAR)))
ALL_OUT_LIBS = $(foreach VAR,$(LIBS),$(addprefix $(LOCAL_OUT)/,$(VAR)))

#===============================================================================
# rules
#===============================================================================
include $(HI_TEE_API_DIR)/stb_api.mak
