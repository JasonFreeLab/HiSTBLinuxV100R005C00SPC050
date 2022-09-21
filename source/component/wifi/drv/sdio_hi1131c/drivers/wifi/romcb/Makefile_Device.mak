#
# Main Makefile for building the corresponding module functioned target
#
#
#
# set the coorespondig path to the project root directory
# DO NOT change the variable value, or else if YOU know what you are changing
export ROOT_DEPTH_ROMCB=../../..
export KERNEL_PATH_ROMCB=$(PWD)/$(ROOT_DEPTH_ROMCB)/$(KERNEL_PATH)

ROMCB_SCRDIR=$(WIFI_SRCDIR)\ROMCB
# set the default make target
# NOTICE: make sure that the target name here is same with the module
# build target defined at the bottom
.PHONY:module_build

# include the config file to setup the compiling environment
#include $(PWD)/$(ROOT_DEPTH)/Script/Build/1151_Host_WiFi/env.config

# set the module objects files
obj-m :=romcb.o
romcb-objs := $(ROMCB_SCRDIR)\hal_romcb.o $(ROMCB_SCRDIR)\dmac_romcb.o
romcb-dump-objs += $(romcb-objs)

# set the feature options
#include $(PWD)/$(ROOT_DEPTH)/Script/Build/1151_Host_WiFi/caps.config
# module's elf header file name
# module's elf header file name
# module's elf header file name
# module's elf header file name
# module's elf header file name
# module's elf header file name
# module's elf header file name
# module's elf header file name
# module's elf header file name
# module's elf header file name
# module's elf header file name
# module's elf header file name
# module's elf header file name
# module's elf header file name
# module's elf header file name
# module's elf header file name
# module's elf header file name
# module's elf header file name
# module's elf header file name
# module's elf header file name
# module's elf header file name
# module's elf header file name
# module's elf header file name
# module's elf header file name
# module's elf header file name
# module's elf header file name
# module's elf header file name
# module's elf header file name
# module's elf header file name
# module's elf header file name
# module's elf header file name
# module's elf header file name
# module's elf header file name
# module's elf header file name

# set the module name
MODULE_NAME=$(subst .o,.ko,$(obj-m))

BACKUP_OBJFILE_FOLDER=$(strip $(subst .o,,$(obj-m)))_objfile

BACKUP_OBJFILE_DIR=$(PWD)/$(BACKUP_OBJFILE_FOLDER)

OBJDUMP_FILE=$(subst .o,.objdump,$(obj-m))
OBJDUMP_TXT_FILE=$(subst .o,.txt,$(obj-m))

# module's elf header file name
MODULE_ELF_HEADER_FILE=$(subst .o,.elf_header,$(obj-m))




