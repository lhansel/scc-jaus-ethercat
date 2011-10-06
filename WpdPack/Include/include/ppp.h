/* Rev:$Revision: 1.11 $ */  

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
/* Definitions for various IP definitions and structures. */
#ifndef _NB_PPP_H
#define _NB_PPP_H

#ifndef NB_NET_TYPES_H
#include "nettypes.h"
#endif

#ifndef _NB_BUFFERS_H
#include "buffers.h"
#endif


#ifdef __cplusplus
extern "C"
{
#endif


   struct pppoptions
   {
         BYTE Restart_Interval; /* The restart interval for PPP Negotiations IN SECONDS!*/
         BYTE Max_Terminate; /*The Maximum number of times to send terminate */
         BYTE Max_Configure;/*The Maximum number of times to send config requests*/
         BYTE Max_Failure;/*The Maximum number of config failures */
         BOOL CHAPenable;  //If TRUE then CHAP will be required for connection
         /*IF you require authentication from the peer then pass in the function to */
         /*call for authentication. A non zero value means the passed in name,password is ok */
         BOOL Chat_Login_disable;  //If TRUE then ppp will not allow Chat_Login mode to occur
         int  ( *authenticate_func )( const char *name, const char *passwd );
         const char *pUserName;            // Used for PAP autentication
         const char *pPassword;            // Used for PAP autentication
         IPADDR SetThisInterfaceAddress; /* Set to zero to require the other side to provide */
         IPADDR SetThatInterfaceAddress; /* Set to non zero to provide an address for the other side */
         IPADDR ActualThisInterfaceAddress; 
         IPADDR ActualThatInterfaceAddress;

         DWORD dwflags;
         WORD MRU;
         DWORD TX_ACCM;
         DWORD RX_ACCM;

         DWORD TX_DESIRED_ACCM; /* Set to any additional ACCM vaues you want to use */
         DWORD RX_DESIRED_ACCM; /* Set to any additional ACCM vaues you want to use */
   };

   typedef enum { eClosed,
                  eInitializingModem,
                  eDialing,
                  eWait4Ring,
                  eAnswering,
                  eWaitForTrain,
                  eLCPNegotiate,
                  ePAPAuthenticate,
                  eCHAPAuthenticate,
                  eNCPNegotiate,
                  eOpen,
                  eClosing }enum_PPPState;

   /*******************************************************************
   *
   *    This function starts the PPP dameon
   *   serial_port is the serial port number.
   *   pppoptions is used to set the configurable PPP options.
   *   
   *******************************************************************/
   int StartPPPDameon( int serial_port, pppoptions *popt );
   int StartPPPDirect( int serial_port, pppoptions *popt );

#define ERR_PPP_SUCCESS (0)
#define ERR_PPP_ALREADY_OPEN (-1)
#define ERR_PPP_NO_DIALTONE (-2)
#define ERR_PPP_NO_ANSWER   (-3)
#define ERR_PPP_BUSY (-4)
#define ERR_PPP_FAIL  (-5)
#define ERR_PPP_PASSFAIL (-6)
#define ERR_PPP_LOSTCARRIER (-7)
#define ERR_PPP_NO_MODEM (-8)
#define ERR_PPP_LCP_FAILED (-9)
#define ERR_PPP_CHAPFAIL (-10)

/* Stop the PPP dameon */
void StopPPPDameon();

int DialPPP( int serial_port, pppoptions *popt, const char *dial_string );
int DirectConnectPPP( int serial_port, pppoptions *popt, const char *dial_string );
enum_PPPState GetPPPState();
void ClosePPPSesion();

IPADDR GetThatPPP_IP(); 
IPADDR GetThisPPP_IP(); 

void SendCHAPChallenge();

extern volatile DWORD PPP_BAUDRATE_TO_USE;
extern volatile BOOL PPP_SW_RX_FLOW;
extern volatile BOOL PPP_SW_TX_FLOW;
extern const char* MODEM_INITSTRING; 
extern const char* MODEM_ENDCMDMODE;
extern const char* MODEM_POSTDIAL;
extern const char* MODEM_ATTNSTRING;
extern const char* MODEM_AUTOBAUD;
extern const char* MODEM_RESET;
extern const char* MODEM_ANSWER;
extern const char* MODEM_HANGSTRING;

#ifdef __cplusplus
}
#endif
#endif

