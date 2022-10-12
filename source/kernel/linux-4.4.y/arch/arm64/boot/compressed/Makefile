################################################################################
#    Copyright (C) 2014 Hisilicon STB Development Dept
#    All rights reserved.
#####
#    Create by Cai Zhiyong
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#    http://www.apache.org/licenses/LICENSE-2.0
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#
################################################################################

################################################################################

KERNEL_OUT_DIR := $(LINUX_DIR)

TOPDIR     := .
CUR_DIR	   := ${KERNEL_SRC_DIR}/arch/arm64/boot/compressed/
DEFTARGET  := $(MAKECMDGOALS)
PLATFORM   :=
PHONYS     :=
TEMPS      :=
CC         := $(CROSS_COMPILE)gcc
AR         := $(CROSS_COMPILE)ar
LD         := $(CROSS_COMPILE)ld
OBJCOPY    := $(CROSS_COMPILE)objcopy
OBJDUMP    := $(CROSS_COMPILE)objdump
NM         := $(CROSS_COMPILE)nm
RM         := rm

ARFLAGS    := rcs
LDFLAGS    :=
CFLAGS     := -Wall -nostdinc -isystem $(TOPDIR) \
		-Os -fno-strict-aliasing \
		-fno-common -fno-builtin -ffreestanding \
		-pipe

# -march=$(ARCH)
#	-fno-common -fno-builtin -isystem -ffreestanding \

#-DCONFIG_SYS_DCACHE_OFF -DCONFIG_SYS_ICACHE_OFF -DCONFIG_SPL_BUILD
CFLAGS	   += -DCONFIG_ARM64 -D__KERNEL__  -DCONFIG_PHYS_64BIT
ASFLAGS    := $(CFLAGS)
ASFLAGS    += -D__ASSEMBLY__

#this for image_data.S look for the Image file
ASFLAGS    += -I$(KERNEL_OUT_DIR)/arch/arm64/boot/

################################################################################
SRCDIR           :=
COMPRESS_DIR     := compress/
LIB              := lib/

OBJS_OUTPUT_DIR	 := $(KERNEL_OUT_DIR)/arch/arm64/boot/compressed/

LIBS  := $(addsuffix $(BUILDOBJ).o,$(addprefix $(TOPDIR)/,$(LIBS)))
ZLIBS := $(addsuffix $(BUILDOBJ).o,$(addprefix $(TOPDIR)/,$(ZLIBS)))

TOOLPATH    := tools
SHELL       := /bin/sh
MKIMAGE     := mkimage
EL_ADDR		:= 0x2000000
################################################################################
UIMAGE_ARCH          := arm64
UIMAGE_COMPRESSION   := none
UIMAGE_TYPE          := kernel
UIMAGE_LOADADDR      := ${EL_ADDR}
UIMAGE_ENTRYADDR     := ${EL_ADDR}
UIMAGE_OUT           := $(KERNEL_OUT_DIR)/arch/arm64/boot/uImage
IMAGE_IN            := Image
TEXTBASE             := ${EL_ADDR}

################################################################################

COBJS := start.o uart_early_put.o image_data.o init.o memmove.o uart_p101x.o tlb.o cache.o cache_v8.o

################################################################################
#/home/lgzhuan/sdksd/Code/tools/linux/utils/bin/mkimage -A arm64 -O linux -C none -T kernel -a 0x2000000 -e 0x00080000 -n Linux-4.4.35_hi3796mv200 -d arch/arm64/boot/Image arch/arm64/boot/uImage
$(UIMAGE_OUT): image.bin
	@echo "Building modules, stage 2."
	@cd ${OBJS_OUTPUT_DIR} && dd if=$< of=$<.dd ibs=4096 conv=sync && mv $<.dd $<
	@rm -f $(UIMAGE_OUT)
	@cd ${OBJS_OUTPUT_DIR} && $(MKIMAGE) -A $(UIMAGE_ARCH) -O linux \
		   -C $(UIMAGE_COMPRESSION) \
		   -T $(UIMAGE_TYPE) \
		   -a $(UIMAGE_LOADADDR) -e $(UIMAGE_ENTRYADDR) \
		   -n $(UIMAGE_NAME) -d $< $(UIMAGE_OUT)
	@cd ${OBJS_OUTPUT_DIR} && cat $(KERNEL_OUT_DIR)/arch/arm64/boot/dts/hisilicon/hi*.dtb >>$(UIMAGE_OUT)
	@echo "uImage $@ is ready"

image.bin: image.elf
	@cd ${OBJS_OUTPUT_DIR} && $(OBJCOPY) --gap-fill=0xff -O binary $< $@

image.elf: $(COBJS)
	@cd ${OBJS_OUTPUT_DIR} && $(LD) -Bstatic -T ${CUR_DIR}/vmlinux.lds -Ttext $(TEXTBASE) \
		$(COBJS) -Map image.map -o $@

$(COBJS):
################################################################################
%.o: %.c
	$(CC) $(CFLAGS) -Wall -Wstrict-prototypes \
		-fno-stack-protector -o ${OBJS_OUTPUT_DIR}/$@ $< -c

%.o: %.S
	$(CC) $(ASFLAGS) -o ${OBJS_OUTPUT_DIR}/$@ $< -c
################################################################################

clean:
	@rm -f ${OBJS_OUTPUT_DIR}/*
################################################################################
