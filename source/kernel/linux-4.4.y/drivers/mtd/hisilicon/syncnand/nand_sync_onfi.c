/******************************************************************************
 *  Copyright (C) 2015 Cai Zhiyong
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Create By Cai Zhiying 2015.7.27
 *
******************************************************************************/
#include <hiflash.h>

#include "nand_sync.h"
/*****************************************************************************/

int enable_sync_onfi_v23(struct flash_regop *regop)
{
	/* B0: timing mode. 
	 * B1: 0
	 * B2: 0
	 * B3: 0
	 */
	u8 status = 0x10; //up to timing mode 4 for onfi2.3, here set to timing mode 0 by default.
	struct flash_regop_info regop_info = {0};

	/* set feature. */
	regop_info.priv = regop->priv;
	regop_info.cmd = 0xEF;
	regop_info.nr_cmd = 1;
	regop_info.addrl = 0x01;
	regop_info.addr_cycle = 1;
	regop_info.buf = &status;
	regop_info.sz_buf = 4;
	regop_info.wait_ready = true;

	regop->write_reg(&regop_info);

	return 0;
}
/*****************************************************************************/

int disable_sync_onfi_v23(struct flash_regop *regop)
{
	/* B0: timing mode. 
	 * B1: 0
	 * B2: 0
	 * B3: 0
	 */
	u8 status = 0;
	struct flash_regop_info regop_info = {0};

	/* set feature. */
	regop_info.priv = regop->priv;
	regop_info.cmd = 0xEF;
	regop_info.nr_cmd = 1;
	regop_info.addrl = 0x01;
	regop_info.addr_cycle = 1;
	regop_info.buf = &status;
	regop_info.sz_buf = 4;
	regop_info.wait_ready = true;

	regop->write_reg(&regop_info);

	return 0;
}
/*****************************************************************************/

int enable_sync_onfi_v30(struct flash_regop *regop)
{
	/* B0: timing mode. 
	 * B1: 0
	 * B2: 0
	 * B3: 0
	 */
	u8 status = 0x25; //up to timing mode 5 for onfi3.0
	struct flash_regop_info regop_info = {0};

	/* set feature. */
	regop_info.priv = regop->priv;
	regop_info.cmd = 0xEF;
	regop_info.nr_cmd = 1;
	regop_info.addrl = 0x01;
	regop_info.addr_cycle = 1;
	regop_info.buf = &status;
	regop_info.sz_buf = 4;
	regop_info.wait_ready = true;

	regop->write_reg(&regop_info);

	return 0;
}
/*****************************************************************************/

int disable_sync_onfi_v30(struct flash_regop *regop)
{
	/* B0: timing mode. 
	 * B1: 0
	 * B2: 0
	 * B3: 0
	 */
	u8 status = 0;
	struct flash_regop_info regop_info = {0};

	/* set feature. */
	regop_info.priv = regop->priv;
	regop_info.cmd = 0xEF;
	regop_info.nr_cmd = 1;
	regop_info.addrl = 0x01;
	regop_info.addr_cycle = 1;
	regop_info.buf = &status;
	regop_info.sz_buf = 4;
	regop_info.wait_ready = true;

	regop->write_reg(&regop_info);

	return 0;
}
/******************************************************************************/

struct nand_sync nand_sync_onfi_v23 = {
	.type          = NAND_MODE_SYNC_ONFI23,
	.enable_sync   = enable_sync_onfi_v23,
	.disable_sync  = disable_sync_onfi_v23,
};
/******************************************************************************/

struct nand_sync nand_sync_onfi_v30 = {
	.type          = NAND_MODE_SYNC_ONFI30,
	.enable_sync   = enable_sync_onfi_v30,
	.disable_sync  = disable_sync_onfi_v30,
};
