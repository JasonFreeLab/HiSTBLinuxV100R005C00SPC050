/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name       : bluetooth.c
Version          :
Author           :
Created         : 2017/01/03
Description    : CNcomment:蓝牙适配CNend\n
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


#include "hi_type.h"

/***************************** Macro Definition ******************************/
/** 遥控器按键个数*/
#define BLUETOOTH_KEY_MAX_NUM  50


/**在input_driver.h中完成各个函数注册*/
DFB_INPUT_DRIVER(bluetooth)


/*************************** Structure Definition ****************************/
/**虚拟键值枚举**/
typedef enum tagBLUETOOTH_KEYCODE_E
{
    /**0 -> 9 **/
    BLUETOOTH_KEY_1  = 1,
    BLUETOOTH_KEY_2,
    BLUETOOTH_KEY_3,
    BLUETOOTH_KEY_4,
    BLUETOOTH_KEY_5,
    BLUETOOTH_KEY_6,
    BLUETOOTH_KEY_7,
    BLUETOOTH_KEY_8,
    BLUETOOTH_KEY_9,
    BLUETOOTH_KEY_0,

    /**第一排*/
    BLUETOOTH_KEY_POWER    = 11,
    BLUETOOTH_KEY_AUDIO,
    BLUETOOTH_KEY_MUTE,

    /**第二排*/
    BLUETOOTH_KEY_CHNDOWN  = 14,
    BLUETOOTH_KEY_CHNUP,
    BLUETOOTH_KEY_VOLDOWN,
    BLUETOOTH_KEY_VOLUP,

    BLUETOOTH_KEY_DEL       = 18,
    BLUETOOTH_KEY_SEARCH,
    BLUETOOTH_KEY_MORE,
    BLUETOOTH_KEY_FAV,
    BLUETOOTH_KEY_IME,


    /**遥控器底下几排按键值**/
    BLUETOOTH_KEY_UP        = 23,
    BLUETOOTH_KEY_DOWN,
    BLUETOOTH_KEY_LEFT,
    BLUETOOTH_KEY_RIGHT,
    BLUETOOTH_KEY_ENTER,

    BLUETOOTH_KEY_EPG       = 28,
    BLUETOOTH_KEY_PGUP,
    BLUETOOTH_KEY_PGDOWN,
    BLUETOOTH_KEY_BACK,

    BLUETOOTH_KEY_BTV       = 32,
    BLUETOOTH_KEY_VOD,
    BLUETOOTH_KEY_NVOD,
    BLUETOOTH_KEY_NPVR,

    BLUETOOTH_KEY_PLAY      = 36,
	BLUETOOTH_KEY_STOP,
	BLUETOOTH_KEY_REW,
	BLUETOOTH_KEY_FF,

    BLUETOOTH_KEY_F1        = 40,
    BLUETOOTH_KEY_F2,
    BLUETOOTH_KEY_F3,
    BLUETOOTH_KEY_F4,

    BLUETOOTH_KEY_SET       = 44,
    BLUETOOTH_KEY_SUB,
    BLUETOOTH_KEY_SEEK,
    BLUETOOTH_KEY_INFO,

    BLUETOOTH_KEY_RESERVER1 = 48,
    BLUETOOTH_KEY_RESERVER2,

	BLUETOOTH_KEY_BUTT
}BLUETOOTH_KEYCODE_E;

typedef struct
{
    HI_S32 s32Code;     /* hardware key code */
    HI_S32	s32VirKey;  /*将物理键值映射成虚拟键值，方便阅读*/
}BLUETOOTH_HARDKEY_MAP_TO_VIRKEY;


typedef struct
{
     HI_S32 VirKeyCode; /** virtual key value that from hardware key code been mapped **/
     DFBInputDeviceKeyIdentifier enIdentifier; /* basic mapping */
     DFBInputDeviceKeySymbol enSymbols;    /* advanced key */
}BLUETOOTH_MAP_TO_INPUT;

typedef struct
{
	CoreInputDevice *device;
	DirectThread    *thread;
	struct termios   old_ts;
	HI_S32  vt_fd;
}HI_BLUETOOTH_DATA;


/********************** Global Variable declaration **************************/
static BLUETOOTH_HARDKEY_MAP_TO_VIRKEY gs_stHardMapToVir[BLUETOOTH_KEY_MAX_NUM] =
{
	{0x6d92ff00, BLUETOOTH_KEY_1},
	{0x6c93ff00, BLUETOOTH_KEY_2},
	{0x33ccff00, BLUETOOTH_KEY_3},
	{0x718eff00, BLUETOOTH_KEY_4},
	{0x708fff00, BLUETOOTH_KEY_5},
	{0x37c8ff00, BLUETOOTH_KEY_6},
	{0x758aff00, BLUETOOTH_KEY_7},
	{0x748bff00, BLUETOOTH_KEY_8},
	{0x3bc4ff00, BLUETOOTH_KEY_9},
	{0x7887ff00, BLUETOOTH_KEY_0},

    {0x639cff00, BLUETOOTH_KEY_POWER},
	{0x2ed1ff00, BLUETOOTH_KEY_AUDIO},
	{0x22ddff00, BLUETOOTH_KEY_MUTE},

    {0x7986ff00, BLUETOOTH_KEY_CHNDOWN},
	{0x7a85ff00, BLUETOOTH_KEY_CHNUP},
	{0x7e81ff00, BLUETOOTH_KEY_VOLDOWN},
	{0x7f80ff00, BLUETOOTH_KEY_VOLUP},

    {0x7788ff00, BLUETOOTH_KEY_DEL},
	{0x6897ff00, BLUETOOTH_KEY_SEARCH},
    {0x39c6ff00, BLUETOOTH_KEY_MORE},
    {0x6b94ff00, BLUETOOTH_KEY_FAV},
	{0x609fff00, BLUETOOTH_KEY_IME},

	{0x35caff00, BLUETOOTH_KEY_UP},
	{0x2dd2ff00, BLUETOOTH_KEY_DOWN},
	{0x6699ff00, BLUETOOTH_KEY_LEFT},
	{0x3ec1ff00, BLUETOOTH_KEY_RIGHT},
	{0x31ceff00, BLUETOOTH_KEY_ENTER},

	{0x629dff00, BLUETOOTH_KEY_EPG},
	{0x30cfff00, BLUETOOTH_KEY_PGUP},
	{0x6798ff00, BLUETOOTH_KEY_PGDOWN},
	{0x6f90ff00, BLUETOOTH_KEY_BACK},

	{0x649bff00, BLUETOOTH_KEY_BTV},
	{0x659aff00, BLUETOOTH_KEY_VOD},
	{0x3fc0ff00, BLUETOOTH_KEY_NVOD},
	{0x3dc2ff00, BLUETOOTH_KEY_NPVR},

	{0x3cc3ff00, BLUETOOTH_KEY_PLAY},
	{0x25daff00, BLUETOOTH_KEY_REW},
	{0x29d6ff00, BLUETOOTH_KEY_FF},
	{0x2fd0ff00, BLUETOOTH_KEY_STOP},

	{0x7b84ff00, BLUETOOTH_KEY_F1},
	{0x7689ff00, BLUETOOTH_KEY_F2},
	{0x26d9ff00, BLUETOOTH_KEY_F3},
	{0x6996ff00, BLUETOOTH_KEY_F4},

	{0x6a95ff00, BLUETOOTH_KEY_SET},
	{0x738cff00, BLUETOOTH_KEY_SUB},
	{0x7d82ff00, BLUETOOTH_KEY_SEEK},
	{0x38c7ff00, BLUETOOTH_KEY_INFO},

	{},
	{},
    {}
};


BLUETOOTH_MAP_TO_INPUT gs_stBluetoothVirKeyToInputSymbols[BLUETOOTH_KEY_MAX_NUM] =
{
	{BLUETOOTH_KEY_1,             DIKI_1,           DIKS_1},
	{BLUETOOTH_KEY_2,             DIKI_2,           DIKS_2},
	{BLUETOOTH_KEY_3,             DIKI_3,           DIKS_3},
	{BLUETOOTH_KEY_4,             DIKI_4,           DIKS_4},
	{BLUETOOTH_KEY_5,             DIKI_5,           DIKS_5},
	{BLUETOOTH_KEY_6,             DIKI_6,           DIKS_6},
	{BLUETOOTH_KEY_7,             DIKI_7,           DIKS_7},
	{BLUETOOTH_KEY_8,             DIKI_8,           DIKS_8},
	{BLUETOOTH_KEY_9,             DIKI_9,           DIKS_9},
	{BLUETOOTH_KEY_0,             DIKI_0,           DIKS_0},

    {BLUETOOTH_KEY_POWER,         DIKI_ESCAPE,      DIKS_POWER},
	{BLUETOOTH_KEY_AUDIO,         DIKI_UNKNOWN,     DIKS_AUDIO},
	{BLUETOOTH_KEY_MUTE,          DIKI_UNKNOWN,     DIKS_MUTE},

    {BLUETOOTH_KEY_CHNDOWN,       DIKI_SHIFT_L,     DIKS_CHANNEL_DOWN},
	{BLUETOOTH_KEY_CHNUP,         DIKI_SHIFT_R,     DIKS_CHANNEL_UP},
	{BLUETOOTH_KEY_VOLDOWN,       DIKI_CONTROL_L,   DIKS_VOLUME_DOWN},
	{BLUETOOTH_KEY_VOLUP,         DIKI_CONTROL_R,   DIKS_VOLUME_UP},

    {BLUETOOTH_KEY_DEL,           DIKI_BACKSPACE,   DIKS_BACKSPACE},
    {BLUETOOTH_KEY_SEARCH,        DIKI_META_R,      DIKS_GOTO},
    {BLUETOOTH_KEY_MORE,          DIKI_META_L,      DIKS_OPTION},
    {BLUETOOTH_KEY_FAV,           DIKI_ALT_R,       DIKS_FAVORITES},
	{BLUETOOTH_KEY_IME,           DIKI_ALT_L,       DIKS_INSERT},

	{BLUETOOTH_KEY_UP,            DIKI_UP,          DIKS_CURSOR_UP},
	{BLUETOOTH_KEY_DOWN,          DIKI_DOWN,        DIKS_CURSOR_DOWN},
	{BLUETOOTH_KEY_LEFT,          DIKI_LEFT,        DIKS_CURSOR_LEFT},
	{BLUETOOTH_KEY_RIGHT,         DIKI_RIGHT,       DIKS_CURSOR_RIGHT},
	{BLUETOOTH_KEY_ENTER,         DIKI_ENTER,       DIKS_ENTER},

    {BLUETOOTH_KEY_EPG,           DIKI_HOME,        DIKS_EPG},
	{BLUETOOTH_KEY_PGUP,          DIKI_PAGE_UP,     DIKS_PAGE_UP},
	{BLUETOOTH_KEY_PGDOWN,        DIKI_PAGE_DOWN,   DIKS_PAGE_DOWN},
    {BLUETOOTH_KEY_BACK,          DIKI_ESCAPE,      DIKS_ESCAPE},

    {BLUETOOTH_KEY_BTV,           DIKI_UNKNOWN,     DIKS_TV},
	{BLUETOOTH_KEY_VOD,           DIKI_UNKNOWN,     DIKS_NULL},
	{BLUETOOTH_KEY_NVOD,          DIKI_UNKNOWN,     DIKS_NULL},
	{BLUETOOTH_KEY_NPVR,          DIKI_UNKNOWN,     DIKS_PVR},


    {BLUETOOTH_KEY_PLAY,           DIKI_PAUSE,      DIKS_PLAYPAUSE},
    {BLUETOOTH_KEY_REW,            DIKI_SUPER_L,    DIKS_REWIND},
    {BLUETOOTH_KEY_FF,             DIKI_SUPER_R,    DIKS_SHUFFLE},
    {BLUETOOTH_KEY_STOP,           DIKI_END,        DIKS_STOP},

	{BLUETOOTH_KEY_F1,             DIKI_F1,         DIKS_F1},
	{BLUETOOTH_KEY_F2,             DIKI_F2,         DIKS_F2},
	{BLUETOOTH_KEY_F3,             DIKI_F3,         DIKS_F3},
	{BLUETOOTH_KEY_F4,             DIKI_F4,         DIKS_F4},

	{BLUETOOTH_KEY_SET,            DIKI_INSERT,     DIKS_SETUP},
	{BLUETOOTH_KEY_SUB,            DIKI_UNKNOWN,    DIKS_SUBTITLE},
	{BLUETOOTH_KEY_SEEK,           DIKI_UNKNOWN,    DIKS_NULL},
	{BLUETOOTH_KEY_INFO,           DIKI_UNKNOWN,    DIKS_INFO},

    {},
	{},
    {}
};

/******************************* API forward declarations *******************/


/******************************* API realization *****************************/

/*****************************************************************************
* func             : driver_get_keymap_entry
* description   : CNcomment: map bluetooth hard value map to virtual key value, and save to input envent CNend\n
                         CNcomment: 将蓝牙物理设备事件映射成虚拟事件，然后匹配相关键值给input
                                              真正使用的时候，也只需要将虚拟键值给input code即可CNend\n
* param[in]    : device
* param[in]    : driver_data
* param[in]    : entry
* retval          : DFB_OK
*****************************************************************************/
static HI_S32 BluetoothTable_Map_InputTable(HI_S32 code, DFBInputDeviceKeyIdentifier *penIdentifier, DFBInputDeviceKeySymbol *penSymbol)
{
	HI_S32 CodeIndex = 0;

	for (CodeIndex = 0;CodeIndex < BLUETOOTH_KEY_MAX_NUM; CodeIndex++)
	{
		if (code == gs_stBluetoothVirKeyToInputSymbols[CodeIndex].VirKeyCode)
		{
            *penIdentifier = gs_stBluetoothVirKeyToInputSymbols[CodeIndex].enIdentifier;
            *penSymbol =  gs_stBluetoothVirKeyToInputSymbols[CodeIndex].enSymbols;
            return HI_SUCCESS;
		}
	}

	return HI_FAILURE;
}

static DFBResult driver_get_keymap_entry(CoreInputDevice *device,void *driver_data,DFBInputDeviceKeymapEntry *entry)
{
	HI_S32 s32Ret = HI_SUCCESS;
	DFBInputDeviceKeyIdentifier enIdentifier;
	DFBInputDeviceKeySymbol enSymbol;
	HI_S32 s32Code = entry->code;

	s32Ret = BluetoothTable_Map_InputTable(s32Code,&enIdentifier,&enSymbol);
	if (s32Ret)
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

static int driver_get_available(void)
{
    HI_S32 fd = -1;

    fd = open("/dev/bluetooth", O_RDWR | O_NOCTTY );
    if (fd < 0)
    {
        return 0;
    }

    close( fd );

    return 1;
}

static void driver_get_info(InputDriverInfo *info)
{
     snprintf( info->name, DFB_INPUT_DRIVER_INFO_NAME_LENGTH, "BLUETOOTH Driver" );
     snprintf( info->vendor,DFB_INPUT_DRIVER_INFO_VENDOR_LENGTH, "directfb.org" );

     info->version.major = 0;
     info->version.minor = 3;
}


/*****************************************************************************
* func             : LircEventThread
* description   : CNcomment: CNend\n
                         CNcomment: 查询虚拟键值，键虚拟键值赋值给key_code，然后分发事件CNend\n
* param[in]    : device
* param[in]    : driver_data
* param[in]    : entry
* retval          : DFB_OK
*****************************************************************************/
static void* BlueToothEventThread(DirectThread *thread, void *driver_data)
{
	HI_S32 KeyCodeIndex = 0;
    DFBInputEvent stInputEvt;
	HI_U64 BlueToothKeyId = 0;
	HI_S32 BlueToothVirKeyCode = 0;
	HI_BLUETOOTH_DATA  *pstData = (HI_BLUETOOTH_DATA*)driver_data;

	while (pstData)
	{
        memset(&stInputEvt, 0x0, sizeof(DFBInputEvent));

	    stInputEvt.type  = DIET_KEYPRESS;
		stInputEvt.flags = DIEF_KEYCODE;

		for (KeyCodeIndex = 0; KeyCodeIndex < BLUETOOTH_KEY_MAX_NUM; KeyCodeIndex++)
		{
			if (BlueToothKeyId == gs_stHardMapToVir[KeyCodeIndex].s32Code)
			{
				BlueToothVirKeyCode = gs_stHardMapToVir[KeyCodeIndex].s32VirKey;
				break;
			}
		}

		stInputEvt.key_code = BlueToothVirKeyCode;

		dfb_input_dispatch(pstData->device, &stInputEvt);
	}

	return NULL;
}

static DFBResult driver_open_device(CoreInputDevice *device, unsigned int number,InputDeviceInfo  *info, void **driver_data )
{
	HI_BLUETOOTH_DATA *pstData = NULL;

    /**
         **不同输入设备类型保存不同的设备信息
         **/
	pstData = D_CALLOC(1, sizeof(HI_BLUETOOTH_DATA));
	if (NULL == pstData)
	{
		return D_OOM();
	}

	pstData->device = device;

    /**设备名字 **/
	snprintf(info->desc.name, DFB_INPUT_DEVICE_DESC_NAME_LENGTH, "BLUETOOTH");
	snprintf(info->desc.vendor, DFB_INPUT_DEVICE_DESC_VENDOR_LENGTH, "Unknown");

    /**设备ID **/
	info->prefered_id = DIDID_REMOTE;
    /**设备类型**/
	info->desc.type   = DIDTF_REMOTE;
	info->desc.caps   = DICAPS_KEYS;

     /**设备有多少个键值**/
	info->desc.min_keycode = 0;
	info->desc.max_keycode = BLUETOOTH_KEY_MAX_NUM;

	pstData->thread = direct_thread_create(DTT_INPUT, BlueToothEventThread, pstData, "BLUETOOTH");

	*driver_data = pstData;

	return DFB_OK;
}

static void driver_close_device(void *driver_data)
{
	HI_BLUETOOTH_DATA *pstData = (HI_BLUETOOTH_DATA*)driver_data;

	direct_thread_cancel(pstData->thread);
	direct_thread_join(pstData->thread);
	direct_thread_destroy(pstData->thread);

	D_FREE( pstData );
}
