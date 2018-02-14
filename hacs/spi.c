#include "spi.h"

	void init ()
	{   
	  
		DDRB |= 0x01; // bit 0 for output		
		PORTB |= 0x01; /// LED is Off	
	    TCCR0 |= (1<<CS01)|(1<<CS00); // timer 0 normal mode 8 prescaler		
	}
void SPI_MasterInit(void)
		{
		DDRB |=(1<<SPI_MOSI)|(1<<SPI_SS)|(1<<SPI_SCK);
		SPCR |= (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	    PORTB|=(1<<SPI_SS)|(1<<SPI_MISO)|(1<<SPI_SCK);
		}

char receiveSPI(){
	//PORTB &= ~(1<<SPI_SS);
//	SPDR = 0xF5;
	while(!(SPSR & (1<<SPIF))){}
	PORTB |= (1<<SPI_SS);
	return SPDR;
}


		void SPI_MasterTransmit(char data)
		{
		PORTB&=~(1<<SPI_SS);
		SPDR = data;
		while(!(SPSR & (1<<SPIF)));
	    PORTB|=(1<<SPI_SS);
		}

		
