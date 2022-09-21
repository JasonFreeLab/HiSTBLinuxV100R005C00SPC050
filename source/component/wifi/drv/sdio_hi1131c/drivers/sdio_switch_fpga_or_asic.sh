#!/bin/bash

#for fpga,sdio clock is 25M
#for asic,sdio clock is 50M

VERSION_FPGA="FPGA"
VERSION_ASIC="ASIC"


if [ "$1" == "$VERSION_FPGA" ]
then
	cp Kconfig_FPGA Kconfig
	echo "switch to FPGA"
elif [ "$1" == "$VERSION_ASIC" ]
then
	cp Kconfig_ASIC Kconfig
	echo "switch to ASIC"
else
	echo "parameter is false,please choose FPGA or ASIC"
fi
