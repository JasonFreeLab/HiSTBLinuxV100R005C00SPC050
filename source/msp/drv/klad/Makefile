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

KLAD_VERSION :=v200

#===============================================================================
# local variable
#===============================================================================
EXTRA_CFLAGS += $(CFG_HI_KMOD_CFLAGS)

EXTRA_CFLAGS += -I$(COMMON_UNF_INCLUDE)             \
                -I$(COMMON_API_INCLUDE)             \
                -I$(COMMON_DRV_INCLUDE)             \
                -I$(MSP_UNF_INCLUDE)                \
                -I$(MSP_API_INCLUDE)                \
                -I$(MSP_DRV_INCLUDE)                \
                -I$(MSP_DIR)/drv/klad               \
                -I$(MSP_DIR)/drv/klad/basic         \
                -I$(MSP_DIR)/drv/klad/include       \
                -I$(MSP_DIR)/drv/klad/basic/include \
                -I$(MSP_DIR)/drv/klad/basic/$(KLAD_VERSION)     \
                -I$(MSP_DIR)/drv/klad/common_ca/$(KLAD_VERSION) \
                -I$(MSP_DIR)/drv/klad/common_ca/include

ifeq ($(CFG_HI_TEE_SUPPORT),y)
EXTRA_AFLAGS += -DHI_TEE_SUPPORT
endif

MOD_NAME := hi_advca

obj-$(HI_DRV_BUILDTYPE) += $(MOD_NAME).o

$(MOD_NAME)-y := drv_klad_intf.o \
                 basic/drv_klad_basic.o \
                 basic/$(KLAD_VERSION)/hal_klad_basic.o \
                 basic/$(KLAD_VERSION)/hal_klad.o \
                 framework/drv_klad.o

ifeq ($(CFG_HI_PROC_SUPPORT),y)
$(MOD_NAME)-y +=    drv_klad_proc.o
endif

ifeq ($(CFG_ADVCA_CONAX),y)
	EXTRA_CFLAGS += -DHI_ADVCA_CONAX_SUPPORT
	EXTRA_CFLAGS += -I$(MSP_DIR)/drv/klad/conax/include
	$(MOD_NAME)-y += conax/drv_klad_conax.o  \
                     conax/$(KLAD_VERSION)/hal_klad_conax.o
endif

ifeq ($(CFG_ADVCA_NAGRA),y)
	EXTRA_CFLAGS += -DHI_ADVCA_NAGRA_SUPPORT
	EXTRA_CFLAGS += -I$(MSP_DIR)/drv/klad/nagra/include
	EXTRA_CFLAGS += -I$(MSP_DIR)/drv/klad/nagra/$(KLAD_VERSION)
	$(MOD_NAME)-y += nagra/drv_klad_nagra.o  \
                     nagra/$(KLAD_VERSION)/hal_klad_nagra.o
endif

ifeq ($(CFG_ADVCA_VERIMATRIX),y)
	EXTRA_CFLAGS += -DHI_ADVCA_VERIMATRIX_SUPPORT
	EXTRA_CFLAGS += -I$(MSP_DIR)/drv/klad/verimatrix/include
	$(MOD_NAME)-y += verimatrix/drv_klad_verimatrix.o  \
                     verimatrix/$(KLAD_VERSION)/hal_klad_verimatrix.o
endif

ifeq ($(CFG_ADVCA_IRDETO),y)
	EXTRA_CFLAGS += -DHI_ADVCA_IRDETO_SUPPORT
	EXTRA_CFLAGS += -I$(MSP_DIR)/drv/klad/irdeto/include
	$(MOD_NAME)-y += irdeto/drv_klad_irdeto.o  \
                     irdeto/$(KLAD_VERSION)/hal_klad_irdeto.o
endif

ifeq ($(CFG_ADVCA_DCAS),y)
	EXTRA_CFLAGS += -DHI_ADVCA_DCAS_SUPPORT
	EXTRA_CFLAGS += -I$(MSP_DIR)/drv/klad/dcas/include
	$(MOD_NAME)-y += dcas/drv_klad_dcas.o  \
                     dcas/$(KLAD_VERSION)/hal_klad_dcas.o
endif

ifeq ($(CFG_ADVCA_NOVEL),y)
	EXTRA_CFLAGS += -DHI_ADVCA_COMMON_CA_SUPPORT
	EXTRA_CFLAGS += -I$(MSP_DIR)/drv/klad/common_ca/include
	$(MOD_NAME)-y += common_ca/drv_klad_common_ca.o  \
                     common_ca/$(KLAD_VERSION)/hal_klad_common_ca.o
endif

ifeq ($(CFG_ADVCA_CTI),y)
	EXTRA_CFLAGS += -DHI_ADVCA_COMMON_CA_SUPPORT
	EXTRA_CFLAGS += -I$(MSP_DIR)/drv/klad/common_ca/include
	$(MOD_NAME)-y += common_ca/drv_klad_common_ca.o  \
                     common_ca/$(KLAD_VERSION)/hal_klad_common_ca.o
endif

ifeq ($(CFG_ADVCA_SUMA),y)
	EXTRA_CFLAGS += -DHI_ADVCA_COMMON_CA_SUPPORT
	EXTRA_CFLAGS += -I$(MSP_DIR)/drv/klad/common_ca/include
	$(MOD_NAME)-y += common_ca/drv_klad_common_ca.o  \
                     common_ca/$(KLAD_VERSION)/hal_klad_common_ca.o
endif

ifeq ($(CFG_ADVCA_PANACCESS),y)
	EXTRA_CFLAGS += -DHI_ADVCA_COMMON_CA_SUPPORT
	EXTRA_CFLAGS += -I$(MSP_DIR)/drv/klad/common_ca/include
	$(MOD_NAME)-y += common_ca/drv_klad_common_ca.o  \
                     common_ca/$(KLAD_VERSION)/hal_klad_common_ca.o
endif

BUILD_DIR := $(HI_OUT_DIR)/$(OBJ_NAME)/$(subst $(SDK_DIR)/,,$(CURDIR))

BUILD_DIR_MAKEFILE := $(BUILD_DIR)/Makefile

CERT_TYPE_DIR = nagra/cert

#===============================================================================
#   rules
#===============================================================================
.PHONY: all clean

all: $(BUILD_DIR_MAKEFILE)
	$(AT)make -C $(LINUX_DIR) ARCH=$(CFG_HI_CPU_ARCH) CROSS_COMPILE=$(HI_KERNEL_TOOLCHAINS_NAME)- M=$(BUILD_DIR) src=$(CURDIR) modules
	$(AT)test -d $(HI_MODULE_DIR) || mkdir -p $(HI_MODULE_DIR)
	$(AT)cp -f $(BUILD_DIR)/$(MOD_NAME).ko $(HI_MODULE_DIR)/
ifeq ($(CFG_ADVCA_NAGRA),y)
	$(AT)make -C $(CERT_TYPE_DIR) all
endif
clean:
	$(AT)make -C $(LINUX_DIR) ARCH=$(CFG_HI_CPU_ARCH) CROSS_COMPILE=$(HI_KERNEL_TOOLCHAINS_NAME)- M=$(BUILD_DIR) src=$(CURDIR) clean
	$(AT)rm -rf $(HI_MODULE_DIR)/$(MOD_NAME).ko
ifeq ($(CFG_ADVCA_NAGRA),y)
	$(AT)make -C $(CERT_TYPE_DIR) clean
endif

$(BUILD_DIR_MAKEFILE): $(BUILD_DIR)
	$(AT)touch $@

$(BUILD_DIR):
	$(AT)mkdir -p $@
