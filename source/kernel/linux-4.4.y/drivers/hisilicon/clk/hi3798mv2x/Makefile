ifeq ($(CONFIG_CLK_HI3798MV300),y)
obj-y	+= clk-hi3798mv300.o
else
obj-y	+= clk-hi3798mv200.o
endif
obj-y	+= clk-hiusb2.o
obj-y	+= clk-hiusb3.o
obj-y	+= clk-higpu.o
obj-y	+= clk-hipcie.o
obj-y	+= clk-hiahci.o
obj-y	+= clk-hifmc100.o
obj-y	+= clk-hiir.o

ccflags-y += -I./drivers/hisilicon/clk
