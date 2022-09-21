#ifndef __VDP_ASYNC_DEFINE_H__
#define __VDP_ASYNC_DEFINE_H__

#define ENERGY_SAVING_QUEUE_IDX 0

/*Register name enum used in enery saving msg*/
typedef enum
{
    REG_V0_LAYER_CLOCK_GATE = 0,
    REG_V1_LAYER_CLOCK_GATE,
    REG_V3_LAYER_CLOCK_GATE,
    REG_VP_WBC_VIDEO_CLOCK_GATE,
    REG_DHD_WBC_VIDEO_CLOCK_GATE,
    REG_VBG_VIDEO_CLOCK_GATE,
    REG_BUTT,
}REG_NAME_E;

/*Struct defination for a message type*/
typedef struct
{
    REG_NAME_E enRegName;
    HI_BOOL bRegStatus;
}ASYNC_MSG_ENERGYSAVING_S;



/*Message type, different types can be extended*/
typedef enum
{
    ASYNC_MSG_TYPE_LOWPOWER = 0,
    // extend ...
    ASYNC_MSG_TYPE_BUTT,
}ASYNC_MSG_TYPE;

/*This struct can store every type of messages*/
typedef struct
{
    /*Expected time that the message take effect, use jiffies*/
    HI_ULONG ulExpectedTime;
    
    ASYNC_MSG_TYPE enAsyncType;
    
    /*Message item infomation, other async message structs can be extended*/
    union
    {
        ASYNC_MSG_ENERGYSAVING_S AsyncMsgEnergysaving;
        // extend ...
    }unMsgItem;
}ASYNC_MSG_S;



#endif  /*__VDP_ASYNC_DEFINE_H__*/
