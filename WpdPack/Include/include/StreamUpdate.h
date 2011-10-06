/* Rev:$Revision: 1.7 $ */ 

/******************************************************************************
 * Copyright 2001-2004 NetBurner Inc., All Rights Reserved
 *   Permission is hereby granted to purchasers of NetBurner Hardware
 *   to use or modify this computer program for any use as long as the
 *   resultant program is only executed on NetBurner provided hardware.
 *
 *   No other rights to use this program or it's derivatives in part or
 *   in whole are granted.
 *
 *   It may be possible to license this or other NetBurner software for
 *   use on non NetBurner Hardware. Please contact sales@netburner.com 
 *   for more information.
 *
 *   NetBurner makes no representation or warranties
 *   with respect to the performance of this computer program, and
 *   specifically disclaims any responsibility for any damages,
 *   special or consequential, connected with the use of this program.
 *
 *---------------------------------------------------------------------
 *
 * NetBurner, Inc.
 * 5404 Morehouse #350
 * San Diego CA, 92121
 *
 * Additional information is available at: http://www.netburner.com,
 * or E-Mail sales@netburner.com
 *
 * Support is available at support@netburner.com
 *
 *****************************************************************************/

#ifndef _NB_STREAM_UP_H                      
#define _NB_STREAM_UP_H                      

#ifdef __cplusplus
extern "C"
{
#endif

#define STREAM_UP_OK   (1)
#define STREAM_UP_FAIL (0)



   /*Stream Update code */
   /*Module: Stream Update
   The functions supplied in this module are intended to be used in conjunction 
   with FTP server and client implementations. Functions are provided to access
   the user parameter storage area of the flash memory, and to update the 
   application code in flash memory.


   See the example application at 
      nburn\examples\ftpd_code_update
   */


   /*Functions:*/
   /*Group:Stream Update of User Parameter Flash Data.*/
   /*Send User Parameter Flash data as a binary output stream.*/
   /*
   This function sends the User Parameter Flash data to the specified fd 
   output stream as a binary record.

   Parameters:
      int fd The socket file descriptor to send the data to

   Returns:
      STREAM_UP_OK The system was able to send the data
      STREAM_UP_FAIL The system failed to send the data


   See Also:
      int SendUserFlashToStreamAsS19(int fd);
      int ReadBinaryUserFlashFromStream(int fd);
      int ReadS19UserFlashFromStream(int fd);


   */ 
   int SendUserFlashToStreamAsBinary( int fd );



   /*Send User Parameter Flash data as a S19 ASCII record to an output stream.*/
   /*
   This function sends the User Parameter Flash data to the specified fd 
   output stream as a S19 text record.

   Parameters:
      int fd The socket file descriptor to send the data to.

   Returns:
      STREAM_UP_OK The system was able to send the data
      STREAM_UP_FAIL The system failed to send the data


   See Also:
      int SendUserFlashToStreamAsBinary(int fd);
      int ReadBinaryUserFlashFromStream(int fd);
      int ReadS19UserFlashFromStream(int fd);

   */ 
   int SendUserFlashToStreamAsS19( int fd );


   /*Read User Parameter Flash data from a S19 ASCII input stream.*/
   /*
   This function reads ASCII S19 records from the specified fd input stream 
   and programs the data in the User Parameter Flash area.

   Parameters:
      int fd The socket file descriptor to read data from

   Returns:
      STREAM_UP_OK The system was able to read the data and update flash
      STREAM_UP_FAIL The system failed to read or update


   See Also:
      int SendUserFlashToStreamAsS19(int fd);
      int SendUserFlashToStreamAsBinary(int fd);
      int ReadBinaryUserFlashFromStream(int fd);

   */
   int ReadS19UserFlashFromStream( int fd );


   /*Read User Parameter Flash data from a binary input stream.*/
   /*
   This function reads binary data from the specified input stream and 
   programs the data into the User Parameter Flash area.

   Parameters:
      int fd The socket file descriptor to read data from

   Returns:
      STREAM_UP_OK The system was able to read the data and update flash
      STREAM_UP_FAIL The system failed to read or update

   See Also:
      int SendUserFlashToStreamAsS19(int fd);
      int SendUserFlashToStreamAsBinary(int fd);
      int ReadS19UserFlashFromStream(int fd);

   */
   int ReadBinaryUserFlashFromStream( int fd );


   /*Functions:*/
   /*Group:Stream Update of Application Code.*/
   /*Read a new application in _APP.S19 format from an ASCII input stream.*/
   /*
   This function reads ASCII S19 records from a _APP.s19 format application file
   and reprograms the Flash memory with the new application. The Flash memory will
   not be modified unless the entire application is received without error. 

   Since applications are run from RAM, the board must be rebooted before the new
   application code becomes active. One way to accomplish a reboot is to use
   the function: void ForceReboot(). Items you need to clean up or close before
   causing a reboot is dependant on your particular application, but at a minimum
   you should clean up and close any FTP client or server sessions before calling 
   ForceReboot(). An example using this function is provided in the ftpd_code_update 
   example.


   Parameters:
      int fd The socket file descriptor to read data from

   Returns:
      STREAM_UP_OK The system was able to read the data and update the Flash
      STREAM_UP_FAIL The system failed to read or update Flash
   */
   int ReadS19ApplicationCodeFromStream( int fd );

   int SendApplicationCodeAsS19( int fd );

   int ReadBinaryApplicationCodeFromStream(int fd );

   //Exposed to allow custom updaters to be used 
   int ProcessS3( const char *cp, DWORD base_Addr, PBYTE CopyTo, DWORD &cur_pos, DWORD maxlen );


#ifdef __cplusplus
}
#endif

#endif


