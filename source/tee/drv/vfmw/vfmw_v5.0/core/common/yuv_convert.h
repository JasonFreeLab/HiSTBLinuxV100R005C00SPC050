#ifndef __DBG_YUV_CONVERT_HEADER__
#define __DBG_YUV_CONVERT_HEADER__

#include "vfmw.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    /*   yuv virAddr  */
    UINT8 *pYAddr_8bit;
    UINT8 *pYAddr_nbit;
    UINT8 *pCAddr_8bit;
    UINT8 *pCAddr_nbit;

}YUV_ADDR_S;

typedef struct
{
    /*   tile virAddr  */
    UINT8 *Yaddress_8bit;
    UINT8 *Yaddress_nbit;
    UINT8 *Caddress_8bit;
    UINT8 *Caddress_nbit;

    /*   bit depth    */
    SINT32 RealBitDepth;
    SINT32 SaveBitDepth;

    UINT32 Is1D;

    UINT32 Stride;
    UINT32 Stride_nbit;

}YUV_PARAM_S;

/*----------------------------EXTERNAL FUNCTION-------------------------------*/
VOID IMAGE_ConvertTo2D(YUV_PARAM_S *pYuvParam, UINT32 Width, UINT32 Height, YUV_ADDR_S *pYuvAddr);


#ifdef __cplusplus
}
#endif

#endif







