#########################################################################
## NOTE: This file is included in trustedcore/trustedcore_kernel/Android.mk
#########################################################################

DEVCHIP_TEE_C := ../platform/devchip/$(PLATFORM_DIR_NAME)/tee
DEVCHIP_TEE_H := ${LOCAL_PATH}/../platform/devchip/$(PLATFORM_DIR_NAME)/tee

#########################################################################
# kernel include
#########################################################################
DEVCHIP_KERNEL_INS := \
	${LOCAL_PATH}/../platform/devchip/$(PLATFORM_DIR_NAME)/ext/kernel \
	$(DEVCHIP_TEE_H)/api/include \
	$(DEVCHIP_TEE_H)/drv/include \
	$(DEVCHIP_TEE_H)/drv/timer

ifeq ($(strip $(CFG_HI_TEE_CIPHER_SUPPORT)), y)
DEVCHIP_KERNEL_INS += \
	$(DEVCHIP_TEE_H)/drv/cipher \
	$(DEVCHIP_TEE_H)/drv/cipher/rsa \
	$(DEVCHIP_TEE_H)/drv/cipher/tee/include
endif

ifeq ($(CFG_HI_TEE_SMMU_SUPPORT), y)
DEVCHIP_KERNEL_INS += $(DEVCHIP_TEE_H)/drv/mem/hi_smmu/include
endif

ifeq ($(CFG_HI_TEE_SEC_MMZ_SUPPORT), y)
DEVCHIP_KERNEL_INS += \
	$(DEVCHIP_TEE_H)/drv/mem/sec_mmz/include \
	$(DEVCHIP_TEE_H)/drv/mem/sec_mmz
endif

DEVCHIP_DRV_INS :=
#########################################################################
# devchip driver include
#########################################################################
ifeq ($(CFG_HI_TEE_VDP_SUPPORT), y)
DEVCHIP_DRV_INS += \
	$(DEVCHIP_TEE_H)/drv/vdp \
	$(DEVCHIP_TEE_H)/drv/vdp/drv \
	$(DEVCHIP_TEE_H)/drv/vdp/hal \
	$(DEVCHIP_TEE_H)/drv/vdp/hal/98cv200 \
	$(DEVCHIP_TEE_H)/drv/vdp/hal/98cv200/inc
endif

#########################################################################
# hdmi
#########################################################################
ifeq ($(CFG_HI_TEE_HDMI_SUPPORT), y)
DEVCHIP_DRV_INS += \
	$(DEVCHIP_TEE_H)/drv/hdmi
endif

#########################################################################
# dmx
#########################################################################
ifeq ($(CFG_HI_TEE_DEMUX_SUPPORT), y)
DEVCHIP_DRV_INS += $(DEVCHIP_TEE_H)/drv/demux
endif

ifeq ($(CFG_HI_TEE_PLCIPHER_SUPPORT), y)
DEVCHIP_DRV_INS += $(DEVCHIP_TEE_H)/drv/plcipher
endif


#########################################################################
# avplay
#########################################################################
ifeq ($(CFG_HI_TEE_AVPLAY_SUPPORT), y)
DEVCHIP_DRV_INS += -I$(DEVCHIP_TEE_H)/drv/avplay \
		   -I$(DEVCHIP_TEE_H)/api/avplay
endif

#########################################################################
# netflix
#########################################################################
ifeq ($(CFG_HI_TEE_NETFLIX_SUPPORT), y)
DEVCHIP_DRV_INS += -I$(DEVCHIP_TEE_H)/drv/netflix \
		   -I$(DEVCHIP_TEE_H)/api/netflix
endif


#########################################################################
# kernel src
#########################################################################
DEVCHIP_KERNEL_SRCS := \
	../platform/devchip/$(PLATFORM_DIR_NAME)/ext/kernel/sre_syscallDispatch_chip.c

INCLUDE += \
	$(DEVCHIP_KERNEL_INS) \
	$(DEVCHIP_DRV_INS)
TRUSTEDCORE_SRCS += $(DEVCHIP_KERNEL_SRCS)

#########################################################################
# devchip libs
#########################################################################
PLATFORM_DEVCHIP_STATIC_LIB := libstbdrv
