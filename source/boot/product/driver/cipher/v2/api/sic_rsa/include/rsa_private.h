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
 * File:        rsa_private.h
 * Description: Header file for RSA private operations
 * Version :    1.0
 *-----------------------------------------------------------------------------
*/
#ifndef __RSA_PRIVATE_H
#define __RSA_PRIVATE_H


/** RSA Decryption Primitive with CRT private key
 * Compute m = c^d mod n,
 * With n = p*q,
 * dP = d mod p,
 * dQ = d mod q,
 * qINV = q^(-1) mod p.
 * \param p
 * \param q
 * \param dP
 * \param dQ
 * \param qINV
 * \param c
 * \param size_p_in_words
 * \param m
 * \return status
 */
int rsa_crt_dec_prim(   const unsigned int * const p,
                        const unsigned int * const q,
                        const unsigned int * const dP,
                        const unsigned int * const dQ,
                        const unsigned int * const qINV,
                        const unsigned int * const c,
                        unsigned int size_p_in_words,
                        unsigned int * const m);


/** RSA Signature Primitive with CRT private key
 * Compute s = m^d mod n,
 * With n = p*q,
 * dP = d mod p,
 * dQ = d mod q,
 * qINV = q^(-1) mod p.
 * \param p
 * \param q
 * \param dP
 * \param dQ
 * \param qINV
 * \param m
 * \param size_p_in_words
 * \param s
 * \return status
 */
int rsa_crt_sig_prim(    const unsigned int * const p,
                        const unsigned int * const q,
                        const unsigned int * const dP,
                        const unsigned int * const dQ,
                        const unsigned int * const qINV,
                        const unsigned int * const m,
                        unsigned int size_p_in_words,
                        unsigned int * const s);



/** RSA Decryption Primitive
 * Compute c^d mod n
 * \param n
 * \param c
 * \param d
 * \param size_n_in_words
 * \param m
 * \return status
 */
int rsa_dec_prim(   const unsigned int * const n,
                    const unsigned int * const c,
                    const unsigned int * const d,
                    unsigned int size_n_in_words,
                    unsigned int * const m);

/** RSA Signature Primitive
 * Compute m^d mod n
 * \param n
 * \param m
 * \param d
 * \param size_n_in_words
 * \param s
 * \return status
 */
int rsa_sig_prim(   const unsigned int * const n,
                    const unsigned int * const m,
                    const unsigned int * const d,
                    unsigned int size_n_in_words,
                    unsigned int * const s);


int get_hardware_version(unsigned int * r);


#endif /* __RSA_PRIVATE_H */
