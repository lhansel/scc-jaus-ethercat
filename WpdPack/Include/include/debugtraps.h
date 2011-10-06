#ifndef DBUGTRAP_H
#define DBUGTRAP_h

#ifdef __cplusplus 
extern "C"
{
#endif


   void SetAddressWrittenTrap( DWORD addr );
   void SetAddressWriteRangeTrap( DWORD startaddr, DWORD endaddr );


/* Call this macro to monitor writes to a single variable */
/* You may only monitor ONE VARIABLE                      */
/* You may not write to this variable after making this call unless */
/* You first use the BEFORE_WRITING_MONITORED_VAR macro */
#define MONITOR_VAR_WRITES(x) SetAddressWrittenTrap((DWORD)&x);

/* use this before writing to a monitored var */
#define BEFORE_WRITING_MONITORED_VAR(x)  asm (" move.w #0x2700,%sr "); SetAddressWrittenTrap( 0); 

/* Use this after writing to a monitored var */
#define AFTER_WRITING_MONITORED_VAR(x) asm(" nop"); SetAddressWrittenTrap((DWORD)&x); asm (" move.w (OSISRLevel),%d0 "); asm (" move.w %d0,%sr "); 




#ifdef __cplusplus 
}
#endif


#endif
