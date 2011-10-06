/* $Revision: 1.1 $ */
/* Copyright $Date: 2008/06/02 20:25:30 $ */  

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

#ifndef _QSPI_BSP_H_
#define _QSPI_BSP_H_

#ifdef __cplusplus 
extern "C"
{
#endif

/*
 *****************************************************************************-
 *
 * Definitions
 *
 *****************************************************************************-
 */
 /*
  * Interrupt controller settings for:
  *      MOD5270
  *      SB70
  *      MOD5213
  *      PK70
  *      MOD5282
  *      MOD5234
  */  
/* Interrupt source (vector) */
#define QSPI_INTERRUPT_SOURCE                   ( 18 )
 
/* Interrupt level */
#define QSPI_INTERRUPT_LEVEL                    ( 2 )
 
/* Interrupt level */
#define QSPI_INTERRUPT_PRIORITY                 ( 7 )

/*
 * RAM addresses
 */
#define QSPI_RAM_ENTRIES                        ( 16 ) 
#define QSPI_RAM_TRANSMIT_START                 ( 0x00 ) 
#define QSPI_RAM_RECEIVE_START                  ( 0x10 ) 
#define QSPI_RAM_COMMAND_START                  ( 0x20 ) 
 
/*
 *****************************************************************************-
 *
 * Structures
 *
 *****************************************************************************-
 */
 /*
   QSPI Mode Register (QMR)
      mstr           - Master mode, must be one
      dohie          - DOUT high impedance or driven when idle?
      bits           - Transfer size 8 through 16 (1000-1111 & 0000 )
      cpol           - Clock polarity (is inactive level)
      cpha           - Clock phase of data capture, 0 leading, 1 falling
      baud           - Baud rate divider 0 disables, 2-255
      
  */
typedef struct _QmrFields
{
   WORD mstr      : 1;
   WORD dohie     : 1;
   WORD bits      : 4;
   WORD cpol      : 1;
   WORD cpha      : 1;
   WORD baud      : 8;

} __attribute__(( packed) ) QmrFields;

typedef union _Qmr
{
   QmrFields field;
   WORD content;
   
} __attribute__(( packed) ) Qmr;
  
 /*
   QSPI Delay Register (QDLYR)
      spe            - Enable
      qcd            - Chip select to valid clock (dsck bit in command RAM)
      dtl            - Delay after transfer (dt bit in command RAM)
      
  */
typedef struct _QdlyrFields
{
   WORD spe       : 1;
   WORD qcd       : 7;
   WORD dtl       : 8;

} __attribute__(( packed) ) QdlyrFields;

typedef union _Qdlyr
{
   QdlyrFields field;
   WORD content;
   
} __attribute__(( packed) ) Qdlyr;
  
 /*
   QSPI Wrap Register (QWR)
      halt           - Halts transfer
      wren           - Wrap around enabled
      wrto           - Wrap around location
      csiv           - Chip select inactive level
      endqp          - End of queue pointer
      cptqp          - Completed queue entry pointer (R)
      newqp          - Start of queue pointer
      
  */
typedef struct _QwrFields
{
   WORD halt      : 1;
   WORD wren      : 1;
   WORD wrto      : 1;
   WORD csiv      : 1;
   WORD endqp     : 4;
   WORD cptqp     : 4;
   WORD newqp     : 4;

} __attribute__(( packed) ) QwrFields;

typedef union _Qwr
{
   QwrFields field;
   WORD content;
   
} __attribute__(( packed) ) Qwr;
  
 /*
   QSPI Interrupt Register (QIR)
      wcefb          - Write collision access error enable
      abrtb          - Abort access error enable
      abrtl          - Abort lockout
      wcefe          - Write collision interrupt enable
      abrte          - Abort interrupt enable
      spife          - Finished interrupt enable
      wcef           - Write collision error flag
      abrt           - Abort flag
      spif           - Finished flag
      
  */
typedef struct _QirFields
{
   WORD wcefb     : 1;
   WORD abrtb     : 1;
   WORD mbz_13    : 1;
   WORD abrtl     : 1;
   WORD wcefe     : 1;
   WORD abrte     : 1;
   WORD mbz_09    : 1;
   WORD spife     : 1;
   WORD mbz_04_07 : 4;
   WORD wcef      : 1;
   WORD abrt      : 1;
   WORD mbz_01    : 1;
   WORD spif      : 1;

} __attribute__(( packed) ) QirFields;

typedef union _Qir
{
   QirFields field;
   WORD content;
   
} __attribute__(( packed) ) Qir;
  
 /*
   QSPI Command Register(s) (QCR)
      cont           - Continuous (0-stop, 1-go)
      bitse          - Eight bits or qmr.field.bits
      dt             - Delay after transfer (0-default, 1-qdlyr.dtl)
      dsck           - Chip select to valid clock (0-1/2 clock, 1-qdlyr.qcd)
      qspi_cs        - Chip select mask [3:0]
      
  */
typedef struct _QcrFields
{
   WORD cont      : 1;
   WORD bitse     : 1;
   WORD dt        : 1;
   WORD dsck      : 1;
   WORD qspi_cs   : 4;
   WORD mbz_00_07 : 8;

} __attribute__(( packed) ) QcrFields;

typedef union _Qcr
{
   QcrFields field;
   WORD content;
   
} __attribute__(( packed) ) Qcr;
  
/*
 ******************************************************************************
 *
 * Routines 
 *
 ******************************************************************************
 */
 
/*
 ******************************************************************************
 
   Interrupt service routine (ISR)
   
   Parameters:
      None
      
   Return:
      None
      
   Notes:
      None
      
 ******************************************************************************
 */
typedef void ( QspiIsr )( void );

/*
 ******************************************************************************
 
   Setup QSPI module 
   
   Parameters:
      setHighDrive               - Drive strength TRUE high, FALSE low
      
   Return:
      0 - OK, all else problems
      
   Notes:
      Set assigned pins QSPI_DOUT, QSPI_DIN, QSPI_CLK and drive strength install
      BSP Isr.
      
 ******************************************************************************
 */
int QspiSetupHardware( BOOL setHighDrive );
 
/*
 ******************************************************************************
 
   Attach chip select to QSPI module 
   
   Parameters:
      controlledChipSelects      - Chip selects [3:0] respectively
      
   Return:
      0 - OK, all else problems
      
   Notes:
      Driver user can let the module assert/de-assert chip select by attaching 
      or use QspiSelectChip and QspiDeselectChip based on device requirements.
      The last call to QspiAttachChipSelects/QspiDetachChipSelects is the one
      controlling.
      
 ******************************************************************************
 */
int QspiAttachChipSelects( BYTE controlledChipSelects );
 
/*
 ******************************************************************************
 
   Detach chip selects from QSPI module set as GPIO pins
   
   Parameters:
      controlledChipSelects      - Chip selects [3:0] respectively
      
   Return:
      0 - OK, all else problems
      
   Notes:
      User can assert/de-assert chip select by detaching and calling 
      QspiAssertChipSelects and QspiDeassertChipSelects.
      The last call to QspiAttachChipSelects/QspiDetachChipSelects is the one
      controlling.
      
 ******************************************************************************
 */
int QspiDetachChipSelects( BYTE controlledChipSelects );
 
/*
 ******************************************************************************
 
   Asserts chip selects
   
   Parameters:
      controlledChipSelects   - Chip selects [3:0] respectively
      isChipSelectActiveLow   - Chips select phase
                                    TRUE Active low, inactive high
                                    TRUE Active high, inactive low
      
      
   Return:
      Notes
      
   Notes:
      Driver must call QspiAttachChipSelects/QspiDetachChipSelects.
      
 ******************************************************************************
 */
void QspiAssertChipSelects( BYTE controlledChipSelects, 
      BOOL isChipSelectActiveLow );
 
/*
 ******************************************************************************
 
   Deasserts chip selects
   
   Parameters:
      controlledChipSelects   - Chip selects [3:0] respectively
      isChipSelectActiveLow   - Chips select phase
                                    TRUE Active low, inactive high
                                    TRUE Active high, inactive low
      
      
   Return:
      Notes
      
   Notes:
      Driver must call QspiAttachChipSelects/QspiDetachChipSelects.
      
 ******************************************************************************
 */
void QspiDeassertChipSelects( BYTE controlledChipSelects, 
      BOOL isChipSelectActiveLow );
 
/*
 ******************************************************************************
 
   Installs interrupt service routine
   
   Parameters:
      isr                        - "C" interrupt service routine
      
   Return:
      None
      
   Notes:
      None
      
 ******************************************************************************
 */
void QspiSetupIsr( QspiIsr isr );

/*
 ******************************************************************************
 
   Get baud rate setting
   
   Parameters:
      baudRateInMhz              - Baud rate requested in Mhz
      
   Return:
      Lowest near integral setting within processor/module limits.
      
   Notes:
      Base on processor and clock speed.
      
 ******************************************************************************
 */
BYTE QspiGetBaudSetting( unsigned long baudRateInMhz );

/*
 ******************************************************************************
 
   Get current baud rate setting
   
   Parameters:
      None
      
   Return:
      Baud rate setting in Mhz
      
   Notes:
      Base on processor and clock speed.
      
 ******************************************************************************
 */
unsigned long QspiGetCurrentBaudSetting( void );

/*
 ******************************************************************************
 
   Enable module interrupt
   
   Parameters:
      None
      
   Return:
      None
      
   Notes:
      None
      
 ******************************************************************************
 */
void QspiEnableIsr( void );

/*
 ******************************************************************************
 
   Disable module interrupt
   
   Parameters:
      None
      
   Return:
      None
      
   Notes:
      None
      
 ******************************************************************************
 */
void QspiDisableIsr( void );

/*
 ******************************************************************************
 
   Get module registers
   
   Parameters:
      None
      
   Return:
      None
      
   Notes:
      None
      
 ******************************************************************************
 */
void QspiGetRegisters( volatile WORD** qmrPtr, volatile WORD** qdlyrPtr, 
      volatile WORD** qwrPtr, volatile WORD** qirPtr, volatile WORD** qarPtr, 
      volatile WORD** qdrPtr );
      

#ifdef __cplusplus
};
#endif

#endif   /* _QSPI_BSP_H_ */
