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
obj-y += sil9293/

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean

all:
	$(AT)make -C sil9293

clean:
	$(AT)make -C sil9293 clean

