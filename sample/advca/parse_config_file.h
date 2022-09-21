#include "hi_unf_advca.h"
#include "hi_unf_cipher.h"

#define    MAX_FILE_NAME_LEN    (128)
#define    MAX_VAR_NUM          (64)
#define    MAX_VAR_NAME_LEN     (128)
#define    MAX_VAR_VALUE_LEN    (MAX_FILE_NAME_LEN)

typedef enum
{
    KEYLADDER_TYPE_CSA2  = 0,
    KEYLADDER_TYPE_CSA3,
    KEYLADDER_TYPE_R2R,
    KEYLADDER_TYPE_MISC,
    KEYLADDER_TYPE_SP,
    KEYLADDER_TYPE_DCAS,    
}KEYLADDER_TYPE_E;

int parse_config_file(char *path_to_config_file);

int get_key_value(HI_CHAR *pName, HI_U8 *pKey, HI_U32 u32keyLen);

HI_CHAR* get_config_var(HI_CHAR* var_name);


HI_S32 get_keyladder_type(KEYLADDER_TYPE_E *penKladType);

HI_S32 get_keyladder_alg(HI_UNF_ADVCA_ALG_TYPE_E *penAlgType);

HI_S32 get_cipher_alg(HI_UNF_CIPHER_ALG_E *penCipherAlg);

HI_S32 get_cipher_mode(HI_UNF_CIPHER_WORK_MODE_E *penMode);

HI_VOID print_all_vars();
