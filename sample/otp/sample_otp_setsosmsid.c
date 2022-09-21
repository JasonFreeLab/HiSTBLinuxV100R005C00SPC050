#include <stdio.h>
#include <stdlib.h>
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
    HI_U8 au8MSID[4] = {0,0,0,0};
    HI_U32 id = 0;

    ret = HI_UNF_OTP_Init();
    if(HI_SUCCESS != ret)
    {
        printf("OTP init failed!\n");
        return HI_FAILURE;
    }

    if(argc !=2)
    {
        printf("useage:input 4 Byte STB SOS MARKET ID \n");
        (HI_VOID)HI_UNF_OTP_DeInit();
        return HI_FAILURE;
    }

    id = strtol(argv[1], NULL, 16);
    au8MSID[0] = (id >> 24) & 0xFF;
    au8MSID[1] = (id >> 16) & 0xFF;
    au8MSID[2] = (id >> 8)  & 0xFF;
    au8MSID[3] = id         & 0xFF;
    ret = HI_UNF_OTP_SetSOSMSID(au8MSID, 4);
    if(HI_SUCCESS != ret)
    {
        printf("HI_UNF_OTP_SetSOSMSID failed!\n");
        (HI_VOID)HI_UNF_OTP_DeInit();
        return HI_FAILURE;
    }

    s_printBuffer("set otp sos market ID", au8MSID, sizeof(au8MSID));
    (HI_VOID)HI_UNF_OTP_DeInit();
    return HI_SUCCESS;
}


