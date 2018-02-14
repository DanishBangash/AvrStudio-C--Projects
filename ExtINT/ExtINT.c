#include <avr/io.h>
#include <avr/interrupt.h>
unsigned char count = 0; //// declared a global variable count = 0 

init()  //// init function for initializing intrrupts and ports
{
  sei();
    
    DDRB= 0x01; ///// a 1 on the bit zero of the register B
	PORTB=0x01; ////  set the out put on the portB LED Off
    GICR |=(1<<INT0); /// register containing the INT0
	MCUCR |=(1<<ISC01); 

}

 void blink()  /// blink method for blinking the LED
 {
   if (count=(0x50)) 
   {
    PORTB ^=0x00;

   }
   
 }
 ISR(INT0_vect)
{
 //PORTB ^= 0x00;
 count++ ;
}

int main(void)
{
   
    init();
	while(1)
	
	{
	  
	 ISR(INT0_vect);
	 void blink();  
	  }
	
	
}
