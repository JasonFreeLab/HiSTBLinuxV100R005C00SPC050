LOCAL_C_INCLUDES := \
    -I$(TRUSTEDCORE_DIR)/platform/$(PLATFORM_DIR)/dispatch \
    -I$(HI_TEE_API_DIR)/mem/include

LOCAL_SRC_FILES := \
         hisi_demo_task.o

LOCAL_MODULE:= $(OUT)/task_hisi_demo.elf
MANIFEST_FILE := $(ROOT)/manifest.txt

# demo release with src, not ELF file, set null.
CONFIG_TRUSTEDCORE_RELEASE :=

ifeq ($(strip $(CFG_HI_TEE_TEST_SUPPORT)), y)
LOCAL_CFLAGS += -DDEMO_TRUSTEDCORE_TEST
endif

include $(HI_TEE_TA_DIR)/ta.mak

