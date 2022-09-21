#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

include $(SAMPLE_DIR)/base.mak

#===============================================================================
# local variable
#===============================================================================
CFLAGS  +=  $(CFG_HI_CFLAGS)
CFLAGS  +=  $(CFG_HI_BOARD_CONFIGS)

CFLAGS  +=  -I$(SAMPLE_DIR)/test/ddr_test/base

ifeq ($(CFG_HI_GPU_SUPPORT),y)
CFLAGS  +=  -I$(SAMPLE_DIR)/test/ddr_test/base/common/inc \
			-I$(SAMPLE_DIR)/test/ddr_test/base/common/egl/inc \
			-I$(SAMPLE_DIR)/test/ddr_test/base/common/key/inc \
			-I$(SAMPLE_DIR)/test/ddr_test/base/common/texture/inc

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798cv200),)
HI_LIBS += -lmali
else
HI_LIBS += -lMali
endif

CFLAGS += -DHI_GPU_SUPPORT
ifeq ($(CFG_EGL_FB), y)
CFLAGS += -DHI3D_DEBUG -DLINUX -DEGL_API_FB -DEGL_FBDEV
endif

endif


SAMPLE_IMAGES := sample_ddr_test
COMMON_OBJS := $(COMMON_SRCS:%.c=%.o)

COMMON_OBJS += ../test/ddr_test/base/hi_play.o \
			   ../test/ddr_test/base/hi_osd.o \
			   ../test/ddr_test/base/hi_demux.o \
			   ../test/ddr_test/base/hi_psi_si.o



ifeq ($(CFG_HI_VENC_SUPPORT),y)
COMMON_OBJS  += ../test/ddr_test/base/hi_transcode.o
endif

ifeq ($(CFG_HI_GPU_SUPPORT),y)
COMMON_OBJS  += ../test/ddr_test/base/commonMath.o \
				../test/ddr_test/base/common.o \
				../test/ddr_test/base/hi_gpu.o \
				../test/ddr_test/base/common/egl/src/hi_egl.o          \
				../test/ddr_test/base/common/egl/src/egl_native.o      \
				../test/ddr_test/base/common/texture/src/hi_texture.o  \
				../test/ddr_test/base/common/key/src/hi_engine_key.o   \
				../test/ddr_test/base/common/key/src/hi_input_dfb.o    \
				../test/ddr_test/base/common/key/src/hi_ir_remote.o
endif
				
DEPEND_LIBS := $(HI_LIBS)
include $(SAMPLE_DIR)/hi_sample_rules.mak

