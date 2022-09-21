#include <unistd.h>
#include <memory>
#include "general_define.h"
#include "widevine_process.h"
#include "file_parser.h"
#include "av_play.h"

#define MAX_CMD_LEN         (32)
#define MIN_AUDIO_FRAME_LEN (2)

using namespace std;

typedef struct
{
    shared_ptr<TvpSampleWidevineProcess> widevine_process;
    shared_ptr<AvPlay> av_play;
    shared_ptr<FileParser> file_parser;
    string video_key_id;
    string audio_key_id;
}STRU_THREAD_INPUT_PARAM;

static HI_BOOL g_stop_thread = HI_FALSE;

HI_VOID* EsDecryptThread(HI_VOID* args)
{
    HI_U8* out_buffer = NULL;
    HI_S32 ret = 0;
    STRU_FRAME_PARAM frame_param = {0};
    STRU_THREAD_INPUT_PARAM* pst_thread_input_param;
    pst_thread_input_param = (STRU_THREAD_INPUT_PARAM*)args;
    shared_ptr<TvpSampleWidevineProcess> widevine_process = pst_thread_input_param->widevine_process;
    shared_ptr<AvPlay> av_play = pst_thread_input_param->av_play;
    shared_ptr<FileParser> file_parser = pst_thread_input_param->file_parser;
    string video_key_id = pst_thread_input_param->video_key_id;
    string audio_key_id = pst_thread_input_param->audio_key_id;

    while (!frame_param.is_last_frame && ! g_stop_thread)
    {
        ret = file_parser->GetOneFrame(&frame_param);

        if (0 != ret)
        {
            WVLOGE("GetOneFrame error\n");
            break;
        }

        //usleep(5000);

        if (frame_param.is_secure)
        {
            WVLOGD("Before GetAvPlayVideoBuffer frame_buffer:0x%x, frame_buffer_length:%d\n", frame_param.frame_buffer, frame_param.frame_buffer_length);
            while (HI_SUCCESS != av_play->GetAvPlayVideoBuffer(frame_param.frame_buffer, frame_param.frame_buffer_length, out_buffer))
	        {
                usleep(15000);
            }
            WVLOGD("Before video DecryptData out_buffer:0x%x\n", out_buffer);
            //we need call widevine decrypt method in the case of both clear stream and encrypt stream.
            widevine_process->DecryptData(&frame_param, video_key_id, (HI_VOID*)out_buffer);
            av_play->PutDataToAvplayVideobuffer(frame_param.frame_buffer_length);
            usleep(15000);
        }
        else if (frame_param.frame_buffer_length > MIN_AUDIO_FRAME_LEN)
        {
            WVLOGD("Before GetAvPlayAudioBuffer frame_buffer:0x%x\n, frame_buffer_length:%d\n", frame_param.frame_buffer, frame_param.frame_buffer_length);
            while (HI_SUCCESS != av_play->GetAvPlayAudioBuffer(frame_param.frame_buffer, frame_param.frame_buffer_length, out_buffer))
            {
                usleep(5000);
            }
            WVLOGD("Before audio DecryptData out_buffer:0x%x\n", out_buffer);
            widevine_process->DecryptData(&frame_param, audio_key_id, (HI_VOID*)out_buffer);
            av_play->PutDataToAvplayAudiobuffer(frame_param.frame_buffer_length);
            usleep(5000);
        }
    }
}

HI_S32 main(HI_S32 argc, HI_CHAR** argv)
{
    WV_PROMPT("Enter main.\n");
    HI_CHAR* file_path = NULL;
    HI_U8* source_stream = NULL;
    HI_U8* es_stream = NULL;
    HI_U8* content_key = NULL;
    HI_U32 content_key_length = 0;
    HI_S32 ret = 0;
    string video_key_id = "";
    string audio_key_id = "";
    string url = "";
    pthread_t es_decrypt_thread;
    HI_CHAR InputCmd[MAX_CMD_LEN] = {0};
    STRU_THREAD_INPUT_PARAM st_thread_input_param;
    shared_ptr<TvpSampleWidevineProcess> widevine_process;
    shared_ptr<AvPlay> av_play;
    shared_ptr<FileParser> file_parser;

    if (!widevine_process.get())
    {
        widevine_process.reset(new TvpSampleWidevineProcess);
    }

    if (!av_play.get())
    {
        av_play.reset(new AvPlay);
    }

    if (!file_parser.get())
    {
        file_parser.reset(new FileParser);
    }

    if (argc < 2)
    {
        WVLOGE("Please enter widevine media file path.\n");
        WVLOGE("usage: sample_tvp_play /usr/data/Nobody.mp4\n");

        return HI_FAILURE;
    }

    file_path = argv[1];
    WVLOGD("file path:%s\n", argv[1]);

    ret = file_parser->ParserStreamInit(file_path);

    if (HI_SUCCESS != ret)
    {
        WVLOGE("ParserStreamInit fail!\n");
        return HI_FAILURE;
    }

    ret = file_parser->GetDrmHead(url, video_key_id, audio_key_id);
    WVLOGD("GetDrmHead, return code:0x%x, url:%s, video_key_id:%s, audio_key_id:%s\n", ret, url.c_str(), video_key_id.c_str(), audio_key_id.c_str());

    if (HI_SUCCESS != ret)
    {
        WVLOGE("GetDrmHead fail!\n");
        return HI_FAILURE;
    }

    ret = widevine_process->StartWidevineProcess(video_key_id, url, content_key, content_key_length);
    WVLOGD("StartWidevineProcess, return code:0x%x, video_key_id:%s, url:%s\n", ret, video_key_id.c_str(), url.c_str());

    if (HI_SUCCESS != ret)
    {
        WVLOGE("StartWidevineProcess fail!\n");
        return HI_FAILURE;
    }

    ret = av_play->StartAvPlay();
    WVLOGD("StartAvPlay, return code:0x%x\n", ret);

    if (HI_SUCCESS != ret)
    {
        WVLOGE("StartAvPlay fail!\n");
        return HI_FAILURE;
    }

    st_thread_input_param.widevine_process = widevine_process;
    st_thread_input_param.av_play = av_play;
    st_thread_input_param.file_parser = file_parser;
    st_thread_input_param.video_key_id = video_key_id;
    st_thread_input_param.audio_key_id = audio_key_id;
    pthread_create(&es_decrypt_thread, HI_NULL, EsDecryptThread, (HI_VOID*)&st_thread_input_param);

    WV_PROMPT("Play Start!\n\n");
    while (HI_TRUE)
    {
        WV_PROMPT("Please input the 'q' to quit!\n");
        SAMPLE_GET_INPUTCMD(InputCmd);

        if ('q' == InputCmd[0])
        {
            WV_PROMPT("prepare to quit!\n");
            break;
        }
    }

    g_stop_thread = HI_TRUE;
    pthread_join(es_decrypt_thread, HI_NULL);

    file_parser->ParserStreamDeInit();

    return HI_SUCCESS;
}
