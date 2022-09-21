/*--------------------------------------------------------------------------
Copyright (c) 2010-2011, Code Aurora Forum. All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of Code Aurora nor
      the names of its contributors may be used to endorse or promote
      products derived from this software without specific prior written
      permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NON-INFRINGEMENT ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
--------------------------------------------------------------------------*/
#ifndef SAMPLE_OMX_H
#define SAMPLE_OMX_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <fcntl.h>
//#include <sys/types.h>
#include <sys/mman.h>
#include <time.h>

#include <errno.h>
#include <pthread.h>
#include <semaphore.h>

#include <sys/time.h>
//#include <linux/android_pmem.h>

#include <signal.h>

#include "OMX_Core.h"
#include "OMX_Component.h"
#include "OMX_IVCommon.h"
#include "OMX_VideoExt.h"
#include "OMX_IndexExt.h"
#include "hi_common.h"

#include "sample_tidx.h"
#include "sample_queue.h"

#define MAX_INST_NUM 20

//#define CalcFrameRate

typedef enum {
    CODEC_H264 = 0x0,
    CODEC_MPEG2,
    CODEC_MPEG4,
    CODEC_H263,
    CODEC_SORENSON,
	CODEC_AVS,
	CODEC_VC1AP,
	CODEC_VC1SMP,
	CODEC_REAL8,
	CODEC_REAL9,
	CODEC_DIVX3,
	CODEC_VP6,
	CODEC_VP6F,
	CODEC_VP6A,
	CODEC_VP8,
	CODEC_MJPEG,
	CODEC_MPEG1,
    CODEC_HEVC,
    CODEC_MVC,
    CODEC_VP9,

    CODEC_MAX,
} codec_format;

typedef enum {
    GOOD_STATE = 0,
    PORT_SETTING_CHANGE_STATE,
    PORT_SETTING_RECONFIG_STATE,
    ERROR_STATE
} inst_status;

typedef enum {
    THREAD_INVALID = 0,
    THREAD_WAITING,
    THREAD_RUNNING,
    THREAD_BUTT
} thread_status;

typedef enum {
    FREE_HANDLE_AT_LOADED = 1,
    FREE_HANDLE_AT_IDLE,
    FREE_HANDLE_AT_EXECUTING,
    FREE_HANDLE_AT_PAUSE
} freeHandle_test;

enum {
    false    =    0,
    true    =    1
};

struct buf_info {
    int index;
    unsigned int length;
    char *start;
};

typedef struct hiOMXVDEC_TEST_BUF_S
{
    HI_CHAR bufname[16];
    HI_U32  phyaddr;
    HI_U8  *user_viraddr;
    HI_U32  bufsize;
}HI_OMXVDEC_TEST_BUF_S;

typedef int    bool;
typedef OMX_U8* OMX_U8_PTR;

typedef struct
{
    int inst_no;
    int is_open;
    int event_is_done;

    FILE  *inputBufferFileFd;

    Queue *etb_queue;
    Queue *ftb_queue;

    pthread_t ebd_thread_id;
    pthread_t fbd_thread_id;

    //MUTEXT
    pthread_mutex_t   etb_lock;
    pthread_mutex_t   ftb_lock;
    pthread_mutex_t   event_lock;
    pthread_cond_t    event_cond;

    //SEMA
    sem_t etb_sem;
    sem_t ftb_sem;
    sem_t in_flush_sem;
    sem_t out_flush_sem;
    sem_t seek_sem;

    //OMX VAR
    OMX_U32 FrameRate;
    OMX_PARAM_COMPONENTROLETYPE  role;
    OMX_PARAM_PORTDEFINITIONTYPE portFmt;
    OMX_PORT_PARAM_TYPE portParam;

    OMX_COLOR_FORMATTYPE color_fmt;
    //OMX_S64 timeStampLfile;
    OMX_COMPONENTTYPE *dec_handle;
    OMX_BUFFERHEADERTYPE **pInputBufHdrs;
    OMX_BUFFERHEADERTYPE **pOutYUVBufHdrs;

    int height;
    int width;
    int sliceheight;
    int stride;

    int used_ip_buf_cnt;
    int used_op_buf_cnt;
    int free_ip_buf_cnt;
    int free_op_buf_cnt;
    int receive_frame_cnt;

    int bInputEosReached;
    int bOutputEosReached;
    int flush_input_progress;
    int flush_output_progress;
    int seeking_progress;
    int fbd_thread_exit;
    int ebd_thread_exit;

    char in_filename[512];

    int test_option;
    int alloc_use_option;
    int sent_disabled;
    int rewind_enable;
    codec_format codec_format_option;
    freeHandle_test freeHandle_option;

    inst_status currentStatus;
    inst_status preStatus;
    thread_status  EtbStatus;
    thread_status  FtbStatus;

    bool frame_in_packet;
    bool readsize_add_in_stream;

    int last_cmd;
       int start_time;
    int stop_time;
    int frame_flag;
    int send_cnt;
    int read_pos;
    unsigned long frame_len;
    unsigned timestampInterval;

    bool bCRCEnable;
    int tvp_option;
    HI_OMXVDEC_TEST_BUF_S CAStreamBuf;

    HI_MMZ_BUF_S buffer[10];
    STR_CONTEXT_S stContext;

    struct timeval t_first_send;
    struct timeval t_last_get;
    struct timeval t_cur_get;
}OmxTestInfo_S;

typedef struct OMXVDEC_TEST_ATTR
{
    bool auto_exit;
}OMXVDEC_TEST_ATTR;

int omxvdec_test(int argc, char **argv, OMXVDEC_TEST_ATTR *ptest_attr);

#endif
