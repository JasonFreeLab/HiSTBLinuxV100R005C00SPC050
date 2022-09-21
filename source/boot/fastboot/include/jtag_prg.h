
#ifndef _JTAG_PRG_
#define _JTAG_PRG_

unsigned int jtag_get_cmd_id(void);
int jtag_clear_cmd_set_flag(void);
int jtag_check_cmd_set_flag(void);
int jtag_set_cmd_result(unsigned int res);
int jtag_set_cmd_done_flag(void);
void jtag_puts(const char *s);
void jtag_pr_tool(char *p);
void jtag_reset_send_buffer(void);
int is_jtag_mode(void);
void jtag_dump_buffer(void *buf, int len);
int jtag_init(void);
#endif /* _JTAG_PRG_ */
