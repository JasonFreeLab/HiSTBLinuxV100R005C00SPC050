#!/bin/bash

###############################################################################
#
#  Ceate By jinghui
#
###############################################################################

function usage ()
{
	echo "Usage: ${selfname} RSAPubKeyFile SWPKFile"
	echo "  RSAPubKeyFile      OEM RSA public key binary file."
	echo "                     used to verify Ext Params Area and SBL"
	echo "  SWPKFile           Encrypted SWPK bin file of OEM, used to decrypt SBL"
	echo ""
	echo "Example:"
	echo "  ${selfname} rsapubkey.bin swpk.bin"
	echo ""
	exit 0
}
###############################################################################

function run ()
{
	dd if=${RSAPubKeyFile} of=${outputfile} bs=1 count=${rsapubkeysize}
	dd if=${SWPKFile} of=${outputfile} bs=1 seek=${rsapubkeysize} count=${swpksize}
	dd if=/dev/zero of=${outputfile} bs=1 seek=${reservedoffset}  count=${reservedsize}
	
}
###############################################################################

if [ $# == 0 ]; then
	usage;
fi

if [ $# != 2 ]; then
	echo "need many parameters."
	exit 1
fi

RSAPubKeyFile=${1}
SWPKFile=${2}
rsapubkeysize=512
swpksize=16
reservedoffset=$((${rsapubkeysize} + ${swpksize}))
reservedsize=16

outputfile=extkeyfile.bin

if [ ! -f "${RSAPubKeyFile}" ]; then 
    echo "$RSAPubKeyFile not exist."
	exit 1
fi 
if [ ! -f "${SWPKFile}" ]; then 
    echo "${SWPKFile} not exist."
	exit 1
fi 

if [ -f "${outputfile}" ]; then 
    rm ${outputfile}
fi 

run;




