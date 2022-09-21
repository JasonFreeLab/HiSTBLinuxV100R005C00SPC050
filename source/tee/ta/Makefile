################################################################
# build
################################################################
.PHONY : all clean

all:
ifeq ($(strip $(CFG_HI_TEE_SEC_MMZ_SUPPORT)), y)
	$(MAKE) -C mmz all
endif

ifeq ($(strip $(CFG_HI_TEE_KLAD_SUPPORT)), y)
	$(MAKE) -C klad all
endif

ifeq ($(strip $(CFG_HI_TEE_SMMU_SUPPORT)), y)
	$(MAKE) -C smmu all
endif

ifeq ($(strip $(CFG_HI_TEE_DEMUX_SUPPORT)), y)
	$(MAKE) -C demux all
endif

ifeq ($(strip $(CFG_HI_TEE_PLCIPHER_SUPPORT)), y)
	$(MAKE) -C plcipher all
endif

ifeq ($(strip $(CFG_HI_TEE_CRYPTOEN_SUPPORT)), y)
	$(MAKE) -C cryptoen all
endif

ifeq ($(strip $(CFG_HI_TEE_PVR_SUPPORT)), y)
	$(MAKE) -C pvr all
endif

ifeq ($(strip $(CFG_HI_TEE_AVPLAY_SUPPORT)), y)
	$(MAKE) -C avplay all
endif

ifeq ($(strip $(CFG_HI_TEE_HDMI_SUPPORT)), y)
	$(MAKE) -C hdmi all
endif

ifeq ($(strip $(CFG_HI_TEE_VFMW_SUPPORT)), y)
	$(MAKE) -C vfmw all
endif
ifeq ($(strip $(CFG_HI_TEE_WIDEVINE_SUPPORT)), y)
	$(MAKE) -C widevine all
endif

ifeq ($(strip $(CFG_HI_TEE_EMPTYDRM_SUPPORT)), y)
	$(MAKE) -C emptydrm all
endif

ifeq ($(strip $(CFG_HI_TEE_PLAYREADY_SUPPORT)), y)
	$(MAKE) -C playready all
endif

ifeq ($(strip $(CFG_HI_TEE_TEST_SUPPORT)), y)
	$(MAKE) -C test all
endif

ifeq ($(strip $(CFG_HI_TEE_NETFLIX_SUPPORT)), y)
	$(MAKE) -C netflix all
endif

ifeq ($(strip $(CFG_HI_TEE_VMX_ULTRA_SUPPORT)), y)
	$(MAKE) -C component/vmx/ultra/HI3798CV200/vmxtac_VMXTA.HSL_HI3798CV200_I all
	$(MAKE) -C component/vmx/ultra/HI3798CV200/vmxtac_videomarkTA.HSL_HI3798CV200_I all
endif
ifeq ($(strip $(CFG_HI_TEE_VMXTAC_TEST_SUPPORT)), y)
	$(MAKE) -C component/vmx/ultra/HI3798CV200/vmxtac_VMXTA.HSL_HI3798CV200_I all
	$(MAKE) -C component/vmx/ultra/HI3798CV200/vmxtac_videomarkTA.HSL_HI3798CV200_I all
	$(MAKE) -C component/vmx/ultra/HI3798CV200/vmxtac_clientId2TA.HSL_HI3798CV200_I all
	$(MAKE) -C component/vmx/ultra/HI3798CV200/vmxtac_clientId3TA.HSL_HI3798CV200_I all
endif
ifeq ($(strip $(CFG_HI_TEE_ITAC_TEST_SUPPORT)), y)
	$(MAKE) -C component/vmx/ultra/HI3798CV200/vmxtac_VMXTA.HSL_HI3798CV200_I all
	$(MAKE) -C component/vmx/ultra/HI3798CV200/vmxtac_videomarkTA.HSL_HI3798CV200_I all
	$(MAKE) -C component/vmx/ultra/HI3798CV200/vmxtac_clientId2TA.HSL_HI3798CV200_I all
	$(MAKE) -C component/vmx/ultra/HI3798CV200/vmxtac_clientId3TA.HSL_HI3798CV200_I all
endif

ifeq ($(strip $(CFG_HI_TEE_DEMO_SUPPORT)), y)
	$(MAKE) -C demo all
endif

ifeq ($(strip $(CFG_HI_TEE_VDP_VERIMATRIX_SUPPORT)), y)
	$(MAKE) -C task_hisi_vdp all
endif

ifeq ($(strip $(CFG_HI_TEE_CRYVER_SUPPORT)), y)
	$(MAKE) -C crypto_verify all
endif

ifeq ($(strip $(CFG_HI_TEE_SUMA_SUPPORT)), y)
	$(MAKE) -C component/suma all
endif

ifeq ($(strip $(CFG_HI_TEE_SM_SUPPORT)), y)
	$(MAKE) -C session_manage all
endif

ifeq ($(strip $(CFG_HI_TEE_CRYPTOEN_SUPPORT)), y)
	$(MAKE) -C component/nagra all
endif

clean:
ifeq ($(strip $(CFG_HI_TEE_SEC_MMZ_SUPPORT)), y)
	$(MAKE) -C mmz clean
endif

ifeq ($(strip $(CFG_HI_TEE_SMMU_SUPPORT)), y)
	$(MAKE) -C smmu clean
endif

ifeq ($(strip $(CFG_HI_TEE_KLAD_SUPPORT)), y)
	$(MAKE) -C klad clean
endif

ifeq ($(strip $(CFG_HI_TEE_DEMUX_SUPPORT)), y)
	$(MAKE) -C demux clean
endif

ifeq ($(strip $(CFG_HI_TEE_CRYPTOEN_SUPPORT)), y)
	$(MAKE) -C cryptoen clean
endif

ifeq ($(strip $(CFG_HI_TEE_VFMW_SUPPORT)), y)
	$(MAKE) -C vfmw clean
endif

ifeq ($(strip $(CFG_HI_TEE_PVR_SUPPORT)), y)
	$(MAKE) -C pvr clean
endif

ifeq ($(strip $(CFG_HI_TEE_AVPLAY_SUPPORT)), y)
	$(MAKE) -C avplay clean
endif

#	$(MAKE) -C test clean
ifeq ($(strip $(CFG_HI_TEE_WIDEVINE_SUPPORT)), y)
	$(MAKE) -C widevine clean
endif

ifeq ($(strip $(CFG_HI_TEE_EMPTYDRM_SUPPORT)), y)
	$(MAKE) -C emptydrm clean
endif

ifeq ($(strip $(CFG_HI_TEE_PLAYREADY_SUPPORT)), y)
	$(MAKE) -C playready clean
endif

ifeq ($(strip $(CFG_HI_TEE_TEST_SUPPORT)), y)
	$(MAKE) -C test clean
endif

ifeq ($(strip $(CFG_HI_TEE_NETFLIX_SUPPORT)), y)
	$(MAKE) -C netflix clean
endif

ifeq ($(strip $(CFG_HI_TEE_HDMI_SUPPORT)), y)
	$(MAKE) -C hdmi clean
endif

ifeq ($(strip $(CFG_HI_TEE_VMX_ULTRA_SUPPORT)), y)
	$(MAKE) -C component/vmx/ultra/HI3798CV200/vmxtac_VMXTA.HSL_HI3798CV200_I clean
	$(MAKE) -C component/vmx/ultra/HI3798CV200/vmxtac_videomarkTA.HSL_HI3798CV200_I clean
endif

ifeq ($(strip $(CFG_HI_TEE_VMXTAC_TEST_SUPPORT)), y)
	$(MAKE) -C component/vmx/ultra/HI3798CV200/vmxtac_VMXTA.HSL_HI3798CV200_I clean
	$(MAKE) -C component/vmx/ultra/HI3798CV200/vmxtac_videomarkTA.HSL_HI3798CV200_I clean
	$(MAKE) -C component/vmx/ultra/HI3798CV200/vmxtac_clientId2TA.HSL_HI3798CV200_I clean
	$(MAKE) -C component/vmx/ultra/HI3798CV200/vmxtac_clientId3TA.HSL_HI3798CV200_I clean
endif
ifeq ($(strip $(CFG_HI_TEE_ITAC_TEST_SUPPORT)), y)
	$(MAKE) -C component/vmx/ultra/HI3798CV200/vmxtac_VMXTA.HSL_HI3798CV200_I clean
	$(MAKE) -C component/vmx/ultra/HI3798CV200/vmxtac_videomarkTA.HSL_HI3798CV200_I clean
	$(MAKE) -C component/vmx/ultra/HI3798CV200/vmxtac_clientId2TA.HSL_HI3798CV200_I clean
	$(MAKE) -C component/vmx/ultra/HI3798CV200/vmxtac_clientId3TA.HSL_HI3798CV200_I clean
endif

ifeq ($(strip $(CFG_HI_TEE_DEMO_SUPPORT)), y)
	$(MAKE) -C demo clean
endif

ifeq ($(strip $(CFG_HI_TEE_VDP_VERIMATRIX_SUPPORT)), y)
	$(MAKE) -C task_hisi_vdp clean
endif

ifeq ($(strip $(CFG_HI_TEE_CRYVER_SUPPORT)), y)
	$(MAKE) -C crypto_verify clean
endif

ifeq ($(strip $(CFG_HI_TEE_SUMA_SUPPORT)), y)
	$(MAKE) -C component/suma clean
endif

ifeq ($(strip $(CFG_HI_TEE_CRYPTOEN_SUPPORT)), y)
	$(MAKE) -C component/nagra clean
endif

ifeq ($(strip $(CFG_HI_TEE_SM_SUPPORT)), y)
	$(MAKE) -C session_manage clean
endif
