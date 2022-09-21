#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../.. && /bin/pwd)

include $(SDK_DIR)/base.mak
endif

.PHONY: all clean

all:

ifneq ($(findstring vmx_ultra, $(CFG_HI_OUT_DIR)),)
	@echo "make ultra sample"
	make -C $(CURDIR)/hi3798mv200_m3/protobuf all
	make -C $(CURDIR)/hi3798mv200_m3/provision all
	make -C $(CURDIR)/hi3798mv200_m3/sample mksamplecommon_lib
	make -C $(CURDIR)/hi3798mv200_m3/sample sample_tvp_play
	./hi3798mv200_m3/build.sh
else
	@echo "make master sample"
	make -C $(CURDIR)/protobuf all
	make -C $(CURDIR)/provision all
	make -C $(CURDIR)/sample mksamplecommon_lib
	make -C $(CURDIR)/sample sample_tvp_play
	./build.sh
endif

clean:
	make -C $(CURDIR)/protobuf clean
	make -C $(CURDIR)/provision clean
	make -C $(CURDIR)/sample clean
	rm -rf $(CURDIR)/GoogleTest/out
