/* $Revision: 1.7 $ */
/* Copyright $Date: 2009/01/19 17:12:20 $ */  

/******************************************************************************
 *
 * Copyright 2001-2008 NetBurner, Inc.  ALL RIGHTS RESERVED
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

#ifndef _NB_SNMP_H_
#define _NB_SNMP_H_

/*
  This file provides null functions for the SNMP counters and functions
  to allow the system to compile without SNMP.
*/

#define SNMPCOUNT(x)    (  (void)0  ) 
#define SNMPDEC(x)      (  (void)0  ) 
#define SNMPADD(x,y)    (  (void)0  )

#endif /* #ifndef _NB_SNMP_H_ */




