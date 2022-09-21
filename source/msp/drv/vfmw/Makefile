#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
    ifneq ($(srctree),)
    KERNEL_DIR := $(srctree)

    SDK_DIR := $(shell cd $(KERNEL_DIR)/../../.. && /bin/pwd)
    else
    SDK_DIR := $(shell cd $(CURDIR)/../../../.. && /bin/pwd)
    endif

    include $(SDK_DIR)/base.mak
endif

#===============================================================================
# local variables
#===============================================================================
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798cv200 hi3798mv200 hi3798mv300 hi3798mv200_a hi3796mv200),)
VFMW_MAKE_DIR = vfmw_v5.0/product/make_stb
else
VFMW_MAKE_DIR = vfmw_v4.0
endif

obj-y += $(VFMW_MAKE_DIR)/

ifeq ($(CFG_HI_VDEC_SVDEC_SUPPORT),y)
obj-y += softlib/
endif

#===============================================================================
#   rules
#===============================================================================
.PHONY: all clean

all:
	$(AT)make -C $(VFMW_MAKE_DIR)/ all
ifeq ($(CFG_HI_VDEC_SVDEC_SUPPORT),y)
	$(AT)make -C softlib/ all
endif

clean:
	$(AT)make -C $(VFMW_MAKE_DIR)/ clean
ifeq ($(CFG_HI_VDEC_SVDEC_SUPPORT),y)
	$(AT)make -C softlib/ clean
endif

