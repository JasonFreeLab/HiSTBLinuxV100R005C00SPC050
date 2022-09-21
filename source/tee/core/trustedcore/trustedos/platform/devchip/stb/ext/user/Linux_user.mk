#########################################################################
## NOTE: This file is included in trustedcore/TEE_ext/Android.mk
#########################################################################

DEVCHIP_TEE_C := $(HI_TEE_API_DIR)/..
DEVCHIP_TEE_H := $(HI_TEE_API_DIR)/..

DEVCHIP_TEE_INS := \
	-I../platform/devchip/$(PLATFORM_DIR_NAME)/ext/user \
	-I../platform/devchip/$(PLATFORM_DIR_NAME)/ext/user/asm_mem \
	-I../platform/devchip/$(PLATFORM_DIR_NAME)/ext/kernel \
	-I$(DEVCHIP_TEE_H)/api/mem/include \
	-I$(DEVCHIP_TEE_H)/api/include \
	-I$(DEVCHIP_TEE_H)/drv/include \
	-I$(COMPONENT_DIR)/harness/nocs3.1/RPCServer/inc \
	-I$(COMPONENT_DIR)/harness/nocs3.1/RPCServer/EAPI/inc

DEVCHIP_TEE_SRCS := \
	../platform/devchip/$(PLATFORM_DIR_NAME)/ext/user/sre_syscalls_chip.o \
	../platform/devchip/$(PLATFORM_DIR_NAME)/ext/user/tee_ta_load.o \
	../platform/devchip/$(PLATFORM_DIR_NAME)/ext/user/tee_config_chip.o

#########################################################################
## asm_memmove
#########################################################################
DEVCHIP_ASM_MEM_SRCS := \
	../platform/devchip/$(PLATFORM_DIR_NAME)/ext/user/tee_external_api.o \
	../platform/devchip/$(PLATFORM_DIR_NAME)/ext/user/asm_mem/memcpy.o \
	../platform/devchip/$(PLATFORM_DIR_NAME)/ext/user/asm_mem/memmove.o

DEVCHIP_TEE_SRCS += $(DEVCHIP_ASM_MEM_SRCS)


#########################################################################
#########################################################################
#########################################################################
# vdp
#########################################################################
ifeq ($(CFG_HI_TEE_VDP_SUPPORT), y)
DEVCHIP_TEE_INS += -I$(DEVCHIP_TEE_H)/drv/vdp
endif
# hdmi
#########################################################################
ifeq ($(CFG_HI_TEE_HDMI_SUPPORT), y)
DEVCHIP_TEE_INS += -I$(DEVCHIP_TEE_H)/api/hdmi
endif
#########################################################################
# dmx
#########################################################################
ifeq ($(CFG_HI_TEE_DEMUX_SUPPORT), y)
DEVCHIP_TEE_INS += -I$(DEVCHIP_TEE_H)/api/demux
endif

#########################################################################
# plcipher
#########################################################################
ifeq ($(CFG_HI_TEE_PLCIPHER_SUPPORT), y)
DEVCHIP_TEE_INS += -I$(DEVCHIP_TEE_H)/api/plcipher
endif

#########################################################################
# cryptoen
#########################################################################
ifeq ($(CFG_HI_TEE_CRYPTOEN_SUPPORT), y)
DEVCHIP_TEE_INS += -I$(DEVCHIP_TEE_H)/api/nocs
endif
#########################################################################
# otp
#########################################################################
ifeq ($(CFG_HI_TEE_OTP_SUPPORT), y)
DEVCHIP_TEE_INS += -I$(DEVCHIP_TEE_H)/api/otp/include
endif
#########################################################################
# pvr
#########################################################################
ifeq ($(CFG_HI_TEE_PVR_SUPPORT), y)
DEVCHIP_TEE_INS += -I$(DEVCHIP_TEE_C)/api/pvr
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
