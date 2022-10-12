#ifndef HIMCI_VERSION_H
#define HIMCI_VERSION_H

#include <linux/uts.h>
#include <linux/utsname.h>
#include <generated/utsrelease.h>
#include <linux/version.h>

#ifdef CONFIG_ARCH_HI3798MV2X       
#  define HIMCI_VERSION        "V2.0"
#else
#if defined(CONFIG_ARCH_HI3796MV2X) || defined(CONFIG_ARCH_HI3798MV310)
#  define HIMCI_VERSION        "V3.0"
#else
#  define HIMCI_VERSION        "V1.0"
#endif
#endif

#define HIMCI_BUILD_DATA       "20170401" 
#define HIMCI_VERSION_STRING   HIMCI_VERSION"_"UTS_RELEASE"_"HIMCI_BUILD_DATA 

#endif
