/*
 * LcdDecorator.c
 *
 *  Created on: 14 Aðu 2016
 *      Author: KaaN
 */
#include "LcdDecorator.h"
#include <stdio.h>

void lcd_decode(LcdConfig* configPtr, u8 inputData, char* resultStr){
	
	switch (configPtr->displayMode) {
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
