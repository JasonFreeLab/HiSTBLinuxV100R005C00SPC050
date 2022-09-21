#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(shell cd $(CURDIR)/../../../.. && /bin/pwd)

include $(SDK_DIR)/base.mak
endif

#===================================================================
#Lib jpeg turbo Version
#==================================================================
JPEG_NAME := libjpeg-turbo
LIB_TURBO_VER := 1.5.1
LIBJPEG_TURBO := $(JPEG_NAME)-$(LIB_TURBO_VER)
LIBJPEG_PATH  := patch/patch_turbo_$(LIB_TURBO_VER)
LIBJPEG_TAG   := $(LIBJPEG_TURBO).tar.gz
#===================================================================
#Lib jpeg-6b
#==================================================================
#JPEG_NAME := libjpeg-9b
#LIBJPEG_TURBO := jpeg-9b
#LIBJPEG_PATH  := patch/patch_linux_9b
#LIBJPEG_TAG   := jpegsrc.v9b.tar.gz

LIBJPEG_HARD_DEC := src/src_hard
LIBJPEG_SOFT_DEC := src/src_soft
LIBJPEG_SOFT_INC := inc/inc_soft
#===============================================================================
# local variable
#===============================================================================
JPEG_OUT_DIR := $(HI_OUT_DIR)/obj/source/msp/api/jpeg
JPEG_OUT_DIR64 := $(HI_OUT_DIR)/obj64/source/msp/api/jpeg

INSTALL_DIR := $(JPEG_OUT_DIR)/jpeg
INSTALL_DIR64 := $(JPEG_OUT_DIR64)/jpeg


ifeq ($(HI_USER_SPACE_LIB),y)
TARGETS += $(JPEG_NAME)
endif
ifeq ($(HI_USER_SPACE_LIB64),y)
TARGETS += $(JPEG_NAME)64
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

INCLUDES += -I$(MSP_DIR)/api/jpeg/patch/patch       \
            -I$(MSP_DIR)/api/jpeg/inc/inc_hard      \
	    -I$(MSP_DIR)/api/jpeg/src/src_hard      \
            -I$(MSP_DIR)/api/jpeg/src/src_soft      \
            -I$(MSP_DIR)/api/jpeg/grc_cmm_inc       \
            -I$(MSP_DIR)/api/tde/include            \
            -I$(MSP_DIR)/drv/include/               \
            -I$(MSP_DIR)/drv/jpeg/include/          \
            -I$(COMMON_DIR)/include                 \
            -I$(COMMON_DIR)/api/include

#===================================================================
#CFLAGS
#==================================================================
CFLAGS := -O2 -DCHIP_TYPE_$(CFG_HI_CHIP_TYPE)

CFLAGS += -DCONFIG_HI_SDK_JPEG_VERSION

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
endif

ifeq ($(CFG_HI_GFX_DEBUG_LOG_SUPPORT), y)
CFLAGS += -DCFG_HI_GFX_DEBUG_LOG_SUPPORT
endif

ifeq ($(CFG_HI_JPEG_SOFT_ENCODE_SUPPORT),y)
CFLAGS += -DCONFIG_GFX_JPGE_SOFT_ENC_ENABLE
endif

ifdef CFG_HI_STATIC_LIB_ONLY
#directfb needed
CFLAGS += -fPIC
endif

CFLAGS += $(INCLUDES)

#===============================================================================
# api include
#===============================================================================
HEADER_FILES := $(MSP_DIR)/api/jpeg/inc/inc_soft/jpeglib.h
HEADER_FILES += $(MSP_DIR)/api/jpeg/inc/inc_soft/jmorecfg.h
HEADER_FILES += $(MSP_DIR)/api/jpeg/inc/inc_soft/jerror.h
HEADER_FILES += $(MSP_DIR)/api/jpeg/inc/inc_soft/jconfig.h
#HEADER_FILES += $(MSP_DIR)/api/jpeg/inc/inc_soft/turbojpeg.h
#===============================================================================
# rules
#===============================================================================
.PHONY: all clean $(JPEG_NAME) $(JPEG_NAME)64

all: $(TARGETS)
	$(AT)test -d $(HI_INCLUDE_DIR) || mkdir -p $(HI_INCLUDE_DIR)
	$(AT)cp -rf $(HEADER_FILES) $(HI_INCLUDE_DIR)/
ifeq ($(HI_USER_SPACE_LIB),y)
	$(AT)test -d $(HI_SHARED_LIB_DIR) || mkdir -p $(HI_SHARED_LIB_DIR)
	$(AT)test -d $(HI_STATIC_LIB_DIR) || mkdir -p $(HI_STATIC_LIB_DIR)
	$(AT)cp -ralf $(INSTALL_DIR)/lib/libjpeg*.so* $(HI_SHARED_LIB_DIR)
	$(AT)cp -ralf $(INSTALL_DIR)/lib/libjpeg*.a*  $(HI_STATIC_LIB_DIR)
endif
ifeq ($(HI_USER_SPACE_LIB64),y)
	$(AT)test -d $(HI_SHARED_LIB64_DIR) || mkdir -p $(HI_SHARED_LIB64_DIR)
	$(AT)test -d $(HI_STATIC_LIB64_DIR) || mkdir -p $(HI_STATIC_LIB64_DIR)
	$(AT)cp -ralf $(INSTALL_DIR64)/lib/lib*jpeg.so* $(HI_SHARED_LIB64_DIR)
	$(AT)cp -ralf $(INSTALL_DIR64)/lib/lib*jpeg.a*  $(HI_STATIC_LIB64_DIR)
endif

clean:
	$(AT)rm -rf $(INSTALL_DIR) $(INSTALL_DIR64)
	$(AT)rm -rf $(JPEG_OUT_DIR) $(JPEG_OUT_DIR64)
	$(AT)rm -rf $(HI_INCLUDE_DIR)/jpeglib.h
	$(AT)rm -rf $(HI_INCLUDE_DIR)/jmorecfg.h
	$(AT)rm -rf $(HI_INCLUDE_DIR)/jerror.h
	$(AT)rm -rf $(HI_INCLUDE_DIR)/jconfig.h
	$(AT)rm -rf $(HI_INCLUDE_DIR)/hi_jpeg_api.h
	$(AT)rm -rf $(HI_SHARED_LIB_DIR)/lib*jpeg*.so*
	$(AT)rm -rf $(HI_STATIC_LIB_DIR)/lib*jpeg*.a*
	$(AT)rm -rf $(HI_SHARED_LIB64_DIR)/lib*jpeg*.so*
	$(AT)rm -rf $(HI_STATIC_LIB64_DIR)/lib*jpeg*.a*

$(JPEG_NAME): $(JPEG_OUT_DIR)/$(LIBJPEG_TURBO)/tar
	$(AT)cd $(JPEG_OUT_DIR)/$(LIBJPEG_TURBO) && make install

$(JPEG_NAME)64: $(JPEG_OUT_DIR64)/$(LIBJPEG_TURBO)/tar
	$(AT)cd $(JPEG_OUT_DIR64)/$(LIBJPEG_TURBO) && make install

$(JPEG_OUT_DIR)/$(LIBJPEG_TURBO)/tar:
	$(AT)test -d $(INSTALL_DIR) || mkdir -p $(INSTALL_DIR)
	$(AT)test -d $(JPEG_OUT_DIR)/$(LIBJPEG_TURBO) || tar xf $(OPEN_SOURCE_DIR)/$(LIBJPEG_TAG) -C $(JPEG_OUT_DIR)
	$(AT)cp -rf $(LIBJPEG_PATH)/*       $(JPEG_OUT_DIR)/$(LIBJPEG_TURBO)/
	$(AT)cp -rf $(LIBJPEG_HARD_DEC)/*.c $(JPEG_OUT_DIR)/$(LIBJPEG_TURBO)/
	$(AT)cp -rf $(LIBJPEG_SOFT_DEC)/*.c $(JPEG_OUT_DIR)/$(LIBJPEG_TURBO)/
	$(AT)cp -rf $(LIBJPEG_SOFT_INC)/*   $(JPEG_OUT_DIR)/$(LIBJPEG_TURBO)/
	$(AT)cd $(JPEG_OUT_DIR)/$(LIBJPEG_TURBO) && sh ./configure --host=$(CFG_HI_ARM_TOOLCHAINS_NAME) --prefix=$(INSTALL_DIR) --build=x86 CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)" CPPFLAGS="$(CPPFLAGS)" CC=$(CFG_HI_ARM_TOOLCHAINS_NAME)-gcc CPP=$(CFG_HI_ARM_TOOLCHAINS_NAME)-cpp AR=$(CFG_HI_ARM_TOOLCHAINS_NAME)-ar AS=$(CFG_HI_ARM_TOOLCHAINS_NAME)-as LD=$(CFG_HI_ARM_TOOLCHAINS_NAME)-ld NM=$(CFG_HI_ARM_TOOLCHAINS_NAME)-nm STRIP=$(CFG_HI_ARM_TOOLCHAINS_NAME)-strip OBJDUMP=$(CFG_HI_ARM_TOOLCHAINS_NAME)-objdump
	$(AT)touch $@

$(JPEG_OUT_DIR64)/$(LIBJPEG_TURBO)/tar:
	$(AT)test -d $(INSTALL_DIR64) || mkdir -p $(INSTALL_DIR64)
	$(AT)test -d $(JPEG_OUT_DIR64)/$(LIBJPEG_TURBO) || tar xf $(OPEN_SOURCE_DIR)/$(LIBJPEG_TAG) -C $(JPEG_OUT_DIR64)
	$(AT)cp -rf $(LIBJPEG_PATH)/*       $(JPEG_OUT_DIR64)/$(LIBJPEG_TURBO)/
	$(AT)cp -rf $(LIBJPEG_HARD_DEC)/*.c $(JPEG_OUT_DIR64)/$(LIBJPEG_TURBO)
	$(AT)cp -rf $(LIBJPEG_SOFT_DEC)/*.c $(JPEG_OUT_DIR64)/$(LIBJPEG_TURBO)/
	$(AT)cp -rf $(LIBJPEG_SOFT_INC)/*   $(JPEG_OUT_DIR64)/$(LIBJPEG_TURBO)/
	$(AT)cd $(JPEG_OUT_DIR64)/$(LIBJPEG_TURBO) && sh ./configure --host=$(CFG_HI_AARCH64_TOOLCHAINS_NAME) --prefix=$(INSTALL_DIR64) --build=x86 CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS64)" CPPFLAGS="$(CPPFLAGS)" CC=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-gcc CPP=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-cpp AR=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-ar AS=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-as LD=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-ld NM=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-nm STRIP=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-strip OBJDUMP=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-objdump
	$(AT)touch $@
