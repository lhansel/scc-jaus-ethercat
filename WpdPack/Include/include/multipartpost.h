/* Rev:$Revision: 1.3 $ */  
/******************************************************************************
 *
 * Copyright 2002-2006 NetBurner  ALL RIGHTS RESERVED
 *   Permission is hereby granted to purchasers of NetBurner Hardware
 *   to use or modify this computer program for any use as long as the
 *   resultant program is only executed on NetBurner provided hardware.
 *
 *   No other rights to use this program or it's derivitives in part or
 *   in whole are granted.
 *
 *   It may be possible to license this or other NetBurner software for
 *   use on non NetBurner Hardware. Please contact Licensing@Netburner.com 
 *   for more infomation.
 *
 *   NetBurner makes no representation or warranties
 *   with respect to the performance of this computer program, and
 *   specifically disclaims any responsibility for any damages,
 *   special or consequential, connected with the use of this program.
 *
 *---------------------------------------------------------------------
 * NetBurner
 * 5405 Morehouse Dr
 * San Diego Ca, 92121
 *
 * information available at:  http://www.netburner.com
 * E-Mail info@netburner.com
 *
 * Support is availible: E-Mail support@netburner.com
 *
 *****************************************************************************/
#ifndef _MULTIPART_FILE_H
#define _MULTIPART_FILE_H

/* Give the max file size you will accept */
/*This mallocs the file buffer and returns true if succesful */
BOOL EnableMultiPartForms( DWORD maxfile_size );


/* Frees up the buffer */
void DisableMultiPartForms();


/* Extract a file from the post data stream.
        name = form field name 
       pData = file data left to process
    PostName = the file name entered by the user in the form

   returns > 0 if successful
   The stream must be closed just like any other stream. 
*/
int ExtractPostFile( PCSTR name, PCSTR pData, char *PostName );



#endif
