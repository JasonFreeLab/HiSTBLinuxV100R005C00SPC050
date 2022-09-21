#=======================================
#   export varibale
#=======================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(shell cd $(CURDIR)/../../../.. && /bin/pwd)

include $(SDK_DIR)/base.mak
endif

#=======================================
#   local varibale
#=======================================
SRCS := unf_payloadcipher.c mpi_plcipher.c

include $(SDK_DIR)/hi_rules.mak
