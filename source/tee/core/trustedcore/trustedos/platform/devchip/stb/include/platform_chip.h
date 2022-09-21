#ifndef PLATFORM_CHIP_H
#define PLATFORM_CHIP_H

#if defined(CFG_HI_TEE_HI3798CV2X_SUPPORT)
#include "../chip/hi3798cv2x/sys.h"
#include "../chip/hi3798cv2x/serial.h"
#include "../chip/hi3798cv2x/timer.h"
#endif

#if defined(CFG_HI_TEE_HI3798MX_SUPPORT)
#include "../chip/hi3798mx/sys.h"
#include "../chip/hi3798mx/serial.h"
#include "../chip/hi3798mx/timer.h"
#endif

#endif /* PLATFORM_CHIP_H */