/* $Revision: 1.18 $ */
/* Copyright $Date: 2009/03/17 19:34:34 $ */  

/******************************************************************************
 *
 * Copyright 2007 NetBurner  ALL RIGHTS RESERVED
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

#ifndef _NB_ETHERNET_H
#define _NB_ETHERNET_H

/*
 ******************************************************************************
 *
 * Definitions
 *
 ******************************************************************************
 */
 
/* 
   EtherType Field ( Ethernet Version II )
      ETHERNET_ETHERTYPE_IPv4       - Internet Protocol, Version 4 (IPv4)
      ETHERNET_ETHERTYPE_ARP        - Address Resolution Protocol (ARP)
      ETHERNET_ETHERTYPE_IPv6       - Internet Protocol, Version 6 (IPv6)
      ETHERNET_ETHERTYPE_AARP       - AppleTalk Address Resolution Prot. (AARP)
      ETHERNET_ETHERTYPE_IPX        - Novell Internet Packet Exchange (IPX) (alt.)
       
*/
#define ETHERNET_ETHERTYPE_IPv4        ( WORD )( 0x0800 )
#define ETHERNET_ETHERTYPE_ARP         ( WORD )( 0x0806 )
#define ETHERNET_ETHERTYPE_IPv6        ( WORD )( 0x08DD )
#define ETHERNET_ETHERTYPE_AARP        ( WORD )( 0x80F3 )
#define ETHERNET_ETHERTYPE_IPX         ( WORD )( 0x8137 )

/*
 ******************************************************************************
 *
 * Data Structures
 *
 ******************************************************************************
 */
/*
   Ethernet Type II Frame Header
   
      macAddrDst  - Destination MAC address
      macAddrSrc  - Source MAC address
      etherType   - Protocol
   
*/
typedef struct _EthernetFrameHeader
{
   MACADDRESS_48 destinationMacAddress;
   MACADDRESS_48 sourceMacAddress;
   WORD etherType;
   
} __attribute__( ( packed) ) EthernetFrameHeader;


/*
 ******************************************************************************
 *
 * Routine Prototypes
 *
 ******************************************************************************
 */
 
/*
 ******************************************************************************
 
   Initializes First Ethernet Controller
   
   Parameters:
      None
      
   Return:
      Interface number 1 thru ( MAX_INTERFACES - 1 ), 0 if not added
      
   Notes:
      None
      
 ******************************************************************************
 */
int AddEthernetInterface( void );

/*
 ******************************************************************************
 
   Returns individual status
      Link
      100 Mbit, else 10 Mbit
      Full duplex, else half duplex
   
   Parameters:
      None
      
   Return:
      TRUE or FALSE for all else
      
   Notes:
      None
      
 ******************************************************************************
 */
BOOL EtherLink( void );
BOOL EtherSpeed100( void );
BOOL EtherDuplex( void );

/*
 ******************************************************************************
 
   Set interface speed, duplex and negotiation maximumcapabilities
   
   Parameters:
      speed100Mbit   - TRUE up to 100Mbit, else 10Mbit
      fullDuplex     - TRUE full duplex, FALSE half duplex only
      autoNegotiate  - TRUE use autonegotiation, FALSE above settings.
      
   Return:
      None
      
   Notes:
      None
      
 ******************************************************************************
 */
/* Used to Manually Configure Ethernet Speed and Duplex Settings */
void ManualEthernetConfig ( BOOL speed100Mbit, BOOL fullDuplex, 
      BOOL autoNegotiate ); 

		

/*
 ******************************************************************************
 
   Disables PHY for saving power.  Will save close to 100mA @ 3.3V when PHY disabled.
     
  Parameters:
      None
      
   Return:
    None
      
   Notes:
      None
******************************************************************************
 */
void DisablePHY( void );


/*      
 ******************************************************************************
 
 Used to turn the PHY back on after calling DisablePHY( );
     
  Parameters:
      None
      
   Return:
    None
      
   Notes:
      None
******************************************************************************
 */
void EnablePHY( void );
		

#endif

