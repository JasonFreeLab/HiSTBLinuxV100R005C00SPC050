//#include <linux/io.h>
//#include <linux/delay.h>
#include "vpss_cbb_common.h"
//#include "vpss_reg.h"

#if 1
HI_VOID VPSS_DRV_Set_VPSS_VHD0LBA_DSIZE(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 Hgt, HI_U32 Wth)
{
    //    VPSS_FATAL("w = %d,h = %d\n",Wth,Hgt);
    U_VPSS_VHD0LBA_DSIZE  VPSS_VHD0LBA_DSIZE;
    VPSS_VHD0LBA_DSIZE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_VHD0LBA_DSIZE.u32));
    VPSS_VHD0LBA_DSIZE.bits.vhd0_lba_width  = Wth - 1;
    VPSS_VHD0LBA_DSIZE.bits.vhd0_lba_height = Hgt - 1;

    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_VHD0LBA_DSIZE.u32), VPSS_VHD0LBA_DSIZE.u32);
}
HI_VOID VPSS_DRV_Set_VPSS_VHD0LBA_VFPOS(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32Y, HI_U32 u32X)
{
    U_VPSS_VHD0LBA_VFPOS VPSS_VHD0LBA_VFPOS;
    VPSS_VHD0LBA_VFPOS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_VHD0LBA_VFPOS.u32));
    VPSS_VHD0LBA_VFPOS.bits.vhd0_lba_xfpos  = u32X;
    VPSS_VHD0LBA_VFPOS.bits.vhd0_lba_yfpos  = u32Y;

    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_VHD0LBA_VFPOS.u32), VPSS_VHD0LBA_VFPOS.u32);
}
HI_VOID VPSS_DRV_Set_VPSS_VHD0LBA_BK(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32YColor, HI_U32 u32CbColor, HI_U32 u32CrColor)
{
    U_VPSS_VHD0LBA_BK VPSS_VHD0LBA_BK;
    VPSS_VHD0LBA_BK.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_VHD0LBA_BK.u32));
    VPSS_VHD0LBA_BK.bits.vhd0_vbk_y   = u32YColor;
    VPSS_VHD0LBA_BK.bits.vhd0_vbk_cb  = u32CbColor;
    VPSS_VHD0LBA_BK.bits.vhd0_vbk_cr  = u32CrColor;

    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_VHD0LBA_BK.u32), VPSS_VHD0LBA_BK.u32);
}

#endif
