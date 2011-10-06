#ifndef _FSF_H_
#define _FSF_H_

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

#include "file/fwerr.h"


/* //////////////////////////////////////////////////////////////////////////////////// 
  
  Reentrancy definition
  
 //////////////////////////////////////////////////////////////////////////////////// */

#define FS_REENTRANCY 0
#define FS_SECURE 0

#if (FS_REENTRANCY && (!FS_SECURE))
#define FS_MULTICWD  1 /* defines multi current working directory on reentrancy */
#else
#define FS_MULTICWD  0 /* don't change this value here*/
#endif

#if FS_MULTICWD
#define FS_MAXTASK   10     /* maximum number of task */
#endif


#include "fsm.h"

/* //////////////////////////////////////////////////////////////////////////////////// */
/*  */
/* 	Init Functions	 */
/*  */
/* //////////////////////////////////////////////////////////////////////////////////// */

extern char *fs_getversion(void);
extern void fs_init(void);
extern int fs_mountdrive(int drivenum,void *buffer,long buffsize,FS_DRVMOUNT mountfunc,FS_PHYGETID phyfunc);
extern int fs_unmountdrive (int drvnum);
extern int fs_format(int drivenum);
extern int fs_getfreespace(int drivenum, FS_SPACE *space);

/* //////////////////////////////////////////////////////////////////////////////////// */
/*  */
/* 	Directory handler functions	 */
/*  */
/* //////////////////////////////////////////////////////////////////////////////////// */

extern int fs_getdrive(void);
extern int fs_chdrive(int drivenum);

extern int fs_getcwd(char *buffer, int maxlen );
extern int fs_getdcwd(int drivenum, char *buffer, int maxlen );

extern int fs_mkdir(const char *dirname);
extern int fs_chdir(const char *dirname);
extern int fs_rmdir(const char *dirname);

extern int fs_setlabel(int drivenum, const char *label);
extern int fs_getlabel(int drivenum, char *label, long len);

/* //////////////////////////////////////////////////////////////////////////////////// */
/*  */
/* 	files functions	 */
/*  */
/* //////////////////////////////////////////////////////////////////////////////////// */

extern int fs_rename(const char *filename,const char *newname);
extern int fs_delete(const char *filename);

extern long fs_filelength(const char *filename);

extern int fs_findfirst(const char *filename,FS_FIND *find);
extern int fs_findnext(FS_FIND *find);

/* //////////////////////////////////////////////////////////////////////////////////// */
/*  */
/* 	file read/write functions	 */
/*  */
/* //////////////////////////////////////////////////////////////////////////////////// */

extern FS_FILE *fs_open(const char *filename,const char *mode);
extern int fs_close(FS_FILE *filehandle);
extern long fs_write(const void *buf,long size,long size_st,FS_FILE *filehandle);
extern long fs_read(void *buf,long size,long size_st,FS_FILE *filehandle);
extern int fs_seek(FS_FILE *filehandle,long offset,long whence);
extern long fs_tell(FS_FILE *filehandle);
extern int fs_eof(FS_FILE *filehandle);
extern int fs_rewind(FS_FILE *filehandle);
extern int fs_putc(int ch,FS_FILE *filehandle);
extern int fs_getc(FS_FILE *filehandle);
extern int fs_flush(FS_FILE *filehandle);

extern int fs_settimedate(const char *filename,unsigned short ctime,unsigned short cdate);
extern int fs_gettimedate(const char *filename,unsigned short *ctime,unsigned short *cdate);

/* Beginning of file */
#ifdef SEEK_SET
#define FS_SEEK_SET SEEK_SET
#else
#define FS_SEEK_SET 0
#endif

/* Current position of file pointer */
#ifdef SEEK_CUR
#define FS_SEEK_CUR SEEK_CUR
#else
#define FS_SEEK_CUR 1
#endif

/* End of file */
#ifdef SEEK_END
#define FS_SEEK_END SEEK_END
#else
#define FS_SEEK_END 2
#endif

extern int fs_getpermission(const char *filename, unsigned long *psecure);
extern int fs_setpermission(const char *filename, unsigned long secure);


/* //////////////////////////////////////////////////////////////////////////////////// */
/*  */
/*  internal common functions for secure parts  */
/*  */
/* //////////////////////////////////////////////////////////////////////////////////// */

extern int _fs_flush(FS_VOLUMEINFO *vi);
extern int _fs_getvolumeinfo(int drivenum,FS_VOLUMEINFO **pvi);
extern int _fs_findpath(FS_NAME *fsname);
extern int _fs_findfile(FS_VOLUMEINFO *vi,char *name,unsigned short dirnum,unsigned short *pdirnum);
extern int _fs_addentry(FS_NAME *fsname,FS_DIRENTRY **pde);
extern int _fs_find(FS_NAME *fsname,FS_DIRENTRY **pde,unsigned short *pdirnum);
extern int _fs_findfilewc(FS_VOLUMEINFO *vi,char *name,unsigned short dirnum,unsigned short *pdirnum,unsigned short startpos);
extern void _fs_setdiscsectors(FS_VOLUMEINFO *vi,unsigned short sector);
extern int _fs_getsector (FS_VOLUMEINFO *vi,long secnum,void *data,long offset,long datalen);
extern void _fs_removedename(FS_VOLUMEINFO *vi, FS_DIRENTRY *de);
extern int _fs_setdename(char *s, FS_VOLUMEINFO *vi, FS_DIRENTRY *de);
extern void _fs_getdename(char *s, FS_VOLUMEINFO *vi, FS_DIRENTRY *de);
extern int _fs_namecheckwc(const char *name,const char *s);
extern int _fs_copychainintomirror(FS_VOLUMEINFO *vi,FS_FILEINT *f,FS_DIRENTRY *de);
extern void _fs_cleanupfile(FS_VOLUMEINFO *vi, FS_FILEINT *f);
extern int _fs_fseek(FS_FILEINT *f,long offset);
extern int _fs_checkfilelock(FS_VOLUMEINFO *vi,FS_DIRENTRY *de,long m_mode);

extern FS_FILESYSTEM fs_filesystem;

/* //////////////////////////////////////////////////////////////////////////////////// */
/*  */
/*  reentrancy function definitions  */
/*  */
/* //////////////////////////////////////////////////////////////////////////////////// */

#if (!FS_REENTRANCY)

#define fl_getversion fs_getversion
#define fl_init fs_init
#define fl_mountdrive(drivenum,buffer,buffsize,mountfunc,phyfunc) fs_mountdrive(drivenum,buffer,buffsize,mountfunc,phyfunc)
#define fl_unmountdrive(drvnum) fs_unmountdrive (drvnum)
#define fl_format(drivenum) fs_format(drivenum)
#define fl_getfreespace(drivenum,space) fs_getfreespace(drivenum,space)
#define fl_getdrive fs_getdrive
#define fl_chdrive(drivenum) fs_chdrive(drivenum)
#define fl_getcwd(buffer,maxlen) fs_getcwd(buffer,maxlen)
#define fl_getdcwd(drivenum,buffer,maxlen) fs_getdcwd(drivenum,buffer,maxlen)
#define fl_mkdir(dirname) fs_mkdir(dirname)
#define fl_chdir(dirname) fs_chdir(dirname)
#define fl_rmdir(dirname) fs_rmdir(dirname)
#define fl_setlabel(drivenum,label) fs_setlabel(drivenum,label)
#define fl_getlabel(drivenum,label,len) fs_getlabel(drivenum,label,len)
#define fl_rename(filename,newname) fs_rename(filename,newname)
#define fl_delete(filename) fs_delete(filename)
#define fl_filelength(filename) fs_filelength(filename)
#define fl_findfirst(filename,find) fs_findfirst(filename,find)
#define fl_findnext(find) fs_findnext(find)
#define fl_open(filename,mode) fs_open(filename,mode)
#define fl_close(filehandle) fs_close(filehandle)
#define fl_write(buf,size,size_st,filehandle) fs_write(buf,size,size_st,filehandle)
#define fl_read(buf,size,size_st,filehandle) fs_read(buf,size,size_st,filehandle)
#define fl_seek(filehandle,offset,whence) fs_seek(filehandle,offset,whence)
#define fl_tell(filehandle) fs_tell(filehandle)
#define fl_eof(filehandle) fs_eof(filehandle)
#define fl_rewind(filehandle) fs_rewind(filehandle)
#define fl_putc(ch,filehandle) fs_putc(ch,filehandle)
#define fl_getc(filehandle) fs_getc(filehandle)
#define fl_flush(filehandle) fs_flush(filehandle)
#define fl_settimedate(filename,ctime,cdate) fs_settimedate(filename,ctime,cdate)
#define fl_gettimedate(filename,pctime,pcdate) fs_gettimedate(filename,pctime,pcdate)
#define fl_getpermission(filename,psecure) fs_getpermission(filename,psecure)
#define fl_setpermission(filename,secure) fs_setpermission(filename,secure)

#else

#include "fsmf.h"

#define fl_getversion fsm_getversion
#define fl_init fsm_init
#define fl_mountdrive(drivenum,buffer,buffsize,mountfunc,phyfunc) fsm_mountdrive(drivenum,buffer,buffsize,mountfunc,phyfunc)
#define fl_unmountdrive(drvnum) fsm_unmountdrive (drvnum)
#define fl_format(drivenum) fsm_format(drivenum)
#define fl_getfreespace(drivenum,space) fsm_getfreespace(drivenum,space)
#define fl_getdrive fsm_getdrive
#define fl_chdrive(drivenum) fsm_chdrive(drivenum)
#define fl_getcwd(buffer,maxlen) fsm_getcwd(buffer,maxlen)
#define fl_getdcwd(drivenum,buffer,maxlen) fsm_getdcwd(drivenum,buffer,maxlen)
#define fl_mkdir(dirname) fsm_mkdir(dirname)
#define fl_chdir(dirname) fsm_chdir(dirname)
#define fl_rmdir(dirname) fsm_rmdir(dirname)
#define fl_setlabel(drivenum,label) fsm_setlabel(drivenum,label)
#define fl_getlabel(drivenum,label,len) fsm_getlabel(drivenum,label,len)
#define fl_rename(filename,newname) fsm_rename(filename,newname)
#define fl_delete(filename) fsm_delete(filename)
#define fl_filelength(filename) fsm_filelength(filename)
#define fl_findfirst(filename,find) fsm_findfirst(filename,find)
#define fl_findnext(find) fsm_findnext(find)
#define fl_open(filename,mode) fsm_open(filename,mode)
#define fl_close(filehandle) fsm_close(filehandle)
#define fl_write(buf,size,size_st,filehandle) fsm_write(buf,size,size_st,filehandle)
#define fl_read(buf,size,size_st,filehandle) fsm_read(buf,size,size_st,filehandle)
#define fl_seek(filehandle,offset,whence) fsm_seek(filehandle,offset,whence)
#define fl_tell(filehandle) fsm_tell(filehandle)
#define fl_eof(filehandle) fsm_eof(filehandle)
#define fl_rewind(filehandle) fsm_rewind(filehandle)
#define fl_putc(ch,filehandle) fsm_putc(ch,filehandle)
#define fl_getc(filehandle) fsm_getc(filehandle)
#define fl_flush(filehandle) fsm_flush(filehandle)
#define fl_settimedate(filename,ctime,cdate) fsm_settimedate(filename,ctime,cdate)
#define fl_gettimedate(filename,pctime,pcdate) fsm_gettimedate(filename,pctime,pcdate)
#define fl_getpermission(filename,psecure) fsm_getpermission(filename,psecure)
#define fl_setpermission(filename,secure) fsm_setpermission(filename,secure)

#endif


#ifdef __cplusplus
}
#endif

/****************************************************************************
 *
 * End of fsf.h
 *
 ***************************************************************************/

#endif /* _FSF_H_ */
