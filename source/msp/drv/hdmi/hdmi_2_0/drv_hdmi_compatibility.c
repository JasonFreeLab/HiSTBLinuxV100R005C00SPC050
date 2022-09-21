#include "drv_hdmi_compatibility.h"
#include "hdmi_osal.h"

#define DEF_FILE_NAMELENGTH 32

#define COMPAT_NULL_CHK(p)	do{\
	if(HI_NULL==p)\
	{HDMI_ERR("NULL pionter!\n");return HI_FAILURE;}\
}while(0);


typedef struct{
    HDMI_EDID_MANUFACTURE_INFO_S stEdid;
    HI_U64                       u64MsUnder340M;
    HI_U64                       u64MsOver340M;
}COMPAT_HDCP_MS_S;

typedef struct
{
    HDMI_EDID_MANUFACTURE_INFO_S stEdid;
    HI_U32                       u32MsCrgDiv;
    HI_U32                       u32MsPhySrst;
}COMPAT_SINK_CRG_S;

typedef struct
{
    HDMI_EDID_MANUFACTURE_INFO_S stEdid;
    HDMI_SAMPLE_RATE_E           enAudioSmpRate;
    HI_U32                       u32TmdsClk;
    HI_U32                       u32NValue;
    HI_U32                       u32CtsValue;
}COMPAT_AUDIO_NCTS_S;

typedef struct{
    HDMI_EDID_MANUFACTURE_INFO_S    stEdid;
    HDMI_VIDEO_TIMING_E             enTimming;      /* note: HDMI_VIDEO_TIMING_BUTT indicate that for all timiming compatibility config is needed to the TV.*/
    HDMI_AVMUTE_CFG_S               stAvmuteCfg;
}COMPAT_SINK_AVMUTE_S;

typedef struct
{
    HDMI_EDID_MANUFACTURE_INFO_S stEdid;
    HDMI_HDR_DEBUG_MOD_E         enHdrDebugMode;
}COMPAT_HDR_S;

typedef struct
{
    HDMI_EDID_MANUFACTURE_INFO_S stEdid;
    HDMI_VIDEO_TIMING_E          enTimming;
    HI_U32                       u32FmtDelay;
    HI_U32                       u32MuteDelay;
}COMPAT_SINK_DELAY_S;

static HDMI_EDID_MANUFACTURE_INFO_S s_astSinkCecUnsupport[] =
{
    /* Name[4],ProdCode,SerialNO,Week,Year */
    {   "000" ,       0,       0,   0,   0,},
};

static COMPAT_HDCP_MS_S s_astSinkHdcpMs[] =
{
    /*  {Name[4],ProdCode,SerialNO,Week, Year},  Under340  Over340 */
    {   {"SNY" ,    51203,16843009,   1, 2015},   500,    2100},        //sony KD-65X9300D
    {   {"MEI" ,    41622,16843009,   0, 2014},  2000,    3000},        //panasonic TH-58AX800C
    {   {"GSM" ,        1,16843009,   1, 2016},   500,    6000},        //LG OLED 65B6P-C
};

static COMPAT_SINK_AVMUTE_S s_astSinkAvmute[] =
{
    /*  {Name[4],ProdCode,SerialNO,Week, Year},                   timming,           mutePkgEn,Set(no use), bMuteClr, bMuteRpt,u32RptCnt */
    {   {"DEF" ,        0,       0,   0,    0},  HDMI_VIDEO_TIMING_BUTT             , {  HI_TRUE,  HI_TRUE,  HI_TRUE,  HI_TRUE,    17} },        //default config for all other TV have no problem.
    {   {"HEC" ,       48,       1,  35, 2010},  HDMI_VIDEO_TIMING_BUTT             , { HI_FALSE, HI_FALSE, HI_FALSE, HI_FALSE,     0} },        // skyworth LED49EC520UA
    {   {"SAM" ,     3140,16777217,  42, 2014},  HDMI_VIDEO_TIMING_BUTT             , { HI_FALSE, HI_FALSE, HI_FALSE, HI_FALSE,     0} },        // samsung UA48JU5900CXXZ
    {   {"SHP" ,     4452,       0, 255, 2016},  HDMI_VIDEO_TIMING_BUTT             , { HI_FALSE, HI_FALSE, HI_FALSE, HI_FALSE,     0} },        // sharp LCD-60TX85A
    {   {"MST" ,       48,       1,   0, 2007},  HDMI_VIDEO_TIMING_BUTT             , { HI_FALSE, HI_FALSE, HI_FALSE, HI_FALSE,     0} },
    {   {"GSM" ,        1,16843009,   1, 2016},  HDMI_VIDEO_TIMING_BUTT             , { HI_FALSE, HI_FALSE, HI_FALSE, HI_FALSE,     0} },
};

static COMPAT_SINK_CRG_S s_astSinkCrgMs[] =

{
    /*  {Name[4],ProdCode,SerialNO,Week, Year},  u32MsCrgDiv  u32MsPhySrst */
    {   {"MEI" ,    41622,16843009,   0, 2014},  100,         100},        //panasonic TH-58AX800C
};

static HDMI_EDID_MANUFACTURE_INFO_S s_astSinkScdcPos[] =

{
    /*  {Name[4],ProdCode,SerialNO,Week, Year},     */
    {"GSM" ,        1,16843009,   1, 2016},             //LG OLED 65B6P-C
};

static COMPAT_AUDIO_NCTS_S s_astSinkAudioNCts[] =
{
    /*  {Name[4],ProdCode,SerialNO,Week, Year},  AudSmpRate, u32TmdsClk,    N,     CTS */
    {   {"SKY" ,        1,16843009,   2, 2016}, HDMI_SAMPLE_RATE_48K, 297000, 6144, 297000},        //sky 50M5
    {   {"SKY" ,       48,       1,   1, 2012}, HDMI_SAMPLE_RATE_48K, 297000, 6144, 297000},        //sky 43E600G
    {   {"SKY" ,        1,16843009,  15, 2016}, HDMI_SAMPLE_RATE_48K, 297000, 6144, 297000},        //sky 43G7200
    {   {"HEC" ,       48,       1,  35, 2010}, HDMI_SAMPLE_RATE_48K, 297000, 6144, 297000},        //hisense LED43K300U
    {   {"SKY" ,        1,16843009,  17, 2015}, HDMI_SAMPLE_RATE_48K, 297000, 6144, 297000},        //sky 43G7200
};

#ifdef HDMI_HDR_SUPPORT
static COMPAT_HDR_S s_stSinkHdrDebugMode[] =
{
    /*  {Name[4],ProdCode,SerialNO,Week, Year},  enHdrDebugMode */
    {   {"GSM" ,        1,16843009,   1, 2016},  HDMI_HDR_DEBUG_MODE_OE},   // LG:65UH770T
};
#endif

static HDMI_EDID_MANUFACTURE_INFO_S s_astSinkCecPingMap[] =
{
    /*  {Name[4],ProdCode,SerialNO,Week, Year},     */
    {"GSM" ,        0,       0,   0, 2016},             //LG 2016
    {"GSM" ,        0,       0,   0, 2017},             //LG 2017
};

static COMPAT_SINK_DELAY_S s_astSinkDelay[] =
{
    /*  {Name[4],ProdCode,SerialNO,Week, Year},                   timming,          fmtDelay, muteDelay */
    //{   {"DEF" ,        0,       0,   0,    0},  HDMI_VIDEO_TIMING_BUTT             ,   500,    120},        //default config for all other TV have no problem.
    {   {"LTV" ,       48,       1,   6, 2014},  HDMI_VIDEO_TIMING_BUTT              ,   200,    120},        // LeTV
    {   {"SKW" ,       48,       1,   1, 2008},  HDMI_VIDEO_TIMING_BUTT              ,   500,    500},        // SKY 24E60HR
    {   {"SKY" ,       48,       1,  10, 2010},  HDMI_VIDEO_TIMING_BUTT              ,   200,      0},
    {   {"TCL" ,        0,       0,  20, 2013},  HDMI_VIDEO_TIMING_BUTT              ,   500,    500},
};

static HI_BOOL CompatEdidMatchChk(HDMI_EDID_MANUFACTURE_INFO_S *pstTmpManuInfo,
                            HDMI_EDID_MANUFACTURE_INFO_S *pstSinkManuInfo)
{
    HI_BOOL bMatch = HI_FALSE;

    if (  (HI_NULL == pstTmpManuInfo)
        ||(HI_NULL == pstSinkManuInfo) )
    {
        return HI_FALSE;
    }
    
    bMatch =  (pstTmpManuInfo->u8MfrsName[0] == pstSinkManuInfo->u8MfrsName[0])
                && (pstTmpManuInfo->u8MfrsName[1] == pstSinkManuInfo->u8MfrsName[1])
                && (pstTmpManuInfo->u8MfrsName[2] == pstSinkManuInfo->u8MfrsName[2])
                && (pstTmpManuInfo->u8MfrsName[3] == pstSinkManuInfo->u8MfrsName[3])
                && (pstTmpManuInfo->u32ProductCode == pstSinkManuInfo->u32ProductCode)
                && (pstTmpManuInfo->u32SerialNumber == pstSinkManuInfo->u32SerialNumber)
                && (pstTmpManuInfo->u32Week == pstSinkManuInfo->u32Week)
                && (pstTmpManuInfo->u32Year == pstSinkManuInfo->u32Year) ;

    return bMatch;
}

HI_BOOL DRV_HDMI_CompatCecValidCheck(HDMI_DEVICE_S *pstHdmiDev)
{
    HI_U32                          i = 0;
    HI_BOOL                         bValid = HI_TRUE;
    HDMI_SINK_CAPABILITY_S          *pstSinkCap = HI_NULL;
    HDMI_EDID_MANUFACTURE_INFO_S    *pstTmpManuInfo = HI_NULL;
    HDMI_EDID_MANUFACTURE_INFO_S    *pstSinkManuInfo= HI_NULL ;

    if (HDMI_EDID_DATA_INVALID == DRV_HDMI_EdidCapabilityGet(&pstHdmiDev->stEdidInfo, &pstSinkCap))
    {
        HDMI_WARN("Get sink capability fail\n");
        bValid  = HI_FALSE;
    }
    else
    {
        pstSinkManuInfo = &pstSinkCap->stMfrsInfo;

        for( i=0, pstTmpManuInfo = &s_astSinkCecUnsupport[0];
            pstTmpManuInfo && pstSinkManuInfo && (i < HDMI_ARRAY_SIZE(s_astSinkCecUnsupport));
            pstTmpManuInfo++,i++)
        {
            if( CompatEdidMatchChk(pstTmpManuInfo,pstSinkManuInfo) )
            {
                bValid  = HI_FALSE;
                HDMI_WARN("error CEC PHY ADDR,not support.\n");
                break;
            }
        }
    }
    pstSinkCap->stCECAddr.bPhyAddrValid &= bValid ;

    return pstSinkCap->stCECAddr.bPhyAddrValid;
}


HI_S32  DRV_HDMI_CompatHdcpMsGet(HDMI_DEVICE_ID_E enHdmiId,HI_U64 *pu64WaitMs)
{
    HI_U32                          i = 0;
    HDMI_SINK_CAPABILITY_S          *pstSinkCap = HI_NULL;
    COMPAT_HDCP_MS_S                *pstHdcpMs = HI_NULL;
    HDMI_EDID_MANUFACTURE_INFO_S    *pstTmpManuInfo = HI_NULL ;
    HDMI_EDID_MANUFACTURE_INFO_S    *pstSinkManuInfo= HI_NULL ;
    HDMI_DEVICE_S                   *pstHdmiDev = HI_NULL;

    pstHdmiDev = GetHdmiDevice(enHdmiId);
    COMPAT_NULL_CHK(pstHdmiDev);
    COMPAT_NULL_CHK(pu64WaitMs);

    /* default value */
    *pu64WaitMs = 500;

    if (HDMI_EDID_DATA_INVALID == DRV_HDMI_EdidCapabilityGet(&pstHdmiDev->stEdidInfo, &pstSinkCap))
    {
        HDMI_WARN("Get sink capability fail\n");
        return HI_FAILURE;
    }
    else
    {
        pstSinkManuInfo = &pstSinkCap->stMfrsInfo;

        for( i=0, pstHdcpMs = &s_astSinkHdcpMs[0];
            pstHdcpMs && (i < HDMI_ARRAY_SIZE(s_astSinkHdcpMs));
            pstHdcpMs++, i++)
        {
            pstTmpManuInfo = &pstHdcpMs->stEdid;

            if( CompatEdidMatchChk(pstTmpManuInfo,pstSinkManuInfo) )
            {
                *pu64WaitMs = pstHdmiDev->stAttr.stVOAttr.u32HdmiAdaptPixClk >= FMT_PIX_CLK_340000 ?
                                pstHdcpMs->u64MsOver340M : pstHdcpMs->u64MsUnder340M;
                break;
            }
        }
    }

    return HI_SUCCESS;
}

HI_S32  DRV_HDMI_CompatAvmuteGet(HDMI_DEVICE_ID_E enHdmiId,HI_BOOL bAvmute,HDMI_AVMUTE_CFG_S *pstAvmuteCfg)
{
    HI_U32                          i = 0;
    HDMI_SINK_CAPABILITY_S          *pstSinkCap = HI_NULL;
    COMPAT_SINK_AVMUTE_S            *pstSinkAvmute = HI_NULL;
    HDMI_EDID_MANUFACTURE_INFO_S    *pstTmpManuInfo = HI_NULL ;
    HDMI_EDID_MANUFACTURE_INFO_S    *pstSinkManuInfo= HI_NULL ;
    HDMI_DEVICE_S                   *pstHdmiDev = HI_NULL;

    pstHdmiDev = GetHdmiDevice(enHdmiId);
    COMPAT_NULL_CHK(pstHdmiDev);
    COMPAT_NULL_CHK(pstAvmuteCfg);

    /* default value */
    pstSinkAvmute = &s_astSinkAvmute[0];
    pstAvmuteCfg->bMutePkgEn    = pstSinkAvmute->stAvmuteCfg.bMutePkgEn;
    pstAvmuteCfg->bMuteSet      = bAvmute;
    pstAvmuteCfg->bMuteClr      = (!bAvmute) && pstSinkAvmute->stAvmuteCfg.bMuteClr;
    pstAvmuteCfg->bMuteRptEn    = pstSinkAvmute->stAvmuteCfg.bMuteRptEn;
    pstAvmuteCfg->u32RptCnt     = pstSinkAvmute->stAvmuteCfg.u32RptCnt;

    if (HDMI_EDID_DATA_INVALID == DRV_HDMI_EdidCapabilityGet(&pstHdmiDev->stEdidInfo, &pstSinkCap))
    {
        HDMI_WARN("Get sink capability fail\n");
        return HI_FAILURE;
    }
    else
    {
        pstSinkManuInfo = &pstSinkCap->stMfrsInfo;

        for( i = 1, pstSinkAvmute = &s_astSinkAvmute[1];
            pstSinkAvmute && (i < HDMI_ARRAY_SIZE(s_astSinkAvmute));
            pstSinkAvmute++, i++)
        {
            pstTmpManuInfo = &pstSinkAvmute->stEdid;

            if( CompatEdidMatchChk(pstTmpManuInfo,pstSinkManuInfo) )
            {
                if ((pstHdmiDev->stAttr.stVOAttr.enVideoTiming == pstSinkAvmute->enTimming)
                    || (HDMI_VIDEO_TIMING_BUTT == pstSinkAvmute->enTimming)) //HDMI_VIDEO_TIMING_BUTT meants all timming use the same config to the TV.
                {
                    pstAvmuteCfg->bMutePkgEn    = pstSinkAvmute->stAvmuteCfg.bMutePkgEn;
                    pstAvmuteCfg->bMuteSet      = bAvmute;
                    pstAvmuteCfg->bMuteClr      = (!bAvmute) && pstSinkAvmute->stAvmuteCfg.bMuteClr;
                    pstAvmuteCfg->bMuteRptEn    = pstSinkAvmute->stAvmuteCfg.bMuteRptEn;
                    pstAvmuteCfg->u32RptCnt     = pstSinkAvmute->stAvmuteCfg.u32RptCnt;
                    break;
                }
            }
        }
    }

    return HI_SUCCESS;
}

HI_S32  DRV_HDMI_CompatCrgMsGet(HDMI_DEVICE_ID_E enHdmiId,HI_U32 *pu32CrgDivMs,HI_U32 *pu32PhySrstMs)
{
    HI_U32                          i = 0;
    HDMI_SINK_CAPABILITY_S          *pstSinkCap = HI_NULL;
    COMPAT_SINK_CRG_S               *pstCrgMs = HI_NULL;
    HDMI_EDID_MANUFACTURE_INFO_S    *pstTmpManuInfo = HI_NULL ;
    HDMI_EDID_MANUFACTURE_INFO_S    *pstSinkManuInfo= HI_NULL ;
    HDMI_DEVICE_S                   *pstHdmiDev = HI_NULL;

    pstHdmiDev = GetHdmiDevice(enHdmiId);
    COMPAT_NULL_CHK(pstHdmiDev);
    COMPAT_NULL_CHK(pu32CrgDivMs);
    COMPAT_NULL_CHK(pu32PhySrstMs);

    /* default value */
    *pu32CrgDivMs      = 1;
    *pu32PhySrstMs     = 1;

    if (HDMI_EDID_DATA_INVALID == DRV_HDMI_EdidCapabilityGet(&pstHdmiDev->stEdidInfo, &pstSinkCap))
    {
        HDMI_WARN("Get sink capability fail\n");
        return HI_FAILURE;
    }
    else
    {
        pstSinkManuInfo = &pstSinkCap->stMfrsInfo;

        for( i = 0, pstCrgMs = &s_astSinkCrgMs[0];
            pstCrgMs && (i < HDMI_ARRAY_SIZE(s_astSinkCrgMs));
            pstCrgMs++, i++)
        {
            pstTmpManuInfo = &pstCrgMs->stEdid;

            if( CompatEdidMatchChk(pstTmpManuInfo,pstSinkManuInfo) )
            {
                *pu32CrgDivMs      = pstCrgMs->u32MsCrgDiv;
                *pu32PhySrstMs     = pstCrgMs->u32MsPhySrst;
                break;
            }
        }
    }

    return HI_SUCCESS;
}

HI_BOOL DRV_HDMI_CompatScdcInStartGet(HDMI_DEVICE_ID_E enHdmiId)
{
    HI_U32                          i = 0;
    HI_BOOL                         bInStart = HI_FALSE;
    HDMI_SINK_CAPABILITY_S          *pstSinkCap = HI_NULL;
    HDMI_EDID_MANUFACTURE_INFO_S    *pstTmpManuInfo = HI_NULL ;
    HDMI_EDID_MANUFACTURE_INFO_S    *pstSinkManuInfo= HI_NULL ;
    HDMI_DEVICE_S                   *pstHdmiDev = HI_NULL;

    pstHdmiDev = GetHdmiDevice(enHdmiId);
    COMPAT_NULL_CHK(pstHdmiDev);

    /* default value */
    bInStart = HI_FALSE;

    if (HDMI_EDID_DATA_INVALID == DRV_HDMI_EdidCapabilityGet(&pstHdmiDev->stEdidInfo, &pstSinkCap))
    {
        HDMI_WARN("Get sink capability fail\n");
        //return HI_FALSE;
    }
    else
    {
        pstSinkManuInfo = &pstSinkCap->stMfrsInfo;

        for( i = 0, pstTmpManuInfo = &s_astSinkScdcPos[0];
            pstTmpManuInfo && (i < HDMI_ARRAY_SIZE(s_astSinkScdcPos));
            pstTmpManuInfo++, i++)
        {
            if( CompatEdidMatchChk(pstTmpManuInfo,pstSinkManuInfo) )
            {
                bInStart = HI_TRUE;
                break;
            }
        }
    }

    return bInStart;
}

HI_S32  DRV_HDMI_CompatAudNCtsGet(HDMI_DEVICE_ID_E enHdmiId, HI_U32 *pu32NValue, HI_U32 *pu32CtsValue)
{
    HI_U32                          i = 0;
    HDMI_SINK_CAPABILITY_S          *pstSinkCap = HI_NULL;
    COMPAT_AUDIO_NCTS_S             *pstAudNCts = HI_NULL;
    HDMI_EDID_MANUFACTURE_INFO_S    *pstTmpManuInfo = HI_NULL ;
    HDMI_EDID_MANUFACTURE_INFO_S    *pstSinkManuInfo= HI_NULL ;
    HDMI_DEVICE_S                   *pstHdmiDev = HI_NULL;
    HI_S32                          s32Ret = HI_FAILURE;

    pstHdmiDev = GetHdmiDevice(enHdmiId);
    COMPAT_NULL_CHK(pstHdmiDev);
    COMPAT_NULL_CHK(pu32NValue);
    COMPAT_NULL_CHK(pu32CtsValue);

    if (HDMI_EDID_DATA_INVALID == DRV_HDMI_EdidCapabilityGet(&pstHdmiDev->stEdidInfo, &pstSinkCap))
    {
        HDMI_WARN("Get sink capability fail\n");
        s32Ret =  HI_FAILURE;
    }
    else
    {
        pstSinkManuInfo = &pstSinkCap->stMfrsInfo;

        for( i = 0, pstAudNCts = &s_astSinkAudioNCts[0];
            pstAudNCts && (i < HDMI_ARRAY_SIZE(s_astSinkAudioNCts));
            pstAudNCts++, i++)
        {
            pstTmpManuInfo = &pstAudNCts->stEdid;

            if ( IS_STR_EQUAL("SKY", pstSinkManuInfo->u8MfrsName)
                || CompatEdidMatchChk(pstTmpManuInfo, pstSinkManuInfo) )
            {
                if ( (pstHdmiDev->stAttr.stVOAttr.u32HdmiAdaptPixClk == pstAudNCts->u32TmdsClk)
                    && (pstHdmiDev->stAttr.stAOAttr.enSampleFs == pstAudNCts->enAudioSmpRate) )
                {
                    *pu32NValue      = pstAudNCts->u32NValue;
                    *pu32CtsValue    = pstAudNCts->u32CtsValue;
                    HDMI_INFO("N = %u, CTS = %u\n", pstAudNCts->u32NValue, pstAudNCts->u32CtsValue);
                    s32Ret = HI_SUCCESS;
                    break;
                }
            }
        }
    }

    return s32Ret;
}

#ifdef HDMI_HDR_SUPPORT
HI_S32  DRV_HDMI_CompatHdrDebugModeGet(HDMI_DEVICE_ID_E enHdmiId, HDMI_HDR_DEBUG_MOD_E *penHdrDebugMode)
{
    HI_U32                          i = 0;
    HDMI_SINK_CAPABILITY_S          *pstSinkCap = HI_NULL;
    COMPAT_HDR_S                    *pstHdr = HI_NULL;
    HDMI_EDID_MANUFACTURE_INFO_S    *pstTmpManuInfo = HI_NULL ;
    HDMI_EDID_MANUFACTURE_INFO_S    *pstSinkManuInfo= HI_NULL ;
    HDMI_DEVICE_S                   *pstHdmiDev = HI_NULL;

    pstHdmiDev = GetHdmiDevice(enHdmiId);
    COMPAT_NULL_CHK(pstHdmiDev);
    COMPAT_NULL_CHK(penHdrDebugMode);

    /* default value */
    *penHdrDebugMode = HDMI_HDR_DEBUG_MODE_NONE;

    if (HDMI_EDID_DATA_INVALID == DRV_HDMI_EdidCapabilityGet(&pstHdmiDev->stEdidInfo, &pstSinkCap))
    {
        HDMI_WARN("Get sink capability fail\n");
        return HI_FAILURE;
    }
    else
    {
        pstSinkManuInfo = &pstSinkCap->stMfrsInfo;

        for ( i = 0, pstHdr = &s_stSinkHdrDebugMode[0];
            pstHdr && (i < HDMI_ARRAY_SIZE(s_stSinkHdrDebugMode));
            pstHdr++, i++)
        {
            pstTmpManuInfo = &pstHdr->stEdid;

            if ( CompatEdidMatchChk(pstTmpManuInfo, pstSinkManuInfo) )
            {
                *penHdrDebugMode = pstHdr->enHdrDebugMode;
                HDMI_INFO("set hdrdebugmode = %d.\n", pstHdr->enHdrDebugMode);
                break;
            }
        }
    }

    return HI_SUCCESS;
}
#endif

HI_BOOL  DRV_HDMI_CompatCecMapPlaydev(HDMI_DEVICE_ID_E enHdmiId)
{
    HI_U32                          i = 0;
    HDMI_SINK_CAPABILITY_S          *pstSinkCap = HI_NULL;
    HDMI_EDID_MANUFACTURE_INFO_S    *pstTmpManuInfo = HI_NULL ;
    HDMI_EDID_MANUFACTURE_INFO_S    *pstSinkManuInfo= HI_NULL ;
    HDMI_DEVICE_S                   *pstHdmiDev = HI_NULL;
    HI_BOOL                         bMatch = HI_FALSE;

    pstHdmiDev = GetHdmiDevice(enHdmiId);
    COMPAT_NULL_CHK(pstHdmiDev);

    if (HDMI_EDID_DATA_INVALID == DRV_HDMI_EdidCapabilityGet(&pstHdmiDev->stEdidInfo, &pstSinkCap))
    {
        HDMI_WARN("Get sink capability fail\n");
    }
    else
    {
        pstSinkManuInfo = &pstSinkCap->stMfrsInfo;

        for ( i = 0, pstTmpManuInfo = &s_astSinkCecPingMap[0];
            pstTmpManuInfo && (i < HDMI_ARRAY_SIZE(s_astSinkCecPingMap));
            pstTmpManuInfo++, i++)
        {
            bMatch =  (pstTmpManuInfo->u8MfrsName[0] == pstSinkManuInfo->u8MfrsName[0])
                && (pstTmpManuInfo->u8MfrsName[1] == pstSinkManuInfo->u8MfrsName[1])
                && (pstTmpManuInfo->u8MfrsName[2] == pstSinkManuInfo->u8MfrsName[2])
                && (pstTmpManuInfo->u8MfrsName[3] == pstSinkManuInfo->u8MfrsName[3])
                && (pstTmpManuInfo->u32Year == pstSinkManuInfo->u32Year) ;

            if (bMatch)
            {
                break;
            }
        }
    }

    return bMatch;
}

HI_S32  DRV_HDMI_CompatDelayGet(HDMI_DEVICE_ID_E enHdmiId, HDMI_DELAY_S *pstDelay)
{
    HI_U32                          i = 0;
    HDMI_SINK_CAPABILITY_S          *pstSinkCap = HI_NULL;
    COMPAT_SINK_DELAY_S             *pstSinkDelay = HI_NULL;
    HDMI_EDID_MANUFACTURE_INFO_S    *pstTmpManuInfo = HI_NULL ;
    HDMI_EDID_MANUFACTURE_INFO_S    *pstSinkManuInfo= HI_NULL ;
    HDMI_DEVICE_S                   *pstHdmiDev = HI_NULL;

    pstHdmiDev = GetHdmiDevice(enHdmiId);
    COMPAT_NULL_CHK(pstHdmiDev);
    COMPAT_NULL_CHK(pstDelay);

    if (HDMI_EDID_DATA_INVALID == DRV_HDMI_EdidCapabilityGet(&pstHdmiDev->stEdidInfo, &pstSinkCap))
    {
        HDMI_WARN("Get sink capability fail\n");
        return HI_FAILURE;
    }
    else
    {
        pstSinkManuInfo = &pstSinkCap->stMfrsInfo;

        for( i = 0, pstSinkDelay = &s_astSinkDelay[0];
            pstSinkDelay && (i < HDMI_ARRAY_SIZE(s_astSinkDelay));
            pstSinkDelay++, i++)
        {
            pstTmpManuInfo = &pstSinkDelay->stEdid;

            if( CompatEdidMatchChk(pstTmpManuInfo,pstSinkManuInfo) )
            {
                if ((pstHdmiDev->stAttr.stVOAttr.enVideoTiming == pstSinkDelay->enTimming)
                    || (HDMI_VIDEO_TIMING_BUTT == pstSinkDelay->enTimming)) //HDMI_VIDEO_TIMING_BUTT meants all timming use the same config to the TV.
                {
                    pstDelay->u32FmtDelay  = pstSinkDelay->u32FmtDelay;
                    pstDelay->u32MuteDelay = pstSinkDelay->u32MuteDelay;
                    break;
                }
            }
        }
    }

    return HI_SUCCESS;

}

