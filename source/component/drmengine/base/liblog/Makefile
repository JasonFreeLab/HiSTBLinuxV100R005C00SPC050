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

DRMENGINE_CC := $(CFG_HI_TOOLCHAINS_NAME)-gcc
DRMENGINE_AR := $(CFG_HI_TOOLCHAINS_NAME)-ar

#####################################################################
#        DIRECTORIES
#####################################################################

DRMENGINE_LOG_SOURCE_DIR        := $(DRMENGINE_DIR)/base/liblog
DRMENGINE_LOG_INC_DIR      := $(DRMENGINE_DIR)/base/include

DRMENGINE_LOG_OBJ_DIR      := $(DRMENGINE_LOG_SOURCE_DIR)/obj_$(CFG_HI_TOOLCHAINS_NAME)
DRMENGINE_LOG_OUTPUTLIB_DIR       := $(DRMENGINE_LOG_SOURCE_DIR)/$(CFG_HI_TOOLCHAINS_NAME)

DRMENGINE_LOG_OUTPUTLIB_S         := $(DRMENGINE_LOG_SOURCE_DIR)/$(CFG_HI_TOOLCHAINS_NAME)/liblog.so
DRMENGINE_LOG_OUTPUTLIB_A         := $(DRMENGINE_LOG_SOURCE_DIR)/$(CFG_HI_TOOLCHAINS_NAME)/liblog.a

###############################include *h##########################################
CFG_INC := -I$(DRMENGINE_LOG_INC_DIR)
CFG_INC += -I$(DRMENGINE_LOG_SOURCE_DIR)
#********************* Define the objs *********************
VPATH := $(DRMENGINE_LOG_SOURCE_DIR)

EXTRA_CFLAGS :=
EXTRA_CFLAGS += -DCHIP_TYPE_$(CFG_HI_CHIP_TYPE) -DBOARD_TYPE_$(CFG_BOARD_TYPE) -DSDK_VERSION=$(CFG_SDK_VERSION)
EXTRA_CFLAGS += $(C_DEFINES)
EXTRA_CFLAGS += -c -O2 -Wall $(CFG_INC) $(CFG_DEBUG) -fPIC -DUSE_AEC
EXTRA_CFLAGS += -D_GNU_SOURCE -D_XOPEN_SOURCE=600 
EXTRA_CFLAGS += -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64
EXTRA_CFLAGS += -DHAVE_SYS_UIO_H=1

DRMENGINE_LOG_CPP=$(notdir $(shell find $(VPATH) -maxdepth 1 -name "*.cpp"))
DRMENGINE_LOG_C=$(notdir $(shell find $(VPATH) -maxdepth 1 -name "*.c"))
DRMENGINE_LOG_OBJS := $(DRMENGINE_LOG_CPP:%.cpp=$(DRMENGINE_LOG_OBJ_DIR)/%.o)
DRMENGINE_LOG_OBJS += $(DRMENGINE_LOG_C:%.c=$(DRMENGINE_LOG_OBJ_DIR)/%.o)

$(DRMENGINE_LOG_OBJ_DIR)/%.o : %.c*
	@$(DRMENGINE_CC) $(EXTRA_CFLAGS) -o "$(DRMENGINE_LOG_OBJ_DIR)/$(*F).o" "$<"

.PHONY: all mklog_lib log_clean
all: BUILD_DRMENGINE_LOG_OBJ_DIR  mklog_lib
clean: log_clean

#********************* Create out dir ***********************
BUILD_DRMENGINE_LOG_OBJ_DIR:
	@[ -e $(DRMENGINE_LOG_OBJ_DIR) ] || mkdir $(DRMENGINE_LOG_OBJ_DIR) 

LIB_OBJS = $(shell ls $(DRMENGINE_LOG_OBJ_DIR)/*.o)

mklog_lib: BUILD_DRMENGINE_LOG_OBJ_DIR $(DRMENGINE_LOG_OBJS)
	@echo "Enter mklog_lib..."
	@rm -f $(DRMENGINE_LOG_OUTPUTLIB_S)
	@rm -f $(DRMENGINE_LOG_OUTPUTLIB_A)

	@echo "create export lib dir"
	@mkdir -p $(DRMENGINE_LOG_OUTPUTLIB_DIR)

	@echo "create output static lib"
	@$(DRMENGINE_AR) -rsv $(DRMENGINE_LOG_OUTPUTLIB_A)  $(LIB_OBJS)
	@echo "create output dynamic lib"
	@$(DRMENGINE_CC) -shared -o $(DRMENGINE_LOG_OUTPUTLIB_S) $(LIB_OBJS)
	@echo "copy lib to pub"
	@cp -f $(DRMENGINE_LOG_OUTPUTLIB_A) $(DST_STATIC_LIB_DIR)
	@cp -f $(DRMENGINE_LOG_OUTPUTLIB_S) $(DST_SHARED_LIB_DIR)
	@echo "Leave mklog_lib..."

log_clean:
	@rm -rf $(DRMENGINE_LOG_OBJ_DIR)
	@rm -rf $(DRMENGINE_LOG_OUTPUTLIB_DIR)
	@rm -f $(DST_STATIC_LIB_DIR)/liblog*
	@rm -f $(DST_SHARED_LIB_DIR)/liblog*
