/* $Revision: 1.22 $ */  
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

#ifndef _NB_SERIAL_H
#define _NB_SERIAL_H

#include "basictypes.h"

/**
 * UART error return codes.
 */
#define SERIAL_ERR_NOSUCH_PORT        (   -1 )
#define SERIAL_ERR_PORT_NOTOPEN       (   -2 )
#define SERIAL_ERR_PORT_ALREADYOPEN   (   -3 )
#define SERIAL_ERR_PARAM_ERROR        (   -4 )


/**
 * Special UART characters.
 */
#define ADDR_ESCAPE_CHAR              ( 0xFF )


/**
 * Definitions used to represent bits of the UART error register.  These are
 * associated with the GetUartErrorReg() function, which is only applicable to
 * the MOD5270, SB70 and SB72.
 */
#define UART_ERR_BREAK                ( 0x08 )
#define UART_ERR_FRAME                ( 0x04 )
#define UART_ERR_PARITY               ( 0x02 )
#define UART_ERR_OVERRUN              ( 0x01 )


#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */


/**
 * User-defined data types.
 */
typedef enum { eParityNone, eParityOdd, eParityEven, eParityMulti } parity_mode;


/**
 * Opens a serial port.
 *
 * portnum   - The UART to open, usually 0 and higher; what and how many UARTs
 *             depends on the platform.
 * baudrate  - The speed of the serial port in bits per second.
 * stop_bits - The number of stop bits to append to character data; valid values
 *             are 1 and 2.
 * data_bits - The number of data bits sent per character or frame; valid values
 *             are 5, 6, 7 and 8.
 * parity    - The type of parity checking to use; valid values are eParityNone,
 *             eParityEven, eParityOdd and eParityMulti.
 *
 * return    - The file descriptor of the initialized port if successful;
 *             otherwise, one of the error codes is returned:
 *             SERIAL_ERR_NOSUCH_PORT (-1)
 *             SERIAL_ERR_PORT_ALREADYOPEN (-3)
 *             SERIAL_ERR_PARAM_ERROR (-4)
 */
int OpenSerial( int portnum, unsigned int baudrate, int stop_bits,
                int data_bits, parity_mode parity );


/**
 * Special function call of OpenSerial() which requires the user to provide the
 * serial port to initialize and the desired baud rate.  The common 1 stop bit,
 * 8 data bits and no parity parameter configurations are used by default.
 */
#define SimpleOpenSerial( p, b )      OpenSerial( p, b, 1, 8, eParityNone )


/**
 * Closes a serial port.
 *
 * portnum - The UART port to close.
 *
 * return  - '0' if successful; otherwise, one of the error codes is returned:
 *           SERIAL_ERR_NOSUCH_PORT (-1)
 *           SERIAL_ERR_PORT_NOTOPEN (-2)
 */
int SerialClose( int portnum );


/**
 * Enables or disables software flow control (XON/XOFF) on transmit.  When
 * enabled, the NetBurner device will recognize the special XON and XOFF
 * characters being sent from another device in order to throttle the output.
 *
 * port   - The UART whose flow control will be toggled.
 * enab   - '0' disables flow control; '1' (or any non-zero number) will enable
 *          it.
 *
 * return - Nothing to return.
 */
void SerialEnableTxFlow( int port, int enab );


/**
 * Enables or disables software flow control (XON/XOFF) on receive.  When
 * enabled, the NetBurner device will send special XON and XOFF characters to
 * another device in order to control the flow of incoming data.
 *
 * port   - The UART whose flow control will be toggled.
 * enab   - '0' disables flow control; '1' (or any non-zero number) will enable
 *          it.
 *
 * return - Nothing to return.
 */
void SerialEnableRxFlow( int port, int enab );


/**
 * Enables or disables clear-to-send hardware flow control on transmit (TxCTS).
 * When enabled, transmit is throttled by the receiver on the other end.
 * Jumpers may also be needed to enable the TxCTS line depending on the device
 * and/or development board used.
 *
 *    (NB Device)    Tx >-->--> Rx    (Other Device)
 *    (NB Device) TxCTS <--<--< RxRTS (Other Device)
 *
 * Note:  Calling this function to disable Tx hardware flow control after
 * enabling RS-485 full-duplex mode configures for RS-422 mode (Tx stays
 * actively driven).
 *
 * port   - The UART whose flow control will be toggled.
 * enab   - '0' disables flow control; '1' (or any non-zero number) will enable
 *          it.
 *
 * return - Nothing to return.
 */
void SerialEnableHwTxFlow( int port, int enab );


/**
 * Enables or disables request-to-send hardware flow control on receive (RxRTS).
 * When enabled, receive throttles the transmitter on the other end.  Jumpers
 * may also be needed to enable the RxRTS line depending on the device and/or
 * development board used.
 *
 *    (NB Device)    Rx <--<--< Tx    (Other Device)
 *    (NB Device) RxRTS >-->--> TxCTS (Other Device)
 *
 * port   - The UART whose flow control will be toggled.
 * enab   - '0' disables flow control; '1' (or any non-zero number) will enable
 *          it.
 *
 * return - Nothing to return.
 */
void SerialEnableHwRxFlow( int port, int enab );


/**
 * Enables or disables RS-485 half-duplex mode.  Full-duplex mode is
 * automatically enabled when half-duplex mode is disabled.  This must be
 * explicitly called before RS-485 functionality can be used.  Jumpers may also
 * be needed depending on the hardware device and/or development board used.      
 *
 * port   - The UART port to use; the UART that can only be used for RS-485
 *          depends on the platform (e.g., MOD52xx mounted on the MOD-DEV-100
 *          develoment board use only UART 0 for RS-485, CB34-EX use only UART 1
 *          for RS-485).
 * enab   - '0' disables half-duplex (enables full-duplex); '1' enables half-
 *          duplex (disables full-duplex)
 *
 * return - Nothing to return.
 */
void Serial485HalfDupMode( int port, int enab );


/**
 * Sets a break in the UART transmission for a given period of time.  The break
 * starts when character transmission completes.  The break is delayed until any
 * character in the transmitter shift register is sent.  Any character in the
 * transmitter holding register is sent after the break.
 *
 * port   - The UART whose transmitter will be forced low (start break).
 * time   - Specifies the amount of time in ticks that the break will hold; when
 *          time expires, the break will be stopped; 20 ticks equal 1 second by
 *          default.
 *
 * return - Nothing to return.
 */
void SendBreak( int port, DWORD time );


/**
 * Sends an address character via the UART port number associated with the given
 * file descriptor.  This function can only be utilized if the UART is
 * initialized in multidrop mode.
 *
 * fd     - The file descriptor associated with the UART serial port that will
 *          be used.
 * c      - The address character to be sent.
 *
 * return - '1' if successful; otherwise, one of the error codes is returned
 *          (note that SERIAL_ERR_PORT_NOTOPEN is also returned if UART is not
 *          initialized to be in multidrop mode):
 *          SERIAL_ERR_NOSUCH_PORT (-1)
 *          SERIAL_ERR_PORT_NOTOPEN (-2)
 */
int serwriteaddress( int fd, const char c );


/**
 * Gets the UART error register.  This is only applicable on select platforms.
 * Any errors are added to this register in a logical OR operation.  Calling
 * this function to read the error status will clear the register.
 *
 *    Bit   Description
 *    ---   --------------
 *     3    Received break
 *     2    Framing error
 *     1    Parity error
 *     0    Overrun error
 *
 * fd     - The file descriptor associated with the UART serial port whose error
 *          register is to be retreived.
 *
 * return - The value of the error register if successful (positive int - the
 *          bitwise values are represented by the UART_ERR_* definitions found
 *          near the top of this file); otherwise, one of the error codes is
 *          returned:
 *          SERIAL_ERR_NOSUCH_PORT (-1)
 *          SERIAL_ERR_PORT_NOTOPEN (-2)
 */
int GetUartErrorReg( int fd );


#if ( defined CB34EX || defined SB72EX )
/**
 * Gets the current state of the Carrier Detect signal from the specified serial
 * port.
 *
 * port   - The UART port whose CD signal will be read.
 *
 * return - TRUE if high, FALSE if low; '0' is returned if port number is
 *          invalid.
 */
BOOL GetCD( int port );


/**
 * Gets the current state of the Ring Indicator signal from the specified serial
 * port.
 *
 * port   - The UART port whose RI signal will be read.
 *
 * return - TRUE if high, FALSE if low; '0' is returned if port number is
 *          invalid.
 */
BOOL GetRI( int port );


/**
 * Gets the current state of the Data Set Ready signal from the specified serial
 * port.
 *
 * port   - The UART port whose DSR signal will be read.
 *
 * return - TRUE if high, FALSE if low; '0' is returned if port number is
 *          invalid.
 */
BOOL GetDSR( int port );


/**
 * Sets or clears the Data Terminal Ready signal for the specified serial port.
 *
 * port   - The UART port whose DTR signal will be set or cleared.
 * val    - The Boolean value to configure the signal; TRUE sets it, while FALSE
 *          clears it.
 *
 * return - Nothing to return.
 */
void SetDTR( int port, BOOL val );
#endif /* CB34EX/SB72EX */


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* _NB_SERIAL_H */
