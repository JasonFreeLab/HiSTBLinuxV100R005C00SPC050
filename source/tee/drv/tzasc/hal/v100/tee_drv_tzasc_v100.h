#ifndef _TEE_DRV_TZASC_V100_H_
#define _TEE_DRV_TZASC_V100_H_

#define SEC_TZASC_ERR_IRQ                 (110)

/* TZASC */
#define MAX_PORT_NUMS                           7
#define MAX_REGIONS                             16

#define MDDRC_BASE_ADDR                         0xf8a30000
#define MDDRC_BASE_SEC_ADDR                     0xf8a36000
#define MDDRC_PORT_BASE_ADDR(x)             	(MDDRC_BASE_SEC_ADDR + 0x400 * (x))  /* port[6~0]*/

#define SEC_CONFIG_REG                   (0x00)
#define SEC_ACTION_REG                   (0x04)
#define SEC_LOCKDOWN_RANGE_REG           (0x08)
#define SEC_LOCKDOWN_SEL_REG             (0x0C)
#define SEC_INT_STATUS_REG               (0x10)
#define SEC_INT_CLEAR_REG                (0x14)
#define SEC_BYPASS_REG                   (0x18)
#define SEC_FAIL_ADDRESS_LOW_REG         (0x20)
#define SEC_FAIL_ADDRESS_HIGH_REG        (0x24)
#define SEC_FAIL_STATUS_REG              (0x28)
#define SEC_FAIL_ID_REG                  (0x2c)
#define SEC_INVERSION_EN_REG             (0x34)

#define SEC_REGION_SETUP_LOW_REG(x)      (0x100 + 0x10 * (x))
#define SEC_REGION_SETUP_HIGH_REG(x)     (0x104 + 0x10 * (x))
#define SET_REGION_ATTRIBUTES(x)         (0x108 + 0x10 * (x))

#define SEC_MID_EN_REG                   (0x220)
#define SEC_MID_INV_REG                  (0x224)
#define SEC_MID01_ADAPT_REG(x)           (0x240 + 0x10 * (x))
#define SEC_MID23_ADAPT_REG(x)           (0x244 + 0x10 * (x))
#define SEC_MID45_ADAPT_REG(x)           (0x248 + 0x10 * (x))
#define SEC_MID67_ADAPT_REG(x)           (0x24c + 0x10 * (x))

#define SEC_MASTER_TYPE_REG              (0x300)

#define SEC_ITCRG_REG                    (MDDRC_BASE_SEC_ADDR + 0x3c0)
#define SEC_ITIP_REG                     (MDDRC_BASE_SEC_ADDR + 0x3c4)
#define SEC_ITOP_REG                     (MDDRC_BASE_SEC_ADDR + 0x3c8)

/* TZPC */
#define TZPC_BASE_ADDR                          0xf8a80000

#define TZMA_ROSIZE_REG                        	(TZPC_BASE_ADDR + 0x00)
#define TZASC_RST_REG                          	(TZPC_BASE_ADDR + 0x04)
#define TZASC_SEC_LOCK_REG                      (TZPC_BASE_ADDR + 0x08)
#define CPU_DBG_CTRL_REG                        (TZPC_BASE_ADDR + 0x0c)
#define SEC_ATTR_CTRL_0_REG                     (TZPC_BASE_ADDR + 0x10)
#define SEC_ATTR_CTRL_1_REG                     (TZPC_BASE_ADDR + 0x14)
#define SEC_ATTR_CTRL_2_REG                     (TZPC_BASE_ADDR + 0x18)
#define SEC_MISC_CTRL_REG                       (TZPC_BASE_ADDR + 0x1c)
#define SEC_OUTPUT_CTRL_REG                     (TZPC_BASE_ADDR + 0x20)

#define NONE_RIGHT                              0x0
#define NON_SECURE_RIGHT                        0xB
#define SECURE_RIGHT                            0xc
#define FULL_RIGHT                              0xf

#define DDR_SIZE_MIN  (256 * 1024 * 1024)

#define MAX_DDR_LEN                             0x100000000ULL

/* When permission fail, set INT High and resp DECERR */
#define REGION_REACTION_VALUE                   0x3

#define NON_SEC_OS_MEM        0
#define SEC_OS_MEM            1
#define SEC_MMZ_MEM           2
#define NON_SEC_MMZ_MEM       3
#define SEC_MEM_RANGE	4
#define TOTAL_MEM_RANGE        5
#define SEC_OS_CODE_RANGE 6
#define SEC_MEM_VERIFY_RANGE 7

union tzpc_attr_ctrl0_reg
{
	struct {
		unsigned int gpu                    : 1; //[0]
		unsigned int reserved               : 1; //[1]
		unsigned int tde                    : 1; //[2]
		unsigned int reserved1              : 3; //[5:3]
		unsigned int jpgd                   : 1; //[6]
		unsigned int reserved2              : 1; //[7]
		unsigned int pgd                    : 1; //[8]
		unsigned int reserved3              : 1; //[9]
		unsigned int vedu                   : 1; //[10]
		unsigned int reserved4              : 1; //[11]
		unsigned int aiao                   : 1; //[12]
		unsigned int reserved5              : 1; //[13]
		unsigned int pvr                    : 1; //[14]
		unsigned int sha                    : 1; //[15]
		unsigned int reserved6              : 2; //[17:16]
		unsigned int timer_sec              : 1; //[18]
		unsigned int ledc                   : 1; //[19]
		unsigned int reserved7              : 1; //[20]
		unsigned int ir                     : 1; //[21]
		unsigned int reserved8              : 1; //[22]
		unsigned int usb2host               : 1; //[23]
		unsigned int usb2device             : 1; //[24]
		unsigned int dmac                   : 1; //[25]
		unsigned int mcum                   : 1; //[26]
		unsigned int mcus                   : 1; //[27]
		unsigned int ddrt                   : 1; //[28]
		unsigned int usb3                   : 1; //[29]
		unsigned int usb2host1              : 1; //[30]
		unsigned int gpio5                  : 1; //[31]
	}bits;
	unsigned int u32;
};

union tzpc_misc_ctrl_reg {
	struct {
		unsigned int firewall_err_resp      : 1;  //[0]
		unsigned int reserved               : 28; //[28:1]
		unsigned int ddrc_dmc_lock          : 1;  //[29]
		unsigned int ddrc_phy_lock          : 1;  //[30]
		unsigned int ddrc_rbc_lock          : 1;  //[31]
	}bits;
	unsigned int u32;
};

union tzpc_tzasc_sec_lock_reg {
	struct {
		unsigned int sec_boot_lock          : 1;  //[0]
		unsigned int reserved               : 31; //[31:1]
	}bits;
	unsigned int u32;
};

union tzasc_sec_cfg_reg {
	struct {
		unsigned int nr_of_regions          : 5; //[4:0]
		unsigned int reserved1              : 3; //[7:5]
		unsigned int nr_of_mids             : 4; //[11:8]
		unsigned int reserved2              : 4; //[15:12]
		unsigned int addr_width             : 6; //[21:16]
		unsigned int reserved3              : 10; //[31:22]
	}bits;
	unsigned int u32;
};

union tzasc_sec_lockdown_sel_reg {
	struct {
		unsigned int region_register:1;	//[0]
		unsigned int security_inv:1;	//[1]
		unsigned int security_bypass:1;	//[2]
		unsigned int reserved1:1;       //[3]
		unsigned int master_type:1;     //[4]
		unsigned int reserved2:27;	//[31:5]
	} bits;
	unsigned int u32;
};

union tzasc_sec_lockdown_range_reg {
	struct {
		unsigned int lockdown_regions     :4;  //[0:3]
		unsigned int reserved             :27; //[30:4]
		unsigned int lockdown_enable               :1;  //[31]
	} bits;
	unsigned int u32;
};

union tzasc_sec_action_reg {
	struct {
		unsigned int int_enable         : 1;       //[0]
		unsigned int reserved           : 3;       //[1:3]
		unsigned int sta_ckg_apb        : 4;       //[4]
	}bits;
	unsigned int u32;
};

union tzasc_sec_security_inv_reg {
	struct {
		unsigned int sec_inv_en  : 1;  //[0]
		unsigned int reserved               : 31; //[31:1]
	}bits;
	unsigned int u32;
};

union tzasc_sec_int_status_reg {
	struct {
		unsigned int status  : 1;  //[0]
		unsigned int overrun  : 1;  //[1]
		unsigned int reserved : 30; //[31:2]
	}bits;
	unsigned int u32;
};

union tzasc_sec_security_bypass_reg {
	struct {
		unsigned int bypass:1;     //[0]
		unsigned int reserved:31;	 //[31:1]
	} bits;
	unsigned int u32;
};

union tzasc_sec_fail_addr_low_reg {
	unsigned int u32;
};

union tzasc_sec_fail_addr_high_reg {
	unsigned int u32;
};

union tzasc_fail_status_reg
{
	struct
	{
		unsigned int reserved1:20; //[19:0]
		unsigned int fail_privil:1;//[20]
		unsigned int fail_nonsec:1;//[21]
		unsigned int reserved2:2;//[23:22]
		unsigned int fail_acc_type:1;//[24]
		unsigned int reserved3:7; //[31:25]

	}bits;
	unsigned int u32;
};

union tzasc_sec_fail_id_reg {
	unsigned int u32;
};

union tzasc_region_setup_low_reg
{
	struct
	{
		unsigned int reserved               : 15; //[14:0]
		unsigned int base_address_low       : 17; //[31:15]
	}bits;
	unsigned int u32;
};

union tzasc_region_attr_reg
{
	struct
	{
		unsigned int en                     : 1;  //[0]
		unsigned int size                   : 6;  //[6:1]
		unsigned int reserved1              : 1;  //[7]
		unsigned int subregion_disable      : 8;  //[15:8]
		unsigned int reserved2              : 12; //[27:16]
		unsigned int sp                     : 4;  //[31:28]
	}bits;
	unsigned int u32;
};

union tzasc_sec_master_type_reg {
	struct {
		unsigned int master_type:1;  //[0]
		unsigned int reserved:31;    //[31:1]
	}bits;
	unsigned int u32;
};

struct tzascregion {
	int en;
	unsigned int base;
	unsigned long long size;
	unsigned int sp;

};

struct ddr_port {
	unsigned int master_type;
	struct tzascregion *regions;
};
#endif /* _TEE_DRV_TZASC_V100_H_ */
