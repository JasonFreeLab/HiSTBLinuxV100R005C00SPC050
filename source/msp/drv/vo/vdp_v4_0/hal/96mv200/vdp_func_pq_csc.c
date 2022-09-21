#include "vdp_drv_pq_ext.h"
#include "hi_type.h"
#include "vdp_hal_vid.h"
#include "vdp_func_pq_csc.h"


HI_S32 VDP_FUNC_GetCSCCoef(HI_PQ_CSC_CRTL_S* pstCscCtrl, VDP_CSC_MODE_E enCscMode, HI_PQ_CSC_COEF_S* pstCscCoef, HI_PQ_CSC_DCCOEF_S* pstCscDcCoef)
{
    HI_U32 u32Pre   = 1 << 10;
    //HI_U32 u32OutDcPre = 64 * u32Pre;
    HI_U32 u32OutDcPre = 4;
    HI_U32 u32InDcPre = 4;
    if (enCscMode == VDP_CSC_RGB2YUV_601)
    {
        pstCscCoef->csc_coef00     = (HI_S32)(0.299  * u32Pre);
        pstCscCoef->csc_coef01     = (HI_S32)(0.587  * u32Pre);
        pstCscCoef->csc_coef02     = (HI_S32)(0.114  * u32Pre);

        pstCscCoef->csc_coef10     = (HI_S32)(-0.172 * u32Pre);
        pstCscCoef->csc_coef11     = (HI_S32)(-0.339 * u32Pre);
        pstCscCoef->csc_coef12     = (HI_S32)(0.511  * u32Pre);

        pstCscCoef->csc_coef20     = (HI_S32)(0.511  * u32Pre);
        pstCscCoef->csc_coef21     = (HI_S32)(-0.428 * u32Pre);
        pstCscCoef->csc_coef22     = (HI_S32)(-0.083 * u32Pre);

        pstCscDcCoef->csc_in_dc2  = 0 * u32InDcPre;
        pstCscDcCoef->csc_in_dc1  = 0 * u32InDcPre;
        pstCscDcCoef->csc_in_dc0  = 0 * u32InDcPre;

        pstCscDcCoef->csc_out_dc0 =  16 * u32OutDcPre;
        pstCscDcCoef->csc_out_dc1 = 128 * u32OutDcPre;
        pstCscDcCoef->csc_out_dc2 = 128 * u32OutDcPre;
    }
    else if (enCscMode == VDP_CSC_YUV2RGB_601)
    {
        pstCscCoef->csc_coef00     = (HI_S32)(    1  * u32Pre);
        pstCscCoef->csc_coef01     = (HI_S32)(    0  * u32Pre);
        pstCscCoef->csc_coef02     = (HI_S32)(1.371  * u32Pre);

        pstCscCoef->csc_coef10     = (HI_S32)(     1 * u32Pre);
        pstCscCoef->csc_coef11     = (HI_S32)(-0.698 * u32Pre);
        pstCscCoef->csc_coef12     = (HI_S32)(-0.336 * u32Pre);

        pstCscCoef->csc_coef20     = (HI_S32)(    1  * u32Pre);
        pstCscCoef->csc_coef21     = (HI_S32)(1.732  * u32Pre);
        pstCscCoef->csc_coef22     = (HI_S32)(    0  * u32Pre);

        pstCscDcCoef->csc_in_dc2  = -16  * u32InDcPre;
        pstCscDcCoef->csc_in_dc1  = -128 * u32InDcPre;
        pstCscDcCoef->csc_in_dc0  = -128 * u32InDcPre;

        pstCscDcCoef->csc_out_dc2 =  0 * u32OutDcPre;
        pstCscDcCoef->csc_out_dc1 =  0 * u32OutDcPre;
        pstCscDcCoef->csc_out_dc0 =  0 * u32OutDcPre;
    }
    else if (enCscMode == VDP_CSC_RGB2YUV_709)
    {
        pstCscCoef->csc_coef00     = (HI_S32)(0.213  * u32Pre);
        pstCscCoef->csc_coef01     = (HI_S32)(0.715  * u32Pre);
        pstCscCoef->csc_coef02     = (HI_S32)(0.072  * u32Pre);
        pstCscCoef->csc_coef10     = (HI_S32)(-0.117 * u32Pre);
        pstCscCoef->csc_coef11     = (HI_S32)(-0.394 * u32Pre);
        pstCscCoef->csc_coef12     = (HI_S32)( 0.511 * u32Pre);
        pstCscCoef->csc_coef20     = (HI_S32)( 0.511 * u32Pre);
        pstCscCoef->csc_coef21     = (HI_S32)(-0.464 * u32Pre);
        pstCscCoef->csc_coef22     = (HI_S32)(-0.047 * u32Pre);

        pstCscDcCoef->csc_in_dc2  = 0 * u32InDcPre;
        pstCscDcCoef->csc_in_dc1  = 0 * u32InDcPre;
        pstCscDcCoef->csc_in_dc0  = 0 * u32InDcPre;

        pstCscDcCoef->csc_out_dc0 = 16  * u32OutDcPre;
        pstCscDcCoef->csc_out_dc1 = 128 * u32OutDcPre;
        pstCscDcCoef->csc_out_dc2 = 128 * u32OutDcPre;
    }
    else if (enCscMode == VDP_CSC_YUV2RGB_709)
    {
        pstCscCoef->csc_coef00     = (HI_S32)(    1  * u32Pre);
        pstCscCoef->csc_coef01     = (HI_S32)(    0  * u32Pre);
        pstCscCoef->csc_coef02     = (HI_S32)(1.540  * u32Pre);

        pstCscCoef->csc_coef10     = (HI_S32)(     1 * u32Pre);
        pstCscCoef->csc_coef11     = (HI_S32)(-0.183 * u32Pre);
        pstCscCoef->csc_coef12     = (HI_S32)(-0.459 * u32Pre);

        pstCscCoef->csc_coef20     = (HI_S32)(    1  * u32Pre);
        pstCscCoef->csc_coef21     = (HI_S32)(1.816  * u32Pre);
        pstCscCoef->csc_coef22     = (HI_S32)(    0  * u32Pre);

        pstCscDcCoef->csc_in_dc0  = -16  * u32InDcPre;
        pstCscDcCoef->csc_in_dc1  = -128 * u32InDcPre;
        pstCscDcCoef->csc_in_dc2  = -128 * u32InDcPre;

        pstCscDcCoef->csc_out_dc0 = 0 * u32OutDcPre;
        pstCscDcCoef->csc_out_dc1 = 0 * u32OutDcPre;
        pstCscDcCoef->csc_out_dc2 = 0 * u32OutDcPre;
    }
    else if (enCscMode == VDP_CSC_YUV2YUV_709_601)
    {
        pstCscCoef->csc_coef00     = (HI_S32)(     1 * u32Pre);
        pstCscCoef->csc_coef01     = (HI_S32)(-0.116 * u32Pre);
        pstCscCoef->csc_coef02     = (HI_S32)( 0.208 * u32Pre);
        pstCscCoef->csc_coef10     = (HI_S32)(     0 * u32Pre);
        pstCscCoef->csc_coef11     = (HI_S32)( 1.017 * u32Pre);
        pstCscCoef->csc_coef12     = (HI_S32)( 0.114 * u32Pre);
        pstCscCoef->csc_coef20     = (HI_S32)(     0 * u32Pre);
        pstCscCoef->csc_coef21     = (HI_S32)( 0.075 * u32Pre);
        pstCscCoef->csc_coef22     = (HI_S32)( 1.025 * u32Pre);

        pstCscDcCoef->csc_in_dc0  = -16  * u32InDcPre;
        pstCscDcCoef->csc_in_dc1  = -128 * u32InDcPre;
        pstCscDcCoef->csc_in_dc2  = -128 * u32InDcPre;

        pstCscDcCoef->csc_out_dc0 =   16 * u32OutDcPre;
        pstCscDcCoef->csc_out_dc1 =  128 * u32OutDcPre;
        pstCscDcCoef->csc_out_dc2 =  128 * u32OutDcPre;
    }
    else if (enCscMode == VDP_CSC_YUV2YUV_601_709)
    {
        pstCscCoef->csc_coef00     = (HI_S32)(     1 * u32Pre);
        pstCscCoef->csc_coef01     = (HI_S32)(-0.116 * u32Pre);
        pstCscCoef->csc_coef02     = (HI_S32)( 0.208 * u32Pre);

        pstCscCoef->csc_coef10     = (HI_S32)(     0 * u32Pre);
        pstCscCoef->csc_coef11     = (HI_S32)( 1.017 * u32Pre);
        pstCscCoef->csc_coef12     = (HI_S32)( 0.114 * u32Pre);

        pstCscCoef->csc_coef20     = (HI_S32)(     0 * u32Pre);
        pstCscCoef->csc_coef21     = (HI_S32)( 0.075 * u32Pre);
        pstCscCoef->csc_coef22     = (HI_S32)( 1.025 * u32Pre);

        pstCscDcCoef->csc_in_dc2  = -16  * u32InDcPre;
        pstCscDcCoef->csc_in_dc1  = -128 * u32InDcPre;
        pstCscDcCoef->csc_in_dc0  = -128 * u32InDcPre;

        pstCscDcCoef->csc_out_dc2 =   16 * u32OutDcPre;
        pstCscDcCoef->csc_out_dc1 =  128 * u32OutDcPre;
        pstCscDcCoef->csc_out_dc0 =  128 * u32OutDcPre;
    }
    else
    {
        pstCscCoef->csc_coef00     = 1 * u32Pre;
        pstCscCoef->csc_coef01     = 0 * u32Pre;
        pstCscCoef->csc_coef02     = 0 * u32Pre;

        pstCscCoef->csc_coef10     = 0 * u32Pre;
        pstCscCoef->csc_coef11     = 1 * u32Pre;
        pstCscCoef->csc_coef12     = 0 * u32Pre;

        pstCscCoef->csc_coef20     = 0 * u32Pre;
        pstCscCoef->csc_coef21     = 0 * u32Pre;
        pstCscCoef->csc_coef22     = 1 * u32Pre;

        pstCscDcCoef->csc_in_dc0  = -16  * u32InDcPre;
        pstCscDcCoef->csc_in_dc1  = -128 * u32InDcPre;
        pstCscDcCoef->csc_in_dc2  = -128 * u32InDcPre;

        pstCscDcCoef->csc_out_dc0 =  16 * u32OutDcPre;
        pstCscDcCoef->csc_out_dc1 = 128 * u32OutDcPre;
        pstCscDcCoef->csc_out_dc2 = 128 * u32OutDcPre;
    }
    return HI_SUCCESS;
}


HI_S32 VDP_FUNC_GetWcgGmmCoef(HI_U32 u32Layer, HI_U16 *pu16GmmCoef)
{

	return HI_SUCCESS;
}

HI_S32 VDP_FUNC_GetWcgDegmmCoef(HI_U32 u32Layer, HI_U16 *pu16DegmmCoef)
{
	return HI_SUCCESS;
}
