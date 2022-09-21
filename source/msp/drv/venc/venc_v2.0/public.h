#ifndef __VENC_PUBLIC_H__
#define __VENC_PUBLIC_H__

#ifdef __cplusplus
extern "C" {
#endif

enum
{
    VEDU_H264  = 0,
    VEDU_JPGE  = 1,
    VEDU_H265  = 2,
};

enum
{
    VEDU_H264_BASELINE_PROFILE    = 0,
    VEDU_H264_MAIN_PROFILE    = 1,
    VEDU_H264_EXTENDED_PROFILE = 2,
    VEDU_H264_HIGH_PROFILE  = 3,
    VEDU_H264_PROFILE_BUTT  = 4
};

#ifdef __cplusplus
}
#endif

#endif  // __VENC_PUBLIC_H__

