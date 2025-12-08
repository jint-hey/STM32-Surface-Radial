#include "MyDial.h"

/// @brief 发送USB数据给主机
/// @param wheel 待发送USB HID滚轮数据
void USBD_HID_SendData(int16_t wheel)
{
    uint8_t buf_tx[3];

    buf_tx[0] = 0x01; // Report ID

    // 高字节在前，低字节在后（小端平台常见写法）
    buf_tx[1] = (uint8_t)((wheel >> 8) & 0xFF);
    buf_tx[2] = (uint8_t)(wheel & 0xFF);

    (void)USBD_HID_SendReport(&hUsbDeviceFS, buf_tx, sizeof(buf_tx));
}
