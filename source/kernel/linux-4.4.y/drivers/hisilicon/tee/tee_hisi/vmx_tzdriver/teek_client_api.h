/**
 * @file tee_client_api.h
 *
 * Copyright(C), 2008-2013, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ����������ǰ�ȫ�ͻ��˽ӿ�\n
 */

/** @defgroup TEEC_API �ͻ���(�ǰ�ȫ��)�ӿ�
 */
/**@defgroup TEEC_BASIC_FUNC ͨ�ýӿ�
 *@ingroup TEEC_API
*/

#ifndef _TEE_CLIENT_API_H_
#define _TEE_CLIENT_API_H_

#include "teek_client_type.h"

/**
 * @ingroup TEEC_BASIC_FUNC
 * ���ڼ���ǰ�ȫ�����밲ȫ���紫�ݲ�������ֵ
 */
#define TEEC_PARAM_TYPES(param0Type, param1Type, param2Type, param3Type) \
	((param3Type) << 12 | (param2Type) << 8 | \
	 (param1Type) << 4 | (param0Type))

/**
 * @ingroup TEEC_BASIC_FUNC
 * ���ڼ���paramTypes���ֶ�index����ֵ
 */
#define TEEC_PARAM_TYPE_GET(paramTypes, index) \
	(((paramTypes) >> (4*(index))) & 0x0F)

/**
 * @ingroup TEEC_BASIC_FUNC
 * ����������Ϊ#TEEC_Valueʱ�������Ա����a��bû�и���ֵ���踳���ֵ��
 * ��ʾû���õ��˳�Ա����
 */
#define TEEC_VALUE_UNDEF 0xFFFFFFFF
#ifdef CONFIG_DEVCHIP_PLATFORM
/**
 * @ingroup TEEC_BASIC_FUNC
 * ���Խӿڣ��ڶ����TEEC_DEBUG�������Ч����TEEC_DEBUG�ǵ��Դ�ӡ����
 */
#ifdef TEEC_DEBUG
#define TEEC_Debug(fmt, args...) printk(KERN_DEBUG "%s(%i, %s): " fmt "\n", \
		__func__, current->pid, current->comm, ## args)
#else
#define TEEC_Debug(fmt, args...)
#endif

/**
 * @ingroup TEEC_BASIC_FUNC
 * ���Խӿڣ�API�����ڲ���ӡ������Ϣ
 */
#define TEEC_Error(fmt, args...) printk(KERN_ERR "%s(%i, %s): " fmt "\n", \
		__func__, current->pid, current->comm, ## args)
#define TEEC_Info(fmt, args...) printk(KERN_INFO "%s(%i, %s): " fmt "\n", \
		__func__, current->pid, current->comm, ## args)
#endif
/*
 * Function:      TEEK_IsAgentAlive
 * Description:   This function check if the special agent is launched.
 *              Used For HDCP key.
 *                e.g. If sfs agent is not alive,
 *                you can not do HDCP key write to SRAM.
 * Parameters:   agent_id.
 * Return:      1:agent is alive
 *              0:agent not exsit.
 */
int TEEK_IsAgentAlive(unsigned int agent_id);
/**
 * @ingroup  TEEC_BASIC_FUNC
 * @brief ��ʼ��TEE����
 *
 * @par ����:
 * ��ʼ��·��Ϊname��TEE����������name����Ϊ�գ�
 * ��ʼ��TEE�����Ǵ򿪻Ự����������Ļ�����
 * ��ʼ���ɹ��󣬿ͻ���Ӧ����TEE����һ�����ӡ�
 *
 * @attention ��
 * @param name [IN] TEE����·��
 * @param context [IN/OUT] contextָ�룬��ȫ���绷�����
 *
 * @retval #TEEC_SUCCESS ��ʼ��TEE�����ɹ�
 * @retval #TEEC_ERROR_BAD_PARAMETERS ��������ȷ��name����ȷ��contextΪ��
 * @retval #TEEC_ERROR_GENERIC ϵͳ������Դ�����ԭ��
 *
 * @par ����:
 * @li libteec���ýӿ������Ĺ����
 * @li tee_client_api.h���ýӿ���������ͷ�ļ�
 * @see TEEC_FinalizeContext
 * @since V100R002C00B301
 */
TEEC_Result TEEK_InitializeContext(const char *name, TEEC_Context *context);

/**
 * @ingroup  TEEC_BASIC_FUNC
 * @brief �ر�TEE����
 *
 * @par ����:
 * �ر�contextָ���TEE�������Ͽ��ͻ���Ӧ����TEE����������
 *
 * @attention ��
 * @param context [IN/OUT] ָ���ѳ�ʼ���ɹ���TEE����
 *
 * @retval ��
 *
 * @par ����:
 * @li libteec���ýӿ������Ĺ����
 * @li tee_client_api.h���ýӿ���������ͷ�ļ�
 * @see TEEC_InitializeContext
 * @since V100R002C00B301
 */
void TEEK_FinalizeContext(TEEC_Context *context);

/**
 * @ingroup  TEEC_BASIC_FUNC
 * @brief �򿪻Ự
 *
 * @par ����:
 * ��ָ����TEE����context�£�Ϊ�ͻ���Ӧ����UUID
 * Ϊdestination�İ�ȫ������һ�����ӣ�
 * ���ӷ�ʽ��connectionMethod������������connectionData,
 * ���ݵ����ݰ�����opetation�
 * �򿪻Ự�ɹ����������session�ǶԸ����ӵ�һ��������
 * ����򿪻Ựʧ�ܣ��������returnOriginΪ������Դ��
 *
 * @attention ��
 * @param context [IN/OUT] ָ���ѳ�ʼ���ɹ���TEE����
 * @param session [OUT] ָ��Ự��ȡֵ����Ϊ��
 * @param destination [IN] ��ȫ�����UUID��һ����ȫ����ӵ��Ψһ��UUID
 * @param connectionMethod [IN] ���ӷ�ʽ��ȡֵ��ΧΪ#TEEC_LoginMethod
 * @param connectionData [IN] �����ӷ�ʽ���Ӧ���������ݣ�
 * ������ӷ�ʽΪ#TEEC_LOGIN_PUBLIC, #TEEC_LOGIN_USE,
 * #TEEC_LOGIN_USER_APPLICATION,
 * #TEEC_LOGIN_GROUP_APPLICATION, ��������ȡֵ����Ϊ�գ�
 * ������ӷ�ʽΪ#TEEC_LOGIN_GROUP��#TEEC_LOGIN_GROUP_APPLICATION��
 * �������ݱ���ָ������Ϊuint32_t�����ݣ������ݱ�ʾ�ͻ���Ӧ���������ӵ����û�
 * @param operation [IN/OUT] �ͻ���Ӧ���밲ȫ���񴫵ݵ�����
 * @param returnOrigin [IN/OUT] ������Դ��ȡֵ��ΧΪ#TEEC_ReturnCodeOrigin
 *
 * @retval #TEEC_SUCCESS �򿪻Ự�ɹ�
 * @retval #TEEC_ERROR_BAD_PARAMETERS ��������ȷ������contextΪ�ջ�sessionΪ�ջ�destinationΪ��
 * @retval #TEEC_ERROR_ACCESS_DENIED ϵͳ����Ȩ�޷���ʧ��
 * @retval #TEEC_ERROR_OUT_OF_MEMORY ϵͳ������Դ����
 * @retval #TEEC_ERROR_TRUSTED_APP_LOAD_ERROR ���ذ�ȫ����ʧ��
 * @retval ��������ֵ�ο� #TEEC_ReturnCode
 *
 * @par ����:
 * @li libteec���ýӿ������Ĺ����
 * @li tee_client_api.h���ýӿ���������ͷ�ļ�
 * @see TEEC_CloseSession
 * @since V100R002C00B301
 */
TEEC_Result TEEK_OpenSession(TEEC_Context *context,
			     TEEC_Session *session,
			     const TEEC_UUID *destination,
			     uint32_t connectionMethod,
			     const void *connectionData,
			     TEEC_Operation *operation,
			     uint32_t *returnOrigin);

/**
 * @ingroup  TEEC_BASIC_FUNC
 * @brief �رջỰ
 *
 * @par ����:
 * �ر�sessionָ��ĻỰ���Ͽ��ͻ���Ӧ���밲ȫ���������
 *
 * @attention ��
 * @param session [IN/OUT] ָ���ѳɹ��򿪵ĻỰ
 *
 * @retval ��
 *
 * @par ����:
 * @li libteec���ýӿ������Ĺ����
 * @li tee_client_api.h���ýӿ���������ͷ�ļ�
 * @see TEEC_OpenSession
 * @since V100R002C00B301
 */
void TEEK_CloseSession(TEEC_Session *session);

/**
 * @ingroup  TEEC_BASIC_FUNC
 * @brief ��������
 *
 * @par ����:
 * ��ָ���ĻỰsession��ɿͻ���Ӧ����ȫ����������commandID��
 * ���͵�����Ϊoperation�������������ʧ�ܣ��������returnOriginΪ������Դ
 *
 * @attention ��
 * @param session [IN/OUT] ָ���Ѵ򿪳ɹ��ĻỰ
 * @param commandID [IN] ��ȫ����֧�ֵ�����ID���ɰ�ȫ������
 * @param operation [IN/OUT] �����˿ͻ���Ӧ����ȫ�����͵���������
 * @param returnOrigin [IN/OUT] ������Դ��ȡֵ��ΧΪ#TEEC_ReturnCodeOrigin
 *
 * @retval #TEEC_SUCCESS ��������ɹ�
 * @retval #TEEC_ERROR_BAD_PARAMETERS ��������ȷ������sessionΪ�ջ����operation��ʽ����ȷ
 * @retval #TEEC_ERROR_ACCESS_DENIED ϵͳ����Ȩ�޷���ʧ��
 * @retval #TEEC_ERROR_OUT_OF_MEMORY ϵͳ������Դ����
 * @retval ��������ֵ�ο� #TEEC_ReturnCode
 *
 * @par ����:
 * @li libteec���ýӿ������Ĺ����
 * @li tee_client_api.h���ýӿ���������ͷ�ļ�
 * @see ��
 * @since V100R002C00B301
 */
TEEC_Result TEEK_InvokeCommand(TEEC_Session *session,
			       uint32_t commandID,
			       TEEC_Operation *operation,
			       uint32_t *returnOrigin);

/**
 * @ingroup  TEEC_BASIC_FUNC
 * @brief ע�Ṳ���ڴ�
 *
 * @par ����:
 * ��ָ����TEE����context��ע�Ṳ���ڴ�sharedMem��
 * ͨ��ע��ķ�ʽ��ȡ�����ڴ���ʵ���㿽����Ҫ����ϵͳ��֧�֣�
 * Ŀǰ��ʵ���У��÷�ʽ����ʵ���㿽��
 *
 * @attention ������sharedMem��size������Ϊ0�������᷵�سɹ������޷�ʹ�����
 * �����ڴ棬��Ϊ����ڴ�û�д�С
 * @param context [IN/OUT] �ѳ�ʼ���ɹ���TEE����
 * @param sharedMem [IN/OUT] �����ڴ�ָ�룬�����ڴ���ָ����ڴ治��Ϊ�ա���С����Ϊ��
 *
 * @retval #TEEC_SUCCESS ��������ɹ�
 * @retval #TEEC_ERROR_BAD_PARAMETERS ��������ȷ������contextΪ�ջ�sharedMemΪ�գ�
 * �����ڴ���ָ����ڴ�Ϊ��
 *
 * @par ����:
 * @li libteec���ýӿ������Ĺ����
 * @li tee_client_api.h���ýӿ���������ͷ�ļ�
 * @see TEEC_AllocateSharedMemory
 * @since V100R002C00B301
 */
TEEC_Result TEEK_RegisterSharedMemory(TEEC_Context *context,
				      TEEC_SharedMemory *sharedMem);

/**
 * @ingroup  TEEC_BASIC_FUNC
 * @brief ���빲���ڴ�
 *
 * @par ����:
 * ��ָ����TEE����context�����빲���ڴ�sharedMem��
 * ͨ�������ڴ����ʵ�ַǰ�ȫ�����밲ȫ���紫������ʱ���㿽��
 *
 * @attention ������sharedMem��size������Ϊ0�������᷵�سɹ������޷�ʹ�����
 * �����ڴ棬��Ϊ����ڴ��û�е�ַҲû�д�С
 * @param context [IN/OUT] �ѳ�ʼ���ɹ���TEE����
 * @param sharedMem [IN/OUT] �����ڴ�ָ�룬�����ڴ�Ĵ�С����Ϊ��
 *
 * @retval #TEEC_SUCCESS ��������ɹ�
 * @retval #TEEC_ERROR_BAD_PARAMETERS ��������ȷ������contextΪ�ջ�sharedMemΪ��
 * @retval #TEEC_ERROR_OUT_OF_MEMORY ϵͳ������Դ���㣬����ʧ��
 *
 * @par ����:
 * @li libteec���ýӿ������Ĺ����
 * @li tee_client_api.h���ýӿ���������ͷ�ļ�
 * @see TEEC_RegisterSharedMemory
 * @since V100R002C00B301
 */
TEEC_Result TEEK_AllocateSharedMemory(TEEC_Context *context,
				      TEEC_SharedMemory *sharedMem);

/**
 * @ingroup  TEEC_BASIC_FUNC
 * @brief �ͷŹ����ڴ�
 *
 * @par ����:
 * �ͷ���ע��ɹ��ĵĻ�������ɹ��Ĺ����ڴ�sharedMem
 *
 * @attention �����ͨ��#TEEC_AllocateSharedMemory��ʽ��ȡ�Ĺ����ڴ棬
 * �ͷ�ʱ���������ڴ棻�����ͨ��#TEEC_RegisterSharedMemory��ʽ
 * ��ȡ�Ĺ����ڴ棬�ͷ�ʱ������չ����ڴ���ָ��ı����ڴ�
 * @param sharedMem [IN/OUT] ָ����ע��ɹ�������ɹ��Ĺ����ڴ�
 *
 * @retval ��
 *
 * @par ����:
 * @li libteec���ýӿ������Ĺ����
 * @li tee_client_api.h���ýӿ���������ͷ�ļ�
 * @see TEEC_RegisterSharedMemory | TEEC_AllocateSharedMemory
 * @since V100R002C00B301
 */
void TEEK_ReleaseSharedMemory(TEEC_SharedMemory *sharedMem);

/**
 * @ingroup  TEEC_BASIC_FUNC
 * @brief cancel API
 *
 * @par ����:
 * ȡ����һ���������е�open Session������һ��invoke command
 * ����һ��cancel��signal����������
 *
 * @attention �˲��������Ƿ���һ��cancel����Ϣ���Ƿ����cancel������ǰ���TEE �� TA����
 * @param operation [IN/OUT] �����˿ͻ���Ӧ����ȫ�����͵���������
 *
 * @retval ��
 *
 * @par ����:
 * @li libteec���ýӿ������Ĺ����
 * @li tee_client_api.h���ýӿ���������ͷ�ļ�
 * @see ��
 * @since V100R002C00B309
 */
void TEEK_RequestCancellation(TEEC_Operation *operation);

#endif
/**
 * History: \n
 * 2013-4-12 sdk: Create this file\n
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
*/
