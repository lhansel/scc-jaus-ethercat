/* $Revision: 1.21 $ */
/* Copyright $Date: 2009/12/01 21:57:58 $ */  

/******************************************************************************
 *
 * Copyright 1998-2009 NetBurner, Inc.  ALL RIGHTS RESERVED
 *   Permission is hereby granted to purchasers of NetBurner Hardware
 *   to use or modify this computer program for any use as long as the
 *   resultant program is only executed on NetBurner provided hardware.
 *
 *   No other rights to use this program or its derivatives in part or
 *   in whole are granted.
 *
 *   It may be possible to license this or other NetBurner software for
 *   use on non-NetBurner Hardware.
 *   Please contact sales@Netburner.com for more information.
 *
 *   NetBurner makes no representation or warranties
 *   with respect to the performance of this computer program, and
 *   specifically disclaims any responsibility for any damages,
 *   special or consequential, connected with the use of this program.
 *
 *---------------------------------------------------------------------
 * NetBurner, Inc.
 * 5405 Morehouse Dr.
 * San Diego, Ca. 92121
 *
 * information available at:  http://www.netburner.com
 * E-Mail info@netburner.com
 *
 * Support is available: E-Mail support@netburner.com
 *
 *****************************************************************************/

#ifndef _NB_TCP_H                      
#define _NB_TCP_H                      

/*
 ******************************************************************************
 *
 * Constant Definitions
 *
 ******************************************************************************
 */
/* TCP socket states RFC 793 (Do not change) */ 
#define TCP_STATE_CLOSED            (0)
#define TCP_STATE_LISTEN            (1)
#define TCP_STATE_SYN_SENT          (2)
#define TCP_STATE_SYN_RCVD          (3)
#define TCP_STATE_WAIT_FOR_ACCEPT   (4)   /* TCP_STATE_ESTABLISHED window = 0 */
#define TCP_STATE_ESTABLISHED       (5)
#define TCP_STATE_CLOSE_WAIT        (6)
#define TCP_STATE_LAST_ACK          (7)
#define TCP_STATE_FIN_WAIT_1        (8)
#define TCP_STATE_FIN_WAIT_2        (9)
#define TCP_STATE_CLOSING           (10)
#define TCP_STATE_TIME_WAIT         (11)


/*********************************************************************/
/*   The Users interface to TCP.                                     */
/*********************************************************************/
/* TCP socket status */
#define TCP_ERR_NORMAL              (0)
#define TCP_ERR_TIMEOUT             (-1)
#define TCP_ERR_NOCON               (-2)
#define TCP_ERR_CLOSING             (-3)
#define TCP_ERR_NOSUCH_SOCKET       (-4)
#define TCP_ERR_NONE_AVAIL          (-5)
#define TCP_ERR_CON_RESET           (-6)
#define TCP_ERR_CON_ABORT           (-7)

/* Any address */
#define INADDR_ANY                  (0)

int listen( IPADDR addr, WORD port, BYTE maxpend = 5 );
int accept( int listening_socket, IPADDR *address, WORD *port, WORD timeout );

/*
 ******************************************************************************
 *
 * Establishes socket with local port and remote IP address and port.
 *    It by default uses the first network interface but can be optionally
 *    directed to use a specific network interface.
 *    
 *    Parameters:
 *       ipAddress         - Remote IP address
 *       localPort         - Port for local side of socket
 *                            If zero (0) a randomly selected port > 0x8000
 *                            will be used.
 *       remotePort        - Remote port of socket
 *       timeout           - Timeout in ticks
 *       interfaceIpAddress- Network interface IP address to use
 *                            If zero (0) it will attempt to use the first 
 *                            interface associated with the remote IP address
 *    Return:
 *       > 0 is a socket file descriptor (fd).
 *       < 0 error described in NetBurner Runtime Libraries Reference
 *
 * ******************************************************************************
 */
int connect( IPADDR ipAddress, WORD localPort, WORD remotePort, DWORD timeout,
      IPADDR interfaceIpAddress = 0 );

int getsocketerror( int fd );

/* Socket status functions */
IPADDR GetSocketRemoteAddr( int i );
WORD GetSocketRemotePort( int i );
WORD GetSocketLocalPort( int i );
IPADDR GetSocketLocalAddr( int fd ); 

/* Keepalive functions */
DWORD TcpGetLastRxTime( int fd ); 
void TcpSendKeepAlive ( int fd );

/*
 *****************************************************************************-
 *
 * Interval in ticks since last received packet
 *
 *    Parameters:
 *       socket
 *
 *    Return:
 *       Interval is ticks from now until the last received packet
 *
 *    Notes:
 *       Will handle one rollover approx. 6 years but not more than one which
 *       given the timeliness of the use of this function should not matter.
 *
 *****************************************************************************-
 */
DWORD TcpGetLastRxInterval( int fd ); 

/* return the number of retransmit counts*/
int GetTcpRtxCount(int fd);



#ifdef MULTIHOME
int connectvia( IPADDR addr, WORD localport, WORD remoteport, DWORD timeout, IPADDR ipa );
#endif

/* Get and set the socket options */
int setsockoption( int fd, int option );
int clrsockoption( int fd, int option );
int getsockoption( int fd );
int setsocketackbuffers( int fd, BYTE val );
int SetSocketRxBuffers( int fd, int n );
int SetSocketTxBuffers( int fd, int n );

#define SO_DEBUG 1
#define SO_NONAGLE 2
#define SO_NOPUSH 4

//INTERNAL FUNCTIONS
extern "C"
{
   int abortsocket( int fd );
   int SockReadWithTimeout( int fd, char *buf, int nbytes, DWORD timeout );
}

void DumpTcpDebug();
void EnableTcpDebug( WORD db );


/**********************************************************************/
/*   Internal TCP Definitions                                         */
/**********************************************************************/
typedef struct
{
      WORD srcPort; 
      WORD dstPort; 
      DWORD SeqNumber;
      DWORD AckNumber;
      BYTE header_len;
      BYTE flags;
      WORD window;
      WORD csum;
      WORD urgent;
      BYTE DATA[4];//The data field is actually as long as the packet....
}TCPPKT;

typedef TCPPKT *PTCPPKT;


/**********************************************************************/
/*   Warning  WARNING  WARNING  If  you  use  these  functions on an  */
/*   uninitialized  buffer you will get bogus values for the pointer  */
/*   As  the header length field in the IP packet is not yet set up!  */
/*   Use the GetInitxxx functions instead             */
/**********************************************************************/

inline PTCPPKT GetTcpPkt( PIPPKT pIp )
{
   if ( pIp == NULL )
   {
      return NULL;
   }
   if ( pIp->bVerHdrLen == 0x45 )
   {
      return ( PTCPPKT ) pIp->DATA;
   }
   return ( PTCPPKT ) ( pIp->DATA + ( ( ( pIp->bVerHdrLen & 0XF ) * 4 ) - 20 ) );
}

inline PTCPPKT GetTcpPkt( PoolPtr p )
{
   return GetTcpPkt( GetIpPkt( p ) );
};
inline PTCPPKT GetTcpPkt( PEFRAME pFrame )
{
   return GetTcpPkt( GetIpPkt( pFrame ) );
};



inline PTCPPKT GetInitTcpPkt( PIPPKT pIp )
{
   pIp->bVerHdrLen = 0x45;
   return ( PTCPPKT ) pIp->DATA;
}


inline PTCPPKT GetInitTcpPkt( PoolPtr p )
{
   return GetInitTcpPkt( GetIpPkt( p ) );
};


#ifdef SPEED_TCP
      
 typedef void  ( tcp_data_handler )( int fd ,PBYTE data, WORD len);  
 void RegisterDataProcessor(int fd,tcp_data_handler * pdh);
#endif


void InitTCP();

//Used by the IP.cpp process packet function
void process_tcp( PoolPtr pp, PIPPKT pIP, WORD csum );

void DumpTcpDebug();            
void EnableTcpDebug( WORD );      
void DumpTcpPacket( PIPPKT pIP ); 

/*
 *****************************************************************************-
 *
 * Check state of socket
 *
 *    Parameters:
 *       socket
 *
 *    Return:
 *       State or TCP_ERR_NOSUCH_SOCKET if not a valid socket
 *
 *    Notes:
 *       none
 *
 *****************************************************************************-
 */
BYTE TcpGetSocketState( int fd );
 
#endif /* #ifndef _NB_TCP_H */
