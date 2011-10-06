#ifndef _SETWRENCHEFFORT
#define _SETWRENCHEFFORT

#include <stdlib.h>
#include <string.h>
#include "JausMessageHeader.h"

struct SetWrenchEffortMessage
{
    JausMessageHeader jausMsgHdr;
    UINT16 PresenceVector;
    INT16 PropulsiveLinearEffortX;
    INT16 PropulsiveLinearEffortY;
    INT16 PropulsiveLinearEffortZ;
    INT16 PropulsiveRotationalEffortX;
    INT16 PropulsiveRotationalEffortY;
    INT16 PropulsiveRotationalEffortZ;
    BYTE ResistiveLinearEffortX;
    BYTE ResistiveLinearEffortY;
    BYTE ResistiveLinearEffortZ;
    BYTE ResistiveRotationalEffortX;
    BYTE ResistiveRotationalEffortY;
    BYTE ResistiveRotationalEffortZ;
};

void printSetWrenchEffort(SetWrenchEffortMessage & SWEmsg);

#endif _SETWRENCHEFFORT