#include "vdp_hal_comm.h"
#include "vdp_hal_ip_nxg.h"

extern S_VDP_REGS_TYPE *pVdpReg;

HI_VOID VDP_NXG_SetNxgDwmEn(HI_U32 u32Data, HI_U32 dwm_en)
{
	U_V0_NXG_CTRL NXG_CTRL;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_NXG_SetNxgDwmEn Select Wrong Layer ID\n");
	}

	NXG_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_NXG_CTRL.u32) + u32Data * VID_NXG_OFFSET));
	NXG_CTRL.bits.dwm_en = dwm_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_NXG_CTRL.u32) + u32Data * VID_NXG_OFFSET),NXG_CTRL.u32);

	return ;
}


HI_VOID VDP_NXG_SetNxgDebugEn(HI_U32 u32Data, HI_U32 debug_en)
{
	U_V0_NXG_CTRL NXG_CTRL;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_NXG_SetNxgDebugEn Select Wrong Layer ID\n");
	}

	NXG_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_NXG_CTRL.u32) + u32Data * VID_NXG_OFFSET));
	NXG_CTRL.bits.debug_en = debug_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_NXG_CTRL.u32) + u32Data * VID_NXG_OFFSET),NXG_CTRL.u32);

	return ;
}

HI_VOID VDP_NXG_SetNxgWm3dEn(HI_U32 u32Data, HI_U32 wm_3d_en)
{
	U_V0_NXG_CTRL NXG_CTRL;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_NXG_SetNxgDwmEn Select Wrong Layer ID\n");
	}

	NXG_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_NXG_CTRL.u32) + u32Data * VID_NXG_OFFSET));
	NXG_CTRL.bits.wm_3d_en = wm_3d_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_NXG_CTRL.u32) + u32Data * VID_NXG_OFFSET),NXG_CTRL.u32);

	return ;
}

HI_VOID VDP_NXG_SetNxgWm3dEyeEn(HI_U32 u32Data, HI_U32 wm_3d_eye)
{
	U_V0_NXG_CTRL NXG_CTRL;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_NXG_SetNxgDwmEn Select Wrong Layer ID\n");
	}

	NXG_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_NXG_CTRL.u32) + u32Data * VID_NXG_OFFSET));
	NXG_CTRL.bits.wm_3d_eye = wm_3d_eye;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_NXG_CTRL.u32) + u32Data * VID_NXG_OFFSET),NXG_CTRL.u32);

	return ;
}


HI_VOID VDP_NXG_SetNxgFrameRate(HI_U32 u32Data, HI_U32 frame_rate)
{
	U_V0_NXG_CTRL NXG_CTRL;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_NXG_SetNxgFrameRate Select Wrong Layer ID\n");
	}

	NXG_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_NXG_CTRL.u32) + u32Data * VID_NXG_OFFSET));
	NXG_CTRL.bits.frame_rate = frame_rate;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_NXG_CTRL.u32) + u32Data * VID_NXG_OFFSET),NXG_CTRL.u32);

	return ;
}


HI_VOID VDP_NXG_SetNxgKeyin(HI_U32 u32Data, HI_U32 keyin)
{
	U_V0_NXG_KEYIN NXG_KEYIN;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_NXG_SetNxgKeyin Select Wrong Layer ID\n");
	}

	NXG_KEYIN.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_NXG_KEYIN.u32) + u32Data * VID_NXG_OFFSET));
	NXG_KEYIN.bits.keyin = keyin;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_NXG_KEYIN.u32) + u32Data * VID_NXG_OFFSET),NXG_KEYIN.u32);

	return ;
}


HI_VOID VDP_NXG_SetNxgPayload(HI_U32 u32Data, HI_U32 payload_0, HI_U32 payload_1)
{
	U_V0_NXG_PAYLOAD0 NXG_PAYLOAD0;
	U_V0_NXG_PAYLOAD1 NXG_PAYLOAD1;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_NXG_SetNxgPayload0 Select Wrong Layer ID\n");
	}

	NXG_PAYLOAD0.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_NXG_PAYLOAD0.u32) + u32Data * VID_NXG_OFFSET));
	NXG_PAYLOAD0.bits.payload_0 = payload_0;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_NXG_PAYLOAD0.u32) + u32Data * VID_NXG_OFFSET),NXG_PAYLOAD0.u32);

	NXG_PAYLOAD1.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_NXG_PAYLOAD1.u32) + u32Data * VID_NXG_OFFSET));
	NXG_PAYLOAD1.bits.payload_1 = payload_1;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_NXG_PAYLOAD1.u32) + u32Data * VID_NXG_OFFSET),NXG_PAYLOAD1.u32);
	return ;
}

HI_VOID VDP_NXG_SetNxgSetting0(HI_U32 u32Data, HI_U32 setting_0)
{
	U_V0_NXG_SETTING0 NXG_SETTING0;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_NXG_SetNxgSetting0 Select Wrong Layer ID\n");
	}

	NXG_SETTING0.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_NXG_SETTING0.u32) + u32Data * VID_NXG_OFFSET));
	NXG_SETTING0.bits.setting_0 = setting_0;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_NXG_SETTING0.u32) + u32Data * VID_NXG_OFFSET),NXG_SETTING0.u32);

	return ;
}


HI_VOID VDP_NXG_SetNxgSetting1(HI_U32 u32Data, HI_U32 setting_1)
{
	U_V0_NXG_SETTING1 NXG_SETTING1;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_NXG_SetNxgSetting1 Select Wrong Layer ID\n");
	}

	NXG_SETTING1.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_NXG_SETTING1.u32) + u32Data * VID_NXG_OFFSET));
	NXG_SETTING1.bits.setting_1 = setting_1;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_NXG_SETTING1.u32) + u32Data * VID_NXG_OFFSET),NXG_SETTING1.u32);

	return ;
}


HI_VOID VDP_NXG_SetNxgSetting2(HI_U32 u32Data, HI_U32 setting_2)
{
	U_V0_NXG_SETTING2 NXG_SETTING2;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_NXG_SetNxgSetting2 Select Wrong Layer ID\n");
	}

	NXG_SETTING2.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_NXG_SETTING2.u32) + u32Data * VID_NXG_OFFSET));
	NXG_SETTING2.bits.setting_2 = setting_2;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_NXG_SETTING2.u32) + u32Data * VID_NXG_OFFSET),NXG_SETTING2.u32);

	return ;
}


HI_VOID VDP_NXG_SetNxgSetting3(HI_U32 u32Data, HI_U32 setting_3)
{
	U_V0_NXG_SETTING3 NXG_SETTING3;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_NXG_SetNxgSetting3 Select Wrong Layer ID\n");
	}

	NXG_SETTING3.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_NXG_SETTING3.u32) + u32Data * VID_NXG_OFFSET));
	NXG_SETTING3.bits.setting_3 = setting_3;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_NXG_SETTING3.u32) + u32Data * VID_NXG_OFFSET),NXG_SETTING3.u32);

	return ;
}


HI_VOID VDP_NXG_SetNxgSetting4(HI_U32 u32Data, HI_U32 setting_4)
{
	U_V0_NXG_SETTING4 NXG_SETTING4;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_NXG_SetNxgSetting4 Select Wrong Layer ID\n");
	}

	NXG_SETTING4.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_NXG_SETTING4.u32) + u32Data * VID_NXG_OFFSET));
	NXG_SETTING4.bits.setting_4 = setting_4;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_NXG_SETTING4.u32) + u32Data * VID_NXG_OFFSET),NXG_SETTING4.u32);

	return ;
}


HI_VOID VDP_NXG_SetNxgSetting5(HI_U32 u32Data, HI_U32 setting_5)
{
	U_V0_NXG_SETTING5 NXG_SETTING5;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_NXG_SetNxgSetting5 Select Wrong Layer ID\n");
	}

	NXG_SETTING5.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_NXG_SETTING5.u32) + u32Data * VID_NXG_OFFSET));
	NXG_SETTING5.bits.setting_5 = setting_5;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_NXG_SETTING5.u32) + u32Data * VID_NXG_OFFSET),NXG_SETTING5.u32);

	return ;
}

#if 0
HI_VOID VDP_NXG_SetNxgSetting(HI_U32 u32Data, HI_U32 setting[6])
{
    U_V0_NXG_SETTING0 NXG_SETTING0;

    HI_U32 i ;

    if(u32Data >= VID_MAX)
    {
        VDP_PRINT("Error, VDP_NXG_SetNxgSetting0 Select Wrong Layer ID\n");
    }

    for(i=0; i<6; i++)
    {
        NXG_SETTING0.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_NXG_SETTING0.u32) + u32Data * VID_NXG_OFFSET + 1*4));
        NXG_SETTING0.bits.setting_0 = setting[i];
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_NXG_SETTING0.u32) + u32Data * VID_NXG_OFFSET + 1*4),NXG_SETTING0.u32); 

    }
    return ;
}
#endif

HI_VOID VDP_NXG_SetNxgVideoYfpos(HI_U32 u32Data, HI_U32 video_yfpos)
{
	U_V0_NXG_FPOS NXG_FPOS;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_NXG_SetNxgVideoYfpos Select Wrong Layer ID\n");
	}

	NXG_FPOS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_NXG_FPOS.u32) + u32Data * VID_NXG_OFFSET));
	NXG_FPOS.bits.video_yfpos = video_yfpos;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_NXG_FPOS.u32) + u32Data * VID_NXG_OFFSET),NXG_FPOS.u32);

	return ;
}


HI_VOID VDP_NXG_SetNxgVideoXfpos(HI_U32 u32Data, HI_U32 video_xfpos)
{
	U_V0_NXG_FPOS NXG_FPOS;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_NXG_SetNxgVideoXfpos Select Wrong Layer ID\n");
	}

	NXG_FPOS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_NXG_FPOS.u32) + u32Data * VID_NXG_OFFSET));
	NXG_FPOS.bits.video_xfpos = video_xfpos;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_NXG_FPOS.u32) + u32Data * VID_NXG_OFFSET),NXG_FPOS.u32);

	return ;
}


HI_VOID VDP_NXG_SetNxgVideoYlpos(HI_U32 u32Data, HI_U32 video_ylpos)
{
	U_V0_NXG_LPOS NXG_LPOS;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_NXG_SetNxgVideoYlpos Select Wrong Layer ID\n");
	}

	NXG_LPOS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_NXG_LPOS.u32) + u32Data * VID_NXG_OFFSET));
	NXG_LPOS.bits.video_ylpos = video_ylpos - 1;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_NXG_LPOS.u32) + u32Data * VID_NXG_OFFSET),NXG_LPOS.u32);

	return ;
}


HI_VOID VDP_NXG_SetNxgVideoXlpos(HI_U32 u32Data, HI_U32 video_xlpos)
{
	U_V0_NXG_LPOS NXG_LPOS;

	if(u32Data >= VID_MAX)
	{
		VDP_PRINT("Error, VDP_NXG_SetNxgVideoXlpos Select Wrong Layer ID\n");
	}

	NXG_LPOS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_NXG_LPOS.u32) + u32Data * VID_NXG_OFFSET));
	NXG_LPOS.bits.video_xlpos = video_xlpos - 1;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_NXG_LPOS.u32) + u32Data * VID_NXG_OFFSET),NXG_LPOS.u32);

	return ;
}

