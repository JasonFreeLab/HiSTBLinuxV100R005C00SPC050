#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

include $(SAMPLE_DIR)/base.mak

#===============================================================================
# sample rawplay
#===============================================================================
SAMPLE_IMAGES := sample_rawplay

COMMON_OBJS := $(COMMON_SRCS:%.c=%.o)

DEPEND_LIBS := $(HI_LIBS)

ifeq ($(CFG_HI_TEE_SUPPORT),y)
CFLAGS := -DHI_TEE_SUPPORT
CFLAGS += -I$(TEE_API_INCLUDE) -I$(SAMPLE_DIR)/../source/common/api/include
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716dv100 hi3796mv100 hi3798mv100),)
CFLAGS += -I$(HI_TEE_OS_DIR)/libteec/sec_mmz/inc
endif
DEPEND_LIBS += -lteec
endif

ifeq ($(CFG_HI_SMMU_SUPPORT),y)
CFLAGS += -DHI_SMMU_SUPPORT
endif

include $(SAMPLE_DIR)/hi_sample_rules.mak
