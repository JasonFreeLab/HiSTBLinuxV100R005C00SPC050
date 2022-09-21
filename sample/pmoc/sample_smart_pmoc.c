#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#include <assert.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>

#include "hi_adp.h"
#include "hi_unf_pmoc.h"

#ifdef CONFIG_SUPPORT_CA_RELEASE
#define HI_INFO_PMOC(format, arg ...)
#else
#define HI_INFO_PMOC(format, arg ...) printf( format, ## arg)
#endif

HI_S32  main(HI_S32 argc,HI_CHAR *argv[])
{
    HI_U32 u32StandbyModule;
    HI_CHAR InputCmd[128];
    HI_S32 ret;
    
    if ((argc <= 1) || (argc > 2))
    {
        printf("Usage: %s [StandbyModule] \n"
               "       StandbyModule(Each bit represent a module): \n"
               "       bitval 0: this module enters standby mode;  \n"
               "       bitval 1: this module doesn't enter standby mode.\n"
               "       Please see HI_UNF_PMOC_HOLD_MOD_E in the hi_unf_pmoc.h\n",
                argv[0]);
        printf("Example: %s 0\n", argv[0]);
        return HI_FAILURE;
    } 

    u32StandbyModule = strtol(argv[1],NULL,0);
    
    ret = HI_UNF_PMOC_Init();
    if (HI_SUCCESS != ret)
    {
        HI_INFO_PMOC("HI_UNF_PMOC_Init err, 0x%08x !\n", ret);
        return ret;
    }

    ret  = HI_UNF_PMOC_EnterSmartStandby(u32StandbyModule);
    if (HI_SUCCESS != ret)
    {
        HI_INFO_PMOC("HI_UNF_PMOC_EnterSmartStandby err, 0x%08x !\n", ret);
        HI_UNF_PMOC_DeInit();
        return ret;
    }
    
    while (1)
    {
        printf("please input 'q' to quit smart standby!\n");
        memset(InputCmd, 0, sizeof(InputCmd));
        SAMPLE_GET_INPUTCMD(InputCmd);
        if ('q' == InputCmd[0])
        {
            printf("prepare to quit!\n");
            break;
        }
    }

    ret  = HI_UNF_PMOC_QuitSmartStandby();
    if (HI_SUCCESS != ret)
    {
        HI_INFO_PMOC("HI_UNF_PMOC_QuitSmartStandby err, 0x%08x !\n", ret);
        HI_UNF_PMOC_DeInit();
        return ret;
    }

    HI_UNF_PMOC_DeInit();

    return HI_SUCCESS;
}
