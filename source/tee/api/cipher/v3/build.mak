CIPHER_OBJ += v3/hi_tee_cipher.o v3/mpi_cipher.o v3/user_osal_lib.o
CIPHER_INS += -I$(HI_TEE_API_DIR)/cipher/v3
CIPHER_INS += -DHI_PLATFORM_TYPE_TEE
