

LOCAL_C_INCLUDES := \
    -I$(HI_TEE_OS_DIR)/trustedcore/include/TEE \
    -I$(HI_TEE_API_DIR)/include \
    -I$(HI_TEE_OS_DIR)/trustedcore/platform/$(PLATFORM_DIR)/dispatch \
    -I$(HI_TEE_API_DIR)/mem/include

LOCAL_SRC_FILES := \
         suma_task.o des.o

LOCAL_MODULE:= $(OUT)/task_suma.elf

include $(HI_TEE_TA_DIR)/ta.mak
