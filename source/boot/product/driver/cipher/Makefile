#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

#===============================================================================
# local variables
#===============================================================================

ifeq ($(CFG_HI_MINIBOOT_SUPPORT),y)
BOOT_DIR  := $(SDK_DIR)/source/boot/miniboot
else
BOOT_DIR  := $(SDK_DIR)/source/boot/fastboot
endif

ifneq ($(O),)
PRODUCT_DIR := $(O)/product
else
PRODUCT_DIR := $(BOOT_DIR)/../product
endif


ifndef CFLAGS
#include $(BOOT_DIR)/define.mak
export MKFLAGS

CC := $(CROSS_COMPILE)gcc

gccincdir := $(shell $(CC) -print-file-name=include)

CFLAGS := -g -Os -D__ARM__ -fno-strict-aliasing -fno-common -ffixed-r8 \
	  -nostdinc -isystem $(gccincdir) $(MKFLAGS) -I$(PRODUCT_DIR) \
	  -fno-builtin -ffreestanding  -pipe -marm  -mabi=aapcs-linux  \
	  -mno-thumb-interwork -march=armv7-a \
	  -Wall -Wstrict-prototypes -fno-stack-protector
endif

ifeq ($(CFG_HI_CHIP_TYPE), hi3796mv200)
CFLAGS  += -I$(PRODUCT_DIR)/driver/include
CFLAGS  += -I$(PRODUCT_DIR)/driver/include_inc
CFLAGS  += -I$(PRODUCT_DIR)/driver/advca
CFLAGS  += -I$(BOOT_DIR)/arch/arm/include
CFLAGS  += -I$(BOOT_DIR)/include
CFLAGS  += -I$(PRODUCT_DIR)/driver/cipher/v2/api
CFLAGS  += -I$(PRODUCT_DIR)/driver/cipher/v2/api/sic_rsa
CFLAGS  += -I$(PRODUCT_DIR)/driver/cipher/v2/api/sic_rsa/include
CFLAGS  += -I$(PRODUCT_DIR)/driver/cipher/v2/drv/platform
CFLAGS  += -I$(PRODUCT_DIR)/driver/cipher/v2/drv/rng
CFLAGS  += -I$(PRODUCT_DIR)/driver/cipher/v2/drv/sm2
CFLAGS  += -I$(PRODUCT_DIR)/driver/cipher/v2/drv/spacc
CFLAGS  += -I$(PRODUCT_DIR)/driver/cipher/v2/drv/include
CFLAGS  += -I$(PRODUCT_DIR)/driver/cipher

OBJS += v2/api/unf_cipher.o \
        v2/api/ree_mpi_cbcmac.o \
        v2/api/ree_mpi_cipher.o \
        v2/api/ree_mpi_hash.o \
        v2/api/ree_mpi_rng.o \
        v2/api/ree_mpi_rsa.o \
        v2/api/cipher_osal.o \
        v2/api/sic_rsa/external/external.o \
        drv_rsa.o \
        drv_rsa_bignum.o

OBJS += v2/drv/drv_cipher_intf.o
OBJS += v2/drv/rng/drv_rng.o
OBJS += v2/drv/rsa/drv_rsa.o
OBJS += v2/drv/spacc/spacc_body.o v2/drv/spacc/spacc_intf.o
OBJS += v2/drv/platform/cipher_adapt.o
OBJS += cmd_cipher.o

SIC_RSA_LIB := $(PRODUCT_DIR)/driver/cipher/v2/api/sic_rsa/lib/$(CFG_HI_ARM_TOOLCHAINS_NAME)/librsa.a
SIC_RSA_OBJS := $(shell $(CFG_HI_ARM_TOOLCHAINS_NAME)-ar -t $(SIC_RSA_LIB))

OBJS += $(SIC_RSA_OBJS)

else
CFLAGS  += -I$(PRODUCT_DIR)/driver/include
CFLAGS  += -I$(PRODUCT_DIR)/driver/include_inc
CFLAGS  += -I$(PRODUCT_DIR)/driver/advca
CFLAGS  += -I$(BOOT_DIR)/arch/arm/include
CFLAGS  += -I$(BOOT_DIR)/include
CIPHER_DIR = $(PRODUCT_DIR)/driver/cipher

OBJS += $(patsubst %.c,%.o,$(wildcard $(CIPHER_DIR)/*.c))
endif

LIBS    := libcipher.a

############################################################################


#===============================================================================
# rules
#===============================================================================

.PHONY: all clean install uninstall $(LIBS) lib_extract

all: lib_extract $(LIBS)

clean:
	$(AT)rm -rf $(OBJS)
	$(AT)rm -rf $(LIBS)
	$(AT)rm -rf $(SIC_RSA_OBJS)

install: all

uninstall:

lib_extract:
	$(shell $(CFG_HI_ARM_TOOLCHAINS_NAME)-ar -x $(SIC_RSA_LIB) )

$(LIBS): $(OBJS)
	$(AT)$(AR) -rc $@ $^
