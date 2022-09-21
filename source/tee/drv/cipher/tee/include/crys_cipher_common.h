#ifndef __CRYS_CRYPTO_COMMON_H_
#define __CRYS_CRYPTO_COMMON_H_
#include "hi_type.h"
#include "dx_pal_types.h"
#include "crys_error.h"
#include "crys_rsa_types.h"

#define malloc(x) tee_hal_malloc((x))
#define free(x)   tee_hal_free((x))
#define RSA_MAX_RSA_KEY_LEN  512
#define HMAC256_OUTPUT_LEN_WORD     (8)
#define HMAC_BLOCK_SIZE             (16)

HI_U32 CRYS_GetBitNum(HI_U8 *pu8BigNum, HI_U32 u32NumLen);
HI_U32 CRYS_Bin2Bn(DxUint32_t *pu32bn, const HI_U8 *pbin, HI_S32 u32Len);
HI_U32 CRYS_Bn2Bin(const HI_U32 *pu32bn, HI_U8 *pbin, HI_S32 u32Len);
HI_S32 CRYS_GetRandomNumber(HI_U8 *pu8Rand, HI_U32 u32Size);
CEXPORT_C CRYSError_t CRYS_RSA_Private(HI_U8 *UserContext_ptr, CRYSRSAPrivKey_t *PrivKey_ptr,
                   HI_U8 *DataIn_ptr, HI_U8 *Output_ptr, HI_U32 DataSize);
CEXPORT_C CRYSError_t CRYS_RSA_Public(HI_U8 *UserContext_ptr, CRYSRSAPubKey_t *PubKey_ptr,
                   HI_U8 *DataIn_ptr, HI_U8 *Output_ptr, HI_U32 DataSize);

HI_VOID *CRYS_Malloc(HI_U32 size);
HI_VOID CRYS_Free(HI_VOID *memblock);

HI_S32 Hal_Cipher_Hmac256Block(HI_U32 u32DataIn[HMAC_BLOCK_SIZE], HI_U32 u32Output[HMAC256_OUTPUT_LEN_WORD]);
#endif

