/* Rev:$Revision: 1.7 $ */  

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

#ifndef _POP3_H_
#define _POP3_H_

#ifdef __cplusplus
extern "C"
{
#endif
#define POP_OK            (0)
#define POP_TIMEOUT       (-1)
#define POP_PASSWORDERROR (-2)
#define POP_CONNECTFAIL   (-3)
#define POP_COMMANDFAIL   (-4)
#define POP_BADSESSION    (-5)
#define POP_NETWORKERROR  (-6)
#define POP_BUFFER_FULL	  (-7)


   /*Module: POP3 Client.
   This Module provides code for reading and managing mail from A POP# server.
   POP3 is defined in the document RFC1939
   */

   /*Functions:*/
   /*Group:Initialization function*/

   /* Initalize the pop3 network connection. */
   /*
   This call makes the connection to the POP server and logs in 
   with the username and password.
   Parameters:
      IPADDR server_address The IP address of the server.
      WORD port The Port to connect to on the server.
      PCSTR UserName The account username.
      PCSTR PassWord The account password.
      DWORD time_out The number of ticks to wait.
      
   Returns:
      Returns:
      int The command success code.
      >0 = Mail session
      POP_TIMEOUT       = Time out
      POP_PASSWORDERROR = Network error.
      POP_CONNECTFAIL   = Password error.
      POP_NETWORKERROR   = Network error.
   */
   /*See Also: POP3_CloseSession(int session);
   */

   int POP3_InitializeSession( IPADDR server_address,
                               WORD port,
                               PCSTR UserName,
                               PCSTR PassWord,
                               DWORD time_out );



   /* Close the pop3 network connection. */
   /*
   Close the session and flush deleted messages  (See RFC1939)
   Returns:
      int The command success code.
      POP_OK Closed successfully
      POP_TIMEOUT       = Time out
      POP_COMMANDFAIL  = Command error.  
      POP_NETWORKERROR   = Network error.
      POP_BADSESSION    = bad session number.
   */
   /*See Also:
      int POP3_InitializeSession(IPADDR server_address, WORD port, PCSTR UserName, PCSTR PassWord, DWORD time_out);  
   */
   int POP3_CloseSession( int session );



   /*Group:POP3 Command functions*/
   /* Get the status of the Mailstore on the pop3 server.*/
   /* Retreives the state of the mail store asociated with this session.
    
   Parameters:
      int session The POP3 session.
      DWORD * num_messages The DWORD variable to hold the number of pending messages.
      DWORD * total_bytes The DWORD variable to hold the total number of bytes in the pending messages.
      DWORD time_out The number of ticks to wait.
      
   Returns:
      int The command success code.
      POP_OK           = Command ok.    
      POP_TIMEOUT     = Time out.         
      POP_COMMANDFAIL  = Command error.  
      POP_NETWORKERROR   = Network error.
      POP_BADSESSION    = bad session number.
   */
   /*See Also: 
      POP3_ListCmd(int session, DWORD message_number, DWORD * total_bytes, DWORD time_out);
      POP3_DeleteCmd(int session,DWORD message_number, DWORD time_out);
      POP3_RetrieveMessage(int session,DWORD message_number, char * buffer, char * subject_ptr, char * body_ptr,int max_bufferlen, DWORD time_out);
   */
   int POP3_StatCmd( int session, DWORD *num_messages, DWORD *total_bytes, DWORD time_out );



   /* Get the size of the specified message.*/
   /* Retreives the size of the message.
    
   Parameters:
      int session The POP3 session.
      DWORD messages_number The message to reterieve the size of the message.
      DWORD * total_bytes The DWORD variable to hold the total number of bytes in the pending messages.
      DWORD time_out The number of ticks to wait.
      
   Returns:
      int The command success code.
      POP_OK           = Command ok.    
      POP_TIMEOUT     = Time out.         
      POP_COMMANDFAIL  = Command error.  
      POP_NETWORKERROR   = Network error.
      POP_BADSESSION    = bad session number.
   */
   /*See Also: POP3_StatCmd(int session, DWORD * num_messages, DWORD * total_bytes, DWORD time_out);
      POP3_DeleteCmd(int session,DWORD message_number, DWORD time_out);
      POP3_RetrieveMessage(int session,DWORD message_number, char * buffer, int max_bufferlen, DWORD time_out);
   */
   int POP3_ListCmd( int session, DWORD message_number, DWORD *total_bytes, DWORD time_out );



   /* Delete a specific message on the server.*/
   /* Deletes a specific message. 
   The message is not actually deleted until the session is closed.
    
   Parameters:
      int session The POP3 session.
      DWORD message_number The message to delete.
      DWORD time_out The number of ticks to wait.
      
   Returns:
      int The command success code.
      POP_OK           = Command ok.    
      POP_TIMEOUT     = Time out.         
      POP_COMMANDFAIL  = Command error.  
      POP_NETWORKERROR   = Network error.
      POP_BADSESSION    = bad session number.
   */
   /*See Also: POP3_ListCmd(int session); 
      POP3_StatCmd(int session, DWORD * num_messages, DWORD * total_bytes, DWORD time_out);
      POP3_RetrieveMessage(int session,DWORD message_number, char * buffer, char * subject_ptr, char * body_ptr,int max_bufferlen, DWORD time_out);
   */
   int POP3_DeleteCmd( int session, DWORD message_number, DWORD time_out );



   /* Reterieve a specific message from the server.*/
   /* Reterieve a specific message. 
   The message is left on the server and will not
   be deleted until you call POPs_DeleteCmd.
    
    The message is reterieved as a large block with all of the headers first.
   Parameters:
      int session The POP3 session.
      DWORD message_number The message to reterieve.
      char * buffer The buffer to hold the message.
      char ** subject_ptr If not null the char pointer will be left pointing at the message subject.
      char ** body_ptr If not null the char pointer will be left pointing at the message body.
      int max_bufferlen The maximum size of the rereived message.
      DWORD time_out The number of ticks to wait.
   Returns:
      int The command success code.
       >0 = length of the message reterieved.
      POP_TIMEOUT     = Time out.         
      POP_COMMANDFAIL  = Command error.  
      POP_NETWORKERROR   = Network error.
      POP_BADSESSION    = bad session number.
   */
   /*See Also: POP3_ListCmd(int session); 
      POP3_StatCmd(int session, DWORD * num_messages, DWORD * total_bytes, DWORD time_out);
      POP3_DeleteCmd(int session,DWORD message_number,DWORD time_out);
   */
   int POP3_RetrieveMessage( int session,
                             DWORD message_number,
                             char *buffer,
                             char **subject_ptr,
                             char **body_ptr,
                             int max_bufferlen,
                             DWORD time_out );


   /* Returns the Error text for a specific code.*/
   /* Returns the Error text for a specific code.
   This only works for POP3 errors
    
   Parameters:
      int err the Error code.
      
   Returns:
      PCSTR the text string
   */
   /*See Also: POP3_ListCmd(int session); 
      POP3_StatCmd(int session, DWORD * num_messages, DWORD * total_bytes, DWORD time_out);
      POP3_RetrieveMessage(int session,DWORD message_number, char * buffer, char * subject_ptr, char * body_ptr,int max_bufferlen, DWORD time_out);
      POP3_InitializeSession(IPADDR server_address, WORD port, PCSTR UserName, PCSTR PassWord, DWORD time_out);  
   */
   PCSTR GetPOPErrorString( int err );


   /*Module Example:
   .
   .
   .
   #include <pop3.h>
   #include <dns.h>
   .
   .
   #define USERID "username"
   #define USERPASS "password"
   #define SERVERNAME "pop.yourserver.com"
   #define POP_PORT (110)
   int StartSession()
   {
   IPADDR srvr_addr;
   if (GetHostByName(SERVERNAME, &srvr_addr,0,TICKS_PER_SECOND*10)==DNS_OK)
    {
     printf("Got Server IP = ");  ShowIP(srvr_addr);  printf("\r\n");
     // Create the POP 3 session with the server 
     int  session=POP3_InitializeSession(srvr_addr,POP_PORT,USERID,USERPASS,TICKS_PER_SECOND*10);  
     return session;
    }
   else
   { 
    printf("Failed to get Server IP Address\n");
    return 0;
   }
   }
   #define MSG_BUF_SIZ (16000)
   static char messagebuffer[MSG_BUF_SIZ];
   void GetMessages()
   {
   DWORD num_mess;
   DWORD num_bytes;
   int session=StartSession();
   if (session>0)
   {
    int rv=POP3_StatCmd(session, &num_mess, &num_bytes, 10*TICKS_PER_SECOND);
    if (rv==POP_OK)
    {
     printf("The server has %ld messages and %ld bytes\r\n",num_mess, num_bytes);
     if (num_mess==0) return;
     for (DWORD nmsg=1; nmsg<=num_mess; nmsg++)
      {
      char * psub;
      char * pbody;
      DWORD predict_size;
      rv=POP3_ListCmd(session,nmsg, &predict_size,TICKS_PER_SECOND*10);
      printf("Predicted message size is %ld\r\n",predict_size);
      rv=POP3_RetrieveMessage(session,nmsg,messagebuffer,&psub,&pbody,MSG_BUF_SIZ-1,TICKS_PER_SECOND*20); 
      if (rv>0)
       {
        printf("Received a message of %d bytes\r\n",rv);
        messagebuffer[rv]=0;
        if (pbody)
         {
          printf("Body Size %ld\r\n,<Start of Message:>\r\n %s\r\n<End of Message>\r\n",strlen(pbody),pbody);
         }
         else
         {
          printf("Unable to locate body.\r\nPrinting the entire message \r\n<Start of Message:>\r\n %s\r\n<End of Message>\r\n",pbody);
         }
        char c;
        do
        {
        printf("Delete this message (Y/N?)");
        c=toupper(getchar());
        }
        while ((c!='N') && (c!='Y'));
       if (c=='Y')
        {
         rv=POP3_DeleteCmd(session,nmsg,TICKS_PER_SECOND*10);
         if (rv==POP_OK) printf("Message deleted\r\n");
         else
          printf("Delete command processing failed with error:%s\r\n",GetPOPErrorString(rv)); 
        }
        else
        printf("Message not deleted\r\n");
       }
      else
        printf("Reterive command processing failed with error:%s\r\n",GetPOPErrorString(rv)); 
      }
    }
    else
    {
     printf("STAT command processing failed with error:%s\r\n",GetPOPErrorString(rv)); 
    }
   POP3_CloseSession(session); 
   }
   else
   {
     printf("Failed to create session with error:%s\r\n",GetPOPErrorString(session));
   }
   }
   */



#ifdef __cplusplus
}
#endif


#endif



