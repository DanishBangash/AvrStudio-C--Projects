#include <avr/io.h>  // io library is used for inputs and outputs
//#include <util/delay.h> /// a delay library is used to have a delay 
#include "Lights.h"

void Light_on(void)
{
DDRD |= (1<<PD4); /// assigning the first pin for portB to output
PORTD|= (1<<PD4); /// SETTING BIT4 FOR PORT REG AS A HIGH READING BIT 
}
void light_Off()
{
   PORTD = 0b00000000;
   DDRD  = 0b00000000;
  }

   
