#ifndef __TEST_CRC_CALC_H__
#define __TEST_CRC_CALC_H__

#include "vfmw.h"

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------EXTERNAL FUNCTION-------------------------------*/
SINT32 CRC_InitCalcEnvironment(VOID);
SINT32 CRC_ExitCalcEnvironment(VOID);
SINT32 CRC_CalcImageCrc(IMAGE *pImage);


#ifdef __cplusplus
}
#endif

#endif





