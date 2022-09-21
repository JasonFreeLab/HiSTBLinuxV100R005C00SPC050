#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
    ifneq ($(srctree),)
    KERNEL_DIR := $(srctree)

    SDK_DIR := $(shell cd $(KERNEL_DIR)/../../.. && /bin/pwd)
    else
    SDK_DIR := $(shell cd $(CURDIR)/../../../../.. && /bin/pwd)
    endif

    include $(SDK_DIR)/base.mak
endif

#===============================================================================
# local variables
#===============================================================================
EXTRA_CFLAGS += -I$(COMMON_UNF_INCLUDE)                 \
                -I$(COMMON_API_INCLUDE)                 \
                -I$(COMMON_DRV_INCLUDE)                 \
                -I$(MSP_UNF_INCLUDE)                    \
                -I$(MSP_API_INCLUDE)                    \
                -I$(MSP_DRV_INCLUDE)

EXTRA_CFLAGS += $(CFG_HI_KMOD_CFLAGS)


MOD_NAME := hi_ir

obj-$(HI_DRV_BUILDTYPE) += $(MOD_NAME).o

$(MOD_NAME)-y   :=  drv_ir_intf.o

$(MOD_NAME)-y   +=  drv_ir_intf.o drv_ir_protocol_entry.o drv_ir_utils.o

ifeq ($(CFG_HI_IR_NEC_SUPPORT), y)
$(MOD_NAME)-y += drv_ir_nec.o
EXTRA_CFLAGS += -DNEC_SUPPORT
endif

ifeq ($(CFG_HI_IR_RC6_SUPPORT), y)
$(MOD_NAME)-y += drv_ir_rc6.o
EXTRA_CFLAGS += -DRC6_SUPPORT
endif

ifeq ($(CFG_HI_IR_RC5_SUPPORT), y)
$(MOD_NAME)-y += drv_ir_rc5.o
EXTRA_CFLAGS += -DRC5_SUPPORT
endif

ifeq ($(CFG_HI_IR_SONY_SUPPORT), y)
$(MOD_NAME)-y += drv_ir_sony.o
EXTRA_CFLAGS += -DSONY_SUPPORT
endif

ifeq ($(CFG_HI_IR_TC9012_SUPPORT), y)
$(MOD_NAME)-y += drv_ir_tc9012.o
EXTRA_CFLAGS += -DTC9012_SUPPORT
endif

ifeq ($(CFG_HI_IR_CREDIT_SUPPORT), y)
$(MOD_NAME)-y += drv_ir_credit.o
EXTRA_CFLAGS += -DCREDIT_SUPPORT
endif

BUILD_DIR := $(HI_OUT_DIR)/$(OBJ_NAME)/$(subst $(SDK_DIR)/,,$(CURDIR))

BUILD_DIR_MAKEFILE := $(BUILD_DIR)/Makefile

#===============================================================================
#   rules
#===============================================================================
.PHONY: all clean

all: $(BUILD_DIR_MAKEFILE)
	$(AT)make -C $(LINUX_DIR) ARCH=$(CFG_HI_CPU_ARCH) CROSS_COMPILE=$(HI_KERNEL_TOOLCHAINS_NAME)- M=$(BUILD_DIR) src=$(CURDIR) modules
	$(AT)test -d $(HI_MODULE_DIR) || mkdir -p $(HI_MODULE_DIR)
	$(AT)cp -f $(BUILD_DIR)/$(MOD_NAME).ko $(HI_MODULE_DIR)/

clean:
	$(AT)make -C $(LINUX_DIR) ARCH=$(CFG_HI_CPU_ARCH) CROSS_COMPILE=$(HI_KERNEL_TOOLCHAINS_NAME)- M=$(BUILD_DIR) src=$(CURDIR) clean
	$(AT)rm -rf $(HI_MODULE_DIR)/$(MOD_NAME).ko

$(BUILD_DIR_MAKEFILE): $(BUILD_DIR)
	$(AT)touch $@

$(BUILD_DIR):
	$(AT)mkdir -p $@

