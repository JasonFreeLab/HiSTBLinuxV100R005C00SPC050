
#include <linux/types.h>
#include <asm/errno.h>
#include <exports.h>
#include <linux/string.h>
#include <image.h>
#include <asm/io.h>
#include <atf.h>


file_info_t files[FIP_MAX_FILES];
unsigned file_info_count = 0;
uuid_t uuid_null = {0};
uuid_t uuid_bl33 = UUID_NON_TRUSTED_FIRMWARE_BL33;
uuid_t uuid_bl32 = UUID_SECURE_PAYLOAD_BL32;
uuid_t uuid_bl31 = UUID_EL3_RUNTIME_FIRMWARE_BL31;

/*
 * TODO: Add ability to specify and flag different file types.
 * Add flags to the toc_entry?
 * const char* format_type_str[] = { "RAW", "ELF", "PIC" };
 */

/* The images used depends on the platform. */
static entry_lookup_list_t toc_entry_lookup_list[] = {
	{ "Trusted Boot Firmware BL2", UUID_TRUSTED_BOOT_FIRMWARE_BL2,
	  "bl2", NULL, FLAG_FILENAME },
	{ "SCP Firmware BL3-0", UUID_SCP_FIRMWARE_BL30,
	  "bl30", NULL, FLAG_FILENAME},
	{ "EL3 Runtime Firmware BL3-1", UUID_EL3_RUNTIME_FIRMWARE_BL31,
	  "bl31", NULL, FLAG_FILENAME},
	{ "Secure Payload BL3-2 (Trusted OS)", UUID_SECURE_PAYLOAD_BL32,
	  "bl32", NULL, FLAG_FILENAME},
	{ "Non-Trusted Firmware BL3-3", UUID_NON_TRUSTED_FIRMWARE_BL33,
	  "bl33", NULL, FLAG_FILENAME},
	{ NULL, {0}, 0 }
};

extern int fdt_check_header(const void *fdt);
extern int do_load_secure_os(ulong addr, ulong org_offset, ulong img_dst, int run, uint32_t *rtos_load_addr);
/* Return 0 for equal uuids */
static inline int compare_uuids(const uuid_t *uuid1, const uuid_t *uuid2)
{
	return memcmp(uuid1, uuid2, sizeof(uuid_t));
}


static inline void copy_uuid(uuid_t *to_uuid, const uuid_t *from_uuid)
{
	memcpy(to_uuid, from_uuid, sizeof(uuid_t));
}

static entry_lookup_list_t *get_entry_lookup_from_uuid(const uuid_t *uuid)
{
	unsigned int lookup_index = 0;

	while (toc_entry_lookup_list[lookup_index].command_line_name != NULL) {
		if (compare_uuids(&toc_entry_lookup_list[lookup_index].name_uuid,
		    uuid) == 0) {
			return &toc_entry_lookup_list[lookup_index];
		}
		lookup_index++;
	}
	return NULL;
}

#if 0
static file_info_t *find_file_info_from_uuid(const uuid_t *uuid)
{
	int index;

	for (index = 0; index < file_info_count; index++) {
		if (compare_uuids(&files[index].name_uuid, uuid) == 0) {
			return &files[index];
		}
	}
	return NULL;
}
#endif

static void dump_toc(void)
{
	unsigned int index = 0;
	unsigned int image_offset;
	unsigned int image_size = 0;

	image_offset = sizeof(fip_toc_header_t) +
		(sizeof(fip_toc_entry_t) * (file_info_count + 1));

	printf("Firmware Image Package ToC:\n");
	printf("---------------------------\n");
	for (index = 0; index < file_info_count; index++) {
		if (files[index].entry) {
			printf("- %s: ", files[index].entry->name);
		} else {
			printf("- Unknown entry: ");
		}
		image_size = files[index].size;

		printf("offset=0x%X, size=0x%X\n", image_offset, image_size);
		image_offset += image_size;

		if (files[index].filename) {
			printf("  file: '%s'\n", files[index].filename);
		}
	}
	printf("---------------------------\n");
}

/* Read and load existing package into memory. */
static int parse_fip(char *fip_buffer)
{
	fip_toc_header_t *toc_header;
	fip_toc_entry_t *toc_entry;
	int found_last_toc_entry = 0;
	file_info_t *file_info_entry;
	int ret = -1;

	if (fip_buffer == NULL) {
		printf("ERROR: Invalid fip buffer addr.\n");
		ret = -EINVAL;
		goto parse_fip_error;
	}

	/* Set the ToC Header at the base of the buffer */
	toc_header = (fip_toc_header_t *)fip_buffer;
	/* The first toc entry should be just after the ToC header */
	toc_entry = (fip_toc_entry_t *)(toc_header + 1);

	/* While the ToC entry is contained into the buffer */
	int cnt = 0;
	while (cnt < FIP_MAX_FILES) {
		/* Check if the ToC Entry is the last one */
		if (compare_uuids(&toc_entry->uuid, &uuid_null) == 0) {
			found_last_toc_entry = 1;
			ret = 0;
			break;
		}

		/* Add the entry into file_info */

		/* Get the new entry in the array and clear it */
		file_info_entry = &files[file_info_count++];
		memset(file_info_entry, 0, sizeof(file_info_t));

		/* Copy the info from the ToC entry */
		copy_uuid(&file_info_entry->name_uuid, &toc_entry->uuid);
		file_info_entry->image_buffer = fip_buffer +
		  toc_entry->offset_address;
		file_info_entry->size = toc_entry->size;

		/* Check if there is a corresponding entry in lookup table */
		file_info_entry->entry =
		  get_entry_lookup_from_uuid(&toc_entry->uuid);

		/* Go to the next ToC entry */
		toc_entry++;
		cnt++;
	}

	if (!found_last_toc_entry) {
		printf("ERROR: Given FIP does not have an end ToC entry.\n");
		ret = -EINVAL;
		goto parse_fip_error;
	}

 parse_fip_error:
	return ret;
}

int is_fip(char *buf)
{
	fip_toc_header_t *header = (fip_toc_header_t *)buf;

	if (NULL == buf) {
		printf("Invalid fip buffer address\n");
		return 0;
	}

	if ((header->name == TOC_HEADER_NAME) && (header->serial_number != 0)) {
		return 1;
	} else {
		return 0;
	}
}
entry_point_info_t bl32_ep_info;
entry_point_info_t bl33_ep_info;
bl31_params_t bl31_params;

extern void setup_boot_atags(ulong rd_start, ulong rd_end);

int load_fip(char *buf)
{
	int ret = 0;
	unsigned int index = 0;
	entry_point_info_t *bl32_ep = &bl32_ep_info;
	entry_point_info_t *bl33_ep = &bl33_ep_info;
	bl31_params_t *bl31_p = &bl31_params;
	uint32_t bl31_pc = 0;
	unsigned int bl31_size = 0;
	char *bl31_img_buf = NULL;
	u32 val;

	memset(bl32_ep, 0, sizeof(entry_point_info_t));
	memset(bl33_ep, 0, sizeof(entry_point_info_t));
	memset(bl31_p, 0, sizeof(bl31_params_t));
	bl31_p->bl32_ep_info = (uint64_t)((uint32_t)bl32_ep);
	bl31_p->bl33_ep_info = (uint64_t)((uint32_t)bl33_ep);

	printf("Load fip from 0x%X ...\n", (uint32_t)buf);
	if (NULL == buf) {
		printf("Invalid fip buffer address\n");
		ret = -EINVAL;
		goto error;
	}
	ret = parse_fip(buf);
	if (ret)
		goto error;

	dump_toc();

	printf("Create Entry Point info ...\n");
	for (index = 0; index < file_info_count; index++) {
		if (!files[index].entry) {
			printf("- Invalid entry: ");
			continue;
		}

		if (compare_uuids(&files[index].name_uuid, &uuid_bl31) == 0) {
			printf("Get - %s \n", files[index].entry->name);
			bl31_pc = CONFIG_BL31_BASE;
			bl31_img_buf = files[index].image_buffer;
			bl31_size = files[index].size;
		}
#if 0 //def CONFIG_TEE_SUPPORT
		if (compare_uuids(&files[index].name_uuid, &uuid_bl32) == 0) {
			uint32_t rtos_addr;
			printf("Get - %s \n", files[index].entry->name);
			ret = do_load_secure_os((ulong)(files[index].image_buffer), 0, 0x7E700000, 0, &rtos_addr);
			if (ret)
				goto error;
			printf("rtos_addr = 0x%X\n", rtos_addr);
			bl32_ep->pc = (uint64_t)rtos_addr;
			SET_SECURITY_STATE(bl32_ep->h.attr,
					 SECURE);
			bl32_ep->spsr = 0;
		}
#endif
		if (compare_uuids(&files[index].name_uuid, &uuid_bl33) == 0) {
			printf("Get - %s \n", files[index].entry->name);
			image_header_t *hdr = (image_header_t *)(files[index].image_buffer);
			if (image_check_arch ((image_header_t *)(files[index].image_buffer), IH_ARCH_ARM64)) {
				char *fdt = (char *)image_get_image_end(hdr);
				ret = fdt_check_header(fdt);
				if (ret) {
					printf("Invalid FDT at 0x%p, hdr at 0x%p\n", fdt, hdr);
					goto error;
				}
				bl33_ep->pc = (uint64_t)image_get_data(hdr);
				bl33_ep->args.arg0 = (uint64_t)((uint32_t)fdt);
				bl33_ep->args.arg1 = (uint64_t)(image_get_ep(hdr));
				bl33_ep->args.arg2 = (uint64_t)(files[index].size - sizeof(image_header_t));
				bl33_ep->args.arg3 = CFG_BOOT_PARAMS;
				bl33_ep->args.arg4 = CFG_BOOT_PARAMS + CONFIG_BOOT_PARAMS_MAX_SIZE;
				bl33_ep->args.arg5 = (uint64_t)(CONFIG_DTB_MAX_SIZE);
				bl33_ep->spsr = SPSR_64(MODE_EL1,
				MODE_SP_ELX, DISABLE_ALL_EXCEPTIONS);
			} else {
				bl33_ep->pc = (uint64_t)image_get_data(files[index].image_buffer);
				bl33_ep->args.arg0 = 0; //no dtb
				bl33_ep->spsr = SPSR_MODE32(MODE32_svc, 0x0 , EP_EE_LITTLE, DISABLE_ALL_EXCEPTIONS);
			}
			printf("bl33_ep->spsr = 0x%X\n", bl33_ep->spsr);
		}
	}

	if (!bl33_ep->pc) {
		printf("Invalid fip image, no kernel found!\n");
		ret = -EINVAL;
		goto error;
	}

	if (!bl31_pc) {
		printf("No ATF found!\n");
		ret = -EINVAL;
		goto error;
	}

	setup_boot_atags(0, 0);

#ifdef CONFIG_TEE_SUPPORT
	extern u32 secure_entry_addr;
	extern u32 _text_end;
	if (secure_entry_addr) {
		unsigned int text_end = roundup(_text_end, 0x10); /* align for secure os clean boot */
		bl32_ep->pc = (uint64_t)secure_entry_addr;
		SET_SECURITY_STATE(bl32_ep->h.attr,
				 SECURE);
		bl32_ep->spsr = 0;
		bl32_ep->args.arg0 = TEXT_BASE;
		bl32_ep->args.arg1 = text_end;
	}
#endif

	printf("Move bl31 img from 0x%p to 0x%X, %d Bytes\n", bl31_img_buf, bl31_pc, bl31_size);
	memmove((void *)bl31_pc, bl31_img_buf, bl31_size);
	memset(bl31_img_buf, 0, bl31_size);
#if defined(CONFIG_HI3798MV2X_FPGA) || defined(CONFIG_HI3796MV2X_FPGA)
	writel(bl31_pc >> 2, REG_PERI_CPU_RVBARADDR);
#else
	writel(bl31_pc, REG_PERI_CPU_RVBARADDR);
#endif
	writel(readl(REG_PERI_CPU_AARCH_MODE) | 0xF,REG_PERI_CPU_AARCH_MODE);

	(*(volatile uint64_t *)0) = (uint64_t)((uint32_t)bl31_p);
	(*(volatile uint64_t *)8) = (uint64_t)((uint32_t)NULL);

	printf("Start Warm Reseting\n");

	cleanup_before_linux();

	/* warm reseting */
	__asm__ __volatile__("isb\n\r"
		"dsb\n\r"
		"mrc p15, 0, %0, c12, c0, 2\n\r"
		"orr %0, %0, #0x3\n\r"
		"mcr p15, 0, %0, c12, c0, 2\n\r"
		"isb\n\r"
		"wfi":"=r"(val)::"cc");
	printf("Fail to warm resetting...\n");
	hang();

error:
	return ret;
}
