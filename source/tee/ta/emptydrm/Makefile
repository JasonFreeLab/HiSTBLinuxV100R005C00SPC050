ROOT      =.

LOCAL_C_INCLUDES := \
    -I$(TRUSTEDCORE_DIR)/platform/$(PLATFORM_DIR)/dispatch \
    -I$(HI_TEE_API_DIR)/mem/include \
    -I$(ROOT)/hal/include \
    -I$(ROOT)/

ifeq ($(strip $(WITH_HISI_SMMU)), true)
LOCAL_C_INCLUDES += \
    -I$(ROOT)/hal/stb/tee
else
LOCAL_C_INCLUDES += \
    -I$(ROOT)/hal/stb/tvp
endif

LOCAL_SRC_FILES := \
         $(ROOT)/hi_wv_util.o \
         $(ROOT)/emptydrm_cipher.o \
         $(ROOT)/emptydrm_task.o \
		 $(ROOT)/aes.o

####drm_hal###
LOCAL_C_INCLUDES += \
    -I$(ROOT)/../drm_hal/include \
    -I$(ROOT)/../drm_hal/stb \

LOCAL_SRC_FILES += \
    $(ROOT)/../drm_hal/stb/hi_haldrmcipher.o \
    $(ROOT)/../drm_hal/stb/hi_haldrmotp.o \
    $(ROOT)/../drm_hal/stb/hi_haldrmsmmu.o \
    $(ROOT)/../drm_hal/stb/hi_haldrmutil.o

ifeq ($(strip $(WITH_HISI_SMMU)), true)
LOCAL_SRC_FILES += \
    $(ROOT)/hal/stb/tee/hi_halwvcipher.o \
    $(ROOT)/hal/stb/tee/hi_halwvotp.o
else
LOCAL_SRC_FILES += \
    $(ROOT)/hal/stb/tvp/hi_halwvcipher.o \
    $(ROOT)/hal/stb/tvp/hi_halwvotp.o
endif

ifeq ($(strip $(WITH_HISI_SMMU)), true)
CFLAGS += -DHI_SMMU_SUPPORT
endif

LOCAL_MODULE:= $(OUT)/task_emptydrm.elf

include $(HI_TEE_TA_DIR)/ta.mak
