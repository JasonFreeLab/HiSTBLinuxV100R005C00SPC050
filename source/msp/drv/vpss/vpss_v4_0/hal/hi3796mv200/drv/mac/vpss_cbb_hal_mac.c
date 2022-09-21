//#include <linux/io.h>
//#include <linux/delay.h>
#include "vpss_cbb_common.h"
//#include "vpss_reg.h"

#if 1
HI_VOID VPSS_Mac_SetImgheight(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 imgheight)
{
    U_VPSS_IMGSIZE VPSS_IMGSIZE;

    VPSS_IMGSIZE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_IMGSIZE.u32));
    VPSS_IMGSIZE.bits.imgheight = imgheight - 1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_IMGSIZE.u32), VPSS_IMGSIZE.u32);

    return ;
}


HI_VOID VPSS_Mac_SetImgwidth(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 imgwidth)
{
    U_VPSS_IMGSIZE VPSS_IMGSIZE;

    VPSS_IMGSIZE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_IMGSIZE.u32));
    VPSS_IMGSIZE.bits.imgwidth = imgwidth - 1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_IMGSIZE.u32), VPSS_IMGSIZE.u32);

    return ;
}
HI_VOID VPSS_Mac_SetRefWidth(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 refwidth)
{
    U_VPSS_REFSIZE VPSS_REFSIZE;

    VPSS_REFSIZE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_REFSIZE.u32));
    VPSS_REFSIZE.bits.refwidth = refwidth - 1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_REFSIZE.u32), VPSS_REFSIZE.u32);

    return ;
}

HI_VOID VPSS_Mac_SetRefHeight(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 refheight)
{
    U_VPSS_REFSIZE VPSS_REFSIZE;

    VPSS_REFSIZE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_REFSIZE.u32));
    VPSS_REFSIZE.bits.refheight = refheight - 1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_REFSIZE.u32), VPSS_REFSIZE.u32);

    return ;
}


HI_VOID VPSS_Mac_SetNx2yLbAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nx2y_lb_addr)
{
    U_VPSS_NX2Y_LB_ADDR VPSS_NX2Y_LB_ADDR;

    VPSS_NX2Y_LB_ADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_NX2Y_LB_ADDR.u32));
    VPSS_NX2Y_LB_ADDR.bits.nx2ylb_addr = nx2y_lb_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_NX2Y_LB_ADDR.u32), VPSS_NX2Y_LB_ADDR.u32);

    return ;
}



HI_VOID VPSS_Mac_SetNx2cLbAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nx2c_lb_addr)
{
    U_VPSS_NX2C_LB_ADDR VPSS_NX2C_LB_ADDR;

    VPSS_NX2C_LB_ADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_NX2C_LB_ADDR.u32));
    VPSS_NX2C_LB_ADDR.bits.nx2clb_addr = nx2c_lb_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_NX2C_LB_ADDR.u32), VPSS_NX2C_LB_ADDR.u32);

    return ;
}



HI_VOID VPSS_Mac_SetNx2LbStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nx2_lb_stride)
{
    U_VPSS_NX2_LB_STRIDE VPSS_NX2_LB_STRIDE;

    VPSS_NX2_LB_STRIDE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_NX2_LB_STRIDE.u32));
    VPSS_NX2_LB_STRIDE.bits.nx2lb_stride = nx2_lb_stride;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_NX2_LB_STRIDE.u32), VPSS_NX2_LB_STRIDE.u32);

    return ;
}



HI_VOID VPSS_Mac_SetTransSrcAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 trans_src_addr)
{
    U_VPSS_TRANS_SRC_ADDR VPSS_TRANS_SRC_ADDR;

    VPSS_TRANS_SRC_ADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TRANS_SRC_ADDR.u32));
    VPSS_TRANS_SRC_ADDR.bits.trans_src_addr = trans_src_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TRANS_SRC_ADDR.u32), VPSS_TRANS_SRC_ADDR.u32);

    return ;
}



HI_VOID VPSS_Mac_SetTransDesAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 trans_des_addr)
{
    U_VPSS_TRANS_DES_ADDR VPSS_TRANS_DES_ADDR;

    VPSS_TRANS_DES_ADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TRANS_DES_ADDR.u32));
    VPSS_TRANS_DES_ADDR.bits.trans_des_addr = trans_des_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TRANS_DES_ADDR.u32), VPSS_TRANS_DES_ADDR.u32);

    return ;
}



HI_VOID VPSS_Mac_SetTransEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 trans_en)
{
    U_VPSS_TRANS_INFO VPSS_TRANS_INFO;

    VPSS_TRANS_INFO.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TRANS_INFO.u32));
    VPSS_TRANS_INFO.bits.trans_en = trans_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TRANS_INFO.u32), VPSS_TRANS_INFO.u32);

    return ;
}


HI_VOID VPSS_Mac_SetTransSize(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 trans_size)
{
    U_VPSS_TRANS_INFO VPSS_TRANS_INFO;

    VPSS_TRANS_INFO.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TRANS_INFO.u32));
    VPSS_TRANS_INFO.bits.trans_size = trans_size;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TRANS_INFO.u32), VPSS_TRANS_INFO.u32);

    return ;
}



HI_VOID VPSS_Mac_SetNx2yTopHeadAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nx2y_top_head_addr)
{
    U_VPSS_NX2Y_HEAD_ADDR VPSS_NX2Y_HEAD_ADDR;

    VPSS_NX2Y_HEAD_ADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_NX2Y_HEAD_ADDR.u32));
    VPSS_NX2Y_HEAD_ADDR.bits.nx2y_top_head_addr = nx2y_top_head_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_NX2Y_HEAD_ADDR.u32), VPSS_NX2Y_HEAD_ADDR.u32);

    return ;
}



HI_VOID VPSS_Mac_SetNx2yBotHeadAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nx2y_bot_head_addr)
{
    U_VPSS_NX2Y_BOT_HEAD_ADDR VPSS_NX2Y_BOT_HEAD_ADDR;

    VPSS_NX2Y_BOT_HEAD_ADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_NX2Y_BOT_HEAD_ADDR.u32));
    VPSS_NX2Y_BOT_HEAD_ADDR.bits.nx2y_bot_head_addr = nx2y_bot_head_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_NX2Y_BOT_HEAD_ADDR.u32), VPSS_NX2Y_BOT_HEAD_ADDR.u32);

    return ;
}



HI_VOID VPSS_Mac_SetNx2cTopHeadAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nx2c_top_head_addr)
{
    U_VPSS_NX2C_HEAD_ADDR VPSS_NX2C_HEAD_ADDR;

    VPSS_NX2C_HEAD_ADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_NX2C_HEAD_ADDR.u32));
    VPSS_NX2C_HEAD_ADDR.bits.nx2c_top_head_addr = nx2c_top_head_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_NX2C_HEAD_ADDR.u32), VPSS_NX2C_HEAD_ADDR.u32);

    return ;
}



HI_VOID VPSS_Mac_SetNx2cBotHeadAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nx2c_bot_head_addr)
{
    U_VPSS_NX2C_BOT_HEAD_ADDR VPSS_NX2C_BOT_HEAD_ADDR;

    VPSS_NX2C_BOT_HEAD_ADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_NX2C_BOT_HEAD_ADDR.u32));
    VPSS_NX2C_BOT_HEAD_ADDR.bits.nx2c_bot_head_addr = nx2c_bot_head_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_NX2C_BOT_HEAD_ADDR.u32), VPSS_NX2C_BOT_HEAD_ADDR.u32);

    return ;
}



HI_VOID VPSS_Mac_SetNx2HeadStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nx2_head_stride)
{
    U_VPSS_NX2_HEAD_STRIDE VPSS_NX2_HEAD_STRIDE;

    VPSS_NX2_HEAD_STRIDE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_NX2_HEAD_STRIDE.u32));
    VPSS_NX2_HEAD_STRIDE.bits.nx2_head_stride = nx2_head_stride;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_NX2_HEAD_STRIDE.u32), VPSS_NX2_HEAD_STRIDE.u32);

    return ;
}



HI_VOID VPSS_Mac_SetNodeid(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nodeid)
{
    U_VPSS_NODEID VPSS_NODEID;

    VPSS_NODEID.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_NODEID.u32));
    VPSS_NODEID.bits.nodeid = nodeid;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_NODEID.u32), VPSS_NODEID.u32);

    return ;
}



HI_VOID VPSS_Mac_SetCurVerOffset(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cur_ver_offset)
{
    U_VPSS_CUR_CTRL VPSS_CUR_CTRL;

    VPSS_CUR_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CUR_CTRL.u32));
    VPSS_CUR_CTRL.bits.cur_ver_offset = cur_ver_offset;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CUR_CTRL.u32), VPSS_CUR_CTRL.u32);

    return ;
}


HI_VOID VPSS_Mac_SetCurHorOffset(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cur_hor_offset)
{
    U_VPSS_CUR_CTRL VPSS_CUR_CTRL;

    VPSS_CUR_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CUR_CTRL.u32));
    VPSS_CUR_CTRL.bits.cur_hor_offset = cur_hor_offset;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CUR_CTRL.u32), VPSS_CUR_CTRL.u32);

    return ;
}


HI_VOID VPSS_Mac_SetCurTileFormat(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cur_tile_format)
{
    U_VPSS_CUR_CTRL VPSS_CUR_CTRL;

    VPSS_CUR_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CUR_CTRL.u32));
    VPSS_CUR_CTRL.bits.cur_tile_format = cur_tile_format;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CUR_CTRL.u32), VPSS_CUR_CTRL.u32);

    return ;
}



HI_VOID VPSS_Mac_SetCuryAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cury_addr)
{
    U_VPSS_CURYADDR VPSS_CURYADDR;

    VPSS_CURYADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CURYADDR.u32));
    VPSS_CURYADDR.bits.cury_addr = cury_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CURYADDR.u32), VPSS_CURYADDR.u32);

    return ;
}



HI_VOID VPSS_Mac_SetCurcAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 curc_addr)
{
    U_VPSS_CURCADDR VPSS_CURCADDR;

    VPSS_CURCADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CURCADDR.u32));
    VPSS_CURCADDR.bits.curc_addr = curc_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CURCADDR.u32), VPSS_CURCADDR.u32);

    return ;
}



HI_VOID VPSS_Mac_SetCurcStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 curc_stride)
{
    U_VPSS_CURSTRIDE VPSS_CURSTRIDE;

    VPSS_CURSTRIDE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CURSTRIDE.u32));
    VPSS_CURSTRIDE.bits.curc_stride = curc_stride;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CURSTRIDE.u32), VPSS_CURSTRIDE.u32);

    return ;
}


HI_VOID VPSS_Mac_SetCuryStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cury_stride)
{
    U_VPSS_CURSTRIDE VPSS_CURSTRIDE;

    VPSS_CURSTRIDE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CURSTRIDE.u32));
    VPSS_CURSTRIDE.bits.cury_stride = cury_stride;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CURSTRIDE.u32), VPSS_CURSTRIDE.u32);

    return ;
}



HI_VOID VPSS_Mac_SetRefVerOffset(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ref_ver_offset)
{
    U_VPSS_REF_CTRL VPSS_REF_CTRL;

    VPSS_REF_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_REF_CTRL.u32));
    VPSS_REF_CTRL.bits.ref_ver_offset = ref_ver_offset;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_REF_CTRL.u32), VPSS_REF_CTRL.u32);

    return ;
}


HI_VOID VPSS_Mac_SetRefHorOffset(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ref_hor_offset)
{
    U_VPSS_REF_CTRL VPSS_REF_CTRL;

    VPSS_REF_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_REF_CTRL.u32));
    VPSS_REF_CTRL.bits.ref_hor_offset = ref_hor_offset;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_REF_CTRL.u32), VPSS_REF_CTRL.u32);

    return ;
}


HI_VOID VPSS_Mac_SetRefTileFormat(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ref_tile_format)
{
    U_VPSS_REF_CTRL VPSS_REF_CTRL;

    VPSS_REF_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_REF_CTRL.u32));
    VPSS_REF_CTRL.bits.ref_tile_format = ref_tile_format;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_REF_CTRL.u32), VPSS_REF_CTRL.u32);

    return ;
}



HI_VOID VPSS_Mac_SetRefyAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 refy_addr)
{
    U_VPSS_REFYADDR VPSS_REFYADDR;

    VPSS_REFYADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_REFYADDR.u32));
    VPSS_REFYADDR.bits.refy_addr = refy_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_REFYADDR.u32), VPSS_REFYADDR.u32);

    return ;
}



HI_VOID VPSS_Mac_SetRefcAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 refc_addr)
{
    U_VPSS_REFCADDR VPSS_REFCADDR;

    VPSS_REFCADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_REFCADDR.u32));
    VPSS_REFCADDR.bits.refc_addr = refc_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_REFCADDR.u32), VPSS_REFCADDR.u32);

    return ;
}



HI_VOID VPSS_Mac_SetRefcStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 refc_stride)
{
    U_VPSS_REFSTRIDE VPSS_REFSTRIDE;

    VPSS_REFSTRIDE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_REFSTRIDE.u32));
    VPSS_REFSTRIDE.bits.refc_stride = refc_stride;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_REFSTRIDE.u32), VPSS_REFSTRIDE.u32);

    return ;
}


HI_VOID VPSS_Mac_SetRefyStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 refy_stride)
{
    U_VPSS_REFSTRIDE VPSS_REFSTRIDE;

    VPSS_REFSTRIDE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_REFSTRIDE.u32));
    VPSS_REFSTRIDE.bits.refy_stride = refy_stride;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_REFSTRIDE.u32), VPSS_REFSTRIDE.u32);

    return ;
}



HI_VOID VPSS_Mac_SetNxt1VerOffset(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nxt1_ver_offset)
{
    U_VPSS_NXT1_CTRL VPSS_NXT1_CTRL;

    VPSS_NXT1_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_NXT1_CTRL.u32));
    VPSS_NXT1_CTRL.bits.nxt1_ver_offset = nxt1_ver_offset;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_NXT1_CTRL.u32), VPSS_NXT1_CTRL.u32);

    return ;
}


HI_VOID VPSS_Mac_SetNxt1HorOffset(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nxt1_hor_offset)
{
    U_VPSS_NXT1_CTRL VPSS_NXT1_CTRL;

    VPSS_NXT1_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_NXT1_CTRL.u32));
    VPSS_NXT1_CTRL.bits.nxt1_hor_offset = nxt1_hor_offset;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_NXT1_CTRL.u32), VPSS_NXT1_CTRL.u32);

    return ;
}


HI_VOID VPSS_Mac_SetNxt1TileFormat(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nxt1_tile_format)
{
    U_VPSS_NXT1_CTRL VPSS_NXT1_CTRL;

    VPSS_NXT1_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_NXT1_CTRL.u32));
    VPSS_NXT1_CTRL.bits.nxt1_tile_format = nxt1_tile_format;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_NXT1_CTRL.u32), VPSS_NXT1_CTRL.u32);

    return ;
}



HI_VOID VPSS_Mac_SetNxt1yAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nxt1y_addr)
{
    U_VPSS_NXT1YADDR VPSS_NXT1YADDR;

    VPSS_NXT1YADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_NXT1YADDR.u32));
    VPSS_NXT1YADDR.bits.nxt1y_addr = nxt1y_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_NXT1YADDR.u32), VPSS_NXT1YADDR.u32);

    return ;
}



HI_VOID VPSS_Mac_SetNxt1cAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nxt1c_addr)
{
    U_VPSS_NXT1CADDR VPSS_NXT1CADDR;

    VPSS_NXT1CADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_NXT1CADDR.u32));
    VPSS_NXT1CADDR.bits.nxt1c_addr = nxt1c_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_NXT1CADDR.u32), VPSS_NXT1CADDR.u32);

    return ;
}



HI_VOID VPSS_Mac_SetNxt1cStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nxt1c_stride)
{
    U_VPSS_NXT1STRIDE VPSS_NXT1STRIDE;

    VPSS_NXT1STRIDE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_NXT1STRIDE.u32));
    VPSS_NXT1STRIDE.bits.nxt1c_stride = nxt1c_stride;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_NXT1STRIDE.u32), VPSS_NXT1STRIDE.u32);

    return ;
}


HI_VOID VPSS_Mac_SetNxt1yStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nxt1y_stride)
{
    U_VPSS_NXT1STRIDE VPSS_NXT1STRIDE;

    VPSS_NXT1STRIDE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_NXT1STRIDE.u32));
    VPSS_NXT1STRIDE.bits.nxt1y_stride = nxt1y_stride;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_NXT1STRIDE.u32), VPSS_NXT1STRIDE.u32);

    return ;
}



HI_VOID VPSS_Mac_SetNxt2DcmpEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nxt2_dcmp_en)
{
    U_VPSS_NXT2_CTRL VPSS_NXT2_CTRL;

    VPSS_NXT2_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_NXT2_CTRL.u32));
    VPSS_NXT2_CTRL.bits.nxt2_dcmp_en = nxt2_dcmp_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_NXT2_CTRL.u32), VPSS_NXT2_CTRL.u32);

    return ;
}


HI_VOID VPSS_Mac_SetNxt2VerOffset(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nxt2_ver_offset)
{
    U_VPSS_NXT2_CTRL VPSS_NXT2_CTRL;

    VPSS_NXT2_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_NXT2_CTRL.u32));
    VPSS_NXT2_CTRL.bits.nxt2_ver_offset = nxt2_ver_offset;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_NXT2_CTRL.u32), VPSS_NXT2_CTRL.u32);

    return ;
}


HI_VOID VPSS_Mac_SetNxt2HorOffset(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nxt2_hor_offset)
{
    U_VPSS_NXT2_CTRL VPSS_NXT2_CTRL;

    VPSS_NXT2_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_NXT2_CTRL.u32));
    VPSS_NXT2_CTRL.bits.nxt2_hor_offset = nxt2_hor_offset;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_NXT2_CTRL.u32), VPSS_NXT2_CTRL.u32);

    return ;
}


HI_VOID VPSS_Mac_SetNxt2TileFormat(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nxt2_tile_format)
{
    U_VPSS_NXT2_CTRL VPSS_NXT2_CTRL;

    VPSS_NXT2_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_NXT2_CTRL.u32));
    VPSS_NXT2_CTRL.bits.nxt2_tile_format = nxt2_tile_format;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_NXT2_CTRL.u32), VPSS_NXT2_CTRL.u32);

    return ;
}

HI_VOID VPSS_Mac_SetNxt2TileSpecField(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nxt2_tile_spec_field)
{
    U_VPSS_NXT2_CTRL VPSS_NXT2_CTRL;

    VPSS_NXT2_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_NXT2_CTRL.u32));
    VPSS_NXT2_CTRL.bits.nxt2_tile_spec_field = nxt2_tile_spec_field;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_NXT2_CTRL.u32), VPSS_NXT2_CTRL.u32);

    return ;
}



HI_VOID VPSS_Mac_SetNxt2yAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nxt2y_addr)
{
    U_VPSS_NXT2YADDR VPSS_NXT2YADDR;

    VPSS_NXT2YADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_NXT2YADDR.u32));
    VPSS_NXT2YADDR.bits.nxt2y_addr = nxt2y_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_NXT2YADDR.u32), VPSS_NXT2YADDR.u32);

    return ;
}



HI_VOID VPSS_Mac_SetNxt2cAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nxt2c_addr)
{
    U_VPSS_NXT2CADDR VPSS_NXT2CADDR;

    VPSS_NXT2CADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_NXT2CADDR.u32));
    VPSS_NXT2CADDR.bits.nxt2c_addr = nxt2c_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_NXT2CADDR.u32), VPSS_NXT2CADDR.u32);

    return ;
}



HI_VOID VPSS_Mac_SetNxt2cStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nxt2c_stride)
{
    U_VPSS_NXT2STRIDE VPSS_NXT2STRIDE;

    VPSS_NXT2STRIDE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_NXT2STRIDE.u32));
    VPSS_NXT2STRIDE.bits.nxt2c_stride = nxt2c_stride;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_NXT2STRIDE.u32), VPSS_NXT2STRIDE.u32);

    return ;
}


HI_VOID VPSS_Mac_SetNxt2yStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nxt2y_stride)
{
    U_VPSS_NXT2STRIDE VPSS_NXT2STRIDE;

    VPSS_NXT2STRIDE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_NXT2STRIDE.u32));
    VPSS_NXT2STRIDE.bits.nxt2y_stride = nxt2y_stride;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_NXT2STRIDE.u32), VPSS_NXT2STRIDE.u32);

    return ;
}



HI_VOID VPSS_Mac_SetRfrDitherMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rfr_dither_mode)
{
    U_VPSS_RFRCTRL VPSS_RFRCTRL;

    VPSS_RFRCTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RFRCTRL.u32));
    VPSS_RFRCTRL.bits.rfr_dither_mode = rfr_dither_mode;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RFRCTRL.u32), VPSS_RFRCTRL.u32);

    return ;
}


HI_VOID VPSS_Mac_SetRfrDitherEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rfr_dither_en)
{
    U_VPSS_RFRCTRL VPSS_RFRCTRL;

    VPSS_RFRCTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RFRCTRL.u32));
    VPSS_RFRCTRL.bits.rfr_dither_en = rfr_dither_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RFRCTRL.u32), VPSS_RFRCTRL.u32);

    return ;
}



HI_VOID VPSS_Mac_SetRfryAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rfry_addr)
{
    U_VPSS_RFRYADDR VPSS_RFRYADDR;

    VPSS_RFRYADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RFRYADDR.u32));
    VPSS_RFRYADDR.bits.rfry_addr = rfry_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RFRYADDR.u32), VPSS_RFRYADDR.u32);

    return ;
}



HI_VOID VPSS_Mac_SetRfrcAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rfrc_addr)
{
    U_VPSS_RFRCADDR VPSS_RFRCADDR;

    VPSS_RFRCADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RFRCADDR.u32));
    VPSS_RFRCADDR.bits.rfrc_addr = rfrc_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RFRCADDR.u32), VPSS_RFRCADDR.u32);

    return ;
}



HI_VOID VPSS_Mac_SetRfrcStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rfrc_stride)
{
    U_VPSS_RFRSTRIDE VPSS_RFRSTRIDE;

    VPSS_RFRSTRIDE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RFRSTRIDE.u32));
    VPSS_RFRSTRIDE.bits.rfrc_stride = rfrc_stride;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RFRSTRIDE.u32), VPSS_RFRSTRIDE.u32);

    return ;
}


HI_VOID VPSS_Mac_SetRfryStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rfry_stride)
{
    U_VPSS_RFRSTRIDE VPSS_RFRSTRIDE;

    VPSS_RFRSTRIDE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RFRSTRIDE.u32));
    VPSS_RFRSTRIDE.bits.rfry_stride = rfry_stride;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RFRSTRIDE.u32), VPSS_RFRSTRIDE.u32);

    return ;
}



HI_VOID VPSS_Mac_SetVhd0DitherMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vhd0_dither_mode)
{
    U_VPSS_VHD0CTRL VPSS_VHD0CTRL;

    VPSS_VHD0CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_VHD0CTRL.u32));
    VPSS_VHD0CTRL.bits.vhd0_dither_mode = vhd0_dither_mode;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_VHD0CTRL.u32), VPSS_VHD0CTRL.u32);

    return ;
}


HI_VOID VPSS_Mac_SetVhd0LcmpEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vhd0_lcmp_en)
{
    U_VPSS_VHD0CTRL VPSS_VHD0CTRL;

    VPSS_VHD0CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_VHD0CTRL.u32));
    VPSS_VHD0CTRL.bits.vhd0_lcmp_en = vhd0_lcmp_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_VHD0CTRL.u32), VPSS_VHD0CTRL.u32);

    return ;
}


HI_VOID VPSS_Mac_SetVhd0UvInvert(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vhd0_uv_invert)
{
    U_VPSS_VHD0CTRL VPSS_VHD0CTRL;

    VPSS_VHD0CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_VHD0CTRL.u32));
    VPSS_VHD0CTRL.bits.vhd0_uv_invert = vhd0_uv_invert;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_VHD0CTRL.u32), VPSS_VHD0CTRL.u32);

    return ;
}


HI_VOID VPSS_Mac_SetVhd0DitherEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vhd0_dither_en)
{
    U_VPSS_VHD0CTRL VPSS_VHD0CTRL;

    VPSS_VHD0CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_VHD0CTRL.u32));
    VPSS_VHD0CTRL.bits.vhd0_dither_en = vhd0_dither_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_VHD0CTRL.u32), VPSS_VHD0CTRL.u32);

    return ;
}


HI_VOID VPSS_Mac_SetVhd0PixBitw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vhd0_pix_bitw)
{
    U_VPSS_VHD0CTRL VPSS_VHD0CTRL;

    VPSS_VHD0CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_VHD0CTRL.u32));
    VPSS_VHD0CTRL.bits.vhd0_pix_bitw = vhd0_pix_bitw;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_VHD0CTRL.u32), VPSS_VHD0CTRL.u32);

    return ;
}


HI_VOID VPSS_Mac_SetVhd0Flip(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vhd0_flip)
{
    U_VPSS_VHD0CTRL VPSS_VHD0CTRL;

    VPSS_VHD0CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_VHD0CTRL.u32));
    VPSS_VHD0CTRL.bits.vhd0_flip = vhd0_flip;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_VHD0CTRL.u32), VPSS_VHD0CTRL.u32);

    return ;
}


HI_VOID VPSS_Mac_SetVhd0Mirror(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vhd0_mirror)
{
    U_VPSS_VHD0CTRL VPSS_VHD0CTRL;

    VPSS_VHD0CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_VHD0CTRL.u32));
    VPSS_VHD0CTRL.bits.vhd0_mirror = vhd0_mirror;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_VHD0CTRL.u32), VPSS_VHD0CTRL.u32);

    return ;
}



HI_VOID VPSS_Mac_SetVhd0Height(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vhd0_height)
{
    U_VPSS_VHD0SIZE VPSS_VHD0SIZE;

    VPSS_VHD0SIZE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_VHD0SIZE.u32));
    VPSS_VHD0SIZE.bits.vhd0_height = vhd0_height - 1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_VHD0SIZE.u32), VPSS_VHD0SIZE.u32);

    return ;
}


HI_VOID VPSS_Mac_SetVhd0Width(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vhd0_width)
{
    U_VPSS_VHD0SIZE VPSS_VHD0SIZE;

    VPSS_VHD0SIZE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_VHD0SIZE.u32));
    VPSS_VHD0SIZE.bits.vhd0_width = vhd0_width - 1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_VHD0SIZE.u32), VPSS_VHD0SIZE.u32);

    return ;
}



HI_VOID VPSS_Mac_SetVhd0yAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vhd0y_addr)
{
    U_VPSS_VHD0YADDR VPSS_VHD0YADDR;

    VPSS_VHD0YADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_VHD0YADDR.u32));
    VPSS_VHD0YADDR.bits.vhd0y_addr = vhd0y_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_VHD0YADDR.u32), VPSS_VHD0YADDR.u32);

    return ;
}



HI_VOID VPSS_Mac_SetVhd0cAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vhd0c_addr)
{
    U_VPSS_VHD0CADDR VPSS_VHD0CADDR;

    VPSS_VHD0CADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_VHD0CADDR.u32));
    VPSS_VHD0CADDR.bits.vhd0c_addr = vhd0c_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_VHD0CADDR.u32), VPSS_VHD0CADDR.u32);

    return ;
}



HI_VOID VPSS_Mac_SetVhd0cStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vhd0c_stride)
{
    U_VPSS_VHD0STRIDE VPSS_VHD0STRIDE;

    VPSS_VHD0STRIDE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_VHD0STRIDE.u32));
    VPSS_VHD0STRIDE.bits.vhd0c_stride = vhd0c_stride;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_VHD0STRIDE.u32), VPSS_VHD0STRIDE.u32);

    return ;
}


HI_VOID VPSS_Mac_SetVhd0yStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vhd0y_stride)
{
    U_VPSS_VHD0STRIDE VPSS_VHD0STRIDE;

    VPSS_VHD0STRIDE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_VHD0STRIDE.u32));
    VPSS_VHD0STRIDE.bits.vhd0y_stride = vhd0y_stride;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_VHD0STRIDE.u32), VPSS_VHD0STRIDE.u32);

    return ;
}

HI_VOID VPSS_Mac_SetStRaddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 st_raddr)
{
    U_VPSS_STRADDR VPSS_STRADDR;

    VPSS_STRADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_STRADDR.u32));
    VPSS_STRADDR.bits.st_raddr = st_raddr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_STRADDR.u32), VPSS_STRADDR.u32);

    return ;
}



HI_VOID VPSS_Mac_SetStWaddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 st_waddr)
{
    U_VPSS_STWADDR VPSS_STWADDR;

    VPSS_STWADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_STWADDR.u32));
    VPSS_STWADDR.bits.st_waddr = st_waddr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_STWADDR.u32), VPSS_STWADDR.u32);

    return ;
}



HI_VOID VPSS_Mac_SetStStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 st_stride)
{
    U_VPSS_STSTRIDE VPSS_STSTRIDE;

    VPSS_STSTRIDE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_STSTRIDE.u32));
    VPSS_STSTRIDE.bits.st_stride = st_stride;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_STSTRIDE.u32), VPSS_STSTRIDE.u32);

    return ;
}



HI_VOID VPSS_Mac_SetSttWAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 stt_w_addr)
{
    U_VPSS_STT_W_ADDR VPSS_STT_W_ADDR;

    VPSS_STT_W_ADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_STT_W_ADDR.u32));
    VPSS_STT_W_ADDR.bits.stt_w_addr = stt_w_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_STT_W_ADDR.u32), VPSS_STT_W_ADDR.u32);

    return ;
}



HI_VOID VPSS_Mac_SetNx2TunlEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nx2_tunl_en)
{
    U_VPSS_NX2_TUNL_CTRL VPSS_NX2_TUNL_CTRL;

    VPSS_NX2_TUNL_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_NX2_TUNL_CTRL.u32));
    VPSS_NX2_TUNL_CTRL.bits.nx2_tunl_en = nx2_tunl_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_NX2_TUNL_CTRL.u32), VPSS_NX2_TUNL_CTRL.u32);

    return ;
}



HI_VOID VPSS_Mac_SetNx2TunlRdInterval(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nx2_tunl_rd_interval)
{
    U_VPSS_NX2_TUNL_CTRL VPSS_NX2_TUNL_CTRL;

    VPSS_NX2_TUNL_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_NX2_TUNL_CTRL.u32));
    VPSS_NX2_TUNL_CTRL.bits.nx2_tunl_rd_interval = nx2_tunl_rd_interval;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_NX2_TUNL_CTRL.u32), VPSS_NX2_TUNL_CTRL.u32);

    return ;
}



HI_VOID VPSS_Mac_SetNx2TunlAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nx2_tunl_addr)
{
    U_VPSS_NX2_TUNL_ADDR VPSS_NX2_TUNL_ADDR;

    VPSS_NX2_TUNL_ADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_NX2_TUNL_ADDR.u32));
    VPSS_NX2_TUNL_ADDR.bits.nx2_tunl_addr = nx2_tunl_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_NX2_TUNL_ADDR.u32), VPSS_NX2_TUNL_ADDR.u32);

    return ;
}


HI_VOID VPSS_Mac_SetVhd0TunlEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vhd0_tunl_en)
{
    U_VPSS_VHD0_TUNL_CTRL VPSS_VHD0_TUNL_CTRL;

    VPSS_VHD0_TUNL_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_VHD0_TUNL_CTRL.u32));
    VPSS_VHD0_TUNL_CTRL.bits.vhd0_tunl_en = vhd0_tunl_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_VHD0_TUNL_CTRL.u32), VPSS_VHD0_TUNL_CTRL.u32);

    return ;
}



HI_VOID VPSS_Mac_SetVhd0TunlMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vhd0_tunl_mode)
{
    U_VPSS_VHD0_TUNL_CTRL VPSS_VHD0_TUNL_CTRL;

    VPSS_VHD0_TUNL_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_VHD0_TUNL_CTRL.u32));
    VPSS_VHD0_TUNL_CTRL.bits.vhd0_tunl_mode = vhd0_tunl_mode;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_VHD0_TUNL_CTRL.u32), VPSS_VHD0_TUNL_CTRL.u32);

    return ;
}

HI_VOID VPSS_Mac_SetVhd0TunlFinishLine(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vhd0_tunl_finish_line)
{
    U_VPSS_VHD0_TUNL_CTRL VPSS_VHD0_TUNL_CTRL;

    VPSS_VHD0_TUNL_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_VHD0_TUNL_CTRL.u32));
    VPSS_VHD0_TUNL_CTRL.bits.vhd0_tunl_finish_line = vhd0_tunl_finish_line;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_VHD0_TUNL_CTRL.u32), VPSS_VHD0_TUNL_CTRL.u32);

    return ;
}


HI_VOID VPSS_Mac_SetVhd0TunlAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vhd0_tunl_addr)
{
    U_VPSS_VHD0_TUNL_ADDR VPSS_VHD0_TUNL_ADDR;

    VPSS_VHD0_TUNL_ADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_VHD0_TUNL_ADDR.u32));
    VPSS_VHD0_TUNL_ADDR.bits.vhd0_tunl_addr = vhd0_tunl_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_VHD0_TUNL_ADDR.u32), VPSS_VHD0_TUNL_ADDR.u32);

    return ;
}


HI_VOID VPSS_Mac_SetDiCntSize(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 di_cnt_width, HI_U32 di_cnt_height)
{
    U_VPSS_DICNT_SIZE VPSS_DICNT_SIZE;

    VPSS_DICNT_SIZE.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DICNT_SIZE.u32));
    VPSS_DICNT_SIZE.bits.di_cnt_width  = di_cnt_width - 1;
    VPSS_DICNT_SIZE.bits.di_cnt_height = di_cnt_height - 1;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DICNT_SIZE.u32), VPSS_DICNT_SIZE.u32);

    return ;
}


HI_VOID VPSS_Mac_SetDiRcntAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 di_rcnt_addr)
{
    U_VPSS_DIRCNT_ADDR VPSS_DIRCNT_ADDR;

    VPSS_DIRCNT_ADDR.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIRCNT_ADDR.u32));
    VPSS_DIRCNT_ADDR.bits.di_rcnt_addr = di_rcnt_addr;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIRCNT_ADDR.u32), VPSS_DIRCNT_ADDR.u32);

    return ;
}

HI_VOID VPSS_Mac_SetDiWcntAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 di_wcnt_addr)
{
    U_VPSS_DIWCNT_ADDR VPSS_DIWCNT_ADDR;

    VPSS_DIWCNT_ADDR.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIWCNT_ADDR.u32));
    VPSS_DIWCNT_ADDR.bits.di_wcnt_addr = di_wcnt_addr;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIWCNT_ADDR.u32), VPSS_DIWCNT_ADDR.u32);

    return ;
}

HI_VOID VPSS_Mac_SetDiCntStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 di_rcnt_stride , HI_U32 di_wcnt_stride)
{
    U_VPSS_DICNT_STRIDE VPSS_DICNT_STRIDE;

    VPSS_DICNT_STRIDE.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DICNT_STRIDE.u32));
    VPSS_DICNT_STRIDE.bits.di_rcnt_stride = di_rcnt_stride;
    VPSS_DICNT_STRIDE.bits.di_wcnt_stride = di_wcnt_stride;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DICNT_STRIDE.u32), VPSS_DICNT_STRIDE.u32);

    return ;
}

HI_VOID VPSS_Mac_SetReeyAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 reey_addr)
{
    U_VPSS_REEYADDR VPSS_REEYADDR;

    VPSS_REEYADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_REEYADDR.u32));
    VPSS_REEYADDR.bits.reey_addr = reey_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_REEYADDR.u32), VPSS_REEYADDR.u32);

    return ;
}



HI_VOID VPSS_Mac_SetReecAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 reec_addr)
{
    U_VPSS_REECADDR VPSS_REECADDR;

    VPSS_REECADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_REECADDR.u32));
    VPSS_REECADDR.bits.reec_addr = reec_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_REECADDR.u32), VPSS_REECADDR.u32);

    return ;
}



HI_VOID VPSS_Mac_SetReecStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 reec_stride)
{
    U_VPSS_REESTRIDE VPSS_REESTRIDE;

    VPSS_REESTRIDE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_REESTRIDE.u32));
    VPSS_REESTRIDE.bits.reec_stride = reec_stride;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_REESTRIDE.u32), VPSS_REESTRIDE.u32);

    return ;
}


HI_VOID VPSS_Mac_SetReeyStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 reey_stride)
{
    U_VPSS_REESTRIDE VPSS_REESTRIDE;

    VPSS_REESTRIDE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_REESTRIDE.u32));
    VPSS_REESTRIDE.bits.reey_stride = reey_stride;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_REESTRIDE.u32), VPSS_REESTRIDE.u32);

    return ;
}

HI_VOID VPSS_Mac_SetCueyAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cuey_addr)
{
    U_VPSS_CUEYADDR VPSS_CUEYADDR;

    VPSS_CUEYADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CUEYADDR.u32));
    VPSS_CUEYADDR.bits.cuey_addr = cuey_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CUEYADDR.u32), VPSS_CUEYADDR.u32);

    return ;
}



HI_VOID VPSS_Mac_SetCuecAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cuec_addr)
{
    U_VPSS_CUECADDR VPSS_CUECADDR;

    VPSS_CUECADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CUECADDR.u32));
    VPSS_CUECADDR.bits.cuec_addr = cuec_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CUECADDR.u32), VPSS_CUECADDR.u32);

    return ;
}



HI_VOID VPSS_Mac_SetCuecStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cuec_stride)
{
    U_VPSS_CUESTRIDE VPSS_CUESTRIDE;

    VPSS_CUESTRIDE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CUESTRIDE.u32));
    VPSS_CUESTRIDE.bits.cuec_stride = cuec_stride;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CUESTRIDE.u32), VPSS_CUESTRIDE.u32);

    return ;
}


HI_VOID VPSS_Mac_SetCueyStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cuey_stride)
{
    U_VPSS_CUESTRIDE VPSS_CUESTRIDE;

    VPSS_CUESTRIDE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CUESTRIDE.u32));
    VPSS_CUESTRIDE.bits.cuey_stride = cuey_stride;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CUESTRIDE.u32), VPSS_CUESTRIDE.u32);

    return ;
}

HI_VOID VPSS_Mac_SetRgmvCurAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rgmv_cur_addr)
{
    U_VPSS_RGMVCURADDR VPSS_RGMVCURADDR;

    VPSS_RGMVCURADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RGMVCURADDR.u32));
    VPSS_RGMVCURADDR.bits.rgmv_cur_addr = rgmv_cur_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RGMVCURADDR.u32), VPSS_RGMVCURADDR.u32);

    return ;
}


HI_VOID VPSS_Mac_SetRgmvNx1Addr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rgmv_nx1_addr)
{
    U_VPSS_RGMVNX1ADDR VPSS_RGMVNX1ADDR;

    VPSS_RGMVNX1ADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RGMVNX1ADDR.u32));
    VPSS_RGMVNX1ADDR.bits.rgmv_nx1_addr = rgmv_nx1_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RGMVNX1ADDR.u32), VPSS_RGMVNX1ADDR.u32);

    return ;
}

HI_VOID VPSS_Mac_SetRgmvNx2Addr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rgmv_nx2_addr)
{
    U_VPSS_RGMVNX2ADDR VPSS_RGMVNX2ADDR;

    VPSS_RGMVNX2ADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RGMVNX2ADDR.u32));
    VPSS_RGMVNX2ADDR.bits.rgmv_nx2_addr = rgmv_nx2_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RGMVNX2ADDR.u32), VPSS_RGMVNX2ADDR.u32);

    return ;
}


HI_VOID VPSS_Mac_SetRgmvNx1Stride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rgmv_nx1_stride)
{
    U_VPSS_RGMVSTRIDE VPSS_RGMVSTRIDE;

    VPSS_RGMVSTRIDE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RGMVSTRIDE.u32));
    VPSS_RGMVSTRIDE.bits.rgmv_nx1_stride = rgmv_nx1_stride;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RGMVSTRIDE.u32), VPSS_RGMVSTRIDE.u32);

    return ;
}

HI_VOID VPSS_Mac_SetRgmvNx2Stride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rgmv_nx2_stride)
{
    U_VPSS_RGMVNX2STRIDE VPSS_RGMVNX2STRIDE;

    VPSS_RGMVNX2STRIDE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RGMVNX2STRIDE.u32));
    VPSS_RGMVNX2STRIDE.bits.rgmv_nx2_stride = rgmv_nx2_stride;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RGMVNX2STRIDE.u32), VPSS_RGMVNX2STRIDE.u32);

    return ;
}


HI_VOID VPSS_Mac_SetRgmvCurStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rgmv_cur_stride)
{
    U_VPSS_RGMVSTRIDE VPSS_RGMVSTRIDE;

    VPSS_RGMVSTRIDE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RGMVSTRIDE.u32));
    VPSS_RGMVSTRIDE.bits.rgmv_cur_stride = rgmv_cur_stride;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RGMVSTRIDE.u32), VPSS_RGMVSTRIDE.u32);

    return ;
}


HI_VOID VPSS_Mac_SetMadRaddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mad_raddr)
{
    U_VPSS_MAD_RADDR VPSS_MAD_RADDR;

    VPSS_MAD_RADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_MAD_RADDR.u32));
    VPSS_MAD_RADDR.bits.mad_raddr = mad_raddr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_MAD_RADDR.u32), VPSS_MAD_RADDR.u32);

    return ;
}



HI_VOID VPSS_Mac_SetMadWaddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mad_waddr)
{
    U_VPSS_MAD_WADDR VPSS_MAD_WADDR;

    VPSS_MAD_WADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_MAD_WADDR.u32));
    VPSS_MAD_WADDR.bits.mad_waddr = mad_waddr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_MAD_WADDR.u32), VPSS_MAD_WADDR.u32);

    return ;
}



HI_VOID VPSS_Mac_SetSnrMadRaddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 snr_mad_raddr)
{
    U_VPSS_SNR_MAD_RADDR VPSS_SNR_MAD_RADDR;

    VPSS_SNR_MAD_RADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_MAD_RADDR.u32));
    VPSS_SNR_MAD_RADDR.bits.snr_mad_raddr = snr_mad_raddr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_MAD_RADDR.u32), VPSS_SNR_MAD_RADDR.u32);

    return ;
}



HI_VOID VPSS_Mac_SetMadStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mad_stride)
{
    U_VPSS_MADSTRIDE VPSS_MADSTRIDE;

    VPSS_MADSTRIDE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_MADSTRIDE.u32));
    VPSS_MADSTRIDE.bits.mad_stride = mad_stride;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_MADSTRIDE.u32), VPSS_MADSTRIDE.u32);

    return ;
}

HI_VOID VPSS_Mac_SetBlkmvRefAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 blkmv_ref_addr)
{
    U_VPSS_BLKMVREFADDR VPSS_BLKMVREFADDR;

    VPSS_BLKMVREFADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_BLKMVREFADDR.u32));
    VPSS_BLKMVREFADDR.bits.blkmv_ref_addr = blkmv_ref_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_BLKMVREFADDR.u32), VPSS_BLKMVREFADDR.u32);

    return ;
}


HI_VOID VPSS_Mac_SetBlkmvCurAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 blkmv_cur_addr)
{
    U_VPSS_BLKMVCURADDR VPSS_BLKMVCURADDR;

    VPSS_BLKMVCURADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_BLKMVCURADDR.u32));
    VPSS_BLKMVCURADDR.bits.blkmv_cur_addr = blkmv_cur_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_BLKMVCURADDR.u32), VPSS_BLKMVCURADDR.u32);

    return ;
}

HI_VOID VPSS_Mac_SetBlkmvNx1Addr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 blkmv_nx1_addr)
{
    U_VPSS_BLKMVNX1ADDR VPSS_BLKMVNX1ADDR;

    VPSS_BLKMVNX1ADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_BLKMVNX1ADDR.u32));
    VPSS_BLKMVNX1ADDR.bits.blkmv_nx1_addr = blkmv_nx1_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_BLKMVNX1ADDR.u32), VPSS_BLKMVNX1ADDR.u32);

    return ;
}



HI_VOID VPSS_Mac_SetBlkmvCurStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 blkmv_cur_stride)
{
    U_VPSS_BLKMVSTRIDE VPSS_BLKMVSTRIDE;

    VPSS_BLKMVSTRIDE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_BLKMVSTRIDE.u32));
    VPSS_BLKMVSTRIDE.bits.blkmv_cur_stride = blkmv_cur_stride;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_BLKMVSTRIDE.u32), VPSS_BLKMVSTRIDE.u32);

    return ;
}

HI_VOID VPSS_Mac_SetBlkmvRefStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 blkmv_ref_stride)
{
    U_VPSS_BLKMVSTRIDE VPSS_BLKMVSTRIDE;

    VPSS_BLKMVSTRIDE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_BLKMVSTRIDE.u32));
    VPSS_BLKMVSTRIDE.bits.blkmv_ref_stride = blkmv_ref_stride;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_BLKMVSTRIDE.u32), VPSS_BLKMVSTRIDE.u32);

    return ;
}

HI_VOID VPSS_Mac_SetBlkmvNx1Stride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 blkmv_nx1_stride)
{
    U_VPSS_BLKMVNX1STRIDE VPSS_BLKMVNX1STRIDE;

    VPSS_BLKMVNX1STRIDE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_BLKMVNX1STRIDE.u32));
    VPSS_BLKMVNX1STRIDE.bits.blkmv_nx1_stride = blkmv_nx1_stride;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_BLKMVNX1STRIDE.u32), VPSS_BLKMVNX1STRIDE.u32);

    return ;
}

HI_VOID VPSS_Mac_SetBlkmtRefAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 blkmt_ref_addr)
{
    U_VPSS_BLKMTREFADDR VPSS_BLKMTREFADDR;

    VPSS_BLKMTREFADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_BLKMTREFADDR.u32));
    VPSS_BLKMTREFADDR.bits.blkmt_ref_addr = blkmt_ref_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_BLKMTREFADDR.u32), VPSS_BLKMTREFADDR.u32);

    return ;
}

HI_VOID VPSS_Mac_SetBlkmtRefStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 blkmt_ref_stride)
{
    U_VPSS_BLKMTREFSTRIDE VPSS_BLKMTREFSTRIDE;

    VPSS_BLKMTREFSTRIDE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_BLKMTREFSTRIDE.u32));
    VPSS_BLKMTREFSTRIDE.bits.blkmt_ref_stride = blkmt_ref_stride;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_BLKMTREFSTRIDE.u32), VPSS_BLKMTREFSTRIDE.u32);

    return ;
}

HI_VOID VPSS_Mac_SetBlkmtCurAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 blkmt_cur_addr)
{
    U_VPSS_BLKMTCURADDR VPSS_BLKMTCURADDR;

    VPSS_BLKMTCURADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_BLKMTCURADDR.u32));
    VPSS_BLKMTCURADDR.bits.blkmt_cur_addr = blkmt_cur_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_BLKMTCURADDR.u32), VPSS_BLKMTCURADDR.u32);

    return ;
}

HI_VOID VPSS_Mac_SetBlkmtCurStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 blkmt_cur_stride)
{
    U_VPSS_BLKMTCURSTRIDE VPSS_BLKMTCURSTRIDE;

    VPSS_BLKMTCURSTRIDE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_BLKMTCURSTRIDE.u32));
    VPSS_BLKMTCURSTRIDE.bits.blkmt_cur_stride = blkmt_cur_stride;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_BLKMTCURSTRIDE.u32), VPSS_BLKMTCURSTRIDE.u32);

    return ;
}

HI_VOID VPSS_Mac_SetPrjvNx2Addr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 prjv_nx2_addr)
{
    U_VPSS_PRJVNX2ADDR VPSS_PRJVNX2ADDR;

    VPSS_PRJVNX2ADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_PRJVNX2ADDR.u32));
    VPSS_PRJVNX2ADDR.bits.prjv_nx2_addr = prjv_nx2_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_PRJVNX2ADDR.u32), VPSS_PRJVNX2ADDR.u32);

    return ;
}

HI_VOID VPSS_Mac_SetPrjhNx2Addr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 prjh_nx2_addr)
{
    U_VPSS_PRJHNX2ADDR VPSS_PRJHNX2ADDR;

    VPSS_PRJHNX2ADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_PRJHNX2ADDR.u32));
    VPSS_PRJHNX2ADDR.bits.prjh_nx2_addr = prjh_nx2_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_PRJHNX2ADDR.u32), VPSS_PRJHNX2ADDR.u32);

    return ;
}


HI_VOID VPSS_Mac_SetPrjvNx2Stride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 prjv_nx2_stride)
{
    U_VPSS_PRJNX2STRIDE VPSS_PRJNX2STRIDE;

    VPSS_PRJNX2STRIDE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_PRJNX2STRIDE.u32));
    VPSS_PRJNX2STRIDE.bits.prjv_nx2_stride = prjv_nx2_stride;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_PRJNX2STRIDE.u32), VPSS_PRJNX2STRIDE.u32);

    return ;
}

HI_VOID VPSS_Mac_SetPrjhNx2Stride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 prjh_nx2_stride)
{
    U_VPSS_PRJNX2STRIDE VPSS_PRJNX2STRIDE;

    VPSS_PRJNX2STRIDE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_PRJNX2STRIDE.u32));
    VPSS_PRJNX2STRIDE.bits.prjh_nx2_stride = prjh_nx2_stride;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_PRJNX2STRIDE.u32), VPSS_PRJNX2STRIDE.u32);

    return ;
}

HI_VOID VPSS_Mac_SetPrjvCurAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 prjv_cur_addr)
{
    U_VPSS_PRJVCURADDR VPSS_PRJVCURADDR;

    VPSS_PRJVCURADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_PRJVCURADDR.u32));
    VPSS_PRJVCURADDR.bits.prjv_cur_addr = prjv_cur_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_PRJVCURADDR.u32), VPSS_PRJVCURADDR.u32);

    return ;
}

HI_VOID VPSS_Mac_SetPrjhCurAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 prjh_cur_addr)
{
    U_VPSS_PRJHCURADDR VPSS_PRJHCURADDR;

    VPSS_PRJHCURADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_PRJHCURADDR.u32));
    VPSS_PRJHCURADDR.bits.prjh_cur_addr = prjh_cur_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_PRJHCURADDR.u32), VPSS_PRJHCURADDR.u32);

    return ;
}


HI_VOID VPSS_Mac_SetPrjvCurStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 prjv_cur_stride)
{
    U_VPSS_PRJCURSTRIDE VPSS_PRJCURSTRIDE;

    VPSS_PRJCURSTRIDE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_PRJCURSTRIDE.u32));
    VPSS_PRJCURSTRIDE.bits.prjv_cur_stride = prjv_cur_stride;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_PRJCURSTRIDE.u32), VPSS_PRJCURSTRIDE.u32);

    return ;
}

HI_VOID VPSS_Mac_SetPrjhCurStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 prjh_cur_stride)
{
    U_VPSS_PRJCURSTRIDE VPSS_PRJCURSTRIDE;

    VPSS_PRJCURSTRIDE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_PRJCURSTRIDE.u32));
    VPSS_PRJCURSTRIDE.bits.prjh_cur_stride = prjh_cur_stride;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_PRJCURSTRIDE.u32), VPSS_PRJCURSTRIDE.u32);

    return ;
}


HI_VOID VPSS_Mac_SetTnrCfgAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 tnr_cfg_addr)
{
    U_VPSS_TNR_ADDR VPSS_TNR_ADDR;

    VPSS_TNR_ADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_ADDR.u32));
    VPSS_TNR_ADDR.bits.tnr_cfg_addr = tnr_cfg_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_ADDR.u32), VPSS_TNR_ADDR.u32);

    return ;
}


HI_VOID VPSS_Mac_SetSnrCfgAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 snr_cfg_addr)
{
    U_VPSS_SNR_ADDR VPSS_SNR_ADDR;

    VPSS_SNR_ADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_ADDR.u32));
    VPSS_SNR_ADDR.bits.snr_cfg_addr = snr_cfg_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_ADDR.u32), VPSS_SNR_ADDR.u32);

    return ;
}



HI_VOID VPSS_Mac_SetZmeCfgAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 zme_cfg_addr)
{
    U_VPSS_ZME_ADDR VPSS_ZME_ADDR;

    VPSS_ZME_ADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_ZME_ADDR.u32));
    VPSS_ZME_ADDR.bits.zme_cfg_addr = zme_cfg_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_ZME_ADDR.u32), VPSS_ZME_ADDR.u32);

    return ;
}

HI_VOID VPSS_Mac_SetDeiCfgAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dei_cfg_addr)
{
    U_VPSS_DEI_ADDR VPSS_DEI_ADDR;

    VPSS_DEI_ADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DEI_ADDR.u32));
    VPSS_DEI_ADDR.bits.dei_cfg_addr = dei_cfg_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DEI_ADDR.u32), VPSS_DEI_ADDR.u32);

    return ;
}

HI_VOID VPSS_Mac_SetFmtcCfgAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 fmtc_cfg_addr)
{
    U_VPSS_FMTC_ADDR VPSS_FMTC_ADDR;

    VPSS_FMTC_ADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_ADDR.u32));
    VPSS_FMTC_ADDR.bits.fmtc_cfg_addr = fmtc_cfg_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_ADDR.u32), VPSS_FMTC_ADDR.u32);

    return ;
}


HI_VOID VPSS_Mac_SetChkSumWAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 chk_sum_w_addr)
{
    U_VPSS_CHK_SUM_W_ADDR VPSS_CHK_SUM_W_ADDR;

    VPSS_CHK_SUM_W_ADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CHK_SUM_W_ADDR.u32));
    VPSS_CHK_SUM_W_ADDR.bits.chk_sum_w_addr = chk_sum_w_addr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CHK_SUM_W_ADDR.u32), VPSS_CHK_SUM_W_ADDR.u32);

    return ;
}



HI_VOID VPSS_Mac_SetWinfoSumSel(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 winfo_sum_sel)
{
    U_VPSS_CHK_SUM_SEL VPSS_CHK_SUM_SEL;

    VPSS_CHK_SUM_SEL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CHK_SUM_SEL.u32));
    VPSS_CHK_SUM_SEL.bits.winfo_sum_sel = winfo_sum_sel;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CHK_SUM_SEL.u32), VPSS_CHK_SUM_SEL.u32);

    return ;
}


HI_VOID VPSS_Mac_SetRinfoSumSel(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rinfo_sum_sel)
{
    U_VPSS_CHK_SUM_SEL VPSS_CHK_SUM_SEL;

    VPSS_CHK_SUM_SEL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CHK_SUM_SEL.u32));
    VPSS_CHK_SUM_SEL.bits.rinfo_sum_sel = rinfo_sum_sel;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CHK_SUM_SEL.u32), VPSS_CHK_SUM_SEL.u32);

    return ;
}


HI_VOID VPSS_Mac_SetRch3SumSel(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch3_sum_sel)
{
    U_VPSS_CHK_SUM_SEL VPSS_CHK_SUM_SEL;

    VPSS_CHK_SUM_SEL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CHK_SUM_SEL.u32));
    VPSS_CHK_SUM_SEL.bits.rch3_sum_sel = rch3_sum_sel;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CHK_SUM_SEL.u32), VPSS_CHK_SUM_SEL.u32);

    return ;
}


HI_VOID VPSS_Mac_SetRch2SumSel(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch2_sum_sel)
{
    U_VPSS_CHK_SUM_SEL VPSS_CHK_SUM_SEL;

    VPSS_CHK_SUM_SEL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CHK_SUM_SEL.u32));
    VPSS_CHK_SUM_SEL.bits.rch2_sum_sel = rch2_sum_sel;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CHK_SUM_SEL.u32), VPSS_CHK_SUM_SEL.u32);

    return ;
}


HI_VOID VPSS_Mac_SetRch1SumSel(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch1_sum_sel)
{
    U_VPSS_CHK_SUM_SEL VPSS_CHK_SUM_SEL;

    VPSS_CHK_SUM_SEL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CHK_SUM_SEL.u32));
    VPSS_CHK_SUM_SEL.bits.rch1_sum_sel = rch1_sum_sel;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CHK_SUM_SEL.u32), VPSS_CHK_SUM_SEL.u32);

    return ;
}


HI_VOID VPSS_Mac_SetRch0SumSel(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch0_sum_sel)
{
    U_VPSS_CHK_SUM_SEL VPSS_CHK_SUM_SEL;

    VPSS_CHK_SUM_SEL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CHK_SUM_SEL.u32));
    VPSS_CHK_SUM_SEL.bits.rch0_sum_sel = rch0_sum_sel;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CHK_SUM_SEL.u32), VPSS_CHK_SUM_SEL.u32);

    return ;
}


HI_VOID VPSS_Mac_SetRchNx2clbBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_nx2clb_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32));
    VPSS_RCH_BYPASS.bits.rch_nx2c_tile_2bit_bypass = rch_nx2clb_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32), VPSS_RCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Mac_SetRchNx2ylbBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_nx2ylb_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32));
    VPSS_RCH_BYPASS.bits.rch_nx2y_tile_2bit_bypass = rch_nx2ylb_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32), VPSS_RCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Mac_SetRchTunlBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_tunl_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32));
    VPSS_RCH_BYPASS.bits.rch_tunl_bypass = rch_tunl_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32), VPSS_RCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Mac_SetRchReecBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_reec_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32));
    VPSS_RCH_BYPASS.bits.rch_reec_bypass = rch_reec_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32), VPSS_RCH_BYPASS.u32);

    return ;
}

HI_VOID VPSS_Mac_SetRchDiCntBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_di_rcnt_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32));
    VPSS_RCH_BYPASS.bits.rch_di_rcnt_bypass = rch_di_rcnt_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32), VPSS_RCH_BYPASS.u32);

    return ;
}

HI_VOID VPSS_Mac_SetRchReeyBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_reey_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32));
    VPSS_RCH_BYPASS.bits.rch_reey_bypass = rch_reey_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32), VPSS_RCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Mac_SetRchRgmvCurBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_rgmv_cur_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32));
    VPSS_RCH_BYPASS.bits.rch_rgmv_cur_bypass = rch_rgmv_cur_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32), VPSS_RCH_BYPASS.u32);

    return ;
}

HI_VOID VPSS_Mac_SetRchRgmvNx1Bypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_rgmv_nx1_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32));
    VPSS_RCH_BYPASS.bits.rch_rgmv_nx1_bypass = rch_rgmv_nx1_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32), VPSS_RCH_BYPASS.u32);

    return ;
}

HI_VOID VPSS_Mac_SetRchBlkmtRefBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_blkmt_ref_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32));
    VPSS_RCH_BYPASS.bits.rch_blkmt_ref_bypass = rch_blkmt_ref_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32), VPSS_RCH_BYPASS.u32);

    return ;
}

HI_VOID VPSS_Mac_SetRchBlkmvRefBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_blkmv_ref_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32));
    VPSS_RCH_BYPASS.bits.rch_blkmv_ref_bypass = rch_blkmv_ref_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32), VPSS_RCH_BYPASS.u32);

    return ;
}

HI_VOID VPSS_Mac_SetRchBlkmvCurBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_blkmv_cur_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32));
    VPSS_RCH_BYPASS.bits.rch_blkmv_cur_bypass = rch_blkmv_cur_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32), VPSS_RCH_BYPASS.u32);

    return ;
}
HI_VOID VPSS_Mac_SetRchPrjvCurBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_prjv_cur_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32));
    VPSS_RCH_BYPASS.bits.rch_prjv_cur_bypass = rch_prjv_cur_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32), VPSS_RCH_BYPASS.u32);

    return ;
}
HI_VOID VPSS_Mac_SetRchPrjhCurBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_prjh_cur_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32));
    VPSS_RCH_BYPASS.bits.rch_prjh_cur_bypass = rch_prjh_cur_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32), VPSS_RCH_BYPASS.u32);

    return ;
}

HI_VOID VPSS_Mac_SetRchRstBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_rst_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32));
    VPSS_RCH_BYPASS.bits.rch_rst_bypass = rch_rst_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32), VPSS_RCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Mac_SetRchSrmdBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_srmd_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32));
    VPSS_RCH_BYPASS.bits.rch_srmd_bypass = rch_srmd_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32), VPSS_RCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Mac_SetRchTrmdBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_trmd_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32));
    VPSS_RCH_BYPASS.bits.rch_trmd_bypass = rch_trmd_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32), VPSS_RCH_BYPASS.u32);

    return ;
}

HI_VOID VPSS_Mac_SetRchNx2cBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_nx2c_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32));
    VPSS_RCH_BYPASS.bits.rch_nx2c_bypass = rch_nx2c_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32), VPSS_RCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Mac_SetRchNx2yBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_nx2y_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32));
    VPSS_RCH_BYPASS.bits.rch_nx2y_bypass = rch_nx2y_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32), VPSS_RCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Mac_SetRchNx1cBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_nx1c_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32));
    VPSS_RCH_BYPASS.bits.rch_nx1c_bypass = rch_nx1c_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32), VPSS_RCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Mac_SetRchNx1yBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_nx1y_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32));
    VPSS_RCH_BYPASS.bits.rch_nx1y_bypass = rch_nx1y_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32), VPSS_RCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Mac_SetRchRefcBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_refc_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32));
    VPSS_RCH_BYPASS.bits.rch_refc_bypass = rch_refc_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32), VPSS_RCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Mac_SetRchRefyBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_refy_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32));
    VPSS_RCH_BYPASS.bits.rch_refy_bypass = rch_refy_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32), VPSS_RCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Mac_SetRchCurcBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_curc_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32));
    VPSS_RCH_BYPASS.bits.rch_curc_bypass = rch_curc_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32), VPSS_RCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Mac_SetRchCuryBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_cury_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32));
    VPSS_RCH_BYPASS.bits.rch_cury_bypass = rch_cury_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32), VPSS_RCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Mac_SetRchTransrBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_transr_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32));
    VPSS_RCH_BYPASS.bits.rch_transr_bypass = rch_transr_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32), VPSS_RCH_BYPASS.u32);

    return ;
}
HI_VOID VPSS_Mac_SetRchNx2yHeadBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_nx2y_head_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32));
    VPSS_RCH_BYPASS.bits.rch_nx2y_head_bypass = rch_nx2y_head_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32), VPSS_RCH_BYPASS.u32);

    return ;
}

HI_VOID VPSS_Mac_SetRchNx2cHeadBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_nx2c_head_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32));
    VPSS_RCH_BYPASS.bits.rch_nx2c_head_bypass = rch_nx2c_head_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32), VPSS_RCH_BYPASS.u32);

    return ;
}

HI_VOID VPSS_Mac_SetWchDiCntBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 wch_di_wcnt_bypass)
{
    U_VPSS_WCH_BYPASS VPSS_WCH_BYPASS;

    VPSS_WCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_WCH_BYPASS.u32));
    VPSS_WCH_BYPASS.bits.wch_di_wcnt_bypass = wch_di_wcnt_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_WCH_BYPASS.u32), VPSS_WCH_BYPASS.u32);

    return ;
}

HI_VOID VPSS_Mac_SetWchCuecBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 wch_cuec_bypass)
{
    U_VPSS_WCH_BYPASS VPSS_WCH_BYPASS;

    VPSS_WCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_WCH_BYPASS.u32));
    VPSS_WCH_BYPASS.bits.wch_cuec_bypass = wch_cuec_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_WCH_BYPASS.u32), VPSS_WCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Mac_SetWchCueyBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 wch_cuey_bypass)
{
    U_VPSS_WCH_BYPASS VPSS_WCH_BYPASS;

    VPSS_WCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_WCH_BYPASS.u32));
    VPSS_WCH_BYPASS.bits.wch_cuey_bypass = wch_cuey_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_WCH_BYPASS.u32), VPSS_WCH_BYPASS.u32);

    return ;
}

HI_VOID VPSS_Mac_SetWchRgmvNx2Bypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 wch_rgmvnx2_bypass)
{
    U_VPSS_WCH_BYPASS VPSS_WCH_BYPASS;

    VPSS_WCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_WCH_BYPASS.u32));
    VPSS_WCH_BYPASS.bits.wch_rgmvnx2_bypass = wch_rgmvnx2_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_WCH_BYPASS.u32), VPSS_WCH_BYPASS.u32);

    return ;
}



HI_VOID VPSS_Mac_SetWchBlkmtCurBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 wch_blkmtcur_bypass)
{
    U_VPSS_WCH_BYPASS VPSS_WCH_BYPASS;

    VPSS_WCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_WCH_BYPASS.u32));
    VPSS_WCH_BYPASS.bits.wch_blkmtcur_bypass = wch_blkmtcur_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_WCH_BYPASS.u32), VPSS_WCH_BYPASS.u32);

    return ;
}
HI_VOID VPSS_Mac_SetWchBlkmvNx1Bypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 wch_blkmvnx1_bypass)
{
    U_VPSS_WCH_BYPASS VPSS_WCH_BYPASS;

    VPSS_WCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_WCH_BYPASS.u32));
    VPSS_WCH_BYPASS.bits.wch_blkmvnx1_bypass = wch_blkmvnx1_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_WCH_BYPASS.u32), VPSS_WCH_BYPASS.u32);

    return ;
}

HI_VOID VPSS_Mac_SetWchPrjvNx2Bypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 wch_prjvnx2_bypass)
{
    U_VPSS_WCH_BYPASS VPSS_WCH_BYPASS;

    VPSS_WCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_WCH_BYPASS.u32));
    VPSS_WCH_BYPASS.bits.wch_prjvnx2_bypass = wch_prjvnx2_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_WCH_BYPASS.u32), VPSS_WCH_BYPASS.u32);

    return ;
}

HI_VOID VPSS_Mac_SetWchPrjhNx2Bypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 wch_prjhnx2_bypass)
{
    U_VPSS_WCH_BYPASS VPSS_WCH_BYPASS;

    VPSS_WCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_WCH_BYPASS.u32));
    VPSS_WCH_BYPASS.bits.wch_prjhnx2_bypass = wch_prjhnx2_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_WCH_BYPASS.u32), VPSS_WCH_BYPASS.u32);

    return ;
}

HI_VOID VPSS_Mac_SetWchSttBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 wch_stt_bypass)
{
    U_VPSS_WCH_BYPASS VPSS_WCH_BYPASS;

    VPSS_WCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_WCH_BYPASS.u32));
    VPSS_WCH_BYPASS.bits.wch_stt_bypass = wch_stt_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_WCH_BYPASS.u32), VPSS_WCH_BYPASS.u32);

    return ;
}



HI_VOID VPSS_Mac_SetWchTwmdBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 wch_twmd_bypass)
{
    U_VPSS_WCH_BYPASS VPSS_WCH_BYPASS;

    VPSS_WCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_WCH_BYPASS.u32));
    VPSS_WCH_BYPASS.bits.wch_twmd_bypass = wch_twmd_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_WCH_BYPASS.u32), VPSS_WCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Mac_SetWchWstBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 wch_wst_bypass)
{
    U_VPSS_WCH_BYPASS VPSS_WCH_BYPASS;

    VPSS_WCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_WCH_BYPASS.u32));
    VPSS_WCH_BYPASS.bits.wch_wst_bypass = wch_wst_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_WCH_BYPASS.u32), VPSS_WCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Mac_SetWchTranswBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 wch_transw_bypass)
{
    U_VPSS_WCH_BYPASS VPSS_WCH_BYPASS;

    VPSS_WCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_WCH_BYPASS.u32));
    VPSS_WCH_BYPASS.bits.wch_transw_bypass = wch_transw_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_WCH_BYPASS.u32), VPSS_WCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Mac_SetWchRfrcBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 wch_rfrc_bypass)
{
    U_VPSS_WCH_BYPASS VPSS_WCH_BYPASS;

    VPSS_WCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_WCH_BYPASS.u32));
    VPSS_WCH_BYPASS.bits.wch_rfrc_bypass = wch_rfrc_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_WCH_BYPASS.u32), VPSS_WCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Mac_SetWchRfryBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 wch_rfry_bypass)
{
    U_VPSS_WCH_BYPASS VPSS_WCH_BYPASS;

    VPSS_WCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_WCH_BYPASS.u32));
    VPSS_WCH_BYPASS.bits.wch_rfry_bypass = wch_rfry_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_WCH_BYPASS.u32), VPSS_WCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Mac_SetWchVhd0cBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 wch_vhd0c_bypass)
{
    U_VPSS_WCH_BYPASS VPSS_WCH_BYPASS;

    VPSS_WCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_WCH_BYPASS.u32));
    VPSS_WCH_BYPASS.bits.wch_vhd0c_bypass = wch_vhd0c_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_WCH_BYPASS.u32), VPSS_WCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Mac_SetWchVhd0yBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 wch_vhd0y_bypass)
{
    U_VPSS_WCH_BYPASS VPSS_WCH_BYPASS;

    VPSS_WCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_WCH_BYPASS.u32));
    VPSS_WCH_BYPASS.bits.wch_vhd0y_bypass = wch_vhd0y_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_WCH_BYPASS.u32), VPSS_WCH_BYPASS.u32);

    return ;
}

HI_VOID VPSS_Mac_SetWchTunlBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 wch_tunl_bypass)
{
    U_VPSS_WCH_BYPASS VPSS_WCH_BYPASS;

    VPSS_WCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_WCH_BYPASS.u32));
    VPSS_WCH_BYPASS.bits.wch_tunl_bypass = wch_tunl_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_WCH_BYPASS.u32), VPSS_WCH_BYPASS.u32);

    return ;
}

HI_VOID VPSS_Mac_SetWchBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 wch_bypass)
{
    U_VPSS_WCH_BYPASS VPSS_WCH_BYPASS;

    VPSS_WCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_WCH_BYPASS.u32));
    VPSS_WCH_BYPASS.u32 = wch_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_WCH_BYPASS.u32), VPSS_WCH_BYPASS.u32);

    return ;
}

HI_VOID VPSS_Mac_SetRchBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32));
    VPSS_RCH_BYPASS.u32 = rch_bypass;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32), VPSS_RCH_BYPASS.u32);

    return ;
}

#endif
