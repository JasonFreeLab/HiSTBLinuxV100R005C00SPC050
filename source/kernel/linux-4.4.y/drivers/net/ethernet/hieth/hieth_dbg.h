/******************************************************************************
 *    Copyright (C) 2014 Hisilicon STB Development Dept
 *    All rights reserved.
 * ***
 *    Create by ZhangYixing
 *
******************************************************************************/
#ifndef HIETH_DBG_H
#define HIETH_DBG_H

int hieth_dbg_init(void __iomem *base, struct platform_device *pdev);
int hieth_dbg_deinit(struct platform_device *pdev);
int multicast_dump_netdev_flags(u32 flags, struct hieth_platdrv_data *pdata);
void multicast_dump_macaddr(u32 nr, char *macaddr, struct hieth_platdrv_data *pdata);

#endif
