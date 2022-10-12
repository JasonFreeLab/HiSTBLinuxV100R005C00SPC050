#include <linux/types.h>
#include <linux/dma-contiguous.h>
#include <linux/dma-mapping.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/string.h>
#include <linux/slab.h>
#include "../ion_priv.h"

#define MMZ_SETUP_CMDLINE_LEN	256
#define NAME_LEN_MAX	64

struct cma_zone {
	struct device pdev;
	char name[NAME_LEN_MAX];
	u32 gfp;
	u32 phys_start;
	u32 nbytes;
	u32 alloc_type;
	u32 block_align;
};
extern struct cma_zone *hisi_get_cma_zone(const char *name);

#ifdef CONFIG_MMZ_PARAM
static char ion_default_cmd[MMZ_SETUP_CMDLINE_LEN] __initdata = CONFIG_MMZ_PARAM;
#else
static char ion_default_cmd[MMZ_SETUP_CMDLINE_LEN] __initdata = "ddr,0,0,160M";
#endif

#define cma_name_len		(10)
#define cma_heap_start		(2)
#define cma_heap_num		(6)
static int cma_heap_index  = cma_heap_start;
static char cma_name[cma_heap_num][cma_name_len];
static struct ion_platform_heap hi_ion_heaps[]  = {
	[0] = {
		.id	= ION_HEAP_TYPE_SYSTEM,
		.type   = ION_HEAP_TYPE_SYSTEM,
		.name   = "vmalloc",
	}, [1] = {
		.id	= ION_HEAP_TYPE_DMA,
		.type	= ION_HEAP_TYPE_DMA,
		.name	= "dma area",
	},
#ifdef CONFIG_TEE_DRIVER
	[cma_heap_start + cma_heap_num -2] = {
		.id	= ION_HEAP_ID_TEE_SEC_MEM, /* secure mem in TEE */
		.type	= ION_HEAP_TYPE_TEE_SEC_MEM,
		.name	= "SEC-MMZ",
	},
#endif
	[cma_heap_start + cma_heap_num - 1] = {
		.id	= ION_HEAP_ID_CMA,
		.type	= ION_HEAP_TYPE_DMA,
	}
};

static struct ion_platform_data hi_ion_pdata __initdata = {
	.nr = ARRAY_SIZE(hi_ion_heaps),
	.heaps = hi_ion_heaps,
};

static struct platform_device hi_ion_dev = {
	.name = "hisi-ion",/* same as ion driver's name */
	.id = 1,
	.dev = { .platform_data = &hi_ion_pdata},
};

static int ion_use_bootargs;
/* borrow from hisi mmz driver */
static int __init hisi_ion_parse_cmdline(char *s)
{
	char *line, *tmp;
	char tmpline[256];
	unsigned int heap_id = ION_HEAP_ID_MULTI_CMA;

	strncpy(tmpline, s, sizeof(tmpline));
	tmpline[sizeof(tmpline)-1] = '\0';
	tmp = tmpline;
	while ((line = strsep(&tmp, ":")) != NULL) {
		int i;
		char *argv[6], *name;
		struct ion_platform_heap *heap;

		if (cma_heap_index >= (cma_heap_start + cma_heap_num - 2)) {
			WARN_ON(1);
			break;
		}

		for (i = 0; (argv[i] = strsep(&line, ",")) != NULL;)
			if (++i == ARRAY_SIZE(argv))
				break;

		if (i == 4) {
			heap = &hi_ion_heaps[cma_heap_index];
			name = &cma_name[cma_heap_index - cma_heap_start][0];
			heap->name = strncpy(name, argv[0], cma_name_len);;
			heap->base = memparse(argv[2], NULL);
			heap->size = memparse(argv[3], NULL);
			heap->priv = hisi_get_cma_device(heap->name);
			heap->type = ION_HEAP_TYPE_DMA;
			if(cma_heap_start == cma_heap_index)
				heap->id = ION_HEAP_ID_CMA;
			else
				heap->id = heap_id ++;
			WARN_ON(heap->priv == NULL);

			cma_heap_index++;
		} else {
			pr_err("hisi ion parameter is not correct\n");
			continue;
		}

	}

	if (cma_heap_index != cma_heap_start)
		ion_use_bootargs = 1;

	return 0;
}
__setup("mmz=", hisi_ion_parse_cmdline);

struct ion_platform_heap *hisi_get_cma_heap(const char *name)
{
	int i = 0;
	struct cma_zone *cma_zone;

	if (!name)
		return NULL;

	for (i = 0; i < (cma_heap_start + cma_heap_num); i++) {
		if (!(hi_ion_heaps[i].name))
			continue;
		if (strcmp(hi_ion_heaps[i].name, name) == 0)
			break;
	}

	if (i == (cma_heap_start + cma_heap_num))
		return NULL;

	cma_zone = hisi_get_cma_zone(hi_ion_heaps[i].name);
	if (cma_zone)
		hi_ion_heaps[i].base = cma_zone->phys_start;

	return &hi_ion_heaps[i];
}
EXPORT_SYMBOL(hisi_get_cma_heap);

static void set_platform_device(void)
{
	int i = 0;

	for(; i< sizeof(hi_ion_heaps)/sizeof(hi_ion_heaps[0]); i++) {
		if (!(hi_ion_heaps[i].name))
			continue;
		if (!(hi_ion_heaps[i].priv)) {
			hi_ion_heaps[i].priv = &(hi_ion_dev.dev);
		}
	}
}

int hisi_register_ion_device(void)
{
	int ret;

	set_platform_device();
	if (!ion_use_bootargs)
		hisi_ion_parse_cmdline(ion_default_cmd);

	ret = platform_device_register(&hi_ion_dev);
	WARN_ON(ret);

	return ret;
}
