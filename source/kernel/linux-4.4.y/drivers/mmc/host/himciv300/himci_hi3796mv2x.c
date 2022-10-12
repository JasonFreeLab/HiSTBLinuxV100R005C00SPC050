
//#define TUNING_PROC_DEBUG

/*HS400 clock config*/
#define HS400_CLK_100M  100000000
#define HS400_CLK_150M  150000000
#define HS400_MAX_CLK  HS400_CLK_100M

/*HS200 clock config*/
#define HS200_CLK_150M  150000000
#define HS200_CLK_187M  187000000
#define HS200_MAX_CLK  HS200_CLK_150M

#define SDR104_CLK_150M  150000000
#define SDR104_CLK_187M  187000000

/* Phase details */
#define SDIO_DRV_PS_MASK                   (0xf << 15)
#define SDIO_SAP_PS_MASK                   (0xf << 11)
#define SDIO_SAP_PS_SHIFT_BIT              (11)
#define SDIO_SAP_PS_NUM                    (16)
#define SDIO_SAP_PS_OFFSET                 (11)

#define SDIO_DRV_PS_0              (0b0000 << 15)
#define SDIO_DRV_PS_45             (0b0010 << 15)
#define SDIO_DRV_PS_90             (0b0100 << 15)
#define SDIO_DRV_PS_135            (0b0110 << 15)
#define SDIO_DRV_PS_180            (0b1000 << 15)
#define SDIO_DRV_PS_225            (0b1010 << 15)
#define SDIO_DRV_PS_270            (0b1100 << 15)
#define SDIO_DRV_PS_315            (0b1110 << 15)
#define SDIO_DRV_PS_22DOT5         (0b0001 << 15)
#define SDIO_DRV_PS_67DOT5         (0b0011 << 15)
#define SDIO_DRV_PS_112DOT5        (0b0101 << 15)
#define SDIO_DRV_PS_157DOT5        (0b0111 << 15)
#define SDIO_DRV_PS_202DOT5        (0b1001 << 15)
#define SDIO_DRV_PS_247DOT5        (0b1011 << 15)
#define SDIO_DRV_PS_292DOT5        (0b1101 << 15)
#define SDIO_DRV_PS_337DOT5        (0b1111 << 15)

#define SDIO_SAP_PS_0              (0b0000 << 11)
#define SDIO_SAP_PS_45             (0b0010 << 11)
#define SDIO_SAP_PS_90             (0b0100 << 11)
#define SDIO_SAP_PS_135            (0b0110 << 11)
#define SDIO_SAP_PS_180            (0b1000 << 11)
#define SDIO_SAP_PS_225            (0b1010 << 11)
#define SDIO_SAP_PS_270            (0b1100 << 11)
#define SDIO_SAP_PS_315            (0b1110 << 11)
#define SDIO_SAP_PS_22DOT5         (0b0001 << 11)
#define SDIO_SAP_PS_67DOT5         (0b0011 << 11)
#define SDIO_SAP_PS_112DOT5        (0b0101 << 11)
#define SDIO_SAP_PS_157DOT5        (0b0111 << 11)
#define SDIO_SAP_PS_202DOT5        (0b1001 << 11)
#define SDIO_SAP_PS_247DOT5        (0b1011 << 11)
#define SDIO_SAP_PS_292DOT5        (0b1101 << 11)
#define SDIO_SAP_PS_337DOT5        (0b1111 << 11)

#define DRV_IOCTRL_PD                       BIT(13)
#define DRV_IOCTRL_PU                       BIT(12)

/* Driver caps details */
#define DRV_CAPS_MASK                       (0xf << 4)
#define DRV_SLEV_RATE                       BIT(8)

#define EMMC_DRV_CAP_HS_CMD_DATA          (0b1110 << 4)
#define EMMC_DRV_CAP_HS_CLOCK             (0b1101 << 4)
#define EMMC_DRV_SR_HS_CMD_DATA            DRV_SLEV_RATE
#define EMMC_DRV_SR_HS_CLOCK               DRV_SLEV_RATE

#define EMMC_DRV_CAP_DDR50_CMD_DATA       (0b1110 << 4)
#define EMMC_DRV_CAP_DDR50_CLOCK          (0b1101 << 4)
#define EMMC_DRV_SR_DDR50_CMD_DATA         DRV_SLEV_RATE
#define EMMC_DRV_SR_DDR50_CLOCK            DRV_SLEV_RATE

#if (HS400_MAX_CLK == HS400_CLK_150M)
/*HS400 IO drv config as 150Mhz*/
#define EMMC_DRV_CAP_HS400_CMD_DATA  (0b1011 << 4)
#define EMMC_DRV_CAP_HS400_CLOCK     (0b1011 << 4)
#define EMMC_DRV_SR_HS400_CMD_DATA    0
#define EMMC_DRV_SR_HS400_CLOCK       0
#elif (HS400_MAX_CLK == HS400_CLK_100M)
/*HS400 IO drv config as 100Mhz*/
#define EMMC_DRV_CAP_HS400_CMD_DATA  (0b1010 << 4)
#define EMMC_DRV_CAP_HS400_CLOCK     (0b1010 << 4)
#define EMMC_DRV_SR_HS400_CMD_DATA    DRV_SLEV_RATE
#define EMMC_DRV_SR_HS400_CLOCK       DRV_SLEV_RATE
#endif

#if (HS200_MAX_CLK == HS200_CLK_187M)
/*HS200 IO drv config as 200Mhz*/
#define EMMC_DRV_CAP_HS200_CMD_DATA  (0b1011 << 4)
#define EMMC_DRV_CAP_HS200_CLOCK     (0b0011 << 4)
#define EMMC_DRV_SR_HS200_CMD_DATA    DRV_SLEV_RATE
#define EMMC_DRV_SR_HS200_CLOCK       0
#elif (HS200_MAX_CLK == HS200_CLK_150M)
/*HS200 IO drv config as 150Mhz*/
#define EMMC_DRV_CAP_HS200_CMD_DATA  (0b1011 << 4)
#define EMMC_DRV_CAP_HS200_CLOCK     (0b1011 << 4)
#define EMMC_DRV_SR_HS200_CMD_DATA    DRV_SLEV_RATE
#define EMMC_DRV_SR_HS200_CLOCK       0
#endif

#define SDIO_DRV_CAP_3V3_50M_CMD_DATA   (0b011 << 4)
#define SDIO_DRV_CAP_3V3_50M_CLOCK      (0b1101 << 4)
#define SDIO_DRV_SR_3V3_50M_CMD_DATA    DRV_SLEV_RATE
#define SDIO_DRV_SR_3V3_50M_CLOCK       DRV_SLEV_RATE

#define SDIO_DRV_CAP_1V8_50M_CMD_DATA   (0b011 << 4)
#define SDIO_DRV_CAP_1V8_50M_CLOCK      (0b1101 << 4)
#define SDIO_DRV_SR_1V8_50M_CMD_DATA    DRV_SLEV_RATE
#define SDIO_DRV_SR_1V8_50M_CLOCK       DRV_SLEV_RATE

#define SDIO_DRV_CAP_1V8_100M_CMD_DATA  (0b011 << 4)
#define SDIO_DRV_CAP_1V8_100M_CLOCK     (0b0011 << 4)
#define SDIO_DRV_SR_1V8_100M_CMD_DATA   DRV_SLEV_RATE
#define SDIO_DRV_SR_1V8_100M_CLOCK      0

#define SDIO_DRV_CAP_1V8_200M_CMD_DATA  (0b011 << 4)
#define SDIO_DRV_CAP_1V8_200M_CLOCK     (0b0000 << 4)
#define SDIO_DRV_SR_1V8_200M_CMD_DATA   0
#define SDIO_DRV_SR_1V8_200M_CLOCK      0

#define IOSHARE_OFFSET_EMMC_CLOCK  0x048
#define IOSHARE_OFFSET_EMMC_CMD    0x050
#define IOSHARE_OFFSET_EMMC_DATA0  0x030
#define IOSHARE_OFFSET_EMMC_DATA1  0x038
#define IOSHARE_OFFSET_EMMC_DATA2  0x040
#define IOSHARE_OFFSET_EMMC_DATA3  0x028
#define IOSHARE_OFFSET_EMMC_DATA4  0x02c
#define IOSHARE_OFFSET_EMMC_DATA5  0x034
#define IOSHARE_OFFSET_EMMC_DATA6  0x03c
#define IOSHARE_OFFSET_EMMC_DATA7  0x044
#define IOSHARE_OFFSET_EMMC_DATA_STROBE  0x058

//sdio0 io-share reg = 0xf8a21190 ~~ 0x20
#define IOSHARE_OFFSET_SDIO0_CLOCK  0x00C
#define IOSHARE_OFFSET_SDIO0_CMD    0x010
#define IOSHARE_OFFSET_SDIO0_DATA0  0x008
#define IOSHARE_OFFSET_SDIO0_DATA1  0x004
#define IOSHARE_OFFSET_SDIO0_DATA2  0x018
#define IOSHARE_OFFSET_SDIO0_DATA3  0x014

//sdio1 io-share reg = 0xf8a210c0 ~~ 0x20
#define IOSHARE_OFFSET_SDIO1_CLOCK  0x00C
#define IOSHARE_OFFSET_SDIO1_CMD    0x010
#define IOSHARE_OFFSET_SDIO1_DATA0  0x008
#define IOSHARE_OFFSET_SDIO1_DATA1  0x004
#define IOSHARE_OFFSET_SDIO1_DATA2  0x018
#define IOSHARE_OFFSET_SDIO1_DATA3  0x014

#define EMMC_IO_VOLTAGE_MASK               (0x01)
#define EMMC_IO_VOL_1_8V                   (0x01)
#define EMMC_IO_VOL_3_3V                   (0x00)

#ifndef REG_BASE_SCTL
#define REG_BASE_SCTL                      (0xF8000000)
#endif

#ifndef REG_SC_GEN29
#define REG_SC_GEN29                        0x00F4
#endif

#define HIMCI_DLL_TUNING
#ifdef HIMCI_DLL_TUNING
#define REG_BASE_CRG	0xF8A22000
#define REG_EMMC_SAP_DLL_CTRL			(REG_BASE_CRG + 0x039C)
#define REG_EMMC_SAP_DLL_STATUS			(REG_BASE_CRG + 0x03A0)
#define REG_SDIO0_SAP_DLL_CTRL			(REG_BASE_CRG + 0x03A4)
#define REG_SDIO0_SAP_DLL_STATUS		(REG_BASE_CRG + 0x03A8)
#define REG_SDIO1_SAP_DLL_CTRL			(REG_BASE_CRG + 0x03AC)
#define REG_SDIO1_SAP_DLL_STATUS		(REG_BASE_CRG + 0x03B0)

#define SAP_DLL_CTRL_SLAVE_EN		BIT(19)
#define SAP_DLL_CTRL_STOP			BIT(18)
#define SAP_DLL_CTRL_BYPASS			BIT(17)
#define SAP_DLL_CTRL_DLLMODE		BIT(16)
#define SAP_DLL_CTRL_DLLSSEL		(0xFF << 8)
#define SAP_DLL_CTRL_DLLSSEL_OFFSET 8

#define SAP_DLL_MDLY_TAP_FLAG		(0xFF)

#define SAP_TUNING_CLKAB_INTERVAL_90   	4

#define MCI_TUNING_CONTROL				0x118
#define MCI_TUNING_FIND_EDGE			BIT(5)
#define MCI_TUNING_DATA_SEL				(0x07 << 2)
#define MCI_TUNING_EDGE_CONTROL			BIT(1)
#define MCI_TUNING_ENABLE_NEW_TUNING	BIT(0)
#define MCI_TUNING_DATA_SEL_OFFSET		(2)

//#define MCI_TUNING_TEST

#ifdef CONFIG_ARM64
#define IOMEM(x)	((void __force __iomem *)(x))
#endif

#define himci_readl(addr) ({unsigned int reg = readl(IOMEM(addr)); \
	himci_trace(1, "readl(0x%04X) = 0x%08X", (unsigned int)addr, reg); \
	reg; })

#define himci_writel(v, addr) do { writel(v, IOMEM(addr)); \
	himci_trace(1, "writel(0x%04X) = 0x%08X", (unsigned int)addr, \
			(unsigned int)(v)); \
} while (0)

static const char himci_mmc_name[]= {"f9830000.himciv200.MMC"};
static const char himci_sdio0_name[]= {"f9820000.himciv200.SD"};
static const char himci_sdio1_name[]= {"f9c40000.himciv200.SD"};

static int himciv300_send_status(struct mmc_host *mmc)
{
	int err;
	struct mmc_command cmd = {0};
	struct himciv300_host *host;

	BUG_ON(!mmc);

	host = mmc_priv(mmc);
	cmd.opcode = MMC_SEND_STATUS;
	if (!mmc_host_is_spi(mmc))
		cmd.arg = (host->card_rca << 16);
	cmd.flags = MMC_RSP_SPI_R2 | MMC_RSP_R1 | MMC_CMD_AC;

	err = mmc_wait_for_cmd(mmc, &cmd, 1);
	if (err)
		return err;

	return 0;
}

static int himciv300_send_tuning(struct mmc_host * mmc, u32 opcode)
{
	int err = 0;
	struct himciv300_host *host;

	host = mmc_priv(mmc);
	himciv300_idma_reset(host);

	switch(opcode) {
		case MMC_SEND_EXT_CSD:
			//err = mmc_send_hs_ddr_tuning(mmc);
			break;

		case MMC_SWITCH:
			//err = mmc_sd_send_tuning(mmc);
			break;

		case MMC_SEND_TUNING_BLOCK:
		case MMC_SEND_TUNING_BLOCK_HS200:
			err = mmc_send_tuning(mmc, opcode, NULL);
			break;

		default :
			err = -1;
			break;
	}
	himciv300_send_status(mmc);
	return err;
}

static u32 himciv300_get_tuning_phase_num(struct himciv300_host *host)
{
	struct mmc_host  *mmc = host->mmc;
	u8 timing = mmc->ios.timing;
	u32 phase_num = SDIO_SAP_PS_NUM;

	if (strncmp(dev_name(host->dev), himci_mmc_name, sizeof(himci_mmc_name)) == 0) {
		if (timing == MMC_TIMING_MMC_DDR52) {
			phase_num /= 2;
		}
	} else if ((strncmp(dev_name(host->dev), himci_sdio0_name, sizeof(himci_sdio0_name)) == 0)||
			  (strncmp(dev_name(host->dev), himci_sdio1_name, sizeof(himci_sdio1_name)) == 0)) {
		if (timing == MMC_TIMING_UHS_DDR50) {
			phase_num /= 2;
		}
	}
	return phase_num;
}


static void himciv300_edge_tuning_enable(struct himciv300_host *host)
{
	u32 regval;
	void __iomem *reg_sap_dll_ctrl;

	if (strncmp(dev_name(host->dev), himci_mmc_name, sizeof(himci_mmc_name)) == 0) {
		reg_sap_dll_ctrl = ioremap_nocache(REG_EMMC_SAP_DLL_CTRL, sizeof(u32));
		if (!reg_sap_dll_ctrl) {
			printk("%s %s iomap fail\n",__func__,dev_name(host->dev));
			return;
		}
		regval = himci_readl(reg_sap_dll_ctrl);
		regval &=~SAP_DLL_CTRL_DLLMODE;
		himci_writel(regval, reg_sap_dll_ctrl);
		iounmap(reg_sap_dll_ctrl);
	} else if (strncmp(dev_name(host->dev), himci_sdio0_name, sizeof(himci_sdio0_name)) == 0) {
		reg_sap_dll_ctrl = ioremap_nocache(REG_SDIO0_SAP_DLL_CTRL, sizeof(u32));
		if (!reg_sap_dll_ctrl) {
			printk("%s %s iomap fail\n",__func__,dev_name(host->dev));
			return;
		}
		regval = himci_readl(reg_sap_dll_ctrl);
		regval &=~SAP_DLL_CTRL_DLLMODE;
		himci_writel(regval, reg_sap_dll_ctrl);
		iounmap(reg_sap_dll_ctrl);
	} else if (strncmp(dev_name(host->dev), himci_sdio1_name, sizeof(himci_sdio1_name)) == 0) {
		reg_sap_dll_ctrl = ioremap_nocache(REG_SDIO1_SAP_DLL_CTRL, sizeof(u32));
		if (!reg_sap_dll_ctrl) {
			printk("%s %s iomap fail\n",__func__,dev_name(host->dev));
			return;
		}
		regval = himci_readl(reg_sap_dll_ctrl);
		regval &=~SAP_DLL_CTRL_DLLMODE;
		himci_writel(regval, reg_sap_dll_ctrl);
		iounmap(reg_sap_dll_ctrl);
	}

	regval = mci_readl(host, MCI_TUNING_CONTROL);
	regval |= MCI_TUNING_ENABLE_NEW_TUNING;
	mci_writel(host, MCI_TUNING_CONTROL, regval);
}

static void himciv300_edge_tuning_disable(struct himciv300_host *host)
{
	u32 regval;
	void __iomem *reg_sap_dll_ctrl;

	if (strncmp(dev_name(host->dev), himci_mmc_name, sizeof(himci_mmc_name)) == 0) {
		reg_sap_dll_ctrl = ioremap_nocache(REG_EMMC_SAP_DLL_CTRL, sizeof(u32));
		if (!reg_sap_dll_ctrl) {
			printk("%s %s iomap fail\n",__func__,dev_name(host->dev));
			return;
		}
		regval = himci_readl(reg_sap_dll_ctrl);
		regval |= SAP_DLL_CTRL_DLLMODE;
		himci_writel(regval, reg_sap_dll_ctrl);
		iounmap(reg_sap_dll_ctrl);
	} else if (strncmp(dev_name(host->dev), himci_sdio0_name, sizeof(himci_sdio0_name)) == 0) {
		reg_sap_dll_ctrl = ioremap_nocache(REG_SDIO0_SAP_DLL_CTRL, sizeof(u32));
		regval = himci_readl(reg_sap_dll_ctrl);
		if (!reg_sap_dll_ctrl) {
			printk("%s %s iomap fail\n",__func__,dev_name(host->dev));
			return;
		}
		regval |= SAP_DLL_CTRL_DLLMODE;
		himci_writel(regval, reg_sap_dll_ctrl);
		iounmap(reg_sap_dll_ctrl);
	} else if (strncmp(dev_name(host->dev), himci_sdio1_name, sizeof(himci_sdio1_name)) == 0) {
		reg_sap_dll_ctrl = ioremap_nocache(REG_SDIO1_SAP_DLL_CTRL, sizeof(u32));
		if (!reg_sap_dll_ctrl) {
			printk("%s %s iomap fail\n",__func__,dev_name(host->dev));
			return;
		}
		regval = himci_readl(reg_sap_dll_ctrl);
		regval |= SAP_DLL_CTRL_DLLMODE;
		himci_writel(regval, reg_sap_dll_ctrl);
		iounmap(reg_sap_dll_ctrl);
	}

	regval = mci_readl(host, MCI_TUNING_CONTROL);
	regval &= ~MCI_TUNING_ENABLE_NEW_TUNING;
	mci_writel(host, MCI_TUNING_CONTROL, regval);
}


static void himciv300_set_sap_phase(struct himciv300_host *host, u32 phase)
{
	u32 regval;

	regval = (u32)clk_get_phase(host->clk);
	regval = regval << SDIO_SAP_PS_SHIFT_BIT;
	regval &= ~SDIO_SAP_PS_MASK;
	regval |= (phase << SDIO_SAP_PS_OFFSET);
	/* clk_set_phase has  regval%360, so shifit 12bit */
	regval = regval >> SDIO_SAP_PS_SHIFT_BIT;
	clk_set_phase(host->clk, (int)regval);
}

static void himciv300_set_dll_element(struct himciv300_host *host, u32 element)
{
	u32 regval;
	void __iomem *reg_sap_dll_ctrl;

	if (strncmp(dev_name(host->dev), himci_mmc_name, sizeof(himci_mmc_name)) == 0) {
		reg_sap_dll_ctrl = ioremap_nocache(REG_EMMC_SAP_DLL_CTRL, sizeof(u32));
		if (!reg_sap_dll_ctrl) {
			printk("%s %s iomap fail\n",__func__,dev_name(host->dev));
			return;
		}
		regval = himci_readl(reg_sap_dll_ctrl);
		regval &=~SAP_DLL_CTRL_DLLSSEL;
		regval |= (element << SAP_DLL_CTRL_DLLSSEL_OFFSET);
		himci_writel(regval, reg_sap_dll_ctrl);
		iounmap(reg_sap_dll_ctrl);
	} else if (strncmp(dev_name(host->dev), himci_sdio0_name, sizeof(himci_sdio0_name)) == 0) {
		reg_sap_dll_ctrl = ioremap_nocache(REG_SDIO0_SAP_DLL_CTRL, sizeof(u32));
		if (!reg_sap_dll_ctrl) {
			printk("%s %s iomap fail\n",__func__,dev_name(host->dev));
			return;
		}
		regval = himci_readl(reg_sap_dll_ctrl);
		regval &=~SAP_DLL_CTRL_DLLSSEL;
		regval |= (element << SAP_DLL_CTRL_DLLSSEL_OFFSET);
		himci_writel(regval, reg_sap_dll_ctrl);
		iounmap(reg_sap_dll_ctrl);
	} else if (strncmp(dev_name(host->dev), himci_sdio1_name, sizeof(himci_sdio1_name)) == 0) {
		reg_sap_dll_ctrl = ioremap_nocache(REG_SDIO1_SAP_DLL_CTRL, sizeof(u32));
		if (!reg_sap_dll_ctrl) {
			printk("%s %s iomap fail\n",__func__,dev_name(host->dev));
			return;
		}
		regval = himci_readl(reg_sap_dll_ctrl);
		regval &=~SAP_DLL_CTRL_DLLSSEL;
		regval |= (element << SAP_DLL_CTRL_DLLSSEL_OFFSET);
		himci_writel(regval, reg_sap_dll_ctrl);
		iounmap(reg_sap_dll_ctrl);
	}
}

static u32 himciv300_get_sap_dll_taps(struct himciv300_host *host)
{
	u32 regval = 0;
	void __iomem *reg_sap_dll_status;

	if (strncmp(dev_name(host->dev), himci_mmc_name, sizeof(himci_mmc_name)) == 0) {
		reg_sap_dll_status = ioremap_nocache(REG_EMMC_SAP_DLL_STATUS, sizeof(u32));
		if (!reg_sap_dll_status) {
			printk("%s %s iomap fail\n",__func__,dev_name(host->dev));
			return 0;
		}
		regval = himci_readl(reg_sap_dll_status);
		iounmap(reg_sap_dll_status);
	} else if (strncmp(dev_name(host->dev), himci_sdio0_name, sizeof(himci_sdio0_name)) == 0) {
		reg_sap_dll_status = ioremap_nocache(REG_SDIO0_SAP_DLL_STATUS, sizeof(u32));
		if (!reg_sap_dll_status) {
			printk("%s %s iomap fail\n",__func__,dev_name(host->dev));
			return 0;
		}
		regval = himci_readl(reg_sap_dll_status);
		iounmap(reg_sap_dll_status);
	} else if (strncmp(dev_name(host->dev), himci_sdio1_name, sizeof(himci_sdio1_name)) == 0) {
		reg_sap_dll_status = ioremap_nocache(REG_SDIO1_SAP_DLL_STATUS, sizeof(u32));
		if (!reg_sap_dll_status) {
			printk("%s %s iomap fail\n",__func__,dev_name(host->dev));
			return 0;
		}
		regval = himci_readl(reg_sap_dll_status);
		iounmap(reg_sap_dll_status);
	}

	return (regval & SAP_DLL_MDLY_TAP_FLAG);
}

static void himciv300_tuning_feedback(struct mmc_host * mmc)
{
	struct himciv300_host *host = mmc_priv(mmc);

	himciv300_control_cclk(host, false);
	msleep(1);
	himciv300_host_reset(host);
	msleep(1);
	mci_writel(host, MCI_RINTSTS, ALL_INT_CLR);
	himciv300_control_cclk(host, true);
	msleep(1);
	host->pending_events = 0;
}

/********************************************
*********************************************
EdgeMode A:
   |<---- totalphases(ele) ---->|
           _____________
    ______|||||||||||||||_______
      edge_p2f       edge_f2p
      (endp)         (startp)

EdgeMode B:
   |<---- totalphases(ele) ---->|
    ________           _________
   ||||||||||_________|||||||||||
       edge_f2p     edge_p2f
       (startp)     (endp)

BestPhase:
    if(endp < startp)
        endp = endp + totalphases;
    Best = ((startp + endp) / 2) % totalphases
*********************************************
********************************************/
static int himciv300_tuning_edgedll_mode(struct himciv300_host *host, u32 opcode, int edge_p2f, int edge_f2p, u32 edgeNum)
{
	u32 index;
	u32 found = 0;
	u32 startp =-1, endp = -1;
	u32 startp_init = 0, endp_init = 0;
	u32 phaseoffset = 0, totalphases = 0;
	u16 ele,start_ele, phase_dll_elements;
	u8 mdly_tap_flag = 0;
	int prev_err = 0, err = 0;
	u32 phase_num = himciv300_get_tuning_phase_num(host);

	himci_trace(3, "begin");

	mdly_tap_flag = himciv300_get_sap_dll_taps(host);
	phase_dll_elements = mdly_tap_flag/SDIO_SAP_PS_NUM;
	totalphases = phase_dll_elements*phase_num;

	startp_init = edge_f2p * phase_dll_elements;
	endp_init = edge_p2f * phase_dll_elements;
	startp = startp_init;
	endp = endp_init;

	found = 1;
	start_ele = 2;

	/*Note: edgedll tuning must from edge_p2f to edge_f2p*/
	if(edge_f2p >=  edge_p2f) {
		phaseoffset = edge_p2f * phase_dll_elements;
		for (index = edge_p2f; index < edge_f2p; index++) {
			/* set phase shift */
			himciv300_set_sap_phase(host, index);
			for (ele = start_ele; ele <= phase_dll_elements ; ele++) {
				himciv300_set_dll_element(host, ele);
				err = himciv300_send_tuning(host->mmc,opcode);

				if (!err)
					found = 1;

				if (!prev_err && err && (endp == endp_init))
					endp = phaseoffset + ele;

				if (err)
					startp = phaseoffset + ele;

				#ifdef TUNING_PROC_DEBUG
				printk("\tphase:%01d ele:%02d st:%03d end:%03d error:%d\n", index, ele, startp, endp, err);
				#endif

				prev_err = err;
				err = 0;
			}
			phaseoffset += phase_dll_elements;
		}
	} else {
		phaseoffset = edge_p2f * phase_dll_elements;
		for (index = edge_p2f ; index < phase_num ; index++) {
			/* set phase shift */
			himciv300_set_sap_phase(host, index);
			for (ele = start_ele; ele <= phase_dll_elements ; ele++) {
				himciv300_set_dll_element(host, ele);
				err = himciv300_send_tuning(host->mmc,opcode);
				if (!err)
					found = 1;

				if (!prev_err && err && (endp == endp_init))
					endp = phaseoffset + ele;

				if (err)
					startp = phaseoffset + ele;

				#ifdef TUNING_PROC_DEBUG
				printk("\tphase:%02d ele:%02d st:%03d end:%03d error:%d\n", index, ele, startp, endp, err);
				#endif

				prev_err = err;
				err = 0;
			}
			phaseoffset += phase_dll_elements;
		}

		phaseoffset = 0;
		for (index = 0; index < edge_f2p; index++) {
			/* set phase shift */
			himciv300_set_sap_phase(host, index);
			for (ele = start_ele; ele <= phase_dll_elements ; ele++) {
				himciv300_set_dll_element(host, ele);
				err = himciv300_send_tuning(host->mmc,opcode);
				if (!err)
					found = 1;

				if (!prev_err && err && (endp == endp_init))
					endp = phaseoffset + ele;

				if (err)
					startp = phaseoffset + ele;

				#ifdef TUNING_PROC_DEBUG
				printk("\tphase:%02d ele:%02d st:%03d end:%03d error:%d\n", index, ele, startp, endp, err);
				#endif

				prev_err = err;
				err = 0;
			}
			phaseoffset += phase_dll_elements;
		}
	}
tuning_out:

	if (found) {
		printk("scan elemnts: startp:%d endp:%d\n", startp, endp);

		if (endp <= startp)
			endp += totalphases;

		phaseoffset = (( startp + endp ) / 2) % totalphases;
		index = (phaseoffset / phase_dll_elements);
		ele = (phaseoffset % phase_dll_elements);
		ele = ((ele > start_ele) ? ele : start_ele);

		himciv300_set_sap_phase(host, index);
		himciv300_set_dll_element(host,ele);
		emmc_boot_tuning_phase = index;

		printk(KERN_NOTICE "Tuning SampleClock. mix set phase:[%02d/%02d] ele:[%02d/%02d] \n",index,(phase_num-1),ele,phase_dll_elements);
		mci_writel(host,  MCI_RINTSTS, ALL_INT_CLR);
		return 0;
	}
	printk(KERN_NOTICE "No valid phase shift! use default\n");
	return -1;
}

int himciv300_tuning_mix_mode(struct mmc_host * mmc, u32 opcode)
{
	struct himciv300_host *host = mmc_priv(mmc);
	u32 index, regval;
	u32 found = 0,prefound = 0;
	u32 edge_p2f, edge_f2p;
	u32 edgeNum = 0;
	int err;
	u32 phase_num = himciv300_get_tuning_phase_num(host);

	himci_trace(3, "begin");
	edge_p2f = 0;
	edge_f2p = phase_num;

	himciv300_edge_tuning_enable(host);
	host->tunning = 1;
	for (index = 0; index < phase_num; index++) {

		/* set phase shift */
		himciv300_set_sap_phase(host, index);
		err = himciv300_send_tuning(mmc,opcode);
		if (!err) {
			regval = mci_readl(host, MCI_TUNING_CONTROL);
			found = ((regval & MCI_TUNING_FIND_EDGE) == MCI_TUNING_FIND_EDGE);
		} else {
			found = 1;
		}

		if(found){
			edgeNum++;
		}
		if (prefound && !found) {
			edge_f2p = index;
		} else if (!prefound && found) {
			edge_p2f = index;
		}
		#ifdef TUNING_PROC_DEBUG
		printk("\tphase:%02d found:%02d p2f:%d f2p:%d error:%d\n",index, found, edge_p2f, edge_f2p, err);
		#endif
		if ((edge_p2f != 0) && (edge_f2p != phase_num))
			break;

		prefound = found;
		found = 0;
	}

	if ((edge_p2f == 0) && (edge_f2p == phase_num)) {
		printk("unfound correct edge! check your config is correct!!\n");
		return -1;
	}
	printk("scan edges:%d p2f:%d f2p:%d\n",edgeNum, edge_p2f, edge_f2p);

	if (edge_f2p < edge_p2f)
		index = (edge_f2p + edge_p2f)/2%phase_num;
	else
		index = (edge_f2p + phase_num + edge_p2f)/2%phase_num;
	printk("mix set temp-phase %d\n", index);
	himciv300_set_sap_phase(host, index);
	err = himciv300_send_tuning(mmc,opcode);

	himciv300_edge_tuning_disable(host);
	err = himciv300_tuning_edgedll_mode(host, opcode, edge_p2f, edge_f2p, edgeNum);
	host->tunning = 0;
	return err;
}

int himciv300_tuning_edge_mode(struct mmc_host * mmc, u32 opcode)
{
	struct himciv300_host *host = mmc_priv(mmc);
	u32 index, regval;
	u32 found = 0,prefound = 0;
	u32 startp = 0, endp = 0;
	u32 edge_p2f, edge_f2p;
	u32 phaseoffset = 0, totalphases = 0;
	u32 ele = 0, start_ele = 2;
	int err = 0;
	u32 edgeNum = 0;
	u16 phase_dll_elements;
	u8 mdly_tap_flag = 0;
	u32 phase_num = himciv300_get_tuning_phase_num(host);

	himci_trace(3, "begin");

	mdly_tap_flag = himciv300_get_sap_dll_taps(host);
	phase_dll_elements = mdly_tap_flag/SDIO_SAP_PS_NUM;
	totalphases = phase_dll_elements*phase_num;

	edge_p2f = 0;
	edge_f2p = phase_num;

	host->tunning = 1;
	himciv300_edge_tuning_enable(host);

	for (index = 0; index < phase_num; index++) {

		/* set phase shift */
		himciv300_set_sap_phase(host, index);
		err = himciv300_send_tuning(mmc,opcode);
		if (!err) {
			regval = mci_readl(host, MCI_TUNING_CONTROL);
			found = ((regval & MCI_TUNING_FIND_EDGE) == MCI_TUNING_FIND_EDGE);
		} else {
			found = 1;
		}

		if(found){
			edgeNum++;
		}
		if (prefound && !found) {
			edge_f2p = index;
		} else if (!prefound && found) {
			edge_p2f = index;
		}
		//printk("\tphase:%02d found:%02d p2f:%d f2p:%d error:%d\n",index, found, edge_p2f, edge_f2p, err);

		if ((edge_p2f != 0) && (edge_f2p != phase_num ))
			break;

		prefound = found;
		found = 0;
	}

	if ((edge_p2f == 0) && (edge_f2p == phase_num)) {
		printk("unfound correct edge! check your config is correct!!\n");
		return -1;
	}
	printk("scan edges:%d p2f:%d f2p:%d\n",edgeNum, edge_p2f, edge_f2p);
	startp = edge_f2p * phase_dll_elements;
	endp = edge_p2f * phase_dll_elements;
	printk("found elemnts: startp:%d endp:%d\n", startp, endp);
	if (endp < startp)
		endp += totalphases;

	phaseoffset = (( startp + endp ) / 2) % totalphases;
	index = (phaseoffset / phase_dll_elements);
	ele = (phaseoffset % phase_dll_elements);
	ele = ((ele > start_ele) ? ele : start_ele);

	himciv300_set_sap_phase(host, index);
	himciv300_set_dll_element(host,ele);
	emmc_boot_tuning_phase = index;
	printk(KERN_NOTICE "Tuning SampleClock. edg set phase:[%02d/%02d] ele:[%02d/%02d] \n",index,(phase_num-1),ele,phase_dll_elements);

	himciv300_edge_tuning_disable(host);
	mci_writel(host,  MCI_RINTSTS, ALL_INT_CLR);
	host->tunning = 0;
	return 0;
}

int himciv300_tuning_dll_mode(struct mmc_host * mmc, u32 opcode)
{
	struct himciv300_host *host = mmc_priv(mmc);
	u32 index;
	u32 found = 0;
	u32 startp = 0, endp = 0;
	u32 phaseoffset = 0, totalphases = 0;
	u16 ele, start_ele, phase_dll_elements;
	u8 mdly_tap_flag = 0;
	int prev_err = 0, err = 0;
	u32 phase_num = himciv300_get_tuning_phase_num(host);

	himci_trace(3, "begin");

	mdly_tap_flag = himciv300_get_sap_dll_taps(host);
	phase_dll_elements = mdly_tap_flag/SDIO_SAP_PS_NUM;
	totalphases = phase_dll_elements*phase_num;

	startp = 0;
	endp = totalphases;

	host->tunning = 1;
	found = 0;
	start_ele = 2;
	for (index = 0; index < phase_num; index++) {
			/* set phase shift */
			himciv300_set_sap_phase(host, index);
			for (ele = start_ele; ele <= phase_dll_elements ; ele++) {
				himciv300_set_dll_element(host, ele);
				err = himciv300_send_tuning(host->mmc,opcode);
				if (!err)
					found = 1;

				if (!prev_err && err)
					endp = phaseoffset + ele;

				if ( prev_err && !err)
					startp = phaseoffset + ele;

				//printk("\tphase:%01d ele:%02d st:%03d end:%03d error:%d\n", index, ele, startp, endp, err);
				if ((startp != 0) && (endp != totalphases))
					goto tuning_out;

				prev_err = err;
				err = 0;
			}
			phaseoffset += phase_dll_elements;
	}

tuning_out:

	if (found) {
		printk("scan elemnts: startp:%d endp:%d\n", startp, endp);
		if (endp < startp)
			endp += totalphases;

		phaseoffset = (( startp + endp ) / 2) % totalphases;
		index = (phaseoffset / phase_dll_elements);
		ele = (phaseoffset % phase_dll_elements);
		ele = ((ele > start_ele)?ele:start_ele);
		himciv300_set_sap_phase(host, index);
		himciv300_set_dll_element(host, ele);

		emmc_boot_tuning_phase = index;
		printk(KERN_NOTICE "Tuning SampleClock. dll set phase:[%02d/%02d] ele:[%02d/%02d] \n",index,(phase_num-1),ele,phase_dll_elements);

		mci_writel(host,  MCI_RINTSTS, ALL_INT_CLR);
		host->tunning = 0;
		return 0;
	}

	printk(KERN_NOTICE "No valid phase shift! use default\n");
	return -1;
}

#endif

#ifdef MCI_TUNING_TEST
int himciv300_tuning_test_mode(struct mmc_host * mmc, u32 opcode)
{
	struct himciv300_host *host = mmc_priv(mmc);
	u32 index, regval;
	u32 dline,maxdline;
	u32 found = 0,prefound = 0;
	u32 startp =-1, endp = -1;
	u32 edgeNum = 0;
	u16 ele, phase_dll_elements;
	u8 mdly_tap_flag = 0;
	u32 phase_num = himciv300_get_tuning_phase_num(host);
	u32 goodphase, goodele ;
	int err;

	if (strncmp(dev_name(host->dev), himci_mmc_name, sizeof(himci_mmc_name)) == 0) {
		return 0;
	} else if (strncmp(dev_name(host->dev), himci_sdio0_name, sizeof(himci_sdio0_name)) == 0) {
		return 0;
	} else if (strncmp(dev_name(host->dev), himci_sdio1_name, sizeof(himci_sdio1_name)) == 0) {
		return 0;
	}

	himci_trace(5, " ################ begin ##################");

	host->tunning = 1;
	maxdline = himciv300_edge_tuning_max_dline(host);
	for (dline = 0 ; dline < maxdline; dline++) {
		regval = mci_readl(host, MCI_TUNING_CONTROL);
		regval &= ~MCI_TUNING_DATA_SEL;
		regval |= (dline << MCI_TUNING_DATA_SEL_OFFSET);
		mci_writel(host, MCI_TUNING_CONTROL, regval);

		found = 0;
		mdly_tap_flag = himciv300_get_sap_dll_taps(host);
		phase_dll_elements = mdly_tap_flag/SDIO_SAP_PS_NUM;
		printk("\n");
		himciv300_edge_tuning_enable(host);
		for (index = 0; index < phase_num; index++) {
			/* set phase shift */
			himciv300_set_sap_phase(host, index);
			err = himciv300_send_tuning(mmc,opcode);
			if (!err) {
				regval = mci_readl(host, MCI_TUNING_CONTROL);
				found = ((regval & MCI_TUNING_FIND_EDGE) == MCI_TUNING_FIND_EDGE);
			} else {
				found = 1;
			}

			if(found)
				printk("data%d p%d tag:%d found:%d phaseele:%d\n",dline,index,mdly_tap_flag,found,phase_dll_elements);
			else
				printk("data%d p%d tag:%d         phaseele:%d\n",dline,index,mdly_tap_flag,phase_dll_elements);
		}
		himciv300_edge_tuning_disable(host);

		for (index = 0; index < phase_num; index++) {
			/* set phase shift */
			himciv300_set_sap_phase(host, index);
			for (ele = 2; ele <= phase_dll_elements ; ele++) {
				himciv300_set_dll_element(host, ele);
				err = himciv300_send_tuning(mmc,opcode);
				if (err) {
					printk("\tp%d ele:%02d error:%d\n",index,ele,err);
				} else {
					goodphase = index;
					goodele = ele;
				}
			}
		}
		himciv300_set_sap_phase(host, goodphase);
		himciv300_set_dll_element(host, goodele);
		err = himciv300_send_tuning(mmc,opcode);
	}
	host->tunning = 0;
	himci_trace(5, " ################ end ##################");
	return err;
}
#endif


/******************************************************************************/

u32 iohs[] = {
	IOSHARE_OFFSET_EMMC_DATA3, EMMC_DRV_CAP_HS_CMD_DATA,
	IOSHARE_OFFSET_EMMC_DATA4, EMMC_DRV_CAP_HS_CMD_DATA,
	IOSHARE_OFFSET_EMMC_DATA0, EMMC_DRV_CAP_HS_CMD_DATA,
	IOSHARE_OFFSET_EMMC_DATA5, EMMC_DRV_CAP_HS_CMD_DATA,
	IOSHARE_OFFSET_EMMC_DATA1, EMMC_DRV_CAP_HS_CMD_DATA,
	IOSHARE_OFFSET_EMMC_DATA6, EMMC_DRV_CAP_HS_CMD_DATA,
	IOSHARE_OFFSET_EMMC_DATA2, EMMC_DRV_CAP_HS_CMD_DATA,
	IOSHARE_OFFSET_EMMC_DATA7, EMMC_DRV_CAP_HS_CMD_DATA,
	IOSHARE_OFFSET_EMMC_CLOCK, EMMC_DRV_CAP_HS_CLOCK,
	IOSHARE_OFFSET_EMMC_CMD,   EMMC_DRV_CAP_HS_CMD_DATA,
	0xff, 0xff,
};

u32 ioddr50[] = {
	IOSHARE_OFFSET_EMMC_DATA3, EMMC_DRV_CAP_DDR50_CMD_DATA,
	IOSHARE_OFFSET_EMMC_DATA4, EMMC_DRV_CAP_DDR50_CMD_DATA,
	IOSHARE_OFFSET_EMMC_DATA0, EMMC_DRV_CAP_DDR50_CMD_DATA,
	IOSHARE_OFFSET_EMMC_DATA5, EMMC_DRV_CAP_DDR50_CMD_DATA,
	IOSHARE_OFFSET_EMMC_DATA1, EMMC_DRV_CAP_DDR50_CMD_DATA,
	IOSHARE_OFFSET_EMMC_DATA6, EMMC_DRV_CAP_DDR50_CMD_DATA,
	IOSHARE_OFFSET_EMMC_DATA2, EMMC_DRV_CAP_DDR50_CMD_DATA,
	IOSHARE_OFFSET_EMMC_DATA7, EMMC_DRV_CAP_DDR50_CMD_DATA,
	IOSHARE_OFFSET_EMMC_CLOCK, EMMC_DRV_CAP_DDR50_CLOCK,
	IOSHARE_OFFSET_EMMC_CMD,   EMMC_DRV_CAP_DDR50_CMD_DATA,
	0xff, 0xff,
};

u32 iohs200[] = {
	IOSHARE_OFFSET_EMMC_DATA3, EMMC_DRV_CAP_HS200_CMD_DATA,
	IOSHARE_OFFSET_EMMC_DATA4, EMMC_DRV_CAP_HS200_CMD_DATA,
	IOSHARE_OFFSET_EMMC_DATA0, EMMC_DRV_CAP_HS200_CMD_DATA,
	IOSHARE_OFFSET_EMMC_DATA5, EMMC_DRV_CAP_HS200_CMD_DATA,
	IOSHARE_OFFSET_EMMC_DATA1, EMMC_DRV_CAP_HS200_CMD_DATA,
	IOSHARE_OFFSET_EMMC_DATA6, EMMC_DRV_CAP_HS200_CMD_DATA,
	IOSHARE_OFFSET_EMMC_DATA2, EMMC_DRV_CAP_HS200_CMD_DATA,
	IOSHARE_OFFSET_EMMC_DATA7, EMMC_DRV_CAP_HS200_CMD_DATA,
	IOSHARE_OFFSET_EMMC_CLOCK, EMMC_DRV_CAP_HS200_CLOCK,
	IOSHARE_OFFSET_EMMC_CMD,   EMMC_DRV_CAP_HS200_CMD_DATA,
	0xff, 0xff,
};

u32 iohs400[] = {
	IOSHARE_OFFSET_EMMC_DATA3, EMMC_DRV_CAP_HS400_CMD_DATA,
	IOSHARE_OFFSET_EMMC_DATA4, EMMC_DRV_CAP_HS400_CMD_DATA,
	IOSHARE_OFFSET_EMMC_DATA0, EMMC_DRV_CAP_HS400_CMD_DATA,
	IOSHARE_OFFSET_EMMC_DATA5, EMMC_DRV_CAP_HS400_CMD_DATA,
	IOSHARE_OFFSET_EMMC_DATA1, EMMC_DRV_CAP_HS400_CMD_DATA,
	IOSHARE_OFFSET_EMMC_DATA6, EMMC_DRV_CAP_HS400_CMD_DATA,
	IOSHARE_OFFSET_EMMC_DATA2, EMMC_DRV_CAP_HS400_CMD_DATA,
	IOSHARE_OFFSET_EMMC_DATA7, EMMC_DRV_CAP_HS400_CMD_DATA,
	IOSHARE_OFFSET_EMMC_CLOCK, EMMC_DRV_CAP_HS400_CLOCK,
	IOSHARE_OFFSET_EMMC_CMD,   EMMC_DRV_CAP_HS400_CMD_DATA,
	0xff, 0xff,
};

u32 io_sdhs[] = {
	IOSHARE_OFFSET_SDIO0_CLOCK, SDIO_DRV_CAP_3V3_50M_CLOCK,
	IOSHARE_OFFSET_SDIO0_CMD,   SDIO_DRV_CAP_3V3_50M_CMD_DATA,
	IOSHARE_OFFSET_SDIO0_DATA0, SDIO_DRV_CAP_3V3_50M_CMD_DATA,
	IOSHARE_OFFSET_SDIO0_DATA1, SDIO_DRV_CAP_3V3_50M_CMD_DATA,
	IOSHARE_OFFSET_SDIO0_DATA2, SDIO_DRV_CAP_3V3_50M_CMD_DATA,
	IOSHARE_OFFSET_SDIO0_DATA3, SDIO_DRV_CAP_3V3_50M_CMD_DATA,
	0xff,0xff,
};

u32 io_uhs_sdr25[] = {
	IOSHARE_OFFSET_SDIO0_CLOCK, SDIO_DRV_CAP_1V8_50M_CLOCK,
	IOSHARE_OFFSET_SDIO0_CMD,   SDIO_DRV_CAP_1V8_50M_CMD_DATA,
	IOSHARE_OFFSET_SDIO0_DATA0, SDIO_DRV_CAP_1V8_50M_CMD_DATA,
	IOSHARE_OFFSET_SDIO0_DATA1, SDIO_DRV_CAP_1V8_50M_CMD_DATA,
	IOSHARE_OFFSET_SDIO0_DATA2, SDIO_DRV_CAP_1V8_50M_CMD_DATA,
	IOSHARE_OFFSET_SDIO0_DATA3, SDIO_DRV_CAP_1V8_50M_CMD_DATA,
	0xff,0xff,
};

u32 io_uhs_sdr50[] = {
	IOSHARE_OFFSET_SDIO0_CLOCK, SDIO_DRV_CAP_1V8_100M_CLOCK,
	IOSHARE_OFFSET_SDIO0_CMD,   SDIO_DRV_CAP_1V8_100M_CMD_DATA,
	IOSHARE_OFFSET_SDIO0_DATA0, SDIO_DRV_CAP_1V8_100M_CMD_DATA,
	IOSHARE_OFFSET_SDIO0_DATA1, SDIO_DRV_CAP_1V8_100M_CMD_DATA,
	IOSHARE_OFFSET_SDIO0_DATA2, SDIO_DRV_CAP_1V8_100M_CMD_DATA,
	IOSHARE_OFFSET_SDIO0_DATA3, SDIO_DRV_CAP_1V8_100M_CMD_DATA,
	0xff,0xff,
};

u32 io_uhs_sdr104[] = {
	IOSHARE_OFFSET_SDIO0_CLOCK, SDIO_DRV_CAP_1V8_200M_CLOCK,
	IOSHARE_OFFSET_SDIO0_CMD,   SDIO_DRV_CAP_1V8_200M_CMD_DATA,
	IOSHARE_OFFSET_SDIO0_DATA0, SDIO_DRV_CAP_1V8_200M_CMD_DATA,
	IOSHARE_OFFSET_SDIO0_DATA1, SDIO_DRV_CAP_1V8_200M_CMD_DATA,
	IOSHARE_OFFSET_SDIO0_DATA2, SDIO_DRV_CAP_1V8_200M_CMD_DATA,
	IOSHARE_OFFSET_SDIO0_DATA3, SDIO_DRV_CAP_1V8_200M_CMD_DATA,
	0xff,0xff,
};

u32 io_sdio1_sdhs[] = {
	IOSHARE_OFFSET_SDIO1_CLOCK, SDIO_DRV_CAP_3V3_50M_CLOCK,
	IOSHARE_OFFSET_SDIO1_CMD,   SDIO_DRV_CAP_3V3_50M_CMD_DATA,
	IOSHARE_OFFSET_SDIO1_DATA0, SDIO_DRV_CAP_3V3_50M_CMD_DATA,
	IOSHARE_OFFSET_SDIO1_DATA1, SDIO_DRV_CAP_3V3_50M_CMD_DATA,
	IOSHARE_OFFSET_SDIO1_DATA2, SDIO_DRV_CAP_3V3_50M_CMD_DATA,
	IOSHARE_OFFSET_SDIO1_DATA3, SDIO_DRV_CAP_3V3_50M_CMD_DATA,
	0xff,0xff,
};

u32 io_sdio1_sdr25[] = {
	IOSHARE_OFFSET_SDIO1_CLOCK, SDIO_DRV_CAP_1V8_50M_CLOCK,
	IOSHARE_OFFSET_SDIO1_CMD,   SDIO_DRV_CAP_1V8_50M_CMD_DATA,
	IOSHARE_OFFSET_SDIO1_DATA0, SDIO_DRV_CAP_1V8_50M_CMD_DATA,
	IOSHARE_OFFSET_SDIO1_DATA1, SDIO_DRV_CAP_1V8_50M_CMD_DATA,
	IOSHARE_OFFSET_SDIO1_DATA2, SDIO_DRV_CAP_1V8_50M_CMD_DATA,
	IOSHARE_OFFSET_SDIO1_DATA3, SDIO_DRV_CAP_1V8_50M_CMD_DATA,
	0xff,0xff,
};

u32 io_sdio1_sdr50[] = {
	IOSHARE_OFFSET_SDIO1_CLOCK, SDIO_DRV_CAP_1V8_100M_CLOCK,
	IOSHARE_OFFSET_SDIO1_CMD,   SDIO_DRV_CAP_1V8_100M_CMD_DATA,
	IOSHARE_OFFSET_SDIO1_DATA0, SDIO_DRV_CAP_1V8_100M_CMD_DATA,
	IOSHARE_OFFSET_SDIO1_DATA1, SDIO_DRV_CAP_1V8_100M_CMD_DATA,
	IOSHARE_OFFSET_SDIO1_DATA2, SDIO_DRV_CAP_1V8_100M_CMD_DATA,
	IOSHARE_OFFSET_SDIO1_DATA3, SDIO_DRV_CAP_1V8_100M_CMD_DATA,
	0xff,0xff,
};

u32 io_sdio1_sdr104[] = {
	IOSHARE_OFFSET_SDIO1_CLOCK, SDIO_DRV_CAP_1V8_200M_CLOCK,
	IOSHARE_OFFSET_SDIO1_CMD,   SDIO_DRV_CAP_1V8_200M_CMD_DATA,
	IOSHARE_OFFSET_SDIO1_DATA0, SDIO_DRV_CAP_1V8_200M_CMD_DATA,
	IOSHARE_OFFSET_SDIO1_DATA1, SDIO_DRV_CAP_1V8_200M_CMD_DATA,
	IOSHARE_OFFSET_SDIO1_DATA2, SDIO_DRV_CAP_1V8_200M_CMD_DATA,
	IOSHARE_OFFSET_SDIO1_DATA3, SDIO_DRV_CAP_1V8_200M_CMD_DATA,
	0xff,0xff,
};

/******************************************************************************/

static void himciv300_set_driver(struct himciv300_host * host, u8 timing)
{
	u32 ix, regval;
	u32* io = NULL;

	if (strncmp(dev_name(host->dev), himci_mmc_name, sizeof(himci_mmc_name)) == 0) {
		 if ((timing == MMC_TIMING_MMC_HS)
			|| (timing == MMC_TIMING_LEGACY)) {
			io = iohs;
			for (ix = 0; io[ix] != 0xff; ix += 2) {
				regval = readl( host->ioshare_addr + io[ix]);
				regval &= ~(DRV_CAPS_MASK | DRV_SLEV_RATE);
				if (IOSHARE_OFFSET_EMMC_CLOCK == io[ix])
					regval |= EMMC_DRV_SR_HS_CLOCK;
				else
					regval |= EMMC_DRV_SR_HS_CMD_DATA;
				regval |= io[ix+1];
				writel(regval, host->ioshare_addr + io[ix]);
			}
		} if (timing == MMC_TIMING_MMC_DDR52) {
			io = ioddr50;
			for (ix = 0; io[ix] != 0xff; ix += 2) {
				regval = readl( host->ioshare_addr + io[ix]);
				regval &= ~(DRV_CAPS_MASK | DRV_SLEV_RATE);
				if (IOSHARE_OFFSET_EMMC_CLOCK == io[ix])
					regval |= EMMC_DRV_SR_DDR50_CLOCK;
				else
					regval |= EMMC_DRV_SR_DDR50_CMD_DATA;
				regval |= io[ix+1];
				writel(regval, host->ioshare_addr + io[ix]);
			}
		} else if (timing == MMC_TIMING_MMC_HS200) {
			io = iohs200;
			for (ix = 0; io[ix] != 0xff; ix += 2) {
				regval = readl( host->ioshare_addr + io[ix]);
				regval &= ~(DRV_CAPS_MASK | DRV_SLEV_RATE);
				if (IOSHARE_OFFSET_EMMC_CLOCK == io[ix])
					regval |= EMMC_DRV_SR_HS200_CLOCK;
				else
					regval |= EMMC_DRV_SR_HS200_CMD_DATA;
				regval |= io[ix+1];
				writel(regval, host->ioshare_addr + io[ix]);
			}
		} else if (timing == MMC_TIMING_MMC_HS400) {
			io = iohs400;
			for (ix = 0; io[ix] != 0xff; ix += 2) {
				regval = readl( host->ioshare_addr + io[ix]);
				regval &= ~(DRV_CAPS_MASK | DRV_SLEV_RATE);
				if (IOSHARE_OFFSET_EMMC_CLOCK == io[ix])
					regval |= EMMC_DRV_SR_HS400_CLOCK;
				else
					regval |= EMMC_DRV_SR_HS400_CMD_DATA;
				regval |= io[ix+1];
				writel(regval, host->ioshare_addr + io[ix]);
			}
			regval = readl( host->ioshare_addr + IOSHARE_OFFSET_EMMC_DATA_STROBE);
			regval |= DRV_IOCTRL_PD;
			writel(regval, host->ioshare_addr + IOSHARE_OFFSET_EMMC_DATA_STROBE);
		}
	} else if(strncmp(dev_name(host->dev), himci_sdio0_name, sizeof(himci_sdio0_name)) == 0){
		if((timing == MMC_TIMING_SD_HS) ||
			(timing == MMC_TIMING_LEGACY)) {
			io = io_sdhs;
			for (ix = 0; io[ix] != 0xff; ix += 2) {
				regval = readl( host->ioshare_addr + io[ix]);
				regval &= ~(DRV_CAPS_MASK | DRV_SLEV_RATE);
				if (IOSHARE_OFFSET_SDIO0_CLOCK == io[ix])
					regval |= SDIO_DRV_SR_3V3_50M_CLOCK;
				else
					regval |= SDIO_DRV_SR_3V3_50M_CMD_DATA;
				regval |= io[ix+1];
				writel(regval, host->ioshare_addr + io[ix]);
			}
		} else if ((timing == MMC_TIMING_UHS_DDR50) ||
					(timing == MMC_TIMING_UHS_SDR25) ||
					(timing == MMC_TIMING_UHS_SDR12)){
			io = io_uhs_sdr25;
			for (ix = 0; io[ix] != 0xff; ix += 2) {
				regval = readl( host->ioshare_addr + io[ix]);
				regval &= ~(DRV_CAPS_MASK | DRV_SLEV_RATE);
				if (IOSHARE_OFFSET_SDIO0_CLOCK == io[ix])
					regval |= SDIO_DRV_SR_1V8_50M_CLOCK;
				else
					regval |= SDIO_DRV_SR_1V8_50M_CMD_DATA;
				regval |= io[ix+1];
				writel(regval, host->ioshare_addr + io[ix]);
			}
		} else if (timing == MMC_TIMING_UHS_SDR50) {
			io = io_uhs_sdr50;
			for (ix = 0; io[ix] != 0xff; ix += 2) {
				regval = readl( host->ioshare_addr + io[ix]);
				regval &= ~(DRV_CAPS_MASK | DRV_SLEV_RATE);
				if (IOSHARE_OFFSET_SDIO0_CLOCK == io[ix])
					regval |= SDIO_DRV_SR_1V8_100M_CLOCK;
				else
					regval |= SDIO_DRV_SR_1V8_100M_CMD_DATA;
				regval |= io[ix+1];
				writel(regval, host->ioshare_addr + io[ix]);
			}
		} else if (timing == MMC_TIMING_UHS_SDR104) {
			io = io_uhs_sdr104;
			for (ix = 0; io[ix] != 0xff; ix += 2) {
				regval = readl( host->ioshare_addr + io[ix]);
				regval &= ~(DRV_CAPS_MASK | DRV_SLEV_RATE);
				if (IOSHARE_OFFSET_SDIO0_CLOCK == io[ix])
					regval |= SDIO_DRV_SR_1V8_200M_CLOCK;
				else
					regval |= SDIO_DRV_SR_1V8_200M_CMD_DATA;
				regval |=  io[ix+1];
				writel(regval, host->ioshare_addr + io[ix]);
			}
		}
	} else if(strncmp(dev_name(host->dev), himci_sdio1_name, sizeof(himci_sdio1_name)) == 0){
		if((timing == MMC_TIMING_SD_HS) ||
			(timing == MMC_TIMING_LEGACY)) {
			io = io_sdio1_sdhs;
			for (ix = 0; io[ix] != 0xff; ix += 2) {
				regval = readl( host->ioshare_addr + io[ix]);
				regval &= ~(DRV_CAPS_MASK | DRV_SLEV_RATE);
				if (IOSHARE_OFFSET_SDIO0_CLOCK == io[ix])
					regval |= SDIO_DRV_SR_3V3_50M_CLOCK;
				else
					regval |= SDIO_DRV_SR_3V3_50M_CMD_DATA;
				regval |= io[ix+1];
				writel(regval, host->ioshare_addr + io[ix]);
			}
		} else if ((timing == MMC_TIMING_UHS_DDR50) ||
					(timing == MMC_TIMING_UHS_SDR25) ||
					(timing == MMC_TIMING_UHS_SDR12)){
			io = io_sdio1_sdr25;
			for (ix = 0; io[ix] != 0xff; ix += 2) {
				regval = readl( host->ioshare_addr + io[ix]);
				regval &= ~(DRV_CAPS_MASK | DRV_SLEV_RATE);
				if (IOSHARE_OFFSET_SDIO0_CLOCK == io[ix])
					regval |= SDIO_DRV_SR_1V8_50M_CLOCK;
				else
					regval |= SDIO_DRV_SR_1V8_50M_CMD_DATA;
				regval |= io[ix+1];
				writel(regval, host->ioshare_addr + io[ix]);
			}
		} else if (timing == MMC_TIMING_UHS_SDR50) {
			io = io_sdio1_sdr50;
			for (ix = 0; io[ix] != 0xff; ix += 2) {
				regval = readl( host->ioshare_addr + io[ix]);
				regval &= ~(DRV_CAPS_MASK | DRV_SLEV_RATE);
				if (IOSHARE_OFFSET_SDIO0_CLOCK == io[ix])
					regval |= SDIO_DRV_SR_1V8_100M_CLOCK;
				else
					regval |= SDIO_DRV_SR_1V8_100M_CMD_DATA;
				regval |= io[ix+1];
				writel(regval, host->ioshare_addr + io[ix]);
			}
		} else if (timing == MMC_TIMING_UHS_SDR104) {
			io = io_sdio1_sdr104;
			for (ix = 0; io[ix] != 0xff; ix += 2) {
				regval = readl( host->ioshare_addr + io[ix]);
				regval &= ~(DRV_CAPS_MASK | DRV_SLEV_RATE);
				if (IOSHARE_OFFSET_SDIO0_CLOCK == io[ix])
					regval |= SDIO_DRV_SR_1V8_200M_CLOCK;
				else
					regval |= SDIO_DRV_SR_1V8_200M_CMD_DATA;
				regval |=  io[ix+1];
				writel(regval, host->ioshare_addr + io[ix]);
			}
		}
	}
}

/******************************************************************************/

static void himciv300_set_crgclk(struct himciv300_host * host, u8 timing)
{
	if (strncmp(dev_name(host->dev), himci_mmc_name, sizeof(himci_mmc_name)) == 0) {

		if(timing == MMC_TIMING_MMC_HS) {
			host->mmc->f_max = 50000000;
		}else if(timing == MMC_TIMING_LEGACY) {
			host->mmc->f_max = 25000000;
		}		 else if (timing == MMC_TIMING_UHS_DDR50) {
			host->mmc->f_max = 50000000;
		} else if (timing == MMC_TIMING_MMC_DDR52) {
			host->mmc->f_max = 50000000;
		} else if (timing == MMC_TIMING_MMC_HS200) {
				host->mmc->f_max = HS200_MAX_CLK;
		} else if (timing == MMC_TIMING_MMC_HS400) {
			host->mmc->f_max = HS400_MAX_CLK;
		}

		clk_set_rate(host->clk,	(unsigned long)host->mmc->f_max);
	} else if ((strncmp(dev_name(host->dev), himci_sdio0_name, sizeof(himci_sdio0_name)) == 0) ||
			   (strncmp(dev_name(host->dev), himci_sdio1_name, sizeof(himci_sdio1_name)) == 0)) {
		if (timing == MMC_TIMING_LEGACY) {
			host->mmc->f_max = 25000000;
		} else if (timing == MMC_TIMING_SD_HS) {
			host->mmc->f_max = 50000000;
		} else if (timing == MMC_TIMING_UHS_DDR50) {
			host->mmc->f_max = 50000000;
		} else if (timing == MMC_TIMING_UHS_SDR12) {
			host->mmc->f_max = 25000000;
		} else if (timing == MMC_TIMING_UHS_SDR25) {
			host->mmc->f_max = 50000000;
		} else if (timing == MMC_TIMING_UHS_SDR50) {
			host->mmc->f_max = 100000000;
		} else if (timing == MMC_TIMING_UHS_SDR104) {
			if (strncmp(dev_name(host->dev), himci_sdio1_name, sizeof(himci_sdio1_name)) == 0)
				host->mmc->f_max = SDR104_CLK_187M;
			else
				host->mmc->f_max = SDR104_CLK_150M;
		}

		clk_set_rate(host->clk, (unsigned long)host->mmc->f_max);
	}
}
/******************************************************************************/
static void himciv300_emmc_set_phase(struct himciv300_host * host, u8 timing)
{
	u32 regval;
	/* config sample clk/drv clk phase shift */
	regval = (u32)clk_get_phase(host->clk);
	regval = regval << SDIO_SAP_PS_SHIFT_BIT;
	if (timing == MMC_TIMING_LEGACY) {
		regval &= ~(SDIO_SAP_PS_MASK | SDIO_DRV_PS_MASK);
		regval |= SDIO_SAP_PS_0 | SDIO_DRV_PS_90;
	} else if (timing == MMC_TIMING_MMC_HS) {
		regval &= ~(SDIO_SAP_PS_MASK| SDIO_DRV_PS_MASK);
		regval |= SDIO_SAP_PS_0 | SDIO_DRV_PS_90;
	} else if (timing == MMC_TIMING_MMC_DDR52) {
		regval &= ~(SDIO_SAP_PS_MASK| SDIO_DRV_PS_MASK);
		regval |= SDIO_DRV_PS_67DOT5;
		if (host->iovoltage == EMMC_IO_VOL_1_8V)
			regval |= SDIO_SAP_PS_112DOT5;
		else
			regval |= SDIO_SAP_PS_45;
	} else if (timing == MMC_TIMING_MMC_HS200) {
		regval &= ~(SDIO_DRV_PS_MASK);
		regval |= SDIO_DRV_PS_112DOT5;
	} else if(timing == MMC_TIMING_MMC_HS400) {
		regval &= ~(SDIO_SAP_PS_MASK | SDIO_DRV_PS_MASK);
		regval |= (emmc_boot_tuning_phase << SDIO_SAP_PS_OFFSET) | SDIO_DRV_PS_90;
	}
	/* clk_set_phase has  regval%360, so shifit 12bit */
	regval = regval >> SDIO_SAP_PS_SHIFT_BIT;
	clk_set_phase(host->clk, (int)regval);

	/* ddr50 need to enable shift */
	regval = mci_readl(host, MCI_ENABLE_SHIFT);
	 if (timing == MMC_TIMING_MMC_DDR52)
		regval |= ENABLE_SHIFT_01;
	else
		regval &= ~ENABLE_SHIFT_01;
	mci_writel(host, MCI_ENABLE_SHIFT, regval);
}

static void himciv300_sdio0_set_phase(struct himciv300_host * host, u8 timing)
{
	u32 regval;
	regval = (u32)clk_get_phase(host->clk);
	regval = regval << SDIO_SAP_PS_SHIFT_BIT;
	if (timing == MMC_TIMING_UHS_SDR104){
		regval &= ~(SDIO_DRV_PS_MASK);
		regval |= (SDIO_DRV_PS_90);
	} else if (timing == MMC_TIMING_UHS_DDR50) {
		regval &= ~(SDIO_DRV_PS_MASK);
		regval |= (SDIO_DRV_PS_67DOT5);
	} else if (timing == MMC_TIMING_UHS_SDR50){
		regval &= ~(SDIO_DRV_PS_MASK);
		regval |= (SDIO_DRV_PS_90);
	}  else if (timing == MMC_TIMING_UHS_SDR25){
		regval &= ~(SDIO_SAP_PS_MASK | SDIO_DRV_PS_MASK);
		regval |= (SDIO_DRV_PS_90 | SDIO_SAP_PS_22DOT5);
	} else if (timing == MMC_TIMING_UHS_SDR12){
		regval &= ~(SDIO_SAP_PS_MASK | SDIO_DRV_PS_MASK);
		regval |= (SDIO_DRV_PS_90 | SDIO_SAP_PS_315);
	} else if (timing == MMC_TIMING_SD_HS){
		regval &= ~(SDIO_SAP_PS_MASK | SDIO_DRV_PS_MASK);
		regval |= (SDIO_DRV_PS_90 | SDIO_SAP_PS_0);
	} else if(timing == MMC_TIMING_LEGACY) {
		regval &= ~(SDIO_SAP_PS_MASK | SDIO_DRV_PS_MASK);
		regval |= (SDIO_DRV_PS_90 | SDIO_SAP_PS_67DOT5);
	}
	/* clk_set_phase has  regval%360, so shifit 12bit */
	regval = regval >> SDIO_SAP_PS_SHIFT_BIT;
	clk_set_phase(host->clk, (int)regval);
}

static void himciv300_sdio1_set_phase(struct himciv300_host * host, u8 timing)
{
	u32 regval;
	regval = (u32)clk_get_phase(host->clk);
	regval = regval << SDIO_SAP_PS_SHIFT_BIT;
	if (timing == MMC_TIMING_UHS_SDR104){
		regval &= ~(SDIO_DRV_PS_MASK);
		regval |= (SDIO_DRV_PS_67DOT5);
	} else if (timing == MMC_TIMING_UHS_DDR50) {
		regval &= ~(SDIO_DRV_PS_MASK);
		regval |= (SDIO_DRV_PS_67DOT5);
	} else if (timing == MMC_TIMING_UHS_SDR50) {
		regval &= ~(SDIO_DRV_PS_MASK);
		regval |= (SDIO_DRV_PS_67DOT5);
	}  else if (timing == MMC_TIMING_UHS_SDR25) {
		regval &= ~(SDIO_SAP_PS_MASK | SDIO_DRV_PS_MASK);
		regval |= (SDIO_DRV_PS_67DOT5 | SDIO_SAP_PS_22DOT5);
	} else if (timing == MMC_TIMING_UHS_SDR12) {
		regval &= ~(SDIO_SAP_PS_MASK | SDIO_DRV_PS_MASK);
		regval |= (SDIO_DRV_PS_67DOT5 | SDIO_SAP_PS_315);
	} else if (timing == MMC_TIMING_SD_HS) {
		regval &= ~(SDIO_SAP_PS_MASK | SDIO_DRV_PS_MASK);
		regval |= (SDIO_DRV_PS_67DOT5 | SDIO_SAP_PS_0);
	} else if(timing == MMC_TIMING_LEGACY) {
		regval &= ~(SDIO_SAP_PS_MASK | SDIO_DRV_PS_MASK);
		regval |= (SDIO_DRV_PS_67DOT5 | SDIO_SAP_PS_67DOT5);
	}
	/* clk_set_phase has  regval%360, so shifit 12bit */
	regval = regval >> SDIO_SAP_PS_SHIFT_BIT;
	clk_set_phase(host->clk, (int)regval);
}

static void himciv300_set_phase(struct himciv300_host * host, u8 timing)
{
	himci_trace(3, "begin");

	if (strncmp(dev_name(host->dev), himci_mmc_name, sizeof(himci_mmc_name)) == 0) {
		himciv300_emmc_set_phase(host, timing);
	} else if(strncmp(dev_name(host->dev), himci_sdio0_name, sizeof(himci_sdio0_name)) == 0) {
		himciv300_sdio0_set_phase(host, timing);
	} else if(strncmp(dev_name(host->dev), himci_sdio1_name, sizeof(himci_sdio1_name)) == 0) {
		himciv300_sdio1_set_phase(host, timing);
	}
}
/******************************************************************************/

static void himciv300_set_timing(struct himciv300_host * host, u8 timing)
{
	himciv300_set_driver(host, timing);
	himciv300_set_crgclk(host, timing);
	himciv300_set_phase(host, timing);
}
/******************************************************************************/

static int himciv300_prepare_hs400(struct mmc_host * mmc, struct mmc_ios * ios)
{
	u32 ix, regval;
	struct himciv300_host *host = mmc_priv(mmc);
	himci_trace(3, "begin");

	if (strncmp(dev_name(host->dev), himci_mmc_name, sizeof(himci_mmc_name)) == 0) {
		/* config driver strength */
		for (ix = 0; iohs400[ix] != 0xff; ix += 2) {
			regval = readl( host->ioshare_addr + iohs400[ix]);
			regval &= ~(DRV_CAPS_MASK | DRV_SLEV_RATE);
			if(HS400_MAX_CLK == HS400_CLK_100M) {
				regval |= DRV_SLEV_RATE;
			}
			regval |= iohs400[ix+1];
			writel(regval, host->ioshare_addr + iohs400[ix]);
		}

		/* config source clock */
		host->mmc->f_max = HS400_MAX_CLK;
		clk_set_rate(host->clk,	(unsigned long)host->mmc->f_max);

		/* config clk phase */
		regval = (u32)clk_get_phase(host->clk);
		regval = regval << SDIO_SAP_PS_SHIFT_BIT;
		regval &= ~(SDIO_DRV_PS_MASK);
		regval |= SDIO_DRV_PS_90;
		regval = regval >> SDIO_SAP_PS_SHIFT_BIT;
		clk_set_phase(host->clk, (int)regval);
	}

	return 0;
}

static int himciv300_check_tuning(struct mmc_host * mmc, u32 opcode)
{
	int err;
	struct himciv300_host *host = mmc_priv(mmc);

	host->tunning = 1;
	err = himciv300_send_tuning(mmc,opcode);
	host->tunning = 0;

	return 	err;
}

/******************************************************************************/

int himciv300_execute_tuning(struct mmc_host * mmc, u32 opcode)
{
	int err;

	himci_trace(3, "begin");
#ifdef MCI_TUNING_TEST
	himciv300_tuning_test_mode(mmc,opcode);
#endif

	err = himciv300_tuning_mix_mode(mmc,opcode);
	himciv300_tuning_feedback(mmc);
	if (!err)
		err = himciv300_check_tuning(mmc,opcode);

	if (err) {
		err = himciv300_tuning_edge_mode(mmc,opcode);
		himciv300_tuning_feedback(mmc);
		if (!err)
			err = himciv300_check_tuning(mmc,opcode);

		if (err) {
				err = himciv300_tuning_dll_mode(mmc,opcode);
				himciv300_tuning_feedback(mmc);
				if (!err)
					err = himciv300_check_tuning(mmc,opcode);
			}
	}
	return err;
}
/******************************************************************************/

unsigned int get_mmc_io_voltage(void)
{
	unsigned int voltage = 0;
	void __iomem *virtaddr;

	virtaddr = ioremap_nocache(REG_BASE_SCTL + REG_SC_GEN29, PAGE_SIZE);
	if (!virtaddr) {
		printk("ioremap emmc error.\n");
		return 1;
	}

	voltage = readl(virtaddr);
	voltage &= EMMC_IO_VOLTAGE_MASK;

	iounmap(virtaddr);

	return voltage;
}
