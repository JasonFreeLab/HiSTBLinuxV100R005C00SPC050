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
 * Module:      prng wrapper
 * File:        prng.h
 * Author:      CM
 * Description: PRNG interface of Secure-IC (functions called from the ECC software stack)
 * Version :    1.2
 *-----------------------------------------------------------------------------
*/
#ifndef __PRNG_H
#define __PRNG_H


/**
	Initialize the PRNG
	* \return 0 on sucess, nonzero otherwise
*/
int prng_init(void);

/**
	Get random bytes from the PRNG. Puts len random bytes into buff
	* \param buff the buffer to put the random bytes
	* \param len the number of random bytes to get
	* \return 0 on sucess, nonzero otherwise
 */
int prng_get_random_bytes(unsigned char * buff, unsigned int len);


#endif /* __PRNG_H */

