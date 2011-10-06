/* $Revision: 1.12 $ */
/* Copyright $Date: 2008/10/08 16:04:55 $ */  

/******************************************************************************
 *
 * Copyright 1998-2008 NetBurner, Inc.  ALL RIGHTS RESERVED
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

#ifndef _NB_ARP_H
#define _NB_ARP_H

/*
 ******************************************************************************
 *
 * Runtime Libraries Routine Prototypes
 *
 ******************************************************************************
 */
/*Section IP functions */
/*Dump the Arp cache to stdio */
void ShowArp();
void fShowArp( FILE *fp );




/*
 ******************************************************************************
 
   Get the MAC address from an IP address
   This does not send and arp it only checks the arp cache.
   If you want it to send an arp then ping the address before calling this function.
   
   
   Parameters  ip address to look up.
			mac MACADR structure to hold the result.(C++ pass by reference)
      
   Return:
      True if it found a valid arp entry.
	 False if it did not.
      
 ******************************************************************************
 */
BOOL GetArpMacFromIp(IPADDR ip,MACADR & ma);





/*
 ******************************************************************************
 
   Send Gratuitous ARP Request
   
   Parameters:
      interfaceNumber         - Interface number
      
   Return:
      None
      
   Notes:
      Used after adding an interface or changing an IP address to update 
      ethernet network device cache(s).  Requires a valid IP address via 
      permanent settings or successful DHCP request.
      
      Currently only implemented for IPV4.
      
 ******************************************************************************
 */
void sendGratuitousArp( int interfaceNumber = 0 ); 


/*INTERNAL FUNCTIONS */
void processArp( PoolPtr p, PEFRAME pF );

void AddCheckArp( MACADR *ma, IPADDR ip, int ifnum );
void DeleteArpFromIp(IPADDR ip);

void RouteOut( PEFRAME pf, IPADDR ip, PoolPtr p );
void RouteOutVia( PEFRAME pf, IPADDR ip, PoolPtr p, int intf );

void AgeArp();

void InitializeArp();

BOOL IsMyAddressUsedArpDetect(WORD timeout, int interface=0);




/*
 ******************************************************************************
 *
 * Data Structures
 *
 ******************************************************************************
 */

/*
 ******************************************************************************
 
   Address Resolution Protocol (ARP) Packet Structure
   
      hard_Type            - Hardware type (HTYPE)
      prot_Type            - Protocol type (PTYPE)
      hard_size            - Hardware length (HLEN)
      
         theMac            - Interface ethernet MAC address
   Notes:
      Should not change data sizes and always add to the end to avoid breaking
      use for interface configuration.         
      
 ******************************************************************************
 */
typedef struct
{
      WORD hard_Type;
      WORD prot_Type;
      BYTE hard_size;
      BYTE prot_size;
      WORD op_code;
      MACADR sender_phy;
      IPADDR sender_Ip;
      MACADR target_phy;
      IPADDR target_Ip;
}ARP;

typedef ARP *PARP;


#endif

