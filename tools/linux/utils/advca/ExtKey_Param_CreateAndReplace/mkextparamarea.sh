#!/bin/bash

###############################################################################
#
#  Ceate By jinghui
#
###############################################################################

function usage ()
{
	echo "Usage: ${selfname} ExtCfgParamFile SecureOSSize SBLSize FBLDataSize SBLVerifyFlag SBLDecryptFlag"
	echo "  ExtCfgParamFile      Chipset configuration parameter."
	echo "                   used to verify Ext Params Area and SBL"
	echo "  SecureOSSize     Secure OS partition size in hex."
	echo "  SBLSize          SBL partition size in hex."
	echo "  FBLDataSize      FBL Data partition size in hex. align by block size of flash."
	echo "  SBLVerifyFlag    1 - SBL image is signed and no need to verify; 0 - SBL image should be verifed."
	echo "  SBLDecryptFlag   1 - SBL image is not encrypted; 0 - SBL image is encrypted. This flag is valid when SBLVerifyFlag is 0"
	echo "Example:"
	echo "  ${selfname} reg.bin 0x10 0x10 0x10 1 0"
	echo ""
	exit 0
}
###############################################################################

function run ()
{
	dd if=${ExtCfgParamFile} of=${outputfile} bs=${ExtCfgParamFileLen} count=1 conv=sync

	len=`expr length $SecureOSSize`
	SecureOSSize=`expr substr $SecureOSSize 3 $(($len-2))`
    loop=$((10-$len))
    for((i=1;i<=$loop;i++))
	do	
		SecureOSSize="0"$SecureOSSize
	done
	
	byte0=`expr substr $SecureOSSize 7 2`
	if [ -z "$byte0" ]; then
			byte0=0
	fi

	byte1=`expr substr $SecureOSSize 5 2`
	if [ -z "$byte1" ]; then
			byte1=0
	fi

	byte2=`expr substr $SecureOSSize 3 2`
    if [ -z "$byte2" ]; then
		byte2=0
	fi

	byte3=`expr substr $SecureOSSize 1 2`
	if [ -z "$byte3" ]; then
		byte3=0
	fi
	
	echo -n -e "\x$byte0" >> ${outputfile}
	echo -n -e "\x$byte1" >> ${outputfile}
	echo -n -e "\x$byte2" >> ${outputfile}
	echo -n -e "\x$byte3" >> ${outputfile}
	
	len=`expr length $SBLSize`
	echo $len
	SBLSize=`expr substr $SBLSize 3 $(($len-2))`
	echo $(($len-2))
	echo $SBLSize
    loop=$((10-$len))
	echo $loop
    for((i=1;i<=$loop;i++))
	do	
		SBLSize="0"$SBLSize
	done
	
	byte0=`expr substr $SBLSize 7 2`
	if [ -z "$byte0" ]; then
			byte0=0
	fi

	byte1=`expr substr $SBLSize 5 2`
	if [ -z "$byte1" ]; then
			byte1=0
	fi

	byte2=`expr substr $SBLSize 3 2`
    if [ -z "$byte2" ]; then
		byte2=0
	fi

	byte3=`expr substr $SBLSize 1 2`
	if [ -z "$byte3" ]; then
		byte3=0
	fi
	
	echo -n -e "\x$byte0" >> ${outputfile}
	echo -n -e "\x$byte1" >> ${outputfile}
	echo -n -e "\x$byte2" >> ${outputfile}
	echo -n -e "\x$byte3" >> ${outputfile}
	
	len=`expr length $FBLDataSize`
	echo $len
	FBLDataSize=`expr substr $FBLDataSize 3 $(($len-2))`
	echo $(($len-2))
    loop=$((10-$len))
    for((i=1;i<=$loop;i++))
	do	
		FBLDataSize="0"$FBLDataSize
	done
	
	byte0=`expr substr $FBLDataSize 7 2`
	if [ -z "$byte0" ]; then
			byte0=0
	fi

	byte1=`expr substr $FBLDataSize 5 2`
	if [ -z "$byte1" ]; then
			byte1=0
	fi

	byte2=`expr substr $FBLDataSize 3 2`
    if [ -z "$byte2" ]; then
		byte2=0
	fi

	byte3=`expr substr $FBLDataSize 1 2`
	if [ -z "$byte3" ]; then
		byte3=0
	fi
	
	echo -n -e "\x$byte0" >> ${outputfile}
	echo -n -e "\x$byte1" >> ${outputfile}
	echo -n -e "\x$byte2" >> ${outputfile}
	echo -n -e "\x$byte3" >> ${outputfile}

	byte3=`expr substr $SBLVerifyFlag 1 2`
	if [ -z "$byte3" ]; then
		byte3=0
	fi
	
	byte2=`expr substr $SBLDecryptFlag 1 2`
	if [ -z "$byte2" ]; then
		byte2=0
	fi
	byte1=0
	byte0=0
	echo "byte0=$byte0,byte1=$byte1,byte2=$byte2,byte3=$byte3"
	echo -n -e "\x$byte0" >> ${outputfile}
	echo -n -e "\x$byte1" >> ${outputfile}
	echo -n -e "\x$byte2" >> ${outputfile}
	echo -n -e "\x$byte3" >> ${outputfile}
	
	dd if=/dev/zero of=${outputfile} bs=1 seek=${reservedoffset}  count=${reservedsize}
	
}
###############################################################################

if [ $# == 0 ]; then
	usage;
fi

if [ $# != 6 ]; then
	echo "need many parameters."
	exit 1
fi

ExtCfgParamFile=${1}
SecureOSSize=${2}
SBLSize=${3}
FBLDataSize=${4}
SBLVerifyFlag=${5}
SBLDecryptFlag=${6}
ExtCfgParamFileLen=9680
reservedoffset=$((${ExtCfgParamFileLen} + 16))
echo $reservedoffset
reservedsize=0

outputfile=extparamarea.bin

if [ ! -f "${ExtCfgParamFile}" ]
then 
    echo "$ExtCfgParamFile not exist."
	exit 1
fi 

if [ -f "${outputfile}" ]
then 
    rm ${outputfile}
fi 

len=`expr length $SecureOSSize`
if [ $len -gt 10 ]
then
    echo "SecureOSSize=$SecureOSSize error"
	exit 1
fi

len=`expr length $SBLSize`
if [ $len -gt 10 ]
then
    echo "SBLSize=$SBLSize error"
	exit 1
fi

len=`expr length $FBLDataSize`
if [ $len -gt 10 ]
then
    echo "FBLDataSize=$FBLDataSize error"
	exit 1
fi

len=`expr $SBLVerifyFlag`	
SBLVerifyFlag=00	
if [ $len -eq 1 ]
then
	SBLVerifyFlag=96
fi

len=`expr $SBLDecryptFlag`
SBLDecryptFlag=00	
if [ $len -eq 1 ]
then
	SBLDecryptFlag=96
fi	

run;
#to do 调用casigntool对镜像进行签名，脚本中注意Algorithm=RSA
#CASigntool 4 crypto_config.cfg


