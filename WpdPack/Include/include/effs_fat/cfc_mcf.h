#ifndef _CFC_IDE_H_
#define _CFC_IDE_H_

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

#include <effs_fat\fat.h>

#ifdef __cplusplus
extern "C" {
#endif

#define HCC_HW
#define F_CFC_DRIVE0 0
#define F_CFC_DRIVE1 1

/*****************************************************************************/
#define CFC_ERR_NOTPLUGGED -1 /* for high level */

enum {
/* 0 */  CFC_NO_ERROR,  
/*101*/  CFC_ERR_BUSY_ATCYL=101,
/*102*/  CFC_ERR_BUSY_ATDRQ,
/*103*/  CFC_ERR_BUSY_ATCMD,
/*104*/  CFC_ERR_TIMEOUT,
/*105*/  CFC_ERR_STATE,
/*106*/  CFC_ERR_SECCOU,
/*107*/  CFC_ERR_NOTAVAILABLE
};

/******************************************************************************
 *
 *  Big endian definitions
 *
 *****************************************************************************/

#define MOTOWORD(x) ( (((x)>>8) & 0x00ff) | (((x)<<8) & 0xff00) )

/******************************************************************************
 *
 *  Functions
 *
 *****************************************************************************/

//extern int cfc_initfunc(unsigned long driver_param); /* driver init function */
extern F_DRIVER *cfc_initfunc(unsigned long driver_param); /* driver init function */
#define CFC_PAGE_SIZE 512  /* CFC page size in bytes */

#ifdef __cplusplus
}
#endif

/******************************************************************************
 *
 * end cfc_ide.h
 *
 *****************************************************************************/

#endif /* _CFC_IDE_H_ */

