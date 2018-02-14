/*#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>
#define LCD_PRT 	PORTA  //LCD data port
#define LCD_DDR 	DDRA   // LCD data DDR
#define LCD_PIN 	PINA      // LCD DATA PIN
#define LCD_RS 		2      //'LCD RS
#define LCD_EN 		3      // LCD EN
unsigned char counter = 0; //// counter is initialized 
   
	void lcdCommand(unsigned char cmnd)
	{
	LCD_PRT = (LCD_PRT & 0x0F) |(cmnd & 0xF0);  					  
	LCD_PRT &= ~(1<<LCD_RS);                      //RS = 0 FOR COMMAND                       
	LCD_PRT|=(1<<LCD_EN);                        //  EN=  1 FOR H-TO-LO
	_delay_us(1);
	LCD_PRT &=~(1<<LCD_EN);
	_delay_us(100);                               //	 WAIT
	LCD_PRT = (LCD_PRT & 0X0F)|(cmnd <<4);						//
	LCD_PRT |=(1<<LCD_EN);                      // EN=1 FOR HI TO LO
	_delay_us(1);                 				// wait to make EN wider
	LCD_PRT &=~(1<<LCD_EN);						// EN=0 for hi to lo 
	_delay_us(100);
	}

void lcdData (unsigned char data)
{
LCD_PRT =  (LCD_PRT & 0x0F) |(data & 0xF0);     // 
LCD_PRT |= (1<<LCD_RS);                       //RS = 1 FOR DATA
LCD_PRT|=(1<<LCD_EN); 						// EN = 1 FOR HI TO Lo
_delay_us(1);								//WAIT TO MAKE ENABLE WIDER
LCD_PRT &=~(1<<LCD_EN);                     // EN=0 FOR H TO L
LCD_PRT = (LCD_PRT & 0X0F)|(data <<4);
LCD_PRT |=(1<<LCD_EN);                      // EN=1 FOR HI TO LO
_delay_us(1);                 				// wait to make EN wider
LCD_PRT &=~(1<<LCD_EN);						// EN=0 for hi to lo      
}
void lcd_init()
{
LCD_DDR = 0xFF;   // LCD PORT IS OUTPUT
LCD_PRT &=~(1<<LCD_EN); //LCD_EN = 0
_delay_us(2000);//wait for stable power
lcdData(0x0C);
_delay_us(100);
lcdData(0x0C);
_delay_us(100);
lcdData(0x0C);
_delay_us(100);
lcdData(0x04);
_delay_us(100);
lcdCommand(0x33);//$33 for 4 bit mode
_delay_us (100);  
lcdCommand(0x32);//$32 
_delay_us (100);  
lcdCommand(0x28);// $28
_delay_us (100);
lcdCommand(0x0e);//display on cursor on
_delay_us (100);
lcdCommand(0x01);// clear lcd
_delay_us (2000);
lcdCommand(0x06); // shift cursor right
_delay_us (100);
}

void lcd_gotoxy(unsigned char x, unsigned char y)
{ //Table 12-5
static unsigned char firstCharAdr[] = {0x80, 0xC0, 0x94, 0xD4};
lcdCommand(firstCharAdr[y-1] + x-1);
_delay_us(100);
}

void lcd_print(char * str)
{
//unsigned char i=0;
while (str[i] !=0)
{
lcdData(str[i]);
i++;

char c;
   for (; (c = *str) != 0; str++)
    lcdData(c); 
}*/
// This content is located in lcdm.h and only included here for simplicity

#include <avr/io.h>    
#include <avr/interrupt.h>
#include <stdio.h> 


#include "lcdo.h"  // File with #define statements and prototypes for the lcdm.c module
#include "Keypad1.h"
#include "press.h"

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
for (; (c = *str) != 0; str++) lcd_data_write(c);

  
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








