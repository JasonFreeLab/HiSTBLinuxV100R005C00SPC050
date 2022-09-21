#===============================================================================
#                   export
#===============================================================================
.EXPORT_ALL_VARIABLES:

SDK_DIR := $(CURDIR)

include base.mak

CFG_HI_EXPORT_FLAG=y

# This is the default target. It must be the first declared target.
.DEFAULT_GOAL := help

#===============================================================================
#                   build
#===============================================================================
.PHONY: build clean

ifeq ($(CFG_HI_ADVCA_SUPPORT),y)
PROGRAMMER := advca_programmer
endif

build: prebuilts hiboot $(PROGRAMMER) rootbox
ifeq ($(CFG_HI_FS_BUILDIN),y)
	$(AT)make -C $(KERNEL_DIR) fs_buildin
else
	$(AT)make $(IMAGES)
ifeq ($(CFG_HI_ADVCA_TYPE)_$(CFG_HI_LOADER_APPLOADER), CONAX_y)
	$(AT)cp -f  $(LINUX_DIR)/arch/$(CFG_HI_CPU_ARCH)/boot/uImage $(HI_IMAGE_DIR)/hi_kernel.bin
	$(AT)test -e $(HI_IMAGE_DIR)/hi_kernel.bin && test -e $(HI_IMAGE_DIR)/rootfs.squashfs \
		&& $(MKBOOTIMG) --kernel $(HI_IMAGE_DIR)/hi_kernel.bin --ramdisk $(HI_IMAGE_DIR)/rootfs.squashfs \
		--base $(CFG_HI_APPLOADER_INITRD_BASE_ADDR) -o $(HI_IMAGE_DIR)/apploader.bin
ifeq ($(CFG_HI_NAND_FLASH_SUPPORT),y)
	$(AT)cp -f $(HI_IMAGE_DIR)/apploader.bin $(HI_NAND_IMAGE_DIR)/
endif
ifeq ($(CFG_HI_EMMC_SUPPORT),y)
	$(AT)cp -f $(HI_IMAGE_DIR)/apploader.bin $(HI_EMMC_IMAGE_DIR)/
endif
ifeq ($(CFG_HI_SPI_SUPPORT)_$(CFG_HI_EMMC_SUPPORT),y_y)
	$(AT)cp -f $(HI_IMAGE_DIR)/apploader.bin $(HI_SPI_EMMC_IMAGE_DIR)/
endif
endif
endif
	$(AT)rm -rf $(HI_IMAGE_DIR)/hi_kernel.bin $(HI_IMAGE_DIR)/apploader.bin $(HI_IMAGE_DIR)/rootfs.squashfs
ifneq ($(CFG_HI_LOADER_APPLOADER),y)
	$(AT)make -C $(SAMPLE_DIR) all
endif
	$(AT)make signature

clean:
	$(AT)rm -rf $(HI_OUT_DIR)
	$(AT)test ! -d $(KERNEL_SRC_DIR).patch || rm -rf $(KERNEL_SRC_DIR)

#====================================================================================
#                   global targets
#====================================================================================
.PHONY: signature signature_clean
#++++++++++++++++++++++++++++++++++++++++++++++++++++
SIGNATURE_SCRIPT_DIR  := none
ifeq ($(CFG_HI_ADVCA_SUPPORT),y)
	ifeq ($(CFG_HI_ADVCA_TYPE),CONAX)
		SIGNATURE_SCRIPT_DIR := Conax
	else ifeq ($(CFG_HI_ADVCA_TYPE),VERIMATRIX)
	    ifeq ($(CFG_HI_ADVCA_VMX_3RD_SIGN),y)
		    SIGNATURE_SCRIPT_DIR := Verimatrix/advance/SignBy3rd
		else
		    SIGNATURE_SCRIPT_DIR := Verimatrix/advance/SignByVmx
		endif
	else ifeq ($(CFG_HI_ADVCA_TYPE),VERIMATRIX_ULTRA)
		SIGNATURE_SCRIPT_DIR := Verimatrix/ultra	
	else ifeq ($(CFG_HI_ADVCA_TYPE)_$(CFG_HI_CHIP_TYPE),NAGRA_hi3796mv200)
		SIGNATURE_SCRIPT_DIR := Nagra/3796mv200
	else ifeq ($(CFG_HI_ADVCA_TYPE)_$(CFG_HI_CHIP_TYPE),NAGRA_hi3716mv420)
		SIGNATURE_SCRIPT_DIR := Nagra/3716mv420
	else ifeq ($(CFG_HI_CHIP_TYPE),hi3796mv200)
		SIGNATURE_SCRIPT_DIR := Basic	
	endif
endif

CREATE_SIGNATURE_DIR= $(HI_OUT_DIR)/tools/linux/utils/advca

signature:
ifneq ($(SIGNATURE_SCRIPT_DIR),none)
	mkdir -p $(CREATE_SIGNATURE_DIR)
	cp -rf $(SDK_DIR)/tools/linux/utils/advca/* $(CREATE_SIGNATURE_DIR)/
	make -C $(CREATE_SIGNATURE_DIR)/CreateSignature/$(SIGNATURE_SCRIPT_DIR) all

endif

signature_clean:
ifneq ($(SIGNATURE_SCRIPT_DIR),none)
	rm -rf $(CREATE_SIGNATURE_DIR)
ifeq ($(CFG_HI_NAND_FLASH_SUPPORT),y)
	-rm -rf $(HI_NAND_IMAGE_DIR)/*.sig $(HI_NAND_IMAGE_DIR)/FinalBoot.bin $(HI_NAND_IMAGE_DIR)/*signature* $(HI_NAND_IMAGE_DIR)/*enc
endif
ifeq ($(CFG_HI_EMMC_SUPPORT),y)
	-rm -rf $(HI_EMMC_IMAGE_DIR)/*.sig $(HI_EMMC_IMAGE_DIR)/FinalBoot.bin $(HI_EMMC_IMAGE_DIR)/*signature* $(HI_EMMC_IMAGE_DIR)/*enc
endif
ifeq ($(CFG_HI_SPI_SUPPORT)_$(CFG_HI_EMMC_SUPPORT),y_y)
	-rm -rf $(HI_SPI_EMMC_IMAGE_DIR)/*.sig $(HI_SPI_EMMC_IMAGE_DIR)/FinalBoot.bin $(HI_SPI_EMMC_IMAGE_DIR)/*signature* $(HI_SPI_EMMC_IMAGE_DIR)/*enc
endif
endif
#====================================================================================
#                   tools
#====================================================================================
.PHONY: tools  tools_clean
#++++++++++++++++++++++++++++++++++++++++++++++++++++
tools:
	$(AT)make -C $(HI_TOOLS_DIR) all

tools_clean:
	$(AT)make -C $(HI_TOOLS_DIR) clean

#====================================================================================
#                   prebuilts
#====================================================================================
.PHONY: prebuilts
include prebuilts.mak

prebuilts:
	$(AT)make prebuilts_compose
	$(AT)echo "make prebuilts over"

#====================================================================================
#                   hiboot
#====================================================================================
.PHONY:  hiboot  hiboot_clean  advca_programmer
#++++++++++++++++++++++++++++++++++++++++++++++++++++
hiboot:
ifneq ($(CFG_HI_LOADER_APPLOADER),y)
ifneq ($(CFG_HI_TWOSTAGEBOOT_SUPPORT),y)
	$(AT)make -C $(BOOT_DIR) all $(if $(HI_OUT_DIR),O=$(HI_OUT_DIR)/obj/source/boot,)
else
	$(AT)make -C $(BOOT_DIR) all $(if $(HI_OUT_DIR),O=$(HI_OUT_DIR)/obj/source/boot_fbl,) CFG_HI_BOOT_ENV_STARTADDR=0
	$(AT)make -C $(BOOT_DIR) all $(if $(HI_OUT_DIR),O=$(HI_OUT_DIR)/obj/source/boot_sbl,)
endif
endif

hiboot_clean:
	$(AT)make -C $(BOOT_DIR) clean $(if $(HI_OUT_DIR),O=$(HI_OUT_DIR)/obj/source/boot,)

advca_programmer:
ifneq ($(CFG_HI_LOADER_APPLOADER),y)
	$(AT)make -C $(BOOT_DIR) advca_programmer_install BOOT_ADVCA_PROGRAMMER=y $(if $(HI_OUT_DIR),O=$(HI_OUT_DIR)/obj/source/programmer,)
endif

#====================================================================================
#                   linux
#====================================================================================
.PHONY:  linux linux_clean

linux:
	$(AT)make -C $(KERNEL_DIR) all

linux_clean:
	$(AT)make -C $(KERNEL_DIR) clean

#====================================================================================
#                   rootfs
#====================================================================================
.PHONY:  rootfs  rootfs_clean

rootfs:
	$(AT)make -C $(ROOTFS_SRC_DIR) all

rootfs_clean:
	$(AT)make -C $(ROOTFS_SRC_DIR) clean

#====================================================================================
#                   common
#====================================================================================
.PHONY:  common common_clean

common:
	$(AT)make -C $(COMMON_DIR)/api all

common_clean:
	$(AT)make -C $(COMMON_DIR)/api clean

#====================================================================================
#                   msp
#====================================================================================
.PHONY:  msp  msp_clean

msp:
	$(AT)make -C $(MSP_DIR)/api all

msp_clean:
	$(AT)make -C $(MSP_DIR)/api clean

#====================================================================================
#                   hal
#====================================================================================
.PHONY:  hal  hal_clean
#++++++++++++++++++++++++++++++++++++++++++++++++++++
hal:
ifeq ($(CFG_GSTREAMER_SUPPORT),y)
	$(AT)make -C $(HI_HAL_DIR) all
endif

hal_clean:
ifeq ($(CFG_GSTREAMER_SUPPORT),y)
	$(AT)make -C $(HI_HAL_DIR) clean
endif
#====================================================================================
#                   higo
#====================================================================================
.PHONY:  higo  higo_clean

higo:
	$(AT)make -C $(MSP_DIR)/api/higo all

higo_clean:
	$(AT)make -C $(MSP_DIR)/api/higo clean

#====================================================================================
#                   jpeg
#====================================================================================
.PHONY:  jpeg  jpeg_clean

jpeg:
ifneq ($(CFG_HI_LOADER_APPLOADER),y)
	$(AT)make -C $(MSP_DIR)/api/jpeg all
endif

jpeg_clean:
	$(AT)make -C $(MSP_DIR)/api/jpeg clean

#====================================================================================
#                   png
#====================================================================================
.PHONY:  png  png_clean

png:
ifneq ($(CFG_HI_LOADER_APPLOADER),y)
	$(AT)make -C $(MSP_DIR)/api/png all
endif

png_clean:
	$(AT)make -C $(MSP_DIR)/api/png clean

#====================================================================================
#                   omx
#====================================================================================
.PHONY:  omx  omx_clean

omx:
ifneq ($(CFG_HI_LOADER_APPLOADER),y)
	$(AT)make -C $(MSP_DIR)/api/omx all
endif

omx_clean:
	$(AT)make -C $(MSP_DIR)/api/omx clean

#====================================================================================
#                   gpu
#====================================================================================
.PHONY:  gpu  gpu_clean

gpu:
ifneq ($(CFG_HI_LOADER_APPLOADER),y)
	$(AT)make -C $(MSP_DIR)/api/gpu all
endif

gpu_clean:
	$(AT)make -C $(MSP_DIR)/api/gpu clean

#====================================================================================
#                   component
#====================================================================================
.PHONY:  component  component_clean

component:
	$(AT)make -C $(COMPONENT_DIR) all

component_clean:
	$(AT)make -C $(COMPONENT_DIR) clean

#====================================================================================
#                   tee
#====================================================================================
.PHONY: tee tee_clean

tee:
ifeq ($(CFG_HI_TEE_SUPPORT),y)
	$(AT)[ ! -d $(HI_TEE_OS_DIR) ] || make -C $(HI_TEE_OS_DIR) all
endif

tee_clean:
	$(AT)[ ! -d $(HI_TEE_OS_DIR) ] || make -C $(HI_TEE_OS_DIR) clean

#====================================================================================
#                   sample
#====================================================================================
.PHONY:  sample  sample_clean

sample:
	$(AT)make -C $(SAMPLE_DIR) all

sample_clean:
	$(AT)make -C $(SAMPLE_DIR) clean

#====================================================================================
#                   rootbox
#====================================================================================
include rootbox.mak

.PHONY:  rootbox  rootbox_clean

rootbox: linux tee tools rootfs common msp higo jpeg png gpu omx hal component
ifeq ($(CFG_HI_DIRECTFB_SUPPORT),y)
	$(AT)make -C $(COMPONENT_DIR)/directfb all
endif

ifeq ($(CFG_HI_QT_SUPPORT),y)
	$(AT)make -C $(COMPONENT_DIR)/qt all
endif

	$(AT)make rootbox_compose
	$(AT)echo "rootbox is ready"

rootbox_clean:
	$(AT)rm -rf $(HI_ROOTBOX_DIR)
ifeq ($(CFG_HI_QT_SUPPORT),y)
	$(AT)make -C $(COMPONENT_DIR)/qt clean
endif

#====================================================================================
#                   fs
#====================================================================================
.PHONY: fs cramfs squashfs jffs2 yaffs extfs ubiimg
#++++++++++++++++++++++++++++++++++++++++++++++++++++
IMAGES :=
ifeq ($(CFG_HI_ROOTFS_CRAMFS),y)
IMAGES += cramfs
endif
ifeq ($(CFG_HI_ROOTFS_SQUASHFS),y)
IMAGES += squashfs
endif
ifeq ($(CFG_HI_ROOTFS_JFFS2),y)
IMAGES += jffs2
endif
ifeq ($(CFG_HI_ROOTFS_YAFFS),y)
IMAGES += yaffs
endif
ifeq ($(CFG_HI_ROOTFS_EXT4),y)
IMAGES += extfs
endif
ifeq ($(CFG_HI_ROOTFS_UBIIMG),y)
IMAGES += ubiimg
endif

fs: $(IMAGES)

ifdef CFG_HI_SPI_BLOCK_SIZE
SPI_BLOCK_SIZE := $(CFG_HI_SPI_BLOCK_SIZE)
else
SPI_BLOCK_SIZE := 0x10000 0x20000 0x40000
endif

YAFFS_MODE := 2k-1bit 4k-1bit 4k-4byte 4k-24bit1k 8k-24bit1k 8k-40bit1k
ifdef CFG_HI_NAND_PAGE_SIZE
ifdef CFG_HI_NAND_ECC_TYPE
YAFFS_MODE :=$(CFG_HI_NAND_PAGE_SIZE)-$(CFG_HI_NAND_ECC_TYPE)
endif
endif

cramfs:
ifeq ($(CFG_HI_NAND_FLASH_SUPPORT),y)
	$(AT)test -d $(HI_NAND_IMAGE_DIR) || mkdir -p $(HI_NAND_IMAGE_DIR)
	$(MKCRAMFS) $(HI_ROOTBOX_DIR) $(HI_NAND_IMAGE_DIR)/rootfs.cramfs
endif

squashfs:
	$(MKSQUASHFS) $(HI_ROOTBOX_DIR) $(HI_IMAGE_DIR)/rootfs.squashfs \
		-no-fragments -noappend -noI -comp xz -T $(RULEFILE) -G $(RULEDBG)
ifeq ($(CFG_HI_NAND_FLASH_SUPPORT),y)
	$(AT)test -d $(HI_NAND_IMAGE_DIR) || mkdir -p $(HI_NAND_IMAGE_DIR)
	$(AT)cp -f $(HI_IMAGE_DIR)/rootfs.squashfs $(HI_NAND_IMAGE_DIR)/
endif
ifeq ($(CFG_HI_EMMC_SUPPORT),y)
	$(AT)test -d $(HI_EMMC_IMAGE_DIR) || mkdir -p $(HI_EMMC_IMAGE_DIR)
	$(AT)cp -f $(HI_IMAGE_DIR)/rootfs.squashfs $(HI_EMMC_IMAGE_DIR)/
endif
ifeq ($(CFG_HI_SPI_SUPPORT)_$(CFG_HI_EMMC_SUPPORT),y_y)
	$(AT)test -d $(HI_SPI_EMMC_IMAGE_DIR) || mkdir -p $(HI_SPI_EMMC_IMAGE_DIR)
	$(AT)cp -f $(HI_IMAGE_DIR)/rootfs.squashfs $(HI_SPI_EMMC_IMAGE_DIR)/
endif

jffs2:
ifeq ($(CFG_HI_SPI_SUPPORT),y)
	$(AT)(for ix in $(SPI_BLOCK_SIZE) ; do ( \
		if [ "$$ix" == "0x10000" ]; then \
			NAME=64k; \
		elif [ "$$ix" == "0x20000" ];then \
			NAME=128k; \
		elif [ "$$ix" == "0x40000" ];then \
			NAME=256k; \
		fi; \
		test -d $(HI_SPI_IMAGE_DIR) || mkdir -p $(HI_SPI_IMAGE_DIR); \
		$(MKJFFS2) -d $(HI_ROOTBOX_DIR) -l -e $${ix} -o $(HI_SPI_IMAGE_DIR)/rootfs_$${NAME}.jffs2; \
	) done )
endif

yaffs:
ifeq ($(CFG_HI_NAND_FLASH_SUPPORT),y)
	$(AT)(for ix in $(YAFFS_MODE) ; do ( \
		NAME=`echo $$ix | sed -s 's/b.*[ket]/b/' | sed -s 's/-//'`; \
		PARAM=`echo $$ix | sed -s 's/-/ /'` ; \
		test -d $(HI_NAND_IMAGE_DIR) || mkdir -p $(HI_NAND_IMAGE_DIR); \
		$(MKYAFFS) $(HI_ROOTBOX_DIR) $(HI_NAND_IMAGE_DIR)/rootfs_$$NAME.yaffs $$PARAM -T $(RULEFILE) -G $(RULEDBG); \
		chmod a+r $(HI_NAND_IMAGE_DIR)/rootfs_$$NAME.yaffs; \
	) done )
endif

ubiimg:
ifeq ($(CFG_HI_NAND_FLASH_SUPPORT),y)
	$(AT)test -d $(HI_NAND_IMAGE_DIR) || mkdir -p $(HI_NAND_IMAGE_DIR)
	$(MKUBIIMG) $(CFG_HI_NAND_PAGE_SIZE) $(CFG_HI_NAND_BLOCK_SIZE) $(HI_ROOTBOX_DIR) $(CFG_HI_UBI_PARTITION_SIZE) \
		$(HI_NAND_IMAGE_DIR)/rootfs_$(CFG_HI_UBI_PARTITION_SIZE).ubiimg $(RULEFILE) $(RULEDBG)
endif

EMMC_SIZE_STR := $(CFG_HI_EMMC_ROOTFS_SIZE)M
ROOTBOX_SIZE := $(word 1,$(shell du -sh $(HI_ROOTBOX_DIR) 2>/dev/null))

extfs:
	$(AT)echo -e "Attention:\n\trootbox size must be less than $(EMMC_SIZE_STR), rootbox size is $(ROOTBOX_SIZE).\n"
	$(MKEXT4FS) -l $(EMMC_SIZE_STR) -s $(HI_IMAGE_DIR)/rootfs_$(EMMC_SIZE_STR).ext4 $(HI_ROOTBOX_DIR)
ifeq ($(CFG_HI_EMMC_SUPPORT),y)
	$(AT)test -d $(HI_EMMC_IMAGE_DIR) || mkdir -p $(HI_EMMC_IMAGE_DIR)
	$(AT)cp -f $(HI_IMAGE_DIR)/rootfs_$(EMMC_SIZE_STR).ext4 $(HI_EMMC_IMAGE_DIR)/
endif
ifeq ($(CFG_HI_SPI_SUPPORT)_$(CFG_HI_EMMC_SUPPORT),y_y)
	$(AT)test -d $(HI_SPI_EMMC_IMAGE_DIR) || mkdir -p $(HI_SPI_EMMC_IMAGE_DIR)
	$(AT)cp -f $(HI_IMAGE_DIR)/rootfs_$(EMMC_SIZE_STR).ext4 $(HI_SPI_EMMC_IMAGE_DIR)/
endif
	$(AT)rm -rf $(HI_IMAGE_DIR)/rootfs_$(EMMC_SIZE_STR).ext4

#====================================================================================
#                   cfg ops
#====================================================================================
.PHONY: menuconfig

#++++++++++++++++++++++++++++++++++++++++++++++++++++
KCONFIG_SRC_DIR := $(SDK_DIR)/tools/linux/kconfig
KCONFIG_OUT_DIR := $(if $(HI_OUT_DIR),$(HI_OUT_DIR)/tools/linux/kconfig/,$(KCONFIG_SRC_DIR)/)
KCONFIG_EXE := $(KCONFIG_OUT_DIR)himconf
KCONFIG_CFG := scripts/kconfig/mainKconfig
#++++++++++++++++++++++++++++++++++++++++++++++++++++
$(KCONFIG_EXE):
	$(AT)mkdir -p $(KCONFIG_OUT_DIR)
	$(AT)make -C $(KCONFIG_SRC_DIR) O=$(KCONFIG_OUT_DIR)

#++++++++++++++++++++++++++++++++++++++++++++++++++++
menuconfig: $(KCONFIG_EXE)
	$(KCONFIG_EXE) $(KCONFIG_CFG)
	$(AT)echo "make $@ over"

#====================================================================================
#     build apploader.bin quickly just for the second time
#====================================================================================
loader_rebuild:
	$(AT)make -C $(COMPONENT_DIR) loader_clean
	$(AT)make -C $(COMPONENT_DIR) loader
ifeq ($(CFG_HI_ADVCA_TYPE), CONAX)
	$(AT)make rootbox_compose
	$(AT)make $(IMAGES)
	$(AT)cp -f  $(LINUX_DIR)/arch/$(CFG_HI_CPU_ARCH)/boot/uImage $(HI_IMAGE_DIR)/hi_kernel.bin
	$(AT)test -e $(HI_IMAGE_DIR)/hi_kernel.bin && test -e $(HI_IMAGE_DIR)/rootfs.squashfs \
		&& $(MKBOOTIMG) --kernel $(HI_IMAGE_DIR)/hi_kernel.bin --ramdisk $(HI_IMAGE_DIR)/rootfs.squashfs \
		--base $(CFG_HI_APPLOADER_INITRD_BASE_ADDR) -o $(HI_IMAGE_DIR)/apploader.bin
ifeq ($(CFG_HI_NAND_FLASH_SUPPORT),y)
	$(AT)cp -f $(HI_IMAGE_DIR)/apploader.bin $(HI_NAND_IMAGE_DIR)/
endif
ifeq ($(CFG_HI_EMMC_SUPPORT),y)
	$(AT)cp -f $(HI_IMAGE_DIR)/apploader.bin $(HI_EMMC_IMAGE_DIR)/
endif
ifeq ($(CFG_HI_SPI_SUPPORT)_$(CFG_HI_EMMC_SUPPORT),y_y)
	$(AT)cp -f $(HI_IMAGE_DIR)/apploader.bin $(HI_SPI_EMMC_IMAGE_DIR)/
endif
	$(AT)rm -rf $(HI_IMAGE_DIR)/hi_kernel.bin $(HI_IMAGE_DIR)/apploader.bin $(HI_IMAGE_DIR)/rootfs.squashfs
else
	$(AT)make -C $(KERNEL_DIR) fs_buildin
endif
#====================================================================================

#====================================================================================
#                   help
#====================================================================================
.PHONY:  help
#++++++++++++++++++++++++++++++++++++++++++++++++++++
GREEN="\e[32;1m"
NORMAL="\e[39m"
RED="\e[31m"

help:
	$(AT)echo -e $(GREEN)
	$(AT)cat $(HI_SCRIPTS_DIR)/MakeHelp | less
	$(AT)echo -e $(NORMAL)
