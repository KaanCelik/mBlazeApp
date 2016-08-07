/*
 * BramController.c
 *
 *  Created on: 26 Tem 2016
 *      Author: KaaN
 */
#include "BramController.h"
#include "xbram.h"
#include "xparameters.h"
#include "../Utilities/Util.h"

const unsigned int BYTE_MASK[4] = {
	0xFF000000,
	0x00FF0000,
	0x0000FF00,
	0x000000FF};

XBram sharedBram;
XBram_Config* bramConfig;
u32 adressCounter;
u32 wordCounter;
Vector stack;
u32 getFreeAddress(){
	u32 newAddress = adressCounter;
	adressCounter= adressCounter+4;
	return newAddress;
}
u32 getCurrentAddress() {
	return adressCounter;
}

void resetBram(){
	adressCounter = 0;
	wordCounter = 0;
}

u8 brc_init(){
	u8 status;
	adressCounter = 0;
	wordCounter=0;
	bramConfig = XBram_LookupConfig(XPAR_AXI_BRAM_CTRL_0_DEVICE_ID);
	status = XBram_CfgInitialize(&sharedBram,bramConfig,XPAR_BRAM_1_BASEADDR);
	status = XBram_SelfTest(&sharedBram,0);
	checkStatus(status);
	return status;
}
void saveData(u32 inputData, u32 memOffset){
	XBram_WriteReg(sharedBram.Config.MemBaseAddress,memOffset,inputData);
}

u32 fetchData(u32 memOffset){
	u32 dataOut = XBram_ReadReg(sharedBram.Config.MemBaseAddress,memOffset);
	return dataOut;
}

void brc_selfTestBramController() {
	brc_init();
	u32 testInput1 = 'A';
	u32 testInput2 = 'B';
	xil_printf("Test input : 0x%X , 0x%X\r\n", testInput1,testInput2);

	u32 adr1 = getFreeAddress();
	u32 adr2 = getFreeAddress();
	saveData(testInput1,adr1);
	saveData(testInput2,adr2);
	u32 testOutput1 = fetchData(adr1);
	u32 testOutput2 = fetchData(adr2);
	xil_printf("Test Output : 0x%X , 0x%X\r\n", testOutput1,testOutput2);
}

int calcShift(int i)
{
    return ((3-(i % 4)) * 8);
}

u8 brc_saveStack(Vector* stack) {
	int i = 0;
	resetBram();
	u32 regData;
	for (i = 0; i < stack->count; i++) {
		if (i % 4 == 0) {
			regData = 0;
		}
		u32 data = (u32) *vector_getElement(stack, i);
		data = (data << calcShift(i)) & BYTE_MASK[i % 4];
		wordCounter++;
		regData = regData | data;
		if ((i % 4 == 3) || i == (stack->count - 1)) {
			u32 memAddress = getFreeAddress();
			saveData(regData, memAddress);
			u32 dataOnRam = fetchData(memAddress);
			if (dataOnRam != regData) {
				return XST_FAILURE;
			}
		}
	}

	return XST_SUCCESS;
}

Vector* brc_getStack() {
	int adr;
	u32 regData = 0;
	vector_init(&stack);
	u32 numWords = 0;
	for (adr = 0; adr < getCurrentAddress(); adr=adr+4) {

		regData = fetchData(adr);
		int i = 0;
		for (i = 0; i < 4; i++) {
			u32 maskedData = regData & BYTE_MASK[i];
			u8 data = (u8) (maskedData >> calcShift(i));
			numWords++;
			vector_push(&stack, data);
			if (numWords == wordCounter) {
				break;
			}
		}
		if (numWords == wordCounter) {
			break;
		}

	}
	return &stack;
}
