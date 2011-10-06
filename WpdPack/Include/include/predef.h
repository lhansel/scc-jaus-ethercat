/* $Revision: 1.60 $ */
/* Copyright $Date: 2009/07/10 00:11:31 $ */

/******************************************************************************
 *
 * Copyright 1998-2008 NetBurner, Inc.  ALL RIGHTS RESERVED
 *   Permission is hereby granted to purchasers of NetBurner Hardware
 *   to use or modify this computer program for any use as long as the
 *   resultant program is only executed on NetBurner provided hardware.
 *
 *   No other rights to use this program or it's derivatives in part or
 *   in whole are granted.
 *
 *   It may be possible to license this or other NetBurner software for
 *        use on non NetBurner Hardware.
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

#ifndef _PREDEF_H_
#define _PREDEF_H_

/* This release  Build on: $Date: 2009/07/10 00:11:31 $ */
/* This build revison tag: $Name: Rel24_rc2 $ */

/*
 *****************************************************************************
 *
 * Features
 *
 *****************************************************************************
 */
/*
 *****************************************************************************
 *
 * Debugging
 *
 *    Use these constants to turn debug features on and off
 *       UCOS_STACKCHECK      - Stack integrity
 *       UCOS_TASKLIST        - Task diagnostics
 *       BUFFER_DIAG          - Buffer integrity and use
 *       _DEBUG_PRINT         - Enables DBPRINT Macros in release builds
 *****************************************************************************
 */
/* #define UCOS_STACKCHECK    (1) */
/* #define UCOS_TASKLIST      (1) */
/* #define BUFFER_DIAG        (1) */
/* #define _DEBUG_PRINT       (1) */

/*
 *****************************************************************************
 *
 * Multihome
 *
 *    Uncomment to enable multihoming operation
 *
 *****************************************************************************
 */
/* #define MULTIHOME */

/*
 *****************************************************************************
 *
 * Multi-home
 *
 *    Uncomment to enable UDP fragments
 *
 *****************************************************************************
 */
/* #define UDP_FRAGMENTS  ( 4 ) */

/*
 *****************************************************************************
 *
 * SSL and/or SSH support
 *
 *    Needs to be uncommented to support these features
 *
 *****************************************************************************
 */
/*
 * SSL Supported
 *    Should be defined when SSL is included in library
 *
 */
/* #define NB_SSL_SUPPORTED   ( 1 ) */

/*
 * SSH Supported
 *    Should be defined when SSH is included in library
 *
 */
/*#define NB_SSH_SUPPORTED   ( 1 ) */

/*
 * Security Random Number Support
 *
 */
#if defined( NB_SSL_SUPPORTED ) || defined( NB_SSH_SUPPORTED )
   #define GATHER_RANDOM   ( 1 )
#endif

/*
 *****************************************************************************
 *
 * User QSPI driver
 *
 *    Uncomment to enable user QSPI driver defined in qspi.h
 *       Enabling the user QSPI driver disables the joint use of the QSPI by
 *       WLAN and SD/MMC.
 *
 *****************************************************************************
 */
 #define NB_ENABLE_USER_QSPI      ( 1 ) 

/*
 *****************************************************************************
 *
 * Library Constants
 *
 *    Please do not modify any definitions below this comment.
 *
 *****************************************************************************
 */
/*
 * Library Versions
 *
 */
#define NB_VERSION_1_5
#define NB_VERSION_1_6
#define NB_VERSION_1_7
#define NB_VERSION_1_8
#define NB_VERSION_1_9
#define NB_VERSION_2_0
#define NB_MINOR_VERSION (0)
#define NB_VERSION_TEXT "2.0"

#endif   /* #ifndef _PREDEF_H_ */

