/******************************************************************************
 *  Copyright (C) 2015 Hisilicon Technologies CO.,LTD.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Create By Cai Zhiyong 2015.6.25
 *
******************************************************************************/

#ifndef HISILICON_CPUTABLE_H
#define HISILICON_CPUTABLE_H

#define _HI3716MV410                (0x0137160410LL)
#define _HI3716MV420                (0x0037160410LL)
#define _HI3716MV410N               (0x0137160460LL)
#define _HI3716MV420N               (0x0037160460LL)
#define _HI3716MV410_MASK           (0xFFFFFFFFFFLL)

#define _HI3798MV100                (0x0137980100ULL)
#define _HI3796MV100                (0x0037980100ULL)
#define _HI3798MV100_MASK           (0xF1FFFFFF0FULL)

#define _HI3798CV200                (0x0037980200ULL)
#define _HI3798CV200_MASK           (0xFFFFFFFFFFULL)

#define _HI3798MV200                (0x0037986200ULL)
#define _HI3798MV300                (0x0037980210ULL)
#define _HI3798MV200_MASK           (0xFFFFFFFFFFULL)

#define _HI3798MV310                (0x0037980300ULL)
#define _HI3798MV300_H              (0x0137980300ULL)
#define _HI3798MV310_MASK           (0xFFFFFFFFFFULL)

#define _HI3796MV200_21X21          (0x0037960200ULL)
#define _HI3796MV200_15X15          (0x0137960200ULL)
#define _HI3716MV450                (0x1037960200ULL)
#define _HI3796MV200_MASK           (0xFFFFFFFFFFULL)

u64 get_chipid(u64 mask);

const char *get_cpuname(void);

extern u64 cpu_chipid;

#endif /* HISILICON_CPUTABLE_H*/
