#include "keypad.h"
#include "lcdo.h"
void key_look();
 unsigned char row;
unsigned char keytab[4][4]= { {'1','2','3','F'},
							  {'4','5','6','E'},
							  {'7','8','9','D'},
							  {'A','0','B','C'} };

void key_init ()
{
  key_DDRA  |= 0x03;
  key_DDRC  &= 0x3F;
   lcd_init();
}

void key_read()
{
int i= 0 ;
while (!(key_PINB &(1<<key_active)))
{
	switch(i)
	{
	   case 0: key_PORTA &= 0xFC; 					 row=3; break;
	   case 1: key_PORTA &= 0xFC; key_PORTA |= 0x01; row=2; break;
	   case 2: key_PORTA &= 0xFC; key_PORTA |= 0x02; row=1; break;
	   default: 				  key_PORTA |= 0x03; row=0; break;
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
		case 0x40:keyit= keytab[row][2];break;
		case 0x80:keyit= keytab[row][1];break;
		default  :keyit= keytab[row][0];break; 
	}
	while (key_PINB & (1<<key_active));
	
	 lcd_data_write(keyit);
	 _delay_ms(100);
	 
}


}

/*int main(void)
{
key_init();
while(1)
{

key_read();
}
return 0;
}*/
