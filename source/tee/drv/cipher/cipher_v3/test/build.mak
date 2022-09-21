CFLAGS += -I$(CIPHER_DIR)/cipher_v3/test

CIPHER_OBJS += cipher_v3/test/test_crys_aes.o  \
               cipher_v3/test/test_crys_des.o  \
               cipher_v3/test/test_crys_kg.o  \
               cipher_v3/test/test_crys_prim.o  \
               cipher_v3/test/test_crys_rsa.o  \
               cipher_v3/test/test_crys_hash.o  \
               cipher_v3/test/test_crys_hmac.o  \
               cipher_v3/test/test_cts.o  \
               cipher_v3/test/test_main.o