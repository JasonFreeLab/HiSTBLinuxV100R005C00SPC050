#ifndef __IMG_INFO_H__
#define __IMG_INFO_H__

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------EXTERNAL FUNCTION-------------------------------*/

VOID IMG_Info_Init(VOID);
VOID IMG_Info_Exit(VOID);
VOID IMG_Info_Convert(SINT32 ChanID, IMAGE *pstImage);


#ifdef __cplusplus
}
#endif

#endif
