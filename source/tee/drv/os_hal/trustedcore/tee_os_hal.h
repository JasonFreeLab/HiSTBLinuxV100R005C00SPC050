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
#ifndef __TEE_OS_HAL_H
#define __TEE_OS_HAL_H

#include <stdarg.h>
#include <boot.h>
#include <tee_internal_api.h>
#include <init_ext.h>
#include <tee_common.h>
#include <platform_chip.h>
#include <hi_tee_debug.h>

/* compiler __attribute__ macros for code easier to read */
#define __deprecated      __attribute__((deprecated))
#define __weak            __attribute__((weak))
#define __noreturn        __attribute__((noreturn))
#define __unused          __attribute__((unused))
#define __maybe_unused    __attribute__((unused))

/* The irq handler return value */
#define TEE_HAL_IRQ_HANDLED	1
#define TEE_HAL_IRQ_NONE	0

typedef unsigned(*tee_hal_timer_handler)(unsigned long);
typedef int(*drv_syscall_t) (const unsigned int, void *, const size_t);

struct mutex {
	void *rlock;
};

struct tee_hal_mutex {
	struct mutex mutex;
};

struct tee_hal_spinlock {
	unsigned spin_lock;
};

struct tee_hal_pm_ops {
    char *dev_name;
    int (*suspend)(void);
    int (*resume)(void);
};

/**
 * struct tee_hal_timer_t - describe a kernel space timer
 *
 * handler   The timer callback function handler
 * expires   The expire time of the timer, the resolution is micro seconds
 *           for example, the expires is set to 10, it means the timer will
 *           be called after 10us
 * data      The global timer data which will be pass to the timer callback
 *           handler, usually, it's set to the pointer to the timer itself
 * timer     The internal pointer which really implements the timer
 *
 */
typedef struct tee_hal_timer_t {
	tee_hal_timer_handler handler;
	unsigned long long expires;
	unsigned long data; /* Private data */
	/* internel data */
	void *timer;
} tee_hal_timer_t;

#define _panic0()   __panic((void *)0)
#define _panic1(s)  __panic(s)
#define _panic_fn(a, b, name, ...) name
#define panic(...) _panic_fn("", ##__VA_ARGS__, _panic1, _panic0)(__VA_ARGS__)
#if defined(CFG_HI_TEE_DEBUG_SUPPORT)
#define __panic(str)	__do_panic(__FILE__, __LINE__, __func__, str)
#else
#define __panic(str)	__do_panic((void *)0, 0, (void *)0, (void *)0)
#endif

/**
 * The active panic function for crital errors which can't be processed.
 * This function will verbose the callstack(depends on the specified CFG) and fall
 * into a dead loop.
 *
 */
#define tee_hal_panic panic

/**
 * Module init helper micros which is similar as Linux module_init
 * they are used to register module init entrypoint to the kernel.
 *
 * The calling sequence is as follow:
 * 1.	tee_hal_core_init
 * 2.	tee_hal_core_init_late
 * 3.	tee_hal_service_init
 * 4.	tee_hal_service_init_late
 * 5.	tee_hal_driver_init
 * 6.	tee_hal_driver_init_late
 *
 */
#define tee_hal_core_init(x) DECLARE_TC_DRV(x, 5, 0, 0, 0, (x), NULL)
#define tee_hal_core_init_late(x) DECLARE_TC_DRV(x, 4, 0, 0, 0, (x), NULL)
#define tee_hal_service_init(x) DECLARE_TC_DRV(x, 3, 0, 0, 0, (x), NULL)
#define tee_hal_service_init_late(x) DECLARE_TC_DRV(x, 2, 0, 0, 0, (x), NULL)
#define tee_hal_driver_init(x) DECLARE_TC_DRV(x, 1, 0, 0, 0, (x), NULL)
#define tee_hal_driver_init_late(x)  DECLARE_TC_DRV(x, 0, 0, 0, 0, (x), NULL)

extern int snprintf(char *str, int sz, const char *fmt, ...);
extern int vsprintf(char *buf, const char *fmt, va_list args);

/**
 *  tee_hal_printf - Standard printf functions in kernel
 *
 */
int tee_hal_printf(const char *fmt, ...);

/**
 * tee_hal_phys_to_virt() - convert physic address to virtual address
 * Often the module driver only has got the physic address, but can only
 * access the virt address.
 * phys_to_virt will convent the physic address to virtual address which
 * can be accessed by cpu, Note: this physic address will be mapped already.
 * In trustedcore, only support IO address.
 *
 * @param pa			The physic address which is to be converted.
 *
 * @return NULL			The physic to virt convert failed.
 * @return virtual address	The virtual address.
 */
void *tee_hal_phys_to_virt(unsigned long pa);

/**
 * tee_hal_virt_to_phys() - convert virtual address to physic address
 * The hardware can only accept physic address, but the software owns the virtual
 * address only.So virt to phys convert is needed.
 *
 * @param va			The virtual address which is to be converted.
 *
 * @return NULL			The virtual to physic convert failed.
 * @return physic address	The physic address.
 */
unsigned long tee_hal_virt_to_phys(void *va);

/*
 * These functions are all time relative functions
 *
 * 1. get_time_in_ms/us will return the system time in ms/us which is the
 * tee time and depends on the arm cp15 timer.
 *
 * 2. udelay/mdelay are used for short dead loop, and there two functions
 * also depends on the arm cp15 timer.
 *
 * 3. msleep is used for a relative long delay, and this function will release
 * the cpu and return back to the REE world, maybe is not so accurate which maybe
 * delayed by REE world but this function more effective.
 *
 */

/**
 * tee_hal_get_system_time_in_us() - get the system monotonic time.
 * this function is base on the system secure timer.
 *
 * @return the system monotonic time in us.
 *
 */
unsigned long long tee_hal_get_system_time_in_us(void);

/**
 * tee_hal_udelay() - delay helper function in resolution us.
 * this function is base on the system secure timer, used for short dead loop
 *
 * @param us		The time to delay.
 *
 */
void tee_hal_udelay(unsigned long us);

/**
 * tee_hal_mdelay() - delay helper function in resolution ms.
 * this function is base on the system secure timer, used for short dead loop
 *
 * @param ms		The time to delay.
 */
void tee_hal_mdelay(unsigned long msec);


/**
 * tee_hal_msleep() - sleep helper function in resolution ms.
 * this function is base on the system secure timer.
 * In trustedcore, actually it is a deap loop.
 * NOTE: the msec should be less than 1000.
 *
 * @param msec		The time to sleep.
 */
void tee_hal_msleep(unsigned long msec);

/**
 *  tee_hal_mutex_init() - The mutex initialize function
 *
 * @param name		The name of the mutex
 * @param mutex		The pointer of the mutex which is to be initialized
 *
 * @return 0		The mutex is initialized successfully.
 */
int tee_hal_mutex_init(const char *name, struct tee_hal_mutex *mutex);

/**
 * tee_hal_mutex_destroy() - The mutex destroy function
 * this function will only validate if the mutex is unlocked and no waiters, etc.
 *
 * @param mutex		The mutex which is to be destroyed
 */
void tee_hal_mutex_destroy(struct tee_hal_mutex *mutex);

/**
 * tee_hal_mutex_lock() - accuire the mutex lock
 *
 * @param mutex		The mutex to be accuired
 */
void tee_hal_mutex_lock(struct tee_hal_mutex *mutex);

/**
 * tee_hal_mutex_unlock() - release the mutex lock
 *
 * @param mutex		The mutex to be released
 */
void tee_hal_mutex_unlock(struct tee_hal_mutex *mutex);

/**
 * tee_hal_spin_lock_init() - spinlock init function
 *
 * @param lock		The lock to be initialized
 */
void tee_hal_spin_lock_init(struct tee_hal_spinlock *lock);

/**
 * tee_hal_spin_lock() - NOTE: Not support in trustedcore
 */
void tee_hal_spin_lock(struct tee_hal_spinlock *lock);

/**
 * tee_hal_spin_unlock() - NOTE: Not support in trustedcore
 */
void tee_hal_spin_unlock(struct tee_hal_spinlock *lock);

/**
 * tee_hal_spin_lock_irqsave() - disable the interrupts
 *
 * @param lock			Not used in trustedcore
 *
 * @return irq status	The irq status which will be used for irqrestore
 */
unsigned int tee_hal_spin_lock_irqsave(struct tee_hal_spinlock *lock);

/**
 * tee_hal_spin_lock_irqrestore() - restore the interrupts
 *
 * @param lock		Not used in trustedcore
 * @param status	The irq status to be restored
 */
void tee_hal_spin_unlock_irqrestore(struct tee_hal_spinlock *lock,
					unsigned int status);

/**
 * tee_hal_malloc() - malloc heap memory
 *
 * @param size		The size of the memory to be allocated
 *
 * @return memory pointer	The allocated memory pointer
 * @return NULL			The allocation failed
 */
void *tee_hal_malloc(size_t size);

/**
 * tee_hal_free() - free the heap memory
 *
 * @param ptr		The pointer of the memory which is be freed.
 */
void tee_hal_free(void *ptr);

/**
 * tee_hal_remap() - map the specified memory into tee kernel
 * this function can only be used to map non secure memory.
 *
 * @param pa		The physic address of the memory to be mapped
 * @param size		The size of the memory to be mapped
 * @param is_secure	The secure attribute of the mapping
 * @cached		The map cached attribute
 *
 * @return virtual address	The cpu virtual address of the map
 * @return NULL			The map failed for some reason
 */
void *tee_hal_remap(unsigned long pa, size_t size, bool is_secure, bool cached);

/**
 * tee_hal_unmap() - unmap the specified memory from tee kernel
 * this function can only be used to unmap non secure memory.
 *
 * @param va		The virtual address of the memory to be unmapped
 * @param size		The size of the memory to be unmapped
 */
void tee_hal_unmap(void *va, size_t size);

/**
 * tee_hal_user_remap() - map the specified  memory into ta space
 * this function can only be used to map non secure memory.
 *
 * @param pa		The physic address of the memory to be mapped
 * @param size		The size of the memory to be mapped
 * @param is_secure	The secure attribute of the mapping
 * @cached		The map cached attribute
 *
 * @return virtual address	The cpu virtual address of the map
 * @return NULL			The map failed for some reason
 */
void *tee_hal_user_remap(unsigned long pa, size_t size, bool is_secure, bool cached);

/**
 * tee_hal_ns_user_unmap() - unmap the specified memory from ta
 * this function can only be used to unmap non secure memory.
 *
 * @param va		The virtual address of the memory to be unmapped
 * @param size		The size of the memory to be unmapped
 */
void tee_hal_user_unmap(void *va, size_t size);

/**
 *  tee_hal_current_uuid() - get the current ta uuid
 *
 * @param uuid		The point which is used to return back the uuid
 *
 * @return TEE_SUCCESS	The function success
 * @return other value	The function failed
 */
int tee_hal_current_uuid(TEE_UUID *uuid);

/**
 * tee_hal_request_irq() - register irq handler
 *
 * @param irq		The irq number
 * @param handler	The irq callback handler
 * @param flag		The irq flag
 * @param dev		The param pass back to the handler
 *
 * @return TEE_SUCCESS	The irq is success registered
 * @return other value	The irq register failed for some reason
 */
int tee_hal_request_irq(unsigned int irq, void *handler,
			unsigned int flag, void *dev);

/**
 * tee_hal_delete_irq() - unregister irq
 *
 * @param irq		The irq to be unregistered
 */
void tee_hal_delete_irq(unsigned int irq);

/**
 * tee_hal_raise_pi() - raise a ipi interrupts
 *
 * @param irq		The ipi(irq) number to raise
 */
void tee_hal_raise_pi(unsigned int irq);

/**
 * tee_hal_backtraces() - print the current callstack
 * used for debug perpose
 *
 */
void tee_hal_backtraces(void);

/**
 * tee_hal_sys_reset() - reset the system
 * this function is used to harden the system, in some unexpected condition,
 * we need to reset the system to protect against attack
 *
 */
void tee_hal_sys_reset(void);

/**
 * tee_hal_get_rodata_pa_range() - get the kernel and rodata physic memory range
 * this is used by the tzasc driver, kernel and rodata can be protect by tzasc as
 * readonly for cpu, this is more secure then only readonly by mmu.
 * Note: the text and kernel text should be physic contigous.
 *
 * @param base		The pointer of val which holds the start physic address
 * @param size		The pointer of val which holds the size of the size
 */
void tee_hal_get_rodata_pa_range(unsigned long long *base, unsigned long long *size);

/**
 * tee_hal_rng_generate() - generate random number
 * This functions is atomic, can be called from any context, mainly used for harden system
 * against fault inject attack.
 *
 * @param buffer	The pointer of val which holds the random number
 * @param len		The length of random nunber in bytes
 */
int tee_hal_rng_generate(void *buffer, size_t len);

/**
 *  tee_hal_dcache_flush() - flush the dcache by va range
 *
 * @param va		The start va to be flushed
 * @param len		The length of the flush range
 */
void tee_hal_dcache_flush(void *va, size_t len);

/**
 * tee_hal_dcache_flush_all() - flush all the dcache
 * don't recommand use of the this function.
 */
void tee_hal_dcache_flush_all(void);

/**
 * tee_hal_dcache_invalidate() - NOTE: Not support in trustedcore
 */
void tee_hal_dcache_invalidate(void *va, size_t len);

/**
 * tee_hal_timer_init() - timer init function
 *
 * @param pstTevent	The timer to be initialized
 */
int tee_hal_timer_init(tee_hal_timer_t *pstTevent);

/**
 * tee_hal_timer_start() - timer start function
 * Note: timer currently is oneshot
 *
 * @param pstTevent	The timer to be started
 */
int tee_hal_timer_start(tee_hal_timer_t *pstTevent);

/**
 * tee_hal_timer_delete()- timer delete function
 *
 * @param pstTevent	The timer to be deleted
 */
int tee_hal_timer_delete(tee_hal_timer_t *pstTevent);

/**
 *  tee_hal_access_check() - check if the specified address range is valid
 *
 * @param addr		The start address to be checked
 * @param size		The size of the memory range to be checked
 */
bool tee_hal_access_check(void *addr, size_t size);

/**
 * tee_hal_read_right_check() - check if the specfied address range is readable
 *
 * @param addr		The start address to be checked
 * @param size		The size of the memory range to be checked
 */
bool tee_hal_read_right_check(void *addr, size_t size);

/**
 * tee_hal_write_right_check() - check if the specfied address range is writeable
 *
 * @param addr		The start address to be checked
 * @param size		The size of the memory range to be checked
 */
bool tee_hal_write_right_check(void *addr, size_t size);

/**
 * tee_hal_agentcall() - call a REE side registered agent
 *
 *
 * @param agent_id	The id of the called agent
 * @param buffer	The data buffer passed to the agent
 * @param len		The length of the buffer
 */
int tee_hal_agentcall(unsigned int agent_id, void *buffer, size_t len);

/**
 * tee_hal_map_sg() - map a sglist of physic memory into tee/ta
 * this interface is only for smmu driver
 *
 * @param pageinfoaddr		The physic address of the sglist structure
 * @param nblocks		The number of frags in the sglist
 * @param size			The memory size of the whole sglist
 * @param va			The return va of the function
 * @param is_secure		The secure attribute of the mapping
 * @param cached		The cached attribute of the mapping
 * @param user_map		The map is userspace mapping or not
 *
 * @return TEE_SUCESS		The function success
 * @return other value		The function failed for some reason
 */
int tee_hal_map_sg(unsigned long pageinfoaddr, unsigned int nblocks,
		size_t size, void *va, bool is_secure,
		bool cached, bool user_map);

/**
 * tee_hal_unmap_sg() - unmap a sglist of physic memory from tee/ta
 * this interface is only for smmu driver
 *
 * @param va			The return va of the function
 * @param size			The memory size of the whole sglist
 * @param is_secure		The secure attribute of the mapping
 * @param user_map		The map is userspace mapping or not
 *
 * @return TEE_SUCESS		The function success
 * @return other value		The function failed for some reason
 */
int tee_hal_unmap_sg(void *va, size_t size, bool is_secure,
		bool user_map);
void __do_panic(const char *file, const int line, const char *func,
		const char *msg);

/**
 * tee_hal_pm_register() - register suspend and resume function to PM
 *
 * @param pm_ops	The operations for power management
 *
 * @return 0			Register successfully
 * @return other value		Register failed
 */
int tee_hal_pm_register(struct tee_hal_pm_ops *pm_ops);

/**
 * tee_hal_module_register() - register a module function to handle system call
 *
 * @param module_id		The module id
 * @param drv_syscall_t		The system call handle function
 *
 * @return 0			Register successfully
 * @return other value		Register failed
 */
int tee_hal_module_register(const unsigned int module_id, drv_syscall_t fn);

extern int memset_s(void* dest, size_t destMax, int c, size_t count);
extern int memcpy_s(void* dest, size_t destMax, const void* src, size_t count);

#define OS_HAL_ERROR(fmt...)        HI_LOG_ERROR(fmt)
#endif
