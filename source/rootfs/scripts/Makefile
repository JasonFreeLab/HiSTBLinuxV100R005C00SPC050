################################################################################
#    ./scripts/Makefile
#    Create By CaiZhiYong
#    2011.06.19
################################################################################
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

PREFIX ?= $(HI_ROOTFS_DIR)

CROSS_COMPILE := $(CFG_HI_ARM_TOOLCHAINS_NAME)

HI_FPGA := $(if $(findstring fpga,$(CFG_HI_BOOT_REG_NAME)),-fpga,)

CONFIG_LIBCPP_SUPPORT := $(if $(CFG_HI_LIBCPP_SUPPORT),$(CFG_HI_LIBCPP_SUPPORT),n)

CONFIG_ETH_SUPPORT := $(if $(CONFIG_ETH_SUPPORT),$(CONFIG_ETH_SUPPORT),y)

################################################################################
.PHONY: all clean

all:
	$(AT)test -d $(PREFIX) || mkdir -p $(PREFIX)
	$(AT)tar -xjf ./rootfs.tar.bz2 -C $(PREFIX)/../
	$(AT)tar -xjf ./libs/$(CFG_HI_ARM_TOOLCHAINS_NAME)$(HI_FPGA).tar.bz2 -C $(PREFIX)
ifeq ($(HI_USER_SPACE_LIB64),y)
	$(AT)tar -xjf ./libs/$(CFG_HI_AARCH64_TOOLCHAINS_NAME)$(HI_FPGA).tar.bz2 -C $(PREFIX)
endif
	$(AT)(echo '#!/bin/sh'; \
		echo -e '# This file auto create by makefile\n'; \
		echo -e "echo \"Compile file system used $(CROSS_COMPILE)\""; \
		echo -e ${CONFIG_ROOTFS_CMD} 1>/dev/null 2>&1; \
	) > $(PREFIX)/etc/init.d/S99init
	$(AT)chmod +rx $(PREFIX)/etc/init.d/S99init
	$(AT)cd ${PREFIX} && ln -fs sbin/init init
ifeq ($(CFG_HI_USER_MODE),y)
	$(AT)sed -i '/telnetd/d' $(PREFIX)/etc/init.d/S90modules
endif
ifneq ($(CONFIG_LIBCPP_SUPPORT),y)
	rm -rf $(PREFIX)/lib/*c++.so*
	rm -rf $(PREFIX)/lib64/*c++.so*
endif
ifneq ($(CONFIG_ADVCA_TYPE),VERIMATRIX)
ifneq ($(CONFIG_ETH_SUPPORT),y)
	$(AT)rm -rf $(PREFIX)/etc/protocols
	$(AT)rm -rf $(PREFIX)/etc/services
	$(AT)rm -rf $(PREFIX)/etc/init.d/S80network
	$(AT)rm -rf $(PREFIX)/usr/share/udhcpc
endif
endif

clean:
	$(AT)rm -rf $(PREFIX)
