/* Rev:$Revision: 1.7 $ */  

/******************************************************************************
 *
 * Copyright 1998-2002 NetBurner  ALL RIGHTS RESERVED
 *   Permission is hereby granted to purchasers of NetBurner Hardware
 *   to use or modify this computer program for any use as long as the
 *   resultant program is only executed on NetBurner provided hardware.
 *
 *   No other rights to use this program or it's derivitives in part or
 *   in whole are granted.
 *
 *   It may be possible to license this or other NetBurner software for
 *        use on non NetBurner Hardware.
 *   Please contact Licensing@Netburner.com for more infomation.
 *
 *   NetBurner makes no representation or warranties
 *   with respect to the performance of this computer program, and
 *   specifically disclaims any responsibility for any damages,
 *   special or consequential, connected with the use of this program.
 *
 *---------------------------------------------------------------------
 * NetBurner
 * 5405 Morehouse Dr #350
 * San Diego Ca, 92131
 *
 * information available at:  http://www.netburner.com
 * E-Mail info@netburner.com
 *
 * Support is availible: E-Mail support@netburner.com
 *
 *****************************************************************************/


/*
 * Defintions of the basic data types.
 */

#ifndef _BASICTYPES_H_
#define _BASICTYPES_H_

typedef unsigned char BOOL;
typedef unsigned char BOOLEAN;
typedef unsigned char BYTE; /* Unsigned  8 bit quantity                           */
typedef signed   short SHORT;/* Signed   16 bit quantity                           */
typedef unsigned short WORD; /* Signed   16 bit quantity                           */
typedef unsigned long DWORD;/* Unsigned 32 bit quantity                           */
typedef signed   long LONG; /* Signed   32 bit quantity                           */

typedef volatile unsigned char VBOOLEAN;
typedef volatile unsigned char VBYTE;  /* Unsigned  8 bit quantity                           */
typedef volatile short VSHORT; /* Signed   16 bit quantity                           */
typedef volatile unsigned short VWORD;  /* Signed   16 bit quantity                           */
typedef volatile unsigned long VDWORD; /* Unsigned 32 bit quantity                           */
typedef volatile signed   long VLONG;  /* Signed   32 bit quantity                           */

typedef VBOOLEAN *PVBOOLEAN;
typedef VBYTE *PVBYTE; 
typedef VSHORT *PVSHORT;
typedef VWORD *PVWORD; 
typedef VDWORD *PVDWORD;
typedef VLONG *PVLONG; 

typedef BOOLEAN *PBOOLEAN;
typedef BYTE *PBYTE; 
typedef SHORT *PSHORT;
typedef WORD *PWORD; 
typedef DWORD *PDWORD;
typedef LONG *PLONG; 

typedef const char *PCSTR;
typedef char *PSTR;

#ifdef TRUE
#undef TRUE
#endif
#define TRUE      (1)
#ifdef FALSE
#undef FALSE
#endif
#define FALSE     (0)
#ifdef NULL
#undef NULL
#endif
#define NULL      (0)



//TYPEDEFS needed for Freescale ETPU API
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef volatile signed char vint8_t;
typedef volatile unsigned char vuint8_t;

typedef signed short int16_t;
typedef unsigned short uint16_t;
typedef volatile signed short vint16_t;
typedef volatile unsigned short vuint16_t;

typedef signed long int32_t;
typedef unsigned long uint32_t;
typedef volatile signed long vint32_t;
typedef volatile unsigned long vuint32_t;

typedef signed char INT8;
typedef unsigned char UINT8;
typedef volatile signed char VINT8;
typedef volatile unsigned char VUINT8;

typedef signed short INT16;
typedef unsigned short UINT16;
typedef volatile signed short VINT16;
typedef volatile unsigned short VUINT16;

typedef signed long INT32;
typedef unsigned long UINT32;
typedef volatile signed long VINT32;
typedef volatile unsigned long VUINT32;


#endif /* _BASICTYPES_H_ */
