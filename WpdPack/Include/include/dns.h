/* Rev:$Revision: 1.8 $ */  

/******************************************************************************
 *
 * Copyright 1998-2002 NetBurner  ALL RIGHTS RESERVED
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
 * San Diego Ca, 92131
 *
 * information available at:  http://www.netburner.com
 * E-Mail info@netburner.com
 *
 * Support is availible: E-Mail support@netburner.com
 *
 *****************************************************************************/

#ifndef _NB_DNS_H
#define _NB_DNS_H

#define DNS_OK (0)
#define DNS_TIMEOUT (1)
#define DNS_NOSUCHNAME (2)
#define DNS_ERR (3)

// DNS record TYPES from RFC1035 page 12
#define DNS_A     1
#define DNS_CNAME 5
#define DNS_MB    7
#define DNS_MG    8
#define DNS_MX    15

#ifdef __cplusplus 
extern "C"
{
#endif



   /*
    GetHostByName  
    Returns:
    #define DNS_OK (0)
    #define DNS_TIMEOUT (1)
    #define NDS_NOSUCH_NAME (2)
   */ 
   /* Pass 0 in for dns_server and it uses the stored value */
   int GetHostByName( const char *name, IPADDR *pIpaddr, IPADDR dns_server, WORD timeout, WORD TYPE = DNS_A );



#ifdef __cplusplus 
}
#endif


#endif

