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
#include "string.h"
#include "Protocol.h"
#include "Utilities/Vector.h"
#include "Utilities/Util.h"
#include "DeviceControllers/IntrController.h"
#include "DeviceControllers/UartController.h"


/*** Devices *****************************************************/
XGpio GpioOutput;
XGpio GpioInput;
XUartLite uartCtr;
XUartLite uartCtr_1;

/*** Variables *****************************************************/
Xuint32 DataRead;
Xuint32 OldData;
volatile int* regLED = (int*) XPAR_DIGILENT_SEVSEG_DISP_BASEADDR;
Vector dataVector;
/*** Methods ******************************************************/
Xuint32 initLed();
Xuint32 initSwitch();
void SendHandler(void *CallBackRef, unsigned int EventData);
void RecvHandler(void *CallBackRef, unsigned int EventData);
/******************************************************************/


int main()
{
	//Initialize basic setup
	/***************************************************************/
	int Status;
	init_platform();
	xil_printf("%c[2J", 27);
	/***************************************************************/
	//Local data stack
	/***************************************************************/
	vector_init(&dataVector);
	memset(RecvBuffer, 0, sizeof(RecvBuffer));
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
	Status = initUartController(&uartCtr,XPAR_AXI_UARTLITE_0_DEVICE_ID );
	xil_printf("Uart Status : 0x%X\r\n", Status);
	Status = initUartController(&uartCtr_1,XPAR_AXI_UARTLITE_1_DEVICE_ID );
	xil_printf("Uart_1 Status : 0x%X\r\n", Status);
	/***************************************************************/
	//Interrupt Controller.
	/***************************************************************/
	Status = initInterruptSystem();
	connectInterrupts(&uartCtr,XPAR_INTC_0_UARTLITE_0_VEC_ID,(XInterruptHandler)XUartLite_InterruptHandler);
	startIntrController();
	enableIntrController();
	checkStatus(Status);
	microblaze_enable_interrupts();
	/***************************************************************/
	//Setup Uart Intr Handlers
	/***************************************************************/
	XUartLite_SetSendHandler(&uartCtr, SendHandler, &uartCtr);
	XUartLite_SetRecvHandler(&uartCtr, RecvHandler, &uartCtr);
	XUartLite_EnableInterrupt(&uartCtr);
	/***************************************************************/
	XUartLite_Recv(&uartCtr,RecvBuffer,8);
	XUartLite_DisableInterrupt(&uartCtr_1);

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
						Status = sendString((unsigned char *)"This is a test.",&uartCtr);
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

void SendHandler(void *CallBackRef, unsigned int EventData)
{
    xil_printf("SendEvent : 0x%X\r\n", EventData);
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
	xil_printf("RcvEvent : 0x%X\r\n", EventData);
	XUartLite_EnableInterrupt(&uartCtr);
	XUartLite_Recv(&uartCtr,RecvBuffer,8);
}







