// Include file for the LCD module 2 x 16   2012-03-23 osc
#include <avr/io.h>
#define F_CPU 10000000UL
#include <util/delay.h>

#define line_0 0x00  // 00-13H  2line mode 00 - 27H
#define line_1 0x40  // 40-53H			40 - 67H
//#define line_2 0x14  // 14-27H
//#define line_3 0x54  // 54-67H

#define SET_DRAM_ADDR   0x80     //0x80 default  offset addr 00 in the DDRAM
#define DAR_MASK        0xFC

#define SET_CGRAM_ADDR  0x40
#define CAR_MASK        0x3f

#define WRT_DRAM        0x00
#define DDR_MASK        0xff

#define SET_FUNCTION    0x20   //4 bit mode  0x20  4 bit mode - default p 13
#define IN8_BIT         0x10
#define LN2_BIT         0x08	//2 lines
#define D11_BIT         0x04     //5x10 dots
 
#define SET_DISPLAY     0x08	//display off
#define ON_BIT          0x04	//display on bit
#define CUR_BIT         0x02	//cursorbit on
#define BLK_BIT         0x01	//blink cursor bit on

#define SET_ENTRY_MODE  0x04   //cursor moves left
#define INC_BIT         0x02	//shift right
#define SHF_BIT         0x01	//

#define CLR_DISPLAY     0x01	//clear display

#define SHF_CURSOR      0x10	//shift cursor right AC decrise
#define MOV_BIT         0x08	
#define LFT_BIT         0x04


#define RTN_HOME        0x02 	//return home
#define RD_DISPLAY      0x00

//////////////////////////////////////////////////////////////////////
//
//            port definitions
//
//////////////////////////////////////////////////////////////////////

// define which port the LCD display is connected to:
// (replace with PORTB, DDRB, PINB for port B, etc.)
#define  lcd_port PORTA
#define lcd_direction DDRA
#define  lcd_pin PINA
#define OFFSET  0x40     // 0x40  for 2nd line 1st character 
#define lcd_RS 2  //PA2
#define lcd_E 3   //PA3

// **** Function prototypes ****

extern void lcd_init();
extern void lcdClear(void);
extern void lcd_cmd_write( unsigned char );
extern void lcd_data_write( unsigned char );
extern void lcd_transfer( unsigned char );
extern void lcd_nibble_transfer( unsigned char );
extern void lcd_update();
