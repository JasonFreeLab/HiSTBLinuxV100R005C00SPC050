#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
    ifneq ($(srctree),)
    KERNEL_DIR := $(srctree)

    SDK_DIR := $(shell cd $(KERNEL_DIR)/../../.. && /bin/pwd)
    else
    SDK_DIR := $(shell cd $(CURDIR)/../../../../../../.. && /bin/pwd)
    endif

    include $(SDK_DIR)/base.mak
endif

#===============================================================================
# export variables  arm64 or arm
#===============================================================================
########tmp value###############################
ifeq ($(CFG_HI_CPU_ARCH),arm)
EXTRA_CFLAGS += -DHI_VFMW_32BIT
endif
# local variables
#===============================================================================
VFMW_DIR := $(MSP_DIR)/drv/vfmw/vfmw_v5.0

EXTRA_CFLAGS += $(filter-out -Wformat-security,$(CFG_HI_KMOD_CFLAGS))

EXTRA_CFLAGS += -I$(COMMON_UNF_INCLUDE)    \
                -I$(COMMON_DRV_INCLUDE)

ifeq ($(CFG_HI_TEE_SUPPORT),y)
EXTRA_CFLAGS += -I$(TEE_DRV_INCLUDE)
endif

ifeq ($(CFG_HI_HDR_SUPPORT),y)
EXTRA_CFLAGS += -DVFMW_HDR_SUPPORT
endif

################################################################################################
#    PRODUCT
################################################################################################
ifeq ($(CFG_HI_CHIP_TYPE), hi3798cv200)
include $(VFMW_DIR)/product/Hi3798CV200/LNX_CFG/vfmw_make.cfg
endif
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv200 hi3798mv300),)
include $(VFMW_DIR)/product/Hi3798MV200/LNX_CFG/vfmw_make.cfg
endif
ifeq ($(CFG_HI_CHIP_TYPE), hi3796mv200)
include $(VFMW_DIR)/product/Hi3796MV200/LNX_CFG/vfmw_make.cfg
endif
ifeq ($(CFG_HI_CHIP_TYPE), hi3796mv200)
ifeq ($(CFG_HI_NVR_SUPPORT),y)
include $(VFMW_DIR)/product/Hi3796MV200_NVR/LNX_CFG/vfmw_make.cfg
else
include $(VFMW_DIR)/product/Hi3796MV200/LNX_CFG/vfmw_make.cfg
endif
endif

EXTRA_CFLAGS += $(VFMW_CFLAGS)
EXTRA_CFLAGS += -fno-pic

ifeq ($(CFG_HI_SMMU_SUPPORT), y)
EXTRA_CFLAGS += -DVFMW_MMU_SUPPORT
endif

EXTRA_CFLAGS += -DVFMW_STB_PRODUCT

ifeq ($(CFG_ADVCA_VERIMATRIX_ULTRA), y)
EXTRA_CFLAGS += -DHI_ULTRA_V_MX
endif

MOD_NAME := hi_vfmw

obj-$(HI_DRV_BUILDTYPE) += $(MOD_NAME).o

$(MOD_NAME)-y := $(VFMW_OBJS)

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
	$(AT)make -C $(LINUX_DIR) ARCH=$(CFG_HI_CPU_ARCH) CROSS_COMPILE=$(HI_KERNEL_TOOLCHAINS_NAME)- M=$(BUILD_DIR)/../.. src=$(CURDIR) clean
	$(AT)rm -rf $(HI_MODULE_DIR)/$(MOD_NAME).ko

$(BUILD_DIR_MAKEFILE): $(BUILD_DIR)
	$(AT)touch $@

$(BUILD_DIR):
	$(AT)mkdir -p $@


#===============================================================================
#   Generate asm
#===============================================================================
asm:
	make -f asm.mak asm SYSTEM_CONFIG=64bit
	make -f asm.mak asm SYSTEM_CONFIG=32bit

asm_clean: 
	make -f asm.mak asm_clean SYSTEM_CONFIG=64bit
	make -f asm.mak asm_clean SYSTEM_CONFIG=32bit
