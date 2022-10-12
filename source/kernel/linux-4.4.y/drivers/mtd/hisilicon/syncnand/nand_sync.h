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
#ifndef NAND_SYNC_H
#define NAND_SYNC_H

/* for sync nand only. */
/* for nand chip that support sync mode only(some toggle2.0 chips). */
#define NAND_MODE_SYNC_ONLY                  0x01

#define NAND_MODE_SYNC_ONFI23                0x10
#define NAND_MODE_SYNC_ONFI30                0x20
#define NAND_MODE_SYNC_ONFI                  (NAND_MODE_SYNC_ONFI23 | NAND_MODE_SYNC_ONFI30)
#define NAND_MODE_SYNC_TOGGLE10              0x40
#define NAND_MODE_SYNC_TOGGLE20              0x80
#define NAND_MODE_SYNC_TOGGLE                (NAND_MODE_SYNC_TOGGLE10 | NAND_MODE_SYNC_TOGGLE20)
#define NAND_MODE_SYNC_TYPE_MASK             0xf1

/******************************************************************************/
#define IS_NANDC_SYNCMODE(_host)    (((_host)->flags & NAND_MODE_SYNC_ONFI23) \
				     | ((_host)->flags & NAND_MODE_SYNC_ONFI30) \
				     | ((_host)->flags & NAND_MODE_SYNC_TOGGLE10) \
				     | ((_host)->flags & NAND_MODE_SYNC_TOGGLE20))

#define IS_NAND_SYNCMODE_ONFI(_dev)   ((_dev)->flags & NAND_MODE_SYNC_ONFI)
#define IS_NAND_SYNCMODE_TOGGLE(_dev)   ((_dev)->flags & NAND_MODE_SYNC_TOGGLE)
#define IS_NAND_SYNCMODE(_dev)   (IS_NAND_SYNCMODE_ONFI(_dev) |  IS_NAND_SYNCMODE_TOGGLE(_dev))
#define IS_NAND_SYNCMODE_ONLY(_dev)    ((_dev)->flags & NAND_MODE_SYNC_ONLY)
/******************************************************************************/

#define DEFAULT_SYNCMODE_TIMING              0xaaaaaaa  //default syncmode timing
#define DEFAULT_SYNCMODE_CLOCK               75         //default syncmode clock.

#define NAND_IO_VOL_3_3V                     0
#define NAND_IO_VOL_1_8V                     1

/**************** sync nand only **********************************************/

extern struct nand_sync nand_sync_toggle_v10;
extern struct nand_sync nand_sync_toggle_v20;
extern struct nand_sync nand_sync_onfi_v23;
extern struct nand_sync nand_sync_onfi_v30;
/******************************************************************************/

struct nand_sync_timing {
	const char *name;
	u8 id[FLASH_ID_LEN];
	int id_len;

	u8 syncmode;

	unsigned int timing;
	unsigned int clock;
};
	
struct nand_sync {
	u8 type;
	int (*enable_sync)(struct flash_regop *regop);
	int (*disable_sync)(struct flash_regop *regop);
};


struct nand_sync_timing *nand_get_sync_timing(struct nand_sync_timing *nand_sync_timing,
					      u8 *id, int id_len);

struct nand_sync *nand_get_sync(char nand_sync_type);

#endif /* NAND_SYNC_H*/
