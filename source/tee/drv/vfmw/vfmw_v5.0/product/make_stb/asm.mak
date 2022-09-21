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
#   Generate asm
#===============================================================================
include $(SDK_DIR)/asm.mk

ifeq ($(CFG_HI_CHIP_TYPE), hi3798cv200)
PRODUCT_DIR := Hi3798CV200
ASM_CFLAGS += -DCHIP_TYPE_hi3798cv200
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv200 hi3798mv300),)
PRODUCT_DIR := Hi3798MV200
ASM_CFLAGS += -DCHIP_TYPE_hi3798mv200 -DCHIP_TYPE_hi3798mv300
endif

ifeq ($(CFG_HI_CHIP_TYPE), hi3796mv200)
ifeq ($(CFG_HI_NVR_SUPPORT),y)
PRODUCT_DIR := Hi3796MV200_NVR
ASM_CFLAGS += -DCHIP_TYPE_hi3796mv200
else
PRODUCT_DIR := Hi3796MV200
ASM_CFLAGS += -DCHIP_TYPE_hi3796mv200
endif
endif

VFMW_DIR := $(MSP_DIR)/drv/vfmw/vfmw_v5.0

include $(VFMW_DIR)/product/$(PRODUCT_DIR)/LNX_CFG/vfmw_make.cfg

DST_DIR =$(VFMW_DIR)/product/$(PRODUCT_DIR)/LNX_CFG/${SYSTEM_CONFIG}

VFMW_BASE := ../..

################################################################################################
#####    PRODUCT

# local include files and macroes, ONLY FOR TEST, PLEASE CHECK CHECK CHECK!!!
ASM_CFLAGS += -I/opt/hisi-linux/x86-arm/aarch64-histbv100-linux/target/usr/include
ASM_CFLAGS += -I/opt/hisi-linux/x86-arm/aarch64-histbv100-linux/lib/gcc/aarch64-gcc51_glibc222-linux-gnu/5.1.1/include

ASM_CFLAGS += -I$(SDK_DIR)/tools/linux/toolchains/aarch64-histbv100-linux/target/usr/include
ASM_CFLAGS += -I$(SDK_DIR)/tools/linux/toolchains/aarch64-histbv100-linux/lib/gcc/aarch64-gcc51_glibc222-linux-gnu/5.1.1/include
################################################################################################
ASM_CFLAGS += -I$(SDK_DIR)/source/common/drv/include
ASM_CFLAGS += -I$(SDK_DIR)/source/common/include

ASM_CFLAGS += $(VFMW_CFLAGS)

# .S files define
ALL_SRC := $(VFMW_OBJS:o=S)
# filter out open source code
OPEN_SRC := $(VFMW_BASE)/platform/osal/linux_kernel/vfmw_linux_kernel_osal.S $(VFMW_BASE)/platform/osal/linux_kernel/vfmw_proc.S  $(VFMW_BASE)/platform/osal/sos_kernel/vfmw_sos_kernel_osal.S 
OPEN_SRC += $(VFMW_BASE)/adapter/vfmw_intf.S $(VFMW_BASE)/adapter/vfmw_adapter.S $(VFMW_BASE)/adapter/vfmw_img_info.S
OPEN_SRC += $(VFMW_BASE)/module/hdr_info/hdr_info.S $(VFMW_BASE)/module/pts_info/pts_info.S $(VFMW_BASE)/module/pts_info/frd_alg.S
OPEN_SRC += $(VFMW_BASE)/module/distributor/vdh_common.S $(VFMW_BASE)/module/distributor/vdh_normal.S $(VFMW_BASE)/module/distributor/vdh_secure.S
OPEN_SRC += $(VFMW_BASE)/core/common/public.S $(VFMW_BASE)/core/common/vfmw.S
OPEN_SRC += $(VFMW_BASE)/platform/tee/client/vfmw_tee_client.S
OPEN_SRC += $(VFMW_BASE)/product/$(PRODUCT_DIR)/product.S

ASM_SRC = $(filter-out $(OPEN_SRC),$(ALL_SRC))
ASM_SRC_TEMP = $(addsuffix .tmp,$(ASM_SRC))

ifeq ($(CFG_HI_SMMU_SUPPORT),y)
ASM_CFLAGS += -DHI_SMMU_SUPPORT
endif

ifeq ($(CFG_HI_HDR_SUPPORT),y)
ASM_CFLAGS += -DVFMW_HDR_SUPPORT
endif

ASM_CFLAGS += -DVFMW_STB_PRODUCT

#$(warning "----------"$(ASM_CFLAGS))

.PHONY: asm asm_clean

asm: $(ASM_SRC)
	mkdir -p ${DST_DIR}/core/common
	mkdir -p ${DST_DIR}/core/driver
	mkdir -p ${DST_DIR}/core/syntax	
	
	cd $(VFMW_BASE)/core/common && find ./ -name "*.h" | xargs cp -f -t $(VFMW_DIR)/product/$(PRODUCT_DIR)/ && cd -
	cd $(VFMW_BASE)/core/syntax && find ./ -name "*.h" | xargs cp -f -t $(VFMW_DIR)/product/$(PRODUCT_DIR)/ && cd -
	cp $(VFMW_BASE)/core/driver/$(SCD_DIR)/scd_drv.h    $(VFMW_DIR)/product/$(PRODUCT_DIR)/
	cp $(VFMW_BASE)/core/driver/$(VDH_DIR)/vdm_hal_*_api.h    $(VFMW_DIR)/product/$(PRODUCT_DIR)/
	
	cd $(VFMW_BASE)/core/common && find ./ -name "*.S" | xargs cp -rf --parent -t ${DST_DIR}/core/common && cd -
	cd $(VFMW_BASE)/core/common && find ./ -name "*.S" | xargs rm -rf "*.S" && cd -
	cd $(VFMW_BASE)/core/driver && find ./ -name "*.S" | xargs cp -rf --parent -t ${DST_DIR}/core/driver && cd -
	cd $(VFMW_BASE)/core/driver && find ./ -name "*.S" | xargs rm -rf "*.S" && cd -
	cd $(VFMW_BASE)/core/syntax && find ./ -name "*.S" | xargs cp -rf --parent -t ${DST_DIR}/core/syntax && cd -
	cd $(VFMW_BASE)/core/syntax && find ./ -name "*.S" | xargs rm -rf "*.S" && cd -
	
	cd $(VFMW_BASE)/core/syntax && find ./ -name "hir8.c" | xargs cp -rf --parent -t ${DST_DIR}/core/syntax && cd -
	cd $(VFMW_BASE)/core/syntax && find ./ -name "hir9.c" | xargs cp -rf --parent -t ${DST_DIR}/core/syntax && cd -
	cd $(VFMW_BASE)/core/syntax && find ./ -name "hidivx3.c" | xargs cp -rf --parent -t ${DST_DIR}/core/syntax && cd -
	cd $(VFMW_BASE)/core/driver/$(VDH_DIR) && find ./ -name "hi_hal_r8.c" | xargs cp -rf --parent -t ${DST_DIR}/core/driver/$(VDH_DIR) && cd -
	cd $(VFMW_BASE)/core/driver/$(VDH_DIR) && find ./ -name "hi_hal_r9.c" | xargs cp -rf --parent -t ${DST_DIR}/core/driver/$(VDH_DIR) && cd -
	cd $(VFMW_BASE)/core/driver/$(VDH_DIR) && find ./ -name "hi_hal_divx3.c" | xargs cp -rf --parent -t ${DST_DIR}/core/driver/$(VDH_DIR) && cd -
	
	cd $(DST_DIR)/core/syntax && find ./ -name "divx3.S" | xargs rm -rf "divx3.S" && cd -
	cd $(DST_DIR)/core/driver/$(VDH_DIR) && find ./ -name "vdm_hal_divx3.S" | xargs rm -rf "vdm_hal_divx3.S" && cd -
	cp $(VFMW_BASE)/core/common/vfmw.c ${DST_DIR}/core/common
	cp $(VFMW_BASE)/core/common/public.c ${DST_DIR}/core/common
        
asm_clean: 
	rm -rf $(ASM_SRC) $(ASM_SRC_TEMP)
	rm -rf $(VFMW_BASE)/product/$(PRODUCT_DIR)/LNX_CFG/$(SYSTEM_CONFIG)
