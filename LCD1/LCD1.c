#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>
#define MrLCDscrib 				PORTA
#define DataDir_MrLCDscrib		DDRA
#define MrLCDsControl 			PORTA
#define DataDir_MrLCDControl    DDRA
#define LightSwitch 			3
#define Readwrite 				7
#define BiPolarMood 			2

void check_if_MrLCD_isbusy(void);
void Peek_A_Boo(void);
void Send_A_command(unsigned char command);
void Send_A_character(unsigned char character);

void Send_A_Command(unsigned char command)
{
 check_if_MrLCD_isbusy();
 MrLCDscrib=command;
 MrLCDsControl &= ~ (1<<BiPolarMood);///1<<Readwrite|
 Peek_A_Boo();
 MrLCDscrib = 0;
}
int main(void)
{  
   DataDir_MrLCDControl |=1<<LightSwitch |1<<BiPolarMood;//|1<<Readwrite 
   _delay_ms(15);
   
   Send_A_Command(0x38);
   _delay_us(50);
  
   Send_A_Command(0b00001110);
   _delay_us(50);
      
   Send_A_character(0x65); //
   Send_A_character(0x77); //
   Send_A_character(0x62); //
   Send_A_character(0x69); //
  Send_A_character(0x65); //
   Send_A_character(0x48); //
   Send_A_character(0x61); //
   Send_A_character(0x63); //
   Send_A_character(0x6B); //
   Send_A_character(0x2E); //
   Send_A_character(0x63); //
   Send_A_character(0x6F); //
   Send_A_character(0x6D); // 
   
   Send_A_Command(0x01); //clear screen 0x01
   _delay_ms(2);
   while(1)
   {
   }
}
void check_if_MrLCD_isbusy()
{
 DataDir_MrLCDscrib = 0;
 MrLCDsControl |= 1<<Readwrite;
 MrLCDsControl &= ~1<<BiPolarMood;
 while( MrLCDscrib>= 0x80)
 {
   Peek_A_Boo();
 }



 DataDir_MrLCDscrib =0xFF; 
}
void Peek_A_Boo()
{
 MrLCDsControl |= 1<<LightSwitch;
 asm volatile ("nop");
 asm volatile ("nop");
 MrLCDsControl &=~1<<LightSwitch;
}


void Send_A_character(unsigned char character)
{
check_if_MrLCD_isbusy();
MrLCDscrib = character;
MrLCDsControl &= ~ (1<<Readwrite);
MrLCDsControl |=1<<BiPolarMood;
 Peek_A_Boo();
 MrLCDscrib = 0;
}
