#include "file_parser.h"

#define KEY_ID_LEN          (32)
#define OUT_KEY_ID_LEN      ((KEY_ID_LEN) / 2)
#define FRAME_NUMBER_LEN    (4)
#define FRAME_HEAD_OFFSET   (0)
#define WV_BUFFER_SIZE      (0x200000)

FILE* fp = HI_NULL;
HI_S32 file_len = 0;
HI_U8* input_buffer = HI_NULL;
HI_U32 read_offset = FRAME_HEAD_OFFSET;
HI_U32 last_frame_seqno = 0;

using namespace std;

FileParser::FileParser()
{
}

FileParser::~FileParser()
{
}

HI_S32 FileParser::ParserStreamInit(IN HI_CHAR* file_path)
{
    CHK_ARG(file_path != NULL);

    fp = fopen(file_path, "rb");

    if (HI_NULL == file_path)
    {
        WVLOGE("%s fopen %s fail\n", __FUNCTION__, file_path);
        return HI_FAILURE;
    }

    //get file length
    fseek(fp, 0, SEEK_END);
    file_len = ftell(fp);
    WVLOGD("%s file_len = %d\n", __FUNCTION__, file_len);

    if (0 >= file_len)
    {
        WVLOGE("%s get file length fail, file_len = %d\n", __FUNCTION__, file_len);
        return HI_FAILURE;
    }

    input_buffer = (HI_U8*)malloc(WV_BUFFER_SIZE);

    if (HI_NULL == input_buffer)
    {
        WVLOGE("%s Malloc input_buffer fail\n", __FUNCTION__);
        return HI_FAILURE;
    }

    memset(input_buffer, 0, WV_BUFFER_SIZE);
    return HI_SUCCESS;
}

HI_S32 FileParser::ParserStreamDeInit()
{
    WVLOGD("Enter %s\n", __FUNCTION__);

    if (HI_NULL != input_buffer)
    {
        free(input_buffer);
        input_buffer = HI_NULL;
    }

    if (HI_NULL != fp)
    {
        fclose(fp);
        fp = HI_NULL;
    }

    return HI_SUCCESS;
}

HI_VOID FileParser::TransformKid(IN const HI_CHAR* key, HI_CHAR* content_key)
{
    int i = 0;
    int n = 0;

    for (i = 0; i < strlen(key); i += 2)
    {
        if (key[i] >= 'A' && key[i] <= 'F')
        {
            content_key[n] = key[i] - 'A' + 10;
        }
        else if (key[i] >= 'a' && key[i] <= 'f')
        {
            content_key[n] = key[i] - 'a' + 10;
        }
        else
        {
            content_key[n] = key[i] - '0';
        }

        if(key[i + 1] >= 'A' && key[i + 1] <= 'F')
        {
            content_key[n] = (content_key[n] << 4) | (key[i + 1] - 'A' + 10);
        }
        else if (key[i + 1] >= 'a' && key[i + 1] <= 'f')
        {
            content_key[n] = (content_key[n] << 4) | (key[i + 1] - 'a' + 10);
        }
        else
        {
            content_key[n] = (content_key[n] << 4) | (key[i + 1] - '0');
        }
        ++n;
    }
}

HI_S32 FileParser::GetDrmHead(OUT string& url, OUT string& video_key_id, OUT string& audio_key_id)
{
    HI_CHAR url_read[255] = {0};
    HI_CHAR video_key_id_read[KEY_ID_LEN + 1] = {0};  // origin video kid read from media file
    HI_CHAR audio_key_id_read[KEY_ID_LEN + 1] = {0};  // origin audio kid read from media file
    HI_CHAR video_key_id_out[OUT_KEY_ID_LEN + 1] = {0};   // output video kid used to decrypt
    HI_CHAR audio_key_id_out[OUT_KEY_ID_LEN + 1] = {0};   // output audio kid used to decrypt
    HI_CHAR frame_number_read[FRAME_NUMBER_LEN] = {0};
    HI_S32 url_read_len = 0;
    HI_S32 video_key_id_read_len = 0;
    HI_S32 audio_key_id_read_len = 0;
    HI_S32 ret = 0;

    fseek(fp, 0, SEEK_SET);

    // get url of the media file.
    ret = fscanf(fp, "%255s", url_read);
    if (ret < 0)
    {
        WVLOGE("Can not find url in stream file!\n");
        return HI_FAILURE;
    }
    WVLOGD("url:%s\n", url_read);
    url.assign(url_read);
    url_read_len = strlen(url_read);
    read_offset += (url_read_len + 1);
    WVLOGD("url_read_len:%d, read_offset:%d\n", url_read_len, read_offset);
    fseek(fp, read_offset, SEEK_SET);

    // get video kid of the media file.
    ret = fscanf(fp, "%33s", video_key_id_read);
    if (ret < 0)
    {
        WVLOGE("Can not find video kid in stream file!\n");
        return HI_FAILURE;
    }
    video_key_id_read_len = strlen(video_key_id_read);
    read_offset += (video_key_id_read_len + 1);
    WVLOGD("video_key_id_read_len:%d, read_offset:%d\n", video_key_id_read_len, read_offset);
    fseek(fp, read_offset, SEEK_SET);

    // transform the video kid to output video kid used to decrypt
    TransformKid(video_key_id_read, video_key_id_out);
    video_key_id.assign(video_key_id_out);

    // get audio kid of the media file.
    ret = fscanf(fp, "%33s", audio_key_id_read);
    if (ret < 0)
    {
        WVLOGE("Can not find audio kid in stream file!\n");
        return HI_FAILURE;
    }
    audio_key_id_read_len = strlen(audio_key_id_read);
    read_offset += (audio_key_id_read_len + 1);
    WVLOGD("audio_key_id_read_len:%d, read_offset:%d\n", audio_key_id_read_len, read_offset);
    fseek(fp, read_offset, SEEK_SET);

    // transform the audio kid to output audio kid used to decrypt
    TransformKid(audio_key_id_read, audio_key_id_out);
    audio_key_id.assign(audio_key_id_out);

    // get the total frame number of the media file.
    ret = fread(&last_frame_seqno, 1, sizeof(HI_U32), fp);
    if (ret < 0)
    {
        WVLOGE("Can not find frame number in stream file!\n");
        return HI_FAILURE;
    }
    read_offset += FRAME_NUMBER_LEN;
    WVLOGD("read_offset:%d\n", read_offset);

    WVLOGD("url = %s, video_key_id_read = %s, audio_key_id_read = %s, last_frame_seqno:%d\n", url_read, video_key_id_read, audio_key_id_read, last_frame_seqno);

    return HI_SUCCESS;
}

HI_S32 FileParser::GetOneFrame(OUT STRU_FRAME_PARAM* frame_param)
{
    CHK_ARG(frame_param != NULL);

    HI_U32 frame_total_len = 0;
    HI_U32 num_subsample = 0;
    HI_U32 i = 0;
    WVLOGD("Enter %s\n", __FUNCTION__);
    WVLOGD("read_offset = %d\n", read_offset);

    if (read_offset >= file_len)
    {
        WVLOGE("file_len = %d\n", file_len);
        WVLOGE("read_offset >= file_len, no more frame to read!\n");
        return HI_FAILURE;
    }

    fseek(fp, read_offset, SEEK_SET);

    if (fread(&frame_total_len, 1, sizeof(HI_U32), fp) != sizeof(HI_U32))
    {
        WVLOGE("read frame_total_len fail\n");
        return HI_FAILURE;
    }

    WVLOGD("frame_total_len = %d\n", frame_total_len);

    if (read_offset + frame_total_len > file_len)
    {
        WVLOGE("file_len = %d\n", file_len);
        WVLOGE("read_offset + frame_total_len > file_len, no more frame to read!\n");
        return HI_FAILURE;
    }

    if (fread(&(frame_param->frame_number), 1, sizeof(HI_U32), fp) != sizeof(HI_U32))
    {
        WVLOGE("read frame_number fail\n");
        return HI_FAILURE;
    }

    WVLOGD("frame_param->frame_number = %d\n", frame_param->frame_number);

    if (fread(&(frame_param->is_secure), 1, sizeof(HI_U8), fp) != sizeof(HI_U8))
    {
        WVLOGE("read is_secure fail\n");
        return HI_FAILURE;
    }

    WVLOGD("frame_param->is_secure = %d\n", frame_param->is_secure);

    if (fread(frame_param->iv, 1, KEY_IV_SIZE, fp) != KEY_IV_SIZE)
    {
        WVLOGE("read iv vector fail\n");
        return HI_FAILURE;
    }

    if (fread(&(frame_param->numSubsamples), 1, sizeof(HI_U32), fp) != sizeof(HI_U32))
    {
        WVLOGE("read num_subsample fail\n");
        return HI_FAILURE;
    }

    WVLOGD("num_subsample = %d\n", frame_param->numSubsamples);

    frame_param->frame_buffer_length = 0;

    for (i = 0; i < 2 * (frame_param->numSubsamples); i++)
    {
        if (fread(&(frame_param->subsampleMaps[i]), 1, sizeof(HI_U32), fp) != sizeof(HI_U32))
        {
            WVLOGE("read subsampleMaps[%d] fail\n", i);
            return HI_FAILURE;
        }

        WVLOGD("subsampleMaps[%d] = %d\n", i, frame_param->subsampleMaps[i]);
        frame_param->frame_buffer_length += frame_param->subsampleMaps[i];
    }

    if (0 != frame_param->frame_buffer_length)
    {
        if (fread(input_buffer, 1, frame_param->frame_buffer_length, fp) != frame_param->frame_buffer_length)
        {
            WVLOGE("read frame_buffer fail\n", i);
            return HI_FAILURE;
        }
    }

    frame_param->frame_buffer = input_buffer;
    WVLOGD("frame_param->frame_buffer_length = %d\n", frame_param->frame_buffer_length);

    if (last_frame_seqno == frame_param->frame_number)
    {
        WVLOGD("This is the last frame!\n");
        frame_param->is_last_frame = HI_TRUE;
        read_offset = FRAME_HEAD_OFFSET;
    }
    else
    {
        frame_param->is_last_frame = HI_FALSE;
        read_offset += frame_total_len;
    }

    return HI_SUCCESS;
}
