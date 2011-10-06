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


#ifndef _NB_FTPD_H                        
#define _NB_FTPD_H                        

#ifdef __cplusplus
extern "C"
{
#endif

/* Jan 16, 2008. These #defines were removed and all server functions (denoted as FTPD) 
  * were modified to use FTPD_OK and FTPD_FAIL. This was necessary so that the FTP
  * client and server header files could be used at the same time. If you have any 
  * errors in your application code, you can salefly change all server functions from 
  * FTP_OK/FAIL to FTPD_OK/FAIL. 
  */
//#define FTP_FAIL        (0)
//#define FTP_OK          (1)


#define FTPD_FAIL           (0)
#define FTPD_OK             (1)
#define FTPD_RUNNING        (2)
#define FTPD_NOT_RUNNING    (3)
#define FTPD_LISTEN_ERR     (4)

   /* FTP Server Code */
   /*Module: FTP Server
   Implementing an FTP server in an embedded system without a built-in 
   file system is not a trivial undertaking. Most embedded applications
   do not require a file system, and a file system is not part of the 
   standard NetBurner package. If a file system is required for a specific
   application, it is the responsibility of the programmer to implement
   the required features. A file system could be the trivially simple 
   example of a single file, or it could be quite complex. 
   Using the FTP Server requires that you, the programmer, write the 
   functions defined in the FTP documentation. These functions are
   "callback" functions that allow you to customize the FTP server
   actions to suit your particular application. All callback functions
   required for your application must be implemented by you.
   The NetBurner examples directory has two FTP server sample applications:
   1. examples\ftpd_trivial - A simple system that reads and writes a single file.
   2. examples\ftpd_expose_hml - A more complex example that exposes all of the
      HTML served files to the  FTP server. This example also shows how to upgrade 
      the NetBurner firmware and reset the system using FTP.
   */
   /*Functions:*/
   /*Group:FTP Server Initialization Functions */
   /*Initialize the FTP Server */
   /*
   This call starts the FTP Server task, which listens for incoming connections. Only one instance of the FTPD is allowed 
   Parameters:
      WORD port The TCP port to listen to for incoming FTP requests
      BYTE server_priority The uC/OS task priority for the FTP Server
   Returns:
      FTPD_RUNNING - The FTPD is already running
      FTPD_LISTEN_ERR - The listen socket was not able to be opened
      FTPD_OK - The FTPD was succesfully started
      FTPD_FAIL - The FTPD task could not be created
   See Also:
      void FTPDStopReq();
   */ 
   int FTPDStart( WORD port, BYTE server_priority );

    /*
   Group: FTP Server stop function
   This function sends a stop request to the currently running FTPD.
   Parameters:
      none
   Returns:
    FTPD_RUNNING - The FTPD is still running
    FTPD_NOT_RUNNING - The FTPD is no longer running
   See Also:
      int FTPDStart( WORD port, BYTE server_priority );
   */  
   int FTPDStopReq();

   /*Group: FTP Session callback typedef */
   /*typedef for all directory reporting callbacks */
   /*
   This callback type definition is used by the directory reporting functions.
   Parameters:
      int handle The handle passed into the listing function
      const char * name_to_report The file name to report for use in a directory listing
   Returns:
      FTPD_RUNNING - The FTPD is already running
      FTPD_LISTEN_ERR - The listen socket was not able to be opened
      FTPD_OK - The FTPD was succesfully started
      FTPD_FAIL - The FTPD task could not be created

   See Also:
      int FTPD_ListSubDirectories(const char * current_directory, void * pSession, FTPDCallBackReportFunct * pFunc, int handle);
      int FTPD_ListFile(const char * current_directory, void * pSession, FTPDCallBackReportFunct * pFunc, int handle);
      */


   
   typedef void ( FTPDCallBackReportFunct )( int handle, const char *name_to_report );


   /*Group: FTP Session callback functions that must be implemented by the programmer */
   /*Functions:*/
   /* Function called to indicate the start of a User Session. */
   /* 
   This function is called following the creation of a new FTP session. The function needs to determine 
   the validity of the user/password pair. The returned void pointer will be passed to all access functions,
   which will be asked to determine the validity of the operation based on the permissions 
   associated with the return value. 
   Parameters:
      const char * user The name of the user attempting to establish an FTP session
      const char * passwd The password of the user attempting to establish an FTP session
      const IPADDR hi_ip The IP address of the server trying to establish this connection
   Returns:
      NULL The user name/password set is invalid
      (obj) A non-null void pointer to an object that will be associated with this login session
   See Also:
      void   FTPDSessionEnd(void * pSession);
   */
   void *FTPDSessionStart( const char *user, const char *passwd, const IPADDR hi_ip );


   /*Called to indicate a user session will be terminated. */
   /*
   This callback function gives the user program the opportunity to clean up any storage 
   associated with the void pointer returned from the FTPBSessionStart( ) call.
   Parameters:
      void * pSession The void * object returned from the FTPBSessionStart( ) function call
   Returns:
       Nothing This is a void function
   See Also:
      void * FTPBSessionStart(const char * user, const char * passwd, const IPADDR hi_ip);
   */
   void FTPDSessionEnd( void *pSession );


   /*Group: FTP Directory callback functions that must be implemented by the programmer */
   /*Functions:*/
   /* Function called by the FTP Server to test for the existence of a directory. */
   /* 
   Called by the FTP Server as the result of an attempt to change to a new directory. This function can also 
   be used to validate the permissions of the session.  This function must be implemented by 
   the programmer.
   Parameters:
      const char * full_directory Name of the new directory to test
      void * pSession The void * object returned from the FTPBSessionStart( ) function call 
   Returns:
      FTPD_OK The requested directory exists
      FTPD_FAIL The requested directory does not exist, or access is not permitted for the user
   See Also:
      int FTPD_CreateSubDirectory(const char * current_directory, const char * new_dir, void * pSession);
      int FTPD_DeleteSubDirectory(const char * current_directory, const char * sub_dir, void * pSession);
   */
   int FTPD_DirectoryExists( const char *full_directory, void *pSession );


   /* Function called by the FTP Server to create a directory. */
   /* 
   Called by the FTP Server as the result of an attempt to create a new directory. This function can 
   also be used to validate the permissions of the session.  This function must be implemented 
   by the programmer.
   Parameters:
         const char * current_directory The current value of the session directory
      const char * new_dir The directory to create under the current_directory
      void * pSession The void * object returned from the FTPBSessionStart( ) function call
   Returns:
      FTPD_OK The requested directory was created
      FTPD_FAIL The requested directory could not be created
   See Also:
      int FTPD_DirectoryExists(const char * full_directory, void * pSession);
      int FTPD_DeleteSubDirectory(const char * current_directory, const char * sub_dir, void * pSession);
   */
   int FTPD_CreateSubDirectory( const char *current_directory,
                                const char *new_dir,
                                void *pSession );


   /* Function called by the FTP Server to delete a directory. */
   /* 
      Called by the FTP Server as the result of an attempt to delete a subdirectory. This function call can be used 
      to validate the permissions of this session.  This function must be implemented by the programmer.
   Parameters:
         const char * current_directory The current value of the session current directory
      const char * sub_dir The directory to delete under the current_directory
      void * pSession The void * object returned from the FTPBSessionStart( ) function call at the beginning of the session   
   Returns:
      FTPD_OK The requested directory was deleted
      FTPD_FAIL The requested directory could not be deleted
   See Also:
      int FTPD_DirectoryExists(const char * full_directory, void * pSession);
      int FTPD_CreateSubDirectory(const char * current_directory, const char * new_dir, void * pSession);
   */
   int FTPD_DeleteSubDirectory( const char *current_directory,
                                const char *sub_dir,
                                void *pSession );


   /* Function called by the FTP Server to list all subdirectories under the current directory. */
   /* 
      Called by the FTP Server as the result of a client's attempt to list the contents of a directory.  
      This function must be implemented by the programmer.
   Parameters:
         const char * current_directory The current value of the session current directory
      void * pSession The void * object returned from the FTPBSessionStart( ) function call
      FTPDCallBackReportFunct * pFunc The pointer to the callback function to be called for each subdirectory
      int handle The handle value to be passed back into the pFunc
   Returns:
      FTPD_OK The requested listing was successfully delivered
      FTPD_FAIL The requested directory could not be listed
   See Also:
      int FTPD_DirectoryExists(const char * full_directory, void * pSession);
      int FTPD_DeleteSubDirectory(const char * current_directory, const char * sub_dir, void * pSession);
      int FTPD_CreateSubDirectory(const char * current_directory, const char * new_dir, void * pSession);
   Example: 
   Everything inside the callback function stub must be supplied by the programmer. The FTP server will
   automatically call this function and provide values for the function variables. It is the programmer's
   responsibility to to execute pFunc( ) with the provided handle and a pointer to the string representing
   the subdirectory name. pFunc( ) must be executed once for each subdirectory name.
   In this example, the variables number_of_directories and DirectoryName[] must be declared and 
   initialized elsewhere in the application program.
   int FTPD_ListSubDirectories(const char * current_directory, void * pSession, FTPDCallBackReportFunct * pFunc, int handle);
   {
      for (int n = 0; n < number_of_dir; n++)
         pFunc(handle, DirectoryName[n]);
      return FTPD_OK;
   }
   */
   int FTPD_ListSubDirectories( const char *current_directory,
                                void *pSession,
                                FTPDCallBackReportFunct *pFunc,
                                int handle );


   /*Group: FTP file callback functions that must be implemented by the programmer */
   /*Functions:*/
   /*Function to report on the whether or not a file exists */
   /*
   Check for the existence of a file, usually just before an attempt is made to download the file.
   This function must be implemented by the programmer.
   Parameters:
         const char * full_directory The current value of the session directory
      const char * file_name The name of the file to check
      void * pSession The void * object returned from the FTPBSessionStart( ) function call
    
   Returns:
      FTPD_OK The requested file exists
      FTPD_FAIL The requested file does not exist
   See Also:
      int FTPD_FileExists(const char * full_directory, const char * file_name, void * pSession);
      int FTPD_SendFileToClient(const char * full_directory, const char * file_name, void * pSession, int fd);
      int FTPD_AbleToCreateFile(const char * full_directory, const char * file_name, void * pSession); 
      int FTPD_GetFileFromClient(const char * full_directory, const char * file_name, void * pSession, int fd);
      int FTPD_DeleteFile(const char * current_directory, const char * file_name, void * pSession);
      int FTPD_ListFile(const char * current_directory, void * pSession, FTPDCallBackReportFunct * pFunc, int handle);
   */
   int FTPD_FileExists( const char *full_directory, const char *file_name, void *pSession );



   /*Function to send the contents of a file to a file descriptor */
   /*
   Send a file to a FTP client. This function must be implemented by the programmer.
   Parameters:
         const char * full_directory. The current value of the session directory
      const char * file_name The name of the file to send
      void * pSession The void * object returned from the FTPBSessionStart( ) function call
      int fd  The file descriptor to send to
   Returns:
      FTPD_OK The requested file was sent.
      FTPD_FAIL The requested file was not sent.
   See Also:
      int FTPD_FileExists(const char * full_directory, const char * file_name, void * pSession);
      int FTPD_AbleToCreateFile(const char * full_directory, const char * file_name, void * pSession); 
      int FTPD_GetFileFromClient(const char * full_directory, const char * file_name, void * pSession, int fd);
      int FTPD_DeleteFile(const char * current_directory, const char * file_name, void * pSession);
      int FTPD_ListFile(const char * current_directory, void * pSession, FTPDCallBackReportFunct * pFunc, int handle);
   */
   int FTPD_SendFileToClient( const char *full_directory,
                              const char *file_name,
                              void *pSession,
                              int fd );



   /*Function to report on the ability to create/receive a file. */
   /*
   Determine if a file can be created.  This function must be implemented by the programmer.
   Parameters:
         const char * full_directory The current value of the session directory
      const char * file_name The name of the file to create
      void * pSession The void * object returned from the FTPBSessionStart( ) function call
   Returns:
      FTPD_OK The requested file can be written/created
      FTPD_FAIL The requested file could not be created
   See Also:
      int FTPD_FileExists(const char * full_directory, const char * file_name, void * pSession);
      int FTPD_SendFileToClient(const char * full_directory, const char * file_name, void * pSession, int fd);
      int FTPD_GetFileFromClient(const char * full_directory, const char * file_name, void * pSession, int fd);
      int FTPD_DeleteFile(const char * current_directory, const char * file_name, void * pSession);
      int FTPD_ListFile(const char * current_directory, void * pSession, FTPDCallBackReportFunct * pFunc, int handle);
   */
   int FTPD_AbleToCreateFile( const char *full_directory,
                              const char *file_name,
                              void *pSession ); 




   /*Function to create/get a file */
   /*
   Receive a file from the FTP client.  This function must be implemented by the programmer.
   Parameters:
         const char * full_directory The current value of the session directory
      const char * file_name The name of the file to create
      void * pSession The void * object returned from the FTPBSessionStart( ) function call
      int fd The file descriptor that will be used to receive the file
   Returns:
      FTPD_OK The requested file was written/created
      FTPD_FAIL The requested file was not created
   See Also:
      int FTPD_FileExists(const char * full_directory, const char * file_name, void * pSession);
      int FTPD_SendFileToClient(const char * full_directory, const char * file_name, void * pSession, int fd);
      int FTPD_AbleToCreateFile(const char * full_directory, const char * file_name, void * pSession); 
      int FTPD_DeleteFile(const char * current_directory, const char * file_name, void * pSession);
      int FTPD_ListFile(const char * current_directory, void * pSession, FTPDCallBackReportFunct * pFunc, int handle);
   */
   int FTPD_GetFileFromClient( const char *full_directory,
                               const char *file_name,
                               void *pSession,
                               int fd );



   /*User written function to delete a file */
   /*
   Delete a file.  This function must be implemented by the programmer.
   Parameters:
         const char * full_directory The current value of the session directory
      const char * file_name The name of the file to delete
      void * pSession The void * object returned from the FTPBSessionStart( ) function call
   Returns:
      FTPD_OK The requested file was deleted
      FTPD_FAIL The requested file could not be deleted
   See Also:
      int FTPD_FileExists(const char * full_directory, const char * file_name, void * pSession);
      int FTPD_SendFileToClient(const char * full_directory, const char * file_name, void * pSession, int fd);
      int FTPD_AbleToCreateFile(const char * full_directory, const char * file_name, void * pSession); 
      int FTPD_GetFileFromClient(const char * full_directory, const char * file_name, void * pSession, int fd);
      int FTPD_ListFile(const char * current_directory, void * pSession, FTPDCallBackReportFunct * pFunc, int handle);
   */
   int FTPD_DeleteFile( const char *current_directory,
                        const char *file_name,
                        void *pSession );


   /*User written function to rename a file */
   /*
   Rename a file.  This function must be implemented by the programmer.
   Parameters:
      const char * full_directory The current value of the session directory
      const char * cur_file_name The name of the file to rename
      const char * new_file_name 
      void * pSession The void * object returned from the FTPBSessionStart( ) function call
   Returns:
      FTPD_OK The requested file was deleted
      FTPD_FAIL The requested file could not be renamed
   See Also:
      int FTPD_FileExists(const char * full_directory, const char * file_name, void * pSession);
      int FTPD_SendFileToClient(const char * full_directory, const char * file_name, void * pSession, int fd);
      int FTPD_AbleToCreateFile(const char * full_directory, const char * file_name, void * pSession); 
      int FTPD_GetFileFromClient(const char * full_directory, const char * file_name, void * pSession, int fd);
      int FTPD_ListFile(const char * current_directory, void * pSession, FTPDCallBackReportFunct * pFunc, int handle);
   */
   int FTPD_Rename( const char *current_directory,
                        const char *cur_file_name,
                        const char *new_file_name,
                        void *pSession );





   /*User supplied function that lists all files in the current directory */
   /*
   List all files in the current directory.  This function must be implemented by the programmer.
   Parameters:
         const char * current_directory The current value of the session directory
      void * pSession The void * object returned from the FTPBSessionStart( ) function call
      FTPDCallBackReportFunct * pFunc The pointer to the callback function to be called for each file name. This is a callback function provided and used by the NetBurner internal FTP code. 
      int handle The handle value to be passed back into the pFunc. This is a handle provided and used by the NetBurner internal FTP code.
   Returns:
      FTPD_OK The requested files were listed
      FTPD_FAIL The requested file was not listed
   See Also:
      int FTPD_FileExists(const char * full_directory, const char * file_name, void * pSession);
      int FTPD_SendFileToClient(const char * full_directory, const char * file_name, void * pSession, int fd);
      int FTPD_AbleToCreateFile(const char * full_directory, const char * file_name, void * pSession); 
      int FTPD_GetFileFromClient(const char * full_directory, const char * file_name, void * pSession, int fd);
      int FTPD_DeleteFile(const char * current_directory, const char * file_name, void * pSession);
   Example: 
   Everything inside the callback function stub must be supplied by the programmer. The FTP server will
   automatically call this function and provide values for the function variables. It is the programmer's
   responsibility to to execute pFunc( ) with the provided handle and a pointer to the string representing
   the file name. pFunc( ) must be executed once for each file name.
   In this example, the variables number_of_directories and FileNames[] must be declared and 
   initialized elsewhere in the application program.
   int FTPD_ListFile(const char * current_directory, void * pSession, FTPDCallBackReportFunct * pFunc, int handle);
   {
      for (int n = 0; n < numberof_files; n++)
         pFunc(handle, FileNames[n]);
      return FTPD_OK;
   }
   */
   int FTPD_ListFile( const char *current_directory,
                      void *pSession,
                      FTPDCallBackReportFunct *pFunc,
                      int handle );




#ifdef __cplusplus
}
#endif

#endif


