/* $Revision: 1.5 $ */
/* Copyright $Date: 2009/08/29 19:34:42 $ */  

/******************************************************************************
 *
 * Copyright 1998-2008 NetBurner, Inc.  ALL RIGHTS RESERVED
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

#ifndef _SDIOBSP_H
#define _SDIOBSP_H

/*
 ******************************************************************************
 *
 * Debugging
 *
 ******************************************************************************
 */
#define SDIO_DEBUG_INT  (1)

/*
 ******************************************************************************
 *
 * C Platform Functions
 *
 ******************************************************************************
 */

#ifdef __cplusplus 
extern "C"
{
#endif

/*
 *****************************************************************************-
 *
 * Set up access
 *
 *    Parameters:
 *       None
 *
 *    Return:
 *       TRUE if OK, FALSE otherwise
 *
 *    Notes:
 *       None
 *
 *****************************************************************************-
 */
BOOL SdioBspSetupHardware( void );
 
/*
 *****************************************************************************-
 *
 * Assert SDIO chip select/deselect
 *
 *    Parameters:
 *       pin               - Pin number, 0 none
 *
 *    Return:
 *       None
 *
 *    Notes:
 *       Implemented for MOD-DEV-70 and MOD-DEV-100
 *
 *****************************************************************************-
 */
void SdioAssertChipSelect( int pin ); 
void SdioDeassertChipSelect( int pin ); 
 
#ifdef __cplusplus 
}
#endif

#endif /* _SDIOBSP_H */
