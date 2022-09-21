/*****************************************************************************/
/**
* @file si_lib_malloc.c
*
* @brief Dynamic memory allocation from static memory pool
*
*****************************************************************************/

#ifndef __SI_LIB_MALLOC_API_H__
#define __SI_LIB_MALLOC_API_H__

/***** #include statements ***************************************************/

#include "si_datatypes.h"

/***** public functions ******************************************************/

void* SiiLibMallocCreate( uint_t size );
void SiiLibMallocDelete( void* p );
uint_t SiiLibMallocBytesAllocatedGet( void );
void SiiLibMallocLock( void );
void SiiLibMallocDeleteAll( void );

#endif /* __SI_LIB_MALLOC_API_H__ */

/***** end of file ***********************************************************/
