
#include "vfmw_linux_kernel_osal.h"

#define VFMW_MAX_PROC_NAME_SIZE 16

#define PROC_PRINT(arg...) seq_printf(arg)

typedef SINT32 (*vfmw_proc_read_fn)(struct seq_file *, VOID *);
typedef SINT32 (*vfmw_proc_write_fn)(struct file *file, const char __user *buf, size_t count, loff_t *ppos);

typedef struct
{
    HI_CHAR proc_name[VFMW_MAX_PROC_NAME_SIZE];

    vfmw_proc_read_fn  read;
    vfmw_proc_write_fn write;
} vfmw_proc_func;


SINT32 vfmw_proc_create(HI_CHAR *proc_name, vfmw_proc_read_fn read, vfmw_proc_write_fn write);
VOID   vfmw_proc_destroy(HI_CHAR *proc_name);
SINT32 vfmw_proc_init(VOID);
VOID   vfmw_proc_exit(VOID);
SINT32 string_to_value(char *str, UINT32 *data);
