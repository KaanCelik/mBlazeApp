/*
 * Protocol.h
 *
 *  Created on: 04 May 2016
 *      Author: KaaN
 *  Implementation of data transfer protocol.
 *  Creates data packet with frames and CRC checksum.
 */

#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include "xbasic_types.h"

char flagByte;
char escByte;
typedef struct Packet{
	u8* buffer;
	int size;
	char* rawData;
	int rawSize;
}Packet;


Packet packet;

void constructPacket(Packet * packetPtr);

#endif /* PROTOCOL_H_ */


