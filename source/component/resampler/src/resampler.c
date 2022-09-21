
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "resampler_public.h"
#include "resampler2X.h"
#include "resampler_v2.h"
#include "resampler_statname.h"
#include "hi_module.h"
#include "hi_debug.h"

typedef struct
{
    int    inrate;
    int    outrate;
    int    convertfrac;
} src_frac_t;

static const src_frac_t SRCFracTable_Mono[]={
    {RESAMPLE_RATE_08K, RESAMPLE_RATE_16K, RESAMPLE_1X2},
    {RESAMPLE_RATE_08K, RESAMPLE_RATE_32K, RESAMPLE_1X4},
    {RESAMPLE_RATE_08K, RESAMPLE_RATE_48K, RESAMPLE_1X6},
    {RESAMPLE_RATE_16K, RESAMPLE_RATE_08K, RESAMPLE_2X1},
    {RESAMPLE_RATE_16K, RESAMPLE_RATE_32K, RESAMPLE_1X2},
    {RESAMPLE_RATE_22K, RESAMPLE_RATE_44K, RESAMPLE_1X2},
    {RESAMPLE_RATE_32K, RESAMPLE_RATE_08K, RESAMPLE_4X1},
    {RESAMPLE_RATE_32K, RESAMPLE_RATE_16K, RESAMPLE_2X1},
    {RESAMPLE_RATE_44K, RESAMPLE_RATE_22K, RESAMPLE_2X1},
    {RESAMPLE_RATE_48K, RESAMPLE_RATE_08K, RESAMPLE_6X1},
};

static const src_frac_t SRCFracTable_Stereo[]={
    {RESAMPLE_RATE_08K, RESAMPLE_RATE_16K, RESAMPLE_1X2},
    {RESAMPLE_RATE_08K, RESAMPLE_RATE_32K, RESAMPLE_1X4},
    {RESAMPLE_RATE_08K, RESAMPLE_RATE_48K, RESAMPLE_1X6},
    {RESAMPLE_RATE_16K, RESAMPLE_RATE_08K, RESAMPLE_2X1},
    {RESAMPLE_RATE_16K, RESAMPLE_RATE_32K, RESAMPLE_1X2},
    {RESAMPLE_RATE_22K, RESAMPLE_RATE_44K, RESAMPLE_1X2},
    {RESAMPLE_RATE_32K, RESAMPLE_RATE_08K, RESAMPLE_4X1},
    {RESAMPLE_RATE_32K, RESAMPLE_RATE_16K, RESAMPLE_2X1},
    {RESAMPLE_RATE_44K, RESAMPLE_RATE_22K, RESAMPLE_2X1},
    {RESAMPLE_RATE_48K, RESAMPLE_RATE_08K, RESAMPLE_6X1},
};

HResampler HI_Resampler_Create(int inrate, int outrate, int chans)
{
    int i,num;
    src_frac_t  *pstSRCFracTable = NULL;

    switch (inrate)
    {
    case RESAMPLE_RATE_08K:
    case RESAMPLE_RATE_11K:
    case RESAMPLE_RATE_12K:
    case RESAMPLE_RATE_16K:
    case RESAMPLE_RATE_22K:
    case RESAMPLE_RATE_24K:
    case RESAMPLE_RATE_32K:
    case RESAMPLE_RATE_44K:
    case RESAMPLE_RATE_48K:
    case RESAMPLE_RATE_88K:
    case RESAMPLE_RATE_96K:
    case RESAMPLE_RATE_176K:
    case RESAMPLE_RATE_192K:
        break;
    default:
        HI_RESAMPLE_PRINT(HI_ID_SRC, " Invalid inrate [%d] \n", inrate);
        return NULL;
    }

    switch (outrate)
    {
    case RESAMPLE_RATE_08K:
    case RESAMPLE_RATE_11K:
    case RESAMPLE_RATE_12K:
    case RESAMPLE_RATE_16K:
    case RESAMPLE_RATE_22K:
    case RESAMPLE_RATE_24K:
    case RESAMPLE_RATE_32K:
    case RESAMPLE_RATE_44K:
    case RESAMPLE_RATE_48K:
    case RESAMPLE_RATE_88K:
    case RESAMPLE_RATE_96K:
    case RESAMPLE_RATE_176K:
    case RESAMPLE_RATE_192K:
        break;
    default:
        HI_RESAMPLE_PRINT(HI_ID_SRC, " Invalid outrate [%d] \n", outrate);
        return NULL;
    }

    if ((chans != MONO) && (chans != STEREO))
    {
        HI_RESAMPLE_PRINT(HI_ID_SRC, " Invalid channels [%d] \n", chans);
        return NULL;
    }

    if (inrate == outrate)
    {
        return Resampler2X_Create(inrate, outrate, RESAMPLE_1X1, chans);
    }

    if (chans == MONO)
    {
        pstSRCFracTable = (src_frac_t *)SRCFracTable_Mono;
        num = sizeof(SRCFracTable_Mono)/sizeof(src_frac_t);
    }
    else //if(chans == STEREO)
    {
        pstSRCFracTable = (src_frac_t *)SRCFracTable_Stereo;
        num = sizeof(SRCFracTable_Stereo)/sizeof(src_frac_t);
    }

    for(i=0; i < num; i++)
    {
       if((inrate == pstSRCFracTable->inrate)&&(outrate == pstSRCFracTable->outrate))
           return Resampler2X_Create(inrate, outrate, pstSRCFracTable->convertfrac, chans);
       pstSRCFracTable++;
    }

    if(i >= num)
    {
        return NEW_ResamplerCreate(inrate, outrate, chans, 16, 0);
    }

    return NULL;
}

int  HI_Resampler_Process(HResampler inst, short *inbuf, int insamps, short *outbuf)
{
    if (!inst || !inbuf || !outbuf)
    {
        return 0;
    }

    state_t *s = (state_t *)inst;
    if(1 == s->isResampler2X)
    {
        return Resampler2X_Process(s, inbuf, insamps, outbuf);
    }
    else
    {
        return NEW_ResamplerProcessFrame(s, (int *)inbuf, (int *)outbuf, insamps, s->inrate, s->outrate, 1);
    }

}

void HI_Resampler_Free(HResampler inst)
{
    if(NULL != inst)
    {
        state_t *s = (state_t *)inst;
        if(1 == s->isResampler2X)
        {
            Resampler2X_Free(s);
        }
        else
        {
            NEW_ResamplerFree(s);
        }
    }
}
