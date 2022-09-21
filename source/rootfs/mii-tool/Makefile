#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

ifneq ($(HI_OUT_DIR),)
TOP_DIR := $(HI_OUT_DIR)/obj/source/rootfs/mii-tool
else
TOP_DIR := $(CURDIR)
endif

PREFIX ?= $(HI_ROOTFS_DIR)

################################################################################
HOST           := $(CFG_HI_ARM_TOOLCHAINS_NAME)
MIITOOL        := mii-tool

################################################################################
.PHONY: all clean
################################################################################
all: $(PREFIX)/usr/local/bin/mii-tool

clean:
	$(AT)rm -rf $(TOP_DIR)/$(MIITOOL)

$(PREFIX)/usr/local/bin/mii-tool: $(TOP_DIR)/$(MIITOOL)/mii-tool
	@test -d $(@D) || mkdir -p $(@D)
	@install -v -t $(@D) $<

$(TOP_DIR)/$(MIITOOL)/mii-tool: $(TOP_DIR)/tar
	cd $(TOP_DIR)/$(MIITOOL) && \
		make CC=$(CFG_HI_ARM_TOOLCHAINS_NAME)-gcc LDFLAGS="-static"

################################################################################
$(TOP_DIR)/tar:
	$(AT)test -d $(TOP_DIR) || mkdir -p $(TOP_DIR)
	$(AT)test -d $(TOP_DIR)/$(MIITOOL) || tar xf $(OPEN_SOURCE_DIR)/$(MIITOOL).tar.tgz -C $(TOP_DIR)
	$(AT)touch $@

