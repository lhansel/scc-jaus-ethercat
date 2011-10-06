/* Rev:$Revision: 1.8 $ */  

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


/* The data counters kept by the TCP/IP system */
#ifndef _NB_COUNTER_H
#define _NB_COUNTER_H
extern VWORD frames_tx;        //   "tx:%u","tx:%d",
extern VWORD frames_rx;        //   "rx:%u","rx:%d",
extern VWORD frames_tx_err;    //   "tx_err:%u","tx_err:%d",
extern VWORD frames_rx_err;    //   "rx_err:%u","rx_err:%d",
extern VWORD frames_rx_arp;    //   "rx_arp:%u","rx_arp:%d",
extern VWORD frames_tx_arp;    //   "tx_arp:%u","tx_arp:%d",
extern VWORD frames_tx_udp;    //   "tx_udp:%u","tx_udp:%d",
extern VWORD frames_rx_udp;    //   "rx_udp:%u","rx_udp:%d",
extern VWORD frames_tx_tcp;    //   "tx_tcp:%u","tx_tcp:%d",
extern VWORD frames_rx_tcp;    //   "rx_tcp:%u","rx_tcp:%d",
extern VWORD frames_tx_icmp;   //   "tx_icmp:%u","tx_icmp:%d",
extern VWORD frames_rx_icmp;   //   "rx_icmp:%u","rx_icmp:%d",
extern VWORD frames_ip_errors; //   "ip_err:%u","ip_err:%d",
extern VWORD frames_ip_discard;   //   "ip_discard:%u","ip_discard:%d",
extern VWORD frames_udp_errors;   //  "udp_err:%u","udp_err:%d",
extern VWORD frames_tcp_errors;   //  "tcp_err:%u","tcp_err:%d",
extern VWORD enet_last_errhw;     //   "last_err:%u""last_err:%d"
extern VWORD enet_last_errlw;     //   "last_err:%u""last_err:%d"
extern VWORD ip_last_err;         //   "last_err:%u""last_err:%d"
extern VWORD enet_isr;            // "enet_isr:%u""enet_isr:%d"
extern VWORD frames_rx_unknown;   //"frames_rx_unknown:%u""frames_rx_unknown%d"
extern VWORD frames_rx_ppp_errors; 
extern VWORD frames_rx_fragment; 

#endif
