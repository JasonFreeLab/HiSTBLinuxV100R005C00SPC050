#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(shell cd $(CURDIR)/../../../.. && /bin/pwd)

include $(SDK_DIR)/base.mak
endif

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#   variable
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

export PLATFORM_DIR_NAME := stb

ifeq ($(CFG_HI_CHIP_TYPE), hi3751v620)
export PLATFORM_DIR_NAME := hi3751vx
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798cv200 hi3798mv200 hi3798mv300 hi3796mv200),)
export PLATFORM_CHIP_NAME := hi3798cv2x
export CFG_HI_TEE_SEC_TIMER_SUPPORT := y
export CFG_HI_TEE_SMMU_SUPPORT := y
export CFG_HI_TEE_EMPTYDRM_SUPPORT := n
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv100 hi3796mv100 hi3716dv100),)
export PLATFORM_CHIP_NAME := hi3798mx
export CFG_HI_TEE_SEC_TIMER_SUPPORT := n
export CFG_HI_TEE_SMMU_SUPPORT := n
export CFG_HI_TEE_EMPTYDRM_SUPPORT := n
endif

ifeq ($(findstring fpga, $(CFG_HI_BOOT_REG_NAME)), fpga)
export CFG_HI_TEE_FPGA_SUPPORT := y
endif

export HI_CHIP_TYPE := $(CFG_HI_CHIP_TYPE)
export CFG_HI_TEE_VFMW_SUPPORT := $(CFG_HI_TEE_VFMW_SUPPORT)
export CFG_HI_TEE_KLAD_SUPPORT := $(CFG_HI_TEE_KLAD_SUPPORT)
export CFG_HI_ADVCA_TYPE := $(CFG_HI_ADVCA_TYPE)
export CFG_HI_TEE_PVR_SUPPORT := $(CFG_HI_TEE_PVR_SUPPORT)
export CFG_HI_TEE_DEMUX_SUPPORT := $(CFG_HI_TEE_DEMUX_SUPPORT)
export CFG_HI_TEE_PLCIPHER_SUPPORT := $(CFG_HI_TEE_PLCIPHER_SUPPORT)
export CFG_HI_TEE_CRYPTOEN_SUPPORT := $(CFG_HI_TEE_CRYPTOEN_SUPPORT)
export CFG_HI_TEE_HDMI_SUPPORT := $(CFG_HI_TEE_HDMI_SUPPORT)
export CFG_HI_TEE_DEMO_SUPPORT := $(CFG_HI_TEE_DEMO_SUPPORT)
export CFG_HI_TEE_VDP_SUPPORT := $(CFG_HI_TEE_VDP_SUPPORT)
export CFG_HI_TEE_BEIDOU_SUPPORT := $(CFG_HI_TEE_BEIDOU_SUPPORT)
export CFG_HI_TEE_I2C_SUPPORT := $(CFG_HI_TEE_I2C_SUPPORT)
export CFG_HI_TEE_WIDEVINE_SUPPORT := $(CFG_HI_TEE_WIDEVINE_SUPPORT)
export CFG_HI_TEE_PLAYREADY_SUPPORT := $(CFG_HI_TEE_PLAYREADY_SUPPORT)
export CFG_HI_TEE_VMX_ULTRA_SUPPORT := $(CFG_HI_TEE_VMX_ULTRA_SUPPORT)
export CFG_HI_TEE_VMXTAC_TEST_SUPPORT := $(CFG_HI_TEE_VMXTAC_TEST_SUPPORT)
export CFG_HI_TEE_ITAC_TEST_SUPPORT := $(CFG_HI_TEE_ITAC_TEST_SUPPORT)
export CFG_HI_TEE_AVPLAY_SUPPORT := $(CFG_HI_TEE_AVPLAY_SUPPORT)
export CFG_HI_TEE_NETFLIX_SUPPORT := $(CFG_HI_TEE_NETFLIX_SUPPORT)
export CFG_HI_TEE_DISPCTRL_SUPPORT := $(CFG_HI_TEE_DISPCTRL_SUPPORT)
export CFG_HI_TEE_PM_SUPPORT := $(CFG_HI_TEE_PM_SUPPORT)
export CFG_HI_TEE_TA_LOAD_SUPPORT := $(CFG_HI_TEE_TA_LOAD_SUPPORT)
export CFG_HI_TEE_TEST_SUPPORT := $(CFG_HI_TEE_TEST_SUPPORT)
export CFG_HI_TEE_SUMA_SUPPORT := $(CFG_HI_TEE_SUMA_SUPPORT)
export CFG_HI_TEE_RPMB_KEY_SUPPORT := $(CFG_HI_TEE_RPMB_KEY_SUPPORT)

ifeq ("$(origin O)", "command line")
OUTPUT_DIR := $(O)
else
OUTPUT_DIR := $(HI_OUT_DIR)/obj/source/tee/core/trustedcore
endif

TEE_OS_NAME := trustedos

ATF_SRC_DIR = ../arm-trusted-firmware_tee
ATF_OUT_DIR = $(subst $(SDK_DIR),$(HI_OUT_DIR)/$(OBJ_NAME),$(HI_TEE_OS_DIR))/../arm-trusted-firmware_tee
BL31_IMG = $(ATF_SRC_DIR)/$(CFG_HI_CHIP_TYPE)/bl31.bin
ATF_EXTRA_FLAGS = "-DCONFIG_TEE_SUPPORT"

ifeq ($(CFG_ADVCA_VERIMATRIX_ULTRA),y)
TEE_OS_BINARY_RELEASE := true
else
TEE_OS_BINARY_RELEASE := false
endif

BINARY_RELEASE_HI3796MV200 := y
BINARY_RELEASE_HI3798MV200 := n
BINARY_RELEASE_HI3798CV200 := n

ifeq ($(BINARY_RELEASE_HI3796MV200),y)
    ifeq ($(CFG_HI_CHIP_TYPE), hi3796mv200)
        TEE_OS_BINARY_RELEASE := true

        ifeq ($(CFG_HI_CPU_ARCH),arm64)
            VER := 64bit
        else
            VER := 32bit
        endif

        ifeq ($(CFG_HI_ADVCA_TYPE),NAGRA)
            SOS_IMG_DIR := $(HI_TEE_OS_DIR)/images/$(CFG_HI_CHIP_TYPE)/nagra/$(VER)
        else ifeq ($(CFG_HI_PLAYREADY_SUPPORT),y)
            SOS_IMG_DIR := $(HI_TEE_OS_DIR)/images/$(CFG_HI_CHIP_TYPE)/playready/$(VER)
        else ifeq ($(CFG_HI_WIDEVINE_SUPPORT),y)
            SOS_IMG_DIR := $(HI_TEE_OS_DIR)/images/$(CFG_HI_CHIP_TYPE)/widevine/$(VER)
        else
            SOS_IMG_DIR := $(HI_TEE_OS_DIR)/images/$(CFG_HI_CHIP_TYPE)/basic/$(VER)
        endif
    endif
endif

ifeq ($(BINARY_RELEASE_HI3798MV200),y)
    ifeq ($(CFG_HI_CHIP_TYPE), hi3798mv200)
        TEE_OS_BINARY_RELEASE := true

        ifeq ($(CFG_HI_CPU_ARCH),arm64)
            VER := 64bit
        else
            VER := 32bit
        endif

        SOS_IMG_DIR := $(HI_TEE_OS_DIR)/images/$(CFG_HI_CHIP_TYPE)/basic/$(VER)/$(CFG_HI_TVP_MEM_LAYOUT)
    endif
endif

ifeq ($(BINARY_RELEASE_HI3798CV200),y)
    ifeq ($(CFG_HI_CHIP_TYPE), hi3798cv200)
        TEE_OS_BINARY_RELEASE := true

        ifeq ($(CFG_HI_CPU_ARCH),arm64)
            VER := 64bit
        else
            VER := 32bit
        endif

        SOS_IMG_DIR := $(HI_TEE_OS_DIR)/images/$(CFG_HI_CHIP_TYPE)/basic/$(VER)/$(CFG_HI_TVP_MEM_LAYOUT)
    endif
endif

ifeq ($(CFG_ADVCA_VERIMATRIX_ULTRA),y)
    ifeq ($(CFG_HI_CHIP_TYPE), hi3796mv200)
        SOS_IMG_DIR := $(HI_TEE_OS_DIR)/images/$(CFG_HI_CHIP_TYPE)/vmx_ultra
    else
        SOS_IMG_DIR := $(HI_TEE_OS_DIR)/images/$(CFG_HI_CHIP_TYPE)/vmx_ultra/$(CFG_HI_TVP_MEM_LAYOUT)
        FBL_IMG_DIR := $(BOOT_DIR)/fbl/$(CFG_HI_CHIP_TYPE)
    endif
endif

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#   rules
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
.PHONY: all clean $(TEE_OS_NAME) teec tee_binary_prepare

ifeq ($(O),)
ifneq ($(TEE_OS_BINARY_RELEASE),true)
all: teec $(TEE_OS_NAME)
else
all: teec tee_binary_prepare
endif
else  ## match ifeq ($(O),) ##
ifneq ($(TEE_OS_BINARY_RELEASE),true)
all: $(TEE_OS_NAME)
else
all: tee_binary_prepare
endif
endif

clean:
	$(AT)rm -rf $(OUTPUT_DIR) $(HI_ROOTFS_DIR)/usr/sbin/teecd
	$(AT)rm -rf $(ATF_OUT_DIR)
ifeq ($(CFG_HI_NAND_FLASH_SUPPORT),y)
	$(AT)rm -rf $(HI_NAND_IMAGE_DIR)/trustedcore.img*
endif
ifeq ($(CFG_HI_EMMC_SUPPORT),y)
	$(AT)rm -rf $(HI_EMMC_IMAGE_DIR)/trustedcore.img*
endif
ifeq ($(CFG_HI_SPI_SUPPORT)_$(CFG_HI_EMMC_SUPPORT),y_y)
	$(AT)rm -rf $(HI_SPI_EMMC_IMAGE_DIR)/trustedcore.img*
endif

$(TEE_OS_NAME):
	$(AT)make -C $(TEE_OS_NAME) all HI_SDK_DIR=$(SDK_DIR) O=$(OUTPUT_DIR)
ifeq ($(CFG_HI_TEE_RESERVED_MEM),y)
ifeq ($(CFG_HI_CPU_ARCH),arm64)
	$(AT)test -d $(ATF_OUT_DIR) || mkdir -p $(ATF_OUT_DIR)
	$(AT)dd if=$(BL31_IMG) of=$(ATF_OUT_DIR)/bl31.bin.$(CFG_HI_BL31_SIZE) conv=sync count=1 bs=$(CFG_HI_BL31_SIZE)
	$(AT)cat $(ATF_OUT_DIR)/bl31.bin.$(CFG_HI_BL31_SIZE) $(OUTPUT_DIR)/trustedcore.img >$(OUTPUT_DIR)/trustedcore.img.atf
	$(AT)mv $(OUTPUT_DIR)/trustedcore.img $(OUTPUT_DIR)/trustedcore.img.org
	$(AT)cp $(OUTPUT_DIR)/trustedcore.img.atf $(OUTPUT_DIR)/trustedcore.img
endif
endif

ifeq ($(CFG_PRODUCT_TYPE),linux)
ifeq ($(CFG_HI_NAND_FLASH_SUPPORT),y)
	$(AT)test -d $(HI_NAND_IMAGE_DIR) || mkdir -p $(HI_NAND_IMAGE_DIR)
	$(AT)cp -f $(OUTPUT_DIR)/trustedcore.img $(HI_NAND_IMAGE_DIR)/
endif
ifeq ($(CFG_HI_EMMC_SUPPORT),y)
	$(AT)test -d $(HI_EMMC_IMAGE_DIR) || mkdir -p $(HI_EMMC_IMAGE_DIR)
	$(AT)cp -f $(OUTPUT_DIR)/trustedcore.img $(HI_EMMC_IMAGE_DIR)/
endif
ifeq ($(CFG_HI_SPI_SUPPORT)_$(CFG_HI_EMMC_SUPPORT),y_y)
	$(AT)test -d $(HI_SPI_EMMC_IMAGE_DIR) || mkdir -p $(HI_SPI_EMMC_IMAGE_DIR)
	$(AT)cp -f $(OUTPUT_DIR)/trustedcore.img $(HI_SPI_EMMC_IMAGE_DIR)/
endif
endif

teec:
ifeq ($(HI_USER_SPACE_LIB),y)
	$(AT)make -C libteec all CROSS_COMPILE=$(CFG_HI_ARM_TOOLCHAINS_NAME)-
endif
ifeq ($(HI_USER_SPACE_LIB64),y)
	$(AT)make -C libteec all CROSS_COMPILE=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-
endif
ifeq ($(HI_USER_SPACE_LIB),y)
	$(AT)test -d $(HI_ROOTFS_DIR)/usr/sbin/ || mkdir -p $(HI_ROOTFS_DIR)/usr/sbin
	$(AT)cp -f $(HI_OUT_DIR)/obj/source/tee/core/trustedcore/libteec/teecd $(HI_ROOTFS_DIR)/usr/sbin/
else ifeq ($(HI_USER_SPACE_LIB64),y)
	$(AT)test -d $(HI_ROOTFS_DIR)/usr/sbin/ || mkdir -p $(HI_ROOTFS_DIR)/usr/sbin
	$(AT)cp -f $(HI_OUT_DIR)/obj64/source/tee/core/trustedcore/libteec/teecd $(HI_ROOTFS_DIR)/usr/sbin/
endif

tee_binary_prepare:
ifeq ($(CFG_PRODUCT_TYPE),linux)
    ifeq ($(CFG_HI_NAND_FLASH_SUPPORT),y)
		$(AT)test -d $(HI_NAND_IMAGE_DIR) || mkdir -p $(HI_NAND_IMAGE_DIR)
		$(AT)cp -f $(SOS_IMG_DIR)/trustedcore.img* $(HI_NAND_IMAGE_DIR)/
        ifeq ($(CFG_ADVCA_VERIMATRIX_ULTRA),y)
			$(AT)test ! -f $(FBL_IMG_DIR)/fbl.bin || cp -f $(FBL_IMG_DIR)/fbl.bin $(HI_NAND_IMAGE_DIR)/
        endif
    endif
    ifeq ($(CFG_HI_EMMC_SUPPORT),y)
		$(AT)test -d $(HI_EMMC_IMAGE_DIR) || mkdir -p $(HI_EMMC_IMAGE_DIR)
		$(AT)cp -f $(SOS_IMG_DIR)/trustedcore.img* $(HI_EMMC_IMAGE_DIR)/
        ifeq ($(CFG_ADVCA_VERIMATRIX_ULTRA),y)
			$(AT)test ! -f $(FBL_IMG_DIR)/fbl.bin || cp -f $(FBL_IMG_DIR)/fbl.bin $(HI_EMMC_IMAGE_DIR)/
        endif
    endif
    ifeq ($(CFG_HI_SPI_SUPPORT)_$(CFG_HI_EMMC_SUPPORT),y_y)
		$(AT)test -d $(HI_SPI_EMMC_IMAGE_DIR) || mkdir -p $(HI_SPI_EMMC_IMAGE_DIR)
		$(AT)cp -f $(SOS_IMG_DIR)/trustedcore.img* $(HI_SPI_EMMC_IMAGE_DIR)/
        ifeq ($(CFG_ADVCA_VERIMATRIX_ULTRA),y)
			$(AT)test ! -f $(FBL_IMG_DIR)/fbl.bin || cp -f $(FBL_IMG_DIR)/fbl.bin $(HI_SPI_EMMC_IMAGE_DIR)/
        endif
    endif
    ifeq ($(CFG_HI_SPI_SUPPORT),y)
		$(AT)test -d $(HI_SPI_IMAGE_DIR) || mkdir -p $(HI_SPI_IMAGE_DIR)
		$(AT)cp -f $(SOS_IMG_DIR)/trustedcore.img* $(HI_SPI_IMAGE_DIR)/
        ifeq ($(CFG_ADVCA_VERIMATRIX_ULTRA),y)
			$(AT)test ! -f $(FBL_IMG_DIR)/fbl.bin || cp -f $(FBL_IMG_DIR)/fbl.bin $(HI_SPI_IMAGE_DIR)/
        endif
    endif
else
	$(AT)cp -f $(SOS_IMG_DIR)/trustedcore.img* $(OUTPUT_DIR)/
    ifeq ($(CFG_ADVCA_VERIMATRIX_ULTRA),y)
		$(AT)test ! -f $(FBL_IMG_DIR)/fbl.bin || cp -f $(FBL_IMG_DIR)/fbl.bin $(OUTPUT_DIR)/
    endif
endif
