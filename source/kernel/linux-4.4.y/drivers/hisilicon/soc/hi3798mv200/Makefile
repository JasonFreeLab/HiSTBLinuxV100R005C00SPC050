obj-y += cpu-hi3798mv200.o
obj-y += hiahci-phy.o
ifndef CONFIG_TEE_VMX_ULTRA
ifdef CONFIG_ARM
obj-$(CONFIG_PM) += hipm_sleep.o
obj-$(CONFIG_PM) += hipm.o
endif
endif
obj-$(CONFIG_CPU_IDLE_HI3798MV2X) 	+= cpuidle-hi3798mv2x.o pm-hi3798mv2x.o

