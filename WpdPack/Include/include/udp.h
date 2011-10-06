/* Rev:$Revision: 1.17 $ */  

/******************************************************************************
 *
 * Copyright 1998-2004 NetBurner  ALL RIGHTS RESERVED
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
 * San Diego Ca, 92121
 *
 * information available at:  http://www.netburner.com
 * E-Mail info@netburner.com
 *
 * Support is availible: E-Mail support@netburner.com
 *
 *****************************************************************************/


#ifndef _NB_UDP_H
#define _NB_UDP_H

#ifdef __cplusplus 

/*-----------------------------------------------------------------------------------------------**
**                                                                                               **
** The folowing class holds PoolBuffers and treats them as UDP PAckets.                          **
** The process for sending a UDP packet is as follows:                                           **
**    UDPPacket up;                                                                                **
**    up.SetSourcePort(123);                                                                       **
**    up.SetDestinatioPort(666);                                                                   **
**                                                                                               **
** You may put data in the UDP packet two ways.                                                  **
** You may get a pointer to the data buffer and fill it your self,                               **
** but you have to set the length when you are done.                                             **
**    WORD len=siprintf(up.GetDataBuffer(),"This is a printf to a packet at time = %ld",TickCount); **
**    up.SetDataSize(len);                                                                         **
**                                                                                               **
** Or you may copy bytes directly to the packet buffer:                                          **
**    AddData("This is to add");                                                                   **
**    AddData(pData,len);                                                                          **
**                                                                                               **
** When your UDP PAcket is formatted as you want it....                                          **
** You can send it two ways:                                                                     **
**    SendAndKeep(IPADDR to);                                                                      **
**                                                                                               **
**    Send(IPADDR to);                                                                             **
** The first way keeps the packet intact,                                                        **
** the second way is more efficient , but destorys the packet in the proccess.                   **
**                                                                                               **
**-----------------------------------------------------------------------------------------------*/
class UDPPacket
{
   protected:
      PoolPtr m_p;
      PUDPPKT m_pPkt;

#ifdef UDP_FRAGMENTS
	  BOOL bIsFragBuffer;
#endif

	  PIPPKT GetIpPacket();

   public:
      //constructors

      //Pend on a fifo and return the UDP packet from that fifo.
      //If the fifo times out then create an invalid UDP packet
      //Check with the Validate Function.
      UDPPacket( OS_FIFO *fifo, DWORD wait ); 
	  /* Make a UDP packet object from a udp socket */
	  UDPPacket(int sock);

      //Make a packet from a poolbuffer.
      UDPPacket( PoolPtr p );
      UDPPacket();

      //Destructor frees the pool buffer if it is defined
      ~UDPPacket();

      void SetSourcePort( WORD );
      WORD GetSourcePort();

      IPADDR GetSourceAddress();
      IPADDR GetDestinationAddress();

      void SetDestinationPort( WORD );
      WORD GetDestinationPort();

      WORD GetPacketId();


      PBYTE GetDataBuffer();
      void SetDataSize( WORD );
      WORD GetDataSize();

      void AddData( PBYTE pData, WORD len );
      void AddData( PCSTR pData );
      void AddDataWord( WORD w );
      void AddDataByte( BYTE b );


      //Check the Checksum
      BOOL Validate();

      //Zero the data buffer and return.
      void ResetData();


      //Send and keep makes a copy of this UDP packet and sends it.
      void SendAndKeep( IPADDR to, BYTE ttl = 0 );

      //Send destroys the data in the packet.
      void Send( IPADDR to, BYTE ttl = 0 );

      //Send destroys the data in the packet.
      void SendViaInterface( IPADDR to, int interface, BYTE ttl = 0 );

#ifdef UDP_FRAGMENTS
      void FragFreeBuffer(PoolPtr mp);
	  void ReleaseBuffer();
	  PoolPtr GetPoolPtr();
      void FixTransmitBuffers();

#else
	  void ReleaseBuffer()
		   {
			  m_p = 0;
		   };

		   PoolPtr GetPoolPtr()
		   {
			  return m_p;
		   };


#endif


#ifdef MULTIHOME
	  //Send and keep makes a copy of this UDP packet and sends it.
	  void SendAndKeepVia(IPADDR to,IPADDR from_ip, BYTE ttl = 0);
	  //Send destroys the data in the packet.
	  void SendVia(IPADDR to ,IPADDR from_ip,BYTE ttl=0);

#endif



};


#ifdef UDP_FRAGMENTS
extern BYTE pFragmentBuffers[UDP_FRAGMENTS * (65536+4)]; 
extern PBYTE pMaxFragmentBuffer; 
#endif


typedef void  ( udp_data_notify )(OS_FIFO * pfifo, WORD port);  

void RegisterUDPFifo( WORD dest_port, OS_FIFO *pfifo );
void RegisterUDPFifoWithNotify( WORD dest_port, OS_FIFO *pfifo,udp_data_notify * pnudp);
void UnregisterUDPFifo( WORD destination_port );




//INTERNAL FUNCTIONS
//Used by the IP.cpp process packet function
void process_udp( PoolPtr pp, PIPPKT pIP, WORD csum );






extern "C"
{
#endif


#define  UDP_ERR_NOSUCH_SOCKET    (-1)
#define  UDP_ERR_NOTOPEN_TO_WRITE (-2)
#define  UDP_ERR_NOTOPEN_TO_READ  (-3)


/* Open a UDP socket that can be used by select to receive UDP datagrams*/
int CreateRxUdpSocket(WORD listening_port);

/* Open a UDP socket that can use write, writestring etc to send data */
int CreateTxUdpSocket(IPADDR send_to_addr, WORD remote_port, WORD local_port);

/* Open a UDP socket that both send sand receives using read, write, write string etc... */
int CreateRxTxUdpSocket(IPADDR send_to_addr, WORD send_to_remote_port, WORD local_port);



/* Send a UDP packet */
int sendto(int sock, PBYTE what_to_send, int len_to_send,IPADDR to_addr, WORD remote_port);
#ifdef MULTIHOME
int sendtovia(int sock, PBYTE what_to_send, int len_to_send,IPADDR to_addr, WORD remote_port, int intfnum);
#endif



/* receive a UDP packet and pointer can be NULL and will not be used in that case*/
/* parmeters :
 sock the UDP socket
 buffer the data to send
 len the length of the data to send
 pAddr a pointer to an IPADDR variable to hold the address of the device that sent the UDP packet
 pLocal_port a pointer to a WORD variable to hold the local port this was sent to.
 pRemote_port a pointer to a WORD variable to hold the remote port this was sent from.
 
 returns the number of bytes read or
 UDP_ERR_NOSUCH_SOCKET (-1)
*/
int recvfrom(int sock, PBYTE buffer, int len, IPADDR * pAddr, WORD * pLocal_port, WORD * pRemote_port);


/* 
Send a large fragmented udp packet
to is the destination address
source_port is the source port
dest_port is the detination port
data is the data to send
length is the length to send

return 0 on failure, length on success

*/
int SendFragmentedUdpPacket(IPADDR to, WORD source_port, WORD dest_port, PBYTE data, int length);
#ifdef __cplusplus
};
#endif








#endif





