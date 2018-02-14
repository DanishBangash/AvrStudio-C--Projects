#include <avr/io.h>
#include <avr/interrupt.h>

//volatile char ms=0;
volatile int timeOut=0;
void init_timer1(char flag){

TCCR1A=(0<<COM1A1)|(0<<COM1B1)|(0<<COM1A0)|(0<<WGM11)|(0<<WGM10);   //enable timer1 out for simulation of pedal speed
TCCR1B=(1<<WGM12)|(1<<CS11); /*prscaling by 8 - 1250000 Hz*/
//TCCR1B=0x0A;

OCR1A=0x04E2;  //04E2gives 1 msec compare og 30D4 gives 10ms 
TCCR1A=0x0000;
if (flag==1)
TIMSK|=(1<<OCIE1A);   //enable timer 1 and disable timer 0 compare interrupt
else
TIMSK&=~(1<<OCIE1A);
asm("SEI");

}
/*ISR(TIMER1_COMPA_vect)

{

timeOut++;
ms++;



}
*/
