Configuration files in default SDK package:

	1.hi3798mv2dmo_hi3798mv200_cfg.mak
		The default configuration file for common usage(no ADVCA, no TEE, no DRM), which support HI3798MV2DMA/B/C/E/P EVB.

	2.hi3798mv2dmg_hi3798mv200_cfg.mak
		The configuration file for HI3798MV2DMG EVB, common usage(no ADVCA, no TEE, no DRM).

	3.hi3798mv2dmo_hi3798mv200_apploader_cfg.mak
		The configuration file for apploader image compile, independent of EVB type.

Confiuration files in other individual component packages:

	Only describes the feature fields of configuration files in individual component packages.

	1.ADVCA
		A configuration file that supports the ADVCA feature contains the corresponding CAS name, such as "suma_cardless".
		For example, "hi3798mv2dma_hi3798mv200_suma_cardless_cfg.mak" means it's a configuration file support SUMA cardless chipset on HI3798MV2DMA EVB.

	2.TEE
		A configuration file that supports the SecureOS feature but not CAS, contains the corresponding string "TEE". 
		DRM could refer to this configuration.
		For example, "hi3798mv2dma_hi3798mv200_TEE_cfg.mak" means it's a configuration file support TEE feature on HI3798MV2DMA EVB.

