#ifndef _FW_ERR_H_
#define _FW_ERR_H_

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

#ifdef __cplusplus
extern "C" {  
#endif

/****************************************************************************
 *
 * FW errorcodes
 *
 ***************************************************************************/

enum{
/*  0 */ FW_NO_ERROR,
/*  1 */ FW_ERR_INVALIDDRIVE,
/*  2 */ FW_ERR_NOTFORMATTED,
/*  3 */ FW_ERR_INVALIDDIR,  
/*  4 */ FW_ERR_INVALIDNAME,
/*  5 */ FW_ERR_NOTFOUND,
/*  6 */ FW_ERR_DUPLICATED,
/*  7 */ FW_ERR_NOMOREENTRY,
/*  8 */ FW_ERR_NOTOPEN,
/*  9 */ FW_ERR_EOF,
/* 10 */ FW_ERR_RESERVED,
/* 11 */ FW_ERR_NOTUSEABLE,
/* 12 */ FW_ERR_LOCKED,
/* 13 */ FW_ERR_ACCESSDENIED,
/* 14 */ FW_ERR_NOTEMPTY,
/* 15 */ FW_ERR_INITFUNC,
/* 16 */ FW_ERR_CARDREMOVED,
/* 17 */ FW_ERR_ONDRIVE,
/* 18 */ FW_ERR_INVALIDSECTOR,
/* 19 */ FW_ERR_READ,
/* 20 */ FW_ERR_WRITE,
/* 21 */ FW_ERR_INVALIDMEDIA,
/* 22 */ FW_ERR_BUSY,
/* 23 */ FW_ERR_WRITEPROTECT,
/* 24 */ FW_ERR_INVFATTYPE,
/* 25 */ FW_ERR_MEDIATOOSMALL,
/* 26 */ FW_ERR_MEDIATOOLARGE,
/* 27 */ FW_ERR_NOTSUPPSECTORSIZE,
/* 28 */ FW_ERR_UNKNOWN,
/* 29 */ FW_ERR_DRVALREADYMNT, 
/* 30 */ FW_ERR_TOOLONGNAME,	  
/* 31 */ FW_ERR_NOTFORREAD
};

/****************************************************************************
 *
 * FS FAT errorcodes
 *
 ***************************************************************************/

#define F_NO_ERROR               FW_NO_ERROR
#define F_ERR_INVALIDDRIVE       FW_ERR_INVALIDDRIVE
#define F_ERR_NOTFORMATTED       FW_ERR_NOTFORMATTED
#define F_ERR_INVALIDDIR         FW_ERR_INVALIDDIR  
#define F_ERR_INVALIDNAME        FW_ERR_INVALIDNAME
#define F_ERR_NOTFOUND           FW_ERR_NOTFOUND
#define F_ERR_DUPLICATED         FW_ERR_DUPLICATED
#define F_ERR_NOMOREENTRY        FW_ERR_NOMOREENTRY
#define F_ERR_NOTOPEN            FW_ERR_NOTOPEN
#define F_ERR_EOF                FW_ERR_EOF
#define F_ERR_RESERVED           FW_ERR_RESERVED
#define F_ERR_NOTUSEABLE         FW_ERR_NOTUSEABLE
#define F_ERR_LOCKED             FW_ERR_LOCKED
#define F_ERR_ACCESSDENIED       FW_ERR_ACCESSDENIED
#define F_ERR_NOTEMPTY           FW_ERR_NOTEMPTY
#define F_ERR_INITFUNC           FW_ERR_INITFUNC
#define F_ERR_CARDREMOVED        FW_ERR_CARDREMOVED
#define F_ERR_ONDRIVE            FW_ERR_ONDRIVE
#define F_ERR_INVALIDSECTOR      FW_ERR_INVALIDSECTOR
#define F_ERR_READ               FW_ERR_READ
#define F_ERR_WRITE              FW_ERR_WRITE
#define F_ERR_INVALIDMEDIA       FW_ERR_INVALIDMEDIA
#define F_ERR_BUSY               FW_ERR_BUSY
#define F_ERR_WRITEPROTECT       FW_ERR_WRITEPROTECT
#define F_ERR_INVFATTYPE         FW_ERR_INVFATTYPE
#define F_ERR_MEDIATOOSMALL      FW_ERR_MEDIATOOSMALL
#define F_ERR_MEDIATOOLARGE      FW_ERR_MEDIATOOLARGE
#define F_ERR_NOTSUPPSECTORSIZE  FW_ERR_NOTSUPPSECTORSIZE


/****************************************************************************
 *
 * FS STD errorcodes
 *
 ***************************************************************************/

#define FS_NOERR			  FW_NO_ERROR 
#define FS_INVALIDDRIVE   FW_ERR_INVALIDDRIVE 
#define FS_INVALIDDIR	  FW_ERR_INVALIDDIR 
#define FS_INVALIDNAME	  FW_ERR_INVALIDNAME 
#define FS_NOMOREENTRY	  FW_ERR_NOMOREENTRY 
#define FS_DRIVEERROR	  FW_ERR_ONDRIVE 
#define FS_DUPLICATED	  FW_ERR_DUPLICATED 
#define FS_NOTFOUND		  FW_ERR_NOTFOUND 
#define FS_NOTEMPTY		  FW_ERR_NOTEMPTY 
#define FS_NOTUSEABLE	  FW_ERR_NOTUSEABLE 
#define FS_NOTFORREAD	  FW_ERR_NOTFORREAD
#define FS_NOTOPEN		  FW_ERR_NOTOPEN 
#define FS_BUSY			  FW_ERR_BUSY 
#define FS_NOTFORMATTED   FW_ERR_NOTFORMATTED 
#define FS_NOPERMISSION   FW_ERR_ACCESSDENIED 
#define FS_DRVALREADYMNT  FW_ERR_DRVALREADYMNT 
#define FS_TOOLONGNAME	  FW_ERR_TOOLONGNAME	   

#ifdef __cplusplus
}
#endif

#endif /* _FWERR_H_ */

