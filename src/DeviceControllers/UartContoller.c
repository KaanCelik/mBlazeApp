/*
 * UartContoller.c
 *
 *  Created on: 19 Haz 2016
 *      Author: KaaN
 */
#include "UartController.h"


u16 initUartController(XUartLite* uartPtr, u16 uartDeviceId){
	u16 Status;
	Status = XUartLite_Initialize(uartPtr,uartDeviceId);
	if (Status != XST_SUCCESS){return XST_FAILURE;}
	XUartLite_ResetFifos(uartPtr);
	Status = XUartLite_SelfTest(uartPtr);
	if (Status != XST_SUCCESS){return XST_FAILURE;}
	return Status;
}

u16 sendString(u8* data, XUartLite* uartPtr) {

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
	sentCount = XUartLite_Send(uartPtr, data, size);
	while(XUartLite_IsSending(uartPtr)){
		/*
		 * Sleep during the uart sends data
		 */
	}
	checkSendSuccess(sentCount - size);
	return XST_SUCCESS;
}

u32 rxHasValidData(XUartLite* uartPtr){
	u32 Status_Reg = XUartLite_GetStatusReg(uartPtr->RegBaseAddress);
	u32 isRxValidData = Status_Reg & XUL_SR_RX_FIFO_VALID_DATA;
	return isRxValidData;
}

void printUartLiteProperties(XUartLite* uartPtr) {
	u32 Status_Reg = XUartLite_GetStatusReg(uartPtr->RegBaseAddress);
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
