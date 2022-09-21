/******************************************************************************
 Copyright (C), 20016-2026, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hdmi_test_cec.c
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2010/07/08
Last Modified :
Description   : HDMI TEST CEC interface
Function List :
History       :
******************************************************************************/
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include "hi_adp.h"
#include "hi_adp_hdmi.h"
#include "hdmi_test_cec.h"

/******************************************************************************/
/* Macro define                                                               */
/******************************************************************************/
#define CEC_MESSAGE_RETURN_OK_WITH_RESPONES     0x01
#define CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES  0x02
#define CEC_MESSAGE_RETURN_ERROR_NOSUPPORT      0x03
#define CEC_MESSAGE_RETURN_BUTT                 0x04

//cec power status
#define CEC_POWER_STATUS_ON                     0x00
#define CEC_POWER_STATUS_STANDBY                0x01
#define CEC_POWER_STATUS_STANDBY2ON             0x02
#define CEC_POWER_STATUS_ON2STANDBY             0x03

#define CEC_READY_TIME

#define HDMI_TEST_CEC_LOG(fmt...) \
do { \
    if(HI_TRUE == s_stCecCtx.bLogView) \
    { \
        printf(fmt); \
    } \
}while(0);
/******************************************************************************/
/* Global Data                                                                */
/******************************************************************************/
static HI_S32      g_cecCmdId = 1;
static HI_U8       g_cecPowerStatus = CEC_POWER_STATUS_STANDBY;

static HDMI_TEST_CEC_S s_stCecCtx;


/******************************************************************************/
/* Public Interface                                                           */
/******************************************************************************/
HI_VOID HDMI_CEC_LogSet(HI_BOOL bLogView)
{
    s_stCecCtx.bLogView = bLogView;

    return;
}

/*
**  Print CEC cmd
*/
HI_VOID HDMI_CEC_PrintCmd(HI_UNF_HDMI_CEC_CMD_S *pstCECCmd)
{
    HI_U32 i;

    HDMI_TEST_CEC_LOG("\n==============================================================================\n");
    HDMI_TEST_CEC_LOG("Cec Cmd Index: %d \n", g_cecCmdId++);
    HDMI_TEST_CEC_LOG("Src Addr:0x%x\n", pstCECCmd->enSrcAdd);
    HDMI_TEST_CEC_LOG("Dst Addr:0x%x\n", pstCECCmd->enDstAdd);
    HDMI_TEST_CEC_LOG("OpCode  :0x%x\n", pstCECCmd->u8Opcode);
    HDMI_TEST_CEC_LOG("cmd len :0x%x\n", pstCECCmd->unOperand.stRawData.u8Length);

    for(i = 0;i < pstCECCmd->unOperand.stRawData.u8Length; i++)
    {
        HDMI_TEST_CEC_LOG("OpData[%d]:0x%x\n", i+1, pstCECCmd->unOperand.stRawData.u8Data[i]);
    }
    HDMI_TEST_CEC_LOG("\n");

    return ;
}

/*
**  Parse CEC message
*/
HI_U32 HDMI_CEC_MsgParse(HI_UNF_HDMI_CEC_CMD_S *pCECCmdGet,HI_UNF_HDMI_CEC_CMD_S *pCECCmdSet)
{
    //Default Return is Error NoSupprot!
    HI_U32 Ret = CEC_MESSAGE_RETURN_ERROR_NOSUPPORT;
    HI_U32 Rec;
    HI_UNF_HDMI_CEC_STATUS_S  stCECStatus;
    HI_U8 Init, Dest, opcode, OperandLength;
    HI_U8 *pOperand;
    HI_U8   u8Para1,u8Para2;

    Rec = HI_UNF_HDMI_CECStatus(HI_UNF_HDMI_ID_0, &stCECStatus);
    if(Rec != HI_SUCCESS)
    {
        HDMI_TEST_CEC_LOG("Get CEC Status Fail! return \n");
        return Ret;
    }

    if(stCECStatus.bEnable != HI_TRUE)
    {
        HDMI_TEST_CEC_LOG("CEC Disable! return \n");
        return Ret;
    }

    //add by sample
    Init = pCECCmdGet->enSrcAdd;
    Dest = pCECCmdGet->enDstAdd;
    opcode = pCECCmdGet->u8Opcode;
    pOperand = pCECCmdGet->unOperand.stRawData.u8Data;
    OperandLength = pCECCmdGet->unOperand.stRawData.u8Length;

    pCECCmdSet->enSrcAdd = stCECStatus.u8LogicalAddr;

    switch(opcode)
    {
        /*General Protocol messages*/
        case CEC_OPCODE_FEATURE_ABORT:                   //0X00
            HDMI_TEST_CEC_LOG("FEATURE ABORT Init:%d, Dest:%d, opcode:0x%x\n", Init, Dest, opcode);
            Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES; //need not response
            break;
        case CEC_OPCODE_ABORT_MESSAGE:                   //0XFF
            HDMI_TEST_CEC_LOG("ABORT MESSAGE\n");
            Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES; //need not response
            break;

        /*One Touch Play Feature*/
        case CEC_OPCODE_ACTIVE_SOURCE:                   //0X82
            HDMI_TEST_CEC_LOG("ACTIVE_SOURCE\n");
             // [Physical Address(A.B.C.D):A B]

            if(pOperand[0] != (((stCECStatus.u8PhysicalAddr[0] << 4) & 0xf0) | (stCECStatus.u8PhysicalAddr[1] & 0x0f)) ||
                pOperand[1] != (((stCECStatus.u8PhysicalAddr[2] << 4) & 0xf0) | (stCECStatus.u8PhysicalAddr[3] & 0x0f)))
            {
                g_cecPowerStatus = CEC_POWER_STATUS_STANDBY;
                HDMI_TEST_CEC_LOG("change to other output port,hdmi standby \n");
            }

            //HDMI_TEST_CEC_LOG("It should be source cmd, ignore!\n");
            break;
        case CEC_OPCODE_IMAGE_VIEW_ON:                   //0X04
            HDMI_TEST_CEC_LOG("IMAGE_VIEW_ON\n");
            HDMI_TEST_CEC_LOG("It should be source cmd, ignore!\n");
            break;
        case CEC_OPCODE_TEXT_VIEW_ON:                    //0X0D
            HDMI_TEST_CEC_LOG("TEXT_VIEW_ON\n");
            HDMI_TEST_CEC_LOG("It should be source cmd, ignore!\n");
            break;

        /*Routing Control Feature*/
        case CEC_OPCODE_INACTIVE_SOURCE:                 //0X9D
            HDMI_TEST_CEC_LOG("INACTIVE_SOURCE, No supprot\n");
            Ret = CEC_MESSAGE_RETURN_ERROR_NOSUPPORT;
            break;
        case CEC_OPCODE_REQUEST_ACTIVE_SOURCE:           //0X85
        //When a device(TV) comes out of the standy state, it maybe broacast a
        //<Request Active Source> message to discover active source.
        //the active source device shall respond by broadcasting an <Active Source> message.
        {
            HDMI_TEST_CEC_LOG("REQUEST_ACTIVE_SOURCE, return Active Source\n");
            //we should send back a message of ACTIVE_SOURCE
            pCECCmdSet->u8Opcode  = CEC_OPCODE_ACTIVE_SOURCE;
            pCECCmdSet->enDstAdd  = HI_UNF_CEC_LOGICALADD_BROADCAST;
            pCECCmdSet->unOperand.stRawData.u8Length         = 2;
            pCECCmdSet->unOperand.stRawData.u8Data[0]     = ((stCECStatus.u8PhysicalAddr[0] << 4) & 0xf0) | (stCECStatus.u8PhysicalAddr[1] & 0x0f); // [Physical Address(A.B.C.D):A B]
            pCECCmdSet->unOperand.stRawData.u8Data[1]     = ((stCECStatus.u8PhysicalAddr[2] << 4) & 0xf0) | (stCECStatus.u8PhysicalAddr[3] & 0x0f) ; // [Physical Address(A.B.C.D):C D]
        }
            Ret = CEC_MESSAGE_RETURN_OK_WITH_RESPONES;
            break;
        case CEC_OPCODE_ROUTING_CHANGE:                  //0X80
            HDMI_TEST_CEC_LOG("ROUTING_CHANGE, it should be brocast message\n");
            break;
        case CEC_OPCODE_ROUTING_INFORMATION:             //0X81
            HDMI_TEST_CEC_LOG("ROUTING_INFORMATION, it should be brocast message\n");
            break;
        case CEC_OPCODE_SET_STREAM_PATH:                 //0X86
        //the <Set Stream Path> is sent by the TV to the source device
        //to request it to broacst its path using an <Active Source> message.

            HDMI_TEST_CEC_LOG("SET_STREAM_PATH\n");

            u8Para1 = ((stCECStatus.u8PhysicalAddr[0] << 4) & 0xf0) | (stCECStatus.u8PhysicalAddr[1] & 0x0f); // [Physical Address(A.B.C.D):A B]
            u8Para2 = ((stCECStatus.u8PhysicalAddr[2] << 4) & 0xf0) | (stCECStatus.u8PhysicalAddr[3] & 0x0f) ;// [Physical Address(A.B.C.D):C D]


            if((pCECCmdGet->unOperand.stRawData.u8Data[0] == u8Para1) &&
                (pCECCmdGet->unOperand.stRawData.u8Data[1] == u8Para2))
            {
                HDMI_TEST_CEC_LOG("STREAM_PATH same as our Tx ,request \n");
                //we should send back a message of ACTIVE_SOURCE
                pCECCmdSet->u8Opcode = CEC_OPCODE_ACTIVE_SOURCE;
                pCECCmdSet->enDstAdd = HI_UNF_CEC_LOGICALADD_BROADCAST;
                pCECCmdSet->unOperand.stRawData.u8Length = 2;
                pCECCmdSet->unOperand.stRawData.u8Data[0] = u8Para1;
                pCECCmdSet->unOperand.stRawData.u8Data[1] = u8Para2;
            }

            Ret = CEC_MESSAGE_RETURN_OK_WITH_RESPONES;
            break;
        /*Standby Feature*/
        case CEC_OPCODE_STANDBY:                         //0X36
            HDMI_TEST_CEC_LOG("STANDBY! It should brocast message\n");
            break;
        /*One Touch Record Feature*/
        case CEC_OPCODE_RECORD_OFF:                      //0X0B
            break;
        case CEC_OPCODE_RECORD_ON:                       //0X09
            break;
        case CEC_OPCODE_RECORD_STATUS:                   //0X0A
            break;
        case CEC_OPCODE_RECORD_TV_SCREEN:                //0X0F
            break;
        /*Timer Programming Feature*/
        case CEC_OPCODE_CLEAR_ANALOGUE_TIMER:            //0X33
            break;
        case CEC_OPCODE_CLEAR_DIGITAL_TIMER:             //0X99
            break;
        case CEC_OPCODE_CLEAR_EXTERNAL_TIMER:            //0XA1
            break;
        case CEC_OPCODE_SET_ANALOGUE_TIMER:              //0X34
            break;
        case CEC_OPCODE_SET_DIGITAL_TIMER:               //0X97
            break;
        case CEC_OPCODE_SET_EXTERNAL_TIMER:              //0XA2
            break;
        case CEC_OPCODE_SET_TIMER_PROGRAM_TITLE:         //0X67
            break;
        case CEC_OPCODE_TIMER_CLEARED_STATUS:            //0X43
            break;
        case CEC_OPCODE_TIMER_STATUS:                    //0X35
            break;

        /*System Information Feature*/
        case CEC_OPCODE_CEC_VERSION:                     //0X9E
            HDMI_TEST_CEC_LOG("CEC_VERSION:\n");
            HDMI_TEST_CEC_LOG("OperandLength:0x%02x \n",OperandLength);
            switch (pOperand[0])
            {
                case 0x04 :
                    HDMI_TEST_CEC_LOG("Version 1.3a\n");
                    break;
                case 0x05 :
                    HDMI_TEST_CEC_LOG("Version 1.4 or Version 1.4a or Version 1.4b \n");
                    break;
                default:
                    HDMI_TEST_CEC_LOG("unknown CEC_VERSION \n");
            }
#if 0 /*--NO MODIFY : COMMENT BY CODINGPARTNER--*/
            {
                int index;
                for(index = 0; index < OperandLength; index ++)
                {
                    if( ((pOperand[index] >= 'a') && (pOperand[index] <= 'z'))
                     || ((pOperand[index] >= 'A') && (pOperand[index] <= 'Z')) )
                    {
                        HDMI_TEST_CEC_LOG("%c", pOperand[index]);
                    }
                    else
                    {
                        HDMI_TEST_CEC_LOG("%02x", pOperand[index]);
                    }
                }
            }
            HDMI_TEST_CEC_LOG("\n");
#endif /*--NO MODIFY : COMMENT BY CODINGPARTNER--*/
            break;
        case CEC_OPCODE_GET_CEC_VERSION:                 //0X9F
            HDMI_TEST_CEC_LOG("GET_CEC_VERSION, Response\n");
            //we should send back a message of ACTIVE_SOURCE
            pCECCmdSet->u8Opcode   = CEC_OPCODE_CEC_VERSION;
            pCECCmdSet->enDstAdd = Init;
            pCECCmdSet->unOperand.stRawData.u8Length         = 1;
            //hdmi spec1.4b cec spec page.108
            // 0x04 cec 1.3a   0x05 cec 1.4/1.4a/1.4b
            pCECCmdSet->unOperand.stRawData.u8Data[0]     = 0x04;

#if 0
            pCECframe->bCount          = 3;
            pCECframe->bOperand[0]     = '1';
            pCECframe->bOperand[1]     = '3' ;
            pCECframe->bOperand[2]     = 'a' ;
#endif
            Ret = CEC_MESSAGE_RETURN_OK_WITH_RESPONES;
            break;
        case CEC_OPCODE_GIVE_PHYSICAL_ADDRESS:           //0X83
            HDMI_TEST_CEC_LOG("GIVE_PHYSICAL_ADDRESS, Response\n");
        {
#if 0 /*--NO MODIFY : COMMENT BY CODINGPARTNER--*/
            HI_U8 PhyAddr[4], LogAddr;
            HI_U32 Rec;
            Rec = DRV_HDMI_GetCECAddress(PhyAddr, &LogAddr);

            if(Rec != HI_SUCCESS)
            {
                break;
            }
#endif /*--NO MODIFY : COMMENT BY CODINGPARTNER--*/
            HDMI_TEST_CEC_LOG("return REPORT_PHYSICAL_ADDRESS\n");
            //we should send back a message of ACTIVE_SOURCE
            pCECCmdSet->u8Opcode   = CEC_OPCODE_REPORT_PHYSICAL_ADDRESS;
            pCECCmdSet->enDstAdd = Init;
            pCECCmdSet->unOperand.stRawData.u8Length          = 3;
            pCECCmdSet->unOperand.stRawData.u8Data[0]     = ((stCECStatus.u8PhysicalAddr[0] << 4) & 0xf0) | (stCECStatus.u8PhysicalAddr[1] & 0x0f); // [Physical Address(A.B.C.D):A B]
            pCECCmdSet->unOperand.stRawData.u8Data[1]     = ((stCECStatus.u8PhysicalAddr[2] << 4) & 0xf0) | (stCECStatus.u8PhysicalAddr[3] & 0x0f) ; // [Physical Address(A.B.C.D):C D]
            pCECCmdSet->unOperand.stRawData.u8Data[2]     = stCECStatus.u8LogicalAddr;
        }
            Ret = CEC_MESSAGE_RETURN_OK_WITH_RESPONES;
            break;
        case CEC_OPCODE_REPORT_PHYSICAL_ADDRESS:         //0X84
            HDMI_TEST_CEC_LOG("REPORT_PHYSICAL_ADDRESS\n");
            if(OperandLength != 3)
            {
                HDMI_TEST_CEC_LOG("Error oprand length:%d\n", OperandLength);
            }
            HDMI_TEST_CEC_LOG("PhysicalAddr:%01d.%01d.%01d.%01d, LogicalAddr:%d\n", (pOperand[0] & 0xf0) >> 4, (pOperand[0] & 0x0f), \
             (pOperand[1] & 0xf0) >> 4, (pOperand[1] & 0x0f), pOperand[2]);

            Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            break;
        case CEC_OPCODE_GET_MENU_LANGUAGE:               //0X91
            HDMI_TEST_CEC_LOG("GET_MENU_LANGUAGE, response\n");
            pCECCmdSet->u8Opcode   = CEC_OPCODE_SET_MENU_LANGUAGE;
            pCECCmdSet->enDstAdd   = Init;
            pCECCmdSet->unOperand.stRawData.u8Length          = 3;


#if 0 /*--use ISO 639-2/T--*/
            //In general the T codes are favored; ISO 639-3 uses ISO 639-2/T.
            //However, ISO 15924 derives its codes when possible from ISO 639-2/B.
            //Language: 3 ASCII Bytes as defined in ISO/FDIS 639-2
            //"terminological" code (ISO 639-2/T)
            pCECframe->bOperand[0]     = 'z';
            pCECframe->bOperand[1]     = 'h' ;
            pCECframe->bOperand[2]     = 'o' ;
#else /*-- use ISO 639-2/B--*/
            //In sumsung TV,we found it use ISO 639-2/B
            //Language: 3 ASCII Bytes as defined in ISO/FDIS 639-2
            //"bibliographic" code (ISO 639-2/B)
            pCECCmdSet->unOperand.stRawData.u8Data[0]     = 'c';
            pCECCmdSet->unOperand.stRawData.u8Data[1]     = 'h' ;
            pCECCmdSet->unOperand.stRawData.u8Data[2]     = 'i' ;
#endif

            Ret = CEC_MESSAGE_RETURN_OK_WITH_RESPONES;
            break;
        case CEC_OPCODE_SET_MENU_LANGUAGE:               //0X32
            HDMI_TEST_CEC_LOG("SET_MENU_LANGUAGE:");
            {
                int index;
                for(index = 0; index < OperandLength; index ++)
                {
                    if( ((pOperand[index] >= 'a') && (pOperand[index] <= 'z'))
                     || ((pOperand[index] >= 'A') && (pOperand[index] <= 'Z')) )
                    {
                        HDMI_TEST_CEC_LOG("%c", pOperand[index]);
                    }
                    else
                    {
                        HDMI_TEST_CEC_LOG("%02x", pOperand[index]);
                    }
                }
            }
            HDMI_TEST_CEC_LOG("\n");
            break;

        /*Deck Control Feature*/
        case CEC_OPCODE_DECK_CONTROL:                    //0X42
            HDMI_TEST_CEC_LOG("DECK_CONTROL\n");
            break;
        case CEC_OPCODE_DECK_STATUS:                     //0X1B
            HDMI_TEST_CEC_LOG("DECK_STATUS\n");
            break;
        case CEC_OPCODE_GIVE_DECK_STATUS:                //0X1A
            HDMI_TEST_CEC_LOG("GIVE_DECK_STATUS\n");
            break;
        case CEC_OPCODE_PLAY:                            //0X41
            HDMI_TEST_CEC_LOG("PLAY\n");
            break;

        /*Tuner Control Feature*/
        case CEC_OPCODE_GIVE_TUNER_DEVICE_STATUS:        //0X08
            break;
        case CEC_OPCODE_SELECT_ANALOGUE_SERVICE:         //0X92
            break;
        case CEC_OPCODE_SELECT_DIGITAL_SERVICE:          //0X93
            break;
        case CEC_OPCODE_TUNER_DEVICE_STATUS:             //0X07
            break;
        case CEC_OPCODE_TUNER_STEP_DECREMENT:            //0X06
            break;
        case CEC_OPCODE_TUNER_STEP_INCREMENT:            //0X05
            break;
        /*Vendor Specific Command*/
        case CEC_OPCODE_DEVICE_VENDOR_ID:                //0X87
            HDMI_TEST_CEC_LOG("DEVICE_VENDOR_ID:");
            {
                int index;
                for(index = 0; index < OperandLength; index ++)
                {
                    HDMI_TEST_CEC_LOG("%02x ", pOperand[index]);
                }
            }
            HDMI_TEST_CEC_LOG("\n");
            break;
        case CEC_OPCODE_GIVE_DEVICE_VENDOR_ID:           //0X8C
            HDMI_TEST_CEC_LOG("GIVE_DEVICE_VENDOR_ID, Response\n");
            pCECCmdSet->u8Opcode   = CEC_OPCODE_DEVICE_VENDOR_ID;
            pCECCmdSet->enDstAdd = 0x0f;
            pCECCmdSet->unOperand.stRawData.u8Length          = 3;
            pCECCmdSet->unOperand.stRawData.u8Data[0]     = 'h';
            pCECCmdSet->unOperand.stRawData.u8Data[1]     = 'i' ;
            pCECCmdSet->unOperand.stRawData.u8Data[2]     = 's' ;

            Ret = CEC_MESSAGE_RETURN_OK_WITH_RESPONES;
            break;
        case CEC_OPCODE_VENDOR_COMMAND:                  //0X89
            break;
        case CEC_OPCODE_VENDOR_COMMAND_WITH_ID:          //0XA0
            break;
        case CEC_OPCODE_VENDOR_REMOTE_BUTTON_DOWN:       //0X8A
            break;
        case CEC_OPCODE_VENDOR_REMOTE_BUTTON_UP:         //0X8B
            break;

        /*OSD Display Feature*/
        case CEC_OPCODE_SET_OSD_STRING:                  //0X64
            HDMI_TEST_CEC_LOG("SET_OSD_NAME:%s\n", pOperand);
            Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            break;
        case CEC_OPCODE_GIVE_OSD_NAME:                   //0X46
            HDMI_TEST_CEC_LOG("CEC_OPCODE_GIVE_OSD_NAME, Response\n");
            pCECCmdSet->u8Opcode   = CEC_OPCODE_SET_OSD_NAME;
            pCECCmdSet->enDstAdd = Init;
            pCECCmdSet->unOperand.stRawData.u8Length          = 3;
            pCECCmdSet->unOperand.stRawData.u8Data[0]     = 'h';
            pCECCmdSet->unOperand.stRawData.u8Data[1]     = 'i' ;
            pCECCmdSet->unOperand.stRawData.u8Data[2]     = 's' ;

            Ret = CEC_MESSAGE_RETURN_OK_WITH_RESPONES;
            break;
        case CEC_OPCODE_SET_OSD_NAME:                    //0X47
            HDMI_TEST_CEC_LOG("SET_OSD_NAME:");
            {
                int index;
                for(index = 0; index < OperandLength; index ++)
                {
                    if( ((pOperand[index] >= 'a') && (pOperand[index] <= 'z'))
                     || ((pOperand[index] >= 'A') && (pOperand[index] <= 'Z')) )
                    {
                        HDMI_TEST_CEC_LOG("%c", pOperand[index]);
                    }
                    else
                    {
                        HDMI_TEST_CEC_LOG("%02x", pOperand[index]);
                    }
                }
            }
            HDMI_TEST_CEC_LOG("\n");
            break;

        /*Device Menu Control Feature*/
        case CEC_OPCODE_MENU_REQUEST:                    //0X8D
            HDMI_TEST_CEC_LOG("MENU_REQUEST\n");
            if(OperandLength < 1)
            {
                HDMI_TEST_CEC_LOG("Invalid OperandLength:%d\n", OperandLength);
                break;
            }

            // Send back Menu STATUS
            pCECCmdSet->u8Opcode   = CEC_OPCODE_MENU_STATUS;
            pCECCmdSet->enDstAdd = Init;
            pCECCmdSet->unOperand.stRawData.u8Length          = 1;

            if(pOperand[0] == 0x00)
            {
                HDMI_TEST_CEC_LOG("Active\n");
                pCECCmdSet->unOperand.stRawData.u8Data[0]     = 0X00;//Active
            }
            else if(pOperand[0] == 0x01)
            {
                HDMI_TEST_CEC_LOG("Deactive\n");
                pCECCmdSet->unOperand.stRawData.u8Data[0]     = 0X01;//Deactive
            }
            else if(pOperand[0] == 0x02)
            {
                HDMI_TEST_CEC_LOG("Query\n");
            }
            else
            {
                HDMI_TEST_CEC_LOG("Unknown, pOperand[0]:0x%x\n", pOperand[0]);
                break;
            }

            Ret = CEC_MESSAGE_RETURN_OK_WITH_RESPONES;
            break;
        case CEC_OPCODE_MENU_STATUS:                     //0X8E
            HDMI_TEST_CEC_LOG("MENU_STATUS:\n");
            if(OperandLength < 1)
            {
                HDMI_TEST_CEC_LOG("Invalid OperandLength:%d\n", OperandLength);
                break;
            }
            if(pOperand[0] == 0x00)
            {
                HDMI_TEST_CEC_LOG("Active\n");
            }
            else if(pOperand[0] == 0x01)
            {
                HDMI_TEST_CEC_LOG("Deactive\n");
            }

            Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            break;
        case CEC_OPCODE_USER_CONTROL_PRESSED:            //0X44
            HDMI_TEST_CEC_LOG("USER_CONTROL_PRESSED\n");
            HDMI_TEST_CEC_LOG("Press RC:0x%02x\n", pOperand[0]);
            Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            break;
        case CEC_OPCODE_USER_CONTROL_RELEASED:           //0X45
            HDMI_TEST_CEC_LOG("USER_CONTROL_RELEASED\n");
            HDMI_TEST_CEC_LOG("Release RC:0x%02x\n", pOperand[0]);
            Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            break;

        /*Power Status Feature*/
        case CEC_OPCODE_GIVE_DEVICE_POWER_STATUS:        //0X8F
            HDMI_TEST_CEC_LOG("GIVE_DEVICE_POWER_STATUS, response\n");

            pCECCmdSet->u8Opcode   = CEC_OPCODE_REPORT_POWER_STATUS;
            pCECCmdSet->enDstAdd = Init;
            pCECCmdSet->unOperand.stRawData.u8Length      = 1;
            pCECCmdSet->unOperand.stRawData.u8Data[0]     = g_cecPowerStatus;//Power on

#if 0 /*--NO MODIFY : COMMENT BY CODINGPARTNER--*/
            if(g_cecPowerStatus < CEC_POWER_STATUS_ON2STANDBY)
            {
                g_cecPowerStatus++;
            }
#endif /*--NO MODIFY : COMMENT BY CODINGPARTNER--*/
            switch(g_cecPowerStatus)
            {
                case CEC_POWER_STATUS_ON:
                    //g_cecPowerStatus = CEC_POWER_STATUS_ON2STANDBY;
                    break;
                case CEC_POWER_STATUS_STANDBY:
                    g_cecPowerStatus = CEC_POWER_STATUS_STANDBY2ON;
                    break;
                case CEC_POWER_STATUS_STANDBY2ON:
                    g_cecPowerStatus = CEC_POWER_STATUS_ON;
                    break;
                case CEC_POWER_STATUS_ON2STANDBY:
                    g_cecPowerStatus = CEC_POWER_STATUS_STANDBY;
                    break;
                default:
                    HDMI_TEST_CEC_LOG("Unknown Power status \n");
            }

            Ret = CEC_MESSAGE_RETURN_OK_WITH_RESPONES;
            break;
        case CEC_OPCODE_REPORT_POWER_STATUS:             //0X90
            HDMI_TEST_CEC_LOG("REPORT_POWER_STATUS\n");
            if(OperandLength < 1)
            {
                HDMI_TEST_CEC_LOG("Invalid OperandLength:%d\n", OperandLength);
                break;
            }
            if(pOperand[0] == 0x00)
            {
                HDMI_TEST_CEC_LOG("Power On\n");
            }
            else if(pOperand[0] == 0x01)
            {
                HDMI_TEST_CEC_LOG("Stand By\n");
            }
            else
            {
                HDMI_TEST_CEC_LOG("Unknown, pOperand[0]:0x%x\n", pOperand[0]);
            }
            Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            break;

        /*System Audio Control Feature*/
        case CEC_OPCODE_GIVE_AUDIO_STATUS:               //0X71
            HDMI_TEST_CEC_LOG("GIVE_AUDIO_STATUS\n");
            break;
        case CEC_OPCODE_GIVE_SYSTEM_AUDIO_MODE_STATUS:   //0x7D
            break;
        case CEC_OPCODE_REPORT_AUDIO_STATUS:             //0X7A
            break;
        case CEC_OPCODE_SET_SYSTEM_AUDIO_MODE:           //0X72
            break;
        case CEC_OPCODE_SYSTEM_AUDIO_MODE_REQUEST:       //0X70
            break;
        case CEC_OPCODE_SYSTEM_AUDIO_MODE_STATUS:        //0X7E
            break;

        /*Audio Rate Control Feature*/
        case CEC_OPCODE_SET_AUDIO_RATE:                  //0X9A
            break;
        default:
            return 3;
    }
    return Ret;
}

/*
**  CEC callback
*/
HI_VOID HDMI_CEC_Proc(HI_UNF_HDMI_ID_E enHdmi, HI_UNF_HDMI_CEC_CMD_S *pstCECCmd, HI_VOID *pData)
{
    HI_UNF_HDMI_CEC_CMD_S stReplyCmd;
    int ret;

    HDMI_CEC_PrintCmd(pstCECCmd);
    memset(&stReplyCmd, 0, sizeof(HI_UNF_HDMI_CEC_CMD_S));

    ret = HDMI_CEC_MsgParse(pstCECCmd,&stReplyCmd);

    if(ret == CEC_MESSAGE_RETURN_OK_WITH_RESPONES)
    {
        HDMI_TEST_CEC_LOG("response \n");
        HI_UNF_HDMI_SetCECCommand(HI_UNF_HDMI_ID_0, &stReplyCmd);
        return ;
    }
    else if(ret == CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES)
    {
        HDMI_TEST_CEC_LOG("not need response \n");
        return ;//direct return!
    }
    else if(ret == CEC_MESSAGE_RETURN_ERROR_NOSUPPORT)
    {
        HDMI_TEST_CEC_LOG("unsupport cec cmd \n");
        //return ;
    }

    // Deal with Unsupport Message!    //
    // Do not reply to Broadcast msgs, otherwise send Feature Abort
    // for all unsupported features.
    if( (pstCECCmd->enSrcAdd & 0x0F) != 0x0F)
    {
        HI_U32 Rec;
        HI_UNF_HDMI_CEC_STATUS_S  stCECStatus;

        Rec = HI_UNF_HDMI_CECStatus(HI_UNF_HDMI_ID_0, &stCECStatus);
        if(Rec != HI_SUCCESS)
        {
            HDMI_TEST_CEC_LOG("Get CEC Status Fail! return \n");
            return ;
        }

        /*All devices shall support the message <Feature Abort>.
          It is used to allow devices to indicate if they do not support an opcode that has been
          sent to them, if it is unable to deal with this message.
          <Feature Abort> has 2 parameters: opcode and the reason of its reject of the frame.
          <Feature Abort> is used as a response to any failure!
        */
        // Unsupported opcode; send feature abort
        //<Feature Abort>has 2 parameters, the opcode and a reason for its rejection of the frame.
        memset(&stReplyCmd, 0, sizeof(HI_UNF_HDMI_CEC_CMD_S));
        stReplyCmd.u8Opcode = CEC_OPCODE_FEATURE_ABORT;//0x00;
        stReplyCmd.enSrcAdd = stCECStatus.u8LogicalAddr;// our logical Addr
        stReplyCmd.enDstAdd = pstCECCmd->enSrcAdd; //(sii_cec->bDestOrRXHeader & 0xf0) >> 4 ;
        stReplyCmd.unOperand.stRawData.u8Data[0]     = pstCECCmd->u8Opcode;
        stReplyCmd.unOperand.stRawData.u8Data[1]     = 0x00; //Unrecognized opcode:0x00
        stReplyCmd.unOperand.stRawData.u8Length = 2;

        HDMI_CEC_PrintCmd(&stReplyCmd);
        HI_UNF_HDMI_SetCECCommand(HI_UNF_HDMI_ID_0,&stReplyCmd);
        HDMI_TEST_CEC_LOG("\n!Unsupported bOpcode:0x%x Feature!\n", pstCECCmd->u8Opcode);
    }
    else
    {
        // Unsupported Broadcast Msg
        HDMI_TEST_CEC_LOG("\n! Unsupported Brocast Msg!\n");
    }

    return;
}

/*
**  CEC enable
*/
HI_S32 hdmi_test_cec_enable(HI_UNF_HDMI_ID_E enHdmi)
{
    HI_S32 s32Ret = 0;


    s32Ret |= HI_UNF_HDMI_RegCECCallBackFunc(HI_UNF_HDMI_ID_0, HDMI_CEC_Proc);

    s32Ret |= HI_UNF_HDMI_CEC_Enable(enHdmi);

    return s32Ret;
}

/*
**  CEC disable
*/
HI_S32 hdmi_test_cec_disable(HI_UNF_HDMI_ID_E enHdmi)
{
    HI_S32 s32Ret = 0;

    s32Ret |= HI_UNF_HDMI_UnRegCECCallBackFunc(HI_UNF_HDMI_ID_0, HDMI_CEC_Proc);
    s32Ret |= HI_UNF_HDMI_CEC_Disable(enHdmi);

    return s32Ret;
}

/*
**  Send CEC cmd
*/
HI_U32 hdmi_test_cec_setcmd(HI_UNF_HDMI_ID_E enHdmi, HDMI_TEST_CEC_CMD_S *pstCecCmd)
{
    HI_U32                   u32RetError = HI_SUCCESS;
    HI_UNF_HDMI_CEC_CMD_S    stCmd;
    HI_UNF_HDMI_CEC_STATUS_S stCecStatus;

    if(HI_NULL == pstCecCmd)
    {
        printf("input param is null!\n");
        return HI_FAILURE;
    }

    printf("CEC hdmi_cec_cmd, cmd: %d, destAddr:0x%x, u8Opcode:0x%x, Datalength:0x%x\n",
            pstCecCmd->enCmd, pstCecCmd->u8DestAddr, pstCecCmd->u8Opcode, pstCecCmd->u8Len);

    memset(&stCecStatus, 0, sizeof(HI_UNF_HDMI_CEC_STATUS_S));
    memset(&stCmd, 0, sizeof(HI_UNF_HDMI_CEC_CMD_S));

    HI_UNF_HDMI_CECStatus(enHdmi, &stCecStatus);
    if(HI_TRUE != stCecStatus.bEnable)
    {
        printf("CEC Line does not enable\n");
    }

    stCmd.enSrcAdd = stCecStatus.u8LogicalAddr;

    switch(pstCecCmd->enCmd)
    {
        case HDMI_TEST_CEC_STANDBY:
            stCmd.enDstAdd = 0x00;
            stCmd.u8Opcode = 0x36;
            break;
        case HDMI_TEST_CEC_IMAMGE_VIEW_ON:
            stCmd.enDstAdd = 0x00;
            stCmd.u8Opcode = 0x04;
            break;
        case HDMI_TEST_CEC_TEXT_VIEW_ON:
            stCmd.enDstAdd = 0x00;
            stCmd.u8Opcode = 0x0d;
            break;
        case HDMI_TEST_CEC_ACTIVE_SOURCE:
            stCmd.enDstAdd = 0x00;
            stCmd.u8Opcode = 0x04;  // image view on
            HI_UNF_HDMI_SetCECCommand(enHdmi, &stCmd);

            stCmd.enDstAdd = 0x0f;
            stCmd.u8Opcode = 0x82;  // active source
            stCmd.unOperand.stRawData.u8Length = 0x02;
            stCmd.unOperand.stRawData.u8Data[0] = (stCecStatus.u8PhysicalAddr[0] << 4) | stCecStatus.u8PhysicalAddr[1];
            stCmd.unOperand.stRawData.u8Data[1] = (stCecStatus.u8PhysicalAddr[2] << 4) | stCecStatus.u8PhysicalAddr[3];
            break;
        case HDMI_TEST_CEC_GET_CEC_VERSION:
            stCmd.enDstAdd = 0x00;
            stCmd.u8Opcode = 0x9f;
            break;
        case HDMI_TEST_CEC_GET_MENU_LAN:
            stCmd.enDstAdd = 0x00;
            stCmd.u8Opcode = 0x91;
            break;
        case HDMI_TEST_CEC_GET_PHY_ADDR:
            stCmd.enDstAdd = 0x00;
            stCmd.u8Opcode = 0x83;
            break;
        case HDMI_TEST_CEC_GET_DEV_VENDOR_ID:
            stCmd.enDstAdd = 0x00;
            stCmd.u8Opcode = 0x8c;
            break;
        case HDMI_TEST_CEC_GET_OSD_NAME:
            stCmd.enDstAdd = 0x00;
            stCmd.u8Opcode = 0x8c;
            break;
        case HDMI_TEST_CEC_SET_OSD_STRING:
            stCmd.enDstAdd = 0x00;
            stCmd.u8Opcode = 0x64;
            stCmd.unOperand.stRawData.u8Length = 0x03;
            stCmd.unOperand.stRawData.u8Data[0] = 0x65;
            stCmd.unOperand.stRawData.u8Data[1] = 0x66;
            stCmd.unOperand.stRawData.u8Data[2] = 0x67;
            break;
        case HDMI_TEST_CEC_GET_POWER_STATUS:
            stCmd.enDstAdd = 0x00;
            stCmd.u8Opcode = 0x8f;
            break;
        case HDMI_TEST_CEC_SET_VOLUME_UP:
            stCmd.enDstAdd = 0x00;
            stCmd.u8Opcode = 0x44;
            stCmd.unOperand.stRawData.u8Length = 0x01;
            stCmd.unOperand.stRawData.u8Data[0] = 0x41;
            break;
        case HDMI_TEST_CEC_SET_VOLUME_DOWN:
            stCmd.enDstAdd = 0x00;
            stCmd.u8Opcode = 0x44;
            stCmd.unOperand.stRawData.u8Length = 0x01;
            stCmd.unOperand.stRawData.u8Data[0] = 0x42;
            break;
        case HDMI_TEST_CEC_SET_VOLUME_MUTE:
            stCmd.enDstAdd = 0x00;
            stCmd.u8Opcode = 0x44;
            stCmd.unOperand.stRawData.u8Length = 0x01;
            stCmd.unOperand.stRawData.u8Data[0] = 0x43;
            break;
        case HDMI_TEST_CEC_USER_DEFINE:
            stCmd.enDstAdd = pstCecCmd->u8DestAddr;  // HI_UNF_CEC_LOGICALADD_TV;
            stCmd.u8Opcode = pstCecCmd->u8Opcode;
            stCmd.unOperand.stRawData.u8Length = pstCecCmd->u8Len;
            memcpy(&(stCmd.unOperand.stRawData.u8Data), pstCecCmd->u8Data, pstCecCmd->u8Len);
            break;
        default:
            printf("cmd error, do not support now!\n");
            u32RetError = HI_FAILURE;
            break;
    }

    if(HI_SUCCESS != u32RetError)
    {
        return u32RetError;
    }

    HI_UNF_HDMI_SetCECCommand(enHdmi, &stCmd);

    return u32RetError;
}

/*
**  CEC auto ping
*/
HI_S32 hdmi_test_cec_autoping(HI_UNF_HDMI_ID_E enHdmi)
{
    HI_U32                 u32RetError = HI_SUCCESS;
    HI_UNF_HDMI_CEC_CMD_S  CECCmd;

    printf("CEC Auto Ping\n");
    memset(&CECCmd, 0, sizeof(HI_UNF_HDMI_CEC_CMD_S));
    CECCmd.enSrcAdd = HI_UNF_CEC_LOGICALADD_TUNER_1;
    CECCmd.enDstAdd = HI_UNF_CEC_LOGICALADD_TV;
    CECCmd.u8Opcode = CEC_OPCODE_POLLING_MESSAGE;

    HI_UNF_HDMI_SetCECCommand(enHdmi, &CECCmd);

    return u32RetError;
}

