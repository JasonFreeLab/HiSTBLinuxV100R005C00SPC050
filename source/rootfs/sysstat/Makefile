#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

ifneq ($(HI_OUT_DIR),)
TOP_DIR := $(HI_OUT_DIR)/obj/source/rootfs/sysstat
else
TOP_DIR := $(CURDIR)
endif

PREFIX ?= $(HI_ROOTFS_DIR)

################################################################################
BUILD_DIR      := $(TOP_DIR)/tmp
HOST           := $(CFG_HI_ARM_TOOLCHAINS_NAME)
STRIP          := $(CFG_HI_ARM_TOOLCHAINS_NAME)-strip
SYSSTAT        := sysstat-11.4.5

################################################################################
.PHONY: all clean
################################################################################
all: $(PREFIX)/sbin/mpstat

clean:
	$(AT)rm -rf $(TOP_DIR)/$(SYSSTAT)

$(PREFIX)/sbin/mpstat: $(TOP_DIR)/$(SYSSTAT)/mpstat
	$(AT)test -d $(@D) || mkdir -p $(@D)
	$(AT)install -vs -t $(@D) --strip-program=$(STRIP) $(TOP_DIR)/$(SYSSTAT)/mpstat
	$(AT)install -vs -t $(@D) --strip-program=$(STRIP) $(TOP_DIR)/$(SYSSTAT)/sar
	$(AT)install -vs -t $(@D) --strip-program=$(STRIP) $(TOP_DIR)/$(SYSSTAT)/iostat
	$(AT)install -vs -t $(@D) --strip-program=$(STRIP) $(TOP_DIR)/$(SYSSTAT)/sadc
	$(AT)install -vs -t $(@D) --strip-program=$(STRIP) $(TOP_DIR)/$(SYSSTAT)/sadf

$(TOP_DIR)/$(SYSSTAT)/mpstat: $(TOP_DIR)/tar
	cd $(TOP_DIR)/$(SYSSTAT) && \
		./configure --host=$(HOST) --prefix=$(BUILD_DIR) \
			--exec-prefix=$(BUILD_DIR) CFLAGS="-static" && \
		make

################################################################################
$(TOP_DIR)/tar:
	$(AT)test -d $(TOP_DIR) || mkdir -p $(TOP_DIR)
	$(AT)test -d $(TOP_DIR)/$(SYSSTAT) || tar Jxf $(OPEN_SOURCE_DIR)/$(SYSSTAT).tar.xz -C $(TOP_DIR)/
	$(AT)touch $@

