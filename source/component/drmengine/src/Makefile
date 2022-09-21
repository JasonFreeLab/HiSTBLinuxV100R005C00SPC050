ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

ifeq ($(HI_USER_SPACE_LIB),y)
CFG_HI_TOOLCHAINS_NAME := $(CFG_HI_ARM_TOOLCHAINS_NAME)
DST_SHARED_LIB_DIR := $(HI_SHARED_LIB_DIR)
DST_STATIC_LIB_DIR := $(HI_STATIC_LIB_DIR)
endif

ifeq ($(HI_USER_SPACE_LIB64),y)
CFG_HI_TOOLCHAINS_NAME := $(CFG_HI_AARCH64_TOOLCHAINS_NAME)
DST_SHARED_LIB_DIR := $(HI_SHARED_LIB64_DIR)
DST_STATIC_LIB_DIR := $(HI_STATIC_LIB64_DIR)
endif

DRM_ENGINE_COMPILELIB_CROSS:=$(CFG_HI_TOOLCHAINS_NAME)
DRM_ENGINE_CC := $(DRM_ENGINE_COMPILELIB_CROSS)-g++
DRM_ENGINE_AR := $(DRM_ENGINE_COMPILELIB_CROSS)-ar

DRMENGINE_DIR=$(SDK_DIR)/source/component/drmengine

DRM_ENGINE_SOURCE_DIR   := $(SDK_DIR)/source/component/drmengine/src

DRM_ENGINE_INC_DIR         := $(DRMENGINE_DIR)/include
DRM_HI_COMMON_INC_DIR      := $(SDK_DIR)/source/common/include
DRM_HI_CURL_INC_DIR        := $(HI_INCLUDE_DIR)/curl

DRM_ENGINE_OBJ_DIR      := $(DRM_ENGINE_SOURCE_DIR)/obj_$(DRM_ENGINE_COMPILELIB_CROSS)
DRM_ENGINE_OUTPUTLIB_DIR       := $(DRM_ENGINE_SOURCE_DIR)/$(DRM_ENGINE_COMPILELIB_CROSS)/
DRM_ENGINE_OUTPUTLIB_HEADR       := $(DRM_ENGINE_SOURCE_DIR)/$(DRM_ENGINE_COMPILELIB_CROSS)/include
DRM_ENGINE_OUTPUTLIB_S         := $(DRM_ENGINE_SOURCE_DIR)/$(DRM_ENGINE_COMPILELIB_CROSS)/libhi_drm_engine.so

#### open debug
###############################include *h##########################################
CFG_INC = -I$(DRM_ENGINE_INC_DIR) \
          -I$(DRMENGINE_DIR) \
		  -I$(DRM_HI_COMMON_INC_DIR) \
		  -I$(DRM_HI_CURL_INC_DIR) \
		  -I$(DRMENGINE_DIR)/base/include

VPATH := $(DRM_ENGINE_SOURCE_DIR)

EXTRA_CFLAGS :=
EXTRA_CFLAGS += -DCHIP_TYPE_$(CFG_HI_CHIP_TYPE) -DBOARD_TYPE_$(CFG_BOARD_TYPE) -DSDK_VERSION=$(CFG_SDK_VERSION)
EXTRA_CFLAGS += $(C_DEFINES)
EXTRA_CFLAGS += -c -O2 -Wall $(CFG_INC) -fPIC

EXTRA_CFLAGS += -DDRM_LINUX

HI_DRM_ENGINE_SRC :=	./drm_engine.cpp \
			./drm_engine_adapter.cpp \
			./drm_engine_classic_adapter.cpp \
			./drm_engine_modular_android_adapter.cpp \
			./SharedLibrary.cpp \
			./WVLog.cpp

ifeq ($(HI_USER_SPACE_LIB),y)
HI_DRM_ENGINE_SRC +=	./drm_engine_modular_linux_adapter.cpp \
			./drm_widevine_http.cpp \
			./hi_playreadyhttp.c \
			./drm_engine_interface.c
			
endif

ifeq ($(HI_USER_SPACE_LIB64),y)
HI_DRM_ENGINE_SRC +=	./drm_engine_modular_linux_adapter_64.cpp \
			./drm_engine_interface_64.c
endif

LIBPATH += -L$(DST_SHARED_LIB_DIR) -L$(DST_STATIC_LIB_DIR)
LIB := -Wl,-dn -lcurl -Wl,-dy
LIB += -lutils -lcutils -llog -landroid

OEM_CDM_DRM_ENGINE_OBJS := $(HI_DRM_ENGINE_SRC:%.cpp=$(DRM_ENGINE_OBJ_DIR)/%.o)
OEM_CDM_DRM_ENGINE_OBJS += $(HI_DRM_ENGINE_SRC:%.c=$(DRM_ENGINE_OBJ_DIR)/%.o)

$(DRM_ENGINE_OBJ_DIR)/%.o : %.c*
	@$(DRM_ENGINE_CC) $(EXTRA_CFLAGS) -o "$(DRM_ENGINE_OBJ_DIR)/$(*F).o" "$<"

.PHONY: all
all: BUILD_PUBLIC_OBJ_DIR  mkhi_drm_engine clean

#********************* Create out dir ***********************
BUILD_PUBLIC_OBJ_DIR:
	@[ -e $(DRM_ENGINE_OBJ_DIR) ] || mkdir $(DRM_ENGINE_OBJ_DIR)
	@echo $(HI_DRM_ENGINE_SRC)

LIB_OBJS=$(shell ls $(DRM_ENGINE_OBJ_DIR)/*.o)

BUILD_PREPARE:
	@echo "build curl"
	make -C $(SDK_DIR)/source/component/curl

mkhi_drm_engine: BUILD_PUBLIC_OBJ_DIR BUILD_PREPARE $(OEM_CDM_DRM_ENGINE_OBJS)
	@echo "Enter build_public..."
	@rm -f $(DRM_ENGINE_OUTPUTLIB_S)

	@echo "create export lib dir"
	@mkdir -p $(DRM_ENGINE_OUTPUTLIB_DIR)

	@echo "create hi_drm_engine output dynamic lib"
	@$(DRM_ENGINE_CC) -shared -o $(DRM_ENGINE_OUTPUTLIB_S) $(LIB_OBJS) $(LIBPATH) $(LIB)
	@cp -f $(DRM_ENGINE_OUTPUTLIB_S) $(DST_SHARED_LIB_DIR)
	@echo "Leave build hi_drm_engine..."

clean:
	@rm -rf $(DRM_ENGINE_OBJ_DIR)
	@rm -rf $(DRM_ENGINE_OUTPUTLIB_DIR)
	@rm -f $(DRM_ENGINE_OUTPUTLIB_S)
	@rm -f $(DST_SHARED_LIB_DIR)/libhi_drm_engine*
