#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../../.. && /bin/pwd)

include $(SDK_DIR)/base.mak
endif

#===============================================================================
# local variable
#===============================================================================
HEADER_FILES := $(wildcard include/*.h)

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean

all:
	$(AT)test -d $(HI_INCLUDE_DIR) || mkdir -p $(HI_INCLUDE_DIR)
	$(AT)test -d $(HI_STATIC_LIB_DIR) || mkdir -p $(HI_STATIC_LIB_DIR)
	$(AT)test -d $(HI_SHARED_LIB_DIR) || mkdir -p $(HI_SHARED_LIB_DIR)
	$(AT)cp -f include/cdm.h $(HI_INCLUDE_DIR)
ifneq ($(findstring vmx_ultra, $(CFG_HI_OUT_DIR)),)
	@echo "copy ultra lib"
	$(AT)cp -r ./lib/hi3798mv200_m3/$(CFG_HI_ARM_TOOLCHAINS_NAME)/libhi_widevine*.a $(HI_STATIC_LIB_DIR)/
	$(AT)cp -r ./lib/hi3798mv200_m3/$(CFG_HI_ARM_TOOLCHAINS_NAME)/libhi_widevine*.so $(HI_SHARED_LIB_DIR)/
else
	@echo "copy master lib"
	$(AT)cp -r ./lib/$(CFG_HI_ARM_TOOLCHAINS_NAME)/libhi_widevine*.a $(HI_STATIC_LIB_DIR)/
	$(AT)cp -r ./lib/$(CFG_HI_ARM_TOOLCHAINS_NAME)/libhi_widevine*.so $(HI_SHARED_LIB_DIR)/
endif
	
clean:
	$(AT)rm -rf $(HI_SHARED_LIB_DIR)/libhi_widevineCdm.so
	$(AT)rm -rf $(HI_STATIC_LIB_DIR)/libhi_widevineCdm.a
	$(AT)rm -rf $(HI_SHARED_LIB_DIR)/libhi_widevine_tee.so
	$(AT)rm -rf $(HI_STATIC_LIB_DIR)/libhi_widevine_tee.a
	$(AT)rm -rf $(HI_INCLUDE_DIR)/cdm.h
	$(AT)rm -rf $(HI_SHARED_LIB_DIR)/libtvpsample.so
	$(AT)rm -rf $(HI_SHARED_LIB_DIR)/libhisample_common.so
	$(AT)rm -rf $(HI_SHARED_LIB_DIR)/libhi_widevine_tee_googletest.so

