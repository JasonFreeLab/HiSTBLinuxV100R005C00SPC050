/* the total cipher hard channel which we can used*/
#define CIPHER_HARD_CHANNEL_CNT         (0x04)

/* mask which cipher channel we can used, bit0 meas channel 0*/
#define CIPHER_HARD_CHANNEL_MASK        (0xF0)

/* the total hash hard channel which we can used*/
#define HASH_HARD_CHANNEL_CNT           (0x01)

/* mask which cipher channel we can used, bit0 meas channel 0*/
#define HASH_HARD_CHANNEL_MASK          (0x01)
#define HASH_HARD_CHANNEL               (0x00)

/* the total cipher hard key channel which we can used*/
#define CIPHER_HARD_KEY_CHANNEL_CNT     (0x04)

/* mask which cipher hard key channel we can used, bit0 meas channel 0*/
#define CIPHER_HARD_KEY_CHANNEL_MASK    (0xF0)

/* secure cpu*/
#define CRYPTO_SEC_CPU

/* enable self test */
/* enable self test */
#ifdef CFG_HI_TEE_TEST_SUPPORT
#define HI_CIPHER_TEST
#define HI_CIPHER_DEBUG
#endif

/* non-support multiple soft hash channel */
#define  MHASH_NONSUPPORT

/* the hardware version */
#define CHIP_SYMC_VER_V100
//#define CHIP_HDCP_VER_V100
#define CHIP_HASH_VER_V100
#define CHIP_TRNG_VER_V100
#define SOFT_SHA1_SUPPORT
#define SOFT_SHA256_SUPPORT
#define SOFT_SHA512_SUPPORT
#define SOFT_SM2_SUPPORT
#define SOFT_SM3_SUPPORT
#define SOFT_SM4_SUPPORT
#define SOFT_ECC_SUPPORT
#define SOFT_RSA_SUPPORT
#define SOFT_AES_CTS_SUPPORT

/* moudle unsupport, we need set the table*/
#define BASE_TABLE_NULL    {\
    .reset_valid = 0,  \
    .clk_valid = 0, \
    .phy_valid = 0, \
    .crg_valid = 0, \
    .ver_valid = 0, \
    .int_valid = 0, \
}

/* define initial value of struct sys_arch_boot_dts for cipher*/
#define HARD_INFO_CIPHER {\
    .name = "cipher",  \
    .reset_valid = 1,  \
    .clk_valid = 1, \
    .phy_valid = 1, \
    .crg_valid = 1, \
    .ver_valid = 0, \
    .int_valid = 0, \
    .clk_bit = 12, \
    .reset_bit = 9, \
    .int_num = 126, \
    .reg_addr_phy = 0xF9A00000, \
    .reg_addr_size = 0x4000,\
    .crg_addr_phy = 0xF8A220C0, \
}

/* define initial value of struct sys_arch_boot_dts for HASH*/
#define HARD_INFO_TRNG {\
    .name = "trng",  \
    .reset_valid = 0,  \
    .clk_valid = 0, \
    .phy_valid = 1, \
    .crg_valid = 0, \
    .ver_valid = 0, \
    .int_valid = 0, \
    .reg_addr_phy = 0xF8005000,  \
    .reg_addr_size = 0x1000,\
}

/* define initial value of struct sys_arch_boot_dts for cipher*/
#define HARD_INFO_HASH {\
    .name = "hash",  \
    .reset_valid = 1,  \
    .clk_valid = 1, \
    .phy_valid = 1, \
    .crg_valid = 1, \
    .ver_valid = 0, \
    .int_valid = 0, \
    .clk_bit = 0, \
    .reset_bit = 4, \
    .reg_addr_phy = 0xF9A10000, \
    .reg_addr_size = 0x1000,\
    .crg_addr_phy = 0xF8A220C4, \
}

#define HARD_INFO_IFEP_RSA         BASE_TABLE_NULL
#define HARD_INFO_SIC_RSA          BASE_TABLE_NULL
#define HARD_INFO_CIPHER_KEY       BASE_TABLE_NULL
#define HARD_INFO_SM2              BASE_TABLE_NULL
#define HARD_INFO_SM4              BASE_TABLE_NULL
#define HARD_INFO_SMMU             BASE_TABLE_NULL

