ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

ifeq ($(COMPILELIB_TOOLCHAINS_NAME),gcc-3.4.3-vfp)
    WIDEVINE_COMPILELIB_CROSS:=arm-vfp_uclibc-linux-gnu
    WIDEVINE_COMPILELIB_USER_CFLAGS = -march=armv5te -mtune=arm926ej-s
endif

ifeq ($(COMPILELIB_TOOLCHAINS_NAME),gcc-3.4.3-soft)
    WIDEVINE_COMPILELIB_CROSS:=arm-hismall-linux
    WIDEVINE_COMPILELIB_USER_CFLAGS = -march=armv5te -mtune=arm926ej-s
endif

WIDEVINE_COMPILELIB_CROSS:=$(CFG_HI_ARM_TOOLCHAINS_NAME)
#WIDEVINE_COMPILELIB_USER_CFLAGS = -march=armv7-a -mcpu=cortex-a9 -mfloat-abi=softfp -mfpu=vfpv3-d16

WIDEVINE_PROVISION_OUTPUT_BIN_DIR := $(HI_OUT_DIR)/obj/sample/widevine/provision

WIDEVINE_OBJ_DIR := $(HI_OUT_DIR)/obj/source/component/drm/widevine
WIDEVINE_SOURCE_DIR=$(SDK_DIR)/source/component/drm/widevine
WIDEVINE_SAMPLE_DIR=$(SDK_DIR)/sample/widevine

WIDEVINE_PROVISION_CC := $(WIDEVINE_COMPILELIB_CROSS)-g++
WIDEVINE_PROVISION_AR := $(WIDEVINE_COMPILELIB_CROSS)-ar

WIDEVINE_OEM_TEE_SOURCE_DIR        := $(WIDEVINE_SOURCE_DIR)/oemcrypto/hisi_teec
WIDEVINE_CDM_DIR       := $(WIDEVINE_SOURCE_DIR)/cdm
WIDEVINE_CORE_SOURCE_DIR   := $(WIDEVINE_SOURCE_DIR)/core/src
WIDEVINE_PROVISION_SOURCE_DIR := $(WIDEVINE_SAMPLE_DIR)/provision

WIDEVINE_OEM_TEE_INC_DIR      := $(WIDEVINE_SOURCE_DIR)/oemcrypto/hisi_teec
WIDEVINE_OEMCRYPTO_TEE_INC_DIR      := $(WIDEVINE_SOURCE_DIR)/oemcrypto/include
WIDEVINE_CDM_INC_DIR      := $(WIDEVINE_SOURCE_DIR)/cdm/include
WIDEVINE_CDM_ORIGIN_INC_DIR      := $(WIDEVINE_SOURCE_DIR)/cdm/include_origin
WIDEVINE_CORE_INC_DIR      := $(WIDEVINE_SOURCE_DIR)/core/include
WIDEVINE_CORE_PROTO_INC_DIR      := $(WIDEVINE_SOURCE_DIR)/core/include_proto
WIDEVINE_LINUX_INC_DIR      := $(WIDEVINE_SOURCE_DIR)/linux/include
WIDEVINE_THIRDPARTY_INC_DIR      := $(WIDEVINE_SOURCE_DIR)/third_party/stringencoders/src
WIDEVINE_THIRDPARTY_JSMN_INC_DIR := $(WIDEVINE_SOURCE_DIR)/third_party/jsmn

WIDEVINE_PROTOBUF_INC_DIR      	:= $(SDK_DIR)/source/rootfs/protobuf/include
WIDEVINE_OPENSSL_INC_DIR      	:= $(SDK_DIR)/source/component/openssl/include
WIDEVINE_TEE_CLIENT_INC_DIR		:= $(SDK_DIR)/source/tee/core/trustedcore/libteec/inc
WIDEVINE_COMM_MMZ_INC_DIR		:= $(SDK_DIR)/source/common/api/include
WIDEVINE_COMM_INC_DIR			:= $(SDK_DIR)/source/common/include
WIDEVINE_MSP_INC_DIR			:= $(SDK_DIR)/source/msp/include
WIDEVINE_RELEASE_INCLUDE_DIR	:= $(SDK_DIR)/source/component/drm/widevine/include

WIDEVINE_PROVISION_OBJ_DIR                 := $(WIDEVINE_PROVISION_SOURCE_DIR)/obj_$(WIDEVINE_COMPILELIB_CROSS)
WIDEVINE_PROVISION_OUTPUT_BIN_DIR          := $(HI_OUT_DIR)/obj/sample/widevine/provision
WIDEVINE_PROVISION_OUTPUTLIB_HEADR         := $(WIDEVINE_PROVISION_SOURCE_DIR)/$(WIDEVINE_COMPILELIB_CROSS)/include
WIDEVINE_PROVISION_OUTPUT_BIN         	   := $(WIDEVINE_PROVISION_SOURCE_DIR)/sample_keybox_provision
WIDEVINE_PROVISION_SIGNLE_CLEAR_OUTPUT_BIN := $(WIDEVINE_PROVISION_SOURCE_DIR)/sample_keybox_single_clear_provision

#### open debug
#CFG_DEBUG = -g
###############################include *h##########################################
CFG_INC = -I$(WIDEVINE_COMM_INC_DIR) \
		  -I$(WIDEVINE_OEM_TEE_INC_DIR) \
		  -I$(WIDEVINE_MSP_INC_DIR) \
		  -I$(WIDEVINE_RELEASE_INCLUDE_DIR) \
		  -I$(WIDEVINE_MSP_INC_DIR)/../api/higo/include

VPATH := $(WIDEVINE_PROVISION_SOURCE_DIR)

EXTRA_CFLAGS :=
EXTRA_CFLAGS += -DCHIP_TYPE_$(CFG_HI_CHIP_TYPE) -DBOARD_TYPE_$(CFG_BOARD_TYPE) -DSDK_VERSION=$(CFG_SDK_VERSION)
EXTRA_CFLAGS += $(C_DEFINES)
EXTRA_CFLAGS += -c -O2 -Wall $(CFG_INC) $(CFG_DEBUG) $(WIDEVINE_COMPILELIB_USER_CFLAGS) -fPIC -DUSE_AEC
#EXTRA_CFLAGS += -c -Wall $(CFG_INC) $(CFG_DEBUG) $(PLAYREADY_COMPILELIB_USER_CFLAGS) -fPIC -DUSE_AEC
EXTRA_CFLAGS += -D_GNU_SOURCE -D_XOPEN_SOURCE=600 
EXTRA_CFLAGS += -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64
#EXTRA_CFLAGS += -DZLIB_SHARED -DZLIB -DOPENSSL_THREADS -march=armv7-a -mcpu=cortex-a9 -mfloat-abi=softfp -mfpu=vfpv3-d16 -DOPENSSL_NO_STATIC_ENGINE -ldl -fPIC

LDFLAGS += -L$(SDK_DIR)/source/component/openssl/release/lib
LDFLAGS += -L$(SDK_DIR)/source/rootfs/protobuf/lib
LDFLAGS += -L$(SDK_DIR)/source/component/widevine/oemcrypto/hisi_teec/arm-histbv310-linux
LDFLAGS += -L$(HI_SHARED_LIB_DIR)
LDFLAGS += -L$(HI_STATIC_LIB_DIR)
LDFLAGS += -lhi_widevine_tee -lhi_msp -lhi_common -ljpeg -lpthread -ldl -lrt -lteec

OEM_PROVISION_WIDEVINE_SRC := ./sample_keybox.cpp
OEM_PROVISION_SIGNLE_CLEAR_WIDEVINE_SRC := ./sample_keybox_single_clear.cpp

OEM_PROVISION_WIDEVINE_OBJS := $(OEM_PROVISION_WIDEVINE_SRC:%.cpp=$(WIDEVINE_PROVISION_OBJ_DIR)/%.o)
OEM_PROVISION_SIGNLE_CLEAR_WIDEVINE_OBJS := $(OEM_PROVISION_SIGNLE_CLEAR_WIDEVINE_SRC:%.cpp=$(WIDEVINE_PROVISION_OBJ_DIR)/%.o)

$(WIDEVINE_PROVISION_OBJ_DIR)/%.o : %.cpp
	@[ -e $(WIDEVINE_PROVISION_OBJ_DIR) ] || mkdir $(WIDEVINE_PROVISION_OBJ_DIR)
	@$(WIDEVINE_PROVISION_CC) $(EXTRA_CFLAGS) $(LDFLAGS) -o "$(WIDEVINE_PROVISION_OBJ_DIR)/$(*F).o" "$<"

.PHONY: all
all: BUILD_PUBLIC_OBJ_DIR  mkprovision_bin mkprovision_single_clear_bin
clean: public_clean

#********************* Create out dir ***********************
BUILD_PUBLIC_OBJ_DIR:
	@[ -e $(WIDEVINE_PROVISION_OBJ_DIR) ] || mkdir $(WIDEVINE_PROVISION_OBJ_DIR)

#LIB_OBJS=$(shell ls $(WIDEVINE_PROVISION_OBJ_DIR)/*.o)
LIB_OBJS=$(WIDEVINE_PROVISION_OBJ_DIR)/sample_keybox.o
LIB_SIGNLE_CLEAR_OBJS=$(WIDEVINE_PROVISION_OBJ_DIR)/sample_keybox_single_clear.o

mkprovision_bin: BUILD_PUBLIC_OBJ_DIR $(OEM_PROVISION_WIDEVINE_OBJS)	
	@echo "create widevine provision output bin"
	@$(WIDEVINE_PROVISION_CC) -o $(WIDEVINE_PROVISION_OUTPUT_BIN) $(LIB_OBJS) $(LDFLAGS)
	@echo "Leave build_provision..."
	
	@echo "copy provision output bin"
	$(AT)test -d $(WIDEVINE_PROVISION_OUTPUT_BIN_DIR) || mkdir -p $(WIDEVINE_PROVISION_OUTPUT_BIN_DIR)
	@cp $(SDK_DIR)/sample/widevine/provision/sample_keybox_provision $(WIDEVINE_PROVISION_OUTPUT_BIN_DIR)
	@echo "copy provision output bin finished"
	
mkprovision_single_clear_bin: BUILD_PUBLIC_OBJ_DIR $(OEM_PROVISION_SIGNLE_CLEAR_WIDEVINE_OBJS)	
	@echo "create widevine provision single clear output bin"
	@$(WIDEVINE_PROVISION_CC) -o $(WIDEVINE_PROVISION_SIGNLE_CLEAR_OUTPUT_BIN) $(LIB_SIGNLE_CLEAR_OBJS) $(LDFLAGS)
	@echo "Leave build_provision..."
	
	@echo "copy provision single clear output bin"
	$(AT)test -d $(WIDEVINE_PROVISION_OUTPUT_BIN_DIR) || mkdir -p $(WIDEVINE_PROVISION_OUTPUT_BIN_DIR)
	@cp $(SDK_DIR)/sample/widevine/provision/sample_keybox_single_clear_provision $(WIDEVINE_PROVISION_OUTPUT_BIN_DIR)
	@echo "copy provision single clear output bin finished"

public_clean:
	@rm -rf $(WIDEVINE_PROVISION_OBJ_DIR)/
	@rm -rf $(WIDEVINE_PROVISION_OUTPUT_BIN_DIR)/
	@rm -f $(WIDEVINE_PROVISION_OUTPUT_BIN)
	@rm -f $(WIDEVINE_PROVISION_SIGNLE_CLEAR_OUTPUT_BIN)
