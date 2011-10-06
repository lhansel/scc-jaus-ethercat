/* $Revision: 1.25 $ */
/* Copyright $Date: 2008/08/05 17:56:35 $ */  

/******************************************************************************
 *
 * Copyright 1998 - 2008 NetBurner  ALL RIGHTS RESERVED
 *   Permission is hereby granted to purchasers of NetBurner Hardware
 *   to use or modify this computer program for any use as long as the
 *   resultant program is only executed on NetBurner provided hardware.
 *
 *   No other rights to use this program or it's derivatives in part or
 *   in whole are granted.
 *
 *   It may be possible to license this or other NetBurner software for
 *   use on non-NetBurner Hardware.
 *   Please contact Licensing@Netburner.com for more information.
 *
 *   NetBurner makes no representation or warranties
 *   with respect to the performance of this computer program, and
 *   specifically disclaims any responsibility for any damages,
 *   special or consequential, connected with the use of this program.
 *
 *---------------------------------------------------------------------
 * NetBurner
 * 5405 Morehouse Dr.
 * San Diego, Ca. 92121
 *
 * information available at:  http://www.netburner.com
 * E-Mail info@netburner.com
 *
 * Support is available: E-Mail support@netburner.com
 *
 *****************************************************************************/

/* Definitions for various IP definitions and structures. */
#ifndef _NB_IP_H
#define _NB_IP_H

#ifndef NB_NET_TYPES_H
   #include "nettypes.h"
#endif

#ifndef _NB_BUFFERS_H
   #include "buffers.h"
#endif
/*
 ******************************************************************************
 *
 * Debugging
 *
 ******************************************************************************
 */
// #define IP_DEBUG              ( 0 )

/*
 ******************************************************************************
 *
 * Definitions
 *
 ******************************************************************************
 */
 
/* 
   IP Version
*/
#define IP_VERSION_MASK                ( 0xF0 )
#define IP_VERSION_IPv4                ( 0x40 )
#define IP_VERSION_IPv6                ( 0x60 )
/*
   Header Length
*/
#define IP_HEADER_LENGTH_MASK          ( 0x0F )
#define IP_HEADER_LENGTH_NO_OPTIONS    ( 0x05 )
/*
   Flags and Fragment Offset
*/
#define IP_FLAGS_MASK                  ( 0xE000 )      
#define IP_FRAGMENT_OFFSET_MASK        ( 0x1FFF )
/*
   IANA protocol
*/
#define IP_PROTOCOL_INTERNET           ( 4 )         

/*
 ******************************************************************************
 *
 * Data Structures
 *
 ******************************************************************************
 */
 
/* 
   IP Header (IPv4)
   
      versionNLength       - Version and header length nibbles
      diffServNEcn         - Service and congestion related
      totalLength          - Datagram size including IP header
      identification       - Fragment identification
      flagsNFragmentOffset - Flags and fragment offset fields
      timeToLive           - Usually hop count
      protocol             - IANA protocol number
      headerChecksum       - 16-bit one's complement of the one's complement 
                                 sum of all 16-bit words in the header
      sourceAddress        - IP address of source 4 8-bit octets                                 
      destinationAddress   - IP address of destination 4 8-bit octets
      
   Note:
      Can contain options, determined by header length ( No options header
      length is 5 for 5 32 bit words ( 20 bytes )
      IETF RFC 791 September 1981, MIL-STD-1777
         
*/         
typedef struct _IpHeaderIPv4
{
   BYTE versionNLength;
   BYTE diffServNEcn;
   WORD totalLength;
   WORD identification;
   WORD flagsNFragmentOffset;
   BYTE timeToLive;
   BYTE protocol;
   WORD headerChecksum;
   DWORD sourceAddress;
   DWORD destinationAddress;
      
} __attribute__( ( packed) ) IpHeaderIPv4;



#ifdef __cplusplus
void InitializeStack( IPADDR ipaddr = 0,
                      IPADDR ipMask = 0,
                      IPADDR ipGate = 0,
                      IPADDR dns = 0 );

class UDPPacket;
typedef int (TaskPacketFunc)(UDPPacket & pkt, int ifn);
extern TaskPacketFunc * pTaskPacketFunc;



extern "C"
{
#endif

   void InitializeCStack( IPADDR ipaddr, IPADDR ipMask, IPADDR ipGate, IPADDR dns );

   /*Section: IP functions */
   void IpProcessEthernetPacket( PoolPtr poolPtr, WORD packetSizeInBytes );

   /*Start the IP stack */

   /*Shutdown the IP stack */
   void KillStack();

   /*Sends a ping and waits for the response 
   returns time ticks, or -1 if it timed out */
   int Ping( IPADDR to, WORD id, WORD seq, WORD maxwaitticks );

   /* Works like Ping() via a designated interface */
   int PingViaInterface( IPADDR to, WORD id, WORD seq, WORD wait, int interface );

   /*Sends a ping packet */
   void SendPing( IPADDR to, WORD id, WORD seq, int interface );

   BOOL IsMyIp( IPADDR ip );
   IPADDR GetSrcIp( IPADDR dst );

#ifdef __cplusplus
};
#endif



#define HTONS(x) (x)
#define HTONL(x) (x)
#define NTOHL(x) (x)
#define NTOHS(x) (x)

#ifdef __cplusplus

/*Dump a buffer for diagnostics */
void ShowIPBuffer( PoolPtr rp );




/*****************************************************************
INTERNAL FUNCTIONS
*****************************************************************/

typedef struct
{
      BYTE bVerHdrLen;
      BYTE bTos;
      WORD wLength;
      WORD wpktId;
      WORD wFlags_Frag;
      BYTE bTTL;
      BYTE proto;
      WORD hCSum;
      IPADDR ipSrc;
      IPADDR ipDst;
      BYTE DATA[4];/*The data field is actually as long as the packet.... */
}IPPKT;

typedef IPPKT *PIPPKT;

typedef struct
{
      WORD srcPort;
      WORD dstPort;
      WORD UdpLen;
      WORD UdpCSum;
      BYTE DATA[4];/*The data field is actually as long as the packet.... */
}UDPPKT;

typedef UDPPKT *PUDPPKT;


typedef struct
{
      WORD proto;
      WORD len;
      IPADDR srcip;
      IPADDR dstip;
}PsudeoHeader;

typedef PsudeoHeader *PPSUH;       


typedef UDPPKT *PUDPPKT;


inline PIPPKT GetIpPkt( PoolPtr p )
{
   return ( p == NULL ) ? NULL : ( PIPPKT ) ( p->pData + 14 );
};

inline PIPPKT GetIpPkt( PEFRAME pFrame )
{
   return ( PIPPKT ) ( pFrame->pData );
};


/*Warning WARNING WARNING */
/*If you use these functions on an uninitialized buffer you will get bogus values for the pointer */
/*As the header length field in the IP packet is not yet set up! */
inline PUDPPKT GetUdpPkt( PIPPKT pIp )
{
   if ( pIp == NULL )
   {
      return NULL;
   }
   if ( pIp->bVerHdrLen == 0x45 )
   {
      return ( PUDPPKT ) pIp->DATA;
   }
   return ( PUDPPKT ) ( pIp->DATA + ( ( ( pIp->bVerHdrLen & 0XF ) * 4 ) - 20 ) );
}

inline PUDPPKT GetUdpPkt( PoolPtr p )
{
   return GetUdpPkt( GetIpPkt( p ) );
};
inline PUDPPKT GetUdpPkt( PEFRAME pFrame )
{
   return GetUdpPkt( GetIpPkt( pFrame ) );
};



inline PUDPPKT GetInitUdpPkt( PIPPKT pIp )
{
   pIp->bVerHdrLen = 0x45;
   return ( PUDPPKT ) pIp->DATA;
}


inline PUDPPKT GetInitUdpPkt( PoolPtr p )
{
   return GetInitUdpPkt( GetIpPkt( p ) );
};


#define IP_ICMP   1 /*All are byte swapped because of big end/little end stuff */
#define IP_TCP    6
#define IP_UDP   17 
#define IP_IGMP   2 

/* IANA Well Known Ports */
#define IANA_ECHO_PORT                    ( 7 )
#define IANA_DISCARD_PORT                 ( 9 )
#define IANA_TELNET_PORT                  ( 23 )
#define IANA_SSH_PORT                     ( 22 )
#define IANA_TFTP_PORT                    ( 69 )
#define IANA_NETBIOS_NAME_SERVICE_PORT    ( 137 )


#define ICMP_TYPE_DEST_UNREACHABLE 3
#define ICMP_CODE_PORT_UNREACHABLE 3

/* Internal stack functions */
void SendICMPError( PoolPtr pBadPacket, BYTE type, BYTE code );

extern "C"
{
   WORD GetSum( PWORD addr, WORD count );
   WORD GetSum20( PDWORD addr );
   WORD GetSumHdr( PsudeoHeader &hdr, PWORD addr, WORD count );
}

void FixHeaderAndSend( PoolPtr p, PIPPKT pIp );
void FixHeaderAndSendViaInterface( PoolPtr p, PIPPKT pIp, int Interface ); 

#endif


/* Definitions for the globbal static system variables */
extern BYTE bTTL_Default;
extern WORD wArpLifetime;
extern BOOL bQuietStart; 

/******************************************************************************
 Function to process IP Packets in promiscious mode. This is only called 
 for packets that fail the IP address==my address.
 This function must free the buffers it receives!
******************************************************************************/
typedef void ( PromisciousPacketFunc )( PoolPtr pp );
extern PromisciousPacketFunc *pPromisciousPacketFunc;

extern IPADDR *FirstInterFaceIP;
extern IPADDR *FirstInterFaceMask;
extern IPADDR *FirstInterFaceGate;
extern IPADDR *FirstInterFaceDNS;  

/* Function to handle fragments */

typedef void (FragmentProcessFunction)(PoolPtr pp);
extern FragmentProcessFunction  *pFragFunc;




/* These definitions are included for backwards compatibility with applictions
   that used the global variables of the same name prior to tools revision 1.95, 
   which added multiple ethernet interfaces.
*/   
#define EthernetIP  (*FirstInterFaceIP)
#define EthernetIpMask  (*FirstInterFaceMask)
#define EthernetIpGate  (*FirstInterFaceGate)
#define EthernetDNS  (*FirstInterFaceDNS)

#endif



