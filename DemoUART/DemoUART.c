#include <avr/io.h>
#include <avr/interrupt.h>
char data=0;

void init ()
{
DDRB |= 0x01; // bit 0 for output
PORTB |= 0x01; /// LED is Off
sei();
}

void init_uart(int baudrate)
{
UCSRB |=(1<<RXEN) | (1<<TXEN)|(1<<RXCIE);
UCSRC |=(1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0); // 8 data bits and 1 stop bit 
UCSRA = (1<<U2X); // full duplex

UBRRH = (char) ( baudrate>>8); // move the upper byte in the integer for fit 8 bits in 16 bits 
UBRRL=(char) baudrate;

}
 void uart_transmit(char Abyte)
{
 while(!(UCSRA & (1<<UDRE)));
 UDR= Abyte;
}

 
 int main()
 {
  init();

  init_uart( 0x40);
  while (1)
  {
    if (data=='a'){
	PORTB &=0x00; // light up the LED
    uart_transmit(data); // to transmit data into terminal
	data=0; //// data clears to zero
	}
	else
	PORTB |=0x01;
  
  }
 }
ISR(USART_RXC_vect)
{
 data = UDR;

}
