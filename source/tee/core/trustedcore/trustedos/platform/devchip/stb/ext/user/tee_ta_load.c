/******************************************************************************
*
* Copyright (C), 2004-2020, Hisilicon Tech. Co., Ltd.
* ******************************************************************************
* File Name     : tee_ta_load.c
* Version       : Initial
* Author        : Hisilicon
* Created       : 2017-4-15
* Last Modified :
* Description   :
* Function List :
* History       :
* ******************************************************************************/

#include "tee_ta_load.h"
#include "tee_log.h"
#include "ta_framework.h"

#ifdef CFG_HI_TEE_TA_LOAD_SUPPORT
/**
 * is_third_identity - check whether hisilicon ta
 */
int32_t is_third_identity(uint8_t *buffer, uint32_t size)
{
	if (!buffer || 0 == size) {
		tloge("Invalid input");
		return false;
	}

	if (hisi_check_header(buffer, size)) {
		tlogd("Invalid header, not hisilicon TA");
		return false;
	}

	tlogd("header check suc");
	return true;
}

/**
 * process_header_third - get buffer total len form header
 *
 * Golbal task will copy dynamic TA form share buffer to TEE memery.
 * When dynamic TA is bigger than max size of share buffer(1M),
 * golbal task will return and wait for next part of TA.
 * So golbal task need the total len of dynamic TA to alloc memery.
 */
TEE_Result process_header_third(uint8_t *buffer, uint32_t size, TEEC_IMAGE_INFO *img_info)
{
	int result;

	if (!buffer || !img_info || 0 == size) {
		tloge("Invalid input");
		return TEE_ERROR_BAD_PARAMETERS;
	}

	result = hisi_get_total_len(buffer, size, &img_info->total_len);
	if (result) {
		tloge("get total len fail");
		return TEE_ERROR_GENERIC;
	}

	return TEE_SUCCESS;
}

/**
 * process_body_third - verify and decrypt dynamic TA
 *
 * Get ta manifest and elf from buffer, return ta information.
 * Golbal task will load elf and configure ta.
 */
TEE_Result process_body_third(uint8_t *buffer, uint32_t size, TEEC_IMAGE_INFO *img_info)
{
	int result;
	char *ta_data = NULL;
	char *ta_elf = NULL;
	HISI_TA_MANIFEST ta_manifest = {0};
	unsigned int data_size;
	unsigned int data_offest;
	unsigned int elf_size;

	if (!buffer || !img_info || 0 == size) {
		tloge("Invalid input");
		return TEE_ERROR_BAD_PARAMETERS;
	}

	/**
	 * buffer layout:
	 *
	 * ----------------------------------
	 * Image Header Description
	 * -------------------------
	 * Private Data
	 * ------------------------- Header
	 * Stuff Data
	 * -------------------------
	 * Signature of Header
	 * ----------------------------------
	 * TA manifest
	 * ----------- Private Data
	 * TA elf
	 * -------------------------
	 * Stuff Data
	 * -------------------------  Data
	 * Signature of Header
	 * -------------------------
	 * Signature of Data
	 * ----------------------------------
	 */
	result = hisi_get_private_data(buffer, size, &data_size, &data_offest);
	if (result) {
		tloge("get ta data fail");
		return TEE_ERROR_GENERIC;
	}

	ta_data = buffer + data_offest;
	ta_elf = ta_data + sizeof(HISI_TA_MANIFEST);
	elf_size = data_size - sizeof(HISI_TA_MANIFEST);

	/* get manifest*/
	TEE_MemMove(&ta_manifest, ta_data, sizeof(HISI_TA_MANIFEST));

	/* move ta elf to head */
	TEE_MemMove(buffer, ta_elf, elf_size);
	img_info->img_buf = buffer;
	img_info->img_buf_len = elf_size;

	/* use the memery behind elf to save TA name */
	img_info->service_name = buffer + elf_size;

	/* set ta info from manifest */
	TEE_MemFill(img_info->service_name, 0, sizeof(ta_manifest.service_name));
	TEE_MemMove(img_info->service_name, ta_manifest.service_name, ta_manifest.service_name_len);
	TEE_MemMove(&img_info->srv_uuid, &ta_manifest.srv_uuid, sizeof(TEE_UUID));
	img_info->service_name_len = ta_manifest.service_name_len;
	img_info->multi_instance = ta_manifest.single_instance ? 0 : 1;
	img_info->multi_session = ta_manifest.multi_session;
	img_info->multi_command = ta_manifest.multi_command;
	img_info->heap_size = ta_manifest.heap_size;
	img_info->stack_size = ta_manifest.stack_size;
	img_info->instance_keep_alive = ta_manifest.instance_keep_alive;

	/* adapt to secure os, devchip not use */
	img_info->manifest_buf = NULL;
	img_info->manifest_str_len = 0;
	img_info->img_version = 0;
	img_info->identity_len = 0;
	img_info->header_len = 0;

	tlogd("load ta[%s]\n", img_info->service_name);
	/* hex_dump("load ta uuid:", &ta_manifest.srv_uuid, sizeof(TEE_UUID)); */

	return TEE_SUCCESS;
}

/**
 * process_end_third - release source after global task loaded ta
 */
void process_end_third(void)
{
	/* not thing to do */
}
#else
int32_t is_third_identity(uint8_t *buffer, uint32_t size) {return false;}
TEE_Result process_header_third(uint8_t *buffer, uint32_t size, TEEC_IMAGE_INFO *img_info) {return TEE_ERROR_GENERIC;}
TEE_Result process_body_third(uint8_t *buffer, uint32_t size, TEEC_IMAGE_INFO *img_info) {return TEE_ERROR_GENERIC;}
void process_end_third(void){return;}
#endif
