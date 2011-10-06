#ifndef _MMC_H_
#define _MMC_H_

/****************************************************************************
 *
 *            Copyright (c) 2003 by HCC Embedded
 *
 * This software is copyrighted by and is the sole property of
 * HCC.  All rights, title, ownership, or other interests
 * in the software remain the property of HCC.  This
 * software may only be used in accordance with the corresponding
 * license agreement.  Any unauthorized use, duplication, transmission,
 * distribution, or disclosure of this software is expressly forbidden.
 *
 * This Copyright notice may not be removed or modified without prior
 * written consent of HCC.
 *
 * HCC reserves the right to modify this software without notice.
 *
 * HCC Embedded
 * Budapest 1132
 * Victor Hugo Utca 11-15
 * Hungary
 *
 * Tel:  +36 (1) 450 1302
 * Fax:  +36 (1) 450 1303
 * http: www.hcc-embedded.com
 * email: info@hcc-embedded.com
 *
 ***************************************************************************/

#include "fat.h"
#include "mmc_dsc.h"
#include "../../../include/effs_fat/common.h"

#ifdef __cplusplus
extern "C" {
#endif
/* 
   SD/MMC shares the (Q)SPI with WLAN (wodule) at default installation
      Uncommenting NB_ENABLE_USER_QSPI in predefs.h changes the driver
      to the user (Q)SPI driver defined in qspi.h and does not then support
      using the SD/MMC and wodule in the same system.
      
      predef.h must precede this include file.
      
*/
#ifdef _PREDEF_H_
   #ifndef NB_ENABLE_USER_QSPI   
      #define SD_SHARES_SPI      ( 1 )
   #endif /* #ifndef NB_ENABLE_USER_QSPI    */
#else /* #ifndef _PREDEF_H_ */
   #error predef.h must be included before mmc_mcf.h is included
#endif /* #ifndef _PREDEF_H_ */

/* Uncomment SD_IRQ_QSPI definition to enable interrupt driven QSPI for the SD
   Card access.  This will have a small decrease in the read and write speeds but
   will signifigantly lighten the load of the CPU while reading and writing to the SD Card.
   Other tasks will function more smoothly durring file transfers with IRQs enabled here.
*/
//#define SD_IRQ_QSPI

#define SDHC_ENABLE		1	/* enable SDHC support */
#define USE_CRC			1	/* use CRC for communication */
#define CRC_ROM_TABLE	1	/* put CRC table in ROM */
extern unsigned long MMC_CRC_Enable;

int spi_init (void);			/* init SPI */
void spi_set_baudrate (unsigned long);	/* set baudrate */
unsigned long spi_get_baudrate (void);	/* get baudrate */
void spi_tx1 (unsigned char);		/* transmit 1 byte */
void spi_tx2 (unsigned short);		/* transmit 2 bytes */
void spi_tx4 (unsigned long);		/* transmit 4 bytes */
void spi_tx512 (unsigned char *);	/* transmit 512 bytes */
unsigned char spi_rx1 (void);		/* receive 1 byte */
void spi_rx512 (unsigned char *);	/* receive 512 bytes */
void spi_cs_lo (void);			/* CS low */
void spi_cs_hi (void);			/* CS high */

int get_cd (void);		/* get Card Detect state */
int get_wp (void);		/* get Write Protect state */

extern F_DRIVER *mmc_initfunc(unsigned long driver_param);

#define MMC_ERR_NOTPLUGGED -1 /* for high level */

#define F_MMC_DRIVE0 0
#define F_MMC_DRIVE1 1
#define F_MMC_DRIVE2 2
#define F_MMC_DRIVE3 3


enum {
  MMC_NO_ERROR,
  MMC_ERR_NOTINITIALIZED=101,
  MMC_ERR_INIT,
  MMC_ERR_CMD,
  MMC_ERR_STARTBIT,
  MMC_ERR_BUSY,
  MMC_ERR_CRC,
  MMC_ERR_WRITE,
  MMC_ERR_WRITEPROTECT,
  MMC_ERR_NOTAVAILABLE
};


#ifdef __cplusplus
}
#endif

/******************************************************************************
 *
 * end of mmc.h
 *
 *****************************************************************************/

#endif /* _MMC_H_ */

