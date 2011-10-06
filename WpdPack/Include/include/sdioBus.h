/* $Revision: 1.7 $ */
/* Copyright $Date: 2009/08/31 18:10:52 $ */  

/******************************************************************************
 *
 * Copyright 2009 NetBurner, Inc.  ALL RIGHTS RESERVED
 *   Permission is hereby granted to purchasers of NetBurner Hardware
 *   to use or modify this computer program for any use as long as the
 *   resultant program is only executed on NetBurner provided hardware.
 *
 *   No other rights to use this program or its derivatives in part or
 *   in whole are granted.
 *
 *   It may be possible to license this or other NetBurner software for
 *   use on non-NetBurner Hardware.
 *   Please contact sales@Netburner.com for more information.
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

#ifndef _SDIOBUS_H_
#define _SDIOBUS_H_

/*
 ******************************************************************************
 *
 * Debugging
 *
 ******************************************************************************
 */
/* Library debugging switch */
#define SDIO_BUS_DEBUG                  ( 1 )
 
#ifdef SDIO_BUS_DEBUG 
   #define SDIO_DEBUG_IPRINTF( ... )\
{ \
   iprintf( "%s:%d", __FUNCTION__, __LINE__ ); \
   iprintf( __VA_ARGS__ ); \
   iprintf( "\r\n" ); \
}   
#else /* #ifdef SDIO_BUS_DEBUG  */
   #define SDIO_DEBUG_IPRINTF( ... )  ( (void)0 )
#endif /* #ifdef SDIO_BUS_DEBUG  */

/*
 ******************************************************************************
 *
 * Runtime Library Definitions
 *
 ******************************************************************************
 */
/* Bus type */
#define SDIO_SPI_BUS             ( 1 ) 
 
/*
 ******************************************************************************
 *
 * Typedefs
 *
 ******************************************************************************
 */
/*
 ******************************************************************************
 
   Controller interrupt service routine (ISR)
   
   Parameters:
      None
      
   Return:
      None
      
   Notes:
      None
      
 ******************************************************************************
 */
extern "C" typedef void ( *SdioInterruptService )( void );

/*
 ******************************************************************************
 *
 * SDIO Bus Base Class
 *
 ******************************************************************************
 */
class SdioBus
{
   public:
      /*** Constructor ***/
      SdioBus( DWORD speed, DWORD connectTimeout, DWORD responseTimeout );

      /*** Destructor ***/
      virtual ~SdioBus();

      /*** Methods ***/
      /* Attach to bus */
      virtual BOOL attachBus( void ) = 0;
      
      /* Acquire bus */
      virtual BOOL acquireBus( void ) = 0;
      
      /* Release bus */
      virtual void releaseBus( void ) = 0;
      
      /* Select card on bus */
      virtual void selectCard( void ) = 0;
      
      /* Release card */
      virtual void releaseCard( void ) = 0;
      
      /* Send command */
      virtual BOOL sendCommand( SdioCommand& command ) = 0;
      
      /* Receive response */
      virtual BOOL receiveResponse( SdioResponse& response, BOOL idle = TRUE  ) = 0;
      
      /* Send data */
      virtual BOOL sendData( const PBYTE dataPtr, ssize_t dataLength ) = 0;
      
      /* Receive data */
      virtual BOOL receiveData( PBYTE dataPtr, ssize_t dataLength ) = 0;
      
      /* Idle bus */
      virtual void idleBus( void ) = 0;
      
      /* Execute extended command (e.g. CMD53) */
      virtual BOOL executeExtendedCommand( SdioCommand& command, 
            SdioResponse& response, BOOL writeData, PBYTE dataPtr, 
            ssize_t dataLength ) = 0;
      
      /*** Accessors ***/
      /* Bus speed in Hz */
      DWORD getSpeed( void );
      
      /* Connect timeout */
      DWORD getConnectTimeout( void );
      
      /* Connect timeout */
      DWORD getResponseTimeout( void );
      
      /* Valid ? */
      BOOL isValid( void );
      
   protected:
      /* None */
       
   private:
      /*** Methods ***/
      /* None */
      
      /*** Data Members ***/
      /* Bus speed in Hz */
      DWORD __speed;
      
      /* Connect timeouts in ticks */
      DWORD __connectTimeout;
      
      /* Response timeouts in ticks */
      DWORD __responseTimeout;
      
      /* Valid? */
      BOOL __valid;

};      

/*
 ******************************************************************************
 *
 * SDIO Bus SPI Mode
 *
 ******************************************************************************
 */
class SdioBusSpiMode : public SdioBus
{
   public:
      /*** Constructor ***/
      SdioBusSpiMode( DWORD speed, DWORD connectTimeout, DWORD responseTimeout, 
            ssize_t idleByteCount, WORD idleFillValue, int chipSelectMask,
            NetDeviceSelectDetail chipSelectDetail );

      /*** Destructor ***/
      ~SdioBusSpiMode();

      /*** Methods ***/
      /* Attach to bus */
      BOOL attachBus( void );
      
      /* Acquire bus */
      BOOL acquireBus( void );
      
      /* Release bus */
      void releaseBus( void );
      
      /* Select card on bus */
      void selectCard( void );
      
      /* Release card */
      void releaseCard( void );
      
      /* Send command */
      BOOL sendCommand( SdioCommand& command );
      
      /* Receive response */
      BOOL receiveResponse( SdioResponse& response, BOOL idleBus = TRUE );
      
      /* Send data */
      BOOL sendData( const PBYTE dataPtr, ssize_t dataLength );
      
      /* Receive data */
      BOOL receiveData( PBYTE dataPtr, ssize_t dataLength );
      
      /* Idle bus */
      void idleBus( void );
      
      /* Execute extended command (e.g. CMD53) */
      BOOL executeExtendedCommand( SdioCommand& command, 
            SdioResponse& response, BOOL writeData, PBYTE dataPtr, 
            ssize_t dataLength );
      
   protected:
      /* None */
       
   private:
      /*** Methods ***/
      /* Wait for and the get data received token */
      BYTE waitForDataReceived( void );
      
      /* Waits for data start token */
      BOOL waitForData( void );
      
      /*** Data Members ***/
      /* SPI setting handle*/
      int __spiSetting;
      
      /* SPI chip select mask */
      int __chipSelectMask;
      
      /* SPI chip select detail */
      NetDeviceSelectDetail __chipSelectDetail;
      
      /* SPI chip select mask */
      int __chipSelectPin;
      
      /* Bytes to idle bus */
      ssize_t __idleByteCount;
      
      /* Value used to idle bus */
      WORD __idleFillValue;
      

};      

#endif /* _SDIOBUS_H_ */
