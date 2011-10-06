//#include "pthread.h"
#include <winsock.h>
#include <stdio.h>
#include <windows.h>
#include "MessageHeader.h"

extern "C" {
	#include "JausUnsignedShort.h"
}

class ClientSetup
{
public:
	ClientSetup::ClientSetup(void);
	int ClientSetup::initializeServer();
	char* ClientSetup::receiveMessage(int msgSize);
};