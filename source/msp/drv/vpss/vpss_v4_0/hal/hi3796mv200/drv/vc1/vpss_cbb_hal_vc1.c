//#include <linux/io.h>
//#include <linux/delay.h>
#include "vpss_cbb_common.h"
//#include "vpss_reg.h"

#if 1
HI_VOID VPSS_Vc1_SetNx2Vc1Ctr0(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 rangedfrm , HI_U32 profile , HI_U32 mapyflg , HI_U32 mapcflg , HI_U32 mapy , HI_U32 mapc)
{
    U_VPSS_NX2_VC1_CTRL0 VPSS_NX2_VC1_CTRL0;

    VPSS_NX2_VC1_CTRL0.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_NX2_VC1_CTRL0.u32));
    VPSS_NX2_VC1_CTRL0.bits.nx2_vc1_rangedfrm      = rangedfrm;
    VPSS_NX2_VC1_CTRL0.bits.nx2_vc1_profile        = profile;
    VPSS_NX2_VC1_CTRL0.bits.nx2_vc1_mapyflg        = mapyflg;
    VPSS_NX2_VC1_CTRL0.bits.nx2_vc1_mapcflg        = mapcflg;
    VPSS_NX2_VC1_CTRL0.bits.nx2_vc1_mapy           = mapy;
    VPSS_NX2_VC1_CTRL0.bits.nx2_vc1_mapc           = mapc;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_NX2_VC1_CTRL0.u32), VPSS_NX2_VC1_CTRL0.u32);

    return;
}

#endif
