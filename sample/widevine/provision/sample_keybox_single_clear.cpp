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
#define PARA_STYLE_STR_LENGTH   (30)
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

    HI_CHAR pPath[PATH_STR_LENGTH] = {0};
    HI_CHAR pParaStyle[PARA_STYLE_STR_LENGTH] = {0};
    const HI_CHAR *error;
    HI_U32 transportkeyMode = TRANSPORTKEY_MODE_CLEAR;
    HI_CHAR* transportkeyFileName = NULL;
    KEYBOX_FILE_S keyboxfile,transportkeyfile;
    KEYBOX_FILE_S wrappedkeyboxfile = {0};

    HI_U32 keyboxEncryptAlgorithm;
    HI_U32 transportkeyAlgorithm;
    HI_U32 transportkeyKeyladderType;
    HI_U32 deviceRootKeyKeyladderType;
    HI_U32 finnalDataStoreMode;

    HI_ENC_BUF_S stKeybox = {0};
    HI_ENC_BUF_S stTransportkey = {0};

    if(argc < 7)
    {
        printf("usage: %s keybox_path keybox_enc_alg transportkey_enc_alg transportkey_klad_type device_root_key_klad_type finnal_data_store_mode\n", argv[0]);
        printf("keybox_path:               /data/drm/widevine/\n");
        printf("keybox_enc_alg:            aes-cbc\n");
        printf("transportkey_enc_alg:      clear/aes-ecb\n");
        printf("transportkey_klad_type:    stb_ta_root_key\n");
        printf("device_root_key_klad_type: device_root_key\n");
        printf("finnal_data_store_mode:    secure_storage/push_back_to_ree\n");
        printf("examples:\n");
        printf("%s /data/drm/widevine/ aes-cbc clear stb_ta_root_key device_root_key secure_storage\n", argv[0]);
        printf("%s /data/drm/widevine/ aes-cbc clear stb_ta_root_key device_root_key push_back_to_ree\n", argv[0]);
        printf("%s /data/drm/widevine/ aes-cbc aes-ecb stb_ta_root_key device_root_key secure_storage\n", argv[0]);
        printf("%s /data/drm/widevine/ aes-cbc aes-ecb stb_ta_root_key device_root_key push_back_to_ree\n", argv[0]);

        return HI_FAILURE;
    }

    strncpy(pParaStyle,(char *)argv[2], PARA_STYLE_STR_LENGTH);
    if (!strncmp(pParaStyle, "aes-cbc", strlen("aes-cbc")))
    {
        keyboxEncryptAlgorithm = KEYBOX_ENCRYPT_ALGORITHM_AES_CBC;
    }
    //else if (!strncmp(pParaStyle, "aes-ctr", strlen("aes-ctr"))
    //{
        //keyboxEncryptAlgorithm = KEYBOX_ENCRYPT_ALGORITHM_AES_CTR;
    //}
    else
    {
        printf("not support keybox_encrypt_algorithm:%s\n", argv[2]);
        return HI_FAILURE;
    }

    strncpy(pParaStyle,(char *)argv[3], PARA_STYLE_STR_LENGTH);
    if (!strncmp(pParaStyle, "clear", strlen("clear")))
    {
        transportkeyAlgorithm = TRANSPORTKEY_DECRYPT_ALGORITHM_CLEAR;
    }
    //else if (!strncmp(pParaStyle, "teds-ecb", strlen("teds-ecb")))
    //{
        //transportkeyAlgorithm = TRANSPORTKEY_DECRYPT_ALGORITHM_TDES_ECB;
    //}
    else if (!strncmp(pParaStyle, "aes-ecb", strlen("aes-ecb")))
    {
        transportkeyAlgorithm = TRANSPORTKEY_DECRYPT_ALGORITHM_AES_ECB;
    }
    else if (!strncmp(pParaStyle, "none", strlen("none")))
    {
        transportkeyAlgorithm = TRANSPORTKEY_DECRYPT_ALGORITHM_NONE;
    }
    else
    {
        printf("not support transportkey_algorithm:%s\n", argv[3]);
        return HI_FAILURE;
    }

    strncpy(pParaStyle,(char *)argv[4], PARA_STYLE_STR_LENGTH);
    if (!strncmp(pParaStyle, "stb_ta_root_key", strlen("stb_ta_root_key")))
    {
        transportkeyKeyladderType = TRANSPORTKEY_KEYLADDER_TYPE_STB_TA;
    }
    else
    {
        printf("not support transportkey_keyladder_type:%s\n", argv[4]);
        return HI_FAILURE;
    }

    strncpy(pParaStyle,(char *)argv[5], PARA_STYLE_STR_LENGTH);
    if (!strncmp(pParaStyle, "device_root_key", strlen("device_root_key")))
    {
        deviceRootKeyKeyladderType = DEVICEROOTKEY_KEYLADDER_TYPE_0;
    }
    else
    {
        printf("not support device_root_key_keyladder_type:%s\n", argv[5]);
        return HI_FAILURE;
    }

    strncpy(pParaStyle,(char *)argv[6], PARA_STYLE_STR_LENGTH);
    if (!strncmp(pParaStyle, "secure_storage", strlen("secure_storage")))
    {
        finnalDataStoreMode = FINNAL_DATA_STORE_MODE_SECURE_STORE;
    }
    else if (!strncmp(pParaStyle, "push_back_to_ree", strlen("push_back_to_ree")))
    {
        finnalDataStoreMode = FINNAL_DATA_STORE_MODE_TO_REE;
    }
    else
    {
        printf("not support keybox_encrypt_algorithm:%s\n", argv[6]);
        return HI_FAILURE;
    }

    if (TRANSPORTKEY_DECRYPT_ALGORITHM_CLEAR == transportkeyAlgorithm)
    {
        transportkeyFileName = TRANSPORT_KEY;
    }
    else if (TRANSPORTKEY_DECRYPT_ALGORITHM_TDES_ECB == transportkeyAlgorithm
        || TRANSPORTKEY_DECRYPT_ALGORITHM_AES_ECB == transportkeyAlgorithm)
    {
        transportkeyFileName = ENC_TRANSPORT_KEY;
    }
    else
    {
        transportkeyFileName = NULL;
        printf("now don't support NULL transportkey!\n");
        return HI_FAILURE;
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
	    printf("read %s fail!\n", keyboxfile.szstring);
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
	    printf("read %s fail!\n", transportkeyfile.szstring);
	    free(keyboxfile.pu8Addr);
	    return HI_FAILURE;
	}

    stKeybox.buffer    = keyboxfile.pu8Addr;
    stKeybox.bufferLen = keyboxfile.s32length;
    stKeybox.encAlg    = keyboxEncryptAlgorithm;

    stTransportkey.buffer    = transportkeyfile.pu8Addr;
    stTransportkey.bufferLen = transportkeyfile.s32length;
    stTransportkey.encAlg    = transportkeyAlgorithm;

    printf("transportkeyAlgorithm:%d\n", stTransportkey.encAlg);
    OEMCrypto_WrapKeybox_Ex(&stKeybox,
                            &stTransportkey,
                            transportkeyKeyladderType,
                            deviceRootKeyKeyladderType,
                            finnalDataStoreMode);

    if (FINNAL_DATA_STORE_MODE_TO_REE == finnalDataStoreMode)
    {
        Widevine_StoreDevCert(&keyboxfile);
    }

    if (ret != HI_SUCCESS)
    {
        printf("Failed to provision keybox!\n");
        return -1;
    }
    printf("Provison Keybox successfully!\n");

    return 0;
}

