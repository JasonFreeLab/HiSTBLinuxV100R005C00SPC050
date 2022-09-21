#include "vdp_hal_comm.h"
#include "vdp_hal_ip_snr.h"

extern S_VDP_REGS_TYPE *pVdpReg;

#if 1
//SNR CFG START

HI_VOID VDP_VID_SetSnrCfgAddr(HI_U32 u32Data, HI_U32 u32Addr)
{
    U_V0_SNR_CFGAD         V0_SNR_CFGAD;
    if(u32Data >= VID_MAX)
    {
      VDP_PRINT("Error,VDP_VID_SetSnrCfgAddr() select wrong video layer ID\n");
      return ;
    }

    V0_SNR_CFGAD.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_CFGAD.u32) + u32Data * VID_OFFSET));

    V0_SNR_CFGAD.bits.coef_addr = u32Addr;

    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_CFGAD.u32) + u32Data * VID_OFFSET), V0_SNR_CFGAD.u32);
    return;
}

HI_VOID VDP_VID_SetSnrEnable(HI_U32 u32Data, HI_U32 u32Data1)
{
    U_V0_PRERD V0_PRERD;
    if(u32Data >= VID_MAX)
    {
      VDP_PRINT("Error,VDP_VID_SetNrEnable() select wrong video layer ID\n");
      return ;
    }
    V0_PRERD.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_PRERD.u32) + u32Data * VID_OFFSET));
    V0_PRERD.bits.snr_en = u32Data1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_PRERD.u32) + u32Data * VID_OFFSET), V0_PRERD.u32);
    return;
}

HI_VOID VDP_VID_SetSnrstrength(HI_U32 u32Data, HI_U32 snrstrength)
{
	U_V0_SNR_ENABLE V0_SNR_ENABLE;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetSnrstrength Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_ENABLE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_ENABLE.u32) + u32Data * VID_OFFSET));
	V0_SNR_ENABLE.bits.snrstrength = snrstrength;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_ENABLE.u32) + u32Data * VID_OFFSET),V0_SNR_ENABLE.u32);

	return ;
}


HI_VOID VDP_VID_SetSnrfiltermode(HI_U32 u32Data, HI_U32 snrfiltermode)
{
	U_V0_SNR_ENABLE V0_SNR_ENABLE;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetSnrfiltermode Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_ENABLE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_ENABLE.u32) + u32Data * VID_OFFSET));
	V0_SNR_ENABLE.bits.snrfiltermode = snrfiltermode;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_ENABLE.u32) + u32Data * VID_OFFSET),V0_SNR_ENABLE.u32);

	return ;
}


HI_VOID VDP_VID_SetMeanedgeratioen(HI_U32 u32Data, HI_U32 meanedgeratioen)
{
	U_V0_SNR_ENABLE V0_SNR_ENABLE;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetMeanedgeratioen Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_ENABLE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_ENABLE.u32) + u32Data * VID_OFFSET));
	V0_SNR_ENABLE.bits.meanedgeratioen = meanedgeratioen;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_ENABLE.u32) + u32Data * VID_OFFSET),V0_SNR_ENABLE.u32);

	return ;
}


HI_VOID VDP_VID_SetEdgelpfmode(HI_U32 u32Data, HI_U32 edgelpfmode)
{
	U_V0_SNR_ENABLE V0_SNR_ENABLE;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetEdgelpfmode Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_ENABLE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_ENABLE.u32) + u32Data * VID_OFFSET));
	V0_SNR_ENABLE.bits.edgelpfmode = edgelpfmode;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_ENABLE.u32) + u32Data * VID_OFFSET),V0_SNR_ENABLE.u32);

	return ;
}


HI_VOID VDP_VID_SetDebugmode(HI_U32 u32Data, HI_U32 debugmode)
{
	U_V0_SNR_ENABLE V0_SNR_ENABLE;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetDebugmode Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_ENABLE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_ENABLE.u32) + u32Data * VID_OFFSET));
	V0_SNR_ENABLE.bits.debugmode = debugmode;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_ENABLE.u32) + u32Data * VID_OFFSET),V0_SNR_ENABLE.u32);

	return ;
}


HI_VOID VDP_VID_SetDebugmodeen(HI_U32 u32Data, HI_U32 debugmodeen)
{
	U_V0_SNR_ENABLE V0_SNR_ENABLE;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetDebugmodeen Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_ENABLE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_ENABLE.u32) + u32Data * VID_OFFSET));
	V0_SNR_ENABLE.bits.debugmodeen = debugmodeen;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_ENABLE.u32) + u32Data * VID_OFFSET),V0_SNR_ENABLE.u32);

	return ;
}


HI_VOID VDP_VID_SetDemomodelr(HI_U32 u32Data, HI_U32 demomodelr)
{
	U_V0_SNR_ENABLE V0_SNR_ENABLE;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetDemomodelr Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_ENABLE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_ENABLE.u32) + u32Data * VID_OFFSET));
	V0_SNR_ENABLE.bits.demomodelr = demomodelr;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_ENABLE.u32) + u32Data * VID_OFFSET),V0_SNR_ENABLE.u32);

	return ;
}


HI_VOID VDP_VID_SetDemomodeen(HI_U32 u32Data, HI_U32 demomodeen)
{
	U_V0_SNR_ENABLE V0_SNR_ENABLE;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetDemomodeen Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_ENABLE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_ENABLE.u32) + u32Data * VID_OFFSET));
	V0_SNR_ENABLE.bits.demomodeen = demomodeen;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_ENABLE.u32) + u32Data * VID_OFFSET),V0_SNR_ENABLE.u32);

	return ;
}


HI_VOID VDP_VID_SetBlendingmode(HI_U32 u32Data, HI_U32 blendingmode)
{
	U_V0_SNR_ENABLE V0_SNR_ENABLE;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetBlendingmode Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_ENABLE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_ENABLE.u32) + u32Data * VID_OFFSET));
	V0_SNR_ENABLE.bits.blendingmode = blendingmode;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_ENABLE.u32) + u32Data * VID_OFFSET),V0_SNR_ENABLE.u32);

	return ;
}


HI_VOID VDP_VID_SetEdgeonlyen(HI_U32 u32Data, HI_U32 edgeonlyen)
{
	U_V0_SNR_ENABLE V0_SNR_ENABLE;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetEdgeonlyen Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_ENABLE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_ENABLE.u32) + u32Data * VID_OFFSET));
	V0_SNR_ENABLE.bits.edgeonlyen = edgeonlyen;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_ENABLE.u32) + u32Data * VID_OFFSET),V0_SNR_ENABLE.u32);

	return ;
}


HI_VOID VDP_VID_SetEdgeprelpfen(HI_U32 u32Data, HI_U32 edgeprelpfen)
{
	U_V0_SNR_ENABLE V0_SNR_ENABLE;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetEdgeprelpfen Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_ENABLE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_ENABLE.u32) + u32Data * VID_OFFSET));
	V0_SNR_ENABLE.bits.edgeprelpfen = edgeprelpfen;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_ENABLE.u32) + u32Data * VID_OFFSET),V0_SNR_ENABLE.u32);

	return ;
}


HI_VOID VDP_VID_SetLumasnren(HI_U32 u32Data, HI_U32 lumasnren)
{
	U_V0_SNR_ENABLE V0_SNR_ENABLE;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetLumasnren Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_ENABLE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_ENABLE.u32) + u32Data * VID_OFFSET));
	V0_SNR_ENABLE.bits.lumasnren = lumasnren;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_ENABLE.u32) + u32Data * VID_OFFSET),V0_SNR_ENABLE.u32);

	return ;
}


HI_VOID VDP_VID_SetMeanedgeratiox2(HI_U32 u32Data, HI_U32 meanedgeratiox2)
{
	U_V0_SNR_EDGE_RATIOX0 V0_SNR_EDGE_RATIOX0;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetMeanedgeratiox2 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_RATIOX0.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_RATIOX0.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_RATIOX0.bits.meanedgeratiox2 = meanedgeratiox2;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_RATIOX0.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_RATIOX0.u32);

	return ;
}


HI_VOID VDP_VID_SetMeanedgeratiox1(HI_U32 u32Data, HI_U32 meanedgeratiox1)
{
	U_V0_SNR_EDGE_RATIOX0 V0_SNR_EDGE_RATIOX0;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetMeanedgeratiox1 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_RATIOX0.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_RATIOX0.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_RATIOX0.bits.meanedgeratiox1 = meanedgeratiox1;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_RATIOX0.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_RATIOX0.u32);

	return ;
}


HI_VOID VDP_VID_SetMeanedgeratiox0(HI_U32 u32Data, HI_U32 meanedgeratiox0)
{
	U_V0_SNR_EDGE_RATIOX0 V0_SNR_EDGE_RATIOX0;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetMeanedgeratiox0 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_RATIOX0.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_RATIOX0.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_RATIOX0.bits.meanedgeratiox0 = meanedgeratiox0;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_RATIOX0.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_RATIOX0.u32);

	return ;
}


HI_VOID VDP_VID_SetMeanedgeratiox5(HI_U32 u32Data, HI_U32 meanedgeratiox5)
{
	U_V0_SNR_EDGE_RATIOX1 V0_SNR_EDGE_RATIOX1;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetMeanedgeratiox5 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_RATIOX1.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_RATIOX1.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_RATIOX1.bits.meanedgeratiox5 = meanedgeratiox5;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_RATIOX1.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_RATIOX1.u32);

	return ;
}


HI_VOID VDP_VID_SetMeanedgeratiox4(HI_U32 u32Data, HI_U32 meanedgeratiox4)
{
	U_V0_SNR_EDGE_RATIOX1 V0_SNR_EDGE_RATIOX1;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetMeanedgeratiox4 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_RATIOX1.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_RATIOX1.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_RATIOX1.bits.meanedgeratiox4 = meanedgeratiox4;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_RATIOX1.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_RATIOX1.u32);

	return ;
}


HI_VOID VDP_VID_SetMeanedgeratiox3(HI_U32 u32Data, HI_U32 meanedgeratiox3)
{
	U_V0_SNR_EDGE_RATIOX1 V0_SNR_EDGE_RATIOX1;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetMeanedgeratiox3 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_RATIOX1.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_RATIOX1.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_RATIOX1.bits.meanedgeratiox3 = meanedgeratiox3;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_RATIOX1.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_RATIOX1.u32);

	return ;
}


HI_VOID VDP_VID_SetMeanedgeratioy2(HI_U32 u32Data, HI_U32 meanedgeratioy2)
{
	U_V0_SNR_EDGE_RATIOY0 V0_SNR_EDGE_RATIOY0;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetMeanedgeratioy2 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_RATIOY0.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_RATIOY0.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_RATIOY0.bits.meanedgeratioy2 = meanedgeratioy2;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_RATIOY0.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_RATIOY0.u32);

	return ;
}


HI_VOID VDP_VID_SetMeanedgeratioy1(HI_U32 u32Data, HI_U32 meanedgeratioy1)
{
	U_V0_SNR_EDGE_RATIOY0 V0_SNR_EDGE_RATIOY0;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetMeanedgeratioy1 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_RATIOY0.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_RATIOY0.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_RATIOY0.bits.meanedgeratioy1 = meanedgeratioy1;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_RATIOY0.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_RATIOY0.u32);

	return ;
}


HI_VOID VDP_VID_SetMeanedgeratioy0(HI_U32 u32Data, HI_U32 meanedgeratioy0)
{
	U_V0_SNR_EDGE_RATIOY0 V0_SNR_EDGE_RATIOY0;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetMeanedgeratioy0 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_RATIOY0.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_RATIOY0.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_RATIOY0.bits.meanedgeratioy0 = meanedgeratioy0;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_RATIOY0.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_RATIOY0.u32);

	return ;
}


HI_VOID VDP_VID_SetMeanedgeratioy4(HI_U32 u32Data, HI_U32 meanedgeratioy4)
{
	U_V0_SNR_EDGE_RATIOY1 V0_SNR_EDGE_RATIOY1;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetMeanedgeratioy4 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_RATIOY1.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_RATIOY1.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_RATIOY1.bits.meanedgeratioy4 = meanedgeratioy4;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_RATIOY1.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_RATIOY1.u32);

	return ;
}


HI_VOID VDP_VID_SetMeanedgeratioy3(HI_U32 u32Data, HI_U32 meanedgeratioy3)
{
	U_V0_SNR_EDGE_RATIOY1 V0_SNR_EDGE_RATIOY1;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetMeanedgeratioy3 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_RATIOY1.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_RATIOY1.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_RATIOY1.bits.meanedgeratioy3 = meanedgeratioy3;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_RATIOY1.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_RATIOY1.u32);

	return ;
}


HI_VOID VDP_VID_SetMeanedgeratiok1(HI_U32 u32Data, HI_U32 meanedgeratiok1)
{
	U_V0_SNR_EDGE_RATIOK0 V0_SNR_EDGE_RATIOK0;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetMeanedgeratiok1 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_RATIOK0.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_RATIOK0.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_RATIOK0.bits.meanedgeratiok1 = meanedgeratiok1;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_RATIOK0.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_RATIOK0.u32);

	return ;
}


HI_VOID VDP_VID_SetMeanedgeratiok0(HI_U32 u32Data, HI_U32 meanedgeratiok0)
{
	U_V0_SNR_EDGE_RATIOK0 V0_SNR_EDGE_RATIOK0;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetMeanedgeratiok0 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_RATIOK0.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_RATIOK0.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_RATIOK0.bits.meanedgeratiok0 = meanedgeratiok0;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_RATIOK0.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_RATIOK0.u32);

	return ;
}


HI_VOID VDP_VID_SetMeanedgeratiok3(HI_U32 u32Data, HI_U32 meanedgeratiok3)
{
	U_V0_SNR_EDGE_RATIOK1 V0_SNR_EDGE_RATIOK1;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetMeanedgeratiok3 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_RATIOK1.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_RATIOK1.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_RATIOK1.bits.meanedgeratiok3 = meanedgeratiok3;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_RATIOK1.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_RATIOK1.u32);

	return ;
}


HI_VOID VDP_VID_SetMeanedgeratiok2(HI_U32 u32Data, HI_U32 meanedgeratiok2)
{
	U_V0_SNR_EDGE_RATIOK1 V0_SNR_EDGE_RATIOK1;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetMeanedgeratiok2 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_RATIOK1.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_RATIOK1.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_RATIOK1.bits.meanedgeratiok2 = meanedgeratiok2;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_RATIOK1.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_RATIOK1.u32);

	return ;
}


HI_VOID VDP_VID_SetMeanedgeratiomin(HI_U32 u32Data, HI_U32 meanedgeratiomin)
{
	U_V0_SNR_EDGE_RATIO V0_SNR_EDGE_RATIO;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetMeanedgeratiomin Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_RATIO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_RATIO.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_RATIO.bits.meanedgeratiomin = meanedgeratiomin;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_RATIO.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_RATIO.u32);

	return ;
}


HI_VOID VDP_VID_SetMeanedgeratiomax(HI_U32 u32Data, HI_U32 meanedgeratiomax)
{
	U_V0_SNR_EDGE_RATIO V0_SNR_EDGE_RATIO;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetMeanedgeratiomax Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_RATIO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_RATIO.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_RATIO.bits.meanedgeratiomax = meanedgeratiomax;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_RATIO.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_RATIO.u32);

	return ;
}


HI_VOID VDP_VID_SetEdgestrmappingx2(HI_U32 u32Data, HI_U32 edgestrmappingx2)
{
	U_V0_SNR_EDGE_STRX0 V0_SNR_EDGE_STRX0;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetEdgestrmappingx2 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_STRX0.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRX0.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_STRX0.bits.edgestrmappingx2 = edgestrmappingx2;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRX0.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_STRX0.u32);

	return ;
}


HI_VOID VDP_VID_SetEdgestrmappingx1(HI_U32 u32Data, HI_U32 edgestrmappingx1)
{
	U_V0_SNR_EDGE_STRX0 V0_SNR_EDGE_STRX0;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetEdgestrmappingx1 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_STRX0.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRX0.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_STRX0.bits.edgestrmappingx1 = edgestrmappingx1;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRX0.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_STRX0.u32);

	return ;
}


HI_VOID VDP_VID_SetEdgestrmappingx0(HI_U32 u32Data, HI_U32 edgestrmappingx0)
{
	U_V0_SNR_EDGE_STRX0 V0_SNR_EDGE_STRX0;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetEdgestrmappingx0 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_STRX0.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRX0.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_STRX0.bits.edgestrmappingx0 = edgestrmappingx0;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRX0.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_STRX0.u32);

	return ;
}


HI_VOID VDP_VID_SetEdgestrmappingx5(HI_U32 u32Data, HI_U32 edgestrmappingx5)
{
	U_V0_SNR_EDGE_STRX1 V0_SNR_EDGE_STRX1;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetEdgestrmappingx5 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_STRX1.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRX1.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_STRX1.bits.edgestrmappingx5 = edgestrmappingx5;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRX1.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_STRX1.u32);

	return ;
}


HI_VOID VDP_VID_SetEdgestrmappingx4(HI_U32 u32Data, HI_U32 edgestrmappingx4)
{
	U_V0_SNR_EDGE_STRX1 V0_SNR_EDGE_STRX1;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetEdgestrmappingx4 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_STRX1.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRX1.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_STRX1.bits.edgestrmappingx4 = edgestrmappingx4;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRX1.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_STRX1.u32);

	return ;
}


HI_VOID VDP_VID_SetEdgestrmappingx3(HI_U32 u32Data, HI_U32 edgestrmappingx3)
{
	U_V0_SNR_EDGE_STRX1 V0_SNR_EDGE_STRX1;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetEdgestrmappingx3 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_STRX1.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRX1.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_STRX1.bits.edgestrmappingx3 = edgestrmappingx3;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRX1.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_STRX1.u32);

	return ;
}


HI_VOID VDP_VID_SetEdgestrmappingx7(HI_U32 u32Data, HI_U32 edgestrmappingx7)
{
	U_V0_SNR_EDGE_STRX2 V0_SNR_EDGE_STRX2;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetEdgestrmappingx7 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_STRX2.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRX2.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_STRX2.bits.edgestrmappingx7 = edgestrmappingx7;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRX2.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_STRX2.u32);

	return ;
}


HI_VOID VDP_VID_SetEdgestrmappingx6(HI_U32 u32Data, HI_U32 edgestrmappingx6)
{
	U_V0_SNR_EDGE_STRX2 V0_SNR_EDGE_STRX2;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetEdgestrmappingx6 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_STRX2.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRX2.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_STRX2.bits.edgestrmappingx6 = edgestrmappingx6;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRX2.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_STRX2.u32);

	return ;
}


HI_VOID VDP_VID_SetEdgestrmappingy3(HI_U32 u32Data, HI_U32 edgestrmappingy3)
{
	U_V0_SNR_EDGE_STRY0 V0_SNR_EDGE_STRY0;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetEdgestrmappingy3 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_STRY0.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRY0.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_STRY0.bits.edgestrmappingy3 = edgestrmappingy3;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRY0.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_STRY0.u32);

	return ;
}


HI_VOID VDP_VID_SetEdgestrmappingy2(HI_U32 u32Data, HI_U32 edgestrmappingy2)
{
	U_V0_SNR_EDGE_STRY0 V0_SNR_EDGE_STRY0;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetEdgestrmappingy2 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_STRY0.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRY0.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_STRY0.bits.edgestrmappingy2 = edgestrmappingy2;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRY0.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_STRY0.u32);

	return ;
}


HI_VOID VDP_VID_SetEdgestrmappingy1(HI_U32 u32Data, HI_U32 edgestrmappingy1)
{
	U_V0_SNR_EDGE_STRY0 V0_SNR_EDGE_STRY0;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetEdgestrmappingy1 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_STRY0.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRY0.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_STRY0.bits.edgestrmappingy1 = edgestrmappingy1;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRY0.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_STRY0.u32);

	return ;
}


HI_VOID VDP_VID_SetEdgestrmappingy0(HI_U32 u32Data, HI_U32 edgestrmappingy0)
{
	U_V0_SNR_EDGE_STRY0 V0_SNR_EDGE_STRY0;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetEdgestrmappingy0 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_STRY0.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRY0.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_STRY0.bits.edgestrmappingy0 = edgestrmappingy0;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRY0.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_STRY0.u32);

	return ;
}


HI_VOID VDP_VID_SetEdgestrmappingy6(HI_U32 u32Data, HI_U32 edgestrmappingy6)
{
	U_V0_SNR_EDGE_STRY1 V0_SNR_EDGE_STRY1;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetEdgestrmappingy6 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_STRY1.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRY1.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_STRY1.bits.edgestrmappingy6 = edgestrmappingy6;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRY1.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_STRY1.u32);

	return ;
}


HI_VOID VDP_VID_SetEdgestrmappingy5(HI_U32 u32Data, HI_U32 edgestrmappingy5)
{
	U_V0_SNR_EDGE_STRY1 V0_SNR_EDGE_STRY1;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetEdgestrmappingy5 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_STRY1.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRY1.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_STRY1.bits.edgestrmappingy5 = edgestrmappingy5;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRY1.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_STRY1.u32);

	return ;
}


HI_VOID VDP_VID_SetEdgestrmappingy4(HI_U32 u32Data, HI_U32 edgestrmappingy4)
{
	U_V0_SNR_EDGE_STRY1 V0_SNR_EDGE_STRY1;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetEdgestrmappingy4 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_STRY1.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRY1.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_STRY1.bits.edgestrmappingy4 = edgestrmappingy4;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRY1.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_STRY1.u32);

	return ;
}


HI_VOID VDP_VID_SetEdgestrmappingk2(HI_U32 u32Data, HI_U32 edgestrmappingk2)
{
	U_V0_SNR_EDGE_STRK0 V0_SNR_EDGE_STRK0;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetEdgestrmappingk2 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_STRK0.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRK0.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_STRK0.bits.edgestrmappingk2 = edgestrmappingk2;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRK0.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_STRK0.u32);

	return ;
}


HI_VOID VDP_VID_SetEdgestrmappingk1(HI_U32 u32Data, HI_U32 edgestrmappingk1)
{
	U_V0_SNR_EDGE_STRK0 V0_SNR_EDGE_STRK0;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetEdgestrmappingk1 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_STRK0.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRK0.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_STRK0.bits.edgestrmappingk1 = edgestrmappingk1;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRK0.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_STRK0.u32);

	return ;
}


HI_VOID VDP_VID_SetEdgestrmappingk0(HI_U32 u32Data, HI_U32 edgestrmappingk0)
{
	U_V0_SNR_EDGE_STRK0 V0_SNR_EDGE_STRK0;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetEdgestrmappingk0 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_STRK0.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRK0.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_STRK0.bits.edgestrmappingk0 = edgestrmappingk0;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRK0.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_STRK0.u32);

	return ;
}


HI_VOID VDP_VID_SetEdgestrmappingk5(HI_U32 u32Data, HI_U32 edgestrmappingk5)
{
	U_V0_SNR_EDGE_STRK1 V0_SNR_EDGE_STRK1;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetEdgestrmappingk5 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_STRK1.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRK1.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_STRK1.bits.edgestrmappingk5 = edgestrmappingk5;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRK1.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_STRK1.u32);

	return ;
}


HI_VOID VDP_VID_SetEdgestrmappingk4(HI_U32 u32Data, HI_U32 edgestrmappingk4)
{
	U_V0_SNR_EDGE_STRK1 V0_SNR_EDGE_STRK1;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetEdgestrmappingk4 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_STRK1.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRK1.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_STRK1.bits.edgestrmappingk4 = edgestrmappingk4;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRK1.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_STRK1.u32);

	return ;
}


HI_VOID VDP_VID_SetEdgestrmappingk3(HI_U32 u32Data, HI_U32 edgestrmappingk3)
{
	U_V0_SNR_EDGE_STRK1 V0_SNR_EDGE_STRK1;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetEdgestrmappingk3 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_STRK1.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRK1.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_STRK1.bits.edgestrmappingk3 = edgestrmappingk3;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STRK1.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_STRK1.u32);

	return ;
}


HI_VOID VDP_VID_SetEdgestrmappingmax(HI_U32 u32Data, HI_U32 edgestrmappingmax)
{
	U_V0_SNR_EDGE_STR V0_SNR_EDGE_STR;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetEdgestrmappingmax Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_STR.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STR.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_STR.bits.edgestrmappingmax = edgestrmappingmax;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STR.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_STR.u32);

	return ;
}


HI_VOID VDP_VID_SetEdgestrmappingmin(HI_U32 u32Data, HI_U32 edgestrmappingmin)
{
	U_V0_SNR_EDGE_STR V0_SNR_EDGE_STR;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetEdgestrmappingmin Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_EDGE_STR.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STR.u32) + u32Data * VID_OFFSET));
	V0_SNR_EDGE_STR.bits.edgestrmappingmin = edgestrmappingmin;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_EDGE_STR.u32) + u32Data * VID_OFFSET),V0_SNR_EDGE_STR.u32);

	return ;
}


HI_VOID VDP_VID_SetSfymaxedgevalthd3(HI_U32 u32Data, HI_U32 sfymaxedgevalthd3)
{
	U_V0_SNR_SFYMAX_VALTH V0_SNR_SFYMAX_VALTH;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetSfymaxedgevalthd3 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_SFYMAX_VALTH.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_SFYMAX_VALTH.u32) + u32Data * VID_OFFSET));
	V0_SNR_SFYMAX_VALTH.bits.sfymaxedgevalthd3 = sfymaxedgevalthd3;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_SFYMAX_VALTH.u32) + u32Data * VID_OFFSET),V0_SNR_SFYMAX_VALTH.u32);

	return ;
}


HI_VOID VDP_VID_SetSfymaxedgevalthd2(HI_U32 u32Data, HI_U32 sfymaxedgevalthd2)
{
	U_V0_SNR_SFYMAX_VALTH V0_SNR_SFYMAX_VALTH;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetSfymaxedgevalthd2 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_SFYMAX_VALTH.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_SFYMAX_VALTH.u32) + u32Data * VID_OFFSET));
	V0_SNR_SFYMAX_VALTH.bits.sfymaxedgevalthd2 = sfymaxedgevalthd2;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_SFYMAX_VALTH.u32) + u32Data * VID_OFFSET),V0_SNR_SFYMAX_VALTH.u32);

	return ;
}


HI_VOID VDP_VID_SetSfymaxedgevalthd1(HI_U32 u32Data, HI_U32 sfymaxedgevalthd1)
{
	U_V0_SNR_SFYMAX_VALTH V0_SNR_SFYMAX_VALTH;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetSfymaxedgevalthd1 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_SFYMAX_VALTH.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_SFYMAX_VALTH.u32) + u32Data * VID_OFFSET));
	V0_SNR_SFYMAX_VALTH.bits.sfymaxedgevalthd1 = sfymaxedgevalthd1;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_SFYMAX_VALTH.u32) + u32Data * VID_OFFSET),V0_SNR_SFYMAX_VALTH.u32);

	return ;
}


HI_VOID VDP_VID_SetSfymaxedgeidxthd3(HI_U32 u32Data, HI_U32 sfymaxedgeidxthd3)
{
	U_V0_SNR_SFYMAX_IDXTH V0_SNR_SFYMAX_IDXTH;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetSfymaxedgeidxthd3 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_SFYMAX_IDXTH.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_SFYMAX_IDXTH.u32) + u32Data * VID_OFFSET));
	V0_SNR_SFYMAX_IDXTH.bits.sfymaxedgeidxthd3 = sfymaxedgeidxthd3;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_SFYMAX_IDXTH.u32) + u32Data * VID_OFFSET),V0_SNR_SFYMAX_IDXTH.u32);

	return ;
}


HI_VOID VDP_VID_SetSfymaxedgeidxthd2(HI_U32 u32Data, HI_U32 sfymaxedgeidxthd2)
{
	U_V0_SNR_SFYMAX_IDXTH V0_SNR_SFYMAX_IDXTH;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetSfymaxedgeidxthd2 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_SFYMAX_IDXTH.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_SFYMAX_IDXTH.u32) + u32Data * VID_OFFSET));
	V0_SNR_SFYMAX_IDXTH.bits.sfymaxedgeidxthd2 = sfymaxedgeidxthd2;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_SFYMAX_IDXTH.u32) + u32Data * VID_OFFSET),V0_SNR_SFYMAX_IDXTH.u32);

	return ;
}


HI_VOID VDP_VID_SetSfymaxedgeidxthd1(HI_U32 u32Data, HI_U32 sfymaxedgeidxthd1)
{
	U_V0_SNR_SFYMAX_IDXTH V0_SNR_SFYMAX_IDXTH;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetSfymaxedgeidxthd1 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_SFYMAX_IDXTH.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_SFYMAX_IDXTH.u32) + u32Data * VID_OFFSET));
	V0_SNR_SFYMAX_IDXTH.bits.sfymaxedgeidxthd1 = sfymaxedgeidxthd1;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_SFYMAX_IDXTH.u32) + u32Data * VID_OFFSET),V0_SNR_SFYMAX_IDXTH.u32);

	return ;
}


HI_VOID VDP_VID_SetSfymeanedgevalthd3(HI_U32 u32Data, HI_U32 sfymeanedgevalthd3)
{
	U_V0_SNR_SFYMEAN_VALTH V0_SNR_SFYMEAN_VALTH;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetSfymeanedgevalthd3 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_SFYMEAN_VALTH.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_SFYMEAN_VALTH.u32) + u32Data * VID_OFFSET));
	V0_SNR_SFYMEAN_VALTH.bits.sfymeanedgevalthd3 = sfymeanedgevalthd3;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_SFYMEAN_VALTH.u32) + u32Data * VID_OFFSET),V0_SNR_SFYMEAN_VALTH.u32);

	return ;
}


HI_VOID VDP_VID_SetSfymeanedgevalthd2(HI_U32 u32Data, HI_U32 sfymeanedgevalthd2)
{
	U_V0_SNR_SFYMEAN_VALTH V0_SNR_SFYMEAN_VALTH;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetSfymeanedgevalthd2 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_SFYMEAN_VALTH.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_SFYMEAN_VALTH.u32) + u32Data * VID_OFFSET));
	V0_SNR_SFYMEAN_VALTH.bits.sfymeanedgevalthd2 = sfymeanedgevalthd2;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_SFYMEAN_VALTH.u32) + u32Data * VID_OFFSET),V0_SNR_SFYMEAN_VALTH.u32);

	return ;
}


HI_VOID VDP_VID_SetSfymeanedgevalthd1(HI_U32 u32Data, HI_U32 sfymeanedgevalthd1)
{
	U_V0_SNR_SFYMEAN_VALTH V0_SNR_SFYMEAN_VALTH;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetSfymeanedgevalthd1 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_SFYMEAN_VALTH.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_SFYMEAN_VALTH.u32) + u32Data * VID_OFFSET));
	V0_SNR_SFYMEAN_VALTH.bits.sfymeanedgevalthd1 = sfymeanedgevalthd1;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_SFYMEAN_VALTH.u32) + u32Data * VID_OFFSET),V0_SNR_SFYMEAN_VALTH.u32);

	return ;
}


HI_VOID VDP_VID_SetWfymaxedgevalthd3(HI_U32 u32Data, HI_U32 wfymaxedgevalthd3)
{
	U_V0_SNR_WFYMAX_VALTH V0_SNR_WFYMAX_VALTH;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetWfymaxedgevalthd3 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_WFYMAX_VALTH.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_WFYMAX_VALTH.u32) + u32Data * VID_OFFSET));
	V0_SNR_WFYMAX_VALTH.bits.wfymaxedgevalthd3 = wfymaxedgevalthd3;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_WFYMAX_VALTH.u32) + u32Data * VID_OFFSET),V0_SNR_WFYMAX_VALTH.u32);

	return ;
}


HI_VOID VDP_VID_SetWfymaxedgevalthd2(HI_U32 u32Data, HI_U32 wfymaxedgevalthd2)
{
	U_V0_SNR_WFYMAX_VALTH V0_SNR_WFYMAX_VALTH;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetWfymaxedgevalthd2 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_WFYMAX_VALTH.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_WFYMAX_VALTH.u32) + u32Data * VID_OFFSET));
	V0_SNR_WFYMAX_VALTH.bits.wfymaxedgevalthd2 = wfymaxedgevalthd2;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_WFYMAX_VALTH.u32) + u32Data * VID_OFFSET),V0_SNR_WFYMAX_VALTH.u32);

	return ;
}


HI_VOID VDP_VID_SetWfymaxedgevalthd1(HI_U32 u32Data, HI_U32 wfymaxedgevalthd1)
{
	U_V0_SNR_WFYMAX_VALTH V0_SNR_WFYMAX_VALTH;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetWfymaxedgevalthd1 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_WFYMAX_VALTH.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_WFYMAX_VALTH.u32) + u32Data * VID_OFFSET));
	V0_SNR_WFYMAX_VALTH.bits.wfymaxedgevalthd1 = wfymaxedgevalthd1;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_WFYMAX_VALTH.u32) + u32Data * VID_OFFSET),V0_SNR_WFYMAX_VALTH.u32);

	return ;
}


HI_VOID VDP_VID_SetWfymaxedgeidxthd3(HI_U32 u32Data, HI_U32 wfymaxedgeidxthd3)
{
	U_V0_SNR_WFYMAX_IDXTH V0_SNR_WFYMAX_IDXTH;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetWfymaxedgeidxthd3 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_WFYMAX_IDXTH.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_WFYMAX_IDXTH.u32) + u32Data * VID_OFFSET));
	V0_SNR_WFYMAX_IDXTH.bits.wfymaxedgeidxthd3 = wfymaxedgeidxthd3;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_WFYMAX_IDXTH.u32) + u32Data * VID_OFFSET),V0_SNR_WFYMAX_IDXTH.u32);

	return ;
}


HI_VOID VDP_VID_SetWfymaxedgeidxthd2(HI_U32 u32Data, HI_U32 wfymaxedgeidxthd2)
{
	U_V0_SNR_WFYMAX_IDXTH V0_SNR_WFYMAX_IDXTH;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetWfymaxedgeidxthd2 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_WFYMAX_IDXTH.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_WFYMAX_IDXTH.u32) + u32Data * VID_OFFSET));
	V0_SNR_WFYMAX_IDXTH.bits.wfymaxedgeidxthd2 = wfymaxedgeidxthd2;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_WFYMAX_IDXTH.u32) + u32Data * VID_OFFSET),V0_SNR_WFYMAX_IDXTH.u32);

	return ;
}


HI_VOID VDP_VID_SetWfymaxedgeidxthd1(HI_U32 u32Data, HI_U32 wfymaxedgeidxthd1)
{
	U_V0_SNR_WFYMAX_IDXTH V0_SNR_WFYMAX_IDXTH;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetWfymaxedgeidxthd1 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_WFYMAX_IDXTH.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_WFYMAX_IDXTH.u32) + u32Data * VID_OFFSET));
	V0_SNR_WFYMAX_IDXTH.bits.wfymaxedgeidxthd1 = wfymaxedgeidxthd1;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_WFYMAX_IDXTH.u32) + u32Data * VID_OFFSET),V0_SNR_WFYMAX_IDXTH.u32);

	return ;
}


HI_VOID VDP_VID_SetWfymeanedgevalthd3(HI_U32 u32Data, HI_U32 wfymeanedgevalthd3)
{
	U_V0_SNR_WFYMEAN_VALTH V0_SNR_WFYMEAN_VALTH;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetWfymeanedgevalthd3 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_WFYMEAN_VALTH.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_WFYMEAN_VALTH.u32) + u32Data * VID_OFFSET));
	V0_SNR_WFYMEAN_VALTH.bits.wfymeanedgevalthd3 = wfymeanedgevalthd3;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_WFYMEAN_VALTH.u32) + u32Data * VID_OFFSET),V0_SNR_WFYMEAN_VALTH.u32);

	return ;
}


HI_VOID VDP_VID_SetWfymeanedgevalthd2(HI_U32 u32Data, HI_U32 wfymeanedgevalthd2)
{
	U_V0_SNR_WFYMEAN_VALTH V0_SNR_WFYMEAN_VALTH;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetWfymeanedgevalthd2 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_WFYMEAN_VALTH.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_WFYMEAN_VALTH.u32) + u32Data * VID_OFFSET));
	V0_SNR_WFYMEAN_VALTH.bits.wfymeanedgevalthd2 = wfymeanedgevalthd2;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_WFYMEAN_VALTH.u32) + u32Data * VID_OFFSET),V0_SNR_WFYMEAN_VALTH.u32);

	return ;
}


HI_VOID VDP_VID_SetWfymeanedgevalthd1(HI_U32 u32Data, HI_U32 wfymeanedgevalthd1)
{
	U_V0_SNR_WFYMEAN_VALTH V0_SNR_WFYMEAN_VALTH;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetWfymeanedgevalthd1 Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_WFYMEAN_VALTH.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_WFYMEAN_VALTH.u32) + u32Data * VID_OFFSET));
	V0_SNR_WFYMEAN_VALTH.bits.wfymeanedgevalthd1 = wfymeanedgevalthd1;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_WFYMEAN_VALTH.u32) + u32Data * VID_OFFSET),V0_SNR_WFYMEAN_VALTH.u32);

	return ;
}


HI_VOID VDP_VID_SetYdefaultfiltertype(HI_U32 u32Data, HI_U32 ydefaultfiltertype)
{
	U_V0_SNR_FILTER_TYPE V0_SNR_FILTER_TYPE;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetYdefaultfiltertype Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_FILTER_TYPE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_FILTER_TYPE.u32) + u32Data * VID_OFFSET));
	V0_SNR_FILTER_TYPE.bits.ydefaultfiltertype = ydefaultfiltertype;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_FILTER_TYPE.u32) + u32Data * VID_OFFSET),V0_SNR_FILTER_TYPE.u32);

	return ;
}


HI_VOID VDP_VID_SetNonoisegain(HI_U32 u32Data, HI_U32 nonoisegain)
{
	U_V0_SNR_NOISE_CORE V0_SNR_NOISE_CORE;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetNonoisegain Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_NOISE_CORE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_NOISE_CORE.u32) + u32Data * VID_OFFSET));
	V0_SNR_NOISE_CORE.bits.nonoisegain = nonoisegain;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_NOISE_CORE.u32) + u32Data * VID_OFFSET),V0_SNR_NOISE_CORE.u32);

	return ;
}


HI_VOID VDP_VID_SetNoisecore(HI_U32 u32Data, HI_U32 noisecore)
{
	U_V0_SNR_NOISE_CORE V0_SNR_NOISE_CORE;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetNoisecore Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_NOISE_CORE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_NOISE_CORE.u32) + u32Data * VID_OFFSET));
	V0_SNR_NOISE_CORE.bits.noisecore = noisecore;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_NOISE_CORE.u32) + u32Data * VID_OFFSET),V0_SNR_NOISE_CORE.u32);

	return ;
}


HI_VOID VDP_VID_SetRandyinnoiselevel(HI_U32 u32Data, HI_U32 randyinnoiselevel)
{
	U_V0_SNR_ADD_NOISE V0_SNR_ADD_NOISE;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetRandyinnoiselevel Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_ADD_NOISE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_ADD_NOISE.u32) + u32Data * VID_OFFSET));
	V0_SNR_ADD_NOISE.bits.randyinnoiselevel = randyinnoiselevel;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_ADD_NOISE.u32) + u32Data * VID_OFFSET),V0_SNR_ADD_NOISE.u32);

	return ;
}


HI_VOID VDP_VID_SetAddrandyinnoiseen(HI_U32 u32Data, HI_U32 addrandyinnoiseen)
{
	U_V0_SNR_ADD_NOISE V0_SNR_ADD_NOISE;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetAddrandyinnoiseen Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_ADD_NOISE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_ADD_NOISE.u32) + u32Data * VID_OFFSET));
	V0_SNR_ADD_NOISE.bits.addrandyinnoiseen = addrandyinnoiseen;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_ADD_NOISE.u32) + u32Data * VID_OFFSET),V0_SNR_ADD_NOISE.u32);

	return ;
}

HI_VOID VDP_VID_SetDemomodecoor(HI_U32 u32Data, HI_U32 demomodecoor)
{
	U_V0_SNR_DEMO V0_SNR_DEMO;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetDemomodecoor Select Wrong Layer ID\n");
		return ;
	}

	V0_SNR_DEMO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_SNR_DEMO.u32) + u32Data * VID_OFFSET));
	V0_SNR_DEMO.bits.demomodecoor = demomodecoor;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_SNR_DEMO.u32) + u32Data * VID_OFFSET),V0_SNR_DEMO.u32);

	return ;
}

HI_VOID VDP_VID_SetSnrMotionEdgeLut(HI_U32 u32Data, HI_U32 snrmotionedgelut[16][32])
{
    U_V0_MOTION_EDGE_LUT_01a V0_MOTION_EDGE_LUT_01a;
    U_V0_MOTION_EDGE_LUT_01b V0_MOTION_EDGE_LUT_01b;
    U_V0_MOTION_EDGE_LUT_01c V0_MOTION_EDGE_LUT_01c;
    U_V0_MOTION_EDGE_LUT_01d V0_MOTION_EDGE_LUT_01d;
    U_V0_MOTION_EDGE_LUT_01e V0_MOTION_EDGE_LUT_01e;
    U_V0_MOTION_EDGE_LUT_01f V0_MOTION_EDGE_LUT_01f;
    U_V0_MOTION_EDGE_LUT_01g V0_MOTION_EDGE_LUT_01g;
    U_V0_MOTION_EDGE_LUT_01h V0_MOTION_EDGE_LUT_01h;
#if 0
    U_V0_MOTION_EDGE_LUT_02a V0_MOTION_EDGE_LUT_02a;
    U_V0_MOTION_EDGE_LUT_02b V0_MOTION_EDGE_LUT_02b;
    U_V0_MOTION_EDGE_LUT_02c V0_MOTION_EDGE_LUT_02c;
    U_V0_MOTION_EDGE_LUT_02d V0_MOTION_EDGE_LUT_02d;
    U_V0_MOTION_EDGE_LUT_02e V0_MOTION_EDGE_LUT_02e;
    U_V0_MOTION_EDGE_LUT_02f V0_MOTION_EDGE_LUT_02f;
    U_V0_MOTION_EDGE_LUT_02g V0_MOTION_EDGE_LUT_02g;
    U_V0_MOTION_EDGE_LUT_02h V0_MOTION_EDGE_LUT_02h;
    U_V0_MOTION_EDGE_LUT_03a V0_MOTION_EDGE_LUT_03a;
    U_V0_MOTION_EDGE_LUT_03b V0_MOTION_EDGE_LUT_03b;
    U_V0_MOTION_EDGE_LUT_03c V0_MOTION_EDGE_LUT_03c;
    U_V0_MOTION_EDGE_LUT_03d V0_MOTION_EDGE_LUT_03d;
    U_V0_MOTION_EDGE_LUT_03e V0_MOTION_EDGE_LUT_03e;
    U_V0_MOTION_EDGE_LUT_03f V0_MOTION_EDGE_LUT_03f;
    U_V0_MOTION_EDGE_LUT_03g V0_MOTION_EDGE_LUT_03g;
    U_V0_MOTION_EDGE_LUT_03h V0_MOTION_EDGE_LUT_03h;
    U_V0_MOTION_EDGE_LUT_04a V0_MOTION_EDGE_LUT_04a;
    U_V0_MOTION_EDGE_LUT_04b V0_MOTION_EDGE_LUT_04b;
    U_V0_MOTION_EDGE_LUT_04c V0_MOTION_EDGE_LUT_04c;
    U_V0_MOTION_EDGE_LUT_04d V0_MOTION_EDGE_LUT_04d;
    U_V0_MOTION_EDGE_LUT_04e V0_MOTION_EDGE_LUT_04e;
    U_V0_MOTION_EDGE_LUT_04f V0_MOTION_EDGE_LUT_04f;
    U_V0_MOTION_EDGE_LUT_04g V0_MOTION_EDGE_LUT_04g;
    U_V0_MOTION_EDGE_LUT_04h V0_MOTION_EDGE_LUT_04h;
    U_V0_MOTION_EDGE_LUT_05a V0_MOTION_EDGE_LUT_05a;
    U_V0_MOTION_EDGE_LUT_05b V0_MOTION_EDGE_LUT_05b;
    U_V0_MOTION_EDGE_LUT_05c V0_MOTION_EDGE_LUT_05c;
    U_V0_MOTION_EDGE_LUT_05d V0_MOTION_EDGE_LUT_05d;
    U_V0_MOTION_EDGE_LUT_05e V0_MOTION_EDGE_LUT_05e;
    U_V0_MOTION_EDGE_LUT_05f V0_MOTION_EDGE_LUT_05f;
    U_V0_MOTION_EDGE_LUT_05g V0_MOTION_EDGE_LUT_05g;
    U_V0_MOTION_EDGE_LUT_05h V0_MOTION_EDGE_LUT_05h;
    U_V0_MOTION_EDGE_LUT_06a V0_MOTION_EDGE_LUT_06a;
    U_V0_MOTION_EDGE_LUT_06b V0_MOTION_EDGE_LUT_06b;
    U_V0_MOTION_EDGE_LUT_06c V0_MOTION_EDGE_LUT_06c;
    U_V0_MOTION_EDGE_LUT_06d V0_MOTION_EDGE_LUT_06d;
    U_V0_MOTION_EDGE_LUT_06e V0_MOTION_EDGE_LUT_06e;
    U_V0_MOTION_EDGE_LUT_06f V0_MOTION_EDGE_LUT_06f;
    U_V0_MOTION_EDGE_LUT_06g V0_MOTION_EDGE_LUT_06g;
    U_V0_MOTION_EDGE_LUT_06h V0_MOTION_EDGE_LUT_06h;
    U_V0_MOTION_EDGE_LUT_07a V0_MOTION_EDGE_LUT_07a;
    U_V0_MOTION_EDGE_LUT_07b V0_MOTION_EDGE_LUT_07b;
    U_V0_MOTION_EDGE_LUT_07c V0_MOTION_EDGE_LUT_07c;
    U_V0_MOTION_EDGE_LUT_07d V0_MOTION_EDGE_LUT_07d;
    U_V0_MOTION_EDGE_LUT_07e V0_MOTION_EDGE_LUT_07e;
    U_V0_MOTION_EDGE_LUT_07f V0_MOTION_EDGE_LUT_07f;
    U_V0_MOTION_EDGE_LUT_07g V0_MOTION_EDGE_LUT_07g;
    U_V0_MOTION_EDGE_LUT_07h V0_MOTION_EDGE_LUT_07h;
    U_V0_MOTION_EDGE_LUT_08a V0_MOTION_EDGE_LUT_08a;
    U_V0_MOTION_EDGE_LUT_08b V0_MOTION_EDGE_LUT_08b;
    U_V0_MOTION_EDGE_LUT_08c V0_MOTION_EDGE_LUT_08c;
    U_V0_MOTION_EDGE_LUT_08d V0_MOTION_EDGE_LUT_08d;
    U_V0_MOTION_EDGE_LUT_08e V0_MOTION_EDGE_LUT_08e;
    U_V0_MOTION_EDGE_LUT_08f V0_MOTION_EDGE_LUT_08f;
    U_V0_MOTION_EDGE_LUT_08g V0_MOTION_EDGE_LUT_08g;
    U_V0_MOTION_EDGE_LUT_08h V0_MOTION_EDGE_LUT_08h;
    U_V0_MOTION_EDGE_LUT_09a V0_MOTION_EDGE_LUT_09a;
    U_V0_MOTION_EDGE_LUT_09b V0_MOTION_EDGE_LUT_09b;
    U_V0_MOTION_EDGE_LUT_09c V0_MOTION_EDGE_LUT_09c;
    U_V0_MOTION_EDGE_LUT_09d V0_MOTION_EDGE_LUT_09d;
    U_V0_MOTION_EDGE_LUT_09e V0_MOTION_EDGE_LUT_09e;
    U_V0_MOTION_EDGE_LUT_09f V0_MOTION_EDGE_LUT_09f;
    U_V0_MOTION_EDGE_LUT_09g V0_MOTION_EDGE_LUT_09g;
    U_V0_MOTION_EDGE_LUT_09h V0_MOTION_EDGE_LUT_09h;
    U_V0_MOTION_EDGE_LUT_10a V0_MOTION_EDGE_LUT_10a;
    U_V0_MOTION_EDGE_LUT_10b V0_MOTION_EDGE_LUT_10b;
    U_V0_MOTION_EDGE_LUT_10c V0_MOTION_EDGE_LUT_10c;
    U_V0_MOTION_EDGE_LUT_10d V0_MOTION_EDGE_LUT_10d;
    U_V0_MOTION_EDGE_LUT_10e V0_MOTION_EDGE_LUT_10e;
    U_V0_MOTION_EDGE_LUT_10f V0_MOTION_EDGE_LUT_10f;
    U_V0_MOTION_EDGE_LUT_10g V0_MOTION_EDGE_LUT_10g;
    U_V0_MOTION_EDGE_LUT_10h V0_MOTION_EDGE_LUT_10h;
    U_V0_MOTION_EDGE_LUT_11a V0_MOTION_EDGE_LUT_11a;
    U_V0_MOTION_EDGE_LUT_11b V0_MOTION_EDGE_LUT_11b;
    U_V0_MOTION_EDGE_LUT_11c V0_MOTION_EDGE_LUT_11c;
    U_V0_MOTION_EDGE_LUT_11d V0_MOTION_EDGE_LUT_11d;
    U_V0_MOTION_EDGE_LUT_11e V0_MOTION_EDGE_LUT_11e;
    U_V0_MOTION_EDGE_LUT_11f V0_MOTION_EDGE_LUT_11f;
    U_V0_MOTION_EDGE_LUT_11g V0_MOTION_EDGE_LUT_11g;
    U_V0_MOTION_EDGE_LUT_11h V0_MOTION_EDGE_LUT_11h;
    U_V0_MOTION_EDGE_LUT_12a V0_MOTION_EDGE_LUT_12a;
    U_V0_MOTION_EDGE_LUT_12b V0_MOTION_EDGE_LUT_12b;
    U_V0_MOTION_EDGE_LUT_12c V0_MOTION_EDGE_LUT_12c;
    U_V0_MOTION_EDGE_LUT_12d V0_MOTION_EDGE_LUT_12d;
    U_V0_MOTION_EDGE_LUT_12e V0_MOTION_EDGE_LUT_12e;
    U_V0_MOTION_EDGE_LUT_12f V0_MOTION_EDGE_LUT_12f;
    U_V0_MOTION_EDGE_LUT_12g V0_MOTION_EDGE_LUT_12g;
    U_V0_MOTION_EDGE_LUT_12h V0_MOTION_EDGE_LUT_12h;
    U_V0_MOTION_EDGE_LUT_13a V0_MOTION_EDGE_LUT_13a;
    U_V0_MOTION_EDGE_LUT_13b V0_MOTION_EDGE_LUT_13b;
    U_V0_MOTION_EDGE_LUT_13c V0_MOTION_EDGE_LUT_13c;
    U_V0_MOTION_EDGE_LUT_13d V0_MOTION_EDGE_LUT_13d;
    U_V0_MOTION_EDGE_LUT_13e V0_MOTION_EDGE_LUT_13e;
    U_V0_MOTION_EDGE_LUT_13f V0_MOTION_EDGE_LUT_13f;
    U_V0_MOTION_EDGE_LUT_13g V0_MOTION_EDGE_LUT_13g;
    U_V0_MOTION_EDGE_LUT_13h V0_MOTION_EDGE_LUT_13h;
    U_V0_MOTION_EDGE_LUT_14a V0_MOTION_EDGE_LUT_14a;
    U_V0_MOTION_EDGE_LUT_14b V0_MOTION_EDGE_LUT_14b;
    U_V0_MOTION_EDGE_LUT_14c V0_MOTION_EDGE_LUT_14c;
    U_V0_MOTION_EDGE_LUT_14d V0_MOTION_EDGE_LUT_14d;
    U_V0_MOTION_EDGE_LUT_14e V0_MOTION_EDGE_LUT_14e;
    U_V0_MOTION_EDGE_LUT_14f V0_MOTION_EDGE_LUT_14f;
    U_V0_MOTION_EDGE_LUT_14g V0_MOTION_EDGE_LUT_14g;
    U_V0_MOTION_EDGE_LUT_14h V0_MOTION_EDGE_LUT_14h;
    U_V0_MOTION_EDGE_LUT_15a V0_MOTION_EDGE_LUT_15a;
    U_V0_MOTION_EDGE_LUT_15b V0_MOTION_EDGE_LUT_15b;
    U_V0_MOTION_EDGE_LUT_15c V0_MOTION_EDGE_LUT_15c;
    U_V0_MOTION_EDGE_LUT_15d V0_MOTION_EDGE_LUT_15d;
    U_V0_MOTION_EDGE_LUT_15e V0_MOTION_EDGE_LUT_15e;
    U_V0_MOTION_EDGE_LUT_15f V0_MOTION_EDGE_LUT_15f;
    U_V0_MOTION_EDGE_LUT_15g V0_MOTION_EDGE_LUT_15g;
    U_V0_MOTION_EDGE_LUT_15h V0_MOTION_EDGE_LUT_15h;
    U_V0_MOTION_EDGE_LUT_16a V0_MOTION_EDGE_LUT_16a;
    U_V0_MOTION_EDGE_LUT_16b V0_MOTION_EDGE_LUT_16b;
    U_V0_MOTION_EDGE_LUT_16c V0_MOTION_EDGE_LUT_16c;
    U_V0_MOTION_EDGE_LUT_16d V0_MOTION_EDGE_LUT_16d;
    U_V0_MOTION_EDGE_LUT_16e V0_MOTION_EDGE_LUT_16e;
    U_V0_MOTION_EDGE_LUT_16f V0_MOTION_EDGE_LUT_16f;
    U_V0_MOTION_EDGE_LUT_16g V0_MOTION_EDGE_LUT_16g;
    U_V0_MOTION_EDGE_LUT_16h V0_MOTION_EDGE_LUT_16h;
#endif

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_VID_SetSnrMotionEdgeLut Select Wrong Layer ID\n");
		return ;
	}

#if 0
    V0_MOTION_EDGE_LUT_16h.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_16h.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_16g.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_16g.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_16f.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_16f.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_16e.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_16e.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_16d.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_16d.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_16c.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_16c.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_16b.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_16b.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_16a.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_16a.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_15h.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_15h.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_15g.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_15g.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_15f.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_15f.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_15e.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_15e.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_15d.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_15d.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_15c.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_15c.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_15b.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_15b.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_15a.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_15a.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_14h.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_14h.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_14g.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_14g.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_14f.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_14f.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_14e.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_14e.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_14d.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_14d.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_14c.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_14c.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_14b.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_14b.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_14a.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_14a.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_13h.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_13h.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_13g.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_13g.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_13f.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_13f.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_13e.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_13e.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_13d.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_13d.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_13c.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_13c.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_13b.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_13b.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_13a.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_13a.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_12h.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_12h.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_12g.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_12g.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_12f.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_12f.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_12e.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_12e.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_12d.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_12d.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_12c.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_12c.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_12b.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_12b.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_12a.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_12a.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_11h.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_11h.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_11g.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_11g.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_11f.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_11f.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_11e.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_11e.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_11d.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_11d.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_11c.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_11c.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_11b.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_11b.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_11a.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_11a.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_10h.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_10h.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_10g.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_10g.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_10f.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_10f.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_10e.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_10e.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_10d.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_10d.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_10c.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_10c.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_10b.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_10b.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_10a.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_10a.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_09h.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_09h.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_09g.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_09g.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_09f.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_09f.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_09e.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_09e.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_09d.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_09d.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_09c.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_09c.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_09b.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_09b.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_09a.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_09a.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_08h.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_08h.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_08g.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_08g.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_08f.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_08f.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_08e.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_08e.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_08d.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_08d.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_08c.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_08c.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_08b.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_08b.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_08a.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_08a.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_07h.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_07h.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_07g.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_07g.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_07f.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_07f.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_07e.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_07e.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_07d.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_07d.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_07c.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_07c.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_07b.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_07b.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_07a.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_07a.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_06h.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_06h.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_06g.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_06g.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_06f.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_06f.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_06e.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_06e.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_06d.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_06d.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_06c.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_06c.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_06b.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_06b.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_06a.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_06a.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_05h.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_05h.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_05g.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_05g.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_05f.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_05f.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_05e.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_05e.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_05d.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_05d.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_05c.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_05c.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_05b.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_05b.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_05a.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_05a.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_04h.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_04h.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_04g.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_04g.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_04f.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_04f.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_04e.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_04e.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_04d.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_04d.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_04c.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_04c.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_04b.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_04b.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_04a.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_04a.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_03h.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_03h.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_03g.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_03g.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_03f.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_03f.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_03e.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_03e.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_03d.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_03d.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_03c.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_03c.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_03b.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_03b.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_03a.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_03a.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_02h.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_02h.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_02g.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_02g.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_02f.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_02f.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_02e.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_02e.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_02d.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_02d.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_02c.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_02c.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_02b.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_02b.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_02a.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_02a.u32) + u32Data * VID_OFFSET));
#endif
    V0_MOTION_EDGE_LUT_01h.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_01h.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_01g.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_01g.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_01f.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_01f.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_01e.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_01e.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_01d.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_01d.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_01c.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_01c.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_01b.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_01b.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_01a.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_01a.u32) + u32Data * VID_OFFSET));
    V0_MOTION_EDGE_LUT_01a.bits.snrmotionedgelut_0__0_  = snrmotionedgelut[0][0];
    V0_MOTION_EDGE_LUT_01a.bits.snrmotionedgelut_0__1_  = snrmotionedgelut[0][1];
    V0_MOTION_EDGE_LUT_01a.bits.snrmotionedgelut_0__2_  = snrmotionedgelut[0][2];
    V0_MOTION_EDGE_LUT_01a.bits.snrmotionedgelut_0__3_  = snrmotionedgelut[0][3];
    V0_MOTION_EDGE_LUT_01b.bits.snrmotionedgelut_0__4_  = snrmotionedgelut[0][4];
    V0_MOTION_EDGE_LUT_01b.bits.snrmotionedgelut_0__5_  = snrmotionedgelut[0][5];
    V0_MOTION_EDGE_LUT_01b.bits.snrmotionedgelut_0__6_  = snrmotionedgelut[0][6];
    V0_MOTION_EDGE_LUT_01b.bits.snrmotionedgelut_0__7_  = snrmotionedgelut[0][7];
    V0_MOTION_EDGE_LUT_01c.bits.snrmotionedgelut_0__8_  = snrmotionedgelut[0][8];
    V0_MOTION_EDGE_LUT_01c.bits.snrmotionedgelut_0__9_  = snrmotionedgelut[0][9];
    V0_MOTION_EDGE_LUT_01c.bits.snrmotionedgelut_0__10_ = snrmotionedgelut[0][10];
    V0_MOTION_EDGE_LUT_01c.bits.snrmotionedgelut_0__11_ = snrmotionedgelut[0][11];
    V0_MOTION_EDGE_LUT_01d.bits.snrmotionedgelut_0__12_ = snrmotionedgelut[0][12];
    V0_MOTION_EDGE_LUT_01d.bits.snrmotionedgelut_0__13_ = snrmotionedgelut[0][13];
    V0_MOTION_EDGE_LUT_01d.bits.snrmotionedgelut_0__14_ = snrmotionedgelut[0][14];
    V0_MOTION_EDGE_LUT_01d.bits.snrmotionedgelut_0__15_ = snrmotionedgelut[0][15];
    V0_MOTION_EDGE_LUT_01e.bits.snrmotionedgelut_0__16_ = snrmotionedgelut[0][16];
    V0_MOTION_EDGE_LUT_01e.bits.snrmotionedgelut_0__17_ = snrmotionedgelut[0][17];
    V0_MOTION_EDGE_LUT_01e.bits.snrmotionedgelut_0__18_ = snrmotionedgelut[0][18];
    V0_MOTION_EDGE_LUT_01e.bits.snrmotionedgelut_0__19_ = snrmotionedgelut[0][19];
    V0_MOTION_EDGE_LUT_01f.bits.snrmotionedgelut_0__20_ = snrmotionedgelut[0][20];
    V0_MOTION_EDGE_LUT_01f.bits.snrmotionedgelut_0__21_ = snrmotionedgelut[0][21];
    V0_MOTION_EDGE_LUT_01f.bits.snrmotionedgelut_0__22_ = snrmotionedgelut[0][22];
    V0_MOTION_EDGE_LUT_01f.bits.snrmotionedgelut_0__23_ = snrmotionedgelut[0][23];
    V0_MOTION_EDGE_LUT_01g.bits.snrmotionedgelut_0__24_ = snrmotionedgelut[0][24];
    V0_MOTION_EDGE_LUT_01g.bits.snrmotionedgelut_0__25_ = snrmotionedgelut[0][25];
    V0_MOTION_EDGE_LUT_01g.bits.snrmotionedgelut_0__26_ = snrmotionedgelut[0][26];
    V0_MOTION_EDGE_LUT_01g.bits.snrmotionedgelut_0__27_ = snrmotionedgelut[0][27];
    V0_MOTION_EDGE_LUT_01h.bits.snrmotionedgelut_0__28_ = snrmotionedgelut[0][28];
    V0_MOTION_EDGE_LUT_01h.bits.snrmotionedgelut_0__29_ = snrmotionedgelut[0][29];
    V0_MOTION_EDGE_LUT_01h.bits.snrmotionedgelut_0__30_ = snrmotionedgelut[0][30];
    V0_MOTION_EDGE_LUT_01h.bits.snrmotionedgelut_0__31_ = snrmotionedgelut[0][31];
#if 0
    V0_MOTION_EDGE_LUT_02a.bits.snrmotionedgelut_1__0_  = snrmotionedgelut[1][0];
    V0_MOTION_EDGE_LUT_02a.bits.snrmotionedgelut_1__1_  = snrmotionedgelut[1][1];
    V0_MOTION_EDGE_LUT_02a.bits.snrmotionedgelut_1__2_  = snrmotionedgelut[1][2];
    V0_MOTION_EDGE_LUT_02a.bits.snrmotionedgelut_1__3_  = snrmotionedgelut[1][3];
    V0_MOTION_EDGE_LUT_02b.bits.snrmotionedgelut_1__4_  = snrmotionedgelut[1][4];
    V0_MOTION_EDGE_LUT_02b.bits.snrmotionedgelut_1__5_  = snrmotionedgelut[1][5];
    V0_MOTION_EDGE_LUT_02b.bits.snrmotionedgelut_1__6_  = snrmotionedgelut[1][6];
    V0_MOTION_EDGE_LUT_02b.bits.snrmotionedgelut_1__7_  = snrmotionedgelut[1][7];
    V0_MOTION_EDGE_LUT_02c.bits.snrmotionedgelut_1__8_  = snrmotionedgelut[1][8];
    V0_MOTION_EDGE_LUT_02c.bits.snrmotionedgelut_1__9_  = snrmotionedgelut[1][9];
    V0_MOTION_EDGE_LUT_02c.bits.snrmotionedgelut_1__10_ = snrmotionedgelut[1][10];
    V0_MOTION_EDGE_LUT_02c.bits.snrmotionedgelut_1__11_ = snrmotionedgelut[1][11];
    V0_MOTION_EDGE_LUT_02d.bits.snrmotionedgelut_1__12_ = snrmotionedgelut[1][12];
    V0_MOTION_EDGE_LUT_02d.bits.snrmotionedgelut_1__13_ = snrmotionedgelut[1][13];
    V0_MOTION_EDGE_LUT_02d.bits.snrmotionedgelut_1__14_ = snrmotionedgelut[1][14];
    V0_MOTION_EDGE_LUT_02d.bits.snrmotionedgelut_1__15_ = snrmotionedgelut[1][15];
    V0_MOTION_EDGE_LUT_02e.bits.snrmotionedgelut_1__16_ = snrmotionedgelut[1][16];
    V0_MOTION_EDGE_LUT_02e.bits.snrmotionedgelut_1__17_ = snrmotionedgelut[1][17];
    V0_MOTION_EDGE_LUT_02e.bits.snrmotionedgelut_1__18_ = snrmotionedgelut[1][18];
    V0_MOTION_EDGE_LUT_02e.bits.snrmotionedgelut_1__19_ = snrmotionedgelut[1][19];
    V0_MOTION_EDGE_LUT_02f.bits.snrmotionedgelut_1__20_ = snrmotionedgelut[1][20];
    V0_MOTION_EDGE_LUT_02f.bits.snrmotionedgelut_1__21_ = snrmotionedgelut[1][21];
    V0_MOTION_EDGE_LUT_02f.bits.snrmotionedgelut_1__22_ = snrmotionedgelut[1][22];
    V0_MOTION_EDGE_LUT_02f.bits.snrmotionedgelut_1__23_ = snrmotionedgelut[1][23];
    V0_MOTION_EDGE_LUT_02g.bits.snrmotionedgelut_1__24_ = snrmotionedgelut[1][24];
    V0_MOTION_EDGE_LUT_02g.bits.snrmotionedgelut_1__25_ = snrmotionedgelut[1][25];
    V0_MOTION_EDGE_LUT_02g.bits.snrmotionedgelut_1__26_ = snrmotionedgelut[1][26];
    V0_MOTION_EDGE_LUT_02g.bits.snrmotionedgelut_1__27_ = snrmotionedgelut[1][27];
    V0_MOTION_EDGE_LUT_02h.bits.snrmotionedgelut_1__28_ = snrmotionedgelut[1][28];
    V0_MOTION_EDGE_LUT_02h.bits.snrmotionedgelut_1__29_ = snrmotionedgelut[1][29];
    V0_MOTION_EDGE_LUT_02h.bits.snrmotionedgelut_1__30_ = snrmotionedgelut[1][30];
    V0_MOTION_EDGE_LUT_02h.bits.snrmotionedgelut_1__31_ = snrmotionedgelut[1][31];
    V0_MOTION_EDGE_LUT_03a.bits.snrmotionedgelut_2__0_  = snrmotionedgelut[2][0];
    V0_MOTION_EDGE_LUT_03a.bits.snrmotionedgelut_2__1_  = snrmotionedgelut[2][1];
    V0_MOTION_EDGE_LUT_03a.bits.snrmotionedgelut_2__2_  = snrmotionedgelut[2][2];
    V0_MOTION_EDGE_LUT_03a.bits.snrmotionedgelut_2__3_  = snrmotionedgelut[2][3];
    V0_MOTION_EDGE_LUT_03b.bits.snrmotionedgelut_2__4_  = snrmotionedgelut[2][4];
    V0_MOTION_EDGE_LUT_03b.bits.snrmotionedgelut_2__5_  = snrmotionedgelut[2][5];
    V0_MOTION_EDGE_LUT_03b.bits.snrmotionedgelut_2__6_  = snrmotionedgelut[2][6];
    V0_MOTION_EDGE_LUT_03b.bits.snrmotionedgelut_2__7_  = snrmotionedgelut[2][7];
    V0_MOTION_EDGE_LUT_03c.bits.snrmotionedgelut_2__8_  = snrmotionedgelut[2][8];
    V0_MOTION_EDGE_LUT_03c.bits.snrmotionedgelut_2__9_  = snrmotionedgelut[2][9];
    V0_MOTION_EDGE_LUT_03c.bits.snrmotionedgelut_2__10_ = snrmotionedgelut[2][10];
    V0_MOTION_EDGE_LUT_03c.bits.snrmotionedgelut_2__11_ = snrmotionedgelut[2][11];
    V0_MOTION_EDGE_LUT_03d.bits.snrmotionedgelut_2__12_ = snrmotionedgelut[2][12];
    V0_MOTION_EDGE_LUT_03d.bits.snrmotionedgelut_2__13_ = snrmotionedgelut[2][13];
    V0_MOTION_EDGE_LUT_03d.bits.snrmotionedgelut_2__14_ = snrmotionedgelut[2][14];
    V0_MOTION_EDGE_LUT_03d.bits.snrmotionedgelut_2__15_ = snrmotionedgelut[2][15];
    V0_MOTION_EDGE_LUT_03e.bits.snrmotionedgelut_2__16_ = snrmotionedgelut[2][16];
    V0_MOTION_EDGE_LUT_03e.bits.snrmotionedgelut_2__17_ = snrmotionedgelut[2][17];
    V0_MOTION_EDGE_LUT_03e.bits.snrmotionedgelut_2__18_ = snrmotionedgelut[2][18];
    V0_MOTION_EDGE_LUT_03e.bits.snrmotionedgelut_2__19_ = snrmotionedgelut[2][19];
    V0_MOTION_EDGE_LUT_03f.bits.snrmotionedgelut_2__20_ = snrmotionedgelut[2][20];
    V0_MOTION_EDGE_LUT_03f.bits.snrmotionedgelut_2__21_ = snrmotionedgelut[2][21];
    V0_MOTION_EDGE_LUT_03f.bits.snrmotionedgelut_2__22_ = snrmotionedgelut[2][22];
    V0_MOTION_EDGE_LUT_03f.bits.snrmotionedgelut_2__23_ = snrmotionedgelut[2][23];
    V0_MOTION_EDGE_LUT_03g.bits.snrmotionedgelut_2__24_ = snrmotionedgelut[2][24];
    V0_MOTION_EDGE_LUT_03g.bits.snrmotionedgelut_2__25_ = snrmotionedgelut[2][25];
    V0_MOTION_EDGE_LUT_03g.bits.snrmotionedgelut_2__26_ = snrmotionedgelut[2][26];
    V0_MOTION_EDGE_LUT_03g.bits.snrmotionedgelut_2__27_ = snrmotionedgelut[2][27];
    V0_MOTION_EDGE_LUT_03h.bits.snrmotionedgelut_2__28_ = snrmotionedgelut[2][28];
    V0_MOTION_EDGE_LUT_03h.bits.snrmotionedgelut_2__29_ = snrmotionedgelut[2][29];
    V0_MOTION_EDGE_LUT_03h.bits.snrmotionedgelut_2__30_ = snrmotionedgelut[2][30];
    V0_MOTION_EDGE_LUT_03h.bits.snrmotionedgelut_2__31_ = snrmotionedgelut[2][31];
    V0_MOTION_EDGE_LUT_04a.bits.snrmotionedgelut_3__0_  = snrmotionedgelut[3][0];
    V0_MOTION_EDGE_LUT_04a.bits.snrmotionedgelut_3__1_  = snrmotionedgelut[3][1];
    V0_MOTION_EDGE_LUT_04a.bits.snrmotionedgelut_3__2_  = snrmotionedgelut[3][2];
    V0_MOTION_EDGE_LUT_04a.bits.snrmotionedgelut_3__3_  = snrmotionedgelut[3][3];
    V0_MOTION_EDGE_LUT_04b.bits.snrmotionedgelut_3__4_  = snrmotionedgelut[3][4];
    V0_MOTION_EDGE_LUT_04b.bits.snrmotionedgelut_3__5_  = snrmotionedgelut[3][5];
    V0_MOTION_EDGE_LUT_04b.bits.snrmotionedgelut_3__6_  = snrmotionedgelut[3][6];
    V0_MOTION_EDGE_LUT_04b.bits.snrmotionedgelut_3__7_  = snrmotionedgelut[3][7];
    V0_MOTION_EDGE_LUT_04c.bits.snrmotionedgelut_3__8_  = snrmotionedgelut[3][8];
    V0_MOTION_EDGE_LUT_04c.bits.snrmotionedgelut_3__9_  = snrmotionedgelut[3][9];
    V0_MOTION_EDGE_LUT_04c.bits.snrmotionedgelut_3__10_ = snrmotionedgelut[3][10];
    V0_MOTION_EDGE_LUT_04c.bits.snrmotionedgelut_3__11_ = snrmotionedgelut[3][11];
    V0_MOTION_EDGE_LUT_04d.bits.snrmotionedgelut_3__12_ = snrmotionedgelut[3][12];
    V0_MOTION_EDGE_LUT_04d.bits.snrmotionedgelut_3__13_ = snrmotionedgelut[3][13];
    V0_MOTION_EDGE_LUT_04d.bits.snrmotionedgelut_3__14_ = snrmotionedgelut[3][14];
    V0_MOTION_EDGE_LUT_04d.bits.snrmotionedgelut_3__15_ = snrmotionedgelut[3][15];
    V0_MOTION_EDGE_LUT_04e.bits.snrmotionedgelut_3__16_ = snrmotionedgelut[3][16];
    V0_MOTION_EDGE_LUT_04e.bits.snrmotionedgelut_3__17_ = snrmotionedgelut[3][17];
    V0_MOTION_EDGE_LUT_04e.bits.snrmotionedgelut_3__18_ = snrmotionedgelut[3][18];
    V0_MOTION_EDGE_LUT_04e.bits.snrmotionedgelut_3__19_ = snrmotionedgelut[3][19];
    V0_MOTION_EDGE_LUT_04f.bits.snrmotionedgelut_3__20_ = snrmotionedgelut[3][20];
    V0_MOTION_EDGE_LUT_04f.bits.snrmotionedgelut_3__21_ = snrmotionedgelut[3][21];
    V0_MOTION_EDGE_LUT_04f.bits.snrmotionedgelut_3__22_ = snrmotionedgelut[3][22];
    V0_MOTION_EDGE_LUT_04f.bits.snrmotionedgelut_3__23_ = snrmotionedgelut[3][23];
    V0_MOTION_EDGE_LUT_04g.bits.snrmotionedgelut_3__24_ = snrmotionedgelut[3][24];
    V0_MOTION_EDGE_LUT_04g.bits.snrmotionedgelut_3__25_ = snrmotionedgelut[3][25];
    V0_MOTION_EDGE_LUT_04g.bits.snrmotionedgelut_3__26_ = snrmotionedgelut[3][26];
    V0_MOTION_EDGE_LUT_04g.bits.snrmotionedgelut_3__27_ = snrmotionedgelut[3][27];
    V0_MOTION_EDGE_LUT_04h.bits.snrmotionedgelut_3__28_ = snrmotionedgelut[3][28];
    V0_MOTION_EDGE_LUT_04h.bits.snrmotionedgelut_3__29_ = snrmotionedgelut[3][29];
    V0_MOTION_EDGE_LUT_04h.bits.snrmotionedgelut_3__30_ = snrmotionedgelut[3][30];
    V0_MOTION_EDGE_LUT_04h.bits.snrmotionedgelut_3__31_ = snrmotionedgelut[3][31];
    V0_MOTION_EDGE_LUT_05a.bits.snrmotionedgelut_4__0_  = snrmotionedgelut[4][0];
    V0_MOTION_EDGE_LUT_05a.bits.snrmotionedgelut_4__1_  = snrmotionedgelut[4][1];
    V0_MOTION_EDGE_LUT_05a.bits.snrmotionedgelut_4__2_  = snrmotionedgelut[4][2];
    V0_MOTION_EDGE_LUT_05a.bits.snrmotionedgelut_4__3_  = snrmotionedgelut[4][3];
    V0_MOTION_EDGE_LUT_05b.bits.snrmotionedgelut_4__4_  = snrmotionedgelut[4][4];
    V0_MOTION_EDGE_LUT_05b.bits.snrmotionedgelut_4__5_  = snrmotionedgelut[4][5];
    V0_MOTION_EDGE_LUT_05b.bits.snrmotionedgelut_4__6_  = snrmotionedgelut[4][6];
    V0_MOTION_EDGE_LUT_05b.bits.snrmotionedgelut_4__7_  = snrmotionedgelut[4][7];
    V0_MOTION_EDGE_LUT_05c.bits.snrmotionedgelut_4__8_  = snrmotionedgelut[4][8];
    V0_MOTION_EDGE_LUT_05c.bits.snrmotionedgelut_4__9_  = snrmotionedgelut[4][9];
    V0_MOTION_EDGE_LUT_05c.bits.snrmotionedgelut_4__10_ = snrmotionedgelut[4][10];
    V0_MOTION_EDGE_LUT_05c.bits.snrmotionedgelut_4__11_ = snrmotionedgelut[4][11];
    V0_MOTION_EDGE_LUT_05d.bits.snrmotionedgelut_4__12_ = snrmotionedgelut[4][12];
    V0_MOTION_EDGE_LUT_05d.bits.snrmotionedgelut_4__13_ = snrmotionedgelut[4][13];
    V0_MOTION_EDGE_LUT_05d.bits.snrmotionedgelut_4__14_ = snrmotionedgelut[4][14];
    V0_MOTION_EDGE_LUT_05d.bits.snrmotionedgelut_4__15_ = snrmotionedgelut[4][15];
    V0_MOTION_EDGE_LUT_05e.bits.snrmotionedgelut_4__16_ = snrmotionedgelut[4][16];
    V0_MOTION_EDGE_LUT_05e.bits.snrmotionedgelut_4__17_ = snrmotionedgelut[4][17];
    V0_MOTION_EDGE_LUT_05e.bits.snrmotionedgelut_4__18_ = snrmotionedgelut[4][18];
    V0_MOTION_EDGE_LUT_05e.bits.snrmotionedgelut_4__19_ = snrmotionedgelut[4][19];
    V0_MOTION_EDGE_LUT_05f.bits.snrmotionedgelut_4__20_ = snrmotionedgelut[4][20];
    V0_MOTION_EDGE_LUT_05f.bits.snrmotionedgelut_4__21_ = snrmotionedgelut[4][21];
    V0_MOTION_EDGE_LUT_05f.bits.snrmotionedgelut_4__22_ = snrmotionedgelut[4][22];
    V0_MOTION_EDGE_LUT_05f.bits.snrmotionedgelut_4__23_ = snrmotionedgelut[4][23];
    V0_MOTION_EDGE_LUT_05g.bits.snrmotionedgelut_4__24_ = snrmotionedgelut[4][24];
    V0_MOTION_EDGE_LUT_05g.bits.snrmotionedgelut_4__25_ = snrmotionedgelut[4][25];
    V0_MOTION_EDGE_LUT_05g.bits.snrmotionedgelut_4__26_ = snrmotionedgelut[4][26];
    V0_MOTION_EDGE_LUT_05g.bits.snrmotionedgelut_4__27_ = snrmotionedgelut[4][27];
    V0_MOTION_EDGE_LUT_05h.bits.snrmotionedgelut_4__28_ = snrmotionedgelut[4][28];
    V0_MOTION_EDGE_LUT_05h.bits.snrmotionedgelut_4__29_ = snrmotionedgelut[4][29];
    V0_MOTION_EDGE_LUT_05h.bits.snrmotionedgelut_4__30_ = snrmotionedgelut[4][30];
    V0_MOTION_EDGE_LUT_05h.bits.snrmotionedgelut_4__31_ = snrmotionedgelut[4][31];
    V0_MOTION_EDGE_LUT_06a.bits.snrmotionedgelut_5__0_  = snrmotionedgelut[5][0];
    V0_MOTION_EDGE_LUT_06a.bits.snrmotionedgelut_5__1_  = snrmotionedgelut[5][1];
    V0_MOTION_EDGE_LUT_06a.bits.snrmotionedgelut_5__2_  = snrmotionedgelut[5][2];
    V0_MOTION_EDGE_LUT_06a.bits.snrmotionedgelut_5__3_  = snrmotionedgelut[5][3];
    V0_MOTION_EDGE_LUT_06b.bits.snrmotionedgelut_5__4_  = snrmotionedgelut[5][4];
    V0_MOTION_EDGE_LUT_06b.bits.snrmotionedgelut_5__5_  = snrmotionedgelut[5][5];
    V0_MOTION_EDGE_LUT_06b.bits.snrmotionedgelut_5__6_  = snrmotionedgelut[5][6];
    V0_MOTION_EDGE_LUT_06b.bits.snrmotionedgelut_5__7_  = snrmotionedgelut[5][7];
    V0_MOTION_EDGE_LUT_06c.bits.snrmotionedgelut_5__8_  = snrmotionedgelut[5][8];
    V0_MOTION_EDGE_LUT_06c.bits.snrmotionedgelut_5__9_  = snrmotionedgelut[5][9];
    V0_MOTION_EDGE_LUT_06c.bits.snrmotionedgelut_5__10_ = snrmotionedgelut[5][10];
    V0_MOTION_EDGE_LUT_06c.bits.snrmotionedgelut_5__11_ = snrmotionedgelut[5][11];
    V0_MOTION_EDGE_LUT_06d.bits.snrmotionedgelut_5__12_ = snrmotionedgelut[5][12];
    V0_MOTION_EDGE_LUT_06d.bits.snrmotionedgelut_5__13_ = snrmotionedgelut[5][13];
    V0_MOTION_EDGE_LUT_06d.bits.snrmotionedgelut_5__14_ = snrmotionedgelut[5][14];
    V0_MOTION_EDGE_LUT_06d.bits.snrmotionedgelut_5__15_ = snrmotionedgelut[5][15];
    V0_MOTION_EDGE_LUT_06e.bits.snrmotionedgelut_5__16_ = snrmotionedgelut[5][16];
    V0_MOTION_EDGE_LUT_06e.bits.snrmotionedgelut_5__17_ = snrmotionedgelut[5][17];
    V0_MOTION_EDGE_LUT_06e.bits.snrmotionedgelut_5__18_ = snrmotionedgelut[5][18];
    V0_MOTION_EDGE_LUT_06e.bits.snrmotionedgelut_5__19_ = snrmotionedgelut[5][19];
    V0_MOTION_EDGE_LUT_06f.bits.snrmotionedgelut_5__20_ = snrmotionedgelut[5][20];
    V0_MOTION_EDGE_LUT_06f.bits.snrmotionedgelut_5__21_ = snrmotionedgelut[5][21];
    V0_MOTION_EDGE_LUT_06f.bits.snrmotionedgelut_5__22_ = snrmotionedgelut[5][22];
    V0_MOTION_EDGE_LUT_06f.bits.snrmotionedgelut_5__23_ = snrmotionedgelut[5][23];
    V0_MOTION_EDGE_LUT_06g.bits.snrmotionedgelut_5__24_ = snrmotionedgelut[5][24];
    V0_MOTION_EDGE_LUT_06g.bits.snrmotionedgelut_5__25_ = snrmotionedgelut[5][25];
    V0_MOTION_EDGE_LUT_06g.bits.snrmotionedgelut_5__26_ = snrmotionedgelut[5][26];
    V0_MOTION_EDGE_LUT_06g.bits.snrmotionedgelut_5__27_ = snrmotionedgelut[5][27];
    V0_MOTION_EDGE_LUT_06h.bits.snrmotionedgelut_5__28_ = snrmotionedgelut[5][28];
    V0_MOTION_EDGE_LUT_06h.bits.snrmotionedgelut_5__29_ = snrmotionedgelut[5][29];
    V0_MOTION_EDGE_LUT_06h.bits.snrmotionedgelut_5__30_ = snrmotionedgelut[5][30];
    V0_MOTION_EDGE_LUT_06h.bits.snrmotionedgelut_5__31_ = snrmotionedgelut[5][31];
    V0_MOTION_EDGE_LUT_07a.bits.snrmotionedgelut_6__0_  = snrmotionedgelut[6][0];
    V0_MOTION_EDGE_LUT_07a.bits.snrmotionedgelut_6__1_  = snrmotionedgelut[6][1];
    V0_MOTION_EDGE_LUT_07a.bits.snrmotionedgelut_6__2_  = snrmotionedgelut[6][2];
    V0_MOTION_EDGE_LUT_07a.bits.snrmotionedgelut_6__3_  = snrmotionedgelut[6][3];
    V0_MOTION_EDGE_LUT_07b.bits.snrmotionedgelut_6__4_  = snrmotionedgelut[6][4];
    V0_MOTION_EDGE_LUT_07b.bits.snrmotionedgelut_6__5_  = snrmotionedgelut[6][5];
    V0_MOTION_EDGE_LUT_07b.bits.snrmotionedgelut_6__6_  = snrmotionedgelut[6][6];
    V0_MOTION_EDGE_LUT_07b.bits.snrmotionedgelut_6__7_  = snrmotionedgelut[6][7];
    V0_MOTION_EDGE_LUT_07c.bits.snrmotionedgelut_6__8_  = snrmotionedgelut[6][8];
    V0_MOTION_EDGE_LUT_07c.bits.snrmotionedgelut_6__9_  = snrmotionedgelut[6][9];
    V0_MOTION_EDGE_LUT_07c.bits.snrmotionedgelut_6__10_ = snrmotionedgelut[6][10];
    V0_MOTION_EDGE_LUT_07c.bits.snrmotionedgelut_6__11_ = snrmotionedgelut[6][11];
    V0_MOTION_EDGE_LUT_07d.bits.snrmotionedgelut_6__12_ = snrmotionedgelut[6][12];
    V0_MOTION_EDGE_LUT_07d.bits.snrmotionedgelut_6__13_ = snrmotionedgelut[6][13];
    V0_MOTION_EDGE_LUT_07d.bits.snrmotionedgelut_6__14_ = snrmotionedgelut[6][14];
    V0_MOTION_EDGE_LUT_07d.bits.snrmotionedgelut_6__15_ = snrmotionedgelut[6][15];
    V0_MOTION_EDGE_LUT_07e.bits.snrmotionedgelut_6__16_ = snrmotionedgelut[6][16];
    V0_MOTION_EDGE_LUT_07e.bits.snrmotionedgelut_6__17_ = snrmotionedgelut[6][17];
    V0_MOTION_EDGE_LUT_07e.bits.snrmotionedgelut_6__18_ = snrmotionedgelut[6][18];
    V0_MOTION_EDGE_LUT_07e.bits.snrmotionedgelut_6__19_ = snrmotionedgelut[6][19];
    V0_MOTION_EDGE_LUT_07f.bits.snrmotionedgelut_6__20_ = snrmotionedgelut[6][20];
    V0_MOTION_EDGE_LUT_07f.bits.snrmotionedgelut_6__21_ = snrmotionedgelut[6][21];
    V0_MOTION_EDGE_LUT_07f.bits.snrmotionedgelut_6__22_ = snrmotionedgelut[6][22];
    V0_MOTION_EDGE_LUT_07f.bits.snrmotionedgelut_6__23_ = snrmotionedgelut[6][23];
    V0_MOTION_EDGE_LUT_07g.bits.snrmotionedgelut_6__24_ = snrmotionedgelut[6][24];
    V0_MOTION_EDGE_LUT_07g.bits.snrmotionedgelut_6__25_ = snrmotionedgelut[6][25];
    V0_MOTION_EDGE_LUT_07g.bits.snrmotionedgelut_6__26_ = snrmotionedgelut[6][26];
    V0_MOTION_EDGE_LUT_07g.bits.snrmotionedgelut_6__27_ = snrmotionedgelut[6][27];
    V0_MOTION_EDGE_LUT_07h.bits.snrmotionedgelut_6__28_ = snrmotionedgelut[6][28];
    V0_MOTION_EDGE_LUT_07h.bits.snrmotionedgelut_6__29_ = snrmotionedgelut[6][29];
    V0_MOTION_EDGE_LUT_07h.bits.snrmotionedgelut_6__30_ = snrmotionedgelut[6][30];
    V0_MOTION_EDGE_LUT_07h.bits.snrmotionedgelut_6__31_ = snrmotionedgelut[6][31];
    V0_MOTION_EDGE_LUT_08a.bits.snrmotionedgelut_7__0_  = snrmotionedgelut[7][0];
    V0_MOTION_EDGE_LUT_08a.bits.snrmotionedgelut_7__1_  = snrmotionedgelut[7][1];
    V0_MOTION_EDGE_LUT_08a.bits.snrmotionedgelut_7__2_  = snrmotionedgelut[7][2];
    V0_MOTION_EDGE_LUT_08a.bits.snrmotionedgelut_7__3_  = snrmotionedgelut[7][3];
    V0_MOTION_EDGE_LUT_08b.bits.snrmotionedgelut_7__4_  = snrmotionedgelut[7][4];
    V0_MOTION_EDGE_LUT_08b.bits.snrmotionedgelut_7__5_  = snrmotionedgelut[7][5];
    V0_MOTION_EDGE_LUT_08b.bits.snrmotionedgelut_7__6_  = snrmotionedgelut[7][6];
    V0_MOTION_EDGE_LUT_08b.bits.snrmotionedgelut_7__7_  = snrmotionedgelut[7][7];
    V0_MOTION_EDGE_LUT_08c.bits.snrmotionedgelut_7__8_  = snrmotionedgelut[7][8];
    V0_MOTION_EDGE_LUT_08c.bits.snrmotionedgelut_7__9_  = snrmotionedgelut[7][9];
    V0_MOTION_EDGE_LUT_08c.bits.snrmotionedgelut_7__10_ = snrmotionedgelut[7][10];
    V0_MOTION_EDGE_LUT_08c.bits.snrmotionedgelut_7__11_ = snrmotionedgelut[7][11];
    V0_MOTION_EDGE_LUT_08d.bits.snrmotionedgelut_7__12_ = snrmotionedgelut[7][12];
    V0_MOTION_EDGE_LUT_08d.bits.snrmotionedgelut_7__13_ = snrmotionedgelut[7][13];
    V0_MOTION_EDGE_LUT_08d.bits.snrmotionedgelut_7__14_ = snrmotionedgelut[7][14];
    V0_MOTION_EDGE_LUT_08d.bits.snrmotionedgelut_7__15_ = snrmotionedgelut[7][15];
    V0_MOTION_EDGE_LUT_08e.bits.snrmotionedgelut_7__16_ = snrmotionedgelut[7][16];
    V0_MOTION_EDGE_LUT_08e.bits.snrmotionedgelut_7__17_ = snrmotionedgelut[7][17];
    V0_MOTION_EDGE_LUT_08e.bits.snrmotionedgelut_7__18_ = snrmotionedgelut[7][18];
    V0_MOTION_EDGE_LUT_08e.bits.snrmotionedgelut_7__19_ = snrmotionedgelut[7][19];
    V0_MOTION_EDGE_LUT_08f.bits.snrmotionedgelut_7__20_ = snrmotionedgelut[7][20];
    V0_MOTION_EDGE_LUT_08f.bits.snrmotionedgelut_7__21_ = snrmotionedgelut[7][21];
    V0_MOTION_EDGE_LUT_08f.bits.snrmotionedgelut_7__22_ = snrmotionedgelut[7][22];
    V0_MOTION_EDGE_LUT_08f.bits.snrmotionedgelut_7__23_ = snrmotionedgelut[7][23];
    V0_MOTION_EDGE_LUT_08g.bits.snrmotionedgelut_7__24_ = snrmotionedgelut[7][24];
    V0_MOTION_EDGE_LUT_08g.bits.snrmotionedgelut_7__25_ = snrmotionedgelut[7][25];
    V0_MOTION_EDGE_LUT_08g.bits.snrmotionedgelut_7__26_ = snrmotionedgelut[7][26];
    V0_MOTION_EDGE_LUT_08g.bits.snrmotionedgelut_7__27_ = snrmotionedgelut[7][27];
    V0_MOTION_EDGE_LUT_08h.bits.snrmotionedgelut_7__28_ = snrmotionedgelut[7][28];
    V0_MOTION_EDGE_LUT_08h.bits.snrmotionedgelut_7__29_ = snrmotionedgelut[7][29];
    V0_MOTION_EDGE_LUT_08h.bits.snrmotionedgelut_7__30_ = snrmotionedgelut[7][30];
    V0_MOTION_EDGE_LUT_08h.bits.snrmotionedgelut_7__31_ = snrmotionedgelut[7][31];
    V0_MOTION_EDGE_LUT_09a.bits.snrmotionedgelut_8__0_  = snrmotionedgelut[8][0];
    V0_MOTION_EDGE_LUT_09a.bits.snrmotionedgelut_8__1_  = snrmotionedgelut[8][1];
    V0_MOTION_EDGE_LUT_09a.bits.snrmotionedgelut_8__2_  = snrmotionedgelut[8][2];
    V0_MOTION_EDGE_LUT_09a.bits.snrmotionedgelut_8__3_  = snrmotionedgelut[8][3];
    V0_MOTION_EDGE_LUT_09b.bits.snrmotionedgelut_8__4_  = snrmotionedgelut[8][4];
    V0_MOTION_EDGE_LUT_09b.bits.snrmotionedgelut_8__5_  = snrmotionedgelut[8][5];
    V0_MOTION_EDGE_LUT_09b.bits.snrmotionedgelut_8__6_  = snrmotionedgelut[8][6];
    V0_MOTION_EDGE_LUT_09b.bits.snrmotionedgelut_8__7_  = snrmotionedgelut[8][7];
    V0_MOTION_EDGE_LUT_09c.bits.snrmotionedgelut_8__8_  = snrmotionedgelut[8][8];
    V0_MOTION_EDGE_LUT_09c.bits.snrmotionedgelut_8__9_  = snrmotionedgelut[8][9];
    V0_MOTION_EDGE_LUT_09c.bits.snrmotionedgelut_8__10_ = snrmotionedgelut[8][10];
    V0_MOTION_EDGE_LUT_09c.bits.snrmotionedgelut_8__11_ = snrmotionedgelut[8][11];
    V0_MOTION_EDGE_LUT_09d.bits.snrmotionedgelut_8__12_ = snrmotionedgelut[8][12];
    V0_MOTION_EDGE_LUT_09d.bits.snrmotionedgelut_8__13_ = snrmotionedgelut[8][13];
    V0_MOTION_EDGE_LUT_09d.bits.snrmotionedgelut_8__14_ = snrmotionedgelut[8][14];
    V0_MOTION_EDGE_LUT_09d.bits.snrmotionedgelut_8__15_ = snrmotionedgelut[8][15];
    V0_MOTION_EDGE_LUT_09e.bits.snrmotionedgelut_8__16_ = snrmotionedgelut[8][16];
    V0_MOTION_EDGE_LUT_09e.bits.snrmotionedgelut_8__17_ = snrmotionedgelut[8][17];
    V0_MOTION_EDGE_LUT_09e.bits.snrmotionedgelut_8__18_ = snrmotionedgelut[8][18];
    V0_MOTION_EDGE_LUT_09e.bits.snrmotionedgelut_8__19_ = snrmotionedgelut[8][19];
    V0_MOTION_EDGE_LUT_09f.bits.snrmotionedgelut_8__20_ = snrmotionedgelut[8][20];
    V0_MOTION_EDGE_LUT_09f.bits.snrmotionedgelut_8__21_ = snrmotionedgelut[8][21];
    V0_MOTION_EDGE_LUT_09f.bits.snrmotionedgelut_8__22_ = snrmotionedgelut[8][22];
    V0_MOTION_EDGE_LUT_09f.bits.snrmotionedgelut_8__23_ = snrmotionedgelut[8][23];
    V0_MOTION_EDGE_LUT_09g.bits.snrmotionedgelut_8__24_ = snrmotionedgelut[8][24];
    V0_MOTION_EDGE_LUT_09g.bits.snrmotionedgelut_8__25_ = snrmotionedgelut[8][25];
    V0_MOTION_EDGE_LUT_09g.bits.snrmotionedgelut_8__26_ = snrmotionedgelut[8][26];
    V0_MOTION_EDGE_LUT_09g.bits.snrmotionedgelut_8__27_ = snrmotionedgelut[8][27];
    V0_MOTION_EDGE_LUT_09h.bits.snrmotionedgelut_8__28_ = snrmotionedgelut[8][28];
    V0_MOTION_EDGE_LUT_09h.bits.snrmotionedgelut_8__29_ = snrmotionedgelut[8][29];
    V0_MOTION_EDGE_LUT_09h.bits.snrmotionedgelut_8__30_ = snrmotionedgelut[8][30];
    V0_MOTION_EDGE_LUT_09h.bits.snrmotionedgelut_8__31_ = snrmotionedgelut[8][31];
    V0_MOTION_EDGE_LUT_10a.bits.snrmotionedgelut_9__0_  = snrmotionedgelut[9][0];
    V0_MOTION_EDGE_LUT_10a.bits.snrmotionedgelut_9__1_  = snrmotionedgelut[9][1];
    V0_MOTION_EDGE_LUT_10a.bits.snrmotionedgelut_9__2_  = snrmotionedgelut[9][2];
    V0_MOTION_EDGE_LUT_10a.bits.snrmotionedgelut_9__3_  = snrmotionedgelut[9][3];
    V0_MOTION_EDGE_LUT_10b.bits.snrmotionedgelut_9__4_  = snrmotionedgelut[9][4];
    V0_MOTION_EDGE_LUT_10b.bits.snrmotionedgelut_9__5_  = snrmotionedgelut[9][5];
    V0_MOTION_EDGE_LUT_10b.bits.snrmotionedgelut_9__6_  = snrmotionedgelut[9][6];
    V0_MOTION_EDGE_LUT_10b.bits.snrmotionedgelut_9__7_  = snrmotionedgelut[9][7];
    V0_MOTION_EDGE_LUT_10c.bits.snrmotionedgelut_9__8_  = snrmotionedgelut[9][8];
    V0_MOTION_EDGE_LUT_10c.bits.snrmotionedgelut_9__9_  = snrmotionedgelut[9][9];
    V0_MOTION_EDGE_LUT_10c.bits.snrmotionedgelut_9__10_ = snrmotionedgelut[9][10];
    V0_MOTION_EDGE_LUT_10c.bits.snrmotionedgelut_9__11_ = snrmotionedgelut[9][11];
    V0_MOTION_EDGE_LUT_10d.bits.snrmotionedgelut_9__12_ = snrmotionedgelut[9][12];
    V0_MOTION_EDGE_LUT_10d.bits.snrmotionedgelut_9__13_ = snrmotionedgelut[9][13];
    V0_MOTION_EDGE_LUT_10d.bits.snrmotionedgelut_9__14_ = snrmotionedgelut[9][14];
    V0_MOTION_EDGE_LUT_10d.bits.snrmotionedgelut_9__15_ = snrmotionedgelut[9][15];
    V0_MOTION_EDGE_LUT_10e.bits.snrmotionedgelut_9__16_ = snrmotionedgelut[9][16];
    V0_MOTION_EDGE_LUT_10e.bits.snrmotionedgelut_9__17_ = snrmotionedgelut[9][17];
    V0_MOTION_EDGE_LUT_10e.bits.snrmotionedgelut_9__18_ = snrmotionedgelut[9][18];
    V0_MOTION_EDGE_LUT_10e.bits.snrmotionedgelut_9__19_ = snrmotionedgelut[9][19];
    V0_MOTION_EDGE_LUT_10f.bits.snrmotionedgelut_9__20_ = snrmotionedgelut[9][20];
    V0_MOTION_EDGE_LUT_10f.bits.snrmotionedgelut_9__21_ = snrmotionedgelut[9][21];
    V0_MOTION_EDGE_LUT_10f.bits.snrmotionedgelut_9__22_ = snrmotionedgelut[9][22];
    V0_MOTION_EDGE_LUT_10f.bits.snrmotionedgelut_9__23_ = snrmotionedgelut[9][23];
    V0_MOTION_EDGE_LUT_10g.bits.snrmotionedgelut_9__24_ = snrmotionedgelut[9][24];
    V0_MOTION_EDGE_LUT_10g.bits.snrmotionedgelut_9__25_ = snrmotionedgelut[9][25];
    V0_MOTION_EDGE_LUT_10g.bits.snrmotionedgelut_9__26_ = snrmotionedgelut[9][26];
    V0_MOTION_EDGE_LUT_10g.bits.snrmotionedgelut_9__27_ = snrmotionedgelut[9][27];
    V0_MOTION_EDGE_LUT_10h.bits.snrmotionedgelut_9__28_ = snrmotionedgelut[9][28];
    V0_MOTION_EDGE_LUT_10h.bits.snrmotionedgelut_9__29_ = snrmotionedgelut[9][29];
    V0_MOTION_EDGE_LUT_10h.bits.snrmotionedgelut_9__30_ = snrmotionedgelut[9][30];
    V0_MOTION_EDGE_LUT_10h.bits.snrmotionedgelut_9__31_ = snrmotionedgelut[9][31];
    V0_MOTION_EDGE_LUT_11a.bits.snrmotionedgelut_10__0_ = snrmotionedgelut[10][0];
    V0_MOTION_EDGE_LUT_11a.bits.snrmotionedgelut_10__1_ = snrmotionedgelut[10][1];
    V0_MOTION_EDGE_LUT_11a.bits.snrmotionedgelut_10__2_ = snrmotionedgelut[10][2];
    V0_MOTION_EDGE_LUT_11a.bits.snrmotionedgelut_10__3_ = snrmotionedgelut[10][3];
    V0_MOTION_EDGE_LUT_11b.bits.snrmotionedgelut_10__4_ = snrmotionedgelut[10][4];
    V0_MOTION_EDGE_LUT_11b.bits.snrmotionedgelut_10__5_ = snrmotionedgelut[10][5];
    V0_MOTION_EDGE_LUT_11b.bits.snrmotionedgelut_10__6_ = snrmotionedgelut[10][6];
    V0_MOTION_EDGE_LUT_11b.bits.snrmotionedgelut_10__7_ = snrmotionedgelut[10][7];
    V0_MOTION_EDGE_LUT_11c.bits.snrmotionedgelut_10__8_ = snrmotionedgelut[10][8];
    V0_MOTION_EDGE_LUT_11c.bits.snrmotionedgelut_10__9_ = snrmotionedgelut[10][9];
    V0_MOTION_EDGE_LUT_11c.bits.snrmotionedgelut_10__10_ = snrmotionedgelut[10][10];
    V0_MOTION_EDGE_LUT_11c.bits.snrmotionedgelut_10__11_ = snrmotionedgelut[10][11];
    V0_MOTION_EDGE_LUT_11d.bits.snrmotionedgelut_10__12_ = snrmotionedgelut[10][12];
    V0_MOTION_EDGE_LUT_11d.bits.snrmotionedgelut_10__13_ = snrmotionedgelut[10][13];
    V0_MOTION_EDGE_LUT_11d.bits.snrmotionedgelut_10__14_ = snrmotionedgelut[10][14];
    V0_MOTION_EDGE_LUT_11d.bits.snrmotionedgelut_10__15_ = snrmotionedgelut[10][15];
    V0_MOTION_EDGE_LUT_11e.bits.snrmotionedgelut_10__16_ = snrmotionedgelut[10][16];
    V0_MOTION_EDGE_LUT_11e.bits.snrmotionedgelut_10__17_ = snrmotionedgelut[10][17];
    V0_MOTION_EDGE_LUT_11e.bits.snrmotionedgelut_10__18_ = snrmotionedgelut[10][18];
    V0_MOTION_EDGE_LUT_11e.bits.snrmotionedgelut_10__19_ = snrmotionedgelut[10][19];
    V0_MOTION_EDGE_LUT_11f.bits.snrmotionedgelut_10__20_ = snrmotionedgelut[10][20];
    V0_MOTION_EDGE_LUT_11f.bits.snrmotionedgelut_10__21_ = snrmotionedgelut[10][21];
    V0_MOTION_EDGE_LUT_11f.bits.snrmotionedgelut_10__22_ = snrmotionedgelut[10][22];
    V0_MOTION_EDGE_LUT_11f.bits.snrmotionedgelut_10__23_ = snrmotionedgelut[10][23];
    V0_MOTION_EDGE_LUT_11g.bits.snrmotionedgelut_10__24_ = snrmotionedgelut[10][24];
    V0_MOTION_EDGE_LUT_11g.bits.snrmotionedgelut_10__25_ = snrmotionedgelut[10][25];
    V0_MOTION_EDGE_LUT_11g.bits.snrmotionedgelut_10__26_ = snrmotionedgelut[10][26];
    V0_MOTION_EDGE_LUT_11g.bits.snrmotionedgelut_10__27_ = snrmotionedgelut[10][27];
    V0_MOTION_EDGE_LUT_11h.bits.snrmotionedgelut_10__28_ = snrmotionedgelut[10][28];
    V0_MOTION_EDGE_LUT_11h.bits.snrmotionedgelut_10__29_ = snrmotionedgelut[10][29];
    V0_MOTION_EDGE_LUT_11h.bits.snrmotionedgelut_10__30_ = snrmotionedgelut[10][30];
    V0_MOTION_EDGE_LUT_11h.bits.snrmotionedgelut_10__31_ = snrmotionedgelut[10][31];
    V0_MOTION_EDGE_LUT_12a.bits.snrmotionedgelut_11__0_  = snrmotionedgelut[11][0];
    V0_MOTION_EDGE_LUT_12a.bits.snrmotionedgelut_11__1_  = snrmotionedgelut[11][1];
    V0_MOTION_EDGE_LUT_12a.bits.snrmotionedgelut_11__2_  = snrmotionedgelut[11][2];
    V0_MOTION_EDGE_LUT_12a.bits.snrmotionedgelut_11__3_  = snrmotionedgelut[11][3];
    V0_MOTION_EDGE_LUT_12b.bits.snrmotionedgelut_11__4_  = snrmotionedgelut[11][4];
    V0_MOTION_EDGE_LUT_12b.bits.snrmotionedgelut_11__5_  = snrmotionedgelut[11][5];
    V0_MOTION_EDGE_LUT_12b.bits.snrmotionedgelut_11__6_  = snrmotionedgelut[11][6];
    V0_MOTION_EDGE_LUT_12b.bits.snrmotionedgelut_11__7_  = snrmotionedgelut[11][7];
    V0_MOTION_EDGE_LUT_12c.bits.snrmotionedgelut_11__8_  = snrmotionedgelut[11][8];
    V0_MOTION_EDGE_LUT_12c.bits.snrmotionedgelut_11__9_  = snrmotionedgelut[11][9];
    V0_MOTION_EDGE_LUT_12c.bits.snrmotionedgelut_11__10_ = snrmotionedgelut[11][10];
    V0_MOTION_EDGE_LUT_12c.bits.snrmotionedgelut_11__11_ = snrmotionedgelut[11][11];
    V0_MOTION_EDGE_LUT_12d.bits.snrmotionedgelut_11__12_ = snrmotionedgelut[11][12];
    V0_MOTION_EDGE_LUT_12d.bits.snrmotionedgelut_11__13_ = snrmotionedgelut[11][13];
    V0_MOTION_EDGE_LUT_12d.bits.snrmotionedgelut_11__14_ = snrmotionedgelut[11][14];
    V0_MOTION_EDGE_LUT_12d.bits.snrmotionedgelut_11__15_ = snrmotionedgelut[11][15];
    V0_MOTION_EDGE_LUT_12e.bits.snrmotionedgelut_11__16_ = snrmotionedgelut[11][16];
    V0_MOTION_EDGE_LUT_12e.bits.snrmotionedgelut_11__17_ = snrmotionedgelut[11][17];
    V0_MOTION_EDGE_LUT_12e.bits.snrmotionedgelut_11__18_ = snrmotionedgelut[11][18];
    V0_MOTION_EDGE_LUT_12e.bits.snrmotionedgelut_11__19_ = snrmotionedgelut[11][19];
    V0_MOTION_EDGE_LUT_12f.bits.snrmotionedgelut_11__20_ = snrmotionedgelut[11][20];
    V0_MOTION_EDGE_LUT_12f.bits.snrmotionedgelut_11__21_ = snrmotionedgelut[11][21];
    V0_MOTION_EDGE_LUT_12f.bits.snrmotionedgelut_11__22_ = snrmotionedgelut[11][22];
    V0_MOTION_EDGE_LUT_12f.bits.snrmotionedgelut_11__23_ = snrmotionedgelut[11][23];
    V0_MOTION_EDGE_LUT_12g.bits.snrmotionedgelut_11__24_ = snrmotionedgelut[11][24];
    V0_MOTION_EDGE_LUT_12g.bits.snrmotionedgelut_11__25_ = snrmotionedgelut[11][25];
    V0_MOTION_EDGE_LUT_12g.bits.snrmotionedgelut_11__26_ = snrmotionedgelut[11][26];
    V0_MOTION_EDGE_LUT_12g.bits.snrmotionedgelut_11__27_ = snrmotionedgelut[11][27];
    V0_MOTION_EDGE_LUT_12h.bits.snrmotionedgelut_11__28_ = snrmotionedgelut[11][28];
    V0_MOTION_EDGE_LUT_12h.bits.snrmotionedgelut_11__29_ = snrmotionedgelut[11][29];
    V0_MOTION_EDGE_LUT_12h.bits.snrmotionedgelut_11__30_ = snrmotionedgelut[11][30];
    V0_MOTION_EDGE_LUT_12h.bits.snrmotionedgelut_11__31_ = snrmotionedgelut[11][31];
    V0_MOTION_EDGE_LUT_13a.bits.snrmotionedgelut_12__0_  = snrmotionedgelut[12][0];
    V0_MOTION_EDGE_LUT_13a.bits.snrmotionedgelut_12__1_  = snrmotionedgelut[12][1];
    V0_MOTION_EDGE_LUT_13a.bits.snrmotionedgelut_12__2_  = snrmotionedgelut[12][2];
    V0_MOTION_EDGE_LUT_13a.bits.snrmotionedgelut_12__3_  = snrmotionedgelut[12][3];
    V0_MOTION_EDGE_LUT_13b.bits.snrmotionedgelut_12__4_  = snrmotionedgelut[12][4];
    V0_MOTION_EDGE_LUT_13b.bits.snrmotionedgelut_12__5_  = snrmotionedgelut[12][5];
    V0_MOTION_EDGE_LUT_13b.bits.snrmotionedgelut_12__6_  = snrmotionedgelut[12][6];
    V0_MOTION_EDGE_LUT_13b.bits.snrmotionedgelut_12__7_  = snrmotionedgelut[12][7];
    V0_MOTION_EDGE_LUT_13c.bits.snrmotionedgelut_12__8_  = snrmotionedgelut[12][8];
    V0_MOTION_EDGE_LUT_13c.bits.snrmotionedgelut_12__9_  = snrmotionedgelut[12][9];
    V0_MOTION_EDGE_LUT_13c.bits.snrmotionedgelut_12__10_ = snrmotionedgelut[12][10];
    V0_MOTION_EDGE_LUT_13c.bits.snrmotionedgelut_12__11_ = snrmotionedgelut[12][11];
    V0_MOTION_EDGE_LUT_13d.bits.snrmotionedgelut_12__12_ = snrmotionedgelut[12][12];
    V0_MOTION_EDGE_LUT_13d.bits.snrmotionedgelut_12__13_ = snrmotionedgelut[12][13];
    V0_MOTION_EDGE_LUT_13d.bits.snrmotionedgelut_12__14_ = snrmotionedgelut[12][14];
    V0_MOTION_EDGE_LUT_13d.bits.snrmotionedgelut_12__15_ = snrmotionedgelut[12][15];
    V0_MOTION_EDGE_LUT_13e.bits.snrmotionedgelut_12__16_ = snrmotionedgelut[12][16];
    V0_MOTION_EDGE_LUT_13e.bits.snrmotionedgelut_12__17_ = snrmotionedgelut[12][17];
    V0_MOTION_EDGE_LUT_13e.bits.snrmotionedgelut_12__18_ = snrmotionedgelut[12][18];
    V0_MOTION_EDGE_LUT_13e.bits.snrmotionedgelut_12__19_ = snrmotionedgelut[12][19];
    V0_MOTION_EDGE_LUT_13f.bits.snrmotionedgelut_12__20_ = snrmotionedgelut[12][20];
    V0_MOTION_EDGE_LUT_13f.bits.snrmotionedgelut_12__21_ = snrmotionedgelut[12][21];
    V0_MOTION_EDGE_LUT_13f.bits.snrmotionedgelut_12__22_ = snrmotionedgelut[12][22];
    V0_MOTION_EDGE_LUT_13f.bits.snrmotionedgelut_12__23_ = snrmotionedgelut[12][23];
    V0_MOTION_EDGE_LUT_13g.bits.snrmotionedgelut_12__24_ = snrmotionedgelut[12][24];
    V0_MOTION_EDGE_LUT_13g.bits.snrmotionedgelut_12__25_ = snrmotionedgelut[12][25];
    V0_MOTION_EDGE_LUT_13g.bits.snrmotionedgelut_12__26_ = snrmotionedgelut[12][26];
    V0_MOTION_EDGE_LUT_13g.bits.snrmotionedgelut_12__27_ = snrmotionedgelut[12][27];
    V0_MOTION_EDGE_LUT_13h.bits.snrmotionedgelut_12__28_ = snrmotionedgelut[12][28];
    V0_MOTION_EDGE_LUT_13h.bits.snrmotionedgelut_12__29_ = snrmotionedgelut[12][29];
    V0_MOTION_EDGE_LUT_13h.bits.snrmotionedgelut_12__30_ = snrmotionedgelut[12][30];
    V0_MOTION_EDGE_LUT_13h.bits.snrmotionedgelut_12__31_ = snrmotionedgelut[12][31];
    V0_MOTION_EDGE_LUT_14a.bits.snrmotionedgelut_13__0_  = snrmotionedgelut[13][0];
    V0_MOTION_EDGE_LUT_14a.bits.snrmotionedgelut_13__1_  = snrmotionedgelut[13][1];
    V0_MOTION_EDGE_LUT_14a.bits.snrmotionedgelut_13__2_  = snrmotionedgelut[13][2];
    V0_MOTION_EDGE_LUT_14a.bits.snrmotionedgelut_13__3_  = snrmotionedgelut[13][3];
    V0_MOTION_EDGE_LUT_14b.bits.snrmotionedgelut_13__4_  = snrmotionedgelut[13][4];
    V0_MOTION_EDGE_LUT_14b.bits.snrmotionedgelut_13__5_  = snrmotionedgelut[13][5];
    V0_MOTION_EDGE_LUT_14b.bits.snrmotionedgelut_13__6_  = snrmotionedgelut[13][6];
    V0_MOTION_EDGE_LUT_14b.bits.snrmotionedgelut_13__7_  = snrmotionedgelut[13][7];
    V0_MOTION_EDGE_LUT_14c.bits.snrmotionedgelut_13__8_  = snrmotionedgelut[13][8];
    V0_MOTION_EDGE_LUT_14c.bits.snrmotionedgelut_13__9_  = snrmotionedgelut[13][9];
    V0_MOTION_EDGE_LUT_14c.bits.snrmotionedgelut_13__10_ = snrmotionedgelut[13][10];
    V0_MOTION_EDGE_LUT_14c.bits.snrmotionedgelut_13__11_ = snrmotionedgelut[13][11];
    V0_MOTION_EDGE_LUT_14d.bits.snrmotionedgelut_13__12_ = snrmotionedgelut[13][12];
    V0_MOTION_EDGE_LUT_14d.bits.snrmotionedgelut_13__13_ = snrmotionedgelut[13][13];
    V0_MOTION_EDGE_LUT_14d.bits.snrmotionedgelut_13__14_ = snrmotionedgelut[13][14];
    V0_MOTION_EDGE_LUT_14d.bits.snrmotionedgelut_13__15_ = snrmotionedgelut[13][15];
    V0_MOTION_EDGE_LUT_14e.bits.snrmotionedgelut_13__16_ = snrmotionedgelut[13][16];
    V0_MOTION_EDGE_LUT_14e.bits.snrmotionedgelut_13__17_ = snrmotionedgelut[13][17];
    V0_MOTION_EDGE_LUT_14e.bits.snrmotionedgelut_13__18_ = snrmotionedgelut[13][18];
    V0_MOTION_EDGE_LUT_14e.bits.snrmotionedgelut_13__19_ = snrmotionedgelut[13][19];
    V0_MOTION_EDGE_LUT_14f.bits.snrmotionedgelut_13__20_ = snrmotionedgelut[13][20];
    V0_MOTION_EDGE_LUT_14f.bits.snrmotionedgelut_13__21_ = snrmotionedgelut[13][21];
    V0_MOTION_EDGE_LUT_14f.bits.snrmotionedgelut_13__22_ = snrmotionedgelut[13][22];
    V0_MOTION_EDGE_LUT_14f.bits.snrmotionedgelut_13__23_ = snrmotionedgelut[13][23];
    V0_MOTION_EDGE_LUT_14g.bits.snrmotionedgelut_13__24_ = snrmotionedgelut[13][24];
    V0_MOTION_EDGE_LUT_14g.bits.snrmotionedgelut_13__25_ = snrmotionedgelut[13][25];
    V0_MOTION_EDGE_LUT_14g.bits.snrmotionedgelut_13__26_ = snrmotionedgelut[13][26];
    V0_MOTION_EDGE_LUT_14g.bits.snrmotionedgelut_13__27_ = snrmotionedgelut[13][27];
    V0_MOTION_EDGE_LUT_14h.bits.snrmotionedgelut_13__28_ = snrmotionedgelut[13][28];
    V0_MOTION_EDGE_LUT_14h.bits.snrmotionedgelut_13__29_ = snrmotionedgelut[13][29];
    V0_MOTION_EDGE_LUT_14h.bits.snrmotionedgelut_13__30_ = snrmotionedgelut[13][30];
    V0_MOTION_EDGE_LUT_14h.bits.snrmotionedgelut_13__31_ = snrmotionedgelut[13][31];
    V0_MOTION_EDGE_LUT_15a.bits.snrmotionedgelut_14__0_  = snrmotionedgelut[14][0];
    V0_MOTION_EDGE_LUT_15a.bits.snrmotionedgelut_14__1_  = snrmotionedgelut[14][1];
    V0_MOTION_EDGE_LUT_15a.bits.snrmotionedgelut_14__2_  = snrmotionedgelut[14][2];
    V0_MOTION_EDGE_LUT_15a.bits.snrmotionedgelut_14__3_  = snrmotionedgelut[14][3];
    V0_MOTION_EDGE_LUT_15b.bits.snrmotionedgelut_14__4_  = snrmotionedgelut[14][4];
    V0_MOTION_EDGE_LUT_15b.bits.snrmotionedgelut_14__5_  = snrmotionedgelut[14][5];
    V0_MOTION_EDGE_LUT_15b.bits.snrmotionedgelut_14__6_  = snrmotionedgelut[14][6];
    V0_MOTION_EDGE_LUT_15b.bits.snrmotionedgelut_14__7_  = snrmotionedgelut[14][7];
    V0_MOTION_EDGE_LUT_15c.bits.snrmotionedgelut_14__8_  = snrmotionedgelut[14][8];
    V0_MOTION_EDGE_LUT_15c.bits.snrmotionedgelut_14__9_  = snrmotionedgelut[14][9];
    V0_MOTION_EDGE_LUT_15c.bits.snrmotionedgelut_14__10_ = snrmotionedgelut[14][10];
    V0_MOTION_EDGE_LUT_15c.bits.snrmotionedgelut_14__11_ = snrmotionedgelut[14][11];
    V0_MOTION_EDGE_LUT_15d.bits.snrmotionedgelut_14__12_ = snrmotionedgelut[14][12];
    V0_MOTION_EDGE_LUT_15d.bits.snrmotionedgelut_14__13_ = snrmotionedgelut[14][13];
    V0_MOTION_EDGE_LUT_15d.bits.snrmotionedgelut_14__14_ = snrmotionedgelut[14][14];
    V0_MOTION_EDGE_LUT_15d.bits.snrmotionedgelut_14__15_ = snrmotionedgelut[14][15];
    V0_MOTION_EDGE_LUT_15e.bits.snrmotionedgelut_14__16_ = snrmotionedgelut[14][16];
    V0_MOTION_EDGE_LUT_15e.bits.snrmotionedgelut_14__17_ = snrmotionedgelut[14][17];
    V0_MOTION_EDGE_LUT_15e.bits.snrmotionedgelut_14__18_ = snrmotionedgelut[14][18];
    V0_MOTION_EDGE_LUT_15e.bits.snrmotionedgelut_14__19_ = snrmotionedgelut[14][19];
    V0_MOTION_EDGE_LUT_15f.bits.snrmotionedgelut_14__20_ = snrmotionedgelut[14][20];
    V0_MOTION_EDGE_LUT_15f.bits.snrmotionedgelut_14__21_ = snrmotionedgelut[14][21];
    V0_MOTION_EDGE_LUT_15f.bits.snrmotionedgelut_14__22_ = snrmotionedgelut[14][22];
    V0_MOTION_EDGE_LUT_15f.bits.snrmotionedgelut_14__23_ = snrmotionedgelut[14][23];
    V0_MOTION_EDGE_LUT_15g.bits.snrmotionedgelut_14__24_ = snrmotionedgelut[14][24];
    V0_MOTION_EDGE_LUT_15g.bits.snrmotionedgelut_14__25_ = snrmotionedgelut[14][25];
    V0_MOTION_EDGE_LUT_15g.bits.snrmotionedgelut_14__26_ = snrmotionedgelut[14][26];
    V0_MOTION_EDGE_LUT_15g.bits.snrmotionedgelut_14__27_ = snrmotionedgelut[14][27];
    V0_MOTION_EDGE_LUT_15h.bits.snrmotionedgelut_14__28_ = snrmotionedgelut[14][28];
    V0_MOTION_EDGE_LUT_15h.bits.snrmotionedgelut_14__29_ = snrmotionedgelut[14][29];
    V0_MOTION_EDGE_LUT_15h.bits.snrmotionedgelut_14__30_ = snrmotionedgelut[14][30];
    V0_MOTION_EDGE_LUT_15h.bits.snrmotionedgelut_14__31_ = snrmotionedgelut[14][31];
    V0_MOTION_EDGE_LUT_16a.bits.snrmotionedgelut_15__0_  = snrmotionedgelut[15][0];
    V0_MOTION_EDGE_LUT_16a.bits.snrmotionedgelut_15__1_  = snrmotionedgelut[15][1];
    V0_MOTION_EDGE_LUT_16a.bits.snrmotionedgelut_15__2_  = snrmotionedgelut[15][2];
    V0_MOTION_EDGE_LUT_16a.bits.snrmotionedgelut_15__3_  = snrmotionedgelut[15][3];
    V0_MOTION_EDGE_LUT_16b.bits.snrmotionedgelut_15__4_  = snrmotionedgelut[15][4];
    V0_MOTION_EDGE_LUT_16b.bits.snrmotionedgelut_15__5_  = snrmotionedgelut[15][5];
    V0_MOTION_EDGE_LUT_16b.bits.snrmotionedgelut_15__6_  = snrmotionedgelut[15][6];
    V0_MOTION_EDGE_LUT_16b.bits.snrmotionedgelut_15__7_  = snrmotionedgelut[15][7];
    V0_MOTION_EDGE_LUT_16c.bits.snrmotionedgelut_15__8_  = snrmotionedgelut[15][8];
    V0_MOTION_EDGE_LUT_16c.bits.snrmotionedgelut_15__9_  = snrmotionedgelut[15][9];
    V0_MOTION_EDGE_LUT_16c.bits.snrmotionedgelut_15__10_ = snrmotionedgelut[15][10];
    V0_MOTION_EDGE_LUT_16c.bits.snrmotionedgelut_15__11_ = snrmotionedgelut[15][11];
    V0_MOTION_EDGE_LUT_16d.bits.snrmotionedgelut_15__12_ = snrmotionedgelut[15][12];
    V0_MOTION_EDGE_LUT_16d.bits.snrmotionedgelut_15__13_ = snrmotionedgelut[15][13];
    V0_MOTION_EDGE_LUT_16d.bits.snrmotionedgelut_15__14_ = snrmotionedgelut[15][14];
    V0_MOTION_EDGE_LUT_16d.bits.snrmotionedgelut_15__15_ = snrmotionedgelut[15][15];
    V0_MOTION_EDGE_LUT_16e.bits.snrmotionedgelut_15__16_ = snrmotionedgelut[15][16];
    V0_MOTION_EDGE_LUT_16e.bits.snrmotionedgelut_15__17_ = snrmotionedgelut[15][17];
    V0_MOTION_EDGE_LUT_16e.bits.snrmotionedgelut_15__18_ = snrmotionedgelut[15][18];
    V0_MOTION_EDGE_LUT_16e.bits.snrmotionedgelut_15__19_ = snrmotionedgelut[15][19];
    V0_MOTION_EDGE_LUT_16f.bits.snrmotionedgelut_15__20_ = snrmotionedgelut[15][20];
    V0_MOTION_EDGE_LUT_16f.bits.snrmotionedgelut_15__21_ = snrmotionedgelut[15][21];
    V0_MOTION_EDGE_LUT_16f.bits.snrmotionedgelut_15__22_ = snrmotionedgelut[15][22];
    V0_MOTION_EDGE_LUT_16f.bits.snrmotionedgelut_15__23_ = snrmotionedgelut[15][23];
    V0_MOTION_EDGE_LUT_16g.bits.snrmotionedgelut_15__24_ = snrmotionedgelut[15][24];
    V0_MOTION_EDGE_LUT_16g.bits.snrmotionedgelut_15__25_ = snrmotionedgelut[15][25];
    V0_MOTION_EDGE_LUT_16g.bits.snrmotionedgelut_15__26_ = snrmotionedgelut[15][26];
    V0_MOTION_EDGE_LUT_16g.bits.snrmotionedgelut_15__27_ = snrmotionedgelut[15][27];
    V0_MOTION_EDGE_LUT_16h.bits.snrmotionedgelut_15__28_ = snrmotionedgelut[15][28];
    V0_MOTION_EDGE_LUT_16h.bits.snrmotionedgelut_15__29_ = snrmotionedgelut[15][29];
    V0_MOTION_EDGE_LUT_16h.bits.snrmotionedgelut_15__30_ = snrmotionedgelut[15][30];
    V0_MOTION_EDGE_LUT_16h.bits.snrmotionedgelut_15__31_ = snrmotionedgelut[15][31];
#endif

#if 0
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_16h.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_16h.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_16g.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_16g.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_16f.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_16f.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_16e.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_16e.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_16d.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_16d.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_16c.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_16c.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_16b.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_16b.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_16a.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_16a.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_15h.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_15h.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_15g.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_15g.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_15f.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_15f.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_15e.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_15e.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_15d.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_15d.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_15c.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_15c.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_15b.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_15b.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_15a.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_15a.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_14h.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_14h.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_14g.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_14g.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_14f.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_14f.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_14e.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_14e.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_14d.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_14d.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_14c.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_14c.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_14b.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_14b.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_14a.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_14a.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_13h.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_13h.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_13g.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_13g.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_13f.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_13f.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_13e.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_13e.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_13d.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_13d.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_13c.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_13c.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_13b.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_13b.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_13a.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_13a.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_12h.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_12h.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_12g.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_12g.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_12f.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_12f.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_12e.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_12e.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_12d.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_12d.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_12c.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_12c.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_12b.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_12b.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_12a.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_12a.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_11h.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_11h.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_11g.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_11g.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_11f.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_11f.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_11e.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_11e.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_11d.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_11d.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_11c.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_11c.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_11b.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_11b.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_11a.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_11a.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_10h.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_10h.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_10g.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_10g.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_10f.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_10f.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_10e.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_10e.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_10d.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_10d.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_10c.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_10c.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_10b.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_10b.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_10a.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_10a.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_09h.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_09h.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_09g.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_09g.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_09f.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_09f.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_09e.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_09e.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_09d.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_09d.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_09c.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_09c.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_09b.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_09b.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_09a.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_09a.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_08h.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_08h.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_08g.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_08g.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_08f.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_08f.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_08e.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_08e.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_08d.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_08d.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_08c.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_08c.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_08b.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_08b.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_08a.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_08a.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_07h.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_07h.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_07g.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_07g.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_07f.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_07f.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_07e.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_07e.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_07d.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_07d.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_07c.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_07c.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_07b.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_07b.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_07a.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_07a.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_06h.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_06h.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_06g.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_06g.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_06f.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_06f.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_06e.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_06e.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_06d.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_06d.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_06c.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_06c.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_06b.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_06b.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_06a.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_06a.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_05h.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_05h.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_05g.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_05g.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_05f.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_05f.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_05e.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_05e.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_05d.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_05d.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_05c.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_05c.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_05b.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_05b.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_05a.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_05a.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_04h.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_04h.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_04g.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_04g.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_04f.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_04f.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_04e.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_04e.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_04d.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_04d.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_04c.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_04c.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_04b.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_04b.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_04a.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_04a.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_03h.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_03h.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_03g.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_03g.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_03f.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_03f.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_03e.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_03e.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_03d.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_03d.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_03c.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_03c.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_03b.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_03b.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_03a.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_03a.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_02h.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_02h.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_02g.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_02g.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_02f.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_02f.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_02e.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_02e.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_02d.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_02d.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_02c.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_02c.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_02b.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_02b.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_02a.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_02a.u32);
#endif
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_01h.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_01h.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_01g.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_01g.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_01f.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_01f.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_01e.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_01e.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_01d.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_01d.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_01c.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_01c.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_01b.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_01b.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MOTION_EDGE_LUT_01a.u32) + u32Data * VID_OFFSET), V0_MOTION_EDGE_LUT_01a.u32);
    return;
}

HI_VOID VPSS_DRV_SetSnrColorBasedLut(HI_U32 u32Data, HI_U32 snrcbcrlut[16][16])
{
#if 0
    U_V0_COLOR_BASED_LUT_01a V0_COLOR_BASED_LUT_01a;
    U_V0_COLOR_BASED_LUT_01b V0_COLOR_BASED_LUT_01b;
    U_V0_COLOR_BASED_LUT_01c V0_COLOR_BASED_LUT_01c;
    U_V0_COLOR_BASED_LUT_01d V0_COLOR_BASED_LUT_01d;
    U_V0_COLOR_BASED_LUT_02a V0_COLOR_BASED_LUT_02a;
    U_V0_COLOR_BASED_LUT_02b V0_COLOR_BASED_LUT_02b;
    U_V0_COLOR_BASED_LUT_02c V0_COLOR_BASED_LUT_02c;
    U_V0_COLOR_BASED_LUT_02d V0_COLOR_BASED_LUT_02d;
    U_V0_COLOR_BASED_LUT_03a V0_COLOR_BASED_LUT_03a;
    U_V0_COLOR_BASED_LUT_03b V0_COLOR_BASED_LUT_03b;
    U_V0_COLOR_BASED_LUT_03c V0_COLOR_BASED_LUT_03c;
    U_V0_COLOR_BASED_LUT_03d V0_COLOR_BASED_LUT_03d;
    U_V0_COLOR_BASED_LUT_04a V0_COLOR_BASED_LUT_04a;
    U_V0_COLOR_BASED_LUT_04b V0_COLOR_BASED_LUT_04b;
    U_V0_COLOR_BASED_LUT_04c V0_COLOR_BASED_LUT_04c;
    U_V0_COLOR_BASED_LUT_04d V0_COLOR_BASED_LUT_04d;
    U_V0_COLOR_BASED_LUT_05a V0_COLOR_BASED_LUT_05a;
    U_V0_COLOR_BASED_LUT_05b V0_COLOR_BASED_LUT_05b;
    U_V0_COLOR_BASED_LUT_05c V0_COLOR_BASED_LUT_05c;
    U_V0_COLOR_BASED_LUT_05d V0_COLOR_BASED_LUT_05d;
    U_V0_COLOR_BASED_LUT_06a V0_COLOR_BASED_LUT_06a;
    U_V0_COLOR_BASED_LUT_06b V0_COLOR_BASED_LUT_06b;
    U_V0_COLOR_BASED_LUT_06c V0_COLOR_BASED_LUT_06c;
    U_V0_COLOR_BASED_LUT_06d V0_COLOR_BASED_LUT_06d;
    U_V0_COLOR_BASED_LUT_07a V0_COLOR_BASED_LUT_07a;
    U_V0_COLOR_BASED_LUT_07b V0_COLOR_BASED_LUT_07b;
    U_V0_COLOR_BASED_LUT_07c V0_COLOR_BASED_LUT_07c;
    U_V0_COLOR_BASED_LUT_07d V0_COLOR_BASED_LUT_07d;
    U_V0_COLOR_BASED_LUT_08a V0_COLOR_BASED_LUT_08a;
    U_V0_COLOR_BASED_LUT_08b V0_COLOR_BASED_LUT_08b;
    U_V0_COLOR_BASED_LUT_08c V0_COLOR_BASED_LUT_08c;
    U_V0_COLOR_BASED_LUT_08d V0_COLOR_BASED_LUT_08d;
    U_V0_COLOR_BASED_LUT_09a V0_COLOR_BASED_LUT_09a;
    U_V0_COLOR_BASED_LUT_09b V0_COLOR_BASED_LUT_09b;
    U_V0_COLOR_BASED_LUT_09c V0_COLOR_BASED_LUT_09c;
    U_V0_COLOR_BASED_LUT_09d V0_COLOR_BASED_LUT_09d;
    U_V0_COLOR_BASED_LUT_10a V0_COLOR_BASED_LUT_10a;
    U_V0_COLOR_BASED_LUT_10b V0_COLOR_BASED_LUT_10b;
    U_V0_COLOR_BASED_LUT_10c V0_COLOR_BASED_LUT_10c;
    U_V0_COLOR_BASED_LUT_10d V0_COLOR_BASED_LUT_10d;
    U_V0_COLOR_BASED_LUT_11a V0_COLOR_BASED_LUT_11a;
    U_V0_COLOR_BASED_LUT_11b V0_COLOR_BASED_LUT_11b;
    U_V0_COLOR_BASED_LUT_11c V0_COLOR_BASED_LUT_11c;
    U_V0_COLOR_BASED_LUT_11d V0_COLOR_BASED_LUT_11d;
    U_V0_COLOR_BASED_LUT_12a V0_COLOR_BASED_LUT_12a;
    U_V0_COLOR_BASED_LUT_12b V0_COLOR_BASED_LUT_12b;
    U_V0_COLOR_BASED_LUT_12c V0_COLOR_BASED_LUT_12c;
    U_V0_COLOR_BASED_LUT_12d V0_COLOR_BASED_LUT_12d;
    U_V0_COLOR_BASED_LUT_13a V0_COLOR_BASED_LUT_13a;
    U_V0_COLOR_BASED_LUT_13b V0_COLOR_BASED_LUT_13b;
    U_V0_COLOR_BASED_LUT_13c V0_COLOR_BASED_LUT_13c;
    U_V0_COLOR_BASED_LUT_13d V0_COLOR_BASED_LUT_13d;
    U_V0_COLOR_BASED_LUT_14a V0_COLOR_BASED_LUT_14a;
    U_V0_COLOR_BASED_LUT_14b V0_COLOR_BASED_LUT_14b;
    U_V0_COLOR_BASED_LUT_14c V0_COLOR_BASED_LUT_14c;
    U_V0_COLOR_BASED_LUT_14d V0_COLOR_BASED_LUT_14d;
    U_V0_COLOR_BASED_LUT_15a V0_COLOR_BASED_LUT_15a;
    U_V0_COLOR_BASED_LUT_15b V0_COLOR_BASED_LUT_15b;
    U_V0_COLOR_BASED_LUT_15c V0_COLOR_BASED_LUT_15c;
    U_V0_COLOR_BASED_LUT_15d V0_COLOR_BASED_LUT_15d;
    U_V0_COLOR_BASED_LUT_16a V0_COLOR_BASED_LUT_16a;
    U_V0_COLOR_BASED_LUT_16b V0_COLOR_BASED_LUT_16b;
    U_V0_COLOR_BASED_LUT_16c V0_COLOR_BASED_LUT_16c;
    U_V0_COLOR_BASED_LUT_16d V0_COLOR_BASED_LUT_16d;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VPSS_DRV_SetSnrColorBasedLut Select Wrong Layer ID\n");
		return ;
	}

    V0_COLOR_BASED_LUT_16d.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_16d.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_16c.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_16c.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_16b.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_16b.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_16a.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_16a.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_15d.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_15d.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_15c.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_15c.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_15b.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_15b.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_15a.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_15a.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_14d.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_14d.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_14c.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_14c.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_14b.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_14b.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_14a.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_14a.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_13d.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_13d.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_13c.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_13c.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_13b.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_13b.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_13a.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_13a.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_12d.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_12d.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_12c.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_12c.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_12b.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_12b.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_12a.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_12a.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_11d.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_11d.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_11c.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_11c.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_11b.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_11b.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_11a.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_11a.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_10d.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_10d.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_10c.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_10c.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_10b.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_10b.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_10a.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_10a.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_09d.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_09d.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_09c.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_09c.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_09b.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_09b.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_09a.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_09a.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_08d.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_08d.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_08c.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_08c.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_08b.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_08b.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_08a.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_08a.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_07d.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_07d.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_07c.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_07c.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_07b.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_07b.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_07a.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_07a.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_06d.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_06d.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_06c.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_06c.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_06b.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_06b.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_06a.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_06a.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_05d.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_05d.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_05c.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_05c.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_05b.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_05b.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_05a.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_05a.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_04d.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_04d.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_04c.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_04c.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_04b.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_04b.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_04a.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_04a.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_03d.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_03d.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_03c.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_03c.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_03b.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_03b.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_03a.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_03a.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_02d.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_02d.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_02c.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_02c.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_02b.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_02b.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_02a.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_02a.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_01d.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_01d.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_01c.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_01c.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_01b.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_01b.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_01a.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_01a.u32) + u32Data * VID_OFFSET));
    V0_COLOR_BASED_LUT_01a.bits.snrcbcrlut_0__0_  = snrcbcrlut[0][0];
    V0_COLOR_BASED_LUT_01a.bits.snrcbcrlut_0__1_  = snrcbcrlut[0][1];
    V0_COLOR_BASED_LUT_01a.bits.snrcbcrlut_0__2_  = snrcbcrlut[0][2];
    V0_COLOR_BASED_LUT_01a.bits.snrcbcrlut_0__3_  = snrcbcrlut[0][3];
    V0_COLOR_BASED_LUT_01b.bits.snrcbcrlut_0__4_  = snrcbcrlut[0][4];
    V0_COLOR_BASED_LUT_01b.bits.snrcbcrlut_0__5_  = snrcbcrlut[0][5];
    V0_COLOR_BASED_LUT_01b.bits.snrcbcrlut_0__6_  = snrcbcrlut[0][6];
    V0_COLOR_BASED_LUT_01b.bits.snrcbcrlut_0__7_  = snrcbcrlut[0][7];
    V0_COLOR_BASED_LUT_01c.bits.snrcbcrlut_0__8_  = snrcbcrlut[0][8];
    V0_COLOR_BASED_LUT_01c.bits.snrcbcrlut_0__9_  = snrcbcrlut[0][9];
    V0_COLOR_BASED_LUT_01c.bits.snrcbcrlut_0__10_ = snrcbcrlut[0][10];
    V0_COLOR_BASED_LUT_01c.bits.snrcbcrlut_0__11_ = snrcbcrlut[0][11];
    V0_COLOR_BASED_LUT_01d.bits.snrcbcrlut_0__12_ = snrcbcrlut[0][12];
    V0_COLOR_BASED_LUT_01d.bits.snrcbcrlut_0__13_ = snrcbcrlut[0][13];
    V0_COLOR_BASED_LUT_01d.bits.snrcbcrlut_0__14_ = snrcbcrlut[0][14];
    V0_COLOR_BASED_LUT_01d.bits.snrcbcrlut_0__15_ = snrcbcrlut[0][15];
    V0_COLOR_BASED_LUT_02a.bits.snrcbcrlut_1__0_  = snrcbcrlut[1][0];
    V0_COLOR_BASED_LUT_02a.bits.snrcbcrlut_1__1_  = snrcbcrlut[1][1];
    V0_COLOR_BASED_LUT_02a.bits.snrcbcrlut_1__2_  = snrcbcrlut[1][2];
    V0_COLOR_BASED_LUT_02a.bits.snrcbcrlut_1__3_  = snrcbcrlut[1][3];
    V0_COLOR_BASED_LUT_02b.bits.snrcbcrlut_1__4_  = snrcbcrlut[1][4];
    V0_COLOR_BASED_LUT_02b.bits.snrcbcrlut_1__5_  = snrcbcrlut[1][5];
    V0_COLOR_BASED_LUT_02b.bits.snrcbcrlut_1__6_  = snrcbcrlut[1][6];
    V0_COLOR_BASED_LUT_02b.bits.snrcbcrlut_1__7_  = snrcbcrlut[1][7];
    V0_COLOR_BASED_LUT_02c.bits.snrcbcrlut_1__8_  = snrcbcrlut[1][8];
    V0_COLOR_BASED_LUT_02c.bits.snrcbcrlut_1__9_  = snrcbcrlut[1][9];
    V0_COLOR_BASED_LUT_02c.bits.snrcbcrlut_1__10_ = snrcbcrlut[1][10];
    V0_COLOR_BASED_LUT_02c.bits.snrcbcrlut_1__11_ = snrcbcrlut[1][11];
    V0_COLOR_BASED_LUT_02d.bits.snrcbcrlut_1__12_ = snrcbcrlut[1][12];
    V0_COLOR_BASED_LUT_02d.bits.snrcbcrlut_1__13_ = snrcbcrlut[1][13];
    V0_COLOR_BASED_LUT_02d.bits.snrcbcrlut_1__14_ = snrcbcrlut[1][14];
    V0_COLOR_BASED_LUT_02d.bits.snrcbcrlut_1__15_ = snrcbcrlut[1][15];
    V0_COLOR_BASED_LUT_03a.bits.snrcbcrlut_2__0_  = snrcbcrlut[2][0];
    V0_COLOR_BASED_LUT_03a.bits.snrcbcrlut_2__1_  = snrcbcrlut[2][1];
    V0_COLOR_BASED_LUT_03a.bits.snrcbcrlut_2__2_  = snrcbcrlut[2][2];
    V0_COLOR_BASED_LUT_03a.bits.snrcbcrlut_2__3_  = snrcbcrlut[2][3];
    V0_COLOR_BASED_LUT_03b.bits.snrcbcrlut_2__4_  = snrcbcrlut[2][4];
    V0_COLOR_BASED_LUT_03b.bits.snrcbcrlut_2__5_  = snrcbcrlut[2][5];
    V0_COLOR_BASED_LUT_03b.bits.snrcbcrlut_2__6_  = snrcbcrlut[2][6];
    V0_COLOR_BASED_LUT_03b.bits.snrcbcrlut_2__7_  = snrcbcrlut[2][7];
    V0_COLOR_BASED_LUT_03c.bits.snrcbcrlut_2__8_  = snrcbcrlut[2][8];
    V0_COLOR_BASED_LUT_03c.bits.snrcbcrlut_2__9_  = snrcbcrlut[2][9];
    V0_COLOR_BASED_LUT_03c.bits.snrcbcrlut_2__10_ = snrcbcrlut[2][10];
    V0_COLOR_BASED_LUT_03c.bits.snrcbcrlut_2__11_ = snrcbcrlut[2][11];
    V0_COLOR_BASED_LUT_03d.bits.snrcbcrlut_2__12_ = snrcbcrlut[2][12];
    V0_COLOR_BASED_LUT_03d.bits.snrcbcrlut_2__13_ = snrcbcrlut[2][13];
    V0_COLOR_BASED_LUT_03d.bits.snrcbcrlut_2__14_ = snrcbcrlut[2][14];
    V0_COLOR_BASED_LUT_03d.bits.snrcbcrlut_2__15_ = snrcbcrlut[2][15];
    V0_COLOR_BASED_LUT_04a.bits.snrcbcrlut_3__0_  = snrcbcrlut[3][0];
    V0_COLOR_BASED_LUT_04a.bits.snrcbcrlut_3__1_  = snrcbcrlut[3][1];
    V0_COLOR_BASED_LUT_04a.bits.snrcbcrlut_3__2_  = snrcbcrlut[3][2];
    V0_COLOR_BASED_LUT_04a.bits.snrcbcrlut_3__3_  = snrcbcrlut[3][3];
    V0_COLOR_BASED_LUT_04b.bits.snrcbcrlut_3__4_  = snrcbcrlut[3][4];
    V0_COLOR_BASED_LUT_04b.bits.snrcbcrlut_3__5_  = snrcbcrlut[3][5];
    V0_COLOR_BASED_LUT_04b.bits.snrcbcrlut_3__6_  = snrcbcrlut[3][6];
    V0_COLOR_BASED_LUT_04b.bits.snrcbcrlut_3__7_  = snrcbcrlut[3][7];
    V0_COLOR_BASED_LUT_04c.bits.snrcbcrlut_3__8_  = snrcbcrlut[3][8];
    V0_COLOR_BASED_LUT_04c.bits.snrcbcrlut_3__9_  = snrcbcrlut[3][9];
    V0_COLOR_BASED_LUT_04c.bits.snrcbcrlut_3__10_ = snrcbcrlut[3][10];
    V0_COLOR_BASED_LUT_04c.bits.snrcbcrlut_3__11_ = snrcbcrlut[3][11];
    V0_COLOR_BASED_LUT_04d.bits.snrcbcrlut_3__12_ = snrcbcrlut[3][12];
    V0_COLOR_BASED_LUT_04d.bits.snrcbcrlut_3__13_ = snrcbcrlut[3][13];
    V0_COLOR_BASED_LUT_04d.bits.snrcbcrlut_3__14_ = snrcbcrlut[3][14];
    V0_COLOR_BASED_LUT_04d.bits.snrcbcrlut_3__15_ = snrcbcrlut[3][15];
    V0_COLOR_BASED_LUT_05a.bits.snrcbcrlut_4__0_  = snrcbcrlut[4][0];
    V0_COLOR_BASED_LUT_05a.bits.snrcbcrlut_4__1_  = snrcbcrlut[4][1];
    V0_COLOR_BASED_LUT_05a.bits.snrcbcrlut_4__2_  = snrcbcrlut[4][2];
    V0_COLOR_BASED_LUT_05a.bits.snrcbcrlut_4__3_  = snrcbcrlut[4][3];
    V0_COLOR_BASED_LUT_05b.bits.snrcbcrlut_4__4_  = snrcbcrlut[4][4];
    V0_COLOR_BASED_LUT_05b.bits.snrcbcrlut_4__5_  = snrcbcrlut[4][5];
    V0_COLOR_BASED_LUT_05b.bits.snrcbcrlut_4__6_  = snrcbcrlut[4][6];
    V0_COLOR_BASED_LUT_05b.bits.snrcbcrlut_4__7_  = snrcbcrlut[4][7];
    V0_COLOR_BASED_LUT_05c.bits.snrcbcrlut_4__8_  = snrcbcrlut[4][8];
    V0_COLOR_BASED_LUT_05c.bits.snrcbcrlut_4__9_  = snrcbcrlut[4][9];
    V0_COLOR_BASED_LUT_05c.bits.snrcbcrlut_4__10_ = snrcbcrlut[4][10];
    V0_COLOR_BASED_LUT_05c.bits.snrcbcrlut_4__11_ = snrcbcrlut[4][11];
    V0_COLOR_BASED_LUT_05d.bits.snrcbcrlut_4__12_ = snrcbcrlut[4][12];
    V0_COLOR_BASED_LUT_05d.bits.snrcbcrlut_4__13_ = snrcbcrlut[4][13];
    V0_COLOR_BASED_LUT_05d.bits.snrcbcrlut_4__14_ = snrcbcrlut[4][14];
    V0_COLOR_BASED_LUT_05d.bits.snrcbcrlut_4__15_ = snrcbcrlut[4][15];
    V0_COLOR_BASED_LUT_06a.bits.snrcbcrlut_5__0_  = snrcbcrlut[5][0];
    V0_COLOR_BASED_LUT_06a.bits.snrcbcrlut_5__1_  = snrcbcrlut[5][1];
    V0_COLOR_BASED_LUT_06a.bits.snrcbcrlut_5__2_  = snrcbcrlut[5][2];
    V0_COLOR_BASED_LUT_06a.bits.snrcbcrlut_5__3_  = snrcbcrlut[5][3];
    V0_COLOR_BASED_LUT_06b.bits.snrcbcrlut_5__4_  = snrcbcrlut[5][4];
    V0_COLOR_BASED_LUT_06b.bits.snrcbcrlut_5__5_  = snrcbcrlut[5][5];
    V0_COLOR_BASED_LUT_06b.bits.snrcbcrlut_5__6_  = snrcbcrlut[5][6];
    V0_COLOR_BASED_LUT_06b.bits.snrcbcrlut_5__7_  = snrcbcrlut[5][7];
    V0_COLOR_BASED_LUT_06c.bits.snrcbcrlut_5__8_  = snrcbcrlut[5][8];
    V0_COLOR_BASED_LUT_06c.bits.snrcbcrlut_5__9_  = snrcbcrlut[5][9];
    V0_COLOR_BASED_LUT_06c.bits.snrcbcrlut_5__10_ = snrcbcrlut[5][10];
    V0_COLOR_BASED_LUT_06c.bits.snrcbcrlut_5__11_ = snrcbcrlut[5][11];
    V0_COLOR_BASED_LUT_06d.bits.snrcbcrlut_5__12_ = snrcbcrlut[5][12];
    V0_COLOR_BASED_LUT_06d.bits.snrcbcrlut_5__13_ = snrcbcrlut[5][13];
    V0_COLOR_BASED_LUT_06d.bits.snrcbcrlut_5__14_ = snrcbcrlut[5][14];
    V0_COLOR_BASED_LUT_06d.bits.snrcbcrlut_5__15_ = snrcbcrlut[5][15];
    V0_COLOR_BASED_LUT_07a.bits.snrcbcrlut_6__0_  = snrcbcrlut[6][0];
    V0_COLOR_BASED_LUT_07a.bits.snrcbcrlut_6__1_  = snrcbcrlut[6][1];
    V0_COLOR_BASED_LUT_07a.bits.snrcbcrlut_6__2_  = snrcbcrlut[6][2];
    V0_COLOR_BASED_LUT_07a.bits.snrcbcrlut_6__3_  = snrcbcrlut[6][3];
    V0_COLOR_BASED_LUT_07b.bits.snrcbcrlut_6__4_  = snrcbcrlut[6][4];
    V0_COLOR_BASED_LUT_07b.bits.snrcbcrlut_6__5_  = snrcbcrlut[6][5];
    V0_COLOR_BASED_LUT_07b.bits.snrcbcrlut_6__6_  = snrcbcrlut[6][6];
    V0_COLOR_BASED_LUT_07b.bits.snrcbcrlut_6__7_  = snrcbcrlut[6][7];
    V0_COLOR_BASED_LUT_07c.bits.snrcbcrlut_6__8_  = snrcbcrlut[6][8];
    V0_COLOR_BASED_LUT_07c.bits.snrcbcrlut_6__9_  = snrcbcrlut[6][9];
    V0_COLOR_BASED_LUT_07c.bits.snrcbcrlut_6__10_ = snrcbcrlut[6][10];
    V0_COLOR_BASED_LUT_07c.bits.snrcbcrlut_6__11_ = snrcbcrlut[6][11];
    V0_COLOR_BASED_LUT_07d.bits.snrcbcrlut_6__12_ = snrcbcrlut[6][12];
    V0_COLOR_BASED_LUT_07d.bits.snrcbcrlut_6__13_ = snrcbcrlut[6][13];
    V0_COLOR_BASED_LUT_07d.bits.snrcbcrlut_6__14_ = snrcbcrlut[6][14];
    V0_COLOR_BASED_LUT_07d.bits.snrcbcrlut_6__15_ = snrcbcrlut[6][15];
    V0_COLOR_BASED_LUT_08a.bits.snrcbcrlut_7__0_  = snrcbcrlut[7][0];
    V0_COLOR_BASED_LUT_08a.bits.snrcbcrlut_7__1_  = snrcbcrlut[7][1];
    V0_COLOR_BASED_LUT_08a.bits.snrcbcrlut_7__2_  = snrcbcrlut[7][2];
    V0_COLOR_BASED_LUT_08a.bits.snrcbcrlut_7__3_  = snrcbcrlut[7][3];
    V0_COLOR_BASED_LUT_08b.bits.snrcbcrlut_7__4_  = snrcbcrlut[7][4];
    V0_COLOR_BASED_LUT_08b.bits.snrcbcrlut_7__5_  = snrcbcrlut[7][5];
    V0_COLOR_BASED_LUT_08b.bits.snrcbcrlut_7__6_  = snrcbcrlut[7][6];
    V0_COLOR_BASED_LUT_08b.bits.snrcbcrlut_7__7_  = snrcbcrlut[7][7];
    V0_COLOR_BASED_LUT_08c.bits.snrcbcrlut_7__8_  = snrcbcrlut[7][8];
    V0_COLOR_BASED_LUT_08c.bits.snrcbcrlut_7__9_  = snrcbcrlut[7][9];
    V0_COLOR_BASED_LUT_08c.bits.snrcbcrlut_7__10_ = snrcbcrlut[7][10];
    V0_COLOR_BASED_LUT_08c.bits.snrcbcrlut_7__11_ = snrcbcrlut[7][11];
    V0_COLOR_BASED_LUT_08d.bits.snrcbcrlut_7__12_ = snrcbcrlut[7][12];
    V0_COLOR_BASED_LUT_08d.bits.snrcbcrlut_7__13_ = snrcbcrlut[7][13];
    V0_COLOR_BASED_LUT_08d.bits.snrcbcrlut_7__14_ = snrcbcrlut[7][14];
    V0_COLOR_BASED_LUT_08d.bits.snrcbcrlut_7__15_ = snrcbcrlut[7][15];
    V0_COLOR_BASED_LUT_09a.bits.snrcbcrlut_8__0_  = snrcbcrlut[8][0];
    V0_COLOR_BASED_LUT_09a.bits.snrcbcrlut_8__1_  = snrcbcrlut[8][1];
    V0_COLOR_BASED_LUT_09a.bits.snrcbcrlut_8__2_  = snrcbcrlut[8][2];
    V0_COLOR_BASED_LUT_09a.bits.snrcbcrlut_8__3_  = snrcbcrlut[8][3];
    V0_COLOR_BASED_LUT_09b.bits.snrcbcrlut_8__4_  = snrcbcrlut[8][4];
    V0_COLOR_BASED_LUT_09b.bits.snrcbcrlut_8__5_  = snrcbcrlut[8][5];
    V0_COLOR_BASED_LUT_09b.bits.snrcbcrlut_8__6_  = snrcbcrlut[8][6];
    V0_COLOR_BASED_LUT_09b.bits.snrcbcrlut_8__7_  = snrcbcrlut[8][7];
    V0_COLOR_BASED_LUT_09c.bits.snrcbcrlut_8__8_  = snrcbcrlut[8][8];
    V0_COLOR_BASED_LUT_09c.bits.snrcbcrlut_8__9_  = snrcbcrlut[8][9];
    V0_COLOR_BASED_LUT_09c.bits.snrcbcrlut_8__10_ = snrcbcrlut[8][10];
    V0_COLOR_BASED_LUT_09c.bits.snrcbcrlut_8__11_ = snrcbcrlut[8][11];
    V0_COLOR_BASED_LUT_09d.bits.snrcbcrlut_8__12_ = snrcbcrlut[8][12];
    V0_COLOR_BASED_LUT_09d.bits.snrcbcrlut_8__13_ = snrcbcrlut[8][13];
    V0_COLOR_BASED_LUT_09d.bits.snrcbcrlut_8__14_ = snrcbcrlut[8][14];
    V0_COLOR_BASED_LUT_09d.bits.snrcbcrlut_8__15_ = snrcbcrlut[8][15];
    V0_COLOR_BASED_LUT_10a.bits.snrcbcrlut_9__0_  = snrcbcrlut[9][0];
    V0_COLOR_BASED_LUT_10a.bits.snrcbcrlut_9__1_  = snrcbcrlut[9][1];
    V0_COLOR_BASED_LUT_10a.bits.snrcbcrlut_9__2_  = snrcbcrlut[9][2];
    V0_COLOR_BASED_LUT_10a.bits.snrcbcrlut_9__3_  = snrcbcrlut[9][3];
    V0_COLOR_BASED_LUT_10b.bits.snrcbcrlut_9__4_  = snrcbcrlut[9][4];
    V0_COLOR_BASED_LUT_10b.bits.snrcbcrlut_9__5_  = snrcbcrlut[9][5];
    V0_COLOR_BASED_LUT_10b.bits.snrcbcrlut_9__6_  = snrcbcrlut[9][6];
    V0_COLOR_BASED_LUT_10b.bits.snrcbcrlut_9__7_  = snrcbcrlut[9][7];
    V0_COLOR_BASED_LUT_10c.bits.snrcbcrlut_9__8_  = snrcbcrlut[9][8];
    V0_COLOR_BASED_LUT_10c.bits.snrcbcrlut_9__9_  = snrcbcrlut[9][9];
    V0_COLOR_BASED_LUT_10c.bits.snrcbcrlut_9__10_ = snrcbcrlut[9][10];
    V0_COLOR_BASED_LUT_10c.bits.snrcbcrlut_9__11_ = snrcbcrlut[9][11];
    V0_COLOR_BASED_LUT_10d.bits.snrcbcrlut_9__12_ = snrcbcrlut[9][12];
    V0_COLOR_BASED_LUT_10d.bits.snrcbcrlut_9__13_ = snrcbcrlut[9][13];
    V0_COLOR_BASED_LUT_10d.bits.snrcbcrlut_9__14_ = snrcbcrlut[9][14];
    V0_COLOR_BASED_LUT_10d.bits.snrcbcrlut_9__15_ = snrcbcrlut[9][15];
    V0_COLOR_BASED_LUT_11a.bits.snrcbcrlut_10__0_ = snrcbcrlut[10][0];
    V0_COLOR_BASED_LUT_11a.bits.snrcbcrlut_10__1_ = snrcbcrlut[10][1];
    V0_COLOR_BASED_LUT_11a.bits.snrcbcrlut_10__2_ = snrcbcrlut[10][2];
    V0_COLOR_BASED_LUT_11a.bits.snrcbcrlut_10__3_ = snrcbcrlut[10][3];
    V0_COLOR_BASED_LUT_11b.bits.snrcbcrlut_10__4_ = snrcbcrlut[10][4];
    V0_COLOR_BASED_LUT_11b.bits.snrcbcrlut_10__5_ = snrcbcrlut[10][5];
    V0_COLOR_BASED_LUT_11b.bits.snrcbcrlut_10__6_ = snrcbcrlut[10][6];
    V0_COLOR_BASED_LUT_11b.bits.snrcbcrlut_10__7_ = snrcbcrlut[10][7];
    V0_COLOR_BASED_LUT_11c.bits.snrcbcrlut_10__8_ = snrcbcrlut[10][8];
    V0_COLOR_BASED_LUT_11c.bits.snrcbcrlut_10__9_ = snrcbcrlut[10][9];
    V0_COLOR_BASED_LUT_11c.bits.snrcbcrlut_10__10_ = snrcbcrlut[10][10];
    V0_COLOR_BASED_LUT_11c.bits.snrcbcrlut_10__11_ = snrcbcrlut[10][11];
    V0_COLOR_BASED_LUT_11d.bits.snrcbcrlut_10__12_ = snrcbcrlut[10][12];
    V0_COLOR_BASED_LUT_11d.bits.snrcbcrlut_10__13_ = snrcbcrlut[10][13];
    V0_COLOR_BASED_LUT_11d.bits.snrcbcrlut_10__14_ = snrcbcrlut[10][14];
    V0_COLOR_BASED_LUT_11d.bits.snrcbcrlut_10__15_ = snrcbcrlut[10][15];
    V0_COLOR_BASED_LUT_12a.bits.snrcbcrlut_11__0_  = snrcbcrlut[11][0];
    V0_COLOR_BASED_LUT_12a.bits.snrcbcrlut_11__1_  = snrcbcrlut[11][1];
    V0_COLOR_BASED_LUT_12a.bits.snrcbcrlut_11__2_  = snrcbcrlut[11][2];
    V0_COLOR_BASED_LUT_12a.bits.snrcbcrlut_11__3_  = snrcbcrlut[11][3];
    V0_COLOR_BASED_LUT_12b.bits.snrcbcrlut_11__4_  = snrcbcrlut[11][4];
    V0_COLOR_BASED_LUT_12b.bits.snrcbcrlut_11__5_  = snrcbcrlut[11][5];
    V0_COLOR_BASED_LUT_12b.bits.snrcbcrlut_11__6_  = snrcbcrlut[11][6];
    V0_COLOR_BASED_LUT_12b.bits.snrcbcrlut_11__7_  = snrcbcrlut[11][7];
    V0_COLOR_BASED_LUT_12c.bits.snrcbcrlut_11__8_  = snrcbcrlut[11][8];
    V0_COLOR_BASED_LUT_12c.bits.snrcbcrlut_11__9_  = snrcbcrlut[11][9];
    V0_COLOR_BASED_LUT_12c.bits.snrcbcrlut_11__10_ = snrcbcrlut[11][10];
    V0_COLOR_BASED_LUT_12c.bits.snrcbcrlut_11__11_ = snrcbcrlut[11][11];
    V0_COLOR_BASED_LUT_12d.bits.snrcbcrlut_11__12_ = snrcbcrlut[11][12];
    V0_COLOR_BASED_LUT_12d.bits.snrcbcrlut_11__13_ = snrcbcrlut[11][13];
    V0_COLOR_BASED_LUT_12d.bits.snrcbcrlut_11__14_ = snrcbcrlut[11][14];
    V0_COLOR_BASED_LUT_12d.bits.snrcbcrlut_11__15_ = snrcbcrlut[11][15];
    V0_COLOR_BASED_LUT_13a.bits.snrcbcrlut_12__0_  = snrcbcrlut[12][0];
    V0_COLOR_BASED_LUT_13a.bits.snrcbcrlut_12__1_  = snrcbcrlut[12][1];
    V0_COLOR_BASED_LUT_13a.bits.snrcbcrlut_12__2_  = snrcbcrlut[12][2];
    V0_COLOR_BASED_LUT_13a.bits.snrcbcrlut_12__3_  = snrcbcrlut[12][3];
    V0_COLOR_BASED_LUT_13b.bits.snrcbcrlut_12__4_  = snrcbcrlut[12][4];
    V0_COLOR_BASED_LUT_13b.bits.snrcbcrlut_12__5_  = snrcbcrlut[12][5];
    V0_COLOR_BASED_LUT_13b.bits.snrcbcrlut_12__6_  = snrcbcrlut[12][6];
    V0_COLOR_BASED_LUT_13b.bits.snrcbcrlut_12__7_  = snrcbcrlut[12][7];
    V0_COLOR_BASED_LUT_13c.bits.snrcbcrlut_12__8_  = snrcbcrlut[12][8];
    V0_COLOR_BASED_LUT_13c.bits.snrcbcrlut_12__9_  = snrcbcrlut[12][9];
    V0_COLOR_BASED_LUT_13c.bits.snrcbcrlut_12__10_ = snrcbcrlut[12][10];
    V0_COLOR_BASED_LUT_13c.bits.snrcbcrlut_12__11_ = snrcbcrlut[12][11];
    V0_COLOR_BASED_LUT_13d.bits.snrcbcrlut_12__12_ = snrcbcrlut[12][12];
    V0_COLOR_BASED_LUT_13d.bits.snrcbcrlut_12__13_ = snrcbcrlut[12][13];
    V0_COLOR_BASED_LUT_13d.bits.snrcbcrlut_12__14_ = snrcbcrlut[12][14];
    V0_COLOR_BASED_LUT_13d.bits.snrcbcrlut_12__15_ = snrcbcrlut[12][15];
    V0_COLOR_BASED_LUT_14a.bits.snrcbcrlut_13__0_  = snrcbcrlut[13][0];
    V0_COLOR_BASED_LUT_14a.bits.snrcbcrlut_13__1_  = snrcbcrlut[13][1];
    V0_COLOR_BASED_LUT_14a.bits.snrcbcrlut_13__2_  = snrcbcrlut[13][2];
    V0_COLOR_BASED_LUT_14a.bits.snrcbcrlut_13__3_  = snrcbcrlut[13][3];
    V0_COLOR_BASED_LUT_14b.bits.snrcbcrlut_13__4_  = snrcbcrlut[13][4];
    V0_COLOR_BASED_LUT_14b.bits.snrcbcrlut_13__5_  = snrcbcrlut[13][5];
    V0_COLOR_BASED_LUT_14b.bits.snrcbcrlut_13__6_  = snrcbcrlut[13][6];
    V0_COLOR_BASED_LUT_14b.bits.snrcbcrlut_13__7_  = snrcbcrlut[13][7];
    V0_COLOR_BASED_LUT_14c.bits.snrcbcrlut_13__8_  = snrcbcrlut[13][8];
    V0_COLOR_BASED_LUT_14c.bits.snrcbcrlut_13__9_  = snrcbcrlut[13][9];
    V0_COLOR_BASED_LUT_14c.bits.snrcbcrlut_13__10_ = snrcbcrlut[13][10];
    V0_COLOR_BASED_LUT_14c.bits.snrcbcrlut_13__11_ = snrcbcrlut[13][11];
    V0_COLOR_BASED_LUT_14d.bits.snrcbcrlut_13__12_ = snrcbcrlut[13][12];
    V0_COLOR_BASED_LUT_14d.bits.snrcbcrlut_13__13_ = snrcbcrlut[13][13];
    V0_COLOR_BASED_LUT_14d.bits.snrcbcrlut_13__14_ = snrcbcrlut[13][14];
    V0_COLOR_BASED_LUT_14d.bits.snrcbcrlut_13__15_ = snrcbcrlut[13][15];
    V0_COLOR_BASED_LUT_15a.bits.snrcbcrlut_14__0_  = snrcbcrlut[14][0];
    V0_COLOR_BASED_LUT_15a.bits.snrcbcrlut_14__1_  = snrcbcrlut[14][1];
    V0_COLOR_BASED_LUT_15a.bits.snrcbcrlut_14__2_  = snrcbcrlut[14][2];
    V0_COLOR_BASED_LUT_15a.bits.snrcbcrlut_14__3_  = snrcbcrlut[14][3];
    V0_COLOR_BASED_LUT_15b.bits.snrcbcrlut_14__4_  = snrcbcrlut[14][4];
    V0_COLOR_BASED_LUT_15b.bits.snrcbcrlut_14__5_  = snrcbcrlut[14][5];
    V0_COLOR_BASED_LUT_15b.bits.snrcbcrlut_14__6_  = snrcbcrlut[14][6];
    V0_COLOR_BASED_LUT_15b.bits.snrcbcrlut_14__7_  = snrcbcrlut[14][7];
    V0_COLOR_BASED_LUT_15c.bits.snrcbcrlut_14__8_  = snrcbcrlut[14][8];
    V0_COLOR_BASED_LUT_15c.bits.snrcbcrlut_14__9_  = snrcbcrlut[14][9];
    V0_COLOR_BASED_LUT_15c.bits.snrcbcrlut_14__10_ = snrcbcrlut[14][10];
    V0_COLOR_BASED_LUT_15c.bits.snrcbcrlut_14__11_ = snrcbcrlut[14][11];
    V0_COLOR_BASED_LUT_15d.bits.snrcbcrlut_14__12_ = snrcbcrlut[14][12];
    V0_COLOR_BASED_LUT_15d.bits.snrcbcrlut_14__13_ = snrcbcrlut[14][13];
    V0_COLOR_BASED_LUT_15d.bits.snrcbcrlut_14__14_ = snrcbcrlut[14][14];
    V0_COLOR_BASED_LUT_15d.bits.snrcbcrlut_14__15_ = snrcbcrlut[14][15];
    V0_COLOR_BASED_LUT_16a.bits.snrcbcrlut_15__0_  = snrcbcrlut[15][0];
    V0_COLOR_BASED_LUT_16a.bits.snrcbcrlut_15__1_  = snrcbcrlut[15][1];
    V0_COLOR_BASED_LUT_16a.bits.snrcbcrlut_15__2_  = snrcbcrlut[15][2];
    V0_COLOR_BASED_LUT_16a.bits.snrcbcrlut_15__3_  = snrcbcrlut[15][3];
    V0_COLOR_BASED_LUT_16b.bits.snrcbcrlut_15__4_  = snrcbcrlut[15][4];
    V0_COLOR_BASED_LUT_16b.bits.snrcbcrlut_15__5_  = snrcbcrlut[15][5];
    V0_COLOR_BASED_LUT_16b.bits.snrcbcrlut_15__6_  = snrcbcrlut[15][6];
    V0_COLOR_BASED_LUT_16b.bits.snrcbcrlut_15__7_  = snrcbcrlut[15][7];
    V0_COLOR_BASED_LUT_16c.bits.snrcbcrlut_15__8_  = snrcbcrlut[15][8];
    V0_COLOR_BASED_LUT_16c.bits.snrcbcrlut_15__9_  = snrcbcrlut[15][9];
    V0_COLOR_BASED_LUT_16c.bits.snrcbcrlut_15__10_ = snrcbcrlut[15][10];
    V0_COLOR_BASED_LUT_16c.bits.snrcbcrlut_15__11_ = snrcbcrlut[15][11];
    V0_COLOR_BASED_LUT_16d.bits.snrcbcrlut_15__12_ = snrcbcrlut[15][12];
    V0_COLOR_BASED_LUT_16d.bits.snrcbcrlut_15__13_ = snrcbcrlut[15][13];
    V0_COLOR_BASED_LUT_16d.bits.snrcbcrlut_15__14_ = snrcbcrlut[15][14];
    V0_COLOR_BASED_LUT_16d.bits.snrcbcrlut_15__15_ = snrcbcrlut[15][15];
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_16d.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_16d.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_16c.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_16c.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_16b.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_16b.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_16a.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_16a.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_15d.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_15d.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_15c.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_15c.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_15b.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_15b.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_15a.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_15a.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_14d.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_14d.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_14c.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_14c.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_14b.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_14b.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_14a.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_14a.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_13d.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_13d.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_13c.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_13c.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_13b.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_13b.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_13a.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_13a.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_12d.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_12d.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_12c.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_12c.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_12b.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_12b.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_12a.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_12a.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_11d.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_11d.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_11c.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_11c.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_11b.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_11b.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_11a.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_11a.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_10d.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_10d.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_10c.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_10c.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_10b.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_10b.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_10a.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_10a.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_09d.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_09d.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_09c.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_09c.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_09b.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_09b.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_09a.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_09a.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_08d.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_08d.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_08c.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_08c.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_08b.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_08b.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_08a.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_08a.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_07d.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_07d.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_07c.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_07c.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_07b.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_07b.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_07a.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_07a.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_06d.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_06d.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_06c.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_06c.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_06b.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_06b.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_06a.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_06a.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_05d.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_05d.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_05c.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_05c.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_05b.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_05b.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_05a.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_05a.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_04d.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_04d.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_04c.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_04c.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_04b.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_04b.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_04a.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_04a.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_03d.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_03d.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_03c.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_03c.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_03b.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_03b.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_03a.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_03a.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_02d.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_02d.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_02c.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_02c.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_02b.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_02b.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_02a.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_02a.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_01d.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_01d.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_01c.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_01c.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_01b.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_01b.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_COLOR_BASED_LUT_01a.u32) + u32Data * VID_OFFSET), V0_COLOR_BASED_LUT_01a.u32);
    return;
#endif
}



//SNR CFG END
#endif

