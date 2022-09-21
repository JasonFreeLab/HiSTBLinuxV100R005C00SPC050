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
# local variable
#===============================================================================
ifeq ($(CFG_HI_IR_TYPE_STD), y)
IR_DIR := ir_std
endif

ifeq ($(CFG_HI_IR_TYPE_S2), y)
IR_DIR := ir_s2
endif

ifeq ($(CFG_HI_IR_TYPE_LIRC),y)
IR_DIR := lirc
endif

obj-y += $(IR_DIR)/

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean

all:    
	$(AT)make -C $(IR_DIR) all

clean:
	$(AT)make -C $(IR_DIR) clean
