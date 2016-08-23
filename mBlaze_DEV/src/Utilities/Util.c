/*
 * Util.c
 *
 *  Created on: 07 May 2016
 *      Author: KaaN
 */
#include "Util.h"

void printBuffer(u8* buffer, char* exp){
	unsigned char * sendData;
	sendData = buffer;
	xil_printf("%s : %s\r\n",exp, sendData);
	int i = 0;
	while(buffer[i]!='\0'){
		xil_printf("0x%X ",buffer[i]);
		i++;
	}
	if(buffer[i]=='\0'){xil_printf("\r\n");}
}
void printStatus(char* message, int status) {
	xil_printf("%s%d\r\n",message, status);
}
