#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <pcap.h>
#include "RawSoc.h"
#include "ecat_packet.h"
#include "functions.h"
#include "stdafx.h"
#include "ClientSetup.h"
#include "sendpack.h"

#pragma warning( disable: 4510 )    // default constructor could not be generated
#pragma warning( disable: 4512 )    // assignment operator could not be generated
#pragma warning( disable: 4610 )    // can never be instantiated user defined constructor required

//static char* jaus_pkt;
//static int jaus_pkt_len;

char * interf = "\\Device\\NPF_{0392DEE3-4F2A-4EED-8133-34D4E6248495}";
//char * interf = "\\Device\\NPF_{D4A93832-D060-4196-B608-48026D57D559}";

extern RawSoc * raw_soc;
RawSoc * raw_soc;

//using namespace std;

void init_msg();
void top_menu();

// A relatively simple framework that waits for the user to type a character,
// then does some function that the character selects.

struct KeyCommandData
{
    const char key;          // key that user types
    const char* description;
    void (*f)();             // function associated with key
};

extern ClientSetup *clientSetup;
ClientSetup *clientSetup;

KeyCommandData kcd[] = 
{
    {'a', "LRD_1", LRD_1},
    {'1', "LWR_1", LWR_1},
    {'2', "LWR_2", LWR_2},
    {'3', "LWR_3", LWR_3
    },
    {'0', "LWR_0", LWR_0},
    {'r', "recieve", receive},
    {'j', "receive JAUS and send EtherCAT", jauscat},
    {'q', "quit", 0},
    {0} // end sentinal
};


/***************************************************************************/
/*                                                                         */
/*                                main                                     */
/*                                                                         */
/***************************************************************************/

int main(int argc,const char* argv[])
{
    clientSetup = new ClientSetup();
    //If the returned value is not 0, there are problems with WSAStartup and Socket Opening/Binding 
    if(clientSetup->initializeServer() != 0) {
        printf("Could not start the server. We're really sorry.\n");
        return 0;
    }
    else {
        ////Part 1. Receive the JAUS message from Subsytem 1
        ////Receiving the message
        //char* msg = clientSetup->receiveMessage(JAUS_MESSAGE_HEADER_LENGTH 
        //    + SET_WRENCH_EFFORT_LENGTH);
        //UINT16 command_code = endian_change_u16((msg[2] << 8) | msg[3]);
        //SetWrenchEffortMessage * swe;
        ////SetWrenchEffort
        //if(command_code == 1029) {
        //
        //    printf("\nSet Wrench Effort");
        //    printf("\n----------------------------------------");
        //    swe = (SetWrenchEffortMessage *) msg;
        //    printSetWrenchEffort(*swe);
        //}
        //
        ////Part 2. Transfer the JAUS packet to functions.cpp and concatenate the packet into ethercat datagram data     
        //jaus_packet = msg;
        //jaus_packet_length = JAUS_MESSAGE_HEADER_LENGTH + (int)swe->jausMsgHdr.DataControl;
    }

    int c;
    raw_soc = new RawSoc(interf);
    // Print opening line, greeting, instructions, copyright notice etc.
    init_msg();

    do // Main loop.
    {
        printf("\nEcat test:"); // Prompt user for input

        c = _getche(); //Get user response.
        putchar('\n');

        // Take various actions based on user's response.
        int i;
        // Start scanning the array, looking for a match with input and ".key" member Only 'q' will have a zero for f
        for (i = 0; kcd[i].key != 0; i++)
        {
            if (c == kcd[i].key)
            {
                if (kcd[i].f != 0) kcd[i].f();
                    break;
            }
        }
        if (kcd[i].key == 0) top_menu(); //No match, print menu

    } while (c != 'q'); // End of main loop.

    delete raw_soc;

//    return 0;
}

/***************************************************************************/
/*                                                                         */
/*                              init_msg                                   */
/*                                                                         */
/***************************************************************************/
void init_msg()
{
    printf( "\nEnter the letter corresponding to the desired command.  You don't need to\n");
    printf( "follow it with a carriage return.  If the letter isn't a valid command, the\n");
    printf( "list of commands will be repeated. To exit from a demo, type any character.\n\n");
}

/***************************************************************************/
/*                                                                         */
/*                              top_menu                                   */
/*                                                                         */
/***************************************************************************/
void top_menu()
{
    printf("Commands:");
    for (int i = 0; kcd[i].key != 0; i++)
    {
        printf("\n");
        printf("    %c - %s", kcd[i].key, kcd[i].description);
    }
}
