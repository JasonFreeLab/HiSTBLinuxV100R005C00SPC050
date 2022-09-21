#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

include $(SAMPLE_DIR)/base.mak

ifeq ($(CFG_HI_HDMI_SUPPORT_2_0),y)
CFLAGS += -DHI_HDMI_SUPPORT_2_0
endif


#===============================================================================
# local variable
#===============================================================================
SAMPLE_IMAGES := sample_hdmi_tsplay

LOCAL_OBJS := hdmi_test_cmd.o \
              hdmi_test_cec.o

COMMON_OBJS := $(COMMON_SRCS:%.c=%.o)

DEPEND_LIBS := $(HI_LIBS)

include $(SAMPLE_DIR)/hi_sample_rules.mak
