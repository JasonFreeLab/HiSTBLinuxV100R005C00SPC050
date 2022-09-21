
#ifndef __ASC_H__
#define __ASC_H__

typedef struct asc_params {
	uint32_t arg0;
	uint32_t arg1;
	uint32_t arg2;
	uint32_t arg3;
	uint32_t arg4;
	uint32_t arg6;
	uint32_t arg7;
	uint32_t arg8;
} asc_params_t;

#define BL33_IMG_ARM32 32
#define BL33_IMG_ARM64 64

#define CMD_SW_TO_NS    0x5AC3A569
#define CMD_LOAD_SOS    0xAC3A5695

#endif /* __ASC_H__ */
