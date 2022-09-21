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
LOCAL_OUT := $(OUT)/drv/klad
else
LOCAL_OUT := $(shell pwd)
endif

LIBS    := libsec_$(notdir $(LOCAL_OUT)).a

KLAD_VERSION :=v200
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716dv100 hi3716mv410 hi3716mv420 hi3796mv100 hi3798cv200 hi3798mv100 hi3798mv200 hi3798mv300),)
    CFLAGS += -DHI_KLAD_VERSION_100
    KLAD_VERSION :=v100
else
    CFLAGS += -DHI_KLAD_VERSION_200
    KLAD_VERSION :=v200
endif

OBJS    := \
				drv_klad_intf.o \
				basic/$(KLAD_VERSION)/hal_klad_basic.o \
				basic/$(KLAD_VERSION)/hal_klad.o \
				basic/drv_klad_basic.o \
				framework/drv_klad.o
				
ifeq ($(CFG_HI_ADVCA_TYPE),VERIMATRIX_ADVANCE)
CFLAGS += -DHI_KLAD_VERIMATRIX_ADVANCE
endif
ifeq ($(CFG_HI_ADVCA_TYPE),VERIMATRIX_ULTRA)
OBJS   += \
                verimatrix/$(KLAD_VERSION)/hal_klad_verimatrix.o \
                verimatrix/drv_klad_verimatrix.o

CFLAGS += -I$(HI_TEE_DRV_DIR)/klad/verimatrix/include
CFLAGS += -DHI_KLAD_VERIMATRIX_ULTRA
endif

ifeq ($(CFG_HI_ADVCA_TYPE),DCAS)
OBJS   += \
                dcas/$(KLAD_VERSION)/hal_klad_dcas.o \
                dcas/drv_klad_dcas.o

CFLAGS += -I$(HI_TEE_DRV_DIR)/klad/dcas/include
CFLAGS += -DHI_KLAD_DCAS
endif

ifeq ($(CFG_HI_ADVCA_TYPE),IRDETO)
OBJS   += \
                irdeto/$(KLAD_VERSION)/hal_klad_irdeto.o \
                irdeto/drv_klad_irdeto.o

CFLAGS += -I$(HI_TEE_DRV_DIR)/klad/irdeto/include
CFLAGS += -DHI_KLAD_IRDETO
endif

ifeq ($(CFG_HI_ADVCA_TYPE),NAGRA)
OBJS   += \
                nagra/$(KLAD_VERSION)/hal_klad_nagra.o \
                nagra/drv_klad_nagra.o \
				nagra/cert/tee_drv_cert.o \
				nagra/cert/tee_drv_cert_intf.o \
				nagra/cert/tee_hal_cert.o

CFLAGS += -I$(HI_TEE_DRV_DIR)/klad/nagra/include
CFLAGS += -I$(HI_TEE_DRV_DIR)/klad/nagra/cert
CFLAGS += -I$(HI_TEE_DRV_DIR)/klad/nagra/$(KLAD_VERSION)
CFLAGS += -DHI_KLAD_NAGRA
CFLAGS += -DHI_KLAD_CERT
endif

#ifeq ($(CFG_HI_ADVCA_TYPE),OTHER)
OBJS   += \
                common_ca/$(KLAD_VERSION)/hal_klad_common_ca.o \
                common_ca/drv_klad_common_ca.o

CFLAGS += -I$(HI_TEE_DRV_DIR)/klad/common_ca/include
#endif

ifeq ($(CFG_HI_ADVCA_TYPE),SUMA)
OBJS   += \
                suma/$(KLAD_VERSION)/hal_klad_suma.o \
                suma/drv_klad_suma.o

CFLAGS += -I$(HI_TEE_DRV_DIR)/klad/suma/include
CFLAGS += -DHI_KLAD_SUMA
endif

CFLAGS += -I$(HI_TEE_DRV_DIR)/klad/include
CFLAGS += -I$(HI_TEE_DRV_DIR)/klad/basic/include
CFLAGS += -I$(HI_TEE_DRV_DIR)/klad/framework
CFLAGS += -I$(HI_TEE_DRV_DIR)/klad/basic/$(KLAD_VERSION)
CFLAGS += -I$(HI_TEE_DRV_DIR)/include
CFLAGS += -I$(HI_TEE_DRV_DIR)/demux
CFLAGS += -I$(HI_TEE_API_DIR)/demux
CFLAGS += -I$(TRUSTEDCORE_DIR)/platform/devchip/$(PLATFORM_DIR_NAME)/pm
CFLAGS += -I$(TRUSTEDCORE_DIR)/platform/devchip/$(PLATFORM_DIR_NAME)/include
CFLAGS += -I$(TRUSTEDCORE_DIR)/include/TEE/libhwsecurec
CFLAGS += -I$(TRUSTEDCORE_DIR)/include/kernel

ALL_OUT_OBJ = $(foreach VAR,$(OBJS),$(addprefix $(LOCAL_OUT)/,$(VAR)))
ALL_OUT_LIBS = $(foreach VAR,$(LIBS),$(addprefix $(LOCAL_OUT)/,$(VAR)))

#===============================================================================
# rules
#===============================================================================
include $(HI_TEE_DRV_DIR)/stb_drv.mak
