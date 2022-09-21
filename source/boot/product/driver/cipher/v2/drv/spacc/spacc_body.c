/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : sapcc_body.c
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/

#include "cipher_adapt.h"
#include "spacc_union_define.h"
#include "spacc_body.h"
#include "spacc_reg.h"

#define SPACC_CHECK_POINT(p) \
    if(!p) return SPACC_ERR_NULL_POINT
#define SPACC_CHECK_INT(val, max) \
    {if((val) >= (max)) return SPACC_ERR_INVALID_PARAM;}

#if 0
#define SAPCC_SYMC_IN_ENTRY_TOTAL_SIZE \
    (sizeof(struct spacc_symc_in_entry_t) * SPACC_MAX_DEPTH)
#define SAPCC_SYMC_OUT_ENTRY_TOTAL_SIZE \
    (sizeof(struct spacc_symc_out_entry_t) * SPACC_MAX_DEPTH)
#define SAPCC_SYMC_ENTRY_TOTAL_SIZE \
    (SAPCC_SYMC_IN_ENTRY_TOTAL_SIZE + SAPCC_SYMC_OUT_ENTRY_TOTAL_SIZE)
#define SAPCC_DIGEST_IN_ENTRY_TOTAL_SIZE \
    (sizeof(struct spacc_digest_in_entry_t) * SPACC_MAX_DEPTH)
#else
#define SAPCC_SYMC_IN_ENTRY_TOTAL_SIZE      (SPACC_PAGE_SIZE)
#define SAPCC_SYMC_OUT_ENTRY_TOTAL_SIZE     (SPACC_PAGE_SIZE)
#define SAPCC_DIGEST_IN_ENTRY_TOTAL_SIZE    (SPACC_PAGE_SIZE)
#endif
#define SPACC_DBG(fmt...)   //HI_PRINT(fmt)

/*spacc symc int entry struct which is defined by hardware, you can't change it */
struct spacc_symc_in_entry_t
{
    unsigned int     spacc_cmd:2;
    unsigned int     rev1:6;
    unsigned int     sym_ctrl:7;
    unsigned int     rev2:1;
    unsigned int     gcm_iv_len:4;
    unsigned int     rev3:12;
    unsigned int     word1;
    unsigned int     sym_start_addr;
    unsigned int     sym_alg_length;
    unsigned int     IV[4];
};

/*spacc digest in entry struct which is defined by hardware, you can't change it */
struct spacc_digest_in_entry_t
{
    unsigned int    spacc_cmd:2;
    unsigned int    rev1:6;
    unsigned int    hash_ctrl:6;
    unsigned int    rev2:18;
    unsigned int    hash_start_addr;
    unsigned int    hash_alg_length;
    unsigned int    word1;
};

/*spacc symc out entry struct which is defined by hardware, you can't change it */
struct spacc_symc_out_entry_t
{
    unsigned int    rev1:8;
    unsigned int    aes_ctrl:4;
    unsigned int    rev2:20;
    unsigned int    sym_start_addr;
    unsigned int    sym_alg_length;
    unsigned int    hash_rslt_start_addr;
    unsigned int    tag[4];
};

struct spacc_symc_context
{
    SYMC_ALG_EN      symc_alg;
    SYMC_MODE_EN     symc_mode;
    unsigned int     symc_IV[4];
    unsigned int     symc_ivlen;

    unsigned int    *pad_vir_addr;
    unsigned int     pad_phy_addr;

    struct spacc_symc_in_entry_t*   entry_symc_in;
    struct spacc_symc_out_entry_t*  entry_symc_out;
    struct spacc_digest_in_entry_t* entry_digest_in;

    unsigned int entry_symc_in_depth;
    unsigned int entry_symc_out_depth;
    unsigned int symc_cur_in_nodes;
    unsigned int symc_cur_out_nodes;
};

struct spacc_digest_context
{
    DIGEST_ALG_EN    digest_alg;
    DIGEST_MODE_EN   digest_mode;
    unsigned int     digest_key[SPACC_MAX_HMAC_KEY_LEN/4];
    unsigned int     digest_klen;
    unsigned int     digest_len;
    unsigned int     digest_blen;

    struct spacc_digest_in_entry_t* entry_digest_in;
    unsigned int entry_digest_in_depth;
    unsigned int digest_cur_in_nodes;

    unsigned int hard_key;
};

static void *s_spacc_reg_base = 0;
static struct spacc_symc_context   s_symc[SPACC_LOGIC_MAX_CHN];
static struct spacc_digest_context s_digest[SPACC_LOGIC_MAX_CHN];

/**
 * spacc_init - spacc hardware initialization.
 * @reg_base: virtual address of spacc module which be accessed by CPU
 * @mmu_table_addr: mmu base table physical addr, if disable mmu, set it to 0
 * @entry_phy_addr: a consecutive physical memory, used for nodes
 *                  list of symc-in, symc-out and hash-in, the size
 *                   must large than spacc_get_node_list_size().
 * @entry_via_addr: virtual address of entry_phy_addr.
 *
 * Description:
 *   spacc hardware initialization as follows:
 *   - reset global var.
 *   - enable interrupt
 *   - set nodes list addr
 *   - set mmu table addr
 *   - configureure hardware register
 *
 * Context:
 *   this function must be called one time in the beginning.
 */
int spacc_init(void *reg_base, unsigned int mmu_table_addr,
               unsigned int entry_phy_addr, void *entry_via_addr)
{
    unsigned int i;
    unsigned int page_phy;
    void * page_via;
    U_CIPHER_INT_EN cipher_int_en;
    U_HASH_INT_EN hash_int_en;

    SPACC_CHECK_POINT(reg_base);
    SPACC_CHECK_POINT(entry_via_addr);

    cipher_memset_s(&s_symc, sizeof(s_symc), 0, sizeof(s_symc));
    cipher_memset_s(&s_digest, sizeof(s_digest), 0, sizeof(s_digest));
    cipher_memset_s(entry_via_addr, spacc_get_node_list_size(),
        0, spacc_get_node_list_size());

    s_spacc_reg_base = reg_base;

    /*secure chn enable*/
#ifndef REE_NONSECURE_ENABLE
    {
        U_SEC_CHN_CFG sec_chn_cfg;
        sec_chn_cfg.u32 = SPACC_READ(SEC_CHN_CFG);
        sec_chn_cfg.bits.cipher_sec_chn_cfg |= SPACC_CHN_MASK;
        sec_chn_cfg.bits.hash_sec_chn_cfg |= SPACC_CHN_MASK;
        SPACC_WRITE(SEC_CHN_CFG, sec_chn_cfg.u32);
        SPACC_DBG("SEC_CHN_CFG[%p]: 0x%x\n", SEC_CHN_CFG, sec_chn_cfg.u32);
        HAL_CIPHER_ReadReg(SEC_CHN_CFG, &sec_chn_cfg.u32);
    }
#endif

    /*smmu enable*/
#ifdef SMMU_ENABLE
    {
        U_CIPHER_IN_SMMU_EN cipher_in_smmu_en;
        U_OUT_SMMU_EN out_smmu_en;
        U_HASH_IN_SMMU_EN hash_in_smmu_en;

        cipher_in_smmu_en.u32 = SPACC_READ(CIPHER_IN_SMMU_EN);
        out_smmu_en.u32 = SPACC_READ(OUT_SMMU_EN);
        hash_in_smmu_en.u32 = SPACC_READ(HASH_IN_SMMU_EN);

        cipher_in_smmu_en.bits.cipher_in_chan_rd_dat_smmu_en  |= SPACC_CHN_MASK >> 1;
        cipher_in_smmu_en.bits.cipher_in_chan_rd_node_smmu_en |= SPACC_CHN_MASK >> 1;

        out_smmu_en.bits.out_chan_wr_dat_smmu_en  |= SPACC_CHN_MASK >> 1;
        out_smmu_en.bits.out_chan_rd_node_smmu_en |= SPACC_CHN_MASK >> 1;

        hash_in_smmu_en.bits.hash_in_chan_rd_dat_smmu_en |= SPACC_CHN_MASK >> 1;
        hash_in_smmu_en.bits.hash_in_chan_rd_node_smmu_en |= SPACC_CHN_MASK >> 1;

        SPACC_WRITE(CIPHER_IN_SMMU_EN, cipher_in_smmu_en.u32);
        SPACC_WRITE(OUT_SMMU_EN, out_smmu_en.u32);
        SPACC_WRITE(HASH_IN_SMMU_EN, hash_in_smmu_en.u32);

        SPACC_DBG("CIPHER_IN_SMMU_EN[%p]: 0x%x\n", CIPHER_IN_SMMU_EN, cipher_in_smmu_en.u32);
        SPACC_DBG("OUT_SMMU_EN[%p]      : 0x%x\n", OUT_SMMU_EN, out_smmu_en.u32);
        SPACC_DBG("HASH_IN_SMMU_EN[%p]  : 0x%x\n", HASH_IN_SMMU_EN, hash_in_smmu_en.u32);
#ifdef REE_NONSECURE_ENABLE
        SPACC_WRITE(NORM_SMMU_START_ADDR, mmu_table_addr);
#else
        SPACC_WRITE(SEC_SMMU_START_ADDR, mmu_table_addr);
#endif
    }
#endif //SMMU_ENABLE

    /*Enable interrupt*/
    cipher_int_en.u32 = SPACC_READ(CIPHER_INT_EN);
    hash_int_en.u32 = SPACC_READ(HASH_INT_EN);

    /*The top interrupt switch only can be enable/disable by secure CPU*/
    cipher_int_en.bits.cipher_nsec_int_en = 1;
    hash_int_en.bits.hash_int_en = 1;
    cipher_int_en.bits.cipher_sec_int_en = 1;
    hash_int_en.bits.hash_sec_int_en = 1;
#ifdef INT_ENABLE
    cipher_int_en.bits.cipher_chn_obuf_en |= SPACC_CHN_MASK;
    hash_int_en.bits.hash_chn_oram_en |= SPACC_CHN_MASK;
#endif
    SPACC_WRITE(CIPHER_INT_EN, cipher_int_en.u32);
    SPACC_WRITE(HASH_INT_EN, hash_int_en.u32);
    SPACC_DBG("CIPHER_INT_EN: 0x%x\n", cipher_int_en.u32);
    SPACC_DBG("HASH_INT_EN: 0x%x\n", hash_int_en.u32);

    /*configure start addr for in-node and out-node */
    page_phy = entry_phy_addr;
    page_via = entry_via_addr;
    for(i=CIPHER_PKGxN_CHAN_MIN; i<=CIPHER_PKGxN_CHAN_MAX; i++)
    {
        U_CHANN_CIPHER_IN_NODE_CFG cipher_in_cfg;
        U_CHANN_CIPHER_OUT_NODE_CFG cipher_out_cfg;
        U_CHANN_HASH_IN_NODE_CFG hash_in_cfg;

        /*set total num and start addr for cipher in node*/
        cipher_in_cfg.u32  = SPACC_READ(CHANn_CIPHER_IN_NODE_CFG(i));
        cipher_in_cfg.bits.cipher_in_node_total_num = SPACC_MAX_DEPTH;
        SPACC_WRITE(CHANn_CIPHER_IN_NODE_CFG(i), cipher_in_cfg.u32);
        SPACC_WRITE(CHANn_CIPHER_IN_NODE_START_ADDR(i), page_phy);
        SPACC_DBG("CHANn_CIPHER_IN_NODE_CFG[%p]: \t0x%x, PHY: 0x%x, VIA %p\n", CHANn_CIPHER_IN_NODE_CFG(i), cipher_in_cfg.u32, page_phy, page_via);
        s_symc[i].entry_symc_in = (struct spacc_symc_in_entry_t*)page_via;
        s_symc[i].symc_cur_in_nodes = cipher_in_cfg.bits.cipher_in_node_wptr;
        s_symc[i].entry_symc_in_depth = 0;
        page_via += SAPCC_SYMC_IN_ENTRY_TOTAL_SIZE;
        page_phy += SAPCC_SYMC_IN_ENTRY_TOTAL_SIZE;

        /*set total num and start addr for cipher out node*/
        cipher_out_cfg.u32 = SPACC_READ(CHANn_CIPHER_OUT_NODE_CFG(i));
        cipher_out_cfg.bits.cipher_out_node_total_num = SPACC_MAX_DEPTH;
        SPACC_WRITE(CHANn_CIPHER_OUT_NODE_CFG(i), cipher_out_cfg.u32);
        SPACC_WRITE(CHANn_CIPHER_OUT_NODE_START_ADDR(i), page_phy);
        SPACC_DBG("CHANn_CIPHER_OUT_NODE_CFG[%p]: \t0x%x, PHY: 0x%x, VIA %p\n", CHANn_CIPHER_OUT_NODE_CFG(i), cipher_out_cfg.u32, page_phy, page_via);
        s_symc[i].entry_symc_out = (struct spacc_symc_out_entry_t*)page_via;
        s_symc[i].symc_cur_out_nodes = cipher_out_cfg.bits.cipher_out_node_wptr;
        s_symc[i].entry_symc_out_depth = 0;
        page_via += SAPCC_SYMC_OUT_ENTRY_TOTAL_SIZE;
        page_phy += SAPCC_SYMC_OUT_ENTRY_TOTAL_SIZE;

        /*set total num and start addr for hash in node*/
        hash_in_cfg.u32 = SPACC_READ(CHANn_HASH_IN_NODE_CFG(i));
        hash_in_cfg.bits.hash_in_node_total_num = SPACC_MAX_DEPTH;
        SPACC_WRITE(CHANn_HASH_IN_NODE_CFG(i), hash_in_cfg.u32);
        SPACC_WRITE(CHANn_HASH_IN_NODE_START_ADDR(i), page_phy);
        SPACC_DBG("CHANn_HASH_IN_NODE_CFG[%p]: \t0x%x, PHY: 0x%x, VIA %p\n", CHANn_HASH_IN_NODE_CFG(i), hash_in_cfg.u32, page_phy, page_via);
        s_digest[i].entry_digest_in = (struct spacc_digest_in_entry_t*)page_via;
        s_digest[i].digest_cur_in_nodes = hash_in_cfg.bits.hash_in_node_wptr;
        s_digest[i].entry_digest_in_depth = 0;
        page_via += SAPCC_DIGEST_IN_ENTRY_TOTAL_SIZE;
        page_phy += SAPCC_DIGEST_IN_ENTRY_TOTAL_SIZE;
    }

    return SPACC_OK;
}

/**
 * spacc_deinit - spacc hardware deinit.
 */
int spacc_deinit(void)
{
    return SPACC_OK;
}

/**
 * spacc_get_node_list_size - return the total size of nodes lists memory required by the drive.
 */
unsigned int spacc_get_node_list_size(void)
{
    /*********************************************************************
    symc in node page x1| symc out node page x0.5 | hash in node page x0.5
    *********************************************************************/
    return (SPACC_PAGE_SIZE * 3) * (CIPHER_PKGxN_CHAN_MAX - CIPHER_PKGxN_CHAN_MIN + 1);
}

int spacc_symc_getiv(unsigned int chn_num, unsigned int *iv,  unsigned int ivsize)
{
    unsigned int i;

    SPACC_CHECK_INT(chn_num, SPACC_LOGIC_MAX_CHN);

    for(i=0; i < 4; i++)
    {
        iv[i] = SPACC_READ(CHANn_CIPHER_IVOUT(chn_num));
    }

    return SPACC_OK;
}

/**
 * spacc_symc_gettag - get the tag for CCM/GCM.
 */
int spacc_symc_gettag(unsigned int chn_num, unsigned char *tag)
{
    struct spacc_symc_context *info = &s_symc[chn_num];
    U_CHANN_CIPHER_OUT_NODE_CFG out_node_cfg;
    unsigned int last;

    SPACC_CHECK_INT(chn_num, SPACC_LOGIC_MAX_CHN);

    out_node_cfg.u32 = SPACC_READ(CHANn_CIPHER_OUT_NODE_CFG(chn_num));
    last = out_node_cfg.bits.cipher_out_node_wptr;
    last = (last == 0) ? (SPACC_MAX_DEPTH - 1) : (last -1);

    cipher_memcpy_s(tag, 16, info->entry_symc_out[last].tag, sizeof(info->entry_symc_out[last].tag));
//    HI_PRINT_HEX ("tag", tag, 16);

    return SPACC_OK;
}

/**
 * spacc_symc_setkey - set even key and odd key for symc.
 * @chn_num: the logic channel number, must 1~7.
 * @even_key: even key
 * @odd_key:  odd key
 * @klen:     length of key.
 *
 * Description:
 *   the odd key only valid for aes ecb/cbc/ofb/cfb/ctr, and the data to encrypt/decprypt
 *   must be aligned with 64.
 *
 */
int spacc_symc_setkey(unsigned int chn_num, unsigned int *even_key, unsigned int *odd_key, unsigned int klen)
{
    struct spacc_symc_context *info = &s_symc[chn_num];
    unsigned int i;

    SPACC_CHECK_INT(chn_num, SPACC_LOGIC_MAX_CHN);

    SPACC_CHECK_POINT(even_key);
    SPACC_CHECK_POINT(odd_key);
    SPACC_CHECK_INT(klen, 49);

    /*Set odd key, only valid for aes ecb/cbc/ofb/cfb/ctr*/
    SPACC_WRITE(ODD_EVEN_KEY_SEL, 0x01);
    for(i=0; (i<klen/4) && (i<8); i++)
    {
        SPACC_WRITE(CIPHER_KEY(chn_num)+i*4, odd_key[i]);
        SPACC_DBG("ODD key[%p]: 0x%x\n", CIPHER_KEY(chn_num)+i*4, odd_key[i]);
    }

    /*Set even key*/
    SPACC_WRITE(ODD_EVEN_KEY_SEL, 0x00);
    for(i=0; (i<klen/4) && (i<8); i++)
    {
        SPACC_WRITE(CIPHER_KEY(chn_num)+i*4, even_key[i]);
        SPACC_DBG("EVEN key[%p]: 0x%x\n", CIPHER_KEY(chn_num)+i*4, even_key[i]);
    }

    if (info->symc_alg == SYMC_ALG_SM1)
    {
        for(i=0; i<4; i++)
        {
            SPACC_WRITE(SM1_SK(chn_num)+i*4, even_key[i + 8]);
            SPACC_DBG("SK[%p]: 0x%x\n", SM1_SK(chn_num)+i*4, even_key[i + 8]);
        }
    }

    return SPACC_OK;
}

/**
 * spacc_symc_setiv - set iv for symc.
 * @chn_num: the logic channel number, must 1~7.
 * @iv: the initialization vector
 * @ivlen:  length of iv.
 *
 * Description:
 *   here store the iv to global structure of channel, don't set to logic,
 *   because the IV must be set in the nodes list.
 *
 */
int spacc_symc_setiv(unsigned int chn_num, unsigned char *iv, unsigned int ivlen)
{
    struct spacc_symc_context *info = &s_symc[chn_num];

    SPACC_CHECK_INT(chn_num, SPACC_LOGIC_MAX_CHN);
    SPACC_CHECK_POINT(iv);
    SPACC_CHECK_INT(ivlen, 33);

    cipher_memset_s(info->symc_IV, sizeof(info->symc_IV), 0, 16);
    cipher_memcpy_s(info->symc_IV, sizeof(info->symc_IV), iv, ivlen);
    info->symc_ivlen = ivlen;

    return SPACC_OK;
}

/**
 * spacc_symc_addbuf - filling the buf addr and length of
 *   encrypt/decrypt data into nodes list.
 *
 */
int spacc_symc_addbuf(unsigned int chn_num, unsigned int buf_phy,
                         unsigned int buf_size,
                         SPACC_BUF_TYPE_EN type,
                         unsigned int ctrl)
{
    struct spacc_symc_context *info = &s_symc[chn_num];
    unsigned int id, size;
    void *addr;

    SPACC_CHECK_INT(chn_num, SPACC_LOGIC_MAX_CHN);
    switch(type)
    {
    case SPACC_BUF_TYPE_SYMC_IN:
        id = info->symc_cur_in_nodes++;
        addr = &info->entry_symc_in[id];
        size = sizeof(struct spacc_symc_in_entry_t);
        cipher_memset_s(addr, sizeof(info->entry_symc_in[id]), 0, size);
        info->entry_symc_in[id].spacc_cmd = 0x00;
        info->entry_symc_in[id].sym_start_addr = buf_phy;
        info->entry_symc_in[id].sym_alg_length = buf_size;
        info->entry_symc_in[id].sym_ctrl =  ctrl;
        info->entry_symc_in_depth++;
        info->symc_cur_in_nodes %= SPACC_MAX_DEPTH;
        SPACC_DBG("chn %d, add symc in buf: id %d, addr 0x%x, len 0x%x, ctrl 0x%x\n", chn_num, id, buf_phy, buf_size, ctrl);
        break;
     case SPACC_BUF_TYPE_SYMC_OUT:
        id = info->symc_cur_out_nodes++;
        addr = &info->entry_symc_out[id];
        size = sizeof(struct spacc_symc_out_entry_t);
        cipher_memset_s(addr, sizeof(info->entry_symc_out[id]), 0, size);
        info->entry_symc_out[id].sym_start_addr = buf_phy;
        info->entry_symc_out[id].sym_alg_length = buf_size;
        info->entry_symc_out[id].aes_ctrl = ctrl;
        info->entry_symc_out_depth++;
        info->symc_cur_out_nodes %= SPACC_MAX_DEPTH;
        SPACC_DBG("chn %d, add symc out buf: id %d, addr 0x%x, len 0x%x\n", chn_num, id, buf_phy, buf_size);
        break;
     default:
        return SPACC_ERR_INVALID_PARAM;
    }

    return SPACC_OK;
}

/**
 * spacc_symc_addbuf - add a flags to the last valid nodes.
 *
 */
int spacc_symc_addctrl(unsigned int chn_num, SPACC_BUF_TYPE_EN type, unsigned int ctrl)
{
    struct spacc_symc_context *info = &s_symc[chn_num];
    unsigned int id;

    SPACC_CHECK_INT(chn_num, SPACC_LOGIC_MAX_CHN);

    switch(type)
    {
    case SPACC_BUF_TYPE_SYMC_IN:
        id = (info->symc_cur_in_nodes == 0) ? SPACC_MAX_DEPTH - 1 : info->symc_cur_in_nodes - 1;
        info->entry_symc_in[id].sym_ctrl |= ctrl;
        break;
     case SPACC_BUF_TYPE_SYMC_OUT:
        id = (info->symc_cur_out_nodes == 0) ? SPACC_MAX_DEPTH - 1 : info->symc_cur_out_nodes - 1;
        info->entry_symc_out[id].aes_ctrl |= ctrl;
        break;
     default:
        return SPACC_ERR_INVALID_PARAM;
    }

    return SPACC_OK;
}

/**
 * spacc_symc_configure - configure logic register, such as alg, mode, key len and so on.
 *
 */
int spacc_symc_config(unsigned int chn_num, SYMC_ALG_EN symc_alg,
                          SYMC_MODE_EN symc_mode,
                          SYMC_DAT_WIDTH_EN symc_width,
                          unsigned char sm1_round_num,
                          unsigned char klen,
                          unsigned char hard_key)
{
    struct spacc_symc_context *info = &s_symc[chn_num];
    U_CHANN_CIPHER_CTRL cipher_ctrl;
    unsigned int symc_klen = 0;

    SPACC_CHECK_INT(chn_num, SPACC_LOGIC_MAX_CHN);
    SPACC_CHECK_INT(symc_alg, SYMC_ALG_COUNT);
    SPACC_CHECK_INT(symc_mode, SYMC_MODE_COUNT);
    SPACC_CHECK_INT(symc_width, SYMC_DAT_WIDTH_COUNT);

    if (symc_alg == SYMC_ALG_AES)
    {
        symc_klen = klen/8 - 2;
    }
    else if (symc_alg == SYMC_ALG_3DES)
    {
        symc_klen = (klen == 16 ? 3 : 2);
    }

 //   SPACC_DBG("chn_num %d, symc_alg %d, symc_mode %d, symc klen %d, klen %d\n",
 //       chn_num, symc_alg, symc_mode, symc_klen, klen);

    cipher_ctrl.u32 = SPACC_READ(CHANn_CIPHER_CTRL(chn_num));
    cipher_ctrl.bits.sym_chn_sm1_round_num = sm1_round_num;
    cipher_ctrl.bits.sym_chn_key_sel = hard_key;
    cipher_ctrl.bits.sym_chn_key_length = symc_klen;
    cipher_ctrl.bits.sym_chn_dat_width = symc_width;
    cipher_ctrl.bits.sym_chn_decrypt = 0x00;
    cipher_ctrl.bits.sym_chn_alg_sel = symc_alg;
    cipher_ctrl.bits.sym_chn_alg_mode = symc_mode;
    SPACC_WRITE(CHANn_CIPHER_CTRL(chn_num), cipher_ctrl.u32);
    SPACC_DBG("CHANn_CIPHER_CTRL(%d): 0x%x\n", chn_num, cipher_ctrl.u32);

    info->symc_alg = symc_alg;
    info->symc_mode = symc_mode;
    info->entry_symc_in_depth = 0;
    info->entry_symc_out_depth = 0;

    return SPACC_OK;
}

/**
 * spacc_symc_start - action the symc start to processing the node list.
 *
 */
int spacc_symc_start(unsigned int chn_num, unsigned int decrypt, unsigned int iv_set_flag)
{
    unsigned int cur;
    unsigned int i, j;
    unsigned int node;
    U_CHANN_CIPHER_IN_NODE_CFG in_node_cfg;
    U_CHANN_CIPHER_OUT_NODE_CFG out_node_cfg;
    U_CHANN_CIPHER_CTRL cipher_ctrl;
    unsigned int ptr;
    struct spacc_symc_context *info = &s_symc[chn_num];

    SPACC_CHECK_INT(chn_num, SPACC_LOGIC_MAX_CHN);

    in_node_cfg.u32 = SPACC_READ(CHANn_CIPHER_IN_NODE_CFG(chn_num));
    ptr = in_node_cfg.bits.cipher_in_node_wptr + info->entry_symc_in_depth;
    in_node_cfg.bits.cipher_in_node_wptr = ptr % SPACC_MAX_DEPTH;
    in_node_cfg.bits.cipher_in_node_mpackage_int_level = info->entry_symc_in_depth;
    cur = in_node_cfg.bits.cipher_in_node_rptr;

    SPACC_DBG("cur %d, depth %d, IV Len %d\n", cur, info->entry_symc_in_depth, info->symc_ivlen);
    for(j=0; j<info->entry_symc_in_depth; j++)
    {
        if(info->symc_ivlen > 0)
        {
            /*Write iv to all nodes*/
            node = (cur + j) % SPACC_MAX_DEPTH;
            for(i=0; i<4; i++)
            {
                info->entry_symc_in[node].IV[i] = info->symc_IV[i];
                SPACC_DBG("IV[%d]: 0x%x\n", i, info->symc_IV[i]);
            }

            /*Set iv len for GCM*/
            if(info->symc_mode == SYMC_MODE_GCM)
            {
                info->entry_symc_in[node].gcm_iv_len = info->symc_ivlen - 1;
            }
            else
            {
                info->entry_symc_in[node].gcm_iv_len = 0;
            }

            /*IV only be set for first node.*/
            if (iv_set_flag == CIPHER_IV_CHANGE_ONE_PKG)
            {
                info->entry_symc_in[node].sym_ctrl |= SPACC_CTRL_SYMC_IN_FIRST;
                iv_set_flag = 0;
            }
            /*IV will be set for each node.*/
            else if ((iv_set_flag == CIPHER_IV_CHANGE_ALL_PKG)
                && (info->symc_mode != SYMC_MODE_CCM)
                && (info->symc_mode != SYMC_MODE_GCM))
            {
                info->entry_symc_in[node].sym_ctrl |= SPACC_CTRL_SYMC_IN_FIRST | SPACC_CTRL_SYMC_IN_LAST;
            }
        }
    }

    /*encrypt or decrypt*/
    cipher_ctrl.u32 = SPACC_READ(CHANn_CIPHER_CTRL(chn_num));
    cipher_ctrl.bits.sym_chn_decrypt = decrypt;
    SPACC_WRITE(CHANn_CIPHER_CTRL(chn_num), cipher_ctrl.u32);

    /*configure out nodes*/
    out_node_cfg.u32 = SPACC_READ(CHANn_CIPHER_OUT_NODE_CFG(chn_num));
    if (out_node_cfg.bits.cipher_out_node_wptr != out_node_cfg.bits.cipher_out_node_rptr)
    {
        SPACC_DBG("Error, chn %d is busy.\n", chn_num);
        return SPACC_ERR_BUSY;
    }
    ptr = out_node_cfg.bits.cipher_out_node_wptr + info->entry_symc_out_depth;
    out_node_cfg.bits.cipher_out_node_wptr = ptr % SPACC_MAX_DEPTH;
    out_node_cfg.bits.cipher_out_node_mpackage_int_level = info->entry_symc_out_depth;
    SPACC_WRITE(CHANn_CIPHER_OUT_NODE_CFG(chn_num), out_node_cfg.u32);
    SPACC_DBG("CHANn_CIPHER_OUT_NODE_CFG: 0x%x\n", out_node_cfg.u32);

    flush_cache();

    /*configure in nodes*/
    SPACC_DBG("CHANn_CIPHER_IN_NODE_CFG: 0x%x\n", in_node_cfg.u32);
    SPACC_DBG("chn %d, start 0x%x from 0x%x to 0x%x\n", chn_num, info->entry_symc_in_depth, in_node_cfg.bits.cipher_in_node_rptr, in_node_cfg.bits.cipher_in_node_wptr);

    /*move forward the in-node ptr to action the symc working*/
    SPACC_WRITE(CHANn_CIPHER_IN_NODE_CFG(chn_num), in_node_cfg.u32);

    /*all the nodes are processing, reset the depth to 0*/
    info->entry_symc_in_depth = 0;
    info->entry_symc_out_depth = 0;

    return SPACC_OK;
}

/**
 * spacc_symc_last_node - get the symc last addr and size in the node list.
 *
 */
int spacc_symc_last_node(unsigned int chn_num,
                         unsigned int *in_addr, unsigned int *in_size,
                         unsigned int *out_addr, unsigned int *out_size)
{
    U_CHANN_CIPHER_IN_NODE_CFG in_node_cfg;
    U_CHANN_CIPHER_OUT_NODE_CFG out_node_cfg;
    unsigned int ptr;
    struct spacc_symc_context *info = &s_symc[chn_num];

    SPACC_CHECK_INT(chn_num, SPACC_LOGIC_MAX_CHN);

    in_node_cfg.u32 = SPACC_READ(CHANn_CIPHER_IN_NODE_CFG(chn_num));
    ptr = (in_node_cfg.bits.cipher_in_node_wptr + SPACC_MAX_DEPTH - 1) % SPACC_MAX_DEPTH;
    *in_addr = info->entry_symc_in[ptr].sym_start_addr;
    *in_size = info->entry_symc_in[ptr].sym_alg_length;

    out_node_cfg.u32 = SPACC_READ(CHANn_CIPHER_OUT_NODE_CFG(chn_num));
    ptr = (out_node_cfg.bits.cipher_out_node_wptr + SPACC_MAX_DEPTH - 1) % SPACC_MAX_DEPTH;
    *out_addr = info->entry_symc_out[ptr].sym_start_addr;
    *out_size = info->entry_symc_out[ptr].sym_alg_length;

    return SPACC_OK;
}

/**
 * spacc_symc_restart - continue to action the symc to processing the node list.
 *
 */
void spacc_symc_restart(unsigned int chn_num, unsigned int iv_set_flag)
{
    U_CHANN_CIPHER_IN_NODE_CFG in_node_cfg;
    U_CHANN_CIPHER_OUT_NODE_CFG out_node_cfg;
    unsigned int ptr;
    unsigned int cur;
    unsigned int i, j;
    unsigned int node;
    struct spacc_symc_context *info = &s_symc[chn_num];

    if (info->entry_symc_in_depth == 0)
    {
        return;
    }

    out_node_cfg.u32 = SPACC_READ(CHANn_CIPHER_OUT_NODE_CFG(chn_num));
    ptr = out_node_cfg.bits.cipher_out_node_wptr + info->entry_symc_in_depth;
    out_node_cfg.bits.cipher_out_node_wptr =  ptr % SPACC_MAX_DEPTH;
    out_node_cfg.bits.cipher_out_node_mpackage_int_level = info->entry_symc_out_depth;
    SPACC_WRITE(CHANn_CIPHER_OUT_NODE_CFG(chn_num), out_node_cfg.u32);
//    SPACC_DBG("CHANn_CIPHER_OUT_NODE_CFG: 0x%x\n", out_node_cfg.u32);

    in_node_cfg.u32 = SPACC_READ(CHANn_CIPHER_IN_NODE_CFG(chn_num));
    if ((iv_set_flag == CIPHER_IV_CHANGE_ALL_PKG)
        && (info->symc_mode != SYMC_MODE_CCM)
        && (info->symc_mode != SYMC_MODE_GCM))
    {
        cur = in_node_cfg.bits.cipher_in_node_wptr;
        for(j=0; j<info->entry_symc_in_depth; j++)
        {
            if(info->symc_ivlen > 0)
            {
                node = (cur + j) % SPACC_MAX_DEPTH;
                for(i=0; i<4; i++)
                {
                    info->entry_symc_in[node].IV[i] = info->symc_IV[i];
                    SPACC_DBG("IV[%d]: 0x%x\n", i, info->symc_IV[i]);
                }
                info->entry_symc_in[node].sym_ctrl |= 0x01;
            }
        }
    }

    ptr = in_node_cfg.bits.cipher_in_node_wptr + info->entry_symc_out_depth;
    in_node_cfg.bits.cipher_in_node_wptr = ptr % SPACC_MAX_DEPTH;
    in_node_cfg.bits.cipher_in_node_mpackage_int_level = info->entry_symc_in_depth;

    flush_cache();

    SPACC_DBG("chn %d, restart 0x%x from 0x%x to 0x%x\n", chn_num, info->entry_symc_in_depth, in_node_cfg.bits.cipher_in_node_rptr, in_node_cfg.bits.cipher_in_node_wptr);

//    SPACC_DBG("CHANn_CIPHER_IN_NODE_CFG: 0x%x\n", in_node_cfg.u32);
    SPACC_WRITE(CHANn_CIPHER_IN_NODE_CFG(chn_num), in_node_cfg.u32);

    info->entry_symc_in_depth = 0;
    info->entry_symc_out_depth = 0;
}

/**
 * spacc_symc_done_try - get the int status of symc.
 *
 */
unsigned int spacc_symc_done_notify(void)
{
    U_CIPHER_INT_RAW    int_raw;
    unsigned int chn_mask;

    int_raw.u32 = SPACC_READ(CIPHER_INT_RAW);
    int_raw.bits.cipher_chn_obuf_raw &= SPACC_CHN_MASK;
    chn_mask = int_raw.bits.cipher_chn_obuf_raw;
    SPACC_WRITE(CIPHER_INT_RAW, int_raw.u32);

    return chn_mask;
}

/**
 * spacc_symc_done_try - test the int status of symc channel.
 *
 */
unsigned int spacc_symc_done_try(unsigned int chn_num)
{
    U_CIPHER_INT_RAW    int_raw;
    unsigned int chn_mask;

    int_raw.u32 = SPACC_READ(CIPHER_INT_RAW);
    int_raw.bits.cipher_chn_obuf_raw &= 0x01 << chn_num;
    chn_mask = int_raw.bits.cipher_chn_obuf_raw;

    /*Clean raw int*/
    int_raw.u32 = 0x00;
    int_raw.bits.cipher_chn_obuf_raw = chn_mask;
    SPACC_WRITE(CIPHER_INT_RAW, int_raw.u32);

    return chn_mask ? 1 : 0;
}

/**
 * spacc_symc_get_err_code - get the error code of symc.
 *
 */
unsigned int spacc_symc_get_err_code(unsigned int chn_num,
                                     unsigned int *src_addr,
                                     unsigned int *dst_addr)
{
    *src_addr = SPACC_READ(CHANn_CIPHER_IN_BUF_RPTR(chn_num));
    *dst_addr = SPACC_READ(CHANn_CIPHER_OUT_BUF_RPTR(chn_num));

    return SPACC_READ(CALC_ERR);
}

/**
 * spacc_digest_configure - configure the hash ctrl register.
 *
 */
int spacc_digest_config(unsigned int chn_num, DIGEST_ALG_EN digest_alg,
                                DIGEST_MODE_EN digest_mode,
                                unsigned char hard_key)
{
    struct spacc_digest_context *info = &s_digest[chn_num];
    U_CHANN_HASH_CTRL hash_ctrl;

    SPACC_CHECK_INT(chn_num, SPACC_LOGIC_MAX_CHN);
    SPACC_CHECK_INT(digest_alg, DIGEST_ALG_COUNT);
    SPACC_CHECK_INT(digest_mode, DIGEST_MODE_COUNT);

    info->digest_alg = digest_alg;
    info->digest_mode = digest_mode;

    switch(digest_alg)
    {
    case DIGEST_ALG_SHA1:
        info->digest_len = 20;
        info->digest_blen = 64;
        break;
    case DIGEST_ALG_SHA224:
        info->digest_len = 28;
        info->digest_blen = 64;
        break;
    case DIGEST_ALG_SM3:
    case DIGEST_ALG_SHA256:
        info->digest_len = 32;
        info->digest_blen = 64;
        break;
    case DIGEST_ALG_SHA384:
        info->digest_len = 48;
        info->digest_blen = 128;
        break;
    case DIGEST_ALG_SHA512:
        info->digest_len = 64;
        info->digest_blen = 128;
        break;
    default:
        return SPACC_ERR_INVALID_PARAM;
    }

    hash_ctrl.u32 = SPACC_READ(CHANn_HASH_CTRL(chn_num));
    hash_ctrl.bits.hash_chn_mode = digest_mode;
    hash_ctrl.bits.hash_chn_agl_sel = digest_alg;
    SPACC_WRITE(CHANn_HASH_CTRL(chn_num), hash_ctrl.u32);
    SPACC_DBG("CTRL: 0x%X\n", hash_ctrl.u32);

    info->entry_digest_in_depth = 0;
    info->hard_key = hard_key;

    return SPACC_OK;
}

/**
 * spacc_digest_addbuf - filling the buf addr and length of
 *   data into nodes list.
 *
 */
int spacc_digest_addbuf(unsigned int chn_num,
                         unsigned int buf_phy,
                         unsigned int buf_size,
                         unsigned int ctrl)
{
    struct spacc_digest_context *info = &s_digest[chn_num];
    unsigned int id, size;
    void *addr;

    SPACC_CHECK_INT(chn_num, SPACC_LOGIC_MAX_CHN);

    id = info->digest_cur_in_nodes++;
    addr = &info->entry_digest_in[id];
    size = sizeof(struct spacc_digest_in_entry_t);
    cipher_memset_s(addr, sizeof(info->entry_digest_in[id]), 0, size);
    info->entry_digest_in[id].spacc_cmd = 0x00;
    info->entry_digest_in[id].hash_start_addr = buf_phy;
    info->entry_digest_in[id].hash_alg_length = buf_size;
    info->entry_digest_in[id].hash_ctrl = ctrl;
    info->entry_digest_in_depth++;
    info->digest_cur_in_nodes %= SPACC_MAX_DEPTH;
    SPACC_DBG("add digest in buf: id %d, addr 0x%x, len 0x%x, ctrl 0x%x\n", id, buf_phy, buf_size, ctrl);

    return SPACC_OK;
}

/**
 * spacc_digest_addctrl - add a flags to the last valid nodes.
 *
 */
int spacc_digest_addctrl(unsigned int chn_num, unsigned int ctrl)
{
    struct spacc_digest_context *info = &s_digest[chn_num];
    unsigned int id;

    SPACC_CHECK_INT(chn_num, SPACC_LOGIC_MAX_CHN);

    id = (info->digest_cur_in_nodes == 0) ? SPACC_MAX_DEPTH - 1 : info->digest_cur_in_nodes - 1;
    info->entry_digest_in[id].hash_ctrl |= ctrl;

    return SPACC_OK;
}

/**
 * spacc_digest_get - get hash result.
 *
 */
int spacc_digest_get(unsigned int chn_num, unsigned int *digest)
{
    unsigned int i;

    SPACC_CHECK_INT(chn_num, SPACC_LOGIC_MAX_CHN);

    for(i=0; i<16; i++)
    {
        SPACC_WRITE(CHANn_HASH_STATE_VAL_ADDR(chn_num), i);
        digest[i] = SPACC_READ(CHANn_HASH_STATE_VAL(chn_num));
        SPACC_DBG("digest[%d]: 0x%x\n", i, digest[i]);
    }

    return SPACC_OK;
}

/**
 * spacc_digest_start - action the hash start to processing the node list.
 *
 */
int spacc_digest_start(unsigned int chn_num, SPACC_CTRL_EN enCtrl,
                                unsigned int *state)
{
    unsigned int i;
    U_CHANN_HASH_IN_NODE_CFG in_node_cfg;
    struct spacc_digest_context *info = &s_digest[chn_num];
    unsigned int ptr;

    SPACC_CHECK_INT(chn_num, SPACC_LOGIC_MAX_CHN);

    SPACC_DBG("chn %d, digest_mode %d, ctrl %d\n", chn_num, info->digest_mode, enCtrl);

    /*Write last state*/
    for(i=0; i<16; i++)
    {
        SPACC_WRITE(CHANn_HASH_STATE_VAL_ADDR(chn_num), i);
        SPACC_WRITE(CHANn_HASH_STATE_VAL(chn_num), state[i]);
        SPACC_DBG("state: 0x%x\n", state[i]);
    }

    if(info->entry_digest_in_depth == 0)
    {
        return SPACC_OK;
    }

    /*configure in-node*/
    in_node_cfg.u32 = SPACC_READ(CHANn_HASH_IN_NODE_CFG(chn_num));
    if (in_node_cfg.bits.hash_in_node_wptr != in_node_cfg.bits.hash_in_node_rptr)
    {
        SPACC_DBG("Error, chn %d is busy.\n", chn_num);
        return SPACC_ERR_BUSY;
    }
    ptr = in_node_cfg.bits.hash_in_node_wptr + info->entry_digest_in_depth;
    in_node_cfg.bits.hash_in_node_wptr = ptr % SPACC_MAX_DEPTH;
    in_node_cfg.bits.hash_in_node_mpackage_int_level = 1;

    flush_cache();

    /*Start*/
    SPACC_WRITE(CHANn_HASH_IN_NODE_CFG(chn_num), in_node_cfg.u32);
    SPACC_DBG("CHANn_HASH_IN_NODE_CFG: 0x%x\n", in_node_cfg.u32);

    return SPACC_OK;
}

/**
 * spacc_digest_last_node - get the hash last addr and size in the node list.
 *
 */
int spacc_digest_last_node(unsigned int chn_num, unsigned int *addr, unsigned int *size)
{
    U_CHANN_HASH_IN_NODE_CFG in_node_cfg;
    struct spacc_digest_context *info = &s_digest[chn_num];
    unsigned int ptr;

    SPACC_CHECK_INT(chn_num, SPACC_LOGIC_MAX_CHN);

    /*configure in-node*/
    in_node_cfg.u32 = SPACC_READ(CHANn_HASH_IN_NODE_CFG(chn_num));
    ptr = (in_node_cfg.bits.hash_in_node_wptr + SPACC_MAX_DEPTH - 1) % SPACC_MAX_DEPTH;
    *addr = info->entry_digest_in[ptr].hash_start_addr;
    *size = info->entry_digest_in[ptr].hash_alg_length;

    return SPACC_OK;
}

/**
 * spacc_digest_done_notify - get the int status of hash.
 *
 */
unsigned int spacc_digest_done_notify(void)
{
    U_HASH_INT_RAW    int_raw;
    unsigned int chn_mask;

    int_raw.u32 = SPACC_READ(HASH_INT_RAW);
    int_raw.bits.hash_chn_oram_raw &= SPACC_CHN_MASK;
    chn_mask = int_raw.bits.hash_chn_oram_raw;

    /*Clean raw int*/
    SPACC_WRITE(HASH_INT_RAW, int_raw.u32);

    return chn_mask;
}

/**
 * spacc_digest_done_try - test the int status of hash channel.
 *
 */
unsigned int spacc_digest_done_try(unsigned int chn_num)
{
    U_HASH_INT_RAW    int_raw;
    unsigned int chn_mask;

    int_raw.u32 = SPACC_READ(HASH_INT_RAW);
    int_raw.bits.hash_chn_oram_raw &= 0x01 << chn_num;
    chn_mask = int_raw.bits.hash_chn_oram_raw;

    /*Clean raw int*/
    SPACC_WRITE(HASH_INT_RAW, int_raw.u32);

    return chn_mask;
}

/**
 * spacc_digest_get_err_code - get the error code of hash.
 *
 */
unsigned int spacc_digest_get_err_code(unsigned int chn_num,
                                     unsigned int *src_addr)
{
    *src_addr = SPACC_READ(CHANn_HASH_IN_BUF_RPTR(chn_num));

    return SPACC_READ(CALC_ERR);
}

