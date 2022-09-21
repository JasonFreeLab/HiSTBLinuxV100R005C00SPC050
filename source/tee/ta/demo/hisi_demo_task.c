#include "uuid_chip.h"
#define TA_DEBUG
#include "hi_tee_ta_al.h"
#ifdef DEMO_TRUSTEDCORE_TEST
#include "rpmb_fcntl.h"
#endif

#define HISI_DEMO_CMD_HELLO				0
#define HISI_DEMO_CMD_STORAGE			1
#define HISI_DEMO_CMD_TA2TA				2
#define HISI_DEMO_CMD_RPMB				3
#define HISI_DEMO_CMD_WR_RPMB_KEY		4
#define HISI_DEMO_CMD_STORAGE_PD		6
#define HISI_DEMO_CMD_STORAGE_LOOP		7
#define HISI_DEMO_CMD_STORAGE_READ		8
#define HISI_DEMO_CMD_IOCTL		        9
#define HISI_DEMO_CMD_MALLOC		    10
#define HISI_DEMO_CMD_RSA		    	11
#define HISI_DEMO_CMD_LOG_LEVEL         12
#define HISI_DEMO_CMD_TIME              13
#define HISI_DEMO_CMD_TA_LOAD           14

#define DEMO_TASK_FILE_NAME "demo_task_file_name.txt"
#define DEMO_TASK_RSA_KEY_FILE_NAME "demo_task_rsa_key.txt"

#define DEMO_TASK_RSA_MODE_NOT_CRT      0
#define DEMO_TASK_RSA_MODE_CRT          1

#define DEMO_TASK_RSA_KEY_NOT_EXIST     0
#define DEMO_TASK_RSA_KEY_EXIST         1

#define DEMO_TASK_FUNC_START() ta_debug("____________start____________\n")
#define DEMO_TASK_FUNC_END()   ta_debug("____________end____________\n")

#define DEMO_TASK_PRINT_HEX(str, len) \
{\
    unsigned int _i = 0; \
    unsigned char *_str = (unsigned char *)str;\
    if (_str != NULL) {\
		for ( _i = 0 ; _i < (len); _i++) {\
		        if( (_i % 16 == 0) && (_i != 0)) ta_printf("\n"); \
		        ta_printf("0x%02x, ", *((_str)+_i)); \
		}\
		ta_printf("\n");\
    }\
}

static uint32_t storageID = TEE_OBJECT_STORAGE_PRIVATE;
unsigned int normal_var;
static unsigned int static_var;

unsigned int storage_flag_debug;

char g_input_data[] = {
	0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
};

char g_hash_data[] = {
	0x26, 0xf6, 0x42, 0x27, 0xb0, 0xdf, 0x27, 0x34, 0xed, 0x95, 0x2f, 0xd1, 0xb9, 0xb6, 0x9f, 0xb3,
	0x7d, 0xfa, 0x08, 0xcf, 0x3c, 0x52, 0x89, 0xa2, 0x3e, 0xcb, 0x28, 0xa1, 0xa8, 0x6c, 0x4f, 0x49,
};

char g_encrypted_data[] = {
	0x01, 0xa8, 0x1f, 0x96, 0xc0, 0x89, 0xdb, 0x7c, 0x9c, 0x67, 0xa8, 0x93, 0x84, 0xa7, 0x25, 0xa4,
	0x48, 0xf7, 0xb0, 0xab, 0x8d, 0x40, 0x81, 0x8d, 0xe5, 0x2c, 0x2a, 0xf1, 0xa3, 0x85, 0x52, 0xd1,
	0xf4, 0xec, 0x5d, 0xfb, 0x32, 0x64, 0x75, 0x9b, 0x3f, 0x1b, 0xea, 0x33, 0x91, 0x3f, 0xa3, 0x40,
	0xa4, 0x55, 0x72, 0x1e, 0xd8, 0x76, 0xce, 0xb6, 0x1a, 0x22, 0x37, 0x96, 0x8f, 0xb8, 0x4d, 0xa3,
	0xb1, 0x1a, 0x67, 0xf0, 0x6e, 0x1f, 0x01, 0xb3, 0xc0, 0x52, 0xf0, 0x2f, 0x8e, 0x41, 0xd8, 0xb3,
	0x64, 0x5e, 0xf0, 0x71, 0xc3, 0xd1, 0xb6, 0xd5, 0xee, 0x98, 0x5c, 0xc8, 0xce, 0x7d, 0xfc, 0x8a,
	0x8f, 0x4f, 0xfb, 0x3f, 0x3b, 0xbc, 0xa3, 0xee, 0x42, 0x68, 0x17, 0x5b, 0xca, 0x1a, 0x1a, 0x42,
	0xf2, 0xac, 0x39, 0x3f, 0xa7, 0x45, 0x8a, 0x71, 0xe0, 0x09, 0x64, 0x2c, 0xd0, 0x99, 0xfd, 0x0d,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

/* RSA key pair 1024 */
/* TEE_ATTR_RSA_MODULUS */
char g_rsa_keypair_n[] = {
	0xac, 0xab, 0x66, 0xa9, 0xa8, 0xa1, 0x62, 0x5f, 0x13, 0x0f, 0x3d, 0x72, 0x6a, 0x93, 0x55, 0xd1,
	0xde, 0xd7, 0x95, 0xe8, 0x24, 0xc3, 0x67, 0x97, 0xe4, 0xfe, 0x4e, 0x63, 0xdb, 0xd1, 0xdb, 0x3e,
	0xe6, 0xcd, 0x4f, 0x1b, 0x76, 0x9b, 0xc5, 0x8a, 0xe4, 0x35, 0xbd, 0xc9, 0xab, 0x7f, 0xcb, 0x8e,
	0xc9, 0x06, 0x6b, 0x32, 0x48, 0x5b, 0x26, 0xce, 0xf3, 0xca, 0xd5, 0x57, 0xe7, 0x89, 0x13, 0x0a,
	0x0a, 0xdd, 0x69, 0x1a, 0xb8, 0x74, 0x66, 0x69, 0xdd, 0x34, 0x9f, 0x95, 0xe7, 0xa1, 0x74, 0x14,
	0xc1, 0x1c, 0x11, 0x3a, 0xe9, 0x38, 0x6c, 0x2c, 0x3b, 0x2f, 0xb3, 0x9a, 0xf6, 0x5b, 0x86, 0x96,
	0xc0, 0x8a, 0xb1, 0x1e, 0x64, 0xbd, 0x4a, 0xdc, 0x41, 0xb4, 0xf7, 0x06, 0x13, 0xd0, 0xa4, 0xfe,
	0x06, 0x50, 0xd3, 0x12, 0xa1, 0x7e, 0x98, 0x17, 0xe5, 0xad, 0xe9, 0xbc, 0xe5, 0x17, 0x37, 0x2f,
};

/* TEE_ATTR_RSA_PUBLIC_EXPONENT */
char g_rsa_keypair_e[] = {
	0x01, 0x00, 0x01,
};

/* TEE_ATTR_RSA_PRIVATE_EXPONENT */
char g_rsa_keypair_d[] = {
	0x1d, 0xe3, 0x4d, 0x51, 0xf0, 0xae, 0x7e, 0xa8, 0x96, 0x53, 0xfc, 0xfe, 0xe1, 0x13, 0xbf, 0xb7,
	0x24, 0x2b, 0x8c, 0xf7, 0x31, 0xe5, 0xe0, 0xf8, 0x99, 0xda, 0xab, 0x16, 0xfd, 0xe5, 0xc5, 0x5d,
	0x8d, 0xf5, 0xdb, 0xcb, 0x95, 0x2c, 0x41, 0x75, 0x59, 0x2b, 0x34, 0x3e, 0xc4, 0x40, 0xca, 0xab,
	0x5c, 0x80, 0x8f, 0xed, 0x94, 0x38, 0xb2, 0xee, 0xff, 0xa4, 0x0c, 0x69, 0xba, 0xda, 0x2f, 0x41,
	0x34, 0x72, 0x3f, 0xc6, 0xcb, 0x86, 0x4f, 0xfd, 0x4d, 0xba, 0x8e, 0xb3, 0x4b, 0x1e, 0x05, 0xb8,
	0x3c, 0xbd, 0xce, 0xf5, 0xd0, 0xa7, 0xb5, 0x2e, 0x4e, 0x00, 0x32, 0x6b, 0x4b, 0xfa, 0xa9, 0x76,
	0xeb, 0xbb, 0x57, 0xc0, 0xa6, 0xb1, 0xb0, 0x75, 0x16, 0x43, 0x32, 0xa0, 0x52, 0x23, 0xf4, 0x73,
	0x27, 0x0b, 0x30, 0xe0, 0x2a, 0x7b, 0x1e, 0x1f, 0x1c, 0x5d, 0xe3, 0x4f, 0x71, 0x4d, 0x49, 0x81,
};

char g_rsa_sign_data[] = {
	0x11, 0xd1, 0x33, 0xe5, 0xb0, 0xc9, 0x25, 0xf7, 0xb4, 0x9c, 0x17, 0x35, 0x90, 0x6f, 0x2d, 0x7a,
	0xda, 0xf1, 0x71, 0x4a, 0x6a, 0x51, 0x55, 0x99, 0x89, 0x9d, 0xc2, 0x25, 0x45, 0x00, 0x72, 0xaf,
	0xe4, 0x10, 0x52, 0x97, 0x4e, 0x85, 0x8e, 0x42, 0x69, 0x10, 0x17, 0x27, 0x9c, 0xc6, 0x4e, 0x8e,
	0x5a, 0x41, 0x74, 0x05, 0xd7, 0xa3, 0xf0, 0x35, 0xe7, 0x87, 0x9b, 0xe5, 0xab, 0xe3, 0x3a, 0x7f,
	0x6e, 0xc0, 0x33, 0x5d, 0x13, 0x76, 0x7a, 0x2c, 0x18, 0x25, 0xc0, 0x53, 0x3d, 0xb4, 0xb8, 0x03,
	0x97, 0xd7, 0xb3, 0x14, 0x63, 0x1c, 0x1e, 0xb5, 0xe7, 0xe7, 0xd1, 0x97, 0x1d, 0xd5, 0xd0, 0x53,
	0x76, 0xd1, 0xd8, 0xb6, 0x80, 0xd2, 0x1f, 0x17, 0xed, 0x76, 0xf1, 0xb5, 0x3d, 0xaa, 0x4a, 0x61,
	0xe5, 0x33, 0x0a, 0xec, 0x92, 0x09, 0xd2, 0xc7, 0xed, 0x7f, 0xcc, 0xfe, 0xdd, 0x30, 0x8f, 0x8e,
};

/* RSA public key */
/* TEE_ATTR_RSA_MODULUS */
char g_rsa_pub_key_n[] = {
	0x7d, 0x17, 0x82, 0xe9, 0xc0, 0x81, 0xdf, 0x81, 0xb1, 0xf0, 0xcc, 0x68, 0xe4, 0x1d, 0x0a, 0x81,
	0xd0, 0x9f, 0xa0, 0xcd, 0x48, 0x22, 0x55, 0xed, 0x61, 0xc5, 0x74, 0xca, 0x8f, 0x52, 0xd7, 0xeb,
	0x1b, 0x4a, 0x2f, 0x02, 0x5c, 0x00, 0xcc, 0xb8, 0x78, 0xa7, 0x0d, 0x63, 0xf9, 0xc7, 0xd0, 0x01,
	0x50, 0x8e, 0x4c, 0x81, 0xbc, 0x74, 0x62, 0x49, 0x9d, 0x83, 0x68, 0xd5, 0xca, 0xc4, 0x8b, 0x61,
	0x79, 0xab, 0xa7, 0x51, 0x45, 0xd9, 0x08, 0x12, 0x2c, 0x6c, 0xfa, 0xab, 0x83, 0x23, 0xb1, 0xef,
	0x7e, 0x4a, 0x1c, 0x6b, 0x78, 0x09, 0xac, 0x7f, 0xa5, 0x73, 0xfe, 0xb0, 0x0f, 0xdc, 0xde, 0xdf,
	0xe3, 0x3d, 0x92, 0x60, 0x18, 0x79, 0x0d, 0xb1, 0xdb, 0x05, 0x0f, 0xa8, 0xe5, 0x5d, 0x78, 0x3c,
	0xad, 0xf5, 0x32, 0x5f, 0x0a, 0x2b, 0xae, 0x24, 0x64, 0x6b, 0x39, 0xdc, 0x6b, 0x4a, 0x33, 0x95,
};

/* TEE_ATTR_RSA_PUBLIC_EXPONENT */
char g_rsa_pub_key_e[] = {
	0x00, 0x00, 0x00, 0x03,
};

TEE_Result test_transient_object(void)
{
	TEE_ObjectHandle first_object;
	TEE_Result ret;
	TEE_Attribute *test_attribute;
	void* attr_buffer = "test save attribute";
	char testget_buff[128];
	size_t size;
	uint32_t objectUsage = TEE_USAGE_ENCRYPT | TEE_USAGE_DECRYPT;

	DEMO_TASK_FUNC_START();

	ret = TEE_AllocateTransientObject(TEE_TYPE_AES, 0x80, &first_object);
	if (TEE_SUCCESS != ret) {
		ta_error("TEE_AllocateTransientObject failed, ret[0x%x]\n", ret);
		return ret;
	}


	/* allocate attribute */
	test_attribute = (TEE_Attribute*)TEE_Malloc(sizeof(TEE_Attribute), 0);
	if (NULL == test_attribute) {
		ta_error("TEE_Malloc failed.\n");
		return TEE_ERROR_OUT_OF_MEMORY;
	}

	TEE_InitRefAttribute(test_attribute, TEE_ATTR_SECRET_VALUE, attr_buffer,
		(size_t)strlen(attr_buffer));

	ret = TEE_PopulateTransientObject(first_object, test_attribute, 1);
	if (TEE_SUCCESS != ret) {
		ta_error("TEE_PopulateTransientObject failed, ret[0x%x]\n", ret);
		goto exit1;
	}

	size = 128;
	ret = TEE_GetObjectBufferAttribute(first_object, TEE_ATTR_SECRET_VALUE,
		testget_buff,  &size);
	if (TEE_SUCCESS == ret) {
		testget_buff[size] = '\0';
		ta_debug("attribute buffer[%s] size[0x%x]\n", testget_buff, size);
	} else {
		ta_error("TEE_GetObjectBufferAttribute failed, ret[0x%x]\n", ret);
		goto exit2;
	}

	TEE_RestrictObjectUsage(first_object, objectUsage);


	TEE_ResetTransientObject(first_object);
	ret = TEE_SUCCESS;

	DEMO_TASK_FUNC_END();

exit2:
	TEE_FreeTransientObject(first_object);

exit1:
	TEE_Free((void*)test_attribute);
	return ret;
}

/* Create file(data stream object), write flash and read */
TEE_Result test_persistent_object(void)
{
	uint32_t r_flags = TEE_DATA_FLAG_ACCESS_READ;
	uint32_t w_flags = TEE_DATA_FLAG_ACCESS_WRITE;
	void* create_objectID = "crt.txtcase2";
	char *initialData = "This a trustedcore created sample initial data\n";
	size_t read_test_size = strlen(initialData);
	TEE_ObjectHandle first_object;
	TEE_Result ret;
	char  read_buffer[255];
	uint32_t count;

	DEMO_TASK_FUNC_START();

	/* create persistent object */
	ret = TEE_CreatePersistentObject(storageID, create_objectID,
		strlen(create_objectID),
		w_flags | TEE_DATA_FLAG_ACCESS_WRITE_META,
		TEE_HANDLE_NULL,
		(void *)initialData,
		(size_t)(strlen(initialData)),
		&first_object);
	if (TEE_SUCCESS != ret) {
		ta_error("TEE_CreatePersistentObject failed, ret[0x%x]\n", ret);
		return ret;
	}

	TEE_CloseObject(first_object);

	/* open file and read data */
	ret = TEE_OpenPersistentObject(storageID, create_objectID,
		strlen(create_objectID),
		r_flags | TEE_DATA_FLAG_ACCESS_WRITE_META,
		&first_object);

	if (TEE_SUCCESS != ret) {
		ta_error("TEE_OpenPersistentObject failed, ret[0x%x]\n", ret);
		return ret;
	}

	ret = TEE_ReadObjectData(first_object,read_buffer, read_test_size, &count);
	if (ret == TEE_SUCCESS) {
		read_buffer[count] = '\0';
		/* verify date */
		if (TEE_MemCompare(read_buffer, initialData, read_test_size)) {
			ta_error("TEE_ReadObjectData failed, initialData[%s] readData[%s]\n",
				initialData, read_buffer);
			goto exit1;
		}
		if (count != read_test_size) {
			ta_error("read data length error [0x%0x] != [0x%x]\n",
				read_test_size, count);
			goto exit1;
		}

	} else {
		ta_error("TEE_ReadObjectData failed, ret[0x%x]\n", ret);
		goto exit1;
	}

	/* delete persistent object */
	TEE_CloseAndDeletePersistentObject(first_object);

	/* check whether delete object suc */
	ret = TEE_OpenPersistentObject(storageID, create_objectID,
		strlen(create_objectID), r_flags, &first_object);
	if (TEE_SUCCESS == ret) {
		ta_error("Close and delete persistent object failed, ret[0x%x]\n", ret);
		goto exit1;
	}

	ret = TEE_SUCCESS;
	DEMO_TASK_FUNC_END();
	return ret;

exit1:
	TEE_CloseObject(first_object);
	return ret;
}

TEE_Result test_storage_sample(void)
{
	TEE_Result ret;

	ret = test_transient_object();
	if (TEE_SUCCESS != ret) {
		ta_error("test_transient_object failed, ret[0x%x]\n", ret);
		goto exit1;
	}

	ret = test_persistent_object();
	if (TEE_SUCCESS != ret) {
		ta_error("test_persistent_object failed, ret[0x%x]\n", ret);
		goto exit1;
	}

exit1:
	return ret;
}

TEE_Result test_storage_api(void)
{
	char *obj_id = "test_file.txt";
	char *data_init = "1234567890";
	char *data_append = "<data append>";
	TEE_ObjectHandle obj;
	TEE_Result ret = 0;
	TEE_ObjectHandle attr_obj;
	char buffer[255];
	unsigned int count;
	unsigned int flag = TEE_DATA_FLAG_ACCESS_WRITE;

	DEMO_TASK_FUNC_START();

	/* object attribute */
	ret = TEE_AllocateTransientObject(TEE_TYPE_AES, 0x80, &attr_obj);
	if (TEE_SUCCESS != ret) {
		ta_error("TEE_AllocateTransientObject failed, ret[0x%x]\n", ret);
		return ret;
	}

#ifdef TEE_DATA_FLAG_OVERWRITE
	flag |= TEE_DATA_FLAG_OVERWRITE;
#else
	flag |= TEE_DATA_FLAG_EXCLUSIVE; /* deprecated */
#endif
	/* create object */
	ret = TEE_CreatePersistentObject(TEE_OBJECT_STORAGE_PRIVATE,
								(void *)obj_id,
								strlen(obj_id),
								flag,
								attr_obj,
								(void *)data_init,
								strlen(data_init),
								&obj);
	if (TEE_SUCCESS != ret) {
		ta_error("TEE_CreatePersistentObject failed. file[%s] data[%s] ret[%x]\n", obj_id, data_init, ret);
		/* do not return */
	} else {
		TEE_CloseObject(obj);
	}

	/* open object */
	ret = TEE_OpenPersistentObject(TEE_OBJECT_STORAGE_PRIVATE,
								   (void *)obj_id,
								   strlen(obj_id),
								   TEE_DATA_FLAG_ACCESS_WRITE | TEE_DATA_FLAG_ACCESS_READ,
								   &obj);
	/* open objdect failed, create and open again */
	if (TEE_SUCCESS != ret)
	{
		ta_debug("File [%s] not exit, create it. ret[0x%x]\n", obj_id, ret);
		/* create object */
		ret = TEE_CreatePersistentObject(TEE_OBJECT_STORAGE_PRIVATE,
									(void *)obj_id,
									strlen(obj_id),
									TEE_DATA_FLAG_ACCESS_WRITE | TEE_DATA_FLAG_ACCESS_READ,
									attr_obj,
									(void *)data_init,
									strlen(data_init),
									&obj);
		if (TEE_SUCCESS != ret) {
			TEE_CloseObject(attr_obj);
			ta_error("TEE_CreatePersistentObject fail. file[%s] data[%s] ret[0x%x]\n", obj_id, data_init, ret);
			return ret;
		} else {
			TEE_CloseObject(obj);
		}

		/* open object */
		ret = TEE_OpenPersistentObject(TEE_OBJECT_STORAGE_PRIVATE,
									   (void *)obj_id,
									   strlen(obj_id),
									   TEE_DATA_FLAG_ACCESS_WRITE | TEE_DATA_FLAG_ACCESS_READ,
									   &obj);
		if (TEE_SUCCESS != ret) {
			ta_error("TEE_OpenPersistentObject fail. file[%s] ret[0x%x]\n", obj_id, ret);
			return ret;
		}
	}

	/* free attribute object */
	TEE_CloseObject(attr_obj);

	TEE_MemFill(&buffer, 0x0, sizeof(buffer));
	ret = TEE_ReadObjectData(obj, (void *)&buffer, sizeof(buffer), &count);
	if (TEE_SUCCESS != ret) {
		TEE_CloseObject(obj);
		ta_error("TEE_ReadObjectData failed, ret[0x%x]\n", ret);
		return ret;
	} else {
		ta_debug("Read object OK. buffer[%s] count[0x%x]\n", buffer, count);
	}

	ret = TEE_WriteObjectData(obj, data_append, strlen(data_append));
	if (TEE_SUCCESS != ret) {
		TEE_CloseObject(obj);
		ta_error("TEE_WriteObjectData failed, ret[0x%x]\n", ret);
		return ret;
	}

	TEE_CloseObject(obj);

	/* open object */
	ret = TEE_OpenPersistentObject(TEE_OBJECT_STORAGE_PRIVATE,
								   (void *)obj_id,
								   strlen(obj_id),
								   TEE_DATA_FLAG_ACCESS_WRITE | TEE_DATA_FLAG_ACCESS_READ,
								   &obj);
	if (TEE_SUCCESS != ret) {
		ta_error("TEE_OpenPersistentObject failed. file[%s] ret[0x%x]\n", obj_id, ret);
		return ret;
	}

	TEE_MemFill(&buffer, 0x0, sizeof(buffer));
	ret = TEE_ReadObjectData(obj, (void *)&buffer, sizeof(buffer), &count);
	if (TEE_SUCCESS != ret) {
		TEE_CloseObject(obj);
		ta_error("TEE_ReadObjectData failed. ret[0x%x]\n", ret);
		return ret;
	} else {
		ta_debug("Read object OK. buffer[%s] count[0x%x]\n",buffer, count);
	}

	TEE_CloseObject(obj);
	DEMO_TASK_FUNC_END();

	return ret;
}

TEE_Result test_storage_power_down(void)
{
	char *obj_id = "loop_file.txt";
	char *data_init = "1234567890";
	char *data_append;
	TEE_ObjectHandle obj;
	TEE_Result ret = 0;
	char buffer[1024];
	unsigned int count;
	int loop = 100;
	int size = 4096;

	DEMO_TASK_FUNC_START();

	/* open object */
	ret = TEE_OpenPersistentObject(TEE_OBJECT_STORAGE_PRIVATE,
								   (void *)obj_id,
								   strlen(obj_id),
								   TEE_DATA_FLAG_ACCESS_WRITE | TEE_DATA_FLAG_ACCESS_READ,
								   &obj);
	if (TEE_SUCCESS != ret)
	{
		ta_debug("File [%s] not exit. ret[%x]\n", obj_id, ret);
		/* create object */
		ret = TEE_CreatePersistentObject(TEE_OBJECT_STORAGE_PRIVATE,
									(void *)obj_id,
									strlen(obj_id),
									TEE_DATA_FLAG_ACCESS_WRITE | TEE_DATA_FLAG_ACCESS_READ,
									NULL,
									(void *)data_init,
									strlen(data_init),
									&obj);
		if (TEE_SUCCESS != ret) {
			ta_error("TEE_CreatePersistentObject failed. file[%s] data[%s] ret[0x%x]\n", obj_id, data_init, ret);
			return ret;
		} else {
			TEE_CloseObject(obj);
		}

		/* open object */
		ret = TEE_OpenPersistentObject(TEE_OBJECT_STORAGE_PRIVATE,
									   (void *)obj_id,
									   strlen(obj_id),
									   TEE_DATA_FLAG_ACCESS_WRITE | TEE_DATA_FLAG_ACCESS_READ,
									   &obj);
		if (TEE_SUCCESS != ret) {
			ta_error("TEE_OpenPersistentObject fail. file[%s] ret[0x%x]\n", obj_id, ret);
			return ret;
		}
	}

	TEE_MemFill(&buffer, 0x0, sizeof(buffer));
	ret = TEE_ReadObjectData(obj, (void *)&buffer, sizeof(buffer), &count);
	if (TEE_SUCCESS != ret) {
		ta_error("TEE_ReadObjectData failed, ret[0x%x]\n", ret);
		return ret;
	} else {
		ta_debug("Read object OK. buffer[%s] count[0x%x]\n", buffer, count);
	}

	data_append = (char *)TEE_Malloc(size, 0);
	while(loop--) {
		ta_debug("write data loop[%d]\n", loop);

		TEE_MemFill(data_append, 0xff, size);
		snprintf_s(data_append, size, size - 1, "<data_append %d>", loop);
		ret = TEE_WriteObjectData(obj, data_append, size);
		if(TEE_SUCCESS != ret)
		{
			ta_error("TEE_WriteObjectData failed, ret[0x%x]\n", ret);
			return ret;
		}
		TEE_Wait(10);
	}
	TEE_CloseObject(obj);
	TEE_Free((void *)data_append);

	/* open object */
	ret = TEE_OpenPersistentObject(TEE_OBJECT_STORAGE_PRIVATE,
								   (void *)obj_id,
								   strlen(obj_id),
								   TEE_DATA_FLAG_ACCESS_WRITE | TEE_DATA_FLAG_ACCESS_READ,
								   &obj);
	if (TEE_SUCCESS != ret) {
		ta_error("TEE_OpenPersistentObject failed. file[%s] ret[0x%x]\n", obj_id, ret);
		return ret;
	}

	TEE_MemFill(&buffer, 0x0, sizeof(buffer));
	ret = TEE_ReadObjectData(obj, (void *)&buffer, sizeof(buffer), &count);
	if (TEE_SUCCESS != ret) {
		ta_error("TEE_ReadObjectData failed, ret[0x%x]\n", ret);
		return ret;
	} else {
		ta_debug("Read object OK. buffer[%s] count[0x%x]\n", buffer, count);
	}

	TEE_CloseObject(obj);

	DEMO_TASK_FUNC_END();
	return ret;
}


TEE_Result demo_task_write_file(char *file_name, const void *data,
	unsigned int len)
{
	TEE_Result ret;
	TEE_ObjectHandle obj;

	ret = TEE_OpenPersistentObject(
		TEE_OBJECT_STORAGE_PRIVATE,
		file_name,
		strlen(file_name),
		TEE_DATA_FLAG_ACCESS_WRITE,
		&obj
	);

	if (TEE_SUCCESS != ret) {
		if (TEE_ERROR_ITEM_NOT_FOUND == ret) {
			ta_debug("%s not found, create it.\n", file_name);

			ret = TEE_CreatePersistentObject(
				TEE_OBJECT_STORAGE_PRIVATE,
				file_name,
				strlen(file_name),
				TEE_DATA_FLAG_ACCESS_WRITE | TEE_DATA_FLAG_ACCESS_WRITE_META,
				TEE_HANDLE_NULL,
				NULL,
				0,
				&obj);

			if (TEE_SUCCESS != ret) {
				ta_error("TEE_CreatePersistentObject failed, ret[0x%x]\n", ret);
				return ret ;
			}

		} else {
			ta_error("TEE_OpenPersistentObject failed, ret[0x%x]\n", ret);
			return ret;
		}
	}

	ret = TEE_WriteObjectData(obj, (void *)data, len);
	if (TEE_SUCCESS != ret) {
		ta_error("TEE_WriteObjectData failed, ret[0x%x]\n", ret);
	}

	TEE_CloseObject(obj);
	return TEE_SUCCESS;
}

TEE_Result demo_task_read_file(char *file_name, void *data,
	unsigned int len, unsigned int *count)
{
	TEE_Result ret;
	TEE_ObjectHandle obj;

	ret = TEE_OpenPersistentObject(
		TEE_OBJECT_STORAGE_PRIVATE,
		file_name,
		strlen(file_name),
		TEE_DATA_FLAG_ACCESS_READ,
		&obj);

	if (TEE_SUCCESS != ret) {
		ta_error("TEE_OpenPersistentObject failed, ret[0x%x]\n", ret);
		return ret;
	}

	ret = TEE_ReadObjectData(obj, (void *)data, len, count);
	if (TEE_SUCCESS != ret) {
		ta_error("TEE_ReadObjectData failed, ret[0x%x]\n", ret);
	}

	TEE_CloseObject(obj);

	return TEE_SUCCESS;
}

TEE_Result test_storage_read(void)
{
	TEE_Result ret = TEE_SUCCESS;
	unsigned int size = 1024;
	unsigned int *buf_virt_read = 0;
	unsigned int count = 0;

	/* alloc memery for read */
	buf_virt_read = (unsigned int *)TEE_Malloc(size, 0);
	if (!buf_virt_read) {
		ta_error("TEE_Malloc fail\n");
		ret = TEE_ERROR_OUT_OF_MEMORY;
		goto exit1;
	}

	/* read and verify */
	TEE_MemFill(buf_virt_read, 0x0, size);
	count = 0;
	ret = demo_task_read_file(DEMO_TASK_FILE_NAME, (void *)buf_virt_read, size, &count);
	ta_debug("file[%s] count[0x%x] buf[0x%x]\n", DEMO_TASK_FILE_NAME,
		count, buf_virt_read[0]);

	TEE_Free(buf_virt_read);

exit1:

	return ret;
}

/*****************************************************************
Parameters    :  void
Return        :
Description   :  write file, read file, verify data.
*****************************************************************/
TEE_Result test_storage_loop(void)
{
	TEE_Result ret = TEE_SUCCESS;
	int loop = 10;
	int i;
	unsigned int size = 1024;
	unsigned int *buf_virt = 0;
	unsigned int *buf_virt_read = 0;
	unsigned int rand = 63;
	unsigned int count = 0;

	DEMO_TASK_FUNC_START();

	/*
	if (HI_TEE_CIPHER_GetRandomNumber(&rand)) {
		ta_error("HI_TEE_CIPHER_GetRandomNumber fail\n", size);
		ret = TEE_ERROR_GENERIC;
		goto exit1;
	}
	*/

	/* malloc memery form TA heap, MUST size < heap */
	size = ((rand % 2) + 1) * 1024;

	ta_debug("loop[%d] size[0x%x] rand[0x%x]\n", loop, size, rand);

	/* alloc memery for write */
	buf_virt = (unsigned int *)TEE_Malloc(size, 0);
	if (!buf_virt) {
		ta_error("TEE_Malloc fail\n");
		ret = TEE_ERROR_OUT_OF_MEMORY;
		goto exit1;
	}

	/* alloc memery for read */
	buf_virt_read = (unsigned int *)TEE_Malloc(size, 0);
	if (!buf_virt_read) {
		ta_error("TEE_Malloc fail\n");
		ret = TEE_ERROR_OUT_OF_MEMORY;
		goto exit2;
	}

	/* write */
	TEE_MemFill(buf_virt, (rand & 0xff), size);
	while(loop--) {
		ret = demo_task_write_file(DEMO_TASK_FILE_NAME, (void *)buf_virt, size);
		if (TEE_SUCCESS != ret) {
			goto exit3;
		}
	}

	/* read and verify */
	TEE_MemFill(buf_virt_read, 0x0, size);
	count = 0;
	ret = demo_task_read_file(DEMO_TASK_FILE_NAME, (void *)buf_virt_read, size, &count);
	if (TEE_SUCCESS != ret) {
		goto exit3;
	}

	ta_debug("count[0x%x] buf[0x%x][0x%x] rand[0x%x]\n", count, buf_virt[0], buf_virt_read[0], rand);

	ret = TEE_MemCompare(buf_virt, buf_virt_read, size);
	if (ret) {
		ta_error("----verify fail size[0x%x] count[0x%x]-----\n", size, count);

		for (i = 0; i < ((int)size)/4; i++) {
			if (buf_virt[i] == buf_virt_read[i]) {
				continue;
			}

			if ((i % 8) ==0) {
				ta_printf("\n[0x%08x]: ", i);
			}

			ta_printf("[%08x][%08x] ", buf_virt[i], buf_virt_read[i]);
		}

		ret = TEE_ERROR_GENERIC;
	} else {
		ret = TEE_SUCCESS;
	}

	DEMO_TASK_FUNC_END();

exit3:
	TEE_Free(buf_virt_read);

exit2:
	TEE_Free(buf_virt);

exit1:

	return ret;
}

/* Test via TA2TA. Target TA shoud call AddCaller_TA_all() for TA authentication. */
TEE_Result test_ta2ta(void)
{
	TEE_Result ret = TEE_SUCCESS;
	TEE_TASessionHandle ta2ta_session;
	uint32_t ret_origin = 0;
	TEE_Param ta2ta_params[4];
	uint32_t param_types = 0;
	char rand[32] = {0};
	TEE_UUID uuid = TEE_SERVICE_CRYPTO_VERIFY;

	DEMO_TASK_FUNC_START();
	param_types = TEE_PARAM_TYPES(TEE_PARAM_TYPE_NONE,
								  TEE_PARAM_TYPE_NONE,
								  TEE_PARAM_TYPE_NONE,
								  TEE_PARAM_TYPE_NONE);
	ret = TEE_OpenTASession(&uuid, 0, param_types, ta2ta_params,
		&ta2ta_session, &ret_origin);
	if (TEE_SUCCESS != ret) {
		ta_error("TEE_OpenTASession failed\n");
		return ret;
	}

	param_types = TEE_PARAM_TYPES(TEE_PARAM_TYPE_MEMREF_OUTPUT,
								  TEE_PARAM_TYPE_NONE,
								  TEE_PARAM_TYPE_NONE,
								  TEE_PARAM_TYPE_NONE);
	TEE_MemFill(rand, 0, sizeof(rand));
	
	TEE_MemFill(&ta2ta_params, 0, sizeof(ta2ta_params));
    ta2ta_params[0].memref.buffer = rand;
	ta2ta_params[0].memref.size = sizeof(rand);
	ret = TEE_InvokeTACommand(ta2ta_session, 0,
							  0x1, /* CMD_GEN_RANDOM_OPER */
							  param_types, ta2ta_params,
							  &ret_origin);
	if (TEE_SUCCESS != ret) {
		ta_error("TEE_InvokeTACommand failed\n");
		return ret;
	}

	ta_debug("Test ta2ta suc, rand:\n");
	DEMO_TASK_PRINT_HEX(rand, sizeof(rand));

	TEE_CloseTASession(ta2ta_session);
	DEMO_TASK_FUNC_END();
	return ret;
}

TEE_Result test_rpmb(void)
{
#ifdef DEMO_TRUSTEDCORE_TEST
	#define CHECK_DATA_LEN 256
	const char *check_file_path = "rpmb_rw_check.dat";
	uint8_t written_data[CHECK_DATA_LEN] = {0xab};
	uint8_t readed_data[CHECK_DATA_LEN];
	uint32_t readed_size = 0;
	struct rpmb_fs_stat stat = {0};
	struct rpmb_fs_statdisk statdisk = {0};
	TEE_Result result;

	DEMO_TASK_FUNC_START();

	/* get RPMB key status */
	uint32_t status = TEE_RPMB_KEY_Status();
	if (TEE_RPMB_KEY_SUCCESS != status) {
		ta_error("TEE_RPMB_KEY_Status status = %x\n", status);
		if (TEE_RPMB_KEY_NOT_PROGRAM == status) {
			ta_error("RPMB key not program\n");
		} else if (TEE_RPMB_KEY_NOT_MATCH == status) {
			ta_error("RPMB key not match\n");
		}
		return TEE_ERROR_GENERIC;
	}

	/* write date to rpmb_rw_check.dat */
	result = TEE_RPMB_FS_Write(check_file_path, written_data, CHECK_DATA_LEN);
	if (TEE_SUCCESS != result) {
		ta_error("TEE_RPMB_FS_Write result = %x\n", result);
		return result;
	}

	/* read data from rpmb_rw_check.dat */
	result = TEE_RPMB_FS_Read(check_file_path, readed_data, CHECK_DATA_LEN, &readed_size);
	if ((TEE_SUCCESS != result) || (CHECK_DATA_LEN != readed_size)) {
		ta_error("TEE_RPMB_FS_Read result = %x, readed_size = %d\n", result, readed_size);
		return result;
	}

	result = TEE_MemCompare(readed_data, written_data, CHECK_DATA_LEN);
	if (0 != result) {
		ta_error("TEE_MemCompare result = 0x%x\n", result);
		return result;
	}

	/* get file rpmb_rw_check.dat stat */
	result = TEE_RPMB_FS_Stat(check_file_path, &stat);
	if(result != TEE_SUCCESS) {
		ta_error("get file stat error. ret = %x\n", result);
		return result;
	}
	ta_debug("TEE_RPMB_FS_Stat stat.size[0x%x]\n", stat.size);


	/* rename rpmb_rw_check.dat to helloworld */
	result = TEE_RPMB_FS_Rename(check_file_path, "helloworld");
	if (TEE_SUCCESS != result) {
		ta_error("TEE_RPMB_FS_Rename = %x\n", result);
		return result;
	}

	/* stat RPMB partition */
	result = TEE_RPMB_FS_StatDisk(&statdisk);
	if (TEE_SUCCESS != result) {
		ta_error("TEE_RPMB_FS_StatDisk result = %x\n", result);
		return result;
	}
	ta_debug("TEE_RPMB_FS_StatDisk disk_size[0x%x] free_size[0x%x] ta_used_size[0x%x]\n",
		statdisk.disk_size, statdisk.free_size, statdisk.ta_used_size);

	/* delete rpmb_rw_check.dat(helloworld) */
	result = TEE_RPMB_FS_Rm("helloworld");
	if (TEE_SUCCESS != result) {
		ta_error("TEE_RPMB_FS_Rm result = %x\n", result);
		return result;
	}

	/* stat RPMB partition */
	result = TEE_RPMB_FS_StatDisk(&statdisk);
	if (TEE_SUCCESS != result) {
		ta_error("TEE_RPMB_FS_StatDisk result = %x\n", result);
		return result;
	}
	ta_debug("TEE_RPMB_FS_StatDisk disk_size[0x%x] free_size[0x%x] ta_used_size[0x%x]\n",
		statdisk.disk_size, statdisk.free_size, statdisk.ta_used_size);

	/*delete file which attr is "can be earse" */
	result = TEE_RPMB_FS_Erase();
	if (TEE_SUCCESS != result) {
		ta_error("TEE_RPMB_FS_Erase result = %x\n", result);
		return result;
	}

	/* stat RPMB partition */
	result = TEE_RPMB_FS_StatDisk(&statdisk);
	if (TEE_SUCCESS != result) {
		ta_error("TEE_RPMB_FS_StatDisk result = %x\n", result);
		return result;
	}
	ta_debug("TEE_RPMB_FS_StatDisk disk_size[0x%x] free_size[0x%x] ta_used_size[0x%x]\n",
		statdisk.disk_size, statdisk.free_size, statdisk.ta_used_size);

	/* format RPMB partition */
	result = TEE_RPMB_FS_Format();
	if (TEE_SUCCESS != result) {
		ta_error("TEE_RPMB_FS_Format result = %x\n", result);
		return result;
	}

	/* stat RPMB partition */
	result = TEE_RPMB_FS_StatDisk(&statdisk);
	if (TEE_SUCCESS != result) {
		ta_error("TEE_RPMB_FS_StatDisk result = %x\n", result);
		return result;
	}
	ta_debug("TEE_RPMB_FS_StatDisk disk_size[0x%x] free_size[0x%x] ta_used_size[0x%x]\n",
		statdisk.disk_size, statdisk.free_size, statdisk.ta_used_size);

	DEMO_TASK_FUNC_END();

	return result;
#else
	ta_error("not support rpmb api\n");
	return TEE_ERROR_GENERIC;
#endif
}

TEE_Result test_mem_malloc(void)
{
#ifdef DEMO_TRUSTEDCORE_TEST
	char *p = 0;
	uint32_t mem_before, mem_after;
	int i = 1;

	while(1) {
		mem_before = get_mem_usage(false);
		p = (char *)TEE_Malloc(1024 * 4 * i, 0);
		mem_after = get_mem_usage(false);
		if (0 == p) {
			ta_error("TEE_Malloc[%d]KB failed, p[%x], mem[%d.%d%]->[%d.%d%]\n", i * 4, p,
				mem_before / 100, mem_before % 100, mem_after / 100, mem_after % 100);
			break;
		} else {
			ta_debug("TEE_Malloc[%d]KB OK, p[%x], mem[%d.%d%]->[%d.%d%]\n", i * 4, p,
				mem_before / 100, mem_before % 100, mem_after / 100, mem_after % 100);
			TEE_Free((void *)p);
			p = 0;
		}

		i++;
    }

	return TEE_SUCCESS;
#else
	ta_error("not support rpmb api\n");
	return TEE_ERROR_GENERIC;
#endif
}

#ifdef DEMO_TRUSTEDCORE_TEST
#define __rsa__
#define DEMO_TASK_RSA_KEY_SIZE_IN_BITS   (1024)
#define DEMO_TASK_RSA_KEY_SIZE_IN_BYTES   (DEMO_TASK_RSA_KEY_SIZE_IN_BITS / 8)

#define DEMO_TASK_HASH_SHA256_IN_BITS (256)
#define DEMO_TASK_HASH_SHA256_IN_BYTES (DEMO_TASK_HASH_SHA256_IN_BITS / 8)
#define DEMO_TASK_MAX_KEY_SIZE (128)

TEE_Result test_rsa_set_key(TEE_ObjectHandle key_obj)
{
    TEE_Result ret = TEE_ERROR_GENERIC;
	TEE_Attribute *attrs;

    if (!key_obj || !key_obj->Attribute ||! key_obj->ObjectInfo) {
        ta_error("Invalid input\n");
		goto exit1;
    }

	ta_debug("[%d] objectType[0x%x] attributesLen[0x%x] CRTMode[0x%x] dataLen[%d]\n", __LINE__,
		key_obj->ObjectInfo->objectType, key_obj->attributesLen,
		key_obj->CRTMode, key_obj->dataLen);

	/**
	 * Please do not direct TEE_InitRefAttribute() g_rsa_keypair_n to obj->Attribute.
	 * Because TEE_InitRefAttribute only set attribute point to g_rsa_keypair_n,
	 * and TEE_FreeTransientObject will free attribute, so it will be error to free g_rsa_keypair_n.
	 */

	attrs = (TEE_Attribute *)TEE_Malloc(sizeof(TEE_Attribute) * key_obj->attributesLen, 0);
	if (!attrs) {
		ta_error("TEE_Malloc failed\n");
		ret = TEE_ERROR_OUT_OF_MEMORY;
		goto exit1;
	}

	/* set attribute with N/E/D */
	TEE_InitRefAttribute(&attrs[0], TEE_ATTR_RSA_MODULUS, g_rsa_keypair_n, (size_t)sizeof(g_rsa_keypair_n));
	TEE_InitRefAttribute(&attrs[1], TEE_ATTR_RSA_PUBLIC_EXPONENT, g_rsa_keypair_e, (size_t)sizeof(g_rsa_keypair_e));
	if (TEE_TYPE_RSA_KEYPAIR == key_obj->ObjectInfo->objectType) {
		TEE_InitRefAttribute(&attrs[2], TEE_ATTR_RSA_PRIVATE_EXPONENT, g_rsa_keypair_d, (size_t)sizeof(g_rsa_keypair_d));
	}

	/* populate attribute to object */
	ret = TEE_PopulateTransientObject(key_obj, attrs, key_obj->attributesLen);
	if (ret != TEE_SUCCESS) {
		ta_error("TEE_PopulateTransientObject failed, ret[0x%x]\n", ret);
		goto exit2;
	}

exit2:
	TEE_Free(attrs);

exit1:
	return ret;
}

void test_rsa_key_dump(TEE_ObjectHandle key_obj)
{
	unsigned int i;
	ta_printf("___________[%s][%d]_________\n", __func__, __LINE__);

	ta_printf("objectType[0x%x] attributesLen[0x%x] CRTMode[0x%x] dataLen[%d]",
		key_obj->ObjectInfo->objectType, key_obj->attributesLen,
		key_obj->CRTMode, key_obj->dataLen);
	for (i = 0; i < key_obj->attributesLen; i++) {
		ta_printf("\nAttribute[%d]: ID[0x%x] Len[%d] buffer[0x%08x]\n", i,
			key_obj->Attribute[i].attributeID,
			key_obj->Attribute[i].content.ref.length,
			key_obj->Attribute[i].content.ref.buffer);
		DEMO_TASK_PRINT_HEX(key_obj->Attribute[i].content.ref.buffer,
			key_obj->Attribute[i].content.ref.length);
    }
}

TEE_Result demo_task_rsa_operate(TEE_ObjectHandle key_obj, unsigned int algorithm,
	unsigned int mode, unsigned int key_size,
	void *src, unsigned int src_len,
	void *dst, unsigned int *dst_len) {

	TEE_Result ret = TEE_ERROR_GENERIC;
	TEE_OperationHandle op = 0;

	ret = TEE_AllocateOperation(&op, algorithm, mode, key_size);
	if (TEE_SUCCESS != ret) {
		ta_error("TEE_AllocateOperation failed, ret[0x%x]\n", ret);
		goto exit1;
	}

	if (key_obj) { /* digest do not need to set key */
		ret = TEE_SetOperationKey(op, key_obj);
		if(TEE_SUCCESS != ret) {
			ta_error("TEE_SetOperationKey failed, ret[0x%x]\n", ret);
			goto exit2;
		}
	}

	switch (mode) {
		case TEE_MODE_ENCRYPT:
			ret = TEE_AsymmetricEncrypt(op, NULL, 0, src, src_len, dst, dst_len);
			break;
		case TEE_MODE_DECRYPT:
			ret = TEE_AsymmetricDecrypt(op, NULL, 0, src, src_len, dst, dst_len);
			break;
		case TEE_MODE_SIGN:
			ret = TEE_AsymmetricSignDigest(op, NULL, 0, src, src_len, dst, dst_len);
			break;
		case TEE_MODE_VERIFY:
			ret = TEE_AsymmetricVerifyDigest(op, NULL, 0, src, src_len, dst, *dst_len);
			break;
		case TEE_MODE_DIGEST:
			ret = TEE_DigestUpdate(op, src, src_len);
			if (TEE_SUCCESS != ret) {
				ta_error("TEE_DigestUpdate failed, ret[0x%x]\n", ret);
				break;
			}
			ret = TEE_DigestDoFinal(op, NULL, 0, dst, dst_len);
			break;
		default:
			ret = TEE_ERROR_BAD_PARAMETERS;
			break;
	}

exit2:
	TEE_FreeOperation(op);

exit1:
	return ret;
}

TEE_Result test_rsa_key_check(TEE_ObjectHandle key_obj)
{
	unsigned char in_data[] = {
		'1','2','3','4','5','6','7','8',
		'9','a','b','c','d','e','f','g'};

	unsigned char *out_hash, *out_encrypt, *out_decrypt;
	size_t in_size, out_size, hash_size;
	TEE_Result ret = TEE_ERROR_GENERIC;

	in_size = sizeof(in_data);
	hash_size = DEMO_TASK_HASH_SHA256_IN_BYTES;
	out_hash = (unsigned char *)TEE_Malloc(hash_size, 0);
	if (!out_hash) {
		ta_error("TEE_Malloc failed\n");
		ret = TEE_ERROR_OUT_OF_MEMORY;
		goto exit1;
	}

	/* DEMO_TASK_PRINT_HEX(in_data, in_size); */
	out_encrypt = (unsigned char *)TEE_Malloc(DEMO_TASK_MAX_KEY_SIZE, 0);
	if (!out_encrypt) {
		ta_error("TEE_Malloc failed\n");
		ret = TEE_ERROR_OUT_OF_MEMORY;
		goto exit2;
	}

	out_decrypt = (unsigned char *)TEE_Malloc(DEMO_TASK_MAX_KEY_SIZE, 0);
	if (!out_decrypt) {
		ta_error("TEE_Malloc failed\n");
		ret = TEE_ERROR_OUT_OF_MEMORY;
		goto exit3;
	}

	/* digest */
	ret = demo_task_rsa_operate(NULL, TEE_ALG_SHA256, TEE_MODE_DIGEST, 0,
		in_data, in_size, out_hash, &hash_size);
	if (TEE_SUCCESS != ret) {
		ta_error("Digest test Error!\n");
		goto exit4;
	}
	ta_debug("Digest suc, hash size[0x%x]\n", hash_size);
	/* DEMO_TASK_PRINT_HEX(out_hash, hash_size); */

	/* encrypt */
	out_size = DEMO_TASK_MAX_KEY_SIZE;
	ret = demo_task_rsa_operate(key_obj, TEE_ALG_RSAES_PKCS1_V1_5, TEE_MODE_ENCRYPT,
		DEMO_TASK_MAX_KEY_SIZE, out_hash, hash_size, out_encrypt, &out_size);
	if (TEE_SUCCESS != ret) {
		ta_error("RSA encrypt faile, ret[0x%x]\n", ret);
		goto exit4;
	}
	ta_debug("RSA encrypt suc, size[0x%x]\n", out_size);

	/* decrypt */
	if (TEE_TYPE_RSA_KEYPAIR == key_obj->ObjectInfo->objectType) {
		in_size = out_size;
		out_size = DEMO_TASK_MAX_KEY_SIZE;
		ret = demo_task_rsa_operate(key_obj, TEE_ALG_RSAES_PKCS1_V1_5, TEE_MODE_DECRYPT,
			DEMO_TASK_MAX_KEY_SIZE, out_encrypt, in_size, out_decrypt, &out_size);
		if (TEE_SUCCESS != ret) {
			ta_error("RSA decrypt faile, ret[0x%x]\n", ret);
			goto exit4;
		}
		ta_debug("RSA decrypt suc, size[0x%x]\n", out_size);

		/* compare data */
		if (0 != TEE_MemCompare(out_hash, out_decrypt, hash_size)) {
			ta_error("RSA memcmp failed\n origin data:\n");
			DEMO_TASK_PRINT_HEX(out_hash, hash_size);
			ta_printf("target data:\n");
			DEMO_TASK_PRINT_HEX(out_encrypt, out_size);
			ret = TEE_ERROR_GENERIC;
			goto exit4;
		}
		ta_debug("Input and decrypt data memcmp suc\n");
	}

	/* sign */
	if (TEE_TYPE_RSA_KEYPAIR == key_obj->ObjectInfo->objectType) {
		out_size = DEMO_TASK_MAX_KEY_SIZE;
		ret = demo_task_rsa_operate(key_obj, TEE_ALG_RSASSA_PKCS1_V1_5_SHA256, TEE_MODE_SIGN,
			DEMO_TASK_MAX_KEY_SIZE, out_hash, hash_size, out_encrypt, &out_size);
		if (TEE_SUCCESS != ret) {
			ta_error("Sign failed, ret[0x%x]\n", ret);
			goto exit4;
		}
		ta_debug("Sign suc, size[0x%x]\n", out_size);
		/* DEMO_TASK_PRINT_HEX(out_encrypt, out_size); */
	} else {
		/* pubkey use an exist sign data to verify */
		TEE_MemMove(out_encrypt, g_rsa_sign_data, sizeof(g_rsa_sign_data));
	}

	/* verify */
	out_size = DEMO_TASK_MAX_KEY_SIZE;
	ret = demo_task_rsa_operate(key_obj, TEE_ALG_RSASSA_PKCS1_V1_5_SHA256, TEE_MODE_VERIFY,
		DEMO_TASK_MAX_KEY_SIZE, out_hash, hash_size, out_encrypt, &out_size);
	if (TEE_SUCCESS != ret) {
		ta_error("Verify failed, ret[0x%x]\n", ret);
		goto exit4;
	}
	ta_debug("Verify suc, size[0x%x]\n", out_size);

exit4:
	TEE_Free(out_decrypt);

exit3:
	TEE_Free(out_encrypt);

exit2:
	TEE_Free(out_hash);

exit1:
	return ret;
}
TEE_Result test_storage_key_process(int is_exist_key)
{
	TEE_Result ret = TEE_ERROR_GENERIC;
	TEE_ObjectHandle key_obj;
	TEE_ObjectHandle key_obj_read;
	TEE_ObjectHandle pst_obj;
	TEE_ObjectHandle pst_obj_read;
	unsigned int i;

	ret = TEE_AllocateTransientObject(TEE_TYPE_RSA_KEYPAIR,
		DEMO_TASK_RSA_KEY_SIZE_IN_BYTES, &key_obj);
	if (TEE_SUCCESS != ret) {
		ta_error("TEE_AllocateTransientObject failed, ret[0x%x]\n", ret);
		return ret;
	}

	if (DEMO_TASK_RSA_KEY_EXIST == is_exist_key) {
		ret = test_rsa_set_key(key_obj);
	} else {
		/* generate key */
		ret = TEE_GenerateKey(key_obj, DEMO_TASK_RSA_KEY_SIZE_IN_BYTES, NULL, 0);
	}
	if (ret != TEE_SUCCESS) {
		ta_error("TEE_GenerateKey failed, ret[0x%x]\n", ret);
		goto exit1;
	}

	/* write key to file */
	/* create persistent object to write key */
	ret = TEE_CreatePersistentObject(storageID, DEMO_TASK_RSA_KEY_FILE_NAME,
		strlen(DEMO_TASK_RSA_KEY_FILE_NAME),
		TEE_DATA_FLAG_ACCESS_WRITE, key_obj, NULL, 0,
		&pst_obj);
	if (TEE_SUCCESS != ret) {
	   ta_error("TEE_CreatePersistentObject failed, ret[0x%x]\n", ret);
	   goto exit1;
	}
	TEE_CloseObject(pst_obj);

	/* open persistent object, read key from file */
	ret = TEE_OpenPersistentObject(storageID, DEMO_TASK_RSA_KEY_FILE_NAME,
		strlen(DEMO_TASK_RSA_KEY_FILE_NAME), TEE_DATA_FLAG_ACCESS_READ,
		&pst_obj_read);
	if (TEE_SUCCESS != ret) {
		ta_error("TEE_OpenPersistentObject failed, ret[0x%x]\n", ret);
		goto exit1;
	}

	ret = TEE_AllocateTransientObject(TEE_TYPE_RSA_KEYPAIR,
		DEMO_TASK_RSA_KEY_SIZE_IN_BYTES, &key_obj_read);
	if (TEE_SUCCESS != ret) {
		ta_error("TEE_AllocateTransientObject failed, ret[0x%x]\n", ret);
		goto exit2;
	}

	/* copy attributes form persistent object to transient object */
	TEE_CopyObjectAttributes(key_obj_read, pst_obj_read);

	for (i = 0; i < key_obj->attributesLen; i++) {
		if (key_obj->Attribute[i].attributeID != pst_obj_read->Attribute[i].attributeID) {
			ta_error("attributeID error\n");
			break;
		}

		if (key_obj->Attribute[i].content.ref.length != pst_obj_read->Attribute[i].content.ref.length) {
			ta_error("length error\n");
			break;
		}

        /* compare key attributes */
		if (TEE_MemCompare(key_obj->Attribute[i].content.ref.buffer,
			pst_obj_read->Attribute[i].content.ref.buffer,
			key_obj->Attribute[i].content.ref.length)) {
				ta_error("TEE_MemCompare failed\n");
			break;
		}
    }

	if (i != key_obj->attributesLen) {
		ta_error("Compare attributes[%d] failed\n", i);
		test_rsa_key_dump(key_obj);
		test_rsa_key_dump(key_obj_read);
	}

	/* sign/verfiy/encrypt/decrypt */
	ret = test_rsa_key_check(key_obj_read);
	if (TEE_SUCCESS != ret) {
		ta_error("test_rsa_key failed, ret[0x%x]\n", ret);
		goto exit3;
    }

exit3:
	TEE_FreeTransientObject(key_obj_read);
exit2:
	TEE_CloseObject(pst_obj_read);
exit1:
	TEE_FreeTransientObject(key_obj);

	return ret;
}

TEE_Result test_storage_key(void)
{
	TEE_Result ret = TEE_ERROR_GENERIC;

	ret = test_storage_key_process(DEMO_TASK_RSA_KEY_NOT_EXIST);
	if (ret != TEE_SUCCESS) {
		ta_error("test_storage_key_process with generate key failed, ret[0x%x]\n", ret);
	} else {
		ta_debug("test_storage_key_process with generate key suc\n");
	}

	ret = test_storage_key_process(DEMO_TASK_RSA_KEY_EXIST);
	if (ret != TEE_SUCCESS) {
		ta_error("test_storage_key_process with an exist key failed, ret[0x%x]\n", ret);
	} else {
		ta_debug("test_storage_key_process with an exist key suc\n");
	}

	return ret;
}

TEE_Result test_rsa_process(int is_crt, int is_exist_key, unsigned int objectType)
{
	TEE_Result ret = TEE_ERROR_GENERIC;
	TEE_ObjectHandle key_obj;

    ret = TEE_AllocateTransientObject(objectType,
		DEMO_TASK_RSA_KEY_SIZE_IN_BYTES, &key_obj);
    if (ret != TEE_SUCCESS) {
		ta_error("TEE_AllocateTransientObject failed, ret[0x%x]\n", ret);
		return ret;
    }

	if (DEMO_TASK_RSA_MODE_CRT == is_crt) {
		key_obj->CRTMode = 1;
	}

	if (DEMO_TASK_RSA_KEY_EXIST == is_exist_key) {
		ret = test_rsa_set_key(key_obj);
	} else {
		/* generate key */
		ret = TEE_GenerateKey(key_obj, DEMO_TASK_RSA_KEY_SIZE_IN_BYTES, NULL, 0);
	}
    if (ret != TEE_SUCCESS) {
		ta_error("TEE_GenerateKey failed, ret[0x%x]\n", ret);
		goto exit1;
    }

	ret = test_rsa_key_check(key_obj);
	if (ret != TEE_SUCCESS) {
		ta_error("test_rsa_key failed, ret[0x%x]\n", ret);
		test_rsa_key_dump(key_obj);
		goto exit1;
    }

exit1:
	TEE_FreeTransientObject(key_obj);

	return ret;
}

unsigned int test_rsa_pub_key(void)
{
	TEE_Result ret = TEE_SUCCESS;
	TEE_ObjectHandle obj = TEE_HANDLE_NULL;
	TEE_OperationHandle opr = TEE_HANDLE_NULL;
	TEE_Attribute attrs[2];

    char *output = g_encrypted_data;
    unsigned int outputLen = sizeof(g_encrypted_data);
    char *input = g_hash_data;
    unsigned int inputLen = sizeof(g_hash_data);

	ret = TEE_AllocateTransientObject(TEE_TYPE_RSA_PUBLIC_KEY ,DEMO_TASK_RSA_KEY_SIZE_IN_BYTES, &obj);
	if (ret != TEE_SUCCESS) {
		ta_error("TEE_AllocateTransientObject failed, ret[0x%x]\n", ret);
		goto exit1;
	}

	/**
	 * Please do not direct TEE_InitRefAttribute() g_rsa_pub_key_n to obj->Attribute.
	 * Because TEE_InitRefAttribute only set attribute point to g_rsa_pub_key_n,
	 * and TEE_FreeTransientObject will free attribute, so it will be error to free g_rsa_pub_key_n.
	 */

	/* set attribute */
	TEE_MemFill(attrs, 0, sizeof(attrs));
	TEE_InitRefAttribute(&attrs[0], TEE_ATTR_RSA_MODULUS, g_rsa_pub_key_n, (size_t)sizeof(g_rsa_pub_key_n));
	TEE_InitRefAttribute(&attrs[1], TEE_ATTR_RSA_PUBLIC_EXPONENT, g_rsa_pub_key_e, (size_t)sizeof(g_rsa_pub_key_e));

	/* populate attribute to object */
	ret = TEE_PopulateTransientObject(obj, (TEE_Attribute *)&attrs, obj->attributesLen);
	if (ret != TEE_SUCCESS) {
		ta_error("TEE_PopulateTransientObject failed, ret[0x%x]\n", ret);
		goto exit2;
	}

	/* test_rsa_key_dump(obj); */

	ret = TEE_AllocateOperation(&opr, TEE_ALG_RSA_NOPAD, TEE_MODE_ENCRYPT, DEMO_TASK_RSA_KEY_SIZE_IN_BYTES);
	if (ret != TEE_SUCCESS) {
		ta_error("TEE_AllocateOperation failed failed, ret[0x%x]\n", ret);
		goto exit2;
	}

	ret = TEE_SetOperationKey(opr, obj);
	if (ret != TEE_SUCCESS) {
		ta_error("TEE_SetOperationKey failed failed, ret[0x%x]\n", ret);
		goto exit3;
	}

	ret = TEE_AsymmetricEncrypt(opr, NULL, 0, input, inputLen, output, &outputLen);
	if (ret != TEE_SUCCESS) {
		ta_error("TEE_AsymmetricEncrypt failed, ret[0x%x]\n", ret);
		goto exit3;
	}

exit3:
	TEE_FreeOperation(opr);
exit2:
	TEE_FreeTransientObject(obj);
exit1:

	return ret;
}

TEE_Result test_rsa(void)
{
	TEE_Result ret = TEE_ERROR_GENERIC;

	DEMO_TASK_FUNC_START();
	ret = test_rsa_process(DEMO_TASK_RSA_MODE_CRT, DEMO_TASK_RSA_KEY_NOT_EXIST, TEE_TYPE_RSA_KEYPAIR);
	if (TEE_SUCCESS != ret) {
		ta_error("test_rsa_key with generate crt key pair failed, ret[0x%x]\n", ret);
	} else {
		ta_debug("test_rsa_key with generate crt key pair suc\n");
	}

	ret = test_rsa_process(DEMO_TASK_RSA_MODE_NOT_CRT, DEMO_TASK_RSA_KEY_NOT_EXIST, TEE_TYPE_RSA_KEYPAIR);
	if (TEE_SUCCESS != ret) {
		ta_error("test_rsa_key with generate key pair failed, ret[0x%x]\n", ret);
	} else {
		ta_debug("test_rsa_key with generate key pair suc\n");
	}

	ret = test_rsa_process(DEMO_TASK_RSA_MODE_NOT_CRT, DEMO_TASK_RSA_KEY_EXIST, TEE_TYPE_RSA_KEYPAIR);
	if (TEE_SUCCESS != ret) {
		ta_error("test_rsa_key with an exist key pair failed, ret[0x%x]\n", ret);
	} else {
		ta_debug("test_rsa_key with an exist key pair suc\n");
	}

	ret = test_rsa_process(DEMO_TASK_RSA_MODE_NOT_CRT, DEMO_TASK_RSA_KEY_EXIST, TEE_TYPE_RSA_PUBLIC_KEY);
	if (TEE_SUCCESS != ret) {
		ta_error("test_rsa_key with an exist public key failed, ret[0x%x]\n", ret);
	} else {
		ta_debug("test_rsa_key with an exist public key suc\n");
	}

	ret = test_rsa_pub_key();
	if (TEE_SUCCESS != ret) {
		ta_error("test_rsa_pub_key failed, ret[0x%x]\n", ret);
	} else {
		ta_debug("test_rsa_pub_key suc\n");
	}

	DEMO_TASK_FUNC_END();

	return ret;
}
#endif

#define __time__
/* 0: TA Global variable, not support reboot, corresponding fast
 * 1: REE FS secure storage, support reboot, corresponding slow
 */
#define HISI_PERSISTENT_TIME_WITH_REE_FS     0
#define HISI_PERSISTENT_TIME_FILE_NAME "hisi_ta_persistent_time.txt"
#define TEE_TIME_MILLIS_BASE    1000

#define TEE_TIME_LT(t1, t2)				\
    (((t1).seconds == (t2).seconds) ?			\
        ((t1).millis < (t2).millis) :			\
        ((t1).seconds < (t2).seconds))

#define TEE_TIME_LE(t1, t2)				\
    (((t1).seconds == (t2).seconds) ?			\
        ((t1).millis <= (t2).millis) :			\
        ((t1).seconds <= (t2).seconds))

#define TEE_TIME_ADD(t1, t2, dst) do {                      \
        (dst).seconds = (t1).seconds + (t2).seconds;        \
        (dst).millis = (t1).millis + (t2).millis;           \
        if ((dst).millis >= TEE_TIME_MILLIS_BASE) {         \
            (dst).seconds++;                                \
            (dst).millis -= TEE_TIME_MILLIS_BASE;           \
        }                                                   \
    } while (0)

#define TEE_TIME_SUB(t1, t2, dst) do {                      \
        (dst).seconds = (t1).seconds - (t2).seconds;        \
        if ((t1).millis < (t2).millis) {                    \
            (dst).seconds--;                                \
            (dst).millis = (t1).millis + TEE_TIME_MILLIS_BASE - (t2).millis;\
        } else {                                            \
            (dst).millis = (t1).millis - (t2).millis;       \
        }                                                   \
    } while (0)

typedef struct {
	TEE_Time offs;
	bool positive;
} tee_ta_persistent_time;

#if (HISI_PERSISTENT_TIME_WITH_REE_FS)
TEE_Result write_ta_pt(tee_ta_persistent_time *ta_pt)
{
	TEE_Result ret = TEE_SUCCESS;
	TEE_ObjectHandle obj;

	ret = TEE_CreatePersistentObject(TEE_OBJECT_STORAGE_PRIVATE,
		HISI_PERSISTENT_TIME_FILE_NAME,
		strlen(HISI_PERSISTENT_TIME_FILE_NAME),
		TEE_DATA_FLAG_ACCESS_WRITE, NULL,
		ta_pt,
		sizeof(tee_ta_persistent_time),
		&obj);
	if (TEE_SUCCESS != ret) {
	   ta_error("Write persistent time failed, ret[0x%x]\n", ret);
	}

	TEE_CloseObject(obj);

	return ret;
}

TEE_Result read_ta_pt(tee_ta_persistent_time *ta_pt)
{
	TEE_Result ret = TEE_SUCCESS;
	TEE_ObjectHandle obj;
	unsigned int count = 0;

	ret = TEE_OpenPersistentObject(TEE_OBJECT_STORAGE_PRIVATE,
		HISI_PERSISTENT_TIME_FILE_NAME,
		strlen(HISI_PERSISTENT_TIME_FILE_NAME),
		TEE_DATA_FLAG_ACCESS_READ,
		&obj);

	if (TEE_SUCCESS != ret) {
		if (TEE_ERROR_ITEM_NOT_FOUND == ret) {
			ta_error("Persistent time not set, ret[0x%x]\n", ret);
			return TEE_ERROR_TIME_NOT_SET;
		}
		ta_error("Open persistent time failed, ret[0x%x]\n", ret);
		return ret;
	}

	ret = TEE_ReadObjectData(obj, (void *)ta_pt, sizeof(tee_ta_persistent_time), &count);
	if (TEE_SUCCESS != ret) {
		ta_error("Read persistent time failed, ret[0x%x]\n", ret);
		TEE_CloseObject(obj);
		return ret;
	}
	TEE_CloseObject(obj);
	
	return ret;
}
#else
tee_ta_persistent_time g_ta_pt = {{0}, false};
TEE_Result write_ta_pt(tee_ta_persistent_time *ta_pt)
{
	TEE_MemMove(&g_ta_pt, ta_pt, sizeof(tee_ta_persistent_time));
	return TEE_SUCCESS;
}

TEE_Result read_ta_pt(tee_ta_persistent_time *ta_pt)
{
	if (!TEE_MemCompare(ta_pt, &g_ta_pt, sizeof(tee_ta_persistent_time))) {
			ta_error("Persistent time not set\n");
			return TEE_ERROR_TIME_NOT_SET;
	}
	TEE_MemMove(ta_pt, &g_ta_pt, sizeof(tee_ta_persistent_time));
	return TEE_SUCCESS;
}
#endif

TEE_Result HISI_SetTAPersistentTime(TEE_Time *time)
{
	tee_ta_persistent_time pst_time;
	TEE_Time sys_time;

	TEE_MemFill(&pst_time, 0, sizeof(tee_ta_persistent_time));
	if (time->millis >= TEE_TIME_MILLIS_BASE)
		return TEE_ERROR_BAD_PARAMETERS;

	TEE_GetSystemTime(&sys_time);

	if (TEE_TIME_LT(sys_time, *time)) {
		TEE_TIME_SUB(*time, sys_time, pst_time.offs);
		pst_time.positive = true;
	} else {
		TEE_TIME_SUB(sys_time, *time, pst_time.offs);
		pst_time.positive = false;
	}

	return write_ta_pt(&pst_time);;
}

TEE_Result HISI_GetTAPersistentTime(TEE_Time *time)
{
	TEE_Result ret = TEE_SUCCESS;
	tee_ta_persistent_time pst_time;
	TEE_Time sys_time;
	TEE_Time tmp_time;

	TEE_MemFill(&pst_time, 0, sizeof(tee_ta_persistent_time));
	ret = read_ta_pt(&pst_time);
	if (TEE_SUCCESS != ret) {
	   return ret;
	}

	TEE_GetSystemTime(&sys_time);

	if (pst_time.positive) {
		TEE_TIME_ADD(sys_time, pst_time.offs, tmp_time);

		/* Detect wrapping, the wrapped time should be returned. */
		if (TEE_TIME_LT(tmp_time, sys_time))
			ret = TEE_ERROR_OVERFLOW;
	} else {
		TEE_TIME_SUB(sys_time, pst_time.offs, tmp_time);

		/* Detect wrapping, the wrapped time should be returned. */
		if (TEE_TIME_LE(sys_time, tmp_time))
			ret = TEE_ERROR_OVERFLOW;
	}

	*time = tmp_time;
	return ret;
}

TEE_Result test_ta_persistent_time(void)
{
	TEE_Result ret = TEE_ERROR_GENERIC;
	TEE_Time time_get_first = {0};
	TEE_Time time_get_second = {0};
	TEE_Time time_set = {100, 500};

	ret = HISI_GetTAPersistentTime(&time_get_first); /* TEE_GetTAPersistentTime */
	if (TEE_SUCCESS != ret) {
		if (TEE_ERROR_TIME_NOT_SET != ret  && TEE_ERROR_OVERFLOW != ret) {
			ta_error("TEE_GetTAPersistentTime failed, ret[0x%x]\n", ret);
			return ret;
		}
	}

	ret = HISI_SetTAPersistentTime(&time_set); /* TEE_SetTAPersistentTime */
	if (TEE_SUCCESS != ret) {
		ta_error("TEE_SetTAPersistentTime failed, ret[0x%x]\n", ret);
		return ret;
	}

	TEE_Wait(1000);

	ret = HISI_GetTAPersistentTime(&time_get_second); /* TEE_GetTAPersistentTime */
	if (TEE_SUCCESS != ret) {
		ta_error("TEE_GetTAPersistentTime failed, ret[0x%x]\n", ret);
		return ret;
	}
	ta_debug("time_get_first[%d][%d] time_set[%d][%d]  time_get_second[%d][%d]\n",
		time_get_first.seconds, time_get_first.millis,
		time_set.seconds, time_set.millis,
		time_get_second.seconds, time_get_second.millis);

	return ret;
}

TEE_Result test_ta_persistent_time_api(void)
{
	TEE_Result ret = TEE_ERROR_GENERIC;
	TEE_Time ta_time = {0};
	TEE_Time sys_time;

	TEE_GetSystemTime(&sys_time);

	TEE_Time null_time = {0, 0};
	TEE_Time normal_time = {100, 500};
	TEE_Time wrap_time = {0xffffffff, 999};

	ret = HISI_GetTAPersistentTime(&ta_time);
	switch (ret) {
	case TEE_SUCCESS:
		ta_debug("TA time [%d][%d]\n", ta_time.seconds, ta_time.millis);
		break;
	case TEE_ERROR_OVERFLOW:
		ta_debug("TA time overflowed [%d][%d]\n", ta_time.seconds, ta_time.millis);
		break;
	case TEE_ERROR_TIME_NOT_SET:
		ta_error("TA time not set\n");
		break;
	case TEE_ERROR_TIME_NEEDS_RESET:
		ta_error("TA time needs reset\n");
		break;
	default:
		return ret;
	}

	/* test null time */
	ta_debug("__________test null time_______\n");
	ret = HISI_SetTAPersistentTime(&null_time);
	if (TEE_SUCCESS != ret) {
		ta_error("TEE_SetTAPersistentTime failed, ret[0x%x]\n", ret);
		return ret;
	}

	ret = HISI_GetTAPersistentTime(&ta_time);
	if (TEE_SUCCESS != ret) {
		ta_error("TEE_GetTAPersistentTime failed, ret[0x%x]\n", ret);
		return ret;
	}
	ta_debug("TA time [%d][%d]\n", ta_time.seconds, ta_time.millis);

	/*
	 * The time between TEE_SetTAPersistentTime() and
	 * TEE_GetTAPersistentTime() should be much less than 1 second, in fact
	 * it's not even a millisecond.
	 */
	if (ta_time.seconds > 1 || ta_time.millis >= 1000) {
		ta_error("Unexpected TA time [%d][%d]\n", ta_time.seconds, ta_time.millis);
		return TEE_ERROR_BAD_STATE;
	}

	/* test normal time */
	ta_debug("__________test normal time_______\n");
	ret = HISI_GetTAPersistentTime(&ta_time); /* TEE_GetTAPersistentTime */
	if (TEE_SUCCESS != ret) {
		ta_error("TEE_GetTAPersistentTime failed, ret[0x%x]\n", ret);
		return ret;
	}
	ta_debug("TA time [%d][%d]\n", ta_time.seconds, ta_time.millis);

	ret = HISI_SetTAPersistentTime(&normal_time); /* TEE_SetTAPersistentTime */
	if (TEE_SUCCESS != ret) {
		ta_error("TEE_SetTAPersistentTime failed, ret[0x%x]\n", ret);
		return ret;
	}

	TEE_Wait(1000);

	ret = HISI_GetTAPersistentTime(&ta_time); /* TEE_GetTAPersistentTime */
	if (TEE_SUCCESS != ret) {
		ta_error("TEE_GetTAPersistentTime failed, ret[0x%x]\n", ret);
		return ret;
	}
	ta_debug("TA time [%d][%d]\n", ta_time.seconds, ta_time.millis);

	/* test wrap time */
	ta_debug("__________test wrap time_______\n");
	ret = HISI_SetTAPersistentTime(&wrap_time);
	if (TEE_SUCCESS != ret) {
		ta_error("TEE_SetTAPersistentTime wrap: failed\n");
		return ret;
	}

	ret = TEE_Wait(1000);
	if (TEE_SUCCESS != ret)
		ta_error("TEE_Wait failed, ret[0x%x]\n", ret);

	ret = HISI_GetTAPersistentTime(&ta_time);
	if (TEE_ERROR_OVERFLOW != ret) {
		ta_error("TEE_GetTAPersistentTime: failed\n");
		return TEE_ERROR_BAD_STATE;
	}
	ta_debug("TA time [%d][%d]\n", ta_time.seconds, ta_time.millis);

	if (ta_time.seconds > sys_time.seconds) {
		ta_error("Unexpected wrapped time [%d][%d] (sys_time [%d][%d])\n",
		     ta_time.seconds, ta_time.millis,
		     sys_time.seconds, sys_time.millis);
		return TEE_ERROR_BAD_STATE;
	}

	ret = TEE_SUCCESS;
	return ret;
}

TEE_Result test_time_api(void)
{
	TEE_Result ret = TEE_SUCCESS;
	TEE_Time sys_time;
	TEE_Time ree_time;
	TEE_GetSystemTime(&sys_time);
	ta_debug("TEE_GetSystemTime [%d][%d]\n", sys_time.seconds, sys_time.millis);

	TEE_GetREETime(&ree_time);
	ta_debug("TEE_GetREETime [%d][%d]\n", ree_time.seconds, ree_time.millis);

	ret = test_ta_persistent_time();
	if (TEE_SUCCESS != ret) {
		ta_error("test_ta_persistent_time failed, ret[0x%x]\n", ret);
		return ret;
	}

#if 0
	ret = test_ta_persistent_time_api();
	if (TEE_SUCCESS != ret) {
		ta_error("test_ta_persistent_time_api failed, ret[0x%x]\n", ret);
		return ret;
	}
#endif
	return ret;
}

TEE_Result TA_CreateEntryPoint(void)
{
	return AddCaller_CA_exec("default", 0);
}

TEE_Result TA_OpenSessionEntryPoint(uint32_t paramTypes, TEE_Param params[4], void **sessionContext)
{
	(void)paramTypes;
	(void)params;
	(void)sessionContext;
	return TEE_SUCCESS;
}

TEE_Result TA_InvokeCommandEntryPoint(void *sessionContext, uint32_t commandID, uint32_t paramTypes, TEE_Param params[4])
{
	TEE_Result ret = TEE_ERROR_BAD_PARAMETERS;
	uint32_t mem_usage_before = 0;
	uint32_t mem_usage_after = 0;
	
	(void)paramTypes;
	(void)sessionContext;

#ifdef DEMO_TRUSTEDCORE_TEST
	mem_usage_before = get_mem_usage(false);
#endif

	switch(commandID) {
	case HISI_DEMO_CMD_HELLO:
		ta_debug("Hello, Secure World! static_var[0x%x][0x%x] normal_var[0x%x][0x%x]\n",
			&static_var, static_var, &normal_var, normal_var);
		static_var++;
		normal_var++;
		params[3].value.a = 0x12345678;
		params[3].value.b = 0x87654321;
		ret = TEE_SUCCESS;
		break;
	case HISI_DEMO_CMD_STORAGE:
		ret = test_storage_sample();
		ret += test_storage_api();
		break;
	case HISI_DEMO_CMD_TA2TA:
		ret = test_ta2ta();
		break;
	case HISI_DEMO_CMD_RPMB:
		ret = test_rpmb();
		break;
	case HISI_DEMO_CMD_WR_RPMB_KEY:
		ta_error("not support write RPMB KEY\n");
		break;
	case HISI_DEMO_CMD_STORAGE_PD:
		ret = test_storage_power_down();
		break;
	case HISI_DEMO_CMD_STORAGE_LOOP:
		ret = test_storage_loop();
		break;
	case HISI_DEMO_CMD_STORAGE_READ:
		ret = test_storage_read();
		break;
#ifdef DEMO_TRUSTEDCORE_TEST
	case HISI_DEMO_CMD_MALLOC:
		ret = test_mem_malloc();
		break;
	case HISI_DEMO_CMD_RSA:
		ret = test_rsa();
		ret += test_storage_key();
		break;
#endif
	case HISI_DEMO_CMD_TIME:
		ret = test_time_api();
		break;
	default:
		ta_debug("Invalid command!\n");
		break;
	}

#ifdef DEMO_TRUSTEDCORE_TEST
	mem_usage_after = get_mem_usage(false);
	if (mem_usage_before != mem_usage_after) {
		ta_error("Memory leak from [%d.%d%] to [%d.%d%] \n",
			mem_usage_before / 100, mem_usage_before % 100,
			mem_usage_after / 100, mem_usage_after % 100);
	}
#endif

	if (TEE_SUCCESS == ret) {
		ta_debug("Invoke command[0x%x] suc\n", commandID);
	} else {
		ta_error("Invoke command[0x%x] failed, ret[0x%x]\n", commandID, ret);
	}

	return  ret;
}

void TA_CloseSessionEntryPoint(void *sessionContext)
{
	(void)sessionContext;
}

void TA_DestroyEntryPoint(void)
{
}
