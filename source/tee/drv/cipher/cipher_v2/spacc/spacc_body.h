/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : spacc_body.c
  Version       : Initial Draft
  Author        :
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
******************************************************************************/
#ifndef _SPACC_BODY_H_
#define _SPACC_BODY_H_

#define SPACC_LOGIC_MAX_CHN                     8
#define CIPHER_PKGx1_CHAN                      (0)
#define SPACC_MAX_DEPTH                        127
#define SPACC_MAX_HMAC_KEY_LEN                 512
#define SPACC_PAGE_SIZE                        4096


#define CIPHER_PKGxN_CHAN_MIN                  (4)
#define CIPHER_PKGxN_CHAN_MAX                  (7)
#define SPACC_CHN_MASK                         (0xF0)

typedef enum
{
    SYMC_ALG_DES = 0,
    SYMC_ALG_3DES,
    SYMC_ALG_AES,
    SYMC_ALG_SM4,
    SYMC_ALG_SM1,
    SYMC_ALG_NULL_CIPHER,
    SYMC_ALG_COUNT,
}SYMC_ALG_EN;

typedef enum
{
    SYMC_MODE_ECB = 0,
    SYMC_MODE_CBC,
    SYMC_MODE_CFB,
    SYMC_MODE_OFB,
    SYMC_MODE_CTR,
    SYMC_MODE_CCM,
    SYMC_MODE_GCM,
    SYMC_MODE_COUNT,
}SYMC_MODE_EN;

typedef enum
{
    SYMC_DAT_WIDTH_128 = 0,
    SYMC_DAT_WIDTH_64 = 0,
    SYMC_DAT_WIDTH_8,
    SYMC_DAT_WIDTH_1,
    SYMC_DAT_WIDTH_COUNT,
}SYMC_DAT_WIDTH_EN;

typedef enum
{
    DIGEST_MODE_HASH,
    DIGEST_MODE_HMAC,
    DIGEST_MODE_COUNT,
} DIGEST_MODE_EN;

typedef enum
{
    DIGEST_ALG_SHA1,
    DIGEST_ALG_SHA224,
    DIGEST_ALG_SHA256,
    DIGEST_ALG_SHA384,
    DIGEST_ALG_SHA512,
    DIGEST_ALG_SM3,
    DIGEST_ALG_COUNT,
}DIGEST_ALG_EN;

typedef enum
{
    SPACC_ALLIED_SYMC = 0x00,
    SPACC_ALLIED_DIGEST,
    SPACC_ALLIED_SYMC_WITH_DIGEST,
    SPACC_ALLIED_DIGEST_WITH_SYMC,
    SPACC_ALLIED_COUNT,
}SPACC_ALLIED_EN;

typedef enum
{
    SPACC_BUF_TYPE_SYMC_IN,
    SPACC_BUF_TYPE_SYMC_OUT,
    SPACC_BUF_TYPE_DIGEST_IN,
    SPACC_BUF_TYPE_COUNT,
}SPACC_BUF_TYPE_EN;

typedef enum
{
    SPACC_CTRL_NONE             = 0x00,
    SPACC_CTRL_SYMC_IN_GCM_A    = 0x00,
    SPACC_CTRL_SYMC_IN_GCM_P    = 0x08,
    SPACC_CTRL_SYMC_IN_GCM_LEN  = 0x10,
    SPACC_CTRL_SYMC_IN_CCM_N    = 0x00,
    SPACC_CTRL_SYMC_IN_CCM_A    = 0x08,
    SPACC_CTRL_SYMC_IN_CCM_P    = 0x10,
    SPACC_CTRL_SYMC_IN_CBC_OUTPUT_DISABLE = 0x04,
    SPACC_CTRL_SYMC_IN_FIRST    = 0x01,
    SPACC_CTRL_SYMC_IN_LAST     = 0x02,
    SPACC_CTRL_HASH_IN_PAD      = 0x04,
    SPACC_CTRL_HASH_IN_FIRST    = 0x01,
    SPACC_CTRL_HASH_IN_LAST     = 0x02,
    SPACC_CTRL_HASH_IN_AUTO_PADDING = 0x04,
    SPACC_CTRL_HASH_IN_HMAC_END = 0x08,
    SPACC_CTRL_SYMC_OUT_LAST    = 0x02,
    SPACC_CTRL_SYMC_CCM_LAST    = 0x20,
    SPACC_CTRL_SYMC_ODD_KEY     = 0x40,
    SPACC_CTRL_SYMC_EVEN_KEY    = 0x00,
    SPACC_CTRL_COUNT,
}SPACC_CTRL_EN;

typedef enum
{
    SPACC_DATA_SEAT_FIRST,
    SPACC_DATA_SEAT_MIDDLE,
    SPACC_DATA_SEAT_LAST,
    SPACC_DATA_SEAT_COUNT,
}SPACC_DATA_SEAT_EN;

struct spacc_status_t
{
    unsigned int     symc_done:1;
    unsigned int     symc_key_err:1;
    unsigned int     symc_len_err:1;
    unsigned int     symc_dfa_attack:1;
    unsigned int     hash_done:1;
    unsigned int     hash_len_err:1;
    unsigned int     aead_done:1;
};

#define SPACC_OK                  0x000
#define SPACC_DIGEST_DONE         0x001
#define SPACC_DIGEST_LEN_ERR      0x002
#define SPACC_SYMC_DONE           0x004
#define SPACC_AEAD_DONE           0x008
#define SPACC_SYMC_KEY_ERR        0x0100
#define SPACC_SYMC_LEN_ERR        0x0200
#define SPACC_SYMC_DFA_ATTACK     0x0400

#define SPACC_ERR_NULL_POINT      0x400
#define SPACC_ERR_INVALID_PARAM   0x401
#define SPACC_ERR_BUSY            0x402
#define SPACC_ERR_TIMEOUT         0x403

#define SPACC_CHN_SECURE_ENABLE   0x80000000

#define SPACC_CHECK_POINT(p) \
    if(!p) return SPACC_ERR_NULL_POINT
#define SPACC_CHECK_INT(val, max) \
    {if((val) >= (max)) return SPACC_ERR_INVALID_PARAM;}
#define SPACC_CHECK_ZERO(val) \
    {if(val == 0) return SPACC_ERR_INVALID_PARAM;}

int spacc_init(void *reg_base, unsigned int mmu_table_addr,
               unsigned int entry_phy_addr, void *entry_via_addr);

int spacc_deinit(void);

void SM4_Enable(HI_VOID);

void SM4_Disable(HI_VOID);

unsigned int spacc_get_node_list_size(void);

/**************************** SYMC API ********************************/
int spacc_symc_getiv(unsigned int chn_num,
                             unsigned int *iv,  unsigned int ivsize);

int spacc_symc_gettag(unsigned int chn_num, unsigned char *tag);

int spacc_symc_setkey(unsigned int chn_num, unsigned int *even_key,
                              unsigned int *odd_key, unsigned int klen);

int spacc_symc_setiv(unsigned int chn_num,
                             unsigned char *iv, unsigned int ivlen);

int spacc_symc_addbuf(unsigned int chn_num, unsigned int buf_phy,
                         unsigned int buf_size,
                         SPACC_BUF_TYPE_EN type,
                         unsigned int ctrl);

int spacc_symc_addctrl(unsigned int chn_num,
                               SPACC_BUF_TYPE_EN type,
                               unsigned int ctrl);

int spacc_symc_config(unsigned int chn_num, SYMC_ALG_EN symc_alg,
                          SYMC_MODE_EN symc_mode,
                          SYMC_DAT_WIDTH_EN symc_width,
                          unsigned char sm1_round_num,
                          unsigned char klen,
                          unsigned char hard_key);

int spacc_symc_start(unsigned int chn_num, unsigned int decrypt, unsigned int iv_set_flag);
void spacc_symc_restart(unsigned int chn_num, unsigned int iv_set_flag);

unsigned int spacc_symc_get_free_nodes(unsigned int chn_num);

unsigned int spacc_symc_is_free(unsigned int chn_num);

unsigned int spacc_symc_done_notify(void);

unsigned int spacc_symc_done_try(unsigned int chn_num);

unsigned int spacc_symc_get_err_code(unsigned int chn_num,
                                     unsigned int *src_addr,
                                     unsigned int *dst_addr);

int spacc_symc_last_node(unsigned int chn_num,
                         unsigned int *in_addr, unsigned int *in_size,
                         unsigned int *out_addr, unsigned int *out_size);

/**************************** DIGEST API ********************************/
int spacc_digest_config(unsigned int chn_num, DIGEST_ALG_EN digest_alg,
                                DIGEST_MODE_EN digest_mode,
                                unsigned char hard_key);

int spacc_digest_addbuf(unsigned int chn_num,
                         unsigned int buf_phy,
                         unsigned int buf_size,
                         unsigned int ctrl);

int spacc_digest_addctrl(unsigned int chn_num, unsigned int ctrl);

int spacc_digest_start(unsigned int chn_num, SPACC_CTRL_EN enCtrl,
                                unsigned int *state);

int spacc_digest_last_node(unsigned int chn_num, unsigned int *addr, unsigned int *size);

unsigned int spacc_digest_done_notify(void);
unsigned int spacc_digest_done_try(unsigned int chn_num);

int spacc_digest_get(unsigned int chn_num, unsigned int *digest);

unsigned int spacc_digest_get_err_code(unsigned int chn_num,
                                     unsigned int *src_addr);

#endif

