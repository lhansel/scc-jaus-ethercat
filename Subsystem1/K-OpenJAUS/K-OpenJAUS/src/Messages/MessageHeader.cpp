#include "MessageHeader.h"
#include "stdafx.h"

MessageHeader::MessageHeader(void){};

unsigned char* MessageHeader::createMessageHeader(
		 //Byte 0
		 unsigned char priority, unsigned char acknak, unsigned char serviceConn, unsigned char expFlag,
		 //Byte 1
		 unsigned char jausVer, unsigned char reserved,
		 //Byte 2 & 3
		 unsigned short coreMessages,
		 //Byte 4                    Byte 5                  Byte 6                  Byte 7
		 unsigned char destInstance, unsigned char destComp, unsigned char destNode, unsigned char destSub,
		 //Byte 8                   Byte 9                 Byte 10                Byte 11
		 unsigned char srcInstance, unsigned char srcComp, unsigned char srcNode, unsigned char srcSub,
		 //Byte 12                         Byte 13          
		 unsigned short dataSize, unsigned char dataFlag, 
		 //Byte 14 & 15
		 unsigned short seqNumber) {
		 
	unsigned char* header = (unsigned char*)calloc
			(JAUS_MESSAGE_HEADER_LENGTH + dataSize + 1,sizeof(unsigned char));

	// Message Properties Byte 1
	header[0] = (priority & 0x0f)
			| (((acknak) & 0x03) << 4)
			| (((serviceConn & 0x01) & 0xff) << 6)
			| (((expFlag) & 0x01) << 7);
	// Message Properties Byte 2
	header[1] = (jausVer & 0x3f)
		     | ((reserved & 0x03) << 6);
	// Command Code/Core Messages
	unsigned char* coreMessagesArray = JausUnsignedShort::jausUnsignedShortToCharArray(coreMessages);
	header[2] = coreMessagesArray[0];
	header[3] = coreMessagesArray[1];
	// Destination ID
	header[4] = destInstance;
	header[5] = destComp;
	header[6] = destNode;
	header[7] = destSub;
	// Source ID
	header[8] = srcInstance;
	header[9] = srcComp;
	header[10] = srcNode;
	header[11] = srcSub;
	// Data Control
	unsigned short dc = ((dataSize) & 0x0fff)
		             | (((dataFlag) << 12) & 0xf000);
	unsigned char* dataControl = JausUnsignedShort::jausUnsignedShortToCharArray(dc);	
	header[12] = dataControl[0];
	header[13] = dataControl[1];
	// Sequence Number
	unsigned char* seqNumberChar = JausUnsignedShort::jausUnsignedShortToCharArray(seqNumber);
	header[14] = seqNumberChar[0];
	header[15] = seqNumberChar[1];

	// add the null terminator character
	header[JAUS_MESSAGE_HEADER_LENGTH + dataSize] = '\0';

	return header;
}

unsigned char MessageHeader::getPriority(unsigned char* msg) {
	return (msg[0] & 0x0f);
}

unsigned char MessageHeader::getAcknak(unsigned char* msg) {
	return ((msg[0] >> 4) & 0x03);
}

unsigned char MessageHeader::getServiceConn(unsigned char* msg) {
	return ((msg[0] >> 6) & 0x01);
}

unsigned char MessageHeader::getExpFlag(unsigned char* msg) {
	return ((msg[0] >> 7) & 0x01);
}

unsigned char MessageHeader::getJausVer(unsigned char* msg) {
	return (msg[1] & 0x3f);
}

unsigned char MessageHeader::getReserved(unsigned char* msg) {
	return ((msg[1] >> 6) & 0x03);
}

unsigned short MessageHeader::getCoreMessages(unsigned char* msg) {
	return (JausUnsignedShort::charArrayToJausUnsignedShort(msg,2));
}

unsigned char MessageHeader::getDestInstance(unsigned char* msg) {
	return (msg[4]);
}

unsigned char MessageHeader::getDestComp(unsigned char* msg) {
	return (msg[5]);
}

unsigned char MessageHeader::getDestNode(unsigned char* msg) {
	return (msg[6]);
}

unsigned char MessageHeader::getDestSub(unsigned char* msg) {
	return (msg[7]);
}

unsigned char MessageHeader::getSrcInstance(unsigned char* msg) {
	return (msg[8]);
}

unsigned char MessageHeader::getSrcComp(unsigned char* msg) {
	return (msg[9]);
}

unsigned char MessageHeader::getSrcNode(unsigned char* msg) {
	return (msg[10]);
}

unsigned char MessageHeader::getSrcSub(unsigned char* msg) {
	return (msg[11]);
}

unsigned short MessageHeader::getDataSize(unsigned char* msg) {
	return ((msg[12] & 0xff) | ((msg[13] & 0x0f) << 12));	
}

unsigned char MessageHeader::getDataFlag(unsigned char* msg) {
	return ((msg[13] >> 4) & 0x0f);	
}

unsigned short MessageHeader::getSeqNumber(unsigned char* msg) {
	return (JausUnsignedShort::charArrayToJausUnsignedShort(msg,14));
}

//----------------------- KEEP THIS ONE ----------------------------------------
// This function prints out the contents of a MessageHeader after
// it has been converted to a JausByte* array.
void MessageHeader::printJausMessageHeaderArray(unsigned char* msg) {
	printf("Message Properties          [0] : %d,%u\n",msg[0],msg[0]);
	printf("Message Properties          [1] : %d,%u\n",msg[1],msg[1]);
	printf("Command Code/Core Messages  [2] : %d,%u\n",msg[2],msg[2]);
	printf("Command Code/Core Messages  [3] : %d,%u\n",msg[3],msg[3]);
	printf("Destination Instance        [4] : %d,%u\n",msg[4],msg[4]);
	printf("Destination Component       [5] : %d,%u\n",msg[5],msg[5]);
	printf("Destination Node            [6] : %d,%u\n",msg[6],msg[6]);
	printf("Destination Subsystem       [7] : %d,%u\n",msg[7],msg[7]);
	printf("Source Instance             [8] : %d,%u\n",msg[8],msg[8]);
	printf("Source Component            [9] : %d,%u\n",msg[9],msg[9]);
	printf("Source Node                [10] : %d,%u\n",msg[10],msg[10]);
	printf("Source Subsystem           [11] : %d,%u\n",msg[11],msg[11]);
	printf("Data Control               [12] : %d,%u\n",msg[12],msg[12]);
	printf("Data Control               [13] : %d,%u\n",msg[13],msg[13]);
	printf("Sequence Number            [14] : %d,%u\n",msg[14],msg[14]);
	printf("Sequence Number            [15] : %d,%u\n",msg[15],msg[15]);
}

void MessageHeader::printJausMessageHeaderValues(unsigned char* msg) {
	printf("Priority                  : %d\n",MessageHeader::getPriority(msg));
	printf("Ack/Nak                   : %d\n",MessageHeader::getAcknak(msg));
	printf("Service Connection        : %d\n",MessageHeader::getServiceConn(msg));
	printf("Experimental              : %d\n",MessageHeader::getExpFlag(msg));
	printf("Version                   : %d\n",MessageHeader::getJausVer(msg));
	printf("Reserved                  : %d\n",MessageHeader::getReserved(msg));
	printf("Command Code/Core Message : %d\n",MessageHeader::getCoreMessages(msg));
	printf("Destination Instance      : %d\n",MessageHeader::getDestInstance(msg));
	printf("Destination Component     : %d\n",MessageHeader::getDestComp(msg));
	printf("Destination Node          : %d\n",MessageHeader::getDestNode(msg));
	printf("Destination Subsystem     : %d\n",MessageHeader::getDestSub(msg));
	printf("Source Instance           : %d\n",MessageHeader::getSrcInstance(msg));
	printf("Source Component          : %d\n",MessageHeader::getSrcComp(msg));
	printf("Source Node               : %d\n",MessageHeader::getSrcNode(msg));
	printf("Source Subsystem          : %d\n",MessageHeader::getSrcSub(msg));
	printf("Data Size                 : %d\n",MessageHeader::getDataSize(msg));
	printf("Data Flag                 : %d\n",MessageHeader::getDataFlag(msg));
	printf("Sequence Number           : %d\n",MessageHeader::getSeqNumber(msg));
}
