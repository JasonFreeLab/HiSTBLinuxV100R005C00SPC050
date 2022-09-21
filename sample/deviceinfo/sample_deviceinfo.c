#include <stdlib.h>
#include <string.h>
#include "hi_osal.h"
#include "hi_flash.h"
#include "hi_unf_common.h"
#include "hi_unf_pdm.h"

#define PDM_DEVICE_INFO_DEF_NAME         "deviceinfo"
#define PDM_DEVICE_INFO_SIZE             (1 * 1024 * 1024)
#define PDM_DEVICE_INFO_MAX_SIZE         (4 * 1024 * 1024)

#define PDM_DEVICE_INFO_ALL              0xf //表示所有条目

typedef enum
{
    PDM_DEVICE_INFO_MAC = 0x0,
    PDM_DEVICE_INFO_SN,
    PDM_DEVICE_INFO_MAGICNUM,
    PDM_DEVICE_INFO_LENGTH,
    PDM_DEVICE_INFO_OUI,
    PDM_DEVICE_INFO_HW,
    PDM_DEVICE_INFO_BUT
}PDM_DEVICE_INFO_E;

/*Flash pation info for mce use*/
typedef struct hiPDM_FLASH_INFO_S
{
    HI_CHAR             Name[256];
    HI_U32              u32Offset;
    HI_U32              u32Size;
    HI_BOOL             bShared;  /*whether share one partition with other data*/
}PDM_FLASH_INFO_S;


HI_CHAR *g_DeviceInfo[] = {\
                            "MAC",\
                            "SN",\
                            "MAGICNUM",\
                            "LENGTH",\
                            "OUI",\
                            "HW"};

 HI_U32 str2flashsize(HI_CHAR *strsize)
{
    char *p, *q;
    char tmp[32];
    int size;

    p = strsize;
    q = strsize + strlen(strsize) - 1;

    if (strlen(strsize) <= 1)
    {
        return 0;
    }

    if (sizeof(tmp) < strlen(strsize))
    {
        return 0;
    }

    memset(tmp, 0x0, sizeof(tmp));

    memcpy(tmp, p, strlen(strsize) - 1);

    size = strtoul(tmp, HI_NULL, 10);

    if ((*q == 'K') || (*q == 'k'))
    {
        size = size * 1024;
    }
    else if ((*q == 'M') || (*q == 'm'))
    {
        size = size * 1024 * 1024;
    }
    else
    {
        size = 0;
    }

    return size;
}

HI_S32 GetFlashInfo(HI_CHAR *DataName, PDM_FLASH_INFO_S *pstInfo)
{
    HI_CHAR Bootargs[512];
    FILE    *pf = HI_NULL;
    HI_CHAR *p, *q;
    HI_CHAR tmp[32];
    HI_S32  ReadLen = 0;

    pf = fopen("/proc/cmdline", "r");
    if (HI_NULL == pf)
    {
        return HI_FAILURE;
    }

    memset(Bootargs, 0x0, 512);

    ReadLen = fread(Bootargs, sizeof(HI_CHAR), 512, pf);
    if (ReadLen <= 0)
    {
        fclose(pf);
        return HI_FAILURE;
    }

    fclose(pf);

    Bootargs[511] = '\0';

    HI_OSAL_Snprintf(tmp, sizeof(tmp), "(%s)", DataName);

    p = strstr(Bootargs, tmp);

    if (0 != p)
    {
        for (q = p; q > Bootargs; q--)
        {
            if ((*q == ',') || (*q == ':'))
            {
                break;
            }
        }

        memset(tmp, 0, sizeof(tmp));

        if ((HI_U32)(p - q - 1) >= sizeof(tmp))
        {
            return HI_FAILURE;
        }

        memcpy(tmp, q + 1, p - q - 1);
        tmp[sizeof(tmp) - 1] = '\0';

        memset(pstInfo->Name, 0x0, sizeof(pstInfo->Name));

        memcpy(pstInfo->Name, DataName, strlen(DataName));
        pstInfo->u32Size   = str2flashsize(tmp);
        pstInfo->u32Offset = 0;
        pstInfo->bShared = HI_FALSE;

        return HI_SUCCESS;
    }

    HI_OSAL_Snprintf(tmp, sizeof(tmp), " %s", DataName);

    p = strstr(Bootargs, tmp);
    if (0 == p)
    {
        return HI_FAILURE;
    }

    p = strstr(p, "=");
    if (0 == p)
    {
        return HI_FAILURE;
    }

    p++;

    q = strstr(p, ",");
    if (0 == q)
    {
        return HI_FAILURE;
    }

    memset(pstInfo->Name, 0x0, sizeof(pstInfo->Name));
    memcpy(pstInfo->Name, p, q - p);

    p = q + 1;
    q = strstr(p, ",");
    if (0 == q)
    {
        return HI_FAILURE;
    }

    memset(tmp, 0, sizeof(tmp));
    memcpy(tmp, p, q - p);

    pstInfo->u32Offset = strtoul(tmp, HI_NULL, 16);

    p = q + 1;

    q = strstr(p, " ");
    if (0 == q)
    {
        q = Bootargs + strlen(Bootargs);
    }

    memset(tmp, 0, sizeof(tmp));
    memcpy(tmp, p, q - p);

    pstInfo->u32Size = strtoul(tmp, HI_NULL, 16);
    pstInfo->bShared = HI_TRUE;

    return HI_SUCCESS;
}


HI_S32 Update_DeviceInfo(HI_CHAR * pstrCfgName, HI_CHAR * pstrCfgValue)
{
    HI_HANDLE hFlash = HI_INVALID_HANDLE;
    HI_CHAR  *pDevInfoBuf = HI_NULL;
    PDM_FLASH_INFO_S stPartInfo;
    HI_S32   s32Ret = HI_FAILURE;
    HI_S32   i = 0 ;
    HI_S32   Size;
    HI_CHAR  TmpCfgValue[256] = {0};
    HI_CHAR  InputCfgValue[256] = {0};
    HI_CHAR* pcWritePosition = HI_NULL;
    HI_CHAR* pcLengthTagPos  = HI_NULL;
    HI_Flash_InterInfo_S FlashInfo;
    HI_U32 StartPos, EndPos, UpdateSize;

    if(HI_NULL == pstrCfgName || HI_NULL == pstrCfgValue)
    {
        s32Ret = HI_FAILURE;
        goto out0;
    }

    s32Ret = GetFlashInfo(PDM_DEVICE_INFO_DEF_NAME, &stPartInfo);
    if (HI_SUCCESS != s32Ret)
    {
        printf("ERR: no found '%s' partition.\n", PDM_DEVICE_INFO_DEF_NAME);
        s32Ret = HI_FAILURE;
        goto out0;
    }

    hFlash = HI_Flash_OpenByName(stPartInfo.Name);
    if(HI_INVALID_HANDLE == hFlash)
    {
        printf("ERR: HI_Flash_Open!\n");
        s32Ret = HI_FAILURE;
        goto out0;
    }

    s32Ret = HI_Flash_GetInfo(hFlash, &FlashInfo);
    if (HI_SUCCESS != s32Ret)
    {
        printf("ERR: HI_Flash_GetInfo!");
        s32Ret = HI_FAILURE;
        goto out1;
    }

    StartPos = stPartInfo.u32Offset - stPartInfo.u32Offset % FlashInfo.BlockSize;

    if (0 == (stPartInfo.u32Offset + PDM_DEVICE_INFO_SIZE) % FlashInfo.BlockSize)
    {
        EndPos = stPartInfo.u32Offset + PDM_DEVICE_INFO_SIZE;
    }
    else
    {
        EndPos = stPartInfo.u32Offset + PDM_DEVICE_INFO_SIZE + FlashInfo.BlockSize -
                 (stPartInfo.u32Offset + PDM_DEVICE_INFO_SIZE) % FlashInfo.BlockSize;
    }

    UpdateSize = EndPos - StartPos;
    if (UpdateSize > PDM_DEVICE_INFO_MAX_SIZE)
    {
        printf("PDM_DEVICE_INFO_MAX_SIZE too large!\n");
        s32Ret =  HI_FAILURE;
        goto out1;
    }

    if (NULL == (pDevInfoBuf = (HI_CHAR*)malloc(UpdateSize)))
    {
        printf("Failed to malloc space(%u bytes).", UpdateSize + 1);
        s32Ret =  HI_FAILURE;
        goto out1;
    }

    memset(pDevInfoBuf, 0, UpdateSize);
    pcWritePosition = pDevInfoBuf;

    for (i = PDM_DEVICE_INFO_MAC; i < PDM_DEVICE_INFO_BUT; i++)
    {
        memset(TmpCfgValue,0x0,sizeof(TmpCfgValue));
        memset(InputCfgValue,0x0,sizeof(InputCfgValue));
        s32Ret = HI_UNF_PDM_GetDeviceInfo( g_DeviceInfo[i], TmpCfgValue, sizeof(TmpCfgValue));
        if (HI_SUCCESS != s32Ret)
        {
            printf("HI_UNF_PDM_GetDeviceInfo fail!\n");
        }

        if ((pcWritePosition - pDevInfoBuf) + strlen(TmpCfgValue) + 1 > UpdateSize)
        {
            printf("here is not enough FLASH space !");
            break;
        }

        if (!strncmp(g_DeviceInfo[i], pstrCfgName, strlen(pstrCfgName)))
        {
            strncpy(TmpCfgValue, pstrCfgValue, strlen(pstrCfgValue) + 1);
        }

        if (i > PDM_DEVICE_INFO_SN)
        {
            snprintf(InputCfgValue, sizeof(InputCfgValue), "%s=%s", g_DeviceInfo[i], TmpCfgValue);
        }
        else
        {
            snprintf(InputCfgValue, sizeof(InputCfgValue), "%s", TmpCfgValue);
        }

        strncpy(pcWritePosition, InputCfgValue, strlen(InputCfgValue) + 1);

        if (PDM_DEVICE_INFO_LENGTH == i)
        {
            pcLengthTagPos = pcWritePosition ;
        }

        pcWritePosition += strlen(InputCfgValue) + 1; /* skip \0 */

    }

    if (i != PDM_DEVICE_INFO_BUT)
    {
        s32Ret = HI_FAILURE;
        goto out2;
    }

    /*update length*/
    memset(TmpCfgValue,0x0,sizeof(TmpCfgValue));
    snprintf(TmpCfgValue, sizeof(TmpCfgValue), "LENGTH=%08x", (HI_U32)(pcWritePosition - pDevInfoBuf));
    strncpy(pcLengthTagPos, TmpCfgValue, strlen(TmpCfgValue) + 1);

    if (HI_FLASH_TYPE_EMMC_0 != FlashInfo.FlashType)
    {
        Size = HI_Flash_Erase(hFlash, StartPos, UpdateSize);
        if (Size <= 0)
        {
            printf("ERR: HI_Flash_Erase!");
            s32Ret = HI_FAILURE;
            goto out2;
        }
    }

    Size = HI_Flash_Write(hFlash, StartPos, (HI_U8 *)pDevInfoBuf, UpdateSize, HI_FLASH_RW_FLAG_RAW);
    if (Size <= 0)
    {
        printf("ERR: HI_Flash_Write!");
        s32Ret = HI_FAILURE;
        goto out2;
    }

out2:
    free(pDevInfoBuf);

out1:
    HI_Flash_Close(hFlash);
out0:
    return s32Ret;
}


HI_VOID PrintHelp(HI_VOID)
{
    printf("Usage:./sample_deviceinfo type item [value]\n");
    printf("\t type: set/get [set]:set item value; [get]:get item value\n");
    printf("\t item: mac/sn/all [all]:all item\n");
    printf("Example:\n\t./sample_deviceinfo set mac 00:00:00:00:00 \n");
}

HI_S32 GetDeviceInfoItem(HI_CHAR *input, PDM_DEVICE_INFO_E * deviceinfoItem)
{
    if (0 == strcasecmp(input, "mac"))
    {
        *deviceinfoItem = PDM_DEVICE_INFO_MAC;
        return HI_SUCCESS;
    }

    if (0 == strcasecmp(input, "sn"))
    {
        *deviceinfoItem = PDM_DEVICE_INFO_SN;
        return HI_SUCCESS;
    }

    if (0 == strcasecmp(input, "all"))
    {
        *deviceinfoItem = PDM_DEVICE_INFO_ALL;
        return HI_SUCCESS;
    }

    *deviceinfoItem = PDM_DEVICE_INFO_BUT;
    return HI_FAILURE;
}

HI_S32 main(HI_S32 argc,HI_CHAR *argv[])
{
    HI_S32                          Ret;
    HI_S32                          i = 0;
    HI_S32                          ProcessType = 0;
    PDM_DEVICE_INFO_E               DeviceInfoItem;
    HI_CHAR                         DeviceInfoValue[128] = {0};

    if(argc < 3)
    {
        PrintHelp();
        return 0;
    }

    if (0 == strcasecmp(argv[1], "get"))
    {
        ProcessType = 0;
    }

    if (0 == strcasecmp(argv[1], "set"))
    {
        ProcessType = 1;
    }

    if (ProcessType == 1 && argc < 4)
    {
        PrintHelp();
        return 0;
    }

    Ret = GetDeviceInfoItem(argv[2], &DeviceInfoItem);
    if (Ret != HI_SUCCESS)
    {
        printf("DeviceInfoType is Invalid\n");
        return HI_FAILURE;
    }

    if (ProcessType)
    {
        if (DeviceInfoItem >= PDM_DEVICE_INFO_BUT)
        {
            printf("DeviceInfoType is invalid\n");
            return HI_FAILURE;
        }

        memset(DeviceInfoValue, 0x00, sizeof(DeviceInfoValue));

        strncpy(DeviceInfoValue, argv[3], sizeof(DeviceInfoValue));
        Ret = Update_DeviceInfo(g_DeviceInfo[DeviceInfoItem], DeviceInfoValue);
        if (Ret != HI_SUCCESS)
        {
            printf("Update_DeviceInfo fail!\n");
            return HI_FAILURE;
        }
    }
    else
    {
        if (DeviceInfoItem == PDM_DEVICE_INFO_ALL)
        {
            for (i = 0; i < PDM_DEVICE_INFO_BUT; i++)
            {
                memset(DeviceInfoValue, 0x00, sizeof(DeviceInfoValue));
                Ret = HI_UNF_PDM_GetDeviceInfo(g_DeviceInfo[i], DeviceInfoValue, sizeof(DeviceInfoValue));
                if (HI_SUCCESS != Ret)
                {
                    printf("HI_UNF_PDM_GetDeviceInfo fail!\n");
                    return HI_FAILURE;
                }

                printf(">>>%-10s: %s\n",g_DeviceInfo[i], DeviceInfoValue);
            }
        }
        else
        {
            memset(DeviceInfoValue, 0x00, sizeof(DeviceInfoValue));
            Ret = HI_UNF_PDM_GetDeviceInfo(g_DeviceInfo[DeviceInfoItem], DeviceInfoValue, sizeof(DeviceInfoValue));
            if (HI_SUCCESS != Ret)
            {
                printf("HI_UNF_PDM_GetDeviceInfo fail!\n");
                return HI_FAILURE;
            }

            printf(">>>%-10s: %s\n",g_DeviceInfo[DeviceInfoItem], DeviceInfoValue);
        }
    }
    return HI_SUCCESS;
}



