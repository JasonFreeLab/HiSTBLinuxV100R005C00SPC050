/* rc-atto.c - Keytable for Atto remotes
 *
 * Copyright (c) 2018 by Leandro Tavares de Melo <leandrotsampa@yahoo.com.br>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <media/rc-map.h>
#include <linux/module.h>

/*
 * Initial mapping is for the Atto remote included in almost Atto bundles,
 * which also ships with a Atto-branded IR transceiver, supported by the mceusb
 * driver. Note that the remote uses an NEC-ish protocol, but instead of having
 * a command/not_command pair, it has a vendor ID of 0xa10c, but some keys, the
 * NEC extended checksums do pass, so the table presently has the intended
 * values and the checksum-passed versions for those keys.
 */
static struct rc_map_table atto[] = {
/* Atto Pixel */
	{ 0x7d3721, KEY_UP },
	{ 0x7d3725, KEY_DOWN },
	{ 0x7d3724, KEY_RIGHT },
	{ 0x7d3722, KEY_LEFT },
	{ 0x7d3723, KEY_OK },
	{ 0x7d37a8, KEY_EXIT },
	{ 0x7d37a6, KEY_MENU },
	{ 0x7d37a0, KEY_POWER },
	{ 0x7d37d0, KEY_HOME },
	{ 0x7d37c4, KEY_VOLUMEUP },
	{ 0x7d37c5, KEY_VOLUMEDOWN },
	{ 0x7d3731, KEY_MUTE },
	{ 0x7d3701, KEY_1 },
	{ 0x7d3702, KEY_2 },
	{ 0x7d3703, KEY_3 },
	{ 0x7d3704, KEY_4 },
	{ 0x7d3705, KEY_5 },
	{ 0x7d3706, KEY_6 },
	{ 0x7d3707, KEY_7 },
	{ 0x7d3708, KEY_8 },
	{ 0x7d3709, KEY_9 },
	{ 0x7d3700, KEY_0 },
	{ 0x7d37c0, KEY_RED },
	{ 0x7d37c1, KEY_GREEN },
	{ 0x7d37c2, KEY_YELLOW },
	{ 0x7d37c3, KEY_BLUE },
	{ 0x7d37b1, KEY_SEARCH },
	{ 0x7d3753, KEY_REWIND },
	{ 0x7d3754, KEY_FORWARD },
	{ 0x7d3757, KEY_STOP },
	{ 0x00ff95, KEY_SETUP },
	{ 0x7d37a1, KEY_INFO },
	{ 0x7d37a2, KEY_AUDIO },
	{ 0x7d37b8, KEY_SUBTITLE },
	{ 0x7d37a9, KEY_BACKSPACE },
	{ 0x7d3752, KEY_PLAY },
	{ 0x7d3758, KEY_PAUSE },
	{ 0x7d37ac, KEY_FAVORITES },
	{ 0x7d3761, KEY_CHANNELUP },
	{ 0x7d3762, KEY_CHANNELDOWN },
	{ 0x00ff86, KEY_PAGEDOWN },
	{ 0x00ff85, KEY_PAGEUP },
	{ 0x00ff9f, KEY_FN_1 },
	{ 0x00ffc6, KEY_FN_2 },
	{ 0x00ff9b, KEY_FN_D },
	{ 0x00ff9a, KEY_FN_E },
	{ 0x00ffc0, KEY_FN_F },
	{ 0x00ff82, KEY_FN_B },
	{ 0x00ff65, KEY_LAST },
	{ 0x7d3751, KEY_RECORD },
	{ 0x7d37aa, KEY_SAT },
	{ 0x7d37d1, KEY_TV },
	{ 0x7d37a7, KEY_EPG },
	{ 0x7d37a3, KEY_TIME },
	{ 0x7d37b7, KEY_TEXT },
	{ 0x7d370d, KEY_RADIO },
	{ 0x7d37d2, KEY_FN_S },

/* Atto Pixel Premium */
	{ 0x200812, KEY_UP },
	{ 0x200813, KEY_DOWN },
	{ 0x200816, KEY_RIGHT },
	{ 0x200814, KEY_LEFT },
	{ 0x200815, KEY_ENTER },
	{ 0x200810, KEY_EXIT },
	{ 0x200857, KEY_MENU },
	{ 0x200800, KEY_POWER },
	{ 0x200811, KEY_HOME },
	{ 0x200802, KEY_VOLUMEUP },
	{ 0x200803, KEY_VOLUMEDOWN },
	{ 0x200804, KEY_MUTE },
	{ 0x20081c, KEY_1 },
	{ 0x20081d, KEY_2 },
	{ 0x20081e, KEY_3 },
	{ 0x200840, KEY_4 },
	{ 0x200841, KEY_5 },
	{ 0x200842, KEY_6 },
	{ 0x200844, KEY_7 },
	{ 0x200845, KEY_8 },
	{ 0x200846, KEY_9 },
	{ 0x200847, KEY_0 },
	{ 0x200818, KEY_RED },
	{ 0x200819, KEY_GREEN },
	{ 0x20081a, KEY_YELLOW },
	{ 0x20081b, KEY_BLUE },
	{ 0x200849, KEY_REWIND },
	{ 0x20084a, KEY_FORWARD },
	{ 0x20084d, KEY_STOP },
	{ 0x200850, KEY_INFO },
	{ 0x20080b, KEY_AUDIO },
	{ 0x20080f, KEY_SUBTITLE },
	{ 0x20080c, KEY_BACK },
	{ 0x20084e, KEY_PLAYPAUSE },
	{ 0x00bf75, KEY_PAUSE },
	{ 0x20080e, KEY_FAVORITES },
	{ 0x200807, KEY_CHANNELDOWN },
	{ 0x200806, KEY_CHANNELUP },
	{ 0x00bf77, KEY_FN_S },
	{ 0x20084c, KEY_RECORD },
	{ 0x200805, KEY_TV },
	{ 0x20080d, KEY_EPG },
	{ 0x200848, KEY_PREVIOUSSONG },
	{ 0x20084b, KEY_NEXTSONG },

/* Atto Turing */
	{ 0x02cd0c, KEY_POWER },
	{ 0x02cd02, KEY_MUTE },
	{ 0x02cd4a, KEY_HELP },
	{ 0x02cd45, KEY_F6 },
	{ 0x02cd54, KEY_TV },
	{ 0x02cd50, KEY_AUDIO },
	{ 0x02cd06, KEY_1 },
	{ 0x02cd60, KEY_2 },
	{ 0x02cd61, KEY_3 },
	{ 0x02cd62, KEY_4 },
	{ 0x02cd63, KEY_5 },
	{ 0x02cd64, KEY_6 },
	{ 0x02cd65, KEY_7 },
	{ 0x02cd66, KEY_8 },
	{ 0x02cd09, KEY_9 },
	{ 0x02cd05, KEY_0 },
	{ 0x02cd01, KEY_BACKSPACE },
	{ 0x02cd43, KEY_FN_S },
	{ 0x02cd0a, KEY_VOLUMEUP },
	{ 0x02cd40, KEY_VOLUMEDOWN },
	{ 0x02cd1c, KEY_CHANNELUP },
	{ 0x02cd18, KEY_CHANNELDOWN },
	{ 0x02cd4b, KEY_F8 },
	{ 0x02cd47, KEY_HOME },
	{ 0x02cd46, KEY_MENU },
	{ 0x02cd42, KEY_EXIT },
	{ 0x02cd55, KEY_UP },
	{ 0x02cd5b, KEY_DOWN },
	{ 0x02cd03, KEY_LEFT },
	{ 0x02cd41, KEY_RIGHT },
	{ 0x02cd1a, KEY_ENTER },
	{ 0x02cd44, KEY_EPG },
	{ 0x02cd4c, KEY_INFO },
	{ 0x02cd14, KEY_RED },
	{ 0x02cd10, KEY_GREEN },
	{ 0x02cd52, KEY_YELLOW },
	{ 0x02cd56, KEY_BLUE },
	{ 0x02cd59, KEY_PLAY },
	{ 0x02cd5d, KEY_STOP },
	{ 0x02cd0b, KEY_PLAYPAUSE },
	{ 0x02cd51, KEY_RECORD },
	{ 0x02cd67, KEY_REWIND },
	{ 0x02cd68, KEY_FASTFORWARD },
	{ 0x02cd4d, KEY_PAGEDOWN },
	{ 0x02cd69, KEY_PAGEUP },
	{ 0x02cd13, KEY_F7 },
	{ 0x02cd07, KEY_FN_F11 },
	{ 0x02cd00, KEY_SUBTITLE },
	{ 0x02cd11, KEY_TEXT },
};

static struct rc_map_list atto_map = {
	.map = {
		.scan    = atto,
		.size    = ARRAY_SIZE(atto),
		.rc_type = RC_TYPE_NEC,
		.name    = "rc-atto",
	}
};

static int __init init_rc_map_atto(void)
{
	return rc_map_register(&atto_map);
}

static void __exit exit_rc_map_atto(void)
{
	rc_map_unregister(&atto_map);
}

module_init(init_rc_map_atto)
module_exit(exit_rc_map_atto)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Leandro Tavares de Melo <leandrotsampa@yahoo.com.br>");
