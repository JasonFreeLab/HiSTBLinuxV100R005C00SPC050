###########################################################
# platform definition
###########################################################

CROSS_COMPILE1 ?= $(ROOT)/../../core/trustedcore/toolchains/arm-eabi-4.8/bin/arm-eabi-
CC1        =$(CROSS_COMPILE1)gcc
LD1        =$(CROSS_COMPILE1)ld
AR1        =$(CROSS_COMPILE1)ar
OBJCOPY1   =$(CROSS_COMPILE1)objcopy

RM         =-rm -rf
MKDIR      =-mkdir -p
COPY       =cp


ALL_OBJ = $(LOCAL_SRC_FILES)

LOCAL_CFLAGS += -O2 -fstrict-aliasing -funswitch-loops -fno-short-enums -W -Wall -mfloat-abi=softfp -mfpu=neon -fno-omit-frame-pointer -fstack-protector-all -Wstack-protector -MD

LOCAL_CFLAGS += -Werror -Wall

LOCAL_C_INCLUDES += \
    -I$(ROOT)/include/gp

ELF_MAIN_ENTRY_PATH = $(ROOT)/lib/elf_main_entry.o
TA_LINK_SCRIPT = $(ROOT)/script/ta_link.ld
TRUSTEDCORE_PACK_TA_SCRIPT = $(ROOT)/script/pack_ta.py

LOCAL_OUT = $(ROOT)/out
ALL_OUT_OBJ = $(foreach VAR,$(ALL_OBJ),$(addprefix $(LOCAL_OUT)/,$(VAR)))

LOCAL_MODULE := $(LOCAL_OUT)/$(MODULE_NAME)

CFLAGS += $(LOCAL_CFLAGS) $(LOCAL_C_INCLUDES)
LDFLAGS += -r -d --strip-debug --whole-archive -T $(TA_LINK_SCRIPT) $(ELF_MAIN_ENTRY_PATH) --no-whole-archive
MANIFEST_FILE := $(ROOT)/manifest.txt

##########################################################
# build
##########################################################
.PHONY : all prepare clean
all: $(ALL_OBJ)
	@echo $(ALL_OBJ)
	$(LD1) $(LDFLAGS) -o $(LOCAL_MODULE) $(ALL_OUT_OBJ) `$(CC1) -mthumb-interwork -print-libgcc-file-name`
	test ! -f $(MANIFEST_FILE) || $(TRUSTEDCORE_PACK_TA_SCRIPT) $(LOCAL_MODULE) $(MANIFEST_FILE)
	@$(RM) $(LOCAL_OUT)/*.o $(LOCAL_OUT)/*.d 
	@echo "Make $(LOCAL_MODULE) Success!"

$(ALL_OBJ):prepare

prepare:
	$(MKDIR) $(foreach VAR,$(ALL_OUT_OBJ),$(dir $(VAR)))

clean:
	@$(RM) $(LOCAL_OUT)/* 

%.o : %.c | prepare
	$(CC1) -c $(CFLAGS) $< -o $(LOCAL_OUT)/$@

%.o : %.S | prepare
	$(CC1) -c $(CFLAGS) $< -o $(LOCAL_OUT)/$@

%.o : %.s | prepare
	$(CC1) -c $(CFLAGS) $< -o $(LOCAL_OUT)/$@

