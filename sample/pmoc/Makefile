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
ifeq ($(CFG_HI_KEYLED_SUPPORT),y)
CFLGAS := -DHI_KEYLED_SUPPORT
endif

SAMPLE_IMAGES := sample_pmoc \
    sample_smart_pmoc

DEPEND_LIBS := $(HI_LIBS)

include $(SAMPLE_DIR)/hi_sample_rules.mak
