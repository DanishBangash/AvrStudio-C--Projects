
#include <avr/io.h>
#define F_CPU 10000000UL
#include <util/delay.h>

#define key_PORTA		PORTA
#define key_PORTC		PORTC
//#define key_PORTB		PORTB

#define key_PINB		PINB
#define key_PINC		PINC
#define key_PINA		PINA

//#define key_DDRB		DDRB
#define key_DDRC		DDRC
#define key_DDRA		DDRA


#define key_row0 		0 
#define key_row1 		1

#define key_col0 		6
#define key_col1 		7

#define key_active 		PB2

#define row3			case 0
#define row2			case 1
#define row1			case 2
#define row0			case 3

void key_read();
void key_init();
void key_look();
