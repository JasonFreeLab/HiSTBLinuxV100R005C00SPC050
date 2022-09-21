/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : tsplay.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2010/01/26
  Description   :
  History       :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <assert.h>
#include <signal.h>

#include "hi_unf_common.h"
#include "hi_unf_ecs.h"
#include "hi_unf_avplay.h"
#include "hi_unf_sound.h"
#include "hi_unf_disp.h"
#include "hi_unf_vo.h"
#include "hi_unf_demux.h"
#include "hi_adp_hdmi.h"
#include "hi_adp_mpi.h"
#include "hi_unf_tsio.h"

#include "HA.AUDIO.MP3.decode.h"
#include "HA.AUDIO.MP2.decode.h"
#include "HA.AUDIO.AAC.decode.h"
#include "HA.AUDIO.DRA.decode.h"
#include "HA.AUDIO.PCM.decode.h"
#include "HA.AUDIO.WMA9STD.decode.h"
#include "HA.AUDIO.AMRNB.codec.h"

FILE *g_pBulkFile = HI_NULL;

HI_HANDLE g_hTsio;
HI_HANDLE g_hTsioInjHandle;

static pthread_t   g_TsioInjThd, g_DecryptRcvThd;

static HI_BOOL     g_bStopTsioInjThread = HI_FALSE, g_bStopDecryptRcvThread = HI_FALSE;

static pthread_mutex_t g_InjMutex = PTHREAD_MUTEX_INITIALIZER;

HI_VOID TsioInjTthread(HI_VOID *args)
{
    HI_UNF_TSIO_BUFFER_S  Buf = {0};
    HI_U32                Readlen;
    HI_S32                Ret;

    while (!g_bStopTsioInjThread)
    {
		pthread_mutex_lock(&g_InjMutex);
        Ret = HI_UNF_TSIO_GetBuffer(g_hTsioInjHandle, 192 * 50, &Buf, 1000);
        if (Ret != HI_SUCCESS )
        {
            pthread_mutex_unlock(&g_InjMutex);
            continue;
        }

loop:
        Readlen = fread(Buf.pu8Data, sizeof(HI_S8), 192 * 50, g_pBulkFile);
        if(Readlen <= 0 || Readlen != 192 * 50)
        {
            printf("read ts file end and rewind!\n");
            rewind(g_pBulkFile);
            goto loop;
        }

        Ret = HI_UNF_TSIO_PutBuffer(g_hTsioInjHandle, &Buf);
        if (Ret != HI_SUCCESS )
        {
            printf("call HI_UNF_TSIO_PutBuffer failed.\n");
        }

        pthread_mutex_unlock(&g_InjMutex);
    }

    return;
}

HI_S32 HIADP_TSIO_Init(HI_VOID)
{
    HI_S32 Ret = HI_FAILURE;
    HI_UNF_TSIO_BUFFER_ATTR_S   RamAttrs = {
        .enStreamType   = HI_UNF_TSIO_RAM_BULK_192,
        .u32BufSize     = 2 * 1024 * 1024,
        .u32MaxDataRate = 0,
    };
    HI_UNF_TSIO_ATTR_S          SrvAttrs = {
        .stOutput       = {
            .enOutputType = HI_UNF_TSIO_OUTPUT_RAM,
            .unParam = {
                .stRAM = {
                    .u32BufferSize = 4 * 1024 * 1024,
                    .enStreamType  = HI_UNF_TSIO_RAM_BULK_192,
                }
            }
        },
        .u32SID         = 0xffffffff,
    };

    Ret = HI_UNF_TSIO_Init(HI_NULL);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_TSIO_Init failed.\n");
        goto out0;
    }

    Ret = HI_UNF_TSIO_CreateBuffer(HI_UNF_TSIO_ANY_RAM_PORT, &RamAttrs, &g_hTsioInjHandle);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_TSIO_CreateBuffer failed.\n");
        goto out1;
    }

    Ret = HI_UNF_TSIO_Create(&SrvAttrs, &g_hTsio);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_TSIO_Create failed.\n");
        goto out2;
    }

    Ret = HI_UNF_TSIO_AttachRAMInput(g_hTsio, g_hTsioInjHandle);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_TSIO_AttachRAMInput failed.\n");
        goto out3;
    }

    Ret = HI_UNF_TSIO_Start(g_hTsio);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_TSIO_Start failed.\n");
        goto out4;
    }

    g_bStopTsioInjThread = HI_FALSE;
    pthread_create(&g_TsioInjThd, HI_NULL, (HI_VOID *)TsioInjTthread, HI_NULL);

    return Ret;

out4:
    HI_UNF_TSIO_DetachInput(g_hTsio);
out3:
    HI_UNF_TSIO_Destroy(g_hTsio);
out2:
    HI_UNF_TSIO_DestroyBuffer(g_hTsioInjHandle);
out1:
    HI_UNF_TSIO_DeInit();
out0:
    return Ret;
}

HI_VOID DecryptRcvThread(HI_VOID *args)
{
    HI_S32 ret = HI_FAILURE;
    HI_UNF_TSIO_BUFFER_S BulkBuf;
    int handle;

    handle = open("./bulk.decrypt", O_CREAT | O_RDWR | O_TRUNC, S_IRWXO | S_IRWXG | S_IRWXU);
    assert(-1 != handle);

    while(!g_bStopDecryptRcvThread)
    {
        ret = HI_UNF_TSIO_AcquireBuffer(g_hTsio, 192* 50, &BulkBuf, 1000);
        if (HI_SUCCESS != ret)
        {
            printf("acquire failed(0x%x).\n", ret);
            continue;
        }

        ret = write(handle, BulkBuf.pu8Data, BulkBuf.u32Length);
        assert(-1 != ret);

        HI_UNF_TSIO_ReleaseBuffer(g_hTsio, &BulkBuf);
    }

    close(handle);
}

HI_S32 HIADP_DECRYPT_Init(HI_U32 ProgNum)
{
    g_bStopDecryptRcvThread = HI_FALSE;
    pthread_create(&g_DecryptRcvThd, HI_NULL, (HI_VOID *)DecryptRcvThread, HI_NULL);

    return HI_SUCCESS;
}

HI_S32 main(HI_S32 argc, HI_CHAR *argv[])
{
    HI_S32                      Ret;
    HI_CHAR                     InputCmd[32];
    HI_U32                      ProgNum;

    g_pBulkFile = fopen(argv[1], "rb");
    if (!g_pBulkFile)
    {
        printf("open file %s error!\n", argv[1]);
        return -1;
    }

    HI_SYS_Init();

    Ret = HIADP_TSIO_Init();
    if (HI_SUCCESS != Ret)
    {
        printf("call HIADP_TSIO_Init failed.\n");
        goto SYS_DEINIT;
    }

    pthread_mutex_lock(&g_InjMutex);
    rewind(g_pBulkFile);
    HI_UNF_TSIO_ResetBuffer(g_hTsioInjHandle);
    pthread_mutex_unlock(&g_InjMutex);

    Ret = HIADP_DECRYPT_Init(ProgNum);
    if (HI_SUCCESS != Ret)
    {
        printf("call HIADP_ES_Init failed.\n");
        goto TSIO_DEINIT;
    }

    while (1)
    {
        printf("please input 'q' to quit!\n");
        SAMPLE_GET_INPUTCMD(InputCmd);

        if ('q' == InputCmd[0])
        {
            printf("prepare to quit!\n");
            break;
        }
    }

    g_bStopDecryptRcvThread = HI_TRUE;
    pthread_join(g_DecryptRcvThd, HI_NULL);

TSIO_DEINIT:
    g_bStopTsioInjThread = HI_TRUE;
    pthread_join(g_TsioInjThd, HI_NULL);
    HI_UNF_TSIO_DeInit();

SYS_DEINIT:
    HI_SYS_DeInit();

    fclose(g_pBulkFile);
    g_pBulkFile = HI_NULL;

    return Ret;
}


