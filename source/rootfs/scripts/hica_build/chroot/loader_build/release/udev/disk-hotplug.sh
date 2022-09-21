#!/bin/sh



remove_disk ()
{
	local ORG_NAME="/home/stb"$1
	
	rm -f ${ORG_NAME}
}

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
	;;
	esac

	return 0
}

hotplug_usb
hotplug_sata