#include <avr/io.h>
#include <avr/interrupt.h>
//#include <util/delay.h>
//#define F_CPU 1000000UL
#define max 8
	char x=0;
	volatile char data_flag=0;
	volatile unsigned char card_flag=0;
	char buffer[max];
	volatile int i=0; 
	void init ()
	{   
	  /*  GICR |=(1<<INT1)|(1<<INT0); /// register containing the INT0
		MCUCR |=(1<<ISC01)|(1<<ISC00)|(1<<ISC10)|(1<<ISC11); //risin edge*/
		//GIFR   |= 0b11000000;
	//	MCUCSR |= 0b00000000;
		DDRB |= 0x01; // bit 0 for output		
		//PORTD|=(1<<PD2)|(1<<PD3);
		PORTB |= 0x01; /// LED is Off	
	//	SPSR =0b00000000;
	    TCCR0 |= (1<<CS01)|(1<<CS00); // timer 0 normal mode 8 prescaler	
		sei();
	}

	void init_uart(int baudrate)
	{
	UCSRB |=(1<<RXEN) | (1<<TXEN)|(1<<RXCIE);
	UCSRC |=(1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0); // 8 data bits and 1 stop bit no parity bit 
	UCSRA = (1<<U2X); // full duplex

	UBRRH = (char) ( baudrate>>8); // move the upper byte in the integer for fit 8 bits in 16 bits 
	UBRRL=(char) baudrate;

	}


	 void uart_transmit(char data)
	{
	 while(!(UCSRA & (1<<UDRE)));     ///wrong ==0 only please read the manual careful.p. 154
	 UDR=data;
	 
	}
		void PutString(char *str) {
   char c;
   for (; (c = *str) != 0; str++)
    uart_transmit(c); //transmit char handles the individual character
}
	
		void SPI_MasterInit(void)
		{
		DDRB |=(1<<PB5)|(1<<PB4)|(1<<PB7);
		SPCR |= (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	    PORTB|=(1<<PB4)|(1<<PB6)|(1<<PB7);
		}


		void SPI_MasterTransmit(char x)
		{
		PORTB&=~(1<<PB4);
		SPDR = x;
		while(!(SPSR & (1<<SPIF)));
	    PORTB|=(1<<PB4);
		}

	/*	void SPI_slaveInit(void)
		{
		DDRB |= (1<<PB5);
		SPCR |= (1<<SPE)|(1<<SPIF);
		PORTB|=(1<<PB6);
		}  

		void SPI_Transmit(char cData)
		{
		 SPDR = cData;
		 while(!(SPSR & (1<<SPIF)));
		 PORTB|=(1<<PB6);	
		}

		char SPI_SlaveRecieve(void)
		{
		PORTB &= ~(1<<PB4);
     	SPDR = 0xF5;
		while(!(SPSR & (1<<SPIF))){}
		PORTB|=(1<<PB4);
		return SPDR;
		}*/
	 ISR(SIG_INTERRUPT0)
		{	 
          card_flag=1;
		}

	 ISR(SIG_INTERRUPT1)
		 { 
		   data_flag=1;
		 }
     ISR(TIMER0_OVF_vect)
	 {
	 data_flag=1;
	 SPI_MasterTransmit(0xF5);   // to transmit data into terminal
    PORTB &=~(1<<PB0);
	 }
	ISR(USART_RXC_vect)
	{
	 SPDR= UDR;
	}  
		 int main()
		 {
		  init();
  		  	init_uart( 0x40);
		   	SPI_MasterInit();	 
	//	int i=0;  
	volatile	char flag=0; 
			  while (1)
			  {
			//	PORTB &=~(1<<PB0);
		
					if (flag==0) {
						if ((PIND & 0x04)==0x04) { 
						card_flag=1;  //bit mask should be 0x04 not 1<<PD2					
			
						}
            		}    
				if ((PIND & 0x08)== 0x08)  {
				TIMSK |=(1<<TOV0);  //bit mask should be 0x08 not (1<<PD3)!
					
				}
 
				if (card_flag==1)
				{
				flag=1;
				SPI_MasterTransmit(0x55);			
				card_flag=0;
				}
				if (data_flag==1)
				{	            	     
				data_flag=0;
								
				buffer[i]=SPDR;
			
			
					i++;
					}
			     if(i==max) {
					TIMSK &=~(1<<TOV0);
					flag=0;
					i=0;                             //reset for i was missing
					PutString(buffer);
					}   
			 	
		  
		  
		  }
		  
		  
return (0);
		  }
 
		

