#ifndef __VFMW_SYSCONFIG_HEADER__
#define __VFMW_SYSCONFIG_HEADER__

/*��֧�ֵ�VDH����*/
#define MAX_VDH_NUM 1

/*��֧�ֵ�SCD����,������VDH�ɶԽ���*/
#define MAX_SCD_NUM  MAX_VDH_NUM
#define MAX_DSP_NUM  MAX_VDH_NUM

/*��ʾ���ӳ�����DSP�ļ������*/
#define LOWDLY_DSP_ID  (0)
#define AVS_DSP_ID     (1)

/* ϵͳ���ƼĴ�����ַ��λ�� */
#define SCD_RESET_REG_PHY_ADDR     0xf8a22078   //scd
#define SCD_RESET_REG_PHY_ADDR_1   SCD_RESET_REG_PHY_ADDR   //scd

/* Ӳ������IP�ӿڼĴ�����ַ */
#define VDM_REG_PHY_ADDR       0xf8c30000     // VDM0 �Ĵ���ӳ�䵽ARM�ռ�ĵ�ַ   asci:0xf8c30000
#define VDM_REG_PHY_ADDR_1     0xf9c50000     // VDM1�Ĵ���ӳ�䵽ARM�ռ�ĵ�ַ
#define DNR_REG_PHY_ADDR       0x10450000     // DNR
#define SCD_REG_PHY_ADDR       0xf8c3c000     // scd �Ĵ���ӳ�䵽ARM�ռ�ĵ�ַ   asci:0xf8c3c000
#define SCD_REG_PHY_ADDR_1     0xf9c5c000     // scd1 �Ĵ���ӳ�䵽ARM�ռ�ĵ�ַ
#define FOD_REG_PHY_ADDR       0x10150000     // fod �Ĵ���ӳ�䵽ARM�ռ�ĵ�ַ
#define BPD_REG_PHY_ADDR       0xf8c3d000     // asci:0xf8c3d000
#define BTL_REG_PHY_ADDR       0xf8d00000     // BTL�Ĵ���ӳ�䵽ARM�ռ�ĵ�ַ����ʼ��ַ����
#define SYSTEM_REG_PHY_ADDR    0xf8a22000     //  ϵͳ�Ĵ���

#define SYSTEM_REG_RANGE       (1024*1024)
/* �жϺ� */
#ifdef ENV_SOS_KERNEL
#define VDM_INT_NUM            (105+32)
#define VDM_INT_NUM_1          (136+32)
#define SCD_INT_NUM            (106+32)
#define SCD_INT_NUM_1          (137+32)
#define MMU_VDH_NUM            (148+32)
#define VDH_IRQ_NAME_INDEX     (1)
#define SCD_IRQ_NAME_INDEX     (5)
#define MMU_IRQ_NAME_INDEX     (14)
#else
#define VDM_INT_NUM            (95+32)
#define VDM_INT_NUM_1          (136+32)
#define SCD_INT_NUM            (104+32)
#define SCD_INT_NUM_1          (137+32)
#define MMU_VDH_NUM            (149+32)
#define VDH_IRQ_NAME_INDEX     (0)
#define SCD_IRQ_NAME_INDEX     (4)
#define MMU_IRQ_NAME_INDEX     (13)

#endif

#define BPD_INT_NUM            (99+32)
#define DNR_INT_NUM            (61+32)
#define BTL_INT_NUM            (103+32)
#ifdef ENV_SOS_KERNEL
#define BOARD_MEM_BASE_ADDR    (0x3B000000) //sos,need sure
#define BOARD_MEM_TOTAL_SIZE   (72*1024*1024)
#else
/* ���Ե����Ͽɱ���Ƶ����ʹ�õ�memoryԤ�� */
//#define BOARD_MEM_BASE_ADDR    0x98000000
#define BOARD_MEM_BASE_ADDR    0x08000000
#define BOARD_MEM_TOTAL_SIZE   (72*1024*1024)
#endif
#endif
