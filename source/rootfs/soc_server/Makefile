################################################################################
#    ./dosfstools/Makefile
#    Create By jinghui
#    2011.09.05
################################################################################
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

PREFIX ?= $(HI_ROOTFS_DIR)

ifneq ($(HI_OUT_DIR),)
TOP_DIR := $(HI_OUT_DIR)/obj/source/rootfs/soc_server
else
TOP_DIR := $(CURDIR)
endif

################################################################################
BUILD_DIR       := $(TOP_DIR)/tmp
HOST            := $(CFG_HI_ARM_TOOLCHAINS_NAME)
CROSS_COMPILE   := $(HOST)-
STRIP           := $(CROSS_COMPILE)strip
REGTOOLS        := soc_server

USER_CFLAGS     ?= -march=armv7-a -mcpu=cortex-a9 -mfloat-abi=softfp -mfpu=vfpv3-d16
CFG_DEFS        := -DCHIP_TYPE_${CFG_HI_CHIP_TYPE}

LN              := $(shell if [ -x "/bin/ln" ]; then echo /bin/ln; else echo ln; fi)

export USER_CFLAGS

################################################################################
.PHONY: all clean
################################################################################
all: $(PREFIX)/bin/soc_server

clean:
	$(AT)rm -rf $(BUILD_DIR)/$(REGTOOLS)

$(PREFIX)/bin/soc_server: $(BUILD_DIR)/bin/soc_server
	test -d $(@D) || mkdir -p $(@D)
	install -v -t $(@D) $(BUILD_DIR)/$(REGTOOLS)/soc_server

$(BUILD_DIR)/bin/soc_server: $(BUILD_DIR)/$(REGTOOLS)/tar
	$(AT)cd $(BUILD_DIR)/$(REGTOOLS) && \
		make CROSS_COMPILE=$(CROSS_COMPILE) \
			PREFIX=$(PREFIX) \
			SRC_ROOT=$(SDK_DIR)/source \
			CFG_DEFS=$(CFG_DEFS)

$(BUILD_DIR)/$(REGTOOLS)/tar:
	$(AT)test -d $(@D) || mkdir -p $(@D)
	$(AT)tar -xjf $(notdir $(@:/tar=)).tar.bz2 -C $(BUILD_DIR)
	$(AT)cp -f $(MSP_DIR)/api/i2c/unf_i2c.c $(BUILD_DIR)/$(REGTOOLS)/hi_unf_i2c.c
	$(AT)cp -f $(COMMON_DIR)/api/log/mpi_log.c $(BUILD_DIR)/$(REGTOOLS)/mpi_log.c
	$(AT)cp -f $(COMMON_DIR)/api/mem/mpi_memmap.c $(BUILD_DIR)/$(REGTOOLS)/mpi_memmap.c
	$(AT)cp -f $(COMMON_DIR)/api/mem/mpi_mem.c $(BUILD_DIR)/$(REGTOOLS)/mpi_mem.c
	$(AT)cp -f $(COMMON_DIR)/api/osal/hi_osal.c $(BUILD_DIR)/$(REGTOOLS)/hi_osal.c
	$(AT)touch $@
