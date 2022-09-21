#ifndef __TEE_TA_LOAD_H
#define __TEE_TA_LOAD_H
#include "tee_internal_api.h"
#include "ta_framework.h"

#define MAX_HEADER_SIZE 0x400

typedef struct {
	uint32_t img_version;  /* optional parameter */
	uint32_t identity_len; /* optional parameter */
	uint32_t header_len;   /* optional parameter */
	uint32_t image_len;
	uint32_t total_len;    /* buffer total len, include header/signature/manifest/ELF */
	TEE_UUID srv_uuid;
	int8_t   *service_name; /* TA name */
	uint32_t service_name_len;
	int32_t  multi_instance;
	int32_t  multi_session;
	int32_t  multi_command;
	uint32_t heap_size;
	uint32_t stack_size;
	int32_t  instance_keep_alive;
	uint8_t *manifest_buf;  /* optional parameter */
	uint8_t manifest_str_len;  /* optional parameter */
	int8_t   *img_buf;
	uint32_t img_buf_len;
	uint32_t img_buf_offset; /* optional parameter */
} TEEC_IMAGE_INFO;

/* Hisilicon private data for ta load */
typedef struct {
	TEE_UUID srv_uuid;
	int32_t  single_instance;
	int32_t  multi_session;
	int32_t  multi_command;
	uint32_t heap_size;
	uint32_t stack_size;
	int32_t  instance_keep_alive;
	int8_t   service_name[SERVICE_NAME_MAX];   /* TA name */
	uint32_t service_name_len;
	int8_t   reserve[128];
} HISI_TA_MANIFEST;

int32_t is_third_identity(uint8_t *buffer, uint32_t size);
TEE_Result process_header_third(uint8_t *buffer, uint32_t size, TEEC_IMAGE_INFO *img_info);
TEE_Result process_body_third(uint8_t *buffer, uint32_t size, TEEC_IMAGE_INFO *img_info);
void process_end_third(void);
#endif
