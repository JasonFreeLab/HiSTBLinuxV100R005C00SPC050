ifeq ($(CONFIG_ARCH_HI3798MV2X),y)
include $(HI110X_DRIVER_PATH)/hi3798_defconfig
endif

obj-y += platform/
obj-y += wifi/

ifeq ($(CONFIG_ARCH_HI3798MV2X),y)
obj-y +=sdio_detect/
endif
