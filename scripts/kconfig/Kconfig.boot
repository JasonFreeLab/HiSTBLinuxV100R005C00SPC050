#+++++++++++++++++++++++++++++++++++++++++++++++++++
choice
    prompt "Boot Type"
    default HI_UBOOT_SUPPORT

config  HI_UBOOT_SUPPORT
    bool "fastboot"
config  HI_MINIBOOT_SUPPORT
    bool "miniboot"
endchoice

config  HI_BOOT_LOG_SUPPORT
    bool "Boot Log Support"
    default y

menuconfig HI_FORCE_ENV_TO_MEDIA
    bool "Force Envionment variables to Nand/SPI Flash/eMMC"
    default n
    depends on HI_UBOOT_SUPPORT
    help
      This option enables forcing envionment variables to Nand/SPI Flash/eMMC.
      if not enabled, the envionment variables are saved to the boot media, that is to say,
      if the boot is burnt to SPI Flash, the envionment variables are saved to SPI Flash.
      The media for choosing:
        Nand
        SPI Flash
        eMMC

source "scripts/kconfig/Kconfig.env.media"

config HI_BOOT_ENV_STARTADDR
    hex "Environment Variables Partition Start Address"
    default 0x80000
    help
      The start address of the partition you want to save your envioronment variables.
      It should be alined with blocksize for Nand/Spinand/Spinor.

config HI_BOOT_ENV_SIZE
    hex "Environment Variables Image Size"
    default 0x10000
    help
      The size of the Environment Variables Image. Default value is 64k.

config HI_BOOT_ENV_RANGE
    hex "Environment Variables Partition Read/Write Range"
    default HI_BOOT_ENV_SIZE
    help
      This value is useful when there are bad blocks in bootargs partition. It should align
      with blocksize, the minimum value is one block. When boot startup, it will read bootargs
      in (HI_BOOT_ENV_STARTADDR~HI_BOOT_ENV_STARTADDR + HI_BOOT_ENV_RANGE), if there are bad blocks,
      boot will skip bad block. This value is only useful when Nand/Spinand/Spinor.
      Generally, HI_BOOT_ENV_RANGE = BLOCK_ALIGN(HI_BOOT_ENV_SIZE) + badblock num * BLOCKSIZE.

config HI_BOOT_ENV_BAK_SUPPORT
    bool "Bakup Environment support"
    default y
    help
      The bakup Environment support. When read and check Environment failed,
      we should try bakup Environment.

config HI_BOOT_ENV_STARTADDR_BAKUP
    hex "Bakup envioronment Variables Partition Start Address"
    depends on HI_BOOT_ENV_BAK_SUPPORT
    default HI_BOOT_ENV_STARTADDR
    help
      The start address of the partition you want to save your BAKUP envioronment variables.
      When boot startup, it will read bootargs in (HI_BOOT_ENV_STARTADDR_BAKUP~HI_BOOT_ENV_STARTADDR_BAKUP + HI_BOOT_ENV_RANGE),
      if there are bad blocks, boot will skip bad block.

config HI_BOOT_COMPRESSED
    bool "Build Compressed Boot Image"
    default n
    help
      Say y here if you want to build compressed boot image. The compressed
      boot image is smaller.

config HI_BENCH_SUPPORT
    bool "Support HiBench"
    default n
    depends on HI_UBOOT_SUPPORT
    help
      HiBench is a tool which can test your cpu. You can run HiBench with "run" command in boot command line.
      Say y here if you want to run HiBench.

config HI_UNIFIED_BOOT_SUPPORT
    bool "Support Unified Boot"
    default y
    depends on HI3798CV200 || HI3798MV200 || HI3798MV300 || HI3798MV200_A || HI3796MV200 || ((HI3716MV410 || HI3716MV420) && ADVCA_NAGRA )
    help
      Unified boot support one boot.bin run on several different boards with same chiptype.
      Say y here if you want to use unified boot.

config HI_BOOT_USB_SUPPORT
    bool "Support Usb Drivers"
    default n if (HI3716MV410 || HI3716MV420)
    default y if (HI3798MV100 || HI3796MV100 || HI3716DV100 || HI3798CV200 || HI3798MV200 || HI3798MV300 || HI3798MV200_A || HI3796MV200)
    depends on HI_UBOOT_SUPPORT
    help
      Say y here if you want to support usb for boot.

config HI_TWOSTAGEBOOT_SUPPORT
    bool "Support Two Stage Boot"
    default n
    depends on HI_UBOOT_SUPPORT && (HI3716MV410 || HI3716MV420) && ADVCA_CONAX
    help
      Say y here if you want to support sbl.
      Only for HI3716MV410 and HI3716MV420.

config HI_BOOT_CMD
    prompt "BOOT_CMD"
      default "nand read 0x1000000 0x100000 0x100000;go 0x1000000"
    string
      depends on HI_TWOSTAGEBOOT_SUPPORT && (!HI_ADVCA_VERIFY_ENABLE)
    help
      Config the boot_cmd in the bootargs of fbl.
      If be null, will use default boot_cmd "nand read 0x1000000 0x100000 0x100000;go 0x1000000".

config HI_SECONDBOOT_STARTADDR
    hex "Second Boot Start Address"
    default 0x100000
      depends on HI_TWOSTAGEBOOT_SUPPORT && HI_ADVCA_VERIFY_ENABLE
    help
      The start address of the second boot you want to read from flash.

config HI_SECONDBOOT_SIZE
    hex "Second Boot Size"
    default 0x100000
      depends on HI_TWOSTAGEBOOT_SUPPORT && HI_ADVCA_VERIFY_ENABLE
    help
      The size of the second boot.

menu "Build Product Code in Boot"
config HI_BUILD_WITH_PRODUCT
    bool "Build Product Code in Boot"
    default n
    help
      This option enables you to build product directory in boot. Final
      fastboot-burn.bin/miniboot.bin contains product. If you set to n here, product
      will not build with Boot, there will generate another bin file,
      which can be run up by "bootapp (addr)" cmd.

source "scripts/kconfig/Kconfig.bootloader"

menuconfig HI_BUILD_WITH_FRONTEND
    bool "Build Frontend Code in Boot"
    depends on HI_BUILD_WITH_PRODUCT && HI_BOOTLOADER_SUPPORT
    default n

config HI_BOOT_DISEQC_SUPPORT
    depends on HI_BUILD_WITH_FRONTEND
    bool "DISEQC Support"
    default n

menu "Tuner Used in Boot"
    depends on HI_BUILD_WITH_FRONTEND

config  HI_BOOT_TUNER_TYPE_ALPS_TDAE
    depends on HI_BUILD_WITH_FRONTEND
    bool "ALPS_TDAE Support"
    default y

config  HI_BOOT_TUNER_TYPE_TDCC
    depends on HI_BUILD_WITH_FRONTEND
    bool "TDCC Support"
    default y

config  HI_BOOT_TUNER_TYPE_TDA18250
    depends on HI_BUILD_WITH_FRONTEND
    bool "TDA18250 Support"
    default y

config  HI_BOOT_TUNER_TYPE_TDA18250B
    depends on HI_BUILD_WITH_FRONTEND
    bool "TDA18250B Support"
    default y

config  HI_BOOT_TUNER_TYPE_SI2147
    depends on HI_BUILD_WITH_FRONTEND
    bool "SI2147 Support"
    default y

config  HI_BOOT_TUNER_TYPE_TMX7070X
    depends on HI_BUILD_WITH_FRONTEND
    bool "TMX7070X Support"
    default y

config  HI_BOOT_TUNER_TYPE_R820C
    depends on HI_BUILD_WITH_FRONTEND
    bool "R820C Support"
    default y

config  HI_BOOT_TUNER_TYPE_MXL203
    depends on HI_BUILD_WITH_FRONTEND
    bool "MXL203 Support"
    default y

config  HI_BOOT_TUNER_TYPE_AV2011
    depends on HI_BUILD_WITH_FRONTEND
    bool "AV2011 Support"
    default y

config  HI_BOOT_TUNER_TYPE_SHARP7903
    depends on HI_BUILD_WITH_FRONTEND
    bool "SHARP7903 Support"
    default y

config  HI_BOOT_TUNER_TYPE_MXL603
    depends on HI_BUILD_WITH_FRONTEND
    bool "MXL603 Support"
    default y

config  HI_BOOT_TUNER_TYPE_MXL214
    depends on HI_BUILD_WITH_FRONTEND
    bool "MXL214 Support"
    default y

config  HI_BOOT_TUNER_TYPE_MXL254
    depends on HI_BUILD_WITH_FRONTEND
    bool "MXL254 Support"
    default y

config  HI_BOOT_TUNER_TYPE_M88TC3800
    depends on HI_BUILD_WITH_FRONTEND
    bool "M88TC3800 Support"
    default y

endmenu

menu "Demod Used in Boot"
    depends on HI_BUILD_WITH_FRONTEND

config  HI_BOOT_DEMOD_TYPE_HI3130I
    depends on HI_BUILD_WITH_FRONTEND
    bool "HI3130_INSIDE Support"
    default y

config  HI_BOOT_DEMOD_TYPE_HI3136
    depends on HI_BUILD_WITH_FRONTEND
    bool "HI3136 Support"
    default y

config  HI_BOOT_DEMOD_TYPE_MXL214
    depends on HI_BUILD_WITH_FRONTEND
    bool "MXL214 Support"
    default y

config  HI_BOOT_DEMOD_TYPE_MXL254
    depends on HI_BUILD_WITH_FRONTEND
    bool "MXL254 Support"
    default y

endmenu

menu "LNB Chip Used in Boot"
    depends on HI_BUILD_WITH_FRONTEND

config  HI_BOOT_LNB_CTRL_ISL9492
    depends on HI_BUILD_WITH_FRONTEND
    bool "ISL9492 Support"
    default n

config  HI_BOOT_LNB_CTRL_MPS8125
    depends on HI_BUILD_WITH_FRONTEND
    bool "MPS8125 Support"
    default n
endmenu

config  HI_BUILD_WITH_DEMUX
    bool "Build DEMUX in Boot"
    depends on HI_BUILD_WITH_PRODUCT && HI_BOOTLOADER_SUPPORT
    default n

config HI_BUILD_WITH_KEYLED
    bool "Build Keyled in Boot"
    depends on HI_BUILD_WITH_PRODUCT && (HI_KEYLED_74HC164_SUPPORT || HI_KEYLED_CT1642_SUPPORT || HI_KEYLED_PT6961_SUPPORT || HI_KEYLED_PT6964_SUPPORT || HI_KEYLED_FD650_SUPPORT) || HI_KEYLED_GPIOKEY_SUPPORT
    default y

config HI_BUILD_WITH_IR
    bool "Build IR in Boot"
    depends on HI_BUILD_WITH_PRODUCT
    default n

config HI_REMOTE_RECOVERY_SUPPORT
    bool "Remote Recovery Support"
    depends on HI_BUILD_WITH_IR && ANDROID_PRODUCT 
    default n

config HI_GPIO_RECOVERY_SUPPORT
    bool "GPIO Recovery Support"
    depends on ANDROID_PRODUCT
    default y

config HI_IDWORD_LOCK_SUPPORT
    bool "Enable ID word lock Support"
    depends on ANDROID_PRODUCT && (HI3798MV200 || HI3798MV300)
    default n

endmenu

