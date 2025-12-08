#ifndef _MYDIAL_H
#define _MYDIAL_H

#include "usbd_hid.h"

extern USBD_HandleTypeDef hUsbDeviceFS;

void USBD_HID_SendData(int16_t wheel);

#endif
