#ifndef __VPSS_CBB_ASSERT_H__
#define __VPSS_CBB_ASSERT_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define MAX(a,b)             (((a) < (b)) ? (b) : (a))
#define MIN(a,b)             (((a) > (b)) ? (b) : (a))
//#define ABS(x)               (((x) < 0) ? -(x) : (x))
#define CLIP(x)              (((x) < 0) ? 0 : (x))
#define CLIP1(high,x)        (MAX(MIN((x),high), 0))
//#define CLIP3(low,high,x)    (MAX(MIN((x),high), low))
#define CLIP255(x)           (MAX(MIN((x),255), 0))
#define CLIP1023(x)          (MAX(MIN((x),1023), 0))

#define YUV422               1
#define YUV420               0
#define DEI_BIT_DEPTH        8
#define DEI_HALFVALUE        (DEI_BIT_DEPTH == 8 ? 4 : 16)
#define DEI_SHIFT            (DEI_BIT_DEPTH == 8 ? 3 : 5)

HI_VOID VPSS_HAL_Assert(HI_S32 s32NodeId, volatile S_VPSS_REGS_TYPE *vpss_reg);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

