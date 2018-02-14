#include "keypad.h"
#include "lcd.h"
void key_look();
unsigned char row;
unsigned char keytab[4][4]= { {'1','2','3','F'},
							  {'4','5','6','E'},
							  {'7','8','9','D'},
							  {'A','0','B','C'} };

void key_init ()
{
  key_DDRA  |=(1<<key_row0 )|(1<<key_row1); 
  key_DDRC  &=(1<<key_col0 )|(1<<key_col1); 
  lcd_init();
}

void key_read()
{
int i= 0 ;
while (!(key_PINB &(1<<key_active)))
{
switch(i)
{
row3: key_PORTA &= 0xFC; 					 		  row=3; 		break;
row2: key_PORTA &= 0xFC; key_PORTA |= (1<<key_row0 ); row=2; 		break;
row1: key_PORTA &= 0xFC; key_PORTA |= (1<<key_row1);  row=1; 		break;
default: 		         key_PORTA |= (1<<key_row0 )|(1<<key_row1); row=0; break;
	}
		i++;	
	}
		key_look();	
	}
void key_look()
{
unsigned char column;
unsigned char lastkey;
unsigned char keyit;
			 	lastkey=(key_PINC & 0xC0);
				_delay_ms(20);
				column=(key_PINC & 0xC0);
if(column==lastkey)
{
 	switch(column)
	{
		case 0x00:keyit= keytab[row][3];break;
		case 0x40:keyit= keytab[row][2];break;///column PC6
		case 0x80:keyit= keytab[row][1];break;///column PC7
		default  :keyit= keytab[row][0];break; 
	}
	while (key_PINB & (1<<key_active));
	
	 lcd_data_write(keyit);
	 _delay_ms(100); 
}
}
