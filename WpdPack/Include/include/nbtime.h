
/* Rev:$Revision: 1.4 $ */  

/******************************************************************************
 *
 * Copyright 1998-2004 NetBurner  ALL RIGHTS RESERVED
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
 *---------------------------------------------------------------------
 * NetBurner
 * 5405 Morehouse Dr #350
 * San Diego Ca, 92121
 *
 * information available at:  http://www.netburner.com
 * E-Mail info@netburner.com
 *
 * Support is availible: E-Mail support@netburner.com
 *
 *****************************************************************************/

#ifndef _NB_TIME_H
#define _NB_TIME_H

#ifdef __cplusplus 
extern "C"
{
#endif


time_t time( time_t *pt );

time_t set_time( time_t time_to_set );

#ifdef NB_NET_TYPES_H
BOOL SetNTPTime( IPADDR ntpserver);
BOOL SetTimeNTPFromPool();
DWORD GetNTPTime( IPADDR NTP_server_ip );
#endif

int IOBoardRTCSetSystemFromRTCTime();

int IOBoardRTCSetRTCfromSystemTime();


/* Set the local TZ time zone variable */
/* For the US use one of:

     tzsetchar("EST5EDT4,M3.2.0/01:00:00,M11.1.0/02:00:00");
     tzsetchar("CST6CDT5,M3.2.0/01:00:00,M11.1.0/02:00:00");
     tzsetchar("MST7MDT6,M3.2.0/01:00:00,M11.1.0/02:00:00"); 
     tzsetchar("PST8PDT7,M3.2.0/01:00:00,M11.1.0/02:00:00");
 
*/
void  tzsetchar(char * tzenv);



#ifdef __cplusplus
};
#endif

#endif
