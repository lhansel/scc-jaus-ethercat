/* Rev:$Revision: 1.25 $ */  

#ifndef _UCOS_H
#define _UCOS_H

#ifdef _COLDFIRE_INTERRUPT_H
#error UCOS FIRST
#endif
#ifdef __cplusplus
extern "C"
{
#endif
#ifdef _COLDFIRE_INTERRUPT_H
#error MUST Include UCOS before cfinter.h 
#endif

#include <basictypes.h>

   /***********************************************************
   *                         UCOS.H
   *                   SYSTEM DECLARATIONS
   ***********************************************************
   */
#define OS_LO_PRIO          63 /*IDLE task priority      */

   /*TASK STATUS             */
#define OS_STAT_RDY       0x00 /*Ready to run            */

#define OS_STAT_MBOX      0x01 /*Pending on mailbox      */
#define OS_STAT_SEM       0x02 /*Pending on semaphore    */
#define OS_STAT_Q         0x04 /*Pending on queue        */
#define OS_STAT_FIFO      0x08 /*Pending on FIFO         */
#define OS_STAT_CRIT      0x10 /*Pending on Critical Section*/
#define OS_STAT_RES3      0x20 /*Reserved                */
#define OS_STAT_RES4      0x40 /*Reserved                */
#define OS_STAT_RES5      0x80 /*Reserved                */

#define  OS_NO_ERR           0
#define  OS_TIMEOUT         10
#define  OS_MBOX_FULL       20
#define  OS_Q_FULL          30
#define  OS_PRIO_EXIST      40
#define  OS_SEM_ERR         50
#define  OS_SEM_OVF         51
#define  OS_CRIT_ERR        60
#define  OS_NO_MORE_TCB     70 //No TCBs free to create task



   /*
   ***********************************************************
   *         uCOS TASK CONTROL BLOCK DATA STRUCTURE
   ***********************************************************
   */
   typedef struct os_tcb
   {
         void *OSTCBStkPtr;
         BYTE OSTCBStat;
         BYTE OSTCBPrio;
         WORD OSTCBDly;
		 const char * pOSTCBName;
#ifdef UCOS_STACKCHECK
         long *OSTCBStkBot;     
         long *OSTCBStkTop;     
#endif
         struct os_tcb *OSTCBNext;
         struct os_tcb *OSTCBPrev;
   
   } OS_TCB;

   /*
   ***********************************************************
   *                SEMAPHORE DATA STRUCTURE
   ***********************************************************
   */
   typedef struct os_sem
   {
         volatile long OSSemCnt;
         volatile BYTE OSSemGrp;
         volatile BYTE OSSemTbl[8];
   } OS_SEM;

   /*
   ***********************************************************
   *                    MAILBOX DATA STRUCTURE
   ***********************************************************
   */
   typedef struct os_mbox
   {
         void *OSMboxMsg;
         BYTE OSMboxGrp;
         BYTE OSMboxTbl[8];
   } OS_MBOX;

   /*
   ***********************************************************
   *                      QUEUE DATA STRUCTURE
   ***********************************************************
   */
   typedef struct os_q
   {
         void **OSQStart;
         void **OSQEnd;
         void **OSQIn;
         void **OSQOut;
         BYTE OSQSize;
         BYTE OSQEntries;
         BYTE OSQGrp;
         BYTE OSQTbl[8];
   } OS_Q;


   /*
   ***********************************************************
   *                      FIFO DATA STRUCTURES
   *
   *     Added by PTB 5/25/98
   ***********************************************************
   */
   typedef struct os_fifo_el
   {
         struct os_fifo_el *pNext;
   }OS_FIFO_EL;


   typedef struct os_fifo
   {
         OS_FIFO_EL *pHead;
         OS_FIFO_EL *pTail;
         BYTE OSFifoGrp;
         BYTE OSFifoTbl[8];
   } OS_FIFO;



   /*
   ***********************************************************
   *                      Critical Section DATA STRUCTURES
   *
   *     Added by PTB 5/09/99
   ***********************************************************
   */

   typedef struct os_crit_section
   {
         BYTE OSCritTaskNum;
         DWORD OSCritDepthCount;
         BYTE OSCritGrp;
         BYTE OSCritTbl[8];
   } OS_CRIT;



   typedef struct os_flags
   {
	 VDWORD current_flags;
	 void * pWaitinglist;
   } OS_FLAGS;



   /*
   ***********************************************************
   *                 uCOS GLOBAL VARIABLES
   ***********************************************************
   */
   extern volatile OS_TCB *OSTCBPrioTbl[];
   extern volatile BYTE OSRdyTbl[];
   extern OS_TCB OSTCBTbl[];
   extern OS_TCB *OSTCBList;
   extern volatile OS_TCB *OSTCBCur;
   extern volatile OS_TCB *OSTCBHighRdy;
   extern OS_TCB *OSTCBFreeList;
   extern volatile DWORD OSIntNesting;
   extern volatile DWORD OSLockNesting;
   extern volatile DWORD OSRdyGrp;
   extern volatile WORD OSISRLevel; 	
   extern volatile BOOLEAN OSRunning;
   extern volatile BOOLEAN OSShowTasksOnLeds;


#ifndef UCOS_C                 /*Required to stop GNU compiler complaining - DJF */
   extern BYTE OSMapTbl[];
   extern BYTE OSUnMapTbl[];
#endif

   /*
   ***********************************************************
   *                 uCOS FUNCTION PROTOTYPES
   ***********************************************************
   */
   void OSInit( void *idle_stk_top, void *idle_Stk_bot, BYTE maxtasks );
   void OSStart( void );
   BYTE OSTaskCreate( void ( *task ) ( void *dptr ),
                      void *data,
                      void *pstktop,
                      void *pstkbot,
                      BYTE  prio );

   BYTE OSTaskCreatewName( void ( *task ) ( void *dptr ),
				   void *data,
				   void *pstktop,
				   void *pstkbot,
				   BYTE  prio, const char * name);



   #define OSSimpleTaskCreate(x,p) { static DWORD   func_##x_Stk[USER_TASK_STK_SIZE] __attribute__( ( aligned( 4 ) ) ); OSTaskCreate(x,NULL,(void *)&func_##x_Stk[USER_TASK_STK_SIZE],(void*)func_##x_Stk,p); }
   #define OSSimpleTaskCreatewName(x,p,n) { static DWORD   func_##x_Stk[USER_TASK_STK_SIZE] __attribute__( ( aligned( 4 ) ) ); OSTaskCreatewName(x,NULL,(void *)&func_##x_Stk[USER_TASK_STK_SIZE],(void*)func_##x_Stk,p,n); }


   void OSTimeDly( WORD ticks );
   void OSTimeTick( void );
   void OSIntEnter( void );
   void OSIntExit( void );
   void OSCtxSw( void );
   void OSIntCtxSw( void );
   void OSTickISR( void );
   void OSStartHighRdy( void );
   void OSSetupVBR( void );
   void OSSched( void );
   OS_TCB *OSTCBGetFree( void );
   BYTE OSChangePrio( BYTE newp );
   void OSSetName(const char * cp);
   void OSTaskDelete( void );
   void OSLock( void );
   void OSUnlock( void );

   BYTE OSSemInit( OS_SEM *psem, long value );
   BYTE OSSemPost( OS_SEM *psem );
   BYTE OSSemPend( OS_SEM *psem, WORD timeout );
   BYTE OSSemPendNoWait( OS_SEM *psem );

   BYTE OSMboxInit( OS_MBOX *pmbox, void *msg );
   BYTE OSMboxPost( OS_MBOX *pmbox, void *msg );
   void *OSMboxPend( OS_MBOX *pmbox, WORD timeout, BYTE *err );
   void *OSMboxPendNoWait( OS_MBOX *pmbox, BYTE *err );

   BYTE OSQInit( OS_Q *pq, void **start, BYTE size );
   BYTE OSQPost( OS_Q *pq, void *msg );
   BYTE OSQPostFirst( OS_Q *pq, void *msg );
   void *OSQPend( OS_Q *pq, WORD timeout, BYTE *err );
   void *OSQPendNoWait( OS_Q *pq, BYTE *err );

   BYTE OSFifoInit( OS_FIFO *pFifo );
   BYTE OSFifoPost( OS_FIFO *pFifo, OS_FIFO_EL *pToPost );
   BYTE OSFifoPostFirst( OS_FIFO *pFifo, OS_FIFO_EL *pToPost );
   OS_FIFO_EL *OSFifoPend( OS_FIFO *pFifo, WORD timeout );
   OS_FIFO_EL *OSFifoPendNoWait( OS_FIFO *pFifo );

   BYTE OSCritInit( OS_CRIT *pCrit );
   BYTE OSCritEnter( OS_CRIT *pCrit, WORD timeout );
   BYTE OSCritEnterNoWait( OS_CRIT *pCrit );
   BYTE OSCritLeave( OS_CRIT *pCrit );


   /* 
    This function returns the current tasks priority
   */
BYTE OSTaskID( void );


   /* 
    This function returns the current tasks name
   */
const char *  OSTaskName();



   /* Create and initialize an OS flags object 
    This function must be called beofre you use an OS_FLAGS object.
   */
void OSFlagCreate( OS_FLAGS *);


   /* Set bits in a OS_FLAG object, this sets or clears  whatever bits are set in bits_to_set 
      flags, a pointer to the OS_FLAG object you whish to operate on
      bits_to_set A bit or of the flag bits you want to set. 
    */
void OSFlagSet(OS_FLAGS * flags, DWORD bits_to_set);
   
   /* Clears bits in a OS_FLAG object, this sets or clears  whatever bits are set in bits_to_set 
   flags, a pointer to the OS_FLAG object you whish to operate on
   bits_to_clr A bit or of the flag bits you want to clear. 
 */
 void OSFlagClear(OS_FLAGS * flags, DWORD bits_to_clr);




   /* This call waits until  ANY of the flags indicated by mask are set 
    flags the OS_FLAGS object to wait on.
    bit_mask The set of bits to wait on
 	timeout the number of time ticks to wait for a flag.
	This returns:
		OS_NO_ERR        If the flags condition is satisfied 
		OS_TIMEOUT        If the timeout expired
   */
   BYTE OSFlagPendAny(OS_FLAGS * flags, DWORD bit_mask, WORD timeout);
   BYTE OSFlagPendAnyNoWait(OS_FLAGS * flags, DWORD bit_mask);



	/* This call waits until  ALL of the flags indicated by mask are set *
    flags the OS_FLAGS object to wait on.
    bit_mask The set of bits to wait on, all of these bit must be set to triger a return.
 	timeout the number of time ticks to wait for a flag.
	
	This returns:
		OS_NO_ERR        If the flags condition is satisfied 
		OS_TIMEOUT        If the timeout expired
   */
   BYTE OSFlagPendAll(OS_FLAGS * flags, DWORD bit_mask, WORD timeout);
   BYTE OSFlagPendAllNoWait(OS_FLAGS * flags, DWORD bit_mask);


   /* This returns the current value of flags stored in the OS_FLAGS structure.
	flags a pointer to the OS_FLAGS structure whoose state you want to return.
	returns:
		The state of the flags object.
   */
   DWORD OSFlagState(OS_FLAGS * flags);

   


   void OSChangeTaskDly( WORD task_prio, WORD newticks );

#ifdef UCOS_STACKCHECK
   void OSDumpTCBStacks( void );
   void OSDumpTasks( void );
#endif

#ifdef    UCOS_TASKLIST

   void ShowTaskList( void );

#endif




#ifdef __cplusplus
}
/*Some CPP Classes for  use */

class OSLockObj
{
   public:
      OSLockObj()
      {
         OSLock();
      };
      ~OSLockObj()
      {
         OSUnlock();
      };
};


class OSCriticalSectionObj
{
      OS_CRIT *pcrit;

   public:
      OSCriticalSectionObj( OS_CRIT &ocrit )
      {
         pcrit = &ocrit;
         OSCritEnter( &ocrit, 0 );
      };


      ~OSCriticalSectionObj()
      {
         OSCritLeave( pcrit );
      }
};


#endif


#endif
