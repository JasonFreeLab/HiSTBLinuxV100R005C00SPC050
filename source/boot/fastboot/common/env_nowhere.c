/*
 * (C) Copyright 2000-2002
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * (C) Copyright 2001 Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Andreas Heppel <aheppel@sysgo.de>

 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <command.h>
#include <environment.h>
#include <linux/stddef.h>

DECLARE_GLOBAL_DATA_PTR;

extern uchar default_environment[];


void ddr_env_relocate_spec (void)
{
}

uchar ddr_env_get_char_spec (int index)
{
	return ( *((uchar *)(gd->env_addr + index)) );
}

/************************************************************************
 * Initialize Environment use
 *
 * We are still running from ROM, so data use is limited
 */
int  ddr_env_init(void)
{
	gd->env_addr  = (ulong)&default_environment[0];
	gd->env_valid = 0;

	return (0);
}

struct env_common_func_t ddr_env_cmn_func = {
	.env_init = ddr_env_init,
	.env_get_char_spec = ddr_env_get_char_spec,
	.saveenv = NULL,
	.env_relocate_spec = ddr_env_relocate_spec,
	.env_name_spec = "DDR",
	.env_media = BOOT_MEDIA_DDR,
};