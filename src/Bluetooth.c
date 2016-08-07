/*
 * Bluetooth.c
 *
 *  Created on: 04 Aðu 2016
 *      Author: KaaN
 */

#include "Bluetooth.h"


XUartLite blueToothUartCtr;
Vector rxStack;
Vector packet;
u8 packetReceived;

u8 bt_setUp(u32 uartDeviceId){
	vector_init(&rxStack);
	u8 status = initUartController(&blueToothUartCtr,uartDeviceId);
	return status;
}

u8 bt_send(char* strMessage){
	u8 status  = sendString((unsigned char *)strMessage,&blueToothUartCtr);
	return status;
}
XUartLite* bt_getPtr(){
	return &blueToothUartCtr;
}
u8 bt_getPacketFlag(){
	return packetReceived;
}
void bt_setPacketFlag(u8 packetFlag){
	packetReceived = packetFlag;
	}
void bt_start(u8 initialRecvSize){
	XUartLite_Recv(&blueToothUartCtr,RecvBuffer,initialRecvSize);
}

Vector* bt_getStack(){
	return &rxStack;
}

void SendHandler(void *CallBackRef, unsigned int EventData)
{
    xil_printf("SendEvent : 0x%X\r\n", EventData);
}
void RecvHandler(void *CallBackRef, unsigned int EventData)
{
	XUartLite_DisableInterrupt(&blueToothUartCtr);
	vector_appendArray(&rxStack,RecvBuffer,EventData);
	int rcvCount=0;

	while(!XUartLite_IsReceiveEmpty(blueToothUartCtr.RegBaseAddress)){
		rcvCount = XUartLite_Recv(&blueToothUartCtr,RecvBuffer,16);
		if(rcvCount){
			xil_printf("Data received\r\n");
			printBuffer(RecvBuffer, "Received buffer");
			vector_appendArray(&rxStack,RecvBuffer,rcvCount);

		}
	}
	if((EventData+rcvCount) > 0) {
		packetReceived = TRUE;
	}
	xil_printf("RcvEvent : 0x%X\r\n", EventData);
	XUartLite_EnableInterrupt(&blueToothUartCtr);
	XUartLite_Recv(&blueToothUartCtr,RecvBuffer,1);
}
void bt_setUpIntr(){

	XUartLite_SetSendHandler(&blueToothUartCtr, SendHandler, &blueToothUartCtr);
	XUartLite_SetRecvHandler(&blueToothUartCtr, RecvHandler, &blueToothUartCtr);
	XUartLite_EnableInterrupt(&blueToothUartCtr);

}

void printStack(){
	printVector(&rxStack);
}

void printUartProperties(){
	printUartLiteProperties(&blueToothUartCtr);
}


