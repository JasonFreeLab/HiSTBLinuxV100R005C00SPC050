#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(shell cd $(CURDIR)/../../../../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

#===============================================================================
# directory
#===============================================================================
DFB_EXTERNAL_CURDIR = $(shell pwd)
DFB_EXTERNAL_SRC_CURDIR := .

DFB_DIR := $(HI_OUT_DIR)/obj/source/component/directfb
#===============================================================================
# local variable
#===============================================================================
CFLAGS  :=  -I$(HI_INCLUDE_DIR)      \
            -I$(DFB_EXTERNAL_CURDIR) \
            -I$(DFB_DIR)/DirectFB-1.6.1         \
            -I$(DFB_DIR)/DirectFB-1.6.1/lib     \
            -I$(DFB_DIR)/DirectFB-1.6.1/src     \
            -I$(DFB_DIR)/DirectFB-1.6.1/include \
            -I$(DFB_DIR)/linux-fusion-9.0.2/linux/include

#=====================================================================================
#add flags
#=====================================================================================
ifdef CFG_HI_STATIC_LIB_ONLY
CFLAGS += -fPIC
endif

#=====================================================================================
#hisi bluetooth source
#=====================================================================================
BLUETOOTH_SOURCES = $(DFB_EXTERNAL_SRC_CURDIR)/bluetooth.c

#=====================================================================================
#fbdev so
#=====================================================================================
SRCS := $(BLUETOOTH_SOURCES)
FILTER := -Werror
LIB_NAME := libdirectfb_hisi_bluetooth

include $(SDK_DIR)/hi_rules.mak
