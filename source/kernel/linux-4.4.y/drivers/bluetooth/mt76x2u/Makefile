CFILES := \
	btmtk_usb_main.c \
	btmtk_usb_dbgfs.c \
	btmtk_usb_fifo.c

EXTRA_CFLAGS := -DMT7632 -DMT7662 -g

MOD_NAME = btmtk_usb

obj-$(CONFIG_BT_MT76X2U) += $(MOD_NAME).o
$(MOD_NAME)-objs := $(CFILES:.c=.o)
