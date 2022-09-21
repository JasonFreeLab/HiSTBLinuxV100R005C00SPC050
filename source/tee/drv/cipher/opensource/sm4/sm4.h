#ifndef _RM_SM4_H_
#define _RM_SM4_H_

#include "tee_os_hal.h"
#include "hi_tee_cipher.h"

#define SM4_ENCRYPT 0
#define SM4_DECRYPT 1

unsigned int rm_sm4(const unsigned char *data_in, unsigned char *data_out, int data_len,
                    HI_TEE_CIPHER_WORK_MODE_E enWorkMode,
                    HI_TEE_CIPHER_CTRL_SM4_S *pstSm4,
                    int decrypt);

void rm4_get_iv(unsigned char *iv);

unsigned int sm4_ecb_rm(const unsigned char *data_in, unsigned char *data_out, int data_len, const unsigned char *key, int bit, unsigned int decrypt) ;

#ifdef __cplusplus
}
#endif

#endif /* _AES_H_ */
