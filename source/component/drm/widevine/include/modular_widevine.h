#ifndef __MODULAR_WIDEVINE_H__
#define __MODULAR_WIDEVINE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"  {
#endif
#endif

#define WIDEVINE_ENV_CFGFILE_PATH  "/data/drm/widevine/widevineconfig.txt"
#define MIN_TEXT_ASCII  (0x20)
#define MAX_TEXT_ASCII  (0x7f)

typedef enum
{
    TRANSPORTKEY_MODE_CLEAR = 0,
    TRANSPORTKEY_MODE_ENCRYPTED,
    TRANSPORTKEY_MODE_NONE
}EN_TRANSPORTKEY_MODE;

typedef enum
{
    KEYBOX_ENCRYPT_ALGORITHM_AES_CBC = 0,
    KEYBOX_ENCRYPT_ALGORITHM_AES_CTR,
    KEYBOX_ENCRYPT_ALGORITHM_AES_BUTT
}EN_KEYBOX_ENCRYPT_ALGORITHM;

typedef enum
{
    TRANSPORTKEY_DECRYPT_ALGORITHM_NONE = 0,
    TRANSPORTKEY_DECRYPT_ALGORITHM_CLEAR,
    TRANSPORTKEY_DECRYPT_ALGORITHM_TDES_ECB,
    TRANSPORTKEY_DECRYPT_ALGORITHM_AES_ECB,
    TRANSPORTKEY_DECRYPT_ALGORITHM_BUTT
}EN_TRANSPORTKEY_DECRYPT_ALGORITHM;

typedef enum
{
    TRANSPORTKEY_KEYLADDER_TYPE_STB_TA = 0,
    TRANSPORTKEY_KEYLADDER_TYPE_BUTT
}EN_TRANSPORTKEY_KEYLADDER_TYPE;


typedef enum
{
    DEVICEROOTKEY_KEYLADDER_TYPE_0 = 0,
    DEVICEROOTKEY_KEYLADDER_TYPE_BUTT
}EN_DEVICEROOTKEY_KEYLADDER_TYPE;


typedef enum
{
    FINNAL_DATA_STORE_MODE_SECURE_STORE = 0,
    FINNAL_DATA_STORE_MODE_TO_REE,
    FINNAL_DATA_STORE_MODE_BUTT
}EN_FINNAL_DATA_STORE_MODE;

typedef struct hiHI_ENC_BUF_S
{
    HI_U8* buffer;
    HI_U32 bufferLen;
    HI_U32 encAlg;
}HI_ENC_BUF_S;

typedef struct hiHI_WIDEVINE_CONFIG_S
{
    EN_DEVICEROOTKEY_KEYLADDER_TYPE enDevieceRootKeyKladType;
    EN_FINNAL_DATA_STORE_MODE  enFinnalDataStoreMode;
}HI_WIDEVINE_CONFIG_S;


int Hi_WVMemory_CA2TA(const unsigned int inputaddr,unsigned int TEEAddr,int  len);

int OEMCrypto_WrapKeyboxWithEncryptedTransportkey(
                            const HI_U8 *keybox,
                            HI_U32 keyBoxLength,
                            HI_U8 *wrappedKeybox,
                            HI_U32 *wrappedKeyBoxLength,
                            const HI_U8 *encTransportKey,
                            HI_U32 encTransportKeyLength);
int OEMCrypto_WrapKeyboxWithoutTransportkey(
                            const HI_U8 *keybox,
                            HI_U32 keyBoxLength,
                            HI_U8 *wrappedKeybox,
                            HI_U32 *wrappedKeyBoxLength);

int OEMCrypto_WrapKeybox_Ex(HI_ENC_BUF_S* keybox,
                            HI_ENC_BUF_S* transportkey,
                            HI_U32 transportkeyKeyladderType,
                            HI_U32 deviceRootKeyKeyladderType,
                            HI_U32 finnalDataStoreMode);

int Hi_Widevine_GetConfig(HI_WIDEVINE_CONFIG_S* pstConfig);
int Hi_Widevine_SetEncKeybox(char* encKeybox, unsigned int keyboxLength);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
