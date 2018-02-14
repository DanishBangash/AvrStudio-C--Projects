#include <avr/io.h> 
#include <avr/interrupt.h>



	void SPI_MasterInit(void)
	{
	DDRB =(1<<PB5)|(1<<PB7);
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	}


	void SPI_MasterTransmit(char cData)
	{
	SPDR = cData;
	while(!(SPSR & (1<<SPIF)));

	}

	void SPI_slaveInit(void)
	{
	DDRB = (1<<PB5);

	SPCR = (1<<SPE);

	}
	char SPI_SlaveRecieve(void)
	{
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
	}
	void blink()
	{
	 PORTA ^=0b00111111;
	}
int main()
{

void SPI_MasterInit(void);
void SPI_MasterTransmit(char cData);
void SPI_slaveInit(void);
char SPI_SlaveRecieve(void);
while(1){}
void blink();
}
