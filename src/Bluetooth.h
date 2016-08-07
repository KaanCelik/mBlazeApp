/*
 * Bluetooth.h
 *
 *  Created on: 04 Aðu 2016
 *      Author: KaaN
 */

#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_
#include "DeviceControllers/UartController.h"
#include "Utilities/Vector.h"
#include "stdlib.h"
u8 bt_setUp(u32 uartDeviceId);
XUartLite* bt_getPtr();
u8 bt_send(char* strMessage);
void bt_start(u8 initialRecvSize);
void bt_setUpIntr();
Vector* bt_getStack();
Vector* bt_getPacket();
u8 bt_getPacketFlag();
void bt_setPacketFlag(u8 packetFlag);



#endif /* BLUETOOTH_H_ */
