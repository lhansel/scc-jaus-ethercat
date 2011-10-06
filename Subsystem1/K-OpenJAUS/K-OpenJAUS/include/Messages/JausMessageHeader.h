#ifndef JAUS_MESSAGE_HEADER
#define JAUS_MESSAGE_HEADER

#include "stdafx.h"

struct JausMessageHeader
{
    UINT16 MessageProperties;
    UINT16 CommandCode;
    BYTE DestinationInstanceID;
    BYTE DestinationComponentID;
    BYTE DestinationNodeID;
    BYTE DestinationSubsystemID;
    BYTE SourceInstanceID;
    BYTE SourceComponentID;
    BYTE SourceNodeID;
    BYTE SourceSubsystemID;
    UINT16 DataControl;
    UINT16 SequenceNumber;
};

#endif JAUS_MESSAGE_HEADER