
#include "hi_mpi_cipher.h"

HI_S32 HI_UNF_HDCP_EncryptHDCPKey(HI_UNF_HDCP_HDCPKEY_S stHdcpKey, HI_BOOL bIsUseOTPRootKey, HI_U8 u8OutEncryptKey[332])
{
    return HI_MPI_CIPHER_EncryptHDCPKey(&stHdcpKey, bIsUseOTPRootKey, u8OutEncryptKey);
}


