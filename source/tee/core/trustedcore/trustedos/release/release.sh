#!/bin/bash

echo ANDROID_PRODUCT_OUT:$ANDROID_PRODUCT_OUT

#ANDROID_PRODUCT_OUT = $1
#echo ANDROID_PRODUCT_OUT:$1
CURDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

#1.copy TEE STATIC LIB
SYSTEM_STATIC_LIB_PATH=$ANDROID_PRODUCT_OUT/obj/STATIC_LIBRARIES
GLOBALTASK_LIB_PATH=${SYSTEM_STATIC_LIB_PATH}/libtee_intermediates/libtee.a
GLOBALTASK_THIRD_PATH=${SYSTEM_STATIC_LIB_PATH}/libthird_intermediates/libthird.a
GLOBALTASK_O=${SYSTEM_STATIC_LIB_PATH}/global_task_o_intermediates/global_task.o

cp -rf ${GLOBALTASK_LIB_PATH} ${CURDIR}/internal_tasks/
cp -rf ${GLOBALTASK_THIRD_PATH} ${CURDIR}/internal_tasks/
cp -rf ${GLOBALTASK_O} ${CURDIR}/internal_tasks/


#2. copy elf_main_entry.o
SYSTEM_ELF_MAIN_PATH=$ANDROID_PRODUCT_OUT/obj/EXECUTABLES/task_storage_intermediates/dotdot/elf_main_entry.o
cp -rf ${SYSTEM_ELF_MAIN_PATH} ${CURDIR}/internal_tasks/

#3. copy libtrustedcore.a
TRUSTCORE_LIB_PATH=${SYSTEM_STATIC_LIB_PATH}/libtrustedcore_intermediates/libtrustedcore.a
cp -rf ${TRUSTCORE_LIB_PATH} ${CURDIR}/trustedcore_lib/


#3. copy internal_tasks
IMG_PATH=$ANDROID_PRODUCT_OUT/obj/EXECUTABLES

#DST_PATH=${ANDROID_PRODUCT_OUT}/trustedcore.img
#CURDIR="${ cd "${ dirname "${BASH_SOURCE[0]}" }" && pwd }"

TASK1_NAME=globaltask.img
TASK1_UUID="00000000000000000000000000000000"
TASK1_PATH=${IMG_PATH}/${TASK1_NAME}_intermediates/${TASK1_NAME}

TASK5_NAME=task_storage.elf
TASK5_UUID="02020202020202020202020202020202"

TASK11_NAME=task_reet.elf
TASK11_UUID="0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A"

TASK12_NAME=task_ssa.elf
TASK12_UUID="999286b954da42359e7796e81fea1ee4"

TASK19_NAME=task_rpmb.elf
TASK19_UUID="004555da864e4a8e8540285818e7e529"

TASK5_PATH=${IMG_PATH}/${TASK5_NAME%.*}_intermediates/${TASK5_NAME}
TASK11_PATH=${IMG_PATH}/${TASK11_NAME%.*}_intermediates/${TASK11_NAME}
TASK12_PATH=${IMG_PATH}/${TASK12_NAME%.*}_intermediates/${TASK12_NAME}
TASK19_PATH=${IMG_PATH}/${TASK19_NAME%.*}_intermediates/${TASK19_NAME}

cp -rf ${TASK5_PATH} ${CURDIR}/internal_tasks/
cp -rf ${TASK11_PATH} ${CURDIR}/internal_tasks/
cp -rf ${TASK12_PATH} ${CURDIR}/internal_tasks/
cp -rf ${TASK19_PATH} ${CURDIR}/internal_tasks/

