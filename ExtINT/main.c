#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
    sei();
    unsigned char count = 0; //// declared a global variable count = 0    

    DDRB= 0b00000001; ///// a 1 on the bit zero of the register B
	PORTB=0b00000001; ////  set the out put on the portB LED Off
    GICR |=(1<<INT0);
	MCUCR |=(1<<ISC01);
	while(1)
	
	{
	
	
	}




}
ISR(INT0_vect)
{
 PORTB ^= 0b00000000;
 count++


}
