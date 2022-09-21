#ifndef __RM_SM3_H
#define __RM_SM3_H

#define FUNC_SM3_RAND 5

#define SM3_DIGEST_LENGTH 32

#ifdef __cplusplus
extern "C" {
#endif

#define SM3_BASE_ADDR 0x10150000
#define SM3_BUSY_FLAG 0x1

void sm3_init(HASH_INFO_S *ctx);
void sm3_update(HASH_INFO_S *ctx, const unsigned char* data, unsigned int data_len);
void sm3_final(HASH_INFO_S *ctx, unsigned char digest[SM3_DIGEST_LENGTH]);
void sm3(const unsigned char *data, unsigned int datalen, unsigned char digest[SM3_DIGEST_LENGTH]);

#ifdef __cplusplus
}
#endif

#endif

