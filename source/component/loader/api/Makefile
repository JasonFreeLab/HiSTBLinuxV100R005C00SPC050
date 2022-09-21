#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(shell cd $(CURDIR)/../../../.. && /bin/pwd)

include $(SDK_DIR)/base.mak
endif

ifeq ($(CFG_HI_LOADER_APPLOADER),y)
CFLAGS := -DHI_LOADER_RUNNING_ENVIRONMENT_APPLOADER
else
CFLAGS := -DHI_LOADER_RUNNING_ENVIRONMENT_MAINSYSTEM
endif

#===============================================================================
# local variable
#===============================================================================
CFLAGS += -I$(CURDIR)/include
CFLAGS += -I$(CURDIR)/src
CFLAGS += -I$(CURDIR)/src/harden/include
CFLAGS += -I$(MSP_DIR)/api/higo/include

SRCS :=  src/loader_osal.c
SRCS +=  src/loader_flash.c
SRCS +=  src/loader_dbinfo.c
SRCS +=  src/hi_loader_info.c
SRCS +=  src/hi_loader_info_v2.c

ifeq ($(CFG_HI_ADVCA_SUPPORT),y)
ifeq ($(CFG_HI_ADVCA_TYPE), CONAX)
CFLAGS += -I$(CURDIR)/src/harden/conax
SRCS +=  src/harden/conax/cx_harden.c
SRCS +=  src/harden/conax/cx_verify.c
else ifeq ($(CFG_HI_ADVCA_TYPE), VERIMATRIX)
CFLAGS += -I$(CURDIR)/src/harden/vmx_advance
CFLAGS += -I$(CURDIR)/src/harden/vmx_advance/3rd_loader_verify_lib
CFLAGS += -I$(CURDIR)/src/harden/vmx_advance/vmx_loader_verify_lib
CFLAGS += -I$(CURDIR)/src/harden/crc
SRCS += src/harden/crc/crc_harden.c
else ifeq ($(CFG_HI_ADVCA_TYPE), VERIMATRIX_ULTRA)
CFLAGS += -I$(CURDIR)/src/harden/vmx_ultra
CFLAGS += -I$(CURDIR)/src/harden/crc
SRCS += src/harden/vmx_ultra/vmx_verify.c
SRCS += src/harden/crc/crc_harden.c
else ifeq ($(CFG_HI_ADVCA_TYPE), NAGRA)
CFLAGS += -I$(CURDIR)/src/harden/crc
CFLAGS += -I$(CURDIR)/src/harden/nagra
SRCS += src/harden/nagra/nagra_verify.c
SRCS += src/harden/crc/crc_harden.c
else
CFLAGS += -I$(CURDIR)/src/harden/crc
SRCS += src/harden/crc/crc_harden.c
endif
else
CFLAGS += -I$(CURDIR)/src/harden/crc
SRCS += src/harden/crc/crc_harden.c
endif

LIB_NAME := libhiloader

HEADER_FILES := $(CURDIR)/include/hi_loader_info.h
HEADER_FILES += $(CURDIR)/include/hi_loader_info_v2.h

include $(SDK_DIR)/hi_rules.mak
