/* $Revision: 1.1 $ */
/* Copyright $Date: 2008/04/29 20:28:16 $ */  

/******************************************************************************
 *
 * Copyright 2008 NetBurner, Inc.  ALL RIGHTS RESERVED
 *   Permission is hereby granted to purchasers of NetBurner Hardware
 *   to use or modify this computer program for any use as long as the
 *   resultant program is only executed on NetBurner provided hardware.
 *
 *   No other rights to use this program or it's derivatives in part or
 *   in whole are granted.
 *
 *   It may be possible to license this or other NetBurner software for
 *   use on non-NetBurner Hardware.
 *   Please contact Licensing@Netburner.com for more information.
 *
 *   NetBurner makes no representation or warranties
 *   with respect to the performance of this computer program, and
 *   specifically disclaims any responsibility for any damages,
 *   special or consequential, connected with the use of this program.
 *
 *---------------------------------------------------------------------
 * NetBurner, Inc.
 * 5405 Morehouse Dr.
 * San Diego, Ca. 92121
 *
 * information available at:  http://www.netburner.com
 * E-Mail info@netburner.com
 *
 * Support is available: E-Mail support@netburner.com
 *
 *****************************************************************************/

#ifndef _DEBUG_ALLOC_H_
#define _DEBUG_ALLOC_H_

/*
 ******************************************************************************
 *
 * Definitions
 *
 ******************************************************************************
 */
/*
 * Memory Allocation Debugging
 *    Should be defined if needed, unnecessary burden to release code
 *
 */
/* #define NB_DEBUG_ALLOC_SUPPORTED   ( 1 ) */

/*
 * Memory Allocation Features
 *
 */
/* All activities are displayed with iprintf */
/* #define NB_DEBUG_ALLOC_VERBOSE         ( 1 ) */

/* Log all activities as well */
/* #define NB_DEBUG_ALLOC_LOG_ALL         ( 1 ) */

/* 
 * Entry log size
 *    Size of allocLogEntry per entry
 *    Additional two for ...LOG_ALL
 *    Overflow is reported but the process continues 
 */
#define NB_DEBUG_ALLOC_LOG_SIZE        ( 2048 )

/* Guardian size in bytes before and after returned allocated memory */
#define NB_DEBUG_ALLOC_GUARD_SIZE      ( 64 )

/* Guardian value filled and checked */
#define NB_DEBUG_ALLOC_GUARD_VALUE     ( 0xA5 )

#ifdef __cplusplus 
extern "C" {
#endif
/*
 ******************************************************************************
 *
 * Debug malloc, calloc, realloc and free "C" Library Interface
 *
 ******************************************************************************
 */

/*
 ******************************************************************************
 
   Debug logger and optionally guardians:
      malloc
      calloc
      realloc
      free

   Parameters:
      byteCount            - Memory needed in bytes
      elementCount         - Elements of byteCount bytes (calloc)
      ptr                  - Previously allocated memory
      caller               - Function calling, best choice __FUNCTION__
      line                 - Line number of call, best choice __LINE__
   
   Return:
      > 0 Address of allocated memory, 0 problems
   
   Notes:
      calloc zeros memory allocated
      realloc can extend or truncate memory, contents are the same as ptr
      realloc if problems does not change or deallocate memory
      Will not free a pointer not logged
   
 ******************************************************************************
 */
void *mallocDebug( size_t byteCount, const char* caller, int line );
void *callocDebug( size_t elementCount, size_t byteCount, const char* caller, 
      int line );
void *reallocDebug( void *ptr, size_t byteCount, const char* caller, int line );
void freeDebug( void *ptr, const char* caller, int line );

/*
 ******************************************************************************
 
   Display using iprintf log and all allocated log

   Parameters:
      None
   
   Return:
      None
   
   Notes:
      None
   
 ******************************************************************************
 */
void printAllocDebugLog( void );
void printAllocDebugLogAll( void );


/*
 ******************************************************************************
 *
 * Definitions
 *
 ******************************************************************************
 */
#ifdef NB_DEBUG_ALLOC_SUPPORTED
   #define NBMALLOC( bYtEcOuNt ) \
         mallocDebug( bYtEcOuNt, __FUNCTION__, __LINE__ );
   #define NBCALLOC( eLeMeNtCoUnT, bYtEcOuNt ) \
         callocDebug( eLeMeNtCoUnT, bYtEcOuNt, __FUNCTION__, __LINE__ );
   #define NBREALLOC( pTr, bYtEcOuNt ) \
         reallocDebug( pTr, bYtEcOuNt, __FUNCTION__, __LINE__ );
   #define NBFREE( pTr ) \
         freeDebug( pTr, __FUNCTION__, __LINE__ );
#else /* #ifdef NB_DEBUG_ALLOC_SUPPORTED */
   #define NBMALLOC( bYtEcOuNt ) \
         malloc( bYtEcOuNt );
   #define NBCALLOC( eLeMeNtCoUnT, bYtEcOuNt ) \
         calloc( eLeMeNtCoUnT, bYtEcOuNt );
   #define NBREALLOC( pTr, bYtEcOuNt ) \
         realloc( pTr, bYtEcOuNt );
   #define NBFREE( pTr ) \
         free( pTr );
#endif /* #ifdef NB_DEBUG_ALLOC_SUPPORTED */

#ifdef __cplusplus
};
#endif
#endif   /* #ifndef _DEBUG_ALLOC_H_ */
