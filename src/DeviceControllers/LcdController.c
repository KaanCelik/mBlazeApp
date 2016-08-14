/*
 * LcdController.c
 *
 *  Created on: 13 Aðu 2016
 *      Author: KaaN
 */
#include "LcdController.h"
#include "UartController.h"

XUartLite lcdUart;
Vector lcdBuffer;
Vector displayVector;
u8 currentDisplayMode;
char* rows[DISPLAY_MATRIX_ROW];
const char escSeq[3] = {0x1B,'[', '\0'};
u16* currDisplayedRows;


u32 lcd_init(u32 deviceId){
	u32 status;
	status = initUartController(&lcdUart,deviceId );

	return status;
}

void decodeData(char* dest, u8 src) {
	switch (currentDisplayMode) {
	case HEX:
		sprintf(dest, "0x%X", src);
		break;
	case CHAR:
		sprintf(dest, "%s", (char *) &src);
		break;
	case DECIMAL:
		sprintf(dest, "%u", src);
		break;
	default:
		sprintf(dest, "0x%X", src);
		break;
	}

}
void calculateDisplayMatrix(){

	int i,r=0;
	for (i = 0; i < lcdBuffer.count; i++) {
		char* tempStr = "";
		decodeData(tempStr, *vector_getElement(&lcdBuffer, i));
		if((strlen(tempStr)+strlen(rows[r]))>=DISPLAY_MATRIX_COL){
			break;
		}
		strcat(rows[r],tempStr);
	}
}



void lcd_setBuffer(Vector* bfVector){
	vector_init(&lcdBuffer);
	vector_append(&lcdBuffer , bfVector);
	calculateDisplayMatrix();
}

/**
 * Displays the selected rows by sending the proper commands via
 * uart to the device.By default it moves the cursor to the beginning
 * and then puts the rows to display.Caller must call calculateDisplayMatrix()
 * method prior to this method.
 *
 *
 * @param 	rowIndexes is a array of integers. Specifies which exact rows
 * 			must be displayed.
 * @param 	len is the length of rowIndexes. Caller must specify it.
 * 			This parameter cannot exceed DISPLAY_MATRIX_ROW.
 *
 * @return	- XST_SUCCESS
 * 			- XST_FAILURE
 * @note
 */
u32 displayRows(u16* rowIndexes, int len){

	if(len>DISPLAY_MATRIX_ROW){
		return XST_INVALID_PARAM;
	}
	char* bundle="";
	strcpy(bundle,escSeq);
	int i;
	for(i=0;i<len;i++){
		sendString((u8*)rows[rowIndexes[i]],&lcdUart);
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
