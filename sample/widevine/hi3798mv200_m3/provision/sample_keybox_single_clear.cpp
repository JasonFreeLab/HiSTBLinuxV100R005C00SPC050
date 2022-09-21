#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hi_type.h"
#include "OEMCryptoCENC.h"
#include "hi_unf_pdm.h"
#include "Tool.h"
#include "modular_widevine.h"

#define KEYBOX_LENGTH           (128)
#define TRANSPORT_KEY_LENGTH    (16)
#define KEYBOX_AREA_SIZE        (144)
#define PATH_STR_LENGTH         (256)
#define DEVICEINFO              "deviceinfo"
#define TRANSPORT_KEY           "key.bin"
#define ENC_TRANSPORT_KEY       "key_enc.bin"
#define KEYBOX_NAME             "keybox_enc.bin"

HI_U8 gEncryptedKey[KEYBOX_LENGTH] = {0};
HI_U8 gWrappedKey[KEYBOX_LENGTH] = {0};
HI_U8 gTransportKey[TRANSPORT_KEY_LENGTH] = {0};


typedef struct
{
    HI_CHAR szstring[PATH_STR_LENGTH];
    HI_U8  *pu8Addr;
    HI_S32  s32length;
}KEYBOX_FILE_S;



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

static HI_S32 Widevine_ReadDevCert(KEYBOX_FILE_S *pDevcert)
{
    HI_S32 s32Ret = HI_SUCCESS;
    FILE *fp_DevCert = NULL;
    HI_U32 u32Len;
    HI_U8 *pu8Tmp = NULL;

    if ( NULL == pDevcert )
    {
        printf("Invalid param, null pointer!\n");
        return HI_FAILURE;
    }

    printf("read %s\n", pDevcert->szstring);
    fp_DevCert = fopen(pDevcert->szstring,"rb");
    if(NULL == fp_DevCert)
    {
        printf("open file '%s' error!\n", (char *)pDevcert->szstring);
        return HI_FAILURE;
    }

    fseek(fp_DevCert,0,SEEK_END);
    pDevcert->s32length = (HI_S32)ftell(fp_DevCert);
    rewind(fp_DevCert);
    //printf("file length:%d!\n", pDevcert->s32length);

    if(pDevcert->s32length <= 0)
    {
        printf("ftell file '%s' error!\n", (char *)pDevcert->szstring);
        s32Ret = HI_FAILURE;
        goto __Quit;
    }
    pu8Tmp = (HI_U8 *)malloc((unsigned long)pDevcert->s32length);
    if(NULL == pu8Tmp)
    {
        printf("malloc size 0x%x error!\n", pDevcert->s32length);
        s32Ret = HI_FAILURE;
        goto __Quit;
    }
    u32Len = fread(pu8Tmp, 1, (unsigned long)pDevcert->s32length, fp_DevCert);
    if(u32Len != (HI_U32)pDevcert->s32length)
    {
        printf("Read '%s' failed. real size(0x%x), should be size(0x%08x).\n", (char *)pDevcert->szstring, u32Len, pDevcert->s32length);
        s32Ret = HI_FAILURE;
        goto __Quit;
    }

    pDevcert->pu8Addr = pu8Tmp;
    //printf("%s length:%d\n", pDevcert->szstring, pDevcert->s32length);

__Quit:
    if ( NULL != fp_DevCert)
    {
        fclose(fp_DevCert);
        fp_DevCert = NULL;
    }

    if ( HI_FAILURE == s32Ret)
    {
        if ( NULL != pu8Tmp)
        {
            free(pu8Tmp);
            pu8Tmp = NULL;
        }
    }

    return s32Ret;
}

// This function realize simple store, just for sample.
static HI_S32 Widevine_StoreDevCert(KEYBOX_FILE_S *pDevcert)
{
    FILE *fp_DevCert = NULL;

    if ( NULL == pDevcert )
    {
        printf("Invalid param, null pointer!\n");
        return HI_FAILURE;
    }

    strncat(pDevcert->szstring, "_stb_root_key_enc", strlen("_stb_root_key_enc"));

    printf("store:%s!\n", pDevcert->szstring);
    fp_DevCert = fopen(pDevcert->szstring, "w+");
    if(NULL == fp_DevCert)
    {
        printf("open file '%s' error!\n", pDevcert->szstring);
        return HI_FAILURE;
    }

    fwrite(pDevcert->pu8Addr, (unsigned long)pDevcert->s32length, 1, fp_DevCert);
    fclose (fp_DevCert);

    return HI_SUCCESS;
}

int main(int argc, char **argv)
{
    HI_S32 ret = -1;
    HI_U32 wrappedKeyLen = KEYBOX_LENGTH;
    wv_provision wvp;
    HI_CHAR pBuf[KEYBOX_AREA_SIZE] = {0};
    HI_CHAR DRMAddr[64] = {0};
    HI_U32 offset = 0;

    HI_CHAR pPath[PATH_STR_LENGTH];
    const HI_CHAR *error;
    HI_U32 transportkeyMode = TRANSPORTKEY_MODE_CLEAR;
    HI_CHAR* transportkeyFileName = NULL;
    KEYBOX_FILE_S keyboxfile,transportkeyfile;
    KEYBOX_FILE_S wrappedkeyboxfile = {0};

    if(argc < 2)
    {
        printf("usage: %s widevine_keybox_path\n", argv[0]);
        printf("under widevine_keybox_path should have:\n");
        printf("keybox transportkey\n");

        return HI_FAILURE;
    }

    printf("Please enter transportkey mode:\n");
    printf("0: clear transportkey\n");
    printf("1: encrypted transportkey\n");

    scanf("%1d", &transportkeyMode);
    if (TRANSPORTKEY_MODE_CLEAR == transportkeyMode)
    {
        transportkeyFileName = TRANSPORT_KEY;
    }
    else if (TRANSPORTKEY_MODE_ENCRYPTED == transportkeyMode)
    {
        transportkeyFileName = ENC_TRANSPORT_KEY;
    }
    else
    {
        transportkeyFileName = NULL;
    }

    strncpy(pPath,(char *)argv[1], PATH_STR_LENGTH);
    ret = snprintf(keyboxfile.szstring, PATH_STR_LENGTH,"%s/%s", pPath, KEYBOX_NAME);
	if(ret < 0)
	{
	    return HI_FAILURE;
	}

    ret = snprintf(transportkeyfile.szstring, PATH_STR_LENGTH, "%s/%s", pPath, transportkeyFileName);
	if(ret < 0)
	{
	    return HI_FAILURE;
	}

    //1. get transport key and encrypted keybox
    ret = Widevine_ReadDevCert(&keyboxfile);
	if(ret < 0)
	{
	    return HI_FAILURE;
	}
    //  length check
    if (KEYBOX_AREA_SIZE != keyboxfile.s32length)
    {
        printf("length:%d ,must be 144!\n", keyboxfile.s32length);
        return HI_FAILURE;
    }
    ret = Widevine_ReadDevCert(&transportkeyfile);
	if(ret < 0)
	{
	    free(keyboxfile.pu8Addr);
	    return HI_FAILURE;
	}

    //2. call OEMCrypto_WrapKeybox to provision
    if (TRANSPORTKEY_MODE_CLEAR == transportkeyMode)
    {
        ret = OEMCrypto_WrapKeybox(keyboxfile.pu8Addr, keyboxfile.s32length,
            gWrappedKey, &wrappedKeyLen, transportkeyfile.pu8Addr, transportkeyfile.s32length);
    }
    else if (TRANSPORTKEY_MODE_ENCRYPTED == transportkeyMode)
    {
        printf("keyboxfile.s32length :%d\n", keyboxfile.s32length);
        printf("transportkeyfile.s32length :%d\n", transportkeyfile.s32length);
        ret = OEMCrypto_WrapKeyboxWithEncryptedTransportkey(keyboxfile.pu8Addr, (HI_U32)keyboxfile.s32length,
            gWrappedKey, &wrappedKeyLen, transportkeyfile.pu8Addr, (HI_U32)transportkeyfile.s32length);

        // TODO: store encrypted keybox by customer. In this sample, we only store in file.
        memcpy(wrappedkeyboxfile.szstring, keyboxfile.szstring, PATH_STR_LENGTH);
        wrappedkeyboxfile.pu8Addr = gWrappedKey;
        wrappedkeyboxfile.s32length = wrappedKeyLen;
        Widevine_StoreDevCert(&wrappedkeyboxfile);
    }
    else if (TRANSPORTKEY_MODE_NONE == transportkeyMode)
    {
        ret = OEMCrypto_WrapKeyboxWithoutTransportkey(keyboxfile.pu8Addr, keyboxfile.s32length,
            gWrappedKey, &wrappedKeyLen);
    }

    if (ret != HI_SUCCESS)
    {
        printf("Failed to provision keybox!\n");
        return -1;
    }
    printf("Provison Keybox successfully!\n");

    return 0;
}

