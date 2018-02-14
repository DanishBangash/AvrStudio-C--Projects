#include <avr/io.h>

void main (void)
{
  DDRB = 0b00000001; //DATA direction register and assigning pin0 on portB to output
  PORTB = 0B00000001;// assigning 5v to pin0
  
while(1)
{
  

}
}
