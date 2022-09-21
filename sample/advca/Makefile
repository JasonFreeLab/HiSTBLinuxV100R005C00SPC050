#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

include $(SAMPLE_DIR)/base.mak

#===============================================================================
# local variable
#===============================================================================
SAMPLE_IMAGES := \
	sample_ca_crypto  \
	sample_ca_tsplay \
	sample_ca_set_otp_fuse \
	sample_ca_get_otp_fuse \
	sample_ca_blpk \
	sample_ca_writeRSAkey

    
ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
SAMPLE_IMAGES += sample_ca_dvbplay
endif

ifeq ($(CFG_HI_ADVCA_TYPE),CONAX)
ifeq ($(CFG_HI_PVR_SUPPORT),y)
ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
SAMPLE_IMAGES += sample_ca_pvr_rec \
    sample_ca_pvr_play \
    sample_ca_pvr_timeshift
endif
endif
SAMPLE_IMAGES += \
    product/sample_product_crypto \
    product/sample_product_encrypt_boot \
    product/sample_product_burn_partition \
    product/sample_product_pv_stb \
    product/sample_product_add_cmac
endif

ifeq ($(CFG_HI_ADVCA_TYPE),CONAX)
ifeq ($(CFG_HI_PVR_SUPPORT),y)
LOCAL_OBJS := sample_ca_adp_pvr.o
endif
endif

COMMON_OBJS := $(filter-out hi_adp_pvr.o,$(COMMON_SRCS:%.c=%.o))

LOCAL_OBJS += parse_config_file.o

DEPEND_LIBS := $(HI_LIBS)

include $(SAMPLE_DIR)/hi_sample_rules.mak
