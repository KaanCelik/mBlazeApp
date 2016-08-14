/*
 * LcdDecorator.c
 *
 *  Created on: 14 Aðu 2016
 *      Author: KaaN
 */
#include "LcdDecorator.h"
#include <stdio.h>

char* lcd_decode(LcdConfig* configPtr, u8 inputData){
	char * result= NULL;
	switch (configPtr->displayMode) {
	case HEX:
		sprintf(result, "0x%X", inputData);
		break;
	case CHAR:
		sprintf(result, "%s", (char *) &inputData);
		break;
	case DECIMAL:
		sprintf(result, "%u", inputData);
		break;
	default:
		sprintf(result, "0x%X", inputData);
		break;
	}
	return result;
}
