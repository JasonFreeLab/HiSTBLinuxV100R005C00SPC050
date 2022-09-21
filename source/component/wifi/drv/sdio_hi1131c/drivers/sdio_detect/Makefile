HI1102_DRIVER_BUILTIN_PATH := $(subst ",,$(CONFIG_HI110X_DRIVER_PATH))
DRIVER_FLODER = sdio_detect
 

export HI1102_DRIVER_VERSION  ?= 1102
export HI1102_BOARD_VERSION ?= v8r2
export PLAT_DEFCONFIG_FILE ?= plat_$(HI1102_DRIVER_VERSION)_$(HI1102_BOARD_VERSION)_defconfig

HI1102_COMM_DEFCONFIG := hi110x_comm_defconfig
ifneq ($(KERNELRELEASE),)
ifeq ($(HI1102_MAKE_FLAG),)
KERNEL_DIR=$(PWD)
HI1102_DRIVER_SRC_PATH=$(KERNEL_DIR)/$(HI1102_DRIVER_BUILTIN_PATH)
endif


HI1102_DRIVER_SRC_PATH := $(src)/..
DRIVER_PATH=$(HI1102_DRIVER_SRC_PATH)/$(DRIVER_FLODER)
PLATFORM_PATH = $(HI1102_DRIVER_SRC_PATH)/platform

include $(PLATFORM_PATH)/$(HI1102_COMM_DEFCONFIG)
include $(PLATFORM_PATH)/$(PLAT_DEFCONFIG_FILE)

detect-objs := plat_sdio_detect.o
board-objs := ../platform/board/board_hi3798/board.o
ini-objs := ../common/customize/hisi_ini.o

sdio_detect-objs += $(detect-objs)
sdio_detect-objs += $(board-objs)
sdio_detect-objs += $(ini-objs)

#plat ko
ifeq ($(CONFIG_HI110X_KERNEL_MODULES_BUILD_SUPPORT), yes)
obj-m += sdio_detect.o
else
obj-y += sdio_detect.o
endif

HI1102_INCLUDES += -I$(PLATFORM_PATH)/inc/oal
HI1102_INCLUDES += -I$(PLATFORM_PATH)/inc/oal/linux
HI1102_INCLUDES += -I$(PLATFORM_PATH)/../common/inc
HI1102_INCLUDES += -I$(PLATFORM_PATH)/../common/chr_log
HI1102_INCLUDES += -I$(PLATFORM_PATH)/board/board_hi3798

HI1102_INCLUDES += -I$(PLATFORM_PATH)/pm
HI1102_INCLUDES += -I$(PLATFORM_PATH)/inc
HI1102_INCLUDES += -I$(PLATFORM_PATH)/../dft
HI1102_INCLUDES += -I$(PLATFORM_PATH)/../common/customize

EXTRA_CFLAGS = $(HI1102_INCLUDES)
EXTRA_CFLAGS += $(COPTS) $(KBUILD_CFLAGS)
EXTRA_CFLAGS += $(COMM_COPTS)
EXTRA_CFLAGS += -DHI1131C_SDIO_DETECT_SUPPORT
EXTRA_CFLAGS += -Werror -Wuninitialized -Wempty-body -Wclobbered -Wignored-qualifiers  -Wmissing-parameter-type -Wold-style-declaration -Woverride-init -Wtype-limits

EXTRA_CFLAGS +=  -fno-pic
MODFLAGS = -fno-pic
else

#make modules
export HI1102_MAKE_FLAG=MODULES
export HI1102_DRIVER_SRC_PATH ?= $(shell pwd)/..

PATH := $(CROSS_DIR):$(PATH)
CONFIG_HI110X_KERNEL_MODULES_BUILD_SUPPORT ?= yes

default:
	$(MAKE) -C $(KERNEL_DIR) $(MODULE_PARAM)  M=$(HI1102_DRIVER_SRC_PATH)/$(DRIVER_FLODER) modules

clean:
	$(MAKE) -C $(KERNEL_DIR) M=$(HI1102_DRIVER_SRC_PATH)/$(DRIVER_FLODER) clean
	-find ../dft/ -type f -name "*.o" -exec rm -f {} \;
	-find ../dft/ -type f -name "*.o.cmd" -exec rm -f {} \;
	-find ../common/ -type f -name "*.o" -exec rm -f {} \;
	-find ../common/ -type f -name "*.o.cmd" -exec rm -f {} \;
	
endif
