

#include <linux/io.h>
#include <linux/of.h>

#include <linux/regulator/driver.h>

#include "mali_osk_mali.h"
#include "mali4xx_cfg.h"
#include "hi_drv_sys.h"

static unsigned long s_DefaultFreq = 0;
static unsigned long s_DefaultVolt = 0;
static unsigned long s_MaxFreq = 0;
static unsigned long s_MinFreq = 0;
static unsigned long s_MaxUtil = 0;
static unsigned long s_MinUtil = 0;

#ifdef GPU_SUPPORT_SVB

typedef enum{
    SVB_REG_ADDR_BASE = 0xf8000000,
    SVB_REG_ADDR_SIZE = 0x100,
    SVB_REG_OFFSET_REGISTER1 = 0xc4, /*about: type - ff - ss*/
    SVB_REG_OFFSET_REGISTER2 = 0xc8, /*about: tt*/
}svb_reg_addr;

typedef enum{
	SVB_CHIP_TYPE_FF = 1,
	SVB_CHIP_TYPE_TT = 2,
	SVB_CHIP_TYPE_SS = 3,
}svb_chip_type;

static char *clock_table[3] = {"operating-points-ff", "operating-points-tt", "operating-points-ss"};

#if defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300)
static char *clock_table_98mv300[3] = {"operating-points-ff-98mv300", "operating-points-tt-98mv300", "operating-points-ss-98mv300"};
static char *clock_table_youtube[3] = {"operating-points-ff-youtube", "operating-points-tt-youtube", "operating-points-ss-youtube"};
#endif

char* opps_get_svb_type(void)
{
    volatile u32* pu32SVBBase = (u32*)ioremap_nocache(SVB_REG_ADDR_BASE,  SVB_REG_ADDR_SIZE);
    int svb_type, svb_corner[3];
    int reg1, reg2;
#if defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300)
    HI_CHIP_TYPE_E ChipType;
    HI_CHIP_VERSION_E ChipID;
    HI_U32 ChipMode;
#endif

    if(pu32SVBBase == NULL)
    {
        HISI_ERROR_INFO();
        return NULL;
    }

    reg1 = *(pu32SVBBase +  (SVB_REG_OFFSET_REGISTER1 >> 2));
    reg2 = *(pu32SVBBase +  (SVB_REG_OFFSET_REGISTER2 >> 2));

    svb_type = (reg1 >> 24) & 0xff;
    svb_corner[0] = (reg1 >> 16) & 0xff;	/*ff*/
    svb_corner[1] = (reg1 >> 8) & 0xff;	    /*tt*/
    svb_corner[2] = reg1 & 0xff;		    /*ss*/

    iounmap(pu32SVBBase);

    if((svb_type != SVB_CHIP_TYPE_FF) && (svb_type != SVB_CHIP_TYPE_TT) && (svb_type != SVB_CHIP_TYPE_SS))
    {
        svb_type = SVB_CHIP_TYPE_SS;
    }

#if defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300)
    HI_DRV_SYS_GetChipVersion(&ChipType, &ChipID);

    HI_DRV_SYS_GetFlag(&ChipMode);

     /* 98mv200 ChipType had 3 solutions */
    if((HI_CHIP_TYPE_HI3798M == ChipType) && (HI_CHIP_VERSION_V300 == ChipID))
    {
        /* (1)98mv300 mode : Max freq is 675M, select 98mv300 clock table */
        s_MaxFreq = 675000000;

        return clock_table_98mv300[svb_type - 1];
    }
    else if(1 == ChipMode)
    {
        /* (2)98mv200 youtube mode : Max freq is 800M, select youtube clock table */
        s_MaxFreq = 800000000;

        return clock_table_youtube[svb_type - 1];
    }
    else
    {
        /* (3)98mv200 non-youtube mode : Max freq is 750M, it can be 800M in some BenchMark */
        s_MaxFreq = 750000000;
    }
#endif

    return clock_table[svb_type - 1];
}

#endif

unsigned long opps_get_default_freq(void)
{
    return s_DefaultFreq;
}

unsigned long opps_get_default_volt(void)
{
    return s_DefaultVolt;
}

unsigned long opps_get_max_freq(void)
{
    return s_MaxFreq;
}

unsigned long opps_get_min_freq(void)
{
    return s_MinFreq;
}

unsigned int opps_get_max_utilization(void)
{
    return s_MaxUtil;
}

unsigned int opps_get_min_utilization(void)
{
    return s_MinUtil;
}

int setup_opps(struct device *dev)
{
    struct mali_device *mdev = dev_get_drvdata(dev);
    const struct property *prop;
    const __be32 *val;
    int nr;
    char *operating_points;
    unsigned long core_vol;

    /* (1) Get Default Frequency */
    prop = of_find_property(dev->of_node, "default-frequency", NULL);
    if(!prop || !prop->value)
    {
        HISI_ERROR_INFO();
        return -ENODATA;
    }

    s_DefaultFreq = be32_to_cpup(prop->value);

    /* (2) Get Max/Min Frequency */
    prop = of_find_property(dev->of_node, "max-frequency", NULL);
    if(!prop || !prop->value)
    {
        HISI_ERROR_INFO();
        return -ENODATA;
    }

    s_MaxFreq = be32_to_cpup(prop->value);

    prop = of_find_property(dev->of_node, "min-frequency", NULL);
    if(!prop || !prop->value)
    {
        HISI_ERROR_INFO();
        return -ENODATA;
    }

    s_MinFreq = be32_to_cpup(prop->value);

    /* (3) Get Max/Min Utilization */
    prop = of_find_property(dev->of_node, "max-utilization", NULL);
    if(!prop || !prop->value)
    {
        HISI_ERROR_INFO();
        return -ENODATA;
    }

    s_MaxUtil = be32_to_cpup(prop->value);

    prop = of_find_property(dev->of_node, "min-utilization", NULL);
    if(!prop || !prop->value)
    {
        HISI_ERROR_INFO();
        return -ENODATA;
    }

    s_MinUtil = be32_to_cpup(prop->value);

    if(HISI_DEBUG)
        printk("setup_opps@ DefaultFreq = %ld, MaxFreq = %ld, MinFreq = %ld, MaxUtil = %ld, MinUtil = %ld\n",
            s_DefaultFreq, s_MaxFreq, s_MinFreq, s_MaxUtil, s_MinUtil);

    /* (4) Get Operating-points */
#ifdef GPU_SUPPORT_SVB
    operating_points = opps_get_svb_type();
#else
    operating_points = "operating-points";
#endif

    if(HISI_DEBUG)
        printk("setup_opps@ vmin table is %s\n", operating_points);

    prop = of_find_property(dev->of_node, operating_points, NULL);
    if(!prop || !prop->value)
    {
        HISI_ERROR_INFO();
        return -ENODATA;
    }

    nr = prop->length / sizeof(u32);
    if (nr % 2)
    {
        HISI_ERROR_INFO();
        return -EINVAL;
    }

    val = prop->value;

    /* (4) add vmin table */
    core_vol = (unsigned int)regulator_get_voltage(mdev->regulator);

    while (nr)
    {
        unsigned long freq = be32_to_cpup(val++) ;
        unsigned long volt = be32_to_cpup(val++) ;

#ifdef GPU_SUPPORT_SVB
        if(volt < core_vol)            /* gpu vmin could not be lower than core vmin */
        {
            volt = core_vol;
        }
#endif

        if(s_DefaultFreq == freq)
        {
            s_DefaultVolt = volt;
        }

        if(HISI_DEBUG)
            printk("setup_opps@ add opps ~ Freq = %ld, Volt = %ld\n", freq, volt);

        dev_pm_opp_add(dev, freq, volt);

        nr -= 2;
    }

	return 0;
}

int term_opps(struct device *dev)
{
    const struct property *prop;
    const __be32 *val;
    int nr;
    char *operating_points;

#ifdef GPU_SUPPORT_SVB
    operating_points = opps_get_svb_type();
#else
    operating_points = "operating-points";
#endif

    prop = of_find_property(dev->of_node, operating_points, NULL);
    if(!prop)
    {
        HISI_ERROR_INFO();
        return -ENODEV;
    }
    if(!prop->value)
    {
        HISI_ERROR_INFO();
        return -ENODATA;
    }

    nr = prop->length / sizeof(u32);
    if (nr % 2)
    {
        HISI_ERROR_INFO();
        return -EINVAL;
    }

    val = prop->value;

    while (nr)
    {
        unsigned long freq = be32_to_cpup(val);

        dev_pm_opp_remove(dev, freq);

        val += 2;
        nr -= 2;
    }

    if(HISI_DEBUG)
        printk("term_opps@\n");

	return 0;
}

