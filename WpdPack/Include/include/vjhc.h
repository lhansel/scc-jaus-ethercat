/* Rev:$Revision: 1.1 $ */  

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
 * 5405 Morehouse Dr #200
 * San Diego Ca, 92121
 *
 * information available at:  http://www.netburner.com
 * E-Mail info@netburner.com
 *
 * Support is availible: E-Mail support@netburner.com
 *
 *****************************************************************************/
 
 #ifdef __cplusplus
extern "C"
{
#endif


#define MAX_HDR 128     /* max TCP+IP hdr length (by protocol def) */
#define MAX_STATES 16   /* must be >2 and <255 */
/*
 * "state" data for each active tcp conversation on the wire.  This is
 * basically a copy of the entire IP/TCP header from the last packet together
 * with a small identifier the transmit & receive ends of the line use to
 * locate saved header.
 */

extern volatile int NumStatesRX;
extern volatile int NumStatesTX;

struct cstate
{
      struct cstate *cs_next;  /* next most recently used cstate (xmit only) */
      WORD cs_hlen;         /* size of hdr (receive only) */
      BYTE cs_id;            /* connection # associated with this state */
      BYTE cs_filler;
      union
      {
            char hdr[MAX_HDR];
            IPPKT csu_ip;   /* ip/tcp hdr from most recent packet */

      } slcs_u;
};

#define cs_hdr slcs_u.csu_hdr
#define cs_ip slcs_u.csu_ip


typedef struct slcompress
{
      struct cstate *last_cs;            /* most recently used tstate */
      BYTE last_recv;                  /* last rcvd conn. id */
      BYTE last_xmit;                  /* last sent conn. id */
      WORD flags;
      struct cstate tstate[MAX_STATES];  /* xmit connection states */
      struct cstate rstate[MAX_STATES];  /* receive connection states */
};


typedef struct mbuf
{
      BYTE *m_off; /* pointer to start of data */
      int m_len;  /* length of data */
};



BYTE sl_compress_tcp( mbuf *m, slcompress *comp, int compress_cid);
PoolPtr  sl_uncompress_tcp(PoolPtr p, BYTE *bufp, int len, DWORD type, slcompress *comp );
void sl_compress_init( slcompress *comp );



#ifdef __cplusplus
}
#endif

