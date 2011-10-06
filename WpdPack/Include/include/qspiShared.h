/* $Revision: 1.4 $ */
/* Copyright $Date: 2009/08/11 23:08:59 $ */  

/******************************************************************************
 *
 * Copyright 1998-2007 NetBurner  ALL RIGHTS RESERVED
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
 *--------------------------------------------------------------------
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

#ifndef _QSPI_SHARED_H_
#define _QSPI_SHARED_H_

/*
 *****************************************************************************
 *
 * Queued Serial Peripheral Interface (QSPI)
 *
 *    Interface consists of data output (QSPI_DOUT), data input (QSPI_DIN),
 *       serial clock (QSPI_CLK) & optionally peripheral chip selects 
 *       (QSPI_CS[3:0]).
 *
 *    SPI parameters are used to match the master (processor) with the slave
 *       device. Chip select can be used to multiplex devices.
 *
 *    The specific hardware initialization for MFCXXXX and MODXXXX are
 *       microprocessor and module specific and need to be correctly 
 *       implemented in the module specific library for each SPI device, for 
 *       example Nburn\MOD5270\system\wifi70_bsp.cpp. 
 *
 *    More than one SPI device requires careful coordination of hardware use 
 *       and synchronization of use.
 *
 *****************************************************************************
 */
 
#ifdef __cplusplus
extern "C"
{
#endif
/*
 *****************************************************************************
 *
 * Definitions
 *
 *****************************************************************************
 */
/* Chip selects
 *    Can connect to QSPI module as supported by the processor.
 */
#define QSPI_CHIP_SELECT_0             ( 0x1 ) 
#define QSPI_CHIP_SELECT_1             ( 0x2 ) 
#define QSPI_CHIP_SELECT_2             ( 0x4 ) 
#define QSPI_CHIP_SELECT_3             ( 0x8 ) 

/* Sets of settings available */
#define QSPI_SETTINGS_MAXIMUM          ( 4 )

/* Block size in bytes */
#define QSPI_BLOCK_SIZE_IN_BYTES       ( 16 ) 

/*
 *****************************************************************************
 *
 * Enumerations
 *
 *****************************************************************************
 */
/*
 * Transfer size in bits, must match settings for qmr.bits
 */ 
typedef enum _SpiTransferSize
{
   TransferSize_16_bits    = 0x0,
   TransferSize_8_bits     = 0x8

} SpiTransferSize;

/*
 *****************************************************************************
 *
 * Runtime Library Routines
 *
 *****************************************************************************
 */

/*
 *****************************************************************************
 *
 * Initialize shared QSPI driver.
 *
 *    Parameters:
 *       isDriveStrengthHigh     - Output drive strength TRUE high, FALSE low
 *       isDoutHighImpedance     - DOUT high impedance between transactions
 *                                     TRUE high impedance, FALSE driven
 *       isClockInactiveHigh     - Clock inactive state 
 *                                     TRUE high, FALSE low
 *       isDataChangeOnLeading   - Clock phase
 *                                     TRUE Data changed on leading edge, 
 *                                        captured on the following edge.
 *                                     FALSE Data captured on leading edge, 
 *                                        changed on the following edge.
 *       isChipSelectActiveLow   - Chips select phase
 *                                     TRUE Active low, inactive high
 *                                     TRUE Active high, inactive low
 *       moduleChipSelects       - Chip selects to integrate with QSPI module.
 *
 *    Return:
 *       None
 *
 *    Notes:
 *       Must be called at least once before any use of the SPI bus.
 *
 *****************************************************************************
 */
extern void QspiInitialize( BOOL isDriveStrengthHigh, BOOL isHighImpedance, 
      BOOL isClockInactiveHigh,BOOL isDataChangeOnLeading, 
      BOOL isChipSelectActiveLow, BYTE moduleChipSelects ); 
 
/*
 *****************************************************************************
 *
 * Allocate SPI bus
 *
 *    Parameters:
 *       spiSetting              - Settings handle
 *       timeout                 - Timeout in ticks
 *
 *    Return:
 *       OS_NO_ERR OK, else probably timed out.
 *
 *    Notes:
 *       Must release when idle to support sharing. Will suspend task until
 *       granted.
 *
 *****************************************************************************
 */
extern BYTE QspiAllocate( int spiSetting, WORD timeout ); 
 
/*
 *****************************************************************************
 *
 * Releases SPI bus
 *
 *    Parameters:
 *       None
 *
 *    Return:
 *       None
 *
 *    Notes:
 *       Will support granting it to any waiting tasks.
 *
 *****************************************************************************
 */
extern void QspiRelease( void ); 
 
/*
 *****************************************************************************
 *
 * Creates bus parameters profile used for transfers.
 *
 *    Parameters:
 *       baudRateInMhz           - Baud rate in Mhz
 *       qspiTransferSize        - Bits transfered for each entry in queue
 *                                     Currently 8 and 16 bits
 *       delayFromCstoClockValid - Delay from assertion of the chip selects to 
 *                                     valid clock transition
 *       delayBetweenTransfers   - Delay after the serial transfer
 *       chipSelects             - Chips select mask
 *       idleValue               - Value while driving idle bus
 *
 *    Return:
 *       >=0 handle assigned to these settings.
 *       <0 Problems with settings.
 *
 *    Notes:
 *       Baud rate has minimum and maximum rates depending on the module.
 *
 *****************************************************************************
 */
extern int QspiCreateSetting( int baudRateInMhz, SpiTransferSize qspiTransferSize,
         WORD delayFromCstoClockValid, WORD delayBetweenTransfers, 
         BYTE chipSelects, WORD idleValue ); 
 
/*
 *****************************************************************************
 *
 * Sets bus parameters used for transfers.
 *
 *    Parameters:
 *       spiSetting              - Settings handle
 *       baudRateInMhz           - Baud rate in Mhz
 *
 *    Return:
 *       None
 *
 *    Notes:
 *       Can be done any time, only used after SpiSet
 *
 *****************************************************************************
 */
extern void QspiChangeBaudRate( int spiSettings, int baudRateInMhz ); 
 
/*
 *****************************************************************************
 *
 * Gets current baud rate in Mhz for the current active setting.
 *
 *    Parameters:
 *       None
 *
 *    Return:
 *       Actual baud rate in Mhz
 *
 *    Notes:
 *       Can be done any time, only used after SpiSet
 *
 *****************************************************************************
 */
extern unsigned long QspiGetBaudRate( void );
 
/*
 *****************************************************************************
 *
 * Change bus setup.
 *
 *    Parameters:
 *       spiSetting              - Settings handle
 *
 *    Return:
 *       None
 *
 *    Notes:
 *       None
 *
 *****************************************************************************
 */
extern void QspiChangeSetting( int spiSetting ); 
 
/*
 *****************************************************************************
 *
 * Send, receive or exchange bytes (8 bits) with slave
 *
 *    Parameters:
 *       transmitBufferPtr       - Buffer of bytes to send, NULL for receiving
 *       receiveBufferPtr        - Buffer to receive data, NULL for sending
 *       byteCount               - Count of bytes to send or receive
 *       finishedSemPtr          - Optional semaphore to set when completed
 *
 *    Return:
 *       None
 *
 *    Notes:
 *       None
 *
 *****************************************************************************
 */
extern void QspiExchangeBytes( BYTE* transmitBufferPtr, BYTE* receiveBufferPtr, 
      DWORD byteCount, OS_SEM* finishedSemPtr ); 

/*
 *****************************************************************************
 *
 * Send, receive or exchange data word with slave (9-16 bits)
 *
 *    Parameters:
 *       transmitBufferPtr       - Buffer of words to send, NULL for receiving
 *       receiveBufferPtr        - Buffer to receive data, NULL for sending
 *       byteCount               - Count of bytes to send or receive
 *       finishedSemPtr          - Optional semaphore to set when completed
 *
 *    Return:
 *       None
 *
 *    Notes:
 *       None
 *
 *****************************************************************************
 */
extern void QspiExchangeWords( WORD* transmitBufferPtr, WORD* receiveBufferPtr, 
      DWORD byteCount, OS_SEM* finishedSemPtr ); 

/*
 *****************************************************************************
 *
 * Setup chip select(s) as user not module controlled
 *
 *    Parameters:
 *       chipSelects             - Chips select mask
 *
 *    Return:
 *       None
 *
 *    Notes:
 *       Polarity set by isChipSelectActiveLow parameter of QspiInitialize.
 *
 *****************************************************************************
 */
extern void QspiUserChipSelects( BYTE chipSelects );
 
/*
 *****************************************************************************
 *
 * Select SPI device(s) by asserting chip select(s)
 *
 *    Parameters:
 *       chipSelects             - Chips select mask
 *
 *    Return:
 *       None
 *
 *    Notes:
 *       None
 *
 *****************************************************************************
 */
extern void QspiSelectDevice( BYTE chipSelects ); 

/*
 *****************************************************************************
 *
 * Release SPI device(s) by deasserting chip select(s)
 *
 *    Parameters:
 *       chipSelects             - Chips select mask
 *
 *    Return:
 *       None
 *
 *    Notes:
 *       None
 *
 *****************************************************************************
 */
extern void QspiReleaseDevice( BYTE chipSelects ); 


/*
 *****************************************************************************
 *
 * SDIO in the SPI Mode Functions (Driver use only)
 *
 *****************************************************************************
 */
/*
 *****************************************************************************
 *
 * Send command, process acknowledgement and send or receive data
 *
 *    Parameters:
 *       commandBufferPtr        - Buffer containing SDIO command (6 bytes)
 *       r5ResponsePtr           - Buffer containing two bytes for SPI response
 *       sendData                - TRUE send data else receive data
 *       dataBufferPtr           - Buffer of bytes to send or recieve data
 *       byteCount               - Count of bytes to send or receive
 *       responseTimeout         - Response delay in ticks
 *
 *    Return:
 *       TRUE - success, FALSE response timeout
 *
 *    Notes:
 *       SDIO using the SPI mode.
 *
 *****************************************************************************
 */
extern BOOL QspiSdioDataExchange( BYTE* commandBufferPtr, BYTE* r5ResponsePtr, 
      BOOL sendData, BYTE* dataBufferPtr, DWORD byteCount, 
      DWORD responseTimeout );
       
#ifdef __cplusplus
}
#endif

#endif /* #ifndef _QSPI_SHARED_H_ */

