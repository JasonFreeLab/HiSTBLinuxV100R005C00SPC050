
###########################################################
# platform definition
###########################################################
ROOT      =.
LOCAL_CFLAGS =
LOCAL_ASFLAGS =

ifeq ($(strip $(CFG_HI_TEE_STB_PLATFORM_SUPPORT)), y)
LOCAL_CFLAGS += -DSTB=1
else
LOCAL_CFLAGS += -DDPT=1
endif

widevine_PATH=modular_widevine

LOCAL_C_INCLUDES += \
    -I$(ROOT)/../../../../source/common/include \
    -I$(ROOT)/../../../../source/common/api/include \
    -I$(HI_TEE_API_DIR)/mem/include \
    -I$(ROOT)/../../../../source/msp/include

LOCAL_C_INCLUDES += \
    -I$(ROOT)/provision \
    -I$(ROOT)/$(widevine_PATH)/ \
    -I$(ROOT)/classic_widevine/ \
    -I$(ROOT)/classic_widevine/hal  \
    -I$(ROOT)
	
LOCAL_SRC_FILES :=  $(ROOT)/task_widevine_tzserver.o \
			$(ROOT)/classic_widevine/task_widevine.o \
			$(ROOT)/classic_widevine/task_wv_tzserver.o \
			$(ROOT)/classic_widevine/widevine_hal.o \
			$(ROOT)/classic_widevine/hal/hi_cipher.o \
			$(ROOT)/classic_widevine/hal/wvcrc.o \
			$(ROOT)/classic_widevine/aes.o \
			$(ROOT)/$(widevine_PATH)/task_modular_wv_tzserver.o \
			$(ROOT)/$(widevine_PATH)/hi_crypto.o \
			$(ROOT)/$(widevine_PATH)/hi_oem_engine_mock.o \
			$(ROOT)/$(widevine_PATH)/hi_oem_keybox_mock.o \
			$(ROOT)/$(widevine_PATH)/hi_oem_key_mock.o \
			$(ROOT)/$(widevine_PATH)/hi_oem_mock.o \
			$(ROOT)/$(widevine_PATH)/hi_oem_usage_table_mock.o \
			$(ROOT)/$(widevine_PATH)/hi_oem_wvcrc.o \
			$(ROOT)/$(widevine_PATH)/hi_wv_util.o \
			$(ROOT)/$(widevine_PATH)/asn1parse.o \
			$(ROOT)/$(widevine_PATH)/bignum.o \
			$(ROOT)/$(widevine_PATH)/pkparse.o \
			$(ROOT)/provision/widevine_provision.o \
			$(ROOT)/provision/tea_decrypt.o

####drm_hal###
LOCAL_C_INCLUDES += \
    -I$(ROOT)/../drm_hal/include \
    -I$(ROOT)/../drm_hal/stb

LOCAL_SRC_FILES += \
    $(ROOT)/../drm_hal/stb/hi_haldrmcipher.o \
    $(ROOT)/../drm_hal/stb/hi_haldrmotp.o \
    $(ROOT)/../drm_hal/stb/hi_haldrmsmmu.o \
    $(ROOT)/../drm_hal/stb/hi_haldrmutil.o \
    $(ROOT)/../drm_hal/stb/hi_haldrmkeyladder.o \
	$(ROOT)/../drm_hal/stb/hi_haldrmcrypto.o

LOCAL_MODULE:= $(OUT)/task_wv_server.elf
ifeq ($(strip $(CFG_HI_TEE_SMMU_SUPPORT)), y)
CFLAGS += -DHI_SMMU_SUPPORT
endif
CFLAGS += -DDRM_HAL_LOG_LEVEL=1
#CFLAGS += -DCIPHER_BASED_CRYPTO

TASK_WIDEVINE_PATH = $(TRUSTEDCORE_RELEASE_DIR)/$(HI_CHIP_TYPE)/$(CFG_HI_TVP_MEM_LAYOUT)/$(notdir $(LOCAL_MODULE))
ifneq ($(strip $(CONFIG_TRUSTEDCORE_RELEASE)), )
ifneq ($(TASK_WIDEVINE_PATH), $(wildcard $(TASK_WIDEVINE_PATH)))
all:
	@echo "Do Not support widevine"
else
include $(HI_TEE_TA_DIR)/ta.mak
endif
else
include $(HI_TEE_TA_DIR)/ta.mak
endif
