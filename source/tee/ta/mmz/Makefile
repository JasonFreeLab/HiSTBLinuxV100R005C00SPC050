LOCAL_C_INCLUDES := \
    -I$(HI_TEE_API_DIR)/mem/include \
    -I$(DEVCHIP_TEE_H)/drv/mem/hi_smmu/include/

LOCAL_SRC_FILES := sec_mmz_server.o

CFLAGS += -Werror -Wall

LOCAL_MODULE := $(OUT)/task_sec_mmz.elf

include $(HI_TEE_TA_DIR)/ta.mak
