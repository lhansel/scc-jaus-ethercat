/* $Revision: 1.35 $ */
/* Copyright $Date: 2009/11/13 11:17:59 $ */  

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
 * 5405 Morehouse Dr.
 * San Diego, Ca. 92121
 *
 * information available at:  http://www.netburner.com
 * E-Mail info@netburner.com
 *
 * Support is available: E-Mail support@netburner.com
 *
 *****************************************************************************/

#ifndef _NB_UTILS_H
#define _NB_UTILS_H

#include <predef.h>
#ifndef NB_NET_TYPES_H
#include "nettypes.h"
#endif // NB_NET_TYPES_H

//
// Flags to control the debug print functions
//
#define DB_TCPIP     (    1 )
#define DB_HTTP      (    2 )
#define DB_ETHER     (    4 )
#define DB_RTOS      (    8 )
#define DB_BUFFER    (   16 )
#define DB_PPP       (   32 )
#define DB_AU        (   64 )
#define DB_MAIL      (  128 )
#define DB_IP        (  256 )
#define DB_TCPDATA   (  512 )
#define DB_SSL       ( 1024 )
#define DB_SNMP      ( 2048 )


////////////////////////////////////////////////////////////////////////////////
// GLOBAL VARIABLES
//
extern VDWORD Secs;                               // Number of seconds since system start
extern VDWORD TimeTick;                           // Number of time ticks since system start


#ifdef __cplusplus 
extern "C"
{
#endif // __cplusplus


////////////////////////////////////////////////////////////////////////////////
// DIAGNOSTIC FUNCTIONS
//
void ShowCounters();                              // Dump all system counters to stdio
void sShowCounters( char *buffer, int slen );     // Dump all system counters to a large memory buffer
#ifdef FILE
void fShowCounters( FILE *fp );                   // Dump all system counters to a file descriptor
#endif // FILE


////////////////////////////////////////////////////////////////////////////////
// UTILITY I/O FUNCTIONS
//
void ShowData( PBYTE fromptr, WORD len );         // Dump a block of data to stdio and show in ASCII and hex
void ShowMac( MACADR *ma );                       // Dump a MAC address to stdio
void outbyte( char c );                           // Write out a single, unbuffered byte to stdio
void print( const char * );                       // Write out a zero-terminated, unbuffered string
void putnum( int i );                             // Write out a hexadecimal, unbuffered number to stdio
void putbytenum( unsigned char c );               // Write out a hexadecimal, unbuffered byte to stdio
IPADDR AsciiToIp( const char *p );                // Convert an ASCII IP string to an IP address
void ShowIP( IPADDR ia );                         // Dump an IP address in ASCII IP string format to stdio
char *itoa( int value, char *buffer, int radix ); // Converts an integer to ASCII (adds the stdlib itoa)


////////////////////////////////////////////////////////////////////////////////
// HIGHER RESOLUTION COUNTER READ FUNCTION
//
extern DWORD GetPreciseTime( void );              // Gets the time tick since system start at a higher
                                                  // resolution, depending on the platform:  0.868-us for
                                                  // MOD5234/70, and 1.929-us for MOD5282


void kill( int i1 );
void _exit( int i );
int _fini( void );


#ifdef _STDIO_H_
#ifndef FILE
void fShowCounters( FILE *fp );
#endif // FILE
void fShowMac( FILE *fp, MACADR *ma );
void fShowIP( FILE *fp, IPADDR ia );
#endif // _STDIO_H_

/*
  Convert Binary to/from Hexadecimal ASCII

  Parameters:
     fromBufferPtr      - Source data
     fromByteCount      - Source byte count
     toBufferPtr        - Converted data
     toByteCount        - Converted byte count
  
  Return:
     Pointer to next free byte in converted buffer
  
  Notes:
     Hexadecimal ASCII buffer must be at least twice the size of the binary
     buffer size.
  
*/
unsigned char* convertBinaryToHexAscii( 
      unsigned char* fromBufferPtr, unsigned int fromByteCount, 
      unsigned char* toBufferPtr, unsigned int toByteCount );

unsigned char* convertHexAsciiToBinary( 
      unsigned char* fromBufferPtr, unsigned int fromByteCount, 
      unsigned char* toBufferPtr, unsigned int toByteCount );


#ifdef __cplusplus
};
#endif // __cplusplus


////////////////////////////////////////////////////////////////////////////////
// DEBUG FUNCTIONS
//
#if( ( defined _DEBUG ) || ( defined _DEBUG_PRINT ) ) 
   extern unsigned int DB_FLAGS;
   void SetLogLevel();
   #define ASSERT( x )           if ( !( x ) ) \
                                 { \
                                    iprintf( "ASSERT failed at %d of %s\n", \
                                          __LINE__, __FILE__ ); \
                                    asm ( "Halt" ); \
                                 }
   #define DBPRINT( x, y )       if ( DB_FLAGS & x ) printf( y );
   #define DBNUM( x, y )         if ( DB_FLAGS & x ) putnum( y );
   #define DBBYTE( x, y )        if ( DB_FLAGS & x ) putbytenum( y );
   #define DBPRINTF( x, ... )    if ( DB_FLAGS & x ) printf( __VA_ARGS__ );
   #define DBIPRINTF( x, ... )   if ( DB_FLAGS & x ) iprintf( __VA_ARGS__ );
#else
   #define ASSERT( x )           ( (void)0 )
   #define DBPRINT( x, y )       ( (void)0 )
   #define DBNUM( x, y )         ( (void)0 )
   #define DBBYTE( x, y )        ( (void)0 )
   #define DBPRINTF( x, ... )    ( (void)0 )
   #define DBIPRINTF( x, ... )   ( (void)0 )
#endif // _DEBUG


#if( ( defined _DEBUG ) || ( defined _DEBUG_PRINT ) )
   #define PPPDBPRINT(x)  DBPRINT(DB_PPP,(x))
   #define PPPDBPRINTF( ... )  DBPRINTF(DB_PPP, __VA_ARGS__)
   #define PPPDBIPRINTF( ... )  DBIPRINTF(DB_PPP, __VA_ARGS__)
   #define PPPDBNUM(x)    DBNUM(DB_PPP,(x))
   #define PPPDBBYTE(x)   DBBYTE(DB_PPP,(x))
#else
   #define PPPDBPRINT(x)
   #define PPPDBPRINTF( ... )
   #define PPPDBIPRINTF( ... )
   #define PPPDBNUM(x)
   #define PPPDBBYTE(x)
#endif


#ifdef __cplusplus 
extern "C"
{
#endif // __cplusplus

////////////////////////////////////////////////////////////////////////////////
// DEVELOPMENT BOARD I/O FUNCTIONS
//
BOOL OnModDev70( void );                          // Return TRUE if on MOD-DEV-70, otherwise FALSE
void putleds( unsigned char c );                  // Set the LEDs on the MOD-DEV-70/100
unsigned char getleds( );                         // Get the LEDs state from CPLD, MOD-DEV-100 only
void putdisp( unsigned short w );                 // Set the 7-segment LEDs on the MOD-DEV-100, BCD input, CPLD controls segmnet switching
unsigned short getdisp( );                        // Get the 7-segment LEDs on the MOD-DEV-100, BCD
unsigned char getdipsw();                         // Read the DIP switch values on the MOD-DEV-70/100

//--- The following functions are only valid on v1.12+ revisions of the dev board
//--- CPLD programming files are available to upgrade older board revs
// Set the 7-segment LEDs on the MOD-DEV-100 
void putSegments( unsigned char DisplayMask,  unsigned char DisplayData);   //Display Mask - 4bit value indicates which display shows value,  DisplayData - Segment bit 7 is decimal point, bits 0-6 = Segments A-G 
void putDecimal( unsigned char DisplayMask );      // Set the 7-segment decimal point on the MOD-DEV-100, Display Mask - 4bit value indicates which display has decimal point
unsigned char getCPLDver();                        // returns the version # of the CPLD 
unsigned char getCPLDrev();                        // returns the revision # of the CPLD   


//  Predefined segments for the putSegments display function
#define SevenSeg_0         (0x3F)
#define SevenSeg_1         (0x06)
#define SevenSeg_2         (0x5B)
#define SevenSeg_3         (0x4F) 
#define SevenSeg_4         (0x66)
#define SevenSeg_5         (0x6D) 
#define SevenSeg_6         (0x7C)
#define SevenSeg_7         (0x07) 
#define SevenSeg_8         (0x7F)
#define SevenSeg_9         (0x67) 
#define SevenSeg_A         (0x77) 
#define SevenSeg_B         (0x7F)
#define SevenSeg_C         (0x39) 
#define SevenSeg_D         (0x3F)
#define SevenSeg_E         (0x79)
#define SevenSeg_F         (0x71)
#define SevenSeg_H         (0x76)
#define SevenSeg_I         (0x06)
#define SevenSeg_J         (0x1E)
#define SevenSeg_L         (0x38)
#define SevenSeg_O         (0x3F)
#define SevenSeg_P         (0x73)
#define SevenSeg_S         (0x6D)
#define SevenSeg_U         (0x3E)
#define SevenSeg_b         (0x7C)
#define SevenSeg_c         (0x58)
#define SevenSeg_d         (0x5E)
#define SevenSeg_h         (0x74)
#define SevenSeg_l         (0x06)
#define SevenSeg_n         (0x54)
#define SevenSeg_o         (0x53)
#define SevenSeg_r         (0x50)
#define SevenSeg_u         (0x1C)
#define SevenSeg_Dash      (0x40)
#define SevenSeg_Decimal   (0x80)
#define SevenSeg_OFF       (0x00) 

#ifdef __cplusplus
};
#endif // __cplusplus

#endif /* #ifndef _NB_UTILS_H */ 
