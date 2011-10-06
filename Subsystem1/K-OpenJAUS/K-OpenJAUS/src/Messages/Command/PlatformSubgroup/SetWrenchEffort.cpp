#include "SetWrenchEffort.h"
#include "stdafx.h"


void printSetWrenchEffort(SetWrenchEffortMessage & SWEmsg) {
	printf("\n");
    printf("-Header---------------------------------\n");
    printf("Message Properties                  : %d\n", SWEmsg.jausMsgHdr.MessageProperties);
    printf("Command Code                        : %d\n", SWEmsg.jausMsgHdr.CommandCode);
    printf("Destination Instance ID             : %d\n", SWEmsg.jausMsgHdr.DestinationInstanceID);
    printf("Destination Component ID            : %d\n", SWEmsg.jausMsgHdr.DestinationComponentID);
    printf("Destination Node ID                 : %d\n", SWEmsg.jausMsgHdr.DestinationNodeID);
    printf("Destination Subsystem ID            : %d\n", SWEmsg.jausMsgHdr.DestinationSubsystemID);
    printf("Source Instance ID                  : %d\n", SWEmsg.jausMsgHdr.SourceInstanceID);
    printf("Source Component ID                 : %d\n", SWEmsg.jausMsgHdr.SourceComponentID);
    printf("Source Node ID                      : %d\n", SWEmsg.jausMsgHdr.SourceNodeID);
    printf("Source Subsystem ID                 : %d\n", SWEmsg.jausMsgHdr.SourceSubsystemID);
    printf("Data Control                        : %d\n", SWEmsg.jausMsgHdr.DataControl);
    printf("Sequence Number                     : %d\n", SWEmsg.jausMsgHdr.SequenceNumber);
    printf("-Body-----------------------------------\n");
	printf("Presence Vector                     : %d\n", SWEmsg.PresenceVector);
    printf("Propulsive Linear Effort X          : %d\n", SWEmsg.PropulsiveLinearEffortX);
    printf("Propulsive Linear Effort Y          : %d\n", SWEmsg.PropulsiveLinearEffortY);
    printf("Propulsive Linear Effort Z          : %d\n", SWEmsg.PropulsiveLinearEffortZ);
    printf("Propulsive Rotational Effort X      : %d\n", SWEmsg.PropulsiveRotationalEffortX);
    printf("Propulsive Rotational Effort Y      : %d\n", SWEmsg.PropulsiveRotationalEffortY);
    printf("Propulsive Rotational Effort Z      : %d\n", SWEmsg.PropulsiveRotationalEffortZ);
    printf("Resistive Linear Effort X           : %d\n", SWEmsg.ResistiveLinearEffortX);
    printf("Resistive Linear Effort Y           : %d\n", SWEmsg.ResistiveLinearEffortY);
    printf("Resistive Linear Effort Z           : %d\n", SWEmsg.ResistiveLinearEffortZ);
    printf("Resistive Rotational Effort X       : %d\n", SWEmsg.ResistiveRotationalEffortX);
    printf("Resistive Rotational Effort Y       : %d\n", SWEmsg.ResistiveRotationalEffortY);
    printf("Resistive Rotational Effort Z       : %d\n", SWEmsg.ResistiveRotationalEffortZ);
	
}