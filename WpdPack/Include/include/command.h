/* Rev:$Revision: 1.10 $ */  

/******************************************************************************
 * Copyright 1998-2005 NetBurner  ALL RIGHTS RESERVED
 *   Permission is hereby granted to purchasers of NetBurner Hardware
 *   to use or modify this computer program for any use as long as the
 *   resultant program is only executed on NetBurner provided hardware.
 *
 *   No other rights to use this program or it's derivitives in part or
 *   in whole are granted.
 *
 *   It may be possible to license this or other NetBurner software for
 *        use on non NetBurner Hardware.
 *   Please contact sales@netburner.com for more infomation.
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


/*****************************************************************************
*****************************************************************************
*****************************************************************************

      This is the header file for a command processor task.
      It reads input one line at a time from multiple sources and
      when it gathers a whole line it sends it to a command processor

*****************************************************************************
*****************************************************************************
*****************************************************************************/

#ifndef _NB_COMMAND_H
#define _NB_COMMAND_H

#ifdef __cplusplus
extern "C"
{
#endif


#define CMD_OK     (0) 
#define CMD_CLOSE  (1)
#define CMD_FAIL   (2)
#define CMD_AUTH_FAIL (3)
#define CMD_TO_MANY_FDS   (4)


   /*****************************************************************************
    External Authentication function CALLBACK , used to verify Username and Password 
    If this function pointer is not NULL then each new Telnet sessioon will
    be asked to authenticate                 
   The function returns: 
   CMD_OK      IF the authentication was ok 
   CMD_CLOSE   IF the authentication causes the session to terminate (Close) 
   *****************************************************************************/
   extern int ( *CmdAuthenticateFunc )( const char *name, const char *passwd );



   /*****************************************************************************
    The command processing CALLBACK function 
    This function is of the form 
   int ProcessCommand(const char * command, int fd_respondeto)
   Where
      command is a pointer to the null terminated ASCII text of the command. 
      fRespondto is the FILE * all response should be set to. (Use fprintf) 
   The function returns: 
   CMD_OK      IF the command was ok 
   CMD_CLOSE   IF the command causes the session to terminate (Close) 
   *****************************************************************************/
   extern int ( * CmdCmd_func )( const char *command, FILE *fRespondto, void *pData );
   
   /* Same as CmdCmd func, but if defined sends single chars 
     If this is implmented does not do echo or line editing this is the responsibility of the 
     Application programmer. 
   */
   extern int ( * CmdChar_func )(char command, FILE *fRespondto, void *pData );



   /*****************************************************************************
   Connect CALLBACK function, if this function is not NULL then the system
   will call this function every time a new session is started 
   This function is of the form 
      void  ConnectCommand(int fd_respondeto)
   Where
      fRespondto is the FILE * all response should be sent to. (Use fprintf) 
   Returns an arbitrary void * data item to be asociated with the session. This
   data item is the same pData item used in other callback functions such as
   CmdPrompt_func. 
   *****************************************************************************/
   extern void*( * CmdConnect_func )( FILE *fRespondto );


   /*****************************************************************************
    Prompt callback function, if this function is not NULL then the system
    will call this function every time a new prompt line needs to be displayed
    This function is of the form 
      void  CommandPrompt(int fd_respondeto)
    Where
      fRespondto is the FILE * all response should be sent to. (Use fprintf) 
    The pData parameter is the value returned by CmdConnect_func.  
   *****************************************************************************/
   extern void ( * CmdPrompt_func )( FILE *fRespondto, void *pData );



   /*****************************************************************************
    Dis-Connect callback function, if this function is not NULL then the system
   will call this function every time a session is terminated
   This function is of the form 
      void  DisconnectCommand(int fd_respondeto, int cause)
   Where
      fRespondto is the FILE * all response should be sent to. (Use fprintf) 
      cause is why it is disconnected.
   The current values of Cause are : */
#define CMD_DIS_CAUSE_TIMEOUT (1)
#define CMD_DIS_CAUSE_CLOSED  (2)
#define CMD_DIS_SOCKET_CLOSED (3) /* Don't send a response for this case */
#define CMD_DIS_AUTH_FAILED   (4) /* Don't send a response for this case */

   /*****************************************************************************/
   extern void ( * CmdDisConnect_func )( FILE *fRespondto, int cause, void *pData );


   /*****************************************************************************
   The number of seconds a connection is idle before it is terminated
   due to inactivity.
   *****************************************************************************/
   extern int CmdIdleTimeout;


   /* If this is not NULL then it will be sent to the socket on connection.
   Before Authentication is tried 
   */
   extern const char *Cmdlogin_prompt;



   /*****************************************************************************
   Start the command processor.
      int priority = the UCOS task priority to run at 
   Returns:
         CMD_OK   
         CMD_FAIL
   *****************************************************************************/
   int CmdStartCommandProcessor( int priority );


   /* Stop the running process and close all open sockets/fd's */
   void CmdStopCommandProcessor();



   /****************************************************************************
    Add an established FD connection to the list of fd's managed 
    by the command processor.
    
      int fd       //the file descriptor 
      int require_auth //Do we Authenticate the connection on this FD?
      int time_out_conn //Do we time out the connection on this FD?
     Returns:
         CMD_OK   
         CMD_FAIL
         CMD_TO_MANY_FDS
   *****************************************************************************/
   int CmdAddCommandFd( int fd, int require_auth, int time_out_conn, int local_echo = TRUE ); 



   /*****************************************************************************/
   /* Remove an established FD (Either a TCP session or a serial connection 
   Returns:
         CMD_OK   
         CMD_FAIL
   *****************************************************************************/
   int CmdRemoveCommandFd( int Fd );


   /*****************************************************************************
    Start listening for connection on a TCP port.
      WORD port  // The port number
      int do_telnet_processing //Should we treat the port as telnet and process telnet negotiations?
      int max_connecitons //What are the max number of connections we should allow on this port
   Returns:
         CMD_OK   
         CMD_FAIL
   *****************************************************************************/
   int CmdListenOnTcpPort( WORD port, int do_telnet_processing, int max_connections );
   /* Same as above, but not siggnon or password */
   int CmdListenQuietOnTcpPort( WORD port, int do_telnet_processing, int max_connections );



   /*****************************************************************************
    Stop Listening for connections on the specified port.
    Also closes all open connections that were based on that port
   Returns:
         CMD_OK   
         CMD_FAIL
   *****************************************************************************/
   int CmdStopListeningOnTcpPort( WORD port );


   /* Send to all connected sockets, excluding "Listening sockets" */
   void SendToAll( char *buffer, int len, BOOL include_serial_ports );

#ifdef __cplusplus
}
#endif
#endif



