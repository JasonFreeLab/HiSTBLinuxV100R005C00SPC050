
#ifndef __R850_H__
#define __R850_H__

extern HI_S32 r850_init_tuner(HI_U32 u32TunerPort);
extern HI_S32 r850_set_tuner(HI_U32 u32TunerPort, HI_U8  enI2cChannel, HI_U32 puRF);
extern HI_VOID r850_tuner_resume (HI_U32 u32TunerPort);
extern HI_VOID r850_get_signal_strength(HI_U32 u32TunerPort, HI_U32 *pu32SignalStrength);
extern HI_S32 r850_tuner_standby(HI_U32 u32TunerPort, HI_U32 u32Status);
#endif

