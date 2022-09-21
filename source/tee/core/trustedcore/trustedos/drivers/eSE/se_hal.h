#ifndef __SE_HAL_H
#define __SE_HAL_H

/* scard_support_mode return value defines */
/* TEE SE API direct call transmit syscall in that do a sync loop to send command and
 * receive response in it */
#define SCARD_MODE_SYNC 0
/* TEE SE API need call seperate syscalls(send, receive and get_status) to make a sync loop
 * to simulate the 'transmit' */
#define SCARD_MODE_SYNC2 1
/* TEE SE API direct transmit syscall in that do a async implemation, for further use */
#define SCARD_MODE_ASYNC 2

/* scard_get_status return value defines */
#define SCARD_STATUS_RECEIVE_NOT_READY 0 /* */
#define SCARD_STATUS_RECEIVE_READY 1 /* */

/*
 * return: SCARD_MODE_SYNC, SCARD_MODE_SYNC2, SCARD_MODE_ASYNC
 *         (see details at defines)
 */
int scard_support_mode(void);

/*
 * reader_id: SE read_id(no used now)
 * atr: SE's atr buffer
 * atr_len: atr buffer's len
 *
 * return: 0 - success
 *         <0 - fails
 */
int scard_connect(int reader_id, void *atr, unsigned int *atr_len);

/*
 * reader_id: SE read_id(no used now)
 *
 * return: 0 - success
 *         <0 - fails
 */
int scard_disconnect(int reader_id);

/*
 * reader_id: SE read_id(no used now)
 * cmd: transfered command to SE
 * cmd_len: command's len
 * rsp: response buffer of this command
 * rsp: response buffer's len
 *
 * return: 0 - success
 *         <0 - fails
 */
int scard_transmit(int reader_id, unsigned char *cmd, unsigned int cmd_len,
		   unsigned char *rsp, unsigned int *rsp_len);

/*
 * reader_id: SE read_id(no used now)
 * cmd: transfered command to SE
 * cmd_len: command's len
 *
 * return: 0 - success
 *         <0 - fails
 */
int scard_send(int reader_id, unsigned char *cmd, unsigned int cmd_len);

/*
 * rsp: response buffer of this command
 * rsp: response buffer's len
 *
 * return: 0 - success
 *         <0 - fails
 */
int scard_receive(unsigned char *rsp, unsigned int *rsp_len);

/*
 * return: SCARD_STATUS_NOT_READY - not ready to receive response
 *         SCARD_STATUS_READY - ready to receive response
 */
int scard_get_status(void);
#endif
