/* Rev:$Revision: 1.7 $ */  

/******************************************************************************
 *
 * Copyright 2000-2004 NetBurner  ALL RIGHTS RESERVED
 *   Permission is hereby granted to purchasers of NetBurner Hardware
 *   to use or modify this computer program for any use as long as the
 *   resultant program is only executed on NetBurner provided hardware.
 *
 *   No other rights to use this program or it's derivitives in part or
 *   in whole are granted.
 *
 *   It may be possible to license this or other NetBurner software for
 *        use on non NetBurner Hardware.
 *   Please contact Licensing@Netburner.com for more infomation.
 *
 *   NetBurner makes no representation or warranties
 *   with respect to the performance of this computer program, and
 *   specifically disclaims any responsibility for any damages,
 *   special or consequential, connected with the use of this program.
 *
 *---------------------------------------------------------------------
 * NetBurner
 * 5405 Morehouse Dr #350
 * San Diego Ca, 92131
 *
 * information available at:  http://www.netburner.com
 * E-Mail info@netburner.com
 *
 * Support is availible: E-Mail support@netburner.com
 *
 *****************************************************************************/


#ifndef _NB_MULTICAST_H
#define _NB_MULTICAST_H

/*Module: Multicast Interface.
  This Module provides code for joining multicast groups.
  This uses the IGMP protocol defined in RFC1112 and RFC 2236 
*/


/*Functions:*/
/*Group:Multicast Group functions*/


/* Register to joing a Multicast group. */
/*
This call initializes the Multicast system. it is not
active until at least one join has taken place. 

Parameters:
   IPADDR group The IP address of the group to join.
   WORD dest_port The UDP Port to listen on.
   OS_FIFO * pfifo the fifo to put incomming packets into.
   

*/
/*See Also: UnregisterMulticastFifo(IPADDR group,WORD destination_port); 
*/
void RegisterMulticastFifo( IPADDR group, WORD  dest_port, OS_FIFO *pfifo );




/* UnRegister to joing a Multicast group. */
/*
This call removes the Netburner from the specified 
multicast group.

Parameters:
   IPADDR group The IP address of the group to leave.
   WORD dest_port The UDP Port it was listening on.
   

*/
/*See Also: RegisterMulticastFifo(IPADDR group, WORD  dest_port, OS_FIFO *pfifo);
*/
void UnregisterMulticastFifo( IPADDR group, WORD destination_port );


/*Module Example:

#include "predef.h"
#include <stdio.h>
#include <ctype.h>
#include <startnet.h>
#include <ucos.h>
#include <udp.h>
#include <multicast.h>
#include <autoupdate.h>


extern "C" {
void UserMain(void * pd);
}

//Make sure they're 4 byte aligned to keep the ColdFire happy
DWORD   MultiTestStk[USER_TASK_STK_SIZE] __attribute__((aligned(4)));

IPADDR ipaddr; // The multicast address 
BOOL shutdown;

//The UCOS task fucntion that just sits and waits for Multi packets...
void MultiReaderMain(void * pd)
{
   int port=(int )pd;
   printf("Reading from port %d\n",port);

   OS_FIFO fifo;
   OSFifoInit(&fifo);

   // Register to listen for Multi packets on port number 'port'
   RegisterMulticastFifo(ipaddr,port,&fifo);

   while (!shutdown)
   {
      // We construct a UDP packet object using the FIFO....
      // This constructor will only return when we have received a packet
      UDPPacket upkt(&fifo,10);

      //Did we get a valid packet? or just time out?
      if (upkt.Validate())
        {WORD len = upkt.GetDataSize();
      printf("Got UDP packet with %d Bytes From :",(int)len);
      ShowIP(upkt.GetSourceAddress());
      printf("\n");
      ShowData(upkt.GetDataBuffer(),len);
      printf("\n");
   }

   iprintf("Unregistering from group\r\n");
   UnregisterMulticastFifo(ipaddr,port);
   iprintf("Done unregistering\r\n");
}



void UserMain(void * pd)
{
   int portnum;
   char buffer[80];

   InitializeStack();
   EnableAutoUpdate();

   printf("Multicast Test \n");
   printf("Input the port number?\n");
   scanf("%d", &portnum);
   printf("\nEnter the Multicast IP Address?");
   buffer[0] = 0;

   while(buffer[0] == 0)
   {
      gets(buffer);
   }

   ipaddr = AsciiToIp(buffer);

   printf("Listening/Sending on Port %d of Group:",portnum);
   ShowIP(ipaddr);
   printf("\n");
 
   OSChangePrio(MAIN_PRIO);
   OSTaskCreate(MultiReaderMain,(void  *)portnum,&MultiTestStk[USER_TASK_STK_SIZE] ,MultiTestStk,MAIN_PRIO- 1);

   while(1)
   {
      iprintf("Enter the test to send in the packet. (Empty string to unregister listener)\n");
      gets(buffer);
      if (strlen(buffer)==0)
      {
         iprintf("Un registering the listener\n");
         iprintf("You must reset the board to continue\n");
         shutdown=TRUE;
         while(1) OSTimeDly(20);
      }
      else
      {
         printf("Sending %s on UDP port %d to IP Address ",buffer,portnum);
         ShowIP(ipaddr);
         {
            UDPPacket pkt;
            pkt.SetSourcePort(portnum);
            pkt.SetDestinationPort(portnum);
            pkt.AddData(buffer);
            pkt.AddDataByte(0);
            pkt.Send(ipaddr);
         }
         printf("\n");
      }
   }
}

*/

#endif

