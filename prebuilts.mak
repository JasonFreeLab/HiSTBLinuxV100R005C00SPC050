.PHONY: prebuilts_compose

ifeq ($(CFG_HI_DONGLE_SUPPORT),y)
    BOOTARGS_DONGLE := _dongle
endif

ifeq ($(CFG_HI_ADVCA_TYPE),VERIMATRIX)
    BOOTARGS_ADVCA := _vmx_advanced
else ifeq ($(CFG_HI_ADVCA_TYPE),VERIMATRIX_ULTRA)
    BOOTARGS_ADVCA := _vmx_ultra
else ifeq ($(CFG_HI_ADVCA_TYPE),NAGRA)
    BOOTARGS_ADVCA := _nagra
else ifeq ($(CFG_HI_ADVCA_TYPE),DCAS)
    BOOTARGS_ADVCA :=
    ifeq ($(CFG_HI_TEE_SUPPORT),y)
        ifeq ($(CFG_HI_CHIP_TYPE), hi3796mv200)
            BOOTARGS_TEE := _tee
        else
            BOOTARGS_TEE := _tee_DDR_$(CFG_HI_TVP_MEM_LAYOUT)B
        endif
    endif
else ifeq ($(CFG_HI_ADVCA_TYPE),SUMA)
    BOOTARGS_ADVCA :=
    ifeq ($(CFG_HI_TEE_SUPPORT),y)
        ifeq ($(CFG_HI_CHIP_TYPE), hi3796mv200)
            BOOTARGS_TEE := _tee
        else
            BOOTARGS_TEE := _tee_DDR_$(CFG_HI_TVP_MEM_LAYOUT)B
        endif
    endif
else ifneq ($(CFG_HI_ADVCA_TYPE),)
    ifeq ($(CFG_HI_ADVCA_FUNCTION),)
        BOOTARGS_ADVCA :=
    else
        BOOTARGS_ADVCA := _ca_$(shell echo $(CFG_HI_ADVCA_FUNCTION) | tr '[A-Z]' '[a-z]')
    endif

    ifeq ($(CFG_HI_TEE_SUPPORT),y)
        ifeq ($(CFG_HI_CHIP_TYPE), hi3796mv200)
            BOOTARGS_TEE := _tee
        else
            BOOTARGS_TEE := _tee_DDR_$(CFG_HI_TVP_MEM_LAYOUT)B
        endif
    endif
else
    ifeq ($(CFG_HI_TEE_SUPPORT),y)
        ifeq ($(CFG_HI_CHIP_TYPE), hi3796mv200)
            BOOTARGS_TEE := _tee
        else
            BOOTARGS_TEE := _tee_DDR_$(CFG_HI_TVP_MEM_LAYOUT)B
        endif
    endif
endif

ifeq ($(CFG_HI_TWOSTAGEBOOT_SUPPORT),y)
	BOOTARGS_SBL := _sbl
endif
NAND_PARTITIONS     := $(HI_PREBUILTS_DIR)/nand_partitions$(BOOTARGS_SBL)$(BOOTARGS_ADVCA).xml
EMMC_PARTITIONS     := $(HI_PREBUILTS_DIR)/emmc_partitions$(BOOTARGS_ADVCA).xml
SPI_EMMC_PARTITIONS := $(HI_PREBUILTS_DIR)/spi_emmc_partitions$(BOOTARGS_ADVCA).xml
SPI_PARTITIONS      := $(HI_PREBUILTS_DIR)/spi_partitions.xml

NAND_BOOTARGS       := $(HI_PREBUILTS_DIR)/nand_bootargs$(BOOTARGS_SBL)$(BOOTARGS_DONGLE)$(BOOTARGS_TEE)$(BOOTARGS_ADVCA).txt
EMMC_BOOTARGS       := $(HI_PREBUILTS_DIR)/emmc_bootargs$(BOOTARGS_DONGLE)$(BOOTARGS_TEE)$(BOOTARGS_ADVCA).txt
SPI_EMMC_BOOTARGS   := $(HI_PREBUILTS_DIR)/spi_emmc_bootargs$(BOOTARGS_DONGLE)$(BOOTARGS_TEE)$(BOOTARGS_ADVCA).txt
SPI_BOOTARGS        := $(HI_PREBUILTS_DIR)/spi_bootargs.txt

ifeq ($(CFG_ADVCA_VERIMATRIX_ULTRA),y)
    ifeq ($(CFG_HI_TVP_MEM_LAYOUT),512M)
        SOS_IMG_DIR := $(HI_TEE_OS_DIR)/images/$(CFG_HI_CHIP_TYPE)/vmx_ultra/512M
    else ifeq ($(CFG_HI_TVP_MEM_LAYOUT),1G)
        SOS_IMG_DIR := $(HI_TEE_OS_DIR)/images/$(CFG_HI_CHIP_TYPE)/vmx_ultra/1G
    else ifeq ($(CFG_HI_TVP_MEM_LAYOUT),1_5G)
        SOS_IMG_DIR := $(HI_TEE_OS_DIR)/images/$(CFG_HI_CHIP_TYPE)/vmx_ultra/1_5G
    else ifeq ($(CFG_HI_TVP_MEM_LAYOUT),2G)
        SOS_IMG_DIR := $(HI_TEE_OS_DIR)/images/$(CFG_HI_CHIP_TYPE)/vmx_ultra/2G
    endif

    FBL_IMG_DIR := $(BOOT_DIR)/fbl/$(CFG_HI_CHIP_TYPE)
endif

prebuilts_compose:
ifneq ($(CFG_HI_LOADER_APPLOADER),y)
ifeq ($(CFG_HI_NAND_FLASH_SUPPORT),y)
	$(AT)test -d $(HI_NAND_IMAGE_DIR) || mkdir -p $(HI_NAND_IMAGE_DIR)
	$(AT)test ! -f $(NAND_PARTITIONS) || cp -f $(NAND_PARTITIONS) $(HI_NAND_IMAGE_DIR)/
	$(AT)cp -f $(HI_PREBUILTS_DIR)/logo.img         $(HI_NAND_IMAGE_DIR)/
	$(AT)cp -f $(HI_PREBUILTS_DIR)/baseparam.img    $(HI_NAND_IMAGE_DIR)/
	$(AT)cp -f $(HI_PREBUILTS_DIR)/pq_param.bin     $(HI_NAND_IMAGE_DIR)/

	$(AT)(test ! -f $(NAND_BOOTARGS) || (cd $(HI_NAND_IMAGE_DIR) && $(MKBOOTARGS) \
		-s 64 -r $(NAND_BOOTARGS) -o bootargs.bin > /dev/null))

    ifeq ($(CFG_ADVCA_VERIMATRIX_ULTRA),y)
		$(AT)test ! -f $(FBL_IMG_DIR)/fbl.bin || cp -f $(FBL_IMG_DIR)/fbl.bin $(HI_NAND_IMAGE_DIR)/
		$(AT)test ! -f $(SOS_IMG_DIR)/trustedcore.img.sig.enc || cp -f $(SOS_IMG_DIR)/trustedcore.img.sig.enc $(HI_NAND_IMAGE_DIR)/
    endif
endif

ifeq ($(CFG_HI_EMMC_SUPPORT),y)
	$(AT)test -d $(HI_EMMC_IMAGE_DIR) || mkdir -p $(HI_EMMC_IMAGE_DIR)
	$(AT)test ! -f $(EMMC_PARTITIONS) || cp -f $(EMMC_PARTITIONS) $(HI_EMMC_IMAGE_DIR)/
	$(AT)cp -f $(HI_PREBUILTS_DIR)/logo.img         $(HI_EMMC_IMAGE_DIR)/
	$(AT)cp -f $(HI_PREBUILTS_DIR)/baseparam.img    $(HI_EMMC_IMAGE_DIR)/
	$(AT)cp -f $(HI_PREBUILTS_DIR)/pq_param.bin     $(HI_EMMC_IMAGE_DIR)/

	$(AT)(test ! -f $(EMMC_BOOTARGS) || (cd $(HI_EMMC_IMAGE_DIR) && $(MKBOOTARGS) \
		-s 64 -r $(EMMC_BOOTARGS) -o bootargs.bin > /dev/null))

    ifeq ($(CFG_ADVCA_VERIMATRIX_ULTRA),y)
		$(AT)test ! -f $(FBL_IMG_DIR)/fbl.bin || cp -f $(FBL_IMG_DIR)/fbl.bin  $(HI_EMMC_IMAGE_DIR)/
		$(AT)test ! -f $(SOS_IMG_DIR)/trustedcore.img.sig.enc || cp -f $(SOS_IMG_DIR)/trustedcore.img.sig.enc $(HI_EMMC_IMAGE_DIR)/
    endif
endif

ifeq ($(CFG_HI_SPI_SUPPORT)_$(CFG_HI_EMMC_SUPPORT),y_y)
	$(AT)test -d $(HI_SPI_EMMC_IMAGE_DIR) || mkdir -p $(HI_SPI_EMMC_IMAGE_DIR)
	$(AT)test ! -f $(SPI_EMMC_PARTITIONS) || cp -f $(SPI_EMMC_PARTITIONS) $(HI_SPI_EMMC_IMAGE_DIR)/
	$(AT)cp -f $(HI_PREBUILTS_DIR)/logo.img         $(HI_SPI_EMMC_IMAGE_DIR)/
	$(AT)cp -f $(HI_PREBUILTS_DIR)/baseparam.img    $(HI_SPI_EMMC_IMAGE_DIR)/
	$(AT)cp -f $(HI_PREBUILTS_DIR)/pq_param.bin     $(HI_SPI_EMMC_IMAGE_DIR)/

	$(AT)(test ! -f $(SPI_EMMC_BOOTARGS) || (cd $(HI_SPI_EMMC_IMAGE_DIR) && $(MKBOOTARGS) \
		-s 64 -r $(SPI_EMMC_BOOTARGS) -o bootargs.bin > /dev/null))

    ifeq ($(CFG_ADVCA_VERIMATRIX_ULTRA),y)
		$(AT)test ! -f $(FBL_IMG_DIR)/fbl.bin || cp -f $(FBL_IMG_DIR)/fbl.bin $(HI_SPI_EMMC_IMAGE_DIR)/
		$(AT)test ! -f $(SOS_IMG_DIR)/trustedcore.img.sig.enc || cp -f $(SOS_IMG_DIR)/trustedcore.img.sig.enc $(HI_SPI_EMMC_IMAGE_DIR)/
    endif
    ifeq ($(CFG_HI_CHIP_TYPE),hi3796mv200)
		$(AT)test ! -f $(SOS_IMG_DIR)/trustedcore.img.sig.enc || cp -f $(SOS_IMG_DIR)/trustedcore.img.sig.enc $(HI_SPI_EMMC_IMAGE_DIR)/
    endif
endif

ifeq ($(CFG_HI_SPI_SUPPORT),y)
	$(AT)test -d $(HI_SPI_IMAGE_DIR) || mkdir -p $(HI_SPI_IMAGE_DIR)
	$(AT)test ! -f $(SPI_PARTITIONS) || cp -f $(SPI_PARTITIONS) $(HI_SPI_IMAGE_DIR)/
	$(AT)cp -f $(HI_PREBUILTS_DIR)/logo.img         $(HI_SPI_IMAGE_DIR)/
	$(AT)cp -f $(HI_PREBUILTS_DIR)/baseparam.img    $(HI_SPI_IMAGE_DIR)/
	$(AT)cp -f $(HI_PREBUILTS_DIR)/pq_param.bin     $(HI_SPI_IMAGE_DIR)/

	$(AT)(test ! -f $(SPI_BOOTARGS) || (cd $(HI_SPI_IMAGE_DIR) && $(MKBOOTARGS) \
		-s 64 -r $(SPI_BOOTARGS) -o bootargs.bin > /dev/null))

    ifeq ($(CFG_ADVCA_VERIMATRIX_ULTRA),y)
		$(AT)test ! -f $(FBL_IMG_DIR)/fbl.bin || cp -f $(FBL_IMG_DIR)/fbl.bin $(HI_SPI_IMAGE_DIR)/
		$(AT)test ! -f $(SOS_SRC_DIR)/trustedcore.img.sig.enc || cp -f $(SOS_SRC_DIR)/trustedcore.img.sig.enc $(HI_SPI_IMAGE_DIR)/
    ifeq ($(CFG_HI_CHIP_TYPE),hi3796mv200)
		$(AT)test ! -f $(SOS_IMG_DIR)/trustedcore.img.sig.enc || cp -f $(SOS_IMG_DIR)/trustedcore.img.sig.enc $(HI_SPI_IMAGE_DIR)/
    endif
    endif
endif

endif
