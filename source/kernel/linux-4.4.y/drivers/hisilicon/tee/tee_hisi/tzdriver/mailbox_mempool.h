#ifndef _MAILBOX_MEMPOOOL_H
#define _MAILBOX_MEMPOOOL_H

#include <linux/kernel.h>
#include "teek_ns_client.h"

#define MAILBOX_POOL_SIZE SZ_4M

/* alloc options */
#define MB_FLAG_ZERO 0x1 /* set 0 after alloc page */

struct mb_cmd_pack {
	unsigned char uuid[17];
	TC_NS_Operation operation;
#ifdef SECURITY_AUTH_ENHANCE
	unsigned char login_data[HASH_PLAINTEXT_ALIGNED_SIZE + IV_BYTESIZE];
	unsigned char token[TOKEN_BUFFER_LEN];
	unsigned char secure_params[ALIGN(sizeof(struct session_secure_params),
		CIPHER_BLOCK_BYTESIZE) + IV_BYTESIZE];
#else
	unsigned char login_data[MAX_SHA_256_SZ];
#endif
};

void *mailbox_alloc(size_t size, int flag);
void mailbox_free(void *ptr);
int mailbox_mempool_init(void);
void mailbox_mempool_destroy(void);
struct mb_cmd_pack *mailbox_alloc_cmd_pack(void);
void *mailbox_copy_alloc(void *src, size_t size);

#endif
