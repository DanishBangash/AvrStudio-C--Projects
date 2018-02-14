#include"Timer.h"
	void init ()
	{   
	    DDRB |= 0x01; ///// a 1 on the bit zero of the register B
		PORTB|=0x01; ////  set the out put on the portB LED Off
	    GICR |=(1<<INT0)|(1<<INT1); /// register containing the INT0
		MCUCR |=(1<<ISC01)|(1<<ISC00)|(1<<ISC10); //risin edge
	DDRB |= 0x00; // bit 0 for output
	PORTB |= 0x00; /// LED is Off
    TCCR0 |= (1<<CS01); // timer 0 normal mode 8 prescaler
	sei();
	}
