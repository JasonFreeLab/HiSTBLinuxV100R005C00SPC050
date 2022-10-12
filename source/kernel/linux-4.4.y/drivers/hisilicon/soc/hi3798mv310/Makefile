obj-y += cpu-hi3798mv310.o
ifndef CONFIG_TEE
ifdef CONFIG_ARM
obj-$(CONFIG_PM) += hipm_sleep.o
obj-$(CONFIG_PM) += hipm.o
endif
endif
obj-$(CONFIG_CPU_IDLE_HI3798MV310) 	+= cpuidle-hi3798mv310.o pm-hi3798mv310.o

