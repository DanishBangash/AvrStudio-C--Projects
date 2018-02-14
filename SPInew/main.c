#define F_CPU 10000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "spi.h"			// define SPI functions.
#define TIMER0_PRESCALER  0
#define TIMER1_PRESCALER  3
#define TIMER2_PRESCALER  0
// The timer frequency is the prescaler frequency divided by the divisor.
// Set the divisor for each timer
#define TIMER0_DIVISOR    1  // allowed range: 1 - 255
#define TIMER1_DIVISOR    15625  // allowed range: 1 - 65535
#define TIMER2_DIVISOR    1  // allowed range: 1 - 255

// Set the defines below if you want an output pin to toggle for each
// time a timer reaches its final count. The output will be a square
// wave with half the timer frequency:
#define TIMER0_TOGGLE     0  // (port B bit 3)
#define TIMER1_TOGGLE     0  // (port D bit 5)
#define TIMER2_TOGGLE     0  // (port D bit 7)

volatile unsigned char cardPresent = 0;
volatile unsigned char dataReady = 0;

void Initialize (){

	// Timer/Counter 1 initialization
	#if TIMER1_PRESCALER
		TCCR1A = (TIMER1_TOGGLE<<6);
		TCCR1B = 8 | TIMER1_PRESCALER;
		TCNT1  = 0;
		OCR1A  = TIMER1_DIVISOR;
		OCR1B  = 0;
	#else
		TCCR1A = 0;
		TCCR1B = 0;
		TCNT1  = 0;
		OCR1A  = 0;
		OCR1B  = 0;
	#endif
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
	// Timer/Counter1 Interrupt enable
	TIMSK = ((TIMER1_PRESCALER!=0)<<4);

	// External interrupts 
	GICR   |= 0b11000000;
	MCUCR  |= 0b00001111;
	MCUCSR |= 0b00000000;
	GIFR   |= 0b11000000;
	// Enable interrupts
//	SetInterrupt();
}
//External Interrupt.
ISR(SIG_INTERRUPT0){
	cardPresent = 1;
}

ISR(SIG_INTERRUPT1){
	dataReady = 1;
}
 int main()

 {
  init_uart(0x40);
		while(1)
	{
		// Operate gate state machine.
	//	checkOnGate();

		
		// send to the cardReader with Command(0x55).
		if(cardPresent == 1){			
			sendSPI(0x55);
			cardPresent = 0;
		
		}

		// If data is ready from cardReader read cardID.
		if((dataReady == 1)){
		
			dataReady = 0;
		
		}
		}
		}
