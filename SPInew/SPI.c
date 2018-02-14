#define F_CPU 10000000UL
#include <util/delay.h>
#include "spi.h"
#include <avr/io.h>

/////////////////////////////////////////////////////////////////////////
//                       Local variables                               //
/////////////////////////////////////////////////////////////////////////

	unsigned char accept;
	unsigned char x = 0;
	int i = 0;


/////////////////////////////////////////////////////////////////////////
//                    Public functions         			               //
/////////////////////////////////////////////////////////////////////////

//Initialize the SPI
void SPIInt(){

	// Set the SPI Registers.

	// SPI Control register SPCR
	// bit7 Interupt disabled.
	// bit6 SPI Enable.
	// bit5 MSB first.
	// bit4 Set to Master.
	// bit3 Rising Edge.
	// bit2 phase sample.
	// bit1 and bit0 fosc/16 = 625 Khz.
	SPCR = 0b01010001;

	// SPI Status Register SPSR
	SPSR = 0b00000000;

	SPI_DIRECTIONB &= ~(1<< SPI_MISO);
	SPI_DIRECTIONB |= (1<< SPI_MOSI);
	SPI_DIRECTIONB |= (1<< SPI_SS);
	SPI_DIRECTIONB |= (1<< SPI_CLOCK);
	
	SPI_DIRECTIOND &= ~(1<< SPI_INT0);
	SPI_DIRECTIOND &= ~(1<< SPI_INT1);

	SPI_PORT |= (1<<SPI_SS);
	SPI_PORT &= ~(1<<SPI_MOSI);

}


//Receive Data from SPI
char receiveSPI(){
	SPI_PORT &= ~(1<<SPI_SS);
	SPDR = 0xF5;
	while(!(SPSR & 0b10000000)){}
	SPI_PORT |= (1<<SPI_SS);
	return SPDR;
}

//Send Data to SPI.
void sendSPI(char x){
	SPI_PORT &= ~(1<<SPI_SS);
	SPDR = x;
	while(!(SPSR & 0b10000000)){}
	SPI_PORT |= (1<<SPI_SS);
}

//Read card ID
void readCardId(unsigned char cardId[]){
	accept = receiveSPI();
	if(accept == 0x86) {
		i = 6;
		while(i >= 0){
			_delay_us(10);
			x = receiveSPI();
			cardId[i] = x;
			i--;
		}
	}
}
