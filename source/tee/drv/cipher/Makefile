#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

#===============================================================================
# local variables
#===============================================================================
ifneq ($(OUT),)
LOCAL_OUT := $(OUT)/drv/cipher
else
LOCAL_OUT := $(shell pwd)
endif

LIBS    := libsec_$(notdir $(LOCAL_OUT)).a

ifeq ($(CFG_HI_CHIP_TYPE), hi3796mv200)
CFG_HI_CIPHER_OPTIMIZ ?= y
endif

ifeq ($(CFG_HI_CIPHER_OPTIMIZ), y)
include $(HI_TEE_DRV_DIR)/cipher/cipher_v3/build.mak
else
ifeq ($(CFG_HI_CHIP_TYPE), hi3796mv200)
CFLAGS += -I$(HI_TEE_DRV_DIR)/cipher/cipher_v2    \
        -I$(HI_TEE_DRV_DIR)/cipher/cipher_v2/sha3    \
        -I$(HI_TEE_DRV_DIR)/cipher/cipher_v2/rng     \
        -I$(HI_TEE_DRV_DIR)/cipher/cipher_v2/rsa     \
        -I$(HI_TEE_DRV_DIR)/cipher/cipher_v2/hdcp    \
        -I$(HI_TEE_DRV_DIR)/cipher/cipher_v2/spacc   \
        -I$(HI_TEE_DRV_DIR)/cipher/cipher_v2/sm2 \
        -I$(HI_TEE_DRV_DIR)/cipher/cipher_v2/platform \
        -I$(HI_TEE_DRV_DIR)/cipher/cipher_v2/sic_rsa_library/include \
        -I$(HI_TEE_DRV_DIR)/cipher/cipher_v2/sic_rsa_library/include_external\
        -I$(HI_TEE_DRV_DIR)/cipher/opensource/rsa \
        -I$(HI_TEE_DRV_DIR)/cipher/opensource/mbedtls/include

OBJS += cipher_v2/platform/cipher_adapt.o
OBJS += cipher_v2/platform/cipher_init.o
OBJS += cipher_v2/drv_cipher_intf.o
OBJS += cipher_v2/rng/drv_rng.o
OBJS += cipher_v2/rsa/drv_rsa.o
OBJS += cipher_v2/sm2/drv_sm2.o
OBJS += cipher_v2/sm2/hal_sm2.o
OBJS += cipher_v2/spacc/spacc_body.o \
        cipher_v2/spacc/spacc_intf.o \
        cipher_v2/spacc/spacc_hash_intf.o
OBJS += cipher_v2/sic_rsa_library/external/external.o
else
OBJS    := \
        tee_drv_cipher.o \
        tee_drv_cipher_intf.o \
        tee_hal_cipher.o \
        opensource/sm2/drv_sm2.o \
        opensource/sm3/drv_sm3.o \
        opensource/sm4/drv_sm4.o \
        opensource/mbedtls/mbedtls_ecp.o \
        opensource/mbedtls/mbedtls_dhm.o \
        opensource/mbedtls/mbedtls_ecdh.o \
        opensource/mbedtls/mbedtls_ecp_curves.o \
        opensource/mbedtls/mbedtls_ecdsa.o \
        opensource/mbedtls/mbedtls_sha512.o

CFLAGS += -I$(HI_TEE_DRV_DIR)/cipher
CFLAGS += -I$(HI_TEE_DRV_DIR)/cipher/cenc
CFLAGS += -I$(HI_TEE_DRV_DIR)/cipher/opensource/rsa
CFLAGS += -I$(HI_TEE_DRV_DIR)/cipher/opensource/sm2
CFLAGS += -I$(HI_TEE_DRV_DIR)/cipher/opensource/sm3
CFLAGS += -I$(HI_TEE_DRV_DIR)/cipher/opensource/sm4
CFLAGS += -I$(HI_TEE_DRV_DIR)/cipher/opensource/mbedtls/include
CFLAGS += -I$(HI_TEE_DRV_DIR)/cipher/tee/include
CFLAGS += -I$(TRUSTEDCORE_DIR)/platform/devchip/$(PLATFORM_DIR_NAME)/pm
CFLAGS += -I$(TRUSTEDCORE_DIR)/platform/devchip/$(PLATFORM_DIR_NAME)/include
CFLAGS += -I$(HI_TEE_DRV_DIR)/mem/sec_mmz/include
endif

OBJS += cenc/tee_drv_cenc.o
OBJS += common/drv_cipher_men.o \
        common/drv_cipher_cts.o \
        common/drv_cipher_test.o

OBJS += tee/src/crys_aes.o \
        tee/src/crys_hmac.o \
        tee/src/crys_rsa.o \
        tee/src/crys_rsa_prim.o \
        tee/src/crys_hash.o \
        tee/src/crys_des.o \
        tee/src/crys_rsa_kg.o \
        tee/src/crys_rnd_rom.o \
        tee/src/crys_common_math.o \
        tee/src/crys_common_conv_endian.o \
        tee/src/crys_cipher_common.o \
        tee/src/crys_rsa_build.o \
        opensource/rsa/drv_rsa.o \
        opensource/mbedtls/mbedtls_rsa.o \
        opensource/mbedtls/mbedtls_bignum.o \
        tee/src/crys_stub.o
endif

CFLAGS += -Werror -Wall

CFLAGS +=   -I$(TRUSTEDCORE_DIR)/platform/devchip/$(PLATFORM_DIR_NAME)/include \
            -I$(HI_TEE_DRV_DIR)/cipher/cenc \
            -I$(HI_TEE_DRV_DIR)/cipher/common \
            -I$(TRUSTEDCORE_DIR)/platform/devchip/$(PLATFORM_DIR_NAME)/pm \
            -I$(HI_TEE_DRV_DIR)/cipher/tee/include \
            -I$(HI_TEE_DRV_DIR)/cipher/tee/include/ccdriver/shared/include \
            -I$(HI_TEE_DRV_DIR)/cipher/tee/include/ccdriver/shared/include/crys \
            -I$(HI_TEE_DRV_DIR)/cipher/tee/include/ccdriver/shared/include/pal \
            -I$(HI_TEE_DRV_DIR)/cipher/tee/include/ccdriver/shared/include/pal/secure_os \
            -I$(HI_TEE_DRV_DIR)/cipher/tee/include/ccdriver/shared/include/dx_util \
            -I$(HI_TEE_DRV_DIR)/klad/include

ALL_OUT_OBJ = $(foreach VAR,$(OBJS),$(addprefix $(LOCAL_OUT)/,$(VAR)))
ALL_OUT_LIBS = $(foreach VAR,$(LIBS),$(addprefix $(LOCAL_OUT)/,$(VAR)))

#===============================================================================
# rules
#===============================================================================
include $(HI_TEE_DRV_DIR)/stb_drv.mak
