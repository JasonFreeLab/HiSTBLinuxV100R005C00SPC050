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

#=======================================
#	local variable
#=======================================
obj-y += adsp_v1_1/

#=================================================================
#	  rules
#=================================================================
.PHONY: all clean

all:
	$(AT)make -C adsp_v1_1

clean:
	$(AT)make -C adsp_v1_1 clean
