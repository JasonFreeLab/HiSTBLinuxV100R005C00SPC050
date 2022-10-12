/*******************************************************************************
* All rights reserved, Copyright (C) huawei LIMITED 2012
*------------------------------------------------------------------------------
* File Name   : tc_client_driver.c
* Description :
* Platform	  :
* Author	  : qiqingchao
* Version	  : V1.0
* Date		  : 2012.12.10
* Notes	:
*
*------------------------------------------------------------------------------
* Modifications:
*	Date		Author			Modifications
*******************************************************************************/
/*******************************************************************************
 * This source code has been made available to you by HUAWEI on an
 * AS-IS basis. Anyone receiving this source code is licensed under HUAWEI
 * copyrights to use it in any way he or she deems fit, including copying it,
 * modifying it, compiling it, and redistributing it either with or without
 * modifications. Any person who transfers this source code or any derivative
 * work must include the HUAWEI copyright notice and this paragraph in
 * the transferred software.
*******************************************************************************/

#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/mutex.h>
#include <linux/kthread.h>
#include <linux/freezer.h>
#include <linux/module.h>
#include <linux/atomic.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#include "tee_client_constants.h"
#include "teek_ns_client.h"
#include "smc.h"
#include "agent.h"
#include "mem.h"
#include "tui.h"
#include "securec.h"
#include "tc_ns_log.h"
#include "mailbox_mempool.h"

#define HASH_FILE_MAX_SIZE 8192
#define AGENT_BUFF_SIZE (4*1024)

static struct list_head tee_agent_list;

struct __agent_control {
	spinlock_t lock;
	struct list_head agent_list;
};
static struct __agent_control agent_control;

int TC_NS_set_nativeCA_hash(unsigned long arg)
{
	int ret = 0;
	TC_NS_SMC_CMD smc_cmd = { 0 };
	uint8_t *inbuf = (uint8_t *)arg;
	uint32_t buflen = 0;
	uint8_t *buftotee = NULL;
	struct mb_cmd_pack *mb_pack;

	if (NULL == inbuf)
		return -1;

	if (TC_NS_get_uid() != 0) {
		tloge("It is a fake tee agent\n");
		return -EACCES;
	}

	if (copy_from_user(&buflen, inbuf, sizeof(buflen))) {
		tloge("copy from user failed\n");
		return -EFAULT;
	}
	if (buflen > HASH_FILE_MAX_SIZE) {
		tloge("ERROR: file size[0x%x] too big\n", buflen);
		return -1;
	}

	buftotee = mailbox_alloc(buflen, 0);
	if (!buftotee) {
		tloge("failed to alloc memory!\n");
		return -1; /*lint !e429 */
	}

	if (copy_from_user(buftotee, inbuf, buflen)) { /*lint !e613 !e668 */
		tloge("copy from user failed\n");
		mailbox_free(buftotee);
		return -EFAULT;
	}

	mb_pack = mailbox_alloc_cmd_pack();
	if (!mb_pack) {
		tloge("alloc cmd pack failed\n");
		mailbox_free(buftotee);
		return -ENOMEM;
	}

	mb_pack->operation.paramTypes = TEE_PARAM_TYPE_VALUE_INPUT |
				(TEE_PARAM_TYPE_VALUE_INPUT << 4);
	mb_pack->operation.params[0].value.a = (unsigned int)virt_to_phys(buftotee);
	mb_pack->operation.params[0].value.b = (unsigned int)(virt_to_phys(buftotee) >> 32); /*lint !e572*/
	mb_pack->operation.params[1].value.a = buflen;

	mb_pack->uuid[0] = 1;
	smc_cmd.uuid_phys = virt_to_phys(mb_pack->uuid);
	smc_cmd.uuid_h_phys = virt_to_phys(mb_pack->uuid) >> 32; /*lint !e572*/
	smc_cmd.cmd_id = GLOBAL_CMD_ID_SET_CA_HASH;
	smc_cmd.operation_phys = virt_to_phys(&mb_pack->operation);
	smc_cmd.operation_h_phys = virt_to_phys(&mb_pack->operation) >> 32; /*lint !e572*/

	ret = TC_NS_SMC(&smc_cmd, 0);

	mailbox_free(buftotee);
	mailbox_free(mb_pack);

	return ret;
}


void TC_NS_send_event_response_all(void)
{
	struct __smc_event_data *event_data = NULL;

	if (TC_NS_send_event_response(AGENT_FS_ID))
		tlogd("failed to send response to AGENT_FS_ID\n");
	event_data = find_event_control(AGENT_FS_ID);
	if (event_data)
		event_data->agent_alive = 0;
	if (TC_NS_send_event_response(AGENT_MISC_ID))
		tlogd("failed to send response to AGENT_MISC_ID\n");
	event_data = find_event_control(AGENT_MISC_ID);
	if (event_data)
		event_data->agent_alive = 0;
	if (TC_NS_send_event_response(AGENT_SOCKET_ID))
		tlogd("failed to send response to AGENT_SOCKET_ID\n");
	event_data = find_event_control(AGENT_SOCKET_ID);
	if (event_data)
		event_data->agent_alive = 0;

}


struct __smc_event_data *find_event_control(unsigned int agent_id)
{
	struct __smc_event_data *event_data = NULL, *tmp_data = NULL;
	unsigned long flags;

	spin_lock_irqsave(&agent_control.lock, flags);
	list_for_each_entry(event_data, &agent_control.agent_list, head) {/*lint !e64 !e826*/
		if (event_data->agent_id == agent_id) {
			tmp_data = event_data;
			break;
		}
	}
	spin_unlock_irqrestore(&agent_control.lock, flags);

	return tmp_data;
}


unsigned int agent_process_work(TC_NS_SMC_CMD *smc_cmd, unsigned int agent_id)
{
	struct __smc_event_data *event_data;

	if (NULL == smc_cmd) {
		/*TODO: if return, the pending task in S can't be resumed!! */
		tloge("agent %u not exist\n", agent_id);
		return TEEC_ERROR_GENERIC;
	}
	tlogd("agent_id=0x%x\n", agent_id);
	/* TODO: needs lock */
	event_data = find_event_control(agent_id);
	if ( NULL == event_data || 0 == event_data->agent_alive) {
		/*TODO: if return, the pending task in S can't be resumed!! */
		tloge("agent %u not exist\n", agent_id);
		return TEEC_ERROR_GENERIC;/*lint !e570*/
	}
	tlogd("agent_process_work: returning client command");

	/* store tui working device for terminate tui
	 * when this device is closed.
	 */
	if (agent_id == TEE_TUI_AGENT_ID)
		set_tui_attach_device(smc_cmd->dev_file_id);

	/* Keep a copy of the SMC cmd to return to TEE when the work is done */
	if (memcpy_s(&event_data->cmd, sizeof(TC_NS_SMC_CMD), smc_cmd, sizeof(TC_NS_SMC_CMD))) {
		tloge("failed to memcpy_s smc_cmd\n");
		return TEEC_ERROR_GENERIC;
	}
	isb();
	wmb();
	event_data->ret_flag = 1;
	/* Wake up the agent that will process the command */
	tlogd("agent_process_work: wakeup the agent");
	wake_up(&event_data->wait_event_wq);

	return TEEC_SUCCESS;
}

/*
 * ADDED BY HISILICON.
 *
 * Function:	  TC_NS_wakeup_event
 * Description:   This function used for informing the agent to exit when driver rmmod.
 * Used For klad driver currently.
 * Parameters:	 agent_id.
 */
int TC_NS_wakeup_event(unsigned int agent_id)
{
	struct __smc_event_data *event_data;

	event_data = find_event_control(agent_id);
	if ( NULL == event_data || 0 == event_data->agent_alive) {
		/*TODO: if return, the pending task in S can't be resumed!! */
		tloge("agent %u not exist\n", agent_id);
		return TEEC_ERROR_GENERIC;/*lint !e570*/
	}

	/* Wake up the agent that will process the command */
	tlogd("agent_process_work: wakeup the agent %p",&event_data->wait_event_wq);
    event_data->ret_flag = 1;
	wake_up(&event_data->wait_event_wq);
    return 0;
}

/*
 * Function:	  is_agent_alive
 * Description:   This function check if the special agent is launched.
 * Used For HDCP key.
 * e.g. If sfs agent is not alive,
 * you can not do HDCP key write to SRAM.
 * Parameters:	 agent_id.
 * Return:		1:agent is alive
 *				0:agent not exsit.
 */
int is_agent_alive(unsigned int agent_id)
{
	if (find_event_control(agent_id))
		return 1;
	else
		return 0;
}

int TC_NS_wait_event(unsigned int agent_id)
{
	int ret = -EINVAL;
	struct __smc_event_data *event_data;

	if (TC_NS_get_uid() != 0) {
		tloge("It is a fake tee agent\n");
		return -EACCES;
	}

	event_data = find_event_control(agent_id);
	tlogd("agent %u waits for command\n", agent_id);
	if (event_data) {
		/* wait event will return either 0 or -ERESTARTSYS so just
		 * return it further to the ioctl handler */
		ret = wait_event_interruptible(event_data->wait_event_wq,/*lint !e774 !e845 !e712 !e40*/
					       event_data->ret_flag);
	} else {
	     return -EINVAL;
	}

	return ret;
}


int TC_NS_sync_sys_time(TC_NS_Time *tc_ns_time)
{
	TC_NS_SMC_CMD smc_cmd = { 0 };
	int ret = 0;
	TC_NS_Time tmp_tc_ns_time = {0};
	struct mb_cmd_pack *mb_pack = NULL;

	if (!tc_ns_time) {
		tloge("tc_ns_time is NULL input buffer\n");
		return -EINVAL;
	}
	if (TC_NS_get_uid() != 0) {
		tloge("It is a fake tee agent\n");
		return TEEC_ERROR_GENERIC;
	}
	if (copy_from_user(&tmp_tc_ns_time, tc_ns_time, sizeof(TC_NS_Time))) {
		tloge("copy from user failed\n");
		return -EFAULT;
	}

	mb_pack = mailbox_alloc_cmd_pack();
	if (!mb_pack) {
		tloge("alloc mb pack failed\n");
		return -ENOMEM;
	}

	mb_pack->uuid[0] = 1;
	smc_cmd.uuid_phys = virt_to_phys(mb_pack->uuid);
	smc_cmd.uuid_h_phys = virt_to_phys(mb_pack->uuid) >> 32; /*lint !e572*/
	smc_cmd.cmd_id = GLOBAL_CMD_ID_ADJUST_TIME;
	smc_cmd.err_origin = (unsigned int)tmp_tc_ns_time.seconds;
	smc_cmd.ret_val = (unsigned int)tmp_tc_ns_time.millis;

	ret = TC_NS_SMC(&smc_cmd, 0);
	if (ret)
		tloge("tee adjust time failed, return error %x\n", ret);

	mailbox_free(mb_pack);

	return ret;
}


int TC_NS_send_event_response(unsigned int agent_id)
{
	struct __smc_event_data *event_data = find_event_control(agent_id);

	if (TC_NS_get_uid() != 0) {
		tloge("It is a fake tee agent\n");
		return -1;
	}

	tlogd("agent %u sends answer back\n", agent_id);
	if (event_data && event_data->ret_flag) {
		event_data->send_flag = 1;
		event_data->ret_flag = 0;
		/* Send the command back to the TA session waiting for it */
		return TC_NS_POST_SMC(&event_data->cmd);
	}
	return -EINVAL;
}


int TC_NS_register_agent(TC_NS_DEV_File *dev_file, unsigned int agent_id,
			 TC_NS_Shared_MEM *shared_mem)
{
	TC_NS_SMC_CMD smc_cmd = { 0 };
	struct __smc_event_data *event_data = NULL;
	int ret = 0;
	int find_flag = 0;
	unsigned long flags;
	struct mb_cmd_pack *mb_pack = NULL;

	if (TC_NS_get_uid() != 0) {
		tloge("It is a fake tee agent\n");
		ret = TEEC_ERROR_GENERIC;
		goto error;
	}

	spin_lock_irqsave(&agent_control.lock, flags);
	list_for_each_entry(event_data, &agent_control.agent_list, head) {
		if (event_data->agent_id == agent_id) {
			find_flag = 1;
			break;
		}
	}
	spin_unlock_irqrestore(&agent_control.lock, flags);

	if (find_flag) {
		if ((AGENT_FS_ID == agent_id) || (AGENT_MISC_ID == agent_id)
		    || (AGENT_SOCKET_ID == agent_id)) {
			event_data->ret_flag = 0;
			event_data->send_flag = 0;
			event_data->owner = dev_file;
			event_data->agent_alive = 1;
			init_waitqueue_head(&(event_data->wait_event_wq));
			init_waitqueue_head(&(event_data->send_response_wq));
			ret = TEEC_SUCCESS;
		} else
			ret = TEEC_ERROR_GENERIC;
		goto error;
	}

	if (!shared_mem) {
		tloge("shared mem is not exist\n");
		ret = TEEC_ERROR_GENERIC;
		goto error;
	}

	mb_pack = mailbox_alloc_cmd_pack();
	if (!mb_pack) {
		tloge("alloc mailbox failed\n");
		ret = TEEC_ERROR_GENERIC;
		goto error;
	}

	mb_pack->operation.paramTypes = TEE_PARAM_TYPE_VALUE_INPUT | (TEE_PARAM_TYPE_VALUE_INPUT << 4);
	mb_pack->operation.params[0].value.a = virt_to_phys(shared_mem->kernel_addr);
	mb_pack->operation.params[0].value.b = virt_to_phys(shared_mem->kernel_addr) >> 32; /*lint !e572*/
	mb_pack->operation.params[1].value.a = shared_mem->len;

	mb_pack->uuid[0] = 1;
	smc_cmd.uuid_phys = virt_to_phys(mb_pack->uuid);
	smc_cmd.uuid_h_phys = virt_to_phys(mb_pack->uuid) >> 32; /*lint !e572*/
	smc_cmd.cmd_id = GLOBAL_CMD_ID_REGISTER_AGENT;
	smc_cmd.operation_phys = virt_to_phys(&mb_pack->operation);
	smc_cmd.operation_h_phys = virt_to_phys(&mb_pack->operation) >> 32; /*lint !e572*/
	smc_cmd.agent_id = agent_id;

	ret = TC_NS_SMC(&smc_cmd, 0);

	if (ret == TEEC_SUCCESS) {
		event_data =
			kzalloc(sizeof(struct __smc_event_data), GFP_KERNEL);
		if (!event_data) {
			ret = -ENOMEM;
			goto error;
		}
		event_data->agent_id = agent_id;
		mutex_init(&event_data->work_lock);
		event_data->ret_flag = 0;
		event_data->send_flag = 0;
		event_data->buffer = shared_mem;
		event_data->owner = dev_file;
		event_data->agent_alive = 1;
		init_waitqueue_head(&(event_data->wait_event_wq));
		init_waitqueue_head(&(event_data->send_response_wq));
		INIT_LIST_HEAD(&event_data->head);

		spin_lock_irqsave(&agent_control.lock, flags);
		list_add_tail(&event_data->head, &agent_control.agent_list);
		spin_unlock_irqrestore(&agent_control.lock, flags);
	}

error:
	if (mb_pack)
		mailbox_free(mb_pack);
	return ret; /*lint !e429 */
}


int TC_NS_unregister_agent(unsigned int agent_id)
{
	struct __smc_event_data *event_data = NULL;
	int ret = 0;
	int find_flag = 0;
	unsigned long flags;
	TC_NS_SMC_CMD smc_cmd = { 0 };
	struct mb_cmd_pack *mb_pack = NULL;
	struct tee_agent_kernel_ops *agent_ops = NULL;
	struct tee_agent_kernel_ops *tmp_ops = NULL;

	if (TC_NS_get_uid() != 0) {
		tloge("It is a fake tee agent\n");
		return TEEC_ERROR_GENERIC;
	}
	if (AGENT_FS_ID == agent_id || AGENT_MISC_ID == agent_id ||
	    AGENT_RPMB_ID == agent_id || AGENT_SOCKET_ID == agent_id ||
	    TEE_TUI_AGENT_ID == agent_id) {
		tloge("system agent is not allowed to unregister\n");
		return TEEC_ERROR_GENERIC;
	}

	spin_lock_irqsave(&agent_control.lock, flags);
	list_for_each_entry(event_data, &agent_control.agent_list, head) {
		if (event_data->agent_id == agent_id) {
			find_flag = 1;
			list_del(&event_data->head);
			break;
		}
	}
	spin_unlock_irqrestore(&agent_control.lock, flags);

	if (!find_flag) {
		tloge("agent is not found\n");
		return TEEC_ERROR_GENERIC;
	}

	mb_pack = mailbox_alloc_cmd_pack();
	if (!mb_pack) {
		tloge("alloc mailbox failed\n");
		return TEEC_ERROR_GENERIC;
	}

	mb_pack->operation.paramTypes = TEE_PARAM_TYPE_VALUE_INPUT | (TEE_PARAM_TYPE_VALUE_INPUT << 4);
	mb_pack->operation.params[0].value.a = virt_to_phys(event_data->buffer->kernel_addr);
	mb_pack->operation.params[0].value.b = virt_to_phys(event_data->buffer->kernel_addr) >> 32; /*lint !e572*/
	mb_pack->operation.params[1].value.a = SZ_4K;

	mb_pack->uuid[0] = 1;
	smc_cmd.uuid_phys = virt_to_phys(mb_pack->uuid);
	smc_cmd.uuid_h_phys = virt_to_phys(mb_pack->uuid) >> 32; /*lint !e572*/
	smc_cmd.cmd_id = GLOBAL_CMD_ID_UNREGISTER_AGENT;
	smc_cmd.operation_phys = virt_to_phys(&mb_pack->operation);
	smc_cmd.operation_h_phys = virt_to_phys(&mb_pack->operation) >> 32; /*lint !e572*/
	smc_cmd.agent_id = agent_id;

	mutex_lock(&event_data->work_lock);
	tlogd("Unregistering agent %u\n", agent_id);
	ret = TC_NS_SMC(&smc_cmd, 0);
	mutex_unlock(&event_data->work_lock);
	mailbox_free(mb_pack);

	list_for_each_entry_safe(agent_ops, tmp_ops, &tee_agent_list, list) {
		if (agent_ops->agent_id == agent_id) {
			list_del(&agent_ops->list);
			break;
		}
	}

	return ret;
}


int TC_NS_unregister_agent_client(TC_NS_DEV_File *dev_file)
{
	struct __smc_event_data *event_data = NULL;
	struct __smc_event_data	*tmp = NULL;

	list_for_each_entry_safe(event_data, tmp,
				 &agent_control.agent_list, head) {
		if (event_data->owner == dev_file)
			TC_NS_unregister_agent(event_data->agent_id);
	}
	return TEEC_SUCCESS;
}
static int def_tee_agent_work(void *instance)
{
	int ret = 0;
	struct tee_agent_kernel_ops *agent_instance;
	agent_instance = (struct tee_agent_kernel_ops *)instance;

	while (!kthread_should_stop()) {
		tlogd("%s agent loop++++\n", agent_instance->agent_name);
		ret = TC_NS_wait_event(agent_instance->agent_id);
		if (ret) {
			tloge("%s wait event fail\n",
			      agent_instance->agent_name);
			break;
		}

		if (agent_instance->tee_agent_work) {
			ret = agent_instance->tee_agent_work(agent_instance);
			if (ret) {
			    tloge("%s agent work fail\n",
				  agent_instance->agent_name);
			}
		}

		ret = TC_NS_send_event_response(agent_instance->agent_id);
		if (ret) {
			tloge("%s send event response fail\n",
			      agent_instance->agent_name);
			break;
		}
		tlogd("%s agent loop----\n", agent_instance->agent_name);
	}

	return ret;
}


static int def_tee_agent_run(struct tee_agent_kernel_ops *agent_instance)
{
	TC_NS_Shared_MEM *shared_mem = NULL;
	TC_NS_DEV_File dev = {0};
	int ret = 0;
	int page_order = 8;

	/*1. Allocate agent buffer */
	shared_mem = tc_mem_allocate(&dev, (size_t)(unsigned)(AGENT_BUFF_SIZE * page_order), true);
	while ((IS_ERR(shared_mem)) && (page_order > 0)) {
		page_order /= 2;
		shared_mem = tc_mem_allocate(&dev, (size_t)(unsigned)(AGENT_BUFF_SIZE * page_order), true);
	}
	if (IS_ERR(shared_mem)) {
		tloge("allocate agent buffer fail\n");
		ret = PTR_ERR(shared_mem);
		goto out;
	}
	agent_instance->agent_buffer = shared_mem;

	/*2. Register agent buffer to TEE */
	ret = TC_NS_register_agent(&dev, agent_instance->agent_id, shared_mem);
	if (ret) {
		tloge("register agent buffer fail\n");
		ret = -1;
		goto out;
	}

	/*3. Creat thread to run agent */
	agent_instance->agent_thread =
		kthread_run(def_tee_agent_work, (void *)agent_instance, "agent_%s",
			    agent_instance->agent_name);
	if (IS_ERR(agent_instance->agent_thread)) {
		tloge("kthread creat fail\n");
		ret = PTR_ERR(agent_instance->agent_thread);
		agent_instance->agent_thread = NULL;
		goto out;
	}
	return 0;

out:
	if (!IS_ERR_OR_NULL(shared_mem))
		tc_mem_free(shared_mem);
	return ret;
}


static int def_tee_agent_stop(struct tee_agent_kernel_ops *agent_instance)
{
	int ret;
	if (TC_NS_send_event_response(agent_instance->agent_id))
		tloge("failed to send response for agent %d\n", agent_instance->agent_id);
	ret = TC_NS_unregister_agent(agent_instance->agent_id);
	if (0 != ret)
		tloge("failed to unregister agent %d\n", agent_instance->agent_id);
	if (!IS_ERR_OR_NULL(agent_instance->agent_thread))
		kthread_stop(agent_instance->agent_thread);
	return 0;
}


static struct tee_agent_kernel_ops def_tee_agent_ops = {
	.agent_name = "default",
	.agent_id = 0,
	.tee_agent_init = NULL,
	.tee_agent_run = def_tee_agent_run,
	.tee_agent_work = NULL,
	.tee_agent_exit = NULL,
	.tee_agent_stop = def_tee_agent_stop,
	.tee_agent_crash_work = NULL,
	.list = LIST_HEAD_INIT(def_tee_agent_ops.list)
};


static int tee_agent_kernel_init(void)
{
	struct tee_agent_kernel_ops *agent_ops = NULL;
	int ret = 0;

	list_for_each_entry(agent_ops, &tee_agent_list, list) {
		/* Check the agent validity */
		if ((0 == agent_ops->agent_id)
		    || (NULL == agent_ops->agent_name)
		    || (NULL == agent_ops->tee_agent_work)) {
			tloge("agent is invalid\n");
			continue;
		}
		tlogd("ready to init %s agent, id=0x%x\n",
			agent_ops->agent_name, agent_ops->agent_id);

		/* Initialize the agent */
		if (agent_ops->tee_agent_init)
			ret = agent_ops->tee_agent_init(agent_ops);
		else if (def_tee_agent_ops.tee_agent_init)
			ret = def_tee_agent_ops.tee_agent_init(agent_ops);
		else
		    tlogw("agent id %d has no init function\n", agent_ops->agent_id);
		if (ret) {
			tloge("tee_agent_init %s failed\n",
			      agent_ops->agent_name);
			continue;
		}

		/* Run the agent */
		if (agent_ops->tee_agent_run)
			ret = agent_ops->tee_agent_run(agent_ops);
		else if (def_tee_agent_ops.tee_agent_run)
			ret = def_tee_agent_ops.tee_agent_run(agent_ops);
		else
		    tlogw("agent id %d has no run function\n", agent_ops->agent_id);
		if (ret) {
			tloge("tee_agent_run %s failed\n",
			      agent_ops->agent_name);
			if (agent_ops->tee_agent_exit)
				agent_ops->tee_agent_exit(agent_ops);
			continue;
		}
	}

	return 0;
}


static int tee_agent_kernel_exit(void)
{
	struct tee_agent_kernel_ops *agent_ops = NULL;

	list_for_each_entry(agent_ops, &tee_agent_list, list) {

		/* Stop the agent */
		if (agent_ops->tee_agent_stop)
			agent_ops->tee_agent_stop(agent_ops);
		else if (def_tee_agent_ops.tee_agent_stop)
			def_tee_agent_ops.tee_agent_stop(agent_ops);
		else
		    tlogw("agent id %d has no stop function\n", agent_ops->agent_id);
		/* Uninitialize the agent */
		if (agent_ops->tee_agent_exit)
			agent_ops->tee_agent_exit(agent_ops);
		else if (def_tee_agent_ops.tee_agent_exit)
			def_tee_agent_ops.tee_agent_exit(agent_ops);
		else
		    tlogw("agent id %d has no exit function\n", agent_ops->agent_id);
	}
	return 0;
}


int tee_agent_clear_work(TC_NS_ClientContext *context,
			 unsigned int dev_file_id)
{
	struct tee_agent_kernel_ops *agent_ops = NULL;

	list_for_each_entry(agent_ops, &tee_agent_list, list) {
		if (agent_ops->tee_agent_crash_work)
			agent_ops->tee_agent_crash_work(agent_ops, context,
							dev_file_id);
	}
	return 0;
}


int tee_agent_kernel_register(struct tee_agent_kernel_ops *new_agent)
{
	if (NULL == new_agent)
		return -1;

	INIT_LIST_HEAD(&new_agent->list);
	list_add_tail(&new_agent->list, &tee_agent_list);
	return 0;
}


int agent_init(void)
{
	spin_lock_init(&agent_control.lock);
	INIT_LIST_HEAD(&agent_control.agent_list);

	INIT_LIST_HEAD(&tee_agent_list);
#ifdef CONFIG_MMC
	rpmb_agent_register();
#endif
	tee_agent_kernel_init();
	return 0;
}


int agent_exit(void)
{
	tee_agent_kernel_exit();
	return 0;
}
#ifdef CONFIG_DEVCHIP_PLATFORM
//by hxw, do not chg
EXPORT_SYMBOL(tee_agent_kernel_register);
EXPORT_SYMBOL(TC_NS_register_agent);
EXPORT_SYMBOL(TC_NS_unregister_agent);
EXPORT_SYMBOL(TC_NS_send_event_response);
EXPORT_SYMBOL(TC_NS_wait_event);
EXPORT_SYMBOL(TC_NS_wakeup_event);
#endif
