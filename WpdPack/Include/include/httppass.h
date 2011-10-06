/* Rev:$Revision: 1.5 $ */  
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
 * NetBurner, Inc. 
 * 5405 Morehouse Dr
 * San Diego Ca, 92121
 *
 *****************************************************************************/

#ifndef _NB_HTTPPASS_H
#define _NB_HTTPPASS_H

#ifdef __cplusplus
extern "C"
{
#endif

   /* Module: HTTP Password support
    * This Module provides basic HTML plain text password support.
    *
    * Check the HTTP request for password information
    * This function examines the PASSWORD field stored in the HTTP request.
    * 
    * Parameters:
    *  PSTR url   A pointer to the url as passed to the user provided get function.
    *  char ** pPassword   A char pointer that will be set to point to the password 
    *                      in the request.
    *  char ** pUser       A char pointer that will be set to point to the user 
    *                      name in the request.
    */
     
   int CheckAuthentication( PSTR url, char **pPassword, char **pUser );


   /* Reject the current HTTP request, and request password.
    * This function will send a 401 authentication requested 
    * message to the socket.
    * 
    * Parameters:
    * 
    *   int sock     The socket file descriptor to get the request.
    *   PCSTR name   The Name that should appear in the password request.
    */    
   void RequestAuthentication( int sock, PCSTR name );


#ifdef __cplusplus
}
#endif


#endif


