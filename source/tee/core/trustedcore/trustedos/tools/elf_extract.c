#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if DEBUG == 0
#include <openssl/evp.h>
#endif

#define EI_NIDENT          16
#define SHN_UNDEF          0
#define STT_FUNC           2
#define SHT_SYMTAB         2
#define SHT_STRTAB         3
#define SHT_NOBITS         8
#if DEBUG == 0
#define FUNC_NAME_LEN      256
#define SUB_BYTE_LENGTH    8
#define SHA256_DIGEST_LENGTH 32
#endif

#define ELF32_ST_TYPE(val)		((val) & 0xf)
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned char u8;

typedef struct {
	u32	    sh_name;		/* Section name (string tbl index) */
	u32	    sh_type;		/* Section type */
	u32	    sh_flags;		/* Section flags */
	u32	    sh_addr;		/* Section virtual addr at execution */
	u32	    sh_offset;		/* Section file offset */
	u32    sh_size;        /* Section size in bytes */
	u32    sh_link;        /* Link to another section */
	u32    sh_info;        /* Additional section information */
	u32    sh_addralign;       /* Section alignment */
	u32    sh_entsize;     /* Entry size if section holds table */
} Elf32_Shdr;

typedef struct {
	u8	eh_ident[EI_NIDENT];	/* Magic number and other info */
	u16	eh_type;			/* Object file type */
	u16	eh_machine;		/* Architecture */
	u32	eh_version;		/* Object file version */
	u32	eh_entry;		/* Entry point virtual address */
	u32	eh_phoff;		/* Program header table file offset */
	u32	eh_shoff;		/* Section header table file offset */
	u32    eh_flags;        /* Processor-specific flags */
	u16    eh_ehsize;       /* ELF header size in bytes */
	u16    eh_phentsize;        /* Program header table entry size */
	u16    eh_phnum;        /* Program header table entry count */
	u16    eh_shentsize;        /* Section header table entry size */
	u16    eh_shnum;        /* Section header table entry count */
	u16    eh_shstrndx;     /* Section header string table index */
} Elf32_Ehdr;

typedef struct {
	u32 st_name;        /* Symbol name (string tbl index) */
	u32 st_value;       /* Symbol value */
	u32 st_size;        /* Symbol size */
	u8  st_info;        /* Symbol type and binding */
	u8  st_other;       /* Symbol visibility */
	u16 st_shndx;       /* Section index */
} elf32_sym;

void usage()
{
	printf("Usage: \"elf_extract type infile outfile\"!!!\n");
}

#if DEBUG == 0
static void byteToHex(char *buf, char data)
{
	const char str[] = "0123456789abcdef";
	u8 index = (u8)((data >> 4) & 0x0F);
	*buf++ = (str[index]) ;
	index = (u8)(data & 0x0F);
	*buf++ = str[data & 0x0F];
}

static void byteToString(char *str, u8 *data, int len)
{
	int i;
	char *pbuf = str;
	char *pdata = (char *)data;

	for (i = 0; i < len; i++) {
		byteToHex(pbuf, *pdata++);
		pbuf += 2;
	}
}

static char *revstr(char *str)
{
	char    *start = str;
	char    *end = str + strlen(str) - 1;
	char    ch;

	if (str != NULL) {
		while (start < end) {
			ch = *start;
			*start++ = *end;
			*end-- = ch;
		}
	}

	return str;
}

static void mix_func_name(char *func_name_mix, u32 mix_len, char *chip_choose, char *func_name)
{
	if (NULL == func_name_mix || NULL == func_name || 0 == mix_len)
		return;

	/* reverse the chip_choose string */
	char *mix_slat = revstr(chip_choose);
	char *pbuf = func_name_mix;
	char *in_buf = func_name;

	u32 i, j = 0, n = 0;
	u32 in_len = strlen(func_name);
	u32 salt_len = strlen(mix_slat);

	/* mix function name string */
	for (i = in_len; i != 0; i--) {
		if (j > (mix_len - 1)) break;

		pbuf[j] = (char)(in_buf[i - 1] + i);
		j++;

		if (n < salt_len) {
			if (j > (mix_len - 1)) break;
			pbuf[j] = mix_slat[n];
			n++;
			j++;
		}
	}
	revstr(chip_choose);
}

static int str_tab_out(char *sym_tab, u32 symtab_size, char *str_tab,
		       char *chip_choose,  FILE *tb_fp, FILE *out_fp)
{
	if (NULL == sym_tab || NULL == str_tab ||
	    NULL == tb_fp || NULL == out_fp || 0 == symtab_size) {
		printf("Error: str_tab_out input params invalid.\n");
		return -1;
	}

	/* initalize the variables */
	elf32_sym *symtab_addr = (elf32_sym *)sym_tab;
	u8 hash_l[SHA256_DIGEST_LENGTH] = {0};
	u8 hash_f[SHA256_DIGEST_LENGTH] = {0};
	char str_sub[SUB_BYTE_LENGTH * 2 + 1] = {0};

	u32 n = (symtab_size / (sizeof(elf32_sym))), i;
	u32 str_sub_len = SUB_BYTE_LENGTH * 2  + 1;

	char *str_tab_out = (char *)malloc(n * str_sub_len);
	if (NULL == str_tab_out) {
		printf("Error: str_tab_out malloc failed.\n");
		return -2;
	}
	memset(str_tab_out, 0, n * str_sub_len);
	char *pStr = str_tab_out;
	/* traverse all function name string in strtab, mix them up */
	for (i = 1; i < n ; i++) {
		u32 index = symtab_addr[i].st_name;
		if (SHN_UNDEF != symtab_addr[i].st_shndx &&
		    STT_FUNC == ELF32_ST_TYPE(symtab_addr[i].st_info)) {
			char str_out[FUNC_NAME_LEN] = {0};
			char name_mix[FUNC_NAME_LEN] = {0};

			/* function name string mix with chip platform */
			char *func_name = (char *)(str_tab + index);
			mix_func_name(name_mix, FUNC_NAME_LEN, chip_choose, func_name);

			/* do hash256 twice */
			EVP_Digest(name_mix, strlen(name_mix), hash_f, NULL, EVP_sha256(), NULL);
			EVP_Digest(hash_f, SHA256_DIGEST_LENGTH, hash_l, NULL, EVP_sha256(), NULL);
			byteToString(str_sub, hash_l, SUB_BYTE_LENGTH);

			/* format the new out strtab buffer */
			snprintf(str_out, FUNC_NAME_LEN, "%s %s\n", str_sub, func_name);
			fputs(str_out, tb_fp);

			/* update the symtab index */
			memcpy(pStr, str_sub, str_sub_len);
			index = pStr - str_tab_out;
			symtab_addr[i].st_name = index;
			pStr += str_sub_len;
		}
	}
	/* write out the updated symtab section */
	(void)fseek(out_fp, 0, SEEK_END);
	(void)fwrite(sym_tab, symtab_size, 1, out_fp);

	/* write out the strtab section */
	(void)fseek(out_fp, 0, SEEK_END);
	(void)fwrite(str_tab_out, (pStr - str_tab_out), 1, out_fp);
	free(str_tab_out);
	return 0;
}
#endif

int main(int argc, char *argv[])
{
#if DEBUG == 0
	if (argc < 6) {
#else
	if (argc < 4) {
#endif
		usage();
		return -1;
	}

	int ret = 0;
	Elf32_Ehdr *elf_head = NULL;
	Elf32_Shdr *sec_head = NULL;
	FILE *infile = NULL;
	FILE *outfile = NULL;
	char *sym_tab = NULL;
	char *str_tab = NULL;
#if DEBUG == 0
	FILE *tb_file = NULL;
	char *chip_choose = NULL;
#endif

	/* check the input type */
	char *type = argv[1];
	if (strncmp(type, "globaltask", strlen("globaltask")) &&
	    strncmp(type, "rtosck", strlen("rtosck"))) {
		printf("Error:wrong type input.\n");
		return -1;
	}

	/* open the infile which globaltask or rtosck elf */
	infile = fopen(argv[2], "rb");
	if (NULL == infile) {
		printf("Error:can't open file.\n");
		return -2;
	}

	/* open the outfile which globaltask or rtosck image */
	outfile = fopen(argv[3], "ab");
	if (NULL == outfile) {
		printf("Error:can't open file.\n");
		ret = -2;
		goto out;
	}

#if DEBUG == 0
	/* for release version, open the tb_file for func table output */
	tb_file = fopen(argv[4], "a+");
	if (NULL == tb_file) {
		printf("Error:can't open tb file.\n");
		ret = -2;
		goto out;
	}
	/* get che chip_choose for func name mix use */
	chip_choose = argv[5];
	if (NULL == chip_choose) {
		printf("Error: chip_choose is null.\n");
		ret = -2;
		goto out;
	}
#endif

	/* parse the elf header to get the elf detail */
	elf_head = (Elf32_Ehdr *)malloc(sizeof(Elf32_Ehdr));
	if (NULL == elf_head) {
		printf("Error:elf head read error!.\n");
		ret = -3;
		goto out;
	}

	ret = fread(elf_head, sizeof(Elf32_Ehdr), 1, infile);
	if (!ret) {
		printf("Error:elf head read error!.\n");
		ret = -3;
		goto out;
	}

	if (elf_head->eh_shnum == 0) {
		printf("Error:elf head shnum is zero!.\n");
		ret = -3;
		goto out;

	}

	if (fseek(infile, elf_head->eh_shoff, SEEK_SET) != 0) {
		printf("Error:elf head read error!.\n");
		ret = -3;
		goto out;
	}

	/* parse the section header to get the elf's section detail */
	sec_head = (Elf32_Shdr *)malloc(sizeof(Elf32_Shdr) * elf_head->eh_shnum);
	if (NULL == sec_head) {
		printf("Error:elf head read error!.\n");
		ret = -3;
		goto out;
	}


	ret = fread(sec_head, sizeof(Elf32_Shdr), elf_head->eh_shnum, infile);
	if (!ret) {
		printf("Error:section head read error!.\n");
		ret = -3;
		goto out;
	}

	int i = 0;
	int j = 0;
	unsigned int symtab_offset = 0;
	unsigned int strtab_offset = 0;

	Elf32_Shdr *sec_entry = sec_head;
	u32 sym_tab_size = 0;
	/* traverse all section and get the symtab and strtab of elf */
	for (i; i < elf_head->eh_shnum; i++) {

		if (sec_entry->sh_size == 0) {
			sec_entry++;
			continue;
		}

		/* read the symtab out */
		if (sec_entry->sh_type == SHT_SYMTAB) {
			symtab_offset = sec_entry->sh_offset;
			(void)fseek(infile, symtab_offset, SEEK_SET);
			sym_tab = (char *)malloc(sec_entry->sh_size);
			if (NULL == sym_tab) {
				printf("ERROR:malloc failed for sym_tab\n");
				ret = -4;
				goto out;
			}

			(void)fread(sym_tab, sec_entry->sh_size, 1, infile);
			sym_tab_size = sec_entry->sh_size;
#if DEBUG != 0
			/* for debug mode, just write into out image file */
			(void)fseek(outfile, 0, SEEK_END);
			(void)fwrite(sym_tab, sym_tab_size, 1, outfile);
#endif
		} else if (sec_entry->sh_type == SHT_STRTAB) {
			if (j == 0 && !strncmp("rtosck", type, strlen("rtosck"))) {
				/* read the rtosck strtab out */
				strtab_offset = sec_entry->sh_offset;
				(void)fseek(infile, strtab_offset, SEEK_SET);
				str_tab = (char *)malloc(sec_entry->sh_size);
				if (NULL == str_tab) {
					printf("ERROR:malloc failed for str_tab\n");
					ret = -4;
					goto out;
				}

				(void)fread(str_tab, sec_entry->sh_size, 1, infile);
#if DEBUG != 0
				/* for debug mode, just write into out image file */
				(void)fseek(outfile, 0, SEEK_END);
				(void)fwrite(str_tab, sec_entry->sh_size, 1, outfile);
#endif
				break;
			} else if (j == 1 && !strncmp("globaltask", type, strlen("globaltask"))) {
				/* read the globaltask strtab out */
				strtab_offset = sec_entry->sh_offset;
				(void)fseek(infile, strtab_offset, SEEK_SET);
				str_tab = (char *)malloc(sec_entry->sh_size);
				if (NULL == str_tab) {
					printf("ERROR:malloc failed for str_tab\n");
					ret = -4;
					goto out;
				}
				(void)fread(str_tab, sec_entry->sh_size, 1, infile);
#if DEBUG != 0
				/* for debug mode, just write into out image file */
				(void)fseek(outfile, 0, SEEK_END);
				(void)fwrite(str_tab, sec_entry->sh_size, 1, outfile);
#endif
				break;
			}
			j++;
		}
		sec_entry++;
	}

#if DEBUG == 0
	/* for release version, should format function table file */
	fputs(chip_choose, tb_file);
	/* header of table file output */
	if (!strncmp("rtosck", type, strlen("rtosck"))) {
		fputs("\n=====================RTOSCK FUNCTION TABLE BEGIN========================\n", tb_file);
	} else if (!strncmp("globaltask", type, strlen("globaltask"))) {
		fputs("\n=====================GLOBALTASK FUNCTION TABLE BEGIN========================\n", tb_file);
	} else {
		fputs("====ERROR TYPE BEGIN====\n", tb_file);
	}

	/* mixed the strtab function name string and write into out image file */
	ret = str_tab_out(sym_tab, sym_tab_size, str_tab, chip_choose, tb_file, outfile);
	if (ret) {
		printf("Error: str_tab_out failed.\n");
		goto out;
	}

	/* tail of table file output */
	if (!strncmp("rtosck", type, strlen("rtosck"))) {
		fputs("=====================RTOSCK FUNCTION TABLE END==========================\n\n", tb_file);
	} else if (!strncmp("globaltask", type, strlen("globaltask"))) {
		fputs("=====================GLOBALTASK FUNCTION TABLE END========================\n\n", tb_file);
	} else {
		fputs("====ERROR TYPE END====\n\n\n", tb_file);
	}
#endif

	/* ret should be success now */
	ret = 0;
out:
	/* free all file and alloced mem */
	if (sym_tab)
		free(sym_tab);
	if (str_tab)
		free(str_tab);
	if (elf_head)
		free(elf_head);
	if (sec_head)
		free(sec_head);
	if (infile)
		fclose(infile);
	if (outfile)
		fclose(outfile);
#if DEBUG == 0
	/* for release version should close func table file */
	if (tb_file)
		fclose(tb_file);
#endif
	return ret;
}
