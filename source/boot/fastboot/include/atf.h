/******************************************************************************
 *    Copyright (C) 2017 Hisilicon STB Development Dept
 *    All rights reserved.
 * ***
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

#ifndef __ATF_H__
#define __ATF_H__

/**************************************************************/
#define ARM_BOOT_SMC_CALL               0x8400ff02

#define SECURE		0x0
#define NON_SECURE	0x1

#define EP_EE_MASK      0x2
#define EP_EE_LITTLE    0x0
#define EP_EE_BIG       0x2
#define EP_GET_EE(x) (x & EP_EE_MASK)
#define EP_SET_EE(x, ee) ((x) = ((x) & ~EP_EE_MASK) | (ee))

/* CPSR/SPSR definitions */
#define DAIF_FIQ_BIT		(1 << 0)
#define DAIF_IRQ_BIT		(1 << 1)
#define DAIF_ABT_BIT		(1 << 2)
#define DAIF_DBG_BIT		(1 << 3)
#define SPSR_DAIF_SHIFT		6
#define SPSR_DAIF_MASK		0xf

#define SPSR_AIF_SHIFT          6
#define SPSR_AIF_MASK           0x7

#define SPSR_E_SHIFT            9
#define SPSR_E_MASK                     0x1
#define SPSR_E_LITTLE           0x0
#define SPSR_E_BIG                      0x1

#define SPSR_T_SHIFT            5
#define SPSR_T_MASK                     0x1
#define SPSR_T_ARM                      0x0
#define SPSR_T_THUMB            0x1

#define MODE_SP_SHIFT		0x0
#define MODE_SP_MASK		0x1
#define MODE_SP_EL0		0x0
#define MODE_SP_ELX		0x1

#define MODE_RW_SHIFT		0x4
#define MODE_RW_MASK		0x1
#define MODE_RW_64			0x0
#define MODE_RW_32			0x1

#define MODE_EL_SHIFT		0x2
#define MODE_EL_MASK		0x3
#define MODE_EL3		0x3
#define MODE_EL2		0x2
#define MODE_EL1		0x1
#define MODE_EL0		0x0

#define MODE32_SHIFT            0
#define MODE32_MASK             0xf
#define MODE32_usr              0x0
#define MODE32_fiq              0x1
#define MODE32_irq              0x2
#define MODE32_svc              0x3
#define MODE32_mon              0x6
#define MODE32_abt              0x7
#define MODE32_hyp              0xa
#define MODE32_und              0xb
#define MODE32_sys              0xf

#define DISABLE_ALL_EXCEPTIONS \
		(DAIF_FIQ_BIT | DAIF_IRQ_BIT | DAIF_ABT_BIT | DAIF_DBG_BIT)

#define PARAM_EP_SECURITY_MASK    0x1
#define GET_SECURITY_STATE(x) (x & PARAM_EP_SECURITY_MASK)
#define SET_SECURITY_STATE(x, security) \
			((x) = ((x) & ~PARAM_EP_SECURITY_MASK) | (security))

#define SPSR_64(el, sp, daif)				\
	(MODE_RW_64 << MODE_RW_SHIFT |			\
	((el) & MODE_EL_MASK) << MODE_EL_SHIFT |	\
	((sp) & MODE_SP_MASK) << MODE_SP_SHIFT |	\
	((daif) & SPSR_DAIF_MASK) << SPSR_DAIF_SHIFT)

#define SPSR_MODE32(mode, isa, endian, aif)		\
	(MODE_RW_32 << MODE_RW_SHIFT |			\
	((mode) & MODE32_MASK) << MODE32_SHIFT |	\
	((isa) & SPSR_T_MASK) << SPSR_T_SHIFT |		\
	((endian) & SPSR_E_MASK) << SPSR_E_SHIFT |	\
	((aif) & SPSR_AIF_MASK) << SPSR_AIF_SHIFT)


/* Length of a node address (an IEEE 802 address). */
#define	_UUID_NODE_LEN		6

#define FIP_MAX_FILES			3

/* TODO: Update this number as required */
#define TOC_HEADER_SERIAL_NUMBER	0x12345678

#define FLAG_FILENAME			(1 << 0)

/* This is used as a signature to validate the blob header */
#define TOC_HEADER_NAME	0xAA640001

/* ToC Entry UUIDs */
#define UUID_TRUSTED_BOOT_FIRMWARE_BL2 \
	{0x0becf95f, 0x224d, 0x4d3e, 0xa5, 0x44, {0xc3, 0x9d, 0x81, 0xc7, 0x3f, 0x0a} }
#define UUID_SCP_FIRMWARE_BL30 \
	{0x3dfd6697, 0xbe89, 0x49e8, 0xae, 0x5d, {0x78, 0xa1, 0x40, 0x60, 0x82, 0x13} }
#define UUID_EL3_RUNTIME_FIRMWARE_BL31 \
	{0x6d08d447, 0xfe4c, 0x4698, 0x9b, 0x95, {0x29, 0x50, 0xcb, 0xbd, 0x5a, 0x00} }
#define UUID_SECURE_PAYLOAD_BL32 \
	{0x89e1d005, 0xdc53, 0x4713, 0x8d, 0x2b, {0x50, 0x0a, 0x4b, 0x7a, 0x3e, 0x38} }
#define UUID_NON_TRUSTED_FIRMWARE_BL33 \
	{0xa7eed0d6, 0xeafc, 0x4bd5, 0x97, 0x82, {0x99, 0x34, 0xf2, 0x34, 0xb6, 0xe4} }

/**************************************************************/
/* XXX namespace pollution? */
typedef struct uuid uuid_t;

/**************************************************************/
/*
 * See also:
 *      http://www.opengroup.org/dce/info/draft-leach-uuids-guids-01.txt
 *      http://www.opengroup.org/onlinepubs/009629399/apdxa.htm
 *
 * A DCE 1.1 compatible source representation of UUIDs.
 */
struct uuid {
	uint32_t	time_low;
	uint16_t	time_mid;
	uint16_t	time_hi_and_version;
	uint8_t		clock_seq_hi_and_reserved;
	uint8_t		clock_seq_low;
	uint8_t		node[_UUID_NODE_LEN];
};

typedef struct entry_lookup_list {
	const char		*name;
	uuid_t			 name_uuid;
	const char		*command_line_name;
	struct file_info	*info;
	unsigned int		 flags;
} entry_lookup_list_t;

typedef struct file_info {
	uuid_t			 name_uuid;
	const char		*filename;
	unsigned int		 size;
	void			*image_buffer;
	entry_lookup_list_t	*entry;
} file_info_t;

typedef struct fip_toc_header {
	uint32_t	name;
	uint32_t	serial_number;
	uint64_t	flags;
} fip_toc_header_t;

typedef struct fip_toc_entry {
	uuid_t		uuid;
	uint64_t	offset_address;
	uint64_t	size;
	uint64_t	flags;
} fip_toc_entry_t;

typedef struct aapcs64_params {
	uint64_t arg0;
	uint64_t arg1;
	uint64_t arg2;
	uint64_t arg3;
	uint64_t arg4;
	uint64_t arg5;
	uint64_t arg6;
	uint64_t arg7;
} aapcs64_params_t;

/***************************************************************************
 * This structure provides version information and the size of the
 * structure, attributes for the structure it represents
 ***************************************************************************/
typedef struct param_header {
	uint8_t type;		/* type of the structure */
	uint8_t version;    /* version of this structure */
	uint16_t size;      /* size of this structure in bytes */
	uint32_t attr;      /* attributes: unused bits SBZ */
} param_header_t;

/*****************************************************************************
 * This structure represents the superset of information needed while
 * switching exception levels. The only two mechanisms to do so are
 * ERET & SMC. Security state is indicated using bit zero of header
 * attribute
 * NOTE: BL1 expects entrypoint followed by spsr while processing
 * SMC to jump to BL31 from the start of entry_point_info
 *****************************************************************************/
typedef struct entry_point_info {
	param_header_t h;
	uint64_t pc;
	uint32_t spsr;
	aapcs64_params_t args;
} entry_point_info_t;

/*****************************************************************************
 * Image info binary provides information from the image loader that
 * can be used by the firmware to manage available trusted RAM.
 * More advanced firmware image formats can provide additional
 * information that enables optimization or greater flexibility in the
 * common firmware code
 *****************************************************************************/
typedef struct atf_image_info {
	param_header_t h;
	uint64_t image_base;   /* physical address of base of image */
	uint32_t image_size;    /* bytes read from image file */
	uint32_t copied_size;	/* image size copied in blocks */
} atf_image_info_t;

/*******************************************************************************
 * This structure represents the superset of information that can be passed to
 * BL31 e.g. while passing control to it from BL2. The BL32 parameters will be
 * populated only if BL2 detects its presence. A pointer to a structure of this
 * type should be passed in X0 to BL31's cold boot entrypoint.
 *
 * Use of this structure and the X0 parameter is not mandatory: the BL31
 * platform code can use other mechanisms to provide the necessary information
 * about BL32 and BL33 to the common and SPD code.
 *
 * BL31 image information is mandatory if this structure is used. If either of
 * the optional BL32 and BL33 image information is not provided, this is
 * indicated by the respective image_info pointers being zero.
 ******************************************************************************/
typedef struct bl31_params {
	param_header_t h;
	uint64_t bl31_image_info;//atf_image_info_t *bl31_image_info;
	uint64_t bl32_ep_info;//entry_point_info_t *bl32_ep_info;
	uint64_t bl32_image_info;//atf_image_info_t *bl32_image_info;
	uint64_t bl33_ep_info;//entry_point_info_t *bl33_ep_info;
	uint64_t bl33_image_info;//atf_image_info_t *bl33_image_info;
} bl31_params_t;

typedef struct smc_cmd_args {
	uint32_t arg1;
	uint32_t arg2;
	uint32_t arg3;
	uint32_t arg4;
	uint32_t arg5;
}smc_cmd_args_t;


#endif /* __ATF_H__ */

