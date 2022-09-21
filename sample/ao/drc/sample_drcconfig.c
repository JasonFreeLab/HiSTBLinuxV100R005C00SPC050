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
#include "hi_unf_sound.h"
#include "hi_unf_disp.h"

#include "hi_adp_mpi.h"
#include "hi_adp_hdmi.h"

#include "hi_drv_ao.h"
#include "drv_ao_ioctl.h"

HI_UNF_SND_DRC_ATTR_S g_stDrcAttr;

HI_S32 main(HI_S32 argc, HI_CHAR* argv[])
{
    HI_S32 ret;
    HI_CHAR InputCmd[32];
    HI_UNF_SND_DRC_ATTR_S stDrcAttr;
    HI_S32 port;
    HI_UNF_SND_DRC_ATTR_S* pstDrcAttr;

    HI_S32 SndDevFd;
    AO_SND_Drc_Param_S stDrcParam, g_stDrcParam;
    stDrcParam.enSound = HI_UNF_SND_0;
    stDrcParam.enOutPort = HI_UNF_SND_OUTPUTPORT_ALL;
    g_stDrcParam.enSound = HI_UNF_SND_0;
    g_stDrcParam.enOutPort = HI_UNF_SND_OUTPUTPORT_DAC0;

    AO_SND_Drc_Enable_S stDrcEnable, g_stDrcEnable;
    stDrcEnable.enSound = HI_UNF_SND_0;
    stDrcEnable.enOutPort = HI_UNF_SND_OUTPUTPORT_ALL;
    g_stDrcEnable.enSound = HI_UNF_SND_0;
    g_stDrcEnable.enOutPort = HI_UNF_SND_OUTPUTPORT_DAC0;

    SndDevFd = open("/dev/hi_ao", O_RDWR);
    if (SndDevFd < 0)
    {
        printf("Open Ao Device err\n");
        return -1;
    }

    ret = ioctl(SndDevFd, CMD_AO_SND_GETDRCENABLE, &g_stDrcEnable);
    if (ret)
    {
        g_stDrcEnable.enOutPort = HI_UNF_SND_OUTPUTPORT_DAC0;
        g_stDrcParam.enOutPort = HI_UNF_SND_OUTPUTPORT_DAC0;
        ret = ioctl(SndDevFd, CMD_AO_SND_GETDRCENABLE, &g_stDrcEnable);
        if (!ret)
        {
            printf("get drc enable fail\n");
            close(SndDevFd);
            return -1;
        }
    }
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
    printf("==========================================\n");
    printf("drc_enable:%s\n", (g_stDrcEnable.bDrcEnable == HI_TRUE) ? "HI_TRUE" : "HI_FALSE");



    printf("g_stDrcParam.enOutPort:%d \n", g_stDrcParam.enOutPort);
    ret = ioctl(SndDevFd, CMD_AO_SND_GETDRCATTR, &g_stDrcParam);
    if (ret)
    {
        printf("get drc attr fail\n");
        close(SndDevFd);
        return -1;
    }
    memcpy(&stDrcAttr, &(g_stDrcParam.stDrcAttr), sizeof(HI_UNF_SND_DRC_ATTR_S));
    printf("attacktime:%d   releasetime:%d\n", stDrcAttr.u32AttackTime, stDrcAttr.u32ReleaseTime);
    printf("Thrhd:%d.%ddB   Limit:%d.%ddB\n", stDrcAttr.s32Thrhd / 1000, \
           -stDrcAttr.s32Thrhd % 1000, stDrcAttr.s32Limit / 1000, - stDrcAttr.s32Limit % 1000);
    printf("RefMode:%d    SpeedCtrlMode:%d\n", stDrcAttr.u32RefMode, stDrcAttr.u32SpeedCtrlMode);
    printf("==========================================\n");

    while (1)
    {
        printf("please input the q to quit!\n");

        printf("please input the p[port] to print port drc attr!\n");

        printf("please input the e[port] to enable port drc, input the d[port] to disnable port drc!\n");

        printf("please input o[OutPort]a[AT]r[RT]t[TH]l[LM]R[RF]S[SP]\n");
        printf("\t\tAT(attacktime,[20,2000])\n");
        printf("\t\tRT(releasetime,[20,2000])\n");
        printf("\t\tTH(threshold,[-80.000,-1.000))\n");
        printf("\t\tLM(limit,(-80.000,-1.000])\n");
        printf("\t\tRF(refmode,[0 or 1])\n");
        printf("\t\tSP(speedctrlmode,[0 or 1])\n");
        SAMPLE_GET_INPUTCMD(InputCmd);

        if ('q' == InputCmd[0])
        {
            close(SndDevFd);
            printf("prepare to quit!\n");
            break;
        }

        if ('p' == InputCmd[0])
        {
            int k = 0;

            k = 1;
            port = 0;
            while (!(InputCmd[k] < '0') && !(InputCmd[k] > '9'))
            {
                port = port * 10 + (InputCmd[k] - '0');
                k++;
            }
            g_stDrcEnable.enOutPort = port;
            g_stDrcParam.enOutPort = port;
            ret = ioctl(SndDevFd, CMD_AO_SND_GETDRCENABLE, &g_stDrcEnable);
            if (ret)
            {
                printf("get drc enable fail\n");
                close(SndDevFd);
                return -1;
            }
            printf("==========================================\n");
            printf("drc_enable:%s\n", (g_stDrcEnable.bDrcEnable == HI_TRUE) ? "HI_TRUE" : "HI_FALSE");

            printf("g_stDrcParam.enOutPort:%d \n", g_stDrcParam.enOutPort);
            ret = ioctl(SndDevFd, CMD_AO_SND_GETDRCATTR, &g_stDrcParam);
            if (ret)
            {
                printf("get drc attr fail\n");
                close(SndDevFd);
                return -1;
            }
            memcpy(&stDrcAttr, &(g_stDrcParam.stDrcAttr), sizeof(HI_UNF_SND_DRC_ATTR_S));
            //printf("drc_enable:%s\n",(stDrcAttr.bEnable == HI_TRUE)?"HI_TRUE":"HI_FALSE");
            printf("attacktime:%d   releasetime:%d\n", stDrcAttr.u32AttackTime, stDrcAttr.u32ReleaseTime);
            printf("Thrhd:%ddB   Limit:%ddB\n", stDrcAttr.s32Thrhd, stDrcAttr.s32Limit);
            printf("RefMode:%d    SpeedCtrlMode:%d\n", stDrcAttr.u32RefMode, stDrcAttr.u32SpeedCtrlMode);
            printf("==========================================\n");
        }

        if ('e' == InputCmd[0])
        {
            int k = 0;

            k = 1;
            port = 0;
            while (!(InputCmd[k] < '0') && !(InputCmd[k] > '9'))
            {
                port = port * 10 + (InputCmd[k] - '0');
                k++;
            }
            stDrcEnable.enOutPort = port;

            stDrcEnable.enSound = HI_UNF_SND_0;
            //stDrcEnable.enOutPort = HI_UNF_SND_OUTPUTPORT_ALL;
            stDrcEnable.bDrcEnable = HI_TRUE;
            ret = ioctl(SndDevFd, CMD_AO_SND_SETDRCENABLE, &stDrcEnable);

            //memcpy(&(stDrcParam.stDrcAttr),&stDrcAttr, sizeof(HI_UNF_SND_DRC_ATTR_S));
            //stDrcParam.stDrcAttr.bEnable = HI_TRUE;
            //ret = ioctl(SndDevFd, CMD_AO_SND_SETDRCATTR, &stDrcParam);
            if (ret)
            {
                printf("Set drc enbale fail\n");
                close(SndDevFd);
                return -1;
            }
        }

        else if ('d' == InputCmd[0])
        {
            int k = 0;

            k = 1;
            port = 0;
            while (!(InputCmd[k] < '0') && !(InputCmd[k] > '9'))
            {
                port = port * 10 + (InputCmd[k] - '0');
                k++;
            }
            stDrcEnable.enOutPort = port;

            stDrcEnable.enSound = HI_UNF_SND_0;
            //stDrcEnable.enOutPort = HI_UNF_SND_OUTPUTPORT_ALL;
            stDrcEnable.bDrcEnable = HI_FALSE;
            ret = ioctl(SndDevFd, CMD_AO_SND_SETDRCENABLE, &stDrcEnable);

            //memcpy(&(stDrcParam.stDrcAttr),&stDrcAttr, sizeof(HI_UNF_SND_DRC_ATTR_S));
            //stDrcParam.stDrcAttr.bEnable = HI_FALSE;
            //ret = ioctl(SndDevFd, CMD_AO_SND_SETDRCATTR, &stDrcParam);
            if (ret)
            {
                printf("Set drc disable fail\n");
                close(SndDevFd);
                return -1;
            }
        }

        else if ('o' == InputCmd[0])
        {
            //HI_S32 sign = 0;
            HI_U32 k = 0;
            HI_U32  u32Outport = 0;
            HI_U32  u32AttackTime = 0;
            HI_U32  u32ReleaseTime = 0;
            HI_S32  s32Thrhd = 0;
            HI_S32  s32Limit = 0;
            HI_U32  u32RefMode = 0;
            HI_U32  u32SpeedCtrlMode = 0;

            k = 1;
            while (!(InputCmd[k] < '0') && !(InputCmd[k] > '9'))
            {

                u32Outport = u32Outport * 10 + (InputCmd[k] - '0');
                k++;
            }
            printf("Outport=%d\n", u32Outport);

            if ('a' == InputCmd[k])
            {
                k++;
                while (!(InputCmd[k] < '0') && !(InputCmd[k] > '9'))
                {
                    u32AttackTime = u32AttackTime * 10 + (InputCmd[k] - '0');
                    k++;
                }
            }
            printf("Set u32AttackTime=%d\n", u32AttackTime);

            if ('r' == InputCmd[k])
            {
                k++;
                while (!(InputCmd[k] < '0') && !(InputCmd[k] > '9'))
                {
                    u32ReleaseTime = u32ReleaseTime * 10 + (InputCmd[k] - '0');
                    k++;
                }
            }
            printf("Set u32ReleaseTime=%d\n", u32ReleaseTime);

            if ('t' == InputCmd[k])
            {
                k++;
                if (InputCmd[k] != '-')
                {
                    printf("Set drc attr fail\n");
                    close(SndDevFd);
                }
                k++;
                while (!(InputCmd[k] < '0') && !(InputCmd[k] > '9'))
                {
                    s32Thrhd = s32Thrhd * 10 + (InputCmd[k] - '0');
                    k++;
                }
                if (InputCmd[k] == '.')
                {
                    k++;
                    while (!(InputCmd[k] < '0') && !(InputCmd[k] > '9'))
                    {
                        s32Thrhd = s32Thrhd * 10 + (InputCmd[k] - '0');
                        k++;
                    }
                }
                else
                {
                    s32Thrhd = s32Thrhd;
                }
            }
            printf("Set new s32Thrhd=%d\n", -s32Thrhd);

            if ('l' == InputCmd[k])
            {
                k++;
                if (InputCmd[k] != '-')
                {
                    printf("Set drc attr fail\n");
                    close(SndDevFd);
                }
                k++;
                while (!(InputCmd[k] < '0') && !(InputCmd[k] > '9'))
                {
                    s32Limit = s32Limit * 10 + (InputCmd[k] - '0');
                    k++;
                }
                if (InputCmd[k] == '.')
                {
                    k++;
                    while (!(InputCmd[k] < '0') && !(InputCmd[k] > '9'))
                    {
                        s32Limit = s32Limit * 10 + (InputCmd[k] - '0');
                        k++;
                    }
                }
                else
                {
                    s32Limit = s32Limit;
                }
            }

            printf("Set new s32Limit=%d\n", -s32Limit);
            if ('R' == InputCmd[k])
            {
                k++;
                if (!(InputCmd[k] < '0') && !(InputCmd[k] > '9'))
                {
                    u32RefMode = (InputCmd[k++] - '0');
                }

                if (u32RefMode > 1)
                {
                    printf("Invalid Parameter!!RefMode is 0 or 1!\n");
                    continue;
                }
            }

            printf("Set refmode = %d\n", u32RefMode);
            if ('S' == InputCmd[k])
            {
                k++;
                if (!(InputCmd[k] < '0') && !(InputCmd[k] > '9'))
                {
                    u32SpeedCtrlMode = (InputCmd[k++] - '0');
                }

                if (u32RefMode > 1)
                {
                    printf("Invalid Parameter!!SpeedCtrlMode is 0 or 1!\n");
                    continue;
                }
            }

            printf("Set SpeedCtrlMode = %d\n", u32SpeedCtrlMode);
            memcpy(&(stDrcParam.stDrcAttr), &stDrcAttr, sizeof(HI_UNF_SND_DRC_ATTR_S));
            stDrcParam.enOutPort = (HI_UNF_SND_OUTPUTPORT_E)u32Outport;
            stDrcParam.stDrcAttr.u32AttackTime = u32AttackTime;
            stDrcParam.stDrcAttr.u32ReleaseTime = u32ReleaseTime;
            stDrcParam.stDrcAttr.s32Thrhd = -s32Thrhd;
            stDrcParam.stDrcAttr.s32Limit = -s32Limit;
            stDrcParam.stDrcAttr.u32RefMode = u32RefMode;
            stDrcParam.stDrcAttr.u32SpeedCtrlMode = u32SpeedCtrlMode;
            pstDrcAttr = &(stDrcParam.stDrcAttr);
            CHECK_AO_DRCATTR(pstDrcAttr);
            ret = ioctl(SndDevFd, CMD_AO_SND_SETDRCATTR, &stDrcParam);

            if (ret)
            {
                printf("Set drc attr fail\n");
                close(SndDevFd);
                return -1;
            }
            printf("set drc attr success!\n");
        }
    }

    return 0;
}

