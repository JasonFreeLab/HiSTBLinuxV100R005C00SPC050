
#define REG_BASE_CRG	0xF8A22000
#define REG_EMMC_SAP_DLL_CTRL			(REG_BASE_CRG + 0x039C)
#define REG_EMMC_SAP_DLL_STATUS			(REG_BASE_CRG + 0x03A0)
#define REG_SDIO0_SAP_DLL_CTRL			(REG_BASE_CRG + 0x03A4)
#define REG_SDIO0_SAP_DLL_STATUS		(REG_BASE_CRG + 0x03A8)

#define SAP_DLL_CTRL_SLAVE_EN		(1<<19)
#define SAP_DLL_CTRL_STOP			(1<<18)
#define SAP_DLL_CTRL_BYPASS			(1<<17)
#define SAP_DLL_CTRL_DLLMODE		(1<<16)
#define SAP_DLL_CTRL_DLLSSEL		(0xFF << 8)
#define SAP_DLL_CTRL_DLLSSEL_OFFSET 8

#define SAP_DLL_MDLY_TAP_FLAG		(0xFF)

#define SAP_TUNING_CLKAB_INTERVAL_90		4

#define MCI_TUNING_CONTROL				0x118
#define MCI_TUNING_FIND_EDGE			(1<<5)
#define MCI_TUNING_DATA_SEL				(0x07 << 2)
#define MCI_TUNING_EDGE_CONTROL			(1<<1)
#define MCI_TUNING_ENABLE_NEW_TUNING	(1<<0)

static int himciv300_send_tuning(struct mmc_dev_t *mmc, unsigned int datastrobe)
{
	int err = 0;

	if (datastrobe)
		err = mmc_send_tuning(mmc, MMC_CMD_SEND_EXT_CSD);
	else
		err = mmc_send_tuning(mmc, MMC_CMD_SEND_TUNING_BLOCK_HS200);

	return err;
}

static void himciv300_edge_tuning_enable(struct himci_host *host)
{
	u32 regval;

	regval = himci_readl(REG_EMMC_SAP_DLL_CTRL);
	regval &=~SAP_DLL_CTRL_DLLMODE;
	himci_writel(regval, REG_EMMC_SAP_DLL_CTRL);

	regval = himci_readl(host->base + MCI_TUNING_CONTROL);
	regval |= MCI_TUNING_ENABLE_NEW_TUNING;
	himci_writel(regval, host->base +MCI_TUNING_CONTROL);
}

static void himciv300_edge_tuning_disable(struct himci_host *host)
{
	u32 regval;

	regval = himci_readl(REG_EMMC_SAP_DLL_CTRL);
	regval |= SAP_DLL_CTRL_DLLMODE;
	himci_writel(regval, REG_EMMC_SAP_DLL_CTRL);

	regval = himci_readl(host->base + MCI_TUNING_CONTROL);
	regval &= ~MCI_TUNING_ENABLE_NEW_TUNING;
	himci_writel(regval, host->base + MCI_TUNING_CONTROL);
}


static void himciv300_set_sap_phase(struct himci_host *host, u32 phase)
{
	u32 regval;

	regval = himci_readl(REG_BASE_CRG + REG_PERI_CRG40);
	regval &= ~EMMC_SAP_PS_MASK;
	regval |= (phase << 12);
	himci_writel(regval, REG_BASE_CRG + REG_PERI_CRG40);
}

static void himciv300_set_dll_element(struct himci_host *host, u32 element)
{
	u32 regval;

	regval = himci_readl(REG_EMMC_SAP_DLL_CTRL);
	regval &=~SAP_DLL_CTRL_DLLSSEL;
	regval |= (element << SAP_DLL_CTRL_DLLSSEL_OFFSET);
	himci_writel(regval, REG_EMMC_SAP_DLL_CTRL);
}

static u32 himciv300_get_dll_element(struct himci_host *host)
{
	u32 regval = 0;

	regval = himci_readl(REG_EMMC_SAP_DLL_CTRL);
	return (regval & SAP_DLL_CTRL_DLLSSEL);
}

static u32 himciv300_get_phase22dot5_element(struct himci_host *host)
{
	u32 regval;
	u32 mdly_tap_flag,phase22dot5_ele;

	regval = himci_readl(REG_EMMC_SAP_DLL_STATUS);
	mdly_tap_flag = (regval & SAP_DLL_MDLY_TAP_FLAG);
	phase22dot5_ele = mdly_tap_flag/EMMC_PHASE_NUM/2;
	return phase22dot5_ele;
}

static u32 himciv300_get_sap_dll_taps(struct himci_host *host)
{
	u32 regval;

	regval = himci_readl(REG_EMMC_SAP_DLL_STATUS);
	return (regval & SAP_DLL_MDLY_TAP_FLAG);
}

static void himciv300_tuning_feedback(struct mmc_dev_t * mmc)
{
	struct himci_host *host = mmc->priv;

	hi_mci_control_cclk(host, DISABLE);
	mdelay(1);
	hi_mci_sys_reset(host);
	mdelay(1);
  	himci_writel(ALL_INT_CLR, host->base + MCI_RINTSTS);
	hi_mci_control_cclk(host, ENABLE);
	mdelay(1);
}

static int himciv300_tuning_edgedll_mode(struct mmc_dev_t *mmc, u32 opcode, int startEdge, int endEdge, int edgeNum)
{
	u32 index;
	u32 found = 0;
	u32 startp =-1, endp = -1;
	u32 curphase,lastphaseoffset = 0,phaseoffset = 0, totalphases = 0;
	u16 ele,start_ele, phase_dll_elements;
	u8 mdly_tap_flag = 0;
	int prev_err = 0, err = 0;
	struct himci_host *host = mmc->priv;

	mdly_tap_flag = himciv300_get_sap_dll_taps(host);
	phase_dll_elements = mdly_tap_flag/EMMC_PHASE_NUM;
	totalphases = phase_dll_elements*EMMC_PHASE_NUM;

	if (endEdge < startEdge)
		endEdge += EMMC_PHASE_NUM;

	phaseoffset = startEdge*phase_dll_elements;
	found = 0;
	start_ele = 2;
	for (index = startEdge; index <= endEdge; index++) {

		curphase = index%EMMC_PHASE_NUM;
		phaseoffset %= totalphases;
		/* set phase shift */
		himciv300_set_sap_phase(host, curphase);

		for (ele = start_ele; ele <= phase_dll_elements ; ele++) {

			himci_writel(ALL_INT_CLR, host->base + MCI_RINTSTS);
			himciv300_set_dll_element(host, ele);

			err = himciv300_send_tuning(mmc,opcode);

			//printf("\tphase:%02d ele:%02d error:%d\n",curphase,ele,err);

			if (!err) {
				found = 1;
			}
			if (!((index == startEdge)&&(ele == start_ele))) {
				if (err && !prev_err) {
					if(ele == start_ele)
						endp = lastphaseoffset + phase_dll_elements;
					else
						endp = phaseoffset + ele - 1;
				}

				if (!err && prev_err) {
					startp = phaseoffset + ele;
				}
			}

			if ((startp != -1) && (endp != -1))
				goto tuning_out;

			prev_err = err;
			err = 0;
		}
		lastphaseoffset = phaseoffset;
		phaseoffset += phase_dll_elements;
	}

tuning_out:

	if (found) {
		printf("scan elemnts /-:%d \\-:%d under edges /-:%d \\-:%d\n",startp,endp,startEdge,endEdge);
		if (-1 == startp)
			startp = ((startEdge + edgeNum)*phase_dll_elements)%totalphases + start_ele;
		if (-1 == endp)
			endp = startEdge*phase_dll_elements - 1;

		if (endp < startp)
			endp += totalphases;

		phaseoffset = (( startp + endp ) / 2) % totalphases;
		index = (phaseoffset / phase_dll_elements);
		ele = (phaseoffset % phase_dll_elements);
		ele = ((ele > start_ele)?ele:start_ele);

		himciv300_set_sap_phase(host, index);
		himciv300_set_dll_element(host,ele);
		emmc_samplephase = index;
		printf( "Tuning SampleClock. mix set phase:[%02d/%02d] ele:[%02d/%02d] \n",index,(EMMC_PHASE_NUM-1),ele,phase_dll_elements);
		himci_writel(ALL_INT_CLR, host->base + MCI_RINTSTS);
		return 0;
	}
	printf( "No valid phase shift! use default\n");
	return -1;
}

int himciv300_tuning_mix_mode(struct mmc_dev_t * mmc, u32 opcode)
{
	struct himci_host *host = mmc->priv;
	u32 index, regval;
	u32 found = 0,prefound = 0;
	u32 startp =-1, endp = -1;
	u32 edgeNum = 0;
	int err;

	host->tunning = 1;
	himciv300_edge_tuning_enable(host);

	for (index = 0; index < EMMC_PHASE_NUM; index++) {

		/* set phase shift */
		himciv300_set_sap_phase(host, index);
		himci_writel(ALL_INT_CLR, host->base + MCI_RINTSTS);

		err = himciv300_send_tuning(mmc,opcode);
		if (!err) {
			regval = himci_readl(host->base + MCI_TUNING_CONTROL);
			found = regval & MCI_TUNING_FIND_EDGE;
		} else {
			found = 1;
		}

		//printf("\tindex:%02d error:%d  found:%d\n",index,err,found);
		if(found){
			edgeNum++;
		}
		if (prefound && !found) {
			endp = index - 1;
		} else if (!prefound && found) {
			if(index != 0) {
				startp = index;
			}
		}

		//if ((startp != -1) && (endp != -1))
		//	break;

		prefound = found;
		found = 0;
	}

	if ((startp == -1)&&(endp == -1))
	{
		printf("unfound correct edge! check your config is correct!!\n");
		return -1;
	}else {
		printf("scan edges:%d /-:%d \\-:%d\n",edgeNum,startp,endp);
	}

	if (startp == -1)
		startp = endp - (edgeNum - 1);

	if (endp == -1)
		endp = startp + (edgeNum - 1);

	himciv300_edge_tuning_disable(host);
	err = himciv300_tuning_edgedll_mode(mmc, opcode, startp, endp, edgeNum);

	host->tunning = 0;
	return err;
}

int himciv300_tuning_edge_mode(struct mmc_dev_t * mmc, u32 opcode)
{
	struct himci_host *host = mmc->priv;
	u32 index, regval;
	u32 found = 0,prefound = 0;
	u32 startp =-1, endp = -1, prevp = 0;
	u32 phaseoffset = 0;
	u32 eleoffset = 0;
	int err = 0;
	u32 edgeNum = 0;

	host->tunning = 1;
	himciv300_edge_tuning_enable(host);

	for (index = 0; index < EMMC_PHASE_NUM; index++) {

		/* set phase shift */
		himciv300_set_sap_phase(host, index);
		himci_writel(ALL_INT_CLR, host->base + MCI_RINTSTS);

		err = himciv300_send_tuning(mmc,opcode);
		if (!err) {
			regval = himci_readl(host->base + MCI_TUNING_CONTROL);
			found = regval & MCI_TUNING_FIND_EDGE;
		} else {
			found = 1;
		}

		//printf("\tindex:%02d error:%d  found:%d\n",index,err,found);
		if(found){
			edgeNum++;
		}
		if (prefound && !found){
			endp = prevp;
		} else if (!prefound && found){
			if(index != 0){
				startp = index;
			}
		}
		if ((startp != -1) && (endp != -1))
			goto scan_out;

		prevp = index;
		prefound = found;
		found = 0;
	}

scan_out:

	if ((startp == -1)&&(endp == -1))
	{
		printf("unfound correct edge! check your config is correct!!\n");
		return -1;
	}

	if (startp == -1)
		startp = endp - (edgeNum - 1);

	if (endp == -1)
		endp = startp + (edgeNum - 1);

	if (startp > endp)
		endp += EMMC_PHASE_NUM;

	if (startp == endp) //one edge
		phaseoffset = (((startp + endp))/2)%EMMC_PHASE_NUM;
	else
		phaseoffset = (((startp + 1) + (endp + 1))/2)%EMMC_PHASE_NUM;
	phaseoffset += EMMC_PHASE_NUM/2;
	phaseoffset %= EMMC_PHASE_NUM;

	himciv300_set_sap_phase(host, phaseoffset);

	if ((startp == endp)||((endp + 1 - startp)%2)) {
		eleoffset = himciv300_get_phase22dot5_element(host);
		himciv300_set_dll_element(host,eleoffset);
	}

	printf( "Tuning SampleClock. edg set phase:[%02d/%02d] ele:[%02d/%02d] \n",phaseoffset,(EMMC_PHASE_NUM-1),eleoffset,eleoffset*2);

	himciv300_edge_tuning_disable(host);
	himci_writel(ALL_INT_CLR, host->base + MCI_RINTSTS);
	host->tunning = 0;
	return 0;
}

int himciv300_tuning_dll_mode(struct mmc_dev_t * mmc, u32 opcode)
{
	struct himci_host *host = mmc->priv;
	u32 index;
	u32 found = 0;
	u32 startp =-1, endp = -1;
	u32 phaseoffset = 0, lastphaseoffset = 0,totalphases = 0;
	u16 ele,start_ele, phase_dll_elements;
	u8 mdly_tap_flag = 0;
	int prev_err = 0, err = 0;

	mdly_tap_flag = himciv300_get_sap_dll_taps(host);
	phase_dll_elements = mdly_tap_flag/EMMC_PHASE_NUM;
	totalphases = phase_dll_elements*EMMC_PHASE_NUM;

	host->tunning = 1;
	found = 0;
	start_ele = 2;
	for (index = 0; index < EMMC_PHASE_NUM; index++) {

		/* set phase shift */
		himciv300_set_sap_phase(host, index);

		for (ele = start_ele; ele <= phase_dll_elements ; ele++) {

			himci_writel(ALL_INT_CLR, host->base + MCI_RINTSTS);
			himciv300_set_dll_element(host, ele);

			err = himciv300_send_tuning(mmc,opcode);
			//printf("\tphase:%02d  ele:%02d error:%d\n",index,ele,err);

			if (!err) {
				found = 1;
			}
			if (!((index == 0)&&(ele == start_ele))) {
				if (err && !prev_err) {
					if(ele == start_ele)
						endp = lastphaseoffset + phase_dll_elements;
					else
						endp = phaseoffset + ele - 1;
				}

				if (!err && prev_err) {
					startp = phaseoffset + ele;
				}
			}

			if ((startp != -1) && (endp != -1))
				goto tuning_out;

			prev_err = err;
			err = 0;
		}
		lastphaseoffset = phaseoffset;
		phaseoffset += phase_dll_elements;
	}

tuning_out:

	if (found) {

		if (-1 == startp)
			startp = 0;
		if (-1 == endp)
			endp = totalphases - 1;

		if (endp < startp){
			endp += totalphases;
		}

		phaseoffset = (( startp + endp ) / 2) % totalphases;

		index = (phaseoffset / phase_dll_elements);
		ele = (phaseoffset % phase_dll_elements);
		ele = ((ele > start_ele)?ele:start_ele);
		himciv300_set_sap_phase(host, index);
		himciv300_set_dll_element(host, ele);

		printf( "Tuning SampleClock. dll set phase:[%02d/%02d] ele:[%02d/%02d] \n",index,(EMMC_PHASE_NUM-1),ele,phase_dll_elements);
		emmc_samplephase = index;

		himci_writel(ALL_INT_CLR, host->base + MCI_RINTSTS);
		host->tunning = 0;
		return 0;
	}

	printf( "No valid phase shift! use default\n");
	return -1;
}

static int himciv300_tuning_normal_mode(struct mmc_dev_t * mmc, u32 opcode)
{
	struct himci_host *host = mmc->priv;
	u32 index;

	u32 found = 0, startp =-1, endp = -1;
	int prev_err, err = 0;

	host->tunning = 1;

	for (index = 0; index < EMMC_PHASE_NUM; index++) {

		/* set phase shift */
		himciv300_set_sap_phase(host,index);
		himci_writel(ALL_INT_CLR, host->base + MCI_RINTSTS);

		err = himciv300_send_tuning(mmc,opcode);
		//printf("\tphase:%02d  error:%d\n",index,err);

		if (!err) {
			found = 1;
		}
		if (index > 0) {
			if (err && !prev_err){
				endp = index - 1;
				}

			if (!err && prev_err){
				startp = index;
				}
		}

		if ((startp != -1) && (endp != -1))
			goto tuning_out;

		prev_err = err;
		err = 0;
	}

tuning_out:

	if (found) {

		if (-1 == startp)
			startp = 0;
		if (-1 == endp)
			endp = EMMC_PHASE_NUM -1;

		if (endp < startp) {
			endp += EMMC_PHASE_NUM;
		}
		index = ((startp + endp) / 2)%EMMC_PHASE_NUM;

		himciv300_set_sap_phase(host, index);
		printf( "Tuning SampleClock. nml set phase:[%02d/%02d]\n",index,(EMMC_PHASE_NUM-1));
	} else {
		printf( "No valid phase shift! use default\n");
		return -1;
	}

	host->tunning = 0;
	himci_writel(ALL_INT_CLR, host->base + MCI_RINTSTS);
	return 0;
}

int himciv300_execute_tuning(struct mmc_dev_t * mmc, u32 opcode)
{
	struct himci_host *host = mmc->priv;
 	int err = 0;

	err = himciv300_tuning_mix_mode(mmc,opcode);
	himciv300_tuning_feedback(mmc);
	if (!err) {
		host->tunning = 1;
		err = himciv300_send_tuning(mmc,opcode);
		host->tunning = 0;
	}

	err = 0;
	return err;
}

static void hi_mci_sys_init(void)
{
	unsigned int tmp_reg;

	HIMCI_DEBUG_FUN("Function Call");

	/* eMMC clock phase */
	tmp_reg = himci_readl(REG_BASE_CRG + REG_EMMC_PERI_CRG);
	tmp_reg &= ~EMMC_CLK_MASK;
	tmp_reg |= EMMC_CLK_MODE0_50M;
	himci_writel(tmp_reg, REG_BASE_CRG + REG_EMMC_PERI_CRG);

	/* eMMC soft reset */
	tmp_reg |= EMMC_SRST_REQ;
	himci_writel(tmp_reg, REG_BASE_CRG + REG_EMMC_PERI_CRG);
	udelay(1000);
	tmp_reg &= ~EMMC_SRST_REQ;
	tmp_reg |= EMMC_CKEN | EMMC_BUS_CKEN;
	himci_writel(tmp_reg, REG_BASE_CRG + REG_EMMC_PERI_CRG);

	udelay(1000);
}

static unsigned int himci_get_clock(void)
{
	unsigned int ix,clk,tmp_reg;
	unsigned int crgclk_m0[] = {
		100000000, EMMC_CLK_MODE0_100M,
		50000000, EMMC_CLK_MODE0_50M,
		25000000, EMMC_CLK_MODE0_25M,
		200000000, EMMC_CLK_MODE0_200M,
		150000000, EMMC_CLK_MODE0_150M,
		0,0,
	};
	unsigned int crgclk_m1[] = {
		50000000, EMMC_CLK_MODE1_50M,
		25000000, EMMC_CLK_MODE1_25M,
		12500000, EMMC_CLK_MODE1_12DOT5M,
		100000000, EMMC_CLK_MODE1_100M,
		150000000, EMMC_CLK_MODE1_150M,
		168750000, EMMC_CLK_MODE1_168DOT75M,
		75000000, EMMC_CLK_MODE1_75M,
		0,0,
	};
	unsigned int *crgclk;

	tmp_reg = himci_readl(REG_BASE_CRG + REG_EMMC_PERI_CRG);
	if ((tmp_reg & EMMC_CLK_MODE) == EMMC_CLK_MODE) {
		clk = EMMC_CLK_MODE1_100M;
		crgclk = crgclk_m1;
	} else {
		clk = EMMC_CLK_MODE0_100M;
		crgclk = crgclk_m0;
	}
	tmp_reg &= EMMC_CLK_MASK;

	for (ix = 0; crgclk[ix]; ix += 2) {
		if (tmp_reg == crgclk[ix+1]) {
			clk = crgclk[ix];
			break;
		}
	}

	return clk;
}

static void himci_set_timing(unsigned int timing)
{
	unsigned int ix,tmp_reg;

	if (timing == MMC_TIMING_MMC_HS) {

		unsigned int ioshare[] = {
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

		for (ix = 0; ioshare[ix] != 0xff; ix += 2) {
			tmp_reg = himci_readl( REG_BASE_IOSHARE+ioshare[ix]);
			tmp_reg &= ~(DRV_STENGTH_MASK);
			tmp_reg |= DRV_SLEV_RATE;
			tmp_reg |= ioshare[ix+1];
			himci_writel(tmp_reg, REG_BASE_IOSHARE+ioshare[ix]);
		}

		/* no config drv_strength by chip */
		tmp_reg = himci_readl(REG_BASE_CRG + REG_EMMC_PERI_CRG);
		tmp_reg &= ~(EMMC_CLK_MASK
			|EMMC_CLK_MODE
			|EMMC_DRV_PS_MASK
			|EMMC_SAP_PS_MASK);
		tmp_reg |= EMMC_CLK_MODE0_50M
			| EMMC_DRV_PS_180_90
			| EMMC_SAP_PS_45_22DOT5;
		himci_writel(tmp_reg,REG_BASE_CRG + REG_EMMC_PERI_CRG);
	}

	if (timing == MMC_TIMING_UHS_DDR50) {

		unsigned int ioshare[] = {
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

		for (ix = 0; ioshare[ix] != 0xff; ix += 2) {
			tmp_reg = himci_readl( REG_BASE_IOSHARE+ioshare[ix]);
			tmp_reg &= ~(DRV_STENGTH_MASK);
			tmp_reg |= DRV_SLEV_RATE;
			tmp_reg |= ioshare[ix+1];
			himci_writel(tmp_reg, REG_BASE_IOSHARE+ioshare[ix]);
		}

		tmp_reg = himci_readl(REG_BASE_CRG + REG_EMMC_PERI_CRG);
		tmp_reg &= ~(EMMC_CLK_MASK | EMMC_CLK_MODE | EMMC_DRV_PS_MASK |EMMC_SAP_PS_MASK);
		tmp_reg |= EMMC_CLK_MODE0_50M  | EMMC_DRV_PS_90_45;
		if (get_mmc_io_voltage() == EMMC_IO_VOL_1_8V) {
			tmp_reg |= EMMC_SAP_PS_90_45;
		} else {
			tmp_reg |= EMMC_SAP_PS_45_22DOT5;
		}
		himci_writel(tmp_reg,REG_BASE_CRG + REG_EMMC_PERI_CRG);
	}

	if (timing == MMC_TIMING_MMC_HS200) {
		unsigned int ioshare[] = {
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

		for (ix = 0; ioshare[ix] != 0xff; ix += 2) {
			tmp_reg = himci_readl( REG_BASE_IOSHARE+ioshare[ix]);
			tmp_reg &= ~(DRV_STENGTH_MASK | DRV_SLEV_RATE);
			if(ioshare[ix] != IOSHARE_OFFSET_EMMC_CLOCK) {
				tmp_reg |= DRV_SLEV_RATE;
			}
			tmp_reg |= ioshare[ix+1];
			himci_writel(tmp_reg, REG_BASE_IOSHARE+ioshare[ix]);
		}

		tmp_reg = himci_readl(REG_BASE_CRG + REG_EMMC_PERI_CRG);
		tmp_reg &= ~(EMMC_CLK_MASK|EMMC_CLK_MODE|EMMC_DRV_PS_MASK);
		tmp_reg |= EMMC_CLK_MODE0_200M | EMMC_DRV_PS_90_45;
		himci_writel(tmp_reg,REG_BASE_CRG + REG_EMMC_PERI_CRG);
	}

	if (timing == MMC_TIMING_MMC_HS400) {
		unsigned int ioshare[] = {
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

		for (ix = 0; ioshare[ix] != 0xff; ix += 2) {
			tmp_reg = himci_readl( REG_BASE_IOSHARE+ioshare[ix]);
			tmp_reg &= ~(DRV_STENGTH_MASK | DRV_SLEV_RATE);
			if (HS400_MAX_CLK == HS400_CLK_100M) {
				tmp_reg |= DRV_SLEV_RATE;
			}
			tmp_reg |= ioshare[ix+1];
			himci_writel(tmp_reg, REG_BASE_IOSHARE+ioshare[ix]);
		}

		tmp_reg = himci_readl(REG_BASE_CRG + REG_EMMC_PERI_CRG);
		tmp_reg &= ~(EMMC_CLK_MASK|EMMC_CLK_MODE|EMMC_DRV_PS_MASK | EMMC_SAP_PS_MASK);

		if (HS400_MAX_CLK == HS400_CLK_100M) {
			tmp_reg |= EMMC_CLK_MODE0_100M | EMMC_DRV_PS_90_45 | (emmc_samplephase << 12);
		} else {
			tmp_reg |= EMMC_CLK_MODE | EMMC_CLK_MODE1_150M | EMMC_DRV_PS_135_67DOT5 | (emmc_samplephase << 12);
		}
		himci_writel(tmp_reg,REG_BASE_CRG + REG_EMMC_PERI_CRG);
	}
}

static void himci_get_tuning_param(int datastrobe, unsigned int * min,
		unsigned int * max, unsigned int * mask,
		unsigned int * offset, unsigned int * reg_addr)
{
	if (datastrobe) {
		*min =1;
		*max = 16;
		*mask =0xff00;
		*offset = 8;
		*reg_addr = REG_BASE_CRG + REG_PERI_CRG164;
	} else {
		*min = 0;
		*max = EMMC_PHASE_NUM;
		*mask = EMMC_SAP_PS_MASK;
		*offset = 12;
		*reg_addr =REG_BASE_CRG + REG_PERI_CRG40;
	}
}
