#!/bin/bash

CUR_DIR=`pwd`
CFG_DIR="$CUR_DIR/../.."
CFG_FILE_NAME="cfg.mak"
CFG_FILE_PATH="$CFG_DIR/$CFG_FILE_NAME"

if [ ! -f "$CFG_FILE_PATH" ] ; then
    echo " Error: $CFG_FILE_PATH not found!"
    exit 1;
fi

CFG_TOOLCHAINS_NAME=`sed '/^CFG_HI_ARM_TOOLCHAINS_NAME=/!d;s/.*=//' ${CFG_FILE_PATH}`
CFG_CHIP_TYPE=`sed '/^CFG_HI_CHIP_TYPE=/!d;s/.*=//' ${CFG_FILE_PATH}`
CFG_OUT_DIR=`sed '/^CFG_HI_OUT_DIR=/!d;s/.*=//' ${CFG_FILE_PATH}`

echo "CFG_TOOLCHAINS_NAME: ${CFG_TOOLCHAINS_NAME} "
echo $CFG_CHIP_TYPE
echo $CFG_OUT_DIR
HI_SHARED_LIB_DIR=${CFG_DIR}/out/${CFG_CHIP_TYPE}/${CFG_OUT_DIR}/lib/share
HI_STATIC_LIB_DIR=${CFG_DIR}/out/${CFG_CHIP_TYPE}/${CFG_OUT_DIR}/lib/static
HI_OBJ_DIR=${CFG_DIR}/out/${CFG_CHIP_TYPE}/${CFG_OUT_DIR}/obj

cd ${CUR_DIR}/GoogleTest
echo `pwd`
./build.py ${CFG_CHIP_TYPE} ${HI_SHARED_LIB_DIR} ${HI_STATIC_LIB_DIR} ${CFG_TOOLCHAINS_NAME}
mkdir -p ${HI_OBJ_DIR}/sample/widevine/GoogleTest
cp ${CUR_DIR}/GoogleTest/out/${CFG_CHIP_TYPE}/Debug/widevine_ce_cdm_unittest ${HI_OBJ_DIR}/sample/widevine/GoogleTest

