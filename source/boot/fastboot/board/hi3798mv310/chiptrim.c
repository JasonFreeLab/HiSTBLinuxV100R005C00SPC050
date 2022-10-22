#include <asm/arch/platform.h>
#include <asm/io.h>
#include <common.h>

#define CHANNEL_SEL            (OTP_REG_BASE + 0x00)
#define CPU_RW_CTRL            (OTP_REG_BASE + 0x04)
#define CPU_WR_START           (OTP_REG_BASE + 0x08)
#define CTRL_STATUS            (OTP_REG_BASE + 0x0C)
#define CPU_OTP_RDATA          (OTP_REG_BASE + 0x10)
#define CPU_OTP_WDATA          (OTP_REG_BASE + 0x14)
#define CPU_OTP_RADDR          (OTP_REG_BASE + 0x18)
#define CPU_OTP_WADDR          (OTP_REG_BASE + 0x1c)
#define OTP_MODE               (OTP_REG_BASE + 0x20)
#define CPU_ADDR_LOCK0         (OTP_REG_BASE + 0x24)
#define CPU_ADDR_LOCK1         (OTP_REG_BASE + 0x28)
#define CPU_ADDR_LOCK2         (OTP_REG_BASE + 0x2c)
#define CPU_ADDR_LOCK3         (OTP_REG_BASE + 0x30)
#define CPU_ADDR_LOCK_EN       (OTP_REG_BASE + 0x34)
#define ID_WORD_DATA           (OTP_REG_BASE + 0x80 + 0xa8)
#define W_ONCE_ONLY            (OTP_REG_BASE + 0x184)

#define OTP_MEM_STATUS         (OTP_REG_BASE + 0x1b8)
#define OTP_PWR_ERROR          (OTP_REG_BASE + 0x1bc)
#define OTP_PWR_CHECK_EN       (OTP_REG_BASE + 0x1c0)
#define REG_W_ONCE_ONLY        (OTP_REG_BASE + 0x184)
#define AUX_CODE_FLAG          (OTP_REG_BASE + 0x1c4)
#define OTP_SOFT_RST_ADDR      (OTP_REG_BASE + 0x1e4)

static inline void wait_otp_ready(void)
{
	int loop;
	u32 value, ctrl_ready;

	value = readl(CTRL_STATUS);
	ctrl_ready = value % 2;
	loop = 0x1000;
	while (ctrl_ready != 1) {
		value = readl(CTRL_STATUS);
		ctrl_ready = value % 2;

		if (loop-- < 0) {
			printf("otp: read otp value time out.\n");
			loop = 0x1000;
		}
	}
}

static void otp_soft_reset(void)
{
	writel(0x01, OTP_SOFT_RST_ADDR);
	writel(0x00, OTP_SOFT_RST_ADDR);
}

static void otp_write(u32 addr, u32 value)
{
	writel(value, addr);
}

static void otp_init(void)
{
	static int init_done = 0;

	if (init_done)
		return;

	otp_soft_reset();

	wait_otp_ready();

	init_done = 1;
}

static u32 get_otp_value(u32 Addr)
{
	u32 result = 0;

	otp_init();

	otp_write(CHANNEL_SEL, 0x00002);
	otp_write(CPU_RW_CTRL, 0x0002); 
	otp_write(CPU_OTP_RADDR, Addr);

	wait_otp_ready();
	result = readl(CPU_OTP_RDATA);

	return result;
}

static int __chiptrim_value[2] = {0};

char *chiptrim_value = (char *)__chiptrim_value;
int chiptrim_size = 0;

void load_chiptrim(void)
{
	__chiptrim_value[0] = get_otp_value(0x4fc);
	__chiptrim_value[1] = get_otp_value(0x250);

	chiptrim_size = 8;
}
