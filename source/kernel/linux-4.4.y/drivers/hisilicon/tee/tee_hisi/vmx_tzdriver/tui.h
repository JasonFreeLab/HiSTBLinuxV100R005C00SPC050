#ifndef __TUI_H
#define __TUI_H

#include "tc_ns_client.h"

#define TEE_TUI_AGENT_ID    0x54554944	/* TUID */

/* tui states */
#define TUI_STATE_UNUSED	0
#define TUI_STATE_CONFIG	1
#define TUI_STATE_RUNNING	2
#define TUI_STATE_ERROR	3

/* command from secure os */
#define TUI_CMD_ENABLE		1
#define TUI_CMD_DISABLE		2
#define TUI_CMD_POLL		3
#define TUI_CMD_SET_STATE	4
#define TUI_CMD_PAUSE		5
#define TUI_CMD_DO_SYNC		6
#define TUI_CMD_START_DELAY_WORK	7
#define TUI_CMD_CANCEL_DELAY_WORK	8
#define TUI_CMD_SEND_INPUT_WORK 9

#define TUI_DRV_NAME_MAX	32

/* poll event type from normal to secure */
enum tui_poll_type {
	TUI_POLL_CFG_OK,
	TUI_POLL_CFG_FAIL,
	TUI_POLL_TP,
	TUI_POLL_TICK,
	TUI_POLL_DELAYED_WORK,
	TUI_POLL_PAUSE_TUI,
	TUI_POLL_RESUME_TUI,
/* For some reasons, we need a method to terminate TUI from no-secure
 * OS, for example the TUI CA maybe killed.
 */
	TUI_POLL_CANCEL,
	TUI_POLL_HANDLE_TUI,	/*for tui to handle event*/
	TUI_POLL_NAVI_H_TO_S,	/*for navigator hide and show*/
	TUI_POLL_NAVI_S_TO_H,
	TUI_POLL_SHS_0_TO_1,	/*for single hand mode switch*/
	TUI_POLL_SHS_0_TO_2,
	TUI_POLL_SHS_1_TO_0,
	TUI_POLL_SHS_2_TO_0,
	TUI_POLL_ROTATION_0,	/*for retation switch*/
	TUI_POLL_ROTATION_90,
	TUI_POLL_ROTATION_180,
	TUI_POLL_ROTATION_270,
	TUI_POLL_KEYBOARDTYPE_0,
	TUI_POLL_KEYBOARDTYPE_3,
	TUI_POLL_SEMITRANS,
	TUI_POLL_CURSOR,
	TUI_POLL_GETFP,
	TUI_POLL_MAX			/*Do Not add type behine this one*/
};

/* tui-max should be bigger than TUI_POLL_MAX in tui.h*/
static const char *const poll_event_type_name[] = {
	"config-ok",
	"config-fail",
	"tp",
	"tui-tick",
	"tui-delaywork",
	"tui-pause",
	"tui-resume",
	"tui-terminate",
	"tui-handle",
	"tui-hs",
	"tui-sh",
	"tui-01",
	"tui-02",
	"tui-10",
	"tui-20",
	"tui-0",
	"tui-90",
	"tui-180",
	"tui-270",
	"tui-k0",
	"tui-k3",
	"tui-SEMI",
	"tui-cursor",
	"tui-gettp",
	"tui-max"
};

static const char *const state_name[] = {
	"unused",
	"config",
	"running",
	"error"
};

struct tui_ctl_shm {
	struct {
		int command;
		int value;
		int ret;
	} s2n;
	struct {
		int event_type;
		int value;
		unsigned int addr;
		unsigned int addr_h;
		int tp_info;
		int tp_info_h_addr;
		int status;
		int x;
		int y;
	} n2s;
};

struct tui_msg_node {
	int type;
	int val;
	void *data;
	struct list_head list;
};

typedef int (*tui_drv_init) (void *pdata, int secure);

struct tui_drv_node {
	tui_drv_init init_func;
	void *pdata;
	char name[TUI_DRV_NAME_MAX];
	int state;
	int priority;
	struct list_head list;
};



#ifdef CONFIG_TEE_TUI
extern int ts_tui_report_input(void *finger_data);
extern int tui_fp_notify(void);
int __init init_tui(struct device *dev);
void tui_exit(void);
int tui_send_event(int event);
int register_tui_driver(tui_drv_init fun, const char *name,
					void *pdata);
void unregister_tui_driver(const char *name);
/*
 * TUI has different state that can recieve given types of message,
 * there are 3 APIs to send message.
 * send_tui_msg_config:send message to TUI in config state only.
 */
int send_tui_msg_config(int type, int val, void *data);
void tui_poweroff_work_start(void);

void set_tui_attach_device(unsigned int id);
unsigned int tui_attach_device(void);
int load_ttf_file(unsigned int ttf_file_size);
void do_ns_tui_release(void);
#else
static inline int init_tui(struct device *dev)
{
	return 0;
}

static inline void tui_exit(void)
{
}

static inline int register_tui_driver(tui_drv_init fun,
		const char *name, void *pdata)
{
	return 0;
}

static inline void unregister_tui_driver(const char *name)
{
}

static inline int send_tui_msg_config(int type, int val, void *data)
{
	return 0;
}

static inline void set_tui_attach_device(unsigned int id)
{
}

static inline unsigned int tui_attach_device(void)
{
	return 0;
}

static inline int load_ttf_file(unsigned int ttf_file_size)
{
	return 0;
}

static inline void do_ns_tui_release(void)
{
}
#endif

#endif
