CIPHER_CFLAGS += -I$(CIPHER_DIR)/cipher_v3/osal/include
CIPHER_CFLAGS += -I$(CIPHER_DIR)/../mem/sec_mmz/include

CIPHER_OBJS   += cipher_v3/osal/drv_osal_init.o \
                 cipher_v3/osal/drv_osal_sys.o
