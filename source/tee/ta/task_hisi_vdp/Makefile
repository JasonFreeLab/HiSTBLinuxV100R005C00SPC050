LOCAL_C_INCLUDES := \
    -I$(HI_TEE_DRV_DIR)/vdp/ \
    -I$(HI_TEE_API_DIR)/mem/include \

LOCAL_SRC_FILES := \
         hisi_vdp_task.o\
         vmx_signoff4_symbols.o

LOCAL_MODULE:= $(OUT)/task_hisi_vdp.elf

include $(HI_TEE_TA_DIR)/ta.mak
