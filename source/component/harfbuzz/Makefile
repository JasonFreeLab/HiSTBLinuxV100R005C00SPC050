#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(shell cd $(CURDIR)/../../.. && /bin/pwd)

include $(SDK_DIR)/base.mak
endif

#===============================================================================
# local variable
#===============================================================================
HARFBUZZ := harfbuzz-1.4.6

CFLAGS  +=  $(CFG_HI_CFLAGS)
#CFLAGS += $(subst -Werror,,$(CFG_HI_CFLAGS))

ifneq ($(findstring -fPIC, $(CFG_HI_CFLAGS)), -fPIC)
CFLAGS += -fPIC
endif

HARFBUZZ_DIR := $(HI_OUT_DIR)/obj/source/component/harfbuzz
INSTALL_DIR := $(HARFBUZZ_DIR)/release

HARFBUZZ_DIR64 := $(HI_OUT_DIR)/obj64/source/component/harfbuzz
INSTALL_DIR64 := $(HARFBUZZ_DIR64)/release

TARGETS :=

ifeq ($(HI_USER_SPACE_LIB),y)
TARGETS += harfbuzz
HARF_INC := $(INSTALL_DIR)/include/harfbuzz
endif

ifeq ($(HI_USER_SPACE_LIB64),y)
TARGETS += harfbuzz64
HARF_INC := $(INSTALL_DIR64)/include/harfbuzz
endif

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean harfbuzz harfbuzz64

all: $(TARGETS)
	$(AT)cp -rf $(HARF_INC)/* ./include
ifeq ($(HI_USER_SPACE_LIB),y)
	$(AT)test -d $(HI_STATIC_LIB_DIR) || mkdir -p $(HI_STATIC_LIB_DIR)
	$(AT)test -d $(HI_SHARED_LIB_DIR) || mkdir -p $(HI_SHARED_LIB_DIR)
	$(AT)cp -ralf $(INSTALL_DIR)/lib/libharfbuzz.a   $(HI_STATIC_LIB_DIR)/
	$(AT)cp -ralf $(INSTALL_DIR)/lib/libharfbuzz.so* $(HI_SHARED_LIB_DIR)/
endif
ifeq ($(HI_USER_SPACE_LIB64),y)
	$(AT)test -d $(HI_STATIC_LIB64_DIR) || mkdir -p $(HI_STATIC_LIB64_DIR)
	$(AT)test -d $(HI_SHARED_LIB64_DIR) || mkdir -p $(HI_SHARED_LIB64_DIR)
	$(AT)cp -ralf $(INSTALL_DIR64)/lib/libharfbuzz.a    $(HI_STATIC_LIB64_DIR)/
	$(AT)cp -ralf $(INSTALL_DIR64)/lib/libharfbuzz.so*  $(HI_SHARED_LIB64_DIR)/
endif

clean:
	$(AT)rm -rf $(INSTALL_DIR) $(INSTALL_DIR64) $(HARFBUZZ_DIR)/$(HARFBUZZ) $(HARFBUZZ_DIR64)/$(HARFBUZZ)
	$(AT)rm -rf $(HI_STATIC_LIB_DIR)/libharfbuzz.a   $(HI_SHARED_LIB_DIR)/libharfbuzz.so*
	$(AT)rm -rf $(HI_STATIC_LIB64_DIR)/libharfbuzz.a $(HI_SHARED_LIB64_DIR)/libharfbuzz.so*

harfbuzz: $(HARFBUZZ_DIR)/$(HARFBUZZ)/tar
	$(AT)cd $(HARFBUZZ_DIR)/$(HARFBUZZ) && make && make install

harfbuzz64: $(HARFBUZZ_DIR64)/$(HARFBUZZ)/tar
	$(AT)cd $(HARFBUZZ_DIR64)/$(HARFBUZZ) && make && make install

$(HARFBUZZ_DIR)/$(HARFBUZZ)/tar:
	$(AT)test -d $(INSTALL_DIR) || mkdir -p $(INSTALL_DIR)
	$(AT)test -d $(HARFBUZZ_DIR)/$(HARFBUZZ) || (tar xf $(OPEN_SOURCE_DIR)/$(HARFBUZZ).tar.bz2 -C $(HARFBUZZ_DIR); cp -rf $(COMPONENT_DIR)/harfbuzz/patch-for-harfbuzz/* $(HARFBUZZ_DIR)/$(HARFBUZZ);\
        cd $(HARFBUZZ_DIR)/$(HARFBUZZ);\
        sh ./configure CC=$(CFG_HI_ARM_TOOLCHAINS_NAME)-gcc CXX=$(CFG_HI_ARM_TOOLCHAINS_NAME)-g++ AR=$(CFG_HI_ARM_TOOLCHAINS_NAME)-ar AS=$(CFG_HI_ARM_TOOLCHAINS_NAME)-as LD=$(CFG_HI_ARM_TOOLCHAINS_NAME)-ld NM=$(CFG_HI_ARM_TOOLCHAINS_NAME)-nm STRIP=$(CFG_HI_ARM_TOOLCHAINS_NAME)-strip OBJDUMP=$(CFG_HI_ARM_TOOLCHAINS_NAME)-objdump --host=$(CFG_HI_ARM_TOOLCHAINS_NAME) --with-glib=no --with-gobject=no --with-cairo=no  --with-fontconfig=no --with-icu=no --with-graphite2=no --with-freetype=no --with-uniscribe=no --with-coretext=no --enable-shared --enable-static CFLAGS="$(CFLAGS)" --prefix=$(INSTALL_DIR) ;\
	cp -rf $(COMPONENT_DIR)/harfbuzz/patch-for-harfbuzz/config.h ./;)
	$(AT)touch $@

$(HARFBUZZ_DIR64)/$(HARFBUZZ)/tar:
	$(AT)test -d $(INSTALL_DIR64) || mkdir -p $(INSTALL_DIR64)
	$(AT)test -d $(HARFBUZZ_DIR64)/$(HARFBUZZ) || (tar xf $(OPEN_SOURCE_DIR)/$(HARFBUZZ).tar.bz2 -C $(HARFBUZZ_DIR64); cp -rf $(COMPONENT_DIR)/harfbuzz/patch-for-harfbuzz/* $(HARFBUZZ_DIR64)/$(HARFBUZZ);\
        cd $(HARFBUZZ_DIR64)/$(HARFBUZZ);\
        sh ./configure CC=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-gcc CXX=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-g++ AR=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-ar AS=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-as LD=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-ld NM=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-nm STRIP=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-strip OBJDUMP=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-objdump --host=$(CFG_HI_AARCH64_TOOLCHAINS_NAME) --with-glib=no --with-gobject=no --with-cairo=no  --with-fontconfig=no --with-icu=no --with-graphite2=no --with-freetype=no --with-uniscribe=no --with-coretext=no --enable-shared --enable-static CFLAGS="$(CFLAGS)" --prefix=$(INSTALL_DIR64);\
	cp -rf $(COMPONENT_DIR)/harfbuzz/patch-for-harfbuzz/config.h ./;)
	$(AT)touch $@
