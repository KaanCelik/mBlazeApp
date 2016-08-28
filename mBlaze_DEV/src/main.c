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
#include "DeviceControllers/LcdController.h"
#include "Bluetooth.h"

/*** Devices *****************************************************/
XGpio GpioOutput;
XGpio GpioInput;
/*** Variables *****************************************************/

/*** Methods ******************************************************/
Xuint32 initLed();
Xuint32 initSwitch();
u8 saveUserInput();
/******************************************************************/

//TODO Implement Error Handling
/**
 * !!!!!!!!!!!!!! IMPLEMENT THIS  !!!!!!!!!!!!!!!!!
 * Seperate initialization code from main
 * Return an error code from each of these functions.
 * Error codes must be enumerated and stored in Errors.h header file
 * Implement an error code parser for the error codes.
 * Define a global variable holds the last error.
 * Call the appropreate error handling functin or shut down gracefully.
 */
int main()
{

	//Initialize basic setup
	/***************************************************************/
	int Status;
	init_platform();
	//xil_printf("%c[2J", 27);
	/***************************************************************/
	//Input Output Devices
	/***************************************************************/
	Status = initLed();
	assertStatus(Status,"LED initialization was unsuccesful.");
	Status =initSwitch();
	assertStatus(Status,"8 bit Switch initialization was unsuccesful.");
	/***************************************************************/
	//Bram Controller
	/***************************************************************/
	brc_init();
	/***************************************************************/
	//LcdController Setup
	/***************************************************************/
	XUartLite* lcdUart = malloc(sizeof(XUartLite));
	Status = constructUartController(lcdUart,XPAR_AXI_UARTLITE_1_DEVICE_ID);
	lcd_construct(lcdUart,XPAR_AXI_UARTLITE_1_DEVICE_ID);
	XUartLite_DisableInterrupt(lcdUart);
	assertStatus(Status,"LCD Uart initialization was unsuccesful.");
	/***************************************************************/
	//Bluetooth setup
	/***************************************************************/
	Status = bt_setUp(XPAR_UARTLITE_0_DEVICE_ID);
	xil_printf("bt setup executed.\r\n");
	checkStatus(Status);
	/***************************************************************/
	//Interrupt Controller.
	/***************************************************************/
	Status = initInterruptSystem();
	connectInterrupts(bt_getPtr(),XPAR_INTC_0_UARTLITE_0_VEC_ID,(XInterruptHandler)XUartLite_InterruptHandler);
	startIntrController();
	enableIntrController();
	assertStatus(Status,"Interrupt controller initialization was unsuccesful.");
	microblaze_enable_interrupts();
	/***************************************************************/
	//Setup Uart Intr Handlers
	/***************************************************************/
	bt_setUpIntr();
	//TODO Increase Interrupt handler sensitivity
	bt_start(16);
	/***************************************************************/

	/***************************************************************/
	//Main loop
	/***************************************************************/
	xil_printf("Entering Main Loop !\r\n");
	u32 oldSwitch = 0x0;
	while (1)
	{
			if (bt_isDataPresent()) {
				Status = saveUserInput();

				if (Status != XST_NO_DATA) {
					printStatus("User Input Received. XST_STATUS : ", Status);
				}

			}

			u32 switchInput = XGpio_DiscreteRead(&GpioInput,1);
			if(switchInput != 0){

				if(oldSwitch<switchInput){
					if(switchInput==128){
						break;
					}
					if(switchInput==1){
						bt_send("This is a test.");
						checkSendSuccess(Status);
					}
					if (switchInput == 2) {
						printVectorWithName(brc_getStack(),"Bram Stack : ");
					}
					if(switchInput==4){
						//Read data from BRAM and forward it to LCD.

						Vector* bramData = brc_getStack();
						xil_printf("Bram get stack executed.\r\n");
						if(bramData->count){
							lcd_setByteVector(bramData);
							xil_printf("got the byte vector.\r\n");
							lcd_generateRows();
							xil_printf("generated rows.\r\n");
							lcd_display();
						} else {
							xil_printf("No data in bram stack.\r\n");
						}
					}

					if(switchInput==8){
						lcd_clearDisplay();
					}
					if(switchInput==16){
						lcd_displayNext();
					}
					if(switchInput==32){
						LcdController* lcdCtrPtr = lcd_getController();
						xil_printf("got the byte vector.\r\n");
						arraylist_push(&lcdCtrPtr->availRows,"Jessie !");
						xil_printf("pushed something.\r\n");
						lcd_displayRow(lcdCtrPtr->availRows.len-1);
						xil_printf("display shit.\r\n");
					}
				}
			}
			oldSwitch = switchInput;
		}
	xil_printf("Program Aborted.\r\n");
	return 0;
}

Xuint32 initLed() {

	Xuint32 status = XGpio_Initialize(&GpioOutput, XPAR_LEDS_8BITS_DEVICE_ID);
	if(status == XST_SUCCESS){
		XGpio_SetDataDirection(&GpioOutput, 1, 0x0);
	}
	return status;
}
Xuint32 initSwitch() {

	Xuint32 status = XGpio_Initialize(&GpioInput, XPAR_DIP_SWITCHES_8BITS_DEVICE_ID);
	if(status == XST_SUCCESS){
		XGpio_SetDataDirection(&GpioInput, 1, 0xFFFFFFFF);
	}
	return status;
}

u8 saveUserInput(){
	//TODO Implement Basic commands and a parser for them
	u8 success = FALSE;
	u8 status;
	if (bt_isDataPresent() == TRUE) {
		Vector* btStack = bt_getStack();
		status = brc_saveStack(btStack);
		assertStatus(status,"Bram brc_saveStack() failed.")
		Vector* brStack = brc_getStack();
		Vector* brLastPacket = vector_split(brStack, btStack->count);
		success = vector_equals(btStack, brLastPacket);
		vector_destruct(brLastPacket);
		bt_resetStack();
		bt_setDataPresent(FALSE);
	}else{
		return XST_NO_DATA;
	}
	if (success) {
		return XST_SUCCESS;
	} else {
		return XST_FAILURE;
	}

}








