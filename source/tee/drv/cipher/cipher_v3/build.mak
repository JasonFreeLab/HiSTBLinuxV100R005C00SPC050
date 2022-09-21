CIPHER_DIR := $(HI_TEE_DRV_DIR)/cipher
CIPHER_CFLAGS += -DHI_PLATFORM_TYPE_TEE

include $(CIPHER_DIR)/cipher_v3/drivers/build.mak
include $(CIPHER_DIR)/cipher_v3/osal/build.mak
include $(CIPHER_DIR)/cipher_v3/tee/build.mak
include $(CIPHER_DIR)/cipher_v3/test/build.mak
include $(CIPHER_DIR)/cipher_v3/compat/build.mak

CIPHER_CFLAGS += -I$(CIPHER_DIR)/cenc
OBJS   += cenc/tee_drv_cenc.o

CFLAGS += $(CIPHER_CFLAGS)
OBJS   += $(CIPHER_OBJS)