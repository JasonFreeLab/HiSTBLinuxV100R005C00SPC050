
/******************************************************************************
 *  Copyright (C) 2015 Hisilicon Technologies CO.,LTD.
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
 * Create By Hisilicon 2017.5.11
 *
******************************************************************************/

#define DRVNAME "tag-bootreg"
#define pr_fmt(fmt) DRVNAME ": " fmt

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/libfdt.h>
#include <linux/bug.h>
#include "setup.h"

#define TAG_BOOTREG 0x53000001

static char __boot_bootreg[12 * 1024];
char *boot_bootreg = __boot_bootreg;
EXPORT_SYMBOL(boot_bootreg);

static int __init parse_tag_bootreg(const struct tag *tag, void *fdt)
{
        int length = *(int *)&tag->u;
        char *p = ((char *)&tag->u + sizeof(int));

	printk(KERN_DEBUG "Parse bootreg tag\n");

        if (length > sizeof(__boot_bootreg) - sizeof(int)) {
                printk(KERN_ERR "boot register space too small");
                BUG ();
        }
        *(int *)__boot_bootreg = length;
        memcpy(__boot_bootreg + sizeof(int), p, length);

//#define __DUMP_REG
#ifdef __DUMP_REG
	printk(KERN_INFO "-----------Boot Reg-------------");
	print_hex_dump(KERN_INFO, " ", DUMP_PREFIX_OFFSET, 16, 4,
		__boot_bootreg, length, true);
	printk(KERN_INFO "--------------End---------------");
#endif
        return 0;
}
/*****************************************************************************/
struct tagtable tag_bootreg __initdata = {TAG_BOOTREG, parse_tag_bootreg};
/*****************************************************************************/

