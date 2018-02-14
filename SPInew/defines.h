/////////////////////////////////////////////////////////////////////////
//                        DEFINES.H                     2010-02-09 AgF //
//                                                                     //
//    Macro definitions etc. for AVR microcontroller.                  //
//                                                                     //
//                                                                     //
/////////////////////////////////////////////////////////////////////////
#pragma once

/////////////////////////////////////////////////////////////////////////
//                                                                     //
//            Definitions for set and clear interrupt                  //
//                                                                     //
/////////////////////////////////////////////////////////////////////////

// set interrupt
#define SetInterrupt()   __asm__ __volatile__ ("sei" ::);

// clear interrupt
#define ClearInterrupt() __asm__ __volatile__ ("cli" ::);

/////////////////////////////////////////////////////////////////////////
//                                                                     //
//            Definitions for bit manipulations                        //
//                                                                     //
/////////////////////////////////////////////////////////////////////////

// This macro reads one bit from an input port. It behaves like a
// function that returns 0 or 1. Example:
// x = InputBit(PINB,4);
// Remember to use the input port names (PINA, PINB, etc.),
// not the output port names (PORTA, PORTB, etc.).
#define InputBit(Port, BitNumber)           \
   ((Port >> (BitNumber)) & 1)

// This macro writes one bit to an output port and leaves the other
// bits unchanged.
// Example: OutputBit(PORTB,3,1)
#define OutputBit(Port, BitNumber, Value)   \
   if (Value) Port |=   (1 << (BitNumber));   \
   else       Port &= ~ (1 << (BitNumber));

// This macro modifies some bits of an output port and leaves the
// other bits unchanged. Mask defines which bits to modify.
// Value must contain the new bit values in the right positions.
// Example: OutputBits(PORTA, 0xF0, 0x30)
#define OutputBits(Port, Mask, Value)       \
   Port = ((Mask) & (Value)) | (~(Mask) & Port);


/////////////////////////////////////////////////////////////////////////
//                                                                     //
//                   Define type bool                                  //
//                                                                     //
/////////////////////////////////////////////////////////////////////////


#ifndef __cplusplus  // bool is defined in C++ but not in C

typedef enum {false, true} bool;

#endif
