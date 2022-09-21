#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../../../../ && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

#===============================================================================
# local variable
#===============================================================================
EXTRA_CFLAGS += $(CFG_HI_CFLAGS)
EXTRA_CFLAGS += $(CFG_CFLAGS)
#===============================================================================
# rules
#===============================================================================
.PHONY : all clean api apiclean install uninstall release
all : api

api:
	$(AT)make -C api COMPILELIB_TOOLCHAINS_NAME=$(CFG_HI_ARM_TOOLCHAINS_NAME)
	$(AT)make -C eapi COMPILELIB_TOOLCHAINS_NAME=$(CFG_HI_ARM_TOOLCHAINS_NAME)

apiclean:
	$(AT)make -C api clean
	$(AT)make -C eapi clean

install: all
	$(AT)make -C api install
	$(AT)make -C eapi install

uninstall: clean
	$(AT)make -C api uninstall
	$(AT)make -C eapi uninstall

clean: apiclean
