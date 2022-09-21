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



//#define DIRECT_ENABLE_DEBUG

#include <config.h>

#include <direct/debug.h>
#include <direct/mem.h>

#include <core/surface_pool.h>

#include <gfx/convert.h>
 //HISILICON add begin
//[TAG]:add Add header file of shared memory
#include <sys/ipc.h>
#include <sys/shm.h>
//HISILICON add end

#include "fbdev.h"
#include "surfacemanager.h"
#include "hi_common.h"

extern FBDev *dfb_fbdev[CONFIG_MAX_LAYER_NUM];

 //HISILICON add begin
//[TAG]:used for output mmz log
FBDevMmzInfo dfb_mmz_info;
//HISILICON add end


D_DEBUG_DOMAIN( FBDev_Surfaces, "FBDev/Surfaces", "FBDev Framebuffer Surface Pool" );
D_DEBUG_DOMAIN( FBDev_SurfLock, "FBDev/SurfLock", "FBDev Framebuffer Surface Pool Locks" );

/**********************************************************************************************************************/
typedef struct {
     int             magic;

     SurfaceManager *manager;
} FBDevPoolData;

typedef struct {
     int             magic;

     CoreDFB        *core;
} FBDevPoolLocalData;


 //HISILICON add begin
//[TAG]:used for mmz
typedef struct{
     void*  vir_addr;
     void*  phy_addr;
     int    pitch;
}MMZSurface;

typedef struct {
     int    magic;
     Chunk *chunk;
#ifndef CFG_MEMPOOL_FB
     MMZSurface mmz_surface;
     int pool_use_up;
#endif
//HISILICON add end
} FBDevAllocationData;

typedef struct{
    void	*pool_phy_addr;
    void	*pool_vir_addr;
    DirectLog    *mmz_log;
}ShardMmzData;

/**********************************************************************************************************************/
static int
fbdevPoolDataSize( void )
{
     return sizeof(FBDevPoolData);
}

static int
fbdevPoolLocalDataSize( void )
{
     return sizeof(FBDevPoolLocalData);
}

static int
fbdevAllocationDataSize( void )
{
     return sizeof(FBDevAllocationData);
}

static DFBResult
fbdevInitPool( CoreDFB                    *core,
               CoreSurfacePool            *pool,
               void                       *pool_data,
               void                       *pool_local,
               void                       *system_data,
               CoreSurfacePoolDescription *ret_desc )
{
     DFBResult           ret;
     FBDevPoolData      *data  = pool_data;
     FBDevPoolLocalData *local = pool_local;

     D_DEBUG_AT( FBDev_Surfaces, "%s()\n", __FUNCTION__ );

     D_ASSERT( core != NULL );
     D_MAGIC_ASSERT( pool, CoreSurfacePool );
     D_ASSERT( data != NULL );
     D_ASSERT( local != NULL );
     D_ASSERT( ret_desc != NULL );
     int nLayerNum = pool->pool_id - 2;

 //HISILICON add begin
/*[TAG]:Initialize the log  and  initialize shared memory
 in order to process more use mmz*/
#ifdef CFG_DEBUG_MMZ
	if(nLayerNum == 0){
		DirectLogType log_type = DLT_FILE;
		const char    *log_param = "/var/dfb.log";
		ret = direct_log_create( log_type, log_param, &dfb_mmz_info.mmz_log );
		if (ret){
		  return DFB_FAILURE;
		}
	}
 #endif

#ifndef CFG_MEMPOOL_FB
	//memory pool
	if(CFG_MEMPOOL_SIZE){
		ShardMmzData *shard_mmz_data;
		int shm_key;
  		//fb0 alloc mmz pool
		if(nLayerNum == 0){
			dfb_mmz_info.pool_phy_addr = (void*)HI_MMZ_New(CFG_MEMPOOL_SIZE, 0, NULL, "DFB");
			if (!dfb_mmz_info.pool_phy_addr){
				D_ERROR("[dfbmmz]HI_MMZ_New Error==%s,%d==\n",__FUNCTION__,__LINE__);
				return DFB_FAILURE;
			}
			dfb_mmz_info.pool_vir_addr = HI_MMZ_Map((HI_U32)dfb_mmz_info.pool_phy_addr , 0);
			if (!dfb_mmz_info.pool_vir_addr){
				HI_MMZ_Unmap((HI_U32)dfb_mmz_info.pool_phy_addr);
				HI_MMZ_Delete((HI_U32)dfb_mmz_info.pool_phy_addr);
				D_ERROR("[dfbmmz]HI_MMZ_Map Error==%s,%d==\n",__FUNCTION__,__LINE__);
				return DFB_FAILURE;
			}
			//create shm of mmz pool
			shm_key = ftok("/usr", 0);
			if((dfb_mmz_info.shmid = shmget(shm_key, sizeof(ShardMmzData ) ,IPC_CREAT)) ==-1){
				D_ERROR("[dfbmmz]shmget error ==%s,%d==\n",__FUNCTION__,__LINE__);
				HI_MMZ_Unmap((HI_U32)dfb_mmz_info.pool_phy_addr);
				HI_MMZ_Delete((HI_U32)dfb_mmz_info.pool_phy_addr);
				return DFB_FAILURE;
			}
			if((int)(dfb_mmz_info.shmptr =shmat(dfb_mmz_info.shmid,0,0))== -1){
				D_ERROR("[dfbmmz]shmat error ==%s,%d==\n",__FUNCTION__,__LINE__);
				HI_MMZ_Unmap((HI_U32)dfb_mmz_info.pool_phy_addr);
				HI_MMZ_Delete((HI_U32)dfb_mmz_info.pool_phy_addr);
				return DFB_FAILURE;
			}

			shard_mmz_data= (ShardMmzData *)dfb_mmz_info.shmptr;

			shard_mmz_data->pool_phy_addr = dfb_mmz_info.pool_phy_addr;
			shard_mmz_data->pool_vir_addr = dfb_mmz_info.pool_vir_addr;
			shard_mmz_data->mmz_log =  dfb_mmz_info.mmz_log;

			ret = dfb_surfacemanager_create( core, CFG_MEMPOOL_SIZE, &data->manager );
			if (ret)
				return ret;
		}

	}else if (CFG_MEMPOOL_SIZE == 0){
	     ret = dfb_surfacemanager_create( core, dfb_fbdev[nLayerNum]->shared->fix.smem_len, &data->manager );
	     if (ret)
	          return ret;
	}
#else
	//framebuffer pool
	ret = dfb_surfacemanager_create( core, dfb_fbdev[nLayerNum]->shared->fix.smem_len, &data->manager );
	if (ret)
		return ret;

#endif


     ret_desc->caps              = CSPCAPS_PHYSICAL | CSPCAPS_VIRTUAL;
     ret_desc->access[CSAID_CPU] = CSAF_READ | CSAF_WRITE | CSAF_SHARED;
     ret_desc->access[CSAID_GPU] = CSAF_READ | CSAF_WRITE | CSAF_SHARED;
     ret_desc->types             = CSTF_LAYER | CSTF_WINDOW | CSTF_CURSOR | CSTF_FONT | CSTF_SHARED | CSTF_EXTERNAL;
     ret_desc->priority          = CSPP_DEFAULT;

     /* For hardware layers */
     ret_desc->access[CSAID_LAYER0] = CSAF_READ;
     ret_desc->access[CSAID_LAYER1] = CSAF_READ;
     ret_desc->access[CSAID_LAYER2] = CSAF_READ;
     ret_desc->access[CSAID_LAYER3] = CSAF_READ;
     ret_desc->access[CSAID_LAYER4] = CSAF_READ;
     ret_desc->access[CSAID_LAYER5] = CSAF_READ;
     ret_desc->access[CSAID_LAYER6] = CSAF_READ;
     ret_desc->access[CSAID_LAYER7] = CSAF_READ;
     ret_desc->access[CSAID_LAYER8] = CSAF_READ;
     ret_desc->access[CSAID_LAYER9] = CSAF_READ;
     ret_desc->access[CSAID_LAYER10] = CSAF_READ;
     ret_desc->access[CSAID_LAYER11] = CSAF_READ;
     ret_desc->access[CSAID_LAYER12] = CSAF_READ;
     ret_desc->access[CSAID_LAYER13] = CSAF_READ;
     ret_desc->access[CSAID_LAYER14] = CSAF_READ;
     ret_desc->access[CSAID_LAYER15] = CSAF_READ;

     snprintf( ret_desc->name, DFB_SURFACE_POOL_DESC_NAME_LENGTH, "Frame Buffer Memory" );

     local->core = core;

     D_MAGIC_SET( data, FBDevPoolData );
     D_MAGIC_SET( local, FBDevPoolLocalData );


     D_ASSERT( dfb_fbdev[nLayerNum] != NULL );
     D_ASSERT( dfb_fbdev[nLayerNum]->shared != NULL );

     if(nLayerNum == 0){
  	   dfb_fbdev[nLayerNum]->shared->manager = data->manager;
     }
//HISILICON add end

     return DFB_OK;
}

static DFBResult
fbdevJoinPool( CoreDFB                    *core,
               CoreSurfacePool            *pool,
               void                       *pool_data,
               void                       *pool_local,
               void                       *system_data )
{
     FBDevPoolData      *data  = pool_data;
     FBDevPoolLocalData *local = pool_local;

     D_DEBUG_AT( FBDev_Surfaces, "%s()\n", __FUNCTION__ );

     D_ASSERT( core != NULL );
     D_MAGIC_ASSERT( pool, CoreSurfacePool );
     D_MAGIC_ASSERT( data, FBDevPoolData );
     D_ASSERT( local != NULL );

     (void) data;

     local->core = core;

     D_MAGIC_SET( local, FBDevPoolLocalData );
 //HISILICON add begin
//[TAG]:initialize shared memory and get mmz log info and address info
#ifndef CFG_MEMPOOL_FB
	if(CFG_MEMPOOL_SIZE){
		 int nLayerNum = pool->pool_id - 2;
		 if(nLayerNum == 0){
			ShardMmzData *shard_mmz_data;
			int shm_key;

			shm_key= ftok("/usr", 0);
			if((dfb_mmz_info.shmid = shmget(shm_key,sizeof(ShardMmzData ),IPC_CREAT)) == -1){
				D_ERROR("[dfbmmz]shmget error ==%s,%d==\n",__FUNCTION__,__LINE__);
				return DFB_FAILURE;
			}
			if((int)(dfb_mmz_info.shmptr = shmat(dfb_mmz_info.shmid,0,0)) == -1){
				D_ERROR("[dfbmmz]shmat error ==%s,%d==\n",__FUNCTION__,__LINE__);
				return DFB_FAILURE;
			}
			shard_mmz_data = (ShardMmzData *)dfb_mmz_info.shmptr;

			dfb_mmz_info.pool_phy_addr = shard_mmz_data->pool_phy_addr;
			dfb_mmz_info.pool_vir_addr = shard_mmz_data->pool_vir_addr;
			dfb_mmz_info.mmz_log = shard_mmz_data->mmz_log;
		}
	}
#endif
//HISILICON add end
     return DFB_OK;
}

static DFBResult
fbdevDestroyPool( CoreSurfacePool *pool,
                  void            *pool_data,
                  void            *pool_local )
{
     FBDevPoolData      *data  = pool_data;
     FBDevPoolLocalData *local = pool_local;

     D_DEBUG_AT( FBDev_Surfaces, "%s()\n", __FUNCTION__ );

     D_MAGIC_ASSERT( pool, CoreSurfacePool );
     D_MAGIC_ASSERT( data, FBDevPoolData );
     D_MAGIC_ASSERT( local, FBDevPoolLocalData );

    if(data->manager)
        dfb_surfacemanager_destroy( data->manager );

     D_MAGIC_CLEAR( data );
     D_MAGIC_CLEAR( local );

//HISILICON add begin
//[TAG]:destroy shared memory and destroy mmz log

#ifndef CFG_MEMPOOL_FB
	if(CFG_MEMPOOL_SIZE){
		int nLayerNum = pool->pool_id -2;
		if(nLayerNum == 0){
			if(shmdt(dfb_mmz_info.shmptr) == -1){
				D_ERROR("[dfbmmz]shmdt error ==%s,%d==\n",__FUNCTION__,__LINE__);
				return DFB_FAILURE;
			}
			if(shmctl(dfb_mmz_info.shmid,IPC_RMID,0) == -1){
				D_ERROR("[dfbmmz]shmctl error ==%s,%d==\n",__FUNCTION__,__LINE__);
				return DFB_FAILURE;
			}
			if(dfb_mmz_info.pool_phy_addr){
				HI_MMZ_Unmap((HI_U32)dfb_mmz_info.pool_phy_addr);
				HI_MMZ_Delete((HI_U32)dfb_mmz_info.pool_phy_addr);
			}
		}
	}
#endif

#ifdef CFG_DEBUG_MMZ
  if(dfb_mmz_info.mmz_log)
  {
     direct_log_destroy(dfb_mmz_info.mmz_log);
     dfb_mmz_info.mmz_log = NULL;
  }
#endif
//HISILICON add end
     return DFB_OK;
}

static DFBResult
fbdevLeavePool( CoreSurfacePool *pool,
                void            *pool_data,
                void            *pool_local )
{
     FBDevPoolData      *data  = pool_data;
     FBDevPoolLocalData *local = pool_local;

     D_DEBUG_AT( FBDev_Surfaces, "%s()\n", __FUNCTION__ );

     D_MAGIC_ASSERT( pool, CoreSurfacePool );
     D_MAGIC_ASSERT( data, FBDevPoolData );
     D_MAGIC_ASSERT( local, FBDevPoolLocalData );

     (void) data;

     D_MAGIC_CLEAR( local );

//HISILICON add begin
//[TAG]:destroy shared memory
#ifndef CFG_MEMPOOL_FB
	if(CFG_MEMPOOL_SIZE){
		int nLayerNum = pool->pool_id -2;
		if(nLayerNum == 0){
			if(shmdt(dfb_mmz_info.shmptr) == -1){
				D_ERROR("[dfbmmz]shmdt error ==%s,%d==\n",__FUNCTION__,__LINE__);
				return DFB_FAILURE;
			}
		}
	}
#endif
//HISILICON add end
     return DFB_OK;
}

static DFBResult
fbdevTestConfig( CoreSurfacePool         *pool,
                 void                    *pool_data,
                 void                    *pool_local,
                 CoreSurfaceBuffer       *buffer,
                 const CoreSurfaceConfig *config )
{
     DFBResult           ret;
     CoreSurface        *surface;
     FBDevPoolData      *data  = pool_data;
     FBDevPoolLocalData *local = pool_local;

     D_DEBUG_AT( FBDev_Surfaces, "%s( %p )\n", __FUNCTION__, buffer );

     D_MAGIC_ASSERT( pool, CoreSurfacePool );
     D_MAGIC_ASSERT( data, FBDevPoolData );
     D_MAGIC_ASSERT( local, FBDevPoolLocalData );
     D_MAGIC_ASSERT( buffer, CoreSurfaceBuffer );

     surface = buffer->surface;
     D_MAGIC_ASSERT( surface, CoreSurface );

     if (surface->type & CSTF_LAYER)
          return DFB_OK;
//HISILICON add begin
//[TAG]:if use mmz return Ok
#ifndef CFG_MEMPOOL_FB
	if(CFG_MEMPOOL_SIZE >= 0){
		return DFB_OK;
	}
#else
	ret = dfb_surfacemanager_allocate( local->core, data->manager, buffer, NULL, NULL );
#endif
//HISILICON add end
     D_DEBUG_AT( FBDev_Surfaces, "  -> %s\n", DirectFBErrorString(ret) );

     return ret;
}

static DFBResult
fbdevAllocateBuffer( CoreSurfacePool       *pool,
                     void                  *pool_data,
                     void                  *pool_local,
                     CoreSurfaceBuffer     *buffer,
                     CoreSurfaceAllocation *allocation,
                     void                  *alloc_data )
{
     DFBResult            ret;
     CoreSurface         *surface;
     FBDevPoolData       *data  = pool_data;
     FBDevPoolLocalData  *local = pool_local;
     FBDevAllocationData *alloc = alloc_data;

     D_DEBUG_AT( FBDev_Surfaces, "%s( %p )\n", __FUNCTION__, buffer );

     D_MAGIC_ASSERT( pool, CoreSurfacePool );
     D_MAGIC_ASSERT( data, FBDevPoolData );
     D_MAGIC_ASSERT( local, FBDevPoolLocalData );
     D_MAGIC_ASSERT( buffer, CoreSurfaceBuffer );

     surface = buffer->surface;
     D_MAGIC_ASSERT( surface, CoreSurface );

     if (surface->type & CSTF_LAYER) {
          D_DEBUG_AT( FBDev_Surfaces, "  -> primary layer buffer (index %d)\n", dfb_surface_buffer_index( buffer ) );
          dfb_surface_calc_buffer_size( surface, 8, 1, NULL, &allocation->size );
     }
     else {
//HISILICON add begin
//[TAG]:  allocate mmz memory from pool or  Dynamic allocation
#ifndef CFG_MEMPOOL_FB
	if(CFG_MEMPOOL_SIZE == 0){
		dfb_surface_calc_buffer_size( surface, 8, 1, &alloc->mmz_surface.pitch , &allocation->size );
		void* phys_addr = (void*)HI_MMZ_New(allocation->size, 0, NULL, "DFB");
		if (!phys_addr){
			D_ERROR("[dfbmmz]HI_MMZ_New Error==%s,%d==\n",__FUNCTION__,__LINE__);
			return DFB_FAILURE;
		}
		void* vir_addr = (void*)HI_MMZ_Map((HI_U32)phys_addr, 0);
		if (!vir_addr){
			HI_MMZ_Unmap((HI_U32)alloc->mmz_surface.phy_addr);
			HI_MMZ_Delete((HI_U32)alloc->mmz_surface.phy_addr);
			D_ERROR("[dfbmmz]HI_MMZ_Map Error==%s,%d==\n",__FUNCTION__,__LINE__);
			return DFB_FAILURE;
		}

		alloc->mmz_surface.vir_addr = vir_addr;
		alloc->mmz_surface.phy_addr = phys_addr;
#ifdef CFG_DEBUG_MMZ
		direct_log_printf(dfb_mmz_info.mmz_log, "[dynamic] allocate mem length: %d\n", allocation->size );
#endif
	}else if(CFG_MEMPOOL_SIZE){
		//if mem pool use up or alloc failure
		ret = dfb_surfacemanager_allocate( local->core, data->manager, buffer, allocation, &alloc->chunk );
		if (ret){
		dfb_surface_calc_buffer_size( surface, 8, 1, &alloc->mmz_surface.pitch , &allocation->size );

		void* phys_addr = (void *)HI_MMZ_New(allocation->size, 0, NULL, "DFB");
		if (!phys_addr){
			D_ERROR("[dfbmmz]HI_MMZ_New Error==%s,%d==\n",__FUNCTION__,__LINE__);
			return DFB_FAILURE;
		}
		void* vir_addr = HI_MMZ_Map((HI_U32)phys_addr, 0);
		if (!vir_addr){
			HI_MMZ_Unmap((HI_U32)alloc->mmz_surface.phy_addr);
			HI_MMZ_Delete((HI_U32)alloc->mmz_surface.phy_addr);
			D_ERROR("[dfbmmz]HI_MMZ_Map Error==%s,%d==\n",__FUNCTION__,__LINE__);
			return DFB_FAILURE;
		}

		alloc->mmz_surface.vir_addr = vir_addr;
		alloc->mmz_surface.phy_addr = phys_addr;
		alloc->pool_use_up = 1;
#ifdef CFG_DEBUG_MMZ
		direct_log_printf(dfb_mmz_info.mmz_log, "[dynamic] allocate mem length: %d\n", allocation->size );
#endif
		return DFB_OK;
		}
	}
#else
	ret = dfb_surfacemanager_allocate( local->core, data->manager, buffer, allocation, &alloc->chunk );
	if (ret)
		return ret;
	D_MAGIC_ASSERT( alloc->chunk, Chunk );

	allocation->offset = alloc->chunk->offset;
	allocation->size   = alloc->chunk->length;
#endif
  //HISILICON add end
	}

     D_MAGIC_SET( alloc, FBDevAllocationData );

     return DFB_OK;
}

static DFBResult
fbdevDeallocateBuffer( CoreSurfacePool       *pool,
                       void                  *pool_data,
                       void                  *pool_local,
                       CoreSurfaceBuffer     *buffer,
                       CoreSurfaceAllocation *allocation,
                       void                  *alloc_data )
{
     FBDevPoolData       *data  = pool_data;
     FBDevAllocationData *alloc = alloc_data;

     D_DEBUG_AT( FBDev_Surfaces, "%s( %p )\n", __FUNCTION__, buffer );

     D_MAGIC_ASSERT( pool, CoreSurfacePool );
     D_MAGIC_ASSERT( data, FBDevPoolData );
     D_MAGIC_ASSERT( alloc, FBDevAllocationData );
//HISILICON add begin
//[TAG]:  free mmz memory from pool or  free Dynamic allocation memory
 #ifndef CFG_MEMPOOL_FB
	if(CFG_MEMPOOL_SIZE == 0){
		if (alloc->mmz_surface.phy_addr){
			HI_MMZ_Unmap((HI_U32)alloc->mmz_surface.phy_addr);
			HI_MMZ_Delete((HI_U32)alloc->mmz_surface.phy_addr);
#ifdef CFG_DEBUG_MMZ
			direct_log_printf(dfb_mmz_info.mmz_log, "[dynamic] release mem length: %d\n", allocation->size );
#endif
		}
	}else if(CFG_MEMPOOL_SIZE){
		if (alloc->chunk)
			dfb_surfacemanager_deallocate( data->manager, alloc->chunk );
		if (alloc->mmz_surface.phy_addr){
			HI_MMZ_Unmap((HI_U32)alloc->mmz_surface.phy_addr);
			HI_MMZ_Delete((HI_U32)alloc->mmz_surface.phy_addr);
#ifdef CFG_DEBUG_MMZ
			direct_log_printf(dfb_mmz_info.mmz_log, "[dynamic] release mem length: %d\n", allocation->size );
#endif
		}
	}
#else
	if (alloc->chunk)
	dfb_surfacemanager_deallocate( data->manager, alloc->chunk );
#endif
 //HISILICON add end
     D_MAGIC_CLEAR( alloc );

     return DFB_OK;
}

static DFBResult
fbdevMuckOut( CoreSurfacePool   *pool,
              void              *pool_data,
              void              *pool_local,
              CoreSurfaceBuffer *buffer )
{
     FBDevPoolData      *data  = pool_data;
     FBDevPoolLocalData *local = pool_local;

     D_DEBUG_AT( FBDev_Surfaces, "%s( %p )\n", __FUNCTION__, buffer );

     D_MAGIC_ASSERT( pool, CoreSurfacePool );
     D_MAGIC_ASSERT( data, FBDevPoolData );
     D_MAGIC_ASSERT( local, FBDevPoolLocalData );
     D_MAGIC_ASSERT( buffer, CoreSurfaceBuffer );

     return dfb_surfacemanager_displace( local->core, data->manager, buffer );
}


//HISILICON add begin
//tag, support fence sync
static DFBResult sync_wait(int layer_num, int buffer_id)
{
    CoreLayerRegionConfig *config = NULL;

    if (NULL == dfb_fbdev[layer_num])
    {
       D_WARN("++++++++++++++ dfb_fbdev handle is null\n");
       return DFB_OK;
    }

    if (NULL == dfb_fbdev[layer_num]->shared)
    {
       D_WARN("++++++++++++++ dfb_fbdev->shared is null\n");
       return DFB_OK;
    }

    config = &(dfb_fbdev[layer_num]->shared->config);

    if ((DLBM_UNKNOWN == config->buffermode) || (DLBM_BACKSYSTEM == config->buffermode))
    {
       return DFB_OK;
    }

    dfb_fbdev_fence_sync_wait(-1, layer_num, buffer_id);

    return DFB_OK;
}
//HISILICON add end


static DFBResult
fbdevLock( CoreSurfacePool       *pool,
           void                  *pool_data,
           void                  *pool_local,
           CoreSurfaceAllocation *allocation,
           void                  *alloc_data,
           CoreSurfaceBufferLock *lock )
{
     int buffer_num = 0;
     int free_buffer_id = -1;
     int nResourceId = 0;
     FBDevAllocationData *alloc  = alloc_data;
     FBDevShared         *shared = dfb_fbdev[0]->shared;;

     D_MAGIC_ASSERT( pool, CoreSurfacePool );
     D_MAGIC_ASSERT( allocation, CoreSurfaceAllocation );
     D_MAGIC_ASSERT( alloc, FBDevAllocationData );
     D_MAGIC_ASSERT( lock, CoreSurfaceBufferLock );

     D_DEBUG_AT( FBDev_SurfLock, "%s( %p )\n", __FUNCTION__, lock->buffer );

    if (allocation->type & CSTF_LAYER)
    {
        nResourceId = allocation->resource_id;
    }
    else
    {
        nResourceId = 0;
    }

    if (NULL != dfb_fbdev[nResourceId])
    {
        shared = dfb_fbdev[nResourceId]->shared;
    }

     if (allocation->type & CSTF_LAYER) {
          int index  = dfb_surface_buffer_index( allocation->buffer);

          D_DEBUG_AT( FBDev_Surfaces, "  -> primary layer buffer (index %d)\n", index );
//HISILICON add begin
//tag, support fence sync
          dfb_fbdev_quene_buffnum(nResourceId, &buffer_num);
#ifdef CONFIG_DFB_POLL_BUFFER
          if (index < buffer_num)
          {
              while (-1 == free_buffer_id)
              {
                 dfb_fbdev_quene_free_buffer_id(nResourceId, &free_buffer_id);
              }
              index = free_buffer_id;
          }
#endif
//HISILICON add end

          lock->pitch  = shared->fix.line_length;
          lock->offset = index * allocation->config.size.h * lock->pitch;

#if D_DEBUG_ENABLED
          allocation->offset = lock->offset;
#endif
//HISILICON add begin
//tag, support fence sync
#ifdef CONFIG_DFB_POLL_BUFFER
         if (index == free_buffer_id)
#else
         if (index < buffer_num)
#endif
         sync_wait(nResourceId,free_buffer_id);
//HISILICON add end
         lock->addr = dfb_fbdev[nResourceId]->framebuffer_base + lock->offset;
         lock->phys = dfb_fbdev[nResourceId]->shared->fix.smem_start + lock->offset;
     }
     else {
#ifndef CFG_MEMPOOL_FB
	if(CFG_MEMPOOL_SIZE ==0){
		lock->pitch  = alloc->mmz_surface.pitch;
		lock->offset = 0;
		lock->addr = (void*) (unsigned long) alloc->mmz_surface.vir_addr;
		lock->phys = (unsigned long) alloc->mmz_surface.phy_addr;
	}else if(CFG_MEMPOOL_SIZE > 0){
		if(alloc->pool_use_up == 0){
			D_MAGIC_ASSERT( alloc->chunk, Chunk );
			lock->pitch  = alloc->chunk->pitch;
			lock->offset = alloc->chunk->offset;

			lock->phys = (unsigned long)dfb_mmz_info.pool_phy_addr + lock->offset;
			lock->addr = (void*) (unsigned long)dfb_mmz_info.pool_vir_addr + lock->offset;

		}else if(alloc->pool_use_up){
			lock->pitch  = alloc->mmz_surface.pitch;
			lock->offset = 0;
			lock->addr = (void*) (unsigned long) alloc->mmz_surface.vir_addr;
			lock->phys = (unsigned long) alloc->mmz_surface.phy_addr;
		}
	}
#else
	D_MAGIC_ASSERT( alloc->chunk, Chunk );
	lock->pitch  = alloc->chunk->pitch;
	lock->offset = alloc->chunk->offset;
	lock->addr = dfb_fbdev[nResourceId]->framebuffer_base + lock->offset;
	lock->phys = dfb_fbdev[nResourceId]->shared->fix.smem_start + lock->offset;

#endif
	}
//HISILICON add end
     D_DEBUG_AT( FBDev_SurfLock, "  -> offset %lu, pitch %d, addr %p, phys 0x%08lx\n",
                 lock->offset, lock->pitch, lock->addr, lock->phys );

     return DFB_OK;
}

static DFBResult
fbdevUnlock( CoreSurfacePool       *pool,
             void                  *pool_data,
             void                  *pool_local,
             CoreSurfaceAllocation *allocation,
             void                  *alloc_data,
             CoreSurfaceBufferLock *lock )
{
     FBDevAllocationData *alloc = alloc_data;

     D_MAGIC_ASSERT( pool, CoreSurfacePool );
     D_MAGIC_ASSERT( allocation, CoreSurfaceAllocation );
     D_MAGIC_ASSERT( alloc, FBDevAllocationData );
     D_MAGIC_ASSERT( lock, CoreSurfaceBufferLock );

     D_DEBUG_AT( FBDev_SurfLock, "%s( %p )\n", __FUNCTION__, lock->buffer );

     (void) alloc;

     return DFB_OK;
}

const SurfacePoolFuncs fbdevSurfacePoolFuncs = {
     .PoolDataSize       = fbdevPoolDataSize,
     .PoolLocalDataSize  = fbdevPoolLocalDataSize,
     .AllocationDataSize = fbdevAllocationDataSize,

     .InitPool           = fbdevInitPool,
     .JoinPool           = fbdevJoinPool,
     .DestroyPool        = fbdevDestroyPool,
     .LeavePool          = fbdevLeavePool,

     .TestConfig         = fbdevTestConfig,
     .AllocateBuffer     = fbdevAllocateBuffer,
     .DeallocateBuffer   = fbdevDeallocateBuffer,

     .MuckOut            = fbdevMuckOut,

     .Lock               = fbdevLock,
     .Unlock             = fbdevUnlock,
};

