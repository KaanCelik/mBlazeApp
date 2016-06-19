/*
 * main.c
 *
 *  Created on: 10 Nis 2016
 *      Author: KaaN
 */
#include "xparameters.h"
#include <stdio.h>
#include "platform.h"
#include "xbasic_types.h"
#include "xgpio.h"
#include "xstatus.h"
#include "xil_io.h"
#include "xuartlite.h"
#include "xuartlite_l.h"
#include "string.h"
#include "Protocol.h"
#include "Utilities/Vector.h"
#include "Utilities/Util.h"
#include "DeviceControllers/IntrController.h"


#define MAX_BUFFER_SIZE 16
/*** Devices *****************************************************/
XGpio GpioOutput;
XGpio GpioInput;
XUartLite uartCtr;
XUartLite uartCtr_1;

/*** Variables *****************************************************/
Xuint32 DataRead;
Xuint32 OldData;
volatile int* regLED = (int*) XPAR_DIGILENT_SEVSEG_DISP_BASEADDR;

u8 SendBuffer[MAX_BUFFER_SIZE];    /* Buffer for Transmitting Data */
u8 RecvBuffer[MAX_BUFFER_SIZE];    /* Buffer for Receiving Data */
int TotalReceivedCount;
int TotalSentCount;
Vector dataVector;
volatile u8 handleType;

/*** Methods ******************************************************/
Xuint32 initLed();
Xuint32 initSwitch();
void printUartLiteProperties();
u32 sendString(u8* data, XUartLite* uartInstancePtr);
void SendHandler(void *CallBackRef, unsigned int EventData);
void RecvHandler(void *CallBackRef, unsigned int EventData);
int rxHasValidData();
/******************************************************************/


int main()
{
	//Initialize basic setup
	/***************************************************************/
	int Status;
	init_platform();
	vector_init(&dataVector);
	xil_printf("%c[2J", 27);
	memset(RecvBuffer, 0, sizeof(RecvBuffer));

	//Setup test message to send
	/***************************************************************/
	Packet testPack;
	testPack.rawSize=strlen("sample");
	testPack.rawData = "sample";
	constructPacket(&testPack);
	/***************************************************************/
	//Input Output Devices
	/***************************************************************/
	Status = initLed();
	checkStatus(Status);
	Status =initSwitch();
	checkStatus(Status);
	/***************************************************************/
	//Axi Timer
	/***************************************************************/
	//UartLite
	/***************************************************************/
	Status = XUartLite_Initialize(&uartCtr,XPAR_AXI_UARTLITE_0_DEVICE_ID );
	checkStatus(Status);
	XUartLite_ResetFifos(&uartCtr);
	Status = XUartLite_SelfTest(&uartCtr);
	xil_printf("Uart Status : 0x%X\r\n", Status);
	checkStatus(Status);

	Status = XUartLite_Initialize(&uartCtr_1,XPAR_AXI_UARTLITE_1_DEVICE_ID );
	checkStatus(Status);
	XUartLite_ResetFifos(&uartCtr_1);
	Status = XUartLite_SelfTest(&uartCtr_1);
	xil_printf("Uart_1 Status : 0x%X\r\n", Status);
	checkStatus(Status);
	/***************************************************************/
	//Interrupt Controller.
	/***************************************************************/
	Status = initInterruptSystem();
	connectInterrupts(&uartCtr);
	startIntrController();
	enableIntrController();
	checkStatus(Status);
	microblaze_enable_interrupts();
	/***************************************************************/
	//Setup for main loop
	/***************************************************************/
	XUartLite_SetSendHandler(&uartCtr, SendHandler, &uartCtr);
	XUartLite_SetRecvHandler(&uartCtr, RecvHandler, &uartCtr);
	XUartLite_EnableInterrupt(&uartCtr);
	XUartLite_Recv(&uartCtr,RecvBuffer,8);

	XUartLite_DisableInterrupt(&uartCtr_1);

	printBuffer((&testPack)->buffer,"Send Buff");


	xil_printf("Entering Main Loop\r\n");
	u32 oldSwitch = 0x0;

	while (1)
		{

			u32 switchInput = XGpio_DiscreteRead(&GpioInput,1);
			if(switchInput != 0){

				if(switchInput==128){
					break;
				}
				if(oldSwitch<switchInput){
					if(switchInput==1){
						Status = sendString((unsigned char *)((&testPack)->buffer) ,&uartCtr);
						checkSendSuccess(Status);
					}
					if(switchInput==2){
						printBuffer(RecvBuffer,"Received Buffer");
					}
					if(switchInput==4){
						printUartLiteProperties();
					}
					if(switchInput==8){
						printVector(&dataVector);
					}
					if(switchInput==16){
						Status = sendString((unsigned char *)"AT",&uartCtr);
						checkSendSuccess(Status);
					}
					if(switchInput==32){

						sendString((u8*)"JESSIE",&uartCtr_1);

						u8 lcdSendBuffer[16];
						unsigned char escSeq[3] = {0x1B,'[', '\0'};

						strcpy((char*)lcdSendBuffer,(char*)escSeq);
						strcat((char*)lcdSendBuffer,"3e");
						sendString(lcdSendBuffer,&uartCtr_1);
						memset((char*)lcdSendBuffer, 0, 16);


						strcpy((char*)lcdSendBuffer,(char*)escSeq);
						strcat((char*)lcdSendBuffer,"j");
						sendString(lcdSendBuffer,&uartCtr_1);

						memset(lcdSendBuffer, 0, 16);
						strcat((char*)lcdSendBuffer,(char*)escSeq);
						strcat((char*)lcdSendBuffer,"0;1H");
						sendString(lcdSendBuffer,&uartCtr_1);

						memset(lcdSendBuffer, 0, 16);
						strcat((char*)lcdSendBuffer,"Slaap lekker...");
						sendString(lcdSendBuffer,&uartCtr_1);

						memset(lcdSendBuffer, 0, 16);
						strcat((char*)lcdSendBuffer,(char*)escSeq);
						strcat((char*)lcdSendBuffer,"1;1H");
						sendString(lcdSendBuffer,&uartCtr_1);

						memset(lcdSendBuffer, 0, 16);
						strcat((char*)lcdSendBuffer,"I love you !");
						sendString(lcdSendBuffer,&uartCtr_1);





					}
				}
			}
			oldSwitch = switchInput;
		}
	xil_printf("Quitting...\r\n");
	return 0;
}

Xuint32 initLed() {

	Xuint32 status = XGpio_Initialize(&GpioOutput, XPAR_LEDS_8BITS_DEVICE_ID);
	xil_printf("LED Status : %X\r\n", status);
	if(status == XST_SUCCESS){
		XGpio_SetDataDirection(&GpioOutput, 1, 0x0);
	}
	return status;
}
Xuint32 initSwitch() {

	Xuint32 status = XGpio_Initialize(&GpioInput, XPAR_DIP_SWITCHES_8BITS_DEVICE_ID);
	xil_printf("8 BITS Switch Status : %X\r\n", status);
	if(status == XST_SUCCESS){
		XGpio_SetDataDirection(&GpioInput, 1, 0xFFFFFFFF);
	}
	return status;
}



void printUartLiteProperties() {
	u32 Status_Reg = XUartLite_GetStatusReg((&uartCtr)->RegBaseAddress);
	xil_printf("Status_Reg : 0x%X\r\n",Status_Reg );
	u32 isIntrEnabled = Status_Reg & XUL_SR_INTR_ENABLED;
	u32 isRxValidData = Status_Reg & XUL_SR_RX_FIFO_VALID_DATA;
	u32 isRxFifoFull = Status_Reg & XUL_SR_RX_FIFO_FULL;
	u32 overrunError = Status_Reg & XUL_SR_OVERRUN_ERROR;
	u32 frameError = Status_Reg & XUL_SR_FRAMING_ERROR;
	u32 parityError = Status_Reg & XUL_SR_PARITY_ERROR;
	xil_printf("|Intr_Enabled | RxValidData | RxFifoFull | Overrun | Frame | Parity |\r\n");
	xil_printf("| %d          | %d           | %d          | %d       | %d     | %d      |\r\n",isIntrEnabled,isRxValidData,isRxFifoFull,overrunError,frameError,parityError );

}
int rxHasValidData(){
	u32 Status_Reg = XUartLite_GetStatusReg((&uartCtr)->RegBaseAddress);
	u32 isRxValidData = Status_Reg & XUL_SR_RX_FIFO_VALID_DATA;
	return isRxValidData;
}



u32 sendString(u8* data, XUartLite* uartInstancePtr) {

	u32 sentCount;
	int Index;
	for (Index = 0; Index < MAX_BUFFER_SIZE; Index++)
	    {
			SendBuffer[Index] = data[Index];
			if(data[Index] == '\0'){
				break;
			}
	    }
	printBuffer(SendBuffer,"Sending data");
	int size =  strlen((char*)data);
	sentCount = XUartLite_Send(uartInstancePtr, data, size);
	while(XUartLite_IsSending(uartInstancePtr)){
		/*
		 * Sleep during the uart sends data
		 */
	}
	checkSendSuccess(sentCount - size);
	return XST_SUCCESS;
}

void SendHandler(void *CallBackRef, unsigned int EventData)
{
    TotalSentCount = EventData;
    xil_printf("SendEvent : 0x%X\r\n", TotalSentCount);
}
void RecvHandler(void *CallBackRef, unsigned int EventData)
{
	XUartLite_DisableInterrupt(&uartCtr);
	vector_appendArray(&dataVector,RecvBuffer,EventData);
	int rcvCount=0;
	while(!XUartLite_IsReceiveEmpty(XPAR_AXI_UARTLITE_0_BASEADDR)){
		rcvCount = XUartLite_Recv(&uartCtr,RecvBuffer,1);
		if(rcvCount){
			xil_printf("Data received\r\n");
			printBuffer(RecvBuffer, "Received buffer");
			vector_appendArray(&dataVector,RecvBuffer,EventData);
		}
	}
	TotalReceivedCount = EventData;
	xil_printf("RcvEvent : 0x%X\r\n", TotalReceivedCount);
	XUartLite_EnableInterrupt(&uartCtr);
	XUartLite_Recv(&uartCtr,RecvBuffer,8);
}







