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
*
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
#ifndef _AUTOUPDATE_H_
#define _AUTOUPDATE_H_
#ifdef __cplusplus
extern "C"
{
#endif

   /**********************************************************************
   /This file defines the operations that enable and modify the Autoupdate 
   /code update functionality.
   /
   /When autoupdate is enabled then the code running on the Netburner can 
   /be updated  remotely using the Newburner Update client application.

   **********************************************************************
   ********************SECURITY RISK*************************************
   **********************************************************************
    When this is updated this is a potential security risk, as someone can
    change the code running on your netburner board remotely.
    This risk can be minimized by providing a Password Authentication
    function to the UpdatePasswordHook.
   **********************************************************************/



   /**********************************************************************
   Enable the autoupdate functionality.
   This is simply done by calling the function.
   Once it is turned on, it can not be disabled.
   To Disable it during program execution then use
   the update_shutdown_func program hook described later in this header file
   **********************************************************************/
   void EnableAutoUpdate();




   /**********************************************************************
   Enable the TCP autoupdate functionality.
   This is simply done by calling the function.
   Once it is turned on, it can not be disabled.
   To Disable it during program execution then use
   the update_shutdown_func program hook described later in this header file
   **********************************************************************/
   int StartTcpUpdate( int priority ); 



   /**********************************************************************
     If this function pointer is set to point at a function of the form:
   int YourFunc(const char * name , const char * password);
   Then the system will indicate to the update requester that a Password 
   is needed. It will then request the password from the other end.
   It will also call this function with the passed in password and 
   name. If they are OK Return a 1 otherwise return a 0.
   It will do this in  an unsecure fashion (The password is in the TCP stream)
   If you need a more secure system it needs to be converted to a challenge/response
   system that would have significantly more impact on the code size.
   **********************************************************************/
   extern int  ( *update_authenticate_func )( const char *name, const char *passwd );
   extern int  ( *ipsetup_authenticate_func )( const char *name, const char *passwd );



   /**********************************************************************
     If this function pointer is set to point at a function of the form:
   int YourFunc(void);

   Then the system will call this function to shutdown the system before 
   it updates the code. If this function returns a 0 then the update will 
   be aborted.

   **********************************************************************/
   extern int  ( *update_shutdown_func )( void );



/**********************************************************************
  If this function pointer is set to point at a function of the form:
void YourFunc(void);

Then the system will call this function throughout the AutoUpdate/TCPUpdate
process to make sure that the watchdog timer is serviced.
**********************************************************************/
extern void  ( *watchdog_service_function )( void );



#ifdef __cplusplus
}
#endif


#endif
