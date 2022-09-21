
/* the total cipher hard channel which we can used*/
#define CIPHER_HARD_CHANNEL_CNT         (0x06)

/* mask which cipher channel we can used, bit0 meas channel 0*/
#define CIPHER_HARD_CHANNEL_MASK        (0xFC)

/* the total hash hard channel which we can used*/
#define HASH_HARD_CHANNEL_CNT           (0x01)

/* mask which cipher channel we can used, bit0 meas channel 0*/
#define HASH_HARD_CHANNEL_MASK          (0x10)
#define HASH_HARD_CHANNEL               (0x04)

/* the total cipher hard key channel which we can used*/
#define CIPHER_HARD_KEY_CHANNEL_CNT     (0x04)

/* mask which cipher hard key channel we can used, bit0 meas channel 0*/
#define CIPHER_HARD_KEY_CHANNEL_MASK    (0xF0)

/* support smmu*/
#define CRYPTO_SMMU_SUPPORT

/* secure cpu*/
#define CRYPTO_SEC_CPU

/* enable self test */
#ifdef CFG_HI_TEE_TEST_SUPPORT
#define HI_CIPHER_TEST
#define HI_CIPHER_DEBUG
#endif

/* the hardware version */
#define CHIP_SYMC_VER_V200
#define CHIP_HASH_VER_V200
#define CHIP_TRNG_VER_V200
#define CHIP_IFEP_RSA_VER_V100
#define CHIP_SM2_VER_V100

/* the hardware capacity */
#define CHIP_AES_CCM_GCM_SUPPORT

/* the software capacity */
//#define SOFT_AES_SUPPORT
//#define SOFT_TDES_SUPPORT
//#define SOFT_AES_CCM_GCM_SUPPORT
//#define SOFT_SHA1_SUPPORT
//#define SOFT_SHA256_SUPPORT
//#define SOFT_SHA512_SUPPORT
//#define SOFT_SM2_SUPPORT
//#define SOFT_SM3_SUPPORT
//#define SOFT_ECC_SUPPORT
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
    .reset_valid = 0,  \
    .clk_valid = 0, \
    .phy_valid = 1, \
    .crg_valid = 0, \
    .ver_valid = 0, \
    .int_valid = 0, \
    .int_num = 126, \
    .reg_addr_phy = 0xF9A00000, \
    .reg_addr_size = 0x4000,    \
}

/* define initial value of struct sys_arch_boot_dts for cipher*/
#define HARD_INFO_HASH {\
    .name = "cipher",  \
    .reset_valid = 0,  \
    .clk_valid = 0, \
    .phy_valid = 1, \
    .crg_valid = 0, \
    .ver_valid = 0, \
    .int_valid = 0, \
    .int_num = 126, \
    .reg_addr_phy = 0xF9A00000, \
    .reg_addr_size = 0x4000, \
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
    .reg_addr_phy = 0xF8abc200,  \
    .reg_addr_size = 0x100,   \
}

/* define initial value of struct sys_arch_boot_dts for IFEP RSA*/
#define HARD_INFO_IFEP_RSA {\
    .name = "rsa",  \
    .reset_valid = 1,  \
    .clk_valid = 1, \
    .phy_valid = 1, \
    .crg_valid = 1, \
    .ver_valid = 0, \
    .int_valid = 0, \
    .reg_addr_phy = 0xF9A30000,  \
    .reg_addr_size = 0x1000,\
    .crg_addr_phy = 0xF8A80060, \
    .reset_bit = 15, \
    .clk_bit = 16, \
    .int_num = 79, \
}

/* define initial value of struct sys_arch_boot_dts for SIC RSA*/
#define HARD_INFO_SIC_RSA {\
    .name = "rsa",  \
    .reset_valid = 1,  \
    .clk_valid = 1, \
    .phy_valid = 1, \
    .crg_valid = 1, \
    .ver_valid = 0, \
    .int_valid = 0, \
    .reg_addr_phy = 0xF9A34000,  \
    .reg_addr_size = 0x4000,\
    .crg_addr_phy = 0xF8A80060, \
    .reset_bit = 10, \
    .clk_bit = 13, \
}

/* define initial value of struct sys_arch_boot_dts for SM2 */
#define HARD_INFO_SMMU {\
    .name = "sm2",  \
    .reset_valid = 1,  \
    .clk_valid = 1, \
    .phy_valid = 1, \
    .crg_valid = 1, \
    .ver_valid = 0, \
    .int_valid = 0, \
    .reg_addr_phy = 0xF9A38000,  \
    .reg_addr_size = 0x1000,\
    .crg_addr_phy = 0xF8A80060, \
    .reset_bit = 9, \
    .clk_bit = 12, \
    .int_num = 157, \
}

/* define initial value of struct sys_arch_boot_dts for SM4*/
#define HARD_INFO_SM4 {\
    .name = "SM4",  \
    .reset_valid = 0,  \
    .clk_valid = 1, \
    .phy_valid = 0, \
    .crg_valid = 1, \
    .ver_valid = 0, \
    .int_valid = 0, \
    .crg_addr_phy = 0xF8A208C4, \
    .clk_bit = 8, \
}

/* define initial value of struct sys_arch_boot_dts for SM2 */
#define HARD_INFO_SM2 {\
    .name = "sm2",  \
    .reset_valid = 1,  \
    .clk_valid = 1, \
    .phy_valid = 1, \
    .crg_valid = 1, \
    .ver_valid = 0, \
    .int_valid = 0, \
    .reg_addr_phy = 0xF9A38000,  \
    .reg_addr_size = 0x1000,\
    .crg_addr_phy = 0xF8A80060, \
    .reset_bit = 9, \
    .clk_bit = 12, \
    .int_num = 157, \
}

#define HARD_INFO_CIPHER_KEY          BASE_TABLE_NULL
