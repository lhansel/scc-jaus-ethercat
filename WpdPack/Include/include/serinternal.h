/* $Revision: 1.15 $ */  
/*******************************************************************************
 *
 * Copyright 1998-2009 NetBurner, Inc.  ALL RIGHTS RESERVED
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

#ifndef _NB_SER_INTERNAL
#define _NB_SER_INTERNAL


/**
 * UART state condition flags.
 */
#define UART_INIT                ( 0x0001 )   /* UART is initialized */


#define UART_TX_EMPTY            ( 0x0002 )   /* UART Tx buffer is empty */


#define UART_SENT_STOP           ( 0x0004 )   /* UART has sent XOFF */


#define UART_RX_STOP             ( 0x0008 )   /* UART has received XOFF */


#define UART_FLOW_TX             ( 0x0010 )   /* UART must respond to received
                                                 flow control */

#define UART_FLOW_RX             ( 0x0020 )   /* UART is allowed to send flow
                                                 control */

#define UART_FLOW_NEED_TOSTOP    ( 0x0040 )   /* UART needs to send XOFF */


#define UART_FLOW_NEED_TOSTART   ( 0x0080 )   /* UART needs to send XON */


#define UART_RS485_TX_MODE       ( 0x0100 )   /* UART is in RS-485 HD/FD mode
                                                 (not used) */

#define UART_MULTI_MODE          ( 0x0200 )   /* UART is in multi-drop mode */


#define UART_FLOW_TXRTSCTS       ( 0x0400 )   /* UART has TxCTS hardware flow
                                                 control enabled */

#define UART_FLOW_TX485FD        ( 0x0800 )   /* UART is in RS-485 full-duplex
                                                 mode */

#define UART_FLOW_TX485HD        ( 0x1000 )   /* UART is in RS-485 half-duplex
                                                 mode */

#define UART_FLOW_RXRTSCTS       ( 0x2000 )   /* UART has RxRTS hardware flow
                                                 control enabled */


/**
 * Software flow control characters.
 */
#define XON    ( 0x11 )
#define XOFF   ( 0x13 )


/**
 * Designates a threshold limit on the amount of space available (in bytes) in
 * the FIFO buffer depending on the type of software flow control character
 * sent.
 */
#define UART_XOFF_LIMIT   ( 100 )
#define UART_XON_LIMIT    ( 200 )


typedef int ( GetNextCharFunc )( int uartnum );
typedef void ( PutNextCharFunc )( int uartnum, BYTE c );


int BaseGetChar( int num );
void BasePutChar( int num, BYTE c );


struct UartDataRec
{
   fifo_buffer_storage m_FifoRead;
   fifo_buffer_storage m_FifoWrite;
   GetNextCharFunc *m_pGetCharFunc;
   PutNextCharFunc *m_pPutCharFunc;
   int m_UartState;
   BYTE m_Errors;
};


extern UartDataRec UartData[];


void WakeTx( int x );


#endif /* _NB_SER_INTERNAL */
