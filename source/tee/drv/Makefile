###########################################################
# platform definition
###########################################################
LOCAL_CFLAGS    += $(TRUSTEDCORE_LOCAL_CFLAGS)
LOCAL_ASFLAGS   += $(TRUSTEDCORE_LOCAL_ASFLAGS)

ifneq ($(findstring $(HI_CHIP_TYPE),hi3798mv200  hi3798mv300 hi3798mv200_a),)
VDP_PRODUCT := 98mv200
endif

ifneq ($(findstring $(HI_CHIP_TYPE),hi3798cv200),)
VDP_PRODUCT := 98cv200
endif

ifneq ($(findstring $(HI_CHIP_TYPE),hi3796mv200),)
VDP_PRODUCT := 96mv200
endif


#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#	variable
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
objects :=


COMMON_KRENEL_INCS := \
        -I$(TRUSTEDCORE_DIR)/include/kernel/ \
        -I$(TRUSTEDCORE_DIR)/include/config/ \
		-I$(TRUSTEDCORE_DIR)/include/TEE \
		-I$(TRUSTEDCORE_DIR)/platform/devchip/$(PLATFORM_DIR_NAME)/include \
		-I$(HI_TEE_DRV_DIR)/os_hal/trustedcore \
		-I$(HI_TEE_DRV_DIR)/include \
		-I$(HI_TEE_API_DIR)/include \
		-I$(HI_TEE_DRV_DIR)/vdp/drv \
		-I$(HI_TEE_DRV_DIR)/vdp/ \
		-I$(HI_TEE_DRV_DIR)/vdp/hal/ \
		-I$(HI_TEE_DRV_DIR)/vdp/hal/$(VDP_PRODUCT)/inc \
	-I$(TRUSTEDCORE_DIR)/platform/devchip/stb/pm

###########################################################
PLAT_SYS_INCS := -I$(TRUSTEDCORE_DIR)/platform

objects +=mem

ifeq ($(strip $(CFG_HI_TEE_OTP_SUPPORT)), y)
objects += otp
endif

ifeq ($(strip $(CFG_HI_TEE_KLAD_SUPPORT)), y)
objects += klad
endif

ifneq ($(findstring $(CFG_HI_ADVCA_TYPE), NAGRA VERIMATRIX VERIMATRIX_ULTRA),)
objects += security_check
endif

ifeq ($(strip $(CFG_HI_TEE_DEMUX_SUPPORT)), y)
objects += demux
endif

ifeq ($(strip $(CFG_HI_TEE_PLCIPHER_SUPPORT)), y)
objects += plcipher
endif

ifeq ($(strip $(CFG_HI_TEE_PVR_SUPPORT)), y)
objects += pvr
endif

#ifeq ($(strip $(CFG_HI_TEE_LOG_SUPPORT)), y)
objects += common/log
#endif

ifeq ($(strip $(CFG_HI_TEE_AVPLAY_SUPPORT)), y)
objects += avplay
endif

ifeq ($(strip $(CFG_HI_TEE_NETFLIX_SUPPORT)), y)
objects += netflix
endif

ifeq ($(strip $(CFG_HI_TEE_CIPHER_SUPPORT)), y)
objects += cipher
endif

ifeq ($(strip $(CFG_HI_TEE_HDMI_SUPPORT)), y)
objects += hdmi
endif

ifeq ($(strip $(CFG_HI_TEE_DISPCTRL_SUPPORT)), y)
objects += dispctrl
endif

ifeq ($(strip $(CFG_HI_TEE_VDP_SUPPORT)), y)
objects += vdp
endif

ifeq ($(strip $(CFG_HI_TEE_VFMW_SUPPORT)), y)
objects += vfmw
endif

ifeq ($(strip $(CFG_HI_TEE_SEC_TIMER_SUPPORT)), y)
objects += timer
endif

ifeq ($(strip $(CFG_HI_TEE_BEIDOU_SUPPORT)), y)
objects += beidou
endif

ifeq ($(strip $(CFG_HI_TEE_I2C_SUPPORT)), y)
objects += i2c
endif

ifeq ($(strip $(CFG_HI_TEE_VMX_ULTRA_SUPPORT)), y)
objects += vmx
endif

ifeq ($(strip $(CFG_HI_TEE_DEBUG_SUPPORT)), y)
objects += debug
endif

ifeq ($(strip $(CFG_HI_TEE_COMMON_SUPPORT)), y)
objects += common
endif

objects += tzasc

ifeq ($(findstring $(CFG_HI_CHIP_TYPE), hi3796mv100 hi3798mv100 hi3716dv100),)
objects += mem_layout
endif

ifeq ($(strip $(CFG_HI_TEE_PM_SUPPORT)), y)
objects += pm
endif

ifeq ($(strip $(CFG_HI_TEE_SM_SUPPORT)), y)
objects += session_manage
endif


ifeq ($(strip $(CFG_HI_TEE_RPMB_KEY_SUPPORT)), y)
objects += mmc
endif

ifeq ($(strip $(CFG_HI_TEE_MAILBOX_SUPPORT)), y)
objects += mailbox
endif

objects += os_hal/trustedcore

##########################################################
# project path definition
##########################################################
LOCAL_OUT = $(OUT)/$(notdir $(CURDIR))

#include $(TRUSTEDCORE_BUILD_RAW_EXECUTABLE)
# add for enum size may different in different toolchain
LOCAL_CFLAGS += -fno-short-enums -fno-exceptions -fno-unwind-tables
LOCAL_ASFLAGS += -fno-short-enums -fno-exceptions -fno-unwind-tables

LOCAL_CFLAGS += -march=armv7-a

CFLAGS += $(COMMON_KRENEL_INCS)
CFLAGS += $(LOCAL_CFLAGS)

ifeq ($(strip $(CFG_HI_LOG_SUPPORT)), y)
CFLAGS += -DHI_TEE_LOG_SUPPORT=1
endif

ifdef CFG_HI_LOG_LEVEL
CFLAGS += -DHI_TEE_LOG_LEVEL=$(CFG_HI_LOG_LEVEL)
else
CFLAGS += -DHI_TEE_LOG_LEVEL=1
endif

#LDFLAGS += $(LOCAL_LDFLAGS)

#export CFLAGS

objects_clean:=$(addsuffix _clean,$(objects))
objects_install:=$(addsuffix _install,$(objects))
objects_uninstall:=$(addsuffix _uninstall,$(objects))

ifeq ($(WITH_ARMV8_SUPPORT) , true)
#ARMV8_POSIX_STR := 64bit
endif

#export ARMV8_POSIX_STR

LIBS := $(LOCAL_OUT)/libstbdrv.a
SUBLIBS := $(foreach sub,$(objects),$(LOCAL_OUT)/$(sub)/libsec_$(notdir $(sub)).a)

##########################################################
# build libstbdrv.a
##########################################################
.PHONY: all clean install uninstall $(LIBS)

#==================================================================
# build libstbdrv.a
#==================================================================

all: $(LIBS)

clean:  $(objects_clean)
	$(AT)rm -rf $(LIBS)
	$(AT)rm -rf ar.mak

install: $(objects_install)

uninstall: $(objects_uninstall)

$(LIBS): $(objects)
	rm -rf $@
	echo "CREATE $@" > $(LOCAL_OUT)/ar.mak
	$(foreach sublib,$(SUBLIBS),echo "ADDLIB $(sublib)" >> $(LOCAL_OUT)/ar.mak;)
	echo "SAVE" >> $(LOCAL_OUT)/ar.mak
	echo "END" >> $(LOCAL_OUT)/ar.mak
	$(AR2) -M < $(LOCAL_OUT)/ar.mak

#==================================================================
#                          modules
#==================================================================
.PHONY: $(objects) $(objects_clean) $(objects_install) $(objects_uninstall)

prepare:
	echo "prepare done!"
$(objects): | prepare
	make -C $@ all

$(objects_clean):
	make -C $(patsubst %_clean,%,$@) clean

$(objects_install):
	make -C $(patsubst %_clean,%,$@) install

$(objects_uninstall):
	make -C $(patsubst %_clean,%,$@) uninstall

