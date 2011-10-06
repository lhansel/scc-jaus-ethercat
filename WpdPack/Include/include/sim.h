/* $Revision: 1.2 $ */  
/*******************************************************************************
 *
 * Copyright 2009 NetBurner, Inc.  ALL RIGHTS RESERVED
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

#ifndef _SIM_H_
#define _SIM_H_


#ifdef MCF5208
#include "..\MCF5208\system\sim5208.h"
#elif MCF5213
#include "sim5213.h"
#elif MCF5234
#include "sim5234.h"
#elif MCF5270
#include "sim5270.h"
#elif MCF5272
#include "sim5272.h"
#elif MCF5282
#include "sim5282.h"
#else
#error PROCESSOR_NOT_DEFINED
#endif


#endif /* _SIM_H_ */
