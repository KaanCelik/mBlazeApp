/*
 * IntrController.c
 *
 *  Created on: 06 May 2016
 *      Author: KaaN
 */
#include "IntrController.h"

XIntc IntrCtr;

int initInterruptSystem()
{
	int Status;
	Status = XIntc_Initialize(&IntrCtr, XPAR_AXI_INTC_0_DEVICE_ID);
	checkStatus(Status);
	return XST_SUCCESS;
}
void enableIntrController() {
	XIntc_Enable(&IntrCtr, XPAR_AXI_INTC_0_AXI_TIMER_0_INTERRUPT_INTR);
	XIntc_Enable(&IntrCtr, XPAR_INTC_0_UARTLITE_0_VEC_ID);
	Xil_ExceptionInit();
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
				(Xil_ExceptionHandler)XIntc_InterruptHandler,
				&IntrCtr);
	Xil_ExceptionEnable();
}
int connectInterrupts(void* intrSrcPtr, u16 intrVecId,XInterruptHandler intrSrcHandler){
	int status;
	status = XIntc_Connect(&IntrCtr, intrVecId,intrSrcHandler,intrSrcPtr);
	return status;
}

int startIntrController(){
	int status;
	status = XIntc_Start(&IntrCtr, XIN_REAL_MODE);
	return status;
}

void printIntcProperties() {
	u32 ISR = XIntc_In32((&IntrCtr)->BaseAddress + XIN_ISR_OFFSET);
	u32 IER = XIntc_In32((&IntrCtr)->BaseAddress + XIN_IER_OFFSET);
	u32 IPR = XIntc_In32((&IntrCtr)->BaseAddress + XIN_IPR_OFFSET);
	u32 IAR = XIntc_In32((&IntrCtr)->BaseAddress + XIN_IAR_OFFSET);
	u32 MER = XIntc_In32((&IntrCtr)->BaseAddress + XIN_MER_OFFSET);
	xil_printf("ISR Reg : 0x%X  IER : 0x%X  IPR : 0x%X IAR : 0x%X  MER : 0x%X\r\n",ISR,IER,IPR,IAR,MER );
}
