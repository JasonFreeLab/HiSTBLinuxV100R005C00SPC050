#=======================================
#	export variable
#=======================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
    ifneq ($(srctree),)
    KERNEL_DIR := $(srctree)

    SDK_DIR := $(shell cd $(KERNEL_DIR)/../../.. && /bin/pwd)
    else
    SDK_DIR := $(shell cd $(CURDIR)/../../../.. && /bin/pwd)
    endif

    include $(SDK_DIR)/base.mak
endif

OTP_DIR := v200
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716dv100 hi3716mv410 hi3716mv420 hi3796mv100 hi3798cv200 hi3798mv100 hi3798mv200 hi3798mv300 hi3798mv200_a),)
    OTP_DIR := v100
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716mv410 hi3716mv420),)
    ifeq ($(CFG_HI_ADVCA_TYPE),NAGRA)
        OTP_DIR := v200
    endif
endif



obj-y += $(OTP_DIR)/

#===============================================================================
#   rules
#===============================================================================
.PHONY: all clean

all: 
	$(AT)make -C $(OTP_DIR) all

clean:
	$(AT)make -C $(OTP_DIR) clean
