#
# arch/arm64/boot/Makefile
#
# This file is included by the global makefile so that you can add your own
# architecture-specific flags and dependencies.
#
# This file is subject to the terms and conditions of the GNU General Public
# License.  See the file "COPYING" in the main directory of this archive
# for more details.
#
# Copyright (C) 2012, ARM Ltd.
# Author: Will Deacon <will.deacon@arm.com>
#
# Based on the ia64 boot/Makefile.
#

include $(srctree)/arch/arm64/boot/dts/Makefile

targets := Image Image.gz uImage

DTB_NAMES := $(subst $\",,$(CONFIG_BUILD_ARM64_APPENDED_DTB_IMAGE_NAMES))
ifneq ($(DTB_NAMES),)
DTB_LIST := $(addsuffix .dtb,$(DTB_NAMES))
else
DTB_LIST := $(dtb-y)
endif
DTB_OBJS := $(addprefix $(obj)/dts/,$(DTB_LIST))

$(obj)/Image: vmlinux FORCE
	$(call if_changed,objcopy)

$(obj)/Image.bz2: $(obj)/Image FORCE
	$(call if_changed,bzip2)

$(obj)/Image-dtb: $(obj)/Image $(DTB_OBJS) FORCE
	$(call if_changed,cat)

$(obj)/Image.gz: $(obj)/Image FORCE
	$(call if_changed,gzip)

$(obj)/Image.lz4: $(obj)/Image FORCE
	$(call if_changed,lz4)

$(obj)/Image.lzma: $(obj)/Image FORCE
	$(call if_changed,lzma)

$(obj)/Image.lzo: $(obj)/Image FORCE
	$(call if_changed,lzo)

$(obj)/Image.gz-dtb: $(obj)/Image.gz $(DTB_OBJS) FORCE
	$(call if_changed,cat)

UIMAGE_LOADADDR=0x2000000
UIMAGE_ENTRYADDR=$(TEXT_OFFSET)
#UIMAGE_COMPRESSION = gzip
check_for_multiple_loadaddr = \
if [ $(words $(UIMAGE_LOADADDR)) -ne 1 ]; then \
	echo 'multiple (or no) load addresses: $(UIMAGE_LOADADDR)'; \
	echo 'This is incompatible with uImages'; \
	echo 'Specify LOADADDR on the commandline to build an uImage'; \
	false; \
fi

rm_uimage:
	@rm -f $(obj)/uImage

$(obj)/uImage:  $(obj)/Image rm_uimage FORCE
	@$(check_for_multiple_loadaddr)
	@dd if=$< of=$<.dd ibs=4096 conv=sync && mv $<.dd $<
	$(call if_changed,uimage)
	$(if $(CONFIG_BUILD_ARM64_APPENDED_DTB_IMAGE),@$(kecho) '  CAT   $(DTB_OBJS) to $@')
	$(if $(CONFIG_BUILD_ARM64_APPENDED_DTB_IMAGE),@cat $(DTB_OBJS) >>$@,)
	@$(kecho) '  Image $@ is ready'

ifeq ($(findstring y, $(CONFIG_ARCH_HI3796MV2X)$(CONFIG_ARCH_HI3798MV2X)$(CONFIG_ARCH_HI3798CV2X)),y)
	@echo "##Enable ARM64 uncompressed"
	$(AT)test -d $(LINUX_DIR)/arch/arm64/boot/compressed || mkdir -p $(LINUX_DIR)/arch/arm64/boot/compressed
	@mv $(LINUX_DIR)/arch/$(CFG_HI_CPU_ARCH)/boot/uImage $(LINUX_DIR)/arch/$(CFG_HI_CPU_ARCH)/boot/uImage.bak
	make -C $(KERNEL_SRC_DIR)/arch/arm64/boot/compressed ARCH=$(CFG_HI_CPU_ARCH) \
		CROSS_COMPILE=$(CROSS_COMPILE) UIMAGE_NAME=${UIMAGE_NAME}
endif

install: $(obj)/Image
	$(CONFIG_SHELL) $(srctree)/$(src)/install.sh $(KERNELRELEASE) \
	$(obj)/Image System.map "$(INSTALL_PATH)"

zinstall: $(obj)/Image.gz
	$(CONFIG_SHELL) $(srctree)/$(src)/install.sh $(KERNELRELEASE) \
	$(obj)/Image.gz System.map "$(INSTALL_PATH)"
