.PHONY:all clean

ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(CURDIR)/../../../..
include $(SDK_DIR)/cfg.mak
include $(SDK_DIR)/base.mak
endif

SAMPLE_DIR=$(shell pwd)


LIB += -Wl,--start-group -lpthread -ldl -lhi_common -Wl,--end-group

SDK_LIB_PATH = -L$(HI_SHARED_LIB_DIR)
SDK_INCLUDE_PATH = -I$(HI_INCLUDE_DIR)

CFLAGS  = -O2 -Wall $(SDK_INCLUDE_PATH)
LDFLAGS = $(SDK_LIB_PATH) $(LIB)

ifeq ($(CFG_HI_SMMU_SUPPORT),y)
CFLAGS += -DBMPGEM_SMMU_SUPPORT
endif

SRC = $(wildcard *.c)

APP = bmpGen

all: $(APP)

$(APP):$(SRC)
	$(QUIET) $(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
clean:
	rm -rf $(APP)
	rm -rf *.o
