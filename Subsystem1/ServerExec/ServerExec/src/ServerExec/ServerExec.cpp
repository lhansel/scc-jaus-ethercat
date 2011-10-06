#include "stdafx.h"
#include "ServerSetup.h"
#define MAX_BUFFER_SIZE 4112 // MessageHeader(16) + NullTerminatingChar(1) + MaxMessageBody(4095)

int main(int argc,const char* argv[]) {
    char ch;                        // handles user input 
    char buffer[MAX_BUFFER_SIZE];   // sufficient to handle one line 
    int char_count;                 // number of characters read for this line 
    bool running = true;            // continue or stop the message exchange 

    ServerSetup* serverSetup = new ServerSetup();
    //If the returned value is not 0, there are problems with WSAStartup and Socket Opening/Binding 
    if(serverSetup->initializeServer() != 0) {
        printf("Could not start the server. We're really sorry.\n");
    }
    else {
        while(running) {
            printf("Enter a number to send a message: 1034 (Set Travel Speed), 1029 (Set Wrench Effort): \n");
            ch = getchar();
            char_count = 0;
            while( (ch != '\n') && (char_count < MAX_JAUS_MESSAGE_SIZE) ) {
                buffer[char_count++] = ch;
                ch = getchar();
            }
            //Null terminating buffer
            buffer[char_count] = 0x00;
            //Quit the connection
            if(char_count == 1 && buffer[0] == 'q') {
                running = false;
            }
            else {			    
				//#define SET_TRAVEL_SPEED_CODE 1034
				//#define SET_TRAVEL_SPEED_LENGTH 2
				/*if(char_count == 4 && buffer[0] == '1' && buffer[1] == '0' && buffer[2] == '3' && buffer[3] == '4' ) {
				    //Message Header
				    unsigned char* msgHeader = MessageHeader::createMessageHeader(
					    10,0,0,0,JAUS_VERSION,0,SET_TRAVEL_SPEED_CODE,0,0,0,2,0,0,0,1,
					    SET_TRAVEL_SPEED_LENGTH,0,0);
					//Message Body
		            static unsigned short parameterValues[] = {36003};
		            unsigned char* msg = SetTravelSpeed::createSetTravelSpeed(msgHeader, parameterValues[0]);
		            
		            //The CLIENT (the other system) socket information
				    SOCKADDR_IN sockSendTo;
				    sockSendTo.sin_family = AF_INET;
				    sockSendTo.sin_addr.s_addr = inet_addr("127.0.0.1");
				    sockSendTo.sin_port = htons(23455);
				    
				    //Sending the message
                    serverSetup->sendMessage((char*)msg,JAUS_MESSAGE_HEADER_LENGTH 
                        + SET_TRAVEL_SPEED_LENGTH + 1,&sockSendTo);
				    free(msg);
				}*/
				/*else*/if(char_count == 4 && buffer[0] == '1' && buffer[1] == '0' && buffer[2] == '2' && buffer[3] == '9' ) {
				    //Message Header
		            SetWrenchEffortMessage swe;
		            // XX|XXXXXX|X|X|XX|XXXX => 00|000011|0|0|00|0101 => 773 (DEC) => 305 (HEX)
		            swe.jausMsgHdr.MessageProperties = 773;
		            swe.jausMsgHdr.CommandCode = SET_WRENCH_EFFORT_CODE;
		            swe.jausMsgHdr.DestinationInstanceID = 0;
		            swe.jausMsgHdr.DestinationComponentID = 0;
		            swe.jausMsgHdr.DestinationNodeID = 0;
		            swe.jausMsgHdr.DestinationSubsystemID = 2;
		            swe.jausMsgHdr.SourceInstanceID = 0;
		            swe.jausMsgHdr.SourceComponentID = 0;
		            swe.jausMsgHdr.SourceNodeID = 0;
		            swe.jausMsgHdr.SourceSubsystemID = 1;
		            swe.jausMsgHdr.DataControl = SET_WRENCH_EFFORT_LENGTH;
		            swe.jausMsgHdr.SequenceNumber = 0;
		            
		            //Message Body
		            swe.PresenceVector = 1;
		            swe.PropulsiveLinearEffortX = 2;
		            swe.PropulsiveLinearEffortY = 3;
		            swe.PropulsiveLinearEffortZ= 4;
		            swe.PropulsiveRotationalEffortX = 5;
		            swe.PropulsiveRotationalEffortY = 6;
		            swe.PropulsiveRotationalEffortZ = 7;
		            swe.ResistiveLinearEffortX = 8;
		            swe.ResistiveLinearEffortY = 9;
		            swe.ResistiveLinearEffortZ = 10;
		            swe.ResistiveRotationalEffortX = 11;
		            swe.ResistiveRotationalEffortY = 12;
		            swe.ResistiveRotationalEffortZ = 13;
		            
		            //The CLIENT (the other system) socket information
				    SOCKADDR_IN sockSendTo;
				    sockSendTo.sin_family = AF_INET;
				    sockSendTo.sin_addr.s_addr = inet_addr("128.0.0.1");
				    sockSendTo.sin_port = htons(23455);
				    
				    char* packet = (char *)&swe;
				    
				    //Sending the message
                    serverSetup->sendMessage((char*)packet, JAUS_MESSAGE_HEADER_LENGTH 
                        + SET_WRENCH_EFFORT_LENGTH, &sockSendTo);
				    //free(packet);
				}
            }
        }
        printf("Exiting program...\n");
        return 0;
    }
    getchar();
}