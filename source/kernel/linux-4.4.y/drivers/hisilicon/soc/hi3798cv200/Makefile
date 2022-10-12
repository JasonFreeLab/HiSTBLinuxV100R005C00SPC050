obj-y					+= irq_affinity_hi3798c2x.o
obj-y					+= cpu-hi3798cv200.o
obj-y					+= hiahci-phy.o
ifdef CONFIG_ARM
ifndef CONFIG_ARM_PSCI_FW
obj-$(CONFIG_PM)			+= hipm_sleep.o
obj-$(CONFIG_PM)			+= hipm.o
endif
endif
obj-$(CONFIG_CPU_IDLE_HI3798CV2X)	+= cpuidle-hi3798cv2x.o pm-hi3798c2x.o
