/*
 * Copyright (c) 2017, Hisilicon Limited
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include <linux/sched.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/version.h>

#include "teek_ns_client.h"
#include "teek_client_api.h"
#include "hisi_ta_auth.h"
#include "libhwsecurec/securec.h"

/* Three CA authentication scenes:
 * 1. TA need user CA authentication. Add TA UUID in g_ta_auth_list, set
 *    st_ta_auth.ca_name and st_ta_auth.uid. When set st_ta_auth.ca_name NULL,
 *    SYSTEM will set it with /proc/pid/cmdline of current task.
 * 2. TA need kernel CA authentication. Most of the same as first scenes(user CA).
 *    NOTE: If st_ta_auth.ca_name is set NULL, TEEC_Operation.params[3].tmpref.buffer
 *    what kernel ca have set will cause different:
 *        1) Set as DEVCHIP_USER_CA_NAME, will be replaced with /proc/pid/cmdline of current task.
 *        2) Set other value, will keep what have set.
 * 3. TA do not need any CA authentication. Remove TA uuid in g_ta_auth_list.
 *    And DEVCHIP_DEFAULT_CA_NAME in TA TA_CreateEntryPoint(), such as
 *    AddCaller_CA_exec("default", 0);
 */
static st_ta_auth g_ta_auth_list[] = {
	{TEE_SERVICE_WIDEVINE, "hisi_widevine_client", 0},
	{TEE_SERVICE_PLAYREADY, "hisi_playready_client", 0},
	{TEE_SERVICE_PLAYREADY, NULL, 0},
	{TEE_SERVICE_HDMI, NULL, 0},
	{TEE_SERVICE_CRYPTO_VERIFY, NULL, 0},
	{TEE_SERVICE_DRM, NULL, 0},
	{TEE_SERVICE_SEC_MMZ, NULL, 0},
	{TEE_SERVICE_VFMW, NULL, 0},
	{TEE_SERVICE_HISI_VDP, NULL, 0},
	{TEE_SERVICE_SMMU, NULL, 0},
	{TEE_SERVICE_VPSS, NULL, 0},
	{TEE_SERVICE_DMX, "tee_dmx_general_session", 0},
	{TEE_SERVICE_COMMON, "tee_common_session", 0},
	{TEE_SERVICE_PLCIPHER, "tee_plcipher_session", 0},
	{TEE_SERVICE_KLAD, NULL, 0},
	{TEE_SERVICE_CRYPTOEN, NULL, 0},
	{TEE_SERVICE_PVR, "hisi_pvr_client", 0},
	{TEE_SERVICE_AVPLAY, NULL, 0},
	{TEE_SERVICE_MCU, NULL, 0},
	{TEE_SERVICE_LOG, NULL, 0},
	{TEE_SERVICE_STB_UPDATE_TA, NULL, 0},
	{TEE_SERVICE_STB_DISPLAY_TA, NULL, 0},
	{TEE_SERVICE_DCAS_COMMON, NULL, 0},
	{TEE_SERVICE_DCAS_NDS, NULL, 0},
	{TEE_SERVICE_DCAS_SUMA, NULL, 0},
	{TEE_SERVICE_DCAS_NOVEL, NULL, 0},
	{TEE_SERVICE_NETFLIX, NULL, 0},
	{TEE_SERVICE_SESSION_MANAGE, NULL, 0},	
};

static int hisi_set_ca_info(TC_NS_DEV_File *dev_file, char *ca_name, unsigned int ca_uid)
{
	if (!dev_file || !ca_name) {
		TCERR("invalid input\n");
		return -1;
	}

	/* uid */
	if (memset_s(dev_file->pub_key, sizeof(dev_file->pub_key), 0, sizeof(dev_file->pub_key))) {
		TCERR("memset_s failed\n");
		return -1;
	}

	if (memcpy_s(dev_file->pub_key, sizeof(dev_file->pub_key), &ca_uid, sizeof(ca_uid))) {
		TCERR("memcpy_s failed\n");
		return -1;
	}

	dev_file->pub_key_len = sizeof(ca_uid);

	/* CA name */
	if (memset_s(dev_file->pkg_name, sizeof(dev_file->pkg_name), 0, sizeof(dev_file->pkg_name))) {
		TCERR("memset_s failed\n");
		return -1;
	}

	if (memcpy_s(dev_file->pkg_name, sizeof(dev_file->pkg_name), ca_name, strlen(ca_name))) {
		TCERR("memcpy_s failed\n");
		return -1;
	}
	dev_file->pkg_name_len = strlen(ca_name);

	return 0;
}

/* get process name form /proc/pid/cmdline */
static int hisi_get_process_name(unsigned int pid, char *name, unsigned int size)
{
	struct file *filp = NULL;
    mm_segment_t oldfs;
    int ret = 0;
	char file_path[MAX_PACKAGE_NAME_LEN];
	char cmdline[MAX_PACKAGE_NAME_LEN];
	char *p = NULL;
	loff_t pos = 0;

	if (!name) {
		TCERR("invalid input\n");
		return -1;
	}

	ret = memset_s(cmdline, sizeof(cmdline), 0x0, sizeof(cmdline));
	if (ret) {
		TCERR("memset_s failed!\n");
		return -1;
	}

	ret = memset_s(file_path, sizeof(file_path), 0, sizeof(file_path));
	if (ret) {
		TCERR("memset_s failed\n");
		return -1;
	}

	memset_s(name, size, 0x0, size);
	if (ret) {
		TCERR("memset_s failed!\n");
		return -1;
	}

	ret = snprintf_s(file_path, sizeof(file_path) - 1, sizeof(file_path) - 1, "/proc/%d/cmdline", pid);
	if (-1 == ret) {
		TCERR("snprintf_s failed %d\n", ret);
		return -1;
	}

    oldfs = get_fs();
    set_fs(get_ds());
    filp = filp_open(file_path, O_RDONLY, 0);
	if (IS_ERR(filp)) {
		set_fs(oldfs);
		TCERR("filp_open failed\n");
        return -1;
    }

	ret = vfs_read(filp, cmdline, size, &pos);
    set_fs(oldfs);
	filp_close(filp, NULL);
	filp = NULL;

	p = strchr(cmdline, ' '); /* find the first blank */
	if (p)
		cmdline[p - cmdline] = '\0'; /* delete parameters */

	ret = snprintf_s(name, size, strlen(cmdline), "%s", cmdline);
	if (-1 == ret) {
		TCERR("snprintf_s failed %d\n", ret);
		return -1;
	}

	return 0;
}

/* set ca with process information get by current task */
static int hisi_set_ca_by_system(TC_NS_DEV_File *dev_file, struct task_struct *ca_task)
{
	const struct cred *cred = NULL;
	char ca_name[MAX_PACKAGE_NAME_LEN];
	unsigned ca_uid = 0;
	int ret;

	if (!ca_task || !dev_file) {
		TCERR("invalid input\n");
		return -1;
	}

	if (memset_s(ca_name, MAX_PACKAGE_NAME_LEN, 0, MAX_PACKAGE_NAME_LEN)) {
		TCERR("memcpy_s failed\n");
		return -1;
	}

	ret = hisi_get_process_name(ca_task->pid, ca_name, sizeof(ca_name));
	if (ret) {
		TCERR("get ca name failed\n");
		return -1;
	}

	cred = get_task_cred(ca_task);
	if (!cred) {
		TCERR("get task cred failed\n");
		return -1;
	}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 13, 0))
	ca_uid = cred->uid.val;
#else
	ca_uid = cred->uid;
#endif
	put_cred(cred);

	return hisi_set_ca_info(dev_file, ca_name, ca_uid);
}

static int hisi_get_ta_auth_list(st_ta_auth **ta_auth, unsigned int *num)
{
	if (!ta_auth || !num)
		return -1;

	*ta_auth = (st_ta_auth *)&g_ta_auth_list;
	*num = sizeof(g_ta_auth_list) / sizeof(st_ta_auth);
	return 0;
}

int hisi_set_ca_login_info(TC_NS_DEV_File *dev_file, TC_NS_ClientContext *context)
{
	unsigned int i;
	unsigned int num;
	st_ta_auth *ta_auth = NULL;

	if (!dev_file || !context) {
		TCERR("invalid input\n");
		return -1;
	}

	if (hisi_get_ta_auth_list(&ta_auth, &num)) {
		TCERR("get ta auth list failed\n");
		return -1;
	}

	for (i = 0; i < num; i++) {
		if (!memcmp(ta_auth->uuid, context->uuid, sizeof(context->uuid))) {
			if (ta_auth->ca_name) {
				/* any ca, set it with fixed value */
				return hisi_set_ca_info(dev_file, ta_auth->ca_name, ta_auth->uid);
			} else if (!memcmp(dev_file->pkg_name, DEVCHIP_USER_CA_NAME, strlen(DEVCHIP_USER_CA_NAME))) {
				/* user ca, set it with current process */
				return hisi_set_ca_by_system(dev_file, current);
			} else {
				/* kernel ca, keep the what it set */
				return 0;
			}
		}
		ta_auth++;
	}

	return hisi_set_ca_info(dev_file, DEVCHIP_DEFAULT_CA_NAME, DEVCHIP_DEFAULT_CA_UID);
}
