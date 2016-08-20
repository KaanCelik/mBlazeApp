/*
 * LcdController.c
 *
 *  Created on: 13 Aðu 2016
 *      Author: KaaN
 */
#include "LcdController.h"


XUartLite lcdUart;
StringArray* stringDataTable;

const char escSeq[3] = {0x1B,'[', '\0'};
u16* currentRow;

u32 lcd_init(u32 deviceId){
	u32 status;
	status = initUartController(&lcdUart,deviceId );
	return status;
	//construct(&lcdBuffer);
}


void lcd_setBuffer(StringArray* processedStrings){
	//calculateDisplayMatrix(Vector* byteVector);
	stringDataTable = processedStrings;
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
