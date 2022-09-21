###############################################################################
# export variables
###############################################################################
ifeq ($(CFG_HI_EXPORT_FLAG),)
    ifneq ($(srctree),)
    KERNEL_DIR := $(srctree)

    SDK_DIR := $(shell cd $(KERNEL_DIR)/../../.. && /bin/pwd)
    else
    SDK_DIR := $(shell cd $(CURDIR)/../../.. && /bin/pwd)
    endif

    include $(SDK_DIR)/base.mak
endif

###############################################################################
# local variables
###############################################################################

## header search path

EXTRA_CFLAGS += -I$(COMMON_DIR)/include \
                -I$(COMMON_DIR)/api/include \
                -I$(COMMON_DIR)/drv/include \
                -I$(COMMON_DIR)/api/log \
                -I$(COMMON_DIR)/api/stat \
                -I$(COMMON_DIR)/api/sys \
                -I$(COMMON_DIR)/api/mmz \
                -I$(COMMON_DIR)/drv/module \
                -I$(COMMON_DIR)/drv/mem \
                -I$(COMMON_DIR)/drv/log \
                -I$(COMMON_DIR)/drv/mmz \
                -I$(COMMON_DIR)/api/mem \
                -I$(MSP_DIR)/drv/include \
                -I$(MSP_DIR)/api/include \
                -I$(MSP_DIR)/api/tde/include \
                -I$(MSP_DIR)/include \
                -I$(TEE_DRV_INCLUDE)

ifdef CFG_HI_LOG_LEVEL
EXTRA_CFLAGS += -DCFG_HI_LOG_LEVEL=$(CFG_HI_LOG_LEVEL)
else
EXTRA_CFLAGS += -DCFG_HI_LOG_LEVEL=1
endif

ifeq ($(CFG_HI_LOG_NETWORK_SUPPORT),y)
EXTRA_CFLAGS += -DLOG_NETWORK_SUPPORT
endif

ifeq ($(CFG_HI_LOG_UDISK_SUPPORT),y)
EXTRA_CFLAGS += -DLOG_UDISK_SUPPORT
endif

ifeq ($(CFG_PRODUCT_TYPE),android)
ifeq ($(TARGET_BUILD_VARIANT),user)
CFG_HI_PROC_WRITE_SUPPORT := n
endif
endif

ifeq ($(CFG_HI_PROC_WRITE_SUPPORT),y)
EXTRA_CFLAGS += -DHI_PROC_WRITE_SUPPORT
endif

EXTRA_CFLAGS += $(CFG_HI_KMOD_CFLAGS)

MOD_NAME_CMN   := hi_common
MOD_NAME_MMZ   := hi_mmz
MOD_NAME_MEDIA := hi_media

$(MOD_NAME_CMN)-y := sys/drv_base_ext_k.o  \
               sys/drv_sys_ext_k.o   \
               dev/drv_dev_ext_k.o   \
               stat/drv_stat_ext_k.o \
               proc/drv_proc_ext_k.o \
               log/drv_log_ext_k.o

$(MOD_NAME_CMN)-y +=    sys/drv_base_ext.o          \
                        sys/drv_sys_ext.o           \
                        sys/drv_reg_common.o        \
                        stat/drv_stat_ext.o         \
                        mem/drv_mutils.o            \
                        module/drv_module_ext.o     \
                        file/drv_file_ext.o         \
                        proc/drv_proc_ext.o         \
                        log/drv_log_ext.o           \
                        memdev/drv_memdev.o         \
                        userproc/drv_userproc.o     \
                        osal/drv_osal.o

$(MOD_NAME_MEDIA)-y :=  himedia/himedia_base.o  \
                        himedia/himedia.o

ifeq ($(HI_MEMMGR_SUPPORT),y)
EXTRA_CFLAGS += -DCMN_MMGR_SUPPORT

$(MOD_NAME_CMN)-y += mem/drv_mmgr_ext.o mem/drv_mem_ext.o
endif

$(MOD_NAME_MMZ)-y := mmz/drv_mmz_ext_k.o \
    mmz/drv_mmz_intf.o \
    mmz/drv_tzsmmu.o

ifdef CONFIG_COMPAT
$(MOD_NAME_MMZ)-y += mmz/drv_mmz_compat.o
endif

$(MOD_NAME_MMZ)-y += mmz/drv_mmz_userdev.o mmz/drv_media_mem.o

ifeq ($(CFG_HI_TEE_SUPPORT),y)
$(MOD_NAME_MMZ)-y += mmz/drv_tee_smmu_agent.o
endif
###############################################################################
obj-$(HI_DRV_BUILDTYPE) += $(MOD_NAME_MEDIA).o $(MOD_NAME_MMZ).o $(MOD_NAME_CMN).o

BUILD_DIR := $(HI_OUT_DIR)/$(OBJ_NAME)/$(subst $(SDK_DIR)/,,$(CURDIR))

BUILD_DIR_MAKEFILE := $(BUILD_DIR)/Makefile

#===============================================================================
#   rules
#===============================================================================
.PHONY: all clean

all: $(BUILD_DIR_MAKEFILE)
	$(AT)make -C $(LINUX_DIR) ARCH=$(CFG_HI_CPU_ARCH) CROSS_COMPILE=$(HI_KERNEL_TOOLCHAINS_NAME)- M=$(BUILD_DIR) src=$(CURDIR) modules
	$(AT)$(HI_KERNEL_TOOLCHAINS_NAME)-strip --strip-unneeded $(BUILD_DIR)/$(MOD_NAME_CMN).ko
	$(AT)test -d $(HI_MODULE_DIR) || mkdir -p $(HI_MODULE_DIR)
	$(AT)cp -f $(BUILD_DIR)/$(MOD_NAME_MEDIA).ko $(HI_MODULE_DIR)/
	$(AT)cp -f $(BUILD_DIR)/$(MOD_NAME_MMZ).ko $(HI_MODULE_DIR)/
	$(AT)cp -f $(BUILD_DIR)/$(MOD_NAME_CMN).ko $(HI_MODULE_DIR)/

clean:
	$(AT)make -C $(LINUX_DIR) ARCH=$(CFG_HI_CPU_ARCH) CROSS_COMPILE=$(HI_KERNEL_TOOLCHAINS_NAME)- M=$(BUILD_DIR) src=$(CURDIR) clean
	$(AT)rm -rf $(HI_MODULE_DIR)/$(MOD_NAME_MEDIA).ko $(HI_MODULE_DIR)/$(MOD_NAME_MMZ).ko $(HI_MODULE_DIR)/$(MOD_NAME_CMN).ko

$(BUILD_DIR_MAKEFILE): $(BUILD_DIR)
	$(AT)touch $@

$(BUILD_DIR):
	$(AT)mkdir -p $@
