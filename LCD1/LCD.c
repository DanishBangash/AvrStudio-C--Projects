/*#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>
#define LCD_PRT 	PORTA  //LCD data port
#define LCD_DDR 	DDRA   // LCD data DDR
#define LCD_PIN 	PINA   // LCD DATA PIN
#define LCD_RW 		1      // LCD RW
#define LCD_RS 		2      //'LCD RS
#define LCD_EN 		3      // LCD EN

	void delay_us(int d)
	{
	   _delay_us(d);
	}

	void delay_ms (int d)
	{
	   _delay_ms(d);
	}

	void lcdCommand(unsigned char cmnd)
	{
	LCD_PRT = (LCD_PRT & 0x0F) | (cmnd & 0xF0);     // 
	LCD_PRT &= ~(1<<LCD_RS);                       //RS = 0 FOR COMMAND
	LCD_PRT &=~(1<<LCD_RW);                       // RW = 0 FOR WRITE
	LCD_PRT|=(1<<LCD_EN);                        //  EN=  1 FOR H-TO-LO
	_delay_us(20);                               //	 WAIT
	LCD_PRT = (LCD_PRT & 0X0F)|(cmnd <<4);
	LCD_PRT |=(1<<LCD_EN);                      // EN=1 FOR HI TO LO
	_delay_us(1);                 				// wait to make EN wider
	LCD_PRT &=~(1<<LCD_EN);						// EN=0 for hi to lo 
	}

void lcdData (unsigned char data)
{
LCD_PRT = (LCD_PRT & 0x0F) | (data & 0xF0);     // 
LCD_PRT |= (1<<LCD_RS);                       //RS = 1 FOR DATA
LCD_PRT &=~(1<<LCD_RW);                       // RW = 0 FOR WRITE
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
unsigned char firstCharAdr[] = {0x80, 0xC0, 0x94, 0xD4};
lcdCommand(firstCharAdr[y-1] + x-1);
_delay_us(100);
}

void lcd_print(char * str)
{
unsigned char i=0;
while (str[i] !=0)
{
lcdData(str[i]);
i++;
}
}
int main(void)
{
lcd_init();
while(1)
{  // stay here for ever 
   lcd_gotoxy(1,1);
   lcd_print("The world is but");
   lcd_gotoxy(1,2);
   lcd_print("one country     ");
   _delay_ms(1000);
   lcd_gotoxy(1,1);
   lcd_print("and mankind its ");
   lcd_gotoxy(1,2);
   lcd_print("citizens        ");
   _delay_ms(1000);
   }
   return 0;
}*/








