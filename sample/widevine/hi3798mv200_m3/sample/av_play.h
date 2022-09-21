#ifndef __AV_PLAY_H__
#define __AV_PLAY_H__

#include "general_define.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#include "hi_unf_common.h"
#include "hi_unf_avplay.h"
#include "hi_unf_sound.h"
#include "hi_unf_disp.h"
#include "hi_unf_vo.h"
#include "hi_unf_demux.h"
#include "HA.AUDIO.MP3.decode.h"
#include "HA.AUDIO.MP2.decode.h"
#include "HA.AUDIO.AAC.decode.h"
#include "HA.AUDIO.DRA.decode.h"
#include "HA.AUDIO.PCM.decode.h"
#include "HA.AUDIO.WMA9STD.decode.h"
#include "HA.AUDIO.AMRNB.codec.h"
#include "HA.AUDIO.AMRWB.codec.h"
#include "HA.AUDIO.DOLBYTRUEHD.decode.h"
#include "HA.AUDIO.G711.codec.h"
#include "HA.AUDIO.TRUEHDPASSTHROUGH.decode.h"
#include "HA.AUDIO.DTSHD.decode.h"
#include "HA.AUDIO.AC3PASSTHROUGH.decode.h"
#include "HA.AUDIO.DTSPASSTHROUGH.decode.h"
#include "HA.AUDIO.DTSM6.decode.h"
#include "hi_adp_mpi.h"
#include "hi_adp_hdmi.h"
#include "hi_unf_mce.h"

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

class AvPlay
{
public:
    AvPlay();
    virtual ~AvPlay();

    HI_S32 StartAvPlay();
    HI_S32 GetAvPlayVideoBuffer(IN HI_U8* buffer, IN HI_U32 buffer_len, INOUT HI_U8*& out_buffer);
    HI_S32 PutDataToAvplayVideobuffer(IN HI_U32 buffer_len);
    HI_S32 GetAvPlayAudioBuffer(IN HI_U8* buffer, IN HI_U32 buffer_len, INOUT HI_U8*& out_buffer);
    HI_S32 PutDataToAvplayAudiobuffer(IN HI_U32 buffer_len);

protected:
    HI_S32 AvPlayOpen(HI_HANDLE* ohAVHandle, HI_HANDLE* ohWin);
    HI_S32 HIADP_MCE_Exit(HI_VOID);

private:
    HI_HANDLE hAVPlay;
    HI_HANDLE hWin;
    HI_UNF_STREAM_BUF_S video_stream_buf;
    HI_UNF_STREAM_BUF_S audio_stream_buf;
};

#endif //__AV_PLAY_H__

