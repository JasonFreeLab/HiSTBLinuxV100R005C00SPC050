#include "hash.h"
#include "lib.h"
/*-----------------------------------------------------------------
 * otp reg
------------------------------------------------------------------ */

/** Advca CA VendorID */
typedef enum hiUNF_ADVCA_VENDORID_E
{
    HI_UNF_ADVCA_NULL       = 0x00,        /**<No-Advcance CA chipset, Marked with 0*/
    HI_UNF_ADVCA_NAGRA      = 0x01,        /**<NAGRA  Chipse, Marked with R*/
    HI_UNF_ADVCA_IRDETO     = 0x02,        /**<IRDETO Chipset, Marked with I*/
    HI_UNF_ADVCA_CONAX      = 0x03,        /**<CONAX Chipset, Marked with C*/
    HI_UNF_ADVCA_SUMA       = 0x05,        /**<SUMA Chipset, Marked with S*/
    HI_UNF_ADVCA_NOVEL      = 0x06,        /**<NOVEL Chipset, Marked with Y*/
    HI_UNF_ADVCA_VERIMATRIX = 0x07,        /**<VERIMATRIX Chipset, Marked with M*/
    HI_UNF_ADVCA_CTI        = 0x08,        /**<CTI Chipset, Marked with T*/
    HI_UNF_ADVCA_COMMONCA   = 0x0b,        /**<COMMONCA Chipset, Marked with H*/
    HI_UNF_ADVCA_DCAS       = 0x0c,        /**<DCAS CA Chipset*/
    HI_UNF_ADVCA_PANACCESS  = 0x0e,        /**<PANACCESS CA Chipset*/
    HI_UNF_ADVCA_VENDORIDE_BUTT
}HI_UNF_ADVCA_VENDORID_E;

#define MCU_SUSPEND_FLAG             0x80510001
#define SECTION_SYS                  0xF8000000 /* 0xf800_0000 ~ 0xf8ff_ffff,SYSCTRL,PERICTRL, MDDRC, HKL, PERMISSION_CTRL, UART1 */
#define DDR_SELF_REFRESH            (0xf8a31000)

#define REG_SC_BASE                 (SECTION_SYS)
#define CA_REG_BASE                 (SECTION_SYS + 0xAB0000) /* CA: 0xf8AB_0000 */
#define PERMISSSION_CTRL_REG_BASE   (CA_REG_BASE) /* PERMISSION_CTRL: 0xf8AB_0000*/

#define REG_CHECK_AREA_NUM          (REG_SC_BASE + 0x0FB0)
#define REG_START_ADDR(i)           (REG_SC_BASE + 0x0FB4 + (i) * 8)
#define REG_SIZE(i)                 (REG_SC_BASE + 0x0FB8 + (i) * 8)
#define REG_HASH_VALUE              (REG_SC_BASE + 0x0FD4)
#define REG_DDR_WAKEUP_FLAG         (REG_SC_BASE + 0x0FF8)
#define REG_UART_PRINT_OUT          (REG_SC_BASE + 0xB00000)

#define REG_DDR_WAKEUP_DISABLE      (CA_REG_BASE)
#define REG_VENDOR_ID               (CA_REG_BASE + 0xF0)


#define ADDR_SHA_KEY_SEL            (PERMISSSION_CTRL_REG_BASE + 0x4114)

#define REG_STANDBY	                (SECTION_SYS + 0x00BC) //This register is set to standby.


#ifndef HI_ADVCA_FUNCTION_RELEASE
#define printChar(a) \
    do{\
        int i;  \
        i = 0;  \
        while(i++ < 0x1fff); \
        reg_set(REG_UART_PRINT_OUT, a);\
    }while (0)

#else
#define printChar(a) 
#endif


static void calc_ddr_address(void)
{
    reg_set(REG_CHECK_AREA_NUM, 1);
    reg_set(REG_START_ADDR(0), 0x0);
    reg_set(REG_SIZE(0), 0x500000);

    return;    
}

static void write_hash_to_reg(unsigned char *hashValue, unsigned int regAddr)
{
    int i;
    for (i = 0; i < 8; i++)
    {
        reg_set((regAddr + (0x4 * i)), (*(unsigned int *)(hashValue + (0x4 * i))));
    }

    return;
}

        
static int nagra_calc_hmachash256(unsigned char *decrypt_sha2)
{
    int i;    
    int block_num = 0;
    unsigned int pad_size = 0;
    unsigned int length = 0;
    SHA_KEY_SEL_U un_sha_key_sel;

    block_num = reg_get(REG_CHECK_AREA_NUM);
    if ((block_num == 0) || (block_num >= 5))
    {
        return -1;
    }
    for ( i = 0 ; i < block_num ; i++ )
    {
        if (reg_get(REG_SIZE(i)) == 0)
        {
            return -1;
        }
        else
        {
            length += reg_get(REG_SIZE(i));
        }
    }

    un_sha_key_sel.u32 = reg_get(ADDR_SHA_KEY_SEL);
    un_sha_key_sel.bits.sha_hw_key_sel = 1;         //Use NONCE as HASH key
    reg_set(ADDR_SHA_KEY_SEL, un_sha_key_sel.u32);
    printChar(0x61);

    hash_cfg_len(MOD_HMAC_HASH256, &length, &pad_size);
    
    for(i = 0; i < block_num; i++)
    {
        if(0 == reg_get(REG_SIZE(i)))
        {
            continue;
        }
        hash_cfg_dma((u8 *)reg_get(REG_START_ADDR(i)), reg_get(REG_SIZE(i)));
    }
    hash_cfg_pad(length, pad_size);

    hash_get_result(MOD_HMAC_HASH256, decrypt_sha2);
    printChar(0x62);

    un_sha_key_sel.u32 = reg_get(ADDR_SHA_KEY_SEL);
    un_sha_key_sel.bits.sha_hw_key_sel = 0;         //Change HASH key back to STB rootkey

    reg_set(ADDR_SHA_KEY_SEL, un_sha_key_sel.u32);
 
    return 0;
}

void nagra_write_hmac_to_lpds(void)
{
    int ret = 0;
    unsigned char result[32];

    ret = nagra_calc_hmachash256(result);
    if (0 != ret)
    {
        return;
    }

        
    write_hash_to_reg(result, REG_HASH_VALUE);
    return;
}

void nagra_setDDRtoSelfRefreshMode(void)
{  
    unsigned int value = 0;

    /* Config DDR to self-refresh state */
    value = reg_get(DDR_SELF_REFRESH);

    value = value | 0x1;
    reg_set(DDR_SELF_REFRESH, value);

    /* Whether DDR change to self-refresh state */   
    while(1)
    {
        if ((reg_get(0xf8a31294) & 0x1) == 1)
        {
            break;
        }
    }

    value = 0;
    value = reg_get(0xf8a38078);
    value = value & 0xFFFFE87F;

    reg_set(0xf8a38078, value);
    
    /* enable DDRPHY ISO */
    value = 0;
    value = reg_get(0xf8000058);
    value = value & 0xfc;
    value = value | 0x02;

    reg_set(0xf8000058, value);

    return;
}


int nagra_ddr_wakeup_check()
{
    unsigned int checkAreaNum = 0;
    unsigned int u32Value;
    unsigned int ddr_wakeup_disable;


    u32Value = reg_get(REG_DDR_WAKEUP_DISABLE);
    ddr_wakeup_disable = (u32Value >> 16) & 0x1;

    checkAreaNum = reg_get(REG_CHECK_AREA_NUM);

    if (0)//((ddr_wakeup_disable == 1) || (checkAreaNum == 0))
    {
        printChar(0x62);//output message to UART1:b
        reg_set(REG_DDR_WAKEUP_FLAG, 0x0);
    }
    else
    {
        //printChar(0x63);//output message to UART1:c
        nagra_write_hmac_to_lpds();
        reg_set(REG_DDR_WAKEUP_FLAG, 0x66031013);
        nagra_setDDRtoSelfRefreshMode(); 
    }

    //printChar(0x64);//output message to UART1:d

    return 0;
}


int main(void)
{
    unsigned int u32Value;
    HI_UNF_ADVCA_VENDORID_E eVendorId = HI_UNF_ADVCA_NULL;

    //printChar(0x61); //print a

    u32Value = reg_get(REG_VENDOR_ID);
	eVendorId = u32Value & 0xFF;

    //calc_ddr_address();
    //if(HI_UNF_ADVCA_NAGRA == eVendorId)
    //{
        nagra_ddr_wakeup_check();
    //}
    //else
    //{
    //	ddr_wakeup_check();
    //}

    //notify c51
    reg_set(REG_STANDBY, MCU_SUSPEND_FLAG);

    while(1);

    return 0;
}

