/*
 * LcdDecorator.c
 *
 *  Created on: 14 Aðu 2016
 *      Author: KaaN
 */
#include "LcdDecorator.h"
#include <stdio.h>

LcdConfig config;
char* stringPtrArray[DISPLAY_MATRIX_COL];
u16	displayTableRowCount = 0;

void construct(){
	int i = 0;
	for(i=0;i<DISPLAY_MATRIX_ROW_MAX; i++){
		stringPtrArray[i] = malloc(sizeof(char*));
		displayTableRowCount++;
	}
}
void destruct(){
	int i = 0;
	for (i = 0; i < DISPLAY_MATRIX_ROW_MAX; i++) {
		free(stringPtrArray[i]);
		displayTableRowCount--;
	}
}

LcdConfig* getLcdConfigPtr(){
	return &config;
}


char** getDisplayMatrixPtr(){
	return (char**) stringPtrArray;
}

void calculateDisplayMatrix(Vector* byteVector){
/*
	int i,r=0;
	for (i = 0; i < byteVector->count; i++) {
		char tempStr[6];

		lcd_decode(*(vector_getElement(byteVector, i)) , tempStr);
		if((strlen(tempStr)+strlen(&displayMatrix[r]))>=DISPLAY_MATRIX_COL){
			r++;
			i--;
			continue;
		}
		strncat(&displayMatrix[r],tempStr,strlen(tempStr));
	}
	*/
}


void lcd_decode(u8 inputData, char* resultStr){
	
	switch (config.displayMode) {
	case HEX:
		sprintf(resultStr, "0x%X", inputData);
		break;
	case DECIMAL:
		sprintf(resultStr, "%u", inputData);
		break;
	case CHAR:
		sprintf(resultStr, "%s", (char *) &inputData);
		break;
	default:
		sprintf(resultStr, "0x%X", inputData);
		break;
	
	}
}

void changeDisplayMode(int dispMode){
	switch (dispMode) {
	case HEX:
		config.displayMode = HEX;
		break;
	case DECIMAL:
		config.displayMode = DECIMAL;
		break;
	case CHAR:
		config.displayMode = CHAR;
		break;
	default:
		config.displayMode = HEX;
		break;
	}
}

char* getRow(int i){
	return &(stringPtrArray[i]);
}
