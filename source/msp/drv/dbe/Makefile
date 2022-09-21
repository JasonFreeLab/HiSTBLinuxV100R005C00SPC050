#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
    ifneq ($(srctree),)
        KERNEL_DIR := $(srctree)

        SDK_DIR := $(KERNEL_DIR)/../../..
    else
        SDK_DIR := $(CURDIR)/../../../..
    endif

    include $(SDK_DIR)/base.mak
endif

##########################################################################################
#	prepare param
##########################################################################################
export CUR_DIR=$(shell pwd)
export ARCH=$(CFG_HI_CPU_ARCH)
export KDIR=$(LINUX_DIR)
export CROSS_COMPILE=$(HI_KERNEL_TOOLCHAINS_NAME)-

##########################################################################################
#	set task
##########################################################################################
all:
	$(MAKE) ARCH=$(ARCH) -C $(KDIR) M=$(CURDIR) EXTRA_CFLAGS="-I$(CURDIR)/../../../include" CONFIG_HI_DMA_BUFFER_EXPORTER=$(HI_DRV_BUILDTYPE)
clean:
	$(MAKE) ARCH=$(ARCH) -C $(KDIR) M=$(CURDIR) clean

