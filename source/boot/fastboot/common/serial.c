/*
 * (C) Copyright 2004
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <serial.h>
#include <stdio_dev.h>

DECLARE_GLOBAL_DATA_PTR;

static struct serial_device *serial_devices = NULL;
static struct serial_device *serial_current = NULL;

static void serial_null(void)
{
}

#define serial_initfunc(name)                            \
       void name(void)                                         \
              __attribute__((weak, alias("serial_null")));

serial_initfunc(pl01x_serial0_initialize);
serial_initfunc(pl01x_serial1_initialize);

void serial_register (struct serial_device *dev)
{
#ifndef CONFIG_RELOC_FIXUP_WORKS
	dev->start += gd->reloc_off;
	dev->setbrg += gd->reloc_off;
	dev->getc += gd->reloc_off;
	dev->tstc += gd->reloc_off;
	dev->putc += gd->reloc_off;
	dev->puts += gd->reloc_off;
#endif

	dev->next = serial_devices;
	serial_devices = dev;
}

void serial_initialize (void)
{
	pl01x_serial0_initialize();
	pl01x_serial1_initialize();

	serial_assign (default_serial_console ()->name);
}

void serial_stdio_init (void)
{
	struct stdio_dev dev;
	struct serial_device *s = serial_devices;

	while (s) {
		memset (&dev, 0, sizeof (dev));

		strncpy (dev.name, s->name, sizeof(dev.name));
		dev.flags = DEV_FLAGS_OUTPUT | DEV_FLAGS_INPUT;

		dev.start = s->start;
		dev.stop = s->stop;
		dev.putc = s->putc;
		dev.puts = s->puts;
		dev.getc = s->getc;
		dev.tstc = s->tstc;

		stdio_register (&dev);

		s = s->next;
	}
}

int serial_assign(const char *name)
{
	struct serial_device *s;
	u8  length;

	for (s = serial_devices; s; s = s->next) {
		length = max(strlen(s->name), strlen(name)) ;
		if (strncmp (s->name, name, length) == 0) {
			serial_current = s;
			return 0;
		}
	}

	return 1;
}

void serial_reinit_all (void)
{
	struct serial_device *s;

	for (s = serial_devices; s; s = s->next) {
		s->start ();
	}
}

static struct serial_device *get_current(void)
{
	struct serial_device *dev;

	if (!(gd->flags & GD_FLG_RELOC) || !serial_current) {
		dev = default_serial_console();

		/* We must have a console device */
		if (!dev)
			panic("Cannot find console");
	} else
		dev = serial_current;
	return dev;
}

int serial_init(void)
{
	return get_current()->start();
}

void serial_setbrg (void)
{
	get_current()->setbrg();
}

int serial_getc (void)
{
	return get_current()->getc();
}

int serial_tstc (void)
{
	return get_current()->tstc();
}

void serial_putc (const char c)
{
	get_current()->putc(c);
}

void serial_puts (const char *s)
{
	get_current()->puts(s);
}
