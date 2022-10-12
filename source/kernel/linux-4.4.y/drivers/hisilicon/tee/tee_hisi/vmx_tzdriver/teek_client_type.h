/**
 * @file tee_client_type.h
 *
 * Copyright(C), 2008-2013, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ��������������������ͺ����ݽṹ\n
 */

#ifndef _TEE_CLIENT_TYPE_H_
#define _TEE_CLIENT_TYPE_H_

#include "teek_client_constants.h"
#include "teek_client_list.h"

/**
 * @ingroup TEEC_COMMON_DATA
 * �޷������Ͷ���
 */
typedef unsigned int uint32_t;
/**
 * @ingroup TEEC_COMMON_DATA
 * �з������Ͷ���
 */
typedef signed int int32_t;
/**
 * @ingroup TEEC_COMMON_DATA
 * �޷��Ŷ����Ͷ���
 */
typedef unsigned short uint16_t;
/**
 * @ingroup TEEC_COMMON_DATA
 * �з��Ŷ����Ͷ���
 */
typedef signed short int16_t;
/**
 * @ingroup TEEC_COMMON_DATA
 * �޷����ַ��Ͷ���
 */
typedef unsigned char uint8_t;
/**
 * @ingroup TEEC_COMMON_DATA
 * �з����ַ��Ͷ���
 */
typedef signed char int8_t;
/**
 * @ingroup TEEC_COMMON_DATA
 * �������Ͷ���
 */
#ifndef bool
#define bool    uint8_t
#endif

/**
 * @ingroup TEEC_COMMON_DATA
 * trueֵ�Ķ���
 */
#ifndef true
#define true    1
#endif

/**
 * @ingroup TEEC_COMMON_DATA
 * falseֵ�Ķ���
 */
#ifndef false
#define false   0
#endif

/**
 * @ingroup TEEC_COMMON_DATA
 * NULLֵ�Ķ���
 */
#ifndef NULL
#define NULL 0
#endif

/**
 * @ingroup TEEC_COMMON_DATA
 * ��������ֵ���Ͷ���
 *
 * ���ڱ�ʾ�������ؽ��
 */
typedef uint32_t TEEC_Result;

/**
 * @ingroup TEEC_COMMON_DATA
 * UUID���Ͷ���
 *
 * UUID������ѭRFC4122 [2]�����ڱ�ʶ��ȫ����
 */
typedef struct {
	uint32_t timeLow;
	/**< ʱ����ĵ�4�ֽ�  */
	uint16_t timeMid;
	/**< ʱ�������2�ֽ�  */
	uint16_t timeHiAndVersion;
	/**< ʱ����ĸ�2�ֽ���汾�ŵ����  */
	uint8_t clockSeqAndNode[8];
	/**< ʱ��������ڵ��ʶ�������  */
} TEEC_UUID;

/**
 * @ingroup TEEC_COMMON_DATA
 * TEEC_Context�ṹ�����Ͷ���
 *
 * �����ͻ���Ӧ���밲ȫ����֮�佨�������ӻ���
 */
typedef struct {
	void *dev;
	uint8_t *ta_path;
	struct list_node session_list;
	/**< �Ự����  */
	struct list_node shrd_mem_list;
	/**< �����ڴ�����  */
} TEEC_Context;

/**
 * @ingroup TEEC_COMMON_DATA
 * TEEC_Session�ṹ�����Ͷ���
 *
 * �����ͻ���Ӧ���밲ȫ����֮�佨���ĻỰ
 */
typedef struct {
	uint32_t session_id;
	/**< �ỰID���ɰ�ȫ���緵��  */
	TEEC_UUID service_id;
	/**< ��ȫ�����UUID��ÿ����ȫ����ӵ��Ψһ��UUID  */
	uint32_t ops_cnt;
	/**< �ڻỰ�ڵĲ�����  */
	struct list_node head;
	/**< �Ự����ͷ  */
	TEEC_Context *context;
	/**< ָ��Ự������TEE����  */
} TEEC_Session;

/**
 * @ingroup TEEC_COMMON_DATA
 * TEEC_SharedMemory�ṹ�����Ͷ���
 *
 * ����һ�鹲���ڴ棬����ע�ᣬҲ���Է���
 */
typedef struct {
	void *buffer;
	/**< �ڴ�ָ��  */
	size_t size;
	/**< �ڴ��С  */
	uint32_t flags;
	/**< �ڴ��ʶ����������������������ȡֵ��ΧΪ#TEEC_SharedMemCtl  */
	uint32_t ops_cnt;
	/**< �ڴ������  */
	bool is_allocated;
	/**< �ڴ�����ʾ��������������ע��ģ����Ƿ����  */
	struct list_node head;
	/**< �����ڴ�����ͷ  */
	TEEC_Context *context;
	/**< ָ��������TEE���� */
} TEEC_SharedMemory;

/**
 * @ingroup TEEC_COMMON_DATA
 * TEEC_TempMemoryReference�ṹ�����Ͷ���
 *
 * ����һ����ʱ������ָ��\n
 * ��������#TEEC_Parameter�����ͣ��������Ӧ�����Ϳ�����
 * #TEEC_MEMREF_TEMP_INPUT�� #TEEC_MEMREF_TEMP_OUTPUT����#TEEC_MEMREF_TEMP_INOUT
 */
typedef struct {
	void *buffer;
	/**< ��ʱ������ָ��  */
	size_t size;
	/**< ��ʱ��������С  */
} TEEC_TempMemoryReference;

/**
 * @ingroup TEEC_COMMON_DATA
 * TEEC_RegisteredMemoryReference�ṹ�����Ͷ���
 *
 * ���������ڴ�ָ�룬ָ������ע������õĹ����ڴ�\n
 * ��������#TEEC_Parameter�����ͣ��������Ӧ�����Ϳ�����
 * #TEEC_MEMREF_WHOLE�� #TEEC_MEMREF_PARTIAL_INPUT��
 * #TEEC_MEMREF_PARTIAL_OUTPUT���� #TEEC_MEMREF_PARTIAL_INOUT
 */
typedef struct {
	TEEC_SharedMemory *parent;
	/**< �����ڴ�ָ��  */
	size_t size;
	/**< �����ڴ��ʹ�ô�С  */
	size_t offset;
	/**< �����ڴ��ʹ��ƫ��  */
} TEEC_RegisteredMemoryReference;

/**
 * @ingroup TEEC_COMMON_DATA
 * TEEC_Value�ṹ�����Ͷ���
 *
 * ��������������\n
 * ��������#TEEC_Parameter�����ͣ��������Ӧ�����Ϳ�����
 * #TEEC_VALUE_INPUT�� #TEEC_VALUE_OUTPUT����#TEEC_VALUE_INOUT
 */
typedef struct {
	uint32_t a;
	/**< ��������a  */
	uint32_t b;
	/**< ��������b  */
} TEEC_Value;

typedef struct {
	int ion_share_fd;  /**< ��������a  */
	size_t ion_size;  /**< ��������b  */
} TEEC_IonReference;

/**
 * @ingroup TEEC_COMMON_DATA
 * TEEC_Parameter���������Ͷ���
 *
 * ����#TEEC_Operation����Ӧ�Ĳ�������
 */
typedef union {
	TEEC_TempMemoryReference tmpref;
	/**< ����#TEEC_TempMemoryReference����  */
	TEEC_RegisteredMemoryReference memref;
	/**< ����#TEEC_RegisteredMemoryReference����  */
	TEEC_Value value;
	/**< ����#TEEC_Value����  */
	TEEC_IonReference ionref;
} TEEC_Parameter;

typedef struct {
	uint32_t event_type;
	/**Tui event type  */
	uint32_t value;
	/**return value, is keycode if tui event is getKeycode*/
} TEEC_TUI_Parameter;

/**
 * @ingroup TEEC_COMMON_DATA
 * TEEC_Operation�ṹ�����Ͷ���
 *
 * �򿪻Ự��������ʱ�Ĳ�������ͨ��������������
 * ȡ������Ҳ����ʹ�ô˲���
 */
typedef struct {
	uint32_t started;
	/**< ��ʶ�Ƿ���ȡ��������0��ʾȡ������  */
	uint32_t paramTypes;
	/**����params�Ĳ�������#TEEC_ParamType,
	*    ��Ҫʹ�ú�#TEEC_PARAM_TYPES��ϲ������� */
	TEEC_Parameter params[4];
	/**< �������ݣ�����Ϊ#TEEC_Parameter  */
	TEEC_Session *session;
	bool cancel_flag;
} TEEC_Operation;

#endif
/**
 * History: \n
 * 2013-4-12 sdk: Create this file\n
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
*/
