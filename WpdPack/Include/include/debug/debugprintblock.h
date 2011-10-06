/* $Revision: 1.1 $ */
/* Copyright $Date: 2008/10/17 21:47:46 $ */  

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

#ifndef _DEBUG_PRINT_BLOCK_H_
#define _DEBUG_PRINT_BLOCK_H_

/*
 * Display of data in blocks
 *    Should be defined if needed, unnecessary burden to release code
 *
 */
/*
 ******************************************************************************
 *
 * Definitions
 *
 ******************************************************************************
 */

#ifdef __cplusplus 
extern "C" {
#endif
/*
 ******************************************************************************
 *
 * Print block "C" Library Interface
 *
 ******************************************************************************
 */

/*
 ******************************************************************************
 
   Print Block
      Print block of data in comma delimited format using iprintf

   Parameters:
      typePtr              - Memory needed in bytes
      dataSize             - Bytes in each data item
      blockPtr             - Buffer with block of data
      byteCount            - Byte count
   
   Return:
      None
   
   Notes:
      None
 ******************************************************************************
 */
void debugPrintBlock( const char* typePtr, size_t dataSize, 
      unsigned char* blockPtr, unsigned int byteCount );
      
#ifdef __cplusplus
};
#endif
#endif   /* #ifndef _DEBUG_PRINT_BLOCK_H_ */
