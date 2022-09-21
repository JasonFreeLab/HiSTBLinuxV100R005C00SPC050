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

ifeq ($(CFG_HI_MINIBOOT_SUPPORT),y)
BOOT_DIR  := $(SDK_DIR)/source/boot/miniboot
else
BOOT_DIR  := $(SDK_DIR)/source/boot/fastboot
endif

ifneq ($(O),)
PRODUCT_DIR := $(O)/product
else
PRODUCT_DIR := $(BOOT_DIR)/../product
endif

KLAD_VERSION :=v200

ifneq ($(CFG_HI_MINIBOOT_SUPPORT), y)
CFLAGS  += -DKLAD_CMD_TEST
endif

KLAD_API    := $(PRODUCT_DIR)/driver/klad/api
KLAD_DRV    := $(PRODUCT_DIR)/driver/klad/drv

CFLAGS  += -I$(BOOT_DIR)/arch/arm/include
CFLAGS  += -I$(BOOT_DIR)/include
CFLAGS  += -I$(BOOT_DIR)/include/linux
CFLAGS  += -I$(PRODUCT_DIR)/driver/include
CFLAGS  += -I$(PRODUCT_DIR)/driver/include_inc

CFLAGS += -I$(KLAD_DRV)
CFLAGS += -I$(KLAD_DRV)/include
CFLAGS += -I$(KLAD_DRV)/basic/include
CFLAGS += -I$(KLAD_DRV)/basic/$(KLAD_VERSION)
CFLAGS += -I$(KLAD_DRV)/framework

LIBS    := libklad.a

OBJS    := $(KLAD_API)/unf_klad.o
OBJS    += $(KLAD_DRV)/drv_klad_intf.o
OBJS    += $(KLAD_DRV)/basic/$(KLAD_VERSION)/hal_klad.o
OBJS    += $(KLAD_DRV)/framework/drv_klad.o

ifeq ($(CFG_HI_ADVCA_TYPE),NAGRA)
CFLAGS   += -DHI_ADVCA_NAGRA_SUPPORT
CFLAGS   += -I$(KLAD_DRV)/nagra/include
CFLAGS   += -I$(KLAD_DRV)/nagra/cert

OBJS    += $(KLAD_API)/nagra/unf_klad_nagra.o
OBJS    += $(KLAD_API)/nagra/unf_cert.o

OBJS    += $(KLAD_DRV)/nagra/drv_klad_nagra.o
OBJS    += $(KLAD_DRV)/nagra/$(KLAD_VERSION)/hal_klad_nagra.o

OBJS    += $(KLAD_DRV)/nagra/cert/drv_cert.o
OBJS    += $(KLAD_DRV)/nagra/cert/drv_cert_intf.o
OBJS    += $(KLAD_DRV)/nagra/cert/hal_cert.o
endif

OBJS    += $(PRODUCT_DIR)/driver/klad/cmd_klad.o

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
