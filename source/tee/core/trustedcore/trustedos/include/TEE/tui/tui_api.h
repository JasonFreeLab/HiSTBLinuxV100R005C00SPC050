#ifndef __TUI_API_H
#define __TUI_API_H

#include "tee_internal_api.h"
#include "ta_framework.h"
#define TEE_TUI_AGENT_ID	0x54554944	//TUI D

extern  notify_data_entry *notify_data_entry_tp;
#define TICK_CURSOR_FIQ_NUMBLER       93

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
	TUI_POLL_HANDLE_TUI, /* for tui to handle event */
	TUI_POLL_NAVI_H_TO_S,	/* or navigator hide and show */
	TUI_POLL_NAVI_S_TO_H,
	TUI_POLL_SHS_0_TO_1,  /* for single hand mode switch */
	TUI_POLL_SHS_0_TO_2,
	TUI_POLL_SHS_1_TO_0,
	TUI_POLL_SHS_2_TO_0,
	TUI_POLL_ROTATION_0,/* for retation switch */
	TUI_POLL_ROTATION_90, /* for retation switch */
	TUI_POLL_ROTATION_180,
	TUI_POLL_ROTATION_270,
	TUI_POLL_KEYBOARDTYPE_0,
	TUI_POLL_KEYBOARDTYPE_3,
	TUI_POLL_SEMITRANS,
	TUI_POLL_CURSOR,
	TUI_POLL_GETFP,
	TUI_POLL_MAX
};

/* event type for gui system */
#define TUI_EVENT_TP            0xf001
#define TUI_EVENT_TERMINATE     0xf002
#define TUI_EVENT_RESUME        0xf003
#define TUI_EVENT_HANDLE        0xf004
#define TUI_EVENT_TICK          0xf005
#define TUI_EVENT_DELAYED_WORK  0xf006
#define TUI_EVENT_NAVI_H_TO_S     0xf007
#define TUI_EVENT_NAVI_S_TO_H     0xf008
#define TUI_EVENT_SHS_0_TO_1     0xf009
#define TUI_EVENT_SHS_0_TO_2     0xf00a
#define TUI_EVENT_SHS_1_TO_0     0xf00b
#define TUI_EVENT_SHS_2_TO_0     0xf00c
#define TUI_EVENT_ROTATION_0   0xf00d
#define TUI_EVENT_ROTATION_90   0xf00e
#define TUI_EVENT_ROTATION_180   0xf00f
#define TUI_EVENT_ROTATION_270   0xf010
#define TUI_EVENT_KEYBOARDTYPE_0  0xf011
#define TUI_EVENT_KEYBOARDTYPE_3  0xf012
#define TUI_EVENT_CURSOR 0xf013
#define TUI_EVENT_GETFP 0xf014

#define TUI_INIT_STATUS_NAVI     0xe001

typedef enum {
	TEE_TUI_NAVI_S = 0xA001,
	TEE_TUI_NAVI_H,
	TEE_TUI_SHS_0,  /* normal screen */
	TEE_TUI_SHS_1,  /* single finger screen ->left   */
	TEE_TUI_SHS_2,  /* single finger screen ->right */
	TEE_TUI_ROTATION_0,
	TEE_TUI_ROTATION_90,
	TEE_TUI_ROTATION_180,
	TEE_TUI_ROTATION_270,
	TEE_TUI_KEYBOARDTYPE_0,
	TEE_TUI_KEYBOARDTYPE_3,
	TEE_TUI_DPI_SMALL,
	TEE_TUI_DPI_MEDIUM,
	TEE_TUI_DPI_LARGE,
	TEE_TUI_MAX
} TEE_TUIKeyBoardType;

/* tp data struct */
struct ts_tui_finger {
	int status;
	int x;
	int y;
	int area;
	int pressure;
	int orientation;
	int major;
	int minor;
	int event;
	unsigned int cur_pid;
};

struct tui_rect {
	int	left;
	int	top;
	int	right;
	int	bottom;
	int	bpp;
};

struct tui_info {
	struct tui_rect disp_rect;
	int display_addr;
	unsigned int display_size;
	int width;
	int height;
};

struct tui_tp {
	int secure;
	int tp_info_addr;
	char *notify_addr;
	int type;
};

struct ttf_mem_u {
	unsigned int ttf_addr_h;
	unsigned int ttf_addr_l;
	unsigned int ttf_buff_virt;
	unsigned int ttf_buff_len;
	unsigned int ttf_file_size;
	unsigned int ttf_buff_conf_size;
};

#define TUI_FONT_FILE_SZ (4 * 1024 * 1024)	/*3081908*/
extern struct ttf_mem_u g_ttf_mem_u;
extern config_mem_to_secure(paddr_t addr, unsigned int size);

#define DOWN_VAL 22  //4M
#define UP_VAL       27  //64M
#define M_INDEX  20
#define M_VAL   (1024*1024)
#define COLOR_TYPE  4  //ARGB
#define BUFFER_NUM 2
#define REL_CB_REGISTER   0
#define REL_CB_UNREGISTER 1

uint32_t get_size(uint32_t num);
TEE_Result tui_init(int *x, int *y, int bpp, char **fb);
TEE_Result tui_release(void);
int poll_tui_event(int *event, int need_agent);
int tui_show(struct tui_info *info);
int tui_get_tpdata(struct ts_tui_finger *data);
TEE_Result do_tp_sync(void);

int init_ttf_mem(smc_cmd_t *cmd);
int register_ttf_mem(struct ttf_mem_u *ttf_info);
int unregister_ttf_mem(struct ttf_mem_u *ttf_mem_info);
unsigned char *get_ttf_buff_info(unsigned int *ttf_file_size);

#endif
