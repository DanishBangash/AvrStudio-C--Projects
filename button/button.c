#include <avr/io.h>
#define F_CPU 10000000UL
#include <util/delay.h>


int main(void){
	DDRB =0x01;          
	PORTB =0x01;
   
   while(1)
   {

	   if (!(PINB  & 0b00000010 ))
	   {
	    _delay_ms(10);
		PORTB =0x00;
	   }
  /* else
   {
    _delay_ms(100);
   }*/
   }
}
