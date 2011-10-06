#ifndef _FSMF_H_
#define _FSMF_H_

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

/* //////////////////////////////////////////////////////////////////////////////////// */
/*  */
/* 	Init Functions	 */
/*  */
/* //////////////////////////////////////////////////////////////////////////////////// */

#define fsm_getversion fs_getversion
#define fsm_init fs_init
#define fsm_mountdrive fs_mountdrive
#define fsm_getfreespace fs_getfreespace

extern int fsm_format(int drivenum);

/* //////////////////////////////////////////////////////////////////////////////////// */
/*  */
/* 	Directory handler functions	 */
/*  */
/* //////////////////////////////////////////////////////////////////////////////////// */

extern int fsm_getdrive(void);
extern int fsm_chdrive(int drivenum);

extern int fsm_getcwd(char *buffer, int maxlen );
extern int fsm_getdcwd(int drivenum, char *buffer, int maxlen );

extern int fsm_mkdir(const char *dirname);
extern int fsm_chdir(const char *dirname);
extern int fsm_rmdir(const char *dirname);

/* //////////////////////////////////////////////////////////////////////////////////// */
/*  */
/* 	files functions	 */
/*  */
/* //////////////////////////////////////////////////////////////////////////////////// */

extern int fsm_rename(const char *filename,const char *newname);
extern int fsm_delete(const char *filename);

extern long fsm_filelength(const char *filename);

extern int fsm_findfirst(const char *filename,FS_FIND *find);
extern int fsm_findnext(FS_FIND *find);

extern int fsm_getpermission(const char *filename, unsigned long *psecure);
extern int fsm_setpermission(const char *filename, unsigned long secure);

/* //////////////////////////////////////////////////////////////////////////////////// */
/*  */
/* 	file read/write functions	 */
/*  */
/* //////////////////////////////////////////////////////////////////////////////////// */

extern FS_FILE *fsm_open(const char *filename,const char *mode);
extern int fsm_close(FS_FILE *filehandle);
extern long fsm_write(const void *buf,long size,long size_st,FS_FILE *filehandle);
extern long fsm_read (void *buf,long size,long size_st,FS_FILE *filehandle);
extern int fsm_seek (FS_FILE *filehandle,long offset,long whence);
extern long fsm_tell (FS_FILE *filehandle);
extern int fsm_eof(FS_FILE *filehandle);
extern int fsm_rewind(FS_FILE *filehandle);
extern int fsm_putc(int ch,FS_FILE *filehandle);
extern int fsm_getc(FS_FILE *filehandle);
extern int fsm_flush(FS_FILE *filehandle);


extern int fsm_settimedate(const char *filename,unsigned short ctime,unsigned short cdate);
extern int fsm_gettimedate(const char *filename,unsigned short *ctime,unsigned short *cdate);
extern int fsm_getlabel(int drivenum, char *label, long len);
extern int fsm_setlabel(int drivenum, const char *label);

/****************************************************************************
 *
 * internal common functions for reantrancy
 *
 ***************************************************************************/

extern int _fsm_checksemaphore(void);
extern void _fsm_releasesemaphore(void);

#ifdef __cplusplus
}
#endif

/****************************************************************************
 *
 * End of fsmf.h
 *
 ***************************************************************************/

#endif /* _FSMF_H_ */
