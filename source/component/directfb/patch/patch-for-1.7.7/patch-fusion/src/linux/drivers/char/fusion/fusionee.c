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

//#define FUSION_ENABLE_DEBUG

#ifdef HAVE_LINUX_CONFIG_H
#include <linux/config.h>
#endif
#include <linux/version.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/version.h>
#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 35)
#include <linux/smp_lock.h>
#endif
#include <linux/sched.h>
#include <asm/uaccess.h>

#include <linux/fusion.h>

#include "call.h"
#include "fifo.h"
#include "list.h"
#include "fusiondev.h"
#include "fusionee.h"
#include "property.h"
#include "reactor.h"
#include "ref.h"
#include "skirmish.h"
#include "shmpool.h"


static MessageCallbackFunc fusion_message_callbacks[] = {
     [FMC_DISPATCH]   = fusion_reactor_dispatch_message_callback,
     [FMC_CALL_QUOTA] = fusion_call_quota_message_callback
};


typedef struct {
     FusionLink             link;

     int                    msg_id;

     FusionMessageCallback  func_index;
     void                  *ctx;
     int                    param;
} MessageCallback;

#define FUSION_MAX_PACKET_SIZE	16384

typedef struct {
     FusionLink           link;

     int                  magic;

     char                 buf[FUSION_MAX_PACKET_SIZE];
     size_t               size;
     bool                 flush;

     FusionFifo           callbacks;
} Packet;

/******************************************************************************/

static Packet *
Packet_New( void )
{
     Packet *packet;

     FUSION_DEBUG( "%s()\n", __FUNCTION__ );

     packet = fusion_core_malloc( fusion_core, sizeof(Packet) );
     if (!packet)
          return NULL;

     packet->link.magic = 0;
     packet->link.prev  = NULL;
     packet->link.next  = NULL;

     packet->size      = 0;
     packet->flush     = false;

     fusion_fifo_reset( &packet->callbacks );

     D_MAGIC_SET( packet, Packet );

     return packet;
}

static void
Packet_Free( Packet *packet )
{
     MessageCallback *callback;

     FUSION_DEBUG( "%s( %p )\n", __FUNCTION__, packet );

     D_MAGIC_ASSERT( packet, Packet );

     D_ASSERT( packet->link.prev == NULL );
     D_ASSERT( packet->link.next == NULL );

     D_MAGIC_CLEAR( packet );

     while ((callback = (MessageCallback *) fusion_fifo_get(&packet->callbacks)) != NULL) {
          D_MAGIC_ASSERT( packet, Packet );

          fusion_core_free( fusion_core,  callback );
     }

     fusion_core_free( fusion_core,  packet );
}

static int
Packet_Write( Packet     *packet,
              int         type,
              int         msg_id,
              int         channel,
              const void *msg_data,
              int         msg_size,
              const void *extra_data,
              int         extra_size,
              bool        from_user )
{
     size_t             total   = sizeof(FusionReadMessage) + msg_size + extra_size;
     size_t             aligned = (total + 3) & ~3;
     FusionReadMessage *header  = (FusionReadMessage *)( packet->buf + packet->size );

     FUSION_DEBUG( "%s( %p, msg_id %d, channel %d, size %d, extra %d, total %zu )\n",
                   __FUNCTION__, packet, msg_id, channel, msg_size, extra_size, total );

     D_MAGIC_ASSERT( packet, Packet );

     FUSION_ASSERT( packet->size + aligned <= FUSION_MAX_PACKET_SIZE );

     header->msg_type    = type;
     header->msg_id      = msg_id;
     header->msg_channel = channel;
     header->msg_size    = msg_size + extra_size;

     if (from_user) {
          if (copy_from_user( header + 1, msg_data, msg_size ))
               return -EFAULT;
     }
     else
          memcpy( header + 1, msg_data, msg_size );

     if (extra_data && extra_size) {
          if (copy_from_user( (char*)(header + 1) + msg_size, extra_data, extra_size ))
               return -EFAULT;
     }

     while (total < aligned)
          packet->buf[packet->size + total++] = 0;

     packet->size += aligned;

     return 0;
}

static int
Packet_AddCallback( Packet                *packet,
                    int                    msg_id,
                    FusionMessageCallback  func,
                    void                  *ctx,
                    int                    param )
{
     MessageCallback *callback;

     FUSION_DEBUG( "%s( %p )\n", __FUNCTION__, packet );

     D_MAGIC_ASSERT( packet, Packet );

     callback = fusion_core_malloc( fusion_core, sizeof(MessageCallback) );
     if (!callback)
          return -ENOMEM;

     callback->msg_id     = msg_id;
     callback->func_index = func;
     callback->ctx        = ctx;
     callback->param      = param;

     fusion_fifo_put( &packet->callbacks, &callback->link );

     return 0;
}

static int
Packet_RunCallbacks( FusionDev *dev,
                     Packet    *packet )
{
     MessageCallback *callback;

     FUSION_DEBUG( "%s( %p )\n", __FUNCTION__, packet );

     D_MAGIC_ASSERT( packet, Packet );

     while ((callback = (MessageCallback *) fusion_fifo_get(&packet->callbacks)) != NULL) {
          D_MAGIC_ASSERT( packet, Packet );

          if (callback->func_index) {
               D_ASSERT( callback->func_index < D_ARRAY_SIZE(fusion_message_callbacks) );

               fusion_message_callbacks[callback->func_index]( dev, callback->msg_id, callback->ctx, callback->param );
          }

          fusion_core_free( fusion_core,  callback );
     }

     return 0;
}

static bool
Packet_Search( Packet              *packet,
               FusionMessageType    msg_type,
               int                  msg_id )
{
     char   *buf = packet->buf;
     size_t  pos = 0;

     FUSION_DEBUG( "%s( %p )\n", __FUNCTION__, packet );

     D_MAGIC_ASSERT( packet, Packet );

     while (pos < packet->size) {
          FusionReadMessage *header = (FusionReadMessage *) &buf[pos];

          if (header->msg_type == msg_type && header->msg_id == msg_id)
               return true;

          pos += sizeof(FusionReadMessage) + ((header->msg_size + 3) & ~3);
     }

     return false;
}

/******************************************************************************/

static int
Fusionee_GetPacket( Fusionee  *fusionee,
                    size_t     size,
                    Packet   **ret_packet )
{
     Packet *packet;

     FUSION_DEBUG( "%s( %p )\n", __FUNCTION__, fusionee );

     if (size > FUSION_MAX_PACKET_SIZE)
          return -E2BIG;

     packet = (Packet*) direct_list_last( fusionee->packets.items );

     D_MAGIC_ASSERT_IF( packet, Packet );

     if (!packet || packet->size + size > FUSION_MAX_PACKET_SIZE) {
          if (packet) {
               packet->flush = true;

//               fusion_core_wq_wake( fusion_core, &fusionee->wait_receive);
               wake_up_interruptible_sync_poll( &fusionee->wait_receive.queue, POLLIN | POLLRDNORM );
          }

          if (fusionee->free_packets.count) {
               packet = (Packet*) fusion_fifo_get( &fusionee->free_packets );

               D_MAGIC_ASSERT( packet, Packet );
          }
          else
               packet = Packet_New();
          if (!packet)
               return -ENOMEM;

          D_ASSERT( packet->link.prev == NULL );
          D_ASSERT( packet->link.next == NULL );

          fusion_fifo_put( &fusionee->packets, &packet->link );
     }

     D_MAGIC_ASSERT( packet, Packet );

     *ret_packet = packet;

     return 0;
}

static void
Fusionee_PutPacket( Fusionee *fusionee,
                    Packet   *packet )
{
     FUSION_DEBUG( "%s( %p )\n", __FUNCTION__, fusionee );

     D_MAGIC_ASSERT( packet, Packet );

     D_ASSERT( packet->link.prev == NULL );
     D_ASSERT( packet->link.next == NULL );

     if (fusionee->free_packets.count > 11)
          Packet_Free( packet );
     else {
          packet->size  = 0;
          packet->flush = false;

          fusion_fifo_reset( &packet->callbacks );

          fusion_fifo_put( &fusionee->free_packets, &packet->link );
     }
}

/******************************************************************************/

static int lookup_fusionee(FusionDev * dev, FusionID id,
                           Fusionee ** ret_fusionee);
static int lock_fusionee(FusionDev * dev, FusionID id,
                         Fusionee ** ret_fusionee);

static void flush_packets(Fusionee *fusionee, FusionDev * dev, FusionFifo * fifo);
static void free_packets(Fusionee *fusionee, FusionDev * dev, FusionFifo * fifo);

/******************************************************************************/

static int
fusionees_proc_show(struct seq_file *m, void *v)
{
     Fusionee *fusionee;
     FusionDev *dev = m->private;

     fusion_core_lock( fusion_core );

     if (!dev->shutdown) {
          direct_list_foreach(fusionee, dev->fusionee.list) {
               seq_printf(m,
                       "(%5d) 0x%08lx (%4d packets waiting, %7ld received, %7ld sent) - wcq 0x%x - '%s'\n",
                       fusionee->pid, fusionee->id,
                       fusionee->packets.count, atomic_long_read(&fusionee->rcv_total),
                       atomic_long_read(&fusionee->snd_total),
                       fusionee->wait_on_call_quota,
                       fusionee->exe_file);
          }
     }

     fusion_core_unlock( fusion_core );

     return 0;
}

static int fusionees_proc_open(struct inode *inode, struct file *file) {
     return single_open(file, fusionees_proc_show, PDE_DATA(inode));
}

static const struct file_operations fusionees_proc_fops = {
     .open    = fusionees_proc_open,
     .read    = seq_read,
     .llseek  = seq_lseek,
     .release = seq_release,
};

int fusionee_init(FusionDev * dev)
{
     if (!dev->refs)
          fusion_core_wq_init( fusion_core, &dev->fusionee.wait);

     proc_create_data("fusionees", 0, fusion_proc_dir[dev->index],
                       &fusionees_proc_fops, dev);

     return 0;
}

void fusionee_deinit(FusionDev * dev)
{
     Fusionee *fusionee, *next;

     fusion_core_unlock( fusion_core );

     remove_proc_entry( "fusionees", fusion_proc_dir[dev->index] );

     fusion_core_lock( fusion_core );

     if (!dev->refs) {
          direct_list_foreach_safe (fusionee, next, dev->fusionee.list) {
               while (fusionee->packets.count) {
                    Packet *packet = (Packet *) fusion_fifo_get(&fusionee->packets);

                    Packet_Free( packet );
               }

               fusion_core_free( fusion_core, fusionee);
          }
     }
}



/******************************************************************************/

static void
put_name_internal( struct dentry *entry,
                   char          *buf,
                   unsigned int  *offset )
{
     int len = strlen( entry->d_name.name ) + 1;

     if (entry->d_parent != entry)
          put_name_internal( entry->d_parent, buf, offset );

     if (len > 1 && entry->d_name.name[0] != '/') {
          if (*offset + len > PATH_MAX-1)
               return;

          snprintf( buf + *offset, PATH_MAX - *offset, "/%s", entry->d_name.name );

          *offset += len;
     }
}

static void
put_name( struct dentry *entry,
          char          *buf )
{
     unsigned int offset = 0;

     put_name_internal( entry, buf, &offset );
}

int fusionee_new(FusionDev * dev, bool force_slave, Fusionee ** ret_fusionee)
{
     Fusionee *fusionee;

     FUSION_DEBUG("%s()\n", __FUNCTION__);

     fusionee = fusion_core_malloc( fusion_core, sizeof(Fusionee) );
     if (!fusionee)
          return -ENOMEM;

     FUSION_DEBUG( "  -> new fusionee at %p\n", fusionee );

     memset(fusionee, 0, sizeof(Fusionee));

     fusionee->refs = 1;

     fusionee->pid = fusion_core_pid( fusion_core );
     fusionee->force_slave = force_slave;
     fusionee->mm = current->mm;

     fusion_core_wq_init( fusion_core, &fusionee->wait_receive);
     fusion_core_wq_init( fusion_core, &fusionee->wait_process);

     direct_list_prepend(&dev->fusionee.list, &fusionee->link);

     fusionee->fusion_dev = dev;

     if (current->mm->exe_file)
          put_name( current->mm->exe_file->f_path.dentry, fusionee->exe_file );
     else
          printk( KERN_WARNING "fusion: Could not determine exe file of fusionee! (pid %d)\n", current->pid );

     D_MAGIC_SET( fusionee, Fusionee );

     *ret_fusionee = fusionee;

     return 0;
}

int fusionee_enter(FusionDev * dev, FusionEnter * enter, Fusionee * fusionee)
{
     D_MAGIC_ASSERT( fusionee, Fusionee );

     if (dev->fusionee.last_id || fusionee->force_slave) {
          while (!dev->enter_ok) {
               fusion_core_wq_wait( fusion_core, &dev->enter_wait, NULL, true );

               if (signal_pending(current))
                    return -EINTR;
          }

          FUSION_ASSERT(dev->fusionee.last_id != 0);
     }

     if (dev->fusionee.last_id == 0) {
          /* master determines Fusion API (if supported) */
          int major = enter->api.major;
          if ((major != 3) && (major != 4) && (major != 8) && (major != 9))
               return -ENOPROTOOPT;

          dev->api.major = enter->api.major;
          dev->api.minor = enter->api.minor;

          if (dev->api.major > 8 || (dev->api.major == 8 && dev->api.minor >= 5))
               dev->secure = enter->secure;
     }
     else {
          if ((enter->api.major != dev->api.major)
              || (enter->api.minor > dev->api.minor))
               return -ENOPROTOOPT;
     }

     fusionee->id = ++dev->fusionee.last_id;

     enter->fusion_id = fusionee->id;

     return 0;
}

int fusionee_fork(FusionDev * dev, FusionFork * fork, Fusionee * fusionee)
{
     int ret;

     D_MAGIC_ASSERT( fusionee, Fusionee );

     ret = fusion_shmpool_fork_all(dev, fusionee->id, fork->fusion_id);
     if (ret)
          return ret;

     ret = fusion_reactor_fork_all(dev, fusionee->id, fork->fusion_id);
     if (ret)
          return ret;

     ret = fusion_ref_fork_all_local(dev, fusionee->id, fork->fusion_id);
     if (ret)
          return ret;

     fork->fusion_id = fusionee->id;

     return 0;
}

int
fusionee_get_info(FusionDev * dev, FusionGetFusioneeInfo * get_info)
{
     int       ret;
     Fusionee *fusionee;

     ret = lookup_fusionee(dev, get_info->fusion_id, &fusionee);
     if (ret)
          return ret;

     strncpy( get_info->exe_file, fusionee->exe_file, PATH_MAX );

     get_info->pid = fusionee->pid;

     return 0;
}

int
fusionee_send_message(FusionDev * dev,
                      Fusionee * sender,
                      FusionID recipient,
                      FusionMessageType msg_type,
                      int msg_id,
                      int msg_channel,
                      int msg_size,
                      const void *msg_data,
                      FusionMessageCallback callback,
                      void *callback_ctx, int callback_param,
                      const void *extra_data, unsigned int extra_size )
{
     int                      ret;
     Packet                  *packet;
     Fusionee                *fusionee;
     size_t                   size;

     ret = lookup_fusionee(dev, recipient, &fusionee);
     if (ret)
          return ret;

     FUSION_DEBUG("fusionee_send_message (%ld -> %ld, type %d, id %d, size %d, extra %d)\n",
                  fusionee ? fusionee->id : 0, recipient, msg_type, msg_id, msg_size, extra_size);

     D_MAGIC_ASSERT( fusionee, Fusionee );

     while (fusionee->packets.count > 10 && sender && sender->id != FUSION_ID_MASTER &&
            fusion_core_pid(fusion_core) != fusionee->dispatcher_pid && msg_type != FMT_LEAVE)
     {
          fusion_core_wq_wait( fusion_core, &fusionee->wait_process, 0, true );

          if (signal_pending(current))
               return -EINTR;
     }

     ret = Fusionee_GetPacket( fusionee, sizeof(FusionReadMessage) + msg_size + extra_size, &packet );
     if (ret)
          return ret;

     D_MAGIC_ASSERT( packet, Packet );


     /* keep size for error handling, the other way round we'd need to remove the callback :( */
     size = packet->size;

     ret = Packet_Write( packet, msg_type, msg_id, msg_channel,
                         msg_data, msg_size, extra_data, extra_size,
                         msg_type != FMT_CALL && msg_type != FMT_CALL3 && msg_type != FMT_SHMPOOL && msg_type != FMT_LEAVE );
     if (ret)
          return ret;



     D_MAGIC_ASSERT( packet, Packet );

     if (callback) {
          ret = Packet_AddCallback( packet, msg_id, callback, callback_ctx, callback_param );
          if (ret) {
               packet->size = size;
               return ret;
          }
     }


     atomic_long_inc(&fusionee->rcv_total);
     if (sender)
          atomic_long_inc(&sender->snd_total);


     packet->flush = true;
//     fusion_core_wq_wake( fusion_core, &fusionee->wait_receive);
     wake_up_interruptible_sync_poll( &fusionee->wait_receive.queue, POLLIN | POLLRDNORM );

     return 0;
}

int
fusionee_send_message2(FusionDev * dev,
                       Fusionee *sender,
                       Fusionee *fusionee,
                       FusionMessageType msg_type,
                       int msg_id,
                       int msg_channel,
                       int msg_size,
                       const void *msg_data,
                       FusionMessageCallback callback,
                       void *callback_ctx, int callback_param,
                       const void *extra_data, unsigned int extra_size,
                       bool flush)
{
     int     ret;
     Packet *packet;
     size_t  size;

     FUSION_DEBUG("fusionee_send_message2 (%ld -> %ld, type %d, id %d, size %d, extra %d)\n",
                  sender ? sender->id : 0, fusionee->id, msg_type, msg_id, msg_size, extra_size);

     D_MAGIC_ASSERT( fusionee, Fusionee );

     while (fusionee->packets.count > 10 && sender && sender->id != FUSION_ID_MASTER &&
            fusion_core_pid(fusion_core) != fusionee->dispatcher_pid && msg_type != FMT_LEAVE)
     {
          fusion_core_wq_wait( fusion_core, &fusionee->wait_process, 0, true );

          if (signal_pending(current))
               return -EINTR;
     }

     ret = Fusionee_GetPacket( fusionee, sizeof(FusionReadMessage) + msg_size + extra_size, &packet );
     if (ret)
          return ret;

     D_MAGIC_ASSERT( packet, Packet );


     /* keep size for error handling, the other way round we'd need to remove the callback :( */
     size = packet->size;

     ret = Packet_Write( packet, msg_type, msg_id, msg_channel,
                         msg_data, msg_size, extra_data, extra_size,
                         msg_type != FMT_CALL && msg_type != FMT_CALL3 && msg_type != FMT_SHMPOOL && msg_type != FMT_LEAVE );
     if (ret)
          return ret;



     D_MAGIC_ASSERT( packet, Packet );

     if (callback) {
          ret = Packet_AddCallback( packet, msg_id, callback, callback_ctx, callback_param );
          if (ret) {
               packet->size = size;
               return ret;
          }
     }


     atomic_long_inc(&fusionee->rcv_total);
     if (sender)
          atomic_long_inc(&sender->snd_total);

     if (flush) {
          packet->flush = true;
//          fusion_core_wq_wake( fusion_core, &fusionee->wait_receive);
          wake_up_interruptible_sync_poll( &fusionee->wait_receive.queue, POLLIN | POLLRDNORM );
     }

     return 0;
}

int
fusionee_get_messages(FusionDev * dev,
                      Fusionee * fusionee, void *buf, int buf_size, bool block)
{
     int written = 0;
     FusionFifo prev_packets;

     FUSION_DEBUG( "%s()\n", __FUNCTION__ );

     D_MAGIC_ASSERT( fusionee, Fusionee );

     fusionee->dispatcher_pid = fusion_core_pid( fusion_core );

     prev_packets = fusionee->prev_packets;

     fusion_fifo_reset(&fusionee->prev_packets);

     fusion_core_wq_wake( fusion_core, &fusionee->wait_process);

     while (!fusionee->packets.count || !((Packet *) fusionee->packets.items)->flush) {
          if (prev_packets.count) {
               flush_packets(fusionee, dev, &prev_packets);
          }
          else {
               if (!block)
                    return -EAGAIN;

               fusionee->waiting = true;
               fusion_core_wq_wait( fusion_core, &fusionee->wait_receive, NULL, true );
               fusionee->waiting = false;

               if (signal_pending(current))
                    return -EINTR;
          }
     }

     while (fusionee->packets.count && ((Packet *) fusionee->packets.items)->flush) {
          Packet *packet = (Packet *) fusionee->packets.items;
          int     bytes  = packet->size;

          D_MAGIC_ASSERT( packet, Packet );

          if (bytes > buf_size) {
               if (!written) {
                    flush_packets(fusionee, dev, &prev_packets);
                    return -EMSGSIZE;
               }

               break;
          }

          if (copy_to_user(buf, packet->buf, packet->size)) {
               flush_packets(fusionee, dev, &prev_packets);
               return -EFAULT;
          }

          written += bytes;
          buf += bytes;
          buf_size -= bytes;

          fusion_fifo_get(&fusionee->packets);

          D_MAGIC_ASSERT( packet, Packet );

          if (packet->callbacks.count)
               fusion_fifo_put(&fusionee->prev_packets, &packet->link);
          else
               Fusionee_PutPacket(fusionee, packet);
     }

     flush_packets(fusionee, dev, &prev_packets);

     return written;
}

int
fusionee_wait_processing(FusionDev * dev,
                         int fusion_id, FusionMessageType msg_type, int msg_id)
{
     Fusionee *fusionee;

     do {
          int ret;
          Packet *packet;

          ret = lock_fusionee(dev, fusion_id, &fusionee);
          if (ret)
               return ret;

          D_MAGIC_ASSERT( fusionee, Fusionee );

          /* Search all pending packets. */
          direct_list_foreach (packet, fusionee->packets.items) {
               if (Packet_Search( packet, msg_type, msg_id ))
                    break;
          }

          /* Search packets being processed right now. */
          if (!packet) {
               direct_list_foreach (packet, fusionee->prev_packets.items) {
                    if (Packet_Search( packet, msg_type, msg_id ))
                         break;
               }
          }

          /* Really no more packet of that type and ID? */
          if (!packet)
               break;

          if (fusionee->dispatcher_pid)
               FUSION_ASSUME(fusionee->dispatcher_pid != fusion_core_pid( fusion_core ));

          /* Otherwise unlock and wait. */
          fusion_core_wq_wait( fusion_core, &fusionee->wait_process, 0, true );

          if (signal_pending(current))
               return -EINTR;
     } while (true);

     return 0;
}

int
fusionee_remove_message_callbacks(Fusionee  *fusionee,
                                  void      *ctx)
{
     Packet          *packet;
     MessageCallback *callback, *next;

     D_MAGIC_ASSERT( fusionee, Fusionee );

     /* Search all pending packets. */
     direct_list_foreach (packet, fusionee->packets.items) {
          D_MAGIC_ASSERT( packet, Packet );

          direct_list_foreach_safe (callback, next, packet->callbacks.items) {
               if (callback->ctx == ctx) {
                    fusion_list_remove( &packet->callbacks.items, &callback->link );
                    packet->callbacks.count--;

                    fusion_core_free( fusion_core, callback );
               }
          }
     }

     /* Search packets being processed right now. */
     direct_list_foreach (packet, fusionee->prev_packets.items) {
          D_MAGIC_ASSERT( packet, Packet );

          direct_list_foreach_safe (callback, next, packet->callbacks.items) {
               if (callback->ctx == ctx) {
                    fusion_list_remove( &packet->callbacks.items, &callback->link );
                    packet->callbacks.count--;

                    fusion_core_free( fusion_core, callback );
               }
          }
     }

     return 0;
}

unsigned int
fusionee_poll( FusionDev                *dev,
               Fusionee                 *fusionee,
               struct file              *file,
               struct poll_table_struct *wait )
{
     unsigned int mask = 0;
     
     D_MAGIC_ASSERT( fusionee, Fusionee );
     
     poll_wait( file, &fusionee->wait_receive.queue, wait );

     mask = 0;
     if (fusionee->packets.count && ((Packet *) fusionee->packets.items)->flush)
          mask |= POLLIN | POLLRDNORM;

     return mask;
}

int
fusionee_sync( FusionDev *dev,
               Fusionee  *fusionee )
{
     D_MAGIC_ASSERT( fusionee, Fusionee );

     while (fusionee->packets.count || fusionee->prev_packets.count || !fusionee->waiting) {
          if (fusionee->packets.count) {
               Packet *packet = (Packet*) direct_list_last( fusionee->packets.items );

               D_MAGIC_ASSERT_IF( packet, Packet );

               if (!packet->flush) {
                    packet->flush = true;

//                    fusion_core_wq_wake( fusion_core, &fusionee->wait_receive);
                    wake_up_interruptible_sync_poll( &fusionee->wait_receive.queue, POLLIN | POLLRDNORM );
               }
          }

          fusion_core_wq_wait( fusion_core, &fusionee->wait_process, NULL, true );

          if (signal_pending(current))
               return -EINTR;
     }

     return 0;
}

int
fusionee_kill(FusionDev * dev,
              Fusionee * fusionee, FusionID target, int signal, int timeout_ms)
{
     int timeout = -1;

     while (true) {
          Fusionee *f;
          int killed = 0;

          direct_list_foreach(f, dev->fusionee.list) {
               if (f != fusionee && (!target || target == f->id)) {
                    struct task_struct *p;

#if defined(CONFIG_TREE_RCU) || defined(CONFIG_TREE_PREEMPT_RCU) || defined(CONFIG_TINY_RCU) || defined(rcu_read_lock)
                    rcu_read_lock();
#else
                    read_lock(&tasklist_lock);
#endif

#ifdef for_each_task		/* 2.4 */
                    for_each_task(p) {
#else /* for >= 2.6.0 & redhat WS EL3 w/ 2.4 kernel */
                    for_each_process(p) {
#endif
                         if (p->mm == f->mm) {
                              send_sig_info(signal,
                                            (void *)1L
                                            /* 1 means from kernel */
                                            ,
                                            p);
                              killed++;
                         }
                    }

#if defined(CONFIG_TREE_RCU) || defined(CONFIG_TREE_PREEMPT_RCU) || defined(CONFIG_TINY_RCU) || defined(rcu_read_unlock)
                    rcu_read_unlock();
#else
                    read_unlock(&tasklist_lock);
#endif
               }
          }

          if (!killed || timeout_ms < 0)
               break;

          if (timeout_ms) {
               switch (timeout) {
                    case 0:   /* timed out */
                         return -ETIMEDOUT;

                    case -1:  /* setup timeout */
                         timeout = (timeout_ms * HZ + 500) / 1000;
                         if (!timeout)
                              timeout = 1;

                         /* fall through */

                    default:
                         fusion_core_wq_wait( fusion_core, &dev->fusionee.wait, &timeout, true );
                         break;
               }
          }
          else
               fusion_core_wq_wait( fusion_core, &dev->fusionee.wait, NULL, true );

          if (signal_pending(current))
               return -EINTR;
     }

     return 0;
}

void
fusionee_ref( Fusionee * fusionee )
{
     D_MAGIC_ASSERT( fusionee, Fusionee );

     FUSION_ASSERT( fusionee->refs > 0 );

     fusionee->refs++;
}

void
fusionee_unref( Fusionee * fusionee )
{
     D_MAGIC_ASSERT( fusionee, Fusionee );

     FUSION_ASSERT( fusionee->refs > 0 );

     if (!--fusionee->refs)
          fusion_core_free( fusion_core,  fusionee );
}


void fusionee_destroy(FusionDev * dev, Fusionee * fusionee)
{
     FusionFifo  prev_packets;
     FusionFifo  packets;
     Fusionee   *other;

     D_MAGIC_ASSERT( fusionee, Fusionee );

     FUSION_ASSERT( fusionee->refs > 0 );

     prev_packets = fusionee->prev_packets;
     packets      = fusionee->packets;

     /* Remove from list. */
     direct_list_remove(&dev->fusionee.list, &fusionee->link);

     /* Wake up waiting killer. */
     fusion_core_wq_wake( fusion_core, &dev->fusionee.wait);

     /* Release locks, references, ... */
     fusion_skirmish_dismiss_all(dev, fusionee->id);
     fusion_skirmish_return_all_from(dev, fusionee->id);
     fusion_call_destroy_all(dev, fusionee);
     fusion_reactor_detach_all(dev, fusionee->id);
     fusion_property_cede_all(dev, fusionee->id);
     fusion_ref_clear_all_local(dev, fusionee->id);
     fusion_shmpool_detach_all(dev, fusionee->id);

     /* Free all pending messages. */
     flush_packets(fusionee, dev, &prev_packets);
     flush_packets(fusionee, dev, &packets);

     free_packets(fusionee, dev, &fusionee->free_packets);

     /* Free fusionee data. */
     fusionee_unref( fusionee );

     if (fusionee->id == FUSION_ID_MASTER)
          fusionee_kill( dev, fusionee, 0, SIGKILL, 0 );
     else
          /* Let all others know we're gone... */
          direct_list_foreach (other, dev->fusionee.list)
               fusionee_send_message2( dev, NULL, other, FMT_LEAVE, 0, 0, sizeof(FusionID), &fusionee->id, FMC_NONE, NULL, 0, NULL, 0, true );
}

FusionID fusionee_id(const Fusionee * fusionee)
{
     D_MAGIC_ASSERT( fusionee, Fusionee );

     return fusionee->id;
}

pid_t fusionee_dispatcher_pid(FusionDev * dev, FusionID fusion_id)
{
     Fusionee *fusionee;
     int ret = -EINVAL;

     direct_list_foreach(fusionee, dev->fusionee.list) {
          D_MAGIC_ASSERT( fusionee, Fusionee );

          if (fusionee->id == fusion_id) {
               /* FIXME: wait for it? */
               FUSION_ASSUME(fusionee->dispatcher_pid != 0);

               ret = fusionee->dispatcher_pid;
               break;
          }
     }

     return ret;
}

/******************************************************************************/

static int
lookup_fusionee(FusionDev * dev, FusionID id, Fusionee ** ret_fusionee)
{
     Fusionee *fusionee;

     direct_list_foreach(fusionee, dev->fusionee.list) {
          D_MAGIC_ASSERT( fusionee, Fusionee );

          if (fusionee->id == id) {
               *ret_fusionee = fusionee;
               return 0;
          }
     }

     return -EINVAL;
}

static int lock_fusionee(FusionDev * dev, FusionID id, Fusionee ** ret_fusionee)
{
     int ret;
     Fusionee *fusionee;

     ret = lookup_fusionee(dev, id, &fusionee);
     if (ret)
          return ret;

     D_MAGIC_ASSERT( fusionee, Fusionee );

     direct_list_move_to_front(&dev->fusionee.list, &fusionee->link);

     *ret_fusionee = fusionee;

     return 0;
}

/******************************************************************************/

static void flush_packets(Fusionee *fusionee, FusionDev * dev, FusionFifo * fifo)
{
     Packet *packet;

     D_MAGIC_ASSERT( fusionee, Fusionee );

     while ((packet = (Packet *) fusion_fifo_get(fifo)) != NULL) {
          D_MAGIC_ASSERT( packet, Packet );

          Packet_RunCallbacks( dev, packet );

          Fusionee_PutPacket( fusionee, packet );
     }
}

static void free_packets(Fusionee *fusionee, FusionDev * dev, FusionFifo * fifo)
{
     Packet *packet;

     D_MAGIC_ASSERT( fusionee, Fusionee );

     while ((packet = (Packet *) fusion_fifo_get(fifo)) != NULL) {
          D_MAGIC_ASSERT( packet, Packet );

          Packet_Free( packet );
     }
}
