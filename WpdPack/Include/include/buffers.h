/* Rev:$Revision: 1.18 $ */  

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
 *
 * NetBurner #350
 * 5405 Morehouse Dr
 * San Diego Ca, 92121
 *
 * information available at:  http://www.netburner.com
 * E-Mail info@netburner.com
 *
 * Support is availible: E-Mail support@netburner.com
 *
 *****************************************************************************/

/*
This file provides the definitions for handling Buffers
*/

#ifndef _NB_BUFFERS_H
#define _NB_BUFFERS_H

#ifdef __cplusplus
extern "C"
{
#endif



#ifdef _DEBUG
#define BUFFER_DIAG
#endif



#ifndef _UCOS_H
#include <ucos.h>
#endif

   struct pool_buffer; /*Forward declaration*/
   typedef struct pool_buffer *PoolPtr;
   typedef volatile PoolPtr VPoolPtr;

   /*The buffer states that define the ownership of the buffer */
#define BO_UNUSED     0 /*The buffer is free*/
#define  BO_SOFTWARE   1   /*The buffer belongs to some software function.*/
#define  BO_PRX         2 /*The buffer is to be used for the RX function.*/
#define  BO_PTXF        3 /*The buffer is to be TXed and then freeded*/
#define  BO_PTXS        4 /*The buffer is to be TXed and then set to S/W owns.*/

   /*The buffer state flags */
#define BS_PHY_BCAST    1 /*The underlying packet is to/from a physical layer broadcast address.*/
#define BS_IP_BCAST     2 /*The underlying packet is to/from a layer 3 broadcast address.*/
#define BS_IP_LOCAL_NET 4 /*The underlying packet is to/from the local subnet.*/
#define BS_TCP_PUSH     8 /*The push flag was set on RX.*/
#define BS_PHY_802_3 0x10 /*The network wants 802_3 encapsulation*/

   struct pool_buffer
   {
         PBYTE pBufQueuePointer;    /*For The OS FIFO List stuff...*/
		 DWORD PreSentinal[16];

#ifdef BUFFER_DIAG
         PCSTR m_fAlloc;
         DWORD m_fline;
         DWORD m_fill;
         DWORD m_fill2;
#endif
         VPoolPtr pPoolNext;     /*A pointer to the next buffer in pool*/
         VPoolPtr pPoolPrev;     /*A pointer to the prev buffer in pool*/
         VDWORD dwTime;
         VDWORD dwTimeFraction;
         VWORD usedsize;
         BYTE bBuffer_state; /*Unused,PRx,PtxF,PtxS,RxC*/
         BYTE bBufferFlag;
         BYTE bUsageCount;
         BYTE bInterfaceNumber;
         BYTE bAlignmentPad[6];
         BYTE pData[ETHER_BUFFER_SIZE];         /*The buffer data*/
         BYTE bPostAlignmentPad[3];
		 DWORD PostSentinal[16];
   };


   /*Buffer operations*/

#ifdef BUFFER_DIAG
   void ShowBuffers();
   PoolPtr GetBufferX( PCSTR file, int line );/*Alocates a Software buffer and returns the buffer number.*/
#define GetBuffer() GetBufferX( __FILE__ , __LINE__ )
   void FreeBufferX( PoolPtr nbuf, PCSTR file, int line );/*Frees a buffer and places it in the unused state.*/
#define FreeBuffer(x) FreeBufferX(x, __FILE__ , __LINE__ )

   void ChangeOwnerX( PoolPtr nbuf, PCSTR file, int line );/*Frees a buffer and places it in the unused state.*/
#define ChangeOwner(x) ChangeOwnerX(x, __FILE__ , __LINE__ )
#else
   PoolPtr GetBuffer();/*Alocates a Software buffer and returns the buffer number.*/
   void FreeBuffer( PoolPtr nbuf );/*Frees a buffer and places it in the unused state.*/
#define ChangeOwner(x) 

#endif

   void IncUsageCount( PoolPtr pp );

   WORD GetFreeCount();

   void InitBuffers(); /* Initializes the buffer system*/

   void ShowBuffer( PoolPtr p );



#ifdef __cplusplus
}; /* End of Extern C */
class buffer_list
{
   public:
      PoolPtr m_Head;
      PoolPtr m_Tail;
      WORD m_wElements;
      void InsertHead( PoolPtr buffer );
      void InsertTail( PoolPtr buffer );
      void InsertBefore( PoolPtr buf2insert, PoolPtr b4buffer );
      void InsertAfter( PoolPtr buf2insert, PoolPtr after_buffer );
      void Remove( PoolPtr buffer );
      PoolPtr RemoveHead();
      PoolPtr RemoveTail();
      buffer_list()
      {
         m_Head = 0; m_Tail = 0; m_wElements = 0;
      }
      WORD GetCount()
      {
         return m_wElements;
      };
};



/*
This defines a class for storing an array of bytes in a list of buffers.
It is used for I/O buffers 
*/
class fifo_buffer_storage
{
   private:
      PoolPtr m_Head;
      PoolPtr m_Tail;
      OS_CRIT m_critical_section;
      int m_BytesStored;
      BYTE m_Segments_Stored;
      BYTE m_MaxSegments; /*Stores the max number of segmenst allowed fore this buffer*/
   public:
      /*The number of availible bytes of storage*/
      WORD SpaceAvail();
      /*The number of bytes used.*/
      WORD SpaceUsed();

      /*Read data from the buffer*/
      /*REturns the number of bytes read*/
      int ReadData( PBYTE pCopyTo, int max_bytes );

      int ReadDatawSum( PBYTE pCopyTo, int max_bytes, DWORD &csum );

      /*Write Data to the buffer*/
      /*Returns the number of bytes read*/
      int WriteData( PBYTE pCopyFrom, int num_bytes );

      /*Returns true if empty*/
      BOOL Empty();

      /*Returns True if Full*/
      BOOL Full();


      /*Build one */
      fifo_buffer_storage( BYTE max_buffers = 0, BYTE use_fromisr = 1 );
      ~fifo_buffer_storage();

      /*Reset frees the storage*/
      void Reset( BYTE max_buffers );

      void SetMaxBuffers( BYTE max_buffers );

      /*Init initializes it to zero*/
      void Init( BYTE max_buffers, BYTE use_fromisr = 1 );
};

#endif


#endif

