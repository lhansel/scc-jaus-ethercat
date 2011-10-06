/* $Revision: 1.15 $ */
/*******************************************************************************
 *
 * Copyright 1998-2008 NetBurner, Inc.  ALL RIGHTS RESERVED
 *
 * Permission is hereby granted to purchasers of NetBurner hardware to use or
 * modify this computer program for any use as long as the resultant program
 * is only executed on NetBurner provided hardware.
 *
 * No other rights to use this program or its derivatives in part or in whole
 * are granted.
 *
 * It may be possible to license this or other NetBurner software for use on
 * non-NetBurner hardware.  Please contact licensing@netburner.com for more
 * information.
 *
 * NetBurner makes no representation or warranties with respect to the
 * performance of this computer program, and specifically disclaims any
 * responsibility for any damages, special or consequential, connected with use
 * of this program.
 *
 * ----------------------------------------------------------------------------
 *
 * NetBurner, Inc.
 * 5405 Morehouse Drive
 * San Diego, CA  92121
 *
 * Information available at:  http://www.netburner.com
 * Support available at:      http://support.netburner.com
 *
 ******************************************************************************/

/*******************************************************************************
 * The system maintains a configuration record for initialization.
 ******************************************************************************/

#ifndef _SYSTEM_STORAGE_H
#define _SYSTEM_STORAGE_H


#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */


#define EXCPT_REBOOT   ( 0 )             /* Reboot after an exception */
#define EXCPT_HALT     ( 1 )             /* Halt after an exception */
#define EXCPT_QUIET    ( 2 )             /* Reboot quietly after an exception */


typedef struct
{
   unsigned long recordsize;             /* The stored size of the struct */
   unsigned long ip_Addr;                /* The device IP address */
   unsigned long ip_Mask;                /* The IP Address Mask */
   unsigned long ip_GateWay;             /* The IP address of the gateway */
   unsigned long ip_TftpServer;          /* The address of the TFTP server to load data from for debugging */
   unsigned long baud_rate;              /* The initial system baud rate */
   unsigned char wait_seconds;           /* The number of seconds to wait before booting */
   unsigned char bBoot_To_Application;   /* True if we boot to the application, false if to the monitor */
   unsigned char bException_Action;      /* What should we do when we have an exception? */
   unsigned char m_FileName[80];         /* The file name of the TFTP file to load */
   unsigned char mac_address[6];         /* The Ethernet MAC address */
   unsigned char ser_boot;               /* The serial debug port to display information */
   unsigned long ip_DNS_server;          /* The DNS server address */
   unsigned char core_mac_address[6];    /* The base unit MAC address */
   unsigned char typeof_if;
   unsigned char direct_Tx;
   unsigned long m_ExtraData[4];
   unsigned char m_bUnused[2];
   unsigned char m_Flags;                /* Bit 0 enables watchdog at boot when = '1' */
   unsigned char m_q_boot;               /* True to boot without messages */
   unsigned short checksum;              /* A checksum for this structure */
} __attribute__( ( packed ) ) ConfigRecord;


extern const ConfigRecord gConfigRec;    /* The read-only system config record */


/*******************************************************************************
 * These functions replace the system config record with the one that is passed
 * in.  It calculates a new checksum, and it ignores the MAC address.
 ******************************************************************************/

void UpdateConfigRecord( ConfigRecord *pNewRec );
ConfigRecord * RawGetConfig( int num ); 
void UpdateConfigRecord_Num( ConfigRecord *pNewRec, int num );
unsigned char isvalidcr( ConfigRecord *cr );


/**
 * *NotifyUpdatePtr() - Callback function for when config record changes.
 */
extern void  ( * NotifyUpdatePtr )( void );


/**
 * SetupDialog() - Prompt the user over stdio for IP parameters and baud rate,
 * using a setup dialog.
 */
void SetupDialog( void );


/*******************************************************************************
 * The following two functions - SaveUserParameters() and GetUserParameters()
 * - allow the user to store and recall up to 8kB of user parameters.
 ******************************************************************************/

/**
 * SaveUserParameters() - This function returns the non-zero length in bytes
 * (provided from the second input parameter) if the user parameter region was
 * programmed successfully.
 */
int SaveUserParameters( void *pCopyFrom, int len );

/**
 * GetUserParameters() - Returns a void pointer to the user parameter area,
 * which is used to access the data from the application.
 */
void * GetUserParameters( void );


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* _SYSTEM_STORAGE_H */
