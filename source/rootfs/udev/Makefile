#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

PREFIX ?= $(HI_ROOTFS_DIR)

ifneq ($(HI_OUT_DIR),)
UDEV_DIR := $(HI_OUT_DIR)/obj/source/rootfs/udev
else
UDEV_DIR := $(CURDIR)
endif

################################################################################
HOST    := $(CFG_HI_ARM_TOOLCHAINS_NAME)
STRIP   := $(CFG_HI_ARM_TOOLCHAINS_NAME)-strip

UDEV    := udev-167

################################################################################
.PHONY: all clean

all: $(PREFIX)/bin/udevd

clean:
	$(AT)rm -rf $(UDEV_DIR)/$(UDEV)

################################################################################
$(PREFIX)/bin/udevd $(PREFIX)/bin/udevadm: $(UDEV_DIR)/$(UDEV)/udev/udevd
	$(AT)test -d $(@D) || mkdir -p $(@D)
	$(AT)install -v -t $(@D) $(UDEV_DIR)/$(UDEV)/udev/udevd
	$(AT)install -v -t $(@D) $(UDEV_DIR)/$(UDEV)/udev/udevadm

$(UDEV_DIR)/$(UDEV)/udev/udevd: $(UDEV_DIR)/tar
	$(AT)make -C $(UDEV_DIR)/$(UDEV) USE_STATIC=false

################################################################################
$(UDEV_DIR)/tar:
	$(AT)test -d $(UDEV_DIR) || mkdir -p $(UDEV_DIR)
	$(AT)test -d $(UDEV_DIR)/$(UDEV) || (tar xf $(OPEN_SOURCE_DIR)/$(UDEV).tar.bz2 -C $(UDEV_DIR); \
        cd $(UDEV_DIR)/$(UDEV); CC=$(HOST)-gcc; ./configure --prefix=/ --host=$(HOST) \
        --disable-logging --disable-extras --disable-introspection;)
	$(AT)touch $@

