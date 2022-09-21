#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

#===============================================================================
# local variable
#===============================================================================

#PROV_COMPILELIB_USER_CFLAGS = -march=armv7-a -mcpu=cortex-a9 -mfloat-abi=softfp -mfpu=vfpv3-d16
WIDEVINE_SAMPLE_OUTPUT_BIN_DIR := $(HI_OUT_DIR)/obj/sample/widevine/sample

WIDEVINE_GOOGLE_TEST_INCLUDE     := $(CURDIR)/../GoogleTest/include
WIDEVINE_OPENSSL_INC_DIR      	 := $(HI_OUT_DIR)/include
WIDEVINE_TEE_CLIENT_INC_DIR		 := $(SDK_DIR)/source/tee/core/trustedcore/libteec/inc
WIDEVINE_MSP_INC_DIR			 := $(SDK_DIR)/source/msp/include
WIDEVINE_HA_CODEC_INC_DIR		 := $(SDK_DIR)/source/component/ha_codec/include
WIDEVINE_SAMPLE_COM_DIR			 := $(SDK_DIR)/sample/common
WIDEVINE_OEMCRYPTO_DIR			 := $(SDK_DIR)/source/component/drm/widevine/oemcrypto/hisi_teec
WIDEVINE_RELEASE_INCLUDE_DIR	 := $(SDK_DIR)/source/component/drm/widevine/include

#===============================================================================
# libhisample_common.so
#===============================================================================

SAMPLE_COMMON_OBJ_DIR = $(HI_OUT_DIR)/obj/sample/common
SAMPLE_COMMON_OBJS = $(SAMPLE_COMMON_OBJ_DIR)/hi_adp_demux.o \
                     $(SAMPLE_COMMON_OBJ_DIR)/hi_adp_tuner.o \
                     $(SAMPLE_COMMON_OBJ_DIR)/hi_adp_data.o \
                     $(SAMPLE_COMMON_OBJ_DIR)/hi_adp_hdmi.o \
                     $(SAMPLE_COMMON_OBJ_DIR)/hi_adp_mpi.o \
                     $(SAMPLE_COMMON_OBJ_DIR)/hi_adp_search.o \
                     $(SAMPLE_COMMON_OBJ_DIR)/hi_filter.o

SAMPLE_COMMON_CC := $(CFG_HI_ARM_TOOLCHAINS_NAME)-gcc
SAMPLE_COMMON_LIB_S := $(SAMPLE_COMMON_OBJ_DIR)/libhisample_common.so

#===============================================================================
# sample_tvp_play
#===============================================================================
#CFG_HI_ARM_TOOLCHAINS_NAME := arm-histbv310-linux
TVP_SAMPLE_CC := $(CFG_HI_ARM_TOOLCHAINS_NAME)-g++
TVP_SAMPLE_AR := $(CFG_HI_ARM_TOOLCHAINS_NAME)-ar

CFG_INC := -I$(SDK_DIR)/source/common/include/ \
		-I$(WIDEVINE_MSP_INC_DIR) \
		-I$(WIDEVINE_SAMPLE_COM_DIR) \
		-I$(WIDEVINE_GOOGLE_TEST_INCLUDE) \
		-I$(WIDEVINE_OPENSSL_INC_DIR) \
		-I$(WIDEVINE_HA_CODEC_INC_DIR) \
		-I$(WIDEVINE_OEMCRYPTO_DIR) \
		-I$(WIDEVINE_RELEASE_INCLUDE_DIR) \
		-I$(CURDIR)/../GoogleTest/third_party/gmock/gtest/include \
		-I$(CURDIR)/../GoogleTest/third_party/gmock/include
		
SAMPLE_TVP_PLAY_SRC := sample_tvp_play.cpp av_play.cpp file_parser.cpp widevine_process.cpp url_request.cpp license_request.cpp http_socket.cpp test_host.cpp device_cert.cpp

SDK_SHARE_LIB_DIR = $(HI_OUT_DIR)/lib/share
LIBPATH := -L$(SDK_SHARE_LIB_DIR)
LIBPATH += -L$(SDK_DIR)/source/component/openssl/release/lib
LIBPATH += -L$(HI_OUT_DIR)/obj/source/rootfs/protobuf/lib

LIB := -Wl,--start-group -lpthread -lrt -lssl -lcrypto -lprotobuf -lm -Wl,--end-group
LIB += -lhi_widevineCdm -lhi_widevine_tee
LIB += -lhi_msp -lhi_common -lteec -ljpeg -lhisample_common

EXTRA_FLAGS := -std=c++11
#EXTRA_FLAGS += -DSET_ENCPRYT_KEYBOX
	
.PHONY: all clean mksamplecommon_lib sample_tvp_play sample_tvp_play_nand
all: mksamplecommon_lib sample_tvp_play sample_tvp_play_nand

mksamplecommon_lib: $(SAMPLE_COMMON_OBJS)
	@echo "Enter mksamplecommon_lib..."
	@echo SAMPLE_COMMON_LIB_S = $(SAMPLE_COMMON_LIB_S)
	@rm -f $(SAMPLE_COMMON_LIB_S)
	@echo "create libhi_samplecommon.so"
	@$(SAMPLE_COMMON_CC) -shared -o $(SAMPLE_COMMON_LIB_S)  $(SAMPLE_COMMON_OBJS)
	cp -f $(SAMPLE_COMMON_LIB_S) $(HI_SHARED_LIB_DIR)

sample_tvp_play: $(SAMPLE_TVP_PLAY_SRC)
	@$(TVP_SAMPLE_CC) -o $@ $^  $(CFG_INC) $(LIBPATH) $(LIB) $(EXTRA_FLAGS)
	@echo "LIBPATH=$(LIBPATH)"
	@echo "LIB=$(LIB)"
	$(AT)test -d $(WIDEVINE_SAMPLE_OUTPUT_BIN_DIR) || mkdir -p $(WIDEVINE_SAMPLE_OUTPUT_BIN_DIR)
	@cp $(SDK_DIR)/sample/widevine/sample/sample_tvp_play $(WIDEVINE_SAMPLE_OUTPUT_BIN_DIR)

clean:
	@rm -rf sample_tvp_play
	@rm -rf $(WIDEVINE_SAMPLE_OUTPUT_BIN_DIR)
