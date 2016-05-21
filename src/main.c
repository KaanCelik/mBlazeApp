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
#include "xintc.h"
#include "xintc_l.h"
#include "xil_exception.h"
#include "xil_io.h"
#include "xuartlite.h"
#include "xuartlite_l.h"
#include "string.h"
#include "Protocol.h"
#include "Utilities/Vector.h"



#define MAX_BUFFER_SIZE 16

/*** Devices *****************************************************/
XGpio GpioOutput;
XGpio GpioInput;

XIntc InterruptController;
XUartLite uartCtr;
/*** Variables *****************************************************/
Xuint32 DataRead;
Xuint32 OldData;
volatile int* regLED = (int*) XPAR_DIGILENT_SEVSEG_DISP_BASEADDR;

u8 SendBuffer[MAX_BUFFER_SIZE];    /* Buffer for Transmitting Data */
u8 RecvBuffer[MAX_BUFFER_SIZE];    /* Buffer for Receiving Data */
int TotalReceivedCount;
int TotalSentCount;
u8 startReceiving;
Vector dataVector;

volatile u8 handleType;
/******************************************************************/
/*** Methods ******************************************************/
Xuint32 initLed();
Xuint32 initSwitch();

int SetUpInterruptSystem(XIntc *XIntcInstancePtr);
void printIntcProperties();
void printUartLiteProperties();
u32 sendString(unsigned char* data);
void SendHandler(void *CallBackRef, unsigned int EventData);
void RecvHandler(void *CallBackRef, unsigned int EventData);
void printBuffer(u8 buffer[MAX_BUFFER_SIZE], char* exp);
/******************************************************************/



int main()
{
	vector_init(&dataVector);
	memset(RecvBuffer, 0, sizeof(RecvBuffer));

	Packet testPack;
	char sampleData[] = "sample";
	int sampleSize = strlen(sampleData);
	data = sampleData;
	dataSize = sampleSize;
	constructPacket(&testPack);

	int Status;
	init_platform();
	xil_printf("%c[2J", 27);
	/***************************************************************/
	//Input Output Devices
	/***************************************************************/
	Status = initLed();
		if (Status != XST_SUCCESS){return XST_FAILURE;}
	Status =initSwitch();
		if (Status != XST_SUCCESS){return XST_FAILURE;}
	/***************************************************************/
	//Axi Timer
	/***************************************************************/
	//Status = initAxiTimer();if (Status != XST_SUCCESS) {return XST_FAILURE;}
	/***************************************************************/
	//UartLite
	/***************************************************************/
	Status = XUartLite_Initialize(&uartCtr,XPAR_AXI_UARTLITE_0_DEVICE_ID );
	xil_printf("Uart Status : 0x%X\r\n", Status);
	if (Status != XST_SUCCESS) {return XST_FAILURE;}
	XUartLite_ResetFifos(&uartCtr);
	Status = XUartLite_SelfTest(&uartCtr);
	xil_printf("Uart Status : 0x%X\r\n", Status);
	if (Status != XST_SUCCESS) {return XST_FAILURE;}

	XUartLite_SetSendHandler(&uartCtr, SendHandler, &uartCtr);
	XUartLite_SetRecvHandler(&uartCtr, RecvHandler, &uartCtr);
	XUartLite_EnableInterrupt(&uartCtr);

	//printUartLiteProperties();
	/***************************************************************/
	//Interrupt Controller.
	/***************************************************************/
	Status = XIntc_Initialize(&InterruptController, XPAR_AXI_INTC_0_DEVICE_ID);
		if (Status != XST_SUCCESS) {return XST_FAILURE;}
	Status = SetUpInterruptSystem(&InterruptController);
		if (Status != XST_SUCCESS) {return XST_FAILURE;}
	microblaze_enable_interrupts();

	/***************************************************************/
	//Setup for main loop
	/***************************************************************/


	char* sendExp = "Send Buff : ";
	printBuffer((&testPack)->buffer,sendExp);
	xil_printf("Entering Main Loop\r\n");

	XUartLite_Recv(&uartCtr,RecvBuffer,1);
	u32 oldSwitch = 0x0;
	while (1)
		{
			if(handleType){
				XUartLite_DisableInterrupt(&uartCtr);
				int recvCount=0;
				while(!XUartLite_IsReceiveEmpty((&uartCtr)->RegBaseAddress)){
				recvCount = XUartLite_Recv(&uartCtr,RecvBuffer,16);
				vector_appendArray(&dataVector, RecvBuffer,recvCount);

				}
				handleType=0;
				char * recvExp= "Received Buffer";
				printBuffer(RecvBuffer,recvExp);
				XUartLite_EnableInterrupt(&uartCtr);
			}else{
				XUartLite_EnableInterrupt(&uartCtr);
				XUartLite_Recv(&uartCtr,RecvBuffer,1);
			}

			u32 switchInput = XGpio_DiscreteRead(&GpioInput,1);
			if(switchInput != 0){

				if(switchInput==128){
					break;
				}
				if(oldSwitch<switchInput){
					if(switchInput==1){

						Status = sendString((unsigned char *)((&testPack)->buffer) );
						if (Status != XST_SUCCESS) {xil_printf("Send Fail!\r\n");return XST_FAILURE;}

					}
					if(switchInput==2){
						char* exp = "Received Buffer";
						printBuffer(RecvBuffer,exp);
					}
					if(switchInput==4){
						printUartLiteProperties();
					}
					if(switchInput==8){
						printVector(&dataVector);
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
	if (status != XST_SUCCESS){return XST_FAILURE;}
	XGpio_SetDataDirection(&GpioOutput, 1, 0x0);
	return status;
}
Xuint32 initSwitch() {

	Xuint32 status = XGpio_Initialize(&GpioInput, XPAR_DIP_SWITCHES_8BITS_DEVICE_ID);
	xil_printf("8 BITS Switch Status : %X\r\n", status);
	if (status != XST_SUCCESS){return XST_FAILURE;}
	XGpio_SetDataDirection(&GpioInput, 1, 0xFFFFFFFF);
	return status;
}

void printIntcProperties() {
	u32 ISR = XIntc_In32((&InterruptController)->BaseAddress + XIN_ISR_OFFSET);
	u32 IER = XIntc_In32((&InterruptController)->BaseAddress + XIN_IER_OFFSET);
	u32 IPR = XIntc_In32((&InterruptController)->BaseAddress + XIN_IPR_OFFSET);
	u32 IAR = XIntc_In32((&InterruptController)->BaseAddress + XIN_IAR_OFFSET);
	u32 MER = XIntc_In32((&InterruptController)->BaseAddress + XIN_MER_OFFSET);
	xil_printf("ISR Reg : 0x%X  IER : 0x%X  IPR : 0x%X IAR : 0x%X  MER : 0x%X\r\n",ISR,IER,IPR,IAR,MER );
}

void printUartLiteProperties() {
	u32 Status_Reg = XUartLite_GetStatusReg((&uartCtr)->RegBaseAddress);
	//u32 Rx_fifo = XUartLite_ReadReg((&uartCtr)->RegBaseAddress,XUL_RX_FIFO_OFFSET);
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

int SetUpInterruptSystem(XIntc *XIntcInstancePtr)
{
	int Status;


	Status = XIntc_Connect(XIntcInstancePtr, XPAR_AXI_INTC_0_AXI_UARTLITE_0_INTERRUPT_INTR,
					   (XInterruptHandler)XUartLite_InterruptHandler,
					   (void *)&uartCtr);
		if (Status != XST_SUCCESS) {
			return XST_FAILURE;
		}

	Status = XIntc_Start(XIntcInstancePtr, XIN_REAL_MODE);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	XIntc_Enable(XIntcInstancePtr, XPAR_AXI_INTC_0_AXI_TIMER_0_INTERRUPT_INTR);
	XIntc_Enable(XIntcInstancePtr, XPAR_AXI_INTC_0_AXI_UARTLITE_0_INTERRUPT_INTR);

	Xil_ExceptionInit();

	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
				(Xil_ExceptionHandler)XIntc_InterruptHandler,
				XIntcInstancePtr);

	Xil_ExceptionEnable();

	return XST_SUCCESS;

}

u32 sendString(unsigned char* data) {

	u32 sentCount;
	int Index;
	for (Index = 0; Index < MAX_BUFFER_SIZE; Index++)
	    {
			SendBuffer[Index] = data[Index];

			if(data[Index] == '\0'){
				break;
			}

	    }
	char * sendExp = "SendData";
	printBuffer(SendBuffer,sendExp);
	int size =  strlen((char*)data);
	sentCount = XUartLite_Send(&uartCtr, data, size);
	while(XUartLite_IsSending(&uartCtr)){

	}
	    if (sentCount != size)
	    {
	    	return XST_FAILURE;
	    }

	    return XST_SUCCESS;
}

void SendHandler(void *CallBackRef, unsigned int EventData)
{
    TotalSentCount = EventData;
    xil_printf("TotalSentCount : 0x%X\r\n", TotalSentCount);
}
void RecvHandler(void *CallBackRef, unsigned int EventData)
{
	if((RecvBuffer[0] == flagByte) |(RecvBuffer[0] != '\0') ){
		vector_add(&dataVector,RecvBuffer[0]);
		handleType=1;
		XUartLite_DisableInterrupt(&uartCtr);
	}
	else{
		handleType=0;
	}
    TotalReceivedCount = EventData;
    xil_printf("REC COUNT : 0x%X\r\n", TotalReceivedCount);
}
void printBuffer(u8 buffer[MAX_BUFFER_SIZE], char* exp){
	unsigned char * sendData;
	sendData = buffer;
	xil_printf("%s : %s\r\n",exp, sendData);
}
