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
ifeq ($(CFG_HI_ADAC_SLIC_SUPPORT),y)
obj-y += slic/
endif

ifeq ($(CFG_HI_ADAC_TVL320AIC31_SUPPORT),y)
obj-y += tlv320aic31/
endif

#=================================================================
#	  rules
#=================================================================
.PHONY: all clean

all:
ifeq ($(CFG_HI_ADAC_SLIC_SUPPORT),y)
	$(AT)make -C slic
endif
ifeq ($(CFG_HI_ADAC_TVL320AIC31_SUPPORT),y)
	$(AT)make -C tlv320aic31
endif

clean:
ifeq ($(CFG_HI_ADAC_SLIC_SUPPORT),y)
	$(AT)make -C slic clean
endif
ifeq ($(CFG_HI_ADAC_TVL320AIC31_SUPPORT),y)
	$(AT)make -C tlv320aic31 clean
endif
