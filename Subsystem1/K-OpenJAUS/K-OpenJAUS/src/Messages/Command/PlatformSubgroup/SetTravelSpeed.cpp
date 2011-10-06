#include "stdafx.h"

SetTravelSpeed::SetTravelSpeed(void){};

// This creates a new SetTravelSpeed, which stores a pre-filled
// MessageHeader and the speed(data for this message)
unsigned char* SetTravelSpeed::createSetTravelSpeed(
		unsigned char* msg, unsigned short speed) {

	// add the data to the message
	msg[16] = speed & (0x00FF);
	msg[17] = (speed & (0xFF00)) >> 8;
	return msg;
}

// Pulls data for this message out of a message that includes the header and data
// and returns the data
unsigned char SetTravelSpeed::retrieveSetTravelSpeedData(unsigned char* msg) {
	return msg[16] + (msg[17] << 8);
}

void SetTravelSpeed::printSetTravelSpeedArray(unsigned char* msg) {
	printf("SetTravelSpeed\n");
	MessageHeader::printJausMessageHeaderValues(msg);
	printf("Speed[16]                  : %d\n\n",msg[16]);
	printf("Speed[17]                  : %d\n\n",msg[17]);
}