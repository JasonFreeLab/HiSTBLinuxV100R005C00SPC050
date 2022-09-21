/**
 * ddr_training_custom.c
 *
 * Copyright (c) 2009-2014, HiSilicon Technologies Co., Ltd.
 * All rights reserved.
 *
 * DDR training custom implement.
 */

#include "ddr_interface.h"
#include "ddr_training_impl.h"

/**
 * ddr_cmd_prepare_copy
 * @void
 *
 * Do some prepare before copy code from DDR to SRAM.
 * Keep empty when nothing to do.
 */
void ddr_cmd_prepare_copy(void) { return; }

/**
 * ddr_cmd_site_save
 * @void
 *
 * Save site before DDR training command execute .
 * Keep empty when nothing to do.
 */
void ddr_cmd_site_save(void) { return; }

/**
 * ddr_cmd_site_restore
 * @void
 *
 * Restore site after DDR training command execute.
 * Keep empty when nothing to do.
 */
void ddr_cmd_site_restore(void) { return; }

void ddr_training_save_reg_custom(void *reg, unsigned int mask)
{
	struct tr_relate_reg *relate_reg = (struct tr_relate_reg *)reg;

	relate_reg->custom.scramb = REG_READ(0xF8AB4100);
	/* disable scramb */
	REG_WRITE(((relate_reg->custom.scramb & 0xffffff0f) | 0x50), 0xF8AB4100);
	DDR_DEBUG("Disable scramb [0xF8AB4100 = %x].", ((relate_reg->custom.scramb & 0xffffff0f) | 0x50));
}
void ddr_training_restore_reg_custom(void *reg)
{
	struct tr_relate_reg *relate_reg = (struct tr_relate_reg *)reg;
	/* restore scramb */
	REG_WRITE(relate_reg->custom.scramb, 0xF8AB4100);
	DDR_DEBUG("Restore scramb[0xF8AB4100 = %x].",
		relate_reg->custom.scramb);
}
