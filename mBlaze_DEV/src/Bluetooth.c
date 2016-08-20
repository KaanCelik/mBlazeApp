/*
 * Bluetooth.c
 *
 *  Created on: 04 Aðu 2016
 *      Author: KaaN
 */

#include "Bluetooth.h"
#define BT_BUFFER_SIZE 64

XUartLite blueToothUartCtr;
Vector rxStack;
volatile u8 dataPresent;
volatile u8 lastReceivedCount;

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
u8 bt_isDataPresent(){
	return dataPresent;
}
void bt_setDataPresent(u8 isDataPresent){
	dataPresent = isDataPresent;
	}
void bt_start(u8 initialRecvSize){
	XUartLite_Recv(&blueToothUartCtr,RecvBuffer,initialRecvSize);
}

void bt_resetStack(){
	vector_init(&rxStack);
}

Vector* bt_getStack(){
	return &rxStack;
}

#define hasValidData (XUartLite_GetStatusReg(blueToothUartCtr.RegBaseAddress)& XUL_SR_RX_FIFO_VALID_DATA)

void SendHandler(void *CallBackRef, unsigned int EventData)
{
    xil_printf("SendEvent : 0x%X\r\n", EventData);
}

void bt_receiveBuffer(){

    vector_appendArray(&rxStack, RecvBuffer, lastReceivedCount);
    u8 rcvCount = 0;
    logVariable(XUartLite_GetStatusReg(blueToothUartCtr.RegBaseAddress) , "hasValid");
    while(XUartLite_GetStatusReg(blueToothUartCtr.RegBaseAddress)& XUL_SR_RX_FIFO_VALID_DATA){
    	XUartLite_DisableInterrupt(&blueToothUartCtr);
    	rcvCount = XUartLite_Recv(&blueToothUartCtr,RecvBuffer,MAX_BUFFER_SIZE);
    	XUartLite_EnableInterrupt(&blueToothUartCtr);

		if(rcvCount){
			vector_appendArray(&rxStack,RecvBuffer,rcvCount);
		}
	}

    XUartLite_Recv(&blueToothUartCtr, RecvBuffer, 16);

}

void RecvHandler(void *CallBackRef, unsigned int EventData) {

	bt_setDataPresent(TRUE);
	lastReceivedCount = EventData;
	//fastReceive();
	bt_receiveBuffer();
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


