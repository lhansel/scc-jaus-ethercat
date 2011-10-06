/* $Revision: 1.7 $ */
/* Copyright $Date: 2008/01/07 21:03:31 $ */  

/******************************************************************************
 *
 * Copyright 1998-2008 NetBurner, Inc.  ALL RIGHTS RESERVED
 *   Permission is hereby granted to purchasers of NetBurner Hardware
 *   to use or modify this computer program for any use as long as the
 *   resultant program is only executed on NetBurner provided hardware.
 *
 *   No other rights to use this program or it's derivatives in part or
 *   in whole are granted.
 *
 *   It may be possible to license this or other NetBurner software for
 *        use on non NetBurner Hardware.
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

#ifndef _NB_IOINTERNALS_H
#define _NB_IOINTERNALS_H

/*
 ******************************************************************************
 *
 * Definitions
 *
 ******************************************************************************
 */
#define IOINTERNALS_FRAMEWORK_TAG      ( (unsigned int)0x10127EB6 )
 
#ifdef __cplusplus
extern "C"
{
#endif
   /*
    ******************************************************************************
    *
    * Structures
    *
    ******************************************************************************
    */
   /*
    * Extra FD Framework
    *    tag                     - Unique tag (Must be IOINTERNALS_FRAMEWORK_TAG)
    *    ioSocketNumber          - I/O socket number
    *    extraSocketNumber       - Extra socket number
    *
    *    Notes:
    *       Must be at the very beginning of any extra data passed to GetExtraFD
    */ 
   typedef struct _IoFrameworkStruct
   {
      unsigned int tag;
      int ioSocketNumber;
      int extraSocketNumber;
   
   } __attribute__(( packed ) ) IoFrameworkStruct;

   /*
    * I/O Expansion Structure
    *    read                    - read function
    *    write                   - write function
    *    close                   - close function
    *    extra                   - Control struct starts with IoFrameworkStruct
    *
    *    Notes:
    *       Expanded routines for library read, write and close
    */ 
   struct IoExpandStruct
   {
      int ( * read )  ( int fd, char *buf, int nbytes ); 
      int ( * write ) ( int fd, const char *buf, int nbytes ); 
      int ( * close ) ( int fd );            
      void *extra;
   };

   /*
    ***************************************************************************
    *
    * Library Routines
    *
    ***************************************************************************
    */
 
   /* 
    ***************************************************************************
    
      Acquire/Release/Access expansion file descriptor

         Parameters:
            extra_data        - Control data structure beginning with 
                                 IoFrameworkStruct
            pFuncs            - Expanded I/O routines
                                             
            fd                - Expanded file descriptor

         Return:
            Acquired fd > EXTRA_IO_OFFSET OK, else -1 for none
         
    ***************************************************************************
    */
   int GetExtraFD( void *extra_data, struct IoExpandStruct *pFuncs );
   void FreeExtraFd( int fd );
   void *GetExtraData( int fd );

   /* 
    ***************************************************************************
    
      Expanded file descriptor callback

         Parameters:
            tcpFd             - Actual connection file descriptor
            notifyHandler     - Notification callback

         Return:
            None
            
         Notes:
            Data arrival or an connection error state calls this routine.            
         
    ***************************************************************************
    */
   typedef void ( tcp_read_notify_handler )( int tcpFd );  
   void RegisterTCPReadNotify( int tcpFd, tcp_read_notify_handler *notifyHandler );

   /* 
    ***************************************************************************
    
      I/O subsystem notification support for use by expanded I/O routines

         Parameters:
            fd                - Expanded file descriptor

         Return:
            None
         
    ***************************************************************************
    */
   void SetDataAvail( int fd );
   void ClrDataAvail( int fd );

   void SetWriteAvail( int fd );
   void ClrWriteAvail( int fd );

   void SetHaveError( int fd );
   void ClrHaveError( int fd );

#ifdef __cplusplus
}
#endif

#endif
