#ifndef _FSSMF_H_
#define _FSSMF_H_

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

#define fssm_getversion fs_getversion
#define fssm_init fs_init
#define fssm_mountdrive fs_mountdrive
#define fssm_getfreespace fs_getfreespace

extern int fssm_format(FSS_USER *fsuser,int drivenum);

/* //////////////////////////////////////////////////////////////////////////////////// */
/*  */
/* 	Directory handler functions	 */
/*  */
/* //////////////////////////////////////////////////////////////////////////////////// */

extern int fssm_getdrive(FSS_USER *fsuser);
extern int fssm_chdrive(FSS_USER *fsuser,int drivenum);

extern int fssm_getcwd(FSS_USER *fsuser,char *buffer, int maxlen );
extern int fssm_getdcwd(FSS_USER *fsuser,int drivenum, char *buffer, int maxlen );

extern int fssm_mkdir(FSS_USER *fsuser,const char *dirname);
extern int fssm_chdir(FSS_USER *fsuser,const char *dirname);
extern int fssm_rmdir(FSS_USER *fsuser,const char *dirname);

/* //////////////////////////////////////////////////////////////////////////////////// */
/*  */
/* 	files functions	 */
/*  */
/* //////////////////////////////////////////////////////////////////////////////////// */
 
extern int fssm_rename(FSS_USER *fsuser,const char *filename, const char *newname);
extern int fssm_delete(FSS_USER *fsuser,const char *filename);

extern long fssm_filelength(FSS_USER *fsuser,const char *filename);

extern int fssm_findfirst(FSS_USER *fsuser,const char *filename,FS_FIND *find);
extern int fssm_findnext(FSS_USER *fsuser,FS_FIND *find);

extern int fssm_setpermission(FSS_USER *fsuser, const char *filename, unsigned long secure);
extern int fssm_getpermission(FSS_USER *fsuser, const char *filename, unsigned long *psecure);

/* //////////////////////////////////////////////////////////////////////////////////// */
/*  */
/* 	file read/write functions	 */
/*  */
/* //////////////////////////////////////////////////////////////////////////////////// */

extern FS_FILE *fssm_open(FSS_USER *fsuser,const char *filename,const char *mode);
extern int fssm_close(FS_FILE *filehandle);
extern long fssm_write(const void *buf,long size,long size_st,FS_FILE *filehandle);
extern long fssm_read (void *buf,long size,long size_st,FS_FILE *filehandle);
extern int fssm_seek (FS_FILE *filehandle,long offset,long whence);
extern long fssm_tell (FS_FILE *filehandle);
extern int fssm_eof(FS_FILE *filehandle);
extern int fssm_rewind(FS_FILE *filehandle);
extern int fssm_putc(int ch,FS_FILE *filehandle);
extern int fssm_getc(FS_FILE *filehandle);
extern int fssm_flush(FS_FILE *filehandle);


extern int fssm_settimedate(FSS_USER *fsuser,const char *filename,unsigned short ctime,unsigned short cdate);
extern int fssm_gettimedate(FSS_USER *fsuser,const char *filename,unsigned short *ctime,unsigned short *cdate);
extern int fssm_getlabel(int drivenum, char *label, long len);
extern int fssm_setlabel(int drivenum, const char *label);

#ifdef __cplusplus
}
#endif

/****************************************************************************
 *
 * End of fssmf.h
 *
 ***************************************************************************/

#endif /* _FSSMF_H_ */
