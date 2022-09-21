#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(shell cd $(CURDIR)/../../.. && /bin/pwd)

include $(SDK_DIR)/base.mak
endif

ifeq ($(CFG_HI_ADVCA_SUPPORT), y)
ifeq ($(CFG_HI_ADVCA_TYPE), VERIMATRIX)
	ifeq ($(CFG_HI_ADVCA_VMX_3RD_SIGN),y)
		VMX_SRC_DIR := api/src/harden/vmx_advance/3rd_loader_verify_lib
	else
		VMX_SRC_DIR := api/src/harden/vmx_advance/vmx_loader_verify_lib
	endif
	
	ifeq ($(VMX_SRC_DIR)/libhi_vmx_loader_verify.a, $(wildcard $(VMX_SRC_DIR)/libhi_vmx_loader_verify.a))
		VMX_LIB_EXIST := y
	else
		VMX_LIB_EXIST := n
	endif
endif
endif

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean

all:
	$(AT)make -C api all
ifeq ($(CFG_HI_LOADER_APPLOADER),y)
ifeq ($(CFG_HI_ADVCA_SUPPORT), y)
ifeq ($(CFG_HI_ADVCA_TYPE), VERIMATRIX)
ifneq ($(VMX_LIB_EXIST),y)
	$(AT)make -C $(VMX_SRC_DIR)
endif
endif
endif
	$(AT)make -C app all
endif

clean:
	$(AT)make -C api clean
ifeq ($(CFG_HI_LOADER_APPLOADER),y)
	$(AT)make -C app clean
ifeq ($(CFG_HI_ADVCA_TYPE), VERIMATRIX)
ifeq ($(CFG_HI_ADVCA_VMX_3RD_SIGN),y)
	$(AT)make -C api/src/harden/vmx_advance/3rd_loader_verify_lib clean
else
	$(AT)make -C api/src/harden/vmx_advance/vmx_loader_verify_lib clean
endif
endif
endif

