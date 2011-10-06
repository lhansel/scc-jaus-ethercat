/* Rev:$Revision: 1.10 $ */  

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
 * San Diego Ca, 92131
 *
 * information available at:  http://www.netburner.com
 * E-Mail info@netburner.com
 *
 * Support is availible: E-Mail support@netburner.com
 *
 *****************************************************************************/

#ifndef _NB_DHCP_H
#define _NB_DHCP_H


#define OPT_SIZE  255             // Size of options area
#define DHCP_OPT_OFFS      236    // Offset into DHCP Message for options data
#define DHCP_CLIENT_PORT    68    // Standard port assignment for client
#define DHCP_SERVER_PORT    67    // Standard port assignment for server


//----- DHCP message types -----
#define DHCPDISCOVER    1
#define DHCPOFFER       2
#define DHCPREQUEST     3
#define DHCPDECLINE     4
#define DHCPACK         5
#define DHCPNAK         6
#define DHCPRELEASE     7
#define DHCPINFORM      8
#define DHCPERROR      99       

//----- DHCP message op codes -----
#define BOOTREQUEST     1
#define BOOTREPLY       2

//----- DHCP option codes -----
#define DHCPOPT_SUBNET_MASK   1    // Client subnet mask
#define DHCPOPT_DNS_SERVER    6    // DNS Server
#define DHCPOPT_ROUTER        3    // Routers
#define DHCPOPT_HOST_NAME    12    // Specifies name of client (Host Name Opt)
#define DHCPOPT_REQ_IPADDR   50    // Client requested IP address
#define DHCPOPT_LEASE_TIME   51    // IP addr lease time assigned by server
#define DHCPOPT_MSG_TYPE     53    // Type of DHCP message
#define DHCPOPT_SERVER_ID    54    // DHCP Server identifier
#define DHCPOPT_PARAM_REQ    55    // Parameter request list
#define DHCPOPT_RENEW_TIME   58    // # of seconds until client renewal state
#define DHCPOPT_REBIND_TIME  59    // # of seconds until client rebinding state
#define DHCPOPT_CLIENT_ID    61    // Unique client identifier
#define DHCPOPT_END         255    // End of options marker

#define DHCPCOOKIE0     (BYTE)99   // DHCP message 4-byte cookie values
#define DHCPCOOKIE1     (BYTE)130
#define DHCPCOOKIE2     (BYTE)83
#define DHCPCOOKIE3     (BYTE)99

//----- ProcessDhcpMsg function return definitions -----
/*
#define PDM_DHCPOFFER   1  // Received DHCPOFFER message
#define PDM_DHCPACK     2  // Received DHCPACK message
#define PDM_DHCPNAK     3  // Received DHCPNAK message
#define PDM_COMPLETE    4  // DHCP configuration complete
#define PDM_ERROR      10  // Received unknown message
*/


//----- DHCP Message Structure -----
typedef struct dhcp_msg
{
      unsigned char op;    // Message opcode; 1=bootrequest, 2=bootreply
      unsigned char htype; // Hardware address type; 1=10Mb ethernet
      unsigned char hlen;  // Hardware address length; 6=10Mb ethernet
      unsigned char hops;  // Client sets this to 0
      unsigned long xid;   // Transaction ID; random number
      unsigned short secs; // Seconds elapsed since client request
      unsigned short flags;   // 
      unsigned long ciaddr;   // Clinet IP address if renew; filled by client
      unsigned long yiaddr;   // Assigned client IP address
      unsigned long siaddr;   // IP address of next server to use in bootstrap
      unsigned long giaddr;   // Relay agent IP address (Gateway)
      unsigned char chaddr[16];  // Client hardware address
      unsigned char sname[64];   // Optional server host name
      unsigned char file[128];   // Boot file name, null terminated string
      unsigned char options[OPT_SIZE];// Optional parameters field
} __attribute__(( packed) ) DHCP_MESSAGE;


//----- DHCP message class -----
class DHCPMessage
{
   private:
      DHCP_MESSAGE Msg;

   public:
      // constructors
      DHCPMessage();
      DHCPMessage( PBYTE pData );

      // member functions
      void SetOp( unsigned char n )
      {
         Msg.op = n;
      }

	  unsigned char  GetMsgType()
	  {
		  return msg_type;
	  }


      void SetHtype( unsigned char n )
      {
         Msg.htype = n;
      }
      void SetHlen( unsigned char n )
      {
         Msg.hlen = n;
      }
      void SetHops( unsigned char n )
      {
         Msg.hops = n;
      }
      void SetXid( unsigned long n )
      {
         Msg.xid = n;
      }
      void SetSecs( unsigned short n )
      {
         Msg.secs = n;
      }
      void SetFlags( unsigned short n )
      {
         Msg.flags = n;
      }
      void SetCiaddr( unsigned long n )
      {
         Msg.ciaddr = n;
      }
      void SetYiaddr( unsigned long n )
      {
         Msg.yiaddr = n;
      }
      void SetSiaddr( unsigned long n )
      {
         Msg.siaddr = n;
      }
      void SetGiaddr( unsigned long n )
      {
         Msg.giaddr = n;
      }
      void SetChaddr( MACADR ma )
      {
         bzero( Msg.chaddr, 16 ); memcpy( Msg.chaddr, ( PBYTE ) ma.phywadr, 6 );
      }
      void SetSname( char *s )
      {
         memcpy( Msg.sname, s, 64 );
      }
      void SetFile( char *s )
      {
         memcpy( Msg.file, s, 128 );
      }
      void SetOptions( char *s )
      {
         memcpy( Msg.options, s, OPT_SIZE );
      }
      void SetOptions( int i, char n )
      {
         Msg.options[i] = n;
      }

      DWORD GetXid()
      {
         return Msg.xid;
      }
      WORD GetSecs()
      {
         return Msg.secs;
      }
      WORD GetFlags()
      {
         return Msg.flags;
      }
      DWORD GetYiaddr()
      {
         return Msg.yiaddr;
      }
      DWORD GetGiaddr()
      {
         return Msg.giaddr;
      }
      DWORD GetSiaddr()
      {
         return Msg.siaddr;
      }
      BYTE GetChaddr( int i )
      {
         return Msg.chaddr[i];
      }

      PBYTE GetDataPtr()
      {
         return ( unsigned char * ) ( &Msg );
      }
      int GetDataLen()
      {
         return sizeof( DHCP_MESSAGE );
      }
      void ShowMsg();        // Displays DHCP message for debug purposes
      void ClearOptions();   // Clears options memory space and adds cookie
      void ResetBytes();     // Clear chaddr, sname, file, and option fields
      PBYTE GetOptionData( BYTE code );   // Returns option data for specified op code
      PBYTE GetOptionData( BYTE code, int & length ); 
      void SendMsg( IPADDR IpAddr, int via_interface );     // Send a DHPC message as a UDP packet
      BOOL MsgForInterface( int intf );
	  unsigned char msg_type;
};

//----- function prototypes -----
void CreateDhcpDiscoverMsg( DHCPMessage &NewMsg, int intf );
void CreateDhcpRequestMsg( DHCPMessage &OfferMsg, DHCPMessage &NewMsg, int intf );
void CreateDhcpReleaseMsg( DHCPMessage &NewMsg, int intf );
void ShowDhcpConfig();                       // Show DHCP configuration paramters
void UpdateIPRuntimeVars( BOOLEAN release ); // Update DHCP & IP runtime vars
void DHCPTimer();                            // Tracks lease time
int ExecDHCPClient( int DhcpState );         // Function that does the work
BOOLEAN ValidDhcpMsg( PBYTE pData );         // Verify the UDP packet contains a DHCP message
BOOLEAN DhcpConfig( DHCPMessage &Msg );      // Configure client from DHCPACK message


/* function pointers to extend DHCP options */
extern void ( *AddDhcpOptionsFunc )( DHCPMessage &NewMsg, int &opt,int MsgType );
extern void ( *AddDhcpFieldsFunc )( DHCPMessage &NewMsg, int &opt,int MsgType );
extern void ( *ParseDhcpOptions )( DHCPMessage &Msg );





#endif
