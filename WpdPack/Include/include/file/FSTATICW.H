#ifndef _FSSTATIC_H_
#define _FSSTATIC_H_

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

#include "file/fsf.h" 


#ifdef __cplusplus
extern "C" {  
#endif

#define FS_STATIC_DISTANCE  1024	/* distance between statically used and free block */
#define FS_STATIC_PERIOD	1024	/* period, when to check static distance */

extern int fs_staticwear(int drvnum);   /* for normal */
extern int fsm_staticwear(int drvnum);  /* for multitask */
extern int fss_staticwear(int drvnum);  /* for secure */
extern int fssm_staticwear(int drvnum); /* for secure multitask */

#ifdef __cplusplus
}
#endif

/****************************************************************************
 *
 * End of fstatic.h
 *
 ***************************************************************************/

#endif /* _FSSTATIC_H_ */


