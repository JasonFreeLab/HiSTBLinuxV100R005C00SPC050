

/*
 *  SDK Version
 * 
 */
#define SDK_VERSION_STRING	"HiSTBLinuxV100R005"


/*
 *  nand flash support
 * 
 */
#define CONFIG_NAND_SUPPORT	y


/*
 *  spi-nand flash support
 *  #define CONFIG_SPI_NAND_SUPPORT
 */


/*
 *  spi flash support
 * 
 */
#define CONFIG_SPIFLASH_SUPPORT	y


/*
 *  eth support
 * 
 */
#define CONFIG_NET_SUPPORT	y


/*
 *  eth upport phy address
 *  #define HISFV_PHY_U
 */


/*
 *  eth downport phy address
 *  #define HISFV_PHY_D
 */


/*
 *  emmc flash support
 *  #define CONFIG_EMMC_SUPPORT
 */
#define CONFIG_EMMC_SUPPORT	y


/*
 *  boot environment variables start address
 * 
 */
#define CFG_ENV_ADDR	0x100000


/*
 *  boot environment variables size
 * 
 */
#define CFG_ENV_SIZE	0x10000


/*
 *  boot environment variables range
 * 
 */
#define CFG_ENV_RANGE	0x20000


/*
 *  Bakup boot environment variables support
 *  #define CONFIG_ENV_BACKUP
 */


/*
 *  Bakup boot environment variables start address
 *  #define CFG_ENV_BACKUP_ADDR
 */


/*
 *  build product with boot
 *  #define CONFIG_PRODUCT_WITH_BOOT
 */


/*
 *  build for umap5 fpga version
 *  #define CONFIG_HI3798MV2X_UMAP5
 */


/*
 *  build auximg from auxcode
 *  #define CONFIG_AUXCODE_COMPILE_SUPPORT
 */


/*
 *  build higmacv300
 *  #define CONFIG_NET_HIGMACV300
 */


/*
 *  build hisfv300
 *  #define CONFIG_NET_HISFV300
 */


/*
 *  build usb2eth
 *  #define CONFIG_USB_HOST_ETHER
 */


/*
 *  FPGA
 * 
 */
#define CFG_HI3716MV420N_FPGA	0


/*
 *  Simulate boot
 *  #define CONFIG_BOOT_SIMULATE
 */


/*
 *  Chip type
 * 
 */
#define CHIP_TYPE_hi3716mv420n	1


/*
 *  AVS config
 *  #define CONFIG_AVS_SUPPORT
 */


/*
 *  PMU Device config
 *  #define CONFIG_PMU_DEVICE
 */


/*
 *  USB Driver config
 *  #define CONFIG_USB_SUPPORT
 */


/*
 *  TEE config
 *  #define CONFIG_TEE_SUPPORT
 */


/*
 *  TEE Memory Layout config
 * 
 */
#define CONFIG_TEE_MEM_LAYOUT_	y


/*
 *  ARM64 toolchains config
 * 
 */
#define CONFIG_ARM64_TOOLCHAINS	arm-histbv310-linux


/*
 *  ARM64 support config
 *  #define CONFIG_ARM64_SUPPORT
 */


/*
 *  Disable console input
 *  #define CONFIG_DISABLE_CONSOLE_INPUT
 */


/*
 *  Unified boot
 * 
 */
#define CONFIG_UNIFIED_BOOT	y


/*
 *  default boot reg
 * 
 */
#define CONFIG_BOOTREG_DEFAULT	"/home/lhui/svn/git/Code/out/hi3716mv420n/hi3716m421tst/obj/source/boot/fastboot/hi3716m42tst_hi3716mv420b03_ddr3_1gbyte_8bit8x_4layers.reg"


/*
 *  boot reg0
 * 
 */
#define BOOT_REG0	"/home/lhui/svn/git/Code/out/hi3716mv421/hi3716m421tst/obj/source/boot/fastboot/hi3716m42tst_hi3716mv420b03_ddr3_1gbyte_8bit8x_4layers.reg"


/*
 *  boot reg1
 *  #define BOOT_REG1
 */


/*
 *  boot reg2
 *  #define BOOT_REG2
 */


/*
 *  boot reg3
 *  #define BOOT_REG3
 */


/*
 *  boot reg4
 *  #define BOOT_REG4
 */


/*
 *  boot reg5
 *  #define BOOT_REG5
 */


/*
 *  boot reg6
 *  #define BOOT_REG6
 */


/*
 *  boot reg7
 *  #define BOOT_REG7
 */
