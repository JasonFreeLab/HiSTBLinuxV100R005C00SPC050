ifeq ($(strip $(CFG_HI_TEE_AVPLAY_SUPPORT)), y)
objects += avplay
endif

ifeq ($(strip $(CFG_HI_TEE_NETFLIX_SUPPORT)), y)
objects += netflix
endif

ifeq ($(strip $(CFG_HI_TEE_BEIDOU_SUPPORT)), y)
objects += beidou
endif

ifeq ($(strip $(CFG_HI_TEE_CIPHER_SUPPORT)), y)
objects += cipher
endif

ifeq ($(strip $(CFG_HI_TEE_COMMON_SUPPORT)), y)
objects += common
endif

ifeq ($(strip $(CFG_HI_ADVCA_TYPE)), DCAS)
objects += klad
endif

ifeq ($(strip $(CFG_HI_TEE_DEMUX_SUPPORT)), y)
objects += demux
endif

ifeq ($(strip $(CFG_HI_TEE_DISPCTRL_SUPPORT)), y)
objects += dispctrl
endif

ifeq ($(strip $(CFG_HI_TEE_HDMI_SUPPORT)), y)
objects += hdmi
endif

ifeq ($(strip $(CFG_HI_TEE_KLAD_SUPPORT)), y)
objects += keyladder
endif

ifeq ($(strip $(CFG_HI_TEE_SEC_MMZ_SUPPORT)), y)
objects += mem
else ifeq ($(strip $(CFG_HI_TEE_SMMU_SUPPORT)), y)
objects += mem
endif

ifeq ($(strip $(CFG_HI_TEE_OTP_SUPPORT)), y)
objects += otp
#objects += security_check
endif

ifeq ($(strip $(CFG_HI_TEE_PLCIPHER_SUPPORT)), y)
objects += plcipher
endif

ifeq ($(strip $(CFG_HI_TEE_PVR_SUPPORT)), y)
objects += pvr
endif

ifeq ($(strip $(CFG_HI_TEE_VDP_SUPPORT)), y)
objects += vdp
endif

ifeq ($(strip $(CFG_HI_TEE_TA_LOAD_SUPPORT)), y)
objects += taload
endif

ifeq ($(strip $(CFG_HI_TEE_SM_SUPPORT)), y)
objects += session_manage
endif

ifeq ($(strip $(CFG_HI_TEE_MAILBOX_SUPPORT)), y)
objects += mailbox
endif

objects += ta_al/trustedcore

#export CFLAGS
##########################################################
# project path definition
##########################################################
LOCAL_OUT = $(OUT)/$(notdir $(CURDIR))

objects_clean:=$(addsuffix _clean,$(objects))
objects_install:=$(addsuffix _install,$(objects))
objects_uninstall:=$(addsuffix _uninstall,$(objects))

DEVCHIP_TEE_INS := \
	-I$(TRUSTEDCORE_DIR)/platform/devchip/$(PLATFORM_DIR_NAME)/ext/user \
	-I$(TRUSTEDCORE_DIR)/platform/devchip/$(PLATFORM_DIR_NAME)/ext/user/asm_mem \
	-I$(TRUSTEDCORE_DIR)/platform/devchip/$(PLATFORM_DIR_NAME)/ext/kernel \
	-I$(HI_TEE_API_DIR)/mem/include \
	-I$(HI_TEE_API_DIR)/ta_al/trustedcore \
	-I$(HI_TEE_API_DIR)/include \
	-I$(HI_TEE_DRV_DIR)/include



CFLAGS += $(DEVCHIP_TEE_INS)

ifeq ($(strip $(CFG_HI_LOG_SUPPORT)), y)
CFLAGS += -DHI_TEE_LOG_SUPPORT=1
endif

ifdef CFG_HI_LOG_LEVEL
CFLAGS += -DHI_TEE_LOG_LEVEL=$(CFG_HI_LOG_LEVEL)
else
CFLAGS += -DHI_TEE_LOG_LEVEL=1
endif

#export CFLAGS
LIBS := $(LOCAL_OUT)/libstbapi.a
SUBLIBS := $(foreach sub,$(objects),$(LOCAL_OUT)/$(sub)/libsec_api_$(notdir $(sub)).a)

##########################################################
# build libstbapi.a
##########################################################
.PHONY: all clean install uninstall $(LIBS)

#==================================================================
# build libstbapi.a
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

