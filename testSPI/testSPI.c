#include <avr/io.h>
#define MOSI 5
#define SCK7

int main(void)
{
  DDRB = (1<<PB5)|(1<<PB7);
  DDRA = 0XFF;
  SPCR = (1<<PB6)|(1<<PB4)|(1<<PB0);
 void uart_transmit(char Abyte)
{
 while(!(SPSR & (1<<PB7)));
 UDR= Abyte;
}

  while(1)
  {
  SPDR = 'G';
  while(!(SPSR & (1<<PB7)));
  PORTB = SPDR;
  }

return 0;

}
