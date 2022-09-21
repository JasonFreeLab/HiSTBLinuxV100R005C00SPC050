#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

################################################################################
ifneq ($(HI_OUT_DIR),)
PROTOBUF_DIR := $(HI_OUT_DIR)/obj/source/rootfs/protobuf
else
PROTOBUF_DIR := $(CURDIR)
endif

PREFIX ?= $(HI_ROOTFS_DIR)

BUILD_DIR       := $(PROTOBUF_DIR)
HOST            := $(CFG_HI_ARM_TOOLCHAINS_NAME)
STRIP           := $(CFG_HI_ARM_TOOLCHAINS_NAME)-strip

PROTO           := protobuf-2.5.0
TARGETS         := lib/libprotobuf.so.8

################################################################################
.PHONY: all clean

all: $(addprefix $(PREFIX)/,$(TARGETS))

$(PREFIX)/%: $(BUILD_DIR)/%
	$(AT)test -d $(@D) || mkdir -p $(@D)
	$(AT)install -v -t $(dir $@) $<
	$(AT)test -d $(HI_INCLUDE_DIR) || mkdir -p $(HI_INCLUDE_DIR)
	$(AT)cp -rf $(BUILD_DIR)/include/google $(HI_INCLUDE_DIR)/

$(BUILD_DIR)/lib/libprotobuf.so.8: $(PROTOBUF_DIR)/$(PROTO)/tar
	cd $(PROTOBUF_DIR)/$(PROTO) && \
		CPPFLAGS="-P"\
		./configure --host=$(HOST) --without-ada --with-protoc=protoc --prefix=$(BUILD_DIR) && \
		make -j && \
		make install && \
	cd -

$(PROTOBUF_DIR)/$(PROTO)/tar:
	$(AT)test -d $(PROTOBUF_DIR) || mkdir -p $(PROTOBUF_DIR)
	$(AT)test -d $(PROTOBUF_DIR)/$(PROTO) || tar -xzf $(CURDIR)/$(PROTO).tar.gz -C $(PROTOBUF_DIR)
	$(AT)touch $@

clean:
	$(AT)rm -rf $(PROTOBUF_DIR)/$(PROTO) $(PROTOBUF_DIR)/lib $(PROTOBUF_DIR)/bin $(PROTOBUF_DIR)/include

