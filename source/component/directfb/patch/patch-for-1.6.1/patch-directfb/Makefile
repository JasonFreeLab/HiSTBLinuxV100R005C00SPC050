#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(shell cd $(CURDIR)/../../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif
#===============================================================================
# export variable
#===============================================================================
.PHONY: all prepare clean

all:prepare
ifeq ($(HI_USER_SPACE_LIB),y)
	$(AT)rm -rf $(HI_STATIC_LIB_DIR)/libdirectfb_hisi_bluetooth.a
	$(AT)rm -rf $(HI_STATIC_LIB_DIR)/libdirectfb_hisi_lirc.a
	$(AT)rm -rf $(HI_STATIC_LIB_DIR)/libdirectfb_hisi_keyboard.a
	$(AT)rm -rf $(HI_STATIC_LIB_DIR)/libdirectfb_hisi_fbdev.a
	$(AT)rm -rf $(HI_STATIC_LIB_DIR)/libdirectfb_hisi_gfx2d.a
	$(AT)test -d $(HI_EXTERN_LIB_DIR)/directfb-1.6-0/inputdrivers || mkdir -p $(HI_EXTERN_LIB_DIR)/directfb-1.6-0/inputdrivers
	$(AT)test -d $(HI_EXTERN_LIB_DIR)/directfb-1.6-0/systems      || mkdir -p $(HI_EXTERN_LIB_DIR)/directfb-1.6-0/systems
	$(AT)test -d $(HI_EXTERN_LIB_DIR)/directfb-1.6-0/gfxdrivers   || mkdir -p $(HI_EXTERN_LIB_DIR)/directfb-1.6-0/gfxdrivers
	$(AT)mv $(HI_SHARED_LIB_DIR)/libdirectfb_hisi_bluetooth.so $(HI_EXTERN_LIB_DIR)/directfb-1.6-0/inputdrivers
	$(AT)mv $(HI_SHARED_LIB_DIR)/libdirectfb_hisi_lirc.so      $(HI_EXTERN_LIB_DIR)/directfb-1.6-0/inputdrivers
	$(AT)mv $(HI_SHARED_LIB_DIR)/libdirectfb_hisi_keyboard.so  $(HI_EXTERN_LIB_DIR)/directfb-1.6-0/inputdrivers
	$(AT)mv $(HI_SHARED_LIB_DIR)/libdirectfb_hisi_fbdev.so     $(HI_EXTERN_LIB_DIR)/directfb-1.6-0/systems
	$(AT)mv $(HI_SHARED_LIB_DIR)/libdirectfb_hisi_gfx2d.so     $(HI_EXTERN_LIB_DIR)/directfb-1.6-0/gfxdrivers
endif
ifeq ($(HI_USER_SPACE_LIB64),y)
	$(AT)rm -rf $(HI_STATIC_LIB64_DIR)/libdirectfb_hisi_bluetooth.a
        $(AT)rm -rf $(HI_STATIC_LIB64_DIR)/libdirectfb_hisi_lirc.a
        $(AT)rm -rf $(HI_STATIC_LIB64_DIR)/libdirectfb_hisi_keyboard.a
        $(AT)rm -rf $(HI_STATIC_LIB64_DIR)/libdirectfb_hisi_fbdev.a
        $(AT)rm -rf $(HI_STATIC_LIB64_DIR)/libdirectfb_hisi_gfx2d.a
	$(AT)test -d $(HI_EXTERN_LIB_DIR)/directfb-1.6-0/inputdrivers || mkdir -p $(HI_EXTERN_LIB_DIR)/directfb-1.6-0/inputdrivers
        $(AT)test -d $(HI_EXTERN_LIB_DIR)/directfb-1.6-0/systems      || mkdir -p $(HI_EXTERN_LIB_DIR)/directfb-1.6-0/systems
        $(AT)test -d $(HI_EXTERN_LIB_DIR)/directfb-1.6-0/gfxdrivers   || mkdir -p $(HI_EXTERN_LIB_DIR)/directfb-1.6-0/gfxdrivers
        $(AT)mv $(HI_SHARED_LIB64_DIR)/libdirectfb_hisi_bluetooth.so $(HI_EXTERN_LIB64_DIR)/directfb-1.6-0/inputdrivers
        $(AT)mv $(HI_SHARED_LIB64_DIR)/libdirectfb_hisi_lirc.so      $(HI_EXTERN_LIB64_DIR)/directfb-1.6-0/inputdrivers
        $(AT)mv $(HI_SHARED_LIB64_DIR)/libdirectfb_hisi_keyboard.so  $(HI_EXTERN_LIB64_DIR)/directfb-1.6-0/inputdrivers
        $(AT)mv $(HI_SHARED_LIB64_DIR)/libdirectfb_hisi_fbdev.so     $(HI_EXTERN_LIB64_DIR)/directfb-1.6-0/systems
        $(AT)mv $(HI_SHARED_LIB64_DIR)/libdirectfb_hisi_gfx2d.so     $(HI_EXTERN_LIB64_DIR)/directfb-1.6-0/gfxdrivers
endif

prepare:
	$(AT)cd systems/fbdev && make
	$(AT)cd gfxdrivers/gfx2d && make
	$(AT)cd inputdrivers/bluetooth && make
	$(AT)cd inputdrivers/lirc && make
	$(AT)cd inputdrivers/keyboard && make

clean:
	$(AT)cd systems/fbdev && make clean
	$(AT)cd gfxdrivers/gfx2d && make clean
	$(AT)cd inputdrivers/bluetooth && make clean
	$(AT)cd inputdrivers/lirc && make clean
	$(AT)cd inputdrivers/keyboard && make clean
