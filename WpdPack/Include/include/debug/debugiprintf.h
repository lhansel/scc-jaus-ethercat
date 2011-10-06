/* $Revision: 1.1 $ */
/* Copyright $Date: 2009/07/24 15:52:53 $ */  

/******************************************************************************
 *
 * Copyright 2008 NetBurner, Inc.  ALL RIGHTS RESERVED
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
 * 5405 Morehouse Dr.
 * San Diego, Ca. 92121
 *
 * information available at:  http://www.netburner.com
 * E-Mail info@netburner.com
 *
 * Support is available: E-Mail support@netburner.com
 *
 *****************************************************************************/

#ifndef _DEBUG_IPRINTF_H_
#define _DEBUG_IPRINTF_H_

/*
 ******************************************************************************
 *
 * Definitions
 *
 ******************************************************************************
 */
/*
 * To include feature define NB_DEBUG_IPRINTF_CONTROL as DWORD for choices
 *    Example:
 *       Declare once
 *          DWORD WifiDebug = ( NB_DEBUG_IPRINTF_INIT | NB_DEBUG_IPRINTF_ERROR );
 *       Define before "include"ing this file
 *          #define NB_DEBUG_IPRINTF_CONTROL   WifiDebug
 *
 */
/*
 * Debug iprintf choices
 *    User defined bits 9 through 27
 *
 */
#define NB_DEBUG_OFF          ( 0x00000000 )
#define NB_DEBUG_ERROR        ( 0x00000001 )
#define NB_DEBUG_INIT         ( 0x00000002 )
#define NB_DEBUG_INT          ( 0x00000004 )
#define NB_DEBUG_RX           ( 0x00000008 )
#define NB_DEBUG_TX           ( 0x00000010 )
#define NB_DEBUG_USER_BEG     ( 0x00010000 )
#define NB_DEBUG_USER_END     ( 0x08000000 )
#define NB_DEBUG_TRACE        ( 0x80000100 )
#define NB_DEBUG_ALL          ( 0xFFFFFFFF )
 
/*
 ******************************************************************************
 *
 * NB_DEBUG_IPRINTF
 *
 ******************************************************************************
 */
#ifdef NB_DEBUG_IPRINTF_CONTROL

   #include <utils.h>
   extern DWORD NB_DEBUG_IPRINTF_CONTROL;
   #define NB_DEBUG_IPRINTF( choice, ... ) \
   { \
      if ( ( NB_DEBUG_IPRINTF_CONTROL & choice ) == choice ) \
      { \
         (void)iprintf( "NB Debug %s, line %d, at %ld\r\n", \
            __FUNCTION__, __LINE__, TimeTick ); \
         iprintf( __VA_ARGS__ ); \
         iprintf( "\r\n" ); \
      } \
   } 
     
#else /* #ifdef NB_DEBUG_IPRINTF_CONTROL */

   #define NB_DEBUG_IPRINTF( choice, ... ) \
         { (void)0; }
         
#endif /* #ifdef NB_DEBUG_IPRINTF_CONTROL */

#endif   /* #ifndef _DEBUG_IPRINTF_H_ */
