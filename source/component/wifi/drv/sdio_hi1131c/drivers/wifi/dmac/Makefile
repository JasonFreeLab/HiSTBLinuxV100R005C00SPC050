#
# Main Makefile for building the corresponding module functioned target
#
#
#
# set the coorespondig path to the project root directory
# DO NOT change the variable value, or else if YOU know what you are changing
export ROOT_DEPTH_DMAC=../../..
export DRV_TEST_DIR=$(ROOT_DEPTH_DMAC)/drivers/wifi/dmac/dmac_verify
export DMAC_RAM_DIR=$(ROOT_DEPTH_DMAC)/drivers/wifi/dmac/dmac_ram
export DMAC_REKEY_DIR=$(ROOT_DEPTH_DMAC)/drivers/wifi/dmac/dmac_rekey
export KERNEL_PATH_DMAC=$(PWD)/$(ROOT_DEPTH_DMAC)/$(KERNEL_PATH)

# set the default make target
# NOTICE: make sure that the target name here is same with the module
# build target defined at the bottom
.PHONY:module_build

# include the config file to setup the compiling environment
include $(PWD)/$(ROOT_DEPTH_DMAC)/build/1151_host_wifi/env.config

# set the module objects files
obj-m :=dmac.o
dmac-objs := dmac_main.o dmac_mgmt_classifier.o dmac_psm_ap.o dmac_rx_data.o dmac_tid.o dmac_tx_bss_comm.o dmac_11w.o dmac_tx_complete.o dmac_user.o dmac_vap.o mac_device.o mac_frame.o mac_user.o mac_vap.o dmac_data_acq.o\
             mac_ie.o dmac_uapsd.o dmac_mgmt_bss_comm.o dmac_beacon.o dmac_alg.o dmac_blockack.o mac_resource.o dmac_mgmt_ap.o dmac_mgmt_sta.o dmac_wep.o dmac_11i.o mac_regdomain.o dmac_scan.o dmac_dfx.o dmac_device.o dmac_resource.o\
	     dmac_reset.o dmac_config.o dmac_stat.o dmac_fcs.o dmac_acs.o dmac_chan_mgmt.o dmac_user_track.o dmac_rx_filter.o dmac_txopps.o dmac_dft.o dmac_ap_pm.o mac_pm.o dmac_hcc_adapt.o mac_board.o mac_data.o dmac_arp_offload.o 
dmac-dump-objs := $(dmac-objs)

dmac-objs :=  $(DMAC_RAM_DIR)\dmac_wow_ram.o
dmac-dump-objs := $(dmac-objs)

dmac-objs += $(DRV_TEST_DIR)/dmac_test_sch.o
dmac-objs += $(DRV_TEST_DIR)/dmac_test_main.o \
	     $(DRV_TEST_DIR)/dmac_lpm_test.o \
 	     $(DRV_TEST_DIR)/dmac_frame_filter_test.o \
		 $(DRV_TEST_DIR)/dmac_wmm_test.o  \
		 $(DRV_TEST_DIR)/dmac_scan_test.o \
		 $(DRV_TEST_DIR)/dmac_acs_test.o
dmac_dump_objs += dmac_test_main.o dmac_lpm_test.o dmac_frame_filter_test.o dmac_test_sch.o dmac_wmm_test.o

dmac-objs += $(DMAC_REKEY_DIR)/dmac_crypt_aes.o \
        $(DMAC_REKEY_DIR)/dmac_crypt_md5.o \
        $(DMAC_REKEY_DIR)/dmac_crypt_sha1.o \
        $(DMAC_REKEY_DIR)/dmac_crypt_tkip.o \
        $(DMAC_REKEY_DIR)/dmac_rekey_offload.o
dmac_dump_objs += dmac_crypt_aes.o dmac_crypt_md5.o dmac_crypt_sha1.o dmac_crypt_tkip.o dmac_rekey_offload.o

# set the feature options
include $(PWD)/$(ROOT_DEPTH_DMAC)/build/1151_host_wifi/caps.config

# for example:
# ifeq ($(SUPPORT_VIDEO_OPTIMIZE),1)
#	alg-objs += alg_video.o
# endif

# set the module name
MODULE_NAME=$(subst .o,.ko,$(obj-m))

BACKUP_OBJFILE_FOLDER=$(strip $(subst .o,,$(obj-m)))_objfile

BACKUP_OBJFILE_DIR=$(PWD)/$(BACKUP_OBJFILE_FOLDER)

OBJDUMP_FILE=$(subst .o,.objdump,$(obj-m))
OBJDUMP_TXT_FILE=$(subst .o,.txt,$(obj-m))

# module's elf header file name 
MODULE_ELF_HEADER_FILE=$(subst .o,.elf_header,$(obj-m))

# build the module
all:
	@echo Building module $(MODULE_NAME)
	make -j $(NJOBS) -C $(KERNEL_PATH_DMAC) M=$(PWD) modules
	$(shell [ -d $(IMAGE_PATH_KO) ] || mkdir -p $(IMAGE_PATH_KO))
	cp ./*.ko $(IMAGE_PATH_KO) -fv
	$(STRIP) $(IMAGE_PATH_KO)/*.ko --strip-unneeded
	make backup_objfile
	make create_objdump
	make create_objdump_txt
	make create_original_ko
	make create_readelf_header

# clean the module
clean:
	@echo cleaning module $(MODULE_NAME)
	-find . -type f -name "*.o" -exec rm -f {} \;
	-find . -type f -name "*.o.uu" -exec rm -f {} \;
	-find . -type f -name "*.cmd" -exec rm -f {} \;
	-find . -type f -name "*.ko" -exec rm -f {} \;
	-find . -type f -name "*.out" -exec rm -f {} \;
	-find . -type f -name "*.order" -exec rm -f {} \;
	-find . -type f -name "*.mod.c" -exec rm -f {} \;
	-find . -type f -name "*.symvers" -exec rm -f {} \;
	rm .tmp_versions -frv
	rm -rf $(IMAGE_PATH_KO)/*.ko

install:
	@echo install the module to the root-file system

backup_objfile:
	@echo backup the temp files
	mkdir -p $(BACKUP_OBJFILE_FOLDER)
	-find . -type f -name "*.o" -exec mv -f {} $(BACKUP_OBJFILE_FOLDER) \;
	-find . -type f -name "*.o.uu" -exec mv -f {} $(BACKUP_OBJFILE_FOLDER) \;
	-find . -type f -name "*.cmd" -exec mv -f {} $(BACKUP_OBJFILE_FOLDER) \;
	-find . -type f -name "*.ko" -exec mv -f {} $(BACKUP_OBJFILE_FOLDER) \;
	-find . -type f -name "*.out" -exec mv -f {} $(BACKUP_OBJFILE_FOLDER) \;
	-find . -type f -name "*.order" -exec mv -f {} $(BACKUP_OBJFILE_FOLDER) \;
	-find . -type f -name "*.mod.c" -exec mv -f {} $(BACKUP_OBJFILE_FOLDER) \;
	-find . -type f -name "*.symvers" -exec mv -f {} $(BACKUP_OBJFILE_FOLDER) \;
	-find . -type f -name "*.c.swp" -exec mv -f {} $(BACKUP_OBJFILE_FOLDER) \;
	cp -fr .tmp_versions $(BACKUP_OBJFILE_FOLDER)
	rm .tmp_versions -frv
	-find $(DRV_TEST_DIR)/ -type f -name "*.o" -exec mv -f {} $(BACKUP_OBJFILE_FOLDER) \;

create_objdump:
ifeq ($(OBJDUMP_ENABLE),y)
	@echo start to create_objdump file
	$(shell [ -d $(OBJDUMP_PATH) ] ||(mkdir -p $(OBJDUMP_PATH)))
	$(foreach OBJFILE, $(dmac-dump-objs), $(OBJDUMP) -S $(BACKUP_OBJFILE_DIR)/$(OBJFILE) >> $(BACKUP_OBJFILE_DIR)/$(OBJDUMP_FILE);)
	@mv -f $(BACKUP_OBJFILE_DIR)/*.objdump $(OBJDUMP_PATH)	
endif

create_objdump_txt:
	$(shell [ -d $(OBJDUMP_TXT_PATH) ] ||(mkdir -p $(OBJDUMP_TXT_PATH)))
	$(foreach OBJFILE, $(obj-m),$(OBJDUMP) -t $(BACKUP_OBJFILE_DIR)/$(obj-m) >> $(BACKUP_OBJFILE_DIR)/$(OBJDUMP_TXT_FILE);)
	@mv -f $(BACKUP_OBJFILE_DIR)/$(OBJDUMP_TXT_FILE) $(OBJDUMP_TXT_PATH)
create_original_ko:
	$(shell [ -d $(ORIGINAL_KO_PATH) ] ||(mkdir -p $(ORIGINAL_KO_PATH)))
	@mv -f $(BACKUP_OBJFILE_DIR)/*.ko $(ORIGINAL_KO_PATH)
	
create_readelf_header:
	$(shell [ -d $(OBJDUMP_TXT_PATH) ] ||(mkdir -p $(OBJDUMP_TXT_PATH)))
	@echo $(MODULE_NAME) > $(OBJDUMP_TXT_PATH)/$(MODULE_ELF_HEADER_FILE)
	@$(READELF) -S $(ORIGINAL_KO_PATH)/$(MODULE_NAME) >> $(OBJDUMP_TXT_PATH)/$(MODULE_ELF_HEADER_FILE)
	
