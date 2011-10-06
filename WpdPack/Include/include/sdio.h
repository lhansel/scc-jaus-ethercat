/* $Revision: 1.3 $ */
/* Copyright $Date: 2009/07/24 15:44:44 $ */  

/******************************************************************************
 *
 * Copyright 2008-2009 NetBurner, Inc.  ALL RIGHTS RESERVED
 *   Permission is hereby granted to purchasers of NetBurner Hardware
 *   to use or modify this computer program for any use as long as the
 *   resultant program is only executed on NetBurner provided hardware.
 *
 *   No other rights to use this program or it's derivatives in part or
 *   in whole are granted.
 *
 *   It may be possible to license this or other NetBurner software for
 *   use on non-NetBurner Hardware.
 *   Please contact Licensing@Netburner.com for more information.
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

#ifndef _SDIO_H_
#define _SDIO_H_

/*
 ******************************************************************************
 *
 * Reference 
 *    SDIO Simplified Specification, SD Specification, Part E1, Version 2.00
 *       February 8, 2007, Technical Committee, SD Card Association
 *
 *    Physical Layer Simplified Specification, SD Specification, Part 1, 
 *       Version 2.00, September 25, 2006, Technical Committee 
 *       SD Card Association
 *
 ******************************************************************************
 */
/*
 ******************************************************************************
 *
 * Debugging
 *
 *    Needs to be uncommented to support these features
 *
 ******************************************************************************
 */
/* Library debugging switch */
/* #define SDIO_DEBUG                  ( 1 ) */
 
/*
 ******************************************************************************
 *
 * Runtime Library Definitions
 *
 ******************************************************************************
 */
/* Bus type */
#define SDIO_SPI_BUS             ( 1 ) 
 
/*
 ******************************************************************************
 *
 * Command and Response Definitions
 *
 ******************************************************************************
 */
/* Command size in bytes */
#define SDIO_COMMAND_SIZE                    ( 6 )

/* Block size */
#define SDIO_BLOCK_SIZE                      ( 512 )
 
/* Direction */
#define SDIO_CARD_TO_HOST                    ( 0x0 ) 
#define SDIO_HOST_TO_CARD                    ( 0x1 ) 

/* Command Index */
#define SDIO_GO_IDLE                         ( 0x00 )
#define SDIO_IO_SEND_OPERATIONAL_CONDITION   ( 0x05 )
#define SDIO_IO_RW_DIRECT                    ( 0x34 )
#define SDIO_IO_RW_EXTENDED                  ( 0x35 )
#define SDIO_CRC_ON_OFF                      ( 0x3B )
 
/* Read/Write */
#define SDIO_READ                            ( 0 )
#define SDIO_WRITE                           ( 1 )
 
/* Function Number (I/O card dependent) */
#define SDIO_FUNCTION_0                      ( 0 )
#define SDIO_FUNCTION_1                      ( 1 )
 
/* Read after write */
#define SDIO_READ_OR_WRITE_ONLY              ( 0 )
#define SDIO_RAW                             ( 1 )

/* Block Mode */
#define SDIO_BYTE_MODE                       ( 0 )
#define SDIO_BLOCK_MODE                      ( 1 )

/* OP code */
#define SDIO_FIXED_ADDRESS                   ( FALSE )
#define SDIO_INCREMENTING_ADDRESS            ( TRUE )

/* Block size */
#define SDIO_BLOCK_SIZE_NONE                 ( 0 )
 
/*
 ******************************************************************************
 *
 * Common I/O Area (CIA) register addresses (Function 0)
 *
 ******************************************************************************
 */
/* Card Common Control Registers (CCCR) */
#define SDIO_CIA_CCCR_CCCR_SDIO_REVISION        ( 0x00000 )
#define SDIO_CIA_CCCR_SD_SPEC_REVISION          ( 0x00001 )
#define SDIO_CIA_CCCR_IO_ENABLE                 ( 0x00002 )
#define SDIO_CIA_CCCR_IO_READY                  ( 0x00003 )
#define SDIO_CIA_CCCR_INTERRUPT_ENABLE          ( 0x00004 )
#define SDIO_CIA_CCCR_INTERRUPT_PENDING         ( 0x00005 )
#define SDIO_CIA_CCCR_IO_ABORT                  ( 0x00006 )
#define SDIO_CIA_CCCR_BUS_INTERFACE_CONTROL     ( 0x00007 )
#define SDIO_CIA_CCCR_CARD_CAPABILITY           ( 0x00008 )
#define SDIO_CIA_CCCR_COMMON_CIS_POINTER_LSB    ( 0x00009 )
#define SDIO_CIA_CCCR_COMMON_CIS_POINTER_CSB    ( 0x0000A )
#define SDIO_CIA_CCCR_COMMON_CIS_POINTER_MSB    ( 0x0000B )
#define SDIO_CIA_CCCR_BUS_SUSPEND               ( 0x0000C )
#define SDIO_CIA_CCCR_FUNCTION_SELECT           ( 0x0000D )
#define SDIO_CIA_CCCR_EXEC_FLAGS                ( 0x0000E )
#define SDIO_CIA_CCCR_READY_FLAGS               ( 0x0000F )
#define SDIO_CIA_CCCR_FN0_BLOCK_SIZE_LSB        ( 0x00010 )
#define SDIO_CIA_CCCR_FN0_BLOCK_SIZE_MSB        ( 0x00011 )
#define SDIO_CIA_CCCR_POWER_CONTROL             ( 0x00012 )
 
/*
 ******************************************************************************
 *
 * Common I/O Area (CIA) register addresses (Function 1)
 *
 ******************************************************************************
 */
#define SDIO_CIA_CCCR_FN1_BLOCK_SIZE_LSB        ( 0x00110 )
#define SDIO_CIA_CCCR_FN1_BLOCK_SIZE_MSB        ( 0x00111 )
/*
 ******************************************************************************
 *
 * Runtime Library Enumerations and Structures
 *
 ******************************************************************************
 */
/*
   SDIO Bus type
      Sdio                 - SD 4-bit mode
      SdioSpiMode          - SPI mode     
      
 */
typedef enum _SdioBusType
{
   Sdio,
   SdioSpiMode
   
} SdioBusType;

/*
   SDIO Response type
      R4                   - IO_SEND_OP_COND Response
      R5                   - IO_RW_DIRECT Response
      
 */
typedef enum _SdioResponseType
{
   R4,
   R5
   
} SdioResponseType;

/*
   Bus token for user
      butType              - Bus type in use for this token
      
      *** SPI ***
      spiSetting           - Shared SPI setting
      spiConnectTimeout    - Bus allocation timeout period in ticks
      spiResponseTimeout   - Command response timeout period in ticks
      idleByteCount        - Bytes required to idle bus
      idleFillValue        - Data to transmit that idles the bus
      
      *** SDIO Future ***
      
 */
typedef struct _SdioBusToken
{
   SdioBusType busType;
   int spiSetting;
   DWORD spiConnectTimeout;
   DWORD spiResponseTimeout;
   ssize_t idleByteCount;
   WORD idleFillValue;
   
}  __attribute__( ( packed ) ) SdioBusToken;

/*
 ******************************************************************************
 *
 * Command and Response Structures
 *
 ******************************************************************************
 */
/*
   Start bit, direction and command
      startBit             - Start bit, always 0
      direction            - 0 card to host, 1 host to card
      index                - Command index
      
 */
typedef struct _CommandIndex
{
   BYTE startBit:1;
   BYTE direction:1;
   BYTE index:6;
   
}  __attribute__( ( packed) ) CommandIndex;

/*
   CRC and end
      crc7                 - 7 bits of CRC data
      endBit               - End bit, always 1
      
 */
typedef struct _Crc
{
   BYTE crc7:7;
   BYTE endBit:1;
   
}  __attribute__( ( packed) ) Crc;

/*
   Response Flags IAW SD Physical Specification
      comCrcError          - 1 yes else 0
      illegalCommand       - 1 yes else 0
      ioCurrentState       - Current I/O state
      error                - Unknown error
      rfu                  - RFU always 0
      functionNumberError  - 1 yes else 0
      outOfRange           - 1 yes else 0
      
 */
typedef struct _ResponseFlags
{
   BYTE comCrcError:1;
   BYTE illegalCommand:1;
   BYTE ioCurrentState:2;
   BYTE error:1;
   BYTE rfu:1;
   BYTE functionNumberError:1;
   BYTE outOfRange:1;
   
}  __attribute__( ( packed) ) ResponseFlags;

/*
   Go idle state (CMD0)
      commandIndex         - Start, direction and command index
      stuff                - MBZ
      crc                  - CRC and end bit
      
 */
typedef struct _GoIdleStateCommand_CMD0
{
   CommandIndex commandIndex;
   BYTE stuff[ 4 ];
   Crc crc;
   
}  __attribute__( ( packed) ) GoIdleStateCommand_CMD0;

/*
   I/O Send Operational Condition
      crc                  - CRC and end bit
      ocr                  - Operations condition register
      stuffBits            - MBZ
      commandIndex         - Start, direction and command index
      
 */
typedef struct _IoSendOpCondCommand_CMD5
{
   CommandIndex commandIndex;
   BYTE stuffBits;
   BYTE ocr[ 3 ];
   Crc crc;
   
}  __attribute__( ( packed) ) IoSendOpCondCommand_CMD5;

/*
   CRC toggle command (CMD59)
      crc                  - CRC and end bit
      ocr                  - Operations condition register
      stuffBits            - MBZ
      commandIndex         - Start, direction and command index
      
      ??? Need more definition
      
 */
typedef struct _CrcOnOffCommand_CMD59
{
   CommandIndex commandIndex;
   BYTE stuffBits;
   BYTE ocr[ 3 ];
   Crc crc;
   
}  __attribute__( ( packed) ) CrcOnOffCommand_CMD59;

/*
   Modified R1 IAW SD Physical Specification
      start                - Start bit, always 0
      parameterError       - 1 yes else 0
      rfu                  - RFU always 0
      functionNumberError  - 1 yes else 0
      comCrcError          - 1 yes else 0
      illegalCommand       - 1 yes else 0
      rfu_1                - RFU always 0
      idleState            - Idle state, always 1
 */
typedef struct _ModifiedR1
{
   BYTE startBit:1;
   BYTE parameterError:1;
   BYTE rfu:1;
   BYTE functionNumberError:1;
   BYTE comCrcError:1;
   BYTE illegalCommand:1;
   BYTE rfu_1:1;
   BYTE idleState:1;
   
}  __attribute__( ( packed) ) ModifiedR1;

/*
   Operate bit, number of I/O functions and memory present
      operate              - 1 card is ready to operate
      ioFunctions          - Number of I/O functions supported
      memoryPresent        - 1 SD memory else 0
      stuffBits            - MBZ
      
 */
typedef struct _NumberIoFunctions
{
   BYTE operate:1;
   BYTE ioFunctions:3;
   BYTE memoryPresent:1;
   BYTE stuffBits:3;
   
}  __attribute__( ( packed) ) NumberIoFunctions;

/*
   I/O Send Operational Condition Response in SPI mode (R4)
      modifiedR1           - Modified R1
      numberIoFunctions    - Number of I/O functions supported
      ocr                  - Operations condition register
      
 */
typedef struct _IoSendOpCondResponseSpiMode_R4
{
   ModifiedR1 modifiedR1;
   NumberIoFunctions numberIoFunctions;
   BYTE ocr[ 3 ];
   
}  __attribute__( ( packed) ) IoSendOpCondResponseSpiMode_R4;

/*
   I/O Send Operational Condition Response  (R4)
      startBit             - Start bit, always 0
      direction            - 0 card to host
      reserved_02_07       - 1s
      numberIoFunctions    - Number of I/O functions supported
      ocr                  - Operations condition register
      reserved_45_46       - 1S
      endBit               - End bit, always 1
      
 */
typedef struct _IoSendOpCondResponse_R4
{
   BYTE startBit:1;
   BYTE direction:1;
   BYTE reserved_02_07:6;
   NumberIoFunctions numberIoFunctions;
   BYTE ocr[ 3 ];
   BYTE reserved_45_46:7;
   BYTE endBit:1;
   
}  __attribute__( ( packed) ) IoSendOpCondResponse_R4;

/*
   R/W flag, function number and raw flag
      rwFlag               - 0 read, 1 write
      functionNumber       - I/O card area
      rawFlag              - Read after write, 1 yes
      stuff                - MBZ
      registerAddress_bits_16thru15  - Register address bits 15 and 16
      
 */
typedef struct _Function
{
   BYTE rwFlag:1;
   BYTE functionNumber:3;
   BYTE rawFlag:1;
   BYTE stuff:1;
   BYTE registerAddress_bits_16thru15:2;
   
}  __attribute__( ( packed) ) Function;

/*
   Register address
      address              - Register address bits 0 through 14
      stuff                - MBZ
      
 */
typedef struct _RegisterAddress
{
   unsigned short address:15;
   unsigned short stuff:1;
   
}  __attribute__( ( packed) ) RegisterAddress;

/*
   I/O read/write direct command
      commandIndex         - Start, direction and command index
      function             - R/W flag, function number and raw flag
      registerAddress      - Register address bits 0 through 14
      dataOrStuff          - Write data byte else MBZ
      stuffBits            - MBZ
      
 */
typedef struct _IoRwDirectCommand_CMD52
{
   CommandIndex commandIndex;
   Function function;
   RegisterAddress registerAddress;
   BYTE dataOrStuff;
   Crc crc;
   
}  __attribute__( ( packed) ) IoRwDirectCommand_CMD52;

/*
   I/O read/write direct response
      commandIndex         - Start, direction and command index
      stuff                - MBZ
      responseFlags        - Status of SDIO card
      readOrWriteData      - RAW read else ignore
      data                 - Read data
      crc                  - CRC
      
 */
typedef struct _IoRwDirectResponse_R5
{
   CommandIndex commandIndex;
   BYTE stuff[ 2 ];
   ResponseFlags responseFlags;
   BYTE readOrWriteData;
   BYTE data;
   Crc crc;
   
}  __attribute__( ( packed) ) IoRwDirectResponse_R5;

/*
   I/O read/write direct response
      modifiedR1           - Modified R1
      data                 - Read data
      
 */
typedef struct _IoRwDirectResponseSpiMode_R5
{
   ModifiedR1 modifiedR1;
   BYTE data;
   
}  __attribute__( ( packed) ) IoRwDirectResponseSpiMode_R5;

/*
   R/W flag, function number and raw flag
      rwFlag               - 0 read, 1 write
      functionNumber       - I/O card area
      blockMode            - 1 block mode else bytes
      opCode               -  1 incrementing, 0 fixed location
      registerAddress_bits_16thru15  - Register address bits 15 and 16
      
 */
typedef struct _FunctionBlock
{
   BYTE rwFlag:1;
   BYTE functionNumber:3;
   BYTE blockMode:1;
   BYTE opCode:1;
   BYTE registerAddress_bits_16thru15:2;
   
}  __attribute__( ( packed) ) FunctionBlock;

/*
   Register extended address
      address              - Register address bits 0 through 14
      byteCount_bit_8       - Byte or block count msb
      
 */
typedef struct _RegisterExtended
{
   unsigned short address:15;
   unsigned short byteCount_bit_8 :1;
   
}  __attribute__( ( packed) ) RegisterExtended;

/*
   I/O read/write extended command
      commandIndex         - Start, direction and command index
      functionBlock        - R/W flag, function number, block and increment
      registerExtended     - Register address bits 0 through 14, msb block count
      byteCount            - Byte count bits 0 through 7
      stuffBits            - MBZ
      
 */
typedef struct _IoRwExtendedCommand_CMD53
{
   CommandIndex commandIndex;
   FunctionBlock functionBlock;
   RegisterExtended registerExtended;
   BYTE byteCount;
   Crc crc;
   
}  __attribute__( ( packed) ) IoRwExtendedCommand_CMD53;

/*
   Register Value ( Host order, Big Endian )
      wValue 16bit value
      bValue 8 bit value
      
*/

#define HIGH_BYTE              ( 0 )
#define LOW_BYTE               ( 1 )

typedef union _RegisterValue
{
   WORD wValue;
   BYTE bValue[ 2 ];
   
} __attribute__( ( packed) ) RegisterValue; 
       
       
/*
 ******************************************************************************
 *
 * CIA CCCR Register field structures
 *
 ******************************************************************************
 */
/*
   CCCR/SDIO Revision Register (SDIO_CIA_CCCR_CCCR_SDIO_REVISION)
      sdio                          - SDIO revision
      cccr                          - CCCR revision
      
 */
typedef struct _CccrSdioRevision
{
   BYTE sdio:4;
   BYTE cccr:4;
   
}  __attribute__( ( packed) ) CccrSdioRevision;

/*
   SDIO Specification Revision Register (SDIO_CIA_CCCR_SD_SPEC_REVISION)
      rfu                           - Reserved for future use
      sd                            - Revision
      
 */
typedef struct _SdioSpecRevision
{
   BYTE rfu:4;
   BYTE sd:4;
   
}  __attribute__( ( packed) ) SdioSpecRevision;

/*
   I/O Enable or Ready Register (SDIO_CIA_CCCR_IO_[ENABLE|READY])
      io7                           - Function 7
      io6                           - Function 6
      io5                           - Function 5
      io4                           - Function 4
      io3                           - Function 3
      io2                           - Function 2
      io1                           - Function 1
      rfu                           - Reserved for future use
      
 */
typedef struct _IoFunctions
{
   BYTE io7:1;
   BYTE io6:1;
   BYTE io5:1;
   BYTE io4:1;
   BYTE io3:1;
   BYTE io2:1;
   BYTE io1:1;
   BYTE rfu:1;
   
}  __attribute__( ( packed) ) IoFunctions;

/*
   Interrupt Enable or Pending Register 
         (SDIO_CIA_CCCR_INTERRUPT_[ENABLE|PENDING])
      int7                          - Interrupt for function 7
      int6                          - Interrupt for function 6
      int5                          - Interrupt for function 5
      int4                          - Interrupt for function 4
      int3                          - Interrupt for function 3
      int2                          - Interrupt for function 2
      int1                          - Interrupt for function 1
      ienm                          - Master enable
      
 */
typedef struct _IntFunctions
{
   BYTE int7:1;
   BYTE int6:1;
   BYTE int5:1;
   BYTE int4:1;
   BYTE int3:1;
   BYTE int2:1;
   BYTE int1:1;
   BYTE ienm:1;
   
}  __attribute__( ( packed) ) IntFunctions;

/*
   Bus Interface Control (SDIO_CIA_CCCR_BUS_INTERFACE_CONTROL)
      cdDisable                     - Card detection
      scsi                          - Support continuous SPI interrupt
      ecsi                          - Enable continuous SPI interrupt
      width                         - SDIO data bus width
      
 */
typedef struct _BusInterfaceControl
{
   BYTE cdDisable:1;
   BYTE scsi:1;
   BYTE ecsi:1;
   BYTE rfu:3;
   BYTE width:2;
   
}  __attribute__( ( packed) ) BusInterfaceControl;

/*
   Card Capability (SDIO_CIA_CCCR_CARD_CAPABILITY)
      s4bls                         - 4-bit support for low speed cards
      lsc                           - Low speed card
      e4mi                          - Enable inter-block interrupts 4 bit mode
      s4mi                          - Supports inter-block interrupts 4 bit mode
      sbs                           - Supports suspend/resume
      srw                           - Supports read wait
      smb                           - Supports multiblock
      sdc                           - Supports direct commands
      
 */
typedef struct _CardCapability
{
   BYTE s4bls:1;
   BYTE lsc:1;
   BYTE e4mi:1;
   BYTE s4mi:1;
   BYTE sbs:1;
   BYTE srw:1;
   BYTE smb:1;
   BYTE sdc:1;
   
}  __attribute__( ( packed) ) CardCapability;

/*
   Power Control (SDIO_CIA_CCCR_POWER_CONTROL)
      empc                          - Enable master power control
      smpc                          - Supports master power control
      
 */
typedef struct _PowerControl
{
   BYTE rfu:6;
   BYTE empc:1;
   BYTE smpc:1;
   
}  __attribute__( ( packed) ) PowerControl;

/*
   Register settings and transfer byte union
      <lower case>                  - Register bits defined as structure
      content                       - Transfer byte
      
 */
typedef union _CccrRegister
{
   CccrSdioRevision cccrSdioRevision;
   SdioSpecRevision sdioSpecRevision;
   IoFunctions ioFunctions;
   IntFunctions intFunctions;
   BusInterfaceControl busInterfaceControl;
   CardCapability cardCapability;
   PowerControl powerControl;
   BYTE content;
   
}  __attribute__( ( packed) ) CccrRegister;

/*
 ******************************************************************************
 *
 * Classes
 *
 ******************************************************************************
 */
/*
 ******************************************************************************
 *
 * SDIO Base Class (CMD0)
 *
 ******************************************************************************
 */
class SdioCommand
{
   public:
      /*** Constructor ***/
      SdioCommand( BYTE commandIndex );

      /*** Destructor ***/
      virtual ~SdioCommand(){ return; };

      /*** Methods ***/
      /* Reset command */
      void reset( void );

      /* Prepare command to send */
      virtual void prepare( void );
      
      /* Generate CRC 7 */
      BYTE generateCrc7( void );
      
      /* Display using iprintf */
      virtual void display( void ){ return; };
      
      /*** Accessors ***/
      /* Get command data pointer */
      PBYTE getPtr( void );
      
      /* Get response size */
      DWORD getSize( void );
      
   protected:
      /* None */
       
   private:
      /*** Methods ***/
      /* None */
      
      /*** Data Members ***/
      /* Command index */
      BYTE __command_index;
      
      /* CRC 7 */
      BYTE __crc7;
      
      /* Command data buffer */
      BYTE __commandData[ SDIO_COMMAND_SIZE ];
      
      /* Command 0 pointer */
      GoIdleStateCommand_CMD0* __commandPtr;

};      

/*
 ******************************************************************************
 *
 * SDIO I/O Send Operational Condition (CMD5)
 *
 ******************************************************************************
 */
class SdioCMD5 : public SdioCommand
{
   public:
      /*** Constructor ***/
      SdioCMD5();

      /*** Destructor ***/
      ~SdioCMD5(){ return; };

      /*** Methods ***/
      /* Prepare command to send */
      void prepare( DWORD ocr );
      
      /*** Accessors ***/
      /* None */
      
   protected:
      /* None */
       
   private:
      /*** Methods ***/
      /* Reset command */
      /* None */

      /*** Data Members ***/
      /* Command 5 pointer */
      IoSendOpCondCommand_CMD5* __commandPtr;

};      

/*
 ******************************************************************************
 *
 * SDIO I/O Read/Write Direct (CMD52)
 *
 ******************************************************************************
 */
class SdioCMD52 : public SdioCommand
{
   public:
      /*** Constructor ***/
      SdioCMD52( void );

      /*** Destructor ***/
      ~SdioCMD52(){ return; };

      /*** Methods ***/
      /* Prepare command to send */
      void prepare( int readWriteFlag, BYTE function, int rawFlag, 
            DWORD registerAddress, BYTE writeData );
      
      /* Display using iprintf */
      void display( void );
      
      /*** Accessors ***/
      /* None */
      
   protected:
      /* None */
       
   private:
      /*** Methods ***/
      /* Reset command */
      /* None */

      /*** Data Members ***/
      /* Command 52 pointer */
      IoRwDirectCommand_CMD52* __commandPtr;

};      

/*
 ******************************************************************************
 *
 * SDIO I/O Read/Write Extended (CMD53)
 *
 ******************************************************************************
 */
class SdioCMD53 : public SdioCommand
{
   public:
      /*** Constructor ***/
      SdioCMD53( void );

      /*** Destructor ***/
      ~SdioCMD53(){ return; };

      /*** Methods ***/
      /* Prepare command to send */
      void prepare( int readWriteFlag, BYTE function, int blockMode, 
            BOOL isIncrementingAddress, DWORD registerAddress, DWORD byteCount, 
            WORD blockSize );
      
      /* Display using iprintf */
      void display( void );
      
      /*** Accessors ***/
      /* Get object */
      IoRwExtendedCommand_CMD53& getCommand( void );
      
   protected:
      /* None */
       
   private:
      /*** Methods ***/
      /* Reset command */
      /* None */

      /*** Data Members ***/
      /* Command 53 pointer */
      IoRwExtendedCommand_CMD53* __commandPtr;

};      

/*
 ******************************************************************************
 *
 * CRC toggle command (CMD59)
 *
 ******************************************************************************
 */
class SdioCMD59 : public SdioCommand
{
   public:
      /*** Constructor ***/
      SdioCMD59( void );

      /*** Destructor ***/
      ~SdioCMD59(){ return; };

      /*** Methods ***/
      /* Prepare command to send */
      void prepare( BOOL isOn );
      
      /*** Accessors ***/
      /* None */
      
   protected:
      /* None */
       
   private:
      /*** Methods ***/
      /* Reset command */
      /* None */

      /*** Data Members ***/
      /* Command 5 pointer */
      CrcOnOffCommand_CMD59* __commandPtr;

};      

/*
 ******************************************************************************
 *
 * SDIO Response Base Class
 *
 ******************************************************************************
 */
class SdioResponse
{
   public:
      /*** Constructor ***/
      SdioResponse( SdioBusType busType, SdioResponseType responseType );

      /*** Destructor ***/
      virtual ~SdioResponse() = 0;

      /*** Methods ***/
      /* Is response OK */
      virtual BOOL isOk( void ) = 0;
      
      /* Display using iprintf */
      virtual void display( void ) = 0;
      
      /*** Accessors ***/
      /* Get response type */
      SdioResponseType getType( void );
      
      /* Get response type */
      SdioBusType getBusType( void );
      
      /* Get remaining response */
      virtual PBYTE getPtr( void ) = 0;
      
      /* Get response size */
      virtual DWORD getSize( void ) = 0;
      
   protected:
      /* None */
       
   private:
      /*** Methods ***/
      /* Synchronize data */
      virtual void synchronize( void ) = 0;

      /*** Data Members ***/
      /* Type */
      SdioResponseType __type;
      
      SdioBusType __busType;

};      

/*
 ******************************************************************************
 *
 * I/O Send Operational Condition response (R4)
 *
 ******************************************************************************
 */
class SdioResponseR4 : public SdioResponse
{
   public:
      /*** Constructor ***/
      SdioResponseR4( SdioBusType busType );

      /*** Destructor ***/
      ~SdioResponseR4();

      /*** Methods ***/
      /* Is response OK */
      BOOL isOk( void );
      
      /* Display using iprintf */
      void display( void );
      
      /*** Accessors ***/
      /* Get response pointer */
      IoSendOpCondResponse_R4* getResponsePtr( void );
      
      /* Get remaining response */
      PBYTE getPtr( void );
      
      /* Get response size */
      DWORD getSize( void );
      
      /* Get response pointer */
      IoSendOpCondResponse_R4& getResponse( void );
      
      /* Get response size */
      DWORD getNumberIoFunctions( void );
      
      /* Get Operations Condition Register (OCR) */
      DWORD getOcr( void );
      
   protected:
      /* None */
       
   private:
      /*** Methods ***/
      /* Synchronize data */
      void synchronize( void );

      /*** Data Members ***/
      /* Response pointer and size */
      PBYTE __responsePtr;
      ssize_t __responseSize;
      
      /* Response */
      IoSendOpCondResponse_R4 __response;
      
      /* Modified R1 (SPI Mode) */
      IoSendOpCondResponseSpiMode_R4 __responseSpiMode;

};      

/*
 ******************************************************************************
 *
 * I/O Read/Write Direct response (R5)
 *
 ******************************************************************************
 */
class SdioResponseR5 : public SdioResponse
{
   public:
      /*** Constructor ***/
      SdioResponseR5( SdioBusType busType );

      /*** Destructor ***/
      ~SdioResponseR5();

      /*** Methods ***/
      /* Is response OK */
      BOOL isOk( void );
      
      /* Is card idle */
      BOOL isIdle( void );
      
      /* Display using iprintf */
      void display( void );
      
      /*** Accessors ***/
      /* Get response pointer */
      IoRwDirectResponse_R5* getResponsePtr( void );
      
      /* Get remaining response */
      PBYTE getPtr( void );
      
      /* Get response size */
      DWORD getSize( void );
      
      /* Get response reference */
      IoRwDirectResponse_R5& getResponse( void );
      
      /* Get data byte */
      BYTE getData( void );
      
   protected:
      /* None */
       
   private:
      /*** Methods ***/
      /* Synchronize data */
      void synchronize( void );

      /*** Data Members ***/
      /* Response pointer and size */
      PBYTE __responsePtr;
      ssize_t __responseSize;
      
      /* IO_RW_DIRECT Response */
      IoRwDirectResponse_R5 __response;

      /* IO_RW_DIRECT Response (SPI Mode) */
      IoRwDirectResponseSpiMode_R5 __responseSpiMode;

};      


#endif /* _SDIO_H_ */
