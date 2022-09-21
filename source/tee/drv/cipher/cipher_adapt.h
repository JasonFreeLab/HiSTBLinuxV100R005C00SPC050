#include "tee_drv_cipher_define.h"
#include "tee_hal_cipher.h"
#include "tee_drv_cipher.h"
#include "tee_drv_cipher_define.h"
#include "drv_cipher_common.h"
#include "sec_mmz.h"

#define  TEE_ERR_CIPHER_NOT_INIT                     (HI_S32)(0x804D0001)
#define  TEE_ERR_CIPHER_INVALID_HANDLE               (HI_S32)(0x804D0002)
#define  TEE_ERR_CIPHER_INVALID_POINT                (HI_S32)(0x804D0003)
#define  TEE_ERR_CIPHER_INVALID_PARA                 (HI_S32)(0x804D0004)
#define  TEE_ERR_CIPHER_FAILED_INIT                  (HI_S32)(0x804D0005)
#define  TEE_ERR_CIPHER_FAILED_GETHANDLE             (HI_S32)(0x804D0006)
#define  TEE_ERR_CIPHER_FAILED_RELEASEHANDLE         (HI_S32)(0x804D0007)
#define  TEE_ERR_CIPHER_FAILED_CONFIGAES             (HI_S32)(0x804D0008)
#define  TEE_ERR_CIPHER_FAILED_CONFIGDES             (HI_S32)(0x804D0009)
#define  TEE_ERR_CIPHER_FAILED_ENCRYPT               (HI_S32)(0x804D000A)
#define  TEE_ERR_CIPHER_FAILED_DECRYPT               (HI_S32)(0x804D000B)
#define  TEE_ERR_CIPHER_BUSY                         (HI_S32)(0x804D000C)
#define  TEE_ERR_CIPHER_NO_AVAILABLE_RNG             (HI_S32)(0x804D000D)


#if defined(TESTSUITE_RTOSck_UT) || defined(TESTSUITE_RTOSck_PT) || defined(TESTSUITE_RTOSck_IT)
#define CIPHER_ACCESS_CHECK(addr, size)

#define CIPHER_ACCESS_READ_RIGHT_CHECK(addr, size)

#define CIPHER_ACCESS_WRITE_RIGHT_CHECK(addr, size)
#else
#define CIPHER_ACCESS_CHECK(addr, size)     if(false == tee_hal_access_check(addr, size)) {\
				    tee_hal_printf("ERROR!!!!, it seems the input buffer is not valid line is %d\n", __LINE__);\
				    return TEE_ERROR_ACCESS_DENIED;\
				    }

#define CIPHER_ACCESS_READ_RIGHT_CHECK(addr, size)  if(false == tee_hal_read_right_check(addr, size)) {\
				    tee_hal_printf("ERROR!!!!, it seems the input buffer READ denied line is %d\n", __LINE__);\
				    return TEE_ERROR_ACCESS_DENIED;\
				    }

#define CIPHER_ACCESS_WRITE_RIGHT_CHECK(addr, size)   if(false == tee_hal_write_right_check(addr, size)) {\
				    tee_hal_printf("ERROR!!!!, it seems the input buffer write denied line is %d\n", __LINE__);\
				    return TEE_ERROR_ACCESS_DENIED;\
				    }
#endif

HI_S32 Cipher_AesCbcCts_Decrypt(HI_HANDLE hCipherHandle,
                                cipher_mmz_buf_t *pstSrcMmz,
                                cipher_mmz_buf_t *pstDesMmz,
                                HI_U32 u32ByteLength);
HI_S32 Cipher_AesCbcCts_Encrypt(HI_HANDLE hCipherHandle,
                                cipher_mmz_buf_t *pstSrcMmz,
                                cipher_mmz_buf_t *pstDesMmz,
                                HI_U32 u32ByteLength);

HI_S32 s_Cipher_Encrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength, HI_BOOL bIsBlock);
HI_S32 s_Cipher_Decrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength, HI_BOOL bIsBlock);
