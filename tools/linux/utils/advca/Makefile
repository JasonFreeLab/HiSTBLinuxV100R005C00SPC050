################################################################################
#    x86/src/mkbootargs
#    Create By
#    2011.01.16
################################################################################
# parameter
PREFIX         ?= $(shell pwd)

################################################################################
#
#  options below should be redefined here, don't use definitions in Makefile
#  in SDK top dir.
#
CC=gcc -static
OBJDUMP=objdump
HOST=
CPP=
LD=
NM=

################################################################################

TARGET          = replace_Ext_Key_Params
################################################################################

all:
	@mkdir -p $(PREFIX)
	$(CC) -o $(PREFIX)/$(TARGET) ExtKey_Param_CreateAndReplace/replace_Ext_Key_Params.c


################################################################################

clean:
	@rm $(PREFIX)/$(TARGET) -rvf
	@rm $(PREFIX)/*.bin -rvf

distclean: clean

################################################################################
.PHONY: clean distclean all
################################################################################
