#!/bin/sh

################### SCSI disk #################################################
#DEVTYPE=partition 
#DEVPATH=/devices/platform/ahci.0/ata1/host0/target0:0:0/0:0:0:0/block/sdb/sdb2 
#SUBSYSTEM=block 
#SEQNUM=800 
#UDEVD_EVENT=1 
#ACTION=remove 
#DEVNAME=/dev/sdb1 
#DEVTYPE=partition 
#DEVPATH=/devices/platform/ahci.0/ata1/host0/target0:0:0/0:0:0:0/block/sdb/sdb1 
#SUBSYSTEM=block 
#SEQNUM=801 
#UDEVD_EVENT=1 
#ACTION=remove 
#DEVNAME=/dev/sdb 
#DEVTYPE=disk 
#DEVPATH=/devices/platform/ahci.0/ata1/host0/target0:0:0/0:0:0:0/block/sdb 
#SUBSYSTEM=block 
#SEQNUM=803 
#UDEVD_EVENT=1 

################### USB disk #################################################
#
# Block device event:
#
# ACTION=add 
# DEVNAME=/dev/sda 
# DEVTYPE=disk 
# DEVPATH=/devices/platform/hiusb-ehci.0/usb1/1-2/1-2.1/1-2.1:1.0/host8/target8:0:0/8:0:0:0/block/sda 
# SUBSYSTEM=block 
# SEQNUM=544 
# UDEVD_EVENT=1 
# 
# ACTION=add 
# DEVNAME=/dev/sda1 
# DEVTYPE=partition 
# DEVPATH=/devices/platform/hiusb-ehci.0/usb1/1-2/1-2.1/1-2.1:1.0/host8/target8:0:0/8:0:0:0/block/sda/sda1 
# SUBSYSTEM=block 
# SEQNUM=545 
# UDEVD_EVENT=1 
#
# Use command "hdparm -z /dev/sda" to reread partition table
#

################################################################################
# new_name
remove_disk ()
{
	local ORG_NAME="/home/stb"$1
	
	#Remove the /home/stb/dev/sd* in advca
	rm -f ${ORG_NAME}
}
################################################################################
hotplug_usb ()
{
	if [ ss"${SUBSYSTEM}" != ss"block" ]; then
		return 1
	fi

	case "${ACTION}" in
	"remove" )
		remove_disk "${DEVNAME}"
	;;
	* )
		echo "ACTION:${ACTION}" > ${CONSOLE}
	;;
	esac

	return 0
}

hotplug_sata ()
{
	if [ ss"${SUBSYSTEM}" != ss"block" ]; then
		return 1
	fi

	case "${ACTION}" in
	"remove" )
		remove_disk "${DEVNAME}"
	;;
	* )
		echo "ACTION:${ACTION}" > ${CONSOLE}
	;;
	esac

	return 0
}
################################################################################
#show_env
hotplug_usb
hotplug_sata