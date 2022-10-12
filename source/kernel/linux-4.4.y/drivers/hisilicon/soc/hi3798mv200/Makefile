obj-y += cpu-hi3798mv200.o
obj-y += hiahci-phy.o
ifdef CONFIG_ARM
# if we have the PSCI_FW, pm job is done inside the driver/firmware/psic.c
ifndef CONFIG_ARM_PSCI_FW
obj-$(CONFIG_PM) += hipm_sleep.o
obj-$(CONFIG_PM) += hipm.o
endif
endif
obj-$(CONFIG_CPU_IDLE_HI3798MV2X) 	+= cpuidle-hi3798mv2x.o pm-hi3798mv2x.o

