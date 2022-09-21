/**
 * \file ecdsa.h
 *
 * \brief Elliptic curve DSA
 *
 *  Copyright (C) 2006-2013, Brainspark B.V.
 *
 *  This file is part of PolarSSL (http://www.polarssl.org)
 *  Lead Maintainer: Paul Bakker <polarssl_maintainer at polarssl.org>
 *
 *  All rights reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#ifndef RM_SM2_H
#define RM_SM2_H

#include "ecp.h"

int ecdsa_self_test( int verbose );

int sm2_sign( mbedtls_mpi *r, mbedtls_mpi *s, mbedtls_mpi *d, /*Private Key*/
              unsigned char *buf, size_t blen,
              int (*f_rng)(void *, unsigned char *, size_t), void *p_rng ) ;

int sm2_verify(  unsigned char *buf, size_t blen,  mbedtls_ecp_point *Q, /*Public key*/
                 mbedtls_mpi *r,  mbedtls_mpi *s) ;

int sm2_encrypt( mbedtls_ecp_point *Z,  mbedtls_ecp_point *Q/*Public key*/, mbedtls_ecp_point *R,
                 int (*f_rng)(void *, unsigned char *, size_t), void *p_rng );

int sm2_decrypt( mbedtls_ecp_point *Z,  mbedtls_mpi *d/*Private key*/,  mbedtls_ecp_point *R);


#ifdef __cplusplus
}
#endif

#endif
