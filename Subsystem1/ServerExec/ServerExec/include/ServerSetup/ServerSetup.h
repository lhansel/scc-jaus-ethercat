//#include "pthread.h"
#include <winsock.h>
#include <stdio.h>
#include <windows.h>
#include "MessageHeader.h"

extern "C" {
	#include "JausUnsignedShort.h"
	//#include "JausSignedLong.h"
	//#include "SetComponentAuthority.h"
}

class ServerSetup
{
public:
	ServerSetup::ServerSetup(void);
	int ServerSetup::initializeServer();
	void ServerSetup::sendMessage(char* msg,int msgSize,SOCKADDR_IN* sockAddrInSendTo);
};
