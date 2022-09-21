/** _____ _____ _____     _____              _           _   ___________   _____
 * /  ___|_   _/  __ \   |_   _|            | |         | | |_   _| ___ \ /  __ \
 * \ `--.  | | | /  \/_____| |_ __ _   _ ___| |_ ___  __| |   | | | |_/ / | /  \/ ___  _ __ ___
 *  `--. \ | | | |  |______| | '__| | | / __| __/ _ \/ _` |   | | |  __/  | |    / _ \| '__/ _ \
 * /\__/ /_| |_| \__/\     | | |  | |_| \__ \ ||  __/ (_| |  _| |_| |     | \__/\ (_) | | |  __/
 * \____/ \___/ \____/     \_/_|   \__,_|___/\__\___|\__,_|  \___/\_|      \____/\___/|_|  \___|
 *
 *-------------------------------------------------------------------------------------------------
 *  © Copyright 2016 Secure-IC S.A.S.
 *  This file is part of SIC-Trusted IP cores family from Secure-IC S.A.S.
 *  This file relies on Secure-IC S.A.S. patent portfolio.
 *  This file cannot be used nor duplicated without prior approval from Secure-IC S.A.S.
 *-----------------------------------------------------------------------------------------------
 * File:        copro.h
 * Description: Copro base address for SIC-Trusted HW accelerator.
 * Version :    1.00
 *-----------------------------------------------------------------------------------------------
 */
#ifndef __COPRO
#define __COPRO

// This function MUST return the ACPU coprocessor base address
unsigned int get_copro_base_address( void );

#endif
