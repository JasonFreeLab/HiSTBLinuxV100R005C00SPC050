#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>

#include <assert.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

#include "hi_unf_common.h"
#include "hi_unf_avplay.h"
#include "hi_unf_sound.h"

#include "hi_adp_mpi.h"
#include "hi_adp_hdmi.h"

#include "hi_drv_ao.h"
#include "drv_ao_ioctl.h"

static inline const HI_CHAR* AOPort2Name(HI_UNF_SND_OUTPUTPORT_E enPort)
{
    switch (enPort)
    {
        case HI_UNF_SND_OUTPUTPORT_DAC0:
            return "DAC0";
        case HI_UNF_SND_OUTPUTPORT_I2S0:
            return "I2S0";
        case HI_UNF_SND_OUTPUTPORT_I2S1:
            return "I2S1";
        case HI_UNF_SND_OUTPUTPORT_SPDIF0:
            return "SPDIF0";
        case HI_UNF_SND_OUTPUTPORT_HDMI0:
            return "HDMI0";
        case HI_UNF_SND_OUTPUTPORT_ARC0:
            return "ARC0";
        case HI_UNF_SND_OUTPUTPORT_EXT_DAC1:
            return "DAC1";
        case HI_UNF_SND_OUTPUTPORT_EXT_DAC2:
            return "DAC2";
        case HI_UNF_SND_OUTPUTPORT_EXT_DAC3:
            return "DAC3";
        default:
            return "UnknownPort";
    }
}

HI_S32 main(HI_S32 argc, HI_CHAR* argv[])
{
    HI_U32 i;
    HI_S32 ret;
    HI_U32 u32OldBandNum;
    HI_S32 SndDevFd;
    HI_CHAR InputCmd[32];
    HI_S32 s32Gain = 0, sign = 0;
    HI_U32 u32FltType = 0;
    HI_U32 u32Freq = 0, u32Qvalue = 0;
    HI_U32 u32BandOrder = 0, k = 0;
    HI_U32 u32OutPort = 0;

    /* PEQ */
    HI_UNF_SND_PEQ_ATTR_S stPeqAttr;
    AO_SND_Eq_Enable_S stPeqEnable;
    AO_SND_Peq_Param_S stPeqParam;
    stPeqParam.enSound   = HI_UNF_SND_0;
    stPeqParam.enOutPort = HI_UNF_SND_OUTPUTPORT_I2S1;
    stPeqEnable.enSound  = HI_UNF_SND_0;
    stPeqEnable.enOutPort  = HI_UNF_SND_OUTPUTPORT_I2S1;

    SndDevFd = open("/dev/hi_ao", O_RDWR);
    if (SndDevFd < 0)
    {
        printf("Open Ao Device err\n");
        return -1;
    }

    while(1)
    {
        printf("==========================================\n");
        printf("port info:\n");
        printf("HI_UNF_SND_OUTPUTPORT_DAC0 = 0\n");
        printf("HI_UNF_SND_OUTPUTPORT_I2S0 = 1\n");
        printf("HI_UNF_SND_OUTPUTPORT_I2S1 = 2\n");
        printf("HI_UNF_SND_OUTPUTPORT_SPDIF0 = 3\n");
        printf("HI_UNF_SND_OUTPUTPORT_HDMI0= 4\n");
        printf("HI_UNF_SND_OUTPUTPORT_ARC0 = 5\n");
        printf("HI_UNF_SND_OUTPUTPORT_EXT_DAC1 = 80\n");
        printf("HI_UNF_SND_OUTPUTPORT_EXT_DAC2= 81\n");
        printf("HI_UNF_SND_OUTPUTPORT_EXT_DAC3 = 82\n");
        printf("HI_UNF_SND_OUTPUTPORT_ALL = 32767\n");
        printf("==========================================\n");
        printf("please input q                to quit!\n");
        printf("please input p[OutPort]       to print Peq attr!\n");
        printf("please input e[OutPort]       to enable Peq, input d[OutPort] to disnable Peq!\n");
        printf("please input b[OutPort]n[num] to set total num of banks -> [1, 10]\n");
        printf("please input o[OutPort]n[num]t[fltype]f[freq]q[Qvalue]g[gain]\n\
             num:(band order,0~9),\n\
             fltype:(HP:0, LS:1, PK:2, HS:3, LP:4), \n\
             freq:(HP and LS[20, 4000], PK[20, 22000], HS[4000, 22000], LP[50, 22000]), \n\
             Qvalue:(HS and LS[7, 10], PK[5, 100], HP and LP is fix to be 7), \n\
             gain:(-15000,15000,step by 125)\n\n");

        memset(InputCmd, 0, 32);
        SAMPLE_GET_INPUTCMD(InputCmd);
        u32OutPort = 0;

        switch(InputCmd[0])
        {
            case 'q':
                close(SndDevFd);
                return -1;
                break;

            case 'p':
                k = 1;
                while(!(InputCmd[k] < '0') && !(InputCmd[k] > '9'))
                {
                    u32OutPort = u32OutPort * 10 + (InputCmd[k] - '0');
                    k++;
                }

                stPeqEnable.enOutPort = (HI_UNF_SND_OUTPUTPORT_E)u32OutPort;
                ret = ioctl(SndDevFd, CMD_AO_SND_GETPEQENABLE, &stPeqEnable);
                if (ret)
                {
                    printf("Get Peq enable fail\n");
                    close(SndDevFd);
                    return -1;
                }

                printf("==================================================\n");
                printf("OutPort:%s\n", AOPort2Name((HI_UNF_SND_OUTPUTPORT_E)u32OutPort));
                printf("Peq_enable:%s\n",(stPeqEnable.bEqEnable == HI_TRUE)?"HI_TRUE":"HI_FALSE");

                stPeqParam.enOutPort = (HI_UNF_SND_OUTPUTPORT_E)u32OutPort;
                ret = ioctl(SndDevFd, CMD_AO_SND_GETPEQATTR, &stPeqParam);
                if (ret)
                {
                    printf("get Peq attr fail\n");
                    close(SndDevFd);
                    return -1;
                }

                memcpy(&stPeqAttr, &(stPeqParam.stEqAttr), sizeof(HI_UNF_SND_PEQ_ATTR_S));
                printf("u32BandNum:%d\n", stPeqAttr.u32BandNum);

                for(i=0; i<stPeqAttr.u32BandNum; i++)
                {
                    printf("band:%d   FltType:%d   freq:%d   Q:%d   gain:%d\n", i, stPeqAttr.stEqParam[i].enFltType,\
                           stPeqAttr.stEqParam[i].u32freq, stPeqAttr.stEqParam[i].u32Q, stPeqAttr.stEqParam[i].s32Gain);
                }
                printf("==================================================\n");

                break;

            case 'e':
                k = 1;
                while(!(InputCmd[k] < '0') && !(InputCmd[k] > '9'))
                {
                    u32OutPort = u32OutPort * 10 + (InputCmd[k] - '0');
                    k++;
                }
                stPeqEnable.enOutPort = (HI_UNF_SND_OUTPUTPORT_E)u32OutPort;
                stPeqEnable.enSound = HI_UNF_SND_0;
                stPeqEnable.bEqEnable = HI_TRUE;
                ret = ioctl(SndDevFd, CMD_AO_SND_SETPEQENABLE, &stPeqEnable);
                if (ret)
                {
                    printf("Set Peq enable fail\n");
                    close(SndDevFd);
                    return -1;
                }
                break;

            case 'd':
                k = 1;
                while(!(InputCmd[k] < '0') && !(InputCmd[k] > '9'))
                {
                    u32OutPort = u32OutPort * 10 + (InputCmd[k] - '0');
                    k++;
                }
                stPeqEnable.enOutPort = (HI_UNF_SND_OUTPUTPORT_E)u32OutPort;
                stPeqEnable.enSound = HI_UNF_SND_0;
                stPeqEnable.bEqEnable = HI_FALSE;
                ret = ioctl(SndDevFd, CMD_AO_SND_SETPEQENABLE, &stPeqEnable);
                if (ret)
                {
                    printf("Set Peq enable fail\n");
                    close(SndDevFd);
                    return -1;
                }
                break;

            case 'o':
                u32Freq   = 0;
                s32Gain   = 0;
                u32Qvalue = 0;
                k = 1;
                while(!(InputCmd[k] < '0') && !(InputCmd[k] > '9'))
                {
                    u32OutPort = u32OutPort * 10 + (InputCmd[k] - '0');
                    k++;
                }
                k++;
                stPeqParam.enOutPort = (HI_UNF_SND_OUTPUTPORT_E)u32OutPort;
                u32BandOrder = InputCmd[k++] - '0';
                printf("u32OutPort %d,u32BandOrder %d\n",u32OutPort,u32BandOrder);

                if('t' == InputCmd[k++])
                {
                    u32FltType   = InputCmd[k++] - '0';
                }
                else
                {
                    printf("**********************wrong parameter formate!**********************\n");
                    printf("*******************please input as example showed!******************\n");
                    printf("********************************************************************\n\n");
                    break;
                }

                printf("Your Setting values is:\n");
                printf("....>>>>>>>>>>>>>>>>>>>>> \n");
                printf("....u32BandOrder = %d\n....u32FltType = %d\n", u32BandOrder, u32FltType);

                if('f' == InputCmd[k++])
                {
                    while(!(InputCmd[k] < '0') && !(InputCmd[k] > '9'))
                    {
                        u32Freq = u32Freq * 10 + (InputCmd[k++] - '0');
                    }
                }
                else
                {
                    printf("********************************************************************\n");
                    printf("**********************wrong parameter formate!**********************\n");
                    printf("*******************please input as example showed!******************\n");
                    printf("********************************************************************\n\n");
                    break;
                }

                printf("....u32Freq = %d\n", u32Freq);

                if('q' == InputCmd[k++])
                {
                    while(!(InputCmd[k] < '0') && !(InputCmd[k] > '9'))
                    {
                        u32Qvalue= u32Qvalue * 10 + (InputCmd[k++] - '0');
                    }
                }
                else
                {
                    printf("********************************************************************\n");
                    printf("**********************wrong parameter formate!**********************\n");
                    printf("*******************please input as example showed!******************\n");
                    printf("********************************************************************\n\n");
                    break;
                }

                printf("....u32Qvalue = %d\n", u32Qvalue);

                if('g' == InputCmd[k])
                {
                    k++;
                    sign = 1;
                    if ('-' == InputCmd[k])
                    {
                        k++;
                        sign = -1;
                    }

                    while(!(InputCmd[k] < '0') && !(InputCmd[k] > '9'))
                    {
                        s32Gain = s32Gain * 10 + (InputCmd[k] - '0');
                        k++;
                    }

                    s32Gain *= sign;
                }
                else
                {
                    printf("********************************************************************\n");
                    printf("**********************wrong parameter formate!**********************\n");
                    printf("*******************please input as example showed!******************\n");
                    printf("********************************************************************\n\n");
                    break;
                }

                printf("....s32Gain = %d \n", s32Gain);
                printf("....>>>>>>>>>>>>>>>>>>>>> \n");

                ret = ioctl(SndDevFd, CMD_AO_SND_GETPEQATTR, &stPeqParam);
                if (ret)
                {
                    printf("Get Peq attr fail\n");
                    close(SndDevFd);
                    return -1;
                }

                 stPeqParam.stEqAttr.stEqParam[u32BandOrder].enFltType = u32FltType;
                 stPeqParam.stEqAttr.stEqParam[u32BandOrder].u32freq = u32Freq;
                 stPeqParam.stEqAttr.stEqParam[u32BandOrder].u32Q = u32Qvalue;
                 stPeqParam.stEqAttr.stEqParam[u32BandOrder].s32Gain = s32Gain;

                ret = ioctl(SndDevFd, CMD_AO_SND_SETPEQATTR, &stPeqParam);
                if (ret)
                {
                    printf("Set PEQATTR fail! ret = %d\n", ret);
                    close(SndDevFd);
                    return -1;
                }

                break;

            case 'b':
                k = 1;
                while(!(InputCmd[k] < '0') && !(InputCmd[k] > '9'))
                {
                    u32OutPort = u32OutPort * 10 + (InputCmd[k] - '0');
                    k++;
                }
                stPeqParam.enOutPort = (HI_UNF_SND_OUTPUTPORT_E)u32OutPort;

                if('n' == InputCmd[k])
                {
                    k++;
                ret = ioctl(SndDevFd, CMD_AO_SND_GETPEQATTR, &stPeqParam);
                if (ret)
                {
                    printf("Set u32BandNum fail\n");
                    close(SndDevFd);
                    return -1;
                }

                u32OldBandNum = stPeqParam.stEqAttr.u32BandNum;

                stPeqParam.stEqAttr.u32BandNum = 0;

                while(!(InputCmd[k] < '0') && !(InputCmd[k] > '9'))
                {
                    stPeqParam.stEqAttr.u32BandNum = stPeqParam.stEqAttr.u32BandNum * 10 + (InputCmd[k] - '0');
                    k++;
                }

                if((stPeqParam.stEqAttr.u32BandNum <= 0) || (stPeqParam.stEqAttr.u32BandNum > 10))
                {
                    printf("******* BandNumbers = %d, BandNumbers should between [1, 10]\n", stPeqParam.stEqAttr.u32BandNum);
                    return -1;
                }

                for(i = u32OldBandNum; i < stPeqParam.stEqAttr.u32BandNum; i++)
                {
                    stPeqParam.stEqAttr.stEqParam[i].enFltType = 2;
                    stPeqParam.stEqAttr.stEqParam[i].u32freq = 5000;
                    stPeqParam.stEqAttr.stEqParam[i].u32Q = 20;
                    stPeqParam.stEqAttr.stEqParam[i].s32Gain = 5000;
                }

                ret = ioctl(SndDevFd, CMD_AO_SND_SETPEQATTR, &stPeqParam);
                if (ret)
                {
                    printf("Set u32BandNum fail\n");
                    close(SndDevFd);
                    return -1;
                }
                break;
                }
                else
                {
                    printf("********************************************************************\n");
                    printf("**********************wrong parameter formate!**********************\n");
                    printf("*******************please input as example showed!******************\n");
                    printf("********************************************************************\n\n");
                    break;
                }
            default:
                printf("Unknown Operation\n");
                break;
        }
    }

    return 0;
}

