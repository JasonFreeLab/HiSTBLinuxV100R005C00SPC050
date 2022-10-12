
obj-y					+= hifmc100_host.o
obj-$(CONFIG_MTD_HIFMC100_SPINOR)	+= hifmc100_spinor.o
ifneq ($(CONFIG_MTD_HIFMC100_NAND)_$(CONFIG_MTD_HIFMC100_SPINAND),_)
obj-y					+= hifmc100_xnand.o
endif

obj-$(CONFIG_ARCH_S40)			+= hifmc100_clock_hi3716mv410.o
obj-$(CONFIG_ARCH_HI3716MV420N)		+= hifmc100_clock_hi3716mv410.o
obj-$(CONFIG_ARCH_HI3798CV2X)		+= hifmc100_clock_hi3798cv2x.o
obj-$(CONFIG_ARCH_HI3798MV2X)		+= hifmc100_clock_hi3798mv2x.o
obj-$(CONFIG_ARCH_HI3798MV310)		+= hifmc100_clock_hi3798mv310.o
obj-$(CONFIG_ARCH_HI3796MV2X)		+= hifmc100_clock_hi3796mv2x.o

ccflags-y += -I./drivers/mtd/hisilicon
