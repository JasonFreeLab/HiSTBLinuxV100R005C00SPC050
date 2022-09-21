/*
 * Copyright (c) 2017, Hisilicon Limited
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __HI_TEE_TA_AL_H
#define __HI_TEE_TA_AL_H

#include <tee_internal_api.h>
#include <tee_log.h>
#include <libhwsecurec/securec.h>
#include <tee_external_api.h>
#include <tee_ext_api.h>
#include <boot.h>
#include <tee_symbol.h>
#include <tee_ta_load.h>

#define ta_printf std_printf_func

/**
 * __tee_hisilicon_ioctl() - hisilicon system call intferace
 *
 * @param module	The module defined in hi_tee_module_id.h
 * @param cmd		The command that system call do
 * @param args		The arguments of command
 * @param size		The size of arguments
 *
 * @return 0		success
 * @return other value	fail
 */
extern int __tee_hisilicon_ioctl(const unsigned int module,
	const unsigned int cmd, void *args, const size_t size);

#endif /* __HI_TEE_TA_AL_H */
