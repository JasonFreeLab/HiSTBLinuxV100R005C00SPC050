#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

################################################################################
ifneq ($(HI_OUT_DIR),)
TOP_DIR := $(HI_OUT_DIR)/obj/source/rootfs/iperf
else
TOP_DIR := $(CURDIR)
endif

PREFIX ?= $(HI_ROOTFS_DIR)

BUILD_DIR      := $(TOP_DIR)/tmp
HOST           := $(CFG_HI_ARM_TOOLCHAINS_NAME)
STRIP          := $(CFG_HI_ARM_TOOLCHAINS_NAME)-strip
IPERF          := iperf-3.0.9

################################################################################
.PHONY: all clean
################################################################################
all: $(PREFIX)/sbin/iperf3

clean:
	$(AT)rm -rf $(TOP_DIR)/$(IPERF)

$(PREFIX)/sbin/iperf3: $(TOP_DIR)/$(IPERF)/src/iperf3
	$(AT)test -d $(@D) || mkdir -p $(@D)
	$(AT)install -v -t $(@D) $<

$(TOP_DIR)/$(IPERF)/src/iperf3: $(TOP_DIR)/tar
	$(AT)cd $(TOP_DIR)/$(IPERF) && \
		./configure CC=gcc CPP="gcc -E" && \
		make CC=$(CFG_HI_ARM_TOOLCHAINS_NAME)-gcc CXX=$(CFG_HI_ARM_TOOLCHAINS_NAME)-g++ LDFLAGS="-static"

################################################################################
$(TOP_DIR)/tar:
	$(AT)test -d $(TOP_DIR) || mkdir -p $(TOP_DIR)
	$(AT)test -d $(TOP_DIR)/$(IPERF) || tar -xzf $(OPEN_SOURCE_DIR)/$(IPERF).tar.gz -C $(TOP_DIR)
	$(AT)touch $@

