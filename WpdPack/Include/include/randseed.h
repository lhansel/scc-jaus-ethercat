/* Rev:$Revision: 1.5 $ */  

/******************************************************************************
 *
 * Copyright 2002-2004 NetBurner, Inc.  ALL RIGHTS RESERVED
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
 *
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

#ifndef _NB_RANDOM_H                      
#define _NB_RANDOM_H                      

#ifdef GATHER_RANDOM
extern volatile BYTE rnd_cnt;
extern volatile WORD rnd_collect[256];
#else
#endif
#endif



