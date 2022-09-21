#by sdk 2015-03-13

#====================================================================================
#                   export
#====================================================================================
.EXPORT_ALL_VARIABLES:
OS_PLATFORM_TYPE := LINUX

include trustedcore.mk

###########################################################
# platform definition
###########################################################
TARGET_IMG = $(OUT)/trustedcore.img

##########################################################
# build all
##########################################################
.PHONY : all build packimg clean
.PHONY : drivers       platform       rtosck       globaltask       internal_tasks
.PHONY : drivers_clean platform_clean rtosck_clean globaltask_clean internal_tasks_clean

all: packimg
packimg: globaltask internal_tasks rtosck

ifneq ($(strip $(CONFIG_TRUSTEDCORE_RELEASE)),true)
rtosck:  drivers
rtosck_clean: drivers_clean
endif

rtosck: platform
rtosck_clean: platform_clean

clean: rtosck_clean globaltask_clean internal_tasks_clean
	$(RM) $(TARGET_IMG)
	$(RM) -rf $(OUT)
	$(RM) -rf $(TRUSTEDCORE_DIR)/tools/elf_extract

##########################################################
# 1. build rtosck
##########################################################
rtosck:
	$(MAKE) -C trustedcore_kernel/ all

rtosck_clean:
	$(MAKE) -C trustedcore_kernel/ clean

##########################################################
# 2. build globaltask
##########################################################
globaltask:
	$(MAKE) -C TEE_ext/ all

globaltask_clean:
	$(MAKE) -C TEE_ext/ clean

##########################################################
# 3. build internal_tasks
##########################################################
internal_tasks:
	$(if $(TRUSTEDCORE_PACK_TA_SCRIPT), chmod 777 $(TRUSTEDCORE_PACK_TA_SCRIPT))
	$(MAKE) -C internal_tasks/ all

internal_tasks_clean:
	$(MAKE) -C internal_tasks/ clean

##########################################################
# 2. build drivers
##########################################################
drivers:
	$(MAKE) -C drivers/ all

drivers_clean:
	$(MAKE) -C drivers/ clean

##########################################################
# 3. build platform
##########################################################
platform:
	$(MAKE) -C platform/ all

platform_clean:
	$(MAKE) -C platform/ clean

##########################################################
# 6. packimg
##########################################################
PACKIMG_SHELL =${TRUSTEDCORE_DIR}/platform/${PLATFORM_DIR}/${PLATFORM_DIR_NAME}/packimg_linux.sh

packimg:
	chmod 777 ${PACKIMG_SHELL}
	@${PACKIMG_SHELL} $(PACKING_CFG)
	@echo "Make $(TARGET_IMG) Success!"

