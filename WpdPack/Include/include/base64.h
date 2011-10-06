/* $Revision: 1.4 $ */
/* Copyright $Date: 2008/09/12 20:10:26 $ */  

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
#ifndef _BASE64_H_
#define _BASE64_H_

/*
 ******************************************************************************
 
   Decodes a null terminated base 64 string into bytes
   
   Parameters:
      input                   - Base 64 string
      outputbuf               - Resulting decoded data
      
   Return:
      Number of bytes returned in outputbuf
      
   Notes:
      outputbuf should be at least the size of input divided by 4, rounded up ???
      Does not null terminate results
      
 ******************************************************************************
 */
int Base64Decode( const char* input , PBYTE outputbuf );

/*
 ******************************************************************************
 
   Encodes arbitrary binary bytes into base 64 string
   
   Parameters:
      input                   - Data
      inlen                   - Length of data
      outputbuf               - Resulting encoded data
      
   Return:
      Number of bytes returned in outputbuf
      
   Notes:
      outputbuf should be at least ???
      Does not null terminate results but terminates with an '='
      
 ******************************************************************************
 */
int Base64Encode( PBYTE input , int inlen, char* outputbuf );

#ifdef TEST_BASE64
   /* Test string */
   const char * base64msg = \
"TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFz\
b24sIGJ1dCBieSB0aGlzIHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aGljaCB\
pcyBhIGx1c3Qgb2YgdGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbi\
B0aGUgY29udGludWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBle\
GNlZWRzIHRoZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4=";
#endif /* #ifdef TEST_BASE64 */

#endif /* #ifndef _BASE64_H_ */


