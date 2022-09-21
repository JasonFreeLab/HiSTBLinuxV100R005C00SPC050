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
		sample_cipher \
		sample_rng \
		sample_multicipher \
		sample_hash \
		sample_cbcmac \
		sample_anticopy \
		sample_rsa_enc \
		sample_rsa_sign \
		sample_dh \
		sample_ecdh \
		sample_ecdsa \
		sample_sm2


DEPEND_LIBS := $(HI_LIBS)

include $(SAMPLE_DIR)/hi_sample_rules.mak
