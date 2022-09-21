#ifndef __R858_H__
#define __R858_H__

extern HI_S32 r858_init_tuner(HI_U32 u32TunerPort);
extern HI_S32 r858_set_tuner(HI_U32 u32TunerPort, HI_U8 enI2cChannel, HI_U32 puRF);
extern HI_VOID r858_tuner_resume (HI_U32 u32TunerPort);
extern HI_S32 r858_get_signal_strength(HI_U32 u32TunerPort, HI_U32 *pu32SignalStrength);
#endif

