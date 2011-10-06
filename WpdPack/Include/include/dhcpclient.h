/* Rev:$Revision: 1.17 $ */  

/******************************************************************************
 *
 * Copyright 1999-2002 NetBurner  ALL RIGHTS RESERVED
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
 * San Diego Ca, 92131
 *
 * information available at:  http://www.netburner.com
 * E-Mail info@netburner.com
 *
 * Support is availible: E-Mail support@netburner.com
 *
 *****************************************************************************/

#ifndef _NB_DHCP_CLIENT_H
#define _NB_DHCP_CLIENT_H

#ifndef _UCOS_H
#include <ucos.h>
#endif


/* Module: DHCP Client
   This Module provides a DHCP client to dynamically get IP configuration parameters 
   using the RFC1541 DHCP protocol. To use this module you must call the StartDHCP(); 
   function after the IP stack is initialized. 
*/

// Functions necessary to use DHCP in the simplest form 
#define DHCP_OK (0)
#define DHCP_NOTNEEDED (1)
#define DHCP_FAILED (-1)


//----- DHCP states -----
#define SDHCP_NOTSTARTED     0   // The System has not been initialized
#define SDHCP_DISCOVER       1   // The system is discovering the DHCP servers
#define SDHCP_OFFER          2   // The system has responded to an OFFER
#define SDHCP_ACK            3   // The System has Acknowledged the OFFER
#define SDHCP_INIT           4   // The System is reinitalzing
#define SDHCP_CMPL           5   // The System has obtained a valid DHCP lease
#define SDHCP_RENEW          6   // The System is in the procecess of renewing
#define SDHCP_REBIND         7   // The System has failed the Renew and is trying to Rebind
#define SDHCP_RELEASE        8   // The System is trying to release the Lease
#define SBOOTP_TRANSMITTING  9   // Trying BOOTP
#define SBOOTP_DONE         10   // BOOTP complete
#define SDHCP_FAILED        11   // DHCP attempt failed - could not obtain a DHCP lease


class DHCPMessage; //Forward declaration 

class DhcpObject
{
   private:
      int DhcpState; // Current state of DHCP engine
      int DhcpRetryCount; // Number of transmit retries.
      int DhcpTimeCounter;//Number of seconds til retry
      DWORD DHCPLastXid; //Last XID 
      int DhcpBackoffTimer;
      volatile int DhcpPendingPacket;
      DWORD DhcpLeasePendingStart;     // IP address lease start time in seconds
      DWORD DhcpLeaseDuration;  // Relative duration of lease in seconds

      void CreateDhcpRenewMsg( DHCPMessage &NewMsg );
      void CreateDhcpReleaseMsg( DHCPMessage &NewMsg );
      BOOLEAN BootpConfig( DHCPMessage &Msg );
      BOOLEAN DhcpConfig( DHCPMessage &Msg );
      void UpdateIPRuntimeVars( BOOLEAN release ); 
      void ReTransmitPacket( DWORD xid = 0 ); 
      void CreateBootpMsg( DHCPMessage &NewMsg ); 

      BOOL bProcessThisDhcp;
      DhcpObject *m_next_in_list;

   public:
      IPADDR DhcpClientIP;    // Allocated IP address
      IPADDR DhcpClientMask;     // Allocated subnet mask
      IPADDR DhcpServerIP;    // Server ID
      IPADDR DhcpRelayIP;     // Relay Agent
      IPADDR DhcpRouterIP;    // Gateway IP
      IPADDR DhcpDNSIP;    // DNS IP
      volatile DWORD DhcpLeaseTimer;   // Tracks current lease time
      DWORD DhcpLeaseStart;      // IP address lease start time in seconds
      DWORD DhcpLeaseTime;    // IP address lease time in seconds
      DWORD DhcpRenewTime;    // Time to Renewing state in seconds
      DWORD DhcpRebindTime;      // Time to Rebinding state in seconds
      int DhcpInterface;      // Interface to use
      OS_SEM NotifySem;


      /*Functions:*/
      /*Group:DHCP operational functions*/


      /*Start the DHCP client */
      /* This function will start the DHCP process. 
      It will return immediatly and you need to either watch the semaphore ,
      or monitor the status of DHCP using GetDHCPState(); 
      before you assume that the IP address has been setup. 
      Parameters:
         OS_SEM * pDhcpSemaphore A pointer to a Semaphore to notify when DHCP is complete. IT may be passed in as Null
      */
      /*Example:
      #include <dhcpclient.h>
      *
      *
      *
      {
      OS_SEM DHCPSem;
      OSSemInit(&DHCPSem,0);//Initialize the Semaphore 
      StartDHCP(&DHCPSem); //Start DHCP
      if (OSSemPend(&dhcpSem,20*TICKS_PER_SECOND)==OS_TIMEOUT) //Wait 20 seconds
         {//DHCP did not initialize handle the error here
         }
      */

      // See Also: StopDHCP(); GetDHCPState();
      void StartDHCP();

      // Start the BOOTP process 
      void StartBOOTP();

      // After BOOTP has failed call this to stop BOOTP processing
      void StopBOOTP();

      // Stop the DHCP client and Release any DHCP leases we own
      void StopDHCP();

      // Force a DHCP Renew 
      void RenewDHCP();

      // Force a DHCP Rebind
      void RebindDHCP();

      // Returns TRUE (1) if lease is valid, FALSE (0) if lease is invalid
      BOOL ValidDhcpLease();

      // Returns number of seconds remaining for current lease
      DWORD GetRemainingDhcpLeaseTime();

      // Returns time at which a renew will occur in seconds
      DWORD GetDhcpRenewTime() { return DhcpRenewTime; }

      // Returns time at which a rebind will occur in seconds
      DWORD GetDhcpRebindTime() { return DhcpRebindTime; }

      // Returns time at which a lease will expire in seconds
      DWORD GetDhcpExpirationTime() { return DhcpLeaseTime; }

      /* Group:DHCP status reporting functions
         Get the current DHCP State 
      Returns:
         SDHCP_DISCOVER The system is discovering the DHCP servers. 
         SDHCP_OFFER    The system has responded to an OFFER.             
         SDHCP_ACK      The System has Acknowledged the OFFER.              
         SDHCP_INIT     The System is reinitalzing.               
         SDHCP_CMPL     The System has completed the last transaction.              
         SDHCP_RENEW    The System is in the procecess of renewing.             
         SDHCP_REBIND   The System has failed the Renew and is trying to Rebind.           
         SDHCP_RELEASE  The System is trying to release the Lease.            
         SDHCP_NOTSTARTED The System has not been initialized.      
         SBOOTP_TRANSMITTING   Trying Bootp 
         SBOOTP_DONE       Done with Bootp     
      */
      int GetDHCPState();

      //---- function prototypes -----
      void PrintDhcpState( int state );

      void DHCPTimer(); 
      void DHCPPacket( PoolPtr p );

      static void staticDHCPPacket( PoolPtr p );
      static void staticDHCPTimer(); 

      void StopProcessing();

      DhcpObject( int interface = 0 );
      ~DhcpObject();

#ifdef DHCP_DEBUG
      friend void PrintDhcpStatus( DhcpObject &dob );
      friend void PrintDhcpState( int state );
#endif



}; //End of DHCP Object


// Point this at a valid text string to register this DHCP name 
extern const char *pDHCPOfferName;



// Return DHCP OK if it was able to setup the system addresses via DHCP 
int GetDHCPAddress( int interface = 0 );



/*------------------------------------------------------------------- 
   Check the network inteface for a static IP address. Use DHCP if
   the static IP is 0.0.0.0. This function will print the result of
   IP address selection to stdout unless "boot quiet" has been selected
   in the boot options through IPSetup or the boot monitor "setup"
   menu. By default, stdout is serial port UART0. 

   Arguments
   int ifc - This is the interface number, ranging from 0 to 2. An 
             interface number is returned by functions such as
             GetFirstInterface(), GetNextInterface() and AddWiFiInterface().
   
   Return Values 
   DHCP_NOTNEEDED - A static IP address has been configured
   DHCP_OK        - A DHCP address was obtained from a DHCP server
   DHCP_FAILED    - A DHCP address is required, but a DHCP server could
                    not be contacted.
                    
   Examples:
      GetDHCPAddressIfNecessary()   // operates on first interface
      GetDHCPAddressIfNecessary(WiFiInterface)   // operates on WiFi interface
 --------------------------------------------------------------------*/
int GetDHCPAddressIfNecessary( int interface = 0 );




/* Set the number of second to be advertised when trying to get a DHCP address */
void SetDHCPDiscoverSeconds(DWORD secs);



#endif
