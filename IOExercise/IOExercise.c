#include <avr/io.h>  // io library is used for inputs and outputs
#include <util/delay.h> /// a delay library is used to have a delay 


int main(void)
{
DDRB |= (1<<PINB0); /// assigning the first pin for portB to output
//DDRB &=~(1<<PINB4); /// making sure that bit 4 is used as input 
PORTB|=(1<<PINB4); /// SETTING BIT4 FOR PORT REG AS A HIGH READING BIT 

while(1)
{
   PORTB ^= 1 << PINB0; // toggling the led  
      
   
   if (bit_is_clear(PINB, 4)) // if the button is pressed the bit  4 is 1 
   {
    
       _delay_ms(500); /////// blink at delay of 500 ms 
	 }	
   else
   {
   
       _delay_ms(10); /// if the button is not pressed blink at the delay of 10 ms
   }
  }
  
  }

   
