#include <avr/io.h>
#include <avr/interrupt.h>
#include "lcdo.h"
#include "keypad.h"
#define max 14
	char data=0;
	char key;
	volatile char spi_data_ready =0;
volatile unsigned char spi_flag=0;
	char buffer[max];
	char Hexbuffer[2];
	volatile int i=0; 
	volatile int j=0;
	volatile int ii=0;
	void init ()
	{   
	    DDRB |= 0x01; ///// a 1 on the bit zero of the register B
		PORTB|=0x01; ////  set the out put on the portB LED Off
	    GICR |=(1<<INT0)|(1<<INT1); /// register containing the INT0
		MCUCR |=(1<<ISC01)|(1<<ISC00)|(1<<ISC10); //risin edge
	DDRB |= 0x00; // bit 0 for output
	PORTB |= 0x00; /// LED is Off
//	PORTD |=(1<<PD3)|(1<<PD2);
    TCCR0 |= (1<<CS01); // timer 0 normal mode 8 prescaler
	sei();
	}

	void init_uart(int baudrate)
	{
	UCSRB |=(1<<RXEN) | (1<<TXEN)|(1<<RXCIE);
	UCSRC |=(1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0); // 8 data bits and 1 stop bit 
	UCSRA |= (1<<U2X); // full duplex

	UBRRH = (char) ( baudrate>>8); // move the upper byte in the integer for fit 8 bits in 16 bits 
	UBRRL=(char) baudrate;

	}
	 void uart_transmit(char cdata)
	{
	 while(!(UCSRA & (1<<UDRE)));     ///wrong ==0 only please read the manual careful.p. 154
	 UDR=cdata;
	 
	}
	unsigned char uart_recieve(void)
	{
	while (!(UCSRA &(1<<RXC)));
	spi_flag = 1;
	return UDR;
	
	}
		void PutString(char *str) {
   char c;
   for (; (c = *str) != 0; str++)
    uart_transmit(c); //transmit char handles the individual character
	}
	 int main()
	 {
	key_init();
	  init();
  		lcd_init();
	  init_uart( 0x40);
		  while (1)
		  {
		    if (spi_data_ready==1){
			//uart_transmit(0xF5);
			
			uart_recieve();
			spi_data_ready=0;
				
		  }
		}
		}
	 ISR(USART_RXC_vect)
	 {  
	 	data=UDR;
		buffer[i]=data;
	// spi_data_ready=1;
	// i++;
	if((j<max)){//&&(data!=0x86)
	 sprintf(Hexbuffer, "%02X", data);
		buffer[i]=Hexbuffer[1];
		i--;
	
		buffer[i]=Hexbuffer[0];
		ii=0;
		i--;
		 PORTB &=0xFE;
		}
	 if (i==max-7) {
	 spi_data_ready=1;
	  //i=0;
	 i=max-1;
	 }
	 else j++;			 
	 LCDPutString(buffer);
		  } 
		  	 



