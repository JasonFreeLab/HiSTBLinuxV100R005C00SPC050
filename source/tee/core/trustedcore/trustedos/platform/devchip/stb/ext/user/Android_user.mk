#########################################################################
# NOTE: This file is included by trustedcore/TEE_ext/Android.mk
#       Use to build user API for TA.
#########################################################################

DEVCHIP_TEE_C := ../platform/devchip/$(PLATFORM_DIR_NAME)/tee
DEVCHIP_TEE_H := ${LOCAL_PATH}/../platform/devchip/$(PLATFORM_DIR_NAME)/tee

DEVCHIP_TEE_INS := \
	${LOCAL_PATH}/../platform/devchip/$(PLATFORM_DIR_NAME)/ext/user \
	${LOCAL_PATH}/../platform/devchip/$(PLATFORM_DIR_NAME)/ext/user/asm_mem \
	${LOCAL_PATH}/../platform/devchip/$(PLATFORM_DIR_NAME)/ext/kernel \
	$(DEVCHIP_TEE_H)/api/mem/include \
	$(DEVCHIP_TEE_H)/api/include \
	$(DEVCHIP_TEE_H)/drv/include \
	$(DEVCHIP_TEE_H)/drv/timer

DEVCHIP_TEE_SRCS := \
	../platform/devchip/$(PLATFORM_DIR_NAME)/ext/user/sre_syscalls_chip.S

#########################################################################
# asm_memmove
#########################################################################		
DEVCHIP_ASM_MEM_SRCS := \
	../platform/devchip/$(PLATFORM_DIR_NAME)/ext/user/tee_external_api.c \
	../platform/devchip/$(PLATFORM_DIR_NAME)/ext/user/asm_mem/memcpy.S \
	../platform/devchip/$(PLATFORM_DIR_NAME)/ext/user/asm_mem/memmove.S

DEVCHIP_TEE_SRCS += $(DEVCHIP_ASM_MEM_SRCS)

#########################################################################
# cipher
#########################################################################
ifeq ($(strip $(CFG_HI_TEE_CIPHER_SUPPORT)), y)
DEVCHIP_TEE_SRCS += $(DEVCHIP_TEE_C)/api/cipher/hi_tee_cipher.c
endif

#########################################################################
# mmz
#########################################################################
ifeq ($(CFG_HI_TEE_SEC_MMZ_SUPPORT), y)
DEVCHIP_TEE_SRCS += $(DEVCHIP_TEE_C)/api/mem/hi_tee_mmz.c 
endif

#########################################################################
# smmu
#########################################################################
ifeq ($(CFG_HI_TEE_SMMU_SUPPORT), y)
DEVCHIP_TEE_SRCS += $(DEVCHIP_TEE_C)/api/mem/hi_tee_mem.c 
endif

#########################################################################
# vdp
#########################################################################
ifeq ($(CFG_HI_TEE_VDP_SUPPORT), y)
DEVCHIP_TEE_SRCS += $(DEVCHIP_TEE_C)/api/vdp/hi_tee_vdp.c 
endif

#########################################################################
# hdmi
#########################################################################
ifeq ($(CFG_HI_TEE_HDMI_SUPPORT), y)
DEVCHIP_TEE_SRCS += \
	$(DEVCHIP_TEE_C)/api/hdmi/hi_tee_hdmi.c \
	$(DEVCHIP_TEE_C)/api/hdmi/hi_tee_drv_hdmi.c \
	$(DEVCHIP_TEE_C)/api/monitor/hi_tee_monitor.c \
	$(DEVCHIP_TEE_C)/api/display/hi_tee_display.c
endif

#########################################################################
# dispctrl
#########################################################################
ifeq ($(CFG_HI_TEE_DISPCTRL_SUPPORT), y)
DEVCHIP_TEE_SRCS += $(DEVCHIP_TEE_C)/api/dispctrl/hi_tee_dispctrl.c
endif

#########################################################################
# dmx
#########################################################################
ifeq ($(CFG_HI_TEE_DEMUX_SUPPORT), y)
DEVCHIP_TEE_SRCS += \
	$(DEVCHIP_TEE_C)/api/demux/tee_descrambler.c \
	$(DEVCHIP_TEE_C)/api/demux/tee_demux_utils.c
endif

#########################################################################
# plcipher
#########################################################################
ifeq ($(CFG_HI_TEE_PLCIPHER_SUPPORT), y)
DEVCHIP_TEE_SRCS += \
	$(DEVCHIP_TEE_C)/api/plcipher/tee_plcipher.c \
	$(DEVCHIP_TEE_C)/api/demux/tee_plcipher_utils.c
endif

#########################################################################
# otp
#########################################################################
ifeq ($(CFG_HI_TEE_OTP_SUPPORT), y)
DEVCHIP_TEE_SRCS += $(DEVCHIP_TEE_C)/api/otp/hi_tee_otp.c
endif

#########################################################################
# klad
#########################################################################
ifeq ($(CFG_HI_TEE_KLAD_SUPPORT), y)
DEVCHIP_TEE_SRCS += $(DEVCHIP_TEE_C)/api/keyladder/tee_keyladder.c
ifeq ($(CFG_HI_ADVCA_TYPE), VERIMATRIX_ULTRA)
DEVCHIP_TEE_SRCS += $(DEVCHIP_TEE_C)/api/keyladder/tee_keyladder_verimatrix.c
endif
ifeq ($(CFG_HI_ADVCA_TYPE), DCAS)
DEVCHIP_TEE_SRCS += $(DEVCHIP_TEE_C)/api/keyladder/tee_keyladder_dcas.c
endif
ifeq ($(CFG_HI_ADVCA_TYPE), SUMA)
DEVCHIP_TEE_SRCS += $(DEVCHIP_TEE_C)/api/keyladder/tee_keyladder_suma.c
endif
endif

#########################################################################
# dcas
#########################################################################
ifeq ($(CFG_HI_TEE_DCAS_SUPPORT), y)
DEVCHIP_TEE_SRCS += $(DEVCHIP_TEE_C)/api/klad/hi_tee_klad.c
endif

#########################################################################
# avplay
#########################################################################
ifeq ($(strip $(CFG_HI_TEE_AVPLAY_SUPPORT)), y)
DEVCHIP_TEE_INS += -I$(DEVCHIP_TEE_C)/api/avplay
endif

#########################################################################
# netflix
#########################################################################
ifeq ($(strip $(CFG_HI_TEE_NETFLIX_SUPPORT)), y)
DEVCHIP_TEE_INS += -I$(DEVCHIP_TEE_C)/api/netflix
endif

INCLUDE += $(DEVCHIP_TEE_INS)
LIB_SRCS += $(DEVCHIP_TEE_SRCS)
