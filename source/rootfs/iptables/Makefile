#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

################################################################################
ifneq ($(HI_OUT_DIR),)
TOP_DIR := $(HI_OUT_DIR)/obj/source/rootfs/iptables
else
TOP_DIR := $(CURDIR)
endif

PREFIX ?= $(HI_ROOTFS_DIR)

BUILD_DIR      := $(TOP_DIR)/tmp
HOST           := $(CFG_HI_ARM_TOOLCHAINS_NAME)

IPTABLES       := iptables-1.6.1

TARGETS        := sbin/iptables sbin/xtables-multi

################################################################################
.PHONY: all clean
################################################################################
all: $(addprefix $(PREFIX)/,$(TARGETS))

clean:
	$(AT)rm -rf $(TOP_DIR)/$(IPTABLES) $(BUILD_DIR)

$(PREFIX)/sbin/xtables-multi: $(BUILD_DIR)/sbin/xtables-multi
	$(AT)test -d $(@D) || mkdir -p $(@D)
	$(AT)install -v -t $(@D) $<

$(PREFIX)/sbin/iptables: $(PREFIX)/sbin/xtables-multi
	$(AT)cd $(@D) && ln -sf $(<F) $(@F)

################################################################################
$(BUILD_DIR)/sbin/xtables-multi: $(TOP_DIR)/tar
	$(AT)cd $(TOP_DIR)/$(IPTABLES) && \
		./configure --host=$(HOST) --prefix=$(BUILD_DIR) \
			-enable-static -disable-shared --disable-nftables \
			--datarootdir=$(BUILD_DIR)     \
			--includedir=$(BUILD_DIR)&& \
		make && make install

################################################################################
$(TOP_DIR)/tar:
	$(AT)test -d $(TOP_DIR) || mkdir -p $(TOP_DIR)
	$(AT)test -d $(TOP_DIR)/$(IPTABLES) || tar -xjf $(OPEN_SOURCE_DIR)/$(IPTABLES).tar.bz2 -C $(TOP_DIR)
	$(AT)touch $@

