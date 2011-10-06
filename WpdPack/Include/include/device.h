/* $Revision: 1.2 $ */
/* Copyright $Date: 2009/08/29 19:17:08 $ */  

/******************************************************************************
 *
 * Copyright 2007-2009 NetBurner  ALL RIGHTS RESERVED
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
#ifndef _DEVICE_H
#define _DEVICE_H

/*
 ******************************************************************************
 *
 * Constants
 *
 ******************************************************************************
 */
/* Fixed interrupt sources */
#define DEVICE_INTERRUPT_MAXIMUM          ( 8 )
 
/*
 ******************************************************************************
 *
 * Enumerations
 *
 ******************************************************************************
 */
/* 
   DeviceSetupIsr interrupt trigger
   
      InterruptTriggerNone               - No interrupt level
      InterruptTriggerSensitive          - Trigger-sensitive interrupt 
      InterruptTriggerRisingEdge         - Rising edge triggered interrupt 
      InterruptTriggerFallingEdge        - Falling edge triggered interrupt 
      InterruptTriggerBothEdges          - Both rising and falling edge triggered 

*/
typedef enum _DeviceInterruptTrigger
{
   InterruptTriggerNone,
   InterruptTriggerSensitive,
   InterruptTriggerRisingEdge,
   InterruptTriggerFallingEdge,
   InterruptTriggerBothEdge
   
} DeviceInterruptTrigger; 

/*
 ******************************************************************************
 *
 * C++ definitions
 *
 ******************************************************************************
 */
 
/*
 ******************************************************************************
 *
 * Routine Prototypes
 *
 ******************************************************************************
 */
/* ISR function */ 
typedef void ( DeviceIsrFn )();
typedef DeviceIsrFn* DeviceIsrFnPtr;

#ifdef __cplusplus
/* 
 ******************************************************************************
 
   Verify availability and support for device.
   
    
      Parameters:
         irq         - Fixed level interrupt source
         
         
      Return:
         TRUE - Support and available on module, FALSE option not supported
         
       Note:
         Only verifies irq is valid
         
 ******************************************************************************
 */
BOOL DeviceIsValid(  int irq );
      
/*
 *****************************************************************************-
  
   Set interrupt controller and attach function to interrupt
  
      Parameters:
         irq               - Fixed level interrupt source
         trigger           - Triggering edge level
         isrPtr            - ISR function
  
      Return:
         TRUE - Set, FALSE - Not valid interrupt source
  
      Notes:
         None
  
 *****************************************************************************-
 */
BOOL DeviceSetupIsr( int irq, DeviceInterruptTrigger trigger, 
      DeviceIsrFnPtr isrPtr );

/*
 *****************************************************************************-
  
   Acknowledge interrupt
  
      Parameters:
         irq               - Fixed level interrupt source
  
      Return:
         None
  
      Notes:
         None
  
 *****************************************************************************-
 */
void DeviceAckInterrupt( int irq );

/*
 *****************************************************************************-
  
   Disable interrupt
  
      Parameters:
         irq               - Fixed level interrupt source
  
      Return:
         None
  
      Notes:
         None
  
 *****************************************************************************-
 */
void DeviceDisableInterrupt( int irq );

/*
 *****************************************************************************-
  
   Enable interrupt
  
      Parameters:
         irq               - Fixed level interrupt source
  
      Return:
         None
  
      Notes:
         None
  
 *****************************************************************************-
 */
void DeviceEnableInterrupt( int irq );

#endif /* #ifdef __cplusplus */

/*
 ******************************************************************************
 *
 * Runtime Libraries Routine Prototypes
 *
 ******************************************************************************
 */
 
/*
 ******************************************************************************
 
   Acquire QSPI semaphore for sharing access to SPI devices.
   
   Parameters:
      None
      
   Return:
      Semaphore, NULL for non-existent device
      
   Notes:
      None
      
 ******************************************************************************
 */
OS_SEM* DeviceGetQspiSem( void );

/*
 ******************************************************************************
 
   Acquire I2C semaphore for sharing access to I2C devices.
   
   Parameters:
      None
      
   Return:
      Semaphore, NULL for non-existent device
      
   Notes:
      None
      
 ******************************************************************************
 */
OS_SEM* DeviceGetI2cSem( void );


#endif   /* _DEVICE_H */


