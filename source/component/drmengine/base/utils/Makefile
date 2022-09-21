ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

DRMENGINE_DIR=$(CURDIR)/../..

C_DEFINES+=-D_DRMENGINE_M_IX86 $(_DRM_C_DEFINES)

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

DRMENGINE_CC := $(CFG_HI_TOOLCHAINS_NAME)-g++
DRMENGINE_AR := $(CFG_HI_TOOLCHAINS_NAME)-ar

#####################################################################
#        DIRECTORIES
#####################################################################

DRMENGINE_UTIL_SOURCE_DIR        := $(DRMENGINE_DIR)/base/utils
DRMENGINE_UTIL_INC_DIR      := $(DRMENGINE_DIR)/base/include

DRMENGINE_UTIL_OBJ_DIR      := $(DRMENGINE_UTIL_SOURCE_DIR)/obj_$(CFG_HI_TOOLCHAINS_NAME)
DRMENGINE_UTIL_OUTPUTLIB_DIR       := $(DRMENGINE_UTIL_SOURCE_DIR)/$(CFG_HI_TOOLCHAINS_NAME)

DRMENGINE_UTIL_OUTPUTLIB_S         := $(DRMENGINE_UTIL_SOURCE_DIR)/$(CFG_HI_TOOLCHAINS_NAME)/libutils.so
DRMENGINE_UTIL_OUTPUTLIB_A         := $(DRMENGINE_UTIL_SOURCE_DIR)/$(CFG_HI_TOOLCHAINS_NAME)/libutils.a

###############################include *h##########################################
CFG_INC :=
CFG_INC += -I$(DRMENGINE_UTIL_INC_DIR)
CFG_INC += -I$(DRMENGINE_UTIL_INC_DIR)/arch/linux-arm

#********************* Define the objs *********************
VPATH := $(DRMENGINE_UTIL_SOURCE_DIR)

EXTRA_CFLAGS :=
EXTRA_CFLAGS += -DCHIP_TYPE_$(CFG_HI_CHIP_TYPE) -DBOARD_TYPE_$(CFG_BOARD_TYPE) -DSDK_VERSION=$(CFG_SDK_VERSION)
EXTRA_CFLAGS += $(C_DEFINES)
EXTRA_CFLAGS += -c -O2 -Wall -std=c++11 $(CFG_INC) $(CFG_DEBUG) -fPIC -DUSE_AEC
EXTRA_CFLAGS += -D_GNU_SOURCE -D_XOPEN_SOURCE=600 
EXTRA_CFLAGS += -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64

LIBPATH := -L$(DST_STATIC_LIB_DIR) -L$(DST_SHARED_LIB_DIR)

LIB :=
LIB += -lpthread

DRMENGINE_UTIL=$(notdir $(shell find $(VPATH) -maxdepth 1 -name "*.cpp"))
DRMENGINE_UTIL_OBJS := $(DRMENGINE_UTIL:%.cpp=$(DRMENGINE_UTIL_OBJ_DIR)/%.o)

$(DRMENGINE_UTIL_OBJ_DIR)/%.o : %.cpp
	@$(DRMENGINE_CC) $(EXTRA_CFLAGS) -o "$(DRMENGINE_UTIL_OBJ_DIR)/$(*F).o" "$<"

.PHONY: all mkutils_lib utils_clean
all: BUILD_DRMENGINE_UTIL_OBJ_DIR  mkutils_lib
clean: utils_clean

#********************* Create out dir ***********************
BUILD_DRMENGINE_UTIL_OBJ_DIR:
	@[ -e $(DRMENGINE_UTIL_OBJ_DIR) ] || mkdir $(DRMENGINE_UTIL_OBJ_DIR) 

LIB_OBJS = $(shell ls $(DRMENGINE_UTIL_OBJ_DIR)/*.o)

mkutils_lib: BUILD_DRMENGINE_UTIL_OBJ_DIR $(DRMENGINE_UTIL_OBJS)
	@echo "Enter build_utils..."
	@rm -f $(DRMENGINE_UTIL_OUTPUTLIB_S)
	@rm -f $(DRMENGINE_UTIL_OUTPUTLIB_A)

	@echo "create export lib dir"
	@mkdir -p $(DRMENGINE_UTIL_OUTPUTLIB_DIR)

	@echo "create utils output static lib"
	@$(DRMENGINE_AR) -rsv $(DRMENGINE_UTIL_OUTPUTLIB_A)  $(LIB_OBJS)
	@echo "create utils output dynamic lib"
	@$(DRMENGINE_CC) -shared -o $(DRMENGINE_UTIL_OUTPUTLIB_S) $(LIB_OBJS) $(LIBPATH) $(LIB)
	@echo "copy utils lib to pub"
	@cp -f $(DRMENGINE_UTIL_OUTPUTLIB_A) $(DST_STATIC_LIB_DIR)
	@cp -f $(DRMENGINE_UTIL_OUTPUTLIB_S) $(DST_SHARED_LIB_DIR)
	@echo "Leave build_utils..."

utils_clean:
	@rm -rf $(DRMENGINE_UTIL_OBJ_DIR)
	@rm -rf $(DRMENGINE_UTIL_OUTPUTLIB_DIR)
	@rm -f $(DST_STATIC_LIB_DIR)/libutils*
	@rm -f $(DST_SHARED_LIB_DIR)/libutils*
