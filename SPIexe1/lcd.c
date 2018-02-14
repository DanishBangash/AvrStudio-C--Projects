/*#include <avr/io.h>
#include <avr/interrupt.h>
#define max 8
	char data=0;
	volatile char spi_data_ready =0;
volatile unsigned char spi_flag=0;
	char buffer[max];
	volatile int i=0; 
	void init ()
	{   
	    DDRB |= 0x01; ///// a 1 on the bit zero of the register B
		PORTB|=0x01; ////  set the out put on the portB LED Off
	    GICR |=(1<<PD3)|(1<<PD2); /// register containing the INT0
		MCUCR |=(1<<ISC01)|(1<<ISC00)|(1<<ISC10); //risin edge
	DDRB |= 0x01; // bit 0 for output
	PORTB |= 0x01; /// LED is Off
//	PORTD |=(1<<PD3)|(1<<PD2);
    TCCR0 |= (1<<CS01); // timer 0 normal mode 8 prescaler
	sei();
	}

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
		void SPI_MasterInit(void)
		{
		DDRB |=(1<<PB5)|(1<<PB4)|(1<<PB7)|(1<<PB2);
		SPCR |= (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	    PORTB|=(1<<PB4);
		PORTB|=(1<<PB6);

		}


		void SPI_MasterTransmit(char cData)
		{
		PORTB|=(1<<PB4);
		SPDR = cData;
		while(!(SPSR & (1<<SPIF)));
	    PORTB|=(1<<PB4);
		}

		void SPI_slaveInit(void)
		{
		DDRB |= (1<<PB5);

		SPCR |= (1<<SPE)|(1<<SPIF);
		PORTB|(1<<PB6);

		}
		void SPI_Transmit(char cData)
		{
		 SPDR = cData;
		 while(!(SPSR & (1<<SPIF)));
		 PORTB|=(1<<PB6);	
		}

		char SPI_SlaveRecieve(void)
		{
		while(!(SPSR & (1<<SPIF)));
		spi_flag = 1;
		return SPDR;
		}
	 int main()
	 {
	  init();
  
	  init_uart( 0x40);
	SPI_MasterInit();
    SPI_slaveInit();
	//done as:
	char card_flag=0;
	char data_flag=0;
	while(1) {
 
	if (PIND & ((1<<PD2)== 0x04))
	card_flag=1;
 
	if (PIND &((1<<PD3)==0x08))
	data_flag=1;
 
	if (card_flag==1)
	{
	SPI_MasterTransmit(0x55);
	card_flag=0;
	}
 
	if (data_flag==1) {
    SPI_MasterTransmit(0xF5);
	data_flag=0;	
	}
	ISR(INT1_vect)
	 {
	  // PORTB |=0x01;
	  TIMSK |=(1<<TOV0);
	  if (data_flag==1)
	  {
	   TIMSK &=~(1<<TOV0);
	   data_flag=0;
	  }
	  else
	   data_flag=1;
	   }
	//coden fra interupt 1 service routinen
	}
	}
	}
		 ISR(INT0_vect)
	{
	// PORTB &=0xF7;
	 SPI_MasterTransmit(0xF5);  //getting the uid from rfid tag
	}
	 ISR(INT1_vect)
	 {
	  // PORTB |=0x01;
	  TIMSK |=(1<<TOV0);
	 
	  if (spi_flag==1)
	  {
	   TIMSK &=~(1<<TOV0);
	   spi_flag=0;
	  }
	  else
	   spi_flag=1;
	 }
	 ISR(TIMER0_OVF_vect)
	 {

	  SPI_MasterTransmit(0xF5);
	 //data=SPDR;
	 buffer[i]=SPDR ;
	 if (i<max) i++;
	  else {
	 i=0;
	 if (i==max) data=1;
	 }
}
	
	ISR(USART_RXC_vect)
	{
	 spi_data_ready = UDR;

	}*/

#include <avr/io.h>    
#include <avr/interrupt.h>
#include <stdio.h> 


#include "lcdo.h"  // File with #define statements and prototypes for the lcdm.c module


//#define FUNCTION_SET  0x28  // etc......
#define OFFSET        0x40   //2nd line
#define lcd_RS 2
//#define lcd_RW 1
#define lcd_E 3
//#define lcd_BUSY 7




char disp_buffer[32];    // One dimensional
//unsigned char disp_buffer[2][16]; // Two dimensional

unsigned char indx=0;
unsigned char inx=0;
unsigned char tmp;
unsigned char lcd_x=0;
unsigned char lcd_y=0;
unsigned char lcd_maxx=16;


// Setup your hierarchy of functions
// Names are just a proposal for your inspiration 

//*******************************************************************
// LCD initialization sequence (works somewhat like a constructor)
//*******************************************************************

void lcd_init()    // Works like a constructor
   
   {

   // Power on delay
	lcd_direction |= 0xfc;							//	set port a as output
   lcd_wait( 20000 );                                   // Power on wait 
   lcd_wait( 20000 );
	lcd_port &= ~((1<<lcd_E) | (1<<lcd_RS)); // EN=0, RS=0
//	lcd_port &= ~(1<<lcd_RW);               // Set RW = 0 in case it is connected
 
   lcd_nibble_transfer(SET_FUNCTION+IN8_BIT);
   //lcd_wait(longdelay );  						 // wait 24 ms
   _delay_ms(24);
   lcd_nibble_transfer(SET_FUNCTION+IN8_BIT);
   //lcd_wait(longdelay);
    _delay_ms(24);
	lcd_nibble_transfer(SET_FUNCTION+IN8_BIT);
   //lcd_wait(longdelay);
    _delay_ms(24);
	lcd_nibble_transfer(SET_FUNCTION);
  // lcd_wait(longdelay);
   _delay_ms(24);
   lcd_cmd_write(SET_FUNCTION+LN2_BIT);                 // Function set: 0x28  2 lines
  // lcd_wait(WAIT_15m);                              // Wait 39 uS
 _delay_ms(2);
    lcd_cmd_write(SET_DISPLAY);						//display off
 //lcd_wait(WAIT_15m);
_delay_ms(2);	
	lcd_cmd_write(CLR_DISPLAY);       // Display clear: 0x01 clear data                 	 
	
  // lcd_wait(WAIT_15m);                // 1.53 mS  
     _delay_ms(2);                  
                               

   lcd_cmd_write(SET_ENTRY_MODE+INC_BIT);          //  +INC_BIT  // Entry mode set: shift cursor 1 position to right
  //   lcd_wait(WAIT_15m);      
  _delay_ms(2);
    lcd_cmd_write(SET_DISPLAY+ON_BIT+CUR_BIT+BLK_BIT); //+CUR_BIT+BLK_BIT);   Display ON/OFF control: 0x0f
  //   lcd_wait(WAIT_15m);                               // Wait 39 uS                      // 1.53 mS     
_delay_ms(2);	
	lcd_cmd_write(RTN_HOME);
  //lcd_wait(WAIT_15m);                            // 1.53 mS  
_delay_ms(2);
  
   } // end lcd_init()






//******************************************************************************************
// Medium level functions 
// Select RS / RW mode and call lower level funtion to complete the transfer

void lcd_cmd_write(unsigned char cmd)
   { 
    lcd_direction |= 0xfc;
     //lcd_RS=0;
  lcd_port &= ~(1<<lcd_RS);
 
  // lcd_port &= ~(1<<lcd_RW);
  asm volatile("NOP");  // Slow down timing 100 nS
   asm volatile("NOP");   // Slow down timing 100 nS
   lcd_transfer(cmd);
   } // end lcd_cmd_write()


void lcd_data_write(unsigned char d)

   {
   lcd_direction |= 0xfc;
   lcd_port|=(1<<lcd_RS);				//rs=1 when writing data
   
  // lcd_port &= ~(1<<lcd_RW);
    asm volatile("NOP");   // Slow down timing 100 nS
   	asm volatile("NOP");   // Slow down timing 100 nS

   lcd_transfer(d); 
   } // end lcd_data_write()


//********************************************************************************************
// Low level functions
// Write to the lcd data bus - generate E pulse 

void lcd_transfer (unsigned char d)

   {
	 lcd_port|= (1<<lcd_E);
	  asm volatile("NOP");  // Slow down timing 100 nS
     asm volatile("NOP"); // Slow down timing 100 nS
 lcd_nibble_transfer(d);   //(msn)
 
//	 asm volatile("NOP");   // Slow down timing 100 nS	 
	 	asm volatile("NOP");   // Slow down timing 100 nS
		lcd_port |= (1<<lcd_E);

 lcd_nibble_transfer(d<<4);   //lsn);
 
   } // end lcd_transfer()


void lcd_nibble_transfer( unsigned char d )  
 
   { 
     lcd_port|= (1<<lcd_E);
	 asm volatile("NOP");   // Slow down timing 100 nS
   	lcd_port= (lcd_port & 0x0f)| (d &0xf0);   //(always msn as 4 bit data bus)
  
  	
 	 //lcd_wait(8);   // Slow down  58 us
_delay_us(60);
	lcd_port &= ~(1<<lcd_E);
//	lcd_wait(8);
_delay_us(60);
   } // end lcd_nibble_transfer()




//clear the display
void lcdClear(void) {

lcd_cmd_write(CLR_DISPLAY);
//lcd_wait(WAIT_15m);
lcd_cmd_write(CLR_DISPLAY+RTN_HOME);
//lcd_wait(WAIT_15m);


}

void clearLine(unsigned char x, unsigned char y){

unsigned char max_x=20;

GoTo(x,y);
for (int i=x; i<max_x; i++)
{
lcd_data_write(0x20);
_delay_ms(1);
}
GoTo(x,y);
}

// Software function for delay insertion after commands/data tranfers




//! write a zero-terminated ASCII string to the display
void LCDPutString(char *str) {
   char c;
for (; (c = *str) != 0; str++) 
lcd_data_write(c);  
}
void lcd_wait(unsigned int count)

   { 
   unsigned int i;

   for ( i = 0 ; i < count ; i++ );    //4 cycles per count
    // end lcd_wait()

  

   } // end lcd_transfer()

//goto x-position and y-line called by parameters x, y used in main() and internally LCDPutChar()

void GoTo(unsigned char x, unsigned char y){

switch (y) {
case 0: 

 lcd_cmd_write(SET_DRAM_ADDR+x);
 lcd_wait(WAIT_15m);  
 break;

 case 1: 

lcd_cmd_write(SET_DRAM_ADDR+line_1+x);
 lcd_wait(WAIT_15m);  
break;

case 2:
lcd_cmd_write(SET_DRAM_ADDR+line_2+x);
 lcd_wait(WAIT_15m);  
break;

case 3:
lcd_cmd_write(SET_DRAM_ADDR+line_3+x);
 lcd_wait(WAIT_15m);  
break;
default:

break;
}

}
 
