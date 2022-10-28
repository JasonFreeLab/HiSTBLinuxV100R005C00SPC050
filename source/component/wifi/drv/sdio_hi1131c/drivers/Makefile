ifeq ($(CONFIG_ARCH_HI3798MV2X),y)
include $(HI110X_DRIVER_PATH)/hi3798_defconfig
endif

ifeq ($(CONFIG_ARCH_HI3798MV310),y)
include $(HI110X_DRIVER_PATH)/hi3798_defconfig
endif

obj-y += platform/
obj-y += wifi/

ifeq ($(CONFIG_ARCH_HI3798MV2X),y)
obj-y +=sdio_detect/
endif

ifeq ($(CONFIG_ARCH_HI3798MV310),y)
obj-y +=sdio_detect/
endif