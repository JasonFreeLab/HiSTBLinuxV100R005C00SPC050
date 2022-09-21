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
CFG_CIPHER_MINI_OR_NOT = y

EXTRA_CFLAGS += $(CFG_HI_KMOD_CFLAGS)

EXTRA_CFLAGS += -I$(MSP_UNF_INCLUDE)            \
                -I$(MSP_DRV_INCLUDE)            \
                -I$(COMMON_UNF_INCLUDE)         \
                -I$(COMMON_DRV_INCLUDE)

ifeq ($(CFG_HI_TEE_SUPPORT),y)
EXTRA_CFLAGS += -I$(TEE_DRV_INCLUDE)
endif

ifeq ($(CFG_HI_CPU_ARCH),arm64)
EXTRA_CFLAGS += -DHI_CPU_ARM64
endif

MOD_NAME := hi_cipher
obj-$(HI_DRV_BUILDTYPE) := $(MOD_NAME).o

ifeq ($(CFG_HI_CHIP_TYPE), hi3796mv200)
EXTRA_CFLAGS += -I$(MSP_DIR)/drv/cipher \
		-I$(MSP_DIR)/drv/cipher/cipher_v2    \
                -I$(MSP_DIR)/drv/cipher/cipher_v2/platform   \
                -I$(MSP_DIR)/drv/cipher/cipher_v2/rng     \
                -I$(MSP_DIR)/drv/cipher/cipher_v2/rsa     \
                -I$(MSP_DIR)/drv/cipher/cipher_v2/hdcp    \
                -I$(MSP_DIR)/drv/cipher/cipher_v2/spacc   \
                -I$(MSP_DIR)/drv/cipher/cipher_v2/sm2     \
                -I$(MSP_DIR)/drv/cipher/cenc

$(MOD_NAME)-y += cipher_v2/drv_cipher_intf.o
$(MOD_NAME)-y += cipher_v2/rng/drv_rng.o
$(MOD_NAME)-y += cipher_v2/rsa/drv_rsa.o
$(MOD_NAME)-y += cipher_v2/sm2/drv_sm2.o
$(MOD_NAME)-y += cipher_v2/sm2/hal_sm2.o
$(MOD_NAME)-y += cipher_v2/hdcp/drv_hdcp.o
$(MOD_NAME)-y += cipher_v2/spacc/spacc_body.o \
                 cipher_v2/spacc/spacc_intf.o
$(MOD_NAME)-y += cipher_v2/platform/cipher_adapt.o
$(MOD_NAME)-y += cipher_v2/platform/cipher_init.o
$(MOD_NAME)-y += drv_rsa_bignum.o drv_rsa.o
$(MOD_NAME)-y += cenc/drv_cenc.o
else
EXTRA_CFLAGS += -I$(MSP_DIR)/drv/cipher
EXTRA_CFLAGS += -I$(MSP_DIR)/drv/cipher/cenc
$(MOD_NAME)-y += drv_cipher.o hal_cipher.o drv_cipher_intf.o 
$(MOD_NAME)-y += drv_rsa_bignum.o drv_rsa.o
$(MOD_NAME)-y += cenc/drv_cenc.o
endif

ifeq ($(CFG_HI_TEE_SUPPORT),y)
EXTRA_CFLAGS += -DHI_TEE_SUPPORT
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
