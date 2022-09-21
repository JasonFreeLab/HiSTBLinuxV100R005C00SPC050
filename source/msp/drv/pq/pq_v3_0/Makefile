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

VERSION := pq_v3_0
MOD_NAME := hi_pq

HAL_DIR := hal
MNG_DIR := mng

obj-$(HI_DRV_BUILDTYPE) += $(MOD_NAME).o

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv100 hi3796mv100 hi3716dv100),)
CHIP := hi3798mv100

$(MOD_NAME)-y :=  $(MNG_DIR)/pq_mng_dbdr.o
$(MOD_NAME)-y +=  $(MNG_DIR)/pq_mng_sharpen.o
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716mv410 hi3716mv420),)
CHIP := 3716mv410

$(MOD_NAME)-y :=  $(MNG_DIR)/pq_mng_dbdm.o
$(MOD_NAME)-y +=  $(MNG_DIR)/pq_mng_dbdm_alg.o
$(MOD_NAME)-y +=  $(HAL_DIR)/$(CHIP)/pq_hal_tnr.o
$(MOD_NAME)-y +=  $(HAL_DIR)/$(CHIP)/pq_hal_deshoot.o
$(MOD_NAME)-y +=  $(MNG_DIR)/pq_mng_sharpen.o
$(MOD_NAME)-y +=  $(MNG_DIR)/pq_mng_tnr.o
$(MOD_NAME)-y +=  $(MNG_DIR)/pq_mng_deshoot.o
endif

#===============================================================================
# local variables
#===============================================================================
EXTRA_CFLAGS += $(CFG_HI_KMOD_CFLAGS)

EXTRA_CFLAGS += -I$(COMMON_UNF_INCLUDE)                 \
                -I$(COMMON_API_INCLUDE)                 \
                -I$(COMMON_DRV_INCLUDE)                 \
                -I$(MSP_UNF_INCLUDE)                    \
                -I$(MSP_API_INCLUDE)                    \
                -I$(MSP_DRV_INCLUDE)                    \
                -I$(MSP_DRV_REG_INCLUDE)                \
                -I$(MSP_DIR)/api/pq/include             \
                -I$(MSP_DIR)/api/higo/include           \
                -I$(MSP_DIR)/drv/pq/$(VERSION)/mng      \
                -I$(MSP_DIR)/drv/pq/$(VERSION)/hal/$(CHIP) \
                -I$(MSP_DIR)/drv/pq/$(VERSION)/hal/common  \
                -I$(MSP_DIR)/drv/pq/$(VERSION)


$(MOD_NAME)-y +=    drv_pq_intf.o   \
                    drv_pq.o   \
                    drv_pq_table.o

$(MOD_NAME)-y +=    $(HAL_DIR)/common/pq_hal_comm.o             \
                    $(HAL_DIR)/$(CHIP)/pq_hal_acm.o             \
                    $(HAL_DIR)/$(CHIP)/pq_hal_csc.o             \
                    $(HAL_DIR)/$(CHIP)/pq_hal_dci.o             \
                    $(HAL_DIR)/$(CHIP)/pq_hal_dei.o             \
                    $(HAL_DIR)/$(CHIP)/pq_hal_dbdr.o            \
                    $(HAL_DIR)/$(CHIP)/pq_hal_sharpen.o         \
                    $(HAL_DIR)/$(CHIP)/pq_hal_zme.o             \
                    $(HAL_DIR)/$(CHIP)/pq_hal_fmd.o             \
                    $(HAL_DIR)/$(CHIP)/pq_hal_sr.o

$(MOD_NAME)-y +=    $(MNG_DIR)/pq_mng_acm.o             \
                    $(MNG_DIR)/pq_mng_csc.o             \
                    $(MNG_DIR)/pq_mng_dci.o             \
                    $(MNG_DIR)/pq_mng_dei.o             \
                    $(MNG_DIR)/pq_mng_zme.o             \
                    $(MNG_DIR)/pq_mng_ifmd.o            \
                    $(MNG_DIR)/pq_mng_ifmd_alg.o        \
                    $(MNG_DIR)/pq_mng_sr.o

asflags-y := -I$(COMMON_DRV_INCLUDE)
ifeq ($(findstring -DHI_ADVCA_FUNCTION_RELEASE, $(CFG_HI_CFLAGS)), -DHI_ADVCA_FUNCTION_RELEASE)
asflags-y += -DCONFIG_REMOVE_STRING
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

