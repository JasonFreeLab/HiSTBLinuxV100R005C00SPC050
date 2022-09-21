#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#	variable
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
objects := common db flash pq disp graphic hdmi i2c gpio pdm

ifeq ($(CFG_HI_BUILD_WITH_FRONTEND), y)
objects += frontend
endif

ifeq ($(CFG_HI_GPIOI2C_SUPPORT), y)
objects += gpioi2c
endif

ifeq ($(CFG_HI_BUILD_WITH_DEMUX), y)
objects += demux
endif

ifeq ($(CFG_HI_BUILD_WITH_IR), y)
objects += ir
endif

ifeq ($(CFG_HI_BUILD_WITH_KEYLED), y)
objects += keyled
endif

ifeq ($(CFG_HI_ADVCA_SUPPORT), y)
	objects += cipher
	objects += pmoc
	ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716dv100 hi3796mv100 hi3798mv100 hi3798cv200 hi3798mv200_a hi3798mv200 hi3798mv300),)
		objects += advca
	else
		ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716mv410 hi3716mv420),)
			ifneq ($(CFG_HI_ADVCA_TYPE),NAGRA)
				objects += advca
			else
				objects += klad
        	endif
    	else
    		objects += klad
    	endif
	endif
endif

ifeq ($(CFG_HI_PM_POWERUP_MODE1_SUPPORT), y)
objects += pmoc
endif

objects += otp

objects_clean:=$(addsuffix _clean,$(objects))
objects_install:=$(addsuffix _install,$(objects))
objects_uninstall:=$(addsuffix _uninstall,$(objects))

LIBS := libdriver.a
SUBLIBS := $(foreach sub,$(objects),$(sub)/lib$(sub).a)

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#	rules
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#==================================================================
#                          all
#==================================================================
.PHONY: all clean install uninstall $(LIBS)

all: $(LIBS)

clean:  $(objects_clean)
	$(AT)rm -rf $(LIBS)
	$(AT)rm -rf ar.mak

install: $(objects_install)

uninstall: $(objects_uninstall)

$(LIBS): $(objects)
	$(AT)rm -rf $@
	$(AT)rm -rf ar.mak
	$(AT)echo "CREATE $@" >> ar.mak
	$(AT)$(foreach sublib,$(SUBLIBS),echo "ADDLIB $(sublib)" >> ar.mak;)
	$(AT)echo "SAVE" >> ar.mak
	$(AT)echo "END" >> ar.mak
	$(AT)$(AR) -M < ar.mak

#==================================================================
#                          modules
#==================================================================
.PHONY: $(objects) $(objects_clean) $(objects_install) $(objects_uninstall)

prepare:
	make -C graphic prepare
	make -C disp prepare
	make -C pq prepare

$(objects): | prepare
	make -C $@ all

$(objects_clean):
	make -C $(patsubst %_clean,%,$@) clean

$(objects_install):
	make -C $(patsubst %_clean,%,$@) install

$(objects_uninstall):
	make -C $(patsubst %_clean,%,$@) uninstall
