/* Rev:$Revision: 1.7 $ */  

/******************************************************************************
 *
 * Copyright 1998-2004 NetBurner  ALL RIGHTS RESERVED
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
 * San Diego Ca, 92121
 *
 * information available at:  http://www.netburner.com
 * E-Mail info@netburner.com
 *
 * Support is availible: E-Mail support@netburner.com
 *
 *****************************************************************************/


/* Definitions for various IP definitions and structures. */
#ifndef _NB_NETTIMER_H
#define _NB_NETTIMER_H
typedef void ( SecondTickFunction )();
extern SecondTickFunction *pDHCPTick;
extern SecondTickFunction *pMultiTick;

typedef void ( DHCPProcessFunction )( PoolPtr p );
extern DHCPProcessFunction *pDHCPProcessFunction;

typedef void ( MULTICastProcessFunction )( PoolPtr p, WORD csum );
extern   MULTICastProcessFunction *pMultiCastFunc;

#endif


