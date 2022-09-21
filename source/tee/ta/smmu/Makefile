LOCAL_C_INCLUDES := \
    -I$(HI_TEE_API_DIR)/mem/include \
    -I$(HI_TEE_DRV_DIR)/include \
    -I$(DEVCHIP_TEE_H)/drv/mem/hi_smmu/include/ 

LOCAL_SRC_FILES := \
         smmu_task.o
#CFLAGS += -Werror -Wall

LOCAL_MODULE:= $(OUT)/smmu_task.elf

include $(HI_TEE_TA_DIR)/ta.mak
