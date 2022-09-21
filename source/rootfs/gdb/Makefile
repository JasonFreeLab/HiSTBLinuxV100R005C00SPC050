#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

PREFIX ?= $(HI_ROOTFS_DIR)

ifeq ($(CFG_HI_64BIT_SYSTEM),y)
OBJ_NAME := obj64
else
OBJ_NAME := obj
endif

ifneq ($(HI_OUT_DIR),)
GDB_DIR := $(HI_OUT_DIR)/$(OBJ_NAME)/source/rootfs/gdb
else
GDB_DIR := $(CURDIR)
endif

################################################################################
HOST := $(HI_KERNEL_TOOLCHAINS_NAME)
STRIP := $(HOST)-strip

BUILD_DIR       := $(GDB_DIR)/tmp

GDB             := gdb-8.0
NCURSES         := ncurses-6.0

################################################################################
.PHONY: all clean
################################################################################
all: $(PREFIX)/bin/gdb

clean:
	$(AT)rm -rf $(GDB_DIR)/$(GDB) $(GDB_DIR)/$(NCURSES) $(BUILD_DIR)

$(PREFIX)/bin/gdb: $(BUILD_DIR)/bin/gdb
	$(AT)test -d $(@D) || mkdir -p $(@D)
	$(AT)install -v -t $(dir $@) $(BUILD_DIR)/bin/gdb
	$(AT)install -v -t $(dir $@) $(BUILD_DIR)/bin/gdbserver

$(BUILD_DIR)/bin/gdb: $(GDB_DIR)/$(GDB)/tar $(BUILD_DIR)/lib/libncurses.a
	$(AT)cd $(GDB_DIR)/$(GDB) && make $(MKFLAGS)
	$(AT)cp $(GDB_DIR)/$(GDB)/gdb/gdb $(BUILD_DIR)/bin
	$(AT)cp -f $(GDB_DIR)/$(GDB)/gdb/gdbserver/gdbserver $(BUILD_DIR)/bin
	$(AT)cp -f $(GDB_DIR)/$(GDB)/opcodes/libopcodes.a $(BUILD_DIR)/lib
	$(AT)cp -f $(GDB_DIR)/$(GDB)/bfd/libbfd.a $(BUILD_DIR)/lib

$(BUILD_DIR)/lib/libncurses.a: $(GDB_DIR)/$(NCURSES)/tar
	$(AT)cd $(GDB_DIR)/$(NCURSES) && make $(MKFLAGS) && make install

################################################################################
$(GDB_DIR)/$(GDB)/tar:
	$(AT)test -d $(GDB_DIR) || mkdir -p $(GDB_DIR)
	$(AT)test -d $(GDB_DIR)/$(GDB) || tar -xzf $(OPEN_SOURCE_DIR)/$(GDB).tar.gz -C $(GDB_DIR)
	$(AT)cd $(GDB_DIR)/$(GDB) && ./configure --target=$(HOST) --host=$(HOST) --prefix=$(BUILD_DIR) \
        --disable-tui CFLAGS="-g -O2" LDFLAGS="-L$(BUILD_DIR)/lib"
	$(AT)touch $@

$(GDB_DIR)/$(NCURSES)/tar:
	$(AT)test -d $(GDB_DIR) || mkdir -p $(GDB_DIR)
	$(AT)test -d $(GDB_DIR)/$(NCURSES) || tar -xjf $(OPEN_SOURCE_DIR)/$(NCURSES).tar.bz2 -C $(GDB_DIR)
	$(AT)cd $(GDB_DIR)/$(NCURSES) && CPPFLAGS="-P" ./configure --host=$(HOST) --without-ada \
        --without-manpages --prefix=$(BUILD_DIR)
	$(AT)touch $@
