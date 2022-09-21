#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

#===============================================================================
# local variables
#===============================================================================
ifneq ($(OUT),)
LOCAL_OUT := $(OUT)/drv/vdp
else
LOCAL_OUT := $(shell pwd)
endif

ifneq ($(findstring $(HI_CHIP_TYPE),hi3798mv200  hi3798mv300),)
VDP_PRODUCT := 98mv200
endif

ifneq ($(findstring $(HI_CHIP_TYPE),hi3798cv200),)
VDP_PRODUCT := 98cv200
endif

ifneq ($(findstring $(HI_CHIP_TYPE),hi3796mv200),)
VDP_PRODUCT := 96mv200
endif



LIBS    := libsec_$(notdir $(LOCAL_OUT)).a
OBJS    :=  \
				drv_vdp_intf.o \
				tee_drv_vdp.o \
				drv/drv_verimatrix.o \
				drv/drv_watermark_common.o \
				drv/drv_analog_ctrl.o \
				drv/drv_cgms.o \
				drv/drv_mcvn.o \
				hal/$(VDP_PRODUCT)/vdp_hal_comm.o \
				hal/$(VDP_PRODUCT)/vdp_software_selfdefine.o\
				hal/$(VDP_PRODUCT)/vdp_hal_ip_vmx.o \
				hal/$(VDP_PRODUCT)/vdp_hal_ip_vmx_fromother.o
				
#ifeq ($(strip $(CFG_HI_TEE_VDP_ANALOGOUTPUT_CTRL_SUPPORT)), y)
OBJS    +=  tee_drv_vdp.o  
#endif

ifeq ($(strip $(CFG_HI_TEE_VDP_NEXTGUARD_SUPPORT)), y)
OBJS    +=  drv/drv_nexguard.o  hal/$(VDP_PRODUCT)/vdp_hal_ip_nxg.o
CFLAGS += -DHI_TEE_VDP_VWM_NEXTGUARD
endif

ifeq ($(strip $(CFG_HI_TEE_VDP_VERIMATRIX_SUPPORT)), y)
OBJS    += drv/drv_verimatrix.o hal/$(VDP_PRODUCT)/vdp_hal_ip_vmx.o  hal/$(VDP_PRODUCT)/vdp_hal_ip_vmx_fromother.o 
CFLAGS += -DHI_TEE_VDP_VWM_VERIMATRIX
endif

CFLAGS += \
					-I$(HI_TEE_DRV_DIR)/vdp \
					-I$(HI_TEE_DRV_DIR)/vdp/drv \
					-I$(HI_TEE_DRV_DIR)/vdp/hal \
					-I$(HI_TEE_DRV_DIR)/vdp/hal/$(VDP_PRODUCT)\
					-I$(HI_TEE_DRV_DIR)/vdp/hal/$(VDP_PRODUCT)/inc\
					-I$(HI_TEE_DRV_DIR)/timer\
					-I$(HI_TEE_DRV_DIR)/include \
					-I$(HI_TEE_DRV_DIR)/../api/include \
					-I$(TRUSTEDCORE_DIR)/platform/devchip/$(PLATFORM_DIR_NAME)/include

ALL_OUT_OBJ = $(foreach VAR,$(OBJS),$(addprefix $(LOCAL_OUT)/,$(VAR)))
ALL_OUT_LIBS = $(foreach VAR,$(LIBS),$(addprefix $(LOCAL_OUT)/,$(VAR)))

#===============================================================================
# rules
#===============================================================================
include $(HI_TEE_DRV_DIR)/stb_drv.mak
