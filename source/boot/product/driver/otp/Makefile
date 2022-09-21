#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR     := $(shell pwd)/../../../../..
include $(SDK_DIR)/base.mak
endif

#===============================================================================
# local variables
#===============================================================================
CA_DRV_FRAMEWORK_VERSION := V200
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716dv100 hi3716mv410 hi3716mv420 hi3796mv100 hi3798cv200 hi3798mv100 hi3798mv200 hi3798mv300 hi3798mv200_a),)
    CA_DRV_FRAMEWORK_VERSION := V100
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716mv410 hi3716mv420),)
    ifeq ($(CFG_HI_ADVCA_TYPE),NAGRA)
        CA_DRV_FRAMEWORK_VERSION := V200
    endif
endif

ifeq ($(CFG_HI_MINIBOOT_SUPPORT),y)
BOOT_DIR    := $(SDK_DIR)/source/boot/miniboot
else
BOOT_DIR    := $(SDK_DIR)/source/boot/fastboot
endif

ifneq ($(O),)
PRODUCT_DIR := $(O)/product
else
PRODUCT_DIR := $(BOOT_DIR)/../product
endif

COMMON_DIR  := $(PRODUCT_DIR)/driver/common

CFLAGS  += -I$(PRODUCT_DIR)/driver/include
CFLAGS  += -I$(PRODUCT_DIR)/driver/otp/include
CFLAGS  += -I$(PRODUCT_DIR)/driver/include_inc
CFLAGS  += -I$(BOOT_DIR)/arch/arm/include
CFLAGS  += -I$(BOOT_DIR)/include
CFLAGS  += -I$(BOOT_DIR)/include/linux

CFLAGS  += -DCHIP_TYPE_${CFG_HI_CHIP_TYPE}

ifneq ($(CFG_HI_MINIBOOT_SUPPORT), y)
CFLAGS  += -DOTP_CMD_TEST
endif

LIBS    := libotp.a
OBJS    := cmd_otp.o unf_otp.o

ifneq ($(findstring $(CA_DRV_FRAMEWORK_VERSION), V200 ),)
OBJS += v200/drv_otp.o
OBJS += v200/hal_otp.o

ifeq ($(CFG_ADVCA_NAGRA),y)
    OBJS += unf_otp_nagra.o
endif
else
OBJS += v100/drv_otp.o
OBJS += v100/hal_otp.o    
endif
#===============================================================================
# rules
#===============================================================================

.PHONY: all clean install uninstall $(LIBS)

all: $(LIBS)

clean:
	$(AT)rm -rf $(OBJS)
	$(AT)rm -rf $(LIBS)

install: all

uninstall:

$(LIBS): $(OBJS)
	$(AT)$(AR) -rc $@ $^
