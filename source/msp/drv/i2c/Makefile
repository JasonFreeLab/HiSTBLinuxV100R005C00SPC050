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
obj-y += std_i2c/

ifeq ($(CFG_HI_GPIOI2C_SUPPORT),y)
obj-y += gpio_i2c/
endif

#=================================================================
#	  rules
#=================================================================
.PHONY: all clean

all: ${objects}
	$(AT)make -C std_i2c
ifeq ($(CFG_HI_GPIOI2C_SUPPORT),y)
	$(AT)make -C gpio_i2c
endif

clean:
	$(AT)make -C std_i2c clean
ifeq ($(CFG_HI_GPIOI2C_SUPPORT),y)
	$(AT)make -C gpio_i2c clean
endif
