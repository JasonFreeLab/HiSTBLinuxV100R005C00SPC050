#include <tee_internal_api.h>
#define TA_DEBUG
#include <tee_log.h>

#define HISI_DEMO_CMD_HELLO				0

TEE_Result TA_CreateEntryPoint(void)
{
	return AddCaller_CA_exec("default", 0);
}

TEE_Result TA_OpenSessionEntryPoint(uint32_t paramTypes, TEE_Param params[4], void** sessionContext)
{
	(void)paramTypes;
	(void)params;
	(void)sessionContext;

	return TEE_SUCCESS;
}

TEE_Result TA_InvokeCommandEntryPoint(void* session_context, uint32_t cmd_id, uint32_t paramTypes, TEE_Param params[4])
{
	TEE_Result ret = TEE_ERROR_BAD_PARAMETERS;

	(void)session_context;
	(void)paramTypes;

	switch(cmd_id) {
	case HISI_DEMO_CMD_HELLO:
		ta_debug("Hello, Welcome to Secure World. ^_^  \n");
		params[3].value.a = 0x12345678;
		params[3].value.b = 0x87654321;
		ret = TEE_SUCCESS;
		break;
	default:
		ta_debug("Invalid command!\n");
		break;
	}

	if (TEE_SUCCESS == ret) {
		ta_debug("Invoke command[0x%x] suc\n", cmd_id);
	} else {
		ta_error("Invoke command[0x%x] failed, ret[0x%x]\n", cmd_id, ret);
	}

	return  ret;
}

void TA_CloseSessionEntryPoint(void* session_context)
{
	(void)session_context;
}

void TA_DestroyEntryPoint(void)
{
}
