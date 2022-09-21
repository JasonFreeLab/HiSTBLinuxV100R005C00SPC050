#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(shell cd $(CURDIR)/../../../.. && /bin/pwd)

include $(SDK_DIR)/base.mak
endif

#===================================================================
#Lib png turbo Version
#==================================================================
PNG_NAME := libpng
LIB_VER := 1.6.29
LIBPNG_NAME := $(PNG_NAME)-$(LIB_VER)
LIBPNG_PATH  := patch
LIBPNG_TAG   := $(LIBPNG_NAME).tar.gz

LIBPNG_HARD_DEC := src/src_hard
LIBPNG_SOFT_INC := inc/inc_soft
#===============================================================================
# local variable
#===============================================================================
PNG_OUT_DIR := $(HI_OUT_DIR)/obj/source/msp/api/png
PNG_OUT_DIR64 := $(HI_OUT_DIR)/obj64/source/msp/api/png

INSTALL_DIR := $(PNG_OUT_DIR)/png
INSTALL_DIR64 := $(PNG_OUT_DIR64)/png


ifeq ($(HI_USER_SPACE_LIB),y)
TARGETS += $(PNG_NAME)
endif
ifeq ($(HI_USER_SPACE_LIB64),y)
TARGETS += $(PNG_NAME)64
endif

#=====================================================================================
#export env
#=====================================================================================
ifeq ($(HI_USER_SPACE_LIB),y)
INCLUDES := -I$(INSTALL_DIR)/include
endif
ifeq ($(HI_USER_SPACE_LIB64),y)
INCLUDES := -I$(INSTALL_DIR64)/include
endif

CFLAGS := -O2 -DCHIP_TYPE_$(CFG_HI_CHIP_TYPE)

CFLAGS += -I$(MSP_DIR)/api/png/inc/inc_hard       \
          -I$(MSP_DIR)/drv/png/include            \
          -I$(MSP_DIR)/api/jpeg/grc_cmm_inc       \
          -I$(COMMON_DIR)/include                 \
          -I$(MSP_DIR)/drv/include                \
          -I$(COMMON_DIR)/api/include             \
          -I$(COMPONENT_DIR)/zlib/include

ZLIBLIB = $(COMPONENT_DIR)/zlib/release/lib
ZLIBINC = $(COMPONENT_DIR)/zlib/include
#===================================================================
#CFLAGS
#==================================================================
CFLAGS  +=  -DHIGFX_COMMON

ifeq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716mv310 hi3716mv320 hi3110ev500),)
CFLAGS += -DHIPNG_ACCELERATE
endif

ifneq ($(findstring $(CFG_HI_CFLAGS), -DHI_ADVCA_FUNCTION_RELEASE),)
CFLAGS += -DHI_ADVCA_FUNCTION_RELEASE
endif

ifeq ($(CFG_HI_PROC_SUPPORT),y)
CFG_HI_CFLAGS += -DHI_PROC_SUPPORT=1
else
CFG_HI_CFLAGS += -DHI_PROC_SUPPORT=0
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798cv200 hi3798mv200 hi3798mv300 hi3796mv200 hi3798mv200_a),)
CFLAGS += -DCONFIG_GFX_MEM_ION
else
CFLAGS += -DCONFIG_GFX_MEM_MMZ
endif

ifeq ($(CFG_HI_SMMU_SUPPORT),y)
CFLAGS += -DCONFIG_GFX_MMU_SUPPORT
CFLAGS += -DHI_SMMU_SUPPORT
endif

ifeq ($(CFG_HI_PROC_SUPPORT),y)
CFLAGS += -DHI_PROC_SUPPORT=1
else
CFLAGS += -DHI_PROC_SUPPORT=0
CFLAGS += -DCONFIG_PNG_PROC_DISABLE
endif

ifeq ($(CFG_HI_GFX_DEBUG_LOG_SUPPORT), y)
CFLAGS += -DCFG_HI_GFX_DEBUG_LOG_SUPPORT
endif

ifdef CFG_HI_STATIC_LIB_ONLY
CFLAGS += -fPIC
endif

#===============================================================================
# api include
#===============================================================================
HEADER_FILES := $(MSP_DIR)/api/png/inc/inc_soft/png.h
HEADER_FILES += $(MSP_DIR)/api/png/inc/inc_soft/pngconf.h
HEADER_FILES += $(MSP_DIR)/api/png/inc/inc_soft/pnglibconf.h
#===============================================================================
# rules
#===============================================================================
.PHONY: all clean $(PNG_NAME) $(PNG_NAME)64

all: $(TARGETS)
	$(AT)test -d $(HI_INCLUDE_DIR) || mkdir -p $(HI_INCLUDE_DIR)
	$(AT)cp -rf $(HEADER_FILES) $(HI_INCLUDE_DIR)/
ifeq ($(HI_USER_SPACE_LIB),y)
	$(AT)test -d $(HI_SHARED_LIB_DIR) || mkdir -p $(HI_SHARED_LIB_DIR)
	$(AT)test -d $(HI_STATIC_LIB_DIR) || mkdir -p $(HI_STATIC_LIB_DIR)
	$(AT)cp -ralf $(INSTALL_DIR)/lib/lib*png*.so* $(HI_SHARED_LIB_DIR)
	$(AT)cp -ralf $(INSTALL_DIR)/lib/lib*png*.a*  $(HI_STATIC_LIB_DIR)
	$(AT)cd $(HI_STATIC_LIB_DIR) && ln -sf libpng16.a libpng.a
	$(AT)cd $(HI_SHARED_LIB_DIR) && ln -sf libpng16.so libpng.so
endif
ifeq ($(HI_USER_SPACE_LIB64),y)
	$(AT)test -d $(HI_SHARED_LIB64_DIR) || mkdir -p $(HI_SHARED_LIB64_DIR)
	$(AT)test -d $(HI_STATIC_LIB64_DIR) || mkdir -p $(HI_STATIC_LIB64_DIR)
	$(AT)cp -ralf $(INSTALL_DIR64)/lib/lib*png*.so* $(HI_SHARED_LIB64_DIR)
	$(AT)cp -ralf $(INSTALL_DIR64)/lib/lib*png*.a*  $(HI_STATIC_LIB64_DIR)
	$(AT)cd $(HI_STATIC_LIB64_DIR) && ln -sf libpng16.a libpng.a
	$(AT)cd $(HI_SHARED_LIB64_DIR) && ln -sf libpng16.so libpng.so
endif

clean:
	$(AT)rm -rf $(INSTALL_DIR) $(INSTALL_DIR64)
	$(AT)rm -rf $(PNG_OUT_DIR) $(PNG_OUT_DIR64)
	$(AT)rm -rf $(HI_INCLUDE_DIR)/png.h
	$(AT)rm -rf $(HI_INCLUDE_DIR)/pngconf.h
	$(AT)rm -rf $(HI_INCLUDE_DIR)/pnglibconf.h
	$(AT)rm -rf $(HI_SHARED_LIB_DIR)/lib*png*.so*
	$(AT)rm -rf $(HI_STATIC_LIB_DIR)/lib*png*.a*
	$(AT)rm -rf $(HI_SHARED_LIB64_DIR)/lib*png*.so*
	$(AT)rm -rf $(HI_STATIC_LIB64_DIR)/lib*png*.a*

$(PNG_NAME): $(PNG_OUT_DIR)/$(LIBPNG_NAME)/tar
	$(AT)cd $(PNG_OUT_DIR)/$(LIBPNG_NAME) && make install-libLTLIBRARIES

$(PNG_NAME)64: $(PNG_OUT_DIR64)/$(LIBPNG_NAME)/tar
	$(AT)cd $(PNG_OUT_DIR64)/$(LIBPNG_NAME) && make install-libLTLIBRARIES

$(PNG_OUT_DIR)/$(LIBPNG_NAME)/tar:
	$(AT)test -d $(INSTALL_DIR) || mkdir -p $(INSTALL_DIR)
	$(AT)test -d $(PNG_OUT_DIR)/$(LIBPNG_NAME) || tar xf $(OPEN_SOURCE_DIR)/$(LIBPNG_TAG) -C $(PNG_OUT_DIR)
	$(AT)cp -rf $(LIBPNG_SOFT_INC)/*                $(PNG_OUT_DIR)/$(LIBPNG_NAME)/
	$(AT)cp -rf $(LIBPNG_PATH)/patch_$(LIB_VER)/*   $(PNG_OUT_DIR)/$(LIBPNG_NAME)/
	$(AT)cp -rf $(LIBPNG_PATH)/patch/*              $(PNG_OUT_DIR)/$(LIBPNG_NAME)/
	$(AT)cp -rf $(LIBPNG_HARD_DEC)/*                $(PNG_OUT_DIR)/$(LIBPNG_NAME)/
	$(AT)cd $(PNG_OUT_DIR)/$(LIBPNG_NAME) && sh ./configure --host=$(CFG_HI_ARM_TOOLCHAINS_NAME) --prefix=$(INSTALL_DIR) --build=x86 ZLIBINC=$(ZLIBINC) CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)" CPPFLAGS="$(CPPFLAGS)" CC=$(CFG_HI_ARM_TOOLCHAINS_NAME)-gcc CPP=$(CFG_HI_ARM_TOOLCHAINS_NAME)-cpp AR=$(CFG_HI_ARM_TOOLCHAINS_NAME)-ar AS=$(CFG_HI_ARM_TOOLCHAINS_NAME)-as LD=$(CFG_HI_ARM_TOOLCHAINS_NAME)-ld NM=$(CFG_HI_ARM_TOOLCHAINS_NAME)-nm STRIP=$(CFG_HI_ARM_TOOLCHAINS_NAME)-strip OBJDUMP=$(CFG_HI_ARM_TOOLCHAINS_NAME)-objdump
	$(AT)touch $@

$(PNG_OUT_DIR64)/$(LIBPNG_NAME)/tar:
	$(AT)test -d $(INSTALL_DIR64) || mkdir -p $(INSTALL_DIR64)
	$(AT)test -d $(PNG_OUT_DIR64)/$(LIBPNG_NAME) || tar xf $(OPEN_SOURCE_DIR)/$(LIBPNG_TAG) -C $(PNG_OUT_DIR64)
	$(AT)cp -rf $(LIBPNG_SOFT_INC)/*                $(PNG_OUT_DIR64)/$(LIBPNG_NAME)/
	$(AT)cp -rf $(LIBPNG_PATH)/patch_$(LIB_VER)/*   $(PNG_OUT_DIR64)/$(LIBPNG_NAME)/
	$(AT)cp -rf $(LIBPNG_PATH)/patch/*              $(PNG_OUT_DIR64)/$(LIBPNG_NAME)/
	$(AT)cp -rf $(LIBPNG_HARD_DEC)/*                $(PNG_OUT_DIR64)/$(LIBPNG_NAME)
	$(AT)cd $(PNG_OUT_DIR64)/$(LIBPNG_NAME) && sh ./configure --host=$(CFG_HI_AARCH64_TOOLCHAINS_NAME) --prefix=$(INSTALL_DIR64) --build=x86 ZLIBINC=$(ZLIBINC) CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS64)" CPPFLAGS="$(CPPFLAGS)" CC=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-gcc CPP=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-cpp AR=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-ar AS=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-as LD=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-ld NM=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-nm STRIP=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-strip OBJDUMP=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-objdump
	$(AT)touch $@
