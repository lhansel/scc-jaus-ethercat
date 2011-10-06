/* Rev:$Revision: 1.3 $ */
/******************************************************************************
 *
 * Copyright 2007 NetBurner  ALL RIGHTS RESERVED
 *   Permission is hereby granted to purchasers of NetBurner Hardware
 *   to use or modify this computer program for any use as long as the
 *   resultant program is only executed on NetBurner provided hardware.
 *
 *   No other rights to use this program or it's derivitives in part or
 *   in whole are granted.
 *
 *   It may be possible to license this or other NetBurner software for
 *        use on non NetBurner Hardware.
 *   Please contact Licensing@Netburner.com for more infomation.
 *
 *   NetBurner makes no representation or warranties
 *   with respect to the performance of this computer program, and
 *   specifically disclaims any responsibility for any damages,
 *   special or consequential, connected with the use of this program.
 *
 *   NetBurner, Inc.
 *   5405 Morehouse Dr
 *   San Diego Ca, 92121
 *   www.netburnre.com
 *****************************************************************************/
/*-------------------------------------------------------------------
 * The Syslog utility enables you to send logging information 
 * to a destination host computer using UDP.
 * -----------------------------------------------------------------*/ 
#ifndef SYSLOG_H
#define SYSLOG_H

#include <nettypes.h>

/* The application assigns this address to the destination host where
 * the syslog information should be sent. If not address is specified,
 * the syslog information is sent to the UDP broadcast address
 * of 255.255.255.255
 */
extern IPADDR SysLogAddress;

/* Call this function when you want to send data to the syslog host.
 * The format is the same as printf(). Note that since it does 
 * floating point, it will increase the application size. 
 */
int SysLog( const char *format, ... );


#endif // SYSLOG_H
