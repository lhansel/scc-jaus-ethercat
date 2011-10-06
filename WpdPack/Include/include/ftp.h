/* Rev:$Revision: 1.11 $ */  
/******************************************************************************
 * Copyright 2001-2008 NetBurner  ALL RIGHTS RESERVED
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
 * 5405 Morehouse Dr #200
 * San Diego Ca, 92121
  *****************************************************************************/
#ifndef _NB_FTP_H                      
#define _NB_FTP_H                      

#ifdef __cplusplus
extern "C"
{
#endif

#define FTP_OK            (0)
#define FTP_TIMEOUT       (-1)
#define FTP_PASSWORDERROR (-2)
#define FTP_CONNECTFAIL   (-3)
#define FTP_COMMANDFAIL   (-4)
#define FTP_COMMANDERROR  (-4)
#define FTP_BADSESSION    (-5)
#define FTP_NETWORKERROR  (-6)




   /* FTP Client code */
   /*Module: FTP Client
   This Module provides code for sending and receiving files from an FTP server.
   Some basic knowledge of the inner workings of FTP will be helpful 
   in using this module. Please see Chapter 27 of Stevens.
   The basic process to use the FTP client is:
   Open the FTP session with the FTP_InitializeSession call.
   Then operate on the FTP session.
   The vast majority of the functions are self explanitory, but 
   Four functions require a little more explanation.
      * FTPGetList
      * FTPFileNames
      * FTPGetFile
      * FTPSendFile
   Please read the documentation for these functions in detail
   before trying to use them.
   Finnaly when your are doce call the function: FTP_CloseSession
   */

   /*Functions:*/
   /*Group:Initialization function*/
   /*Create/Initialize a connection to an FTP server.*/
   /*
   This call makes the connection to the FTP server and logs in 
   with the username and password.
   The session returned from this call should be
   used with the file and directory functions.
   When one is done with this session one must call the function:
   FTP_CloseSession
   to close the session.
   Parameters:
      IPADDR server_address The IP address of the server.
      WORD port The Port to connect to on the server.
      PCSTR UserName The account username.
      PCSTR PassWord The account password.
      DWORD time_out The number of ticks to wait.
      
   Returns:
      Returns:
      int The command success code.
      >0 = FTP session
      FTP_TIMEOUT       = Time out
      FTP_PASSWORDERROR = Password error.
      FTP_CONNECTFAIL   = Network error.
      FTP_NETWORKERROR   = Network error.
   */
   /*See Also: 
      int FTP_CloseSession(int session);
   */
   int FTP_InitializeSession( IPADDR server_address,
                              WORD port,
                              PCSTR UserName,
                              PCSTR PassWord,
                              DWORD time_out );


   /* Close the ftp session. */
   /*
   Close the ftp session . 
   This function should be called when an FTP session is complete.
   Failure to call this function will result in memory/resource leaks.
   Returns:
      int The command success code.
      FTP_OK Closed successfully
      FTP_TIMEOUT       = Time out
      FTP_COMMANDFAIL  = Command error.  
      FTP_NETWORKERROR   = Network error.
      FTP_BADSESSION    = bad session number.
   */
   /*See Also: 
      int FTP_InitializeSession(IPADDR server_address, WORD port, PCSTR UserName, PCSTR PassWord, DWORD time_out);  
   */
   int FTP_CloseSession( int session );














   /*Group:FTP client Directory functions*/
   /* Get the current working directory */
   /*
   Copy the name of the current working directory into the 
   provided buffer.
   Parameters:
      int ftp_Session The ftp session id returned from the FTP_InitializeSession call.
      char * dir_buf The buffer to hold the directory name.
      int nbytes The maximum nuber of bytes to copy.
      WORD timeout Number of ticks to wait for timeout.
   Returns:
      int The command success code.
      >0 = The number of bytes read.
      FTP_TIMEOUT       = Time out
      FTP_CONNECTFAIL   = FTP failure.
      FTP_NETWORKERROR   = Network error.
      FTP_COMMANDFAIL   = FTP failed to process/execute the command.
   */
   /*See Also:
      int FTPSetDir(int ftp_Session, const char * new_dir, WORD timeout);
      int FTPDeleteDir(int ftp_Session, const char * dir_to_delete, WORD timeout);
      int FTPMakeDir(int ftp_Session, const char * dir_to_make, WORD timeout);
      int FTPUpDir(int ftp_Session, WORD timeout);
   */
   int FTPGetDir( int ftp_Session, char *dir_buf, int nbytes, WORD timeout );




   /* Set the current working directory */
   /*
   Set the current working directory.
   Parameters:
      int ftp_Session The ftp session id returned from the FTP_InitializeSession call.
      const char * new_dir The name of the directory to change to.
      WORD timeout Number of ticks to wait for timeout.
   Returns:
      int The command success code.
      FTP_OK Changed successfully
      FTP_TIMEOUT       = Time out
      FTP_CONNECTFAIL   = FTP failure.
      FTP_NETWORKERROR   = Network error.
      FTP_COMMANDFAIL   = FTP failed to process/execute the command.
   */
   /*See Also:
      int FTPGetDir(int ftp_Session, char * dir_buf, int nbytes, WORD timeout);
      int FTPDeleteDir(int ftp_Session, const char * dir_to_delete, WORD timeout);
      int FTPMakeDir(int ftp_Session, const char * dir_to_make, WORD timeout);
      int FTPUpDir(int ftp_Session, WORD timeout);
   */
   int FTPSetDir( int ftp_Session, const char *new_dir, WORD timeout );






   /* Delete a directory*/
   /*
   Delete a directory.
   Parameters:
      int ftp_Session The ftp session id returned from the FTP_InitializeSession call.
      const char * dir_to_delete The name of the directory to be deleted.
      WORD timeout Number of ticks to wait for timeout.
   Returns:
      int The command success code.
      FTP_OK Deleted successfully
      FTP_TIMEOUT       = Time out
      FTP_CONNECTFAIL   = FTP failure.
      FTP_NETWORKERROR   = Network error.
      FTP_COMMANDFAIL   = FTP failed to process/execute the command.
   */
   /*See Also:
      int FTPGetDir(int ftp_Session, char * dir_buf, int nbytes, WORD timeout);
      int FTPSetDir(int ftp_Session, const char * new_dir, WORD timeout);
      int FTPMakeDir(int ftp_Session, const char * dir_to_make, WORD timeout);
      int FTPUpDir(int ftp_Session, WORD timeout);
   */
   int FTPDeleteDir( int ftp_Session, const char *dir_to_delete, WORD timeout );



   /*Make a directory */
   /*
   Make a new directory on the server.
   Parameters:
      int ftp_Session The ftp session id returned from the FTP_InitializeSession call.
      const char * dir_to_make The name of the directory to make.
      WORD timeout Number of ticks to wait for timeout.
   Returns:
      int The command success code.
      FTP_OK Created successfully
      FTP_TIMEOUT       = Time out
      FTP_CONNECTFAIL   = FTP failure.
      FTP_NETWORKERROR   = Network error.
      FTP_COMMANDFAIL   = FTP failed to process/execute the command.
   */
   /*See Also:
      int FTPGetDir(int ftp_Session, char * dir_buf, int nbytes, WORD timeout);
      int FTPSetDir(int ftp_Session, const char * new_dir, WORD timeout);
      int FTPDeleteDir(int ftp_Session, const char * dir_to_delete, WORD timeout);
      int FTPUpDir(int ftp_Session, WORD timeout);
   */int FTPMakeDir( int ftp_Session, const char *dir_to_make, WORD timeout );



   /*Move up one directory level*/
   /*
   Move up one directory level in the directory hierarchy on the server.
   Parameters:
      int ftp_Session The ftp session id returned from the FTP_InitializeSession call.
      WORD timeout Number of ticks to wait for timeout.
   Returns:
      int The command success code.
      FTP_OK Changed directory successfully
      FTP_TIMEOUT       = Time out
      FTP_CONNECTFAIL   = FTP failure.
      FTP_NETWORKERROR   = Network error.
      FTP_COMMANDFAIL   = FTP failed to process/execute the command.
   */
   /*See Also:
      int FTPGetDir(int ftp_Session, char * dir_buf, int nbytes, WORD timeout);
      int FTPSetDir(int ftp_Session, const char * new_dir, WORD timeout);
      int FTPDeleteDir(int ftp_Session, const char * dir_to_delete, WORD timeout);
      int FTPMakeDir(int ftp_Session, const char * dir_to_make, WORD timeout);
   */
   int FTPUpDir( int ftp_Session, WORD timeout );







   /*Group:FTP client Misc file functions*/
   /*Delete a file on the server*/
   /* 
   This call Deletes the specified  file on the server.
   Parameters:
      int ftp_Session The ftp session id returned from the FTP_InitializeSession call.
      const char * file_name The file name to be deleted.
      WORD timeout Number of ticks to wait for timeout.
   Returns:
      int The command success code.
      FTP_OK Deleted successfully
      FTP_TIMEOUT       = Time out
      FTP_CONNECTFAIL   = FTP Failure.
      FTP_NETWORKERROR  = Network error.
      FTP_COMMANDFAIL   = FTP failed to process/execute the command.
   */
   /*See Also:
      int FTPSendFile(int ftp_Session,const char * full_file_name,BOOL bBinaryMode, WORD timeout);
      int FTPGetFile(int ftp_Session, const char * full_file_name,BOOL bBinaryMode, WORD timeout);
      int FTPRenameFile(int ftp_Session,const char * old_file_name,const char * new_file_name, WORD timeout);
    
   */
   int FTPDeleteFile( int ftp_Session, const char *file_name, WORD timeout );




   /*Rename a file on the server*/
   /* 
   This call renames the specified file on the server.
   Parameters:
      int ftp_Session The ftp session id returned from the FTP_InitializeSession call.
      const char * old_file_name The file name to be renamed.
      const char * new_file_name The new file name.
      WORD timeout Number of ticks to wait for timeout.
   Returns:
          Returns:
      int The command success code.
      FTP_OK Deleted successfully
      FTP_TIMEOUT       = Time out
      FTP_CONNECTFAIL   = FTP Failure.
      FTP_NETWORKERROR  = Network error
      FTP_COMMANDFAIL   = FTP failed to process/execute the command.
   */
   /*See Also:
      int FTPSendFile(int ftp_Session,const char * full_file_name,BOOL bBinaryMode, WORD timeout);
      int FTPGetFile(int ftp_Session, const char * full_file_name,BOOL bBinaryMode, WORD timeout);
      int FTPDeleteFile(int ftp_Session,const char * file_name, WORD timeout);
    
   */
   int FTPRenameFile( int ftp_Session,
                      const char *old_file_name,
                      const char *new_file_name,
                      WORD timeout );








   /*Group:FTP client Send file functions*/
   /*Setup to send a file on an existing FTP session*/
   /* 
   This call initializes the send file process to send a file to the server.
   Using this requires some knowledge of how FTP works.
   This call sets up a new TCP connection to send a file to the server.
   To actually send the file use the returned file descriptor
   to write out the file use the standard IO write commands and 
   then close the returned file descriptor.
   VERY IMPORTANT!
   after you have sent the file you must call  FTPGetCommandResult
   to get the result from the write. a return value of 226 is normal.
   Failing to do this will cause the system to get out of sync.
   Parameters:
      int ftp_Session The ftp session id returned from the FTP_InitializeSession call.
      const char * file_name The file name to be transfered.
      BOOL bBinaryMode True if the file is to be transfered in binary mode.
      WORD timeout Number of ticks to wait for timeout.
   Returns:
      int The command success code.
      >0 = FTP write file descriptor.
      FTP_TIMEOUT       = Time out
      FTP_CONNECTFAIL   = FTP Failure.
      FTP_NETWORKERROR  = Network error.
      FTP_COMMANDFAIL   = FTP failed to process/execute the command.
   */
   /*Example:
        int fdr=FTPSendFile(ftp,"FOOBAR.TXT",FALSE,100);
         if (fdr>0)
            {
         writestring(fdr,"This is a test file\r\n");
         writestring(fdr,"This is line 2 of the test file\r\n");
         writestring(fdr,"Last Line\r\n");
         close(fdr);
         rv=FTPGetCommandResult(ftp,tmp_resultbuff,255,100);
            if (rv!=226) iprintf("Write Error Command result = %d %s\r\n",rv,tmp_resultbuff);
            }
            else
            iprintf("Failed to create file FOOBAR.TXT\r\n");
   */
   /*See Also: 
      int FTPDeleteFile(int ftp_Session,const char * file_name, WORD timeout);
      int FTPRenameFile(int ftp_Session,const char * old_file_name,const char * new_file_name, WORD timeout);
      int FTPGetCommandResult(int ftp_Session, char * cmd_buf, int nbytes, WORD timeout);
   */
   int FTPSendFile( int ftp_Session,
                    const char *full_file_name,
                    BOOL bBinaryMode,
                    WORD timeout );



















   /*Group:FTP client Get file functions*/
   /*Setup to receive a file on an existing FTP session*/
   /* 
   This call initializes the get file process to receive a file from the server.
   Using this requires some knowledge of how FTP works.
   This call sets up a new TCP connection to receive a file from the server.
   To actually receive the file use the returned file descriptor
   to read the  file useing the standard IO read commands.
   Then close the returned file descriptor when you are done.
   VERY IMPORTANT!
   After you have received the file you must call  FTPGetCommandResult
   to get the result from the read. A return value of 226 is normal.
   Failing to do this will cause the system to get out of sync.
   Parameters:
      int ftp_Session The ftp session id returned from the FTP_InitializeSession call.
      const char * full_file_name The complete file name to be transfered. (Includes path )
      BOOL bBinaryMode True if the file is to be transfered in binary mode.
      WORD timeout Number of ticks to wait for timeout.
   Returns:
      int The command success code.
      >0 = FTP read file descriptor.
      FTP_TIMEOUT       = Time out
      FTP_CONNECTFAIL   = FTP Failure.
      FTP_NETWORKERROR  = Network error.
      FTP_COMMANDFAIL   = FTP failed to process/execute the command.
   */
   /*Example:
      int fdr=FTPGetFile(ftp,"FOOBAR.TXT",FALSE,100);
         if (fdr>0)
            { 
              ShowFileContents(fdr); //This function reads data from the file until complete.
                      //You would probably use a different function.
                      //The source for this function is shown in the module example.   
            close(fdr);
         // Now read the command result code from the GetFile command 
            rv=FTPGetCommandResult(ftp,tmp_resultbuff,255,100);
            if (rv!=226) iprintf("Error Command result = %d %s\r\n",rv,tmp_resultbuff);
            }
            else
            iprintf("Failed to get file FOOBAR.TXT\r\n");
   */
   /*See Also: 
      int FTPGetList(int ftp_Session, const char * full_dir_name,BOOL bBinaryMode, WORD timeout);
      int FTPDeleteFile(int ftp_Session,const char * file_name, WORD timeout);
      int FTPRenameFile(int ftp_Session,const char * old_file_name,const char * new_file_name, WORD timeout);
      int FTPGetCommandResult(int ftp_Session, char * cmd_buf, int nbytes, WORD timeout);
   */
   int FTPGetFile( int ftp_Session,
                   const char *full_file_name,
                   BOOL bBinaryMode,
                   WORD timeout );















   /*Setup to receive a directory on an existing FTP session*/
   /* 
   This call initializes the get directory process to receive a full directory listing from the server.
   Using this requires some knowledge of how FTP works.
   This call sets up a new TCP connection to receive the  file listing from the server.
   To actually receive the list use the returned file descriptor
   to read the  list useing the standard IO read commands.
   Then close the returned file descriptor when you are done.
   VERY IMPORTANT!
   After you have received the list you must call  FTPGetCommandResult
   to get the result from the read. A return value of 226 is normal.
   Failing to do this will cause the system to get out of sync.
   Parameters:
      int ftp_Session The ftp session id returned from the FTP_InitializeSession call.
      const char * full_dir_name The complete dir name to be transfered. (Can be NULL)
      WORD timeout Number of ticks to wait for timeout.
   Returns:
      int The command success code.
      >0 = FTP read file descriptor.
      FTP_TIMEOUT       = Time out
      FTP_CONNECTFAIL   = FTP Failure.
      FTP_NETWORKERROR  = Network error.
      FTP_COMMANDFAIL   = FTP failed to process/execute the command.
   */
   /*Example:
          int fdr=FTPGetList(ftp,NULL,100);
         if (fdr>0)
            { 
              ShowFileContents(fdr); //This function reads data from the fd until complete.
                      //You would probably use a different function.
                      //The source for this function is shown in the module example.   
            close(fdr);
         // Now read the command result code from the GetList command 
            rv=FTPGetCommandResult(ftp,tmp_resultbuff,255,100);
            if (rv!=226) iprintf("Error Command result = %d %s\r\n",rv,tmp_resultbuff);
            }
            else
            iprintf("Failed to get file list\r\n");
   */

   /*See Also:
      int FTPGetFileNames(int ftp_Session, const char * full_dir_name, WORD timeout);
      int FTPGetFile(int ftp_Session, const char * full_file_name,BOOL bBinaryMode, WORD timeout);
      int FTPGetCommandResult(int ftp_Session, char * cmd_buf, int nbytes, WORD timeout);
   */
   int FTPGetList( int ftp_Session, const char *full_dir_name, WORD timeout );










   /*Setup to receive a just the file names from the existing FTP session*/
   /* 
   This call initializes the get directory process to receive just the file names listing from the server.
   Using this requires some knowledge of how FTP works.
   This call sets up a new TCP connection to receive the  file listing from the server.
   To actually receive the list use the returned file descriptor
   to read the  list useing the standard IO read commands.
   Then close the returned file descriptor when you are done.
   VERY IMPORTANT!
   After you have received the list you must call  FTPGetCommandResult
   to get the result from the read. A return value of 226 is normal.
   Failing to do this will cause the system to get out of sync.
   Parameters:
      int ftp_Session The ftp session id returned from the FTP_InitializeSession call.
      const char * full_dir_name The complete file name to be transfered. (Includes path )
      WORD timeout Number of ticks to wait for timeout.
   Returns:
      int The command success code.
      >0 = FTP read file descriptor.
      FTP_TIMEOUT       = Time out
      FTP_CONNECTFAIL   = FTP Failure.
      FTP_NETWORKERROR  = Network error.
      FTP_COMMANDFAIL   = FTP failed to process/execute the command.
   */
   /*Example:
          int fdr=FTPFileNames(ftp,NULL,100);
         if (fdr>0)
            { 
              ShowFileContents(fdr); //This function reads data from the fd until complete.
                      //You would probably use a different function.
                      //The source for this function is shown in the module example.   
            close(fdr);
         // Now read the command result code from the GetList command 
            rv=FTPGetCommandResult(ftp,tmp_resultbuff,255,100);
            if (rv!=226) iprintf("Error Command result = %d %s\r\n",rv,tmp_resultbuff);
            }
            else
            iprintf("Failed to get file list\r\n");
   */
   /*See Also:
      int FTPGetList(int ftp_Session, const char * full_dir_name, WORD timeout);
      int FTPGetFileNames(int ftp_Session, const char * full_dir_name, WORD timeout);
      int FTPGetFile(int ftp_Session, const char * full_file_name,BOOL bBinaryMode, WORD timeout);
      int FTPGetCommandResult(int ftp_Session, char * cmd_buf, int nbytes, WORD timeout);
   */
   int FTPGetFileNames( int ftp_Session, const char *full_dir_name, WORD timeout );









   /*Group:FTP client lower level functions*/
   /*Send a command and get a response from the control connection*/
   /*This command is the basis for most of the FTP commands
   It is used where a stream return is not expected.
   Parameters:
      int ftp_Session The ftp session id returned from the FTP_InitializeSession call.
      const char * cmd The command to send not INCLUDING the \r\n.
      char * cmd_buf The buffer to hold the result.
      int nbytes The maximum nuber of bytes to copy.
      WORD timeout Number of ticks to wait for timeout.
   Returns:
      int The command success code.
      >0 = FTP read file descriptor.
      FTP_TIMEOUT       = Time out
      FTP_CONNECTFAIL   = FTP failure.
      FTP_NETWORKERROR   = Network error.
      FTP_COMMANDFAIL   = FTP failed to process/execute the command.
   See Also:
      int FTPGetCommandResult(int ftp_Session, char * cmd_buf, int nbytes, WORD timeout);
      int FTPRawStreamCommand(int ftp_Session, const char * cmd,int * pResult,char * cmd_buf, int nbytes, WORD timeout);
   */
   int FTPRawCommand( int ftp_Session,
                      const char *cmd,
                      char *cmd_buf,
                      int nbytes,
                      WORD timeout );



   /*Get a response from the control connection without sending a command */
   /*This command may be used after 
         *  FTPGetList
         *  FTPFileNames
         *  FTPGetFile
         *  FTPSendFile
   to get the command result.
   Parameters:
      int ftp_Session The ftp session id returned from the FTP_InitializeSession call.
      char * cmd_buf The buffer to hold the result.
      int nbytes The maximum nuber of bytes to copy.
      WORD timeout Number of ticks to wait for timeout.
   Returns:
      int The command success code.
      >0 = FTP read file descriptor.
      FTP_TIMEOUT       = Time out
      FTP_CONNECTFAIL   = FTP failure.
      FTP_NETWORKERROR   = Network error.
      FTP_COMMANDFAIL   = FTP failed to process/execute the command.
   See Also:
      int FTPRawCommand(int ftp_Session, const char * cmd,char * cmd_buf, int nbytes, WORD timeout);
      int FTPRawStreamCommand(int ftp_Session, const char * cmd,int * pResult,char * cmd_buf, int nbytes, WORD timeout);
   */
   int FTPGetCommandResult( int ftp_Session, char *cmd_buf, int nbytes, WORD timeout );


   /*Send a command and get a response over a stream connection*/
   /*This command is the basis for most of the GetList, GetFiles etc commands
   It is used where a stream return IS expected.
   Parameters:
      int ftp_Session The ftp session id returned from the FTP_InitializeSession call.
      const char * cmd The command to send not INCLUDING the \r\n.
      int * pResult The FTP command result code.
      char * cmd_buf The buffer to hold the command connection result.
      int nbytes The maximum nuber of bytes to copy into the cmd_buf.
      WORD timeout Number of ticks to wait for timeout.
   Returns:
      int The command success code.
      >0 = The FTP numeric response code.
      FTP_TIMEOUT       = Time out
      FTP_CONNECTFAIL   = FTP failure.
      FTP_NETWORKERROR   = Network error.
      FTP_COMMANDFAIL   = FTP failed to process/execute the command.
   See Also:
      int FTPGetCommandResult(int ftp_Session, char * cmd_buf, int nbytes, WORD timeout);
      int FTPRawCommand(int ftp_Session, const char * cmd,char * cmd_buf, int nbytes, WORD timeout);
   */
   int FTPRawStreamCommand( int ftp_Session,
                            const char *cmd,
                            int *pResult,
                            char *cmd_buf,
                            int nbytes,
                            WORD timeout );



   /* Set FTP in normal Active mode */
   void FTPActiveMode( int ftp_Session );


   /*Set FTP in Passive mode for better Firewall behavior*/
   void FTPPassiveMode( int ftp_Session );





   /*Module Example:
   // *******************************************************************
   // FTP Client Example Program
   // 
   // This program will run a FTP Client program on the NetBurner board
   // to do the following:
   // - Connect to a FTP Server
   // - Change to a remote directory called "test1"
   // - Obtain a directory listing and print the listing to stdout
   // - Create a file on the FTP Server called FOOBAR.TXT
   // - Read back contents of FOOBAR.TXT and send to stdout
   // 
   // Setup Requirements:
   // 1. Access to a FTP Server
   // 2. User name and password for the FTP Server
   // 3. A directory called "test1" must exist on the FTP Server
   // 4. Write permissions to the test1 directory
   // 
   // 
   // *******************************************************************
   #include <predef.h>
   #include <stdio.h>
   #include <ctype.h>
   #include <startnet.h>
   #include <autoupdate.h>
   #include <ftp.h>
   extern "C" {
   void UserMain(void * pd);
   }
   #define SERVER_IP_ADDR "10.1.1.3"
   #define FTP_PORT 21
   #define USER "pbreed"
   #define PASS "yodi03848"
   char tmp_resultbuff[255];
   // This function reads the data stream from the fd and 
   // displays it to stdout, which is usually the com1 serial 
   // port on the NetBurner board.
   void ShowFileContents(int fdr)
   {
      iprintf("\r\n[");
      int rv;
      do
      {
         rv = ReadWithTimeout(fdr,tmp_resultbuff,255,20);
         if (rv < 0) iprintf("RV = %d\r\n",rv);
         else
        {
           tmp_resultbuff[rv] = 0;
           iprintf("%s",tmp_resultbuff); 
        }
      }
      while (rv > 0);
      iprintf("]\r\n");
   }
   // UserMain Function
   void UserMain(void * pd)
   {
      InitializeStack();        // Initialize TCP/IP Stack
      EnableAutoUpdate();       // Enable NetBurner AutoUpdate downloads
      OSChangePrio(MAIN_PRIO);  // Set UserMain priority level to default
      // Open FTP session at specified IP Address with specified user name
      // and password. There is a 5 second timeout.
      int ftp = FTP_InitializeSession(AsciiToIp(SERVER_IP_ADDR),FTP_PORT,USER,PASS,5*TICKS_PER_SECOND);
      if (ftp > 0) // if the var ftp is > 0, it is the session handle
      {
         int rv = 0;
         // Change to the test directory 
         // ************************************WARNING***************************
         // To run this sample a test1 directory must exist on the test server.
         // ************************************WARNING***************************
         // Change to test1 directory
         rv = FTPSetDir(ftp,"test1",5*TICKS_PER_SECOND);
         if (rv == FTP_OK)
        {
            iprintf("Reading file names from test1 directory\r\n");
            int fdr = FTPGetList(ftp,NULL,5*TICKS_PER_SECOND);
            if (fdr > 0)
            {
               ShowFileContents(fdr);
               close(fdr);
               // Read the command result code from the FTPGetList command 
               rv = FTPGetCommandResult(ftp,tmp_resultbuff,255,5*TICKS_PER_SECOND);
               if (rv != 226) 
                  iprintf("Error Command result = %d %s\r\n", rv,tmp_resultbuff);
            }
            else
               iprintf("Failed to get file list\r\n");
            // Create sample file 
            iprintf("Now creating the sample file FOOBAR.TXT\r\n");
            int fdw = FTPSendFile(ftp, "FOOBAR.TXT", FALSE, 5*TICKS_PER_SECOND);
            if (fdw > 0)
            {
               writestring(fdw,"This is a test file\r\n");
               writestring(fdw,"This is line 2 of the test file\r\n");
               writestring(fdw,"Last Line\r\n");
               close(fdw);
               
               rv = FTPGetCommandResult(ftp,tmp_resultbuff,255,5*TICKS_PER_SECOND);
               if (rv != 226) 
                  iprintf("Error Command result = %d %s\r\n",rv,tmp_resultbuff);
               iprintf("Now trying to readback the file we created \r\n");
               fdr = FTPGetFile(ftp,"FOOBAR.TXT",FALSE,5*TICKS_PER_SECOND);
               if (fdr > 0)
               { 
                  ShowFileContents(fdr);
                  close(fdr);
                  // Read the command result code from the FTPGetFile command 
                  rv = FTPGetCommandResult(ftp,tmp_resultbuff,255,5*TICKS_PER_SECOND);
                  if (rv != 226) 
                     iprintf("Error Command result = %d %s\r\n",rv,tmp_resultbuff);
               }
               else
                  iprintf("Failed to get file FOOBAR.TXT\r\n");
             }
            else
                iprintf("Failed to create file FOOBAR.TXT code = %d\r\n",rv);
          }
          else
             iprintf("Failed to change to test directory");
          FTP_CloseSession(ftp);
      }
      else
         iprintf("Failed to open FTP Session\r\n");
      while(1);
   }
   */
#ifdef __cplusplus
}
#endif

#endif





