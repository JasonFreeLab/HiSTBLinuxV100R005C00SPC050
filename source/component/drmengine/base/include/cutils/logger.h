/* utils/logger.h
**
** Copyright 2007-2014, The Android Open Source Project
**
** This file is dual licensed.  It may be redistributed and/or modified
** under the terms of the Apache 2.0 License OR version 2 of the GNU
** General Public License.
*/

#ifndef _LIBS_LOG_LOGGER_H
#define _LIBS_LOG_LOGGER_H

#include <stdint.h>

struct logger_entry {
    uint16_t    len;    /* length of the payload */
    uint16_t    __pad;  /* no matter what, we get 2 bytes of padding */
    int32_t     pid;    /* generating process's pid */
    int32_t     tid;    /* generating process's tid */
    int32_t     sec;    /* seconds since Epoch */
    int32_t     nsec;   /* nanoseconds */
    char        msg[0]; /* the entry's payload */
};

/*
 * The userspace structure for version 2 of the logger_entry ABI.
 * This structure is returned to userspace if ioctl(LOGGER_SET_VERSION)
 * is called with version==2; or used with the user space log daemon.
 */
struct logger_entry_v2 {
    uint16_t    len;       /* length of the payload */
    uint16_t    hdr_size;  /* sizeof(struct logger_entry_v2) */
    int32_t     pid;       /* generating process's pid */
    int32_t     tid;       /* generating process's tid */
    int32_t     sec;       /* seconds since Epoch */
    int32_t     nsec;      /* nanoseconds */
    uint32_t    euid;      /* effective UID of logger */
    char        msg[0];    /* the entry's payload */
} __attribute__((__packed__));

struct logger_entry_v3 {
    uint16_t    len;       /* length of the payload */
    uint16_t    hdr_size;  /* sizeof(struct logger_entry_v3) */
    int32_t     pid;       /* generating process's pid */
    int32_t     tid;       /* generating process's tid */
    int32_t     sec;       /* seconds since Epoch */
    int32_t     nsec;      /* nanoseconds */
    uint32_t    lid;       /* log id of the payload */
    char        msg[0];    /* the entry's payload */
} __attribute__((__packed__));

#define LOGGER_LOG_MAIN        "log_main"
#define LOGGER_LOG_RADIO    "log_radio"
#define LOGGER_LOG_EVENTS    "log_events"
#define LOGGER_LOG_SYSTEM    "log_system"

#define LOGGER_ENTRY_MAX_LEN        (4*1024)
#define LOGGER_ENTRY_MAX_PAYLOAD    \
    (LOGGER_ENTRY_MAX_LEN - sizeof(struct logger_entry))

#ifdef HAVE_IOCTL

#include <sys/ioctl.h>

#define __LOGGERIO    0xAE

#define LOGGER_GET_LOG_BUF_SIZE        _IO(__LOGGERIO, 1) /* size of log */
#define LOGGER_GET_LOG_LEN        _IO(__LOGGERIO, 2) /* used log len */
#define LOGGER_GET_NEXT_ENTRY_LEN    _IO(__LOGGERIO, 3) /* next entry len */
#define LOGGER_FLUSH_LOG        _IO(__LOGGERIO, 4) /* flush log */

#endif // HAVE_IOCTL

#endif /* _LIBS_LOG_LOGGER_H */
