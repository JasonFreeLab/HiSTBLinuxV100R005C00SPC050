/*
 * SHA256 hash implementation and interface functions
 * Copyright (c) 2003-2006, Jouni Malinen <j@w1.fi>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Alternatively, this software may be distributed under the terms of BSD
 * license.
 *
 * See README and COPYING for more details.
 */

#ifndef SHA256_H
#define SHA256_H

#include <hi_type.h>

#define SHA256_MAC_LEN 32
#define INTERNAL_SHA256

/* Macros for handling unaligned memory accesses */

#define WPA_GET_BE16(a) ((unsigned short) (((a)[0] << 8) | (a)[1]))
#define WPA_PUT_BE16(a, val)                    \
        do {                                    \
                (a)[0] = ((unsigned short) (val)) >> 8;    \
                (a)[1] = ((unsigned short) (val)) & 0xff;  \
        } while (0)

#define WPA_GET_LE16(a) ((unsigned short) (((a)[1] << 8) | (a)[0]))
#define WPA_PUT_LE16(a, val)                    \
        do {                                    \
                (a)[1] = ((unsigned short) (val)) >> 8;    \
                (a)[0] = ((unsigned short) (val)) & 0xff;  \
        } while (0)

#define WPA_GET_BE24(a) ((((unsigned int) (a)[0]) << 16) | (((unsigned int) (a)[1]) << 8) | \
                         ((unsigned int) (a)[2]))
#define WPA_PUT_BE24(a, val)                                    \
        do {                                                    \
                (a)[0] = (unsigned char) ((((unsigned int) (val)) >> 16) & 0xff);   \
                (a)[1] = (unsigned char) ((((unsigned int) (val)) >> 8) & 0xff);    \
                (a)[2] = (unsigned char) (((unsigned int) (val)) & 0xff);           \
        } while (0)

#define WPA_GET_BE32(a) ((((unsigned int) (a)[0]) << 24) | (((unsigned int) (a)[1]) << 16) | \
                         (((unsigned int) (a)[2]) << 8) | ((unsigned int) (a)[3]))
#define WPA_PUT_BE32(a, val)                                    \
        do {                                                    \
                (a)[0] = (unsigned char) ((((unsigned int) (val)) >> 24) & 0xff);   \
                (a)[1] = (unsigned char) ((((unsigned int) (val)) >> 16) & 0xff);   \
                (a)[2] = (unsigned char) ((((unsigned int) (val)) >> 8) & 0xff);    \
                (a)[3] = (unsigned char) (((unsigned int) (val)) & 0xff);           \
        } while (0)

#define WPA_GET_LE32(a) ((((unsigned int) (a)[3]) << 24) | (((unsigned int) (a)[2]) << 16) | \
                         (((unsigned int) (a)[1]) << 8) | ((unsigned int) (a)[0]))
#define WPA_PUT_LE32(a, val)                                    \
        do {                                                    \
                (a)[3] = (unsigned char) ((((unsigned int) (val)) >> 24) & 0xff);   \
                (a)[2] = (unsigned char) ((((unsigned int) (val)) >> 16) & 0xff);   \
                (a)[1] = (unsigned char) ((((unsigned int) (val)) >> 8) & 0xff);    \
                (a)[0] = (unsigned char) (((unsigned int) (val)) & 0xff);           \
        } while (0)

#define WPA_GET_BE64(a) ((((unsigned long long) (a)[0]) << 56) | (((unsigned long long) (a)[1]) << 48) | \
                         (((unsigned long long) (a)[2]) << 40) | (((unsigned long long) (a)[3]) << 32) | \
                         (((unsigned long long) (a)[4]) << 24) | (((unsigned long long) (a)[5]) << 16) | \
                         (((unsigned long long) (a)[6]) << 8) | ((unsigned long long) (a)[7]))
#define WPA_PUT_BE64(a, val)                            \
        do {                                            \
                (a)[0] = (unsigned char) (((unsigned long long) (val)) >> 56);    \
                (a)[1] = (unsigned char) (((unsigned long long) (val)) >> 48);    \
                (a)[2] = (unsigned char) (((unsigned long long) (val)) >> 40);    \
                (a)[3] = (unsigned char) (((unsigned long long) (val)) >> 32);    \
                (a)[4] = (unsigned char) (((unsigned long long) (val)) >> 24);    \
                (a)[5] = (unsigned char) (((unsigned long long) (val)) >> 16);    \
                (a)[6] = (unsigned char) (((unsigned long long) (val)) >> 8);     \
                (a)[7] = (unsigned char) (((unsigned long long) (val)) & 0xff);   \
        } while (0)

#define WPA_GET_LE64(a) ((((unsigned long long) (a)[7]) << 56) | (((unsigned long long) (a)[6]) << 48) | \
                         (((unsigned long long) (a)[5]) << 40) | (((unsigned long long) (a)[4]) << 32) | \
                         (((unsigned long long) (a)[3]) << 24) | (((unsigned long long) (a)[2]) << 16) | \
                         (((unsigned long long) (a)[1]) << 8) | ((unsigned long long) (a)[0]))
                         
void hmac_sha256_vector(const unsigned char *key, unsigned int key_len, unsigned int num_elem,
                      const unsigned char *addr[], const unsigned int *len, unsigned char *mac);
void hmac_sha256(const unsigned char *key, unsigned int key_len, const unsigned char *data,
                 unsigned int data_len, unsigned char *mac);
void sha256_prf(const unsigned char *key, unsigned int key_len, const char *label,
              const unsigned char *data, unsigned int data_len, unsigned char *buf, unsigned int buf_len);

#endif /* SHA256_H */