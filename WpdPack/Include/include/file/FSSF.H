#ifndef _FSSF_H_
#define _FSSF_H_

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
/*  typedefs  */
/*  */
/* //////////////////////////////////////////////////////////////////////////////////// */

typedef struct {
char cwd[FS_MAXPATH];		/* current working folder in this volume */
} FSS_CWD;                 /* structure for current working folder */

typedef struct {
unsigned long secure;       /* secure code for user */
int curdrive;					 /* current drive */
FSS_CWD cwds[FS_MAXVOLUME]; /* individual working folders */
} FSS_USER;                 /* structure for user */

#define FSS_SEC_RD     0x01
#define FSS_SEC_WR     0x02
#define FSS_SEC_MOD    0x04
#define FSS_SEC_OWNER  0x08

#define FSS_SEC_ALLRD    0x11111111
#define FSS_SEC_ALLWR    0x22222222
#define FSS_SEC_ALLMOD   0x44444444
#define FSS_SEC_ALLOWNER 0x88888888

#define FSS_SUPERVISOR 0xffffffff 

/* //////////////////////////////////////////////////////////////////////////////////// */
/*  */
/* 	Init Functions	 */
/*  */
/* //////////////////////////////////////////////////////////////////////////////////// */

#define fss_getversion fs_getversion
#define fss_init fs_init
#define fss_mountdrive fs_mountdrive
#define fss_format fs_format
#define fss_getfreespace fs_getfreespace

/* //////////////////////////////////////////////////////////////////////////////////// */
/*  */
/* 	Directory handler functions	 */
/*  */
/* //////////////////////////////////////////////////////////////////////////////////// */

extern int fss_getdrive(FSS_USER *fsuser);
extern int fss_chdrive(FSS_USER *fsuser,int drivenum);

extern int fss_getcwd(FSS_USER *fsuser,char *buffer, int maxlen );
extern int fss_getdcwd(FSS_USER *fsuser,int drivenum, char *buffer, int maxlen );

extern int fss_mkdir(FSS_USER *fsuser,const char *dirname);
extern int fss_chdir(FSS_USER *fsuser,const char *dirname);
extern int fss_rmdir(FSS_USER *fsuser,const char *dirname);

/* //////////////////////////////////////////////////////////////////////////////////// */
/*  */
/* 	files functions	 */
/*  */
/* //////////////////////////////////////////////////////////////////////////////////// */

extern int fss_rename(FSS_USER *fsuser,const char *filename, const char *newname);
extern int fss_delete(FSS_USER *fsuser,const char *filename);

extern long fss_filelength(FSS_USER *fsuser,const char *filename);

extern int fss_findfirst(FSS_USER *fsuser,const char *filename,FS_FIND *find);
extern int fss_findnext(FSS_USER *fsuser,FS_FIND *find);

extern int fss_setpermission(FSS_USER *fsuser, const char *filename, unsigned long secure);
extern int fss_getpermission(FSS_USER *fsuser, const char *filename, unsigned long *psecure);

/* //////////////////////////////////////////////////////////////////////////////////// */
/*  */
/* 	file read/write functions	 */
/*  */
/* //////////////////////////////////////////////////////////////////////////////////// */

extern FS_FILE *fss_open(FSS_USER *fsuser,const char *filename,const char *mode);
extern int fss_close(FS_FILE *filehandle);
extern long fss_write(const void *buf,long size,long size_st,FS_FILE *filehandle);
extern long fss_read (void *buf,long size,long size_st,FS_FILE *filehandle);
extern int fss_seek (FS_FILE *filehandle,long offset,long whence);
extern long fss_tell (FS_FILE *filehandle);
extern int fss_eof(FS_FILE *filehandle);
extern int fss_rewind(FS_FILE *filehandle);
extern int fss_putc(int ch,FS_FILE *filehandle);
extern int fss_getc(FS_FILE *filehandle);
extern int fss_flush(FS_FILE *filehandle);


extern int fss_settimedate(FSS_USER *fsuser,const char *filename,unsigned short ctime,unsigned short cdate);
extern int fss_gettimedate(FSS_USER *fsuser,const char *filename,unsigned short *ctime,unsigned short *cdate);

extern int fss_getlabel(int drivenum, char *label, long len);
extern int fss_setlabel(int drivenum, const char *label);

#ifdef __cplusplus
}
#endif

/****************************************************************************
 *
 * End of fssf.h
 *
 ***************************************************************************/

#endif /* _FSSF_H_ */

