export HI110X_DRIVER_PATH := "drivers/wifi/sdio_hi1131c/drivers"
HI110X_DRIVER_PATH := $(subst ",,$(HI110X_DRIVER_PATH))

ifeq ($(CFG_PRODUCT_TYPE),linux)
CONFIG_HI1131C_DRIVER_PATH ?= "source/component/wifi/drv/sdio_hi1131c"
else
CONFIG_HI1131C_DRIVER_PATH ?= "device/hisilicon/bigfish/sdk/source/component/wifi/drv/sdio_hi1131c"
endif

HI1131C_DRIVER_BUILTIN_PATH := $(subst ",,$(CONFIG_HI1131C_DRIVER_PATH))
FIRMWARE_PATH := $(PWD)/$(HI1131C_DRIVER_BUILTIN_PATH)/firmware/

ifeq ($(CFG_PRODUCT_TYPE),linux)
FIRMWARE_DIR := $(HI_ROOTFS_DIR)/etc/Wireless/firmware
else
FIRMWARE_DIR := $(ANDROID_PRODUCT_OUT)/system/vendor/firmware
endif

$(warning firmware_src:$(FIRMWARE_PATH))
$(warning firmware_dest:$(FIRMWARE_DIR))

$(shell test -d $(FIRMWARE_DIR) || mkdir -p $(FIRMWARE_DIR))
$(shell cp -arf $(FIRMWARE_PATH)/* $(FIRMWARE_DIR)/)

obj-y += drivers/
