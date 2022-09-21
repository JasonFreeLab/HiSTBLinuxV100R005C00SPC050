/******************************************************************************
 *    Copyright (C) 2014 Hisilicon STB Development Dept
 *    All rights reserved.
 * ***
 *    Create by Czyong
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *   http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
******************************************************************************/

#ifndef COMPILEH
#define COMPILEH
#include <hi_type.h>

#define inline

typedef signed char                   int8;
typedef signed short                  int16;
typedef signed int                    int32;
typedef signed long long              int64;

typedef unsigned char                 uint8;
typedef unsigned short                uint16;
typedef unsigned int                  uint32;
typedef unsigned long long            uint64;

typedef unsigned char                 u_char;
typedef unsigned int                  u_int;
typedef unsigned short                u_short;
typedef unsigned long                 u_long;

typedef unsigned char                 u8;
typedef unsigned int                  u32;
typedef unsigned short                u16;
typedef unsigned long long            u64;

typedef uint32                        size_t;
//typedef uint32                        ssize_t;
typedef int32                         ptrdiff_t;
typedef int64                         quad_t;
typedef uint64                        u_quad_t;

typedef uint32                        uint32_t;
typedef uint64                        uint64_t;
typedef unsigned char                 uint8_t;
typedef unsigned short                uint16_t;

#define ARRAY_SIZE(x)  (sizeof(x) / sizeof(*(x)))

#define AROUND(size, align)     ((size + align - 1) & (~(align - 1)))

#define roundup(x, y)           ((((x) + ((y) - 1)) / (y)) * (y))

#define SWAP32(_x) ((uint32)(\
	((((uint32)(_x)) & 0x000000FF) << 24) | \
	((((uint32)(_x)) & 0x0000FF00) << 8)  | \
	((((uint32)(_x)) & 0xFF000000) >> 24) | \
	((((uint32)(_x)) & 0x00FF0000) >> 8)))

#define SWAP16(_x) ((uint16)(\
	((((uint16)(_x)) & 0xFF00) >> 8) | \
	((((uint16)(_x)) & 0x00FF) << 8)))

#define	SWAP64(x, sfx) \
	((((x) & 0xff00000000000000##sfx) >> 56) | \
	 (((x) & 0x00ff000000000000##sfx) >> 40) | \
	 (((x) & 0x0000ff0000000000##sfx) >> 24) | \
	 (((x) & 0x000000ff00000000##sfx) >>  8) | \
	 (((x) & 0x00000000ff000000##sfx) <<  8) | \
	 (((x) & 0x0000000000ff0000##sfx) << 24) | \
	 (((x) & 0x000000000000ff00##sfx) << 40) | \
	 (((x) & 0x00000000000000ff##sfx) << 56))
	 
#if	defined(__GNUC__)
# define uswap_64(x) _uswap_64(x, ull)
#else
# define uswap_64(x) _uswap_64(x, )
#endif

#ifndef	__LITTLE_ENDIAN
#define	__LITTLE_ENDIAN	1234
#endif

#ifndef	__LITTLE_ENDIAN_BITFIELD
#define	__LITTLE_ENDIAN_BITFIELD
#endif
#define	__BYTE_ORDER	__LITTLE_ENDIAN

#if	__BYTE_ORDER ==	__LITTLE_ENDIAN
# define cpu_to_le16(x)		(x)
# define cpu_to_le32(x)		(x)
# define cpu_to_le64(x)		(x)
# define le16_to_cpu(x)		(x)
# define le32_to_cpu(x)		(x)
# define le64_to_cpu(x)		(x)
# define cpu_to_be16(x)		SWAP16(x)
# define cpu_to_be32(x)		SWAP32(x)
# define cpu_to_be64(x)		SWAP64(x)
# define be16_to_cpu(x)		SWAP16(x)
# define be32_to_cpu(x)		SWAP32(x)
# define be64_to_cpu(x)		SWAP64(x)
#else
# define cpu_to_le16(x)		SWAP16(x)
# define cpu_to_le32(x)		SWAP32(x)
# define cpu_to_le64(x)		SWAP64(x)
# define le16_to_cpu(x)		SWAP16(x)
# define le32_to_cpu(x)		SWAP32(x)
# define le64_to_cpu(x)		SWAP64(x)
# define cpu_to_be16(x)		(x)
# define cpu_to_be32(x)		(x)
# define cpu_to_be64(x)		(x)
# define be16_to_cpu(x)		(x)
# define be32_to_cpu(x)		(x)
# define be64_to_cpu(x)		(x)
#endif

/*
 * The current upper bound for ARM L1 data cache line sizes	is 64 bytes.  We
 * use that	value for aligning DMA buffers unless the board	config has specified
 * an alternate	cache line size.
 */
#ifdef CONFIG_SYS_CACHELINE_SIZE
#define	ARCH_DMA_MINALIGN	CONFIG_SYS_CACHELINE_SIZE
#else
#define	ARCH_DMA_MINALIGN	64
#endif

#ifndef ALIGN
#define	ALIGN(x,a)		__ALIGN_MASK((x),(typeof(x))(a)-1)
#endif
#define	__ALIGN_MASK(x,mask)	(((x)+(mask))&~(mask))

#define	ALLOC_ALIGN_BUFFER(type, name, size, align)			\
	char __##name[AROUND(size * sizeof(type), align)	+ (align - 1)];	\
									\
	type *name = (type *) ALIGN((uint32)__##name, align)
#define	ALLOC_CACHE_ALIGN_BUFFER(type, name, size)			\
	ALLOC_ALIGN_BUFFER(type, name, size, ARCH_DMA_MINALIGN)

#ifndef CONFIG_NO_STRING
#  define _T(x)     x
#else
#  define _T(x)     0
#endif

#endif /* COMPILEH */
