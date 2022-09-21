/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name       : df_lirc.c
Version          :
Author           :
Created         : 2017/01/01
Description    : CNcomment:遥控器红外操作CNend\n
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

#include <directfb_keynames.h>
#include <direct/util.h>

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
} DFB_INPUT_IDENTIFIER_PRINT;


typedef struct tatDeviceInfo DeviceInfo;

struct tatDeviceInfo
{
     DFBInputDeviceID           device_id;
     DFBInputDeviceDescription  desc;
     DeviceInfo *next;
};


/********************** Global Variable declaration **************************/

/**<  the super interface  **/
static IDirectFB *gs_dfb = NULL;

/**<  the primary surface (surface of primary layer)  **/
static IDirectFBSurface *gs_Primary = NULL;

/**<  fonts **/
static IDirectFBFont *gs_Font = NULL;

/**<   input interfaces: device and its buffer */
static IDirectFBEventBuffer *gs_Events = NULL;

/**<  display screen width and height */
static HI_S32 gs_ScreenWidth = 0;
static HI_S32 gs_ScreenHeight = 0;


static int gs_MousePosX, gs_MousePosY;
static int gs_MousePosXMin = -1, gs_MousePosYMin = -1;
static int gs_MousePosXMax = -1, gs_MousePosYMax = -1;
static int raxis = -1;
static int joy_axis[8];


static const DirectFBKeySymbolNames(keynames);
static const DirectFBKeyIdentifierNames(idnames);

/******************************* API forward declarations *******************/

static DFBEnumerationResult test_enum_input_device( DFBInputDeviceID device_id,DFBInputDeviceDescription desc,void *data);
static DFBInputDeviceTypeFlags test_get_device_type(DeviceInfo *devices, DFBInputDeviceID device_id);
static const HI_CHAR *test_get_device_name( DeviceInfo *devices, DFBInputDeviceID device_id);
static HI_VOID test_show_event(const HI_CHAR *device_name,DFBInputDeviceTypeFlags device_type,DFBInputEvent *evt);
static HI_VOID test_show_key_event(DFBInputEvent *evt);
static HI_S32 test_compare_symbol(const void *a, const void *b);
static HI_S32 test_compare_id(const void *a, const void *b);
static HI_VOID test_show_key_modifier_state(DFBInputEvent *evt);
static HI_VOID test_show_key_lock_state(DFBInputEvent *evt);
static HI_VOID test_show_mouse_event(DFBInputEvent *evt);
static HI_VOID test_show_mouse_buttons (DFBInputEvent *evt);
static HI_VOID test_show_any_button_event(DFBInputEvent *evt);
static HI_VOID test_show_any_axis_event(DFBInputEvent *evt);

static HI_VOID test_show_joystick_event(DFBInputEvent *evt);
static HI_VOID test_joystick_show_axisgroup(DFBRectangle *rect, int axis_x, int axis_y);
static inline HI_S32 test_joystick_calc_screenlocation(int screenres, int axisvalue);

/******************************* API realization *****************************/
int main( int argc, char *argv[] )
{
    DFBResult err;
    DFBSurfaceDescription SurfaceDsc;
    DFBFontDescription FontDsc;

    DeviceInfo *pDevices = NULL;
    DeviceInfo *pNextDevices = NULL;
    DFBInputDeviceTypeFlags DeviceType;
    DFBInputDeviceKeySymbol KeySymbol = DIKS_NULL;
    DFBInputEvent InputEvt;

    const HI_CHAR *pInputDeviceName = NULL;
    const HI_CHAR* FontFile = FONT;

    DFBCHECK(DirectFBInit( &argc, &argv ));

    /**< layer-bg-none */
    DFBCHECK(DirectFBSetOption ("bg-none", NULL));

    /**< create the super interface */
    DFBCHECK(DirectFBCreate(&gs_dfb));

    /**< set our cooperative level to DFSCL_FULLSCREEN for exclusive access to the primary layer */
    gs_dfb->SetCooperativeLevel(gs_dfb, DFSCL_FULLSCREEN );

    /**< get the primary surface, i.e. the surface of the primary layer we have exclusive access to */
    SurfaceDsc.flags = DSDESC_CAPS;
    SurfaceDsc.caps  = DSCAPS_PRIMARY | DSCAPS_DOUBLE;
    DFBCHECK(gs_dfb->CreateSurface( gs_dfb, &SurfaceDsc, &gs_Primary ));

    /**< get screen size */
    gs_Primary->GetSize( gs_Primary, &gs_ScreenWidth, &gs_ScreenHeight );
    gs_MousePosX = gs_ScreenWidth  / 2;
    gs_MousePosY = gs_ScreenHeight / 2;

    /**< create font handle */
    FontDsc.flags  = DFDESC_HEIGHT;
    FontDsc.height = gs_ScreenWidth / 30;
    DFBCHECK(gs_dfb->CreateFont(gs_dfb, FontFile, &FontDsc, &gs_Font));

    /**< clear screen */
    gs_Primary->Clear(gs_Primary, 0, 0, 0, 0 );
    /**< fresh layer to display */
    gs_Primary->Flip(gs_Primary, NULL, 0 );

    /**< draw log */
    gs_Primary->Clear(gs_Primary, 0, 0, 0, 0 );
    gs_Primary->SetFont(gs_Primary, gs_Font);
    gs_Primary->SetColor(gs_Primary, 0x60, 0x60, 0x60, 0xFF);
    gs_Primary->DrawString(gs_Primary, "<-- Press any key to continue -->", -1, 200, gs_ScreenHeight / 2 - 50, DSTF_LEFT);
    gs_Primary->Flip(gs_Primary, NULL, 0 );
    sleep(5);

    /**< create a list of input devices */
    gs_dfb->EnumInputDevices(gs_dfb, test_enum_input_device, &pDevices);

    /**< create an event buffer for all devices */
    DFBCHECK(gs_dfb->CreateInputEventBuffer(gs_dfb, DICAPS_ALL,DFB_FALSE, &gs_Events));

    /**< wait 1minutes, if not input event, exit */
    if (gs_Events->WaitForEventWithTimeout(gs_Events, 100, 0 ) == DFB_TIMEOUT)
    {
       gs_Primary->Clear(gs_Primary, 0, 0, 0, 0 );
       gs_Primary->DrawString(gs_Primary, "<-- Timed out, Not has any events input -->", -1, 200, gs_ScreenHeight/2, DSTF_LEFT);
       gs_Primary->Flip(gs_Primary, NULL, 0 );
       sleep(2);
       goto FINISH_EXIT;
    }

    /**< show event type, and show which keyvalue we has press down */
    while (1)
    {
        while (gs_Events->GetEvent(gs_Events, DFB_EVENT(&InputEvt)) == DFB_OK)
        {
             DeviceType = test_get_device_type(pDevices, InputEvt.device_id);
             pInputDeviceName = test_get_device_name(pDevices, InputEvt.device_id);

             gs_Primary->Clear( gs_Primary, 0, 0, 0, 0 );
             test_show_event(pInputDeviceName,DeviceType,&InputEvt);

             gs_Primary->Flip( gs_Primary, NULL, 0 );
        }

        if (InputEvt.type == DIET_KEYRELEASE)
        {
             if (   (KeySymbol == DIKS_ESCAPE || KeySymbol == DIKS_EXIT)
                 && (InputEvt.key_symbol == DIKS_ESCAPE || InputEvt.key_symbol == DIKS_EXIT))
             {
                  break;
             }

             KeySymbol = InputEvt.key_symbol;
        }

        gs_Events->WaitForEvent( gs_Events );
    }


FINISH_EXIT:

    while (pDevices)
    {
        pNextDevices = pDevices->next;
        free(pDevices);
        pDevices = pNextDevices;
     }

     gs_Font->Release(gs_Font);
     gs_Primary->Clear(gs_Primary, 0, 0, 0, 0);
     gs_Primary->Release(gs_Primary);
     gs_Events->Release(gs_Events);
     gs_dfb->Release(gs_dfb);

     return 0;
}


static DFBEnumerationResult test_enum_input_device(DFBInputDeviceID device_id,DFBInputDeviceDescription desc,void *data)
{
     DeviceInfo **devices = data;
     DeviceInfo  *device;

     device = malloc( sizeof(DeviceInfo) );

     device->device_id = device_id;
     device->desc      = desc;
     device->next      = *devices;

     *devices = device;

     return DFENUM_OK;
}

static DFBInputDeviceTypeFlags test_get_device_type(DeviceInfo *devices, DFBInputDeviceID device_id)
{
     while (devices)
     {
          if (devices->device_id == device_id)
          {
             return devices->desc.type;
          }

          devices = devices->next;
     }

     return DIDTF_NONE;
}


static const HI_CHAR *test_get_device_name( DeviceInfo *devices, DFBInputDeviceID device_id)
{
     while (devices)
     {
          if (devices->device_id == device_id)
          {
              return devices->desc.name;
          }

          devices = devices->next;
     }

     return "<unknown>";
}


static HI_VOID test_show_event(const HI_CHAR *device_name,DFBInputDeviceTypeFlags device_type,DFBInputEvent *evt)
{
     HI_CHAR buf[256] = {'\0'};

     /**< evt->device_id is key identifiers (for basic mapping) */
     snprintf(buf, sizeof(buf), "%s --> device id %d", device_name, evt->device_id);

     gs_Primary->SetFont(gs_Primary, gs_Font);
     gs_Primary->SetColor(gs_Primary, 0x20, 0x20, 0x20, 0xFF);
     gs_Primary->DrawString(gs_Primary, buf, -1, 50, 50, DSTF_TOP);

     switch (evt->type)
     {
          /**< show lir bluetooth board */
          case DIET_KEYPRESS:
          case DIET_KEYRELEASE:
               test_show_key_event(evt);
               break;
          /**< show mouse. joystick */
          case DIET_BUTTONPRESS:
          case DIET_BUTTONRELEASE:
          case DIET_AXISMOTION:
               if (device_type & DIDTF_MOUSE )
               {
                  test_show_mouse_event( evt );
               }
               else if (device_type & DIDTF_JOYSTICK)
               {
                   test_show_joystick_event(evt);
               }
               else
               {
                    if (evt->type == DIET_BUTTONPRESS || evt->type == DIET_BUTTONRELEASE)
                    {
                        test_show_any_button_event(evt);
                    }
                    else
                    {
                        test_show_any_axis_event(evt);
                    }
               }
               break;

          default:
               break;
     }
}


/*****************************************************************************
* func             : test_show_key_event
* description   : CNcomment: lirc and bluetooth and board CNend\n
                         CNcomment: 遥控红外、蓝牙、键盘事件CNend\n
* param[in]    : evt
* retval          : NA
* others:       : NA
*****************************************************************************/
static HI_VOID test_show_key_event(DFBInputEvent *evt)
{
     static DFBInputDeviceKeyIdentifier last_id = DIKI_UNKNOWN;
     static int count   = 0;

     char buf[16];
     struct DFBKeySymbolName *symbol_name;
     struct DFBKeyIdentifierName  *id_name;

     if (DFB_KEY_TYPE(evt->key_symbol) == DIKT_UNICODE)
     {
          gs_Primary->SetFont(gs_Primary, gs_Font );
          gs_Primary->SetColor(gs_Primary, 0x70, 0x80, 0xE0, 0xFF );
          gs_Primary->DrawGlyph(gs_Primary, evt->key_symbol,gs_ScreenWidth/2, gs_ScreenHeight/2,DSTF_CENTER);
     }

     symbol_name = bsearch(&evt->key_symbol, keynames,sizeof(keynames) / sizeof(keynames[0]) - 1,sizeof(keynames[0]), test_compare_symbol);


     gs_Primary->SetFont(gs_Primary, gs_Font);
     if (symbol_name)
     {
          gs_Primary->SetColor(gs_Primary, 0xF0, 0xC0, 0x30, 0xFF );
          gs_Primary->DrawString(gs_Primary, symbol_name->name, -1,40, gs_ScreenHeight/3, DSTF_LEFT);
     }

     gs_Primary->SetColor(gs_Primary, 0x60, 0x60, 0x60, 0xFF);
     snprintf(buf, sizeof(buf), "0x%X", evt->key_symbol);
     gs_Primary->DrawString(gs_Primary, buf, -1,gs_ScreenWidth - 40, gs_ScreenHeight/3,DSTF_RIGHT);


     gs_Primary->SetFont(gs_Primary, gs_Font);
     gs_Primary->SetColor(gs_Primary, 0x80, 0x80, 0x80, 0xFF);
     snprintf (buf, sizeof(buf), "%d", evt->key_code);
     gs_Primary->DrawString(gs_Primary, buf, -1,gs_ScreenWidth - 40, gs_ScreenHeight/4,DSTF_RIGHT );


     gs_Primary->SetFont(gs_Primary, gs_Font);
     id_name = bsearch(&evt->key_id, idnames,sizeof(idnames) / sizeof(idnames[0]) - 1,sizeof(idnames[0]), test_compare_id );
     if (id_name)
     {
          gs_Primary->SetColor(gs_Primary, 0x60, 0x60, 0x60, 0xFF);
          gs_Primary->DrawString(gs_Primary, id_name->name, -1,40, 2 * gs_ScreenHeight/3, DSTF_LEFT );
     }

     test_show_key_modifier_state( evt );
     test_show_key_lock_state( evt );

     if (evt->type == DIET_KEYPRESS)
      {
          if (evt->key_id != DIKI_UNKNOWN && evt->key_id == last_id)
          {
             count++;
          }
          else
          {
               count = 0;
          }
          last_id = evt->key_id;
     }
     else
     {
          count = 0;
          last_id = DIKI_UNKNOWN;
     }


     gs_Primary->SetColor( gs_Primary, 0x60, 0x60, 0x60, 0xFF );

     if (count > 0)
     {
          snprintf(buf, sizeof(buf), "%dx PRESS", count + 1);
          gs_Primary->DrawString(gs_Primary, buf, -1,gs_ScreenWidth - 40, 2 * gs_ScreenHeight/3,DSTF_RIGHT );
     }
     else
     {
          gs_Primary->DrawString(gs_Primary, (evt->type == DIET_KEYPRESS) ? "PRESS" : "RELEASE", -1,gs_ScreenWidth - 40, 2 * gs_ScreenHeight/3,DSTF_RIGHT);

     }

     if (evt->key_symbol == DIKS_ESCAPE || evt->key_symbol == DIKS_EXIT)
     {
          gs_Primary->SetFont(gs_Primary, gs_Font);
          gs_Primary->SetColor(gs_Primary, 0xF0, 0xC0, 0x30, 0xFF);
          gs_Primary->DrawString(gs_Primary, "Press ESC/EXIT again to quit", -1,gs_ScreenWidth/2, gs_ScreenHeight/6,DSTF_CENTER );
     }
}


static HI_S32 test_compare_symbol(const void *a, const void *b)
{
     DFBInputDeviceKeySymbol *symbol  = (DFBInputDeviceKeySymbol *) a;
     struct DFBKeySymbolName *symname = (struct DFBKeySymbolName *) b;

     return *symbol - symname->symbol;
}

static HI_S32 test_compare_id(const void *a, const void *b)
{
     DFBInputDeviceKeyIdentifier *id     = (DFBInputDeviceKeyIdentifier *) a;
     struct DFBKeyIdentifierName *idname = (struct DFBKeyIdentifierName *) b;

     return *id - idname->identifier;
}

static HI_VOID test_show_key_modifier_state(DFBInputEvent *evt)
{
     static struct {
          DFBInputDeviceModifierMask  modifier;
          const char                 *name;
          int                         x;
     } modifiers[] = {
          { DIMM_SHIFT,   "Shift", 0 },
          { DIMM_CONTROL, "Ctrl",  0 },
          { DIMM_ALT,     "Alt",   0 },
          { DIMM_ALTGR,   "AltGr", 0 },
          { DIMM_META,    "Meta",  0 },
          { DIMM_SUPER,   "Super", 0 },
          { DIMM_HYPER,   "Hyper", 0 }
     };
     static int n_modifiers = sizeof(modifiers) / sizeof(modifiers[0]);
     static int y           = 0;

     int i;

     if (!(evt->flags & DIEF_MODIFIERS))
          return;

     if (!y) {
          y = 2 * gs_ScreenHeight / 3 + 20;

          modifiers[0].x = 40;
          for (i = 0; i < n_modifiers - 1; i++) {
               int w;

               gs_Font->GetStringWidth (gs_Font,
                                            modifiers[i].name, -1, &w);
               modifiers[i+1].x = modifiers[i].x + w + 20;
          }
     }

     gs_Primary->SetFont( gs_Primary, gs_Font );

     for (i = 0; i < n_modifiers; i++) {
          if (evt->modifiers & modifiers[i].modifier)
               gs_Primary->SetColor( gs_Primary, 0x90, 0x30, 0x90, 0xFF );
          else
               gs_Primary->SetColor( gs_Primary, 0x20, 0x20, 0x20, 0xFF );

          gs_Primary->DrawString( gs_Primary, modifiers[i].name, -1,
                               modifiers[i].x, y, DSTF_TOPLEFT );
     }
}

static HI_VOID test_show_key_lock_state(DFBInputEvent *evt)
{
     static struct {
          DFBInputDeviceLockState  lock;
          const char              *name;
          int                      x;
     } locks[] = {
          { DILS_SCROLL, "ScrollLock", 0 },
          { DILS_NUM,    "NumLock",    0 },
          { DILS_CAPS,   "CapsLock",   0 },
     };
     static int n_locks = sizeof(locks) / sizeof(locks[0]);
     static int y       = 0;

     int i;

     if (!(evt->flags & DIEF_LOCKS))
          return;

     if (!y) {
          int w;

          y = gs_ScreenHeight - 40;

          gs_Font->GetStringWidth (gs_Font,
                                       locks[n_locks-1].name, -1, &w);
          locks[n_locks-1].x = gs_ScreenWidth - 40 - w;

          for (i = n_locks - 1; i > 0; i--) {
               int w;

               gs_Font->GetStringWidth (gs_Font,
                                            locks[i-1].name, -1, &w);
               locks[i-1].x = locks[i].x - w - 20;
          }
     }

     gs_Primary->SetFont( gs_Primary, gs_Font );

     for (i = 0; i < n_locks; i++) {
          if (evt->locks & locks[i].lock)
               gs_Primary->SetColor( gs_Primary, 0x90, 0x30, 0x90, 0xFF );
          else
               gs_Primary->SetColor( gs_Primary, 0x20, 0x20, 0x20, 0xFF );

          gs_Primary->DrawString( gs_Primary, locks[i].name, -1,
                               locks[i].x, y, DSTF_LEFT );
     }
}


/*****************************************************************************
* func             : test_show_mouse_event
* description   : CNcomment: mouse CNend\n
                         CNcomment: 鼠标时间应用CNend\n
* param[in]    : evt
* retval          : NA
* others:       : NA
*****************************************************************************/
static HI_VOID test_show_mouse_event(DFBInputEvent *evt)
{
     char buf[32];
     static int AdjustedMousePosX = 0;
     static int AdjustedMousePosY = 0;

     gs_Primary->SetFont(gs_Primary, gs_Font);

     test_show_mouse_buttons( evt );

     *buf = 0;

     if (evt->type == DIET_AXISMOTION)
     {
          if (evt->flags & DIEF_AXISABS)
          {
               switch (evt->axis)
               {
                   case DIAI_X:
                        gs_MousePosX = evt->axisabs;
    		            gs_MousePosXMin = evt->min;
    		            gs_MousePosXMax = evt->max;
                        break;
                   case DIAI_Y:
                        gs_MousePosY = evt->axisabs;
    		            gs_MousePosYMin = evt->min;
    		            gs_MousePosYMax = evt->max;
                        break;
                   case DIAI_Z:
                        snprintf(buf, sizeof(buf), "Z axis (abs): %d", evt->axisabs);
    	                break;
                   default:
                        snprintf(buf, sizeof(buf),"Axis %d (abs): %d", evt->axis, evt->axisabs);
                        break;
               }
    	       raxis = 0;
          }
          else if (evt->flags & DIEF_AXISREL)
           {
               switch (evt->axis)
               {
                  case DIAI_X:
    	               gs_MousePosX += evt->axisrel;
                       break;
                  case DIAI_Y:
                       gs_MousePosY += evt->axisrel;
                       break;
                  case DIAI_Z:
                       snprintf(buf, sizeof(buf),"Z axis (rel): %d", evt->axisrel);
   	            break;
                  default:
                       snprintf(buf, sizeof(buf),"Axis %d (rel): %d", evt->axis, evt->axisrel);
                       break;
               }
	           raxis = 1;
          }

          /* Touchpad axis range may not be the same as screen size */
	      if ((gs_MousePosYMin < gs_MousePosYMax) && (gs_MousePosXMin < gs_MousePosXMax))
          {
    	       AdjustedMousePosX = CLAMP (gs_MousePosX, 0, gs_MousePosXMax);
    	       AdjustedMousePosY = CLAMP (gs_MousePosY, 0, gs_MousePosYMax);
    	       AdjustedMousePosX = ((gs_ScreenWidth  - 1) * AdjustedMousePosX) / gs_MousePosXMax;
    	       AdjustedMousePosY = ((gs_ScreenHeight - 1) * AdjustedMousePosY) / gs_MousePosYMax;
          }
          else
          {
               AdjustedMousePosX = CLAMP (gs_MousePosX, 0, gs_ScreenWidth  - 1);
               AdjustedMousePosY = CLAMP (gs_MousePosY, 0, gs_ScreenHeight - 1);
          }
     }
     else
     {  /* BUTTON_PRESS or BUTTON_RELEASE */
          snprintf (buf, sizeof(buf), "Button %d", evt->button);
     }

     if (*buf)
     {
          gs_Primary->SetColor(gs_Primary, 0xF0, 0xC0, 0x30, 0xFF );
          gs_Primary->DrawString(gs_Primary, buf, -1,40, gs_ScreenHeight - 40, DSTF_LEFT );
     }

     gs_Primary->SetColor(gs_Primary, 0x70, 0x80, 0xE0, 0xFF );
     gs_Primary->FillRectangle(gs_Primary, AdjustedMousePosX, 0, 1, gs_ScreenHeight );
     gs_Primary->FillRectangle(gs_Primary, 0, AdjustedMousePosY, gs_ScreenWidth, 1 );
}


static HI_VOID test_show_mouse_buttons (DFBInputEvent *evt)
{
     static struct {
          DFBInputDeviceButtonMask  mask;
          const char               *name;
          int                       x;
     } buttons[] = {
          { DIBM_LEFT,   "Left",   0 },
          { DIBM_MIDDLE, "Middle", 0 },
          { DIBM_RIGHT,  "Right",  0 },
     };
     static int n_buttons = sizeof(buttons) / sizeof(buttons[0]);
     static int y         = 0;
     static char str[64];
     int width;

     int i;

     if (!y)
     {
          int w;

          y = gs_ScreenHeight - 40;

          gs_Font->GetStringWidth(gs_Font,buttons[n_buttons-1].name, -1, &w);
          buttons[n_buttons-1].x = gs_ScreenWidth - 40 - w;

          for (i = n_buttons-1; i > 0; i--)
          {
               gs_Font->GetStringWidth(gs_Font,buttons[i-1].name, -1, &w);
               buttons[i-1].x = buttons[i].x - w - 20;
          }
     }

     for (i = 0; i < n_buttons; i++)
      {
          if (evt->flags & DIEF_BUTTONS && evt->buttons & buttons[i].mask)
          {
               gs_Primary->SetColor(gs_Primary, 0x90, 0x30, 0x90, 0xFF );
          }
          else
          {
               gs_Primary->SetColor(gs_Primary, 0x20, 0x20, 0x20, 0xFF );
          }

          gs_Primary->DrawString(gs_Primary, buttons[i].name, -1,buttons[i].x, y, DSTF_LEFT );
     }

     if (gs_MousePosXMax > 0 || gs_MousePosYMax > 0)
     {
          snprintf( str, sizeof(str), "(%d/%d,%d/%d)",gs_MousePosX, gs_MousePosXMax, gs_MousePosY, gs_MousePosYMax);
     }
     else
     {
          snprintf( str, sizeof(str), "(%d,%d)",gs_MousePosX, gs_MousePosY);
     }

     gs_Primary->SetFont(gs_Primary, gs_Font);
     gs_Font->GetStringWidth(gs_Font, str, -1, &width );
     gs_Primary->SetColor(gs_Primary, 0xF0, 0xF0, 0xF0, 0xFF );
     gs_Primary->DrawString(gs_Primary, str, -1,gs_ScreenWidth - 40 - width, y + 32, DSTF_LEFT);
     gs_Primary->SetFont(gs_Primary, gs_Font);
}



static HI_VOID test_show_any_button_event(DFBInputEvent *evt)
{
     char buf[40];

     gs_Primary->SetFont(gs_Primary, gs_Font);

     snprintf(buf, sizeof(buf), "Button %d %s", evt->button,(evt->type == DIET_BUTTONPRESS) ? "pressed" : "released");

     gs_Primary->SetColor(gs_Primary, 0xF0, 0xC0, 0x30, 0xFF );
     gs_Primary->DrawString(gs_Primary, buf, -1,40, gs_ScreenHeight - 40, DSTF_LEFT );
}

static HI_VOID test_show_any_axis_event(DFBInputEvent *evt)
{
     char buf[32];

     gs_Primary->SetFont(gs_Primary, gs_Font);

     if (evt->flags & DIEF_AXISABS)
     {
          snprintf(buf, sizeof(buf),"Axis %d (abs): %d", evt->axis, evt->axisabs);
     }
     else
     {
          snprintf(buf, sizeof(buf),"Axis %d (rel): %d", evt->axis, evt->axisrel);
     }

     gs_Primary->SetColor(gs_Primary, 0xF0, 0xC0, 0x30, 0xFF);
     gs_Primary->DrawString(gs_Primary, buf, -1,40, gs_ScreenHeight - 40, DSTF_LEFT);
}


static HI_VOID test_show_joystick_event( DFBInputEvent *evt )
{
     char buf[32];

     DFBRectangle rect;

     gs_Primary->SetFont(gs_Primary, gs_Font);

     *buf = 0;

     if ((evt->type == DIET_AXISMOTION) && (evt->axis < 8))
     {
          if (evt->flags & DIEF_AXISABS)
          {
               joy_axis[evt->axis] = evt->axisabs;
          }
          else if (evt->flags & DIEF_AXISREL)
          {
               joy_axis[evt->axis] += evt->axisrel;
          }
     }
     else
     {  /* BUTTON_PRESS or BUTTON_RELEASE */
          snprintf(buf, sizeof(buf), "Button %d", evt->button);
     }

     if (*buf)
     {
          gs_Primary->SetColor(gs_Primary, 0xF0, 0xC0, 0x30, 0xFF);
          gs_Primary->DrawString(gs_Primary, buf, -1,40, gs_ScreenHeight - 40, DSTF_LEFT);
     }

     rect.x = 0;
     rect.y = 0;
     rect.w = gs_ScreenWidth/2 - 10;
     rect.h = gs_ScreenHeight/2 - 10;
     test_joystick_show_axisgroup(&rect, joy_axis[0], joy_axis[1]);

     rect.x+= gs_ScreenWidth/2;
     test_joystick_show_axisgroup(&rect, joy_axis[2], joy_axis[3]);

     rect.y+= gs_ScreenWidth/2;
     test_joystick_show_axisgroup(&rect, joy_axis[4], joy_axis[5]);
}

static HI_VOID test_joystick_show_axisgroup(DFBRectangle *rect, int axis_x, int axis_y)
{
     int screen_x;
     int screen_y;

     screen_x = test_joystick_calc_screenlocation( rect->w, axis_x );
     screen_y = test_joystick_calc_screenlocation( rect->h, axis_y );

     gs_Primary->SetColor(gs_Primary, 0x80, 0x80, 0x80, 0xFF);
     gs_Primary->DrawRectangle(gs_Primary, rect->x, rect->y, rect->w, rect->h);

     gs_Primary->SetColor(gs_Primary, 0x00, 0x00, 0xFF, 0xFF);
     gs_Primary->DrawLine(gs_Primary, screen_x+rect->x, rect->y,screen_x+rect->x, rect->y + rect->h-1);
     gs_Primary->DrawLine(gs_Primary, rect->x, screen_y + rect->y,rect->x + rect->w-1, screen_y + rect->y);
}


static inline HI_S32 test_joystick_calc_screenlocation(int screenres, int axisvalue)
{
     return ((axisvalue + 32768)/65535.0f) * (screenres - 1);
}
