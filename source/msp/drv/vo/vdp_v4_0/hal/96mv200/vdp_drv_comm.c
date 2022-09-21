#include "vdp_drv_comm.h"
#include "vdp_fpga_define.h"
VDP_COEF_ADDR_S gstVdpCoefBufAddr;

#if (VDP_CBB_FPGA &&  !defined(__DISP_PLATFORM_BOOT__))
#include "hi_drv_mmz.h"
#if FPGA_AUTORUN
#include "vdp_util.h"
#endif
#endif
extern  HI_S32 HI_DRV_PDM_AllocReserveMem(const HI_CHAR *BufName, HI_U32 u32Len, HI_U32 *pu32PhyAddr);
//----------------------------------------------------------------------
// memory/address managerment
//----------------------------------------------------------------------
HI_S32 VDP_DRV_AllocateMem(HI_U32 u32Size,VDP_MMZ_BUFFER_S *stVdpMmzBuffer)
{
#if (VDP_CBB_FPGA &&  !defined(__DISP_PLATFORM_BOOT__))
	HI_S32 nRet;
	nRet = HI_DRV_MMZ_AllocAndMap("VDP_DDR_CFG", HI_NULL, u32Size, 0, (MMZ_BUFFER_S *)stVdpMmzBuffer);
	if (nRet != 0)
	{
		 VDP_PRINT("VDP_DDR_CFG  failed\n");
		 return HI_FAILURE;
	}
#elif (defined(__DISP_PLATFORM_BOOT__))
	HI_S32 nRet;
    nRet = HI_DRV_PDM_AllocReserveMem("VDP_DDR_CFG", u32Size, &stVdpMmzBuffer->u32StartPhyAddr);
    if (nRet != 0)
	{
		 VDP_PRINT("VDP_DDR_CFG  failed\n");
		 return HI_FAILURE;
	}
	stVdpMmzBuffer->pu8StartVirAddr = HI_NULL;
	stVdpMmzBuffer->u32Size         = u32Size;
#else
    stVdpMmzBuffer->pu8StartVirAddr = (HI_U8*)0x8000000;
    stVdpMmzBuffer->u32StartPhyAddr = 0x8000000;
#endif

    return HI_SUCCESS;
}


HI_S32 VDP_DRV_DeleteMem(VDP_MMZ_BUFFER_S *stVdpMmzBuffer)
{
#if (VDP_CBB_FPGA &&  !defined(__DISP_PLATFORM_BOOT__))
    HI_DRV_MMZ_UnmapAndRelease((MMZ_BUFFER_S *)stVdpMmzBuffer);
#elif (defined(__DISP_PLATFORM_BOOT__))
#endif
    return HI_SUCCESS;
}

HI_S32 VDP_DRV_IoRemap(HI_U32 u32Phy, HI_U32 u32Size,HI_U32 **pu32VirtualAddr)
{
#if (VDP_CBB_FPGA &&  !defined(__DISP_PLATFORM_BOOT__))

	*pu32VirtualAddr = ioremap_nocache(u32Phy, u32Size);
    if (HI_NULL == *pu32VirtualAddr)
    {
		return HI_FAILURE;
	}
#elif (defined(__DISP_PLATFORM_BOOT__))
#endif

	return HI_SUCCESS;
}

HI_S32 VDP_DRV_IoUnmap(HI_U32 **pu32VirtualAddr)
{
#if (VDP_CBB_FPGA &&  !defined(__DISP_PLATFORM_BOOT__))
	(HI_VOID)iounmap(*pu32VirtualAddr);
	*pu32VirtualAddr = HI_NULL;
#endif

	return HI_SUCCESS;
}

HI_S32 VDP_DRV_CoefBufAddrDistribute(VDP_COEF_ADDR_S *stVdpCoefBufAddr)
{
    HI_U32 u32CoefAlign = 0x10;//0x10 ;
    //printk("stVdpCoefBufAddr->stBufBaseAddr.pu8StartVirAddr= %x\n",stVdpCoefBufAddr->stBufBaseAddr.pu8StartVirAddr);

    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_NO_USE   ]  = stVdpCoefBufAddr->stBufBaseAddr.pu8StartVirAddr + 0;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_IN_GAMMA ]  = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_NO_USE] + COEF_SIZE_NO_USE - u32CoefAlign;

    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_OUT_GAMMA  ]  = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_IN_GAMMA   ] + COEF_SIZE_IN_GAMMA   - u32CoefAlign;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_IN_DEGAMMA ]  = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_OUT_GAMMA  ] + COEF_SIZE_OUT_GAMMA  - u32CoefAlign;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_OUT_DEGAMMA]  = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_IN_DEGAMMA ] + COEF_SIZE_IN_DEGAMMA - u32CoefAlign;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_CVM        ]  = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_OUT_DEGAMMA] + COEF_SIZE_OUT_DEGAMMA - u32CoefAlign;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_GDM_GAMMA  ]  = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_CVM        ] + COEF_SIZE_CVM        - u32CoefAlign;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_GDM_DEGAMMA]  = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_GDM_GAMMA  ] + COEF_SIZE_GDM_GAMMA  - u32CoefAlign;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_ZMEH]  = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_GDM_DEGAMMA] + COEF_SIZE_GDM_DEGAMMA       - u32CoefAlign;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_ZMEV]  = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_ZMEH] + COEF_SIZE_ZMEH  - u32CoefAlign;

    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_ZME2H]  = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_ZMEV] + COEF_SIZE_ZMEV  - u32CoefAlign;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_ZME2V]  = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_ZME2H] + COEF_SIZE_ZME2H - u32CoefAlign;

    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_ZME_V1_H]  = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_ZME2V] + COEF_SIZE_ZMEV - u32CoefAlign;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_ZME_V1_V]  = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_ZME_V1_H] + COEF_SIZE_ZMEH - u32CoefAlign;


    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP] = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_ZME_V1_V] + COEF_SIZE_ZMEV  - u32CoefAlign;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_VMX_V0]  = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP] + COEF_SIZE_ZME_TMP - u32CoefAlign;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_VMX_V1]  = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_VMX_V0] + COEF_SIZE_VMX_V0 - u32CoefAlign;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_VMX_VP0] = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_VMX_V1] + COEF_SIZE_VMX_V1 - u32CoefAlign;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_WBC_ZMEH]  = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_VMX_VP0] + COEF_SIZE_VMX_VP0 - u32CoefAlign;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_WBC_ZMEV] = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_WBC_ZMEH] + COEF_SIZE_WBC_ZMEH  - u32CoefAlign;

    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_HDR_METADATA] = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_WBC_ZMEV] + COEF_SIZE_WBC_ZMEV - u32CoefAlign;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_TCHDR_C] = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_HDR_METADATA] + COEF_SIZE_TCHDR  - u32CoefAlign;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_TCHDR_P] = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_TCHDR_C] + COEF_SIZE_TCHDR  - u32CoefAlign;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_TCHDR_S] = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_TCHDR_P] + COEF_SIZE_TCHDR - u32CoefAlign;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_TCHDR_I] = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_TCHDR_S] + COEF_SIZE_TCHDR - u32CoefAlign;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_TCHDR_D] = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_TCHDR_I] + COEF_SIZE_TCHDR  - u32CoefAlign;

    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_VDM_DEGAMMA] = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_TCHDR_D]  + COEF_SIZE_TCHDR  - u32CoefAlign;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_VDM_GAMMA] = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_VDM_DEGAMMA] + COEF_SIZE_VDM_DEGAMMA - u32CoefAlign;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_VDM_TONEMAP] = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_VDM_GAMMA] + COEF_SIZE_VDM_GAMMA - u32CoefAlign;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_VDM_SMAP] = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_VDM_TONEMAP] + COEF_SIZE_VDM_TONEMAP  - u32CoefAlign;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_GDM_GAMMA2] = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_VDM_SMAP] + COEF_SIZE_VDM_SMAP  - u32CoefAlign;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_GDM_TONEMAP] = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_GDM_GAMMA2] + COEF_SIZE_GDM_GAMMA2  - u32CoefAlign;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_GCVM] = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_GDM_TONEMAP] + COEF_SIZE_GDM_TONEMAP - u32CoefAlign;

    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_MUTE_V1_L] = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_GCVM] + COEF_SIZE_HDR_METADATA ;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_MUTE_V1_C] = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_MUTE_V1_L] + COEF_SIZE_V1_MUTE_L ;


	memset((HI_VOID *)stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_MUTE_V1_L],0x10,COEF_SIZE_V1_MUTE_L);
	memset((HI_VOID *)stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_MUTE_V1_C],0x80,COEF_SIZE_V1_MUTE_C);

    //printk("stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_GCVM] = %x\n",stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_GCVM]);
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_NO_USE   ]  = stVdpCoefBufAddr->stBufBaseAddr.u32StartPhyAddr + 0;

    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_IN_GAMMA   ]  = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_NO_USE   ] + COEF_SIZE_NO_USE - u32CoefAlign;
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_OUT_GAMMA  ]  = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_IN_GAMMA   ] + COEF_SIZE_IN_GAMMA   - u32CoefAlign;
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_IN_DEGAMMA ]  = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_OUT_GAMMA  ] + COEF_SIZE_OUT_GAMMA  - u32CoefAlign;
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_OUT_DEGAMMA]  = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_IN_DEGAMMA ] + COEF_SIZE_IN_DEGAMMA - u32CoefAlign;
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_CVM        ]  = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_OUT_DEGAMMA] + COEF_SIZE_OUT_DEGAMMA - u32CoefAlign;
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_GDM_GAMMA  ]  = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_CVM        ] + COEF_SIZE_CVM        - u32CoefAlign;
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_GDM_DEGAMMA]  = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_GDM_GAMMA  ] + COEF_SIZE_GDM_GAMMA  - u32CoefAlign;


    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_ZMEH]  = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_GDM_DEGAMMA] + COEF_SIZE_GDM_DEGAMMA  - u32CoefAlign;
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_ZMEV]  = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_ZMEH] + COEF_SIZE_ZMEH  - u32CoefAlign;

    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_ZME2H]  = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_ZMEV] + COEF_SIZE_ZMEV  - u32CoefAlign;
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_ZME2V]  = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_ZME2H] + COEF_SIZE_ZME2H - u32CoefAlign;

    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_ZME_V1_H]  = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_ZME2V] + COEF_SIZE_ZMEV  - u32CoefAlign;
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_ZME_V1_V]  = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_ZME_V1_H] + COEF_SIZE_ZMEH - u32CoefAlign;

    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_ZME_TMP]  = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_ZME_V1_V] + COEF_SIZE_ZMEV  - u32CoefAlign;
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_VMX_V0]  = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_ZME_TMP] + COEF_SIZE_ZME_TMP  - u32CoefAlign;


    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_VMX_V1]  = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_VMX_V0] + COEF_SIZE_VMX_V0 - u32CoefAlign;
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_VMX_VP0] = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_VMX_V1] + COEF_SIZE_VMX_V1 - u32CoefAlign;

    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_WBC_ZMEH]  = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_VMX_VP0] + COEF_SIZE_VMX_VP0 - u32CoefAlign;
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_WBC_ZMEV] = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_WBC_ZMEH] + COEF_SIZE_WBC_ZMEH - u32CoefAlign;

    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_HDR_METADATA] = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_WBC_ZMEV] + COEF_SIZE_WBC_ZMEV - u32CoefAlign;
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_TCHDR_C] = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_HDR_METADATA] + COEF_SIZE_TCHDR  - u32CoefAlign;
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_TCHDR_P] = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_TCHDR_C] + COEF_SIZE_TCHDR   - u32CoefAlign;
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_TCHDR_S] = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_TCHDR_P] + COEF_SIZE_TCHDR  - u32CoefAlign;
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_TCHDR_I] = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_TCHDR_S] + COEF_SIZE_TCHDR  - u32CoefAlign;
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_TCHDR_D] = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_TCHDR_I] + COEF_SIZE_TCHDR  - u32CoefAlign;

    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_VDM_DEGAMMA]  = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_TCHDR_D] + COEF_SIZE_TCHDR  - u32CoefAlign;
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_VDM_GAMMA] = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_VDM_DEGAMMA] + COEF_SIZE_VDM_DEGAMMA  - u32CoefAlign;
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_VDM_TONEMAP] = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_VDM_GAMMA] + COEF_SIZE_VDM_GAMMA  - u32CoefAlign;
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_VDM_SMAP] = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_VDM_TONEMAP] + COEF_SIZE_VDM_TONEMAP  - u32CoefAlign;

    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_GDM_GAMMA2] = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_VDM_SMAP] + COEF_SIZE_VDM_SMAP  - u32CoefAlign;
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_GDM_TONEMAP] = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_GDM_GAMMA2] + COEF_SIZE_GDM_GAMMA2  - u32CoefAlign;

    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_GCVM] = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_GDM_TONEMAP] + COEF_SIZE_GDM_TONEMAP - u32CoefAlign;

    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_MUTE_V1_L] = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_GCVM] + COEF_SIZE_HDR_METADATA ;
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_MUTE_V1_C] = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_MUTE_V1_L] + COEF_SIZE_V1_MUTE_L ;

    //printk("stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_GCVM] = %x\n",stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_GCVM]);
    return HI_SUCCESS;
}


HI_S32 VDP_DRV_LayerBufAddrDistribute(VDP_LAYER_BUF_ADDR_S  *stVdpLayerBufAddr)
{
#if EDA_TEST
    stVdpLayerBufAddr->u32BufAddr[VDP_BUF_V0]  = stVdpLayerBufAddr->stBufBaseAddr.u32StartVirAddr + 0;
    stVdpLayerBufAddr->u32BufAddr[VDP_BUF_V1]  = stVdpLayerBufAddr->u32BufAddr[VDP_BUF_V0] + VDP_BUF_SIZE_V0;
    stVdpLayerBufAddr->u32BufAddr[VDP_BUF_V2]  = stVdpLayerBufAddr->u32BufAddr[VDP_BUF_V1] + VDP_BUF_SIZE_V1;
    stVdpLayerBufAddr->u32BufAddr[VDP_BUF_V3]  = stVdpLayerBufAddr->u32BufAddr[VDP_BUF_V2] + VDP_BUF_SIZE_V2;
    stVdpLayerBufAddr->u32BufAddr[VDP_BUF_V4]  = stVdpLayerBufAddr->u32BufAddr[VDP_BUF_V3] + VDP_BUF_SIZE_V3;
#endif

    return HI_SUCCESS;
}

//----------------------------------------------------------------------
// function
//----------------------------------------------------------------------
/*
HI_U32 uGetRand(HI_U32 max, HI_U32 min)
{
	#if  0
    HI_U32 u32_max_data = 0;
    HI_U32 u32_min_data = 0;

    if(max > min)
    {
        u32_max_data = max;
        u32_min_data = min;
    }
    else
    {
        u32_max_data = min;
        u32_min_data = max;
    }

    return (u32_min_data + rand()%((HI_U32)u32_max_data + 1 - u32_min_data));
	#endif
	return HI_SUCCESS;
}

HI_S32 sGetRand(HI_S32 max, HI_S32 min)
{
	#if  0
    HI_U32 u32_max_data = 0;
    HI_U32 u32_min_data = 0;

    HI_S32 s32_return_data = 0;

    if(((max == 0)&&(min == 0)) || (min == max))
    {
        //cout << "Error, Worng sRand seed!" << endl;
    }
    else if(((max >= 0)&&(min > 0)) || ((max > 0)&&(min >= 0)))
    {
        if(max > min)
        {
            u32_max_data = max;
            u32_min_data = min;
        }
        else
        {
            u32_max_data = min;
            u32_min_data = max;
        }

        s32_return_data = (u32_min_data + rand()%(u32_max_data + 1 - u32_min_data));
    }
    else if(((max <= 0)&&(min < 0)) || ((max < 0)&&(min <= 0)))
    {
        if(VDP_ABS(max) > VDP_ABS(min))
        {
            u32_max_data = VDP_ABS(max);
            u32_min_data = VDP_ABS(min);
        }
        else
        {
            u32_max_data = VDP_ABS(min);
            u32_min_data = VDP_ABS(max);
        }

        s32_return_data = -(u32_min_data + rand()%(u32_max_data + 1 - u32_min_data));
    }
    else
    {
        if((max > 0)&&(min < 0))
        {
            u32_max_data = VDP_ABS(max);
            u32_min_data = VDP_ABS(min);
        }
        else
        {
            u32_max_data = VDP_ABS(min);
            u32_min_data = VDP_ABS(max);
        }

        if(rand()%2 == 0)
        {
            s32_return_data = -(rand()%(u32_min_data + 1));
        }
        else
        {
            s32_return_data =    rand()%(u32_max_data + 1);
        }
    }

    return s32_return_data;
	#endif

	return HI_SUCCESS;
}


HI_U32 uGetRandEx(HI_U32 max, HI_U32 min)
{
	#if  1
    HI_U32 u32_max_data = 0;
    HI_U32 u32_min_data = 0;

    if(max > min)
    {
        u32_max_data = max;
        u32_min_data = min;
    }
    else
    {
        u32_max_data = min;
        u32_min_data = max;
    }

    return (u32_min_data + rand()%((HI_U32)u32_max_data + 1 - u32_min_data));
	#endif

	return HI_SUCCESS;
}

HI_S32 sGetRandEx(HI_S32 max, HI_S32 min)
{
	#if  1
    HI_U32 u32_max_data = 0;
    HI_U32 u32_min_data = 0;

    HI_S32 s32_return_data = 0;

    if(((max == 0)&&(min == 0)) || (min == max))
    {
      //  cout << "Error, Worng sRand seed!" << endl;
    }
    if(((max >= 0)&&(min > 0)) || ((max > 0)&&(min >= 0)))
    {
        if(max > min)
        {
            u32_max_data = max;
            u32_min_data = min;
        }
        else
        {
            u32_max_data = min;
            u32_min_data = max;
        }

        s32_return_data = (u32_min_data + rand()%(u32_max_data + 1 - u32_min_data));
    }
    else if(((max <= 0)&&(min < 0)) || ((max < 0)&&(min <= 0)))
    {
        if(VDP_ABS(max) > VDP_ABS(min))
        {
            u32_max_data = VDP_ABS(max);
            u32_min_data = VDP_ABS(min);
        }
        else
        {
            u32_max_data = VDP_ABS(min);
            u32_min_data = VDP_ABS(max);
        }

        s32_return_data = -(u32_min_data + rand()%(u32_max_data + 1 - u32_min_data));
    }
    else
    {
        if((max > 0)&&(min < 0))
        {
            u32_max_data = VDP_ABS(max);
            u32_min_data = VDP_ABS(min);
        }
        else
        {
            u32_max_data = VDP_ABS(min);
            u32_min_data = VDP_ABS(max);
        }

        if(rand()%2 == 0)
        {
            s32_return_data = -(rand()%(u32_min_data + 1));
        }
        else
        {
            s32_return_data =    rand()%(u32_max_data + 1);
        }
    }

    return s32_return_data;
	#endif

	return HI_SUCCESS;
}

*/



