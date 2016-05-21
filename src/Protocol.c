/*
 * Protocol.c
 *
 *  Created on: 04 May 2016
 *      Author: KaaN
 *
 *  Implementation of data transfer protocol.
 *  Creates data packet with frames and CRC checksum.
 */

#include "Protocol.h"
#include "stdlib.h"

char flagByte = 0x7e;
char escByte  = 0x7d;

int extractPacketSize();
void constructPacket(Packet * packetPtr){
	packetPtr->size = extractPacketSize();
	unsigned char* tempBuffer = malloc(packetPtr->size * sizeof(unsigned char));

	int index;
	tempBuffer[packetPtr->size-1] = '\0';
	tempBuffer[packetPtr->size-2] = flagByte;
	int c=0;
	for (index = 0; index < packetPtr->size-2; index++){
		tempBuffer[packetPtr->size-3-index-c] = data[dataSize-index];
		if(data[dataSize-index] == '\0'){
					tempBuffer[packetPtr->size-3-index-c]= '#';
				}
		if((data[dataSize-index] == flagByte) | (data[dataSize-index] == escByte )){
			c++;
			tempBuffer[packetPtr->size-3-index-c]= escByte;
		}
	}
	tempBuffer[0] = flagByte;
	packetPtr->buffer = tempBuffer;
}

int extractPacketSize(){
	static int packetSize=0;
	int index;
	for (index = 0; index < dataSize; index++){
			if((data[index] == flagByte) | (data[index] == escByte )){
				packetSize++;
			}
			packetSize++;
		}
	packetSize = packetSize+4;//start - stop flags and string null pointer
	return packetSize;
}


