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
 * Module:      ecc and ecdsa
 * File:        code_error.h
 * Author:      CM
 * Description: code error constants
 * Version :    1.6
 *-----------------------------------------------------------------------------
*/
#ifndef __CODE_ERROR_H
#define __CODE_ERROR_H

// ECC error codes
#define ECC_SUCCESS                    0
#define ECC_NOT_READY                  -16001
#define ECC_ERR_UNDEFINED              -16002
#define ECC_ERR_INFINITY               -16003
#define ECC_ERR_NOT_CONSISTENT         -16004
#define ECC_ERR_FALSE_POINT            -16005
#define ECC_ERR_PRNG                   -16006
// #define ECC_ERR_TIMEOUT             -16007
#define ECC_ERR_INVALID_INPUTS         -16008

// ECDSA error codes
#define ECDSA_SUCCESS                  0
#define ECDSA_ERR_UNDEFINED            -16011
#define ECDSA_ERR_PRNG                 -16012
#define ECDSA_ERR_INVALID_INPUTS       -16013
#define ECDSA_ERR_R_OR_S_IS_ZERO       -16014

#define RSA_SUCCESS                    0
#define RSA_ERR_UNDEFINED              1
#define RSA_ERR_INVALID_INPUTS         2
#define RSA_ERR_FAULT_DETECTED         3
#define RSA_ERR_PRNG                   4
#define RSA_ERR_HASH                   5


#endif /* __CODE_ERROR_H */
