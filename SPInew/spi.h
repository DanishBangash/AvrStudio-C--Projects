#include <avr/interrupt.h>



/////////////////////////////////////////////////////////////////////////
//                       Port and pin definitions                      //
/////////////////////////////////////////////////////////////////////////

// Define which ports the SPI is connected to:

#define SPI_PORT	PORTB
#define SPI_PINB	PINB
#define SPI_PIND	PIND

#define SPI_DIRECTIONB	DDRB
#define SPI_DIRECTIOND	DDRD

// Define Connections.
#define SPI_SS		4
#define SPI_MOSI	5
#define SPI_MISO	6
#define SPI_CLOCK	7
#define SPI_INT0	2
#define SPI_INT1	3


/////////////////////////////////////////////////////////////////////////
//                       Function prototypes:        	               //
/////////////////////////////////////////////////////////////////////////

//Initialize the SPI
void SPIInt();

//Receive Data from SPI
char receiveSPI();

//Send Data to SPI.
void sendSPI(char x);

//Read card ID
void readCardId(unsigned char cardId[]);
