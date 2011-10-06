/* $Revision: 1.6 $ */
/* Copyright $Date: 2008/07/22 20:08:42 $ */  

/******************************************************************************
 *
 * Copyright 1998 - 2008 NetBurner  ALL RIGHTS RESERVED
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

#ifndef _NB_TFTP_H
#define _NB_TFTP_H

#define TFTP_OK (0)
#define TFTP_TIMEOUT (1)
#define TFTP_ERROR (2)

/******************************************************************************
The following function gets a file from a TFTP server.
it returns the following values:
TFTP_OK
TFTP_ERROR
TFTP_TIMEOUT
*****************************************************************************/
int GetTFTP( PCSTR filename, //The Ascii file name
        PCSTR mode, //The mode, 'b' or 't'
        PBYTE buffer, //The destination buffer
        int &len, //The length passed in and passed back
        DWORD total_timeout, //The total timeout in ticks
        IPADDR server, //The address of the server
        WORD opening_port = IANA_TFTP_PORT //The port to use
);

/******************************************************************************
The following function sends a file to a TFTP server.
It returns the following values:
TFTP_OK
TFTP_ERROR
TFTP_TIMEOUT
*****************************************************************************/
int SendTFTP( PCSTR filename, //The Ascii file name
        PCSTR mode, //The mode, 'b' or 't'
        PBYTE buffer, //The destination buffer
        int  len, //The length passed in.
        DWORD total_timeout, //The total timeout in ticks
        DWORD packet_timeout, //The packet timeout in ticks
        IPADDR server, //The address of the server
        WORD opening_port = IANA_TFTP_PORT //The port to use
);



#endif


