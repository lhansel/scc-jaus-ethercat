/* Rev:$Revision: 1.14 $ */  

#ifndef _NB_MAILTO
#define _NB_MAILTO
/******************************************************************************
 *
 * Copyright 1998-2008 NetBurner  ALL RIGHTS RESERVED
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
 * 5405 Morehouse Dr
 * San Diego Ca, 92121
 *
 * http://www.netburner.com
 *****************************************************************************/


/*Returns 0 on Failure, 1 on success.*/
int SendMail( IPADDR smtp_server, /*IP address of the smtp server */
              PCSTR userid, /*AscII String to provide for RFC931 IDentification */
              PCSTR from_addr, /*From E-Mail address */
              PCSTR to_addr, /*To E-Mail Address */
              PCSTR subject, /*E-Mail subject */
              PCSTR textbody    /* E-Mail body */ );


/*Returns 0 on Failure, 1 on success.*/
int SendMailAuth( IPADDR smtp_server, /*IP address of the smtp server */
				  PCSTR userid, /*AscII String to provide for RFC931 IDentification */
              PCSTR pass, /*AscII String to provide for AUTH IDentification */
              PCSTR from_addr, /*From E-Mail address */
              PCSTR to_addr, /*To E-Mail Address */
              PCSTR subject, /*E-Mail subject */
              PCSTR textbody    /* E-Mail body */ );



/* from_addr_rev_path = From E-Mail Addr - RFC 821 <reverse-path>
   from_addr_memo_hdr = From E-Mail Addr - RFC 821 memo header
*/
int SendMailEx( IPADDR smtp_server,
                PCSTR userid,
                PCSTR from_addr_rev_path,
                PCSTR from_addr_memo_hdr,
                PCSTR to_addr,
                PCSTR subject,
                PCSTR textbody );
					 
					 
int SendMailAsServer( PCSTR from_addr,
							 PCSTR to_addr,
                      PCSTR subject,
                      PCSTR textbody );

extern WORD SMTP_PORT;
extern WORD RFC931_PORT;
extern WORD LOCAL_MAIL_PORT;

/* 
The following functions, variables and definitions are used for 
error reporting of the mail system.
*/
//Returns 0 if mail sent correctly else error code
int IsMailError();
// Prints NB Error string of last mail transaction to FD or stdio if parameter not included
void PrintNBError( int FDout = 0 );
// Prints Server Log of last mail transaction to FD or stdio if parameter not included
void PrintServerLog( int FDout = 0 );

extern int NB_Mail_Error_Code;
extern char NB_Mail_Error_String[];
extern char Server_Mail_Log_String[];

#define STATUS_OK                      (0)
#define CONNECT_TO_SMTP_SERVER_FAILED  (-1)
#define INITIAL_SERVER_REPLY_FAILED    (-2)
#define HELO_SERVER_REPLY_FAILED       (-3)
#define MAIL_FROM_SERVER_REPLY_FAILED  (-4)
#define RCPT_TO_SERVER_REPLY_FAILED    (-5)
#define DATA_SERVER_REPLY_FAILED       (-6)
#define DATA_END_SERVER_REPLY_FAILED   (-7)
#define AUTH_LOGIN_SERVER_REPLY_FAILED (-8)
#define USER_ID_SERVER_REPLY_FAILED    (-9)
#define PASSWORD_SERVER_REPLY_FAILED   (-10)
#define CONNECT931_SMTP_SERVER_FAILED  (-11)


// MIME Content Types
extern enum CONTENT_TYPE_ENUM
{
	CONTENT_TYPE_PLAIN_TEXT,
	CONTENT_TYPE_PLAIN_TEXT_ATTACH,
	CONTENT_TYPE_BINARY_ATTACH,
	// Add additional types above CONTENT_TYPE_END
	CONTENT_TYPE_END
} CONTENT_TYPE;

/* Functions for MIME multipart messages.
 * To send a MIME multipart message:
 * - Call SendMaiAuthStartMIME() to initiate the session,
 *   which will leave the socket, fd, open.
 * - Call SendMailAuthAddMIME() to add each MIME part of your message.
 * - Call SendMailAuthEndMIME() to close the session and send the message.
 * 
 */
extern int SendMailAuthStartMIME( IPADDR smtp_server, PCSTR userid, PCSTR pass, 
                                  PCSTR from_addr, PCSTR to_addr, PCSTR subject, int &fd );
extern int SendMailAuthAddMIME( int fd, int ContentType, const char *pContent, const char *FileName );
extern int SendMailAuthEndMIME( int fd, PCSTR userid );


#endif
