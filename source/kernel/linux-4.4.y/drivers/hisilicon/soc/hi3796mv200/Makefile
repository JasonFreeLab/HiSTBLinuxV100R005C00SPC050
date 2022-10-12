ccflags-y += -I$(srctree)

obj-y += cpu-hi3796mv200.o
obj-y += hiahci-phy.o
obj-y += hiahci-phy0.o
obj-y += hiplat_common.o
obj-$(CONFIG_PM) += hipm_check.o
obj-$(CONFIG_PM) += bootreg_resume.o
ifdef CONFIG_ARM
ifdef CONFIG_ARM_PSCI_FW
obj-$(CONFIG_PM) += hipm_aarch64.o
else
obj-$(CONFIG_PM) += hipm_sleep.o
obj-$(CONFIG_PM) += hipm.o
endif
else
obj-$(CONFIG_PM) += hipm_aarch64.o
endif
obj-$(CONFIG_CPU_IDLE_HI3796MV200) 	+= cpuidle-hi3796mv200.o pm-hi3796mv200.o
