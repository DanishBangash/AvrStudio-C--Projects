#include "lcdo.h"  // File with #define statements and prototypes for the lcdm.c module
#include "Keypad1.h"
#include "press.h"

#include <avr/io.h>
#define F_CPU 10000000UL

#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd.h"
unsigned volatile  char row;
void find_Key();
unsigned char keypad[4][4]= { {'1','2','3','F'},
							  {'4','5','6','E'},
							  {'7','8','9','D'},
							  {'A','0','B','C'} };

void scan_keypad(){
int i=0;

while(!(PINB&(1<<PB2)))

{
	switch(i)
	{ case 0:
			PORTA&=0xFC;
			row=3;
			break;

			case 1:
			PORTA&=0xFC;
			PORTA|=0x01;
			row=2;
			break;

			case 2:
			PORTA&=0xFC;
			PORTA|=0x02;
			row=1;
			break;

			default:
		//	PORTA&=0xFC;
			PORTA|=0x03;
			row=0;		
			break;
		
	}
	i++;
	}

find_Key();
}
void keypad_init()
{
		DDRA|=0x03;
		DDRC&=0x3F;
		lcd_init();

}

void find_Key(){

unsigned volatile char col;
unsigned volatile  char oldcol;
unsigned volatile char res;
				
				//_delay_ms(20);
				oldcol=(PINC&0xC0);
				_delay_ms(20);
				col=(PINC&0xC0);
				if(col==oldcol){
			switch(col)
			{
			case 0x00:
			res=keypad[row][3];
			break;

			case 0x40:
			res=keypad[row][1];
			break;

			case 0x80:
			res=keypad[row][2];
			break;
				
			default:
			res=keypad[row][0];	
			break;	
			
		}	
		//if(res=='C')lcd_cmd_write(CLR_DISPLAY);
	//	else{
		/*	if((res=='F')||(res=='E')||(res=='D')||(res=='C')){
			_delay_ms(10);
			}*/
			while(PINB&(1<<PB2));

			lcd_data_write(res);
			_delay_ms(90);
//}
			 
	}
}




int main(void)
{
//lcd_init();
keypad_init();  
//init();
//DDRB=0b00000000;
//PORTB=0b00000010;
//char lastkey=0;
while(1){
scan_keypad();
//	IsButtonPressed();
/*	char key=

	if( key!= lastkey) {
	lcd_data_write(key);
	_delay_ms(90);

	lastkey=key;
	}*/
}
   return 0;
}
