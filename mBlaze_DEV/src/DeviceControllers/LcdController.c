/*
 * LcdController.c
 *
 *  Created on: 13 Aðu 2016
 *      Author: KaaN
 */
#include "LcdController.h"



LcdController lcdCtr;
const char escSeq[3] = {0x1B,'[', '\0'};
u16* currentRow;

void lcd_construct(XUartLite* uartCtrPtr, u32 deviceId){
	lcdCtr.uartDeviceCtr = *uartCtrPtr;
	lcdCtr.lcdUartDeviceId=deviceId;
	lcdCtr.stringDataTable = NULL;
}

LcdController* lcd_getController(){
	return &lcdCtr;
}


void lcd_setBuffer(StringArray* processedStrings){
	//calculateDisplayMatrix(Vector* byteVector);
	lcdCtr.stringDataTable = processedStrings;
}


u32 displayRow(u16 rowIndex){

	char* bundle="";
	strcpy(bundle,escSeq);
	u32 status = 0;
	// implement send logic
	//sendString((u8*)getElement(stringDataTable,rowIndex),&lcdUart);
	return status;

}

void setViewToDefault(){
	u16 rowIndexArray[DISPLAY_MATRIX_ROW];

		int i;
		for(i=0;i<DISPLAY_MATRIX_ROW;i++){
			rowIndexArray[i]=i;
		}
		currentRow = rowIndexArray;
}
u32 displayRows(u16 *currDisplayedRows)
{
	u32 status;
    int i = 0;
    for (i = 0; i < DISPLAY_MATRIX_ROW; ++i) {
		status = displayRow(currDisplayedRows[i]);
	}
    return status;
}

u32 lcd_display() {
	setViewToDefault();
	u32 status;
    status = displayRows(currentRow);
    return status;
}



void setViewToNext() {
	int i;
	for (i = 0; i < DISPLAY_MATRIX_ROW; i++) {
		currentRow[i]++;
	}
}

void setViewToPrev() {
	int i;
	for (i = 0; i < DISPLAY_MATRIX_ROW; i++) {
		currentRow[i]--;
	}
}

u32 lcd_displayNext(){
	setViewToNext();
	u32 status;
	status = displayRow(*currentRow);
	return status;
}

u32 lcd_displayPrevious(){
	setViewToPrev();
	u32 status;
	status = displayRow(*currentRow);
	return status;
}

void lcd_clearDisplay(){

	strcpy(lcdCtr.lcdSendBuffer,(char*)escSeq);
	strcat(lcdCtr.lcdSendBuffer,"j");
	sendString((u8*)lcdCtr.lcdSendBuffer,&lcdCtr.uartDeviceCtr);
}
