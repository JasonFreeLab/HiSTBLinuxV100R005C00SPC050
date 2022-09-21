#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../.. && /bin/pwd)

ifeq ($(wildcard $(SDK_DIR)/base.mak),$(SDK_DIR)/base.mak)
include $(SDK_DIR)/base.mak
endif
endif

#===============================================================================
# local variable
#===============================================================================
CFLAGS += $(CFG_HI_CFLAGS)

ADVCA_COMPILE_FLAG=FALSE

ifndef ADVCA_DIR
ADVCA_DIR = $(COMPONENT_DIR)/advca
endif

ifeq ($(CFG_HI_ADVCA_TYPE), NAGRA)
CFG_ADVCA_PATH_NAME = nagra
ADVCA_TYPE_DIR = nagra

ADVCA_COMMON_DIR = $(ADVCA_DIR)/common
ADVCA_COMMON_SRC_DIR = $(ADVCA_DIR)/common_src
export SDK_DIR ADVCA_DIR ADVCA_TYPE_DIR ADVCA_COMMON_SRC_DIR ADVCA_COMMON_DIR CFG_ADVCA_PATH_NAME
ADVCA_COMPILE_FLAG=TRUE
endif

ifeq ($(CFG_HI_ADVCA_TYPE), VERIMATRIX_ULTRA)
ifeq ($(CFG_HI_CHIP_TYPE), hi3798mv200)
CFG_ADVCA_PATH_NAME = vmx/ultra/HI3798CV200_I/hi_vmx_adapter
ADVCA_TYPE_DIR = vmx/ultra/HI3798CV200_I/hi_vmx_adapter
ADVCA_COMMON_DIR = $(ADVCA_DIR)/vmx/ultra/HI3798CV200_I
ADVCA_COMMON_SRC_DIR = $(ADVCA_DIR)/vmx/ultra/HI3798CV200_I/hi_vmx_adapter
ADVCA_COMPILE_FLAG=TRUE
endif
endif

ifeq ($(ADVCA_COMPILE_FLAG), TRUE)

export SDK_DIR ADVCA_DIR ADVCA_TYPE_DIR ADVCA_COMMON_SRC_DIR ADVCA_COMMON_DIR CFG_ADVCA_PATH_NAME
#===============================================================================
# rules
#===============================================================================
.PHONY : all clean install uninstall

all :
	make -C $(ADVCA_TYPE_DIR) all

clean:
	make -C $(ADVCA_TYPE_DIR) clean

install:
	make -C $(ADVCA_TYPE_DIR) install

uninstall: clean
	make -C $(ADVCA_TYPE_DIR) uninstall

else
all :
	echo "done"

clean:
	echo "done"   

install:
	echo "done" 

uninstall: clean
	echo "done" 
endif

