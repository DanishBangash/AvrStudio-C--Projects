#include <avr/io.h>  /// library for input output 
#define F_CPU 10000000 /// set the clock frequency to 10000000
#include <util/delay.h> //// library used to have a delay 
#include <avr/interrupt.h> /// library for the interrupts 

int main(void){    /// main method 

unsigned char counter = 0; //// counter is initialized 
    DDRB= 0b00000001; ///// a 1 on the bit zero of the register B
	PORTB=0b00000001; ////  set the out put on the portB LED Off
   while(1){ ///// while 1
	   if (!(PINB  & 0b00010000 ))   {	/// if not PINB & bit4
	   		 _delay_ms(25); ////// with a delay of 25 ms 
	  		 if (!(PINB  & 0b00010000 )){ ///// if not PINB & bit4
			     counter++; /// increment the counter 
				 while(!(PINB  & 0b00010000 )){} /// while not PINB & bit4  looop
			    
	   		 }
		}
		if (counter >= 10){       ///// if the counter is greater or equal to 10 
		      PORTB &= 0b00000000; //// the LED which is bit0 of PORT B
		 }
		 
		 if(!(PORTB & 0b00000001)){
		     if (!(PINB  & 0b00010000 ))   {	/// if not PINB & bit4
	   		 _delay_ms(25); ////// with a delay of 25 ms 
	  		 if (!(PINB  & 0b00010000 )){ ///// if not PINB & bit4
			     counter--; /// increment the counter 
				 while(!(PINB  & 0b00010000 )){} /// while not PINB & bit4  looop
			    
	   		 }
		}
		if (counter >= 0){       ///// if the counter is greater or equal to 10 
		      PORTB &= !(0b00000000); //// the LED which is bit0 of PORT B
		 }
		 }	
	}
  return 0 ;            //// beside everything return 0

}
