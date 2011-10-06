/* Rev:$Revision: 1.9 $ */  

/********************************************************************/
/**  Header : uCOSMCFc                                             **/
/**                                                                **/
/**  Description : This header file contains the macros which      **/
/**  define how critical sections and task level context switches  **/
/**  happen in uC/OS. It also contains definitions of the data     **/
/**  types used within the OS.                                     **/
/**                                                                **/
/**  Version History :                                             **/
/**                                                                **/
/**  A0.01     Initial version started                   15/09/97  **/
/**                                                                **/
/** Copyright (c) 1997 David Fiddes, D.J.Fiddes@hw.ac.uk           **/
/** Copyright (c) 1998 - 2008 NetBurner                            **/
/** This code is derived from Public Domain sources                **/
/** There are no restrictions on the use or redstribution          **/
/** of these uC/OS sources                                         **/
/********************************************************************/


/********************************************************************/
/**  Adaptations                                                    **/
#ifdef __cplusplus
extern "C"
{
#endif
   extern volatile unsigned long critical_count;
   void UCosSetup();
   void UCosBegin();

#ifdef __cplusplus
};
#endif




/********************************************************************/
/**  Macros                                                        **/

#define  UCOS_ENTER_CRITICAL() \
{                         \
      asm(" nop"); \
      asm(" move.w #0x2700,%sr "); \
}
      
#define  UCOS_EXIT_CRITICAL()           			\
		 asm ( "    nop \n\t              			\
						move.w %0, %%d1 \n\t   			\
						move.w %%d1, %%sr"     			\
						:  /* output */  			  			\
						: "m" ( OSISRLevel ) /* input */  \
						: "%d1"/*clobbered register*/ 			\
						);   
					 
#define  USER_ENTER_CRITICAL()\
{ \
   asm(".extern critical_count"); \
   asm(" nop"); \
   asm(" move.w #0x2700,%sr "); \
   asm(" addq.l #1,critical_count ");\
}

#define  USER_EXIT_CRITICAL() \
{ \
   asm(".extern critical_count"); \
   asm(" nop"); \
   asm(" subq.l #1,critical_count "); \
   if ( critical_count==0 ) \
   { \
          asm ( " move.w %0, %%d1 \n\t   			\
						move.w %%d1, %%sr"     			\
						:  /* output */  			  			\
						: "m" ( OSISRLevel ) /* input */  \
						: "%d1"/*clobbered register*/ 			\
						);   									\
   } \
}


#define  OS_TASK_SW() \
   asm (" trap #14 ");
   
#define  OS_IDLE_LOOP() \
   asm (" stop #0x2000 ");

