#ifndef _DVB_USB_TBSUSB_H_
#define _DVB_USB_TBSUSB_H_

#define DVB_USB_LOG_PREFIX "tbsusb"
#include "dvb-usb.h"

#define deb_xfer(args...) dprintk(dvb_usb_tbsusb_debug, 0x02, args)
#define deb_info(args...) dprintk(dvb_usb_tbsusb_debug, 0x01, args)
#endif
