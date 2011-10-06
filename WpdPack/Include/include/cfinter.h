/* $Revision: 1.16 $ */
/* Copyright $Date: 2008/11/19 23:06:49 $ */  

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

#ifndef _COLDFIRE_INTERRUPT_H
#define _COLDFIRE_INTERRUPT_H


/*-------------------------------------------------------------------------
**                                                             
** The following MACRO allows you to setup interrupt functions 
** in C                                                        
**                                                             
** Example Usage:                                                          
**                                                                         
** INTERRUPT(timetick)                                                     
** {                                                                       
** //Your interrupt function code goes here..                              
** }                                                                       
**                                                                         
** This example exposes a symbol timetick that can be used a a function pointer to 
** put into athe vector base register array.                              
**                                                                         
**-------------------------------------------------------------------------*/
#ifdef __cplusplus

#ifdef _UCOS_H
#define INTERRUPT(x,y)extern "C" { void real_##x();  void x(); } void fake_##x(){\
__asm__  (".global "#x);\
__asm__  (#x":");\
__asm__  ("move.w #0x2700,%sr ");\
__asm__  ("lea      -60(%a7),%a7 ");\
__asm__  ("movem.l  %d0-%d7/%a0-%a6,(%a7) ");\
__asm__  ("move.w (OSISRLevel),%d0 ");\
__asm__  ("move.l %d0,-(%sp) ");\
__asm__  ("move.l (OSIntNesting),%d0");\
__asm__  ("addq.l #1,%d0");\
__asm__  ("move.l %d0,(OSIntNesting)");\
__asm__  ("move.w #"#y",%d0 ");\
__asm__  ("move.w %d0,%sr ");\
__asm__  ("move.w %d0,(OSISRLevel)");\
__asm__  ("jsr real_"#x );\
__asm__  ("move.l (%sp)+,%d0 ");\
__asm__  ("move.w %d0,(OSISRLevel)");\
__asm__  (" jsr      OSIntExit  ");\
__asm__  ("movem.l  (%a7),%d0-%d7/%a0-%a6 ");\
__asm__  ("lea    60(%a7),%a7 ");\
__asm__  ("rte");} void real_##x()

#else
#define INTERRUPT(x) extern "C" { void real_##x();  void x();} void fake_##x(){\
__asm__  (".global "#x);\
__asm__  (#x":");\
__asm__  ("lea      -60(%a7),%a7 ");\
__asm__  ("movem.l  %d0-%d7/%a0-%a6,(%a7) ");\
__asm__  ("jsr real_"#x );\
__asm__  ("movem.l  (%a7),%d0-%d7/%a0-%a6 ");\
__asm__  ("lea      60(%a7),%a7 ");\
__asm__  ("rte");}void real_##x()

#endif

#else /*Do C version */

#ifdef _UCOS_H
#define INTERRUPT(x,y) void x(); void fake_##x(){\
__asm__  (".global "#x);\
__asm__  (#x":");\
__asm__  ("move.w #0x2700,%sr ");\
__asm__  ("lea     -60(%a7),%a7 ");\
__asm__  ("movem.l %d0-%d7/%a0-%a6,(%a7) ");\
__asm__  ("move.w (OSISRLevel),%d0 ");\
__asm__  ("move.l %d0,-(%sp) ");\
__asm__  ("move.l (OSIntNesting),%d0");\
__asm__  ("addq.l #1,%d0");\
__asm__  ("move.l %d0,(OSIntNesting)");\
__asm__  ("move.w #"#y",%d0 ");\
__asm__  ("move.w %d0,%sr ");\
__asm__  ("move.w %d0,(OSISRLevel)");\
__asm__  ("jsr real_"#x );\
__asm__  ("move.l (%sp)+,%d0 ");\
__asm__  ("move.w %d0,(OSISRLevel)");\
__asm__  (" jsr      OSIntExit  ");\
__asm__  ("movem.l  (%a7),%d0-%d7/%a0-%a6 ");\
__asm__  ("lea    60(%a7),%a7 ");\
__asm__  ("rte");} void real_##x()
#else
#define INTERRUPT(x) void x(); void fake_##x(){\
__asm__  (".global "#x);\
__asm__  (#x":");\
__asm__  ("lea      -60(%a7),%a7 ");\
__asm__  ("movem.l  %d0-%d7/%a0-%a6,(%a7) ");\
__asm__  ("jsr real_"#x );\
__asm__  ("movem.l  (%a7),%d0-%d7/%a0-%a6 ");\
__asm__  ("lea      60(%a7),%a7 ");\
__asm__  ("rte");}void real_##x()

#endif
#endif /*C Version */



/*----------------------------------------------------------------------------------------------------**
** The following definitions define the vector offset for various predefined vectors on the coldfire. **
**----------------------------------------------------------------------------------------------------*/
#define CF_ACCESSERROR_VECTOR         2
#define CF_ADDRESSERROR_VECTOR        3
#define CF_ILLEGAL_INSTRUCTION_VECTOR 4
#define CF_PRIVLEDGE_VIOLATION_VECTOR 8
#define CF_TRACE_VECTOR               9
#define CF_UNIMPLMENTED_A_VECTOR     10
#define CF_UNIMPLMENTED_F_VECTOR     11
#define CF_DEBUG_INTERRUPT           12
#define CF_FORMAT_ERR_VECTOR         14
#define CF_UNINITIALIZED_VECTOR      15
#define CF_SPURIOUS_INT_VECTOR       24
#define CF_AUTOVECTOR_IRQ1           25
#define CF_AUTOVECTOR_IRQ2           26
#define CF_AUTOVECTOR_IRQ3           27
#define CF_AUTOVECTOR_IRQ4           28
#define CF_AUTOVECTOR_IRQ5           29
#define CF_AUTOVECTOR_IRQ6           30
#define CF_AUTOVECTOR_IRQ7           31
#define CF_TRAP0_VECTOR              32
#define CF_TRAP1_VECTOR              33
#define CF_TRAP2_VECTOR              34
#define CF_TRAP3_VECTOR              35
#define CF_TRAP4_VECTOR              36
#define CF_TRAP5_VECTOR              37
#define CF_TRAP6_VECTOR              38
#define CF_TRAP7_VECTOR              39
#define CF_TRAP8_VECTOR              40
#define CF_TRAP9_VECTOR              41
#define CF_TRAP10_VECTOR             42
#define CF_TRAP11_VECTOR             43
#define CF_TRAP12_VECTOR             44
#define CF_TRAP13_VECTOR             45
#define CF_TRAP14_VECTOR             46
#define CF_TRAP15_VECTOR             47
#define CF_USER_BASE_VECTOR          64


#ifdef __cplusplus
extern "C"
{
#endif
   /*-------------------------------------------------------------------------------------*/
   /*---------------------------------------------------------------**
   ** This gets the current interupt mask level in the SR register. **
   ** You must have supervisor privledges to use this macro         **
   **---------------------------------------------------------------*/
   WORD GetSR_IntLevel();

   /*------------------------------------------------------------**
   ** The folowing macro sets the interupt mask level in the SR. **
   ** You must have supervisor privlidges to use this macro.     **
   **------------------------------------------------------------*/
   void SetSR_IntLevel( WORD sv );

#ifdef __cplusplus
};
#endif


#endif
