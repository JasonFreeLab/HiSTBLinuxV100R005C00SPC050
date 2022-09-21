#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include "hi_unf_otp.h"
#include "hi_type.h"

static HI_S32 s_printBuffer(HI_CHAR *pString, HI_U8 *pu8Buf, HI_U32 u32Len)
{
    HI_U32 i;

    if ( (NULL == pu8Buf) || (NULL == pString) )
    {
        printf("null pointer input in function print_buf!\n");
        return HI_FAILURE;
    }

    printf("%s:\n", pString);
    for ( i = 0 ; i < u32Len ; i++ )
    {
        if ( ( i != 0) && ( (i% 16) == 0) )
        {
            printf("\n");
        }
        printf("%x ", pu8Buf[i]);
    }
    printf("\n");

    return HI_SUCCESS;
}

HI_S32 main(int argc, char *argv[])
{
    HI_S32 ret = HI_SUCCESS;
    HI_U8 au8StbTaRootKey[16] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};

    ret = HI_UNF_OTP_Init();
    if(HI_SUCCESS != ret)
    {
        printf("OTP init failed!\n");
        return HI_FAILURE;
    }

    ret = HI_UNF_OTP_SetRootKey(HI_UNF_OTP_STBTA_ROOTKEY, au8StbTaRootKey, 16);
    if(HI_SUCCESS != ret)
    {
        (HI_VOID)HI_UNF_OTP_DeInit();
        return HI_FAILURE;
    }

    s_printBuffer("set stb root key", au8StbTaRootKey, sizeof(au8StbTaRootKey));

    (HI_VOID)HI_UNF_OTP_DeInit();

    return HI_SUCCESS;
}




