/*
   (c) Copyright 2002-2011  The world wide DirectFB Open Source Community (directfb.org)
   (c) Copyright 2002-2004  Convergence (integrated media) GmbH

   All rights reserved.

   Written by Denis Oliver Kropp <dok@directfb.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version
   2 of the License, or (at your option) any later version.
*/

#include <linux/version.h>
#include <linux/module.h>
#ifdef HAVE_LINUX_CONFIG_H
#include <linux/config.h>
#endif
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/sched.h>

#include "debug.h"

#include "fusioncore.h"



FusionCoreResult
fusion_core_enter( int          cpu_index,
                   FusionCore **ret_core )
{
     FusionCore *core;

     D_ASSERT( ret_core != NULL );

     core = kmalloc( sizeof(FusionCore), GFP_KERNEL );
     if (!core)
          return FC_FAILURE;

     core->cpu_index = cpu_index;

     sema_init( &core->lock, 1 );

     D_MAGIC_SET( core, FusionCore );

     *ret_core = core;

     return FC_OK;
}

void
fusion_core_exit( FusionCore *core )
{
     D_MAGIC_ASSERT( core, FusionCore );


     D_MAGIC_CLEAR( core );

     kfree( core );
}

// FIXME: in theory pids could be more than 16bit wide, so we'd have to use a 64bit type here
pid_t
fusion_core_pid( FusionCore *core )
{
     D_MAGIC_ASSERT( core, FusionCore );

     return (core->cpu_index << 16) | current->pid;
}


void *
fusion_core_malloc( FusionCore *core,
                    size_t      size )
{
     D_MAGIC_ASSERT( core, FusionCore );

     return kzalloc( size, GFP_KERNEL );
}

void
fusion_core_free( FusionCore *core,
                  void       *ptr )
{
     D_MAGIC_ASSERT( core, FusionCore );

     kfree( ptr );
}


void
fusion_core_set_pointer( FusionCore      *core,
                         unsigned int     index,
                         void            *ptr )
{
     FUSION_DEBUG( "%s( %p, index %d, ptr %p )\n", __FUNCTION__, core, index, ptr );

     D_MAGIC_ASSERT( core, FusionCore );

     D_ASSERT( index < sizeof(core->pointers) );

     core->pointers[index] = ptr;
}

void *
fusion_core_get_pointer( FusionCore      *core,
                         unsigned int     index )
{
     FUSION_DEBUG( "%s( %p, index %d )\n", __FUNCTION__, core, index );

     D_MAGIC_ASSERT( core, FusionCore );

     D_ASSERT( index < sizeof(core->pointers) );

     FUSION_DEBUG( "  -> returning %p\n", core->pointers[index] );

     return core->pointers[index];
}


void
fusion_core_lock( FusionCore *core )
{
     D_MAGIC_ASSERT( core, FusionCore );

     down( &core->lock );
}

void
fusion_core_unlock( FusionCore *core )
{
     D_MAGIC_ASSERT( core, FusionCore );

     up( &core->lock );
}


FusionCoreResult
fusion_core_wq_init( FusionCore      *core,
                     FusionWaitQueue *queue )
{
     D_MAGIC_ASSERT( core, FusionCore );

     memset( queue, 0, sizeof(FusionWaitQueue) );

     init_waitqueue_head( &queue->queue );

     D_MAGIC_SET( queue, FusionWaitQueue );

     return FC_OK;
}

void
fusion_core_wq_deinit( FusionCore      *core,
                       FusionWaitQueue *queue )
{
     D_MAGIC_ASSERT( core, FusionCore );
     D_MAGIC_ASSERT( queue, FusionWaitQueue );

     D_MAGIC_CLEAR( queue );
}

void
fusion_core_wq_wait( FusionCore      *core,
                     FusionWaitQueue *queue,
                     int             *timeout_ms,
                     bool             interruptible )
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 0)
     DEFINE_WAIT(wait);

     D_MAGIC_ASSERT( core, FusionCore );
     D_MAGIC_ASSERT( queue, FusionWaitQueue );

     prepare_to_wait( &queue->queue, &wait, interruptible ? TASK_INTERRUPTIBLE : TASK_UNINTERRUPTIBLE );

     fusion_core_unlock( core );

     if (timeout_ms)
          *timeout_ms = schedule_timeout(*timeout_ms);
     else
          schedule();

     finish_wait( &queue->queue, &wait );

     fusion_core_lock( core );
#else
     wait_queue_t wait;

     D_MAGIC_ASSERT( core, FusionCore );
     D_MAGIC_ASSERT( queue, FusionWaitQueue );

     init_waitqueue_entry(&wait, current);

     current->state = interruptible ? TASK_INTERRUPTIBLE : TASK_UNINTERRUPTIBLE;

     write_lock( &queue->queue.lock);
     __add_wait_queue( &queue->queue, &wait);
     write_unlock( &queue->queue.lock );

     fusion_core_unlock( core );

     if (timeout_ms)
          *timeout_ms = schedule_timeout(*timeout_ms);
     else
          schedule();

     fusion_core_lock( core );

     write_lock( &queue->queue.lock );
     __remove_wait_queue( &queue->queue, &wait );
     write_unlock( &queue->queue.lock );
#endif
}

void
fusion_core_wq_wake( FusionCore      *core,
                     FusionWaitQueue *queue )
{
     D_MAGIC_ASSERT( core, FusionCore );
     D_MAGIC_ASSERT( queue, FusionWaitQueue );

     wake_up_all( &queue->queue );
}

