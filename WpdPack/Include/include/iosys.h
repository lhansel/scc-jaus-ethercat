/* Rev:$Revision: 1.9 $ */  

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

#ifndef _NB_IOSYS_H
#define _NB_IOSYS_H


#ifdef __cplusplus
extern "C"
{
#endif

   /**********************************************************************/
   /*This file defines the operations on the I/O system           */
   /*All serial I/O and TCP socket I/O is done through these IO calls.   */
   /**********************************************************************/


   /**********************************************************************/
   /*   Close open file descriptors.                                     */
   /*    returns 0 on success.                     */
   /**********************************************************************/
   int close( int fd );

   /**********************************************************************/
   /*   read data from a file descriptor                                 */
   /*    returns the number of charactors read.on success.        */
   /*    returns a number <0 on failure.                          */
   /**********************************************************************/
   int read( int fd, char *buf, int nbytes );

   /**********************************************************************/
   /*    write data to a file descriptor                                 */
   /*    returns the number of charactors written on success.        */
   /*    returns a number <0 on failure.                          */
   /*                                                                    */
   /*    Note: It is possible for this call to return a number less      */
   /*    than the requested number of bytes.                */
   /**********************************************************************/
   int write( int fd, const char *buf, int nbytes );

   /*Write a string to the file descriptor*/
   int writestring( int fd, const char *str );

   /* Write to a FD blocking until the write is complete */
   int writeall( int fd, const char *buf, int nbytes );

   /**********************************************************************/
   /*   read data from a file descriptor a timeout limit.                */
   /*    returns the number of charactors read.on success.        */
   /*    returns a number <0 on failure.                 */
   /*    returns 0 on Timeout                         */
   /**********************************************************************/
   int ReadWithTimeout( int fd, char *buf, int nbytes, unsigned long timeout );

   /**********************************************************************
   *    Check to see if data is availible for read                      
   *  returns 1 if data is availible.
   *  returns 0 if no data is availible.
   **********************************************************************/
   int dataavail( int fd );



   /**********************************************************************
   *    Check to see if data is availible for read on stdin                    
   *  returns 1 if data is availible.
   *  returns 0 if no data is availible.
   **********************************************************************/
   int charavail();


#ifdef fd_set 
#undef fd_set
#endif

#ifdef FD_ZERO
#undef FD_ZERO
#endif

#ifdef FD_CLR 
#undef FD_CLR
#endif


#ifdef FD_SET
#undef FD_SET
#endif

#ifdef FD_ISSET
#undef FD_ISSET
#endif


#ifdef FD_SETSIZE
#undef FD_SETSIZE
#endif


   typedef struct
   {
         unsigned long fd_val[2];
   }fd_set ;

   void FD_ZERO( fd_set *pfds );
   void FD_CLR( int fd, fd_set *pfds );
   void FD_SET( int fd, fd_set *pfds );
   int FD_ISSET( int fd, fd_set *pfds );

#define FD_SETSIZE (64)


   int select( int nfds,
               fd_set *readfds,
               fd_set *writefds,
               fd_set *errorfds,
               unsigned long timeout );


   /* Operates identically to select, but does not wait at all */
   int ZeroWaitSelect( int nfds, fd_set *readfds, fd_set *writefds, fd_set *errorfds );  


   /**********************************************************************/
   /*   This defines a set of flags to pass to the ioctl function        */
   /**********************************************************************/

#define IOCTL_TX_CHANGE_CRLF   (1) /*When set transmitted char \n gets converted to \r\n */

#define IOCTL_RX_CHANGE_CRLF   (2) /*When set recievied \r\n get turned into \n */

#define IOCTL_RX_PROCESS_EDITS (4) /*When set Process backspace and do simple line editing */

#define IOCTL_RX_ECHO          (8) /*When set echo chars recievied to tx*/

#define IOCTL_ALL_OPTIONS      (15)

#define IOCTL_SET         (0x4000)
#define IOCTL_CLR         (0x2000)



   int ioctl( int fd, int cmd );

   /*
   Example usage turns on all the options....for stdout,stdin and stderr
    ioctl(0,IOCTL_SET| IOCTL_ALL_OPTIONS);
    ioctl(1,IOCTL_SET| IOCTL_ALL_OPTIONS);
    ioctl(2,IOCTL_SET| IOCTL_ALL_OPTIONS);
   Or just some options
    ioctl(1,IOCTL_SET| IOCTL_RX_CHANGE_CRLF|IOCTL_RX_PROCESS_EDITS);
   */



   /**********************************************************************
   *   This remapps the stdio files to other file descriptors.
   *stdio_fd=0 remaps stdin
   *stdio_fd=1 remaps stdout
   *stdio_fd=2 remaps stderr
   *
   * returns the old map value.
   **********************************************************************/
   int ReplaceStdio( int stdio_fd, int new_fd );

   // Returns current FD mapped to stdio file
   int CurrentStdioFD( int stdio_fd );



#ifdef __cplusplus
}
#endif

#endif



