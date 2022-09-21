/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name       : keyboard.c
Version          :
Author           :
Created         : 2017/01/03
Description    : CNcomment:¼üÅÌ²Ù×÷CNend\n
Function List  :
History          :
Date                                   Author                            Modification
2017/01/03                  sdk
******************************************************************************/


/*********************************add include here******************************/
#include <config.h>
#include <asm/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/kd.h>
#include <sys/vt.h>
#include <errno.h>
#include <linux/keyboard.h>
#include <linux/input.h>
#include <termios.h>
#include <directfb.h>
#include <core/coredefs.h>
#include <core/coretypes.h>
#include <core/input.h>
#include <core/system.h>
#include <misc/conf.h>
#include <direct/debug.h>
#include <direct/mem.h>
#include <direct/messages.h>
#include <direct/thread.h>
#include <core/input_driver.h>

#include "fbdev.h"
#include "fb.h"
#include "hi_type.h"


/***************************** Macro Definition ******************************/
#define KEYBOARD_MAX_NUM 127


DFB_INPUT_DRIVER( keyboard )


/*************************** Structure Definition ****************************/
typedef enum tagKEYBOARD_CODE_NUM_E
{

    KEYBOARD_CODE_ESC       = 1,
    KEYBOARD_CODE_BACKSPACE = 14,
    KEYBOARD_CODE_ENTER     = 28,
    KEYBOARD_CODE_SPACE     = 57,

    /**< F1 ~ F10 **/
    KEYBOARD_CODE_F1     = 59,
    KEYBOARD_CODE_F2     = 60,
    KEYBOARD_CODE_F3     = 61,
    KEYBOARD_CODE_F4     = 62,
    KEYBOARD_CODE_F5     = 63,
    KEYBOARD_CODE_F6     = 64,
    KEYBOARD_CODE_F7     = 65,
    KEYBOARD_CODE_F8     = 66,
    KEYBOARD_CODE_F9     = 67,
    KEYBOARD_CODE_F10    = 68,

    /**< F11 ~ F12 **/
    KEYBOARD_CODE_F11    = 87,
    KEYBOARD_CODE_F12    = 88,

    KEYBOARD_CODE_HOME   = 102,
    KEYBOARD_CODE_UP     = 103,
    KEYBOARD_CODE_PGUP   = 104,
    KEYBOARD_CODE_LEFT   = 105,
    KEYBOARD_CODE_RIGHT  = 106,
    KEYBOARD_CODE_END    = 107,
    KEYBOARD_CODE_DOWN   = 108,
    KEYBOARD_CODE_PGDOWN = 109,

    KEYBOARD_CODE_INSERT = 110,
    KEYBOARD_CODE_DELETE = 111,

    KEYBOARD_CODE_BUTT
}KEYBOARD_CODE_NUM_E;


typedef struct
{
     HI_S32 Code;
     DFBInputDeviceKeyIdentifier enIdentifier;
     DFBInputDeviceKeySymbol     enSymbols;
} KEYBOARD_CODE_MAP_ENTRY;


KEYBOARD_CODE_MAP_ENTRY g_stKeyBoardArray[KEYBOARD_MAX_NUM] =
{
	{KEYBOARD_CODE_ESC,         DIKI_ESCAPE,          DIKS_BACK},
	{KEYBOARD_CODE_BACKSPACE,   DIKI_BACKSPACE,       DIKS_BACKSPACE},
	{KEYBOARD_CODE_ENTER,       DIKI_ENTER,           DIKS_OK},
	{KEYBOARD_CODE_SPACE,       DIKI_SPACE,           DIKS_SPACE},
    {KEYBOARD_CODE_F1,          DIKI_F1,              DIKS_F1},
    {KEYBOARD_CODE_F2,          DIKI_F2,              DIKS_F2},
    {KEYBOARD_CODE_F3,          DIKI_F3,              DIKS_F3},
    {KEYBOARD_CODE_F4,          DIKI_F4,              DIKS_F4},
	{KEYBOARD_CODE_F5,          DIKI_F5,              DIKS_F5},
	{KEYBOARD_CODE_F6,          DIKI_F6,              DIKS_F6},
    {KEYBOARD_CODE_F7,          DIKI_F7,              DIKS_F7},
    {KEYBOARD_CODE_F8,          DIKI_F8,              DIKS_F8},
    {KEYBOARD_CODE_F9,          DIKI_F9,              DIKS_F9},
    {KEYBOARD_CODE_F10,         DIKI_F10,             DIKS_F10},
    {KEYBOARD_CODE_F11,         DIKI_F11,             DIKS_F11},
    {KEYBOARD_CODE_F12,         DIKI_F12,             DIKS_F12},
    {KEYBOARD_CODE_HOME,        DIKI_HOME,            DIKS_COLON},
    {KEYBOARD_CODE_UP,          DIKI_UP,              DIKS_CURSOR_UP},
	{KEYBOARD_CODE_PGUP,        DIKI_PAGE_UP,         DIKS_PAGE_UP},
	{KEYBOARD_CODE_LEFT,        DIKI_LEFT,            DIKS_CURSOR_LEFT},
    {KEYBOARD_CODE_RIGHT,       DIKI_RIGHT,           DIKS_CURSOR_RIGHT},
    {KEYBOARD_CODE_END,         DIKI_END,             DIKS_END},
    {KEYBOARD_CODE_DOWN,        DIKI_DOWN,            DIKS_CURSOR_DOWN},
    {KEYBOARD_CODE_PGDOWN,      DIKI_PAGE_DOWN,       DIKS_PAGE_DOWN},
    {KEYBOARD_CODE_INSERT,      DIKI_INSERT,          DIKS_INSERT},
    {KEYBOARD_CODE_DELETE,      DIKI_DELETE,          DIKS_DELETE},
    {},
    {},
	{},
	{},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
	{},
	{},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
	{},
	{},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
	{},
	{},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
	{},
	{},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
	{},
	{},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
	{},
	{},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
	{},
	{},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
	{},
	{},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
	{},
	{},
    {},
    {},
    {},
    {},
    {},
    {},
    {}
};


typedef struct {
     CoreInputDevice *device;
     DirectThread    *thread;

     struct termios   old_ts;

     int              vt_fd;
} KeyboardData;



/********************** Global Variable declaration **************************/


/******************************* API forward declarations *******************/


/******************************* API realization *****************************/
static HI_S32 keymap_entry(HI_S32 Code, DFBInputDeviceKeyIdentifier *penIdentifier, DFBInputDeviceKeySymbol *penSymbol)
{
	HI_S32 KeyBoardNumIndex = 0;

	for (KeyBoardNumIndex = 0; KeyBoardNumIndex < KEYBOARD_MAX_NUM; KeyBoardNumIndex++)
	{
		if (Code == g_stKeyBoardArray[KeyBoardNumIndex].Code)
		{
			*penIdentifier = g_stKeyBoardArray[KeyBoardNumIndex].enIdentifier;
			*penSymbol     = g_stKeyBoardArray[KeyBoardNumIndex].enSymbols;
			return HI_SUCCESS;
		}
	}

	return HI_FAILURE;
}



static void
keyboard_set_lights( KeyboardData *data, DFBInputDeviceLockState locks )
{
     ioctl( data->vt_fd, KDSKBLED, locks );
}


static void* keyboardEventThread( DirectThread *thread, void *driver_data)
{
     int readlen;
     struct input_event event[64];
     KeyboardData  *data = (KeyboardData*) driver_data;

     /* Read keyboard data */
     while ((readlen = read (data->vt_fd, event, sizeof(struct input_event) * 64)) >= 0 || errno == EINTR)
     {
          int i;

          direct_thread_testcancel( thread );

          if (readlen < (int) sizeof(struct input_event))
          {
			 continue;
		  }

          for (i = 0; i < readlen / sizeof(struct input_event); i++)
          {

                DFBInputEvent evt;

                if (event[i].type == EV_SYN)
                {
    			}
                else if (event[i].type == EV_MSC && (event[i].code == MSC_RAW || event[i].code == MSC_SCAN))
                {
    			}
                else
                {
                   evt.type  = (1 == event[i].value) ? (DIET_KEYPRESS) : (DIET_KEYRELEASE);

                   evt.flags = DIEF_KEYCODE;

                   evt.key_code = event[i].code;

                   dfb_input_dispatch( data->device, &evt );

                   keyboard_set_lights( data, evt.locks );
    			}

          }

          if (readlen <= 0)
          {
               usleep( 200000 );
          }

     }

     if (readlen <= 0 && errno != EINTR)
     {
          D_PERROR ("keyboard thread died\n");
     }

     return NULL;
}


/* driver functions */

static int driver_get_available( void )
{
     int fd;

     switch (dfb_system_type())
     {
          case CORE_FBDEV:
          case CORE_DEVMEM:
               return 1;
          default:
               return 0;
     }

     fd = open("/dev/input/event0", O_RDWR | O_NOCTTY );
     if (fd < 0)
     {
        return 0;
     }

     close( fd );

     return 1;
}


static void driver_get_info( InputDriverInfo *info)
{
     /* fill driver info structure */
     snprintf(info->name,DFB_INPUT_DRIVER_INFO_NAME_LENGTH, "Keyboard Driver" );

     snprintf(info->vendor,DFB_INPUT_DRIVER_INFO_VENDOR_LENGTH, "directfb.org" );

     info->version.major = 0;
     info->version.minor = 9;

     return;
}


static DFBResult
driver_open_device( CoreInputDevice  *device,
                    unsigned int      number,
                    InputDeviceInfo  *info,
                    void            **driver_data )
{
     int             fd;
     struct termios  ts;
     KeyboardData   *data;


     if (dfb_system_type() == CORE_FBDEV && dfb_config->vt) {
          FBDev *dfb_fbdev = dfb_system_data();

          fd = dup( dfb_fbdev->vt->fd );
          if (fd < 0) {
               D_PERROR( "DirectFB/Keyboard: Could not dup() file descriptor of TTY!\n" );
               return DFB_INIT;
          }
     }
     else {
          //fd = open( "/dev/tty0", O_RDWR | O_NOCTTY );
          fd = open ("/dev/input/event0", O_RDWR | O_NOCTTY );
          if (fd < 0) {
               D_PERROR( "DirectFB/Keyboard: Could not open() /dev/tty0!\n" );
               return DFB_INIT;
          }
     }

     /* allocate and fill private data */
     data = D_CALLOC( 1, sizeof(KeyboardData) );
     if (!data) {
          close( fd );
          return D_OOM();
     }

     data->device = device;
     data->vt_fd  = fd;

     tcgetattr( data->vt_fd, &data->old_ts );

     ts = data->old_ts;
     ts.c_cc[VTIME] = 0;
     ts.c_cc[VMIN] = 1;
     ts.c_lflag &= ~(ICANON|ECHO|ISIG);
     ts.c_iflag = 0;
     tcsetattr( data->vt_fd, TCSAFLUSH, &ts );

     tcsetpgrp( data->vt_fd, getpgrp() );

     if (dfb_system_type() == CORE_FBDEV && dfb_config->vt) {
          FBDev *dfb_fbdev = dfb_system_data();
          dfb_fbdev->vt->flush = false;
     }

     /* fill device info structure */
     snprintf( info->desc.name,
               DFB_INPUT_DEVICE_DESC_NAME_LENGTH, "Keyboard" );

     snprintf( info->desc.vendor,
               DFB_INPUT_DEVICE_DESC_VENDOR_LENGTH, "Unknown" );

     /* claim to be the primary keyboard */
     info->prefered_id = DIDID_KEYBOARD;

     /* classify as a keyboard able to produce key events */
     info->desc.type   = DIDTF_KEYBOARD;
#ifndef DIRECTFB_DISABLE_DEPRECATED
     info->desc.caps   = DICAPS_KEYS;
#else
     info->desc.caps   = DIDCAPS_KEYS;
#endif

     /* enable translation of raw hardware keycodes */
     info->desc.min_keycode = 0;
     info->desc.max_keycode = 127;

     /* start input thread */
     data->thread = direct_thread_create( DTT_INPUT, keyboardEventThread, data, "Keyboard Input" );

     /* set private data pointer */
     *driver_data = data;

     return DFB_OK;
}


/*
 * Fetch one entry from the kernel keymap.
 */
static DFBResult driver_get_keymap_entry( CoreInputDevice *device, void *driver_data, DFBInputDeviceKeymapEntry *entry)
{
    HI_S32 Ret  = HI_SUCCESS;
    HI_S32 Code = entry->code;
    DFBInputDeviceKeyIdentifier enIdentifier;
    DFBInputDeviceKeySymbol enSymbol;

    Ret = keymap_entry(Code,&enIdentifier,&enSymbol);
    if (HI_SUCCESS != Ret)
    {
       return DFB_INVARG;
    }

    if (enIdentifier >= DIKI_KP_DECIMAL && enIdentifier <= DIKI_KP_9)
    {
       entry->locks |= DILS_NUM;
    }

    entry->identifier = enIdentifier;
    entry->symbols[DIKSI_BASE] = enSymbol;

    return DFB_OK;
}


static void driver_close_device( void *driver_data)
{
     KeyboardData *data = (KeyboardData*) driver_data;

     /* stop input thread */
     direct_thread_cancel( data->thread );
     direct_thread_join( data->thread );
     direct_thread_destroy( data->thread );

     if (tcsetattr( data->vt_fd, TCSAFLUSH, &data->old_ts ) < 0)
     {
          D_PERROR("DirectFB/keyboard: tcsetattr for original values failed!\n");
     }

     close( data->vt_fd );

     /* free private data */
     D_FREE( data );
}
