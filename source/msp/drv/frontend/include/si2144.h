
#ifndef __SI2144_H__
#define __SI2144_H__

extern HI_S32 si2144_init_tuner(HI_U32 u32TunerPort,HI_U32 u32I2cChannel);
extern HI_S32 si2144_set_tuner (HI_U32 u32TunerPort, HI_U32 u32Frequency,HI_U32 u32BandWidth);
extern HI_S32 si2144_set_tuner_dvbc(HI_U32 u32TunerPort, HI_U8 enI2cChannel, HI_U32 u32PuRF);
extern HI_VOID si2144_tuner_resume (HI_U32 u32TunerPort);
extern HI_S32 si2144_init_tuner_dvbc(HI_U32 u32TunerPort);
extern HI_S32 si2144_get_signal_strength(HI_U32 u32TunerPort, HI_U32 *pu32SignalStrength);
#endif

