ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(shell cd $(CURDIR)/../../../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

ifeq ($(CFG_HI_MINIBOOT_SUPPORT),y)
CFLAGS += -DHI_LOADER_RUNNING_ENVIRONMENT_MINIBOOT
CFLAGS += -DHI_LOADER_RUNNING_ENVIRONMENT_BOOT
CFLAGS += -I$(BOOT_DIR)/miniboot/include
else ifeq ($(CFG_HI_UBOOT_SUPPORT),y)
CFLAGS += -DHI_LOADER_RUNNING_ENVIRONMENT_UBOOT
CFLAGS += -DHI_LOADER_RUNNING_ENVIRONMENT_BOOT
CFLAGS += -I$(BOOT_DIR)/fastboot/include
else 

endif

CFLAGS += -I$(BOOT_DIR)/product/driver/include

CFLAGS += -I$(CURDIR)/include
CFLAGS += -I$(CURDIR)/src
CFLAGS += -I$(CURDIR)/src/harden/include


SOURCE :=  src/loader_osal.c
SOURCE +=  src/loader_flash.c
SOURCE +=  src/loader_dbinfo.c

ifeq ($(CFG_HI_ADVCA_SUPPORT),y)
ifeq ($(CFG_HI_ADVCA_TYPE), CONAX)
CFLAGS += -I$(CURDIR)/src/harden/conax
SOURCE +=  src/harden/conax/cx_harden.c
SOURCE +=  src/harden/conax/cx_verify.c
else ifeq ($(CFG_HI_ADVCA_TYPE), VERIMATRIX)
CFLAGS += -I$(CURDIR)/src/harden/crc
CFLAGS += -I$(CURDIR)/src/harden/vmx_advance/3rd_loader_verify_lib
CFLAGS += -I$(CURDIR)/src/harden/vmx_advance/vmx_loader_verify_lib
SOURCE +=  src/harden/crc/crc_harden.c
else ifeq ($(CFG_HI_ADVCA_TYPE), VERIMATRIX_ULTRA)
CFLAGS += -I$(CURDIR)/src/harden/vmx_ultra
CFLAGS += -I$(CURDIR)/src/harden/crc
SOURCE +=  src/harden/vmx_ultra/vmx_verify.c
SOURCE +=  src/harden/crc/crc_harden.c
else ifeq ($(CFG_HI_ADVCA_TYPE), NAGRA)
CFLAGS += -I$(CURDIR)/src/harden/nagra
CFLAGS += -I$(CURDIR)/src/harden/include
SOURCE +=  src/harden/nagra/nagra_verify.c
SOURCE +=  src/harden/crc/crc_harden.c
else
CFLAGS += -I$(CURDIR)/src/harden/crc
SOURCE +=  src/harden/crc/crc_harden.c
endif
else
CFLAGS += -I$(CURDIR)/src/harden/crc
SOURCE +=  src/harden/crc/crc_harden.c
endif

LIBS := libapi.a
OBJS := $(patsubst %.c,%.o, $(SOURCE))

all: $(LIBS)

install: all

$(LIBS): $(OBJS)
	$(AT)$(AR) -rc $@ $^

%.o: %.c
	$(AT)$(CC) $(CFLAGS) -c $^ -o "$(*D)/$(*F).o"

clean:
	$(AT)rm -f $(OBJS) $(LIBS)

