/** _____ _____ _____     _____              _           _   _____  ______   ____  _____        _    __   _____  ____
 * /  ___|_   _/  __ \   |_   _|            | |         | | /  ___|/  __  \ |  __||_   _|\ \   / /  /  \ |  __ ||  __|
 * \ `--.  | | | /  \/_____| |_ __ _   _ ___| |_ ___  __| | \ `--. | /  \ | | |_    | |   | |  | | / /\ \| |__||| |_
 *  `--. \ | | | |  |______| | '__| | | / __| __/ _ \/ _` |  `--. \| |  | | |  _|   | |   \ \ ^/ / | -- ||    _||  _|
 * /\__/ /_| |_| \__/\     | | |  | |_| \__ \ ||  __/ (_| | /\__/ /| \__/ | | |     | |    |    |  | || || |\ \ | |__
 * \____/ \___/ \____/     \_/_|   \__,_|___/\__\___|\__,_| \____/  \____/  |_|     \_/    \_/\_/  |_||_||_| \ \|____|
 *
 *-----------------------------------------------------------------------------
 *   © Copyright 2016 Secure-IC S.A.S.
 *   This file is part of SIC-Trusted IP cores family from Secure-IC S.A.S.
 *   This file relies on Secure-IC S.A.S. patent portfolio.
 *   This file cannot be used nor duplicated without prior approval from Secure-IC S.A.S.
 *----------------------------------------------------------------------------
 * File:        rsa_public.h
 * Description: Header file for RSA public operations
 * Version :    1.0
 *-----------------------------------------------------------------------------
*/
#ifndef __RSA_PUBLIC_H
#define __RSA_PUBLIC_H




/** RSA Encryption Primitive
 * Compute m^e mod n
 * \param n
 * \param m
 * \param e
 * \param size_n_in_words
 * \param c
 * \return status
 */
int rsa_enc_prim(   const unsigned int * const n,
                    const unsigned int * const m,
                    unsigned int size_n_in_words,
                    const unsigned int * const e,
                    unsigned int size_e_in_words,
                    unsigned int * const c);



/** RSA Verification Primitive
 * Compute s^e mod n
 * \param n
 * \param s
 * \param e
 * \param size_n_in_words
 * \param m
 * \return status
 */
int rsa_ver_prim(   const unsigned int * const n,
                    const unsigned int * const s,
                    unsigned int size_n_in_words,
                    const unsigned int * const e,
                    unsigned int size_e_in_words,
                    unsigned int * const m);


int get_hardware_version(unsigned int * r);


#endif /* __RSA_PUBLIC_H */
