#include <avr/io.h>
#define SETBIT(DDRB,BIT)(DDRB|=(1<<BIT))/// setting bit to DDRB
#define DIRBIT(DDRB, BIT)(DDRB|=(1<<BIT))/// assigning the direction bit to DDRB
#define CLRBIT(DDRB,BIT)(DDRB &=~(1<<BIT))// clearing the bit of DDRB
#define CHKBIT(DDRB,BIT)(DDRB&(1<<BIT) // checking the bit on DDRB

int main() // main method
{
while(1){
DIRBIT(DDRB,0);/// assigned the direction bit to the DDRB bit 0
if(bit_is_clear(PINB,4)) // if button is pressed 
{
   PORTB ^=(1<<PB0); // Shift 1 to bit 0 of port B and LED is on 
}

}
return(0); //// off the LED 


}
