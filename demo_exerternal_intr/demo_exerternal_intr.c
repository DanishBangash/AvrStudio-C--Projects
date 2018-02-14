#include <avr/io.h>
#include <avr/interrupt.h>
#define max 8;
char flag =0;
int i =0;

void init()
{
//init the erxternal intterupt 1 activated by a low level on PIND bit3
GICR |=(1<<INT1); /// GICR |= 0x80; GICR |= 0b10000000;
SREG = 0X80; // enabeling the global interupt 
// alternativeasm("SETI"); //?
DDRB|=!(1<<PB0);
PORTB |=!(1<<PB0);
}

int main()

{
init();

while(1)
{
   if (flag==1)
   {
   flag=0;
   PORTB |=(1<<PB0);
    /* if(i<=max)
	 {
	 	//i=0;
		PORTB |=(1<<PB0);
	 
	 }   */
   }

}

}

ISR(INT1_vect) {
flag=1;
i++;
}
