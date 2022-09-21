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
            -I$(DFB_EXTERNAL_CURDIR)/../../systems/fbdev  \
            -I$(DFB_DIR)/linux-fusion-9.0.2/linux/include \
            -I$(MSP_DIR)/drv/hifb/include

#=====================================================================================
#add flags
#=====================================================================================
ifdef CFG_HI_STATIC_LIB_ONLY
CFLAGS += -fPIC
endif

#=====================================================================================
#hisi gfx2d source
#=====================================================================================
GFX2D_SOURCES = $(DFB_EXTERNAL_SRC_CURDIR)/hi_primary.c   \
                $(DFB_EXTERNAL_SRC_CURDIR)/hisi_layer.c   \
                $(DFB_EXTERNAL_SRC_CURDIR)/tde_2d.c       \
                $(DFB_EXTERNAL_SRC_CURDIR)/tde_driver.c   \
                $(DFB_EXTERNAL_SRC_CURDIR)/tde_gfxdriver.c

#=====================================================================================
#fbdev so
#=====================================================================================
SRCS := $(GFX2D_SOURCES)
FILTER := -Werror
LIB_NAME := libdirectfb_hisi_gfx2d

include $(SDK_DIR)/hi_rules.mak
