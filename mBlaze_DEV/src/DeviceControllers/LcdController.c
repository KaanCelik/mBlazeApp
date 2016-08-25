/*
 * LcdController.c
 *
 *  Created on: 13 Aðu 2016
 *      Author: KaaN
 */
#include "LcdController.h"



LcdController lcdCtr;
const char escSeq[3] = {0x1B,'[', '\0'};

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

void lcd_construct(XUartLite* uartCtrPtr, u32 deviceId){
	lcdCtr.uartDeviceCtr = *uartCtrPtr;
	lcdCtr.lcdUartDeviceId=deviceId;
	arraylist_new(&lcdCtr.availRows,32);
	lcdCtr.currentViewRows = malloc(sizeof(u16)*DISPLAY_MATRIX_ROW);
	lcd_setViewToDefault();
	lcdCtr.displayMode = HEX;

}

LcdController* lcd_getController(){
	return &lcdCtr;
}


void lcd_setViewToDefault(){
	
	int i;
	for(i=0;i<DISPLAY_MATRIX_ROW;i++){
		lcdCtr.currentViewRows[i]=i;
	}	
}

u32 lcd_displayRow(u16 rowIndex){


	u32 status = 0;

	status = sendString((u8*) lcdCtr.availRows.items[rowIndex],&lcdCtr.uartDeviceCtr);
	return status;

}


u32 lcd_displayRows()
{
	u32 status;
    int i = 0;
    for (i = 0; i < DISPLAY_MATRIX_ROW; ++i) {
		status = lcd_displayRow(lcdCtr.currentViewRows[i]);
	}
    return status;
}

u32 lcd_display() {
	lcd_setViewToDefault();
	u32 status;
    status = lcd_displayRows();
    return status;
}



u32 lcd_displayNext(){
	setViewToNext();
	u32 status = 0;
	status = lcd_displayRows(*lcdCtr.currentViewRows);
	return status;
}

u32 lcd_displayPrevious(){
	setViewToPrev();
	u32 status;
	status = lcd_displayRows(*lcdCtr.currentViewRows);
	return status;
}

void lcd_clearDisplay(){

	strcpy(lcdCtr.lcdSendBuffer,(char*)escSeq);
	strcat(lcdCtr.lcdSendBuffer,"j");
	sendString((u8*)lcdCtr.lcdSendBuffer,&lcdCtr.uartDeviceCtr);
}


void lcd_byteToString(u8 byte, char* resultStr){
	
	switch (lcdCtr.displayMode) {
	case HEX:
		sprintf(resultStr, "0x%X", byte);
		break;
	case DECIMAL:
		sprintf(resultStr, "%u", byte);
		break;
	case CHAR:
		sprintf(resultStr, "%s", (char *) &byte);
		break;
	default:
		sprintf(resultStr, "0x%X", byte);
		break;
	
	}
}

void lcd_changeDisplayMode(int dispMode){
	switch (dispMode) {
	case HEX:
		lcdCtr.displayMode = HEX;
		break;
	case DECIMAL:
		lcdCtr.displayMode = DECIMAL;
		break;
	case CHAR:
		lcdCtr.displayMode = CHAR;
		break;
	default:
		lcdCtr.displayMode = HEX;
		break;
	}
}

void lcd_setByteVector(Vector* bytes){
	lcdCtr.byteVector = *bytes;
}

void lcd_generateRows(){

	int i = 0;
	for(i=0;i<lcdCtr.byteVector.count;i++){
		char* rowStr = malloc(sizeof(char)*DISPLAY_MATRIX_COL);

		char* rowIndexStr=malloc(sizeof(char)*4);
		if(i>=100){
			sprintf(rowIndexStr,"%d : ",i);
		}else if (i>=10){
			sprintf(rowIndexStr,"%d  : ",i);
		}
		else{
			sprintf(rowIndexStr,"%d   : ",i);	
		}
				
		strcpy(rowStr,rowIndexStr);
		char* byteStr = malloc(sizeof(char)*5);

		lcd_byteToString(*vector_getElement(&lcdCtr.byteVector,i),byteStr);
		
		strcat(rowStr,byteStr);
		arraylist_push(&lcdCtr.availRows,rowStr);
	}

}