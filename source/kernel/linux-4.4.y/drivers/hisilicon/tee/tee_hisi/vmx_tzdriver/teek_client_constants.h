/**
 * @file tee_client_constants.h
 *
 * Copyright(C), 2008-2013, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ���������徲̬����\n
 */

/** @defgroup TEEC_COMMON_DATA �������ݶ���
 *@ingroup TEEC_API
 */

#ifndef _TEE_CLIENT_CONSTANTS_H_
#define _TEE_CLIENT_CONSTANTS_H_

/**
 * @ingroup  TEEC_COMMON_DATA
 *
 * �������صĴ�����
 */
enum TEEC_ReturnCode {
	TEEC_SUCCESS = 0x0,
	/**< �������سɹ�	*/
	TEEC_ERROR_INVALID_CMD,			 /**< �Ƿ������ȫ����֧�ֵ����� */
	TEEC_ERROR_SERVICE_NOT_EXIST,		 /**< ��ȫ���񲻴��� */
	TEEC_ERROR_SESSION_NOT_EXIST,		 /**< �ͻ���Ӧ���밲ȫ��������Ӳ����� */
	TEEC_ERROR_SESSION_MAXIMUM,		 /**< ��ȫ��������������� */
	TEEC_ERROR_REGISTER_EXIST_SERVICE,	 /**< ע���Ѿ����ڵİ�ȫ���� */
	TEEC_ERROR_TAGET_DEAD_FATAL,		 /**< ��ȫ����Global���� ��(��ȫ����Global�����а�ȫ����Ļ���) */
	TEEC_ERROR_READ_DATA,			 /**< ��ȡ�ļ�����	*/
	TEEC_ERROR_WRITE_DATA,			 /**< д���ļ�����	*/
	TEEC_ERROR_TRUNCATE_OBJECT,		 /**< �ض��ļ�����	*/
	TEEC_ERROR_SEEK_DATA,			 /**< �����ļ�����	*/
	TEEC_ERROR_RENAME_OBJECT,		 /**< �������ļ�����  */
	TEEC_ERROR_TRUSTED_APP_LOAD_ERROR,	 /**< �򿪻Ựʱ�����ذ�ȫ����ʧ��*/
	TEEC_ERROR_GENERIC = 0xFFFF0000,
	/**< ͨ�ô��󣬳�ʼ����ȫ����ʧ��  */
	TEEC_ERROR_ACCESS_DENIED = 0xFFFF0001,
	/**< Ȩ��У��ʧ�ܣ�
	��TEE�������򿪻Ự�ͷ�����������Ȩ�޵�У�飬
	Ȩ��У�鲻ͨ���᷵�ش������  */
	TEEC_ERROR_CANCEL = 0xFFFF0002,
	/**< ������ȡ����
	���������ȡ����־λ����λ���ٶԴ˲������в���ʱ���ش������ */
	TEEC_ERROR_ACCESS_CONFLICT = 0xFFFF0003,
	/**< �������ʵ���Ȩ�޳�ͻ��
	��ȫ�洢�����ж��ļ��Ĳ������ʿ��ܻ�����������  */
	TEEC_ERROR_EXCESS_DATA = 0xFFFF0004,
	/**< ��������������̫�� ����ȫ�����޷����� */
	TEEC_ERROR_BAD_FORMAT = 0xFFFF0005,
	/**< ���ݸ�ʽ����ȷ��
	�ͻ���Ӧ�����Ĳ�����ʽ������ͻ���Ӧ���밲ȫ�����ͨ��Э�飬
	��ȫӦ���޷�����  */
	TEEC_ERROR_BAD_PARAMETERS = 0xFFFF0006,
	/**< ������Ч�����Ϊ�ջ�Ƿ��ȴ���  */
	TEEC_ERROR_BAD_STATE = 0xFFFF0007,
	/**< ��ǰ״̬�µĲ�����Ч��
	����ȫ�洢�������ʱ�����û�г�ʼ����ȫ�洢���񣬻᷵�ش������*/
	TEEC_ERROR_ITEM_NOT_FOUND = 0xFFFF0008,
	/**< ���������δ�ҵ�	*/
	TEEC_ERROR_NOT_IMPLEMENTED = 0xFFFF0009,
	/**< ����Ĳ������ڵ���δʵ�֣�
	����ȡ������ʱ���ش������	*/
	TEEC_ERROR_NOT_SUPPORTED = 0xFFFF000A,
	/**< ����Ĳ�����Ч��δ֧�֣�
	����ȫ�ӽ��ܷ����һЩ�㷨��DSA��ʱ���ش������  */
	TEEC_ERROR_NO_DATA = 0xFFFF000B,
	/**< ���ݴ��� ������Ĳ����Ҳ�����Ӧ������ */
	TEEC_ERROR_OUT_OF_MEMORY = 0xFFFF000C,
	/**< ϵͳ������Դ���㣬
	�ڴ�����ʧ�ܻ᷵�ش������	*/
	TEEC_ERROR_BUSY = 0xFFFF000D,
	/**< ϵͳ��æ��ϵͳ�������ڶ�ռһЩ��Դ	*/
	TEEC_ERROR_COMMUNICATION = 0xFFFF000E,
	/**< �ǰ�ȫ����Ӧ�ó�����
	��ȫӦ��ͨ��ʱ��������	*/
	TEEC_ERROR_SECURITY = 0xFFFF000F,
	/**< ��⵽��ȫ���󣬰�ȫ���緢������  */
	TEEC_ERROR_SHORT_BUFFER = 0xFFFF0010,
	/**< �ڴ����볤��С��������ȣ�
	ʹ������Ϊ#TEEC_MEMREF_TEMP_OUTPUTʱ��Ҫע��������  */
	TEEC_ERROR_MAC_INVALID = 0xFFFF3071,
	/**< MACֵУ�����  */
};

/**
 * @ingroup  TEEC_COMMON_DATA
 *
 * �������ش��������Դ
 */
enum TEEC_ReturnCodeOrigin {
	TEEC_ORIGIN_API = 0x1,
	/**< ���������Կͻ���API  */
	TEEC_ORIGIN_COMMS = 0x2,
	/**< ���������Էǰ�ȫ�����밲ȫ�����ͨ��  */
	TEEC_ORIGIN_TEE = 0x3,
	/**< ���������԰�ȫ����  */
	TEEC_ORIGIN_TRUSTED_APP = 0x4,
	/**< ���������԰�ȫ����  */
};

/**
 * @ingroup  TEEC_COMMON_DATA
 *
 * �����ڴ��ʶ
 */
enum TEEC_SharedMemCtl {
	TEEC_MEM_INPUT = 0x1,
	/**< �����ڴ���������Ǵӿͻ���Ӧ�õ���ȫ����  */
	TEEC_MEM_OUTPUT = 0x2,
	/**< �����ڴ���������ǴӰ�ȫ���񵽿ͻ���Ӧ��  */
	TEEC_MEM_INOUT = 0x3,
	/**< �����ڴ���ڿͻ���Ӧ���밲ȫ����֮��˫�򴫵�  */
};

/**
 * @ingroup  TEEC_COMMON_DATA
 *
 * �������Ͷ���
 */
enum TEEC_ParamType {
	TEEC_NONE = 0x0,
	/**< ����û��ʹ��  */
	TEEC_VALUE_INPUT = 0x01,
	/**< ������#TEEC_Value���Ӧ��ֻ����Ϊ���룬
	�������Ǵӿͻ���Ӧ�õ���ȫ����*/
	TEEC_VALUE_OUTPUT = 0x02,
	/**< ������#TEEC_Value���Ӧ��ֻ����Ϊ�����
	�������ǴӰ�ȫ���񵽿ͻ���Ӧ��*/
	TEEC_VALUE_INOUT = 0x03,
	/**< ������#TEEC_Value���Ӧ���ȿ�����Ҳ�����  */
	TEEC_MEMREF_TEMP_INPUT = 0x05,
	/**< ������#TEEC_TempMemoryReference���Ӧ��
	ֻ����Ϊ���룬�������Ǵӿͻ���Ӧ�õ���ȫ����  */
	TEEC_MEMREF_TEMP_OUTPUT = 0x06,
	/**< ������#TEEC_TempMemoryReference���Ӧ��
	ֻ����Ϊ������������ǴӰ�ȫ���񵽿ͻ���Ӧ��  */
	TEEC_MEMREF_TEMP_INOUT = 0x07,
	/**< ������#TEEC_TempMemoryReference���Ӧ��
	�ȿ�����Ҳ����������ڿͻ���Ӧ���밲ȫ����֮��˫�򴫵�*/
	TEEC_ION_INPUT = 0x08,	/**< ������#TEEC_IonReference���Ӧ��ֻ����Ϊ����,
				�������Ǵӿͻ���Ӧ�õ���ȫ����*/
	TEEC_MEMREF_WHOLE = 0xc,
	/**< ������#TEEC_RegisteredMemoryReference
	���Ӧ�����������ڴ� ������������ָ��Ĺ����ڴ�ı�ʶ#TEEC_SharedMemCtlһ�� */
	TEEC_MEMREF_PARTIAL_INPUT = 0xd,
	/**< ������#TEEC_RegisteredMemoryReference���Ӧ��
	ֻ����Ϊ���룬�������Ǵӿͻ���Ӧ�õ���ȫ���� */
	TEEC_MEMREF_PARTIAL_OUTPUT = 0xe,
	/**< ������#TEEC_RegisteredMemoryReference
	���Ӧ��ֻ����Ϊ������������ǴӰ�ȫ���񵽿ͻ���Ӧ�� */
	TEEC_MEMREF_PARTIAL_INOUT = 0xf
				    /**< ������#TEEC_RegisteredMemoryReference���Ӧ��
				    �ȿ�����Ҳ����������ڿͻ���Ӧ���밲ȫ����֮��˫�򴫵�*/
};

/****************************************************
 *		Session Login Methods
 ****************************************************/
/**
 * @ingroup  TEEC_COMMON_DATA
 *
 * Login��ʽ
 */
enum TEEC_LoginMethod {
	TEEC_LOGIN_PUBLIC = 0x0,
	/**< ����ҪLogin����	*/
	TEEC_LOGIN_USER,
	/**< �ṩ�û����пͻ���Ӧ�õ�Login����  */
	TEEC_LOGIN_GROUP,
	/**< �ṩ���û����пͻ���Ӧ�õ�Login����  */
	TEEC_LOGIN_APPLICATION = 0x4,
	/**< �ṩ�ͻ���Ӧ���Լ���Login����  */
	TEEC_LOGIN_USER_APPLICATION = 0x5,
	/**< �ṩ�û����пͻ���Ӧ��
	  ��Login���ݣ��Լ��ͻ���Ӧ���Լ���Login����*/
	TEEC_LOGIN_GROUP_APPLICATION = 0x6,
	/**< �ṩ���û����пͻ���Ӧ��
	��Login���ݣ��Լ��ͻ���Ӧ���Լ���Login����*/
	TEEC_LOGIN_IDENTIFY = 0x7,
	/**< ʹ�ð�ȫ�洢ʱ��Ҫ�ṩLogin����  */
};

#endif
/**
 * History: \n
 * 2013-4-12 sdk: Create this file\n
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
*/
