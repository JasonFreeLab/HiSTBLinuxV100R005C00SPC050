/******************************************************************************
 *    Copyright (C) 2014 Hisilicon STB Development Dept
 *    All rights reserved.
 * ***
 *    Create by Lai Yingjun
 *

 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *   http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
******************************************************************************/

#include <config.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <asm/io.h>
#include <delay.h>
#include <errno.h>
#include <string.h>
#include <module.h>
#include <malloc.h>
#include <platform.h>
#include <cpuinfo.h>
#include <mmu.h>
#include "himciv200_reg.h"
#include "himciv200.h"
#include "mmc_drv.h"

#ifdef CONFIG_GENERIC_MMC
extern u32 emmc_offline;
extern u32 emmc_samplephase;
extern u32 emmc_caps2;
#endif

/*************************************************************************/
#ifdef CONFIG_ARCH_GODBOX
#  include "himciv200_godbox.c"
#endif

#if defined(CONFIG_ARCH_S40) || defined(CONFIG_ARCH_S5) || defined(CONFIG_ARCH_HI3798MX) \
    || defined(CONFIG_ARCH_HI3716MV410) || defined(CONFIG_ARCH_HI3716MV420N)
#  include "himciv200_s40.c"
#endif

#if defined(CONFIG_ARCH_HIFONE)
#  include "himciv200_hifone.c"
#endif

#if defined(CONFIG_ARCH_HI3798CV2X)
extern unsigned int get_mmc_io_voltage(void);
#  include "himciv200_hi3798cv2x.c"
#endif

/*************************************************************************/
#if defined(CONFIG_HIMCI_V100)
#  define DRIVER_NAME "himci v100"
#elif defined(CONFIG_HIMCI_V200)
#  define DRIVER_NAME "himci v200"
#endif

#if HI_MCI_DEBUG
int debug_type = HIMCI_DEBUG_TYPE;

char *get_debug_type_string(int type)
{
	if (type & HIMCI_DEBUG_TYPE_REG)
		return "REG";
	else if (type & HIMCI_DEBUG_TYPE_FUN)
		return "FUN";
	else if (type & HIMCI_DEBUG_TYPE_CMD)
		return "CMD";
	else if (type & HIMCI_DEBUG_TYPE_INFO)
		return "INFO";
	else if (type & HIMCI_DEBUG_TYPE_ERR)
		return "ERR";
	else
		return "UNKNOWN";
}
#endif

static unsigned int retry_count = MAX_RETRY_COUNT;

#define MAX_DMA_DES	20480
static struct himci_dma_des hi_dma_des[MAX_DMA_DES]
	__attribute__ ((aligned(512)));

extern unsigned int get_ca_vendor(void);
extern int mmc_read(struct mmc_dev_t *mmc_dev, uint32 start, size_t cnt, void *buf);
extern int mmc_write(struct mmc_dev_t *mmc_dev, uint32 start, size_t cnt, const void *buf);
extern int mmc_send_ext_csd(struct mmc_dev_t *mmc_dev, char *ext_csd);
extern int mmc_switch(struct mmc_dev_t *mmc_dev, uint8 set, uint8 index, uint8 value);

/*************************************************************************/

/* reset MMC host controler */
static void hi_mci_sys_reset(struct himci_host *host)
{
	unsigned int tmp_reg;
	unsigned int time_out;

	HIMCI_DEBUG_FUN("Function Call");
	HIMCI_ASSERT(host);

	tmp_reg = himci_readl(host->base + MCI_BMOD);
	tmp_reg |= BMOD_SWR;
	himci_writel(tmp_reg, host->base + MCI_BMOD);

	time_out = 10;
	do {
		tmp_reg = himci_readl(host->base + MCI_BMOD);
		mdelay(1);
	} while ((tmp_reg & BMOD_SWR) && time_out--);

	tmp_reg = himci_readl(host->base + MCI_BMOD);
	tmp_reg |= BURST_16 | BURST_INCR;
	himci_writel(tmp_reg, host->base + MCI_BMOD);

	tmp_reg = himci_readl(host->base + MCI_CTRL);
	tmp_reg |=  CTRL_RESET | FIFO_RESET | DMA_RESET;
	himci_writel(tmp_reg, host->base + MCI_CTRL);
}

static void hi_mci_ctrl_power(struct himci_host *host, int flag)
{
	HIMCI_DEBUG_FUN("Function Call: flag %d", flag);
	HIMCI_ASSERT(host);

	himci_writel(flag, host->base + MCI_PWREN);
}

static int hi_mci_wait_cmd(struct himci_host *host)
{
	unsigned int tmp_reg, wait_retry_count = 0;

	HIMCI_DEBUG_FUN("Function Call");
	HIMCI_ASSERT(host);

	do {
		tmp_reg = himci_readl(host->base + MCI_CMD);
		if ((tmp_reg & START_CMD) == 0)
			return 0;
		wait_retry_count++;
	} while (wait_retry_count < retry_count);

	HIMCI_DEBUG_INFO("CMD send timeout");

	return -1;
}

static void hi_mci_control_cclk(struct himci_host *host, unsigned int flag)
{
	unsigned int reg;
	cmd_arg_s cmd_reg;

	HIMCI_DEBUG_FUN("Function Call: flag %d", flag);
	HIMCI_ASSERT(host);

	reg = himci_readl(host->base + MCI_CLKENA);
	if (flag == ENABLE)
		reg |= CCLK_ENABLE;
	else
		reg &= ~CCLK_ENABLE;
	himci_writel(reg, host->base + MCI_CLKENA);

	cmd_reg.cmd_arg = himci_readl(host->base + MCI_CMD);
	cmd_reg.cmd_arg &= ~MCI_CMD_MASK;
	cmd_reg.bits.start_cmd = 1;
	cmd_reg.bits.update_clk_reg_only = 1;
	cmd_reg.bits.use_hold_reg = 1;
	himci_writel(cmd_reg.cmd_arg, host->base + MCI_CMD);

	if (hi_mci_wait_cmd(host) != 0)
		HIMCI_DEBUG_ERR("Disable or enable CLK is timeout");

}

static void hi_mci_set_cclk(struct himci_host *host, unsigned int cclk)
{
	unsigned int reg_value, srcclk;
	cmd_arg_s cmd_reg;

	HIMCI_DEBUG_FUN("Function Call: cclk %d", cclk);
	HIMCI_ASSERT(host);
	HIMCI_ASSERT(cclk);

	srcclk = himci_get_clock();

	/*set card clk divider value, clk_divider = Fmmcclk/(Fmmc_cclk * 2) */
	reg_value = 0;
	if (cclk < srcclk) {
		reg_value = srcclk / (cclk * 2);
		if (srcclk % (cclk * 2))
			reg_value++;
		if (reg_value > 0xFF)
			reg_value = 0xFF;
	}
	himci_writel(reg_value, host->base + MCI_CLKDIV);

	cmd_reg.cmd_arg = himci_readl(host->base + MCI_CMD);
	cmd_reg.cmd_arg &= ~MCI_CMD_MASK;
	cmd_reg.bits.start_cmd = 1;
	cmd_reg.bits.update_clk_reg_only = 1;
	cmd_reg.bits.use_hold_reg = 1;
	himci_writel(cmd_reg.cmd_arg, host->base + MCI_CMD);

	if (hi_mci_wait_cmd(host) != 0)
		HIMCI_DEBUG_ERR("Set card CLK divider is failed");
}

static void hi_mci_init_card(struct himci_host *host)
{
	unsigned int tmp_reg;

	HIMCI_DEBUG_FUN("Function Call");
	HIMCI_ASSERT(host);

	hi_mci_sys_reset(host);

	/* card reset */
	himci_writel(0, host->base + MCI_RESET_N);
	udelay(CONFIG_MMC_RESET_LOW_TIMEOUT);

	/* card power off and power on */
	hi_mci_ctrl_power(host, POWER_OFF);
	udelay(CONFIG_MMC_POWER_OFF_TIMEOUT * 1000);
	hi_mci_ctrl_power(host, POWER_ON);
	udelay(CONFIG_MMC_POWER_ON_TIMEROUT * 1000);

	/* card reset cancel */
	himci_writel(1, host->base + MCI_RESET_N);
	udelay(CONFIG_MMC_RESET_HIGH_TIMEROUT);

	/* clear MMC host intr */
	himci_writel(ALL_INT_CLR, host->base + MCI_RINTSTS);

	/* MASK MMC host intr */
	tmp_reg = himci_readl(host->base + MCI_INTMASK);
	tmp_reg &= ~ALL_INT_MASK;
	himci_writel(tmp_reg, host->base + MCI_INTMASK);

	/* enable inner DMA mode and close intr of MMC host controler */
	tmp_reg = himci_readl(host->base + MCI_CTRL);
	tmp_reg &= ~INTR_EN;
	tmp_reg |= USE_INTERNAL_DMA;
	himci_writel(tmp_reg, host->base + MCI_CTRL);

	/* enable dma intr */
	tmp_reg = himci_readl(host->base + MCI_IDINTEN);
	tmp_reg &= ~MCI_IDINTEN_MASK;
	tmp_reg = TI | RI | NI;
	himci_writel(tmp_reg, host->base + MCI_IDINTEN);

	/* set timeout param */
	himci_writel(DATA_TIMEOUT | RESPONSE_TIMEOUT, host->base + MCI_TIMEOUT);

	/* set FIFO param */
	himci_writel(BURST_SIZE | RX_WMARK | TX_WMARK, host->base + MCI_FIFOTH);

	/* only for FPGA */
#ifdef CONFIG_HI3798MV2X_FPGA
	unsigned int drv, sap;
	drv = 0x1;
	sap = 0x1;//S28:0x0(0) 0x1(45) 0x2(90) 0x3(135),T28:0x0(0) 0x1(90) 0x2(180) 0x3(270)
	tmp_reg = himci_readl(host->base + 0x108);
	tmp_reg |= (drv << 24) | (sap << 17);
	himci_writel(tmp_reg,host->base + 0x108);

	printf("drv:%x,sap:%x\n",drv,sap);
#endif
}

static void hi_mci_idma_start(struct himci_host *host, struct mmc_data *data)
{
	unsigned int tmp_reg;

	HIMCI_DEBUG_FUN("Function Call");
	HIMCI_ASSERT(host);
	HIMCI_ASSERT(data);

	himci_writel((unsigned long)host->dma_des, host->base + MCI_DBADDR);
	HIMCI_DEBUG_INFO("host->dma_des is 0x%x", (unsigned int)host->dma_des);

	tmp_reg = himci_readl(host->base + MCI_BMOD);
	tmp_reg |= BMOD_DMA_EN;
	himci_writel(tmp_reg, host->base + MCI_BMOD);
}

static void hi_mci_idma_stop(struct himci_host *host)
{
	unsigned int tmp_reg;

	HIMCI_DEBUG_FUN("Function Call");
	HIMCI_ASSERT(host);

	tmp_reg = himci_readl(host->base + MCI_BMOD);
	tmp_reg &= ~BMOD_DMA_EN;
	himci_writel(tmp_reg, host->base + MCI_BMOD);
	himci_writel(0, host->base + MCI_BYTCNT);
	himci_writel(0, host->base + MCI_BLKSIZ);
	himci_writel(0, host->base + MCI_DBADDR);
}

static int hi_mci_setup_data(struct himci_host *host, struct mmc_data *data)
{
	struct himci_dma_des *des = host->dma_des;
	unsigned long des_cnt;
	unsigned long data_size = data->blocks * data->blocksize;
	unsigned long src = (unsigned long)data->src;

	HIMCI_DEBUG_FUN("Function Call");
	HIMCI_ASSERT(host);
	HIMCI_ASSERT(data);

	if (((data_size + DMA_BUFFER_SIZE - 1) / DMA_BUFFER_SIZE) > MAX_DMA_DES) {
		HIMCI_ERROR("Data size outside the limit of DMA des, "
			    "data size: 0x%08lx, limit of DMA des: 0x%08x",
			    data_size, DMA_BUFFER_SIZE * MAX_DMA_DES);
		return -1;
	}

	des_cnt = 0;
	while (data_size) {
		des[des_cnt].idmac_des_ctrl = DMA_DES_OWN | DMA_DES_NEXT_DES;
		des[des_cnt].idmac_des_buf_addr = src;
		des[des_cnt].idmac_des_next_addr =
			(unsigned long)(des + des_cnt + 1);

		if (data_size >= DMA_BUFFER_SIZE) {
			des[des_cnt].idmac_des_buf_size = DMA_BUFFER_SIZE;
			data_size -= DMA_BUFFER_SIZE;
			src += DMA_BUFFER_SIZE;
		} else {
			des[des_cnt].idmac_des_buf_size = data_size;
			data_size = 0;
		}

		HIMCI_DEBUG_INFO("des[%ld] vaddr is 0x%X", des_cnt,
				 (unsigned int)&des[des_cnt]);
		HIMCI_DEBUG_INFO("des[%ld].idmac_des_ctrl is 0x%X", des_cnt,
				 (unsigned int)des[des_cnt].idmac_des_ctrl);
		HIMCI_DEBUG_INFO("des[%ld].idmac_des_buf_size is 0x%X",
				 des_cnt,
				 (unsigned int)des[des_cnt].idmac_des_buf_size);
		HIMCI_DEBUG_INFO("des[%ld].idmac_des_buf_addr 0x%X", des_cnt,
				 (unsigned int)des[des_cnt].idmac_des_buf_addr);
		HIMCI_DEBUG_INFO("des[%ld].idmac_des_next_addr is 0x%X",
			des_cnt,
			(unsigned int)des[des_cnt].idmac_des_next_addr);

		des_cnt++;
	}

	des[0].idmac_des_ctrl |= DMA_DES_FIRST_DES;
	des[des_cnt - 1].idmac_des_ctrl |= DMA_DES_LAST_DES;
	des[des_cnt - 1].idmac_des_next_addr = 0;

	return 0;
}

static int hi_mci_exec_cmd(struct himci_host *host, struct mmc_cmd *cmd,
			   struct mmc_data *data)
{
	volatile cmd_arg_s cmd_reg;

	HIMCI_DEBUG_FUN("Function Call");
	HIMCI_ASSERT(host);
	HIMCI_ASSERT(cmd);

	himci_writel(cmd->cmd_args, host->base + MCI_CMDARG);

	cmd_reg.cmd_arg = himci_readl(host->base + MCI_CMD);
	cmd_reg.cmd_arg &= ~MCI_CMD_MASK;
	cmd_reg.bits.use_hold_reg = 1;

	if (data) {
		cmd_reg.bits.data_transfer_expected = 1;
		if (data->flags & (MMC_DATA_WRITE | MMC_DATA_READ))
			cmd_reg.bits.transfer_mode = 0;

		if (data->flags & MMC_DATA_WRITE)
			cmd_reg.bits.read_write = 1;
		else if (data->flags & MMC_DATA_READ)
			cmd_reg.bits.read_write = 0;
	} else {
		cmd_reg.bits.data_transfer_expected = 0;
		cmd_reg.bits.transfer_mode = 0;
		cmd_reg.bits.read_write = 0;
	}

	switch (cmd->resp_type) {
	case MMC_RSP_NONE:
		cmd_reg.bits.response_expect = 0;
		cmd_reg.bits.response_length = 0;
		cmd_reg.bits.check_response_crc = 0;
		break;
	case MMC_RSP_R1:
	case MMC_RSP_R1b:
		cmd_reg.bits.response_expect = 1;
		cmd_reg.bits.response_length = 0;
		cmd_reg.bits.check_response_crc = 1;
		break;
	case MMC_RSP_R2:
		cmd_reg.bits.response_expect = 1;
		cmd_reg.bits.response_length = 1;
		cmd_reg.bits.check_response_crc = 1;
		break;
	case MMC_RSP_R3:
		cmd_reg.bits.response_expect = 1;
		cmd_reg.bits.response_length = 0;
		cmd_reg.bits.check_response_crc = 0;
		break;
	default:
		HIMCI_ERROR("unhandled response type %02x", cmd->resp_type);
		return -1;
	}

	HIMCI_DEBUG_INFO("Send cmd of card is CMD %d(0x%X)\n", cmd->cmd_index, cmd->cmd_args);

	if (cmd->cmd_index == MMC_CMD_GO_IDLE_STATE)
		cmd_reg.bits.send_initialization = 1;
	else
		cmd_reg.bits.send_initialization = 0;

	if (cmd->cmd_index == MMC_CMD_STOP_TRANSMISSION) {
		cmd_reg.bits.stop_abort_cmd = 1;
		cmd_reg.bits.wait_prvdata_complete = 0;
	} else {
		cmd_reg.bits.stop_abort_cmd = 0;
		cmd_reg.bits.wait_prvdata_complete = 1;
	}

	cmd_reg.bits.card_number = 0;
	cmd_reg.bits.cmd_index = cmd->cmd_index;
	cmd_reg.bits.send_auto_stop = 0;
	cmd_reg.bits.start_cmd = 1;
	cmd_reg.bits.update_clk_reg_only = 0;
	himci_writel(cmd_reg.cmd_arg, host->base + MCI_CMD);

	if (hi_mci_wait_cmd(host) != 0) {
		HIMCI_DEBUG_ERR("Send card cmd is failed");
		return -1;
	}
	return 0;
}

static int hi_mci_cmd_done(struct himci_host *host, unsigned int stat)
{
	struct mmc_cmd *cmd = host->cmd;

	HIMCI_DEBUG_FUN("Function Call: stat 0x%08x", stat);
	HIMCI_ASSERT(host);
	HIMCI_ASSERT(cmd);

	host->cmd = NULL;

	if (cmd->resp_type & MMC_RSP_PRESENT) {
		if (cmd->resp_type & MMC_RSP_136) {
			cmd->response[0] = himci_readl(host->base + MCI_RESP3);
			cmd->response[1] = himci_readl(host->base + MCI_RESP2);
			cmd->response[2] = himci_readl(host->base + MCI_RESP1);
			cmd->response[3] = himci_readl(host->base + MCI_RESP0);
			HIMCI_DEBUG_INFO("CMD Response of card is "
					 "%08x %08x %08x %08x",
					 cmd->response[0], cmd->response[1],
					 cmd->response[2], cmd->response[3]);
		} else {
			cmd->response[0] = himci_readl(host->base + MCI_RESP0);
			HIMCI_DEBUG_INFO("CMD Response of card is %08x",
					 cmd->response[0]);
		}
		if ((cmd->resp_type == MMC_RSP_R1)
		    || (cmd->resp_type == MMC_RSP_R1b)) {
			if (cmd->response[0] & MMC_CS_ERROR_MASK) {
				HIMCI_DEBUG_ERR("Card status stat = 0x%x"
						" is card error!",
						cmd->response[0]);
				return -1;
			}
		}
	}

	if (stat & RTO_INT_STATUS) {
		if (!host->tunning) {
			HIMCI_DEBUG_ERR("CMD status stat = 0x%x is timeout error!",
				stat);
		}
		return TIMEOUT;
	} else if (stat & (RCRC_INT_STATUS | RE_INT_STATUS)) {
		if (!host->tunning) {
			HIMCI_DEBUG_ERR("CMD status stat = 0x%x is response error!",
				stat);
		}
		return -1;
	}
	return 0;
}

static void hi_mci_data_done(struct himci_host *host, unsigned int stat)
{
	HIMCI_DEBUG_FUN("Function Call: stat 0x%08x", stat);
	HIMCI_ASSERT(host);

	if (!host->tunning) {
		if (stat & (HTO_INT_STATUS | DRTO_INT_STATUS)) {
			HIMCI_DEBUG_ERR("Data status stat = 0x%x is timeout error!",
				stat);
		} else if (stat & (EBE_INT_STATUS | SBE_INT_STATUS | FRUN_INT_STATUS
			   | DCRC_INT_STATUS)) {
			HIMCI_DEBUG_ERR("Data status stat = 0x%x is data error!", stat);
		}
	}
}

static int hi_mci_wait_cmd_complete(struct himci_host *host)
{
	unsigned int wait_retry_count = 0;
	unsigned int retry_num = retry_count;
	unsigned int reg_data = 0;
	int ret = 0;

	HIMCI_DEBUG_FUN("Function Call");
	HIMCI_ASSERT(host);

	if(host->tunning)
		retry_num = 15000;

	do {
		reg_data = himci_readl(host->base + MCI_RINTSTS);
		if (reg_data & CD_INT_STATUS) {
			ret = hi_mci_cmd_done(host, reg_data);
			return ret;
		}
		udelay(10);
		wait_retry_count++;
	} while (wait_retry_count < retry_num);

	if (!host->tunning) {
		HIMCI_DEBUG_ERR("Wait cmd complete error! irq status is 0x%x",
			reg_data);
	}

	return -1;
}

static int hi_mci_wait_data_complete(struct himci_host *host)
{
	unsigned int wait_retry_count = 0;
	unsigned int retry_num = retry_count;
	unsigned int reg_data = 0;

	HIMCI_DEBUG_FUN("Function Call");
	HIMCI_ASSERT(host);

	if(host->tunning)
		retry_num = 15000;

	do {
		reg_data = himci_readl(host->base + MCI_RINTSTS);
		if (reg_data & DTO_INT_STATUS) {
			hi_mci_idma_stop(host);
			hi_mci_data_done(host, reg_data);
			return 0;
		}
		udelay(10);
		wait_retry_count++;
	} while (wait_retry_count < retry_num);

	if (!host->tunning) {
		HIMCI_DEBUG_ERR("Wait cmd complete error! irq status is 0x%x",
			reg_data);
	}

	return -1;
}

static int hi_mci_wait_card_complete(struct himci_host *host)
{
	unsigned int wait_retry_count = 0;
	unsigned int reg_data = 0;

	HIMCI_DEBUG_FUN("Function Call");
	HIMCI_ASSERT(host);

	do {
		reg_data = himci_readl(host->base + MCI_STATUS);
		if (!(reg_data & DATA_BUSY))
			return 0;
		udelay(10);
		wait_retry_count++;
	} while (wait_retry_count < retry_count);

	HIMCI_DEBUG_ERR("Wait card complete error! status is 0x%x", reg_data);

	return -1;
}

static int hi_mci_request(struct mmc_dev_t *mmc_dev, struct mmc_cmd *cmd,
			  struct mmc_data *data)
{
	struct himci_host *host = mmc_dev->priv;
	unsigned int blk_size;
	unsigned int tmp_reg, fifo_count = 0;
	int ret = 0;

	HIMCI_DEBUG_FUN("Function Call");
	HIMCI_ASSERT(mmc_dev);
	HIMCI_ASSERT(host);
	HIMCI_ASSERT(cmd);

	host->cmd = cmd;

	himci_writel(ALL_INT_CLR, host->base + MCI_RINTSTS);

	//mmu_cache_disable();

	/* prepare data */
	if (data) {
		ret = hi_mci_setup_data(host, data);
		if (ret) {
			HIMCI_ERROR("Data setup is error!");
			goto request_end;
		}

		blk_size = data->blocks * data->blocksize;
		himci_writel(blk_size, host->base + MCI_BYTCNT);
		himci_writel(data->blocksize, host->base + MCI_BLKSIZ);

		tmp_reg = himci_readl(host->base + MCI_CTRL);
		tmp_reg |= FIFO_RESET;
		himci_writel(tmp_reg, host->base + MCI_CTRL);

		do {
			tmp_reg = himci_readl(host->base + MCI_CTRL);
			if (fifo_count > retry_count) {
				HIMCI_ERROR("FIFO reset error!");
				break;
			}
			fifo_count++;
		} while (tmp_reg & FIFO_RESET);

		/* start DMA */
		hi_mci_idma_start(host, data);
	} else {
		himci_writel(0, host->base + MCI_BYTCNT);
		himci_writel(0, host->base + MCI_BLKSIZ);
	}

	/* send command */
	ret = hi_mci_exec_cmd(host, cmd, data);
	if (ret) {
		HIMCI_ERROR("CMD execute is error!");
		goto request_end;
	}

	/* wait command send complete */
	ret = hi_mci_wait_cmd_complete(host);
	if (ret)
		goto request_end;

	/* start data transfer */
	if (data) {
		/* wait data transfer complete */
		ret = hi_mci_wait_data_complete(host);
		if (ret)
			goto request_end;
	}

	/* wait card complete */
	ret = hi_mci_wait_card_complete(host);

request_end:
	/* clear MMC host intr */
	himci_writel(ALL_INT_CLR, host->base + MCI_RINTSTS);

	//mmu_cache_enable();

	return ret;
}

static void hi_mci_set_ios(struct mmc_dev_t *mmc_dev)
{
	struct himci_host *host = mmc_dev->priv;
	unsigned int tmp_reg;

	HIMCI_DEBUG_FUN("Function Call");
	HIMCI_ASSERT(mmc_dev);
	HIMCI_ASSERT(host);

	if (mmc_dev->clock) {
		hi_mci_control_cclk(host, DISABLE);
		himci_set_timing(mmc_dev->timing);
		hi_mci_set_cclk(host, mmc_dev->clock);
		hi_mci_control_cclk(host, ENABLE);
	} else {
		hi_mci_control_cclk(host, DISABLE);
	}

	/* set bus_width */
	HIMCI_DEBUG_INFO("ios->bus_width = %d", mmc_dev->bus_width);

	tmp_reg = himci_readl(host->base + MCI_CTYPE);
	tmp_reg &= ~CARD_WIDTH_MASK;

	if (mmc_dev->bus_width == 8)
		tmp_reg |= CARD_WIDTH_8BIT;
	else if (mmc_dev->bus_width == 4)
		tmp_reg |= CARD_WIDTH_4BIT;
	else
		tmp_reg |= CARD_WIDTH_1BIT;

	himci_writel(tmp_reg, host->base + MCI_CTYPE);

	/* set UHS reg */
	tmp_reg = himci_readl(host->base + MCI_UHS_REG);
	if (mmc_dev->timing == MMC_TIMING_UHS_DDR50)
		tmp_reg |= UHS_DDR_MODE;
	else
		tmp_reg &= ~UHS_DDR_MODE;
	himci_writel(tmp_reg, host->base + MCI_UHS_REG);

#if defined(CONFIG_ARCH_HI3798CV2X)/* || defined(CONFIG_ARCH_HI3798MV2X) */
	/* enable shift */
	tmp_reg = himci_readl(host->base +MCI_ENABLE_SHIFT);
	if (mmc_dev->timing == MMC_TIMING_UHS_DDR50) {
		tmp_reg |= ENABLE_SHIFT_01;
	} else {
		tmp_reg &= ~ENABLE_SHIFT_01;
	}
	himci_writel(tmp_reg, host->base + MCI_ENABLE_SHIFT);
#endif

	/* set ddr reg */
	tmp_reg = himci_readl(host->base + MCI_DDR_REG);
	if (mmc_dev->timing == MMC_TIMING_MMC_HS400)
		tmp_reg |= ENABLE_HS400_MODE;
	else
		tmp_reg &= ~ENABLE_HS400_MODE;

	himci_writel(tmp_reg, host->base + MCI_DDR_REG);

	/* set cardthrctl reg */
	tmp_reg = himci_readl(host->base + MCI_CARDTHRCTL);
	if (mmc_dev->timing == MMC_TIMING_MMC_HS200)
		tmp_reg = READ_THRESHOLD_SIZE;
	else if (mmc_dev->timing == MMC_TIMING_MMC_HS400)
		tmp_reg = RW_THRESHOLD_SIZE;
	else
		tmp_reg = 0x0;

	himci_writel(tmp_reg, host->base + MCI_CARDTHRCTL);

}
static void hi_mci_prepare_hs400(struct mmc_dev_t *mmc_dev)
{
	struct himci_host *host = mmc_dev->priv;
	unsigned int tmp_reg;

	/* set ddr reg */
	tmp_reg = himci_readl(host->base + MCI_DDR_REG);
	tmp_reg &= ~ENABLE_HS400_MODE;
	himci_writel(tmp_reg, host->base + MCI_DDR_REG);

	/* set cardthrctl reg */
	tmp_reg = himci_readl(host->base + MCI_CARDTHRCTL);
	tmp_reg = READ_THRESHOLD_SIZE;
	himci_writel(tmp_reg, host->base + MCI_CARDTHRCTL);

}
static int hi_mci_execute_tuning(struct mmc_dev_t *mmc_dev, unsigned int datastrobe)
{
	unsigned int index = 0, min = 0, max = 0, mask = 0, offset = 0, reg_addr = 0;
	unsigned int value, tmp_reg;
	unsigned int found = 0;
	unsigned int count = 0,tuning_count=0;
	unsigned int prev_err = -1;
	unsigned int raise_point = -1;
	unsigned int fall_point = -1;
	unsigned int phase_180 = 0;
	int err = 0;
	struct himci_host *host = mmc_dev->priv;

	himci_get_tuning_param(datastrobe,&min,&max,&mask,&offset,&reg_addr);

	if (datastrobe) {
		tmp_reg = himci_readl(reg_addr);
		tmp_reg |= 0x10000;
		himci_writel(tmp_reg, reg_addr);
	}

tuning_start:
	host->tunning = 1;
	found = 0;
	count = 0;
	prev_err = -1;
	raise_point = -1;
	fall_point = -1;
	err = 0;
	tuning_count++;

	for (index = min; index < max; index++) {

		value = index;

		/* set phase shift */
		tmp_reg = himci_readl(reg_addr);
		tmp_reg &= ~mask;
		tmp_reg |= (value << offset);
		himci_writel(tmp_reg, reg_addr);

		count = 0;
		do {
			himci_writel(ALL_INT_CLR, host->base + MCI_RINTSTS);

			if (datastrobe)
				err = mmc_send_tuning(mmc_dev, MMC_CMD_SEND_EXT_CSD);
			else
				err = mmc_send_tuning(mmc_dev, MMC_CMD_SEND_TUNING_BLOCK_HS200);

			if (err)
				break;
		} while (count++ < 4);

		if (!err) {
			/* found first valid phase */
			found = 1;
		}
		if (index > min) {
			if (err && !prev_err)
				fall_point = index - 1;

			if (!err && prev_err)
				raise_point = index;
		}

		if ((raise_point != -1) && (fall_point != -1))
			goto tuning_out;

		prev_err = err;
		err = 0;
	}

tuning_out:

	if (found) {
		if (-1 == raise_point)
			raise_point = min;
		if (-1 == fall_point)
			fall_point = max-1;

		if (fall_point < raise_point) {
			value = (max + raise_point + fall_point) / 2;
			if (value >=max)
				value = value -max;
		} else
			value = (raise_point + fall_point) / 2;

		/* all sample[0-7] is ok, config 2 */
		if((!datastrobe)&&(raise_point == min)&&(fall_point == max-1)) {
			if (tuning_count < 10) {
				goto tuning_start;
#if defined(CONFIG_ARCH_HI3798CV2X) || defined(CONFIG_ARCH_HI3798MV2X) || defined(CONFIG_ARCH_HI3798MV310)
			} else if ((mmc_dev->timing == MMC_TIMING_MMC_HS400) && (tuning_count < 20)) {
				tmp_reg = himci_readl(reg_addr);
				tmp_reg |= EMMC_CLK_MODE;
				himci_writel(tmp_reg, reg_addr);

				tmp_reg = himci_readl(reg_addr);
				tmp_reg &= ~EMMC_CLK_MASK;
				tmp_reg |= EMMC_CLK_MODE1_150M;
				himci_writel(tmp_reg, reg_addr);

				tmp_reg = himci_readl(reg_addr);
				tmp_reg &= ~EMMC_DRV_PS_MASK;
				tmp_reg |= EMMC_DRV_PS_180_90;
				himci_writel(tmp_reg, reg_addr);

				phase_180 = 1;
				goto tuning_start;
#endif
			} else {
				emmc_caps2 = 0;
				host->tunning = 0;
				himci_writel(ALL_INT_CLR, host->base + MCI_RINTSTS);
				return -1;
			}
		}
#if defined(CONFIG_ARCH_HI3798CV2X) || defined(CONFIG_ARCH_HI3798MV2X) || defined(CONFIG_ARCH_HI3798MV310)
		if (phase_180 == 1) {
			if (value < 2)
				value = 6;
			else if (value < 4)
				value = 7;
			else if (value < 6)
				value = 4;
			else
				value = 5;

			tmp_reg = himci_readl(reg_addr);
			tmp_reg &= ~EMMC_CLK_MASK;
			tmp_reg |= EMMC_CLK_MODE0_150M;
			himci_writel(tmp_reg, reg_addr);

			tmp_reg = himci_readl(reg_addr);
			tmp_reg &= ~EMMC_CLK_MODE;
			himci_writel(tmp_reg, reg_addr);

			tmp_reg = himci_readl(reg_addr);
			tmp_reg &= ~EMMC_DRV_PS_MASK;
			tmp_reg |= EMMC_DRV_PS_90_45;
			himci_writel(tmp_reg, reg_addr);
		}
#endif
		tmp_reg = himci_readl(reg_addr);
		tmp_reg &= ~mask;
		tmp_reg |= (value << offset);
		himci_writel(tmp_reg,reg_addr);

		if(!datastrobe)
			emmc_samplephase = value;

		printf("Tuning %s[%d,%d],set[%d],type[%d]\n",
			datastrobe?"datastrobe":"clk_sample",
			raise_point, fall_point, value, phase_180);
	} else {
		printf("no valid %s shift! use default\n", datastrobe?"datastrobe":"clk_sample");
		if(!datastrobe)
			emmc_caps2 = 0;
		host->tunning = 0;
		himci_writel(ALL_INT_CLR, host->base + MCI_RINTSTS);
		return -1;
	}
	//use final sap phase and send a cmd again
	if (datastrobe)
		err = mmc_send_tuning(mmc_dev, MMC_CMD_SEND_EXT_CSD);
	else
		err = mmc_send_tuning(mmc_dev, MMC_CMD_SEND_TUNING_BLOCK_HS200);
	host->tunning = 0;
	himci_writel(ALL_INT_CLR, host->base + MCI_RINTSTS);

	return 0;
}

static int hi_mci_init(struct mmc_dev_t *mmc_dev)
{
	struct himci_host *host = mmc_dev->priv;

	HIMCI_DEBUG_FUN("Function Call");

	hi_mci_sys_init();
	hi_mci_init_card(host);

	return 0;
}

static void himci_shutdown(void *p)
{
	unsigned long base_addr = REG_BASE_MCI;
	unsigned int value;

	value = readl(base_addr + MCI_CTRL);
	value |= CTRL_RESET | FIFO_RESET | DMA_RESET;

	writel(value, (base_addr + MCI_CTRL));
	writel(POWER_OFF, (base_addr + MCI_PWREN));

	/* Delay 100ms, waiting for the eMMC device power off*/
	mdelay(100);
}

static int hi_mci_chk_host_ver(void)
{
	unsigned int regval;

	regval = himci_readl(REG_BASE_MCI + MCI_VERID);
	if ((regval != MCI_VERID_VALUE) && (regval != MCI_VERID_VALUE2)) {
		printf("MMC/SD controller version incorrect.\n");
		return -ENODEV;
	}

	return 0;
}

static int hi_mci_detect_dev(void)
{
	unsigned int regval;

	regval = himci_readl(REG_BASE_MCI + MCI_CDETECT);
	if (regval & 0x01) {
		return -ENODEV;
	}

	return 0;
}

struct mmc_dev_t *hi_mci_initialize(void)
{
	static struct mmc_dev_t *mmc_dev = NULL;
	static struct himci_host *host;

	int ret = 0;

	if (mmc_dev) {
		return mmc_dev;
	}

	HIMCI_DEBUG_FUN("Function Call");

	/* enable SDIO clock and clock 50MHz */
	hi_mci_sys_init();

	/* check controller version. */
	ret = hi_mci_chk_host_ver();
	if (ret < 0)
		return NULL;

	host = malloc(sizeof(struct himci_host));
	if (!host)
		return NULL;

	memset(host, 0, sizeof(struct himci_host));

	mmc_dev = &host->mmc_dev;
	mmc_dev->priv = host;

	host->base = REG_BASE_MCI;
	host->dma_des = hi_dma_des;

	snprintf(mmc_dev->name, sizeof(mmc_dev->name), DRIVER_NAME);
	mmc_dev->send_cmd = hi_mci_request;
	mmc_dev->set_ios = hi_mci_set_ios;
	mmc_dev->prepare_hs400_tuning = hi_mci_prepare_hs400;
	mmc_dev->init = hi_mci_init;
	mmc_dev->execute_tuning = hi_mci_execute_tuning;
	mmc_dev->host_caps = MMC_MODE_HS | MMC_MODE_HS_52MHz
		| MMC_MODE_4BIT | MMC_MODE_8BIT | MMC_MODE_CMD23;

#if defined(CONFIG_ARCH_HI3798MX) || defined(CONFIG_ARCH_HIFONE) || defined(CONFIG_ARCH_HI3798CV2X) || defined(CONFIG_ARCH_HI3798MV2X) || defined(CONFIG_ARCH_HI3798MV310)
	mmc_dev->host_caps |= MMC_MODE_DDR_52MHz;
#endif
#if defined(CONFIG_ARCH_HIFONE) || defined(CONFIG_ARCH_HI3798CV2X)
	mmc_dev->iovoltage = get_mmc_io_voltage();
	if (mmc_dev->iovoltage == EMMC_IO_VOL_1_8V) {
		mmc_dev->host_caps |= MMC_MODE_HS200 | MMC_MODE_HS400;
		emmc_caps2 = (MMC_MODE_HS200 | MMC_MODE_HS400)>>7;
	}
#endif
	mmc_dev->voltages = MMC_VDD_32_33 | MMC_VDD_33_34;

	mmc_dev->freq_min = MMC_CCLK_MIN;
	mmc_dev->freq_max = MMC_CCLK_MAX;
	mmc_dev->is_init = 0;

	mmc_dev->devnum = 0;
	mmc_dev->read = mmc_read;
	mmc_dev->write = mmc_write;

	return mmc_dev;
}

void check_ext_csd(struct mmc_dev_t *mmc_dev)
{
	char ext_csd[512];
	unsigned int tmp, tmp1, boot_part, boot_bus_width;

	HIMCI_DEBUG_FUN("Function Call");

	/* check bootcfg on est_csd */
	int err = mmc_send_ext_csd(mmc_dev, ext_csd);
	if (err) {
		HIMCI_ERROR("Check est_csd error!");
		return;
	}

	if (get_ca_vendor())
		boot_part = 0x1;
	else
		boot_part = 0x7;

	if (readl(REG_BASE_PERI_CTRL + REG_START_MODE) & NF_BOOTBW_MASK)
		boot_bus_width = 0x2; /* 8bits */
	else
		boot_bus_width = 0x1; /* 4bits */

	/*
	 * only s40 Architecture support reset pin
	 */
	tmp = ext_csd[EXT_CSD_RST_N_FUNCTION];
	tmp1 = ext_csd[EXT_CSD_REV];
	if ((tmp1 >= 5)
	    && ((tmp & EXT_CSD_RST_N_EN_MASK) != EXT_CSD_RST_N_ENABLED)) {
		err = mmc_switch(mmc_dev, EXT_CSD_CMD_SET_NORMAL,
				 EXT_CSD_RST_N_FUNCTION,
				 EXT_CSD_RST_N_ENABLED);
		if (err) {
			HIMCI_ERROR("Set EXT_CSD_RST_N_FUNCTION error!");
			return;
		}
	}

	tmp = ext_csd[EXT_CSD_WR_REL_PARAM];
	tmp1 = ext_csd[EXT_CSD_REV];
	if ((tmp1 >= 5)
	    && ((tmp & EXT_CSD_WR_REL_PARAM_HCR) == EXT_CSD_WR_REL_PARAM_HCR)) {
		tmp1 = ext_csd[EXT_CSD_WR_REL_SET];
		if (tmp1 != EXT_CSD_WR_REL_VALUE) {
			err = mmc_switch(mmc_dev, EXT_CSD_CMD_SET_NORMAL,
					 EXT_CSD_WR_REL_SET,
					 EXT_CSD_WR_REL_VALUE);
			if (err) {
				HIMCI_ERROR("Set EXT_CSD_WR_REL_SET error!");
				return;
			}
		}
	}

	tmp = ext_csd[EXT_CSD_BOOT_CONFIG] >> 0x3 & 0xF;
	tmp1 = ext_csd[EXT_CSD_BOOT_BUS_WIDTH] & 0x3;
	if (tmp == boot_part && tmp1 == boot_bus_width)
		return;

	if (tmp != boot_part) {
		printf("Set EXT_CSD_BOOT_CONFIG!\n");
		tmp = ext_csd[EXT_CSD_BOOT_CONFIG];
		tmp &= (~(0xF << 3));
		tmp |= (boot_part << 3);
		err = mmc_switch(mmc_dev, EXT_CSD_CMD_SET_NORMAL,
				 EXT_CSD_BOOT_CONFIG, tmp);
		if (err) {
			HIMCI_ERROR("Set EXT_CSD_BOOT_CONFIG error!");
			return;
		}
	}

	if (tmp1 != boot_bus_width) {
		printf("Set EXT_CSD_BOOT_BUS_WIDTH to 0x%X!\n", boot_bus_width);
		tmp1 = ext_csd[EXT_CSD_BOOT_BUS_WIDTH];
		tmp1 &= (~0x3);
		tmp1 |= boot_bus_width;
		err = mmc_switch(mmc_dev, EXT_CSD_CMD_SET_NORMAL,
				 EXT_CSD_BOOT_BUS_WIDTH, tmp1);
		if (err) {
			HIMCI_ERROR("set EXT_CSD_BOOT_BUS_WIDTH error!");
			return;
		}
	}

	err = mmc_send_ext_csd(mmc_dev, ext_csd);
	if (err) {
		HIMCI_ERROR("Check est_csd error!");
		return;
	}

	tmp = ext_csd[EXT_CSD_BOOT_CONFIG] >> 0x3 & 0xF;
	tmp1 = ext_csd[EXT_CSD_BOOT_BUS_WIDTH] & 0x3;

	if (tmp == boot_part && tmp1 == boot_bus_width)
		printf("EXT_CSD CONFIG OK!\n");
	else
		printf("EXT_CSD CONFIG Fail!\n");
}

int select_boot_part(struct mmc_dev_t *mmc_dev, int boot_part)
{
	char ext_csd[512];
	unsigned int tmp;

	HIMCI_DEBUG_FUN("Function Call");

	int err = mmc_send_ext_csd(mmc_dev, ext_csd);
	if (err) {
		HIMCI_ERROR("Read boot part error!");
		return -1;
	}

	boot_part = boot_part & 0x7;
	tmp = ext_csd[EXT_CSD_BOOT_CONFIG] & 0x7;
	if (tmp == boot_part)
		return 0;

	tmp = ext_csd[EXT_CSD_BOOT_CONFIG];
	tmp &= (~0x7);
	tmp |= boot_part;
	err = mmc_switch(mmc_dev, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_BOOT_CONFIG, tmp);
	if (err) {
		HIMCI_ERROR("Select boot part error!");
		return -1;
	}

	err = mmc_send_ext_csd(mmc_dev, ext_csd);
	if (err) {
		HIMCI_ERROR("Read boot part error!");
		return -1;
	}

	tmp = ext_csd[EXT_CSD_BOOT_CONFIG] & 0x7;
	if (tmp == boot_part)
		HIMCI_DEBUG_INFO("Select boot part OK!\n");
	else
		HIMCI_DEBUG_INFO("Select boot part Fail!\n");

	return (tmp == boot_part) ? 0 : -1;
}

void print_ext_csd(struct mmc_dev_t *mmc_dev)
{
	char ext_csd[512];
	unsigned int tmp;

	HIMCI_DEBUG_FUN("Function Call");

	int err = mmc_send_ext_csd(mmc_dev, ext_csd);
	if (err) {
		HIMCI_ERROR("Check est_csd error!");
		return;
	}

	HIMCI_DEBUG_INFO("Extended CSD register:");
	for (tmp = 0; tmp < 512; tmp += 8)
		HIMCI_DEBUG_INFO
		    ("%03d: %02x %02x %02x %02x %02x %02x %02x %02x", tmp,
		     ext_csd[tmp], ext_csd[tmp + 1], ext_csd[tmp + 2],
		     ext_csd[tmp + 3], ext_csd[tmp + 4], ext_csd[tmp + 5],
		     ext_csd[tmp + 6], ext_csd[tmp + 7]);
}

void print_mmcinfo(struct mmc_dev_t *mmc_dev)
{
	HIMCI_DEBUG_FUN("Function Call");

	printf("MMC/SD Card:\n");
	printf("    MID:         0x%x\n", mmc_dev->cid[0] >> 24);
	printf("    Read Block:  %d Bytes\n", mmc_dev->r_blk_len);
	printf("    Write Block: %d Bytes\n", mmc_dev->w_blk_len);
	printf("    Chip Size:   %s Bytes (%s)\n",
	       ultohstr(mmc_dev->capacity),
	       mmc_dev->high_capacity ? "High Capacity" : "Low Capacity");
	printf("    Name:        \"%c%c%c%c%c%c\"\n",
	       mmc_dev->cid[0] & 0xff,
	       (mmc_dev->cid[1] >> 24),
	       (mmc_dev->cid[1] >> 16) & 0xff,
	       (mmc_dev->cid[1] >> 8) & 0xff,
	       mmc_dev->cid[1] & 0xff,
	       mmc_dev->cid[2] >> 24);

	printf("    Chip Type:   %s\n"
	       "    Version:     %d.%d\n",
	       IS_SD(mmc_dev) ? "SD" : "MMC",
	       (mmc_dev->version >> 8) & 0xf, mmc_dev->version & 0xff);

	printf("    Speed:       %sHz\n", ultohstr(mmc_dev->speed));
	printf("    Mode:        %s\n", ((mmc_dev->timing == MMC_TIMING_MMC_HS400) ? "HS400":
		((mmc_dev->timing == MMC_TIMING_MMC_HS200)?"HS200":"DDR50")));
#if defined(CONFIG_ARCH_HIFONE) || defined(CONFIG_ARCH_HI3798CV2X) || defined(CONFIG_ARCH_HI3798MV2X) || defined(CONFIG_ARCH_HI3798MV310)
	printf("    Voltage:     %sV\n", (mmc_dev->iovoltage == EMMC_IO_VOL_1_8V)?"1.8":"3.3");
#endif
	printf("    Bus Width:   %dbit\n", mmc_dev->bus_width);
	printf("    Boot Addr:   %d Bytes\n", CONFIG_MMC_BOOT_ADDR);
}

int print_mmc_reg(struct mmc_dev_t *mmc_dev, int show_ext_csd)
{
	unsigned int tmp;
	char ext_csd[512];


	printf("OCR register: %08x\n", mmc_dev->ocr);
	printf("CID register: %08x %08x %08x %08x\n",
	       mmc_dev->cid[0], mmc_dev->cid[1], mmc_dev->cid[2], mmc_dev->cid[3]);
	printf("CSD register: %08x %08x %08x %08x\n",
	       mmc_dev->csd[0], mmc_dev->csd[1], mmc_dev->csd[2], mmc_dev->csd[3]);
	printf("RCA register: %08x\n", mmc_dev->rca);
	if (show_ext_csd) {
		int err = mmc_send_ext_csd(mmc_dev, ext_csd);
		if (err) {
			printf("send est_csd error!\n");
			return -1;
		}
		printf("Extended CSD register:\n");
		for (tmp = 0; tmp < 512; tmp += 8)
			printf("%03d: %02x %02x %02x %02x %02x %02x %02x %02x\n",
			       tmp,
			       ext_csd[tmp],
			       ext_csd[tmp+1],
			       ext_csd[tmp+2],
			       ext_csd[tmp+3],
			       ext_csd[tmp+4],
			       ext_csd[tmp+5],
			       ext_csd[tmp+6],
			       ext_csd[tmp+7]);
	}
	printf("\n");
	return 0;
}

struct mmc_dev_t *mmc_flash_init(void)
{
	struct mmc_dev_t *mmc_dev;
	int err = 0;

#if 0 //TODO: XXX
	unsigned int devs = (get_cpudevs() & DEV_EMMC_MASK);

	if (devs != DEV_EMMCV100
	    && devs != DEV_EMMCV200 && devs != DEV_EMMC_AUTO)
		return -1;
#endif
	mmu_cache_disable();

	puts("\nMMC/SD controller initialization.\n");
	mmc_dev = hi_mci_initialize();
	if (!mmc_dev)
		return NULL;

	/* check card power off pin */
	err = hi_mci_detect_dev();
	if (err < 0) {
		/* maybe SDIO_CARD_DETECT should be low */
		printf("No MMC/SD card detect when read `SDIO_CARD_DETECT` pin.\n");
		return NULL;
	}

	err = mmc_dev_init(mmc_dev);
	if (err) {
		printf("No MMC device found !\n");
		return NULL;
	}

#ifdef CONFIG_GENERIC_MMC
	emmc_offline = 0;
#endif

	print_mmcinfo(mmc_dev);

	check_ext_csd(mmc_dev);

	mmc_dev->blocksize = mmc_dev->r_blk_len < mmc_dev->w_blk_len? \
						 mmc_dev->r_blk_len : mmc_dev->w_blk_len;
	return mmc_dev;
}

static void himci_init(void *p)
{
	mmcdev_driver_init = mmc_flash_init;
}

struct module_t module_himci = {
	.priority =MODULE_PRI_DRV,
	.ptr = NULL,
	.init = himci_init,
	.exit = NULL,
	.reboot = himci_shutdown,
};
MODULE(module_himci);

