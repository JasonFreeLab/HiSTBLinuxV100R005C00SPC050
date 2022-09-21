#!/bin/bash -x
#trustedcore packager
#created by sdk


KERNEL_TEXT_BASE=$1
PLATFORM_CHOOSE=$2
RELEASE_OUT_PATH=$3
COMPARE_IMAGE=$4
CHIP_CHOOSE=$5
DEBUG=$6
TASK_HISI_LIST=$7


IMG_PATH=${RELEASE_OUT_PATH}
KERNEL_NAME=rtosck.img
KERNEL_PATH=${IMG_PATH}/${KERNEL_NAME}
KERNEL_ELF=${IMG_PATH}/${KERNEL_NAME}.elf
DST_PATH=${IMG_PATH}/trustedcore.img
CURDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )"/../../.. && pwd )"
SCRIPT_PATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

ELF_EXTRACT_SRC=${CURDIR}/tools/elf_extract.c
if [ ${DEBUG} -eq 0 ]; then
	ELF_EXTRACT_BIN=${CURDIR}/tools/elf_extract_release
else
	ELF_EXTRACT_BIN=${IMG_PATH}/elf_extract
fi

if [ -f ${ELF_EXTRACT_BIN} ];then
	echo "Info: found elf_extract tool"
	chmod 777 ${ELF_EXTRACT_BIN}
elif [ -f ${ELF_EXTRACT_SRC} ];then
	if [ ${DEBUG} -eq 0 ]; then
		gcc ${ELF_EXTRACT_SRC} -o ${ELF_EXTRACT_BIN} -lcrypto -DDEBUG=1 -static
	else
		gcc ${ELF_EXTRACT_SRC} -o ${ELF_EXTRACT_BIN} -DDEBUG=${DEBUG} -static
	fi
	if [ $? -ne 0 ];then
		echo "Error: build elf_extract tool fail"
		exit -1
	fi
else
	echo "Error: Can not find elf_extract tool"
	exit -1
fi

TASK_GLOBAL_NAME=globaltask.img
TASK_GLOBAL_UUID="00000000000000000000000000000000"
TASK_GLOBAL_PATH=${IMG_PATH}/${TASK_GLOBAL_NAME}
TASK_GLOBAL_ELF=${IMG_PATH}/${TASK_GLOBAL_NAME}.elf
TASK_GLOBAL_SYM=${CURDIR}/release/elfile


TASK_REET_NAME=task_reet.elf
TASK_REET_UUID="0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A"
TASK_REET_PATH=${CURDIR}/release/internal_tasks/${TASK_REET_NAME}

TASK16_NAME=task_ssa.elf
TASK16_UUID="999286b954da42359e7796e81fea1ee4"
TASK19_NAME=task_rpmb.elf
TASK19_UUID="004555da864e4a8e8540285818e7e529"
TASK16_PATH=${CURDIR}/release/internal_tasks/${TASK16_NAME}
TASK19_PATH=${CURDIR}/release/internal_tasks/${TASK19_NAME}

#Add new internal task here:
TASK_LIST="${TASK_GLOBAL_PATH},${TASK_GLOBAL_NAME%.*},${TASK_GLOBAL_UUID},0x1000 \
    ${TASK_REET_PATH},${TASK_REET_NAME%.*},${TASK_REET_UUID},0x1000 \
    ${TASK16_PATH},${TASK16_NAME%.*},${TASK16_UUID},0x1000 \
    ${TASK19_PATH},${TASK19_NAME%.*},${TASK19_UUID},0x1000 \
    "

TASK_LIST=${TASK_LIST}${TASK_HISI_LIST}
echo "task list 2: is ${TASK_LIST}"

echo "1. repack globaltask.img and rtosck.img and place their symbol tables to the file tail"
FUNC_TAB_FILE_PATH=${RELEASE_OUT_PATH}/func_table_release.txt
if [ ${DEBUG} -eq 0 ]; then
	if [ -f ${FUNC_TAB_FILE_PATH} ];then
		rm ${FUNC_TAB_FILE_PATH}
	fi
	touch ${FUNC_TAB_FILE_PATH}
fi
KERNEL_SYMTAB_OFFSET=$(ls -l ${KERNEL_PATH}| awk '{print $5}')
${ELF_EXTRACT_BIN} "rtosck"     ${KERNEL_ELF} ${KERNEL_PATH} ${FUNC_TAB_FILE_PATH} ${CHIP_CHOOSE}
if [ $? -ne 0 ];then
    echo "Error: elf_extract rtosck failed."
    exit -1
fi
GLOBAL_SYMTAB_OFFSET=$(ls -l ${TASK_GLOBAL_PATH}| awk '{print $5}')
${ELF_EXTRACT_BIN} "globaltask" ${TASK_GLOBAL_ELF}  ${TASK_GLOBAL_PATH} ${FUNC_TAB_FILE_PATH} ${CHIP_CHOOSE}
if [ $? -ne 0 ];then
    echo "Error: elf_extract globaltask fail."
    exit -1
fi


KERNEL_TOTAL_SIZE=$(ls -l ${KERNEL_PATH}| awk '{print $5}')
GLOBAL_TOTAL_SIZE=$(ls -l ${TASK_GLOBAL_PATH}| awk '{print $5}')
KERNEL_SYMSTR_TOTAL_SIZE=`expr ${KERNEL_TOTAL_SIZE} - ${KERNEL_SYMTAB_OFFSET}`
GLOBAL_SYMSTR_TOTAL_SIZE=`expr ${GLOBAL_TOTAL_SIZE} - ${GLOBAL_SYMTAB_OFFSET}`

echo "2. generator symbol table header for globaltask.img and rtosck.img"
GLOBAL_SYMTAB_SIZE=$(readelf -S ${TASK_GLOBAL_ELF}| awk '{if ($2==".symtab") {print $6}}')
GLOBAL_BSS_SIZE=$(readelf -S ${TASK_GLOBAL_ELF}| awk '{if ($2==".bss") {print $6}}')
KERNEL_SYMTAB_SIZE=$(readelf -S ${KERNEL_ELF}| awk '{if ($2==".symtab") {print $6}}')
GLOBAL_SYM_HEAD="${GLOBAL_SYMTAB_OFFSET},${GLOBAL_SYMTAB_SIZE},${GLOBAL_SYMSTR_TOTAL_SIZE},${GLOBAL_BSS_SIZE}"
KERNEL_SYM_HEAD="${KERNEL_SYMTAB_OFFSET},${KERNEL_SYMTAB_SIZE},${KERNEL_SYMSTR_TOTAL_SIZE}"

echo "3. get globaltask.got size"
GOT_SIZE=$(size -A -x ${TASK_GLOBAL_ELF}| awk '{if ($1==".rel.dyn") {print $2}}')
echo "GOT_SIZE=${GOT_SIZE}"

echo "4. generate header"
#modify by sdk, set globaltask relocation info to image header
readelf -s -W ${TASK_GLOBAL_ELF} > ${TASK_GLOBAL_SYM}
#if [ "${CHIP_CHOOSE}" == "WITH_CHIP_HI3660" ];then
#    KECC1PUB_PLAT=kecc1pub_chicago
#fi
#if [ "${CHIP_CHOOSE}" == "WITH_CHIP_HI3650" ];then
#    KECC1PUB_PLAT=kecc1pub_austin
#fi
#if [ "${CHIP_CHOOSE}" == "WITH_CHIP_HI6250" ];then
#    KECC1PUB_PLAT=kecc1pub_dallas
#fi
chmod 777 ${CURDIR}/header.py
${CURDIR}/header.py \
	${DST_PATH} \
	${KERNEL_PATH} \
	${KERNEL_TEXT_BASE} \
	${GOT_SIZE} \
	${GLOBAL_SYM_HEAD} \
	${KERNEL_SYM_HEAD} \
	${TASK_GLOBAL_ELF} \
	${TASK_GLOBAL_SYM} \
	${COMPARE_IMAGE} \
	${KECC1PUB_PLAT} \
	${TASK_LIST}
RET=$?
if [ 0 -ne ${RET} ];then
    echo "failed to do header.py ret is ${RET}"
	if [ -f ${DST_PATH} ];then
	    rm ${DST_PATH}
	fi
else
    echo "succeed to execute head.py"
fi

if [ -f ${KERNEL_PATH} ];then
	rm ${KERNEL_PATH}
fi
if [ -f ${TASK_GLOBAL_PATH} ];then
	rm ${TASK_GLOBAL_PATH}
fi
if [ -f ${TASK_GLOBAL_SYM} ];then
	rm ${TASK_GLOBAL_SYM}
fi

exit ${RET}
