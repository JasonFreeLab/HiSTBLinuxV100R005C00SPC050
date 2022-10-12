/*
 * himci.c - hisilicon MMC Host driver
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/dma-mapping.h>
#include <linux/of.h>
#include <linux/mmc/host.h>
#include <linux/mmc/mmc.h>
#include <linux/mmc/card.h>
#include <linux/mmc/sd.h>
#include <linux/mmc/sdio.h>
#include <linux/delay.h>
#include <linux/hikapi.h>
#include <linux/clk.h>

#include "../version.h"
#undef  pr_fmt
#define DRVNAME "himciv200"
#define pr_fmt(fmt) DRVNAME "_%d" ": " fmt

#include "himciv300_def.h"
#include "himciv300.h"
#include "himciv300_dbg.h"
#ifndef CONFIG_64BIT
#include <mach/hardware.h>
#else
#define __io_address(x) ((void *)x)
#endif

static void himciv300_control_cclk(struct himciv300_host *host, u32 enable);
static void himciv300_host_reset(struct himciv300_host *host);
static void himciv300_idma_reset(struct himciv300_host *host);
static void himciv300_set_ldo(struct himciv300_host *host, u8 volt);

#define himci_pr_dts DBG_OUT
extern u32 emmc_boot_tuning_phase;
/*************************************************************************/

#if defined(CONFIG_ARCH_HI3798MV2X)
#include "himci_hi3798mv2x.c"
#endif

#if defined(CONFIG_ARCH_HI3796MV2X)
#include "himci_hi3796mv2x.c"
#endif

#if defined(CONFIG_ARCH_HI3798MV310)
#include "himci_hi3798mv310.c"
#endif

static u32 detect_time = HI_MCI_DETECT_TIMEOUT;
static u32 retry_count = MAX_RETRY_COUNT;
static u32 request_timeout = HI_MCI_REQUEST_TIMEOUT;
int trace_level = HIMCI_TRACE_LEVEL;
int himci_hung = 0;

module_param(himci_hung, uint, 0600);
MODULE_PARM_DESC(himci_hung, "himci drv hung when error found(default:0))");

module_param(detect_time, uint, 0600);
MODULE_PARM_DESC(detect_timer, "card detect time (default:500ms))");

module_param(retry_count, uint, 0600);
MODULE_PARM_DESC(retry_count, "retry count times (default:100))");

module_param(request_timeout, uint, 0600);
MODULE_PARM_DESC(request_timeout, "Request timeout time (default:3s))");

module_param(trace_level, int, 0600);
MODULE_PARM_DESC(trace_level, "HIMCI_TRACE_LEVEL");

/******************************************************************************/
static void himciv300_cur_status(struct himciv300_host *host)
{
	u32 biu,ciu,rint,sts,idsta;

	himci_trace(2, "begin");
	ciu = mci_readl(host, MCI_TCBCNT);
	biu = mci_readl(host, MCI_TBBCNT);
	idsta = mci_readl(host, MCI_IDSTS);
	rint = mci_readl(host, MCI_RINTSTS);
	sts = mci_readl(host, MCI_STATUS);

	himci_trace(5, " [CIU:%#X BIU:%#X RINT:%#X STS:%#X IDSTS:%#X]\n",
					ciu,biu,rint,sts,idsta);
}

static void himciv300_host_reset(struct himciv300_host *host)
{
	u32 regval;

	himci_trace(2, "begin");

	regval = mci_readl(host, MCI_BMOD);
	regval |= BMOD_SWR;
	mci_writel(host, MCI_BMOD, regval);

	mdelay(10);

	regval = mci_readl(host, MCI_BMOD);
	regval |= BURST_16 | BURST_INCR;
	mci_writel(host, MCI_BMOD, regval);

	regval = mci_readl(host, MCI_CTRL);
	regval |= CTRL_RESET | FIFO_RESET | DMA_RESET;
	mci_writel(host, MCI_CTRL, regval);
}
/******************************************************************************/

static void himciv300_host_power(struct himciv300_host *host, u32 power_on,
				 bool force)
{
	himci_trace(2, "begin");

	if (host->power_on != power_on || force) {
		if (!power_on) {
			mci_writel(host, MCI_PWREN, 0);
		} else {
			mci_writel(host, MCI_PWREN, 1);
		}

		if (in_interrupt())
			mdelay(100);
		else
			msleep(100);

		host->power_on = power_on;
	}
}
/******************************************************************************
 *1: card insert
 *0: card remove
 ******************************************************************************/

static int himciv300_get_card_detect_register(struct himciv300_host *host)
{
	u32 regval = mci_readl(host, MCI_CDETECT);

	return (regval & HIMCI_CARD0) ? 0 : 1;
}
/******************************************************************************/

static int himciv300_card_detect(struct mmc_host *mmc)
{
	struct himciv300_host *host = mmc_priv(mmc);

	if (host->force_unpluged)
		return 0;

	return himciv300_get_card_detect_register(host);
}
/******************************************************************************/

static int himciv300_wait_cmd(struct himciv300_host *host)
{
	unsigned long timeout = jiffies + msecs_to_jiffies(500);
	u32 regval = 0;
	unsigned long flags;

	while (time_before(jiffies, timeout)) {
		/*
		   Check if CMD::CMD_START bit is clear.
		   CMD_START = 0 means MMC Host controller has loaded registers
		   and next command can be loaded in.
		 */
		regval = mci_readl(host, MCI_CMD);
		if ((regval & CMD_START) == 0)
			return 0;

		/* Check if Raw_Intr_Status::HLE bit is set. */
		spin_lock_irqsave(&host->lock, flags);
		regval = mci_readl(host, MCI_RINTSTS);
		if (regval & HLE_INT_STATUS) {
			regval |= HLE_INT_STATUS;
			mci_writel(host, MCI_RINTSTS, regval);
			spin_unlock_irqrestore(&host->lock, flags);

			himci_error("hardware locked write error,Other CMD is running\n",
					host->devid);
			himciv300_host_reset(host);
			return 1;
		}
		spin_unlock_irqrestore(&host->lock, flags);
	}

	return -1;
}
/******************************************************************************/

static void himciv300_control_cclk(struct himciv300_host *host, u32 enable)
{
	u32 regval;

	himci_trace(2, "begin");

	regval = mci_readl(host, MCI_CLKENA);
	if (enable) {
		regval |= CCLK_ENABLE;
	//TODO: low power mode disable
#ifdef CONFIG_ARCH_HI3798MV310

		/*enable low power mode, if sdio interrupt not enabled*/
		if (!(mci_readl(host, MCI_INTMASK) & SDIO_INT_MASK))
			regval |= CCLK_LOW_POWER;
		else
#endif
			regval &= ~CCLK_LOW_POWER;
	} else {
		regval &= ~(CCLK_LOW_POWER | CCLK_ENABLE);
	}

	mci_writel(host, MCI_CLKENA, regval);
	mci_writel(host, MCI_CMDARG, 0);

	/*when voltage switching, We must continue to set bit 28 in CMD
	*until the change is complete
	*/
	regval = mci_readl(host, MCI_CMD);
	regval |= CMD_START | CMD_UPD_CLK | CMD_PRV_DAT_WAIT;
	mci_writel(host, MCI_CMD, regval);

	if (himciv300_wait_cmd(host) != 0)
		himci_error("disable or enable clk is timeout!", host->devid);
}
/******************************************************************************/
static void himciv300_set_cclk(struct himciv300_host *host, unsigned int cclk)
{
	u32 regval = 0;
	u32 srcclk = 0;

	himci_trace(2, "begin");

	srcclk = clk_get_rate(host->clk);

	/*set card clk divider value, clk_divider = Fmmcclk/(Fmmc_cclk * 2) */
	if (cclk < srcclk) {
		regval = srcclk / (cclk * 2);
		if (srcclk % (cclk * 2))
			regval++;
		if (regval > 0xFF)
			regval = 0xFF;
	}
	mci_writel(host, MCI_CLKDIV, regval);
	mci_writel(host, MCI_CMDARG, 0);

	/*when voltage switching, We must continue to set bit 28 in CMD
	*until the change is complete, so read from mci_cmd
	*/
	regval = mci_readl(host, MCI_CMD);
	regval |= CMD_START | CMD_UPD_CLK | CMD_PRV_DAT_WAIT;
	mci_writel(host, MCI_CMD, regval);

	if (himciv300_wait_cmd(host) != 0)
		himci_error("set card clk divider is failed!", host->devid);
}
/******************************************************************************/

static void himciv300_host_init(struct himciv300_host *host)
{
	u32 regval;
	unsigned long flags;

	himci_trace(2, "begin");

	himciv300_host_power(host, false, true);

	himciv300_host_power(host, true, true);

	/* clear MMC host intr */
	mci_writel(host, MCI_RINTSTS, ALL_INT_CLR);

	spin_lock_irqsave(&host->lock, flags);
	host->pending_events = 0;
	spin_unlock_irqrestore(&host->lock, flags);

	/* MASK MMC host intr */
	regval = mci_readl(host, MCI_INTMASK);
	regval &= ~ALL_INT_MASK;
	regval |= DTO_INT_MASK
			| CARD_DETECT_IRQ_MASK
			| CD_INT_MASK
			| VOLT_SWITCH_INT_MASK
			| SBE_INT_MASK;
	mci_writel(host, MCI_INTMASK, regval);

	/* set card read threshold */
	regval = mci_readl(host, MCI_CARDTHRCTL);
	regval |= RW_THRESHOLD_SIZE;
	mci_writel(host, MCI_CARDTHRCTL, regval);

	/* enable inner DMA mode and close intr of MMC host controler */
	regval = mci_readl(host, MCI_CTRL);
	regval &= ~INTR_EN;
	regval |= USE_INTERNAL_DMA | INTR_EN;
	mci_writel(host, MCI_CTRL, regval);

	/* set timeout param */
	regval = DATA_TIMEOUT | RESPONSE_TIMEOUT;
	mci_writel(host, MCI_TIMEOUT, regval);

	/* set FIFO param */
	regval = BURST_SIZE | RX_WMARK | TX_WMARK;
	mci_writel(host, MCI_FIFOTH, regval);
}
/******************************************************************************/

static void himciv300_detect_card(unsigned long arg)
{
	struct himciv300_host *host = (struct himciv300_host *)arg;
	unsigned int i;
	unsigned int curr_status;
	unsigned int status[3];
	unsigned int detect_retry_count = 0;
	unsigned long flags;

	while (1) {
		for (i = 0; i < 3; i++) {
			status[i] = himciv300_get_card_detect_register(host);
			udelay(10);
		}
		if ((status[0] == status[1]) && (status[0] == status[2]))
			break;
		detect_retry_count++;
		if (detect_retry_count >= retry_count) {
			pr_err("this is a dithering, card detect error!", host->devid);
			goto err;
		}
	}

	curr_status = status[0];

	spin_lock_irqsave(&host->lock, flags);
	if (!host->card_detect_change) {
		spin_unlock_irqrestore(&host->lock, flags);
		goto err ;
	}

	host->card_detect_change = 0;
	host->force_unpluged = 1;
	spin_unlock_irqrestore(&host->lock, flags);

	if (host->force_unpluged) {
		/*
		 * previous      current        force_unpluged
		 * pluged        pluged         1
		 * pluged        unpluged       0
		 * unpluged      unpluged       0
		 * unpluged      pluged         0
		 */
		if (host->card_status == CARD_UNPLUGED ||
		    curr_status == CARD_UNPLUGED)
			host->force_unpluged = 0;
		else
			curr_status = CARD_UNPLUGED;
	}

	if (curr_status != host->card_status) {
		himci_trace(2, "begin card_status = %d\n", host->card_status);
		host->card_status = curr_status;
		if (curr_status != CARD_UNPLUGED) {
			himciv300_host_init(host);
			printk(KERN_INFO "card connected!\n");
		} else {
		#ifdef CONFIG_ARCH_HI3796MV2X
			himciv300_set_ldo(host, 0);
		#endif
			himciv300_host_reset(host);
			himciv300_host_power(host,false,false);
			printk(KERN_INFO "card disconnected!\n");
		}

		mmc_detect_change(host->mmc, 0);
	}
err:
	mod_timer(&host->timer, jiffies + detect_time);
}
/******************************************************************************/

static void himciv300_idma_start(struct himciv300_host *host)
{
	u32 regval;

	himci_trace(2, "begin");

	mci_writel(host, MCI_DBADDR, host->dma_paddr);

	regval = mci_readl(host, MCI_BMOD);
	regval |= BMOD_DMA_EN;
	mci_writel(host, MCI_BMOD, regval);
}
/******************************************************************************/

static void himciv300_idma_stop(struct himciv300_host *host)
{
	u32 regval;

	himci_trace(2, "begin");

	regval = mci_readl(host, MCI_BMOD);
	regval &= ~BMOD_DMA_EN;
	mci_writel(host, MCI_BMOD, regval);
}

static void himciv300_idma_reset(struct himciv300_host *host)
{
	u32 regval;

	regval = mci_readl(host, MCI_BMOD);
	regval |= BMOD_SWR;
	mci_writel(host, MCI_BMOD, regval);

	regval = mci_readl(host, MCI_CTRL);
	regval |= FIFO_RESET | DMA_RESET;
	mci_writel(host, MCI_CTRL, regval);

	udelay(1);
	mci_writel(host,  MCI_RINTSTS, ALL_INT_CLR);
}

/******************************************************************************/

static int himciv300_setup_data(struct himciv300_host *host, struct mmc_data *data)
{
	u32 sg_phyaddr;
	unsigned int sg_length;
	unsigned int i, ret = 0;
	unsigned int data_size;
	unsigned int des_cnt;
	struct himci_des *des;

	himci_trace(2, "begin");

	host->data = data;

	if (data->flags & MMC_DATA_READ)
		host->dma_dir = DMA_FROM_DEVICE;
	else
		host->dma_dir = DMA_TO_DEVICE;

	host->dma_sg = data->sg;
	host->dma_sg_num = dma_map_sg(mmc_dev(host->mmc), data->sg,
				      data->sg_len, host->dma_dir);

	himci_trace(2, "host->dma_sg_num is %d\n", host->dma_sg_num);

	data_size = data->blksz * data->blocks;
	if (data_size > (DES_BUFFER_SIZE * MAX_DMA_DES)) {
		himci_error("mci request data_size is too big!\n", host->devid);
		ret = -1;
		goto out;
	}

	himci_trace(2, "host->dma_paddr is 0x%lX,host->dma_vaddr is 0x%p\n",
		(unsigned long)host->dma_paddr, host->dma_vaddr);

	des = (struct himci_des *)host->dma_vaddr;
	des_cnt = 0;

	for (i = 0; i < host->dma_sg_num; i++) {
		sg_length = sg_dma_len(&data->sg[i]);
		sg_phyaddr = sg_dma_address(&data->sg[i]);
		himci_trace(2, "sg[%d] sg_length is 0x%08X,"
			" sg_phyaddr is 0x%08X\n",
			i,
			(unsigned int)sg_length, (unsigned int)sg_phyaddr);
		while (sg_length) {
			des[des_cnt].idmac_des_ctrl =
				DMA_DES_OWN | DMA_DES_NEXT_DES | DMA_DES_DIC;
			des[des_cnt].idmac_des_buf_addr = sg_phyaddr;
			/* idmac_des_next_addr is paddr for dma */
			des[des_cnt].idmac_des_next_addr = host->dma_paddr +
			    (des_cnt + 1) * sizeof(struct himci_des);

			if (sg_length >= DES_BUFFER_SIZE) {
				des[des_cnt].idmac_des_buf_size = DES_BUFFER_SIZE;
				sg_length -= DES_BUFFER_SIZE;
				sg_phyaddr += DES_BUFFER_SIZE;
			} else {
				/* data alignment */
				des[des_cnt].idmac_des_buf_size = sg_length;
				sg_length = 0;
			}

			des_cnt++;
		}
	}
	des[0].idmac_des_ctrl |= DMA_DES_FIRST_DES;
	des[des_cnt - 1].idmac_des_ctrl |= DMA_DES_LAST_DES;
	des[des_cnt - 1].idmac_des_next_addr = 0;
out:
	return ret;
}
/******************************************************************************/

static int himciv300_exec_cmd(struct himciv300_host *host,
			   struct mmc_command *cmd, struct mmc_data *data)
{
	u32 regval;

	himci_trace(2, "begin");

	host->cmd = cmd;

	regval = cmd->opcode;
	regval |= CMD_USE_HOLD_REG;

	if (cmd->opcode == MMC_STOP_TRANSMISSION ||
	    cmd->opcode == MMC_GO_IDLE_STATE ||
	    cmd->opcode == MMC_GO_INACTIVE_STATE ||
	    (cmd->opcode == SD_IO_RW_DIRECT &&
	     ((cmd->arg >> 9) & 0x1FFFF) == SDIO_CCCR_ABORT)) {
		regval |= CMD_STOP;
	} else if (cmd->opcode != MMC_SEND_STATUS && data) {
		regval |= CMD_PRV_DAT_WAIT;
	}

	if (cmd->opcode == SD_SWITCH_VOLTAGE) {
		/* Special bit makes CMD11 not die */
		regval |= CMD_VOLT_SWITCH;
	}

	if (cmd->opcode == MMC_GO_IDLE_STATE) {
		regval |= CMD_INIT;
	}

	if (cmd->opcode == MMC_SELECT_CARD) {
		host->card_rca = (cmd->arg >> 16 );
	}

	if (cmd->flags & MMC_RSP_PRESENT) {
		/* We expect a response, so set this bit */
		regval |= CMD_RESP_EXP;
		if (cmd->flags & MMC_RSP_136) {
			regval |= CMD_RESP_LONG;
		}
	}

	if (cmd->flags & MMC_RSP_CRC) {
		regval |= CMD_RESP_CRC;
	}

	if (data) {
		regval |= CMD_DAT_EXP;
		if (data->flags & MMC_DATA_STREAM) {
			regval |= CMD_STRM_MODE;
		}
		if (data->flags & MMC_DATA_WRITE) {
			regval |= CMD_DAT_WR;
		}
	}

	if (data)
		himci_trace(3, "send CMD%d(0x%X), data->blocks = 0x%X\n",
			cmd->opcode, cmd->arg, data->blocks);
	else
		himci_trace(3, "send CMD%d(%X)\n",
			cmd->opcode, cmd->arg);

	mci_writel(host, MCI_CMDARG, cmd->arg);
	mci_writel(host, MCI_CMD, CMD_START | regval);

	if (himciv300_wait_cmd(host) != 0) {
		himci_error("send card cmd to CIU is failed!, CMD%u(%X)", host->devid, cmd->opcode, cmd->arg);
		return -EINVAL;
	}
	return 0;
}

/******************************************************************************/

static void himciv300_cmd_done(struct himciv300_host *host, unsigned int stat)
{
	struct mmc_command *cmd = host->cmd;
	u8 i;

	himci_trace(2, "begin");

	//host->cmd = NULL;

	for (i = 0; i < 4; i++) {
		if (mmc_resp_type(cmd) == MMC_RSP_R2)
			cmd->resp[i] = mci_readl(host, MCI_RESP3 - i * 0x4);
		else
			cmd->resp[i] = mci_readl(host, MCI_RESP0 + i * 0x4);
	}

	if (stat & RTO_INT_STATUS) {
		cmd->error = -ETIMEDOUT;
		himci_trace(3, "response timeout/interrupt stat = 0x%x, CMD%u(%X)",
			    stat, cmd->opcode, cmd->arg);
	} else if (stat & (RCRC_INT_STATUS | RE_INT_STATUS)) {
		cmd->error = -EILSEQ;
		if(!host->tunning) {
			if (stat & RCRC_INT_STATUS) {
				himci_error(" error: response CRC error (%x), CMD%u(%X)", host->devid, stat, cmd->opcode, cmd->arg);
				himciv300_cur_status(host);
			}

			if (stat & RE_INT_STATUS) {
				himci_error(" error: response error (%x), CMD%u(%X)", host->devid, stat, cmd->opcode, cmd->arg);
				himciv300_cur_status(host);
			}
		}
	}
}
/******************************************************************************/

static void himciv300_data_done(struct himciv300_host *host, unsigned int stat)
{
	struct mmc_data *data = host->data;
	struct mmc_command *cmd = host->cmd;

	himci_trace(2, "begin");

	dma_unmap_sg(mmc_dev(host->mmc), data->sg, data->sg_len, host->dma_dir);

	if (stat & (HTO_INT_STATUS | DRTO_INT_STATUS)) {
		data->error = -ETIMEDOUT;
		if (stat & HTO_INT_STATUS) {
			himci_error(" error: data starvation-by-host timeout (%x), CMD%u(%X)",
					host->devid, stat, cmd->opcode, cmd->arg);
			himciv300_cur_status(host);
		}
		if (stat & DRTO_INT_STATUS) {
			himci_error(" error: data read timeout (%x), CMD%u(%X)",
					host->devid, stat, cmd->opcode, cmd->arg);
			himciv300_cur_status(host);
		}

	} else if (stat & (EBE_INT_STATUS | SBE_INT_STATUS |
			   FRUN_INT_STATUS | DCRC_INT_STATUS)) {
		data->error = -EILSEQ;
		if(!host->tunning) {
		if (stat & EBE_INT_STATUS) {
			himci_error(" error: end-bit error (%x), CMD%u(%X)", host->devid, stat, cmd->opcode, cmd->arg);
			himciv300_cur_status(host);
		}
		if (stat & SBE_INT_STATUS) {
			himci_error(" error: start bit error (%x), CMD%u(%X)", host->devid, stat, cmd->opcode, cmd->arg);
			himciv300_cur_status(host);
		}
		if (stat & FRUN_INT_STATUS) {
			himci_error(" error: FIFO underrun/overrun error (%x), CMD%u(%X)",
					host->devid, stat, cmd->opcode, cmd->arg);
			himciv300_cur_status(host);
		}
		if (stat & DCRC_INT_STATUS) {
			himci_error(" error: data CRC error (%x), CMD%u(%X)", host->devid, stat, cmd->opcode, cmd->arg);
			himciv300_cur_status(host);
		}
		}
	}

	if (!data->error) {
		if (!host->tunning) {
			unsigned int i = 0;
			int count = 1000;
			struct himci_des *des;

			des = (struct himci_des *)host->dma_vaddr;
			for (i = 0; des[i].idmac_des_buf_size; i++) {
				if (des[i].idmac_des_ctrl & DMA_DES_LAST_DES)
					break;
			}

			while ((des[i].idmac_des_ctrl & DMA_DES_OWN) && count-- > 0) {
				himci_trace(3, "wait for DMA_DES_OWN clear.\n");
				msleep(1);
			}

			if ((des[i].idmac_des_ctrl & DMA_DES_OWN) && count <= 0)
				pr_err("wait for DMA_DES_OWN clear timeout.\n", host->devid);
		}
		data->bytes_xfered = data->blocks * data->blksz;
	} else
		data->bytes_xfered = 0;

	host->data = NULL;
}
/******************************************************************************/

static int himciv300_wait_cmd_complete(struct himciv300_host *host)
{
	struct mmc_command *cmd = host->cmd;
	unsigned long flags;
	u32 regval;
	long time = request_timeout;

	himci_trace(2, "begin");

	time = wait_event_timeout(host->intr_wait,
				test_bit(HIMCI_PEND_CD_b, &host->pending_events)
				| test_bit(HIMCI_PEND_VOLT_SWITCH_b, &host->pending_events),
				time);

	if ((time <= 0)
		&& (!test_bit(HIMCI_PEND_CD_b, &host->pending_events))
		&& (!test_bit(HIMCI_PEND_VOLT_SWITCH_b, &host->pending_events))) {
		cmd->error = -ETIMEDOUT;
		spin_lock_irqsave(&host->lock, flags);
		regval = mci_readl(host, MCI_RINTSTS);
		spin_unlock_irqrestore(&host->lock, flags);
		himci_error("wait cmd request complete is timeout!"
			"Raw interrupt status 0x%08X, CMD%u(%X)", host->devid, regval, cmd->opcode, cmd->arg);
		himciv300_cur_status(host);
		return -1;
	}

	spin_lock_irqsave(&host->lock, flags);
	regval = mci_readl(host, MCI_RINTSTS);
	if (test_bit(HIMCI_PEND_CD_b, &host->pending_events)) {
		mci_writel(host, MCI_RINTSTS, (CD_INT_STATUS | RTO_INT_STATUS |
			RCRC_INT_STATUS | RE_INT_STATUS));
		host->pending_events &= ~HIMCI_PEND_CD_m;
	} else if (test_bit(HIMCI_PEND_VOLT_SWITCH_b, &host->pending_events)) {
		host->pending_events &= ~HIMCI_PEND_VOLT_SWITCH_m;
	}
	spin_unlock_irqrestore(&host->lock, flags);

	himciv300_cmd_done(host, regval);

	return 0;
}
/******************************************************************************/

static int himciv300_wait_data_complete(struct himciv300_host *host)
{
	struct mmc_data *data = host->data;
	struct mmc_command *cmd = host->cmd;
	u32 regval;
	long time = request_timeout;
	unsigned long flags;

	himci_trace(2, "begin");

	if(host->tunning)
		time = HZ/2;

	time = wait_event_timeout(host->intr_wait,
				  test_bit(HIMCI_PEND_DTO_b,
					   &host->pending_events), time);

	if ((time <= 0)
	    && (!test_bit(HIMCI_PEND_DTO_b, &host->pending_events))) {
		data->error = -ETIMEDOUT;
		spin_lock_irqsave(&host->lock, flags);
		regval = mci_readl(host, MCI_RINTSTS);
		spin_unlock_irqrestore(&host->lock, flags);
		himci_error("wait data request complete is timeout! 0x%08X, CMD%u(%X)",
				host->devid, regval, cmd->opcode, cmd->arg);
		himciv300_idma_stop(host);
		himciv300_data_done(host, regval);
		himciv300_cur_status(host);
		return -1;
	}

	spin_lock_irqsave(&host->lock, flags);
	regval = mci_readl(host, MCI_RINTSTS);
	mci_writel(host, MCI_RINTSTS, (HTO_INT_STATUS 	| DRTO_INT_STATUS
		| EBE_INT_STATUS | SBE_INT_STATUS | FRUN_INT_STATUS
		| DCRC_INT_STATUS));

	host->pending_events &= ~HIMCI_PEND_DTO_m;
	spin_unlock_irqrestore(&host->lock, flags);

	himciv300_idma_stop(host);
	himciv300_data_done(host, regval);

	return 0;
}
/******************************************************************************/

static int himciv300_wait_card_complete(struct himciv300_host *host)
{
	u32 count = 0;
	u32 regval;
	unsigned long card_jiffies_timeout;

	himci_trace(2, "begin");

	card_jiffies_timeout = jiffies + request_timeout;
	while (1) {
		if (!time_before(jiffies, card_jiffies_timeout)) {
			himci_error("wait card ready complete is timeout!\n", host->devid);
			return -1;
		}

		do {
			regval = mci_readl(host, MCI_STATUS);
			if (!(regval & DATA_BUSY)) {
				return 0;
			}
			count++;
		} while (count < retry_count);
		schedule();
	}
}
/******************************************************************************/

static void himciv300_request(struct mmc_host *mmc, struct mmc_request *mrq)
{
	struct himciv300_host *host = mmc_priv(mmc);
	u32 blk_size, regval, fifo_count = 0;
	int ret = 0;

	himci_trace(2, "begin");

	host->mrq = mrq;

	if (host->card_status == CARD_UNPLUGED) {
		mrq->cmd->error = -ENODEV;
		goto request_end;
	}

	ret = himciv300_wait_card_complete(host);
	if (ret) {
		mrq->cmd->error = ret;
		goto request_end;
	}

	/* prepare data */
	if (mrq->data) {

		ret = himciv300_setup_data(host, mrq->data);
		if (ret) {
			mrq->data->error = ret;
			himci_error("data setup is error!", host->devid);
			goto request_end;
		}

		blk_size = mrq->data->blksz * mrq->data->blocks;
		mci_writel(host, MCI_BYTCNT, blk_size);
		mci_writel(host, MCI_BLKSIZ, mrq->data->blksz);

		regval = mci_readl(host, MCI_CTRL);
		regval |= FIFO_RESET;
		mci_writel(host, MCI_CTRL, regval);

		do {
			regval = mci_readl(host, MCI_CTRL);
			fifo_count++;
			if (fifo_count >= retry_count) {
				himci_error("fifo reset is timeout!", host->devid);
				return;
			}
		} while (regval & FIFO_RESET);

		himciv300_idma_start(host);
	} else {
		mci_writel(host, MCI_BYTCNT, 0);
		mci_writel(host, MCI_BLKSIZ, 0);
	}

	if (mrq->sbc) {
		ret = himciv300_exec_cmd(host, mrq->sbc, NULL);
		if (ret) {
			mrq->sbc->error = ret;
			goto request_end;
		}

		/* wait command send complete */
		ret = himciv300_wait_cmd_complete(host);
		if (ret) {
			mrq->sbc->error = ret;
			goto request_end;
		}
	}

	ret = himciv300_exec_cmd(host, mrq->cmd, mrq->data);
	if (ret) {
		mrq->cmd->error = ret;
		goto request_end;
	}

	/* wait command send complete */
	himciv300_wait_cmd_complete(host);

	/* start data transfer */
	if (mrq->data) {
		if (!(mrq->cmd->error)) {
			ret = himciv300_wait_data_complete(host);
		} else {
			himciv300_idma_stop(host);
		}

		if (mrq->stop && (!mrq->sbc
			|| (mrq->sbc && (mrq->cmd->error || mrq->data->error)))) {
			ret = himciv300_exec_cmd(host, host->mrq->stop,
					      NULL);
			if (ret) {
				mrq->stop->error = ret;
				goto request_end;
			}

			ret = himciv300_wait_cmd_complete(host);
			if (test_bit(HIMCI_PEND_DTO_b, &host->pending_events)) {
				regval = mci_readl(host, MCI_RINTSTS);
				mci_writel(host, MCI_RINTSTS, (HTO_INT_STATUS | DRTO_INT_STATUS
					| EBE_INT_STATUS | SBE_INT_STATUS | FRUN_INT_STATUS | DCRC_INT_STATUS));
				host->pending_events &= ~HIMCI_PEND_DTO_m;
			}

			if (ret)
				goto request_end;
		}

		if (mrq->data->flags & MMC_DATA_WRITE)
			himci_dbg_rw(host->devid, 1,  mrq->cmd->arg,
			mrq->data->blocks);

		if (mrq->data->flags & MMC_DATA_READ)
			himci_dbg_rw(host->devid, 0,  mrq->cmd->arg,
			mrq->data->blocks);
	}

request_end:

	host->mrq = NULL;
	mmc_request_done(mmc, mrq);
}
/******************************************************************************/

static void himciv300_set_ldo(struct himciv300_host *host, u8 volt)
{
	u32 regval;

	if (host->ldoaddr) {
		if (volt == MMC_SIGNAL_VOLTAGE_330) {
			regval = readl(host->ldoaddr);
			regval &= ~(SD_LDO_MASK<<host->ldo_shift);
			regval |= (SD_LDO_BYPASS | SD_LDO_ENABLE)<<host->ldo_shift;
			writel(regval, host->ldoaddr);
		} else if (volt == MMC_SIGNAL_VOLTAGE_180)  {
			regval = readl(host->ldoaddr);
			regval &= ~(SD_LDO_MASK<<host->ldo_shift);
			regval |= SD_LDO_ENABLE<<host->ldo_shift;
			writel(regval, host->ldoaddr);
		} else if (volt == MMC_SIGNAL_VOLTAGE_120) {
			regval = readl(host->ldoaddr);
			regval &= ~(SD_LDO_MASK<<host->ldo_shift);
			regval |= (SD_LDO_ENABLE | SD_LDO_VOLTAGE)<<host->ldo_shift;
			writel(regval, host->ldoaddr);
		} else {
			himci_error("NO Support this voltage\n", host->devid);
		}
	}
}
/******************************************************************************/

static int himciv300_switch_voltage(struct mmc_host *mmc,
					      struct mmc_ios *ios)
{
	struct himciv300_host *host = mmc_priv(mmc);
	u32 regval;
	long time = request_timeout;

	himci_trace(2, "begin");

	/* only support sd */
	if ((host->devid == 0) || (host->devid == 2) || (!host->ldoaddr))
		return 0;
	/*
	 * We first check whether the request is to set signalling voltage
	 * to 3.3V. If so, we change the voltage to 3.3V and return quickly.
	 */
	regval = mci_readl(host, MCI_UHS_REG);

	switch (ios->signal_voltage) {
	case MMC_SIGNAL_VOLTAGE_330:

		/* Set 1.8V Signal Enable in the MCI_UHS_REG to 1 */
		regval &= ~ENABLE_UHS_VDD_180;
		mci_writel(host, MCI_UHS_REG, regval);

		himciv300_set_ldo(host, ios->signal_voltage);

		/* Wait for 5ms */
		usleep_range(5000, 5500);

		/* 3.3V regulator output should be stable within 5 ms */
		regval = mci_readl(host, MCI_UHS_REG);
		if (!(regval & ENABLE_UHS_VDD_180))
			return 0;

		himci_error("Switching to 3.3V signalling voltage failed\n", host->devid);
		return -EAGAIN;

	case MMC_SIGNAL_VOLTAGE_180:

		/* Enable 1.8V Signal Enable in the MCI_UHS_REG */
		regval |= ENABLE_UHS_VDD_180;
		mci_writel(host, MCI_UHS_REG, regval);

		himciv300_set_ldo(host, ios->signal_voltage);

		/* Wait for 8ms */
		usleep_range(8000, 8500);

		regval = mci_readl(host, MCI_UHS_REG);
		if (regval & ENABLE_UHS_VDD_180) {
			/* Provide SDCLK again and wait for 1ms */
			himciv300_control_cclk(host, true);
			usleep_range(1000, 1500);

			/*
			 * If CMD11 return CMD down, then the card
			 * was successfully switched to 1.8V signaling.
			 */
			time = wait_event_timeout(host->intr_wait,
					test_bit(HIMCI_PEND_CD_b, &host->pending_events)
					&& test_bit(HIMCI_PEND_VOLT_SWITCH_b,
					&host->pending_events), time);
			if (time > 0) {
				host->pending_events &=
					~(HIMCI_PEND_VOLT_SWITCH_m|HIMCI_PEND_CD_m);
				return 0;
			}
		}

		himci_error("Switching to 1.8V signalling voltage failed\n", host->devid);
		return -EAGAIN;
	case MMC_SIGNAL_VOLTAGE_120:
		himciv300_set_ldo(host, ios->signal_voltage);
		return 0;
	default:
		/* No signal voltage switch required */
		return 0;
	}
}
/******************************************************************************/

static void himciv300_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct himciv300_host *host = mmc_priv(mmc);
	u32 regval;

	himci_trace(2, "begin");
	himci_trace(3, "ios->power_mode = %d ", ios->power_mode);
	himci_trace(3, "ios->clock = %d ", ios->clock);
	himci_trace(3, "ios->bus_width = %d ", ios->bus_width);
	himci_trace(3, "ios->timing = %d ", ios->timing);

	if (!ios->clock) {
		himciv300_control_cclk(host, false);
	}

	switch (ios->power_mode) {
	case MMC_POWER_OFF:
		himciv300_host_power(host, false, false);
		break;
	case MMC_POWER_UP:
	case MMC_POWER_ON:
		himciv300_host_power(host, true, false);
		break;
	}

	if (ios->clock) {
		himciv300_control_cclk(host, false);
		himciv300_set_timing(host, ios->timing);
		himciv300_set_cclk(host, ios->clock);
		himciv300_control_cclk(host, true);
	}

	/* clear bus width to 1bit first */
	regval = mci_readl(host, MCI_CTYPE);
	regval &= ~(CARD_WIDTH_0 | CARD_WIDTH_1);

	if (ios->bus_width == MMC_BUS_WIDTH_8) {
		regval |= CARD_WIDTH_0;
	} else if (ios->bus_width == MMC_BUS_WIDTH_4) {
		regval |= CARD_WIDTH_1;
	}
	mci_writel(host, MCI_CTYPE, regval);

	/* ddr uhs reg */
	regval = mci_readl(host, MCI_UHS_REG);
	if (ios->timing == MMC_TIMING_UHS_DDR50 ||
			ios->timing == MMC_TIMING_MMC_DDR52) {
		regval |= ENABLE_UHS_DDR_MODE;
	} else {
		regval &= ~ENABLE_UHS_DDR_MODE;
	}
	mci_writel(host, MCI_UHS_REG, regval);

	/* hs200/hs400 cardthrctl reg */
	regval = RW_THRESHOLD_SIZE;
	mci_writel(host, MCI_CARDTHRCTL, regval);

	/* hs400 ddr reg */
	regval = mci_readl(host, MCI_DDR_REG);
	if (ios->timing == MMC_TIMING_MMC_HS400)
		regval |= ENABLE_HS400_MODE;
	else
		regval &= ~ENABLE_HS400_MODE;
	mci_writel(host, MCI_DDR_REG, regval);
	
	/*logic:fix bug*/
#ifdef CONFIG_ARCH_HI3798MV310
	regval = mci_readl(host, MCI_GPIO);
	regval |= DTO_FIX_ENABLE;
	mci_writel(host, MCI_GPIO, regval);
#endif

}
/******************************************************************************
 *1: card readonly
 *0: card read/write
 ******************************************************************************/

static int himciv300_get_card_ro(struct mmc_host *mmc)
{
	struct himciv300_host *host = mmc_priv(mmc);
	u32 regval;

	himci_trace(2, "begin");

	regval = mci_readl(host, MCI_WRTPRT);
	regval &= HIMCI_CARD0;

	return regval;
}
/******************************************************************************/

static void himciv300_hw_reset(struct mmc_host *mmc)
{
	struct himciv300_host *host = mmc_priv(mmc);

	himci_trace(2, "begin");

	mci_writel(host, MCI_RESET_N, 0);
	/* For eMMC, minimum is 1us but give it 10us for good measure */
	udelay(10);
	mci_writel(host, MCI_RESET_N, 1);
	/* For eMMC, minimum is 200us but give it 300us for good measure */
	usleep_range(300, 1000);
}
/******************************************************************************/

static void himciv300_enable_sdio_irq(struct mmc_host *mmc, int enable)
{
	struct himciv300_host *host = mmc_priv(mmc);
	u32 regval;
	unsigned long flags;

	himci_trace(2, "begin");

	if (!in_interrupt())
		spin_lock_irqsave(&host->lock, flags);

	regval = mci_readl(host, MCI_INTMASK);
	if (enable) {
		regval |= SDIO_INT_MASK;
	} else {
		regval &= (~SDIO_INT_MASK);
	}
	mci_writel(host, MCI_INTMASK, regval);

	if (!in_interrupt())
		spin_unlock_irqrestore(&host->lock, flags);
}
/******************************************************************************/

static int himciv300_card_busy(struct mmc_host *mmc)
{
	struct himciv300_host *host = mmc_priv(mmc);
	u32 regval;

	himci_trace(2, "begin");

	regval = mci_readl(host, MCI_STATUS);
	regval &= DATA_BUSY;

	return regval;
}
/******************************************************************************/

static irqreturn_t himciv300_irq(int irq, void *dev_id)
{
	struct himciv300_host *host = dev_id;
	unsigned long flags;
	int need_wakeup = 0;
	u32 state, regval;

	spin_lock_irqsave(&host->lock, flags);
	state = mci_readl(host, MCI_MINTSTS);
	himci_trace(2, "irq state 0x%08X\n", state);

	if (state & CARD_DETECT_IRQ_STATUS) {
		mci_writel(host, MCI_RINTSTS, CARD_DETECT_IRQ_STATUS);

		host->card_detect_change = 1;
	}

	if (state & DTO_INT_STATUS) {
		regval = mci_readl(host, MCI_INTMASK);
		regval &= ~DTO_INT_MASK;
		mci_writel(host, MCI_INTMASK, regval);

		need_wakeup = 1;
		host->pending_events |= HIMCI_PEND_DTO_m;
		mci_writel(host, MCI_RINTSTS, DTO_INT_STATUS);

		regval = mci_readl(host, MCI_INTMASK);
		regval |= DTO_INT_MASK;
		mci_writel(host, MCI_INTMASK, regval);
	}

	if (state & CD_INT_STATUS) {
		regval = mci_readl(host, MCI_INTMASK);
		regval &= ~CD_INT_MASK;
		mci_writel(host, MCI_INTMASK, regval);

		need_wakeup = 1;
		host->pending_events |= HIMCI_PEND_CD_m;
		mci_writel(host, MCI_RINTSTS, CD_INT_STATUS);

		regval = mci_readl(host, MCI_INTMASK);
		regval |= CD_INT_MASK;
		mci_writel(host, MCI_INTMASK, regval);
	}

	if (state & VOLT_SWITCH_INT_STATUS) {
		regval = mci_readl(host, MCI_INTMASK);
		regval &= ~VOLT_SWITCH_INT_MASK;
		mci_writel(host, MCI_INTMASK, regval);

		need_wakeup = 1;
		host->pending_events |= HIMCI_PEND_VOLT_SWITCH_m;
		mci_writel(host, MCI_RINTSTS, VOLT_SWITCH_INT_STATUS);

		regval = mci_readl(host, MCI_INTMASK);
		regval |= VOLT_SWITCH_INT_MASK;
		mci_writel(host, MCI_INTMASK, regval);
	}

	if (state & SDIO_INT_STATUS) {
		regval = mci_readl(host, MCI_INTMASK);
		regval &= ~SDIO_INT_MASK;
		mci_writel(host, MCI_INTMASK, regval);

		mci_writel(host, MCI_RINTSTS, SDIO_INT_STATUS);
		mmc_signal_sdio_irq(host->mmc);
	}

	if (state & SBE_INT_STATUS) {
		host->pending_events |= HIMCI_PEND_DTO_m;
		mci_writel(host, MCI_RINTSTS, SBE_INT_STATUS);
		need_wakeup = 1;
	}

	spin_unlock_irqrestore(&host->lock, flags);

	if (need_wakeup)
		wake_up(&host->intr_wait);

	return IRQ_HANDLED;
}
/******************************************************************************/

static const struct mmc_host_ops himci_ops = {
	.request = himciv300_request,
	.set_ios = himciv300_set_ios,
	.get_ro = himciv300_get_card_ro,
	.get_cd = himciv300_card_detect,
	.enable_sdio_irq = himciv300_enable_sdio_irq,
	.start_signal_voltage_switch = himciv300_switch_voltage,
	.card_busy = himciv300_card_busy,
	.execute_tuning = himciv300_execute_tuning,
	.prepare_hs400_tuning = himciv300_prepare_hs400,
	.select_drive_strength = NULL,
	.hw_reset = himciv300_hw_reset,
};
/******************************************************************************/

static int __init himciv300_pltm_probe(struct platform_device *pdev)
{
	int ret;
	struct resource *res;
	struct mmc_host *mmc;
	struct himciv300_host *host = NULL;
	struct device_node *np = pdev->dev.of_node;
	u32 ldo_addr = 0;

	himci_trace(2, "begin");

	mmc = mmc_alloc_host(sizeof(struct himciv300_host), &pdev->dev);
	if (!mmc) {
		printk(KERN_ERR "failed to allocate mmc_host\n");
		ret = -ENOMEM;
		goto out;
	}

	platform_set_drvdata(pdev, mmc);

	mmc->ops = &himci_ops;
	mmc->f_min = 60000;
	mmc->max_segs = PAGE_SIZE / sizeof(struct himci_des);
	mmc->max_blk_size = 65536;
	mmc->max_blk_count = mmc->max_segs;
	mmc->max_seg_size = 0x1000;
	mmc->max_req_size = mmc->max_seg_size * mmc->max_segs;
	mmc->ocr_avail = MMC_VDD_32_33 | MMC_VDD_33_34;

	himci_trace(3, "Max Block Size: %u\n", mmc->max_blk_size);
	himci_trace(3, "Max Block Count: %u\n", mmc->max_blk_count);
	himci_trace(3, "Max Block Queue Segments: %u\n", mmc->max_segs);
	himci_trace(3, "Max Block Queue Segment Size: %u\n", mmc->max_seg_size);
	himci_trace(3, "Max Bytes in One Request: %u\n", mmc->max_req_size);
	himci_trace(3, "\n");

	host = mmc_priv(mmc);
	host->mmc = mmc;
	host->dev = &pdev->dev;
	host->devid = mmc->index;

	/* mmc_of_parse have some ugly printf */
	if (of_property_read_u32(np, "caps", &mmc->caps))
		mmc->caps = MMC_CAP_4_BIT_DATA | MMC_CAP_SD_HIGHSPEED | MMC_CAP_MMC_HIGHSPEED;

	of_property_read_u32(np, "caps2", &mmc->caps2);
	of_property_read_u32(np, "max-frequency", &mmc->f_max);

#if defined(CONFIG_ARCH_HI3798MV2X)
	/* not support sdio3.0 on hi3798mv200 DMS board sdio0 */
	{
		void __iomem *reg_board_type;
		u32 regval;
		reg_board_type = ioremap_nocache(REG_BOARD_TYPE, sizeof(u32));
		if (!reg_board_type) {
			printk("%s %s iomap fail\n",__func__,dev_name(host->dev));
			return;
		}

		regval = readl(reg_board_type);
		regval &= (0x1<<30);
		iounmap(reg_board_type);

		if ((regval) &&(strcmp(dev_name(&pdev->dev), "f9820000.himciv200.SD") == 0)) {
			mmc->caps &= ~(MMC_CAP_UHS_SDR12 | MMC_CAP_UHS_SDR25 |
					MMC_CAP_UHS_SDR50 | MMC_CAP_UHS_SDR104);
		}
	}
#endif

	if (of_property_read_u32(np, "ldo-addr", &ldo_addr) == 0) {
		host->ldoaddr = ioremap_nocache(ldo_addr, 4);
		if (IS_ERR_OR_NULL(host->ldoaddr)) {
			printk(KERN_ERR "ldoaddr remap failed.\n");
			ret = PTR_ERR(host->ldoaddr);
			goto out;
		}
		of_property_read_u32(np, "ldo-shift", &host->ldo_shift);
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	host->ioaddr = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR_OR_NULL(host->ioaddr)) {
		printk(KERN_ERR "ioaddr remap failed.\n");
		ret = PTR_ERR(host->ioaddr);
		goto out;
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	host->ioshare_addr = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR_OR_NULL(host->ioshare_addr)) {
		printk(KERN_ERR "ioshare_addr remap failed.\n");
		ret = PTR_ERR(host->ioshare_addr);
		goto out;
	}

	host->iovoltage = get_mmc_io_voltage();

	host->irq = platform_get_irq(pdev, 0);
	if (host->irq < 0) {
		printk(KERN_ERR "%s: no irq defined\n", pdev->name);
		ret = -ENODEV;
		goto out;
	}

	host->dma_vaddr = dma_alloc_coherent(&pdev->dev, PAGE_SIZE,
		&host->dma_paddr, GFP_KERNEL);
	if (!host->dma_vaddr) {
		printk(KERN_ERR "dma_alloc_coherent fail.\n");
		ret = -ENOMEM;
		goto out;
	}

	host->clk = devm_clk_get(&pdev->dev, "clk");
	if (IS_ERR_OR_NULL(host->clk)) {
		printk(KERN_ERR "%s: get clock fail.\n", pdev->name);
		ret = PTR_ERR(host->clk);
		goto out;
	}

	clk_prepare_enable(host->clk);

	spin_lock_init(&host->lock);

	himciv300_host_init(host);

	host->card_detect_change = 0;
	host->force_unpluged = 0;
	host->card_status = himciv300_card_detect(host->mmc);
	if (!host->card_status) {
		printk(KERN_NOTICE "%s: eMMC/MMC/SD Device NOT detected!\n",
			pdev->name);
	}
	init_timer(&host->timer);

	host->timer.function = himciv300_detect_card;
	host->timer.data = (unsigned long)host;
	host->timer.expires = jiffies + detect_time;

	add_timer(&host->timer);

	init_waitqueue_head(&host->intr_wait);

	ret = request_irq(host->irq, himciv300_irq, 0, DRVNAME, host);
	if (ret) {
		printk(KERN_ERR "request_irq error!\n");
		goto out;
	}

	mmc_add_host(mmc);

	/* only support eMMC */
	if (host->devid == 0) {
		himci_dbg_init(host->devid);
	}

	return 0;

out:
	if (host) {
		if (host->ioaddr)
			iounmap(host->ioaddr);
		if (host->ioshare_addr)
			iounmap(host->ioshare_addr);
		if (host->ldoaddr)
			iounmap(host->ldoaddr);
		if (host->dma_vaddr)
			dma_free_coherent(&pdev->dev, PAGE_SIZE,
					  host->dma_vaddr, host->dma_paddr);
	}
	if (mmc)
		mmc_free_host(mmc);
	return ret;
}
/******************************************************************************/

static int himciv300_pltm_remove(struct platform_device *pdev)
{
	struct mmc_host *mmc = platform_get_drvdata(pdev);
	struct himciv300_host *host;
	int ret = 0;

	himci_trace(2, "begin");

	platform_set_drvdata(pdev, NULL);

	if (mmc) {
		host = mmc_priv(mmc);

		free_irq(host->irq, host);
		del_timer_sync(&host->timer);
		mmc_remove_host(mmc);
		himciv300_host_power(host, false, false);
		himciv300_control_cclk(host, false);
		if (host->ioaddr)
			iounmap(host->ioaddr);
		if (host->ioshare_addr)
			iounmap(host->ioshare_addr);
		if (host->ldoaddr)
			iounmap(host->ldoaddr);
		if (host->dma_vaddr)
			dma_free_coherent(&pdev->dev, PAGE_SIZE, host->dma_vaddr,
				  host->dma_paddr);
		mmc_free_host(mmc);
	}

	return ret;
}
/******************************************************************************/

static void himciv300_pltm_shutdown(struct platform_device *pdev)
{
	struct mmc_host *mmc = platform_get_drvdata(pdev);
	struct himciv300_host *host;
	struct device_node *np = pdev->dev.of_node;
	u32 regval;

	himci_trace(2, "begin");

	if (mmc) {
		host = mmc_priv(mmc);

		/* If Hi3798mx && sdio1, not shutdown here, reset card befor wdg. */
		if ((of_device_is_compatible(np, "hi3798mv100,himciv200"))
			&& (strcmp(dev_name(&pdev->dev), "f9830000.himciv200.MMC") == 0)) {
			return;
		}

		regval = mci_readl(host, MCI_CTRL);
		regval |= CTRL_RESET | FIFO_RESET | DMA_RESET;
		mci_writel(host, MCI_CTRL, regval);

		himciv300_host_power(host, false, false);
	}
}
/******************************************************************************/

#ifdef CONFIG_PM
static int himciv300_pltm_suspend(struct platform_device *pdev, pm_message_t state)
{
	struct mmc_host *mmc = platform_get_drvdata(pdev);
	struct himciv300_host *host ;
	int ret = 0;

	himci_trace(2, "begin");

	if (mmc) {
		host = mmc_priv(mmc);
		del_timer_sync(&host->timer);

		clk_disable_unprepare(host->clk);
	}

	return ret;
}
/******************************************************************************/

static int himciv300_pltm_resume(struct platform_device *pdev)
{
	struct mmc_host *mmc = platform_get_drvdata(pdev);
	struct himciv300_host *host;
	int ret = 0, status = 0;

	himci_trace(2, "begin");

	if (mmc) {
		host = mmc_priv(mmc);

		clk_prepare_enable(host->clk);

		himciv300_host_init(host);

		/* after suspend uplug sd, host can't scan */
		status = himciv300_get_card_detect_register(host);
		if (host->card_status != status)
			host->card_detect_change = 1;

		add_timer(&host->timer);
	}

	return ret;
}
#else
#define himciv300_pltm_suspend    NULL
#define himciv300_pltm_resume     NULL
#endif
/******************************************************************************/

static const struct of_device_id
himciv300_match[] __maybe_unused = {
	{ .compatible = "hi3798mv200,himciv200", },
	{ .compatible = "hi3796mv200,himciv200", },
#ifndef CONFIG_TEE
	{ .compatible = "hi3798mv200,himciv300_sd", },
#endif
	{},
};
MODULE_DEVICE_TABLE(of, hi3716cv200_himciv300_match);

static struct platform_driver himciv300_pltfm_driver = {
	.probe = himciv300_pltm_probe,
	.remove = himciv300_pltm_remove,
	.shutdown = himciv300_pltm_shutdown,
	.suspend = himciv300_pltm_suspend,
	.resume = himciv300_pltm_resume,
	.driver = {
		.name = DRVNAME,
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(himciv300_match),
	},
};
/******************************************************************************
 * sdio wifi interface
 * get mmc_host by driver_find_device
 ******************************************************************************/

struct device_driver *himciv300_get_driver(void)
{
	return &himciv300_pltfm_driver.driver;
}

EXPORT_SYMBOL(himciv300_get_driver);
/******************************************************************************/

static int __init himciv300_module_init(void)
{
	printk("registered new interface driver himci%s\n", HIMCI_VERSION_STRING);

	return platform_driver_register(&himciv300_pltfm_driver);
}
module_init(himciv300_module_init);
/******************************************************************************/

static void __exit himciv300_module_exit(void)
{
	platform_driver_unregister(&himciv300_pltfm_driver);
}
module_exit(himciv300_module_exit);

MODULE_AUTHOR("Hisilicon");
MODULE_DESCRIPTION("MMC/SD driver for the Hisilicon MMC/SD Host Controller");
MODULE_LICENSE("GPL");
