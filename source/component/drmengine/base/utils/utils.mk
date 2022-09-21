LOCAL_PATH := $(my-dir)

# build utils
include $(CLEAR_VARS)

LOCAL_MODULE := libutils

LOCAL_SRC_FILES += $(notdir $(foreach dir, $(LOCAL_PATH), $(wildcard $(dir)/*.cpp)))

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../include

LOCAL_CPPFLAGS := -include $(LOCAL_PATH)/../include/arch/linux-arm/AndroidConfig.h \
                  -I$(LOCAL_PATH)/../include/arch \
                  -fpermissive -Wno-unused-function -Wno-unused-variable
LOCAL_LDLIBS :=  -lpthread

include $(BUILD_SHARED_LIBRARY)
