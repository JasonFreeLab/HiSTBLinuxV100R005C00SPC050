#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <vector>
#include "hi_type.h"

#define IN
#define OUT
#define INOUT

#define WV_DEBUG_TAG "[WV debug]"
#define WVLOGD(fmt, args...) printf("%s %s %d: " fmt "", WV_DEBUG_TAG, __FUNCTION__, __LINE__, ## args)
#define WVLOGD(fmt, args...)

#define WV_INFO_TAG "[WV info]"
#define WVLOGI(fmt, args...) printf("%s %s %d: " fmt "", WV_INFO_TAG, __FUNCTION__, __LINE__, ## args)

#define WV_ERR_TAG "[WV error]"
#define WVLOGE(fmt, args...) printf("%s %s %d: " fmt "", WV_ERR_TAG, __FUNCTION__, __LINE__, ## args)

#define WV_PROMPT printf

#define CHK_ARG(expr) do {                                     \
        if (!(expr))                                           \
        {                                                      \
            WVLOGE("Invalid argument!\n");                     \
            return HI_FAILURE;                                 \
        }                                                      \
    }while(HI_FALSE)