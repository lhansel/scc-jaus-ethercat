/* $Revision: 1.38 $ */
/* Copyright $Date: 2009/11/13 11:16:45 $ */  

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

#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#define TICK_IRQ_LEVEL (5)      /* System clock IRQ level */
#define SERIAL_IRQ_LEVEL (3)
#define SERIAL_VECTOR_BASE (64)

#define TICKS_PER_SECOND (20)   /* System clock tick */

/* Ethernet buffer defines */
#define ETHER_BUFFER_SIZE 1548
#define ETH_MAX_SIZE  (1500)
#define ETH_MIN_SIZE  (46)
#define MAX_UDPDATA (ETH_MAX_SIZE-(20+8+14))

#define SERIAL_TX_BUFFERS (2) /* ETHERN_BUFFER_SIZE = bytes of serial TX fifo */
#define SERIAL_RX_BUFFERS (2) /* ETHERN_BUFFER_SIZE = bytes of serial RX fifo */
#define stdin_buffer_size (200)

#define OS_MAX_TASKS    20 /* Max number of system tasks */

/*
 ******************************************************************************
 *
 * System task priorities
 *
 *    Restating the uC/OS RTOS Library document (uCOSLibrary.pdf)
 *       Lowest priority is 63, 1 is the highest.
 *       There can only be one task at each priority level.
 *       Idle task is created at priority 63.
 *
 *    UserMain is created at priority 10. It is recommended and is supported by
 *       examples and default projects that a call to 
 *          OSChangePrio( MAIN_PRIO );
 *       be made to lower the priority to the range recommended for the main 
 *       application.
 *
 *    Factory applications use priorities 46 through 56.
 *
 *    Netburner Runtime library support and driver tasks use 36 through 45.
 *
 *    Care should be taken in use of priorities it can affect reliability and 
 *       performance.
 *
 ******************************************************************************
 */
 
/* Recommend UserMain priority */ 
#define MAIN_PRIO          (50)

/* Runtime library driver and support task priorities */ 
#define HTTP_PRIO          (45)
#define PPP_PRIO           (44)
#define WIFI_TASK_PRIO     (41)
#define TCP_PRIO           (40)
#define IP_PRIO            (39)
#define ETHER_SEND_PRIO    (38)

/* Features */
#ifdef NB_SSH_SUPPORTED
   /* SSH server must be lower than main for progress displays */
   #define SSH_TASK_PRIORITY  (56)
#endif /* #ifdef NB_SSH_SUPPORTED */

/*
 ******************************************************************************
 *
 * Stack size definitions
 *
 *    SSH requires larger stacks for session key generation see predef.h
 *
 ******************************************************************************
 */
#ifdef NB_SSH_SUPPORTED
   #define MAIN_TASK_STK_SIZE    (3072)
   #define IP_STK_SIZE           (3072)
   #define TCP_STK_SIZE          (3072)
   #define HTTP_STK_SIZE         (3072)
   #define IDLE_STK_SIZE         (2048)
   #define ETHER_SEND_STK_SIZE   (2048)
   #define PPP_STK_SIZE          (2048)
   #define USER_TASK_STK_SIZE    (3072)
#else /* #ifdef NB_SSH_SUPPORTED */
   #define MAIN_TASK_STK_SIZE    (2048)
   #define IP_STK_SIZE           (2048)
   #define TCP_STK_SIZE          (2048)
   #define HTTP_STK_SIZE         (2048)
   #define IDLE_STK_SIZE         (2048)
   #define ETHER_SEND_STK_SIZE   (2048)
   #define PPP_STK_SIZE          (2048)
   #define USER_TASK_STK_SIZE    (2048)
#endif /* #ifdef NB_SSH_SUPPORTED */



/* TCP definitions */
#define DEFAULT_TCP_MSS (512)
#define DEFAULT_TCP_RTTVAR ((TICKS_PER_SECOND*3)/4)  /*See RFC 1122 for a 50msec tick 60 ticks=3 sec 4*15=60 (The 4 comes from stevens Vol1-300) */
#define TCP_CONN_TO (75 * TICKS_PER_SECOND)    /* 75 seconds Min  */
#define TCP_ACK_TICK_DLY (TICKS_PER_SECOND /5) /* 200 msec delayed ACK timer */
#define DEFAULT_INITAL_RTO (TICKS_PER_SECOND*3)
#define TCP_MAX_RTO (64 * TICKS_PER_SECOND)
#define TCP_MIN_RTO (TICKS_PER_SECOND/2)
#define TCP_2MSL_WAIT (60 * TICKS_PER_SECOND)
#define MAX_TCP_RETRY (12)
#define TCP_WRITE_TIMEOUT (TICKS_PER_SECOND*10)
#define TCP_BUFFER_SEGMENTS (3)               /* Store 3 segments max in tx and rx buffers */

#define MAX_MULTICAST_GROUPS  (32)

#define HTTP_TIMEOUT   (TICKS_PER_SECOND*10)  /* 10 idle Seconds and a partially recieved request is abandoned */
#define HTTP_READ_TIME_LIMIT (30) /* Seconds to allow reading to avoid denial of service*/
#define HTTP_RX_BUFFERSIZE  (10000)

#define SERIAL_SOCKET_OFFSET (3)
#define TCP_SOCKET_OFFSET (5)
#define TCP_SOCKET_STRUCTS (32) 

#define EXTRA_IO_OFFSET (TCP_SOCKET_OFFSET+TCP_SOCKET_STRUCTS)
#define MAX_IP_ERRS 3

#define BUFFER_POOL_SIZE  (256) /* was 64 in last release, we increased buffer segments to handle higher throughput events*/
#define POOL_BUFFER_SIZE ( 164 + ETHER_BUFFER_SIZE ) // Size of each buffer - 1712 bytes by default
#define UDP_DISPATCH_SIZE (10)
#define UDP_MIN_BUFFER_THRESHOLD (10)
#define ARP_ENTRY_SIZE    (256)

#define UDP_NETBURNERID_PORT (0x4E42) /* NB */
#define UDP_DHCP_CLIENT_PORT (68) 

#define TFTP_RX_PORT  (1414)

#define LINK_STATUS_CHECK_INTERVAL (2*TICKS_PER_SECOND)



#ifndef _DEBUG
#define ENABLE_SRAM_SYS
#endif

/* If ENABLE _SRAM_SYS is TRUE, then the processor's on-chip SRAM will be
    used for fast network buffering and OS tasks as defined below:
*/
#ifdef ENABLE_SRAM_SYS	
#define FAST_SYSTEM_VARIABLES   

// Uncommented system tasks will be stored in SRAM, otherwise SDRAM will be used.
//#define FAST_IDLE_STACK
#define FAST_MAIN_STACK
#define FAST_ETHERNET_VARIABLES
#define FAST_ETHERNET_STACK
#define FAST_BUFFERS_VARIABLES
#define FAST_BUFFERS
#define FAST_IP_VARIABLES
#define FAST_IP_STACK
#define FAST_TCP_VARIABLES
#define FAST_TCP_STACK
//#define FAST_HTTP_STACK
//#define FAST_FTP_STACK
//#define FAST_WIFI_STACK
//#define FAST_PPP_STACK
//#define FAST_COMMAND_STACK

/* If these defines are enabled, any user variables or tasks declared with 
    FAST_USR_STK or FAST_USR_VAR will be stored in SRAM. 
*/	
#define FAST_USER_VARIABLES
#define FAST_USER_STACK

#endif



#ifdef FAST_SYSTEM_VARIABLES 
#define FAST_SYS_VAR __attribute__((section("SYS_VAR_SECT")))
#else
#define FAST_SYS_VAR
#endif
#ifdef FAST_IDLE_STACK
#define FAST_IDLE_STK __attribute__((section("IDLE_STK_SECT")))
#else
#define FAST_IDLE_STK
#endif
#ifdef FAST_MAIN_STACK
#define FAST_MAIN_STK __attribute__((section("MAIN_STK_SECT")))
#else
#define FAST_MAIN_STK
#endif
#ifdef FAST_USER_STACK
#define FAST_USER_STK __attribute__((section("USER_STK_SECT")))
#else
#define FAST_USER_STK
#endif
#ifdef FAST_USER_VARIABLES
#define FAST_USER_VAR __attribute__((section("USER_VAR_SECT")))
#else
#define FAST_USER_VAR
#endif
#ifdef FAST_ETHERNET_VARIABLES
#define FAST_ETHER_VAR __attribute__((section("ETHER_VAR_SECT")))
#else
#define FAST_ETHER_VAR
#endif
#ifdef FAST_ETHERNET_STACK
#define FAST_ETHER_STK __attribute__((section("ETHER_STK_SECT")))
#else
#define FAST_ETHER_STK
#endif
#ifdef FAST_IP_VARIABLES
#define FAST_IP_VAR __attribute__((section("IP_VAR_SECT")))
#else
#define FAST_IP_VAR
#endif
#ifdef FAST_IP_STACK
#define FAST_IP_STK __attribute__((section("IP_STK_SECT")))
#else
#define FAST_IP_STK
#endif
#ifdef FAST_TCP_VARIABLES
#define FAST_TCP_VAR __attribute__((section("TCP_VAR_SECT")))
#else
#define FAST_TCP_VAR
#endif
#ifdef FAST_TCP_STACK 
#define FAST_TCP_STK __attribute__((section("TCP_STK_SECT")))
#else
#define FAST_TCP_STK
#endif
#ifdef FAST_HTTP_STACK
#define FAST_HTTP_STK __attribute__((section("HTTP_STK_SECT")))
#else
#define FAST_HTTP_STK
#endif
#ifdef FAST_FTP_STACK
#define FAST_FTP_STK __attribute__((section("FTP_STK_SECT")))
#else
#define FAST_FTP_STK
#endif
#ifdef FAST_WIFI_STACK
#define FAST_WIFI_STK __attribute__((section("WIFI_STK_SECT")))
#else
#define FAST_WIFI_STK
#endif
#ifdef FAST_PPP_STACK
#define FAST_PPP_STK __attribute__((section("PPP_STK_SECT")))
#else
#define FAST_PPP_STK
#endif
#ifdef FAST_COMMAND_STACK
#define FAST_COMMAND_STK __attribute__((section("COMMAND_STK_SECT")))
#else
#define FAST_COMMAND_STK
#endif
#ifdef FAST_BUFFERS_VARIABLES
#define FAST_BUFF_VAR __attribute__((section("BUFFERS_VAR_SECT")))
#else
#define FAST_BUFF_VAR
#endif


#endif /* #ifndef _CONSTANTS_H */

