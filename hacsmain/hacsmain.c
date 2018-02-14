#include "RFIDstate.h"
#include"Packet.h"
char command;
int flag_pass=1;
	 int main()
	 {
	  	init();   //// timer0 initializing
  		lcd_init(); //// lcd initialization
	 	init_uart( 0x40);// uart initialization 
		SPI_MasterInit();// SPI initialization 
		key_init();      // keypad initialization 
		  while (1)
		  {		
			 	
			 if(flag_pass){
			 EnterPassword();   /// called from keypad 
			 flag_pass=0;
			}
				
		  
	}
	}
ISR(USART_RXC_vect)
{	
	if(isValidate()){
		lcdClear();
		_delay_ms(100);
		receivePacket();
		}
}
