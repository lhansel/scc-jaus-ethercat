/* $Revision: 1.11 $ */
/* Copyright $Date: 2008/09/30 20:27:38 $ */
/*******************************************************************************
 *
 * Copyright 1998-2008 NetBurner, Inc.  ALL RIGHTS RESERVED
 *
 * Permission is hereby granted to purchasers of NetBurner hardware to use or
 * modify this computer program for any use as long as the resultant program is
 * only executed on NetBurner-provided hardware.
 *
 * No other rights to use this program or its derivatives in part or in whole
 * are granted.
 *
 * It may be possible to license this or other NetBurner software for use on
 * non-NetBurner hardware.  Please contact licensing@netburner.com for more
 * information.
 *
 * NetBurner makes no representation or warranties with respect to the
 * performance of this computer program, and specifically disclaims any
 * responsibility for any damages, special or consequential, connected with use
 * of this program.
 *
 * ----------------------------------------------------------------------------
 *
 * NetBurner, Inc.
 * 5405 Morehouse Drive
 * San Diego, CA  92121
 *
 * Information available at:  http://www.netburner.com
 * Support available at:      http://support.netburner.com
 *
 ******************************************************************************/

#ifndef NB_NET_TYPES_H
#define NB_NET_TYPES_H


#include <basictypes.h>


#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */


/*
 *******************************************************************************
 *
 * Definitions
 *
 *******************************************************************************
 */

#define PPP_TYPE       ( 0x0021 )   /* These are Big Endian constants! */
#define EIP_TYPE       ( 0x0800 )   /* These are Big Endian constants! */
#define HARD_ENET      ( 0x0001 )   /* These are Big Endian constants! */
#define EARP_TYPE      ( 0x0806 )
#define ARP_REQUEST    (   0x01 )
#define ARP_RESPONSE   (   0x02 )


/* 
 * MAC address
 */
#define MACADDRESS_OCTETS_48   ( 6 )


/*
 *******************************************************************************
 *
 * Data Structures
 *
 *******************************************************************************
 */

/*
 * MAC address
 *    octet - address bytes
 */
typedef struct _MACADDRESS_48
{
   BYTE octet[MACADDRESS_OCTETS_48];
} __attribute__( ( packed ) ) MACADDRESS_48;


typedef struct
{
   WORD phywadr[3];
} MACADR;


extern MACADR ENET_BCAST;
extern MACADR ENET_ZERO;


typedef DWORD IPADDR;


/*
 * Definition for an Ethernet frame
 */
typedef struct
{
   MACADR dest_addr;
   MACADR src_addr;
   WORD eType;
   BYTE pData[4];
} EFRAME;


typedef EFRAME *PEFRAME;


#ifdef __cplusplus 
};
#endif /* __cplusplus */


#endif /* NB_NET_TYPES_H */
