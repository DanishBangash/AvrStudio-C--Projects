#include <avr/io.h>    
#include <avr/interrupt.h>
#include <stdio.h> 

#include "LCD.h"    //header file

void lcd_init() {   // Works like a constructor
lcd_direction |= 0xfc;      //	set port A a as output bit 7 downto 2
_delay_ms(2000);      //power on delay
	lcd_port &= ~((1<<PA3) | (1<<PA2));        // EN=0, RS=0
   lcd_nibble_transfer(SET_FUNCTION);
   _delay_ms(24);
   lcd_nibble_transfer(SET_FUNCTION); 
_delay_ms(24);
	lcd_nibble_transfer(SET_FUNCTION);
    _delay_ms(24);
	lcd_nibble_transfer(SET_FUNCTION);
   _delay_ms(24);
   lcd_cmd_write(SET_FUNCTION+LN2_BIT);                 // Function set: 0x28  2 lines
_delay_ms(2);
    lcd_cmd_write(SET_DISPLAY);	           //display off
_delay_ms(2);	
	lcd_cmd_write(CLR_DISPLAY);       // Display clear: 0x01 clear data                 	 
_delay_ms(2);                                              
   lcd_cmd_write(SET_ENTRY_MODE+INC_BIT);          //  +INC_BIT  // Entry mode set: shift cursor 1 position to right
_delay_ms(2);
    lcd_cmd_write(SET_DISPLAY+ON_BIT+CUR_BIT+BLK_BIT);     //+CUR_BIT+BLK_BIT);   Display ON/OFF control: 0x0f
_delay_ms(2);	
lcd_cmd_write(RTN_HOME);
_delay_ms(2);
  
    } // end lcd_init()

// Medium level functions 
// Select RS / RW mode and call lower level funtion to complete the transfer

void lcd_cmd_write(unsigned char cmd)
   { 
    lcd_direction &= 0xfc;
     //lcd_RS=0;
  lcd_port &= ~(1<<PA2);
 asm volatile("NOP");  // Slow down timing 100 nS
   asm volatile("NOP");   // Slow down timing 100 nS
   lcd_transfer(cmd);
   } // end lcd_cmd_write()


void lcd_data_write(unsigned char d)

   {
   lcd_direction &= 0xfc;
   lcd_port|=(1<<PA2);	//rs=1 when writing data
   
  asm volatile("NOP");   // Slow down timing 100 nS
   asm volatile("NOP");   // Slow down timing 100 nS

   lcd_transfer(d); 
   } // end lcd_data_write()

 //Low level functions
// Write to the lcd data bus - generate E pulse 

void lcd_transfer (unsigned char d)

   {
	 lcd_port|= (1<<PA3);
	  asm volatile("NOP");  // Slow down timing 100 nS
     asm volatile("NOP"); // Slow down timing 100 nS
       lcd_nibble_transfer(d);   //(msn)
 
//	 asm volatile("NOP");   // Slow down timing 100 nS	 
	 	asm volatile("NOP");   // Slow down timing 100 nS
		lcd_port |= (1<<PA3);

 lcd_nibble_transfer(d<<4);   //lsn);
 
   } // end lcd_transfer()
void lcd_nibble_transfer( unsigned char d )  
    { 
     lcd_port|= (1<<PA3);
	 asm volatile("NOP");   // Slow down timing 100 nS
   	lcd_port= (lcd_port & 0x0f)| (d &0xf0);   //(always msn as 4 bit data bus)
  	_delay_us(60); // Slow down  60 us
	lcd_port &= ~(1<<PA3);
_delay_us(60);
   } // end lcd_nibble_transfer()
   int main (){
   lcd_cmd_write(0x02);       //cursor home

lcd_cmd_write(0x0c);       //cursor off
   while(1){

}
}
// Software function for delay insertion after commands/data tranfers

void lcd_wait(unsigned int count)

   { 
   unsigned int i;

   for ( i = 0 ; i < count ; i++ );    //4 cycles per count  
   } // end lcd_wait()
