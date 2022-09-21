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
VENC_DIR := $(MSP_DIR)/drv/venc/venc_v2.0
#===============================================================================
# local variables
#===============================================================================
ifeq ($(CFG_HI_64BIT_SYSTEM),y)
ASM_DST_DIR := 64Bit
else
ASM_DST_DIR := 32Bit
endif

EXTRA_CFLAGS += $(filter-out -Wformat-security,$(CFG_HI_KMOD_CFLAGS))

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv200 hi3798mv300 hi3798mv200_a),)
include $(VENC_DIR)/firmware/product/Hi3798MV200/$(ASM_DST_DIR)/venc_make.cfg
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3796mv200),)
include $(VENC_DIR)/firmware/product/Hi3796MV200/$(ASM_DST_DIR)/venc_make.cfg
endif
EXTRA_CFLAGS += $(VENC_CFLAGS)


EXTRA_CFLAGS += -I$(COMMON_UNF_INCLUDE)                 \
                -I$(COMMON_API_INCLUDE)                 \
                -I$(COMMON_DRV_INCLUDE)                 \
                -I$(MSP_UNF_INCLUDE)                    \
                -I$(MSP_API_INCLUDE)                    \
                -I$(MSP_DRV_INCLUDE)                    \
                -I$(MSP_DIR)/api/venc                   \
                -I$(MSP_DIR)/drv/venc                   \
                -I$(MSP_DIR)/drv/jpge/include           \
                -I$(MSP_DIR)/api/jpge/include

MOD_NAME := hi_venc

obj-$(HI_DRV_BUILDTYPE) += $(MOD_NAME).o

$(MOD_NAME)-y := $(venc_obj_list)


#===============================================================================#       
asflags-y := -I$(COMMON_DRV_INCLUDE)
ifeq ($(findstring -DHI_ADVCA_FUNCTION_RELEASE, $(CFG_HI_CFLAGS)), -DHI_ADVCA_FUNCTION_RELEASE)
asflags-y += -DCONFIG_REMOVE_STRING
endif
#===============================================================================

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

