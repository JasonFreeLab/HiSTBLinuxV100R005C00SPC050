#+++++++++++++++++++++++++++++++++++++
menu "PowerManagement Config"
#+++++++++++++++++++++++++++++++++++++

config HI_DVFS_CPU_SUPPORT
    bool "CPU DVFS Support"
    default y

config HI_AVS_SUPPORT
    bool "AVS Support"
    depends on HI_DVFS_CPU_SUPPORT
    default y

# for power up standby
config HI_PM_POWERUP_MODE1_SUPPORT
    bool "Power Up Standby Mode1 Support"
    default n

menuconfig HI_TEMP_CTRL_CONFIG
    bool "Temperature Control"
    depends on HI_DVFS_CPU_SUPPORT
    default n

config HI_TEMP_CTRL_DOWN_THRESHOLD
    depends on HI_TEMP_CTRL_CONFIG
    hex "Downclock: The CPU will be downclocked to reduce its power"
    default 0x73

config HI_TEMP_CTRL_UP_THRESHOLD
    depends on HI_TEMP_CTRL_CONFIG
    hex "Switch on: Above the temperature, Control loop starts operating"
    default 0x64

config HI_TEMP_CTRL_REBOOT_THRESHOLD
    depends on HI_TEMP_CTRL_CONFIG
    hex "Shutdown: Shut the system down to protect your CPU"
    default 0x7d

config HI_PM_START_MCU_RUNNING
    bool "Start Mcu When Power Up"
    default n
#+++++++++++++++++++++++++++++++++++++
endmenu
#+++++++++++++++++++++++++++++++++++++
