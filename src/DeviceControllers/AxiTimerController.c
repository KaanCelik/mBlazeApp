/*
 * AxiTimerController.c
 *
 *  Created on: 06 May 2016
 *      Author: KaaN
 */
#include "xtmrctr.h"
#include "xparameters.h"
#include "xil_types.h"
#include "AxiTimerController.h"

#define RESET_VALUE	0x04FAF080

XTmrCtr axiTimerCtr;
unsigned int axiTimerBaseAddress;

int initAxiTimer() {
	XTmrCtr_Config *TmrCtrConfigPtr;
	TmrCtrConfigPtr = XTmrCtr_LookupConfig(XPAR_AXI_TIMER_0_DEVICE_ID);
	axiTimerBaseAddress = TmrCtrConfigPtr->BaseAddress;

	Xuint32 status = XTmrCtr_Initialize(&axiTimerCtr, XPAR_AXI_TIMER_0_DEVICE_ID);
		if(status == XST_DEVICE_IS_STARTED){
			killTimer();
			status = XTmrCtr_Initialize(&axiTimerCtr, XPAR_AXI_TIMER_0_DEVICE_ID);
			if(status == XST_FAILURE){
					return XST_FAILURE;
				}
		}
		if(status == XST_FAILURE){
			return XST_FAILURE;
		}
	// end init

	XTmrCtr_SetHandler(&axiTimerCtr, Timer_InterruptHandler, &axiTimerCtr);
	XTmrCtr_SetOptions(&axiTimerCtr, 0, XTC_INT_MODE_OPTION | XTC_DOWN_COUNT_OPTION);
	return XST_SUCCESS;
}

void Timer_InterruptHandler(void *CallBackRef, u8 tmrCtrId)
{
	XTmrCtr_Stop (&axiTimerCtr, 0);
	XTmrCtr_SetResetValue(&axiTimerCtr, 0, RESET_VALUE);
	XTmrCtr_Start(&axiTimerCtr, 0);
}
void killTimer(){

	XTmrCtr_Disable(axiTimerBaseAddress, 0);
}
void printTimerSettings() {
	u32 tmrSettings = XTmrCtr_ReadReg(axiTimerBaseAddress,0,XTC_TCSR_OFFSET);

	xil_printf("Timer : 0x%X  ", tmrSettings&XTC_CSR_ENABLE_TMR_MASK);
	xil_printf("Intr : 0x%X  ", tmrSettings&XTC_CSR_ENABLE_INT_MASK);
	xil_printf("AutoReload : 0x%X  ", tmrSettings&XTC_CSR_AUTO_RELOAD_MASK);
	xil_printf("Count Down : 0x%X\r\n", tmrSettings&XTC_CSR_DOWN_COUNT_MASK);
}
