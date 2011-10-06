/* $Revision: 1.1 $ */
/* Copyright $Date: 2008/06/02 20:29:55 $ */  

/******************************************************************************
 *
 * Copyright 1998 - 2007 NetBurner, Inc.  ALL RIGHTS RESERVED
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

#ifndef _WIFI_BSP_H_
#define _WIFI_BSP_H_

typedef void ( WiFiISR )();

/* The asociated BSP must export the folowing five functions to work with the WiFi interface */
WORD *WiFiBSP_SetUpWiFiHardware( void );

void WiFiBSP_SetUpWiFiISR( WiFiISR *pisr );

void WiFiBSP_AckWiFiISR( void );

void WiFiBSP_DisAbleWiFiISR( void );

void WiFiBSP_EnAbleWiFiISR( void );

WORD GetTickFraction( void );

#endif /* #ifndef _WIFI_BSP_H_ */
