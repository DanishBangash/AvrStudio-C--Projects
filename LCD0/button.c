#include <avr/io.h>
#define F_CPU 10000000UL
#include <util/delay.h>


int main(void)
{
	DDRB |= 1<<PB0;
	DDRB&=~(1<<PB2);
	PORTB |=1<<PB2;
   
   while(1)
   {
   PORTB ^=1<<PB0;
   _delay_ms(100);
   if(bit_is_clear(PINB, 2)
   {
    _delay_ms(10);
   }
   else
   {
    _delay_ms(100);
   }
   }
}
