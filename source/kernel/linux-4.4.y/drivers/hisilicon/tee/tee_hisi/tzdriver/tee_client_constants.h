/*
 * FileName:
 * Author:         sdk  Version: 0.0.1  Date: 2012-12-22
 * Description:
 * Version:
 * Function List:
 *                 1.
 * History:
 *     <author>   <time>    <version >   <desc>
 */

#ifndef _TEE_CLIENT_CONSTANTS_H_
#define _TEE_CLIENT_CONSTANTS_H_

enum global_service_cmd_id {
	GLOBAL_CMD_ID_INVALID = 0x0,
	GLOBAL_CMD_ID_BOOT_ACK = 0x1,
	GLOBAL_CMD_ID_OPEN_SESSION = 0x2,
	GLOBAL_CMD_ID_CLOSE_SESSION = 0x3,
	GLOBAL_CMD_ID_LOAD_SECURE_APP = 0x4,
	/**< Global Task 动态加载安全应用*/
	GLOBAL_CMD_ID_NEED_LOAD_APP = 0x5,/**< Global Task 判断是否是需要加载安全应用*/
	GLOBAL_CMD_ID_REGISTER_AGENT = 0x6,
	GLOBAL_CMD_ID_UNREGISTER_AGENT = 0x7,
	GLOBAL_CMD_ID_REGISTER_NOTIFY_MEMORY = 0x8,
	GLOBAL_CMD_ID_UNREGISTER_NOTIFY_MEMORY = 0x9,
	GLOBAL_CMD_ID_INIT_CONTENT_PATH = 0xa,    /**< Global Task初始化content path*/
	GLOBAL_CMD_ID_TERMINATE_CONTENT_PATH = 0xb,
	/**< Global Task释放content path*/
	GLOBAL_CMD_ID_ALLOC_EXCEPTION_MEM = 0xc,
	GLOBAL_CMD_ID_TEE_TIME = 0xd,
	GLOBAL_CMD_ID_TEE_INFO = 0xe,
	GLOBAL_CMD_ID_REGISTER_RDR_MEM = 0xf,
	GLOBAL_CMD_ID_KILL_TASK = 0x10,   /** Global Task Kill session */
	GLOBAL_CMD_ID_TUI_EXCEPTION = 0x11,   /** TUI异常事件处理 */
	GLOBAL_CMD_ID_ADJUST_TIME = 0x12,   /** TIME时间校正处理 */
	GLOBAL_CMD_ID_SET_CA_HASH = 0x13,   /*set ca hash info设置用于检验CA身份的hash*/
	GLOBAL_CMD_ID_SET_BUILD_VERSION = 0x14, /* set the Android's build version */
	GLOBAL_CMD_ID_REGISTER_TTF_MEM = 0x15,
	GLOBAL_CMD_ID_REGISTER_MAILBOX = 0x17,
	GLOBAL_CMD_ID_UNKNOWN = 0x7FFFFFFE,
	GLOBAL_CMD_ID_MAX = 0x7FFFFFFF
};

/****************************************************
 *		Return Codes
 ****************************************************/
enum TEEC_Result {
	TEEC_SUCCESS = 0x0,
	TEEC_ERROR_INVALID_CMD = 0x1,
	TEEC_ERROR_SERVICE_NOT_EXIST = 0x2,
	TEEC_ERROR_SESSION_NOT_EXIST = 0x3,
	TEEC_ERROR_GENERIC = 0xFFFF0000,
	TEEC_ERROR_ACCESS_DENIED = 0xFFFF0001,
	TEEC_ERROR_CANCEL = 0xFFFF0002,
	TEEC_ERROR_ACCESS_CONFLICT = 0xFFFF0003,
	TEEC_ERROR_EXCESS_DATA = 0xFFFF0004,
	TEEC_ERROR_BAD_FORMAT = 0xFFFF0005,
	TEEC_ERROR_BAD_PARAMETERS = 0xFFFF0006,
	TEEC_ERROR_BAD_STATE = 0xFFFF0007,
	TEEC_ERROR_ITEM_NOT_FOUND = 0xFFFF0008,
	TEEC_ERROR_NOT_IMPLEMENTED = 0xFFFF0009,
	TEEC_ERROR_NOT_SUPPORTED = 0xFFFF000A,
	TEEC_ERROR_NO_DATA = 0xFFFF000B,
	TEEC_ERROR_OUT_OF_MEMORY = 0xFFFF000C,
	TEEC_ERROR_BUSY = 0xFFFF000D,
	TEEC_ERROR_COMMUNICATION = 0xFFFF000E,
	TEEC_ERROR_SECURITY = 0xFFFF000F,
	TEEC_ERROR_SHORT_BUFFER = 0xFFFF0010,
	TEEC_PENDING = 0xFFFF2000,
	TEEC_PENDING2 = 0xFFFF2001,
	TEE_ERROR_TAGET_DEAD = 0xFFFF3024,
	TEE_ERROR_GT_DEAD = 0xFFFF3124,
	TEEC_ERROR_MAC_INVALID = 0xFFFF3071,
	TEEC_CLIENT_INTR = 0xFFFF4000,
	TEE_ERROR_CA_AUTH_FAIL = 0xFFFFCFE5,
};

/****************************************************
 *		Return Code Origins
 ****************************************************/
enum TEEC_ReturnCodeOrigin {
	TEEC_ORIGIN_API = 0x1,
	TEEC_ORIGIN_COMMS = 0x2,
	TEEC_ORIGIN_TEE = 0x3,
	TEEC_ORIGIN_TRUSTED_APP = 0x4,
	TEEC_ORIGIN_TRUSTED_APP_TUI = 0x5,
};

/****************************************************
 *		Shared Memory Control
 ****************************************************/
enum TEEC_SharedMemCtl {
	TEEC_MEM_INPUT = 0x1,
	TEEC_MEM_OUTPUT = 0x2,
	TEEC_MEM_INOUT = 0x3,
};

/****************************************************
 *		API Parameter Types
 ****************************************************/
enum TEEC_ParamType {
	TEEC_NONE = 0x0,
	TEEC_VALUE_INPUT = 0x01,
	TEEC_VALUE_OUTPUT = 0x02,
	TEEC_VALUE_INOUT = 0x03,
	TEEC_MEMREF_TEMP_INPUT = 0x05,
	TEEC_MEMREF_TEMP_OUTPUT = 0x06,
	TEEC_MEMREF_TEMP_INOUT = 0x07,
	TEEC_ION_INPUT = 0x08,
	TEEC_MEMREF_WHOLE = 0xc,
	TEEC_MEMREF_PARTIAL_INPUT = 0xd,
	TEEC_MEMREF_PARTIAL_OUTPUT = 0xe,
	TEEC_MEMREF_PARTIAL_INOUT = 0xf
};
enum TEE_ParamType {
	TEE_PARAM_TYPE_NONE = 0x0,
	TEE_PARAM_TYPE_VALUE_INPUT = 0x1,
	TEE_PARAM_TYPE_VALUE_OUTPUT = 0x2,
	TEE_PARAM_TYPE_VALUE_INOUT = 0x3,
	TEE_PARAM_TYPE_MEMREF_INPUT = 0x5,
	TEE_PARAM_TYPE_MEMREF_OUTPUT = 0x6,
	TEE_PARAM_TYPE_MEMREF_INOUT = 0x7,
	TEE_PARAM_TYPE_ION_INPUT = 0x8,
};

/****************************************************
 *		Session Login Methods
 ****************************************************/
enum TEEC_LoginMethod {
	TEEC_LOGIN_PUBLIC = 0x0,
	TEEC_LOGIN_USER,
	TEEC_LOGIN_GROUP,
	TEEC_LOGIN_APPLICATION = 0x4,
	TEEC_LOGIN_USER_APPLICATION = 0x5,
	TEEC_LOGIN_GROUP_APPLICATION = 0x6,
	TEEC_LOGIN_IDENTIFY = 0x7,
};

/* dir: 0-inclue input, 1-include output, 2-both */
static inline bool teec_value_type(unsigned int type, int dir)
{
	return (((0 == dir || 2 == dir) && TEEC_VALUE_INPUT == type) ||
		((1 == dir || 2 == dir) && TEEC_VALUE_OUTPUT == type) ||
		TEEC_VALUE_INOUT == type) ? true : false;
}

static inline bool teec_tmpmem_type(unsigned int type, int dir)
{
	return (((0 == dir || 2 == dir) && TEEC_MEMREF_TEMP_INPUT == type) ||
		((1 == dir || 2 == dir) && TEEC_MEMREF_TEMP_OUTPUT == type) ||
		TEEC_MEMREF_TEMP_INOUT == type) ? true : false;
}

static inline bool teec_memref_type(unsigned int type, int dir)
{
	return (((0 == dir || 2 == dir) && TEEC_MEMREF_PARTIAL_INPUT == type) ||
		((1 == dir || 2 == dir) && TEEC_MEMREF_PARTIAL_OUTPUT == type) ||
		TEEC_MEMREF_PARTIAL_INOUT == type) ? true : false;
}

#endif
