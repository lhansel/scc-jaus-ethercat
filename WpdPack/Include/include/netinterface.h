/* $Revision: 1.5 $ */
/* Copyright $Date: 2007/09/12 20:45:53 $ */  

/******************************************************************************
 *
 * Copyright 1998-2007 NetBurner, Inc.  ALL RIGHTS RESERVED
 *   Permission is hereby granted to purchasers of NetBurner Hardware
 *   to use or modify this computer program for any use as long as the
 *   resultant program is only executed on NetBurner provided hardware.
 *
 *   No other rights to use this program or it's derivatives in part or
 *   in whole are granted.
 *
 *   It may be possible to license this or other NetBurner software for
 *        use on non NetBurner Hardware.
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

#ifndef _NB_NETIF_H
#define _NB_NETIF_H

/*
 ******************************************************************************
 *
 * Definitions
 *
 ******************************************************************************
 */

/*
 ******************************************************************************
 *
 * MAC Address for second and subsequent interfaces
 *    For a second and subequent NICs the MSB(it) of the 5th octet is XOR'ed 
 *    with 1 to support prior released tools.
 *
 *                               6 bytes
 *   <--------------------------------------------------------------------->
 *        0           1           2           3           4           5
 *   -----------------------------------------------------------------------
 *  | 6th byte  | 5th byte  | 4th byte  | 3rd byte  | 2nd byte  | 1st byte  | 
 *  | 1st octet | 2nd octet | 3rd octet | 4th octet | 5th octet | 6th octet |
 *   -----------------------------------------------------------------------
 *
 *                 3 bytes                             3 bytes
 *   <---------------------------------> <--------------------------------->
 *   -----------------------------------------------------------------------
 *  | Organizationally Unique Identifer |   Network Interface Controller    |
 *  |           |   (OUI)   |           |           |  (NIC)    |           |
 *  |    0x00   |    0x03   |   0xF4    |    0xYX   |   0xZX    |   0xXX    |
 *   -----------------------------------------------------------------------
 *  |            \   OUI is NetBurner's      Y is IIXX XXXX binary
 *  |             \                          I is the interface defined as
 *  |              \                            bits in NB_MAX_NIC... below
 *  |               |                                     Z is WXXX binary
 *  V               V                                       W ix XOR'd bit
 *  |1|2|3|4|5|6|7|8| (7) 0 global, 1 local, (8) 0 unicast, 1 multicast (IEE)
 *
 * Notes:
 *    0-5 are C language offsets, 6th byte thru 1st byte is ethernet 
 *    transmission order and octet notation is from IEEE 802 MAC-48 address.
 *    Derivation is needed if the NIC does not have a non-volatile MAC address.
 *
 ******************************************************************************
 */
#ifndef NB_MAC_ADDRESS
#define NB_MAC_ADDRESS 

   /* 4th Octet */
   #define NB_MAC_NIC_INTERFACE              ( 0x00 )
   #define NB_MAC_NIC_SECOND_INTERFACE       ( 0x80 )
   #define NB_MAC_NIC_THIRD_INTERFACE        ( 0x40 )
   #define NB_MAC_NIC_FOURTH_INTERFACE       ( 0xC0 )
   #define NB_MAC_NIC_SECOND_INTERFACE_MASK  ( \
                                               NB_MAC_NIC_INTERFACE | \
                                               NB_MAC_NIC_SECOND_INTERFACE | \
                                               NB_MAC_NIC_THIRD_INTERFACE | \
                                               NB_MAC_NIC_FOURTH_INTERFACE \
                                             )
   #define NB_MAC_OCTET_4                    ( 3 )
   #define NB_MAC_OCTET_5                    ( 4 )
   #define NB_MAC_OCTET_5_XOR                ( 0x80 )
   
#endif /* NB_MAC_ADDRESS */

/*
   Interface Configuration Identifiers
*/   
#define CONFIG_IF_ID_ETHERNET       ( 0 )
#define CONFIG_IF_ID_WIFI           ( 1 )
#define CONFIG_IF_ID_ETHERNET2      ( 2 )

/*
   PPP Interface Identifier
*/   
#define ARP_PPP_INTERFACE           ( 255 )

/*
 ******************************************************************************
 *
 * Callback Function Prototypes
 *
 ******************************************************************************
 */

/*
 ******************************************************************************

   Process Internet Protocol Packet (IP)
   
   Parameters:
      poolPtr           - Packet from pool
      ethernetFramePtr  - Ethernet frame
      checksum          - IP frame checksum
      
   Return:
      None
      
   Notes;
      Called for every IP packet received and meets this criteria.    
         1)The packet is an IP packet.                                          
         2)The IP header checksum is valid.                 
         3)The packet was addressed to us or to a broadcast address. 
      Before the callback is called the flags member of the buffer is setup to 
      indicate physical broadcast etc.... 
                   
 ******************************************************************************
 */
typedef void ( ProcessPacketFunc )( PoolPtr poolPtr, PEFRAME ethernetFramePtr, 
      WORD checksum );
      
/*
 ******************************************************************************
 
   Process Address Resolution Packet (ARP)
   
   Parameters:
      poolPtr           - Packet from pool
      ethernetFramePtr  - Ethernet frame
      
   Return:
      None
      
   Notes;
      Called for every ARP packet received. Before the callback is called the 
      flags member of the buffer is setup to indicate physical broadcast etc...
      
 ******************************************************************************
 */
typedef void ( ProcessArpFunc )( PoolPtr poolPtr, PEFRAME ethernetFramePtr );

/*
 ******************************************************************************
 
   Transmit Network Packet
   
   Parameters:
      poolPtr           - Packet from pool
      
   Return:
      None
      
   Notes:
      Adds interface source MAC address, performs control and formating
      required to send the packet on the interface. Release packet to pool.
      
 ******************************************************************************
 */
typedef void ( TransmitPacketFunc )( PoolPtr poolPtr );

/*
 ******************************************************************************
 
   Kills Interface
   
   Parameters:
      None
      
   Return:
      None
      
   Notes:
      Resets interface disabling it.
      
 ******************************************************************************
 */
typedef void ( KillInterfaceFunc )( void );

/*
 ******************************************************************************
 
   Adds or Subtracts Multicast MAC Address to Interface Filter
   
   Parameters:
      macAddress        - Multicast MAC address
      addAddress        - TRUE to add, FALSE to subtract from filter
      
   Return:
      None
      
   Notes:
      Provides no feedback, addresses and the number of addresses vary by
      interface. When there are no addresses, multicast filter should be
      disabled if the interface support it. Once the number of addresses
      supported is added, all others are ignored.
      
 ******************************************************************************
 */
typedef void ( EnableMulticastFunc )( MACADR macAddress, BOOL addAddress );

/*
 ******************************************************************************
 
   Returns current link active status
   
   Parameters:
      None
      
   Return:
      TRUE active, FALSE all else.
      
   Notes:
      Interface driver must minimize latency.
      
 ******************************************************************************
 */
typedef BOOL ( LinkActiveFunc )( void );

/*
 ******************************************************************************
 *
 * Data Structures
 *
 ******************************************************************************
 */

/*
 ******************************************************************************
 
   Interface Configuration and Control Block
   
      Ethernet
         theMac            - Interface ethernet MAC address
         
      TCP/IP
         netIP             - Interface IP address
         netIpMask         - Interface network IP mask
         netIpGate         - Interface gateway IP address
         netMss            - Interface maximum segment size (0 default)
         
      Network Processing
         send_func         - Transmit packet function
         kill_if           - Kill interface function
         enab_multicast    - Enable/Disable multicast addresses
         
      Identification
         InterfaceName     - Name
         config_num        - Configuration record number
         
      Multi-Home Feature
         bMultiHome        - Multi-home?
         root_if           - Physical interface number for ???
         
      Routing Support
         LinkActiveFuncPtr - Link active function
         
   Notes:
      Should not change data sizes and always add to the end to avoid breaking
      use for interface configuration.         
      
 ******************************************************************************
 */
typedef struct _InterfaceBlock
{
   MACADR theMac;
   IPADDR netIP;
   IPADDR netIpMask;
   IPADDR netIpGate;
   IPADDR netDNS;
   TransmitPacketFunc* send_func;
   KillInterfaceFunc* kill_if;
   EnableMulticastFunc* enab_multicast;
   const char* InterfaceName;
   int config_num;
   BOOL bMultiHome;
   int root_if;
   LinkActiveFunc* linkActiveFuncPtr;
   WORD netMss;
     
} InterfaceBlock;

/*
 ******************************************************************************
 *
 * External Definitions
 *
 ******************************************************************************
 */
/*
   System ARP Process Function
*/   
extern ProcessArpFunc *pArpFunc;

/*
   System IP Packet Process Function
*/   
extern ProcessPacketFunc *pPacketfunc;

/*
 ******************************************************************************
 *
 * Routine Prototypes
 *
 ******************************************************************************
 */
 
/*
 ******************************************************************************
 
   Selects Packet Transmission for the Interface
   
   Parameters:
      poolPtr        - Packet from pool
      interface      - Interface number
      
      
   Return:
      None
      
   Notes:
      Frees buffer if interface is not valid
      
 ******************************************************************************
 */
void TransmitBuffer( PoolPtr poolPtr, int interface ); 

/*
 ******************************************************************************
 
   Extracts Data (Ethernet Frame) Pointer from Pool Packet
   
   Parameters:
      poolPtr        - Packet from pool
      
      
   Return:
      Pointer to data segment (ethernet frame) of pool packet.
      
   Notes:
      Does not check for validity
      
 ******************************************************************************
 */
PEFRAME GetEframe( PoolPtr poolPtr );

/*
 ******************************************************************************
 
   Register interface with network system.
   
   Parameters:
      interfaceBlockPtr    - Interface block
      
   Return:
      Interface number, 0 if exceeded interfaces allowed (MAX_INTERFACES)
      
   Notes:
      RegisterMultiHomeInterface for Multihome interface use.
      
 ******************************************************************************
 */
#ifdef MULTIHOME
int RegisterMultiHomeInterface( InterfaceBlock* interfaceBlockPtr );
#endif
int RegisterInterface( InterfaceBlock* interfaceBlockPtr );

/*
 ******************************************************************************
 
   Remove interface with network system.
   
   Parameters:
      interface      - Interface number
      
   Return:
      1 removed, 0 if otherwise invalid or empty
      
   Notes:
      None
      
 ******************************************************************************
 */
int Removeinterface( int interface );

/*
 ******************************************************************************
 
   Enable/Disable Multicast on an interface.
   
   Parameters:
      macAddress     - Multicast MAC address
      interface      - Interface number
      
   Return:
      None
      
   Notes:
      Calls registered interface multicast routine.
      
 ******************************************************************************
 */
void EnableMulticast( MACADR macAddress, int interface = 0 );
void DisableMulticast( MACADR macAddress, int interface = 0 );

/*
 ******************************************************************************
 
   Get interface block
   
   Parameters:
      interface      - Interface number
      
   Return:
      Interface block, NULL if not valid interface
      
   Notes:
      None
      
 ******************************************************************************
 */
InterfaceBlock *GetInterFaceBlock( int interface = 0 );

/*
 ******************************************************************************
 
   Get first and subsequent interface numbers
   
   Parameters:
      lastInterface        - Last valid interface number
      
   Return:
      Next valid interface number, 0 if exhausted
      
   Notes:
      None
      
 ******************************************************************************
 */
int GetFirstInterface( void );
int GetnextInterface( int lastInterface );


#ifdef _SYSTEM_STORAGE_H 

/*
 ******************************************************************************
 
   Get interface configuration record
   
   Parameters:
      interface         - Interface number
      
   Return:
      Configuration record, NULL if interface nuumber invalid
      
   Notes:
      None
      
 ******************************************************************************
 */
ConfigRecord* GetIfConfig( int interface );

/*
 ******************************************************************************
 
   Update interface configuration record
   
   Parameters:
      configRecordPtr   - Configuration record
      interface         - Interface number
      
   Return:
      None
      
   Notes:
      None
      
 ******************************************************************************
 */
void SaveIfConfig( ConfigRecord* cr, int interface );

/*
 ******************************************************************************
 
   Setup initial interface configuration record from interface block
   
   Parameters:
      interfaceBlock    - Interface block
      
   Return:
      None
      
   Notes:
      Ignore multihome since they do not have or need a record
      
 ******************************************************************************
 */
void SetupIFConfigRec( InterfaceBlock &interfaceBlock );

#endif /*_SYSTEM_STORAGE_H */


/*
 ******************************************************************************
 *
 * Runtime Libraries Routine Prototypes
 *
 ******************************************************************************
 */
 
/*
 ******************************************************************************
 
   Initialize the first Ethernet Interface
   
   Parameters:
      processPacketFuncPtr    - IP Packet process function
      processArpFuncPtr       - ARP Packet process function
      
      
   Return:
      TRUE success, else problems
      
   Notes:
      Should be called once in the system to create first interface.
      
 ******************************************************************************
 */
BOOL InitializeNetwork( ProcessPacketFunc *processPacketFuncPtr, 
      ProcessArpFunc *processArpFuncPtr ); 

/*
 ******************************************************************************
 
   Disables network.
   
   Parameters:
      None
      
   Return:
      None
      
   Notes:
      None
      
 ******************************************************************************
 */
void StopNetworks( void );

/*
 ******************************************************************************
 
   Get current network settings.
   
   Parameters:
      interface      - Interface number
      
   Return:
      Specific setting requested for the interface, 0 if invalid interface.
      
   Notes:
      None
      
 ******************************************************************************
 */
MACADR InterfaceMAC( int interface );
IPADDR InterfaceIP( int interface );
IPADDR InterfaceDNS( int interface );
IPADDR InterfaceMASK( int interface );
IPADDR InterfaceGate( int interface );
 
#endif /* _NB_NETIF_H */
