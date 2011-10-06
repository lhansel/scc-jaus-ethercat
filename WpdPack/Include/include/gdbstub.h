/* Rev:$Revision: 1.4 $ */  

#ifndef _GDB_MON_H
#define _GDB_MON_H
#ifdef __cplusplus
extern "C"
{
#endif
   /* GDB Stub functions */
   /*Module: GDB Stub
   This Module provides code for operating a serial GDB stub.
   This is used to debug programs running on a NetBurner system.
   More information can be fount in ..nburn/docs/gdb/GDB-Gettingstarted
   */

   /*Functions:*/
   /*Group:Stub Initialization functions*/
   /* Start the GDB stub and then immediatly stop at a break point */
   /*
   This function will start the GDB stub, and will stop immediatly at
   a breakpoint. This function is best used during development to 
   stop the system from executing questionable code at startup.
   It is also useful to control the system execution to debug startup 
   and initialization code.

   Parameters:
      int port The serial port to use this can be 0 or 1 coresponding to uart 0 or uart 1
      int baudrate The baud rate to use on the port.


   */
   /*See Also: 
      void InitGDBStubNoBreak(int port, int baudrate);
   */
   void InitGDBStub( int port, int baudrate );


   /* Start the GDB stub and continue without stopping */
   /*
   This function will start the GDB stub, and continue with normal
   program execution. This function is best used to debug a program that
   is operating correctly and has intermitant bugs or anomallies.
   The program will run as normal until you connect the debugger.
   Thus you can operate the program until one needs to debug it.

   Parameters:
      int port The serial port to use this can be 0 or 1 coresponding to uart 0 or uart 1
      int baudrate The baud rate to use on the port.


   */
   /*See Also: 
      void InitGDBStub(int port, int baudrate);
   */
   void InitGDBStubNoBreak( int port, int baudrate );

#ifdef __cplusplus
}
#endif

#endif


