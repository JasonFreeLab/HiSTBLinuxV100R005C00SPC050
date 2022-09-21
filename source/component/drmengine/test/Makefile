ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

ifeq ($(COMPILELIB_TOOLCHAINS_NAME),gcc-3.4.3-vfp)
    DRM_ENGINE_COMPILELIB_CROSS:=arm-vfp_uclibc-linux-gnu
    DRM_ENGINE_COMPILELIB_USER_CFLAGS = -march=armv5te -mtune=arm926ej-s
endif

ifeq ($(COMPILELIB_TOOLCHAINS_NAME),gcc-3.4.3-soft)
    DRM_ENGINE_COMPILELIB_CROSS:=arm-hismall-linux
    DRM_ENGINE_COMPILELIB_USER_CFLAGS = -march=armv5te -mtune=arm926ej-s
endif

DRM_ENGINE_COMPILELIB_CROSS:=$(CFG_HI_TOOLCHAINS_NAME)

ifndef COMPILELIB_TOOLCHAINS_NAME
$(error please back to top dir to make)
endif

DRM_ENGINE_CC := $(DRM_ENGINE_COMPILELIB_CROSS)-g++
DRM_ENGINE_AR := $(DRM_ENGINE_COMPILELIB_CROSS)-ar

DRM_ENGINE_TEST_SOURCE_DIR	:= $(DRM_ENGINE_SOURCE_DIR)/test

DRM_ENGINE_INC_DIR      := $(DRM_ENGINE_SOURCE_DIR)/include
DRM_HI_COMMON_INC_DIR      := $(SDK_DIR)/source/common/include
DRM_HI_CURL_INC_DIR			:= $(HI_INCLUDE_DIR)/curl
DRM_HI_GMOCK_INC_DIR		:= $(SDK_DIR)/source/rootfs/gmock/include
DRM_HI_GMOCK_LIB_DIR		:= $(SDK_DIR)/source/rootfs/gmock

DRM_ENGINE_TEST_OBJ_DIR      := $(DRM_ENGINE_TEST_SOURCE_DIR)/obj_$(DRM_ENGINE_COMPILELIB_CROSS)
DRM_ENGINE_TEST_OUTPUT_DIR       := $(DRM_ENGINE_TEST_SOURCE_DIR)/$(DRM_ENGINE_COMPILELIB_CROSS)/
DRM_ENGINE_TEST_OUTPUTLIB_HEADR       := $(DRM_ENGINE_TEST_SOURCE_DIR)/$(DRM_ENGINE_COMPILELIB_CROSS)/include
DRM_ENGINE_TEST_BIN         := $(DRM_ENGINE_TEST_SOURCE_DIR)/$(DRM_ENGINE_COMPILELIB_CROSS)/drm_engine_test

#### open debug
#CFG_DEBUG = -g
###############################include *h##########################################
CFG_INC = -I$(DRM_HI_GMOCK_INC_DIR) \
		  -I$(DRM_HI_COMMON_INC_DIR)

VPATH := $(DRM_ENGINE_TEST_SOURCE_DIR)

EXTRA_CFLAGS :=
EXTRA_CFLAGS += -DCHIP_TYPE_$(CFG_HI_CHIP_TYPE) -DBOARD_TYPE_$(CFG_BOARD_TYPE) -DSDK_VERSION=$(CFG_SDK_VERSION)
EXTRA_CFLAGS += $(C_DEFINES)
EXTRA_CFLAGS += -c -O2 -Wall $(CFG_INC) $(CFG_DEBUG) $(DRM_ENGINE_COMPILELIB_USER_CFLAGS) -fPIC -DUSE_AEC
#EXTRA_CFLAGS += -c -Wall $(CFG_INC) $(CFG_DEBUG) $(PLAYREADY_COMPILELIB_USER_CFLAGS) -fPIC -DUSE_AEC
EXTRA_CFLAGS += -D_GNU_SOURCE -D_XOPEN_SOURCE=600
EXTRA_CFLAGS += -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64

#add by swx340119
EXTRA_CFLAGS += -DDRM_LINUX

LDFLAGS += -L$(SHARED_LIB_DIR)
LDFLAGS += -L$(STATIC_LIB_DIR)
LDFLAGS += -L$(DRM_HI_GMOCK_LIB_DIR)
LDFLAGS += -lgmock -lgtest -lpthread -ldl -lhi_drm_engine -lcurl

HI_DRM_ENGINE_TEST_SRC := ./drm_engine_test_main.cpp \
						  ./drm_engine_test.cpp \
						  ./WVLog.cpp \
						  ./string_conversions.cpp

OEM_CDM_DRM_ENGINE_TEST_OBJS := $(HI_DRM_ENGINE_TEST_SRC:%.cpp=$(DRM_ENGINE_TEST_OBJ_DIR)/%.o)

$(DRM_ENGINE_TEST_OBJ_DIR)/%.o : %.cpp
	@$(DRM_ENGINE_CC) $(EXTRA_CFLAGS) $(LDFLAGS) -o "$(DRM_ENGINE_TEST_OBJ_DIR)/$(*F).o" "$<"

.PHONY: all
all: BUILD_PUBLIC_OBJ_DIR  mkhi_drm_engine_test public_clean

#********************* Create out dir ***********************
BUILD_PUBLIC_OBJ_DIR:
	@[ -e $(DRM_ENGINE_TEST_OBJ_DIR) ] || mkdir $(DRM_ENGINE_TEST_OBJ_DIR)
	@echo $(HI_DRM_ENGINE_TEST_SRC)

LIB_OBJS=$(shell ls $(DRM_ENGINE_TEST_OBJ_DIR)/*.o)

mkhi_drm_engine_test: BUILD_PUBLIC_OBJ_DIR $(OEM_CDM_DRM_ENGINE_TEST_OBJS)
	@rm -f $(DRM_ENGINE_TEST_BIN)
	
	@mkdir -p $(DRM_ENGINE_TEST_OUTPUT_DIR)
	@echo "wmftest $(DRM_ENGINE_COMPILELIB_CROSS)"	
	@echo "create hi_drm_engine_test output bin"
	@$(DRM_ENGINE_CC) -o $(DRM_ENGINE_TEST_BIN) $(LIB_OBJS) $(LDFLAGS)
	@echo "Leave build hi_drm_engine_test..."

public_clean:
	@rm -rf $(DRM_ENGINE_TEST_OBJ_DIR)
	@rm -rf $(DRM_ENGINE_TEST_OUTPUT_DIR)
	@rm -f $(DRM_ENGINE_TEST_BIN)
