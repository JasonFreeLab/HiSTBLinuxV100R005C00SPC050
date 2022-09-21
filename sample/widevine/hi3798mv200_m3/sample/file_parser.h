#ifndef __FILE_PARSER_H__
#define __FILE_PARSER_H__

#include "general_define.h"

using namespace std;

#define KEY_ID_SIZE    (16)
#define KEY_IV_SIZE    (16)
#define kAESBlockSize  (16)
#define MAX_SUBSAMPLE_NUMBER    (16)

typedef struct
{
    HI_U8* frame_buffer;
    HI_U32 frame_buffer_length;
    HI_U8 iv[KEY_IV_SIZE];
    HI_U32 frame_number;
    bool is_last_frame;
    bool is_secure;
    HI_U32 subsampleMaps[MAX_SUBSAMPLE_NUMBER];
    HI_U32 numSubsamples;
} STRU_FRAME_PARAM;

class FileParser
{
public:
    FileParser();
    virtual ~FileParser();
    HI_S32 ParserStreamInit(IN HI_CHAR* file_path);
    HI_S32 ParserStreamDeInit();
    HI_VOID TransformKid(IN const HI_CHAR* key, HI_CHAR* content_key);
    HI_S32 GetDrmHead(OUT string& url, OUT string& video_key_id, OUT string& audio_key_id);
    HI_S32 GetOneFrame(OUT STRU_FRAME_PARAM* frame_param);
};

#endif //__FILE_PARSER_H__

