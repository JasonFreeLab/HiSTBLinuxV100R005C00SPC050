#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../.. && /bin/pwd)

include $(SDK_DIR)/base.mak
endif

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean

all:
	$(AT)test -d $(HI_INCLUDE_DIR) || mkdir -p $(HI_INCLUDE_DIR)
	$(AT)cp -f include/drm_engine_interface.h $(HI_INCLUDE_DIR)
ifeq ($(HI_USER_SPACE_LIB),y)
	$(AT)test -d $(HI_SHARED_LIB_DIR) || mkdir -p $(HI_SHARED_LIB_DIR)
	$(AT)cp -r ./lib/$(CFG_HI_ARM_TOOLCHAINS_NAME)/libhi_drm_engine.so $(HI_SHARED_LIB_DIR)/
	$(AT)cp -r ./lib/$(CFG_HI_ARM_TOOLCHAINS_NAME)/libandroid.so $(HI_SHARED_LIB_DIR)/
	$(AT)cp -r ./lib/$(CFG_HI_ARM_TOOLCHAINS_NAME)/libutils.so $(HI_SHARED_LIB_DIR)/
	$(AT)cp -r ./lib/$(CFG_HI_ARM_TOOLCHAINS_NAME)/libcutils.so $(HI_SHARED_LIB_DIR)/
	$(AT)cp -r ./lib/$(CFG_HI_ARM_TOOLCHAINS_NAME)/liblog.so $(HI_SHARED_LIB_DIR)/
endif
ifeq ($(HI_USER_SPACE_LIB64),y)
	$(AT)test -d $(HI_SHARED_LIB64_DIR) || mkdir -p $(HI_SHARED_LIB64_DIR)
	$(AT)cp -r ./lib/$(CFG_HI_AARCH64_TOOLCHAINS_NAME)/libhi_drm_engine.so $(HI_SHARED_LIB64_DIR)/
	$(AT)cp -r ./lib/$(CFG_HI_AARCH64_TOOLCHAINS_NAME)/libandroid.so $(HI_SHARED_LIB64_DIR)/
	$(AT)cp -r ./lib/$(CFG_HI_AARCH64_TOOLCHAINS_NAME)/libutils.so $(HI_SHARED_LIB64_DIR)/
	$(AT)cp -r ./lib/$(CFG_HI_AARCH64_TOOLCHAINS_NAME)/libcutils.so $(HI_SHARED_LIB64_DIR)/
	$(AT)cp -r ./lib/$(CFG_HI_AARCH64_TOOLCHAINS_NAME)/liblog.so $(HI_SHARED_LIB64_DIR)/
endif

clean:
	$(AT)rm -rf $(HI_INCLUDE_DIR)/drm_engine_interface.h
	$(AT)rm -rf $(HI_SHARED_LIB_DIR)/libhi_drm_engine.so
	$(AT)rm -rf $(HI_SHARED_LIB_DIR)/libandroid.so
	$(AT)rm -rf $(HI_SHARED_LIB_DIR)/libutils.so
	$(AT)rm -rf $(HI_SHARED_LIB_DIR)/libcutils.so
	$(AT)rm -rf $(HI_SHARED_LIB_DIR)/liblog.so
	$(AT)rm -rf $(HI_SHARED_LIB64_DIR)/libhi_drm_engine.so
	$(AT)rm -rf $(HI_SHARED_LIB64_DIR)/libandroid.so
	$(AT)rm -rf $(HI_SHARED_LIB64_DIR)/libutils.so
	$(AT)rm -rf $(HI_SHARED_LIB64_DIR)/libcutils.so
	$(AT)rm -rf $(HI_SHARED_LIB64_DIR)/liblog.so
