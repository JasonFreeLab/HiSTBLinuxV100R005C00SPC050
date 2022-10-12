/**
 * @file tee_client_id.h
 *
 * Copyright(C), 2008-2013, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ��������ȫ�����ṩ�İ�ȫ�����������ͷ�ļ�\n
 */
#ifndef _TEE_CLIENT_ID_H_
#define _TEE_CLIENT_ID_H_

/**
 *  * @ingroup  TEE_ID
 *   *
 *    * secboot��
 *     */
#define TEE_SERVICE_SECBOOT \
{ \
	0x08080808, \
	0x0808, \
	0x0808, \
	{ \
		0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08 \
	} \
}

/*e7ed1f64-4687-41da-96dc-cbe4f27c838f*/
#define TEE_SERVICE_ANTIROOT \
{ \
	0xE7ED1F64, \
	0x4687, \
	0x41DA, \
	{ \
		0x96, 0xDC, 0xCB, 0xE4, 0xF2, 0x7C, 0x83, 0x8F \
	} \
}

/**
 * @ingroup  TEE_COMMON_DATA
 *
 * ��ȫ����secboot֧�ֵ�����ID
 */
enum SVC_SECBOOT_CMD_ID {
	SECBOOT_CMD_ID_INVALID = 0x0,	/**< Secboot Task ��ЧID*/
	SECBOOT_CMD_ID_COPY_VRL,	/**< Secboot Task ����VRL*/
	SECBOOT_CMD_ID_COPY_DATA,	/**< Secboot Task ��������*/
	SECBOOT_CMD_ID_VERIFY_DATA,	/**< Secboot Task ��֤*/
	SECBOOT_CMD_ID_RESET_IMAGE,	/**< Secboot Task ��λSoC����*/
	SECBOOT_CMD_ID_COPY_VRL_TYPE,  /**< Secboot Task ����VRL��������SoC Type*/
	SECBOOT_CMD_ID_COPY_DATA_TYPE,	/**< Secboot Task ��������,������SoC Type*/
	SECBOOT_CMD_ID_VERIFY_DATA_TYPE, /**< Secboot Task У�飬������SoC Type��У��ɹ��⸴λSoC*/
	 /**< Secboot Taskԭ��У�飬������SoC Type,У��ɹ��⸴λSoC*/
	SECBOOT_CMD_ID_VERIFY_DATA_TYPE_LOCAL,
	SECBOOT_CMD_ID_BSP_MODEM_CALL,           /**< Secboot Task ִ�ж�Ӧ����*/
	SECBOOT_CMD_ID_BSP_MODULE_VERIFY,        /**< Secboot Task modem moduleУ�麯��*/
};

/**
 * @ingroup TEE_COMMON_DATA
 *
 * ��ȫ����secboot֧�ֵľ�������
 */
enum SVC_SECBOOT_IMG_TYPE {
	MODEM,
	HIFI,
	DSP,
	XDSP,
	TAS,
	WAS,
	CAS,
	MODEM_DTB,
    ISP,
	SOC_MAX
};
/**
 * @ingroup  TEEC_COMMON_DATA
 *
 * ��ȫ����Global֧�ֵ�����ID
 */
enum SVC_GLOBAL_CMD_ID {
	GLOBAL_CMD_ID_INVALID = 0x0,	/**< ��ȫ����Global����Ч������*/
	GLOBAL_CMD_ID_BOOT_ACK,	   /**< ��ȫ����Global������Ӧ��*/
	GLOBAL_CMD_ID_OPEN_SESSION,    /**< ��ȫ����Global����Session*/
	GLOBAL_CMD_ID_CLOSE_SESSION,	/**< ��ȫ����Global���ر�Session*/
	GLOBAL_CMD_ID_LOAD_SECURE_APP,
	/**< ��ȫ����Global����̬���ذ�ȫӦ��*/
	GLOBAL_CMD_ID_NEED_LOAD_APP,/**< ��ȫ����Global���ж��Ƿ�����Ҫ���ذ�ȫӦ��*/
	GLOBAL_CMD_ID_REGISTER_AGENT,
	/**< ��ȫ����Global��ע�����*/
	GLOBAL_CMD_ID_UNREGISTER_AGENT,
	/**< ��ȫ����Global��ע������*/
	GLOBAL_CMD_ID_REGISTER_NOTIFY_MEMORY,
	/**< ��ȫ����Global��ע���첽���û�����*/
	GLOBAL_CMD_ID_UNREGISTER_NOTIFY_MEMORY,
	 /**< ��ȫ����Global��ע���첽���û�����*/
	GLOBAL_CMD_ID_INIT_CONTENT_PATH,  /**< ��ȫ����Global����ʼ��content path*/
	GLOBAL_CMD_ID_TERMINATE_CONTENT_PATH,
	 /**< ��ȫ����Global���ͷ�content path*/
	GLOBAL_CMD_ID_ALLOC_EXCEPTION_MEM,
	/**< ��ȫ����Global�������쳣��Ϣ����ռ�*/
	GLOBAL_CMD_ID_TEE_TIME,	    /**< ��ȫ����Global����ȡ��ȫOS��ʱ�� */
	GLOBAL_CMD_ID_TEE_INFO,	   /** tlogcat ����OS  �� */
	GLOBAL_CMD_ID_KILL_TASK,   /** Global Task Kill session */
	GLOBAL_CMD_ID_SET_CA_HASH,   /*set ca hash info*/
	GLOBAL_CMD_ID_MAX,    /**< ��ȫ����Global��δ֧�ֵ�����*/
};

#endif
/**
 * History: \n
 * 2013-4-12 sdk: Create this file\n
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
*/
