/* $Revision: 1.2 $ */
/* Copyright $Date: 2009/07/24 15:44:44 $ */  

/******************************************************************************
 *
 * Copyright 2009 NetBurner, Inc.  ALL RIGHTS RESERVED
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
 * NetBurner, Inc.
 * 5405 Morehouse Drive
 * San Diego, California 92121
 *
 * information available at:  http://www.netburner.com
 * E-Mail info@netburner.com
 *
 * Support is available: E-Mail support@netburner.com
 *
 *****************************************************************************/

#ifndef _IEEE802_H_
#define _IEEE802_H_

/*
 ******************************************************************************
 *
 * All structures are in network order (big-endian)
 *
 ******************************************************************************
 */
 
/*
 ******************************************************************************
 *
 * Constant definitions
 *
 ******************************************************************************
 */
/*  Destination service access point */
#define IEEE802_DSAP_SNAP_PACKET_UNNUMBERED     ( 0xAA )

/*  Source service access point */
#define IEEE802_SSAP_SNAP_PACKET_UNNUMBERED     ( 0xAA )

/*  Source service access point */
#define IEEE802_CONTROL_SNAP_PACKET_UNNUMBERED  ( 0x03 )

/* 
   OUI 
      IEEE802_OUI_ETHERNET_TYPE  00-00-00
      IEEE801_OUI_DEC            00-00-F8
      
   Notes:
      Only OUI byte 3 changes so far
      
 */
#define IEEE802_OUI_ETHERNET_TYPE               ( 0x00 )
#define IEEE801_OUI_DEC                         ( 0xF8 )

/* OUI length */ 
#define IEEE802_P80211_OUI_LEN                  ( 3 )
 
 
/* 
   IEEE 802.11 Control Frame
      Type
         IEEE80211_TYPE_MANAGEMENT     - Management
         IEEE80211_TYPE_CONTROL        - Control
         IEEE80211_TYPE_DATA           - Data
         
      Subtype 
         IEEE80211_SUBTYPE_DATA        - Data
         IEEE80211_SUBTYPE_NULL        - No data
         
 */
#define IEEE80211_TYPE_MANAGEMENT               ( 0x0 )
#define IEEE80211_TYPE_CONTROL                  ( 0x1 )
#define IEEE80211_TYPE_DATA                     ( 0x2 )

#define IEEE80211_SUBTYPE_DATA                  ( 0x0 )
#define IEEE80211_SUBTYPE_NULL                  ( 0x4 )

/*
 ******************************************************************************
 *
 * Structures
 *
 ******************************************************************************
 */
/*
   IEEE 802.3 Standard Frame Media Access Control (MAC) Header
      destination          - Destination MAC-48
      source               - Source MAC-48 address
      typeOrLength         - Type or length
   
*/
typedef struct _Ieee802_3_Header
{
   MACADDRESS_48 destination;
   MACADDRESS_48 source;
   WORD typeOrLength;
   
} __attribute__(( packed) ) Ieee802_3_Header;

/*
   IEEE 802.2 Logical Link Control (LLC) + 
         Subnetwork Access Protocol (SNAP) header
         
      dsap                 - Destination service access point
      ssap                 - Source service access point
      control              - Control 
      oui                  - Organizationally Unique Identfier
      
      
*/
typedef struct _Ieee802_2_SnapHeader
{   
   /* LLC for SNAP Header 0xAA 0xAA 0x03 */
   BYTE dsap;
   BYTE ssap;
   BYTE control;
   
   /* Organizational Unique Identifier */
   BYTE oui[ IEEE802_P80211_OUI_LEN ];
   
   /* Typically EtherType IPV4 (0x0800) */
   WORD protocolType;
   
}  __attribute__(( packed) ) Ieee802_2_SnapHeader;

/*
 ******************************************************************************
 * IEEE 802.11
 ******************************************************************************
 */
/*
   IEEE 802.11 Packet Header Frame Control Field 
      order                - 1 frames strictly ordered
      wep                  - 1 yes, 0 no
      more                 - More data for destination
      power                - 1 power save, 0 no after transmit
      retry                - Retransmission of previous fragment
      fragmented           - 1 more fragment frames to follow, 0 last frame
      fromDs               - Incoming from distribution system
      toDs                 - Forward to distribution system
      subType              - Subtype
      type                 - Type
      version              - Currently 0
      
 */
typedef struct _FrameControl          
{
   WORD order:1;
   WORD wep:1;
   WORD more:1;
   WORD power:1;
   WORD retry:1;
   WORD fragmented:1;
   WORD fromDs:1;
   WORD toDs:1;
   WORD subType:4;
   WORD type:2;
   WORD version:2;
   
} __attribute__(( packed) ) FrameControl;

/*
   IEEE 802.11 Packet Header Format 
      frameControl         - Frame control
      durationId           - Data frame duration, control id of transmitter
      address[1|2|3|4}     - MAC-48 address based on control frame from/to DS
      sequence             - sequence control
      
   Notes:
      Precedes data followed by 4 byte frame sequence check defined in P802.11
      Addresses
          -------------------------------------------------------------------
         |  To DS  | From DS | Address 1 | Address 2 | Address 3 | Address 4 |
          -------------------------------------------------------------------
         |    0    |    0    |    DA     |    SA     |   BSSID   |    N/A    |
         |    0    |    1    |    DA     |   BSSID   |    SA     |    N/A    |
         |    1    |    0    |   BSSID   |    SA     |    DA     |    N/A    |
         |    1    |    1    |    RA     |    TA     |    DA     |    SA     |
         
      ONLY defined for 3 addresses, the 4 address header is used AP to AP         
         
 */
typedef struct _Ieee802_11_Header          
{
   FrameControl frameControl;
   WORD durationId;
   MACADDRESS_48 address1;
   MACADDRESS_48 address2;
   MACADDRESS_48 address3;
   WORD sequence;
   
} __attribute__(( packed) ) Ieee802_11_Header;

#endif /* _IEEE802_H_ */
