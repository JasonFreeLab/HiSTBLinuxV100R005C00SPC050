/******************************************************************************
 Copyright (C), 2015-2025, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : Logger.h
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2015/7/14
Last Modified :
Description   : Logger module.
                CNcomment: Logger模块CNend
Function List :
History       :
******************************************************************************/
#ifndef DFX_LOGGER_H_
#define DFX_LOGGER_H_

#include <cutils/logd.h>

/*************************** Structure Definition ****************************/
/** \addtogroup      LOGGER */
/** @{ */  /** <!-- [LOGGER]*/

/*
 * Normally we strip HI_LOGV (VERBOSE messages) from release builds.
 * You can modify this (for example with "#define LOG_NDEBUG 0"
 * at the top of your source file) to change that behavior.
 */
#ifndef LOG_NDEBUG
#ifdef NDEBUG
#define LOG_NDEBUG 1
#else
#define LOG_NDEBUG 0
#endif
#endif

/*
 * This is the local tag used for the following simplified
 * logging macros.  You can change this preprocessor definition
 * before using the other macros to change the tag.
 */
#ifndef LOG_TAG
#define LOG_TAG NULL
#endif

/** Defines the type of log level *//** CNcomment:定义日志优先级 */
typedef enum hiLOGGERLEVEL_E {
    HI_LOGGER_UNKNOWN = 0,
    HI_LOGGER_DEFAULT,     /* only for SetMinPriority() */
    HI_LOGGER_VERBOSE,     /**<lowest priority *//**<CNcomment:最低优先级 */
    HI_LOGGER_DEBUG,       /**<debug priority *//**<CNcomment:打印debug信息 */
    HI_LOGGER_INFO,        /**<info priority *//**<CNcomment:打印info信息 */
    HI_LOGGER_WARN,        /**<warnning priority *//**<CNcomment:打印warnning信息 */
    HI_LOGGER_ERROR,       /**<error priority *//**<CNcomment:打印error信息 */
    HI_LOGGER_FATAL,       /**<fatal priority *//**<CNcomment:打印fatal信息 */
    HI_LOGGER_SILENT,      /* only for SetMinPriority(); must be last */
} HI_LOGGERLEVEL_E;

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      LOGGER */
/** @{ */  /** <!-- [LOGGER]*/

/*
 * Basic log message macro.
 *
 * Example:
 *  LOGGER(HI_LOG_WARN, NULL, "Failed with error %d", errno);
 *
 * The second argument may be NULL or "" to indicate the "global" tag.
 */
#ifndef LOGGER
#define LOGGER(priority, tag, file, line, ...) \
    LOG_PRIORITY(priority, tag, file, line, __VA_ARGS__)
#endif

#if 1
#define LOG_PRIORITY(prio, tag, file, line, fmt...) \
    __android_log_print_ex(prio, tag, file, line, fmt)
#else
#define LOG_PRIORITY(prio, tag, file, line, fmt...) \
     __android_log_print(prio, tag, fmt)
#endif

/*
 * Simplified macro to send a verbose log message using the current LOG_TAG.
 */
#ifndef HI_LOGV
#if LOG_NDEBUG
#define HI_LOGV(...) ((void)0)
#else
#define HI_LOGV(...) ((void)LOGGER(HI_LOGGER_VERBOSE, LOG_TAG, __FILE__, __LINE__, __VA_ARGS__))
#endif
#endif

/*
 * Simplified macro to send a debug log message using the current LOG_TAG.
 */
#ifndef HI_LOGD
#if LOG_NDEBUG
#define HI_LOGD(...) ((void)0)
#else
#define HI_LOGD(...) ((void)LOGGER(HI_LOGGER_DEBUG, LOG_TAG, __FILE__, __LINE__, __VA_ARGS__))
#endif
#endif

/*
 * Simplified macro to send an info log message using the current LOG_TAG.
 */
#ifndef HI_LOGI
#if LOG_NDEBUG
#define HI_LOGI(...) ((void)0)
#else
#define HI_LOGI(...) ((void)LOGGER(HI_LOGGER_INFO, LOG_TAG, __FILE__, __LINE__, __VA_ARGS__))
#endif
#endif

/*
 * Simplified macro to send a warning log message using the current LOG_TAG.
 */
#ifndef HI_LOGW
#if LOG_NDEBUG
#define HI_LOGW(...) ((void)0)
#else
#define HI_LOGW(...) ((void)LOGGER(HI_LOGGER_WARN, LOG_TAG, __FILE__, __LINE__, __VA_ARGS__))
#endif
#endif

/*
 * Simplified macro to send an error log message using the current LOG_TAG.
 */
#ifndef HI_LOGE
#if LOG_NDEBUG
#define HI_LOGE(...) ((void)0)
#else
#define HI_LOGE(...) ((void)LOGGER(HI_LOGGER_ERROR, LOG_TAG, __FILE__, __LINE__, __VA_ARGS__))
#endif
#endif

/** @} */  /** <!-- ==== API declaration end ==== */

#endif /* DFX_LOGGER_H_ */
