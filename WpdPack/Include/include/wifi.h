/* $Revision: 1.16 $ */
/* Copyright $Date: 2009/08/31 18:10:52 $ */  

/******************************************************************************
 *
 * Copyright 1998-2009 NetBurner, Inc.  ALL RIGHTS RESERVED
 *   Permission is hereby granted to purchasers of NetBurner Hardware
 *   to use or modify this computer program for any use as long as the
 *   resultant program is only executed on NetBurner provided hardware.
 *
 *   No other rights to use this program or its derivatives in part or
 *   in whole are granted.
 *
 *   It may be possible to license this or other NetBurner software for
 *   use on non-NetBurner Hardware.
 *   Please contact sales@Netburner.com for more information.
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

#ifndef _WIFI_H
#define _WIFI_H
/*
 *****************************************************************************
 *
 * Include files
 *
 *****************************************************************************
 */
#include <device.h> 
#include <netDevice.h> 
#include <qspiShared.h> 

/******************************************************************************
 *
 * ***  Legacy controllers removed intentionally 2009/06/18 ***
 *          Intersil PRISM 2
 *          NXP BGW211g
 *
 ******************************************************************************
 */
 
/* 
   Wodule shares the (Q)SPI with SD/MMC at default installation
      Uncommenting NB_ENABLE_USER_QSPI in predefs.h changes the driver
      to the user (Q)SPI driver defined in qspi.h and does not then support
      using the SD/MMC and WLAN in the same system.
      
      predef.h must precede this include file.
      
*/
#ifdef _PREDEF_H_
   #ifndef NB_ENABLE_USER_QSPI   
      #define WIFI_SHARES_SPI    ( 1 )
   #endif /* #ifndef NB_ENABLE_USER_QSPI    */
#else /* #ifndef _PREDEF_H_ */
   #error predef.h must be included before wifi.h is included
#endif /* #ifndef _PREDEF_H_ */

/* 
   Uncomment WIFI_USES_PRISM2 if using this interface and rebuild all libraries, 
   else it uses the RTL8711 module
*/
/* #define WIFI_USES_PRISM2   1 */

/*
 ******************************************************************************
 *
 * Constants
 *
 ******************************************************************************
 */
/*
   TCP/IP maximum segment size (MSS) supported by the interface
   
      DO NOT MODIFY
         RTL8711  -  ETH_MAX_SIZE - TCPTOTAL_HEADER_SIZE - 30
         
      Note: For RTL8711 the smaller size was determined empirically from the
         firmware. Above that size the module crashes. ???
      
 */ 
#define WIFI_MSS              ( 1400 )
 
/*
   Regulatory Domains
   
      WIFI_DOMAIN_AMERICAS          - FCC
      WIFI_DOMAIN_EMEA              - Europe, the Middle East and Africa
      WIFI_DOMAIN_JAPAN             - Japan
      WIFI_DOMAIN_WORLD             - Rest of world
      
      One set must match use domain
   
*/
#define WIFI_DOMAIN_AMERICAS        ( 1 ) 
/* #define WIFI_DOMAIN_EMEA            ( 1 ) */
/* #define WIFI_DOMAIN_JAPAN           ( 1 ) */
/* #define WIFI_DOMAIN_WORLD           ( 1 ) */
 
 
/*
   WiFi Parameter Sizes
   
      WIFI_MAC_SIZE_IN_WORDS     - Media Access Control (MAC) address size in 
                                    16bit words (IEEE 802.3)
      WIFI_SSID_SIZE_IN_BYTES    - Service Set Identity (SSID) size maximum in 
                                    8 bit characters (IEEE 802.11)
      WIFI_WEP_KEY_SIZE_MAX      - Wired Equivalent Privacy (WEP) key size in
                                    8 bit characters maximum (IEEE 802.11),
                                    hexadecimal encoded characters 
                                    ('0'-'9', 'A'-'F')
                                       WEP 64  - 10 
                                       WEP 128 - 26
      WIFI_SCAN_STATION_MAXIMUM  - Maximum number of stations in the scan 
   
*/
#define WIFI_MAC_SIZE_IN_WORDS         ( 3 )
#define WIFI_SSID_SIZE_IN_BYTES_MAX    ( 32 )
#define WIFI_WEP_KEY_SIZE_MAX          ( 26 )
#define WIFI_WEP_64_KEY_SIZE           ( 10 )
#define WIFI_WEP_104_KEY_SIZE          ( 26 )
#define WIFI_SCAN_STATION_MAXIMUM      ( 32 )
#define WIFI_BINARY_KEY_LENGTH_MAX     ( 16 )
   
/*
   Security settings
      WIFI_SECURITY_NONE            - None
      WIFI_SECURITY_WEP_40          - WEP 40 bit key
      WIFI_SECURITY_TKIP            - Temporal Key Integrity Protocol
      WIFI_SECURITY_TKIP_WTMIC      - RTL8711 Legacy
      WIFI_SECURITY_AES             - WPA2 802.11i
      WIFI_SECURITY_WEP_104         - WEP 104 bit key
      
      Note: TKIP used in Wi-Fi(tm) Protected Access (WPA), AES in WPA2
      
 */
#define WIFI_SECURITY_NONE             ( 0x0 )
#define WIFI_SECURITY_WEP_40           ( 0x1 )
#define WIFI_SECURITY_TKIP             ( 0x2 )
#define WIFI_SECURITY_TKIP_WTMIC       ( 0x3 )
#define WIFI_SECURITY_AES              ( 0x4 )
#define WIFI_SECURITY_WEP_104          ( 0x5 )
       
/* 
   AddWiFiInterface* Returns
   
      WIFI_REQUEST_FAILED        - Was not added by the system
      WIFI_MODULE_NOT_FOUND      - Module not detected
      WIFI_ALREADY_EXISTS        - Already exists
      WIFI_SUPPORT_TASK_FAILED   - Driver task not created
      WIFI_UNSUPPORTED_OPTION    - Either IRQ, controller or bus not supported

*/

#define WIFI_REQUEST_FAILED         (  0 )
#define WIFI_MODULE_NOT_FOUND       ( -1 )
#define WIFI_ALREADY_EXISTS         ( -2 )
#define WIFI_SUPPORT_TASK_FAILED    ( -3 )
#define WIFI_UNSUPPORTED_OPTION     ( -4 )

/* 
   Wifi Activity Values
   
      WIFI_NO_ACTIVITY           - None
      WIFI_CHATTER               - Interesting information in details
      WIFI_INITIALIZING          - Setting up interface
      WIFI_DOWNLOADING           - Downloading firmware and settings
      WIFI_SURVEYING             - Surveying wireless sites
      WIFI_CONNECTING            - Connection attempt
      WIFI_DISCONNECTED          - Disconnect by the access point
      

*/

#define WIFI_NO_ACTIVITY            (  0 )
#define WIFI_CHATTER                (  1 )
#define WIFI_INITIALIZING           (  2 )
#define WIFI_DOWNLOADING            (  3 )
#define WIFI_SURVEYING              (  4 )
#define WIFI_CONNECTING             (  5 )
#define WIFI_DISCONNECTED           (  6 )

/*
 ******************************************************************************
 *
 * Enumerations
 *
 ******************************************************************************
 */
/*
   Security algorithm
       NoSecurity       - None
       WEP              - Wired Equivalent Privacy (WAP)
       WPA              - Wi-Fi(R) Protected Access (WPA) IEEE 802.11i
       WPA2             - Wi-Fi(R) Protected Access (WPA) WAP with AES
       
 */
typedef enum _WifiSecurityAlgorithm
{
   NoSecurity,
   WEP,
   WPA,
   WPA2

} WifiSecurityAlgorithm;

/*
 ******************************************************************************
 *
 * Structures
 *
 ******************************************************************************
 */
 
/* 
 ******************************************************************************
 
   Scan Results
   
      anl         - Signal level in - dbm less negative is better
      sl          - Connected Signal level in - dbm less negative is better
      HostMac     - MAC address of advertising access point
      SSID        - Network name
      Rate        - Probe rate in MBPS * 10
      security    - Encryption type
      quality     - Quality of signal out of 100
      channel     - Channel
      
 ******************************************************************************
 */
typedef struct _WifiScanResult
{
   int anl;
   int sl;
   WORD HostMac[ WIFI_MAC_SIZE_IN_WORDS ];
   char SSID[ WIFI_SSID_SIZE_IN_BYTES_MAX ];
   WORD Rate;
   DWORD security;
   DWORD quality;
   DWORD channel;
   
} WifiScanResult;

/*
 ******************************************************************************
 *
 * Runtime Libraries Routine Prototypes
 *
 ******************************************************************************
 */
 
/* 
 ******************************************************************************
 
   Initialize the Wireless Interface specifying SSID and WEP
    
      Parameters:
         SSID        - Service Set Identity (SSID) is "wireless network name" 
                           Access Point (AP) or Station (STA) to attach to, 
                           NULL use configuration record for SSID and WEP_Key
         WEP_Key     - Wired Equivalent Privacy (WEP) is mechanism for 
                           authentication using key shared with 
                           access point (AP) or peer
                              Example:
                                 WEP 40 "0c4bb8a23f" or 
                                 WEP 128 "0c4bb8a23f8da600f3469a1233" or
                                 NULL use configuration record for both
         adhoc       - TRUE for adhoc network, FALSE for infrastructure.
         irq         - Fixed level interrupt source
         controller  - IEEE 802.11g controller
         busType     - Bus used by the controller
         select      - Chip select is controller and bus specific
                        SDIO using SPI mode (BusTypeSdioBusSpiMode)
                           (Q)SPI chip select lines QSPI_CS[0:3]
                           See QSPI_CHIP_SELECT_N in qspiShared.h
         selectDetail   - See SelectDetail... defined in netDevice.h                  
         
      Return:
         > 0 interface number ( 1 through MAX_INTERFACES ), 
         <= 0 see WIFI_ definitions above
         
       Notes:
         (Q)SPI chip selects vary by module QSPI_CS1 is available on all
         
         Sharing the (Q)SPI with other SPI devices like the SD/MMC and Compact
         Flash card is supported by default on the MOD-DEV-100 and the Micro
         SD/MMC on the SB700.
         
         For sharing with others see the documentation for the shared (Q)SPI.
         
         
 ******************************************************************************
 */
int AddWiFiInterfacewName( const char *SSID, const char *WEP_Key, 
      BOOL adhoc = FALSE, int irq = 3, 
      NetDeviceController controller = ControllerRealtekRtl8711,
      NetDeviceBusType busType = BusTypeSdioBusSpiMode, 
      int select = QSPI_CHIP_SELECT_1,
      NetDeviceSelectDetail selectDetail = SelectDetailSpiUnmanaged );

/* 
 ******************************************************************************
 
   Initialize the Wireless Interface using stored configuration parameters and
      default parameters used above.

      Parameters:
         adhoc    - TRUE for adhoc network, FALSE for infrastructure.

      Return:
         > 0 interface number, < 0 set WIFI_ definitions above
         
 ******************************************************************************
 */
int AddWiFiInterface( BOOL adhoc = FALSE );


/* 
 ******************************************************************************
 
   Attached to a specific Wireless access point
   
      Parameters:
         SSID        - Network name to connect to, NULL for any network.
         WEP_Key     - Security key 
                           Example WEP 40 "0c4bb8a23f" or 
                           WEP 128 "0c4bb8a23f8da600f3469a1233" or
                           NULL for no WEP key.
         useDefault  -     TRUE to use configuration record
         
      Return:
         TRUE - Attached, FALSE - Problems
         
      Notes:
         SSID and WEP_KEY setting override configuration record settings but
         do not replace them permanently.
         
      Notes:
         (1) NULL SSID will attach to the AP (peer if adhoc) with the 
            strongest signal level during the connect scan that will allow it.
         (2) NULL WEP_Key will only allow attachment according to the SSID to
            an AP (or peer if adhoc) that has wired equivalency privacy 
            disabled.            
            
 ******************************************************************************
 */
BOOL WiFiAttachTo( const char *SSID, const char *WEP_Key, 
      BOOL useDefault = FALSE );

/* 
 ******************************************************************************
 
   Find what devices are out there
    
      Parameters:
         sitePtr        - SSID of site of interest, else NULL
         
      Return:
         List of access points, last with a SSID starting with '\0'.
         
 ******************************************************************************
 */
WifiScanResult* WiFiScanForAP( char* sitePtr = NULL );

/* 
 ******************************************************************************
 
   Print using iprint interface list of access points in last scan 

      Parameters:
         sitePtr        - SSID of site of interest, else NULL
         
      Return:
         None
         
 ******************************************************************************
 */
void WiFiShowScanForAP( char* sitePtr = NULL );

/* 
 ******************************************************************************
 
   Is WiFi connected to AP or STA
    
      Parameters:
         None
         
      Return:
         TRUE - Connected, FALSE - Disconnected
         
 ******************************************************************************
 */
BOOL WiFiConnected( void );

/* 
 ******************************************************************************
 
   Get the name of the current SSID connection

      Parameters:
         buffer         - Contains SSID
         maxlen         - Maximum length of buffer

      Return:
         >0 size of SSID in buffer, 0 not connected
         
 ******************************************************************************
 */
int GetCurrentSSID( char *buffer, int maxlen );

/* 
 ******************************************************************************
 
   Get the SSID in the configuration record

      Parameters:
         buffer         - SSID
         maxlen         - Maximum length of buffer, truncated if less than
                           WIFI_SSID_SIZE_IN_BYTES.

      Return:
         >0 size of SSID in buffer, 0 none or invalid record
         
 ******************************************************************************
 */
int GetWiFiConfigurationSSID( char *buffer, int maxlen );

/* 
 ******************************************************************************
 
   Get the WEP key in the configuration record

      Parameters:
         buffer         - WEP key, hexadecimal encoded bytes
         maxlen         - Maximum length of buffer, truncated if less than
                           WIFI_WEP_KEY_SIZE_MAX.

      Return:
         >0 size of WEP key in buffer, 0 none or invalid record
            WEP 64 is 10, WEP 128 -s 26 
         
 ******************************************************************************
 */
int GetWiFiConfigurationWEPKey( char *buffer, int maxlen );

/* 
 ******************************************************************************
 
   Setup the WiFi configuration over the serial port
      
      Prompts for SSID, WEP , IP address etc....
      This is the WiFi equivalent to the SetupDialog(); call from system.h
      
      Parameters:
         None
         
      Return:
         None
         
 ******************************************************************************
 */
void SetupWiFiConfig( void ); 

/* 
 ***************************************************************************
 
   Setup the WiFi callback function for initialization and download
   
      Parameters:
         activity       - Wifi Activity Values above
         progress       - Progress in 1/100ths
         details        - Additional information or NULL
      
      Return:
         None
         
      Notes:
         Starts the activity with progress set to 0, ends with set to 100
         details must be a NULL terminated string.
      
 ***************************************************************************
 */
/*
   Prototype for state change callback
*/
typedef void ( WifiProgressFn )( int activity, int progress, char* details );   
typedef WifiProgressFn* WifiProgressFnPtr;

 
void SetupWifiProgressCallback( WifiProgressFnPtr wifiProgressFnPtr ); 

#endif /* #ifndef _WIFI_H */
