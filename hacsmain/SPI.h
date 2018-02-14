#include <avr/io.h>
#include <avr/interrupt.h>
#define max 14
// define connections
#define SPI_SS			4 // !SS CONECTED TO PB4
#define SPI_MOSI		5 // MOSI TO PB5
#define SPI_MISO		6 //MISO PB6
#define SPI_SCK 		7 //SCK TO PB7
#define SPI_INT0		2 // INTERRUPT 0 TO PD2
#define SPI_INT1		3 //INTTERUPT 1 TO PD3
// Functions Prototypes
extern  void SPI_MasterInit();				  //  initialize SPI
extern  void SPI_MasterTransmit(char x);	 // TRANSMIT DATA
extern  void init ();
extern  char receiveSPI();



