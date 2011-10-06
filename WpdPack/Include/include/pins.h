/* $Revision: 1.6 $ */
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

#ifndef _NB_PINS_H_
#define _NB_PINS_H_


#include <pinconstant.h>


#if ( !defined ( PK70 ) && !defined ( SB70LC ) )
/**
 * The following class is created to assist in processor pin configuration and
 * operation for GPIO and special functions. Each pin is defined by the system
 * in the \Nburn\<Platform>\system and \Nburn\<Platform>\include directories for
 * the specific platform you are using.
 *
 * Examples:
 * J1[5] = 1;                        Set pin J1-5 high
 * J2[30] = 0;                       Set pin J2-30 low
 * J1[5].hiz();                      Set pin J1-5 to be a high impedance input
 * BOOL bpinstate = J2[30];          Set the pin to be an input and read
 * if ( !J2[30] )
 *    iprintf( "The pin is low" );
 */
class PinIO
{
   BYTE connector, pinnum;
   PinIO( int j, int n ) { connector = j; pinnum = n; };

   public:
      void set( BOOL = TRUE );                                    // Set output high
      void clr() { set( FALSE ); };                               // Set output low
      BOOL read();                                                // Read pin hi/low state
      void hiz() { read(); };                                     // Set output to tristate
      void drive();                                               // Turn output on (opposite of tristate)
      void function( int ft );                                    // Set pin to special function
      PinIO &operator = ( BOOL b ) { set( b ); return *this; };
      PinIO &operator = ( int  i ) { set( i ); return *this; }; 
      operator int() { return read(); };                          // Read and return int value
      operator BOOL() { return read(); };                         // Read and return BOOL value
      operator bool() { return ( read() != 0 ); };                // Read and return boolean value
      friend class PinIOJ1Array;
      friend class PinIOJ2Array;
};


class PinIOJ1Array
{
   public:
      PinIO operator [] ( int n ) { return PinIO( 1, n ); };
};


class PinIOJ2Array
{
   public:
      PinIO operator [] ( int n ) { return PinIO( 2, n ); };
};


extern PinIOJ1Array J1;
extern PinIOJ2Array J2;

#else

/**
 * The following class is created to assist in processor pin configuration and
 * operation for GPIO and special functions. Each pin is defined by the system
 * in the \Nburn\<Platform>\system and \Nburn\<Platform>\include directories for
 * the specific platform you are using.
 *
 * Examples:
 *  Pins[32] = 1;                     Set pin 32 high 
 *  Pins[32] = 0;                     Set pin 32 low 
 *  Pins[32].hiz();                   Set pin 32 to be a high impedance input
 *  BOOL bpinstate = Pins[32];        Set the pin to be an input and read
 *  if( !Pins[32] )
 *     iprintf( "The pin is low" );
 */
class PinIO
{
   BYTE pinnum;
   PinIO( int n ) { pinnum = n; };

   public:
      void set( BOOL = TRUE );                                    // Set output high
      void clr() { set( FALSE ); };                               // Set output low
      BOOL read();                                                // Read pin hi/low state
      void hiz() { read(); };                                     // Set output to tristate
      void drive();                                               // Turn output on (opposite of tristate)
      void function( int ft );                                    // Set pin to special function
      PinIO &operator = ( BOOL b ) { set( b ); return *this; };
      PinIO &operator = ( int  i ) { set( i ); return *this; };
      operator int() { return ( int )read();};                    // Read and return int value
      operator BOOL() { return ( BOOL ) read(); };                // Read and return BOOL value
      operator bool() { return ( bool ) read(); };                // Read and return boolean value
      friend class PinIOArray;
};


class PinIOArray
{
   public:
      PinIO operator[] ( int n ) { return PinIO( n ); };
};


extern PinIOArray Pins;
#endif /* ( !defined ( PK70 ) && !defined ( SB70LC ) ) */


#endif /* _NB_PINS_H_ */
