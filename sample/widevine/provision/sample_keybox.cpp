#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hi_type.h"
#include "OEMCryptoCENC.h"
#include "hi_unf_pdm.h"
#include "Tool.h"

#define KEYBOX_LENGTH    (144)
#define TRANSPORT_KEY_LENGTH    (16)
#define KEYBOX_AREA_SIZE    (160)
#define DEVICEINFO      "deviceinfo"
#define KEYBOX_OFFSET   (0x4000)


HI_U8 gEncryptedKey[KEYBOX_LENGTH] = {0};
HI_U8 gWrappedKey[KEYBOX_LENGTH] = {0};
HI_U8 gTransportKey[TRANSPORT_KEY_LENGTH] = {0};

using namespace android;

static void printfHex(HI_CHAR* buffer, HI_U32 len)
{
    HI_U32 i = 0;
    for (i = 0; i < len; i++)
    {
        if ((i + 1) % 16 == 0)
        {
            printf("%2X\n", buffer[i]);
        }
        else
        {
            printf("%2X ", buffer[i]);
        }
    }
    return;
}

int main(int argc, char **argv)
{
    HI_S32 ret = -1;
    FILE *fp = NULL;
    HI_U32 wrappedKeyLen = KEYBOX_LENGTH;
    wv_provision wvp;
    HI_CHAR pBuf[KEYBOX_AREA_SIZE] = {0};
    HI_CHAR DRMAddr[64] = {0};
    HI_U32 offset = 0;

    if (argc != 1)
    {
        printf("Usage: sample_keybox\n");
        return -1;
    }
    //1. set DRMAddr in deviceinfo
    offset = KEYBOX_OFFSET;
    printf("offset = 0x%x\n", offset);

    //2. get transport key and encrypted keybox
    if (-1 == wvp.HI_Flash_ReadDRMData(DEVICEINFO, offset, pBuf, KEYBOX_AREA_SIZE))
    {
        printf("Failed to read DRMData!\n");
        return -1;
    }

    memcpy(gTransportKey, pBuf, TRANSPORT_KEY_LENGTH);
    memcpy(gEncryptedKey, pBuf + TRANSPORT_KEY_LENGTH, KEYBOX_LENGTH);

    printf("gTransportKey:\n");
    printfHex(pBuf, TRANSPORT_KEY_LENGTH);

    //3. call OEMCrypto_WrapKeybox to provision
    ret = OEMCrypto_WrapKeybox(gEncryptedKey, KEYBOX_LENGTH,gWrappedKey, &wrappedKeyLen,
                               gTransportKey, TRANSPORT_KEY_LENGTH);

    if (ret != HI_SUCCESS)
    {
        printf("Failed to provision keybox!\n");
        return -1;
    }
    printf("Provison Keybox successfully!\n");

    //4. erase transport key and keybox on flash
    memset(pBuf, 0, KEYBOX_AREA_SIZE);
    if (-1 == wvp.HI_Flash_WriteDRMData(DEVICEINFO, offset, pBuf, KEYBOX_AREA_SIZE))
    {
        printf("Failed to erase keybox on flash!\n");
        return -1;
    }
    printf("Erase keybox on flash successfully!\n");
    return 0;
}

