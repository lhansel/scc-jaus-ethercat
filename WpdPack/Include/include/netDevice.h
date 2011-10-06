/* $Revision: 1.8 $ */
/* Copyright $Date: 2009/09/16 15:02:51 $ */  

/******************************************************************************
 *
 * Copyright 2009 NetBurner, Inc.  ALL RIGHTS RESERVED
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
 * 5405 Morehouse Drive
 * San Diego, California 92121
 *
 * information available at:  http://www.netburner.com
 * E-Mail info@netburner.com
 *
 * Support is available: E-Mail support@netburner.com
 *
 *****************************************************************************/

#ifndef _NETDEVICE_H_
#define _NETDEVICE_H_

/*
 ******************************************************************************
 *
 * Include Files
 *
 ******************************************************************************
 */
 
/*
 ******************************************************************************
 *
 * Debugging
 *
 ******************************************************************************
 */
/* Library debugging switch */
#define NETDEVICE_DEVICE_DEBUG            ( 1 )
 
/*
 ******************************************************************************
 *
 * Constants
 *
 ******************************************************************************
 */
/* Maximum Network Devices */
#define NETDEVICE_DEVICE_MAXIMUM          ( 5 )

/* 
   NetworkAddInterface Returns
   
      NETDEVICE_REQUEST_FAILED        - Was not added by the system
      NETDEVICE_MODULE_NOT_FOUND      - Module not detected
      NETDEVICE_ALREADY_EXISTS        - Already exists
      NETDEVICE_SUPPORT_TASK_FAILED   - Driver task not created

*/

#define NETDEVICE_REQUEST_FAILED          (  0 )
#define NETDEVICE_MODULE_NOT_FOUND        ( -1 )
#define NETDEVICE_ALREADY_EXISTS          ( -2 )
#define NETDEVICE_SUPPORT_TASK_FAILED     ( -3 )
#define NETDEVICE_MODULE_NOT_SUPPORTED    ( -4 )


/* List requests */
#define NETDEVICE_SITE_COUNT              ( 1 )
#define NETDEVICE_SITE_LIST               ( 2 )

/*
 ******************************************************************************
 *
 * Enumerations
 *
 ******************************************************************************
 */
/*
   Network interface controller (NIC)
   
      ControllerNone             - No controller
      ControllerPointToPoint     - Point-to-Point data link protocol
      ControllerRealtekRtl8711   - Realtek IEEE 802.11g
      
 */ 
typedef enum _NetDeviceController
{
   ControllerNone,
   ControllerPointToPoint,
   ControllerRealtekRtl8711
   
} NetDeviceController;
 
/*
   Network interface controller (NIC) bus type used
   
      BusTypeNone                - No bus
      BusTypeMemoryMapped        - External data bus access
      BusTypeSdioBusType         - Secure Digital Input Output (SDIO)
      BusTypeSdioBusSpiMode      - SDIO using SPI mode
      BusTypeSpiBus              - Serial Peripheral Interface (SPI)
      
 */ 
typedef enum _NetDeviceBusType
{
   BusTypeNone,
   BusTypeMemoryMapped,
   BusTypeSdioBusType,
   BusTypeSdioBusSpiMode,
   BusTypeSpiBus
   
} NetDeviceBusType; 

/* 
      Select details (chip select)
      
         Chip select are either managed (asserted/deasserted by the processor
         module (e.g. (Q)SPI module) or unmanaged and handled by the driver.
         
         The (Q)SPI module supports connecting additional hardware that using
         the (Q)SPI chip selects can select several devices (multiplex) up to 15.
         
      SelectDetailNone                    - No chip select
      SelectDetailSpiUnmanaged            - Single signal unmanaged chip select 
      SelectDetailSpiUnmanagedMultiplex   - Multiplexed unmanaged chip select 
      SelectDetailSpiManaged              - Single signal managed chip select 
      SelectDetailSpiManagedMultiplex     - Multiplexed managed chip select 
      SelectDetailGpioUnmanaged           - Single signal unmanaged chip select 
      
      Changing the ordering of these parameters require complete system and platform
      rebuilds.

*/

typedef enum _NetDeviceSelectDetail
{
   SelectDetailNone,
   SelectDetailSpiUnmanaged,
   SelectDetailSpiUnmanagedMultiplex,
   SelectDetailSpiManaged,
   SelectDetailSpiManagedMultiplex,
   SelectDetailGpioUnmanaged,
   
} NetDeviceSelectDetail; 

/*
 ******************************************************************************
 *
 * C++ definitions
 *
 ******************************************************************************
 */
 
/*
 ******************************************************************************
 *
 * Routine Prototypes
 *
 ******************************************************************************
 */
/* Device management */ 
typedef void ( NetDeviceProgressFn )( int activity, int progress, char* detail );   
typedef NetDeviceProgressFn* NetDeviceProgressFnPtr;

#ifdef __cplusplus

/*
 ******************************************************************************
 *
 * Classes
 *
 ******************************************************************************
 */
/*
 ******************************************************************************
 * Network Device Base Class
 ******************************************************************************
 */
class NetDevice
{
   public:
      /*** Constructor ***/
      NetDevice( int irq, NetDeviceController controller, 
            NetDeviceBusType busType, int select, 
            NetDeviceSelectDetail selectDetails );

      /*** Destructor ***/
      virtual ~NetDevice();

      /*** Copy Constructor ***/
      /* Default */

      /*** Static Methods ***/
      /* Verify platform support, create controller object */
      static int add( int irq, NetDeviceController controller, 
            NetDeviceBusType busType, int select, 
            NetDeviceSelectDetail selectDetails );
      
      /* Get network device  */
      static NetDevice* getNetDevice( int deviceIndex );
      
      /*** Methods ***/
      /* Setup bus for controller */
      virtual BOOL setupBus( void );

      /* Setup ISR */
      virtual BOOL setupIsr( DeviceIsrFnPtr isrFunction, int irq );
            
      /* Determine existence of controller on bus */
      virtual BOOL probe( void );

      /* Initialize controller in idle state, add to network stack */
      virtual BOOL open( void );

      /* Reset controller to quiescent idle state */
      virtual BOOL close( void );

      /* Remove controller from network stack */
      virtual BOOL remove( void );
      
      /* Configure */
      virtual BOOL configure( int request, ssize_t parameterSize, 
            void* parameterPtr );
      
      /* List */
      virtual BOOL list( int request, ssize_t& listSize, void* listPtr );
      
      /* Network name */
      virtual void getNetworkName( char* name, ssize_t maximumBytes );
      
      /* Survey network */
      virtual BOOL surveyNetwork( char* site );
      
      /* Connect */
      virtual BOOL connect( const char* identifier = NULL, 
            const char* securityKey = NULL, BOOL adhoc = FALSE );
            
      /* Disconnect */
      virtual BOOL disconnect( void );
      
      /*** Network stack routines ***/
      /* Transmit packet */
      virtual BOOL transmitPacket( PoolPtr poolPtr );
      
      /* Set/Reset multicast */
      virtual void resetMulticast( MACADDRESS_48 macAddress, BOOL addAddress );
      
      /*** Accessors ***/
      /* Access stack interface number */
      void setInterfaceNumber( int interfaceNumber );
      int getInterfaceNumber( void );
      
      /* Get number */
      int getNumber( void );

      /* Get name */
      char* getName( void );

      /* Get unit */
      int getUnit( void );
      
      /* Get controller */
      NetDeviceController getController( void );

      /* Get bus type */
      NetDeviceBusType getBusType( void );
      
      /* Get select */
      int getSelect( void );
      
      /* Get select */
      NetDeviceSelectDetail getSelectDetail( void );
      
      /* Get MAC address */
      virtual BOOL getMacAddress( MACADDRESS_48& macAddress );

      /* Connected? */
      virtual BOOL isConnected( void );
      
      /* Progress routine */
      virtual void setProgressRoutine( NetDeviceProgressFnPtr routinePtr );
      
      /* Signal interrupt */
      virtual void signalInterrupt( void );
            
      /* Valid? */
      BOOL isValid( void );
      
   protected:
      /* Set name */
      void setName( const char* namePtr );
      
      /* Set unit */
      void setUnit( int unit );
      
      /* Set valid */
      void setValid( BOOL valid );
      
   private:
      /*** Methods ***/
      /* None */
      
      /*** Data Members ***/
      /* Index in __device */
      int __index;
      
      /* Name */
      char* __namePtr;
      
      /* Unit */
      int __unit;
      
      /* IRQ */
      int __irq;
      
      /* Controller */
      NetDeviceController __controller;
      
      /* Bus */
      NetDeviceBusType __busType;
      
      /* Select */
      int __select;
      
      /* Select */
      NetDeviceSelectDetail __selectDetail;
      
      /* Interface number */
      int __interfaceNumber;
      
      /* Valid */
      BOOL __valid;

      /*** Static Data Members ***/
      /* One time initialization */
      static BOOL __isInitialized;
      
      /* Critical section for mutex */
      static OS_CRIT __criticalSection;
      
      /* Interface objects */
      static NetDevice* __device[ NETDEVICE_DEVICE_MAXIMUM ];
      
};      

/* 
 ******************************************************************************
 
   Verify availability and support for device.
   
    
      Parameters:
         irq         - Fixed level interrupt source
         controller  - IEEE 802.11g controller
         busType     - Bus used by the controller
         
         
      Return:
         TRUE - Support and available on module, FALSE option not supported
         
       Note:
         Does not verify controller is attached and operational.
         
 ******************************************************************************
 */
BOOL NetDeviceIsValid( int irq, NetDeviceController controller,
      NetDeviceBusType busType );
      
/* 
 ******************************************************************************
 
   Get device handle
   
    
      Parameters:
         irq         - Fixed level interrupt source
         controller  - IEEE 802.11g controller
         busType     - Bus used by the controller
         select      - Chip select is bus specific
                        SDIO using SPI mode (BusTypeSdioBusSpiMode)
                        0 - 3 (Q)SPI chip select lines QSPI_CS[0:3]
         
      Return:
         Handle - Supported and available on module, 
               NULL interface not supported
         
       Note:
         Verify parameters and platform support for device.
         Does not verify controller is attached and operational.
         
 ******************************************************************************
 */
NetDevice* NetDeviceGetDevice( int irq, NetDeviceController controller,
      NetDeviceBusType busType, int select, 
      NetDeviceSelectDetail selectDetails );

/* Device Realtek RTL8711 Controller on SDIO bus in SPI mode */
NetDevice* NetDeviceGetDeviceRtl8711SdioSpi( int irq,int select, 
      NetDeviceSelectDetail selectDetails );

#endif /* #ifdef __cplusplus */

#endif /* _NETDEVICE_H_ */
