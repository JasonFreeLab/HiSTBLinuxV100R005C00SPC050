/*
   (c) Copyright 2012-2013  DirectFB integrated media GmbH
   (c) Copyright 2001-2013  The world wide DirectFB Open Source Community (directfb.org)
   (c) Copyright 2000-2004  Convergence (integrated media) GmbH

   All rights reserved.

   Written by Denis Oliver Kropp <dok@directfb.org>,
              Andreas Shimokawa <andi@directfb.org>,
              Marek Pikarski <mass@directfb.org>,
              Sven Neumann <neo@directfb.org>,
              Ville Syrjälä <syrjala@sci.fi> and
              Claudio Ciccani <klan@users.sf.net>.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the
   Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.
*/



#ifndef __CORE__FBDEV_H__
#define __CORE__FBDEV_H__

#include <asm/types.h>    /* Needs to be included before dfb_types.h */

#include <core/coretypes.h>

#include <core/layers_internal.h>

#include <core/system.h>

#include <direct/log.h>
#include <direct/messages.h>

#include <fusion/call.h>
#include <fusion/reactor.h>

#include "agp.h"
#include "fb.h"
#include "surfacemanager.h"
#include "vt.h"

#ifndef FBIO_WAITFORVSYNC
#define FBIO_WAITFORVSYNC	_IOW('F', 0x20, u_int32_t)
#endif


//HISILICON add begin
//tag, support fence sync
#define  PRIMARYLAYER             0
#define  MAX_FB_NUM               3
#define  CONFIG_MAX_LAYER_NUM     2
//HISILICON add end


typedef struct {
     /* fbdev fixed screeninfo, contains infos about memory and type of card */
     struct fb_fix_screeninfo fix;

     VideoMode                *modes;        /* linked list of valid
                                                video modes */
     VideoMode                 current_mode; /* current video mode */

     struct fb_var_screeninfo current_var;   /* fbdev variable screeninfo
                                                set by DirectFB */
     struct fb_var_screeninfo orig_var;      /* fbdev variable screeninfo
                                                before DirectFB was started */

     void                    *orig_cmap_memory;
     void                    *temp_cmap_memory;
     void                    *current_cmap_memory;

     struct fb_cmap           orig_cmap;     /* original palette */

     struct fb_cmap           current_cmap;  /* our copy of the cmap */

     struct fb_cmap           temp_cmap;     /* scratch */

     FusionCall               fbdev_ioctl;   /* ioctl rpc */

     unsigned long            page_mask;     /* PAGE_SIZE - 1 */

     CoreSurfacePool          *pool;

     struct {
          int                 bus;
          int                 dev;
          int                 func;
     } pci;                                  /* PCI Bus ID of graphics device */

     struct {
          unsigned short      vendor;        /* Graphics device vendor id */
          unsigned short      model;         /* Graphics device model id */
     } device;

     AGPShared               *agp;

     FusionSHMPoolShared     *shmpool;
     FusionSHMPoolShared     *shmpool_data;

     CoreLayerRegionConfig    config;

     SurfaceManager          *manager;
} FBDevShared;

typedef struct {
     FBDevShared             *shared;

     CoreDFB                 *core;

     /* virtual framebuffer address */
     void                    *framebuffer_base;

     int                      fd;            /* file descriptor for /dev/fb */
     int                      fence_fd[MAX_FB_NUM];
     int                      current_fence_index;

     VirtualTerminal         *vt;

     AGPDevice               *agp;
} FBDev;

 //HISILICON add begin
//[TAG]:save mmz info
typedef struct{
      void  *pool_phy_addr;
      void  *pool_vir_addr;
      DirectLog    *mmz_log;
      int shmid;
      void *shmptr;
}FBDevMmzInfo;
//HISILICON add end


//HISILICON add begin
//tag, support fence sync
DFBResult dfb_fbdev_quene_buffnum(int layer_num, int *pbuffer_num);
DFBResult dfb_fbdev_fence_sync_wait(int timeout, int layernum, int buffer_id);
DFBResult dfb_fbdev_quene_buffer_id(int layernum,unsigned int buffer, int *pbufferid);
DFBResult dfb_fbdev_quene_free_buffer_id(int layernum,int *pbufferid);
//HISILICON add end
#endif
