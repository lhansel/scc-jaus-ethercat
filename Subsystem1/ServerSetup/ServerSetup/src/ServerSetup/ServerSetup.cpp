// This is a SERVER that handles the message sending using Socket

#include "stdafx.h"
//#include <memory>
#include "ServerSetup.h"
#define MAX_BUFFER_SIZE 4112 // MessageHeader(16) + NullTerminatingChar(1) + MaxMessageBody(4095)

WSADATA wsaData;
//CLIENT Socket
SOCKET clientSocket;
int clientSock;
//SERVER Socket
SOCKADDR_IN sockAddrInServer;

ServerSetup::ServerSetup(void) {}

//Initializes the CLIENT and SERVER
int ServerSetup::initializeServer() {
    //Initializes the Winsock version 1.1
    if(WSAStartup(MAKEWORD(1,1),&wsaData) != 0) {
            fprintf(stderr,"WSAStartup failed.\n");
            WSACleanup();
            return -1;
    }
    
    //Initializes the CLIENT (the other system)  socket: connection-less using UDP
    if( (clientSocket = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP)) == -1 ) {
        fprintf(stderr,"Could not open CLIENT socket\n");
        WSACleanup();
        return -1;
    }
    
    //The SERVER (this system) socket information
	sockAddrInServer.sin_family = AF_INET;
	sockAddrInServer.sin_addr.s_addr = htonl(INADDR_ANY);
    sockAddrInServer.sin_port = htons(23456);
    
    //Binds the SERVER (this system) socket to the local address
    if((clientSock = bind(clientSocket,(struct sockaddr*)&sockAddrInServer,
			sizeof(struct sockaddr))) == SOCKET_ERROR) {
        fprintf(stderr,"Could not bind client with server\n");
        WSACleanup();
        return -1;
    }
    
    return 0;
}

// Sends a message to the CLIENT (the other system)
void ServerSetup::sendMessage(char* msg,int msgSize,SOCKADDR_IN* sockAddrInSendTo) {
    printf("Sending message : %s\n",msg);
	if((clientSock = sendto(clientSocket,msg,msgSize,0,
			(struct sockaddr*)sockAddrInSendTo,sizeof(*sockAddrInSendTo))) == -1) {
        fprintf(stderr,"Could not send the message to the client\n");
        closesocket(clientSocket);
        WSACleanup();
    }
}

//int main(int argc,const char* argv[]) {
//    char ch;                        // handles user input 
//    char buffer[MAX_BUFFER_SIZE];   // sufficient to handle one line 
//    int char_count;                 // number of characters read for this line 
//    bool running = true;            // continue or stop the message exchange 
//
//    ServerSetup *c = new ServerSetup();
//    //If the returned value is not 0, there are problems with WSAStartup and Socket Opening/Binding 
//    if(c->initializeServer() != 0) {
//        printf("Could not start the server. We're really sorry.\n");
//    }
//    else {
//        while(running) {
//            printf("Enter a number to send a message: 1034 (Set Travel Speed): \n");
//            ch = getchar();
//            char_count = 0;
//            while( (ch != '\n') && (char_count < MAX_JAUS_MESSAGE_SIZE) ) {
//                buffer[char_count++] = ch;
//                ch = getchar();
//            }
//            //Null terminating buffer
//            buffer[char_count] = 0x00;
//            //Quit the connection
//            if(char_count == 1 && buffer[0] == 'q') {
//                running = false;
//            }
//            else {			    
//				//#define SET_TRAVEL_SPEED_CODE 1034
//				//#define SET_TRAVEL_SPEED_LENGTH 2
//				if(char_count == 4 && buffer[0] == '1' && buffer[1] == '0' && buffer[2] == '3' && buffer[3] == '4' ) {
//				    //Message Header
//				    unsigned char* msgHeader = MessageHeader::createMessageHeader(
//					    10,0,0,0,JAUS_VERSION,0,SET_TRAVEL_SPEED_CODE,0,0,0,2,0,0,0,1,
//					    SET_TRAVEL_SPEED_LENGTH,0,0);
//					//Message Body
//		            static unsigned short parameterValues[] = {36003};
//		            unsigned char* msg = SetTravelSpeed::createSetTravelSpeed(msgHeader, parameterValues[0]);
//		            
//		            //The CLIENT (the other system) socket information
//				    SOCKADDR_IN sockSendTo;
//				    sockSendTo.sin_family = AF_INET;
//				    sockSendTo.sin_addr.s_addr = inet_addr("127.0.0.1");
//				    sockSendTo.sin_port = htons(23455);
//				    
//				    //Sending the message
//                    c->sendMessage((char*)msg,JAUS_MESSAGE_HEADER_LENGTH 
//                        + SET_TRAVEL_SPEED_LENGTH + 1,&sockSendTo);
//				    free(msg);
//				}
//				else {
//				    printf("Invalid message code!");
//				}			
//            }
//        }
//        printf("Exiting program...\n");
//        return 0;
//    }
//    getchar();
//}