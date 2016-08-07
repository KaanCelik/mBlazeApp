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
#include "Utilities/Util.h"
#include "DeviceControllers/IntrController.h"
#include "DeviceControllers/BramController.h"
#include "Bluetooth.h"

/*** Devices *****************************************************/
XGpio GpioOutput;
XGpio GpioInput;
XUartLite uartCtr_1;
/*** Variables *****************************************************/

/*** Methods ******************************************************/
Xuint32 initLed();
Xuint32 initSwitch();
u8 saveUserInput();
/******************************************************************/

int main()
{
	//Initialize basic setup
	/***************************************************************/
	int Status;
	init_platform();
	xil_printf("%c[2J", 27);
	/***************************************************************/
	//Input Output Devices
	/***************************************************************/
	Status = initLed();
	checkStatus(Status);
	Status =initSwitch();
	checkStatus(Status);
	/***************************************************************/
	//Bram Controller
	/***************************************************************/
	brc_selfTestBramController();

	//brc_selfTestBramController('A');
	//brc_selfTestBramController('B');
	/***************************************************************/
	//UartLite
	/***************************************************************/
	xil_printf("Uart Status : 0x%X\r\n", Status);
	Status = initUartController(&uartCtr_1,XPAR_AXI_UARTLITE_1_DEVICE_ID );
	xil_printf("Uart_1 Status : 0x%X\r\n", Status);
	/***************************************************************/
	//Bluetooth
	/***************************************************************/
	Status = bt_setUp(XPAR_UARTLITE_0_DEVICE_ID);
	checkStatus(Status);
	/***************************************************************/
	//Interrupt Controller.
	/***************************************************************/
	Status = initInterruptSystem();
	connectInterrupts(bt_getPtr(),XPAR_INTC_0_UARTLITE_0_VEC_ID,(XInterruptHandler)XUartLite_InterruptHandler);
	startIntrController();
	enableIntrController();
	checkStatus(Status);
	microblaze_enable_interrupts();
	/***************************************************************/
	//Setup Uart Intr Handlers
	/***************************************************************/
	bt_setUpIntr();
	bt_start(1);
	/***************************************************************/

	XUartLite_DisableInterrupt(&uartCtr_1);
	brc_init();
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
						bt_send("This is a test.");
						//Status = sendString((unsigned char *)"This is a test.",&blueToothUartCtr);
						checkSendSuccess(Status);
					}
					if(switchInput==2){
						Status = saveUserInput();
						printStatus("User Input Received. XST_STATUS : ", Status );
						//printBuffer(RecvBuffer,"Received Buffer");
					}
					if(switchInput==4){
						brc_selfTestBramController();
					}
					if(switchInput==8){
						//printVector(&dataVector);
					}
					if(switchInput==16){
						bt_send("AT");
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

u8 saveUserInput(){
	u8 success = FALSE;
	u8 status;
	if (bt_getPacketFlag() == TRUE) {
		Vector* btStack = bt_getStack();
		status = brc_saveStack(btStack);
		checkStatus(status);
		bt_setPacketFlag(FALSE);
		Vector* brStack = brc_getStack();
		printVectorWithName(btStack, "btVector : ");
		printVectorWithName(brStack, "brVector : ");
		Vector* brLastPacket = vector_split(brStack, btStack->count);
		success = vector_equals(btStack, brLastPacket);
		vector_destruct(brLastPacket);
	}
	if (success) {
		return XST_SUCCESS;
	} else {
		return XST_FAILURE;
	}

}








