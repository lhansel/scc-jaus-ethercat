/* Rev:$Revision: 1.11 $ */  

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
 * NetBurner, Inc.
 * 5405 Morehouse Dr #350
 * San Diego Ca, 92121
 *
 * information available at:  http://www.netburner.com
 * E-Mail info@netburner.com
 *
 * Support is availible: E-Mail support@netburner.com
 *
 *****************************************************************************/

#ifndef _NB_HTTP_H
#define _NB_HTTP_H

#include <nettypes.h>

#ifdef __cplusplus

//Internal use only
enum HTTP_RequestTypes { tUnknown, tGet, tPost, tHead };

struct HTTP_Request
	{
	PSTR pURL;
	PSTR pAuthorization;
	PSTR pFirstCookie;
	PSTR pData;
	PSTR pSep;
	PSTR last_datarx;
	WORD sep_len;
	DWORD content_length;
	DWORD rx_length;
	IPADDR client;
	HTTP_RequestTypes req;
	void ProcessLine( PSTR startofline );
	int Respond( int socket );
	};




extern "C"
{
#endif
    
	enum eWEB_ERROR  
    {                                  
        eTCP_CONN_OPEN_NO_DATA, // WEB client open TCP port#80 conn, but no data request was sent 
        eTCP_CONN_OPEN_TO_LONG, // WEB client open TCP connect and send endless data ( for example - never ending POST).                             
    };                                 





   typedef int ( http_posthandler )( int sock, PSTR url, PSTR pData, PSTR rxb ); 
   typedef int ( http_gethandler )( int sock, PSTR url, PSTR rxb );                                                                               
   typedef int ( http_headhandler )( int sock, PSTR url, PSTR rxb );                                                                                
   typedef int ( http_multiparthandler )( int sock,
                                          PSTR url,
                                          PSTR seperator,
                                          PSTR unused_data,
                                          DWORD unused_len );                                                                                
   typedef int ( http_multiextracthandler )( PCSTR name, PCSTR data, PSTR dest, int maxlen );
   typedef int ( http_errorhandler )( IPADDR ip, enum eWEB_ERROR Err, void *prm ); 

   /*Start the HTTP subsystem */
#ifdef __cplusplus
   void StartHTTP( WORD port = 80 );
#else
   void StartHTTP( WORD port );
#endif

   /*Setup a custom Post Handler */
   http_posthandler *SetNewPostHandler( http_posthandler *newhandler );

   /*Setup a custom get Handler */
   http_gethandler *SetNewGetHandler( http_gethandler *newhandler );

   /*Setup a custom Head Handler */
   http_headhandler *SetNewHeadHandler( http_headhandler *newhandler );

   http_multiparthandler *SetNewMultiPartHandler( http_multiparthandler *pNewHandler );
   http_multiextracthandler *SetNewMultiPartExtractHandler( http_multiextracthandler *pNewHandler );
   
   /*Setup a custom WEB Error Report Handler */
   http_errorhandler * SetNewErrorHandler( http_errorhandler *newhandler );


   /*Stop the HTTP subsystem */
   void StopHTTP();

   /* This function takes the HTML post data sent to the DoPost function and */
   /* extracts the data asociated with a specific name and returns it in dest_buffer */
   /*  It returns -1 if no data of that name was found. */
   /*  It returns  0 If the data field was presented, but Empty */
   /*  It returns  the number of chars copied into dest_buffer otherwise. */

   int ExtractPostData( PCSTR name, PCSTR data, PSTR dest_buffer, int maxlen );

   /*Send an html response header */
   void SendHTMLHeader( int sock );

   /*Send a header and include a cookie */
   void SendHTMLHeaderWCookie( int sock, char *cookie );

   /*Send a text header */
   void SendTextHeader( int sock );

   /*Send a Gif header */
   void SendGifHeader( int sock );

   /*Send a response that redirects the request to the new page */
   void RedirectResponse( int sock, PCSTR new_page );

   /*Send a response that indicates the page can't be found. */
   void NotFoundResponse( int sock, PCSTR new_page );

   /*Write out an string while escaping all special charactors.... */
   void writesafestring( int fd, PCSTR str );

   /* write out a string while escaping all special chars and waiting to make sure the writes complete. */
   int writeallsafestring( int fd, PCSTR str );

   /*This is a special compare */
   /*returns 1 if the strings match til one ==0 */
   int httpstricmp( PCSTR s1, PCSTR sisupper2 );

   /*Used internally as a response to Get,Head and Post requests */
   int BaseDoGet( int sock, PSTR url, PSTR rxb );
   int BaseDoHead( int sock, PSTR url, PSTR rxb );
   int BaseDoPost( int sock, PSTR url, PSTR pData, PSTR rxb );


#ifdef __cplusplus
};

void append( char *&cpto, char *cpfrm );
#endif


#endif
