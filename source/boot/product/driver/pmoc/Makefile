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

CFLAGS   += -I$(PRODUCT_DIR)/driver/include
CFLAGS   += -I$(BOOT_DIR)/arch/arm/include
CFLAGS   += -I$(BOOT_DIR)/include
#CFLAGS   += -I$(COMPONENT_DIR)/pm/c51

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3796mv200),)
CFLAGS += -I$(COMPONENT_DIR)/pm/c51_96mv200
else
CFLAGS += -I$(COMPONENT_DIR)/pm/c51
endif

LIBS     := libpmoc.a

###########################ca_common#####################
OBJS += drv_c51.o

ifdef CFG_HI_ADVCA_TYPE
CFLAGS += -DADVCA_SUPPORT  -DADVCA_TYPE_$(CFG_HI_ADVCA_TYPE)
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
