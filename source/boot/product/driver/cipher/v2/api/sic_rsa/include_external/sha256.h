/** _____ _____ _____     _____              _           _   ___________   _____
 * /  ___|_   _/  __ \   |_   _|            | |         | | |_   _| ___ \ /  __ \
 * \ `--.  | | | /  \/_____| |_ __ _   _ ___| |_ ___  __| |   | | | |_/ / | /  \/ ___  _ __ ___
 *  `--. \ | | | |  |______| | '__| | | / __| __/ _ \/ _` |   | | |  __/  | |    / _ \| '__/ _ \
 * /\__/ /_| |_| \__/\     | | |  | |_| \__ \ ||  __/ (_| |  _| |_| |     | \__/\ (_) | | |  __/
 * \____/ \___/ \____/     \_/_|   \__,_|___/\__\___|\__,_|  \___/\_|      \____/\___/|_|  \___|
 *
 *-----------------------------------------------------------------------------
 *   © Copyright 2016 Secure-IC S.A.S.
 *   This file is part of SIC-Trusted IP cores family from Secure-IC S.A.S.
 *   This file relies on Secure-IC S.A.S. patent portfolio.
 *   This file cannot be used nor duplicated without prior approval from Secure-IC S.A.S.
 *----------------------------------------------------------------------------
 * Module:      SHA256
 * File:        SHA256.h
 * Author:      MM
 * Description: PRNG interface of Secure-IC (functions called from the ECC software stack)
 * Version :    1.0
 *-----------------------------------------------------------------------------
*/

#ifndef SHA256_H_
#define SHA256_H_

/*************************** HEADER FILES ***************************/
#include <stddef.h>

/****************************** MACROS ******************************/
#define SHA256_BLOCK_SIZE 32            // SHA256 outputs a 32 byte digest

/**************************** DATA TYPES ****************************/
typedef unsigned char BYTE;             // 8-bit byte
typedef unsigned int  WORD;             // 32-bit word, change to "long" for 16-bit machines

typedef struct {
	BYTE data[64];
	WORD datalen;
	unsigned long long bitlen;
	WORD state[8];
} SHA256_CTX;


/*********************** FUNCTION DECLARATIONS **********************/
void sha256_init(SHA256_CTX *ctx);
void sha256_update(SHA256_CTX *ctx, const BYTE data[], size_t len);
void sha256_final(SHA256_CTX *ctx, BYTE hash[]);

#endif /* SHA256_H_ */
