/*
 * LcdController.c
 *
 *  Created on: 13 Aðu 2016
 *      Author: KaaN
 */
#include "LcdController.h"


XUartLite lcdUart;
StringArray* lcdStrTablePtr;

const char escSeq[3] = {0x1B,'[', '\0'};
u16* currDisplayedRows;

u32 lcd_init(u32 deviceId){
	u32 status;
	status = initUartController(&lcdUart,deviceId );
	return status;
	//construct(&lcdBuffer);
}


void lcd_setBuffer(Vector* byteVector){
	//calculateDisplayMatrix(Vector* byteVector);
	lcdStrTablePtr = getLcdStringArray();
}


u32 displayRows(u16* rowIndexes, int len){

	if(len>DISPLAY_MATRIX_ROW){
		return XST_INVALID_PARAM;
	}
	char* bundle="";
	strcpy(bundle,escSeq);
	int i;
	for(i=0;i<len;i++){
		sendString((u8*)getElement(lcdStrTablePtr,i),&lcdUart);
	}
	return XST_SUCCESS;
}

void setViewToDefault(){
	u16 rowIndexArray[DISPLAY_MATRIX_ROW];
		int i;
		for(i=0;i<DISPLAY_MATRIX_ROW;i++){
			rowIndexArray[i]=i;
		}
		currDisplayedRows = rowIndexArray;
}
u32 lcd_display(){
	setViewToDefault();
	u32 status;
	status = displayRows(currDisplayedRows,DISPLAY_MATRIX_ROW);
	return status;
}



void setViewToNext() {
	int i;
	for (i = 0; i < DISPLAY_MATRIX_ROW; i++) {
		currDisplayedRows[i]++;
	}
}

void setViewToPrev() {
	int i;
	for (i = 0; i < DISPLAY_MATRIX_ROW; i++) {
		currDisplayedRows[i]--;
	}
}

u32 lcd_displayNext(){
	setViewToNext();
	u32 status;
	status = displayRows(currDisplayedRows,DISPLAY_MATRIX_ROW);
	return status;
}

u32 lcd_displayPrevious(){
	setViewToPrev();
	u32 status;
	status = displayRows(currDisplayedRows,DISPLAY_MATRIX_ROW);
	return status;
}
