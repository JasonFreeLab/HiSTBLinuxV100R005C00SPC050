/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name       : df_keyboard.c
Version          :
Author           :
Created         : 2017/01/01
Description    : CNcomment:±ê×¼¼üÅÌ²Ù×÷CNend\n
Function List  :
History          :
Date                                   Author                            Modification
2017/01/01                  y00181162
******************************************************************************/


/*********************************add include here******************************/
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>


#include "hi_adp_gfx.h"


/***************************** Macro Definition ******************************/

#define DFBCHECK(x...) \
     {                                                                \
          err = x;                                                    \
          if (err != DFB_OK) {                                        \
               SAMPLE_TRACE("%s <%d>:\n\t", __FILE__, __LINE__ );     \
               DirectFBErrorFatal( #x, err );                         \
          }                                                           \
     }


#define KEY_MAX_NUM      127

/*************************** Structure Definition ****************************/
typedef struct
{
    HI_U32  KeyId;
    HI_CHAR pIdentifier[256];
}DFB_INPUT_IDENTIFIER_PRINT;


/********************** Global Variable declaration **************************/
IDirectFB               *dfb;
IDirectFBSurface        *primary;
IDirectFBInputDevice    *keyboard;
IDirectFBEventBuffer    *keybuffer;
IDirectFBImageProvider  *provider;
IDirectFBFont           *font;


DFB_INPUT_IDENTIFIER_PRINT gs_IdentifierArray[KEY_MAX_NUM] =
{
    {DIKI_UNKNOWN,  "DIKI_UNKNOWN"},/** 0xf600 **/
    {DIKI_A,        "DIKI_A"},  /** 0xf601 **/
    {DIKI_B,        "DIKI_B"},  /** 0xf602 **/
    {DIKI_C,        "DIKI_C"},  /** 0xf603 **/
    {DIKI_D,        "DIKI_D"},  /** 0xf604 **/
    {DIKI_E,        "DIKI_E"},  /** 0xf605 **/
    {DIKI_F,        "DIKI_F"},  /** 0xf606 **/
    {DIKI_G,        "DIKI_G"},  /** 0xf607 **/
    {DIKI_H,        "DIKI_H"},  /** 0xf608 **/
    {DIKI_I,        "DIKI_I"},  /** 0xf609 **/
    {DIKI_J,        "DIKI_J"},  /** 0xf60a **/
    {DIKI_K,        "DIKI_K"},  /** 0xf60b **/
    {DIKI_L,        "DIKI_L"},  /** 0xf60c **/
    {DIKI_M,        "DIKI_M"},  /** 0xf60d **/
    {DIKI_N,        "DIKI_N"},  /** 0xf60e **/
    {DIKI_O,        "DIKI_O"},  /** 0xf60f **/
    {DIKI_P,        "DIKI_P"},  /** 0xf610 **/
    {DIKI_Q,        "DIKI_Q"},  /** 0xf611 **/
    {DIKI_R,        "DIKI_R"},  /** 0xf612 **/
    {DIKI_S,        "DIKI_S"},  /** 0xf613 **/
    {DIKI_T,        "DIKI_T"},  /** 0xf614 **/
    {DIKI_U,        "DIKI_U"},  /** 0xf615 **/
    {DIKI_V,        "DIKI_V"},  /** 0xf616 **/
    {DIKI_W,        "DIKI_W"},  /** 0xf617 **/
    {DIKI_X,        "DIKI_X"},  /** 0xf618 **/
    {DIKI_Y,        "DIKI_Y"},  /** 0xf619 **/
    {DIKI_Z,        "DIKI_Z"},  /** 0xf61a **/

    {DIKI_0,        "DIKI_0"},  /** 0xf61b **/
    {DIKI_1,        "DIKI_1"},  /** 0xf61c **/
    {DIKI_2,        "DIKI_2"},  /** 0xf61d **/
    {DIKI_3,        "DIKI_3"},  /** 0xf61e **/
    {DIKI_4,        "DIKI_4"},  /** 0xf61f **/
    {DIKI_5,        "DIKI_5"},  /** 0xf620 **/
    {DIKI_6,        "DIKI_6"},  /** 0xf621 **/
    {DIKI_7,        "DIKI_7"},  /** 0xf622 **/
    {DIKI_8,        "DIKI_8"},  /** 0xf623 **/
    {DIKI_9,        "DIKI_9"},  /** 0xf624 **/

    {DIKI_F1,       "DIKI_F1"}, /** 0xf625 **/
    {DIKI_F2,       "DIKI_F2"}, /** 0xf626 **/
    {DIKI_F3,       "DIKI_F3"}, /** 0xf627 **/
    {DIKI_F4,       "DIKI_F4"}, /** 0xf628 **/
    {DIKI_F5,       "DIKI_F5"}, /** 0xf629 **/
    {DIKI_F6,       "DIKI_F6"}, /** 0xf62a **/
    {DIKI_F7,       "DIKI_F7"}, /** 0xf62b **/
    {DIKI_F8,       "DIKI_F8"}, /** 0xf62c **/
    {DIKI_F9,       "DIKI_F9"}, /** 0xf62d **/
    {DIKI_F10,      "DIKI_F10"},/** 0xf62e **/
    {DIKI_F11,      "DIKI_F11"},/** 0xf62f **/
    {DIKI_F12,      "DIKI_F12"},/** 0xf630 **/

    {DIKI_SHIFT_L,   "DIKI_SHIFT_L"},   /** 0xf631 **/
    {DIKI_SHIFT_R,   "DIKI_SHIFT_R"},   /** 0xf632 **/
    {DIKI_CONTROL_L, "DIKI_CONTROL_L"}, /** 0xf633 **/
    {DIKI_CONTROL_R, "DIKI_CONTROL_R"}, /** 0xf634 **/
    {DIKI_ALT_L,     "DIKI_ALT_L"},     /** 0xf635 **/
    {DIKI_ALT_R,     "DIKI_ALT_R"},     /** 0xf636 **/
    {DIKI_META_L,    "DIKI_META_L"},    /** 0xf637 **/
    {DIKI_META_R,    "DIKI_META_R"},    /** 0xf638 **/
    {DIKI_SUPER_L,   "DIKI_SUPER_L"},   /** 0xf639 **/
    {DIKI_SUPER_R,   "DIKI_SUPER_R"},   /** 0xf63a **/
    {DIKI_HYPER_L,   "DIKI_HYPER_L"},   /** 0xf63b **/
    {DIKI_HYPER_R,   "DIKI_HYPER_R"},   /** 0xf63c **/

    {DIKI_CAPS_LOCK,   "DIKI_CAPS_LOCK"}, /** 0xf63d **/
    {DIKI_NUM_LOCK,    "DIKI_NUM_LOCK"},  /** 0xf63e **/
    {DIKI_SCROLL_LOCK, "DIKI_SCROLL_LOCK"},/** 0xf63f **/

    {DIKI_ESCAPE,    "DIKI_ESCAPE"},    /** 0xf640 **/
    {DIKI_LEFT,      "DIKI_LEFT"},      /** 0xf641 **/
    {DIKI_RIGHT,     "DIKI_RIGHT"},     /** 0xf642 **/
    {DIKI_UP,        "DIKI_UP"},        /** 0xf643 **/
    {DIKI_DOWN,      "DIKI_DOWN"},      /** 0xf644 **/
    {DIKI_TAB,       "DIKI_TAB"},       /** 0xf645 **/
    {DIKI_ENTER,     "DIKI_ENTER"},     /** 0xf646 **/
    {DIKI_SPACE,     "DIKI_SPACE"},     /** 0xf647 **/
    {DIKI_BACKSPACE, "DIKI_BACKSPACE"}, /** 0xf648 **/
    {DIKI_INSERT,    "DIKI_INSERT"},    /** 0xf649 **/
    {DIKI_DELETE,    "DIKI_DELETE"},    /** 0xf64a **/
    {DIKI_HOME,      "DIKI_HOME"},      /** 0xf64b **/
    {DIKI_END,       "DIKI_END"},       /** 0xf64c **/
    {DIKI_PAGE_UP,   "DIKI_PAGE_UP"},   /** 0xf64d **/
    {DIKI_PAGE_DOWN, "DIKI_PAGE_DOWN"}, /** 0xf64e **/
    {DIKI_PRINT,     "DIKI_PRINT"},     /** 0xf64f **/
    {DIKI_PAUSE,     "DIKI_PAUSE"},     /** 0xf650 **/

    {DIKI_QUOTE_LEFT,   "DIKI_QUOTE_LEFT"},
    {DIKI_MINUS_SIGN,   "DIKI_MINUS_SIGN"},
    {DIKI_EQUALS_SIGN,  "DIKI_EQUALS_SIGN"},
    {DIKI_BRACKET_LEFT, "DIKI_BRACKET_LEFT"},
    {DIKI_BRACKET_RIGHT,"DIKI_BRACKET_RIGHT"},
    {DIKI_BACKSLASH,    "DIKI_BACKSLASH"},
    {DIKI_SEMICOLON,    "DIKI_SEMICOLON"},
    {DIKI_QUOTE_RIGHT,  "DIKI_QUOTE_RIGHT"},
    {DIKI_COMMA,        "DIKI_COMMA"},
    {DIKI_PERIOD,       "DIKI_PERIOD"},
    {DIKI_SLASH,        "DIKI_SLASH"},

    {DIKI_LESS_SIGN,    "DIKI_LESS_SIGN"},

    {DIKI_KP_DIV,       "DIKI_KP_DIV"},
    {DIKI_KP_MULT,      "DIKI_KP_MULT"},
    {DIKI_KP_MINUS,     "DIKI_KP_MINUS"},
    {DIKI_KP_PLUS,      "DIKI_KP_PLUS"},
    {DIKI_KP_ENTER,     "DIKI_KP_ENTER"},
    {DIKI_KP_SPACE,     "DIKI_KP_SPACE"},
    {DIKI_KP_TAB,       "DIKI_KP_TAB"},
    {DIKI_KP_F1,        "DIKI_KP_F1"},
    {DIKI_KP_F2,        "DIKI_KP_F2"},
    {DIKI_KP_F3,        "DIKI_KP_F3"},
    {DIKI_KP_F4,        "DIKI_KP_F4"},
    {DIKI_KP_EQUAL,     "DIKI_KP_EQUAL"},
    {DIKI_KP_SEPARATOR, "DIKI_KP_SEPARATOR"},

    {DIKI_KP_DECIMAL,   "DIKI_KP_DECIMAL"},
    {DIKI_KP_0,         "DIKI_KP_0"},
    {DIKI_KP_1,         "DIKI_KP_1"},
    {DIKI_KP_2,         "DIKI_KP_2"},
    {DIKI_KP_3,         "DIKI_KP_3"},
    {DIKI_KP_4,         "DIKI_KP_4"},
    {DIKI_KP_5,         "DIKI_KP_5"},
    {DIKI_KP_6,         "DIKI_KP_6"},
    {DIKI_KP_7,         "DIKI_KP_7"},
    {DIKI_KP_8,         "DIKI_KP_8"},
    {DIKI_KP_9,         "DIKI_KP_9"},

    {DIKI_KEYDEF_END,   "DIKI_KEYDEF_END"},
    {DIKI_NUMBER_OF_KEYS, "DIKI_NUMBER_OF_KEYS"},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {}
};


/******************************* API forward declarations *******************/
static HI_VOID PRINT_KeyIdentifier(HI_U32 KeyId);

/******************************* API realization *****************************/

int main( int argc, char *argv[] )
{

    DFBResult err;
    int quit = 0;

    DFBCHECK(DirectFBInit( &argc, &argv ));
    DFBCHECK(DirectFBCreate( &dfb ));

    DFBCHECK(dfb->GetInputDevice( dfb, DIDID_KEYBOARD, &keyboard ));
    DFBCHECK(keyboard->CreateEventBuffer( keyboard, &keybuffer ));

    DFBCHECK(dfb->SetCooperativeLevel( dfb, DFSCL_FULLSCREEN ));

    while (!quit)
    {
         DFBInputEvent evt;

         keybuffer->WaitForEvent( keybuffer );
         while (keybuffer->GetEvent( keybuffer, DFB_EVENT(&evt)) == DFB_OK)
         {
            SAMPLE_TRACE("\n==================================================================\n");
            if (evt.type == DIET_KEYPRESS)
            {
               quit = (evt.key_id == DIKI_ESCAPE) ? 1 : 0;
               SAMPLE_TRACE("key press\n");
               PRINT_KeyIdentifier(evt.key_id);
            }
            SAMPLE_TRACE("==================================================================\n");
         }
    }

    DFBCHECK(keybuffer->Release( keybuffer ));
    DFBCHECK(keyboard->Release( keyboard ));
    DFBCHECK(dfb->Release( dfb ));

    return 0;
}


static HI_VOID PRINT_KeyIdentifier(HI_U32 KeyId)
{
     HI_S32 Index = 0;

     for (Index = 0; Index < KEY_MAX_NUM; Index++)
     {
          if ( KeyId == gs_IdentifierArray[Index].KeyId)
          {
              SAMPLE_TRACE("key indentifier = %s key code = 0x%x\n",gs_IdentifierArray[Index].pIdentifier,gs_IdentifierArray[Index].KeyId);
              break;
          }
     }
     return;
}
