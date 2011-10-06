/* $Revision: 1.13 $ */
/*******************************************************************************
 *
 * Copyright 1999-2009 NetBurner, Inc.  ALL RIGHTS RESERVED
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

#ifndef _NB_BSP_H_
#define _NB_BSP_H_


#ifdef __cplusplus 
extern "C"
{
#endif /* __cplusplus */


/**
 * Initializes the system hardware such as the timer, cache and clock speed.
 *
 * irq_func - Only used for systems utilizing the MCF5272 processor.
 *
 * return   - Nothing to return.
 */
void HardwareSetup( long irq_func );


/**
 * These functions are reserved only for the CFV2-40 and CFV-66 platforms.
 */
void SetEthernetIrq( long isr );
void DisableEthernetIrq();
void EnableEthernetIrq();


/**
 * Forces the system hardware to perform a soft reset.
 *
 * return - Nothing to return.
 */
void ForceReboot();


/**
 * Erases the flash memory.
 *
 * pWhere - The starting location in flash to begin the erasure.
 * len    - Indicates how much in bytes of the flash that will be erased.
 *
 * return - Nothing to return.
 */
void FlashErase( void *pWhere, int len );


/**
 * Programs the flash memory.
 *
 * pWhere - The starting location in flash to begin the programming.
 * pWhat  - The content that will be programmed into flash.
 * len    - Indicates how much in bytes of the flash that will be programmed.
 *
 * return - Nothing to return.
 */
void FlashProgram( void *pWhere, void *pWhat, int len );


/**
 * Disables the MCF52xx cache.
 *
 * return - Nothing to return.
 */
void DisableCache();


/**
 * Enables the MCF52xx cache.
 *
 * return - Nothing to return.
 */
void EnableCache();


/**
 * Determines how much free unallocated space is left in memory.
 *
 * return - The amount of space left in memory.
 */
DWORD spaceleft(); 


/**
 * If the following function pointer is set to point at a function of the form:
 *
 *    void YourFunc( void );
 *
 * Then the system will call this function throughout the AutoUpdate/TCPUpdate
 * process to make sure that the watchdog timer is serviced.
 */
extern void  ( *watchdog_service_function )( void );

/**
 * Fraction of the current tick.
 *
 * return - The current counter value used to generate tick count
 */
extern WORD BspGetTickFraction( void ); 


#ifdef __cplusplus
};
#endif /* __cplusplus */


/**
 * Checks the interrupt sources used in the system along with their associated
 * interrupt level and priority, and also checks for any conflicts in using
 * the same level and priority between different sources.  These results are
 * sent to stdout.
 *
 * return - Nothing to return.
 */
void StdioCheckIntc( void );


/**
 * This is just like the StdioCheckIntc() function, except that the results are
 * displayed via UDP.
 *
 * return - Nothing to return.
 */
void SysLogCheckIntc( void );


#endif /* _NB_BSP_H_ */
