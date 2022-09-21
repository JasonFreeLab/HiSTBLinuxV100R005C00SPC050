#======================NOTE==========================
# The location of this directory is tee/drv/cipher/cipher_v3/drivers,
# ree access this directory by soft link, which created by command:
# cd source/msp/drv/cipher/cipher_v3
# ln -s ../../../../tee/drv/cipher/cipher_v3/drivers drivers
# you can show the source in ree by command:
# ls -al
# drivers -> ../../../../tee/drv/cipher/cipher_v3/drivers
# if you want to copy the soft link, must add option of -d
# cp -drf drivers other_dir
# otherwise will copy real directory to other_dir
#
# !!! change this directory will affects ree and tee codes.

CIPHER_CFLAGS += -I$(CIPHER_DIR)/cipher_v3/drivers/core/include
CIPHER_CFLAGS += -I$(CIPHER_DIR)/cipher_v3/drivers/crypto/include
CIPHER_CFLAGS += -I$(CIPHER_DIR)/cipher_v3/drivers/extend
CIPHER_CFLAGS += -I$(CIPHER_DIR)/cipher_v3/drivers/extend/include

CIPHER_OBJS +=  cipher_v3/drivers/core/drv_symc_v100.o          \
                cipher_v3/drivers/core/drv_symc_v200.o          \
                cipher_v3/drivers/core/drv_hash_v100.o          \
                cipher_v3/drivers/core/drv_hash_v200.o          \
                cipher_v3/drivers/core/drv_hdcp_v100.o          \
                cipher_v3/drivers/core/drv_hdcp_v200.o          \
                cipher_v3/drivers/core/drv_ifep_rsa_v100.o      \
                cipher_v3/drivers/core/drv_sm2_v100.o           \
                cipher_v3/drivers/core/drv_trng_v100.o          \
                cipher_v3/drivers/core/drv_trng_v200.o          \
                cipher_v3/drivers/core/drv_lib.o

CIPHER_OBJS += cipher_v3/drivers/crypto/cryp_symc.o             \
               cipher_v3/drivers/crypto/cryp_hash.o             \
               cipher_v3/drivers/crypto/cryp_hdcp.o             \
               cipher_v3/drivers/crypto/cryp_trng.o             \
               cipher_v3/drivers/crypto/cryp_rsa.o              \
               cipher_v3/drivers/crypto/cryp_sm2.o

CIPHER_OBJS += cipher_v3/drivers/kapi_symc.o                    \
               cipher_v3/drivers/kapi_hash.o                    \
               cipher_v3/drivers/kapi_rsa.o                     \
               cipher_v3/drivers/kapi_hdcp.o                    \
               cipher_v3/drivers/kapi_trng.o                    \
               cipher_v3/drivers/kapi_sm2.o                     \
               cipher_v3/drivers/kapi_dispatch.o

CIPHER_OBJS += cipher_v3/drivers/extend/mbedtls/bignum.o        \
               cipher_v3/drivers/extend/mbedtls/ecdh.o          \
               cipher_v3/drivers/extend/mbedtls/ecdsa.o         \
               cipher_v3/drivers/extend/mbedtls/ecp.o           \
               cipher_v3/drivers/extend/mbedtls/ecp_curves.o    \
               cipher_v3/drivers/extend/mbedtls/md.o            \
               cipher_v3/drivers/extend/mbedtls/rsa.o           \
               cipher_v3/drivers/extend/mbedtls/sha1.o          \
               cipher_v3/drivers/extend/mbedtls/sha256.o        \
               cipher_v3/drivers/extend/mbedtls/sha512.o        \
               cipher_v3/drivers/extend/mbedtls/aes.o           \
               cipher_v3/drivers/extend/mbedtls/aesni.o         \
               cipher_v3/drivers/extend/mbedtls/asn1parse.o     \
               cipher_v3/drivers/extend/mbedtls/ccm.o           \
               cipher_v3/drivers/extend/mbedtls/cipher.o        \
               cipher_v3/drivers/extend/mbedtls/cipher_wrap.o   \
               cipher_v3/drivers/extend/mbedtls/des.o           \
               cipher_v3/drivers/extend/mbedtls/dhm.o           \
               cipher_v3/drivers/extend/mbedtls/error.o         \
               cipher_v3/drivers/extend/mbedtls/gcm.o           \
               cipher_v3/drivers/extend/mbedtls/md_wrap.o       \
               cipher_v3/drivers/extend/mbedtls/oid.o           \
               cipher_v3/drivers/extend/mbedtls/asn1write.o     \

CIPHER_OBJS += cipher_v3/drivers/extend/ext_cmac.o              \
               cipher_v3/drivers/extend/ext_aead.o              \
               cipher_v3/drivers/extend/ext_hash.o              \
               cipher_v3/drivers/extend/ext_symc.o              \
               cipher_v3/drivers/extend/ext_ecc.o               \
               cipher_v3/drivers/extend/ext_sm2.o               \
               cipher_v3/drivers/extend/ext_sm3.o               \
               cipher_v3/drivers/extend/ext_sm4.o