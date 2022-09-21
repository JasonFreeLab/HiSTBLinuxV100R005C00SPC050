ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

ifeq ($(CFG_HI_MINIBOOT_SUPPORT),y)
CFLAGS += -DHI_LOADER_RUNNING_ENVIRONMENT_MINIBOOT
CFLAGS += -DHI_LOADER_RUNNING_ENVIRONMENT_BOOT
CFLAGS += -I$(BOOT_DIR)/miniboot/include
else ifeq ($(CFG_HI_UBOOT_SUPPORT),y)
CFLAGS += -DHI_LOADER_RUNNING_ENVIRONMENT_UBOOT
CFLAGS += -DHI_LOADER_RUNNING_ENVIRONMENT_BOOT
CFLAGS += -I$(BOOT_DIR)/fastboot/include
else
endif

CFLAGS += -I$(BOOT_DIR)/product/driver/include
CFLAGS += -I$(COMPONENT_DIR)/loader/api/include
CFLAGS += -I$(COMPONENT_DIR)/loader/api/src

ifeq ($(CFG_HI_BOOTLOADER_SUPPORT),y)
CFLAGS += -DHI_BOOTLOADER_SUPPORT
endif

ifeq ($(CFG_HI_APPLOADER_SUPPORT),y)
CFLAGS += -DHI_APPLOADER_SUPPORT
endif

ifeq ($(CFG_HI_BUILD_WITH_KEYLED),y)
CFLAGS += -DHI_BUILD_WITH_KEYLED
endif

SCHEDULELIB := libschedule.a
SCHEDULEOBJ := schedule.o loader_verify.o


all: $(SCHEDULELIB)

install: $(SCHEDULEOBJ)

$(SCHEDULELIB): $(SCHEDULEOBJ)
	$(AT)$(AR) -rc $@ $^

%.o: %.c
	$(CC) -c  $^ $(CFLAGS)

clean:
	rm -f *.o
	rm -f *.a

