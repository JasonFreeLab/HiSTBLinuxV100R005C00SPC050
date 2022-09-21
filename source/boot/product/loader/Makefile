ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#   variable
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

objects := api
SUBLIBS += api/libapi.a

LOADER_API_DIR := $(SOURCE_DIR)/boot/product/loader/api

ifeq ($(CFG_HI_ADVCA_SUPPORT), y)
ifeq ($(CFG_HI_ADVCA_TYPE), VERIMATRIX)
    ifeq ($(CFG_HI_ADVCA_VMX_3RD_SIGN),y)
        objects += api/src/harden/vmx_advance/3rd_loader_verify_lib
        SUBLIBS += api/src/harden/vmx_advance/3rd_loader_verify_lib/libhi_vmx_loader_verify.a
    else
        EXISTED := $(shell if [ -f $(LOADER_API_DIR)/src/harden/vmx_advance/vmx_loader_verify_lib/libhi_vmx_loader_verify.a ]; then echo "exist"; else echo "notexist"; fi;)
        ifneq (exist, $(EXISTED))
            objects += api/src/harden/vmx_advance/vmx_loader_verify_lib
        endif
        SUBLIBS += api/src/harden/vmx_advance/vmx_loader_verify_lib/libhi_vmx_loader_verify.a
    endif
endif

ifeq ($(CFG_HI_ADVCA_TYPE), NAGRA)
endif

else
objects += schedule
SUBLIBS += schedule/libschedule.a
endif

ifeq ($(CFG_HI_LOADER_BOOTLOADER),y)
objects += app
SUBLIBS += app/libapp.a
endif

ifeq ($(CFG_HI_MINIBOOT_SUPPORT),y)
CFLAGS += -DHI_LOADER_RUNNING_ENVIRONMENT_MINIBOOT
CFLAGS += -DHI_LOADER_RUNNING_ENVIRONMENT_BOOT
else ifeq ($(CFG_HI_UBOOT_SUPPORT),y)
CFLAGS += -DHI_LOADER_RUNNING_ENVIRONMENT_UBOOT
CFLAGS += -DHI_LOADER_RUNNING_ENVIRONMENT_BOOT
endif

objects_clean := $(addsuffix _clean,$(objects))

LIBS := libloader.a

$(LIBS): $(objects)
	$(AT)rm -rf $@
	$(AT)rm -rf ar.mak
	$(AT)echo "CREATE $@" >> ar.mak
	$(AT)$(foreach sublib,$(SUBLIBS),echo "ADDLIB $(sublib)" >> ar.mak;)
	$(AT)echo "SAVE" >> ar.mak
	$(AT)echo "END" >> ar.mak
	$(AT)$(AR) -M < ar.mak

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#   rules
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
.PHONY: all clean

all:
	cd $(COMPONENT_DIR)/loader/api && find ./ -name "*.[ch]" | xargs cp -rf --parents -t $(CURDIR)/api
	make $(LIBS)

clean: $(objects_clean)
	$(AT)rm -fr ar.mak $(LIBS)

#==================================================================
#                          modules
#==================================================================
.PHONY: $(objects) $(objects_clean)

$(objects):
	make -C $@ all

$(objects_clean):
	make -C $(patsubst %_clean,%,$@) clean

