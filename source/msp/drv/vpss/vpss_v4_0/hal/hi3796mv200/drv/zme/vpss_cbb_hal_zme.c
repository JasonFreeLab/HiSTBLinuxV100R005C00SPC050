//#include <linux/io.h>
//#include <linux/delay.h>
#include "vpss_cbb_common.h"
//#include "vpss_reg.h"

#if 1
//addr=0x2000
HI_VOID VPSS_Zme_Set_VPSS_VHD0_HSP(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 hlmsc_en , HI_U32 hchmsc_en , HI_U32 hlmid_en , HI_U32 hchmid_en , HI_U32 hlfir_en , HI_U32 hchfir_en , HI_U32 hfir_order , HI_U32 hratio )
{
    U_VPSS_VHD0_HSP VPSS_VHD0_HSP;

    VPSS_VHD0_HSP.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_VHD0_HSP.u32));
    VPSS_VHD0_HSP.bits.hlmsc_en   = hlmsc_en   ;
    VPSS_VHD0_HSP.bits.hchmsc_en  = hchmsc_en  ;
    VPSS_VHD0_HSP.bits.hlmid_en   = hlmid_en   ;
    VPSS_VHD0_HSP.bits.hchmid_en  = hchmid_en  ;
    VPSS_VHD0_HSP.bits.hlfir_en   = hlfir_en   ;
    VPSS_VHD0_HSP.bits.hchfir_en  = hchfir_en  ;
    VPSS_VHD0_HSP.bits.hfir_order = hfir_order ;
    VPSS_VHD0_HSP.bits.hratio     = hratio     ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_VHD0_HSP.u32), VPSS_VHD0_HSP.u32);

    return;

}
//addr=0x2004
HI_VOID VPSS_Zme_Set_VPSS_VHD0_HLOFFSET(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 hor_loffset )
{
    U_VPSS_VHD0_HLOFFSET VPSS_VHD0_HLOFFSET;

    VPSS_VHD0_HLOFFSET.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_VHD0_HLOFFSET.u32));
    VPSS_VHD0_HLOFFSET.bits.hor_loffset = hor_loffset ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_VHD0_HLOFFSET.u32), VPSS_VHD0_HLOFFSET.u32);

    return;

}
//addr=0x2008
HI_VOID VPSS_Zme_Set_VPSS_VHD0_HCOFFSET(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 hor_coffset )
{
    U_VPSS_VHD0_HCOFFSET VPSS_VHD0_HCOFFSET;

    VPSS_VHD0_HCOFFSET.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_VHD0_HCOFFSET.u32));
    VPSS_VHD0_HCOFFSET.bits.hor_coffset = hor_coffset ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_VHD0_HCOFFSET.u32), VPSS_VHD0_HCOFFSET.u32);

    return;

}
//addr=0x200c
HI_VOID VPSS_Zme_Set_VPSS_VHD0_VSP(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 vlmsc_en , HI_U32 vchmsc_en , HI_U32 vlmid_en , HI_U32 vchmid_en , HI_U32 vlfir_en , HI_U32 vchfir_en , HI_U32 zme_out_fmt )
{
    U_VPSS_VHD0_VSP VPSS_VHD0_VSP;

    VPSS_VHD0_VSP.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_VHD0_VSP.u32));
    VPSS_VHD0_VSP.bits.vlmsc_en    = vlmsc_en    ;
    VPSS_VHD0_VSP.bits.vchmsc_en   = vchmsc_en   ;
    VPSS_VHD0_VSP.bits.vlmid_en    = vlmid_en    ;
    VPSS_VHD0_VSP.bits.vchmid_en   = vchmid_en   ;
    VPSS_VHD0_VSP.bits.vlfir_en    = vlfir_en    ;
    VPSS_VHD0_VSP.bits.vchfir_en   = vchfir_en   ;
    VPSS_VHD0_VSP.bits.zme_out_fmt = zme_out_fmt ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_VHD0_VSP.u32), VPSS_VHD0_VSP.u32);

    return;

}
HI_VOID VPSS_Zme_Set_VPSS_VHD0_VSP_OutFmt(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 zme_out_fmt )
{
    U_VPSS_VHD0_VSP VPSS_VHD0_VSP;

    VPSS_VHD0_VSP.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_VHD0_VSP.u32));
    VPSS_VHD0_VSP.bits.zme_out_fmt = zme_out_fmt ;
    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_VHD0_VSP.u32), VPSS_VHD0_VSP.u32);

    return;

}

//addr=0x2010
HI_VOID VPSS_Zme_Set_VPSS_VHD0_VSR(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 vratio )
{
    U_VPSS_VHD0_VSR VPSS_VHD0_VSR;

    VPSS_VHD0_VSR.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_VHD0_VSR.u32));
    VPSS_VHD0_VSR.bits.vratio     = vratio     ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_VHD0_VSR.u32), VPSS_VHD0_VSR.u32);

    return;

}
//addr=0x2014
HI_VOID VPSS_Zme_Set_VPSS_VHD0_VOFFSET(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 vluma_offset , HI_U32 vchroma_offset )
{
    U_VPSS_VHD0_VOFFSET VPSS_VHD0_VOFFSET;

    VPSS_VHD0_VOFFSET.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_VHD0_VOFFSET.u32));
    VPSS_VHD0_VOFFSET.bits.vluma_offset   = vluma_offset   ;
    VPSS_VHD0_VOFFSET.bits.vchroma_offset = vchroma_offset ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_VHD0_VOFFSET.u32), VPSS_VHD0_VOFFSET.u32);

    return;

}

HI_VOID VPSS_Zme_Set_VPSS_VHD0_ZMEORESO(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 oh, HI_U32 ow)
{
    U_VPSS_VHD0_ZMEORESO VPSS_VHD0_ZMEORESO;

    VPSS_VHD0_ZMEORESO.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_VHD0_ZMEORESO.u32));
    VPSS_VHD0_ZMEORESO.bits.vhd0_zme_oh = oh - 1;
    VPSS_VHD0_ZMEORESO.bits.vhd0_zme_ow = ow - 1;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_VHD0_ZMEORESO.u32), VPSS_VHD0_ZMEORESO.u32);

    return;
}

HI_VOID VPSS_Zme_Set_VPSS_VHD0_ZME_LHADDR(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 vhd0_scl_lh )
{
    U_VPSS_VHD0_ZME_LHADDR VPSS_VHD0_ZME_LHADDR;

    VPSS_VHD0_ZME_LHADDR.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_VHD0_ZME_LHADDR.u32));
    VPSS_VHD0_ZME_LHADDR.bits.vhd0_scl_lh = vhd0_scl_lh ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_VHD0_ZME_LHADDR.u32), VPSS_VHD0_ZME_LHADDR.u32);

    return;
}

HI_VOID VPSS_Zme_Set_VPSS_VHD0_ZME_LVADDR(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 vhd0_scl_lv )
{
    U_VPSS_VHD0_ZME_LVADDR VPSS_VHD0_ZME_LVADDR;

    VPSS_VHD0_ZME_LVADDR.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_VHD0_ZME_LVADDR.u32));
    VPSS_VHD0_ZME_LVADDR.bits.vhd0_scl_lv = vhd0_scl_lv ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_VHD0_ZME_LVADDR.u32), VPSS_VHD0_ZME_LVADDR.u32);

    return;
}

HI_VOID VPSS_Zme_Set_VPSS_VHD0_ZME_CHADDR(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 vhd0_scl_ch )
{
    U_VPSS_VHD0_ZME_CHADDR VPSS_VHD0_ZME_CHADDR;

    VPSS_VHD0_ZME_CHADDR.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_VHD0_ZME_CHADDR.u32));
    VPSS_VHD0_ZME_CHADDR.bits.vhd0_scl_ch = vhd0_scl_ch ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_VHD0_ZME_CHADDR.u32), VPSS_VHD0_ZME_CHADDR.u32);

    return;

}
HI_VOID VPSS_Zme_Set_VPSS_VHD0_ZME_CVADDR(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 vhd0_scl_cv )
{
    U_VPSS_VHD0_ZME_CVADDR VPSS_VHD0_ZME_CVADDR;

    VPSS_VHD0_ZME_CVADDR.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_VHD0_ZME_CVADDR.u32));
    VPSS_VHD0_ZME_CVADDR.bits.vhd0_scl_cv = vhd0_scl_cv ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_VHD0_ZME_CVADDR.u32), VPSS_VHD0_ZME_CVADDR.u32);

    return;
}

#endif
