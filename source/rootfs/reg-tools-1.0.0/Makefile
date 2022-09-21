ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

PREFIX ?= $(HI_ROOTFS_DIR)

ifneq ($(HI_OUT_DIR),)
REGTOOLS_DIR := $(HI_OUT_DIR)/obj/source/rootfs/reg-tools-1.0.0
else
REGTOOLS_DIR := $(CURDIR)
endif

################################################################################
BUILD_DIR       := $(REGTOOLS_DIR)/tmp
HOST            := $(CFG_HI_ARM_TOOLCHAINS_NAME)
CROSS_COMPILE   := $(HOST)-
STRIP           := $(CROSS_COMPILE)strip
REGTOOLS        := reg-tools-1.0.0

ifeq ($(CROSS_COMPILE),arm-histbv320-linux-)
USER_CFLAGS     ?= -march=armv7-a -mcpu=cortex-a9 -mfloat-abi=hard -mfpu=vfpv3-d16
else
USER_CFLAGS     ?= -march=armv7-a -mcpu=cortex-a9 -mfloat-abi=softfp -mfpu=vfpv3-d16
endif
CFG_DEFS        := -DCHIP_TYPE_${CFG_HI_CHIP_TYPE}

LN              := $(shell if [ -x "/bin/ln" ]; then echo /bin/ln; else echo ln; fi)

export USER_CFLAGS

################################################################################
.PHONY: all clean
################################################################################
all: $(PREFIX)/bin/btools

clean:
	$(AT)test ! -d $(BUILD_DIR) || rm -rf $(BUILD_DIR)

$(PREFIX)/bin/btools: $(BUILD_DIR)/bin/btools
	$(AT)test -d $(@D) || mkdir -p $(@D)
	$(AT)install -v -t $(@D) $(BUILD_DIR)/$(REGTOOLS)/btools
	$(AT)rm -rf $(PREFIX)/bin/him* $(PREFIX)/bin/hiv* $(PREFIX)/bin/hie*
	$(AT)cd $(PREFIX)/bin && (${LN} -sf btools himd; \
		${LN} -fs btools himd.l; \
		${LN} -fs btools himm;   \
		${LN} -fs btools himc;   \
		${LN} -fs btools hivd;   \
		${LN} -fs btools hier;   \
		${LN} -fs btools hiew;   \
		${LN} -fs btools hismd;  \
		${LN} -fs btools hismm)

$(BUILD_DIR)/bin/btools: $(BUILD_DIR)/$(REGTOOLS)/tar
	$(AT)cd $(BUILD_DIR)/$(REGTOOLS) && \
		make install -j1 CROSS_COMPILE=$(CROSS_COMPILE) \
			PREFIX=$(PREFIX) \
			SRC_ROOT=$(SDK_DIR)/source \
			CFG_DEFS=$(CFG_DEFS)

$(BUILD_DIR)/%/tar:
	$(AT)test -d $(@D) || mkdir -p $(@D)
	$(AT)tar -xjf $(notdir $(@:/tar=)).tar.bz2 -C $(BUILD_DIR)
	$(AT)cp -f $(MSP_DIR)/api/i2c/unf_i2c.c $(BUILD_DIR)/$(REGTOOLS)/source/tools/hi_unf_i2c.c
	$(AT)cp -f $(COMMON_DIR)/api/log/mpi_log.c $(BUILD_DIR)/$(REGTOOLS)/source/tools/mpi_log.c
	$(AT)cp -f $(COMMON_DIR)/api/mem/mpi_memmap.c $(BUILD_DIR)/$(REGTOOLS)/source/tools/mpi_memmap.c
	$(AT)cp -f $(COMMON_DIR)/api/mem/mpi_mem.c $(BUILD_DIR)/$(REGTOOLS)/source/tools/mpi_mem.c
	$(AT)cp -f $(COMMON_DIR)/api/osal/hi_osal.c $(BUILD_DIR)/$(REGTOOLS)/source/tools/hi_osal.c
	$(AT)touch $@

