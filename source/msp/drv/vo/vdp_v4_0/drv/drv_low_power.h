#ifndef __VDP_ENERGY_SAVING_H__
#define __VDP_ENERGY_SAVING_H__

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* __cplusplus */



HI_S32  LowPower_Init(HI_VOID);
HI_S32  LowPower_DeInit(HI_VOID);
HI_S32  LowPower_OpenIsogeny(HI_VOID);
HI_S32  LowPower_CloseIsogeny(HI_VOID);
HI_S32  LowPower_OperatePipLayer(HI_U32 u32LayerEnRecorder);



#endif  /*__VDP_ENERGY_SAVING_H__*/
