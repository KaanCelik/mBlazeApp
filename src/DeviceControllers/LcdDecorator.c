/*
 * LcdDecorator.c
 *
 *  Created on: 14 Aðu 2016
 *      Author: KaaN
 */
#include "LcdDecorator.h"
#include <stdio.h>

void lcd_decode(LcdConfig* configPtr, u8* inputData, char* dest){

	switch (configPtr->displayMode) {
	case HEX:
		sprintf(dest, "0x%X", *inputData);
		break;
	case CHAR:
		sprintf(dest, "%s", (char *) inputData);
		break;
	case DECIMAL:
		sprintf(dest, "%u", *inputData);
		break;
	default:
		sprintf(dest, "0x%X", *inputData);
		break;
	}

}
