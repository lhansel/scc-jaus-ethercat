/* $Revision: 1.4 $ */
/* Copyright $Date: 2007/12/04 21:16:54 $ */  

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
 *---------------------------------------------------------------------
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

#ifndef _QSPI_H
#define _QSPI_H
#include <basictypes.h>

/*
 *****************************************************************************-
 *
 * Queued Serial Peripheral Interface (QSPI)
 *
 *    Interface consists of data output (QSPI_DOUT), data input (QSPI_DIN),
 *       serial clock (QSPI_CLK) & peripheral chip selects (QSPI_CS[3:0]).
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
 *****************************************************************************-
 */
 
#ifdef __cplusplus
extern "C"
{
#endif

/*
   QSPI state
*/   
#define QSPI_OK      ( 0 )
#define QSPI_BUSY    ( 1 )

/*
 *****************************************************************************-
 *
 * Initialize Queued Serial Peripheral Interface (QSPI)
 *
 *    Parameters:
 *       baudRateInBps           - Maximum speed requested. (1) (2)
 *       transferSizeInBits      - 8 thru 32 valid (3)
 *       peripheralChipSelects   - QSPI_CS[3:0] (4)
 *       chipSelectPolarity      - 0 inactive logic level low, 1 high
 *       clockPolarity           - 0 inactive logic level low, 1 high
 *       clockPhase              - 0 (5) or 1 (6)
 *       doutHiz                 - Data output high impedance between transfers
 *       csToClockDelay          - Delay form chip select to valid clock (7)
 *       delayAfterTransfer      - Delay between data transfers (8)
 *
 *    Return:
 *       Current QSPI state      - QSPI_OK success or QSPI_BUSY busy
 *
 *    Notes:
 *       (1) Maximum BAUD rate is dependent on the processor internal clock.
 *       (2) Will select highest BAUD rate available that does not exceed.
 *       (3) Transfers > 8 must be word aligned
 *       (4) Select based on chipSelectPolarity  
 *       (5) 0 data captured leading edge of QSPI_CLK, changed following edge.
 *       (6) 1 data changed leading edge of QSPI_CLK, captured following edge.
 *       (7) 0 default is 1/2 QSPI_CLK or see MFCXXXX reference manual
 *       (8) 0 default is 8192/(system clock / 2) see MFCXXXX reference manual
 *
 *****************************************************************************-
 */
 
BYTE QSPIInit( DWORD baudRateInBps = 2000000, BYTE transferSizeInBits = 8, 
      BYTE peripheralChipSelects = 0x0F, BYTE chipSelectPolarity = 1, 
      BYTE clockPolarity = 0, BYTE clockPhase = 1, BOOL doutHiz = TRUE, 
      BYTE csToClockDelay = 0, BYTE delayAfterTransfer = 0 );  

/*
 *****************************************************************************-
 *
 * Start QSPI Data Transfer
 *
 *    Parameters:
 *       transmitBufferPtr       - Buffer with data to send, NULL for receiving
 *       receiveBufferPtr        - Buffer to receive data, NULL for sending
 *       byteCount               - Count of bytes to send or receive
 *       finishedSem             - Optional semaphore to set when completed
 *
 *    Return:
 *       Current QSPI state      - QSPI_OK success or QSPI_BUSY busy
 *
 *    Notes:
 *       None
 *
 *****************************************************************************-
 */
 
BYTE QSPIStart( PBYTE transmitBufferPtr, volatile BYTE* receiveBufferPtr, 
      DWORD byteCount, OS_SEM* finishedSem = NULL );

/*
 *****************************************************************************-
 *
 * Check current QSPI Data Transfer
 *
 *    Parameters:
 *       None
 *
 *    Return:
 *       Progress of transfer    - TRUE is finished, FALSE is active
 *
 *    Notes:
 *       None
 *
 *****************************************************************************-
 */
 
BOOL QSPIdone( void );


/*
 *****************************************************************************-
 *
 *   QSPI_Record 
 *
 *   This struct contains the major variables/configurations used for a QSPI transfer
 *    
 *   volatile BYTE* pQSPIRxbuf/pQSPITxbuf -
 *   These pointers are used to track the locations in memory where data will be 
 *   read or written to the peripheral    
 *    
 *   BYTE BitsPerQueue - This is the number if bits per transfer, (value = 8 - 32) 
 *    
 *   DWORD QSPI_SizeLeft - This is the number if bytes left in the transfer
 *
 *   WORD Command_Mask - This is a partial configuration for the queue's command reg
 *
 *   OS_SEM* QSPI_Sem - This is a pointer to an external semaphore provided by QSPIStart() 
 *         
 *****************************************************************************-
 */
 
typedef struct QSPI_Record
{	  
   volatile BYTE* pQSPIRxbuf;               
   volatile BYTE* pQSPITxbuf;
   BYTE BitsPerQueue;
   DWORD QSPI_SizeLeft;
   WORD Command_Mask;
   OS_SEM* QSPI_Sem;
};

#ifdef __cplusplus
}
#endif

#endif
