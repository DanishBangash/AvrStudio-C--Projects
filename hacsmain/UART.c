#include "UART.h"
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
	unsigned char uart_recieve(void)
	{
	while (!(UCSRA &(1<<RXC)));
	return UDR;
	}
		void PutString(char *str) {
   char c;
   for (; (c = *str) != 0; str++)
    uart_transmit(c); //transmit char handles the individual character
}

