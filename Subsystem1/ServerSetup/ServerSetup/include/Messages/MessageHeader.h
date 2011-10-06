#ifndef _MESSAGEHEADER
#define _MESSAGEHEADER

#include <stdio.h>
#include <stdlib.h>

#define MAX_JAUS_MESSAGE_SIZE 4095

// the current Jaus version
// 2 corresponds to JAUS v3.3
#define JAUS_VERSION 2

// number of 8-bit bytes for the JAUS 
// Message header length
#define JAUS_MESSAGE_HEADER_LENGTH 16

// Definitions for JAUS Command Messages
// Platform Subgroup
#define SET_TRAVEL_SPEED_CODE 1034
#define SET_TRAVEL_SPEED_LENGTH 2

#define SET_WRENCH_EFFORT_CODE 1029
#define SET_WRENCH_EFFORT_LENGTH 20

class MessageHeader {

public:
    // be sure to include a name here, not just a generic
    // definition to avoid redefinition errors when this
    // is included in multiple, other files.

    MessageHeader::MessageHeader(void);

	static unsigned char* MessageHeader::createMessageHeader(
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
		 unsigned short seqNumber);

	static unsigned char MessageHeader::getPriority(unsigned char* msg);
	static unsigned char MessageHeader::getAcknak(unsigned char* msg);
	static unsigned char MessageHeader::getServiceConn(unsigned char* msg);
	static unsigned char MessageHeader::getExpFlag(unsigned char* msg);
	static unsigned char MessageHeader::getJausVer(unsigned char* msg);
	static unsigned char MessageHeader::getReserved(unsigned char* msg);

	static unsigned short MessageHeader::getCoreMessages(unsigned char* msg);

	static unsigned char MessageHeader::getDestInstance(unsigned char* msg);
	static unsigned char MessageHeader::getDestComp(unsigned char* msg);
	static unsigned char MessageHeader::getDestNode(unsigned char* msg);
	static unsigned char MessageHeader::getDestSub(unsigned char* msg);

	static unsigned char MessageHeader::getSrcInstance(unsigned char* msg);
	static unsigned char MessageHeader::getSrcComp(unsigned char* msg);
	static unsigned char MessageHeader::getSrcNode(unsigned char* msg);
	static unsigned char MessageHeader::getSrcSub(unsigned char* msg);

	static unsigned short MessageHeader::getDataSize(unsigned char* msg);
	static unsigned char MessageHeader::getDataFlag(unsigned char* msg);

	static unsigned short MessageHeader::getSeqNumber(unsigned char* msg);

    static void MessageHeader::printJausMessageHeaderArray(unsigned char* msg);
	static void MessageHeader::printJausMessageHeaderValues(unsigned char* msg);



};

#endif _MESSAGEHEADER