#include <avr\io.h> // h is header and io is the inputoutput for the avr kit

volatile unsigned char x =0; // Volatile: The compiler is forced not to use a register for the variable and the variable can be changed in a function and read outside the function–the value is saved in SRAM
y =0xc9; // int value


char main (void) ////  char is because of the output "x" declared as a char
{
	x&=~y;
	x=y<<3;
	x=y>>4;
	x=y&0x3F;                       /// functions inside the main 
	x^=y;
	x=y&0x10;
	y|=0xF0;
	x|=y;
	x^=y;
}

