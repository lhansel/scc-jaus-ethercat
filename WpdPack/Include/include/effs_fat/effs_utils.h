/*-------------------------------------------------------------------
 EFFS, Embedded FAT File System Utilities
 -------------------------------------------------------------------*/

#ifndef _EFFS_UTILS_H_
#define _EFFS_UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif


/*-------------------------------------------------------------------
 fgets()

  Description
  Reads at most len-1 characters from fp until a newline is found. 
  The characters including the newline (0x0A) are stored in buf. 
  The buffer is terminated with a NULL.

  Returns
  fgets returns the buffer passed to it, with the data filled in. 
  If end of file occurs with some data already accumulated, the 
  data is returned with no other indication. If no data are read, 
  NULL is returned instead.
  
  Note that fgets returns all of the data, while gets removes the 
  trailing newline (with no indication that it has done so.)
 ------------------------------------------------------------------*/
extern char * f_fgets( char *buf, int len, F_FILE *fp );


/*-------------------------------------------------------------------
 int fputs(const char *s, FILE *fp);

 Description:
 fputs writes the string at s (but without the trailing null) to 
 the sprcified file, fp.

 Returns:
  If successful, the result is 0; otherwise, the result is EOF.

 Portability
  ANSII C requires fputs, but does not specify that the result 
  on success must be 0; any non-negative value is permitted.
 ------------------------------------------------------------------*/
extern int f_fputs(const char *s, F_FILE *fp);



/*-------------------------------------------------------------------
 EFFS fprintf implementation
 -------------------------------------------------------------------*/
extern int f_fprintf(F_FILE* fp, const char *format, ... );


#ifdef __cplusplus
}
#endif


#endif /* _EFFS_UTILS_H_ */



