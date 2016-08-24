/*
 * LcdController.c
 *
 *  Created on: 13 Aðu 2016
 *      Author: KaaN
 */
#include "LcdController.h"



LcdController lcdCtr;
const char escSeq[3] = {0x1B,'[', '\0'};


void lcd_construct(XUartLite* uartCtrPtr, u32 deviceId){
	lcdCtr.uartDeviceCtr = *uartCtrPtr;
	lcdCtr.lcdUartDeviceId=deviceId;
	arraylist_new(&lcdCtr.availRows,32);
	lcdCtr.currentViewRows = malloc(sizeof(u16)*DISPLAY_MATRIX_ROW);
	setViewToDefault();

}

LcdController* lcd_getController(){
	return &lcdCtr;
}


void lcd_setBuffer(arraylist_t* processedRows){
	//calculateDisplayMatrix(Vector* byteVector);
	lcdCtr.availRows = *processedRows;
}

void setViewToDefault(){
	
	int i;
	for(i=0;i<DISPLAY_MATRIX_ROW;i++){
		lcdCtr.currentViewRows[i]=i;
	}	
}

u32 displayRow(u16 rowIndex){

	char* bundle="";
	strcpy(bundle,escSeq);
	u32 status = 0;
	// implement send logic
	//sendString((u8*)getElement(stringDataTable,rowIndex),&lcdUart);
	return status;

}


u32 displayRows()
{
	u32 status;
    int i = 0;
    for (i = 0; i < DISPLAY_MATRIX_ROW; ++i) {
		status = displayRow(lcdCtr.currentViewRows[i]);
	}
    return status;
}

u32 lcd_display() {
	setViewToDefault();
	u32 status;
    status = displayRows();
    return status;
}



void setViewToNext() {
	int i;
	for (i = 0; i < DISPLAY_MATRIX_ROW; i++) {
		lcdCtr.currentViewRows[i]++;
	}
}

void setViewToPrev() {
	int i;
	for (i = 0; i < DISPLAY_MATRIX_ROW; i++) {
		lcdCtr.currentViewRows[i]--;
	}
}

u32 lcd_displayNext(){
	setViewToNext();
	u32 status = 0;
	//status = displayRow(*lcdCtr.currentViewRows);
	return status;
}

u32 lcd_displayPrevious(){
	setViewToPrev();
	u32 status;
	status = displayRow(*lcdCtr.currentViewRows);
	return status;
}

void lcd_clearDisplay(){

	strcpy(lcdCtr.lcdSendBuffer,(char*)escSeq);
	strcat(lcdCtr.lcdSendBuffer,"j");
	sendString((u8*)lcdCtr.lcdSendBuffer,&lcdCtr.uartDeviceCtr);
}
